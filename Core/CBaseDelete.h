int reloadingM = 0; 
void insertOfflineReward(int PID, int Index, int Amount, int Class, int Prefix, int Info, int Attack, int Magic, int TOA, int Upgrade, int Defense, int Evasion, int Endurance, int ItemStat, const char* Message) {
	CDBSocket::Write(115, "dddddddddddddds", PID, Index, Amount, Class, Prefix, Info, Attack, Magic, TOA, Upgrade, Defense, Evasion, Endurance, ItemStat, Message);
}


void SendDiscordMessage(const std::string& webhookURL, const std::string& message) {
	CURL* curl;
	CURLcode res;

	curl = curl_easy_init();
	if (curl) {
		curl_easy_setopt(curl, CURLOPT_URL, webhookURL.c_str());
		curl_easy_setopt(curl, CURLOPT_POST, 1);

		std::string jsonMessage = "{ \"content\": \"" + message + "\" }";
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, jsonMessage.c_str());

		res = curl_easy_perform(curl);
		if (res != CURLE_OK) {
			CConsole::Red("Failed to send message to Discord: %s\n", curl_easy_strerror(res));
		}

		curl_easy_cleanup(curl);
	}
}

bool CheckRangeProtection(int Player, signed int SkillID, int Target, int pPacket, int pPos)
{
	IChar IPlayer((void*)Player);
	IChar ITarget((void*)Target);

	int maxrange = 0;
	if (CheckRangeConfig.count(SkillID + (IPlayer.GetClass() * 100)))
		maxrange = CheckRangeConfig.find(SkillID + (IPlayer.GetClass() * 100))->second.maxRange;
	else
	{
		if (IPlayer.GetClass() == 0)
			maxrange = KRange;
		else if (IPlayer.GetClass() == 1)
			maxrange = MRange;
		else if (IPlayer.GetClass() == 2)
			maxrange = ARRange;
		else if (IPlayer.GetClass() == 3)
			maxrange = TRange;
		else if (IPlayer.GetClass() == 4)
			maxrange = SRange;
	}

	int Around = IPlayer.GetObjectListAround(maxrange);
	bool isValidRange = false;

	while (Around)
	{
		IChar Object((void*)CBaseList::Offset((void*)Around));

		if (ITarget.GetOffset())
		{
			if (ITarget.GetOffset() == Object.GetOffset())
			{
				isValidRange = true;
				break;
			}
		}
		else {

			if (Object.GetOffset() && IPlayer.GetOffset() != Object.GetOffset())
			{
				isValidRange = true;
				break; // No need to check further
			}
		}

		Around = CBaseList::Pop((void*)Around);
	}

	return isValidRange;

}

void ProcessNPCList(bool showNPC) {
	for (auto i = 1; i < 100000; i++) {
		int NPC = CNPC::FindNPC((char)i);
		IChar INPC((void*)NPC);
		if (NPC) {
			if (showNPC)
				CPlayer::WriteAll(52, "dwbdddwId", *(DWORD *)(NPC + 28), *(DWORD*)((int)NPC + 448), *(DWORD *)(NPC + 452), INPC.GetX(), INPC.GetY(), INPC.GetZ(), *(DWORD *)(NPC + 348), (unsigned __int64)*(DWORD *)(NPC + 280), 0);
			else
				CPlayer::WriteAll(57, "d", *(DWORD *)(NPC + 28));
		}
		CIOObject::Release((void*)NPC);
	}
}

void DeleteNPCList() {
	ProcessNPCList(false);
}

void ShowNPCList() {
	ProcessNPCList(true);
}

