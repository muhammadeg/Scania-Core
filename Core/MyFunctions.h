void ShowMySkin(void* Player){
	IChar IPlayer((void*)Player);

	if (IPlayer.IsOnline() && !IPlayer.isDead() && !IPlayer.isAssassin()){
		IPlayer.setSkinView(IPlayer.IsHide() ? -1 : 0);
		IPlayer.SystemMessage("Skins appearance has been turned on.", TEXTCOLOR_GREEN);

		if (IPlayer.GetBuffValue(BuffNames::SuitsUsing))
			CPlayer::Write(IPlayer.GetOffset(), 5, "ddw", IPlayer.GetID(), 0, IPlayer.GetBuffValue(BuffNames::SuitsUsing));

		int custWeap = IPlayer.GetBuffValue(BuffNames::custWeap);
		if (custWeap) {
			CPlayer::Write(IPlayer.GetOffset(), 5, "ddw", IPlayer.GetID(), 0, custWeap);

			if (CostWeaponsEffects.count(custWeap) && IPlayer.GetBuffValue(BuffNames::WeaponWear))
				CPlayer::Write(IPlayer.GetOffset(), 0xFE, "ddsd", 177, IPlayer.GetID(), IPlayer.CostEffect(CostWeaponsEffects.find(custWeap)->second).c_str(), 1);
		}

		IPlayer.Teleport(IPlayer.GetMap(), IPlayer.GetX(), IPlayer.GetY(), IPlayer.GetZ());
	}
}

//int TimedItemExtend(void* Item, int Player, int NewPrefix)
//{
//	IChar IPlayer((void*)Player);
//	IItem IItem(Item);
//
//	if (TimeTalisman.count(NewPrefix))
//	{
//		ConfigTimeTalisman t = TimeTalisman.find(NewPrefix)->second;
//
//		int TotalItems = t.items.size();
//		bool itemFound = false;
//		for (int i = 0; i < TotalItems; i++)
//		{
//			int Index = String2Int(t.items[i]);
//			if (IItem.CheckIndex() == Index)
//			{
//
//				if (CBase::IsDeleted((int)Item))
//					return 0;
//
//				if (IPlayer.IsBuff(328))
//					return 0;
//				else
//					IPlayer.Buff(328, 3, 0);
//
//				int ReplacePrefix = 0, ReplaceItem = 0, ReplaceInfo = 0, ReplaceDef = 0, ReplaceEva = 0, ReplaceGem = 0;
//				int ItemStat = 0;
//
//				itemStat.Enter();
//				if (GetItemStat.count(IItem.GetIID()))
//					ItemStat = GetItemStat.find(IItem.GetIID())->second;
//				itemStat.Leave();
//
//				if (*(DWORD *)((int)Item + 44))
//					ReplacePrefix = *(DWORD *)(*(DWORD *)((int)Item + 44) + 32);
//
//				if (*(DWORD *)((int)Item + 48))
//					ReplaceInfo = *(DWORD *)((int)Item + 48);
//
//				if (*(DWORD *)((int)Item + 108))
//					ReplaceDef = *(DWORD *)((int)Item + 108);
//
//				if (IItem.HighMemory()) {
//					if (*(DWORD *)((int)Item + 116))
//						ReplaceEva = *(DWORD *)((int)Item + 116);
//
//					if (*(DWORD *)((int)Item + 84))
//						ReplaceGem = *(DWORD *)((int)Item + 84);
//				}
//
//				int ItemNewIndex = IItem.CheckIndex();
//				int DeleteCheck = (*(int(__thiscall **)(DWORD, void *, signed int, signed int))(*(DWORD*)Item + 120))((int)Item, IPlayer.GetOffset(), 9, -1);
//
//				if (!DeleteCheck)
//				{
//					ReplaceItem = CItem::CreateItem(ItemNewIndex, ReplacePrefix, 1, -1);
//
//					if (ReplaceItem)
//					{
//						CIOObject::AddRef(ReplaceItem);
//						if (ReplaceInfo)
//							*(DWORD *)(ReplaceItem + 48) = ReplaceInfo;
//						if (ReplaceDef)
//							*(DWORD *)(ReplaceItem + 108) = ReplaceDef;
//						if (ReplaceEva)
//							*(DWORD *)(ReplaceItem + 116) = ReplaceEva;
//						if (ReplaceGem)
//							*(DWORD *)(ReplaceItem + 84) = ReplaceGem;
//
//						if (CPlayer::_InsertItem(IPlayer.GetOffset(), 27, ReplaceItem) != 1)
//						{
//							CConsole::Red("Real time armor insert item Null error [PID (%d)] ", IPlayer.GetPID());
//							CBase::Delete((void *)ReplaceItem);
//							CIOObject::Release((void *)ReplaceItem);
//							return 0;
//						}
//
//						CIOObject::Release((void *)ReplaceItem);
//						itemStat.Enter();
//						GetItemStat[*(DWORD *)(ReplaceItem + 36)] = ItemStat;
//						itemStat.Leave();
//
//						CDBSocket::Write(90, "dd", ItemStat, *(DWORD *)(ReplaceItem + 36));
//						CDBSocket::Write(87, "ddd", IPlayer.GetPID(), *(DWORD *)(ReplaceItem + 84), *(DWORD *)(ReplaceItem + 36));
//						CDBSocket::Write(21, "dddbb", *(DWORD *)(ReplaceItem + 36), *(DWORD *)(ReplaceItem + 32), *(DWORD *)(ReplaceItem + 48), 8, 7);
//
//						if (ReplaceDef)
//							CDBSocket::Write(17, "ddbbb", *(DWORD *)(ReplaceItem + 36), *(DWORD *)(ReplaceItem + 32), 15, *(DWORD *)(ReplaceItem + 108), 0);
//						if (ReplaceEva)
//							CDBSocket::Write(17, "ddbbb", *(DWORD *)(ReplaceItem + 36), *(DWORD *)(ReplaceItem + 32), 10, *(DWORD *)(ReplaceItem + 116), 0);
//
//						CItem::SendItemInfo((void*)ReplaceItem, (int)IPlayer.GetOffset(), 92);
//						CPlayer::Write(IPlayer.GetOffset(), 0xFF, "ddddd", 242, 0, 0, 128, 255);
//
//
//						IPlayer.SystemMessage("Your item's rental period has been increased.", TEXTCOLOR_GREEN);
//						itemFound = true;
//
//					}
//				}
//				else {
//					IPlayer.BoxMsg("Extension can not be used on this item.");
//
//					return 0;
//				}
//
//				return 1;
//
//			}
//		}
//	}
//}

void SendShoutWebhookMessage(const std::string& webhookUrl, const std::string& message, const std::string& avatarUrl, const std::string& username) {
	//// Check if the message is empty or contains only whitespace
	//if (message.empty() || std::all_of(message.begin(), message.end(), ::isspace)) {
	//	CConsole::Red("Cannot send an empty message or a message with only whitespace.");
	//	return;
	//}

	CURL* curl;
	CURLcode res;

	curl_global_init(CURL_GLOBAL_DEFAULT);
	curl = curl_easy_init();

	if (curl) {

		std::string jsonData = "{"
			"\"content\": \"" + message + "\","
			"\"username\": \"" + username + "\","
			"\"avatar_url\": \"" + avatarUrl + "\""
			"}";

		curl_easy_setopt(curl, CURLOPT_URL, webhookUrl.c_str());
		curl_easy_setopt(curl, CURLOPT_POST, 1L);
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, jsonData.c_str());

		struct curl_slist* list = NULL;
		list = curl_slist_append(list, "Content-Type: application/json");
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, list);

		std::string response;
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

		res = curl_easy_perform(curl);

		if (res != CURLE_OK) {
			CConsole::Red("Failed to send webhook message. Error code: %d", res);
		}

		curl_slist_free_all(list);
		curl_easy_cleanup(curl);
	}
	else {
		CConsole::Red("Failed to initialize cURL.");
	}

	curl_global_cleanup();
}


