#ifndef DEHACKEDDATA_H
#define DEHACKEDDATA_H

#include "dehackedParser.h"
#include <iostream>
#include <functional>
#include <vector>

//This file contains the necessary arrays needed for parsing dehacked files

//These structs associate strings to functions
struct stringAction
{
    std::string str;
    std::function <void( std::ifstream& fileStream, std::string number, base::baseArray& )> foo;
};

struct stringAction2
{
    std::string str;
    std::function <void( std::string value, base::baseArray&, int number )> foo;
};

struct stringValues
{
    std::string str;
    uint32_t value;
};

//These functions must necessarily be defined in here
namespace dehacked
{
    void dehackedReadDoomSet( std::ifstream &fileStream, std::string setValue, base::baseArray &DoomBase, std::vector<stringAction2> strAct );
    void dehackedReadFlags(std::string value, base::baseArray &DoomBase, int number);
    void dehackedReadBoomCodep( std::ifstream &fileStream, base::baseArray &DoomBase);
    void dehackedSkip( std::ifstream &fileStream);
}

//==========================================================================
//
//  NUMERICAL CONSTANTS
//
//==========================================================================

//Radius and Height are scaled up by this value in DEHACKED
const int THINGSCALE = 0x10000;

//These are the name of the flags and their values
const std::vector<stringValues> FLAGVALUES
{
	{"SPECIAL",		 0x00000001},
	{"SOLID",		 0x00000002},
	{"SHOOTABLE",	 0x00000004},
	{"NOSECTOR",	 0x00000008},
	{"NOBLOCKMAP",	 0x00000010},
	{"AMBUSH",		 0x00000020},
	{"JUSTHIT",		 0x00000040},
	{"JUSTATTACKED", 0x00000080},
	{"SPAWNCEILING", 0x00000100},
	{"NOGRAVITY",	 0x00000200},
	{"DROPOFF",		 0x00000400},
	{"PICKUP",		 0x00000800},
	{"NOCLIP",		 0x00001000},
	{"SLIDE",		 0x00002000},
	{"FLOAT",		 0x00004000},
	{"TELEPORT",	 0x00008000},
	{"MISSILE",		 0x00010000},
	{"DROPPED",		 0x00020000},
	{"SHADOW",		 0x00040000},
	{"NOBLOOD",		 0x00080000},
	{"CORPSE",		 0x00100000},
	{"INFLOAT",		 0x00200000},
	{"COUNTKILL",	 0x00400000},
	{"COUNTITEM",	 0x00800000},
	{"SKULLFLY",	 0x01000000},
	{"NOTDMATCH",	 0x02000000},
	{"TRANSLATION1", 0x04000000},
	{"TRANSLATION2", 0x08000000},
	{"TOUCHY",		 0x10000000},
	{"BOUNCES",		 0x20000000},
	{"FRIEND",		 0x40000000},
	{"TRANSLUCENT",	 0x80000000},
	//Aliases
    {"TRANSLATION",	 0x04000000},
    {"UNUSED1",		 0x08000000},
    {"UNUSED2",		 0x10000000},
    {"UNUSED3",		 0x20000000},
    {"UNUSED4",		 0x40000000},
};

// Table of which states in MBF have Actions by default (need for Doom Codep format)
const int CODEPLIST[]
{
	  1,   2,   3,   4,   6,   9,  10,  11,  12,  14,
	 16,  17,  18,  19,  20,  22,  29,  30,  31,  32,
	 33,  34,  36,  38,  39,  41,  43,  44,  47,  48,
	 49,  50,  51,  52,  53,  54,  55,  56,  57,  58,
	 59,  60,  61,  62,  63,  65,  66,  67,  68,  69,
	 70,  71,  72,  73,  74,  75,  76,  77,  78,  79,
	 80,  81,  82,  83,  84,  85,  86,  87,  88,  89,
	119, 127, 157, 159, 160, 166, 167, 174, 175, 176,
	177, 178, 179, 180, 181, 182, 183, 184, 185, 188,
	190, 191, 195, 196, 207, 208, 209, 210, 211, 212,
	213, 214, 215, 216, 217, 218, 221, 223, 224, 228,
	229, 241, 242, 243, 244, 245, 246, 247, 248, 249,
	250, 251, 252, 253, 254, 255, 256, 257, 258, 259,
	260, 261, 262, 263, 264, 270, 272, 273, 281, 282,
	283, 284, 285, 286, 287, 288, 289, 290, 291, 292,
	293, 294, 295, 296, 297, 298, 299, 300, 301, 302,
	303, 304, 305, 306, 307, 308, 309, 310, 316, 317,
	321, 322, 323, 324, 325, 326, 327, 328, 329, 330,
	331, 332, 333, 334, 335, 336, 337, 338, 339, 340,
	341, 342, 344, 347, 348, 362, 363, 364, 365, 366,
	367, 368, 369, 370, 371, 372, 373, 374, 375, 376,
	377, 378, 379, 380, 381, 382, 383, 384, 385, 387,
	389, 390, 397, 406, 407, 408, 409, 410, 411, 412,
	413, 414, 415, 416, 417, 418, 419, 421, 423, 424,
	430, 431, 442, 443, 444, 445, 446, 447, 448, 449,
	450, 451, 452, 453, 454, 456, 458, 460, 463, 465,
	475, 476, 477, 478, 479, 480, 481, 482, 483, 484,
	485, 486, 487, 489, 491, 493, 502, 503, 504, 505,
	506, 508, 511, 514, 527, 528, 529, 530, 531, 532,
	533, 534, 535, 536, 537, 538, 539, 541, 543, 545,
	548, 556, 557, 558, 559, 560, 561, 562, 563, 564,
	565, 566, 567, 568, 570, 572, 574, 585, 586, 587,
	588, 589, 590, 594, 596, 598, 601, 602, 603, 604,
	605, 606, 607, 608, 609, 610, 611, 612, 613, 614,
	615, 616, 617, 618, 620, 621, 622, 631, 632, 633,
	635, 636, 637, 638, 639, 640, 641, 642, 643, 644,
	645, 646, 647, 648, 650, 652, 653, 654, 659, 674,
	675, 676, 677, 678, 679, 680, 681, 682, 683, 684,
	685, 686, 687, 688, 689, 690, 692, 696, 700, 701,
	702, 703, 704, 705, 706, 707, 708, 709, 710, 711,
	713, 715, 718, 726, 727, 728, 729, 730, 731, 732,
	733, 734, 735, 736, 737, 738, 739, 740, 741, 743,
	745, 746, 750, 751, 766, 774, 777, 779, 780, 783,
	784, 785, 786, 787, 788, 789, 790, 791, 792, 793,
	794, 795, 796, 797, 798, 801, 809, 811, // 448th
	// Now for the 74 MBF states with code pointers
	968, 969, 970, 972, 973, 974, 975, 976, 977, 978,
	979, 980, 981, 982, 983, 984, 986, 988, 990, 999,
	1000, 1001, 1002, 1003, 1004, 1005, 1006, 1007,
	1008, 1009, 1010, 1011, 1012, 1013, 1014, 1015,
	1016, 1017, 1018, 1019, 1020, 1021, 1022, 1023,
	1024, 1025, 1026, 1027, 1028, 1029, 1030, 1031,
	1032, 1033, 1034, 1035, 1036, 1037, 1038, 1039,
	1040, 1041, 1056, 1057, 1058, 1059, 1060, 1061,
	1062, 1065, 1071, 1073, 1074, 1075 // Total: 522
};

