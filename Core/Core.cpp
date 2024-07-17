#define _WIN32_DCOM
#include <Windows.h>
#include <process.h>
#include <wininet.h>
#include <time.h>
#include <random>
#include <math.h>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <iostream>
#include <fstream>
#include <sstream>
#include <strstream>
#include <sql.h>
#include <sqltypes.h>
#include <sqlext.h>
#include <fcntl.h>
#include <io.h>
#include <list>
#include <vector>
#include <algorithm>
#include "MD5.h"
#include "base64.h"
#include "Sha256.h"
#include <iterator>
#include <iomanip>
#include <comdef.h>
#include <wbemidl.h>
#include "Functions.h"
#include "Lock.h"
#include "MyIterator.h"
#include "Pointer.h"
#include "CriticalLock.h"
#include "MutexMap.h"
#include "TargetFind.h"
#include "Buffer.h"
//#include "sqlite3.h"
#include "ConcurrentMap.h"
#include "ConcurrentSet.h"
#include "ConcurrentVector.h"
#include "SystemRegistration.h"
#include "RegistrationMap.h"
#include <tlhelp32.h>
#include <dbghelp.h> // Include this header for symbols-related functions
#include "Variables.h"

#pragma comment(lib, "Dbghelp.lib")
#pragma pack(1)
HINSTANCE hL = 0;

CHAR ClassName[104]; // idb
CHAR WindowName[100]; // idb
HINSTANCE hInstance; // idb
HWND hWnd; // idb

FARPROC p[806] = {0};
#pragma warning(disable: 4018)
#pragma warning(disable: 4129)
#pragma warning (disable : 4244)
#pragma warning (disable : 4305)
#pragma warning (disable : 4309)
#pragma warning (disable : 4996)
char key = '255';
char newkey = 'Hell';

void Console()
{
	int hCrtIn, hCrtOut;
	FILE *conIn, *conOut;
	AllocConsole();
	hCrtIn = _open_osfhandle ((intptr_t) GetStdHandle(STD_INPUT_HANDLE), _O_TEXT);
	hCrtOut = _open_osfhandle ((intptr_t) GetStdHandle(STD_OUTPUT_HANDLE), _O_TEXT);
	conIn = _fdopen( hCrtIn, "r" );
	conOut = _fdopen( hCrtOut, "w" );
	*stdin = *conIn;
	*stdout = *conOut; 
	HWND hwnd = ::GetConsoleWindow();
	if (hwnd != NULL)
	{
		HMENU hMenu = ::GetSystemMenu(hwnd, FALSE);
		if (hMenu != NULL) DeleteMenu(hMenu, SC_CLOSE, MF_BYCOMMAND);
	}
	SetConsoleTitleA("ScaniaDevelopments");
}

std::string encryptDecrypt(std::string toEncrypt)
{
	std::string output = toEncrypt;

	for (int i = 0; i < toEncrypt.size(); i++)
		output[i] = toEncrypt[i] ^ key;
	
	return output;
}

std::string newencryptDecrypt(std::string toEncrypt)
{
	std::string output = toEncrypt;

	for (int i = 0; i < toEncrypt.size(); i++)
		output[i] = toEncrypt[i] ^ newkey;

	return output;
}

long uniqueKey(int X, int Y) {
	return (((X + Y)*(X + Y + 1)) / 2) + Y;
}

std::string random_string(size_t length)
{
	srand(time(0));
	auto randchar = []() -> char
	{
		const char charset[] =
			"0123456789"
			"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
			"abcdefghijklmnopqrstuvwxyz";
		const size_t max_index = (sizeof(charset) - 1);
		return charset[rand() % max_index];
	};
	std::string str(length, 0);
	std::generate_n(str.begin(), length, randchar);
	return str;
}
//// Define a structure to represent a set of coordinates
//struct TeleCoordinates {
//	uint32_t x;
//	uint32_t y;
//	uint32_t z;
//	uint32_t comment;
//};

/*
// Function to create the Tele_Scrolls vector with predefined coordinates
std::vector<TeleCoordinates> CreateTeleScrolls() {
	std::vector<TeleCoordinates> Tele_Scrolls;

	// Define the coordinates and comments in a readable way
	struct CoordInfo {
		uint32_t x;
		uint32_t y;
		uint32_t z;
		uint32_t comment;
	};

	CoordInfo coordInfo[] = {
		{ 0, 257798, 259386, 16080 },  // 0 Naro
		{ 0, 265022, 262538, 16190 },  // 1 Cargo
		{ 0, 266040, 284976, 22650 },  // 2 Mine
		{ 0, 255825, 288802, 27050 },  // 3 Pub
		{ 0, 267618, 242946, 19630 },  // 4 Fort
		{ 0, 232954, 294672, 45300 },  // 5 Cop
		{ 0, 123456, 123456, 12346 },  // 6 Custom coordinates
		// Add new coordinates here
	};

	// Populate the Tele_Scrolls vector
	for (int i = 0; i < sizeof(coordInfo) / sizeof(coordInfo[0]); ++i) {
		TeleCoordinates coord;
		coord.x = coordInfo[i].x;
		coord.y = coordInfo[i].y;
		coord.z = coordInfo[i].z;
		coord.comment = coordInfo[i].comment;
		Tele_Scrolls.push_back(coord);
	}

	return Tele_Scrolls;
}
*/
//Teleport Scrolls
char* stristr(const char* str1, const char* str2)
{
	const char* p1 = str1;
	const char* p2 = str2;
	const char* r = *p2 == 0 ? str1 : 0;

	if (str1[0] == ';')
		return 0;

	while (*p1 != 0 && *p2 != 0)
	{
		if (tolower((unsigned char)*p1) == tolower((unsigned char)*p2))
		{
			if (r == 0)
			{
				r = p1;
			}

			p2++;
		}
		else
		{
			p2 = str2;
			if (r != 0)
			{
				p1 = r + 1;
			}

			if (tolower((unsigned char)*p1) == tolower((unsigned char)*p2))
			{
				r = p1;
				p2++;
			}
			else
			{
				r = 0;
			}
		}

		p1++;
	}

	return *p2 == 0 ? (char*)r : 0;
}

int roundNo(double num)
{
	return num < 0 ? num - 0.5 : num + 0.5;
}
enum ItemType {
	CUSTOM_WEAPON = 1,
	COSTUME_SUIT = 2,
	RIDING_ARMOR = 3,
	RIDING_PET = 4,
	PREMIUM_PET = 5,
	SOUL_POCKET = 6,
	NORMAL_PET = 7,
	MONSTER_PET = 8,
	NECKLACE2 = 9,
	COSTUMEEFFECT = 10,
	Wings = 11,
};


//#define ConsoleColAdr *(DWORD*)0x4D62A8
//
//void ConsoleWrite(COLORREF Color, const char *Text, ...)
//{
//	ConsoleColAdr = Color;
//	va_list va;
//	va_start(va, Text);
//	//std::string _Tag = ("Quickly ~ ");
//	std::string _Text(Text);
//	std::string _RetText = (/*_Tag +*/ _Text);
//	CLog::AddV(2, _RetText.c_str(), va);
//	va_end(va);
//	ConsoleColAdr = 0x0000FF;
//}

enum NoticeColor
{
	NOTICECOLOR_BLUE		= 0,
	NOTICECOLOR_RED			= 1,
	NOTICECOLOR_ORANGE		= 2,
	NOTICECOLOR_REDCENTER	= 3,
	NOTICECOLOR_WHITE		= 4,
	NOTICECOLOR_REDLONG		= 5,
	NOTICECOLOR_BLUECENTER	= 6,
	NOTICECOLOR_YELLOW		= 7,
	NOTICECOLOR_PINK		= 8,
	NOTICECOLOR_ORANGELONG	= 9,
};

enum C2S {
	C2S_ExecuteSkill = 16,
	C2S_PrepareSkill = 43,
	C2S_Shop = 67,
	C2S_UseItem = 33,
	C2S_MOVE = 20,
	C2S_STOP = 21,
	C2S_SendMsg = 17,
	C2S_AddFriend = 64,
	C2S_SendMail = 92,

};

