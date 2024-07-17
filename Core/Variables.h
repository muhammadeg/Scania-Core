#ifndef VARIABLES_H
#define VARIABLES_H

#include <unordered_map>
#include <string>
#include <map>
#include <cstdint>
//#include "Lock.h"
#include "ConcurrentMap.h"
#include "ConcurrentSet.h"

enum TextColor
{
	TEXTCOLOR_GENERAL = RGB(255, 255, 255),
	TEXTCOLOR_INFOMSG = RGB(70, 227, 232),
	TEXTCOLOR_SHUTDOWN = RGB(240, 116, 15),
	TEXTCOLOR_ORANGE = RGB(255, 128, 64),
	TEXTCOLOR_BLUE = RGB(0, 128, 255),
	TEXTCOLOR_BLUELIGHT = RGB(0, 255, 255),
	TEXTCOLOR_YELLOW = RGB(255, 255, 128),
	TEXTCOLOR_RED = RGB(255, 0, 0),
	TEXTCOLOR_PARTY = RGB(210, 64, 0),
	TEXTCOLOR_GUILD = RGB(10, 255, 229),
	TEXTCOLOR_ALLIANCE = RGB(128, 128, 192),
	TEXTCOLOR_GREEN = RGB(0, 255, 0),
	TEXTCOLOR_DARKGREEN = RGB(0, 170, 0),
	TEXTCOLOR_FAILED = RGB(250, 210, 0),
	TEXTCOLOR_CLASSMATE = RGB(0, 128, 0),
	TEXTCOLOR_PUPIL = RGB(255, 128, 64),
	TEXTCOLOR_PINK = RGB(255, 155, 255),
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
struct ChanceItem {
	int Index;
	int Amount;
	int Chance;
};

struct SwapItem {
	int Index;
	int Chance;
	SwapItem(int nIndex, int nChance) {
		Index = nIndex;
		Chance = nChance;
	}
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

struct Area
{
	int level;
	int item;
	int type;
};

struct IWebs {
	std::string URL;
	int remove;
};

struct MD5Type
{
	std::string filename;
	std::string hash;
};

struct ZProtection
{
	int maxZ;
	int minZ;
};

struct AFKCheck
{
	RECT rectangle;
	int seconds;
};

struct SkillDamage
{
	std::string damage;
	std::string PVECrit;
	std::string PVPCrit;

	int PVE;
	int PVP;
	int Reduce;
	int AOE;
	int PVEDamage;
	int PVPDamage;

};
struct ItemTime
{
	int Time;
	int Wearable;
};
struct ItemBuff
{
	std::vector<Buffs> BuffList;
};

struct SBoxes
{
	std::vector<std::string> Rewards;
	std::vector<std::string> Amounts;

	int item;
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
struct WCReward
{
	int Index;
	int Amount;
};

struct WCRew
{
	std::vector<WCReward> RewardList;
};
struct CheckCalculations
{
	int Class;
	int Rate;
};

struct AutoNoticeConf {
	std::string Day;
	std::string Msg;
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

struct Msss
{
	int MobIndex;
	int Time;
	int Amount;
	int Public;
};

struct ItemMss
{
	std::vector<Msss> MonsterList;
};
struct CItemUsed
{
	int HTML;
	int Remove;
};
struct CAutoNotice
{
	int minutes;
	std::string msg;
	int color;

};
struct ConfigLevelReward
{
	std::vector<std::string> Indexes;
	std::vector<std::string> Amounts;
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
	int ID;
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
struct AreaMax
{
	int maxlevel;
	int type;
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
struct MakeItem_ {
	int item;
	std::string requireIndexs;
	std::string requireAmounts;
};
struct SwapMineral {
	std::string requires;
	std::string requireAmounts;
	std::string itemRewards;
	std::string itemAmounts;
	std::string chances;
};
struct CMonstersBuff
{
	int mobindex;
	int buffid;
	int buffgrade;

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
struct CheckSkillBook
{
	int Class;
	int Action;
	int UpgradeAmount;
	int UpgradeMax;
	int DowngradeAmount;
	int RewardPoints;
};

struct CheckConfigEggCooldown
{
	int EggCooldownConfig;
	int EggDelayConfig;
};
struct CheckConfigCooldown
{
	int CooldownConfig;
	int DelayConfig;
};
struct ConfigPetTime
{
	int Time;
	int Heal;
	int Pick;
	int Monster;
	int Speed;
	int Exp;
	int Egg;
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
struct SkillRangeConfig {
	int maxRange;
};

struct CommandLink {
	std::string Command;
	std::string Link;
};
struct SummonGuard {
	int guard;
	int amount;
	int hp;
	int boss;
};
struct BuffDisable
{
	int BuffDisableIndex;
	std::vector<std::string> BuffDisableID;
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
	std::vector<std::string> altBuff;
	int BuffDisableIndex;
	int BuffDisableID;
};
struct ConfigBuffer
{
	int Index;
	int Grade;
	int Delete;
	int Speed;
	int Limit;
	int cd;
};
struct ConfigTimeTalisman
{
	int prefix;
	int time;
	int itemindex;
};
struct Reward {
	std::vector<std::string> Indexes;
	std::vector<std::string> Amounts;
	int HonorPts;
	int RewardPts;
	signed __int64 EXP;
	int Level;
	int Progress;
	int Bound;
	int HTML;
	int HousePoints;
	std::string Notice;
};
struct DailyDuty {
	int quest;
	std::vector<std::string> NormalMob;
	std::vector<std::string> NormalAmount;
	std::vector<std::string> MiniBoss;
	std::vector<std::string> BossAmount;
	std::vector<std::string> InstanceD;
	std::vector<std::string> IMobAmount;
	int pLevel;
	int cooldown;

