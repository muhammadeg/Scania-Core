int COKGroup = 0;

int WorldCupX[8] = { 219480,217083,219441,217316,214799,219551,217092,214732 };
int WorldCupY[8] = { 280824,280811,283290,283278,283304,285656,285677,285651 };

bool compareTeamByLength(const Team &a, const Team &b)
{
	if (CupRegistration[a.PID].team.Points == CupRegistration[b.PID].team.Points)
		return WCDamage[a.PID] > WCDamage[b.PID];

	return CupRegistration[a.PID].team.Points > CupRegistration[b.PID].team.Points;
}

void ShowWCGroup(IChar IPlayer, int Group) {
	if (CupOfKal.count(Group) && !CupOfKal.find(Group)->second.Groups.empty()) {
		CPlayer::Write(IPlayer.GetOffset(), 0xFE, "ds", 213, "   \n\n\n=====================GROUP " + Int2String(Group) + "=====================\n");
		std::sort(CupOfKal.find(Group)->second.Groups.begin(), CupOfKal.find(Group)->second.Groups.end(), compareTeamByLength);
		for (int i = 0; i < CupOfKal.find(Group)->second.Groups.size(); i++) {
			Team t = CupOfKal.find(Group)->second.Groups[i];
			int dmg = 0;
			if (WCDamage.count(t.PID))
				dmg = WCDamage.find(t.PID)->second;

			std::string text = "   " + t.Name + "                                     " + Int2String(dmg) + " Dmg                                    " + Int2String(CupRegistration.find(t.PID)->second.team.Points) + " Pts";
			CPlayer::Write(IPlayer.GetOffset(), 0xFE, "ds", 213, text.c_str());
		}
	}
}

void StartWorldCup() {
	if (!WorldCup::Active) {
		for (int n = 1; n <= 8; n++) {
			if (CupOfKal.find(n)->second.Groups.size() == 4) {
				srand(time(0));
				std::random_shuffle(CupOfKal.find(n)->second.Groups.begin(), CupOfKal.find(n)->second.Groups.end());

				int coordType = n;

				if (n > 4)
					coordType = n - 4;

				coordType = coordType * 2;

				Fight FirstFight1 = Fight(CupOfKal.find(n)->second.Groups[0].PID, CupOfKal.find(n)->second.Groups[2].PID, WorldCupX[coordType - 2], WorldCupY[coordType - 2], 0, 2);
				Fight FirstFight2 = Fight(CupOfKal.find(n)->second.Groups[1].PID, CupOfKal.find(n)->second.Groups[3].PID, WorldCupX[coordType - 1], WorldCupY[coordType - 1], 1, 3);

				FirstFight[n].FightList.push_back(FirstFight1);
				FirstFight[n].FightList.push_back(FirstFight2);

				Fight SecondFight1 = Fight(CupOfKal.find(n)->second.Groups[0].PID, CupOfKal.find(n)->second.Groups[1].PID, WorldCupX[coordType - 2], WorldCupY[coordType - 2], 0, 1);
				Fight SecondFight2 = Fight(CupOfKal.find(n)->second.Groups[2].PID, CupOfKal.find(n)->second.Groups[3].PID, WorldCupX[coordType - 1], WorldCupY[coordType - 1], 2, 3);

				SecondFight[n].FightList.push_back(SecondFight1);
				SecondFight[n].FightList.push_back(SecondFight2);

				Fight ThirdFight1 = Fight(CupOfKal.find(n)->second.Groups[3].PID, CupOfKal.find(n)->second.Groups[0].PID, WorldCupX[coordType - 2], WorldCupY[coordType - 2], 3, 0);
				Fight ThirdFight2 = Fight(CupOfKal.find(n)->second.Groups[1].PID, CupOfKal.find(n)->second.Groups[2].PID, WorldCupX[coordType - 1], WorldCupY[coordType - 1], 1, 2);

				ThirdFight[n].FightList.push_back(ThirdFight1);
				ThirdFight[n].FightList.push_back(ThirdFight2);

			}
		}
		WorldCup::Active = true;
		WorldCup::Time = 0;
		WorldCup::Round = 0;
		WorldCup::FightsActive = false;
		FinalsWinners.clear();
	}
}

