int __fastcall CBuffCBuffPrtyExIsExpired(int Buff, void *edx, int Player)
{
	IChar Object((void*)Player);

	if (*(DWORD*)(Buff + 4) == 400 && Object.IsOnline() && Object.IsValid())
	{
		int Time = ((*(DWORD*)(Buff + 8)) - GetTickCount()) / 1000;
		int Damage = *(DWORD*)(Buff + 12);
		if ((GetTickCount() / 1000) % 2 == 0 && Object.GetCurHp() > 1)
		{
			if (Damage > Object.GetCurHp()) Damage = Object.GetCurHp() - 1;
			Object.DecreaseHp(Damage);
			if (Object.GetType() == 1 && (*(int(__thiscall **)(int))(*(DWORD*)Player + 64))(Player)) *(DWORD*)(Player + 472) = GetTickCount() + 20000;
		}
	}

	if (*(DWORD*)(Buff + 4) == 411 && Object.IsOnline())
	{
		int Time = ((*(DWORD*)(Buff + 8)) - GetTickCount()) / 1000;
		int Damage = *(DWORD*)(Buff + 12);
		if (Time == 2)
		{
			Object.AddMaxAttack(Damage);
			Object.AddMinAttack(Damage);
		}
	}

	if (*(DWORD*)(Buff + 4) == 415 && Object.IsOnline())
	{
		int Time = ((*(DWORD*)(Buff + 8)) - GetTickCount()) / 1000;
		int Damage = *(DWORD*)(Buff + 12);
		if (Time == 2) Object.AddDef(Damage);
	}

	if (*(DWORD*)(Buff + 4) == 416 && Object.IsOnline())
	{
		int Time = ((*(DWORD*)(Buff + 8)) - GetTickCount()) / 1000;
		int Damage = *(DWORD*)(Buff + 12);
		if (Time == 2) Object.AddOTP(Damage);
	}

	return CBuff::CBuffPrtyExIsExpired(Buff, Player);
}

int __fastcall CBuffPrtyExFreeBuff(int Buff, void *edx, int Player)
{
	IChar IPlayer((void*)Player);

	if (IPlayer.IsOnline())
	{
		if (*(DWORD*)(Buff + 4) == 118 && *(DWORD*)(Buff + 28) == 2 && *(DWORD*)(Buff + 12))
		{
			if (!IPlayer.IsBuff(BuffNames::IceStone))
			{
				IPlayer.Buff(BuffNames::IceStone, 86400, 1);
			}
			else{
				IPlayer.UpdateBuff(BuffNames::IceStone, 86400, IPlayer.GetBuffValue(BuffNames::IceStone) + 1);
			}

			if (IPlayer.GetBuffValue(BuffNames::IceStone) >= iceStoneMax)
			{
				IPlayer.UpdateBuff(BuffNames::IceStone, 86400, iceStoneMax - iceStoneDebuff);
				return (*(int(__cdecl **)(DWORD, DWORD, DWORD, DWORD))(*(DWORD*)Player + 96))(Player, 32, 0, (iceStoneDebuff * iceStoneValue));
			}

		}

		return CBuffPrtyEx::FreeBuff(Buff, Player);
	}

	return 0;
}

int __cdecl CreateBuff(int BuffID, __int32 Time, int Stat, int Object)
{
	if (BuffID == 103)
		return 0;

	if (myc)
		return 0;

	/*if (BuffID == 5 && CGuild::IsWarringPeriod())
		return 0;*/

	if (BuffID == 9 && Time == 900 && Stat == 3 && *(DWORD*)(Object + 4) == 10)
		Stat = 3 * *(DWORD*)(Object + 8);

	if (BuffID == 29 && Object < 0 && Stat < 0)
	{
		Object *= -1;
		Stat *= -1;
	}

	if ((BuffID >= 119 && BuffID <= 155))
	{
		int SetTime = 0;

		if (!Stat)
			SetTime = Time + time(0);

		void *Check = CBuff::CheckBuffCreate(0x20u);

		if (Check)
			return (int)CBuff::CBuffExpire(Check, BuffID, SetTime, 0, 0, 0, 32);
		else
			return 0;
	}
	else if (BuffID >= 156 && BuffID <= 255)
	{
		void *Check = CBuff::CheckBuffCreate(0x28u);

		if (Check)
			return CBuff::CBuffRemainPrty(Check, BuffID, Time, 0, 0, 0, 0);
		else
			return 0;
	}
	else if (BuffID >= 256)
	{
		void *Check = CBuff::CheckBuffCreate(0x2Cu);

		if (Check)
			return CBuff::CBuffPrtyEx(Check, BuffID, Time * 1000, 0, 0, 0, 0, 0, 0, 0);
		else
			return 0;
	}
	else {
		if (BuffID == 74 && Object) {
			int Grade = *(DWORD*)(Object + 8);
			int Buff = CBuff::CreateBuff(74, Time, Stat, Object);
			*(DWORD*)(Buff + 24) = Stat;
			*(DWORD*)(Buff + 28) = 27;
			return Buff;
		}

		return CBuff::CreateBuff(BuffID, Time, Stat, Object);
	}
}