void SendWebhookMessage(const std::string& webhookUrl, const std::string& message, const std::string& avatarUrl, const std::string& username) {
	// Check if the message is empty or contains only whitespace
	if (message.empty() || std::all_of(message.begin(), message.end(), ::isspace)) {
		CConsole::Red("Cannot send an empty message or a message with only whitespace.");
	}
	else{

		CURL* curl;
		CURLcode res;

		curl_global_init(CURL_GLOBAL_DEFAULT);
		curl = curl_easy_init();

		if (curl) {

			std::string jsonData = "{"
				"\"content\": \"" + message + "\","
				"\"username\": \"" + username + "\","
				"\"avatar_url\": \"" + avatarUrl + "\""
				"}";

			curl_easy_setopt(curl, CURLOPT_URL, webhookUrl.c_str());
			curl_easy_setopt(curl, CURLOPT_POST, 1L);
			curl_easy_setopt(curl, CURLOPT_POSTFIELDS, jsonData.c_str());

			struct curl_slist* list = NULL;
			list = curl_slist_append(list, "Content-Type: application/json");
			curl_easy_setopt(curl, CURLOPT_HTTPHEADER, list);

			std::string response;
			curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
			curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

			res = curl_easy_perform(curl);

			if (res != CURLE_OK) {
				CConsole::Red("Failed to send webhook message. Error code: %d", res);
			}

			curl_slist_free_all(list);
			curl_easy_cleanup(curl);
		}
		else {
			CConsole::Red("Failed to initialize cURL.");
		}

		curl_global_cleanup();
	}
}
void MyAgentsWebhook(std::string servername){
	std::string url = "https://discord.com/api/webhooks/1193728182982025286/y0YEGdScsfyJKEWHdTWWcEO1UU9xxBYr9fNoVHOtbdUYsl00IWxtasBvDphjqY7zKvtq";

	std::string avatar = Avatar;
	SendWebhookMessage(url, servername + " has started MainSvrT, Machine: " + getMachineName() + " HWID: " + getHWID() + ", IP: " + getIP(), avatar.c_str(), thisServerName);
}

void ToNoticeWebhook(std::string notice)
{
	std::string url = NoticeWebHook;
	std::string avatar = Avatar;
	SendWebhookMessage(url, notice.c_str(), avatar.c_str(), thisServerName);
}

void ToHonorNoticeWebhook(std::string notice)
{
	std::string url = HonorNoticeWebhook;
	std::string avatar = Avatar;
	SendWebhookMessage(url, notice.c_str(), avatar.c_str(), thisServerName);
}

void ToAssassinWebhook(std::string notice)
{
	std::string url = AssassinWebhook;
	std::string avatar = Avatar;
	SendWebhookMessage(url, notice.c_str(), avatar.c_str(), thisServerName);
}

bool CheckRequiredItems(IChar player, const eventMap& questEvent) {
	bool hasRequiredItems = true;
	int itemsNumber = questEvent.ReqItemx.size();

	for (int i = 0; i < itemsNumber; i++) {
		int index = String2Int(questEvent.ReqItemx[i]);
		int amount = String2Int(questEvent.ReqAmountx[i]);

		if (!CPlayer::FindItem(player.GetOffset(), index, amount)) {
			hasRequiredItems = false;
			break;
		}
	}

	if (!hasRequiredItems) {
		player.SystemMessage("You do not have enough required items to register to " + questEvent.Name + ".", TEXTCOLOR_RED);
	}

	return hasRequiredItems;
}

void RemoveRequiredItems(IChar player, const eventMap& questEvent) {
	int itemsNumber = questEvent.ReqItemx.size();

	for (int i = 0; i < itemsNumber; i++) {
		int index = String2Int(questEvent.ReqItemx[i]);
		int amount = String2Int(questEvent.ReqAmountx[i]);
		CPlayer::RemoveItem((void*)player.GetOffset(), 9, index, amount);
	}
}

bool CheckRequiredItemsMembers(IChar player, const eventMap& questEvent) {
	bool hasRequiredItems = true;
	int itemsNumber = questEvent.ReqItemM.size();

	for (int i = 0; i < itemsNumber; i++) {
		int index = String2Int(questEvent.ReqItemM[i]);
		int amount = String2Int(questEvent.ReqAmountM[i]);

		if (!CPlayer::FindItem(player.GetOffset(), index, amount)) {
			hasRequiredItems = false;
			break;
		}
	}

	if (!hasRequiredItems) {
		player.SystemMessage("You do not have enough required items to register to " + questEvent.Name + ".", TEXTCOLOR_RED);
	}

	return hasRequiredItems;
}

void RemoveRequiredItemsMembers(IChar player, const eventMap& questEvent) {
	int itemsNumber = questEvent.ReqItemM.size();

	for (int i = 0; i < itemsNumber; i++) {
		int index = String2Int(questEvent.ReqItemM[i]);
		int amount = String2Int(questEvent.ReqAmountM[i]);
		CPlayer::RemoveItem((void*)player.GetOffset(), 9, index, amount);
	}
}

void UpdateMissionProgress(int Quest, IChar& IPlayer, IChar& ITarget, int questIndex, const std::vector<std::string>& mobList, int buffName, int& missionProgress, int targetAmount, int writeValue) {
	for (auto it = mobList.begin(); it != mobList.end(); ++it) {
		int mobIndex = String2Int(*it);
		if (mobIndex == ITarget.GetMobIndex() && missionProgress <= targetAmount) {
			if (!IPlayer.IsBuff(buffName)) {
				IPlayer.Buff(buffName, 86400, 1);
				CPlayer::Write(IPlayer.GetOffset(), 184, "ddd", questIndex, writeValue, 1);
				switch (buffName) {
				case BuffNames::NormalDuty:
					CDBSocket::Write(125, "dddddd", 4, IPlayer.GetPID(), Quest, 1, 0, 0);
					break;
				case BuffNames::MiniBoss:
					CDBSocket::Write(125, "dddddd", 4, IPlayer.GetPID(), Quest, 0, 1, 0);
					break;
				case BuffNames::InstanceDuty:
					CDBSocket::Write(125, "dddddd", 4, IPlayer.GetPID(), Quest, 0, 0, 1);
					break;
				}
			}
			else {
				IPlayer.UpdateBuff(buffName, 86400, missionProgress);
				CPlayer::Write(IPlayer.GetOffset(), 184, "ddd", questIndex, writeValue, missionProgress);
				switch (buffName) {
				case BuffNames::NormalDuty:
					CDBSocket::Write(125, "dddddd", 4, IPlayer.GetPID(), Quest, missionProgress, 0, 0);
					break;
				case BuffNames::MiniBoss:
					CDBSocket::Write(125, "dddddd", 4, IPlayer.GetPID(), Quest, 0, missionProgress, 0);
					break;
				case BuffNames::InstanceDuty:
					CDBSocket::Write(125, "dddddd", 4, IPlayer.GetPID(), Quest, 0, 0, missionProgress);
					break;
				}
			}
		}
	}
}

bool CheckMissionProgress(IChar& IPlayer, int TotalAmount, int QuestIndex, int Cooldown, int RewardID)
{
	int missionProgress = IPlayer.GetBuffValue(BuffNames::NormalDuty) + 1;
	int bossMissionProgress = IPlayer.GetBuffValue(BuffNames::MiniBoss) + 1;
	int instanceMissionProgress = IPlayer.GetBuffValue(BuffNames::InstanceDuty) + 1;

	if ((missionProgress - 1) + (instanceMissionProgress - 1) + (bossMissionProgress - 1) >= TotalAmount - 1) {
		IPlayer.CancelBuff(BuffNames::NormalDuty);
		IPlayer.CancelBuff(BuffNames::InstanceDuty);
		IPlayer.CancelBuff(BuffNames::MiniBoss);
		IPlayer.CancelBuff(BuffNames::DailyDuty + QuestIndex);
		IPlayer.SaveBuff(BuffNames::DutyTrigger + QuestIndex, Cooldown);
		IPlayer.EndQuest(QuestIndex, 0, 0, 1);
		CDBSocket::Write(125, "ddd", 5, IPlayer.GetPID(), QuestIndex);

		IPlayer.systemReward(RewardID);
		return true;
	}
	return false;
}