void UpdateAutoMission(void* Player, void* Monster) {
	IChar IPlayer(Player);
	IChar ITarget(Monster);
	if (IPlayer.IsValid() && ITarget.IsValid() && IPlayer.GetType() == 0 && ITarget.GetType() == 1) {
		int MissionMonsterIndex = ITarget.GetMobIndex();

		for (std::unordered_map<int, MissionInfo>::const_iterator it = MissionQuests.begin(); it != MissionQuests.end(); ++it) {
			const MissionInfo& mission = it->second;
			if (mission.Monster == MissionMonsterIndex) {
				int currentMission = it->first;
				int nextMission = mission.nextmission;
				int questIndex = (currentMission << 16) + 1;
				int missionMonsterAmount = mission.Amount;
				int isNewCurrentMission = IPlayer.GetBuffValue(BuffNames::CurrentMissionBuff + currentMission);
				int isPreviousMission = IPlayer.GetBuffValue(BuffNames::CurrentMissionBuff + (currentMission - 1));
				int isNextMission = IPlayer.GetBuffValue(BuffNames::CurrentMissionBuff + (currentMission + 1));

				bool isQuest = (CPlayer::CheckQuestFlag((int)IPlayer.GetOffset(), questIndex) == true);
				int isQuestClear = CPlayer::CheckQuestClear((int)IPlayer.GetOffset(), static_cast<char>(currentMission));
				// if player isnt quest and isnt next quest
				if ((currentMission != 0 && !isQuest && !isNewCurrentMission))
					continue;

				// Check if the player has completed the previous mission and isn't in next mission
				if ((currentMission != 0 && isPreviousMission && !isNewCurrentMission))
					continue;

				if ((currentMission != 0 && !isQuestClear && !isNextMission && IPlayer.GetBuffValue(BuffNames::MissionBuff) <= missionMonsterAmount)) {
					int missionProgress = IPlayer.GetBuffValue(BuffNames::MissionBuff);

					if (!IPlayer.IsBuff(BuffNames::MissionBuff)) {
						IPlayer.SaveBuff(BuffNames::MissionBuff, 86400, 0, 0, 0);

					}

					missionProgress++;
					IPlayer.SaveBuff(BuffNames::MissionBuff, 86400, missionProgress, 0, 0);
					// Write the current mission progress to the client
					CPlayer::Write(IPlayer.GetOffset(), 184, "ddd", questIndex, ITarget.GetMobIndex(), missionProgress);

					if (missionProgress >= missionMonsterAmount) {
						IPlayer.EndQuestMission(currentMission, 0, 0, 1);
						IPlayer.systemReward(mission.rewardID);
						missionProgress = 0;
						if (nextMission != 0) {
							IPlayer.SaveBuff(BuffNames::MissionBuff, 86400, 0, 0, 0);
							IPlayer.StartQuest(nextMission, 0, 0, 0);
							CQuest::Start(nextMission << 16 | 1, (int)IPlayer.GetOffset());
							if (PeaceEvil)
							IPlayer.AddHousePoints(2);
							IPlayer.SaveBuff(BuffNames::CurrentMissionBuff + nextMission, 86400, nextMission, 0, 0);
							IPlayer.SaveBuff(BuffNames::CurrentMissionBuff + currentMission, 86400, currentMission, 0, 0);
						}
					}
				}
			}
		}
	}
}

void UpdateAutoMissionItem(void* Player) {

	IChar IPlayer(Player);
	for (std::unordered_map<int, MissionInfo>::const_iterator it = MissionQuests.begin(); it != MissionQuests.end(); ++it) {
		const MissionInfo& mission = it->second;
	//	IItem IItem((void*)mission.Item);
	//	int itemAmount = IItem.GetAmount();
		int ItemFound = CPlayer::FindItem(IPlayer.GetOffset(), mission.Item, mission.itemAmount);
		if (ItemFound) {
			int currentMission = it->first;
			int nextMission = mission.nextmission;
			int questIndex = (currentMission << 16) + 1;
			int isNewCurrentMission = IPlayer.GetBuffValue(BuffNames::CurrentMissionBuff + currentMission);
			int isPreviousMission = IPlayer.GetBuffValue(BuffNames::CurrentMissionBuff + (currentMission - 1));
			int isNextMission = IPlayer.GetBuffValue(BuffNames::CurrentMissionBuff + (currentMission + 1));

			bool isQuest = (CPlayer::CheckQuestFlag((int)IPlayer.GetOffset(), questIndex) == true);
			int isQuestClear = CPlayer::CheckQuestClear((int)IPlayer.GetOffset(), static_cast<char>(currentMission));
			// if player isnt quest and isnt next quest
			if ((currentMission != 0 && !isQuest && !isNewCurrentMission))
				continue;

			// Check if the player has completed the previous mission and isn't in next mission
			if ((currentMission != 0 && isPreviousMission && !isNewCurrentMission))
				continue;

			if ((currentMission != 0 && !isQuestClear && !isNextMission && ItemFound)) {

				if (ItemFound) {
					IPlayer.EndQuestMission(currentMission, 0, 0, 1);
					IPlayer.systemReward(mission.rewardID);
					if (nextMission != 0) {
						IPlayer.StartQuest(nextMission, 0, 0, 0);
						if (PeaceEvil)
							IPlayer.AddHousePoints(2);
						IPlayer.SaveBuff(BuffNames::CurrentMissionBuff + nextMission, 86400, nextMission, 0, 0);
						IPlayer.SaveBuff(BuffNames::CurrentMissionBuff + currentMission, 86400, currentMission, 0, 0);
						IPlayer.RemoveItem(mission.Item, mission.itemAmount);
						CPlayer::RemoveItem(IPlayer.GetOffset(), 9, mission.Item, mission.itemAmount);
						if (mission.teleportX)
						IPlayer.Teleport(mission.teleportMap, mission.teleportX, mission.teleportY);
					}
				}
			}
		}
	}
}


