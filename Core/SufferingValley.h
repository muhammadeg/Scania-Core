void InsertWinnerSV(int GID, std::string Name) {
	std::string Datko = "./Winners/SufferingValley.db";
	std::fstream DGkLOG;
	DGkLOG.open(Datko, std::fstream::in | std::fstream::out | std::fstream::app);
	DGkLOG << "(Winner (Time " << Time::GetDate() + " " + Time::GetTime() << ")(GID " << GID << ")(name '" << Name << "'))" << std::endl;
	DGkLOG.close();
}

void SVSelection() {
	if (SufferingValleyRegistration.size() > 1)
	{
		string line;

		ifstream fin;
		fin.open("./Database/SufferingValley.db");
		ofstream temp;
		temp.open("./Database/temps.txt");

		while (getline(fin, line))
		{
			int PID = 0;
			if (sscanf(line.c_str(), "(registration (GID %d)", &PID) == 1)
				temp << line << endl;
		}

		temp.close();
		fin.close();
		remove("./Database/SufferingValley.db");
		rename("./Database/temps.txt", "./Database/SufferingValley.db");

		std::vector<DKInfo> GuildSelections;
		for (auto it = SufferingValleyRegistration.begin(); it != SufferingValleyRegistration.end(); it++) {
			if (!((SystemBlacklist.count(4) && SystemBlacklist.find(4)->second.count(it->first)) || it->first == Protect32::GuildFirst || it->first == Protect32::GuildSecond || it->first == Scenario::GuildFirst || it->first == Scenario::GuildSecond)) {
				DKInfo dk = DKInfo();
				dk.GID = it->first;
				dk.Name = it->second;
				GuildSelections.push_back(dk);
			}
		}

		SufferingValleyRegistration.clear();

		if (GuildSelections.size() > 1) {
			srand(time(0));
			std::random_shuffle(GuildSelections.begin(), GuildSelections.end());
			DKInfo dk = GuildSelections[0];
			DKInfo dk1 = GuildSelections[1];

			SufferingValley::GuildFirst = dk.GID;
			SufferingValley::FirstGuild = dk.Name;

			SufferingValley::GuildSecond = dk1.GID;
			SufferingValley::SecondGuild = dk1.Name;
			SVParticipantsRed.clear();
			SVParticipantsBlue.clear();

			if (SVRegisterDefault) {
				CIOCriticalSection::Enter((void*)0x004e2078);
				CIOCriticalSection::Enter((void*)0x004e2098);
				CLink::MoveTo((void*)0x004e200c, (int)0x004e2004);
				CIOCriticalSection::Leave((void*)0x004e2098);
				for (DWORD a = *(DWORD*)0x004E2004; a != 0x004E2004; a = *(DWORD*)a)
				{
					if ((void*)(a - 428))
					{
						IChar IParticipant((void*)(a - 428));
						int GID = IParticipant.GetGID();
						if (GID == SufferingValley::GuildFirst || GID == SufferingValley::GuildSecond) {
							SVParticipant participant = SVParticipant();
							participant.Name = IParticipant.GetName();
							participant.Level = IParticipant.GetLevel();
							participant.Specialty = (IParticipant.GetClass() << 16) | IParticipant.GetSpecialty();

							if (GID == SufferingValley::GuildFirst)
								SVParticipantsRed.replaceInsert(IParticipant.GetPID(), participant);
							else
								if (GID == SufferingValley::GuildSecond)
									SVParticipantsBlue.replaceInsert(IParticipant.GetPID(), participant);

							IParticipant.SystemMessage("You have been selected to play on Suffering Valley.", TEXTCOLOR_GREEN);
						}
					}
				}
				CIOCriticalSection::Leave((void*)0x004e2078);
			}

			std::string Datko = "./Database/SufferingValley.db";
			std::fstream DGkLOG;
			DGkLOG.open(Datko, std::fstream::in | std::fstream::out | std::fstream::app);
			DGkLOG << "(chosen (GID " << SufferingValley::GuildFirst << ")(name '" << SufferingValley::FirstGuild << "'))" << std::endl;
			DGkLOG << "(chosen (GID " << SufferingValley::GuildSecond << ")(name '" << SufferingValley::SecondGuild << "'))" << std::endl;
			DGkLOG.close();

			std::string msg = "Suffering Valley will start between " + SufferingValley::FirstGuild + " guild and " + SufferingValley::SecondGuild + " guild.";
			CPlayer::WriteAll(0xFF, "dsd", 247, msg.c_str(), 2);
			SufferingValley::Selection = true;
		}
		else {
			std::string msg = "Destructing Key selection could not have been made due to low amount of registered guilds.";
			CPlayer::WriteAll(0xFF, "dsd", 247, msg.c_str(), 2);
			SufferingValley::Selection = false;
		}
	}
}

