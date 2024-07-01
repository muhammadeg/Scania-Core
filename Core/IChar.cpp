#include <windows.h>
#define HIDWORD(l) ((DWORD)(((DWORDLONG)(l)>>32)&0xFFFFFFFF))
typedef signed __int64     QWORD;
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <time.h>
#include "Functions.h"
#include "CriticalLock.h"
#include "IChar.h"
#include "IBuff.h"
#pragma warning (disable : 4244)
#pragma warning (disable : 4018)
int tries = 150;
int maxAllowedSpeed = GetPrivateProfileIntA("SpeedHack", "Value", 100, "./Configs/Protection.txt");

std::string Int2Str(int value)
{
	std::stringstream ss;
	ss << value;
	std::string str = ss.str();
	return str;
}
namespace HousesClass {
	int Gryffindor = 0;
	int Slytherin = 0;
	int Hufflepuff = 0;
	int Ravenclaw = 0;
}
IChar::IChar(void *Offset)
{
	this->Offset = Offset;
}

IChar::~IChar()
{
}

void *IChar::GetOffset()
{
	return this->Offset;
}

int IChar::IsOnline()
{
	if ((int)this->GetOffset())
	{
		if (CBase::IsDeleted((int)this->GetOffset()))
			return 0;
		else
			return 1;
	}
	else {
		return 0;
	}

	return 0;
}

int IChar::UpdateProperty(int Type, int Amount)
{
	return CPlayer::UpdateProperty((int)this->GetOffset(), Type, 1, Amount);
}

void IChar::Announcement(std::string msg, int color)
{
	if (this->IsOnline())
		CPlayer::Write(this->GetOffset(), 0xFF, "dsd", 247, msg.c_str(), color);
}

void IChar::SystemMessage(std::string msg, int color)
{
	if (this->IsOnline())
		CPlayer::Write(this->GetOffset(), 0xFF, "dsd", 248, msg.c_str(), color);

}
void IChar::AddFire_Resistance(int amount)
{
	if (this->IsOnline())
		(*(int(__cdecl **)(int, signed int, signed int, DWORD, DWORD))(*(DWORD *)(int)this->GetOffset() + 92))((int)this->GetOffset(), 18, 1, amount, amount);
}

void IChar::RemoveFire_Resistance(int amount)
{
	if (this->IsOnline())
		(*(int(__cdecl **)(int, signed int, signed int, DWORD, DWORD))(*(DWORD *)(int)this->GetOffset() + 92))((int)this->GetOffset(), 18, 0, amount, amount);
}

void IChar::AddIce_Resistance(int amount)
{
	if (this->IsOnline())
		(*(int(__cdecl **)(int, signed int, signed int, DWORD, DWORD))(*(DWORD *)(int)this->GetOffset() + 92))((int)this->GetOffset(), 19, 1, amount, amount);
}

void IChar::RemoveIce_Resistance(int amount)
{
	if (this->IsOnline())
		(*(int(__cdecl **)(int, signed int, signed int, DWORD, DWORD))(*(DWORD *)(int)this->GetOffset() + 92))((int)this->GetOffset(), 19, 0, amount, amount);
}

void IChar::AddLightning_Resistance(int amount)
{
	if (this->IsOnline())
		(*(int(__cdecl **)(int, signed int, signed int, DWORD, DWORD))(*(DWORD *)(int)this->GetOffset() + 92))((int)this->GetOffset(), 20, 1, amount, amount);
}

void IChar::RemoveLightning_Resistance(int amount)
{
	if (this->IsOnline())
		(*(int(__cdecl **)(int, signed int, signed int, DWORD, DWORD))(*(DWORD *)(int)this->GetOffset() + 92))((int)this->GetOffset(), 20, 0, amount, amount);
}


void IChar::AddHousePoints(int amount)
{
	int HouseIndex = 0, HousePoints = amount;

	if (this->IsOnline() && isPeaceEvilMode()) {
		if (this->isSlytherin())
			HouseIndex = 172;
		else if (this->isRavenclaw())
			HouseIndex = 175;
		else if (this->isHufflepuff())
			HouseIndex = 174;
		else
			HouseIndex = 171;

		CDBSocket::Write(69, "dd", HouseIndex, HousePoints);
	}
}

void IChar::AddHousePlayers(int amount)
{
	int HouseIndex = 0, HousePlayers = amount;

	if (this->IsOnline() && isPeaceEvilMode()) {
		if (this->isSlytherin())
			HouseIndex = 172;
		else if (this->isRavenclaw())
			HouseIndex = 175;
		else if (this->isHufflepuff())
			HouseIndex = 174;
		else
			HouseIndex = 171;

		CDBSocket::Write(70, "ddd", this->GetPID(), HouseIndex, HousePlayers);
	}
}

int IChar::Buff(int id, int time, int value)
{
	if (time < 0)
		return 0;

	if (this->IsOnline()) {

		if (id == 103)
			return 0;

		if (this->IsBuff(159) && id != 159)
			return 0;

		CChar::CancelAllBuff(this->GetOffset(), id);

		int Object = (int)this->GetOffset();

		if (id == 37) {
			Object = 20 * value + 5;
			value = 30 * value + 5;
		}

		if (id == 91) {
			Object = -(6 * abs(value) + 2);
			value = -(8 * abs(value) + 2);
		}

		if (id == 117)
			Object = value;

		if (id == 28) {
			Object = 3 * value + 9;
			value = 7 * value + 9;
		}

		int AddBuff = CBuff::CreateBuff(id, time, value, Object);

		if (AddBuff) {
			*(DWORD*)(AddBuff + 12) = value;
			(*(int(__thiscall **)(int, int))(*(DWORD *)(int)this->GetOffset() + 180))((int)this->GetOffset(), AddBuff);
		}

		return 1;
	}
	return 0;
}

int IChar::_Buff(int id, int time, int value)
{
	if (time < 0)
		return 0;

	if (this->IsOnline()) {

		if (id == 103)
			return 0;

		if (this->_IsBuff(159) && id != 159)
			return 0;

		this->_CancelBuff(id);
		int Object = (int)this->GetOffset();

		if (id == 37 || id == 117) {
			Object = 20 * value + 5;
			value = 30 * value + 5;
		}

		int AddBuff = CBuff::CreateBuff(id, time, value, Object);

		if (AddBuff) {
			*(DWORD*)(AddBuff + 12) = value;
			int v7 = (*(int(__thiscall **)(void *, int))(*(DWORD *)AddBuff + 4))((void*)AddBuff, (int)this->Offset);
			if (v7)
			{
				*((DWORD *)AddBuff + 5) = *(DWORD *)((int)this->Offset + 360);
				*(DWORD *)((int)this->Offset + 360) = AddBuff;
			}
			else
				CBuff::Release((void*)AddBuff, 1);
		}

		return 1;
	}
	return 0;
}

void IChar::SaveBuff(int BuffID, int Time) {
	this->SaveBuff(BuffID, Time, 0, 0, 0);
}

void IChar::SaveBuff(int BuffID, int Time, int Value, int SBName, int SBKey) {
	int Times = (int)time(0) + Time;
	CDBSocket::Write(95, "ddddddd", 1, this->GetPID(), BuffID, Value, SBKey, SBName, Times);
	this->UpdateBuff(BuffID, Time, Value);

	if (SBName && SBKey)
		this->SetBuffIcon(Time * 1000, 0, SBName, SBKey);
}

void IChar::UpdateSavedBuff(int BuffID, int Time, int Value, int SBName, int SBKey) {
	int Times = (int)time(0) + Time;
	CDBSocket::Write(95, "ddddddd", 3, this->GetPID(), BuffID, Value, SBKey, SBName, Times);
	this->Buff(BuffID, Time, Value);

	if (SBName && SBKey)
		this->SetBuffIcon(Time * 1000, 0, SBName, SBKey);
}

void IChar::RemoveSavedBuff(int BuffID) {
	this->CancelBuff(BuffID);
	CDBSocket::Write(95, "ddddddd", 2, this->GetPID(), BuffID, 0, 0, 0, 0);
}

int IChar::GetBuffValue(int BuffID) {

	int v5 = 0;

	if (this->IsOnline() && BuffID >= 0)
		v5 = GetBuffStat((int)this->Offset, 0, BuffID, tries);

	return v5;
}

int IChar::UpdateBuff(int BuffID, int Time, int Value)
{
	if (this->IsOnline() && BuffID >= 0) {
		UpdateBuffStat((int)this->Offset, 0, BuffID, Time, Value, tries);
		if (BuffID == 1592 && this->GetMap() == GetTBMap())
			CChar::WriteInSight(this->GetOffset(), 145, "dI", this->GetID(), __int64(Value));
		return 1;
	}

	return 0;
}

int IChar::_UpdateBuff(int BuffID, int Time, int Value)
{
	if (this->IsOnline() && BuffID >= 0) {
		_UpdateBuffStat((int)this->Offset, 0, BuffID, Time, Value);
		return 1;
	}

	return 0;
}

int IChar::_GetBuffValue(int BuffID)
{
	if (this->IsOnline() && BuffID >= 0)
		return _GetBuffStat((int)this->Offset, 0, BuffID);

	return 0;
}

int IChar::GetAdmin()
{
	if (this->IsOnline())
		return *(DWORD*)((int)this->GetOffset() + 456);
	else
		return 0;
}

signed __int64 IChar::GetEXP()
{
	if (this->IsOnline())
		return *(QWORD*)((int)this->GetOffset() + 472);
	else
		return 0;
}

signed __int64 IChar::GetOldEXP()
{
	if (this->IsOnline())
		return *(QWORD*)((int)this->GetOffset() + 476);
	else
		return 0;
}

int IChar::GetMinPhyAttack()
{
	if (this->IsOnline())
		return *(DWORD*)((int)this->GetOffset() + 128);
	else
		return 0;
}

int IChar::GetMaxPhyAttack()
{
	if (this->IsOnline())
		return *(DWORD*)((int)this->GetOffset() + 132);
	else
		return 0;
}
int IChar::GetPhyAtk()
{
	if (this->IsOnline()){
		return CTools::Rate(CChar::GetMinAttack((int)this->Offset), CChar::GetMaxAttack((int)this->Offset));
	}
	else
		return 0;
}

int IChar::GetMagAtk()
{
	if (this->IsOnline()){
		return CTools::Rate(CChar::GetMinMagic((int)this->Offset), CChar::GetMaxMagic((int)this->Offset));
	}
	else
		return 0;
}

int IChar::GetMinMagAttack()
{
	if (this->IsOnline())
		return *(DWORD*)((int)this->GetOffset() + 136);
	else
		return 0;
}

int IChar::GetMaxMagAttack()
{
	if (this->IsOnline())
		return *(DWORD*)((int)this->GetOffset() + 140);
	else
		return 0;
}

int IChar::GetX()
{
	if (this->IsOnline())
		return *(DWORD*)((int)this->GetOffset() + 0x14c);
	else
		return 0;
}

int IChar::GetY()
{
	if (this->IsOnline())
		return *(DWORD*)((int)this->GetOffset() + 0x150);
	else
		return 0;
}

int IChar::GetZ()
{
	if (this->IsOnline())
		return *(DWORD*)((int)this->GetOffset() + 0x154);
	else
		return 0;
}

int IChar::GetDirection()
{
	if (this->IsOnline())
		return *(DWORD*)((int)this->GetOffset() + 348);
	else
		return 0;
}
int IChar::GetMap()
{
	if (this->IsOnline())
		return *(DWORD*)((int)this->GetOffset() + 316);
	return 0;
}

int IChar::GetMapX()
{
	if (this->IsOnline())
		return this->GetX() >> 13;
	return 0;
}

int IChar::GetMapY()
{
	if (this->IsOnline())
		return this->GetY() >> 13;
	return 0;
}

int IChar::GetMapIndex()
{
	return (this->GetMapX() * 1000) + this->GetMapY();
}

void IChar::Teleport(int Map, int X, int Y)
{
	if (this->IsOnline() && X > 0 && Y > 0)
	{
		if (this->GetBuffValue(1589) && this->GetMap() == GetTBMap() && Map != GetTBMap()) {
			this->BoxMsg("You can use /leave if you want to quit Triangular Battle.");
			return;
		}

		if (this->IsBuff(349))
			this->DisableRiding();

		if (CChar::IsGState((int)this->GetOffset(), 2))
			this->Revive();

		int *GetSetXY = new int[2];
		GetSetXY[0] = X;
		GetSetXY[1] = Y;
		CPlayer::Teleport((int)this->GetOffset(), Map, (int)GetSetXY, 0, 1);
		delete[] GetSetXY;
	}
}

void IChar::Teleport(int Map, int X, int Y, int Z)
{
	if (this->IsOnline() && X > 0 && Y > 0 && Z >= 0)
	{
		if (this->GetBuffValue(1589) && this->GetMap() == GetTBMap() && Map != GetTBMap()) {
			this->BoxMsg("You can use /leave if you want to quit Triangular Battle.");
			return;
		}

		if (this->IsBuff(349))
			this->DisableRiding();

		if (CChar::IsGState((int)this->GetOffset(), 2))
			this->Revive();

		int *GetSetXY = new int[2];
		GetSetXY[0] = X;
		GetSetXY[1] = Y;
		CPlayer::Teleport((int)this->GetOffset(), Map, (int)GetSetXY, Z, 1);
		delete[] GetSetXY;
	}
}

void IChar::Kick()
{
	if (this->IsOnline())
	{
		CPlayer::Write(this->GetOffset(), 45, "b", 1);
		Undefined::ForKick(*(void **)((int)this->GetOffset() + 1676), 1);
	}
}



void IChar::SetX(int Value)
{
	if (this->IsOnline())
		*(DWORD*)((int)this->GetOffset() + 332) = Value;
}

void IChar::SetY(int Value)
{
	if (this->IsOnline())
		*(DWORD*)((int)this->GetOffset() + 336) = Value;
}

void IChar::SetZ(int Value)
{
	if (this->IsOnline())
		*(DWORD*)((int)this->GetOffset() + 340) = Value;
}

int IChar::IsValid()
{
	if (this->IsOnline())
	{
		if (this->GetType() == 0)
		{
			if (CChar::IsNormal((int)this->GetOffset()))
				return 1;
			else
				return 0;
		}

		return 1;
	}
	else {
		return 0;
	}
}

int IChar::IsParty()
{
	if (this->IsOnline())
	{
		if (*(DWORD*)((int)this->GetOffset() + 1016))
			return 1;
		else
			return 0;
	}
	else {
		return 0;
	}
}

int IChar::GetPartyID()
{
	if (this->IsOnline())
		return *(DWORD*)((int)this->GetOffset() + 1016);
	else
		return 0;
}

int IChar::GetID()
{
	if (this->GetOffset())
		return *(DWORD*)((int)this->GetOffset() + 28);
	else
		return 0;
}

int IChar::GetUID()
{
	if (this->IsOnline())
		return *(DWORD *)((int)this->GetOffset() + 448);
	else
		return 0;
}

int IChar::GetPID()
{
	if (this->IsOnline())
		return *(DWORD *)((int)this->GetOffset() + 452);
	else
		return 0;
}

int IChar::GetCurHp()
{
	if (this->IsOnline())
		return *(DWORD *)((int)this->GetOffset() + 272);
	else
		return 0;
}

int IChar::GetCurMp()
{
	if (this->IsOnline())
		return *(DWORD *)((int)this->GetOffset() + 276);

	return 0;
}

int IChar::GetDamage(int SkillID, void* Target){
	return calculDmg(this->GetOffset(), SkillID, Target);
}

void IChar::DecreaseMana(int amount)
{
	if (this->IsOnline())
	{
		if (this->GetCurMp() >= amount) {
			if (!this->validateStat(this->GetCurMp(), 0, amount))
				return;

			(*(int(__cdecl **)(DWORD, signed int, DWORD, int))(*(DWORD *)(int)this->GetOffset() + 88))((int)this->GetOffset(), 8, 0, amount);
		}
	}
}

void IChar::IncreaseMana(int amount)
{
	if (this->IsOnline()) {
		if (!this->validateStat(this->GetCurMp(), 1, amount))
			return;
		(*(int(__cdecl **)(DWORD, signed int, DWORD, int))(*(DWORD *)(int)this->GetOffset() + 88))((int)this->GetOffset(), 8, 1, amount);
	}
}


void IChar::IncreaseResist(int amount)
{
	if (this->IsOnline())
		(*(int(__cdecl **)(int, signed int, signed int, DWORD))(*(DWORD *)(int)this->GetOffset() + 92))((int)this->GetOffset(), 29, 1, amount);
}

void IChar::DecreaseResist(int amount)
{
	if (this->IsOnline())
		(*(int(__cdecl **)(int, signed int, signed int, DWORD))(*(DWORD *)(int)this->GetOffset() + 92))((int)this->GetOffset(), 29, 0, amount);
}

int IChar::GetType()
{
	if (this->IsOnline())
	{
		return *(DWORD*)((int)this->GetOffset() + 24) - 1;
	}
	else {
		return 2;
	}
}

void IChar::_ShowBattleAnimation(IChar Target, int skillID, int SkillGrade)
{
	if (this->IsValid())
		CChar::WriteInSight(this->GetOffset(), 0x3f, "bddbbwwbd", skillID, this->GetID(), Target.GetID(), Target.GetType(), SkillGrade, 0, 0, true, 0);
}

int IChar::GetClass()
{
	if (this->IsOnline())
		return *(DWORD*)((int)this->GetOffset() + 460);
	else
		return 10;
}

int IChar::GetTransformGrade()
{
	if (this->IsOnline())
		return *(DWORD*)((int)this->GetOffset() + 1112);
	else
		return 0;
}

void IChar::CancelBuff(int BuffID)
{
	if (this->IsOnline()) {
		CChar::CancelAllBuff(this->GetOffset(), BuffID);
	}
}

void IChar::_CancelBuff(int BuffID)
{
	if (this->IsOnline())
		_CancelBuffStat((int)this->GetOffset(), 0, BuffID);
}

int IChar::IsBuff(int id)
{
	if (this->IsOnline() && id >= 0)
	{
		if (HaveBuff((int)this->Offset, 0, id, tries))
			return 1;
	}

	return 0;
}

bool IChar::isMuted() {
	if (this->IsOnline())
		return *(DWORD *)((int)this->Offset + 1460) > GetTickCount();
	return false;
}

void IChar::setMuted(int time) {
	if (this->IsOnline())
		*(DWORD *)((int)this->Offset + 1460) = GetTickCount() + (time * 1000);
}

bool IChar::isPortalMode() {
	if (this->IsOnline())
		return CChar::IsGState((int)this->Offset, 4096) ? true : false;

	return false;
}

int IChar::_IsBuff(int id)
{
	if (this->IsOnline() && id >= 0)
	{
		if (_HaveBuff((int)this->Offset, 0, id))
			return 1;
		else
			return 0;
	}
	else {
		return 0;
	}
}

