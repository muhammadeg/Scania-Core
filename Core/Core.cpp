#define _WIN32_DCOM
#include <Windows.h>
#include <process.h>
#include <wininet.h>
#include <time.h>
#include <random>
#include <math.h>
#include <map>
#include <unordered_map>
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
// Define a structure to represent a set of coordinates
struct TeleCoordinates {
	uint32_t x;
	uint32_t y;
	uint32_t z;
	uint32_t comment;
};
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
};


struct ShoutData {
	COLORREF color;
	int index;
	int remove;

	ShoutData() : color(0), index(0), remove(0) {} // Default constructor

	ShoutData(COLORREF c, int i, int r) : color(c), index(i), remove(r) {}
};
enum TextColor
{
	TEXTCOLOR_GENERAL   = RGB( 255, 255, 255 ),
	TEXTCOLOR_INFOMSG   = RGB(  70, 227, 232 ),
	TEXTCOLOR_SHUTDOWN  = RGB( 240, 116,  15 ),
	TEXTCOLOR_ORANGE    = RGB( 255, 128,  64 ),
	TEXTCOLOR_BLUE      = RGB(   0, 128, 255 ),
	TEXTCOLOR_BLUELIGHT = RGB(   0, 255, 255 ),
	TEXTCOLOR_YELLOW    = RGB( 255, 255, 128 ),
	TEXTCOLOR_RED       = RGB( 255,   0,   0 ),
	TEXTCOLOR_PARTY     = RGB( 210,  64,   0 ),
	TEXTCOLOR_GUILD     = RGB(  10, 255, 229 ),
	TEXTCOLOR_ALLIANCE  = RGB( 128, 128, 192 ),
	TEXTCOLOR_GREEN     = RGB(   0, 255,   0 ),
	TEXTCOLOR_DARKGREEN = RGB(   0, 170,   0 ),
	TEXTCOLOR_FAILED    = RGB( 250, 210,   0 ),
	TEXTCOLOR_CLASSMATE = RGB(   0, 128,   0 ),
	TEXTCOLOR_PUPIL     = RGB( 255, 128,  64 ),
	TEXTCOLOR_PINK      = RGB( 255, 155, 255 ),
	TEXTCOLOR_Undefined = RGB(152, 155, 189),
	TEXTCOLOR_UndefinedI = RGB(150, 10, 25),
	TEXTCOLOR_DARK_MAGENTA = RGB(139, 0, 139),
	TEXTCOLOR_DAMAGE = RGB(255, 187, 153),
	GRAY = RGB(190, 190, 190),
	RED = RGB(255, 0, 0),
	DARK_RED = RGB(139, 0, 0),
	ORANGE_RED = RGB(255, 69, 0),
	BLUE = RGB(0, 128, 255),
	DARK_BLUE = RGB(0, 0, 139),
	DARK_SKYBLUE = RGB(0, 178, 238),
	STEAL_BLUE = RGB(99, 184, 255),
	YELLOW = RGB(238, 238, 0),
	GREEN_YELLOW = RGB(173, 255, 47),
	ORANGE = RGB(255, 165, 0),
	DARK_ORANGE = RGB(255, 140, 0),
	GREEN = RGB(0, 255, 0),
	LIME_GREEN = RGB(50, 205, 50),
	DARK_GREEN = RGB(0, 100, 0),
	LAWN_GREEN = RGB(124, 252, 0),
	FOREST_GREEN = RGB(34, 139, 34),
	CYAN = RGB(0, 255, 255),
	DARK_CYAN = RGB(0, 139, 139),
	SADDLE_BROWN = RGB(139, 69, 19),
	SANDY_BROWN = RGB(244, 164, 96),
	PERU = RGB(205, 133, 63),
	MAGENTA = RGB(255, 0, 255),
	DARK_MAGENTA = RGB(139, 0, 139),
	DARK_ORCHID = RGB(153, 50, 204),
	PURPLE = RGB(160, 32, 240),
	DEEP_PURPLE = RGB(255, 20, 147),
	GOLD = RGB(255, 215, 0),
	DARK_GOLD = RGB(184, 134, 11),
	MyOrange = RGB(184, 80, 11),

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
		Mute = 164,
		Jail = 177,
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
		Bandits = 61534,
		BanditsCheck1 = 61535,
		BanditsCheck2 = 61536,
		BanditsCheck3 = 61537,
		BanditsCheck4 = 61540,
		BanditsCheck5 = 61541,
		BanditsCheck6 = 61542,
		BanditsStart = 61538,
		BanditsMaxDeath = 61539,
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
		AdditionalDef = 61558,
		AdditionalStr = 61559,
		AdditionalHP = 61560,
		AdditionalAgi = 61561,
		AdditionalInt = 61562,
		AdditionalCrit = 61563,
		AdditionalRef = 61564,
		StickScale = 61565,
		Blessing = 61566,
		StandardOn = 61567,
		IceStone = 61568

	};
}

std::map<int, std::string> GuildNameMap; // Define the map at a global or visible scope

