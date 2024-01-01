int TimeDayIndex = 0;
int TimeIndex = 0;
int LastTimeIndex = 0;
bool MidnightClean = false;
const char* event1 = NULL;
const char* event2 = NULL;
const char* endevent1 = NULL;
const char* endevent2 = NULL;

bool isMapsEvent(const char* type) {
	const char* result1 = NULL;
	const char* result2 = NULL;

	if (TimeIndex == LastTimeIndex)
		return false;

	auto it = EventMapsTimer.find(TimeDayIndex);

	if (it != EventMapsTimer.end())
		result1 = it->second.c_str();

	if (result1 && strlen(result1) && strstr(result1, type))
		return true;

	auto it2 = EventMapsTimer.find(TimeIndex);

	if (it2 != EventMapsTimer.end())
		result2 = it2->second.c_str();

	if (result2 && strlen(result2) && strstr(result2, type))
		return true;

	return false;
}

bool EventMapRegister(int Quest) {
	if (Quest && EventMapsQuests.count(Quest)) {
		EventMapsQuestsOn.insert(Quest);
		eventMap questEvent = EventMapsQuests.find(Quest)->second;
		std::string notice = "Registration for " + questEvent.Name + " has been activated.";
		CPlayer::WriteAll(0xFF, "ds", 234, notice.c_str());
		return true;
	}

	return false;
}

bool EventMapStart(int Quest) {
	if (EventMapsRegistration.count(Quest)) {
		std::set<int> Players = EventMapsRegistration.findValue(Quest).toSet();

		if (Players.empty())
			return false;

		eventMap questEvent = EventMapsQuests.find(Quest)->second;
		SpawnEventMap(questEvent, 0, questEvent.Duration * 1000);

		CIOCriticalSection::Enter((void*)0x004e2078);
		CIOCriticalSection::Enter((void*)0x004e2098);
		CLink::MoveTo((void*)0x004e200c, (int)0x004e2004);
		CIOCriticalSection::Leave((void*)0x004e2098);
		for (DWORD a = *(DWORD*)0x004E2004; a != 0x004E2004; a = *(DWORD*)a)
		{
			if ((void*)(a - 428))
			{
				IChar IPlayer((void*)(a - 428));
				if (Players.count(IPlayer.GetPID()) && IPlayer.IsPVPValid() && questEvent.LvlMin <= IPlayer.GetLevel() && questEvent.LvlMax >= IPlayer.GetLevel()) {
					IPlayer.SaveBuff(BuffNames::EventMapQuest, questEvent.Duration + 10, Quest, 0, 0);
					IPlayer.ScreenTime(questEvent.Duration);
				}
			}
		}
		CIOCriticalSection::Leave((void*)0x004e2078);

		EventMapsRegistration.erase(Quest);
		EventMapsQuestsOn.erase(Quest);

		string line;

		ifstream fin;
		fin.open("./Database/EventMaps.db");
		ofstream temp;
		temp.open("./Database/tempEventMaps.txt");

		while (getline(fin, line))
		{
			int Type = 0, PID = 0;
			if (sscanf(line.c_str(), "(registration (ID %d)(PID %d)", &Type, &PID) == 2)
			{
				if (Type != Quest)
					temp << line << endl;
			}
		}

		temp.close();
		fin.close();
		remove("./Database/EventMaps.db");
		rename("./Database/tempEventMaps.txt", "./Database/EventMaps.db");

		if (!questEvent.Name.empty()) {
			std::string notice = questEvent.Name + " has started.";
			CPlayer::WriteAll(0xFF, "ds", 234, notice.c_str());
		}
		return true;
	}
	return false;
}

bool isSystemTime(const char* type) {
	if (TimeIndex == LastTimeIndex)
		return false;

	if (event1 && strlen(event1) && strstr(event1, type))
		return true;

	if (event2 && strlen(event2) && strstr(event2, type))
		return true;

	return false;
}

int EventDay(std::string day) {
	std::transform(day.begin(), day.end(), day.begin(), ::tolower);

	day = day.substr(0, 3);

	int value = -2;
	if (day == "dai" || day == "eve")
		value = -1;

	else if (day == "sun")
		value = 0;
	else if (day == "mon")
		value = 1;
	else if (day == "tue")
		value = 2;
	else if (day == "wed")
		value = 3;
	else if (day == "thu")
		value = 4;
	else if (day == "fri")
		value = 5;
	else if (day == "sat")
		value = 6;

	return value;
}

int EventConfig(std::string day) {
	std::transform(day.begin(), day.end(), day.begin(), ::tolower);

	day = day.substr(0, 3);

	int value = 0;

	if (day == "sun")
		value = 1;
	else if (day == "mon")
		value = 2;
	else if (day == "tue")
		value = 3;
	else if (day == "wed")
		value = 4;
	else if (day == "thu")
		value = 5;
	else if (day == "fri")
		value = 6;
	else if (day == "sat")
		value = 7;

	return value;
}

bool isEndSystemTime(const char* type) {
	if (TimeIndex == LastTimeIndex)
		return false;

	if (endevent1 && strlen(endevent1) && strstr(endevent1, type))
		return true;

	if (endevent2 && strlen(endevent2) && strstr(endevent2, type))
		return true;

	return false;
}

void startBF(bool EvilVsGood) {
	if (Battlefield::Active == false) {
		if (BattlefieldRegistration.size() > 1)
		{
			Battlefield::BTeamLvl = 0;
			Battlefield::RTeamLvl = 0;
			std::string msg = EvilVsGood ? "The battle of Hogwarts has begun."  : (std::string(BFName) + " started.");
			CPlayer::WriteAll(0xFF, "dsd", 247, msg.c_str(), 2);
			Battlefield::Time = EvilVsGood ? GVETime : BFTime;
			Battlefield::RedScore = 0;
			Battlefield::BlueScore = 0;
			Battlefield::RegisterAmount = 0;
			RewardLimit.clear();
			BFRewardLimit.clear();
			Battlefield::GoodVsEvil = EvilVsGood;
			Battlefield::Active = true;
			IChar M1((void*)Summon(0, BFMap, EvilVsGood ? BlueStoneXG : BlueStoneX, EvilVsGood ? BlueStoneYG : BlueStoneY, 445, 1, 0, 0, 0, 0));
			IChar m1((void*)Summon(0, BFMap, EvilVsGood ? RedStoneXG : RedStoneX, EvilVsGood ? RedStoneYG : RedStoneY, 448, 1, 0, 0, 0, 0));
			Battlefield::BlueStoneID = M1.GetID();
			Battlefield::RedStoneID = m1.GetID();

			std::vector<int> Team;

			CIOCriticalSection::Enter((void*)0x004e2078);
			CIOCriticalSection::Enter((void*)0x004e2098);
			CLink::MoveTo((void*)0x004e200c, (int)0x004e2004);
			CIOCriticalSection::Leave((void*)0x004e2098);
			for (DWORD a = *(DWORD*)0x004E2004; a != 0x004E2004; a = *(DWORD*)a)
			{
				if ((void*)(a - 428))
				{
					IChar IPlayer((void*)(a - 428));
					if (BattlefieldRegistration.count(IPlayer.GetPID()) && IPlayer.IsPVPValid()) {
						if (!(SystemBlacklist.count(1) && SystemBlacklist.find(1)->second.count(IPlayer.GetPID())))
							Team.push_back((int)IPlayer.GetOffset());
					}
				}
			}
			CIOCriticalSection::Leave((void*)0x004e2078);

			BattlefieldRegistration.clear();

			std::sort(Team.begin(), Team.end(), compareTeamByLevel);

			if (EvilVsGood) {
				for (int i = 0; i < Team.size(); i++) {
					IChar IPlayer((void*)Team[i]);
					
					if(IPlayer.isSlytherin() || IPlayer.isRavenclaw())
						IPlayer.Buff(160, 3650, 0);
					else
						IPlayer.Buff(161, 3650, 0);
				}
			}
			else {
				int BFBuff = 161;
				for (int i = 0; i < Team.size(); i++) {
					IChar IPlayer((void*)Team[i]);
					IPlayer.Buff(BFBuff, 3650, 0);

					if (BFBuff == 161)
						BFBuff = 160;
					else
						BFBuff = 161;
				}
			}

			return;
		}
	}
	else {
		BattlefieldRegistration.clear();
		Battlefield::Active = false;
		Battlefield::Time = 0;
		return;
	}
}

void startSinEvent(int Time) {
	if (!SinEvent::Active) {
		CPlayer::WriteAll(0xFF, "dsd", 247, thisServerName + " Sin Event has started, move to the map right now to participate!", 2);
		SinEvent::Active = true;
		SinEvent::Time = (int)time(0) + Time; 
		
		for (auto x = SinSpawners.begin(); x != SinSpawners.end(); x++) {
			for (int i = 0; i<x->Amount; i++)
				Summon(0, 0, x->X, x->Y, x->Index, 1, 0, 0, Time * 1000, 0);
		}
	}
	else {
		CPlayer::WriteAll(0xFF, "dsd", 247, thisServerName + " Sin Event has ended.", 2);
		SinEvent::Active = false;
		SinEvent::Time = 0;
		int PlayerWinner = 0;
		int CurPts = 0;

		CIOCriticalSection::Enter((void*)0x004e2078);
		CIOCriticalSection::Enter((void*)0x004e2098);
		CLink::MoveTo((void*)0x004e200c, (int)0x004e2004);
		CIOCriticalSection::Leave((void*)0x004e2098);
		for (DWORD a = *(DWORD*)0x004E2004; a != 0x004E2004; a = *(DWORD*)a)
		{
			if ((void*)(a - 428))
			{
				IChar IPlayer((void*)(a - 428));
				if (IPlayer.IsOnline() && ((IPlayer.GetMapX() == SEMapX && IPlayer.GetMapY() == SEMapY) || (IPlayer.GetMapX() == SEMapX2 && IPlayer.GetMapY() == SEMapY2))) {
					int Pts = IPlayer.GetBuffValue(BuffNames::SinEventMobs) + IPlayer.GetBuffValue(BuffNames::SinEventPlayers);
					if (Pts > CurPts) {
						PlayerWinner = IPlayer.GetPID();
						CurPts = Pts;
					}

					if (Pts >= SEMinimumPoints)
						IPlayer.systemReward(SERewardLoser);
					
					IPlayer.CancelBuff(BuffNames::SinEventMobs);
					IPlayer.CancelBuff(BuffNames::SinEventPlayers);
					IPlayer.CloseScenario3_3Score();
					IPlayer.CancelBuff(104);
				}
			}
		}
		CIOCriticalSection::Leave((void*)0x004e2078);

		if (PlayerWinner) {
			TargetFind myTarget(0, 1, PlayerWinner);
			int Player = (int)myTarget.getTarget();
			IChar IPlayer((void*)Player);
			if (IPlayer.IsOnline()) {
				IPlayer.systemReward(SERewardWinner); 
				std::string msg = (std::string)IPlayer.GetName() + " has won the Sin Event with " + Int2String(CurPts) + " points.";
				CPlayer::WriteAll(0xFF, "dsd", 247, msg.c_str(), 2);
			}
		}
	}
}