void UpdateDailyDuty(void* Player, void* Monster) {
	IChar IPlayer(Player);
	IChar ITarget(Monster);

	if (IPlayer.IsValid() && ITarget.IsValid() && IPlayer.GetType() == 0 && ITarget.GetType() == 1) {

		int QValue = 0;
		std::vector<MonsterDailyDuty> Quests = DutyMonsterQuests.find(ITarget.GetMobIndex())->second;

		if (!Quests.empty())
		{
			for (int i = 0; i < Quests.size(); i++){
				MonsterDailyDuty mDailyQ = Quests[i];
				if (mDailyQ.Quest){
					QValue = IPlayer.GetBuffValue(BuffNames::DailyDuty + mDailyQ.Quest);
					break;
				}
			}
		}

		if (IPlayer.IsBuff(BuffNames::DailyDuty + QValue) && DutyQuest.count(QValue)){
			const DailyDuty& mission = DutyQuest.find(QValue)->second;
			int currentMission = DutyQuest.find(QValue)->first;
			int questIndex = (currentMission << 16) + 1;
			//bool isQuest = (CPlayer::CheckQuestFlag((int)IPlayer.GetOffset(), questIndex) == true);

			if (currentMission != 0 && QValue == currentMission){

				int missionProgress = IPlayer.GetBuffValue(BuffNames::NormalDuty) + 1;
				int bossMissionProgress = IPlayer.GetBuffValue(BuffNames::MiniBoss) + 1;
				int instanceMissionProgress = IPlayer.GetBuffValue(BuffNames::InstanceDuty) + 1;

				int amount = String2Int(mission.NormalAmount[0]);
				int bAmount = String2Int(mission.BossAmount[0]);
				int iAmount = String2Int(mission.IMobAmount[0]);

				int totalAmount = amount + bAmount + iAmount;

				if (IPlayer.IsParty())
				{
					int Party = CParty::FindParty(IPlayer.GetPartyID());

					if (Party){
						for (int i = CParty::GetPlayerList((void*)Party); i; i = CBaseList::Pop((void *)i))
						{
							IChar IMembers((void*)*(DWORD*)((void*)i));

							if (IMembers.IsValid() && IMembers.IsBuff(BuffNames::DailyDuty + QValue) && IMembers.IsInRange(IPlayer, 300))
							{
								if (!CheckMissionProgress(IMembers, totalAmount, QValue, mission.cooldown, mission.Reward)){

									int MmissionProgress = IMembers.GetBuffValue(BuffNames::NormalDuty) + 1;
									int MbossMissionProgress = IMembers.GetBuffValue(BuffNames::MiniBoss) + 1;
									int MinstanceMissionProgress = IMembers.GetBuffValue(BuffNames::InstanceDuty) + 1;

									UpdateMissionProgress(currentMission, IMembers, ITarget, questIndex, mission.NormalMob, BuffNames::NormalDuty, MmissionProgress, amount, 5000);
									UpdateMissionProgress(currentMission, IMembers, ITarget, questIndex, mission.MiniBoss, BuffNames::MiniBoss, MbossMissionProgress, bAmount, 5001);
									UpdateMissionProgress(currentMission, IMembers, ITarget, questIndex, mission.InstanceD, BuffNames::InstanceDuty, MinstanceMissionProgress, iAmount, 5002);
								}
							}
						}
						CIOObject::Release((void*)Party);
					}
				}
				else{
					if (!CheckMissionProgress(IPlayer, totalAmount, QValue, mission.cooldown, mission.Reward)){
						UpdateMissionProgress(currentMission, IPlayer, ITarget, questIndex, mission.NormalMob, BuffNames::NormalDuty, missionProgress, amount, 5000);
						UpdateMissionProgress(currentMission, IPlayer, ITarget, questIndex, mission.MiniBoss, BuffNames::MiniBoss, bossMissionProgress, bAmount, 5001);
						UpdateMissionProgress(currentMission, IPlayer, ITarget, questIndex, mission.InstanceD, BuffNames::InstanceDuty, instanceMissionProgress, iAmount, 5002);
					}
				}
			}
		}
	}
}

void UpdateAutoMission(void* Player, void* Monster) {

	IChar IPlayer(Player);
	IChar ITarget(Monster);
	if (IPlayer.IsValid() && ITarget.IsValid() && IPlayer.GetType() == 0 && ITarget.GetType() == 1) {
		int MissionMonsterIndex = ITarget.GetMobIndex();

		if (MissionQuests.count(MissionMonsterIndex)) {
			const MissionInfo& mission = MissionQuests.find(MissionMonsterIndex)->second;

			int currentMission = mission.currentmission;
			int nextMission = mission.nextmission;
			int questIndex = (currentMission << 16) + 1;
			if (IPlayer.IsParty())
			{
				int Party = CParty::FindParty(IPlayer.GetPartyID());

				if (Party){
					for (int i = CParty::GetPlayerList((void*)Party); i; i = CBaseList::Pop((void *)i))
					{
						IChar IMembers((void*)*(DWORD*)((void*)i));

						if (IMembers.IsValid() && IMembers.IsInRange(IPlayer, 300))
						{
							bool isQuest = (CPlayer::CheckQuestFlag((int)IMembers.GetOffset(), questIndex) == true);
							int isQuestClear = CPlayer::CheckQuestClear((int)IMembers.GetOffset(), static_cast<char>(currentMission));

							if (mission.Monster == MissionMonsterIndex && isQuest && !isQuestClear) {
								int missionMonsterAmount = mission.Amount;
								int missionProgress = IMembers.GetBuffValue(BuffNames::MissionMonsterBuff);

								if (currentMission != 0 && missionProgress < missionMonsterAmount) {

									missionProgress++;

									if (!IMembers.IsBuff(BuffNames::MissionMonsterQuest)){
										IMembers.SaveBuff(BuffNames::MissionMonsterQuest, BuffNames::BuffTime, currentMission, 0, 0);
										IMembers.SaveBuff(BuffNames::MissionMonsterMob, BuffNames::BuffTime, MissionMonsterIndex, 0, 0);
									}
									else{
										IMembers.UpdateSavedBuff(BuffNames::MissionMonsterQuest, BuffNames::BuffTime, currentMission, 0, 0);
										IMembers.UpdateSavedBuff(BuffNames::MissionMonsterMob, BuffNames::BuffTime, MissionMonsterIndex, 0, 0);
									}

									if (!IMembers.IsBuff(BuffNames::MissionMonsterBuff))
										IMembers.SaveBuff(BuffNames::MissionMonsterBuff, BuffNames::BuffTime, 0, 0, 0);
									else
										IMembers.UpdateSavedBuff(BuffNames::MissionMonsterBuff, BuffNames::BuffTime, missionProgress, 0, 0);

									CPlayer::Write(IMembers.GetOffset(), 184, "ddd", questIndex, ITarget.GetMobIndex(), missionProgress);

									if (missionProgress >= missionMonsterAmount) {
										IMembers.systemReward(mission.rewardID);
										missionProgress = 0;
										if (nextMission != 0) {
											IMembers.SaveBuff(BuffNames::MissionMonsterBuff, BuffNames::BuffTime, 0, 0, 0);
											CQuest::Start((nextMission << 16) | 1, (int)IMembers.GetOffset());

											if (PeaceEvil)
												IMembers.AddHousePoints(2);

										}
									}
								}
							}
						}
					}
					CIOObject::Release((void*)Party);
				}
			}
			else{
				bool isQuest = (CPlayer::CheckQuestFlag((int)IPlayer.GetOffset(), questIndex) == true);
				int isQuestClear = CPlayer::CheckQuestClear((int)IPlayer.GetOffset(), static_cast<char>(currentMission));

				if (mission.Monster == MissionMonsterIndex && isQuest && !isQuestClear) {
					int missionMonsterAmount = mission.Amount;
					int missionProgress = IPlayer.GetBuffValue(BuffNames::MissionMonsterBuff);

					if (currentMission != 0 && missionProgress < missionMonsterAmount) {

						missionProgress++;

						if (!IPlayer.IsBuff(BuffNames::MissionMonsterQuest)){
							IPlayer.SaveBuff(BuffNames::MissionMonsterQuest, BuffNames::BuffTime, currentMission, 0, 0);
							IPlayer.SaveBuff(BuffNames::MissionMonsterMob, BuffNames::BuffTime, MissionMonsterIndex, 0, 0);
						}
						else{
							IPlayer.UpdateSavedBuff(BuffNames::MissionMonsterQuest, BuffNames::BuffTime, currentMission, 0, 0);
							IPlayer.UpdateSavedBuff(BuffNames::MissionMonsterMob, BuffNames::BuffTime, MissionMonsterIndex, 0, 0);
						}

						if (!IPlayer.IsBuff(BuffNames::MissionMonsterBuff))
							IPlayer.SaveBuff(BuffNames::MissionMonsterBuff, BuffNames::BuffTime, 0, 0, 0);
						else
							IPlayer.UpdateSavedBuff(BuffNames::MissionMonsterBuff, BuffNames::BuffTime, missionProgress, 0, 0);

						CPlayer::Write(IPlayer.GetOffset(), 184, "ddd", questIndex, ITarget.GetMobIndex(), missionProgress);

						if (missionProgress >= missionMonsterAmount) {
							IPlayer.systemReward(mission.rewardID);
							missionProgress = 0;
							if (nextMission != 0) {
								IPlayer.SaveBuff(BuffNames::MissionMonsterBuff, BuffNames::BuffTime, 0, 0, 0);
								CQuest::Start((nextMission << 16) | 1, (int)IPlayer.GetOffset());

								if (PeaceEvil)
									IPlayer.AddHousePoints(2);

							}
						}
					}
				}
			}
		}
	}
}

