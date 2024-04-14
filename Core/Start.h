
void __fastcall RealBlob(int Monster, void *edx)
{
	IChar IMonster((void*)Monster);

	int Tanker = IMonster.GetMobTanker();
	if (Tanker) {
		IChar IPlayer((void*)Tanker);

		if (IPlayer.IsValid() && IPlayer.GetType() == 0)
		{
			if (!IPlayer.IsUnblobbing() && !UnBlob.count(IMonster.GetMobIndex()))
			{
				CChar::Unlock(IMonster.GetOffset());
				IMonster.Blob();
				CChar::Lock(IMonster.GetOffset());
				return;
			}
		}
	}

	(*(int(__thiscall **)(int, DWORD))(*(DWORD *)Monster + 188))(Monster, 0);
}

std::string getServerName() {
	if (thisServerName.empty()) {
		return "Kal Online";
	}
	else if (thisServerName.length() > 20) { // set maximum length to 20
		return thisServerName.substr(0, 20);
	}
	else {
		return thisServerName;
	}
}

int getIndex(char* line) {
	int Index = 0;
	std::vector<std::string> arra = getExplode("(", ")", line);
	sscanf(arra[2].c_str(), "Index %d", &Index);

	if (!Index)
		sscanf(arra[2].c_str(), "index %d", &Index);

	return Index;
}

int getAction(char* line, int Type) {
	std::vector<std::string> arra = getExplode("(", ")", line);
	
	for (int i = 0; i < arra.size(); i++) {
		int AID = 0, AFlag = 0;
		if (sscanf(arra[i].c_str(), "action %d %d", &AID, &AFlag) == 2 || sscanf(arra[i].c_str(), "Action %d %d", &AID, &AFlag) == 2)
			return (Type == 1 ? AFlag : AID);
	}

	return 0;
}

void setInitItem() {

	FILE *file = fopen("./Config/InitItem.txt", "r");
	if (file != NULL)
	{
		char line[BUFSIZ];
		while (fgets(line, sizeof line, file) != NULL)
		{
			if (stristr(line, "(class ornament soulpocket)") != NULL)
				NewItemType[getIndex(line)] = SOUL_POCKET;
			
			if (stristr(line, "(class ornament resistnecklace") != NULL)
				NewItemType[getIndex(line)] = NECKLACE2;

			if (stristr(line, "(class weapon cost)") != NULL) {
				NewItemType[getIndex(line)] = CUSTOM_WEAPON;
				int action = getAction(line, 0);
				if(action == 44 || action == 45)
					CostWeaponsEffects[getIndex(line)] = action;
			}

			if (stristr(line, "(class defense cost)") != NULL)
				NewItemType[getIndex(line)] = COSTUME_SUIT;

			if (stristr(line, "(class pet premiumegg)") != NULL)
				NewItemType[getIndex(line)] = PREMIUM_PET;

			if (stristr(line, "(class defense riding") != NULL)
				NewItemType[getIndex(line)] = RIDING_ARMOR;

			if (stristr(line, "(class pet egg)") != NULL)
				NewItemType[getIndex(line)] = NORMAL_PET;

			if (stristr(line, "(class LimitedPet egg)") != NULL)
				NewItemType[getIndex(line)] = NORMAL_PET;

			if (stristr(line, "(class pet monsteregg)") != NULL)
				NewItemType[getIndex(line)] = MONSTER_PET;

			if (stristr(line, "(class defense standard)") != NULL)
				NewItemType[getIndex(line)] = Wings;

			if (stristr(line, "(class ride ") != NULL) {
				NewItemType[getIndex(line)] = RIDING_PET;
				CDBSocket::Write(109, "dd", getIndex(line), 0);
				InvCheck.insert(getIndex(line));
			}

			if (stristr(line, "(class defense costumeeffect)") != NULL) {
				NewItemType[getIndex(line)] = COSTUMEEFFECT;
				CostumeEffects[getIndex(line)] = getAction(line,1);
			}

			if (stristr(line, "(class quest ") != NULL) {
				InvCheck.insert(getIndex(line));
				CDBSocket::Write(109, "dd", getIndex(line), 1);
			}
		}
	}
	fclose(file);
}