void updateDailyQuestKill(int MonsterIndex, IChar EAPlayer) {

	std::vector<MonsterDailyQuest> Quests = MonsterQuests.find(MonsterIndex)->second;
	MonsterDailyQuest dailyQuest = MonsterDailyQuest();
	dailyQuest.Quest = 0;
	dailyQuest.Amount = 0;
	int OldIndex = MonsterIndex;
	ConfigDailyQuest dQuest = ConfigDailyQuest();
	int diff = BuffNames::MonsterQuestEnd - BuffNames::MonsterQuestBegin;

	if (!Quests.empty()) {

		int killAmount = 0;
		for (int i = 0; i < Quests.size(); i++) {
			MonsterDailyQuest mDailyQ = Quests[i];
			if (mDailyQ.MainIndex)
				MonsterIndex = mDailyQ.MainIndex;
			else
				MonsterIndex = OldIndex;

			killAmount = EAPlayer.GetBuffValue(BuffNames::MonsterQuestBegin + ((MonsterIndex + (mDailyQ.Quest * 100)) % diff));

			if (killAmount >= maxAmountQ)
				killAmount -= maxAmountQ;

			if (killAmount < mDailyQ.Amount && EAPlayer.GetBuffValue((BuffNames::DailyCountBegin + mDailyQ.Quest) % BuffNames::DailyCountEnd) == -1) {

				dQuest = DailyQuest.find(mDailyQ.Quest)->second;

				if (EAPlayer.IsParty() && dQuest.Party == 0)
					continue;

				if (!EAPlayer.IsParty() && dQuest.Party == 1)
					continue;


				dailyQuest = mDailyQ;
				break;
			}
		}

		int Quest = dailyQuest.Quest;

		if (!Quest)
			return;

		int eachAmount = (killAmount + 1);

		if (eachAmount <= dailyQuest.Amount) {
			EAPlayer.UpdateBuff(BuffNames::MonsterQuestBegin + ((MonsterIndex + (Quest * 100)) % diff), BuffNames::BuffTime, eachAmount + maxAmountQ);
			CPlayer::Write(EAPlayer.GetOffset(), 184, "ddd", Quest << 16, MonsterIndex, eachAmount);
		}

		if (eachAmount >= dailyQuest.Amount) {
			int TotalAmount = 0;

			for (int i = 0; i < dQuest.Monsters.size(); i++) {
				int Index = String2Int(dQuest.Monsters[i]);
				if (dQuest.Type == 1) {
					std::vector<std::string> MonstersPerGroup_ = explode("-", dQuest.Monsters[i]);
					Index = String2Int(MonstersPerGroup_[0]);
				}

				if (Index) {
					int AmountM = EAPlayer.GetBuffValue(BuffNames::MonsterQuestBegin + ((Index + (Quest * 100)) % diff));

					if (AmountM >= maxAmountQ)
						AmountM -= maxAmountQ;

					TotalAmount += AmountM;
				}
			}

			if (TotalAmount >= dQuest.MobAmount) {
				int Repeat = (EAPlayer.GetBuffValue((BuffNames::DailyRepeatBegin + Quest) % BuffNames::DailyRepeatEnd)) + 1;

				int nTime = (int)time(0) + dQuest.Time;

				EAPlayer.UpdateBuff((BuffNames::DailyRepeatBegin + Quest) % BuffNames::DailyRepeatEnd, BuffNames::BuffTime, Repeat);
				EAPlayer.UpdateBuff((BuffNames::DailyQuestBegin + Quest) % BuffNames::DailyQuestEnd, BuffNames::BuffTime, nTime);
				EAPlayer.UpdateBuff((BuffNames::DailyCountBegin + Quest) % BuffNames::DailyCountEnd, BuffNames::BuffTime, 0);

				for (int i = 0; i < dQuest.Monsters.size(); i++) {
					int Index = String2Int(dQuest.Monsters[i]);
					if (dQuest.Type == 1) {
						std::vector<std::string> MonstersPerGroup_ = explode("-", dQuest.Monsters[i]);
						Index = String2Int(MonstersPerGroup_[0]);
					}

					if (Index) {
						EAPlayer.CancelBuff(BuffNames::MonsterQuestBegin + ((Index + (Quest * 100)) % diff));
						CPlayer::Write(EAPlayer.GetOffset(), 184, "ddd", Quest << 16, Index, 0);
					}
				}

				EAPlayer.DailyQuestUpdate(Quest, -1, 0);
				EAPlayer.EndQuest(Quest, nTime, Repeat, 1);

				if (!dQuest.Item.empty() || dQuest.Exp) {
					for (int i = 0; i < dQuest.Item.size(); i++) {
						int Index = String2Int(dQuest.Item[i]);
						int Amount = String2Int(dQuest.ItemAmount[i]);
						if (Index && Amount)
							EAPlayer.InsertItem(Index, DQBound ? 256 : 0, Amount);
					}
					if (dQuest.Exp) {
						if (DQuestGap)
							(*(int(__cdecl **)(int, signed int, signed int, unsigned __int64, unsigned __int64))(*(DWORD *)EAPlayer.GetOffset() + 88))((int)EAPlayer.GetOffset(), 25, 1, (unsigned __int64)dQuest.Exp, HIDWORD(dQuest.Exp));
						else
							CPlayer::UpdateProperty((int)EAPlayer.GetOffset(), 25, 1, dQuest.Exp);
					}
				}

				int Honor = dQuest.Honor;
				int RewardPt = dQuest.RewardPt;
				if (Honor || RewardPt)
					EAPlayer.SetHonor(Honor, RewardPt, 0, 0, 0, 0, 0, 0, 0, 0);
				if (PeaceEvil && dQuest.HousePoints)
					EAPlayer.AddHousePoints(dQuest.HousePoints);
			}
		}
	}
}

