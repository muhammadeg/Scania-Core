#include <sys/types.h>
#include <sys/stat.h>
#include "dirent.h"
extern int maximum(int a, int b);
extern int BofConfigRead , dgConfigRead , insanityRead , qigongRead , ImpConfigRead , ScaniaLicense , NailKill , Bof2ConfigRead , Imp2ConfigRead ;
extern int ScrollTimeCheck;
extern int ReloadingMobs;
extern char ConfigCheck[50], ConfigClient[50], ConfigEngine[50], ConfigEpk[50], AntiKsCheck[50], SinCheck[50], PlayerCheck[50], Active2ndPwd[50], ThiefActiveCheck[50],ShamanActiveCheck[50], ShopRewardCheck[50];
extern char ServerName[50], AuthSvr[50], VoteAPIKey[50];
extern char BossEXPName[50], BossEXPFinalMsg[BUFSIZ];
extern char BFName[50], LMSName[50], DKName[50], PLName[50], TBName[50], SVName[50], DTName[50], CTFName[50], LotteryName[50], LottoName[50], F10Name[50], MautName[50], HuntingSysName[50], WCName[50];
extern char ShoutsWebhook[BUFSIZ], LevelWebhook[BUFSIZ], BofWebhook[BUFSIZ], NoticeWebHook[BUFSIZ], Avatar[BUFSIZ], StarterWebhook[BUFSIZ], RebornWebhook[BUFSIZ], AssassinWebhook[BUFSIZ], HonorNoticeWebhook[BUFSIZ], AuctionNoticeWebhook[BUFSIZ];
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
extern int FireStormVThief, HealScale;
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
extern int ShadowAOE, ShadowRange; 
extern int EFakePlayers;
extern int AuctionLimit;
extern int GuildLimit;
extern int SQCheck, maxAmountQ;
extern int DuelDuration;
extern int MinMacro, MaxMacro, MacroStartTime;

extern int MAX_CONNECTIONS_PER_IP;
extern unsigned int CONNECTION_DELAY;
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
extern int HSRange;
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
extern int My_CDProtection, My_CDValue;
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
extern int PPSys, PPSysB, PPEXP, CJBEXP, CJBSYS, CJBSYSB, CJBEXPActive, CJBRange, PPActive, My_PPActive, My_PPRange;
extern int itemIndex;
extern int EVGoodReward, EVGoodLoser, EVGoodDraw;
extern int PetBound, TimedItemBound;
extern int BossEXPQuest, BossEXPRange, BossEXPTime, BossEXPPrepare, BossEXPMap, BossEXPMob, BossEXPMX, BossEXPMY, BossEXPPX, BossEXPPY;
extern int t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16, t17, t18, t19, t20, t21, t22, t23;
extern int HonorNotices, ImperialNotices, BofNotices;
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
extern void ReadConfig(bool command);
extern void CleanLoadConfig();
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