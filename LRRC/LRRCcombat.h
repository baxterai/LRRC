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
 * File Name: LRRCcombat.h
 * Author: Richard Bruce Baxter - Copyright (c) 2005-2017 Baxter AI (baxterai.com)
 * Project: Lego Rules CG Rounds Checker
 * Project Version: 3j1b 14-January-2017
 * Project First Internal Release: 1aXx 18-Sept-05 (C)
 * Project Second Internal Release: 2aXx 02-April-06 (convert to C++)
 * Project Third Internal Release: 2b7d 26-Sept-06 (added sprites)
 * Project Fourth Internal Release: 2c4a 25-Feb-07 [rotation of models supported, copyCombatRelevantInheritedImmediateParentUnitDetailsIntoChildObject() no longer used]
 * Project Fifth Internal Release: 2d11a 3-June-07
 *
 *******************************************************************************/


#ifndef HEADER_LRRC_COMBAT
#define HEADER_LRRC_COMBAT

#include "LDreferenceClass.h"
#include "LDparser.h"
#include "LRRCrules.h"
#include "LRRCparser.h"
#include "SHAREDvector.h"
#include "SHAREDvars.h"

#define CLOSE_AND_LONGDISTANCE_COMBAT_BOUNDARY_NAME "CLOSE_AND_LONGDISTANCE_COMBAT_BOUNDARY"
#define RANGE_MODIFIER_BASED_ON_INCREASED_HEIGHT_NAME "RANGE_MODIFIER_BASED_ON_INCREASED_HEIGHT"
//#define CLOSE_AND_LONGDISTANCE_COMBAT_BOUNDARY (4)		//distance given in cm
//#define RANGE_MODIFIER_BASED_ON_INCREASED_HEIGHT //0.2	//distance given in cm

#define ABS_OF_SHORT 32767.0
	//this is the same as RAND_MAX C++ constant

#define ATTACK_ERROR_FILE_IO 0
#define ATTACK_NEITHER_UNIT_CAN_STRIKE 1
#define ATTACK_BOTH_UNITS_STRIKE_BOTH_CAN_STRIKE 2
#define ATTACK_NEITHER_UNITS_STRIKE_BOTH_CAN_STRIKE 3
#define ATTACK_UNIT1_STRIKES_BOTH_CAN_STRIKE 4
#define ATTACK_UNIT1_STRIKES_UNIT1_CAN_STRIKE 5
#define ATTACK_NEITHER_STRIKES_UNIT1_CAN_STRIKE 6
#define ATTACK_UNIT2_STRIKES_BOTH_CAN_STRIKE 7
#define ATTACK_UNIT2_STRIKES_UNIT2_CAN_STRIKE 8
#define ATTACK_NEITHER_STRIKES_UNIT2_CAN_STRIKE 9
#define TOTAL_NUMBER_OF_COMBAT_OUTCOMES 10

#define DEFAULT_COLOUR_OF_SUB_MODEL_CURRENTLY_BEING_SEARCHED_FOR 0





extern double CLOSE_AND_LONGDISTANCE_COMBAT_BOUNDARY;
extern double RANGE_MODIFIER_BASED_ON_INCREASED_HEIGHT;