void PBattlepassCheck(void* Player, void* QuestOffset){
	IQuest Quest(QuestOffset);

	IChar IPlayer((void*)Player);

	if (IPlayer.IsOnline() && Quest.GetIndex() == BattlepassQuest)
	{
		int battlepassToReward = IPlayer.GetProperty(PlayerProperty::CurrentPBReward);
		int battlepassMaxReward = IPlayer.GetProperty(PlayerProperty::MaxBReward);
		int Item = CPlayer::FindItem((void*)Player, BattlepassIndex, 1);

		if (Item){
			if (battlepassToReward >= battlepassMaxReward)
			{
				//		IPlayer.SystemMessage("You have already claimed previous premium rewards.", TEXTCOLOR_RED);
				return;
			}

			for (int level = 1; level <= IPlayer.GetProperty(PlayerProperty::BattlepassLv); level++)
			{
				std::vector<ConfigLevelReward> pbattleReward = PremiumPass.find(level)->second;

				for (int i = 0; i < (int)pbattleReward.size(); i++)
				{
					ConfigLevelReward premiumReward = pbattleReward[i];
					if (premiumReward.Class == IPlayer.GetClass() || premiumReward.Class == 5)
					{
						if (battlepassToReward < battlepassMaxReward && battlepassToReward < premiumReward.ID)
						{
							for (int j = 0; j < premiumReward.Indexes.size(); j++) {
								int Index = String2Int(premiumReward.Indexes[j]);
								int Amount = String2Int(premiumReward.Amounts[j]);
								if (Index && Amount)
									IPlayer.GiveReward(Index, premiumReward.Prefix, Amount, (premiumReward.Prefix == 256) ? 0 : -128, 0, 0, 0, 0, 0, 0, 0, premiumReward.Msg.c_str());
							}

							CDBSocket::Write(122, "dd", IPlayer.GetPID(), 6);
						//	IPlayer.SystemMessage("Executed " + Int2String(IPlayer.GetProperty(PlayerProperty::BattlepassLv)) + " " + Int2String(battlepassToReward) + " " + Int2String(battlepassMaxReward), TEXTCOLOR_GREEN);
							CDBSocket::Write(122, "dd", IPlayer.GetPID(), 1);

						}
					}
				}
			}
		}
		return;
	}


}

void BattlepassCheck(void* Player, void* QuestOffset){
	IQuest Quest(QuestOffset);

	IChar IPlayer((void*)Player);

	if (IPlayer.IsOnline() && Quest.GetIndex() == BattlepassQuest)
	{
		int battlepassToReward = IPlayer.GetProperty(PlayerProperty::CurrentBReward);
		int battlepassMaxReward = IPlayer.GetProperty(PlayerProperty::MaxBReward);

		if (battlepassToReward >= battlepassMaxReward)
		{
			IPlayer.SystemMessage("You have already claimed previous rewards.", TEXTCOLOR_RED);
			return;
		}

		for (int level = 1; level <= IPlayer.GetProperty(PlayerProperty::BattlepassLv); level++)
		{
			std::vector<ConfigLevelReward> battleReward = BattlepassReward.find(level)->second;

			for (int i = 0; i < (int)battleReward.size(); i++)
			{
				ConfigLevelReward reward = battleReward[i];
				if (reward.Class == IPlayer.GetClass() || reward.Class == 5)
				{
					if (battlepassToReward < battlepassMaxReward && battlepassToReward < reward.ID)
					{

						for (int j = 0; j < reward.Indexes.size(); j++) {
							int Index = String2Int(reward.Indexes[j]);
							int Amount = String2Int(reward.Amounts[j]);
							if (Index && Amount){
								IPlayer.GiveReward(Index, reward.Prefix, Amount, (reward.Prefix == 256) ? 0 : -128, 0, 0, 0, 0, 0, 0, 0, reward.Msg.c_str());
								CDBSocket::Write(122, "dd", IPlayer.GetPID(), 1);
							}
						}

						CDBSocket::Write(122, "dd", IPlayer.GetPID(), 4);
					}
				}
			}
		}
		return;
	}


}

void CJBRefBuff(void* Player, int BuffGrade, int SpeedUp)
{
	IChar IPlayer(Player);

	IPlayer.Buff(48, 1800, 8 * BuffGrade + 3);
	IPlayer.Buff(50, 1800, 8 * BuffGrade + 3);
	IPlayer.Buff(47, 1800, 8 * BuffGrade + 3);
	IPlayer.Buff(49, 1800, 8 * BuffGrade + 3);
	IPlayer.Buff(46, 1800, 8 * BuffGrade + 3);
	IPlayer.Buff(36, 1800, 8 * BuffGrade + 16);
	CChar::CancelAllBuff(IPlayer.GetOffset(), 37);
	int AddBuff = CBuff::CreateBuff(37, 1800, 30 * BuffGrade + 5, 20 * BuffGrade + 5);
	(*(int(__thiscall **)(int, int))(*(DWORD *)(int)IPlayer.GetOffset() + 180))((int)IPlayer.GetOffset(), AddBuff);

	IPlayer.Buff(12, 1800, SpeedUp ? SpeedUp : 55);
}

void UpdateAutoMissionItem(void* Player, int currentMission) {

	IChar IPlayer(Player);

	if (MissionQuestsItem.count(currentMission))
	{
		MissionInfo mission = MissionQuestsItem.find(currentMission)->second;

		int nextMission = mission.nextmission;
		int questIndex = (currentMission << 16) + 1;
		bool isQuest = (CPlayer::CheckQuestFlag((int)IPlayer.GetOffset(), questIndex) == true);
		int isQuestClear = CPlayer::CheckQuestClear((int)IPlayer.GetOffset(), static_cast<char>(currentMission));
		bool FoundItem = true;
		if (isQuest && !isQuestClear)
		{
			for (int i = 0; i < mission.Items.size(); i++)
			{
				int ItemFound = CPlayer::FindItem(IPlayer.GetOffset(), String2Int(mission.Items[i]), String2Int(mission.Amounts[i]));

				if (!ItemFound)
					FoundItem = false;
			}

			if (FoundItem){
				IPlayer.systemReward(mission.rewardID);
				CQuest::Start((nextMission << 16) | 1, (int)IPlayer.GetOffset());

				for (int i = 0; i < mission.Items.size(); i++)
					CPlayer::RemoveItem(IPlayer.GetOffset(), 9, String2Int(mission.Items[i]), String2Int(mission.Amounts[i]));

				if (!IPlayer.IsBuff(BuffNames::MissionBuff))
					IPlayer.SaveBuff(BuffNames::MissionBuff, BuffNames::BuffTime, nextMission, 0, 0);
				else
					IPlayer.UpdateSavedBuff(BuffNames::MissionBuff, BuffNames::BuffTime, nextMission, 0, 0);

				if (mission.teleportX)
					IPlayer.Teleport(mission.teleportMap, mission.teleportX, mission.teleportY);

				if (PeaceEvil)
					IPlayer.AddHousePoints(2);
			}
		}
	}
}

