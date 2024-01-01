#include <string>
#include <set>

struct PlayerBuffs
{
	int Value;
	int Remain;
}; 


int GetLevelDiff();
bool isPlayerInPVP(void* Player);
void PortToStart(void* Player);
int GetTBMap();
std::string getUptime();
std::string getSysUpTime();

void __fastcall ContinueArrowExplosion(void* Player);
std::string Int2String(int value);
std::string getServerName();
std::string ReplaceInvalidCharacters(std::string value);

int EventConfig(std::string day);
int isPeaceEvilMode();
int HonorMessageSys(void* Player, int Type);
int HonorMessageSysA(void* Player, int Type);
bool isPKIgnoredItem(int Index);
void insertReward(void* Player, int RewardID);
int __fastcall Tick(void *Player, void *edx);
int calculDmg(void* Player, int SkillID, void* Target);
int GetBuffStat(int ID, int BuffID);
bool BuffExists(int ID, int BuffID);
void __fastcall CancelBuffPrty(int a1, void* _edx, int a5);
void updateBuff(int ID, int BuffID, int Value);
void insertBuff(int ID, int BuffID, int Value, int Offset);
//void insertMail(int IID, int Index, int MaxEnd, int CurEnd, int Info, int Num, int XHit, int XDefense, int XAttack, int XMagic, int XDodge, int Protect, int UpgrLevel, int SetGem, int Prefix, int ItemStat);
int __fastcall GetBuffStat(int a5, void* edx, int BuffID, int tries);
void __fastcall UpdateBuffStat(int a5, void* edx, int BuffID, int Time, int Value, int tries);
int __fastcall _GetBuffStat(int a5, void* edx, int BuffID);
bool __fastcall _HaveBuff(int a5, void* edx, int BuffID);
void __fastcall _UpdateBuffStat(int a5, void* edx, int BuffID, int Time, int Value);
void __fastcall _CancelBuffStat(int a5, void* edx, int BuffID);
bool __fastcall HaveBuff(int a5, void* edx, int BuffID, int tries);
int __fastcall MyGetBuffRemain(int a5, void* edx, int BuffID, int tries);
int __fastcall _MyGetBuffRemain(int a5, void* edx, int BuffID);
int __fastcall OrnamentPutOff(void *Itemx, void *edx, int Playerx);
void __fastcall addSpecialBuff(int a5, void* edx, int BuffID, int Value);
int __fastcall hasSpecialBuff(int a5, void* edx, int BuffID);
void __fastcall deleteSpecialBuff(int a5, void* edx, int BuffID);
int __fastcall GetSpecialBuff(int a5, void* edx, int BuffID);
bool isSpecialBuff(int index);
int SoulPocketDamage(void* Player, int Damage);
int _SoulPocketDamage(void* Player, int Damage);
void CheckForDailyQuest(void* Player, void* Monster);
void UpdateAutoMission(void* Player, void* Monster);
void RandomSummoning(void* Player, void* Monster);
void UpdateAutoMissionItem(void* Player);
void setMapData();
void setInitItem();
bool isSoulPocket(int Index);
bool isNecklace2(int Index);
bool isPet(int Index);
bool isUnaggroMob(int Index);
bool isItemRiding(int Index);
bool isItemSuit(int Index);
bool isItemCustomWeapon(int Index);
void updateRidingCollection(void* Player, int Collection, int Type, int Stat, int Rate);
void ShowAuction(void* Player, char Type, unsigned short Page);
void UpdateAuction();
int __fastcall LevelUp(void *Player, void *edx);
bool isInMacroMap(int MapX, int MapY);
bool isSystemTime(const char* type);
bool isEndSystemTime(const char* type);
int __fastcall GetInventorySize(int Player, void *edx);
void AddHouseReward(int Time);
void GVGSelection();
void reloadGVG();
void reloadBlock();
void startGVG();
void ProtectSelection();
void reloadProtect();
void reloadSV();
void startProtect();
void DrawMainMenu(std::string MenuName);
void insertReward(void* Player, int RewardID);
void GenMonsterChannel();
bool is_file_exist(const char *fileName);
void UpdateMD5();
int GetObjectChannel(int Object);
void SetObjectChannel(int Object, int Channel);
std::string GetHardware(void* Player);
std::string GetMACAddr(void* Player);
std::string GetPC(void* Player);
bool isIPEnabled();

namespace PlayerProperty
{
	/* Continue Skills Begin */
	static int const ContinueSkillPlayerX = 1720;
	static int const ContinueSkillPlayerY = 1724;
	static int const ContinueSkillPlayerTarget = 1728;
	static int const ContinueSkillPlayerSkillGrade = 1732;
	static int const ContinueSkillPlayerSkillID = 1736;
	static int const ContinueSkillPlayerSkillDelay = 1740;
	static int const ContinueSkillPlayerSkillCount = 1744;
	static int const FarContinueSkillPlayerTarget = 1748;
	static int const FarContinueSkillPlayerSkillGrade = 1752;
	static int const FarContinueSkillPlayerSkillID = 1756;
	static int const FarContinueSkillPlayerSkillDelay = 1760;
	static int const FarContinueSkillPlayerSkillCount = 1764;
	static int const FarContinueSkillPlayerDamage = 1768;
	static int const RuptureContinueSkillPlayerTarget = 1772;
	static int const RuptureContinueSkillPlayerSkillGrade = 1776;
	static int const RuptureContinueSkillPlayerSkillID = 1780;
	static int const RuptureContinueSkillPlayerSkillDelay = 1784;
	static int const RuptureContinueSkillPlayerSkillCount = 1788;
	static int const RuptureContinueSkillPlayerDamage = 1792;
	static int const ContinueSkillThiefReset = 1796;
	/* Continue Skills End */

	static int const Unblob = 1684;
	static int const MobPet = 1688;
	static int const Channel = 1692;
	static int const SecondCall = 1696;
	static int const PickRange = 1700;
	static int const ContinueSkill = 1704;
	static int const RefreshCheck = 1708;
	static int const SkinView = 1712;
	static int const HonorTag = 1716;
	static int const ManaCost = 1800;
	static int const CWPlayer = 1804;
	static int const SkillsEdit = 1808;
	static int const InventoryCheck = 1812;
	static int const UnGap = 1816;
	static int const DamageAggro = 1820;
	static int const Reborn = 1824;
	static int const EmokTime = 1828;
	static int const EmokDay = 1832;
	static int const EmokEXP = 1836;
	static int const HPx = 1840;
	static int const HKx = 1844;
	static int const DKPTx = 1848;
	static int const DKPWx = 1852;
	static int const PLTx = 1856;
	static int const PLWx = 1860;
	static int const SVWx = 1864;
	static int const RPx = 1868;
	static int const HDx = 1872;
	static int const SVTx = 1876;
	static int const CurrentBReward = 1880;
	static int const MaxBReward = 1884;
	static int const CurrentPBReward = 1888;
	static int const BattlepassLv = 1892;

	static int const MaxSize = 1896;
}

namespace _Window {
	static LRESULT(__stdcall* Proc)(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam) = (LRESULT(__stdcall*)(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam))0x004348E0;
}

namespace AuthSocket {
	static DWORD *Port = (DWORD*)0x4E1168;
}

namespace Timer {
	static DWORD *Second = (DWORD*)0x4DA790;
	static DWORD *Minute = (DWORD*)0x4DA78C;
	static DWORD *Hour = (DWORD*)0x4DA788;
	static DWORD *Day = (DWORD*)0x4DA784;
	static DWORD *Month = (DWORD*)0x4DA780;
	static DWORD *Year = (DWORD*)0x4DA77C;
}

namespace CSkill
{
	static bool(__thiscall *Check1)(void *Skill, int Player, int Target) = (bool(__thiscall*)(void *Skill, int Player, int Target))0x00489A10;
	static bool(__thiscall *Check2)(void *Skill, int Player, int Target) = (bool(__thiscall*)(void *Skill, int Player, int Target))0x0048A560;
	static bool(__thiscall *Check3)(void *Skill, int Player, int Target) = (bool(__thiscall*)(void *Skill, int Player, int Target))0x00480E80;
	static bool(__thiscall *Check4)(void *Skill, int Player, int Target) = (bool(__thiscall*)(void *Skill, int Player, int Target))0x00482570;
	static bool(__thiscall *Check5)(void *Skill, int Player, int Target) = (bool(__thiscall*)(void *Skill, int Player, int Target))0x00485AE0;
	static bool(__thiscall *Check6)(void *Skill, int Player, int Target) = (bool(__thiscall*)(void *Skill, int Player, int Target))0x004863B0;
	static bool(__thiscall *Check7)(void *Skill, int Player, int Target) = (bool(__thiscall*)(void *Skill, int Player, int Target))0x00486860;
	static bool(__thiscall *Check8)(void *Skill, int Player, int Target) = (bool(__thiscall*)(void *Skill, int Player, int Target))0x00486E20;
	static bool(__thiscall *Check9)(void *Skill, int Player, int Target) = (bool(__thiscall*)(void *Skill, int Player, int Target))0x00487900;
	static bool(__thiscall *Check10)(void *Skill, int Player, int Target) = (bool(__thiscall*)(void *Skill, int Player, int Target))0x00487B40;
	static bool(__thiscall *Check11)(void *Skill, int Player, int Target) = (bool(__thiscall*)(void *Skill, int Player, int Target))0x00487CF0;
	static bool(__thiscall *Check12)(void *Skill, int Player, int Target) = (bool(__thiscall*)(void *Skill, int Player, int Target))0x00489550;


