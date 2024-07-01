#include <cstdio>
#include <string>
#include <set>
#include <Windows.h>
#include "dirent.h"
#include "Declarations.h"
int maximum(int a, int b) {
	return (a > b) ? a : b;
}


int ScrollTimeCheck = 0;
int ReloadingMobs = 0;
char ConfigCheck[50], ConfigClient[50], ConfigEngine[50], ConfigEpk[50], AntiKsCheck[50], SinCheck[50], PlayerCheck[50], Active2ndPwd[50], ThiefActiveCheck[50], ShamanActiveCheck[50], ShopRewardCheck[50];
char ServerName[50], AuthSvr[50], VoteAPIKey[50];
char BossEXPName[50], BossEXPFinalMsg[BUFSIZ];
char BFName[50], LMSName[50], DKName[50], PLName[50], TBName[50], SVName[50], DTName[50], CTFName[50], LotteryName[50], LottoName[50], F10Name[50], MautName[50], HuntingSysName[50], WCName[50];
char ShoutsWebhook[BUFSIZ], LevelWebhook[BUFSIZ], BofWebhook[BUFSIZ], NoticeWebHook[BUFSIZ], Avatar[BUFSIZ], StarterWebhook[BUFSIZ], RebornWebhook[BUFSIZ], AssassinWebhook[BUFSIZ], HonorNoticeWebhook[BUFSIZ];
int CurGroup = 1, WorldCupTime = 195;
std::string ConfigCheckDB3 = "Hell", ConfigCheckDB4 = "Hell";
char key1 = '\xFF', key2 = '\xFF', key3 = '\xFF', key4 = '\xFF', key5 = '\xFF', key6 = '\xFF', key7 = '\xFF';
int ConfigMix = 0, ConfigImp = 0, ConfigDBCheck = 0;
int EggExpTime = 0, EggExpKill = 0, ConfigMaxDamage = 0, ConfigMaxMagAtk = 0, ConfigMaxPhyAtk = 0;
int EmokQuestIndex = 0, EmokX = 0, EmokY = 0, EmokMap = 0, EmokCert = 0;
int MysteryResetItem = 0, MysteryQuest = 0, MysteryEnable = 0;
int MD5Check = 0, HellCooldown = 0, testcmd = 0, tmcd = 0;
int Shouts = 0, DefaultUnblob = 0, DefaultSkinView = 0;
int BattlepassActive = 0, BattlepassQuest = 0, BattlepassIndex = 0;
int MaxLoginAttemps = 2;
int IPEnable = 0;
int SkillTestAction = 0, SkillR1 = 0, SkillR2 = 0, SkillTimer = 0, SkillIndex = 0;
int testK = 0;
std::set<int> disabledNPCIndices;
volatile LONG summonPets = 0;
volatile LONG CreatePacket = 0;
volatile LONG LastIP = 0;
int MautMap = 0, MautQuest = 0, MautQuestEnd = 0, MautRIndex = 0, MautRPrefix = 0, MautRAmount = 0, MautChance = 0, MautX = 0, MautY = 0, MautSpawnX = 0, MautSpawnY = 0, MautLevel = 0;
int BossEXPChance = 0;
int maxxStatPoints = 254;
long long int StoreSoldCheck = 0, StoreCheckQuest = 0;
int NewcomerValue = 0, NewcomerLevel = 0, NewcomerActive = 0, NewcomerSys = 0;
int Snow = 0;
int tradePVP = 0;
int RaidRoundCounter = 0;
double DelaySpam = 0;
int FireStormVThief = 0;
int PacketProtection = 0, AFKRange = 0;
unsigned __int64 LotteryCheck = 0;
int itemin = 0, itemam = 0, itempr = 0;
int JewelIndex = 0;
int Gun = 0;
int EmoteQuest = 0, EmoteCooldown = 0, EmoteItem = 0;
int SendItemIndex = 0;
int VODConf = 0;
int KillerHPPL = 0, KillerRPPL = 0, KilledHPPL = 0, KilledRPPL = 0, KillerHPBF = 0, KillerRPBF = 0, KilledHPBF = 0, KilledRPBF = 0, KillerHPGVG = 0, KillerRPGVG = 0, KilledHPGVG = 0, KilledRPGVG = 0;
int OriginalLowest = 0, OriginalLow = 0, OriginalNormal = 0, OriginalHard = 0, OriginalHardest = 0;
int VoteQuest = 0, VoteID = 0;
int CaptureQuest = 0, CaptureMap = 0, CaptureReward = 0, CaptureRewardAmount = 0, CaptureMonster = 0;
int DNPCQ = 0, DNPCRQ = 0, DNPCDL = 0, DNPCIA = 0, DNPCDU = 0, DNPCII = 0, DNPCDD = 0, DNPCDC = 0;
int FishLowest = 0, FishLow = 0, FishNormal = 0, FishHard = 0, FishHardest = 0;
int KnightManaCirculation = 0, Knight, KPWWReduce = 0, KPWWMul = 0, KPWWMin = 0, KPWWMax = 0;
int KPOBReduce = 0, KPOBMul = 0, KPOBRange = 0, KPOBMin = 0, KPOBMax = 0;
int KSSReduce = 0, KSSMul = 0, KSSMin = 0, KSSMax = 0, KSSDBMin = 0, KSSDBMax = 0;
int KSDReduce = 0, KSDMul = 0, KSDMin = 0, KSDMax = 0;
int MageManaCirculation = 0, MRIAmount = 0, ArcherManaCirculation = 0;
int MSDReduce = 0, MSDMul = 0, MSDMin = 0, MSDMax = 0;
int MFBReduce = 0, MFBMul = 0, MFBMin = 0, MFBMax = 0;
int MIAReduce = 0, MIAMul = 0, MIAMin = 0, MIAMax = 0;
int MIcicleReduce = 0, MIcicleMul = 0, MIcicleMin = 0, MIcicleMax = 0;
int MTBReduce = 0, MTBMul = 0, MTBMin = 0, MTBMax = 0;
int AVAReduce = 0, AVAMul = 0, AVAMin = 0, AVAMax = 0, AVAPoisonMin = 0, AVAPoisonMax = 0;;
int AAEReduce = 0, AAEMul = 0, AAEMin = 0, AAEMax = 0;
int AARReduce = 0, AARMul = 0, AARMin = 0, AARMax = 0;
int EBSMul = 0, EBSReduce = 0, ERAReduce = 0, ERAMul = 0, ETBReduce = 0, ETBMul = 0;
int ALAReduce = 0, ALAMul = 0;
int ACSReduce = 0, ACSMul = 0, ACSMin = 0, ACSMax = 0, ACAOE = 0, ACPVPAOE = 0, ACAOERange = 0;
int MLAReduce = 0, MLAMul = 0, MLAMin = 0, MLAMax = 0;
int MFIReduce = 0, MFIMul = 0, MFIMin = 0, MFIMax = 0;
int MMIReduce = 0, MMIMul = 0, MMIMin = 0, MMIMax = 0;
int TEShinReduce = 0, TEShinMul = 0, TEZilReduce = 0, TEZilMul = 0, TEWhirReduce = 0, TEWhirMul = 0;
int TWOHReduce = 0, TWOHMul = 0, TWOHMin = 0, TWOHMax = 0;
int TSBReduce = 0, TSBMul = 0, TSBMin = 0, TSBMax = 0;
int TSSReduce = 0, TSSMul = 0, TSSMin = 0, TSSMax = 0;
int TLSReduce = 0, TLSMul = 0, TLSMin = 0, TLSMax = 0;
int TDOKReduce = 0, TDOKMul = 0, TDOKMin = 0, TDOKMax = 0;
int TCOReduce = 0, TCOMin = 0, TCOMax = 0, MageFakeDamage = 0;
int TCAReduce = 0, TCAMin = 0, TCAMax = 0;
int TTBSReduce = 0, TTBSMul = 0, TTBSMin = 0, TTBSMax = 0;
int TSAReduce = 0, TSAMul = 0, TSAMin = 0, TSAMax = 0;
int TSuBReduce = 0, TSuBMul = 0, TSuBMin = 0, TSuBMax = 0;
int TFBReduce = 0, TFBMul = 0, TFBMin = 0, TFBMax = 0;
int TAssReduce = 0, TAssMul = 0, TAssMin = 0, TAssMax = 0;
int TVSReduce = 0, TVSMul = 0, TVSMin = 0, TVSMax = 0;
int TRupReduce = 0, TRupMul = 0, TRupMin = 0, TRupMax = 0;
int TFWReduce = 0, TFWMul = 0, TFWMin = 0, TFWMax = 0;
int TStranReduce = 0, TStranMul = 0, TStranMin = 0, TStranMax = 0;
int TStunReduce = 0, TStunMul = 0, TStunMin = 0, TStunMax = 0;
int BFMap = 0, BFQuest = 0, ScenarioMap = 0, ScenarioQuest = 0, DonationCoin = 0, F10Quest = 0, BFTime = 0, ScenarioTime = 0, F10Level = 0;
int GVETime = 0;
int DTQuest = 0, DTLimit = 0, ConfigPVPMaxDmg = 100000;
int BFRange = 0, BFBoss = 0, BFBossX = 0, BFBossY = 0, BFBossTime = 0, BFBossReward = 0, BFBossBuffX1 = 0, BFBossBuffY1 = 0, BFBossBuffX2 = 0, BFBossBuffY2 = 0;
//REWARDS
int WinnerBF = 0, LoserBF = 0, DrawBF = 0;
int WinnerDK = 0, LoserDK = 0, DrawDK = 0;
int WinnerCapture = 0, LoserCapture = 0, DrawCapture = 0;
int WinnerPL = 0, LoserPL = 0;
int WinnerDuel = 0, LoserDuelRound = 0, WinnerDuelRound = 0;
int amount = 0;
int WinnerLMS = 0, LoserLMS = 0;
int WinnerHell = 0;
int VoteReward = 0;
int BossHuntReward = 0;
int ExtensionTime = 0;
int ScenarioQuestR = 0, ScenarioQuestB = 0;
int COKQuest = 0, COKLimit = 0, COKR = 0, COKA = 0;
unsigned __int64 Hashes = 0;
bool MessageExecuted = false;
unsigned __int64 F10Exp1 = 1, F10Exp2 = 1, F10Exp3 = 1, F10Exp4 = 1, F10Exp5 = 1, F10Exp6 = 1, F10Exp7 = 1, F10Exp8 = 0;
unsigned __int64 MautExp1 = 1, MautExp2 = 1, MautExp3 = 1, MautExp4 = 1, MautExp5 = 1, MautExp6 = 1, MautExp7 = 1, MautExp8 = 0;
int HellQuest = 0, HellMap = 0, HellX = 0, HellY = 0, HellReturnX = 0, HellReturnY = 0, HellSummonX = 0, HellSummonY = 0;
int F10BuffEnable = 0, F10BuffSys = 0, F10Agi = 0, F10Hth = 0, F10Int = 0, F10Wis = 0, F10Str = 0, F10Min = 0, F10Max = 0, F10EXPBuff = 0;
int CaptureDuration = 0, HaninChance = 0, HaninChange = 0;
int FilterCheck = 0;
int SDAOE = 0, SDLOWAOE = 0;
int F10Multiply = 0, MautMultiply = 0;
int SDPVPAOE = 0;
int SDRange = 0;
int GZLvl = 0, ReviveLvl = 0, ReviveCD = 0, ReviveBuff = 0, ReviveSpeed = 0;
int Maskon = 0, Maskoff = 0;
int HTime = 0, jailtime = 0;;
int betType = 0, betAmount = 0, ReplyLottoQuest = 0;
int RaidQuest = 0, RaidHonor = 0, RaidRP = 0, RaidMap = 0;
int Raid1 = 0, Raid2 = 0, Raid3 = 0, Raid4 = 0, Raid5 = 0, Raid6 = 0, Raid7 = 0, Raid8 = 0, Raid9 = 0, RaidReward1 = 0, RaidAmount1 = 0, RaidReward2 = 0, RaidAmount2 = 0;
int RaidReward3 = 0, RaidAmount3 = 0, RaidReward5 = 0, RaidAmount5 = 0, RaidReward7 = 0, RaidAmount7 = 0, RaidReward8 = 0, RaidAmount8 = 0, RaidReward9 = 0, RaidAmount9 = 0, RaidReward6 = 0, RaidAmount6 = 0, RaidReward4 = 0, RaidAmount4 = 0;
char RaidTime[50] = "", CaptureTime[50] = "";
int RaidItem = 0, RaidItemAmount = 0, RaidLevel = 0;
int RaidMini1 = 0, RaidMiniAmount1 = 0, RaidMini2 = 0, RaidMiniAmount2 = 0, RaidMini3 = 0, RaidMiniAmount3 = 0, RaidMini4 = 0, RaidMiniAmount4 = 0;
int packetDebugger = 0, chatDebug = 0, skillDebug = 0, commandDebug = 0, questDebug = 0, loginDebug = 0, rangeDebug = 0, attackDebug = 0;
int HWIDBlock = 0, EXPLimit = 0, MaxEXP = 0;
int GOBOTP = 0, SOFSMIN = 0, SOFSMAX = 0, LMSReward = 0, LMSAmount = 0, BFReward = 0, BFAmount = 0, GVGReward = 0, GVGAmount = 0, PReward = 0, PAmount = 0;
int DReward = 0, DAmount = 0, FishScale = 0;
int PacketTime = 0, PacketLimit = 0, PacketActive = 0, PacketInBetween = 0;
int betAct = 0, betGeon = 0, betDona = 0, betCoin = 0, betSuicide = 0, betSurrender = 0;
int LotAct = 0, LotQuest = 0, LotRQuest = 0, LotIndex = 0, LotAmount = 0, HRQuest = 0;
int LotLevelMin = 0, LotLevelMax = 0;
int levellimit = 0;
int PVPArenaTiming = 0;
int LottoAct = 0, LottoQuest = 0, LottoIndex = 0, LottoAmount = 0, LottoReward = 0, LottoRAmount = 0, LottoLevelMin = 0, LottoLevelMax = 0;
int BossIndex = 0, BossRewardIndex = 0, BossRewardAmount = 0;
int BFRewardPts = 0, BFHonorPts = 0, ScenarioRewardPts = 0, ScenarioHonorPts = 0, ProtectHonorPts = 0, ProtectRewardPts = 0, DuelRewardPts = 0, DuelHonorPts = 0, CaptureHonorPts = 0, CaptureRewardPts = 0, LMSRewardPts = 0, LMSHonorPts = 0;
int KVK = 0, KVA = 0, KVM = 0, KVT = 0, KVS = 0, AVK = 0, AVA = 0, AVM = 0, AVT = 0, AVS = 0, MVK = 0, MVA = 0, MVM = 0, MVT = 0, MVS = 0, TVK = 0, TVA = 0, TVM = 0, TVT = 0, TVS = 0, SVK = 0, SVA = 0, SVM = 0, SVT = 0, SVS = 0;
int FatalDamagePVP = 0, FatalDamagePVE = 0;
char boxnotice[BUFSIZ], moveto[BUFSIZ], portuser[BUFSIZ], bet[BUFSIZ], ignoredPlayer[BUFSIZ], unignoredPlayer[BUFSIZ], block[BUFSIZ], unblock[BUFSIZ], hardblock[BUFSIZ], newnotice[BUFSIZ], donatename[BUFSIZ], duelname[BUFSIZ], mutename[BUFSIZ], jailname[BUFSIZ], ipname[BUFSIZ], nameugog[BUFSIZ], buffnameplayer[BUFSIZ], unjailname[BUFSIZ], unmutename[BUFSIZ], guildinvitename[BUFSIZ], honorupName[BUFSIZ], rewardupName[BUFSIZ], bypassName[BUFSIZ];
int blocktime = 0;
int newnoticetype = 0, senditemindx = 0, buffid = 0, bufftime = 0, buffvalue = 0, geonamount = 0, speedvalue = 0, maskups = 0, killmobs = 0, summonindex = 1, summonamount = 1, donateamount = 1, senditemprefix = 0, cwtotaltime = 0, mutetime = 0;
const char *MyReLisansCheckChar = "nothing"; std::string MyReLisansCheckStr = "nothing";
int ShopRewardTime = 0;
int ShopFortCheck = 0;
int shopPlayers = 0;
char ShopRewardIndex[512], ShopRewardAmount[512], ShopRewardLvl[512];
char ExpEventStart[50] = "Hell", ExpEventEnd[50] = "Hell", ActiveExpEvent[50] = "Hell";
char Honor1[50] = "Empty", Honor2[50] = "Empty", Honor3[50] = "Empty", Honor4[50] = "Empty", Honor5[50] = "Empty", Honor6[50] = "Empty", Honor7[50] = "Empty", Honor8[50] = "Empty", Honor9[50] = "Empty", Honor10[50] = "Empty";
int Honor1Sys = 0, Honor2Sys = 0, Honor3Sys = 0, Honor4Sys = 0, Honor5Sys = 0, Honor6Sys = 0, Honor7Sys = 0, Honor8Sys = 0, Honor9Sys = 0, Honor10Sys = 0, Honor1Stats = 0, Honor2Stats = 0, Honor3Stats = 0, Honor4Stats = 0, Honor5Stats = 0, Honor6Stats = 0, Honor7Stats = 0, Honor8Stats = 0, Honor9Stats = 0, Honor10Stats = 0, Honor1PVE = 0, Honor2PVE = 0, Honor3PVE = 0, Honor4PVE = 0, Honor5PVE = 0, Honor6PVE = 0, Honor7PVE = 0, Honor8PVE = 0, Honor9PVE = 0, Honor10PVE = 0;
int Honor1PVP = 0, Honor2PVP = 0, Honor3PVP = 0, Honor4PVP = 0, Honor5PVP = 0, Honor6PVP = 0, Honor7PVP = 0, Honor8PVP = 0, Honor9PVP = 0, Honor10PVP = 0;
int Honor1Fatal = 0, Honor2Fatal = 0, Honor3Fatal = 0, Honor4Fatal = 0, Honor5Fatal = 0, Honor6Fatal = 0, Honor7Fatal = 0, Honor8Fatal = 0, Honor9Fatal = 0, Honor10Fatal = 0;
int Honor1EB = 0, Honor2EB = 0, Honor3EB = 0, Honor4EB = 0, Honor5EB = 0, Honor6EB = 0, Honor7EB = 0, Honor8EB = 0, Honor9EB = 0, Honor10EB = 0;
int DutyTotalAmount = 0;
int HonorTimer = 0;
int LMSLimit = 0, LMSQuest = 0, LMSMap = 0, LMSX = 0, LMSY = 0;
int LMSMobIndex = 0, LMSMobX = 0, LMSMobY = 0, LMSRange = 0;
int PLQuest = 0, PLMap = 0, PLRNPC = 0, PLBNPC = 0;
int NWOEMul = 0, NWOEMin = 0, NWOEMax = 0, NWOEReduce = 0;
int NOHSMul = 0, NOHSMin = 0, NOHSMax = 0, NOHSReduce = 0;
int NAOTMMul = 0, NAOTMMin = 0, NAOTMMax = 0, NAOTMReduce = 0;
int NMFMul = 0, NMFMin = 0, NMFMax = 0, NMFReduce = 0;
int NSOTAMul = 0, NSOTAMin = 0, NSOTAMax = 0, NSOTAReduce = 0;
int NMPMul = 0, NMPMin = 0, NMPMax = 0, NMPReduce = 0;
int NCSMul = 0, NCSMin = 0, NCSMax = 0, NCSReduce = 0;
int NSOGMul = 0, NSOGMin = 0, NSOGMax = 0, NSOGReduce = 0;
int NDAMul = 0, NDAMin = 0, NDAMax = 0, NDAReduce = 0;
int NBOMMul = 0, NBOMMin = 0, NBOMMax = 0, NBOMReduce = 0;
int ENPCQ = 0, ENPCRQ = 0, ENPCDL = 0, ENPCIA = 0, ENPCDU = 0, ENPCII = 0, ENPCDD = 0, ENPCDC = 0;
char HGST[50] = ""; int HGXC = 0, HGYC = 0, HGMapI = 0, HGMobI = 0, HGEA = 0;
char CWTCC[50] = ""; int CWTCD = 0, CWTCSH = 0, CWTCEH = 0;
int ShopJewelIndex = 0, ShopGoldIndex = 0, ShopSilverIndex = 0;
int SHMGK = 0, SHMGF = 0, SHMW = 0, SHMGW = 0, SHMED = 0, SHMTSP = 0, SHMAOB = 0, SHMWOE = 0, SHMSOP = 0, SHMSP = 0, SHMDB = 0;
int SHMME = 0, SHMC = 0, SHMSS = 0, SHMES = 0, SHMSW = 0, SHMD = 0, SHMRK = 0;
int Insanity = 0, Thunder = 0, Violent = 0, Storm = 0, Ancient = 0, Perfo = 0;
int ReplyWC = 0, WCWinQuest = 0;
int off = 0, pla = 0;
int FOESkillsActive = 0;
int Tries = 0;
int Restri = 0, TrackerActive = 0;
int BFTeleRedX = 0, BFTeleRedY = 0, BFTeleRedZ = 0, BFTeleBlueX = 0, BFTeleBlueY = 0, BFTeleBlueZ = 0, BFRedSafeX1 = 0, BFRedSafeX2 = 0, BFRedSafeY1 = 0, BFRedSafeY2 = 0, BFBlueSafeX1 = 0, BFBlueSafeX2 = 0, BFBlueSafeY1 = 0, BFBlueSafeY2 = 0;
int CPTeleRedX = 0, CPTeleRedY = 0, CPTeleBlueX = 0, CPTeleBlueY = 0, CPRedSafeX1 = 0, CPRedSafeX2 = 0, CPBlueSafeX1 = 0, CPBlueSafeX2 = 0;
int RedStoneX = 0, RedStoneY = 0, BlueStoneX = 0, BlueStoneY = 0;
int PVPMobIndex = 0, PartyTime = 0, PartyMobScore = 0, PartyReviveCD = 0;
RECT rectBlueSafe = RECT(), rectRedSafe = RECT();
int BFTeleRedXG = 0, BFTeleRedYG = 0, BFTeleRedZG = 0, BFTeleBlueXG = 0, BFTeleBlueYG = 0, BFTeleBlueZG = 0, BFRedSafeX1G = 0, BFRedSafeX2G = 0, BFRedSafeY1G = 0, BFRedSafeY2G = 0, BFBlueSafeX1G = 0, BFBlueSafeX2G = 0, BFBlueSafeY1G = 0, BFBlueSafeY2G = 0;
int CPTeleRedXG = 0, CPTeleRedYG = 0, CPTeleBlueXG = 0, CPTeleBlueYG = 0, CPRedSafeX1G = 0, CPRedSafeX2G = 0, CPBlueSafeX1G = 0, CPBlueSafeX2G = 0;
int RedStoneXG = 0, RedStoneYG = 0, BlueStoneXG = 0, BlueStoneYG = 0;
RECT rectBlueSafeG = RECT(), rectRedSafeG = RECT();
RECT BFBossBuff = RECT();

