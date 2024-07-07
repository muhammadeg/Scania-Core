void StartTournament();
void EndTournament(int WinnerA);

std::map<int, std::map<int, std::vector<DuelRegistre>>> duelGroups;
struct curDFight
{
	int Time;
	int RedScore;
	int BlueScore;
	int Cooldown;
	curDFight() {
		Time = GetTickCount() + (DuelDuration * 1000) + 20000;
		RedScore = 0;
		BlueScore = 0;
		Cooldown = 20;
	}
};

std::map<int, curDFight> ArenasBusy;

int FightCount = 0;
int Tournament = 0;
bool finalFights = false;
bool Selection = false;
int nVictory = 0;

struct DuelFight
{
	int Player1;
	int Player2;
	DuelRegistre WinDefault;
	int Arena;
	DuelFight() {
		Player1 = 0;
		Player2 = 0;
		WinDefault = DuelRegistre();
		Arena = 0;
	}
	DuelFight(int NewPlayer1, int NewPlayer2, int NewArena, DuelRegistre Default) {
		Player1 = NewPlayer1;
		Player2 = NewPlayer2;
		WinDefault = Default;
		Arena = NewArena;
	}
};

typedef struct tagTournamentParty
{
	tagTournamentParty()
	{
		memset(this, 0, sizeof(*this));
	}
	char                    szName[6][21];
	BOOL                    bAbsence;
	BOOL                    bNULL;
	int                        nPosition;
	int                        nWinCnt;
}TOURNAMENT_PARTY;

#pragma pack(push, 1)
typedef struct tagShowdownPaticipateInfo
{
	char szName[20];

	char Level;
	char Class;
}SHOWDOWN_PATICIPATE_INFO;
#pragma pack(pop)

std::vector<DuelFight> curFights;
std::vector<DuelFight> nextFights;
std::map<int, std::vector<TOURNAMENT_PARTY>> AllFights;

int DuelArenas[][4] = {
	{ 219480,217083,219441,217316 },
	{ 280824,280811,283290,283278 }
};

int DuelPortBack[][4] = {
	{ 219584,217182,219495,217276 },
	{ 281404,281508,282725,282740 }
};

std::vector<DuelRegistre> cleanGroups(int Arena) {
	std::vector<DuelRegistre> Group = duelGroups.find(Tournament)->second.find(Arena)->second;

	vector< DuelRegistre >::iterator it = Group.begin();
	while (it != Group.end()) {

		if (it->nVictory < nVictory) 
			it = Group.erase(it);
		else
			++it;
	}

	return Group;
}

void ShowPotentialParticipants(IChar IPlayer, int Tournament) {
	if (!DuelRegistrationList.count(Tournament))
		return;

	std::vector<DuelRegistre> vect = DuelRegistrationList.find(Tournament)->second;
	int Size = vect.size();

	int Packetsize = 0;
	Interface <ITools> Tools;

	char* PlayerPack = new char[Size * sizeof SHOWDOWN_PATICIPATE_INFO];
	for (int i = 0; i < Size; i++) {
		DuelRegistre reg = vect[i];
		SHOWDOWN_PATICIPATE_INFO pt = tagShowdownPaticipateInfo();
		ZeroMemory(&pt, sizeof SHOWDOWN_PATICIPATE_INFO);

		for (int j = 0; j < reg.Name.size(); j++)
			pt.szName[j] = reg.Name[j];

		pt.Class = reg.Class;
		pt.Level = reg.Level;
		Tools->Compile(PlayerPack + Packetsize, "m", &pt, sizeof SHOWDOWN_PATICIPATE_INFO);
		Packetsize += sizeof SHOWDOWN_PATICIPATE_INFO;
	}

	CPlayer::Write(IPlayer.GetOffset(), 123, "ddbm", 6, 10+Tournament, Size, PlayerPack, Packetsize);
	delete[] PlayerPack;

}