	static signed int(__thiscall *LoadInitSkill)(int SkillPointer) = (signed int(__thiscall*)(int))0x0047F1E0;
	static int(__thiscall *MageCalculation)(void* pSkill, int Player, int Target) = (int(__thiscall*)(void*, int, int))0x004833D0;
	static void (__thiscall *Occupation)(void *SkillPointer) = (void (__thiscall*)(void*))0x004800E0;
	static signed int (__thiscall *LearnSkillCheck)(void *SkillPointer, signed int SkillID) = (int (__thiscall*)(void*,int))0x0047FD70;
	static bool (__stdcall *SkillPointers)(int Value, int Argument) = (bool (__stdcall*)(int,int))0x0048D9E0;
	static int (__thiscall *Calculations)(void *pSkill, int Player) = (int (__thiscall*)(void*,int))0x00480F20;
	static int (__thiscall *GetMagic)(void *Object, int Player, char Index, int Argument) = (int (__thiscall*)(void*,int,char,int))0x004856D0;
	static signed int (__thiscall *MagicTick)(void *Monster) = (signed int (__thiscall*)(void*))0x00442030;
	static int (__thiscall *Cure)(void *pSkill, int Player, void *pPacket, int pPos) = (int (__thiscall*)(void*, int, void*, int))0x00485B80;
	static int (__thiscall *GroupCure)(void *pSkill, int Player, int pPacket, int pPos) = (int (__thiscall*)(void*, int, int, int))0x004871C0;
	static void (__thiscall *SkillUp)(void *SkillPointer, signed int SkillID) = (void (__thiscall*)(void*,signed int))0x0047F970; 
	static void(__thiscall *LearnSkillGrade)(void *SkillPointer, signed int SkillID, int Grade) = (void(__thiscall*)(void*, int, int))0x0047FA60;
	static void (__thiscall *LearnSkill)(void *SkillPointer, signed int SkillID) = (void (__thiscall*)(void*,int))0x0047F7A0;
	static int (__thiscall *PrepareSkill)(void *SkillPointer, signed int SkillID, int Argument) = (int (__thiscall*)(void*,signed int,int))0x00480390;
	static void (__thiscall *LifeAbsorption) (void* pSkill, void* pPlayer, char* pPacket, char* pPos) = (void (__thiscall*) (void*, void*, char*, char*))0x00488330;
	static void (__thiscall *SoulDestruction) (void* pSkill, void* pPlayer, char* pPacket, char* pPos) = (void (__thiscall*) (void*, void*, char*, char*))0x00482FA0;
	static int (__thiscall *BlessingOfHealth) (int SkillPointer, int Player, int Target, int Argument) = (int (__thiscall*) (int, int, int,int))0x00489DD0;
	static int (__thiscall *BlessingOfCriticalHit) (int SkillPointer, int Player, int Target, int Argument) = (int (__thiscall*) (int, int, int,int))0x00489F60;
	static int (__thiscall *BlessingOfAgility) (int SkillPointer, int Player, int Target, int Argument) = (int (__thiscall*) (int, int, int,int))0x00489E60;
	static int (__thiscall *BlessingOfStrength) (int SkillPointer, int Player, int Target, int Argument) = (int (__thiscall*) (int, int, int,int))0x00489D90;
	static int (__thiscall *BlessingOfIntelligence) (int SkillPointer, int Player, int Target, int Argument) = (int (__thiscall*) (int, int, int,int))0x00489EE0;
	static void(__thiscall *LongRangeProtectSkill) (void *SkillID, int IPlayer, int Argument, int Value) = (void(__thiscall*)(void*, int, int, int))0x00487EF0;

	static int (__thiscall *ExecuteSkill) (void *SkillPointer, signed int SkillID, int Argument, int Value) = (int (__thiscall*)(void*,signed int,int,int))0x0047FBB0;
	static void (__thiscall *RefiningWeapon) (void* pSkill, void* pPlayer, char* pPacket, char* pPos) = (void (__thiscall*) (void*, void*, char*, char*))0x00488820;
	static void (__thiscall *DefenseImprovement) (void* pSkill, void* pPlayer, char* pPacket, char* pPos) = (void (__thiscall*) (void*, void*, char*, char*))0x004889F0;
	static void (__thiscall *SpeedUp) (void* pSkill, void* pPlayer, char* pPacket, char* pPos) = (void (__thiscall*) (void*, void*, char*, char*))0x00486EC0;
	static int (__thiscall *CheckBuff)(void *Value, int Argument, int Player) = (int (__thiscall*)(void*,int,int))0x00489AA0;
	static LONG (__thiscall* ObjectRelease)(void* pOject, LONG lpAddend) = (LONG (__thiscall*)(void*, LONG))0x004239C0;
	static void (__thiscall *ExecuteTransformSkill)(void *SkillPointer, signed int SkillID, int Argument, int Value) = (void (__thiscall*)(void*,signed int,int,int))0x0047FC90;
	static void(__thiscall *SkillOnLoad)(int pSkill, signed int SkillID, int pPos) = (void(__thiscall*)(int, signed int, int))0x0047F6B0;
	static int(__thiscall *IsSkill)(void* pSkill, int SkillID) = (int(__thiscall*)(void*, int))0x0047F6B0;
	static int (__thiscall* Storm)(void* a, int a2, void* Player, int a4) = (int (__thiscall*)(void*, int, void*, int))0x004854D0;
	static int (__thiscall *Calls)(void *pSkill, int Player, int pPacket, int pPos) = (int (__thiscall*)(void*,int,int,int))0x0048A9A0;
	static int (__thiscall *Behead)(void *pSkill, int Player, void *pPacket, int pPos) = (int (__thiscall*)(void*,int,void*,int))0x004813A0;
}

namespace CConfig
{
	static int(__thiscall *GetToken)(void *File) = (int(__thiscall*)(void*))0x0040BD40;
	static int(__thiscall *GetInt)(char* Var, char* Type, int DefaultValue) = (int(__thiscall*)(char* Var, char* Type, int DefaultValue))0x0040C9A0;
}

namespace CConfigs
{
	static int(__cdecl *Load)() = (int(__cdecl*)())0x0044BEF0;
}

namespace CScreen {
	static void(__cdecl* Add)(int Screen, int nType, const char* format, ...) = (void(__cdecl*)(int, int, const char*, ...))0x0047E320;
	static void(__thiscall* AddString)(int Screen, int nType, const char* string) = (void(__thiscall*)(int, int, const char*))0x0047E3D0;
	static int* color = (int*)0x4D62A0;
}

namespace CIOBuffer
{
	static int(__cdecl *PacketBuilder)(void* Socket, const char* Format, ...) = (int(__cdecl*)(void*,const char*,...))0x00496F10;
	static LONG(__thiscall *Release)(void *Buffer) = (LONG(__thiscall*)(void*))0x00401070;
	static LONG(__thiscall *Free)(void *thispointer) = (LONG(__thiscall*)(void *thispointerpointer))0x00424040;
	static int(__cdecl *Alloc)() = (int(__cdecl*)())0x00423F90;
	static int(__cdecl *CIOBuffer__FreeAll)() = (int(__cdecl*)())0x004240A0;
	static int(__thiscall *sub_496B30)(char a4, int a5, int a6) = (int(__thiscall*)(char a4, int a5, int a6))0x00496B30;
	static signed int(__stdcall *sub_497D5D)(void *a1, void *a2, int a3, void *a4, int a5) = (signed int(__stdcall*)(void *a1, void *a2, int a3, void *a4, int a5))0x00497D5D;
	static void(__thiscall *CSocket___CSocket)(void* player, char* Inv) = (void(__thiscall*)(void* a5,char* Inv))0x004947F0;
}
namespace CIOSocket {
	static void(__thiscall *CIOSocket__Close)(int Socket) = (void(__thiscall*)(int))0x00424260;
	static int(__thiscall *IsSBit)(int Socket, int Value) = (int(__thiscall*)(int, int))0x0040DC60;
	static void(__thiscall *Lock)(int Socket) = (void(__thiscall*)(int))0x004327C0;
	static void(__thiscall *Unlock)(int Socket) = (void(__thiscall*)(int))0x004327E0;
	static void(__thiscall *Enter)(int Socket) = (void(__thiscall*)(int))0x004944F0;
	static int(__thiscall* Create)(int CServerThisPointer, int Socket, int Infos) = (int(__thiscall*)(int, int, int))0x0047E940;
	static void(__thiscall *GraceFulClose)(int Socket) = (void(__thiscall*)(int))0x004242E0;
}
namespace CPacket
{
	static int(__cdecl *xRead)(void *pPacket, const char* Format, ...) = (int(__cdecl*)(void*, const char*, ...))0x00497220;
	static void*(__cdecl *xRead2)(void *pPacket, char Format, ...) = (void*(__cdecl*)(void*, char, ...))0x00497220;
	static int (__cdecl *Read)(char *pPacket, char *pPos, const char *sFormat, ...) = (int (__cdecl*)(char*, char*, const char*, ...))0x004975F0;
}
namespace CMenu
{
	static int(__cdecl *GenerateMenu)(HINSTANCE hInstance, int nCmdShow) = (int(__cdecl*)(HINSTANCE hInstance, int nCmdShow))0x00434790;
}