void startGVG() {
	if (ScenarioRegistration.size() > 1)
	{
		if (!Scenario::Selection)
			GVGSelection();

		if (Scenario::Selection) {
			std::string msg = "Destructing Key Points started between " + Scenario::FirstGuild + " guild and " + Scenario::SecondGuild + " guild.";
			CPlayer::WriteAll(0xFF, "dsd", 247, msg.c_str(), 2);

			Scenario::Time = ScenarioTime;
			Scenario::RedScore = 0;
			Scenario::BlueScore = 0;
			Scenario::BlueTeamSeal = 0;
			Scenario::RedTeamSeal = 0;
			Scenario::BlueTeamTowerCount = 0;
			Scenario::RedTeamTowerCount = 0;

			ScenarioGuild.clear();
			RewardLimit.clear();
			DKRewardLimit.clear();
			Scenario::RegisterAmount = 0;
			Scenario::Active = true;
			Summon(0, ScenarioMap, 286786, 351034, 360, 1, 0, 0, 0, 0);
			Summon(0, ScenarioMap, 286239, 351036, 352, 1, 0, 0, 0, 0);
			Summon(0, ScenarioMap, 285936, 351318, 354, 1, 0, 0, 0, 0);
			Summon(0, ScenarioMap, 286589, 350285, 354, 1, 0, 0, 0, 0);
			Summon(0, ScenarioMap, 285808, 350665, 354, 1, 0, 0, 0, 0);
			Summon(0, ScenarioMap, 287677, 350530, 354, 1, 0, 0, 0, 0);
			Summon(0, ScenarioMap, 286479, 351338, 354, 1, 0, 0, 0, 0);
			Summon(0, ScenarioMap, 286999, 351590, 354, 1, 0, 0, 0, 0);
			Summon(0, ScenarioMap, 287353, 351038, 356, 1, 0, 0, 0, 0);
			Summon(0, ScenarioMap, 285935, 351547, 358, 1, 0, 0, 0, 0);
			Summon(0, ScenarioMap, 286590, 350494, 358, 1, 0, 0, 0, 0);
			Summon(0, ScenarioMap, 287677, 350756, 358, 1, 0, 0, 0, 0);
			Summon(0, ScenarioMap, 287777, 351408, 358, 1, 0, 0, 0, 0);
			Summon(0, ScenarioMap, 287113, 350741, 358, 1, 0, 0, 0, 0);
			Summon(0, ScenarioMap, 287001, 351787, 358, 1, 0, 0, 0, 0);
			remove("./Database/Destructing.db");
		}
	}
	else
		CPlayer::WriteAll(0xFF, "dsd", 247, "Enough guilds did not registered for Destructing Key Points.", 2);
}

void GVGSelection() {

	if (ScenarioGuild.size() > 1)
	{
		string line;

		ifstream fin;
		fin.open("./Database/Destructing.db");
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
		remove("./Database/Destructing.db");
		rename("./Database/temps.txt", "./Database/Destructing.db");
		
		vector< DKInfo >::iterator it = ScenarioGuild.begin();
		while (it != ScenarioGuild.end()) {

			if ((SystemBlacklist.count(2) && SystemBlacklist.find(2)->second.count(it->GID)) || it->GID == Protect32::GuildFirst || it->GID == Protect32::GuildSecond)
				it = ScenarioGuild.erase(it);
			else
				++it;
		}

		if (ScenarioGuild.size() > 1) {
			srand(time(0));
			std::random_shuffle(ScenarioGuild.begin(), ScenarioGuild.end());
			DKInfo dk = ScenarioGuild[0];
			DKInfo dk1 = ScenarioGuild[1];

			Scenario::GuildFirst = dk.GID;
			Scenario::FirstGuild = dk.Name;
			Scenario::GuildSecond = dk1.GID;
			Scenario::SecondGuild = dk1.Name;

			std::string Datko = "./Database/Destructing.db";
			std::fstream DGkLOG;
			DGkLOG.open(Datko, std::fstream::in | std::fstream::out | std::fstream::app);
			DGkLOG << "(chosen (GID " << Scenario::GuildFirst << ")(name '" << Scenario::FirstGuild << "'))" << std::endl;
			DGkLOG << "(chosen (GID " << Scenario::GuildSecond << ")(name '" << Scenario::SecondGuild << "'))" << std::endl;
			DGkLOG.close();

			std::string msg = "Destructing Key Points will start between " + Scenario::FirstGuild + " guild and " + Scenario::SecondGuild + " guild.";
			CPlayer::WriteAll(0xFF, "dsd", 247, msg.c_str(), 2);
			Scenario::Selection = true;
		}
		else {
			std::string msg = "Destructing Key selection could not have been made due to low amount of registered guilds.";
			CPlayer::WriteAll(0xFF, "dsd", 247, msg.c_str(), 2);
			Scenario::Selection = false;
		}
	}
}

void ProtectSelection() {
	if (ProtectLeaderList.size() > 1)
	{
		string line;

		ifstream fin;
		fin.open("./Database/ProtectLeader.db");
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
		remove("./Database/ProtectLeader.db");
		rename("./Database/temps.txt", "./Database/ProtectLeader.db");

		vector< int >::iterator it = ProtectLeaderList.begin();
		while (it != ProtectLeaderList.end()) {

			if ((SystemBlacklist.count(3) && SystemBlacklist.find(3)->second.count(*it)) || *it == Scenario::GuildFirst || *it == Scenario::GuildSecond)
				it = ProtectLeaderList.erase(it);
			else
				++it;
		}

		if (ProtectLeaderList.size() > 1) {
			srand(time(0));
			std::random_shuffle(ProtectLeaderList.begin(), ProtectLeaderList.end());
			Protect32::GuildFirst = ProtectLeaderList.front();
			ProtectLeaderList.erase(ProtectLeaderList.begin());
			std::random_shuffle(ProtectLeaderList.begin(), ProtectLeaderList.end());
			Protect32::GuildSecond = ProtectLeaderList.front();
			ProtectLeaderList.erase(ProtectLeaderList.begin());
			Protect32::FirstGuild = ProtectLeaderName.findValue(Protect32::GuildFirst);
			Protect32::SecondGuild = ProtectLeaderName.findValue(Protect32::GuildSecond);
			ProtectLeaderList.clear();
			ProtectLeaderName.clear();

			std::string Datko = "./Database/ProtectLeader.db";
			std::fstream DGkLOG;
			DGkLOG.open(Datko, std::fstream::in | std::fstream::out | std::fstream::app);
			DGkLOG << "(chosen (GID " << Protect32::GuildFirst << ")(name '" << Protect32::FirstGuild << "'))" << std::endl;
			DGkLOG << "(chosen (GID " << Protect32::GuildSecond << ")(name '" << Protect32::SecondGuild << "'))" << std::endl;
			DGkLOG.close();

			std::string msg = "Protecting Leader will start between " + Protect32::FirstGuild + " guild and " + Protect32::SecondGuild + " guild.";
			CPlayer::WriteAll(0xFF, "dsd", 247, msg.c_str(), 2);
			Protect32::Selection = true;
		}
		else {
			std::string msg = "Protecting Leader selection could not have been made due to low amount of registered guilds.";
			CPlayer::WriteAll(0xFF, "dsd", 247, msg.c_str(), 2);
			Protect32::Selection = false;
		}
	}
}

void startProtect() {
	if (!Protect32::GuildFirst || !Protect32::GuildSecond || Protect32::Selection == false)
		ProtectSelection();

	if (Protect32::Selection && Protect32::GuildFirst && Protect32::GuildSecond)
	{
		std::string msg = "Protecting Leader started between ";
		msg = msg + Protect32::FirstGuild;
		msg = msg + " guild and ";
		msg = msg + Protect32::SecondGuild;
		msg = msg + " guild.";
		CPlayer::WriteAll(0xFF, "dsd", 247, msg.c_str(), 2);
		Protect32::Prayer = 0;
		Protect32::RedScore = 0;
		Protect32::BlueScore = 0;
		Protect32::RedWin = 0;
		Protect32::BlueWin = 0;
		Protect32::Winner = 0;
		Protect32::RedPrayerTime = 0;
		Protect32::BluePrayerTime = 0;
		Protect32::Round = 1;
		Protect32::Time = 1260;
		RewardLimit.clear();
		remove("./Database/ProtectLeader.db");
		Protect32::BlueOpened = false;
		Protect32::RedOpened = false;
		GateSummon(369, PLMap, 308929, 287447, 65021);
		GateSummon(369, PLMap, 309966, 287452, 64006);
		Protect32::Active = true;
	}
	else {
		CPlayer::WriteAll(0xFF, "dsd", 247, "Enough guilds did not registered for Protecting Leader.", 2);
	}
}

void InsertWinnerDestructing(int GID, std::string Name) {
	std::string Datko = "./Winners/Destructing.db";
	std::fstream DGkLOG;
	DGkLOG.open(Datko, std::fstream::in | std::fstream::out | std::fstream::app);
	DGkLOG << "(Winner (Time " << Time::GetDate() + " " + Time::GetTime() << ")(GID " << GID << ")(name '" << Name << "'))" << std::endl;
	DGkLOG.close();
}

void InsertWinnerProtecting(int GID, std::string Name) {
	std::string Datko = "./Winners/ProtectLeader.db";
	std::fstream DGkLOG;
	DGkLOG.open(Datko, std::fstream::in | std::fstream::out | std::fstream::app);
	DGkLOG << "(Winner (Time " << Time::GetDate() + " " + Time::GetTime() << ")(GID " << GID << ")(name '" << Name << "'))" << std::endl;
	DGkLOG.close();
}