void AddHouseReward(int Time)
{
	int TotalTime = Time;
	int FutureTime = (int)time(0) + TotalTime;

	if (isPeaceEvilMode()) {
		CDBSocket::Write(71, "d", FutureTime);
	}
}

void SpawnEventMap(eventMap questEvent, int spawnIndex, int Timeleft) {
	int Quest = questEvent.Quest;
	std::vector<std::string> monsters = questEvent.monsters;
	if (!monsters.empty()) {
		std::vector<std::string> MPG = explode("-", questEvent.monsters[spawnIndex]);
		std::vector<std::string> APG = explode("-", questEvent.amounts[spawnIndex]);
		std::vector<std::string> XPG = explode("-", questEvent.X.size() > spawnIndex ? questEvent.X[spawnIndex] : questEvent.X[0]);
		std::vector<std::string> YPG = explode("-", questEvent.Y.size() > spawnIndex ? questEvent.Y[spawnIndex] : questEvent.Y[0]);
		int TotalAmount = 0;
		if (MPG.size() == APG.size() && XPG.size() == YPG.size()) {
			eventMapMonster evMonster = eventMapMonster();
			evMonster.Quest = Quest;
			evMonster.CIndex = spawnIndex;
			for (int i = 0; i < MPG.size(); i++) {
				int X = String2Int(XPG.size() > i ? XPG[i] : XPG[0]);
				int Y = String2Int(YPG.size() > i ? YPG[i] : YPG[0]);
				int Index = String2Int(MPG[i]);
				int Amount = String2Int(APG[i]);
				for (int j = 0; j < Amount; j++)
					EventMapsMobsOn.replaceInsert(Summon(0, 0, X + CTools::Rate(-100, 100), Y + CTools::Rate(-100, 100), Index, 1, 0, 0, Timeleft, 0), evMonster);
				TotalAmount += Amount;
			}
		}
		EventMapsOn.replaceInsert(Quest, TotalAmount);
	}
}