std::string GetPacketName(int packetID) {
	switch (packetID) {
	case C2S_ExecuteSkill:
		return "C2S_ExecuteSkill";
	case C2S_Shop:
		return "C2S_Shop";
	case C2S_UseItem:
		return "C2S_UseItem";
	case C2S_MOVE:
		return "C2S_MOVE";
	case C2S_STOP:
		return "C2S_STOP";
	case C2S_PrepareSkill:
		return "C2S_PrepareSkill";
	case C2S_SendMsg:
		return "C2S_SendMsg";
	case C2S_SendMail:
		return "C2S_SendMail";
	case C2S_AddFriend:
		return "C2S_AddFriend";
	default:
		return Int2String(packetID);
	}
}
namespace BuffNames {
	enum
	{
		CPRed = 180,
		CPBlue = 179,
		BuffTime = 648000,
		ArmorWears = 1400,
		SuitsUsing = 1401,
		RidingUsing = 1402,
		Essence1 = 1403,
		Essence2 = 1404,
		Essence3 = 1405,
		Essence4 = 1406,
		Essence5 = 1407,
		MirrorBuff = 1408,
		TrigramGrade = 1409,
		TrigramHP = 1410,
		TrigramMP = 1411,
		TrigramAtk = 1412,
		TrigramStr = 1413,
		TrigramAgi = 1414,
		TrigramInt = 1415,
		TrigramWis = 1416,
		TrigramHth = 1417,
		Taegeuk = 1418,
		NormalHits = 1419,
		SkillsEdit = 1420,
		MageMICheck = 1421,
		CheckBlob = 1422,
		PetOwner = 1423,
		PetBuff = 1424,
		PetIID = 1425,
		MonsterDisappear = 1426,
		SummonAI = 1427,
		ShinyTarget = 1428,
		ShinyDelay = 1429,
		SpamSkillTime = 1430,
		ContinueSkillPlayerX = 1431,
		ContinueSkillPlayerY = 1432,
		ContinueSkillPlayerTarget = 1433,
		ContinueSkillPlayerSkillGrade = 1434,
		ContinueSkillPlayerSkillID = 1435,
		ContinueSkillPlayerSkillDelay = 1436,
		ContinueSkillPlayerSkillCount = 1437,
		FarContinueSkillPlayerTarget = 1438,
		FarContinueSkillPlayerSkillGrade = 1439,
		FarContinueSkillPlayerSkillID = 1440,
		FarContinueSkillPlayerSkillDelay = 1441,
		FarContinueSkillPlayerSkillCount = 1442,
		FarContinueSkillPlayerDamage = 1443,
		RuptureContinueSkillPlayerTarget = 1444,
		RuptureContinueSkillPlayerSkillGrade = 1445,
		RuptureContinueSkillPlayerSkillID = 1446,
		RuptureContinueSkillPlayerSkillDelay = 1447,
		RuptureContinueSkillPlayerSkillCount = 1448,
		RuptureContinueSkillPlayerDamage = 1449,
		BOFChest = 1450,
		BOFGloves = 1451,
		BOFBoots = 1452,
		BOFHelmet = 1453,
		BOFShort = 1454,
		BOFFullSet = 1455,
		BOFHalfSet = 1456,
		BetOpponent = 1457,
		BetType = 1458,
		BetAmount = 1459,
		EmokTime = 1460,
		EmokDay = 1461,
		HPx = 1462,
		HKx = 1463,
		HDx = 1464,
		DKPTx = 1465,
		DKPWx = 1466,
		PLTx = 1467,
		PLWx = 1468,
		SVTx = 1469,
		SVWx = 1470,
		RPx = 1471,
		PacketHack = 1472,
		SpamSkillID = 1473,
		SpeedCheckX = 1474,
		SpeedCheckY = 1475,
		SOFSType = 1476,
		SOFSTime = 1477,
		CDType = 1478,
		CDTime = 1479,
		CODelay = 1480,
		AFKTime = 1481,
		MinAtk = 1482,
		MaxAtk = 1483,
		OTP = 1484,
		EVA = 1485,
		DeathBlow = 1486,
		CheckIceArrow = 1487,
		Riding1 = 1488,
		Riding2 = 1489,
		Riding3 = 1490,
		Riding4 = 1491,
		Riding5 = 1492,
		Riding6 = 1493,
		Riding7 = 1494,
		Riding8 = 1495,
		Riding9 = 1496,
		SkillHit = 1497,
		BossHunt = 1498,
		PetOwner2 = 1499,
		PetBuff2 = 1500,
		PetIID2 = 1501,
		PetOwner3 = 1502,
		PetBuff3 = 1503,
		PetIID3 = 1504,
		PetPick = 1505,
		SoulPocketIID = 1506,
		SoulPocketAmount = 1507,
		SpawnedMobQuest = 1508,
		custWeap = 1509,
		fish = 1510,
		expstone = 1511,
		RewardClaim = 1512,
		WeaponWear = 1513,
		NamePad = 1514,
		TrainingFree = 1515,
		TrainingTime = 1516,
		TrainingHits = 1517,
		Channel = 1518,
		Satiety = 1519,
		RidingIID = 1520,
		SoulPIndex = 1521,
		HaninStats1 = 1522,
		HaninStats2 = 1523,
		HaninStats3 = 1524,
		HaninStats4 = 1525,
		HaninStats5 = 1526,
		Inventory = 1527,
		Extension1 = 1528,
		Extension2 = 1529,
		Extension3 = 1530,
		MacroCheck = 1531,
		CallOfPhy = 1532,
		MobPet = 1533,
		TargetAttack = 1534,
		PTVsPTRed = 1535,
		PTVsPTBlue = 1536,
		NPCSummon = 1537,
		RevivalCheck = 1538,
		Fighter = 1539,
		SkinView = 1540,
		InitItemReload = 1542,
		SendMailResult = 1543,
		UnGap = 1544,
		MacroMap = 1545,
		EventMap = 1546,
		EventMapLapse = 1547,
		EventMapQuest = 1548,
		QuestDBCheck = 1549,
		CostumeEffect = 1550,
		CostumeEffectCheck = 1551,
		EmergencyEscape = 1552,
		SPUpdated = 1553,
		BuffHPDecrease = 1554,
		ItemMixCheck = 1555,
		ItemMixCheckCust = 1556,
		PVEPimp = 1557,
		PVPPimp = 1558,
		SkillPrepTime = 1559,
		SkillPrepID = 1560,
		MD5Hash = 1561,
		MD5Time = 1562,
		SpeedCheck = 1563,
		Slytherin = 1564,
		EPEvent = 1565,
		AreaQuest = 1566,
		CWPlayer = 1567,
		LMS = 1568,
		PVPHit = 1569,
		Mautareta = 1570,
		Necklace = 1571,
		Belt = 1572,
		CritChance = 1573,
		OrnamentDmg = 1574,
		BeltBuff = 1575,
		NecklaceCD = 1576,
		BeltCD = 1577,
		AntiKS = 1578,
		Party = 1579,
		Duel = 1580,
		CallBuffer = 1581,
		CallPlayer = 1582,
		CallPlayer2 = 1583,
		StormCheck = 1584,
		StormTick = 1585,
		InstanceCD = 1586,
		LawlessPoints = 1587,
		LawlessEXP = 1588,
		TriangularType = 1589,
		TriangularEmblemSet = 1590,
		TriangularEmblemPull = 1591,
		TriangularState = 1592,
		TriangularTime = 1593,
		TriangularItemIID = 1594,
		ContractingSpace = 1595,
		ImprovingAttack = 1596,
		ImprovingDefense = 1597,
		RecoveringHP = 1598,
		SpontaneousCure = 1599,
		Recovery = 1600,
		Unkillableness = 1601,
		Precision = 1602,
		TeleportBuff = 1603,
		AssaPointsLimit = 1604,
		IPAddress = 1605,
		LawlessPort = 1606,
		HostilityValue = 1607,
		DamageAggro = 1608,
		SkillManaCost = 1609,
		OTPScroll = 1610,
		EvaScroll = 1611,
		OTPScrollCheck = 1612,
		EvaScrollCheck = 1613,
		EXPLoss = 1614,
		Artillery = 1615,
		ExtensionCheck = 1616,
		SinEventMobs = 1617,
		SinEventPlayers = 1618,
		EmokTeleport = 1619,
		BossEXP = 1620,
		NewName = 1621,
		Reborn = 1622,
		TimedCheck = 1623,
		ShamanBuff = 1624,
		BypassAFK = 1626,
		NewComer = 7826,
		Mute = 164,
		Jail = 177,
		CDProtect = 3750,
		DelayProtect = 6750,
		BuffPhyAtk = 7080,
		BuffMagAtk = 7480,
		DailyQuestBegin = 10000,
		DailyQuestEnd = 20000,
		DailyRepeatBegin = 20000,
		DailyRepeatEnd = 30000,
		DailyCountBegin = 30000,
		DailyCountEnd = 40000,
		MonsterQuestBegin = 40000,
		MonsterQuestEnd = 60000,
		NirvanaBuff = 61000,
		F10Buff = 61531,
		F10BuffCancel = 61532,
		NameOn = 61533,
		Ravenclaw = 61543,
		Hufflepuff = 61544,
		MissionBuff = 61545,
		CurrentMissionBuff = 61546,
		NextMissionBuff = 61547,
		Gryffindor = 61548,
		Emote = 61549,
		CJBEXP = 61550,
		MystPhy = 61551,
		MystMag = 61552,
		MystDef = 61553,
		MystHP = 61554,
		MystOTP = 61555,
		MystEVA = 61556,
		PowerAdm = 61557,
		Blessing = 59566,
		DailyDuty = 31571,
		NormalDuty = 31572,
		MiniBoss = 31573,
		InstanceDuty = 31574,
		DutyTrigger = 31579,
		MissionMonsterBuff = 31580,
		MissionMonsterQuest = 31581,
		MissionMonsterMob = 31582, 
		IceStone = 61568,
		StandardOn = 61567,
		HonorPVE = 61575,
		HonorPVP = 61576,
		HonorFatal = 61577,
		HonorEB = 61578,
		BlessingTrigger = 61581,
		BattlefieldBoss = 6760,
		CastleWarBuffW = 6761,
		ItemsEffects = 61583,
		EffectsIID = 61584,
		WeaponUp = 61585,
		WeaponsEffects = 61586,
		WEffectIID = 61587,
		Certificates = 62500,

	};
}

std::string Int2String(int value)
{
	std::stringstream ss;
	ss << value;
	std::string str = ss.str();
	return str;
}

int String2Int(std::string String)
{
	int Integer;
	std::istringstream iss(String);
	iss >> Integer;
	return Integer;
}

std::string GetHexString(char *bt)
{
	std::string s; s.clear();

	for (int i = 0; i < strlen(bt); i++)
	{
		byte b = bt[i];
		int n = 0, n1 = 0, n2 = 0;
		n = (int)b;
		n1 = n & 15;
		n2 = (n >> 4) & 15;
		
		if (n2 > 9)
			s += Int2String((char)(n2 - 10 + (int)'A'));
		else
			s += Int2String(n2);
		
		if (n1 > 9)
			s += Int2String((char)(n1 - 10 + (int)'A'));
		else
			s += Int2String(n1);
		
		if ((i + 1) != strlen(bt) && (i + 1) % 4 == 0) s += "-";
	}

	return s;
}
int catchInt(std::string s) {

	int value = 0;
	for(int i=0;i<s.size();i++){
		if(isdigit(s[i]))
			value += s[i];
	}
	return value;
}

namespace PartyVsParty
{
	int Time = 0;
	int MemberSize = 0;
}

namespace SufferingValley
{
	bool Active = false;
	int Time = 0;
	std::string FirstGuild = "";
	std::string SecondGuild = "";
	int GuildFirst = 0;
	int GuildSecond = 0;
	int RedScore = 0;
	int BlueScore = 0;
	int Round = 0;
	bool BlueOpened = false;
	bool RedOpened = false;
	bool Selection = false;
}

namespace Protect32
{
	int Time = 0;
	bool Active = false;
	std::string FirstGuild = "";
	std::string SecondGuild = "";
	int GuildFirst = 0;
	int GuildSecond = 0;
	int Prayer = 0;
	int RedScore = 0;
	int BlueScore = 0;
	int RedWin = 0;
	int BlueWin = 0;
	int Winner = 0;
	int Round = 0;
	int BluePrayerTime = 0;
	int RedPrayerTime = 0;
	bool BlueOpened = false;
	bool RedOpened = false;
	bool Selection = false;
}

namespace SinEvent
{
	bool Active = false;
	int Time = 0;
}

namespace RaidDoors
{
	int Round = 0;
	bool Opened = false;

}
namespace PartyVPartys
{
	int FlagID = 0;
}
namespace Battlefield
{
	bool Active = false;
	bool GoodVsEvil = false;
	int RedScore = 0;
	int BlueScore = 0;
	int BossID = 0;
	int Time = 0;
	std::vector<int> Players;
	int BTeamLvl = 0;
	int RTeamLvl = 0;
	int RedStoneID = 0;
	int BlueStoneID = 0;
	int RegisterAmount = 0;
	std::string slayerName = "";
}