// Table of what actions occur at each state (need for Doom Codep format)
const std::string ACTIONLIST[]
{
	"NULL", "Light0", "WeaponReady", "Lower", "Raise", "NULL",
	"Punch", "NULL", "NULL", "ReFire", "WeaponReady", "Lower",
	"Raise", "NULL", "FirePistol", "NULL", "ReFire", "Light1",
	"WeaponReady", "Lower", "Raise", "NULL", "FireShotgun", "NULL",
	"NULL", "NULL", "NULL", "NULL", "NULL", "ReFire", "Light1",
	"Light2", "WeaponReady", "Lower", "Raise", "NULL",
	"FireShotgun2", "NULL", "CheckReload", "OpenShotgun2", "NULL",
	"LoadShotgun2", "NULL", "CloseShotgun2", "ReFire", "NULL", "NULL",
	"Light1", "Light2", "WeaponReady", "Lower", "Raise",
	"FireCGun", "FireCGun", "ReFire", "Light1", "Light2",
	"WeaponReady", "Lower", "Raise", "GunFlash", "FireMissile",
	"ReFire", "Light1", "NULL", "Light2", "Light2", "WeaponReady",
	"WeaponReady", "Lower", "Raise", "Saw", "Saw", "ReFire",
	"WeaponReady", "Lower", "Raise", "FirePlasma", "ReFire",
	"Light1", "Light1", "WeaponReady", "Lower", "Raise",
	"BFGsound", "GunFlash", "FireBFG", "ReFire", "Light1",
	"Light2", "NULL", "NULL", "NULL", "NULL", "NULL", "NULL", "NULL",
	"NULL", "NULL", "NULL", "NULL", "NULL", "NULL", "NULL", "NULL", "NULL",
	"NULL", "NULL", "NULL", "NULL", "NULL", "NULL", "NULL", "NULL", "NULL",
	"NULL", "NULL", "NULL", "NULL", "BFGSpray", "NULL", "NULL", "NULL",
	"NULL", "NULL", "NULL", "NULL", "Explode", "NULL", "NULL", "NULL",
	"NULL", "NULL", "NULL", "NULL", "NULL", "NULL", "NULL", "NULL", "NULL",
	"NULL", "NULL", "NULL", "NULL", "NULL", "NULL", "NULL", "NULL", "NULL",
	"NULL", "NULL", "NULL", "NULL", "NULL", "NULL", "NULL", "NULL",
	"Pain", "NULL", "PlayerScream", "Fall", "NULL", "NULL", "NULL",
	"NULL", "NULL", "XScream", "Fall", "NULL", "NULL", "NULL", "NULL",
	"NULL", "NULL", "Look", "Look", "Chase", "Chase", "Chase",
	"Chase", "Chase", "Chase", "Chase", "Chase", "FaceTarget",
	"PosAttack", "NULL", "NULL", "Pain", "NULL", "Scream", "Fall",
	"NULL", "NULL", "NULL", "XScream", "Fall", "NULL", "NULL", "NULL",
	"NULL", "NULL", "NULL", "NULL", "NULL", "NULL", "NULL", "Look",
	"Look", "Chase", "Chase", "Chase", "Chase", "Chase",
	"Chase", "Chase", "Chase", "FaceTarget", "SPosAttack", "NULL",
	"NULL", "Pain", "NULL", "Scream", "Fall", "NULL", "NULL", "NULL",
	"XScream", "Fall", "NULL", "NULL", "NULL", "NULL", "NULL", "NULL",
	"NULL", "NULL", "NULL", "NULL", "NULL", "Look", "Look",
	"VileChase", "VileChase", "VileChase", "VileChase",
	"VileChase", "VileChase", "VileChase", "VileChase",
	"VileChase", "VileChase", "VileChase", "VileChase",
	"VileStart", "FaceTarget", "VileTarget", "FaceTarget",
	"FaceTarget", "FaceTarget", "FaceTarget", "FaceTarget",
	"FaceTarget", "VileAttack", "NULL", "NULL", "NULL", "NULL", "NULL",
	"Pain", "NULL", "Scream", "Fall", "NULL", "NULL", "NULL", "NULL",
	"NULL", "NULL", "NULL", "StartFire", "Fire", "Fire", "Fire",
	"FireCrackle", "Fire", "Fire", "Fire", "Fire", "Fire",
	"Fire", "Fire", "Fire", "Fire", "Fire", "Fire", "Fire",
	"Fire", "FireCrackle", "Fire", "Fire", "Fire", "Fire",
	"Fire", "Fire", "Fire", "Fire", "Fire", "Fire", "Fire",
	"NULL", "NULL", "NULL", "NULL", "NULL", "Tracer", "Tracer", "NULL",
	"NULL", "NULL", "Look", "Look", "Chase", "Chase", "Chase",
	"Chase", "Chase", "Chase", "Chase", "Chase", "Chase",
	"Chase", "Chase", "Chase", "FaceTarget", "SkelWhoosh",
	"FaceTarget", "SkelFist", "FaceTarget", "FaceTarget",
	"SkelMissile", "FaceTarget", "NULL", "Pain", "NULL", "NULL",
	"Scream", "Fall", "NULL", "NULL", "NULL", "NULL", "NULL", "NULL",
	"NULL", "NULL", "NULL", "NULL", "NULL", "NULL", "NULL", "Look",
	"Look", "Chase", "Chase", "Chase", "Chase", "Chase",
	"Chase", "Chase", "Chase", "Chase", "Chase", "Chase",
	"Chase", "FatRaise", "FatAttack1", "FaceTarget", "FaceTarget",
	"FatAttack2", "FaceTarget", "FaceTarget", "FatAttack3",
	"FaceTarget", "FaceTarget", "NULL", "Pain", "NULL", "Scream",
	"Fall", "NULL", "NULL", "NULL", "NULL", "NULL", "NULL", "BossDeath",
	"NULL", "NULL", "NULL", "NULL", "NULL", "NULL", "NULL", "NULL",
	"Look", "Look", "Chase", "Chase", "Chase", "Chase",
	"Chase", "Chase", "Chase", "Chase", "FaceTarget",
	"CPosAttack", "CPosAttack", "CPosRefire", "NULL", "Pain",
	"NULL", "Scream", "Fall", "NULL", "NULL", "NULL", "NULL", "NULL",
	"XScream", "Fall", "NULL", "NULL", "NULL", "NULL", "NULL", "NULL",
	"NULL", "NULL", "NULL", "NULL", "Look", "Look", "Chase",
	"Chase", "Chase", "Chase", "Chase", "Chase", "Chase",
	"Chase", "FaceTarget", "FaceTarget", "TroopAttack", "NULL",
	"Pain", "NULL", "Scream", "NULL", "Fall", "NULL", "NULL",
	"XScream", "NULL", "Fall", "NULL", "NULL", "NULL", "NULL", "NULL",
	"NULL", "NULL", "NULL", "NULL", "Look", "Look", "Chase",
	"Chase", "Chase", "Chase", "Chase", "Chase", "Chase",
	"Chase", "FaceTarget", "FaceTarget", "SargAttack", "NULL",
	"Pain", "NULL", "Scream", "NULL", "Fall", "NULL", "NULL", "NULL",
	"NULL", "NULL", "NULL", "NULL", "NULL", "Look", "Chase",
	"FaceTarget", "FaceTarget", "HeadAttack", "NULL", "Pain",
	"NULL", "NULL", "Scream", "NULL", "NULL", "Fall", "NULL", "NULL",
	"NULL", "NULL", "NULL", "NULL", "NULL", "NULL", "NULL", "NULL", "NULL",
	"NULL", "Look", "Look", "Chase", "Chase", "Chase", "Chase",
	"Chase", "Chase", "Chase", "Chase", "FaceTarget",
	"FaceTarget", "BruisAttack", "NULL", "Pain", "NULL", "Scream",
	"NULL", "Fall", "NULL", "NULL", "BossDeath", "NULL", "NULL", "NULL",
	"NULL", "NULL", "NULL", "NULL", "Look", "Look", "Chase",
	"Chase", "Chase", "Chase", "Chase", "Chase", "Chase",
	"Chase", "FaceTarget", "FaceTarget", "BruisAttack", "NULL",
	"Pain", "NULL", "Scream", "NULL", "Fall", "NULL", "NULL", "NULL",
	"NULL", "NULL", "NULL", "NULL", "NULL", "NULL", "NULL", "Look",
	"Look", "Chase", "Chase", "FaceTarget", "SkullAttack", "NULL",
	"NULL", "NULL", "Pain", "NULL", "Scream", "NULL", "Fall", "NULL",
	"NULL", "Look", "Look", "Metal", "Chase", "Chase", "Chase",
	"Metal", "Chase", "Chase", "Chase", "Metal", "Chase",
	"Chase", "Chase", "FaceTarget", "SPosAttack", "SPosAttack",
	"SpidRefire", "NULL", "Pain", "Scream", "Fall", "NULL", "NULL",
	"NULL", "NULL", "NULL", "NULL", "NULL", "NULL", "BossDeath", "Look",
	"Look", "NULL", "BabyMetal", "Chase", "Chase", "Chase",
	"Chase", "Chase", "BabyMetal", "Chase", "Chase", "Chase",
	"Chase", "Chase", "FaceTarget", "BspiAttack", "NULL",
	"SpidRefire", "NULL", "Pain", "Scream", "Fall", "NULL", "NULL",
	"NULL", "NULL", "BossDeath", "NULL", "NULL", "NULL", "NULL", "NULL",
	"NULL", "NULL", "NULL", "NULL", "NULL", "NULL", "NULL", "NULL", "NULL",
	"Look", "Look", "Hoof", "Chase", "Chase", "Chase",
	"Chase", "Chase", "Metal", "Chase", "FaceTarget",
	"CyberAttack", "FaceTarget", "CyberAttack", "FaceTarget",
	"CyberAttack", "Pain", "NULL", "Scream", "NULL", "NULL", "NULL",
	"Fall", "NULL", "NULL", "NULL", "BossDeath", "Look", "Chase",
	"Chase", "Chase", "Chase", "Chase", "Chase", "FaceTarget",
	"FaceTarget", "FaceTarget", "PainAttack", "NULL", "Pain",
	"NULL", "Scream", "NULL", "NULL", "PainDie", "NULL", "NULL", "NULL",
	"NULL", "NULL", "NULL", "NULL", "Look", "Look", "Chase",
	"Chase", "Chase", "Chase", "Chase", "Chase", "Chase",
	"Chase", "FaceTarget", "FaceTarget", "CPosAttack",
	"FaceTarget", "CPosAttack", "CPosRefire", "NULL", "Pain",
	"NULL", "Scream", "Fall", "NULL", "NULL", "NULL", "XScream",
	"Fall", "NULL", "NULL", "NULL", "NULL", "NULL", "NULL", "NULL",
	"NULL", "NULL", "NULL", "NULL", "NULL", "NULL", "NULL", "Scream",
	"NULL", "NULL", "NULL", "NULL", "NULL", "NULL", "NULL", "KeenDie",
	"NULL", "NULL", "Pain", "NULL", "BrainPain", "BrainScream",
	"NULL", "NULL", "BrainDie", "Look", "BrainAwake", "BrainSpit",
	"SpawnSound", "SpawnFly", "SpawnFly", "SpawnFly", "Fire",
	"Fire", "Fire", "Fire", "Fire", "Fire", "Fire", "Fire",
	"NULL", "NULL", "BrainExplode", "NULL", "NULL", "NULL", "NULL",
	"NULL", "NULL", "NULL", "Scream", "NULL", "Explode",

	// 156 NULLs so we can get to MBF-specific entries
	"NULL", "NULL", "NULL", "NULL", "NULL", "NULL", "NULL", "NULL",
	"NULL", "NULL", "NULL", "NULL", "NULL", "NULL", "NULL", "NULL",
	"NULL", "NULL", "NULL", "NULL", "NULL", "NULL", "NULL", "NULL",
	"NULL", "NULL", "NULL", "NULL", "NULL", "NULL", "NULL", "NULL",
	"NULL", "NULL", "NULL", "NULL", "NULL", "NULL", "NULL", "NULL",
	"NULL", "NULL", "NULL", "NULL", "NULL", "NULL", "NULL", "NULL",
	"NULL", "NULL", "NULL", "NULL", "NULL", "NULL", "NULL", "NULL",
	"NULL", "NULL", "NULL", "NULL", "NULL", "NULL", "NULL", "NULL",
	"NULL", "NULL", "NULL", "NULL", "NULL", "NULL", "NULL", "NULL",
	"NULL", "NULL", "NULL", "NULL", "NULL", "NULL", "NULL", "NULL",
	"NULL", "NULL", "NULL", "NULL", "NULL", "NULL", "NULL", "NULL",
	"NULL", "NULL", "NULL", "NULL", "NULL", "NULL", "NULL", "NULL",
	"NULL", "NULL", "NULL", "NULL", "NULL", "NULL", "NULL", "NULL",
	"NULL", "NULL", "NULL", "NULL", "NULL", "NULL", "NULL", "NULL",
	"NULL", "NULL", "NULL", "NULL", "NULL", "NULL", "NULL", "NULL",
	"NULL", "NULL", "NULL", "NULL", "NULL", "NULL", "NULL", "NULL",
	"NULL", "NULL", "NULL", "NULL", "NULL", "NULL", "NULL", "NULL",
	"NULL", "NULL", "NULL", "NULL", "NULL", "NULL", "NULL", "NULL",
	"NULL", "NULL", "NULL", "NULL", "NULL", "NULL", "NULL", "NULL",
	"NULL", "NULL", "NULL", "NULL",

	// Now, these are all new to MBF.
	"Die", "Scream", "Detonate", "NULL", "Look", "Look",
	"Chase", "Chase", "Chase", "Chase", "Chase", "Chase", "Chase", "Chase",
	"FaceTarget", "FaceTarget", "SargAttack", "NULL", "Pain", "NULL", "Scream",
	"NULL", "Fall", "NULL", "NULL", "NULL", "NULL", "NULL", "NULL", "NULL", "NULL", "BFGsound",
	"FireOldBFG", "FireOldBFG", "FireOldBFG", "FireOldBFG", "FireOldBFG", "FireOldBFG", "FireOldBFG", "FireOldBFG",
	"FireOldBFG", "FireOldBFG", "FireOldBFG", "FireOldBFG", "FireOldBFG", "FireOldBFG", "FireOldBFG", "FireOldBFG",
	"FireOldBFG", "FireOldBFG", "FireOldBFG", "FireOldBFG", "FireOldBFG", "FireOldBFG", "FireOldBFG", "FireOldBFG",
	"FireOldBFG", "FireOldBFG", "FireOldBFG", "FireOldBFG", "FireOldBFG", "FireOldBFG", "FireOldBFG", "FireOldBFG",
	"FireOldBFG", "FireOldBFG", "FireOldBFG", "FireOldBFG", "FireOldBFG", "FireOldBFG", "FireOldBFG", "FireOldBFG",
	"Light0", "ReFire", "NULL", "NULL", "NULL", "NULL", "NULL", "NULL", "NULL",
	"NULL", "NULL", "NULL", "NULL", "NULL", "NULL", "NULL",
	"Look", "Chase", "Chase", "Chase", "Chase", "FaceTarget",
	"BetaSkullAttack", "NULL", "NULL", "Pain", "NULL",
	"NULL", "NULL", "NULL", "NULL", "Scream", "NULL", "Fall", "Stop",
	"Mushroom",
};