void deathmatchRegister(int Tournament, std::string Name) {
	TOURNAMENT_PARTY pt;
	ZeroMemory(&pt, sizeof TOURNAMENT_PARTY);

	pt = tagTournamentParty();
	std::string Names = Name.size() < 21 ? " " + Name : Name;
	if (Names.size() < 21) {
		for (int i = 0; i < Names.size(); i++)
			pt.szName[0][i] = Names[i];

		pt.nWinCnt = 0;
		pt.bAbsence = false;
		pt.bNULL = false;
		pt.nPosition = 0;
		duelShowLock.Enter();
		AllFights[Tournament].push_back(pt);
		duelShowLock.Leave();
	}
}

void PrepareGroupFights(int Arena) {
	if (!duelGroups.count(Tournament) || !duelGroups.find(Tournament)->second.count(Arena))
		return;

	std::vector<DuelRegistre> Group = duelGroups.find(Tournament)->second.find(Arena)->second;

	int Size = Group.size();

	if (Size % 2)
		Size -= 1;

	if (!Size)
		return;

	int i = 0;
	while (i < (Size - 1)) {
		DuelRegistre P1 = Group[i];

		DuelRegistre P2 = Group[i+1];

		TargetFind myTarget1(0, 1, P1.PID);
		TargetFind myTarget2(0, 1, P2.PID);
		
		DuelRegistre Random = P2;
		if (CTools::Rate(0, 9) >= 5)
			Random = P1;

		if (Random.PID < 0)
			Random = (Random.PID == P1.PID) ? P2 : P1;

		nextFights.push_back(DuelFight((int)myTarget1.getTarget(), (int)myTarget2.getTarget(), Arena, Random));

		i += 2;
		FightCount++;
	}
}
void ClearTournament() {
	string line;

	ifstream fin;
	fin.open("./Database/Duel.db");
	ofstream temp;
	temp.open("./Database/temp.txt");

	while (getline(fin, line))
	{
		int Type = 0, PID = 0;
		if (sscanf(line.c_str(), "(registration (type %d)(PID %d)", &Type, &PID) == 2)
		{
			if (Type != Tournament)
				temp << line << endl;
			else
				DuelNames.erase(PID);
		}
	}

	temp.close();
	fin.close();
	remove("./Database/Duel.db");
	rename("./Database/temp.txt", "./Database/Duel.db");
}

std::string getTournamentName(int Type) {
	if (Type == 1)
		return "50 to 54";
	if (Type == 2)
		return "55 to 59";
	if (Type == 3)
		return "60 to 64";
	if (Type == 4)
		return "65 to 69";
	if (Type == 5)
		return "70 to 74";
	if (Type == 6)
		return "75 to 79";
	if (Type == 7)
		return "80 to 84";

	return "85+";
}

void selectParticipants(int T) {

	if (T > 8)
		return;

	if (!DuelRegistrationList.count(T))
		return selectParticipants(T + 1);

	std::vector<DuelRegistre> Groups = DuelRegistrationList.find(T)->second;

	/*int GetSize = Groups.size();
	for (int i = 0; i < GetSize; i++) {
	int PID = Groups.front().PID;
	Groups.erase(Groups.begin());
	TargetFind myTarget(0, 1, PID);
	IChar DuelPlayer(myTarget.getTarget());
	if (DuelPlayer.IsValid() && DuelPlayer.IsPVPValid()) {
	DuelRegistre reg;
	reg.PID = DuelPlayer.GetPID();
	reg.Name = (std::string)DuelPlayer.GetName();
	Groups.push_back(reg);
	}
	}*/

	int Size = Groups.size();

	if (Size < 8)
		return selectParticipants(T + 1);

	duelLock.Enter(); 
	srand(time(0));
	std::random_shuffle(Groups.begin(), Groups.end());

	for (int i = 0; i < 32; i++) {
		DuelRegistre registration;
		if (Size > i) {
			registration = Groups.front();
			deathmatchRegister(T, registration.Name);
			Groups.erase(Groups.begin());
		}
		else
		{
			registration = DuelRegistre();
			registration.Name = "NULL" + Int2String(T) + Int2String(i);
			registration.PID = CTools::Rate(-10000, -1);
			registration.nVictory = 0;
		}
		if (i >= 0 && i < 8)
			duelGroups[T][0].push_back(registration);
		else if (i >= 8 && i < 16)
			duelGroups[T][1].push_back(registration);
		else if (i >= 16 && i < 24)
			duelGroups[T][2].push_back(registration);
		else if (i >= 24 && i < 32)
			duelGroups[T][3].push_back(registration);
	}

	duelLock.Leave();
	DuelRegistrationList.erase(T);
	Selection = true;
	return selectParticipants(T + 1);
}