int CPSummonX = 0, CPSummonY = 0, RedCPSummonX = 0, RedCPSummonY = 0, BlueCPSummonX = 0, BlueCPSummonY = 0;
int CPQuestR = 0, CPQuestB = 0;

int CPHP = 0; char CPBuffEffect[50];
int CPPoints = 0, CPSeconds = 0, CPMaxScore = 0;
int CPGate = 0, CPMob = 0, CPMobAmount = 0;
int CPGateRX = 0, CPGateRY = 0, CPGateBX = 0, CPGateBY = 0, CPMobRedX = 0, CPMobRedY = 0, CPMobBlueX = 0, CPMobBlueY = 0;
int DailyLoginLimit = 0, DailyLoginBound = 0, DailyLogin = 0, IPCheck = 0, DailyRewardQuest = 0;
//new
int FishLimit = 0, ShoppingLimit = 0;
int F10Chance = 0;
int NirvanaEnable = 0, NirvanaQuest = 0;
int TrainingHit = 0, FreeTime = 0, TrainingPrice = 0;
int namePadIndex = 0, namePadPrice = 0, namePadDuration = 0;
int ShadowAOEPVE = 0, ShadowRange = 0, ShadowAOEPVP;
int EFakePlayers = 0;
int AuctionLimit = 0;
int GuildLimit = 0;
int SQCheck = 0, maxAmountQ = 0;
int DuelDuration = 0;
int MinMacro = 0, MaxMacro = 0, MacroStartTime = 0;