//==========================================================================
//
//  FUNCTIONAL CONSTANTS
//
//==========================================================================

//Contains all the parsing done on a Thing
const std::vector<stringAction2> thingActions
{
/*-------------------------------------Thing Properties-------------------------------------------------------*/
    {"ID #",   [](std::string value, base::baseArray &DoomBase, int number)   {
        if( isNumber(value) )
            DoomBase.thingArray[number].setID( stoi(value) );
        else
            std::cerr << "Error on line " << lineNumber << ": numerical value expected on left of = sign" << std::endl;
    } },

    {"Hit points",   [](std::string value, base::baseArray &DoomBase, int number)   {
        if( isNumber(value) )
            DoomBase.thingArray[number].setHealth( stoi(value) );
        else
            std::cerr << "Error on line " << lineNumber << ": numerical value expected on left of = sign" << std::endl;
    } },

    {"Speed",   [](std::string value, base::baseArray &DoomBase, int number)   {
        if( isNumber(value) )
        {
            if( stoi(value) >= THINGSCALE )
            {
                DoomBase.thingArray[number].setSpeed( stoi(value)/THINGSCALE );
            }
            else
                DoomBase.thingArray[number].setSpeed( stoi(value) );
        }
        else
            std::cerr << "Error on line " << lineNumber << ": numerical value expected on left of = sign" << std::endl;
    } },

    {"Width",   [](std::string value, base::baseArray &DoomBase, int number)   {
        if( isNumber(value) )
            DoomBase.thingArray[number].setRadius( stoi(value)/THINGSCALE );
        else
            std::cerr << "Error on line " << lineNumber << ": numerical value expected on left of = sign" << std::endl;
    } },

    {"Height",   [](std::string value, base::baseArray &DoomBase, int number)   {
        if( isNumber(value) )
            DoomBase.thingArray[number].setHeight( stoi(value)/THINGSCALE );
        else
            std::cerr << "Error on line " << lineNumber << ": numerical value expected on left of = sign" << std::endl;
    } },

    {"Missile damage",   [](std::string value, base::baseArray &DoomBase, int number)   {
        if( isNumber(value) )
            DoomBase.thingArray[number].setDamage( stoi(value) );
        else
            std::cerr << "Error on line " << lineNumber << ": numerical value expected on left of = sign" << std::endl;
    } },

    {"Reaction time",   [](std::string value, base::baseArray &DoomBase, int number)   {
        if( isNumber(value) )
            DoomBase.thingArray[number].setReactionTime( stoi(value) );
        else
            std::cerr << "Error on line " << lineNumber << ": numerical value expected on left of = sign" << std::endl;
    } },

    {"Pain chance",   [](std::string value, base::baseArray &DoomBase, int number)   {
        if( isNumber(value) )
            DoomBase.thingArray[number].setPainChance( stoi(value) );
        else
            std::cerr << "Error on line " << lineNumber << ": numerical value expected on left of = sign" << std::endl;
    } },

    {"Mass",   [](std::string value, base::baseArray &DoomBase, int number)   {
        if( isNumber(value) )
            DoomBase.thingArray[number].setMass( stoi(value) );
        else
            std::cerr << "Error on line " << lineNumber << ": numerical value expected on left of = sign" << std::endl;
    } },


/*-------------------------------------Thing States-----------------------------------------------------------*/
    {"Initial frame",   [](std::string value, base::baseArray &DoomBase, int number)   {
        if( isNumber(value) )
            DoomBase.thingArray[number].setSpawnState( stoi(value) );
        else
            std::cerr << "Error on line " << lineNumber << ": numerical value expected on left of = sign" << std::endl;
    } },

    {"First moving frame",   [](std::string value, base::baseArray &DoomBase, int number)   {
        if( isNumber(value) )
            DoomBase.thingArray[number].setWalkState( stoi(value) );
        else
            std::cerr << "Error on line " << lineNumber << ": numerical value expected on left of = sign" << std::endl;
    } },

    {"Injury frame",   [](std::string value, base::baseArray &DoomBase, int number)   {
        if( isNumber(value) )
            DoomBase.thingArray[number].setPainState( stoi(value) );
        else
            std::cerr << "Error on line " << lineNumber << ": numerical value expected on left of = sign" << std::endl;
    } },

    {"Close attack frame",   [](std::string value, base::baseArray &DoomBase, int number)   {
        if( isNumber(value) )
            DoomBase.thingArray[number].setMeleeState( stoi(value) );
        else
            std::cerr << "Error on line " << lineNumber << ": numerical value expected on left of = sign" << std::endl;
    } },

    {"Far attack frame",   [](std::string value, base::baseArray &DoomBase, int number)   {
        if( isNumber(value) )
            DoomBase.thingArray[number].setAttackState( stoi(value) );
        else
            std::cerr << "Error on line " << lineNumber << ": numerical value expected on left of = sign" << std::endl;
    } },

    {"Death frame",   [](std::string value, base::baseArray &DoomBase, int number)   {
        if( isNumber(value) )
            DoomBase.thingArray[number].setDeathState( stoi(value) );
        else
            std::cerr << "Error on line " << lineNumber << ": numerical value expected on left of = sign" << std::endl;
    } },

    {"Exploding frame",   [](std::string value, base::baseArray &DoomBase, int number)   {
        if( isNumber(value) )
            DoomBase.thingArray[number].setExplodeState( stoi(value) );
        else
            std::cerr << "Error on line " << lineNumber << ": numerical value expected on left of = sign" << std::endl;
    } },

    {"Respawn frame",   [](std::string value, base::baseArray &DoomBase, int number)   {
        if( isNumber(value) )
            DoomBase.thingArray[number].setRaiseState( stoi(value) );
        else
            std::cerr << "Error on line " << lineNumber << ": numerical value expected on left of = sign" << std::endl;
    } },


/*-------------------------------------Thing Sounds-----------------------------------------------------------*/
    {"Alert sound",   [](std::string value, base::baseArray &DoomBase, int number)   {
        if( isNumber(value) )
            DoomBase.thingArray[number].setAlertSound( stoi(value) );
        else
            std::cerr << "Error on line " << lineNumber << ": numerical value expected on left of = sign" << std::endl;
    } },

    {"Attack sound",   [](std::string value, base::baseArray &DoomBase, int number)   {
        if( isNumber(value) )
            DoomBase.thingArray[number].setAttackSound( stoi(value) );
        else
            std::cerr << "Error on line " << lineNumber << ": numerical value expected on left of = sign" << std::endl;
    } },

    {"Pain sound",   [](std::string value, base::baseArray &DoomBase, int number)   {
        if( isNumber(value) )
            DoomBase.thingArray[number].setPainSound( stoi(value) );
        else
            std::cerr << "Error on line " << lineNumber << ": numerical value expected on left of = sign" << std::endl;
    } },

    {"Death sound",   [](std::string value, base::baseArray &DoomBase, int number)   {
        if( isNumber(value) )
            DoomBase.thingArray[number].setDeathSound( stoi(value) );
        else
            std::cerr << "Error on line " << lineNumber << ": numerical value expected on left of = sign" << std::endl;
    } },

    {"Action sound",   [](std::string value, base::baseArray &DoomBase, int number)   {
        if( isNumber(value) )
            DoomBase.thingArray[number].setActiveSound( stoi(value) );
        else
            std::cerr << "Error on line " << lineNumber << ": numerical value expected on left of = sign" << std::endl;
    } },


/*-------------------------------------Thing Flags------------------------------------------------------------*/
    {"Bits",   [](std::string value, base::baseArray &DoomBase, int number)   {
        dehacked::dehackedReadFlags( value, DoomBase, number );
    } },

};