namespace CChar
{
	static void*(__thiscall *CChar)(void* thispointer) = (void*(__thiscall*)(void* thispointer))0x0040AA10;
	static void*(__thiscall *_CChar)(void* thispointer) = (void*(__thiscall*)(void* thispointer))0x0040ADE0;
	static int (__thiscall *GetDodge)(int Player) = (int (__thiscall*)(int))0x0043DB90;
	static int (__thiscall *GetDex)(int Player) = (int (__thiscall*)(int))0x0043BF20;
	static int (__thiscall *GetMaxMagic)(int Player) = (int (__thiscall*)(int))0x00458240;
	static int (__thiscall *GetMinMagic)(int Player) = (int (__thiscall*)(int))0x00458210;
	static int (__thiscall *GetInt)(int Player) = (int (__thiscall*)(int))0x0043BEA0;
	static int (__thiscall *GetMaxHP)(int Player) = (int (__thiscall*)(int))0x0043A200;
	static int (__thiscall *GetStr)(int Player) = (int (__thiscall*)(int))0x0043BE20;
	static int (__thiscall *GetHit)(int Player) = (int (__thiscall*)(int))0x0043DB60;
	static int (__thiscall *GetMinAttack)(int Player) = (int (__thiscall*)(int))0x0043D9A0;
	static int (__thiscall *IsMStateEx)(int Player, int Buff) = (int (__thiscall*)(int,int))0x00409310;
	static int (__thiscall *GetHth)(int Player) = (int (__thiscall*)(int))0x0043BE60;
	static __int64 (__thiscall *IsBState)(int Object, __int64 Value) = (__int64 (__thiscall*)(int,__int64))0x00409720;
	static void(__thiscall *ResetAllBuff)(int Player) = (void(__thiscall*)(int a2edx))0x0040B920;
	static int (__thiscall *GetWis)(int Player) = (int (__thiscall*)(int))0x0043BEE0;
	static int(__thiscall *GetFatalDamage)(int Player, int Damage, int Argument, int Value) = (int(__thiscall*)(int, int, int, int))0x0043EAC0;
	static int(__thiscall *PerfectCure)(int Player, int a2, int a3) = (int(__thiscall*)(int, int, int))0x00485FA0;
	static int (__thiscall *GetMaxHp)(int Object) = (int (__thiscall*)(int))0x0043A200;
	static int (__thiscall *GetMaxMp)(int Object) = (int (__thiscall*)(int))0x0043AF90;
	static int (__thiscall *IsNormal) (int Object) = (int (__thiscall*) (int))0x0040B280;
	static int (__thiscall *Lock) (void *Object) = (int (__thiscall*) (void*))0x00412E90;
	static int (__thiscall *Unlock) (void *Object) = (int (__thiscall*) (void*))0x00412EB0;
	static int (__cdecl *WriteInSight) (void* pPlayer, BYTE bType, const char *Format, ...) = (int (__cdecl*) (void*, BYTE, const char*, ...))0x0040B9E0;
	static int (__thiscall *IsGState) (int Player, int Argument) = (int (__thiscall*)(int,int))0x0040B310;
	static int (__thiscall *FindBuff)(int Player, int BuffID) = (int (__thiscall*)(int,int))0x0040B4A0;
	static LONG (__thiscall *AddGState) (int Player, int Argument) = (LONG (__thiscall*) (int, int))0x00409910;
	static signed int (__thiscall *GetFinalDamage)(void *Value, int Player, int Damage, int Argument) = (signed int (__thiscall*)(void*,int,int,int))0x0043AD50;
	static void (__cdecl *WriteInRect)(int Player, unsigned char Type, int value, const char* Format, ...) = (void (__cdecl*)(int, unsigned char, int, const char*, ...))0x0040BA70;
	static bool (__thiscall *CheckHit) (void* pPlayer, void* pTarget, int arg) = (bool (__thiscall*) (void*, void*, int))0x0043DA00;
	static int (__thiscall *CancelBuffParty) (void *Player, int BuffID) = (int (__thiscall*)(void*,int))0x0040B870;
	static int (__thiscall *CancelAllBuff)(void *Player, int BuffID) = (int (__thiscall*)(void*,int))0x0040B6A0;
	static int (__thiscall *CancelAllBuff2)(void *Player) = (int (__thiscall*)(void*))0x0040B750;
	static __int64 (__thiscall *IsMState)(int Player, __int64 Argument) = (__int64 (__thiscall*)(int,__int64))0x00406BA0;
	static void (__thiscall *SetDirection)(void *Value, int Player, int Argument) = (void (__thiscall*)(void*,int,int))0x0040B180;
	static int (__thiscall *GetAttack)(void *Object) = (int (__thiscall*)(void*))0x0043D970;
	static unsigned (__thiscall* GetMagic) (void* pPlayer) = (unsigned (__thiscall*) (void*))0x00483230;
	static signed int (__thiscall *GetASpeed)(int Object) = (signed int (__thiscall*)(int))0x0043D8E0;
	static int (__cdecl *GetRange) (int Object, int NextObject) = (int (__cdecl*) (int, int))0x00448870;
	static int (__thiscall *GetAbsorb)(int Object) = ( int (__thiscall*)(int))0x00438F70;
	static int (__thiscall *GetDefense)(void *Value, int Player) = (int (__thiscall*)(void*,int))0x00438F30;
	static int (__thiscall *GetMaxAttack)(int Object) = (int (__thiscall*)(int))0x0043D9D0;
	static int (__thiscall *GetResist)(void* Object, int Type) = (int (__thiscall*)(void*, int))0x00438FA0;
	static int (__thiscall *AddMState)(void *player, int a2, int a3) = (int (__thiscall*)(void*,int,int))0x0043CE00;
	static int (__thiscall *SubMState)(void *player, int a2, int a3) = (int (__thiscall*)(void*,int,int))0x0043CE50;
	static int (__thiscall *SubGState)(int player, int a2) = (int (__thiscall*)(int,int))0x0040AC20;
	static int (__thiscall *SetXY)(int Object, int Tile) = (int (__thiscall*)(int,int))0x0040B110;
	static int (__thiscall *GetBuffRemain)(void *Object, int BuffID) = (int (__thiscall*)(void*,int))0x0040B4E0;
	static int(__thiscall *AddBuff)(int Player, void* Buff) = (int(__thiscall*)(int, void*))0x0040B3D0;
	static void(__thiscall *RefreshBuff)(int Player) = (void(__thiscall*)(int))0x0040B5F0;
	static void(__thiscall *CChar__UpdateBuff)(int Player, int Buff) = (void(__thiscall*)(int Player, int Buff))0x0040B540;
	static void(__thiscall *SetBuff)(int Player,int Buff, int Time) = (void(__thiscall*)(int Player,int Buff, int Time))0x0040B330;
}

namespace CIOCriticalSection
{
	static struct _RTL_CRITICAL_SECTION*(__thiscall *Init)(struct _RTL_CRITICAL_SECTION *thispointer) = (struct _RTL_CRITICAL_SECTION*(__thiscall*)(struct _RTL_CRITICAL_SECTION *thispointerpointer))0x004235E0;
	static struct _RTL_CRITICAL_SECTION*(__thiscall *Delete)(struct _RTL_CRITICAL_SECTION *thispointer) = (struct _RTL_CRITICAL_SECTION*(__thiscall*)(struct _RTL_CRITICAL_SECTION *thispointerpointer))0x00423610;
	static void (__thiscall *Enter)(void *Section) = (void (__thiscall*)(void*))0x00423640;
	static int (__thiscall *Leave)(void *Section) = (int (__thiscall*)(void*))0x004236D0;
}

namespace CItemDefense
{
	static int (__thiscall *SetWearState)(int Item, int Player) = (int (__thiscall*)(int,int))0x0042A800;
	static signed int (__thiscall *StorageIn)(void *Item, int Player, int Argument) = (signed int (__thiscall*)(void*,int,int))0x0042B0F0;
	static char (__thiscall *ApplySpec) (int Item, int Player) = (char (__thiscall*)(int,int))0x0042AAF0;
	static int (__thiscall *PutOn)(int Item, int Player) = (int (__thiscall*)(int ,int))0x0042AC10;
	static int (__thiscall *PutOff)(void *Item, int Player) = (int (__thiscall*)(void*,int))0x0042AD60;
	static signed int (__thiscall *ChangePrefix)(void *Item, int Player, int ID, int Chance, int a5) = (signed int (__thiscall*)(void*,int,int,int,int))0x0042B710;
}

namespace CMonsterReal
{
	static int (__thiscall *Move)(int Monster) = (int (__thiscall*)(int))0x0043DBC0;
	static signed int (__thiscall *GetChasePt)(int Monster, int Argument, int Value) = (signed int (__thiscall*)(int,int,int))0x0043E470;
	static int (__thiscall *AI) (void *Monster) = (int (__thiscall*) (void*))0x0043D060;
	static int (__thiscall *ScanSight) (int Object) = (int (__thiscall*)(int))0x0043E8C0;
	static int (__thiscall *Attack) (int Monster) = (int (__thiscall*)(int))0x0043D510;
	static void (__thiscall *Tick) (void* Monster) = (void (__thiscall*)(void*))0x0043D140;
	static int (__thiscall *AddHostility) (void *Monster, int Player, int mainHost, signed int additionalHost) = (int (__thiscall*)(void*,int, int, signed int))0x0043D210;
	static int (__thiscall *Die) (int mob, int buffIndex, int a3, int a4, int tankerID) = (int (__thiscall*) (int, int, int, int, int))0x00442360;
	static int (__thiscall *AllotExp) (int mob, int a2, int tankerID, int* a4) = (int (__thiscall*) (int, int, int, int*))0x0043ECC0;
	static void *(__thiscall *SendCreate)(void *Monster, int Player, int Argument) = (void *(__thiscall*)(void*, int, int))0x0043AAC0;
}

namespace CInitMonster
{
	static bool (__thiscall *IsRace)(int Object, int Type) = (bool (__thiscall*)(int,int))0x00441570;
	static int (__thiscall *DropItem)(int InitMonster, int Monster, int IsParty, int tankerID, int a5, int a6) = (int (__thiscall*)(int,int, int, int, int, int))0x00437D70;
	static int(__thiscall *Release)(int InitMonster, char Argument) = (int(__thiscall*)(int, char))0x00437260;
	static void(__cdecl *Stop)() = (void(__cdecl*)())0x00439130;
	static void(__cdecl *Start)() = (void(__cdecl*)())0x004390C0;
}

namespace CItemGeneral
{
	static signed int (__thiscall *StorageIn)(int Item, int Player, int Amount) = (signed int (__thiscall*)(int,int,int))0x0042D180;
	static int (__thiscall *Use)(void *Item, int Player) = (int (__thiscall*)(void*,int))0x0042CFB0;
}

namespace CInitItem
{
	static char (__thiscall *ApplySpec)(int Item,int Player) = (char (__thiscall*)(int,int))0x0041ED70;
	static int(__thiscall *Use)(int Item, int Player) = (int(__thiscall*)(int, int))0x0041EE50;
	static int(__thiscall *Open)() = (int(__thiscall*)())0x0041D5E0;
	static int(__thiscall *Close)() = (int(__thiscall*)())0x00426490;
	static int(__thiscall *Copy)() = (int(__thiscall*)())0x0041D690;
	static int(__thiscall *Release)(int InitItem, char Argument) = (int(__thiscall*)(int, char))0x0041D500;
	static int(__thiscall *ReleaseItem)(int InitItem, char Argument) = (int(__thiscall*)(int, char))0x00425A00;
}
namespace CItemStandard
{
	static void (__thiscall *PutOn)(int Item, int Player) = (void (__thiscall*)(int,int))0x0042BF70; 
	static int (__thiscall *Broken)(void* pointer,int a5, int a6) = (int (__thiscall*)(void*,int a5, int a6))0x0042C340;
	static void (__thiscall *PutOff)(void* Item, int Player) = (void (__thiscall*)(void*,int))0x0042C1B0; 
	static char(__thiscall *ApplySpec) (int Item, int Player) = (char(__thiscall*)(int, int))0x0042BEF0;
}

