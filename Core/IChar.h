#include <iostream>
#include <windows.h>
#include "Sha256.h"
#include <map>
extern int maxAllowedSpeed;

class IChar
{

public:
	void* Offset;

public:
	IChar()
	{
	}

	IChar(void* Object);
	virtual ~IChar();
	int UpdateProperty(int Type, int Amount);
	void Command(const char *command);
	void *GetOffset();
	int IsOnline();
	void Announcement(std::string msg, int color);
	void SystemMessage(std::string msg, int color);
	void PlayerMessage(char* MessageName, char* PlayerMessage);

	int Buff(int id, int time, int value);
	int _Buff(int id, int time, int value);
	int GetAdmin();
	signed __int64 GetEXP();
	signed __int64 GetOldEXP();
	bool IsHide();
	int GetMinPhyAttack();
	int GetPhyAtk();
	int GetMagAtk();
	int GetMaxPhyAttack();
	int GetMinMagAttack();
	int GetMaxMagAttack();
	int UpdateBuff(int BuffID, int Time, int Value);
	int _UpdateBuff(int BuffID, int Time, int Value);
	void SaveBuff(int BuffID,int Time);
	void SaveBuff(int BuffID, int Time, int Value, int SBName, int SBKey);
	void UpdateSavedBuff(int BuffID, int Time, int Value, int SBName, int SBKey);
	void RemoveSavedBuff(int BuffID);
	void AddFire_Resistance(int amount);
	void RemoveFire_Resistance(int amount);
	void AddIce_Resistance(int amount);
	void RemoveIce_Resistance(int amount);
	void AddLightning_Resistance(int amount);
	void RemoveLightning_Resistance(int amount);
	void AddHousePoints(int amount);

	void AddHousePlayers(int amount);
	int GetX();
	int GetY();
	int GetZ();
	int GetDirection();
	int GetMap();
	int GetMapX();
	int GetMapY();
	int GetMapIndex();
	void Teleport(int Map, int X, int Y);
	void Teleport(int Map, int X, int Y, int Z);
	void _Teleport(int Map, int X, int Y);
	void Kick();
	void SetX(int Value);
	void SetY(int Value);
	void SetZ(int Value);
	int IsValid();
	int IsParty();
	int GetPartyID();
	int GetID();
	int GetUID();
	int GetPID();
	int GetCurHp();
	int GetCurMp();
	void DecreaseMana(int amount);
	void IncreaseMana(int amount);
	void IncreaseResist(int amount);
	void DecreaseResist(int amount);
	int GetType();
	void _ShowBattleAnimation(IChar Target, int skillID, int SkillGrade = 1);
	int GetClass();
	int GetTransformGrade();
	void CancelBuff(int BuffID);
	void _CancelBuff(int BuffID);
	int IsBuff(int id);
	bool isMuted();
	void setMuted(int time);
	bool isRidingMode();
	bool isPortalMode();
	int _IsBuff(int id);
	int GetLevel();
	int GetDamage(int SkillID,void* Target);
	void BoxMsg(std::string msg);
	const char *GetName();
	int GetSkillPointer(int SkillID);
	int IsShopping();
	int IsTransform();
	int IsFishing();
	int ScaniaTimer(int amount);
	void AddMinAttack(int amount);
	void RemoveMinAttack(int amount);
	void AddMaxAttack(int amount);
	void RemoveMaxAttack(int amount);
	void DecreaseMaxHp(int amount);
	void IncreaseMaxHp(int amount);
	void DecreaseMaxMp(int amount);
	void IncreaseMaxMp(int amount);
	void AddHp(int amount);
	void RemoveHp(int amount);
	void AddStr(int amount);
	void RemoveStr(int amount);
	void AddInt(int amount);
	void RemoveInt(int amount);
	void AddWis(int amount);
	void RemoveWis(int amount);
	void AddAgi(int amount);
	void RemoveAgi(int amount);
	void AddOTP(int amount);
	void RemoveOTP(int amount);
	void AddEva(int amount);
	void RemoveEva(int amount);
	void AddDef(int amount);
	void RemoveDef(int amount);
	void AddFxToTarget(std::string effectName, bool AutoRemove, bool Continues, bool nForced);
	void AddFxToBone(std::string effectName, int Type);
	void RemoveFxBone(std::string effectName);
	void _AddFxToTarget(std::string effectName, bool AutoRemove, bool Continues, bool nForced);
	void AddParticle(int Bone, const char *ParticleName);
	void AddParticleE(std::string effectName, int Type);