namespace TriangularBattle
{
	bool Active = false;
	bool CDActive = false;
	int HumanScore = 0;
	int DemonScore = 0;
	int DoggebiScore = 0;

	int HumanPulling = 0;
	int DemonPulling = 0;
	int DoggebiPulling = 0;

	int HumanSetting = 0;
	int DemonSetting = 0;
	int DoggebiSetting = 0;
	int Time = 0;
	int CooldownTime = 0;
	int QuitSize = 0;
	int BuffTime = 0;

	std::vector<int> Players;
	int BTeamLvl = 0;
	int RTeamLvl = 0;
	int YTeamLvl = 0;

	int HumanNPCID = 0;
	int DemonNPCID = 0;
	int DoggebiNPCID = 0;

	int RegisterAmount = 0;
}

namespace Immortal
{
	bool Active = false;
}
namespace EggEvent
{
	bool Active = false;
}
namespace HappyHour
{
	bool Active = false;
}
namespace BossHunting
{
	int Time = 0;
	int maxDmg = 0;
}
namespace WorldCup
{
	bool Active = false;
	double Round = 0;
	int Fights = 0;
	bool FightsActive = false;
	int Time = 0;
}
namespace Scenario
{
	int Time ;
	int RedScore = 0;
	int BlueScore = 0;
	int BlueTeamSeal = 0;
	int RedTeamSeal = 0;
	int BlueTeamTowerCount = 0;
	int RedTeamTowerCount = 0;
	bool Active = false;
	int RegisterAmount = 0;
	std::string FirstGuild = "";
	std::string SecondGuild = "";
	int GuildFirst = 0;
	int GuildSecond = 0;
	bool Selection = false;
}

namespace Maut
{
	bool Active = false;
	int RegisterAmount = 0;
	int KillCount = 0;
	int Boss = 0;
	int Timer = 0;
}

namespace BossEXP
{
	bool Active = false;
	int RegisterAmount = 0;
	int KillCount = 0;
	int Boss = 0;
	int Timer = 0;
}

namespace F10
{
	bool Active = false;
	int RegisterAmount = 0;
	int ShowTime = 0;
	int KillCount = 0;
	int Dunamic = 0;
	int Cheios = 0;
	int Ilyer = 0;
	int DunamicSkill = 0;
	int CheiosSkill = 0;
	DWORD DunamicSkillDelay = 0;
	DWORD CheiosSkillDelay = 0;
}

namespace Hell
{
	bool Active = false;
	int Countdown = -1;
	int Round = 0;
	int KillCount = 0;
	int Time = 0;
	int Rebirth = 0;
	int Delay = 0;
	int Size = 0;
	int Lapse = 0;
}

namespace CaptureFlag
{
	bool Active = false;
	int RedScore = 0;
	int BlueScore = 0;
	int Time = 0;
	int LastHit = 0;
	int BTeamLvl = 0;
	int RTeamLvl = 0;
	int PlayerID = 0;
	int CurrentCapturers = 0;
	int MonsterOffset = 0;
}

namespace DuelTournament
{
	bool Active = false;
	int RoundTime = 0;
	int RedScore = 0;
	int BlueScore = 0;
	int RegisterAmount = 0;
	int Delay = 0;
	bool SelectPlayers = false;
	int FirstPlayer = 0;
	int SecondPlayer = 0;
}




enum PROPERTY_TYPE
{
	P_EXP = 0x19,
};
namespace LastManStand
{
	bool Active = false;
	int RegisterAmount = 0;
	int Notice = 0;
	std::string WinnerName;
	int Time = 0;
}

namespace Hunting
{
	bool Active = false;
	int Guild = 0;
	void *Monster = 0;
	int Time = 0;
	int End = 0;
}

namespace DamageEvent
{
	bool Active = false;
}

namespace Raid
{
	bool Active = false;
	int Round = 0;
	int Time = 0;
}

namespace GuildRaid
{
	bool Active = false;
	int Time = 0;
	void* Boss = 0;
	int GID = 0;
	int Reward = 0;
}


struct ConfigPetLife
{
	int Time;
	int Player;
};

struct ConfigIceArrow
{
	DWORD Cooldown;
	DWORD Delay;
};


struct ConfigMining
{
	DWORD Time;
	int Index;
	int Amount;
	int Cycle;
};


struct ConfigPlayerQuest
{
	int Active;
	int MobAmount;
	int Repeat;
	int Time;
};



struct PacketCheck
{
	long int FirstDelay;
	int Type;
};

struct ShoutsMaps
{
	int item;
};

struct Vote
{
	std::string Token;
	int Time;
};

struct Team
{
	int PID;
	std::string Name;
	int Points;
};

namespace CoordinatesGet
{
	bool Active = false;
	int X1 = 0;
	int Y1 = 0;
	int X2 = 0;
	int Y2 = 0;
	int X3 = 0;
	int Y3 = 0;
	int Z3 = 0;
}

struct WCGroups
{
	std::vector<Team> Groups;
};

struct UserInfo
{
	std::string Hardware;
	std::string PCName;
	std::string MAC;
};

struct Blocked
{
	int id;
	std::string Hardware;
	std::string PCName;
};

struct SkillDisabling
{
	int Class;
	int Map;
};




struct MD5Map
{
	int Index;
	std::string hash;
};
struct SoulsP
{
	int SetTime;
	int Dmg;
};
struct PickedChoice
{
	int Position;
	int Opponent;
	int FightNumber;
};
struct Fight
{
	int Player1;
	int P1Position;
	int Player2;
	int P2Position;
	int CoordX;
	int CoordY;
	double Round;
	Fight(){
		P1Position=0;
		Player1=0;
		P2Position=0;
		Player2=0;
		CoordX=0;
		CoordY=0;
	}
	Fight(int NewPlayer1,int NewPlayer2,int X,int Y,int Position,int Position2){
		Player1 = NewPlayer1;
		P1Position = Position;
		Player2 = NewPlayer2;
		P2Position = Position2;
		CoordX = X;
		CoordY = Y;
	}
};
struct Fights
{
	std::vector<Fight> FightList;
};
struct Winners
{
	std::vector<int> PlayerList;
};
struct PlayerFight
{
	Fight fight;
	Team team;
	int group;
};

struct BuffData
{
	Lock lock;
	unsigned long Value;
};

struct FakeShop
{
	int ShopIndex;
	std::string Name;
};




struct BetTrade
{
	int PID;
	int Item;
	int Amount;
};

struct ManaCost
{
	int ManaOriginal;
	int ManaExtra;
};

struct AuctionItem
{
	std::string Seller;
	int BidRemain;
	int Price;
	int PID;
	int RPID;
	std::string Bidder;
	int CurrentBid;
	int Index;
	int Prefix;
	int Amount;
	int SetGem;
	char ItemPacket[67];
};


struct CenterNotice {
	std::string Day;
	std::string Msg;
	int type;
};

enum CGenMonsterEx {
	nIndex = 8,
	nMap,
	nArea,
	nMax,
	nUnknown1,
	nLive,
	nLeft,
	nTop,
	nRight,
	nBottom,
	nSMap,
	nUnknown2,
	nCycle,
	nUnknown3
};

struct GenMonster
{
	DWORD unk_0;
	DWORD unk_4;
	DWORD unk_8;
	DWORD unk_12;
	DWORD unk_16;
	DWORD unk_20;
	DWORD unk_24;
	DWORD unk_28;
	DWORD Index; //32   *((_DWORD *)v3 + 128) = *(_DWORD *)(a2 + 32);
	DWORD Map;   //36   *((_DWORD *)v3 + 79) = *(_DWORD *)(a2 + 36);
	DWORD ID;  //40  *((_DWORD *)v3 + 111) = *(_DWORD *)(a2 + 40);
	DWORD Max;   //44
	DWORD Cur;   //48
	DWORD unk_52;
	DWORD X1;    //56    *((_DWORD *)v3 + 112) = *(_DWORD *)(a2 + 56);
	DWORD Y1;    //60  *((_DWORD *)v3 + 113) = *(_DWORD *)(a2 + 60);
	DWORD X2;    //64 *((_DWORD *)v3 + 114) = *(_DWORD *)(a2 + 64);
	DWORD Y2;    //68  *((_DWORD *)v3 + 115) = *(_DWORD *)(a2 + 68)
	DWORD unk_72;  // *(_DWORD *)(a2 + 320);
	DWORD unk_76; // Get Tick Count
	DWORD unk_80;
	DWORD unk_84;
	DWORD unk_88;
	DWORD unk_92;
	DWORD unk_96;
	DWORD unk_100;
	DWORD unk_104;
	DWORD unk_108;
	DWORD unk_112;
	DWORD unk_116;
	DWORD unk_120;
	DWORD unk_124;
	DWORD unk_128;
	DWORD unk_132;
	DWORD unk_136;
	DWORD unk_140;
	DWORD unk_144;
};

struct MailItem_
{
	int Index;
	int MaxEnd;
	int CurEnd;
	int Info;
	int Num;
	int XHit;
	int XDefense;
	int XAttack;
	int XMagic;
	int XDodge;
	int Protect;
	int UpgrLevel;
	int SetGem;
	int Prefix;
	int ItemStat;
};
struct BuffStruct {
	int Time;
	int Value;
};

struct SendCreate {
	int Riding;
	int NamePad;
	int SuitUsing;
	int WepWear;
	int CustWear;
	int ArmorWears;
	int Pet1;
	int Pet2;
	int Pet3;
	int PetIID1;
	int PetIID2;
	int PetIID3;
	int CostumeEffect;
	int CostumeEffectCheck;
	int LawlessEXP;
	int GState;
};

struct eventMapMonster {
	int CIndex;
	int Quest;

	eventMapMonster() {
		CIndex = 0;
		Quest = 0;
	}
};



struct GuildTopDonator
{
	std::string name;
	int PID;
	int Amount;
};

struct PacketEncryption
{
	int Key;
	int Time;
};


struct SVParticipant
{
	int Specialty;
	int Level;
	std::string Name;
};



struct RestoreItem
{
	int IID;
	int Index;
	int RestoreTime;
	int Date;
	int Num;
	int Info;
	int Prefix;
	int MaxEnd;
	int CurEnd;
	int SetGem;
	int XAtk;
	int XMagic;
	int XDefense;
	int XHit;
	int XDodge;
	int Protect;
	int UpgrLevel;
	int UpgrRate;
	int PetTime;
	int ItemStat;
};

