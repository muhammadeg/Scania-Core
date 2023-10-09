volatile LONG areas = 0;
void __cdecl Spawn(int index, int amount, int x, int y, int map) {
	int GetMap = Undefined::MapCheck(map);
	
	if (GetMap) {
		int* s_gen = new int[22];
		int factor = 10;
		InterlockedDecrement(&areas);
		CBase::CBase((void*)s_gen);
		*s_gen = *(DWORD*)0x004B7DC8;
		s_gen[8] = index;
		s_gen[9] = map;
		s_gen[10] = areas;
		s_gen[11] = 1;
		s_gen[12] = 0;
		s_gen[13] = factor;
		s_gen[14] = x;
		s_gen[15] = y;
		s_gen[16] = x;
		s_gen[17] = y;
		s_gen[18] = GetMap;
		s_gen[19] = GetTickCount();
		s_gen[20] = 1000;
		s_gen[21] = 0;

		for (int i = 0; i < amount; i++) {
			if (!CMonster::Create((int)s_gen, 0))
				break;
			else
				InterlockedIncrement((volatile LONG *)((int)s_gen + 48));
		}

		delete[] s_gen;
	}
}

void __cdecl GateSummon(char Index, int Map, int X, int Y, int Direction) {
	int *GetSetXY = new int[2];
	GetSetXY[0] = X;
	GetSetXY[1] = Y;
	CMonsterGuildWar::Create(Index, Map, (int)GetSetXY, Direction, 0, "", 0);
	delete[] GetSetXY;
}

int __cdecl Summon(int Player, int Map, int X, int Y, int Index, int Amount, int SafeZoneCheck, int Delay, int Disappear, int Pet)
{
	void *GetMonster = 0; int Value = 0, Monster = 0, Argument = 0;
	int GetMap = Undefined::MapCheck(Map);

	if (GetMap)
	{
		if (SummonTrack.count(Index))
			CDBSocket::Write(111, "dd", Index, 1);

		void *MonsterValueCheck = (void*)Undefined::GetMonsterValue(0x2B0u);

		if (MonsterValueCheck)
			GetMonster = Undefined::MonsterCreate(MonsterValueCheck);
		else
			GetMonster = 0;

		Monster = (int)GetMonster;

		IChar IMonster((void*)Monster);
		CIOCriticalSection::Enter((void*)0x4E182C);
		Undefined::CreateMonsterValue((void*)0x4E1820, (int)&Argument, (int)&Index);
		int GetCheck = Undefined::Check((int)0x4E1820, (int)&Value);

		if (*(DWORD*)(void*)&Argument == *(DWORD*)GetCheck)
		{
			CIOCriticalSection::Leave((void*)0x4E182C);
		}
		else {
			int Check = *(DWORD *)(Undefined::GetValue(&Argument) + 4);

			if (Check && *(DWORD *)(Check + 304))
			{
				int *GetSetXY = new int[2];
				GetSetXY[0] = X;
				GetSetXY[1] = Y;
				*(DWORD *)(Monster + 316) = Map;
				*(DWORD *)(Monster + 320) = GetMap;
				*(DWORD *)(Monster + 512) = Index;
				*(DWORD *)(Monster + 476) = 1;
				
				CChar::SetXY(Monster, (int)GetSetXY);
				delete[] GetSetXY;
				(*(void(__thiscall **)(int, int))(*(DWORD *)Monster + 192))(Monster, Check);
				
				if (Disappear)
					MonsterDisappear.replaceInsert((int)Monster, GetTickCount() + Disappear);

				if (Player) {
					IChar IPlayer((void*)Player);
					int Channel = IPlayer.GetChannel();
					if (Channel)
						*(DWORD *)(Monster + 516) = Channel * -1;
				}

				if (Delay)
				{
					IMonster.Buff(159, (Delay + 2000) / 1000, 0);
					IMonster.Delay(Delay);
					IMonster.UnAttack(Delay);
				}
				if (Pet)
				{
					*(DWORD *)(Monster + 476) = 0;
					*(DWORD *)(Monster + 472) = 0;
					IMonster.SetMobHostility(0);
					IMonster.RemoveDef(IMonster.GetDef());
					IMonster.AddDef(54123);
					IChar IPlayer((void*)Player);
					*(DWORD *)(Monster + 232) = Player;

					IPlayer.SetMobPet(Monster);
				}
				CIOCriticalSection::Leave((void*)0x4E182C);
				CChar::Lock((void*)Monster);
				int *CellMapCoordinate = new int[2];
				CellMapCoordinate[0] = X >> 5;
				CellMapCoordinate[1] = Y >> 5;
				IMonster.MonsterSummonWrite(SafeZoneCheck, Monster, (int)CellMapCoordinate);
				delete[] CellMapCoordinate;
			}
			else {
				CIOCriticalSection::Leave((void*)0x4E182C);
			}
		}
	}
	if (Pet && Monster) {
		*(DWORD *)((int)Monster + 260) = *(DWORD *)(Player + 260) - 50 + MobPets.find(Index)->second;
		CChar::WriteInSight((void*)Monster, 72, "dbw", *(DWORD *)(Monster + 28), 32, *(DWORD *)(Monster + 260));

		InterlockedIncrement(&summonPets);
	}
	return Monster;
}

int __fastcall SummonAI(void *Monster, void *edx)
{
	IChar IMonster(Monster);

	if (IMonster.IsOnline())
	{
		if (MobPets.count(IMonster.GetMobIndex()))
		{
			CChar::Lock(Monster);
			if (*(DWORD *)((int)Monster + 144) == 54123)
			{
				int Player = *(DWORD *)((int)Monster + 232);
				int Tanker = IMonster.GetMobTanker();
				IChar IPlayer((void*)Player);
				if (IPlayer.IsValid())
				{
					IMonster.SetMobHostility(0);
					*(DWORD *)((int)Monster + 232) = (int)IPlayer.GetOffset();
					if (((*(DWORD *)((int)Monster + 260) + 50) - MobPets.find(IMonster.GetMobIndex())->second) != *(DWORD *)((int)IPlayer.GetOffset() + 260)) {
						*(DWORD *)((int)Monster + 260) = *(DWORD *)((int)IPlayer.GetOffset() + 260) - 50 + MobPets.find(IMonster.GetMobIndex())->second;
						CChar::WriteInSight((void*)Monster, 72, "dbw", *(DWORD *)((int)Monster + 28), 32, *(DWORD *)((int)Monster + 260));
					}

					int xDiff = IMonster.GetX() - IPlayer.GetX();
					int yDiff = IMonster.GetY() - IPlayer.GetY();

					int rangeCheck = CChar::GetRange((int)IPlayer.GetOffset() + 332, (int)IMonster.GetOffset() + 332);

					if (rangeCheck > 230 || IMonster.GetMap() != IPlayer.GetMap() || IMonster.GetChannel() != IPlayer.GetChannel())
					{
						int Index = IMonster.GetMobIndex();

						*(DWORD *)((int)Monster + 472) = 0;
						CChar::Unlock(Monster);
						IMonster.MobDelete();
						Summon((int)IPlayer.GetOffset(), IPlayer.GetMap(), IPlayer.GetX() - 6, IPlayer.GetY() - 6, Index, 1, false, 0, 0, 2);

						return 0;
					}
					else {
						if (rangeCheck > 12 && (!Tanker || (rangeCheck > 40 && *(DWORD *)((int)Monster + 472) && *(DWORD *)((int)Monster + 472) >= GetTickCount()))) {
							*(DWORD *)((int)Monster + 472) = 0;
							Undefined::MonsterPath(*(void **)((int)Monster + 320), (int)Monster, -xDiff - 6, -yDiff - 6, 0, 1);
							CChar::Unlock(Monster);
							return 0;
						}
					}
				}
				else if (IPlayer.IsOnline()) {
					IMonster.SetMobTarget(0);
					*(DWORD *)((int)Monster + 472) = 0;
					CChar::Unlock(Monster);
					return 0;
				}
				else {
					*(DWORD *)((int)Monster + 472) = 0;
					CChar::Unlock(Monster);
					IMonster.MobDelete();
					return 0;
				}

				if (!Tanker) {
					*(DWORD *)((int)Monster + 472) = 0;
					CChar::Unlock(Monster);
					return 0;
				}
				else {
					IChar ITarget((void*)Tanker);
					if (!ITarget.IsValid() || ITarget.GetCurHp() <= 0 || ITarget.GetMobTanker() != Player) {
						IMonster.SetMobTarget(0);
						*(DWORD *)((int)Monster + 472) = 0;
						CChar::Unlock(Monster);
						return 0;
					}
				}
			}

			CChar::Unlock(Monster);
		}

		if (IMonster.GetMobIndex() == 566 && F10::DunamicSkillDelay)
			return 0;

		if (IMonster.GetMobIndex() == 572 && F10::CheiosSkillDelay)
			return 0;

		if (IMonster.GetMobIndex() == CaptureMonster || IMonster.GetMobIndex() == CPGate)
			return 0;

		if (IMonster.GetMobIndex() == 369)
			return 0;

		if (IMonster.GetMobIndex() == 445 || IMonster.GetMobIndex() == 448)
			return 0;

		if (IMonster.GetMobIndex() >= 352 && IMonster.GetMobIndex() <= 360)
			return 0;

		if (IMonster.GetMobIndex() == 384)
			return 0;
	}

	return CMonsterMaguniMaster::AI(Monster);
}

