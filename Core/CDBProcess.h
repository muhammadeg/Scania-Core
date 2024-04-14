int K = 0;

int __cdecl CDBProcess(char *Data)
{

	if ((unsigned char)Data[2] == 18 && !K) {
		GetNPCList();
		setMapData();

		K = 1;
	}

	if ((unsigned char)Data[2] == 25)
	{
		int PID = 0, MID = 0, RPID = 0, IID = 0; char Type = 0, xType = 0, Status = 0; const char *Name = "nopwd";
		Interface<ITools> Tools;
		//Tools->ParseData((char*)(void*)(Data + 3), "dbdbbdsd", &PID, &Type, &MID, &xType, &Status, &RPID, &Name, &IID);
		CPacket::xRead((char*)(void*)(Data + 3), "dbdbbdsd", &PID, &Type, &MID, &xType, &Status, &RPID, &Name, &IID);
		if (PID == -1 && Type == 1 && MID > 0 && RPID > 0 && IID)
		{
			TargetFind myTarget(0, 1, RPID);
			int Player = (int)myTarget.getTarget();

			if (Player)
			{
				CDBSocket::Write(30, "dbddbbddwdd", MID, 1, 0, MID, 0, 1, RPID, IID, 0, 0, 0);
				CPlayer::Write((void*)Player, 68, "bbs", 85, 0, thisServerName.c_str());
				return 0;
			}
		}
	}
	if ((unsigned char)Data[2] == 50)
	{
		int PID = 0, HP = 0, HK = 0, HD = 0, DKPT = 0, DKPW = 0, PLT = 0, PLW = 0, SVT = 0, SVW = 0, RP = 0; Interface<ITools> Tools;
		//Tools->ParseData((char*)(void*)(Data + 3), "ddddddddddd", &PID, &HP, &HK, &HD, &DKPT, &DKPW, &PLT, &PLW, &SVT, &SVW, &RP);
		CPacket::xRead((char*)(void*)(Data + 3), "ddddddddddd", &PID, &HP, &HK, &HD, &DKPT, &DKPW, &PLT, &PLW, &SVT, &SVW, &RP);
		if (PID)
		{
			TargetFind myTarget(0, 1, PID);
			int Player = (int)myTarget.getTarget();
			IChar IPlayer((void*)Player);
			if (IPlayer.IsOnline()) {
				IPlayer.SetProperty(PlayerProperty::HPx, HP);
				IPlayer.SetProperty(PlayerProperty::HKx, HK);
				IPlayer.SetProperty(PlayerProperty::HDx, HD);
				IPlayer.SetProperty(PlayerProperty::DKPTx, DKPT);
				IPlayer.SetProperty(PlayerProperty::DKPWx, DKPW);
				IPlayer.SetProperty(PlayerProperty::PLTx, PLT);
				IPlayer.SetProperty(PlayerProperty::PLWx, PLW);
				IPlayer.SetProperty(PlayerProperty::SVTx, SVT);
				IPlayer.SetProperty(PlayerProperty::SVWx, SVW);
				IPlayer.SetProperty(PlayerProperty::RPx, RP);
				if (!IPlayer.isPortalMode())
					IPlayer.ShowHonor(HP, HK, HD, DKPT, DKPW, PLT, PLW, SVT, SVW, RP, 0);
				IPlayer.UpdateHonorTag(HP);
			}

		}

		return 0;
	}

	if ((unsigned char)Data[2] == 51)
	{
		int PID = 0, Time = 0, Day = 0; Interface<ITools> Tools;
		//Tools->ParseData((char*)(void*)(Data + 3), "ddd", &PID, &Day, &Time);
		CPacket::xRead((char*)(void*)(Data + 3), "ddd", &PID, &Day, &Time);
		if (PID && Day)
		{
			TargetFind myTarget(0, 1, PID);
			int Player = (int)myTarget.getTarget();
			IChar IPlayer((void*)Player);

			if (IPlayer.IsOnline()) {
				IPlayer.SetProperty(PlayerProperty::EmokTime, Time);
				IPlayer.SetProperty(PlayerProperty::EmokDay, Day);
			}
		}

		return 0;
	}

	if ((unsigned char)Data[2] == 52)
	{
		int Remain = 0, Type = 0, PID = 0; Interface<ITools> Tools;
		//Tools->ParseData((char*)(void*)(Data + 3), "ddd", &PID, &Type, &Remain);
		CPacket::xRead((char*)(void*)(Data + 3), "ddd", &PID, &Type, &Remain);
		if (PID && Type && Remain) {
			TargetFind myTarget(0, 1, PID);
			int Player = (int)myTarget.getTarget();
			IChar IPlayer((void*)Player);
			if (IPlayer.IsOnline())
				IPlayer.Buff(Type, Remain, 0);
		}
		return 0;
	}

	if ((unsigned char)Data[2] == 53)
	{
		unsigned char Num = 0;
		int Packet = CPacket::xRead((char*)(void*)(Data + 3), "b", &Num);

		int PetLife = 0, IID = 0;

		for (unsigned char i = 0; i < Num; i++) {
			Packet = CPacket::xRead((void*)Packet, "dd", &IID, &PetLife);
			PetLifeCheck.replaceInsert(IID, PetLife);
			PetLife = 0, IID = 0;
		}

		return 0;
	}

	if ((unsigned char)Data[2] == 54)
	{
		const char* Lock = "";
		int IID = 0;
		CPacket::xRead((char*)(void*)(Data + 3), "ds", &IID, &Lock);

		if (IID && Lock && strlen(Lock)) {
			itemLockLock.Enter();
			ItemLockCheck.insert(std::pair<int, std::string>(IID, Lock));
			itemLockLock.Leave();
		}

		return 0;
	}

	if ((unsigned char)Data[2] == 55)
	{
		unsigned char Num = 0;
		int Packet = CPacket::xRead((char*)(void*)(Data + 3), "b", &Num);

		int IID = 0, ItemStat = 0;

		for (unsigned char i = 0; i < Num; i++) {
			Packet = CPacket::xRead((void*)Packet, "dd", &IID, &ItemStat);

			itemStat.Enter();
			GetItemStat.insert(std::pair<int, int>(IID, ItemStat));
			itemStat.Leave();

			IID = 0, ItemStat = 0;
		}

		return 0;
	}

	if ((unsigned char)Data[2] == 56)
	{
		int PID = 0, QuestID = 0, Clear = 0, QuestTime = 0, QuestRepeat = 0, MonsterCount = 0, Type = 0;
		CPacket::xRead((char*)(void*)(Data + 3), "dddddd", &PID, &QuestID, &Clear, &QuestTime, &QuestRepeat, &MonsterCount);
		if (PID && QuestID)
		{
			TargetFind myTarget(0, 1, PID);
			int Player = (int)myTarget.getTarget();
			IChar IPlayer((void*)Player);
			if (IPlayer.IsOnline()) {
				if (!Clear)
					IPlayer.UpdateBuff((BuffNames::DailyCountBegin + QuestID) % BuffNames::DailyCountEnd, BuffNames::BuffTime, -1);

				IPlayer.UpdateBuff((BuffNames::DailyQuestBegin + QuestID) % BuffNames::DailyQuestEnd, BuffNames::BuffTime, QuestTime);
				IPlayer.UpdateBuff((BuffNames::DailyRepeatBegin + QuestID) % BuffNames::DailyRepeatEnd, BuffNames::BuffTime, QuestRepeat);

			}
		}

		return 0;
	}

	if ((unsigned char)Data[2] == 62)
	{
		int PID = 0, Quest = 0, Monster = 0, Amount = 0;
		CPacket::xRead((char*)(void*)(Data + 3), "dddd", &PID, &Quest, &Monster, &Amount);
		if (PID && Quest && Amount)
		{
			TargetFind myTarget(0, 1, PID);
			int Player = (int)myTarget.getTarget();

			IChar IPlayer((void*)Player);
			if (IPlayer.IsOnline()) {
				IPlayer.UpdateBuff(BuffNames::MonsterQuestBegin + ((Monster + (Quest * 100)) % (BuffNames::MonsterQuestEnd - BuffNames::MonsterQuestBegin)), BuffNames::BuffTime, Amount);
				CPlayer::Write((void*)Player, 184, "ddd", Quest << 16, Monster, Amount);

			}
		}

		return 0;
	}

	if ((unsigned char)Data[2] == 57)
	{
		int PID = 0, BuffID = 0, Value = 0, SBKey = 0, SBName = 0, Time = 0;
		Interface<ITools> Tools;
		CPacket::xRead((char*)(void*)(Data + 3), "dddddd", &PID, &BuffID, &Value, &SBKey, &SBName, &Time);
		TargetFind myTarget(0, 1, PID);
		int Player = (int)myTarget.getTarget();
		IChar IPlayer((void*)Player);

		if (IPlayer.IsOnline()) {
			if (BuffID == 156 && Value) {
				if (IPlayer.IsBuff(BuffID)) {
					IPlayer.UpdateBuff(BuffID, BuffNames::BuffTime, Value);
					IPlayer.SetProperty(PlayerProperty::EmokEXP, Value);
				}
				else
					IPlayer.RemoveSavedBuff(BuffID);

				return 0;
			}

			if ((Time == BuffNames::BuffTime && BuffID >= 5000 && BuffID <= 5400 && Value > GetTickCount()) || (!(BuffID >= 5000 && BuffID <= 5400) && Time > (int)time(0))) {

				int RemainTime = Time == BuffNames::BuffTime ? Time : (Time - (int)time(0));
				if (!IPlayer.IsBuff(BuffID)) {
					IPlayer.Buff(BuffID, RemainTime, Value);
					IPlayer.SetBuffIcon(RemainTime * 1000, 0, SBKey, SBName);

					//	if (SBKey && SBName)
					// IPlayer.SetBuffIcon(RemainTime * 1000, 0, 10004, 10004);

					if (BuffID >= BuffNames::Extension1 && BuffID <= BuffNames::Extension3) {
						if (Value > (int)time(0)) {
							if (BuffID == BuffNames::Extension1) {
								CPlayer::Write(IPlayer.GetOffset(), 181, "dwd", IPlayer.GetID(), 501, Value - (int)time(0));
								CPlayer::Write(IPlayer.GetOffset(), 204, "d", 108);
							}
							if (BuffID == BuffNames::Extension2) {
								CPlayer::Write(IPlayer.GetOffset(), 181, "dwd", IPlayer.GetID(), 500, Value - (int)time(0));
								if (!IPlayer.IsBuff(BuffNames::Extension1))
									CPlayer::Write(IPlayer.GetOffset(), 204, "d", 72);
							}
							if (BuffID == BuffNames::Extension3) {
								CPlayer::Write(IPlayer.GetOffset(), 181, "dwd", IPlayer.GetID(), 499, Value - (int)time(0));
								if (!IPlayer.IsBuff(BuffNames::Extension1) && !IPlayer.IsBuff(BuffNames::Extension2))
									CPlayer::Write(IPlayer.GetOffset(), 204, "d", 36);
							}
						}
						else
							IPlayer.RemoveSavedBuff(BuffID);
					}

					if (BuffID == BuffNames::TriangularState && IPlayer.GetMap() == TBMap) {
						SendCreate mSendCreate = SendCreatePlayer.count(Player) ? SendCreatePlayer.findValue(Player) : SendCreate();
						mSendCreate.GState = Value;
						SendCreatePlayer.replaceInsert(Player, mSendCreate);

						IPlayer.Teleport(TBMap, IPlayer.GetX(), IPlayer.GetY(), IPlayer.GetZ());

						CPlayer::Write((void*)Player, 145, "dI", IPlayer.GetID(), __int64(Value));

						if (TriangularBattle::Active && TriangularBattle::QuitSize > 0)
							TriangularBattle::QuitSize--;
					}

					if (BuffID == BuffNames::NamePad && !PeaceEvil)
						CChar::WriteInSight((void*)Player, 0xFE, "ddd", 209, IPlayer.GetID(), Value);

					if (BuffID == BuffNames::EventMapQuest)
						IPlayer.ScreenTime(RemainTime - 10);
				}
			}
			else
				CDBSocket::Write(95, "ddddddd", 2, PID, BuffID, Value, SBKey, SBName, Time);
		}

		return 0;
	}



	if ((unsigned char)Data[2] == 58)
	{
		const char *Name = "";
		int PID = 0;
		Interface<ITools> Tools;
		//Tools->ParseData((char*)(void*)(Data + 3), "ds", &PID, &Name);

		/*if (PID && Name)
			FriendsName.insert(std::pair<int, std::string>(PID, Name));
			*/

		return 0;
	}

	if ((unsigned char)Data[2] == 59)
	{
		int PID = 0, Index = 0, Amount = 0, Prefix = 0, Storage = 0;
		Interface<ITools> Tools;
		//Tools->ParseData((char*)(void*)(Data + 3), "ddddd", &PID, &Index, &Amount, &Prefix, &Storage);
		CPacket::xRead((char*)(void*)(Data + 3), "ddddd", &PID, &Index, &Amount, &Prefix, &Storage);
		if (PID && Index && Amount) {
			TargetFind myTarget(0, 1, PID);
			int Player = (int)myTarget.getTarget();
			IChar IPlayer((void*)Player);

			if (IPlayer.IsOnline()) {
				if (GetInventorySize((int)IPlayer.GetOffset(), 0) < 60)
					CItem::InsertItem((int)IPlayer.Offset, 27, Index, Prefix, Amount, -1);
				else
					IPlayer.GiveReward(Index, Prefix, Amount, (Prefix == 256) ? 0 : -128, 0, 0, 0, 0, 0, 0, 0, "Thank you for your contribution!");

				if (Storage)
					CDBSocket::Write(97, "dddd", IPlayer.GetUID(), Index, Amount, Prefix);
				else
					CDBSocket::Write(97, "dddd", PID, Index, Amount, Prefix);
			}

		}
		return 0;
	}

	if ((unsigned char)Data[2] == 60)
	{
		const char *GuildName = "";
		int GID = 0;
		Interface<ITools> Tools;
		//Tools->ParseData((char*)(void*)(Data + 3), "ds", &GID, &GuildName);
		CPacket::xRead((char*)(void*)(Data + 3), "ds", &GID, &GuildName);
		if (GID && GuildName) {
			CWGID = GID;
			CWGuildName = GuildName;
			HuntingAddAll(GID, GuildName);
		}

		return 0;
	}

	if ((unsigned char)Data[2] == 61)
	{
		const char *WinnerName = "";
		//Tools->ParseData((char*)(void*)(Data + 3), "s", &WinnerName);
		CPacket::xRead((char*)(void*)(Data + 3), "s", &WinnerName);
		if (WinnerName)
			WCWinner = WinnerName;

		return 0;
	}

	if ((unsigned char)Data[2] == 64)
	{
		int PID = 0, Index = 0;

		CPacket::xRead((char*)(void*)(Data + 3), "dd", &PID, &Index);

		if (Index && RidingCollectionIndex.count(Index)) {
			TargetFind myTarget(0, 1, PID);
			int Player = (int)myTarget.getTarget();
			IChar IPlayer((void*)Player);

			if (IPlayer.IsOnline()) {
				int Collection = RidingCollectionIndex.find(Index)->second;
				if (RidingCollections.count(Collection) && IPlayer.IsBuff(5500 + Collection)) {
					RidingCollection ridingCollection = RidingCollections.find(Collection)->second;
					if (!CPlayer::FindItem((void*)Player, Index, 1))
						updateRidingCollection((void*)Player, Collection, 0, ridingCollection.Stat, ridingCollection.Rate);
				}
			}
		}
		return 0;
	}

	if ((unsigned char)Data[2] == 63)
	{
		if (!DailyLogin || DailyLogins.empty())
			return 0;

		int PID = 0, Day = 0;
		CPacket::xRead((char*)(void*)(Data + 3), "dd", &PID, &Day);

		Day = Day % DailyLogins.size();
		if (!Day)
			Day = DailyLogins.size();

		if (PID && Day) {
			IChar EAPlayer((void*)PID);
			if (EAPlayer.IsOnline() && DailyLogins.count(Day)) {
				DailyReward dailyReward = DailyLogins.find(Day)->second;
				if (dailyReward.ClaimHTML) {
					EAPlayer.OpenHTML(dailyReward.ClaimHTML);
					EAPlayer.Buff(BuffNames::RewardClaim, BuffNames::BuffTime, Day);
					return 0;
				}

				std::vector<std::string> Items_ = explode(",", dailyReward.Items);
				std::vector<std::string> iAmounts_ = explode(",", dailyReward.Amount);
				if (Items_.size() == iAmounts_.size()) {
					for (int i = 0; i < Items_.size(); i++) {
						int Index = String2Int(Items_[i]);
						int Amount = String2Int(iAmounts_[i]);
						if (Index && Amount) {
							int Prefix = (DailyLoginBound == 1) ? 256 : 0;
							if (GetInventorySize((int)EAPlayer.GetOffset(), 0) < 60)
								CItem::InsertItem((int)EAPlayer.GetOffset(), 27, Index, Prefix, Amount, -1);
							else
								EAPlayer.GiveReward(Index, Prefix, Amount, 0, 0, 0, 0, 0, 0, 0, 0, "Here is your Daily Reward.");
						}
					}
				}
				int Honor = dailyReward.Honor;
				int Reward = dailyReward.Reward;
				int HTML = dailyReward.HTML;
				if (Honor || Reward)
					EAPlayer.SetHonor(Honor, Reward, 0, 0, 0, 0, 0, 0, 0, 0);
				if (HTML)
					EAPlayer.OpenHTML(HTML);

				CDBSocket::Write(100, "dddddddss", 2, EAPlayer.GetUID(), PID, String2Int(Time::GetMonth()), String2Int(Time::GetDay()), DailyLoginLimit, IPCheck, EAPlayer.GetIP().c_str(), EAPlayer.GetHWID().c_str());
			}
		}
		return 0;
	}

	if ((unsigned char)Data[2] == 65)
	{
		int PID = 0;
		CPacket::xRead((char*)(void*)(Data + 3), "d", &PID);
		TargetFind myTarget(0, 1, PID);
		int Player = (int)myTarget.getTarget();
		IChar IPlayer((void*)Player);
		if (IPlayer.IsOnline()) {
			if (Starters.count(IPlayer.GetClass())) {
				StarterClass starter = Starters.find(IPlayer.GetClass())->second;
				if (starter.CoordX && starter.CoordY)
					IPlayer.Teleport(starter.Map, starter.CoordX, starter.CoordY);

				if (starter.EXP)
					(*(int(__cdecl **)(int, signed int, signed int, unsigned __int64, unsigned __int64))(*(DWORD *)IPlayer.GetOffset() + 88))((int)IPlayer.GetOffset(), 25, 1, (unsigned __int64)starter.EXP, HIDWORD(starter.EXP));

				if (starter.HTML)
					IPlayer.OpenHTML(starter.HTML);

				if (!starter.Msg.empty() && IPlayer.IsValid()) {
					size_t sizeOf = starter.Msg.find("$name");
					if (sizeOf != std::string::npos)
						starter.Msg.replace(sizeOf, sizeof("$name") - 1, IPlayer.GetName());

					int textColor = 9;
					int messageType = 2;
					RewardMessage reward;
					reward.message = starter.Msg;
					reward.textColor = textColor;
					reward.messageType = messageType;

					PlayerRewardNotice.push_back(reward);

					std::string avatar = Avatar;
					std::string playerName = std::string(IPlayer.GetName());
					std::string url = StarterWebhook;
					SendWebhookMessage(url, starter.Msg.c_str(), avatar.c_str(), std::string(playerName));

				}
			}

			if (StarterItems.count(IPlayer.GetClass())) {
				std::vector<Items> items = StarterItems.find(IPlayer.GetClass())->second;
				int NumberOfItems = items.size();

				if (CPlayer::GetInvenSize((int)IPlayer.GetOffset()) < IPlayer.MaxInventorySize() - NumberOfItems) {
					for (int i = 0; i < NumberOfItems; i++) {
						Items t = items[i];

						int Item = CItem::CreateItem(t.Index, t.Prefix, t.Amount, -1);

						if (Item) {
							IItem xItem((void*)Item);

							int Info = t.Info;

							if (t.Dss)
								*(DWORD*)(Item + 84) = t.Dss;

							if (t.Mix)
								Info += t.Mix;

							if (t.Bof)
								Info += 2097152;

							*(DWORD*)(Item + 48) = Info;

							if (xItem.HighMemory()) {
								if (t.Def)
									*(DWORD*)(Item + 108) = t.Def;
								if (t.Eva)
									*(DWORD*)(Item + 116) = t.Eva;

								if (t.Attack)
									*(DWORD*)(Item + 100) = t.Attack;
								if (t.Magic)
									*(DWORD*)(Item + 104) = t.Magic;
								if (t.Toa)
									*(DWORD*)(Item + 112) = t.Toa;
								if (t.Upgrade)
									*(DWORD*)(Item + 124) = t.Upgrade;
							}

							if (CPlayer::InsertItem(IPlayer.GetOffset(), 7, Item) == 1)
							{
								if (xItem.HighMemory() && (t.Attack || t.Magic)) {
									CDBSocket::Write(17, "ddbbb", *(DWORD *)(Item + 36), *(DWORD *)(Item + 32), 27, *(DWORD*)(Item + 100), 0);
									CDBSocket::Write(17, "ddbbb", *(DWORD *)(Item + 36), *(DWORD *)(Item + 32), 28, *(DWORD*)(Item + 104), 0);
									CDBSocket::Write(17, "ddbbb", *(DWORD *)(Item + 36), *(DWORD *)(Item + 32), 9, *(DWORD*)(Item + 112), 0);
									CDBSocket::Write(28, "ddbb", *(DWORD *)(Item + 36), *(DWORD *)(Item + 32), 2, *(DWORD*)(Item + 124));
								}

								if (t.Type == 1)
									CItemWeapon::PutOn(CPlayer::FindItem(IPlayer.GetOffset(), t.Index, 1), (int)IPlayer.GetOffset());
								else if (t.Type == 2)
									CItemDefense::PutOn(CPlayer::FindItem(IPlayer.GetOffset(), t.Index, 1), (int)IPlayer.GetOffset());
								else if (t.Type == 3)
									CItemOrnament::PutOn(CPlayer::FindItem(IPlayer.GetOffset(), t.Index, 1), (int)IPlayer.GetOffset());
							}
							else
								CBase::Delete((void*)Item);
						}
					}
				}
			}
		}
		return 0;
	}

	/*
	if ((unsigned char)Data[2] == 66)
	{
	int IID = 0, Index = 0, Prefix = 0, MaxEnd = 0, CurEnd = 0, Info = 0, Num = 0, XHit = 0, XDefense = 0, XAttack = 0, XMagic = 0, XDodge = 0, Protect = 0, UpgrLevel = 0, SetGem = 0, ItemStat = 0;

	CPacket::xRead((void*)(Data + 3), "dddddddddddddddd", &IID, &Index, &MaxEnd, &CurEnd, &Info, &Num, &XHit, &XDefense, &XAttack, &XMagic, &XDodge, &Protect, &UpgrLevel, &SetGem, &Prefix, &ItemStat);

	if (IID != 0 && Index)
	insertMail(IID, Index, MaxEnd, CurEnd, Info, Num, XHit, XDefense, XAttack, XMagic, XDodge, Protect, UpgrLevel, SetGem, Prefix, ItemStat);

	return 0;
	}
	*/

	if ((unsigned char)Data[2] == 67)
	{
		const char *PlayerName = "";
		int GID = 0, PID = 0, Amount = 0;

		CPacket::xRead((char*)(void*)(Data + 3), "ddds", &PID, &GID, &Amount, &PlayerName);
		if (GID && PID) {
			GuildTopDonator donator = GuildTopDonator();
			donator.name = PlayerName;
			donator.Amount = Amount;
			donator.PID = PID;
			std::vector<GuildTopDonator> tops = std::vector<GuildTopDonator>();
			if (GuildTopDonatorList.count(GID))
				tops = GuildTopDonatorList.findValue(GID);

			tops.push_back(donator);
			GuildTopDonatorList.replaceInsert(GID, tops);
		}

		return 0;
	}

	if ((unsigned char)Data[2] == 68)
	{
		int PID = 0, Index = 0, Amount = 0, Class = 0, Prefix = 0, Info = 0, Attack = 0, Magic = 0, TOA = 0, Upgrade = 0, Defense = 0, Evasion = 0, Endurance = 0, ItemStat = 0;
		const char* Message = "";

		CPacket::xRead((char*)(void*)(Data + 3), "dddddddddddddds", &PID, &Index, &Amount, &Class, &Prefix, &Info, &Attack, &Magic, &TOA, &Upgrade, &Defense, &Evasion, &Endurance, &ItemStat, &Message);
		TargetFind myTarget(0, 1, PID);
		int Player = (int)myTarget.getTarget();
		IChar IPlayer((void*)Player);
		if (IPlayer.IsOnline() && (Class == IPlayer.GetPID() || Class == 5))
			IPlayer.GiveReward(Index, Prefix, Amount, Info, Attack, Magic, TOA, Upgrade, Defense, Evasion, Endurance, Message);

		return 0;
	}

	if ((unsigned char)Data[2] == 71)
	{
		int PID = 0;
		const char *Message = "";
		Interface<ITools> Tools;
		CPacket::xRead((char*)(void*)(Data + 3), "ds", &PID, &Message);
		TargetFind myTarget(0, 1, PID);
		int Player = (int)myTarget.getTarget();
		IChar IPlayer((void*)Player);

		if (IPlayer.IsOnline())
		{
			string loginMsg = "Dear " + (std::string)IPlayer.GetName() + ", Welcome back to " + thisServerName + ", enjoy the game, dont forget to follow the rules and play fair! You have last logged in at: " + std::string(Message);
			IPlayer.SystemMessage(loginMsg.c_str(), TEXTCOLOR_GREEN);

			//	IPlayer.BoxMsg("You have last logged in at: " + std::string(Message));
		}

		return 0;
	}



	if ((unsigned char)Data[2] == 72)
	{
		int PID = 0;
		int RemainingTime = 0;
		Interface<ITools> Tools;
		CPacket::xRead((char*)(void*)(Data + 3), "dd", &PID, &RemainingTime);
		TargetFind myTarget(0, 1, PID);
		int Player = (int)myTarget.getTarget();
		IChar IPlayer((void*)Player);

		if (IPlayer.IsOnline())
			IPlayer.GiveReward(HouseReward, 0, HouseRewardAmount, 128, 0, 0, 0, 0, 0, 0, 0, "Congratulations Warrior! Your house has won the weekly reward.");
		else
			insertOfflineReward(PID, HouseReward, HouseRewardAmount, PID, 0, 128, 0, 0, 0, 0, 0, 0, 0, 0, "Congratulations Warrior! Your house has won the weekly reward..");

		return 0;
	}

	if ((unsigned char)Data[2] == 73)
	{
		int PID = 0;
		int QuestID = 0, Normal = 0, Mini = 0, Instance = 0;
		Interface<ITools> Tools;
		CPacket::xRead((char*)(void*)(Data + 3), "ddddd", &PID, &QuestID, &Normal, &Mini, &Instance);
		TargetFind myTarget(0, 1, PID);
		int Player = (int)myTarget.getTarget();
		IChar IPlayer((void*)Player);

		if (IPlayer.IsOnline())
		{
			if (DutyQuest.count(QuestID)){
				int questIndex = (QuestID << 16) + 1;

				IPlayer.Buff(BuffNames::DailyDuty + QuestID, BuffNames::BuffTime, QuestID);
				IPlayer.Buff(BuffNames::NormalDuty, BuffNames::BuffTime, Normal);
				IPlayer.Buff(BuffNames::MiniBoss, BuffNames::BuffTime, Mini);
				IPlayer.Buff(BuffNames::InstanceDuty, BuffNames::BuffTime, Instance);

				CPlayer::Write(IPlayer.GetOffset(), 184, "ddd", questIndex, 5000, Normal);
				CPlayer::Write(IPlayer.GetOffset(), 184, "ddd", questIndex, 5001, Mini);
				CPlayer::Write(IPlayer.GetOffset(), 184, "ddd", questIndex, 5002, Instance);
			}

		}

		return 0;
	}

	if ((unsigned char)Data[2] == 74)
	{
		int PID = 0;
		int Battlepasslvl = 0, BattlepassEXP = 0, CurrentB = 0, MaxB = 0, CurrentPB = 0;
		CPacket::xRead((char*)(void*)(Data + 3), "dddddd", &PID, &Battlepasslvl, &BattlepassEXP, &CurrentB, &MaxB, &CurrentPB);

		TargetFind myTarget(0, 1, PID);
		int Player = (int)myTarget.getTarget();
		IChar IPlayer((void*)Player);
		if (IPlayer.IsOnline()){
			IPlayer.SetProperty(PlayerProperty::CurrentBReward, CurrentB);
			IPlayer.SetProperty(PlayerProperty::MaxBReward, MaxB);
			IPlayer.SetProperty(PlayerProperty::CurrentPBReward, CurrentPB);
			IPlayer.SetProperty(PlayerProperty::BattlepassLv, Battlepasslvl);

			CPlayer::Write((void*)Player, 0xFE, "ddddd", 254, Battlepasslvl, BattlepassEXP, CurrentB, CurrentPB);
		}
		//		IPlayer.SystemMessage("Executed " + Int2String(Battlepasslvl) + " " + Int2String(BattlepassEXP) + " " + Int2String(CurrentB) + " " + Int2String(MaxB) + " " + Int2String(CurrentPB), TEXTCOLOR_GREEN);
		return 0;
	}

	if ((unsigned char)Data[2] == 70)
	{
		int PID = 0, RebornID = 0;

		CPacket::xRead((char*)(void*)(Data + 3), "dd", &PID, &RebornID);

		TargetFind myTarget(0, 1, PID);
		int Player = (int)myTarget.getTarget();
		IChar IPlayer((void*)Player);

		if (RebornID) {
			IPlayer.SetProperty(PlayerProperty::Reborn, RebornID);
			if (Reborns.count(RebornID)) {
				int Value = Reborns.find(RebornID)->second.NamePad;
				if (Value) {
					IPlayer.UpdateBuff(BuffNames::NamePad, BuffNames::BuffTime, Value);
					CChar::WriteInSight((void*)Player, 0xFE, "ddd", 209, IPlayer.GetID(), Value);
				}
			}
		}

		return 0;
	}

	return CDBSocket::RealProcess(Data);
}