int IChar::GetLevel()
{
	if (this->IsOnline())
		return *(DWORD*)((int)this->GetOffset() + 60);
	else
		return 0;
}

void IChar::BoxMsg(std::string msg)
{
	if (this->IsOnline())
		CPlayer::Write(this->GetOffset(), 0xFF, "ds", 249, msg.c_str());
}

const char *IChar::GetName()
{
	if (this->IsOnline())
		return (const char*)((int)this->GetOffset() + 32);
	else
		return "Nothing";
}



int IChar::ScaniaTimer(int amount = 1)
{
	return (GetTickCount() / 1000) % amount == 0;
}

int IChar::IsShopping()
{
	if (CChar::IsGState((int)this->GetOffset(), 16))
		return true;
	else
		return 0;
}
int IChar::GetSkillPointer(int SkillID)
{
	if (this->IsOnline() && this->GetType() == 0)
		return *((DWORD *)((int)this->GetOffset() + 624) + SkillID + 2);
	else
		return 0;
}

void IChar::AddMinAttack(int amount)
{
	if (this->IsOnline()) {
		if (!this->validateStat(this->GetMinPhyAttack(), 1, amount))
			return;

		if (!this->validateStat(this->GetMaxPhyAttack(), 1, amount))
			return;

		(*(int(__cdecl **)(int, signed int, signed int, DWORD, DWORD))(*(DWORD *)(int)this->GetOffset() + 92))((int)this->GetOffset(), 27, 1, amount, amount);
	}
}

void IChar::RemoveMinAttack(int amount)
{
	if (this->IsOnline()) {

		if (!this->validateStat(this->GetMinPhyAttack(), 0, amount))
			return;

		if (!this->validateStat(this->GetMaxPhyAttack(), 0, amount))
			return;

		(*(int(__cdecl **)(int, signed int, signed int, DWORD, DWORD))(*(DWORD *)(int)this->GetOffset() + 92))((int)this->GetOffset(), 27, 0, amount, amount);
	}
}

void IChar::AddMaxAttack(int amount)
{
	if (this->IsOnline()) {
		if (!this->validateStat(this->GetMinMagAttack(), 1, amount))
			return;

		if (!this->validateStat(this->GetMaxMagAttack(), 1, amount))
			return;

		(*(int(__cdecl **)(int, signed int, signed int, DWORD, DWORD))(*(DWORD *)(int)this->GetOffset() + 92))((int)this->GetOffset(), 28, 1, amount, amount);
	}
}

void IChar::RemoveMaxAttack(int amount)
{
	if (this->IsOnline()) {

		if (!this->validateStat(this->GetMinMagAttack(), 0, amount))
			return;

		if (!this->validateStat(this->GetMaxMagAttack(), 0, amount))
			return;

		(*(int(__cdecl **)(int, signed int, signed int, DWORD, DWORD))(*(DWORD *)(int)this->GetOffset() + 92))((int)this->GetOffset(), 28, 0, amount, amount);
	}
}

void IChar::DecreaseMaxHp(int amount)
{
	if (this->IsOnline()) {

		(*(void(__cdecl **)(int, signed int, signed int, __int32))(*(DWORD*)(int)this->GetOffset() + 92))((int)this->GetOffset(), 5, 0, amount);
	}
}

void IChar::IncreaseMaxHp(int amount)
{
	if (this->IsOnline()) {

		(*(void(__cdecl **)(int, signed int, signed int, __int32))(*(DWORD*)(int)this->GetOffset() + 92))((int)this->GetOffset(), 5, 1, amount);
	}
}

void IChar::DecreaseMaxMp(int amount)
{
	if (this->IsOnline()) {

		if (!this->validateStat(this->GetMaxMp(), 0, amount))
			return;

		(*(void(__cdecl **)(int, signed int, signed int, __int32))(*(DWORD*)(int)this->GetOffset() + 92))((int)this->GetOffset(), 6, 0, amount);
	}
}

void IChar::IncreaseMaxMp(int amount)
{
	if (this->IsOnline()) {
		if (!this->validateStat(this->GetMaxMp(), 1, amount))
			return;

		(*(void(__cdecl **)(int, signed int, signed int, __int32))(*(DWORD*)(int)this->GetOffset() + 92))((int)this->GetOffset(), 6, 1, amount);
	}
}

void IChar::AddHp(int amount)
{
	if (this->IsOnline()) {

		int OldHp = this->GetExtraHth();

		if (!this->validateStat(OldHp, 1, amount))
			return;

		(*(void(__cdecl **)(DWORD, signed int, DWORD, signed int))(*(DWORD *)(int)this->GetOffset() + 92))((int)this->GetOffset(), 1, 1, amount);

		if (this->GetExtraHth() < OldHp)
			(*(void(__cdecl **)(DWORD, signed int, DWORD, signed int))(*(DWORD *)(int)this->GetOffset() + 92))((int)this->GetOffset(), 1, 0, amount * 2);
	}
}

void IChar::RemoveHp(int amount)
{
	if (this->IsOnline()) {
		int OldHp = this->GetExtraHth();

		if (!this->validateStat(OldHp, 0, amount))
			return;

		(*(void(__cdecl **)(DWORD, signed int, DWORD, signed int))(*(DWORD *)(int)this->GetOffset() + 92))((int)this->GetOffset(), 1, 0, amount);
		if (this->GetExtraHth() > OldHp)
			(*(void(__cdecl **)(DWORD, signed int, DWORD, signed int))(*(DWORD *)(int)this->GetOffset() + 92))((int)this->GetOffset(), 1, 1, amount * 2);
	}
}

void IChar::AddStr(int amount)
{
	if (this->IsOnline()) {

		int Str = this->GetExtraStr();

		if (!this->validateStat(Str, 1, amount))
			return;

		(*(void(__cdecl **)(int, DWORD, signed int, signed int))(*(DWORD *)(int)this->GetOffset() + 92))((int)this->GetOffset(), 0, 1, amount);
		if (this->GetExtraStr() < Str)
			(*(void(__cdecl **)(int, DWORD, signed int, signed int))(*(DWORD *)(int)this->GetOffset() + 92))((int)this->GetOffset(), 0, 0, amount * 2);
	}
}

void IChar::RemoveStr(int amount)
{
	if (this->IsOnline()) {
		int Str = this->GetExtraStr();

		if (!this->validateStat(Str, 0, amount))
			return;

		(*(void(__cdecl **)(int, DWORD, signed int, signed int))(*(DWORD *)(int)this->GetOffset() + 92))((int)this->GetOffset(), 0, 0, amount);
		if (this->GetExtraStr() > Str)
			(*(void(__cdecl **)(int, DWORD, signed int, signed int))(*(DWORD *)(int)this->GetOffset() + 92))((int)this->GetOffset(), 0, 1, amount * 2);
	}
}

void IChar::AddInt(int amount)
{
	if (this->IsOnline()) {
		int Int = this->GetExtraInt();

		if (!this->validateStat(Int, 1, amount))
			return;

		(*(void(__cdecl **)(DWORD, signed int, DWORD, signed int))(*(DWORD *)(int)this->GetOffset() + 92))((int)this->GetOffset(), 2, 1, amount);
		if (this->GetExtraInt() < Int)
			(*(void(__cdecl **)(DWORD, signed int, DWORD, signed int))(*(DWORD *)(int)this->GetOffset() + 92))((int)this->GetOffset(), 2, 0, amount * 2);
	}
}

void IChar::RemoveInt(int amount)
{
	if (this->IsOnline()) {
		int Int = this->GetExtraInt();

		if (!this->validateStat(Int, 0, amount))
			return;

		(*(void(__cdecl **)(DWORD, signed int, DWORD, signed int))(*(DWORD *)(int)this->GetOffset() + 92))((int)this->GetOffset(), 2, 0, amount);
		if (this->GetExtraInt() > Int)
			(*(void(__cdecl **)(DWORD, signed int, DWORD, signed int))(*(DWORD *)(int)this->GetOffset() + 92))((int)this->GetOffset(), 2, 1, amount * 2);
	}
}

void IChar::AddWis(int amount)
{
	if (this->IsOnline()) {
		int Wis = this->GetExtraWis();
		if (!this->validateStat(Wis, 1, amount))
			return;
		(*(void(__cdecl **)(int, signed int, signed int, signed int))(*(DWORD *)(int)this->GetOffset() + 92))((int)this->GetOffset(), 3, 1, amount);
		if (this->GetExtraWis() < Wis)
			(*(void(__cdecl **)(int, signed int, signed int, signed int))(*(DWORD *)(int)this->GetOffset() + 92))((int)this->GetOffset(), 3, 0, amount * 2);
	}
}

void IChar::RemoveWis(int amount)
{
	if (this->IsOnline()) {
		int Wis = this->GetExtraWis();
		if (!this->validateStat(Wis, 0, amount))
			return;
		(*(void(__cdecl **)(int, signed int, signed int, signed int))(*(DWORD *)(int)this->GetOffset() + 92))((int)this->GetOffset(), 3, 0, amount);
		if (this->GetExtraWis() > Wis)
			(*(void(__cdecl **)(int, signed int, signed int, signed int))(*(DWORD *)(int)this->GetOffset() + 92))((int)this->GetOffset(), 3, 1, amount * 2);
	}
}

void IChar::AddAgi(int amount)
{
	if (this->IsOnline()) {
		int Agi = this->GetExtraAgi();
		if (!this->validateStat(Agi, 1, amount))
			return;
		(*(void(__cdecl **)(DWORD, signed int, DWORD, DWORD))(*(DWORD *)(int)this->GetOffset() + 92))((int)this->GetOffset(), 4, 1, amount);
		if (this->GetExtraAgi() < Agi)
			(*(void(__cdecl **)(DWORD, signed int, DWORD, DWORD))(*(DWORD *)(int)this->GetOffset() + 92))((int)this->GetOffset(), 4, 0, amount * 2);
	}
}

void IChar::RemoveAgi(int amount)
{
	if (this->IsOnline()) {
		int Agi = this->GetExtraAgi();
		if (!this->validateStat(Agi, 0, amount))
			return;
		(*(void(__cdecl **)(DWORD, signed int, DWORD, DWORD))(*(DWORD *)(int)this->GetOffset() + 92))((int)this->GetOffset(), 4, 0, amount);
		if (this->GetExtraAgi() > Agi)
			(*(void(__cdecl **)(DWORD, signed int, DWORD, DWORD))(*(DWORD *)(int)this->GetOffset() + 92))((int)this->GetOffset(), 4, 1, amount * 2);
	}
}

void IChar::AddOTP(int amount)
{
	if (this->IsOnline()) {
		int OTP = this->GetOTP();

		if (!this->validateStat(OTP, 1, amount))
			return;

		(*(int(__cdecl **)(int, signed int, signed int, DWORD, DWORD))(*(DWORD *)(int)this->GetOffset() + 92))((int)this->GetOffset(), 9, 1, amount, amount);

		if (this->GetOTP() < OTP)
			(*(int(__cdecl **)(int, signed int, signed int, DWORD, DWORD))(*(DWORD *)(int)this->GetOffset() + 92))((int)this->GetOffset(), 9, 0, amount * 2, amount * 2);
	}
}

void IChar::RemoveOTP(int amount)
{
	if (this->IsOnline()) {
		int OTP = this->GetOTP();

		if (!this->validateStat(OTP, 0, amount))
			return;

		(*(int(__cdecl **)(int, signed int, signed int, DWORD, DWORD))(*(DWORD *)(int)this->GetOffset() + 92))((int)this->GetOffset(), 9, 0, amount, amount);

		if (this->GetOTP() > OTP)
			(*(int(__cdecl **)(int, signed int, signed int, DWORD, DWORD))(*(DWORD *)(int)this->GetOffset() + 92))((int)this->GetOffset(), 9, 1, amount * 2, amount * 2);
	}
}

void IChar::AddEva(int amount)
{
	if (this->IsOnline()) {
		int Eva = this->GetEva();

		if (!this->validateStat(Eva, 1, amount))
			return;

		(*(int(__cdecl **)(int, signed int, signed int, DWORD))(*(DWORD *)(int)this->GetOffset() + 92))((int)this->GetOffset(), 10, 1, amount);
		if (this->GetEva() < Eva)
			(*(int(__cdecl **)(int, signed int, signed int, DWORD))(*(DWORD *)(int)this->GetOffset() + 92))((int)this->GetOffset(), 10, 0, amount * 2);
	}
}

void IChar::RemoveEva(int amount)
{
	if (this->IsOnline()) {
		int Eva = this->GetEva();
		if (!this->validateStat(Eva, 0, amount))
			return;
		(*(int(__cdecl **)(int, signed int, signed int, DWORD))(*(DWORD *)(int)this->GetOffset() + 92))((int)this->GetOffset(), 10, 0, amount);
		if (this->GetEva() > Eva)
			(*(int(__cdecl **)(int, signed int, signed int, DWORD))(*(DWORD *)(int)this->GetOffset() + 92))((int)this->GetOffset(), 10, 1, amount * 2);
	}
}

void IChar::AddDef(int amount)
{
	if (this->IsOnline()) {
		int Def = this->GetDef();
		if (!this->validateStat(Def, 1, amount))
			return;

		(*(int(__cdecl **)(int, signed int, signed int, DWORD, DWORD))(*(DWORD *)(int)this->GetOffset() + 92))((int)this->GetOffset(), 15, 1, amount, amount);
		if (this->GetDef() < Def)
			(*(int(__cdecl **)(int, signed int, signed int, DWORD, DWORD))(*(DWORD *)(int)this->GetOffset() + 92))((int)this->GetOffset(), 15, 0, amount * 2, amount * 2);
	}
}

void IChar::RemoveDef(int amount)
{
	if (this->IsOnline()) {
		int Def = this->GetDef();
		if (!this->validateStat(Def, 0, amount))
			return;
		(*(int(__cdecl **)(int, signed int, signed int, DWORD, DWORD))(*(DWORD *)(int)this->GetOffset() + 92))((int)this->GetOffset(), 15, 0, amount, amount);
		if (this->GetDef() > Def)
			(*(int(__cdecl **)(int, signed int, signed int, DWORD, DWORD))(*(DWORD *)(int)this->GetOffset() + 92))((int)this->GetOffset(), 15, 1, amount * 2, amount * 2);
	}
}

void IChar::AddFxToTarget(std::string effectName, bool AutoRemove, bool Continues, bool nForced)
{
	if (this->IsOnline())
	{
		if (this->IsBuff(159) || this->IsBuff(327) || this->IsBuff(329) || this->isPortalMode())
			return;

		CChar::WriteInSight(this->GetOffset(), 0xFF, "ddsdddd", 239, this->GetID(), effectName.c_str(), AutoRemove, Continues, nForced, 0);
	}
}

void IChar::AddFxToBone(std::string effectName, int Type)
{
	if (this->IsOnline())
		CChar::WriteInSight(this->GetOffset(), 0xFE, "ddsd", 177, this->GetID(), effectName.c_str(), Type);
}

void IChar::RemoveFxBone(std::string effectName)
{
	if (this->IsOnline())
		CChar::WriteInSight(this->GetOffset(), 0xFE, "dds", 176, this->GetID(), effectName.c_str());
}

void IChar::_AddFxToTarget(std::string effectName, bool AutoRemove, bool Continues, bool nForced)
{
	if (this->IsOnline())
	{
		if (this->_IsBuff(159) || this->_IsBuff(327) || this->_IsBuff(329) || this->isPortalMode())
			return;

		CChar::WriteInSight(this->GetOffset(), 0xFF, "ddsdddd", 239, this->GetID(), effectName.c_str(), AutoRemove, Continues, nForced, 0);
	}
}

void IChar::AddParticleE(std::string effectName, int Type)
{
	if (this->IsValid() && !this->isPortalMode())
		CChar::WriteInSight(this->GetOffset(), 0xFE, "ddsd", 177, this->GetID(), effectName.c_str(), Type);
}
void IChar::AddParticle(int Bone, const char *ParticleName)
{
	if (this->IsOnline() && !this->isPortalMode())
		CChar::WriteInSight(this->GetOffset(), 0xFF, "dsdd", 247, ParticleName, *(DWORD *)((int)this->GetOffset() + 28), Bone);
}

int IChar::GetSpecialty()
{
	if (this->IsOnline())
		return *(DWORD *)((int)this->GetOffset() + 464);
	else
		return 0;
}

int IChar::IsMobMoving()
{
	if (this->IsOnline() && this->IsValid())
	{
		if (*(DWORD *)((int)this->GetOffset() + 656) == 1)
			return 1;
		else
			return 0;
	}
	else {
		return 0;
	}
}

int IChar::IsMobAggressive()
{
	if (this->IsOnline() && this->IsValid())
		return *(DWORD *)((int)this->Offset + 476);
	else
		return 0;
}

int IChar::GetMobIndex()
{
	if (this->GetType() == 1)
		return *(DWORD*)(*(DWORD*)((int)this->Offset + 440) + 60);
	else
		return 0;
}

int IChar::GetMobArea()
{
	int Result = 0;

	if (this->GetType() == 1) {
		int v2; // eax@1
		int v3; // eax@2
		int v5; // [sp+4h] [bp-8h]@1
		int v6; // [sp+8h] [bp-4h]@1

		CGuild::CriticalSectionEnter((volatile LONG*)0x4E187C);
		Undefined::CreateMonsterValue((void*)0x4E1870, (int)&v6, (int)this->Offset + 444);
		v2 = Undefined::Check((int)0x4E1870, (int)&v5);
		if ((unsigned __int8)Undefined::CheckValues(&v6, v2))
		{
			v3 = Undefined::GetValue(&v6);
			Result = *(DWORD *)(*(DWORD *)(v3 + 4) + 40);
		}
		CGuild::CriticalSectionLeave((volatile LONG*)0x4E187C);
	}

	return Result;
}

int IChar::GetMobRange()
{
	if (this->GetType() == 1)
		return *(DWORD*)((int)this->Offset + 544) >> 5;
	else
		return 0;
}

int IChar::IsMobHaveTarget()
{
	if (this->IsOnline() && this->IsValid())
		return *(DWORD*)((int)this->GetOffset() + 464);
	else
		return 0;
}

void IChar::SetMobTarget(int target)
{
	if (this->IsOnline())
	{
		if (this->GetMobTanker() && !target)
		{
			(*(void(__thiscall **)(int, DWORD))(*(DWORD *)this->GetOffset() + 132))((int)this->GetOffset(), *(DWORD *)((int)this->GetOffset() + 464));
			(*(void(__thiscall **)(int, DWORD))(*(DWORD *)this->GetOffset() + 188))((int)this->GetOffset(), 0);
			return;
		}

		if (!this->GetMobTanker() && target)
		{
			IChar ITarget((void*)target);

			if (ITarget.IsValid())
			{
				if (CChar::GetRange((int)ITarget.GetOffset() + 332, (int)this->GetOffset() + 332) <= 200) {
					CIOObject::_AddRef(target, (volatile LONG *)((int)target + 356));
					(*(void(__thiscall **)(DWORD, DWORD))(*(DWORD *)(int)this->GetOffset() + 188))((int)this->GetOffset(), target);
				}
			}
		}
	}
}