void StartTournament() {
	
	if (!Selection || AllFights.empty()) {
		AllFights.clear();
		selectParticipants(1);
	}

	Tournament++;

	if (!AllFights.count(Tournament)) {
		ClearTournament();
		EndTournament(0);
		return;
	}

	/*int GetSize = Groups.size();
	for (int i = 0; i < GetSize; i++) {
		int PID = Groups.front().PID;
		Groups.erase(Groups.begin());
		TargetFind myTarget(0, 1, PID);
		IChar DuelPlayer(myTarget.getTarget());
		if (DuelPlayer.IsValid() && DuelPlayer.IsPVPValid()) {
			DuelRegistre reg;
			reg.PID = DuelPlayer.GetPID();
			reg.Name = (std::string)DuelPlayer.GetName();
			Groups.push_back(reg);
		}
	}*/

	ClearTournament();
	nVictory = 0;
	FightCount = 0;

	for (int i = 0; i < 4; i++)
		PrepareGroupFights(i);

	DuelTournament::Active = true;
	std::string notice = "Duel Tournament started for levels "+getTournamentName(Tournament)+".";
	CPlayer::WriteAll(0xFF, "dsd", 247, notice.c_str(), 2);
}

void EndTournament(int WinnerA) {
	TargetFind myTarget1(0, 1, WinnerA);
	IChar WinnerPlayer(myTarget1.getTarget());
	FightCount = 0;
	nVictory = 0;
	finalFights = false;
	ArenasBusy.clear();
	curFights.clear();
	nextFights.clear();

	std::string msg = "Duel Tournament for levels " + getTournamentName(Tournament) + " has ended with no winner.";

	if (WinnerA) {
		if (WinnerPlayer.IsOnline()) {
			msg = "Duel Tournament for levels " + getTournamentName(Tournament) + " has been won by " + (std::string)WinnerPlayer.GetName() + ".";
			WinnerPlayer.BoxMsg("Congratulations, you are the new winner of this tournament!");
			if (WinnerDuel)
				WinnerPlayer.systemReward(WinnerDuel);

			std::string Datko = "./Winners/Duel.db";
			std::fstream DGkLOG;
			DGkLOG.open(Datko, std::fstream::in | std::fstream::out | std::fstream::app);
			DGkLOG << "(Winner (Time " << Time::GetDate() + " " +Time::GetTime() << ")(Type " << Tournament << ")(PID " << WinnerPlayer.GetPID() << ")(name '" << WinnerPlayer.GetName() << "'))" << std::endl;
			DGkLOG.close();
		}
	}

	CPlayer::WriteAll(0xFF, "dsd", 247, msg.c_str(), 2);
	if(WinnerPlayer.IsOnline())
		CPlayer::WriteAll(15, "s", msg.c_str());

	if (Tournament == 8) {
		DuelTournament::Active = false;
		Selection = false;
		duelGroups.clear();
		Tournament = 0;
	}
	else
		StartTournament();
}