namespace CItem
{
	static LONG (__cdecl *NewIID)() = (LONG (__cdecl*)())0x004273B0;
	static char* (__cdecl *PutByte)(char*, char) = (char* (__cdecl*)(char*, char))0x004189A0;
	static char* (__cdecl *PutWord)(char*, short) = (char* (__cdecl*)(char*, short))0x0042F960;
	static char* (__cdecl *PutDword)(char*, long) = (char* (__cdecl*)(char*, long))0x0044F9b0;
	static int (__thiscall *OnTimer)(int Item, int Value) = (int (__thiscall*)(int,int))0x00426640;
	static int (__cdecl *FindInitItem)(int Index) = (int (__cdecl*)(int))0x00425C60;
	static int (__cdecl *NewItem)(int Value) = (int (__cdecl*)(int))0x00425D00;
	static int (__thiscall *AddGState)(int Object, int Item) = (int (__thiscall*)(int,int))0x004261F0;
	static int (__thiscall *RemoveItem)(void *Player, int Item) = (int (__thiscall*)(void*,int))0x0046F320;
	static signed int (__stdcall *MixItemCheck)(int MainItem, int Weapon, int Armor) = (signed int (__stdcall*)(int,int,int))0x0046EF90;
	static int (__thiscall *ReturnIndex)(int Item) = (int (__thiscall*)(int))0x0046EF70;
	static int (__stdcall *InsertItem)(int Player, int Value, int Index, int Prefix, int Amount, int Argument) = (int (__stdcall*)(int,int,int,int,int,int))0x004274A0;
	static int (__thiscall *GetLevel)(int Item) = (int (__thiscall*)(int))0x004295B0;
	static int (__thiscall *SendItemInfo)(void *Item, int Player, char Argument) = (int (__thiscall*)(void*,int,char))0x00427430;
	static int (__thiscall *IsState)(int Item, int Argument) = (int (__thiscall*)(int,int))0x00427130;
	static int (__thiscall *SubState)(int Item, int Argument) = (int (__thiscall*)(int,int))0x00427B90;
	static int (__cdecl *FindPrefix)(char ID) = (int (__cdecl*)(char))0x00425CB0;
	static int (__cdecl *CreateItem)(int Index, int Prefix, int Value, int Argument) = (int (__cdecl*)(int,int,int,int))0x00426110;
	static int (__thiscall *AddState)(int a, int a2) = (int (__thiscall*)(int,int))0x004261F0;
	static void(__thiscall *InitDrop)(DWORD a1, int a4, int a5, char a6, int a7, int a8, DWORD *a9, int a10) = (void(__thiscall*)(DWORD, int, int, char, int, int, DWORD *, int))0x00437C30;
	static LONG(__thiscall *Drop)(int Item, int a5, int a6, int a7, int a8, int a9, int a10) = (LONG(__thiscall*)(int Item, int a5, int a6, int a7, int a8, int a9, int a10))0x00426D00;
	static int (__thiscall *OutOfInv)(void* Inv, DWORD * Item) = (int (__thiscall*)(void*, DWORD *))0x00470740;
	static int (_cdecl *CreateDropItem)(char Checkc, int Checki) = (int(_cdecl*)(char, int))0x00470740;

}

namespace CConsole
{
	static int (__cdecl *Red)(char *arg0, ...) = (int (__cdecl*)(char*,...))0x004328C0;
	static int (__cdecl *Blue)(char *arg0, ...) = (int (__cdecl*)(char*,...))0x00432860;
	static int (__cdecl *Black)(char *arg0, ...) = (int (__cdecl*)(char*,...))0x00432890;
	static int(__cdecl *Exception)(char *arg0, ...) = (int(__cdecl*)(char*,...))0x00422B30;
}