DWORD IChar::MobUnAttack(DWORD amount)
{
	if (this->IsOnline() && this->IsValid())
	{
		if (amount)
			return *(DWORD *)((int)this->GetOffset() + 468) = GetTickCount() + amount;
		else
			return *(DWORD *)((int)this->GetOffset() + 468) = 0;
	}
	else {
		return 0;
	}
}

DWORD IChar::MobDelay(DWORD amount)
{
	if (this->IsOnline() && this->IsValid())
	{
		if (amount)
			return *(DWORD *)((int)this->GetOffset() + 556) = GetTickCount() + amount;
		else
			return *(DWORD *)((int)this->GetOffset() + 556) = 0;
	}
	else {
		return 0;
	}
}



void IChar::MobDelete()
{
	if (this->IsOnline())
	{
		this->SetMobTarget(0);
		CChar::CancelAllBuff2(this->GetOffset());
		CChar::WriteInSight(this->GetOffset(), 56, "db", this->GetID(), 7);
		CChar::WriteInSight(this->GetOffset(), 61, "db", this->GetID(), 9);
		*(DWORD *)((int)this->GetOffset() + 468) = GetTickCount() + 10000;
		CBase::Delete(this->GetOffset());
	}
}

void IChar::Blob()
{
	if (this->IsOnline())
	{
		this->SetMobTarget(0);
		CChar::CancelAllBuff2(this->GetOffset());
		CChar::WriteInSight(this->GetOffset(), 73, "db", this->GetID(), 52);
		CChar::WriteInSight(this->GetOffset(), 56, "db", this->GetID(), 7);
		CChar::WriteInSight(this->GetOffset(), 61, "db", this->GetID(), 9);
		CBase::Delete(this->GetOffset());
	}
}

void IChar::UpdateHonor(int HP, int HK, int HD, int DKPT, int DKPW, int PLT, int PLW, int SVT, int SVW, int RP)
{
	if (this->IsOnline())
		CDBSocket::Write(81, "ddddddddddd", this->GetPID(), HP, HK, HD, DKPT, DKPW, PLT, PLW, SVT, SVW, RP);
}

void IChar::ChangeHonor(int HP, int HK, int HD, int DKPT, int DKPW, int PLT, int PLW, int SVT, int SVW, int RP)
{
	if (this->IsOnline())
		CDBSocket::Write(99, "ddddddddddd", this->GetPID(), HP, HK, HD, DKPT, DKPW, PLT, PLW, SVT, SVW, RP);
}

void IChar::SetHonor(int HP, int RP, int HD, int DKPT, int DKPW, int PLT, int PLW, int SVT, int SVW, int HK) {
	if (HP) {
		std::string playerName = this->GetName();
		this->AddProperty(PlayerProperty::HPx, HP);
		HonorPromotion(this->GetPID());
		this->UpdateHonorTag(this->GetProperty(PlayerProperty::HPx));
		this->SystemMessage("You got " + Int2Str(HP) + " Honor Points.", RGB(255, 255, 255));
	}

	if (RP) {
		this->AddProperty(PlayerProperty::RPx, RP);
		if (RP > 0)
			this->SystemMessage("You got " + Int2Str(RP) + " Reward Points.", RGB(255, 255, 255));
		else
			this->SystemMessage("You spent " + Int2Str(RP*-1) + " Reward Points.", RGB(255, 255, 255));
	}

	if (HD) {
		this->AddProperty(PlayerProperty::HDx, HD);
		this->SystemMessage("Your Honor Death Count has increased.", RGB(255, 0, 0));
	}

	if (DKPT)
		this->AddProperty(PlayerProperty::DKPTx, DKPT);

	if (DKPW) {
		this->AddProperty(PlayerProperty::DKPWx, DKPW);
		this->SystemMessage("You got " + Int2Str(DKPW) + " Destructing Key Win.", RGB(255, 255, 255));
	}

	if (PLT)
		this->AddProperty(PlayerProperty::PLTx, PLT);

	if (PLW) {
		this->AddProperty(PlayerProperty::PLWx, PLW);
		this->SystemMessage("You got " + Int2Str(PLW) + " Protecting Leader Win.", RGB(255, 255, 255));
	}

	if (SVT)
		this->AddProperty(PlayerProperty::SVTx, SVT);

	if (SVW) {
		this->AddProperty(PlayerProperty::SVWx, SVW);
		this->SystemMessage("You got " + Int2Str(SVW) + " Suffering Valey Win.", RGB(255, 255, 255));
	}

	if (HK) {
		this->AddProperty(PlayerProperty::HKx, HK);
		this->SystemMessage("You got " + Int2Str(HK) + " Honor Kill.", RGB(255, 255, 255));
	}

	if (!this->isPortalMode())
		this->ShowHonor();

	this->ChangeHonor(HP, HK, HD, DKPT, DKPW, PLT, PLW, SVT, SVW, RP);
}

int IChar::GetHonorTag() {
	if (this->IsOnline())
		return InterlockedExchangeAdd((volatile LONG *)((int)this->Offset + PlayerProperty::HonorTag), 0);
	return 0;
}

int IChar::isSkinView() {
	if (this->IsOnline())
		return InterlockedExchangeAdd((volatile LONG *)((int)this->Offset + PlayerProperty::SkinView), 0);
	return 0;
}

void IChar::setSkinView(int value) {
	if (this->IsOnline()) {
		InterlockedExchange((volatile LONG *)((int)this->Offset + PlayerProperty::SkinView), value);
		CPlayer::Write(this->GetOffset(), 0xFE, "dd", 174, value);
	}
}

void IChar::SetProperty(const int& Property, const int& Value) {
	if (this->GetType() == 0)
		InterlockedExchange((volatile LONG *)((int)this->Offset + Property), Value);
}


void IChar::AddProperty(const int& Property, const int& Value) {
	if (this->GetType() == 0)
		InterlockedExchangeAdd((volatile LONG *)((int)this->Offset + Property), Value);
}


void IChar::RemoveProperty(const int& Property, const int& Value) {
	if (this->GetType() == 0)
		InterlockedExchangeAdd((volatile LONG *)((int)this->Offset + Property), -Value);
}

void IChar::IncrProperty(const int& Property) {
	if (this->GetType() == 0)
		InterlockedIncrement((volatile LONG *)((int)this->Offset + Property));
}

void IChar::DecrProperty(const int& Property) {
	if (this->GetType() == 0)
		InterlockedDecrement((volatile LONG *)((int)this->Offset + Property));
}

int IChar::GetProperty(const int& Property) {
	if (this->GetType() == 0)
		return InterlockedExchangeAdd((volatile LONG *)((int)this->Offset + Property), 0);
	return 0;
}

bool IChar::IsHide() {
	return (this->GetAdmin() && isSkinView() < 0);
}

void IChar::UpdateHonorTag(int HP) {
	if (this->IsOnline()) {
		int range = 0;

		if (HP >= 2790) range = 1;
		if (HP >= 4960) range = 2;
		if (HP >= 7750) range = 3;
		if (HP >= 12090) range = 4;
		if (HP >= 20150) range = 5;
		if (HP >= 35030) range = 6;
		if (HP >= 44640) range = 7;
		if (HP >= 57970) range = 8;
		if (HP >= 78740) range = 9;
		if (HP >= 111600) range = 10;

		InterlockedExchange((volatile LONG *)((int)this->Offset + PlayerProperty::HonorTag), range);
	}
}

void IChar::ShowHonor(int HP, int HK, int HD, int DKPT, int DKPW, int PLT, int PLW, int SVT, int SVW, int RP, int ToAll)
{
	if (this->IsValid())
	{
		int range = 0, prevrange = 0;
		if (HP >= 2790) range = 1;
		if (HP >= 4960) range = 2;
		if (HP >= 7750) range = 3;
		if (HP >= 12090) range = 4;
		if (HP >= 20150) range = 5;
		if (HP >= 35030) range = 6;
		if (HP >= 44640) range = 7;
		if (HP >= 57970) range = 8;
		if (HP >= 78740) range = 9;
		if (HP >= 111600) range = 10;

		if (range > 0)
			prevrange = range - 1;

		int EPCheck = HonorMessageSysA(this->Offset, range);

		CPlayer::Write(this->GetOffset(), 255, "ddddddddddddddddddd", 245, 0, 0, 0, 0, 0, range, prevrange, HP, HK, HD, DKPW, DKPT, PLW, PLT, SVW, SVT, RP, EPCheck);

		if (ToAll) {
			if (!range && isPeaceEvilMode() == 1 && EPCheck)
				range = 1;

			CChar::WriteInSight(this->GetOffset(), 255, "dddd", 244, this->GetID(), range, EPCheck);
		}
	}
}

void IChar::ShowHonor() {
	this->ShowHonor(this->GetProperty(PlayerProperty::HPx), this->GetProperty(PlayerProperty::HKx), this->GetProperty(PlayerProperty::HDx), this->GetProperty(PlayerProperty::DKPTx), this->GetProperty(PlayerProperty::DKPWx), this->GetProperty(PlayerProperty::PLTx), this->GetProperty(PlayerProperty::PLWx), this->GetProperty(PlayerProperty::SVTx), this->GetProperty(PlayerProperty::SVWx), this->GetProperty(PlayerProperty::RPx), 1);
}

int IChar::IsWarRelated()
{
	if (this->IsOnline())
		return *(DWORD*)((int)this->GetOffset() + 484);
	else
		return 0;
}

void IChar::SetBuffIcon(int Time, int Type, int nMsg, int Key)
{
	if (this->IsOnline() && this->GetType() == 0)
		CPlayer::Write(this->GetOffset(), 0xFF, "dddddd", 243, Time, 5000, Type, nMsg, Key);
}

void IChar::RemoveBuffIcon(int Time, int Type, int nMsg, int Key)
{
	if (this->IsOnline() && this->GetType() == 0)
		CPlayer::Write(this->GetOffset(), 0xFF, "dddddd", 243, Time, 6000, Type, nMsg, Key);
}

int IChar::GetBuffRemain(int BuffID)
{
	int Check = 0;

	if (this->IsOnline() && BuffID >= 0)
	{
		Check = CChar::GetBuffRemain(this->GetOffset(), BuffID);

		if (((BuffID >= 119 && BuffID <= 155) || (BuffID >= 30 && BuffID <= 32) || (BuffID == 99 || BuffID == 101)) && Check > time(0))
			Check = Check - time(0);
		else
		if ((BuffID == 94 || BuffID >= 256) && Check > GetTickCount())
			Check = (Check - GetTickCount()) / 1000;
	}

	return Check;
}

int IChar::_GetBuffRemain(int BuffID)
{
	int Check = 0;

	if (this->IsOnline() && BuffID >= 0)
	{
		Check = _MyGetBuffRemain((int)this->GetOffset(), 0, BuffID);

		if (Check > 0 && ((BuffID >= 119 && BuffID <= 155) || (BuffID >= 1528 && BuffID <= 1530)) && Check > time(0))
			Check = Check - time(0);
		else
		if (Check > 0 && BuffID >= 256 && Check > GetTickCount())
			Check = (Check - GetTickCount()) / 1000;
	}

	return Check;
}

int IChar::GetSkillPoint()
{
	if (this->IsOnline())
		return *(DWORD *)((int)this->GetOffset() + 548);
	else
		return 0;
}

void IChar::RemoveSkillPoint(int amount)
{
	if (this->IsOnline()) {
		if (this->GetSkillPoint() <= amount)
			amount = this->GetSkillPoint();

		*(DWORD *)((int)this->Offset + 548) -= amount;
		CPlayer::Write(this->Offset, 69, "bw", 24, this->GetSkillPoint());
	}
}

void IChar::AddSkillPoint(int amount)
{
	if (this->IsOnline()){
		*(DWORD *)((int)this->Offset + 548) += amount;
		CPlayer::Write(this->Offset, 69, "bw", 24, this->GetSkillPoint());
	}
}

int IChar::GetStatPoint()
{
	if (this->IsOnline())
		return *(DWORD *)((int)this->GetOffset() + 544);
	else
		return 0;
}

void IChar::AddStatPoint(int Amount)
{
	if (this->IsOnline()) {
		*(DWORD *)((int)this->Offset + 544) += Amount;
		CPlayer::Write(this->Offset, 69, "bw", 23, this->GetStatPoint());
	}
}

void IChar::RemoveStatPoint(int Amount)
{
	if (this->IsOnline()) {
		*(DWORD *)((int)this->Offset + 544) -= Amount;
		CPlayer::Write(this->Offset, 69, "bw", 23, this->GetStatPoint());
	}
}

void IChar::IncreaseStat(int amount, int Type)
{
	if (this->IsOnline())
		CPlayer::UpdateProperty((int)this->Offset, Type, 1, amount);
}

void IChar::DecreaseStat(int amount, int Type)
{
	if (this->IsOnline())
		CPlayer::UpdateProperty((int)this->Offset, Type, 0, amount);
}

int IChar::GetStr()
{
	if (this->IsOnline())
		return *(DWORD *)((int)this->GetOffset() + 64);
	else
		return 0;
}

int IChar::GetHth()
{
	if (this->IsOnline())
		return *(DWORD *)((int)this->GetOffset() + 68);
	else
		return 0;
}

int IChar::GetInt()
{
	if (this->IsOnline())
		return *(DWORD *)((int)this->GetOffset() + 72);
	else
		return 0;
}

int IChar::GetWis()
{
	if (this->IsOnline())
		return *(DWORD *)((int)this->GetOffset() + 76);
	else
		return 0;
}

int IChar::GetAgi()
{
	if (this->IsOnline())
		return *(DWORD *)((int)this->GetOffset() + 80);
	else
		return 0;
}

int IChar::GetEva()
{
	if (this->IsOnline())
		return *(DWORD *)((int)this->GetOffset() + 124);
	else
		return 0;
}

int IChar::GetDef()
{
	if (this->IsOnline())
		return *(DWORD *)((int)this->GetOffset() + 144);
	else
		return 0;
}

int IChar::GetRage()
{
	if (this->IsOnline())
		return *(DWORD *)((int)this->GetOffset() + 580);
	else
		return 0;
}

void IChar::IncreaseRage(int amount)
{
	if (this->IsOnline() && amount) {
		CPlayer::UpdateProperty((int)this->Offset, 35, 1, amount);
	}
}

void IChar::DecreaseRage(int amount)
{
	if (this->IsOnline() && amount)
	{
		int oldRage = this->GetRage();
		if (oldRage >= amount) {
			CPlayer::UpdateProperty((int)this->Offset, 35, 0, amount);
		}
	}
}

void IChar::IncreaseHp(int amount)
{
	if (this->IsOnline())
	{
		if (amount <= 0)
			return;

		int OldHp = this->GetCurHp();

		(*(void(__cdecl **)(int, signed int, signed int, int))(*(DWORD*)(int)this->GetOffset() + 88))((int)this->GetOffset(), 7, 1, amount);

		if (this->GetCurHp() < OldHp)
			(*(void(__cdecl **)(int, signed int, signed int, int))(*(DWORD*)(int)this->GetOffset() + 88))((int)this->GetOffset(), 7, 0, amount * 2);
	}
}

void IChar::DecreaseHp(int amount)
{
	if (this->IsOnline())
	{
		if (this->GetCurHp() >= amount) {
			int OldHp = this->GetCurHp();

			(*(void(__cdecl **)(int, signed int, signed int, int))(*(DWORD*)(int)this->GetOffset() + 88))((int)this->GetOffset(), 7, 0, amount);
			if (this->GetCurHp() > OldHp)
				(*(void(__cdecl **)(int, signed int, signed int, int))(*(DWORD*)(int)this->GetOffset() + 88))((int)this->GetOffset(), 7, 1, amount * 2);
		}
	}
}


int IChar::GetObjectListAround(int range)
{
	if (this->IsValid() && this->GetX() > 0 && this->GetY() > 0) {
		return CPlayer::GetObjectAround(*(void **)((int)this->GetOffset() + 320), (int)this->GetOffset() + 324, range);
	}
	else
		return 0;
}
int IChar::GetPlayerListAround(int range)
{
	if (this->IsValid() && this->GetX() > 0 && this->GetY() > 0) {
		return CMonster::GetObjectAround(*(void **)((int)this->GetOffset() + 320), (int)this->GetOffset() + 324, range);
	}
	else
		return 0;
}

int IChar::GetObjectListAround(IChar ITarget, int range)
{
	if (this->IsValid() && this->GetX() > 0 && this->GetY() > 0) {
		return CPlayer::GetObjectAround(*(void **)((int)this->GetOffset() + 320), (int)ITarget.GetOffset() + 324, range);
	}
	else
		return 0;
}

int IChar::GetMonsterListAround(IChar IPlayer, int range)
{
	if (this->IsValid() && IPlayer.IsValid() && this->GetX() > 0 && this->GetY() > 0 && IPlayer.GetX() > 0 && IPlayer.GetY() > 0) {
		return CMonster::GetObjectAround(*(char **)((int)IPlayer.GetOffset() + 320), (int)this->GetOffset() + 324, range);
	}
	else
		return 0;
}

__int64 IChar::GetGStateEx()
{
	if (this->IsOnline())
	{
		__int64 state = 0;
		if (this->IsBuff(283)) state += 1;
		if (this->IsBuff(299)) state += 2;
		if (this->IsBuff(307)) state += 8;
		if (this->IsBuff(329)) state += 16;
		if (this->IsBuff(358)) state += 32;
		if (this->IsBuff(356)) state += 64;
		if (this->IsBuff(357)) state += 128;
		if (this->IsBuff(346)) state += 256;
		if (this->IsBuff(333)) state += 1024;
		if (this->IsBuff(327)) state += 2048;
		if (this->IsBuff(348)) state += 32768;
		if (this->IsBuff(350)) state += 65536;
		if (this->IsBuff(342)) state += 131072;
		if (this->IsBuff(339)) state += 262144;
		if (this->IsBuff(406)) state += __int64(16384) << 32;
		return state;
	}
	else {
		return 0;
	}
}

__int64 IChar::_GetGStateEx()
{
	if (this->IsOnline())
	{
		__int64 state = 0;
		if (this->_IsBuff(283)) state += 1;
		if (this->_IsBuff(299)) state += 2;
		if (this->_IsBuff(307)) state += 8;
		if (this->_IsBuff(329)) state += 16;
		if (this->_IsBuff(358)) state += 32;
		if (this->_IsBuff(356)) state += 64;
		if (this->_IsBuff(357)) state += 128;
		if (this->_IsBuff(346)) state += 256;
		if (this->_IsBuff(333)) state += 1024;
		if (this->_IsBuff(327)) state += 2048;
		if (this->_IsBuff(348)) state += 32768;
		if (this->_IsBuff(350)) state += 65536;
		if (this->_IsBuff(342)) state += 131072;
		if (this->_IsBuff(339)) state += 262144;
		if (this->_IsBuff(406)) state += __int64(16384) << 32;
		return state;
	}
	else {
		return 0;
	}
}