struct JobSystem
{
	int action;
	int compare4;
	int compare3;
	int Class;
};
struct RewardMessage {
	std::string message;
	int textColor;
	int messageType; // Added messageType member
};
int round(double value) {
	return static_cast<int>(value + 0.5);
}

static int ShamanBuffs[] = { 401, 403, 407, 409, 413 };
unsigned __int64 _ExpTable[312];
Poll pollAsk;
time_t uptimestart; 
int GuildWinnerCW = 0, AllyWinnerCW = 0, WarEndTime = 0;
int CryptKey = 0;
std::string ConfigCheckDB1, ConfigCheckDB2;
int firstDig = 0;
int ScaniaLicense = 0;
volatile LONG OnlinePlayers = 0;
volatile LONG PlayerLevelNotice = 0;
volatile LONG MonsterReloaded = 0;
volatile LONG auctionItemsNum = 0;
int HuntingID = 0, CWGID = 0 ;
int NPCID = 0;
std::string WCWinner = "None";
std::string HuntingName = "", CWGuildName = "";
int DNPCEDailyLimit = 0, DNPCECollectedTotalItem = 0, DNPCELeftTime = 0, test = 0;
int NPCEDailyLimit = 0, NPCECollectedTotalItem = 0, NPCELeftTime = 0; char ItemShopPacket[9000] = {0};
//char AuctionPacket[9000] = { 0 };
int AuctionAmount = 0, AuctionSize = 0;
char FakePlayerPacket[14];
#define HIDWORD(l) ((DWORD)(((DWORDLONG)(l)>>32)&0xFFFFFFFF))
std::string thisServerName = "";
Lock itemStat = Lock();
Lock npcLock = Lock();
Lock itemBet = Lock();
Lock auctionVecLock = Lock();
Lock petLifeLock = Lock();
Lock itemLockLock = Lock();
Lock duelLock = Lock();
Lock duelShowLock = Lock();
ConcurrentMap<int, SkillRangeConfig> CheckRangeConfig;

ConcurrentMap<int, AreaExpItem> AreasExpItems; // declare a vector to hold the areas
ConcurrentMap<int, int> HighGradeBof;
ConcurrentMap<int, int> HighGradeImperial;
std::unordered_map<int, std::pair<std::string, int>> EmoteSystem;
//std::unordered_map<int, std::string> EmoteSystem;
std::unordered_map<int, MissionInfo> MissionQuests;
std::unordered_map<int, MissionInfo> MAbandonCheck;
std::unordered_map<int, CertificatesPlayer> certPlayer;
std::unordered_map<int, std::unordered_set<int>> activeMapsByPID;

std::unordered_map<int, MissionInfo> MissionQuestsItem;
ConcurrentMap<int, Certificates> AreaCert;
ConcurrentMap<int, Certificates> AreaCertMap;

ConcurrentMap<int, PerfectParty> My_PerfectParty;
std::unordered_map<int, int> playerPartySizes;

std::unordered_map<int, DailyDuty> DutyQuest;

std::vector<RewardMessage> PlayerRewardNotice;
ConcurrentSet<int> BoundAllowedItems;
ConcurrentMap<int, std::vector<MLMReward>> MLMRewards;
ConcurrentMap<int, Combinator> Combinators;
ConcurrentMap<int, Items> RentQuests;
ConcurrentMap<int, EmokCertConf> EmokCerts;
ConcurrentMap<int, int> PlayerVsPlayerDmg;
std::vector<SinSpawner> SinSpawners;

ConcurrentMap<int, int> RestoredIIDs;
ConcurrentMap<long, std::vector<GuildBuff>> ActiveGuildBuffs;
ConcurrentMap<int, std::vector<GuildTopDonator>> GuildTopDonatorList;
ConcurrentMap<int, GuildBuffQuest> GuildBuffQuests;
RegistrationMap<long, int> GuildBuffItems;
std::vector<int> GuildBuffs;
RegistrationMap<int, int> GuildRaidItems;
ConcurrentMap<int, SVParticipant> SVParticipantsRed;
ConcurrentMap<int, SVParticipant> SVParticipantsBlue;
ConcurrentMap<int, int> ChannelItems;
ConcurrentMap<int, GuildRaidLevel> GuildRaidLevels;
ConcurrentMap<int, NecklaceBuff> NecklaceBuffs;
ConcurrentMap<int, BeltBuff> BeltBuffs;
ConcurrentMap<int, ConfigBuff> BuffCheck;
ConcurrentMap<int, BuffMaker> BuffMakerCheck;
ConcurrentMap<int, BuffDisable> BuffDisableCheck;
ConcurrentMap<int, BuffDisable> BuffRemoveCheck;
ConcurrentMap<std::string, ShoutData> CustomShouts;
ConcurrentMap<std::string, CommandLink> CustomCommands;
ConcurrentMap<std::string, ShoutData> CustomHouse;
std::unordered_map<int, int> PlayerMissionProgress;
std::unordered_map<char, int> npcMap;
ConcurrentMap<int, ItemExchange> ItemExchanges;
ConcurrentMap<int, SMultiple> EXPMultipliers;
	
ConcurrentMap<int, Reborn> Reborns;
ConcurrentMap<int, RbPenalty> RebornsPenalty;
ConcurrentMap<int, RbPenalty> NonRebornsPenalty;
ConcurrentMap<int, RbGear> RebornGear;
ConcurrentMap<int, RbQuest> RebornsMaps;
ConcurrentMap<int, int> FatalDmg;
ConcurrentMap<int, MSkill> MSkills;
ConcurrentMap<int, std::vector<int>> MonsterSkills;
ConcurrentMap<int, int> CostumeEffects;
ConcurrentMap<int, int> CostWeaponsEffects;
ConcurrentMap<int, ConcurrentSet<int>> EventMapsRegistration;
ConcurrentMap<int, eventMap> EventMapsQuests;
ConcurrentMap<int, int> LoginAttempts;
ConcurrentSet<int> EventMapsQuestsOn;
ConcurrentSet<int> EventMaps;
ConcurrentMap<long, int> MonsterDamage;
ConcurrentMap<int, int> EventMapsOn;
ConcurrentMap<int, int> InstancesCD;
ConcurrentMap<int, eventMapMonster> EventMapsMobsOn;
ConcurrentMap<int, int> ObjectChannels;
std::vector<Point> JailCoords;
ConcurrentMap<int, Reward> Rewards;
ConcurrentMap<int, SBoxes> Boxes;
ConcurrentMap<int, F10EXP> F10EXPs;
ConcurrentMap<int, F10EXP> MautEXPs;
ConcurrentMap<int, F10EXP> BossEXPs;
ConcurrentMap<int, BossEXPMsg> BossEXPMsgs;
ConcurrentMap<int, SendCreate> SendCreatePlayer;
RegistrationMap<int,int> SummonQuestRegistration;
RegistrationMap<int, int> EventQuests;
SystemRegistration<int> Lottery;
SystemRegistration<int> XLottery;
ConcurrentMap<int, ConcurrentMap<long int, int>> BuffList;
ConcurrentMap<int, int> MobPets;
ConcurrentSet<int> PKIgnoreItem;
ConcurrentMap<int, std::vector<DuelRegistre>> DuelRegistrationList;
ConcurrentMap<int, std::string> DuelNames;
std::vector<int> DuelUnbuff;
ConcurrentMap<int, int> MonsterDisappear;
ConcurrentMap<int, FakePlayers_> FakePlayers;
ConcurrentMap<int, FakeItems_> FakeItems;
ConcurrentMap<std::string, int> FakeNames;
ConcurrentSet<int> DailyLoginLimits;
ConcurrentMap<int, SecretBlackSmithSkill>SecretBlackSmith;
ConcurrentMap<int, SwapMineral>MakeMinerals;
ConcurrentMap<int, SwapMineral>MakeChange;
ConcurrentMap<int, MakeItem_>MakeItem;
//ConcurrentMap<int, ConcurrentMap<int,int>>DailyQuestMonsterKilled;
ConcurrentSet<int> InvCheck;
ConcurrentSet<int> PKDropEnable;
ConcurrentMap<int, SoulPocketConfig> SoulPockets;
ConcurrentMap<int, MiningItem> MiningItems;
ConcurrentMap<int, PartyReward> PartyRewards;
ConcurrentMap<int, PartyReg> PTEnabled;
ConcurrentMap<std::string, PartyReg> PTCommands;
ConcurrentMap<std::string, std::vector<PartyReg>> PartyTimer;
std::vector<PartyReg> PartyRegistrations;
ConcurrentMap<int, PartyBattle> CurPartys;
ConcurrentSet<int> MQuest;
ConcurrentMap<int, QuestEx> QuestExs;
ConcurrentMap<int, std::string> EventTimer;
ConcurrentMap<int, std::string> EventMapsTimer;
ConcurrentMap<int, std::string> EndTimer;
ConcurrentMap<int, MSummonConfig> SummonQuest;
ConcurrentMap<int, MSummonedConfig> SummonedQuest;
ConcurrentMap<int, ZProtection> ugog;
ConcurrentSet<std::string> DisablePM;
ConcurrentSet<std::string> DisableEXP;

ConcurrentSet<int> ugCheck;
ConcurrentSet<int> ogCheck;
ConcurrentMap<int, CreateMonsterPet> MonsterPet;
ConcurrentMap<int, int> ItemQuest;
ConcurrentMap<int, IWebs> ItemWebsite;
ConcurrentMap<int, int> ItemReward;
ConcurrentMap<int, std::string> QuestWebsite;
ConcurrentMap<std::string, std::string> Tracker;
ConcurrentMap<int, int> NewItemType;
ConcurrentMap<int,Winners> FinalsWinners;
ConcurrentMap<int, std::vector<Items>> StarterItems;
ConcurrentMap<int, StarterClass> Starters;
ConcurrentMap<int, InitSwap> InitPetSwap;
ConcurrentMap<int, std::vector<int>> QuestRentItem;
ConcurrentMap<int,PlayerFight> CupRegistration;
ConcurrentMap<int, Vote> PlayerVote;
ConcurrentMap<uint32_t, int> VoteList;
ConcurrentMap<int, std::vector<RectLevel>> RectArea;
ConcurrentMap<int, std::vector<AFKCheck>> AFKMap;
ConcurrentMap<int, int> EnchantCount;
std::set<int> Macro;
ConcurrentMap<int, MasterEnchanting> MasterEnchant;
ConcurrentMap<int, RidingCollection> RidingCollections;
ConcurrentMap<int, SummonGuard> SGuard;
ConcurrentMap<int, int> RidingCollectionIndex;
ConcurrentMap<int, ItemTime> TimedItems;
ConcurrentMap<int, RentalExtend> RentalItems;
ConcurrentMap<int, ItemBuff> BuffedItems;
ConcurrentMap<int, ItemMss> MSS;
ConcurrentMap<int, int> PacketSpamConf;
ConcurrentMap<int, int> EmblemDropped;
ConcurrentMap<int, int> PacketSpam;
ConcurrentMap<int,PacketCheck> PacketDelay;
ConcurrentMap<int,WCGroups> CupOfKal;
ConcurrentMap<int,Fights> FirstFight;
ConcurrentMap<int,Fights> SecondFight;
ConcurrentMap<int, Fights> ThirdFight;
std::map<int, std::vector<BetTrade>> BetItems;
ConcurrentSet<std::string> RewardLimit;
ConcurrentMap<uint32_t, int> MiningLimit;
ConcurrentMap<uint32_t, int> FishingLimit;
ConcurrentMap<uint32_t, int> ShopLimit;
ConcurrentMap<int,std::vector<ChanceItem>> FishingList;
std::vector<ChanceItem> F10Items;
std::vector<ChanceItem> MautItem;
std::vector<ChanceItem> BossExpItem;
std::vector<ChanceItem> MonstersItem;