	int GetSpecialty();
	int IsMobMoving();
	int IsMobAggressive();
	int GetMobIndex();
	int GetMobArea();
	int IsMobHaveTarget();
	void SetMobTarget(int target);
	DWORD MobUnAttack(DWORD amount);
	DWORD MobDelay(DWORD amount);
	void MobDelete();
	void Blob();
	void Rb(int time);
	void UpdateHonor(int HP, int HK, int HD, int DKPT, int DKPW, int PLT, int PLW, int SVT, int SVW, int RP);
	void ChangeHonor(int HP, int HK, int HD, int DKPT, int DKPW, int PLT, int PLW, int SVT, int SVW, int RP);
	void ShowHonor(int HP, int HK, int HD, int DKPT, int DKPW, int PLT, int PLW, int SVT, int SVW, int RP, int ToAll);
	void ShowHonor();
	int GetHonorTag();
	int isSkinView();
	void setSkinView(int value);
	void SetProperty(const int& Property, const int& Value);
	void AddProperty(const int& Property, const int& Value);
	void RemoveProperty(const int& Property, const int& Value);
	void IncrProperty(const int& Property);
	void DecrProperty(const int& Property);
	int GetProperty(const int& Property);
	void UpdateHonorTag(int HP);
	void SetHonor(int HP, int RP, int HD, int DKPT, int DKPW, int PLT, int PLW, int SVT, int SVW, int HK);
	void _SetHonor(int HP, int RP, int HD, int DKPT, int DKPW, int PLT, int PLW, int SVT, int SVW, int HK);
	int IsWarRelated();
	void SetBuffIcon(int Time,int Type,int nMsg,int Key);
	void RemoveBuffIcon(int Time,int Type,int nMsg,int Key);
	int GetBuffRemain(int BuffID);
	int _GetBuffRemain(int BuffID);
	int GetSkillPoint();
	void RemoveSkillPoint(int amount);
	void AddSkillPoint(int amount);
	int GetStatPoint();
	void AddStatPoint(int Amount);
	void RemoveStatPoint(int Amount);
	void IncreaseStat(int amount, int Type);
	void DecreaseStat(int amount, int Type);
	int GetStr();
	int GetHth();
	int GetInt();
	int GetWis();
	int GetAgi();
	int GetEva();
	int GetDef();
	int GetRage();
	void IncreaseRage(int amount);
	void DecreaseRage(int amount);
	void IncreaseHp(int amount);
	void DecreaseHp(int amount);
	int GetObjectListAround(int range);
	int GetPlayerListAround(int range);
	int GetObjectListAround(IChar ITarget, int range);
	int GetMonsterListAround(IChar IPlayer, int range);
	__int64 GetGStateEx();
	__int64 _GetGStateEx();
	bool IsGStateEx(__int64 state);
	void SendGStateExIceArrow(__int64 state);
	void SendGStateEx(__int64 state);
	void _SendGStateEx(__int64 state);
	int CheckHit(IChar Target, int value);
	void CouldntExecuteSkill();
	void _CouldntExecuteSkill();
	void Kill();
	void Kill(int Target);
	int GetAttack();
	int _ShowBattleMiss(IChar Target, int skillID);
	int __ShowBattleMiss(IChar Target, int skillID);
	void SetDirection(IChar Target);
	int OktayDamageNoAgro(IChar Target, int Damage, int SkillID);
	int OktayDamageSingle(IChar Target, int Damage, int SkillID);
	void OktayDamageArea(IChar Target, int Damage, int SkillID);
	void XEAMagDamageArea(IChar Target, int Damage, int Skill);
	void OktayDamageStorm(IChar Target, int Damage);
	int GetDeathBlow();
	int GetOTP();
	void AddDeathBlow(int amount);
	void RemoveDeathBlow(int amount);
	int IsInRange(IChar Target, int maxRange);
	void AddAbsorb(int amount);
	void RemoveAbsorb(int amount);
	int GetMagic();
	int _GetBuffValue(int BuffID);
	int GetBuffValue(int BuffID);
	int IsMoved(int x, int y);
	DWORD UnAttack(DWORD amount);
	DWORD Delay(DWORD amount);
	void MonsterSummonWrite(int SafeZoneCheck,int Monster,int CellMapCoordinate);
	int GetMobTanker();
	int GetMaxHp();
	int GetMaxMp();
	void OpenHTML(int html);
	void OpenWindow(std::string WindowName,int Type,int Time);
	void CloseWindow(std::string WindowName);
	void Revive();
	void CheckSpeed(int maxSpeed);
	void SetBlue();
	void SetRed();
	void RemoveSetBlue();
	void RemoveSetRed();
	int GetGID();
	void GuildColor();
	int GetRectX();
	int GetRectY();
	void IncreaseCritRate(int Amount);
	void DecreaseCritRate(int Amount);
	void NewAnnouncement(std::string msg);
	void OpenWebsite(std::string URL);
	void ScreenTime(int Time);
	void CloseScreenTime();
	void Scenario3Score(int Time,int RedScore,int BlueScore);
	void CloseScenario3Score();
	void Scenario3_3Score(int Time,int RedScore,int BlueScore);
	void CloseScenario3_3Score();
	void SpScore(int Time,int Type,int RedScore,int BlueScore,int RedWin,int BlueWin);
	void CloseSpScore();
	void SetRebirthTalisman(int Amount);
	void CloseRebirthTalisman();
	void IncreaseCritDamage(int Amount);
	void DecreaseCritDamage(int Amount);
	void SetMobHostility(int Amount);
	int GetAlliance();
	void SetAsAdmin();
	void SetAsSleep();
	void IncreaseMovingSpeed(int amount);
	void GetMovingSpeed();