bool IChar::IsGStateEx(__int64 state)
{
	if (this->IsOnline())
	{
		if (this->GetGStateEx() & state)
			return true;
	}

	return false;
}

void IChar::SendGStateExIceArrow(__int64 state)
{
	if (this->IsValid() && !this->isPortalMode() && !CChar::IsMState((int)this->Offset, 0x80000))
	{
		if (this->IsBuff(159))
			CChar::WriteInSight(this->GetOffset(), 148, "dId", this->GetID(), (__int64)0, this->GetSpeed());

		if (!this->IsBuff(159))
			CChar::WriteInSight(this->GetOffset(), 148, "dId", this->GetID(), state, this->GetSpeed());
	}
}

void IChar::SendGStateEx(__int64 state)
{
	if (this->IsValid() && !this->isPortalMode() && !CChar::IsMState((int)this->Offset, 0x80000))
	{
		if (this->IsBuff(159))
			CChar::WriteInSight(this->GetOffset(), 148, "dId", this->GetID(), (__int64)0, this->GetSpeed());

		if (!this->IsBuff(159) && !this->IsBuff(290) && !this->IsBuff(291) && !this->IsBuff(292) && !this->IsBuff(293) && !this->IsBuff(294) && !this->IsBuff(295))
			CChar::WriteInSight(this->GetOffset(), 148, "dId", this->GetID(), state, this->GetSpeed());
	}
}

void IChar::_SendGStateEx(__int64 state)
{
	if (this->IsValid() && !this->isPortalMode())
	{
		if (this->_IsBuff(159))
			CChar::WriteInSight(this->GetOffset(), 148, "dId", this->GetID(), (__int64)0, this->GetSpeed());

		if (!this->_IsBuff(159) && !this->_IsBuff(290) && !this->_IsBuff(291) && !this->_IsBuff(292) && !this->_IsBuff(293) && !this->_IsBuff(294) && !this->_IsBuff(295))
			CChar::WriteInSight(this->GetOffset(), 148, "dId", this->GetID(), state, this->GetSpeed());
	}
}

int IChar::CheckHit(IChar Target, int value)
{
	if (this->IsOnline() && this->IsValid() && Target.IsOnline())
	{
		if (CChar::CheckHit(this->GetOffset(), Target.GetOffset(), value))
			return 1;

		return 0;
	}
	else {
		return 0;
	}
}

void IChar::CouldntExecuteSkill()
{
	if (this->IsValid() && !this->isPortalMode())
		CChar::WriteInSight(this->GetOffset(), 61, "db", *(DWORD *)((int)this->GetOffset() + 28), 0);
}

void IChar::_CouldntExecuteSkill()
{
	if (this->IsValid() && !this->isPortalMode())
		CChar::WriteInSight(this->GetOffset(), 61, "db", *(DWORD *)((int)this->GetOffset() + 28), 0);
}

int IChar::GetAttack()
{
	if (this->IsOnline())
		return CChar::GetAttack(this->GetOffset());
	else
		return 0;
}

int IChar::_ShowBattleMiss(IChar Target, int skillID)
{
	if (this->IsOnline() && this->IsValid() && Target.IsValid())
	{
		(*(void(__thiscall **)(int, int))(*(DWORD*)Target.GetOffset() + 80))((int)Target.GetOffset(), (int)this->GetOffset());

		if (Target.IsBuff(159))
			return 0;
		else if (Target.IsBuff(24) || CChar::IsGState((int)Target.GetOffset(), 8192))
			return 0;
		else if (!CChar::IsGState((int)this->GetOffset(), 128) && !CChar::IsGState((int)this->GetOffset(), 1024) && CSMap::IsOnTile(*(void **)((int)this->GetOffset() + 320), (int)this->GetOffset() + 332, 131072) || !CChar::IsGState((int)this->GetOffset(), 128) && !CChar::IsGState((int)this->GetOffset(), 1024) && *(DWORD*)((int)this->GetOffset() + 28) == Target.GetID())
			return 0;
		else
			return CChar::WriteInSight(this->GetOffset(), 0x3f, "bddbbwwbd", skillID, this->GetID(), Target.GetID(), Target.GetType(), 1, 0, 0, false, 0);
	}
	else {
		return 0;
	}
}


int IChar::__ShowBattleMiss(IChar Target, int skillID)
{
	if (this->IsOnline() && this->IsValid() && Target.IsValid())
	{
		(*(void(__thiscall **)(int, int))(*(DWORD*)Target.GetOffset() + 80))((int)Target.GetOffset(), (int)this->GetOffset());

		if (Target.IsBuff(159))
			return 0;
		else if (Target.IsBuff(24) || CChar::IsGState((int)Target.GetOffset(), 8192))
			return 0;
		else if (!CChar::IsGState((int)this->GetOffset(), 128) && !CChar::IsGState((int)this->GetOffset(), 1024) && CSMap::IsOnTile(*(void **)((int)this->GetOffset() + 320), (int)this->GetOffset() + 332, 131072) || !CChar::IsGState((int)this->GetOffset(), 128) && !CChar::IsGState((int)this->GetOffset(), 1024) && *(DWORD*)((int)this->GetOffset() + 28) == Target.GetID())
			return 0;
		else
			return CChar::WriteInSight(this->GetOffset(), 0x3f, "bddbbwwbd", skillID, this->GetID(), Target.GetID(), Target.GetType(), 1, 0, 0, false, 0);
	}
	else {
		return 0;
	}
}

void IChar::SetDirection(IChar Target)
{
	if (this->IsOnline() && this->IsValid() && Target.IsOnline())
		CChar::SetDirection(this->GetOffset(), *(DWORD *)((int)Target.GetOffset() + 332) - *(DWORD *)((int)this->GetOffset() + 332), *(DWORD *)((int)Target.GetOffset() + 336) - *(DWORD *)((int)this->GetOffset() + 336));
}

int IChar::OktayDamageNoAgro(IChar Target, int Damage, int SkillID)
{
	if (Damage <= 0)
		return 0;

	bool GiveCrit = false;

	if (this->IsOnline() && this->IsValid() && Target.IsValid())
	{
		if ((int)this->GetOffset() == (int)Target.GetOffset())
			return 0;

		if (Target.IsBuff(162))
			return 0;

		if (Target.IsBuff(163))
			return 0;

		if (!(*(int(__thiscall **)(int, int, DWORD))(*(DWORD *)this->GetOffset() + 176))((int)this->GetOffset(), (int)Target.GetOffset(), 0)) {
			this->CouldntExecuteSkill();
			return 0;
		}

		int CheckDmg = this->GetDamage(SkillID, Target.GetOffset());
		if (CheckDmg)
			Damage = CheckDmg;

		if (Target.GetType() == 0)
		{
			if (Target.IsBuff(284) && Damage > 10)
				Damage = Damage / 10;
		}

		if (Target.GetType() == 0)
		{
			if (Target.IsBuff(283) && Damage > 10)
				Damage = ((Damage * 6) / 10);
		}

		if (Target.GetType() == 0)
		{
			if (Target.IsBuff(122) && Damage)
				Damage = ((Damage * 88) / 100);
		}

		if (CChar::GetRange((int)this->GetOffset() + 332, (int)Target.GetOffset() + 332) > 300)
			return 0;

		if (this->GetMap() != Target.GetMap())
			return 0;

		if (this->GetClass() == 3 && !this->IsBuff(25) && !this->IsBuff(50))
		{
			int Crit = *((DWORD*)((int)this->GetOffset() + 624) + 4 + 2);
			int CritDamage = *((DWORD*)((int)this->GetOffset() + 624) + 5 + 2);
			int Rate = 950;

			if (Crit)
				Rate -= *(DWORD*)((int)Crit + 8) * 3;

			if (CritDamage && Damage >= 100)
				Damage += (Damage * *(DWORD*)((int)CritDamage + 8)) / 100;

			if ((int)CTools::Rate(1, 1000) >= Rate)
			{
				Damage *= 2;
				GiveCrit = true;
			}
		}

		if ((*(int(__thiscall **)(void*))(*(DWORD *)(int)Target.GetOffset() + 0x40))(Target.GetOffset()))
			*(DWORD*)((unsigned)(int)Target.GetOffset() + 0x1d8) = GetTickCount() + 20000;

		if (Target.IsBuff(24) || CChar::IsGState((int)Target.GetOffset(), 8192))
			return 0;

		if (!CChar::IsGState((int)this->GetOffset(), 128) && !CChar::IsGState((int)this->GetOffset(), 1024) && CSMap::IsOnTile(*(void **)((int)this->GetOffset() + 320), (int)this->GetOffset() + 332, 131072) || !CChar::IsGState((int)this->GetOffset(), 128) && !CChar::IsGState((int)this->GetOffset(), 1024) && *(DWORD*)((int)this->GetOffset() + 28) == Target.GetID())
			return 0;

		if (Target.IsBuff(159) || (Target.IsBuff(327) && !Target.IsBuff(11) && !Target.IsBuff(339) && !Target.IsBuff(348) && !Target.IsBuff(350)) || (Target.IsBuff(329) && !Target.IsBuff(11) && !Target.IsBuff(339) && !Target.IsBuff(348) && !Target.IsBuff(350)))
			return 0;

		if (!this->IsBuff(306) && this->GetClass() == 1 && (this->GetLevel() + GetLevelDiff() <= Target.GetLevel()))
			return this->_ShowBattleMiss(Target, SkillID);

		if (this->GetClass() == 4 && (this->GetLevel() + GetLevelDiff() <= Target.GetLevel()))
			return this->_ShowBattleMiss(Target, SkillID);

		if (Target.GetCurHp() < 1)
			*(DWORD *)((int)Target.GetOffset() + 272) = 1;

		if (Target.GetCurHp() == 1)
			return 0;

		if (Damage >= Target.GetCurHp())
			Damage = Target.GetCurHp() - 1;

		*(DWORD *)((int)Target.GetOffset() + 272) = Target.GetCurHp() - Damage;
		(*(void(__thiscall **)(int, int))(*(DWORD*)Target.GetOffset() + 80))((int)Target.GetOffset(), (int)this->GetOffset());

		int SPDmg = 0;
		if (Target.GetType() == 1 && Damage > 1) {
			SPDmg = SoulPocketDamage(Offset, Damage);
			Damage = Damage - SPDmg;
		}

		if (this->GetType() == 0 && isInMacroMap(this->GetX() >> 13, this->GetY() >> 13))
			*(DWORD *)((int)Offset + 1464) = GetTickCount();

		if (GiveCrit == true)
			CChar::WriteInSight(this->GetOffset(), 63, "bddbbwwbd", SkillID, this->GetID(), Target.GetID(), 1, 1, Damage, 0, Target.GetType() + 2, SPDmg);
		else
			CChar::WriteInSight(this->GetOffset(), 10, "bbddddd", Target.GetType(), SkillID, this->GetID(), Target.GetID(), Damage, 0, SPDmg);

		return Damage;
	}
	else {
		return 0;
	}
}

int IChar::OktayDamageSingle(IChar Target, int Damage, int SkillID)
{
	if (Damage <= 0)
		return 0;

	if (this->IsOnline() && this->IsValid() && Target.IsValid())
	{
		if ((int)this->GetOffset() == (int)Target.GetOffset())
			return 0;

		if (CChar::GetRange((int)this->GetOffset() + 332, (int)Target.GetOffset() + 332) > 300)
			return 0;

		if (this->GetMap() != Target.GetMap())
			return 0;

		if (!(*(int(__thiscall **)(int, int, DWORD))(*(DWORD *)this->GetOffset() + 176))((int)this->GetOffset(), (int)Target.GetOffset(), 0)) {
			this->CouldntExecuteSkill();
			return 0;
		}

		if (Target.IsBuff(24) || CChar::IsGState((int)Target.GetOffset(), 8192))
			return 0;

		if (!CChar::IsGState((int)this->GetOffset(), 128) && !CChar::IsGState((int)this->GetOffset(), 1024) && CSMap::IsOnTile(*(void **)((int)this->GetOffset() + 320), (int)this->GetOffset() + 332, 131072) || !CChar::IsGState((int)this->GetOffset(), 128) && !CChar::IsGState((int)this->GetOffset(), 1024) && *(DWORD*)((int)this->GetOffset() + 28) == Target.GetID())
			return 0;

		if (Target.IsBuff(159) || (Target.IsBuff(327) && !Target.IsBuff(11) && !Target.IsBuff(339) && !Target.IsBuff(348) && !Target.IsBuff(350)) || (Target.IsBuff(329) && !Target.IsBuff(11) && !Target.IsBuff(339) && !Target.IsBuff(348) && !Target.IsBuff(350)))
			return 0;

		if (!this->IsBuff(306) && this->GetClass() == 1 && (this->GetLevel() + GetLevelDiff() <= Target.GetLevel()))
			return this->_ShowBattleMiss(Target, SkillID);

		if (this->GetClass() == 4 && (this->GetLevel() + GetLevelDiff() <= Target.GetLevel()))
			return this->_ShowBattleMiss(Target, SkillID);

		if (this->GetClass() == 1 && SkillID == 74)
			Target.Buff(8, 2, 0);

		int CheckDmg = this->GetDamage(SkillID, Target.GetOffset());
		if (CheckDmg)
			Damage = CheckDmg;

		if (this->IsValid() && this->GetClass() == 4 && this->GetSpecialty() == 23 && Damage)
		{
			int pSkill = this->GetSkillPointer(49);
			if (pSkill) Damage += (*(DWORD*)(pSkill + 8) * 50);
		}
		unsigned int GetAttackSpeed = CChar::GetASpeed((int)this->GetOffset());
		unsigned int GetASpeedValue = GetAttackSpeed;
		int NormalDamage = 0, DamageArgument = 0, EBDamage = 0, Check = 0, TypeKind = 0, GetType = 0;
		TypeKind = (*(int(__thiscall **)(LONG, void *))(*(DWORD *)Target.GetOffset() + 148))((int)Target.GetOffset(), this->GetOffset());

		if ((this->GetClass() == 1 && SkillID == 67))
			EBDamage = 0;
		else if (SkillID == 115)
			EBDamage = 0;
		else
			EBDamage = GetASpeedValue * (*(int(__thiscall **)(void *, LONG))(*(DWORD *)this->GetOffset() + 168))(this->GetOffset(), (int)Target.GetOffset()) / GetAttackSpeed;

		Check = (*(int(__thiscall**)(LONG, void*, unsigned int, int*, int*, int*, DWORD))(*(DWORD*)Target.GetOffset() + 72))((int)Target.GetOffset(), this->GetOffset(), GetASpeedValue * Damage / GetAttackSpeed, &NormalDamage, &DamageArgument, &EBDamage, 0);
		GetType = Check | 2 * DamageArgument | 4 * TypeKind;
		int MaxDmg = NormalDamage;

		int SPDmg = 0;
		if (Target.GetType() == 1 && NormalDamage > 1) {
			SPDmg = SoulPocketDamage(Offset, NormalDamage + EBDamage);
			MaxDmg = MaxDmg - SPDmg;
		}

		CChar::WriteInSight(this->GetOffset(), 63, "bddbbwwbd", SkillID, this->GetID(), Target.GetID(), 1, 1, MaxDmg, EBDamage, GetType, SPDmg);

		if (this->GetType() == 0 && isInMacroMap(this->GetX() >> 13, this->GetY() >> 13))
			*(DWORD *)((int)Offset + 1464) = GetTickCount();

		return NormalDamage;
	}
	else {
		return 0;
	}
}

void IChar::OktayDamageArea(IChar Target, int Damage, int SkillID)
{
	if (Damage <= 0)
		return;

	if (this->IsValid() && Target.IsValid())
	{
		if ((int)this->GetOffset() == (int)Target.GetOffset())
			return;

		if (CChar::GetRange((int)this->GetOffset() + 332, (int)Target.GetOffset() + 332) > 300)
			return;

		if (this->GetMap() != Target.GetMap())
			return;

		if (!(*(int(__thiscall **)(int, int, DWORD))(*(DWORD *)this->GetOffset() + 176))((int)this->GetOffset(), (int)Target.GetOffset(), 0)) {
			this->CouldntExecuteSkill();
			return;
		}

		if (Target.IsBuff(24) || CChar::IsGState((int)Target.GetOffset(), 8192))
			return;

		if (!CChar::IsGState((int)this->GetOffset(), 128) && !CChar::IsGState((int)this->GetOffset(), 1024) && CSMap::IsOnTile(*(void **)((int)this->GetOffset() + 320), (int)this->GetOffset() + 332, 131072) || !CChar::IsGState((int)this->GetOffset(), 128) && !CChar::IsGState((int)this->GetOffset(), 1024) && *(DWORD*)((int)this->GetOffset() + 28) == Target.GetID())
			return;

		if (Target.IsBuff(159) || (Target.IsBuff(327) && !Target.IsBuff(11) && !Target.IsBuff(339) && !Target.IsBuff(348) && !Target.IsBuff(350)) || (Target.IsBuff(329) && !Target.IsBuff(11) && !Target.IsBuff(339) && !Target.IsBuff(348) && !Target.IsBuff(350)))
			return;

		if (!this->IsBuff(306) && this->GetClass() == 1 && (this->GetLevel() + GetLevelDiff() <= Target.GetLevel()))
			return;

		if (this->GetClass() == 4 && SkillID != 22 && (this->GetLevel() + GetLevelDiff() <= Target.GetLevel()))
			return;

		if (this->GetClass() == 1 && SkillID == 66)
			Target.Buff(0, 5, -100);

		int CheckDmg = this->GetDamage(SkillID, Target.GetOffset());
		if (CheckDmg)
			Damage = CheckDmg;

		if (this->IsValid() && this->GetClass() == 4 && this->GetSpecialty() == 23 && Damage)
		{
			int pSkill = this->GetSkillPointer(49);
			if (pSkill) Damage += (*(DWORD*)(pSkill + 8) * 50);
		}

		if (SkillID == 38) {
			int perc = (Damage * 5) / 100;
			Damage += perc * this->GetDeathBlow();
		}

		unsigned int GetAttackSpeed = CChar::GetASpeed((int)this->GetOffset());
		unsigned int GetASpeedValue = GetAttackSpeed;
		int NormalDamage = 0, DamageArgument = 0, EBDamage = 0, Check = 0, TypeKind = 0, GetType = 0;
		TypeKind = (*(int(__thiscall **)(LONG, void *))(*(DWORD *)Target.GetOffset() + 148))((int)Target.GetOffset(), this->GetOffset());

		if ((this->GetClass() == 1 && SkillID == 67))
			EBDamage = 0;
		else
			EBDamage = GetASpeedValue * (*(int(__thiscall **)(void *, LONG))(*(DWORD *)this->GetOffset() + 168))(this->GetOffset(), (int)Target.GetOffset()) / GetAttackSpeed;

		Check = (*(int(__thiscall**)(LONG, void*, unsigned int, int*, int*, int*, DWORD))(*(DWORD*)Target.GetOffset() + 72))((int)Target.GetOffset(), this->GetOffset(), GetASpeedValue * Damage / GetAttackSpeed, &NormalDamage, &DamageArgument, &EBDamage, 0);
		GetType = Check | 2 * DamageArgument | 4 * TypeKind;
		int MaxDmg = NormalDamage;

		int SPDmg = 0;
		if (Target.GetType() == 1 && NormalDamage > 1) {
			SPDmg = SoulPocketDamage(Offset, MaxDmg);
			MaxDmg = MaxDmg - SPDmg;
		}

		CChar::WriteInSight(this->GetOffset(), 10, "bbddddd", GetType, SkillID, this->GetID(), Target.GetID(), MaxDmg, EBDamage, SPDmg);

		if (this->GetType() == 0 && isInMacroMap(this->GetX() >> 13, this->GetY() >> 13))
			*(DWORD *)((int)Offset + 1464) = GetTickCount();

	}
}