SystemRegistration<int> RaidSystem;
ConcurrentMap<int, OldStats> PlayerStats;
ConcurrentMap<int, int> NPCIDs;
ConcurrentMap<int, Poll> Polls;
ConcurrentMap<int, Poll> PollTimer;
ConcurrentMap<std::string, ConcurrentSet<int>> PollVotes;
ConcurrentMap<int, int> PollVoteAmount;
ConcurrentMap<int,SingleConfigBuffer> SingleBufferCheck;
ConcurrentSet<int> SinDisable;
ConcurrentMap<int, ConcurrentSet<int>> DisableSkill;
std::vector<int> MD5FileChecker;
ConcurrentMap<int, ConcurrentSet<int>> DisableSkillFile;
ConcurrentSet<int> RidingDisableSkill;
ConcurrentMap<int, CItemUsed> ItemUsed;
ConcurrentMap<int, CItemTasty> ItemTasty;
ConcurrentMap<int, CItemTasty> ItemHpDef;
ConcurrentMap<int, CItemTasty> ItemScrolls;
ConcurrentMap<int, CItemTasty> ItemExpansion;
ConcurrentMap<int, ItemsEffects> EquipEffects;
ConcurrentMap<int, PVEWeaponsS> PVEWeapon;
ConcurrentMap<int, CItemTasty> ItemBuffSrv;

ConcurrentMap<int, ItemLimit> ItemLimits;
ConcurrentMap<int, ItemQuestRepeat> ItemQuestRepeats;
ConcurrentMap<int, ItemLimitConf> ItemLimitUsage;
ConcurrentMap<int, int> ItemNPC;
std::map<int, SummonNPC> ItemNPCSummoned;
std::map<int, SummonNPC> NPCSummoned;
ConcurrentMap<int, CAutoNotice> AutoNotices;
ConcurrentMap<int, CMonstersBuff> MonstersBuff;
ConcurrentMap<int, CMonstersBuff> RMonstersBuff;
ConcurrentMap<int, CQuestsNotice> QuestsNotice;
ConcurrentMap<int, CQuestsNotice> cQuestsNotice;

ConcurrentMap<int, CMonstersRewards> MonstersRewards;

ConcurrentSet<int> QuestDisable;
ConcurrentSet<int> QBattleEnable;
ConcurrentMap<int, QuestTime> TimedQuest;
ConcurrentMap<int, AreaQuest> AreaQuests;
ConcurrentSet<int> TimedMaps;
ConcurrentMap<long, QuestTime> PlayerTimedQuest;
ConcurrentMap<long int, AuctionItem> AuctionItems;
std::vector<AuctionItem> AuctionVec;
ConcurrentMap<int,Area> MapLvl;
ConcurrentMap<int, ShoutsMaps> ShoutMap;

ConcurrentSet<int> PacketBlock;
ConcurrentMap<int,int> MD5Checks;
std::vector<MD5Type> MD5File;
ConcurrentMap<int, QuestLevel> QuestLevels;
ConcurrentMap<int, MD5Type> MD5MapsKCM;
ConcurrentMap<int, MD5Type> MD5MapsOPL;
ConcurrentMap<int, SkillDamage> SkillsDamage;
ConcurrentMap<int, UserInfo> User;
ConcurrentMap<int, int> SocketInfos;
ConcurrentMap<int, int> SocketPacket;
ConcurrentMap<int, PacketEncryption> SocketNewInfos;
ConcurrentSet<uint32_t> BlockList;
ConcurrentSet<int> SkillsPVP;
ConcurrentMap<int,int> WCDamage;
ConcurrentMap<int,WCRew> WCRewards;
ConcurrentMap<int, AreaMax> MapMax;
ConcurrentSet<int> UnGap;
ConcurrentSet<int> UnAggro;
ConcurrentSet<int> UnBreak;
std::vector<int> LawlessEXP;
ConcurrentSet<int> UnChannel;
ConcurrentSet<int> ChannelMaps;
ConcurrentSet<int> UnReload;
ConcurrentSet<int> AntiKs;
ConcurrentSet<std::string> Filter;
ConcurrentMap<int, Restriction> Restrictions;
ConcurrentMap<int, Restriction> HWIDRestrictions;
ConcurrentMap<int, HaninRate> HaninLow;
ConcurrentMap<int, HaninRate> HaninMiddle;
ConcurrentMap<int, HaninRate> HaninHigh;
ConcurrentMap<int,CheckCalculations> PVPConfigCalculations;
ConcurrentSet<int> ItemDisable;
ConcurrentSet<int> AuctionItemDisable;
ConcurrentMap<int,int> PlayerOffset;
ConcurrentMap<__int16,ConfigItemShop> ItemShopCheck;
//ConcurrentMap<__int64,ConfigPlayerQuest> PlayerQuest;
ConcurrentMap<int, ConfigDailyQuest> DailyQuest;
ConcurrentMap<int, std::vector<MonsterDailyQuest>> MonsterQuests;
ConcurrentMap<int, std::vector<MonsterDailyDuty>> DutyMonsterQuests;

ConcurrentMap<int, std::vector<ConfigLevelReward>> LevelReward;
ConcurrentMap<int, std::vector<ConfigLevelReward>> BattlepassReward;
ConcurrentMap<int, std::vector<ConfigLevelReward>> PremiumPass;
ConcurrentMap<int,ConfigMining> CheckMining;
std::map<int, int> GetItemStat;
ConcurrentSet<int> ItemStatDisable;
ConcurrentSet<int> ItemTimerDisable;
ConcurrentMap<int,ConfigBuffer> BufferCheck;
std::set<int> summonedGuardians;
ConcurrentMap<int,ConfigRentArmor> RentArmor;
ConcurrentMap<int, ConfigRentWeapon> RentWeapon;
ConcurrentMap<int,CheckSkillBook> SkillBook;
ConcurrentMap<int, CheckSkillBook> SkillDowngrade;
ConcurrentMap<int,CheckConfigCooldown> CheckCooldownConfig;
ConcurrentMap<int, JobSystem> Cooldowns;
ConcurrentMap<int,CheckConfigEggCooldown> CheckEggCooldownConfig;
ConcurrentMap<int,CheckCalculations> ConfigCalculations;
ConcurrentMap<int,PimpConfig> CheckPimp;
ConcurrentMap<int, std::vector<CheckSummonTimer>> SummonTimer;
ConcurrentMap<std::string, std::vector<RGBNotice>> RGBAutoNotice;
ConcurrentMap<std::string, int> CustomNotices;
ConcurrentMap<std::string, int> AutoNoticesRGB;

ConcurrentMap<int, int> PetLifeCheck;
ConcurrentMap<int, int> PetLifeExtend;
ConcurrentSet<int> SocketCheck;

ConcurrentMap<std::string,std::string> Read2ndPwd;
ConcurrentSet<int> UnBlob;
ConcurrentMap<int, ConcurrentSet<int>> StoreItems;
ConcurrentSet<int> MixConfigPrefix;
ConcurrentMap<int, int> MixConfigInfo;
ConcurrentMap<int,std::string> MixConfigMsg;
SystemRegistration<int> BattlefieldRegistration;
SystemRegistration<std::string> BattlefieldHWID;
SystemRegistration<std::string> LastManHWID;

ConcurrentMap<int, std::string> SufferingValleyRegistration;
SystemRegistration<int> SVGuild1;
SystemRegistration<int> SVGuild2;
SystemRegistration<int> TBRegistration;
ConcurrentSet<int> ScenarioRegistration;
ConcurrentSet<int> SummonTrack;
std::vector<DKInfo> ScenarioGuild;
ConcurrentMap<int, std::vector<AutoNoticeConf>> AutoCenterNotices;
std::vector<int> RShopItems;
std::vector<int> RShopAmounts;
std::vector<int> RShopLevels;

ConcurrentMap<int, double> LevelGap;
ConcurrentMap<int, TrainingLvl> TrainingEXP;
ConcurrentMap<int, ChanceItem> TrainingDrops;
ConcurrentMap<int,int> HonorShop;
ConcurrentMap<int, int> HonorIndex;
ConcurrentMap<int, ConcurrentSet<int>> SystemBlacklist;
SystemRegistration<int> F10Registration;
SystemRegistration<int> MautRegistration;
SystemRegistration<int> BossEXPRegistration;
ConcurrentMap<int,int> WeaponReplace;
SystemRegistration<int> CaptureRegistration;
ConcurrentMap<int,int> WeaponReplaceIndex;
std::unordered_map<int, std::string> WeaponReplaceMsg;

//std::vector<int> HighestDamage;
ConcurrentSet<int> WeaponReplacePrefix;
ConcurrentSet<int> DisablePrefix;
ConcurrentMap<int, int> ArmorPimpConfig;
ConcurrentMap<int, int> PVEDamagePimp;
ConcurrentMap<int, int> PVPDamagePimp;
std::map<int,std::string> ItemLockCheck;
ConcurrentMap<int, ConfigPetTime> PetTime;
ConcurrentMap<int, ConfigTimeTalisman> NormalPetTalisman;
ConcurrentMap<int, ConfigTimeTalisman> MonsterPetTalisman;
ConcurrentMap<int, ConfigTimeTalisman> CostumeTalisman;
ConcurrentMap<int, ConfigTimeTalisman> SkinTalisman;