int __fastcall SummonDie(int Monster, void *edx, int TankerID, int Arg1, int Arg2, int Arg3)
{

	IChar IMonster((void*)Monster);

	if (SinEvent::Active && IMonster.GetMapX() == SEMapX && IMonster.GetMapY() == SEMapY) {
		IChar IPlayer((void*)TankerID);
		IPlayer.UpdateBuff(BuffNames::SinEventMobs, BuffNames::BuffTime, IPlayer.GetBuffValue(BuffNames::SinEventMobs) + SEPtsPerMob);
	}

	// Monsters Rewards
	if (MonstersRewards.count(IMonster.GetMobIndex())) {
		int RewardID = MonstersRewards.find(IMonster.GetMobIndex())->second.rewardid;
		int PlayerChance = MonstersRewards.find(IMonster.GetMobIndex())->second.pickchance;
		int Around = IMonster.GetObjectListAround(50);
		int Size = 0;
		int PlayersToPick = 0;
		bool rewardAllPlayers = false;

		if (PlayerChance == 100) {
			rewardAllPlayers = true;
		}
		else {
			while (Around) {
				IChar Object((void*)CBaseList::Offset((void*)Around));
				if (Object.IsValid() && Object.GetType() == 0)
					Size++;
				Around = CBaseList::Pop((void*)Around);
			}
			PlayersToPick = round(Size * (PlayerChance / 100.0));
		}

		int PlayersPicked = 0;
		std::string namePicked = "";
		int x = 1;
		Around = IMonster.GetObjectListAround(50);
		int Randomize = CTools::Rate(1, Size); // Add this line to define and initialize Randomize
		while (Around && (rewardAllPlayers || PlayersPicked < PlayersToPick)) {
			IChar Object((void*)CBaseList::Offset((void*)Around));
			if (Object.GetType() == 0) {
				int PlayerPickChance = CTools::Rate(1, 100);
				if (rewardAllPlayers || (PlayerPickChance <= PlayerChance && x >= Randomize)) {
					Object.systemReward(RewardID);

					if (!MonstersItem.empty()) {
						int Chance = CTools::Rate(1, 100);
						int Index = 0;
						int Value = 0;
						bool itemFound = false;

						for (int i = 0; i < MonstersItem.size(); i++) {
							ChanceItem f = MonstersItem[i];
							if (f.Chance >= Chance) {
								Index = f.Index;
								Value = f.Amount;
								itemFound = true;
								break;
							}
						}

						if (itemFound) {
							Object.InsertItem(Index, 0, Value);
							namePicked = Object.GetName();
							if (!namePicked.empty()) {
								std::string notice = namePicked + " has been randomly picked to receive " + thisServerName + " Reward";
								CPlayer::WriteAll(0xFF, "dsd", 247, notice.c_str(), 2);
							}
							PlayersPicked++;
						}
					}
				}

				x++;
			}

			Around = CBaseList::Pop((void*)Around);
		}
	}
	// Monsters Reward end



	if (BossEXP::Active && Monster == BossEXP::Boss) {
		std::string SysMsg(BossEXPFinalMsg);
		CPlayer::WriteInMap(BossEXPMap, 0xFF, "dsd", 247, SysMsg.c_str(), 3);
		int Size = 0;
		int Around = IMonster.GetObjectListAround(50);
		while (Around)
		{
			IChar Object((void*)CBaseList::Offset((void*)Around));
			if (Object.IsValid() && Object.GetType() == 0)
				Size++;
			Around = CBaseList::Pop((void*)Around);
		}

		int PlayersPicked = 0;
		std::string namePicked = "";
		// CTools::Rate(0, Size) modify to this if there were any problems -Scania
		int Randomize = CTools::Rate(0, Size - BossEXPChance);
		int x = 1;
		Around = IMonster.GetObjectListAround(50);

		while (Around)
		{
			IChar Object((void*)CBaseList::Offset((void*)Around));

			if (Object.GetType() == 0 && Object.IsBuff(BuffNames::BossEXP))
			{
				/* Maut EXP Start */
				if (!BossEXPLimit || (BossEXPLimit && !isRewarded(Object))) {
					if (BossEXPs.count(Object.GetLevel())) {
						F10EXP mautExp = BossEXPs.find(Object.GetLevel())->second;

						if (mautExp.Gap) {
							for (int i = 0; i<mautExp.Mult; i++)
								(*(int(__cdecl **)(int, signed int, signed int, unsigned __int64, unsigned __int64))(*(DWORD *)Object.GetOffset() + 88))((int)Object.GetOffset(), 25, 1, (unsigned __int64)mautExp.Exp, HIDWORD(mautExp.Exp));
						}
						else
						{
							for (int i = 0; i<mautExp.Mult; i++)
								CPlayer::UpdateProperty((int)Object.GetOffset(), 25, 1, mautExp.Exp);
						}

						Object.systemReward(mautExp.RID);
					}

					if (!BossExpItem.empty() && PlayersPicked < BossEXPChance && x >= Randomize) {

						int Chance = CTools::Rate(1, 1000);
						int Index = 0;
						int Value = 0;
						for (int i = 0; i < BossExpItem.size(); i++) {
							ChanceItem f = BossExpItem[i];
							if ((f.Chance * 10) >= Chance) {
								Index = f.Index;
								Value = f.Amount;
								break;
							}
						}
						if (!Index) {
							Index = BossExpItem[BossExpItem.size() - 1].Index;
							Value = BossExpItem[BossExpItem.size() - 1].Amount;
						}
						Object.InsertItem(Index, 0, Value);
						namePicked = (std::string)Object.GetName();
						if (!namePicked.empty()) {
							std::string notice = namePicked + " has been randomly picked to receive a special Reward";
							CPlayer::WriteAll(0xFF, "dsd", 247, notice.c_str(), 2);
						}
						PlayersPicked++;
					}
					if (BossEXPLimit)
						rewardLimit(Object);
				}
				Object.CloseScreenTime();
				Object.CancelBuff(BuffNames::BossEXP);
				x++;
			}

			Around = CBaseList::Pop((void*)Around);
		}

		RewardLimit.clear();
		BossEXP::Boss = 0;
		BossEXP::Timer = 0;
		BossEXP::KillCount = 0;
		BossEXP::RegisterAmount = 0;
		BossEXPRegistration.clear();
		BossEXP::Active = false;
	}

	if (Maut::Active && Monster == Maut::Boss) {
		CPlayer::WriteInMap(MautMap, 0xFF, "dsd", 247, "Thank you for saving the world...", 3);
		int Size = 0;
		int Around = IMonster.GetObjectListAround(50);
		while (Around)
		{
			IChar Object((void*)CBaseList::Offset((void*)Around));
			if (Object.IsValid() && Object.GetType() == 0)
				Size++;
			Around = CBaseList::Pop((void*)Around);
		}

		int PlayersPicked = 0;
		std::string namePicked = "";
		int Randomize = CTools::Rate(0, Size);
		int x = 1;
		Around = IMonster.GetObjectListAround(50);

		while (Around)
		{
			IChar Object((void*)CBaseList::Offset((void*)Around));

			if (Object.GetType() == 0 && Object.IsBuff(BuffNames::Mautareta))
			{
				/* Maut EXP Start */
				if (!MautLimit || (MautLimit && !isRewarded(Object))) {
					if (MautEXPs.count(Object.GetLevel())) {
						F10EXP mautExp = MautEXPs.find(Object.GetLevel())->second;

						if (mautExp.Gap) {
							for (int i = 0; i<mautExp.Mult; i++)
								(*(int(__cdecl **)(int, signed int, signed int, unsigned __int64, unsigned __int64))(*(DWORD *)Object.GetOffset() + 88))((int)Object.GetOffset(), 25, 1, (unsigned __int64)mautExp.Exp, HIDWORD(mautExp.Exp));
						}
						else
						{
							for (int i = 0; i<mautExp.Mult; i++)
								CPlayer::UpdateProperty((int)Object.GetOffset(), 25, 1, mautExp.Exp);
						}

						Object.systemReward(mautExp.RID);
					}
					else {
						if (Object.GetLevel() >= 1 && Object.GetLevel() <= 70)
							(*(int(__cdecl **)(int, signed int, signed int, unsigned __int64, unsigned __int64))(*(DWORD *)Object.GetOffset() + 88))((int)Object.GetOffset(), 25, 1, (unsigned __int64)MautExp1, HIDWORD(MautExp1));
						if (Object.GetLevel() >= 71 && Object.GetLevel() < 75)
							(*(int(__cdecl **)(int, signed int, signed int, unsigned __int64, unsigned __int64))(*(DWORD *)Object.GetOffset() + 88))((int)Object.GetOffset(), 25, 1, (unsigned __int64)MautExp2, HIDWORD(MautExp2));
						if (Object.GetLevel() >= 75 && Object.GetLevel() < 80)
							(*(int(__cdecl **)(int, signed int, signed int, unsigned __int64, unsigned __int64))(*(DWORD *)Object.GetOffset() + 88))((int)Object.GetOffset(), 25, 1, (unsigned __int64)MautExp3, HIDWORD(MautExp3));
						if (Object.GetLevel() >= 80 && Object.GetLevel() < 85) {
							for (int i = 0; i < MautMultiply; i++)
								CPlayer::UpdateProperty((int)Object.GetOffset(), 25, 1, MautExp4);
						}
						if (Object.GetLevel() >= 85 && Object.GetLevel() < 90) {
							for (int i = 0; i < MautMultiply; i++)
								CPlayer::UpdateProperty((int)Object.GetOffset(), 25, 1, MautExp5);
						}
						if (Object.GetLevel() >= 90 && Object.GetLevel() < 95) {
							for (int i = 0; i < MautMultiply; i++)
								CPlayer::UpdateProperty((int)Object.GetOffset(), 25, 1, MautExp6);
						}
						if (Object.GetLevel() >= 95 && Object.GetLevel() <= 100) {
							for (int i = 0; i < MautMultiply; i++)
								CPlayer::UpdateProperty((int)Object.GetOffset(), 25, 1, MautExp7);
						}
						else if (Object.GetLevel() > 100) {
							for (int i = 0; i < MautMultiply; i++)
								CPlayer::UpdateProperty((int)Object.GetOffset(), 25, 1, MautExp8);
						}
					}
					/* Maut EXP End */

					if (!MautItem.empty() && PlayersPicked < MautChance && x >= Randomize) {

						int Chance = CTools::Rate(1, 1000);
						int Index = 0;
						int Value = 0;
						for (int i = 0; i < MautItem.size(); i++) {
							ChanceItem f = MautItem[i];
							if ((f.Chance * 10) >= Chance) {
								Index = f.Index;
								Value = f.Amount;
								break;
							}
						}
						if (!Index) {
							Index = MautItem[MautItem.size() - 1].Index;
							Value = MautItem[MautItem.size() - 1].Amount;
						}
						Object.InsertItem(Index, 0, Value);
						namePicked = (std::string)Object.GetName();
						if (!namePicked.empty()) {
							std::string notice = namePicked + " has been randomly picked to receive Mautareta Reward";
							CPlayer::WriteAll(0xFF, "dsd", 247, notice.c_str(), 2);
						}
						PlayersPicked++;
					}
					if (MautLimit)
						rewardLimit(Object);
				}
				Object.CloseScreenTime();
				Object.CancelBuff(BuffNames::Mautareta);
				x++;
			}

			Around = CBaseList::Pop((void*)Around);
		}
		RewardLimit.clear();
		Maut::Boss = 0;
		Maut::Timer = 0;
		Maut::KillCount = 0;
		Maut::RegisterAmount = 0;
		MautRegistration.clear();
		Maut::Active = false;
	}

	if (GuildRaid::Active && IMonster.GetOffset() == GuildRaid::Boss)
	{
		CChar::WriteInSight((void*)Monster, 0xFF, "dsd", 247, "Guild Raid System successfully completed.", 1);
		int Around = IMonster.GetObjectListAround(50);

		while (Around)
		{
			IChar Object((void*)CBaseList::Offset((void*)Around));

			if (Object.GetType() == 0 && Object.GetGID() == GuildRaid::GID && !isRewarded(Object)) {
				Object.AddReward(GuildRaid::Reward);
				Object.CloseScreenTime();
				rewardLimit(Object);
			}

			Around = CBaseList::Pop((void*)Around);
		}

		RewardLimit.clear();
		GuildRaid::Active = false;
		GuildRaid::Reward = 0;
		GuildRaid::GID = 0;
		GuildRaid::Time = 0;
		GuildRaid::Boss = 0;
	}

	if (Hunting::Active == true && IMonster.GetOffset() == Hunting::Monster)
	{
		int Around = IMonster.GetObjectListAround(50);

		while(Around)
		{
			IChar Object((void*)CBaseList::Offset((void*)Around));

			if (Object.GetType() == 0 && (!F10Limit || (F10Limit && !isRewarded(Object))) && Object.GetMap() == HGMapI) {
				if (F10EXPs.count(Object.GetLevel())) {
					F10EXP f10Exp = F10EXPs.find(Object.GetLevel())->second;

					if (f10Exp.Gap) {
						for (int i = 0; i<f10Exp.Mult; i++)
							(*(int(__cdecl **)(int, signed int, signed int, unsigned __int64, unsigned __int64))(*(DWORD *)Object.GetOffset() + 88))((int)Object.GetOffset(), 25, 1, (unsigned __int64)f10Exp.Exp, HIDWORD(f10Exp.Exp));
					}
					else
					{
						for (int i = 0; i<f10Exp.Mult; i++)
							CPlayer::UpdateProperty((int)Object.GetOffset(), 25, 1, f10Exp.Exp);
					}

					Object.systemReward(f10Exp.RID);
				}
				else {
					if (Object.GetLevel() >= 1 && Object.GetLevel() <= 70)
						(*(int(__cdecl **)(int, signed int, signed int, unsigned __int64, unsigned __int64))(*(DWORD *)Object.GetOffset() + 88))((int)Object.GetOffset(), 25, 1, (unsigned __int64)F10Exp1, HIDWORD(F10Exp1));
					if (Object.GetLevel() >= 71 && Object.GetLevel() < 75)
						(*(int(__cdecl **)(int, signed int, signed int, unsigned __int64, unsigned __int64))(*(DWORD *)Object.GetOffset() + 88))((int)Object.GetOffset(), 25, 1, (unsigned __int64)F10Exp2, HIDWORD(F10Exp2));
					if (Object.GetLevel() >= 75 && Object.GetLevel() < 80)
						(*(int(__cdecl **)(int, signed int, signed int, unsigned __int64, unsigned __int64))(*(DWORD *)Object.GetOffset() + 88))((int)Object.GetOffset(), 25, 1, (unsigned __int64)F10Exp3, HIDWORD(F10Exp3));
					if (Object.GetLevel() >= 80 && Object.GetLevel() < 85) {
						for (int i = 0; i < F10Multiply; i++)
							CPlayer::UpdateProperty((int)Object.GetOffset(), 25, 1, F10Exp4);
					}
					if (Object.GetLevel() >= 85 && Object.GetLevel() < 90) {
						for (int i = 0; i < F10Multiply; i++)
							CPlayer::UpdateProperty((int)Object.GetOffset(), 25, 1, F10Exp5);
					}
					if (Object.GetLevel() >= 90 && Object.GetLevel() < 95) {
						for (int i = 0; i < F10Multiply; i++)
							CPlayer::UpdateProperty((int)Object.GetOffset(), 25, 1, F10Exp6);
					}
					if (Object.GetLevel() >= 95 && Object.GetLevel() <= 100) {
						for (int i = 0; i < F10Multiply; i++)
							CPlayer::UpdateProperty((int)Object.GetOffset(), 25, 1, F10Exp7);
					}
					else if (Object.GetLevel() > 100) {
						for (int i = 0; i < F10Multiply; i++)
							CPlayer::UpdateProperty((int)Object.GetOffset(), 25, 1, F10Exp8);
					}

					Object.systemReward(HGEA);
				}

				Object.CloseScreenTime();
				if(F10Limit)
					rewardLimit(Object);
			}
			Around = CBaseList::Pop((void*)Around);
		}
		RewardLimit.clear();
	}

	if (Raid::Active) {
		if (IMonster.GetMobIndex() == Raid1 && Raid::Round == 1) {
			int Around = IMonster.GetObjectListAround(50);

			while (Around)
			{
				IChar Object((void*)CBaseList::Offset((void*)Around));

				if (Object.GetType() == 0 && Object.IsBuff(175))
				{
					if (GetInventorySize((int)Object.GetOffset(), 0) < 60 && !isRewarded(Object)) {
						CItem::InsertItem((int)Object.Offset, 27, RaidReward1, 0, RaidAmount1, -1);
						Object.SetHonor(RaidHonor, RaidRP, 0, 0, 0, 0, 0, 0, 0, 0);
						rewardLimit(Object);
					}
					Object.CloseScreenTime();
					Object.Teleport(RaidMap, 232398, 231201);
				}

				Around = CBaseList::Pop((void*)Around);
			}
			CChar::WriteInSight((void*)Monster, 0xFF, "dsd", 247, "Don't get happy yet, this was my weakest warrior.", 1);
			Raid::Round = 2;
			Raid::Time = 488;
		}
		if (IMonster.GetMobIndex() == Raid2 && Raid::Round == 2) {
			int Around = IMonster.GetObjectListAround(50);

			while (Around)
			{
				IChar Object((void*)CBaseList::Offset((void*)Around));

				if (Object.GetType() == 0 && Object.IsBuff(175))
				{
					if (GetInventorySize((int)Object.GetOffset(), 0) < 60 && !isRewarded(Object)) {
						CItem::InsertItem((int)Object.Offset, 27, RaidReward2, 0, RaidAmount2, -1);
						Object.SetHonor(RaidHonor, RaidRP, 0, 0, 0, 0, 0, 0, 0, 0);
						rewardLimit(Object);
					}
					Object.CloseScreenTime();
					Object.Teleport(RaidMap, 235373, 235589);
				}

				Around = CBaseList::Pop((void*)Around);
			}
			CChar::WriteInSight((void*)Monster, 0xFF, "dsd", 247, "This is only a training, you have not seen anything!", 1);
			Raid::Round = 3;
			Raid::Time = 668;
		}

		if (IMonster.GetMobIndex() == Raid3 && Raid::Round == 3) {
			int Around = IMonster.GetObjectListAround(50);

			while (Around)
			{
				IChar Object((void*)CBaseList::Offset((void*)Around));

				if (Object.GetType() == 0 && Object.IsBuff(175))
				{
					if (GetInventorySize((int)Object.GetOffset(), 0) < 60 && !isRewarded(Object)) {
						CItem::InsertItem((int)Object.Offset, 27, RaidReward3, 0, RaidAmount3, -1);
						Object.SetHonor(RaidHonor, RaidRP, 0, 0, 0, 0, 0, 0, 0, 0);
						rewardLimit(Object);
					}
					Object.CloseScreenTime();
					Object.Teleport(RaidMap, 234120, 230825);
				}

				Around = CBaseList::Pop((void*)Around);
			}

			CChar::WriteInSight((void*)Monster, 0xFF, "dsd", 247, "I see... You are tougher than I thought!", 1);
			Raid::Round = 4;
			Raid::Time = 908;
		}

		if (IMonster.GetMobIndex() == Raid4 && Raid::Round == 4) {
			int Around = IMonster.GetObjectListAround(50);

			while (Around)
			{
				IChar Object((void*)CBaseList::Offset((void*)Around));

				if (Object.GetType() == 0 && Object.IsBuff(175))
				{
					if (GetInventorySize((int)Object.GetOffset(), 0) < 60 && !isRewarded(Object)) {
						CItem::InsertItem((int)Object.Offset, 27, RaidReward4, 0, RaidAmount4, -1);
						Object.SetHonor(RaidHonor, RaidRP, 0, 0, 0, 0, 0, 0, 0, 0);
						rewardLimit(Object);
					}
					Object.CloseScreenTime();
					Object.Teleport(RaidMap, 236830, 233300);
				}

				Around = CBaseList::Pop((void*)Around);
			}

			CChar::WriteInSight((void*)Monster, 0xFF, "dsd", 247, "You are getting on my nerves!", 1);
			Raid::Round = 5;
			Raid::Time = 1208;
		}

		if (IMonster.GetMobIndex() == Raid5 && Raid::Round == 5) {
			int Around = IMonster.GetObjectListAround(50);

			while (Around)
			{
				IChar Object((void*)CBaseList::Offset((void*)Around));

				if (Object.GetType() == 0 && Object.IsBuff(175))
				{
					if (GetInventorySize((int)Object.GetOffset(), 0) < 60 && !isRewarded(Object)) {
						CItem::InsertItem((int)Object.Offset, 27, RaidReward5, 0, RaidAmount5, -1);
						Object.SetHonor(RaidHonor, RaidRP, 0, 0, 0, 0, 0, 0, 0, 0);
						rewardLimit(Object);
					}
					Object.CloseScreenTime();
					Object.Teleport(RaidMap, 231806, 235225);
				}

				Around = CBaseList::Pop((void*)Around);
			}

			CChar::WriteInSight((void*)Monster, 0xFF, "dsd", 247, "AAAAAARGH!!!!!!!!!!!!!!!!!!", 1);
			Raid::Round = 6;
			Raid::Time = 1448;
		}

		if (IMonster.GetMobIndex() == Raid6 && Raid::Round == 6) {
			int Around = IMonster.GetObjectListAround(50);

			while (Around)
			{
				IChar Object((void*)CBaseList::Offset((void*)Around));

				if (Object.GetType() == 0 && Object.IsBuff(175))
				{
					if (GetInventorySize((int)Object.GetOffset(), 0) < 60 && !isRewarded(Object)) {
						CItem::InsertItem((int)Object.Offset, 27, RaidReward6, 0, RaidAmount6, -1);
						Object.SetHonor(RaidHonor, RaidRP, 0, 0, 0, 0, 0, 0, 0, 0);
						rewardLimit(Object);
					}
					Object.CloseScreenTime();
					Object.Teleport(RaidMap, 231781, 235363);
				}

				Around = CBaseList::Pop((void*)Around);
			}

			CChar::WriteInSight((void*)Monster, 0xFF, "dsd", 247, "STOP IT!!!!!!!!!!!!!!!!!!", 1);
			Raid::Round = 7;
			Raid::Time = 1628;
		}

		if (IMonster.GetMobIndex() == Raid7 && Raid::Round == 7) {
			int Around = IMonster.GetObjectListAround(50);

			while (Around)
			{
				IChar Object((void*)CBaseList::Offset((void*)Around));

				if (Object.GetType() == 0 && Object.IsBuff(175))
				{
					if (GetInventorySize((int)Object.GetOffset(), 0) < 60 && !isRewarded(Object)) {
						CItem::InsertItem((int)Object.Offset, 27, RaidReward7, 0, RaidAmount7, -1);
						Object.SetHonor(RaidHonor, RaidRP, 0, 0, 0, 0, 0, 0, 0, 0);
						rewardLimit(Object);
					}
					Object.CloseScreenTime();
					Object.Teleport(RaidMap, 236830, 233300);
				}

				Around = CBaseList::Pop((void*)Around);
			}

			CChar::WriteInSight((void*)Monster, 0xFF, "dsd", 247, "MADNESS!!!!!", 1);
			Raid::Round = 8;
			Raid::Time = 1688;
		}

		if (IMonster.GetMobIndex() == Raid8 && Raid::Round == 8) {
			int Around = IMonster.GetObjectListAround(50);

			while (Around)
			{
				IChar Object((void*)CBaseList::Offset((void*)Around));

				if (Object.GetType() == 0 && Object.IsBuff(175))
				{
					if (GetInventorySize((int)Object.GetOffset(), 0) < 60 && !isRewarded(Object)) {
						CItem::InsertItem((int)Object.Offset, 27, RaidReward8, 0, RaidAmount8, -1);
						Object.SetHonor(RaidHonor, RaidRP, 0, 0, 0, 0, 0, 0, 0, 0);
						rewardLimit(Object);
					}
					Object.CloseScreenTime();
					Object.Teleport(RaidMap, 231806, 235225);
				}

				Around = CBaseList::Pop((void*)Around);
			}

			CChar::WriteInSight((void*)Monster, 0xFF, "dsd", 247, "Getting Ready...", 1);
			Raid::Round = 9;
			Raid::Time = 1808;
		}

		if (IMonster.GetMobIndex() == Raid9 && Raid::Round == 9) {
			int Around = IMonster.GetObjectListAround(50);

			while (Around)
			{
				IChar Object((void*)CBaseList::Offset((void*)Around));

				if (Object.GetType() == 0 && Object.IsBuff(175))
				{
					if (GetInventorySize((int)Object.GetOffset(), 0) < 60 && !isRewarded(Object)) {
						CItem::InsertItem((int)Object.Offset, 27, RaidReward9, 0, RaidAmount9, -1);
						Object.SetHonor(RaidHonor, RaidRP, 0, 0, 0, 0, 0, 0, 0, 0);
						rewardLimit(Object);
					}
					Object.CloseScreenTime();
				}

				Around = CBaseList::Pop((void*)Around);
			}

			CChar::WriteInSight((void*)Monster, 0xFF, "dsd", 247, "Do not think this is over...", 1);
			Raid::Round = 10;
			Raid::Time = 1808;
		}

		if (IMonster.GetMobIndex() == Raid9 && Raid::Round == 11) {
			int Around = IMonster.GetObjectListAround(50);

			while (Around)
			{
				IChar Object((void*)CBaseList::Offset((void*)Around));

				if (Object.GetType() == 0 && Object.IsBuff(175))
				{
					if (GetInventorySize((int)Object.GetOffset(), 0) < 60 && !isRewarded(Object)) {
						CItem::InsertItem((int)Object.Offset, 27, RaidReward9, 0, RaidAmount9 * 2, -1);
						Object.SetHonor(RaidHonor * 2, RaidRP * 2, 0, 0, 0, 0, 0, 0, 0, 0);
						rewardLimit(Object);
					}
					Object.CloseScreenTime();
					Object.SystemMessage("You have successfully completed " + thisServerName + " Raid System!", TEXTCOLOR_GREEN);
					Object.CancelBuff(175);
				}

				Around = CBaseList::Pop((void*)Around);
			}

			CChar::WriteInSight((void*)Monster, 0xFF, "dsd", 247, "ARGHHHH! I WILL COME BACK STRONGER TOMORROW!", 1);
			RewardLimit.clear();
			Raid::Round = 0;
			Raid::Time = 0;
			Raid::Active = false;
		}
	}

	if (IMonster.GetMobIndex() == BossIndex) {
		int Around = IMonster.GetObjectListAround(50);
		void* WinOffset = 0;
		while (Around)
		{
			IChar Object((void*)CBaseList::Offset((void*)Around));
			int Value = Object.GetBuffValue(BuffNames::BossHunt);
			if (Value) {
				if (Value == BossHunting::maxDmg) {
					Object.systemReward(BossHuntReward);
					WinOffset = Object.GetOffset();
				}
			}
			Around = CBaseList::Pop((void*)Around);
		}

		if (WinOffset) {
			IChar Winner(WinOffset);
			if (Winner.IsOnline())
				CChar::WriteInSight(WinOffset, 0xFF, "dsd", 247, "Congratulations to " + (std::string)Winner.GetName() + " for being our " + thisServerName + " Hunter.", 5);
		}

		BossHunting::maxDmg = 0;
		BossHunting::Time = 0;
		RewardLimit.clear();
	}

	if (CaptureFlag::Active == true && IMonster.GetMobIndex() == CaptureMonster && IMonster.GetMap() == CaptureMap) {
		IChar Tanker((void*)TankerID);
		if (Tanker.IsOnline()) {
			CaptureFlag::CurrentCapturers = 0;
			CaptureFlag::MonsterOffset = 0;
			CChar::WriteInSight((void*)Monster, 0xFF, "dsd", 247, (std::string)Tanker.GetName() + " has taken the flag.", NOTICECOLOR_REDLONG);
			Tanker.SystemMessage("You are now the Flag Owner", TEXTCOLOR_GREEN);
			CaptureFlag::PlayerID = (int)Tanker.GetOffset();
		}
	}

	if (Hell::Active && IMonster.GetMap() == HellMap)
	{
		if (IMonster.GetMobIndex() == 667)
		{
			int Around = IMonster.GetObjectListAround(50);

			while (Around)
			{
				IChar Object((void*)CBaseList::Offset((void*)Around));

				if (Object.GetType() == 0 && Object.IsBuff(166))
					Object.systemReward(WinnerHell);

				Around = CBaseList::Pop((void*)Around);
			}
			Hell::Lapse = GetTickCount() + 5000;
		}

		Hell::KillCount += 1;
	}

	if (IMonster.GetMobIndex() == 572)
	{
		F10::Ilyer = Summon(0, 21, 117332, 36840, 573, 1, 0, 15000, 3616000, 0);
		F10::KillCount += 1;
		CPlayer::WriteInMap(21, 0xFF, "dsd", 247, "Aghhhh! You thought it's over? HAHAHA! It's my turn now.", 1);

	}

	if (IMonster.GetMobIndex() == 566)
		F10::KillCount += 1;

	if (IMonster.GetMobIndex() == 573)
		F10::KillCount += 1;

	if (IMonster.GetMobIndex() == 384)
	{
		for (int i = 0; i < 8; i++)
		{
			Summon(0, EmokMap, IMonster.GetX(), IMonster.GetY(), 385, 1, 0, 0, 3600000, 0);
		}

		for (int i = 0; i < 8; i++)
		{
			Summon(0, EmokMap, IMonster.GetX(), IMonster.GetY(), 386, 1, 0, 0, 3600000, 0);
		}

		NailKill += 1;

		if (NailKill == 4)
		{
			NailKill = 0;
			Summon(0, EmokMap, 330904, 264756, 383, 1, 0, 0, 3600000, 0);
			CChar::WriteInSight((void*)Monster, 0xFF, "dsd", 247, "A Thousand Year Old E-Moogi has been appeared.", 2);
		}
	}

	if (IMonster.GetMobIndex() == 383)
	{
		Summon(0, EmokMap, 330904, 264756, 382, 1, 0, 0, 3600000, 0);
		CChar::WriteInSight((void*)Monster, 0xFF, "dsd", 247, "Ghost of Dragon has been appeared.", 2);
	}

	if (IMonster.GetMobIndex() == 445)
	{
		Battlefield::RedScore += 25;
		CChar::WriteInSight((void*)Monster, 0xFF, "dsd", 247, "Blue Tiger stone destroyed.", 3);
	}

	if (IMonster.GetMobIndex() == 448)
	{
		Battlefield::BlueScore += 25;
		CChar::WriteInSight((void*)Monster, 0xFF, "dsd", 247, "White Tiger stone destroyed.", 6);
	}

	if (IMonster.GetMobIndex() == 352)
	{
		Scenario::BlueScore += 5;
		Scenario::BlueTeamTowerCount += 1;
		CChar::WriteInSight((void*)Monster, 0xFF, "ddddd", 242, 22, 255, 255, 255);
	}

	if (IMonster.GetMobIndex() == 354)
	{
		Scenario::BlueScore += 2;
		Scenario::BlueTeamTowerCount += 1;
		CChar::WriteInSight((void*)Monster, 0xFF, "ddddd", 242, 19, 255, 255, 255);
	}

	if (IMonster.GetMobIndex() == 356)
	{
		Scenario::RedScore += 5;
		Scenario::RedTeamTowerCount += 1;
		CChar::WriteInSight((void*)Monster, 0xFF, "ddddd", 242, 33, 255, 255, 255);
	}

	if (IMonster.GetMobIndex() == 358)
	{
		Scenario::RedScore += 2;
		Scenario::RedTeamTowerCount += 1;
		CChar::WriteInSight((void*)Monster, 0xFF, "ddddd", 242, 30, 255, 255, 255);
	}

	if (Scenario::RedTeamTowerCount == 7)
	{
		Scenario::RedTeamSeal = 1;
		CChar::WriteInSight((void*)Monster, 0xFF, "ddddd", 242, 17, 255, 255, 255);
	}

	if (Scenario::BlueTeamTowerCount == 7)
	{
		Scenario::BlueTeamSeal = 1;
		CChar::WriteInSight((void*)Monster, 0xFF, "ddddd", 242, 28, 255, 255, 255);
	}

	return CMonsterMaguniMaster::Die(Monster,TankerID,Arg1,Arg2,Arg3);
}