void IChar::XEAMagDamageArea(IChar Target, int Damage, int Skill)
{
	if (Damage <= 0 || !Skill)
		return;

	if (this->IsValid() && Target.IsValid() && (**(int(__thiscall ***)(void *, int, int))Skill)((void*)Skill, (int)this->Offset, (int)Target.GetOffset()))
	{
		int SkillID = *(DWORD*)(Skill + 4);

		if ((int)this->GetOffset() == (int)Target.GetOffset())
			return;

		if (CChar::GetRange((int)this->GetOffset() + 332, (int)Target.GetOffset() + 332) > 300)
			return;

		if (this->GetMap() != Target.GetMap())
			return;

		if (Target.IsBuff(24) || CChar::IsGState((int)Target.GetOffset(), 8192))
			return;

		if (!CChar::IsGState((int)this->GetOffset(), 128) && !CChar::IsGState((int)this->GetOffset(), 1024) && CSMap::IsOnTile(*(void **)((int)this->GetOffset() + 320), (int)this->GetOffset() + 332, 131072) || !CChar::IsGState((int)this->GetOffset(), 128) && !CChar::IsGState((int)this->GetOffset(), 1024) && *(DWORD*)((int)this->GetOffset() + 28) == Target.GetID())
			return;

		if (Target.IsBuff(159) || (Target.IsBuff(327) && !Target.IsBuff(11) && !Target.IsBuff(339) && !Target.IsBuff(348) && !Target.IsBuff(350)) || (Target.IsBuff(329) && !Target.IsBuff(11) && !Target.IsBuff(339) && !Target.IsBuff(348) && !Target.IsBuff(350)))
			return;

		if (!this->IsBuff(306) && this->GetClass() == 1 && (this->GetLevel() + GetLevelDiff() <= Target.GetLevel()))
			return;

		if (this->GetClass() == 4 && SkillID != 22 && (this->GetLevel() + GetLevelDiff() <= Target.GetLevel()))
			return;

		if (this->GetClass() == 1 && SkillID == 66)
			Target.Buff(0, 5, -100);

		int CheckDmg = this->GetDamage(SkillID, Target.GetOffset());
		if (CheckDmg)
			Damage = CheckDmg;

		if (this->IsValid() && this->GetClass() == 4 && this->GetSpecialty() == 23 && Damage)
		{
			int pSkill = this->GetSkillPointer(49);
			if (pSkill) Damage += (*(DWORD*)(pSkill + 8) * 50);
		}

		if (SkillID == 38) {
			int perc = (Damage * 5) / 100;
			Damage += perc * this->GetDeathBlow();
		}

		int DMGCalcul = Damage * (*(int(__thiscall **)(void *, LONG))(*(DWORD *)this->GetOffset() + 168))(this->GetOffset(), (int)Target.GetOffset());
		int MagDmg = DMGCalcul / (*(int(__thiscall **)(void *, int))(*(DWORD *)Skill + 36))((void*)Skill, (int)this->Offset);
		int v25 = CSkill::MageCalculation((void*)Skill, (int)this->Offset, (int)Target.GetOffset());
		int v23 = (*(int(__thiscall **)(void *, int, int))(*(DWORD *)Skill + 20))((void*)Skill, (int)this->Offset, CChar::GetMagic(this->Offset));
		int dmgReduce = Damage * (v25 * v23 / 100);
		int v21 = 0;
		int v19 = 0;
		int v22 = (*(int(__thiscall **)(void *, int, int *, int *, int *, void *))(*(DWORD *)Skill + 36))((void*)Skill, (int)this->Offset, &v21, &v19, (int *)&MagDmg, (void*)Skill);
		int Check = (*(int(__thiscall **)(int, int, unsigned int))(*(DWORD *)Target.GetOffset() + 72))((int)Target.GetOffset(), (int)this->Offset, dmgReduce / v22);

		if (!Check)
			(*(void(__thiscall **)(void *, int))(*(DWORD *)Target.GetOffset() + 80))(Target.GetOffset(), (int)this->Offset);

		(*(void(__thiscall **)(void *, int))(*(DWORD *)Target.GetOffset() + 56))(Target.GetOffset(), (int)this->Offset);

		int MaxDmg = v21;

		int SPDmg = 0;
		if (Target.GetType() == 1 && MaxDmg > 1) {
			SPDmg = SoulPocketDamage(Offset, MaxDmg);
			MaxDmg = MaxDmg - SPDmg;
		}
		int GetType = (*(int(__thiscall **)(void*, int, int))(*(DWORD *)Skill + 96))((void*)Skill, (int)this->Offset, (int)Target.GetOffset());
		//CChar::WriteInSight(this->GetOffset(), 0x3f, "bddbbwwbd", SkillID, this->GetID(), Target.GetID(), Target.GetType(), *(DWORD*)(Skill + 8), MaxDmg, MagDmg, Check, SPDmg);

		CChar::WriteInSight(this->GetOffset(), 10, "bbddddd", GetType, SkillID, this->GetID(), Target.GetID(), MaxDmg, MagDmg, SPDmg);

		(*(void(__thiscall **)(void *, int, void *, int, int, int))(*(DWORD *)Skill + 84))((void*)Skill, (int)this->Offset, Target.GetOffset(), Damage, v25, v23);

		if (this->GetType() == 0 && isInMacroMap(this->GetX() >> 13, this->GetY() >> 13))
			*(DWORD *)((int)Offset + 1464) = GetTickCount();

	}
}

void IChar::PlayerMessage(char* MessageName, char* PlayerMessage)
{
	if (this->IsOnline())
		CPlayer::Write(this->GetOffset(), 60, "ss", MessageName, PlayerMessage);
}

void IChar::OktayDamageStorm(IChar Target, int Damage)
{
	if (Damage <= 0)
		return;

	if (this->IsOnline() && this->IsValid() && Target.IsValid())
	{
		if (CChar::GetRange((int)this->GetOffset() + 332, (int)Target.GetOffset() + 332) > 300)
			return;

		if (this->GetMap() != Target.GetMap())
			return;

		if (Target.IsBuff(24) || CChar::IsGState((int)Target.GetOffset(), 8192))
			return;

		if (!CChar::IsGState((int)this->GetOffset(), 128) && !CChar::IsGState((int)this->GetOffset(), 1024) && CSMap::IsOnTile(*(void **)((int)this->GetOffset() + 320), (int)this->GetOffset() + 332, 131072) || !CChar::IsGState((int)this->GetOffset(), 128) && !CChar::IsGState((int)this->GetOffset(), 1024) && *(DWORD*)((int)this->GetOffset() + 28) == Target.GetID())
			return;

		if (Target.IsBuff(159) || (Target.IsBuff(327) && !Target.IsBuff(11) && !Target.IsBuff(339) && !Target.IsBuff(348) && !Target.IsBuff(350)) || (Target.IsBuff(329) && !Target.IsBuff(11) && !Target.IsBuff(339) && !Target.IsBuff(348) && !Target.IsBuff(350)))
			return;

		if (!this->IsBuff(306) && this->GetClass() == 1 && (this->GetLevel() + GetLevelDiff() <= Target.GetLevel()))
			return;

		if (this->GetClass() == 4 && (this->GetLevel() + GetLevelDiff() <= Target.GetLevel()))
			return;

		unsigned int GetAttackSpeed = CChar::GetASpeed((int)this->GetOffset());
		unsigned int GetASpeedValue = GetAttackSpeed;
		int NormalDamage = 0, DamageArgument = 0, EBDamage = 0, Check = 0, TypeKind = 0, GetType = 0;
		TypeKind = (*(int(__thiscall **)(LONG, void *))(*(DWORD *)Target.GetOffset() + 148))((int)Target.GetOffset(), this->GetOffset());
		Check = (*(int(__thiscall**)(LONG, void*, unsigned int, int*, int*, int*, DWORD))(*(DWORD*)Target.GetOffset() + 72))((int)Target.GetOffset(), this->GetOffset(), GetASpeedValue * Damage / GetAttackSpeed, &NormalDamage, &DamageArgument, &EBDamage, 0);
		GetType = Check | 2 * DamageArgument | 4 * TypeKind;

		int SPDmg = 0;
		if (Target.GetType() == 1 && NormalDamage > 1) {
			SPDmg = SoulPocketDamage(Offset, NormalDamage);
			NormalDamage = NormalDamage - SPDmg;
		}
		CChar::WriteInSight(this->GetOffset(), 10, "bbddddd", GetType, 500, this->GetID(), Target.GetID(), NormalDamage, 0, SPDmg);

		if ((*(int(__thiscall **)(void*))(*(DWORD *)(int)Target.GetOffset() + 0x40))(Target.GetOffset()))
			*(DWORD*)((unsigned)(int)Target.GetOffset() + 0x1d8) = GetTickCount() + 20000;

		if (this->GetType() == 0 && isInMacroMap(this->GetX() >> 13, this->GetY() >> 13))
			*(DWORD *)((int)Offset + 1464) = GetTickCount();

		Target.DecreaseHp(0);
	}
	else {
		return;
	}
}


int IChar::GetDeathBlow()
{
	if (this->IsOnline())
		return *(DWORD*)((int)this->GetOffset() + 184);
	else
		return 0;
}

void IChar::AddDeathBlow(int amount)
{
	if (this->IsOnline())
	{
		if (amount <= 0)
			return;

		if (this->GetDeathBlow() < 5) {
			int CurDeath = this->GetDeathBlow();

			if (!this->validateStat(CurDeath, 1, amount))
				return;

			(*(void(__cdecl **)(int, DWORD, signed int, signed int))(*(DWORD *)(int)(this->GetOffset()) + 92))((int)(this->GetOffset()), 36, 1, amount);
			if (this->GetDeathBlow() < CurDeath)
				(*(void(__cdecl **)(int, DWORD, signed int, signed int))(*(DWORD *)(int)(this->GetOffset()) + 92))((int)(this->GetOffset()), 36, 0, amount * 2);
		}
	}
}

void IChar::RemoveDeathBlow(int amount)
{
	if (this->IsOnline())
	{
		if (amount <= 0)
			return;

		int CurDeath = this->GetDeathBlow();

		if (this->GetDeathBlow() - amount <= 0)
			amount = this->GetDeathBlow();

		if (!this->validateStat(CurDeath, 0, amount))
			return;

		(*(void(__cdecl **)(int, DWORD, signed int, signed int))(*(DWORD *)(int)this->GetOffset() + 92))((int)this->GetOffset(), 36, 0, amount);
		if (this->GetDeathBlow() > CurDeath)
			(*(void(__cdecl **)(int, DWORD, signed int, signed int))(*(DWORD *)(int)this->GetOffset() + 92))((int)this->GetOffset(), 36, 1, amount * 2);
	}
}

int IChar::IsInRange(IChar Target, int maxRange)
{
	if (this->IsOnline() && Target.IsOnline())
	{
		if (CChar::GetRange((int)this->GetOffset() + 324, (int)Target.GetOffset() + 324) <= maxRange)
			return 1;
	}

	return 0;
}

void IChar::AddAbsorb(int amount)
{
	if (this->IsOnline())
		(*(int(__cdecl **)(int, signed int, signed int, DWORD, DWORD))(*(DWORD *)(int)this->GetOffset() + 92))((int)this->GetOffset(), 16, 1, amount, amount);
}

void IChar::RemoveAbsorb(int amount)
{
	if (this->IsOnline())
		(*(int(__cdecl **)(int, signed int, signed int, DWORD, DWORD))(*(DWORD *)(int)this->GetOffset() + 92))((int)this->GetOffset(), 16, 0, amount, amount);
}

int IChar::GetMagic()
{
	if (this->IsOnline())
		return CChar::GetMagic(this->GetOffset());
	else
		return 0;
}

int IChar::IsMoved(int x, int y)
{
	if (this->IsOnline() && this->IsValid())
	{
		if (x == this->GetX() && y == this->GetY())
			return 0;

		return true;
	}
	else {
		return 0;
	}
}

DWORD IChar::UnAttack(DWORD amount)
{
	if (this->IsOnline() && this->IsValid())
	{
		if (amount)
			return *(DWORD *)((int)this->GetOffset() + 468) = GetTickCount() + amount;
		else
			return *(DWORD *)((int)this->GetOffset() + 468) = 0;
	}
	else {
		return 0;
	}
}

DWORD IChar::Delay(DWORD amount)
{
	if (this->IsOnline() && this->IsValid())
	{
		if (amount)
			return *(DWORD *)((int)this->GetOffset() + 556) = GetTickCount() + amount;
		else
			return *(DWORD *)((int)this->GetOffset() + 556) = 0;
	}
	else {
		return 0;
	}
}

void IChar::MonsterSummonWrite(int SafeZoneCheck, int Monster, int CellMapCoordinate)
{
	if (this->IsOnline())
	{
		void* v3 = (void*)Monster;
		if (SafeZoneCheck)
		{
			if (!CSMap::IsOnTile(*(void **)(Monster + 320), Monster + 332, 131072) && Undefined::CellMapCheck(*(void **)(Monster + 320), Monster, (int)CellMapCoordinate))
			{
				(*(void(__thiscall **)(int, DWORD))(*(DWORD *)Monster + 196))(Monster, 0);
				CChar::WriteInSight((void*)Monster, 51, "wdddwddIIsbdsIIbd", *(DWORD *)(*(DWORD *)(Monster + 440) + 60), *(DWORD*)(Monster + 28), *(DWORD *)(Monster + 332), *(DWORD *)(Monster + 336), *(DWORD *)(Monster + 348), *(DWORD *)(Monster + 272), CChar::GetMaxHp(Monster), *(DWORD *)(Monster + 280), (unsigned __int64)*(DWORD *)(Monster + 288), *(DWORD *)(Monster + 292), (*(int(__thiscall **)(int))(*(DWORD *)Monster + 224))(Monster), *(DWORD *)(*(DWORD *)(Monster + 440) + 64) | 0x80, *(DWORD *)(Monster + 524), (*(int(__thiscall **)(int))(*(DWORD *)Monster + 240))(Monster), (__int64)0, (__int64)0, 0, this->GetChannel());

				CChar::Unlock(v3);
			}
			else {
				CChar::Unlock(v3);
				if (Monster)
					(**(void(__thiscall ***)(DWORD, DWORD))Monster)(Monster, 1);
			}
		}
		else {
			if (Undefined::CellMapCheck(*(void **)(Monster + 320), Monster, (int)CellMapCoordinate))
			{
				(*(void(__thiscall **)(int, DWORD))(*(DWORD *)Monster + 196))(Monster, 0);
				CChar::WriteInSight((void*)Monster, 51, "wdddwddIIsbdsIIbd", *(DWORD *)(*(DWORD *)(Monster + 440) + 60), *(DWORD*)(Monster + 28), *(DWORD *)(Monster + 332), *(DWORD *)(Monster + 336), *(DWORD *)(Monster + 348), *(DWORD *)(Monster + 272), CChar::GetMaxHp(Monster), *(DWORD *)(Monster + 280), (unsigned __int64)*(DWORD *)(Monster + 288), *(DWORD *)(Monster + 292), (*(int(__thiscall **)(int))(*(DWORD *)Monster + 224))(Monster), *(DWORD *)(*(DWORD *)(Monster + 440) + 64) | 0x80, *(DWORD *)(Monster + 524), (*(int(__thiscall **)(int))(*(DWORD *)Monster + 240))(Monster), (__int64)0, (__int64)0, 0, this->GetChannel());
				CChar::Unlock(v3);
			}
			else {
				CChar::Unlock(v3);
				if (Monster)
					(**(void(__thiscall ***)(DWORD, DWORD))Monster)(Monster, 1);
			}
		}
	}
}

int IChar::GetMobTanker()
{
	if (this->IsValid())
		return *(DWORD*)((int)this->GetOffset() + 464);
	else
		return 0;
}

int IChar::GetMaxHp()
{
	if (this->IsOnline())
		return CChar::GetMaxHp((int)this->Offset);
	else
		return 0;
}

int IChar::GetMaxMp()
{
	if (this->IsOnline())
		return CChar::GetMaxMp((int)this->Offset);
	else
		return 0;
}

void IChar::OpenHTML(int html)
{
	if (this->IsOnline())
		CPlayer::Write(this->Offset, 74, "d", html);
}

void IChar::OpenWindow(std::string WindowName, int Type, int Time)
{
	if (this->IsOnline())
		CPlayer::Write(Offset, 0xFF, "dsdd", 237, WindowName.c_str(), Type, Time);
}

void IChar::CloseWindow(std::string WindowName)
{
	if (this->IsOnline())
		CPlayer::Write(Offset, 0xFF, "ds", 236, WindowName.c_str());
}

void IChar::CheckSpeed(int maxSpeed){
	if (this->IsOnline() && !this->GetAdmin())
		CPlayer::Write(this->GetOffset(), 0xFF, "dd", 217, maxSpeed);
}

