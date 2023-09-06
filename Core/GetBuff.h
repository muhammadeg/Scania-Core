

int __fastcall FindBuff(int Player, void* edx, int BuffID) {
	int i = *(DWORD *)(Player + 360); // [sp+4h] [bp-4h]@1

	while (i) {
		int Diff = (((int)*(DWORD *)i) - ((int)(int *)0x004B4630));

		if (Diff > 10000 || Diff < 0)
			return 0;

		if ((*(DWORD *)(i + 4)) == BuffID)
			return i;

		i = *(DWORD *)(i + 20);
	}
	return 0;
}

//new
int __fastcall CancelAllBuffs(void* Monster, void* edx) {
	IChar IMonster(Monster);
	IChar IPlayer((void*)IMonster.GetMobTanker());

	if (IMonster.IsValid() && IMonster.GetType() == 1) {
		if (MonsterQuests.count(IMonster.GetMobIndex()))
			CheckForDailyQuest((void*)IMonster.GetMobTanker(), Monster);


		if (MQuest.count(IMonster.GetMobIndex())) {
			int SpawnedMobQuest = IMonster.GetBuffValue(BuffNames::SpawnedMobQuest);
			if (SpawnedMobQuest && SummonedQuest.count(SpawnedMobQuest)) {
				MSummonedConfig mSummon = SummonedQuest.findValue(SpawnedMobQuest);
				mSummon.Spawned--;
				SummonedQuest.replaceInsert(SpawnedMobQuest, mSummon);
			}
		}

		if(SummonTrack.count(IMonster.GetMobIndex()))
			CDBSocket::Write(111, "dd", IMonster.GetMobIndex(), -1);


		UpdateAutoMission((void*)IMonster.GetMobTanker(), Monster);

		if (SufferingValley::Active && IMonster.GetMap() == SVMap) {
			IChar IPlayer((void*)IMonster.GetMobTanker());
			bool IsBlue = SVParticipantsBlue.count(IPlayer.GetPID());
			bool IsRed = !IsBlue ? SVParticipantsRed.count(IPlayer.GetPID()) : false;

			if (IsBlue)
				SufferingValley::BlueScore += SVPtMob;
			else if (IsRed)
				SufferingValley::RedScore += SVPtMob;
		}
	}
	
	return CChar::CancelAllBuff2(Monster);
}
//endnew

void* __fastcall ReleaseBuff(void* Buff, void* edx, char Argument) {
	IBuff IBuff(Buff);
	CConsole::Red("%d", IBuff.GetBuffID());

	void* check = CBuff::Release(Buff, Argument);
	
	return check;
}

bool __fastcall HaveBuff(int a5, void* edx, int BuffID, int tries)
{
	int v6; // [sp+0h] [bp-Ch]@1
	int v7; // [sp+4h] [bp-8h]@1
	v6 = a5;
	v7 = 0;

	if (!CBase::IsDeleted(v6)) {
		CriticalLock  lock((struct _RTL_CRITICAL_SECTION *)(v6 + 364));
		v7 = CChar::FindBuff(v6, BuffID);
	}

	if (v7)
		return true;

	return false;
}

bool __fastcall _HaveBuff(int a5, void* edx, int BuffID)
{
	int v6; // [sp+0h] [bp-Ch]@1
	int v7; // [sp+4h] [bp-8h]@1
	v6 = a5;
	v7 = 0;

	if (!CBase::IsDeleted(v6))
		v7 = CChar::FindBuff(v6, BuffID);

	if (v7)
		return true;

	return false;
}

bool isSpecialBuff(int index) {
	return (index == 349 || (index >= 1400 && index <= 7000));
}

int __fastcall hasSpecialBuff(int a5, void* edx, int BuffID) {
	if (BuffList.count(a5)) {
		ConcurrentMap<long int, int> mapper = BuffList.find(a5)->second;
		if(mapper.count(BuffID))
			return 1;
	}
	return 0;
}

int __fastcall GetSpecialBuff(int a5, void* edx, int BuffID)
{
	if (BuffList.count(a5)) {
		ConcurrentMap<long int, int> mapper = BuffList.find(a5)->second;
		if (mapper.count(BuffID))
			return mapper.find(BuffID)->second;
	}
	return 0;
}

