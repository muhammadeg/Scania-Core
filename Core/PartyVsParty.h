int portArena = 0;
int PTRegisterSize = 0;

int PartyArenas[][9] = {
	{ 219480,219480,217083,219441,217316,214799,219551,217092,214732 },
	{ 280824,280824,280811,283290,283278,283304,285656,285677,285651 }
};

int PartyPortBack[][9] = {
	{ 219584,219584,217182,219495,217276,214775,219620,217177,214744 },
	{ 281404,281404,281508,282725,282740,282724,285023,285014,286230 }
};

void RemoveParty(int PID) {
	vector< PartyReg >::iterator it = PartyRegistrations.begin();
	while (it != PartyRegistrations.end()) {

		if (it->PID == PID) {
			PTRegisterSize--;
			it = PartyRegistrations.erase(it);
			break;
		}
		else
			++it;
	}
}

void RegisterParticipants(int Type, int PTSize) {
	for (auto x = PartyRegistrations.begin(); x != PartyRegistrations.end(); x++)
	{
		if (x->PartySize == PTSize) {
			TOURNAMENT_PARTY pt;
			ZeroMemory(&pt, sizeof TOURNAMENT_PARTY);

			pt = tagTournamentParty();

			for (int i = 0; i < PTSize; i++)
				strcpy(pt.szName[i], x->Names[i]);

			pt.nWinCnt = 0;
			pt.bAbsence = false;
			pt.bNULL = false;
			pt.nPosition = 0;
			duelShowLock.Enter();
			AllFights[Type].push_back(pt);
			duelShowLock.Leave();
		}
	}
}

int GetPTSize(int PartyID) {
	int Size = 0;
	int Party = CParty::FindParty(PartyID);
	if (Party) {
		Size = CParty::GetSize((void*)Party);
		CIOObject::Release((void*)Party);
	}
	return Size;
}

bool CheckTournamentSize(int Arena, int Min) {
	int Size = 0;
	for (auto x = PartyRegistrations.begin(); x != PartyRegistrations.end(); x++)
	{
		if (x->PVPArena == Arena)
			Size++;
		if (Size > Min)
			return false;
	}
	return true;
}

bool isPartyTournamentFinished(int Arena) {
	return CheckTournamentSize(Arena, 0);
}

void SendPartyToArena(int PartyID, int Arena, int Type) {
	int Party = CParty::FindParty(PartyID);
	if (Party) {
		int RatesX = CTools::Rate(-50 + (100 * Type), 50 * (Type + 1));
		int RatesY = CTools::Rate(-50 + (100 * Type), 50 * (Type + 1));
		for (int i = CParty::GetPlayerList((void*)Party); i; i = CBaseList::Pop((void *)i))
		{
			int Members = *(DWORD*)((void*)i);
			IChar Member((void*)*(DWORD*)((void*)i));

			if (Member.IsValid() && Member.IsPVPValid())
			{
				Member.Teleport(0, PartyArenas[0][Arena] + RatesX + CTools::Rate(32 * Type, 32 * (Type + 1)) , PartyArenas[1][Arena] + RatesY + CTools::Rate(32 * Type, 32 * (Type + 1)));
				Member.UpdateBuff(BuffNames::PTVsPTRed + Type, BuffNames::BuffTime, Arena);
			}
		}
		CIOObject::Release((void*)Party);
	}
}

bool IsPartyAlive(int PTID, int Type) {
	int Party = CParty::FindParty(PTID);
	bool result = false;
	if (Party) {
		for (int i = CParty::GetPlayerList((void*)Party); i; i = CBaseList::Pop((void *)i))
		{
			IChar Member((void*)*(DWORD*)((void*)i));

			if (Member.IsBuff(BuffNames::PTVsPTRed + Type))
				result = true;
		}
		CIOObject::Release((void*)Party);
	}
	return result;
}

