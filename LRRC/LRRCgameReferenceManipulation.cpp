/*******************************************************************************
 *
 * This file is part of BAIPROJECT.
 *
 * BAIPROJECT is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License version 3
 * only, as published by the Free Software Foundation. The use of
 * intermediary programs or interfaces including file i/o is considered
 * remote network interaction. This does not imply such arrangements
 * do not constitute derivative works.
 *
 * BAIPROJECT is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License version 3 for more details
 * (a copy is included in the LICENSE file that accompanied this code).
 *
 * You should have received a copy of the GNU Affero General Public License
 * version 3 along with BAIPROJECT.  If not, see <http://www.gnu.org/licenses/>
 * for a copy of the AGPLv3 License.
 *
 *******************************************************************************/

/*******************************************************************************
 *
 * File Name: LRRCgameReferenceManipulation.cpp
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2014 Baxter AI (baxterai.com)
 * Project: Lego Rules CG Rounds Checker
 * Project Version: 3e3a 01-September-2014
 * Project First Internal Release: 1aXx 18-Sept-05 (C)
 * Project Second Internal Release: 2aXx 02-April-06 (convert to C++)
 * Project Third Internal Release: 2b7d 26-Sept-06 (added sprites)
 * Project Fourth Internal Release: 2c4a 25-Feb-07 [rotation of models supported, copyCombatRelevantInheritedImmediateParentUnitDetailsIntoChildObject() no longer used]
 * Project Fifth Internal Release: 2d11a 3-June-07
 *
 *******************************************************************************/

#include "LRRCgameReferenceManipulation.h"
#include "LDreferenceManipulation.h"
#include "SHAREDvector.h"
#include "LDparser.h"

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <iostream>
#include <fstream>
#include <time.h>
#include <math.h>
using namespace std;




/*secondary game routines*/

Reference * searchReferenceListRemoveReference(Reference * initialReferenceInSceneFile, char * unitFileName, int unitColour, bool * unitIDFound, bool * result)
{
	Reference * modInitialReferenceInSceneFile = initialReferenceInSceneFile;

	Reference * currentReference = initialReferenceInSceneFile;
	Reference * previousReference = NULL;

	while(currentReference->next != NULL)
	{
		bool unitIDFoundInCurrentReference = false;

		if(currentReference->isSubModelReference)
		{
			if(compareReferenceNameAndColour(currentReference, unitFileName, unitColour))
			{
				if(*unitIDFound == true)
				{
					*result = false;
					cout << "Invalid Scene File - multiple units exist with same unit name and ID (colour)" << endl;
					cout << "searchReferenceListRemoveReference, unitFileName=" << unitFileName << " unitColour=" << unitColour;
				}
				else
				{
					*unitIDFound = true;
					unitIDFoundInCurrentReference = true;

					if(previousReference != NULL)
					{
						previousReference->next = currentReference->next;
					}
					else
					{
						modInitialReferenceInSceneFile = currentReference->next;
					}

				}
			}
			else
			{
				searchReferenceListRemoveReference(currentReference->firstReferenceWithinSubModel, unitFileName, unitColour, unitIDFound, result);
			}
		}

		previousReference = currentReference;
		currentReference = currentReference->next;

		if(unitIDFoundInCurrentReference == true)
		{
			previousReference->firstReferenceWithinSubModel = NULL;
			previousReference->next = NULL;

			delete (previousReference);	//remove found unit from reference tree
		}
	}


	return modInitialReferenceInSceneFile;

}


/*
void searchReferenceListAssignHasPerformedCombat(int currentPhase, Reference * initialReferenceInSceneFile, char * unitFileName, int unitColour, bool * unitIDFound, bool * result)
{
	Reference * currentReference = initialReferenceInSceneFile;
	while(currentReference->next != NULL)
	{
		if(currentReference->isSubModelReference)
		{
			if(compareReferenceNameAndColour(currentReference, unitFileName, unitColour))
			{
				if(*unitIDFound == true)
				{
					*result = false;
					cout << "Invalid Scene File - multiple units exist with same unit name and ID (colour)" << endl;
					cout << "searchReferenceListAssignHasPerformedCombat, unitFileName=" << unitFileName << " unitColour=" << unitColour;
				}
				else
				{
					*unitIDFound = true;
					currentReference->subModelDetails->hasPerformedAction[currentPhase] = true;
				}
			}

			searchReferenceListAssignHasPerformedCombat(currentPhase, currentReference->firstReferenceWithinSubModel, unitFileName, unitColour, unitIDFound, result);
		}

		currentReference = currentReference->next;
	}
}
*/