void __fastcall addSpecialBuff(int a5, void* edx, int BuffID, int Value)
{
	ConcurrentMap<long int, int> mapper;
	if (BuffList.count(a5))
		mapper = BuffList.find(a5)->second;

	mapper.replaceInsert(BuffID, Value);
	BuffList.replaceInsert(a5, mapper);
}

void __fastcall deleteSpecialBuff(int a5, void* edx, int BuffID)
{
	if (BuffList.count(a5)) {
		ConcurrentMap<long int, int> mapper = BuffList.find(a5)->second;
		if (mapper.count(BuffID)) {
			mapper.erase(BuffID);
			BuffList.replaceInsert(a5, mapper);
		}
	}
}

int __fastcall GetBuffStat(int a5, void* edx, int BuffID, int tries)
{
	int v6; // [sp+0h] [bp-Ch]@1
	int v7 = 0; // [sp+4h] [bp-8h]@1
	int v8; // [sp+8h] [bp-4h]@1

	v6 = a5;
	v8 = 0;
	if (!CBase::IsDeleted(v6)) {
		CriticalLock lock((struct _RTL_CRITICAL_SECTION *)(v6 + 364));
		v7 = CChar::FindBuff(v6, BuffID);
		if (v7)
			v8 = *(DWORD *)(v7 + 12);
	}
	return v8;
}


int __fastcall _GetBuffStat(int a5, void* edx, int BuffID)
{
	int v6 = a5; // [sp+0h] [bp-Ch]@1
	int v7 = 0; // [sp+4h] [bp-8h]@1
	int v8 = 0; // [sp+8h] [bp-4h]@1

	if (!CBase::IsDeleted(v6)) {
		v7 = CChar::FindBuff(v6, BuffID);
		if (v7)
			v8 = *(DWORD *)(v7 + 12);
	}
	return v8;
}

void __fastcall getAllBuffs(void* a5, void* edx, std::map<int, PlayerBuffs>& buffs)
{
	int v6; // [sp+0h] [bp-Ch]@1

	v6 = (int)a5;

	CriticalLock lock((struct _RTL_CRITICAL_SECTION *)(v6 + 364));
	for (int i = *(DWORD *)((int)a5 + 360); i; i = *(DWORD *)(i + 20)) {
		int BuffID = *(DWORD *)(i + 4);
		int Check = *(DWORD *)(i + 8);
		int Value = *(DWORD *)(i + 12);

		if (((BuffID >= 119 && BuffID <= 155) || (BuffID >= 30 && BuffID <= 32) || (BuffID == 99 || BuffID == 101)) && Check > time(0))
			Check = Check - time(0);

		else if (BuffID >= 256 && Check > GetTickCount())
			Check = (Check - GetTickCount()) / 1000;

		PlayerBuffs buff = PlayerBuffs();
		buff.Remain = Check;
		buff.Value = Value;

		buffs.insert((std::pair<int, PlayerBuffs>(BuffID, buff)));
	}
}

int __fastcall showBuffIcons(void* a5, void* edx)
{
	int v6; // [sp+0h] [bp-Ch]@1
	int v8; // [sp+8h] [bp-4h]@1

	v6 = (int)a5;
	v8 = 0;
	if (!CBase::IsDeleted(v6)) {
		CRITICAL_SECTION *sec = (struct _RTL_CRITICAL_SECTION *)(v6 + 364);
		CriticalLock  lock(sec);
		for (int i = *(DWORD *)((int)a5 + 360); i; i = *(DWORD *)(i + 20)) {
			int BuffID = *(DWORD *)(i + 4);
			int Check = *(DWORD *)(i + 8);

			if (((BuffID >= 119 && BuffID <= 155) || (BuffID >= 30 || BuffID <= 32) || (BuffID == 99 || BuffID == 101)) && Check > time(0))
				Check = Check - time(0);

			if (BuffID >= 256 && Check > GetTickCount())
				Check = (Check - GetTickCount()) / 1000;

			CPlayer::Write(a5, 68, "bId", 75, *(DWORD *)(i + 24), *(DWORD *)(i + 28), 0);
			CPlayer::Write(a5, 68, "bIdd", 74, *(DWORD *)(i + 24), *(DWORD *)(i + 28), Check, 0);
		}
		v8 = 1;
	}
	return v8;
}