//Contains all the parsing done on a State
const std::vector<stringAction2> stateActions
{
    {"Sprite number",   [](std::string value, base::baseArray &DoomBase, int number)   {
        if( isNumber(value) )
            DoomBase.stateArray[number].setSprite( stoi(value) );
        else
            std::cerr << "Error on line " << lineNumber << ": numerical value expected on left of = sign" << std::endl;
    } },

    {"Sprite subnumber",   [](std::string value, base::baseArray &DoomBase, int number)   {
        if( isNumber(value) )
            DoomBase.stateArray[number].setSpriteSub( stoi(value) );
        else
            std::cerr << "Error on line " << lineNumber << ": numerical value expected on left of = sign" << std::endl;
    } },

    {"Next frame",   [](std::string value, base::baseArray &DoomBase, int number)   {
        if( isNumber(value) )
            DoomBase.stateArray[number].setNextState( stoi(value) );
        else
            std::cerr << "Error on line " << lineNumber << ": numerical value expected on left of = sign" << std::endl;
    } },

    {"Duration",   [](std::string value, base::baseArray &DoomBase, int number)   {
        if( isNumber(value) )
            DoomBase.stateArray[number].setDuration( stoi(value) );
        else
            std::cerr << "Error on line " << lineNumber << ": numerical value expected on left of = sign" << std::endl;
    } },

    {"Unknown 1",   [](std::string value, base::baseArray &DoomBase, int number)   {
        if( isNumber(value) )
            DoomBase.stateArray[number].setParam1( stoi(value) );
        else
            std::cerr << "Error on line " << lineNumber << ": numerical value expected on left of = sign" << std::endl;
    } },

    {"Unknown 2",   [](std::string value, base::baseArray &DoomBase, int number)   {
        if( isNumber(value) )
            DoomBase.stateArray[number].setParam2( stoi(value) );
        else
            std::cerr << "Error on line " << lineNumber << ": numerical value expected on left of = sign" << std::endl;
    } },
};