ConcurrentMap<int, int> SoulPocketEffect;
ConcurrentMap<int, SuitStat> SuitStats;
ConcurrentMap<int, SkillLearn> SkillChecks;
ConcurrentMap<int, DailyReward> DailyLogins;
ConcurrentMap<int, TaskQ> TaskQuests;

ConcurrentSet<int> PlayerBlockCheck;
std::vector<int> ProtectLeaderList;
ConcurrentMap<int,std::string> ProtectLeaderName;
ConcurrentSet<int> ProtectBlackList;
ConcurrentSet<int> DestructingBlackList;
ConcurrentSet<int> SVBlackList;
SystemRegistration<int> LastManRegistration;
//ConcurrentMap<int, std::string> FriendsName;



#pragma comment(lib,"Detours/enigma_ide.lib")
#pragma comment(lib,"Detours/detours.lib")
#pragma comment(lib,"Ws2_32.lib")
#pragma comment(lib,"Wininet.lib")
#pragma comment(lib,"netapi32.lib")
#pragma comment(lib,"wbemuuid.lib")
#include <stdio.h>
#include <lm.h>
#include "Detours/enigma_ide.h"
#include "Detours/detours.h"
#include "Exports.h"
#include "Memory.h"
#include "Tools.h"
#include "Interface.h"
#include "Time.h"
#include "NPC.h"
#include "Lisans.h"
#include "ReadConfig.h"
#include "CProtection.h"
#include "StatPointValue.h"
#include "PasswordDecode.h"
#include "ISkill.h"
#include "IChar.h"
#include "ResetContinueSkill.h"
#include "IItem.h"
#include "ItemType.h"
#include "IBuff.h"
#include "IQuest.h"
#include "Calculations.h"
#include "Cleaner.h"
#include "GetBuff.h"
#include "CreateBuff.h"
#include "Process.h"
#include "DuelTournament.h"
#include "SufferingValley.h"
#include "TriangularBattle.h"
#include "PartyVsParty.h"
#include "WorldCup.h"
#include "Summon.h"
#include "CBaseDelete.h"
#include "Hardware.h"
#include "MyFunctions.h"
#include "Mage.h"
#include "RefreshBuff.h"
#include "Mix.h"
#include "Reload.h"
#include "Channel.h"
#include "Lawless.h"
#include "ExpTable.h"
#include "EagleStat.h"
#include "StoneOfBirth.h"
#include "StoneOfChance.h"
#include "MonsterBlob.h"
#include "SaveAllProperty.h"
#include "BuyItemEx.h"
#include "SendMail.h"
#include "Duel.h"
#include "CastleWarFix.h"
#include "Timer.h"
#include "Command.h"
#include "ProcessMsg.h"
#include "Loader.h"
#include "CDBProcess.h"
#include "ArmorPut.h"
#include "StandardPut.h"
#include "Ornament.h"
#include "CChar.h"
#include "Player.h"
#include "OnLoadPlayer.h"
#include "LevelUp.h"
#include "SkillUpgradeCheck.h"
#include "AutoLearn.h"
#include "Packet.h"
#include "SkillPointer.h"
#include "CanAttack.h"
#include "EggExp.h"
#include "FinalDamage.h"
#include "Trade.h"
#include "Quest.h"
#include "ItemUse.h"
#include "Knight.h"
#include "Egg.h"
#include "Archer.h"
#include "Thief.h"
#include "Behead.h"
#include "WalkOnTheAir.h"
#include "Shaman.h"
#include "SkillCalculation.h"
#include "Skill.h"
#include "EggSkill.h"
#include "SkillCheck.h"
#include "DropItem.h"
#include "WeaponPut.h"
#include "DefenseChangePrefix.h"
#include "WeaponChangePrefix.h"
#include "CutDownExp.h"
#include "Calls.h"
#include "Transform.h"
#include "ContinuesSkill.h"
#include "Start.h"
#include "NormalHit.h"
#include "Storage.h"
#include "ItemFixes.h"
#include "Menu.h"


BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	{
							   // Set the custom exception handler
			//				   SetUnhandledExceptionFilter(CustomExceptionHandler);

			InitializeADVAPI32(); 
			ConfigCheckDB1 = "kal_auth";
			ConfigCheckDB2 = "kal_db";
			ReadConfig(false);
			thisServerName = ServerName;
			ItemFixes();
			ExpMultiplier();
			SwitchTable();
			Loader();
			SetSkillPointer();
			uptimestart = time(0);
			firstDig = (int)uptimestart % 10;
			CryptKey = sha256((Int2String(uptimestart))) % 9000;
			timeReloading = time(0);
			ConfigDBCheck = 1;
			SetLearnUpgradeLimit();
			DetourTransactionBegin();
			DetourAttach(&(PVOID&)CIOServer::Start, Start);
			DetourAttach(&(PVOID&)_Window::Proc, Proc);
			if (ConfigDBCheck)
			{
				//DetourAttach(&(PVOID&)CIOCriticalSection::Enter, CIOCriticalSectionEnter);
				//DetourAttach(&(PVOID&)CIOSocket::Enter, CIOSocketEnter);
				DetourAttach(&(PVOID&)MSocket::AcceptConnection, AcceptConnection);
				DetourAttach(&(PVOID&)MSocket::OnClose, OnCloseSocket);

				DetourAttach(&(PVOID&)CIOObject::_Release, ObjectRelease);
				DetourAttach(&(PVOID&)CIOBuffer::Release, CIOBufferRelease);
				DetourAttach(&(PVOID&)CIOObject::_AddRef, ObjectRef);
				DetourAttach(&(PVOID&)CIOSocket::Create, CIOSocketCreate);
				DetourAttach(&(PVOID&)CIOSocket::CIOSocket__Close, CIOSocketClose);
				DetourAttach(&(PVOID&)CIOSocket::GraceFulClose, CIOSocketGracefulClose);
				DetourAttach(&(PVOID&)CPlayer::_IntoInven, IntoInventory);
				DetourAttach(&(PVOID&)CPlayer::_OutOfInven, OutOfInventory);
				DetourAttach(&(PVOID&)CPlayer::RemoveItem, PlayerRemoveItem);
				DetourAttach(&(PVOID&)CChar::RefreshBuff, ObjectTick);
				DetourAttach(&(PVOID&)CNPCDoor::Tick, NPCTick);
		//		DetourAttach(&(PVOID&)CParty::DistrbuteItem, PartyDistrbute);
				DetourAttach(&(PVOID&)CBuff::CreateBuff, CreateBuff);
				DetourAttach(&(PVOID&)CChar::CancelAllBuff2, CancelAllBuffs);
				DetourAttach(&(PVOID&)CDBSocket::Process, Process);
				DetourAttach(&(PVOID&)CSkill::BlessingOfHealth, BlessingOfHealth);
				DetourAttach(&(PVOID&)CSkill::BlessingOfStrength, BlessingOfStrength);
				DetourAttach(&(PVOID&)CSkill::BlessingOfAgility, BlessingOfAgility);
				DetourAttach(&(PVOID&)CSkill::BlessingOfIntelligence, BlessingOfIntelligence);
				DetourAttach(&(PVOID&)CSkill::BlessingOfCriticalHit, BlessingOfCriticalHit);
				DetourAttach(&(PVOID&)CSkill::RefiningWeapon, RefiningWeapon);
				DetourAttach(&(PVOID&)CSkill::DefenseImprovement, DefenseImprovement);
				DetourAttach(&(PVOID&)CSkill::SpeedUp, SpeedUp);
				DetourAttach(&(PVOID&)CSkill::CheckBuff, CheckBuff);
				DetourAttach(&(PVOID&)CChar::PerfectCure, PerfectCureFix);
				DetourAttach(&(PVOID&)CPlayer::EnforceItem, EnforceItem);
				DetourAttach(&(PVOID&)CPlayer::OnTeleport, MyOnTeleport);
				DetourAttach(&(PVOID&)CPlayer::Imperial, Imperial);
				DetourAttach(&(PVOID&)CItemTransform::ApplySpec, TransformApplySpec);
				DetourAttach(&(PVOID&)CItemTransform::FreeSpec, TransformFreeSpec);
				DetourAttach(&(PVOID&)CItemMoney::Drop, MoneyDrop);
				DetourAttach(&(PVOID&)CItem::Drop, ItemDrop);
				DetourAttach(&(PVOID&)Undefined::StoneOfChance, StoneOfChance);
				DetourAttach(&(PVOID&)CPlayer::InitStat, SOB);
				DetourAttach(&(PVOID&)CPlayer::EndPvP, EndPvP);
				DetourAttach(&(PVOID&)CPlayer::SaveAllProperty, SaveAllProperty);
				DetourAttach(&(PVOID&)CPlayer::SendMail, SendMail);
				DetourAttach(&(PVOID&)CPlayer::ChatCommand, ChatCommand);
				DetourAttach(&(PVOID&)CPlayer::ProcessMsg, MyProcessMsg);
				DetourAttach(&(PVOID&)CDBSocket::RealProcess, CDBProcess);
				DetourAttach(&(PVOID&)CCalendar::OnTimer, OnTimer);
				DetourAttach(&(PVOID&)CPlayer::Tick, Tick);
				DetourAttach(&(PVOID&)CPlayer::CPlayer, InitPlayer);
				DetourAttach(&(PVOID&)CPlayer::OnLoadPlayer, OnLoadPlayer);
				DetourAttach(&(PVOID&)CPlayer::Process, Packet);
				DetourAttach(&(PVOID&)CPlayer::LevelUp, LevelUp);
				DetourAttach(&(PVOID&)CSkill::Occupation, Occupation);
				DetourAttach(&(PVOID&)CSkill::LearnSkillCheck, LearnSkillCheck);
				DetourAttach(&(PVOID&)CSkill::SkillOnLoad, SkillOnLoad);
				DetourAttach(&(PVOID&)CPlayer::LevelUpUnknown, AutoLearn);
				DetourAttach(&(PVOID&)CPlayer::CancelTrade, CancelTrade);
				DetourAttach(&(PVOID&)CPlayer::TradeAgreed, TradeAgreed);
				DetourAttach(&(PVOID&)CPlayer::ShowOffItem, ShowOffItem);
				DetourAttach(&(PVOID&)CPlayer::CanAttack, CanAttack);
				DetourAttach(&(PVOID&)CChar::CheckHit, CheckHit);
				DetourAttach(&(PVOID&)CItemTransform::UpdateExp, UpdateExp);
				DetourAttach(&(PVOID&)CChar::GetFinalDamage, GetFinalDamage);
				DetourAttach(&(PVOID&)CPlayer::GetPalsyDamage, GetPalsyDamage);
				DetourAttach(&(PVOID&)CChar::GetFatalDamage, GetFatalDamage);
				DetourAttach(&(PVOID&)CQuest::Run, Quest);
				DetourAttach(&(PVOID&)CItemGeneral::Use, ItemUse);
				DetourAttach(&(PVOID&)CSkill::ExecuteTransformSkill, ExecuteTransformSkill);
				DetourAttach(&(PVOID&)CSkill::ExecuteSkill, ExecuteSkill);
				DetourAttach(&(PVOID&)CPlayer::DropItemONPKDie, DropItemONPKDie);
				DetourAttach(&(PVOID&)CItemDefense::ApplySpec, DefenseApplySpec);
				DetourAttach(&(PVOID&)CItemDefense::PutOff, DefensePutOff);
				DetourAttach(&(PVOID&)CItemWeapon::ApplySpec, WeaponApplySpec);
				DetourAttach(&(PVOID&)CItemWeapon::PutOff, WeaponPutOff);
				DetourAttach(&(PVOID&)CItemWeapon::PutOn, WeaponPutOn);
				DetourAttach(&(PVOID&)CItemStandard::Broken, StandardBroken);
				DetourAttach(&(PVOID&)CItemStandard::ApplySpec, StandardApplySpec);
				DetourAttach(&(PVOID&)CItemStandard::PutOn, StandardPutOn);
				DetourAttach(&(PVOID&)CItemStandard::PutOff, StandardPutOff);
				DetourAttach(&(PVOID&)CItemDefense::ChangePrefix, DefenseChangePrefix);
				DetourAttach(&(PVOID&)CItemWeapon::ChangePrefix, WeaponChangePrefix);
				DetourAttach(&(PVOID&)CItemWeapon::CharmingCheat, WeaponCharmingCheat);
				DetourAttach(&(PVOID&)CItemWeapon::Charming, WeaponCharming);
				DetourAttach(&(PVOID&)CItemWeapon::UpgradeLevel, WeaponUpgradeLevel);
				DetourAttach(&(PVOID&)CItemWeapon::UpgradeDestroy, WeaponUpgradeDestroy);
				DetourAttach(&(PVOID&)CPlayer::RevivalItem, RevivalItem);
				DetourAttach(&(PVOID&)CPlayer::RevivalSkill, RevivalSkill);
				DetourAttach(&(PVOID&)CMonsterGuildWar::Damage, GuildWarDamage);
				DetourAttach(&(PVOID&)CPlayer::CutdownExp, CutdownExp);
				DetourAttach(&(PVOID&)CSkill::Calls, Calls);
				DetourAttach(&(PVOID&)CConsole::Black, Black);
				DetourAttach(&(PVOID&)CConsole::Blue, Blue);
				DetourAttach(&(PVOID&)CConsole::Red, Red);
				DetourAttach(&(PVOID&)CItemDefense::PutOn, ArmorPutOn);
				DetourAttach(&(PVOID&)CPlayer::MAILProcess, MAILProcess);
				DetourAttach(&(PVOID&)CPlayer::Transform, Transform);
				DetourAttach(&(PVOID&)CSkill::Calculations, Calculations);
				DetourAttach(&(PVOID&)CPlayer::Attack, NormalHit);
				DetourAttach(&(PVOID&)CPlayer::PKKill, PKKill);
				DetourAttach(&(PVOID&)CMonsterMaguniMaster::Tick, SummonTick);
				DetourAttach(&(PVOID&)CInitMonster::DropItem, InitMonsterDrop);
				DetourAttach(&(PVOID&)CSkill::LifeAbsorption, LifeAbsorption);
				DetourAttach(&(PVOID&)CSkill::MagicTick, MagicTick);
				DetourAttach(&(PVOID&)CItem::NewItem, NewItem);
				DetourAttach(&(PVOID&)CItem::SubState, SubState);
				DetourAttach(&(PVOID&)CItemOrnament::PutOn, OrnamentPutOn);
				DetourAttach(&(PVOID&)CItemOrnament::ApplySpec, OrnamentApplySpec);
				DetourAttach(&(PVOID&)CItemOrnament::PutOff, OrnamentPutOff);
				DetourAttach(&(PVOID&)CMonsterMaguniMaster::AI, SummonAI);
				DetourAttach(&(PVOID&)CMonsterMaguniMaster::Die, SummonDie);
				DetourAttach(&(PVOID&)CMonsterReal::Die, MonsterDie);

				DetourAttach(&(PVOID&)CItemWeapon::StorageIn, CItemWeaponStorageIn);
				DetourAttach(&(PVOID&)CItemDefense::StorageIn, CItemDefenseStorageIn);
				DetourAttach(&(PVOID&)CBase::Delete, CBaseDelete);
				DetourAttach(&(PVOID&)CNPCSiegeGun::Reply, SiegeGunReply);
				DetourAttach(&(PVOID&)CMonsterMagic::Create, CMonsterMagicCreate);
				DetourAttach(&(PVOID&)CPlayer::CheckBlock, CheckBlock);
				DetourAttach(&(PVOID&)CItem::CreateItem, MyCreateItem);
				DetourAttach(&(PVOID&)CItemGeneral::StorageIn, CItemGeneralStorageIn);
				DetourAttach(&(PVOID&)CItemGeneral::StorageOut, CItemGeneralStorageOut);
				DetourAttach(&(PVOID&)CMonsterReal::Tick, MonsterTick);
				DetourAttach(&(PVOID&)CMonsterReal::AddHostility, MonsterAddHostility);
				DetourAttach(&(PVOID&)CMonsterReal::ScanSight, MonsterScanSight);
				DetourAttach(&(PVOID&)CObjectDB::Open, CObjectDBOpen);
				DetourAttach(&(PVOID&)CItemOrnament::ChangePrefix, OrnamentChangePrefix);
				DetourAttach(&(PVOID&)CItem::OnTimer, ItemOnTimer);
				DetourAttach(&(PVOID&)CPlayer::GameStart, MyGameStart);
				DetourAttach(&(PVOID&)CNPC::SendCreate, NPCSendCreate);
				DetourAttach(&(PVOID&)CPlayer::SendCreate, MySendCreate);
				DetourAttach(&(PVOID&)CCastle::WarBegin, WarBegin);
				DetourAttach(&(PVOID&)CGuild::GetWarEndTime, GetWarEndTime);
				DetourAttach(&(PVOID&)CCastle::WarEnd, WarEnd);
				DetourAttach(&(PVOID&)CItemOrnament::StorageIn, CItemOrnamentStorageIn);
				DetourAttach(&(PVOID&)CBuffPrtyEx::FreeBuff, CBuffPrtyExFreeBuff);
				DetourAttach(&(PVOID&)CItemOrnament::SetWearState, OrnamentSetWearState);
				DetourAttach(&(PVOID&)CItemDefense::SetWearState, DefenseSetWearState);
				DetourAttach(&(PVOID&)CPlayer::UpdateProperty, MyUpdateProperty);
				DetourAttach(&(PVOID&)CMonsterReal::AllotExp, MonsterAllotEXP);
				DetourAttach(&(PVOID&)CParty::AllotExp, PartyEXP);
				DetourAttach(&(PVOID&)CParty::Join, PartyJoin);
				DetourAttach(&(PVOID&)CParty::Leave, PartyLeave);
				DetourAttach(&(PVOID&)CParty::Exile, PartyExile);
				DetourAttach(&(PVOID&)CBuff::CBuffPrtyExIsExpired, CBuffCBuffPrtyExIsExpired);
			}
			DetourTransactionCommit();
			break;
		}
	case DLL_PROCESS_DETACH:
		{
			FinalizeADVAPI32();
			ItemFixes();
			ExpMultiplier();
			SwitchTable();
			Loader();
			SetSkillPointer();
			SetLearnUpgradeLimit();
			DetourTransactionBegin();
			DetourDetach(&(PVOID&)CIOServer::Start, Start);
			DetourDetach(&(PVOID&)_Window::Proc, Proc);
			DetourDetach(&(PVOID&)CIOObject::_Release, ObjectRelease);
			DetourDetach(&(PVOID&)CIOBuffer::Release, CIOBufferRelease);
			DetourDetach(&(PVOID&)CIOObject::_AddRef, ObjectRef);

			DetourDetach(&(PVOID&)MSocket::AcceptConnection, AcceptConnection);
			DetourDetach(&(PVOID&)MSocket::OnClose, OnCloseSocket);

			//DetourDetach(&(PVOID&)CParty::DistrbuteItem, PartyDistrbute);
			DetourDetach(&(PVOID&)CIOSocket::Create, CIOSocketCreate);
			DetourDetach(&(PVOID&)CIOSocket::CIOSocket__Close, CIOSocketClose);
			DetourDetach(&(PVOID&)CIOSocket::GraceFulClose, CIOSocketGracefulClose);
			DetourDetach(&(PVOID&)CPlayer::_IntoInven, IntoInventory);
			DetourDetach(&(PVOID&)CPlayer::_OutOfInven, OutOfInventory);
			DetourDetach(&(PVOID&)CPlayer::RemoveItem, PlayerRemoveItem);
			DetourDetach(&(PVOID&)CChar::RefreshBuff, ObjectTick);
			DetourDetach(&(PVOID&)CNPCDoor::Tick, NPCTick);
			DetourDetach(&(PVOID&)CBuff::CreateBuff, CreateBuff);
			DetourDetach(&(PVOID&)CChar::FindBuff, FindBuff);
			DetourDetach(&(PVOID&)CChar::CancelAllBuff2, CancelAllBuffs);
			DetourDetach(&(PVOID&)CDBSocket::Process, Process);
			DetourDetach(&(PVOID&)CSkill::BlessingOfHealth, BlessingOfHealth);
			DetourDetach(&(PVOID&)CSkill::BlessingOfStrength, BlessingOfStrength);
			DetourDetach(&(PVOID&)CSkill::BlessingOfAgility, BlessingOfAgility);
			DetourDetach(&(PVOID&)CSkill::BlessingOfIntelligence, BlessingOfIntelligence);
			DetourDetach(&(PVOID&)CSkill::BlessingOfCriticalHit, BlessingOfCriticalHit);
			DetourDetach(&(PVOID&)CSkill::RefiningWeapon, RefiningWeapon);
			DetourDetach(&(PVOID&)CSkill::DefenseImprovement, DefenseImprovement);
			DetourDetach(&(PVOID&)CSkill::SpeedUp, SpeedUp);
			DetourDetach(&(PVOID&)CSkill::CheckBuff, CheckBuff);
			DetourDetach(&(PVOID&)CChar::PerfectCure, PerfectCureFix);
			DetourDetach(&(PVOID&)CPlayer::EnforceItem, EnforceItem);
			DetourDetach(&(PVOID&)CPlayer::OnTeleport, MyOnTeleport);
			DetourDetach(&(PVOID&)CPlayer::Imperial, Imperial);
			DetourDetach(&(PVOID&)CItemTransform::ApplySpec, TransformApplySpec);
			DetourDetach(&(PVOID&)CItemTransform::FreeSpec, TransformFreeSpec);
			DetourDetach(&(PVOID&)CItem::Drop, ItemDrop);
			DetourDetach(&(PVOID&)CItemMoney::Drop, MoneyDrop);
			DetourDetach(&(PVOID&)Undefined::StoneOfChance, StoneOfChance);
			DetourDetach(&(PVOID&)CPlayer::InitStat, SOB);
			DetourDetach(&(PVOID&)CPlayer::EndPvP, EndPvP);
			DetourDetach(&(PVOID&)CPlayer::SaveAllProperty, SaveAllProperty);
			DetourDetach(&(PVOID&)CPlayer::SendMail, SendMail);
			DetourDetach(&(PVOID&)CPlayer::ChatCommand, ChatCommand);
			DetourDetach(&(PVOID&)CPlayer::ProcessMsg, MyProcessMsg);
			DetourDetach(&(PVOID&)CDBSocket::RealProcess, CDBProcess);
			DetourDetach(&(PVOID&)CCalendar::OnTimer, OnTimer);
			DetourDetach(&(PVOID&)CPlayer::Tick, Tick);
			DetourDetach(&(PVOID&)CPlayer::CPlayer, InitPlayer);
			DetourDetach(&(PVOID&)CPlayer::OnLoadPlayer, OnLoadPlayer);
			DetourDetach(&(PVOID&)CPlayer::Process, Packet);
			DetourDetach(&(PVOID&)CPlayer::LevelUp, LevelUp);
			DetourDetach(&(PVOID&)CSkill::Occupation, Occupation);
			DetourDetach(&(PVOID&)CSkill::LearnSkillCheck, LearnSkillCheck);
			DetourDetach(&(PVOID&)CSkill::SkillOnLoad, SkillOnLoad);
			DetourDetach(&(PVOID&)CPlayer::LevelUpUnknown, AutoLearn);
			DetourDetach(&(PVOID&)CPlayer::CancelTrade, CancelTrade);
			DetourDetach(&(PVOID&)CPlayer::TradeAgreed, TradeAgreed);
			DetourDetach(&(PVOID&)CPlayer::ShowOffItem, ShowOffItem);
			DetourDetach(&(PVOID&)CPlayer::CanAttack, CanAttack);
			DetourDetach(&(PVOID&)CChar::CheckHit, CheckHit);
			DetourDetach(&(PVOID&)CMonsterReal::ScanSight, MonsterScanSight);
			DetourDetach(&(PVOID&)CItemTransform::UpdateExp, UpdateExp);
			DetourDetach(&(PVOID&)CChar::GetFinalDamage, GetFinalDamage);
			DetourDetach(&(PVOID&)CPlayer::GetPalsyDamage, GetPalsyDamage);
			DetourDetach(&(PVOID&)CChar::GetFatalDamage, GetFatalDamage);
			DetourDetach(&(PVOID&)CQuest::Run, Quest);
			DetourDetach(&(PVOID&)CNPCSiegeGun::Reply, SiegeGunReply);
			DetourDetach(&(PVOID&)CItemGeneral::Use, ItemUse);
			DetourDetach(&(PVOID&)CSkill::ExecuteTransformSkill, ExecuteTransformSkill);
			DetourDetach(&(PVOID&)CSkill::ExecuteSkill, ExecuteSkill);
			DetourDetach(&(PVOID&)CPlayer::DropItemONPKDie, DropItemONPKDie);
			DetourDetach(&(PVOID&)CItemDefense::ApplySpec, DefenseApplySpec);
			DetourDetach(&(PVOID&)CItemDefense::PutOff, DefensePutOff);
			DetourDetach(&(PVOID&)CItemWeapon::ApplySpec, WeaponApplySpec);
			DetourDetach(&(PVOID&)CItemWeapon::PutOff, WeaponPutOff);
			DetourDetach(&(PVOID&)CItemWeapon::PutOn, WeaponPutOn);
			DetourDetach(&(PVOID&)CItemStandard::Broken, StandardBroken);
			DetourDetach(&(PVOID&)CItemStandard::ApplySpec, StandardApplySpec);
			DetourDetach(&(PVOID&)CItemStandard::PutOn, StandardPutOn);
			DetourDetach(&(PVOID&)CItemStandard::PutOff, StandardPutOff);
			DetourDetach(&(PVOID&)CItemDefense::ChangePrefix, DefenseChangePrefix);
			DetourDetach(&(PVOID&)CItemWeapon::ChangePrefix, WeaponChangePrefix);
			DetourDetach(&(PVOID&)CItemWeapon::CharmingCheat, WeaponCharmingCheat);
			DetourDetach(&(PVOID&)CItemWeapon::Charming, WeaponCharming);
			DetourDetach(&(PVOID&)CItemWeapon::UpgradeLevel, WeaponUpgradeLevel);
			DetourDetach(&(PVOID&)CItemWeapon::UpgradeDestroy, WeaponUpgradeDestroy);
			DetourDetach(&(PVOID&)CPlayer::RevivalItem, RevivalItem);
			DetourDetach(&(PVOID&)CPlayer::RevivalSkill, RevivalSkill);
			DetourDetach(&(PVOID&)CMonsterGuildWar::Damage, GuildWarDamage);
			DetourDetach(&(PVOID&)CPlayer::CutdownExp, CutdownExp);
			DetourDetach(&(PVOID&)CSkill::Calls, Calls);
			DetourDetach(&(PVOID&)CConsole::Black, Black);
			DetourDetach(&(PVOID&)CConsole::Blue, Blue);
			DetourDetach(&(PVOID&)CConsole::Red, Red);
			DetourDetach(&(PVOID&)CItemDefense::PutOn, ArmorPutOn);
			DetourDetach(&(PVOID&)CPlayer::MAILProcess, MAILProcess);
			DetourDetach(&(PVOID&)CPlayer::Transform, Transform);
			DetourDetach(&(PVOID&)CSkill::Calculations, Calculations);
			DetourDetach(&(PVOID&)CPlayer::Attack, NormalHit);
			DetourDetach(&(PVOID&)CPlayer::PKKill, PKKill);
			DetourDetach(&(PVOID&)CMonsterMaguniMaster::Tick, SummonTick);
			DetourDetach(&(PVOID&)CInitMonster::DropItem, InitMonsterDrop);
			DetourDetach(&(PVOID&)CSkill::LifeAbsorption, LifeAbsorption);
			DetourDetach(&(PVOID&)CSkill::MagicTick, MagicTick);
			DetourDetach(&(PVOID&)CItem::NewItem, NewItem);
			DetourDetach(&(PVOID&)CItem::SubState, SubState);
			DetourDetach(&(PVOID&)CItemOrnament::PutOn, OrnamentPutOn);
			DetourDetach(&(PVOID&)CItemOrnament::ApplySpec, OrnamentApplySpec);
			DetourDetach(&(PVOID&)CItemOrnament::PutOff, OrnamentPutOff);
			DetourDetach(&(PVOID&)CMonsterMaguniMaster::AI, SummonAI);
			DetourDetach(&(PVOID&)CMonsterMaguniMaster::Die, SummonDie);
			DetourDetach(&(PVOID&)CMonsterReal::Die, MonsterDie);

			DetourDetach(&(PVOID&)CItemWeapon::StorageIn, CItemWeaponStorageIn);
			DetourDetach(&(PVOID&)CItemDefense::StorageIn, CItemDefenseStorageIn);
			DetourDetach(&(PVOID&)CBase::Delete, CBaseDelete);
			DetourDetach(&(PVOID&)CMonsterMagic::Create, CMonsterMagicCreate);
			DetourDetach(&(PVOID&)CPlayer::CheckBlock, CheckBlock);
			DetourDetach(&(PVOID&)CItemGeneral::StorageIn, CItemGeneralStorageIn);
			DetourDetach(&(PVOID&)CItemGeneral::StorageOut, CItemGeneralStorageOut);
			DetourDetach(&(PVOID&)CMonsterReal::Tick, MonsterTick);
			DetourDetach(&(PVOID&)CMonsterReal::AddHostility, MonsterAddHostility);
			DetourDetach(&(PVOID&)CItemOrnament::ChangePrefix, OrnamentChangePrefix);
			DetourDetach(&(PVOID&)CItem::OnTimer, ItemOnTimer);
			DetourDetach(&(PVOID&)CPlayer::GameStart, MyGameStart);
			DetourDetach(&(PVOID&)CNPC::SendCreate, NPCSendCreate);
			DetourDetach(&(PVOID&)CPlayer::SendCreate, MySendCreate);
			DetourDetach(&(PVOID&)CCastle::WarBegin, WarBegin);
			DetourDetach(&(PVOID&)CGuild::GetWarEndTime, GetWarEndTime);
			DetourDetach(&(PVOID&)CCastle::WarEnd, WarEnd);
			DetourDetach(&(PVOID&)CItemOrnament::StorageIn, CItemOrnamentStorageIn);
			DetourDetach(&(PVOID&)CBuffPrtyEx::FreeBuff, CBuffPrtyExFreeBuff);
			DetourDetach(&(PVOID&)CItemOrnament::SetWearState, OrnamentSetWearState);
			DetourDetach(&(PVOID&)CItemDefense::SetWearState, DefenseSetWearState);
			DetourDetach(&(PVOID&)CPlayer::UpdateProperty, MyUpdateProperty);
			DetourDetach(&(PVOID&)CMonsterReal::AllotExp, MonsterAllotEXP);
			DetourDetach(&(PVOID&)CParty::AllotExp, PartyEXP);
			DetourDetach(&(PVOID&)CParty::Join, PartyJoin);
			DetourDetach(&(PVOID&)CParty::Leave, PartyLeave);
			DetourDetach(&(PVOID&)CParty::Exile, PartyExile);
			DetourDetach(&(PVOID&)CBuff::CBuffPrtyExIsExpired, CBuffCBuffPrtyExIsExpired);
			DetourDetach(&(PVOID&)CObjectDB::Open, CObjectDBOpen);
			DetourTransactionCommit();
			break;
		}
	}
	return TRUE;
}