void FightDraw(Fight fight) {
	CupRegistration[fight.Player1].team.Points += 1;
	CupRegistration[fight.Player2].team.Points += 1;

	TargetFind myTarget(0, 1, fight.Player1);
	int xPlayer = (int)myTarget.getTarget();

	IChar IPlayer1((void*)xPlayer);

	if (IPlayer1.IsOnline()) {
		IPlayer1.RemoveSetBlue();
		IPlayer1.RemoveSetRed();
		IPlayer1.Teleport(0, 215296, 280724);
		IPlayer1.CloseScreenTime();
		IPlayer1.CancelBuff(902);
		IPlayer1.CancelBuff(903);
		IPlayer1.SetHonor(2 * WorldCup::Round, 4 * WorldCup::Round, 0, 0, 0, 0, 0, 0, 0, 0);
	}

	TargetFind myTarget1(0, 1, fight.Player2);
	int xPlayer2 = (int)myTarget1.getTarget();
	IChar IPlayer2((void*)xPlayer2);

	if (IPlayer2.IsOnline()) {
		IPlayer2.RemoveSetBlue();
		IPlayer2.RemoveSetRed();
		IPlayer2.Teleport(0, 215296, 280724);
		IPlayer2.CloseScreenTime();
		IPlayer2.CancelBuff(902);
		IPlayer2.CancelBuff(903);
		IPlayer2.SetHonor(2 * WorldCup::Round, 4 * WorldCup::Round, 0, 0, 0, 0, 0, 0, 0, 0);
	}

	WorldCup::Fights--;
}

void PlayerWonFight(int PID, int position) {

	TargetFind myTarget(0, 1, PID);
	int xPlayer = (int)myTarget.getTarget();

	IChar IPlayer((void*)xPlayer);
	if (IPlayer.IsOnline()) {
		if (WorldCup::Round == 7) {
			if (IPlayer.GetLevel() >= 1 && IPlayer.GetLevel() <= 70)
				(*(int(__cdecl **)(int, signed int, signed int, unsigned __int64, unsigned __int64))(*(DWORD *)IPlayer.GetOffset() + 88))((int)IPlayer.GetOffset(), 25, 1, (unsigned __int64)F10Exp1, HIDWORD(F10Exp1));
			if (IPlayer.GetLevel() >= 71 && IPlayer.GetLevel() < 75)
				(*(int(__cdecl **)(int, signed int, signed int, unsigned __int64, unsigned __int64))(*(DWORD *)IPlayer.GetOffset() + 88))((int)IPlayer.GetOffset(), 25, 1, (unsigned __int64)F10Exp2, HIDWORD(F10Exp2));
			if (IPlayer.GetLevel() >= 75 && IPlayer.GetLevel() < 80)
				(*(int(__cdecl **)(int, signed int, signed int, unsigned __int64, unsigned __int64))(*(DWORD *)IPlayer.GetOffset() + 88))((int)IPlayer.GetOffset(), 25, 1, (unsigned __int64)F10Exp3, HIDWORD(F10Exp3));
			if (IPlayer.GetLevel() >= 80 && IPlayer.GetLevel() < 85)
				(*(int(__cdecl **)(int, signed int, signed int, unsigned __int64, unsigned __int64))(*(DWORD *)IPlayer.GetOffset() + 88))((int)IPlayer.GetOffset(), 25, 1, (unsigned __int64)F10Exp4, HIDWORD(F10Exp4));
			if (IPlayer.GetLevel() >= 85 && IPlayer.GetLevel() < 90)
				(*(int(__cdecl **)(int, signed int, signed int, unsigned __int64, unsigned __int64))(*(DWORD *)IPlayer.GetOffset() + 88))((int)IPlayer.GetOffset(), 25, 1, (unsigned __int64)F10Exp5, HIDWORD(F10Exp5));
			if (IPlayer.GetLevel() >= 90 && IPlayer.GetLevel() < 95)
				(*(int(__cdecl **)(int, signed int, signed int, unsigned __int64, unsigned __int64))(*(DWORD *)IPlayer.GetOffset() + 88))((int)IPlayer.GetOffset(), 25, 1, (unsigned __int64)F10Exp6, HIDWORD(F10Exp6));
			if (IPlayer.GetLevel() >= 95 && IPlayer.GetLevel() < 100)
				(*(int(__cdecl **)(int, signed int, signed int, unsigned __int64, unsigned __int64))(*(DWORD *)IPlayer.GetOffset() + 88))((int)IPlayer.GetOffset(), 25, 1, (unsigned __int64)F10Exp7, HIDWORD(F10Exp7));

			CDBSocket::Write(98, "dddd", IPlayer.GetPID(), 1, 1, 1);
			WCWinner = (std::string) IPlayer.GetName();
			IPlayer.BoxMsg("Congratulations! You've won the World Cup!");
			std::string msg = (std::string) IPlayer.GetName() + " has won the World Cup! ";
			CPlayer::WriteAll(0xFF, "dsd", 247, msg.c_str(), 2);
		}
		else {
			IPlayer.BoxMsg("Congratulations! You've won round " + Int2String(WorldCup::Round) + " !");
			std::string msg = (std::string) IPlayer.GetName() + " has won the round due to the opponent not being online ";
			CPlayer::WriteAll(0xFF, "dsd", 247, msg.c_str(), 2);
		}

		if (WCRewards.count((WorldCup::Round * 100) + 1)) {
			for (int i = 0; i<WCRewards.find((WorldCup::Round * 100) + 1)->second.RewardList.size(); i++) {
				WCReward reward = WCRewards.find((WorldCup::Round * 100) + 1)->second.RewardList[i];
				if (GetInventorySize((int)IPlayer.GetOffset(), 0) < 60)
					CItem::InsertItem((int)IPlayer.Offset, 27, reward.Index, 0, reward.Amount, -1);
			}
		}
		IPlayer.SetHonor(10 * WorldCup::Round, 20 * WorldCup::Round, 0, 0, 0, 0, 0, 0, 0, 1);
		CupRegistration[IPlayer.GetPID()].team.Points += 3;
		IPlayer.RemoveSetBlue();
		IPlayer.RemoveSetRed();
		IPlayer.Teleport(0, 215296, 280724);
		IPlayer.CloseScreenTime();
		IPlayer.CancelBuff(902);
		IPlayer.CancelBuff(903);
	}

	if (WorldCup::Round >= 4) {
		if (WorldCup::Round == 7) {
			CupRegistration.clear();
			WCDamage.clear();
			FinalsWinners.clear();
			WorldCup::Active = false;
		}
		else
			FinalsWinners[position].PlayerList.push_back(PID);
	}

	WorldCup::Fights--;
}