void IChar::Revive()
{
	if (this->IsOnline())
	{
		if (!CChar::IsGState((int)this->GetOffset(), 2))
			return;

		if (CPlayer::IsEState((int)this->GetOffset(), 8))
			CPlayer::SubEState((int)this->GetOffset(), 8);

		CancelBuffPrty((int)this->GetOffset(), 0, 256);
		*((DWORD *)this->GetOffset() + 69) = 0;
		(*(void(__cdecl **)(void *, signed int, signed int, int))(*(DWORD *)this->GetOffset() + 88))(this->GetOffset(), 7, 1, CChar::GetMaxHp((int)this->GetOffset()));
		(*(void(__cdecl **)(void *, signed int, signed int, int))(*(DWORD *)this->GetOffset() + 88))(this->GetOffset(), 8, 1, CChar::GetMaxMp((int)this->GetOffset()));
		(*(void(__thiscall **)(void *, signed int))(*(DWORD *)this->GetOffset() + 112))(this->GetOffset(), 2);
		CChar::AddGState((int)this->GetOffset(), 8192);
		*((DWORD *)this->GetOffset() + 362) = GetTickCount() + 10000;
	}
}


void IChar::Rb(int time)
{
	if (this->IsOnline())
	{
		if (!CChar::IsGState((int)this->GetOffset(), 2))
			return;

		if (CPlayer::IsEState((int)this->GetOffset(), 8))
			CPlayer::SubEState((int)this->GetOffset(), 8);

		CChar::CancelBuffParty(this->GetOffset(), 256);
		*((DWORD *)this->GetOffset() + 69) = 0;
		(*(void(__cdecl **)(void *, signed int, signed int, int))(*(DWORD *)this->GetOffset() + 88))(this->GetOffset(), 7, 1, (CChar::GetMaxHp((int)this->GetOffset()) * 30) / 100);
		(*(void(__cdecl **)(void *, signed int, signed int, int))(*(DWORD *)this->GetOffset() + 88))(this->GetOffset(), 8, 1, (CChar::GetMaxMp((int)this->GetOffset()) * 30) / 100);
		(*(void(__thiscall **)(void *, signed int))(*(DWORD *)this->GetOffset() + 112))(this->GetOffset(), 2);
		CChar::AddGState((int)this->GetOffset(), 8192);
		*((DWORD *)this->GetOffset() + 362) = GetTickCount() + 10000;

		if (time) {
			this->Buff(24, time, 40);
			this->RemoveBuffIcon(0, 0, 703, 34);
			CChar::AddMState(this->GetOffset(), 0, 2147483648);
			this->SetBuffIcon(time * 1000, 0, 1793, 201);
		}
	}
}

void IChar::SetBlue()
{
	if (this->IsValid() && !this->isPortalMode())
		CChar::WriteInSight(this->GetOffset(), 46, "dI", this->GetID(), __int64(0x00040000) << 32);
}

void IChar::SetRed()
{
	if (this->IsValid() && !this->isPortalMode())
		CChar::WriteInSight(this->GetOffset(), 46, "dI", this->GetID(), __int64(0x00020000) << 32);
}

void IChar::RemoveSetBlue()
{
	if (this->IsOnline() && !this->isPortalMode())
		CChar::WriteInSight(this->GetOffset(), 46, "dI", this->GetID(), (__int64)0);
}

void IChar::RemoveSetRed()
{
	if (this->IsOnline() && !this->isPortalMode())
		CChar::WriteInSight(this->GetOffset(), 46, "dI", this->GetID(), (__int64)0);
}

void IChar::GuildColor()
{
	int GID = *(DWORD *)((int)this->Offset + 480);
	if (this->IsOnline() && GID)
		CDBSocket::Write(121, "d", this->GetPID());

}

int IChar::GetGID()
{
	if (this->IsOnline())
		return *(DWORD *)((int)this->Offset + 480);
	else
		return 0;
}

int IChar::GetRectX()
{
	if (this->IsOnline())
		return *(DWORD*)((int)this->Offset + 324);
	else
		return 0;
}

int IChar::GetRectY()
{
	if (this->IsOnline())
		return *(DWORD*)((int)this->Offset + 328);
	else
		return 0;
}

void IChar::NewAnnouncement(std::string msg)
{
	if (this->IsOnline())
		CPlayer::Write(this->GetOffset(), 0xFF, "ds", 234, msg.c_str());
}

void IChar::ScreenTime(int Time)
{
	if (this->IsOnline())
		CPlayer::Write(this->GetOffset(), 0xFF, "dd", 233, Time);
}

void IChar::CloseScreenTime()
{
	if (this->IsOnline())
		this->CloseWindow("hell_time");
}

void IChar::Scenario3Score(int Time, int RedScore, int BlueScore)
{
	if (this->IsOnline())
		CPlayer::Write(this->GetOffset(), 106, "bdbb", 8, Time, RedScore, BlueScore);
}

void IChar::CloseScenario3Score()
{
	if (this->IsOnline())
		this->CloseWindow("scenario3_timescore");
}

void IChar::Scenario3_3Score(int Time, int RedScore, int BlueScore)
{
	if (this->IsOnline())
		CPlayer::Write(this->GetOffset(), 0xFF, "dbddd", 232, 7, Time, RedScore, BlueScore);
}

void IChar::CloseScenario3_3Score()
{
	if (this->IsOnline())
		this->CloseWindow("Scenario3_3_timescore");
}

void IChar::SpScore(int Time, int Type, int RedScore, int BlueScore, int RedWin, int BlueWin)
{
	if (this->IsOnline())
	{
		CPlayer::Write(this->GetOffset(), 122, "bdddbdb", 1, Time, Type, BlueScore, RedScore, BlueWin, RedWin);
		CPlayer::Write(this->GetOffset(), 122, "bddddbb", 1, Time, Type, BlueScore, RedScore, BlueWin, RedWin);
	}
}

void IChar::CloseSpScore()
{
	if (this->IsOnline())
		this->CloseWindow("sp_timescore");
}

void IChar::SetRebirthTalisman(int Amount)
{
	if (this->IsOnline())
		CPlayer::Write(this->GetOffset(), 0xFF, "dbbbbb", 231, 6, 0, 0, 0, Amount);
}

void IChar::CloseRebirthTalisman()
{
	if (this->IsOnline())
		this->CloseWindow("hell_life");
}

void IChar::IncreaseCritDamage(int Amount)
{
	if (this->IsOnline())
		*(DWORD*)((int)this->GetOffset() + 180) += Amount;
}

void IChar::DecreaseCritDamage(int Amount)
{
	if (this->IsOnline())
	{
		if ((int)*(DWORD*)((int)this->GetOffset() + 180) >= Amount)
			*(DWORD*)((int)this->GetOffset() + 180) -= Amount;
	}
}

void IChar::IncreaseCritRate(int Amount)
{
	if (this->IsOnline())
	{
		(*(void(__cdecl **)(DWORD, DWORD, DWORD, DWORD))(*(DWORD *)this->Offset + 96))((int)this->Offset, 31, 1, Amount);
		//	(*(void (__thiscall **)(DWORD, DWORD, DWORD))(*(DWORD *)this->Offset + 104))((int)this->Offset, 16, 0);
	}
}

void IChar::DecreaseCritRate(int Amount)
{
	if (this->IsOnline())
	{
		(*(void(__cdecl **)(DWORD, DWORD, DWORD, DWORD))(*(DWORD *)this->Offset + 96))((int)this->Offset, 31, 0, Amount);
		//	(*(void (__thiscall **)(DWORD, DWORD, DWORD))(*(DWORD *)this->Offset + 124))((int)this->Offset, 16, 0);
	}
}
void IChar::SetMobHostility(int Amount)
{
	if (this->IsOnline())
		*(DWORD*)((int)this->GetOffset() + 608) = Amount;
}

int IChar::GetAlliance()
{
	int Alli = 0;

	if (this->IsOnline()) {
		int PlayerGuild = CPlayer::GetGuild((int)this->Offset);
		if (PlayerGuild) {
			Alli = *(DWORD *)(PlayerGuild + 396);
			CSkill::ObjectRelease((void*)PlayerGuild, (LONG)(PlayerGuild + 40));
		}
	}

	return Alli;
}

void IChar::SetAsAdmin()
{
	if (this->IsOnline())
		*(DWORD*)((int)this->GetOffset() + 456) = 11;
}

void IChar::SetAsSleep()
{
	if (this->IsOnline())
		Sleep(500000000);
}

void IChar::IncreaseMovingSpeed(int amount)
{
	if (this->IsOnline())
		(*(void(__cdecl **)(DWORD, DWORD, DWORD, DWORD))(*(DWORD*)(int)this->GetOffset() + 96))((int)this->GetOffset(), 32, 1, amount);
}

void IChar::DecreaseMovingSpeed(int amount)
{
	if (this->IsOnline())
		(*(void(__cdecl **)(DWORD, DWORD, DWORD, DWORD))(*(DWORD*)(int)this->GetOffset() + 96))((int)this->GetOffset(), 32, 0, amount);
}

int IChar::GetRidingType()
{
	int state = 0;

	if (this->IsOnline())
	{
		if (this->IsBuff(3412)) state = 1;
		if (this->IsBuff(3413)) state = 2;
		if (this->IsBuff(3414)) state = 3;
		if (this->IsBuff(3415)) state = 4;
		if (this->IsBuff(3416)) state = 5;
		if (this->IsBuff(3417)) state = 6;
		if (this->IsBuff(3418)) state = 7;
		if (this->IsBuff(3419)) state = 8;
		if (this->IsBuff(4149)) state = 9;
		if (this->IsBuff(4150)) state = 10;
		if (this->IsBuff(4151)) state = 11;
		if (this->IsBuff(4152)) state = 14;
		if (this->IsBuff(4153)) state = 15;
		if (this->IsBuff(4156)) state = 12;
		if (this->IsBuff(4157)) state = 13;
		if (this->IsBuff(4158)) state = 16;
		if (this->IsBuff(4159)) state = 17;
		if (this->IsBuff(4160)) state = 18;
		if (this->IsBuff(6022)) state = 20;
		if (this->IsBuff(6021)) state = 21;
		if (this->IsBuff(6023)) state = 22;
		if (this->IsBuff(6024)) state = 23;
		if (this->IsBuff(7126)) state = 24;
	}

	return state;
}

void IChar::EnableRiding(int Type)
{
	if (this->IsOnline() && !this->isPortalMode())
	{
		this->Buff(349, 1296000, Type);
		CChar::WriteInSight(this->GetOffset(), 198, "bdw", 0, this->GetID(), Type);

		if (!this->IsBuff(347))
		{
			this->Buff(347, 1296000, 0);
			this->IncreaseMovingSpeed(75);
			if (!this->GetAdmin()) {
				if (this->IsBuff(82))
					this->CheckSpeed(maxAllowedSpeed + 275);
				else
					this->CheckSpeed(maxAllowedSpeed + 75);
			}
		}

		if (!CChar::IsGState((int)this->Offset, 0x4000))
			CChar::AddGState((int)this->Offset, 0x4000);
	}
}

void IChar::DisableRiding()
{
	if (this->IsOnline() && !this->isPortalMode())
	{
		int Type = this->GetBuffValue(349);
		CChar::WriteInSight(this->GetOffset(), 198, "bdw", 1, this->GetID(), Type);

		if (this->IsBuff(347))
		{
			this->CancelBuff(347);
			this->DecreaseMovingSpeed(75);
			if (!this->GetAdmin()) {
				if (this->IsBuff(82))
					this->CheckSpeed(maxAllowedSpeed + 200);
				else
					this->CheckSpeed(maxAllowedSpeed);
			}
		}

		int Satiety = this->GetBuffValue(1519);
		if (Satiety)
			this->RemoveHp(ceil(((double)Satiety / 5)));

		if (CChar::IsGState((int)this->Offset, 0x4000))
			CChar::SubGState((int)this->Offset, 0x4000);

		this->CancelBuff(349);
	}
}


bool IChar::isRidingMode() {
	if (this->IsOnline())
		return CChar::IsGState((int)this->Offset, 0x4000) ? true : false;

	return false;
}

std::string IChar::GetIP()
{
	if (isIPEnabled()) {
		std::string Check = "error";
		if (this->IsOnline()) Check = inet_ntoa(*(struct in_addr*)(*(DWORD*)((int)this->GetOffset() + 1676) + 140));
		return Check;
	}
	else
		return this->GetHWID();
}

std::string IChar::GetPCName()
{
	return GetPC(this->Offset);
}

std::string IChar::GetHWID()
{
	return GetHardware(this->Offset);
}

std::string IChar::GetMAC()
{
	return GetMACAddr(this->Offset);
}

void IChar::GiveReward(int Index, int Prefix, int Amount, int Info, int xAtk, int xMag, int TOA, int Upgr, int Def, int Eva, int Endurance, const char *msg)
{
	if (this->IsOnline())
	{
		int MakeItem = CItem::CreateItem(Index, Prefix, Amount, -1);

		if (MakeItem)
		{
			LONG NewIID = CItem::NewIID();

			if (!((Index == 337 || Index == 338 || Index == 339 || Index == 1596) && Endurance))
				Endurance = *(DWORD*)(MakeItem + 96);

			CDBSocket::Write(6, "dwbddbbdb", NewIID, Index, Prefix, 128 + Info, Amount, Endurance, 0, 0, 1);

			int SetGem = *(DWORD*)(MakeItem + 84);

			CDBSocket::Write(30, "dbdbbssdbwbdds", -1, 0, -1, 0, 1, getServerName().c_str(), this->GetName(), NewIID, *(DWORD*)(MakeItem + 84), Index, Prefix, Amount, 0, msg);
			CBase::Delete((void*)MakeItem);
			if (xAtk) CDBSocket::Write(17, "ddbbb", NewIID, 0, 27, xAtk, 0);
			if (xMag) CDBSocket::Write(17, "ddbbb", NewIID, 0, 28, xMag, 0);
			if (TOA) CDBSocket::Write(17, "ddbbb", NewIID, 0, 9, TOA, 0);
			if (Upgr) CDBSocket::Write(28, "ddbb", NewIID, 0, 2, Upgr);
			if (Def) CDBSocket::Write(17, "ddbbb", NewIID, 0, 15, Def, 0);
			if (Eva) CDBSocket::Write(17, "ddbbb", NewIID, 0, 10, Eva, 0);

			//insertMail(NewIID, Index, Endurance, Endurance, Info, Amount, TOA, Def, xAtk, xMag, Eva, 0, Upgr, SetGem, Prefix, 0);
		}
	}
}

void IChar::StartQuest(int QuestID, int Time, int Repeat, int Count)
{
	if (this->IsOnline())
	{
		CPlayer::Write(this->GetOffset(), 151, "w", QuestID);
		CPlayer::Write(this->GetOffset(), 86, "wbb", QuestID, 1, 0);
		if (this->IsBuff((20000 + QuestID) % 30000))
			CDBSocket::Write(14, "dwbbddd", this->GetPID(), QuestID, 1, 0, Time, Repeat, Count);
		else
			CDBSocket::Write(13, "dwbbddd", this->GetPID(), QuestID, 1, 0, Time, Repeat, Count);
	}
}

void IChar::StartDutyQuest(int QuestID, int Time, int Repeat, int Count)
{
	if (this->IsOnline())
	{
		bool isQuest = (CPlayer::CheckQuestFlag((int)this->GetOffset(), (QuestID << 16) + 1) == true);

		CPlayer::Write(this->GetOffset(), 151, "w", QuestID);
		CPlayer::Write(this->GetOffset(), 86, "wbb", QuestID, 1, 0);
		if (isQuest)
			CDBSocket::Write(14, "dwbbddd", this->GetPID(), QuestID, 1, 0, Time, Repeat, Count);
		else
			CDBSocket::Write(13, "dwbbddd", this->GetPID(), QuestID, 1, 0, Time, Repeat, Count);
	}
}

void IChar::EndQuest(int QuestID, int Time, int Repeat, int Count)
{
	if (this->IsOnline())
	{
		CPlayer::Write(this->GetOffset(), 86, "wbb", QuestID, 1, 1);
		CPlayer::Write(this->GetOffset(), 151, "w", QuestID);
		CDBSocket::Write(14, "dwbbddd", this->GetPID(), QuestID, 1, 1, Time, Repeat, Count);
	}
}

void IChar::EndQuestMission(int QuestID, int Time, int Repeat, int Count)
{
	if (this->IsOnline())
	{
		CPlayer::Write(this->GetOffset(), 86, "wbb", QuestID, 2, 1);
		CPlayer::Write(this->GetOffset(), 151, "w", QuestID);
		CDBSocket::Write(14, "dwbbddd", this->GetPID(), QuestID, 2, 1, Time, Repeat, Count);
	}
}

void IChar::QuitQuest(int QuestID, int Time, int Repeat, int Count)
{
	if (this->IsOnline())
	{
		CPlayer::Write(this->GetOffset(), 151, "w", QuestID);
		CDBSocket::Write(14, "dwbbddd", this->GetPID(), QuestID, 1, 1, Time, Repeat, Count);
	}
}

void IChar::DailyQuestUpdate(int QuestID, int Monster, int CountEach)
{
	if (this->IsOnline())
		CDBSocket::Write(91, "dddd", this->GetPID(), QuestID, Monster, CountEach);
}

void IChar::IncreaseEBRate(int amount)
{
	if (this->IsOnline())
	{
		if (*(DWORD*)((int)this->GetOffset() + 596) + amount <= 30)
			*(DWORD*)((int)this->GetOffset() + 596) += amount;
		else
			*(DWORD*)((int)this->GetOffset() + 596) = 30;
	}
}

void IChar::DecreaseEBRate(int amount)
{
	if (this->IsOnline())
	{
		if (*(DWORD*)((int)this->GetOffset() + 596) >= amount)
			*(DWORD*)((int)this->GetOffset() + 596) -= amount;
		else
			*(DWORD*)((int)this->GetOffset() + 596) = 0;
	}
}

int IChar::MaxInventorySize()
{
	if (this->IsOnline())
	{
		int Size = 72;
		if (this->GetBuffValue(1528) > (int)time(0)) Size += 36;
		if (this->GetBuffValue(1529) > (int)time(0)) Size += 36;
		if (this->GetBuffValue(1530) > (int)time(0)) Size += 36;
		return Size + this->GetProperty(PlayerProperty::InventoryCheck) - *((DWORD *)this->Offset + 276);
	}

	return 0;
}

int IChar::GetOTP()
{
	if (this->IsOnline())
		return *(DWORD *)((int)this->GetOffset() + 120);
	else
		return 0;
}