void SummonIdentify(int Index, int X, int Y, int Time)
{
	Summon(0, 0, X, Y, Index, 1, 0, 0, Time, 0);

}

void SummonPartys()
{
	TargetFind myTarget(1, 0, PartyVPartys::FlagID);
	void *MonsterParty = myTarget.getTarget();

	IChar M1(MonsterParty);

	if (!M1.IsValid())
	{
		IChar N1((void*)Summon(0, 0, 289551, 257125, PVPMobIndex, 1, 0, 0, (PartyTime - 1) * 1000, 0));
		PartyVPartys::FlagID = N1.GetID();
	}
}

void BuffMakerLoad(void* Player)
{
	// Buffsystem
	IChar IPlayer(Player);
	for (auto buffMaker = BuffMakerCheck.begin(); buffMaker != BuffMakerCheck.end(); buffMaker++) {
		int BuffID = buffMaker->second.BuffID;
		if (IPlayer.IsBuff(BuffID) || IPlayer.IsBuff(BuffID + 1000))
		{
			char mana_heal[BUFSIZ], hp_heal[BUFSIZ];
			int MinAttack = buffMaker->second.MinAttack, MaxAttack = buffMaker->second.MaxAttack, Hp = buffMaker->second.Hp, Str = buffMaker->second.Str, Int = buffMaker->second.Int, Wis = buffMaker->second.Wis, Agi = buffMaker->second.Agi, OTP = buffMaker->second.OTP, Eva = buffMaker->second.Eva, Def = buffMaker->second.Def, Fire_Resistance = buffMaker->second.Fire_Resistance, Ice_Resistance = buffMaker->second.Ice_Resistance, Lightning_Resistance = buffMaker->second.Lightning_Resistance, Absorb = buffMaker->second.Absorb, CritRate = buffMaker->second.CritRate, CritDamage = buffMaker->second.CritDamage, Sys_name = buffMaker->second.Sys_name, Time = buffMaker->second.Time, amount = buffMaker->second.amount, count = buffMaker->second.count, mana = buffMaker->second.mana, hp = buffMaker->second.hp, MaxHp = buffMaker->second.MaxHp, MaxMp = buffMaker->second.MaxMp, MD = buffMaker->second.MD, EBRate = buffMaker->second.EBRate;
			int MinPhyAtk = IPlayer.GetMinPhyAttack(), MinMagAttack = IPlayer.GetMinMagAttack(), MaxPhyAtk = IPlayer.GetMaxPhyAttack(), MaxMagAtk = IPlayer.GetMaxMagAttack();

			if (IPlayer.GetCurMp() < IPlayer.GetMaxMp() && (GetTickCount() / 1000) % 1 == 0 && !IPlayer.isDead() && (std::string)mana_heal == "true")
				IPlayer.IncreaseMana(mana);

			if (IPlayer.GetCurHp() < IPlayer.GetMaxHp() && (GetTickCount() / 1000) % 1 == 0 && !IPlayer.isDead() && (std::string)hp_heal == "true")
				IPlayer.IncreaseHp(hp);

			if (IPlayer.IsOnline() && !IPlayer.IsBuff(BuffID + 1000))
			{
				IPlayer.Buff(BuffID + 1000, Time, 0);

				if (IPlayer.IsOnline() && IPlayer.GetBuffRemain(BuffID) > 10 && buffMaker->second.BuffIcon == "true")
					IPlayer.SetBuffIcon(IPlayer.GetBuffRemain(BuffID) * 1000, 0, 0, Sys_name);

				if (MinAttack)
				{
					IPlayer.AddMinAttack((MinPhyAtk * MinAttack) / 100);
					IPlayer.SaveBuff(BuffNames::BuffPhyAtk + (BuffID / 2), Time, ((MinPhyAtk * MinAttack) / 100), 0, 0);
				}
				if (MaxAttack)
				{
					IPlayer.AddMaxAttack((MinMagAttack * MaxAttack) / 100);
					IPlayer.SaveBuff(BuffNames::BuffMagAtk + (BuffID / 2), Time, ((MinMagAttack * MaxAttack) / 100), 0, 0);
				}

				IPlayer.AddStr(Str);
				IPlayer.AddInt(Int);
				IPlayer.AddWis(Wis);
				IPlayer.AddAgi(Agi);
				IPlayer.AddOTP(OTP);
				IPlayer.AddEva(Eva);
				IPlayer.AddDef(Def);
				IPlayer.AddLightning_Resistance(Lightning_Resistance);
				IPlayer.AddIce_Resistance(Ice_Resistance);
				IPlayer.AddFire_Resistance(Fire_Resistance);
				IPlayer.AddAbsorb(Absorb);
				IPlayer.IncreaseCritRate(CritRate);
				IPlayer.IncreaseCritDamage(CritDamage);
				IPlayer.IncreaseMaxHp(MaxHp);
				IPlayer.IncreaseMaxMp(MaxMp);
				IPlayer.IncreaseEBRate(EBRate);
			}

			if (IPlayer.IsOnline() && IPlayer.GetBuffRemain(BuffID) < 10 && IPlayer.IsBuff(BuffID + 1000))
			{
				if (MinAttack)
				{
					IPlayer.RemoveMinAttack(IPlayer.GetBuffValue(BuffNames::BuffPhyAtk + (BuffID / 2)));
					IPlayer.RemoveSavedBuff(BuffNames::BuffPhyAtk + (BuffID / 2));
				}
				if (MaxAttack)
				{
					IPlayer.RemoveMaxAttack(IPlayer.GetBuffValue(BuffNames::BuffMagAtk + (BuffID / 2)));
					IPlayer.RemoveSavedBuff(BuffNames::BuffMagAtk + (BuffID / 2));
				}

				IPlayer.RemoveHp(Hp);
				IPlayer.RemoveStr(Str);
				IPlayer.RemoveInt(Int);
				IPlayer.RemoveWis(Wis);
				IPlayer.RemoveAgi(Agi);
				IPlayer.RemoveOTP(OTP);
				IPlayer.RemoveEva(Eva);
				IPlayer.RemoveDef(Def);
				IPlayer.RemoveLightning_Resistance(Lightning_Resistance);
				IPlayer.RemoveIce_Resistance(Ice_Resistance);
				IPlayer.RemoveFire_Resistance(Fire_Resistance);
				IPlayer.RemoveAbsorb(Absorb);
				IPlayer.DecreaseCritRate(CritRate);
				IPlayer.DecreaseCritDamage(CritDamage);
				IPlayer.DecreaseMaxHp(MaxHp);
				IPlayer.DecreaseMaxMp(MaxMp);
				IPlayer.DecreaseEBRate(EBRate);
				IPlayer.RemoveBuffIcon(0, 0, 0, Sys_name);
				IPlayer.CancelBuff(BuffID + 1000);
				IPlayer.CancelBuff(BuffID);
			}
		}
	}
}

std::string GetDaggerName(int grade) {
	switch (grade) {
	case 48: return "Savage Tribe's Dagger";
	case 50: return "Golden Treasure Dagger";
	case 53: return "Diamond Dagger";
	case 56: return "Ancient Daggers";
	case 59: return "Dagger of Doggebi";
	case 62: return "Golden Dagger";
	case 65: return "Dragon Dagger of Sky";
	case 70: return "Blood Dragon's Dagger";
	case 75: return "Heavenly Executioner Dagger";
	default: return "Unknown Dagger";
	}
}
std::string GetSwordName(int grade, bool isTwoHanded = false) {
	switch (grade) {
	case 48:
		if (isTwoHanded) return "";
		return "Savage Tribe's Treasure Sword";
	case 50:
		if (isTwoHanded) return "Butterfly Shaped Giant Sword";
		return "Golden Treasure Sword";
	case 53:
		if (isTwoHanded) return "Diamond Giant Sword of Phantom";
		return "Diamond Treasure Sword";
	case 56:
		if (isTwoHanded) return "General's Giant Sword";
		return "Ancient Treasure Sword";
	case 59:
		if (isTwoHanded) return "Giant Sword of High Class Doggebi";
		return "Treasure Sword of Doggebi";
	case 62:
		if (isTwoHanded) return "Golden Giant Sword";
		return "Golden Sword";
	case 65:
		if (isTwoHanded) return "Dragon Giant Sword of Sky";
		return "Dragon Sword of Sky";
	case 70:
		if (isTwoHanded) return "Blood Dragon's Giant Sword";
		return "Blood Dragon's Sword";
	case 75:
		if (isTwoHanded) return "Heavenly Executioner Giant Sword";
		return "Heavenly Executioner Sword";
	default:
		return "Unknown Sword";
	}
}