namespace CPlayer
{
	static BYTE *Name = (BYTE*)0x4B437D;
	static DWORD*(__thiscall *RemoveAllEvents)(void* Player) = (DWORD*(__thiscall*)(void*))0x004655E0;
	static void*(__thiscall *CPlayer)(void* Player, int Socket, int UID, int PID) = (void*(__thiscall*)(void*, int, int, int))0x0044FF20;
	static int(__thiscall *GetPalsyDamage)(int Player, int Target) = (int(__thiscall*)(int, int))0x0046C9F0;
	static int(__thiscall *_MLMFind)(int Player, int Number, int Teacher) = (int(__thiscall*)(int, int, int))0x00466F20;
	static int(__thiscall *FishStart)(int Player, int Argument) = (int(__thiscall*)(int, int))0x0047B0E0;
	static int (__cdecl *UpdatePrtyPer)(int Player, int Type, int InOut, char Amount, int Value) = (int (__cdecl*)(int,int,int,char,int))0x0045B100;
	static int (__thiscall *OutOfInv)(void *Player, int Item) = (int (__thiscall*)(void*,int))0x0046F320;
	static int (__cdecl *UpdatePrtyPt)(int Player, int Type, int InOut, char Amount, int Value) = (int (__cdecl*)(int,int,int,char,int))0x00459840;
	static int (__cdecl *UpdateProperty)(int Player, int Type, int InOut, signed __int64 Exp) = (int (__cdecl*)(int,int,int,signed __int64))0x00458800;
	static int(__thiscall *AddWState)(int Player, char Type) = (int(__thiscall*)(int, char))0x00427BB0;
	static int(__thiscall *AddBState)(int Player, int Buff, int Type, int Time) = (int(__thiscall*)(int, int, int, int))0x00451DE0;
	static int(__thiscall *SubBState)(int Player, int Buff, int Type) = (int(__thiscall*)(int, int, int))0x00451EB0;
	static int(__thiscall *AddEState)(int Player, int Type) = (int(__thiscall*)(int, int))0x00409AF0;
	static size_t (__thiscall *ProcessMsg)(void *Player, char *Msg) = (size_t (__thiscall*)(void*,char*))0x00460A50;
	static int(__cdecl *CountWarrelationPlayer)() = (int(__cdecl*)())0x0046E0D0;
	static void(__thiscall *UpgradeItem)(int Player, char Type, int IID) = (void(__thiscall*)(int Player, char Type, int IID))0x0045E0A0;
	static int (__thiscall *SwitchStall)(void *Player, int Value) = (int (__thiscall*)(void*,int))0x0045F540;
	static void (__thiscall *OnTeleport)(void *Player, int Argument, int Value) = (void (__thiscall*)(void*,int,int))0x0045CE50;
	static int (__thiscall *GameStart)(void *Player) = (int (__thiscall*)(void*))0x00458270;
	static void *(__thiscall *SendCreate)(void *Player, int Object, void *Argument) = (void *(__thiscall*)(void*, int, void*))0x00451390;
	static void *(__thiscall *Send)(int Player, int Packet) = (void *(__thiscall*)(int, int))0x00452E00;
	static void (__thiscall *SendPacket)(int Player, void* Packet) = (void (__thiscall*)(int, void*))0x00450460;
	static int (__thiscall *CheckBlock)(int Player, int Object) = (int (__thiscall*)(int,int))0x00452130;
	static void (__cdecl *WriteInMap)(int Map, unsigned char Type, const char* Format, ...) = (void (__cdecl*)(int, unsigned char, const char*, ...))0x004509F0;
	static int (__cdecl *ScanPlayer)(int PID) = (int (__cdecl*)(int))0x00450790;
	static void(__thiscall *ProcessEvent)(int Player, int Type, char *Packet, unsigned int pPos) = (void(__thiscall*)(int, int, char*, unsigned int))0x00464B40;
	static int (__thiscall *AskPvP)(int a1,int a5) = (int (__thiscall*)(int,int))0x00460300;
	static signed int(__thiscall *_CheckTrade)(int Player) = (signed int(__thiscall*)(int))0x0045E780;
	static void(__thiscall *OnAskPvP)(int Player, int a5, int TargetID) = (void(__thiscall*)(int,int,int))0x004604C0;
	static int(__thiscall *OnAskTrade)(int Player, int a5, int TargetID) = (int(__thiscall*)(int, int, int))0x0045E2F0;
	static int(__thiscall *EndTrade)(int player, int a5) = (int(__thiscall*)(int,int))0x0045E410;
	static void(__thiscall *PKKill)(void*killer , int killed) = (void(__thiscall*)(void*,int))0x0046B0C0;
	static int (__thiscall *EndPvP)(void *Player,int nextPlayer, int a6, int a7, int a8) = (int (__thiscall*)(void*,int,int,int,int))0x00460940; 
	static int (__thiscall *MLMAccumFee)(int Player, int Value) = (int (__thiscall*)(int,int))0x00467400;
	static int (__stdcall *SetEventCode)(signed int a1, int a2) = (int (__stdcall*)(signed int,int))0x0046BFD0;
	static int (__thiscall *GetInvenSize)(int Player) = (int (__thiscall*)(int))0x00456720;
	static int (__thiscall *GetMSpeed)(void *Player, int Value) = (int (__thiscall*)(void*,int))0x00452070;
	static void (__thiscall *DropItem)(int Player, char a2, int a3) = (void (__thiscall*)(int,char,int))0x0045D7E0;
	static void (__thiscall *DropItemONPKDie)(void *Player) = (void (__thiscall*)(void*))0x0046B890;
	static int(__thiscall *GetGuildName)(int Player) = (int(__thiscall*)(int))0x0046ACD0;
	static int(__thiscall *GetGuildClassTitle)(int Player) = (int(__thiscall*)(int))0x0046AD70;
	static int(__thiscall *GetGuild)(int Player) = (int(__thiscall*)(int))0x0046AAD0;
	static signed int (__thiscall *InitStat)(void *Player) = (signed int (__thiscall*)(void*))0x00465250;
	static int (__thiscall *TradeAgreed)(void *Player) = (int (__thiscall*)(void*))0x0045E720;
	static int (__thiscall *CancelTrade)(void *Player) = (int (__thiscall*)(void*))0x0045E3B0;
	static char(__thiscall *TradeItem)(int Player,void *Target) = (char(__thiscall*)(int,void *a5))0x0045E890;
	static int (__thiscall *CutdownExp)(int Player, signed int expLoss) = (int (__thiscall*)(int, signed int))0x004643A0;
	static void (__cdecl *EventBuff)(int ID) = (void (__cdecl*)(int))0x0046B770;
	static signed int (__thiscall *RemoveItem)(void *Player, int Value, int Index, int Amount) = (signed int (__thiscall*)(void*,int,int,int))0x0045DA90;
	static int (__thiscall *BuyItemEx)(void *Player, char Npc, int Tax, int ItemSize, int pPacket, int pPos) = (int (__thiscall*)(void*,char,int,int,int,int))0x0045D2F0;
	static int (__thiscall *Imperial)(void *pPlayer, int MainItem, int Armor, int Stone, int Weapon, int NextStone) = (int (__thiscall*)(void*,int,int,int,int,int))0x0046F350;
	static void (__thiscall *EnforceItem)(void *pPlayer, int MixLevel, int ItemIndex, int DemonSword, int Item, int NextItem, char Stone) = (void (__thiscall*)(void*,int,int,int,int,int,char))0x0046E1B0;
	static int (__thiscall *_OutOfInven)(void *Player,int Item) = (int (__thiscall*)(void*,int))0x0045D140;
	static int(__thiscall *_IntoInven)(void *Player, int Item) = (int(__thiscall*)(void*, int))0x0045D0D0;
	static int (__thiscall *ChatCommand)(int Player, const char *Command) = (int (__thiscall*)(int,const char*))0x00461080;
	static int (__thiscall *RevivalSkill) (void *Player, int Argument, int Target) = (int (__thiscall*) (void*, int, int))0x00464750;
	static signed int (__thiscall *RevivalItem) (void *Player, int Argument) = (signed int (__thiscall*) (void*, int))0x00464950;
	static void (__cdecl *Write)(void *Player, unsigned char Type, const char* Format, ...) = (void (__cdecl*)(void*, unsigned char, const char*, ...))0x00452E60;
	static int (__thiscall *Attack)(void *Player,int Target, int TargetID) = (int (__thiscall*)(void*,int,int))0x0045C740;
	static signed int (__thiscall *Damage)(int Player, int Target, int Damage, int Argument, int Argument1, int Argument2, int Argument3) = (signed int (__thiscall*)(int,int,int,int,int,int,int))0x00451530;
	static int (__thiscall *Rest)(void *Player, int Value) = (int (__thiscall*)(void*,int))0x004642B0;
	static int (__thiscall *IsEState) (int Player, int Argument) = (int (__thiscall*) (int, int))0x0044A510;
	static int (__thiscall *SubEState) (int Player, int Argument) = (int (__thiscall*) (int, int))0x0044A4E0;
	static int (__cdecl *FindPlayerByName)(char Name) = (int (__cdecl*)(char))0x00450890;
	static void(__thiscall *SiegeGunUnset) (int Player, int Type) = (void(__thiscall*) (int, int))0x0046DE50;
	static void* (__cdecl* FindPlayer) (int nID) = (void* (__cdecl*) (int))0x00450810;
	static int (__thiscall *Teleport) (int Player, int Map, int X, int Y, int Z) = (int (__thiscall*) (int, int, int, int, int))0x0045CC90;
	static bool (__thiscall *IsWearBuffStandard)(int Player) = (bool (__thiscall*)(int))0x0046BD80;
	static int (__thiscall *IsWState)(int Player, char Argument) = (int (__thiscall*)(int,char))0x00427BE0;
	static int (__thiscall *SubWState)(int Player, char Argument) = (int (__thiscall*)(int,char))0x00428CD0;
	static int (__thiscall *GetObjectAround)(void *Value, int pPlayer, int Argument) = (int (__thiscall*)(void*,int,int))0x004935A0;
	static int(__thiscall *InsertItem)(void *Player, int Argument, int Item) = (int(__thiscall*)(void*, int, int))0x0045DDC0;
	static int (__thiscall *_InsertItem)(void *Player, int Argument, int Item) = (int (__thiscall*)(void*,int,int))0x0045DE10;
	static char (__thiscall *Process)(void *Player, int Packet, void *Argument, int Value) = ( char (__thiscall*)(void*,int,void*, int))0x00452ED0;
	static void (__thiscall *ShowOffItem)(void *a, int a2, void *a3, int a4) = (void (__thiscall*)(void*,int,void*,int))0x0045E460;
	static int (__thiscall *MAILProcess)(void *a, int a2, int a3, int a4) = (int (__thiscall*)(void*,int,int,int))0x00468890;
	static int (__thiscall *FRDProcess)(void *a, int a2, void *a3, int a4) = (int (__thiscall*)(void*,int,void*,int))0x004675B0;
	static int (__thiscall *LevelUp)(void *Player) = (int (__thiscall*)(void*))0x0045CC00;
	static int (__thiscall *SaveAllProperty)(int Player, int Argument) = (int (__thiscall*)(int,int))0x004586A0;
	static int(__thiscall *UpdatePartyMember)(int Player, int Argument) = (int(__thiscall*)(int, int))0x0045FEB0;
	static int(__thiscall *LevelUpUnknown)(void *Player, int Argument) = (int(__thiscall*)(void*, int))0x0047FF00;
	static int(__thiscall *LoadSkills)(DWORD *Player) = (int(__thiscall*)(DWORD*))0x0047FC00;
	static int (__thiscall *MLMPayMoney)(int Player, int Argument) = (int (__thiscall*)(int,int))0x00467080;
	static int (__thiscall *MLMLevelUp)(void *Player) = (int (__thiscall*)(void*))0x004674D0;
	static int (__thiscall *ExchangeDanjiToItem) (void *Player, int Value, int Argument) = (int (__thiscall*) (void*, int, int))0x0046D570;
	static int (__thiscall *ExchahgeItem) (void *Player, int Argument, int Value, int a4, int Index, int Amount) = (int (__thiscall*)(void*,int,int,int,int,int))0x00456AD0;
	static void (__thiscall *Transform)(void *Player, int Type, signed int Grade) = (void (__thiscall*)(void*,int,signed int))0x0046BA30;
	static void (__thiscall *FreeTransform)(void *Player) = (void (__thiscall*)(void*))0x0046BB90;
	static void(__thiscall *ChangeName)(int Player, char* Name) = (void(__thiscall*)(int, char*))0x0046CEA0;
	static int(__thiscall *Tick)(void *Player) = (int(__thiscall*)(void*))0x00452620;
	static int(__thiscall *AI)(void *Player) = (int(__thiscall*)(void*))0x004514F0;
	static void(__thiscall *OnTimer)(int Timer, int Type) = (void(__thiscall*)(int,int))0x0044FDD0;
	static int(__cdecl* SnowEvent)(int Type) = (int(__cdecl*)(int))0x0046B770;
	static signed int (__thiscall *OnLoadPlayer)(void *Player, int Value) = (signed int (__thiscall*)(void*,int))0x00456C40;
	static int(__thiscall *LeaveParty)(int Player) = (int(__thiscall*)(int))0x0045FD70;
	static signed int (__thiscall *CanAttack)(void *Player, int Target, int Value) = (signed int (__thiscall*)(void*,int,int))0x0046AE50;
	static int (__cdecl *WriteAll)(unsigned char Type, const char* Format, ...) = (int (__cdecl*)(unsigned char, const char*, ...))0x00450910;
	static int(__thiscall *FindItem)(void *Player, int ItemIndex, int Amount) = (int(__thiscall*)(void*, int, int))0x0045D190;
	static int(__thiscall *_FindItem)(int Player, int ItemIndex, int Amount) = (int(__thiscall*)(int, int, int))0x0045D1E0;
	static int (__thiscall* SendMail)(void *Player, int a1, int a2, char* ReceiverName, const char *Message, int a5, int IID, int Index, int Prefix, int Amount, int Price) = (int (__thiscall*)(void*,int, int, char *, const char*, int, int, int, int, int, int))0x00468280;
	static void (__thiscall *Pick)(void* MapObject, int Player, int x, int y) = (void (__thiscall*)(void*,int,int,int))0x004938A0;
	static void(__thiscall *PutOffItem)(int Player, char IID) = (void(__thiscall*)(int, char))0x0045DC50;
	static void(__cdecl *OnDelete)(int Player) = (void(__cdecl*)(int))0x00450E60;
	static int(__thiscall *GameRestart)(int Player) = (int(__thiscall*)(int))0x004585B0;
	static void(__thiscall *SaveQuestFlag)(int Player, int Quest, int Clear) = (void(__thiscall*)(int, int, int))0x0045FF20;
	static bool(__thiscall *CheckQuestFlag)(int Player, int Quest) = (bool(__thiscall*)(int, int))0x004600D0;
	static int(__thiscall *CheckQuestClear)(int Player, char Quest) = (int(__thiscall*)(int, char))0x00460180;

}

namespace CQuest
{
	static char (__thiscall *Run)(void *Quest, int Player) = ( char (__thiscall*)(void*,int))0x0047CEC0;
	static int (__cdecl *FindQuest)(int QuestID) = ( int (__cdecl*)(int))0x0047CAC0;
	static int(__cdecl *Start)(int Quest, int Player) = (int(__cdecl*)(int, int))0x0047CB40;
	static int(__thiscall *Release)(int Quest, char Argument) = (int(__thiscall*)(int, char))0x0044CE50;
	static int(__thiscall *ReleaseAll)() = (int(__thiscall*)())0x0047CA50;
}

namespace CDBSocket 
{
	static int (__cdecl *RealProcess)(char *a1) = (int (__cdecl*)(char*))0x0040CD90;
	static LPVOID (__cdecl *MemoryMalloc)(size_t size) = (LPVOID (__cdecl*)(size_t))0x00401000;
	static int (__cdecl *Write)(unsigned char Type, const char* Format, ...) = (int (__cdecl*)(unsigned char, const char*, ...))0x0040DC80;
	static int (__thiscall *Process)(void *Socket, const char* Data) = (int (__thiscall*)(void*, const char*))0x00494930;
	static int (__cdecl *ProcessHtml)(int a1, char a2, char a3, ...) = (int (__cdecl*)(int,char,char,...))0x004948C0;
}

