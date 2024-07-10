#ifndef VARIABLES_H
#define VARIABLES_H

#include <unordered_map>
#include <string>
#include <map>
#include <cstdint>
//#include "Lock.h"
#include "ConcurrentMap.h"
#include "ConcurrentSet.h"

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

	std::set<int> Maps;
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

struct pRewards
{
	int Level;
	int Progress;
};

extern std::map<int, pRewards> F10EXPRewards;
extern std::vector<int> ProtectLeaderList;
extern ConcurrentMap<int, std::string> ProtectLeaderName;
extern std::set<int> ProtectBlackList;
extern std::vector<DKInfo> ScenarioGuild;
extern std::set<int> SVBlackList;
extern std::set<int> DestructingBlackList;
extern ConcurrentMap<int, std::string> SufferingValleyRegistration;
extern ConcurrentSet<int> PlayerBlockCheck;
extern ConcurrentSet<int> ScenarioRegistration;
extern ConcurrentMap<int, ConcurrentSet<int>> EventMapsRegistration;
extern ConcurrentMap<int, std::vector<DuelRegistre>> DuelRegistrationList;
extern ConcurrentMap<int, std::string> DuelNames;
extern ConcurrentMap<int, int> PollVoteAmount;
extern ConcurrentMap<std::string, std::set<int>> PollVotes;
extern ConcurrentMap<int, ItemLimitConf> ItemLimitUsage;
extern std::map<int, std::vector<MonsterDailyQuest>> MonsterQuests;
extern std::map<int, std::vector<MonsterDailyDuty>> DutyMonsterQuests;
extern std::map<int, ItemQuestRepeat> ItemQuestRepeats;
extern std::map<int, MSkill> MSkills;
extern std::map<int, std::vector<int>> MonsterSkills;
extern std::map<int, TaskQ> TaskQuests;
extern std::map<int, QuestEx> QuestExs;
extern std::map<int, SuitStat> SuitStats;
extern std::map<int, SkillLearn> SkillChecks;
extern std::map<int, DailyReward> DailyLogins;
extern std::map<int, std::vector<MLMReward>> MLMRewards;
extern std::map<int, SecretBlackSmithSkill>SecretBlackSmith;
extern std::map<int, RentalExtend> RentalItems;
extern std::map<int, ConfigRentArmor> RentArmor;
extern std::map<int, ConfigRentWeapon> RentWeapon;
extern std::map<int, Items> RentQuests;
extern std::map<int, std::vector<int>> QuestRentItem;
extern std::set<int> DisablePrefix;
extern std::map<int, int> HonorShop;
extern std::map<int, int> HonorIndex;
extern std::map<int, BossEXPMsg> BossEXPMsgs;
extern std::vector<ChanceItem> F10Items;
extern std::vector<ChanceItem> MautItem;
extern std::vector<ChanceItem> BossExpItem;
extern std::map<int, F10EXP> F10EXPs;
extern std::map<int, F10EXP> MautEXPs;
extern std::map<int, F10EXP> BossEXPs;
extern std::map<int, GuildRaidLevel> GuildRaidLevels;
extern std::map<int, TrainingLvl> TrainingEXP;
extern std::map<int, ChanceItem> TrainingDrops;
extern std::map<int, MasterEnchanting> MasterEnchant;
extern std::map<int, int> RidingCollectionIndex;
extern std::map<int, int> EnchantCount;
extern std::map<int, RidingCollection> RidingCollections;
extern std::map<int, GuildBuffQuest> GuildBuffQuests;
extern std::set<int> SummonTrack;
extern std::map<int, Reborn> Reborns;
extern std::map<int, RbPenalty> RebornsPenalty;
extern std::map<int, RbPenalty> NonRebornsPenalty;
extern std::map<int, RbGear> RebornGear;
extern std::map<int, RbQuest> RebornsMaps;
extern std::map<int, double> LevelGap;
extern std::map<int, HaninRate> HaninLow;
extern std::map<int, HaninRate> HaninMiddle;
extern std::map<int, HaninRate> HaninHigh;
extern std::map<int, ItemsEffects> EquipEffects;
extern std::map<int, PVEWeaponsS> PVEWeapon;
extern std::set<int> MixConfigPrefix;
extern std::map<int, int> MixConfigInfo;
extern std::map<int, std::string> MixConfigMsg;
extern std::map<int, PimpConfig> CheckPimp;
extern std::map<int, int> ArmorPimpConfig;
extern std::map<int, int> PVEDamagePimp;
extern std::map<int, int> PVPDamagePimp;
extern std::vector<int> MD5FileChecker;
extern std::map<int, std::vector<RectLevel>> RectArea;
extern std::map<int, CMonstersRewards> MonstersRewards;
extern std::vector<ChanceItem> MonstersItem;
extern std::map<int, CQuestsNotice> cQuestsNotice;
extern std::map<int, std::vector<ConfigLevelReward>> PremiumPass;
extern std::map<int, std::set<int>> StoreItems;
extern std::map<int, Restriction> HWIDRestrictions;
extern std::map<std::string, ShoutData> CustomHouse;
extern std::map<std::string, int> CustomNotices;
extern std::map<std::string, ShoutData> CustomShouts;
extern std::map<std::string, std::vector<RGBNotice>> RGBAutoNotice;
extern ConcurrentMap<int, MSummonedConfig> SummonedQuest;
extern std::set<int> MQuest;
extern std::map<int, MSummonConfig> SummonQuest;
extern ConcurrentSet<int> EventMaps;
extern std::map<int, eventMap> EventMapsQuests;
extern std::vector<int> DuelUnbuff;
extern std::map<int, Poll> Polls;
extern std::map<int, Poll> PollTimer;
extern std::map<int, MiningItem> MiningItems;
extern std::map<int, SoulPocketConfig> SoulPockets;
extern std::map<int, int> SoulPocketEffect;
extern std::map<int, SingleConfigBuffer> SingleBufferCheck;
extern std::set<int> PKDropEnable;
extern std::map<int, Combinator> Combinators;
extern std::map<int, PerfectParty> My_PerfectParty;
extern std::map<int, Certificates> AreaCert;
extern std::map<int, Certificates> AreaCertMap;
extern std::vector<int> LawlessEXP;
extern std::set<int> UnBreak;
extern std::map<int, std::set<int>> SystemBlacklist;
extern std::vector<SinSpawner> SinSpawners;
extern std::map<int, SMultiple> EXPMultipliers;
extern std::map<int, EmokCertConf> EmokCerts;
extern std::set<int> UnAggro;
extern std::map<int, int> FatalDmg;
extern std::set<int> UnChannel;
extern std::set<int> ChannelMaps;
extern std::set<int> TimedMaps;
extern std::map<int, AreaQuest> AreaQuests;
extern ConcurrentMap<long, QuestTime> PlayerTimedQuest;
extern std::map<int, QuestTime> TimedQuest;
extern std::set<int> QBattleEnable;
extern std::map<int, int> PlayerVsPlayerDmg;
extern std::map<int, QuestLevel> QuestLevels;
extern std::map<int, PartyReward> PartyRewards;
extern std::map<int, PartyReg> PTEnabled;
extern std::map<std::string, PartyReg> PTCommands;
extern std::map<std::string, std::vector<PartyReg>> PartyTimer;
extern std::vector<PartyReg> PartyRegistrations;
extern std::map<int, PartyBattle> CurPartys; extern std::map<int, std::string> EventTimer;
extern std::map<int, std::string> EventMapsTimer;
extern std::map<int, std::string> EndTimer;
extern std::map<int, std::vector<Items>> StarterItems;
extern std::map<int, StarterClass> Starters;
extern std::set<int> AntiKs;
extern std::map<int, NecklaceBuff> NecklaceBuffs;
extern std::map<int, BeltBuff> BeltBuffs;
extern std::vector<Point> JailCoords;
extern std::set<int> AuctionItemDisable;
extern std::map<int, SummonNPC> ItemNPCSummoned;
extern std::map<int, int> ItemReward;
extern std::map<int, ItemLimit> ItemLimits;
extern std::map<int, int> ItemNPC;
extern std::map<int, CItemTasty> ItemTasty;
extern std::map<int, CItemTasty> ItemHpDef;
extern std::map<int, CItemTasty> ItemScrolls;
extern std::map<int, CItemTasty> ItemExpansion;
extern std::map<int, CItemTasty> ItemBuffSrv;
extern std::map<int, OldStats> PlayerStats;
extern std::map<int, InitSwap> InitPetSwap;
extern std::map<int, ItemExchange> ItemExchanges;
extern std::set<int> PKIgnoreItem;
extern std::map<int, int> MobPets;
extern std::vector<int> RShopItems;
extern std::vector<int> RShopAmounts;
extern std::vector<int> RShopLevels;
extern std::set<int> BoundAllowedItems;
extern std::map<int, ConfigBuff> BuffCheck;
extern std::unordered_map<int, MissionInfo> MissionQuests;
extern std::unordered_map<int, MissionInfo> MAbandonCheck;
extern std::unordered_map<int, MissionInfo> MissionQuestsItem;
extern std::map<int, AreaExpItem> AreasExpItems;
extern std::map<__int16, ConfigItemShop> ItemShopCheck;
extern std::map<int, CreateMonsterPet> MonsterPet;
extern ConcurrentMap<int, FakePlayers_> FakePlayers;
extern ConcurrentMap<int, FakeItems_> FakeItems;
extern ConcurrentMap<std::string, int> FakeNames;
extern std::map<int, std::vector<ChanceItem>> FishingList;
extern std::unordered_map<int, std::pair<std::string, int>> EmoteSystem;
extern std::map<int, IWebs> ItemWebsite;
extern std::vector<MD5Type> MD5File;
extern std::set<int> SkillsPVP;
extern std::set<int> ItemDisable;
extern std::set<int> RidingDisableSkill;
extern std::map<int, ZProtection> ugog;
extern std::set<int> QuestDisable;
extern std::map<int, SkillDamage> SkillsDamage;
extern std::map<int, ItemTime> TimedItems;
extern std::map<int, ItemBuff> BuffedItems;
extern std::map<int, SBoxes> Boxes;
extern std::map<int, WCRew> WCRewards;
extern std::set<int> WeaponReplacePrefix;
extern std::map<int, int> WeaponReplaceIndex;
extern std::unordered_map<int, std::string> WeaponReplaceMsg;
extern std::map<int, int> WeaponReplace;
extern std::map<int, CheckCalculations> PVPConfigCalculations;
extern std::map<int, CheckCalculations> ConfigCalculations;
extern std::map<int, std::vector<AutoNoticeConf>> AutoCenterNotices;
extern std::map<int, std::vector<CheckSummonTimer>> SummonTimer;
extern std::map<int, std::vector<AFKCheck>> AFKMap;
extern std::set<int> SinDisable;
extern std::map<int, ItemMss> MSS;
extern std::map<int, CItemUsed> ItemUsed;
extern std::map<int, int> ItemQuest;
extern std::map<int, CAutoNotice> AutoNotices;
extern std::set<int> UnBlob;
extern std::set<int> UnGap;
extern std::map<int, Area> MapLvl;
extern std::map<int, std::vector<ConfigLevelReward>> LevelReward;
extern std::map<int, ConfigDailyQuest> DailyQuest;
extern std::map<int, std::set<int>> DisableSkill;
extern std::map<int, AreaMax> MapMax;
extern ConcurrentMap<int, int> PacketSpam;
extern std::set<int> PacketBlock;
extern std::map<int, int> PacketSpamConf;
extern std::set<std::string> Filter;
extern ConcurrentSet<uint32_t> BlockList;
extern std::map<std::string, std::string> Tracker;
extern std::map<int, Restriction> Restrictions;
extern ConcurrentSet<std::string> RewardLimit;
extern std::map<int, MakeItem_>MakeItem;
extern std::map<int, SwapMineral>MakeChange;
extern std::map<int, SwapMineral>MakeMinerals;
extern std::set<int> Macro;
extern std::map<int, std::set<int>> DisableSkillFile;
extern std::map<int, CMonstersBuff> MonstersBuff;
extern std::map<int, CMonstersBuff> RMonstersBuff;
extern std::map<int, CQuestsNotice> QuestsNotice;
extern std::map<int, CheckSkillBook> SkillBook;
extern std::map<int, CheckSkillBook> SkillDowngrade;
extern std::map<int, CheckConfigEggCooldown> CheckEggCooldownConfig;
extern std::map<int, CheckConfigCooldown> CheckCooldownConfig;
extern std::map<int, ConfigPetTime> PetTime;
extern std::map<int, SkillRangeConfig> CheckRangeConfig;
extern std::map<int, std::string> QuestWebsite;
extern std::map<std::string, CommandLink> CustomCommands;
extern std::map<int, SummonGuard> SGuard;
extern std::map<int, BuffDisable> BuffDisableCheck;
extern std::map<int, BuffDisable> BuffRemoveCheck;
extern std::map<int, ConfigBuffer> BufferCheck;
extern std::map<int, BuffMaker> BuffMakerCheck;
extern std::map<int, int> HighGradeBof;
extern std::map<int, int> HighGradeImperial;
extern std::map<int, std::vector<ConfigLevelReward>> BattlepassReward;
extern std::map<int, ConfigTimeTalisman> NormalPetTalisman;
extern std::map<int, ConfigTimeTalisman> MonsterPetTalisman;
extern std::map<int, ConfigTimeTalisman> CostumeTalisman;
extern std::map<int, ConfigTimeTalisman> SkinTalisman;
extern std::map<int, Reward> Rewards;
extern std::unordered_map<int, DailyDuty> DutyQuest;

extern int String2Int(std::string String);
extern char ItemShopPacket[9000];
extern unsigned __int64 _ExpTable[312];


#endif  // VARIABLES_H