void PlayerWonFight(IChar IPlayer, Fight fight) {

	int OPID = fight.Player1;
	std::string msg = "";
	if (IPlayer.IsOnline()) {
		if (IPlayer.GetPID() == fight.Player1)
			OPID = fight.Player2;

		if (WCRewards.count((fight.Round * 100) + 1)) {
			for (int i = 0; i<WCRewards.find((fight.Round * 100) + 1)->second.RewardList.size(); i++) {
				WCReward reward = WCRewards.find((fight.Round * 100) + 1)->second.RewardList[i];
				if (GetInventorySize((int)IPlayer.GetOffset(), 0) < 60)
					CItem::InsertItem((int)IPlayer.Offset, 27, reward.Index, 0, reward.Amount, -1);
			}
		}
		IPlayer.SetHonor(10 * fight.Round, 20 * fight.Round, 0, 0, 0, 0, 0, 0, 0, 1);
		if (fight.Round == 7) {

			if (IPlayer.GetLevel() >= 1 && IPlayer.GetLevel() <= 70)
				(*(int(__cdecl **)(int, signed int, signed int, unsigned __int64, unsigned __int64))(*(DWORD *)IPlayer.GetOffset() + 88))((int)IPlayer.GetOffset(), 25, 1, (unsigned __int64)F10Exp1, HIDWORD(F10Exp1));
			if (IPlayer.GetLevel() >= 71 && IPlayer.GetLevel() < 75)
				(*(int(__cdecl **)(int, signed int, signed int, unsigned __int64, unsigned __int64))(*(DWORD *)IPlayer.GetOffset() + 88))((int)IPlayer.GetOffset(), 25, 1, (unsigned __int64)F10Exp2, HIDWORD(F10Exp2));
			if (IPlayer.GetLevel() >= 75 && IPlayer.GetLevel() < 80)
				(*(int(__cdecl **)(int, signed int, signed int, unsigned __int64, unsigned __int64))(*(DWORD *)IPlayer.GetOffset() + 88))((int)IPlayer.GetOffset(), 25, 1, (unsigned __int64)F10Exp3, HIDWORD(F10Exp3));
			if (IPlayer.GetLevel() >= 80 && IPlayer.GetLevel() < 85)
				(*(int(__cdecl **)(int, signed int, signed int, unsigned __int64, unsigned __int64))(*(DWORD *)IPlayer.GetOffset() + 88))((int)IPlayer.GetOffset(), 25, 1, (unsigned __int64)F10Exp4, HIDWORD(F10Exp4));
			if (IPlayer.GetLevel() >= 85 && IPlayer.GetLevel() < 90)
				(*(int(__cdecl **)(int, signed int, signed int, unsigned __int64, unsigned __int64))(*(DWORD *)IPlayer.GetOffset() + 88))((int)IPlayer.GetOffset(), 25, 1, (unsigned __int64)F10Exp5, HIDWORD(F10Exp5));
			if (IPlayer.GetLevel() >= 90 && IPlayer.GetLevel() < 95)
				(*(int(__cdecl **)(int, signed int, signed int, unsigned __int64, unsigned __int64))(*(DWORD *)IPlayer.GetOffset() + 88))((int)IPlayer.GetOffset(), 25, 1, (unsigned __int64)F10Exp6, HIDWORD(F10Exp6));
			if (IPlayer.GetLevel() >= 95 && IPlayer.GetLevel() < 100)
				(*(int(__cdecl **)(int, signed int, signed int, unsigned __int64, unsigned __int64))(*(DWORD *)IPlayer.GetOffset() + 88))((int)IPlayer.GetOffset(), 25, 1, (unsigned __int64)F10Exp7, HIDWORD(F10Exp7));

			IPlayer.BoxMsg("Congratulations! You've won the World Cup!");
			msg = (std::string) IPlayer.GetName() + " has won the World Cup";
			CDBSocket::Write(98, "dddd", IPlayer.GetPID(), 1, 1, 1);
			WCWinner = (std::string) IPlayer.GetName();
		}
		else {
			IPlayer.BoxMsg("Congratulations! You've won round " + Int2String(fight.Round) + " !");
			msg = (std::string) IPlayer.GetName() + " has won the round";
		}
	}

	TargetFind myTarget(0, 1, OPID);
	int xPlayer = (int)myTarget.getTarget();

	IChar IPlayer2((void*)xPlayer);

	if (IPlayer2.IsOnline()) {
		if (WCRewards.count((fight.Round * 100) + 2)) {
			for (int i = 0; i < WCRewards.find((fight.Round * 100) + 2)->second.RewardList.size(); i++) {
				WCReward reward = WCRewards.find((fight.Round * 100) + 2)->second.RewardList[i];
				if (GetInventorySize((int)IPlayer2.GetOffset(), 0) < 60)
					CItem::InsertItem((int)IPlayer2.Offset, 27, reward.Index, 0, reward.Amount, -1);
			}
		}
		IPlayer2.SetHonor(0, 0, 1, 0, 0, 0, 0, 0, 0, 0);

		if (fight.Round >= 4)
			IPlayer2.SetHonor(8 * (fight.Round - 2), 15 * (fight.Round - 2), 0, 0, 0, 0, 0, 0, 0, 0);

		if (fight.Round == 7) {
			if (IPlayer2.GetLevel() >= 1 && IPlayer2.GetLevel() <= 70)
				(*(int(__cdecl **)(int, signed int, signed int, unsigned __int64, unsigned __int64))(*(DWORD *)IPlayer2.GetOffset() + 88))((int)IPlayer2.GetOffset(), 25, 1, (unsigned __int64)F10Exp1 / 3, HIDWORD(F10Exp1 / 3));
			if (IPlayer2.GetLevel() >= 71 && IPlayer2.GetLevel() < 75)
				(*(int(__cdecl **)(int, signed int, signed int, unsigned __int64, unsigned __int64))(*(DWORD *)IPlayer2.GetOffset() + 88))((int)IPlayer2.GetOffset(), 25, 1, (unsigned __int64)F10Exp2 / 3, HIDWORD(F10Exp2 / 3));
			if (IPlayer2.GetLevel() >= 75 && IPlayer2.GetLevel() < 80)
				(*(int(__cdecl **)(int, signed int, signed int, unsigned __int64, unsigned __int64))(*(DWORD *)IPlayer2.GetOffset() + 88))((int)IPlayer2.GetOffset(), 25, 1, (unsigned __int64)F10Exp3 / 3, HIDWORD(F10Exp3 / 3));
			if (IPlayer2.GetLevel() >= 80 && IPlayer2.GetLevel() < 85)
				(*(int(__cdecl **)(int, signed int, signed int, unsigned __int64, unsigned __int64))(*(DWORD *)IPlayer2.GetOffset() + 88))((int)IPlayer2.GetOffset(), 25, 1, (unsigned __int64)F10Exp4 / 3, HIDWORD(F10Exp4 / 3));
			if (IPlayer2.GetLevel() >= 85 && IPlayer2.GetLevel() < 90)
				(*(int(__cdecl **)(int, signed int, signed int, unsigned __int64, unsigned __int64))(*(DWORD *)IPlayer2.GetOffset() + 88))((int)IPlayer2.GetOffset(), 25, 1, (unsigned __int64)F10Exp5 / 3, HIDWORD(F10Exp5 / 3));
			if (IPlayer2.GetLevel() >= 90 && IPlayer2.GetLevel() < 95)
				(*(int(__cdecl **)(int, signed int, signed int, unsigned __int64, unsigned __int64))(*(DWORD *)IPlayer2.GetOffset() + 88))((int)IPlayer2.GetOffset(), 25, 1, (unsigned __int64)F10Exp6 / 3, HIDWORD(F10Exp6 / 3));
			if (IPlayer2.GetLevel() >= 95 && IPlayer2.GetLevel() < 100)
				(*(int(__cdecl **)(int, signed int, signed int, unsigned __int64, unsigned __int64))(*(DWORD *)IPlayer2.GetOffset() + 88))((int)IPlayer2.GetOffset(), 25, 1, (unsigned __int64)F10Exp7 / 3, HIDWORD(F10Exp7 / 3));

			CDBSocket::Write(98, "dddd", IPlayer.GetPID(), 0, 1, 0);
		}

		msg += " against " + (std::string)IPlayer2.GetName();

		CPlayer::WriteAll(0xFF, "dsd", 247, msg.c_str(), 2);
	}

	if (IPlayer.IsOnline()) {
		CupRegistration[IPlayer.GetPID()].team.Points += 3;
		IPlayer.RemoveSetBlue();
		IPlayer.RemoveSetRed();
		IPlayer.CancelBuff(902);
		IPlayer.CancelBuff(903);
		IPlayer.Teleport(0, 215296, 280724);
		IPlayer.CloseScreenTime();
	}

	if (IPlayer2.IsOnline()) {
		IPlayer2.RemoveSetBlue();
		IPlayer2.RemoveSetRed();
		IPlayer2.CancelBuff(902);
		IPlayer2.CancelBuff(903);
		IPlayer2.Teleport(0, 215296, 280724);
		IPlayer2.CloseScreenTime();
	}

	if (fight.Round >= 4) {
		if (fight.Round == 7) {
			CupRegistration.clear();
			WCDamage.clear();
			FinalsWinners.clear();
			WorldCup::Active = false;
		}
		else
			FinalsWinners[fight.P2Position].PlayerList.push_back(IPlayer.GetPID());
	}

	WorldCup::Fights--;
}