//Contains all the parsing done on a Doom-style codepointer
const std::vector<stringAction2> codepDoomActions
{
    {"Codep Frame",   [](std::string value, base::baseArray &DoomBase, int number)   {
        if( isNumber(value) )
            DoomBase.stateArray[ CODEPLIST[number] ].setAction( ACTIONLIST[stoi(value)] );
        else
            std::cerr << "Error on line " << lineNumber << ": numerical value expected on left of = sign" << std::endl;
    } },
};

//Contains all the parsing done on a Weapon
const std::vector<stringAction2> weaponActions
{
    {"Select frame",   [](std::string value, base::baseArray &DoomBase, int number)   {
        if( isNumber(value) )
            DoomBase.weaponArray[number].setLower( stoi(value) );
        else
            std::cerr << "Error on line " << lineNumber << ": numerical value expected on left of = sign" << std::endl;
    } },

    {"Deselect frame",   [](std::string value, base::baseArray &DoomBase, int number)   {
        if( isNumber(value) )
            DoomBase.weaponArray[number].setRaise( stoi(value) );
        else
            std::cerr << "Error on line " << lineNumber << ": numerical value expected on left of = sign" << std::endl;
    } },

    {"Bobbing frame",   [](std::string value, base::baseArray &DoomBase, int number)   {
        if( isNumber(value) )
            DoomBase.weaponArray[number].setBob( stoi(value) );
        else
            std::cerr << "Error on line " << lineNumber << ": numerical value expected on left of = sign" << std::endl;
    } },

    {"Shooting frame",   [](std::string value, base::baseArray &DoomBase, int number)   {
        if( isNumber(value) )
            DoomBase.weaponArray[number].setFire( stoi(value) );
        else
            std::cerr << "Error on line " << lineNumber << ": numerical value expected on left of = sign" << std::endl;
    } },

    {"Firing frame",   [](std::string value, base::baseArray &DoomBase, int number)   {
        if( isNumber(value) )
            DoomBase.weaponArray[number].setFlash( stoi(value) );
        else
            std::cerr << "Error on line " << lineNumber << ": numerical value expected on left of = sign" << std::endl;
    } },

    {"Ammo type",   [](std::string value, base::baseArray &DoomBase, int number)   {
        if( isNumber(value) )
            DoomBase.weaponArray[number].setAmmoType( stoi(value) );
        else
            std::cerr << "Error on line " << lineNumber << ": numerical value expected on left of = sign" << std::endl;
    } },
};