void __fastcall CBaseDelete(void *Object, void *edx)
{
	IChar Check(Object);
	int Type = 2, IID = 0, index = 0, MobIndex = 0, Offset = 0, PID = 0, PIDItem = 0, Erase = (int)Object; std::string DeleteIP = "error";
	int Def = 0;
	if (Check.IsOnline())
		Type = Check.GetType();

	if (Type == 0 && Check.IsOnline())
	{
		PID = Check.GetPID();

		if (TriangularBattle::Active && Check.GetBuffValue(BuffNames::TriangularType))
			QuitTBPlayer(Check);

		int TargetID = Check.GetBuffValue(BuffNames::BetOpponent);
		if (TargetID) {
			TargetFind myTarget(0, 0, TargetID);
			IChar ITarget(myTarget.getTarget());
			int Index = PID * ITarget.GetPID();
			if (BetItems.count(Index)) {
				std::vector<BetTrade> Items = BetItems.find(Index)->second;
				if (ITarget.IsOnline()) {
					for (int i = 0; i < (int)Items.size(); i++) {
						BetTrade Item = Items[i];
						IItem IItem((void*)Item.Item);

						if (IItem.Exists()) {
							if (Item.Item) {
								CIOObject::AddRef(Item.Item);

								if (CPlayer::InsertItem(ITarget.GetOffset(), 10, Item.Item) != 1)
									CBase::Delete((void*)Item.Item);

								CIOObject::Release((void*)Item.Item);
							}
						}
					}
				}
				BetItems.erase(Index);
			}
		}

		if (Protect32::Active == true && Protect32::Prayer == 1 && Check.GetGID() == Check.GetPID() && Check.GetGID() == Protect32::GuildFirst)
		{
			Protect32::Prayer = 0;
			Protect32::BluePrayerTime = 0;
		}

		if (Protect32::Active == true && Protect32::Prayer == 2 && Check.GetGID() == Check.GetPID() && Check.GetGID() == Protect32::GuildSecond)
		{
			Protect32::Prayer = 0;
			Protect32::RedPrayerTime = 0;
		}

		if (Check.IsBuff(BuffNames::Extension1) || Check.IsBuff(BuffNames::Extension2) || Check.IsBuff(BuffNames::Extension3)) {
			CPlayer::Write(Check.GetOffset(), 204, "d", 0);
			CPlayer::Write(Check.GetOffset(), 181, "dwd", Check.GetID(), 499, 0);
			CPlayer::Write(Check.GetOffset(), 181, "dwd", Check.GetID(), 500, 0);
			CPlayer::Write(Check.GetOffset(), 181, "dwd", Check.GetID(), 501, 0);
		}

		int diff = BuffNames::MonsterQuestEnd - BuffNames::MonsterQuestBegin;

		for (auto x = MonsterQuests.begin(); x != MonsterQuests.end(); x++)
		{
			std::vector<MonsterDailyQuest> Quests = x->second;
			int Index = x->first;

			for (auto y = Quests.begin(); y != Quests.end();y++) {
				if (y->MainIndex)
					Index = y->MainIndex;
				else
					Index = x->first;

				if (Check.GetBuffValue((BuffNames::DailyCountBegin + y->Quest) % BuffNames::DailyCountEnd) == -1) {

					ConfigDailyQuest dQuest = DailyQuest.find(y->Quest)->second;

					if (Check.IsParty() && dQuest.Party == 0)
						continue;

					if (!Check.IsParty() && dQuest.Party == 1)
						continue;

					int eachAmount = Check.GetBuffValue(BuffNames::MonsterQuestBegin + ((Index + (y->Quest * 100)) % diff));

					if (eachAmount > maxAmountQ)
						Check.DailyQuestUpdate(y->Quest, Index, eachAmount - maxAmountQ);

					break;
				}
			}
		}
		int RIID = Check.GetBuffValue(BuffNames::RidingIID);
		if (RIID) {
			itemStat.Enter();
			int ItemStat = GetItemStat.count(RIID) ? GetItemStat.find(RIID)->second : 0;
			itemStat.Leave();
			if (ItemStat) {
				int Satiety = ItemStat / 100;
				if (Satiety) {
					ItemStat -= (Satiety * 100);
					int PSasiety = Check.GetBuffValue(BuffNames::Satiety);
					if (PSasiety)
						Satiety = PSasiety;
					itemStat.Enter();
					GetItemStat[RIID] = ItemStat + (100 * Satiety);
					itemStat.Leave();
					CDBSocket::Write(90, "dd", ItemStat + (100 * Satiety), RIID);
				}
			}
		}

		int SoulPocket = Check.GetBuffValue(BuffNames::SoulPocketIID);
		if (SoulPocket) {
			Check.UpdateBuff(BuffNames::SoulPocketIID, BuffNames::BuffTime, 0);
			int bf = Check.GetBuffValue(BuffNames::SoulPocketAmount);
			itemStat.Enter();
			GetItemStat[SoulPocket] = bf;
			itemStat.Leave();
			CDBSocket::Write(90, "dd", bf, SoulPocket);
			Check.UpdateBuff(BuffNames::SoulPocketAmount, BuffNames::BuffTime, 0);
		}

		for (int i = 5000; i <= 5400; i++) {
			int value = Check.GetBuffValue(i);
			if (value > GetTickCount())
				CDBSocket::Write(95, "ddddddd", 1, PID, i, value, 0, 0, BuffNames::BuffTime);
		}

		int Time = Check.GetBuffValue(BuffNames::TrainingTime);
		if (Time)
			CDBSocket::Write(95, "ddddddd", 1, Check.GetPID(), BuffNames::TrainingTime, Time, 0, 0, (int)time(0) + BuffNames::BuffTime);

		if (PSActive) {
			int Limit = Check.GetBuffValue(BuffNames::AssaPointsLimit);
			if(Limit)
				CDBSocket::Write(95, "ddddddd", 1, Check.GetPID(), BuffNames::AssaPointsLimit, Limit, 0, 0, (int)time(0) + Check.GetBuffRemain(BuffNames::AssaPointsLimit));
		}

		if (LastManStand::Active == true && Check.IsBuff(BuffNames::LMS))
			LastManStand::RegisterAmount--;

		if (Hell::Active == true && Check.IsBuff(166) && Hell::Size > 0)
			Hell::Size--;

		if (FishLimit || ShoppingLimit || MiningPCLimit) {
			uint32_t LimitIndex = sha256(Check.GetHWID() + Check.GetIP());

			if (FishLimit && Check.IsBuff(3958) && FishingLimit.count(LimitIndex)) {
				int Limited = FishingLimit.findValue(LimitIndex) - 1;
				if (!Limited)
					FishingLimit.erase(LimitIndex);
				else
					FishingLimit.replaceInsert(LimitIndex, Limited);
			}

			if (ShoppingLimit && Check.IsBuff(3959) && ShopLimit.count(LimitIndex)) {
				int Limited = ShopLimit.findValue(LimitIndex) - 1;
				if (!Limited)
					ShopLimit.erase(LimitIndex);
				else
					ShopLimit.replaceInsert(LimitIndex, Limited);
			}

			if (MiningPCLimit && Check.IsBuff(3960) && MiningLimit.count(LimitIndex)) {
				int Limited = MiningLimit.findValue(LimitIndex) - 1;
				if (!Limited)
					MiningLimit.erase(LimitIndex);
				else
					MiningLimit.replaceInsert(LimitIndex, Limited);
			}
		}
	}

	if (Type == 1 && Check.IsOnline())
	{
		MobIndex = Check.GetMobIndex();
		
		if (reloadingM) {
			CChar::WriteInSight(Check.GetOffset(), 56, "db", Check.GetID(), 7);
			CChar::WriteInSight(Check.GetOffset(), 61, "db", Check.GetID(), 9);
		}

		Def = Check.GetDef();

		if (GuildRaid::Active && Object == GuildRaid::Boss) {
			CChar::WriteInSight(Object, 0xFF, "dsd", 247, "Guild Raid System has failed.", 3);
			GuildRaid::Active = false;
			GuildRaid::Reward = 0;
			GuildRaid::GID = 0;
			GuildRaid::Time = 0;
			GuildRaid::Boss = 0;
		}

		if (Maut::Active && (int)Object == Maut::Boss)
		{
			CPlayer::WriteInMap(MautMap, 0xFF, "dsd", 247, "Mautareta System failed...", 3);

			int Around = Check.GetObjectListAround(50);

			while (Around)
			{
				IChar Object((void*)CBaseList::Offset((void*)Around));

				if (Object.GetType() == 0 && Object.IsBuff(BuffNames::Mautareta)) {
					Object.CloseScreenTime();
					Object.CancelBuff(BuffNames::Mautareta);
				}

				Around = CBaseList::Pop((void*)Around);
			}

			Maut::Timer = 0;
			Maut::Boss = 0;
			Maut::KillCount = 0;
			Maut::RegisterAmount = 0;
			MautRegistration.clear();
			Maut::Active = false;
		}

		if (BossEXP::Active && (int)Object == BossEXP::Boss)
		{
			std::string SysName(BossEXPName);
			std::string msg = SysName + " failed...";

			CPlayer::WriteInMap(MautMap, 0xFF, "dsd", 247, SysName.c_str(), 3);

			int Around = Check.GetObjectListAround(50);

			while (Around)
			{
				IChar Object((void*)CBaseList::Offset((void*)Around));

				if (Object.GetType() == 0 && Object.IsBuff(BuffNames::BossEXP)) {
					Object.CloseScreenTime();
					Object.CancelBuff(BuffNames::BossEXP);
				}

				Around = CBaseList::Pop((void*)Around);
			}

			BossEXP::Timer = 0;
			BossEXP::Boss = 0;
			BossEXP::KillCount = 0;
			BossEXP::RegisterAmount = 0;
			BossEXPRegistration.clear();
			BossEXP::Active = false;
		}

		if (Scenario::Active == true && Check.GetMobTanker())
		{
			IChar IPlayer((void*)Check.GetMobTanker());

			if (Check.GetMobIndex() == 360 && IPlayer.IsBuff(162))
			{
				Scenario::RedScore += 10;
				Scenario::RedTeamTowerCount += 1;
				Scenario::Time = 0;
			}

			if (Check.GetMobIndex() == 360 && IPlayer.IsBuff(163))
			{
				Scenario::BlueScore += 10;
				Scenario::BlueTeamTowerCount += 1;
				Scenario::Time = 0;
			}
		}

		if (EventMapsMobsOn.count(Erase)) {
			eventMapMonster evMonster = EventMapsMobsOn.findValue(Erase);
			if (EventMapsOn.count(evMonster.Quest)) {
				int MobAmount = EventMapsOn.findValue(evMonster.Quest);
				if (MobAmount == 1) {
					if (EventMapsQuests.count(evMonster.Quest)) {
						std::set<std::string> RLimit;
						eventMap evMap = EventMapsQuests.find(evMonster.Quest)->second;
						int TimeLeft = MonsterDisappear.findValue(Erase);
						if (TimeLeft > GetTickCount() && evMap.monsters.size() > evMonster.CIndex + 1) {
							if (evMap.Reward.size() > 1) {
								int Around = Check.GetObjectListAround(50);

								while (Around)
								{
									IChar Object((void*)CBaseList::Offset((void*)Around));

									if (Object.GetType() == 0) {
										int Quest = Object.GetBuffValue(BuffNames::EventMapQuest);
										if (Quest && !isRewarded(Object)) {
											int Size = evMap.Reward.size();

											if (Size > evMonster.CIndex)
												Object.AddReward(String2Int(evMap.Reward[evMonster.CIndex]));
											else
												Object.AddReward(String2Int(evMap.Reward[0]));
											rewardLimit(Object);
										}
										CPlayer::Write(Object.GetOffset(), 0xFF, "dsd", 247, "Round Completed, Next Round Started...", 2);
									}

									Around = CBaseList::Pop((void*)Around);
								}
								RewardLimit.clear();
							}
							SpawnEventMap(evMap, evMonster.CIndex + 1, TimeLeft - GetTickCount());
						}
						else {
							int Lapse = evMap.Lapse;
							InstancesCD.replaceInsert(evMonster.Quest, GetTickCount() + ((Lapse + 2) * 1000));

							int Around = Check.GetObjectListAround(50);

							while (Around)
							{
								IChar Object((void*)CBaseList::Offset((void*)Around));

								if (Object.GetType() == 0) {
									if (TimeLeft > GetTickCount()) {
										int Quest = Object.GetBuffValue(BuffNames::EventMapQuest);
										if (Quest) {
											if (!evMap.Reward.empty() && !isRewarded(Object)) {
												Object.AddReward(String2Int(evMap.Reward[evMap.Reward.size() - 1]));
												rewardLimit(Object);
											}
											Object.Buff(BuffNames::EventMapLapse, Lapse, 0);
										}
										CPlayer::Write(Object.GetOffset(), 0xFF, "dsd", 247, "Event successfully Completed.", 1);
									}
									else
										CPlayer::Write(Object.GetOffset(), 0xFF, "dsd", 247, "Event has failed.", 3);

									Object.CloseScreenTime();
								}

								Around = CBaseList::Pop((void*)Around);
							}
							RewardLimit.clear();
							EventMapsOn.erase(evMonster.Quest);
						}
					}
				}
				else
					EventMapsOn.replaceInsert(evMonster.Quest, MobAmount - 1);
			}
			EventMapsMobsOn.erase(Erase);
		}

		if (Check.GetMobTanker())
		{
			IChar EAPlayer((void*)Check.GetMobTanker());
			if (EAPlayer.IsValid() && EAPlayer.GetProperty(PlayerProperty::ContinueSkillPlayerSkillID) == 49)
				ContinueArrowExplosion(EAPlayer.GetOffset());
		}
	}

	if (Type == 3 && Check.IsOnline())
	{
		IItem xItem(Object);
		IID = xItem.GetIID();
	}
	
	CBase::Delete(Object);

	if (Type == 0 && PID && Erase && CBase::IsDeleted(Erase))
	{
		//userLock.Enter();
		User.erase(PID);
		//userLock.Leave(); 
		CheckMining.erase(PID);

		for (auto x = PacketSpamConf.begin(); x != PacketSpamConf.end(); x++)
			PacketSpam.erase((PID * 1000) + x->first);

		InterlockedDecrement(&OnlinePlayers); 
		SendCreatePlayer.erase(Erase);
	}

	if (Type == 1 && Erase && CBase::IsDeleted(Erase))
	{
		if(Def == 54123)
			InterlockedDecrement(&summonPets);
		MonsterDisappear.erase(Erase);

		//MonsterDisappear.erase(Erase);
		//MonsterAI.erase(Erase);
		if (Erase == (int)Hunting::Monster) {
			Hunting::Active = false;
			Hunting::Guild = 0;
			Hunting::Monster = 0;
			Hunting::Time = 0;
			CPlayer::WriteAll(0xFF, "dsd", 247, "Hunting System ended.", 2);
			if (CWGID) {
				HuntingID = CWGID;
				HuntingName = CWGuildName;
			}
		}
	}

	if (Type == 3 && Erase && IID && CBase::IsDeleted(Erase))
	{
		itemLockLock.Enter();
		ItemLockCheck.erase(IID); 
		itemLockLock.Leave();
		//petLifeLock.Enter();
		if (!ItemTimerDisable.count(IID))
			PetLifeCheck.erase(IID);
		else
			ItemTimerDisable.erase(IID);
		//petLifeLock.Leave();
		if (!ItemStatDisable.count(IID)) {
			itemStat.Enter();
			GetItemStat.erase(IID);
			itemStat.Leave();
		}
		else
			ItemStatDisable.erase(IID);
		//RemovedStats.erase(IID);
	}
}