class LRRCcombatClass
{
	private: LRRCmodelClassClass LRRCmodelClass;
	private: LDparserClass LDparser;
	private: LDreferenceClassClass LDreferenceClass;
	private: SHAREDvarsClass SHAREDvars;
	private: SHAREDvectorClass SHAREDvector;
	public: void fillInCombatExternVariables();

//combat routines supported by rules checker software (see preconditions and postconditions of functions for their requirements)
//* ******
	public: bool calculateUnitClassBasic(string unitFileName);
	public: int performCloseCombatBasic(string unit1FileName, string unit2FileName, const bool unit1performsCloseCombatAttack, const bool unit2performsCloseCombatAttack, const bool unit1TakesTheInitative, const bool unit2TakesTheInitative);
	public: int performLongDistanceCombatBasic(string unit1FileName, string unit2FileName, bool unit1performsLongDistanceAttack, bool unit2performsLongDistanceAttack);

//* ******
	public: int performLongDistanceCombatWithSceneFile(const string unit1FileName, const string unit2FileName, const int unit1ID, const int unit2ID, bool unit1intendsToPerformLongDistanceAttack, bool unit2intendsToPerformLongDistanceAttack, string thisPhaseStartSceneFileName);
		public: int performCloseCombatWithScene(const string unit1FileName, const string unit2FileName, const int unit1ID, const int unit2ID, const bool unit1intendsToPerformCloseCombatAttack, const bool unit2intendsToPerformCloseCombatAttack, LDreference* initialReferenceInThisPhaseStartScene);
	public: int performCloseCombatWithSceneFile(const string unit1FileName, const string unit2FileName, const int unit1ID, const int unit2ID, const bool unit1intendsToPerformCloseCombatAttack, const bool unit2intendsToPerformCloseCombatAttack, string thisPhaseStartSceneFileName);
		public: int performCloseCombatWithConsecutiveScenes(const string unit1FileName, const string unit2FileName, const int unit1ID, const int unit2ID, const bool unit1intendsToPerformCloseCombatAttack, const bool unit2intendsToPerformCloseCombatAttack, LDreference* initialReferenceInThisPhaseStartScene, LDreference* initialReferenceInPreMovementPhaseScene);
	public: int performCloseCombatWithConsecutiveSceneFiles(const string unit1FileName, const string unit2FileName, const int unit1ID, const int unit2ID, const bool unit1intendsToPerformCloseCombatAttack, const bool unit2intendsToPerformCloseCombatAttack, string thisPhaseStartSceneFileName, string preMovementPhaseSceneFileName);
		public: int performLongDistanceCombatWithScene(const string unit1FileName, const string unit2FileName, const int unit1ID, const int unit2ID, bool unit1intendsToPerformLongDistanceAttack, bool unit2intendsToPerformLongDistanceAttack, LDreference* initialReferenceInThisPhaseStartScene);
	public: int performLongDistanceCombatWithConsecutiveSceneFiles(const string unit1FileName, const string unit2FileName, const int unit1ID, const int unit2ID, const bool unit1intendsToPerformLongDistanceAttack, const bool unit2intendsToPerformLongDistanceAttack, string thisPhaseStartSceneFileName, string preMovementPhaseSceneFileName);
		public: int performLongDistanceCombatWithConsecutiveScenes(const string unit1FileName, const string unit2FileName, const int unit1ID, const int unit2ID, const bool unit1intendsToPerformLongDistanceAttack, const bool unit2intendsToPerformLongDistanceAttack, LDreference* initialReferenceInThisPhaseStartScene, LDreference* initialReferenceInPreMovementPhaseScene);

//* ******
	public: bool calculateUnitClassNormal(string unitFileName);
	public: int performCloseCombatNormal(string unit1FileName, string unit2FileName, const bool unit1performsCloseCombatAttack, const bool unit2performsCloseCombatAttack);
	public: int performLongDistanceCombatNormal(string unit1FileName, string unit2FileName, bool unit1performsLongDistanceAttack, bool unit2performsLongDistanceAttack);

//combat unit properties post parser (reference list searching)
	public: bool searchSceneReferenceListAndDetermineTheDetailsOfAParticularUnitSubmodel(LDreference* referenceBeingSearchedFor, LDreference* initialReference, const LDreference* parentReference, const bool isFillingParentUnitWithAllCombatRelevantChildModelDetails);
	private: bool compareSubmodelNamesAndIfSameCopySubmodelReference(LDreference* referenceBeingSearchedFor, LDreference* referenceCurrentlyFoundDuringSearch);

//combat routines invoked with well established combat parameters and ModelDetails details
	private: int performCloseCombatWithReferences(LDreference* unit1ReferenceInThisPhaseStartSceneFile, LDreference* unit2ReferenceInThisPhaseStartSceneFile, const bool unit1intendsToPerformCloseCombatAttack, const bool unit2intendsToPerformCloseCombatAttack, const bool unit1TakesTheInitative, const bool unit2TakesTheInitative);
		private: int performCloseCombat(ModelDetails* unit1, ModelDetails* unit2, const bool unit1performsCloseCombatAttack, const bool unit2performsCloseCombatAttack, const bool unit1TakesTheInitative, const bool unit2TakesTheInitative);
	private: int performLongDistanceCombatWithReferences(LDreference* unit1ReferenceInThisPhaseStartSceneFile, LDreference* unit2ReferenceInThisPhaseStartSceneFile, bool unit1HasNotMovedInPreviousRoundAndIntendsToPerformLongDistanceAttack, bool unit2HasNotMovedInPreviousRoundAndIntendsToPerformLongDistanceAttack);
		private: int performLongDistanceCombat(const ModelDetails* unit1, const ModelDetails* unit2, bool unit1performsLongDistanceAttack, bool unit2performsLongDistanceAttack);


	public: void performFinalUnitClassCalculations(ModelDetails* u);
	public: void performFinalUnitGroupClassCalculations(ModelDetails* u);
	private: int calculateCloseCombatAttackBonus(ModelDetails* unit, const bool unit2HasHorse, const bool unitTakesInitative);
	public: void calculateLongDistanceAttackBonus(LDreference* unit1ReferenceInThisPhaseStartSceneFile, LDreference* unit2ReferenceInThisPhaseStartSceneFile, const bool unit1HasNotMovedInPreviousRoundAndIntendsToPerformLongDistanceAttack, const bool unit2HasNotMovedInPreviousRoundAndIntendsToPerformLongDistanceAttack, bool* unit1CanPerformLongDistanceAttack, bool* unit2CanPerformLongDistanceAttack, const double distanceBetweenUnitsForLDTest);
	private: bool performUnitOrdinatesCheck(const ModelDetails* u);

//range calculations
	private: bool calculateIfTwoUnitsAreWithinAGivenLongRangeAttackDistance(const double positionXOfUnit1, const double positionXOfUnit2, const double positionYOfUnit1, const double positionYOfUnit2, const double positionZOfUnit1, const double positionZOfUnit2, const int maximumDistance, const int minimumDistance);
	public: double calculateTheDistanceBetweenTwoUnits(vec* positionOfUnit1, vec* positionOfUnit2);
	public: double calculateTheDistanceBetweenTwoUnits(const double positionXOfUnit1, const double positionXOfUnit2, const double positionYOfUnit1, const double positionYOfUnit2, const double positionZOfUnit1, const double positionZOfUnit2);
	private: bool calculateIfUnitIsWithinAGivenLongRangeAttackDistance(const double distanceBetweenTheTwoUnits, const int maximumDistance, const int minimumDistance);
//double calculateExtraHorizontalDistanceOfProjectileWithHeightAdvantage(double verticalHeightAdvantage, double maxHorizRangeOfWeapon);
	private: int calculateLongDistanceRangeModifier(const LDreference* targetUnitReference, const LDreference* unitReference);
};



#endif