std::string GetStickName(int grade) {
	switch (grade) {
	case 48: return "Savage Tribe's Religious Stick";
	case 50: return "Stick with Black Crow's Feather";
	case 53: return "Diamond Stick";
	case 56: return "Ancient Stick";
	case 59: return "Stick of Doggebi";
	case 62: return "Golden Stick";
	case 65: return "Dragon Stick of Sky";
	case 70: return "Blood Dragon's Stick";
	case 75: return "Heavenly Executioner Stick";
	default: return "Unknown Stick";
	}
}

std::string GetBowName(int grade) {
	switch (grade) {
	case 48: return "Savage Tribe's ChulTae Bow";
	case 50: return "Steel Bow";
	case 53: return "Diamond Bow";
	case 56: return "Ancient Tribal Mac's Bow";
	case 59: return "Bow of Doggebi";
	case 62: return "Golden Bow";
	case 65: return "Dragon Bow of Sky";
	case 70: return "Blood Dragon's Bow";
	case 75: return "Heavenly Executioner Bow";
	default: return "Unknown Bow";
	}
}

std::string GetThiefHoodName(int grade) {
	switch (grade) {
	case 46: return "BeeDan Hood High class thief";
	case 50: return "Diamond Hood of thief";
	case 55: return "Doggebi Hood of thief";
	case 60: return "Golden Helmet of thief";
	case 65: return "Blood Dragon's Hood of thief";
	case 70: return "Heavenly Executioner Hood of thief";
	default: return "Unknown Thief Hood";
	}

}std::string GetThiefGlovesName(int grade) {
	switch (grade) {
	case 46: return "BeeDan Gloves High class thief";
	case 50: return "Diamond Gloves of thief";
	case 55: return "Doggebi Gloves of thief";
	case 60: return "Golden Gloves of thief";
	case 65: return "Blood Dragon's Gloves of thief";
	case 70: return "Heavenly Executioner Gloves of thief";
	default: return "Unknown Thief Gloves";
	}
}

std::string GetThiefShortsName(int grade) {
	switch (grade) {
	case 46: return "BeeDan Shorts High class thief";
	case 50: return "Diamond Shorts of thief";
	case 55: return "Doggebi Shorts of thief";
	case 60: return "Golden Shorts of thief";
	case 65: return "Blood Dragon's Shorts of thief";
	case 70: return "Heavenly Executioner Shorts of thief";
	default: return "Unknown Thief Shorts";
	}
}

std::string GetThiefSuitName(int grade) {
	switch (grade) {
	case 46: return "BeeDan Suit High class thief";
	case 50: return "Diamond Suit of thief";
	case 55: return "Doggebi Suit of thief";
	case 60: return "Golden Suit of thief";
	case 65: return "Blood Dragon's Suit of thief";
	case 70: return "Heavenly Executioner Suit of thief";
	default: return "Unknown Thief Suit";
	}
}

std::string GetThiefBootsName(int grade) {
	switch (grade) {
	case 46: return "BeeDan Boots High class thief";
	case 50: return "Diamond Boots of thief";
	case 55: return "Doggebi Boots of thief";
	case 60: return "Golden Boots of thief";
	case 65: return "Blood Dragon's Boots of thief";
	case 70: return "Heavenly Executioner Boots of thief";
	default: return "Unknown Thief Boots";
	}
}

std::string GetArcherBootsName(int grade) {
	switch (grade) {
	case 46: return "SinGak DooSukLin Shoes";
	case 50: return "Diamond Shoes";
	case 55: return "Shoes of Doggebi";
	case 60: return "Golden Boots";
	case 65: return "Blood Dragon's Boots";
	case 70: return "Heavenly Executioner Boots";
	default: return "Unknown Boots";
	}
}

std::string GetArcherArmorName(int grade) {
	switch (grade) {
	case 46: return "SinGak DooSukLin Armor";
	case 50: return "Diamond Armor";
	case 55: return "Armor of Doggebi";
	case 60: return "Golden Chest";
	case 65: return "Blood Dragon's Chest";
	case 70: return "Heavenly Executioner Chest";
	default: return "Unknown Armor";
	}
}

std::string GetArcherGlovesName(int grade) {
	switch (grade) {
	case 46: return "SinGak DooSukLin Gloves";
	case 50: return "Diamond Gloves";
	case 55: return "Gloves of Doggebi";
	case 60: return "Golden Gloves";
	case 65: return "Blood Dragon's Gloves";
	case 70: return "Heavenly Executioner Gloves";
	default: return "Unknown Gloves";
	}
}

std::string GetArcherShortsName(int grade) {
	switch (grade) {
	case 46: return "SinGak DooSukLin Shorts";
	case 50: return "Diamond Shorts";
	case 55: return "Shorts of Doggebi";
	case 60: return "Golden Shorts";
	case 65: return "Blood Dragon's Shorts";
	case 70: return "Heavenly Executioner Shorts";
	default: return "Unknown Shorts";
	}
}

std::string GetArcherHelmetName(int grade) {
	switch (grade) {
	case 46: return "SinGak DooSukLin Hood";
	case 50: return "Diamond Helmet";
	case 55: return "Helmet of Doggebi";
	case 60: return "Golden Helmet";
	case 65: return "Blood Dragon's Helmet";
	case 70: return "Heavenly Executioner Helmet";
	default: return "Unknown Helmet";
	}
}

std::string GetMageArmorName(int grade) {
	switch (grade) {
	case 46: return "BeeDan DaeChangEau";
	case 50: return "White DaeChangEau";
	case 55: return "DaeChangEau of Doggebi";
	case 60: return "Golden DaeChangEau";
	case 65: return "Blood Dragon's DaeChangEau";
	case 70: return "Heavenly Executioner DaeChangEau";
	default: return "Unknown Mage Armor";
	}
}

std::string GetMageShortsName(int grade) {
	switch (grade) {
	case 46: return "BeeDan DaeChangEau Shorts";
	case 50: return "White DaeChangEau Shorts";
	case 55: return "DaeChangEau Shorts of Doggebi";
	case 60: return "Golden DaeChangEau Shorts";
	case 65: return "Blood Dragon's DaeChangEau Shorts";
	case 70: return "Heavenly Executioner DaeChangEau Shorts";
	default: return "Unknown Mage Shorts";
	}
}

std::string GetMageHairDecorationName(int grade) {
	switch (grade) {
	case 46: return "BeeDan DaeChangEau Hair Decoration";
	case 50: return "White DaeChangEau Hair Decoration";
	case 55: return "DaeChangEau Hair Decoration of Doggebi";
	case 60: return "Golden DaeChangEau Hair Decoration";
	case 65: return "Blood Dragon's DaeChangEau Hair Decoration";
	case 70: return "Heavenly Executioner DaeChangEau Hair Decoration";
	default: return "Unknown Mage Hair Decoration";
	}
}

std::string GetMageGlovesName(int grade) {
	switch (grade) {
	case 46: return "BeeDan DaeChangEau Gloves";
	case 50: return "White DaeChangEau Gloves";
	case 55: return "DaeChangEau Gloves of Doggebi";
	case 60: return "Golden DaeChangEau Gloves";
	case 65: return "Blood Dragon's DaeChangEau Gloves";
	case 70: return "Heavenly Executioner DaeChangEau Gloves";
	default: return "Unknown Mage Gloves";
	}
}

std::string GetMageShoesName(int grade) {
	switch (grade) {
	case 46: return "BeeDan DaeChangEau Shoes";
	case 50: return "White DaeChangEau Shoes";
	case 55: return "DaeChangEau Shoes of Doggebi";
	case 60: return "Golden DaeChangEau Shoes";
	case 65: return "Blood Dragon's DaeChangEau Shoes";
	case 70: return "Heavenly Executioner DaeChangEau Shoes";
	default: return "Unknown Mage Shoes";
	}
}