namespace CParty
{
	static int (__cdecl *FindParty) (int partyID) = (int (__cdecl*)(int))0x0044D4E0;
	static int (__thiscall *GetRandomPlayer) (void *PartyID) = (int (__thiscall*)(void*))0x0044E7C0;
	static int (__thiscall *GetSize) (void *Party) = (int (__thiscall*)(void*))0x00412ED0;
	static int(__thiscall *Join) (int party, int inviter, int joiner) = (int(__thiscall*)(int, int, int))0x0044D9D0;
	static void(__thiscall *Leave) (int party, int player) = (void(__thiscall*)(int, int))0x0044DB20;
	static void(__thiscall *Exile) (int party, int kicker, int player) = (void(__thiscall*)(int, int, int))0x0044DDC0;
	static int (__cdecl *Accept) (int inviter, int joiner) = (int (__cdecl*)(int, int))0x0044D550;
	static void* (__cdecl *CParty) (void *a, int a2) = (void* (__cdecl*)(void*, int))0x0044D3C0;
	static void* (__cdecl *Add) (void *a) = (void* (__cdecl*)(void*))0x0044D7F0;
	static signed int (__thiscall *IsHead) (int a, int a2) = (signed int (__thiscall*)(int, int))0x0044D890;
	static int (__cdecl *Locks) (void *inviter, void *joiner) = (int (__cdecl*)(void*, void*))0x00460490;
	static int (__cdecl *Delocks) (void *inviter, void *joiner) = (int (__cdecl*)(void*, void*))0x0044D620;
	static void* (__cdecl *Unknown1) (size_t a1) = (void* (__cdecl*)(size_t))0x00435820;
	static int(__thiscall *GetPlayerList) (void *Party) = (int(__thiscall*)(void*))0x0044F390;
	static int(__thiscall *_GetPlayerList) (void *Party) = (int(__thiscall*)(void*))0x0044F3D0;
	static int(__thiscall *Chant)(void *Party, int Player, int BuffID) = (int(__thiscall*)(void*, int, int))0x0044F290;
	static int(__thiscall *AllotExp)(int Party, signed int *EXP, int Check, int PlayerX ) = (int(__thiscall*)(int, signed int*, int,int))0x0044E020;
}

namespace CIOServer
{
	static void (__thiscall *Start)(int start,u_short hostshort) = (void (__thiscall*)(int start,u_short))0x00424A40;
}

namespace CItemWeapon
{
	static int (__thiscall *PutOff)(void *Item, int Player) = (int (__thiscall*)(void*,int))0x00428770;
	static int (__thiscall *ApplySpec)(int Item, int Player) = (int (__thiscall*)(int,int))0x00427E70;
	static int (__thiscall *PutOn)(int Item, int Player) = (int (__thiscall*)(int,int))0x00428140;
	static signed int(__thiscall *ChangePrefix)(void *Item, int Player, int Type, int Chance, int Argument) = (signed int(__thiscall*)(void*, int, int, int, int))0x004297B0;
	static signed int(__thiscall *CharmingCheat)(void *Item, int Player, int Type, int Value) = (signed int(__thiscall*)(void*, int, int, int))0x004295F0;
	static signed int(__thiscall *Charming)(void *Item, int Player, int Type) = (signed int(__thiscall*)(void*, int, int))0x00429100;
	static signed int(__thiscall *UpgradeLevel)(void *Item, int Player) = (signed int(__thiscall*)(void*, int))0x00429FB0;
	static void(__thiscall *UpgradeDestroy)(int Item, int Player) = (void(__thiscall*)(int, int))0x00429D50;
	static signed int (__thiscall *StorageIn)(void *Item, int Player, int Argument) = (signed int (__thiscall*)(void*,int,int))0x00428F30;
}

namespace Charming {
	static DWORD *EBMin = (DWORD*)0x004D5E40;
	static DWORD *EBMax = (DWORD*)0x004D5E90;
	static DWORD *XHit = (DWORD*)0x004D5C48;
	static DWORD *XAttack = (DWORD*)0x004D5B88;
	static DWORD *MinStones = (DWORD*)0x004D5F90;
	static DWORD *MaxStones = (DWORD*)0x004D5F38;
}

namespace CPrefix
{
	static char (__thiscall *ApplySpec)(int Item,int Player) = (char (__thiscall*)(int,int))0x0041FA60;
}

namespace CMonster
{
	static DWORD *Amount = (DWORD*)0x4E1810;
	static void (__thiscall *OnDelete)(void *Monster) = (void (__thiscall*)(void*))0x0043a3f0;
	static int (__thiscall *IsRemoved) (void *mID) = (int (__thiscall*) (void*))0x00449450;
	static void* (__cdecl *FindMonster) (int nID) = (void* (__cdecl*) (int))0x0043A240;
	static int (__thiscall *GetObjectAround)(void *Value, int pPlayer, int Argument) = (int (__thiscall*)(void*,int,int))0x004934F0;
	static signed int (__thiscall *CanAttack) (int Monster, int Target, int Value) = (signed int (__thiscall*) (int, int, int))0x0043A770;
	static int (__cdecl *ScanMonster) (int Index) = (int (__cdecl*) (int))0x0043A350;
	static signed int(__cdecl *Create)(int a1, int a2) = (signed int(__cdecl*)(int a1, int a2))0x00439FB0;
	static void *(__thiscall *SendCreate)(void *Monster, int Player, int Argument) = (void *(__thiscall*)(void*, int, int))0x0043A4D0;
	static unsigned long(__thiscall *GetGuildName)(void *Monster) = (unsigned long(__thiscall*)(void*))0x00438eb0;
	static char* (__cdecl *NewMonster)(int InitMonster, int GenMonster) = (char* (__cdecl*)(int, int))0x00439200;
	static int(__thiscall *SetProperty)(void* thisMonster, void* thisInitMonster) = (int(__thiscall*)(void*, void*))0x0043CEA0;
	static LONG(__thiscall *AddMonster)(void* thisMonster, int a5) = (LONG(__thiscall*)(void*, int))0x0043CFA0;
	static unsigned long(__thiscall *GetOperatorName)(void *Monster) = (unsigned long(__thiscall*)(void*))0x0043a720;
	static int(__thiscall *SetTarget)(int Monster, int Player) = (int(__thiscall*)(int, int))0x0043A590;
}

namespace CConsolef
{
	static int (__cdecl *Red)(char *arg0, ...) = (int (__cdecl*)(char*,...))0x004328C0;
	static int (__cdecl *Blue)(char *arg0, ...) = (int (__cdecl*)(char*,...))0x00432860;
	static int (__cdecl *Black)(char *arg0, ...) = (int (__cdecl*)(char*,...))0x00432890;
	static BOOL (__cdecl *Status)() = (BOOL (__cdecl*)())0x004961B0;
}

namespace CBuff
{
	static int(__thiscall *CBuffAttack)(int Skill, int a2) = (int(__thiscall*)(int, int))0x0048ADA0;
	static void *(__thiscall *CBuffExpire)(void *Check, int BuffID, int Time, int Value, int Argument, int Val, int Arg) = (void *(__thiscall*)(void*,int,int,int,int,int,int))0x004064F0;
	static int (__cdecl *CreateBuff)(int BuffID, __int32 Time, int Stat, int Object) = (int (__cdecl*)(int,__int32,int,int))0x00402610;
	static void *(__cdecl *CheckBuffCreate)(size_t Check) = (void *(__cdecl*)(size_t))0x00401000;
	static int (__thiscall *CBuffRemainPrty)(void *Check, int BuffID, int Time, int Type, int Stat, int Argument, int Value) = (int (__thiscall*)(void*,int,int,int,int,int,int))0x00406770;
	static int (__thiscall *CBuffPrtyEx)(void *Check, int BuffID, int Time, int Type, int Stat, int Argument, int Value, int nType, int bType, int cType) = (int (__thiscall*)(void*,int,int,int,int,int,int,int,int,int))0x00406490;
	static int (__thiscall *CBuffPrtyExIsExpired)(int Buff, int Player) = (int (__thiscall*)(int,int))0x00409480;
	static void *(__thiscall *Release)(void *Buff, char Argument) = (void *(__thiscall*)(void*, char))0x004025C0;
	static signed int(__thiscall *UpdateBuff)(int a2, int a3) = (signed int(__thiscall*)(int a2, int a3))0x00402580;
	static signed int(__thiscall *CBuffRemainCount__UpdateBuff)(int Buff, int Buff2, int Player) = (signed int(__thiscall*)(int Buff,int Buff2, int Player))0x00409C80;
	static bool(__thiscall *IsExpired)(void *thispointer, int a2) = (bool(__thiscall*)(void *thispointerpointer, int a2))0x00406990;
}

namespace CBase
{
	static int (__thiscall *IsDeleted)(int Object) = (int (__thiscall*)(int))0x0040B2F0;
	static int(__thiscall *Delete)(void *Object) = (int(__thiscall*)(void*))0x00411780;
	static int(__thiscall *Next)(int Object) = (int(__thiscall*)(int))0x0043E420;
	static int(__thiscall *OnDelete)(void *Object) = (int(__thiscall*)(void*))0x00402180;
	static int(__thiscall *CBase)(void* thispointer) = (int(__thiscall*)(void* thispointer))0x00402110;
}

namespace CBaseList
{
	static int(__thiscall *Push)(void *Object, int Value) = (int(__thiscall*)(void*, int))0x004023F0;
	static int(__thiscall *Pop)(void *Object) = (int(__thiscall*)(void*))0x00402430;
	static int(__thiscall *Offset)(void *Object) = (int(__thiscall*)(void*))0x0042F830;
}

namespace CLink
{
	static void* (__thiscall *MoveTo)(void *Value, int Argument) = (void* (__thiscall*)(void*,int))0x00438C40;
}

namespace CSMap
{
	static int (__stdcall *IsValidTile)(int X, int Argument) = (int (__stdcall*)(int,int))0x00438130;
	static int(__thiscall *IsOnTile)(void *Map, int CoordinateX, int Argument) = (int(__thiscall*)(void*, int, int))0x0045CD80;
	static unsigned long(__thiscall *GetCellMap)(void *_this, void*, void* point) = (unsigned long(__thiscall*)(void*, void*, void*))0x00491360;
}