void StartFight(Fight fight) {

	fight.Round = WorldCup::Round;
	WorldCup::Fights++;

	if (!fight.Player1 || !fight.Player2) {
		WorldCup::Fights--;
		return;
	}

	if (!WorldCup::FightsActive)
		WorldCup::FightsActive = true;

	TargetFind myTarget1(0, 1, fight.Player1);
	int xPlayer1 = (int)myTarget1.getTarget();

	TargetFind myTarget(0, 1, fight.Player2);
	int xPlayer2 = (int)myTarget.getTarget();

	if (!xPlayer1 && !xPlayer2) {
		WorldCup::Fights--;
		return;
	}

	if (!xPlayer1 || !xPlayer2) {
		if (xPlayer1) {
			IChar IPlayer((void*)xPlayer1);
			PlayerWonFight(IPlayer, fight);
		}
		if (xPlayer2) {
			IChar IPlayer2((void*)xPlayer2);
			PlayerWonFight(IPlayer2, fight);
		}
		return;
	}

	IChar IPlayer1((void*)xPlayer1);
	IChar IPlayer2((void*)xPlayer2);

	if (!IPlayer1.IsValid() && !IPlayer2.IsValid()) {
		WorldCup::Fights--;
		return;
	}
	if (!IPlayer1.IsValid() && IPlayer2.IsValid()) {

		PlayerWonFight(IPlayer2, fight);
		return;
	}

	if (!IPlayer2.IsValid() && IPlayer1.IsValid()) {
		PlayerWonFight(IPlayer1, fight);
		return;
	}

	if (IPlayer1.IsValid() && IPlayer2.IsValid()) {
		IPlayer1.Teleport(0, fight.CoordX + CTools::Rate(-100, 100), fight.CoordY + CTools::Rate(-100, 100));
		IPlayer2.Teleport(0, fight.CoordX + CTools::Rate(-100, 100), fight.CoordY + CTools::Rate(-100, 100));

		IPlayer1.Buff(902, WorldCupTime + 5, 0);
		IPlayer2.Buff(903, WorldCupTime + 5, 0);

		IPlayer1.ScreenTime(WorldCup::Time);
		IPlayer1.SetRed();

		IPlayer2.ScreenTime(WorldCup::Time);
		IPlayer2.SetBlue();
	}

	CupRegistration[IPlayer1.GetPID()].fight = fight;
	CupRegistration[IPlayer2.GetPID()].fight = fight;

}

