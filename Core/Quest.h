void InsertJewels1(void* Player,int DonaAmount,int JewelsAmount){
	IChar IPlayer(Player);
	if (GetInventorySize((int)IPlayer.GetOffset(), 0) < 60) {
		if (CPlayer::RemoveItem(IPlayer.GetOffset(), 9, DonationCoin, DonaAmount)) {
			int MakeItem = CItem::CreateItem(JewelIndex, 0, JewelsAmount, -1);
			int v15 = MakeItem;
			if (MakeItem) {
				if (CPlayer::InsertItem(Player, 7, MakeItem) != 1)
					CBase::Delete((void*)v15);
			}
			IPlayer.OpenHTML(941);
		}
		else
			IPlayer.OpenHTML(999018);
	}else
		CPlayer::Write(IPlayer.GetOffset(), 67, "b", 40);
}

void InsertJewels(void* Player, int DonaAmount, int JewelsAmount) {
	IChar IPlayer(Player);
	if (CPlayer::RemoveItem(IPlayer.GetOffset(), 9, DonationCoin, DonaAmount)) {
		IPlayer.GiveReward(JewelIndex, 0, JewelsAmount, 0, 0, 0, 0, 0, 0, 0, 0, "Thank you for your contribution to our server.");
		//CItem::InsertItem((int)IPlayer.Offset, 27, 3360, 0, JewelsAmount, -1);
		IPlayer.OpenHTML(941);
	}
	else
		IPlayer.OpenHTML(999018);
}

bool SaveTimedQuest(IChar IPlayer, int Index, int Flag, bool save) {
	if (IPlayer.IsOnline() && TimedQuest.count((Index * 1000) + Flag)) {
		QuestTime qTime = TimedQuest.find((Index * 1000) + Flag)->second;

		long MIndex = uniqueKey((Index * 10) + Flag, IPlayer.GetPID());
		QuestTime quest = QuestTime();

		if (PlayerTimedQuest.count(MIndex)) {
			quest = PlayerTimedQuest.findValue(MIndex);

			if (quest.MaxRepeat >= qTime.MaxRepeat) {
				int Time = (int)time(0) - quest.Time;

				if (Time < 0)
				{
					int Day = (Time / 86400) * -1;
					int Hour = ((Time / 3600) % 24) * -1;
					int Minute = ((Time / 60) % 60) * -1;
					int Second = (Time % 60) * -1;
					std::string msg = "You can use the quest again in: " + Int2String(Day) + " Days " + Int2String(Hour) + " Hours " + Int2String(Minute) + " Minutes " + Int2String(Second) + " Seconds.";
					IPlayer.SystemMessage(msg, TEXTCOLOR_RED);
					return false;
				}
				else
					quest.MaxRepeat = 0;
			}
		}

		if (save) {
			quest.MaxRepeat++;
			if(!qTime.Type)
				quest.Time = (int)time(0) + qTime.Time;
			else {
				int Time = 0;
				int TimeIndex = (String2Int(Time::GetHour()) * 3600) + (String2Int(Time::GetMinute()) * 60) + String2Int(Time::GetSecond());
				
				if (TimeIndex > qTime.Time)
					Time = (24 * 3600) - (TimeIndex - qTime.Time);
				else
					Time = qTime.Time - TimeIndex;

				quest.Time = (int)time(0) + Time;
			}
				
			bool edited = false;

			string line;
			ifstream fin;
			fin.open("./Database/TimedQuest.db");
			ofstream temp;
			temp.open("./Database/tempQ.txt");
			while (getline(fin, line))
			{
				int Type = 0, Repeat = 0, Time = 0;
				if (sscanf(line.c_str(), "(timedQuest (ID %d)(Repeat %d)(Time %d))", &Type, &Repeat, &Time) == 3)
				{
					if (Type == MIndex) {
						edited = true;
						temp << "(timedQuest (ID " << MIndex << ")(Repeat " << quest.MaxRepeat << ")(Time " << quest.Time << "))" << endl;
					}
					else
						temp << line << endl;
				}
			}
			temp.close();
			fin.close();
			remove("./Database/TimedQuest.db");
			rename("./Database/tempQ.txt", "./Database/TimedQuest.db");

			if (!edited) {
				std::string Datko = "./Database/TimedQuest.db";
				std::fstream DGkLOG;
				DGkLOG.open(Datko, std::fstream::in | std::fstream::out | std::fstream::app);
				DGkLOG << "(timedQuest (ID " << MIndex << ")(Repeat " << quest.MaxRepeat << ")(Time " << quest.Time << "))" << std::endl;
				DGkLOG.close();
			}

			PlayerTimedQuest.replaceInsert(MIndex, quest);
		}
	}

	return true;
}