void StartAuction() {
	Interface <ITools> Tools;
	char Seller[17], Bidder[17];
	int PID = 0, RPID = 0, IID = 0, BidRemain = 0, CurrentBid = 0, Price = 0, Index = 0, Prefix = 0, Info = 0, Num = 0, MaxEnd = 0, CurEnd = 0, SetGem = 0, XAttack = 0, XMagic = 0, XDefense = 0, XHit = 0, XDodge = 0, Protect = 0, UpgrLevel = 0, UpgrRate = 0, x = 0, y = 0, z = 0, remaintime = 0, dsstype = 0, phyatk = 0, magatk = 0, def = 0, absorb = 0, eva = 0, otp = 0, hpinc = 0, mpinc = 0, str = 0, hp = 0, intel = 0, wis = 0, agi = 0, PerfShotCheck = 0, QIgongGrade = 0, dg1stat = 0, dg1type = 0, a = 0, dg2stat = 0, dg2type = 0, refill = 0;
	RETCODE rc; HENV henv; HDBC hdbc; HSTMT hstmt; SDWORD cbData;
	const char *db = ConfigCheckDB2.c_str();
	SQLAllocEnv(&henv);
	SQLAllocConnect(henv, &hdbc);
	rc = SQLConnect(hdbc, (unsigned char*)db, SQL_NTS, 0, 0, 0, 0);

	if ((rc != SQL_SUCCESS) && (rc != SQL_SUCCESS_WITH_INFO))
	{
		SQLFreeConnect(hdbc);
		SQLFreeEnv(henv);
		return;
	}

	rc = SQLAllocStmt(hdbc, &hstmt);
	std::stringstream query;
	query << "SELECT IID, Seller, Bidder, BidRemain, CurrentBid, Price, [Index], Prefix, Info, Num, MaxEnd, CurEnd, SetGem, XAttack, XMagic, XDefense, XHit, XDodge, Protect, UpgrLevel, UpgrRate, x, y, z, remaintime, dsstype, phyatk, magatk, def, absorb, eva, otp, hpinc, mpinc, str, hp, intel, wis, agi, PerfShotCheck, QIgongGrade, dg1stat, dg1type, a, dg2stat, dg2type, refill,PID,RPID  FROM  Auction";
	std::string runquery = query.str();
	const char *sql = runquery.c_str();
	rc = SQLExecDirect(hstmt, (unsigned char*)sql, SQL_NTS);
	if ((rc != SQL_SUCCESS) && (rc != SQL_SUCCESS_WITH_INFO))
	{
		SQLFreeStmt(hstmt, SQL_DROP);
		SQLDisconnect(hdbc);
		SQLFreeConnect(hdbc);
		SQLFreeEnv(henv);
		return;
	}
	else {
		for (rc = SQLFetch(hstmt); rc == SQL_SUCCESS; rc = SQLFetch(hstmt))
		{
			SQLGetData(hstmt, 1, SQL_INTEGER, &IID, sizeof(int), &cbData);
			SQLGetData(hstmt, 2, SQL_CHAR, &Seller, sizeof(Seller), &cbData);
			SQLGetData(hstmt, 3, SQL_CHAR, &Bidder, sizeof(Bidder), &cbData);
			SQLGetData(hstmt, 4, SQL_INTEGER, &BidRemain, sizeof(int), &cbData);
			SQLGetData(hstmt, 5, SQL_INTEGER, &CurrentBid, sizeof(int), &cbData);
			SQLGetData(hstmt, 6, SQL_INTEGER, &Price, sizeof(int), &cbData);
			SQLGetData(hstmt, 7, SQL_INTEGER, &Index, sizeof(int), &cbData);
			SQLGetData(hstmt, 8, SQL_INTEGER, &Prefix, sizeof(int), &cbData);
			SQLGetData(hstmt, 9, SQL_INTEGER, &Info, sizeof(int), &cbData);
			SQLGetData(hstmt, 10, SQL_INTEGER, &Num, sizeof(int), &cbData);
			SQLGetData(hstmt, 11, SQL_INTEGER, &MaxEnd, sizeof(int), &cbData);
			SQLGetData(hstmt, 12, SQL_INTEGER, &CurEnd, sizeof(int), &cbData);
			SQLGetData(hstmt, 13, SQL_INTEGER, &SetGem, sizeof(int), &cbData);
			SQLGetData(hstmt, 14, SQL_INTEGER, &XAttack, sizeof(int), &cbData);
			SQLGetData(hstmt, 15, SQL_INTEGER, &XMagic, sizeof(int), &cbData);
			SQLGetData(hstmt, 16, SQL_INTEGER, &XDefense, sizeof(int), &cbData);
			SQLGetData(hstmt, 17, SQL_INTEGER, &XHit, sizeof(int), &cbData);
			SQLGetData(hstmt, 18, SQL_INTEGER, &XDodge, sizeof(int), &cbData);
			SQLGetData(hstmt, 19, SQL_INTEGER, &Protect, sizeof(int), &cbData);
			SQLGetData(hstmt, 20, SQL_INTEGER, &UpgrLevel, sizeof(int), &cbData);
			SQLGetData(hstmt, 21, SQL_INTEGER, &UpgrRate, sizeof(int), &cbData);
			SQLGetData(hstmt, 22, SQL_INTEGER, &x, sizeof(int), &cbData);
			SQLGetData(hstmt, 23, SQL_INTEGER, &y, sizeof(int), &cbData);
			SQLGetData(hstmt, 24, SQL_INTEGER, &z, sizeof(int), &cbData);
			SQLGetData(hstmt, 25, SQL_INTEGER, &remaintime, sizeof(int), &cbData);
			SQLGetData(hstmt, 26, SQL_INTEGER, &dsstype, sizeof(int), &cbData);
			SQLGetData(hstmt, 27, SQL_INTEGER, &phyatk, sizeof(int), &cbData);
			SQLGetData(hstmt, 28, SQL_INTEGER, &magatk, sizeof(int), &cbData);
			SQLGetData(hstmt, 29, SQL_INTEGER, &def, sizeof(int), &cbData);
			SQLGetData(hstmt, 30, SQL_INTEGER, &absorb, sizeof(int), &cbData);
			SQLGetData(hstmt, 31, SQL_INTEGER, &eva, sizeof(int), &cbData);
			SQLGetData(hstmt, 32, SQL_INTEGER, &otp, sizeof(int), &cbData);
			SQLGetData(hstmt, 33, SQL_INTEGER, &hpinc, sizeof(int), &cbData);
			SQLGetData(hstmt, 34, SQL_INTEGER, &mpinc, sizeof(int), &cbData);
			SQLGetData(hstmt, 35, SQL_INTEGER, &str, sizeof(int), &cbData);
			SQLGetData(hstmt, 36, SQL_INTEGER, &hp, sizeof(int), &cbData);
			SQLGetData(hstmt, 37, SQL_INTEGER, &intel, sizeof(int), &cbData);
			SQLGetData(hstmt, 38, SQL_INTEGER, &wis, sizeof(int), &cbData);
			SQLGetData(hstmt, 39, SQL_INTEGER, &agi, sizeof(int), &cbData);
			SQLGetData(hstmt, 40, SQL_INTEGER, &PerfShotCheck, sizeof(int), &cbData);
			SQLGetData(hstmt, 41, SQL_INTEGER, &QIgongGrade, sizeof(int), &cbData);
			SQLGetData(hstmt, 42, SQL_INTEGER, &dg1stat, sizeof(int), &cbData);
			SQLGetData(hstmt, 43, SQL_INTEGER, &dg1type, sizeof(int), &cbData);
			SQLGetData(hstmt, 44, SQL_INTEGER, &a, sizeof(int), &cbData);
			SQLGetData(hstmt, 45, SQL_INTEGER, &dg2stat, sizeof(int), &cbData);
			SQLGetData(hstmt, 46, SQL_INTEGER, &dg2type, sizeof(int), &cbData);
			SQLGetData(hstmt, 47, SQL_INTEGER, &refill, sizeof(int), &cbData);
			SQLGetData(hstmt, 48, SQL_INTEGER, &PID, sizeof(int), &cbData);
			SQLGetData(hstmt, 49, SQL_INTEGER, &RPID, sizeof(int), &cbData);

			AuctionItem item = AuctionItem();
			std::string Bid(Bidder);
			std::string Sell(Seller);
			item.Bidder = Bid;
			item.BidRemain = BidRemain;
			item.CurrentBid = CurrentBid;
			item.Index = Index;
			item.SetGem = SetGem;
			item.Prefix = Prefix;
			item.Amount = Num;
			item.PID = PID;
			item.RPID = RPID == 255 ? 0 : RPID;
			memset(item.ItemPacket, 0, sizeof item.ItemPacket);
			Tools->Compile(item.ItemPacket, "wdbddbbbbbbbbwbbbbbdbwwwwbbbbbbbbbbdbbwbbd", Index, IID, Prefix, Info, Num, MaxEnd, CurEnd, SetGem, XAttack, XMagic, XDefense, XHit, XDodge, Protect, UpgrLevel, UpgrRate, x, y, z, 0, dsstype, phyatk, magatk, def, absorb, eva, otp, hpinc, mpinc, str, hp, intel, wis, agi, PerfShotCheck, QIgongGrade, dg1stat, dg1type, a, dg2stat, dg2type, refill);
			item.Price = Price;
			item.Seller = Sell;
			AuctionItems[IID] = item;

			InterlockedIncrement(&auctionItemsNum);
			PID = 0, RPID = 0, IID = 0, BidRemain = 0, CurrentBid = 0, Price = 0, Index = 0, Prefix = 0, Info = 0, Num = 0, MaxEnd = 0, CurEnd = 0, SetGem = 0, XAttack = 0, XMagic = 0, XDefense = 0, XHit = 0, XDodge = 0, Protect = 0, UpgrLevel = 0, UpgrRate = 0, x = 0, y = 0, z = 0, remaintime = 0, dsstype = 0, phyatk = 0, magatk = 0, def = 0, absorb = 0, eva = 0, otp = 0, hpinc = 0, mpinc = 0, str = 0, hp = 0, intel = 0, wis = 0, agi = 0, PerfShotCheck = 0, QIgongGrade = 0, dg1stat = 0, dg1type = 0, a = 0, dg2stat = 0, dg2type = 0, refill = 0;
		}
	}

	SQLFreeStmt(hstmt, SQL_DROP);
	SQLDisconnect(hdbc);
	SQLFreeConnect(hdbc);
	SQLFreeEnv(henv); 

	if (InterlockedExchangeAdd(&auctionItemsNum, 0) >= 1)
		UpdateAuction();

}

