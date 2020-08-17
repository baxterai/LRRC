/*******************************************************************************
 *
 * This file is part of BAIPROJECT.
 *
 * BAIPROJECT is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License version 3
 * only, as published by the Free Software Foundation.
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
 * File Name: LRRCrules.h
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


#ifndef HEADER_LRRC_RULES
#define HEADER_LRRC_RULES

#include "SHAREDglobalDefs.h"
#include "XMLparserClass.h"
#include "XMLrulesClass.h"

extern XMLrulesClass* LRRCrulesUnitTypeDetails;
extern XMLrulesClass* LRRCrulesUnitCombatDetailsDefenceHead;
extern XMLrulesClass* LRRCrulesUnitCombatDetailsDefenceTorso;
extern XMLrulesClass* LRRCrulesUnitCombatDetailsDefenceShield;
extern XMLrulesClass* LRRCrulesUnitCombatDetailsAttackCloseCombat;
extern XMLrulesClass* LRRCrulesUnitCombatDetailsAttackLongDistance;
extern XMLrulesClass* LRRCrulesBuildingDetails;
extern XMLrulesClass* LRRCrulesTerrainDetails;
extern XMLrulesClass* LRRCrulesUnitTypeCatagories;
extern XMLrulesClass* LRRCrulesMiscellaneous;
extern XMLrulesClass* LRRCrulesSprite;

//there really should be child classes of XMLrulesClass called LRRCrulesUnitTypeDetails, unitCombatDetailsAttack, and unitCombatDetailsDefence that inherit rulesObject and include unique parameters

class LRRCrulesClass
{
	private: XMLparserClassClass XMLparserClass;
	private: XMLrulesClassClass XMLrulesClassObject;
	public: bool parseLRRCrulesXMLfile();
		private: bool parseLRRCrulesTag(XMLparserTag* currentTag);
			private: bool parseTagUnitCombatDetails(XMLparserTag* currentTag);
				private: bool parseTagArmour(XMLparserTag* currentTag);
					private: bool parseTagHead(XMLparserTag* currentTag);
					private: bool parseTagTorso(XMLparserTag* currentTag);
					private: bool parseTagShield(XMLparserTag* currentTag);
				private: bool parseTagWeapons(XMLparserTag* currentTag);
					private: bool parseTagCloseCombat(XMLparserTag* currentTag);
					private: bool parseTagLongDistanceCombat(XMLparserTag* currentTag);
};




#endif