int __fastcall sFindBuff(int Player, void *edx, int Buff)
{
	int i; // [sp+4h] [bp-4h]@1

	for (i = *(DWORD *)(Player + 360); i && *(DWORD *)(i + 4) != Buff; i = *(DWORD *)(i + 20))
		;
	return i;
}
static int callback(void *NotUsed, int argc, char **argv, char **azColName)
{
	int i;
	for (i = 0; i < argc; i++)
	{
		cout << azColName[i] << " = " << (argv[i] ? argv[i] : "NULL") << "\n";
	}
	cout << "\n";
	return 0;
}
/*
void* __fastcall releaseBuff(void* Buff, void *edx, char Argument)
{
int BuffID = (*(DWORD *)((int)Buff + 4));
int ID = getIDFromBuff((int)Buff);

if (ID)
removeBuff(ID, BuffID);

return CBuff::Release(Buff, Argument);
}

void __fastcall SetBuff(int Player, void *edx, int Buff, int Time)
{
int v7; // [sp+4h] [bp-10h]@1
DWORD *v8; // [sp+10h] [bp-4h]@1

v7 = Player;
v8 = (DWORD *)CreateBuff(Buff, Time, 1, 0);
if (v8)
{
if ((*(int(__thiscall **)(DWORD *, int))*v8)(v8, v7))
{
//makeBuff((int)v8, *(DWORD *)(v7 + 28));
insertBuff(*(DWORD *)(v7 + 28), Buff, (int)v8);

CIOCriticalSection::Enter((struct _RTL_CRITICAL_SECTION *)(v7 + 364));
v8[5] = *(DWORD *)(v7 + 360);
*(DWORD *)(v7 + 360) = (int)v8;
CIOCriticalSection::Leave((void*)((char *)v7 + 364));

}
else if (v8)
{
releaseBuff(v8, 0, 1);
}
}
}


int __fastcall FindBuff(int Player, void *edx, int Buff)
{
int i; // [sp+4h] [bp-4h]@1

for (i = *(DWORD *)(Player + 360); i && *(DWORD *)(i + 4) != Buff; i = *(DWORD *)(i + 20))
;

return i;
}
*/
int __fastcall AddBuff(int a1, void *edx, void *a5)
{
	int result; // eax@2
	int v6; // [sp+4h] [bp-14h]@1
	int v7; // [sp+10h] [bp-8h]@4
	int v8; // [sp+14h] [bp-4h]@3

	v6 = a1;
	if (a5)
	{
		//insertBuff(*(DWORD *)(v6 + 28), *(DWORD *)((int)a5 + 4), *(DWORD *)((int)a5 + 12), (int)a5);

		CIOCriticalSection::Enter((struct _RTL_CRITICAL_SECTION *)(a1 + 364));
		v8 = CChar::FindBuff(v6, *((DWORD *)a5 + 1));
		if (v8)
		{
			v7 = (*(int(__thiscall **)(int, void *, int))(*(DWORD *)v8 + 12))(v8, a5, v6);
		}
		else
		{
			v7 = (*(int(__thiscall **)(void *, int))(*(DWORD *)a5 + 4))(a5, v6);
			if (v7)
			{
				*((DWORD *)a5 + 5) = *(DWORD *)(v6 + 360);
				*(DWORD *)(v6 + 360) = (int)a5;
			}
			else if (a5)
			{
				CBuff::Release(a5, 1);
			}
		}

		CIOCriticalSection::Leave((void*)((char *)v6 + 364));

		result = v7;
	}
	else
	{
		result = 0;
	}

	return result;
}
/*
void* __fastcall releaseBuff(void* Buff, void *edx, char Argument)
{
removeBuff((int)Buff);

return CBuff::Release(Buff, Argument);
}
*/
void __fastcall SetBuff(int Player, void *edx, int Buff, int Time)
{
	int v7; // [sp+4h] [bp-10h]@1
	DWORD *v8; // [sp+10h] [bp-4h]@1

	v7 = Player;
	v8 = (DWORD *)CreateBuff(Buff, Time, 1, 0);
	if (v8)
	{
		if ((*(int(__thiscall **)(DWORD *, int))*v8)(v8, v7))
		{
			//insertBuff(*(DWORD *)(v7 + 28), Buff, *(DWORD *)((int)v8 + 12),(int)v8);

			CIOCriticalSection::Enter((struct _RTL_CRITICAL_SECTION *)(v7 + 364));
			v8[5] = *(DWORD *)(v7 + 360);
			*(DWORD *)(v7 + 360) = (int)v8;
			CIOCriticalSection::Leave((void*)((char *)v7 + 364));

		}
		else if (v8)
		{
			CBuff::Release(v8, 1);
		}
	}
}