void StartItemDB() {
	Interface <ITools> Tools;
	RETCODE rc; HENV henv; HDBC hdbc; HSTMT hstmt; SDWORD cbData;
	const char *db = ConfigCheckDB2.c_str();
	SQLAllocEnv(&henv);
	SQLAllocConnect(henv, &hdbc);
	rc = SQLConnect(hdbc, (unsigned char*)db, SQL_NTS, 0, 0, 0, 0);

	if ((rc != SQL_SUCCESS) && (rc != SQL_SUCCESS_WITH_INFO))
	{
		SQLFreeConnect(hdbc);
		SQLFreeEnv(henv);
		return;
	}

	rc = SQLAllocStmt(hdbc, &hstmt);
	std::stringstream query;
	query << "SELECT [IID],[ItemStat],[PetTime],[Lock] FROM Item WHERE [PID] = 0 AND ([ItemStat] != 0 OR [PetTime] != 0 OR [Lock] != 'nopwd')";
	std::string runquery = query.str();
	const char *sql = runquery.c_str();
	rc = SQLExecDirect(hstmt, (unsigned char*)sql, SQL_NTS);
	if ((rc != SQL_SUCCESS) && (rc != SQL_SUCCESS_WITH_INFO))
	{
		SQLFreeStmt(hstmt, SQL_DROP);
		SQLDisconnect(hdbc);
		SQLFreeConnect(hdbc);
		SQLFreeEnv(henv);
		return;
	}
	else {
		for (rc = SQLFetch(hstmt); rc == SQL_SUCCESS; rc = SQLFetch(hstmt))
		{
			char Lock[17];
			int IID = 0, ItemStat = 0, PetTime = 0;

			SQLGetData(hstmt, 1, SQL_INTEGER, &IID, sizeof(int), &cbData);
			SQLGetData(hstmt, 2, SQL_INTEGER, &ItemStat, sizeof(int), &cbData);
			SQLGetData(hstmt, 3, SQL_INTEGER, &PetTime, sizeof(int), &cbData);
			SQLGetData(hstmt, 4, SQL_CHAR, &Lock, sizeof(Lock), &cbData);

			if (ItemStat) {
				itemStat.Enter();
				GetItemStat.insert(std::pair<int, int>(IID, ItemStat));
				itemStat.Leave();
			}

			if (PetTime)
				PetLifeCheck.replaceInsert(IID, PetTime);

			if (Lock && strlen(Lock)) {
				itemLockLock.Enter();
				ItemLockCheck.insert(std::pair<int, std::string>(IID, Lock));
				itemLockLock.Leave();
			}
		}
	}

	SQLFreeStmt(hstmt, SQL_DROP);
	SQLDisconnect(hdbc);
	SQLFreeConnect(hdbc);
	SQLFreeEnv(henv);
}