int __fastcall MyGetBuffRemain(int a5, void* edx, int BuffID, int tries)
{
	int v6; // [sp+0h] [bp-Ch]@1
	int v7 = 0; // [sp+4h] [bp-8h]@1
	int v8; // [sp+8h] [bp-4h]@1

	v6 = a5;
	v8 = 0;
	if (!CBase::IsDeleted(v6)) {
		CriticalLock  lock((struct _RTL_CRITICAL_SECTION *)(v6 + 364));
		v7 = CChar::FindBuff(v6, BuffID);
		if (v7)
			v8 = *(DWORD *)(v7 + 8);
	}
	return v8;
}

int __fastcall _MyGetBuffRemain(int a5, void* edx, int BuffID)
{
	int v6; // [sp+0h] [bp-Ch]@1
	int v7 = 0; // [sp+4h] [bp-8h]@1
	int v8; // [sp+8h] [bp-4h]@1

	v6 = a5;
	v8 = 0;
	if (!CBase::IsDeleted(v6)) {
		v7 = CChar::FindBuff(v6, BuffID);
		if (v7)
			v8 = *(DWORD *)(v7 + 8);
	}
	return v8;
}

void __fastcall _CancelBuffStat(int a5, void* edx, int BuffID)
{
	DWORD* v7; // [sp+4h] [bp-8h]@1
	int i;
	int v5 = a5;
	if (!CBase::IsDeleted(v5)) {
		v7 = (DWORD *)(v5 + 360);
		for (i = *(DWORD *)(v5 + 360); i; i = *(DWORD *)(i + 20))
		{
			if (*(DWORD *)(i + 4) == BuffID)
			{
				(*(void(__thiscall **)(int, int))(*(DWORD *)i + 8))(i, v5);
				*v7 = *(DWORD *)(i + 20);
				if (i)
					CBuff::Release((void *)i, 1);
				break;
			}
			v7 = (DWORD *)(i + 20);
		}
	}
}

void __fastcall _UpdateBuffStat(int a5, void* edx, int BuffID, int Time, int Value)
{
	int v6; // [sp+0h] [bp-Ch]@1
	int v7 = 0; // [sp+4h] [bp-8h]@1

	v6 = a5;
	if (!CBase::IsDeleted(v6)) {
		v7 = CChar::FindBuff(v6, BuffID);
		if (v7)
			*(DWORD *)(v7 + 12) = Value;
		else {
			IChar IPlayer((void*)a5);
			IPlayer._Buff(BuffID, Time, Value);
		}
	}
}

void __fastcall UpdateBuffStat(int a5, void* edx, int BuffID, int Time, int Value,int tries)
{
	int v6; // [sp+0h] [bp-Ch]@1
	int v7 = 0; // [sp+4h] [bp-8h]@1

	v6 = a5; 
	if (!CBase::IsDeleted(v6)) {
		CriticalLock  lock((struct _RTL_CRITICAL_SECTION *)(v6 + 364));
		v7 = CChar::FindBuff(v6, BuffID);
		if (v7)
			*(DWORD *)(v7 + 12) = Value;
		else {
			IChar IPlayer((void*)a5);
			IPlayer._Buff(BuffID, Time, Value);
		}
	}
}

void __fastcall CancelBuffPrty(int a1, void* _edx, int a5)
{
	int v5; // [sp+4h] [bp-14h]@1
	int i; // [sp+10h] [bp-8h]@1
	int *v7; // [sp+14h] [bp-4h]@1

	v5 = a1;
	v7 = (int *)(v5 + 360);
	for (i = *(DWORD *)(v5 + 360); i; i = *v7)
	{
		if (a5 & *(DWORD *)(i + 16))
		{
			(*(void(__thiscall **)(int, int))(*(DWORD *)i + 8))(i, v5);
			*v7 = *(DWORD *)(i + 20);
			if (i)
				CBuff::Release((void *)i, 1);
		}
		else
		{
			v7 = (int *)(i + 20);
		}
	}
}