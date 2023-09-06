#include <windows.h>
#include "IItem.h"
#include "IChar.h"
#include "Functions.h"

#define WEAPON 0   
#define ARMOR 1   
#define ORNAMENT 2   
#define GENERAL 3   
#define QUEST 4   
#define MONEY 5   
#define TRANSFORM 6   

IItem::IItem(void* Offset)
{
	this->Offset = Offset;
}

IItem::~IItem()
{
}

void* IItem::GetOffset()
{
	return this->Offset;
}

bool IItem::Exists() {

	if ((int)this->GetOffset())
	{
		if (CBase::IsDeleted((int)this->GetOffset()))
			return false;
		else
			return true;
	}
	else {
		return false;
	}
}


int IItem::GetInfo()
{
	if (!this->Exists())
		return 0;

	return *(DWORD *)((int)this->Offset + 48);
}

int IItem::GetType()
{
	if (!this->Exists())
		return 0;
	return *(DWORD *)(*(DWORD *)((int)this->Offset + 40) + 72) - 2;
}

int IItem::Prefix()
{
	if (!this->Exists())
		return 0;
	return *(DWORD*)((int)this->Offset + 44);
}

int IItem::PrefixID()
{
	if (this->Prefix())
		return *(DWORD*)(*(DWORD*)((int)this->Offset + 44) + 32);
	else
		return 0;
}

int IItem::GetIntEndurance()
{
	if (!this->Exists())
		return 0;

	return *(DWORD *)(*(DWORD *)((int)this->Offset + 40) + 116);
}

int IItem::GetEndurance()
{
	if (!this->Exists())
		return 0;

	return *(DWORD*)((int)this->Offset + 96);
}

int IItem::GetIID()
{
	if (!this->Exists())
		return 0;
	return *(DWORD *)((int)this->Offset + 36);
}

int IItem::CheckIndex()
{
	if (!this->Exists())
		return 0;
	return *(DWORD *)(*(DWORD *)((int)this->Offset + 40) + 64);
}

int IItem::GetItemClass()
{
	if (!this->Exists())
		return 0;

	return *(DWORD *)(*(DWORD *)((int)this->Offset + 40) + 68);
}

bool IItem::HighMemory()
{
	int Class = this->GetItemClass();

	return (Class == WEAPON || Class == ARMOR || Class == TRANSFORM);
}

bool IItem::IsOrnament()
{
	return (this->GetItemClass() == ORNAMENT);
}

bool IItem::IsWeapon()
{
	return (this->GetItemClass() == WEAPON);
}

bool IItem::IsMoney()
{
	return (this->GetItemClass() == MONEY);
}

bool IItem::IsTransform()
{
	return (this->GetItemClass() == TRANSFORM);
}

bool IItem::IsQuest()
{
	return (this->GetItemClass() == QUEST);
}

bool IItem::IsGeneral()
{
	return (this->GetItemClass() == GENERAL);
}

bool IItem::IsMask()
{
	int Type = *(DWORD *)(*(DWORD *)((int)this->Offset + 40) + 72);
	return (this->GetItemClass() == ARMOR && Type == 20);
}

bool IItem::IsStandard()
{
	int Type = *(DWORD *)(*(DWORD *)((int)this->Offset + 40) + 72);
	return (this->GetItemClass() == ARMOR && Type == 22);
}

bool IItem::IsDefense()
{
	int Type = *(DWORD *)(*(DWORD *)((int)this->Offset + 40) + 72);
	return (this->GetItemClass() == ARMOR && (Type != 20 && Type != 22));
}

int IItem::GetInitItem()
{
	if (!this->Exists())
		return 0;
	return *(DWORD*)((int)this->Offset + 40);
}

void IItem::IncreaseEndurance(int Value)
{
	if (!this->Exists())
		return;

	*(DWORD*)((int)this->Offset + 96) += Value;
}

void IItem::DecreaseEndurance(int Value)
{
	if (!this->Exists())
		return;

	*(DWORD*)((int)this->Offset + 96) -= Value;
}