Reference * searchReferenceListFindReference(Reference * initialReferenceInSceneFile, string unitFileName, int unitColour, bool * unitIDFound, bool * result)
{
	Reference * foundReference = NULL;
	Reference * currentReference = initialReferenceInSceneFile;
	while(currentReference->next != NULL)
	{
		if(currentReference->isSubModelReference)
		{
			if(compareReferenceNameAndColour(currentReference, unitFileName, unitColour))
			{
				if(*unitIDFound == true)
				{
					*result = false;
				}
				else
				{
					*unitIDFound = true;


					foundReference = currentReference;

					//cout << "currentReference->name = " << currentReference->name << endl;
					//cout << "foundReference->name = " << foundReference->name << endl;

				}
			}

			bool tempUnitIDFound = false;
			Reference * tempReferenceFound;
			tempReferenceFound = searchReferenceListFindReference(currentReference->firstReferenceWithinSubModel, unitFileName, unitColour, &tempUnitIDFound , result);
			if(tempUnitIDFound)
			{
				foundReference = tempReferenceFound;
				*unitIDFound = true;
			}
		}

		currentReference = currentReference->next;
	}

	return foundReference;
}


void searchReferenceListPrintReferenceDetails(Reference * initialReferenceInSceneFile)
{
	Reference * currentReference = initialReferenceInSceneFile;
	while(currentReference->next != NULL)
	{

		if(currentReference->isSubModelReference)
		{
			cout << "currentReference->name = " << currentReference->name << endl;

			/*
			cout << "currentReference->colour = " << currentReference->colour << endl;
			cout << "x rel = " << currentReference->relativePosition.x << endl;
			cout << "y rel = " << currentReference->relativePosition.y << endl;
			cout << "z rel = " << currentReference->relativePosition.z << endl;
			cout << "x abs = " << currentReference->absolutePosition.x << endl;
			cout << "y abs = " << currentReference->absolutePosition.y << endl;
			cout << "z abs = " << currentReference->absolutePosition.z << endl;
			*/
			searchReferenceListPrintReferenceDetails(currentReference->firstReferenceWithinSubModel);
		}

		currentReference = currentReference->next;
	}
}




bool obtainUserInputInt(int * userInputInt)
{
	bool result = true;

	bool UIstatus = true;
	char answerAsString[100];
	int answerAsInt;

	while(UIstatus == true)
	{

		cout << ">> ";
		cin >> answerAsString;
		answerAsInt = int(atof(answerAsString));

		if(answerAsInt > 0)
		{
			*userInputInt = answerAsInt;

			UIstatus = false;
		}
		else
		{
			cout << "Invalid answer, please try again" << endl;
		}
	}

	return result;
}











bool obtainUnitDetailsFromUserWOSceneRef(int currentPhase, char * unit1FileName, char * unit2FileName, int * unit1ID, int * unit2ID, char * sceneFileName)
{
	bool result = true;

	Reference * initialReferenceInSceneFile = new Reference();
	Reference * topLevelReferenceInSceneFile = new Reference(sceneFileName, 1, true);	//The submodel information in this object is not required or meaningful, but needs to be passed into the parseFile/parseReferenceList recursive function

	if(!parseFile(sceneFileName, initialReferenceInSceneFile, topLevelReferenceInSceneFile, false))
	{//file does not exist
		cout << "The file: " << sceneFileName << " does not exist in the directory" << endl;
		result = false;
	}

	obtainUnitDetailsFromUserForCombat(unit1FileName, unit2FileName, unit1ID, unit2ID, initialReferenceInSceneFile);

#ifdef GAME_USE_COLOUR_AS_UNIQUE_UNIT_IDS
	if(!determineUnitNamesWithColours(currentPhase, unit1FileName, unit2FileName, *unit1ID, *unit2ID, initialReferenceInSceneFile))
	{
		result = false;
	}
#else

	if(!determineIfUnitsExists(currentPhase, unit1FileName, unit2FileName, *unit1ID, *unit2ID, initialReferenceInSceneFile))
	{
		result = false;
	}
#endif

	delete initialReferenceInSceneFile;
	delete topLevelReferenceInSceneFile;

	return result;
}