void PortPartyAway(int PartyID, int Arena) {
	int Party = CParty::FindParty(PartyID);
	if (Party) {
		for (int i = CParty::GetPlayerList((void*)Party); i; i = CBaseList::Pop((void *)i))
		{
			int Members = *(DWORD*)((void*)i);
			IChar Member((void*)*(DWORD*)((void*)i));

			Member.CancelBuff(BuffNames::PTVsPTBlue);
			Member.CancelBuff(BuffNames::PTVsPTRed);
			Member.RemoveSetBlue();
			Member.RemoveSetRed();
			Member.Teleport(0, PartyPortBack[0][Arena], PartyPortBack[1][Arena]);
			Member.CloseScenario3_3Score();
		}
		CIOObject::Release((void*)Party);
	}
}

std::string GetPartyLeaderName(int PartyID) {
	std::string Name = "";
	int Party = CParty::FindParty(PartyID);
	if (Party) {
		int LeaderP = *(DWORD *)(Party + 20);
		IChar ILeader((void*)LeaderP);
		Name = (std::string)ILeader.GetName();
		CIOObject::Release((void*)Party);
	}
	return Name;
}

void IncreaseWins(int Type, int PartyID) {
	int PTSize = Type == -4 ? 6 : 3;
	std::string LeaderName = GetPartyLeaderName(PartyID);
	duelShowLock.Enter();
	if (AllFights.count(Type)) {
		std::vector<TOURNAMENT_PARTY> Vec = AllFights.find(Type)->second;
		int Size = Vec.size();
		for (int i = 0; i < Size; i++) {
			TOURNAMENT_PARTY pt = Vec[i];
			for (int j = 0; j < PTSize; j++) {
				std::string Name(pt.szName[j]);
				if (Name == " " + LeaderName) {
					AllFights[Type][i].nWinCnt++;
					break;
				}
			}
		}
	}
	duelShowLock.Leave();
}

void CleanBattle(int Arena) {
	PartyBattle pBattle = CurPartys.find(Arena)->second;
	pBattle.PTID1 = 0;
	pBattle.PTID2 = 0;
	pBattle.Cooldown = GetTickCount() + 10000;
	pBattle.FightAvailable = true;
	CurPartys[Arena] = pBattle;
}

void PartyDraw(int PTID1, int PTID2, int Arena) {
	PortPartyAway(PTID1,Arena);
	PortPartyAway(PTID2,Arena);
	bool Finished = isPartyTournamentFinished(Arena);

	if (Finished) {
		CPlayer::WriteAll(0xFF, "dsd", 247, "The Party Vs Party tournament has ended in a draw", 2);
		CurPartys.erase(Arena);
	}
	else {
		std::string notice = "Battle between "+GetPartyLeaderName(PTID1) + "'s Party and " +GetPartyLeaderName(PTID2)+"'s party has ended in a draw.";
		CPlayer::WriteAll(0xFF, "dsd", 247, notice.c_str(), 2);
		CleanBattle(Arena);
	}
}