bool compareByIndex(const AuctionItem &a, const AuctionItem &b)
{
	return a.Index == b.Index;
}

bool compareByTime(const AuctionItem &a, const AuctionItem &b)
{
	return a.BidRemain < b.BidRemain && compareByIndex(a,b);
}

void UpdateAuction() {
	//auctionLock.Enter();
	ConcurrentMap<long, AuctionItem> cloneA = AuctionItems;
	//auctionLock.Leave();

	auctionVecLock.Enter();

	AuctionVec.clear();
	for (auto x = cloneA.rbegin(); x != cloneA.rend(); x++)
		AuctionVec.push_back(x->second);
	std::sort(AuctionVec.begin(), AuctionVec.end(), compareByTime);

	auctionVecLock.Leave();
}

void ShowAuction(void* Player, char Type, unsigned short Page) {
	if (Page) {
		IChar IPlayer((void*)Player);
		if (IPlayer.IsOnline()) {
			Interface <ITools> Tools;

			auctionVecLock.Enter();
			std::vector<AuctionItem> CloneAuction = AuctionVec;
			auctionVecLock.Leave();
			
			char PlayerPack[7000] = { 0 };
			int Size = CloneAuction.size();

			int Packetsize = 0;
			int i = 0; 

			if ((int)Type == 0) {
				for (int j = (Page - 1) * 8; j < (Page * 8 <= CloneAuction.size() ? Page * 8 : CloneAuction.size()); j++) {
					AuctionItem x = CloneAuction[j];
					Tools->Compile(PlayerPack + Packetsize, "swdsdmd", x.Seller.c_str(), (int)ceil((double)((x.BidRemain - (int)time(0)) / 3600)), x.Price, x.Bidder.c_str(), x.CurrentBid, x.ItemPacket, 67, 2513);
					Packetsize += 67 + strlen(x.Seller.c_str()) + strlen(x.Bidder.c_str()) + 2 + 14;
					i++;
				}
			}
			else if (Type == 1) {
				Size = 0;
				for (int j = 0; j < CloneAuction.size(); j++) {
					AuctionItem x = CloneAuction[j];
					if (x.RPID == IPlayer.GetPID()) {
						if (j >= (Page - 1) * 8 && j < (Page * 8 <= CloneAuction.size() ? Page * 8 : CloneAuction.size())) {
							Tools->Compile(PlayerPack + Packetsize, "swdsdmd", x.Seller.c_str(), (int)ceil((double)((x.BidRemain - (int)time(0)) / 3600)), x.Price, x.Bidder.c_str(), x.CurrentBid, x.ItemPacket, 67, 2513);
							Packetsize += 67 + strlen(x.Seller.c_str()) + strlen(x.Bidder.c_str()) + 2 + 14;
							i++;
						}
						Size++;
					}
				}
			}
			else if (Type == 2) {
				Size = 0;
				for (int j = 0; j < CloneAuction.size(); j++) {
					AuctionItem x = CloneAuction[j];
					if (x.PID == IPlayer.GetPID()) {
						if (j >= (Page - 1) * 8 && j < (Page * 8 <= CloneAuction.size() ? Page * 8 : CloneAuction.size())) {
							Tools->Compile(PlayerPack + Packetsize, "swdsdmd", x.Seller.c_str(), (int)ceil((double)((x.BidRemain - (int)time(0)) / 3600)), x.Price, x.Bidder.c_str(), x.CurrentBid, x.ItemPacket, 67, 2513);
							Packetsize += 67 + strlen(x.Seller.c_str()) + strlen(x.Bidder.c_str()) + 2 + 14;
							i++;
						}
						Size++;
					}
				}
			}
			if (i || !Type)
				CPlayer::Write((void*)Player, 0xFE, "dbdwbm", 196, Type, Size, Page, i, PlayerPack, Packetsize);
		}
	}
}