void StartGroupFights(int start, int end) {

	int round = WorldCup::Round;
	std::map<int, Fights> FightRounds = FirstFight;
	if (round == 2 || round == 2.5)
		FightRounds = SecondFight;
	if (round == 3 || round == 3.5)
		FightRounds = ThirdFight;

	for (int i = start; i <= end; i++) {
		for each(Fight fight in FightRounds.find(i)->second.FightList)
			StartFight(fight);
	}
	FightRounds.clear();
}

void StartFinalRounds() {

	if (WorldCup::Round == 4) {
		FirstFight.clear();
		SecondFight.clear();
		ThirdFight.clear();

		for (int i = 1; i <= 8; i++) {
			std::sort(CupOfKal.find(i)->second.Groups.begin(), CupOfKal.find(i)->second.Groups.end(), compareTeamByLength);
		}

		for (int n = 1; n <= 8; n += 2) {
			Fight Fight1 = Fight(CupOfKal.find(n)->second.Groups[0].PID, CupOfKal.find(n + 1)->second.Groups[1].PID, WorldCupX[n - 1], WorldCupY[n - 1], 0, 1);
			Fight Fight2 = Fight(CupOfKal.find(n + 1)->second.Groups[0].PID, CupOfKal.find(n)->second.Groups[1].PID, WorldCupX[n], WorldCupY[n], 0, 2);
			StartFight(Fight1);
			StartFight(Fight2);
		}
	}

	if (WorldCup::Round == 5) {
		CupOfKal.clear();

		std::map<int, Winners> sFinalsWinners = FinalsWinners;
		FinalsWinners.clear();
		for (int i = 1; i <= 2; i++) {
			if (!sFinalsWinners.count(i))
				continue;

			if (sFinalsWinners.find(i)->second.PlayerList.size()<2) {

				if (sFinalsWinners.find(i)->second.PlayerList.size() == 1) {
					WorldCup::FightsActive = true;
					WorldCup::Fights++;
					PlayerWonFight(sFinalsWinners.find(i)->second.PlayerList[0], i);
				}
				continue;
			}
			for (int n = 0; n<sFinalsWinners.find(i)->second.PlayerList.size() - 1; n += 2) {
				Fight Fight1 = Fight(sFinalsWinners.find(i)->second.PlayerList[n], sFinalsWinners.find(i)->second.PlayerList[n + 1], WorldCupX[n + i], WorldCupY[n + i], 0, i);
				StartFight(Fight1);
			}
		}
		sFinalsWinners.clear();
	}

	if (WorldCup::Round == 6) {
		std::map<int, Winners> sFinalsWinners = FinalsWinners;
		FinalsWinners.clear();
		for (int i = 1; i <= 2; i++) {
			if (!sFinalsWinners.count(i)) {
				continue;
			}

			if (sFinalsWinners.find(i)->second.PlayerList.size()<2) {
				if (sFinalsWinners.find(i)->second.PlayerList.size() == 1) {
					WorldCup::FightsActive = true;
					WorldCup::Fights++;
					PlayerWonFight(sFinalsWinners.find(i)->second.PlayerList[0], 1);
				}
				continue;
			}
			Fight Fight1 = Fight(sFinalsWinners.find(i)->second.PlayerList[0], sFinalsWinners.find(i)->second.PlayerList[1], WorldCupX[i], WorldCupY[i], 0, 1);

			StartFight(Fight1);
		}
		sFinalsWinners.clear();
	}

	if (WorldCup::Round == 7) {
		std::map<int, Winners> sFinalsWinners = FinalsWinners;
		FinalsWinners.clear();

		if (!sFinalsWinners.count(1))
			return;

		if (sFinalsWinners.find(1)->second.PlayerList.size()<2) {
			if (sFinalsWinners.find(1)->second.PlayerList.size() == 1) {
				WorldCup::FightsActive = true;
				WorldCup::Fights++;
				PlayerWonFight(sFinalsWinners.find(1)->second.PlayerList[0], 1);
				sFinalsWinners.clear();
			}
			return;
		}

		Fight Fight1 = Fight(sFinalsWinners.find(1)->second.PlayerList[0], sFinalsWinners.find(1)->second.PlayerList[1], WorldCupX[0], WorldCupY[0], 0, 1);
		StartFight(Fight1);
		sFinalsWinners.clear();
	}
}