// NEW MYSTERY SKILLS
int MystPAtkQ = 0, MystMAtkQ = 0, MystHPQ = 0, MystDefQ = 0, MystOTPQ = 0, MystEVAQ = 0;
int MystPAtkS = 0, MystMAtkS = 0, MystHPS = 0, MystDefS = 0, MystOTPS = 0, MystEVAS = 0;
int MystLevel = 0, MystLevelMax = 0, NewMystEnable = 0, NewMystReset = 0;
int GuildEXPGrade4 = 0;
int GuildEXPGrade3 = 0;
int GuildEXPGrade2 = 0;
int GuildColors = 0, LeaderColor = 0, SubLeaderColor = 0, ChiefColor = 0;
int iceStoneMax = 0, iceStoneValue = 0;
char IceStoneEffect[BUFSIZ] = "", LightningStoneEffect[BUFSIZ] = "";
int AuthTimer = 0;
int MemberFull1 = 0;
int MemberFull2 = 0;
int MemberFull3 = 0;
int MemberFull4 = 0;
int TempMemberFull = 0;
int AllyMemberFull = 0;
int MaxTimeAlly = 0;
int ChannelActivated = 0;
int EmokLvl = 0, BattlefieldLevel = 0, BattlefieldAFK = 0, BFAFKActive = 0, BFHWID = 0, LMSHWID = 0, PVPHWID = 0, BattlefieldBuffs = 0;
int BattlefieldSpeed = 0;