void IItem::SetInfo(int Value)
{
	if (!this->Exists())
		return;

	*(DWORD *)((int)this->Offset + 48) = Value;
}

int IItem::GetTalismanOA()
{
	if (!this->Exists())
		return 0;

		return *(DWORD *)((int)this->Offset + 100);
}

int IItem::GetTalismanOM()
{
	if (!this->Exists())
		return 0;

	return *(DWORD *)((int)this->Offset + 104);
}

int IItem::GetTOA()
{
	if (!this->Exists())
		return 0;

	return *(DWORD *)((int)this->Offset + 112);
}

int IItem::GetUpgrade()
{
	if (!this->Exists())
		return 0;

	return *(DWORD *)((int)this->Offset + 124);
}

void IItem::SetTalismanOA(int Value)
{
	if (!this->Exists())
		return;

	*(DWORD *)((int)this->Offset + 100) = Value;
}

void IItem::SetTalismanOM(int Value)
{
	if (!this->Exists())
		return;

	*(DWORD *)((int)this->Offset + 104) = Value;
}

void IItem::SetTOA(int Value)
{
	if (!this->Exists())
		return;

	*(DWORD *)((int)this->Offset + 112) = Value;
}

void IItem::SetUpgrade(int Value)
{
	if (!this->Exists())
		return;

	*(DWORD *)((int)this->Offset + 124) = Value;
}

int IItem::GetAmount()
{
	if (!this->Exists())
		return 0;

	return *(DWORD *)((int)this->Offset + 52);
}

int IItem::GetSetGem()
{
	if (!this->Exists())
		return 0;

	return *(DWORD *)((int)this->Offset + 84);
}

void IItem::SetSetGem(int Value)
{
	if (!this->Exists())
		return;

	*(DWORD *)((int)this->Offset + 84) = Value;
}

int IItem::LevelLimit()
{
	if (!this->Exists())
		return 0;
	return *(DWORD *)(*(DWORD *)((int)this->Offset + 40) + 100);
}

void IItem::SetLevelLimit(int Value)
{
	if (!this->Exists())
		return;

	*(DWORD *)(*(DWORD *)((int)this->Offset + 40) + 100) = Value;
}

int IItem::GetItemPointerFromIID(void *Player,int IID)
{
	IChar IPlayer(Player);

	if (IPlayer.IsOnline())
	{
		int CheckValue = 0, Checkx = 0, Recheckx = 0, IID = this->GetIID(), MyItem = 0;
		Undefined::CreateMonsterValue((char*)IPlayer.GetOffset() + 1068, (int)&CheckValue, (int)&IID);
		Checkx = Undefined::Check((int)((char*)IPlayer.GetOffset() + 1068), (int)&Recheckx);

		if (Undefined::CheckValues(&CheckValue, Checkx))
		{
			MyItem = *(DWORD *)(Undefined::GetValue(&CheckValue) + 4);
			return MyItem;
		}
	}

	return 0;
}

int IItem::GetGrade()
{
	if (!this->Exists())
		return 0;

	return *(DWORD *)(*(DWORD *)((int)this->Offset + 40) + 80);
}

int IItem::GetClass()
{
	if (!this->Exists())
		return 0;

	return *(DWORD *)(*(DWORD *)((int)this->Offset + 40) + 96);
}

int IItem::GetXDefense()
{
	if (!this->Exists())
		return 0;

	return *(DWORD *)((int)this->Offset + 108);
}

int IItem::GetXDodge()
{
	if (!this->Exists())
		return 0;

	return *(DWORD *)((int)this->Offset + 116);
}

int IItem::GetXHit()
{
	if (!this->Exists())
		return 0;

	return *(DWORD *)((int)this->Offset + 112);
}

char IItem::GetXAttack()
{
	if (!this->Exists())
		return 0;

	return (char)*(DWORD *)((int)this->Offset + 100);
}

int IItem::GetXMagic()
{
	if (!this->Exists())
		return 0;

	return *(DWORD *)((int)this->Offset + 104);
}

int IItem::GetUpgrRate()
{
	if (!this->Exists())
		return 0;

	return *(DWORD *)((int)this->Offset + 128);
}