int __fastcall SummonTick(void *Monster, void *edx)
{
	IChar IMonster(Monster);

	if (IMonster.IsOnline()) {
		if (IMonster.GetMobIndex() == BossIndex && !BossHunting::Time) {
			CPlayer::WriteInMap(IMonster.GetMap(), 0xFF, "dsd", 247, "Time to show what you all got in this hunting moment!", 1);
			BossHunting::Time = 3600;
			BossHunting::maxDmg = 0;
		}

	//	if (IMonster.GetMobIndex() == 573 && IMonster.GetCurHp() != IMonster.GetMaxHp())
	//		IMonster.IncreaseHp(100000);

		if (Raid::Active == true && IMonster.GetMobIndex() == Raid4 && Raid::Round == 4) {
			if (Raid::Time == 850) {
				CPlayer::WriteInMap(RaidMap, 0xFF, "dsd", 247, "Not so easy...", 1);
				for (int i = 0; i < RaidMiniAmount1; i++)
					Summon(0, RaidMap, IMonster.GetX(), IMonster.GetY(), RaidMini1, 1, 1, 0, 0, 0);
			}
		}

		if (Raid::Active == true && IMonster.GetMobIndex() == Raid5 && Raid::Round == 5) {
			if (Raid::Time == 1150) {
				CPlayer::WriteInMap(RaidMap, 0xFF, "dsd", 247, "Not so easy...", 1);
				for (int i = 0; i < RaidMiniAmount2; i++)
					Summon(0, RaidMap, IMonster.GetX(), IMonster.GetY(), RaidMini2, 1, 1, 0, 0, 0);
			}
		}

		if (Raid::Active == true && IMonster.GetMobIndex() == Raid9 && Raid::Round == 9) {
			if (Raid::Time == 1790)
				CPlayer::WriteInMap(RaidMap, 0xFF, "dsd", 247, "It's Tougher than I thought...", 1);
			if (Raid::Time == 1740) {
				CPlayer::WriteInMap(RaidMap, 0xFF, "dsd", 247, "Surprise!", 1);
				for (int i = 0; i < RaidMiniAmount4; i++)
					Summon(0, RaidMap, IMonster.GetX(), IMonster.GetY(), RaidMini4, 1, 1, 0, 0, 0);
			}
		}

		if (Raid::Active == true && IMonster.GetMobIndex() == Raid6 && Raid::Round == 6) {
			if (Raid::Time == 1360) {
				CPlayer::WriteInMap(RaidMap, 0xFF, "dsd", 247, "COME ON GUYS, DO SOMETHING!", 1);
				for (int i = 0; i < RaidMiniAmount3; i++)
					Summon(0, RaidMap, IMonster.GetX(), IMonster.GetY(), RaidMini3, 1, 1, 0, 0, 0);
			}
		}

		if (F10::Active == true && IMonster.GetMobIndex() == 702)
		{
			if (F10::KillCount < 3)
			{
				DWORD Check = (MonsterDisappear.findValue((int)Monster) - GetTickCount()) / 1000;

				if (Check == 3695)
					Undefined::MonsterPath(*(void **)((int)Monster + 320), (int)Monster, 0, -1, 0, 1);
				
				if (Check == 3691)
					CPlayer::WriteInMap(21, 0xFF, "dsd", 247, "I have a supernatural feeling that something invisible is trying to embody.", 1);

				if (Check == 3688)
					CPlayer::WriteInMap(21, 0xFF, "dsd", 247, "Finally here you come. I have waited so long... about 100 years...", 1);

				if (Check == 3684)
					CPlayer::WriteInMap(21, 0xFF, "dsd", 247, "You look very tired. I know the way that you had come here was not easy.", 1);

				if (Check == 3680)
					CPlayer::WriteInMap(21, 0xFF, "dsd", 247, "Then, I'd like to get you through the final wringer I will estimate.", 1);

				if (Check == 3676)
					CPlayer::WriteInMap(21, 0xFF, "dsd", 247, "Whatever you have a qualification and an ability to defeat energy of evil.", 1);

				if (Check == 3672)
					CPlayer::WriteInMap(21, 0xFF, "dsd", 247, "If you pass it, I will pave the way to the subject of energy of evil.", 1);

				if (Check == 3668)
					CPlayer::WriteInMap(21, 0xFF, "dsd", 247, "I hope you will pass it and annihilate the energy of evil which has been existed.", 1);

				if (Check == 3664)
					CPlayer::WriteInMap(21, 0xFF, "dsd", 247, "Since the first year of an era and thrown into confusion, so save the world finally.", 1);
				
				if (Check == 3660)
					IMonster.AddFxToTarget("davi_M573_72", 1, 0, 0);

				if (Check == 3659)
					CChar::WriteInSight(IMonster.Offset, 63, "bddbb", 258, IMonster.GetID(), IMonster.GetID(), 1, 1);

				if (Check == 3658)
					CChar::WriteInSight(IMonster.Offset, 63, "bddbb", 258, IMonster.GetID(), IMonster.GetID(), 1, 1);

				if (Check == 3657)
					CChar::WriteInSight(IMonster.Offset, 63, "bddbb", 258, IMonster.GetID(), IMonster.GetID(), 1, 1);

				if (Check == 3656)
					CChar::WriteInSight(IMonster.Offset, 63, "bddbb", 258, IMonster.GetID(), IMonster.GetID(), 1, 1);

				if (Check == 3655)
					CChar::WriteInSight(IMonster.Offset, 63, "bddbb", 258, IMonster.GetID(), IMonster.GetID(), 1, 1);

				if (Check == 3654)
					CChar::WriteInSight(IMonster.Offset, 63, "bddbb", 258, IMonster.GetID(), IMonster.GetID(), 1, 1);

				if (Check == 3653)
					CChar::WriteInSight(IMonster.Offset, 63, "bddbb", 256, IMonster.GetID(), IMonster.GetID(), 1, 1);
				
				if (Check >= 3653 && Check <= 3656 && (!F10::Cheios || !F10::Dunamic))
				{
					if (!F10::Cheios)
					{
						F10::Cheios = Summon(0, 21, 117248, 36843, 572, 1, 0, 16000, 3616000, 0);
						IChar Cheios((void*)F10::Cheios);

						if (Cheios.IsValid())
							Undefined::MonsterPath(*(void **)(F10::Cheios + 320), F10::Cheios, 0, -1, 0, 1);
					}

					if (!F10::Dunamic)
					{
						F10::Dunamic = Summon(0, 21, 117432, 36840, 566, 1, 0, 16000, 3616000, 0);
						IChar Dunamic((void*)F10::Dunamic);

						if (Dunamic.IsValid())
							Undefined::MonsterPath(*(void **)(F10::Dunamic + 320), F10::Dunamic, 0, -1, 0, 1);
					}
				}	
				
				if (Check == 3646)
					Undefined::MonsterPath(*(void **)((int)Monster + 320), (int)Monster, 0, 120, 0, 1);

				if (Check == 3644)
					Undefined::MonsterPath(*(void **)((int)Monster + 320), (int)Monster, 0, 120, 0, 1);

				if (Check == 3642)
					Undefined::MonsterPath(*(void **)((int)Monster + 320), (int)Monster, 0, 120, 0, 1);

				if (Check == 3640)
					Undefined::MonsterPath(*(void **)((int)Monster + 320), (int)Monster, 0, 120, 0, 1);

				if (Check == 3638)
					Undefined::MonsterPath(*(void **)((int)Monster + 320), (int)Monster, 0, 120, 0, 1);

				if (Check == 3635)
					Undefined::MonsterPath(*(void **)((int)Monster + 320), (int)Monster, 0, -1, 0, 1);
				
				if (Check == 3634)
				{
					for (int x = 0; x < 10; x++)
						Summon(0, 21, CTools::Rate(117028, 117028 + 550), CTools::Rate(36601, 36601 + 550), 564, 1, 1, 0, 0, 0);

					int Around = IMonster.GetObjectListAround(50);

					while (Around)
					{
						IChar Object((void*)CBaseList::Offset((void*)Around));

						if (Object.GetType() == 0 && Object.IsBuff(165))
						{
							Object.Buff(308, 3600, 0);
							Object.ScreenTime(3600);
						}

						Around = CBaseList::Pop((void*)Around);
					}

					F10::ShowTime = 3600;
				}

				

				if ((Check == 300 || Check == 600 || Check == 900 || Check == 1200 || Check == 1500 || Check == 1800 || Check == 2100 || Check == 2400 || Check == 3000 || Check == 3300) && F10::Active == true)
				{
					for (int x = 0; x < 8; x++)
						Summon(0, 21, CTools::Rate(117028, 117028 + 550), CTools::Rate(36601, 36601 + 550), 564, 1, 1, 0, 0, 0);
				}

				if (Check <= 33)
				{
					CPlayer::WriteInMap(21, 0xFF, "dsd", 247, "Company System failed...", 3);

					int Around = IMonster.GetObjectListAround(50);

					while (Around)
					{
						IChar Object((void*)CBaseList::Offset((void*)Around));

						if (Object.GetType() == 0 && Object.IsBuff(165))
							Object.CloseScreenTime();

						Around = CBaseList::Pop((void*)Around);
					}

					F10::CheiosSkillDelay = 0;
					F10::DunamicSkillDelay = 0;
					F10::Dunamic = 0;
					F10::Cheios = 0;
					F10::KillCount = 0;
					F10::RegisterAmount = 0;
					F10::Ilyer = 0;
					F10Registration.clear();
					F10::Active = false;
				}
			}
			else {
				int Size = 0;
				int Around = IMonster.GetObjectListAround(50);
				while (Around)
				{
					IChar Object((void*)CBaseList::Offset((void*)Around));
					if (Object.IsValid() && Object.GetType() == 0)
						Size++;
					Around = CBaseList::Pop((void*)Around);
				}

				int PlayersPicked = 0;
				std::string namePicked = "";
				int Randomize = CTools::Rate(0, Size);
				int x = 1;

				CPlayer::WriteInMap(21, 0xFF, "dsd", 247, "Thank you for saving the world...", 3);
				Around = IMonster.GetObjectListAround(50);

				while (Around)
				{
					IChar Object((void*)CBaseList::Offset((void*)Around));

					if (Object.GetType() == 0 && Object.IsBuff(165)) {
						if ((!F10Limit || (F10Limit && !isRewarded(Object)))) {

							if (F10EXPs.count(Object.GetLevel())) {
								F10EXP f10Exp = F10EXPs.find(Object.GetLevel())->second;

								if (f10Exp.Gap) {
									for(int i=0;i<f10Exp.Mult;i++)
										(*(int(__cdecl **)(int, signed int, signed int, unsigned __int64, unsigned __int64))(*(DWORD *)Object.GetOffset() + 88))((int)Object.GetOffset(), 25, 1, (unsigned __int64)f10Exp.Exp, HIDWORD(f10Exp.Exp));
								}
								else
								{
									for (int i = 0; i<f10Exp.Mult; i++)
										CPlayer::UpdateProperty((int)Object.GetOffset(), 25, 1, f10Exp.Exp);
								}

								Object.systemReward(f10Exp.RID);
							}
							else {
								if (Object.GetLevel() >= 1 && Object.GetLevel() <= 70)
									(*(int(__cdecl **)(int, signed int, signed int, unsigned __int64, unsigned __int64))(*(DWORD *)Object.GetOffset() + 88))((int)Object.GetOffset(), 25, 1, (unsigned __int64)F10Exp1, HIDWORD(F10Exp1));
								if (Object.GetLevel() >= 71 && Object.GetLevel() < 75)
									(*(int(__cdecl **)(int, signed int, signed int, unsigned __int64, unsigned __int64))(*(DWORD *)Object.GetOffset() + 88))((int)Object.GetOffset(), 25, 1, (unsigned __int64)F10Exp2, HIDWORD(F10Exp2));
								if (Object.GetLevel() >= 75 && Object.GetLevel() < 80)
									(*(int(__cdecl **)(int, signed int, signed int, unsigned __int64, unsigned __int64))(*(DWORD *)Object.GetOffset() + 88))((int)Object.GetOffset(), 25, 1, (unsigned __int64)F10Exp3, HIDWORD(F10Exp3));
								if (Object.GetLevel() >= 80 && Object.GetLevel() < 85) {
									for (int i = 0; i < F10Multiply; i++)
										CPlayer::UpdateProperty((int)Object.GetOffset(), 25, 1, F10Exp4);
								}
								if (Object.GetLevel() >= 85 && Object.GetLevel() < 90) {
									for (int i = 0; i < F10Multiply; i++)
										CPlayer::UpdateProperty((int)Object.GetOffset(), 25, 1, F10Exp5);
								}
								if (Object.GetLevel() >= 90 && Object.GetLevel() < 95) {
									for (int i = 0; i < F10Multiply; i++)
										CPlayer::UpdateProperty((int)Object.GetOffset(), 25, 1, F10Exp6);
								}
								if (Object.GetLevel() >= 95 && Object.GetLevel() <= 100) {
									for (int i = 0; i < F10Multiply; i++)
										CPlayer::UpdateProperty((int)Object.GetOffset(), 25, 1, F10Exp7);
								}
								else if (Object.GetLevel() > 100) {
									for (int i = 0; i < F10Multiply; i++)
										CPlayer::UpdateProperty((int)Object.GetOffset(), 25, 1, F10Exp8);
								}
							}

							if (!F10Items.empty() && PlayersPicked < F10Chance && x >= Randomize) {

								int Chance = CTools::Rate(1, 1000);
								int Index = 0;
								int Value = 0;
								for (int i = 0; i < F10Items.size(); i++) {
									ChanceItem f = F10Items[i];
									if ((f.Chance * 10) >= Chance) {
										Index = f.Index;
										Value = f.Amount;
										break;
									}
								}
								if (!Index) {
									Index = F10Items[F10Items.size() - 1].Index;
									Value = F10Items[F10Items.size() - 1].Amount;
								}
								Object.InsertItem(Index, 0, Value);
								namePicked = (std::string)Object.GetName();
								if (!namePicked.empty()) {
									std::string notice = namePicked + " has been randomly picked to receive F10 Reward";
									CPlayer::WriteAll(0xFF, "dsd", 247, notice.c_str(), 2);
								}
								PlayersPicked++;
							}

							if (F10BuffEnable && F10BuffSys)
							{
								Object.Buff(BuffNames::F10Buff, 1800, 1);
								Object.SetBuffIcon(1800000, 0, F10BuffSys, F10BuffSys);
							}

						}

						if (F10Limit)
							rewardLimit(Object);

						Object.CloseScreenTime();
						Object.CancelBuff(165);
					}

					Around = CBaseList::Pop((void*)Around);
				}

				RewardLimit.clear();
				F10::CheiosSkillDelay = 0;
				F10::DunamicSkillDelay = 0;
				F10::Dunamic = 0;
				F10::Cheios = 0;
				F10::KillCount = 0;
				F10::Ilyer = 0;
				F10::RegisterAmount = 0;
				F10Registration.clear();
				F10::Active = false;
			}
		}

		if (IMonster.GetMobIndex() >= 352 && IMonster.GetMobIndex() <= 360)
		{
			if (IMonster.GetCurHp() <= (CChar::GetMaxHp((int)IMonster.GetOffset()) / 100 * 25))
				CChar::WriteInSight(IMonster.GetOffset(), 46, "dI", IMonster.GetID(), __int64(0x00100000) << 32);
			else if (IMonster.GetCurHp() <= (CChar::GetMaxHp((int)IMonster.GetOffset()) / 100 * 50))
				CChar::WriteInSight(IMonster.GetOffset(), 46, "dI", IMonster.GetID(), __int64(0x00080000) << 32);
			else
				CChar::WriteInSight(IMonster.GetOffset(), 46, "dI", IMonster.GetID(), __int64(0));
		}

		if (IMonster.GetMobIndex() == 382 && (GetTickCount() / 1000) % 300 == 0)
		{
			for (int i = 0; i < 6; i++)
			{
				Summon(0, EmokMap, IMonster.GetX(), IMonster.GetY(), 385, 1, 1, 0, 0, 0);
			}

			for (int i = 0; i < 6; i++)
			{
				Summon(0, EmokMap, IMonster.GetX(), IMonster.GetY(), 386, 1, 1, 0, 0, 0);
			}
		}

		int MDisappear = MonsterDisappear.findExists((int)Monster);

		if (MDisappear)
		{
			if (GetTickCount() >= MDisappear) {
				IMonster.MobDelete();
				return CMonsterMaguniMaster::Tick(Monster);
			}

			eventMapMonster evMonster = EventMapsMobsOn.findExists((int)Monster);
			if (evMonster.Quest && !EventMapsOn.count(evMonster.Quest)) {
				IMonster.MobDelete();
				return CMonsterMaguniMaster::Tick(Monster);
			}
		}

		if (IMonster.GetMobIndex() == 566 && IMonster.GetMobTanker() && GetTickCount() >= F10::DunamicSkillDelay)
		{
			if (F10::DunamicSkillDelay && GetTickCount() >= F10::DunamicSkillDelay)
			{
				F10::DunamicSkillDelay = 0;

				if (F10::DunamicSkill == 1)
				{
					F10::DunamicSkill = 0;
					int Around = IMonster.GetObjectListAround(3);

					while (Around)
					{
						IChar Object((void*)CBaseList::Offset((void*)Around));

						if (Object.GetType() == 0)
							IMonster.OktayDamageStorm(Object, CTools::Rate(1000, 1250));

						Around = CBaseList::Pop((void*)Around);
					}
				}

				if (F10::DunamicSkill == 2)
				{
					F10::DunamicSkill = 0;

					int Around = IMonster.GetObjectListAround(3);

					while (Around)
					{
						IChar Object((void*)CBaseList::Offset((void*)Around));

						if (Object.GetType() == 0 && !Object.IsBuff(371))
						{
							Object.SetBuffIcon(10000, 0, 2038, 224);
							Object.Buff(370, 10, 0);
							Object.Buff(371, 3600, 0);
						}

						Around = CBaseList::Pop((void*)Around);
					}
				}
			}

			if ((GetTickCount() / 1000) % 45 == 0)
			{
				F10::DunamicSkill = 2;
				F10::DunamicSkillDelay = GetTickCount() + 1000;
				CChar::WriteInSight(IMonster.Offset, 61, "dbbd", IMonster.GetID(), 5, 19, IMonster.GetID());
			}

			if ((GetTickCount() / 1000) % 75 == 0)
			{
				F10::DunamicSkill = 2;
				F10::DunamicSkillDelay = GetTickCount() + 1000;
				CChar::WriteInSight(IMonster.Offset, 61, "dbbd", IMonster.GetID(), 5, 27, IMonster.GetID());
			}
		}

		if (IMonster.GetMobIndex() == 572 && IMonster.GetMobTanker() && GetTickCount() >= F10::CheiosSkillDelay)
		{
			if (F10::CheiosSkillDelay && GetTickCount() >= F10::CheiosSkillDelay)
			{
				F10::CheiosSkillDelay = 0;

				if (F10::CheiosSkill == 1)
				{
					CChar::WriteInSight(IMonster.Offset, 61, "dbbd", IMonster.GetID(), 5, 19, IMonster.GetID());
					F10::CheiosSkill = 0;
					int Around = IMonster.GetObjectListAround(3);

					while (Around)
					{
						IChar Object((void*)CBaseList::Offset((void*)Around));

						if (Object.GetType() == 0)
							IMonster.OktayDamageStorm(Object, CTools::Rate(1000, 1250));

						Around = CBaseList::Pop((void*)Around);
					}
				}

				if (F10::CheiosSkill == 2)
				{
					CChar::WriteInSight(IMonster.Offset, 61, "dbbd", IMonster.GetID(), 5, 20, IMonster.GetID());
					F10::CheiosSkill = 0;

					int Around = IMonster.GetObjectListAround(3);

					while (Around)
					{
						IChar Object((void*)CBaseList::Offset((void*)Around));

						if (Object.GetType() == 0 && !Object.IsBuff(369))
						{
							if (Object.GetEva() >= 10)
							{
								Object.SetBuffIcon(-2, -1, 2042, 226);
								Object.RemoveEva(10);
								Object.Buff(40, 10, -50);
								Object.Buff(368, 10, 0);
								Object.Buff(369, 3600, 0);
							}
						}

						Around = CBaseList::Pop((void*)Around);
					}
				}
			}

			if ((GetTickCount() / 1000) % 45 == 0)
			{
				F10::CheiosSkill = 1;
				F10::CheiosSkillDelay = GetTickCount() + 2000;
				CChar::WriteInSight(IMonster.Offset, 61, "dbbd", IMonster.GetID(), 5, 26, IMonster.GetID());
			}

			if ((GetTickCount() / 1000) % 75 == 0)
			{
				F10::CheiosSkill = 2;
				F10::CheiosSkillDelay = GetTickCount() + 1000;
				CChar::WriteInSight(IMonster.Offset, 61, "dbbd", IMonster.GetID(), 5, 28, IMonster.GetID());
			}
		}

		if (F10::Active == false && (IMonster.GetMobIndex() == 564 || IMonster.GetMobIndex() == 566 || IMonster.GetMobIndex() == 572 || IMonster.GetMobIndex() == 573 || IMonster.GetMobIndex() == 702))
		{
			IMonster.MobDelete();
			return CMonsterMaguniMaster::Tick(Monster);
		}

		if (CaptureFlag::Active == true && CaptureFlag::PlayerID != 0 && (IMonster.GetMobIndex() == CaptureMonster))
		{
			IMonster.MobDelete();
			return CMonsterMaguniMaster::Tick(Monster);
		}

		if (IMonster.GetMobIndex() == BossIndex && BossHunting::Time == 0) {
			IMonster.MobDelete();
			CPlayer::WriteAll(0xFF, "dsd", 247, "There will not be a " + thisServerName + " Hunter since Time Expired, Better luck next time!", 2);
			return CMonsterMaguniMaster::Tick(Monster);
		}

		if (Battlefield::Active == false && (IMonster.GetMobIndex() == 445 || IMonster.GetMobIndex() == 448))
		{
			IMonster.MobDelete();
			return CMonsterMaguniMaster::Tick(Monster);
		}

		if (Scenario::Active == false && (IMonster.GetMobIndex() >= 352 && IMonster.GetMobIndex() <= 360))
		{
			IMonster.MobDelete();
			return CMonsterMaguniMaster::Tick(Monster);
		}

		if (Raid::Active == false && IMonster.GetMap() == RaidMap && (IMonster.GetMobIndex() == Raid1 || IMonster.GetMobIndex() == Raid2 || IMonster.GetMobIndex() == Raid3 || IMonster.GetMobIndex() == Raid4 || IMonster.GetMobIndex() == Raid5 || IMonster.GetMobIndex() == Raid6 || IMonster.GetMobIndex() == Raid7 || IMonster.GetMobIndex() == Raid8 || IMonster.GetMobIndex() == Raid9))
		{
			IMonster.MobDelete();
			return CMonsterMaguniMaster::Tick(Monster);
		}

		if (Hell::Active == false && IMonster.GetMap() == HellMap)
		{
			IMonster.MobDelete();
			return CMonsterMaguniMaster::Tick(Monster);
		}

		if (CaptureFlag::Active == false && (IMonster.GetMobIndex() == CPMob || IMonster.GetMobIndex() == CPGate || IMonster.GetMobIndex() == CaptureMonster)) {
			IMonster.MobDelete();
			return CMonsterMaguniMaster::Tick(Monster);
		}

		if (CaptureFlag::Active && CaptureFlag::CurrentCapturers  && IMonster.GetMobIndex() == CPMob && IMonster.GetMap() == CaptureMap) {
			int Opposite = (CaptureFlag::CurrentCapturers == BuffNames::CPRed) ? BuffNames::CPBlue : BuffNames::CPRed;

			int Tanker = IMonster.GetMobTanker();
			IChar ITanker((void*)Tanker);
			if (((Tanker && !ITanker.IsBuff(Opposite)) || !Tanker) && IMonster.GetCurHp() > 0) {
				IMonster.SetMobTarget(0);
				int Around = IMonster.GetObjectListAround(7);
				bool F = false;
				while (Around)
				{
					if (!F) {
						IChar Object((void*)CBaseList::Offset((void*)Around));

						if (Object.IsValid() && Object.GetType() == 0 && Object.IsBuff(Opposite)) {
							IMonster.SetMobTarget((int)Object.GetOffset());
							F = true;
						}
					}

					Around = CBaseList::Pop((void*)Around);
				}
			}
		}

		if (!Maut::Active && IMonster.GetMap() == MautMap)
		{
			IMonster.MobDelete();
			return CMonsterMaguniMaster::Tick(Monster);
		}

		if (!BossEXP::Active && IMonster.GetMap() == BossEXPMap)
		{
			IMonster.MobDelete();
			return CMonsterMaguniMaster::Tick(Monster);
		}

		if (*(DWORD *)((int)Monster + 144) == 54023 && !IMonster.IsMobMoving()) {
			IMonster.MobDelete();
			return CMonsterMaguniMaster::Tick(Monster);
		}

		if (IMonster.IsBuff(BuffNames::SummonAI))
		{
			IChar IPlayer((void*)IMonster.GetBuffValue(BuffNames::SummonAI));

			if (!IPlayer.IsValid())
			{
				IMonster.MobDelete();
				return CMonsterMaguniMaster::Tick(Monster);
			}

			/*if (IPlayer.IsOnline()  && IMonster.GetMobTanker() && IMonster.GetMobTanker() != (int)IPlayer.GetOffset())
			{
			if (!IPlayer.GetPartyID())
			{
			IMonster.MobDelete();
			return CMonsterMaguniMaster::Tick(Monster);
			} else {
			IChar Tanker((void*)IMonster.GetMobTanker());

			if (Tanker.GetPartyID() != IPlayer.GetPartyID())
			{
			IMonster.MobDelete();
			return CMonsterMaguniMaster::Tick(Monster);
			}
			}
			}*/

			if (IPlayer.IsOnline() && CChar::GetRange((int)IPlayer.GetOffset() + 332, (int)IMonster.GetOffset() + 332) >= 400)
			{
				IMonster.MobDelete();
				return CMonsterMaguniMaster::Tick(Monster);
			}

			if (IPlayer.IsValid() && IMonster.GetCurHp() > 0 && !IMonster.GetMobTanker())
			{
				int Target = CMonsterReal::ScanSight((int)IMonster.GetOffset());
				if (Target) {
					IChar xPlayer((void*)Target);

					if (xPlayer.IsValid() && xPlayer.GetOffset() == IPlayer.GetOffset()) {
						*(DWORD *)((int)IMonster.GetOffset() + 656) = 0;
						(*(void(__thiscall **)(DWORD, DWORD))(*(DWORD *)(int)IMonster.GetOffset() + 188))((int)IMonster.GetOffset(), Target);
					}
					else
						CSkill::ObjectRelease((void*)Target, (LONG)(Target + 356));
				}
			}
		}
	}

	return CMonsterMaguniMaster::Tick(Monster);
}