void fightWon(DuelFight fight, int Winner, int PID) {

	if (PID) {

		if (!fight.WinDefault.Name.empty() && fight.WinDefault.Name.find("NULL") == std::string::npos) {
			std::string notice = "the randomly picked winner of the offline fight is " + fight.WinDefault.Name + ".";
			CPlayer::WriteAll(0xFF, "dsd", 247, notice.c_str(), 2);
		}

		duelShowLock.Enter();
		if (AllFights.count(Tournament)) {
			std::vector<TOURNAMENT_PARTY> &Vec = AllFights.find(Tournament)->second;
			for (auto x = Vec.begin(); x != Vec.end(); x++) {
				std::string Name(x->szName[0]);
				if (Name == " " + fight.WinDefault.Name) {
					x->nWinCnt++;
					break;
				}
			}
		}
		duelShowLock.Leave();

		duelLock.Enter();
		if (duelGroups.count(Tournament) && duelGroups.find(Tournament)->second.count(fight.Arena)) {
			std::vector<DuelRegistre>& vect = duelGroups.find(Tournament)->second.find(fight.Arena)->second;
			
			for (auto x = vect.begin(); x != vect.end(); x++) {
				if (x->PID == fight.WinDefault.PID) {
					x->nVictory++;
					break;
				}
			}
		}
		duelLock.Leave();
	}
	else {
		int Loser = fight.Player1;
		if (Winner == fight.Player1)
			Loser = fight.Player2;

		IChar WinnerPlayer((void*)Winner);
		IChar LoserPlayer((void*)Loser);

		if (WinnerPlayer.IsOnline()) {
			std::string notice =  (std::string)WinnerPlayer.GetName() + " has won the battle.";
			CPlayer::WriteAll(0xFF, "dsd", 247, notice.c_str(), 2);

			duelShowLock.Enter();
			if (AllFights.count(Tournament)) {
				std::vector<TOURNAMENT_PARTY> &Vec = AllFights.find(Tournament)->second;
				for (auto x = Vec.begin(); x != Vec.end();x++) {
					std::string Name(x->szName[0]);
					if (Name == " " + (std::string)WinnerPlayer.GetName()) {
						x->nWinCnt++;
						break;
					}
				}
			}
			duelShowLock.Leave();

			WinnerPlayer.Buff(3871, 3, 0);
			WinnerPlayer.BoxMsg("Congratulations, you are going to the next round of this tournament!");
			WinnerPlayer.CancelBuff(373);
			WinnerPlayer.CancelBuff(374);
			WinnerPlayer.Teleport(0, DuelPortBack[0][fight.Arena], DuelPortBack[1][fight.Arena]);
			WinnerPlayer.RemoveSetBlue();
			WinnerPlayer.RemoveSetRed();
			WinnerPlayer.systemReward(WinnerDuelRound);

			CChar::WriteInSight(WinnerPlayer.GetOffset(), 0xFF, "ds", 236, "Scenario3_3_timescore");

			duelLock.Enter();
			if (duelGroups.count(Tournament) && duelGroups.find(Tournament)->second.count(fight.Arena)) {
				std::vector<DuelRegistre>& vect = duelGroups.find(Tournament)->second.find(fight.Arena)->second;
				
				for (auto x = vect.begin(); x != vect.end(); x++) {
					if (x->PID == WinnerPlayer.GetPID()) {
						x->nVictory++;
						break;
					}
				}

				WinnerPlayer.SetHonor(nVictory * 90, nVictory * 900, 0, 0, 0, 0, 0, 0, 0, 1);
			}

			duelLock.Leave();
		}

		if (LoserPlayer.IsOnline()) {
			LoserPlayer.Buff(3871, 3, 0);
			LoserPlayer.CancelBuff(373);
			LoserPlayer.CancelBuff(374);
			LoserPlayer.RemoveSetBlue();
			LoserPlayer.RemoveSetRed();
			LoserPlayer.Teleport(0, DuelPortBack[0][fight.Arena], DuelPortBack[1][fight.Arena]);
			LoserPlayer.BoxMsg("You are unfortunately out of this tournament, better luck next time!");
			LoserPlayer.systemReward(LoserDuelRound);

			LoserPlayer.SetHonor(nVictory * 10, nVictory * 100, 1, 0, 0, 0, 0, 0, 0, 0);
		}
	}
	ArenasBusy.erase(fight.Arena);

	FightCount--;
}