std::string GetKnightArmorName(int grade) {
	switch (grade) {
	case 46: return "Intensified Steel Armor";
	case 50: return "Diamond Scaled Armor";
	case 55: return "Scaled Armor of Doggebi";
	case 60: return "Golden Scaled Armor";
	case 65: return "Blood Dragon's Scaled Armor";
	case 70: return "Heavenly Executioner Scaled Armor";
	default: return "Unknown Knight Armor";
	}
}

std::string GetKnightShortsName(int grade) {
	switch (grade) {
	case 46: return "Intensified Steel Shorts";
	case 50: return "Diamond Scaled Shorts";
	case 55: return "Scaled Shorts of Doggebi";
	case 60: return "Golden Scaled Shorts";
	case 65: return "Blood Dragon's Scaled Shorts";
	case 70: return "Heavenly Executioner Scaled Shorts";
	default: return "Unknown Knight Shorts";
	}
}

std::string GetKnightHelmetName(int grade) {
	switch (grade) {
	case 46: return "Intensified Steel Helmet";
	case 50: return "Diamond Scaled Helmet";
	case 55: return "Scaled Helmet of Doggebi";
	case 60: return "Golden Scaled Helmet";
	case 65: return "Blood Dragon's Scaled Helmet";
	case 70: return "Heavenly Executioner Scaled Helmet";
	default: return "Unknown Knight Helmet";
	}
}
std::string GetKnightGlovesName(int grade) {
	switch (grade) {
	case 46: return "Intensified Steel Gloves";
	case 50: return "Diamond Scaled Gloves";
	case 55: return "Scaled Gloves of Doggebi";
	case 60: return "Golden Scaled Gloves";
	case 65: return "Blood Dragon's Scaled Gloves";
	case 70: return "Heavenly Executioner Scaled Gloves";
	default: return "Unknown Knight Gloves";
	}
}
std::string GetKnightBootsName(int grade) {
	switch (grade) {
	case 46: return "Intensified Steel Shoes";
	case 50: return "Diamond Scaled Shoes";
	case 55: return "Scaled Boots of Doggebi";
	case 60: return "Golden Scaled Boots";
	case 65: return "Blood Dragon's Scaled Boots";
	case 70: return "Heavenly Executioner Scaled Boots";
	default: return "Unknown Knight Boots";
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

	bool isValidRange = false;

	if (IPlayer.IsInRange(ITarget, maxrange))
		isValidRange = true;


	return isValidRange;

}

void HonorPromotion(int PID)
{
	if (HonorNotices){
		TargetFind myTarget(0, 1, PID);
		int Player = (int)myTarget.getTarget();
		IChar IPlayer((void*)Player);
		std::string playerName = IPlayer.GetName();

		std::string msg = "Player [" + playerName + "] has been promoted to ";
		int honorThresholds[] = { 2790, 4960, 7750, 12090, 20150, 35030, 44640, 57970, 78740, 111600 };
		std::string ranks[] = { "[Recruit]", "[Private]", "[Specialist]", "[Corporal]", "[Sergeant]", "[Lieutenant]", "[Captain]", "[Major]", "[Colonel]", "[General]" };
		for (int i = 0; i < 10; ++i) {
			if (IPlayer.GetProperty(PlayerProperty::HPx) >= honorThresholds[i] && IPlayer.GetHonorTag() == i) {
				std::string rank = ranks[i];
				int textColor = NOTICECOLOR_PINK;
				int messageType = 2;
				RewardMessage reward;
				reward.message = msg + rank;
				reward.textColor = textColor;
				reward.messageType = messageType;
				ToHonorNoticeWebhook(msg + rank);
				PlayerRewardNotice.push_back(reward);
				break;
			}
		}
	}
}
//
//void ApplyBuff(IChar& member, int buffID, int buffValue) {
//	if (!member.IsBuff(buffID)) {
//		member.SetBuffIcon(-2, -1, 8300, 8300);
//		member.Buff(buffID, BuffNames::BuffTime, buffValue);
//	}
//}
//
//void RemoveBuff(IChar& player, int buffID) {
//	player.CancelBuff(buffID);
//	player.RemoveBuffIcon(0, 0, 8300, 8300);
//}
//
//void ApplyPartyBuff(IChar& player, int partySize, int partyBuffID, int buffValue, int partyBuffRange) {
//	for (int i = CParty::GetPlayerList((void*)player.GetPartyID()); i; i = CBaseList::Pop((void*)i)) {
//		int memberAddress = *(DWORD*)((void*)i);
//		IChar member((void*)memberAddress);
//
//		if (member.IsValid()) {
//			int memberRange = CChar::GetRange((int)member.GetOffset() + 332, memberAddress + 332);
//
//			if (memberRange <= partyBuffRange) {
//				ApplyBuff(member, partyBuffID, buffValue);
//			}
//			else {
//				RemoveBuff(member, partyBuffID);
//			}
//		}
//	}
//}
//
//void ProcessPartyBuffs(IChar& player, int partyBuffRange, int* expValues) {
//	if (player.IsParty()) {
//		int party = CParty::FindParty(player.GetPartyID());
//
//		if (party) {
//			int partySize = CParty::GetSize((void*)party);
//
//			switch (partySize) {
//			case 3:
//			case 4:
//			case 5:
//			case 6:
//			case 7:
//			case 8:
//				ApplyPartyBuff(player, partySize, 1700 + partySize - 3, expValues[partySize], partyBuffRange);
//				break;
//			default:
//				break;
//			}
//
//			CIOObject::Release((void*)party);
//		}
//	}
//	else {
//		for (int i = 0; i < 8; i++) {
//			if (player.IsBuff(1700 + i))
//				player.CancelBuff(1700 + i);
//		}
//	}
//}
//void tester(void* Player)
//{
//    int PartyBuffActive = 1;
//    int PartyBuffRange = 30;
//    int EXPValues[] = {0, 0, 0, 10, 15, 20, 25, 30, 35};
//	IChar IPlayer;
//
//	if (PartyBuffActive) {
//		ProcessPartyBuffs(IPlayer, PartyBuffRange, EXPValues);
//	}
//
//	if (PartyBuffActive){
//		if (IPlayer.IsParty())
//		{
//			int Party = CParty::FindParty(IPlayer.GetPartyID());
//
//			if (Party){
//				int PartySize = CParty::GetSize((void*)Party);
//
//				for (int i = CParty::GetPlayerList((void*)Party); i; i = CBaseList::Pop((void *)i))
//				{
//					int Members = *(DWORD*)((void*)i);
//					IChar IMembers((void*)*(DWORD*)((void*)i));
//					if (IMembers.IsValid()){
//						switch (PartySize){
//						case 3:
//							if (CChar::GetRange((int)IMembers.GetOffset() + 332, Members + 332) <= PartyBuffRange)
//							{
//								if (!IMembers.IsBuff(1700)){
//									IMembers.SetBuffIcon(-2, -1, 8300, 8300);
//									IMembers.Buff(1700, BuffNames::BuffTime, EXPValues[3]);
//								}
//							}
//							else
//							{
//								IPlayer.CancelBuff(1700);
//								IPlayer.RemoveBuffIcon(0, 0, 8300, 8300);
//							}
//							break;
//						case 4:
//							if (CChar::GetRange((int)IMembers.GetOffset() + 332, Members + 332) <= PartyBuffRange)
//							{
//								if (!IMembers.IsBuff(1701)){
//									IMembers.SetBuffIcon(-2, -1, 8300, 8300);
//									IMembers.Buff(1701, BuffNames::BuffTime, EXPValues[4]);
//								}
//							}
//							else
//							{
//								IPlayer.CancelBuff(1701);
//								IPlayer.RemoveBuffIcon(0, 0, 8300, 8300);
//							}
//							break;
//						case 5:
//							if (CChar::GetRange((int)IMembers.GetOffset() + 332, Members + 332) <= PartyBuffRange)
//							{
//								if (!IMembers.IsBuff(1702)){
//									IMembers.SetBuffIcon(-2, -1, 8300, 8300);
//									IMembers.Buff(1702, BuffNames::BuffTime, EXPValues[5]);
//								}
//							}
//							else
//							{
//								IPlayer.CancelBuff(1702);
//								IPlayer.RemoveBuffIcon(0, 0, 8300, 8300);
//							}
//							break;
//						case 6:
//							if (CChar::GetRange((int)IMembers.GetOffset() + 332, Members + 332) <= PartyBuffRange) {
//								if (!IMembers.IsBuff(1703)) {
//									IMembers.SetBuffIcon(-2, -1, 8300, 8300);
//									IMembers.Buff(1703, BuffNames::BuffTime, EXPValues[6]);
//								}
//							}
//							else {
//								IPlayer.CancelBuff(1703);
//								IPlayer.RemoveBuffIcon(0, 0, 8300, 8300);
//							}
//							break;
//						case 7:
//							if (CChar::GetRange((int)IMembers.GetOffset() + 332, Members + 332) <= PartyBuffRange) {
//								if (!IMembers.IsBuff(1704)) {
//									IMembers.SetBuffIcon(-2, -1, 8300, 8300);
//									IMembers.Buff(1704, BuffNames::BuffTime, EXPValues[7]);
//								}
//							}
//							else {
//								IPlayer.CancelBuff(1704);
//								IPlayer.RemoveBuffIcon(0, 0, 8300, 8300);
//							}
//							break;
//						case 8:
//							if (CChar::GetRange((int)IMembers.GetOffset() + 332, Members + 332) <= PartyBuffRange) {
//								if (!IMembers.IsBuff(1705)) {
//									IMembers.SetBuffIcon(-2, -1, 8300, 8300);
//									IMembers.Buff(1705, BuffNames::BuffTime, EXPValues[8]);
//								}
//							}
//							else {
//								IPlayer.CancelBuff(1705);
//								IPlayer.RemoveBuffIcon(0, 0, 8300, 8300);
//							}
//							break;
//						default: break;
//						}
//					}
//				}
//				CIOObject::Release((void*)Party);
//			}
//		}
//		if (!IPlayer.IsParty())
//		{
//			for (int i = 0; i < 8; i++){
//				if (IPlayer.IsBuff(1700 + i))
//					IPlayer.CancelBuff(1700 + i);
//			}
//		}
//	}
//}
void UpdateHonorStats(void* Player)
{
	IChar IPlayer(Player);
	int HonorP = IPlayer.GetHonorTag();

	if (IPlayer.IsOnline() && HonorP >= 1 && HonorP <= 10) {
		int MinPhyAtk = IPlayer.GetMinPhyAttack();
		int MaxPhyAtk = IPlayer.GetMaxPhyAttack();

		if (IPlayer.GetClass() == 1) {
			MinPhyAtk = IPlayer.GetMinMagAttack();
			MaxPhyAtk = IPlayer.GetMaxMagAttack();
		}

		for (int i = 1; i <= 10; ++i) {
			if (HonorP == i) {
				int honorStats = 0;
				int honorPVE = 0;
				int honorPVP = 0;
				int honorEB = 0;
				int honorFatal = 0;
				int honorSys = 0;

				switch (i) {
				case 1: honorStats = Honor1Stats; honorPVE = Honor1PVE; honorPVP = Honor1PVP; honorEB = Honor1EB; honorFatal = Honor1Fatal; honorSys = Honor1Sys; break;
				case 2: honorStats = Honor2Stats; honorPVE = Honor2PVE; honorPVP = Honor2PVP; honorEB = Honor2EB; honorFatal = Honor2Fatal; honorSys = Honor2Sys; break;
				case 3: honorStats = Honor3Stats; honorPVE = Honor3PVE; honorPVP = Honor3PVP; honorEB = Honor3EB; honorFatal = Honor3Fatal; honorSys = Honor3Sys; break;
				case 4: honorStats = Honor4Stats; honorPVE = Honor4PVE; honorPVP = Honor4PVP; honorEB = Honor4EB; honorFatal = Honor4Fatal; honorSys = Honor4Sys; break;
				case 5: honorStats = Honor5Stats; honorPVE = Honor5PVE; honorPVP = Honor5PVP; honorEB = Honor5EB; honorFatal = Honor5Fatal; honorSys = Honor5Sys; break;
				case 6: honorStats = Honor6Stats; honorPVE = Honor6PVE; honorPVP = Honor6PVP; honorEB = Honor6EB; honorFatal = Honor6Fatal; honorSys = Honor6Sys; break;
				case 7: honorStats = Honor7Stats; honorPVE = Honor7PVE; honorPVP = Honor7PVP; honorEB = Honor7EB; honorFatal = Honor7Fatal; honorSys = Honor7Sys; break;
				case 8: honorStats = Honor8Stats; honorPVE = Honor8PVE; honorPVP = Honor8PVP; honorEB = Honor8EB; honorFatal = Honor8Fatal; honorSys = Honor8Sys; break;
				case 9: honorStats = Honor9Stats; honorPVE = Honor9PVE; honorPVP = Honor9PVP; honorEB = Honor9EB; honorFatal = Honor9Fatal; honorSys = Honor9Sys; break;
				case 10: honorStats = Honor10Stats; honorPVE = Honor10PVE; honorPVP = Honor10PVP; honorEB = Honor10EB; honorFatal = Honor10Fatal; honorSys = Honor10Sys; break;
				}

				IPlayer.AddAgi(honorStats);
				IPlayer.AddStr(honorStats);
				IPlayer.AddHp(honorStats);
				IPlayer.AddWis(honorStats);
				IPlayer.AddInt(honorStats);
				IPlayer.Buff(BuffNames::HonorPVE, BuffNames::BuffTime, honorPVE);
				IPlayer.Buff(BuffNames::HonorPVP, BuffNames::BuffTime, honorPVP);
				IPlayer.AddDeathBlow(honorEB);
				IPlayer.Buff(BuffNames::HonorFatal, BuffNames::BuffTime, honorFatal);
				IPlayer.SetBuffIcon(-2, -1, honorSys, honorSys);

				break;
			}
		}
	}
}

void UpdateNewMyst(void* Player) {
	if (NewMystEnable) {

		IChar IPlayer(Player);

		int buffTypes[] = { BuffNames::MystOTP, BuffNames::MystEVA, BuffNames::MystHP, BuffNames::MystPhy, BuffNames::MystMag, BuffNames::MystDef };
		int buffIcons[] = { MystOTPS, MystEVAS, MystHPS, MystPAtkS, MystMAtkS, MystDefS };
		int statIncrements[] = { 2, 2, 250, 10, 10, 10 };

		for (int i = 0; i < 6; ++i) {
			int buffType = buffTypes[i];
			int buffIcon = buffIcons[i];
			int statIncrement = statIncrements[i];

			if (IPlayer.IsBuff(buffType)) {
				int checkGrade = 0;
				int getGrade = IPlayer.GetBuffValue(buffType);

				if (IPlayer.GetLevel() >= MystLevelMax)
					checkGrade = 30;
				else
					checkGrade = IPlayer.GetLevel() - MystLevel + 1;


				IPlayer.SaveBuff(buffType, BuffNames::BuffTime, checkGrade, 0, 0);
				IPlayer.SetBuffIcon(-2, -1, buffIcon, buffIcon);

				if (checkGrade) {
					switch (i) {
					case 0: IPlayer.AddOTP(2 * checkGrade); break;
					case 1: IPlayer.AddEva(2 * checkGrade); break;
					case 2: IPlayer.IncreaseMaxHp(250 * checkGrade); break;
					case 3: IPlayer.AddMinAttack(10 * checkGrade); break;
					case 4: IPlayer.AddMaxAttack(10 * checkGrade); break;
					case 5: IPlayer.AddDef(10 * checkGrade); break;
					}
				}
				else {
					switch (i) {
					case 0: IPlayer.AddOTP(2); break;
					case 1: IPlayer.AddEva(2); break;
					case 2: IPlayer.IncreaseMaxHp(250); break;
					case 3: IPlayer.AddMinAttack(10); break;
					case 4: IPlayer.AddMaxAttack(10); break;
					case 5: IPlayer.AddDef(10); break;
					}
				}
			}
		}
	}
}