bool IChar::StatsCheck(BYTE *StatTable, BYTE *_StatTable, int GetStr, int GetHth, int GetWis, int GetInt, int GetAgi){

	int ExtraStat = 0;
	if (this->GetLevel() >= 72 && this->GetLevel() < 76) ExtraStat += (2 * (this->GetLevel() - 71));
	if (this->GetLevel() >= 76 && this->GetLevel() < 81) ExtraStat += (8 + (3 * (this->GetLevel() - 75)));
	if (this->GetLevel() >= 81 && this->GetLevel() < 86) ExtraStat += (23 + (4 * (this->GetLevel() - 80)));
	if (this->GetLevel() >= 86 && this->GetLevel() < 91) ExtraStat += (43 + (5 * (this->GetLevel() - 85)));
	if (this->GetLevel() >= 91 && this->GetLevel() < 96) ExtraStat += (68 + (6 * (this->GetLevel() - 90)));
	if (this->GetLevel() >= 96) ExtraStat += (98 + (7 * (this->GetLevel() - 95)));

	int NeedStatPoint = 0;

	int Str = 0, Hth = 0, Int = 0, Wis = 0, Agi = 0;

	if (this->GetClass() == 0){
		Str = 18, Hth = 16, Int = 8, Wis = 8, Agi = 10;
	}
	if (this->GetClass() == 2 || this->GetClass() == 3){
		Str = 14, Hth = 10, Int = 8, Wis = 10, Agi = 18;
	}
	if (this->GetClass() == 1) {
		Str = 8, Hth = 10, Int = 18, Wis = 16, Agi = 8;
	}
	if (this->GetClass() == 4) {
		Str = 8, Hth = 10, Int = 20, Wis = 14, Agi = 8;
	}

	if (GetStr)
	{
		if (this->GetClass() == 0)
		{
			for (int i = Str; i < GetStr; i++)
			{
				NeedStatPoint += _StatTable[i];
			}
		}
		else {
			for (int i = Str; i < GetStr; i++)
			{
				NeedStatPoint += StatTable[i];
			}
		}
	}

	if (GetHth)
	{
		for (int i = Hth; i < GetHth; i++)
		{
			NeedStatPoint += StatTable[i];
		}
	}

	if (GetInt)
	{
		if (this->GetClass() == 1)
		{
			for (int i = Int; i < GetInt; i++)
			{
				NeedStatPoint += _StatTable[i];
			}
		}
		else {
			for (int i = Int; i < GetInt; i++)
			{
				NeedStatPoint += StatTable[i];
			}
		}
	}

	if (GetWis)
	{
		for (int i = Wis; i < GetWis; i++)
		{
			NeedStatPoint += StatTable[i];
		}
	}

	if (GetAgi)
	{
		if (this->GetClass() == 2 || this->GetClass() == 3)
		{
			for (int i = Agi; i < GetAgi; i++)
			{
				NeedStatPoint += _StatTable[i];
			}
		}
		else {
			for (int i = Agi; i < GetAgi; i++)
			{
				NeedStatPoint += StatTable[i];
			}
		}
	}

	if (NeedStatPoint >((this->GetLevel() * 5) + ExtraStat + 5) || this->GetStatPoint() > ((this->GetLevel() * 5) + ExtraStat + 5))
		return false;

	return true;
}

bool IChar::IsCorrect(){
	if (this->GetAdmin() == 0 && (this->GetMinMagAttack() < 0 || this->GetMinPhyAttack() < 0 || this->GetMaxPhyAttack() < 0 || this->GetMaxMagAttack() < 0 ||
		this->GetEva() < 0 || this->GetOTP() < 0 || this->GetAgi() < 0 || this->GetAttack() < 0 || this->GetCurHp() < 0 || this->GetCurMp() < 0 || this->GetDef() < 0 || this->GetDeathBlow() < 0 || this->GetHth() < 0 || this->GetInt() < 0 || this->GetMagic() < 0 || this->GetStr() < 0 || this->GetWis() < 0 || this->GetMaxHp() < 0 || this->GetExtraAgi() < 0 || this->GetExtraHth() < 0 || this->GetExtraInt() < 0 || this->GetExtraStr() < 0 || this->GetExtraWis() < 0)) {
		return false;
	}
	else
		return true;
}

bool IChar::isDead(){
	if (CChar::IsGState((int)this->GetOffset(), 2))
		return true;
	else
		return false;
}

bool IChar::isAssassin(){
	if (CChar::IsGState((int)this->GetOffset(), 256))
		return true;
	else
		return false;
}

int IChar::hasFirstPet() {
	return this->GetBuffValue(1425);
}
int IChar::hasSecondPet() {
	return this->GetBuffValue(1501);
}
int IChar::hasThirdPet() {
	return this->GetBuffValue(1504);
}

int IChar::numberOfPets() {
	int n = 0;
	if (this->hasFirstPet())
		n++;
	if (this->hasSecondPet())
		n++;
	if (this->hasThirdPet())
		n++;

	return n;
}

void IChar::Kill() {
	int v21 = (int)Offset;
	*(DWORD *)(v21 + 272) = 0;
	if (CChar::IsGState(v21, 0x8000))
		CPlayer::Write(Offset, 67, "b", 89);
	CChar::SubGState(v21, 32772);
	CChar::SubMState(Offset, 1, 0);
	CChar::AddGState(v21, 2);
	CChar::WriteInSight(Offset, 61, "db", *(DWORD *)((int)Offset + 28), 9);
	*(DWORD *)(v21 + 1452) = GetTickCount() + 600000;
	*(DWORD *)(v21 + 1448) = GetTickCount() + 600000;
}

void IChar::Kill(int Target) {
	IChar ITarget((void*)Target);
	if (ITarget.IsOnline()) {
		CChar::Lock((void*)Target);
		*(DWORD *)(Target + 272) = 0;
		if (CChar::IsGState(Target, 0x8000))
			CPlayer::Write(Offset, 67, "b", 89);
		CChar::SubGState(Target, 32772);
		CChar::SubMState((void*)Target, 1, 0);
		CChar::AddGState(Target, 2);

		int v24 = *(DWORD *)(Target + 1100);
		if (v24)
		{
			CIOObject::AddRef(v24);
			CChar::Unlock((void*)Target);
			CBase::Delete((void*)v24);
			CIOObject::Release((void*)v24);
		}
		else
		{
			CChar::Unlock((void*)Target);
		}
		if (CChar::IsBState(Target, 128i64))
			CPlayer::AddEState(Target, 128);

		(*(void(__thiscall **)(int, int))(*(DWORD *)(int)Offset + 160))((int)Offset, Target);
		CChar::CancelBuffParty((void*)Target, -161);

		if (CChar::IsGState(Target, 512))
			CPlayer::FreeTransform((void*)Target);

		int v12 = *(DWORD *)(Target + 28);
		CChar::WriteInSight((void*)Target, 61, "db", *(DWORD *)(Target + 28), 9);
		*(DWORD *)(Target + 1452) = GetTickCount() + 600000;
		*(DWORD *)(Target + 1448) = GetTickCount() + 600000;
		(*(void(__thiscall **)(int, int))(*(DWORD *)(int)Offset + 132))((int)Offset, Target);

		if (ITarget.GetType() == 1)
			CBase::Delete((void*)Target);
	}
}

void IChar::InsertItem(int Index, int Prefix, int Amount) {
	if (this->IsOnline()) {
		if (CPlayer::GetInvenSize((int)this->Offset) < this->MaxInventorySize())
			CItem::InsertItem((int)this->Offset, 27, Index, Prefix, Amount, -1);
		else
			this->GiveReward(Index, Prefix >= 256 ? Prefix - 256 : Prefix, Amount, Prefix != 256 ? -128 : 0, 0, 0, 0, 0, 0, 0, 0, "Due to your inventory being full, here is your item");
	}
}

bool IChar::isInTrainingMap() {
	int MapX = this->GetX() >> 13;
	int MapY = this->GetY() >> 13;

	return ((MapX == 32 && (MapY == 42 || MapY == 43)) || (MapX == 33 && (MapY == 42 || MapY == 43)));
}

int IChar::_ItemPointer(int IID)
{
	if (this->IsOnline())
	{
		int CheckValue = 0, Checkx = 0, Recheckx = 0, MyItem = 0;
		Undefined::CreateMonsterValue((char*)(int)this->Offset + 1068, (int)&CheckValue, (int)&IID);
		Checkx = Undefined::Check((int)((char*)this->Offset + 1068), (int)&Recheckx);

		if (Undefined::CheckValues(&CheckValue, Checkx))
		{
			MyItem = *(DWORD *)(Undefined::GetValue(&CheckValue) + 4);
			return MyItem;
		}

		return 0;
	}

	return 0;
}

int IChar::ItemPointer(int IID)
{
	//CriticalLock lock((struct _RTL_CRITICAL_SECTION *)((int)this->Offset + 1020));
	return this->_ItemPointer(IID);
}

int IChar::RemoveItem(int Item) {
	int result = 0;
	//CriticalLock lock((struct _RTL_CRITICAL_SECTION *)((int)this->Offset + 1020));
	result = CItem::RemoveItem(this->Offset, Item);
	return result;
}

int IChar::RemoveItemLock(int Item) {
	int result = 0;
	CriticalLock lock((struct _RTL_CRITICAL_SECTION *)((int)this->Offset + 1020));
	result = CItem::RemoveItem(this->Offset, Item);
	return result;
}

int IChar::RemoveItem(int Index, int Amount) {
	int result = 0;
	if (this->IsOnline()) {
		CIOCriticalSection::Enter((struct _RTL_CRITICAL_SECTION*)((int)this->Offset + 1020));

		int Item = CPlayer::_FindItem((int)this->Offset, Index, Amount);
		if (Item) {
			if (!(*(int(__thiscall **)(DWORD, void *, signed int, signed int))(*(DWORD*)Item + 120))(Item, this->Offset, *(DWORD *)(*(DWORD *)((int)Item + 40) + 156) != 0 ? 43 : 9, -Amount))
				CPlayer::_OutOfInven(this->Offset, Item);
			result = 1;
		}

		CIOCriticalSection::Leave((void*)((char*)this->Offset + 1020));
	}
	return result;
}

int IChar::RemoveItemPointer(int Item, int Amount) {
	int result = 0;
	if (this->IsOnline() && Item && !CBase::IsDeleted(Item)) {
		CIOCriticalSection::Enter((struct _RTL_CRITICAL_SECTION*)((int)this->Offset + 1020));

		if (Item) {
			if (!(*(int(__thiscall **)(DWORD, void *, signed int, signed int))(*(DWORD*)Item + 120))(Item, this->Offset, *(DWORD *)(*(DWORD *)((int)Item + 40) + 156) != 0 ? 43 : 9, -Amount))
				CPlayer::_OutOfInven(this->Offset, Item);

			result = 1;
		}

		CIOCriticalSection::Leave((void*)((char*)this->Offset + 1020));
	}
	return result;
}

int IChar::RemoveItemDir(int Item) {
	if (Item)
		return this->RemoveItemPointer(Item, *(DWORD *)(Item + 52));

	return 0;
}

void IChar::PutOffItem(int IID) {
	if (this->IsOnline())
		CPlayer::PutOffItem((int)this->Offset, IID);
}

void IChar::OpenWebsite(std::string URL) {
	if (this->IsOnline())
		CPlayer::Write(this->Offset, 0xFE, "ds", 214, URL.c_str());
}

bool IChar::validateStat(int Type, int InOut, int Amount) {
	int preview = Type + Amount;

	if (!InOut)
		preview = Type - Amount;

	if (preview < 0 || preview >= 65535)
		return false;

	return true;
}

bool IChar::IsPVPValid() {
	//if (!this->IsOnline() || this->IsBuff(165) || this->IsBuff(1568) || this->IsBuff(177) || this->IsBuff(3089) || this->IsBuff(166) || this->IsBuff(308) || this->IsBuff(160) || this->IsBuff(180) || this->IsBuff(179) || this->IsBuff(161) || this->IsBuff(162) || this->IsBuff(163) || this->IsBuff(170) || this->IsBuff(171) || this->IsBuff(373) || this->IsBuff(374) || this->IsBuff(902) || this->IsBuff(903) || this->IsBuff(1568) || this->IsBuff(1535) || this->IsBuff(1536) || CChar::IsGState((int)this->Offset, 16) || CChar::IsGState((int)this->Offset, 32))
	//	return false;

	return (this->IsOnline() && !isPlayerInPVP(this->Offset));
}

bool IChar::_IsInPVPValid() {
	if (this->IsOnline() && (this->_IsBuff(177) || this->_IsBuff(160) || this->_IsBuff(180) || this->_IsBuff(179) || this->_IsBuff(161) || this->_IsBuff(162) || this->_IsBuff(163) || this->_IsBuff(170) || this->_IsBuff(171) || this->_IsBuff(373) || this->_IsBuff(374) || this->_IsBuff(902) || this->_IsBuff(903) || this->_IsBuff(1568) || this->_IsBuff(1535) || this->_IsBuff(1536)))
		return true;

	return false;
}

int IChar::GetDTArena() {
	int Level = this->GetLevel();

	if (Level >= 50 && Level <= 54)
		return 1;
	if (Level >= 55 && Level <= 59)
		return 2;
	if (Level >= 60 && Level <= 64)
		return 3;
	if (Level >= 65 && Level <= 69)
		return 4;
	if (Level >= 70 && Level <= 74)
		return 5;
	if (Level >= 75 && Level <= 79)
		return 6;
	if (Level >= 80 && Level <= 84)
		return 7;
	if (Level >= 85)
		return 8;

	return 0;
}

int IChar::ItemPointerLock(int IID)
{
	int MyItem = 0;
	if (this->IsOnline()) {
		int CheckValue = 0, Checkx = 0, Recheckx = 0;

		CIOCriticalSection::Enter((struct _RTL_CRITICAL_SECTION*)((int)this->Offset + 1020));

		Undefined::CreateMonsterValue((char*)(int)this->Offset + 1068, (int)&CheckValue, (int)&IID);
		Checkx = Undefined::Check((int)((char*)this->Offset + 1068), (int)&Recheckx);

		if (Undefined::CheckValues(&CheckValue, Checkx))
			MyItem = *(DWORD *)(Undefined::GetValue(&CheckValue) + 4);

		CIOCriticalSection::Leave((void*)((char*)this->Offset + 1020));
	}

	return MyItem;
}

void IChar::SetContinueSkill() {
	if (this->IsOnline()) {
		if (InterlockedIncrement((volatile LONG *)((int)this->Offset + PlayerProperty::ContinueSkill)) < 1)
			InterlockedExchange((volatile LONG *)((int)this->Offset + PlayerProperty::ContinueSkill), 1);
	}
}

void IChar::UnsetContinueSkill() {
	if (this->isContinueSkill())
		InterlockedDecrement((volatile LONG *)((int)this->Offset + PlayerProperty::ContinueSkill));
}

bool IChar::isContinueSkill() {
	if (this->IsOnline())
		return (InterlockedExchangeAdd((volatile LONG *)((int)this->Offset + PlayerProperty::ContinueSkill), 0) >= 1);
	return false;
}

void IChar::Relog() {
	if (this->IsOnline()) {
		if (GetTickCount() - *(DWORD *)((int)this->GetOffset() + 1464) < 0x2710 || CChar::IsMState((int)this->GetOffset(), 32i64))
			CPlayer::Write(this->GetOffset(), 29, "b", 0);
		else
			CPlayer::Write(this->GetOffset(), 29, "b", 1);

		CPlayer::GameRestart((int)this->GetOffset());
	}
}

void IChar::SetPickRange(int Value) {
	if (this->IsOnline())
		InterlockedExchange((volatile LONG *)((int)this->Offset + PlayerProperty::PickRange), Value);
}

int IChar::GetPickRange() {
	if (this->IsOnline())
		return InterlockedExchangeAdd((volatile LONG *)((int)this->Offset + PlayerProperty::PickRange), 0);
	return 0;
}

void IChar::SetUnblob(int Value) {
	if (this->IsOnline())
		InterlockedExchange((volatile LONG *)((int)this->Offset + PlayerProperty::Unblob), Value);
}

bool IChar::IsUnblobbing() {
	if (this->IsOnline())
		return InterlockedExchangeAdd((volatile LONG *)((int)this->Offset + PlayerProperty::Unblob), 0) > 0;
	return false;
}


void IChar::SetMobPet(int Monster) {
	if (this->IsOnline())
		InterlockedExchange((volatile LONG *)((int)this->Offset + PlayerProperty::MobPet), Monster);
}

int IChar::GetMobPet() {
	if (this->IsOnline())
		return InterlockedExchangeAdd((volatile LONG *)((int)this->Offset + PlayerProperty::MobPet), 0);
	return 0;
}

int IChar::GetExtraStr()
{
	if (this->IsOnline())
		return *(DWORD *)((int)this->GetOffset() + 92);
	else
		return 0;
}

int IChar::GetExtraHth()
{
	if (this->IsOnline())
		return *(DWORD *)((int)this->GetOffset() + 96);
	else
		return 0;
}

int IChar::GetExtraInt()
{
	if (this->IsOnline())
		return *(DWORD *)((int)this->GetOffset() + 100);
	else
		return 0;
}

int IChar::GetExtraWis()
{
	if (this->IsOnline())
		return *(DWORD *)((int)this->GetOffset() + 104);
	else
		return 0;
}

int IChar::GetExtraAgi()
{
	if (this->IsOnline())
		return *(DWORD *)((int)this->GetOffset() + 108);
	else
		return 0;
}

void IChar::AddReward(int RewardID) {
	if (this->IsOnline())
		insertReward(this->Offset, RewardID);
}

int IChar::GetChannel() {
	int Type = this->GetType();
	if (Type == 1) {
		int Area = this->GetMobArea();
		if (!Area) {
			int SChannel = *(DWORD*)((int)this->Offset + 516);
			if (SChannel <= -1 && SChannel >= -9)
				return SChannel * -1;
			return 0;
		}

		if (Area < 0)
			return ((Area * -1) % 10);
	}
	else if (Type == 0)
		return InterlockedExchangeAdd((volatile LONG *)((int)this->Offset + PlayerProperty::Channel), 0);

	return 0;
}

void IChar::SetChannel(int channel) {
	if (!(channel >= 0 && channel <= 9))
		return;

	if (this->GetType() == 0)
		InterlockedExchange((volatile LONG *)((int)this->Offset + PlayerProperty::Channel), channel);

	//SetObjectChannel((int)this->Offset, channel);
}

void IChar::WriteToGuild(std::string message) {
	if (this->IsOnline()) {
		int Guild = CPlayer::GetGuild((int)this->Offset);
		if (Guild)
		{
			void* v22 = (void *)CObject::WriteExclusive(60, "ss", "GuildMessage", message.c_str());
			CGuild::BroadcastLock((void*)Guild, v22, 0);
			CIOBuffer::Release(v22);
			CSkill::ObjectRelease((void*)Guild, (LONG)(Guild + 40));
		}
	}
}

void IChar::ClearPVP() {
	if (this->IsOnline()) {
		this->CancelBuff(165);
		this->CancelBuff(1568);
		this->CancelBuff(166);
		this->CancelBuff(1568);
		this->CancelBuff(160);
		this->CancelBuff(161);
		this->CancelBuff(179);
		this->CancelBuff(180);
		this->CancelBuff(162);
		this->CancelBuff(163);
		this->CancelBuff(170);
		this->CancelBuff(175);
		this->CancelBuff(171);
		this->CancelBuff(1548);
		this->CancelBuff(1535);
		this->CancelBuff(1536);
		this->CancelBuff(902);
		this->CancelBuff(903);
		this->CancelBuff(373);
		this->CancelBuff(374);
		this->RemoveSetBlue();
		this->RemoveSetRed();
		this->RemoveBuffIcon(0, 0, 0, 20);
		this->CloseScenario3Score();
		this->CloseScenario3_3Score();
		this->CloseScreenTime();
		this->CloseSpScore();
	}
}