namespace CCellMap
{
	static int(__thiscall *GetTile)(int Map, int Type) = (int(__thiscall*)(int, int))0x00438220;
}

namespace CSellMap
{
	static void(__thiscall *SendPacket)(void *Map, int Tile, int Packet) = (void(__thiscall*)(void*, int, int))0x00490990;
	static int(__thiscall *SendCreate)(char *Map, int Player, int Tile, int Packet) = (int(__thiscall*)(char*, int, int, int))0x00493390;
}

namespace CIOObject
{
	static int(__thiscall* _Release)(void* pOject, volatile LONG* lpAddend) = (int(__thiscall*)(void*, volatile LONG*))0x004239C0;
	static int (__thiscall *Release)(void *Object) = (int (__thiscall*)(void*))0x00401DE0;
	static LONG(__thiscall *AddRef)(int Object) = (LONG(__thiscall*)(int))0x004010D0;
	static LONG(__thiscall *_AddRef)(int Object, volatile LONG *lpAddend) = (LONG(__thiscall*)(int, volatile LONG*))0x00423980;
	static int(__thiscall *CIOObject)(int Object) = (int(__thiscall*)(int))0x00401FA0;
	static int(__thiscall *AddTimer)(int Object, int Time, int Argument) = (int(__thiscall*)(int, int, int))0x00423B40;
}

namespace CItemOrnament
{
	static int (__thiscall *SetWearState)(int Item, int Player) = (int (__thiscall*)(int,int))0x0042C4B0;
	static signed int (__thiscall *StorageIn)(int Item, int Player, int Value) = (signed int (__thiscall*)(int,int,int))0x0042CB80;
	static int (__thiscall *PutOff)(void *Item, int Player) = (int (__thiscall*)(void*,int))0x0042C870;
	static char (__thiscall *ApplySpec)(void *Item, int Player) = (char (__thiscall*)(void*,int))0x0042C6E0;
	static int (__thiscall *PutOn)(int Item, int Player) = (int (__thiscall*)(int,int))0x0042C760;
	static void *(__thiscall *CItemOrnament)(void *Pointer, int Value) = (void *(__thiscall*)(void*,int))0x0042C450;
	static signed int (__thiscall *ChangePrefix)(void *Item, int Player, int Type, int Chance, int Argument) = (signed int (__thiscall*)(void*,int,int,int,int))0x0042CD20;
}

namespace CTools
{
	static unsigned int(__cdecl *Rate)(unsigned int Value, signed int Argument) = (unsigned int(__cdecl*)(unsigned int, signed int))0x00406E10;
	static int(__cdecl *LvlDiff)(int MobLevel, int PlayerLevel) = (int(__cdecl*)(int, int))0x0044FD40;
	static int(__thiscall *DropLvlDiff)(void* _this, int Monster, int Level) = (int(__thiscall*)(void*, int, int))0x004833D0;
}

namespace CItemTransform
{
	static int (__thiscall *SaveInfo)(int Argument, int Value) = (int (__thiscall*)(int,int))0x0042F2C0;
	static int (__thiscall *PutOn)(int Item, int Player) = (int (__thiscall*)(int,int))0x0042EAE0;
	static int (__thiscall *ApplySpec)(void *Item, int Player) = (int (__thiscall*)(void*,int))0x0042EA00;
	static int (__thiscall *FreeSpec)(void *Item, int Player) = (int (__thiscall*)(void*,int))0x0042EA70;
	static int (__thiscall *ApplyTransform)(int Type, int Player, signed int Grade) = (int (__thiscall*)(int,int,signed int))0x0042F300;
	static int (__thiscall *UpdateExp)(int PlayerEgg, int Player, int Check) = (int (__thiscall*)(int,int,int))0x0042F030;
}

namespace Undefined
{
	static int (__thiscall *ForPortalCheck)(void *Value, int Player) = (int (__thiscall*)(void*,int))0x00496520;
	static int (__thiscall *CreateSkillValue)(void *a, int a2, int a3) = (int (__thiscall*)(void*,int,int))0x00446130;
	static int (__thiscall *CheckSkillValue)(void *a, int a2, int a3) = (int (__thiscall*)(void*,int,int))0x0047F910;
	static void *(__thiscall *CheckSkillX)(void *a) = (void *(__thiscall*)(void*))0x0047F760;
	static int (__thiscall *CheckSkillY)(int a, int a2, int a3) = (int (__thiscall*)(int,int,int))0x0047F780;
	static int (__thiscall *CreateMonsterValueNew)(void *a, int a2, int a3) = (int (__thiscall*)(void*,int,int))0x00433170;
	static int (__cdecl *NewGetItem)(int a1, int a2) = (int (__cdecl*)(int,int))0x00426060;
	static int (__cdecl *DeleteSkill)(int SkillPointer) = (int (__cdecl*)(int))0x00401020;
	static int (__cdecl *Login)(char a1, char a2, ...) = (int (__cdecl*)(char,char,...))0x00401E00;
	static signed int (__stdcall *CheckID)(int *ID) = (signed int (__stdcall*)(int*))0x00494230;
	static signed int (__fastcall *LoginSuccess)(signed __int32 *a1, unsigned int a2) = (signed int (__fastcall*)(signed __int32 *,unsigned int))0x00496CD0;
	static int (__thiscall *StoneOfChance)(void *pSkill, signed int SkillID) = (int (__thiscall*)(void*,signed int))0x00480240;
	static LONG (__thiscall *ForKick)(void *Object, int Value) = (LONG (__thiscall*)(void*,int))0x00495B20;
	static bool (__thiscall *CheckValues)(void *Argument, int Value) = (bool (__thiscall*)(void*,int))0x0047D070;
	static int (__cdecl *MapCheck)(signed int a1) = (int (__cdecl*)(signed int))0x00491080;
	static int (__cdecl *GetMonsterValue)(size_t Argument) = (int (__cdecl*)(size_t))0x00401000;
	static signed int (__thiscall *CellMapCheck)(void *a, int a2, int a3) = (int (__thiscall*)(void*,int,int))0x00491360;
	static void* (__thiscall *MonsterCreate)(void *a) = (void* (__thiscall*)(void*))0x00442DF0;
	static int (__thiscall *CreateMonsterValue)(void *a, int a2, int a3) = (int (__thiscall*)(void*,int,int))0x0044AE20;
	static int (__thiscall *Check)(int a, int a2) = (int (__thiscall*)(int,int))0x00430C20;
	static int (__thiscall *GetValue)(void *a) = (int (__thiscall*)(void*))0x00420250;
	static signed int (__thiscall *MonsterPath)(void *Map, int Object, signed int AddX, signed int AddY, int Value, int Argument) = (signed int (__thiscall*)(void*,int,signed int,signed int,int,int))0x004925C0;
	static int (__cdecl *CalcRange)(int a1, int a2) = (int (__cdecl*)(int, int))0x00448870;
	static int (__cdecl *Blob)(int a1, int a2) = (int (__cdecl*)(int,int))0x0043D870;
	static int (__thiscall *sub_40F070)(void *a, int a2) = (int (__thiscall*)(void*, int))0x0040F070;
	static int (__thiscall *sub_430C20)(int a, int *a2) = (int (__thiscall*)(int, int*))0x00430C20;
	static int(__thiscall *sub_420250)(void *a) = (int(__thiscall*)(void*))0x00420250;
	static int(__thiscall *sub_446090)(void *Player, char *a2, int a3) = (int(__thiscall*)(void*, char*,int))0x00446090;
	static unsigned __int32(__thiscall *sub_47E080)(volatile LONG* a1) = (unsigned __int32(__thiscall*)(volatile LONG*))0x0047E080;
}

namespace CMonsterMaguniMaster
{
	static int(__thiscall *AI)(void *Monster) = (int(__thiscall*)(void*))0x00440550;
	static int(__thiscall *Tick)(void *Monster) = (int(__thiscall*)(void*))0x00442E10;
	static int(__thiscall *Die)(int a, int b, int c, int d, int e) = (int(__thiscall*)(int, int, int, int, int))0x00444560;
}


namespace CMonsterMaguni
{
	static int(__thiscall *Die)(int a, int b, int c, int d, int e) = (int(__thiscall*)(int, int, int, int, int))0x0043F3D0;
}

namespace CNPCSiegeGun
{
	static int(__thiscall *Reply)(int NPC, int Player) = (int(__thiscall*)(int, int))0x00449D80;
}

namespace CNPC
{
	static void(__thiscall *SendCreate)(int NPC, int Player, int Argument) = (void(__thiscall*)(int, int, int))0x004491B0;
	static void(__thiscall *SendDelete)(int NPC, int Player, int Argument) = (void(__thiscall*)(int, int, int))0x00449180;
	static int(__thiscall *Remove)(int Npc) = (int(__thiscall*)(int))0x00449400;

	static int(__cdecl *FindNPC)(char Npc) = (int(__cdecl*)(char))0x00448FA0;
	static int(__cdecl *OpenNPC)(char ID, int Player) = (int(__cdecl*)(char, int))0x004490A0;
	static int(__thiscall *OnDelete)(int Npc) = (int(__thiscall*)(int))0x00449130;
	static int(__thiscall *Start)() = (int(__thiscall*)())0x00448F10;
	static int(__thiscall *GenClose)() = (int(__thiscall*)())0x00447FB0;
	static int(__cdecl *InitClose)() = (int(__cdecl*)())0x00447C90;

	static int(__thiscall *Release)(int NPC, char Argument) = (int(__thiscall*)(int, char))0x00447C40;
	static int(__thiscall *ReleaseNPC)(int NPC, char Argument) = (int(__thiscall*)(int, char))0x004488E0;

	static int(__thiscall *ReleaseGen)(int NPC, char Argument) = (int(__thiscall*)(int, char))0x00447F60;
}

namespace CAlliance
{
	static int(__cdecl *Expire)(int Time) = (int(__cdecl*)(int))0x00419470;
}

