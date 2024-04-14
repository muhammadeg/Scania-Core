LONG __fastcall WarGState(int Player, void *edx, int Argument)
{

	LONG C = CChar::AddGState(Player, Argument);
	IChar IPlayer((void*)Player);
	if (IPlayer.GetType() == 0) {
		CConsole::Red("%d ", Argument);
		CChar::WriteInSight((void*)Player, 46, "dI", IPlayer.GetID(), (__int64)*(DWORD *)((int)Player + 280));
	}

	return C;
}

void __cdecl WarBegin(int Time)
{

	CCastle::WarBegin(Time);

	CIOCriticalSection::Enter((void*)0x004e2078);
	CIOCriticalSection::Enter((void*)0x004e2098);
	CLink::MoveTo((void*)0x004e200c, (int)0x004e2004);
	CIOCriticalSection::Leave((void*)0x004e2098);
	for (DWORD i = *(DWORD*)0x004E2004; i != 0x004E2004; i = *(DWORD*)i)
	{
		IChar IPlayer((void*)(i - 428));
		if (IPlayer.IsOnline()) {
			int Guild = CPlayer::GetGuild((int)IPlayer.GetOffset());
			if (Guild) {
				if (CCastle::IsAllCastleWarRelation(Guild)) {
					IPlayer.SetProperty(PlayerProperty::CWPlayer, 1);
					CChar::WriteInSight(IPlayer.GetOffset(), 46, "dI", IPlayer.GetID(), (__int64)*(DWORD *)((int)IPlayer.GetOffset() + 280));
				}
				CSkill::ObjectRelease((void*)Guild, (LONG)(Guild + 40));
			}
		}
	}

	CIOCriticalSection::Leave((void*)0x004e2078);

}

time_t __cdecl GetWarEndTime()
{

	time_t v1; // [sp+0h] [bp-8h]@1
	struct tm *v2; // [sp+4h] [bp-4h]@1

	v1 = time(0);
	v2 = localtime(&v1);

	if ((int)*(DWORD**)0x004E1174 & 0x100)
		v2->tm_hour = CWTCEH;
	else
	{
		int DayBefore = CWTCD > 0 ? CWTCD - 1 : 6;
		int DayBefore2 = CWTCD > 0 ? CWTCD - 2 : 5;
		if (CWTCD == 1)
			DayBefore2 = 6;

		int day = v2->tm_wday;
		int i = 0;
		if (day == DayBefore)
			i = 5;
		else if (day == DayBefore2)
			i = 4;
		else if (day == CWTCD)
			i = 6;

		v1 += 86400 * (7 - i);
		v2 = localtime(&v1);
		v2->tm_hour = 7;
	}
	v2->tm_sec = 0;
	v2->tm_min = 0;

	return mktime(v2);
}

int __fastcall WarEnd(void *Value, void *edx)
{
	int Guild = *(DWORD *)((int)Value + 48);
	GuildWinnerCW = Guild;

	if (Guild)
	{
		AllyWinnerCW = *(DWORD *)(Guild + 396);
		int GID = *(DWORD *)((int)Value + 32);
		HuntingAddAll(GID, "Castle Owners");
		CWGID = GID;
		CWGuildName = "Castle Owners";
	}

	WarEndTime = (int)time(0) + 10;
	return CCastle::WarEnd(Value);
}

int __fastcall SiegeGunReply(int NPC, void* edx, int Player)
{
	CPlayer::Write((void*)Player, 0, "bId", 0, __int64(*(DWORD *)(NPC + 280)), *(DWORD *)(NPC + 456));
	return 1;
}

int __fastcall GuildWarDamage(void *Target, void *edx, int Player, int Damage, int a4, int a5, int a6, int a7)
{
	IChar IPlayer((void*)Player);
	IChar ITarget(Target);
	int Argument = 0, v13 = 0, v14 = 0, v10 = 0, Flag = 0, Gate = 0;
	*(DWORD*)a6 = 0;

	if (Damage < 0)
		return 0;

	if (a7)
		Argument = (*(int (__thiscall **)(int))(*(DWORD *)a7 + 52))(a7);
	else
		Argument = 1;

	if (Argument)
	{
		v13 = CChar::GetFinalDamage(Target, Player, Damage, Argument);

		if (v13 > 0)
		{
			CChar::Lock(Target);

			if (CChar::IsNormal((int)Target))
			{
				v14 = v13 + CChar::GetFatalDamage(Player, v13, a5, 0);

				if (v14 >= (int)*((DWORD*)Target + 68))
					v10 = *((DWORD*)Target + 68);
				else
					v10 = v14;

				*(DWORD *)a4 = v10;
				*((DWORD *)Target + 68) -= *(DWORD *)a4;
				*((DWORD *)Target + 118) = GetTickCount() + 20000;

				if (*((DWORD *)Target + 68) > 0)
				{
					CChar::Unlock(Target);
				}
				else {
					*((DWORD *)Target + 68) = 0;
					(*(void(__thiscall **)(int, DWORD, DWORD))(*(DWORD *)Player + 76))(Player, *((DWORD *)Target + 7), *(DWORD *)a5);
					int targetID = *((DWORD *)Target + 7);
					CChar::Unlock(Target);

					CChar::WriteInSight(Target, 61, "db", *((DWORD *)Target + 7), 9);

					if (CInitMonster::IsRace(*((DWORD*)Target + 110), 2))
					{
						Flag = CCastle::GetMonsterTile2CID(*((DWORD *)Target + 79), *((DWORD *)Target + 83), *((DWORD *)Target + 84));
						CGuild::BrokenStandard(Flag);
					}
					else
						if (CInitMonster::IsRace(*((DWORD*)Target + 110), 3))
						{
							Gate = CCastle::GetMonsterTile2CID(*((DWORD *)Target + 79), *((DWORD *)Target + 83), *((DWORD *)Target + 84));
							CGuild::BrokenGate(Gate, (int)Target);
						}

					CBase::Delete(Target);
				}

				return 1;
			} else {
				CChar::Unlock(Target);
				return 1;
			}
		} else {
			return 0;
		}
	} else {
		return 0;
	}
}