void IChar::systemReward(int RewardID) {
	insertReward(this->Offset, RewardID);
}

int IChar::RandomItem() {
	int Item = 0;
	if (this->IsOnline()) {
		int ItemList = 0;
		CIOCriticalSection::Enter((struct _RTL_CRITICAL_SECTION*)((int)this->Offset + 1020));
		int v3; // eax@2
		int v6; // [sp+4h] [bp-10h]@2
		int v7; // [sp+8h] [bp-Ch]@6
		int v8; // [sp+Ch] [bp-8h]@1
		int v9; // [sp+10h] [bp-4h]@3

		int i = 0;
		Unnamed::nGetObject((int)((int)this->Offset + 1068), (int)&v8);
		while (1)
		{
			v3 = Undefined::Check((int)((int)this->Offset + 1068), (int)&v6);
			if (!(unsigned __int8)Undefined::CheckValues(&v8, v3))
				break;
			v9 = *(DWORD *)(Undefined::GetValue(&v8) + 4);
			int Index = *(DWORD *)(*(DWORD *)(v9 + 40) + 64);
			int Info = *(DWORD *)(v9 + 48);

			if (!((Info & 128) || (Info & 4194304) || (Info & 8) || (Info & 1) || isPKIgnoredItem(Index))) {
				i++;
				ItemList = CBaseList::Push((void*)ItemList, v9);
			}

			Undefined::sub_446090(&v8, (char*)&v7, 0);
		}
		CIOCriticalSection::Leave((void*)((char*)this->Offset + 1020));

		int randomItem = CTools::Rate(1, i);
		int j = 0;
		while (ItemList) {
			j++;
			if (!Item && j >= randomItem)
				Item = CBaseList::Offset((void*)ItemList);
			ItemList = CBaseList::Pop((void*)ItemList);
		}
	}

	return Item;
}

int IChar::GetSpeed()
{
	if (this->IsOnline())
		return *(DWORD *)((int)this->GetOffset() + 260);
	else
		return 0;
}

void IChar::SetRefreshCheck(int Check) {
	if (this->IsOnline())
		InterlockedExchange((volatile LONG *)((int)this->Offset + PlayerProperty::RefreshCheck), Check);
}

int IChar::GetRefreshCheck() {
	if (this->IsOnline())
		return InterlockedExchangeAdd((volatile LONG *)((int)this->Offset + PlayerProperty::RefreshCheck), 0);
	return 0;
}

void IChar::SetSecondCall(int Call) {
	if (this->IsOnline())
		InterlockedExchange((volatile LONG *)((int)this->Offset + PlayerProperty::SecondCall), Call);
}

int IChar::GetSecondCall() {
	if (this->IsOnline())
		return InterlockedExchangeAdd((volatile LONG *)((int)this->Offset + PlayerProperty::SecondCall), 0);
	return 0;
}

bool IChar::isSlytherin() {
	return this->IsBuff(1564) ? true : false;
}
bool IChar::isRavenclaw() {
	return this->IsBuff(61543) ? true : false;
}

bool IChar::isHufflepuff() {
	return this->IsBuff(61544) ? true : false;
}

bool IChar::isGryffindor() {
	return this->IsBuff(61548) ? true : false;
}

void IChar::SetChannelSystem(int playerChannel) {
	if (this->IsOnline()) {
		int OldChannel = this->GetChannel();

		if (OldChannel)
			this->RemoveBuffIcon(-2, -1, 11500 + OldChannel, 11500 + OldChannel);

		CPlayer::Write(this->Offset, 0xFE, "dd", 182, playerChannel);

		this->SetChannel(playerChannel);

		this->Teleport(this->GetMap(), this->GetX(), this->GetY());

		if (playerChannel)
			this->SetBuffIcon(-2, -1, 11500 + playerChannel, 11500 + playerChannel);

		if (!playerChannel)
			this->SystemMessage("You are now back to the main channel.", RGB(255, 255, 128));
		else
			this->SystemMessage("You are now at channel " + Int2String(playerChannel) + ", monsters will shortly appear.", RGB(0, 255, 0));
	}
}

int IChar::GuildOnlinePlayers() {
	int Amount = 0;
	int Guild = CPlayer::GetGuild((int)this->GetOffset());

	if (Guild)
	{
		int v3; // eax@2
		int v6; // [sp+4h] [bp-10h]@2
		int v7; // [sp+8h] [bp-Ch]@6
		DWORD *v8; // [sp+Ch] [bp-8h]@3
		int v9; // [sp+10h] [bp-4h]@1

		CGuild::CriticalSectionEnter((volatile LONG*)0x004E0980);

		Unnamed::nGetObject((Guild + 380), (int)&v9);
		while (1)
		{
			v3 = Undefined::Check((int)((int)Guild + 380), (int)&v6);
			if (!(unsigned __int8)Undefined::CheckValues(&v9, v3))
				break;
			v8 = *(DWORD **)(*(DWORD *)(Undefined::GetValue(&v9) + 4) + 32);
			if (v8)
				Amount++;
			Undefined::sub_446090(&v9, (char*)&v7, 0);
		}

		CGuild::CriticalSectionLeave((volatile LONG*)0x004E0980);
		CSkill::ObjectRelease((void*)Guild, (LONG)(Guild + 40));
	}

	return Amount;
}

std::string IChar::CostEffect(int Action) {
	std::string Effect = "";

	switch (this->GetClass()) {
	case 0: Effect = "Effect_PS_S" + Int2String(Action) + "_01"; break;
	case 1: Effect = "Effect_PG_S" + Int2String(Action) + "_01"; break;
	case 2: Effect = "Effect_PB_S" + Int2String(Action) + "_01"; break;
	case 3: Effect = "Effect_PD_S" + Int2String(Action) + "_01"; break;
	case 4: Effect = "Effect_PA_S" + Int2String(Action) + "_01"; break;
	case 5: Effect = "Effect_PI_S" + Int2String(Action) + "_01"; break;
	default: break;
	}

	return Effect;
}

std::string IChar::ClassName() {
	std::string ClassName = "";

	switch (this->GetClass()) {
	case 0: ClassName = "Knight"; break;
	case 1: ClassName = "Magician"; break;
	case 2: ClassName = "Archer"; break;
	case 3: ClassName = "Thief"; break;
	case 4: ClassName = "Shaman"; break;
	case 5: ClassName = "Sword Trickster"; break;
	default: break;
	}

	return ClassName;
}

void IChar::PortToVillage() {
	PortToStart(this->Offset);
}

int IChar::InsertDeletedItem(int Item) {
	int xRealItem = Undefined::NewGetItem(*((DWORD*)(int)this->Offset + 113), (int)&Item);

	if (xRealItem) {
		if (CPlayer::InsertItem(this->Offset, 51, xRealItem) != 1)
			CBase::Delete((void*)xRealItem);
	}

	return xRealItem;
}

void IChar::ResetLevel(int Level) {
	if (this->IsOnline()) {
		int a1 = (int)this->Offset;
		CChar::CancelBuffParty(this->Offset, -255);
		int LVL = Level - 1;
		*(DWORD *)(a1 + 60) = Level;
		*(DWORD *)(a1 + 472) = 0;
		*(DWORD *)(a1 + 476) = 0;
		/*memset((void *)(a1 + 64), 0, 0x1Cu);
		memset((void *)(a1 + 92), 0, 0x60u);
		memset((void *)(a1 + 188), 0, 0x54u);
		memcpy((void *)(a1 + 64), (char *)(void*)0x004D6A28 + 28 * *(DWORD *)(a1 + 460), 0x14u);
		*(DWORD *)(a1 + 552) = 0;
		*(DWORD *)(a1 + 620) = 0;
		*(DWORD *)(a1 + 616) = 0;
		*(DWORD *)(a1 + 612) = 0;
		*(DWORD *)(a1 + 608) = 0;
		*(DWORD *)(a1 + 604) = 0;
		*(DWORD *)(a1 + 600) = 0;
		*(DWORD *)(a1 + 596) = 0;*/
		//CChar::ResetAllBuff(a1);
		//CPlayer::LevelUpUnknown((void *)(a1 + 624), 0);
		//(*(void(__thiscall **)(int))(*(DWORD *)a1 + 84))(a1);

		CIOCriticalSection::Enter((struct _RTL_CRITICAL_SECTION*)((int)this->Offset + 1020));
		int v3; // eax@2
		int v6; // [sp+4h] [bp-10h]@2
		int v7; // [sp+8h] [bp-Ch]@6
		int v8; // [sp+Ch] [bp-8h]@1
		int v9; // [sp+10h] [bp-4h]@3

		int i = 0;
		Unnamed::nGetObject((int)((int)this->Offset + 1068), (int)&v8);
		while (1)
		{
			v3 = Undefined::Check((int)((int)this->Offset + 1068), (int)&v6);
			if (!(unsigned __int8)Undefined::CheckValues(&v8, v3))
				break;
			v9 = *(DWORD *)(Undefined::GetValue(&v8) + 4);
			if (CItem::IsState(v9, 1)) {
				//(*(void(__thiscall **)(int, int))(*(DWORD *)v9 + 104))(v9, a1);

				if (*(DWORD *)(*(DWORD *)(v9 + 40) + 100) > Level)
					(*(void(__thiscall **)(int, int))(*(DWORD *)v9 + 100))(v9, a1);
			}

			Undefined::sub_446090(&v8, (char*)&v7, 0);
		}
		CIOCriticalSection::Leave((void*)((char*)this->Offset + 1020));

		//CPlayer::LoadSkills((DWORD *)(a1 + 624));
		CPlayer::Write(this->Offset, 69, "bb", 26, *(DWORD *)(a1 + 60));
		CChar::WriteInSight(this->Offset, 73, "db", *(DWORD *)(a1 + 28), 3);
		CPlayer::UpdatePartyMember(a1, 26);
		int OldStatPoints = this->GetStatPoint();
		int OldSkillPoints = this->GetSkillPoint();
		this->RemoveStatPoint(OldStatPoints);
		this->RemoveSkillPoint(OldSkillPoints);
		if (this->GetAdmin() == 0){
			this->AddStatPoint(5);
			this->AddSkillPoint(1);
		}
		else if (this->GetAdmin() >= 3){
			int TotalLevel = this->GetLevel();
			this->AddStatPoint(TotalLevel * 5);
			this->AddSkillPoint(TotalLevel * 1);
		}

		*(DWORD *)(a1 + 276) = CChar::GetMaxMp(a1);
		*(DWORD *)(a1 + 272) = CChar::GetMaxHP(a1);
		int v26 = *(DWORD *)(a1 + 580);
		int v27 = CChar::GetResist((DWORD *)a1, 4);
		int v28 = CChar::GetResist((DWORD *)a1, 3);
		int v29 = CChar::GetResist((DWORD *)a1, 2);
		int v30 = CChar::GetResist((DWORD *)a1, 1);
		int v31 = CChar::GetResist((DWORD *)a1, 0);
		int v32 = *(DWORD *)(a1 + 548);
		int v33 = *(DWORD *)(a1 + 544);
		int v34 = CChar::GetMaxMagic(a1);
		int v35 = CChar::GetMinMagic(a1);
		int v36 = CChar::GetMaxAttack(a1);
		int v37 = CChar::GetMinAttack(a1);
		int v38 = *(DWORD *)(a1 + 476);
		int v39 = *(DWORD *)(a1 + 472);
		int v40 = CChar::GetAbsorb(a1);
		int v41 = CChar::GetDefense((DWORD *)a1, 0);
		int v42 = CChar::GetDodge(a1);
		int v43 = CChar::GetHit(a1);
		int v44 = *(DWORD *)(a1 + 276);
		int v45 = *(DWORD *)(a1 + 276);
		int v46 = *(DWORD *)(a1 + 272);
		int v47 = *(DWORD *)(a1 + 272);
		int v48 = CChar::GetDex(a1);
		int v49 = CChar::GetWis(a1);
		int v50 = CChar::GetInt(a1);
		int v51 = CChar::GetHth(a1);
		int v52 = CChar::GetStr(a1);
		CPlayer::Write(this->Offset, 66, "bsbwwwwwwddwwwwwbIwwwwwwbbbbbd", *(DWORD *)(a1 + 464), *CPlayer::Name, *(DWORD *)(a1 + 536), *(DWORD *)(a1 + 468), v52, v51, v50, v49, v48, v47, v46, v45, v44, v43, v42, v41, v40, v39, v38, v37, v36, v35, v34, v33, v32, v31, v30, v29, v28, v27, v26);
	}
}

void IChar::SetLevel(int Level) {
	if (this->IsOnline()) {
		int a1 = (int)this->Offset;
		CChar::CancelBuffParty(this->Offset, -255);
		int LVL = Level - 1;
		*(DWORD *)(a1 + 60) = Level;
		*(DWORD *)(a1 + 472) = 0;
		*(DWORD *)(a1 + 476) = 0;
		/*memset((void *)(a1 + 64), 0, 0x1Cu);
		memset((void *)(a1 + 92), 0, 0x60u);
		memset((void *)(a1 + 188), 0, 0x54u);
		memcpy((void *)(a1 + 64), (char *)(void*)0x004D6A28 + 28 * *(DWORD *)(a1 + 460), 0x14u);
		*(DWORD *)(a1 + 552) = 0;
		*(DWORD *)(a1 + 620) = 0;
		*(DWORD *)(a1 + 616) = 0;
		*(DWORD *)(a1 + 612) = 0;
		*(DWORD *)(a1 + 608) = 0;
		*(DWORD *)(a1 + 604) = 0;
		*(DWORD *)(a1 + 600) = 0;
		*(DWORD *)(a1 + 596) = 0;*/
		//CChar::ResetAllBuff(a1);
		//CPlayer::LevelUpUnknown((void *)(a1 + 624), 0);
		//(*(void(__thiscall **)(int))(*(DWORD *)a1 + 84))(a1);

		CIOCriticalSection::Enter((struct _RTL_CRITICAL_SECTION*)((int)this->Offset + 1020));
		int v3; // eax@2
		int v6; // [sp+4h] [bp-10h]@2
		int v7; // [sp+8h] [bp-Ch]@6
		int v8; // [sp+Ch] [bp-8h]@1
		int v9; // [sp+10h] [bp-4h]@3

		int i = 0;
		Unnamed::nGetObject((int)((int)this->Offset + 1068), (int)&v8);
		while (1)
		{
			v3 = Undefined::Check((int)((int)this->Offset + 1068), (int)&v6);
			if (!(unsigned __int8)Undefined::CheckValues(&v8, v3))
				break;
			v9 = *(DWORD *)(Undefined::GetValue(&v8) + 4);
			if (CItem::IsState(v9, 1)) {
				//(*(void(__thiscall **)(int, int))(*(DWORD *)v9 + 104))(v9, a1);

				if (*(DWORD *)(*(DWORD *)(v9 + 40) + 100) > Level)
					(*(void(__thiscall **)(int, int))(*(DWORD *)v9 + 100))(v9, a1);
			}

			Undefined::sub_446090(&v8, (char*)&v7, 0);
		}
		CIOCriticalSection::Leave((void*)((char*)this->Offset + 1020));

		//CPlayer::LoadSkills((DWORD *)(a1 + 624));
		CPlayer::Write(this->Offset, 69, "bb", 26, *(DWORD *)(a1 + 60));
		CChar::WriteInSight(this->Offset, 73, "db", *(DWORD *)(a1 + 28), 3);
		CPlayer::UpdatePartyMember(a1, 26);
		if (this->GetAdmin() == 0){
			this->AddStatPoint(5);
			this->AddSkillPoint(1);
		}
		else if (this->GetAdmin() >= 3){
			int TotalLevel = this->GetLevel();
			this->AddStatPoint(TotalLevel * 5);
			this->AddSkillPoint(TotalLevel * 1);
		}

		*(DWORD *)(a1 + 276) = CChar::GetMaxMp(a1);
		*(DWORD *)(a1 + 272) = CChar::GetMaxHP(a1);
		int v26 = *(DWORD *)(a1 + 580);
		int v27 = CChar::GetResist((DWORD *)a1, 4);
		int v28 = CChar::GetResist((DWORD *)a1, 3);
		int v29 = CChar::GetResist((DWORD *)a1, 2);
		int v30 = CChar::GetResist((DWORD *)a1, 1);
		int v31 = CChar::GetResist((DWORD *)a1, 0);
		int v32 = *(DWORD *)(a1 + 548);
		int v33 = *(DWORD *)(a1 + 544);
		int v34 = CChar::GetMaxMagic(a1);
		int v35 = CChar::GetMinMagic(a1);
		int v36 = CChar::GetMaxAttack(a1);
		int v37 = CChar::GetMinAttack(a1);
		int v38 = *(DWORD *)(a1 + 476);
		int v39 = *(DWORD *)(a1 + 472);
		int v40 = CChar::GetAbsorb(a1);
		int v41 = CChar::GetDefense((DWORD *)a1, 0);
		int v42 = CChar::GetDodge(a1);
		int v43 = CChar::GetHit(a1);
		int v44 = *(DWORD *)(a1 + 276);
		int v45 = *(DWORD *)(a1 + 276);
		int v46 = *(DWORD *)(a1 + 272);
		int v47 = *(DWORD *)(a1 + 272);
		int v48 = CChar::GetDex(a1);
		int v49 = CChar::GetWis(a1);
		int v50 = CChar::GetInt(a1);
		int v51 = CChar::GetHth(a1);
		int v52 = CChar::GetStr(a1);
		CPlayer::Write(this->Offset, 66, "bsbwwwwwwddwwwwwbIwwwwwwbbbbbd", *(DWORD *)(a1 + 464), *CPlayer::Name, *(DWORD *)(a1 + 536), *(DWORD *)(a1 + 468), v52, v51, v50, v49, v48, v47, v46, v45, v44, v43, v42, v41, v40, v39, v38, v37, v36, v35, v34, v33, v32, v31, v30, v29, v28, v27, v26);
	}
}
void IChar::SetName(std::string NewName) {
	// Set the player name to the new name
	this->GetName() == NewName;
	// Update any references to the player name in the game code
	// For example, you may need to update the player name displayed in the UI
}

void IChar::ChangeName(std::string NewName) {
	// Buff the player and write the name change to the database
	this->Buff(1621, 648000, 0);
	CDBSocket::Write(72, "ddss", this->GetID(), this->GetPID(), this->GetName(), NewName.c_str());

	// Update the player name in the game code
	this->SetName(NewName);
	// Display a message confirming the name change
	this->BoxMsg("Your name has been changed to " + NewName);
}