void WorldCupTick() {

	std::map<int, PlayerFight> Cup = CupRegistration.toMap();

	for (auto x = Cup.begin(); x != Cup.end(); x++) {
		if (!x->second.fight.Round)
			continue;

		TargetFind myTarget1(0, 1, x->first);
		int xPlayer1 = (int)myTarget1.getTarget();
		IChar IPlayer((void*)xPlayer1);

		if (IPlayer.IsOnline()) {
			Fight playerFight = x->second.fight;
			int OPID = playerFight.Player1;
			if (IPlayer.IsBuff(902)) {
				IPlayer.SetRed();
				OPID = playerFight.Player2;
			}
			else if (IPlayer.IsBuff(903))
				IPlayer.SetBlue();
			else
				continue;

			TargetFind myTarget(0, 1, OPID);
			int xPlayer = (int)myTarget.getTarget();
			IChar IPlayer2((void*)xPlayer);

			if (!IPlayer2.IsOnline())
				PlayerWonFight(IPlayer, playerFight);
			else
			{
				if (CChar::IsGState((int)IPlayer.GetOffset(), 2))
					PlayerWonFight(IPlayer2, playerFight);

				else if (!WorldCup::Time) {
					if (playerFight.Round >= 4) {
						if (IPlayer.GetCurHp() > IPlayer2.GetCurHp())
							PlayerWonFight(IPlayer, playerFight);
						else
							PlayerWonFight(IPlayer2, playerFight);
					}
					else {
						FightDraw(playerFight);
					}
				}
			}
		}
	}
}