//This constant contains the strings and their associated actions
const std::vector<stringAction> parseActions
{
    {"Thing",      [](std::ifstream &fileStream, std::string number, base::baseArray &DoomBase)   { dehacked::dehackedReadDoomSet(fileStream,number,DoomBase,thingActions)      ;} },
    {"Frame",      [](std::ifstream &fileStream, std::string number, base::baseArray &DoomBase)   { dehacked::dehackedReadDoomSet(fileStream,number,DoomBase,stateActions)      ;} },
    {"Pointer",    [](std::ifstream &fileStream, std::string number, base::baseArray &DoomBase)   { dehacked::dehackedReadDoomSet(fileStream,number,DoomBase,codepDoomActions)  ;} },
    {"Weapon",     [](std::ifstream &fileStream, std::string number, base::baseArray &DoomBase)   { dehacked::dehackedReadDoomSet(fileStream,number,DoomBase,weaponActions)     ;} },
    {"[CODEPTR]",  [](std::ifstream &fileStream, std::string number, base::baseArray &DoomBase)   { dehacked::dehackedReadBoomCodep(fileStream,DoomBase) ;} },

    //For now, skip these
    {"Sound",       [](std::ifstream &fileStream, std::string number, base::baseArray &DoomBase)   { dehacked::dehackedSkip(fileStream) ;} },
    {"Text",        [](std::ifstream &fileStream, std::string number, base::baseArray &DoomBase)   { dehacked::dehackedSkip(fileStream) ;} },
    {"Ammo",        [](std::ifstream &fileStream, std::string number, base::baseArray &DoomBase)   { dehacked::dehackedSkip(fileStream) ;} },
    {"Cheat",       [](std::ifstream &fileStream, std::string number, base::baseArray &DoomBase)   { dehacked::dehackedSkip(fileStream) ;} },
    {"Misc",        [](std::ifstream &fileStream, std::string number, base::baseArray &DoomBase)   { dehacked::dehackedSkip(fileStream) ;} },
    {"[STRINGS]",   [](std::ifstream &fileStream, std::string number, base::baseArray &DoomBase)   { dehacked::dehackedSkip(fileStream) ;} },
    {"[PARS]",      [](std::ifstream &fileStream, std::string number, base::baseArray &DoomBase)   { dehacked::dehackedSkip(fileStream) ;} },
};