void __fastcall OnTimer(void *Value, void *edx, int Argument)
{
	int TimerNow = 0;
	int TickCount = 0;
	
	do{
		TickCount = GetTickCount() + 1000;

		CCalendar::OnTimer(Value, Argument);
		
		time_t v3 = time(0);
		struct tm *TimeNow = localtime(&v3);

		std::string TimeStr = Time::GetTime();
		LastTimeIndex = TimeIndex;

		TimeIndex = (TimeNow->tm_hour * 10000) + (TimeNow->tm_min * 100) + TimeNow->tm_sec;
		TimeDayIndex = TimeIndex + ((TimeNow->tm_wday + 1) * 1000000);

		if (EventTimer.count(TimeDayIndex))
			event1 = EventTimer.find(TimeDayIndex)->second.c_str();

		if (EventTimer.count(TimeIndex))
			event2 = EventTimer.find(TimeIndex)->second.c_str();

		if (EndTimer.count(TimeDayIndex))
			endevent1 = EndTimer.find(TimeDayIndex)->second.c_str();

		if (EndTimer.count(TimeIndex))
			endevent2 = EndTimer.find(TimeIndex)->second.c_str();

		if (TimeIndex != LastTimeIndex && SummonTimer.count(TimeIndex))
		{
			std::vector<CheckSummonTimer> summonTimer = SummonTimer.find(TimeIndex)->second;

			for (auto x = summonTimer.begin(); x != summonTimer.end(); x++) {
				if (x->Day == Time::GetDayName() || x->Day == "Daily")
				{
					std::string summonmsg = x->Msg;
					if (strlen(summonmsg.c_str())) {
						CPlayer::WriteAll(0xFF, "dsd", 247, summonmsg.c_str(), 2);
						CPlayer::WriteAll(15, "s", summonmsg.c_str());
					}

					for (int i = 0; i < x->Amount; i++)
						Summon(0, x->Map, x->X, x->Y, x->Index, 1, 1, 0, x->Disappear * 1000, 0);
				}
			}
		}

		if (!CaptureFlag::Active && isSystemTime("ProtectTheFlag")) {
			if (CaptureRegistration.size() > 1) {
				CPlayer::WriteAll(0xFF, "dsd", 247, thisServerName + " Capture the flag has been started.", 2);
				CaptureFlag::Time = CaptureDuration;
				CaptureFlag::RedScore = 0;
				CaptureFlag::BlueScore = 0;
				CaptureFlag::LastHit = 0;
				CaptureFlag::CurrentCapturers = 0;
				CaptureFlag::PlayerID = 0;
				Summon(0, CaptureMap, CPSummonX, CPSummonY, CaptureMonster, 1, 0, 0, 0, 0);
				Summon(0, CaptureMap, CPGateBX, CPGateBY, CPGate, 1, 0, 0, 0, 0);
				Summon(0, CaptureMap, CPGateRX, CPGateRY, CPGate, 1, 0, 0, 0, 0);
				CaptureFlag::Active = true;
			}
		}

		if (CaptureFlag::Active && CaptureFlag::PlayerID != 0) {
			IChar IPlayer((void*)CaptureFlag::PlayerID);
			if (!IPlayer.IsOnline()) {
				CPlayer::WriteInMap(CaptureMap, 0xFF, "dsd", 247, "Flag Monster has been respawned.", NOTICECOLOR_REDLONG);
				//Spawn(CaptureMonster, 1, CPSummonX, CPSummonY, CaptureMap);
				Summon(0, CaptureMap, CPSummonX, CPSummonY, CaptureMonster, 1, 0, 0, 0, 0);
				CaptureFlag::PlayerID = 0;
				CaptureFlag::CurrentCapturers = 0;
				CaptureFlag::MonsterOffset = 0;
			}
		}

		if (!TriangularBattle::CDActive && !TriangularBattle::Active && isSystemTime("TriangularBattle"))
			StartTriangularBattle();
	
		if (!Battlefield::Active && isSystemTime("Battlefield"))
			startBF(false);

		if (!Battlefield::Active && isSystemTime("GoodVsEvil"))
			startBF(true);

		if (Hell::Active) {
			if (Hell::Round == 1)
			{
				if (Hell::Time == 1800)
				{
					CPlayer::WriteInMap(HellMap, 0xFF, "ddddd", 242, 75, 255, 255, 255);
					//Spawn(841, 21, HellSummonX + CTools::Rate(1, 20), HellSummonY + CTools::Rate(1, 20), HellMap);

					for (int i = 0; i < 21; i++)
					{
						Summon(0, HellMap, HellSummonX + CTools::Rate(1, 20), HellSummonY + CTools::Rate(1, 20), 841, 1, 1, 0, 0, 0);
						//xSummon.Buff(168, 3600, 0);
					}
				}

				if (Hell::KillCount == 21)
				{
					CPlayer::WriteInMap(HellMap, 0xFF, "ddddd", 242, 86, 255, 255, 255);
					Hell::Round += 1;
					Hell::KillCount = 0;
					Hell::Delay = 5;
				}
			}

			if (Hell::Round == 2)
			{
				if (Hell::Delay == 3)
					CPlayer::WriteInMap(HellMap, 0xFF, "ddddd", 242, 87, 255, 255, 255);

				if (Hell::Delay == 1)
				{
					CPlayer::WriteInMap(HellMap, 0xFF, "ddddd", 242, 76, 255, 255, 255);
					//Spawn(842, 14, HellSummonX + CTools::Rate(1, 20), HellSummonY + CTools::Rate(1, 20), HellMap);
					for (int i = 0; i < 14; i++)
					{
						Summon(0, HellMap, HellSummonX + CTools::Rate(1, 20), HellSummonY + CTools::Rate(1, 20), 842, 1, 1, 0, 0, 0);
						//xSummon.Buff(168, 3600, 0);
					}
				}

				if (Hell::KillCount == 14)
				{
					CPlayer::WriteInMap(HellMap, 0xFF, "ddddd", 242, 86, 255, 255, 255);
					Hell::Round += 1;
					Hell::KillCount = 0;
					Hell::Delay = 5;
				}
			}

			if (Hell::Round == 3)
			{
				if (Hell::Delay == 3)
					CPlayer::WriteInMap(HellMap, 0xFF, "ddddd", 242, 87, 255, 255, 255);

				if (Hell::Delay == 1)
				{
					CPlayer::WriteInMap(HellMap, 0xFF, "ddddd", 242, 77, 255, 255, 255);
					//Spawn(843, 16, HellSummonX + CTools::Rate(1, 20), HellSummonY + CTools::Rate(1, 20), HellMap);

					for (int i = 0; i < 16; i++)
					{
						Summon(0, HellMap, HellSummonX + CTools::Rate(1, 20), HellSummonY + CTools::Rate(1, 20), 843, 1, 1, 0, 0, 0);
						//xSummon.Buff(168, 3600, 0);
					}
				}

				if (Hell::KillCount == 16)
				{
					CPlayer::WriteInMap(HellMap, 0xFF, "ddddd", 242, 86, 255, 255, 255);
					Hell::Round += 1;
					Hell::KillCount = 0;
					Hell::Delay = 5;
				}
			}

			if (Hell::Round == 4)
			{
				if (Hell::Delay == 3)
					CPlayer::WriteInMap(HellMap, 0xFF, "ddddd", 242, 87, 255, 255, 255);

				if (Hell::Delay == 1)
				{
					CPlayer::WriteInMap(HellMap, 0xFF, "ddddd", 242, 78, 255, 255, 255);
					//Spawn(845, 12, HellSummonX + CTools::Rate(1, 20), HellSummonY + CTools::Rate(1, 20), HellMap);

					for (int i = 0; i < 12; i++)
					{
						Summon(0, HellMap, HellSummonX + CTools::Rate(1, 20), HellSummonY + CTools::Rate(1, 20), 845, 1, 1, 0, 0, 0);
						//xSummon.Buff(168, 3600, 0);
					}
				}

				if (Hell::KillCount == 12)
				{
					CPlayer::WriteInMap(HellMap, 0xFF, "ddddd", 242, 86, 255, 255, 255);
					Hell::Round += 1;
					Hell::KillCount = 0;
					Hell::Delay = 5;
				}
			}

			if (Hell::Round == 5)
			{
				if (Hell::Delay == 3)
					CPlayer::WriteInMap(HellMap, 0xFF, "ddddd", 242, 87, 255, 255, 255);

				if (Hell::Delay == 1)
				{
					CPlayer::WriteInMap(HellMap, 0xFF, "ddddd", 242, 79, 255, 255, 255);
					//Spawn(846, 13, HellSummonX + CTools::Rate(1, 20), HellSummonY + CTools::Rate(1, 20), HellMap);

					for (int i = 0; i < 13; i++)
					{
						Summon(0, HellMap, HellSummonX + CTools::Rate(1, 20), HellSummonY + CTools::Rate(1, 20), 846, 1, 1, 0, 0, 0);
						//xSummon.Buff(168, 3600, 0);
					}
				}

				if (Hell::KillCount == 13)
				{
					CPlayer::WriteInMap(HellMap, 0xFF, "ddddd", 242, 86, 255, 255, 255);
					Hell::Round += 1;
					Hell::KillCount = 0;
					Hell::Delay = 5;
				}
			}

			if (Hell::Round == 6)
			{
				if (Hell::Delay == 3)
					CPlayer::WriteInMap(HellMap, 0xFF, "ddddd", 242, 87, 255, 255, 255);

				if (Hell::Delay == 1)
				{
					CPlayer::WriteInMap(HellMap, 0xFF, "ddddd", 242, 80, 255, 255, 255);
					//Spawn(847, 18, HellSummonX + CTools::Rate(1, 20), HellSummonY + CTools::Rate(1, 20), HellMap);

					for (int i = 0; i < 18; i++)
					{
						Summon(0, HellMap, HellSummonX + CTools::Rate(1, 20), HellSummonY + CTools::Rate(1, 20), 847, 1, 1, 0, 0, 0);
						//xSummon.Buff(168, 3600, 0);
					}
				}

				if (Hell::KillCount == 18)
				{
					CPlayer::WriteInMap(HellMap, 0xFF, "ddddd", 242, 86, 255, 255, 255);
					Hell::Round += 1;
					Hell::KillCount = 0;
					Hell::Delay = 5;
				}
			}

			if (Hell::Round == 7)
			{
				if (Hell::Delay == 3)
					CPlayer::WriteInMap(HellMap, 0xFF, "ddddd", 242, 87, 255, 255, 255);

				if (Hell::Delay == 1)
				{
					CPlayer::WriteInMap(HellMap, 0xFF, "ddddd", 242, 81, 255, 255, 255);
					//Spawn(849, 15, HellSummonX + CTools::Rate(1, 20), HellSummonY + CTools::Rate(1, 20), HellMap);

					for (int i = 0; i < 15; i++)
					{
						Summon(0, HellMap, HellSummonX + CTools::Rate(1, 20), HellSummonY + CTools::Rate(1, 20), 849, 1, 1, 0, 0, 0);
						//xSummon.Buff(168, 3600, 0);
					}
				}

				if (Hell::KillCount == 15)
				{
					CPlayer::WriteInMap(HellMap, 0xFF, "ddddd", 242, 86, 255, 255, 255);
					Hell::Round += 1;
					Hell::KillCount = 0;
					Hell::Delay = 5;
				}
			}

			if (Hell::Round == 8)
			{
				if (Hell::Delay == 3)
					CPlayer::WriteInMap(HellMap, 0xFF, "ddddd", 242, 87, 255, 255, 255);

				if (Hell::Delay == 1)
				{
					CPlayer::WriteInMap(HellMap, 0xFF, "ddddd", 242, 82, 255, 255, 255);
					//Spawn(850, 17, HellSummonX + CTools::Rate(1, 20), HellSummonY + CTools::Rate(1, 20), HellMap);

					for (int i = 0; i < 17; i++)
					{
						Summon(0, HellMap, HellSummonX + CTools::Rate(1, 20), HellSummonY + CTools::Rate(1, 20), 850, 1, 1, 0, 0, 0);
						//xSummon.Buff(168, 3600, 0);
					}
				}

				if (Hell::KillCount == 17)
				{
					CPlayer::WriteInMap(HellMap, 0xFF, "ddddd", 242, 86, 255, 255, 255);
					Hell::Round += 1;
					Hell::KillCount = 0;
					Hell::Delay = 5;
				}
			}

			if (Hell::Round == 9)
			{
				if (Hell::Delay == 3)
					CPlayer::WriteInMap(HellMap, 0xFF, "ddddd", 242, 87, 255, 255, 255);

				if (Hell::Delay == 1)
				{
					CPlayer::WriteInMap(HellMap, 0xFF, "ddddd", 242, 83, 255, 255, 255);
					//Spawn(852, 12, HellSummonX + CTools::Rate(1, 20), HellSummonY + CTools::Rate(1, 20), HellMap);

					for (int i = 0; i < 12; i++)
					{
						Summon(0, HellMap, HellSummonX + CTools::Rate(1, 20), HellSummonY + CTools::Rate(1, 20), 852, 1, 1, 0, 0, 0);
						//xSummon.Buff(168, 3600, 0);
					}
				}

				if (Hell::KillCount == 12)
				{
					CPlayer::WriteInMap(HellMap, 0xFF, "ddddd", 242, 86, 255, 255, 255);
					Hell::Round += 1;
					Hell::KillCount = 0;
					Hell::Delay = 5;
				}
			}

			if (Hell::Round == 10)
			{
				if (Hell::Delay == 3)
					CPlayer::WriteInMap(HellMap, 0xFF, "ddddd", 242, 87, 255, 255, 255);

				if (Hell::Delay == 1)
				{
					CPlayer::WriteInMap(HellMap, 0xFF, "ddddd", 242, 84, 255, 255, 255);
					//Spawn(851, 18, HellSummonX + CTools::Rate(1, 20), HellSummonY + CTools::Rate(1, 20), HellMap);

					for (int i = 0; i < 18; i++)
					{
						Summon(0, HellMap, HellSummonX + CTools::Rate(1, 20), HellSummonY + CTools::Rate(1, 20), 851, 1, 1, 0, 0, 0);
						//xSummon.Buff(168, 3600, 0);
					}
				}

				if (Hell::KillCount == 18)
				{
					CPlayer::WriteInMap(HellMap, 0xFF, "ddddd", 242, 86, 255, 255, 255);
					Hell::Round += 1;
					Hell::KillCount = 0;
					Hell::Delay = 5;
				}
			}

			if (Hell::Round == 11)
			{
				if (Hell::Delay == 3)
					CPlayer::WriteInMap(HellMap, 0xFF, "ddddd", 242, 87, 255, 255, 255);

				if (Hell::Delay == 1)
				{
					CPlayer::WriteInMap(HellMap, 0xFF, "ddddd", 242, 85, 255, 255, 255);
					//Spawn(667, 1, HellSummonX + CTools::Rate(1, 20), HellSummonY + CTools::Rate(1, 20), HellMap);

					Summon(0, HellMap, HellSummonX, HellSummonY, 667, 1, 1, 0, 0, 0);
					//xSummon.Buff(168, 3600, 0);
				}

				if (Hell::KillCount == 1)
				{
					CPlayer::WriteInMap(HellMap, 0xFF, "ddddd", 242, 88, 255, 255, 255);
					Hell::Countdown = 15;
					Hell::KillCount = 0;
					//Hell::Active = false;
					//Hell::Time = 0;
				}
			}
		}

		if (TriangularBattle::Active || TriangularBattle::CDActive)
			TBOnTimer();

		if (Hell::Active == true && Hell::Time > 0)
			Hell::Time -= 1;

		if (Hell::Active == true && Hell::Delay > 0)
			Hell::Delay -= 1;

		if (Hell::Active == true && Hell::Size == 0) {
			CPlayer::WriteInMap(HellMap, 0xFF, "ddddd", 242, 90, 255, 255, 255);
			Hell::Active = false;
			Hell::Time = 0;
		}

		if (Hell::Active == true && Hell::Time == 0)
		{
			CPlayer::WriteInMap(HellMap, 0xFF, "ddddd", 242, 90, 255, 255, 255);
			Hell::Countdown = -1;
			Hell::Active = false;
			Hell::Time = 0;
		}

		if (Hell::Countdown > 0)
			Hell::Countdown--;

		if (Hell::Active == true && Hell::Countdown == 0) {
			Hell::Lapse = GetTickCount() + 5000;
			Hell::Active = false;
			Hell::Time = 0;
			Hell::Countdown = -1;
		}

		if (isSystemTime("Emok"))
		{
			NailKill = 0;
			Summon(0, EmokMap, 330747, 266095, 384, 1, 0, 0, 3600000, 0);
			Summon(0, EmokMap, 331444, 265375, 384, 1, 0, 0, 3600000, 0);
			Summon(0, EmokMap, 330222, 264165, 384, 1, 0, 0, 3600000, 0);
			Summon(0, EmokMap, 329511, 264894, 384, 1, 0, 0, 3600000, 0);
			CPlayer::WriteAll(0xFF, "dsd", 247, "Nail of Dragons have been appeared.", 2);
		}

		if (!SinEvent::Active && isSystemTime("SinEvent"))
			startSinEvent(SEDefaultTime);

		if (SinEvent::Active) {
			int TimeLeft = SinEvent::Time - (int)time(0);

			if (TimeLeft <= 0)
				startSinEvent(0);
			else
			{
				if ((TimeLeft % SESpawnCycle) == 0) {
					for (auto x = SinSpawners.begin(); x != SinSpawners.end(); x++) {
						for(int i=0;i<x->Amount;i++)
							Summon(0, 0, x->X, x->Y, x->Index, 1, 0, 0, TimeLeft * 1000, 0);
					}
					CPlayer::WriteAll(0xFF, "dsd", 247, "Sin Event monsters have re-appeared.", 2);
				}
			}
		}

		if (!Bandits::Active && isSystemTime("Bandits"))
		{
			if (BanditsRegisteration.size() > 0)
			{
				Bandits::RegisterAmount = 0;
				Bandits::Active = true;
				Bandits::Time = (int)time(0) + BanditsTime;
				CPlayer::WriteAll(0xFF, "dsd", 247, "Bandits System has started.", 2);
			}
			else {
				CPlayer::WriteAll(0xFF, "dsd", 247, "Not enough players registered for Bandits System.", 2);

			}
		}

		if (Bandits::Active && isEndSystemTime("Bandits"))
		{
				Bandits::RegisterAmount = 0;
				Bandits::Active = false;
				Bandits::Time = 0;
				BanditsRegisteration.clear();
				CPlayer::WriteAll(0xFF, "dsd", 247, "Bandits System has ended.", 2);
		}

		if (Bandits::Active)
		{
			DWORD Check = Bandits::Time - (int)time(0);

			if (Check < 2){
				Bandits::RegisterAmount = 0;
				Bandits::Active = false;
				Bandits::Time = 0;
				BanditsRegisteration.clear();
				CPlayer::WriteAll(0xFF, "dsd", 247, "Bandits System has ended.", 2);
			}
		}

		if (isSystemTime("HouseRewards")){
			AddHouseReward(HouseRewardTime);
			CPlayer::WriteAll(0xFF, "dsd", 247, "Houses Points have resetted | Rewards sent to Winners.", 2);
		}

		if (!F10::Active && isSystemTime("F10"))
		{
			if (F10Registration.size() > 0)
			{
				F10::CheiosSkillDelay = 0;
				F10::DunamicSkillDelay = 0;
				F10::Dunamic = 0;
				F10::Cheios = 0;
				F10::KillCount = 0;
				F10::RegisterAmount = 0;
				F10::Ilyer = 0;
				F10::Active = true;
				CPlayer::WriteAll(0xFF, "dsd", 247, "Ilyer Company System started.", 2);
				Summon(0, 21, 117339, 36841, 702, 1, 0, 3700000, 3700000, 0);
			}
		}

		if (!Maut::Active && isSystemTime("Mautareta"))
		{
			if (!MautRegistration.empty())
			{
				Maut::Timer = (int)time(0) + 1799;
				Maut::Boss = 0;
				Maut::KillCount = 0;
				Maut::RegisterAmount = 0;
				Maut::Active = true;
				CPlayer::WriteAll(0xFF, "dsd", 247, "Mautareta System started.", 2);
			}
		}
			
		if (Maut::Active) {
			DWORD Check = Maut::Timer - (int)time(0);

			if (Check < 1780 && !Maut::Boss)
			{
				Maut::Boss = Summon(0, MautMap, MautSpawnX, MautSpawnY, 670, 1, 0, 0, Check * 1000, 0);
				CPlayer::WriteInMap(MautMap, 0xFF, "ds", 234, "Mautareta has appeared!");
			}

			if (Check == 1730)
			{
				for (int x = 0; x < 24; x++)
				{
					Summon(0, MautMap, MautSpawnX + CTools::Rate(-300, 400), MautSpawnY + CTools::Rate(-300, 400), 671, 1, 1, 0, 0, 0);
				}
				for (int x = 0; x < 16; x++)
				{
					Summon(0, MautMap, MautSpawnX + CTools::Rate(-300, 400), MautSpawnY + CTools::Rate(-300, 400), 672, 1, 1, 0, 0, 0);
				}
			}

			if (Check < 1730 && (Check % 30) == 0)
			{
				for (int x = 0; x < 22; x++)
				{
					Summon(0, MautMap, MautSpawnX + CTools::Rate(-1000, 1500), MautSpawnY + CTools::Rate(-1000, 1500), 671, 1, 1, 0, 120000, 0);
				}
				for (int x = 0; x < 18; x++)
				{
					Summon(0, MautMap, MautSpawnX + CTools::Rate(-1000, 1500), MautSpawnY + CTools::Rate(-1000, 1500), 672, 1, 1, 0, 120000, 0);
				}
			}

			if (Check < 1730 && (Check % 45) == 0)
			{
				for (int x = 0; x < 14; x++)
					Summon(0, MautMap, MautSpawnX + CTools::Rate(-1000, 1000), MautSpawnY + CTools::Rate(-1000, 1000), 671, 1, 1, 0, 60000, 0);
			}
		}

		if (!BossEXP::Active && isSystemTime("BossEXP"))
		{
			if (!BossEXPRegistration.empty())
			{
				BossEXP::Timer = (int)time(0) + BossEXPTime;
				BossEXP::Boss = 0;
				BossEXP::KillCount = 0;
				BossEXP::RegisterAmount = 0;
				BossEXP::Active = true;
			}
		}

		if (BossEXP::Active) {
			int Check = BossEXP::Timer - (int)time(0);

			if (Check <= (BossEXPTime - BossEXPPrepare) && !BossEXP::Boss)
			{
				BossEXP::Boss = Summon(0, BossEXPMap, BossEXPMX, BossEXPMY, BossEXPMob, 1, 0, 0, Check * 1000, 0);
				std::string SysName(BossEXPName);
				std::string Notice = SysName + " has begun!";
				CPlayer::WriteInMap(BossEXPMap, 0xFF, "ds", 234, Notice.c_str());
			}

			if (BossEXPMsgs.count(Check)) {
				BossEXPMsg msgCheck = BossEXPMsgs.find(Check)->second;
				if (msgCheck.Index && msgCheck.Amount) {
					for (int i = 0; i < msgCheck.Amount; i++)
						Summon(0, BossEXPMap, msgCheck.X, msgCheck.Y, msgCheck.Index, 1, 0, 0, 0, 0);
				}

				if(!msgCheck.message.empty())
					CPlayer::WriteInMap(BossEXPMap, 0xFF, "dsd", 247, msgCheck.message.c_str(), 1);
			}
		}

		if (!SufferingValley::Active && isSystemTime("SufferingValley"))
			startSV();

		if (!SufferingValley::Selection && isSystemTime("SVSelection"))
			SVSelection();

		if (SufferingValley::Active)
			SVOnTimer();

		if (Battlefield::Active == true && (Battlefield::Time == 1500 || Battlefield::Time == 1200 || Battlefield::Time == 1000 || Battlefield::Time == 600 || Battlefield::Time == 300))
		{
			TargetFind myTarget(1, 0, Battlefield::RedStoneID);
			void *MonsterRed = myTarget.getTarget();

			TargetFind myTarget2(1, 0, Battlefield::BlueStoneID);
			void *MonsterBlue = myTarget2.getTarget();

			IChar M1(MonsterBlue);
			IChar m1(MonsterRed);

			if (!M1.IsValid())
			{
				IChar N1((void*)Summon(0, BFMap, Battlefield::GoodVsEvil ? BlueStoneXG : BlueStoneX, Battlefield::GoodVsEvil ? BlueStoneYG : BlueStoneY, 445, 1, 0, 0, 0, 0));
				Battlefield::BlueStoneID = N1.GetID();
			}

			if (!m1.IsValid())
			{
				IChar n1((void*)Summon(0, BFMap, Battlefield::GoodVsEvil ? RedStoneXG : RedStoneX, Battlefield::GoodVsEvil ? RedStoneYG : RedStoneY, 448, 1, 0, 0, 0, 0));
				Battlefield::BlueStoneID = n1.GetID();
			}

			std::string msg = std::string(BFName) + " team stones have been re-spawned.";
			CPlayer::WriteInMap(BFMap, 0xFF, "dsd", 247, msg.c_str(), 2);
		}

		if (!Scenario::Active && !Scenario::Selection && isSystemTime("DKSelection"))
			GVGSelection();

		if (!Scenario::Active && isSystemTime("DestructingKeys"))
			startGVG();

		if (Raid::Active) {
			if (Raid::Round == 0) {
				if (Raid::Time == 313)
					CPlayer::WriteInMap(RaidMap, 0xFF, "dsd", 247, "I have a feeling that you little slaves came here for nothing.", 1);
				if (Raid::Time == 310)
					CPlayer::WriteInMap(RaidMap, 0xFF, "dsd", 247, "In this " + thisServerName + " world, nobody has ever come close to breaking our kingdom.", 1);
				if (Raid::Time == 307)
					CPlayer::WriteInMap(RaidMap, 0xFF, "dsd", 247, "Let me laugh. First, show me what you can do against with my warriors.", 1);
				if (Raid::Time == 304)
					CPlayer::WriteInMap(RaidMap, 0xFF, "dsd", 247, "If any of you had made it as far as the last round, I will show you how it's done.", 1);
				if (Raid::Time == 301) {
					RewardLimit.clear();
					RaidSystem.clear();
					Summon(0, RaidMap, 233580, 235710, Raid1, 1, 0, 0, 0, 0);
					CPlayer::WriteInMap(RaidMap, 0xFF, "dd", 233, Raid::Time);
					Raid::Round = 1;
				}
			}

			if (Raid::Round == 2) {
				if (Raid::Time == 486)
					CPlayer::WriteInMap(RaidMap, 0xFF, "dsd", 247, "Here comes one of my other little boys.", 1);
				if (Raid::Time == 483)
					CPlayer::WriteInMap(RaidMap, 0xFF, "dsd", 247, "He isn't as easy as you think.", 1);
				if (Raid::Time == 481) {
					RewardLimit.clear();
					Summon(0, RaidMap, 232611, 231607, Raid2, 1, 0, 0, 0, 0);
					CPlayer::WriteInMap(RaidMap, 0xFF, "dd", 233, Raid::Time);
				}
			}
			if (Raid::Round == 3) {

				if (Raid::Time == 665)
					CPlayer::WriteInMap(RaidMap, 0xFF, "dsd", 247, "This one will be tough to beat.", 1);
				if (Raid::Time == 662)
					CPlayer::WriteInMap(RaidMap, 0xFF, "dsd", 247, "You will suffer by the end.", 1);
				if (Raid::Time == 661) {
					RewardLimit.clear();
					Summon(0, RaidMap, 235169, 235257, Raid3, 1, 0, 0, 0, 0);
					CPlayer::WriteInMap(RaidMap, 0xFF, "dd", 233, Raid::Time);
				}
			}
			if (Raid::Round == 4) {

				if (Raid::Time == 906)
					CPlayer::WriteInMap(RaidMap, 0xFF, "dsd", 247, "Do you think you're ready for my next companion?", 1);
				if (Raid::Time == 903)
					CPlayer::WriteInMap(RaidMap, 0xFF, "dsd", 247, "He will make you regret your decision.", 1);
				if (Raid::Time == 901) {
					RewardLimit.clear();
					Summon(0, RaidMap, 234088, 231087, Raid4, 1, 0, 0, 0, 0);
					CPlayer::WriteInMap(RaidMap, 0xFF, "dd", 233, Raid::Time);
				}
			}

			if (Raid::Round == 5) {

				if (Raid::Time == 1206)
					CPlayer::WriteInMap(RaidMap, 0xFF, "dsd", 247, "NIRVANA!!!", 1);
				if (Raid::Time == 1203)
					CPlayer::WriteInMap(RaidMap, 0xFF, "dsd", 247, "You must be proud for making it to the 5th round... But your journey ends here!", 1);
				if (Raid::Time == 1201) {
					RewardLimit.clear();
					Summon(0, RaidMap, 236452, 233297, Raid5, 1, 0, 0, 0, 0);
					CPlayer::WriteInMap(RaidMap, 0xFF, "dd", 233, Raid::Time);
				}
			}

			if (Raid::Round == 6) {

				if (Raid::Time == 1446)
					CPlayer::WriteInMap(RaidMap, 0xFF, "dsd", 247, "YOU WILL PAY!!!", 1);
				if (Raid::Time == 1443)
					CPlayer::WriteInMap(RaidMap, 0xFF, "dsd", 247, "THIS HAS TO END RIGHT NOW!", 1);
				if (Raid::Time == 1441) {
					RewardLimit.clear();
					Summon(0, RaidMap, 231772, 234875, Raid6, 1, 0, 0, 0, 0);
					CPlayer::WriteInMap(RaidMap, 0xFF, "dd", 233, Raid::Time);
				}
			}

			if (Raid::Round == 7) {
				if (Raid::Time == 1626)
					CPlayer::WriteInMap(RaidMap, 0xFF, "dsd", 247, "WHAT IS GOING ON!!!", 1);
				if (Raid::Time == 1623)
					CPlayer::WriteInMap(RaidMap, 0xFF, "dsd", 247, "NIRVANA!! YOUR TIME STOPS RIGHT NOW!", 1);
				if (Raid::Time == 1621) {
					RewardLimit.clear();
					Summon(0, RaidMap, 231772, 234875, Raid7, 1, 0, 0, 0, 0);
					CPlayer::WriteInMap(RaidMap, 0xFF, "dd", 233, Raid::Time);
				}
			}

			if (Raid::Round == 8) {
				if (Raid::Time == 1686)
					CPlayer::WriteInMap(RaidMap, 0xFF, "dsd", 247, "I NEED DOGGEBI LORD'S HELP!!!", 1);
				if (Raid::Time == 1683)
					CPlayer::WriteInMap(RaidMap, 0xFF, "dsd", 247, "NIRVANA!! WHAT IS THE SECRET OF YOUR POWER?!", 1);
				if (Raid::Time == 1681) {
					RewardLimit.clear();
					Summon(0, RaidMap, 236452, 233297, Raid8, 1, 0, 0, 0, 0);
					CPlayer::WriteInMap(RaidMap, 0xFF, "dd", 233, Raid::Time);
				}
			}

			if (Raid::Round == 9) {
				if (Raid::Time == 1806)
					CPlayer::WriteInMap(RaidMap, 0xFF, "dsd", 247, "ITS TIME TO FACE THE " + thisServerName + " BEAST!!!", 1);
				if (Raid::Time == 1803)
					CPlayer::WriteInMap(RaidMap, 0xFF, "dsd", 247, "Let me show all of you how it is done.", 1);
				if (Raid::Time == 1801) {
					RewardLimit.clear();
					Summon(0, RaidMap, 231772, 234875, Raid9, 1, 0, 0, 0, 0);
					CPlayer::WriteInMap(RaidMap, 0xFF, "dd", 233, Raid::Time);
				}
			}

			if (Raid::Round == 10) {
				if (Raid::Time == 1806)
					CPlayer::WriteInMap(RaidMap, 0xFF, "dsd", 247, "Im getting tired playing with you little miserable warriors!!!", 1);
				if (Raid::Time == 1803)
					CPlayer::WriteInMap(RaidMap, 0xFF, "dsd", 247, "I'm about to drop all whats left in my energy on everyone of you!", 1);
				if (Raid::Time == 1801) {
					RewardLimit.clear();
					Summon(0, RaidMap, 231772, 234875, Raid9, 1, 0, 0, 0, 0);
					CPlayer::WriteInMap(RaidMap, 0xFF, "dd", 233, Raid::Time);
					Raid::Round = 11;
				}
			}
		}

		if (!Hunting::Active && isSystemTime("Hunting"))
		{
			std::string GetGuildName;

			if (HuntingID)
			{
				Hunting::Guild = HuntingID;
				GetGuildName = HuntingName;
			}
			else {
				Hunting::Guild = 0;
			}

			if (Hunting::Guild > 0 && !GetGuildName.empty())
			{
				Hunting::Active = true;
				std::string msg = "Hunting System started for " + GetGuildName + " guild.";
				CPlayer::WriteAll(0xFF, "dsd", 247, msg.c_str(), 2);
				int Mob = Summon(0, HGMapI, HGXC, HGYC, HGMobI, 1, 0, 0, 3600000, 0);
				Hunting::Time = HTime;
				Hunting::Monster = (void*)Mob;
			}
		}

		WorldCupTimer();

		if (F10::ShowTime > 0)
			F10::ShowTime--;

		if (BossHunting::Time > 0)
			BossHunting::Time--;

		if (Raid::Time > 0)
			Raid::Time--;

		if (Hunting::Time > 0)
			Hunting::Time--;

		if (Protect32::Time > 0)
			Protect32::Time--;

		if (Hunting::Active == true && Hunting::Time == 0) {
			Hunting::Active = false;
			Hunting::Guild = 0;
			Hunting::Monster = 0;
			Hunting::Time = 0;
			if (CWGID)
				HuntingAddAll(CWGID, CWGuildName);
		}

		if (Protect32::Active == true && Protect32::Time == 0)
		{
			if (Protect32::RedScore > Protect32::BlueScore)
				Protect32::RedWin += 1;

			if (Protect32::BlueScore > Protect32::RedScore)
				Protect32::BlueWin += 1;

			if (Protect32::RedWin < 2 && Protect32::BlueWin < 2)
			{
				Protect32::Round += 1;
				Protect32::Prayer = 0;
				Protect32::RedScore = 0;
				Protect32::BlueScore = 0;

				if (Protect32::Round < 4) {
					Protect32::BlueOpened = false;
					Protect32::RedOpened = false;
					Protect32::Time = 1260;
				}
			}

			if (Protect32::Active == true && Protect32::RedWin >= 2)
			{
				Protect32::Winner = Protect32::GuildSecond;
				std::string msg = Protect32::SecondGuild + " won the Protecting Leader.";
				CPlayer::WriteAll(0xFF, "dsd", 247, msg.c_str(), 2);
				CPlayer::WriteAll(0xFF, "dsd", 247, Protect32::SecondGuild + " is now the next hunting Guild of " + (std::string)ServerName + " !", 2);
				HuntingAddAll(Protect32::GuildSecond, Protect32::SecondGuild);
				InsertWinnerProtecting(Protect32::GuildSecond, Protect32::SecondGuild);
				Protect32::Active = false;
				Protect32::Selection = false;
				Protect32::GuildSecond = 0;
				Protect32::GuildFirst = 0;
			}

			if (Protect32::Active == true && Protect32::BlueWin >= 2)
			{
				Protect32::Winner = Protect32::GuildFirst;
				std::string msg = Protect32::FirstGuild + " won the Protecting Leader.";
				CPlayer::WriteAll(0xFF, "dsd", 247, msg.c_str(), 2);
				CPlayer::WriteAll(0xFF, "dsd", 247, Protect32::FirstGuild + " is now the next hunting Guild of " + thisServerName + "!", 2);

				HuntingAddAll(Protect32::GuildFirst, Protect32::FirstGuild);
				InsertWinnerProtecting(Protect32::GuildFirst, Protect32::FirstGuild);
				Protect32::Active = false;
				Protect32::Selection = false;
				Protect32::GuildSecond = 0;
				Protect32::GuildFirst = 0;
			}

			if (Protect32::Active == true && Protect32::Round > 3)
			{
				if (Protect32::Active == true && Protect32::BlueWin > Protect32::RedWin)
				{
					Protect32::Winner = Protect32::GuildFirst;
					std::string msg = Protect32::FirstGuild + " won the Protecting Leader.";
					CPlayer::WriteAll(0xFF, "dsd", 247, msg.c_str(), 2);
					CPlayer::WriteAll(0xFF, "dsd", 247, Protect32::FirstGuild + " is now the next hunting Guild of " + thisServerName + "!", 2);

					HuntingAddAll(Protect32::GuildFirst, Protect32::FirstGuild);
					InsertWinnerProtecting(Protect32::GuildFirst, Protect32::FirstGuild);
					Protect32::Active = false;
					Protect32::Selection = false;
					Protect32::GuildSecond = 0;
					Protect32::GuildFirst = 0;
				}

				if (Protect32::Active == true && Protect32::RedWin > Protect32::BlueWin)
				{
					Protect32::Winner = Protect32::GuildSecond;
					std::string msg = Protect32::SecondGuild + " won the Protecting Leader.";
					CPlayer::WriteAll(0xFF, "dsd", 247, msg.c_str(), 2);
					CPlayer::WriteAll(0xFF, "dsd", 247, Protect32::SecondGuild + " is now the next hunting Guild of " + thisServerName + "!", 2);
					HuntingAddAll(Protect32::GuildSecond, Protect32::SecondGuild);
					InsertWinnerProtecting(Protect32::GuildSecond, Protect32::SecondGuild);

					Protect32::Active = false;
					Protect32::Selection = false;
					Protect32::GuildSecond = 0;
					Protect32::GuildFirst = 0;
				}

				if (Protect32::Active == true)
				{
					Protect32::Winner = 0;
					std::string msg = "Protecting Leader between " + Protect32::FirstGuild + " guild and " + Protect32::SecondGuild + " guild ended in a draw.";
					CPlayer::WriteAll(0xFF, "dsd", 247, msg.c_str(), 2);
					Protect32::Active = false;
					Protect32::Selection = false;
					Protect32::GuildSecond = 0;
					Protect32::GuildFirst = 0;
				}
			}
		}

		if (LastManStand::Time > 0)
			LastManStand::Time--;

		if (LastManStand::Notice == 1)
		{
			std::string msg = (std::string)LastManStand::WinnerName + " won the " + std::string(LMSName);
			CPlayer::WriteAll(0xFF, "dsd", 247, msg.c_str(), 2);
			LastManStand::Notice = 0;
		}

		if (NPCELeftTime && NPCELeftTime <= (int)time(0))
		{
			CPlayer::WriteAll(0xFF, "ds", 234, "[" + thisServerName + " Event] Event duration has been over!");
			NPCELeftTime = 0;
			CPlayer::SnowEvent(4);
			Snow = 4;
			CPlayer::WriteAll(68, "bI", 75, 16, 0);
			CPlayer::WriteAll(68, "bI", 75, 32, 0);
			CPlayer::WriteAll(68, "bI", 75, 64, 0);
			CPlayer::SetEventCode(0, 0);
		}

		if (!MidnightClean && TimeNow->tm_hour == 0) {
			DailyLoginLimits.clear();
			DNPCEDailyLimit = 0;

			CDBSocket::Write(114, "");

			CIOCriticalSection::Enter((void*)0x004e2078);
			CIOCriticalSection::Enter((void*)0x004e2098);
			CLink::MoveTo((void*)0x004e200c, (int)0x004e2004);
			CIOCriticalSection::Leave((void*)0x004e2098);
			for (DWORD a = *(DWORD*)0x004E2004; a != 0x004E2004; a = *(DWORD*)a)
			{
				if ((void*)(a - 428))
				{
					IChar IPlayer((void*)(a - 428));
					if (IPlayer.IsOnline()) {
						for (auto x = DailyQuest.begin(); x != DailyQuest.end(); x++) {
							if (x->second.Resetable == 1) {
								int Repeat = IPlayer.GetBuffValue((BuffNames::DailyRepeatBegin + x->first) % BuffNames::DailyRepeatEnd);
								if (Repeat > 0)
									IPlayer.UpdateBuff((BuffNames::DailyRepeatBegin + x->first) % BuffNames::DailyRepeatEnd, BuffNames::BuffTime, 0);
							}
						}

						CPlayer::Write(IPlayer.GetOffset(), 0xFF, "dsd", 247, "Resetable Daily Quests have been reseted", 2);

						if (DailyLogin)
							CDBSocket::Write(100, "dddddddss", 1, IPlayer.GetUID(), (int)IPlayer.GetOffset(), String2Int(Time::GetMonth()), String2Int(Time::GetDay()), DailyLoginLimit, IPCheck, IPlayer.GetIP().c_str(), IPlayer.GetHWID().c_str());

						if (IPlayer.IsBuff(156)) {
							int addtime = 0;

							int honor = IPlayer.GetProperty(PlayerProperty::HPx);

							if (honor >= 2790 && honor < 12090)
								addtime = 30;
							else if (honor >= 12090 && honor < 44640)
								addtime = 40;
							else if (honor >= 44640 && honor < 78740)
								addtime = 50;
							else if (honor >= 78740)
								addtime = 60;

							IPlayer.UpdateBuff(156, 3600 + (addtime * 60), 0);
							IPlayer.SetProperty(PlayerProperty::EmokDay, String2Int(Time::GetDay()));
						}
					}

				}
			}
			CIOCriticalSection::Leave((void*)0x004e2078);

			NPCEDailyLimit = 0;

			for (std::map<int, MSummonedConfig>::iterator iter = SummonedQuest.begin(); iter != SummonedQuest.end(); ++iter)
			{
				int k = iter->first;
				MSummonedConfig mConfig = iter->second;
				mConfig.Limit = 0;
				SummonedQuest.replaceInsert(k, mConfig);
			}

			MidnightClean = true;
		}

		if (MidnightClean && TimeNow->tm_hour == 1)
			MidnightClean = false;

		if (Scenario::RedScore > 999)
		{
			Scenario::RedScore = 999;
			Scenario::Time = 0;
		}

		if (Scenario::BlueScore > 999)
		{
			Scenario::BlueScore = 999;
			Scenario::Time = 0;
		}

		/*if (DuelTournament::RedScore > 9999999)
		DuelTournament::RedScore = 9999999;

		if (DuelTournament::BlueScore > 9999999)
		DuelTournament::BlueScore = 9999999;
		*/

		if (Scenario::Active == true && Scenario::Time > 0)
			Scenario::Time -= 1;

		if (AutoCenterNotices.count(TimeIndex))
		{
			std::vector<AutoNoticeConf> autoNotice = AutoCenterNotices.find(TimeIndex)->second;
			for (auto x = autoNotice.begin(); x != autoNotice.end(); x++) {
				if (x->Day == Time::GetDayName() || x->Day == "Daily") {
					std::string notice = x->Msg;
					if (!notice.empty()) {
						CPlayer::WriteAll(0xFF, "dsd", 247, notice.c_str(), 2);
						CPlayer::WriteAll(15, "s", notice.c_str());
					}
				}
			}
		}

		if (PartyTimer.count(TimeStr)) {
			std::vector<PartyReg> regs = PartyTimer.find(TimeStr)->second;
			for (int i = 0; i < regs.size(); i++) {
				PartyReg reg = regs[i];
				if (reg.Day == Time::GetDayName() || reg.Day == "Daily")
					managePartyRegistration(reg);
			}
		}

		if (!CurPartys.empty() || !PartyRegistrations.empty())
			PartyVsPartyOnTick();

		if (DuelTournament::Active)
			DuelTournamentTick();

		if (AutoNotices.size() > 0)
		{
			time_t diff = difftime(time(NULL), notices);
			const unsigned int SECS_PER_DAY = 60 * 60 * 24;
			const unsigned int SECS_PER_HR = 60 * 60;
			const unsigned int SECS_PER_MIN = 60;
			unsigned int days = diff / SECS_PER_DAY;
			diff = diff % SECS_PER_DAY;
			unsigned int hours = diff / SECS_PER_HR;
			diff = diff % SECS_PER_HR;
			unsigned int minutes = diff / SECS_PER_MIN;
			diff = diff % SECS_PER_MIN;
			unsigned int seconds = diff;
			float showAt;
			for (int l = 0; l < AutoNotices.size(); l++)
			{
				if (AutoNotices[l].minutes < 60 && AutoNotices[l].minutes > 0)
				{
					if (AutoNotices[l].minutes > 1)
					{
						showAt = 60 / static_cast<float>(AutoNotices[l].minutes);
					}
					else
					{
						showAt = 60 / (((AutoNotices[l].minutes) + (AutoNotices[l].minutes - (AutoNotices[l].minutes / 1.25))));
					}

					if (minutes != 0 && (minutes % AutoNotices[l].minutes) == 0 && seconds == ceil(showAt))
					{
						if (AutoNotices[l].msg.size() > 0)
						CPlayer::WriteAll(0xFE, "dds", 178, AutoNotices[l].color, AutoNotices[l].msg.c_str());
					}
				}
			}

			if (minutes != 0 && (minutes % 30) == 0 && seconds == 0)
			{
				CPlayer::WriteAll(15, "s", "This Server is Sponsored by KalTechSolutions - All rights reserved.");
			}
		}

		if (isMapsEvent("EventRegisterMap")) {
			std::string line = EventMapsTimer.count(TimeDayIndex) ? EventMapsTimer.find(TimeDayIndex)->second : EventMapsTimer.find(TimeIndex)->second;
			int Quest = 0;

			std::vector<std::string> arra = getExplode("{", "}", line);
			for (int i = 0; i<arra.size(); i++) {
				if (sscanf(arra[i].c_str(), "%d", &Quest) == 1) {
					if (EventMapRegister(Quest))
						break;
				}
			}
		}

		if (isMapsEvent("EventMap")) {
			std::string line = EventMapsTimer.count(TimeDayIndex) ? EventMapsTimer.find(TimeDayIndex)->second : EventMapsTimer.find(TimeIndex)->second;
			int Quest = 0;
			std::vector<std::string> arra = getExplode("{", "}", line);
			for (int i = 0; i<arra.size(); i++) {
				if (sscanf(arra[i].c_str(), "%d", &Quest) == 1) {
					if (EventMapStart(Quest))
						break;
				}
			}
		}

		if (RGBAutoNotice.count(TimeStr)) {
			std::vector<RGBNotice> notices = RGBAutoNotice.find(TimeStr)->second;
			for (auto x = notices.begin(); x != notices.end(); x++) {
				if (x->day == "Daily" || x->day == Time::GetDayName())
					CPlayer::WriteAll(0xFE, "dds", 178, x->Color, x->msg.c_str());
			}
		}

		if (!DamageEvent::Active && isSystemTime("Damage")) {
			CPlayer::WriteAll(0xFF, "ds", 234, thisServerName + " Damage Event has started.");
			DamageEvent::Active = true;
		}
		if (DamageEvent::Active && isEndSystemTime("Damage")) {
			CPlayer::WriteAll(0xFF, "ds", 234, thisServerName + " Damage Event has ended.");
			DamageEvent::Active = false;
		}

		if (!EggEvent::Active && isSystemTime("EGG")) {
			CPlayer::WriteAll(0xFF, "ds", 234, thisServerName + " Egg Event has started.");
			EggEvent::Active = true;
		}

		if (!PollTimer.empty() && !TimeNow->tm_sec) {
			int Index = ((TimeNow->tm_mon+1) * 1000000) + (TimeNow->tm_mday * 10000) + (TimeNow->tm_hour * 100) + TimeNow->tm_min;
			if (PollTimer.count(Index)) {
				Poll poll = PollTimer.find(Index)->second;
				if (Index == poll.Start) {
					std::string question = "New Poll : " + poll.Question + " is now available.";
					CPlayer::WriteAll(0xFF, "ds", 234, question.c_str());
				}
				else {
					std::string question = "Poll : " + poll.Question + " has now ended.";
					CPlayer::WriteAll(0xFF, "ds", 234, question.c_str());

					std::string Datko = "./Database/PollResult" + Int2String(poll.Quest) + ".db";
					std::fstream DGkLOG;
					DGkLOG.open(Datko, std::fstream::in | std::fstream::out | std::fstream::app);
					DGkLOG << "Question = " << poll.Question << std::endl;

					int TotalVotes = 0;
					for (int i = poll.FlagMin; i <= poll.FlagMax; i++) {
						int Value = PollVoteAmount.count((poll.Quest * 1000) + i) ? PollVoteAmount.findValue((poll.Quest * 1000) + i) : 0;
						DGkLOG << "(Result (Option " << Int2String(i) << ") (Amount " << Int2String(Value) << "))" << std::endl;
						TotalVotes += Value;
						PollVoteAmount.erase(((poll.Quest * 1000) + i));
					}

					DGkLOG << "TotalVotes = " << Int2String(TotalVotes) << std::endl;
					DGkLOG << "" << std::endl;
					DGkLOG.close();

					ifstream fPolls("./Database/Polls.db");
					if (fPolls.good()) {
						string line;
						ofstream temp("./Database/tempP.txt");

						while (getline(fPolls, line))
						{
							int Quest = 0, Vote = 0;
							char Hash[BUFSIZ];

							if (sscanf(line.c_str(), "(PollVote (Index %d) (Vote %d) (Hash '%[a-z | A-Z | 0-9/<>|.,~*;`:!^+%&=?_-£#$€]'))", &Quest, &Vote, &Hash) == 3)
							{
								if (Quest != poll.Quest)
									temp << line << endl;
								else if (PollVotes.count(Hash)) {
									std::set<int> votes = PollVotes.findValue(Hash);
									votes.erase(Quest);
									PollVotes[Hash] = votes;
								}
							}
						}

						temp.close();
						fPolls.close();
						remove("./Database/Polls.db");
						rename("./Database/tempP.txt", "./Database/Polls.db");
					}
				}
			}
		}

		if (EggEvent::Active && isEndSystemTime("EGG")) {
			CPlayer::WriteAll(0xFF, "ds", 234, thisServerName + " Egg Event has ended.");
			EggEvent::Active = false;
		}

		if (!Immortal::Active && isSystemTime("Immortal")) {
			CPlayer::WriteAll(0xFF, "ds", 234, thisServerName + " Immortal Event has started.");
			Immortal::Active = true;
		}

		if (Immortal::Active && isEndSystemTime("Immortal")) {
			CPlayer::WriteAll(0xFF, "ds", 234, thisServerName + " Immortal Event has ended.");
			Immortal::Active = false;
		}

		if (isSystemTime("EXP")) {
			CPlayer::WriteAll(0xFF, "ds", 234, thisServerName + " EXP Event has started.");
			CPlayer::SetEventCode(0, 1);
		}

		if (isEndSystemTime("EXP")) {
			CPlayer::WriteAll(0xFF, "ds", 234, thisServerName + " EXP Event has ended.");
			CPlayer::SetEventCode(0, 0);
		}

		if (TimeStr == "01:59:59" || TimeStr == "03:59:59" || TimeStr == "05:59:59" || TimeStr == "07:59:59" || TimeStr == "09:59:59" || TimeStr == "13:59:59" || TimeStr == "15:59:59" || TimeStr == "17:59:59" || TimeStr == "19:59:59" || TimeStr == "21:59:59" || TimeStr == "02:59:59" || TimeStr == "04:59:59" || TimeStr == "06:59:59" || TimeStr == "08:59:59" || TimeStr == "10:59:59" || TimeStr == "12:59:59" || TimeStr == "14:59:59" || TimeStr == "16:59:59" || TimeStr == "18:59:59" || TimeStr == "20:59:59" || TimeStr == "22:59:59" || TimeStr == "00:59:59") {
			CPlayer::WriteAll(0xFF, "dsd", 247, "This Server Is Sponsored By KalTechSolutions.", NOTICECOLOR_WHITE);
		}

		if (TimeNow->tm_wday == CWTCD && TimeNow->tm_hour < CWTCSH && (int)*(DWORD**)0x004E0964 != 1 && (int)*(DWORD**)0x004E0964 != 4)
			*(DWORD**)0x004E0964 = (DWORD*)1;

		if (TimeNow->tm_wday == CWTCD && TimeNow->tm_hour == (CWTCSH - 3) && !TimeNow->tm_min && !TimeNow->tm_sec && !CGuild::IsWarringPeriod()) {
			*(DWORD**)0x004E0964 = (DWORD*)1;
			CPlayer::WriteAll(0xFF, "dsd", 247, "Guilds can declare for castle war.", 2);
		}

		if (TimeStr == Int2String(CWTCSH - 1) + ":59:00" && TimeNow->tm_wday == CWTCD && !CGuild::IsWarringPeriod()) {
			*(DWORD**)0x004E0964 = (DWORD*)0;
			CPlayer::WriteAll(0xFF, "dsd", 247, "Declaring for castle war ended.", 2);
		}
		/* Castle War Declare End */

		/* Castle War Start */
		if (TimeStr == Int2String(CWTCSH) + ":00:05" && TimeNow->tm_wday == CWTCD && !CGuild::IsWarringPeriod()) {
			time_t MyTime = time(0);

			int SetCwTime = MyTime;
			SetCwTime += 3600;
			*(DWORD**)0x004E0964 = (DWORD*)4;
			WarBegin(SetCwTime);
			CPlayer::WriteAll(0xFF, "dsd", 247, thisServerName + " Castle War has started.", 5);
		}

		if (!HappyHour::Active && isSystemTime("HappyHour")) {
			HappyHour::Active = true;
		}

		if (HappyHour::Active && isEndSystemTime("HappyHour")) {
			HappyHour::Active = false;
		}

		/*if ((Time::GetTime() == "11:59:34" || Time::GetTime() == "23:59:40") && Lottery.size()>0) {
		CPlayer::WriteAll(0xFF, "dsd", 247, thisServerName+" Lottery draw has started.", 5);
		}

		if ((Time::GetTime() == "11:59:45" || Time::GetTime() == "23:59:50") && Lottery.size()>0) {
		CPlayer::WriteAll(0xFF, "dsd", 247, "Our next big winner is being picked...", 5);
		}

		if ((Time::GetTime() == "19:29:34") && XLottery.size()>0) {
		CPlayer::WriteAll(0xFF, "dsd", 247, "Daily Lotto draw has started.", 5);
		}

		if ((Time::GetTime() == "19:29:45") && XLottery.size()>0) {
		CPlayer::WriteAll(0xFF, "dsd", 247, "Today's Lotto winner is being picked...", 5);
		}*/

		if (InterlockedExchangeAdd(&PlayerLevelNotice, 0)) {
			IChar IPlayer((void*)InterlockedExchangeAdd(&PlayerLevelNotice, 0));
			if (IPlayer.IsOnline()) {
				string congratsMsg = "Dear " + (std::string)IPlayer.GetName() + ", Congratulations on reaching level " + Int2String(IPlayer.GetLevel());
				CPlayer::WriteAll(0xFF, "dsd", 247, congratsMsg.c_str(), NOTICECOLOR_WHITE);
			}
			InterlockedExchange(&PlayerLevelNotice, 0);
		}

		if (WarEndTime && WarEndTime <= (int)time(0)) {
			WarEndTime = 0;
			if(CWRLimit)
				RewardLimit.clear();
		}

		if ((GetTickCount() / 1000) % 30 == 0 && InterlockedExchangeAdd(&auctionItemsNum, 0) >= 1) {
			//auctionLock.Enter();
			ConcurrentMap<long, AuctionItem> cloneAuction = AuctionItems;
			//auctionLock.Leave();
			for (auto x = cloneAuction.begin(); x != cloneAuction.end(); x++)
			{
				if (x->second.BidRemain <= (int)time(0)) {
					if (x->second.RPID) {
						if (x->second.PID)
							CDBSocket::Write(104, "dddd", x->second.PID, 31, x->second.CurrentBid, 0);
						TargetFind myTarget(0, 1, x->second.RPID);
						int Player = (int)myTarget.getTarget();
						if (Player)
							CDBSocket::Write(30, "dbdbbssdbwbdds", -1, 0, -1, 0, 1, "Kal Online", x->second.Bidder.c_str(), x->first, x->second.SetGem, x->second.Index, x->second.Prefix, x->second.Amount, 0, "Congratulations, you have won the auction for this item.");
						else
							CDBSocket::Write(108, "dd", x->second.RPID, x->first);
					}
					else {
						TargetFind myTarget(0, 1, x->second.PID);
						int Player = (int)myTarget.getTarget();
						if (Player)
							CDBSocket::Write(30, "dbdbbssdbwbdds", -1, 0, -1, 0, 1, "Kal Online", x->second.Seller.c_str(), x->first, x->second.SetGem, x->second.Index, x->second.Prefix, x->second.Amount, 0, "Due to lack of time, your item has been returned from auction.");
						else
							CDBSocket::Write(108, "dd", x->second.PID, x->first);
					}
					CDBSocket::Write(107, "d", x->first);
					//auctionLock.Enter();
					AuctionItems.erase(x->first);
					//auctionLock.Leave();
					UpdateAuction();
					InterlockedIncrement(&auctionItemsNum);
				}
			}
		}

		if (CaptureFlag::Active && CaptureFlag::CurrentCapturers && (GetTickCount() / 1000) % CPSeconds == 0) {
			if (CaptureFlag::CurrentCapturers == BuffNames::CPBlue)
				CaptureFlag::BlueScore += CPPoints;
			if (CaptureFlag::CurrentCapturers == BuffNames::CPRed)
				CaptureFlag::RedScore += CPPoints;
		}

		if (isSystemTime("Lotto") && XLottery.size() > 0)
		{
			int Winner = XLottery.randomSelect();
			TargetFind myTarget(0, 1, Winner);
			int player = (int)myTarget.getTarget();

			while (!player && XLottery.size() > 0) {
				XLottery.erase(Winner);
				Winner = XLottery.randomSelect();
				TargetFind myTarget(0, 1, Winner);
				player = (int)myTarget.getTarget();
			}
			if (player) {
				IChar Target((void*)player);
				if (Target.IsOnline())
				{
					Target.systemReward(LottoReward);
					Target.BoxMsg("*************Congratulations***************\n\nYou have been selected as our Lotto's Winner!");

					std::string msg = (std::string) Target.GetName() + " is our new Lotto Winner, Congratulations!";
					CPlayer::WriteAll(0xFF, "ds", 234, msg.c_str());
					CPlayer::WriteAll(15, "s", msg.c_str());
				}
			}
			else {
				CPlayer::WriteAll(0xFF, "ds", 234, "Lotto Selection has ended. There is no winner.");
			}
			RewardLimit.clear();
			XLottery.clear();
		}

		if (LotteryCheck > 0 && isSystemTime("Lottery"))
		{
			int Winner = Lottery.randomSelect();
			TargetFind myTarget(0, 1, Winner);
			int player = (int)myTarget.getTarget();

			while (!player && Lottery.size() > 0) {
				Lottery.erase(Winner);
				Winner = Lottery.randomSelect();
				TargetFind myTarget(0, 1, Winner);
				player = (int)myTarget.getTarget();
			}
			if (player) {
				IChar Target((void*)player);

				if (LotteryCheck > 2000000000)
					LotteryCheck = 2000000000;

				if (Target.IsOnline())
				{
					if (GetInventorySize((int)Target.GetOffset(), 0) < 60)
						CItem::InsertItem((int)Target.Offset, 27, LotIndex, 0, LotteryCheck, -1);
					else {
						Target.GiveReward(LotIndex, 0, LotteryCheck, 0, 0, 0, 0, 0, 0, 0, 0, "Congratulations on winning the lottery!");
					}

					Target.BoxMsg("*************Congratulations***************\n\nYou have been selected as our Lottery Winner!");

					std::string msg = (std::string)Target.GetName() + " has won the " + thisServerName + " Public Lottery, Congratulations!";
					CPlayer::WriteAll(0xFF, "ds", 234, msg.c_str());
					CPlayer::WriteAll(15, "s", msg.c_str());
				}
			}
			else {
				CPlayer::WriteAll(0xFF, "ds", 234, "Lottery Selection has ended. There is no winner.");
			}
			RewardLimit.clear();
			LotteryCheck = 0;
			Lottery.clear();
		}

		if (!LastManStand::Active && isSystemTime("LastManStanding"))
		{
			if (LastManRegistration.size() > 1)
			{
				std::string msg = std::string(LMSName) + " started.";
				CPlayer::WriteAll(0xFF, "dsd", 247, msg.c_str(), 2);
				RewardLimit.clear();
				LastManStand::Active = true;
				LastManStand::Time = 3;
			}
		}

		if (DuelTournament::Active == false && isSystemTime("DuelTournament"))
			StartTournament();

		if (isSystemTime("DuelSelection")) {
			AllFights.clear();
			selectParticipants(1);
			CPlayer::WriteAll(0xFF, "ds", 234, "Duel tournament selection has been made.");
		}

		if (Protect32::Active == false && isSystemTime("ProtectingLeader"))
			startProtect();

		/*if (isSystemTime("Raid")) {
			if (RaidSystem.size() > 0 && Raid::Active == false) {
				CPlayer::WriteAll(0xFF, "dsd", 247, thisServerName + " Raid System has been started.", 2);
				Raid::Time = 315;
				Raid::Round = 0;
				Raid::Active = true;
			}
		}

		if (Raid::Active == true && Raid::Time == 0) {
			CPlayer::WriteInMap(RaidMap, 0xFF, "dsd", 247, "As I said, You failed to beat me, train harder, we will see tomorrow!", 1);
			CPlayer::WriteInMap(RaidMap, 0xFF, "ds", 236, "hell_time");
			Raid::Round = 0;
			Raid::Active = false;
		}
		*/

		if (Scenario::Active == true && Scenario::Time == 0)
		{
			ScenarioRegistration.clear();
			if (Scenario::RedScore > Scenario::BlueScore) {

				HuntingAddAll(Scenario::GuildFirst, Scenario::FirstGuild);

				CPlayer::WriteAll(0xFF, "dsd", 247, Scenario::FirstGuild + " won the Destructing Keys against " + Scenario::SecondGuild, 2);
				CPlayer::WriteAll(0xFF, "dsd", 247, Scenario::FirstGuild + " is now the next hunting Guild of " + thisServerName + "!", 2);

				InsertWinnerDestructing(Scenario::GuildFirst, Scenario::FirstGuild);
			}
			else if (Scenario::BlueScore > Scenario::RedScore) {

				HuntingAddAll(Scenario::GuildSecond, Scenario::SecondGuild);
				CPlayer::WriteAll(0xFF, "dsd", 247, Scenario::SecondGuild + " won the Destructing Keys against " + Scenario::FirstGuild, 2);
				CPlayer::WriteAll(0xFF, "dsd", 247, Scenario::SecondGuild + " is now the next hunting Guild of " + thisServerName + "!", 2);

				InsertWinnerDestructing(Scenario::GuildSecond, Scenario::SecondGuild);
			}
			Scenario::Active = false;
			Scenario::Selection = false;
			Scenario::Time = 0;
			Scenario::GuildFirst = 0;
			Scenario::GuildSecond = 0;
		}

		if (Battlefield::Active) {
			if (Battlefield::RedScore > 999)
			{
				Battlefield::RedScore = 999;
				Battlefield::Time = 0;
			}

			if (Battlefield::BlueScore > 999)
			{
				Battlefield::BlueScore = 999;
				Battlefield::Time = 0;
			}
		}

		if (CaptureFlag::Active) {
			if (CaptureFlag::RedScore > 1900)
			{
				CaptureFlag::RedScore = 1900;
				CaptureFlag::Time = 0;
			}

			if (CaptureFlag::BlueScore > 1900)
			{
				CaptureFlag::BlueScore = 1900;
				CaptureFlag::Time = 0;
			}
		}
		if (Battlefield::Active == true && Battlefield::Time > 0)
			Battlefield::Time -= 1;

		if (CaptureFlag::Active == true && CaptureFlag::Time > 0)
			CaptureFlag::Time -= 1;

		if (Battlefield::Active == true && Battlefield::Time == 0)
		{
			BattlefieldRegistration.clear();
			Battlefield::Active = false;
			Battlefield::Time = 0;
		}

		if (CaptureFlag::Active == true && (CaptureFlag::Time == 0 || CaptureFlag::BlueScore >= CPMaxScore || CaptureFlag::RedScore >= CPMaxScore))
		{
			CaptureRegistration.clear();
			CaptureFlag::Active = false;
			CaptureFlag::Time = 0;
		}

		if (DNPCELeftTime && DNPCELeftTime <= (int)time(0))
		{
			CPlayer::WriteAll(0xFF, "ds", 234, "[" + thisServerName + " Damage Event] Event duration has been over!");
			DNPCELeftTime = 0;
			DamageEvent::Active = false;
		}

		event1 = NULL;
		event2 = NULL;
		endevent1 = NULL;
		endevent2 = NULL;

		TimerNow = GetTickCount();
	}while (TickCount <= TimerNow);

	CIOObject::AddTimer((int)Value, TickCount - TimerNow, 0);
}