void setMapData() {
	std::map<int, int> tempSummon = SummonQuestRegistration.toMap();
	for (auto x = tempSummon.begin(); x != tempSummon.end(); x++) {
		MSummonedConfig mConf = MSummonedConfig();
		MSummonConfig msConfig = SummonQuest.find(x->first)->second;
		if (x->second < 0 || x->second >= msConfig.ItemAmount) {
			SummonQuestRegistration.erase(x->first);
			continue;
		}
		mConf.Spawned = 0;
		mConf.Limit = 0;
		mConf.CurAmount = x->second;
		SummonedQuest.replaceInsert(x->first,mConf);
	}

	LotteryCheck = LotAmount * Lottery.size();
	DNPCECollectedTotalItem = EventQuests.count(1) ? EventQuests.find(1)->second : 0;
	NPCECollectedTotalItem = EventQuests.count(2) ? EventQuests.find(2)->second : 0;
}
void initSummonTracker() {
	for (auto x = SummonTrack.begin(); x != SummonTrack.end(); x++)
		CDBSocket::Write(111, "dd", *x, 0);
}

void __fastcall Start(int Start, void *edx, u_short hostshort)
{
	RemoteLisansCheck();

	if (ScaniaLicense) {
		setInitItem();
		CDBSocket::Write(102, "d", 1);
		StartItemDB();
		StartAuction();
	}

	CConsole::Black("[MD5 Check] Client file Checksum.scn file has been generated.");

	CIOServer::Start(Start,hostshort);
	Interface<IMemory> Memory;
	Memory->Hook(0x0043DEE1, RealBlob, 0xe8, 6); 
	
	if (strlen(CWTCC) > 0 && (std::string)CWTCC == "true")
	{
		//int End = CWTCEH < 23 ? CWTCEH + 1 : CWTCEH;
		int DayBefore = CWTCD > 0 ? CWTCD - 1 : 6;
		int DayBefore2 = CWTCD > 0 ? CWTCD - 2 : 5;
		if (CWTCD == 1)
			DayBefore2 = 6;

		int CWTime = 3600;

		Memory->Copy((void*)0x00411A0F, &CWTime, 2);
		Memory->Copy((void*)0x004118D7, &DayBefore2, 1);
		Memory->Copy((void*)0x004118F2, &DayBefore, 1);
		Memory->Copy((void*)0x00411916, &CWTCD, 1);
		Memory->Copy((void*)0x00411A08, &CWTCSH, 1);
		Memory->Copy((void*)0x004118E0, &CWTCSH, 1);
		Memory->Copy((void*)0x004118FB, &CWTCSH, 1);
		Memory->Copy((void*)0x0041191F, &CWTCSH, 1);
		Memory->Copy((void*)0x00411931, &CWTCEH, 1);
	}
	std::string uptime = getSysUpTime();
	unsigned int days = 0;

	// Find the index of the first digit
	std::size_t firstDigitPos = uptime.find_first_of("0123456789");

	if (firstDigitPos != std::string::npos) {
		// Extract the substring starting from the first digit to the next space
		std::string daysStr = uptime.substr(firstDigitPos, uptime.find(' ', firstDigitPos) - firstDigitPos);

		// Convert the substring to an unsigned int
		std::istringstream iss(daysStr);
		iss >> days;
	}
	if (days >= 7){
		CConsole::Red("[Warning] Machine uptime exceeded 7 days. Restart machine to avoid any bug that may occur");
	}

	if (ScaniaLicense) {
		SummonQuestRegistration = RegistrationMap<int, int>("SummonedQuest");
		//ItemLimitUsage = RegistrationMap<int, int>("ItemLimitUsage");
		//ItemLimitTime = RegistrationMap<int, int>("ItemLimitTime");
		EventQuests = RegistrationMap<int, int>("EventQuests");
		GuildRaidItems = RegistrationMap<int, int>("GuildRaidItems");
		GuildBuffItems = RegistrationMap<long, int>("GuildBuffItems");
		XLottery = SystemRegistration<int>("XLottery");
		Lottery = SystemRegistration<int>("Lottery");
		LastManRegistration = SystemRegistration<int>("LMS");
		BattlefieldRegistration = SystemRegistration<int>("Battlefield");
		TBRegistration = SystemRegistration<int>("TriangularBattle");
		//ScenarioRegistration = Registration("GVG");
		RaidSystem = SystemRegistration<int>("Raid");
		F10Registration = SystemRegistration<int>("F10");
		MautRegistration = SystemRegistration<int>("Mautareta");
		BossEXPRegistration = SystemRegistration<int>("BossEXP");
		CaptureRegistration = SystemRegistration<int>("Capture");
		//RewardLimit = SystemRegistration<std::string>();
		initSummonTracker();
		CConsole::Blue("KalTechSolutions [%s Version] . . .", ServerName);
		MyAgentsWebhook(ServerName);
		_beginthread(ContinuesSkill, 0, 0);
	}
	else
		exit(1);
}