void PartyWon(int WinnerParty, int LoserParty, int Arena, int Reward, int Type) {
	bool Finished = isPartyTournamentFinished(Arena);

	PortPartyAway(WinnerParty, Arena);
	PortPartyAway(LoserParty, Arena);

	if (!WinnerParty || !LoserParty)
		return;

	IncreaseWins(Type == 6 ? -4 : -7, WinnerParty);

	//PartyRegistrations.erase(LoserParty);

	int Party = CParty::FindParty(WinnerParty);

	PartyReward Rewards = PartyRewards.count(Reward) ? PartyRewards.find(Reward)->second : PartyReward();
	if (Party) {
		for (int i = CParty::GetPlayerList((void*)Party); i; i = CBaseList::Pop((void *)i))
		{
			int Members = *(DWORD*)((void*)i);
			IChar Member((void*)*(DWORD*)((void*)i));

			if (Member.IsOnline()) {
				if (Finished) {
					if (!Rewards.winnerIndexes.empty()) {
						for (int i = 0; i < Rewards.winnerIndexes.size(); i++)
							Member.InsertItem(String2Int(Rewards.winnerIndexes[i]), 0, String2Int(Rewards.winnerAmounts[i]));
					}
					if(Rewards.WinnerHonor || Rewards.WinnerReward)
						Member.SetHonor(Rewards.WinnerHonor, Rewards.WinnerReward, 0, 0, 0, 0, 0, 0, 0, 0);
					Member.SystemMessage("You have won the Party Vs Party Tournament.", TEXTCOLOR_GREEN);
				}
				else {
					if (!Rewards.battleIndexes.empty()) {
						for (int i = 0; i < Rewards.battleIndexes.size(); i++)
							Member.InsertItem(String2Int(Rewards.battleIndexes[i]), 0, String2Int(Rewards.battleAmounts[i]));
					}
					if (Rewards.BattleHonor || Rewards.BattleReward)
						Member.SetHonor(Rewards.BattleHonor, Rewards.BattleReward, 0, 0, 0, 0, 0, 0, 0, 0);
					Member.SystemMessage("You have won the battle.", TEXTCOLOR_GREEN);
				}
				CPlayer::Write(Member.GetOffset(), 0xFF, "ddddd", 242, 52, 255, 255, 255);
			}
		}
		CIOObject::Release((void*)Party);
	}

	if (!Finished) {
		std::string notice = "The party battle has been won by " + GetPartyLeaderName(WinnerParty) + "'s Party.";
		CPlayer::WriteAll(0xFF, "dsd", 247, notice.c_str(), 2);
		CleanBattle(Arena);
		PartyReg pt = PartyReg();
		pt.PID = WinnerParty;
		pt.PVPArena = Arena;
		pt.RewardID = Reward;
		pt.PartySize = Type;
		PartyRegistrations.push_back(pt);
	}
	else {
		std::string notice = GetPartyLeaderName(WinnerParty) + "'s Party has won the Party vs Party tournament.";
		CPlayer::WriteAll(0xFF, "dsd", 247, notice.c_str(), 2);
		CurPartys.erase(Arena);
	}
}

void managePartyRegistration(PartyReg reg) {
	std::string Size = Int2String(reg.PartySize);

	if (!reg.Type) {
		CurPartys.erase(reg.PVPArena);
		PTEnabled[reg.Quest] = reg;
		std::string notice = Size + " Vs " + Size + " Registration has been started for Level " + Int2String(reg.MinLevel) + " To " + Int2String(reg.MaxLevel) + " In PVP Arena " + Int2String(reg.PVPArena) + ".";
		CPlayer::WriteAll(0xFF, "dsd", 247, notice.c_str(), 2);
	}
	else if (reg.Type == 1) {
		PTEnabled[reg.Quest].Type = 3;
		std::string notice = Size + " Vs " + Size + " Registration has ended for Level " + Int2String(reg.MinLevel) + " To " + Int2String(reg.MaxLevel) + " In PVP Arena " + Int2String(reg.PVPArena) + ".";
		CPlayer::WriteAll(0xFF, "dsd", 247, notice.c_str(), 2);
	}
	else if (reg.Type == 2) {
		if (CheckTournamentSize(reg.PVPArena, 1)) {
			std::string notice = Size + " Vs " + Size + " for Level " + Int2String(reg.MinLevel) + " To " + Int2String(reg.MaxLevel) + " did not start due to low amount of registered players.";
			CPlayer::WriteAll(0xFF, "dsd", 247, notice.c_str(), 2);
		}
		else {
			if (reg.PartySize == 3)
				RegisterParticipants(-7, 3);
			else if (reg.PartySize == 6)
				RegisterParticipants(-4, 6);
			PTEnabled[reg.Quest].Type = 3;
			std::string notice = Size + " Vs " + Size + " for Level " + Int2String(reg.MinLevel) + " To " + Int2String(reg.MaxLevel) + " has started in PVP Arena " + Int2String(reg.PVPArena) + ".";
			CPlayer::WriteAll(0xFF, "dsd", 247, notice.c_str(), 2);
			PartyBattle pBattle = PartyBattle();
			pBattle.Reward = reg.RewardID;
			pBattle.Cooldown = GetTickCount() + 10000;
			pBattle.PartySize = reg.PartySize;
			CurPartys[reg.PVPArena] = pBattle;
		}
	}
}

