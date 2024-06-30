#include <sys/types.h>
#include <sys/stat.h>
#include "dirent.h"
extern int maximum(int a, int b);

extern int ScrollTimeCheck;
extern int ReloadingMobs;
extern char ConfigCheck[50], ConfigClient[50], ConfigEngine[50], ConfigEpk[50], AntiKsCheck[50], SinCheck[50], PlayerCheck[50], Active2ndPwd[50], ThiefActiveCheck[50],ShamanActiveCheck[50], ShopRewardCheck[50];
extern char ServerName[50], AuthSvr[50], VoteAPIKey[50];
extern char BossEXPName[50], BossEXPFinalMsg[BUFSIZ];
extern char BFName[50], LMSName[50], DKName[50], PLName[50], TBName[50], SVName[50], DTName[50], CTFName[50], LotteryName[50], LottoName[50], F10Name[50], MautName[50], HuntingSysName[50], WCName[50];
extern char ShoutsWebhook[BUFSIZ], LevelWebhook[BUFSIZ], BofWebhook[BUFSIZ], NoticeWebHook[BUFSIZ], Avatar[BUFSIZ], StarterWebhook[BUFSIZ], RebornWebhook[BUFSIZ], AssassinWebhook[BUFSIZ], HonorNoticeWebhook[BUFSIZ];
extern int CurGroup, WorldCupTime;
extern std::string ConfigCheckDB3, ConfigCheckDB4;
extern char key1, key2, key3, key4, key5, key6, key7;
extern int ConfigMix, ConfigImp, ConfigDBCheck;
extern int EggExpTime, EggExpKill, ConfigMaxDamage, ConfigMaxMagAtk, ConfigMaxPhyAtk;
extern int EmokQuestIndex, EmokX, EmokY, EmokMap, EmokCert;
extern int MysteryResetItem, MysteryQuest, MysteryEnable;
extern int MD5Check, HellCooldown, testcmd,tmcd;
extern int Shouts, DefaultUnblob, DefaultSkinView;
extern int BattlepassActive, BattlepassQuest, BattlepassIndex;
extern int MaxLoginAttemps;
extern int IPEnable;
extern int SkillTestAction, SkillR1, SkillR2, SkillTimer, SkillIndex;
extern int testK;
extern std::set<int> disabledNPCIndices;
extern volatile LONG summonPets;
extern volatile LONG CreatePacket;
extern volatile LONG LastIP;
extern int MautMap, MautQuest, MautQuestEnd, MautRIndex, MautRPrefix, MautRAmount, MautChance, MautX, MautY, MautSpawnX, MautSpawnY, MautLevel;
extern int BossEXPChance;
extern int maxxStatPoints;
extern long long int StoreSoldCheck, StoreCheckQuest;
extern int NewcomerValue, NewcomerLevel, NewcomerActive, NewcomerSys;
extern int Snow;
extern int tradePVP;
extern int RaidRoundCounter;
extern double DelaySpam;
extern int FireStormVThief;
extern int PacketProtection, AFKRange;
extern unsigned __int64 LotteryCheck;
extern int itemin,itemam,itempr;
extern int JewelIndex;
extern int Gun;
extern int EmoteQuest, EmoteCooldown, EmoteItem;
extern int SendItemIndex;
extern int VODConf;
extern int KillerHPPL, KillerRPPL, KilledHPPL, KilledRPPL, KillerHPBF, KillerRPBF, KilledHPBF, KilledRPBF, KillerHPGVG, KillerRPGVG, KilledHPGVG, KilledRPGVG;
extern int OriginalLowest, OriginalLow, OriginalNormal, OriginalHard, OriginalHardest;
extern int VoteQuest,VoteID;
extern int CaptureQuest, CaptureMap, CaptureReward, CaptureRewardAmount, CaptureMonster;
extern int DNPCQ, DNPCRQ, DNPCDL, DNPCIA, DNPCDU, DNPCII, DNPCDD, DNPCDC;
extern int FishLowest, FishLow, FishNormal, FishHard, FishHardest;
extern int KnightManaCirculation, Knight, KPWWReduce, KPWWMul, KPWWMin, KPWWMax;
extern int KPOBReduce, KPOBMul, KPOBRange, KPOBMin, KPOBMax;
extern int KSSReduce, KSSMul, KSSMin, KSSMax, KSSDBMin, KSSDBMax;
extern int KSDReduce, KSDMul, KSDMin, KSDMax;
extern int MageManaCirculation, MRIAmount, ArcherManaCirculation;
extern int MSDReduce, MSDMul, MSDMin, MSDMax;
extern int MFBReduce, MFBMul, MFBMin, MFBMax;
extern int MIAReduce, MIAMul, MIAMin, MIAMax;
extern int MIcicleReduce, MIcicleMul, MIcicleMin, MIcicleMax;
extern int MTBReduce, MTBMul, MTBMin, MTBMax;
extern int AVAReduce, AVAMul, AVAMin, AVAMax, AVAPoisonMin, AVAPoisonMax;;
extern int AAEReduce, AAEMul, AAEMin, AAEMax;
extern int AARReduce, AARMul, AARMin, AARMax;
extern int EBSMul, EBSReduce, ERAReduce, ERAMul, ETBReduce, ETBMul;
extern int ALAReduce, ALAMul;
extern int ACSReduce, ACSMul, ACSMin, ACSMax, ACAOE, ACPVPAOE, ACAOERange;
extern int MLAReduce, MLAMul, MLAMin, MLAMax;
extern int MFIReduce, MFIMul, MFIMin, MFIMax;
extern int MMIReduce, MMIMul, MMIMin, MMIMax;
extern int TEShinReduce, TEShinMul, TEZilReduce, TEZilMul, TEWhirReduce, TEWhirMul;
extern int TWOHReduce, TWOHMul, TWOHMin, TWOHMax;
extern int TSBReduce, TSBMul, TSBMin, TSBMax;
extern int TSSReduce, TSSMul, TSSMin, TSSMax;
extern int TLSReduce, TLSMul, TLSMin, TLSMax;
extern int TDOKReduce, TDOKMul, TDOKMin, TDOKMax;
extern int TCOReduce, TCOMin, TCOMax, MageFakeDamage;
extern int TCAReduce, TCAMin, TCAMax;
extern int TTBSReduce, TTBSMul, TTBSMin, TTBSMax;
extern int TSAReduce, TSAMul, TSAMin, TSAMax;
extern int TSuBReduce, TSuBMul, TSuBMin, TSuBMax;
extern int TFBReduce, TFBMul, TFBMin, TFBMax;
extern int TAssReduce, TAssMul, TAssMin, TAssMax;
extern int TVSReduce, TVSMul, TVSMin, TVSMax;
extern int TRupReduce, TRupMul, TRupMin, TRupMax;
extern int TFWReduce, TFWMul, TFWMin, TFWMax;
extern int TStranReduce, TStranMul, TStranMin, TStranMax;
extern int TStunReduce, TStunMul, TStunMin, TStunMax;
extern int BFMap, BFQuest, ScenarioMap, ScenarioQuest, DonationCoin, F10Quest, BFTime, ScenarioTime, F10Level;
extern int GVETime;
extern int DTQuest, DTLimit, ConfigPVPMaxDmg;
extern int BFRange, BFBoss, BFBossX, BFBossY, BFBossTime, BFBossReward, BFBossBuffX1, BFBossBuffY1, BFBossBuffX2, BFBossBuffY2;
//REWARDS
extern int WinnerBF, LoserBF, DrawBF;
extern int WinnerDK, LoserDK, DrawDK;
extern int WinnerCapture, LoserCapture, DrawCapture;
extern int WinnerPL, LoserPL;
extern int WinnerDuel, LoserDuelRound, WinnerDuelRound;
extern int amount;
extern int WinnerLMS, LoserLMS;
extern int WinnerHell;
extern int VoteReward;
extern int BossHuntReward;
extern int ExtensionTime;
extern int ScenarioQuestR, ScenarioQuestB;
extern int COKQuest,COKLimit,COKR,COKA;
extern unsigned __int64 Hashes;
extern bool MessageExecuted;
extern unsigned __int64 F10Exp1, F10Exp2, F10Exp3, F10Exp4, F10Exp5, F10Exp6, F10Exp7, F10Exp8;
extern unsigned __int64 MautExp1, MautExp2, MautExp3, MautExp4, MautExp5, MautExp6, MautExp7, MautExp8;
extern int HellQuest, HellMap, HellX, HellY, HellReturnX, HellReturnY, HellSummonX, HellSummonY;
extern int F10BuffEnable, F10BuffSys, F10Agi, F10Hth, F10Int, F10Wis, F10Str, F10Min, F10Max, F10EXPBuff;
extern int CaptureDuration,HaninChance, HaninChange;
extern int FilterCheck;
extern int SDAOE, SDLOWAOE;
extern int F10Multiply, MautMultiply;
extern int SDPVPAOE;
extern int SDRange;
extern int GZLvl, ReviveLvl, ReviveCD, ReviveBuff, ReviveSpeed;
extern int Maskon, Maskoff;
extern int HTime, jailtime;;
extern int betType,betAmount, ReplyLottoQuest;
extern int RaidQuest,RaidHonor,RaidRP,RaidMap;
extern int Raid1,Raid2,Raid3,Raid4,Raid5,Raid6,Raid7,Raid8,Raid9,RaidReward1,RaidAmount1,RaidReward2,RaidAmount2;
extern int RaidReward3,RaidAmount3,RaidReward5,RaidAmount5,RaidReward7,RaidAmount7,RaidReward8,RaidAmount8,RaidReward9,RaidAmount9,RaidReward6,RaidAmount6,RaidReward4,RaidAmount4;
extern char RaidTime[50], CaptureTime[50];
extern int RaidItem,RaidItemAmount,RaidLevel;
extern int RaidMini1,RaidMiniAmount1,RaidMini2,RaidMiniAmount2,RaidMini3,RaidMiniAmount3,RaidMini4,RaidMiniAmount4;
extern int packetDebugger, chatDebug, skillDebug, commandDebug, questDebug, loginDebug, rangeDebug, attackDebug;
extern int HWIDBlock, EXPLimit, MaxEXP;
extern int GOBOTP, SOFSMIN, SOFSMAX, LMSReward, LMSAmount, BFReward, BFAmount, GVGReward,GVGAmount,PReward,PAmount;
extern int DReward,DAmount, FishScale;
extern int PacketTime, PacketLimit, PacketActive, PacketInBetween;
extern int betAct,betGeon,betDona, betCoin, betSuicide, betSurrender;
extern int LotAct,LotQuest, LotRQuest, LotIndex, LotAmount, HRQuest;
extern int LotLevelMin, LotLevelMax;
extern int levellimit;
extern int PVPArenaTiming;
extern int LottoAct, LottoQuest, LottoIndex, LottoAmount, LottoReward, LottoRAmount, LottoLevelMin, LottoLevelMax;
extern int BossIndex,BossRewardIndex,BossRewardAmount;
extern int BFRewardPts,BFHonorPts,ScenarioRewardPts,ScenarioHonorPts,ProtectHonorPts,ProtectRewardPts,DuelRewardPts,DuelHonorPts,CaptureHonorPts,CaptureRewardPts,LMSRewardPts,LMSHonorPts;
extern int KVK, KVA, KVM, KVT, KVS, AVK, AVA, AVM, AVT, AVS, MVK, MVA, MVM, MVT, MVS, TVK, TVA, TVM, TVT, TVS, SVK, SVA, SVM, SVT, SVS;
extern int FatalDamagePVP, FatalDamagePVE;
extern char boxnotice[BUFSIZ], moveto[BUFSIZ], portuser[BUFSIZ], bet[BUFSIZ], ignoredPlayer[BUFSIZ], unignoredPlayer[BUFSIZ], block[BUFSIZ], unblock[BUFSIZ], hardblock[BUFSIZ], newnotice[BUFSIZ], donatename[BUFSIZ], duelname[BUFSIZ], mutename[BUFSIZ],jailname[BUFSIZ], ipname[BUFSIZ], nameugog[BUFSIZ], buffnameplayer[BUFSIZ], unjailname[BUFSIZ], unmutename[BUFSIZ], guildinvitename[BUFSIZ], honorupName[BUFSIZ], rewardupName[BUFSIZ], bypassName[BUFSIZ];
extern int blocktime;
extern int newnoticetype, senditemindx, buffid, bufftime, buffvalue, geonamount, speedvalue, maskups, killmobs, summonindex, summonamount, donateamount, senditemprefix, cwtotaltime, mutetime;
extern const char *MyReLisansCheckChar; extern std::string MyReLisansCheckStr;
extern int ShopRewardTime;
extern int ShopFortCheck;
extern int shopPlayers;
extern char ShopRewardIndex[512], ShopRewardAmount[512], ShopRewardLvl[512];
extern char ExpEventStart[50], ExpEventEnd[50], ActiveExpEvent[50];
extern char Honor1[50], Honor2[50], Honor3[50], Honor4[50], Honor5[50], Honor6[50], Honor7[50], Honor8[50], Honor9[50], Honor10[50];
extern int Honor1Sys, Honor2Sys, Honor3Sys, Honor4Sys, Honor5Sys, Honor6Sys, Honor7Sys, Honor8Sys, Honor9Sys, Honor10Sys, Honor1Stats, Honor2Stats, Honor3Stats, Honor4Stats, Honor5Stats, Honor6Stats, Honor7Stats, Honor8Stats, Honor9Stats, Honor10Stats, Honor1PVE, Honor2PVE, Honor3PVE, Honor4PVE, Honor5PVE, Honor6PVE, Honor7PVE, Honor8PVE, Honor9PVE, Honor10PVE;
extern int Honor1PVP, Honor2PVP, Honor3PVP, Honor4PVP, Honor5PVP, Honor6PVP, Honor7PVP, Honor8PVP, Honor9PVP, Honor10PVP;
extern int Honor1Fatal, Honor2Fatal, Honor3Fatal, Honor4Fatal, Honor5Fatal, Honor6Fatal, Honor7Fatal, Honor8Fatal, Honor9Fatal, Honor10Fatal;
extern int Honor1EB, Honor2EB, Honor3EB, Honor4EB, Honor5EB, Honor6EB, Honor7EB, Honor8EB, Honor9EB, Honor10EB;
extern int DutyTotalAmount;
extern int HonorTimer;
extern int LMSLimit, LMSQuest, LMSMap, LMSX, LMSY;
extern int LMSMobIndex, LMSMobX, LMSMobY, LMSRange;
extern int PLQuest, PLMap, PLRNPC, PLBNPC;
extern int NWOEMul, NWOEMin, NWOEMax, NWOEReduce;
extern int NOHSMul, NOHSMin, NOHSMax, NOHSReduce;
extern int NAOTMMul, NAOTMMin, NAOTMMax, NAOTMReduce;
extern int NMFMul, NMFMin, NMFMax, NMFReduce;
extern int NSOTAMul, NSOTAMin, NSOTAMax, NSOTAReduce;
extern int NMPMul, NMPMin, NMPMax, NMPReduce;
extern int NCSMul, NCSMin, NCSMax, NCSReduce;
extern int NSOGMul, NSOGMin, NSOGMax, NSOGReduce;
extern int NDAMul, NDAMin, NDAMax, NDAReduce;
extern int NBOMMul, NBOMMin, NBOMMax, NBOMReduce;
extern int ENPCQ, ENPCRQ, ENPCDL, ENPCIA, ENPCDU, ENPCII, ENPCDD, ENPCDC;
extern char HGST[50]; extern int HGXC, HGYC, HGMapI, HGMobI,  HGEA;
extern char CWTCC[50]; extern int CWTCD, CWTCSH, CWTCEH;
extern int ShopJewelIndex, ShopGoldIndex, ShopSilverIndex;
extern int SHMGK, SHMGF, SHMW, SHMGW, SHMED, SHMTSP, SHMAOB, SHMWOE, SHMSOP, SHMSP, SHMDB;
extern int SHMME, SHMC, SHMSS, SHMES, SHMSW, SHMD, SHMRK;
extern int Insanity, Thunder, Violent, Storm, Ancient, Perfo;
extern int ReplyWC, WCWinQuest;
extern int off,pla;
extern int FOESkillsActive;
extern int Tries;
extern int Restri, TrackerActive;
extern int BFTeleRedX, BFTeleRedY, BFTeleRedZ, BFTeleBlueX, BFTeleBlueY, BFTeleBlueZ, BFRedSafeX1, BFRedSafeX2, BFRedSafeY1, BFRedSafeY2, BFBlueSafeX1, BFBlueSafeX2, BFBlueSafeY1, BFBlueSafeY2;
extern int CPTeleRedX, CPTeleRedY, CPTeleBlueX, CPTeleBlueY, CPRedSafeX1, CPRedSafeX2, CPBlueSafeX1, CPBlueSafeX2;
extern int RedStoneX, RedStoneY, BlueStoneX, BlueStoneY;
extern int PVPMobIndex, PartyTime, PartyMobScore, PartyReviveCD;
extern RECT rectBlueSafe, rectRedSafe;
extern int BFTeleRedXG, BFTeleRedYG, BFTeleRedZG, BFTeleBlueXG, BFTeleBlueYG, BFTeleBlueZG, BFRedSafeX1G, BFRedSafeX2G, BFRedSafeY1G, BFRedSafeY2G, BFBlueSafeX1G, BFBlueSafeX2G, BFBlueSafeY1G, BFBlueSafeY2G;
extern int CPTeleRedXG, CPTeleRedYG, CPTeleBlueXG, CPTeleBlueYG, CPRedSafeX1G, CPRedSafeX2G, CPBlueSafeX1G, CPBlueSafeX2G;
extern int RedStoneXG, RedStoneYG, BlueStoneXG, BlueStoneYG;
extern RECT rectBlueSafeG, rectRedSafeG;
extern RECT BFBossBuff;

extern int CPSummonX, CPSummonY, RedCPSummonX, RedCPSummonY, BlueCPSummonX, BlueCPSummonY;
extern int CPQuestR, CPQuestB;

extern int CPHP; extern char CPBuffEffect[50];
extern int CPPoints, CPSeconds, CPMaxScore;
extern int CPGate, CPMob, CPMobAmount;
extern int CPGateRX, CPGateRY, CPGateBX, CPGateBY, CPMobRedX, CPMobRedY, CPMobBlueX, CPMobBlueY;
extern int DailyLoginLimit, DailyLoginBound, DailyLogin, IPCheck, DailyRewardQuest;
//new
extern int FishLimit, ShoppingLimit;
extern int F10Chance;
extern int NirvanaEnable, NirvanaQuest;
extern int TrainingHit, FreeTime, TrainingPrice;
extern int namePadIndex, namePadPrice, namePadDuration;
extern int ShadowAOEPVE, ShadowRange, ShadowAOEPVP; 
extern int EFakePlayers;
extern int AuctionLimit;
extern int GuildLimit;
extern int SQCheck, maxAmountQ;
extern int DuelDuration;
extern int MinMacro, MaxMacro, MacroStartTime;

// NEW MYSTERY SKILLS
extern int MystPAtkQ, MystMAtkQ, MystHPQ, MystDefQ, MystOTPQ, MystEVAQ;
extern int MystPAtkS, MystMAtkS, MystHPS, MystDefS, MystOTPS, MystEVAS;
extern int MystLevel, MystLevelMax, NewMystEnable, NewMystReset;
extern int GuildEXPGrade4;
extern int GuildEXPGrade3;
extern int GuildEXPGrade2;
extern int GuildColors, LeaderColor, SubLeaderColor, ChiefColor;
extern int iceStoneMax, iceStoneValue;
extern char IceStoneEffect[BUFSIZ], LightningStoneEffect[BUFSIZ];
extern int AuthTimer;
extern int MemberFull1;
extern int MemberFull2;
extern int MemberFull3;
extern int MemberFull4;
extern int TempMemberFull;
extern int AllyMemberFull;
extern int MaxTimeAlly;
extern int ChannelActivated;
extern int EmokLvl, BattlefieldLevel, BattlefieldAFK, BFAFKActive, BFHWID, LMSHWID, PVPHWID, BattlefieldBuffs;
extern int BattlefieldSpeed;

extern int MLMMax;
extern int MLMStudentLevel;
extern int MLMTeacherLevel;
extern int MLMLevel1Reward;
extern int MLMMoneyReward;
extern int RewardHWID;
extern int ShopLevelLimit;
extern int TradeLevelLimit;
extern int ExpansionIndex, ExpansionAmount;
extern int ImmortalEffect, ImmortalSBKey, ImmortalSBName, ImmortalPVP;
extern int PKKillActive, PKKillPlayer, PKKillChance, PKKillPlayerChance, PKLvlDiff;
extern int PeaceEvil, PEStartHTML, SlytherinQuest, GryffindorQuest, SlytherinColor, GryffindorColor, SlytherinGCIndex, GryffindorGCIndex, TimerEP, AmountEP, PELoginHTML, PECSlytherin, PECGryffindor, PECHufflepuff, PECRavenclaw;
extern int RavenQuest, RavenColor, RavenGCIndex;
extern int HuffleQuest, HuffleColor, HuffleGCIndex;
//HonorTags
extern int Slytherin0, Slytherin1, Slytherin2, Slytherin3, Slytherin4, Slytherin5, Slytherin6, Slytherin7, Slytherin8, Slytherin9, Slytherin10;
extern int Gryffindor0, Gryffindor1, Gryffindor2, Gryffindor3, Gryffindor4, Gryffindor5, Gryffindor6, Gryffindor7, Gryffindor8, Gryffindor9, Gryffindor10;
extern int Ravenclaw0, Ravenclaw1, Ravenclaw2, Ravenclaw3, Ravenclaw4, Ravenclaw5, Ravenclaw6, Ravenclaw7, Ravenclaw8, Ravenclaw9, Ravenclaw10;
extern int Hufflepuff0, Hufflepuff1, Hufflepuff2, Hufflepuff3, Hufflepuff4, Hufflepuff5, Hufflepuff6, Hufflepuff7, Hufflepuff8, Hufflepuff9, Hufflepuff10;
extern int HouseReward, HouseRewardTime, HouseRewardAmount;
//HTEnd
extern char SlytherinLoginMSG[512], GryffindorLoginMSG[512], RavenclawLoginMSG[512], HufflepuffLoginMSG[512];
extern int AQuestBackX, AQuestBackY, ACooldown;
extern const char* ErrorMsg;
extern int StBroken;
extern int STBuffEnabled;
extern int ShopBound;
extern int TastyLvl;
extern int ScrollOfInv, ScrollOfMovingPL;
extern int EggPercentage, EggSBName, EggSBKey;
extern int EggBuff, EggValue;
extern int DamagePercentage, DamageSBName, DamageSBKey;
extern int thirdCheck, thirdCheck2 , fuseNotice, F10Limit, MautLimit, InstanceLimit;
extern int BossEXPLimit;
extern int JailMap;
extern int CwRewardGuild, CwRewardAlly, CwRewardOther;
extern int RaidDonateQuest, RaidDonateQFlag;
extern int RaidStartQuest, RaidStartQFlag;
extern int RaidReplyQuest, RaidReplyQFlag;
extern int RaidGuildMap, RaidGuildIndex;
extern int RaidMinimumAmount, RaidMaximumAmount;
extern int RaidGuildTime;
extern int SpinSlashRange;
extern int MaxAttempts;
extern int DBOutput;
extern int GoldenCoinA, GoldenCoinT, GoldenCoinI;
extern int AntiKSTime;
extern int DQBound;
extern int AssassinLimit, AssassinParty;
extern int PartyEXPMax;
extern int CBuffRange, CRangeCheck;
extern int AETime;
extern int OBPVPEnable, OBActive;
extern int LawlessMap;
extern int LawlessMKill, LawlessPKill;
extern int ARRange, MRange, KRange, TRange, SRange, RangeKick;
extern int CWRLimit;
extern bool ShamanDisabled, ThiefDisabled;
extern int LawlessSpawnX, LawlessSpawnY, LawlessReviveCD;
extern int TBPlayersMin, TBPlayersMax, TBMin, TBMax;
extern int TBBackX, TBBackY, TBBackZ, EmblemSet, EmblemPull, EmblemExpire;
extern int TBReward0, TBReward1, TBReward2, TBReward3;
extern int TestVV, AutoMissionQuest;
extern int TBMap, TBRedX, TBRedY, TBRedZ, TBBlueX, TBBlueY, TBBlueZ, TBYellowX, TBYellowY, TBYellowZ, TBBuffEach, TBTime, TBCooldown;
extern int SVMap, SVReplyQuest, SVRegisterDefault, SVTime, SVWinnerReward, SVLoserReward, SVDrawReward, SVPtMob, SVPtPlayer;
extern int RupPVPAoe, RupRange, RupAOE;
extern int PSActive, PSHonor, PSReward, PSLimit, KrPSsysReward, KdPSsysReward;
extern int BSOFSky, BSOFSkyMax;
extern int PVPLvLDiffDmg;
extern int MiningPCLimit, MiningAreaLimit;
extern int SlytherinDieX, SlytherinDieY, SlytherinDieZ, GryffindorDieX, GryffindorDieY, GryffindorDieZ, RavenDieX, RavenDieY, RavenDieZ, HuffleDieX, HuffleDieY, HuffleDieZ;
extern int DQuestGap;
extern int ManaCostActive;
extern int TransmigrationLimit;
extern int SEMapX, SEMapY, SERewardWinner, SERewardLoser, SEPtsPerMob, SEPtsPerPlayer, SEMinimumPoints, SEDefaultTime, SESpawnCycle, SEImmunityTime;
extern int BoundAllow;
extern int ScrollEM;
extern int RebornQuest, RebornActive, RebornGZ;
extern int MageDifference;
extern int PDMul, PDPVP, BlessPVP;
extern int PPSys, PPSysB, PPEXP, CJBEXP, CJBSYS, CJBSYSB, CJBEXPActive, CJBRange, PPActive;
extern int itemIndex;
extern int EVGoodReward, EVGoodLoser, EVGoodDraw;
extern int PetBound, TimedItemBound;
extern int BossEXPQuest, BossEXPRange, BossEXPTime, BossEXPPrepare, BossEXPMap, BossEXPMob, BossEXPMX, BossEXPMY, BossEXPPX, BossEXPPY;
extern int t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, t21, t22, t23;
extern int HonorNotices = 0, ImperialNotices = 0, BofNotices = 0;
extern bool sortByChance(const ChanceItem &a, const ChanceItem &b);
extern bool sortSwapChance(const SwapItem &a, const SwapItem &b);
extern bool sortByKey(const int &a, const int &b);
extern int GetLevelDiff();
extern time_t notices, timeReloading;
//endnew
extern std::set<std::string> modifiedFiles;
extern void readDir(std::string dirName);

extern int IntTime(int day, int hour, int minute, int second);

extern int GetTBMap();
//
//void logLastExecutedCode(const std::string& message) {
//	std::string Dato = "./Debugger/CrashCheck/Debugger.txt";
//
//	std::ofstream DGLOG(Dato, std::ofstream::app);
//
//	if (DGLOG.is_open()) {
//		DGLOG << Time::GetDay() << "_" << Time::GetMonth() << "_" << Time::GetTime() << "(Message: " << message << ")" << endl;
//		DGLOG.flush();  // Flush the stream
//	}
//}

void ReadConfig(bool command)
{
	if (command) {
		modifiedFiles.clear();
		readDir("./Configs");
		readDir("./Skills");
		readDir("./Systems");

		if (modifiedFiles.empty())
			return;
	}
	int OldMD5Check = MD5Check;

	PDMul = GetPrivateProfileIntA("PerfectDefense", "TimeMultiply", 5, "./Skills/Knight.txt");
	PDPVP = GetPrivateProfileIntA("PerfectDefense", "PVPReduce", 50, "./Skills/Knight.txt");
	PetBound = GetPrivateProfileIntA("Bound", "Active", 1, "./Configs/Pet.txt");
	TimedItemBound = GetPrivateProfileIntA("Bound", "Active", 1, "./Configs/TimedItems.txt");

	DefaultUnblob = GetPrivateProfileIntA("DefaultSet", "Unblob", 1, "./Configs/Protection.txt");
	DefaultSkinView = GetPrivateProfileIntA("DefaultSet", "SkinView", 1, "./Configs/Protection.txt");

	BattlepassActive = GetPrivateProfileIntA("Battlepass", "Active", 0, "./Configs/Battlepass.txt");
	BattlepassQuest = GetPrivateProfileIntA("Battlepass", "Quest", 0, "./Configs/Battlepass.txt");
	BattlepassIndex = GetPrivateProfileIntA("Battlepass", "PremiumToken", 0, "./Configs/Battlepass.txt");

	StoreCheckQuest = GetPrivateProfileIntA("Store", "ReplyQuest", 0, "./Configs/Protection.txt");

	NewcomerValue = GetPrivateProfileIntA("Newcomer", "PVE", 15, "./Configs/Newcomer.txt");
	NewcomerLevel = GetPrivateProfileIntA("Newcomer", "MaxLvl", 50, "./Configs/Newcomer.txt");
	NewcomerActive = GetPrivateProfileIntA("Newcomer", "Active", 1, "./Configs/Newcomer.txt");
	NewcomerSys = GetPrivateProfileIntA("Newcomer", "Syskey", 0, "./Configs/Newcomer.txt");
	ReviveLvl = GetPrivateProfileIntA("Revive", "MaxLvl", 50, "./Configs/Newcomer.txt");
	ReviveCD = GetPrivateProfileIntA("Revive", "Cooldown", 10, "./Configs/Newcomer.txt");
	ReviveBuff = GetPrivateProfileIntA("Revive", "BuffGrade", 1, "./Configs/Newcomer.txt");
	ReviveSpeed = GetPrivateProfileIntA("Revive", "SpeedValue", 50, "./Configs/Newcomer.txt");

	Maskon = GetPrivateProfileIntA("MaskUp", "EnablePrice", 200, "./Configs/PKKill.txt");
	Maskoff = GetPrivateProfileIntA("MaskUp", "DisablePrice", 50, "./Configs/PKKill.txt");

	HonorNotices = GetPrivateProfileIntA("CustomNotices", "Honor", 0, "./Configs/Protection.txt");
	BofNotices = GetPrivateProfileIntA("CustomNotices", "BeadOfFire", 0, "./Configs/Protection.txt");
	ImperialNotices = GetPrivateProfileIntA("CustomNotices", "Imperial", 0, "./Configs/Protection.txt");

	ARRange = GetPrivateProfileIntA("RangeProtection", "Archer", 9, "./Configs/Range.txt");
	MRange = GetPrivateProfileIntA("RangeProtection", "Mage", 8, "./Configs/Range.txt");
	KRange = GetPrivateProfileIntA("RangeProtection", "Knight", 3, "./Configs/Range.txt");
	TRange = GetPrivateProfileIntA("RangeProtection", "Thief", 4, "./Configs/Range.txt");
	SRange = GetPrivateProfileIntA("RangeProtection", "Shaman", 8, "./Configs/Range.txt");
	RangeKick = GetPrivateProfileIntA("PlayerKick", "Enable", 0, "./Configs/Range.txt");


	RebornActive = GetPrivateProfileIntA("Reborn", "Active", 0, "./Configs/Reborn.txt");
	RebornQuest = GetPrivateProfileIntA("Quest", "Index", 0, "./Configs/Reborn.txt");
	RebornGZ = GetPrivateProfileIntA("GzMsg", "MinReborn", 1, "./Configs/Reborn.txt");

	MageDifference = GetPrivateProfileIntA("MageShaman", "LevelHit", 30, "./Configs/Protection.txt");
	PPActive = GetPrivateProfileIntA("PerfectParty", "Active", 1, "./Configs/Protection.txt");
	PPSys = GetPrivateProfileIntA("PerfectParty", "SysKey", 2268, "./Configs/Protection.txt");
	PPSysB = GetPrivateProfileIntA("PerfectParty", "BuffKey", 252, "./Configs/Protection.txt");
	PPEXP = GetPrivateProfileIntA("PerfectParty", "EXP", 5, "./Configs/Protection.txt");
	CJBEXP = GetPrivateProfileIntA("CJBParty", "EXP", 20, "./Configs/Protection.txt");
	CJBSYS = GetPrivateProfileIntA("CJBParty", "SysKey", 0, "./Configs/Protection.txt");
	CJBSYSB = GetPrivateProfileIntA("CJBParty", "BuffKey", 0, "./Configs/Protection.txt");
	CJBEXPActive = GetPrivateProfileIntA("CJBParty", "Active", 0, "./Configs/Protection.txt");
	CJBRange = GetPrivateProfileIntA("CJBParty", "Range", 30, "./Configs/Protection.txt");

	ScrollEM = GetPrivateProfileIntA("SavingScroll", "Active", 1, "./Configs/EventMaps.txt");
	MaxLoginAttemps = GetPrivateProfileIntA("Login", "MaxAttempts", 2, "./Configs/Protection.txt");

	PVPMobIndex = GetPrivateProfileIntA("PartyVsParty", "FlagIndex", 3377, "./Systems/PartyVsParty.txt");
	PartyTime = GetPrivateProfileIntA("PartyVsParty", "FlagTime", 60, "./Systems/PartyVsParty.txt");
	PartyMobScore = GetPrivateProfileIntA("PartyVsParty", "Score", 10, "./Systems/PartyVsParty.txt");
	PartyReviveCD = GetPrivateProfileIntA("PartyVsParty", "ReviveCD", 10, "./Systems/PartyVsParty.txt");

	SEMapX = GetPrivateProfileIntA("Map", "X", 0, "./Systems/SinEvent.txt");
	SEMapY = GetPrivateProfileIntA("Map", "Y", 0, "./Systems/SinEvent.txt");
	SERewardLoser = GetPrivateProfileIntA("Reward", "ParticipantRewardID", 0, "./Systems/SinEvent.txt");
	SERewardWinner = GetPrivateProfileIntA("Reward", "WinnerRewardID", 0, "./Systems/SinEvent.txt");
	SEMinimumPoints = GetPrivateProfileIntA("Limit", "MinimumPoints", 0, "./Systems/SinEvent.txt");
	SEDefaultTime = GetPrivateProfileIntA("System", "DefaultTime", 900, "./Systems/SinEvent.txt");
	SESpawnCycle = GetPrivateProfileIntA("System", "SpawnCycle", 60, "./Systems/SinEvent.txt");
	SEImmunityTime = GetPrivateProfileIntA("System", "ImmunityTime", 6, "./Systems/SinEvent.txt");
	SEPtsPerMob = GetPrivateProfileIntA("Points", "PerMob", 1, "./Systems/SinEvent.txt");
	SEPtsPerPlayer = GetPrivateProfileIntA("Points", "PerPlayer", 2, "./Systems/SinEvent.txt");
	
	t1 = GetPrivateProfileIntA("Test", "a1", 120, "./Configs/Test.txt");
	t2 = GetPrivateProfileIntA("Test", "a2", 0, "./Configs/Test.txt");
	t3 = GetPrivateProfileIntA("Test", "a3", 0, "./Configs/Test.txt");
	t4 = GetPrivateProfileIntA("Test", "a4", 0, "./Configs/Test.txt");
	t5 = GetPrivateProfileIntA("Test", "a5", 0, "./Configs/Test.txt");
	t6 = GetPrivateProfileIntA("Test", "a6", 0, "./Configs/Test.txt");
	t7 = GetPrivateProfileIntA("Test", "a7", 0, "./Configs/Test.txt");
	t8 = GetPrivateProfileIntA("Test", "a8", 0, "./Configs/Test.txt");
	t9 = GetPrivateProfileIntA("Test", "a9", 0, "./Configs/Test.txt");
	t10 = GetPrivateProfileIntA("Test", "a10", 0, "./Configs/Test.txt");
	t11 = GetPrivateProfileIntA("Test", "a11", 0, "./Configs/Test.txt");
	t12 = GetPrivateProfileIntA("Test", "a12", 0, "./Configs/Test.txt");
	t13 = GetPrivateProfileIntA("Test", "a13", 0, "./Configs/Test.txt");
	t14 = GetPrivateProfileIntA("Test", "a14", 0, "./Configs/Test.txt");
	t15 = GetPrivateProfileIntA("Test", "a15", 0, "./Configs/Test.txt");
	t16 = GetPrivateProfileIntA("Test", "a16", 0, "./Configs/Test.txt");
	t17 = GetPrivateProfileIntA("Test", "a17", 0, "./Configs/Test.txt");
	t18 = GetPrivateProfileIntA("Test", "a18", 0, "./Configs/Test.txt");
	t19 = GetPrivateProfileIntA("Test", "a19", 0, "./Configs/Test.txt");
	t20 = GetPrivateProfileIntA("Test", "a20", 0, "./Configs/Test.txt");
	t21 = GetPrivateProfileIntA("Test", "a21", 0, "./Configs/Test.txt");
	t22 = GetPrivateProfileIntA("Test", "a22", 0, "./Configs/Test.txt");
	t23 = GetPrivateProfileIntA("Test", "a23", 0, "./Configs/Test.txt");

	BoundAllow = GetPrivateProfileIntA("Storage", "Allow", 0, "./Configs/BoundItems.txt");


	//BossEXP

	GetPrivateProfileStringA("System", "Name", "Boss EXP", BossEXPName, 50, "./Systems/BossEXP.txt");
	GetPrivateProfileStringA("System", "FinalMessage", "Thank you for saving the world...", BossEXPFinalMsg, BUFSIZ, "./Systems/BossEXP.txt");
	BossEXPTime = GetPrivateProfileIntA("System", "Time", 1800, "./Systems/BossEXP.txt");
	BossEXPPrepare = GetPrivateProfileIntA("System", "PrepareTime", 60, "./Systems/BossEXP.txt");
	BossEXPQuest = GetPrivateProfileIntA("Quest", "Index", 0, "./Systems/BossEXP.txt");
	BossEXPChance = GetPrivateProfileIntA("PickPlayer", "Chance", 10, "./Systems/BossEXP.txt");
	BossEXPMob = GetPrivateProfileIntA("Mob", "Index", 0, "./Systems/BossEXP.txt");
	BossEXPMap = GetPrivateProfileIntA("Map", "Index", 30, "./Systems/BossEXP.txt");
	BossEXPRange = GetPrivateProfileIntA("Map", "Range", 100, "./Systems/BossEXP.txt");
	BossEXPMX = GetPrivateProfileIntA("Mob", "SpawnX", 0, "./Systems/BossEXP.txt");
	BossEXPMY = GetPrivateProfileIntA("Mob", "SpawnY", 0, "./Systems/BossEXP.txt");
	BossEXPLimit = GetPrivateProfileIntA("Limit", "Active", 1, "./Systems/BossEXP.txt");
	BossEXPPX = GetPrivateProfileIntA("Player", "SpawnX", 0, "./Systems/BossEXP.txt");
	BossEXPPY = GetPrivateProfileIntA("Player", "SpawnY", 0, "./Systems/BossEXP.txt");


	GetPrivateProfileStringA("SystemNames", "Battlefield", "Battlefield", BFName, 50, "./Systems/Names.txt");
	GetPrivateProfileStringA("SystemNames", "LastManStanding", "Last Man Standing", LMSName, 50, "./Systems/Names.txt");
	GetPrivateProfileStringA("SystemNames", "DuelTournament", "Duel Tournament", DTName, 50, "./Systems/Names.txt");
	GetPrivateProfileStringA("SystemNames", "F10", "Company System", F10Name, 50, "./Systems/Names.txt");
	GetPrivateProfileStringA("SystemNames", "Mautareta", "Mautareta", MautName, 50, "./Systems/Names.txt");
	GetPrivateProfileStringA("SystemNames", "Lottery", "Lottery", LotteryName, 50, "./Systems/Names.txt");
	GetPrivateProfileStringA("SystemNames", "Lotto", "Lotto", LottoName, 50, "./Systems/Names.txt");
	GetPrivateProfileStringA("SystemNames", "TriangularBattle", "Triangular Battle", TBName, 50, "./Systems/Names.txt");
	GetPrivateProfileStringA("SystemNames", "CaptureTheFlag", "Capture the Flag", CTFName, 50, "./Systems/Names.txt");
	GetPrivateProfileStringA("SystemNames", "WorldCup", "World Cup", WCName, 50, "./Systems/Names.txt");
	GetPrivateProfileStringA("SystemNames", "DestructingKeys", "Destructing Keys", DKName, 50, "./Systems/Names.txt");
	GetPrivateProfileStringA("SystemNames", "ProtectingLeader", "Protecting Leader", PLName, 50, "./Systems/Names.txt");
	GetPrivateProfileStringA("SystemNames", "SufferingValley", "Suffering Valley", SVName, 50, "./Systems/Names.txt");
	GetPrivateProfileStringA("SystemNames", "Hunting", "Hunting", HuntingSysName, 50, "./Systems/Names.txt");

	GetPrivateProfileStringA("Webhook", "Shouts", "https://discord.com/api/webhooks/1193728182982025286/y0YEGdScsfyJKEWHdTWWcEO1UU9xxBYr9fNoVHOtbdUYsl00IWxtasBvDphjqY7zKvtq", ShoutsWebhook, 512, "./Configs/Discord.txt");
	GetPrivateProfileStringA("Webhook", "Level", "https://discord.com/api/webhooks/1193728182982025286/y0YEGdScsfyJKEWHdTWWcEO1UU9xxBYr9fNoVHOtbdUYsl00IWxtasBvDphjqY7zKvtq", LevelWebhook, 512, "./Configs/Discord.txt");
	GetPrivateProfileStringA("Webhook", "Notice", "https://discord.com/api/webhooks/1193728182982025286/y0YEGdScsfyJKEWHdTWWcEO1UU9xxBYr9fNoVHOtbdUYsl00IWxtasBvDphjqY7zKvtq", NoticeWebHook, 512, "./Configs/Discord.txt");
	GetPrivateProfileStringA("Webhook", "HonorNotice", "https://discord.com/api/webhooks/1193728182982025286/y0YEGdScsfyJKEWHdTWWcEO1UU9xxBYr9fNoVHOtbdUYsl00IWxtasBvDphjqY7zKvtq", HonorNoticeWebhook, 512, "./Configs/Discord.txt");

	GetPrivateProfileStringA("Webhook", "Assassin", "https://discord.com/api/webhooks/1193728182982025286/y0YEGdScsfyJKEWHdTWWcEO1UU9xxBYr9fNoVHOtbdUYsl00IWxtasBvDphjqY7zKvtq", AssassinWebhook, 512, "./Configs/Discord.txt");

	GetPrivateProfileStringA("Webhook", "Enchant", "https://discord.com/api/webhooks/1193728182982025286/y0YEGdScsfyJKEWHdTWWcEO1UU9xxBYr9fNoVHOtbdUYsl00IWxtasBvDphjqY7zKvtq", BofWebhook, 512, "./Configs/Discord.txt");
	GetPrivateProfileStringA("Webhook", "Starter", "https://discord.com/api/webhooks/1193728182982025286/y0YEGdScsfyJKEWHdTWWcEO1UU9xxBYr9fNoVHOtbdUYsl00IWxtasBvDphjqY7zKvtq", StarterWebhook, 512, "./Configs/Discord.txt");
	GetPrivateProfileStringA("Webhook", "Reborn", "https://discord.com/api/webhooks/1193728182982025286/y0YEGdScsfyJKEWHdTWWcEO1UU9xxBYr9fNoVHOtbdUYsl00IWxtasBvDphjqY7zKvtq", RebornWebhook, 512, "./Configs/Discord.txt");

	GetPrivateProfileStringA("Avatar", "URL", "https://cdn.discordapp.com/attachments/1048039559360958465/1197387263571673119/Kal_Online_Logo.png?ex=65bb14ca&is=65a89fca&hm=4701133d38b57a71fec995b1e36d72f56829d71be89b1cd7ca878f726736d9dd&", Avatar, 512, "./Configs/Discord.txt");

	MAX_CONNECTIONS_PER_IP = GetPrivateProfileIntA("FilterIP", "MaxConnection", 15, "./Configs/Protection.txt");
	CONNECTION_DELAY = GetPrivateProfileIntA("FilterIP", "DelayTime", 5000, "./Configs/Protection.txt");

	TestVV = GetPrivateProfileIntA("Test", "Value", 0, "./Configs/Test.txt");
	BSOFSky = GetPrivateProfileIntA("BlessingSonOfTheSky", "ItemIndex", 0, "./Configs/Protection.txt");
	BSOFSkyMax = GetPrivateProfileIntA("BlessingSonOfTheSky", "MaxGrade", 0, "./Configs/Protection.txt");

	NirvanaEnable = GetPrivateProfileIntA("Nirvana", "Enable", 0, "./Configs/Protection.txt");
	NirvanaQuest = GetPrivateProfileIntA("Nirvana", "Quest", 0, "./Configs/Protection.txt");
	EmoteQuest = GetPrivateProfileIntA("EmoteSystem", "QuestIndex", 0, "./Configs/EmoteSystem.txt");
	EmoteCooldown = GetPrivateProfileIntA("EmoteSystem", "Cooldown", 0, "./Configs/EmoteSystem.txt");
	EmoteItem = GetPrivateProfileIntA("EmoteSystem", "ItemIndex", 0, "./Configs/EmoteSystem.txt");

	SVMap = GetPrivateProfileIntA("Map", "Index", 32, "./Systems/SufferingValley.txt");
	SVPtMob = GetPrivateProfileIntA("Points", "MobKill", 1, "./Systems/SufferingValley.txt");
	SVPtPlayer = GetPrivateProfileIntA("Points", "PlayerKill", 2, "./Systems/SufferingValley.txt");
	SVReplyQuest = GetPrivateProfileIntA("Participants", "Quest", 0, "./Systems/SufferingValley.txt");
	SVRegisterDefault = GetPrivateProfileIntA("Participants", "OnlinePlayers", 2, "./Systems/SufferingValley.txt");
	SVTime = GetPrivateProfileIntA("Time", "Duration", 1800, "./Systems/SufferingValley.txt");
	SVWinnerReward = GetPrivateProfileIntA("Reward", "WinnerRewardID", 0, "./Systems/SufferingValley.txt");
	SVLoserReward = GetPrivateProfileIntA("Reward", "LoserRewardID", 0, "./Systems/SufferingValley.txt");
	SVDrawReward = GetPrivateProfileIntA("Reward", "DrawRewardID", 0, "./Systems/SufferingValley.txt");
	
	TBMap = GetPrivateProfileIntA("Map", "Index", 17, "./Systems/TriangularBattle.txt");
	TBReward0 = GetPrivateProfileIntA("Reward", "NoEssence", 0, "./Systems/TriangularBattle.txt");
	TBReward1 = GetPrivateProfileIntA("Reward", "OneEssence", 0, "./Systems/TriangularBattle.txt");
	TBReward2 = GetPrivateProfileIntA("Reward", "TwoEssence", 0, "./Systems/TriangularBattle.txt");
	TBReward3 = GetPrivateProfileIntA("Reward", "ThreeEssence", 0, "./Systems/TriangularBattle.txt");

	EmblemPull = GetPrivateProfileIntA("Emblem", "PullTime", 10, "./Systems/TriangularBattle.txt");
	EmblemExpire = GetPrivateProfileIntA("Emblem", "ExpirationTime", 300, "./Systems/TriangularBattle.txt");
	EmblemSet = GetPrivateProfileIntA("Emblem", "SetTime", 10, "./Systems/TriangularBattle.txt");

	TBBlueX = GetPrivateProfileIntA("HumanSpawn", "X", 217239, "./Systems/TriangularBattle.txt");
	TBBlueY = GetPrivateProfileIntA("HumanSpawn", "Y", 252959, "./Systems/TriangularBattle.txt");
	TBBlueZ = GetPrivateProfileIntA("HumanSpawn", "Z", 16553, "./Systems/TriangularBattle.txt");

	TBRedX = GetPrivateProfileIntA("DoggebiSpawn", "X", 219591, "./Systems/TriangularBattle.txt");
	TBRedY = GetPrivateProfileIntA("DoggebiSpawn", "Y", 257665, "./Systems/TriangularBattle.txt");
	TBRedZ = GetPrivateProfileIntA("DoggebiSpawn", "Z", 16553, "./Systems/TriangularBattle.txt");

	TBYellowX = GetPrivateProfileIntA("DemonSpawn", "X", 222718, "./Systems/TriangularBattle.txt");
	TBYellowY = GetPrivateProfileIntA("DemonSpawn", "Y", 252647, "./Systems/TriangularBattle.txt");
	TBYellowZ = GetPrivateProfileIntA("DemonSpawn", "Z", 18591, "./Systems/TriangularBattle.txt");

	TBBackX = GetPrivateProfileIntA("TeleportBack", "X", 257514, "./Systems/TriangularBattle.txt");
	TBBackY = GetPrivateProfileIntA("TeleportBack", "Y", 259273, "./Systems/TriangularBattle.txt");
	TBBackZ = GetPrivateProfileIntA("TeleportBack", "Z", 0, "./Systems/TriangularBattle.txt");

	TBPlayersMin = GetPrivateProfileIntA("Registration", "MinPlayers", 1, "./Systems/TriangularBattle.txt");
	TBPlayersMax = GetPrivateProfileIntA("Registration", "MaxPlayers", 255, "./Systems/TriangularBattle.txt");
	TBMin = GetPrivateProfileIntA("Registration", "MinLevel", 1, "./Systems/TriangularBattle.txt");
	TBMax = GetPrivateProfileIntA("Registration", "MaxLevel", 255, "./Systems/TriangularBattle.txt");

	TBBuffEach = GetPrivateProfileIntA("RandomBuff", "Every", 180, "./Systems/TriangularBattle.txt");
	TBTime = GetPrivateProfileIntA("Time", "Duration", 1800, "./Systems/TriangularBattle.txt");
	TBCooldown = GetPrivateProfileIntA("Time", "CooldownToStart", 240, "./Systems/TriangularBattle.txt");

	AutoMissionQuest = GetPrivateProfileIntA("Quest", "FirstMission", 0, "./Configs/Missions.txt");

	LawlessReviveCD = GetPrivateProfileIntA("Revive", "Cooldown", 30, "./Systems/Lawless.txt");
	LawlessSpawnX = GetPrivateProfileIntA("DeathSpawn", "X", 257514, "./Systems/Lawless.txt");
	LawlessSpawnY = GetPrivateProfileIntA("DeathSpawn", "Y", 259273, "./Systems/Lawless.txt");
	LawlessMap = GetPrivateProfileIntA("Map", "Index", 300, "./Systems/Lawless.txt");
	LawlessPKill = GetPrivateProfileIntA("Points", "PlayerKill", 10, "./Systems/Lawless.txt");
	LawlessMKill = GetPrivateProfileIntA("Points", "MobKill", 1, "./Systems/Lawless.txt");
	PVPLvLDiffDmg = GetPrivateProfileIntA("PVPDamage", "LevelDiffMultiply", 0, "./Configs/Protection.txt");
	PartyEXPMax = GetPrivateProfileIntA("PartyEXP", "MaxValue", 1000000000, "./Configs/Protection.txt");
	OBActive = GetPrivateProfileIntA("OrnamentBuff", "Active", 1, "./Configs/OrnamentBuff.txt");
	OBPVPEnable = GetPrivateProfileIntA("PVP", "Enable", 1, "./Configs/OrnamentBuff.txt");

	DQuestGap = GetPrivateProfileIntA("EXPGap", "Active", 1, "./Configs/DailyQuest.txt");
	DQBound = GetPrivateProfileIntA("Reward", "Bound", 0, "./Configs/DailyQuest.txt");

	CBuffRange = GetPrivateProfileIntA("Range", "Buff", 300, "./Skills/Calls.txt");
	CRangeCheck = GetPrivateProfileIntA("Range", "Check", 300, "./Skills/Calls.txt");

	RaidDonateQuest = GetPrivateProfileIntA("DonateQuest", "Index", 0, "./Systems/GuildRaid.txt");
	RaidDonateQFlag = GetPrivateProfileIntA("DonateQuest", "Flag", 0, "./Systems/GuildRaid.txt");
	RaidStartQuest = GetPrivateProfileIntA("StartQuest", "Index", 0, "./Systems/GuildRaid.txt");
	RaidStartQFlag = GetPrivateProfileIntA("StartQuest", "Flag", 0, "./Systems/GuildRaid.txt");
	RaidGuildTime = GetPrivateProfileIntA("StartQuest", "Time", 1800, "./Systems/GuildRaid.txt");
	RaidReplyQuest = GetPrivateProfileIntA("ReplyQuest", "Index", 0, "./Systems/GuildRaid.txt");
	RaidReplyQFlag = GetPrivateProfileIntA("ReplyQuest", "Flag", 0, "./Systems/GuildRaid.txt");
	RaidGuildIndex = GetPrivateProfileIntA("DonateItem", "Index", 31, "./Systems/GuildRaid.txt");

	FatalDamagePVE = GetPrivateProfileIntA("FatalDamage", "PVERate", 100, "./Configs/FatalDamage.txt");
	FatalDamagePVP = GetPrivateProfileIntA("FatalDamage", "PVPRate", 100, "./Configs/FatalDamage.txt");

	JailMap = GetPrivateProfileIntA("Map", "Index", 7, "./Configs/Jail.txt");
	GoldenCoinA = GetPrivateProfileIntA("GoldenCoin", "Amount", 1, "./Configs/Protection.txt");
	GoldenCoinI = GetPrivateProfileIntA("GoldenCoin", "Index", 649, "./Configs/Protection.txt");
	GoldenCoinT = GetPrivateProfileIntA("GoldenCoin", "Time", 1800, "./Configs/Protection.txt");
	CwRewardGuild = GetPrivateProfileIntA("CastleWar", "GuildRewardID", 0, "./Configs/Protection.txt");
	CwRewardAlly = GetPrivateProfileIntA("CastleWar", "AllianceRewardID", 0, "./Configs/Protection.txt");
	CwRewardOther = GetPrivateProfileIntA("CastleWar", "LoserRewardID", 0, "./Configs/Protection.txt");
	CWRLimit = GetPrivateProfileIntA("CastleWar", "RewardLimit", 0, "./Configs/Protection.txt");

	thirdCheck = GetPrivateProfileIntA("ThirdJobUpgrade", "Level", 75, "./Configs/Protection.txt");
	thirdCheck2 = GetPrivateProfileIntA("ThirdJobUpgrade", "Level2", 71, "./Configs/Protection.txt");
	fuseNotice = GetPrivateProfileIntA("FuseNotice", "Active", 0, "./Configs/Protection.txt");

	TastyLvl = GetPrivateProfileIntA("TastyItems", "Level", 70, "./Configs/ItemUse.txt");
	ScrollOfInv = GetPrivateProfileIntA("Scrolls", "Invincibility", 0, "./Configs/ItemUse.txt");
	ScrollOfMovingPL = GetPrivateProfileIntA("Scrolls", "PLLeader", 0, "./Configs/ItemUse.txt");

	IPEnable = GetPrivateProfileIntA("IP", "Active", 1, "./Configs/Protection.txt");
	StBroken = GetPrivateProfileIntA("Break", "Active", 0, "./Configs/StandardBreak.txt");
	STBuffEnabled = GetPrivateProfileIntA("StandardBuff", "Active", 1, "./Configs/StandardBreak.txt");
	AQuestBackX = GetPrivateProfileIntA("TeleportBack", "X", 257514, "./Configs/AreaQuests.txt");
	AQuestBackY = GetPrivateProfileIntA("TeleportBack", "Y", 259273, "./Configs/AreaQuests.txt");
	ACooldown = GetPrivateProfileIntA("Cooldown", "Time", 15, "./Configs/AreaQuests.txt");


	MystLevel = GetPrivateProfileIntA("Mystery", "MinLevel", 70, "./Configs/NewMystery.txt");
	MystLevelMax = GetPrivateProfileIntA("Mystery", "MaxLevel", 100, "./Configs/NewMystery.txt");
	NewMystEnable = GetPrivateProfileIntA("Mystery", "Enable", 0, "./Configs/NewMystery.txt");
	NewMystReset = GetPrivateProfileIntA("Mystery", "ResetItem", 0, "./Configs/NewMystery.txt");

	MystPAtkQ = GetPrivateProfileIntA("PhyAttack", "QuestIndex", 0, "./Configs/NewMystery.txt");
	MystPAtkS = GetPrivateProfileIntA("PhyAttack", "SysKey", 0, "./Configs/NewMystery.txt");

	MystMAtkQ = GetPrivateProfileIntA("MagAttack", "QuestIndex", 0, "./Configs/NewMystery.txt");
	MystMAtkS = GetPrivateProfileIntA("MagAttack", "SysKey", 0, "./Configs/NewMystery.txt");

	MystHPQ = GetPrivateProfileIntA("Health", "QuestIndex", 0, "./Configs/NewMystery.txt");
	MystHPS = GetPrivateProfileIntA("Health", "SysKey", 0, "./Configs/NewMystery.txt");

	MystDefQ = GetPrivateProfileIntA("Defense", "QuestIndex", 0, "./Configs/NewMystery.txt");
	MystDefS = GetPrivateProfileIntA("Defense", "SysKey", 0, "./Configs/NewMystery.txt");

	MystEVAQ = GetPrivateProfileIntA("Evasion", "QuestIndex", 0, "./Configs/NewMystery.txt");
	MystEVAS = GetPrivateProfileIntA("Evasion", "SysKey", 0, "./Configs/NewMystery.txt");

	MystOTPQ = GetPrivateProfileIntA("OnTargetPoint", "QuestIndex", 0, "./Configs/NewMystery.txt");
	MystOTPS = GetPrivateProfileIntA("OnTargetPoint", "SysKey", 0, "./Configs/NewMystery.txt");


	SkillTestAction = GetPrivateProfileIntA("Skill", "Action", 0, "./Configs/SkillTest.txt");
	SkillR1 = GetPrivateProfileIntA("Skill", "R1", 0, "./Configs/SkillTest.txt");
	SkillR2 = GetPrivateProfileIntA("Skill", "R2", 0, "./Configs/SkillTest.txt");
	SkillIndex = GetPrivateProfileIntA("Skill", "Index", 0, "./Configs/SkillTest.txt");
	SkillTimer = GetPrivateProfileIntA("Skill", "Timer", 0, "./Configs/SkillTest.txt");

	PeaceEvil = GetPrivateProfileIntA("PeaceEvil", "Active", 0, "./Configs/Hogwarts.txt");
	SlytherinQuest = GetPrivateProfileIntA("Quest", "Slytherin", 0, "./Configs/Hogwarts.txt");
	GryffindorQuest = GetPrivateProfileIntA("Quest", "Gryffindor", 0, "./Configs/Hogwarts.txt");
	RavenQuest = GetPrivateProfileIntA("Quest", "Ravenclaw", 0, "./Configs/Hogwarts.txt");
	HuffleQuest = GetPrivateProfileIntA("Quest", "Hufflepuff", 0, "./Configs/Hogwarts.txt");
	SlytherinColor = GetPrivateProfileIntA("Color", "Slytherin", 0, "./Configs/Hogwarts.txt");
	GryffindorColor = GetPrivateProfileIntA("Color", "Gryffindor", 0, "./Configs/Hogwarts.txt");
	RavenColor = GetPrivateProfileIntA("Color", "Ravenclaw", 0, "./Configs/Hogwarts.txt");
	HuffleColor = GetPrivateProfileIntA("Color", "Hufflepuff", 0, "./Configs/Hogwarts.txt");
	SlytherinGCIndex = GetPrivateProfileIntA("TimerCoin", "Slytherin", 0, "./Configs/Hogwarts.txt");
	GryffindorGCIndex = GetPrivateProfileIntA("TimerCoin", "Gryffindor", 0, "./Configs/Hogwarts.txt");
	RavenGCIndex = GetPrivateProfileIntA("TimerCoin", "Ravenclaw", 0, "./Configs/Hogwarts.txt");
	HuffleGCIndex = GetPrivateProfileIntA("TimerCoin", "Hufflepuff", 0, "./Configs/Hogwarts.txt");


	TimerEP = GetPrivateProfileIntA("TimerCoin", "Timer", 0, "./Configs/Hogwarts.txt");
	AmountEP = GetPrivateProfileIntA("TimerCoin", "Amount", 1, "./Configs/Hogwarts.txt");
	GetPrivateProfileStringA("LoginMessage", "Slytherin", "", SlytherinLoginMSG, 512, "./Configs/Hogwarts.txt");
	GetPrivateProfileStringA("LoginMessage", "Gryffindor", "", GryffindorLoginMSG, 512, "./Configs/Hogwarts.txt");
	GetPrivateProfileStringA("LoginMessage", "Ravenclaw", "", RavenclawLoginMSG, 512, "./Configs/Hogwarts.txt");
	GetPrivateProfileStringA("LoginMessage", "Hufflepuff", "", HufflepuffLoginMSG, 512, "./Configs/Hogwarts.txt");

	PECSlytherin = GetPrivateProfileIntA("LoginMessage", "ColorSlytherin", 1, "./Configs/Hogwarts.txt");
	PECGryffindor = GetPrivateProfileIntA("LoginMessage", "ColorGryffindor", 1, "./Configs/Hogwarts.txt");
	PECRavenclaw = GetPrivateProfileIntA("LoginMessage", "ColorRavenclaw", 1, "./Configs/Hogwarts.txt");
	PECHufflepuff = GetPrivateProfileIntA("LoginMessage", "ColorHufflepuff", 1, "./Configs/Hogwarts.txt");

	PELoginHTML = GetPrivateProfileIntA("LoginImage", "HTML", 0, "./Configs/Hogwarts.txt");
	HouseRewardTime = GetPrivateProfileIntA("HouseRank", "Time", 0, "./Configs/Hogwarts.txt");
	HouseReward = GetPrivateProfileIntA("HouseRank", "RewardIndex", 0, "./Configs/Hogwarts.txt");
	HouseRewardAmount = GetPrivateProfileIntA("HouseRank", "RewardAmount", 0, "./Configs/Hogwarts.txt");

	// Honor Rank Buff
	GetPrivateProfileStringA("Recruit", "Effect", "", Honor1, 512, "./Configs/HonorEffects.txt");
	GetPrivateProfileStringA("Private", "Effect", "", Honor2, 512, "./Configs/HonorEffects.txt");
	GetPrivateProfileStringA("Specialist", "Effect", "", Honor3, 512, "./Configs/HonorEffects.txt");
	GetPrivateProfileStringA("Corporal", "Effect", "", Honor4, 512, "./Configs/HonorEffects.txt");
	GetPrivateProfileStringA("Sergeant", "Effect", "", Honor5, 512, "./Configs/HonorEffects.txt");
	GetPrivateProfileStringA("Lieutenant", "Effect", "", Honor6, 512, "./Configs/HonorEffects.txt");
	GetPrivateProfileStringA("Captain", "Effect", "", Honor7, 512, "./Configs/HonorEffects.txt");
	GetPrivateProfileStringA("Major", "Effect", "", Honor8, 512, "./Configs/HonorEffects.txt");
	GetPrivateProfileStringA("Colonel", "Effect", "", Honor9, 512, "./Configs/HonorEffects.txt");
	GetPrivateProfileStringA("General", "Effect", "", Honor10, 512, "./Configs/HonorEffects.txt");

	HonorTimer = GetPrivateProfileIntA("Timer", "Seconds", 3, "./Configs/HonorEffects.txt");

	Honor1Sys = GetPrivateProfileIntA("Recruit", "SysKey", 0, "./Configs/HonorEffects.txt");
	Honor2Sys = GetPrivateProfileIntA("Private", "SysKey", 0, "./Configs/HonorEffects.txt");
	Honor3Sys = GetPrivateProfileIntA("Specialist", "SysKey", 0, "./Configs/HonorEffects.txt");
	Honor4Sys = GetPrivateProfileIntA("Corporal", "SysKey", 0, "./Configs/HonorEffects.txt");
	Honor5Sys = GetPrivateProfileIntA("Sergeant", "SysKey", 0, "./Configs/HonorEffects.txt");
	Honor6Sys = GetPrivateProfileIntA("Lieutenant", "SysKey", 0, "./Configs/HonorEffects.txt");
	Honor7Sys = GetPrivateProfileIntA("Captain", "SysKey", 0, "./Configs/HonorEffects.txt");
	Honor8Sys = GetPrivateProfileIntA("Major", "SysKey", 0, "./Configs/HonorEffects.txt");
	Honor9Sys = GetPrivateProfileIntA("Colonel", "SysKey", 0, "./Configs/HonorEffects.txt");
	Honor10Sys = GetPrivateProfileIntA("General", "SysKey", 0, "./Configs/HonorEffects.txt");

	Honor1Stats = GetPrivateProfileIntA("Recruit", "Stats", 0, "./Configs/HonorEffects.txt");
	Honor2Stats = GetPrivateProfileIntA("Private", "Stats", 0, "./Configs/HonorEffects.txt");
	Honor3Stats = GetPrivateProfileIntA("Specialist", "Stats", 0, "./Configs/HonorEffects.txt");
	Honor4Stats = GetPrivateProfileIntA("Corporal", "Stats", 0, "./Configs/HonorEffects.txt");
	Honor5Stats = GetPrivateProfileIntA("Sergeant", "Stats", 0, "./Configs/HonorEffects.txt");
	Honor6Stats = GetPrivateProfileIntA("Lieutenant", "Stats", 0, "./Configs/HonorEffects.txt");
	Honor7Stats = GetPrivateProfileIntA("Captain", "Stats", 0, "./Configs/HonorEffects.txt");
	Honor8Stats = GetPrivateProfileIntA("Major", "Stats", 0, "./Configs/HonorEffects.txt");
	Honor9Stats = GetPrivateProfileIntA("Colonel", "Stats", 0, "./Configs/HonorEffects.txt");
	Honor10Stats = GetPrivateProfileIntA("General", "Stats", 0, "./Configs/HonorEffects.txt");

	Honor1PVE = GetPrivateProfileIntA("Recruit", "PVEDmg", 0, "./Configs/HonorEffects.txt");
	Honor2PVE = GetPrivateProfileIntA("Private", "PVEDmg", 0, "./Configs/HonorEffects.txt");
	Honor3PVE = GetPrivateProfileIntA("Specialist", "PVEDmg", 0, "./Configs/HonorEffects.txt");
	Honor4PVE = GetPrivateProfileIntA("Corporal", "PVEDmg", 0, "./Configs/HonorEffects.txt");
	Honor5PVE = GetPrivateProfileIntA("Sergeant", "PVEDmg", 0, "./Configs/HonorEffects.txt");
	Honor6PVE = GetPrivateProfileIntA("Lieutenant", "PVEDmg", 0, "./Configs/HonorEffects.txt");
	Honor7PVE = GetPrivateProfileIntA("Captain", "PVEDmg", 0, "./Configs/HonorEffects.txt");
	Honor8PVE = GetPrivateProfileIntA("Major", "PVEDmg", 0, "./Configs/HonorEffects.txt");
	Honor9PVE = GetPrivateProfileIntA("Colonel", "PVEDmg", 0, "./Configs/HonorEffects.txt");
	Honor10PVE = GetPrivateProfileIntA("General", "PVEDmg", 0, "./Configs/HonorEffects.txt");

	Honor1PVP = GetPrivateProfileIntA("Recruit", "PVPDmg", 0, "./Configs/HonorEffects.txt");
	Honor2PVP = GetPrivateProfileIntA("Private", "PVPDmg", 0, "./Configs/HonorEffects.txt");
	Honor3PVP = GetPrivateProfileIntA("Specialist", "PVPDmg", 0, "./Configs/HonorEffects.txt");
	Honor4PVP = GetPrivateProfileIntA("Corporal", "PVPDmg", 0, "./Configs/HonorEffects.txt");
	Honor5PVP = GetPrivateProfileIntA("Sergeant", "PVPDmg", 0, "./Configs/HonorEffects.txt");
	Honor6PVP = GetPrivateProfileIntA("Lieutenant", "PVPDmg", 0, "./Configs/HonorEffects.txt");
	Honor7PVP = GetPrivateProfileIntA("Captain", "PVPDmg", 0, "./Configs/HonorEffects.txt");
	Honor8PVP = GetPrivateProfileIntA("Major", "PVPDmg", 0, "./Configs/HonorEffects.txt");
	Honor9PVP = GetPrivateProfileIntA("Colonel", "PVPDmg", 0, "./Configs/HonorEffects.txt");
	Honor10PVP = GetPrivateProfileIntA("General", "PVPDmg", 0, "./Configs/HonorEffects.txt");

	Honor1Fatal = GetPrivateProfileIntA("Recruit", "FatalDmg", 0, "./Configs/HonorEffects.txt");
	Honor2Fatal = GetPrivateProfileIntA("Private", "FatalDmg", 0, "./Configs/HonorEffects.txt");
	Honor3Fatal = GetPrivateProfileIntA("Specialist", "FatalDmg", 0, "./Configs/HonorEffects.txt");
	Honor4Fatal = GetPrivateProfileIntA("Corporal", "FatalDmg", 0, "./Configs/HonorEffects.txt");
	Honor5Fatal = GetPrivateProfileIntA("Sergeant", "FatalDmg", 0, "./Configs/HonorEffects.txt");
	Honor6Fatal = GetPrivateProfileIntA("Lieutenant", "FatalDmg", 0, "./Configs/HonorEffects.txt");
	Honor7Fatal = GetPrivateProfileIntA("Captain", "FatalDmg", 0, "./Configs/HonorEffects.txt");
	Honor8Fatal = GetPrivateProfileIntA("Major", "FatalDmg", 0, "./Configs/HonorEffects.txt");
	Honor9Fatal = GetPrivateProfileIntA("Colonel", "FatalDmg", 0, "./Configs/HonorEffects.txt");
	Honor10Fatal = GetPrivateProfileIntA("General", "FatalDmg", 0, "./Configs/HonorEffects.txt");

	Honor1EB = GetPrivateProfileIntA("Recruit", "ExplosiveBlow", 0, "./Configs/HonorEffects.txt");
	Honor2EB = GetPrivateProfileIntA("Private", "ExplosiveBlow", 0, "./Configs/HonorEffects.txt");
	Honor3EB = GetPrivateProfileIntA("Specialist", "ExplosiveBlow", 0, "./Configs/HonorEffects.txt");
	Honor4EB = GetPrivateProfileIntA("Corporal", "ExplosiveBlow", 0, "./Configs/HonorEffects.txt");
	Honor5EB = GetPrivateProfileIntA("Sergeant", "ExplosiveBlow", 0, "./Configs/HonorEffects.txt");
	Honor6EB = GetPrivateProfileIntA("Lieutenant", "ExplosiveBlow", 0, "./Configs/HonorEffects.txt");
	Honor7EB = GetPrivateProfileIntA("Captain", "ExplosiveBlow", 0, "./Configs/HonorEffects.txt");
	Honor8EB = GetPrivateProfileIntA("Major", "ExplosiveBlow", 0, "./Configs/HonorEffects.txt");
	Honor9EB = GetPrivateProfileIntA("Colonel", "ExplosiveBlow", 0, "./Configs/HonorEffects.txt");
	Honor10EB = GetPrivateProfileIntA("General", "ExplosiveBlow", 0, "./Configs/HonorEffects.txt");

	SlytherinDieX = GetPrivateProfileIntA("DeathSpawn", "SlytherinX", 257514, "./Configs/Hogwarts.txt");
	SlytherinDieY = GetPrivateProfileIntA("DeathSpawn", "SlytherinY", 259273, "./Configs/Hogwarts.txt");
	SlytherinDieZ = GetPrivateProfileIntA("DeathSpawn", "SlytherinZ", 0, "./Configs/Hogwarts.txt");

	GryffindorDieX = GetPrivateProfileIntA("DeathSpawn", "GryffindorX", 257514, "./Configs/Hogwarts.txt");
	GryffindorDieY = GetPrivateProfileIntA("DeathSpawn", "GryffindorY", 259273, "./Configs/Hogwarts.txt");
	GryffindorDieZ = GetPrivateProfileIntA("DeathSpawn", "GryffindorZ", 0, "./Configs/Hogwarts.txt");

	RavenDieX = GetPrivateProfileIntA("DeathSpawn", "RavenX", 257514, "./Configs/Hogwarts.txt");
	RavenDieY = GetPrivateProfileIntA("DeathSpawn", "RavenY", 259273, "./Configs/Hogwarts.txt");
	RavenDieZ = GetPrivateProfileIntA("DeathSpawn", "RavenZ", 0, "./Configs/Hogwarts.txt");

	HuffleDieX = GetPrivateProfileIntA("DeathSpawn", "HuffleX", 257514, "./Configs/Hogwarts.txt");
	HuffleDieY = GetPrivateProfileIntA("DeathSpawn", "HuffleY", 259273, "./Configs/Hogwarts.txt");
	HuffleDieZ = GetPrivateProfileIntA("DeathSpawn", "HuffleZ", 0, "./Configs/Hogwarts.txt");

	Slytherin0 = GetPrivateProfileIntA("SlytherinTags", "None", 0, "./Configs/Hogwarts.txt");
	Slytherin1 = GetPrivateProfileIntA("SlytherinTags", "Recruit", 0, "./Configs/Hogwarts.txt");
	Slytherin2 = GetPrivateProfileIntA("SlytherinTags", "Private", 0, "./Configs/Hogwarts.txt");
	Slytherin3 = GetPrivateProfileIntA("SlytherinTags", "Specialist", 0, "./Configs/Hogwarts.txt");
	Slytherin4 = GetPrivateProfileIntA("SlytherinTags", "Corporal", 0, "./Configs/Hogwarts.txt");
	Slytherin5 = GetPrivateProfileIntA("SlytherinTags", "Sergeant", 0, "./Configs/Hogwarts.txt");
	Slytherin6 = GetPrivateProfileIntA("SlytherinTags", "Lieutenant", 0, "./Configs/Hogwarts.txt");
	Slytherin7 = GetPrivateProfileIntA("SlytherinTags", "Captain", 0, "./Configs/Hogwarts.txt");
	Slytherin8 = GetPrivateProfileIntA("SlytherinTags", "Major", 0, "./Configs/Hogwarts.txt");
	Slytherin9 = GetPrivateProfileIntA("SlytherinTags", "Colonel", 0, "./Configs/Hogwarts.txt");
	Slytherin10 = GetPrivateProfileIntA("SlytherinTags", "General", 0, "./Configs/Hogwarts.txt");

	Hufflepuff0 = GetPrivateProfileIntA("HufflepuffTags", "None", 0, "./Configs/Hogwarts.txt");
	Hufflepuff1 = GetPrivateProfileIntA("HufflepuffTags", "Recruit", 0, "./Configs/Hogwarts.txt");
	Hufflepuff2 = GetPrivateProfileIntA("HufflepuffTags", "Private", 0, "./Configs/Hogwarts.txt");
	Hufflepuff3 = GetPrivateProfileIntA("HufflepuffTags", "Specialist", 0, "./Configs/Hogwarts.txt");
	Hufflepuff4 = GetPrivateProfileIntA("HufflepuffTags", "Corporal", 0, "./Configs/Hogwarts.txt");
	Hufflepuff5 = GetPrivateProfileIntA("HufflepuffTags", "Sergeant", 0, "./Configs/Hogwarts.txt");
	Hufflepuff6 = GetPrivateProfileIntA("HufflepuffTags", "Lieutenant", 0, "./Configs/Hogwarts.txt");
	Hufflepuff7 = GetPrivateProfileIntA("HufflepuffTags", "Captain", 0, "./Configs/Hogwarts.txt");
	Hufflepuff8 = GetPrivateProfileIntA("HufflepuffTags", "Major", 0, "./Configs/Hogwarts.txt");
	Hufflepuff9 = GetPrivateProfileIntA("HufflepuffTags", "Colonel", 0, "./Configs/Hogwarts.txt");
	Hufflepuff10 = GetPrivateProfileIntA("HufflepuffTags", "General", 0, "./Configs/Hogwarts.txt");

	Gryffindor0 = GetPrivateProfileIntA("GryffindorTags", "None", 0, "./Configs/Hogwarts.txt");
	Gryffindor1 = GetPrivateProfileIntA("GryffindorTags", "Recruit", 0, "./Configs/Hogwarts.txt");
	Gryffindor2 = GetPrivateProfileIntA("GryffindorTags", "Private", 0, "./Configs/Hogwarts.txt");
	Gryffindor3 = GetPrivateProfileIntA("GryffindorTags", "Specialist", 0, "./Configs/Hogwarts.txt");
	Gryffindor4 = GetPrivateProfileIntA("GryffindorTags", "Corporal", 0, "./Configs/Hogwarts.txt");
	Gryffindor5 = GetPrivateProfileIntA("GryffindorTags", "Sergeant", 0, "./Configs/Hogwarts.txt");
	Gryffindor6 = GetPrivateProfileIntA("GryffindorTags", "Lieutenant", 0, "./Configs/Hogwarts.txt");
	Gryffindor7 = GetPrivateProfileIntA("GryffindorTags", "Captain", 0, "./Configs/Hogwarts.txt");
	Gryffindor8 = GetPrivateProfileIntA("GryffindorTags", "Major", 0, "./Configs/Hogwarts.txt");
	Gryffindor9 = GetPrivateProfileIntA("GryffindorTags", "Colonel", 0, "./Configs/Hogwarts.txt");
	Gryffindor10 = GetPrivateProfileIntA("GryffindorTags", "General", 0, "./Configs/Hogwarts.txt");

	Ravenclaw0 = GetPrivateProfileIntA("RavenclawTags", "None", 0, "./Configs/Hogwarts.txt");
	Ravenclaw1 = GetPrivateProfileIntA("RavenclawTags", "Recruit", 0, "./Configs/Hogwarts.txt");
	Ravenclaw2 = GetPrivateProfileIntA("RavenclawTags", "Private", 0, "./Configs/Hogwarts.txt");
	Ravenclaw3 = GetPrivateProfileIntA("RavenclawTags", "Specialist", 0, "./Configs/Hogwarts.txt");
	Ravenclaw4 = GetPrivateProfileIntA("RavenclawTags", "Corporal", 0, "./Configs/Hogwarts.txt");
	Ravenclaw5 = GetPrivateProfileIntA("RavenclawTags", "Sergeant", 0, "./Configs/Hogwarts.txt");
	Ravenclaw6 = GetPrivateProfileIntA("RavenclawTags", "Lieutenant", 0, "./Configs/Hogwarts.txt");
	Ravenclaw7 = GetPrivateProfileIntA("RavenclawTags", "Captain", 0, "./Configs/Hogwarts.txt");
	Ravenclaw8 = GetPrivateProfileIntA("RavenclawTags", "Major", 0, "./Configs/Hogwarts.txt");
	Ravenclaw9 = GetPrivateProfileIntA("RavenclawTags", "Colonel", 0, "./Configs/Hogwarts.txt");
	Ravenclaw10 = GetPrivateProfileIntA("RavenclawTags", "General", 0, "./Configs/Hogwarts.txt");

	PKKillActive = GetPrivateProfileIntA("RandomItem", "Active", 0, "./Configs/PKKill.txt");
	PKKillPlayer = GetPrivateProfileIntA("RandomItem", "AssassinOnly", 1, "./Configs/PKKill.txt");
	PKKillChance = GetPrivateProfileIntA("RandomItem", "AssassinChance", 1000, "./Configs/PKKill.txt");
	PKKillPlayerChance = GetPrivateProfileIntA("RandomItem", "PlayerChance", 1000, "./Configs/PKKill.txt");
	PKLvlDiff = GetPrivateProfileIntA("RandomItem", "LevelDiff", 10, "./Configs/PKKill.txt");
	AssassinLimit = GetPrivateProfileIntA("Assassin", "LevelDiff", 10, "./Configs/PKKill.txt");
	AssassinParty = GetPrivateProfileIntA("Assassin", "PartyEnable", 0, "./Configs/PKKill.txt");

	iceStoneMax = GetPrivateProfileIntA("IceStone", "MaxTime", 10, "./Configs/Mix.txt");
	iceStoneValue = GetPrivateProfileIntA("IceStone", "Value", 10, "./Configs/Mix.txt");

	GetPrivateProfileStringA("Effects", "Ice", "", IceStoneEffect, 512, "./Configs/Mix.txt");
	GetPrivateProfileStringA("Effects", "Light", "", LightningStoneEffect, 512, "./Configs/Mix.txt");


	PSActive = GetPrivateProfileIntA("PointSystem", "Active", 0, "./Configs/PKKill.txt");
	PSLimit = GetPrivateProfileIntA("PointSystem", "Limit", 20, "./Configs/PKKill.txt");
	KrPSsysReward = GetPrivateProfileIntA("PointSystem", "KillerRewardID", 0, "./Configs/PKKill.txt");
	KdPSsysReward = GetPrivateProfileIntA("PointSystem", "KilledRewardID", 0, "./Configs/PKKill.txt");

	ImmortalEffect = GetPrivateProfileIntA("Immortal", "Percentage", 100, "./Systems/Immortal.txt");
	ImmortalPVP = GetPrivateProfileIntA("Immortal", "PVPEnable", 0, "./Systems/Immortal.txt");
	ImmortalSBName = GetPrivateProfileIntA("Immortal", "SkillBuffMsg", 1660, "./Systems/Immortal.txt");
	ImmortalSBKey = GetPrivateProfileIntA("Immortal", "SkillBuffKey", 191, "./Systems/Immortal.txt");

	EggPercentage = GetPrivateProfileIntA("EggEvent", "Percentage", 100, "./Systems/EggEvent.txt");
	EggSBKey = GetPrivateProfileIntA("EggEvent", "SBKey", 965, "./Systems/EggEvent.txt");
	EggSBName = GetPrivateProfileIntA("EggEvent", "SBName", 4408, "./Systems/EggEvent.txt");

	DamagePercentage = GetPrivateProfileIntA("Damage", "Percentage", 100, "./Systems/Damage.txt");
	DamageSBKey = GetPrivateProfileIntA("Damage", "SBKey", 650, "./Systems/Damage.txt");
	DamageSBName = GetPrivateProfileIntA("Damage", "SBName", 6150, "./Systems/Damage.txt");

	FireStormVThief = GetPrivateProfileIntA("FireStorm", "Activate", 1, "./Configs/Protection.txt");


	ExpansionIndex = GetPrivateProfileIntA("InvExpansion", "Index", 3360, "./Configs/ItemUse.txt");
	ExpansionAmount = GetPrivateProfileIntA("InvExpansion", "Amount", 100, "./Configs/ItemUse.txt");
	ExtensionTime = GetPrivateProfileIntA("InvExpansion", "Time", 1296000, "./Configs/ItemUse.txt");

	ShopLevelLimit = GetPrivateProfileIntA("LevelLimit", "Shop", 11, "./Configs/Protection.txt");
	TradeLevelLimit = GetPrivateProfileIntA("LevelLimit", "Trade", 11, "./Configs/Protection.txt");
	ChannelActivated = GetPrivateProfileIntA("Channels", "Activate", 1, "./Configs/Channel.txt");

	RewardHWID = GetPrivateProfileIntA("LimitCheck", "HWID", 0, "./Configs/Rewards.txt");

	MLMMax = GetPrivateProfileIntA("Student", "Max", 20, "./Configs/MLM.txt");
	MLMStudentLevel = GetPrivateProfileIntA("Student", "MaxLevel", 15, "./Configs/MLM.txt");
	MLMTeacherLevel = GetPrivateProfileIntA("Teacher", "MinLevel", 16, "./Configs/MLM.txt");
	MLMLevel1Reward = GetPrivateProfileIntA("Reward", "StarterEnable", 1, "./Configs/MLM.txt");
	MLMMoneyReward = GetPrivateProfileIntA("Reward", "MoneyEnable", 1, "./Configs/MLM.txt");

	GuildEXPGrade4 = GetPrivateProfileIntA("EXP", "Level4", 16000000, "./Configs/Guild.txt");
	GuildEXPGrade3 = GetPrivateProfileIntA("EXP", "Level3", 7800000, "./Configs/Guild.txt");
	GuildEXPGrade2 = GetPrivateProfileIntA("EXP", "Level2", 2400000, "./Configs/Guild.txt");
	MemberFull4 = GetPrivateProfileIntA("MaxMembers", "Level4", 54, "./Configs/Guild.txt");
	MemberFull3 = GetPrivateProfileIntA("MaxMembers", "Level3", 40, "./Configs/Guild.txt");
	MemberFull2 = GetPrivateProfileIntA("MaxMembers", "Level2", 26, "./Configs/Guild.txt");
	MemberFull1 = GetPrivateProfileIntA("MaxMembers", "Level1", 12, "./Configs/Guild.txt");
	TempMemberFull = GetPrivateProfileIntA("MaxMembers", "TempMember", 10, "./Configs/Guild.txt");
	AllyMemberFull = GetPrivateProfileIntA("MaxMembers", "Alliance", 8, "./Configs/Guild.txt");
	MaxTimeAlly = GetPrivateProfileIntA("Alliance", "MaxDays", 15, "./Configs/Guild.txt");
	GuildColors = GetPrivateProfileIntA("GuildColors", "Activate", 0, "./Configs/Guild.txt");
	LeaderColor = GetPrivateProfileIntA("GuildColors", "Leader", 1, "./Configs/Guild.txt");
	SubLeaderColor = GetPrivateProfileIntA("GuildColors", "SubLeader", 5, "./Configs/Guild.txt");
	ChiefColor = GetPrivateProfileIntA("GuildColors", "Chief", 3, "./Configs/Guild.txt");

	Insanity = GetPrivateProfileIntA("Insanity", "Rate", 0, "./Configs/Rates.txt");
	Thunder = GetPrivateProfileIntA("Thunder", "Rate", 0, "./Configs/Rates.txt");
	Violent = GetPrivateProfileIntA("Violent", "Rate", 0, "./Configs/Rates.txt");
	Storm = GetPrivateProfileIntA("Storm", "Rate", 0, "./Configs/Rates.txt");
	Ancient = GetPrivateProfileIntA("Ancient", "Rate", 0, "./Configs/Rates.txt");
	Perfo = GetPrivateProfileIntA("Perforation", "Rate", 0, "./Configs/Rates.txt");
	Gun = GetPrivateProfileIntA("Gun", "Rate", 0, "./Configs/Rates.txt");
	VODConf = GetPrivateProfileIntA("VOD", "MinLvl", 80, "./Configs/Area.txt");
	Tries = GetPrivateProfileIntA("Buff", "Tries", 20, "./Configs/Protection.txt");
	GetPrivateProfileStringA("AntiKs", "Enable", "false", AntiKsCheck, 50, "./Configs/AntiKs.txt");
	AntiKSTime = GetPrivateProfileIntA("AntiKs", "Time", 0, "./Configs/AntiKs.txt");

	KVK = GetPrivateProfileIntA("KnightVsKnight", "Value", 0, "./Configs/PlayerVsPlayer.txt");
	KVA = GetPrivateProfileIntA("KnightVsArcher", "Value", 0, "./Configs/PlayerVsPlayer.txt");
	KVM = GetPrivateProfileIntA("KnightVsMage", "Value", 0, "./Configs/PlayerVsPlayer.txt");
	KVT = GetPrivateProfileIntA("KnightVsThief", "Value", 0, "./Configs/PlayerVsPlayer.txt");
	KVS = GetPrivateProfileIntA("KnightVsShaman", "Value", 0, "./Configs/PlayerVsPlayer.txt");

	AVK = GetPrivateProfileIntA("ArcherVsKnight", "Value", 0, "./Configs/PlayerVsPlayer.txt");
	AVA = GetPrivateProfileIntA("ArcherVsArcher", "Value", 0, "./Configs/PlayerVsPlayer.txt");
	AVM = GetPrivateProfileIntA("ArcherVsMage", "Value", 0, "./Configs/PlayerVsPlayer.txt");
	AVT = GetPrivateProfileIntA("ArcherVsThief", "Value", 0, "./Configs/PlayerVsPlayer.txt");
	AVS = GetPrivateProfileIntA("ArcherVsShaman", "Value", 0, "./Configs/PlayerVsPlayer.txt");

	MVK = GetPrivateProfileIntA("MageVsKnight", "Value", 0, "./Configs/PlayerVsPlayer.txt");
	MVA = GetPrivateProfileIntA("MageVsArcher", "Value", 0, "./Configs/PlayerVsPlayer.txt");
	MVM = GetPrivateProfileIntA("MageVsMage", "Value", 0, "./Configs/PlayerVsPlayer.txt");
	MVT = GetPrivateProfileIntA("MageVsThief", "Value", 0, "./Configs/PlayerVsPlayer.txt");
	MVS = GetPrivateProfileIntA("MageVsShaman", "Value", 0, "./Configs/PlayerVsPlayer.txt");

	TVK = GetPrivateProfileIntA("ThiefVsKnight", "Value", 0, "./Configs/PlayerVsPlayer.txt");
	TVA = GetPrivateProfileIntA("ThiefVsArcher", "Value", 0, "./Configs/PlayerVsPlayer.txt");
	TVM = GetPrivateProfileIntA("ThiefVsMage", "Value", 0, "./Configs/PlayerVsPlayer.txt");
	TVT = GetPrivateProfileIntA("ThiefVsThief", "Value", 0, "./Configs/PlayerVsPlayer.txt");
	TVS = GetPrivateProfileIntA("ThiefVsShaman", "Value", 0, "./Configs/PlayerVsPlayer.txt");

	SVK = GetPrivateProfileIntA("ShamanVsKnight", "Value", 0, "./Configs/PlayerVsPlayer.txt");
	SVA = GetPrivateProfileIntA("ShamanVsArcher", "Value", 0, "./Configs/PlayerVsPlayer.txt");
	SVM = GetPrivateProfileIntA("ShamanVsMage", "Value", 0, "./Configs/PlayerVsPlayer.txt");
	SVT = GetPrivateProfileIntA("ShamanVsThief", "Value", 0, "./Configs/PlayerVsPlayer.txt");
	SVS = GetPrivateProfileIntA("ShamanVsShaman", "Value", 0, "./Configs/PlayerVsPlayer.txt");
	JewelIndex = GetPrivateProfileIntA("Jewel", "Index", 3360, "./Configs/Protection.txt");
	levellimit = GetPrivateProfileIntA("Limit", "Level", 255, "./Configs/Protection.txt");
	//new
	FishLimit = GetPrivateProfileIntA("Limit", "FishingPerPC", 0, "./Configs/Protection.txt");
	ShoppingLimit = GetPrivateProfileIntA("Limit", "ShoppingPerPC", 0, "./Configs/Protection.txt");
	MiningPCLimit = GetPrivateProfileIntA("Limit", "MiningPerPC", 0, "./Configs/Protection.txt");
	AuctionLimit = GetPrivateProfileIntA("Limit", "Auction", 0, "./Configs/Protection.txt");
	GuildLimit = GetPrivateProfileIntA("Limit", "GuildMembers", 64, "./Configs/Protection.txt");
	TransmigrationLimit = GetPrivateProfileIntA("Limit", "Transmigration", 0, "./Configs/Protection.txt");
	MiningAreaLimit = GetPrivateProfileIntA("Area", "Limit", 1, "./Configs/Mining.txt");
	namePadIndex = GetPrivateProfileIntA("NamePad", "Index", 3360, "./Configs/Protection.txt");
	namePadPrice = GetPrivateProfileIntA("NamePad", "Price", 6, "./Configs/Protection.txt");
	namePadDuration = GetPrivateProfileIntA("NamePad", "Days", 7, "./Configs/Protection.txt");
	//endnew
	BossIndex = GetPrivateProfileIntA("Monster", "Index", 0, "./Systems/Boss.txt");
	
	RaidQuest = GetPrivateProfileIntA("Quest", "Index", 0, "./Systems/Raid.txt");
	RaidLevel = GetPrivateProfileIntA("Limit", "Level", 1, "./Systems/Raid.txt");
	RaidItem = GetPrivateProfileIntA("Requirement", "Item", 0, "./Systems/Raid.txt");
	RaidItemAmount = GetPrivateProfileIntA("Requirement", "Amount", 0, "./Systems/Raid.txt");
	RaidMap = GetPrivateProfileIntA("Map", "Index", 0, "./Systems/Raid.txt");
	GetPrivateProfileStringA("Start", "Time", "true", RaidTime, 50, "./Systems/Raid.txt");
	RaidHonor = GetPrivateProfileIntA("PerRound", "HonorPoint", 0, "./Systems/Raid.txt");
	RaidRP = GetPrivateProfileIntA("PerRound", "RewardPoint", 0, "./Systems/Raid.txt");
	Raid1 = GetPrivateProfileIntA("Round1", "Monster", 0, "./Systems/Raid.txt");
	Raid2 = GetPrivateProfileIntA("Round2", "Monster", 0, "./Systems/Raid.txt");
	Raid3 = GetPrivateProfileIntA("Round3", "Monster", 0, "./Systems/Raid.txt");
	Raid4 = GetPrivateProfileIntA("Round4", "Monster", 0, "./Systems/Raid.txt");
	Raid5 = GetPrivateProfileIntA("Round5", "Monster", 0, "./Systems/Raid.txt");
	Raid6 = GetPrivateProfileIntA("Round6", "Monster", 0, "./Systems/Raid.txt");
	Raid7 = GetPrivateProfileIntA("Round7", "Monster", 0, "./Systems/Raid.txt");
	Raid8 = GetPrivateProfileIntA("Round8", "Monster", 0, "./Systems/Raid.txt");
	Raid9 = GetPrivateProfileIntA("Round9", "Monster", 0, "./Systems/Raid.txt");
	RaidMini1 = GetPrivateProfileIntA("Round4", "MiniMonster", 0, "./Systems/Raid.txt");
	RaidMiniAmount1 = GetPrivateProfileIntA("Round4", "MiniAmount", 0, "./Systems/Raid.txt");
	RaidMini2 = GetPrivateProfileIntA("Round5", "MiniMonster", 0, "./Systems/Raid.txt");
	RaidMiniAmount2 = GetPrivateProfileIntA("Round5", "MiniAmount", 0, "./Systems/Raid.txt");
	RaidMini3 = GetPrivateProfileIntA("Round6", "MiniMonster", 0, "./Systems/Raid.txt");
	RaidMiniAmount3 = GetPrivateProfileIntA("Round6", "MiniAmount", 0, "./Systems/Raid.txt");
	RaidMini4 = GetPrivateProfileIntA("Round9", "MiniMonster", 0, "./Systems/Raid.txt");
	RaidMiniAmount4 = GetPrivateProfileIntA("Round9", "MiniAmount", 0, "./Systems/Raid.txt");
	RaidReward1 = GetPrivateProfileIntA("Round1", "Index", 0, "./Systems/Raid.txt");
	RaidReward2 = GetPrivateProfileIntA("Round2", "Index", 0, "./Systems/Raid.txt");
	RaidReward3 = GetPrivateProfileIntA("Round3", "Index", 0, "./Systems/Raid.txt");
	RaidReward4 = GetPrivateProfileIntA("Round4", "Index", 0, "./Systems/Raid.txt");
	RaidReward5 = GetPrivateProfileIntA("Round5", "Index", 0, "./Systems/Raid.txt");
	RaidReward6 = GetPrivateProfileIntA("Round6", "Index", 0, "./Systems/Raid.txt");
	RaidReward7 = GetPrivateProfileIntA("Round7", "Index", 0, "./Systems/Raid.txt");
	RaidReward8 = GetPrivateProfileIntA("Round8", "Index", 0, "./Systems/Raid.txt");
	RaidReward9 = GetPrivateProfileIntA("Round9", "Index", 0, "./Systems/Raid.txt");
	RaidAmount1 = GetPrivateProfileIntA("Round1", "Amount", 0, "./Systems/Raid.txt");
	RaidAmount2 = GetPrivateProfileIntA("Round2", "Amount", 0, "./Systems/Raid.txt");
	RaidAmount3 = GetPrivateProfileIntA("Round3", "Amount", 0, "./Systems/Raid.txt");
	RaidAmount4 = GetPrivateProfileIntA("Round4", "Amount", 0, "./Systems/Raid.txt");
	RaidAmount5 = GetPrivateProfileIntA("Round5", "Amount", 0, "./Systems/Raid.txt");
	RaidAmount6 = GetPrivateProfileIntA("Round6", "Amount", 0, "./Systems/Raid.txt");
	RaidAmount7 = GetPrivateProfileIntA("Round7", "Amount", 0, "./Systems/Raid.txt");
	RaidAmount8 = GetPrivateProfileIntA("Round8", "Amount", 0, "./Systems/Raid.txt");
	RaidAmount9 = GetPrivateProfileIntA("Round9", "Amount", 0, "./Systems/Raid.txt");
	VoteQuest = GetPrivateProfileIntA("Quest", "Index", 0, "./Systems/Vote.txt");
	VoteID = GetPrivateProfileIntA("Topofmmos", "ID", 1, "./Systems/Vote.txt");
	betAct = GetPrivateProfileIntA("Bet", "Active", 0, "./Systems/Bet.txt");
	betGeon = GetPrivateProfileIntA("Item", "Geons", 0, "./Systems/Bet.txt");
	betDona = GetPrivateProfileIntA("Item", "DC", 0, "./Systems/Bet.txt");
	betCoin = GetPrivateProfileIntA("Item", "Coin", 0, "./Systems/Bet.txt");
	betSuicide = GetPrivateProfileIntA("Suicide", "Disable", 0, "./Systems/Bet.txt");
	betSurrender = GetPrivateProfileIntA("Surrender", "Disable", 0, "./Systems/Bet.txt");
	LotAct = GetPrivateProfileIntA("Lottery", "Active", 0, "./Systems/Lottery.txt");
	LotQuest = GetPrivateProfileIntA("Quest", "Index", 4095, "./Systems/Lottery.txt");
	LotLevelMax = GetPrivateProfileIntA("Quest", "LevelMax", 255, "./Systems/Lottery.txt");
	LotLevelMin = GetPrivateProfileIntA("Quest", "LevelMin", 1, "./Systems/Lottery.txt");
	LotRQuest = GetPrivateProfileIntA("ReplyQuest", "Index", 4096, "./Systems/Lottery.txt");
	LotIndex = GetPrivateProfileIntA("Item", "Index", 31, "./Systems/Lottery.txt");
	LotAmount = GetPrivateProfileIntA("Item", "Amount", 10000, "./Systems/Lottery.txt");
	LottoAct = GetPrivateProfileIntA("Lotto", "Active", 0, "./Systems/Lotto.txt");
	LottoQuest = GetPrivateProfileIntA("Quest", "Index", 4098, "./Systems/Lotto.txt");
	ReplyLottoQuest = GetPrivateProfileIntA("ReplyQuest", "Index", 4098, "./Systems/Lotto.txt");
	LottoIndex = GetPrivateProfileIntA("Item", "Index", 31, "./Systems/Lotto.txt");
	LottoAmount = GetPrivateProfileIntA("Item", "Amount", 10000, "./Systems/Lotto.txt");
	LottoReward = GetPrivateProfileIntA("Reward", "WinnerRewardID", 0, "./Systems/Lotto.txt");
	PacketActive = GetPrivateProfileIntA("PacketHack", "Active", 0, "./Configs/PacketBlock.txt");
	PacketLimit = GetPrivateProfileIntA("PacketHack", "Limit", 0, "./Configs/PacketBlock.txt");
	PacketTime = GetPrivateProfileIntA("PacketHack", "Time", 0, "./Configs/PacketBlock.txt");
	PacketInBetween = GetPrivateProfileIntA("PacketHack", "Delay", 20, "./Configs/PacketBlock.txt");
	DBOutput = GetPrivateProfileIntA("Debugger", "Database", 0, "./Configs/Protection.txt");
	
	if (command)
		CDBSocket::Write(117, "d", DBOutput);

	packetDebugger = GetPrivateProfileIntA("Debugger", "Packets", 0, "./Configs/Protection.txt");
	questDebug = GetPrivateProfileIntA("Debugger", "Quests", 0, "./Configs/Protection.txt");
	chatDebug = GetPrivateProfileIntA("Debugger", "Chats", 0, "./Configs/Protection.txt");
	commandDebug = GetPrivateProfileIntA("Debugger", "Commands", 0, "./Configs/Protection.txt");
	skillDebug = GetPrivateProfileIntA("Debugger", "Skills", 0, "./Configs/Protection.txt");
	rangeDebug = GetPrivateProfileIntA("Debugger", "Range", 0, "./Configs/Protection.txt");
	loginDebug = GetPrivateProfileIntA("Debugger", "Logins", 0, "./Configs/Protection.txt");
	attackDebug = GetPrivateProfileIntA("Debugger", "Attack", 0, "./Configs/Protection.txt");
	HWIDBlock = GetPrivateProfileIntA("HWIDBlock", "ExtraBlock", 0, "./Configs/Protection.txt");
	EXPLimit = GetPrivateProfileIntA("MaxEXP", "Active", 0, "./Configs/Protection.txt");
	MaxEXP = GetPrivateProfileIntA("MaxEXP", "EXP", 2147483647, "./Configs/Protection.txt");
	PacketProtection = GetPrivateProfileIntA("PacketCheck", "Active", 1, "./Configs/Protection.txt");
	DNPCQ = GetPrivateProfileIntA("Quest", "Index", 0, "./Configs/DamageNPC.txt");
	DNPCRQ = GetPrivateProfileIntA("ReplyQuest", "Index", 0, "./Configs/DamageNPC.txt");
	DNPCDL = GetPrivateProfileIntA("Daily", "Limit", 0, "./Configs/DamageNPC.txt");
	DNPCII = GetPrivateProfileIntA("EventItem", "Index", 0, "./Configs/DamageNPC.txt");
	DNPCIA = GetPrivateProfileIntA("Item", "Amount", 0, "./Configs/DamageNPC.txt");
	DNPCDU = GetPrivateProfileIntA("Duration", "Seconds", 0, "./Configs/DamageNPC.txt");
	DNPCDD = GetPrivateProfileIntA("Delay", "Seconds", 0, "./Configs/DamageNPC.txt");
	SHMRK = GetPrivateProfileIntA("4thRisingKing", "PVPReduce", 1, "./Skills/Shaman.txt");
	SHMD = GetPrivateProfileIntA("Doggebi", "PVPReduce", 1, "./Skills/Shaman.txt");
	SHMSW = GetPrivateProfileIntA("SpiritWave", "PVPReduce", 1, "./Skills/Shaman.txt");
	SHMES = GetPrivateProfileIntA("ExplodingSpirit", "PVPReduce", 1, "./Skills/Shaman.txt");
	SHMSS = GetPrivateProfileIntA("SixSouls", "PVPReduce", 1, "./Skills/Shaman.txt");
	SHMC = GetPrivateProfileIntA("Collapse", "PVPReduce", 1, "./Skills/Shaman.txt");
	SHMME = GetPrivateProfileIntA("MentalBreakdown", "PVPReduce", 1, "./Skills/Shaman.txt");
	SHMDB = GetPrivateProfileIntA("DrainBlood", "PVPReduce", 1, "./Skills/Shaman.txt");
	SHMSP = GetPrivateProfileIntA("SoulBlow", "PVPReduce", 1, "./Skills/Shaman.txt");
	SHMSOP = GetPrivateProfileIntA("SpearOfPain", "PVPReduce", 1, "./Skills/Shaman.txt");
	SHMWOE = GetPrivateProfileIntA("WaveOfEmperor", "PVPReduce", 1, "./Skills/Shaman.txt");
	SHMAOB = GetPrivateProfileIntA("AmplificationOfBlood", "PVPReduce", 1, "./Skills/Shaman.txt");
	SHMTSP = GetPrivateProfileIntA("TheSoulsPenance", "PVPReduce", 1, "./Skills/Shaman.txt");
	SHMED = GetPrivateProfileIntA("ExecutiveDirector", "PVPReduce", 1, "./Skills/Shaman.txt");
	SHMGW = GetPrivateProfileIntA("GhostWindow", "PVPReduce", 1, "./Skills/Shaman.txt");
	SHMW = GetPrivateProfileIntA("Wave", "PVPReduce", 1, "./Skills/Shaman.txt");
	SHMGF = GetPrivateProfileIntA("GhostFlash", "PVPReduce", 1, "./Skills/Shaman.txt");
	SHMGK = GetPrivateProfileIntA("GhostKnife", "PVPReduce", 1, "./Skills/Shaman.txt");
	ShopJewelIndex = GetPrivateProfileIntA("ItemShopIndex", "Jewel", 0, "./Configs/ItemShop.txt");
	ShopGoldIndex = GetPrivateProfileIntA("ItemShopIndex", "GoldKC", 0, "./Configs/ItemShop.txt");
	ShopSilverIndex = GetPrivateProfileIntA("ItemShopIndex", "SilverKC", 0, "./Configs/ItemShop.txt");
	ConfigPVPMaxDmg = GetPrivateProfileIntA("PVPMaxDamage", "Damage", 100000, "./Configs/Protection.txt");
	CWTCEH = GetPrivateProfileIntA("CastleWar", "EndHour", 0, "./Configs/Protection.txt");
	CWTCSH = GetPrivateProfileIntA("CastleWar", "StartHour", 0, "./Configs/Protection.txt");
	CWTCD = GetPrivateProfileIntA("CastleWar", "Day", 0, "./Configs/Protection.txt");
	GetPrivateProfileStringA("CastleWar", "Enable", "false", CWTCC, 50, "./Configs/Protection.txt");
	HGEA = GetPrivateProfileIntA("Reward", "RewardID", 0, "./Systems/Hunting.txt");
	HTime = GetPrivateProfileIntA("Duration", "Seconds", 0, "./Systems/Hunting.txt");
	HGMobI = GetPrivateProfileIntA("Monster", "Index", 0, "./Systems/Hunting.txt");
	HGMapI = GetPrivateProfileIntA("Map", "Index", 0, "./Systems/Hunting.txt");
	HGXC = GetPrivateProfileIntA("Summon", "X", 0, "./Systems/Hunting.txt");
	HGYC = GetPrivateProfileIntA("Summon", "Y", 0, "./Systems/Hunting.txt");
	HRQuest = GetPrivateProfileIntA("ReplyQuest", "Index", 0, "./Systems/Hunting.txt");
	GetPrivateProfileStringA("Start", "Time", "true", HGST, 50, "./Systems/Hunting.txt");
	PLQuest = GetPrivateProfileIntA("Quest", "Index", 100, "./Systems/ProtectLeader.txt");
	PLMap = GetPrivateProfileIntA("Map", "Index", 1, "./Systems/ProtectLeader.txt");

	KillerHPPL = GetPrivateProfileIntA("HonorReward", "KillerHP", 0, "./Systems/ProtectLeader.txt");
	KillerRPPL = GetPrivateProfileIntA("HonorReward", "KillerRP", 0, "./Systems/ProtectLeader.txt");
	KilledHPPL = GetPrivateProfileIntA("HonorReward", "KilledHP", 0, "./Systems/ProtectLeader.txt");
	KilledRPPL = GetPrivateProfileIntA("HonorReward", "KilledRP", 0, "./Systems/ProtectLeader.txt");

	KillerHPBF = GetPrivateProfileIntA("HonorReward", "KillerHP", 0, "./Systems/Battlefield.txt");
	KillerRPBF = GetPrivateProfileIntA("HonorReward", "KillerRP", 0, "./Systems/Battlefield.txt");
	KilledHPBF = GetPrivateProfileIntA("HonorReward", "KilledHP", 0, "./Systems/Battlefield.txt");
	KilledRPBF = GetPrivateProfileIntA("HonorReward", "KilledRP", 0, "./Systems/Battlefield.txt");

	KillerHPGVG = GetPrivateProfileIntA("HonorReward", "KillerHP", 0, "./Systems/Destructing.txt");
	KillerRPGVG = GetPrivateProfileIntA("HonorReward", "KillerRP", 0, "./Systems/Destructing.txt");
	KilledHPGVG = GetPrivateProfileIntA("HonorReward", "KilledHP", 0, "./Systems/Destructing.txt");
	KilledRPGVG = GetPrivateProfileIntA("HonorReward", "KilledRP", 0, "./Systems/Destructing.txt");

	PLRNPC = GetPrivateProfileIntA("NPCRed", "Index", 1, "./Systems/ProtectLeader.txt");
	PLBNPC = GetPrivateProfileIntA("NPCBlue", "Index", 1, "./Systems/ProtectLeader.txt");
	ENPCQ = GetPrivateProfileIntA("Quest", "Index", 0, "./Configs/EventNPC.txt");
	ENPCRQ = GetPrivateProfileIntA("ReplyQuest", "Index", 0, "./Configs/EventNPC.txt");
	ENPCDL = GetPrivateProfileIntA("Daily", "Limit", 0, "./Configs/EventNPC.txt");
	ENPCII = GetPrivateProfileIntA("EventItem", "Index", 0, "./Configs/EventNPC.txt");
	ENPCIA = GetPrivateProfileIntA("Item", "Amount", 0, "./Configs/EventNPC.txt");
	ENPCDU = GetPrivateProfileIntA("Duration", "Seconds", 0, "./Configs/EventNPC.txt");
	ENPCDD = GetPrivateProfileIntA("Delay", "Seconds", 0, "./Configs/EventNPC.txt");
	SOFSMIN = GetPrivateProfileIntA("ShoutOfFightingSpirit", "MinAtk", 1, "./Skills/Nirvana.txt");
	SOFSMAX = GetPrivateProfileIntA("ShoutOfFightingSpirit", "MaxAtk", 1, "./Skills/Nirvana.txt");
	NBOMMul = GetPrivateProfileIntA("Bombing", "Multiply", 1, "./Skills/Nirvana.txt");
	NBOMMin = GetPrivateProfileIntA("Bombing", "GradeDamageIncreaseMin", 1, "./Skills/Nirvana.txt");
	NBOMMax = GetPrivateProfileIntA("Bombing", "GradeDamageIncreaseMax", 1, "./Skills/Nirvana.txt");
	NBOMReduce = GetPrivateProfileIntA("Bombing", "PVPReduce", 1, "./Skills/Nirvana.txt");
	NSOGMul = GetPrivateProfileIntA("StrikeOfGod", "Multiply", 1, "./Skills/Nirvana.txt");
	NSOGMin = GetPrivateProfileIntA("StrikeOfGod", "GradeDamageIncreaseMin", 1, "./Skills/Nirvana.txt");
	NSOGMax = GetPrivateProfileIntA("StrikeOfGod", "GradeDamageIncreaseMax", 1, "./Skills/Nirvana.txt");
	NSOGReduce = GetPrivateProfileIntA("StrikeOfGod", "PVPReduce", 1, "./Skills/Nirvana.txt");
	NDAMul = GetPrivateProfileIntA("DestroyingArmor", "Multiply", 1, "./Skills/Nirvana.txt");
	NDAMin = GetPrivateProfileIntA("DestroyingArmor", "GradeDamageIncreaseMin", 1, "./Skills/Nirvana.txt");
	NDAMax = GetPrivateProfileIntA("DestroyingArmor", "GradeDamageIncreaseMax", 1, "./Skills/Nirvana.txt");
	NDAReduce = GetPrivateProfileIntA("DestroyingArmor", "PVPReduce", 1, "./Skills/Nirvana.txt");
	NCSMul = GetPrivateProfileIntA("CriticalStrike", "Multiply", 1, "./Skills/Nirvana.txt");
	NCSMin = GetPrivateProfileIntA("CriticalStrike", "GradeDamageIncreaseMin", 1, "./Skills/Nirvana.txt");
	NCSMax = GetPrivateProfileIntA("CriticalStrike", "GradeDamageIncreaseMax", 1, "./Skills/Nirvana.txt");
	NCSReduce = GetPrivateProfileIntA("CriticalStrike", "PVPReduce", 1, "./Skills/Nirvana.txt");
	NMPMul = GetPrivateProfileIntA("Punishment", "Multiply", 1, "./Skills/Nirvana.txt");
	NMPMin = GetPrivateProfileIntA("Punishment", "GradeDamageIncreaseMin", 1, "./Skills/Nirvana.txt");
	NMPMax = GetPrivateProfileIntA("Punishment", "GradeDamageIncreaseMax", 1, "./Skills/Nirvana.txt");
	NMPReduce = GetPrivateProfileIntA("Punishment", "PVPReduce", 1, "./Skills/Nirvana.txt");
	NSOTAMul = GetPrivateProfileIntA("SpiritOfTheArrows", "Multiply", 1, "./Skills/Nirvana.txt");
	NSOTAMin = GetPrivateProfileIntA("SpiritOfTheArrows", "GradeDamageIncreaseMin", 1, "./Skills/Nirvana.txt");
	NSOTAMax = GetPrivateProfileIntA("SpiritOfTheArrows", "GradeDamageIncreaseMax", 1, "./Skills/Nirvana.txt");
	NSOTAReduce = GetPrivateProfileIntA("SpiritOfTheArrows", "PVPReduce", 1, "./Skills/Nirvana.txt");
	NMFMul = GetPrivateProfileIntA("MassiveFire", "Multiply", 1, "./Skills/Nirvana.txt");
	NMFMin = GetPrivateProfileIntA("MassiveFire", "GradeDamageIncreaseMin", 1, "./Skills/Nirvana.txt");
	NMFMax = GetPrivateProfileIntA("MassiveFire", "GradeDamageIncreaseMax", 1, "./Skills/Nirvana.txt");
	NMFReduce = GetPrivateProfileIntA("MassiveFire", "PVPReduce", 1, "./Skills/Nirvana.txt");
	NAOTMMul = GetPrivateProfileIntA("ArrowsOfTheMaster", "Multiply", 1, "./Skills/Nirvana.txt");
	NAOTMMin = GetPrivateProfileIntA("ArrowsOfTheMaster", "GradeDamageIncreaseMin", 1, "./Skills/Nirvana.txt");
	NAOTMMax = GetPrivateProfileIntA("ArrowsOfTheMaster", "GradeDamageIncreaseMax", 1, "./Skills/Nirvana.txt");
	NAOTMReduce = GetPrivateProfileIntA("ArrowsOfTheMaster", "PVPReduce", 1, "./Skills/Nirvana.txt");
	NOHSMul = GetPrivateProfileIntA("OneHitStrike", "Multiply", 1, "./Skills/Nirvana.txt");
	NOHSMin = GetPrivateProfileIntA("OneHitStrike", "GradeDamageIncreaseMin", 1, "./Skills/Nirvana.txt");
	NOHSMax = GetPrivateProfileIntA("OneHitStrike", "GradeDamageIncreaseMax", 1, "./Skills/Nirvana.txt");
	NOHSReduce = GetPrivateProfileIntA("OneHitStrike", "PVPReduce", 1, "./Skills/Nirvana.txt");
	NWOEMul = GetPrivateProfileIntA("TheWaveOfEarth", "Multiply", 1, "./Skills/Nirvana.txt");
	NWOEMin = GetPrivateProfileIntA("TheWaveOfEarth", "GradeDamageIncreaseMin", 1, "./Skills/Nirvana.txt");
	NWOEMax = GetPrivateProfileIntA("TheWaveOfEarth", "GradeDamageIncreaseMax", 1, "./Skills/Nirvana.txt");
	NWOEReduce = GetPrivateProfileIntA("TheWaveOfEarth", "PVPReduce", 1, "./Skills/Nirvana.txt");
	LMSLimit = GetPrivateProfileIntA("Limit", "Level", 100, "./Systems/LastManStand.txt");
	LMSMobIndex = GetPrivateProfileIntA("StoneHP", "MobIndex", 1446, "./Systems/LastManStand.txt");
	LMSMobX = GetPrivateProfileIntA("StoneHP", "X", 1446, "./Systems/LastManStand.txt");
	LMSMobY = GetPrivateProfileIntA("StoneHP", "Y", 1446, "./Systems/LastManStand.txt");
	LMSRange = GetPrivateProfileIntA("StoneHP", "HealRange", 300, "./Systems/LastManStand.txt");

	LMSQuest = GetPrivateProfileIntA("Quest", "Index", 1, "./Systems/LastManStand.txt");
	LMSMap = GetPrivateProfileIntA("Map", "Index", 1, "./Systems/LastManStand.txt");
	LMSX = GetPrivateProfileIntA("Teleport", "X", 1, "./Systems/LastManStand.txt");
	LMSY = GetPrivateProfileIntA("Teleport", "Y", 1, "./Systems/LastManStand.txt");
	GetPrivateProfileStringA("ExpEvent", "Active", "true", ActiveExpEvent, 50, "./Configs/Protection.txt");
	GetPrivateProfileStringA("ExpEvent", "Start", "true", ExpEventStart, 50, "./Configs/Protection.txt");
	GetPrivateProfileStringA("ExpEvent", "End", "true", ExpEventEnd, 50, "./Configs/Protection.txt");
	DTQuest = GetPrivateProfileIntA("Quest", "Index", 0, "./Systems/Duel.txt");
	DTLimit = GetPrivateProfileIntA("Limit", "Level", 1, "./Systems/Duel.txt");
	DuelDuration = GetPrivateProfileIntA("Duel", "BattleDuration", 300, "./Systems/Duel.txt");
	COKQuest = GetPrivateProfileIntA("Quest", "Index", 0, "./Systems/WorldCup.txt");
	COKLimit = GetPrivateProfileIntA("Limit", "Level", 1, "./Systems/WorldCup.txt");
	ReplyWC = GetPrivateProfileIntA("RemainQuest", "Index", 0, "./Systems/WorldCup.txt");
	WCWinQuest = GetPrivateProfileIntA("WinnerQuest", "Index", 0, "./Systems/WorldCup.txt");
	GetPrivateProfileStringA("ShopReward", "Active", "false", ShopRewardCheck, 50, "./Configs/Protection.txt");
	GetPrivateProfileStringA("ShopReward", "Index", "0", ShopRewardIndex, 512, "./Configs/Protection.txt");
	GetPrivateProfileStringA("ShopReward", "Amount", "0", ShopRewardAmount, 512, "./Configs/Protection.txt");
	GetPrivateProfileStringA("ShopReward", "Level", "1", ShopRewardLvl, 512, "./Configs/Protection.txt");

	ShopRewardTime = GetPrivateProfileIntA("ShopReward", "Time", 3600, "./Configs/Protection.txt");
	ShopFortCheck = GetPrivateProfileIntA("ShopReward", "FortCheck", 1, "./Configs/Protection.txt");
	ShopBound = GetPrivateProfileIntA("ShopReward", "Bound", 1, "./Configs/Protection.txt");
	DailyLoginLimit = GetPrivateProfileIntA("DailyReward", "Limit", 0, "./Configs/DailyLogin.txt");
	IPCheck = GetPrivateProfileIntA("DailyReward", "IPCheck", 1, "./Configs/DailyLogin.txt");
	DailyLoginBound = GetPrivateProfileIntA("DailyReward", "Bound", 0, "./Configs/DailyLogin.txt");
	DailyLogin = GetPrivateProfileIntA("DailyReward", "Active", 0, "./Configs/DailyLogin.txt");
	DailyRewardQuest = GetPrivateProfileIntA("DailyReward", "Quest", 0, "./Configs/DailyLogin.txt");
	
	MageFakeDamage = GetPrivateProfileIntA("FakeDamage", "Damage", 1, "./Configs/Protection.txt");
	HellSummonY = GetPrivateProfileIntA("Spawn", "Y", 0, "./Systems/Hell.txt");
	HellSummonX = GetPrivateProfileIntA("Spawn", "X", 0, "./Systems/Hell.txt");
	HellReturnY = GetPrivateProfileIntA("TeleportBack", "Y", 0, "./Systems/Hell.txt");
	HellReturnX = GetPrivateProfileIntA("TeleportBack", "X", 0, "./Systems/Hell.txt");
	HellY = GetPrivateProfileIntA("Teleport", "Y", 0, "./Systems/Hell.txt");
	HellX = GetPrivateProfileIntA("Teleport", "X", 0, "./Systems/Hell.txt");
	HellMap = GetPrivateProfileIntA("Map", "Index", 0, "./Systems/Hell.txt");
	HellQuest = GetPrivateProfileIntA("Quest", "Index", 0, "./Systems/Hell.txt");
	HellCooldown = GetPrivateProfileIntA("Quest", "Cooldown", 0, "./Systems/Hell.txt");
	F10Limit = GetPrivateProfileIntA("Limit", "Active", 1, "./Systems/F10.txt");
	InstanceLimit = GetPrivateProfileIntA("Instance", "Limit", 1, "./Configs/EventMaps.txt");

	F10Exp1 = GetPrivateProfileIntA("First", "Amount", 1, "./Systems/F10.txt");
	F10Exp2 = GetPrivateProfileIntA("Second", "Amount", 1, "./Systems/F10.txt");
	F10Exp3 = GetPrivateProfileIntA("Third", "Amount", 1, "./Systems/F10.txt");
	F10Exp4 = GetPrivateProfileIntA("Forth", "Amount", 1, "./Systems/F10.txt");
	F10Exp5 = GetPrivateProfileIntA("Fifth", "Amount", 1, "./Systems/F10.txt");
	F10Exp6 = GetPrivateProfileIntA("Sixth", "Amount", 1, "./Systems/F10.txt");
	F10Exp7 = GetPrivateProfileIntA("Seventh", "Amount", 1, "./Systems/F10.txt");
	F10Exp8 = GetPrivateProfileIntA("Eighth", "Amount", 1, "./Systems/F10.txt");
	F10Quest = GetPrivateProfileIntA("Quest", "Index", 0, "./Systems/F10.txt");
	F10Level = GetPrivateProfileIntA("Limit", "Level", 50, "./Systems/F10.txt");

	F10BuffEnable = GetPrivateProfileIntA("Buff", "Enable", 1, "./Systems/F10.txt");
	F10BuffSys = GetPrivateProfileIntA("Buff", "BuffSys", 0, "./Systems/F10.txt");
	F10Str = GetPrivateProfileIntA("Buff", "Strength", 0, "./Systems/F10.txt");
	F10Hth = GetPrivateProfileIntA("Buff", "Health", 0, "./Systems/F10.txt");
	F10Int = GetPrivateProfileIntA("Buff", "Intelligence", 0, "./Systems/F10.txt");
	F10Wis = GetPrivateProfileIntA("Buff", "Wisdom", 0, "./Systems/F10.txt");
	F10Agi = GetPrivateProfileIntA("Buff", "Agility", 0, "./Systems/F10.txt");
	F10Min = GetPrivateProfileIntA("Buff", "MinAttack", 0, "./Systems/F10.txt");
	F10Max = GetPrivateProfileIntA("Buff", "MaxAttack", 0, "./Systems/F10.txt");
	F10EXPBuff = GetPrivateProfileIntA("Buff", "EXPRate", 0, "./Systems/F10.txt");

	F10Chance = GetPrivateProfileIntA("PickPlayer", "Chance", 10, "./Systems/F10.txt");
	F10Multiply = GetPrivateProfileIntA("HighExp", "Multiply", 1, "./Systems/F10.txt");


	MautMultiply = GetPrivateProfileIntA("HighExp", "Multiply", 1, "./Systems/Mautareta.txt");
	MautLimit = GetPrivateProfileIntA("Limit", "IPActive", 1, "./Systems/Mautareta.txt");
	MautLevel = GetPrivateProfileIntA("Limit", "Level", 1, "./Systems/Mautareta.txt");

	MautExp1 = GetPrivateProfileIntA("First", "Amount", 1, "./Systems/Mautareta.txt");
	MautExp2 = GetPrivateProfileIntA("Second", "Amount", 1, "./Systems/Mautareta.txt");
	MautExp3 = GetPrivateProfileIntA("Third", "Amount", 1, "./Systems/Mautareta.txt");
	MautExp4 = GetPrivateProfileIntA("Forth", "Amount", 1, "./Systems/Mautareta.txt");
	MautExp5 = GetPrivateProfileIntA("Fifth", "Amount", 1, "./Systems/Mautareta.txt");
	MautExp6 = GetPrivateProfileIntA("Sixth", "Amount", 1, "./Systems/Mautareta.txt");
	MautExp7 = GetPrivateProfileIntA("Seventh", "Amount", 1, "./Systems/Mautareta.txt");
	MautExp8 = GetPrivateProfileIntA("Eighth", "Amount", 1, "./Systems/Mautareta.txt");
	MautChance = GetPrivateProfileIntA("PickPlayer", "Chance", 10, "./Systems/Mautareta.txt");
	MautMap = GetPrivateProfileIntA("Map", "Index", 30, "./Systems/Mautareta.txt");
	MautQuest = GetPrivateProfileIntA("Quest", "Index", 0, "./Systems/Mautareta.txt");
	MautX = GetPrivateProfileIntA("Map", "X", 0, "./Systems/Mautareta.txt");
	MautY = GetPrivateProfileIntA("Map", "Y", 0, "./Systems/Mautareta.txt");
	MautSpawnX = GetPrivateProfileIntA("Spawn", "X", 0, "./Systems/Mautareta.txt");
	MautSpawnY = GetPrivateProfileIntA("Spawn", "Y", 0, "./Systems/Mautareta.txt");

	DonationCoin = GetPrivateProfileIntA("DonationCoin", "Index", 48, "./Configs/Protection.txt");
	ScenarioTime = GetPrivateProfileIntA("Time", "Time", 3600, "./Systems/Destructing.txt");
	ScenarioMap = GetPrivateProfileIntA("Map", "Index", 100, "./Systems/Destructing.txt");
	ScenarioQuest = GetPrivateProfileIntA("Quest", "Index", 0, "./Systems/Destructing.txt");
	ScenarioQuestR = GetPrivateProfileIntA("Quest", "Blue", 0, "./Systems/Destructing.txt");
	ScenarioQuestB = GetPrivateProfileIntA("Quest", "Red", 0, "./Systems/Destructing.txt");

	//REWARDS
	WinnerBF = GetPrivateProfileIntA("Reward", "WinnerRewardID", 0, "./Systems/Battlefield.txt");
	LoserBF = GetPrivateProfileIntA("Reward", "LoserRewardID", 0, "./Systems/Battlefield.txt");
	DrawBF = GetPrivateProfileIntA("Reward", "DrawRewardID", 0, "./Systems/Battlefield.txt");

	WinnerDK = GetPrivateProfileIntA("Reward", "WinnerRewardID", 0, "./Systems/Destructing.txt");
	LoserDK = GetPrivateProfileIntA("Reward", "LoserRewardID", 0, "./Systems/Destructing.txt");
	DrawDK = GetPrivateProfileIntA("Reward", "DrawRewardID", 0, "./Systems/Destructing.txt");

	WinnerCapture = GetPrivateProfileIntA("Reward", "WinnerRewardID", 0, "./Systems/Capture.txt");
	LoserCapture = GetPrivateProfileIntA("Reward", "LoserRewardID", 0, "./Systems/Capture.txt");
	DrawCapture = GetPrivateProfileIntA("Reward", "DrawRewardID", 0, "./Systems/Capture.txt");

	WinnerPL = GetPrivateProfileIntA("Reward", "WinnerRewardID", 0, "./Systems/ProtectLeader.txt");
	LoserPL = GetPrivateProfileIntA("Reward", "LoserRewardID", 0, "./Systems/ProtectLeader.txt");

	WinnerDuel = GetPrivateProfileIntA("Reward", "Winner", 0, "./Systems/Duel.txt");
	WinnerDuelRound = GetPrivateProfileIntA("Reward", "RoundWinner", 0, "./Systems/Duel.txt");
	LoserDuelRound = GetPrivateProfileIntA("Reward", "RoundLoser", 0, "./Systems/Duel.txt");

	WinnerHell = GetPrivateProfileIntA("Reward", "RewardID", 0, "./Systems/Hell.txt");
	WinnerLMS = GetPrivateProfileIntA("Reward", "Winner", 0, "./Systems/LastManStand.txt");
	LoserLMS = GetPrivateProfileIntA("Reward", "Loser", 0, "./Systems/LastManStand.txt");

	VoteReward = GetPrivateProfileIntA("Reward", "RewardID", 0, "./Systems/Vote.txt");
	BossHuntReward = GetPrivateProfileIntA("Reward", "RewardID", 0, "./Systems/Boss.txt");

	//END

	BFRedSafeX1 = GetPrivateProfileIntA("RedRectSafeZone", "X1", 0, "./Systems/Battlefield.txt");
	BFRedSafeY1 = GetPrivateProfileIntA("RedRectSafeZone", "Y1", 0, "./Systems/Battlefield.txt");
	BFRedSafeX2 = GetPrivateProfileIntA("RedRectSafeZone", "X2", 0, "./Systems/Battlefield.txt");
	BFRedSafeY2 = GetPrivateProfileIntA("RedRectSafeZone", "Y2", 0, "./Systems/Battlefield.txt");

	rectRedSafe.left = min(BFRedSafeX1, BFRedSafeX2);
	rectRedSafe.right = max(BFRedSafeX1, BFRedSafeX2);
	rectRedSafe.top = min(BFRedSafeY1, BFRedSafeY2);
	rectRedSafe.bottom = max(BFRedSafeY1, BFRedSafeY2);

	BFBlueSafeX1 = GetPrivateProfileIntA("BlueRectSafeZone", "X1", 0, "./Systems/Battlefield.txt");
	BFBlueSafeY1 = GetPrivateProfileIntA("BlueRectSafeZone", "Y1", 0, "./Systems/Battlefield.txt");
	BFBlueSafeX2 = GetPrivateProfileIntA("BlueRectSafeZone", "X2", 0, "./Systems/Battlefield.txt");
	BFBlueSafeY2 = GetPrivateProfileIntA("BlueRectSafeZone", "Y2", 0, "./Systems/Battlefield.txt");

	rectBlueSafe.left = min(BFBlueSafeX1, BFBlueSafeX2);
	rectBlueSafe.right = max(BFBlueSafeX1, BFBlueSafeX2);
	rectBlueSafe.top = min(BFBlueSafeY1, BFBlueSafeY2);
	rectBlueSafe.bottom = max(BFBlueSafeY1, BFBlueSafeY2);
		
	BFTeleRedX = GetPrivateProfileIntA("RedTeleport", "X", 282821, "./Systems/Battlefield.txt");
	BFTeleRedY = GetPrivateProfileIntA("RedTeleport", "Y", 217307, "./Systems/Battlefield.txt");
	BFTeleRedZ = GetPrivateProfileIntA("RedTeleport", "Z", 0, "./Systems/Battlefield.txt");
	BFTeleBlueX = GetPrivateProfileIntA("BlueTeleport", "X", 274256, "./Systems/Battlefield.txt");
	BFTeleBlueY = GetPrivateProfileIntA("BlueTeleport", "Y", 208690, "./Systems/Battlefield.txt");
	BFTeleBlueZ = GetPrivateProfileIntA("BlueTeleport", "Z", 0, "./Systems/Battlefield.txt");

	//BlueStoneX = GetPrivateProfileIntA("BlueStone", "X", 276460, "./Systems/Battlefield.txt");
	//BlueStoneY = GetPrivateProfileIntA("BlueStone", "Y", 315762, "./Systems/Battlefield.txt");
	//RedStoneX = GetPrivateProfileIntA("RedStone", "X", 275535, "./Systems/Battlefield.txt");
	//RedStoneY = GetPrivateProfileIntA("RedStone", "Y", 314195, "./Systems/Battlefield.txt");

	BlueStoneX = GetPrivateProfileIntA("BlueStone", "X", 0, "./Systems/Battlefield.txt");
	BlueStoneY = GetPrivateProfileIntA("BlueStone", "Y", 0, "./Systems/Battlefield.txt");
	RedStoneX = GetPrivateProfileIntA("RedStone", "X", 0, "./Systems/Battlefield.txt");
	RedStoneY = GetPrivateProfileIntA("RedStone", "Y", 0, "./Systems/Battlefield.txt");

	//shelter
	BFRedSafeX1G = GetPrivateProfileIntA("RedRectSafeZone", "X1", 0, "./Configs/Hogwarts.txt");
	BFRedSafeY1G = GetPrivateProfileIntA("RedRectSafeZone", "Y1", 0, "./Configs/Hogwarts.txt");
	BFRedSafeX2G = GetPrivateProfileIntA("RedRectSafeZone", "X2", 0, "./Configs/Hogwarts.txt");
	BFRedSafeY2G = GetPrivateProfileIntA("RedRectSafeZone", "Y2", 0, "./Configs/Hogwarts.txt");

	rectRedSafeG.left = min(BFRedSafeX1G, BFRedSafeX2G);
	rectRedSafeG.right = max(BFRedSafeX1G, BFRedSafeX2G);
	rectRedSafeG.top = min(BFRedSafeY1G, BFRedSafeY2G);
	rectRedSafeG.bottom = max(BFRedSafeY1G, BFRedSafeY2G);

	BFBlueSafeX1G = GetPrivateProfileIntA("BlueRectSafeZone", "X1", 0, "./Configs/Hogwarts.txt");
	BFBlueSafeY1G = GetPrivateProfileIntA("BlueRectSafeZone", "Y1", 0, "./Configs/Hogwarts.txt");
	BFBlueSafeX2G = GetPrivateProfileIntA("BlueRectSafeZone", "X2", 0, "./Configs/Hogwarts.txt");
	BFBlueSafeY2G = GetPrivateProfileIntA("BlueRectSafeZone", "Y2", 0, "./Configs/Hogwarts.txt");

	rectBlueSafeG.left = min(BFBlueSafeX1G, BFBlueSafeX2G);
	rectBlueSafeG.right = max(BFBlueSafeX1G, BFBlueSafeX2G);
	rectBlueSafeG.top = min(BFBlueSafeY1G, BFBlueSafeY2G);
	rectBlueSafeG.bottom = max(BFBlueSafeY1G, BFBlueSafeY2G);

	BFTeleRedXG = GetPrivateProfileIntA("RedTeleport", "X", 282821, "./Configs/Hogwarts.txt");
	BFTeleRedYG = GetPrivateProfileIntA("RedTeleport", "Y", 217307, "./Configs/Hogwarts.txt");
	BFTeleRedZG = GetPrivateProfileIntA("RedTeleport", "Z", 0, "./Configs/Hogwarts.txt");
	BFTeleBlueXG = GetPrivateProfileIntA("BlueTeleport", "X", 274256, "./Configs/Hogwarts.txt");
	BFTeleBlueYG = GetPrivateProfileIntA("BlueTeleport", "Y", 208690, "./Configs/Hogwarts.txt");
	BFTeleBlueZG = GetPrivateProfileIntA("BlueTeleport", "Z", 0, "./Configs/Hogwarts.txt");

	BlueStoneXG = GetPrivateProfileIntA("BlueStone", "X", 0, "./Configs/Hogwarts.txt");
	BlueStoneYG = GetPrivateProfileIntA("BlueStone", "Y", 0, "./Configs/Hogwarts.txt");
	RedStoneXG = GetPrivateProfileIntA("RedStone", "X", 0, "./Configs/Hogwarts.txt");
	RedStoneYG = GetPrivateProfileIntA("RedStone", "Y", 0, "./Configs/Hogwarts.txt");

	GVETime = GetPrivateProfileIntA("GoodVsEvil", "Time", 1800, "./Configs/Hogwarts.txt");
	EVGoodReward = GetPrivateProfileIntA("GoodVsEvil", "WinnerRewardID", WinnerBF, "./Configs/Hogwarts.txt");
	EVGoodLoser = GetPrivateProfileIntA("GoodVsEvil", "LoserRewardID", LoserBF, "./Configs/Hogwarts.txt");
	EVGoodDraw = GetPrivateProfileIntA("GoodVsEvil", "DrawRewardID", DrawBF, "./Configs/Hogwarts.txt");
	//shelterend

	BattlefieldLevel = GetPrivateProfileIntA("Limit", "Level", 50, "./Systems/Battlefield.txt");
	BFAFKActive = GetPrivateProfileIntA("AFKCheck", "Active", 0, "./Systems/Battlefield.txt");
	BattlefieldAFK = GetPrivateProfileIntA("AFKCheck", "Time", 300, "./Systems/Battlefield.txt");
	BattlefieldBuffs = GetPrivateProfileIntA("Revive", "BuffGrade", 0, "./Systems/Battlefield.txt");
	BattlefieldSpeed = GetPrivateProfileIntA("Revive", "SpeedValue", 0, "./Systems/Battlefield.txt");

	BFHWID = GetPrivateProfileIntA("HWIDLimit", "Active", 1, "./Systems/Battlefield.txt");
	LMSHWID = GetPrivateProfileIntA("HWIDLimit", "Active", 1, "./Systems/LastManStand.txt");

	FOESkillsActive = GetPrivateProfileIntA("ForestOfElements", "SkillsActive", 0, "./Configs/Protection.txt");

	BFTime = GetPrivateProfileIntA("Time", "Time", 3600, "./Systems/Battlefield.txt");
	BFMap = GetPrivateProfileIntA("Map", "Index", 100, "./Systems/Battlefield.txt");
	BFQuest = GetPrivateProfileIntA("Quest", "Index", 0, "./Systems/Battlefield.txt");
	BFRange = GetPrivateProfileIntA("Map", "Range", 100, "./Systems/Battlefield.txt");
	BFBoss = GetPrivateProfileIntA("Boss", "Index", 205, "./Systems/Battlefield.txt");
	BFBossX = GetPrivateProfileIntA("Boss", "X", 0, "./Systems/Battlefield.txt");
	BFBossY = GetPrivateProfileIntA("Boss", "Y", 0, "./Systems/Battlefield.txt");
	BFBossTime = GetPrivateProfileIntA("Boss", "SpawnEvery", 0, "./Systems/Battlefield.txt");
	BFBossReward = GetPrivateProfileIntA("Boss", "RewardID", 0, "./Systems/Battlefield.txt");
	BFBossBuffX1 = GetPrivateProfileIntA("Boss", "BuffX1", 0, "./Systems/Battlefield.txt");
	BFBossBuffY1 = GetPrivateProfileIntA("Boss", "BuffY1", 0, "./Systems/Battlefield.txt");
	BFBossBuffX2 = GetPrivateProfileIntA("Boss", "BuffX2", 0, "./Systems/Battlefield.txt");
	BFBossBuffY2 = GetPrivateProfileIntA("Boss", "BuffY2", 0, "./Systems/Battlefield.txt");

	BFBossBuff.left = min(BFBossBuffX1, BFBossBuffX2);
	BFBossBuff.right = max(BFBossBuffX1, BFBossBuffX2);
	BFBossBuff.top = min(BFBossBuffY1, BFBossBuffY2);
	BFBossBuff.bottom = max(BFBossBuffY1, BFBossBuffY2);

	CaptureMap = GetPrivateProfileIntA("Map", "Index", 100, "./Systems/Capture.txt"); 
	CPRedSafeX1 = GetPrivateProfileIntA("RedRectSafeZone", "MaxX", 8560, "./Systems/Capture.txt");
	CPRedSafeX2 = GetPrivateProfileIntA("RedRectSafeZone", "MinX", 8579, "./Systems/Capture.txt");
	CPBlueSafeX1 = GetPrivateProfileIntA("BlueRectSafeZone", "MaxX", 8828, "./Systems/Capture.txt");
	CPBlueSafeX2 = GetPrivateProfileIntA("BlueRectSafeZone", "MinX", 8847, "./Systems/Capture.txt");
	CPTeleRedX = GetPrivateProfileIntA("RedTeleport", "X", 282821, "./Systems/Capture.txt");
	CPTeleRedY = GetPrivateProfileIntA("RedTeleport", "Y", 217307, "./Systems/Capture.txt");
	CPTeleBlueX = GetPrivateProfileIntA("BlueTeleport", "X", 274256, "./Systems/Capture.txt");
	CPTeleBlueY = GetPrivateProfileIntA("BlueTeleport", "Y", 208690, "./Systems/Capture.txt");
	CaptureMonster = GetPrivateProfileIntA("MonsterFlag", "Index", 100, "./Systems/Capture.txt");
	CPSummonX = GetPrivateProfileIntA("MonsterFlag", "X", 298330, "./Systems/Capture.txt");
	CPSummonY = GetPrivateProfileIntA("MonsterFlag", "Y", 218720, "./Systems/Capture.txt");
	RedCPSummonX = GetPrivateProfileIntA("MonsterFlag", "RedX", 298330, "./Systems/Capture.txt");
	RedCPSummonY = GetPrivateProfileIntA("MonsterFlag", "RedY", 218720, "./Systems/Capture.txt");
	BlueCPSummonX = GetPrivateProfileIntA("MonsterFlag", "BlueX", 298330, "./Systems/Capture.txt");
	BlueCPSummonY = GetPrivateProfileIntA("MonsterFlag", "BlueY", 218720, "./Systems/Capture.txt");
	CPGate = GetPrivateProfileIntA("MonsterGate", "Index", 100, "./Systems/Capture.txt"); 
	CPGateRX = GetPrivateProfileIntA("MonsterGate", "RedX", 298330, "./Systems/Capture.txt");
	CPGateRY = GetPrivateProfileIntA("MonsterGate", "RedY", 218720, "./Systems/Capture.txt");
	CPGateBX = GetPrivateProfileIntA("MonsterGate", "BlueX", 298330, "./Systems/Capture.txt");
	CPGateBY = GetPrivateProfileIntA("MonsterGate", "BlueY", 218720, "./Systems/Capture.txt");
	CPMob = GetPrivateProfileIntA("MonsterAttackers", "Index", 100, "./Systems/Capture.txt");
	CPMobAmount = GetPrivateProfileIntA("MonsterAttackers", "Amount", 100, "./Systems/Capture.txt");
	CPMobRedX = GetPrivateProfileIntA("MonsterAttackers", "RedX", 298330, "./Systems/Capture.txt");
	CPMobRedY = GetPrivateProfileIntA("MonsterAttackers", "RedY", 218720, "./Systems/Capture.txt");
	CPMobBlueX = GetPrivateProfileIntA("MonsterAttackers", "BlueX", 298330, "./Systems/Capture.txt");
	CPMobBlueY = GetPrivateProfileIntA("MonsterAttackers", "BlueY", 218720, "./Systems/Capture.txt");
	CaptureDuration = GetPrivateProfileIntA("Duration", "Seconds", 3600, "./Systems/Capture.txt");
	CPHP = GetPrivateProfileIntA("Capturer", "HPDecrease", 100, "./Systems/Capture.txt");
	CaptureQuest = GetPrivateProfileIntA("Quest", "Index", 0, "./Systems/Capture.txt");
	CPQuestR = GetPrivateProfileIntA("Quest", "RedIndex", 0, "./Systems/Capture.txt");
	CPQuestB = GetPrivateProfileIntA("Quest", "BlueIndex", 0, "./Systems/Capture.txt");
	CPPoints = GetPrivateProfileIntA("Score", "Points", 5, "./Systems/Capture.txt");
	CPSeconds = GetPrivateProfileIntA("Score", "Seconds", 60, "./Systems/Capture.txt");
	CPMaxScore = GetPrivateProfileIntA("Score", "MaxScore", 1000, "./Systems/Capture.txt");
	GetPrivateProfileStringA("Start", "Time", "true", CaptureTime, 50, "./Systems/Capture.txt");
	TStunReduce = GetPrivateProfileIntA("Stun", "PVPReduce", 1, "./Skills/Thief.txt");
	TStunMul = GetPrivateProfileIntA("Stun", "Multiply", 1, "./Skills/Thief.txt");
	TStunMin = GetPrivateProfileIntA("Stun", "GradeDamageIncreaseMin", 1, "./Skills/Thief.txt");
	TStunMax = GetPrivateProfileIntA("Stun", "GradeDamageIncreaseMax", 1, "./Skills/Thief.txt");
	TStranReduce = GetPrivateProfileIntA("Strangle", "PVPReduce", 1, "./Skills/Thief.txt");
	TStranMul = GetPrivateProfileIntA("Strangle", "Multiply", 1, "./Skills/Thief.txt");
	TStranMin = GetPrivateProfileIntA("Strangle", "GradeDamageIncreaseMin", 1, "./Skills/Thief.txt");
	TStranMax = GetPrivateProfileIntA("Strangle", "GradeDamageIncreaseMax", 1, "./Skills/Thief.txt");
	TRupReduce = GetPrivateProfileIntA("Rupture", "PVPReduce", 1, "./Skills/Thief.txt");
	TRupMul = GetPrivateProfileIntA("Rupture", "Multiply", 1, "./Skills/Thief.txt");
	TRupMin = GetPrivateProfileIntA("Rupture", "GradeDamageIncreaseMin", 1, "./Skills/Thief.txt");
	TRupMax = GetPrivateProfileIntA("Rupture", "GradeDamageIncreaseMax", 1, "./Skills/Thief.txt");
	RupPVPAoe = GetPrivateProfileIntA("Rupture", "PVPAOE", 0, "./Skills/Thief.txt");
	RupRange = GetPrivateProfileIntA("Rupture", "AOERange", 0, "./Skills/Thief.txt");
	RupAOE = GetPrivateProfileIntA("Rupture", "AOE", 0, "./Skills/Thief.txt");
	TFWReduce = GetPrivateProfileIntA("FatalWound", "PVPReduce", 1, "./Skills/Thief.txt");
	TFWMul = GetPrivateProfileIntA("FatalWound", "Multiply", 1, "./Skills/Thief.txt");
	TFWMin = GetPrivateProfileIntA("FatalWound", "GradeDamageIncreaseMin", 1, "./Skills/Thief.txt");
	TFWMax = GetPrivateProfileIntA("FatalWound", "GradeDamageIncreaseMax", 1, "./Skills/Thief.txt");
	TVSReduce = GetPrivateProfileIntA("VitalStrike", "PVPReduce", 1, "./Skills/Thief.txt");
	TVSMul = GetPrivateProfileIntA("VitalStrike", "Multiply", 1, "./Skills/Thief.txt");
	TVSMin = GetPrivateProfileIntA("VitalStrike", "GradeDamageIncreaseMin", 1, "./Skills/Thief.txt");
	TVSMax = GetPrivateProfileIntA("VitalStrike", "GradeDamageIncreaseMax", 1, "./Skills/Thief.txt");
	TAssReduce = GetPrivateProfileIntA("Assault", "PVPReduce", 1, "./Skills/Thief.txt");
	TAssMul = GetPrivateProfileIntA("Assault", "Multiply", 1, "./Skills/Thief.txt");
	TAssMin = GetPrivateProfileIntA("Assault", "GradeDamageIncreaseMin", 1, "./Skills/Thief.txt");
	TAssMax = GetPrivateProfileIntA("Assault", "GradeDamageIncreaseMax", 1, "./Skills/Thief.txt");
	TSuBReduce = GetPrivateProfileIntA("SuicidalBlow", "PVPReduce", 1, "./Skills/Thief.txt");
	TSuBMul = GetPrivateProfileIntA("SuicidalBlow", "Multiply", 1, "./Skills/Thief.txt");
	TSuBMin = GetPrivateProfileIntA("SuicidalBlow", "GradeDamageIncreaseMin", 1, "./Skills/Thief.txt");
	TSuBMax = GetPrivateProfileIntA("SuicidalBlow", "GradeDamageIncreaseMax", 1, "./Skills/Thief.txt");
	TFBReduce = GetPrivateProfileIntA("FinalBlow", "PVPReduce", 1, "./Skills/Thief.txt");
	TFBMul = GetPrivateProfileIntA("FinalBlow", "Multiply", 1, "./Skills/Thief.txt");
	TFBMin = GetPrivateProfileIntA("FinalBlow", "GradeDamageIncreaseMin", 1, "./Skills/Thief.txt");
	TFBMax = GetPrivateProfileIntA("FinalBlow", "GradeDamageIncreaseMax", 1, "./Skills/Thief.txt");
	TSAReduce = GetPrivateProfileIntA("SpinAttack", "PVPReduce", 1, "./Skills/Thief.txt");
	TSAMul = GetPrivateProfileIntA("SpinAttack", "Multiply", 1, "./Skills/Thief.txt");
	TSAMin = GetPrivateProfileIntA("SpinAttack", "GradeDamageIncreaseMin", 1, "./Skills/Thief.txt");
	TSAMax = GetPrivateProfileIntA("SpinAttack", "GradeDamageIncreaseMax", 1, "./Skills/Thief.txt");
	TTBSReduce = GetPrivateProfileIntA("TwinBladeStrike", "PVPReduce", 1, "./Skills/Thief.txt");
	TTBSMul = GetPrivateProfileIntA("TwinBladeStrike", "Multiply", 1, "./Skills/Thief.txt");
	TTBSMin = GetPrivateProfileIntA("TwinBladeStrike", "GradeDamageIncreaseMin", 1, "./Skills/Thief.txt");
	TTBSMax = GetPrivateProfileIntA("TwinBladeStrike", "GradeDamageIncreaseMax", 1, "./Skills/Thief.txt");
	TCAReduce = GetPrivateProfileIntA("CounterAttack", "PVPReduce", 1, "./Skills/Thief.txt");
	TCAMin = GetPrivateProfileIntA("CounterAttack", "GradeDamageIncreaseMin", 1, "./Skills/Thief.txt");
	TCAMax = GetPrivateProfileIntA("CounterAttack", "GradeDamageIncreaseMax", 1, "./Skills/Thief.txt");
	TCOReduce = GetPrivateProfileIntA("CounterOffensive", "PVPReduce", 1, "./Skills/Thief.txt");
	TCOMin = GetPrivateProfileIntA("CounterOffensive", "GradeDamageIncreaseMin", 1, "./Skills/Thief.txt");
	TCOMax = GetPrivateProfileIntA("CounterOffensive", "GradeDamageIncreaseMax", 1, "./Skills/Thief.txt");
	TDOKReduce = GetPrivateProfileIntA("DanceOfKilling", "PVPReduce", 1, "./Skills/Thief.txt");
	TDOKMul = GetPrivateProfileIntA("DanceOfKilling", "Multiply", 1, "./Skills/Thief.txt");
	TDOKMin = GetPrivateProfileIntA("DanceOfKilling", "GradeDamageIncreaseMin", 1, "./Skills/Thief.txt");
	TDOKMax = GetPrivateProfileIntA("DanceOfKilling", "GradeDamageIncreaseMax", 1, "./Skills/Thief.txt");
	TLSReduce = GetPrivateProfileIntA("LightningSlash", "PVPReduce", 1, "./Skills/Thief.txt");
	TLSMul = GetPrivateProfileIntA("LightningSlash", "Multiply", 1, "./Skills/Thief.txt");
	TLSMin = GetPrivateProfileIntA("LightningSlash", "GradeDamageIncreaseMin", 1, "./Skills/Thief.txt");
	TLSMax = GetPrivateProfileIntA("LightningSlash", "GradeDamageIncreaseMax", 1, "./Skills/Thief.txt");
	TSSReduce = GetPrivateProfileIntA("ShadowSlash", "PVPReduce", 1, "./Skills/Thief.txt");
	TSSMul = GetPrivateProfileIntA("ShadowSlash", "Multiply", 1, "./Skills/Thief.txt");
	TSSMin = GetPrivateProfileIntA("ShadowSlash", "GradeDamageIncreaseMin", 1, "./Skills/Thief.txt");
	TSSMax = GetPrivateProfileIntA("ShadowSlash", "GradeDamageIncreaseMax", 1, "./Skills/Thief.txt");
	ShadowAOEPVE = GetPrivateProfileIntA("ShadowSlash", "PVEAOE", 0, "./Skills/Thief.txt");
	ShadowAOEPVP = GetPrivateProfileIntA("ShadowSlash", "PVPAOE", 0, "./Skills/Thief.txt");
	ShadowRange = GetPrivateProfileIntA("ShadowSlash", "Range", 4, "./Skills/Thief.txt");
	TWOHReduce = GetPrivateProfileIntA("WrathOfHeaven", "PVPReduce", 1, "./Skills/Thief.txt");
	TWOHMul = GetPrivateProfileIntA("WrathOfHeaven", "Multiply", 1, "./Skills/Thief.txt");
	TWOHMin = GetPrivateProfileIntA("WrathOfHeaven", "GradeDamageIncreaseMin", 1, "./Skills/Thief.txt");
	TWOHMax = GetPrivateProfileIntA("WrathOfHeaven", "GradeDamageIncreaseMax", 1, "./Skills/Thief.txt");
	TSBReduce = GetPrivateProfileIntA("SpinBlade", "PVPReduce", 1, "./Skills/Thief.txt");
	TSBMul = GetPrivateProfileIntA("SpinBlade", "Multiply", 1, "./Skills/Thief.txt");
	TSBMin = GetPrivateProfileIntA("SpinBlade", "GradeDamageIncreaseMin", 1, "./Skills/Thief.txt");
	TSBMax = GetPrivateProfileIntA("SpinBlade", "GradeDamageIncreaseMax", 1, "./Skills/Thief.txt");
	TEZilReduce = GetPrivateProfileIntA("ZilPoong", "PVPReduce", 1, "./Skills/Egg.txt");
	TEZilMul = GetPrivateProfileIntA("ZilPoong", "Multiply", 1, "./Skills/Egg.txt");
	TEWhirReduce = GetPrivateProfileIntA("WhirlwindFeather", "PVPReduce", 1, "./Skills/Egg.txt");
	TEWhirMul = GetPrivateProfileIntA("WhirlwindFeather", "Multiply", 1, "./Skills/Egg.txt");
	TEShinReduce = GetPrivateProfileIntA("ShinRhoe", "PVPReduce", 1, "./Skills/Egg.txt");
	TEShinMul = GetPrivateProfileIntA("ShinRhoe", "Multiply", 1, "./Skills/Egg.txt");
	MMIReduce = GetPrivateProfileIntA("MagicIntensification", "PVPReduce", 1, "./Skills/Mage.txt");
	MMIMul = GetPrivateProfileIntA("MagicIntensification", "Multiply", 1, "./Skills/Mage.txt");
	MMIMin = GetPrivateProfileIntA("MagicIntensification", "GradeDamageIncreaseMin", 1, "./Skills/Mage.txt");
	MMIMax = GetPrivateProfileIntA("MagicIntensification", "GradeDamageIncreaseMax", 1, "./Skills/Mage.txt");
	MFIReduce = GetPrivateProfileIntA("FlameInjection", "PVPReduce", 1, "./Skills/Mage.txt");
	MFIMul = GetPrivateProfileIntA("FlameInjection", "Multiply", 1, "./Skills/Mage.txt");
	MFIMin = GetPrivateProfileIntA("FlameInjection", "GradeDamageIncreaseMin", 1, "./Skills/Mage.txt");
	MFIMax = GetPrivateProfileIntA("FlameInjection", "GradeDamageIncreaseMax", 1, "./Skills/Mage.txt");
	MLAReduce = GetPrivateProfileIntA("LightningArrow", "PVPReduce", 1, "./Skills/Mage.txt");
	MLAMul = GetPrivateProfileIntA("LightningArrow", "Multiply", 1, "./Skills/Mage.txt");
	MLAMin = GetPrivateProfileIntA("LightningArrow", "GradeDamageIncreaseMin", 1, "./Skills/Mage.txt");
	MLAMax = GetPrivateProfileIntA("LightningArrow", "GradeDamageIncreaseMax", 1, "./Skills/Mage.txt");
	BlessPVP = GetPrivateProfileIntA("Blessing", "PVPReduce", 50, "./Skills/Mage.txt");

	ACSReduce = GetPrivateProfileIntA("CombativeSpirit", "PVPReduce", 1, "./Skills/Archer.txt");
	ACSMul = GetPrivateProfileIntA("CombativeSpirit", "Multiply", 1, "./Skills/Archer.txt");
	ACSMin = GetPrivateProfileIntA("CombativeSpirit", "GradeDamageIncreaseMin", 1, "./Skills/Archer.txt");
	ACSMax = GetPrivateProfileIntA("CombativeSpirit", "GradeDamageIncreaseMax", 1, "./Skills/Archer.txt");
	ACAOE = GetPrivateProfileIntA("CombativeSpirit", "PVEAOE", 1, "./Skills/Archer.txt");
	ACPVPAOE = GetPrivateProfileIntA("CombativeSpirit", "PVPAOE", 1, "./Skills/Archer.txt");
	ACAOERange = GetPrivateProfileIntA("CombativeSpirit", "AOERange", 1, "./Skills/Archer.txt");

	ALAReduce = GetPrivateProfileIntA("LifeAbsorption", "PVPReduce", 1, "./Skills/Archer.txt");
	ALAMul = GetPrivateProfileIntA("LifeAbsorption", "Multiply", 1, "./Skills/Archer.txt");
	ETBReduce = GetPrivateProfileIntA("Thunderbolt", "PVPReduce", 1, "./Skills/Egg.txt");
	ETBMul = GetPrivateProfileIntA("Thunderbolt", "Multiply", 1, "./Skills/Egg.txt");
	ERAReduce = GetPrivateProfileIntA("RevolveAttack", "PVPReduce", 1, "./Skills/Egg.txt");
	ERAMul = GetPrivateProfileIntA("RevolveAttack", "Multiply", 1, "./Skills/Egg.txt");
	EBSReduce = GetPrivateProfileIntA("BloodSuction", "PVPReduce", 1, "./Skills/Egg.txt");
	EBSMul = GetPrivateProfileIntA("BloodSuction", "Multiply", 1, "./Skills/Egg.txt");
	AARReduce = GetPrivateProfileIntA("ArrowRain", "PVPReduce", 1, "./Skills/Archer.txt");
	AARMul = GetPrivateProfileIntA("ArrowRain", "Multiply", 1, "./Skills/Archer.txt");
	AARMin = GetPrivateProfileIntA("ArrowRain", "GradeDamageIncreaseMin", 1, "./Skills/Archer.txt");
	AARMax = GetPrivateProfileIntA("ArrowRain", "GradeDamageIncreaseMax", 1, "./Skills/Archer.txt");
	AETime = GetPrivateProfileIntA("ArrowExplosion", "Time", 3, "./Skills/Archer.txt");
	AAEReduce = GetPrivateProfileIntA("ArrowExplosion", "PVPReduce", 1, "./Skills/Archer.txt");
	AAEMul = GetPrivateProfileIntA("ArrowExplosion", "Multiply", 1, "./Skills/Archer.txt");
	AAEMin = GetPrivateProfileIntA("ArrowExplosion", "GradeDamageIncreaseMin", 1, "./Skills/Archer.txt");
	AAEMax = GetPrivateProfileIntA("ArrowExplosion", "GradeDamageIncreaseMax", 1, "./Skills/Archer.txt");
	AVAReduce = GetPrivateProfileIntA("VirulentArrow", "PVPReduce", 1, "./Skills/Archer.txt");
	AVAMul = GetPrivateProfileIntA("VirulentArrow", "Multiply", 1, "./Skills/Archer.txt");
	AVAMin = GetPrivateProfileIntA("VirulentArrow", "GradeDamageIncreaseMin", 1, "./Skills/Archer.txt");
	AVAMax = GetPrivateProfileIntA("VirulentArrow", "GradeDamageIncreaseMax", 1, "./Skills/Archer.txt"); 

	AVAPoisonMin = GetPrivateProfileIntA("VirulentArrow", "GradeDamagePoisonMin", AVAMin, "./Skills/Archer.txt");
	AVAPoisonMax = GetPrivateProfileIntA("VirulentArrow", "GradeDamagePoisonMax", AVAMax, "./Skills/Archer.txt");
	MTBReduce = GetPrivateProfileIntA("Thunderbolt", "PVPReduce", 1, "./Skills/Mage.txt");
	MTBMul = GetPrivateProfileIntA("Thunderbolt", "Multiply", 1, "./Skills/Mage.txt");
	MTBMin = GetPrivateProfileIntA("Thunderbolt", "GradeDamageIncreaseMin", 1, "./Skills/Mage.txt");
	MTBMax = GetPrivateProfileIntA("Thunderbolt", "GradeDamageIncreaseMax", 1, "./Skills/Mage.txt");
	MIcicleReduce = GetPrivateProfileIntA("Icicle", "PVPReduce", 1, "./Skills/Mage.txt");
	MIcicleMul = GetPrivateProfileIntA("Icicle", "Multiply", 1, "./Skills/Mage.txt");
	MIcicleMin = GetPrivateProfileIntA("Icicle", "GradeDamageIncreaseMin", 1, "./Skills/Mage.txt");
	MIcicleMax = GetPrivateProfileIntA("Icicle", "GradeDamageIncreaseMax", 1, "./Skills/Mage.txt");
	MIAReduce = GetPrivateProfileIntA("IceArrow", "PVPReduce", 1, "./Skills/Mage.txt");
	MIAMul = GetPrivateProfileIntA("IceArrow", "Multiply", 1, "./Skills/Mage.txt");
	MIAMin = GetPrivateProfileIntA("IceArrow", "GradeDamageIncreaseMin", 1, "./Skills/Mage.txt");
	MIAMax = GetPrivateProfileIntA("IceArrow", "GradeDamageIncreaseMax", 1, "./Skills/Mage.txt");
	MFBReduce = GetPrivateProfileIntA("Fireball", "PVPReduce", 1, "./Skills/Mage.txt");
	MFBMul = GetPrivateProfileIntA("Fireball", "Multiply", 1, "./Skills/Mage.txt");
	MFBMin = GetPrivateProfileIntA("Fireball", "GradeDamageIncreaseMin", 1, "./Skills/Mage.txt");
	MFBMax = GetPrivateProfileIntA("Fireball", "GradeDamageIncreaseMax", 1, "./Skills/Mage.txt");
	ArcherManaCirculation = GetPrivateProfileIntA("ManaCirculation", "Increase", 1, "./Skills/Archer.txt");
	MSDReduce = GetPrivateProfileIntA("SoulDestruction", "PVPReduce", 1, "./Skills/Mage.txt");
	MSDMul = GetPrivateProfileIntA("SoulDestruction", "Multiply", 1, "./Skills/Mage.txt");
	MSDMin = GetPrivateProfileIntA("SoulDestruction", "GradeDamageIncreaseMin", 1, "./Skills/Mage.txt");
	MSDMax = GetPrivateProfileIntA("SoulDestruction", "GradeDamageIncreaseMax", 1, "./Skills/Mage.txt");
	SDPVPAOE = GetPrivateProfileIntA("SoulDestruction", "PVPAOE", 0, "./Skills/Mage.txt");
	SDRange = GetPrivateProfileIntA("SoulDestruction", "AOERange", 0, "./Skills/Mage.txt");
	SDAOE = GetPrivateProfileIntA("SoulDestruction", "AOE", 0, "./Skills/Mage.txt");
	SDLOWAOE = GetPrivateProfileIntA("SoulDestruction", "AOESpecialty", 0, "./Skills/Mage.txt");
	MageManaCirculation = GetPrivateProfileIntA("ManaCirculation", "Increase", 1, "./Skills/Mage.txt");
	MRIAmount = GetPrivateProfileIntA("HealRage", "Increase", 1, "./Skills/Mage.txt");
	KSDReduce = GetPrivateProfileIntA("SwordDance", "PVPReduce", 1, "./Skills/Knight.txt");
	KSDMul = GetPrivateProfileIntA("SwordDance", "Multiply", 1, "./Skills/Knight.txt");
	KSDMin = GetPrivateProfileIntA("SwordDance", "GradeDamageIncreaseMin", 1, "./Skills/Knight.txt");
	KSDMax = GetPrivateProfileIntA("SwordDance", "GradeDamageIncreaseMax", 1, "./Skills/Knight.txt");
	KSSReduce = GetPrivateProfileIntA("SpinSlash", "PVPReduce", 1, "./Skills/Knight.txt");
	SpinSlashRange = GetPrivateProfileIntA("SpinSlash", "Range", 6, "./Skills/Knight.txt");
	KSSMul = GetPrivateProfileIntA("SpinSlash", "Multiply", 1, "./Skills/Knight.txt");
	KSSMin = GetPrivateProfileIntA("SpinSlash", "GradeDamageIncreaseMin", 1, "./Skills/Knight.txt");
	KSSMax = GetPrivateProfileIntA("SpinSlash", "GradeDamageIncreaseMax", 1, "./Skills/Knight.txt");
	KSSDBMin = GetPrivateProfileIntA("SpinSlash", "DeathBlowDamageIncreaseMin", 1, "./Skills/Knight.txt");
	KSSDBMax = GetPrivateProfileIntA("SpinSlash", "DeathBlowDamageIncreaseMax", 1, "./Skills/Knight.txt");
	KPOBReduce = GetPrivateProfileIntA("ProvocationOfBlow", "PVPReduce", 1, "./Skills/Knight.txt");
	KPOBMul = GetPrivateProfileIntA("ProvocationOfBlow", "Multiply", 1, "./Skills/Knight.txt");
	KPOBRange = GetPrivateProfileIntA("ProvocationOfBlow", "Range", 2, "./Skills/Knight.txt");
	KPOBMin = GetPrivateProfileIntA("ProvocationOfBlow", "GradeDamageIncreaseMin", 1, "./Skills/Knight.txt");
	KPOBMax = GetPrivateProfileIntA("ProvocationOfBlow", "GradeDamageIncreaseMax", 1, "./Skills/Knight.txt");
	KPWWReduce = GetPrivateProfileIntA("PowerfulWideningWound", "PVPReduce", 1, "./Skills/Knight.txt");
	KPWWMul = GetPrivateProfileIntA("PowerfulWideningWound", "Multiply", 1, "./Skills/Knight.txt");
	KPWWMin = GetPrivateProfileIntA("PowerfulWideningWound", "GradeDamageIncreaseMin", 1, "./Skills/Knight.txt");
	KPWWMax = GetPrivateProfileIntA("PowerfulWideningWound", "GradeDamageIncreaseMax", 1, "./Skills/Knight.txt");
	KnightManaCirculation = GetPrivateProfileIntA("ManaCirculation", "Increase", 1, "./Skills/Knight.txt");
	FishHardest = GetPrivateProfileIntA("Bonus", "Hardest", 1, "./Configs/Fishing.txt");
	FishHard = GetPrivateProfileIntA("Bonus", "Hard", 1, "./Configs/Fishing.txt");
	FishNormal = GetPrivateProfileIntA("Bonus", "Normal", 1, "./Configs/Fishing.txt");
	FishLow = GetPrivateProfileIntA("Bonus", "Easy", 1, "./Configs/Fishing.txt");
	FishLowest = GetPrivateProfileIntA("Bonus", "Easiest", 1, "./Configs/Fishing.txt");
	OriginalHardest = GetPrivateProfileIntA("Original", "Hardest", 244, "./Configs/Fishing.txt");
	OriginalHard = GetPrivateProfileIntA("Original", "Hard", 444, "./Configs/Fishing.txt");
	OriginalNormal = GetPrivateProfileIntA("Original", "Normal", 241, "./Configs/Fishing.txt");
	OriginalLow = GetPrivateProfileIntA("Original", "Easy", 239, "./Configs/Fishing.txt");
	OriginalLowest = GetPrivateProfileIntA("Original", "Easiest", 237, "./Configs/Fishing.txt");
	MysteryResetItem = GetPrivateProfileIntA("ResetItem", "Index", 1, "./Skills/Mystery.txt");
	MysteryQuest = GetPrivateProfileIntA("Quest", "Index", 1, "./Skills/Mystery.txt");
	MysteryEnable = GetPrivateProfileIntA("MysterySkills", "Active", 1, "./Skills/Mystery.txt");
	EmokCert = GetPrivateProfileIntA("Certificate", "Index", 1, "./Configs/Emok.txt");
	EmokX = GetPrivateProfileIntA("Teleport", "X", 1, "./Configs/Emok.txt");
	EmokY = GetPrivateProfileIntA("Teleport", "Y", 1, "./Configs/Emok.txt");
	EmokMap = GetPrivateProfileIntA("Map", "Index", 1, "./Configs/Emok.txt");
	EmokQuestIndex = GetPrivateProfileIntA("Quest", "Index", 1, "./Configs/Emok.txt");
	EmokLvl = GetPrivateProfileIntA("Quest", "Level", 50, "./Configs/Emok.txt");
	ConfigMaxDamage = GetPrivateProfileIntA("Protection", "MaxDamage", 100000, "./Configs/Protection.txt");
	ConfigMaxMagAtk = GetPrivateProfileIntA("Protection", "MaxMagAtk", 10000, "./Configs/Protection.txt");
	ConfigMaxPhyAtk = GetPrivateProfileIntA("Protection", "MaxPhyAtk", 10000, "./Configs/Protection.txt");
	EggExpTime = GetPrivateProfileIntA("EggExp", "ByTime", 1, "./Configs/Protection.txt");
	EggExpKill = GetPrivateProfileIntA("EggExp", "ByKill", 1, "./Configs/Protection.txt");
	ConfigMix = GetPrivateProfileIntA("Mix", "Rate", 1, "./Configs/Mix.txt");
	ConfigImp = GetPrivateProfileIntA("Imp", "Rate", 1, "./Configs/Mix.txt");
	MD5Check = GetPrivateProfileIntA("MD5", "Active", 0, "./Configs/MD5Check.txt");
	Restri = GetPrivateProfileIntA("Restriction", "Active", 0, "./Configs/Restriction.txt");
	TrackerActive = GetPrivateProfileIntA("Tracker", "Active", 0, "./Configs/Tracker.txt");
	HaninChance = GetPrivateProfileIntA("Mirrors", "Upgrade", 1, "./Configs/Mix.txt");
	HaninChange = GetPrivateProfileIntA("Mirrors", "Change", 1, "./Configs/Mix.txt");
	AFKRange = GetPrivateProfileIntA("Range", "Value", 12, "./Configs/AFKCheck.txt");
	MinMacro = GetPrivateProfileIntA("Macro", "MinTime", 60, "./Configs/AFKCheck.txt");
	MaxMacro = GetPrivateProfileIntA("Macro", "MaxTime", 900, "./Configs/AFKCheck.txt");
	MacroStartTime = GetPrivateProfileIntA("Macro", "Cooldown", 30, "./Configs/AFKCheck.txt");
	FilterCheck = GetPrivateProfileIntA("WordFilter", "Active", 0, "./Configs/Filter.txt");
	GetPrivateProfileStringA("Topofmmos", "ApiKey", "", VoteAPIKey, 50, "./Systems/Vote.txt");
	GetPrivateProfileStringA("Server", "Name", "KalTechSolutions", ServerName, 50, "./Configs/Protection.txt");
	GetPrivateProfileStringA("Server", "AuthServer", "AuthSvr.exe", AuthSvr, 50, "./Configs/Protection.txt");
	GZLvl = GetPrivateProfileIntA("Server", "GzMsgLvl", 80, "./Configs/Protection.txt");
	GetPrivateProfileStringA("2ndPwd", "Active", "true", Active2ndPwd, 50, "./Configs/Protection.txt");
	GetPrivateProfileStringA("Thief", "Active", "true", ThiefActiveCheck, 50, "./Configs/Protection.txt");
	GetPrivateProfileStringA("Shaman", "Active", "true", ShamanActiveCheck, 50, "./Configs/Protection.txt");
	GetPrivateProfileStringA("Player", "Drop", NULL, PlayerCheck, 50, "./Configs/Protection.txt");
	GetPrivateProfileStringA("Assassin", "Drop", NULL, SinCheck, 50, "./Configs/Protection.txt");
	GetPrivateProfileStringA("EngineProtect", "Engine.dll", NULL, ConfigEngine, 50, "./Configs/MD5Check.txt");
	GetPrivateProfileStringA("Capturer", "BuffEffect", "Pet_Defensebuff_02", CPBuffEffect, 50, "./Systems/Capture.txt");

	ShamanDisabled = (strlen(ShamanActiveCheck) && ((std::string)ShamanActiveCheck == "false" || (std::string)ShamanActiveCheck == "False"));
	ThiefDisabled = (strlen(ThiefActiveCheck) && ((std::string)ThiefActiveCheck == "false" || (std::string)ThiefActiveCheck == "False"));

	if (!command || (command && modifiedFiles.count("./Configs/ItemShop.txt"))) {
		memset(ItemShopPacket, 0, sizeof ItemShopPacket);
		FILE *oItemShop = fopen("./Configs/ItemShop.txt", "r");
		if (oItemShop != NULL)
		{
			Interface<ITools> Tools;
			char line[BUFSIZ]; int count = 0;
			while (fgets(line, sizeof line, oItemShop) != NULL)
			{
				int BillCode = 0, Type = 0, Discount = 0, Price = 0, ItemIndex = 0, Amount = 0, Priority = 0;
				if (sscanf(line, "(itemshop (billcode %d)(priority %d)(type %d)(price %d)(discount %d)(itemindex %d)(amount %d))", &BillCode, &Priority, &Type, &Price, &Discount, &ItemIndex, &Amount) == 7)
				{
					Tools->Compile(ItemShopPacket + (count * 12), "wbbbbbdb", BillCode, (char)Priority, 0, 0, 0, (char)Type, Price, (char)Discount);
					ConfigItemShop itemShop = ConfigItemShop();
					itemShop.Type = Type;
					itemShop.Priority = Priority;
					itemShop.Price = Price;
					itemShop.Discount = Discount;
					itemShop.ItemIndex = ItemIndex;
					itemShop.Amount = Amount;

					ItemShopCheck[BillCode] = itemShop;

					count++;
					BillCode = 0, Type = 0, Priority = 0, Discount = 0, Price = 0, ItemIndex = 0, Amount = 0;
				}
			}
			fclose(oItemShop);
		}
	}

	if (!command || (command && modifiedFiles.count("./Configs/MonsterPets.txt"))) {
		FILE *filemo = fopen("./Configs/MonsterPets.txt", "r");
		if (filemo != NULL) {
			MonsterPet.clear();
			char line[BUFSIZ];
			while (fgets(line, sizeof line, filemo) != NULL)
			{
				int Index = 0, Material1 = 0, Count1 = 0, Material2 = 0, Count2 = 0, Money = 0, Jewel = 0;
				if (sscanf(line, "%*[ \t|]<MONSTER_PET Index = \"%d\" > <MATERIAL Index = \"%d\" Count = \"%d\"/> <MATERIAL Index = \"%d\" Count = \"%d\"/> <MONSTERPET_PRICE  Money= \"%d\" Jewel = \"%d\"/></MONSTER_PET>%*s", &Index, &Material1, &Count1, &Material2, &Count2, &Money, &Jewel) == 7)
				{
					CreateMonsterPet mp = CreateMonsterPet();
					mp.Count1 = Count1;
					mp.Count2 = Count2;
					mp.Material1 = Material1;
					mp.Material2 = Material2;
					mp.Money = Money;
					mp.Jewel = Jewel;
					MonsterPet[Index] = mp;
				}
			}
			fclose(filemo);
		}
	}

	if (!command || (command && modifiedFiles.count("./Configs/FakePlayers.txt"))) {
		ifstream fFakeP("./Configs/FakePlayers.txt");
		if (fFakeP.good()) {
			string line; 
			int newIID = 1;
			FakePlayers.clear();
			FakeNames.clear();
			FakeItems.clear();
			int id = 0;
			Interface<ITools> Tools;
			while (getline(fFakeP, line))
			{
				int honor = 0, color = 0, cclass = 0, state = 0, cx = 0, cy = 0, cz = 0, direction = 0, weapon = 0, chest = 0, helmet = 0, glove = 0, boot = 0, cshort = 0, shield = 0, costume = 0, face = 0, hair = 0;
				char shopindex[BUFSIZ];
				char amount[BUFSIZ];
				char price[BUFSIZ];
				char name[BUFSIZ];
				char msg[BUFSIZ];

				if (sscanf(line.c_str(), "(player (name '%[^']')(class %d)(state %d)(cx %d)(cy %d)(cz %d)(direction %d)(weapon %d)(chest %d)(helmet %d)(glove %d)(boot %d)(short %d)(shield %d)(costume %d)(face %d)(hair %d)(color %d)(honor %d)(msg '%[^']')(shopindex %[0-9\,])(amount %[0-9/,])(price %[0-9/,]))", &name, &cclass, &state, &cx, &cy, &cz, &direction, &weapon, &chest, &helmet, &glove, &boot, &cshort, &shield, &costume, &face, &hair, &color, &honor, &msg, &shopindex, &amount, &price) == 23)
				{
					id--;
					FakeNames.replaceInsert(std::string(name),id);
					FakePlayers_ fakePlayer = FakePlayers_();
					fakePlayer.check= 0;
					fakePlayer.id = id;
					fakePlayer.name = std::string(name);
					fakePlayer.cclass = cclass;
					fakePlayer.gstate = 0;
					fakePlayer.state = state;
					fakePlayer.x = cx;
					fakePlayer.y = cy;
					fakePlayer.z = cz;
					fakePlayer.direction = direction;
					fakePlayer.weapon = weapon;
					fakePlayer.chest = chest;
					fakePlayer.helmet = helmet;
					fakePlayer.glove = glove;
					fakePlayer.boot = boot;
					fakePlayer.skirt = cshort;
					fakePlayer.shield = shield;
					fakePlayer.costume = costume;
					fakePlayer.face = face;
					fakePlayer.hair = hair;
					fakePlayer.color = color;
					fakePlayer.honor = honor;

					fakePlayer.msg = std::string(msg);

					if (state == 1)
						fakePlayer.gstate = 32;
					else 	if (state == 2)
						fakePlayer.gstate = 20;
					else 	if (state == 3)
						fakePlayer.gstate = 4;

					std::string shopi = std::string(shopindex);
					std::string amounti = std::string(amount);
					std::string pricei = std::string(price);
					std::vector<std::string> shopiex = Tools->Explode(shopi, ",");
					std::vector<std::string> amountiex = Tools->Explode(amounti, ",");
					std::vector<std::string> priceiex = Tools->Explode(pricei, ",");
					if (shopiex.size() == amountiex.size() && priceiex.size() == amountiex.size() && state == 2) {
						for (int i = 0; i < shopiex.size(); i++) {
							FakeItems_ fakeItem = FakeItems_();
							FakePlayers_Shop fShopP = FakePlayers_Shop();
							fShopP.amount = atoi(amountiex[i].c_str());
							fShopP.price = atoi(priceiex[i].c_str());
							fShopP.iid = newIID;
							fakePlayer.Shop.replaceInsert(atoi(shopiex[i].c_str()), fShopP);
							fakeItem.index = atoi(shopiex[i].c_str());
							fakeItem.amount = atoi(amountiex[i].c_str());
							fakeItem.price = atoi(priceiex[i].c_str());
							FakeItems.replaceInsert(newIID, fakeItem);
							newIID++;
						}
						fakePlayer.check = 1;
					}
					else if (state != 2)
						fakePlayer.check = 1;

					FakePlayers.replaceInsert(id,fakePlayer);
				}
			}
			fFakeP.close();
		}
	}


	if (!command || (command && modifiedFiles.count("./Configs/EXPItem.txt"))) {
		FILE* filekd = fopen("./Configs/EXPItem.txt", "r");
		if (filekd != NULL) {
			AreasExpItems.clear();
			char line[BUFSIZ];
			while (fgets(line, sizeof line, filekd) != NULL) {
				int map = 0, exp = 0, item = 0, time = 0;
				AreaExpItem newArea;
				if (sscanf(line, "(Area (map %d)(exp %d)(item %d)(time %d))", &map, &exp, &item, &time) == 4) {
					newArea.type = 2;
					newArea.map = map;
					newArea.item = item;
					newArea.experience = exp;
					newArea.time = time;

					AreasExpItems[map] = newArea;
				}
			}
			fclose(filekd);
		}
	}




	if (!command || (command && modifiedFiles.count("./Configs/Missions.txt"))) {
		FILE* Missions = fopen("./Configs/Missions.txt", "r");
		if (Missions != NULL) {
			MissionQuests.clear();
			MissionQuestsItem.clear();
			char line[BUFSIZ];
			while (fgets(line, sizeof line, Missions) != NULL) {
				int index = 0, nextmission = 0, teleportX = 0, teleportY = 0, monsterIndex = 0, amount = 0, reward = 0, itemIndex = 0, itemAmount = 0, teleportMap = 0;
				char MissionItems[BUFSIZ], MissionAmounts[BUFSIZ];
				if (sscanf(line, "(Mission (CurrentMission %d)(NextMission %d)(Teleport %d %d)(Monster %d)(MobAmount %d)(Reward %d))",
					&index, &nextmission, &teleportX, &teleportY, &monsterIndex, &amount, &reward) == 7) {
					MissionInfo mission;
					mission.nextmission = nextmission;
					mission.teleportX = teleportX;
					mission.teleportY = teleportY;
					mission.currentmission = index;
					mission.Monster = monsterIndex;
					mission.Amount = amount;
					mission.rewardID = reward;

					MissionQuests[monsterIndex] = mission;
					MAbandonCheck[index] = mission;
				}
				else if (sscanf(line, "(MissionItem (CurrentMission %d)(NextMission %d)(Teleport %d %d %d)(ItemIndex %[0-9/,])(ItemAmount %[0-9/,])(Reward %d))",
					&index, &nextmission, &teleportMap, &teleportX, &teleportY, &MissionItems, &MissionAmounts, &reward) == 8) {
					std::string ItemsX = std::string((const char*)MissionItems);
					std::string AmountsX = std::string((const char*)MissionAmounts);

					MissionInfo mission;
					mission.nextmission = nextmission;
					mission.teleportX = teleportX;
					mission.teleportY = teleportY;
					mission.teleportMap = teleportMap;
					mission.Items = explode(",", ItemsX);
					mission.Amounts = explode(",", AmountsX);
					mission.rewardID = reward;

					MissionQuestsItem[index] = mission;
				}
			}
			fclose(Missions);
		}
	}


	if (!command || (command && modifiedFiles.count("./Configs/DailyDuty.txt"))) {
		FILE* DDuty = fopen("./Configs/DailyDuty.txt", "r");
		if (DDuty != NULL) {
			DutyQuest.clear();
			DutyMonsterQuests.clear();
			char line[BUFSIZ];
			while (fgets(line, sizeof line, DDuty) != NULL) {
				int index = 0, reward = 0, qlevel = 0, cooldown = 0;
				char nMobs[BUFSIZ], nAmounts[BUFSIZ], Bosses[BUFSIZ], bAmounts[BUFSIZ], iMobs[BUFSIZ], insAmounts[BUFSIZ];
				
				if (sscanf(line, "(Duty (Quest %d)(Level %d)(NormalMobs %[0-9/,])(Amounts %[0-9/,])(MiniBosses %[0-9/,])(Amounts %[0-9/,])(Instances %[0-9/,])(Amounts %[0-9/,])(Reward %d)(Cooldown %d))",
					&index, &qlevel, &nMobs, &nAmounts, &Bosses, &bAmounts, &iMobs, &insAmounts, &reward, &cooldown) == 10) {
					DailyDuty mission;

					std::string nIndexes = std::string((const char*)nMobs);
					std::string nmAmounts = std::string((const char*)nAmounts);

					std::string MIndexes = std::string((const char*)Bosses);
					std::string MmAmounts = std::string((const char*)bAmounts);

					std::string iIndexes = std::string((const char*)iMobs);
					std::string iAmounts = std::string((const char*)insAmounts);
					std::vector<std::string> _nIndexes = explode(",", nIndexes);
					std::vector<std::string> _MIndexes = explode(",", MIndexes);
					std::vector<std::string> _iIndexes = explode(",", iIndexes);

					mission.NormalMob = _nIndexes;
					mission.NormalAmount = explode(",", nmAmounts);

					mission.MiniBoss = _MIndexes;
					mission.BossAmount = explode(",", MmAmounts);

					mission.InstanceD = _iIndexes;
					mission.IMobAmount = explode(",", iAmounts);
					mission.pLevel = qlevel;
					mission.cooldown = cooldown;

					//mission.Boxes = Boxes;
					//mission.BoxAmount = boxAmounts;
					mission.Reward = reward;

					int maxSize = maximum(_MIndexes.size(), maximum(_nIndexes.size(), _iIndexes.size()));

					for (int i = 0; i < maxSize; i++) {
						MonsterDailyDuty mQuest = MonsterDailyDuty();
						mQuest.Quest = index;

						if (i < _MIndexes.size())
							DutyMonsterQuests[String2Int(_MIndexes[i])].push_back(mQuest);

						if (i < _nIndexes.size())
							DutyMonsterQuests[String2Int(_nIndexes[i])].push_back(mQuest);

						if (i < _iIndexes.size())
							DutyMonsterQuests[String2Int(_iIndexes[i])].push_back(mQuest);
					}

					DutyQuest[index] = mission;
				}

			}
			fclose(DDuty);
		}
	}


	if (!command || (command && modifiedFiles.count("./Configs/ExpTable.txt"))) {
		FILE* fileExpTable = fopen("./Configs/ExpTable.txt", "r");
		if (fileExpTable != NULL) {
			char line[BUFSIZ];
			int expTableIndex = 0;

			while (fgets(line, sizeof line, fileExpTable) != NULL) {
				if (strstr(line, "{") != NULL) {
					break;
				}
			}

			while (fgets(line, sizeof line, fileExpTable) != NULL && expTableIndex < sizeof(_ExpTable) / sizeof(_ExpTable[0])) {
				if (strstr(line, "}") != NULL) {
					break;
				}

				char* token = strtok(line, ",");
				while (token != NULL) {
					unsigned __int64 expValue;
					if (sscanf(token, "%llu", &expValue) == 1) {
						_ExpTable[expTableIndex++] = expValue;
					}
					token = strtok(NULL, ",");
				}
			}

			fclose(fileExpTable);
		}
	}

	if (!command || (command && modifiedFiles.count("./Configs/EmoteSystem.txt"))) {
		FILE *fileemote = fopen("./Configs/EmoteSystem.txt", "r");
		if (fileemote != NULL) {
			EmoteSystem.clear();
			char line[BUFSIZ];
			while (fgets(line, sizeof line, fileemote) != NULL) {
				int QuestFlag = 0, itemIndex = 0;
				char Particle[512];

				if (sscanf(line, "(Emote (QuestFlag %d)(Particle '%[a-z | A-Z | 0-9/<>|.,~*;`:!^+%&=?_-£#$€]')(ItemIndex %d))", &QuestFlag, Particle, &itemIndex) == 3) {
					EmoteSystem[QuestFlag] = std::make_pair(Particle, itemIndex);
				}
			}
			fclose(fileemote);
		}
	}
	//if (!command || (command && modifiedfiles.count("./configs/emotesystem.txt"))) {
	//	file *fileemote = fopen("./configs/emotesystem.txt", "r");
	//	if (fileemote != null) {
	//		emotesystem.clear();
	//		char line[bufsiz];
	//		while (fgets(line, sizeof line, fileemote) != null) {
	//			int questflag = 0;
	//			char particle[512];

	//			if (sscanf(line, "(emote (questflag %d)(particle '%[a-z | a-z | 0-9/<>|.,~*;`:!^+%&=?_-£#$€]'))", &questflag, particle) == 2) {
	//				emotesystem[questflag] = particle;
	//			}
	//		}
	//		fclose(fileemote);
	//	}
	//}
	if (!command || (command && modifiedFiles.count("./Configs/BuffSystem.txt"))) {
		FILE *Sys = fopen("./Configs/BuffSystem.txt", "r");
		if (Sys != NULL)
		{
			BuffMakerCheck.clear();
			BuffDisableCheck.clear();
			BuffRemoveCheck.clear();
			char line[1000], LimitMsg[BUFSIZ], BuffDisableID[BUFSIZ], BuffRemoveID[BUFSIZ], BuffIcon[BUFSIZ], ExpALLOW[BUFSIZ], save[BUFSIZ], Egg[BUFSIZ], ItemN[BUFSIZ], mana_heal[BUFSIZ], hp_heal[BUFSIZ], Damage[BUFSIZ], altBuff[BUFSIZ];
			while (fgets(line, sizeof line, Sys) != NULL)
			{
				int Quest_Index = 0, CQuest_Index = 0, Buff = 0, Call = 0, Maker = 0, Delete = 0, MinLevel = 0, MaxLevel = 0, StrBuff = 0, AgiBuff = 0, HthBuff = 0, IntBuff = 0, DefBuff = 0,
					CritBuff = 0, RefBuff = 0, SpeedBuff = 0, LightningDefense = 0, IceDefense = 0, FireDefense = 0, OTPCall = 0, PhysicalAttack = 0, CallofDefense = 0
					, MinAttack = 0, MaxAttack = 0, Hp = 0, Str = 0, Int = 0, Wis = 0, Agi = 0, OTP = 0, Eva = 0, Def = 0, Fire_Resistance = 0, Ice_Resistance = 0
					, Lightning_Resistance = 0, Absorb = 0, CritRate = 0, CritDamage = 0, exp = 0, HTML = 0, Time = 0, Sys_name = 0, BuffID = 0,
					amount = 0, count = 0, Expindex = 0, expcount = 0, HPx = 0, RPx = 0, DKPTx = 0, DKPWx = 0, PLTx = 0, PLWx = 0, SVTx = 0, SVWx = 0,
					Honorindex = 0, Removeindex = 0, mana = 0, hp = 0, MaxHp = 0, MaxMp = 0, MD = 0, EBRate = 0, BuffDisableIndex = 0, BuffRemoveIndex = 0;

				if (sscanf(line, "(ItemBuffDisable (Index %d) (Buff %[0-9/,]))", &BuffDisableIndex, &BuffDisableID) == 2)
				{
					std::string disableBuff = std::string((const char*)BuffDisableID);

					BuffDisableCheck[BuffDisableIndex].BuffDisableIndex = BuffDisableIndex;
					BuffDisableCheck[BuffDisableIndex].BuffDisableID = explode(",", disableBuff);
				}

				if (sscanf(line, "(ItemBuffRemove (Index %d) (Buff %[0-9/,]))", &BuffRemoveIndex, &BuffRemoveID) == 2)
				{
					std::string removeBuff = std::string((const char*)BuffRemoveID);

					BuffRemoveCheck[BuffRemoveIndex].BuffDisableIndex = BuffRemoveIndex;
					BuffRemoveCheck[BuffRemoveIndex].BuffDisableID = explode(",", removeBuff);
				}
				if (sscanf(line, "(Call (Item_Name '%[a-z | A-Z | 0-9/<>|.,~*;`:!^+%&=?_-£#$€]')(Index %d)(Permanently %d)(Level-> Min %d Max %d LimitMsg '%[a-z | A-Z | 0-9/<>|.,~*;`:!^+%&=?_-£#$€]')(Call-> LightningDefense %d IceDefense %d FireDefense %d OTPCall %d PhysicalAttack %d CallofDefense %d))", &ItemN, &Call, &Delete, &MinLevel, &MaxLevel, &LimitMsg, &LightningDefense, &IceDefense, &FireDefense, &OTPCall, &PhysicalAttack, &CallofDefense) == 12)
				{
					ConfigBuff Calls = ConfigBuff();
					Calls.Call = Call;
					Calls.Delete = Delete;
					Calls.MinLevel = MinLevel;
					Calls.MaxLevel = MaxLevel;
					Calls.LimitMsg = LimitMsg;
					Calls.LightningDefense = LightningDefense;
					Calls.IceDefense = IceDefense;
					Calls.FireDefense = FireDefense;
					Calls.OTPCall = OTPCall;
					Calls.PhysicalAttack = PhysicalAttack;
					Calls.CallofDefense = CallofDefense;
					BuffCheck[Call] = Calls;
				}
				if (sscanf(line, "(Maker (Item_Name '%[a-z | A-Z | 0-9/<>|.,~*;`:!^+%&=?_-£#$€]')(Index %d)(Permanently %d)(Level-> Min %d Max %d LimitMsg '%[a-z | A-Z | 0-9/<>|.,~*;`:!^+%&=?_-£#$€]')(Stats-> PhyAtk %d MagAtk %d Hp %d Str %d Int %d Wis %d Agi %d OTP %d Eva %d Def %d Fire_Resistance %d Ice_Resistance %d Lightning_Resistance %d Absorb %d CritRate %d CritDamage %d MaxHp %d MaxMp %d Explosive_Blow %d)(auto_heal Active_HP'%[a-z | A-Z | 0-9/<>|.,~*;`:!^+%&=?_-£#$€]' amount %d Active_MP '%[a-z | A-Z | 0-9/<>|.,~*;`:!^+%&=?_-£#$€]' amount %d)(Damage_monster-> Active '%[a-z | A-Z | 0-9/<>|.,~*;`:!^+%&=?_-£#$€]' Decrease %d)(BuffIcon-> Active '%[a-z | A-Z | 0-9/<>|.,~*;`:!^+%&=?_-£#$€]' Time %d Sys %d BuffID %d [Login '%[a-z | A-Z | 0-9/<>|.,~*;`:!^+%&=?_-£#$€]'])(Exp-> Exp_Active '%[a-z | A-Z | 0-9/<>|.,~*;`:!^+%&=?_-£#$€]' Exp %d Egg_Active '%[a-z | A-Z | 0-9/<>|.,~*;`:!^+%&=?_-£#$€]' Egg %d AltBuff %[0-9/,]))", &ItemN, &Maker, &Delete, &MinLevel, &MaxLevel, &LimitMsg, &MinAttack, &MaxAttack, &Hp, &Str, &Int, &Wis, &Agi, &OTP, &Eva, &Def, &Fire_Resistance, &Ice_Resistance, &Lightning_Resistance, &Absorb, &CritRate, &CritDamage, &MaxHp, &MaxMp, &EBRate, &hp_heal, &hp, &mana_heal, &mana, &Damage, &MD, &BuffIcon, &Time, &Sys_name, &BuffID, &save, &ExpALLOW, &amount, &Egg, &count, &altBuff) == 41)
				{
					BuffMaker buffer = BuffMaker();

					buffer.Maker = Maker;
					buffer.Delete = Delete;
					buffer.MinLevel = MinLevel;
					buffer.MaxLevel = MaxLevel;
					buffer.LimitMsg = LimitMsg;
					buffer.MinAttack = MinAttack;
					buffer.MaxAttack = MaxAttack;
					buffer.Hp = Hp;
					buffer.Str = Str;
					buffer.Int = Int;
					buffer.Wis = Wis;
					buffer.Agi = Agi;
					buffer.OTP = OTP;
					buffer.Eva = Eva;
					buffer.Def = Def;
					buffer.Fire_Resistance = Fire_Resistance;
					buffer.Ice_Resistance = Ice_Resistance;
					buffer.Lightning_Resistance = Lightning_Resistance;
					buffer.Absorb = Absorb;
					buffer.CritRate = CritRate;
					buffer.CritDamage = CritDamage;
					buffer.MaxHp = MaxHp;
					buffer.MaxMp = MaxMp;
					buffer.BuffIcon = BuffIcon;
					buffer.Time = Time;
					buffer.Sys_name = Sys_name;
					buffer.BuffID = BuffID;
					buffer.EBRate = EBRate;
					buffer.save = save;
					buffer.mana = mana;
					buffer.hp = hp;
					buffer.mana_heal = mana_heal;
					buffer.hp_heal = hp_heal;
					buffer.Damage = Damage;
					buffer.MD = MD;
					buffer.ExpALLOW = ExpALLOW;
					buffer.amount = amount;
					buffer.Egg = Egg;
					buffer.count = count;

					std::string alternativeBuffs = std::string((const char*)altBuff);

					buffer.altBuff = explode(",", alternativeBuffs);
					BuffMakerCheck[Maker] = buffer;
				}

				if (sscanf(line, "(NPC_Buff (Quest_Index %d)(Str %d)(Agi %d)(Hth %d)(Int %d)(Def %d)(Crit %d)(Speed %d)(Ref %d)(Level-> Min %d Max %d LimitMsg '%[a-z | A-Z | 0-9/<>|.,~*;`:!^+%&=?_-£#$€]'))",
					&Quest_Index, &StrBuff, &AgiBuff, &HthBuff, &IntBuff, &DefBuff, &CritBuff, &SpeedBuff, &RefBuff, &MinLevel, &MaxLevel, &LimitMsg) == 12)
				{
					BuffCheck[Quest_Index].Quest_Index = Quest_Index;
					BuffCheck[Quest_Index].MinLevel = MinLevel;
					BuffCheck[Quest_Index].MaxLevel = MaxLevel;
					BuffCheck[Quest_Index].LimitMsg = LimitMsg;
					BuffCheck[Quest_Index].StrBuff = StrBuff;
					BuffCheck[Quest_Index].AgiBuff = AgiBuff;
					BuffCheck[Quest_Index].HthBuff = HthBuff;
					BuffCheck[Quest_Index].IntBuff = IntBuff;
					BuffCheck[Quest_Index].DefBuff = DefBuff;
					BuffCheck[Quest_Index].CritBuff = CritBuff;
					BuffCheck[Quest_Index].RefBuff = RefBuff;
					BuffCheck[Quest_Index].SpeedBuff = SpeedBuff;
				}

				if (sscanf(line, "(NPC_Call (Quest_Index %d)(Level-> Min %d Max %d LimitMsg '%[a-z | A-Z | 0-9/<>|.,~*;`:!^+%&=?_-£#$€]')(Call-> LightningDefense %d IceDefense %d FireDefense %d OTPCall %d PhysicalAttack %d CallofDefense %d))"
					, &CQuest_Index, &MinLevel, &MaxLevel, &LimitMsg, &LightningDefense, &IceDefense, &FireDefense, &OTPCall, &PhysicalAttack, &CallofDefense) == 10)
				{
					BuffCheck[CQuest_Index].CQuest_Index = CQuest_Index;
					BuffCheck[CQuest_Index].MinLevel = MinLevel;
					BuffCheck[CQuest_Index].MaxLevel = MaxLevel;
					BuffCheck[CQuest_Index].LimitMsg = LimitMsg;
					BuffCheck[CQuest_Index].LightningDefense = LightningDefense;
					BuffCheck[CQuest_Index].IceDefense = IceDefense;
					BuffCheck[CQuest_Index].FireDefense = FireDefense;
					BuffCheck[CQuest_Index].OTPCall = OTPCall;
					BuffCheck[CQuest_Index].PhysicalAttack = PhysicalAttack;
					BuffCheck[CQuest_Index].CallofDefense = CallofDefense;
				}
			}
			fclose(Sys);
		}
	}



	if (!command || (command && modifiedFiles.count("./Configs/BoundItems.txt"))) {
		FILE *filemo = fopen("./Configs/BoundItems.txt", "r");
		if (filemo != NULL) {
			BoundAllowedItems.clear();
			char line[BUFSIZ];
			while (fgets(line, sizeof line, filemo) != NULL)
			{
				int index = 0;
				if (sscanf(line, "(AllowStorage (Index %d))", &index) == 1)
					BoundAllowedItems.insert(index);
				
			}
			fclose(filemo);
		}
	}

	if (!command || (command && modifiedFiles.count("./Configs/Protection.txt"))) {
		Interface<ITools> Tools;
		RShopItems.clear();
		RShopAmounts.clear();

		std::vector<std::string> shopiex = Tools->Explode(ShopRewardIndex, ",");
		std::vector<std::string> amountiex = Tools->Explode(ShopRewardAmount, ",");
		std::vector<std::string> levelx = Tools->Explode(ShopRewardLvl, ",");

		if (shopiex.size() == amountiex.size() == levelx.size()) {
			for (int i = 0; i < shopiex.size(); i++) {
				RShopItems.push_back(String2Int(shopiex[i]));
				RShopAmounts.push_back(String2Int(amountiex[i]));
				RShopLevels.push_back(String2Int(levelx[i]));

			}
		}
	}

	if (!command || (command && modifiedFiles.count("./Skills/Calculations.txt"))) {
		FILE *filepa = fopen("./Skills/Calculations.txt", "r");
		if (filepa != NULL)
		{
			SkillsDamage.clear();

			char line[BUFSIZ];
			while (fgets(line, sizeof line, filepa) != NULL)
			{
				int SkillID = 0, Class = 0, PVPReduces = 0, AOE = 0, PVEDamageT = 0, PVPDamageT = 0, CritDmgPVP = 0, CritDmgPVE = 0;
				char Damage[BUFSIZ];
				int maxDamage = 0, maxPVPDamage = 0;
				if (sscanf(line, "(EditSkill (class %d)(action %d)(damage '%[a-z | A-Z | 0-9/<>|.,~*;` ():!^+%&=?_-£#$€]')(pvpreduce %d)(maxpvedamage %d)(maxpvpdamage %d)(AOE %d))", &Class, &SkillID, &Damage, &PVPReduces, &maxDamage, &maxPVPDamage, &AOE) == 7)
				{
					SkillDamage sDmg = SkillDamage();
					sDmg.damage = Damage;
					sDmg.Reduce = PVPReduces;
					sDmg.PVE = maxDamage;
					sDmg.PVP = maxPVPDamage;
					sDmg.AOE = AOE;

					SkillsDamage[(Class * 1000) + SkillID] = sDmg;
				}
				else
				{
					SkillID = 0, Class = 0, PVPReduces = 0, AOE = 0, maxDamage = 0, maxPVPDamage = 0;
					memset(Damage, 0, sizeof(Damage));

					int Type = 0;
					if (sscanf(line, "(AdvancedSkill (type %d)(class %d)(action %d)(damage '%[a-z | A-Z | 0-9/<>|.,~*;` ():!^+%&=?_-£#$€]')(maxdamage %d)(AOE %d))", &Type, &Class, &SkillID, &Damage, &maxDamage, &AOE) == 6)
					{
						SkillDamage sDmg = SkillDamage();
						sDmg.damage = Damage;
						sDmg.Reduce = 0;
						sDmg.PVE = maxDamage;
						sDmg.PVP = 0;
						sDmg.AOE = AOE;

						SkillsDamage[(Class * 1000) + (Type * 100) + SkillID] = sDmg;
					}
				}
			}
			fclose(filepa);
		}
	}

	if (!command || (command && modifiedFiles.count("./Configs/Range.txt"))) {
		FILE *filerange = fopen("./Configs/Range.txt", "r");
		if (filerange != NULL)
		{
			CheckRangeConfig.clear();

			char line[BUFSIZ];
			while (fgets(line, sizeof line, filerange) != NULL)
			{
				int classId = 0, skillId = 0, maxRange = 0;
				if (sscanf(line, "(SkillRange (Class %d)(Action %d)(MaxRange %d))", &classId, &skillId, &maxRange) == 3)
					CheckRangeConfig[skillId + (classId * 100)].maxRange = maxRange;

			}
			fclose(filerange);
		}

	}

	if (!command || (command && modifiedFiles.count("./Configs/Pet.txt"))) {
		FILE *file = fopen("./Configs/Pet.txt", "r");
		if (file != NULL)
		{
			PetTime.clear();
			char line[BUFSIZ];
			while (fgets(line, sizeof line, file) != NULL)
			{
				int PetIndex = 0, GetPetTime = 0, Heal = 0, AutoPick = 0, HPLimit = 0, RangePick = 0, EXP = 0, EGGEXP = 0;
				if (sscanf(line, "(pet (index %d)(time %d)(heal %d)(hplimit %d)(autopick %d)(pickrange %d)(addexp %d)(eggexp %d))", &PetIndex, &GetPetTime, &Heal, &HPLimit, &AutoPick, &RangePick, &EXP, &EGGEXP) == 8)
				{
					ConfigPetTime pet = ConfigPetTime();
					pet.Time = GetPetTime;
					pet.Heal = Heal;
					pet.Pick = AutoPick;
					pet.Range = RangePick;
					pet.HPLimit = HPLimit;
					pet.Monster = 0;
					pet.Exp = EXP;
					pet.Egg = EGGEXP;
					PetTime[PetIndex] = pet;
				}
				else {
					int Monster = 0, Speed = 0, Attack = 0, Delay = 0;
					char effects[BUFSIZ];
					if (sscanf(line, "(pet (index %d)(monster %d)(speed %d)(time %d)(heal %d)(hplimit %d)(autopick %d)(pickrange %d)(addexp %d)(eggexp %d)(attack %d)(AOEDelay %d)(effects '%[a-z | A-Z | 0-9/<>|.,~*;`:!^+%&=?_-£#$€]'))", &PetIndex, &Monster, &Speed, &GetPetTime, &Heal, &HPLimit, &AutoPick, &RangePick, &EXP, &EGGEXP, &Attack, &Delay, &effects) >= 10)
					{
						std::string sEffects = std::string((const char*)effects);
						ConfigPetTime pet = ConfigPetTime();
						pet.Time = GetPetTime;
						pet.Heal = Heal;
						pet.HPLimit = HPLimit;
						pet.Pick = AutoPick;
						pet.Range = RangePick;
						pet.Exp = EXP;
						pet.Egg = EGGEXP;
						pet.Monster = Monster;
						pet.AttackPet = Attack;
						pet.effects = explode(",", sEffects);
						pet.AOEDelay = Delay;
						PetTime[PetIndex] = pet;

						MobPets[Monster] = Speed;
					}
				}
			}

			fclose(file);
		}
	}

	if (!command || (command && modifiedFiles.count("./Configs/PKKill.txt"))) {
		FILE *PKKill = fopen("./Configs/PKKill.txt", "r");
		if (PKKill != NULL)
		{
			PKIgnoreItem.clear();
			char line[BUFSIZ];
			while (fgets(line, sizeof line, PKKill) != NULL)
			{
				int index = 0;
				if (sscanf(line, "(ignoreItem (index %d))", &index) == 1)
					PKIgnoreItem.insert(index);
			}

			fclose(PKKill);
		}
	}

	if (!command || (command && modifiedFiles.count("./Configs/SwapItem.txt"))) {
		FILE *initSwapF = fopen("./Configs/SwapItem.txt", "r");
		if (initSwapF != NULL)
		{
			ItemExchanges.clear();
			char line[BUFSIZ];
			while (fgets(line, sizeof line, initSwapF) != NULL)
			{
				int ExchangeID = 0, MID = 0, MAmount = 0, IOut = 0;
				if (sscanf(line, "(itemexchange (index %d) (material (%d %d)) (item %d) )", &ExchangeID, &MID, &MAmount, &IOut) == 4){
					ItemExchange exchange = ItemExchange();
					exchange.Material = MID;
					exchange.MaterialAmount = MAmount;
					exchange.ItemOut = IOut;
					ItemExchanges[ExchangeID] = exchange;
					continue;
				}

				int index = 0, material1 = 0, amount1 = 0, material2 = 0, amount2 = 0, item = 0, chance = 0;
				int item2 = 0, chance2 = 0, item3 = 0, chance3 = 0, item4 = 0, chance4 = 0, item5 = 0, chance5 = 0, item6 = 0, chance6 = 0;
				int count = sscanf(line, "(InitPetSwap	(index %d)	(Material1 %d %d ) (Material2 %d %d ) (item %d %d)	(item %d %d)	(item %d %d)	(item %d %d)	(item %d %d)	(item %d %d))", &index, &material1, &amount1, &material2, &amount2, &item, &chance, &item2, &chance2, &item3, &chance3, &item4, &chance4, &item5, &chance5, &item6, &chance6);
				if (count >= 7) {
					InitSwap initSwap = InitSwap();
					initSwap.Material1 = SwapMaterial(material1, amount1);
					initSwap.Material12 = SwapMaterial(material1, amount1);
					initSwap.Material2 = SwapMaterial(material2, amount2);
					initSwap.Material22 = SwapMaterial(material2, amount2);
					initSwap.items.clear();
					if (item)
						initSwap.items.push_back(SwapItem(item, chance));
					if (item2)
						initSwap.items.push_back(SwapItem(item2, chance2));
					if (item3)
						initSwap.items.push_back(SwapItem(item3, chance3));
					if (item4)
						initSwap.items.push_back(SwapItem(item4, chance4));
					if (item5)
						initSwap.items.push_back(SwapItem(item5, chance5));
					if (item6)
						initSwap.items.push_back(SwapItem(item6, chance6));

					InitPetSwap[index] = initSwap;
					item2 = 0, chance2 = 0, item3 = 0, chance3 = 0, item4 = 0, chance4 = 0, item5 = 0, chance5 = 0, item6 = 0, chance6 = 0;
					index = 0, material1 = 0, amount1 = 0, material2 = 0, amount2 = 0, item = 0, chance = 0;
				}
				else {
					int material11 = 0, amount11 = 0, material21 = 0, amount21 = 0;
					int count = sscanf(line, "(InitPetSwap	(index %d)	(Material1 %d %d )(Material1 %d %d ) (Material2 %d %d )(Material2 %d %d ) (item %d %d)	(item %d %d)	(item %d %d)	(item %d %d)	(item %d %d)	(item %d %d))", &index, &material1, &amount1, &material11, &amount11, &material2, &amount2, &material21, &amount21, &item, &chance, &item2, &chance2, &item3, &chance3, &item4, &chance4, &item5, &chance5, &item6, &chance6);
					if (count >= 11) {
						InitSwap initSwap = InitSwap();

						initSwap.Material1 = SwapMaterial(material1, amount1);
						initSwap.Material12 = SwapMaterial(material11, amount11);
						initSwap.Material2 = SwapMaterial(material2, amount2);;
						initSwap.Material22 = SwapMaterial(material21, amount21);;
						initSwap.items.clear();

						if (item)
							initSwap.items.push_back(SwapItem(item, chance));
						if (item2)
							initSwap.items.push_back(SwapItem(item2, chance2));
						if (item3)
							initSwap.items.push_back(SwapItem(item3, chance3));
						if (item4)
							initSwap.items.push_back(SwapItem(item4, chance4));
						if (item5)
							initSwap.items.push_back(SwapItem(item5, chance5));
						if (item6)
							initSwap.items.push_back(SwapItem(item6, chance6));

						InitPetSwap[index] = initSwap;
						material11 = 0, amount11 = 0, material21 = 0, amount21 = 0;
						item2 = 0, chance2 = 0, item3 = 0, chance3 = 0, item4 = 0, chance4 = 0, item5 = 0, chance5 = 0, item6 = 0, chance6 = 0;
						index = 0, material1 = 0, amount1 = 0, material2 = 0, amount2 = 0, item = 0, chance = 0;
					}
				}
			}

			for (auto x = InitPetSwap.rbegin(); x != InitPetSwap.rend(); x++)
				std::sort(InitPetSwap[x->first].items.begin(), InitPetSwap[x->first].items.end(), sortSwapChance);

			fclose(initSwapF);
		}
	}

	if (!command || (command && modifiedFiles.count("./Configs/State.txt"))) {
		FILE *filekop = fopen("./Configs/State.txt", "r");
		if (filekop != NULL)
		{
			char line[BUFSIZ];
			while (fgets(line, sizeof line, filekop) != NULL)
			{
				int Level = 0, Class = 0, Specialty = 0, OTP = 0, EVA = 0, HP = 0, MP = 0, INT = 0, AGI = 0, DEF = 0, STR = 0, HTH = 0, ATK = 0, ABSORB = 0, WIS = 0;

				if (sscanf(line, "(state (level %d) (class %d) (specialty %d) (str %d) (hth %d) (int %d) (wis %d) (agi %d) (atk %d) (otp %d) (eva %d) (def %d) (absorb %d) (hp %d) (mp %d))", &Level, &Class, &Specialty, &STR, &HTH, &INT, &WIS, &AGI, &ATK, &OTP, &EVA, &DEF, &ABSORB, &HP, &MP) == 15)
				{
					int specs[2];
					specs[0] = Specialty;
					if (Specialty == 23 || Specialty == 7) {
						specs[0] = 7;
						specs[1] = 23;
					}
					if (Specialty == 43 || Specialty == 11) {
						specs[0] = 11;
						specs[1] = 43;
					}
					for (int i = 0; i < 2; i++) {
						if (specs[i]) {
							PlayerStats[(Class * 1000) + (specs[i] * 1000)].Level = Level;
							PlayerStats[(Level * 100) + (Class * 1000) + (specs[i] * 1000)].Agi += AGI;
							PlayerStats[(Level * 100) + (Class * 1000) + (specs[i] * 1000)].OTP += OTP;
							PlayerStats[(Level * 100) + (Class * 1000) + (specs[i] * 1000)].Eva += EVA;
							PlayerStats[(Level * 100) + (Class * 1000) + (specs[i] * 1000)].HP += HP;
							PlayerStats[(Level * 100) + (Class * 1000) + (specs[i] * 1000)].MP += MP;
							PlayerStats[(Level * 100) + (Class * 1000) + (specs[i] * 1000)].Def += DEF;
							PlayerStats[(Level * 100) + (Class * 1000) + (specs[i] * 1000)].Int += INT;
							PlayerStats[(Level * 100) + (Class * 1000) + (specs[i] * 1000)].Wis += WIS;
							PlayerStats[(Level * 100) + (Class * 1000) + (specs[i] * 1000)].ATK += ATK;
							PlayerStats[(Level * 100) + (Class * 1000) + (specs[i] * 1000)].Absorb += ABSORB;
							PlayerStats[(Level * 100) + (Class * 1000) + (specs[i] * 1000)].Str += STR;
						}
					}
				}
			}
			fclose(filekop);
		}
	}


	if (!command || (command && modifiedFiles.count("./Configs/ItemUse.txt"))) {
		FILE *filewe = fopen("./Configs/ItemUse.txt", "r");
		if (filewe != NULL)
		{
			char line[BUFSIZ];
			while (fgets(line, sizeof line, filewe) != NULL)
			{
				int timeindex = 0, extime = 0;
				if (sscanf(line, "(NormalPetExtend (index %d)(time %d))", &timeindex, &extime) == 2)
				{
					ConfigTimeTalisman talis = ConfigTimeTalisman();

					talis.itemindex = timeindex;
					talis.time = extime;
					NormalPetTalisman[timeindex] = talis;
				}

				int mPetTimeIndex = 0, mPetExtime = 0;
				if (sscanf(line, "(MonsterPetExtend (index %d)(time %d))", &mPetTimeIndex, &mPetExtime) == 2)
				{
					ConfigTimeTalisman talis = ConfigTimeTalisman();

					talis.itemindex = mPetTimeIndex;
					talis.time = mPetExtime;
					MonsterPetTalisman[mPetTimeIndex] = talis;
				}

				int CostumeTimeIndex = 0, CostumeExtime = 0;
				if (sscanf(line, "(CostumeExtend (index %d)(time %d))", &CostumeTimeIndex, &CostumeExtime) == 2)
				{
					ConfigTimeTalisman talis = ConfigTimeTalisman();

					talis.itemindex = CostumeTimeIndex;
					talis.time = CostumeExtime;
					CostumeTalisman[CostumeTimeIndex] = talis;
				}

				int SkinTimeIndex = 0, SkinExtime = 0;
				if (sscanf(line, "(SkinExtend (index %d)(time %d))", &SkinTimeIndex, &SkinExtime) == 2)
				{
					ConfigTimeTalisman talis = ConfigTimeTalisman();

					talis.itemindex = SkinTimeIndex;
					talis.time = SkinExtime;
					SkinTalisman[SkinTimeIndex] = talis;
				}

				int ItemIndex = 0, HTMLPage = 0, Remove = 0, Time = 0, Prevent = 0, AddIcon = 0;
				if (sscanf(line, "(ItemWindow (Index %d)(HTML %d)(Remove %d))", &ItemIndex, &HTMLPage, &Remove) == 3)
				{
					ItemUsed[ItemIndex].HTML = HTMLPage;
					ItemUsed[ItemIndex].Remove = Remove;
				}

				int ItemIndeX = 0, ItemIndeXPerm = 0, ItemBuffServer = 0, ItemRemove = 0, ItemLevel = 0;
				if (sscanf(line, "(ItemTasty (Index %d)(Remove %d)(Level %d))", &ItemIndeX, &ItemRemove, &ItemLevel) == 3)
				{
					ItemTasty[ItemIndeX].index = ItemIndeX;
					ItemTasty[ItemIndeX].remove = ItemRemove;
					ItemTasty[ItemIndeX].level = ItemLevel;

				}

				if (sscanf(line, "(ItemAbsorb (Index %d)(Remove %d)(Level %d))", &ItemIndeX, &ItemRemove, &ItemLevel) == 3)
				{
					ItemHpDef[ItemIndeX].index = ItemIndeX;
					ItemHpDef[ItemIndeX].remove = ItemRemove;
					ItemHpDef[ItemIndeX].level = ItemLevel;

				}

				if (sscanf(line, "(ItemScrolls (Index %d)(Remove %d)(Level %d))", &ItemIndeX, &ItemRemove, &ItemLevel) == 3)
				{
					ItemScrolls[ItemIndeX].index = ItemIndeX;
					ItemScrolls[ItemIndeX].remove = ItemRemove;
					ItemScrolls[ItemIndeX].level = ItemLevel;

				}

				if (sscanf(line, "(ItemBuffServer (Index %d))", &ItemBuffServer) == 1)
				{
					ItemBuffSrv[ItemBuffServer].index = ItemBuffServer;
				}


				if (sscanf(line, "(ItemExpansion (Index %d)(Days %d)(Remove %d)(Level %d))", &ItemIndeX, &Time, &ItemRemove, &ItemLevel) == 4)
				{
					ItemExpansion[ItemIndeX].index = ItemIndeX;
					ItemExpansion[ItemIndeX].remove = ItemRemove;
					ItemExpansion[ItemIndeX].level = ItemLevel;
					ItemExpansion[ItemIndeX].Time = Time;


				}
				int Item = 0, Quest = 0, Flag = 0;
				if (sscanf(line, "(ItemQuest (Index %d)(Quest %d %d))", &Item, &Quest, &Flag) == 3)
				{
					ItemQuest[Item] = (Quest << 16) | Flag;
				}

				else {
					if (sscanf(line, "(ItemQuest (Index %d)(Quest %d))", &Item, &Quest) == 2)
					{
						ItemQuest[Item] = (Quest << 16) | 1;
					}
				}

				int ItemN = 0, NPC = 0;
				if (sscanf(line, "(ItemNPC (Index %d)(NPC %d))", &ItemN, &NPC) == 2)
				{
					ItemNPC[ItemN] = NPC;
				}

				int ItemU = 0, ILimit = 0, ITime = 0;
				if (sscanf(line, "(ItemLimit (Index %d)(Limit %d)(Time %d))", &ItemU, &ILimit, &ITime) == 3)
				{
					ItemLimits[ItemU].Usage = ILimit;
					ItemLimits[ItemU].Time = ITime;
				}

				char url[BUFSIZ];
				if (sscanf(line, "(ItemWebsite (Index %d)(Link '%[a-z | A-Z | 0-9/<>|.,~*;`:!^+%&=?_-£#$€]')(Remove %d))", &ItemN, &url, &Remove) == 3) {
					ItemWebsite[ItemN].URL = url;
					ItemWebsite[ItemN].remove = Remove;
				}

				int RewardID = 0;
				if (sscanf(line, "(ItemReward (Index %d)(RewardID %d))", &ItemN, &RewardID) == 2) {
					ItemReward[ItemN] = RewardID;
				}

				int ItemS = 0, NPCS = 0, StoreS = 0, TimeS = 0, ModelS = 0;
				if (sscanf(line, "(ItemStoreNPC (Index %d)(NPC %d)(Model %d)(Store %d)(Time %d))", &ItemS, &NPCS, &ModelS, &StoreS, &TimeS) == 5)
				{
					ItemNPCSummoned[ItemS].NPC = NPCS;
					ItemNPCSummoned[ItemS].Store = StoreS;
					ItemNPCSummoned[ItemS].Model = ModelS;
					ItemNPCSummoned[ItemS].Time = TimeS;
				}

				int IndexDisable = 0, Area = 0;
				if (sscanf(line, "(ItemDisable (Index %d)(Map %d))", &IndexDisable, &Area) == 2)
				{
					ItemDisable.insert(IndexDisable*(Area + 1000));
				}

				int AucDisable = 0;
				if (sscanf(line, "(AuctionItemDisable (Index %d))", &AucDisable) == 1)
				{
					AuctionItemDisable.insert(AucDisable);
				}

				int IndexaDisable = 0, MapX = 0, MapY = 0;
				if (sscanf(line, "(ItemDisable (Index %d)(File %d_%d))", &IndexaDisable, &MapX, &MapY) == 3)
				{
					ItemDisable.insert(IndexaDisable*((MapX + 1000)*(MapY + 100)));
				}
			}
			fclose(filewe);
		}
	}


	if (!command || (command && modifiedFiles.count("./Configs/Jail.txt"))) {
		FILE *JailCoordsFile = fopen("./Configs/Jail.txt", "r");
		if (JailCoordsFile != NULL)
		{
			JailCoords.clear();
			char line[BUFSIZ];
			while (fgets(line, sizeof line, JailCoordsFile) != NULL)
			{
				int X = 0, Y = 0, Z = 0;
				if (sscanf(line, "(jailCoord (X %d)(Y %d)(Z %d))", &X, &Y, &Z) == 3)
				{
					Point coord = Point();
					coord.X = X;
					coord.Y = Y;
					coord.Z = Z;
					JailCoords.push_back(coord);
				}
				else
				if (sscanf(line, "(jailCoord (X %d)(Y %d))", &X, &Y) == 2)
				{
					Point coord = Point();
					coord.X = X;
					coord.Y = Y;
					coord.Z = 0;
					JailCoords.push_back(coord);
				}
			}
			fclose(JailCoordsFile);
		}
	}

	if (!command || (command && modifiedFiles.count("./Configs/OrnamentBuff.txt"))) {
		FILE *OrnamentBuff = fopen("./Configs/OrnamentBuff.txt", "r");
		if (OrnamentBuff != NULL)
		{
			NecklaceBuffs.clear();
			BeltBuffs.clear();

			char line[BUFSIZ];
			while (fgets(line, sizeof line, OrnamentBuff) != NULL)
			{
				int index = 0, dmg = 0, crit = 0, duration = 0, cooldown = 0, hp = 0;
				char Effect[BUFSIZ];
				if (sscanf(line, "(necklaceBuff (index %d) (dmg %d) (critchance %d) (duration %d) (cooldown %d) (effect '%[a-z | A-Z | 0-9/<>|.,~*;`:!^+%&=?_-£#$€]'))", &index, &dmg, &crit, &duration, &cooldown, &Effect) == 6)
				{
					NecklaceBuff nBuff = NecklaceBuff();
					nBuff.Cooldown = cooldown;
					nBuff.CritChance = crit;
					nBuff.Dmg = dmg;
					nBuff.Duration = duration;
					nBuff.Cooldown = cooldown;
					nBuff.Effect = Effect;
					NecklaceBuffs[index] = nBuff;
				}
				else
					if (sscanf(line, "(beltBuff (index %d) (hpincrease %d) (duration %d) (cooldown %d) (effect '%[a-z | A-Z | 0-9/<>|.,~*;`:!^+%&=?_-£#$€]'))", &index, &hp, &duration, &cooldown, &Effect) == 5)
					{
						BeltBuff bBuff = BeltBuff();
						bBuff.Cooldown = cooldown;
						bBuff.HP = hp;
						bBuff.Duration = duration;
						bBuff.Effect = Effect;
						bBuff.Cooldown = cooldown;
						BeltBuffs[index] = bBuff;
					}
			}
			fclose(OrnamentBuff);
		}
	}

	if (!command || (command && modifiedFiles.count("./Configs/AntiKs.txt"))) {
		FILE *AntiKsFile = fopen("./Configs/AntiKs.txt", "r");
		if (AntiKsFile != NULL)
		{
			char line[BUFSIZ];
			while (fgets(line, sizeof line, AntiKsFile) != NULL)
			{
				int index = 0;

				if (sscanf(line, "(disable (index %d))", &index) == 1)
				{
					AntiKs.insert(index);
				}
			}
			fclose(AntiKsFile);
		}
	}

	if (!command || (command && modifiedFiles.count("./Configs/Starter.txt"))) {
		FILE *StarterFile = fopen("./Configs/Starter.txt", "r");
		if (StarterFile != NULL)
		{
			StarterItems.clear();
			char line[BUFSIZ];
			while (fgets(line, sizeof line, StarterFile) != NULL)
			{
				int Class = 0, Info = 0, RewardIndex = 0, Amount = 0, Bof = 0, Dss = 0, Def = 0, Eva = 0, Prefix = 0, Atk = 0, Magic = 0, TOA = 0, UPG = 0, Mix = 0, Type = 0;

				if (sscanf(line, "(starterItem (class %d)(index %d)(amount %d)(info %d)(prefix %d)(defense %d)(evasion %d)(attack %d)(magic %d)(toa %d)(upgrade %d)(mix %d)(bof %d)(dss %d)(type %d))", &Class, &RewardIndex, &Amount, &Info, &Prefix, &Def, &Eva, &Atk, &Magic, &TOA, &UPG, &Mix, &Bof, &Dss, &Type) == 15)
				{
					Items t = Items();
					t.Index = RewardIndex;
					t.Amount = Amount;
					t.Bof = Bof;
					t.Def = Def;
					t.Info = Info;
					t.Dss = Dss;
					t.Eva = Eva;
					t.Prefix = Prefix;
					t.Attack = Atk;
					t.Magic = Magic;
					t.Mix = Mix;
					t.Toa = TOA;
					t.Upgrade = UPG;
					t.Type = Type;

					StarterItems[Class].push_back(t);
				}
				else {
					int Map = 0, X = 0, Y = 0, HTML = 0;
					char msg[BUFSIZ];
					memset(msg, 0, sizeof(msg));
					signed __int64 EXP = 0;
					if (sscanf(line, "(starter (Class %d)(Map %d)(X %d)(Y %d)(EXP %lld)(HTML %d)(WelcomeMsg '%[a-z | A-Z | 0-9/<>|.,~*;`:!^+%&=?_-£#$€]'))", &Class, &Map, &X, &Y, &EXP, &HTML, &msg) >= 6)
					{
						StarterClass newClass = StarterClass();
						newClass.CoordX = X;
						newClass.CoordY = Y;
						newClass.EXP = EXP;
						newClass.Map = Map;
						newClass.HTML = HTML;
						if (msg && strlen(msg))
							newClass.Msg = msg;
						else
							newClass.Msg = "";

						Starters[Class] = newClass;
					}
				}
			}
			fclose(StarterFile);
		}
	}

	if (!command || (command && modifiedFiles.count("./Configs/EventTimer.txt"))) {
		FILE *timerEvent = fopen("./Configs/EventTimer.txt", "r");
		if (timerEvent != NULL)
		{
			EventTimer.clear();
			EndTimer.clear();
			char line[BUFSIZ];
			while (fgets(line, sizeof line, timerEvent) != NULL)
			{
				char type[BUFSIZ], day[BUFSIZ];
				int hour = 0, minute = 0, second = 0, hend = 0, mend = 0, send = 0;

				if (sscanf(line, "(system (Type '%[a-z | A-Z | 0-9/<>|.,~*;`:!^+%&=?_-£#$€]')(Day '%[a-z | A-Z | 0-9/<>|.,~*;`:!^+%&=?_-£#$€]')(Time '%d:%d:%d')(End '%d:%d:%d'))", &type, &day, &hour, &minute, &second, &hend, &mend, &send) == 8)
				{
					std::string realDay(day);

					int day = EventConfig(realDay);

					int indexstart = IntTime(day, hour, minute, second);

					int indexend = IntTime(day, hend, mend, send);

					EventTimer[indexstart] += type;
					EndTimer[indexend] += type;
				}

				else if (sscanf(line, "(system (Type '%[a-z | A-Z | 0-9/<>|.,~*;`:!^+%&=?_-£#$€]')(Day '%[a-z | A-Z | 0-9/<>|.,~*;`:!^+%&=?_-£#$€]')(Time '%d:%d:%d'))", &type, &day, &hour, &minute, &second) == 5)
				{
					std::string realDay(day);
					int day = EventConfig(realDay);

					int index = IntTime(day, hour, minute, second);

					EventTimer[index] += type;
				}

			}
			fclose(timerEvent);
		}
	}

	if (!command || (command && modifiedFiles.count("./Configs/Boxes.txt"))) {
		FILE *filte = fopen("./Configs/Boxes.txt", "r");
		if (filte != NULL)
		{
			Boxes.clear();
			char line[BUFSIZ];
			while (fgets(line, sizeof line, filte) != NULL)
			{
				char RewardIndex[BUFSIZ], Amount[BUFSIZ];
				int BoxIndex = 0, Bof = 0, Dss = 0, Def = 0, Eva = 0, Prefix = 0, Atk = 0, Magic = 0, TOA = 0, UPG = 0, Mix = 0, stat = 0, bound = 0, rewardID = 0;
				if (sscanf(line, "(box (index %d)(rewardindex %[0-9/,])(amount %[0-9/,])(prefix %d)(defense %d)(evasion %d)(attack %d)(magic %d)(toa %d)(upgrade %d)(mix %d)(bof %d)(dss %d)(itemstat %d)(bound %d))", &BoxIndex, &RewardIndex, &Amount, &Prefix, &Def, &Eva, &Atk, &Magic, &TOA, &UPG, &Mix, &Bof, &Dss, &stat, &bound) >= 13)
				{
					std::string Indexes = std::string((const char*)RewardIndex);
					std::string Amounts = std::string((const char*)Amount);

					SBoxes t = SBoxes();
					t.Rewards = explode(",", Indexes);
					t.Amounts = explode(",", Amounts);
					t.Bof = Bof;
					t.Bound = bound;
					t.Def = Def;
					t.Dss = Dss;
					t.Eva = Eva;
					t.Prefix = Prefix;
					t.Attack = Atk;
					t.Magic = Magic;
					t.Mix = Mix;
					t.Toa = TOA;
					t.Upgrade = UPG;
					t.ItemStat = stat;
					Boxes[BoxIndex] = t;
				}

			}
			fclose(filte);
		}
	}
	// commar
	if (!command || (command && modifiedFiles.count("./Configs/Rewards.txt"))) {
		FILE *filte = fopen("./Configs/Rewards.txt", "r");
		if (filte != NULL)
		{
			Interface<ITools> ITools;
			char line[BUFSIZ];
			while (fgets(line, sizeof line, filte) != NULL)
			{
				char indexes[BUFSIZ], amounts[BUFSIZ], notice[BUFSIZ];
				memset(notice, 0, sizeof(notice));
				int ID = 0, HonorPts = 0, RewardPts = 0, HTML = 0, Bound = 0, HousePoints = 0;
		//		int userKey = 0;
				signed __int64 EXP = 0;
				if (sscanf(line, "(Reward (ID %d) (ItemIndex %[0-9/,]) (ItemAmount %[0-9/,]) (HonorPt %d) (RewardPt %d) (EXP %lld) (HTML %d) (Bound %d) (Msg '%[a-z | A-Z | 0-9/<>|.,~*;`:!^+%&=?_-£#$€]'))", &ID, &indexes, &amounts, &HonorPts, &RewardPts, &EXP, &HTML, &Bound, &notice) >= 8)
				{
					std::string sBIndexs = std::string((const char*)indexes);
					std::string sBAmounts = std::string((const char*)amounts);

					Reward pReward = Reward();
					pReward.Indexes = explode(",", sBIndexs);
					pReward.Amounts = explode(",", sBAmounts);
					pReward.EXP = EXP;
					pReward.HonorPts = HonorPts;
					pReward.RewardPts = RewardPts;
					pReward.HTML = HTML;
					pReward.Bound = Bound;
					if (notice && strlen(notice))
						pReward.Notice = notice;
					else
						pReward.Notice = ""; // Set to empty string for rewards without a message

					if (pReward.Indexes.size() == pReward.Amounts.size())
						Rewards[ID] = pReward;
				}

				if (PeaceEvil && sscanf(line, "(RewardHouse (ID %d) (ItemIndex %[0-9/,]) (ItemAmount %[0-9/,]) (HonorPt %d) (RewardPt %d) (EXP %lld) (HTML %d) (Bound %d) (HousePoints %d))", &ID, &indexes, &amounts, &HonorPts, &RewardPts, &EXP, &HTML, &Bound, &HousePoints) >= 8)
				{
					std::string sBIndexs = std::string((const char*)indexes);
					std::string sBAmounts = std::string((const char*)amounts);

					Reward pReward = Reward();
					pReward.Indexes = explode(",", sBIndexs);
					pReward.Amounts = explode(",", sBAmounts);
					pReward.EXP = EXP;
					pReward.HonorPts = HonorPts;
					pReward.RewardPts = RewardPts;
					pReward.HTML = HTML;
					pReward.Bound = Bound;
					pReward.HousePoints = HousePoints;
					if (pReward.Indexes.size() == pReward.Amounts.size())
						Rewards[ID] = pReward;
				}
				//_snprintf(keyLine, sizeof(keyLine), "ExpReward (Key %d)", userKey);
				//if (strstr(line, keyLine)) {
				//		int Level = 0;
				//		int Percentage = 0;
				//		if (sscanf(line, "(Exp (Level %d) (Percentage %d))", &Level, &Percentage) == 2) {
				//			std::string sBIndexs = std::string((const char*)indexes);
				//			std::string sBAmounts = std::string((const char*)amounts);

				//			Reward pReward = Reward();
				//			pReward.Indexes = explode(",", 0);
				//			pReward.Amounts = explode(",", 0);
				//			pReward.EXP = 0;
				//			pReward.HonorPts = 0;
				//			pReward.RewardPts = 0;
				//			pReward.HTML = 0;
				//			pReward.Bound = 0;
				//			pReward.HousePoints = 0;
				//			pReward.userKey = userKey;
				//			if (pReward.Indexes.size() == pReward.Amounts.size())
				//				Rewards[userKey] = pReward;
				//			F10EXPRewards[Level].Level = Level;
				//			F10EXPRewards[Level].Progress = Percentage;

				//		}
				//	}
				}
			}
		}
	

	if (!command || (command && modifiedFiles.count("./Systems/PartyVsParty.txt"))) {
		FILE *filte = fopen("./Systems/PartyVsParty.txt", "r");
		if (filte != NULL)
		{
			PartyTimer.clear();
			char line[BUFSIZ];
			while (fgets(line, sizeof line, filte) != NULL)
			{
				int PTSize = 0, QIndex = 0, QFlag = 0, PVPArena = 0, MinL = 0, MaxL = 0, RID = 0, PTTime = 0;
				char RStart[BUFSIZ], REnd[BUFSIZ], StartTime[BUFSIZ], Day[BUFSIZ], commands[BUFSIZ];

				if (sscanf(line, "(PartyVsParty (Quest %d %d) (PVPArena %d) (PartySize %d) (Level %d-%d) (RewardID %d) (Day '%[a-z | A-Z | 0-9/<>|.,~*;`:!^+%&=?_-£#$€]') (RegistrationTime '%[a-z | A-Z | 0-9/<>|.,~*;`:!^+%&=?_-£#$€]'-'%[a-z | A-Z | 0-9/<>|.,~*;`:!^+%&=?_-£#$€]') (StartTime '%[a-z | A-Z | 0-9/<>|.,~*;`:!^+%&=?_-£#$€]') (commands '%[a-z | A-Z | 0-9/<>|.,~*;`:!^+%&=?_-£#$€]') (DuelTime %d))", &QIndex, &QFlag, &PVPArena, &PTSize, &MinL, &MaxL, &RID, &Day, &RStart, &REnd, &StartTime, &commands, &PTTime) >= 12)
				{
					if (PVPArena > 8)
						PVPArena %= 8;

					if (!PVPArena)
						PVPArena = 1;

					PartyReg Reg = PartyReg();
					Reg.Day = Day;
					Reg.PartySize = PTSize;
					Reg.ArenaTime = PTTime;
					Reg.PVPArena = PVPArena;
					Reg.MaxLevel = MaxL;
					Reg.MinLevel = MinL;
					Reg.Time = StartTime;
					Reg.Quest = ((QIndex % 65536) * 1000) + QFlag;
					Reg.RewardID = RID;

					if (!command) {
						PTEnabled[Reg.Quest] = Reg;
						PTEnabled[Reg.Quest].Type = 3;
					}
					std::string commandsList = std::string((const char*)commands);
					std::vector<std::string> commandsVec = explode(",", commandsList);

					Reg.Type = 0;
					PartyTimer[RStart].push_back(Reg);
					if (commandsVec.size())
						PTCommands[commandsVec[0]] = Reg;
					Reg.Type = 1;
					PartyTimer[REnd].push_back(Reg);
					if (commandsVec.size()>1)
						PTCommands[commandsVec[1]] = Reg;
					Reg.Type = 2;
					PartyTimer[StartTime].push_back(Reg);
					if (commandsVec.size()>2)
						PTCommands[commandsVec[2]] = Reg;
				}

				else {
					char battleIndex[BUFSIZ], battleAmount[BUFSIZ], winnerIndex[BUFSIZ], winnerAmount[BUFSIZ];
					int ID = 0, battleHonor = 0, battleReward = 0, winnerHonor = 0, winnerReward = 0;
					if (sscanf(line, "(Reward (ID %d) (battleIndexes %[0-9/,]) (battleAmounts %[0-9/,]) (battleHonorPt %d) (battleRewardPt %d) (winnerIndexes %[0-9/,]) (winnerAmounts %[0-9/,]) (winnerHonorPt %d) (winnerRewardPt %d))", &ID, &battleIndex, &battleAmount, &battleHonor, &battleReward, &winnerIndex, &winnerAmount, &winnerHonor, &winnerReward) == 9)
					{
						std::string sBIndexs = std::string((const char*)battleIndex);
						std::string sBAmounts = std::string((const char*)battleAmount);
						std::string sWIndexs = std::string((const char*)winnerIndex);
						std::string sWAmounts = std::string((const char*)winnerAmount);

						PartyReward pReward = PartyReward();

						pReward.battleIndexes = explode(",", sBIndexs);
						pReward.battleAmounts = explode(",", sBAmounts);
						pReward.winnerIndexes = explode(",", sWIndexs);
						pReward.winnerAmounts = explode(",", sWAmounts);

						if (pReward.battleIndexes.size() == pReward.battleAmounts.size() && pReward.winnerIndexes.size() == pReward.winnerAmounts.size()) {
							pReward.BattleReward = battleReward;
							pReward.BattleHonor = battleHonor;
							pReward.WinnerHonor = winnerHonor;
							pReward.WinnerReward = winnerReward;

							PartyRewards[ID] = pReward;
						}

						memset(battleIndex, 0, sizeof(battleIndex));
						memset(battleAmount, 0, sizeof(battleAmount));
						memset(winnerIndex, 0, sizeof(winnerIndex));
						memset(winnerAmount, 0, sizeof(winnerAmount));
					}
				}
			}
			fclose(filte);
		}
	}

	if (!command || (command && modifiedFiles.count("./Configs/QuestLevel.txt"))) {
		FILE *falex = fopen("./Configs/QuestLevel.txt", "r");
		if (falex != NULL)
		{
			QuestLevels.clear();
			char line[BUFSIZ];
			while (fgets(line, sizeof line, falex) != NULL)
			{
				int QIndex = 0, QFlag = 0, LevelMin = 0, LevelMax = 0;;
				if (sscanf(line, "(QuestLevel (index %d %d)(LevelMin %d)(LevelMax %d))", &QIndex, &QFlag, &LevelMin, &LevelMax) == 4)
				{
					QuestLevel qlvl = QuestLevel();
					qlvl.LevelMin = LevelMin;
					qlvl.LevelMax = LevelMax;
					QuestLevels[((QIndex % 65536) * 1000) + QFlag] = qlvl;
				}
			}
			fclose(falex);
		}
	}

	if (!command || (command && modifiedFiles.count("./Configs/PlayerVsPlayer.txt"))) {
		FILE *falex = fopen("./Configs/PlayerVsPlayer.txt", "r");
		if (falex != NULL)
		{
			PlayerVsPlayerDmg.clear();
			char line[BUFSIZ];
			while (fgets(line, sizeof line, falex) != NULL)
			{
				int Class = 0, Spec = 0, TClass = 0, TSpec = 0, Rate = 0;
				if (sscanf(line, "(PVP (Class %d)(Specialty %d)(TargetClass %d)(TargetSpecialty %d)(Rate %d))", &Class, &Spec, &TClass, &TSpec, &Rate) == 5)
					PlayerVsPlayerDmg[(Class * 100000) + (Spec * 1000) + (TClass * 100) + TSpec] = Rate;
			}
			fclose(falex);
		}
	}

	if (!command || (command && modifiedFiles.count("./Configs/QuestDisable.txt"))) {
		FILE *falex = fopen("./Configs/QuestDisable.txt", "r");
		if (falex != NULL)
		{
			QuestDisable.clear();
			QBattleEnable.clear();
			char line[BUFSIZ];
			while (fgets(line, sizeof line, falex) != NULL)
			{
				int QIndex1 = 0, QFlag1 = 0;
				if (sscanf(line, "(BattleEnable (index %d %d))", &QIndex1, &QFlag1) == 2)
					QBattleEnable.insert(((QIndex1 % 65536) * 1000) + QFlag1);

				else {
					int QIndex = 0, QFlag = 0;
					if (sscanf(line, "(QuestDisable (index %d %d))", &QIndex, &QFlag) == 2)
					{
						QuestDisable.insert(((QIndex % 65536) * 10000) + QFlag);
					}

					int Index = 0, Flag = 0, MapX = 0, MapY = 0;
					if (sscanf(line, "(QuestDisable (index %d %d)(File %d_%d))", &Index, &Flag, &MapX, &MapY) == 4)
					{
						QuestDisable.insert(((Index % 65536) * 10000) + Flag + (MapX * 100) + (MapY * 10));
					}

					int MIndex = 0, MFlag = 0, Map = 0;
					if (sscanf(line, "(QuestDisable (index %d %d)(Map %d))", &MIndex, &MFlag, &Map) == 3)
					{
						QuestDisable.insert(((Index % 65536) * 10000) + Flag + (Map * 5000));
					}
				}
			}
			fclose(falex);
		}
	}

	if (!command || (command && modifiedFiles.count("./Configs/QuestWebsite.txt"))) {
		FILE *falex = fopen("./Configs/QuestWebsite.txt", "r");
		if (falex != NULL)
		{
			CustomCommands.clear();
			QuestWebsite.clear();
			char line[BUFSIZ];
			while (fgets(line, sizeof line, falex) != NULL)
			{
				for (int i = 0; i < strlen(line); i++) {
					if (line[i] == '-')
						line[i] = '!';
				}

				int QIndex = 0, QFlag = 0;

				char url[BUFSIZ], cmd[BUFSIZ];

				if (sscanf(line, "(QuestWebsite (index %d %d)(Link '%[a-z | A-Z | 0-9/<>|.,~*;`:!^+%&=?_-£#$€]'))", &QIndex, &QFlag, &url) == 3) {
					for (int i = 0; i < strlen(url); i++) {
						if (url[i] == '!')
							url[i] = '-';
					}

					QuestWebsite[((QIndex % 65536) * 1000) + QFlag] = url;
				}


				if (sscanf(line, "(WebsiteCmd (command '%[a-z | A-Z | 0-9/<>|.,~*;`:!^+%&=?_-£#$€]')(Link '%[a-z | A-Z | 0-9/<>|.,~*;`:!^+%&=?_-£#$€]'))", &cmd, &url) == 2) {
					for (int i = 0; i < strlen(url); i++) {
						if (url[i] == '!')
							url[i] = '-';
					}
					CustomCommands[cmd].Link = url;
				}


			}
			fclose(falex);
		}
	}

	if (!command || (command && modifiedFiles.count("./Configs/TimedQuests.txt"))) {
		FILE *faltex = fopen("./Configs/TimedQuests.txt", "r");
		if (faltex != NULL)
		{
			char line[BUFSIZ];
			int id = 0;
			while (fgets(line, sizeof line, faltex) != NULL)
			{
				int QIndex = 0, QFlag = 0, Repeat = 0, Time = 0;
				int hour = 0, minute = 0, second = 0; 
				
				if (sscanf(line, "(TimedQuest (index %d %d)(maxrepeat %d)(resettime '%d:%d:%d'))", &QIndex, &QFlag, &Repeat, &hour, &minute, &second) == 6)
				{
					QuestTime time = QuestTime();
					time.Type = 1;
					time.Time = (hour * 3600) + (minute * 60) + second;
					time.MaxRepeat = Repeat;
					TimedQuest[((QIndex % 65536) * 1000) + QFlag] = time;
				}
				else
				if (sscanf(line, "(TimedQuest (index %d %d)(maxrepeat %d)(time %d))", &QIndex, &QFlag, &Repeat, &Time) == 4)
				{
					QuestTime time = QuestTime();
					time.Type = 0;
					time.Time = Time;
					time.MaxRepeat = Repeat;
					TimedQuest[((QIndex % 65536)* 1000) + QFlag] = time;
				}
			}
			fclose(faltex);
		}
	}

	if (!command || (command && modifiedFiles.count("./Configs/AreaQuests.txt"))) {
		FILE *faltex = fopen("./Configs/AreaQuests.txt", "r");
		if (faltex != NULL)
		{
			AreaQuests.clear();
			TimedMaps.clear();

			char line[BUFSIZ];
			while (fgets(line, sizeof line, faltex) != NULL)
			{
				int QIndex = 0, QFlag = 0, Party = 0, LevelMin = 0, LevelMax = 0, Time = 0, TX = 0, TY = 0, TMap = 0;
				char ksm[BUFSIZ];
				if (sscanf(line, "(quest (index %d %d)(ksm %[0-9\\,_])(level %d-%d)(party %d)(time %d)(teleport %d %d %d))", &QIndex, &QFlag, &ksm, &LevelMin, &LevelMax, &Party, &Time, &TMap, &TX, &TY) == 10)
				{
					AreaQuest quest = AreaQuest();
					quest.LevelMin = LevelMin;
					quest.LevelMax = LevelMax;
					quest.Time = Time;
					quest.Party = Party;
					quest.TX = TX;
					quest.TY = TY;
					std::vector<std::string> KSM_ = explode(",", std::string((const char*)ksm));

					for (int i = 0; i < KSM_.size(); i++) {
						std::vector<std::string> XPR = explode("_", KSM_[i]);
						if (XPR.size() > 1)
							TimedMaps.insert((String2Int(XPR[0]) * 1000) + String2Int(XPR[1]));
					}
					TimedMaps.insert(((TX >> 13) * 1000) + (TY >> 13));
					quest.TMap = TMap;
					AreaQuests[((QIndex % 65536) * 1000) + QFlag] = quest;
				}
			}
			fclose(faltex);
		}
	}

	if (!command || (command && modifiedFiles.count("./Configs/Channel.txt"))) {
		FILE *filetx = fopen("./Configs/Channel.txt", "r");
		if (filetx != NULL)
		{
			UnChannel.clear();
			ChannelMaps.clear();
			char line[BUFSIZ];
			while (fgets(line, sizeof line, filetx) != NULL)
			{
				int MapX = 0, MapY = 0;
				if (sscanf(line, "(disable (file %d_%d))", &MapX, &MapY) == 2)
					UnChannel.insert((MapX * 1000) + MapY);
				else
				if (sscanf(line, "(enable (file %d_%d))", &MapX, &MapY) == 2)
					ChannelMaps.insert((MapX * 1000) + MapY);
			}
			fclose(filetx);
		}
	}



	if (!command || (command && modifiedFiles.count("./Configs/FatalDamage.txt"))) {
		FILE *filetx = fopen("./Configs/FatalDamage.txt", "r");
		if (filetx != NULL)
		{
			FatalDmg.clear();
			char line[BUFSIZ];
			while (fgets(line, sizeof line, filetx) != NULL)
			{
				int Class = 0, Spec = 0, Rate = 0;
				if (sscanf(line, "(fataldmg (class %d)(specialty %d)(rate %d))", &Class, &Spec, &Rate) == 3)
					FatalDmg[(Class * 1000) + Spec] = Rate;
			}
			fclose(filetx);
		}
	}

	if (!command || (command && modifiedFiles.count("./Configs/MonsterDamage.txt"))) {
		FILE *filetx = fopen("./Configs/MonsterDamage.txt", "r");
		if (filetx != NULL)
		{
			UnAggro.clear();
			char line[BUFSIZ];
			while (fgets(line, sizeof line, filetx) != NULL)
			{
				int CheckMobIndex = 0;
				if (sscanf(line, "(ignoreAggro (index %d))", &CheckMobIndex) == 1)
					UnAggro.insert(CheckMobIndex);
			}
			fclose(filetx);
		}
	}

	if (!command || (command && modifiedFiles.count("./Configs/UnBlob.txt"))) {
		UnBlob.clear();
		FILE *filex = fopen("./Configs/UnBlob.txt", "r");
		if (filex != NULL)
		{
			char line[BUFSIZ];
			while (fgets(line, sizeof line, filex) != NULL)
			{
				int CheckMobIndex = 0;
				if (sscanf(line, "(unblob (index %d))", &CheckMobIndex) == 1)
					UnBlob.insert(CheckMobIndex);
			}
			fclose(filex);
		}

		UnBlob.insert(670);
		UnBlob.insert(671);
		UnBlob.insert(566);
		UnBlob.insert(572);
		UnBlob.insert(573);
		UnBlob.insert(672);
	}

	if (!command || (command && modifiedFiles.count("./Configs/UnGap.txt"))) {
		FILE *filetx = fopen("./Configs/UnGap.txt", "r");
		if (filetx != NULL)
		{
			UnGap.clear();
			char line[BUFSIZ];
			while (fgets(line, sizeof line, filetx) != NULL)
			{
				int CheckMobIndex = 0;
				if (sscanf(line, "(ungap (index %d))", &CheckMobIndex) == 1)
					UnGap.insert(CheckMobIndex);
			}
			fclose(filetx);
		}
	}

	if (!command || (command && modifiedFiles.count("./Configs/Emok.txt"))) {
		FILE *filetx = fopen("./Configs/Emok.txt", "r");
		if (filetx != NULL)
		{
			EmokCerts.clear();
			char line[BUFSIZ];
			while (fgets(line, sizeof line, filetx) != NULL)
			{
				int Index = 0, Time = 0, EXP = 0;
				if (sscanf(line, "(EmokCert (Index %d)(Time %d)(EXP %d))", &Index, &Time, &EXP) == 3) {
					EmokCertConf eCert = EmokCertConf();
					eCert.Time = Time;
					eCert.EXP = EXP;
					EmokCerts[Index] = eCert;
				}
			}
			fclose(filetx);
		}
	}

	if (!command || (command && modifiedFiles.count("./Configs/EXPMultiplier.txt"))) {
		FILE *falmulti = fopen("./Configs/EXPMultiplier.txt", "r");
		if (falmulti != NULL)
		{
			EXPMultipliers.clear();
			char line[BUFSIZ];
			while (fgets(line, sizeof line, falmulti) != NULL)
			{
				int mobIndex = 0, mMultiple = 0;
				if (sscanf(line, "(Multiplier (Index %d)(Multiply %d))", &mobIndex, &mMultiple) == 2){
					SMultiple Mmob = SMultiple();
					Mmob.Multiple = mMultiple;

					EXPMultipliers[mobIndex] = Mmob;
				}
			}
			fclose(falmulti);
		}
	}

	if (!command || (command && modifiedFiles.count("./Systems/SinEvent.txt"))) {
		FILE *filetx = fopen("./Systems/SinEvent.txt", "r");
		if (filetx != NULL)
		{
			SinSpawners.clear();
			char line[BUFSIZ];
			while (fgets(line, sizeof line, filetx) != NULL)
			{
				int index = 0, amount = 0, X = 0, Y = 0;
				if (sscanf(line, "(Spawn (Index %d)(Amount %d)(X %d)(Y %d))", &index, &amount, &X, &Y) == 4) {
					SinSpawner spawner = SinSpawner();
					spawner.Index = index;
					spawner.Amount = amount;
					spawner.X = X;
					spawner.Y = Y;
					SinSpawners.push_back(spawner);
				}
			}
			fclose(filetx);
		}
	}

	if (!command || (command && modifiedFiles.count("./Configs/Blacklist.txt"))) {
		FILE *filetx = fopen("./Configs/Blacklist.txt", "r");
		if (filetx != NULL)
		{
			SystemBlacklist.clear();
			char line[BUFSIZ];
			while (fgets(line, sizeof line, filetx) != NULL)
			{
				int Type, ID = 0;

				if (sscanf(line, "(Blacklist (Type %d)(ID %d))", &Type, &ID) == 2) {
					std::set<int> BL = SystemBlacklist.count(Type) ? SystemBlacklist.find(Type)->second : std::set<int>();
					BL.insert(ID);
					SystemBlacklist[Type] = BL;
				}
			}
			fclose(filetx);
		}
	}

	if (!command || (command && modifiedFiles.count("./Configs/StandardBreak.txt"))) {
		FILE *filetx = fopen("./Configs/StandardBreak.txt", "r");
		if (filetx != NULL)
		{
			UnBreak.clear();
			char line[BUFSIZ];
			while (fgets(line, sizeof line, filetx) != NULL)
			{
				int Index = 0;
				if (sscanf(line, "(unbreak (index %d))", &Index) == 1)
					UnBreak.insert(Index);
			}
			fclose(filetx);
		}
	}

	if (!command || (command && modifiedFiles.count("./Systems/Lawless.txt"))) {
		FILE *filetx = fopen("./Systems/Lawless.txt", "r");
		if (filetx != NULL)
		{
			LawlessEXP.clear();
			char line[BUFSIZ];
			while (fgets(line, sizeof line, filetx) != NULL)
			{
				int points = 0;
				if (sscanf(line, "(lawlessEXP (points %d))", &points) == 1)
					LawlessEXP.push_back(points);
			}
			fclose(filetx);
		}
		std::sort(LawlessEXP.begin(), LawlessEXP.end(), sortByKey);
	}
	if (!command || (command && modifiedFiles.count("./Configs/Certificates.txt"))) {
		FILE* filecert = fopen("./Configs/Certificates.txt", "r");
		if (filecert != NULL) {
			AreaCert.clear();
			char line[BUFSIZ];
			while (fgets(line, sizeof line, filecert) != NULL) {
				int itemIndex = 0, map = 0, time = 0, exp = 0, sbKey = 0, sbMsg = 0;
				if (sscanf(line, "(MapCert (Index %d)(Map %d)(Time %d)(Exp %d)(SBKey %d)(SBMsg %d))", &itemIndex, &map, &time, &exp, &sbKey, &sbMsg) == 6) {
					Certificates Cert = Certificates();
					Cert.itemIndex = itemIndex;
					Cert.Map = map;
					Cert.Time = time;
					Cert.Exp = exp;
					Cert.SBKey = sbKey;
					Cert.SBMsg = sbMsg;

					AreaCert[itemIndex] = Cert;
					AreaCertMap[map] = Cert;

				}
			}
			fclose(filecert);
		}
	}
	if (!command || (command && modifiedFiles.count("./Configs/ItemCombine.txt"))) {
		FILE *filetx = fopen("./Configs/ItemCombine.txt", "r");
		if (filetx != NULL)
		{
			Combinators.clear();
			char line[BUFSIZ];
			while (fgets(line, sizeof line, filetx) != NULL)
			{
				int QuestID = 0, Flag = 0, Index = 0, Bound = 0;
				if (sscanf(line, "(Combine (Quest %d %d)(Item %d)(Bound %d))", &QuestID, &Flag, &Index, &Bound) == 4) {
					Combinator cItem = Combinator();
					cItem.Index = Index;
					cItem.Bound = Bound;
					Combinators[((QuestID % 65536) * 1000) + Flag] = cItem;
				}
			}
			fclose(filetx);
		}
	}

	if (!command || (command && modifiedFiles.count("./Configs/SinDisable.txt"))) {
		FILE *fileyt = fopen("./Configs/SinDisable.txt", "r");
		if (fileyt != NULL)
		{
			char line[BUFSIZ];
			while (fgets(line, sizeof line, fileyt) != NULL)
			{
				int Map = 0;
				if (sscanf(line, "(DisableSin (Map %d))", &Map) == 1)
				{
					SinDisable.insert(Map);
				}
				int MapX = 0, MapY = 0;
				if (sscanf(line, "(DisableSin (File %d_%d))", &MapX, &MapY) == 2)
				{
					SinDisable.insert((MapX + 1000)*(MapY + 100));
				}
				
				if (sscanf(line, "(EnablePKDrop (File %d_%d))", &MapX, &MapY) == 2)
				{
					PKDropEnable.insert((MapX * 1000) + MapY);
				}
			}
			fclose(fileyt);
		}
	}

	if (!command || (command && modifiedFiles.count("./Configs/UgOg.txt"))) {
		FILE *filewytu = fopen("./Configs/UgOg.txt", "r");
		if (filewytu != NULL)
		{
			char line[BUFSIZ];
			while (fgets(line, sizeof line, filewytu) != NULL)
			{
				int MapX = 0, MapY = 0, MinZ = 0, MaxZ = 0;

				if (sscanf(line, "(ugog (map %d_%d)(minZ %d)(maxZ %d))", &MapX, &MapY, &MinZ, &MaxZ) == 4)
				{
					ugog[(MapX * 1000) + MapY].minZ = MinZ;
					ugog[(MapX * 1000) + MapY].maxZ = MaxZ;
				}
			}
			fclose(filewytu);
		}
	}
	if (!command || (command && modifiedFiles.count("./Configs/BuffItems.txt"))) {
		FILE *filewtu = fopen("./Configs/BuffItems.txt", "r");
		if (filewtu != NULL)
		{
			BuffedItems.clear();
			char line[BUFSIZ];
			while (fgets(line, sizeof line, filewtu) != NULL)
			{
				int Andex = 0, ABuff = 0, AEffect = 0, ATime = 0, SBKey = 0, SBName = 0;

				if (sscanf(line, "(buffitem (index %d)(buff %d)(effect %d)(time %d)(SBKey %d)(SBName %d))", &Andex, &ABuff, &AEffect, &ATime, &SBKey, &SBName) == 6)
				{
					Buffs buff = Buffs(ABuff, AEffect, ATime, SBKey, SBName);
					BuffedItems[Andex].BuffList.push_back(buff);
				}
			}
			fclose(filewtu);
		}
	}

	if (!command || (command && modifiedFiles.count("./Systems/Duel.txt"))) {
		FILE *filewta = fopen("./Systems/Duel.txt", "r");
		if (filewta != NULL)
		{
			DuelUnbuff.clear();
			char line[BUFSIZ];
			while (fgets(line, sizeof line, filewta) != NULL)
			{
				int buff = 0;

				if (sscanf(line, "(unbuff (index %d))", &buff) == 1)
					DuelUnbuff.push_back(buff);
			}
			fclose(filewta);
		}
	}

	if (!command || (command && modifiedFiles.count("./Systems/WorldCup.txt"))) {
		FILE *filewta = fopen("./Systems/WorldCup.txt", "r");
		if (filewta != NULL)
		{
			WCRewards.clear();
			char line[BUFSIZ];
			while (fgets(line, sizeof line, filewta) != NULL)
			{
				int round = 0, type = 0, index = 0, amount = 0;

				if (sscanf(line, "(reward (round %d)(type %d)(index %d)(amount %d))", &round, &type, &index, &amount) == 4)
				{
					WCReward t = WCReward();
					t.Index = index;
					t.Amount = amount;
					WCRewards[(round * 100) + type].RewardList.push_back(t);
				}
			}
			fclose(filewta);
		}
	}

	if (!command || (command && modifiedFiles.count("./Configs/Single.txt"))) {
		FILE *filewu = fopen("./Configs/Single.txt", "r");
		if (filewu != NULL)
		{
			char line[BUFSIZ];
			while (fgets(line, sizeof line, filewu) != NULL)
			{
				int Andex = 0, ARemove = 0, ALevel = 0, AGrade = 0, ABuff = 0;

				if (sscanf(line, "(single (index %d)(grade %d)(buff %d)(remove %d))", &Andex, &AGrade, &ABuff, &ARemove) == 4)
				{
					SingleBufferCheck[Andex].Index = Andex;
					SingleBufferCheck[Andex].Grade = AGrade;
					SingleBufferCheck[Andex].Delete = ARemove;
					SingleBufferCheck[Andex].Type = ABuff;
				}

			}
			fclose(filewu);
		}
	}

	if (!command || (command && modifiedFiles.count("./Configs/SoulPocket.txt"))) {
		FILE *filetwu = fopen("./Configs/SoulPocket.txt", "r");
		if (filetwu != NULL)
		{
			char line[BUFSIZ];
			while (fgets(line, sizeof line, filetwu) != NULL)
			{
				int Index = 0, Type = 0, Amount = 0, Refill = 0, Max = 0;

				if (sscanf(line, "(soulpocket (index %d)(type %d)(amount %d)(refill %d)(max %d))", &Index, &Type, &Amount, &Refill, &Max) == 5)
				{
					SoulPockets[(Index * 1000) + Type].Amount = Amount;
					SoulPockets[(Index * 1000) + Type].Refill = Refill;
					SoulPockets[(Index * 1000) + Type].Max = Max;
				}
				int EffectIndex = 0, Damage = 0;
				if (sscanf(line, "(soulEffect (index %d)(damage %d))", &EffectIndex, &Damage) == 2)
				{
					SoulPocketEffect[EffectIndex] = Damage;
				}
			}
			fclose(filetwu);
		}
	}

	if (!command || (command && modifiedFiles.count("./Configs/Mining.txt"))) {
		FILE *filetwu = fopen("./Configs/Mining.txt", "r");
		if (filetwu != NULL)
		{
			MiningItems.clear();
			char line[BUFSIZ];
			while (fgets(line, sizeof line, filetwu) != NULL)
			{
				int pickax = 0, chance = 0, items = 0;
				char indexes[BUFSIZ];
				char amounts[BUFSIZ];

				if (sscanf(line, "(mining (pickax %d)(chance %d)(items %d)(index %[0-9/,])(amount %[0-9/,]))", &pickax, &chance, &items, &indexes, &amounts) == 5)
				{
					std::vector<std::string> sItems = explode(",", std::string((const char*)indexes));
					std::vector<std::string> sAmounts = explode(",", std::string((const char*)amounts));

					MiningItem mItem = MiningItem();

					mItem.NumItems = items;
					for (int i = 0; i < sItems.size(); i++) {
						ItemStruct item = ItemStruct();
						item.Index = String2Int(sItems[i]);
						item.Amount = String2Int(sAmounts[i]);
						mItem.Items.push_back(item);
					}

					MiningItems[(pickax * 1000) + chance] = mItem;
				}
			}
			fclose(filetwu);
		}
	}

	if (!command || (command && modifiedFiles.count("./Configs/Polls.txt"))) {
		FILE *filetwa = fopen("./Configs/Polls.txt", "r");
		if (filetwa != NULL)
		{
			Polls.clear();
			PollTimer.clear();
			char line[BUFSIZ];
			while (fgets(line, sizeof line, filetwa) != NULL)
			{
				char question[BUFSIZ];

				for (int i = 0; i < strlen(line); i++) {
					if (line[i] == '-')
						line[i] = ';';
					if (line[i] == '_')
						line[i] = '^';
				}

				int Index = 0, FlagMin = 0, FlagMax = 0, HTML = 0;
				int StartDay = 0, StartMonth = 0, StartHour = 0, StartMinute = 0;
				int EndDay = 0, EndMonth = 0, EndHour = 0, EndMinute = 0;

				if (sscanf(line, "(poll (quest %d) (flags %d;%d) (question '%[a-z | A-Z | 0-9/<>|.,~*;`:!^+%&=?_-£#$\\€]') (answerHTML %d) (start %d;%d %d:%d) (end %d;%d %d:%d))", &Index, &FlagMin, &FlagMax, &question, &HTML, &StartDay, &StartMonth, &StartHour, &StartMinute, &EndDay, &EndMonth, &EndHour, &EndMinute) == 13)
				{
					for (int i = 0; i < strlen(question); i++) {
						if (question[i] == ';')
							question[i] = '-';
						if (question[i] == '^')
							question[i] = '_';
					}

					Poll poll = Poll();
					poll.Quest = Index;
					poll.FlagMin = FlagMin;
					poll.FlagMax = FlagMax;
					poll.Question = question;
					poll.HTML = HTML;
					poll.Start = (StartMonth * 1000000) + (StartDay * 10000) + (StartHour * 100) + StartMinute;
					poll.End = (EndMonth * 1000000) + (EndDay * 10000) + (EndHour * 100) + EndMinute;

					PollTimer[poll.Start] = poll;
					PollTimer[poll.End] = poll;
					Polls[Index] = poll;
				}
			}
			fclose(filetwa);
		}
	}

	if (!command || (command && modifiedFiles.count("./Configs/Tracker.txt"))) {
		FILE *filetwa = fopen("./Configs/Tracker.txt", "r");
		if (filetwa != NULL)
		{
			Tracker.clear();
			char line[BUFSIZ];
			while (fgets(line, sizeof line, filetwa) != NULL)
			{
				char type[BUFSIZ], argument[BUFSIZ], file[BUFSIZ];

				for (int i = 0; i < strlen(line); i++) {
					if (line[i] == '-')
						line[i] = '!';
					if (line[i] == '_')
						line[i] = '?';
				}

				if (sscanf(line, "(Tracker (Type '%[a-z | A-Z | 0-9/<>|.,~*;`:!^+%&=?_-£#$€]') (argument '%[a-z | A-Z | 0-9/<>|.,~*;`:!^+%&=?_-£#$€]') (file '%[a-z | A-Z | 0-9/<>|.,~*;`:!^+%&=?_-£#$€]'))", &type, &argument, &file) == 3)
				{
					for (int i = 0; i < strlen(argument); i++) {
						if (argument[i] == '!')
							argument[i] = '-';
						if (argument[i] == '?')
							argument[i] = '_';
					}

					Tracker[argument] = file;
				}
			}
			fclose(filetwa);
		}
	}

	if (!command || (command && modifiedFiles.count("./Configs/EventMaps.txt"))) {
		ifstream filenwu("./Configs/EventMaps.txt");
		if (filenwu.good())
		{
			EventMapsTimer.clear();
			EventMapsQuests.clear();
			string line;
			while (getline(filenwu, line))
			{
				int QuestID, PTSize = 0, Cooldown = 0, QuestFlag, Duration, MinLvl, MaxLvl, TX = 0, TY = 0, Lapse = 0;
				char Reward[BUFSIZ], mobs[BUFSIZ], amounts[BUFSIZ], day[BUFSIZ], name[BUFSIZ], X[BUFSIZ], Y[BUFSIZ], ReqItemx[BUFSIZ], ReqAmountx[BUFSIZ], ReqItemM[BUFSIZ], ReqAmountM[BUFSIZ];
				int hour = 0, minute = 0, second = 0, hourr = 0, minuter = 0, secondr = 0;
				int item2 = 0, item2am = 0;

				if (sscanf(line.c_str(), "(EventMap (Name '%[a-z | A-Z | 0-9/<>|.,~*;`:!^+%&=?_-£#$€]') (Quest %d %d) (ReqItem %[0-9\\,-]) (ReqAmount %[0-9\\,-]) (Level %d-%d) (Teleport %d %d) (Mobs %[0-9\\,-]) (Amount %[0-9\\,-]) (SpawnX %[0-9\\,-]) (SpawnY %[0-9\\,-]) (Day '%[a-z | A-Z | 0-9/<>|.,~*;`:!^+%&=?_-£#$€]') (Time '%d:%d:%d') (RegistrationTime '%d:%d:%d') (Duration %d) (Lapse %d) (Reward %[0-9\\,-]))", &name, &QuestID, &QuestFlag, &ReqItemx, &ReqAmountx, &MinLvl, &MaxLvl, &TX, &TY, &mobs, &amounts, &X, &Y, &day, &hour, &minute, &second, &hourr, &minuter, &secondr, &Duration, &Lapse, &Reward) == 23)
				{
					std::string sBIndexs = std::string((const char*)mobs);
					std::string sBAmounts = std::string((const char*)amounts);
					std::string sRewards = std::string((const char*)Reward);
					std::string Xs = std::string((const char*)X);
					std::string Ys = std::string((const char*)Y);
					std::string itemIndexes = std::string((const char*)ReqItemx);
					std::string itemAmounts = std::string((const char*)ReqAmountx);

					std::vector<std::string> Rewards_ = explode(",", sRewards);
					std::vector<std::string> Monsters_ = explode(",", sBIndexs);
					std::vector<std::string> Amounts_ = explode(",", sBAmounts);
					std::vector<std::string> X_ = explode(",", Xs);
					std::vector<std::string> Y_ = explode(",", Ys);

					if (Monsters_.size() == Amounts_.size() && X_.size() == Y_.size()) {
						std::string realDay(day);
						int day = EventConfig(realDay);

						int index = IntTime(day, hour, minute, second);

						int startindex = IntTime(day, hourr, minuter, secondr);

						EventMapsTimer[index] = "EventMap{" + Int2String((QuestID * 1000) + QuestFlag) + "}";
						EventMapsTimer[startindex] = "EventRegisterMap{" + Int2String((QuestID * 1000) + QuestFlag) + "}";

						eventMap mapEvent = eventMap();
						for (int i = 0; i < X_.size(); i++) {
							std::vector<std::string> XPR = explode("-", X_[i]);
							std::vector<std::string> YPR = explode("-", Y_[i]);
							for (int j = 0; j < XPR.size(); j++) {
								int MapXY = ((String2Int(XPR[j]) >> 13) * 1000) + (String2Int(YPR[j]) >> 13);
								mapEvent.Maps.insert(MapXY);
								EventMaps.insert(MapXY);
							}
							mapEvent.Maps.insert(((TX >> 13) * 1000) + (TY >> 13));
							EventMaps.insert(((TX >> 13) * 1000) + (TY >> 13));
						}

						mapEvent.Type = 0;
						mapEvent.Cooldown = 0;
						mapEvent.PTSize = 0;
						mapEvent.Lapse = Lapse;
						mapEvent.Duration = Duration;
						mapEvent.Name = name;
						mapEvent.monsters = Monsters_;
						mapEvent.amounts = Amounts_;
						mapEvent.X = X_;
						mapEvent.Y = Y_;
						mapEvent.TX = TX;
						mapEvent.TY = TY;
						mapEvent.LvlMin = MinLvl;
						mapEvent.LvlMax = MaxLvl;
						mapEvent.Reward = Rewards_;
						mapEvent.ReqItemx = explode(",", itemIndexes);
						mapEvent.ReqAmountx = explode(",", itemAmounts);
						mapEvent.Quest = (QuestID * 1000) + QuestFlag;
						EventMapsQuests[(QuestID * 1000) + QuestFlag] =  mapEvent;
					}
				}
				else
					if (sscanf(line.c_str(), "(InstanceDungeon (Name '%[a-z | A-Z | 0-9/<>|.,~*;`:!^+%&=?_-£#$€]') (PartySize %d) (Quest %d %d) (LeaderReqItem %[0-9\\,-]) (LeaderReqAmount %[0-9\\,-]) (MemberReqItem %[0-9\\,-]) (MemberReqAmount %[0-9\\,-]) (Level %d-%d) (Teleport %d %d) (Mobs %[0-9\\,-]) (Amount %[0-9\\,-]) (SpawnX %[0-9\\,-]) (SpawnY %[0-9\\,-]) (Duration %d) (Lapse %d) (Cooldown %d) (Reward %[0-9\\,-]))", &name, &PTSize, &QuestID, &QuestFlag, &ReqItemx, &ReqAmountx, &ReqItemM, &ReqAmountM, &MinLvl, &MaxLvl, &TX, &TY, &mobs, &amounts, &X, &Y, &Duration, &Lapse, &Cooldown, &Reward) == 20)
					{
						std::string sBIndexs = std::string((const char*)mobs);
						std::string sBAmounts = std::string((const char*)amounts);
						std::string sRewards = std::string((const char*)Reward);
						std::string Xs = std::string((const char*)X);
						std::string Ys = std::string((const char*)Y);
						std::string itemIndexes = std::string((const char*)ReqItemx);
						std::string itemAmounts = std::string((const char*)ReqAmountx);
						std::string MitemIndexes = std::string((const char*)ReqItemM);
						std::string MitemAmounts = std::string((const char*)ReqAmountM);

						std::vector<std::string> Rewards_ = explode(",", sRewards);
						std::vector<std::string> Monsters_ = explode(",", sBIndexs);
						std::vector<std::string> Amounts_ = explode(",", sBAmounts);
						std::vector<std::string> X_ = explode(",", Xs);
						std::vector<std::string> Y_ = explode(",", Ys);


						if (Monsters_.size() == Amounts_.size() && X_.size() == Y_.size()) {

							eventMap mapEvent = eventMap();
							for (int i = 0; i < X_.size(); i++) {
								std::vector<std::string> XPR = explode("-", X_[i]);
								std::vector<std::string> YPR = explode("-", Y_[i]);
								for (int j = 0; j < XPR.size(); j++) {
									int MapXY = ((String2Int(XPR[j]) >> 13) * 1000) + (String2Int(YPR[j]) >> 13);
									mapEvent.Maps.insert(MapXY);
									EventMaps.insert(MapXY);
								}
								mapEvent.Maps.insert(((TX >> 13) * 1000) + (TY >> 13));
								EventMaps.insert(((TX >> 13) * 1000) + (TY >> 13));
							}

							mapEvent.Type = 1;
							mapEvent.Cooldown = Cooldown;
							mapEvent.PTSize = PTSize;
							mapEvent.Lapse = Lapse;
							mapEvent.Duration = Duration;
							mapEvent.Name = name;
							mapEvent.monsters = Monsters_;
							mapEvent.amounts = Amounts_;
							mapEvent.X = X_;
							mapEvent.Y = Y_;
							mapEvent.TX = TX;
							mapEvent.TY = TY;
							mapEvent.LvlMin = MinLvl;
							mapEvent.LvlMax = MaxLvl;
							mapEvent.Reward = Rewards_;
							mapEvent.ReqItemx = explode(",", itemIndexes);
							mapEvent.ReqAmountx = explode(",", itemAmounts);
							mapEvent.ReqItemM = explode(",", MitemIndexes);
							mapEvent.ReqAmountM = explode(",", MitemAmounts);
							mapEvent.Quest = (QuestID * 1000) + QuestFlag;
							EventMapsQuests[(QuestID * 1000) + QuestFlag] = mapEvent;
						}
					}
			}
			filenwu.close();
		}
	}

	if (!command || (command && modifiedFiles.count("./Configs/SummonQuest.txt"))) {
		FILE *filenwu = fopen("./Configs/SummonQuest.txt", "r");
		if (filenwu != NULL)
		{
			char line[BUFSIZ];
			while (fgets(line, sizeof line, filenwu) != NULL)
			{
				int QIndex = 0, QFlag = 0, RQuest = 0, RFlag = 0, ItemIndex = 0, ItemAmount = 0, MIndex = 0, MAmount = 0, X = 0, Y = 0, Map = 0, Check = 0, Limit = 0;
				char notice[BUFSIZ];

				if (sscanf(line, "(SummonQuest (Quest %d %d) (ReplyQuest %d %d) (Item_Index %d) (Item_Amount %d) (Monster_Index %d) (Monster_Amount %d) (Coordinates %d-%d-%d) (Notice '%[a-z | A-Z | 0-9/<>|.,~*;`:!^+%&=?_-£#$€]') (Check %d) (DailyLimit %d))", &QIndex, &QFlag, &RQuest, &RFlag, &ItemIndex, &ItemAmount, &MIndex, &MAmount, &Map, &X, &Y, &notice, &Check, &Limit) == 14)
				{
					MSummonConfig msConfig = MSummonConfig();
					msConfig.Type = 0;
					msConfig.ItemIndex = ItemIndex;
					msConfig.ItemAmount = ItemAmount;
					msConfig.Check = Check;
					msConfig.Map = Map;
					msConfig.X = X;
					msConfig.Y = Y;
					msConfig.notice = notice;
					msConfig.MonsterIndex = MIndex;
					msConfig.MonsterAmount = MAmount;
					msConfig.Limit = Limit;
					msConfig.QIndex = ((QIndex % 65536) * 1000) + QFlag;
					MQuest.insert(MIndex);
					SummonQuest[((QIndex % 65536) * 1000) + QFlag] = msConfig;
					SummonQuest[((RQuest % 65536) * 1000) + RFlag] = msConfig;
					SummonQuest[((RQuest % 65536) * 1000) + RFlag].Type = 1;

					if (!SummonedQuest.count((QIndex * 1000) + QFlag)) {
						MSummonedConfig mConfig = MSummonedConfig();
						mConfig.CurAmount = 0;
						mConfig.Limit = 0;
						mConfig.Spawned = 0;
						SummonedQuest.replaceInsert(((QIndex % 65536) * 1000) + QFlag, mConfig);
					}
				}

			}
			fclose(filenwu);
		}
	}

	if (!command || (command && modifiedFiles.count("./Configs/CustomNotices.txt"))) {
		FILE *filetwsu = fopen("./Configs/CustomNotices.txt", "r");
		if (filetwsu != NULL)
		{
			RGBAutoNotice.clear();
			CustomNotices.clear();
			CustomShouts.clear();

			char line[BUFSIZ];
			while (fgets(line, sizeof line, filetwsu) != NULL)
			{
				int R = 0, G = 0, B = 0, ShoutsIndex = 0, Removal = 0;
				char cmd[BUFSIZ];
				int ShoutIndex = 0;

				if (sscanf(line, "(CustomNotice (command '%[a-z | A-Z | 0-9/<>|.,~*;`:!^+%&=?_-£#$€]') (RGB %d %d %d))", &cmd, &R, &G, &B) == 4)
					CustomNotices[cmd] = RGB(R, G, B);

				if (sscanf(line, "(CustomShouts (command '%[a-z | A-Z | 0-9/<>|.,~*;`:!^+%&=?_-£#$€]') (RGB %d %d %d) (ItemIndex %d) (Remove %d))", &cmd, &R, &G, &B, &ShoutsIndex, &Removal) == 6) {
					CustomShouts[cmd] = ShoutData(RGB(R, G, B), ShoutsIndex, Removal);
				}


				int Ra = 0, Ga = 0, Ba = 0;
				char day[BUFSIZ], time[BUFSIZ], notice[BUFSIZ];
				if (sscanf(line, "(rgbnotice (day '%[a-z | A-Z | 0-9/<>|.,~*;`:!^+%&=?_-£#$€]')(time '%[a-z | A-Z | 0-9/<>|.,~*;`:!^+%&=?_-£#$€]')(msg '%[a-z | A-Z | 0-9/<>|.,~*;`:!^+%&=?_-£#$€]')(RGB %d %d %d))", &day, &time, &notice, &Ra, &Ga, &Ba) == 6)
				{
					RGBNotice noticeRGB = RGBNotice();
					noticeRGB.day = day;
					noticeRGB.msg = notice;
					noticeRGB.Color = RGB(Ra, Ga, Ba);
					std::vector<RGBNotice> curNotices = RGBAutoNotice.count(time) ? RGBAutoNotice.find(time)->second : std::vector<RGBNotice>();
					curNotices.push_back(noticeRGB);
					RGBAutoNotice[time] = curNotices;
				}
			}
			fclose(filetwsu);
		}
	}

	if (!command || (command && modifiedFiles.count("./Configs/Hogwarts.txt"))) {
		FILE *filehogw = fopen("./Configs/Hogwarts.txt", "r");
		if (filehogw != NULL)
		{
			RGBAutoNotice.clear();

			char line[BUFSIZ];
			while (fgets(line, sizeof line, filehogw) != NULL)
			{
				int R = 0, G = 0, B = 0, ShoutsIndex = 0, Removal = 0;
				char cmd[BUFSIZ];
				int HouseIndex = 0;

				if (sscanf(line, "(HouseCmd (command '%[a-z | A-Z | 0-9/<>|.,~*;`:!^+%&=?_-£#$€]') (RGB %d %d %d) (House %d) (Remove %d))", &cmd, &R, &G, &B, &HouseIndex, &Removal) == 6) {
					CustomHouse[cmd] = ShoutData(RGB(R, G, B), HouseIndex, Removal);
				}

			}
			fclose(filehogw);
		}
	}

	if (!command || (command && modifiedFiles.count("./Configs/Restriction.txt"))) {
		ifstream fRestrictions("./Configs/Restriction.txt");
		if (fRestrictions.good()) {
			string line;
			Restrictions.clear();
			while (getline(fRestrictions, line))
			{
				int PID = 0;
				char cmds[1024];

				int Trade = 0, Shop = 0, Storage = 0, Mail = 0, Party = 0, Duel = 0, Attack = 0, Drop = 0, Skill = 0, Pick = 0;
				char hwids[1024];

				if (sscanf(line.c_str(), "(AdminHWID (PID %d) (HWID '%[a-z0-9-]+'))", &PID, hwids) == 2)
					HWIDRestrictions[PID].HWIDs = hwids;

				if (sscanf(line.c_str(), "(DisableCommand (PID %d) (Commands '%[a-z | A-Z | 0-9/<>|.,~*;`:!^+%&=?_-£#$€]'))", &PID, &cmds) == 2)
					Restrictions[PID].Commands = cmds;

				if (sscanf(line.c_str(), "(DisableSystems (PID %d) (Trade %d) (Shop %d) (Storage %d) (Mail %d) (Party %d) (Duel %d) (Attack %d) (Skill %d) (Drop %d) (Pick %d))", &PID, &Trade, &Shop, &Storage, &Mail, &Party, &Duel, &Attack, &Skill, &Drop, &Pick) == 11) {
					Restrictions[PID].Trade = Trade;
					Restrictions[PID].Shop = Shop;
					Restrictions[PID].Storage = Storage;
					Restrictions[PID].Mail = Mail;
					Restrictions[PID].Party = Party;
					Restrictions[PID].Duel = Duel;
					Restrictions[PID].Attack = Attack;
					Restrictions[PID].Drop = Drop;
					Restrictions[PID].Skill = Skill;
					Restrictions[PID].Pick = Pick;
				}
			}
			fRestrictions.close();
		}
	}

	if (!command || (command && modifiedFiles.count("./Configs/AFKCheck.txt"))) {
		FILE *filewwu = fopen("./Configs/AFKCheck.txt", "r");
		if (filewwu != NULL)
		{
			AFKMap.clear();
			char line[BUFSIZ];
			while (fgets(line, sizeof line, filewwu) != NULL)
			{
				int RectX1 = 0, RectX2 = 0, RectY1 = 0, RectY2 = 0, seconds = 0;
				if (sscanf(line, "(AFKCheck (Rect %d %d %d %d)(Time %d))", &RectX1, &RectY1, &RectX2, &RectY2, &seconds) == 5)
				{
					RECT rect = RECT();
					rect.left = min(RectX1, RectX2);
					rect.right = max(RectX1, RectX2);
					rect.top = min(RectY1, RectY2);
					rect.bottom = max(RectY1, RectY2);

					AFKCheck check = AFKCheck();
					check.rectangle = rect;
					check.seconds = seconds;
					int Map1 = ((RectX1 / 256) * 1000) + (RectY1 / 256);
					int Map2 = ((RectX2 / 256) * 1000) + (RectY2 / 256);
					AFKMap[Map1].push_back(check);
					
					if (Map1 != Map2)
						AFKMap[Map2].push_back(check);
				}

				int MapX = 0, MapY = 0;
				if (sscanf(line, "(macroCheck (file %d_%d))", &MapX, &MapY) == 2)
					Macro.insert((MapX + 1000)*(MapY + 100));

			}
			fclose(filewwu);
		}
	}

	if (!command || (command && modifiedFiles.count("./Configs/Buff.txt"))) {
		FILE *fileq = fopen("./Configs/Buff.txt", "r");
		if (fileq != NULL)
		{
			BufferCheck.clear();

			char line[BUFSIZ];
			while (fgets(line, sizeof line, fileq) != NULL)
			{
				int Index = 0, IRemove = 0, ILevel = 0, IGrade = 0, Quest = 0, QGrade = 0, QRemove = 0, QLimit = 0;
				int Speed = 0, SpeedQ = 0, cd = 0;
				if (sscanf(line, "(buff (index %d)(grade %d)(remove %d)(level %d)(cd %d))", &Index, &IGrade, &IRemove, &ILevel, &cd) >= 4)
				{
					BufferCheck[Index].Index = Index;
					BufferCheck[Index].Speed = 60;
					BufferCheck[Index].Grade = IGrade;
					BufferCheck[Index].Delete = IRemove;
					BufferCheck[Index].Limit = ILevel;
					BufferCheck[Index].cd = cd;

				}
				else if (sscanf(line, "(buff (index %d)(grade %d)(speed %d)(remove %d)(level %d)(cd %d))", &Index, &IGrade, &Speed, &IRemove, &ILevel, &cd) >= 5)
				{
					BufferCheck[Index].Index = Index;
					BufferCheck[Index].Speed = Speed;
					BufferCheck[Index].Grade = IGrade;
					BufferCheck[Index].Delete = IRemove;
					BufferCheck[Index].Limit = ILevel;
					BufferCheck[Index].cd = cd;

				}

				if (sscanf(line, "(buff (quest %d)(grade %d)(remove %d)(level %d)(cd %d))", &Quest, &QGrade, &QRemove, &QLimit, &cd) >= 4)
				{
					BufferCheck[Quest % 65536].Index = Quest;
					BufferCheck[Quest % 65536].Speed = 45;
					BufferCheck[Quest % 65536].Grade = QGrade;
					BufferCheck[Quest % 65536].Delete = QRemove;
					BufferCheck[Quest % 65536].Limit = QLimit;
					BufferCheck[Quest % 65536].cd = cd;

				}
				else if (sscanf(line, "(buff (quest %d)(grade %d)(speed %d)(remove %d)(level %d)(cd %d))", &Quest, &QGrade, &SpeedQ, &QRemove, &QLimit, &cd) >= 5)
				{
					BufferCheck[Quest % 65536].Index = Quest;
					BufferCheck[Quest % 65536].Speed = SpeedQ;
					BufferCheck[Quest % 65536].Grade = QGrade;
					BufferCheck[Quest % 65536].Delete = QRemove;
					BufferCheck[Quest % 65536].Limit = QLimit;
					BufferCheck[Quest % 65536].cd = cd;

				}
			}
			fclose(fileq);
		}
	}

	if (!command || (command && modifiedFiles.count("./Configs/Store.txt"))) {
		ifstream fStore("./Configs/Store.txt");
		if (fStore.good()) {
			string line;
			StoreItems.clear();
			while (getline(fStore, line))
			{
				if (!line.empty() && line.at(0) != ';') {
					stringstream str_strm;
					str_strm << line;
					string temp_str;
					int temp_int;
					int Key = 0;
					while (!str_strm.eof()) {
						str_strm >> temp_str;
						if (stringstream(temp_str) >> temp_int) {
							if (!Key)
								Key = temp_int;
							else
								StoreItems[Key].insert(temp_int);
						}
						temp_str = "";
					}
				}
			}
			fStore.close();
		}
	}

	if (!command || (command && modifiedFiles.count("./Configs/Filter.txt"))) {
		FILE *fileaym = fopen("./Configs/Filter.txt", "r");
		if (fileaym != NULL)
		{
			char line[BUFSIZ];
			while (fgets(line, sizeof line, fileaym) != NULL)
			{
				char msg[BUFSIZ];
				if (sscanf(line, "(text '%[a-z | A-Z | 0-9/<>|.,~*;`:!^+%&=?_-£#$€]')", &msg) == 1)
				{
					std::string MsgFilter = msg;
					std::transform(MsgFilter.begin(), MsgFilter.end(), MsgFilter.begin(), ::tolower);
					Filter.insert(MsgFilter);
				}
			}
			fclose(fileaym);
		}
	}

	if (!command || (command && modifiedFiles.count("./Configs/SkillBook.txt"))) {
		FILE *filey = fopen("./Configs/SkillBook.txt", "r");
		if (filey != NULL)
		{
			char line[BUFSIZ];
			while (fgets(line, sizeof line, filey) != NULL)
			{
				int Class = 0, Index = 0, SkillID = 0, UpgradeAmount = 0, MaxGrade = 0, downgradeAmount = 0, rewardPoints = 0;
				if (sscanf(line, "(skillbook (class %d)(index %d)(action %d)(upgradeamount %d)(maxgrade %d))", &Class, &Index, &SkillID, &UpgradeAmount, &MaxGrade) == 5)
				{
					SkillBook[Index].Class = Class;
					SkillBook[Index].Action = SkillID;
					SkillBook[Index].UpgradeAmount = UpgradeAmount;
					SkillBook[Index].UpgradeMax = MaxGrade;
				}
				if (sscanf(line, "(downgrade (class %d)(index %d)(action %d)(downgradeamount %d)(rewardPoint %d))", &Class, &Index, &SkillID, &downgradeAmount, &rewardPoints) == 5)
				{
					SkillDowngrade[Index].Class = Class;
					SkillDowngrade[Index].Action = SkillID;
					SkillDowngrade[Index].DowngradeAmount = downgradeAmount;
					SkillDowngrade[Index].RewardPoints = rewardPoints;
				}
			}
			fclose(filey);
		}
	}

	if (!command || (command && modifiedFiles.count("./Configs/Cooldown.txt"))) {
		FILE *filez = fopen("./Configs/Cooldown.txt", "r");
		if (filez != NULL)
		{
			char line[BUFSIZ];
			while (fgets(line, sizeof line, filez) != NULL)
			{
				int GetClass = 0, GetSkillID = 0, GetDelay = 0, GetCooldown = 0, GetSkillIDx = 0, GetDelayx = 0, GetCooldownx = 0;
				double Spam = 0;

				if (sscanf(line, "(skillSpam (delay %lf))", &Spam) == 1)
					DelaySpam = Spam;

				if (sscanf(line, "(eggskill (action %d)(delay %d)(cooldown %d))", &GetSkillIDx, &GetDelayx, &GetCooldownx) == 3)
				{
					CheckEggCooldownConfig[GetSkillIDx].EggCooldownConfig = GetCooldownx;
					CheckEggCooldownConfig[GetSkillIDx].EggDelayConfig = GetDelayx;
				}

				if (sscanf(line, "(skill (class %d)(action %d)(delay %d)(cooldown %d))", &GetClass, &GetSkillID, &GetDelay, &GetCooldown) == 4)
				{
					CheckCooldownConfig[GetSkillID + (GetClass * 100)].CooldownConfig = GetCooldown;
					CheckCooldownConfig[GetSkillID + (GetClass * 100)].DelayConfig = GetDelay;
				}
			}
			fclose(filez);
		}
	}

	if (!command || (command && modifiedFiles.count("./Configs/PvPSkillDamage.txt"))) {
		FILE *filegw = fopen("./Configs/PvPSkillDamage.txt", "r");
		if (filegw != NULL)
		{
			char line[BUFSIZ];
			while (fgets(line, sizeof line, filegw) != NULL)
			{
				int Class = 0, SkillID = 0, Rate = 0, Target = 0;
				if (sscanf(line, "(pvpdamage (class %d)(targetclass %d)(action %d)(rate %d))", &Class, &Target, &SkillID, &Rate) == 4)
				{
					SkillsPVP.insert((Class * 100) + SkillID);
					PVPConfigCalculations[(Class * 1000) + SkillID + (Target * 100)].Class = Target;
					PVPConfigCalculations[(Class * 1000) + SkillID + (Target * 100)].Rate = Rate;
				}
			}
			fclose(filegw);
		}
	}

	if (!command || (command && modifiedFiles.count("./Configs/Battlepass.txt"))) {
		FILE *Battlepass = fopen("./Configs/Battlepass.txt", "r");
		if (Battlepass != NULL)
		{
			char line[BUFSIZ];
			while (fgets(line, sizeof line, Battlepass) != NULL)
			{
				int Class = 0, Level = 0, Prefix = 0, ID = 0; char rewardnotice[BUFSIZ];
				char indexes[BUFSIZ], amounts[BUFSIZ];


				if (sscanf(line, "(normal (ID %d)(level %d)(class %d)(indexes %[0-9/,])(amounts %[0-9/,])(prefix %d)(msg '%[a-z | A-Z | 0-9/<>|.,~*;`:!^+%&=?_-£#$€]'))", &ID, &Level, &Class, &indexes, &amounts, &Prefix, &rewardnotice) == 7)
				{
					ConfigLevelReward battleReward = ConfigLevelReward();

					std::string bpIndexes = std::string((const char*)indexes);
					std::string bpAmounts = std::string((const char*)amounts);

					battleReward.Class = Class;
					battleReward.Indexes = explode(",", bpIndexes);
					battleReward.Prefix = Prefix;
					battleReward.Amounts = explode(",", bpAmounts);
					battleReward.Msg = rewardnotice;
					battleReward.ID = ID;

					if (battleReward.Indexes.size() == battleReward.Amounts.size())
						BattlepassReward[Level].push_back(battleReward);

				}

				if (sscanf(line, "(premium (ID %d)(level %d)(class %d)(indexes %[0-9/,])(amounts %[0-9/,])(prefix %d)(msg '%[a-z | A-Z | 0-9/<>|.,~*;`:!^+%&=?_-£#$€]'))", &ID, &Level, &Class, &indexes, &amounts, &Prefix, &rewardnotice) == 7)
				{
					ConfigLevelReward premiumReward = ConfigLevelReward();

					std::string bpPIndexes = std::string((const char*)indexes);
					std::string bpPAmounts = std::string((const char*)amounts);

					premiumReward.Class = Class;
					premiumReward.Indexes = explode(",", bpPIndexes);
					premiumReward.Prefix = Prefix;
					premiumReward.Amounts = explode(",", bpPAmounts);
					premiumReward.Msg = rewardnotice;
					premiumReward.ID = ID;

					if (premiumReward.Indexes.size() == premiumReward.Amounts.size())
						PremiumPass[Level].push_back(premiumReward);
				}
			}
			fclose(Battlepass);
		}
	}

	if (!command || (command && modifiedFiles.count("./Configs/PacketBlock.txt"))) {
		FILE *filjw = fopen("./Configs/PacketBlock.txt", "r");
		if (filjw != NULL)
		{
			PacketSpam.clear();
			PacketBlock.clear();
			PacketSpamConf.clear();
			char line[BUFSIZ];
			while (fgets(line, sizeof line, filjw) != NULL)
			{
				int SpamPacket = 0, SpamTime;
				if (sscanf(line, "(PacketSpam (type %d)(cooldown %d))", &SpamPacket, &SpamTime) == 2)
					PacketSpamConf[SpamPacket] = SpamTime;
				else {
					int Packet = 0;
					if (sscanf(line, "(PacketBlock (type %d))", &Packet) == 1)
						PacketBlock.insert(Packet);
				}
			}
			fclose(filjw);
		}
	}

	if (!command || (command && modifiedFiles.count("./Configs/SkillDisable.txt"))) {
		FILE *filqew = fopen("./Configs/SkillDisable.txt", "r");
		if (filqew != NULL)
		{
			char line[BUFSIZ];
			while (fgets(line, sizeof line, filqew) != NULL)
			{
				int Class = 0, SkillID = 0, Map = 0;
				if (sscanf(line, "(DisableSkill (class %d)(action %d)(map %d))", &Class, &SkillID, &Map) == 3)
					DisableSkill[(Class * 1000) + SkillID].insert(Map);
				
				int Skill = 0, MapX = 0, MapY = 0, ClassID = 0;
				if (sscanf(line, "(DisableSkill (class %d)(action %d)(File %d_%d))", &ClassID, &Skill, &MapX, &MapY) == 4)
					DisableSkillFile[(ClassID * 1000) + Skill].insert((MapX * 1000) + MapY);
								
				int SkillR = 0, ClassIDR = 0;
				if (sscanf(line, "(DisableBattleRideSkill (class %d)(action %d))", &ClassIDR, &SkillR) == 2)
				{
					RidingDisableSkill.insert((ClassIDR * 1000) + SkillR);
				}
			}
			fclose(filqew);
		}
	}

	if (!command || (command && modifiedFiles.count("./Configs/Auto.txt"))) {
		FILE *fileym = fopen("./Configs/Auto.txt", "r");
		if (fileym != NULL)
		{
			AutoNotices.clear();
			int l = 0;
			char line[BUFSIZ];
			while (fgets(line, sizeof line, fileym) != NULL)
			{
				int minutes, r, g, b;
				char msg[BUFSIZ];
				if (sscanf(line, "(AutoNotice (minutes %d)(msg '%[a-z | A-Z | 0-9/<>|.,~*;`:!^+%&=?_-£#$€]')(RGB %d %d %d))", &minutes, &msg, &r, &g, &b) == 5)
				{

					AutoNotices[l].minutes = minutes;
					AutoNotices[l].msg = msg;
					AutoNotices[l].color = RGB(r, g, b);


					l++;

				}

			}
			fclose(fileym);
		}
	}

	if (!command || (command && modifiedFiles.count("./Configs/QuestsNotice.txt"))){
		FILE *filemQON = fopen("./Configs/QuestsNotice.txt", "r");
		if (filemQON != NULL)
		{
			QuestsNotice.clear();

			char line[BUFSIZ];
			while (fgets(line, sizeof line, filemQON) != NULL)
			{
				int qIndex = 0, qItem = 0, qAmount = 0, qFlag = 0;
				int clearQ = 0;
				char qNotice[BUFSIZ];
				if (sscanf(line, "(QuestNotice (QuestIndex %d %d)(QuestNotice '%[a-z | A-Z | 0-9/<>|.,~*;`:!^+%&=?_-£#$€]')(QuestItem %d)(QuestAmount %d))", &qIndex, &qFlag, &qNotice, &qItem, &qAmount) == 5)
				{
					QuestsNotice[qIndex].QuestIndex = qIndex;
					QuestsNotice[qIndex].Notice = qNotice;
					QuestsNotice[qIndex].qFlag = qFlag;
					QuestsNotice[qIndex].QuestItem = qItem;
					QuestsNotice[qIndex].qAmount = qAmount;

				}
				else if (sscanf(line, "(QuestNotice (QuestIndex %d %d)(QuestNotice '%[a-z | A-Z | 0-9/<>|.,~*;`:!^+%&=?_-£#$€]')(ClearedQuest %d))", &qIndex, &qFlag, &qNotice, &clearQ) == 4)
				{
					cQuestsNotice[qIndex].QuestIndex = qIndex;
					cQuestsNotice[qIndex].Notice = qNotice;
					cQuestsNotice[qIndex].clearQ = clearQ;
					cQuestsNotice[qIndex].qFlag = qFlag;

				}

			}
			fclose(filemQON);
		}
	}

	if (!command || (command && modifiedFiles.count("./Configs/MonsterBuffs.txt"))) {
		FILE *filemobuf = fopen("./Configs/MonsterBuffs.txt", "r");
		if (filemobuf != NULL)
		{
			MonstersBuff.clear();
			RMonstersBuff.clear();

			char line[BUFSIZ];
			while (fgets(line, sizeof line, filemobuf) != NULL)
			{
				int monsterindex, buff, grade;
				if (sscanf(line, "(MonsterBuff (MobIndex %d)(BuffID %d)(Grade %d))", &monsterindex, &buff, &grade) == 3)
				{
					MonstersBuff[monsterindex].mobindex = monsterindex;
					MonstersBuff[monsterindex].buffid = buff;
					MonstersBuff[monsterindex].buffgrade = grade;

				}
				else if (sscanf(line, "(RandomBuff (MobIndex %d)(Grade %d))", &monsterindex, &grade) == 2)
				{
					RMonstersBuff[monsterindex].mobindex = monsterindex;
					RMonstersBuff[monsterindex].buffid = 0;
					RMonstersBuff[monsterindex].buffgrade = grade;

				}

			}
			fclose(filemobuf);
		}
	}

	if (!command || (command && modifiedFiles.count("./Configs/MonstersRewards.txt"))) {
		FILE *filemorewa = fopen("./Configs/MonstersRewards.txt", "r");
		if (filemorewa != NULL)
		{
			MonstersItem.clear();
			MonstersRewards.clear();

			char line[BUFSIZ];
			while (fgets(line, sizeof line, filemorewa) != NULL)
			{
				int monsterindex = 0, reward = 0, randomitem = 0, randomchance = 0, itemamount = 0, playerchance = 0, Range = 0;
				int chance = 0;
				bool found = false;

				if (sscanf(line, "(MonsterReward (Index %d)(RewardID %d)(RandomItemIndex %d)(Amount %d)(ItemChance %d)(PlayerChance %d)(Range %d))", &monsterindex, &reward, &randomitem, &itemamount, &randomchance, &playerchance, &Range) == 7)
				{
					for (int i = 0; i < MonstersItem.size(); i++) {
						ChanceItem f = MonstersItem[i];
						if (f.Index == randomitem && f.Amount == itemamount && f.Chance == randomchance)
							found = true;
					}
					if (found)
						continue;

					ChanceItem mobsitems = ChanceItem();
					mobsitems.Index = randomitem;
					mobsitems.Amount = itemamount;
					mobsitems.Chance = randomchance;
					MonstersItem.push_back(mobsitems);
					
					CMonstersRewards MobReward = CMonstersRewards();
					MobReward.mobindex = monsterindex;
					MobReward.rewardid = reward;
					MobReward.randomindex = randomitem;
					MobReward.itemamount = itemamount;
					MobReward.pickchance = playerchance;
					MobReward.Range = Range;
					MonstersRewards[monsterindex] = MobReward;

				}

			}
			std::sort(MonstersItem.begin(), MonstersItem.end(), sortByChance);
			fclose(filemorewa);
		}
	}
	if (!command || (command && modifiedFiles.count("./Configs/Area.txt"))) {
		FILE *filekd = fopen("./Configs/Area.txt", "r");
		if (filekd != NULL)
		{
			RectArea.clear();
			char line[BUFSIZ];
			while (fgets(line, sizeof line, filekd) != NULL)
			{
				int RectX1 = 0, RectX2 = 0, RectY1 = 0, RectY2 = 0, lvlmin = 0, lvlmax = 0;
				if (sscanf(line, "(Area (Rect %d %d %d %d)(Level %d-%d))", &RectX1, &RectY1, &RectX2, &RectY2, &lvlmin, &lvlmax) == 6)
				{
					RectLevel check = RectLevel();
					check.LevelMin = lvlmin;
					check.LevelMax = lvlmax;

					int Map1 = ((RectX1 / 256) * 1000) + (RectY1 / 256);
					int Map2 = ((RectX2 / 256) * 1000) + (RectY2 / 256);

					RECT rect = RECT();
					rect.left = min(RectX1, RectX2);
					rect.right = max(RectX1, RectX2);
					rect.top = min(RectY1, RectY2);
					rect.bottom = max(RectY1, RectY2);
					check.rectangle = rect;

					RectArea[Map1].push_back(check);

					if (Map1 != Map2)
						RectArea[Map2].push_back(check);
				}

				int mapX = 0, mapY = 0, levela = 0, itemid = 0;
				if (sscanf(line, "(Area (file %d_%d)(level %d)(item %d))", &mapX, &mapY, &levela, &itemid) == 4)
				{
					MapLvl[(mapX * 1000)+(mapY)].level = levela;
					MapLvl[(mapX * 1000) + (mapY)].item = itemid;
					MapLvl[(mapX * 1000) + (mapY)].type = 1;
				}

				int mapids = 0, levelas = 0, itemids = 0;
				if (sscanf(line, "(Area (map %d)(level %d)(item %d))", &mapids, &levelas, &itemids) == 3)
				{
					MapLvl[mapids].level = levelas;
					MapLvl[mapids].item = itemids;
					MapLvl[mapids].type = 0;
				}
			}
			fclose(filekd);
		}
	}

	if (!command || (command && modifiedFiles.count("./Configs/AreaLimit.txt"))) {
		FILE *filekt = fopen("./Configs/AreaLimit.txt", "r");
		if (filekt != NULL)
		{
			char line[BUFSIZ];
			while (fgets(line, sizeof line, filekt) != NULL)
			{
				int mapX = 0, mapY = 0, levela = 0;
				if (sscanf(line, "(AreaMax (file %d_%d)(maxLevel %d))", &mapX, &mapY, &levela) == 3)
				{
					MapMax[(mapX * 1000) + mapY].maxlevel = levela;
					MapMax[(mapX * 1000) + mapY].type = 1;
				}
				int mapid = 0, levelx = 0;
				if (sscanf(line, "(AreaMax (map %d)(maxLevel %d))", &mapid, &levelx) == 2)
				{
					MapMax[mapid].maxlevel = levelx;
					MapMax[mapid].type = 0;
				}
			}
			fclose(filekt);
		}
	}

	if (!command || (command && modifiedFiles.count("./Configs/MD5Check.txt"))) {
		FILE *fileor = fopen("./Configs/MD5Check.txt", "r");
		if (fileor != NULL)
		{
			MD5FileChecker.clear();
			unsigned __int64 Total = 0;

			char line[BUFSIZ]; 

			int NbLines = 0;
			while (fgets(line, sizeof line, fileor) != NULL)
			{
				char filename[BUFSIZ], filehash[BUFSIZ];
				if (sscanf(line, "((File %[a-z | A-Z | 0-9/<>|.,~*;`:!^+%&=?_-£#$€]) (Hash %[a-z | A-Z | 0-9/<>|.,~*;`:!^+%&=?_-£#$€]))", &filename, &filehash) == 2)
					NbLines++;
			}

			fclose(fileor);
			memset(line, 0, sizeof(line));

			fileor = fopen("./Configs/MD5Check.txt", "r");
			ofstream temp;
			temp.open("./checksum.scn");
			int count = 0;
			while (fgets(line, sizeof line, fileor) != NULL)
			{
				char filename[BUFSIZ], filehash[BUFSIZ];
				if (sscanf(line, "((File %[a-z | A-Z | 0-9/<>|.,~*;`:!^+%&=?_-£#$€]) (Hash %[a-z | A-Z | 0-9/<>|.,~*;`:!^+%&=?_-£#$€]))", &filename, &filehash) == 2)
				{
					count++;

					std::string fileUpName = (std::string)filename;
					temp << base64_encode((const unsigned char*)fileUpName.c_str(), strlen(fileUpName.c_str())) << endl;

					std::string fileUphash = (std::string)filehash;

					std::transform(fileUphash.begin(), fileUphash.end(), fileUphash.begin(), ::tolower);

					Total += sha256(fileUphash);

					Total %= INT_MAX;

					if (((count % 500) == 0) || count == NbLines)
						MD5FileChecker.push_back((int)Total);
				}
			}

			Hashes = Total;
			temp.close();
			
			if (command) {
				if (!OldMD5Check && MD5Check)
					UpdateMD5();
				CConsole::Blue("[MD5 Check] Client file checksum.scn file has been generated.");
			}
			 
			fclose(fileor);
		}
	}

	if (!command || (command && modifiedFiles.count("./Configs/OldSkillDamage.txt"))) {
		FILE *filew = fopen("./Configs/OldSkillDamage.txt", "r");
		if (filew != NULL)
		{
			ConfigCalculations.clear();
			char line[BUFSIZ];
			while (fgets(line, sizeof line, filew) != NULL)
			{
				int Class = 0, SkillID = 0, Rate = 0;
				if (sscanf(line, "(updatedamage (class %d)(action %d)(rate %d))", &Class, &SkillID, &Rate) == 3)
				{
					ConfigCalculations[(Class * 100) + SkillID].Class = Class;
					ConfigCalculations[(Class * 100) + SkillID].Rate = Rate;
				}
			}
			fclose(filew);
		}
	}
	
	if (!command || (command && modifiedFiles.count("./Configs/MirrorRate.txt"))) {
		FILE *filew = fopen("./Configs/MirrorRate.txt", "r");
		if (filew != NULL)
		{
			char line[BUFSIZ];
			while (fgets(line, sizeof line, filew) != NULL)
			{
				int Type = 0, Min = 0, Max = 0;
				if (sscanf(line, "(low (type %d) (rate %d-%d))", &Type, &Min, &Max) == 3)
				{
					HaninRate rate = HaninRate();
					rate.Max = Max;
					rate.Min = Min;
					HaninLow[Type] = rate;
				}
				else if (sscanf(line, "(middle (type %d) (rate %d-%d))", &Type, &Min, &Max) == 3)
				{
					HaninRate rate = HaninRate();
					rate.Max = Max;
					rate.Min = Min;
					HaninMiddle[Type] = rate;
				}
				else if (sscanf(line, "(high (type %d) (rate %d-%d))", &Type, &Min, &Max) == 3)
				{
					HaninRate rate = HaninRate();
					rate.Max = Max;
					rate.Min = Min;
					HaninHigh[Type] = rate;
				}
			}
			fclose(filew);
		}
	}


	if (!command || (command && modifiedFiles.count("./Configs/PVEWeapon.txt"))) {
		FILE *PVEFile = fopen("./Configs/PVEWeapon.txt", "r");
		if (PVEFile != NULL)
		{
			PVEWeapon.clear();
			char line[BUFSIZ];
			while (fgets(line, sizeof line, PVEFile) != NULL)
			{
				int index = 0;

				if (sscanf(line, "(PVEWeapon (Index %d))", &index) == 1)
					PVEWeapon[index].index = index;
			}
			fclose(PVEFile);
		}
	}
	if (!command || (command && modifiedFiles.count("./Configs/ItemEffects.txt"))) {
		FILE *Effectsfile = fopen("./Configs/ItemEffects.txt", "r");
		if (Effectsfile != NULL)
		{
			EquipEffects.clear();
			char line[BUFSIZ];
			while (fgets(line, sizeof line, Effectsfile) != NULL)
			{
				int index = 0, efTime = 0;
				char EffectName[BUFSIZ];

				if (sscanf(line, "(ItemEffect (Index %d) (Effect '%[a-z | A-Z | 0-9/<>|.,~*;`:!^+%&=?_-£#$€]') (Time %d))", &index, &EffectName, &efTime) == 3){
					ItemsEffects Equipment = ItemsEffects();

					Equipment.index = index;
					Equipment.Effect = EffectName;
					Equipment.effectTime = efTime;

					EquipEffects[index] = Equipment;
				}
			}
			fclose(Effectsfile);
		}
	}

	if (!command || (command && modifiedFiles.count("./Configs/RealTime.txt"))) {
		FILE *filen = fopen("./Configs/RealTime.txt", "r");
		if (filen != NULL)
		{
			PVEDamagePimp.clear();
			PVPDamagePimp.clear();
			char line[BUFSIZ];
			while (fgets(line, sizeof line, filen) != NULL)
			{
				int CustomBofPrefix = 0, CustomImpPrefix = 0;
				int ArmorGetPrefix = 0, ArmorGetDef = 0, BofGrade = 0, ImpGrade = 0, BofPrefix = 0, DGPrefix = 0, ImpPrefix = 0, InPrefix = 0, QiPrefix = 0, GetA = 0, GetM = 0, GetTOA = 0, GetUpg = 0, GetPrefix = 0, MixPrefix = 0, MixInfo = 0; char mixnotice[BUFSIZ];
				if (sscanf(line, "(armorpimp (prefix %d)(defense %d))", &ArmorGetPrefix, &ArmorGetDef) == 2)
				{
					ArmorPimpConfig[ArmorGetPrefix] = ArmorGetDef;
				}

				if (sscanf(line, "(bof (prefix %d))", &BofPrefix) == 1)
				{
					BofConfigRead = BofPrefix;
				}

				if (sscanf(line, "(CustomBof (prefix %d))", &CustomBofPrefix) == 1)
				{
					Bof2ConfigRead = CustomBofPrefix;
				}

				if (sscanf(line, "(HighBof (prefix %d) (grade %d))", &BofPrefix, &BofGrade) == 2)
				{
					HighGradeBof[BofPrefix] = BofGrade;
				}

				int dmgPrefix = 0, type = 0, damagePimp = 0;
				if (sscanf(line, "(damage (prefix %d)(type %d)(rate %d))", &dmgPrefix, &type, &damagePimp) == 3)
				{
					if(type == 0 || type == 2)
						PVEDamagePimp[dmgPrefix] = damagePimp;
					
					if(type == 1 || type == 2)
						PVPDamagePimp[dmgPrefix] = damagePimp;
				}

				if (sscanf(line, "(dgremover (prefix %d))", &DGPrefix) == 1)
				{
					dgConfigRead = DGPrefix;
				}

				if (sscanf(line, "(insanityRandom (prefix %d))", &InPrefix) == 1)
				{
					insanityRead = InPrefix;
				}

				if (sscanf(line, "(qigongRandom (prefix %d))", &QiPrefix) == 1)
				{
					qigongRead = QiPrefix;
				}

				if (sscanf(line, "(imp (prefix %d))", &ImpPrefix) == 1)
				{
					ImpConfigRead = ImpPrefix;
				}

				if (sscanf(line, "(CustomImp (prefix %d))", &CustomImpPrefix) == 1)
				{
					Imp2ConfigRead = CustomImpPrefix;
				}

				if (sscanf(line, "(HighImp (prefix %d) (grade %d))", &ImpPrefix, &ImpGrade) == 2)
				{
					HighGradeImperial[ImpPrefix] = ImpGrade;
				}

				if (sscanf(line, "(pimp (prefix %d)(attack %d)(magic %d)(toa %d)(upgrade %d))", &GetPrefix, &GetA, &GetM, &GetTOA, &GetUpg) == 5)
				{
					CheckPimp[GetPrefix].Prefix = 1;
					CheckPimp[GetPrefix].GetA = GetA;
					CheckPimp[GetPrefix].GetM = GetM;
					CheckPimp[GetPrefix].GetTOA = GetTOA;
					CheckPimp[GetPrefix].GetUpg = GetUpg;
				}

				if (sscanf(line, "(mix (prefix %d)(info %d)(msg '%[a-z | A-Z | 0-9/<>|.,~*;`:!^+%&=?_-£#$€]'))", &MixPrefix, &MixInfo, &mixnotice) == 3)
				{
					MixConfigPrefix.insert(MixPrefix);
					MixConfigInfo[MixPrefix] = MixInfo;
					MixConfigMsg[MixPrefix] = mixnotice;
				}
			}
			fclose(filen);
		}
	}

	if (!command || (command && modifiedFiles.count("./Configs/Notice.txt"))) {
		FILE *filem = fopen("./Configs/Notice.txt", "r");
		if (filem != NULL)
		{
			AutoCenterNotices.clear();
			char line[BUFSIZ];
			while (fgets(line, sizeof line, filem) != NULL)
			{
				char day[BUFSIZ], notice[BUFSIZ];
				int hour = 0, minute = 0, second = 0;
				if (sscanf(line, "(notice (day '%[a-z | A-Z | 0-9/<>|.,~*;`:!^+%&=?_-£#$€]')(time '%d:%d:%d')(msg '%[a-z | A-Z | 0-9/<>|.,~*;`:!^+%&=?_-£#$€]'))", &day, &hour, &minute, &second, &notice) == 5)
				{
					int time = IntTime(0, hour, minute, second);
					AutoNoticeConf noticeTime = AutoNoticeConf();
					noticeTime.Day = day;
					noticeTime.Msg = notice;
					AutoCenterNotices[time].push_back(noticeTime);
				}
			}
			fclose(filem);
		}
	}

	if (!command || (command && modifiedFiles.count("./Configs/Gap.txt"))) {
		FILE *fileo = fopen("./Configs/Gap.txt", "r");
		if (fileo != NULL)
		{
			char line[BUFSIZ];
			while (fgets(line, sizeof line, fileo) != NULL)
			{
				int gaplevel = 0;
				double gaprate = 0;
				if (sscanf(line, "(gap (level %d)(rate %lf))", &gaplevel, &gaprate) == 2)
				{
					LevelGap[gaplevel] = gaprate;
				}
			}
			fclose(fileo);
		}
	}


	if (!command || (command && modifiedFiles.count("./Configs/Reborn.txt"))) {
		FILE *fileo = fopen("./Configs/Reborn.txt", "r");
		if (fileo != NULL)
		{
			Reborns.clear();
			RebornsPenalty.clear();
			NonRebornsPenalty.clear();
			RebornsMaps.clear();
			RebornGear.clear();
			char line[BUFSIZ];
			while (fgets(line, sizeof line, fileo) != NULL)
			{
				int ID = 0, NamePad = 0, MinLvl = 0, ResetLevel = 0, RewardID = 0, Penalty = 0, QuestIndex = 0, QuestFlag = 0;
				int sbKey = 0, sbMsg = 0;
				int RebornLvl = 0, RebornGrade = 0;
				char tag[10];
				if (sscanf(line, "(Reborn (Num %d)(NameTag '%[a-z | A-Z | 0-9/<>|.,~*;`:!^+%&=?_-£#$€]')(NamePad %d)(MinLvl %d)(ResetLvl %d)(RewardID %d)(SBKey %d)(SBMsg %d))", &ID, &tag, &NamePad, &MinLvl, &ResetLevel, &RewardID, &sbKey, &sbMsg) >= 6)
				{
					Reborn rb = Reborn();
					rb.NamePad = NamePad;
					rb.MinLvl = MinLvl;
					rb.ResetLevel = ResetLevel;
					rb.RewardID = RewardID;
					rb.NameTag = tag;
					rb.sbKey = sbKey;
					rb.sbMsg = sbMsg;
					Reborns[ID] = rb;
				}

				if (sscanf(line, "(RebornGear (Grade %d)(Reborn %d))", &RebornGrade, &RebornLvl) == 2)
				{
					RbGear rb = RbGear();
					rb.Level = RebornLvl;
					RebornGear[RebornGrade] = rb;
				}

				if (sscanf(line, "(RebornPenalty (Num %d)(Penalty %d))", &ID, &Penalty) == 2)
				{
					RbPenalty rb = RbPenalty();
					rb.rbPenalty = Penalty;
					RebornsPenalty[ID] = rb;
				}

				if (sscanf(line, "(NonReborn (Increasement %d))", &Penalty) == 2)
				{
					RbPenalty rb = RbPenalty();
					rb.rbPenalty = Penalty;
					NonRebornsPenalty[1] = rb;
				}

				if (sscanf(line, "(RebornMap (Num %d)(Quest %d %d))", &ID, &QuestIndex, &QuestFlag) == 3)
				{
					RbQuest rb = RbQuest();
					rb.rbQuest = QuestIndex;
					rb.rbQFlag = QuestFlag;
					rb.rbIndex = ID;

					RebornsMaps[(QuestIndex * 1000) + QuestFlag] = rb;
				}

			}
			fclose(fileo);
		}
	}

	if (!command || (command && modifiedFiles.count("./Configs/SummonTrack.txt"))) {
		FILE *fileo = fopen("./Configs/SummonTrack.txt", "r");
		if (fileo != NULL)
		{
			char line[BUFSIZ];
			while (fgets(line, sizeof line, fileo) != NULL)
			{
				int index = 0;
				if (sscanf(line, "(summonTrack (index %d))", &index) == 1)
					SummonTrack.insert(index);
			}
			fclose(fileo);
		}
	}

	if (!command || (command && modifiedFiles.count("./Configs/GuildBuffs.txt"))) {
		FILE *fileo = fopen("./Configs/GuildBuffs.txt", "r");
		if (fileo != NULL)
		{
			char line[BUFSIZ];
			while (fgets(line, sizeof line, fileo) != NULL)
			{
				int Quest, Flag, RFlag, Item, Amount = 0;

				char Name[BUFSIZ];
				char Buff[BUFSIZ];
				char BuffTime[BUFSIZ];
				char BuffValue[BUFSIZ];
				char SBName[BUFSIZ];
				char SBKey[BUFSIZ];

				if (sscanf(line, "(GuildBuff (Name '%[a-z | A-Z | 0-9/<>|.,~*;`:!^+%&=?_-£#$€]') (Quest %d) (Flag %d) (FlagReply %d) (ItemIndex %d) (ItemAmount %d) (Buff %[0-9/,]) (Time %[0-9/,]) (Value %[0-9/,]) (SBName %[0-9/,]) (SBKey %[0-9/,]))", &Name, &Quest, &Flag, &RFlag, &Item, &Amount, &Buff, &BuffTime, &BuffValue, &SBName, &SBKey) == 11)
				{
					GuildBuffQuest guildBuff = GuildBuffQuest();
					guildBuff.Name = Name;
					guildBuff.Amount = Amount;
					guildBuff.Flag = Flag;
					guildBuff.ReplyFlag = RFlag;
					guildBuff.Index = Item;

					std::string Buffs = std::string((const char*)Buff);
					std::string BuffTimes = std::string((const char*)BuffTime);
					std::string BuffValues = std::string((const char*)BuffValue);
					std::string SBNames = std::string((const char*)SBName);
					std::string SBKeys = std::string((const char*)SBKey);

					std::vector<std::string> sBuffs = explode(",", Buffs);
					std::vector<std::string> sBuffTimes = explode(",", BuffTimes);
					std::vector<std::string> sBuffValues = explode(",", BuffValues);
					std::vector<std::string> sSBNames = explode(",", SBNames);
					std::vector<std::string> sSBKeys = explode(",", SBKeys);
					
					for (int i = 0; i < sBuffs.size(); i++) {
						GuildBuff gBuff = GuildBuff();
						int BuffID = String2Int(sBuffs[i]);
						
						gBuff.BuffID = BuffID;
						gBuff.Time = String2Int(sBuffTimes[i]);
						gBuff.Value = String2Int(sBuffValues[i]);
						gBuff.SBKey = i < sSBKeys.size() ? String2Int(sSBKeys[i]) : 0;
						gBuff.SBName = i < sSBNames.size() ? String2Int(sSBNames[i]) : 0;
						guildBuff.Buffs.push_back(gBuff);
					}

					GuildBuffQuests[Quest % 65536] = guildBuff;
				}
			}
			fclose(fileo);
		}
	}

	if (!command || (command && modifiedFiles.count("./Configs/RidingCollection.txt"))) {
		FILE *fileRidingCo = fopen("./Configs/RidingCollection.txt", "r");
		if (fileRidingCo != NULL) {
			char line[BUFSIZ];
			int CurType = 0;
			while (fgets(line, sizeof line, fileRidingCo) != NULL)
			{
				int Type = 0, Stat = 0, Rate = 0, Title = 0;
				if (sscanf(line, "%*[ \t|]<RIDING_COLLECTION type=\"%d\" stat=\"%d\" rate=\"%d\" title=\"%d\"/>", &Type, &Stat, &Rate, &Title) == 4)
				{
					RidingCollections[Type].Rate = Rate;
					RidingCollections[Type].Stat = Stat;
				}

				if (sscanf(line, "%*[ \t|]<TYPE type=\"%d\">", &CurType) == 1)
					RidingCollections[CurType].Indexes.clear();

				int Index = 0;
				if (sscanf(line, "%*[ \t|]<INDEX index=\"%d\"/>", &Index) == 1) {
					RidingCollections[CurType].Indexes.push_back(Index);
					RidingCollectionIndex[Index] = CurType;
				}
			}
			fclose(fileRidingCo);
		}
	}

	if (!command || (command && modifiedFiles.count("./Configs/MasterEnchant.txt"))) {
		FILE *masterEnchant = fopen("./Configs/MasterEnchant.txt", "r");
		if (masterEnchant != NULL) {
			MasterEnchant.clear();
			char line[BUFSIZ];
			int Info = 0;
			int In = 0;
			int Material = 0;
			int Rate = 0;
			int RateStart = 0;
			while (fgets(line, sizeof line, masterEnchant) != NULL)
			{
				int count = 0, rate = 0;
				int in = 0;
				int info = 0, material = 0, rateind = 0, out = 0;

				int OldRateStart = RateStart;
				if (sscanf(line, "%*[ \t|]<RATE no=\"%d\"/>", &RateStart) != 1)
					RateStart = OldRateStart;

				if (sscanf(line, "%*[ \t|]<SUCCESS_RATE count=\"%d\" rate=\"%d\"/>", &count, &rate) == 2)
					EnchantCount[(RateStart * 1000) + count] = rate;

				if (sscanf(line, "%*[ \t|]<INFO no=\"%d\">%*[ \t|]<IN index=\"%d\"/>%*[ \t|]<MATERIAL index=\"%d\" rateIndex=\"%d\"/>%*[ \t|]<OUT index=\"%d\"/>%*[ \t|]</INFO>", &info, &in, &material, &rateind, &out) == 5) {
					MasterEnchanting mEnchant = MasterEnchanting();
					mEnchant.IndexIn = in;
					mEnchant.MaterialUsed = material;
					mEnchant.IndexOut = out;
					mEnchant.Rate = rateind;
					MasterEnchant[info] = mEnchant;
				}
				else {
					int OldInfo = Info;
					if (sscanf(line, "%*[ \t|]<INFO no=\"%d\"/>", &Info) != 1)
						Info = OldInfo;

					int OldIn = In;
					if (sscanf(line, "%*[ \t|]<IN index=\"%d\"/>", &In) != 1)
						In = OldIn;

					int OldRate = Rate;
					int OldMat = Material;
					if (sscanf(line, "%*[ \t|]<MATERIAL index=\"%d\" rateIndex=\"%d\"/>", &Material, &Rate) != 2) {
						Material = OldMat;
						Rate = OldRate;
					}

					int Out = 0;
					if (sscanf(line, "%*[ \t|]<OUT index=\"%d\"/>", &Out) == 1 && In && Material) {
						MasterEnchanting mEnchant = MasterEnchanting();
						mEnchant.IndexIn = In;
						mEnchant.MaterialUsed = Material;
						mEnchant.IndexOut = Out;
						mEnchant.Rate = Rate;
						MasterEnchant[Info] = mEnchant;

						Material = 0;
						In = 0;
						Out = 0;
						Rate = 0;
						Info = 0;
					}
				}

			}
			fclose(masterEnchant);
		}
	}

	if (!command || (command && modifiedFiles.count("./Systems/TrainingCenter.txt"))) {
		FILE *fileTraining = fopen("./Systems/TrainingCenter.txt", "r");
		if (fileTraining != NULL) {
			char line[BUFSIZ];
			while (fgets(line, sizeof line, fileTraining) != NULL)
			{
				int MaxLvl = 0, EXP = 0, dropType = 0;
				if (sscanf(line, "%*[ \t|]<VALUE maxLv=\"%d\" fixExp=\"%d\" dropType=\"%d\"/>%*s", &MaxLvl, &EXP, &dropType) == 3)
				{
					TrainingEXP[MaxLvl].EXP = EXP;
					TrainingEXP[MaxLvl].Drop = dropType;
				}
				sscanf(line, "%*[ \t|]<GET_Free_TIME free_time=\"%d\" />%*s", &FreeTime);
				sscanf(line, "%*[ \t|]<GET_EXP_TIME time=\"%d\" />%*s", &TrainingHit);
				sscanf(line, "%*[ \t|]<GET_Time_Price Time_price=\"%d\" />%*s", &TrainingPrice);

				int Type = 0, Item = 0, Chance = 0;
				if (sscanf(line, "%*[ \t|]<VALUE key=\"%d\" rate=\"%d\" itemIndex=\"%d\"/>%*s", &Type, &Chance, &Item) == 3)
				{
					TrainingDrops[Type].Index = Item;
					TrainingDrops[Type].Chance = Chance;
					TrainingDrops[Type].Amount = 1;
				}
			}
			fclose(fileTraining);
		}
	}

	if (!command || (command && modifiedFiles.count("./Configs/Fishing.txt"))) {
		FILE *filefsh = fopen("./Configs/Fishing.txt", "r");
		if (filefsh != NULL)
		{
			FishingList.clear();
			char line[BUFSIZ];
			while (fgets(line, sizeof line, filefsh) != NULL)
			{
				int index = 0, amount = 0, chance = 0;
				if (sscanf(line, "(FishItem (index %d)(amount %d)(chance %d))", &index, &amount, &chance) == 3)
				{
					ChanceItem fish = ChanceItem();
					fish.Index = index;
					fish.Amount = amount;
					fish.Chance = chance;
					FishingList[chance].push_back(fish);
				}
			}
			fclose(filefsh);
		}
	}

	if (!command || (command && modifiedFiles.count("./Systems/GuildRaid.txt"))) {
		FILE *filegr = fopen("./Systems/GuildRaid.txt", "r");
		if (filegr != NULL)
		{
			RaidMinimumAmount = INT_MAX;
			RaidMaximumAmount = 0;
			GuildRaidLevels.clear();
			char line[BUFSIZ];
			while (fgets(line, sizeof line, filegr) != NULL)
			{
				int level = 0, amount = 0, index = 0, reward = 0, minplayers = 0, time = 0;

				if (sscanf(line, "(GuildRaid (Level %d)(Time %d)(MinPlayers %d)(AmountRequired %d)(MobIndex %d)(RewardID %d))", &level, &time, &minplayers, &amount, &index, &reward) == 6)
				{
					if (amount < RaidMinimumAmount)
						RaidMinimumAmount = amount;

					if (amount > RaidMaximumAmount)
						RaidMaximumAmount = amount;

					GuildRaidLevel lvl = GuildRaidLevel();
					lvl.MobIndex = index;
					lvl.ReqAmount = amount;
					lvl.Reward = reward;
					lvl.MinPlayers = minplayers;
					lvl.Time = time;
					GuildRaidLevels[level] = lvl;
					UnBlob.insert(index);
				}
			}
			fclose(filegr);
		}
	}

	if (!command || (command && modifiedFiles.count("./Systems/F10.txt"))) {
		FILE *filef10 = fopen("./Systems/F10.txt", "r");
		if (filef10 != NULL)
		{
			F10EXPs.clear();
			F10Items.clear();
			char line[BUFSIZ];
			while (fgets(line, sizeof line, filef10) != NULL)
			{
				int index = 0, amount = 0, chance = 0;
				bool found = false;
				int lvl = 0, mult = 0, gap = 0, ID = 0;
				signed __int64 value = 0;
				if (sscanf(line, "(F10Item (index %d)(amount %d)(chance %d))", &index, &amount, &chance) == 3)
				{
					for (int i = 0; i < F10Items.size(); i++) {
						ChanceItem f = F10Items[i];
						if (f.Index == index && f.Amount == amount && f.Chance == chance)
							found = true;
					}
					if (found)
						continue;

					ChanceItem f10Item = ChanceItem();
					f10Item.Index = index;
					f10Item.Amount = amount;
					f10Item.Chance = chance;
					F10Items.push_back(f10Item);
				}

				else
					if (sscanf(line, "(F10EXP (Level %d)(EXP %lld)(Multiply %d)(Gap %d)(RewardID %d))", &lvl, &value, &mult, &gap, &ID) == 5)
					{
						F10EXP exp = F10EXP();
						exp.Exp = value;
						exp.Gap = gap;
						exp.Mult = mult;
						exp.RID = ID;

						F10EXPs[lvl] = exp;
					}
			}
			std::sort(F10Items.begin(), F10Items.end(), sortByChance);
			fclose(filef10);
		}
	}
	
	if (!command || (command && modifiedFiles.count("./Systems/Mautareta.txt"))) {
		FILE *filemautitem = fopen("./Systems/Mautareta.txt", "r");
		if (filemautitem != NULL)
		{
			MautEXPs.clear();
			MautItem.clear();
			char line[BUFSIZ];
			while (fgets(line, sizeof line, filemautitem) != NULL)
			{
				int index = 0, amount = 0, chance = 0;
				int lvl = 0, mult = 0, gap = 0, ID = 0;
				signed __int64 value = 0;
				bool found = false;
				if (sscanf(line, "(Mautareta (index %d)(amount %d)(chance %d))", &index, &amount, &chance) == 3)
				{
					for (int i = 0; i < MautItem.size(); i++) {
						ChanceItem f = MautItem[i];
						if (f.Index == index && f.Amount == amount && f.Chance == chance)
							found = true;
					}
					if (found)
						continue;

					ChanceItem mautItem = ChanceItem();
					mautItem.Index = index;
					mautItem.Amount = amount;
					mautItem.Chance = chance;
					MautItem.push_back(mautItem);
				}
				else
					if (sscanf(line, "(MautEXP (Level %d)(EXP %lld)(Multiply %d)(Gap %d)(RewardID %d))", &lvl, &value, &mult, &gap, &ID) == 5)
					{
						F10EXP exp = F10EXP();
						exp.Exp = value;
						exp.Gap = gap;
						exp.Mult = mult;
						exp.RID = ID;

						MautEXPs[lvl] = exp;
					}

			}
			std::sort(MautItem.begin(), MautItem.end(), sortByChance);
			fclose(filemautitem);
		}
	}

	if (!command || (command && modifiedFiles.count("./Systems/BossEXP.txt"))) {
		FILE *filemautitem = fopen("./Systems/BossEXP.txt", "r");
		if (filemautitem != NULL)
		{
			BossEXPMsgs.clear();
			BossEXPs.clear();
			BossExpItem.clear();
			char line[BUFSIZ];
			while (fgets(line, sizeof line, filemautitem) != NULL)
			{
				int timeleft = 0, mob = 0, AAmount = 0, x = 0, y = 0;
				char msg[BUFSIZ];
				int index = 0, amount = 0, chance = 0;
				int lvl = 0, mult = 0, gap = 0, ID = 0;
				signed __int64 value = 0;
				bool found = false;
				if (sscanf(line, "(BossItem (index %d)(amount %d)(chance %d))", &index, &amount, &chance) == 3)
				{
					for (int i = 0; i < BossExpItem.size(); i++) {
						ChanceItem f = BossExpItem[i];
						if (f.Index == index && f.Amount == amount && f.Chance == chance)
							found = true;
					}
					if (found)
						continue;

					ChanceItem mautItem = ChanceItem();
					mautItem.Index = index;
					mautItem.Amount = amount;
					mautItem.Chance = chance;
					BossExpItem.push_back(mautItem);
				}
				else
					if (sscanf(line, "(BossEXP (Level %d)(EXP %lld)(Multiply %d)(Gap %d)(RewardID %d))", &lvl, &value, &mult, &gap, &ID) == 5)
					{
						F10EXP exp = F10EXP();
						exp.Exp = value;
						exp.Gap = gap;
						exp.Mult = mult;
						exp.RID = ID;

						BossEXPs[lvl] = exp;
					}
				else
					if(sscanf(line, "(BossMsg (TimeLeft %d)(MiniMob %d)(Amount %d)(X %d)(Y %d)(Message '%[^\"]'))", &timeleft, &mob, &AAmount, &x, &y, &msg) == 6)
				{
						std::string message(msg);
						BossEXPMsg msgEXP = BossEXPMsg();
						msgEXP.Index = mob;
						msgEXP.Amount = AAmount;
						msgEXP.X = x;
						msgEXP.Y = y;
						msgEXP.message = message.substr(0, message.length() - 4);;
						BossEXPMsgs[timeleft] = msgEXP;
				}
			}
			std::sort(BossExpItem.begin(), BossExpItem.end(), sortByChance);
			fclose(filemautitem);
		}
	}

	if (!command || (command && modifiedFiles.count("./Configs/HonorShop.txt"))) {
		FILE *filep = fopen("./Configs/HonorShop.txt", "r");
		if (filep != NULL)
		{
			char line[BUFSIZ];
			while (fgets(line, sizeof line, filep) != NULL)
			{
				int honorquest = 0, honorreward = 0, honorindex = 0, honorindexreward;
				if (sscanf(line, "(honorshop (quest %d)(reward %d))", &honorquest, &honorreward) == 2)
				{
					HonorShop[honorquest % 65536] = honorreward;
				}

				if (sscanf(line, "(honorshop (index %d)(reward %d))", &honorindex, &honorindexreward) == 2)
				{
					HonorIndex[honorindex] = honorindexreward;
				}
			}
			fclose(filep);
		}
	}

	if (!command || (command && modifiedFiles.count("./Configs/ItemReplace.txt"))) {
		FILE *filer = fopen("./Configs/ItemReplace.txt", "r");
		if (filer != NULL)
		{
			char line[BUFSIZ];
			while (fgets(line, sizeof line, filer) != NULL)
			{
				int disableP = 0, disableI = 0;
				if (sscanf(line, "(disablePrefix (prefix %d)(index %d))", &disableP, &disableI) == 2)
					DisablePrefix.insert((disableI + 100000)*disableP);

				int wrprefix = 0, wrindex = 0, wrnewindex = 0, arprefix = 0, arindex = 0, arnewindex = 0, orprefix = 0, orindex = 0, ornewindex = 0;
				char wrmsg[BUFSIZ], armsg[BUFSIZ], ormsg[BUFSIZ];
				if (sscanf(line, "(weapon (prefix %d)(index %d)(newindex %d)(msg '%[a-z | A-Z | 0-9/<>|.,~*;`:!^+%&=?_-£#$€]')", &wrprefix, &wrindex, &wrnewindex, &wrmsg) >= 3)
				{
					WeaponReplacePrefix.insert(wrprefix);
					WeaponReplace[(wrindex + 100000)*wrprefix] = wrprefix;
					WeaponReplaceIndex[(wrindex + 100000)*wrprefix] = wrnewindex;
					if (wrmsg)
					WeaponReplaceMsg[(wrindex + 100000)*wrprefix] = wrmsg;

				}

				if (sscanf(line, "(armor (prefix %d)(index %d)(newindex %d)(msg '%[a-z | A-Z | 0-9/<>|.,~*;`:!^+%&=?_-£#$€]'))", &arprefix, &arindex, &arnewindex, &armsg) >= 3)
				{
					WeaponReplacePrefix.insert(arprefix);
					WeaponReplace[(arindex + 100000)*arprefix] = arprefix;
					WeaponReplaceIndex[(arindex + 100000)*arprefix] = arnewindex;
					if (armsg)
					WeaponReplaceMsg[(arindex + 100000)*arprefix] = armsg;

				}

				if (sscanf(line, "(ornament (prefix %d)(index %d)(newindex %d)(msg '%[a-z | A-Z | 0-9/<>|.,~*;`:!^+%&=?_-£#$€]'))", &orprefix, &orindex, &ornewindex, &ormsg) >= 3)
				{
					WeaponReplacePrefix.insert(orprefix);
					WeaponReplace[(orindex + 100000)*orprefix] = orprefix;
					WeaponReplaceIndex[(orindex + 100000)*orprefix] = ornewindex;
					if (ormsg)
						WeaponReplaceMsg[(orindex + 100000)*orprefix] = ormsg;
				}

			}
			fclose(filer);
		}
	}

	if (!command || (command && modifiedFiles.count("./Configs/Summon.txt"))) {
		FILE *files = fopen("./Configs/Summon.txt", "r");
		if (files != NULL)
		{
			SummonTimer.clear();
			char line[BUFSIZ];
			while (fgets(line, sizeof line, files) != NULL)
			{
				char day[BUFSIZ], notice[BUFSIZ]; int MobIndex = 0, hour = 0, minute = 0, second = 0, MobAmount = 0, MobMap = 0, MobX = 0, MobY = 0, MobDis = 0;
				if (sscanf(line, "(summon (index %d)(amount %d)(map %d)(x %d)(y %d)(disappear %d)(day '%[a-z | A-Z | 0-9/<>|.,~*;`:!^+%&=?_-£#$€]')(time '%d:%d:%d')(msg '%[a-z | A-Z | 0-9/<>|.,~*;`:!^+%&=?_-£#$€]'))", &MobIndex, &MobAmount, &MobMap, &MobX, &MobY, &MobDis, &day, &hour, &minute, &second, &notice) == 11)
				{
					CheckSummonTimer timer = CheckSummonTimer();
					timer.Index = MobIndex;
					timer.Amount = MobAmount;
					timer.Map = MobMap;
					timer.X = MobX;
					timer.Y = MobY;
					timer.Disappear = MobDis;
					timer.Day = day;
					timer.Msg = notice;
					int time = IntTime(0, hour, minute, second);
					SummonTimer[time].push_back(timer);
				}
			}
			fclose(files);
		}
	}

	if (!command || (command && modifiedFiles.count("./Configs/Rent.txt"))) {
		FILE *filet = fopen("./Configs/Rent.txt", "r");
		if (filet != NULL)
		{
			char line[BUFSIZ];
			while (fgets(line, sizeof line, filet) != NULL)
			{
				int Billcode = 0, Rent = 0;
				if (sscanf(line, "(rent (billcode %d)(quest %d))", &Billcode, &Rent) == 2)
				{
					QuestRentItem[Billcode].push_back(Rent);
				}

				int QuestID = 0, Flag = 0, RewardIndex = 0, Info = 0, Dss = 0, Def = 0, Eva = 0, Prefix = 0, Atk = 0, Magic = 0, TOA = 0, UPG = 0, Mix = 0, stat = 0, Time = 0;

				if (sscanf(line, "(rentItem (quest %d %d)(index %d)(prefix %d)(info %d)(defense %d)(evasion %d)(attack %d)(magic %d)(toa %d)(upgrade %d)(dss %d)(itemstat %d)(time %d))", &QuestID, &Flag, &RewardIndex, &Prefix, &Info, &Def, &Eva, &Atk, &Magic, &TOA, &UPG, &Dss, &stat, &Time) >= 14)
				{
					Items t = Items();
					t.Index = RewardIndex;
					t.Amount = 1;
					t.Info = Info;
					t.Def = Def;
					t.Dss = Dss;
					t.Eva = Eva;
					t.Prefix = Prefix;
					t.Attack = Atk;
					t.Magic = Magic;
					t.Mix = Mix;
					t.Toa = TOA;
					t.Upgrade = UPG;
					t.ItemStat = stat;
					t.Time = Time;
					RentQuests[(QuestID * 1000) + Flag] = t;
				}

				int RAQuest = 0, RAIndex = 0, RAPrefix = 0, RADef = 0, RAEva = 0, RABof = 0, RADss = 0, RACoin = 0, RATime = 0;
				if (sscanf(line, "(rentarmor (quest %d)(index %d)(prefix %d)(defense %d)(evasion %d)(bof %d)(dss %d)(coin %d)(time %d))", &RAQuest, &RAIndex, &RAPrefix, &RADef, &RAEva, &RABof, &RADss, &RACoin, &RATime) == 9)
				{
					RentArmor[RAQuest % 65536].Quest = RAQuest;
					RentArmor[RAQuest % 65536].Index = RAIndex;
					RentArmor[RAQuest % 65536].Prefix = RAPrefix;
					RentArmor[RAQuest % 65536].Def = RADef;
					RentArmor[RAQuest % 65536].Eva = RAEva;
					RentArmor[RAQuest % 65536].Bof = RABof;
					RentArmor[RAQuest % 65536].Dss = RADss;
					RentArmor[RAQuest % 65536].Coin = RACoin;
					RentArmor[RAQuest % 65536].Time = RATime;
				}

				int RWQuest = 0, RWIndex = 0, RWPrefix = 0, RWAttack = 0, RWMagic = 0, RWToa = 0, RWUpgrade = 0, RWMix = 0, RWDss = 0, RWCoin = 0, RWTime = 0;
				if (sscanf(line, "(rentweapon (quest %d)(index %d)(prefix %d)(attack %d)(magic %d)(toa %d)(upgrade %d)(mix %d)(dss %d)(coin %d)(time %d))", &RWQuest, &RWIndex, &RWPrefix, &RWAttack, &RWMagic, &RWToa, &RWUpgrade, &RWMix, &RWDss, &RWCoin, &RWTime) == 11)
				{
					RentWeapon[RWQuest % 65536].Quest = RWQuest;
					RentWeapon[RWQuest % 65536].Index = RWIndex;
					RentWeapon[RWQuest % 65536].Prefix = RWPrefix;
					RentWeapon[RWQuest % 65536].Attack = RWAttack;
					RentWeapon[RWQuest % 65536].Magic = RWMagic;
					RentWeapon[RWQuest % 65536].Toa = RWToa;
					RentWeapon[RWQuest % 65536].Upgrade = RWUpgrade;
					RentWeapon[RWQuest % 65536].Mix = RWMix;
					RentWeapon[RWQuest % 65536].Dss = RWDss;
					RentWeapon[RWQuest % 65536].Coin = RWCoin;
					RentWeapon[RWQuest % 65536].Time = RWTime;
				}
			}
			fclose(filet);
		}
	}

	if (!command || (command && modifiedFiles.count("./Configs/TimedItems.txt"))) {
		FILE *filetm = fopen("./Configs/TimedItems.txt", "r");
		if (filetm != NULL)
		{
			TimedItems.clear();
			RentalItems.clear();
			char line[BUFSIZ];
			while (fgets(line, sizeof line, filetm) != NULL)
			{
				int Index = 0, Time = 0, Wearable = 0;
				if (sscanf(line, "(timeditem (index %d)(time %d)(wearable %d))", &Index, &Time, &Wearable) == 3)
				{
					TimedItems[Index].Time = Time;
					TimedItems[Index].Wearable = Wearable;
				}
				int ID = 0, EXTime = 0, Price = 0;
				if (sscanf(line, "(rental (index %d)(extendtime %d)(price %d))", &ID, &EXTime, &Price) == 3)
				{
					RentalItems[ID].Time = EXTime;
					RentalItems[ID].Price = Price;
				}
			}
			fclose(filetm);
		}
	}

	if (!command || (command && modifiedFiles.count("./Configs/SummonGuard.txt"))) {
		FILE *SummonGuardians = fopen("./Configs/SummonGuard.txt", "r");
		if (SummonGuardians != NULL)
		{
			SGuard.clear();
			char line[BUFSIZ];
			while (fgets(line, sizeof line, SummonGuardians) != NULL)
			{
				int BossIndex = 0, GuardIndex = 0, HP = 0, Amount = 0;
				if (sscanf(line, "(Guard (BossIndex %d)(GuardIndex %d)(SpawnHP %d)(SpawnAmount %d))", &BossIndex, &GuardIndex, &HP, &Amount) >= 4)
				{
					SummonGuard summon = SummonGuard();
					summon.amount = Amount;
					summon.boss = BossIndex;
					summon.guard = GuardIndex;
					summon.hp = HP;

					SGuard[BossIndex] = summon;
				}

			}
			fclose(SummonGuardians);
		}
	}

	if (!command || (command && modifiedFiles.count("./Configs/MonsterSummon.txt"))) {
		FILE *Summon = fopen("./Configs/MonsterSummon.txt", "r");
		if (Summon != NULL)
		{
			MSS.clear();
			char line[BUFSIZ];
			while (fgets(line, sizeof line, Summon) != NULL)
			{
				int ItemIndex = 0, MobIndex = 0, Time = 0, Amount = 0, AI = 0;
				if (sscanf(line, "(mss (itemindex %d)(mobindex %d)(amount %d)(time %d)(public %d))", &ItemIndex, &MobIndex, &Amount, &Time, &AI) >= 4)
				{
					Msss mss;
					mss.Amount = Amount;
					mss.MobIndex = MobIndex;
					mss.Time = Time;
					mss.Public = (AI == 1) ? 1 : 0;
					MSS[ItemIndex].MonsterList.push_back(mss);
				}

			}
			fclose(Summon);
		}
	}

	if (!command || (command && modifiedFiles.count("./Configs/MakeItem.txt"))) {
		FILE *fileqM = fopen("./Configs/MakeItem.txt", "r");
		if (fileqM != NULL)
		{
			char line[BUFSIZ];
			while (fgets(line, sizeof line, fileqM) != NULL)
			{
				int Index = 0, item = 0;
				char requireIndexs[BUFSIZ];
				char requireAmounts[BUFSIZ];
				if (sscanf(line, "(makeitem (index %d) (item %d) (requireIndexs %[0-9/,]) (requireAmounts %[0-9/,]))", &Index, &item, &requireIndexs, &requireAmounts) == 4)
				{
					MakeItem[Index].item = item;
					MakeItem[Index].requireIndexs = std::string(requireIndexs);
					MakeItem[Index].requireAmounts = std::string(requireAmounts);
					memset(requireIndexs, 0, sizeof(requireIndexs));
					memset(requireAmounts, 0, sizeof(requireAmounts));
				}

				char items[BUFSIZ];
				char itemsAmounts[BUFSIZ];
				char rates[BUFSIZ];
				if (sscanf(line, "(mineralmix (key %d) (requireIndexs %[0-9/,]) (requireAmounts %[0-9/,]) (items %[0-9/,]) (itemsAmounts %[0-9/,]) (rates %[0-9/,]))", &Index, &requireIndexs, &requireAmounts, &items, &itemsAmounts, &rates) == 6)
				{
					MakeMinerals[Index].requires = std::string(requireIndexs);
					MakeMinerals[Index].requireAmounts = std::string(requireAmounts);
					MakeMinerals[Index].itemRewards = std::string(items);
					MakeMinerals[Index].itemAmounts = std::string(itemsAmounts);
					MakeMinerals[Index].chances = std::string(rates);
					memset(requireIndexs, 0, sizeof(requireIndexs));
					memset(requireAmounts, 0, sizeof(requireAmounts));
					memset(requireIndexs, 0, sizeof(items));
					memset(requireAmounts, 0, sizeof(itemsAmounts));
					memset(requireIndexs, 0, sizeof(rates));
				}

				if (sscanf(line, "(itemchange (key %d) (requireIndexs %[0-9/,]) (requireAmounts %[0-9/,]) (items %[0-9/,]) (itemsAmounts %[0-9/,]) (rates %[0-9/,]))", &Index, &requireIndexs, &requireAmounts, &items, &itemsAmounts, &rates) == 6)
				{
					MakeChange[Index].requires = std::string(requireIndexs);
					MakeChange[Index].requireAmounts = std::string(requireAmounts);
					MakeChange[Index].itemRewards = std::string(items);
					MakeChange[Index].itemAmounts = std::string(itemsAmounts);
					MakeChange[Index].chances = std::string(rates);
					memset(requireIndexs, 0, sizeof(requireIndexs));
					memset(requireAmounts, 0, sizeof(requireAmounts));
					memset(requireIndexs, 0, sizeof(items));
					memset(requireAmounts, 0, sizeof(itemsAmounts));
					memset(requireIndexs, 0, sizeof(rates));
				}
			}
			fclose(fileqM);
		}
	}

	if (!command || (command && modifiedFiles.count("./Configs/SecretBlacksmith.txt"))) {
		FILE *fileqZ = fopen("./Configs/SecretBlacksmith.txt", "r");
		if (fileqZ != NULL)
		{
			char line[BUFSIZ];
			while (fgets(line, sizeof line, fileqZ) != NULL)
			{
				int Index = 0;
				char requireIndexs[BUFSIZ];
				char requireAmounts[BUFSIZ];
				char items[BUFSIZ];

				if (sscanf(line, "(InitSwapHighWearItem (key %d) (requireIndexs %[0-9/,]) (requireAmounts %[0-9/,]) (items %[0-9/,]))", &Index, &requireIndexs, &requireAmounts, &items) == 4)
				{
					SecretBlackSmith[Index].requires = std::string(requireIndexs);
					SecretBlackSmith[Index].requireAmounts = std::string(requireAmounts);
					SecretBlackSmith[Index].rewards = std::string(items);
					memset(requireIndexs, 0, sizeof(requireIndexs));
					memset(requireAmounts, 0, sizeof(requireAmounts));
					memset(requireIndexs, 0, sizeof(items));
				}
			}
			fclose(fileqZ);
		}
	}

	if (!command || (command && modifiedFiles.count("./Configs/MLM.txt"))) {
		FILE *LReward = fopen("./Configs/MLM.txt", "r");
		if (LReward != NULL)
		{
			MLMRewards.clear();
			char line[BUFSIZ];
			while (fgets(line, sizeof line, LReward) != NULL)
			{
				int Class = 0, Level = 0, Index = 0, Prefix = 0, Amount = 0, Info = 0, Attack = 0, Magic = 0, Toa = 0, Upgrade = 0, Defense = 0, Evasion = 0, Endurance = 0, Type = 0;

				if (sscanf(line, "(MLMReward (type %d)(level %d)(class %d)(index %d)(prefix %d)(amount %d)(info %d)(attack %d)(magic %d)(toa %d)(upgrade %d)(defense %d)(evasion %d)(endurance %d))", &Type, &Level, &Class, &Index, &Prefix, &Amount, &Info, &Attack, &Magic, &Toa, &Upgrade, &Defense, &Evasion, &Endurance) == 14)
				{
					MLMReward lvlReward = MLMReward();

					lvlReward.Type = Type;
					lvlReward.Class = Class;
					lvlReward.Index = Index;
					lvlReward.Prefix = Prefix;
					lvlReward.Amount = Amount;
					lvlReward.Info = Info;
					lvlReward.Attack = Attack;
					lvlReward.Magic = Magic;
					lvlReward.Toa = Toa;
					lvlReward.Upgrade = Upgrade;
					lvlReward.Defense = Defense;
					lvlReward.Evasion = Evasion;
					lvlReward.Endurance = Endurance;
					MLMRewards[Level].push_back(lvlReward);
				}
			}
			fclose(LReward);
		}
	}

	if (!command || (command && modifiedFiles.count("./Configs/LevelReward.txt"))) {
		FILE *LReward = fopen("./Configs/LevelReward.txt", "r");
		if (LReward != NULL)
		{
			LevelReward.clear();
			char line[BUFSIZ];
			while (fgets(line, sizeof line, LReward) != NULL)
			{
				int Class = 0, Level = 0, Index = 0, Prefix = 0, Amount = 0, Info = 0, Attack = 0, Magic = 0, Toa = 0, Upgrade = 0, Defense = 0, Evasion = 0, Endurance = 0; char rewardnotice[BUFSIZ];

				if (sscanf(line, "(reward (level %d)(class %d)(index %d)(prefix %d)(amount %d)(info %d)(attack %d)(magic %d)(toa %d)(upgrade %d)(defense %d)(evasion %d)(endurance %d)(msg '%[a-z | A-Z | 0-9/<>|.,~*;`:!^+%&=?_-£#$€]'))", &Level, &Class, &Index, &Prefix, &Amount, &Info, &Attack, &Magic, &Toa, &Upgrade, &Defense, &Evasion, &Endurance, &rewardnotice) == 14)
				{
					ConfigLevelReward lvlReward = ConfigLevelReward();

					lvlReward.Class = Class;
					lvlReward.Index = Index;
					lvlReward.Prefix = Prefix;
					lvlReward.Amount = Amount;
					lvlReward.Info = Info;
					lvlReward.Attack = Attack;
					lvlReward.Magic = Magic;
					lvlReward.Toa = Toa;
					lvlReward.Upgrade = Upgrade;
					lvlReward.Defense = Defense;
					lvlReward.Evasion = Evasion;
					lvlReward.Endurance = Endurance;
					lvlReward.Msg = rewardnotice;
					LevelReward[Level].push_back(lvlReward);
				}
			}
			fclose(LReward);
		}
	}

	if (!command || (command && modifiedFiles.count("./Configs/DailyLogin.txt"))) {
		FILE *filedLogin = fopen("./Configs/DailyLogin.txt", "r");
		if (filedLogin != NULL)
		{
			char line[BUFSIZ];
			while (fgets(line, sizeof line, filedLogin) != NULL)
			{
				int day = 0, HTML = 0, honor = 0, reward = 0, claim = 0;
				char items[BUFSIZ];
				char iamounts[BUFSIZ];
				if (sscanf(line, "(dailylogin (day %d)(claimHTML %d)(item %[0-9\\,])(amount %[0-9\\,])(honor %d)(reward %d)(HTML %d))", &day, &claim, &items, &iamounts, &honor, &reward, &HTML) == 7)
				{
					std::string sItems = std::string((const char*)items);
					std::string sAmounts = std::string((const char*)iamounts);
					DailyLogins[day].Items = sItems;
					DailyLogins[day].Amount = sAmounts;
					DailyLogins[day].Honor = honor;
					DailyLogins[day].Reward = reward;
					DailyLogins[day].HTML = HTML;
					DailyLogins[day].ClaimHTML = claim;
				}
			}
			fclose(filedLogin);
		}
	}

	if (!command || (command && modifiedFiles.count("./Configs/SkillCheck.txt"))) {
		FILE *fSkills = fopen("./Configs/SkillCheck.txt", "r");
		if (fSkills != NULL)
		{
			SkillChecks.clear();
			char line[BUFSIZ];
			while (fgets(line, sizeof line, fSkills) != NULL)
			{
				int Class = 0, ID = 0;

				char specialties[BUFSIZ], levels[BUFSIZ];

				if (sscanf(line, "(Skill (Class %d)(Index %d)(Specialties %[0-9\\,])(Levels %[0-9\\,]))", &Class, &ID, &specialties, &levels) == 4) {
					SkillLearn skill = SkillLearn();
					std::vector<std::string> specs = explode(",", std::string((const char*)specialties));
					std::vector<std::string> lvls = explode(",", std::string((const char*)levels));

					for (int i = 0; i < specs.size(); i++)
						skill.Specialties.push_back(String2Int(specs[i]));
					for (int i = 0; i < lvls.size(); i++)
						skill.Levels.push_back(String2Int(lvls[i]));

					std::sort(skill.Levels.begin(), skill.Levels.end());

					SkillChecks[(Class * 1000) + ID] = skill;
				}
			}
			fclose(fSkills);
		}
	}

	if (!command || (command && modifiedFiles.count("./Configs/Suits.txt"))) {
		FILE *fSuits = fopen("./Configs/Suits.txt", "r");
		if (fSuits != NULL)
		{
			char line[BUFSIZ];
			while (fgets(line, sizeof line, fSuits) != NULL)
			{
				int index = 0, type = 0, mult = 0;
				if (sscanf(line, "(itemCost (index %d)(type %d)(multiply %d))", &index, &type, &mult) == 3) {
					SuitStats[index].Type = type;
					SuitStats[index].Multiply = mult;
				}
			}
			fclose(fSuits);
		}
	}

	if (!command || (command && modifiedFiles.count("./Configs/QuestEx.txt"))) {
		FILE *fQuestEx = fopen("./Configs/QuestEx.txt", "r");
		if (fQuestEx != NULL)
		{
			QuestExs.clear();
			char line[BUFSIZ];
			while (fgets(line, sizeof line, fQuestEx) != NULL)
			{
				char items[BUFSIZ];
				char amounts[BUFSIZ];
				char require[BUFSIZ];
				char requireAmount[BUFSIZ];
				int index = 0, flag = 0, save = 0, minlvl = 0, maxlvl = 0, html = 0;

				if (sscanf(line, "(QuestEx (Index %d %d) (Items %[0-9\\,]) (Amount %[0-9\\,]) (Reusable %d) (MinLevel %d) (MaxLevel %d) (RequiredItems %[0-9\\,]) (RequiredAmount %[0-9\\,]) (HTML %d))", &index, &flag, &items, &amounts, &save, &minlvl, &maxlvl, &require, &requireAmount, &html) == 10) {
					QuestEx quest = QuestEx();

					std::vector<std::string> sItems = explode(",", std::string((const char*)items));
					std::vector<std::string> sAmounts = explode(",", std::string((const char*)amounts));
					std::vector<std::string> rAmounts = explode(",", std::string((const char*)requireAmount));
					std::vector<std::string> rItems = explode(",", std::string((const char*)require));

					if (rItems.size() == rAmounts.size()) {
						for (int i = 0; i < rItems.size(); i++) {
							quest.Required.push_back(String2Int(rItems[i]));
							quest.Amounts.push_back(String2Int(rAmounts[i]));
						}
					}

					if (sItems.size() == sAmounts.size()) {
						for (int i = 0; i < sItems.size(); i++) {
							quest.Items.push_back(String2Int(sItems[i]));
							quest.SAmounts.push_back(String2Int(sAmounts[i]));
						}
					}

					quest.MaxLvl = maxlvl;
					quest.MinLvl = minlvl;
					quest.Save = save;
					quest.html = html;

					QuestExs[((index % 65536) * 1000) + flag] = quest;
				}
			}
			fclose(fQuestEx);
		}
	}

	if (!command || (command && modifiedFiles.count("./Configs/TaskQuest.txt"))) {
		FILE *taskQuest = fopen("./Configs/TaskQuest.txt", "r");
		if (taskQuest != NULL)
		{
			char line[BUFSIZ];
			while (fgets(line, sizeof line, taskQuest) != NULL)
			{
				int index = 0, honor = 0, reward = 0, html = 0;
				char items[BUFSIZ];
				char require[BUFSIZ];
				char requireAmount[BUFSIZ];
				char iamounts[BUFSIZ];
				if (sscanf(line, "(taskquest (index %d)(require %[0-9\\,])(amount %[0-9\\,])(item %[0-9\\,])(amount %[0-9\\,])(honor %d)(reward %d)(HTML %d))", &index, &require, &requireAmount, &items, &iamounts, &honor, &reward, &html) == 8)
				{
					std::string sItems = std::string((const char*)items);
					std::string sAmounts = std::string((const char*)iamounts);
					std::string rItems = std::string((const char*)require);
					std::string rAmounts = std::string((const char*)requireAmount);
					TaskQuests[index % 65536].Items = sItems;
					TaskQuests[index % 65536].Amount = sAmounts;
					TaskQuests[index % 65536].Require = rItems;
					TaskQuests[index % 65536].RequireAmount = rAmounts;
					TaskQuests[index % 65536].Honor = honor;
					TaskQuests[index % 65536].Reward = reward;
					TaskQuests[index % 65536].HTML = html;
				}
			}
			fclose(taskQuest);
		}
	}	


	if (!command || (command && modifiedFiles.count("./Configs/MonsterSkills.txt"))) {
		FILE *monsterSkills = fopen("./Configs/MonsterSkills.txt", "r");
		if (monsterSkills != NULL)
		{
			MonsterSkills.clear();
			char line[BUFSIZ];
			while (fgets(line, sizeof line, monsterSkills) != NULL)
			{
				int ID, AOE, Cooldown, Buff, BuffTime, BuffValue, DamageMin, DamageMax, SBName, SBKey = 0, effectType = 0;
				char effect[BUFSIZ];
				if (sscanf(line, "(Skill (ID %d) (AOE %d) (Cooldown %d) (Effect '%[a-z | A-Z | 0-9/<>|.,~*;`:!^+%&=?_-£#$€]') (EffectType %d) (Buff %d) (BuffTime %d) (BuffValue %d) (Damage %d-%d) (SBName %d) (SBKey %d))", &ID, &AOE, &Cooldown, &effect, &effectType, &Buff, &BuffTime, &BuffValue, &DamageMin, &DamageMax, &SBName, &SBKey) == 12)
				{
					MSkill mSkill = MSkill();
					mSkill.AOERange = AOE;
					mSkill.Buff = Buff;
					mSkill.BuffValue = BuffValue;
					mSkill.BuffTime = BuffTime;
					mSkill.Cooldown = Cooldown;
					mSkill.EffectType = effectType;
					mSkill.Effect = effect;
					mSkill.DamageMin = DamageMin;
					mSkill.DamageMax = DamageMax;
					mSkill.SBKey = SBKey;
					mSkill.SBName = SBName;
					MSkills[ID] = mSkill;
				}
				else {
					char skills[BUFSIZ];

					if (sscanf(line, "(monsterSkill (Index %d) (Skills %[0-9\\,]))", &ID, &skills) == 2) {

						std::string sSkills = std::string((const char*)skills);

						std::vector<std::string> Skills_ = explode(",", sSkills);
						for (int i = 0; i < Skills_.size(); i++)
							MonsterSkills[ID].push_back((String2Int(Skills_[i])));
					}
				}
			}
			fclose(monsterSkills);
		}
	}

	if (!command || (command && modifiedFiles.count("./Configs/DailyQuest.txt"))) {
		ifstream filenwu("./Configs/DailyQuest.txt");
		if (filenwu.good())
		{
			ItemQuestRepeats.clear();
			maxAmountQ = 0;
			string line;
			while (getline(filenwu, line))
			{
				int ItemU = 0, Permanent = 0;;
				char repeatQuests[BUFSIZ];
				if (sscanf(line.c_str(), "(RepeatItem (Index %d)(Quests %[0-9\\,])(Permanent %d))", &ItemU, &repeatQuests, &Permanent) == 3)
				{
					std::string sQuests = std::string((const char*)repeatQuests);
					std::vector<std::string> Quests_ = explode(",", sQuests);
					for (int i = 0; i < Quests_.size(); i++)
						ItemQuestRepeats[ItemU].Quests.push_back(String2Int(Quests_[i]));
					ItemQuestRepeats[ItemU].Permanent = Permanent;
				}

				int DailyQuesty = 0, DailyLevel = 0, DailyMonster = 0, DailyAmount = 0, DailyRepeat = 0, DailyTime = 0, DailyItem = 0, DailyIAmount = 0, Honor = 0, RewardPt = 0, Party = 0, Resetable = 0, HousePoints = 0;;
				char monsters[BUFSIZ];
				char amounts[BUFSIZ];
				char items[BUFSIZ];
				char iamounts[BUFSIZ];
				signed __int64 DailyExp = 0;

				if (sscanf(line.c_str(), "(dailyquest (quest %d)(level %d)(party %d)(monster %[0-9\\,])(amount %[0-9\\,])(maxrepeat %d)(timelimit %d)(item %[0-9\\,])(amount %[0-9\\,])(exp %lld)(honor %d)(reward %d)(resetable %d))", &DailyQuesty, &DailyLevel, &Party, &monsters, &amounts, &DailyRepeat, &DailyTime, &items, &iamounts, &DailyExp, &Honor, &RewardPt, &Resetable) >= 12)
				{
					std::string sMonsters = std::string((const char*)monsters);
					std::string sAmounts = std::string((const char*)amounts);
					std::string sItems = std::string((const char*)items);
					std::string sIAmounts = std::string((const char*)iamounts);
					std::vector<std::string> Monsters_ = explode(",", sMonsters);
					std::vector<std::string> Amounts_ = explode(",", sAmounts);
					std::vector<std::string> Items_ = explode(",", sItems);
					std::vector<std::string> iAmounts_ = explode(",", sIAmounts);
					if (Monsters_.size() == Amounts_.size() && Items_.size() == iAmounts_.size()) {
						ConfigDailyQuest dailyQ = ConfigDailyQuest();
						dailyQ.Type = 0;
						dailyQ.Level = DailyLevel;
						dailyQ.MobAmount = 0;
						dailyQ.Repeat = DailyRepeat;
						dailyQ.Time = DailyTime;
						dailyQ.Resetable = Resetable;
						dailyQ.Item = Items_;
						dailyQ.ItemAmount = iAmounts_;
						dailyQ.Monsters = Monsters_;
						dailyQ.Exp = DailyExp;
						dailyQ.Honor = Honor;
						dailyQ.RewardPt = RewardPt;
						dailyQ.Party = Party;
						for (int i = 0; i < Monsters_.size(); i++) {
							MonsterDailyQuest mQuest = MonsterDailyQuest();
							mQuest.Quest = DailyQuesty;
							int Amount = String2Int(Amounts_[i]);

							if (Amount > maxAmountQ)
								maxAmountQ = Amount;

							mQuest.MainIndex = 0;
							mQuest.Amount = Amount;
							MonsterQuests[String2Int(Monsters_[i])].push_back(mQuest);
							dailyQ.MobAmount += Amount;
						}
						DailyQuest[DailyQuesty % 65536] = dailyQ;
					}
				}
				else if (sscanf(line.c_str(), "(dailyquest (quest %d)(level %d)(party %d)(monster %[0-9\\,])(amount %[0-9\\,])(maxrepeat %d)(timelimit %d)(item %[0-9\\,])(amount %[0-9\\,])(exp %lld)(honor %d)(reward %d)(resetable %d)(HousePoints %d))", &DailyQuesty, &DailyLevel, &Party, &monsters, &amounts, &DailyRepeat, &DailyTime, &items, &iamounts, &DailyExp, &Honor, &RewardPt, &Resetable, &HousePoints) >= 13)
				{
					std::string sMonsters = std::string((const char*)monsters);
					std::string sAmounts = std::string((const char*)amounts);
					std::string sItems = std::string((const char*)items);
					std::string sIAmounts = std::string((const char*)iamounts);
					std::vector<std::string> Monsters_ = explode(",", sMonsters);
					std::vector<std::string> Amounts_ = explode(",", sAmounts);
					std::vector<std::string> Items_ = explode(",", sItems);
					std::vector<std::string> iAmounts_ = explode(",", sIAmounts);
					if (Monsters_.size() == Amounts_.size() && Items_.size() == iAmounts_.size()) {
						ConfigDailyQuest dailyQ = ConfigDailyQuest();
						dailyQ.Type = 0;
						dailyQ.Level = DailyLevel;
						dailyQ.MobAmount = 0;
						dailyQ.Repeat = DailyRepeat;
						dailyQ.Time = DailyTime;
						dailyQ.Resetable = Resetable;
						dailyQ.Item = Items_;
						dailyQ.ItemAmount = iAmounts_;
						dailyQ.Monsters = Monsters_;
						dailyQ.Exp = DailyExp;
						dailyQ.Honor = Honor;
						dailyQ.RewardPt = RewardPt;
						dailyQ.Party = Party;
						dailyQ.HousePoints = HousePoints;

						for (int i = 0; i < Monsters_.size(); i++) {
							MonsterDailyQuest mQuest = MonsterDailyQuest();
							mQuest.Quest = DailyQuesty;
							int Amount = String2Int(Amounts_[i]);

							if (Amount > maxAmountQ)
								maxAmountQ = Amount;

							mQuest.MainIndex = 0;
							mQuest.Amount = Amount;
							MonsterQuests[String2Int(Monsters_[i])].push_back(mQuest);
							dailyQ.MobAmount += Amount;
						}
						DailyQuest[DailyQuesty % 65536] = dailyQ;
					}
				}
				else if (sscanf(line.c_str(), "(dailyquest (quest %d)(level %d)(party %d)(monsterGroup %[0-9\\,-])(amount %[0-9\\,])(maxrepeat %d)(timelimit %d)(item %[0-9\\,])(amount %[0-9\\,])(exp %lld)(honor %d)(reward %d)(resetable %d)(HousePoints %d))", &DailyQuesty, &DailyLevel, &Party, &monsters, &amounts, &DailyRepeat, &DailyTime, &items, &iamounts, &DailyExp, &Honor, &RewardPt, &Resetable, &HousePoints) >= 13)
				{
					std::string sMonsters = std::string((const char*)monsters);
					std::string sAmounts = std::string((const char*)amounts);
					std::string sItems = std::string((const char*)items);
					std::string sIAmounts = std::string((const char*)iamounts);
					std::vector<std::string> Monsters_ = explode(",", sMonsters);
					std::vector<std::string> Amounts_ = explode(",", sAmounts);
					std::vector<std::string> Items_ = explode(",", sItems);
					std::vector<std::string> iAmounts_ = explode(",", sIAmounts);
					if (Monsters_.size() == Amounts_.size() && Items_.size() == iAmounts_.size()) {
						ConfigDailyQuest dailyQ = ConfigDailyQuest();
						dailyQ.Resetable = Resetable;
						dailyQ.Type = 1;
						dailyQ.Level = DailyLevel;
						dailyQ.MobAmount = 0;
						dailyQ.Repeat = DailyRepeat;
						dailyQ.Time = DailyTime;
						dailyQ.Item = Items_;
						dailyQ.ItemAmount = iAmounts_;
						dailyQ.Monsters = Monsters_;
						dailyQ.Exp = DailyExp;
						dailyQ.Honor = Honor;
						dailyQ.RewardPt = RewardPt;
						dailyQ.Party = Party;
						dailyQ.HousePoints = HousePoints;
						for (int i = 0; i < Monsters_.size(); i++) {

							std::vector<std::string> MonstersPerGroup_ = explode("-", Monsters_[i]);
							int Amount = String2Int(Amounts_[i]);
							for (int j = 0; j < MonstersPerGroup_.size(); j++) {
								MonsterDailyQuest mQuest = MonsterDailyQuest();
								mQuest.Quest = DailyQuesty;
								mQuest.MainIndex = String2Int(MonstersPerGroup_[0]);
								mQuest.Amount = Amount;
								MonsterQuests[String2Int(MonstersPerGroup_[j])].push_back(mQuest);
							}
							if (Amount > maxAmountQ)
								maxAmountQ = Amount;

							dailyQ.MobAmount += Amount;
						}
						DailyQuest[DailyQuesty % 65536] = dailyQ;
					}
				}
				else if (sscanf(line.c_str(), "(dailyquest (quest %d)(level %d)(party %d)(monsterGroup %[0-9\\,-])(amount %[0-9\\,])(maxrepeat %d)(timelimit %d)(item %[0-9\\,])(amount %[0-9\\,])(exp %lld)(honor %d)(reward %d)(resetable %d))", &DailyQuesty, &DailyLevel, &Party, &monsters, &amounts, &DailyRepeat, &DailyTime, &items, &iamounts, &DailyExp, &Honor, &RewardPt, &Resetable) >= 12)
				{
					std::string sMonsters = std::string((const char*)monsters);
					std::string sAmounts = std::string((const char*)amounts);
					std::string sItems = std::string((const char*)items);
					std::string sIAmounts = std::string((const char*)iamounts);
					std::vector<std::string> Monsters_ = explode(",", sMonsters);
					std::vector<std::string> Amounts_ = explode(",", sAmounts);
					std::vector<std::string> Items_ = explode(",", sItems);
					std::vector<std::string> iAmounts_ = explode(",", sIAmounts);
					if (Monsters_.size() == Amounts_.size() && Items_.size() == iAmounts_.size()) {
						ConfigDailyQuest dailyQ = ConfigDailyQuest();
						dailyQ.Resetable = Resetable;
						dailyQ.Type = 1;
						dailyQ.Level = DailyLevel;
						dailyQ.MobAmount = 0;
						dailyQ.Repeat = DailyRepeat;
						dailyQ.Time = DailyTime;
						dailyQ.Item = Items_;
						dailyQ.ItemAmount = iAmounts_;
						dailyQ.Monsters = Monsters_;
						dailyQ.Exp = DailyExp;
						dailyQ.Honor = Honor;
						dailyQ.RewardPt = RewardPt;
						dailyQ.Party = Party;
						for (int i = 0; i < Monsters_.size(); i++) {

							std::vector<std::string> MonstersPerGroup_ = explode("-", Monsters_[i]);
							int Amount = String2Int(Amounts_[i]);
							for (int j = 0; j < MonstersPerGroup_.size(); j++) {
								MonsterDailyQuest mQuest = MonsterDailyQuest();
								mQuest.Quest = DailyQuesty;
								mQuest.MainIndex = String2Int(MonstersPerGroup_[0]);
								mQuest.Amount = Amount;
								MonsterQuests[String2Int(MonstersPerGroup_[j])].push_back(mQuest);
							}
							if (Amount > maxAmountQ)
								maxAmountQ = Amount;

							dailyQ.MobAmount += Amount;
						}
						DailyQuest[DailyQuesty % 65536] = dailyQ;
					}
				}

			}
			maxAmountQ *= 1000;
			filenwu.close();
		}
	}

	timeReloading = time(0);

	if (!command) {
		
		ifstream fTimedQuest("./Database/TimedQuest.db");
		if (fTimedQuest.good()) {
			string line;
			ofstream temp("./Database/tempQ.txt");

			while (getline(fTimedQuest, line))
			{
				int Type = 0, Repeat = 0, Time = 0;
				if (sscanf(line.c_str(), "(timedQuest (ID %d)(Repeat %d)(Time %d))", &Type, &Repeat, &Time) == 3)
				{
					if (Time > (int)time(0)) {
						QuestTime quest = QuestTime();
						quest.MaxRepeat = Repeat;
						quest.Time = Time;
						PlayerTimedQuest.replaceInsert(Type, quest);
						temp << line << endl;
					}
				}
			}
			temp.close();
			fTimedQuest.close();
			remove("./Database/TimedQuest.db");
			rename("./Database/tempQ.txt", "./Database/TimedQuest.db");
		}


		ifstream fItemLimit("./Database/ItemLimit.db");
		if (fItemLimit.good()) {
			string line;
			ofstream temp("./Database/tempIL.txt");
			ItemLimitUsage.clear();
			while (getline(fItemLimit, line))
			{
				int Key = 0, Usage = 0, Time = 0;
				if (sscanf(line.c_str(), "(itemLimit (Key %d)(Usage %d)(Time %d))", &Key, &Usage, &Time) == 3)
				{
					if (Time > (int)time(0)) {
						ItemLimitConf itemL = ItemLimitConf();
						itemL.Usage = Usage;
						itemL.Time = Time;
						ItemLimitUsage.replaceInsert(Key, itemL);
						temp << line << endl;
					}
				}
			}
			temp.close();
			fItemLimit.close();
			remove("./Database/ItemLimit.db");
			rename("./Database/tempIL.txt", "./Database/ItemLimit.db");
		}

		ifstream fPolls("./Database/Polls.db");
		if (fPolls.good()) {
			string line;
			ofstream temp("./Database/tempP.txt");

			while (getline(fPolls, line))
			{
				int Index = 0, Vote = 0;
				char Hash[BUFSIZ];

				if (sscanf(line.c_str(), "(PollVote (Index %d) (Vote %d) (Hash '%[a-z | A-Z | 0-9/<>|.,~*;`:!^+%&=?_-£#$€]'))", &Index, &Vote, &Hash) == 3)
				{
					if (Polls.count(Index)) {
						std::set<int> votes = PollVotes.count(Hash) ? PollVotes.findValue(Hash) : std::set<int>();
						votes.insert(Index);
						PollVotes.replaceInsert(Hash, votes);
						int CurVotes = PollVoteAmount.count((Index * 1000) + Vote) ? PollVoteAmount.findValue((Index * 1000) + Vote) : 0;
						PollVoteAmount.replaceInsert((Index * 1000) + Vote, CurVotes + 1);
						temp << line << endl;
					}
				}
			}

			temp.close();
			fPolls.close();
			remove("./Database/Polls.db");
			rename("./Database/tempP.txt", "./Database/Polls.db");
		}

		FILE *filekx = fopen("./Database/Duel.db", "r");
		if (filekx != NULL)
		{
			char line[BUFSIZ];
			while (fgets(line, sizeof line, filekx) != NULL)
			{
				int type = 0, pid = 0, mclass = 0, level = 0;
				char Name[BUFSIZ];
				if (sscanf(line, "(registration (type %d)(PID %d)(name '%[a-z | A-Z | 0-9/<>|.,~*;`:!^+%&=?_-£#$€]')(class %d)(level %d))", &type, &pid, &Name, &mclass, &level) == 5) {
					DuelRegistre reg;
					reg.PID = pid;
					reg.Name = Name;
					reg.nVictory = 0;
					reg.Class = mclass;
					reg.Level = level;
					if (!DuelNames.count(pid)) {
						DuelNames.replaceInsert(pid, reg.Name);
						std::vector<DuelRegistre> kc = DuelRegistrationList.count(type) ? DuelRegistrationList.findValue(type) : std::vector<DuelRegistre>();
						kc.push_back(reg);
						DuelRegistrationList.replaceInsert(type, kc);
					}
				}
			}
			fclose(filekx);
		}

		FILE *fileqx = fopen("./Database/EventMaps.db", "r");
		if (fileqx != NULL)
		{
			char line[BUFSIZ];
			while (fgets(line, sizeof line, fileqx) != NULL)
			{
				int ID = 0, PID = 0;
				if (sscanf(line, "(registration (ID %d)(PID %d))", &ID, &PID) == 2)
					EventMapsRegistration[ID].insert(PID);
				
			}
			fclose(fileqx);
		}

		reloadGVG();
		reloadProtect();
		reloadSV();
		reloadBlock();
	}
}

void reloadBlock() {
	FILE *filekx = fopen("./Database/HWIDBlock.txt", "r");
	if (filekx != NULL)
	{
		BlockList.clear();
		PlayerBlockCheck.clear();
		char line[BUFSIZ];
		while (fgets(line, sizeof line, filekx) != NULL)
		{
			for (int i = 0; i < strlen(line); i++) {
				if (line[i] == '-')
					line[i] = '!';
			}

			int uid = 0;
			char HWID[BUFSIZ], MAC[BUFSIZ], IP[BUFSIZ];
			if (sscanf(line, "(hwidblock (uid %d)(hwid '%[a-z | A-Z | 0-9/<>|.,~*;`:!^+%&=?_-£#$€]')(mac '%[a-z | A-Z | 0-9/<>|.,~*;`:!^+%&=?_-£#$€]')(ip '%[a-z | A-Z | 0-9/<>|.,~*;`:!^+%&=?_-£#$€]'))", &uid, &HWID, &MAC, &IP) == 4)
			{
				for (int i = 0; i < strlen(HWID); i++) {
					if (HWID[i] == '!')
						HWID[i] = '-';
				}

				PlayerBlockCheck.insert(uid);
				//blockLock.Enter();
				BlockList.insert(sha256(HWID));
				BlockList.insert(sha256(MAC));
				BlockList.insert(sha256(IP));
				//blockLock.Leave();
			}
		}
		fclose(filekx);
	}
}

void reloadSV() {
	FILE *filekx = fopen("./Database/SufferingValley.db", "r");
	if (filekx != NULL)
	{
		SufferingValleyRegistration.clear();
		DestructingBlackList.clear();

		SufferingValley::GuildFirst = 0;
		SufferingValley::GuildSecond = 0;
		SufferingValley::FirstGuild = "";
		SufferingValley::SecondGuild = "";

		char line[BUFSIZ];
		while (fgets(line, sizeof line, filekx) != NULL)
		{
			int gid = 0;
			char Name[BUFSIZ];
			if (sscanf(line, "(registration (GID %d)(name '%[a-z | A-Z | 0-9/<>|.,~*;`:!^+%&=?_-£#$€]'))", &gid, &Name) == 2)
				SufferingValleyRegistration.replaceInsert(gid, Name);
			else
				if (sscanf(line, "(chosen (GID %d)(name '%[a-z | A-Z | 0-9/<>|.,~*;`:!^+%&=?_-£#$€]'))", &gid, &Name) == 2) {
					if (!SufferingValley::GuildFirst) {
						SufferingValley::GuildFirst = gid;
						SufferingValley::FirstGuild = Name;
					}
					else if (!SufferingValley::GuildSecond) {
						SufferingValley::GuildSecond = gid;
						SufferingValley::SecondGuild = Name;
						SufferingValley::Selection = true;
					}
				}
				else
					if (sscanf(line, "(BlackListed (GID %d))", &gid) == 1)
						SVBlackList.insert(gid);
		}
		fclose(filekx);
	}
}

void reloadGVG() {
	FILE *filekx = fopen("./Database/Destructing.db", "r");
	if (filekx != NULL)
	{
		ScenarioRegistration.clear();
		ScenarioGuild.clear();
		DestructingBlackList.clear();
		
		Scenario::GuildFirst = 0;
		Scenario::GuildSecond = 0;
		Scenario::FirstGuild = "";
		Scenario::SecondGuild = "";
		Scenario::RegisterAmount = 0;

		char line[BUFSIZ];
		while (fgets(line, sizeof line, filekx) != NULL)
		{
			int gid = 0;
			char Name[BUFSIZ];
			if (sscanf(line, "(registration (GID %d)(name '%[a-z | A-Z | 0-9/<>|.,~*;`:!^+%&=?_-£#$€]'))", &gid, &Name) == 2) {
				ScenarioRegistration.insert(gid);
				Scenario::RegisterAmount += 1;
				DKInfo dk = DKInfo();
				dk.GID = gid;
				dk.Name = Name;
				ScenarioGuild.push_back(dk);
			}else
				if (sscanf(line, "(chosen (GID %d)(name '%[a-z | A-Z | 0-9/<>|.,~*;`:!^+%&=?_-£#$€]'))", &gid, &Name) == 2) {
					if (!Scenario::GuildFirst) {
						Scenario::GuildFirst = gid;
						Scenario::FirstGuild = Name;
					}
					else if(!Scenario::GuildSecond) {
						Scenario::GuildSecond = gid;
						Scenario::SecondGuild = Name; 
						Scenario::Selection = true;
					}
				}
				else
					if (sscanf(line, "(BlackListed (GID %d))", &gid) == 1)
						DestructingBlackList.insert(gid);
		}
		fclose(filekx);
	}
}

void reloadProtect() {
	FILE *filekx = fopen("./Database/ProtectLeader.db", "r");
	if (filekx != NULL)
	{
		ProtectLeaderList.clear();
		ProtectLeaderName.clear();
		ProtectBlackList.clear();

		Protect32::GuildFirst = 0;
		Protect32::GuildSecond = 0;
		Protect32::FirstGuild = "";
		Protect32::SecondGuild = "";

		char line[BUFSIZ];
		while (fgets(line, sizeof line, filekx) != NULL)
		{
			int gid = 0;
			char Name[BUFSIZ];
			if (sscanf(line, "(registration (GID %d)(name '%[a-z | A-Z | 0-9/<>|.,~*;`:!^+%&=?_-£#$€]'))", &gid, &Name) == 2) {
				ProtectLeaderList.push_back(gid);
				ProtectLeaderName.replaceInsert(gid, Name);
			}
			else
				if (sscanf(line, "(chosen (GID %d)(name '%[a-z | A-Z | 0-9/<>|.,~*;`:!^+%&=?_-£#$€]'))", &gid, &Name) == 2) {
					if (!Protect32::GuildFirst) {
						Protect32::GuildFirst = gid;
						Protect32::FirstGuild = Name;
					}
					else if (!Protect32::GuildSecond) {
						Protect32::GuildSecond = gid;
						Protect32::SecondGuild = Name;
						Protect32::Selection = true;
					}
				}
				else
					if (sscanf(line, "(BlackListed (GID %d))", &gid) == 1)
						ProtectBlackList.insert(gid);
		}
		fclose(filekx);
	}
}

void CleanLoadConfig() {
	EmoteSystem.clear();
	ItemWebsite.clear();
	FishingList.clear();
	MD5File.clear();
	SkillsPVP.clear();
	ItemDisable.clear();
	RidingDisableSkill.clear();
	ugog.clear();
	QuestDisable.clear();
	SkillsDamage.clear();
	TimedItems.clear();
	BuffedItems.clear();
	Boxes.clear();
	WCRewards.clear();
	WeaponReplacePrefix.clear();
	WeaponReplaceIndex.clear();
	WeaponReplace.clear();
	WeaponReplaceMsg.clear();
	PVPConfigCalculations.clear();
	ConfigCalculations.clear();
	AutoCenterNotices.clear();
	SummonTimer.clear();
	AFKMap.clear();
	SinDisable.clear();
	MSS.clear();
	ItemUsed.clear();
	ItemQuest.clear();
	AutoNotices.clear();
	UnBlob.clear();
	UnGap.clear();
	MapLvl.clear();
	LevelReward.clear();
	DailyQuest.clear();
	DisableSkill.clear();
	MapMax.clear();
	PacketSpam.clear();
	PacketBlock.clear();
	PacketSpamConf.clear();
	Filter.clear();
	BlockList.clear();
	Tracker.clear();
	Restrictions.clear();
	RewardLimit.clear();
	MakeItem.clear();
	MakeChange.clear();
	MakeMinerals.clear();
	Macro.clear();
	DisableSkillFile.clear();
	MonstersBuff.clear();
	RMonstersBuff.clear();
	QuestsNotice.clear();
	SkillBook.clear();
	SkillDowngrade.clear();
	CheckCooldownConfig.clear();
	CheckEggCooldownConfig.clear();
	PetTime.clear();
	CheckRangeConfig.clear();
	QuestWebsite.clear();
	CustomCommands.clear();
	SGuard.clear();
	BuffDisableCheck.clear();
	BuffRemoveCheck.clear();
	BufferCheck.clear();
	BuffMakerCheck.clear();
	BofConfigRead = 0;
	Bof2ConfigRead = 0;

	HighGradeBof.clear();
	BattlepassReward.clear();
	HighGradeImperial.clear();
	NormalPetTalisman.clear();
	MonsterPetTalisman.clear();
	CostumeTalisman.clear();
	SkinTalisman.clear();
	Rewards.clear();
	DutyQuest.clear();
	DutyMonsterQuests.clear();

	ReadConfig(false);
}

int DBCheck()
{
	int x = 0, y = 0;
	RETCODE rc; HENV henv; HDBC hdbc;
	const char *db = ConfigCheckDB1.c_str();
	SQLAllocEnv(&henv);
	SQLAllocConnect(henv, &hdbc);
	rc = SQLConnect(hdbc, (unsigned char*)db, SQL_NTS, 0, 0, 0, 0);

	if ((rc != SQL_SUCCESS) && (rc != SQL_SUCCESS_WITH_INFO))
	{
		SQLFreeConnect(hdbc);
		SQLFreeEnv(henv);
	} else {
		x = 1;
	}

	SQLDisconnect(hdbc);
	SQLFreeConnect(hdbc);
	SQLFreeEnv(henv);
	RETCODE rcx; HENV henvx; HDBC hdbcx;
	const char *dbx = ConfigCheckDB2.c_str();
	SQLAllocEnv(&henvx);
	SQLAllocConnect(henvx, &hdbcx);
	rcx = SQLConnect(hdbcx, (unsigned char*)dbx, SQL_NTS, 0, 0, 0, 0);

	if ((rcx != SQL_SUCCESS) && (rcx != SQL_SUCCESS_WITH_INFO))
	{
		SQLFreeConnect(hdbcx);
		SQLFreeEnv(henvx);
	} else {
		y = 1;
	}

	SQLDisconnect(hdbcx);
	SQLFreeConnect(hdbcx);
	SQLFreeEnv(henvx);

	if (!x || !y)
		return 1;
	else
		return 1;
}