void startSV() {
	if (!SufferingValley::GuildFirst || !SufferingValley::GuildSecond || !SufferingValley::Selection)
		SVSelection();

	if (SufferingValley::Selection && SufferingValley::GuildFirst && SufferingValley::GuildSecond)
	{
		if (SVParticipantsRed.empty() || SVParticipantsBlue.empty() || SVRegisterDefault == 2) {
			SVParticipantsRed.clear();
			SVParticipantsBlue.clear();
			CIOCriticalSection::Enter((void*)0x004e2078);
			CIOCriticalSection::Enter((void*)0x004e2098);
			CLink::MoveTo((void*)0x004e200c, (int)0x004e2004);
			CIOCriticalSection::Leave((void*)0x004e2098);
			for (DWORD a = *(DWORD*)0x004E2004; a != 0x004E2004; a = *(DWORD*)a)
			{
				if ((void*)(a - 428))
				{
					IChar IParticipant((void*)(a - 428));
					int GID = IParticipant.GetGID();
					if (GID == SufferingValley::GuildFirst || GID == SufferingValley::GuildSecond) {
						SVParticipant participant = SVParticipant();
						participant.Name = IParticipant.GetName();
						participant.Level = IParticipant.GetLevel();
						participant.Specialty = (IParticipant.GetClass() << 16) | IParticipant.GetSpecialty();

						if (GID == SufferingValley::GuildFirst)
							SVParticipantsRed.replaceInsert(IParticipant.GetPID(), participant);
						else
							if (GID == SufferingValley::GuildSecond)
								SVParticipantsBlue.replaceInsert(IParticipant.GetPID(), participant);

						IParticipant.SystemMessage("You have been selected to play on Suffering Valley.", TEXTCOLOR_GREEN);
					}
				}
			}
			CIOCriticalSection::Leave((void*)0x004e2078);
		}

		std::string msg = "Suffering Valley started between ";
		msg = msg + SufferingValley::FirstGuild;
		msg = msg + " guild and ";
		msg = msg + SufferingValley::SecondGuild;
		msg = msg + " guild.";
		CPlayer::WriteAll(0xFF, "dsd", 247, msg.c_str(), 2);
		SufferingValley::RedScore = 0;
		SufferingValley::BlueScore = 0;
		SufferingValley::Time = SVTime + 60 + (int)time(0);
		RewardLimit.clear();
		remove("./Database/SufferingValley.db");
		SufferingValley::BlueOpened = false;
		SufferingValley::RedOpened = false;
		SufferingValley::Active = true;
		SufferingValley::Selection = false;
	}
	else {
		CPlayer::WriteAll(0xFF, "dsd", 247, "Enough guilds did not registered for Suffering Valley.", 2);
	}
}

void SVPortPlayer(IChar IPlayer, bool IsRed) {
	if (IsRed)
		IPlayer.Teleport(SVMap, 335621 + CTools::Rate(-25, 25), 340759 + CTools::Rate(-25, 25));
	else
		IPlayer.Teleport(SVMap, 335651 + CTools::Rate(-25, 25), 330953 + CTools::Rate(-25, 25));
}