void beginFight(DuelFight fight) {

	IChar IPlayer1((void*)fight.Player1);
	IChar IPlayer2((void*)fight.Player2);

	if (IPlayer1.IsPVPValid() && IPlayer2.IsPVPValid() && IPlayer2.GetPID() != IPlayer1.GetPID()) {
		IPlayer1.Buff(BuffNames::Fighter, 20, 0);
		IPlayer2.Buff(BuffNames::Fighter, 20, 0);

		IPlayer1.SetRed();
		IPlayer2.SetBlue();

		IPlayer1.Teleport(0, DuelArenas[0][fight.Arena] + CTools::Rate(-100, 100), DuelArenas[1][fight.Arena] + CTools::Rate(-100, 100));
		IPlayer2.Teleport(0, DuelArenas[0][fight.Arena] + CTools::Rate(-100, 100), DuelArenas[1][fight.Arena] + CTools::Rate(-100, 100));

		ArenasBusy[fight.Arena] = curDFight();
		curFights.push_back(fight);

		std::string notice = "A duel tournament fight is about to start between " + (std::string) IPlayer1.GetName() + " and " + (std::string)IPlayer2.GetName() + " in PVP Arena " + Int2String(fight.Arena + 1) + ".";
		CPlayer::WriteAll(0xFF, "dsd", 247, notice.c_str(), 2);

		if (!DuelUnbuff.empty()) {
			int USize = DuelUnbuff.size();
			for (int i = 0; i < USize; i++) {
				IPlayer1.CancelBuff(DuelUnbuff[i]);
				IPlayer2.CancelBuff(DuelUnbuff[i]);
			}
		}

		IPlayer1.IncreaseHp(IPlayer1.GetMaxHp());
		IPlayer2.IncreaseHp(IPlayer2.GetMaxHp());
		IPlayer1.Buff(12, 300, 45);
		IPlayer2.Buff(12, 300, 45);
	}
	else {
		if ((!IPlayer1.IsValid() || !IPlayer1.IsPVPValid()) && (IPlayer2.IsValid() && IPlayer2.IsPVPValid()))
			fightWon(fight, (int)IPlayer2.GetOffset(),0);
		else if ((IPlayer1.IsValid() && IPlayer1.IsPVPValid()) && (!IPlayer2.IsPVPValid() || !IPlayer2.IsValid()))
			fightWon(fight, (int)IPlayer1.GetOffset(), 0);
		else 
			fightWon(fight, 0, 1);
	}
}