void PartyVsPartyOnTick() {
	int PID = 0;
	int PID2 = 0;
	int Arena = 0;
	int PTSize = 0;
	int Winner = 0;
	int Loser = 0;
	int Type = 0;
	int Reward = 0;

	std::map<int, PartyBattle> CurPartysClone = CurPartys;

	for (auto x = CurPartysClone.begin(); x != CurPartysClone.end(); x++)
	{
		if (x->second.Cooldown > GetTickCount()) {
			std::string PTSizeString = Int2String(x->second.PartySize);
			std::string notice = "The next " + PTSizeString + " vs " + PTSizeString + " Battle in PVP Arena " + Int2String(x->first) + " will start in " + Int2String((x->second.Cooldown - GetTickCount()) / 1000) + " seconds...";
			CPlayer::WriteAll(0xFF, "dsd", 247, notice.c_str(), 2);
			return;
		}
		if (x->second.PTID1 && x->second.PTID2) {
			if (x->second.Time && GetTickCount() > x->second.Time) {
				if (x->second.BlueScore > x->second.RedScore)
					PartyWon(x->second.PTID2, x->second.PTID1, x->first, x->second.Reward, x->second.PartySize);

				else if (x->second.RedScore > x->second.BlueScore)
					PartyWon(x->second.PTID1, x->second.PTID2, x->first, x->second.Reward, x->second.PartySize);

				else
					PartyDraw(x->second.PTID2, x->second.PTID1, x->first);

				return;
			}

			if (!IsPartyAlive(x->second.PTID1, 0) || (GetPTSize(x->second.PTID1) != x->second.PartySize && GetPTSize(x->second.PTID2) == x->second.PartySize))
			{
				PartyWon(x->second.PTID2, x->second.PTID1, x->first, x->second.Reward, x->second.PartySize);
				return;
			}

			else if (!IsPartyAlive(x->second.PTID2, 1) || (GetPTSize(x->second.PTID2) != x->second.PartySize && GetPTSize(x->second.PTID1) == x->second.PartySize))
			{
				PartyWon(x->second.PTID1, x->second.PTID2, x->first, x->second.Reward, x->second.PartySize);
				return;
			}

			continue;
		}

		if (PID && PID2)
			break;

		if (x->second.FightAvailable) {
			if (!Arena)
				Arena = x->first;

			for (auto y = PartyRegistrations.begin(); y != PartyRegistrations.end(); y++)
			{
				if (y->PVPArena == Arena) {
					PTSize = y->PartySize;
					if (!PID)
						PID = y->PID;
					else if (!PID2) {
						PID2 = y->PID;
						break;
					}
				}
			}
		}
	}

	if (!PTSize)
		return;

	if (PID && PID2 && GetPTSize(PID) == PTSize && GetPTSize(PID2) == PTSize) {
		RemoveParty(PID);
		RemoveParty(PID2);
		PartyBattle pBattle = CurPartys.find(Arena)->second;
		pBattle.PartySize = PTSize;
		pBattle.FightAvailable = false;
		pBattle.PTID1 = PID;
		pBattle.PTID2 = PID2;
		pBattle.Time = GetTickCount() + 300000;
		pBattle.RedScore = 0;
		pBattle.BlueScore = 0;
		pBattle.Cooldown = 0;
		SendPartyToArena(PID, Arena, 0);
		SendPartyToArena(PID2, Arena, 1);
		std::string notice = "The battle between " + GetPartyLeaderName(PID) + "'s Party and " + GetPartyLeaderName(PID2) + "'s Party has started.";
		CPlayer::WriteAll(0xFF, "dsd", 247, notice.c_str(), 2);
		CurPartys[Arena] = pBattle;
	}
	else {
		if (PID && PID2) {
			RemoveParty(PID);
			RemoveParty(PID2);
			PartyBattle pBattle = CurPartys.find(Arena)->second;
			if (GetPTSize(PID) != PTSize && GetPTSize(PID2) == PTSize)
				PartyWon(PID2, PID, Arena, pBattle.Reward, pBattle.PartySize);
			else if (GetPTSize(PID2) != PTSize && GetPTSize(PID) == PTSize)
				PartyWon(PID, PID2, Arena, pBattle.Reward, pBattle.PartySize);
			else {
				if (isPartyTournamentFinished(Arena)) {
					CPlayer::WriteAll(0xFF, "dsd", 247, "The Party vs Party tournament has ended as the last two finalist parties were unavailable.", 2);
					CurPartys.erase(Arena);
				}
			}		
		}
	}
}