int __cdecl Black(char *Msg, ...)
{
	std::string GetMsg = std::string(Msg);
	time_t MyTime = time(0);
	tm *MT = localtime(&MyTime);
	if ( GetMsg.substr(0,2) == "##" || GetMsg.substr(0,2) == "$$" || GetMsg.substr(0,2) == "@@" )
		return 0;

	if ( GetMsg.substr(0,11) == "[SpeedHack]" )
		return 0;

	if ( GetMsg.substr(0,20) == "invalid monster move" )
		return 0;

	if ( GetMsg.substr(0,9) == "move hack" )
		return 0;

	if ( GetMsg.substr(0,41) == "Invalid state at CSocket::Process() Type(" )
		return 0;

	if ( GetMsg.substr(0,20) == "close pending socket" )
		return 0;

	//if (GetMsg.substr(0, 40) == "DB server version (Version:%d, IID:0x%x)")
	//	return 0;

	//if (GetMsg.substr(0, 32) == "Auth server version (Version:%d)")
	//	return 0;

	//if (GetMsg.substr(0, 75) == "Server is ready on port %d (time stamp: %02d/%02d/%02d %02d:%02d:%02d (KR))")
	//{

	//	ConsoleWrite(SADDLE_BROWN, "Server is ready on port %d (time stamp: %02d/%02d/%02d %02d:%02d:%02d)", *(DWORD *)0x004E1170,
	//		MT->tm_year % 100, MT->tm_mon + 1, MT->tm_mday, MT->tm_hour, MT->tm_min, MT->tm_sec);
	//	return 0;
	//}
	va_list va;
	va_start(va,Msg);
	int Check = CLog::AddV(1,Msg,va);
	va_end(va);
	return Check;
}