	//int Boxes;
	//int BoxAmount;

	int Reward;
};
struct MonsterDailyDuty {
	int Quest;
	int Index;
	int Amount;
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

struct Skills
{
	int Type;
	DWORD Time;
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
	int currentmission;
	int teleportMap;
	int teleportX;
	int teleportY;
	int Monster;
	int Item;
	std::vector<std::string> Items;
	std::vector<std::string> Amounts;
	int itemAmount;
	int Amount;
	int rewardID;
	int progress;
};

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

struct ItemExchange
{
	int Material;
	int MaterialAmount;
	int ItemOut;
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
struct CItemTasty
{
	int index;
	int remove;
	int level;
	int Time;
	int prevent;
	std::vector<std::string> buffs;
	std::vector<std::string> values;
	std::vector<std::string> cancelBuff;
	std::vector<std::string> removeIcon;
	int addIcon;

};
struct ItemLimit
{
	int Usage;
	int Time;
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
struct Point
{
	int X;
	int Y;
	int Z;
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
	int Type;
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

struct PartyReg {
	int PID;
	std::string Day;
	std::string Time;
	int PVPArena;
	int PartySize;
	int ArenaTime;
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
	int FlagTime;
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
struct QuestLevel
{
	int LevelMin;
	int LevelMax;
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

struct EmokCertConf
{
	int Time;
	int EXP;
};
struct SMultiple {
	int Multiple;
};

struct SinSpawner
{
	int Index;
	int Amount;
	int X;
	int Y;
};
struct Certificates {
	int itemIndex;
	int Map;
	int Time;
	int Exp;
	int SBKey;
	int SBMsg;
};
struct PerfectParty {
	int PartySize;
	int Exp;
	int SBKey;
	int SBMsg;
};
struct CertificatesPlayer {
	int Map;
	int Time;
	int Day;
	unsigned __int64 Exp;
};
struct Combinator
{
	int Index;
	int Bound;
};
struct SingleConfigBuffer
{
	int Index;
	int Grade;
	int Delete;
	int Type;
};

struct SoulPocketConfig
{
	int Amount;
	int Refill;
	int Max;
};
struct ItemStruct {
	int Index;
	int Amount;
};
struct MiningItem
{
	int NumItems;
	std::vector<ItemStruct> Items;
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

struct eventMap {
	std::vector<std::string> monsters;
	std::vector<std::string> amounts;
	std::vector<std::string> Reward;
	std::string Name;
	int Duration;
	int Lapse;
	std::vector<std::string> X;
	std::vector<std::string> Y;
	std::vector<std::string> Gate;
	std::vector<std::string> GateX;
	std::vector<std::string> GateY;