void WorldCupTimer() {
	if (WorldCup::Active) {
		if (WorldCup::Round == 0 && WorldCup::Time == 0) {
			WorldCup::Round = 1;
			WorldCup::Fights = 0;
			WorldCup::FightsActive = false;
			WorldCup::Time = WorldCupTime;
		}
		if (WorldCup::Round == 1 && WorldCup::Time == 0) {
			WorldCup::Round = 1.5;
			WorldCup::Fights = 0;
			WorldCup::FightsActive = false;
			WorldCup::Time = WorldCupTime;
		}
		if (WorldCup::Round == 1.5 && WorldCup::Time == 0) {
			WorldCup::Round = 2;
			WorldCup::Fights = 0;
			WorldCup::FightsActive = false;
			WorldCup::Time = WorldCupTime;
		}
		if (WorldCup::Round == 2 && WorldCup::Time == 0) {
			WorldCup::Round = 2.5;
			WorldCup::Fights = 0;
			WorldCup::FightsActive = false;
			WorldCup::Time = WorldCupTime;
		}
		if (WorldCup::Round == 2.5 && WorldCup::Time == 0) {
			WorldCup::Round = 3;
			WorldCup::Fights = 0;
			WorldCup::FightsActive = false;
			WorldCup::Time = WorldCupTime;
		}
		if (WorldCup::Round == 3 && WorldCup::Time == 0) {
			WorldCup::Round = 3.5;
			WorldCup::Fights = 0;
			WorldCup::FightsActive = false;
			WorldCup::Time = WorldCupTime;
		}
		if (WorldCup::Round == 3.5 && WorldCup::Time == 0) {
			WorldCup::Round = 4;
			WorldCup::Fights = 0;
			WorldCup::FightsActive = false;
			WorldCup::Time = WorldCupTime + 5;
		}
		if (WorldCup::Round == 4 && WorldCup::Time == 0) {
			WorldCup::Round = 5;
			WorldCup::Fights = 0;
			WorldCup::FightsActive = false;
			WorldCup::Time = WorldCupTime + 10;
		}
		if (WorldCup::Round == 5 && WorldCup::Time == 0) {
			WorldCup::Round = 6;
			WorldCup::Fights = 0;
			WorldCup::FightsActive = false;
			WorldCup::Time = WorldCupTime + 20;
		}
		if (WorldCup::Round == 6 && WorldCup::Time == 0) {
			WorldCup::Round = 7;
			WorldCup::Fights = 0;
			WorldCup::FightsActive = false;
			WorldCup::Time = WorldCupTime + 30;
		}
		if (WorldCup::Round == 7 && WorldCup::Time == 0) {
			CupRegistration.clear();
			WCDamage.clear();
			FinalsWinners.clear();
			WorldCup::Active = false;
		}

		if (WorldCup::Time>0) {
			WorldCup::Time--;
			if (WorldCup::Fights <= 0 && WorldCup::FightsActive) {
				WorldCup::Time = 0;
			}
		}

		std::string Type = "";
		if (WorldCup::Round == 1)
			Type = "World Cup Group Stage Matchday 1 (Groups 1 to 4)";
		if (WorldCup::Round == 1.5)
			Type = "World Cup Group Stage Matchday 1 (Groups 5 to 8)";
		if (WorldCup::Round == 2)
			Type = "World Cup Group Stage Matchday 2 (Groups 1 to 4)";
		if (WorldCup::Round == 2.5)
			Type = "World Cup Group Stage Matchday 2 (Groups 5 to 8)";
		if (WorldCup::Round == 3)
			Type = "World Cup Group Stage Matchday 3 (Groups 1 to 4)";
		if (WorldCup::Round == 3.5)
			Type = "World Cup Group Stage Matchday 3 (Groups 5 to 8)";
		if (WorldCup::Round == 4)
			Type = "World Cup Round of 16";
		if (WorldCup::Round == 5)
			Type = "World Cup Quarter-finals";
		if (WorldCup::Round == 6)
			Type = "World Cup Semi-finals";
		if (WorldCup::Round == 7)
			Type = "World Cup Final";

		if (WorldCup::Time == WorldCupTime - 15) {

			WorldCup::Fights = 0;
			WorldCup::FightsActive = false;

			if (WorldCup::Round == 1 || WorldCup::Round == 2 || WorldCup::Round == 3)
				StartGroupFights(1, 4);
			if (WorldCup::Round == 1.5 || WorldCup::Round == 2.5 || WorldCup::Round == 3.5)
				StartGroupFights(5, 8);
			if (WorldCup::Round >= 4 && WorldCup::Round <= 7)
				StartFinalRounds();
			return;
		}

		if (WorldCup::Time>WorldCupTime - 16 && WorldCup::Round <= 7) {
			int color = WorldCup::Round;
			if (color == 3)
				color = 8;
			if (color == 6)
				color = 9;
			std::string msg = Type + " Is Starting in " + Int2String(WorldCup::Time - 180) + " seconds";
			CPlayer::WriteAll(0xFF, "dsd", 247, msg.c_str(), color);
		}
		else
			WorldCupTick();

	}
}