namespace CCastle
{
	static int(__cdecl *WarBegin)(int Time) = (int(__cdecl*)(int))0x00419E10;
	static int(__cdecl *Stop)() = (int(__cdecl*)())0x00419AB0;
	static int(__cdecl *Start)() = (int(__cdecl*)())0x00419A60;
	static int (__thiscall *WarEnd)(void *Value) = (int (__thiscall*)(void*))0x0041BEE0;
	static int (__cdecl *GetMonsterTile2CID)(int a1, int a2, int a3) = (int (__cdecl*)(int,int,int))0x0041A400;
	static signed int (__cdecl *IsAllCastleWarRelation)(int Check) = (signed int (__cdecl*)(int))0x0041A670;
	static int (__cdecl *GetCastle)(char Castle) = (int (__cdecl*)(char))0x0041A3B0;
	static int (__thiscall *GetTaxRate)(void *Tax) = (int (__thiscall*)(void*))0x0041B610;
	static int (__thiscall *IsPayment)(void *Castle) = (int (__thiscall*)(void*))0x0041B690;
	static int (__thiscall *AddTax)(void *Castle, int Price) = (int (__thiscall*)(void*,int))0x0041B700;
}

namespace CGuild
{
	static int(__thiscall *BroadcastLock)(void* Guild, void* Packet, int Size) = (int(__thiscall*)(void*, void*, int))0x00416CB0;
	static int(__cdecl *BrokenStandard)(int a1) = (int(__cdecl*)(int))0x00417BA0;
	static int (__cdecl *BrokenGate)(int a1, int a2) = (int (__cdecl*)(int,int))0x00417BE0;
	static LONG(__cdecl *SendPlayerSight)(int Player, void* Packet, int Sight) = (LONG(__cdecl*)(int, void*, int))0x00416D70;
	static bool(__cdecl *IsWarringPeriod)() = (bool(__cdecl*)())0x00417450;
	static time_t(__cdecl *GetWarEndTime)() = (time_t(__cdecl*)())0x00417470;
	static LONG(__thiscall *CriticalSectionEnter)(volatile LONG* value) = (LONG(__thiscall*)(volatile LONG*))0x0047DE70;
	static LONG(__thiscall *CriticalSectionLeave)(volatile LONG* value) = (LONG(__thiscall*)(volatile LONG*))0x0047E080;
}

namespace CLog
{
	static bool (__cdecl *AddV)(signed int Value, const char *Msg, va_list Argument) = (bool (__cdecl*)(signed int, const char*, va_list))0x00432530;
}

namespace CMonsterGuildWar
{
	static signed int(__thiscall *Damage)(void *Target, int Player, int Damage, int Arg, int Val, int Value, int Argument) = (signed int(__thiscall*)(void*, int, int, int, int, int, int))0x00441590;
	static signed int(__cdecl *Create)(char Index, char Map, int XY, int Direction, int GID, char *GuildName, int Type) = (signed int(__cdecl*)(char Index, char Map, int XY, int Direction, int GID, char *GuildName, int Type))0x004412B0;
}

namespace CCalendar
{
	static void(__thiscall *OnTimer)(void *Value, int Argument) = (void(__thiscall*)(void*, int))0x0040A750;
}

namespace CGenMonster
{
	static void(__thiscall *OnTimer)(void* Value, int Argument) = (void(__thiscall*)(void*, int))0x00438770;

	static int(__thiscall *Release)(int GenMonster, char Argument) = (int(__thiscall*)(int, char))0x00438370;

	static int(__thiscall *Stop)() = (int(__thiscall*)())0x00438950;
}

namespace CItemMoney
{
	static signed int(__thiscall *StorageIn)(int Item, int Player, int Amount) = (signed int(__thiscall*)(int, int, int))0x0042E080;
	//new
	static signed int(__thiscall *Drop)(int Item, int a5, int a6, int a7, int a8, int a9, int PlayerID) = (signed int(__thiscall*)(int, int, int, int, int, int, int))0x0042DD20;
	//endnew
}

namespace Unnamed {
	static char* (__cdecl* WritePacket)(char* p, const char* format, ...) = (char* (__cdecl*)(char* p, const char* format, ...))0x496F10;
	static int(__thiscall* CMapObject_GetState)(int Object) = (int(__thiscall*)(int))0x493EB0;
	static signed int(__fastcall* sub_496CD0)(volatile signed __int32* a1, unsigned int a2) = (signed int(__fastcall*)(volatile signed __int32* a1, unsigned int a2))0x496CD0;
	static void(__cdecl* EBREAK)() = (void(__cdecl*)())0x422D80;
	//static DWORD*(__stdcall* sub_496B90)(int _this, DWORD *a2, int a3) = (DWORD*(__stdcall*)(int _this, DWORD *a2, int a3))0x496B90;
	static DWORD* (__thiscall* sub_446090)(int _this, int a2, int a3) = (DWORD * (__thiscall*)(int _this, int a2, int a3))0x446090;

	static DWORD* (__thiscall* sub_446000)(void* ptr) = (DWORD * (__thiscall*)(void*))0x446000;
	static DWORD* (__thiscall* sub_47E1C0)(int _this) = (DWORD * (__thiscall*)(int))0x47E1C0;

	static signed int(__thiscall* Interlocked_bit_test_and_reset)(volatile signed __int32* a1, unsigned int a2) = (signed int(__thiscall*)(volatile signed __int32* a1, unsigned int a2))0x496CE0;
	static int(__cdecl* CreateObject)(size_t Value) = (int(__cdecl*)(size_t))0x00401000;
	static int(__thiscall* CreateObjectValue)(int Object, int ReturnValue, int ObjectData) = (int(__thiscall*)(int, int, int))0x0044AE20;
	static int(__thiscall* CompareObjectValue)(int Object, int ReturnValue) = (int(__thiscall*)(int, int))0x00430C20;
	static int(__thiscall* nGetObject)(int Object_Value, int Object) = (int(__thiscall*)(int, int))0x0040F070;
	static int(__thiscall* GetOffset)(int Object) = (int(__thiscall*)(int))0x00420250;
	static BOOL(__thiscall* CompareValues)(int Object, int CompareObject) = (BOOL(__thiscall*)(int, int))0x0047D070;
	static BOOL(__thiscall* CSMap_Coordinates_Check)(int Player320, int Object, int CSMap) = (BOOL(__thiscall*)(int, int, int))0x00491360;

	static int(__thiscall* sub_40F040)(int Object) = (int(__thiscall*)(int))0x0040F040;
	static void(__thiscall* sub_40EFA0)(int Object44, int NewValue) = (void(__thiscall*)(int, int))0x0040EFA0;
	static void(__thiscall* sub_445BF0)(int Object) = (void(__thiscall*)(int))0x00445BF0;
	static void(__thiscall* SHOWOFFITEM)(int Object, int IID) = (void(__thiscall*)(int, int))0x004707D0;

	static const char* (__thiscall* sub_4023A0)(int Value, int ObjectValue) = (const char* (__thiscall*)(int, int))0x004023A0;
	static int(__thiscall* sub_40C8D0)(const char* Name) = (int(__thiscall*)(const char*))0x0040C8D0;
	static char* (__cdecl* sub_432EF0)(char Name) = (char* (__cdecl*)(char))0x00432EF0;
	static char* (__cdecl* sub_44C550)(char Name) = (char* (__cdecl*)(char))0x0044C550;
	static volatile LONG* (__thiscall* sub_47E0D0)(int ptr) = (volatile LONG * (__thiscall*)(int))0x0047E0D0;

	static void(__thiscall* sub_493440)(void* _this, int a2, int Packet, int a4) = (void(__thiscall*)(void*, int, int, int))0x00493440;
	static int(__thiscall* CheckItemOut)(int nItem1068, int nItemInvertIID) = (int(__thiscall*)(int, int))0x00470740;
}
namespace CObjectDB {
	static BOOL(__thiscall* Open)(int CObjectDB, LPCSTR szFileName) = (BOOL(__thiscall*)(int CObjectDB, LPCSTR szFileName))0x0044C300;
}

namespace CMonsterInvaderBoss
{
	static void (__thiscall *AI)(void *Monster) = (void (__thiscall*)(void*))0x004457F0;
}

namespace CMonsterMaguniWithSkillOnly
{
	static void (__thiscall *AI)(void *Monster) = (void (__thiscall*)(void*))0x0043F4E0;
}

namespace CMonsterMaguniWithSkill
{
	static void (__thiscall *AI)(void *Monster) = (void (__thiscall*)(void*))0x0043F8E0;
}

namespace CMonsterSiegeGunBall
{
	static void (__thiscall *AI)(void *Monster) = (void (__thiscall*)(void*))0x004453B0;
}

namespace CMonsterSiegeGunRuins
{
	static void (__thiscall *AI)(void *Monster) = (void (__thiscall*)(void*))0x00442730;
}

namespace CMonsterSiegeGun
{
	static void(__thiscall *AI)(void *Monster) = (void(__thiscall*)(void*))0x00444A10;
	static void*(__thiscall *CMonsterSiegeGun)(void *Monster, int a2, int a3, int a4, char *a5, int a6) = (void*(__thiscall*)(void *Monster, int a2, int a3, int a4, char *a5, int a6))0x004446D0;
}

namespace CMonsterMagic
{
	static int (__cdecl *Create)(int Index, int Value, int Argument, int Arg, int Player, int Damage, int Time) = (int (__cdecl*)(int,int,int,int,int,int,int))0x00441DE0;
}

namespace CNPCDoor
{
	static int (__thiscall *Tick)(void *NPC) = (int (__thiscall*)(void*))0x00449BF0;
}

namespace CBuffPrtyEx
{
	static int (__thiscall *FreeBuff)(int a, int Player) = (int (__thiscall*)(int,int))0x00409230;
}

namespace CPortal
{
	static int (__cdecl *OpenPortal)(int Player) = (int (__cdecl*)(int))0x0040EC70;
}

namespace CTrade
{
	static int (__thiscall *GetOther)(int TradeID, int Player) = (int (__thiscall*)(int,int))0x0045E6E0;
	static int (__thiscall *IsEnd)(int TradeID) = (int (__thiscall*)(int))0x0045E6C0;
}

namespace CObject
{
	static int(__cdecl *WriteExclusive)(unsigned char Type, const char* Format, ...) = (int(__cdecl*)(unsigned char, const char*, ...))0x0044fce0;
}