void SVPlayerTick(IChar IPlayer) {
	if (SufferingValley::Active) {
		int PID = IPlayer.GetPID();
		bool IsBlue = SVParticipantsBlue.count(PID);
		bool IsRed = !IsBlue ? SVParticipantsRed.count(PID) : false;
		if (IsBlue || IsRed) {
			if (IPlayer.GetMap() != SVMap) {
				SVPortPlayer(IPlayer, IsRed);
				CPlayer::Write(IPlayer.GetOffset(), 46, "dI", IPlayer.GetID(), __int64(0x20000 << (IsBlue ? 1 : 0)) << 32);
			}
			else {
				if ((SufferingValley::Time - (int)time(0)) <= SVTime)
					CPlayer::Write(IPlayer.GetOffset(), 0xFE, "dbddd", 168, 7, SufferingValley::Time - (int)time(0), SufferingValley::RedScore, SufferingValley::BlueScore);

				if (CChar::IsGState((int)IPlayer.GetOffset(), 2)) {
					if (IPlayer.IsBuff(BuffNames::RevivalCheck)) {
						int TimeLeft = IPlayer.GetBuffRemain(BuffNames::RevivalCheck);
						if (TimeLeft <= 1) {
							SVPortPlayer(IPlayer, IsRed);
							IPlayer.Buff(24, 6, 40);
							IPlayer.RemoveBuffIcon(0, 0, 703, 34);
							CChar::AddMState(IPlayer.GetOffset(), 0, 2147483648);
							IPlayer.SetBuffIcon(6000, 0, 1793, 201);
							CPlayer::Write(IPlayer.GetOffset(), 46, "dI", IPlayer.GetID(), __int64(0x20000 << (IsBlue ? 1 : 0)) << 32);
						}
						else
							IPlayer.SystemMessage("[Suffering Valley] Reviving in " + Int2String(TimeLeft - 1) + "...", TEXTCOLOR_DARKGREEN);
					}
					else {
						IPlayer.SystemMessage("[Suffering Valley] Reviving in " + Int2String(30) + "...", TEXTCOLOR_DARKGREEN);
						IPlayer.Buff(BuffNames::RevivalCheck, 31, 0);
					}
				}

				if (IsRed && IPlayer.GetRectY() <= 10351)
					SVPortPlayer(IPlayer, IsRed);

				if (IsBlue && IPlayer.GetRectY() >= 10639)
					SVPortPlayer(IPlayer, IsRed);
			}
		}
		else if (IPlayer.GetMap() == SVMap)
			IPlayer.PortToVillage();
	}
	else if (IPlayer.GetMap() == SVMap)
		IPlayer.PortToVillage();
}

void SVOnTimer() {
	if (SufferingValley::Time <= (int)time(0)) {

		bool Draw = SufferingValley::RedScore == SufferingValley::BlueScore;
		bool RedWin = Draw ? false : SufferingValley::RedScore > SufferingValley::BlueScore;
		bool BlueWin = Draw ? false : SufferingValley::BlueScore > SufferingValley::RedScore;

		int Overlay = 0;
		if (BlueWin) {
			Overlay = 1;
			InsertWinnerSV(SufferingValley::GuildSecond, SufferingValley::SecondGuild);
		}
		else
			if (RedWin) {
				Overlay = 2;
				InsertWinnerSV(SufferingValley::GuildFirst, SufferingValley::FirstGuild);
			}

		for (auto x = SVParticipantsRed.begin(); x != SVParticipantsRed.end(); x++) {
			int PID = x->first;
			TargetFind myTarget(0, 1, PID);
			int Player = (int)myTarget.getTarget();
			IChar IPlayer((void*)Player);
			if (Player && IPlayer.IsOnline()) {
				if (Draw)
					IPlayer.systemReward(SVDrawReward);
				else {
					if (RedWin)
						IPlayer.systemReward(SVWinnerReward);
					else
						IPlayer.systemReward(SVLoserReward);
				}
				IPlayer.RemoveSetRed();
				IPlayer.SetHonor(0, 0, 0, 0, 0, 0, 0, 1, RedWin ? 1 : 0, 0);
				CPlayer::Write((void*)Player, 0xFE, "dbb", 168, 10, Overlay);
			}
		}

		for (auto x = SVParticipantsBlue.begin(); x != SVParticipantsBlue.end(); x++) {
			int PID = x->first;
			TargetFind myTarget(0, 1, PID);
			int Player = (int)myTarget.getTarget();
			IChar IPlayer((void*)Player);
			if (Player && IPlayer.IsOnline()) {
				if (Draw)
					IPlayer.systemReward(SVDrawReward);
				else {
					if (BlueWin)
						IPlayer.systemReward(SVWinnerReward);
					else
						IPlayer.systemReward(SVLoserReward);
				}
				IPlayer.RemoveSetBlue();
				IPlayer.SetHonor(0, 0, 0, 0, 0, 0, 0, 1, BlueWin ? 1 : 0, 0);
				CPlayer::Write((void*)Player, 0xFE, "dbb", 168, 10, Overlay);
			}
		}

		SufferingValley::Selection = false;
		SufferingValley::Active = false;
		remove("./Database/SufferingValley.db");
	}
}