bool obtainUnitDetailsFromUserForCombat(char * unit1FileName, char * unit2FileName, int * unit1ID, int * unit2ID, Reference * initialReferenceInSceneFile)
{
	bool result = true;

	char answerAsString[100];
	long answerAsInt;

	cout << "Enter Unit 1 ID (Eg '1'):";
	cin >> answerAsString;
	answerAsInt = int(atof(answerAsString));
	*unit1ID = answerAsInt;

	cout << "Enter Unit 2 ID (Eg '2'):";
	cin >> answerAsString;
	answerAsInt = int(atof(answerAsString));
	*unit2ID = answerAsInt;


#ifndef GAME_USE_COLOUR_AS_UNIQUE_UNIT_IDS
	cout << "Enter Unit 1 Name (Eg 'unit1.ldr'):";
	cin >> unit1FileName;

	cout << "Enter Unit 2 Name (Eg 'unit2.ldr'):";
	//cin.get(unit2FileName, 50);
	cin >> unit2FileName;

#endif

	return result;
}


bool determineIfUnitsExists(int currentPhase, char * unitAttackerFileName, char * unitDefenderFileName, int unitAttackerPlayerID, int unitDefenderPlayerID, Reference * initialReferenceInSceneFile)
{
	bool result = true;

	bool unitIDFound;

	unitIDFound = false;
	parseRefListCheckUnitExists(currentPhase, initialReferenceInSceneFile, unitAttackerFileName, unitAttackerPlayerID, &unitIDFound, &result);
	if(!unitIDFound)
	{
		cout << "Problem: Combat Ready player " << unitAttackerPlayerID << " unit name " << unitAttackerFileName << " cannot be found," << endl;
		result = false;
	}
	unitIDFound = false;
	parseRefListCheckUnitExists(currentPhase, initialReferenceInSceneFile, unitDefenderFileName, unitDefenderPlayerID, &unitIDFound, &result);
	if(!unitIDFound)
	{
		cout << "Problem: Combat Ready player " << unitDefenderPlayerID << " unit name " << unitDefenderFileName << " cannot be found," << endl;
		result = false;
	}

	return result;
}


bool determineUnitNamesWithColours(int currentPhase, char * unit1FileName, char * unit2FileName, int unit1ID, int unit2ID, Reference * initialReferenceInSceneFile)
{
	bool result = true;

	bool unitIDFound;
	unitIDFound = false;
	parseRefListDetRefNames(currentPhase, initialReferenceInSceneFile, unit1FileName, unit1ID, &unitIDFound, &result);
	if(!unitIDFound)
	{
		cout << "Problem: Combat Ready Unit 1 ID " << unit1ID << "not found." << endl;
		result = false;
	}
	unitIDFound = false;
	parseRefListDetRefNames(currentPhase, initialReferenceInSceneFile, unit2FileName, unit2ID, &unitIDFound, &result);
	if(!unitIDFound)
	{
		cout << "Problem: Combat Ready Unit 2 ID " << unit2ID << "not found." << endl;
		result = false;
	}

	return result;

}


void parseRefListCheckUnitExists(int currentPhase, Reference * initialReferenceInSceneFile, char * unitFileName, int unitColour, bool * unitIDFound, bool * result)
{
	Reference * currentReference = initialReferenceInSceneFile;
	while(currentReference->next != NULL)
	{
		if(currentReference->isSubModelReference)
		{
			if(compareReferenceNameAndColour(currentReference, unitFileName, unitColour))
			{

				if(*unitIDFound == true)
				{
					*result = false;
					cout << "parseRefListCheckUnitExists, Invalid Scene File - multiple units exist with same unit name and ID (colour), unitFileName=" << unitFileName << " unitColour=" << unitColour << endl;
				}
				else
				{
					*unitIDFound = true;
				}
			}

			parseRefListCheckUnitExists(currentPhase, currentReference->firstReferenceWithinSubModel, unitFileName, unitColour, unitIDFound, result);
		}

		currentReference = currentReference->next;
	}
}


void parseRefListDetRefNames(int currentPhase, Reference * reference, char * referenceName, int referenceColour, bool * unitIDFound, bool * result)
{
	Reference * currentReference = reference;
	while(currentReference->next != NULL)
	{
		if(currentReference->isSubModelReference)
		{
			if(currentReference->colour == referenceColour)
			{
				if(*unitIDFound == true)
				{
					cout << "Invalid Scene File - multiple units exist with same unit ID (colour)" << endl;
					*result = false;
				}
				else
				{
					*unitIDFound = true;
					strcpy(referenceName, (currentReference->name).c_str());
				}
			}

			parseRefListDetRefNames(currentPhase, currentReference->firstReferenceWithinSubModel, referenceName, referenceColour, unitIDFound, result);
		}
		currentReference = currentReference->next;
	}
}