int __cdecl Blue(char *Msg, ...)
{
	std::string GetMsg = std::string(Msg);

	if ( GetMsg.substr(0,22) == "new connection in_addr" )
		return 0;

	if ( GetMsg.substr(0,20) == "close pending socket" )
		return 0;

	//if (GetMsg.substr(0, 19) == "Reading [Map] . . .")
	//{
	//	ConsoleWrite(SADDLE_BROWN, "Reading [Map] . . .");
	//	return 0;
	//}

	//if (GetMsg.substr(0, 27) == "Reading [InitMonster] . . .")
	//{
	//	ConsoleWrite(SADDLE_BROWN, "Reading [InitMonster] . . .");
	//	return 0;
	//}

	//if (GetMsg.substr(0, 26) == "Reading [GenMonster] . . .")
	//{
	//	ConsoleWrite(SADDLE_BROWN, "Reading [GenMonster] . . .");
	//	return 0;
	//}

	//if (GetMsg.substr(0, 24) == "Reading [InitItem] . . .")
	//{
	//	ConsoleWrite(SADDLE_BROWN, "Reading [InitItem] . . .");
	//	return 0;
	//}

	//if (GetMsg.substr(0, 22) == "Reading [Prefix] . . .")
	//{
	//	ConsoleWrite(SADDLE_BROWN, "Reading [Prefix] . . .");
	//	return 0;
	//}

	//if (GetMsg.substr(0, 25) == "Reading [ItemGroup] . . .")
	//{
	//	ConsoleWrite(SADDLE_BROWN, "Reading [ItemGroup] . . .");
	//	return 0;
	//}

	//if (GetMsg.substr(0, 21) == "Reading [Goods] . . .")
	//{
	//	ConsoleWrite(SADDLE_BROWN, "Reading [Goods] . . .");
	//	return 0;
	//}

	//if (GetMsg.substr(0, 23) == "Reading [InitNPC] . . .")
	//{
	//	ConsoleWrite(SADDLE_BROWN, "Reading [InitNPC] . . .");
	//	return 0;
	//}

	//if (GetMsg.substr(0, 25) == "Reading [InitSkill] . . .")
	//{
	//	ConsoleWrite(SADDLE_BROWN, "Reading [InitSkill] . . .");
	//	return 0;
	//}

	//if (GetMsg.substr(0, 21) == "Reading [Quest] . . .")
	//{
	//	ConsoleWrite(SADDLE_BROWN, "Reading [Quest] . . .");
	//	return 0;
	//}

	//if (GetMsg.substr(0, 25) == "Reading [Etc] . . .")
	//{
	//	ConsoleWrite(SADDLE_BROWN, "Reading [Etc] . . .");
	//	return 0;
	//}

	//if (GetMsg.substr(0, 25) == "Another Server is running")
	//{
	//	ConsoleWrite(SADDLE_BROWN, "Another Server is running");
	//	return 0;
	//}


	va_list va;
	va_start(va,Msg);
	int Check = CLog::AddV(0,Msg,va);
	va_end(va);
	return Check;
}

int __cdecl Red(char *Msg, ...)
{
	std::string GetMsg = std::string(Msg);

	if (GetMsg.substr(0, 19) == "invalid buffer size")
		return 0;

	if (GetMsg.substr(0, 18) == "Excess of Item Num")
		return 0;

	if (GetMsg.substr(0, 15) == "CQuest::Proceed")
		return 0;
	
	va_list va;
	va_start(va, Msg);
	int Check = CLog::AddV(2, Msg, va);
	va_end(va);
	return Check;
}