void __fastcall Quest(void *QuestOffset, void *edx, int PlayerOffset)
{
	IQuest Quest(QuestOffset); 

	IChar IPlayer((void*)PlayerOffset);
	int MapX = IPlayer.GetX() >> 13;
	int MapY = IPlayer.GetY() >> 13;

	if (questDebug == 1) {
		std::string Datoe = "./Debugger/Quest/QUEST_" + Time::GetDay() + "_" + Time::GetMonth() + "_" + Time::GetYear() + "_" + Time::GetHour() + "." + Time::GetMinute() + ".txt";
		std::fstream CHLOG;
		CHLOG.open(Datoe, std::fstream::in | std::fstream::out | std::fstream::app);
		CHLOG << Time::GetTime() << " " << IPlayer.GetName() << ": " << Quest.GetIndex() << std::endl;
		CHLOG.close();
	}

	if (IPlayer.IsOnline() && QuestDisable.count((Quest.GetIndex() * 10000) + Quest.GetFlag()) || QuestDisable.count((Quest.GetIndex() * 10000) + Quest.GetFlag()+(IPlayer.GetMap() * 5000)) || QuestDisable.count((Quest.GetIndex() * 10000) + Quest.GetFlag()+((MapX * 100)+(MapY * 10)))) {
		IPlayer.SystemMessage("This feature is currently disabled.", TEXTCOLOR_RED);
		return;
	}
	
	if (IPlayer.IsOnline() && QuestLevels.count((Quest.GetIndex() * 1000) + Quest.GetFlag())) {
		QuestLevel qlvl = QuestLevels.find((Quest.GetIndex() * 1000) + Quest.GetFlag())->second;
		if ((IPlayer.GetLevel() < qlvl.LevelMin) || (IPlayer.GetLevel() > qlvl.LevelMax)) {
			IPlayer.SystemMessage("This feature only applies for levels between " + Int2String(qlvl.LevelMin) + " and " + Int2String(qlvl.LevelMax) + ".", TEXTCOLOR_RED);
			return;
		}
	}

	if (IPlayer.IsOnline() && Quest.GetIndex() == EmoteQuest) {
		int questFlag = Quest.GetFlag();
		if (EmoteSystem.count(questFlag)) {
			const std::pair<std::string, int>& emoteData = EmoteSystem.find(questFlag)->second;
			const std::string& particle = emoteData.first;
			int itemIndex = emoteData.second;

			if (!IPlayer.IsBuff(BuffNames::Emote)) {
				if (itemIndex && !CPlayer::FindItem((void*)PlayerOffset, itemIndex, 1)){
					IPlayer.SystemMessage("You dont have the required item to use Emote.", TEXTCOLOR_RED);
					return;
				}

				IPlayer.AddFxToBone(particle.c_str(), 0);
				IPlayer.Buff(BuffNames::Emote, EmoteCooldown, questFlag);
				return;
			}
			else {
				IPlayer.SystemMessage("You need to wait " + Int2String(IPlayer.GetBuffRemain(BuffNames::Emote)) + " seconds to use Emote Feature", TEXTCOLOR_RED);
				return;
			}
		}
		return;
	}

	if (IPlayer.IsOnline() && DutyQuest.count(Quest.GetIndex()))
	{
		int QLvl = DutyQuest.find(Quest.GetIndex())->second.pLevel;
		int QTime = DutyQuest.find(Quest.GetIndex())->second.cooldown;
		int QID = Quest.GetIndex();

		if (IPlayer.GetLevel() < QLvl)
		{
			IPlayer.SystemMessage("Your level must be " + Int2String(QLvl) + " or higher.", TEXTCOLOR_RED);
			return;
		}

		if (IPlayer.IsBuff(BuffNames::DutyTrigger + QID))
		{
			int TriggerValue = IPlayer.GetBuffRemain(BuffNames::DutyTrigger + QID);
			int Day = (TriggerValue / 86400);
			int Hour = ((TriggerValue / 3600) % 24);
			int Minute = ((TriggerValue / 60) % 60);
			int Second = (TriggerValue % 60);
			std::string msg = "You need to wait " + Int2String(Day) + " Days " + Int2String(Hour) + " Hours " + Int2String(Minute) + " Minutes " + Int2String(Second) + " Seconds.";
			IPlayer.SystemMessage(msg, TEXTCOLOR_RED);

			return;
		}
		else 
			if (!IPlayer.IsBuff(BuffNames::DailyDuty + QID)){
				IPlayer.StartDutyQuest(QID, 0, 0, 1);
				IPlayer.Buff(BuffNames::DailyDuty + QID, BuffNames::BuffTime, QID);
				CDBSocket::Write(125, "dddddd", 4, IPlayer.GetPID(), QID, 0, 0, 0);
			//	IPlayer.SaveBuff(BuffNames::DutyDelete, BuffNames::BuffTime, QID, 0, 0);
				return;
			}
			else{
				IPlayer.SystemMessage("You already have quest", TEXTCOLOR_RED);
				return;
			}
	}

	if (IPlayer.IsOnline() && Quest.GetIndex() == StoreCheckQuest)
	{
		IPlayer.SystemMessage(Int2String(StoreSoldCheck) + " has been withdrawal from server in total", TEXTCOLOR_INFOMSG);
		return;
	}

	//if (IPlayer.IsOnline() && Quest.GetIndex() == EmoteQuest) {
	//	int questFlag = Quest.GetFlag();
	//	if (EmoteSystem.count(questFlag)) {
	//		const std::string& particle = EmoteSystem.find(questFlag)->second;
	//		if (!IPlayer.IsBuff(BuffNames::Emote)){
	//			IPlayer.AddParticleE(particle.c_str(), 0); // Use c_str() to pass a const char*
	//			IPlayer.Buff(BuffNames::Emote, EmoteCooldown, 0);
	//		}
	//		else
	//			IPlayer.SystemMessage("You need to wait " + Int2String(IPlayer.GetBuffRemain(BuffNames::Emote)) + " seconds to use Emote Feature", TEXTCOLOR_RED);
	//	}
	//}

	if (IPlayer.IsOnline() && Quest.GetIndex() == AutoMissionQuest){

		bool questFound = false;

			for (auto x = MissionQuestsItem.begin(); x != MissionQuestsItem.end(); x++)
			{
				int currentMission = x->first;
				int questIndex = (currentMission << 16) + 1;
				bool isQuest = (CPlayer::CheckQuestFlag((int)IPlayer.GetOffset(), questIndex) == true);
				int isQuestClear = CPlayer::CheckQuestClear((int)IPlayer.GetOffset(), static_cast<char>(currentMission));

				if (isQuest && isQuestClear)
					continue;

				if (isQuest && !isQuestClear){
					if (!IPlayer.IsBuff(BuffNames::MissionBuff))
						IPlayer.SaveBuff(BuffNames::MissionBuff, BuffNames::BuffTime, currentMission, 0, 0);
					else
					IPlayer.UpdateSavedBuff(BuffNames::MissionBuff, BuffNames::BuffTime, currentMission, 0, 0);
					questFound = true;
					break;
				}
			}
			if (!questFound)
				IPlayer.SaveBuff(BuffNames::MissionBuff, BuffNames::BuffTime, 0, 0, 0);

	}

	if (IPlayer.IsOnline() && AreaQuests.count((Quest.GetIndex() * 1000) + Quest.GetFlag()))
	{
		if (IPlayer.IsBuff(BuffNames::AreaQuest))
		{
			std::string msg = "You need to complete this area first.";
			IPlayer.SystemMessage(msg.c_str(), TEXTCOLOR_RED);
			return;
		}

		if (IPlayer.GetBuffValue(2167) == (Quest.GetIndex() * 1000) + Quest.GetFlag())
		{
			std::string msg = "You need to wait " + Int2String(IPlayer.GetBuffRemain(2167)) + " seconds to re-join the area.";
			IPlayer.SystemMessage(msg.c_str(), TEXTCOLOR_RED);
			return;
		}

		AreaQuest aQuest = AreaQuests.find((Quest.GetIndex() * 1000) + Quest.GetFlag())->second;

		if (IPlayer.IsParty())
		{
			if (aQuest.Party == 2) {
				IPlayer.SystemMessage("This quest must be done in solo mode!", TEXTCOLOR_RED);
				return;
			}

			int Party = CParty::FindParty(IPlayer.GetPartyID());

			if (!Party)
				return;

			if (!CParty::IsHead(Party, (int)IPlayer.Offset))
			{
				IPlayer.SystemMessage("You are not the party leader to start Picture Of Hell.", TEXTCOLOR_RED);
				CIOObject::Release((void*)Party);
				return;
			}

			bool notAllowed = false;

			for (int i = CParty::GetPlayerList((void*)Party); i; i = CBaseList::Pop((void *)i))
			{
				int Members = *(DWORD*)((void*)i);
				IChar Member((void*)*(DWORD*)((void*)i));

				if (CChar::IsNormal(Members) && IPlayer.IsValid())
				{
					if (Member.GetLevel() < aQuest.LevelMin || Member.GetLevel() > aQuest.LevelMax || Member.IsBuff(BuffNames::AreaQuest) || !SaveTimedQuest(Member, Quest.GetIndex(), Quest.GetFlag(), false) || Member.GetBuffValue(2167) == (Quest.GetIndex() * 1000) + Quest.GetFlag())
						notAllowed = true;
				}
				else
					notAllowed = true;
			}

			if (notAllowed) {
				IPlayer.SystemMessage("Some of your party members do not meet the level requirements or have time limit.", TEXTCOLOR_RED);
				CIOObject::Release((void*)Party);
				return;
			}

			for (int i = CParty::GetPlayerList((void*)Party); i; i = CBaseList::Pop((void *)i))
			{
				int Members = *(DWORD*)((void*)i);
				IChar Member((void*)*(DWORD*)((void*)i));

				if (CChar::IsNormal(Members) && IPlayer.IsValid())
				{
					Member.ScreenTime(aQuest.Time + 1);
					Member.Teleport(aQuest.TMap, aQuest.TX, aQuest.TY);
					Member.Buff(BuffNames::AreaQuest, aQuest.Time, (Quest.GetIndex() * 1000) + Quest.GetFlag());
					SaveTimedQuest(Member, Quest.GetIndex(), Quest.GetFlag(), true);
				}
			}
			CIOObject::Release((void*)Party);
		}
		else {
			if (aQuest.Party == 1) {
				IPlayer.SystemMessage("This quest must be done in party mode!", TEXTCOLOR_RED);
				return;
			}

			if (IPlayer.GetLevel() < aQuest.LevelMin || IPlayer.GetLevel() > aQuest.LevelMax) {
				IPlayer.SystemMessage("You do not meet the level requirements for this quest", TEXTCOLOR_RED);
				return;
			}
			if (!SaveTimedQuest(IPlayer, Quest.GetIndex(), Quest.GetFlag(), false))
				return;

			if (IPlayer.IsValid()) {
				IPlayer.ScreenTime(aQuest.Time + 1);
				IPlayer.Teleport(aQuest.TMap, aQuest.TX, aQuest.TY);
				IPlayer.Buff(BuffNames::AreaQuest, aQuest.Time, (Quest.GetIndex() * 1000) + Quest.GetFlag()); 
				SaveTimedQuest(IPlayer, Quest.GetIndex(), Quest.GetFlag(), true);
			}
		}

		return;
	}

	if (!SaveTimedQuest(IPlayer, Quest.GetIndex(), Quest.GetFlag(),true))
		return;


	if (IPlayer.IsOnline() && Quest.GetIndex() == (F10Quest % 65536))
	{
		if (F10::Active == true)
		{
			IPlayer.SystemMessage("You can not register while Company System running.", TEXTCOLOR_RED);
			return;
		}

		if (F10Registration.count(IPlayer.GetPID()))
		{
			IPlayer.SystemMessage("You already registered to Company System.", TEXTCOLOR_RED);
			return;
		}
		if (IPlayer.GetLevel() < F10Level)
		{
			IPlayer.SystemMessage("You must be atleast level " + Int2String(F10Level) + " to register for Company System", TEXTCOLOR_RED);
			return;
		}
		else {
			F10Registration.insert(IPlayer.GetPID());
			F10::RegisterAmount += 1;
			IPlayer.SystemMessage("Successfully registered to Company System.", TEXTCOLOR_GREEN);
			return;
		}

		return;
	}

	if (IPlayer.IsOnline() && Quest.GetIndex() == (MautQuest % 65536))
	{
		if (Maut::Active == true)
		{
			IPlayer.SystemMessage("You can not register while Mautareta System running.", TEXTCOLOR_RED);
			return;
		}

		if (MautRegistration.count(IPlayer.GetPID()))
		{
			IPlayer.SystemMessage("You already registered to Mautareta System.", TEXTCOLOR_RED);
			return;
		}
		if (IPlayer.GetLevel() < MautLevel)

		{
			IPlayer.SystemMessage("You must be atleast level " + Int2String(MautLevel) + " to register for Mautareta System.", TEXTCOLOR_RED);
			return;
		}

		else {
			MautRegistration.insert(IPlayer.GetPID());
			Maut::RegisterAmount += 1;
			IPlayer.SystemMessage("Successfully registered to Mautareta System.", TEXTCOLOR_GREEN);
			return;
		}

		return;
	}

	if (IPlayer.IsOnline() && Quest.GetIndex() == (BossEXPQuest % 65536))
	{
		std::string SysName(BossEXPName);
		if (BossEXP::Active == true)
		{
			IPlayer.SystemMessage("You can not register while "+ SysName +" is running.", TEXTCOLOR_RED);
			return;
		}

		if (BossEXPRegistration.count(IPlayer.GetPID()))
		{
			IPlayer.SystemMessage("You already registered to "+ SysName+".", TEXTCOLOR_RED);
			return;
		}
		else {
			BossEXPRegistration.insert(IPlayer.GetPID());
			BossEXP::RegisterAmount += 1;
			IPlayer.SystemMessage("Successfully registered to " + SysName + ".", TEXTCOLOR_GREEN);
			return;
		}

		return;
	}

	if (IPlayer.IsOnline() && Combinators.count((Quest.GetIndex() * 1000) + Quest.GetFlag())) {
		Combinator cItem = Combinators.find((Quest.GetIndex() * 1000) + Quest.GetFlag())->second;

		if (cItem.Index) {
			int Amount = 0;

			while (int Item = CPlayer::FindItem((void*)PlayerOffset, cItem.Index, 1)) {
				Amount += *(DWORD *)(Item + 52);
				IPlayer.RemoveItemDir(Item);
			}

			if (Amount) {
				IPlayer.InsertItem(cItem.Index, cItem.Bound == 1 ? 256 : 0, Amount);
				IPlayer.SystemMessage("You have combined " + Int2String(Amount) + " items.", TEXTCOLOR_GREEN);
			}
			else
				IPlayer.SystemMessage("You have no items to combine.", TEXTCOLOR_RED);
		}

		return;
	}

	if (IPlayer.IsOnline() && SummonQuest.count((Quest.GetIndex() * 1000) + Quest.GetFlag())) {
		MSummonConfig msConfig = SummonQuest.find(((Quest.GetIndex() * 1000) + Quest.GetFlag()))->second;

		if (msConfig.Type) {
			IPlayer.SystemMessage(Int2String((msConfig.ItemAmount - (SummonedQuest.count(msConfig.QIndex) ? SummonedQuest.findValue(msConfig.QIndex).CurAmount : 0))) + " Items left for the monster to summon!", TEXTCOLOR_GREEN);
			return;
		}
		else if (SummonedQuest.count((Quest.GetIndex() * 1000) + Quest.GetFlag())) {
			int DNPCItemCheck = CPlayer::FindItem(IPlayer.GetOffset(), msConfig.ItemIndex, 1);

			if (!DNPCItemCheck)
			{
				IPlayer.SystemMessage("You do not have any item to collect!", TEXTCOLOR_RED);
				return;
			}

			MSummonedConfig msedConfig = SummonedQuest.findValue(((Quest.GetIndex() * 1000) + Quest.GetFlag()));

			if (msConfig.Limit && msedConfig.Limit == msConfig.Limit) {
				IPlayer.SystemMessage("Daily Limit has been reached. Please wait untill tomorrow.", TEXTCOLOR_RED);
				return;
			}

			if (msConfig.Check && msedConfig.Spawned)
			{
				IPlayer.SystemMessage("Please wait untill the current monsters are killed.", TEXTCOLOR_RED);
				return;
			}

			IItem IItem((void*)DNPCItemCheck);
			int CheckItem = 0, CheckItemLeft = msConfig.ItemAmount - msedConfig.CurAmount;

			if (IItem.GetAmount() > CheckItemLeft)
				CheckItem = CheckItemLeft;
			else
				CheckItem = IItem.GetAmount();

			int NewAmount = msedConfig.CurAmount + CheckItem;

			if (NewAmount < 0)
				NewAmount = CheckItem;

			msedConfig.CurAmount = NewAmount;

			//SummonedQuest[(Quest.GetIndex() * 1000) + Quest.GetFlag()].CurAmount = NewAmount;

			SummonQuestRegistration.insert(((Quest.GetIndex() * 1000) + Quest.GetFlag()), NewAmount);

			std::string msg = Int2String(CheckItem) + " items have been collected from you. " + Int2String(NewAmount) + " items have been collected in total!";
			IPlayer.SystemMessage(msg, TEXTCOLOR_GREEN);
			CPlayer::RemoveItem(IPlayer.GetOffset(), 9, msConfig.ItemIndex, CheckItem);

			if (NewAmount == msConfig.ItemAmount)
			{
				msedConfig.Spawned = 0;

				for (int i = 0; i < msConfig.MonsterAmount; i++) {
					IChar Monster((void*)Summon((int)IPlayer.GetOffset(), msConfig.Map, msConfig.X, msConfig.Y, msConfig.MonsterIndex, 1, 1, 0, 7200 * 1000, 0));
					if (msConfig.Check) {
						Monster.UpdateBuff(BuffNames::SpawnedMobQuest, BuffNames::BuffTime, (Quest.GetIndex() * 1000) + Quest.GetFlag());
						msedConfig.Spawned++;
					}
				}

				msedConfig.CurAmount = 0;
				msedConfig.Limit++;

				//SummonedQuest[(Quest.GetIndex() * 1000) + Quest.GetFlag()].CurAmount = 0;
				//SummonedQuest[(Quest.GetIndex() * 1000) + Quest.GetFlag()].Limit++;

				SummonQuestRegistration.erase((Quest.GetIndex() * 1000) + Quest.GetFlag());

				if(!msConfig.notice.empty())
					CPlayer::WriteAll(0xFF, "ds", 234, msConfig.notice.c_str());
			}
			SummonedQuest.replaceInsert((Quest.GetIndex() * 1000) + Quest.GetFlag(), msedConfig);
		}

		return;
	}

	if (IPlayer.IsOnline() && Quest.GetIndex() == (DailyRewardQuest % 65536)) {
		int Day = IPlayer.GetBuffValue(BuffNames::RewardClaim);
		if (Day && DailyLogins.count(Day)) {
			std::string HWID = IPlayer.GetHWID();

			if (DailyLoginLimit) {
				int Hardware = sha256(HWID);
				if (DailyLoginLimits.count(Hardware)) {
					IPlayer.SystemMessage("You have already received a daily reward.", TEXTCOLOR_RED);
					return;
				}
				else
					DailyLoginLimits.insert(Hardware);
			}

			DailyReward dailyReward = DailyLogins.find(Day)->second;
			std::vector<std::string> Items_ = explode(",", dailyReward.Items);
			std::vector<std::string> iAmounts_ = explode(",", dailyReward.Amount);
			if (Items_.size() == iAmounts_.size()) {
				for (int i = 0; i < Items_.size(); i++) {
					int Index = String2Int(Items_[i]);
					int Amount = String2Int(iAmounts_[i]);
					if (Index && Amount) {
						int Prefix = (DailyLoginBound == 1) ? 256 : 0;
						if (GetInventorySize((int)IPlayer.GetOffset(), 0) < 60)
							CItem::InsertItem((int)IPlayer.GetOffset(), 27, Index, Prefix, Amount, -1);
						else
							IPlayer.GiveReward(Index, Prefix, Amount, 0, 0, 0, 0, 0, 0, 0, 0, "Here is your Daily Reward.");
					}
				}
			}
			int Honor = dailyReward.Honor;
			int Reward = dailyReward.Reward;
			int HTML = dailyReward.HTML;
			if (Honor || Reward)
				IPlayer.SetHonor(Honor, Reward, 0, 0, 0, 0, 0, 0, 0, 0);
			if (HTML)
				IPlayer.OpenHTML(HTML);
			IPlayer.CancelBuff(BuffNames::RewardClaim);

			CDBSocket::Write(100, "dddddddss", 2, IPlayer.GetUID(), (int)IPlayer.GetOffset(), String2Int(Time::GetMonth()), String2Int(Time::GetDay()), DailyLoginLimit, IPCheck, IPlayer.GetIP().c_str(), HWID.c_str());
		}
		return;
	}
	/*
	if (IPlayer.IsOnline() && ((PeaceEvil && Quest.GetIndex() == SlytherinQuest || Quest.GetIndex() == HuffleQuest || Quest.GetIndex() == RavenQuest || Quest.GetIndex() == GryffindorQuest) || (Quest.GetIndex() == 9010 && (Quest.GetFlag() == 1 || Quest.GetFlag() == 2))) && IPlayer.GetLevel() > 1) {
		IPlayer.SystemMessage("Starter NPC can only be used at level 1!.", TEXTCOLOR_RED);
		return;
	}
	*/
	//check this quest
	if (IPlayer.IsOnline() && Quest.GetIndex() == 9118) {

		if (GetInventorySize(PlayerOffset, 0) >= 60) {
			CPlayer::Write(IPlayer.GetOffset(), 67, "b", 40);
			return;
		}

		if (Quest.GetFlag() == 1)
			InsertJewels((void*)PlayerOffset, 10, 10);
		if (Quest.GetFlag() == 2)
			InsertJewels((void*)PlayerOffset, 100, 100);
		if (Quest.GetFlag() == 3)
			InsertJewels((void*)PlayerOffset, 300, 300);
		if (Quest.GetFlag() == 4)
			InsertJewels((void*)PlayerOffset, 495, 500);
		if (Quest.GetFlag() == 5)
			InsertJewels((void*)PlayerOffset, 980, 1000);
		if (Quest.GetFlag() == 6)
			InsertJewels((void*)PlayerOffset, 1950, 2000);

		return;
	}

	if (IPlayer.IsOnline() && BattlepassActive){
		BattlepassCheck((void*)PlayerOffset, QuestOffset);
		PBattlepassCheck((void*)PlayerOffset, QuestOffset);
	}

	if (IPlayer.IsOnline() && RebornsMaps.count((Quest.GetIndex() * 1000) + Quest.GetFlag()))
	{
		int CurrentReborn = IPlayer.GetProperty(PlayerProperty::Reborn);
		RbQuest rb = RebornsMaps.find((Quest.GetIndex() * 1000) + Quest.GetFlag())->second;

		if (CurrentReborn < rb.rbIndex)
		{
			IPlayer.SystemMessage("You must be atleast " + Int2String(rb.rbIndex) + " Reborn to use this quest.", TEXTCOLOR_RED);
			return;
		}
	}

	if (IPlayer.IsOnline() && RebornActive && Quest.GetIndex() == RebornQuest) {
		int NextReborn = IPlayer.GetProperty(PlayerProperty::Reborn) + 1;
		if (Reborns.count(NextReborn)) {
			Reborn rb = Reborns.find(NextReborn)->second;

			if (IPlayer.GetLevel() < rb.MinLvl) {
				IPlayer.SystemMessage("To reach your next reborn, you must be atleast level " + Int2String(rb.MinLvl) + ".", TEXTCOLOR_RED);
				return;
			}

			std::string XName(IPlayer.GetName());
			if (startsWith(XName, "<")) {
				int end = XName.find(">");
				if (end != std::string::npos) {
					XName.erase(0, end + 1);
				}
			}
			XName = "<" + rb.NameTag + ">" + XName;

			IPlayer.ChangeName(XName);
			//ShowMySkin((void*)PlayerOffset);
			IPlayer.SetLevel(rb.ResetLevel);

			if (rb.sbKey && rb.sbMsg) {
				int rbBuffID = (rb.sbKey + rb.sbMsg) * 15;
				IPlayer.SaveBuff(rbBuffID, BuffNames::BuffTime);
			}

			if (rb.NamePad) {
				IPlayer.UpdateBuff(BuffNames::NamePad, BuffNames::BuffTime, rb.NamePad);
				CChar::WriteInSight(IPlayer.GetOffset(), 0xFE, "ddd", 209, IPlayer.GetID(), rb.NamePad);
			}

			if (NextReborn >= RebornGZ) {
				std::string msg = "Congratulations to " + XName + " for reaching Reborn Level " + Int2String(NextReborn) + "!";
				CPlayer::WriteAll(0xFF, "dsd", 247, msg.c_str(), NOTICECOLOR_RED);
				std::string url = RebornWebhook;
				std::string avatar = Avatar;
				std::string playerName = std::string(IPlayer.GetName());
				SendWebhookMessage(url, msg.c_str(), avatar.c_str(), std::string(playerName));
			}

			IPlayer.SetProperty(PlayerProperty::Reborn, NextReborn);
			IPlayer.systemReward(rb.RewardID);
			CDBSocket::Write(119, "dd", IPlayer.GetPID(), NextReborn);
		}
		return;
	}

	if (IPlayer.IsOnline() && PeaceEvil && Quest.GetIndex() == SlytherinQuest) {
		int SQuest = (SlytherinQuest << 16) | 1;
		int GQuest = (GryffindorQuest << 16) | 1;
		int RQuest = (RavenQuest << 16) | 1;
		int HQuest = (HuffleQuest << 16) | 1;

		bool checkSlytherin = CPlayer::CheckQuestFlag(PlayerOffset, SQuest);
		bool checkGryffindor = CPlayer::CheckQuestFlag(PlayerOffset, GQuest);
		bool checkRaven = CPlayer::CheckQuestFlag(PlayerOffset, RQuest);
		bool checkHuffle = CPlayer::CheckQuestFlag(PlayerOffset, HQuest);

		if (!checkSlytherin && !checkGryffindor && !checkRaven && !checkHuffle) {
			IPlayer.Buff(BuffNames::Slytherin, BuffNames::BuffTime, 1); 
			IPlayer.ShowHonor();
			IPlayer.UpdateBuff(BuffNames::NamePad, BuffNames::BuffTime, SlytherinColor);
			CChar::WriteInSight((void*)PlayerOffset, 0xFE, "ddd", 209, IPlayer.GetID(), SlytherinColor);
			IPlayer.BoxMsg("You have chosen the Slyhterin's House.");
			IPlayer.AddFxToTarget("HellGate_FX32", 1, 0, 0);
			IPlayer.AddHousePlayers(1);

		}
		else
			IPlayer.BoxMsg("You have already chosen a House.");
	}

	if (IPlayer.IsOnline() && PeaceEvil && Quest.GetIndex() == RavenQuest) {
		int SQuest = (SlytherinQuest << 16) | 1;
		int GQuest = (GryffindorQuest << 16) | 1;
		int RQuest = (RavenQuest << 16) | 1;
		int HQuest = (HuffleQuest << 16) | 1;

		bool checkSlytherin = CPlayer::CheckQuestFlag(PlayerOffset, SQuest);
		bool checkGryffindor = CPlayer::CheckQuestFlag(PlayerOffset, GQuest);
		bool checkRaven = CPlayer::CheckQuestFlag(PlayerOffset, RQuest);
		bool checkHuffle = CPlayer::CheckQuestFlag(PlayerOffset, HQuest);

		if (!checkSlytherin && !checkGryffindor && !checkRaven && !checkHuffle) {
			IPlayer.Buff(BuffNames::Ravenclaw, BuffNames::BuffTime, 1);
			IPlayer.ShowHonor();
			IPlayer.UpdateBuff(BuffNames::NamePad, BuffNames::BuffTime, RavenColor);
			CChar::WriteInSight((void*)PlayerOffset, 0xFE, "ddd", 209, IPlayer.GetID(), RavenColor);
			IPlayer.BoxMsg("You have chosen the Ravenclaw's House.");
			IPlayer.AddFxToTarget("HellGate_FX32", 1, 0, 0);
			IPlayer.AddHousePlayers(1);


		}
		else
			IPlayer.BoxMsg("You have already chosen a House.");
	}
	if (IPlayer.IsOnline() && PeaceEvil && Quest.GetIndex() == HuffleQuest) {
		int SQuest = (SlytherinQuest << 16) | 1;
		int GQuest = (GryffindorQuest << 16) | 1;
		int RQuest = (RavenQuest << 16) | 1;
		int HQuest = (HuffleQuest << 16) | 1;

		bool checkSlytherin = CPlayer::CheckQuestFlag(PlayerOffset, SQuest);
		bool checkGryffindor = CPlayer::CheckQuestFlag(PlayerOffset, GQuest);
		bool checkRaven = CPlayer::CheckQuestFlag(PlayerOffset, RQuest);
		bool checkHuffle = CPlayer::CheckQuestFlag(PlayerOffset, HQuest);

		if (!checkSlytherin && !checkGryffindor && !checkRaven && !checkHuffle) {
			IPlayer.Buff(BuffNames::Hufflepuff, BuffNames::BuffTime, 1);
			IPlayer.ShowHonor();
			IPlayer.UpdateBuff(BuffNames::NamePad, BuffNames::BuffTime, HuffleColor);
			CChar::WriteInSight((void*)PlayerOffset, 0xFE, "ddd", 209, IPlayer.GetID(), HuffleColor);
			IPlayer.BoxMsg("You have chosen the Hufflepuff's House.");
			IPlayer.AddFxToTarget("HellGate_FX32", 1, 0, 0);
			IPlayer.AddHousePlayers(1);


		}
		else
			IPlayer.BoxMsg("You have already chosen a House.");
	}

	if (IPlayer.IsOnline() && Quest.GetIndex() == SVReplyQuest) {
		if (SufferingValley::Selection || SufferingValley::Active) {
			int Type = 4;
			if (SufferingValley::Active)
				Type = 7;
			CPlayer::Write((void*)PlayerOffset, 0xFE, "dbdbss", 168, 3, 4, 2, SufferingValley::FirstGuild.c_str(), SufferingValley::SecondGuild.c_str());
		}
		else
			CPlayer::Write((void*)PlayerOffset, 0xFE, "dbb", 168, 5, 1);
		return;
	}

	if (IPlayer.IsOnline() && PeaceEvil && Quest.GetIndex() == GryffindorQuest) {
		int SQuest = (SlytherinQuest << 16) | 1;
		int GQuest = (GryffindorQuest << 16) | 1;
		int RQuest = (RavenQuest << 16) | 1;
		int HQuest = (HuffleQuest << 16) | 1;

		bool checkSlytherin = CPlayer::CheckQuestFlag(PlayerOffset, SQuest);
		bool checkGryffindor = CPlayer::CheckQuestFlag(PlayerOffset, GQuest);
		bool checkRaven = CPlayer::CheckQuestFlag(PlayerOffset, RQuest);
		bool checkHuffle = CPlayer::CheckQuestFlag(PlayerOffset, HQuest);

		if (!checkSlytherin && !checkGryffindor && !checkRaven && !checkHuffle) {
			IPlayer.Buff(BuffNames::Gryffindor, BuffNames::BuffTime, 1);
			IPlayer.BoxMsg("You have chosen the Gryffindor's House.");
			IPlayer.AddFxToTarget("iland02", 1, 0, 0);
			IPlayer.AddHousePlayers(1);

		}
		else
			IPlayer.BoxMsg("You have already chosen a House.");
	}

	if (IPlayer.IsOnline() && Quest.GetIndex() == (VoteQuest % 65536)) {
		//userLock.Enter();
		UserInfo playerInfo = User.find(IPlayer.GetPID())->second;
		//userLock.Leave();
		if (VoteList.count(sha256(IPlayer.GetIP())) || VoteList.count(sha256(playerInfo.Hardware))) {
			if (VoteList.count(sha256(IPlayer.GetIP())) && VoteList.find(sha256(IPlayer.GetIP()))->second >= (int)time(0)) {
				int Time = VoteList.find(sha256(IPlayer.GetIP()))->second - (int)time(0);
				int Day = (Time / 86400);
				int Hour = ((Time / 3600) % 24);
				int Minute = ((Time / 60) % 60);
				int Second = (Time % 60);
				if (Time > 0) {
					IPlayer.SystemMessage("You have to wait " + Int2String(Day) + " Days, " + Int2String(Hour) + " Hours, " + Int2String(Minute) + " Minutes, " + Int2String(Second) + " Seconds to vote again", TEXTCOLOR_RED);
					return;
				}
			}
			if (VoteList.count(sha256(playerInfo.Hardware)) && VoteList.find(sha256(playerInfo.Hardware))->second >= (int)time(0)) {
				int Time = VoteList.find(sha256(playerInfo.Hardware))->second - (int)time(0);
				int Day = (Time / 86400);
				int Hour = ((Time / 3600) % 24);
				int Minute = ((Time / 60) % 60);
				int Second = (Time % 60);
				if (Time > 0) {
					IPlayer.SystemMessage("You have to wait " + Int2String(Day) + " Days, " + Int2String(Hour) + " Hours, " + Int2String(Minute) + " Minutes, " + Int2String(Second) + " Seconds to vote again", TEXTCOLOR_RED);
					return;
				}
			}
		}

		std::string VoteToken = random_string(30);
		IPlayer.OpenWebsite("http://topofmmos.com/site/" + Int2String(VoteID) + "/vote/" + VoteToken);
		Vote vote = Vote();
		vote.Token = VoteToken;
		vote.Time = (int)time(0) + 120;
		PlayerVote.replaceInsert(IPlayer.GetPID(), vote);
		return;
	}

	if (IPlayer.IsOnline() && DailyQuest.count(Quest.GetIndex()))
	{
		ConfigDailyQuest dQuest = DailyQuest.find(Quest.GetIndex())->second;
		if (dQuest.Level > IPlayer.GetLevel())
		{
			IPlayer.SystemMessage("Your level is not enough to accepted the quest!", TEXTCOLOR_RED);
			return;
		}

		if (IPlayer.GetBuffValue((BuffNames::DailyCountBegin + Quest.GetIndex()) % BuffNames::DailyCountEnd) == -1)
		{
			IPlayer.SystemMessage("You already accepted the quest!", TEXTCOLOR_RED);
			return;
		}

		if (dQuest.Party == 0 && IPlayer.IsParty())
		{
			IPlayer.SystemMessage("This quest must be done in solo mode!", TEXTCOLOR_RED);
			return;
		}

		if (dQuest.Party == 1 && !IPlayer.IsParty())
		{
			IPlayer.SystemMessage("This quest must be done in party mode!", TEXTCOLOR_RED);
			return;
		}

		int Repeat = IPlayer.GetBuffValue((BuffNames::DailyRepeatBegin + Quest.GetIndex()) % BuffNames::DailyRepeatEnd);
		if (Repeat < dQuest.Repeat) {
			IPlayer.UpdateBuff((BuffNames::DailyCountBegin + Quest.GetIndex()) % BuffNames::DailyCountEnd, BuffNames::BuffTime, -1);
			IPlayer.StartQuest(Quest.GetIndex(), 0, Repeat, 1);
		}
		else {
			if (IPlayer.GetBuffValue((BuffNames::DailyRepeatBegin + Quest.GetIndex()) % BuffNames::DailyRepeatEnd) >= dQuest.Repeat)
			{
				int Time = (int)time(0) - IPlayer.GetBuffValue((BuffNames::DailyQuestBegin + Quest.GetIndex()) % BuffNames::DailyQuestEnd);

				if (Time < 0)
				{
					int Day = (Time / 86400) * -1;
					int Hour = ((Time / 3600) % 24) * -1;
					int Minute = ((Time / 60) % 60) * -1;
					int Second = (Time % 60) * -1;
					std::string msg = "Exceeded the maximum repeat limit of quest. You need to wait " + Int2String(Day) + " Days " + Int2String(Hour) + " Hours " + Int2String(Minute) + " Minutes " + Int2String(Second) + " Seconds.";
					IPlayer.SystemMessage(msg, TEXTCOLOR_RED); 
					if (dQuest.Resetable == 1)
						IPlayer.SystemMessage("This quest also resets at 00:00 server time.", TEXTCOLOR_YELLOW);
				}
				else {
					IPlayer.DailyQuestUpdate(Quest.GetIndex(), -1, 0);
					IPlayer.UpdateBuff((BuffNames::DailyCountBegin + Quest.GetIndex()) % BuffNames::DailyCountEnd, BuffNames::BuffTime, -1);
					IPlayer.UpdateBuff((BuffNames::DailyRepeatBegin + Quest.GetIndex()) % BuffNames::DailyRepeatEnd, BuffNames::BuffTime, 0);
					int Time = (int)time(0) + dQuest.Time;
					IPlayer.UpdateBuff((BuffNames::DailyQuestBegin + Quest.GetIndex()) % BuffNames::DailyQuestEnd, BuffNames::BuffTime, Time);
					IPlayer.StartQuest(Quest.GetIndex(), Time, 0, 1);

				}
			}
		}

		return;
	}

	if (IPlayer.IsOnline() && Polls.count(Quest.GetIndex())) {
		Poll poll = Polls.find(Quest.GetIndex())->second;

		int Index = (String2Int(Time::GetMonth()) * 1000000) + (String2Int(Time::GetDay()) * 10000) + (String2Int(Time::GetHour()) * 100) + (String2Int(Time::GetMinute()));

		if (Index < poll.Start) {
			IPlayer.SystemMessage("This poll will start in " + Int2String(poll.Start - Index) + " minutes." , TEXTCOLOR_RED);
			return;
		}

		if (Quest.GetFlag() == (poll.FlagMin - 1)) {
			IPlayer.OpenHTML(poll.HTML);
			IPlayer.BoxMsg(poll.Question);
			return;
		}

		std::string HWID = sha256Str(IPlayer.GetHWID());

		if (Quest.GetFlag() == (poll.FlagMax + 1)) {
			if (PollVotes.count(HWID)) {
				if (PollVotes.findValue(HWID).count(Quest.GetIndex())) {
					int TotalVotes = 0;
					for (int i = poll.FlagMin; i <= poll.FlagMax; i++) {
						int Value = PollVoteAmount.count((Quest.GetIndex() * 1000) + i) ? PollVoteAmount.findValue((Quest.GetIndex() * 1000) + i) : 0;
						std::string pollVote = " Option " + Int2String(i) + ": " + Int2String(Value) + " votes.";
						CPlayer::Write(IPlayer.GetOffset(), 0xFE, "ds", 213, pollVote.c_str());
						TotalVotes += Value;
					}
					std::string totVote = " Total Votes: " + Int2String(TotalVotes) + +".";
					CPlayer::Write(IPlayer.GetOffset(), 0xFE, "ds", 213, totVote.c_str());
				}
				else
					IPlayer.SystemMessage("You can only see the results once you have voted.", TEXTCOLOR_RED);
			}else
				IPlayer.SystemMessage("You can only see the results once you have voted.", TEXTCOLOR_RED);
			return;
		}

		if (Index >= poll.End) {
			IPlayer.SystemMessage("This poll has ended.", TEXTCOLOR_RED);
			return;
		}

		std::set<int> votes = std::set<int>();

		if (PollVotes.count(HWID)) {
			votes = PollVotes.findValue(HWID);
			if (votes.count(Quest.GetIndex())) {
				IPlayer.SystemMessage("Your vote has already been saved for this poll.", TEXTCOLOR_RED);
				return;
			}
		}
		
		int CurVotes = PollVoteAmount.count((Quest.GetIndex() * 1000) + Quest.GetFlag()) ? PollVoteAmount.findValue((Quest.GetIndex() * 1000) + Quest.GetFlag()) : 0;
		PollVoteAmount.replaceInsert((Quest.GetIndex() * 1000) + Quest.GetFlag(), CurVotes + 1);
		votes.insert(Quest.GetIndex());
		PollVotes.replaceInsert(HWID, votes);

		IPlayer.SystemMessage("Thank you for voting, you can now see the results.", TEXTCOLOR_GREEN);

		std::string Datko = "./Database/Polls.db";
		std::fstream DGkLOG;
		DGkLOG.open(Datko, std::fstream::in | std::fstream::out | std::fstream::app);
		DGkLOG << "(PollVote (Index " << Int2String(Quest.GetIndex()) << ") (Vote " << Int2String(Quest.GetFlag()) << ") (Hash '" << HWID << "'))" << std::endl;
		DGkLOG.close();

		int TotalVotes = 0;
		for (int i = poll.FlagMin; i <= poll.FlagMax; i++) {
			int Value = PollVoteAmount.count((Quest.GetIndex() * 1000) + i) ? PollVoteAmount.findValue((Quest.GetIndex() * 1000) + i) : 0;
			std::string pollVote = " Option " + Int2String(i) + ": " + Int2String(Value) + " votes.";
			CPlayer::Write(IPlayer.GetOffset(), 0xFE, "ds", 213, pollVote.c_str());
			TotalVotes += Value;
		}
		std::string totVote = " Total Votes: " + Int2String(TotalVotes) + +".";
		CPlayer::Write(IPlayer.GetOffset(), 0xFE, "ds", 213, totVote.c_str());

		return;
	}

	if (IPlayer.IsOnline() && Quest.GetIndex() == (RaidDonateQuest % 65536) && Quest.GetFlag() == RaidDonateQFlag) {
		int GID = IPlayer.GetGID();
		if (!GID) {
			IPlayer.SystemMessage("[Guild Raid System] You must be in a guild to use this system.", TEXTCOLOR_RED);
			return;
		}

		int CurAmount = GuildRaidItems.count(GID) ? GuildRaidItems.findValue(GID) : 0;

		int Item = CPlayer::FindItem((void*)PlayerOffset, RaidGuildIndex, 1);
		if (!Item) {
			IPlayer.SystemMessage("[Guild Raid System] You have no guild raid items.", TEXTCOLOR_RED);
			return;
		}

		IItem IItem((void*)Item);
		int Amount = IItem.GetAmount();
		int NewAmount = Amount + CurAmount;

		int CurLvl = 0;

		for (auto x = GuildRaidLevels.begin(); x != GuildRaidLevels.end(); x++) {
			if (CurLvl < x->first && NewAmount >= x->second.ReqAmount)
				CurLvl = x->first;
		}

		CIOCriticalSection::Enter((struct _RTL_CRITICAL_SECTION*)((int)IPlayer.GetOffset() + 1020));
		if (!(*(int(__thiscall **)(DWORD, void *, signed int, signed int))(*(DWORD*)Item + 120))(Item, IPlayer.GetOffset(), *(DWORD *)(*(DWORD *)((int)Item + 40) + 156) != 0 ? 43 : 9, -Amount))
			CPlayer::_OutOfInven(IPlayer.GetOffset(), Item);
		CIOCriticalSection::Leave((void*)((char*)IPlayer.GetOffset() + 1020));

		IPlayer.WriteToGuild("$" + (std::string)IPlayer.GetName() + " has donated " + Int2String(Amount) + " raid items. Raid Level: " + Int2String(CurLvl) + ". New Total: " + Int2String(NewAmount) + " donated items.");
		
		GuildRaidItems.insert(GID, CurAmount + Amount);

		IPlayer.SystemMessage("[Guild Raid System] Your donation has been made.", TEXTCOLOR_GREEN);
		return;
	}

	if (IPlayer.IsOnline() && Quest.GetIndex() == (RaidReplyQuest % 65536) && Quest.GetFlag() == RaidReplyQFlag) {
		int GID = IPlayer.GetGID();
		if (!GID) {
			IPlayer.SystemMessage("[Guild Raid System] You must be in a guild to use this system.", TEXTCOLOR_RED);
			return;
		}

		int CurAmount = GuildRaidItems.count(GID) ? GuildRaidItems.findValue(GID) : 0;

		int CurLvl = 0;
		for (auto x = GuildRaidLevels.begin(); x != GuildRaidLevels.end(); x++) {
			if (CurLvl < x->first && CurAmount >= x->second.ReqAmount)
				CurLvl = x->first;
		}

		IPlayer.SystemMessage("[Guild Raid System] Raid Level: " + Int2String(CurLvl) + ". " + Int2String(CurAmount) + " donated items.", TEXTCOLOR_GREEN);
		return;
	}

	if (IPlayer.IsOnline() && Quest.GetIndex() == (RaidStartQuest % 65536) && Quest.GetFlag() == RaidStartQFlag) {
		int GID = IPlayer.GetGID();
		if (!GID) {
			IPlayer.SystemMessage("[Guild Raid System] You must be in a guild to use this system.", TEXTCOLOR_RED);
			return;
		}

		if (IPlayer.GetPID() != GID) {
			IPlayer.SystemMessage("[Guild Raid System] Only guild leader must can start raid guild system.", TEXTCOLOR_RED);
			return;
		}

		if (GuildRaid::Active) {
			IPlayer.SystemMessage("Guild Raid System is already running at the moment. Please try again later.", TEXTCOLOR_RED);
			return;
		}

		int CurAmount = GuildRaidItems.count(GID) ? GuildRaidItems.findValue(GID) : 0;

		int CurLvl = 0;
		for (auto x = GuildRaidLevels.begin(); x != GuildRaidLevels.end(); x++) {
			if (CurLvl < x->first && CurAmount >= x->second.ReqAmount)
				CurLvl = x->first;
		}

		if (GuildRaidLevels.count(CurLvl)) {
			GuildRaidLevel raid = GuildRaidLevels.find(CurLvl)->second;

			if (IPlayer.GuildOnlinePlayers() < raid.MinPlayers) {
				IPlayer.SystemMessage("[Guild Raid System] There must be at least " + Int2String(raid.MinPlayers) + " guild players online for this raid.", TEXTCOLOR_RED);
				return;
			}

			IPlayer.WriteToGuild("$Raid Level " + Int2String(CurLvl) + " has started.");

			if (CurAmount > raid.ReqAmount)
				GuildRaidItems.insert(GID, CurAmount - raid.ReqAmount);
			else
				GuildRaidItems.erase(GID);

			int Guild = CPlayer::GetGuild((int)IPlayer.GetOffset());
			if (Guild)
			{
				void* v22 = (void *)CObject::WriteExclusive(0xFF, "dd", 233, raid.Time);
				CGuild::BroadcastLock((void*)Guild, v22, 0);
				CIOBuffer::Release(v22);
				CSkill::ObjectRelease((void*)Guild, (LONG)(Guild + 40));
			}

			GuildRaid::GID = GID;
			GuildRaid::Time = (int)time(0) + raid.Time;
			GuildRaid::Reward = raid.Reward;
			GuildRaid::Boss = (void*)Summon(0, 0, 239389, 348335, raid.MobIndex, 1, 0, 0, raid.Time * 1000, 0);
			GuildRaid::Active = true;

			IPlayer.SystemMessage("[Guild Raid System] Raid has started.", TEXTCOLOR_GREEN);
		}
		else
			IPlayer.SystemMessage("[Guild Raid System] Your Guild Raid Level is too low to start. Minimum items needed for level 1 raid: " + Int2String(RaidMinimumAmount) + " donated items.", TEXTCOLOR_YELLOW);
		return;
	}

	if (IPlayer.IsOnline() && GuildBuffQuests.count(Quest.GetIndex())) {
		int GID = IPlayer.GetGID();
		if (!GID) {
			IPlayer.SystemMessage("You must be in a guild to use this system.", TEXTCOLOR_RED);
			return;
		}

		GuildBuffQuest quest = GuildBuffQuests.find(Quest.GetIndex())->second;

		long Index = uniqueKey(Quest.GetIndex(), GID); 
		
		int CurItems = GuildBuffItems.count(Index) ? GuildBuffItems.findValue(Index) : 0;

		int LeftAmount = quest.Amount - CurItems;

		if (Quest.GetFlag() == quest.Flag) {

			if (ActiveGuildBuffs.count(Index)) {
				IPlayer.SystemMessage(quest.Name + " is already active for your guild.", TEXTCOLOR_RED);
				return;
			}

			int Item = CPlayer::FindItem((void*)PlayerOffset, quest.Index, 1);
			if (!Item) {
				IPlayer.SystemMessage("You have no guild buff items.", TEXTCOLOR_RED);
				return;
			}
			IItem IItem((void*)Item);
			int Amount = IItem.GetAmount();

			if (Amount > LeftAmount)
				Amount = LeftAmount;

			IPlayer.RemoveItem(quest.Index, Amount);
			CDBSocket::Write(113, "ddd", IPlayer.GetPID(), GID, Amount);
			IPlayer.WriteToGuild("$" + (std::string)IPlayer.GetName() + " has added " + Int2String(Amount) + " coins for " + quest.Name + ".");

			int newAmount = CurItems + Amount;
			if (newAmount < quest.Amount)
				GuildBuffItems.insert(Index, newAmount);
			else {
				GuildBuffItems.insert(Index, 0);
				IPlayer.WriteToGuild("$" + quest.Name + " has started.");
				for (int i = 0; i < quest.Buffs.size(); i++)
					quest.Buffs[i].Time = (quest.Buffs[i].Time * 1000) + GetTickCount();

				ActiveGuildBuffs.replaceInsert(Index, quest.Buffs);
			}
		}
		else if (Quest.GetFlag() == quest.ReplyFlag) {
			IPlayer.SystemMessage("["+ quest.Name + "] "+Int2String(LeftAmount) +" items left to start.", TEXTCOLOR_YELLOW);
			return;
		}
		return;
	}

	if (IPlayer.IsOnline() && PTEnabled.count((Quest.GetIndex() * 1000) + Quest.GetFlag())) {
		PartyReg Reg = PTEnabled.find((Quest.GetIndex() * 1000) + Quest.GetFlag())->second;

		if (Reg.Type == 3) {
			IPlayer.SystemMessage("Registration for this tournament is not activated.", TEXTCOLOR_RED);
			return;
		}

		for (int i = 0; i < PartyRegistrations.size(); i++) {
			if (PartyRegistrations[i].PID == IPlayer.GetPartyID()) {
				IPlayer.SystemMessage("Your party is already registered for Party vs Party.", TEXTCOLOR_RED);
				return;
			}
		}

		int Party = CParty::FindParty(IPlayer.GetPartyID());

		if (!Party) {
			IPlayer.SystemMessage("You must be in a party to register for Party Vs Party.", TEXTCOLOR_RED);
			return;
		}

		if (!CParty::IsHead(Party, (int)IPlayer.Offset))
		{
			IPlayer.SystemMessage("Only party leader can register for Party Vs Party.", TEXTCOLOR_RED);
			CIOObject::Release((void*)Party);
			return;
		}

		if (CParty::GetSize((void*)Party) != Reg.PartySize) {
			IPlayer.SystemMessage("Your party size must be " + Int2String(Reg.PartySize), TEXTCOLOR_RED);
			CIOObject::Release((void*)Party);
			return;
		}
		bool notAllowed = false;
		int j = 0;
		for (int i = CParty::GetPlayerList((void*)Party); i; i = CBaseList::Pop((void *)i))
		{
			int Members = *(DWORD*)((void*)i);
			IChar Member((void*)*(DWORD*)((void*)i));

			if (CChar::IsNormal(Members) && IPlayer.IsValid())
			{
				if (Member.GetLevel() < Reg.MinLevel)
					notAllowed = true;

				if (Member.GetLevel() > Reg.MaxLevel)
					notAllowed = true;
				
				std::string Name = " " + (std::string)Member.GetName();
				if(j<6)
					strcpy(Reg.Names[j], Name.c_str());
				
				j++;
			}
			else
				notAllowed = true;
		}

		if (notAllowed) {
			IPlayer.SystemMessage("Some of your party members do not meet the requirements.", TEXTCOLOR_RED);
			CIOObject::Release((void*)Party);
			return;
		}
		Reg.nWin = 0;
		Reg.PID = IPlayer.GetPartyID();
		PartyRegistrations.push_back(Reg);
		PTRegisterSize++;
		IPlayer.SystemMessage("Your party has been registered to the battle", TEXTCOLOR_GREEN);
		CIOObject::Release((void*)Party);
		return;
	}

	if (IPlayer.IsOnline() && IPlayer.IsBuff(349))
	{
		IPlayer.SystemMessage("You can not use quest while riding.", TEXTCOLOR_RED);
		return;
	}
	if (IPlayer.IsOnline() && !QBattleEnable.count((Quest.GetIndex() * 1000) + Quest.GetFlag()) && (IPlayer.IsBuff(160) || IPlayer.IsBuff(180) || IPlayer.IsBuff(179) || IPlayer.IsBuff(161) || IPlayer.IsBuff(162) || IPlayer.IsBuff(163) || IPlayer.IsBuff(170) || IPlayer.IsBuff(171) || IPlayer.IsBuff(373) || IPlayer.IsBuff(374) || IPlayer.IsBuff(902) || IPlayer.IsBuff(903) || IPlayer.IsBuff(BuffNames::LMS) || IPlayer.IsBuff(BuffNames::PTVsPTBlue) || IPlayer.IsBuff(BuffNames::PTVsPTRed) || IPlayer.GetBuffValue(BuffNames::TriangularType) || IPlayer.GetMap() == SVMap) && Quest.GetIndex() != ScenarioQuestR && Quest.GetIndex() != ScenarioQuestB && Quest.GetIndex() != CPQuestB && Quest.GetIndex() != CPQuestR)
	{
		IPlayer.SystemMessage("You can not do this in battle.", TEXTCOLOR_RED);
		return;
	}

	if (IPlayer.IsOnline() && IPlayer.IsBuff(3089)) {
		IPlayer.SystemMessage("You can not do this while youre in the middle of a bet", TEXTCOLOR_RED);
		return;
	}

	if (IPlayer.IsOnline() && IPlayer.IsBuff(BuffNames::Jail)) {
		IPlayer.SystemMessage("You're restricted in jail.", TEXTCOLOR_RED);
		return;
	}

	if (IPlayer.IsOnline() && RentQuests.count((Quest.GetIndex() * 1000) + Quest.GetFlag()))
	{
		Items t = RentQuests.find((Quest.GetIndex() * 1000) + Quest.GetFlag())->second;

		int Item = CItem::CreateItem(t.Index, t.Prefix, t.Amount, -1);

		if (Item) {
			IItem xItemAdd((void*)Item);

			int Info = t.Info;

			if (t.Dss)
				*(DWORD*)(Item + 84) = t.Dss;

			*(DWORD*)(Item + 48) = Info;

			if (xItemAdd.HighMemory()) {
				if (t.Attack)
					*(DWORD *)(Item + 100) = t.Attack;
				if (t.Magic)
					*(DWORD *)(Item + 104) = t.Magic;

				if (!xItemAdd.IsTransform()) {
					if (t.Def)
						*(DWORD *)(Item + 108) = t.Def;
					if (t.Eva)
						*(DWORD *)(Item + 116) = t.Eva;
					if (xItemAdd.IsWeapon()) {
						if (t.Toa)
							*(DWORD *)(Item + 112) = t.Toa;
						if (t.Upgrade)
							*(DWORD *)(Item + 124) = t.Upgrade;
					}
				}
			}

			bool TimedCheck = false;
			if (TimedItems.count(t.Index)) {
				TimedCheck = true;
				IPlayer.UpdateBuff(BuffNames::TimedCheck, BuffNames::BuffTime, t.Index);
			}

			if (CPlayer::InsertItem(IPlayer.GetOffset(), 27, Item) == 1)
			{
				int IID = *(DWORD *)(Item + 36);

				if (t.Dss)
					CDBSocket::Write(87, "ddd", IPlayer.GetPID(), t.Dss, IID);
				if (t.Info)
					CDBSocket::Write(21, "dddbb", IID, IPlayer.GetPID(), t.Info, 8, 7);
				if (t.Def)
					CDBSocket::Write(17, "ddbbb", IID, IPlayer.GetPID(), 15, t.Def, 0);
				if (t.Eva)
					CDBSocket::Write(17, "ddbbb", IID, IPlayer.GetPID(), 10, t.Eva, 0);
				if (t.Attack)
					CDBSocket::Write(17, "ddbbb", IID, IPlayer.GetPID(), 27, t.Attack, 0);
				if (t.Magic)
					CDBSocket::Write(17, "ddbbb", IID, IPlayer.GetPID(), 28, t.Magic, 0);
				if (t.Toa)
					CDBSocket::Write(17, "ddbbb", IID, IPlayer.GetPID(), 9, t.Toa, 0);
				if (t.Upgrade)
					CDBSocket::Write(28, "ddbb", IID, IPlayer.GetPID(), 2, t.Upgrade);

				if (t.Time) {
					CDBSocket::Write(89, "ddd", IPlayer.GetPID(), (int)time(0) + t.Time, IID);
					PetLifeCheck.replaceInsert(IID, t.Time + (int)time(0));

					*(DWORD*)(Item + 68) = GetTickCount() + (2000 * abs(t.Time));
					*(DWORD*)(Item + 72) = 0;

					CItem::OnTimer(Item, 0);
					CPlayer::Write(IPlayer.GetOffset(), 0xFF, "ddd", 230, IID, t.Time);
				}

				if (t.ItemStat) {
					itemStat.Enter();
					GetItemStat[IID] = t.ItemStat;
					itemStat.Leave();
					CDBSocket::Write(90, "dd", t.ItemStat, IID);
					CItem::SendItemInfo((void*)Item, (int)IPlayer.GetOffset(), 92);
				}
			}
			else
				CBase::Delete((void*)Item);

			if (TimedCheck)
				IPlayer.UpdateBuff(BuffNames::TimedCheck, BuffNames::BuffTime, 0);
		}
		return;
	}

	if (IPlayer.IsOnline() && RentArmor.count(Quest.GetIndex()))
	{
		if (GetInventorySize(PlayerOffset, 0) < 60) {
			int DonationCoinCheck = 0;

			if (RentArmor.find(Quest.GetIndex())->second.Coin != 0) {
				DonationCoinCheck = CPlayer::FindItem(IPlayer.GetOffset(), DonationCoin, RentArmor.find(Quest.GetIndex())->second.Coin);

				if (!(DonationCoinCheck && CPlayer::RemoveItem(IPlayer.GetOffset(), 9, DonationCoin, RentArmor.find(Quest.GetIndex())->second.Coin))) {
					IPlayer.SystemMessage("Not enough coins!", TEXTCOLOR_RED);
					return;
				}
			}
			if (RentArmor.find(Quest.GetIndex())->second.Index)
			{
				int Armor = CItem::CreateItem(RentArmor.find(Quest.GetIndex())->second.Index, RentArmor.find(Quest.GetIndex())->second.Prefix, 1, -1);

				if (Armor)
				{
					IItem IItem((void*)Armor);
					int Info = 4194432;

					if (RentArmor.find(Quest.GetIndex())->second.Dss)
						*(DWORD*)(Armor + 84) = RentArmor.find(Quest.GetIndex())->second.Dss;

					if (RentArmor.find(Quest.GetIndex())->second.Bof)
						Info += 2097152;

					*(DWORD*)(Armor + 48) = Info;

					if (IItem.HighMemory() && RentArmor.find(Quest.GetIndex())->second.Def)
						*(DWORD*)(Armor + 108) = RentArmor.find(Quest.GetIndex())->second.Def;
					if (IItem.HighMemory() && RentArmor.find(Quest.GetIndex())->second.Eva)
						*(DWORD*)(Armor + 116) = RentArmor.find(Quest.GetIndex())->second.Eva;

					int ValidItem = CPlayer::InsertItem(IPlayer.GetOffset(), 7, Armor);

					if (ValidItem == 1)
					{
						if(IItem.HighMemory())
							CDBSocket::Write(17, "ddbbb", *(DWORD *)(Armor + 36), *(DWORD *)(Armor + 32), 15, *(DWORD *)(Armor + 108), 0);
						if(IItem.HighMemory())
							CDBSocket::Write(17, "ddbbb", *(DWORD *)(Armor + 36), *(DWORD *)(Armor + 32), 10, *(DWORD *)(Armor + 116), 0);

						//petLifeLock.Enter();
						PetLifeCheck.replaceInsert(*(DWORD *)(Armor + 36), (int)time(0) + RentArmor.find(Quest.GetIndex())->second.Time);
						//petLifeLock.Leave();

						CDBSocket::Write(89, "ddd", IPlayer.GetPID(), PetLifeCheck.findValue(*(DWORD *)(Armor + 36)), *(DWORD *)(Armor + 36));

						CPlayer::Write(IPlayer.GetOffset(), 0xFF, "ddd", 230, *(DWORD *)(Armor + 36), RentArmor.find(Quest.GetIndex())->second.Time);
						*(DWORD*)(Armor + 68) = GetTickCount() + (2000 * RentArmor.find(Quest.GetIndex())->second.Time);
						*(DWORD*)(Armor + 72) = 0;
						ItemOnTimer(Armor, 0, 0);
					}
					else
						CBase::Delete((void*)ValidItem);
				}
			}
			else
				IPlayer.SystemMessage("Not enough coins!", TEXTCOLOR_RED);
		}
		else
			CPlayer::Write(IPlayer.GetOffset(), 67, "b", 40);
		return;
	}

	if (LottoAct == 1 && IPlayer.IsOnline() && Quest.GetIndex() == (LottoQuest % 65536)) {
		if (CPlayer::FindItem(IPlayer.GetOffset(), LottoIndex, LottoAmount)) {
			if (!XLottery.count(IPlayer.GetPID())) {
				XLottery.insert(IPlayer.GetPID());
				if (CPlayer::RemoveItem(IPlayer.GetOffset(), 9, LottoIndex, LottoAmount)) {
					IPlayer.SystemMessage("Thank you for your Lotto Contribution!", TEXTCOLOR_GREEN);
					IPlayer.SystemMessage("Stay tuned for the announcement of the next winner!", TEXTCOLOR_GREEN);
				}
			}
			else {
				IPlayer.SystemMessage("You are already participating in Lotto's lottery!", TEXTCOLOR_RED);
			}
		}
		else {
			IPlayer.SystemMessage("You do not have enough items to participate in the lottery!", TEXTCOLOR_RED);
		}
		return;
	}

	if (IPlayer.IsOnline() && LotAct == 1 && Quest.GetIndex() == (LotQuest % 65536)) {

		if (CPlayer::FindItem(IPlayer.GetOffset(), LotIndex, LotAmount)) {
			if (!Lottery.count(IPlayer.GetPID())) {
				Lottery.insert(IPlayer.GetPID());
				LotteryCheck += LotAmount;
				if (CPlayer::RemoveItem(IPlayer.GetOffset(), 9, LotIndex, LotAmount)) {
					IPlayer.SystemMessage("Thank you for your contribution.", TEXTCOLOR_GREEN);
					IPlayer.SystemMessage("Stay tuned for the announcement of the next winner!", TEXTCOLOR_GREEN);
					if (String2Int(Time::GetHour()) >= 12) {
						IPlayer.BoxMsg("***********Lottery Receipt*************\n\nNext Lottery Selection Time: 00:00\n\nMake sure you're online during the selection time\nOffline characters will not be a part of the selection!");
					}
					else {
						IPlayer.BoxMsg("***********Lottery Receipt*************\n\nNext Lottery Selection Time: 12:00\n\nMake sure you're online during the selection time\nOffline characters will not be a part of the selection!");
					}
				}
			}
			else {
				IPlayer.SystemMessage("You are already participating in today's lottery!", TEXTCOLOR_RED);
			}
		}
		else {
			IPlayer.SystemMessage("You do not have enough geons to participate in the lottery!", TEXTCOLOR_RED);
		}
		return;
	}
	if (IPlayer.IsOnline() && Quest.GetIndex() == (LotRQuest % 65536)) {
		IPlayer.SystemMessage("Current Lottery Amount: " + Int2String(LotteryCheck) + " Geons", TEXTCOLOR_PINK);
		return;
	}

	if (IPlayer.IsOnline() && Quest.GetIndex() == (COKQuest % 65536)) {
		if (!WorldCup::Active) {
			if (IPlayer.GetLevel() >= COKLimit) {
				if (!CupRegistration.count(IPlayer.GetPID())) {
					Team playerTeam = Team();
					playerTeam.PID = IPlayer.GetPID();
					playerTeam.Name = (std::string)IPlayer.GetName();
					playerTeam.Points = 0;
					if (!CupOfKal.count(CurGroup) || CupOfKal.find(CurGroup)->second.Groups.size() < 4) {
						CupRegistration[IPlayer.GetPID()].group = CurGroup;
						CupRegistration[IPlayer.GetPID()].team = playerTeam;

						CupOfKal[CurGroup].Groups.push_back(playerTeam);

						IPlayer.SystemMessage("Successfully registered to Cup Of Kal Tournament!", TEXTCOLOR_GREEN);
						IPlayer.SystemMessage("You have been registered in Group " + Int2String(CurGroup), TEXTCOLOR_YELLOW);
						IPlayer.SystemMessage("Type /cokgroups to find out more about your group and your opponents!", TEXTCOLOR_GREEN);
						IPlayer.SystemMessage("Type /cokgroup " + Int2String(CurGroup) + " to find out about the ranking of your group!", TEXTCOLOR_GREEN);

						if (CurGroup == 8)
							CurGroup = 0;

						CurGroup++;
						if (CupRegistration.size() == 32)
							StartWorldCup();

					}
					else {
						IPlayer.SystemMessage("World Cup groups are all full!", TEXTCOLOR_RED);
						return;
					}
				}
				else
					IPlayer.SystemMessage("You are already registered to the World Cup!", TEXTCOLOR_RED);
			}
			else
				IPlayer.SystemMessage("You must be atleast level " + Int2String(COKLimit) + " To register!", TEXTCOLOR_RED);
		}
		else
			IPlayer.SystemMessage("World Cup has started already!", TEXTCOLOR_RED);
		return;
	}

	if (IPlayer.IsOnline() && Quest.GetIndex() == (ReplyLottoQuest % 65536)) {
		IPlayer.SystemMessage("Number of Players registered for Lotto: " + Int2String(XLottery.size()), TEXTCOLOR_PINK);
		return;
	}

	if (IPlayer.IsOnline() && Quest.GetIndex() == (HRQuest % 65536)) {
		IPlayer.SystemMessage("Current Guild Hunting: " + HuntingName, TEXTCOLOR_PINK);
		return;
	}

	if (IPlayer.IsOnline() && Quest.GetIndex() == (ReplyWC % 65536)) {
		IPlayer.SystemMessage("Players left for World Cup to start: " + Int2String(32 - CupRegistration.size()), TEXTCOLOR_YELLOW);
		return;
	}

	if (IPlayer.IsOnline() && Quest.GetIndex() == (WCWinQuest % 65536)) {
		IPlayer.SystemMessage("Current World Cup Winner: " + WCWinner, TEXTCOLOR_INFOMSG);
		return;
	}

	if (IPlayer.IsOnline() && RentWeapon.count(Quest.GetIndex()))
	{
		if (GetInventorySize(PlayerOffset, 0) < 60) {
			int DonationCoinCheck = 0;

			if (RentWeapon.find(Quest.GetIndex())->second.Coin) {
				DonationCoinCheck = CPlayer::FindItem(IPlayer.GetOffset(), DonationCoin, RentWeapon.find(Quest.GetIndex())->second.Coin);

				if (!(DonationCoinCheck && CPlayer::RemoveItem(IPlayer.GetOffset(), 9, DonationCoin, RentWeapon.find(Quest.GetIndex())->second.Coin))) {
					IPlayer.SystemMessage("Not enough coins!", TEXTCOLOR_RED);
					return;
				}
			}

			if (RentWeapon.find(Quest.GetIndex())->second.Index)
			{
				int Weapon = CItem::CreateItem(RentWeapon.find(Quest.GetIndex())->second.Index, RentWeapon.find(Quest.GetIndex())->second.Prefix, 1, -1);

				if (Weapon)
				{
					int Info = 4194432;

					if (RentWeapon.find(Quest.GetIndex())->second.Dss)
						*(DWORD*)(Weapon + 84) = RentWeapon.find(Quest.GetIndex())->second.Dss;

					if (RentWeapon.find(Quest.GetIndex())->second.Mix)
						Info += RentWeapon.find(Quest.GetIndex())->second.Mix;

					*(DWORD*)(Weapon + 48) = Info;
					*(DWORD*)(Weapon + 100) = RentWeapon.find(Quest.GetIndex())->second.Attack;
					*(DWORD*)(Weapon + 104) = RentWeapon.find(Quest.GetIndex())->second.Magic;
					*(DWORD*)(Weapon + 112) = RentWeapon.find(Quest.GetIndex())->second.Toa;
					*(DWORD*)(Weapon + 124) = RentWeapon.find(Quest.GetIndex())->second.Upgrade;
					int ValidItem = CPlayer::InsertItem(IPlayer.GetOffset(), 7, Weapon);

					if (ValidItem == 1)
					{
						CDBSocket::Write(17, "ddbbb", *(DWORD *)(Weapon + 36), *(DWORD *)(Weapon + 32), 27, *(DWORD*)(Weapon + 100), 0);
						CDBSocket::Write(17, "ddbbb", *(DWORD *)(Weapon + 36), *(DWORD *)(Weapon + 32), 28, *(DWORD*)(Weapon + 104), 0);
						CDBSocket::Write(17, "ddbbb", *(DWORD *)(Weapon + 36), *(DWORD *)(Weapon + 32), 9, *(DWORD*)(Weapon + 112), 0);
						CDBSocket::Write(28, "ddbb", *(DWORD *)(Weapon + 36), *(DWORD *)(Weapon + 32), 2, *(DWORD*)(Weapon + 124));
						//petLifeLock.Enter();
						PetLifeCheck.replaceInsert(*(DWORD *)(Weapon + 36), (int)time(0) + RentWeapon.find(Quest.GetIndex())->second.Time);
						//petLifeLock.Leave();
						CDBSocket::Write(89, "ddd", IPlayer.GetPID(), PetLifeCheck.findValue(*(DWORD *)(Weapon + 36)), *(DWORD *)(Weapon + 36));

						CPlayer::Write(IPlayer.GetOffset(), 0xFF, "ddd", 230, *(DWORD *)(Weapon + 36), RentWeapon.find(Quest.GetIndex())->second.Time);
						*(DWORD*)(Weapon + 68) = GetTickCount() + (2000 * RentWeapon.find(Quest.GetIndex())->second.Time);
						*(DWORD*)(Weapon + 72) = 0;
						ItemOnTimer(Weapon, 0, 0);
					}
					else
						CBase::Delete((void*)ValidItem);
				}
			}
			else
				IPlayer.SystemMessage("Not enough coins!", TEXTCOLOR_RED);
		}
		else
			CPlayer::Write(IPlayer.GetOffset(), 67, "b", 40);
		return;
	}

	if (IPlayer.IsOnline() && Quest.GetIndex() == (PLQuest % 65536))
	{
		if (IPlayer.IsOnline() && Protect32::Active == true)
		{
			IPlayer.SystemMessage("You can not register while Protecting Leader running.", TEXTCOLOR_RED);
			return;
		}

		if (IPlayer.IsOnline() && IPlayer.GetPID() != IPlayer.GetGID())
		{
			IPlayer.SystemMessage("Only guild leader can register for Protecting Leader.", TEXTCOLOR_RED);
			return;
		}

		if (IPlayer.IsOnline() && ProtectLeaderName.count(IPlayer.GetGID()))
		{
			IPlayer.SystemMessage("You already registered to Protecting Leader.", TEXTCOLOR_RED);
			return;
		}
		else {
			int PlayerGuild = CPlayer::GetGuildName(PlayerOffset);

			if (IPlayer.IsOnline() && PlayerGuild)
			{
				ProtectLeaderName.replaceInsert(IPlayer.GetGID(), (char*)CPlayer::GetGuildName(PlayerOffset));
				ProtectLeaderList.push_back(IPlayer.GetGID());

				std::string Datko = "./Database/ProtectLeader.db";
				std::fstream DGkLOG;
				DGkLOG.open(Datko, std::fstream::in | std::fstream::out | std::fstream::app);
				DGkLOG << "(registration (GID " << IPlayer.GetGID() << ")(name '" << (char*)CPlayer::GetGuildName(PlayerOffset) << "'))" << std::endl;
				DGkLOG.close();

				IPlayer.SystemMessage("Successfully registered to Protecting Leader.", TEXTCOLOR_GREEN);
			}
			else {
				IPlayer.SystemMessage("Guild level is low for Protecting Leader registration.", TEXTCOLOR_RED);
			}
		}

		return;
	}

	if (IPlayer.IsOnline() && Quest.GetIndex() == (DNPCQ % 65536))
	{
		if (DNPCDD && DNPCDC && DNPCDC >= (int)time(0))
		{
			IPlayer.SystemMessage("Cooldown did not over for Damage NPC!", TEXTCOLOR_RED);
			return;
		}

		int DNPCItemCheck = CPlayer::FindItem(IPlayer.GetOffset(), DNPCII, 1);

		if (!DNPCItemCheck)
		{
			IPlayer.SystemMessage("You do not have any event item to collect!", TEXTCOLOR_RED);
			return;
		}

		if (DNPCEDailyLimit < DNPCDL)
		{
			if (DNPCItemCheck)
			{
				IItem IItem((void*)DNPCItemCheck);
				int CheckItem = 0, CheckItemLeft = DNPCIA - DNPCECollectedTotalItem;

				if (IItem.GetAmount() > CheckItemLeft)
					CheckItem = CheckItemLeft;
				else
					CheckItem = IItem.GetAmount();

				DNPCECollectedTotalItem += CheckItem;
				EventQuests.insert(1, DNPCECollectedTotalItem);
				std::string msg = Int2String(CheckItem) + " damage event items have been collected from you. " + Int2String(DNPCECollectedTotalItem) + " damage event items have been collected in total! " + Int2String(CheckItemLeft) + " needed to start event";
				IPlayer.SystemMessage(msg, TEXTCOLOR_GREEN);
				CPlayer::RemoveItem(IPlayer.GetOffset(), 9, DNPCII, CheckItem);
			}

			if (DNPCECollectedTotalItem == DNPCIA)
			{
				if (DNPCELeftTime > 0)
					CPlayer::WriteAll(0xFF, "ds", 234, "[Damage NPC] Damage Event time has been extended!");
				else {
					DNPCELeftTime = (int)time(0);
					CPlayer::WriteAll(0xFF, "ds", 234, "[Damage NPC] Damage Event has been started!");
				}

				DamageEvent::Active = true;
				DNPCEDailyLimit++;
				DNPCELeftTime += (DNPCDU);
				DNPCECollectedTotalItem = 0;
				EventQuests.erase(1);
				DNPCDC = (int)time(0) + DNPCDD;
			}
		}
		else {
			IPlayer.SystemMessage("Daily limit has been exceeded! Please try again tomorrow!", TEXTCOLOR_RED);
		}

		return;
	}

	if (IPlayer.IsOnline() && QuestsNotice.count(Quest.GetIndex()))
	{
		if (Quest.GetFlag() == QuestsNotice.find(Quest.GetIndex())->second.qFlag){
			if (CPlayer::FindItem(IPlayer.GetOffset(), QuestsNotice.find(Quest.GetIndex())->second.QuestItem, QuestsNotice.find(Quest.GetIndex())->second.qAmount)){

				std::string msg = (std::string)IPlayer.GetName() + " " + QuestsNotice.find(Quest.GetIndex())->second.Notice;
				CPlayer::WriteAll(0xFF, "dsd", 247, msg.c_str(), NOTICECOLOR_WHITE);
			}
		}
	}

	if (IPlayer.IsOnline() && cQuestsNotice.count(Quest.GetIndex()))
	{
	//		int QuestIn = (CQuestsNotice.find(Quest.GetIndex())->second.clearQ << 16);
		int ClearQ = CPlayer::CheckQuestClear((int)IPlayer.GetOffset(), cQuestsNotice.find(Quest.GetIndex())->second.clearQ);
			if (Quest.GetFlag() == cQuestsNotice.find(Quest.GetIndex())->second.qFlag){
				if (ClearQ){
					std::string msg = (std::string)IPlayer.GetName() + " " + QuestsNotice.find(Quest.GetIndex())->second.Notice;
					CPlayer::WriteAll(0xFF, "dsd", 247, msg.c_str(), NOTICECOLOR_WHITE);
				}
			}
	}

	if (IPlayer.IsOnline() && Quest.GetIndex() == (DNPCRQ % 65536))
	{
		int CheckItemLeft = DNPCIA - DNPCECollectedTotalItem;
		std::string msg = Int2String(DNPCECollectedTotalItem) + " damage event items have been collected in total! " + Int2String(CheckItemLeft) + " needed to start event";;
		IPlayer.SystemMessage(msg, TEXTCOLOR_GREEN);
		return;
	}

	if (IPlayer.IsOnline() && Quest.GetIndex() == (ENPCQ % 65536))
	{
		if (ENPCDD && ENPCDC && ENPCDC >= (int)time(0))
		{
			IPlayer.SystemMessage("Cooldown did not over for Event NPC!", TEXTCOLOR_RED);
			return;
		}

		int ENPCItemCheck = CPlayer::FindItem(IPlayer.GetOffset(), ENPCII, 1);

		if (!ENPCItemCheck)
		{
			IPlayer.SystemMessage("You do not have any event item to collect!", TEXTCOLOR_RED);
			return;
		}

		if (NPCEDailyLimit < ENPCDL)
		{
			if (ENPCItemCheck)
			{
				IItem IItem((void*)ENPCItemCheck);
				int CheckItem = 0, CheckItemLeft = ENPCIA - NPCECollectedTotalItem;

				if (IItem.GetAmount() > CheckItemLeft)
					CheckItem = CheckItemLeft;
				else
					CheckItem = IItem.GetAmount();

				NPCECollectedTotalItem += CheckItem;
				EventQuests.insert(2, NPCECollectedTotalItem);
				std::string msg = Int2String(CheckItem) + " event items have been collected from you. " + Int2String(NPCECollectedTotalItem) + " event items have been collected in total! " + Int2String(CheckItemLeft) + " needed to start event";;;
				IPlayer.SystemMessage(msg, TEXTCOLOR_GREEN);
				CPlayer::RemoveItem(IPlayer.GetOffset(), 9, ENPCII, CheckItem);
			}

			if (NPCECollectedTotalItem == ENPCIA)
			{
				if (NPCELeftTime > 0)
					CPlayer::WriteAll(0xFF, "ds", 234, "[Exp Event NPC] Event time has been extended!");
				else {
					NPCELeftTime = (int)time(0);
					CPlayer::WriteAll(0xFF, "ds", 234, "[Exp Event NPC] Event has been started!");
				}

				CPlayer::SnowEvent(3);
				Snow = 3;
				CPlayer::WriteAll(68, "bIdd", 74, 64, 0, 1000, 0);

				CPlayer::SetEventCode(0, 1);
				NPCEDailyLimit++;
				NPCELeftTime += ENPCDU;
				NPCECollectedTotalItem = 0;
				EventQuests.erase(2);
				ENPCDC = (int)time(0) + ENPCDD;
			}
		}
		else {
			IPlayer.SystemMessage("Daily limit has been exceeded! Please try again tomorrow!", TEXTCOLOR_RED);
		}

		return;
	}

	if (IPlayer.IsOnline() && Quest.GetIndex() == (ENPCRQ % 65536))
	{
		int CheckItemLeft = ENPCIA - NPCECollectedTotalItem;
		std::string msg = Int2String(NPCECollectedTotalItem) + " event items have been collected in total! " + Int2String(CheckItemLeft) + " needed to start event";;;
		IPlayer.SystemMessage(msg, TEXTCOLOR_GREEN);
		return;
	}

	if (IPlayer.IsOnline() && BufferCheck.count(Quest.GetIndex()) && BufferCheck.find(Quest.GetIndex())->second.Index == Quest.GetIndex())
	{
		if (IPlayer.GetLevel() <= BufferCheck.find(Quest.GetIndex())->second.Limit)
		{
			int cd = BufferCheck.find(Quest.GetIndex())->second.cd;

			if (IPlayer.IsBuff(1625))
			{
				IPlayer.SystemMessage("You need to wait " + Int2String(IPlayer.GetBuffRemain(1625)) + " seconds to re-use buff.", TEXTCOLOR_RED);
				return;
			}

			if (cd)
				IPlayer.Buff(1625, cd, 1);


			IPlayer.Buff(48, 1800, 8 * (BufferCheck.find(Quest.GetIndex())->second.Grade) + 3);
			IPlayer.Buff(50, 1800, 8 * (BufferCheck.find(Quest.GetIndex())->second.Grade) + 3);
			IPlayer.Buff(47, 1800, 8 * (BufferCheck.find(Quest.GetIndex())->second.Grade) + 3);
			IPlayer.Buff(49, 1800, 8 * (BufferCheck.find(Quest.GetIndex())->second.Grade) + 3);
			IPlayer.Buff(46, 1800, 8 * (BufferCheck.find(Quest.GetIndex())->second.Grade) + 3);
			IPlayer.Buff(36, 1800, 8 * (BufferCheck.find(Quest.GetIndex())->second.Grade) + 16);
			CChar::CancelAllBuff(IPlayer.GetOffset(), 37);
			int AddBuff = CBuff::CreateBuff(37, 1800, 30 * (BufferCheck.find(Quest.GetIndex())->second.Grade) + 5, 20 * (BufferCheck.find(Quest.GetIndex())->second.Grade) + 5);
			(*(int(__thiscall **)(int, int))(*(DWORD *)PlayerOffset + 180))(PlayerOffset, AddBuff);
			IPlayer.Buff(12, 1800, BufferCheck.find(Quest.GetIndex())->second.Speed);
		}
		else {
			IPlayer.SystemMessage("Your level is too high!", TEXTCOLOR_RED);
		}

		return;
	}

	if (IPlayer.IsOnline() && Quest.GetIndex() == (LMSQuest % 65536))
	{
		if (IPlayer.IsOnline() && LastManStand::Active == true)
		{
			IPlayer.SystemMessage(std::string(LMSName)+" already running. Please try again later.", TEXTCOLOR_RED);
			return;
		}

		if (LMSHWID && LastManHWID.count(IPlayer.GetHWID()))
		{
			std::string msg = "You have already registered to " + std::string(LMSName) + " using another character.";
			IPlayer.SystemMessage(msg.c_str(), TEXTCOLOR_RED);
			return;
		}

		if (IPlayer.GetLevel() < LMSLimit)
		{
			IPlayer.SystemMessage("You must be atleast " + Int2String(LMSLimit) + " to register for " + std::string(LMSName) , TEXTCOLOR_RED);
		}
		else {
			if (!LastManRegistration.count(IPlayer.GetPID()))
			{
				LastManRegistration.insert(IPlayer.GetPID());

				if (LMSHWID)
					LastManHWID.insert(IPlayer.GetHWID());

				IPlayer.SystemMessage("Successfully registered to " + std::string(LMSName), TEXTCOLOR_GREEN);
			}
			else {
				IPlayer.SystemMessage("You already registered to " + std::string(LMSName), TEXTCOLOR_RED);
			}
		}

		return;
	}

	if (IPlayer.IsOnline() && EventMapsQuests.count((Quest.GetIndex() * 1000) + Quest.GetFlag())) {
		int Index = (Quest.GetIndex() * 1000) + Quest.GetFlag();
		eventMap questEvent = EventMapsQuests.find(Index)->second;
		
		if (questEvent.LvlMin > IPlayer.GetLevel() || questEvent.LvlMax < IPlayer.GetLevel()) {
			IPlayer.SystemMessage(questEvent.Name + " registration levels must be between " + Int2String(questEvent.LvlMin) + " and " + Int2String(questEvent.LvlMax) + ".", TEXTCOLOR_RED);
			return;
		}
		if (EventMapsRegistration.count(Index) && EventMapsRegistration.find(Index)->second.count(IPlayer.GetPID())) {
			IPlayer.SystemMessage("You are already registered for " + questEvent.Name + "." , TEXTCOLOR_RED);
			return;
		}
		if (EventMapsOn.count(Index)) {
			int PlayerX = IPlayer.GetX() >> 13;
			int PlayerY = IPlayer.GetY() >> 13;
			if (questEvent.Maps.count((PlayerX * 1000) + PlayerY)) {
				IPlayer.SystemMessage("You have left "+questEvent.Name+".", TEXTCOLOR_FAILED);
				IPlayer.RemoveSavedBuff(BuffNames::EventMapQuest);
				IPlayer.RemoveSavedBuff(BuffNames::EventMapLapse);
				IPlayer.CloseScreenTime();
				return;
			}
			IPlayer.SystemMessage(questEvent.Name+" is currently running. Please try at another time.", TEXTCOLOR_RED);
			return;
		}

		if (questEvent.Type == 1) {
			if (InstancesCD.count(Index)) {
				if (InstancesCD.findValue(Index) >= GetTickCount()) {
					IPlayer.SystemMessage("Try again in a few seconds", TEXTCOLOR_RED);
					return;
				}
				else
					InstancesCD.erase(Index);
			}

			if (IPlayer.IsBuff(BuffNames::InstanceCD))
			{
				int Time = IPlayer.GetBuffRemain(BuffNames::InstanceCD) / 60;
				std::string msg = "You need to wait ";

				if (Time > 0)
				{
					msg = msg + Int2String(Time);
					msg = msg + " minutes to re-join " + questEvent.Name + ".";
				}
				else {
					msg = msg + " less then a minute to re-join " + questEvent.Name + ".";
				}

				IPlayer.SystemMessage(msg.c_str(), TEXTCOLOR_RED);
				return;
			}

			if (IPlayer.IsParty())
			{
				int Party = CParty::FindParty(IPlayer.GetPartyID());

				if (!Party)
					return;

				if (!CParty::IsHead(Party, (int)IPlayer.Offset))
				{
					IPlayer.SystemMessage("Only the party leader can start " + questEvent.Name + ".", TEXTCOLOR_RED);
					CIOObject::Release((void*)Party);
					return;
				}

				if (CParty::GetSize((void*)Party) < questEvent.PTSize)
				{
					IPlayer.SystemMessage("You need at least "+Int2String(questEvent.PTSize)+" members to start " + questEvent.Name + ".", TEXTCOLOR_RED);
					CIOObject::Release((void*)Party);
					return;
				}

				bool allMembersHaveItems = true;
				bool notAllowed = false;

				for (int i = CParty::GetPlayerList((void*)Party); i; i = CBaseList::Pop((void *)i))
				{
					int Members = *(DWORD*)((void*)i);
					IChar Member((void*)*(DWORD*)((void*)i));

					if (!CheckRequiredItemsMembers(Member, questEvent)) {
						allMembersHaveItems = false;
						IPlayer.SystemMessage("Player: " +  std::string(Member.GetName()) + " do not have the required key or money for " + questEvent.Name + ".", TEXTCOLOR_RED);
					}

					if (!allMembersHaveItems) {
						CIOObject::Release((void*)Party);
						return;
					}

					if (CChar::IsNormal(Members) && Member.IsPVPValid())
					{
						if (questEvent.LvlMin > Member.GetLevel() || questEvent.LvlMax < Member.GetLevel() || Member.IsBuff(BuffNames::InstanceCD))
							notAllowed = true;
					}
					else
						notAllowed = true;
				}

				if (notAllowed) {
					IPlayer.SystemMessage("Some of your party members do not meet the requirements or have time limit.", TEXTCOLOR_RED);
					CIOObject::Release((void*)Party);
					return;
				}

				if (!CheckRequiredItems(IPlayer, questEvent)) return;
				RemoveRequiredItems(IPlayer, questEvent);

				SpawnEventMap(questEvent, 0, questEvent.Duration * 1000);
				for (int i = CParty::GetPlayerList((void*)Party); i; i = CBaseList::Pop((void *)i))
				{
					int Members = *(DWORD*)((void*)i);
					IChar Member((void*)*(DWORD*)((void*)i));

					if (Member.IsOnline()) {
						Member.UpdateBuff(BuffNames::EventMapQuest, BuffNames::BuffTime, Index);
						Member.ScreenTime(questEvent.Duration);
						RemoveRequiredItemsMembers(Member, questEvent);

					}
				}
				CIOObject::Release((void*)Party);
			}
			else {
				IPlayer.SystemMessage("You need a party to start " + questEvent.Name + ".", TEXTCOLOR_RED);
				return;
			}

			IPlayer.SystemMessage("You have started " + questEvent.Name + ".", TEXTCOLOR_GREEN);
			return;
		}

		if (!EventMapsQuestsOn.count(Index)) {
			IPlayer.SystemMessage("Registration for " + questEvent.Name + " is not yet activated.", TEXTCOLOR_RED);
			return;
		}

		if (!CheckRequiredItems(IPlayer, questEvent)) return;
		RemoveRequiredItems(IPlayer, questEvent);

		EventMapsRegistration.lock();
		ConcurrentSet<int>& mapSet = EventMapsRegistration.findPointer(Index);
		mapSet.insert(IPlayer.GetPID());
		EventMapsRegistration.unlock();

		std::string Datko = "./Database/EventMaps.db";
		std::fstream DGkLOG;
		DGkLOG.open(Datko, std::fstream::in | std::fstream::out | std::fstream::app);
		DGkLOG << "(registration (QID " << Index << ")(PID " << IPlayer.GetPID() << "))" << std::endl;
		DGkLOG.close();

		IPlayer.SystemMessage("You have been registered to "+ questEvent.Name+".", TEXTCOLOR_GREEN);
		return;
	}

	if (IPlayer.IsOnline() && QuestWebsite.count((Quest.GetIndex() * 1000) + Quest.GetFlag())) {
		IPlayer.OpenWebsite(QuestWebsite.find((Quest.GetIndex() * 1000) + Quest.GetFlag())->second);
		return;
	}

	if (IPlayer.IsOnline() && Quest.GetIndex() == (DTQuest % 65536))
	{
		if (IPlayer.IsOnline() && DuelTournament::Active)
		{
			IPlayer.SystemMessage("Duel Tournament already running. Please try again later.", TEXTCOLOR_RED);
			return;
		}

		if (!IPlayer.GetDTArena())
		{
			IPlayer.SystemMessage("You must be atleast level 50 to register for Duel Tournament.", TEXTCOLOR_RED);
			return;
		}

		if (DuelNames.count(IPlayer.GetPID())) {
			IPlayer.SystemMessage("You are already registered for Duel Tournament.", TEXTCOLOR_RED);
			return;
		}
		
		DuelRegistre reg;
		reg.PID = IPlayer.GetPID();
		reg.Name = IPlayer.GetName();
		reg.Level = IPlayer.GetLevel();
		reg.Class = IPlayer.GetClass();
		reg.nVictory = 0;
		DuelNames.replaceInsert(IPlayer.GetPID(), reg.Name);
		int i = IPlayer.GetDTArena();

		DuelRegistrationList.lock();
		std::vector<DuelRegistre>& kc = DuelRegistrationList.findPointer(i);
		kc.push_back(reg);
		DuelRegistrationList.unlock();

		IPlayer.SystemMessage("Successfully registered to Duel Tournament for levels " + getTournamentName(IPlayer.GetDTArena()) + ".", TEXTCOLOR_GREEN);

		std::string Datko = "./Database/Duel.db";
		std::fstream DGkLOG;
		DGkLOG.open(Datko, std::fstream::in | std::fstream::out | std::fstream::app);
		DGkLOG << "(registration (type " << IPlayer.GetDTArena() << ")(PID " << IPlayer.GetPID() << ")(name '" << IPlayer.GetName() << "')(class " << IPlayer.GetClass() << ")(level " << IPlayer.GetLevel() << "))" << std::endl;
		DGkLOG.close();

		DuelTournament::RegisterAmount += 1;

		return;
	}

	if (IPlayer.IsOnline() && Quest.GetIndex() == (RaidQuest % 65536))
	{
		if (Raid::Active == true)
			IPlayer.SystemMessage("Raid System currently running!", TEXTCOLOR_RED);
		else
			if (RaidItem && RaidItemAmount && !CPlayer::FindItem(IPlayer.GetOffset(), RaidItem, RaidItemAmount))
				IPlayer.SystemMessage("You do not have the required item to register for " + thisServerName + "Raid System!", TEXTCOLOR_RED);
			else
				if (IPlayer.GetLevel() < RaidLevel)
					IPlayer.SystemMessage("Your level is too low to register for " + thisServerName + " Raid System!", TEXTCOLOR_RED);
				else
					if (RaidSystem.count(IPlayer.GetPID()))
						IPlayer.SystemMessage("You're already registered to " + thisServerName + " Raid System!", TEXTCOLOR_RED);
					else {
						if (CPlayer::RemoveItem(IPlayer.GetOffset(), 9, RaidItem, RaidItemAmount)) {
							RaidSystem.insert(IPlayer.GetPID());
							IPlayer.SystemMessage("Successfully registred to " + thisServerName + " Raid System.", TEXTCOLOR_GREEN);
						}
					}
					return;
	}

	if (IPlayer.IsOnline() && Quest.GetIndex() == (HellQuest % 65536))
	{
		if(Hell::Lapse > GetTickCount() || Hell::Countdown > 0){
			IPlayer.SystemMessage("Try again in a few seconds",TEXTCOLOR_RED);
			return;
		}
		if (IPlayer.IsBuff(167))
		{
			int Time = IPlayer.GetBuffRemain(167) / 60;
			std::string msg = "You need to wait ";

			if (Time > 0)
			{
				msg = msg + Int2String(Time);
				msg = msg + " minutes to re-join Picture Of Hell!";
			} else {
				msg = msg + " less then a minute to re-join Picture Of Hell!";
			}

			IPlayer.SystemMessage(msg.c_str(),TEXTCOLOR_RED);
			return;
		}

		if (IPlayer.IsOnline() && Hell::Active == true)
		{
			IPlayer.SystemMessage("Picture Of Hell already running. Please try again later.",TEXTCOLOR_RED);
			return;
		}

		if (IPlayer.IsOnline() && IPlayer.IsParty())
		{
			int Party = CParty::FindParty(IPlayer.GetPartyID());

			if (!Party)
				return;

			if (!CParty::IsHead(Party, (int)IPlayer.Offset))
			{
				IPlayer.SystemMessage("You are not the party leader to start Picture Of Hell.", TEXTCOLOR_RED);
				CIOObject::Release((void*)Party);
				return;
			}
			bool notAllowed = false;
			for (int i = CParty::GetPlayerList((void*)Party); i; i = CBaseList::Pop((void *)i))
			{
				int Members = *(DWORD*)((void*)i);
				IChar Member((void*)*(DWORD*)((void*)i));

				if (CChar::IsNormal(Members) && IPlayer.IsValid())
				{
					if (Member.GetLevel() < 60 || Member.IsBuff(167))
						notAllowed = true;
				}
				else
					notAllowed = true;
			}

			if (notAllowed) {
				IPlayer.SystemMessage("Some of your party members do not meet the requirements or have time limit.",TEXTCOLOR_RED);
				CIOObject::Release((void*)Party);
				return;
			}

			Hell::Delay = 0;
			Hell::KillCount = 0;
			Hell::Countdown = -1;
			Hell::Round = 1;
			Hell::Time = 1803;
			Hell::Size = CParty::GetSize((void*)Party);
			Hell::Rebirth = CParty::GetSize((void*)Party) * 3;
			Hell::Active = true;

			for (int i = CParty::GetPlayerList((void*)Party); i; i = CBaseList::Pop((void *)i))
			{
				int Members = *(DWORD*)((void*)i);
				IChar Member((void*)*(DWORD*)((void*)i));

				if (CChar::IsNormal(Members) && IPlayer.IsValid())
				{
					CPlayer::Write(Member.GetOffset(), 0xFF, "ddddd", 242, 74, 255, 255, 255);
					Member.Teleport(HellMap, HellX, HellY);
					Member.Buff(166,1802,0);
					Member.ScreenTime(1800);
					Member.SetRebirthTalisman(Hell::Rebirth);
				}
			}
			CIOObject::Release((void*)Party);
		} else {
			IPlayer.SystemMessage("You need a party to start Picture Of Hell.",TEXTCOLOR_RED);
			return;
		}

		return;
	}

	if (IPlayer.IsOnline() && Quest.GetIndex() == (ScenarioQuest % 65536))
	{
		if (ScenarioRegistration.count(IPlayer.GetPID()) && IPlayer.GetPID() == IPlayer.GetGID())
		{
			int Check = 0;

			if (!ScenarioGuild.empty())
			{
				int Size = ScenarioGuild.size();
				for (int i = 0; i < Size; i++)
				{
					if (ScenarioGuild[i].GID == IPlayer.GetGID())
					{
						Check = 1;
						break;
					}
				}
			}

			if (Check == 0)
				ScenarioRegistration.erase(IPlayer.GetPID());
		}

		if (IPlayer.IsOnline() && Scenario::Active == true)
		{
			IPlayer.SystemMessage("You can not register while Destructing Key Points running.",TEXTCOLOR_RED);
			return;
		}

		if (IPlayer.IsOnline() && IPlayer.GetPID() != IPlayer.GetGID())
		{
			IPlayer.SystemMessage("Only guild leader can register for Destructing Key Points.",TEXTCOLOR_RED);
			return;
		}

		if (IPlayer.IsOnline() && ScenarioRegistration.count(IPlayer.GetPID()))
		{
			IPlayer.SystemMessage("You already registered to Destructing Key Points.",TEXTCOLOR_RED);
			return;
		} else {
			int PlayerGuild = CPlayer::GetGuildName(PlayerOffset);

			if (IPlayer.IsOnline() && PlayerGuild)
			{
				ScenarioRegistration.insert(IPlayer.GetPID());
				Scenario::RegisterAmount += 1;
				DKInfo dk = DKInfo();
				dk.GID = IPlayer.GetGID();
				dk.Name = (char*)CPlayer::GetGuildName(PlayerOffset);
				ScenarioGuild.push_back(dk);
				
				std::string Datko = "./Database/Destructing.db";
				std::fstream DGkLOG;
				DGkLOG.open(Datko, std::fstream::in | std::fstream::out | std::fstream::app);
				DGkLOG << "(registration (GID " << IPlayer.GetGID() << ")(name '" << (char*)CPlayer::GetGuildName(PlayerOffset) << "'))" << std::endl;
				DGkLOG.close();

				IPlayer.SystemMessage("Successfully registered to Destructing Key Points.",TEXTCOLOR_GREEN);
			} else {
				IPlayer.SystemMessage("Guild level is low for Destructing Key Points registration.",TEXTCOLOR_RED);
			}
		}

		return;
	}

	if (IPlayer.IsOnline() && HonorShop.count(Quest.GetIndex()))
	{
		if (HonorShop.find(Quest.GetIndex())->second > IPlayer.GetProperty(PlayerProperty::RPx))
		{
			IPlayer.SystemMessage("You do not have enough reward points.",TEXTCOLOR_RED);
			return;
		} else {
			IPlayer.SetHonor(0, -HonorShop.find(Quest.GetIndex())->second, 0, 0, 0, 0, 0, 0, 0, 0);
		}
	}

	if (IPlayer.IsOnline() && Quest.GetIndex() == (BFQuest % 65536))
	{
		std::string SysName(BFName);
		if (Quest.GetFlag() == 2)
			SysName = "Good Vs Evil";

		if (Battlefield::Active == true)
		{
			std::string msg = "You can not register while " + SysName + " is running.";
			IPlayer.SystemMessage(msg.c_str(),TEXTCOLOR_RED);
			return;
		}

		if (BattlefieldRegistration.count(IPlayer.GetPID()))
		{
			std::string msg = "You are already registered to " + SysName;
			IPlayer.SystemMessage(msg.c_str(),TEXTCOLOR_RED);
			return;
		}
		
		if (BFHWID && BattlefieldHWID.count(IPlayer.GetHWID()))
		{
			std::string msg = "You have already registered to " + SysName + " using another character.";
			IPlayer.SystemMessage(msg.c_str(), TEXTCOLOR_RED);
			return;
		}

		if (IPlayer.GetLevel() < BattlefieldLevel)
		{
			IPlayer.SystemMessage("You must be atleast " + Int2String(BattlefieldLevel) + " to register for Battlefield", TEXTCOLOR_RED);
			return;
		}
		else {
			BattlefieldRegistration.insert(IPlayer.GetPID());

			if (BFHWID)
				BattlefieldHWID.insert(IPlayer.GetHWID());

			Battlefield::RegisterAmount += 1;
			std::string msg = "Successfully registered to " + SysName;
			IPlayer.SystemMessage(msg.c_str(),TEXTCOLOR_GREEN);
			return;
		}

		return;
	}

	if (IPlayer.IsOnline() && Quest.GetIndex() == (CaptureQuest % 65536))
	{
		if (CaptureFlag::Active == true)
		{
			IPlayer.SystemMessage("You can not register while Capture the Flag is running.",TEXTCOLOR_RED);
			return;
		}

		if (CaptureRegistration.count(IPlayer.GetPID()))
		{
			IPlayer.SystemMessage("You already registered to Capture The Flag.",TEXTCOLOR_RED);
			return;
		} else {
			CaptureRegistration.insert(IPlayer.GetPID());
			IPlayer.SystemMessage("Successfully registered to Capture The Flag.",TEXTCOLOR_GREEN);
			return;
		}

		return;
	}

	if (IPlayer.IsOnline() && Quest.GetIndex() == (CPQuestR % 65536))
	{
		if(!IPlayer.IsBuff(BuffNames::CPRed)) {
			IPlayer.SystemMessage("You are not from the red team", TEXTCOLOR_RED);
			return;
		}

		if (CaptureFlag::PlayerID == PlayerOffset) {
			CaptureFlag::CurrentCapturers = BuffNames::CPRed; 
			CPlayer::WriteInMap(CaptureMap, 0xFF, "dsd", 247, "Flag Monster has been respawned in Red Zone.", NOTICECOLOR_REDLONG);
			
			//Spawn(CaptureMonster, 1, RedCPSummonX, RedCPSummonY, CaptureMap);
			Summon((int)IPlayer.GetOffset(), CaptureMap, RedCPSummonX, RedCPSummonY, CaptureMonster, 1, 0, 0, 0, 0);

			//Spawn(CPMob, CPMobAmount, CPMobRedX + CTools::Rate(-1050, 1050), CPMobRedY + CTools::Rate(-1050, 1050), CaptureMap);
				for (int i = 0; i < CPMobAmount; i++)
				Summon((int)IPlayer.GetOffset(), CaptureMap, CPMobRedX+CTools::Rate(-1050, 1050), CPMobRedY+CTools::Rate(-1050, 1050), CPMob, 1, 0, 0, 0, 0);

			CaptureFlag::PlayerID = 0;
		}else
			IPlayer.SystemMessage("Only Capturer is allowed to give the flag.", TEXTCOLOR_RED);
			
		return;
	}
	if (IPlayer.IsOnline() && Quest.GetIndex() == (CPQuestB % 65536))
	{
		if (!IPlayer.IsBuff(BuffNames::CPBlue)) {
			IPlayer.SystemMessage("You are not from the blue team", TEXTCOLOR_RED);
			return;
		}

		if (CaptureFlag::PlayerID == PlayerOffset) {
			CaptureFlag::CurrentCapturers = BuffNames::CPBlue;
			CPlayer::WriteInMap(CaptureMap, 0xFF, "dsd", 247, "Flag Monster has been respawned in Blue Zone.", NOTICECOLOR_REDLONG);

			//Spawn(CaptureMonster, 1, BlueCPSummonX, BlueCPSummonY, CaptureMap);
		
			//Spawn(CPMob, CPMobAmount, CPMobBlueX + CTools::Rate(-1050, 1050), CPMobBlueY + CTools::Rate(-1050, 1050), CaptureMap);

			Summon((int)IPlayer.GetOffset(), CaptureMap, BlueCPSummonX, BlueCPSummonY, CaptureMonster, 1, 0, 0, 0, 0);

			for (int i = 0; i < CPMobAmount; i++)
				Summon((int)IPlayer.GetOffset(), CaptureMap, CPMobBlueX + CTools::Rate(-1050, 1050), CPMobBlueY + CTools::Rate(-1050, 1050), CPMob, 1, 0, 0, 0, 0);
			
			CaptureFlag::PlayerID = 0;
		}
		else
			IPlayer.SystemMessage("Only Capturer is allowed to give the flag.", TEXTCOLOR_RED);

		return;
	}

	if (IPlayer.IsOnline() && Quest.GetIndex() == (EmokQuestIndex % 65536))
	{

		if (IPlayer.GetLevel() < EmokLvl)
		{
			IPlayer.SystemMessage("You must be atleast " + Int2String(EmokLvl) + " to teleport.", TEXTCOLOR_RED);
			return;
		}

		int honor = 0, addtime = 0;

		honor = IPlayer.GetProperty(PlayerProperty::HPx);

		if(honor >= 2790 && honor < 12090)
			addtime = 30;
		else if(honor >= 12090 && honor < 44640)
			addtime = 40;
		else if(honor >= 44640 && honor < 78740)
			addtime = 50;
		else if(honor >= 78740)
			addtime = 60;

		if (IPlayer.GetProperty(PlayerProperty::EmokTime) > 10)
		{
			IPlayer.Buff(BuffNames::EmokTeleport, BuffNames::BuffTime, 0);
			IPlayer.Buff(156, IPlayer.GetProperty(PlayerProperty::EmokTime), IPlayer.GetProperty(PlayerProperty::EmokEXP));
			IPlayer.Teleport(EmokMap, EmokX, EmokY);
		} else if (IPlayer.GetProperty(PlayerProperty::EmokDay) != String2Int(Time::GetDay()))
		{
			if (IPlayer.GetBuffValue(156)) {
				IPlayer.SystemMessage("Your daily free time will be activated once your certificate runs out of time.", TEXTCOLOR_YELLOW);
				IPlayer.Buff(BuffNames::EmokTeleport, BuffNames::BuffTime, 0); 
				IPlayer.Teleport(EmokMap, EmokX, EmokY);
				return;
			}

			IPlayer.SetProperty(PlayerProperty::EmokTime, 3600 + addtime);
			IPlayer.SetProperty(PlayerProperty::EmokDay, String2Int(Time::GetDay()));
			IPlayer.SetProperty(PlayerProperty::EmokEXP, 0);
			IPlayer.Buff(BuffNames::EmokTeleport, BuffNames::BuffTime, 0);
			IPlayer.Buff(156, 3600 + addtime, 0);
			IPlayer.Teleport(EmokMap, EmokX, EmokY);
			CDBSocket::Write(83,"ddd",IPlayer.GetPID(), String2Int(Time::GetDay()), 3600 + addtime);
		} else {
			IPlayer.SystemMessage("You already used your daily free time.",TEXTCOLOR_RED);
		}

		return;
	}

	// new mystery

	if (IPlayer.IsOnline() && (Quest.GetIndex() == (MystPAtkQ % 65536) || Quest.GetIndex() == (MystMAtkQ % 65536) || Quest.GetIndex() == (MystHPQ % 65536) || Quest.GetIndex() == (MystOTPQ % 65536) || Quest.GetIndex() == (MystEVAQ % 65536) || Quest.GetIndex() == (MystDefQ % 65536)))
	{
		int OTP = IPlayer.IsBuff(BuffNames::MystOTP);
		int EVA = IPlayer.IsBuff(BuffNames::MystEVA);
		int HP = IPlayer.IsBuff(BuffNames::MystHP);
		int PhyAtk = IPlayer.IsBuff(BuffNames::MystPhy);
		int MagAtk = IPlayer.IsBuff(BuffNames::MystMag);
		int Def = IPlayer.IsBuff(BuffNames::MystDef);

		if (!NewMystEnable){
			IPlayer.BoxMsg("Mystery skills are disabled.");
			return;
		}

		if (IPlayer.GetLevel() < MystLevel){
			IPlayer.BoxMsg("You must be atleast " + Int2String(MystLevel) + " to learn Mystery Skills.");
			return;
		}

		if (OTP || EVA || HP || PhyAtk || MagAtk || Def){
			IPlayer.BoxMsg("You already learnt a Mystery Skill.");
			return;
		}

		if (Quest.GetIndex() == MystPAtkQ){
			int CheckGrade = 0;
			int GetGrade = IPlayer.GetBuffValue(BuffNames::MystPhy);
			if (IPlayer.GetLevel() >= MystLevelMax)
				CheckGrade = 30;
			else
				CheckGrade = IPlayer.GetLevel() - MystLevel + 1;

					IPlayer.SaveBuff(BuffNames::MystPhy, BuffNames::BuffTime, CheckGrade, 0 , 0);
					IPlayer.SetBuffIcon(-2, -1, MystPAtkS, MystPAtkS);

					if (CheckGrade){
						IPlayer.AddMinAttack(10 * CheckGrade);
						IPlayer.BoxMsg("You have learnt Mystery Skill of Physical Attack.");
					}
					else {
						IPlayer.AddMinAttack(10);
						IPlayer.BoxMsg("You have learnt Mystery Skill of Physical Attack.");
					}
			}

		else if (Quest.GetIndex() == MystMAtkQ){
			int CheckGrade = 0;
			int GetGrade = IPlayer.GetBuffValue(BuffNames::MystMag);
			if (IPlayer.GetLevel() >= MystLevelMax)
				CheckGrade = 30;
			else
				CheckGrade = IPlayer.GetLevel() - MystLevel + 1;

					IPlayer.SaveBuff(BuffNames::MystMag, BuffNames::BuffTime, CheckGrade, 0, 0);
					IPlayer.SetBuffIcon(-2, -1, MystMAtkS, MystMAtkS);

					if (CheckGrade){
						IPlayer.AddMaxAttack(10 * CheckGrade);
						IPlayer.BoxMsg("You have learnt Mystery Skill of Magical Attack.");
					}
					else {
						IPlayer.AddMaxAttack(10);
						IPlayer.BoxMsg("You have learnt Mystery Skill of Magical Attack.");
					}

		}

		else if (Quest.GetIndex() == MystDefQ){
			int CheckGrade = 0;
			int GetGrade = IPlayer.GetBuffValue(BuffNames::MystDef);
			if (IPlayer.GetLevel() >= MystLevelMax)
				CheckGrade = 30;
			else
				CheckGrade = IPlayer.GetLevel() - MystLevel + 1;

					IPlayer.SaveBuff(BuffNames::MystDef, BuffNames::BuffTime, CheckGrade, 0, 0);
					IPlayer.SetBuffIcon(-2, -1, MystDefS, MystDefS);

					if (CheckGrade){
						IPlayer.AddDef(10 * CheckGrade);
						IPlayer.BoxMsg("You have learnt Mystery Skill of Defense.");
					}
					else {
						IPlayer.AddDef(10);
						IPlayer.BoxMsg("You have learnt Mystery Skill of Defense.");
					}

		}

		else if (Quest.GetIndex() == MystHPQ){
			int CheckGrade = 0;
			int GetGrade = IPlayer.GetBuffValue(BuffNames::MystHP);
			if (IPlayer.GetLevel() >= MystLevelMax)
				CheckGrade = 30;
			else
				CheckGrade = IPlayer.GetLevel() - MystLevel + 1;

					IPlayer.SaveBuff(BuffNames::MystHP, BuffNames::BuffTime, CheckGrade, 0, 0);
					IPlayer.SetBuffIcon(-2, -1, MystHPS, MystHPS);

					if (CheckGrade){
						IPlayer.IncreaseMaxHp(250 * CheckGrade);
						IPlayer.BoxMsg("You have learnt Mystery Skill of Health Point.");
					}
					else {
						IPlayer.IncreaseMaxHp(250);
						IPlayer.BoxMsg("You have learnt Mystery Skill of Health Point.");
					}
		}

		else if (Quest.GetIndex() == MystEVAQ){
			int CheckGrade = 0;
			int GetGrade = IPlayer.GetBuffValue(BuffNames::MystEVA);
			if (IPlayer.GetLevel() >= MystLevelMax)
				CheckGrade = 30;
			else
				CheckGrade = IPlayer.GetLevel() - MystLevel + 1;

					IPlayer.SaveBuff(BuffNames::MystEVA, BuffNames::BuffTime, CheckGrade, 0, 0);
					IPlayer.SetBuffIcon(-2, -1, MystEVAS, MystEVAS);

					if (CheckGrade){
						IPlayer.AddEva(2 * CheckGrade);
						IPlayer.BoxMsg("You have learnt Mystery Skill of Evasion Point.");
					}
					else {
						IPlayer.AddEva(2);
						IPlayer.BoxMsg("You have learnt Mystery Skill of Evasion Point.");
					}
		}


		else if (Quest.GetIndex() == MystOTPQ){
			int CheckGrade = 0;
			int GetGrade = IPlayer.GetBuffValue(BuffNames::MystOTP);
			if (IPlayer.GetLevel() >= MystLevelMax)
				CheckGrade = 30;
			else
				CheckGrade = IPlayer.GetLevel() - MystLevel + 1;

					IPlayer.SaveBuff(BuffNames::MystOTP, BuffNames::BuffTime, CheckGrade, 0, 0);
					IPlayer.SetBuffIcon(-2, -1, MystOTPS, MystOTPS);

					if (CheckGrade){
						IPlayer.AddOTP(2 * CheckGrade);
						IPlayer.BoxMsg("You have learnt Mystery Skill of On Target Point.");
					}
					else {
						IPlayer.AddOTP(2);
						IPlayer.BoxMsg("You have learnt Mystery Skill of On Target Point.");
					}
		}
	}


	if (IPlayer.IsOnline() && Quest.GetIndex() == (MysteryQuest % 65536))
	{
		if (!MysteryEnable) {
			IPlayer.SystemMessage("Mystery skills are disabled", TEXTCOLOR_RED);
			return;
		}

		int OTP = IPlayer.GetSkillPointer(87);
		int EVA = IPlayer.GetSkillPointer(88);
		int DEF = IPlayer.GetSkillPointer(89);

		if (!OTP && !EVA && !DEF)
		{
			IPlayer.SystemMessage("You do not have mystery skill to reset.",TEXTCOLOR_RED);
			return;
		}

		int MysteryItemCheck = CPlayer::FindItem(IPlayer.GetOffset(),MysteryResetItem,1);

		if (!MysteryItemCheck)
		{
			IPlayer.SystemMessage("You do not have Stone of chance for Mystery Skill to reset.",TEXTCOLOR_RED);
			return;
		}

		if (IPlayer.IsOnline() && OTP)
		{
			IPlayer.RemoveOTP(8 * *(DWORD*)(OTP + 8));
			*(DWORD*)(OTP + 8) = 0;
			CPlayer::Write(IPlayer.GetOffset(),11,"bb",85,0);
			CDBSocket::Write(22,"dbbw",IPlayer.GetPID(),*(DWORD*)(OTP + 4),*(DWORD*)(OTP + 8),*(DWORD*)((int)IPlayer.GetOffset() + 548));
			*(DWORD*)((int)IPlayer.GetOffset() + 4 * *(DWORD*)(OTP +4) + 632) = 0;
			Undefined::DeleteSkill(OTP);
		}

		if (IPlayer.IsOnline() && EVA)
		{
			IPlayer.RemoveEva(6 * *(DWORD*)(EVA + 8));
			*(DWORD*)(EVA + 8) = 0;
			CPlayer::Write(IPlayer.GetOffset(),11,"bb",86,0);
			CDBSocket::Write(22,"dbbw",IPlayer.GetPID(),*(DWORD*)(EVA + 4),*(DWORD*)(EVA + 8),*(DWORD*)((int)IPlayer.GetOffset() + 548));
			*(DWORD*)((int)IPlayer.GetOffset() + 4 * *(DWORD*)(EVA +4) + 632) = 0;
			Undefined::DeleteSkill(EVA);
		}

		if (IPlayer.IsOnline() && DEF)
		{
			IPlayer.RemoveDef(24 + (7 * *(DWORD*)(DEF + 8)));
			*(DWORD*)(DEF + 8) = 0;
			CPlayer::Write(IPlayer.GetOffset(),11,"bb",87,0);
			CDBSocket::Write(22,"dbbw",IPlayer.GetPID(),*(DWORD*)(DEF + 4),*(DWORD*)(DEF + 8),*(DWORD*)((int)IPlayer.GetOffset() + 548));
			*(DWORD*)((int)IPlayer.GetOffset() + 4 * *(DWORD*)(DEF +4) + 632) = 0;
			Undefined::DeleteSkill(DEF);
		}

		if(!(*(int (__thiscall **)(DWORD, void *, signed int, signed int))(*(DWORD*)MysteryItemCheck + 120))(MysteryItemCheck,IPlayer.GetOffset(),9,-1))
			CPlayer::_OutOfInven(IPlayer.GetOffset(), MysteryItemCheck);

		return;
	}

	CQuest::Run(QuestOffset, PlayerOffset);
}