int MLMMax = 0;
int MLMStudentLevel = 0;
int MLMTeacherLevel = 0;
int MLMLevel1Reward = 0;
int MLMMoneyReward = 0;
int RewardHWID = 0;
int ShopLevelLimit = 0;
int TradeLevelLimit = 0;
int ExpansionIndex = 0, ExpansionAmount = 0;
int ImmortalEffect, ImmortalSBKey, ImmortalSBName = 0, ImmortalPVP = 0;
int PKKillActive = 0, PKKillPlayer = 0, PKKillChance = 0, PKKillPlayerChance = 0, PKLvlDiff = 0;
int PeaceEvil = 0, PEStartHTML = 0, SlytherinQuest = 0, GryffindorQuest = 0, SlytherinColor = 0, GryffindorColor = 0, SlytherinGCIndex = 0, GryffindorGCIndex = 0, TimerEP = 0, AmountEP = 0, PELoginHTML = 0, PECSlytherin = 0, PECGryffindor = 0, PECHufflepuff = 0, PECRavenclaw = 0;
int RavenQuest = 0, RavenColor = 0, RavenGCIndex = 0;
int HuffleQuest = 0, HuffleColor = 0, HuffleGCIndex = 0;
//HonorTags
int Slytherin0 = 0, Slytherin1 = 0, Slytherin2 = 0, Slytherin3 = 0, Slytherin4 = 0, Slytherin5 = 0, Slytherin6 = 0, Slytherin7 = 0, Slytherin8 = 0, Slytherin9 = 0, Slytherin10 = 0;
int Gryffindor0 = 0, Gryffindor1 = 0, Gryffindor2 = 0, Gryffindor3 = 0, Gryffindor4 = 0, Gryffindor5 = 0, Gryffindor6 = 0, Gryffindor7 = 0, Gryffindor8 = 0, Gryffindor9 = 0, Gryffindor10 = 0;
int Ravenclaw0 = 0, Ravenclaw1 = 0, Ravenclaw2 = 0, Ravenclaw3 = 0, Ravenclaw4 = 0, Ravenclaw5 = 0, Ravenclaw6 = 0, Ravenclaw7 = 0, Ravenclaw8 = 0, Ravenclaw9 = 0, Ravenclaw10 = 0;
int Hufflepuff0 = 0, Hufflepuff1 = 0, Hufflepuff2 = 0, Hufflepuff3 = 0, Hufflepuff4 = 0, Hufflepuff5 = 0, Hufflepuff6 = 0, Hufflepuff7 = 0, Hufflepuff8 = 0, Hufflepuff9 = 0, Hufflepuff10 = 0;
int HouseReward = 0, HouseRewardTime = 0, HouseRewardAmount = 0;
//HTEnd
char SlytherinLoginMSG[512], GryffindorLoginMSG[512], RavenclawLoginMSG[512], HufflepuffLoginMSG[512];
int AQuestBackX = 0, AQuestBackY = 0, ACooldown = 0;
const char* ErrorMsg = "An error has occured, please try again.";
int StBroken = 0;
int STBuffEnabled = 0;
int ShopBound = 0;
int TastyLvl = 0;
int ScrollOfInv = 0, ScrollOfMovingPL = 0;
int EggPercentage, EggSBName = 0, EggSBKey = 0;
int EggBuff = 0, EggValue = 0;
int DamagePercentage, DamageSBName = 0, DamageSBKey = 0;
int thirdCheck = 0, thirdCheck2 = 0, fuseNotice = 0, F10Limit = 0, MautLimit = 0, InstanceLimit = 0;
int BossEXPLimit = 0;
int JailMap = 0;
int CwRewardGuild = 0, CwRewardAlly = 0, CwRewardOther = 0;
int RaidDonateQuest = 0, RaidDonateQFlag = 0;
int RaidStartQuest = 0, RaidStartQFlag = 0;
int RaidReplyQuest = 0, RaidReplyQFlag = 0;
int RaidGuildMap = 0, RaidGuildIndex = 0;
int RaidMinimumAmount = 0, RaidMaximumAmount = 0;
int RaidGuildTime = 0;
int SpinSlashRange = 0;
int MaxAttempts = 0;
int DBOutput = 0;
int GoldenCoinA = 0, GoldenCoinT = 0, GoldenCoinI = 0;
int AntiKSTime = 0;
int DQBound = 0;
int AssassinLimit = 0, AssassinParty = 0;
int PartyEXPMax = 0;
int CBuffRange = 0, CRangeCheck = 0;
int AETime = 0;
int OBPVPEnable = 0, OBActive = 0;
int LawlessMap = 0;
int LawlessMKill = 0, LawlessPKill = 0;
int ARRange = 0, MRange = 0, KRange = 0, TRange = 0, SRange = 0, RangeKick = 0;
int CWRLimit = 0;
bool ShamanDisabled = false, ThiefDisabled = false;
int LawlessSpawnX = 0, LawlessSpawnY = 0, LawlessReviveCD = 0;
int TBPlayersMin = 0, TBPlayersMax = 0, TBMin = 0, TBMax = 0;
int TBBackX = 0, TBBackY = 0, TBBackZ = 0, EmblemSet = 0, EmblemPull = 0, EmblemExpire = 0;
int TBReward0 = 0, TBReward1 = 0, TBReward2 = 0, TBReward3 = 0;
int TestVV = 0, AutoMissionQuest = 0;
int TBMap = 0, TBRedX = 0, TBRedY = 0, TBRedZ = 0, TBBlueX = 0, TBBlueY = 0, TBBlueZ = 0, TBYellowX = 0, TBYellowY = 0, TBYellowZ = 0, TBBuffEach = 0, TBTime = 0, TBCooldown = 0;
int SVMap = 0, SVReplyQuest = 0, SVRegisterDefault = 0, SVTime = 0, SVWinnerReward = 0, SVLoserReward = 0, SVDrawReward = 0, SVPtMob = 0, SVPtPlayer = 0;
int RupPVPAoe = 0, RupRange = 0, RupAOE = 0;
int PSActive = 0, PSHonor = 0, PSReward = 0, PSLimit = 0, KrPSsysReward = 0, KdPSsysReward = 0;
int BSOFSky = 0, BSOFSkyMax = 0;
int PVPLvLDiffDmg = 0;
int MiningPCLimit = 0, MiningAreaLimit = 0;
int SlytherinDieX = 0, SlytherinDieY = 0, SlytherinDieZ = 0, GryffindorDieX = 0, GryffindorDieY = 0, GryffindorDieZ = 0, RavenDieX = 0, RavenDieY = 0, RavenDieZ = 0, HuffleDieX = 0, HuffleDieY = 0, HuffleDieZ = 0;
int DQuestGap = 0;
int ManaCostActive = 0;
int TransmigrationLimit = 0;
int SEMapX = 0, SEMapY = 0, SERewardWinner = 0, SERewardLoser = 0, SEPtsPerMob = 0, SEPtsPerPlayer = 0, SEMinimumPoints = 0, SEDefaultTime = 0, SESpawnCycle = 0, SEImmunityTime = 0;
int BoundAllow = 0;
int ScrollEM = 0;
int RebornQuest = 0, RebornActive = 0, RebornGZ = 0;
int MageDifference = 0;
int PDMul = 0, PDPVP = 0, BlessPVP = 0;
int PPSys = 0, PPSysB = 0, PPEXP = 0, CJBEXP = 0, CJBSYS = 0, CJBSYSB = 0, CJBEXPActive = 0, CJBRange = 0, PPActive = 0, My_PPActive = 0;
int itemIndex = 0;
int EVGoodReward = 0, EVGoodLoser = 0, EVGoodDraw = 0;
int PetBound = 0, TimedItemBound = 0;
int BossEXPQuest = 0, BossEXPRange = 0, BossEXPTime = 0, BossEXPPrepare = 0, BossEXPMap = 0, BossEXPMob = 0, BossEXPMX = 0, BossEXPMY = 0, BossEXPPX = 0, BossEXPPY = 0;
int t1 = 0, t2 = 0, t3 = 0, t4 = 0, t5 = 0, t6 = 0, t7 = 0, t8 = 0, t9 = 0, t10 = 0, t11 = 0, t12 = 0, t13 = 0, t14 = 0, t15 = 0, t16 = 0, t17 = 0, t18 = 0, t19 = 0, t20 = 0, t21 = 0, t22 = 0, t23 = 0;

bool sortByChance(const ChanceItem &a, const ChanceItem &b)
{
	return a.Chance < b.Chance;
}

bool sortSwapChance(const SwapItem &a, const SwapItem &b)
{
	return a.Chance < b.Chance;
}
bool sortByKey(const int &a, const int &b)
{
	return a < b;
}

int GetLevelDiff() {
	return MageDifference;
}
time_t notices, timeReloading;

std::set<std::string> modifiedFiles;
void readDir(std::string dirName)
{
	DIR *directory = opendir(dirName.c_str());
	struct dirent *dirEntry = readdir(directory);
	dirEntry = readdir(directory);
	struct stat buff;
	while (dirEntry = readdir(directory)) {
		std::string fileName = dirName + "/" + dirEntry->d_name;
		if (dirEntry->d_type == 16384)
			readDir(fileName);
		else if (dirEntry->d_type == 32768) {
			stat(fileName.c_str(), &buff);
			if (buff.st_mtime > timeReloading)
				modifiedFiles.insert(fileName);
		}
	}

	closedir(directory);
}

int IntTime(int day, int hour, int minute, int second) {
	return (day * 1000000) + (hour * 10000) + (minute * 100) + second;
}

int GetTBMap() {
	return TBMap;
}