//==========================================================================
//
//  Functions
//
//==========================================================================

//  dehackedReadSet
    /*
     * This file reads a set of data in DOOM format (i.e stuff below THING 12)
     *
     * @fileStream: the filestream to the DEHACKED file
     * @setValue: the value to modify (i.e. the above is 12) as a string
     * @DoomBase: The base thing the DEHACKED file is changing
     * @strAct: This is the vector of actions to perform when a specific string is encountered
     *
     * On exit, the DoomBase array will be modified based on the DEHACKED file
     */
void dehacked::dehackedReadDoomSet( std::ifstream &fileStream, std::string setValue, base::baseArray &DoomBase, std::vector<stringAction2> strAct )
{
    bool exitFlag = 0;
    std::string currentLine;
    std::streampos oldpos;

    std::string frontLine;
    std::string backLine;

    while( !exitFlag && !fileStream.eof() )
    {
        oldpos = fileStream.tellg();
        getline(fileStream, currentLine);
        lineNumber++;
        bool parseMatch=false;

        //If line is empty or comment, skip it
        std::stringstream dataStream(currentLine);
        std::string firstWord;
        dataStream >> firstWord;
        if( icompare(currentLine,"") || firstWord[0] == '#' )
        {
            continue;
        }

        //break expression of form "frontLine=backLine"
        size_t middle = currentLine.find('=');
        if( middle != std::string::npos && middle != 0)
        {
            frontLine = currentLine.substr(0,middle);
            backLine  = currentLine.substr(middle+1);
        }
        else
        {
            exitFlag = true;
            continue;
        }

        //If backLine is not a number, return an error for that line
        if( !isNumber(setValue) )
        {
            std::cerr << "Error on line " << lineNumber << ": numerical value expected on left of = sign" << std::endl;
            continue;
        }

        for_each( strAct.begin(), strAct.end(), [&](stringAction2 Action)
        {
            if( icompare(frontLine,Action.str) && !parseMatch )
            {
                //std::cout << "Line " << lineNumber << ": " << Action.str << " set to " << backLine << std::endl;
                Action.foo(backLine, DoomBase, stoi(setValue));
                parseMatch=true;
            }
        });
        if(!parseMatch)
        {
            std::cerr << "Error on line " << lineNumber << ": cannot interpret meaning of \"" << removeBreaks(currentLine) << "\" in this context" << std::endl;
        }
    }

    //If function finished before end of file (by finding something like another THING),
    //go back one line (otherwise it will be skipped by the parser)
    if( !fileStream.eof() )
    {
        fileStream.seekg(oldpos);
        lineNumber--;
    }
}