	void DecreaseMovingSpeed(int amount);
	int GetRidingType();
	void EnableRiding(int Type);
	void DisableRiding();
	void _DisableRiding();
	std::string GetIP();
	void GiveReward(int Index, int Prefix, int Amount, int Info, int xAtk, int xMag, int TOA, int Upgr, int Def, int Eva, int Endurance, const char *msg);
	void StartQuest(int QuestID, int Time, int Repeat, int Count);
	void EndQuest(int QuestID, int Time, int Repeat, int Count);
	void EndQuestMission(int QuestID, int Time, int Repeat, int Count);
	void StartDutyQuest(int QuestID, int Time, int Repeat, int Count);

	void QuitQuest(int QuestID, int Time, int Repeat, int Count);
	void DailyQuestUpdate(int QuestID,int Monster,int CountEach);
	void IncreaseEBRate(int amount);
	void DecreaseEBRate(int amount);
	bool IsRiding1();
	bool IsRiding2();
	bool IsRiding3();
	bool IsRiding4();
	bool IsRiding5();
	bool IsRiding6();
	bool IsRiding7();
	bool IsRiding8();
	bool IsRiding9();
	bool IChar::StatsCheck(BYTE *StatTable,BYTE *_StatTable,int GetStr, int GetHth, int GetWis, int GetInt, int GetAgi);
	bool IsCorrect();
	bool isDead();
	bool isAssassin();
	int MaxInventorySize();
	int hasFirstPet();
	int hasSecondPet();
	int hasThirdPet();
	int numberOfPets();
	//new
	void InsertItem(int Index, int Prefix, int Amount);
	bool isInTrainingMap();
	int _ItemPointer(int IID);
	int ItemPointer(int IID);
	int RemoveItem(int Item);
	int RemoveItemLock(int Item);
	int RemoveItemDir(int Item);
	int RemoveItemPointer(int Item, int Amount);
	int RemoveItem(int Index, int Amount);
	void PutOffItem(int IID);
	bool validateStat(int Type, int InOut, int Amount);
	bool IsPVPValid();
	bool _IsInPVPValid();
	int GetDTArena();
	int ItemPointerLock(int IID);
	void SetContinueSkill();
	bool isContinueSkill();
	void UnsetContinueSkill();
	void SetPickRange(int Range);
	int GetPickRange();
	void SetUnblob(int Value);
	bool IsUnblobbing();
	int GetMobPet();
	void SetMobPet(int Monster);
	void Relog();
	int GetExtraStr();
	int GetExtraHth();
	int GetExtraInt();
	int GetExtraWis();
	int GetExtraAgi();
	void AddReward(int RewardID);
	int GetChannel();
	int GetMobRange();
	void SetChannel(int channel);
	void WriteToGuild(std::string message);
	void ClearPVP();
	void systemReward(int RewardID);
	int RandomItem();
	int GetSpeed();
	int GetRefreshCheck();
	void SetRefreshCheck(int Check);
	int GetSecondCall();
	void SetSecondCall(int Call);
	bool isSlytherin();
	bool isRavenclaw();
	bool isHufflepuff();
	bool isGryffindor();

	void SetChannelSystem(int Channel);
	std::string GetHWID();
	std::string GetPCName();
	std::string GetMAC();
	int GuildOnlinePlayers();
	std::string CostEffect(int Action);
	std::string ClassName();
	void PortToVillage();
	int InsertDeletedItem(int IID);
	void SetLevel(int Level);
	void ResetLevel(int Level);
	void ChangeName(std::string NewName);
	void SetName(std::string NewName);

};