	int LvlMin;
	int LvlMax;
	int Quest;
	int TX;
	int TY;
	std::vector<std::string> ReqItemx;
	std::vector<std::string> ReqAmountx;
	std::vector<std::string> ReqItemM;
	std::vector<std::string> ReqAmountM;

	ConcurrentSet<int> Maps;
	int Cooldown;
	int PTSize;
	int Type;
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
struct ShoutData {
	COLORREF color;
	int index;
	int remove;

	ShoutData() : color(0), index(0), remove(0) {} // Default constructor

	ShoutData(COLORREF c, int i, int r) : color(c), index(i), remove(r) {}
};
struct RGBNotice
{
	std::string day;
	std::string msg;
	int Color;
};

struct CMonstersRewards
{
	int mobindex;
	int rewardid;
	int randomindex;
	int itemamount;
	int pickchance;
	int Range;

};

struct RectLevel
{
	RECT rectangle;
	int LevelMin;
	int LevelMax;
};
struct PimpConfig
{
	int Prefix;
	int GetA;
	int GetM;
	int GetTOA;
	int GetUpg;
};
struct ItemsEffects
{
	int index;
	int Class;
	std::string Effect;
	int effectTime;
};
struct PVEWeaponsS {
	int index;
};
struct HaninRate
{
	int Min;
	int Max;
};
struct Reborn
{
	std::string NameTag;
	int NamePad;
	int MinLvl;
	int ResetLevel;
	int RewardID;
	int sbKey;
	int sbMsg;
	int Map;
	int X;
	int Y;
};

struct RbGear {
	int Level;
	int Reborn;
};
struct RbPenalty
{
	int rbIndex;
	int rbPenalty;
};

struct RbQuest
{
	int rbIndex;
	int rbQuest;
	int rbQFlag;
};
struct RentQuest
{
	int ReqItem;
	int Amount;
	int Index;
	int Time;
};

struct GuildBuff
{
	int BuffID;
	int Time;
	int Value;
	int SBName;
	int SBKey;
};

struct GuildBuffItem
{
	int QuestID;
	int curAmount;
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
struct RidingCollection {
	std::vector<int> Indexes;
	int Stat;
	int Rate;
};
struct MasterEnchanting
{
	int IndexIn;
	int MaterialUsed;
	int IndexOut;
	int Rate;
};
struct TrainingLvl
{
	int EXP;
	int Drop;
};

struct GuildRaidLevel
{
	int ReqAmount;
	int MobIndex;
	int Reward;
	int MinPlayers;
	int Time;
};
struct F10EXP
{
	signed __int64 Exp;
	int Gap;
	int Mult;
	int RID;
};
struct BossEXPMsg
{
	int Index;
	int X;
	int Y;
	int Amount;
	std::string message;
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
struct RentalExtend
{
	int Time;
	int Price;
};

struct SecretBlackSmithSkill {
	std::string requires;
	std::string requireAmounts;
	std::string rewards;
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
struct DailyReward
{
	std::string Items;
	std::string Amount;
	int Honor;
	int Reward;
	int HTML;
	int ClaimHTML;
};
struct SkillLearn
{
	std::vector<int> Levels;
	std::vector<int> Specialties;
};
struct SuitStat
{
	int Type;
	int Multiply;
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
struct ItemQuestRepeat {
	int Permanent;
	std::vector<int> Quests;
};
struct MonsterDailyQuest {
	int Quest;
	int Amount;
	int MainIndex;
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

namespace SufferingValley
{
	extern	bool Active;
	extern int Time;
	extern std::string FirstGuild;
	extern std::string SecondGuild;
	extern int GuildFirst;
	extern int GuildSecond;
	extern int RedScore;
	extern int BlueScore;
	extern int Round;
	extern bool BlueOpened;
	extern bool RedOpened;
	extern bool Selection;
}
struct DKInfo
{
	int GID;
	std::string Name;
};

namespace DuelTournament
{
	extern	bool Active;
	extern	int RoundTime;
	extern	int RedScore;
	extern	int BlueScore;
	extern	int RegisterAmount;
	extern	int Delay;
	extern	bool SelectPlayers;
	extern	int FirstPlayer;
	extern	int SecondPlayer;
}

namespace Scenario
{
	extern int Time;
	extern int RedScore;
	extern int BlueScore;
	extern int BlueTeamSeal;
	extern int RedTeamSeal;
	extern int BlueTeamTowerCount;
	extern int RedTeamTowerCount;
	extern bool Active;
	extern int RegisterAmount;
	extern std::string FirstGuild;
	extern std::string SecondGuild;
	extern int GuildFirst;
	extern int GuildSecond;
	extern bool Selection;
}

namespace Protect32
{
	extern int Time;
	extern bool Active;
	extern std::string FirstGuild;
	extern std::string SecondGuild;
	extern int GuildFirst;
	extern int GuildSecond;
	extern int Prayer;
	extern int RedScore;
	extern int BlueScore;
	extern int RedWin;
	extern int BlueWin;
	extern int Winner;
	extern int Round;
	extern int BluePrayerTime;
	extern int RedPrayerTime;
	extern bool BlueOpened;
	extern bool RedOpened;
	extern bool Selection;
}

// Maps Start //
extern ConcurrentMap<int, std::string> SufferingValleyRegistration;
extern ConcurrentMap<int, ConcurrentSet<int>> EventMapsRegistration;
extern ConcurrentMap<int, std::vector<DuelRegistre>> DuelRegistrationList;
extern ConcurrentMap<int, std::string> DuelNames;
extern ConcurrentMap<int, int> PollVoteAmount;
extern ConcurrentMap<int, std::string> ProtectLeaderName;
extern ConcurrentMap<std::string, ConcurrentSet<int>> PollVotes;
extern ConcurrentMap<int, ItemLimitConf> ItemLimitUsage;
extern ConcurrentMap<long, QuestTime> PlayerTimedQuest;
extern ConcurrentMap<int, MSummonedConfig> SummonedQuest;
extern ConcurrentMap<int, FakePlayers_> FakePlayers;
extern ConcurrentMap<int, FakeItems_> FakeItems;
extern ConcurrentMap<std::string, int> FakeNames;
extern ConcurrentMap<int, int> PacketSpam;
extern ConcurrentMap<int, std::vector<MonsterDailyQuest>> MonsterQuests;
extern ConcurrentMap<int, std::vector<MonsterDailyDuty>> DutyMonsterQuests;
extern ConcurrentMap<int, ItemQuestRepeat> ItemQuestRepeats;
extern ConcurrentMap<int, MSkill> MSkills;
extern ConcurrentMap<int, std::vector<int>> MonsterSkills;
extern ConcurrentMap<int, TaskQ> TaskQuests;
extern ConcurrentMap<int, QuestEx> QuestExs;
extern ConcurrentMap<int, SuitStat> SuitStats;
extern ConcurrentMap<int, SkillLearn> SkillChecks;
extern ConcurrentMap<int, DailyReward> DailyLogins;
extern ConcurrentMap<int, std::vector<MLMReward>> MLMRewards;
extern ConcurrentMap<int, SecretBlackSmithSkill>SecretBlackSmith;
extern ConcurrentMap<int, RentalExtend> RentalItems;
extern ConcurrentMap<int, ConfigRentArmor> RentArmor;
extern ConcurrentMap<int, ConfigRentWeapon> RentWeapon;
extern ConcurrentMap<int, Items> RentQuests;
extern ConcurrentMap<int, std::vector<int>> QuestRentItem;
extern ConcurrentMap<int, int> HonorShop;
extern ConcurrentMap<int, int> HonorIndex;
extern ConcurrentMap<int, BossEXPMsg> BossEXPMsgs;
extern ConcurrentMap<int, F10EXP> F10EXPs;
extern ConcurrentMap<int, F10EXP> MautEXPs;
extern ConcurrentMap<int, F10EXP> BossEXPs;
extern ConcurrentMap<int, GuildRaidLevel> GuildRaidLevels;
extern ConcurrentMap<int, TrainingLvl> TrainingEXP;
extern ConcurrentMap<int, ChanceItem> TrainingDrops;
extern ConcurrentMap<int, MasterEnchanting> MasterEnchant;
extern ConcurrentMap<int, int> RidingCollectionIndex;
extern ConcurrentMap<int, int> EnchantCount;
extern ConcurrentMap<int, RidingCollection> RidingCollections;
extern ConcurrentMap<int, GuildBuffQuest> GuildBuffQuests;
extern ConcurrentMap<int, Reborn> Reborns;
extern ConcurrentMap<int, RbPenalty> RebornsPenalty;
extern ConcurrentMap<int, RbPenalty> NonRebornsPenalty;
extern ConcurrentMap<int, RbGear> RebornGear;
extern ConcurrentMap<int, RbQuest> RebornsMaps;
extern ConcurrentMap<int, double> LevelGap;
extern ConcurrentMap<int, HaninRate> HaninLow;
extern ConcurrentMap<int, HaninRate> HaninMiddle;
extern ConcurrentMap<int, HaninRate> HaninHigh;
extern ConcurrentMap<int, ItemsEffects> EquipEffects;
extern ConcurrentMap<int, PVEWeaponsS> PVEWeapon;
extern ConcurrentMap<int, int> MixConfigInfo;
extern ConcurrentMap<int, std::string> MixConfigMsg;
extern ConcurrentMap<int, PimpConfig> CheckPimp;
extern ConcurrentMap<int, int> ArmorPimpConfig;
extern ConcurrentMap<int, int> PVEDamagePimp;
extern ConcurrentMap<int, int> PVPDamagePimp;
extern ConcurrentMap<int, std::vector<RectLevel>> RectArea;
extern ConcurrentMap<int, CMonstersRewards> MonstersRewards;
extern ConcurrentMap<int, CQuestsNotice> cQuestsNotice;
extern ConcurrentMap<int, std::vector<ConfigLevelReward>> PremiumPass;
extern ConcurrentMap<int, ConcurrentSet<int>> StoreItems;
extern ConcurrentMap<int, Restriction> HWIDRestrictions;
extern ConcurrentMap<std::string, ShoutData> CustomHouse;
extern ConcurrentMap<std::string, int> CustomNotices;
extern ConcurrentMap<std::string, ShoutData> CustomShouts;
extern ConcurrentMap<std::string, std::vector<RGBNotice>> RGBAutoNotice;
extern ConcurrentMap<int, Combinator> Combinators;
extern ConcurrentMap<int, PerfectParty> My_PerfectParty;
extern ConcurrentMap<int, Certificates> AreaCert;
extern ConcurrentMap<int, Certificates> AreaCertMap;
extern ConcurrentMap<int, eventMap> EventMapsQuests;
extern ConcurrentMap<int, Poll> Polls;
extern ConcurrentMap<int, Poll> PollTimer;
extern ConcurrentMap<int, MiningItem> MiningItems;
extern ConcurrentMap<int, SoulPocketConfig> SoulPockets;
extern ConcurrentMap<int, int> SoulPocketEffect;
extern ConcurrentMap<int, SingleConfigBuffer> SingleBufferCheck;
extern ConcurrentMap<int, MSummonConfig> SummonQuest;
extern ConcurrentMap<int, SMultiple> EXPMultipliers;
extern ConcurrentMap<int, EmokCertConf> EmokCerts;
extern ConcurrentMap<int, ConcurrentSet<int>> SystemBlacklist;
extern ConcurrentMap<int, int> FatalDmg;
extern ConcurrentMap<int, AreaQuest> AreaQuests;
extern ConcurrentMap<int, QuestTime> TimedQuest;
extern ConcurrentMap<int, int> PlayerVsPlayerDmg;
extern ConcurrentMap<int, QuestLevel> QuestLevels;
extern ConcurrentMap<int, PartyReward> PartyRewards;
extern ConcurrentMap<int, PartyReg> PTEnabled;
extern ConcurrentMap<std::string, PartyReg> PTCommands;
extern ConcurrentMap<std::string, std::vector<PartyReg>> PartyTimer;
extern ConcurrentMap<int, PartyBattle> CurPartys;
extern ConcurrentMap<int, std::string> EventTimer;
extern ConcurrentMap<int, std::string> EventMapsTimer;
extern ConcurrentMap<int, std::string> EndTimer;
extern ConcurrentMap<int, std::vector<Items>> StarterItems;
extern ConcurrentMap<int, StarterClass> Starters;
extern ConcurrentMap<int, NecklaceBuff> NecklaceBuffs;
extern ConcurrentMap<int, BeltBuff> BeltBuffs;
extern std::map<int, SummonNPC> ItemNPCSummoned;
extern ConcurrentMap<int, int> ItemReward;
extern ConcurrentMap<int, ItemLimit> ItemLimits;
extern ConcurrentMap<int, int> ItemNPC;
extern ConcurrentMap<int, CItemTasty> ItemTasty;
extern ConcurrentMap<int, CItemTasty> ItemHpDef;
extern ConcurrentMap<int, CItemTasty> ItemScrolls;
extern ConcurrentMap<int, CItemTasty> ItemExpansion;
extern ConcurrentMap<int, CItemTasty> ItemBuffSrv;
extern ConcurrentMap<int, OldStats> PlayerStats;
extern ConcurrentMap<int, InitSwap> InitPetSwap;
extern ConcurrentMap<int, ItemExchange> ItemExchanges;
extern ConcurrentMap<int, int> MobPets;
extern ConcurrentMap<int, ConfigBuff> BuffCheck;
extern ConcurrentMap<int, AreaExpItem> AreasExpItems;
extern ConcurrentMap<__int16, ConfigItemShop> ItemShopCheck;
extern ConcurrentMap<int, CreateMonsterPet> MonsterPet;
extern ConcurrentMap<int, std::vector<ChanceItem>> FishingList;
extern ConcurrentMap<int, IWebs> ItemWebsite;
extern ConcurrentMap<int, ZProtection> ugog;
extern ConcurrentMap<int, SkillDamage> SkillsDamage;
extern ConcurrentMap<int, ItemTime> TimedItems;
extern ConcurrentMap<int, ItemBuff> BuffedItems;
extern ConcurrentMap<int, SBoxes> Boxes;
extern ConcurrentMap<int, WCRew> WCRewards;
extern ConcurrentMap<int, int> WeaponReplaceIndex;
extern ConcurrentMap<int, int> WeaponReplace;
extern ConcurrentMap<int, CheckCalculations> PVPConfigCalculations;
extern ConcurrentMap<int, CheckCalculations> ConfigCalculations;
extern ConcurrentMap<int, std::vector<AutoNoticeConf>> AutoCenterNotices;
extern ConcurrentMap<int, std::vector<CheckSummonTimer>> SummonTimer;
extern ConcurrentMap<int, std::vector<AFKCheck>> AFKMap;
extern ConcurrentMap<int, ItemMss> MSS;
extern ConcurrentMap<int, CItemUsed> ItemUsed;
extern ConcurrentMap<int, int> ItemQuest;
extern ConcurrentMap<int, CAutoNotice> AutoNotices;
extern ConcurrentMap<int, Area> MapLvl;
extern ConcurrentMap<int, std::vector<ConfigLevelReward>> LevelReward;
extern ConcurrentMap<int, ConfigDailyQuest> DailyQuest;
extern ConcurrentMap<int, ConcurrentSet<int>> DisableSkill;
extern ConcurrentMap<int, AreaMax> MapMax;
extern ConcurrentMap<int, int> PacketSpamConf;
extern ConcurrentMap<std::string, std::string> Tracker;
extern ConcurrentMap<int, Restriction> Restrictions;
extern ConcurrentMap<int, MakeItem_>MakeItem;
extern ConcurrentMap<int, SwapMineral>MakeChange;
extern ConcurrentMap<int, SwapMineral>MakeMinerals;
extern ConcurrentMap<int, ConcurrentSet<int>> DisableSkillFile;
extern ConcurrentMap<int, CMonstersBuff> MonstersBuff;
extern ConcurrentMap<int, CMonstersBuff> RMonstersBuff;
extern ConcurrentMap<int, CQuestsNotice> QuestsNotice;
extern ConcurrentMap<int, CheckSkillBook> SkillBook;
extern ConcurrentMap<int, CheckSkillBook> SkillDowngrade;
extern ConcurrentMap<int, CheckConfigEggCooldown> CheckEggCooldownConfig;
extern ConcurrentMap<int, CheckConfigCooldown> CheckCooldownConfig;
extern ConcurrentMap<int, ConfigPetTime> PetTime;
extern ConcurrentMap<int, SkillRangeConfig> CheckRangeConfig;
extern ConcurrentMap<int, std::string> QuestWebsite;
extern ConcurrentMap<std::string, CommandLink> CustomCommands;
extern ConcurrentMap<int, SummonGuard> SGuard;
extern ConcurrentMap<int, BuffDisable> BuffDisableCheck;
extern ConcurrentMap<int, BuffDisable> BuffRemoveCheck;
extern ConcurrentMap<int, ConfigBuffer> BufferCheck;
extern ConcurrentMap<int, BuffMaker> BuffMakerCheck;
extern ConcurrentMap<int, int> HighGradeBof;
extern ConcurrentMap<int, int> HighGradeImperial;
extern ConcurrentMap<int, std::vector<ConfigLevelReward>> BattlepassReward;
extern ConcurrentMap<int, ConfigTimeTalisman> NormalPetTalisman;
extern ConcurrentMap<int, ConfigTimeTalisman> MonsterPetTalisman;
extern ConcurrentMap<int, ConfigTimeTalisman> CostumeTalisman;
extern ConcurrentMap<int, ConfigTimeTalisman> SkinTalisman;
extern ConcurrentMap<int, Reward> Rewards;

// Maps End //

// Set Start //
extern ConcurrentSet<int> PlayerBlockCheck;
extern ConcurrentSet<int> ScenarioRegistration;
extern ConcurrentSet<int> SVBlackList;
extern ConcurrentSet<int> DestructingBlackList;
extern ConcurrentSet<int> ProtectBlackList;
extern ConcurrentSet<int> DisablePrefix;
extern ConcurrentSet<int> SummonTrack;
extern ConcurrentSet<int> MixConfigPrefix;
extern ConcurrentSet<int> MQuest;
extern ConcurrentSet<int> EventMaps;
extern ConcurrentSet<int> PKDropEnable;
extern ConcurrentSet<int> UnBreak;
extern ConcurrentSet<int> UnAggro;
extern ConcurrentSet<int> UnChannel;
extern ConcurrentSet<int> ChannelMaps;
extern ConcurrentSet<int> TimedMaps;
extern ConcurrentSet<int> QBattleEnable;
extern ConcurrentSet<int> AuctionItemDisable;
extern ConcurrentSet<int> AntiKs;
extern ConcurrentSet<int> PKIgnoreItem;
extern ConcurrentSet<int> BoundAllowedItems;
extern ConcurrentSet<int> QuestDisable;
extern ConcurrentSet<int> SkillsPVP;
extern ConcurrentSet<int> ItemDisable;
extern ConcurrentSet<int> RidingDisableSkill;
extern ConcurrentSet<int> WeaponReplacePrefix;
extern ConcurrentSet<int> UnBlob;
extern ConcurrentSet<int> UnGap;
extern ConcurrentSet<int> SinDisable;
extern std::set<int> Macro;
extern ConcurrentSet<std::string> Filter;
extern ConcurrentSet<int> PacketBlock;
extern ConcurrentSet<std::string> RewardLimit;
extern ConcurrentSet<uint32_t> BlockList;

// Set End //

extern std::vector<int> ProtectLeaderList;
extern std::vector<DKInfo> ScenarioGuild;
extern std::vector<ChanceItem> F10Items;
extern std::vector<ChanceItem> MautItem;
extern std::vector<ChanceItem> BossExpItem;
extern std::vector<int> MD5FileChecker;
extern std::vector<ChanceItem> MonstersItem;
extern std::vector<int> DuelUnbuff;
extern std::vector<int> LawlessEXP;
extern std::vector<Point> JailCoords;
extern std::vector<SinSpawner> SinSpawners;
extern std::vector<PartyReg> PartyRegistrations;
extern std::vector<int> RShopItems;
extern std::vector<int> RShopAmounts;
extern std::vector<int> RShopLevels;
extern std::vector<MD5Type> MD5File;

extern std::unordered_map<int, MissionInfo> MissionQuests;
extern std::unordered_map<int, MissionInfo> MAbandonCheck;
extern std::unordered_map<int, MissionInfo> MissionQuestsItem;
extern std::unordered_map<int, std::pair<std::string, int>> EmoteSystem;
extern std::unordered_map<int, std::string> WeaponReplaceMsg;
extern std::unordered_map<int, DailyDuty> DutyQuest;

extern int String2Int(std::string String);
extern char ItemShopPacket[9000];
extern unsigned __int64 _ExpTable[312];
extern std::string ConfigCheckDB1, ConfigCheckDB2;;
extern std::string WCWinner;


#endif  // VARIABLES_H