//  dehackedReadFlags
    /*
     * This file parses flags (i.e. Bits = ....). This function takes both Doom
     * and Boom style flag-declaration
     *
     * @value: the string on the right side of "bits = value"
     * @DoomBase: the base thing the DEHACKED file is changing
     * @number: the number of the thing being modified
     *
     * On exit, the DoomBase array will be modified based on the DEHACKED file
     */
void dehacked::dehackedReadFlags( std::string value, base::baseArray &DoomBase, int number )
{
   uint32_t flagBits=0;

   //Bits are numeric
   if( isNumber(value) )
   {
        flagBits = stoi(value);
   }
   //Bits are "SHOOTABLE+TRANSLUCENT+..."
   else
   {
        std::string flagName;
        size_t index1=0;
        size_t index2=value.find_first_not_of("ABCDEFGHIJKLMNOPQRSTURVWXYZabcdefghijklmnopqrsturvwxyz1234567890 ");
        bool flagMatch;

        while( index2 != std::string::npos )
        {
            flagMatch=false;
            flagName = value.substr(index1,index2-index1);
            for(size_t i=0; i<FLAGVALUES.size(); i++)
            {
                if(icompare( flagName,FLAGVALUES[i].str ))
                {
                    flagBits |= FLAGVALUES[i].value;
                    flagMatch=true;
                    break;
                }
            }
            if(!flagMatch)
            {
                std::cerr << "Error on line " << lineNumber << ": " << flagName << " is not a recognized flag" << std::endl;
            }
            index1=index2+1;
            index2=value.find_first_not_of("ABCDEFGHIJKLMNOPQRSTURVWXYZabcdefghijklmnopqrsturvwxyz1234567890 ",index2+1);
        }
   }

   DoomBase.thingArray[number].setFlags(flagBits);
}


//  dehackedReadBoomCodep
    /*
     * This file parses Boom-style codepointers (with a "[CODEPTRS]" header)
     *
     * @fileStream: the filestream to the DEHACKED file
     * @DoomBase: the base thing the DEHACKED file is changing
     *
     * On exit, the DoomBase array will be modified based on the DEHACKED file
     */
void dehacked::dehackedReadBoomCodep( std::ifstream &fileStream, base::baseArray &DoomBase )
{
    bool exitFlag = 0;
    std::string currentLine;
    std::streampos oldpos;

    std::string frontLine;
    std::string backLine;

    while( !exitFlag && !fileStream.eof() )
    {
        oldpos = fileStream.tellg();
        getline(fileStream, currentLine);
        lineNumber++;

        //If line is empty or comment, skip it
        std::stringstream dataStream(currentLine);
        std::string firstWord;
        std::string secondWord;
        dataStream >> firstWord;
        if( icompare(currentLine,"") || firstWord[0] == '#' )
        {
            continue;
        }

        //break expression of form "frontLine=backLine"
        size_t middle = currentLine.find('=');
        if( middle != std::string::npos && middle != 0)
        {
            frontLine = currentLine.substr(0,middle);
            backLine  = currentLine.substr(middle+1);
        }
        else
        {
            exitFlag = true;
            continue;
        }

        //Not prefixed with "FRAME ###"
        dataStream.str(currentLine);
        dataStream >> firstWord >> secondWord;
        if( !icompare(firstWord,"FRAME") || !isNumber(secondWord) )
        {
            std::cerr << "Error on line " << lineNumber << ": expected \"FRAME ##\", received \"" << removeBreaks(frontLine) << "\" instead" << std::endl;
            continue;
        }

        DoomBase.stateArray[ stoi(secondWord) ].setAction( removeSpace(backLine) );
    }

    //If function finished before end of file (by finding something like another THING),
    //go back one line (otherwise it will be skipped by the parser)
    if( !fileStream.eof() )
    {
        fileStream.seekg(oldpos);
        lineNumber--;
    }
}


//  dehackedSkip
    /*
     * This file skips ahead until a recognized header is found
     *
     * @fileStream: the filestream to the DEHACKED file
     *
     * On exit, the filestream will be at the next recognized header or the end of file
     */
void dehacked::dehackedSkip( std::ifstream &fileStream )
{
    std::string currentLine;
    std::streampos oldpos;
    bool parseMatch=false;

    while( !fileStream.eof() )
    {
        oldpos = fileStream.tellg();
        getline(fileStream, currentLine);
        lineNumber++;

        std::stringstream dataStream(currentLine);
        std::string firstWord;
        dataStream >> firstWord;

        for_each( parseActions.begin(), parseActions.end(), [&](stringAction Action)
        {
            if( icompare(firstWord,Action.str) && !parseMatch )
            {
                parseMatch=true;
            }
        });

        if(parseMatch)
            break;
    }

    //If function finished before end of file (by finding something like another THING),
    //go back one line (otherwise it will be skipped by the parser)
    if( !fileStream.eof() )
    {
        fileStream.seekg(oldpos);
        lineNumber--;
    }
}


#endif //DEHACKEDDATA_H