int GetWinnersGroupSize() {
	int Size = 0;

	duelLock.Enter();
	for (int i = 0; i < 4; i++) {
		if (!duelGroups.count(Tournament) || !duelGroups.find(Tournament)->second.count(i))
			continue;
		if (duelGroups.find(Tournament)->second.find(i)->second.size() == 1)
			Size++;
	}

	duelLock.Leave();
	return Size;
}
void DuelTournamentTick() {

	int GetSize = nextFights.size();
	for (int i = 0; i < GetSize; i++) {
		DuelFight fight = nextFights.front();
		nextFights.erase(nextFights.begin());

		if (!ArenasBusy.count(fight.Arena)) {
			beginFight(fight);
		}
		else
			nextFights.push_back(fight);
	}

	vector< DuelFight >::iterator it = curFights.begin();
	
	while (it != curFights.end()) {

		DuelFight fight = *it;

		if (ArenasBusy.count(fight.Arena)) {

			curDFight arenaFight = ArenasBusy.find(fight.Arena)->second;
			IChar IPlayer1((void*)fight.Player1);
			IChar IPlayer2((void*)fight.Player2);

			if (!IPlayer1.IsOnline()) {
				fightWon(fight, fight.Player2, 0);
				it = curFights.erase(it);
				break;
			}
			if (!IPlayer2.IsOnline()) {
				fightWon(fight, fight.Player1, 0);
				it = curFights.erase(it);
				break;
			}

			IPlayer1.SetRed();
			IPlayer2.SetBlue();

			if (arenaFight.Cooldown) {
				std::string msg = "Fight between " + (std::string)IPlayer1.GetName() + " and " + (std::string)IPlayer2.GetName() + " is starting in " + Int2String(arenaFight.Cooldown) + " seconds...";

				CChar::WriteInSight(IPlayer2.GetOffset(), 0xFF, "dsd", 247, msg.c_str(), 2);
				ArenasBusy[fight.Arena].Cooldown--;
			}
			else {
				if (!IPlayer1.IsBuff(373))
					IPlayer1.Buff(373, BuffNames::BuffTime, 0);
				if (!IPlayer2.IsBuff(374))
					IPlayer2.Buff(374, BuffNames::BuffTime, 0);

				if (IPlayer1.IsBuff(373) && IPlayer2.IsBuff(374)) {
					CChar::WriteInSight(IPlayer1.GetOffset(), 0xFF, "dbddd", 232, 7, (arenaFight.Time - GetTickCount()) / 1000, arenaFight.RedScore, arenaFight.BlueScore);

					if (arenaFight.Time <= GetTickCount()) {
						if (arenaFight.BlueScore > arenaFight.RedScore)
							fightWon(fight, fight.Player2, 0);
						else if (arenaFight.BlueScore < arenaFight.RedScore)
							fightWon(fight, fight.Player1, 0);
						else {
							if (IPlayer1.GetBuffValue(373) > IPlayer2.GetBuffValue(374))
								fightWon(fight, fight.Player1, 0);
							else
								fightWon(fight, fight.Player2, 0);
						}
						it = curFights.erase(it);
						break;
					}

					if (IPlayer2.IsShopping() || IPlayer2.IsFishing()) {
						fightWon(fight, fight.Player1, 0);
						it = curFights.erase(it);
						break;
					}

					if (IPlayer1.IsShopping() || IPlayer1.IsFishing()) {
						fightWon(fight, fight.Player2, 0);
						it = curFights.erase(it);
						break;
					}

					if (IPlayer2.isDead()) {
						if (IPlayer2.IsBuff(BuffNames::RevivalCheck)) {
							if (IPlayer2.GetBuffRemain(BuffNames::RevivalCheck) <= 1) {
								IPlayer2.Teleport(0, DuelArenas[0][fight.Arena] + CTools::Rate(-100, 100), DuelArenas[1][fight.Arena] + CTools::Rate(-100, 100));
								IPlayer2.Buff(24, 3, 0);
								IPlayer2.Buff(12, 300, 45);
								IPlayer2.RemoveBuffIcon(0, 0, 703, 34);
								CChar::AddMState(IPlayer2.GetOffset(), 0, 2147483648);
							}
							else
								IPlayer2.SystemMessage("Reviving in " + Int2String(IPlayer2.GetBuffRemain(BuffNames::RevivalCheck) - 1) + "...", TEXTCOLOR_DARKGREEN);
						}
						else {
							ArenasBusy[fight.Arena].RedScore += 3;
							IPlayer2.Buff(BuffNames::RevivalCheck, 7, 0);
						}
					}

					if (IPlayer1.isDead()) {
						if (IPlayer1.IsBuff(BuffNames::RevivalCheck)) {
							if (IPlayer1.GetBuffRemain(BuffNames::RevivalCheck) <= 1) {
								IPlayer1.Teleport(0, DuelArenas[0][fight.Arena] + CTools::Rate(-100, 100), DuelArenas[1][fight.Arena] + CTools::Rate(-100, 100));
								IPlayer1.Buff(24, 3, 0);
								IPlayer1.RemoveBuffIcon(0, 0, 703, 34);
								CChar::AddMState(IPlayer1.GetOffset(), 0, 2147483648);
							}
							else
								IPlayer1.SystemMessage("Reviving in " + Int2String(IPlayer1.GetBuffRemain(BuffNames::RevivalCheck) - 1) + "...", TEXTCOLOR_DARKGREEN);
						}
						else {
							ArenasBusy[fight.Arena].BlueScore += 3;
							IPlayer1.Buff(BuffNames::RevivalCheck, 7, 0);
						}
					}

					if ((IPlayer1.GetX() >> 13) != 26 || (IPlayer1.GetY() >> 13) != 34 || IPlayer1.GetZ() >= 37200 || IPlayer1.GetZ() < 36550)
						IPlayer1.Teleport(0, DuelArenas[0][fight.Arena] + CTools::Rate(-100, 100), DuelArenas[1][fight.Arena] + CTools::Rate(-100, 100));

					if ((IPlayer2.GetX() >> 13) != 26 || (IPlayer2.GetY() >> 13) != 34 || IPlayer2.GetZ() >= 37200 || IPlayer2.GetZ() < 36550)
						IPlayer2.Teleport(0, DuelArenas[0][fight.Arena] + CTools::Rate(-100, 100), DuelArenas[1][fight.Arena] + CTools::Rate(-100, 100));
				}
			}
		}

		++it;
	}

	if (FightCount <= 0) {
		nVictory++;
		duelLock.Enter();
		for (int i = 0; i < 4; i++) {
			if (duelGroups.count(Tournament) && duelGroups.find(Tournament)->second.count(i))
				duelGroups[Tournament][i] = cleanGroups(i);
		}
		duelLock.Leave();

		int WinSize = GetWinnersGroupSize();
		if (WinSize == 4)
			finalFights = true;

		if (!finalFights) {
			for (int i = 0; i < 4; i++)
				PrepareGroupFights(i);
		}
		else {

			if (WinSize > 1) {

				duelLock.Enter();
				std::map<int, std::vector<DuelRegistre>> duelGroupsx;
				while (WinSize > 1) {
					DuelRegistre PlayerA = DuelRegistre();
					DuelRegistre PlayerB = DuelRegistre();
					int i = 0;
					while (i < 4) {
						if (duelGroups.count(Tournament) && duelGroups.find(Tournament)->second.count(i) && !duelGroups.find(Tournament)->second.find(i)->second.empty()) {
							PlayerA = duelGroups.find(Tournament)->second.find(i)->second.front();
							duelGroups[Tournament].erase(i);
							break;
						}
						i++;
					}
					i = 0;
					while (i < 4) {
						if (duelGroups.count(Tournament) && duelGroups.find(Tournament)->second.count(i) && !duelGroups.find(Tournament)->second.find(i)->second.empty()) {
							DuelRegistre PlayerC = duelGroups.find(Tournament)->second.find(i)->second.front();
							if (PlayerC.PID != PlayerA.PID) {
								PlayerB = PlayerC;
								duelGroups[Tournament].erase(i);
								break;
							}
						}
						i++;
					}

					if (PlayerA.PID && PlayerB.PID && PlayerA.PID != PlayerB.PID) {
						duelGroupsx[FightCount].push_back(PlayerA);
						duelGroupsx[FightCount].push_back(PlayerB);
					}

					TargetFind myTarget1(0, 1, PlayerA.PID);
					TargetFind myTarget2(0, 1, PlayerB.PID);

					DuelRegistre random = PlayerA;

					if (CTools::Rate(0, 9) >= 5)
						random = PlayerB;

					if (random.PID < 0)
						random = (random.PID == PlayerB.PID) ? PlayerA : PlayerB;

					nextFights.push_back(DuelFight((int)myTarget1.getTarget(), (int)myTarget2.getTarget(), FightCount, random));
					FightCount++;
					WinSize -= 2;
				}
				duelGroups[Tournament] = duelGroupsx;

				duelLock.Leave();
			}
			else if (WinSize == 1) {
				duelLock.Enter();
				int PID = (duelGroups.count(Tournament) && duelGroups.find(Tournament)->second.count(0) && !duelGroups.find(Tournament)->second.find(0)->second.empty()) ? duelGroups.find(Tournament)->second.find(0)->second.front().PID : 0;
				duelLock.Leave();
				EndTournament(PID);
			}
		}
	}

}