const char* GetGuildNameById(int guildId) {
	std::map<int, std::string>::iterator it = GuildNameMap.find(guildId);
	if (it != GuildNameMap.end()) {
		return it->second.c_str();
	}
	return "Unknown"; // Return a default value if guild name not found
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

namespace Battlefield
{
	bool Active = false;
	bool GoodVsEvil = false;
	int RedScore = 0;
	int BlueScore = 0;
	int Time = 0;
	std::vector<int> Players;
	int BTeamLvl = 0;
	int RTeamLvl = 0;
	int RedStoneID = 0;
	int BlueStoneID = 0;
	int RegisterAmount = 0;
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
	int Time = 3600;
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

namespace Bandits
{
	bool Active = false;
	int RegisterAmount = 0;
	int Time = 0;
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


struct ConfigBuff
{
	int MinLevel;
	int MaxLevel;
	int Buff;
	int Call;
	int Delete;
	std::string LimitMsg;
	int StrBuff;
	int AgiBuff;
	int HthBuff;
	int IntBuff;
	int DefBuff;
	int CritBuff;
	int SpeedBuff;
	int LocalHTML;
	int RefBuff;
	int LightningDefense;
	int IceDefense;
	int FireDefense;
	int OTPCall;
	int PhysicalAttack;
	int CallofDefense;
	int Time;
	int Quest_Index;
	int CQuest_Index;
	int Honorindex;
};

struct BuffDisable
{
	int BuffDisableIndex;
	int BuffDisableID;
};
struct BuffMaker
{
	int MinLevel;
	int MaxLevel;
	int Buff;
	int Call;
	int Maker;
	int Delete;
	std::string LimitMsg;
	int MinAttack;
	int MaxAttack;
	int Hp;
	int Str;
	int Int;
	int Wis;
	int Agi;
	int OTP;
	int Eva;
	int Def;
	int Fire_Resistance;
	int Ice_Resistance;
	int Lightning_Resistance;
	int Absorb;
	int CritRate;
	int CritDamage;
	int HTML;
	std::string BuffIcon;
	int Time;
	int Sys_name;
	int BuffID;
	int MaxMp;
	int MaxHp;
	int EBRate;
	std::string save;
	std::string mana_heal;
	std::string hp_heal;
	std::string Damage;
	std::string ExpALLOW;
	std::string Egg;
	int hp;
	int mana;
	int MD;
	int amount;
	int count;
	int altBuff;
	int BuffDisableIndex;
	int BuffDisableID;
};

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
	int Time = 0;
}

namespace Hunting
{
	bool Active = false;
	int Guild = 0;
	void *Monster = 0;
	int Time = 0;
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

struct CheckConfigCooldown
{
	int CooldownConfig;
	int DelayConfig;
};

struct CheckConfigEggCooldown
{
	int EggCooldownConfig;
	int EggDelayConfig;
};

struct CheckSkillBook
{
	int Class;
	int Action;
	int UpgradeAmount;
	int UpgradeMax;
	int DowngradeAmount;
	int RewardPoints;
};

struct CheckSummonTimer
{
	int Index;
	int Amount;
	int Map;
	int X;
	int Y;
	int Disappear;
	std::string Msg;
	std::string Day;
};

struct SkillRangeConfig {
	int maxRange;
};

struct CheckCalculations
{
	int Class;
	int Rate;
};

struct PimpConfig
{
	int Prefix;
	int GetA;
	int GetM;
	int GetTOA;
	int GetUpg;
};

struct ConfigPetLife
{
	int Time;
	int Player;
};

struct ConfigBuffer
{
	int Index;
	int Grade;
	int Delete;
	int Speed;
	int Limit;
};

struct ConfigIceArrow
{
	DWORD Cooldown;
	DWORD Delay;
};

struct ConfigRentArmor
{
	int Quest;
	int Index;
	int Prefix;
	int Def;
	int Eva;
	int Bof;
	int Dss;
	int Coin;
	int Time;
};

struct ConfigRentWeapon
{
	int Quest;
	int Index;
	int Prefix;
	int Attack;
	int Magic;
	int Toa;
	int Upgrade;
	int Mix;
	int Dss;
	int Coin;
	int Time;
};

struct ConfigMining
{
	DWORD Time;
	int Index;
	int Amount;
	int Cycle;
};

struct ConfigLevelReward
{
	int Class;
	int Index;
	int Prefix;
	int Amount;
	int Info;
	int Attack;
	int Magic;
	int Toa;
	int Upgrade;
	int Defense;
	int Evasion;
	int Endurance;
	std::string Msg;
};

struct ConfigDailyQuest
{
	int MobAmount;
	int Repeat;
	int Time;
	std::vector<std::string> Item;
	std::vector<std::string> ItemAmount;
	std::vector<std::string> Monsters;
	int Level;
	signed __int64 Exp;
	int Honor;
	int RewardPt;
	int Party;
	int Type;
	int Resetable;
	int HousePoints;
};

struct ConfigPlayerQuest
{
	int Active;
	int MobAmount;
	int Repeat;
	int Time;
};

struct FakePlayers_Shop {
	int amount;
	int iid;
	int price;
};
struct FakePlayers_ {
	std::string name;
	int id;
	int gstate;
	int hair;
	int face;
	int cclass;
	int state;
	int x;
	int y;
	int z;
	int direction;
	int weapon;
	int chest;
	int helmet;
	int glove;
	int boot;
	int shield;
	int skirt;
	int costume;
	int color;
	int honor;
	std::string msg;
	int check;
	ConcurrentMap<int, FakePlayers_Shop>Shop;
};
struct FakeItems_ {
	int amount;
	int price;
	int index;
};
struct ConfigPetTime
{
	int Time;
	int Heal;
	int Pick;
	int Monster;
	int Speed;
	int Exp;
	int Range;
	int AttackPet;
	int AOEDelay;
	int HPLimit;
	std::vector<std::string> effects;

	ConfigPetTime() {
		Time = 0, Heal = 0, Pick = 0, HPLimit = 0, Monster = 0, Speed = 0, Exp = 0, Range = 0, AttackPet = 0;
		effects = std::vector<std::string>();
	}
};

struct DailyReward
{
	std::string Items;
	std::string Amount;
	int Honor;
	int Reward;
	int HTML;
	int ClaimHTML;
};
struct TaskQ
{
	std::string Items;
	std::string Amount;
	std::string Require;
	std::string RequireAmount;
	int Honor;
	int Reward;
	int HTML;
};


struct ConfigItemShop
{
	int Type;
	int Priority;
	int Price;
	int Discount;
	int ItemIndex;
	int Amount;
};

struct AFKCheck
{
	RECT rectangle;
	int seconds;
};

struct Skills
{
	int Type;
	DWORD Time;
};

struct PacketCheck
{
	long int FirstDelay;
	int Type;
};
struct Area
{
	int level;
	int item;
	int type;
};

struct ShoutsMaps
{
	int item;
};
struct AreaMax
{
	int maxlevel;
	int type;
};
struct Vote
{
	std::string Token;
	int Time;
};

struct Items
{
	int Index;
	int Amount;
	int reward;
	int Prefix;
	int Bound;
	int Info;
	int Def;
	int Eva;
	int Bof;
	int Time;
	int Dss;
	int Attack;
	int Magic;
	int Toa;
	int Upgrade;
	int Mix;
	int ItemStat;
};

struct StarterClass
{
	int CoordX;
	int CoordY;
	int Map;
	int HTML;
	signed __int64 EXP;
	std::string Msg;
};

struct Team
{
	int PID;
	std::string Name;
	int Points;
};
struct Buffs
{
	int BuffId;
	int Effect;
	int Time;
	int SBKey;
	int SBName;
	Buffs(int NewBuff, int NewEffect, int NewTime, int SKill, int SName) {
		BuffId = NewBuff;
		Effect = NewEffect;
		Time = NewTime;
		SBKey = SKill;
		SBName = SName;
	}
};

struct Msss
{
	int MobIndex;
	int Time;
	int Amount;
	int Public;
};
struct AreaExpItem
{
	int level;
	int experience;
	int item;
	int type;
	int map;
	int save;
	int time;
};


struct MissionInfo {
	int nextmission;
	int teleportMap;
	int teleportX;
	int teleportY;
	int Monster;
	int Item;
	int itemAmount;
	int Amount;
	int rewardID;
	int progress;
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

struct ItemBuff
{
	std::vector<Buffs> BuffList;
};

struct ItemMss
{
	std::vector<Msss> MonsterList;
};

struct WCGroups
{
	std::vector<Team> Groups;
};

struct OldStats
{
	int Level;
	int MinAtk;
	int MaxAtk;
	int DeathBlow;
	int HP;
	int MP;
	int Eva;
	int OTP;
	int Int;
	int Agi;
	int Def;
	int ATK;
	int Str;
	int Hth;
	int Wis;
	int Absorb;
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
struct SingleConfigBuffer
{
	int Index;
	int Grade;
	int Delete;
	int Type;
};
struct SkillDisabling
{
	int Class;
	int Map;
};
struct CItemUsed
{
	int HTML;
	int Remove;
};

struct CItemTasty
{
	int index;
	int remove;
	int level;
	int Time;

};


struct ItemLimit
{
	int Usage;
	int Time;
};
struct ItemQuestRepeat {
	int Permanent;
	std::vector<int> Quests;
};
struct ItemTime
{
	int Time;
	int Wearable;
};
struct RentalExtend
{
	int Time;
	int Price;
};
struct QuestTime
{
	int Type;
	int Time;
	int MaxRepeat;
};

struct AreaQuest
{
	int Party;
	int LevelMin;
	int LevelMax;
	int Time;
	int TMap;
	int TX;
	int TY;
	int BMap;
	int BX;
	int BY;
};
int round(double value) {
	return static_cast<int>(value + 0.5);
}

struct CMonstersRewards
{
	int mobindex;
	int rewardid;
	int randomindex;
	int itemamount;
	int pickchance;

};
struct pRewards
{
	int Level;
	int Progress;
};
struct CQuestsNotice
{
	int QuestIndex;
	int QuestItem;
	int clearQ;
	int qAmount;
	int qFlag;
	std::string Notice;
};
struct CMonstersBuff
{
	int mobindex;
	int buffid;
	int buffgrade;

};
struct CAutoNotice
{
	int minutes;
	std::string msg;
	int color;

};

struct MD5Type
{
	std::string filename;
	std::string hash;
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
struct WCReward
{
	int Index;
	int Amount;
};
struct SkillDamage
{
	std::string damage;
	int PVE;
	int PVP;
	int Reduce;
	int AOE;
};
struct ZProtection
{
	int maxZ;
	int minZ;
};

struct WCRew
{
	std::vector<WCReward> RewardList;
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

struct CreateMonsterPet
{
	int Material1;
	int Count1;
	int Material2;
	int Count2;
	int Money;
	int Jewel;
};

struct SoulPocketConfig
{
	int Amount;
	int Refill;
	int Max;
};

struct HaninRate
{
	int Min;
	int Max;
};

struct Restriction
{
	std::string Commands;
	std::string HWIDs;
	int Trade;
	int Shop;
	int Storage;
	int Mail;
	int Party;
	int Duel;
	int Attack;
	int Drop;
	int Pick;
	int Skill;
};

struct MSummonConfig
{
	int Type;
	int QIndex;
	int RQuest;
	int ItemIndex;
	int ItemAmount;
	int MonsterIndex;
	int MonsterAmount;
	int Map;
	int X;
	int Y;
	std::string notice;
	int Check;
	int Limit;
};

struct MSummonedConfig
{
	int CurAmount;
	int Spawned;
	int Limit;
};

struct MakeItem_ {
	int item;
	std::string requireIndexs;
	std::string requireAmounts;
};

struct MonsterDailyQuest {
	int Quest;
	int Amount;
	int MainIndex;
};

struct ChanceItem {
	int Index;
	int Amount;
	int Chance;
};

struct ItemStruct {
	int Index;
	int Amount;
};

struct TrainingLvl
{
	int EXP;
	int Drop;
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

struct SummonNPC
{
	int NPC;
	int Store;
	int Time;
	int Model;
	int X;
	int Y;
	int Z;
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

struct RidingCollection {
	std::vector<int> Indexes;
	int Stat;
	int Rate;
};

struct SwapItem {
	int Index;
	int Chance;
	SwapItem(int nIndex, int nChance) {
		Index = nIndex;
		Chance = nChance;
	}
};

struct SwapMaterial {
	int Index;
	int Amount;
	SwapMaterial() {

	}
	SwapMaterial(int nIndex, int nAmount) {
		Index = nIndex;
		Amount = nAmount;
	}
};

struct InitSwap {
	SwapMaterial Material1;
	SwapMaterial Material12;
	SwapMaterial Material2;
	SwapMaterial Material22;
	std::vector<SwapItem> items;
};

struct SwapMineral {
	std::string requires;
	std::string requireAmounts;
	std::string itemRewards;
	std::string itemAmounts;
	std::string chances;
};
struct StickBuff {
	int Sgrade;
	int hp;
	int str;
	int agi;
	int def;
	int intel;
	int crit;
	int atk;
	std::string BuffName;
};
struct CenterNotice {
	std::string Day;
	std::string Msg;
	int type;
};

struct AutoNoticeConf {
	std::string Day;
	std::string Msg;
};

struct SecretBlackSmithSkill {
	std::string requires;
	std::string requireAmounts;
	std::string rewards;
};

struct IWebs {
	std::string URL;
	int remove;
};

struct PartyReg {
	int PID;
	std::string Day;
	std::string Time;
	int PVPArena;
	int PartySize;
	int MinLevel;
	int MaxLevel;
	int Type;
	int Quest;
	int RewardID;
	char Names[6][21];
	int nWin;
};

struct PartyBattle {
	bool FightAvailable;
	int RedScore;
	int BlueScore;
	int PartySize;
	int PTID1;
	int PTID2;
	int Time;
	int Reward;
	int Cooldown;
	PartyBattle() {
		FightAvailable = true;
		RedScore = 0;
		BlueScore = 0;
		PartySize = 0;
		PTID1 = 0;
		PTID2 = 0;
		Time = 0;
		Reward = 0;
		Cooldown = 10;
	}
};

struct PartyReward {
	std::vector<std::string> battleIndexes;
	std::vector<std::string> battleAmounts;
	std::vector<std::string> winnerIndexes;
	std::vector<std::string> winnerAmounts;
	int BattleReward;
	int BattleHonor;
	int WinnerHonor;
	int WinnerReward;
	PartyReward() {
		battleIndexes = std::vector<std::string>();
		battleAmounts = std::vector<std::string>();
		winnerIndexes = std::vector<std::string>();
		winnerAmounts = std::vector<std::string>();
		BattleReward = 0;
		BattleHonor = 0;
		WinnerHonor = 0;
		WinnerReward = 0;
	}
};

struct Reward {
	std::vector<std::string> Indexes;
	std::vector<std::string> Amounts;
	int HonorPts;
	int RewardPts;
	signed __int64 EXP;
	int Bound;
	int HTML;
	int HousePoints;
	int userKey;
};

struct DuelRegistre {
	int PID;
	std::string Name;
	char Level;
	char Class;
	int nVictory;
	DuelRegistre() {
		PID = 0;
		Name = "";
		nVictory = 0;
	}
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

struct DKInfo
{
	int GID;
	std::string Name;
};

struct RGBNotice
{
	std::string day;
	std::string msg;
	int Color;
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

struct eventMap {
	std::vector<std::string> monsters;
	std::vector<std::string> amounts; 
	std::vector<std::string> Reward;
	std::string Name;
	int Duration;
	int Lapse;
	std::vector<std::string> X;
	std::vector<std::string> Y;
	int LvlMin;
	int LvlMax;
	int Quest;
	int TX;
	int TY;
	int ReqItem;
	int ReqAmount;
	std::set<int> Maps;
	int Cooldown;
	int PTSize;
	int Type;
};

struct eventMapMonster {
	int CIndex;
	int Quest;

	eventMapMonster() {
		CIndex = 0;
		Quest = 0;
	}
};

struct MSkill
{
	int AOERange;
	int Cooldown;
	int EffectType;
	std::string Effect;
	int Buff;
	int BuffTime;
	int BuffValue;
	int DamageMin;
	int DamageMax;
	int SBName;
	int SBKey;
};

struct GuildBuff
{
	int BuffID;
	int Time;
	int Value;
	int SBName;
	int SBKey;
};

struct GuildBuffQuest 
{
	std::string Name;
	int Flag;
	int ReplyFlag;
	int Index;
	int Amount;
	std::vector<GuildBuff> Buffs;
};

struct GuildBuffItem
{
	int QuestID;
	int curAmount;
};

struct GuildRaidLevel
{
	int ReqAmount;
	int MobIndex;
	int Reward;
	int MinPlayers;
	int Time;
};

struct GuildTopDonator
{
	std::string name;
	int PID;
	int Amount;
};

struct SuitStat
{
	int Type;
	int Multiply;
};

struct SkillLearn
{
	std::vector<int> Levels;
	std::vector<int> Specialties;
};

struct QuestEx
{
	std::vector<int> Items;
	std::vector<int> SAmounts;
	std::vector<int> Required;
	std::vector<int> Amounts;
	int MinLvl;
	int MaxLvl;
	int html;
	int Save;
};

struct MLMReward
{
	int Type;
	int Class;
	int Index;
	int Prefix;
	int Amount;
	int Info;
	int Attack;
	int Magic;
	int Toa;
	int Upgrade;
	int Defense;
	int Evasion;
	int Endurance;
};

struct PacketEncryption
{
	int Key;
	int Time;
};

struct Poll
{
	int Quest;
	int FlagMin;
	int FlagMax;
	std::string Question;
	int HTML;
	int Start;
	int End;
};

struct QuestLevel
{
	int LevelMin;
	int LevelMax;
};

struct Point
{
	int X;
	int Y;
	int Z;
};

struct ItemLimitConf
{
	int Usage;
	int Time;

	ItemLimitConf() {
		Usage = 0;
		Time = 0;
	}
};

struct PVEWeaponsS
{
	int index;
};

struct NecklaceBuff
{
	int Dmg;
	int CritChance;
	int Duration;
	int Cooldown;
	std::string Effect;
};

struct BeltBuff
{
	int HP;
	int Duration;
	int Cooldown;
	std::string Effect;
};

struct SVParticipant
{
	int Specialty;
	int Level;
	std::string Name;
};

struct MiningItem
{
	int NumItems;
	std::vector<ItemStruct> Items;
};

struct F10EXP
{
	signed __int64 Exp;
	int Gap;
	int Mult;
	int RID;
};

struct RectLevel
{
	RECT rectangle;
	int LevelMin;
	int LevelMax;
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

struct Combinator
{
	int Index;
	int Bound;
};

struct SinSpawner
{
	int Index;
	int Amount;
	int X;
	int Y;
};

struct MasterEnchanting
{
	int IndexIn;
	int MaterialUsed;
	int IndexOut;
	int Rate;
};

struct EmokCertConf
{
	int Time;
	int EXP;
};

struct BossEXPMsg
{
	int Index;
	int X;
	int Y;
	int Amount;
	std::string message;
};

struct Reborn
{
	std::string NameTag;
	int NamePad;
	int MinLvl;
	int ResetLevel;
	int RewardID;
};

struct RbPenalty
{
	int rbIndex;
	int rbPenalty;
};
struct RentQuest
{
	int ReqItem;
	int Amount;
	int Index;
	int Time;
};

struct ItemExchange
{
	int Material;
	int MaterialAmount;
	int ItemOut;
};

static int ShamanBuffs[] = { 401, 403, 407, 409, 413 };
unsigned __int64 _ExpTable[312]; // Definition of the global variable
Poll pollAsk;
time_t uptimestart; 
int GuildWinnerCW = 0, AllyWinnerCW = 0, WarEndTime = 0;
int CryptKey = 0;
std::string ConfigCheckDB1, ConfigCheckDB2;
int firstDig = 0;
int BofConfigRead = 0, dgConfigRead = 0, insanityRead = 0, qigongRead = 0, ImpConfigRead = 0, ScaniaLicense = 0, NailKill = 0;
time_t notices,timeReloading;
volatile LONG OnlinePlayers = 0;
volatile LONG PlayerLevelNotice = 0;
volatile LONG MonsterReloaded = 0;
volatile LONG auctionItemsNum = 0;
int HuntingID = 0, CWGID = 0 ;
int NPCID = 0;
std::string WCWinner = "None";
std::string HuntingName = "", CWGuildName = "";
int myc = 0;
int DNPCEDailyLimit = 0, DNPCECollectedTotalItem = 0, DNPCELeftTime = 0, test = 0;
int NPCEDailyLimit = 0, NPCECollectedTotalItem = 0, NPCELeftTime = 0; char ItemShopPacket[9000] = {0};
//char AuctionPacket[9000] = { 0 };
int AuctionAmount = 0, AuctionSize = 0;
char FakePlayerPacket[14];
#define HIDWORD(l) ((DWORD)(((DWORDLONG)(l)>>32)&0xFFFFFFFF))
std::string thisServerName = "";
Lock itemStat = Lock();
Lock npcLock = Lock();
Lock summonLock = Lock();
Lock itemBet = Lock();
Lock auctionLock = Lock();
Lock auctionVecLock = Lock();
Lock offsetLock = Lock();
Lock playerQuestLock = Lock();
Lock petLifeLock = Lock();
Lock itemLockLock = Lock();
Lock userLock = Lock();
Lock duelLock = Lock();
Lock duelShowLock = Lock();
Lock monsterKillLock = Lock();
Lock blockLock = Lock();
Lock packetLock = Lock();
Lock rewardLock = Lock();

std::vector<AreaExpItem> AreasExpItems; // declare a vector to hold the areas

std::map<int, int> HighGradeBof;
std::map<int, int> HighGradeImperial;
//std::unordered_map<int, std::pair<std::string, int>> EmoteSystem;
std::unordered_map<int, std::string> EmoteSystem;
std::unordered_map<int, MissionInfo> MissionQuests;

std::set<int> BoundAllowedItems;
std::map<int, std::vector<MLMReward>> MLMRewards;
std::map<int, Combinator> Combinators;
std::map<int, Items> RentQuests;
std::map<int, EmokCertConf> EmokCerts;
std::map<int, int> PlayerVsPlayerDmg;
std::vector<SinSpawner> SinSpawners;

ConcurrentMap<int, int> RestoredIIDs;

ConcurrentMap<long, std::vector<GuildBuff>> ActiveGuildBuffs;
ConcurrentMap<int, std::vector<GuildTopDonator>> GuildTopDonatorList;
std::map<int, GuildBuffQuest> GuildBuffQuests;
RegistrationMap<long, int> GuildBuffItems;
std::vector<int> GuildBuffs;
RegistrationMap<int, int> GuildRaidItems;
ConcurrentMap<int, SVParticipant> SVParticipantsRed;
ConcurrentMap<int, SVParticipant> SVParticipantsBlue;
ConcurrentMap<int, int> ChannelItems;
std::map<int, GuildRaidLevel> GuildRaidLevels;
std::map<int, NecklaceBuff> NecklaceBuffs;
std::map<int, BeltBuff> BeltBuffs;
std::map<int, ConfigBuff> BuffCheck;
std::map<int, BuffMaker> BuffMakerCheck;
std::map<int, BuffDisable> BuffDisableCheck;
std::map<std::string, ShoutData> CustomShouts;
std::map<std::string, ShoutData> CustomHouse;
std::unordered_map<int, int> PlayerMissionProgress;
std::unordered_map<char, int> npcMap;
std::map<int, ItemExchange> ItemExchanges;
std::map<int, Reborn> Reborns;
std::map<int, RbPenalty> RebornsPenalty;

std::map<int, int> FatalDmg;
std::map<int, MSkill> MSkills;
std::map<int, std::vector<int>> MonsterSkills;
std::map<int, int> CostumeEffects;
std::map<int, int> CostWeaponsEffects;
ConcurrentMap<int, ConcurrentSet<int>> EventMapsRegistration;
std::map<int, eventMap> EventMapsQuests;
ConcurrentMap<int, int> LoginAttempts;
ConcurrentSet<int> EventMapsQuestsOn;
ConcurrentSet<int> EventMaps;
ConcurrentMap<long, int> MonsterDamage;
ConcurrentMap<int, int> EventMapsOn;
ConcurrentMap<int, int> InstancesCD;
ConcurrentMap<int, eventMapMonster> EventMapsMobsOn;
ConcurrentMap<int, int> ObjectChannels;
std::vector<Point> JailCoords;
std::map<int, Reward> Rewards;
std::map<int, F10EXP> F10EXPs;
std::map<int, F10EXP> MautEXPs;
std::map<int, F10EXP> BossEXPs;
std::map<int, BossEXPMsg> BossEXPMsgs;
ConcurrentMap<int, SendCreate> SendCreatePlayer;
RegistrationMap<int,int> SummonQuestRegistration;
RegistrationMap<int, int> EventQuests;
SystemRegistration<int> Lottery;
SystemRegistration<int> XLottery;
ConcurrentMap<int, ConcurrentMap<long int, int>> BuffList;
std::map<int, int> MobPets;
std::set<int> PKIgnoreItem;
ConcurrentMap<int, std::vector<DuelRegistre>> DuelRegistrationList;
ConcurrentMap<int, std::string> DuelNames;
std::vector<int> DuelUnbuff;
ConcurrentMap<int, int> MonsterDisappear;
ConcurrentMap<int, FakePlayers_> FakePlayers;
ConcurrentMap<int, FakeItems_> FakeItems;
ConcurrentMap<std::string, int> FakeNames;
ConcurrentSet<int> DailyLoginLimits;
std::map<int, StickBuff>BuffScale;

std::map<int, SecretBlackSmithSkill>SecretBlackSmith;
std::map<int, SwapMineral>MakeMinerals;
std::map<int, SwapMineral>MakeChange;
std::map<int, MakeItem_>MakeItem;
//std::map<int, std::map<int,int>>DailyQuestMonsterKilled;
std::set<int> InvCheck;
std::set<int> PKDropEnable;
std::map<int, SoulPocketConfig> SoulPockets;
std::map<int, MiningItem> MiningItems;

std::map<int, PartyReward> PartyRewards;
std::map<int, PartyReg> PTEnabled;
std::map<std::string, PartyReg> PTCommands;
std::map<std::string, std::vector<PartyReg>> PartyTimer;
std::vector<PartyReg> PartyRegistrations;
std::map<int, PartyBattle> CurPartys;
std::set<int> MQuest;
std::map<int, QuestEx> QuestExs;
std::map<int, std::string> EventTimer;
std::map<int, std::string> EventMapsTimer;
std::map<int, std::string> EndTimer;
std::map<int, MSummonConfig> SummonQuest;
ConcurrentMap<int, MSummonedConfig> SummonedQuest;
std::map<int, ZProtection> ugog;
ConcurrentSet<std::string> DisablePM;
std::set<int> ugCheck;
std::set<int> ogCheck;
std::map<int, CreateMonsterPet> MonsterPet;
std::map<int, int> ItemQuest;
std::map<int, IWebs> ItemWebsite;
std::map<int, int> ItemReward;
std::map<int, std::string> QuestWebsite;
std::map<std::string, std::string> Tracker;
std::map<int, int> NewItemType;
std::map<int,Winners> FinalsWinners;
std::map<int, std::vector<Items>> Boxes;
std::map<int, std::vector<Items>> StarterItems;
std::map<int, StarterClass> Starters;
std::map<int, InitSwap> InitPetSwap;
std::map<int, std::vector<int>> QuestRentItem;
ConcurrentMap<int,PlayerFight> CupRegistration;
ConcurrentMap<int, Vote> PlayerVote;
ConcurrentMap<uint32_t, int> VoteList;
std::map<int, std::vector<RectLevel>> RectArea;
std::map<int, std::vector<AFKCheck>> AFKMap;
std::map<int, int> EnchantCount;
std::set<int> Macro;
std::map<int, MasterEnchanting> MasterEnchant;
std::map<int, RidingCollection> RidingCollections;
std::map<int, int> RidingCollectionIndex;
std::map<int, ItemTime> TimedItems;
std::map<int, RentalExtend> RentalItems;
std::map<int, ItemBuff> BuffedItems;
std::map<int, ItemMss> MSS;
std::map<int, int> PacketSpamConf;
ConcurrentMap<int, int> EmblemDropped;
ConcurrentMap<int, int> PacketSpam;
ConcurrentMap<int,PacketCheck> PacketDelay;
std::map<int,WCGroups> CupOfKal;
std::map<int,Fights> FirstFight;
std::map<int,Fights> SecondFight;
std::map<int, Fights> ThirdFight;
std::map<int, std::vector<BetTrade>> BetItems;
ConcurrentSet<std::string> RewardLimit;
ConcurrentMap<uint32_t, int> MiningLimit;
ConcurrentMap<uint32_t, int> FishingLimit;
ConcurrentMap<uint32_t, int> ShopLimit;
std::map<int,std::vector<ChanceItem>> FishingList;
std::vector<ChanceItem> F10Items;
std::vector<ChanceItem> MautItem;
std::vector<ChanceItem> BossExpItem;
std::vector<ChanceItem> MonstersItem;

SystemRegistration<int> RaidSystem;
std::map<int, OldStats> PlayerStats;
std::map<int, int> NPCIDs;
std::map<int, Poll> Polls;
std::map<int, Poll> PollTimer;
ConcurrentMap<std::string, std::set<int>> PollVotes;
ConcurrentMap<int, int> PollVoteAmount;
std::map<int,SingleConfigBuffer> SingleBufferCheck;
std::set<int> SinDisable;
std::map<int, std::set<int>> DisableSkill;
std::vector<int> MD5FileChecker;
std::map<int, std::set<int>> DisableSkillFile;
std::set<int> RidingDisableSkill;
std::map<int, CItemUsed> ItemUsed;
std::map<int, CItemTasty> ItemTasty;
std::map<int, CItemTasty> ItemExpansion;
std::map<int, CItemTasty> ItemHpDef;
std::map<int, CItemTasty> ItemScrolls;
std::map<int, CItemTasty> ItemBuffSrv;

std::map<int, ItemLimit> ItemLimits;
std::map<int, ItemQuestRepeat> ItemQuestRepeats;
ConcurrentMap<int, ItemLimitConf> ItemLimitUsage;
std::map<int, int> ItemNPC;
std::map<int, SummonNPC> ItemNPCSummoned;
std::map<int, SummonNPC> NPCSummoned;
std::map<int, CAutoNotice> AutoNotices;
std::map<int, CMonstersBuff> MonstersBuff;
std::map<int, CMonstersBuff> RMonstersBuff;
std::map<int, CQuestsNotice> QuestsNotice;
std::map<int, CQuestsNotice> cQuestsNotice;
std::map<int, pRewards> F10EXPRewards;

std::map<int, CMonstersRewards> MonstersRewards;

std::set<int> QuestDisable;
std::set<int> QBattleEnable;
std::map<int, QuestTime> TimedQuest;
std::map<int, AreaQuest> AreaQuests;
std::set<int> TimedMaps;
ConcurrentMap<long, QuestTime> PlayerTimedQuest;
ConcurrentMap<long int, AuctionItem> AuctionItems;
std::vector<AuctionItem> AuctionVec;
std::map<int,Area> MapLvl;
std::map<int, ShoutsMaps> ShoutMap;

std::set<int> PacketBlock;
std::map<int,int> MD5Checks;
std::vector<MD5Type> MD5File;
std::map<int, QuestLevel> QuestLevels;
std::map<int, MD5Type> MD5MapsKCM;
std::map<int, MD5Type> MD5MapsOPL;
std::map<int, SkillDamage> SkillsDamage;
ConcurrentMap<int, UserInfo> User;
ConcurrentMap<int, int> SocketInfos;
ConcurrentMap<int, int> SocketPacket;
ConcurrentMap<int, PacketEncryption> SocketNewInfos;
ConcurrentSet<uint32_t> BlockList;
std::set<int> SkillsPVP;
std::map<int,int> WCDamage;
std::map<int,WCRew> WCRewards;
std::map<int, AreaMax> MapMax;
std::set<int> UnGap;
std::set<int> UnAggro;
std::set<int> UnBreak;
std::vector<int> LawlessEXP;
std::set<int> UnChannel;
std::set<int> ChannelMaps;
std::set<int> UnReload;
std::set<int> AntiKs;
std::map<int, PVEWeaponsS> PVEWeapon;

std::set<std::string> Filter;
std::map<int, Restriction> Restrictions;
std::map<int, Restriction> HWIDRestrictions;

std::map<int, HaninRate> HaninLow;
std::map<int, HaninRate> HaninMiddle;
std::map<int, HaninRate> HaninHigh;
std::map<int,CheckCalculations> PVPConfigCalculations;
std::map<int, SkillRangeConfig> CheckRangeConfig;
std::set<int> ItemDisable;
std::set<int> AuctionItemDisable;
ConcurrentMap<int,int> PlayerOffset;
std::map<__int16,ConfigItemShop> ItemShopCheck;
//std::map<__int64,ConfigPlayerQuest> PlayerQuest;
std::map<int, ConfigDailyQuest> DailyQuest;
std::map<int, std::vector<MonsterDailyQuest>> MonsterQuests;
std::map<int, std::vector<ConfigLevelReward>> LevelReward;
ConcurrentMap<int,ConfigMining> CheckMining;
std::map<int, int> GetItemStat;
ConcurrentSet<int> ItemStatDisable;
ConcurrentSet<int> ItemTimerDisable;
std::map<int,ConfigBuffer> BufferCheck;
std::map<int,ConfigRentArmor> RentArmor;
std::map<int, ConfigRentWeapon> RentWeapon;
std::map<int,CheckSkillBook> SkillBook;
std::map<int, CheckSkillBook> SkillDowngrade;
std::map<int,CheckConfigCooldown> CheckCooldownConfig;
std::map<int,CheckConfigEggCooldown> CheckEggCooldownConfig;
std::map<int,CheckCalculations> ConfigCalculations;
std::map<int,PimpConfig> CheckPimp;
std::map<int, std::vector<CheckSummonTimer>> SummonTimer;
std::map<std::string, std::vector<RGBNotice>> RGBAutoNotice;
std::map<std::string, int> CustomNotices;
std::map<std::string, int> AutoNoticesRGB;

ConcurrentMap<int, int> PetLifeCheck;
ConcurrentMap<std::string,std::string> Read2ndPwd;
std::set<int> UnBlob;
std::map<int, std::set<int>> StoreItems;
std::set<int> MixConfigPrefix;
std::map<int, int> MixConfigInfo;
std::map<int,std::string> MixConfigMsg;
SystemRegistration<int> BattlefieldRegistration;
ConcurrentMap<int, std::string> SufferingValleyRegistration;
SystemRegistration<int> SVGuild1;
SystemRegistration<int> SVGuild2;
SystemRegistration<int> TBRegistration;
ConcurrentSet<int> ScenarioRegistration;
std::set<int> SummonTrack;
std::vector<DKInfo> ScenarioGuild;
std::map<int, std::vector<AutoNoticeConf>> AutoCenterNotices;
std::vector<int> RShopItems;
std::vector<int> RShopAmounts;
std::map<int, double> LevelGap;
std::map<int, TrainingLvl> TrainingEXP;
std::map<int, ChanceItem> TrainingDrops;
std::map<int,int> HonorShop;
std::map<int, int> HonorIndex;
std::map<int, std::set<int>> SystemBlacklist;
SystemRegistration<int> F10Registration;
SystemRegistration<int> MautRegistration;
SystemRegistration<int> BanditsRegisteration;
SystemRegistration<int> BossEXPRegistration;
std::map<int,int> WeaponReplace;
SystemRegistration<int> CaptureRegistration;
std::map<int,int> WeaponReplaceIndex;
std::unordered_map<int, std::string> WeaponReplaceMsg;

//std::vector<int> HighestDamage;
std::set<int> WeaponReplacePrefix;
std::set<int> DisablePrefix;
std::map<int, int> ArmorPimpConfig;
std::map<int, int> PVEDamagePimp;
std::map<int, int> PVPDamagePimp;
std::map<int,std::string> ItemLockCheck;
std::map<int, ConfigPetTime> PetTime;
std::map<int, int> SoulPocketEffect;
std::map<int, SuitStat> SuitStats;
std::map<int, SkillLearn> SkillChecks;
std::map<int, DailyReward> DailyLogins;
std::map<int, TaskQ> TaskQuests;

ConcurrentSet<int> PlayerBlockCheck;
std::vector<int> ProtectLeaderList;
ConcurrentMap<int,std::string> ProtectLeaderName;
std::set<int> ProtectBlackList;
std::set<int> DestructingBlackList;
std::set<int> SVBlackList;
SystemRegistration<int> LastManRegistration;
//std::map<int, std::string> FriendsName;



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
#include "DirectoryReader.h"
#include "Lisans.h"
#include "ReadConfig.h"
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
#include "BlessingOfHealth.h"
#include "BlessingOfStrength.h"
#include "BlessingOfAgility.h"
#include "BlessingOfIntelligence.h"
#include "BlessingOfCriticalHit.h"
#include "RefiningWeapon.h"
#include "DefenseImprovement.h"
#include "SpeedUp.h"
#include "RefreshBuff.h"
#include "Mix.h"
#include "Reload.h"
#include "Channel.h"
#include "Lawless.h"
#include "Guild.h"
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
#include "PowerfulWideningWound.h"
#include "PerfectDefense.h"
#include "ProvocationOfBlow.h"
#include "SpinSlash.h"
#include "SwordDance.h"
#include "TherapeuticTouch.h"
#include "Blessing.h"
#include "Fireball.h"
#include "IceArrow.h"
#include "Icicle.h"
#include "Thunderbolt.h"
#include "VirulentArrow.h"
#include "ArrowExplosion.h"
#include "ArrowRain.h"
#include "CombativeSpirit.h"
#include "RevolveAttack.h"
#include "BloodSuction.h"
#include "EggThunderbolt.h"
#include "LifeAbsorption.h"
#include "LightningArrow.h"
#include "FlameInjection.h"
#include "CounterDamage.h"
#include "WhirlwindFeather.h"
#include "HighClassHiding.h"
#include "ShinRhoe.h"
#include "ZilPoong.h"
#include "Hiding.h"
#include "Behead.h"
#include "WrathOfHeaven.h"
#include "LightningSlash.h"
#include "ShadowSlash.h"
#include "SpinBlade.h"
#include "TwinBladeStrike.h"
#include "ArmorBreaker.h"
#include "SpinAttack.h"
#include "SuicidalBlow.h"
#include "FinalBlow.h"
#include "Assault.h"
#include "VitalStrike.h"
#include "AnkleAmputate.h"
#include "Rupture.h"
#include "FatalWound.h"
#include "Confusion.h"
#include "Stun.h"
#include "Strangle.h"
#include "DualShadow.h"
#include "ShoutOfDefense.h"
#include "TheBoomOfEarth.h"
#include "ShoutOfFightingSpirit.h"
#include "TheWaveOfEarth.h"
#include "WalkOnTheAir.h"
#include "OneHitStrike.h"
#include "ArrowsOfTheMaster.h"
#include "MassiveFire.h"
#include "SpiritOfTheArrows.h"
#include "Punishment.h"
#include "CriticalStrike.h"
#include "CriticalDiffusion.h"
#include "StrikeOfGod.h"
#include "DestroyingArmor.h"
#include "Bombing.h"
#include "Incapacitation.h"
#include "ReleasingTheEnergy.h"
#include "GhostKnife.h"
#include "GhostFlash.h"
#include "SoulShield.h"
#include "Wave.h"
#include "GhostWindow.h"
#include "MudRoom.h"
#include "ExecutiveDirector.h"
#include "TheSoulsPenance.h"
#include "JigukKing.h"
#include "JeungjangKing.h"
#include "AmplificationOfBlood.h"
#include "WaveOfEmperor.h"
#include "Entangling.h"
#include "SpearOfPain.h"
#include "JigukKingOfTaein.h"
#include "JeungjangKingOfTaein.h"
#include "SoulBlow.h"
#include "DrainBlood.h"
#include "MagicalExplosion.h"
#include "MentalBreakdown.h"
#include "Collapse.h"
#include "SixSouls.h"
#include "ExplodingSpirit.h"
#include "SpiritWave.h"
#include "Doggebi.h"
#include "RisingKing4th.h"
#include "Gangshin4th.h"
#include "SkillCalculation.h"
#include "Skill.h"
#include "EggSkill.h"
#include "SkillCheck.h"
#include "DropItem.h"
#include "WeaponPut.h"
#include "DefenseChangePrefix.h"
#include "WeaponChangePrefix.h"
#include "Revival.h"
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
//				DetourAttach(&(PVOID&)CSkill::ProtectSkill, ProtectSkill);
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
				DetourAttach(&(PVOID&)CItemWeapon::StorageIn, CItemWeaponStorageIn);
				DetourAttach(&(PVOID&)CItemDefense::StorageIn, CItemDefenseStorageIn);
				DetourAttach(&(PVOID&)CBase::Delete, CBaseDelete);
				DetourAttach(&(PVOID&)CNPCSiegeGun::Reply, SiegeGunReply);
				DetourAttach(&(PVOID&)CMonsterMagic::Create, CMonsterMagicCreate);
				DetourAttach(&(PVOID&)CPlayer::CheckBlock, CheckBlock);
				DetourAttach(&(PVOID&)CItem::CreateItem, MyCreateItem);
				DetourAttach(&(PVOID&)CItemGeneral::StorageIn, CItemGeneralStorageIn);
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
//			DetourDetach(&(PVOID&)CSkill::ProtectSkill, ProtectSkill);
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
			DetourDetach(&(PVOID&)CItemWeapon::StorageIn, CItemWeaponStorageIn);
			DetourDetach(&(PVOID&)CItemDefense::StorageIn, CItemDefenseStorageIn);
			DetourDetach(&(PVOID&)CBase::Delete, CBaseDelete);
			DetourDetach(&(PVOID&)CMonsterMagic::Create, CMonsterMagicCreate);
			DetourDetach(&(PVOID&)CPlayer::CheckBlock, CheckBlock);
			DetourDetach(&(PVOID&)CItemGeneral::StorageIn, CItemGeneralStorageIn);
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