int __fastcall ItemUse(void *ItemOffset, void *edx, int PlayerOffset)
{
	IItem Item(ItemOffset);
	IChar IPlayer((void*)PlayerOffset);

	if (!Item.Exists() || !IPlayer.IsOnline())
		return 0;

	int MapX = IPlayer.GetX() >> 13;
	int MapY = IPlayer.GetY() >> 13;

	if (IPlayer.IsOnline() && (ItemDisable.count(Item.CheckIndex()*(IPlayer.GetMap() + 1000)) || ItemDisable.count(Item.CheckIndex()*(((MapX)+1000)*((MapY)+100))) || ItemDisable.count(Item.CheckIndex() * 1255))) {
		IPlayer.SystemMessage("This item usage has been temporarly disabled", TEXTCOLOR_RED);
		return Item.GetAmount();
	}

	if (IPlayer.IsOnline() && ItemLimits.count(Item.CheckIndex())) {
		ItemLimit itemLimit = ItemLimits.find(Item.CheckIndex())->second;

		int KeyIndex = (IPlayer.GetPID() * 1000) + Item.CheckIndex();

		ItemLimitConf itemL = ItemLimitUsage.count(KeyIndex) ? ItemLimitUsage.findValue(KeyIndex) : ItemLimitConf();

		int TimeLeft = itemL.Time - (int)time(0);

		int CalcLeftTime = TimeLeft > 0 ? TimeLeft : itemLimit.Time;

		int Day = (CalcLeftTime / 86400);
		int Hour = ((CalcLeftTime / 3600) % 24);
		int Minute = ((CalcLeftTime / 60) % 60);
		int Second = (CalcLeftTime % 60);

		if (TimeLeft <= 0) {
			itemL.Time = (int)time(0) + itemLimit.Time;
			itemL.Usage = 0;
		}
		else if (itemLimit.Usage <= itemL.Usage) {
			IPlayer.SystemMessage("Exceeded the maximum limit of item usage. You can use it again in " + Int2String(Day) + " Days " + Int2String(Hour) + " Hours " + Int2String(Minute) + " Minutes " + Int2String(Second) + " Seconds.", TEXTCOLOR_RED);
			return Item.GetAmount();
		}

		itemL.Usage++;
		ItemLimitUsage.replaceInsert(KeyIndex, itemL);

		IPlayer.SystemMessage("This item's usage is limited to " + Int2String(itemLimit.Usage) + " usages, you have used it " + Int2String(itemL.Usage) + " times untill now.", TEXTCOLOR_YELLOW);

		IPlayer.SystemMessage("Your limit for this item will reset in " + Int2String(Day) + " Days " + Int2String(Hour) + " Hours " + Int2String(Minute) + " Minutes " + Int2String(Second) + " Seconds.", TEXTCOLOR_GENERAL);

		std::string Datko = "./Database/ItemLimit.db";
		std::string Datko1 = "./Database/ItemLimitTemp.db";
		string line;

		ifstream fin;
		fin.open(Datko.c_str());
		ofstream temp;
		temp.open(Datko1.c_str());
		bool edited = false;
		while (getline(fin, line))
		{
			int Keya = 0;
			if (sscanf(line.c_str(), "(itemLimit (Key %d)", &Keya) == 1) {
				if (Keya == KeyIndex) {
					temp << "(itemLimit (Key " + Int2String(KeyIndex) + ")(Usage " + Int2String(itemL.Usage) + ")(Time " + Int2String(itemL.Time) + "))" << endl;
					edited = true;
				}
				else
					temp << line << endl;
			}
		}

		temp.close();
		fin.close();
		remove(Datko.c_str());
		rename(Datko1.c_str(), Datko.c_str());

		if (!edited) {
			std::string Datko = "./Database/ItemLimit.db";
			std::fstream DGkLOG;
			DGkLOG.open(Datko, std::fstream::in | std::fstream::out | std::fstream::app);
			DGkLOG << "(itemLimit (Key " + Int2String(KeyIndex) + ")(Usage " + Int2String(itemL.Usage) + ")(Time " + Int2String(itemL.Time) + "))" << std::endl;
			DGkLOG.close();
		}
	}


	if (IPlayer.IsOnline() && AreaCert.count(Item.CheckIndex())) {

		Certificates area = AreaCert.find(Item.CheckIndex())->second;
		int buffID = ((Item.CheckIndex() * 2) + area.Map);
		int Time = area.Time;
		int Exp = area.Exp;
		int sbKey = area.SBKey;
		int sbMsg = area.SBMsg;
		int timeInMin = Time / 60;

		if (!IPlayer.IsBuff(buffID)) {
			IPlayer.SaveBuff(buffID, Time, Exp, sbMsg, sbKey);
			IPlayer.SystemMessage("Area Certificate applied for " + Int2String(timeInMin) + " minutes.", LIME_GREEN);

			(*(int(__thiscall **)(DWORD, void *, signed int, signed int))(*(DWORD*)ItemOffset + 120))((int)ItemOffset, IPlayer.GetOffset(), 9, -1);
			return Item.GetAmount();
		}
		else {
			int remainingTime = IPlayer.GetBuffRemain(buffID);
			IPlayer.UpdateSavedBuff(buffID, remainingTime + Time, Exp, sbMsg, sbKey);
			IPlayer.SystemMessage("Area Certificate extended by " + Int2String(timeInMin) + " minutes.", LIME_GREEN);

			(*(int(__thiscall **)(DWORD, void *, signed int, signed int))(*(DWORD*)ItemOffset + 120))((int)ItemOffset, IPlayer.GetOffset(), 9, -1);
			return Item.GetAmount();
		}
		return Item.GetAmount();
	}
	//Calls
	if (IPlayer.IsOnline() && BuffCheck.count(Item.CheckIndex()))
	{

		if (IPlayer.GetLevel() >= BuffCheck.find(Item.CheckIndex())->second.MinLevel&&IPlayer.GetLevel() <= BuffCheck.find(Item.CheckIndex())->second.MaxLevel&& BuffCheck.find(Item.CheckIndex())->second.Call == Item.CheckIndex())
		{
			if (IPlayer.IsBuff(70) && IPlayer.IsBuff(71) && IPlayer.IsBuff(72) && IPlayer.IsBuff(73) && IPlayer.IsBuff(74) && IPlayer.IsBuff(28))
			{
				IPlayer.SystemMessage("You Already have Call's", TEXTCOLOR_RED);
				return Item.GetAmount();
			}
			IPlayer.Buff(70, 1800, BuffCheck.find(Item.CheckIndex())->second.LightningDefense);
			IPlayer.Buff(71, 1800, BuffCheck.find(Item.CheckIndex())->second.IceDefense);
			IPlayer.Buff(72, 1800, BuffCheck.find(Item.CheckIndex())->second.FireDefense);
			IPlayer.Buff(73, 1800, BuffCheck.find(Item.CheckIndex())->second.OTPCall);
			IPlayer.Buff(74, 1800, BuffCheck.find(Item.CheckIndex())->second.PhysicalAttack);
			IPlayer.Buff(28, 1800, BuffCheck.find(Item.CheckIndex())->second.CallofDefense);
			if (BuffCheck.find(Item.CheckIndex())->second.Delete)
				(*(int(__thiscall **)(DWORD, void *, signed int, signed int))(*(DWORD*)ItemOffset + 120))((int)ItemOffset, IPlayer.GetOffset(), 9, -1);

			return Item.GetAmount();
		}
		else{
			IPlayer.SystemMessage(BuffCheck.find(Item.CheckIndex())->second.LimitMsg.c_str(), TEXTCOLOR_RED);
			return Item.GetAmount();
		}
	}

	if (IPlayer.IsOnline() && BuffDisableCheck.count(Item.CheckIndex()))
	{
		BuffDisable buffdisable = BuffDisableCheck.find(Item.CheckIndex())->second;

		for (int i = 0; i < buffdisable.BuffDisableID.size(); i++){
			int disableID = String2Int(buffdisable.BuffDisableID[i]);
			if (IPlayer.IsBuff(disableID)){
				IPlayer.SystemMessage("Alternative Buff is already in use.", TEXTCOLOR_RED);
				return Item.GetAmount();
			}
		}
	}


	if (IPlayer.IsOnline() && BuffRemoveCheck.count(Item.CheckIndex()))
	{
		BuffDisable buffRemove = BuffRemoveCheck.find(Item.CheckIndex())->second;

		for (int i = 0; i < buffRemove.BuffDisableID.size(); i++){
			int removeID = String2Int(buffRemove.BuffDisableID[i]);
			if (IPlayer.IsBuff(removeID)){
				IPlayer.RemoveSavedBuff(removeID);
			}
		}

	}

	if (IPlayer.IsOnline() && BuffMakerCheck.count(Item.CheckIndex()))
	{
		BuffMaker buffMaker = BuffMakerCheck.find(Item.CheckIndex())->second;

		int MinPhyAttackGet = IPlayer.GetMinPhyAttack(), MinMagAttack = IPlayer.GetMinMagAttack();

		if (!IPlayer.IsBuff(buffMaker.BuffID))
		{
			int TotalAmounts = buffMaker.altBuff.size();
			int buffAmounts = 0;

			for (int i = 0; i < buffMaker.altBuff.size(); i++)
			{
				int altBuffID = String2Int(buffMaker.altBuff[i]);
				if (IPlayer.IsBuff(altBuffID))
					buffAmounts++;
			}

			if (TotalAmounts == buffAmounts)
			{
				IPlayer.SystemMessage("All Buffs are already in use.", TEXTCOLOR_RED);
				return Item.GetAmount();
			}

			for (int i = 0; i < buffMaker.altBuff.size(); i++)
			{
				int altBuffID = String2Int(buffMaker.altBuff[i]);
				if (IPlayer.IsBuff(altBuffID))
					IPlayer.RemoveSavedBuff(altBuffID);
			}

			if (IPlayer.GetLevel() >= buffMaker.MinLevel && IPlayer.GetLevel() <= buffMaker.MaxLevel && buffMaker.Maker == Item.CheckIndex())
			{
				if (buffMaker.BuffIcon == "true")
					IPlayer.SetBuffIcon(buffMaker.Time * 1000, 0, 0, buffMaker.Sys_name);

				if (buffMaker.MinAttack){
					IPlayer.AddMinAttack((MinPhyAttackGet * buffMaker.MinAttack) / 100);
					IPlayer.SaveBuff(BuffNames::BuffPhyAtk + (buffMaker.BuffID / 2), buffMaker.Time, ((MinPhyAttackGet * buffMaker.MinAttack) / 100), 0, 0);
				}
				if (buffMaker.MaxAttack){
					IPlayer.AddMaxAttack((MinMagAttack * buffMaker.MaxAttack) / 100);
					IPlayer.SaveBuff(BuffNames::BuffMagAtk + (buffMaker.BuffID / 2), buffMaker.Time, ((MinMagAttack * buffMaker.MaxAttack) / 100), 0, 0);
				}
				//	IPlayer.AddMaxAttack((MinMagAttack * buffMaker.MaxAttack) / 100);
				IPlayer.AddHp(buffMaker.Hp);
				IPlayer.AddStr(buffMaker.Str);
				IPlayer.AddInt(buffMaker.Int);
				IPlayer.AddWis(buffMaker.Wis);
				IPlayer.AddAgi(buffMaker.Agi);
				IPlayer.AddOTP(buffMaker.OTP);
				IPlayer.AddEva(buffMaker.Eva);
				IPlayer.AddDef(buffMaker.Def);
				IPlayer.AddLightning_Resistance(buffMaker.Lightning_Resistance);
				IPlayer.AddIce_Resistance(buffMaker.Ice_Resistance);
				IPlayer.AddFire_Resistance(buffMaker.Fire_Resistance);
				IPlayer.AddAbsorb(buffMaker.Absorb);
				IPlayer.IncreaseCritRate(buffMaker.CritRate);
				IPlayer.IncreaseCritDamage(buffMaker.CritDamage);
				IPlayer.IncreaseMaxMp(buffMaker.MaxMp);
				IPlayer.IncreaseMaxHp(buffMaker.MaxHp);
				IPlayer.IncreaseEBRate(buffMaker.EBRate);

				if (buffMaker.save == "true")
					IPlayer.SaveBuff(buffMaker.BuffID, buffMaker.Time);
				else
					IPlayer.Buff(buffMaker.BuffID, buffMaker.Time, 1);
				IPlayer.Buff(buffMaker.BuffID + 1000, buffMaker.Time, 1);

				if (buffMaker.Delete)
					(*(int(__thiscall **)(DWORD, void *, signed int, signed int))(*(DWORD*)ItemOffset + 120))((int)ItemOffset, IPlayer.GetOffset(), 9, -1);

				return Item.GetAmount();
			}
			else{
				IPlayer.SystemMessage(buffMaker.LimitMsg.c_str(), TEXTCOLOR_RED);
				return Item.GetAmount();
			}
		}
		else{
			IPlayer.SystemMessage("Buff already in use", TEXTCOLOR_RED);
			return Item.GetAmount();
		}

	}


	if (IPlayer.IsOnline() && ItemQuestRepeats.count(Item.CheckIndex())) {
		ItemQuestRepeat iRepeat = ItemQuestRepeats.find(Item.CheckIndex())->second;
		for (int i = 0; i < iRepeat.Quests.size(); i++) {
			int Quest = iRepeat.Quests[i];
			long MIndex = uniqueKey((Quest * 10) + 1, IPlayer.GetPID());
			if (PlayerTimedQuest.count(MIndex)) {
				PlayerTimedQuest.erase(MIndex);

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
						if (Type != MIndex)
							temp << line << endl;
					}
				}
				temp.close();
				fin.close();
				remove("./Database/TimedQuest.db");
				rename("./Database/tempQ.txt", "./Database/TimedQuest.db");
			}
			int Repeat = IPlayer.GetBuffValue((BuffNames::DailyRepeatBegin + Quest) % BuffNames::DailyRepeatEnd);
			if (Repeat > 0)
				IPlayer.UpdateBuff((BuffNames::DailyRepeatBegin + Quest) % BuffNames::DailyRepeatEnd, BuffNames::BuffTime, Repeat - 1);
		}

		IPlayer.SystemMessage("Your quest limits have been unlocked.", TEXTCOLOR_GREEN);

		if (!iRepeat.Permanent)
			(*(int(__thiscall **)(DWORD, void *, signed int, signed int))(*(DWORD*)ItemOffset + 120))((int)ItemOffset, IPlayer.GetOffset(), *(DWORD *)(*(DWORD *)((int)ItemOffset + 40) + 156) != 0 ? 43 : 9, -1);
		return Item.GetAmount();
	}

	if (IPlayer.IsOnline() && Item.CheckIndex() == 3387)
	{
		if (GetInventorySize(PlayerOffset, 0) < 60)
		{
			int xItem = CItem::CreateItem(3384, 0, 1, -1);

			if (xItem)
			{
				IItem IItem((void*)xItem);

				if (CPlayer::_InsertItem(IPlayer.GetOffset(), 27, xItem) != 1) {
					CBase::Delete((void*)xItem);
					return Item.GetAmount();
				}

				int Value = CTools::Rate(0, 12);
				int Add = HaninLow.count(Value) ? CTools::Rate(HaninLow.find(Value)->second.Min, HaninLow.find(Value)->second.Max) : 30;
				CPlayer::Write(IPlayer.GetOffset(), 193, "ddd", IItem.GetIID(), Value, Add);
				itemStat.Enter();
				GetItemStat[IItem.GetIID()] = Value + (Add * 1000);
				itemStat.Leave();

				CDBSocket::Write(90, "dd", Value + (Add * 1000), IItem.GetIID());
			}
		}
		else {
			CPlayer::Write(IPlayer.GetOffset(), 67, "b", 40);
			return Item.GetAmount();
		}

		(*(int(__thiscall **)(DWORD, void *, signed int, signed int))(*(DWORD*)ItemOffset + 120))((int)ItemOffset, IPlayer.GetOffset(), *(DWORD *)(*(DWORD *)((int)ItemOffset + 40) + 156) != 0 ? 43 : 9, -1);
		return Item.GetAmount();
	}

	if (IPlayer.IsOnline() && Item.CheckIndex() == 3104 && IPlayer.IsBuff(334))
		return Item.GetAmount();

	if (IPlayer.IsOnline() && Item.CheckIndex() == 3104 && !IPlayer.IsBuff(334))
	{
		IPlayer.Buff(334, 3, 0);
		return Item.GetAmount();
	}

	if (IPlayer.IsOnline() && isItemRiding(Item.CheckIndex()) && CChar::IsGState((int)IPlayer.GetOffset(), 4))
		return Item.GetAmount();

	if (IPlayer.IsOnline() && isItemRiding(Item.CheckIndex()) && CChar::IsGState((int)IPlayer.GetOffset(), 512))
		return Item.GetAmount();

	if (IPlayer.IsOnline() && isItemRiding(Item.CheckIndex()) && (IPlayer.IsBuff(18) || IPlayer.IsBuff(19) || IPlayer.IsBuff(313) || IPlayer.IsBuff(329)))
		return Item.GetAmount();

	if (IPlayer.IsOnline() && isItemRiding(Item.CheckIndex()) && !IPlayer.IsBuff(349))
		return Item.GetAmount();

	if (IPlayer.IsOnline() && isItemRiding(Item.CheckIndex()) && IPlayer.IsBuff(349))
		return Item.GetAmount();

	if (IPlayer.IsOnline() && TaskQuests.count(Item.CheckIndex())) {
		TaskQ task = TaskQuests.find(Item.CheckIndex())->second;

		std::vector<std::string> Items_ = explode(",", task.Items);
		std::vector<std::string> iAmounts_ = explode(",", task.Amount);
		std::vector<std::string> rItems_ = explode(",", task.Require);
		std::vector<std::string> rAmounts_ = explode(",", task.RequireAmount);
		if (rItems_.size() == rAmounts_.size() && Items_.size() == iAmounts_.size()) {
			for (int i = 0; i < rItems_.size(); i++) {
				int Index = String2Int(rItems_[i]);
				int Amount = String2Int(rAmounts_[i]);

				if (Index && Amount && Index != Item.CheckIndex() && !CPlayer::_FindItem(PlayerOffset, Index, Amount)){
					IPlayer.SystemMessage("You dont have the required amount of items!", TEXTCOLOR_RED);
					return Item.GetAmount();
				}
			}

			for (int i = 0; i < rItems_.size(); i++) {
				int Index = String2Int(rItems_[i]);
				int Amount = String2Int(rAmounts_[i]);
				if (Index && Amount && Index != Item.CheckIndex()) {
					int Removing = CPlayer::_FindItem(PlayerOffset, Index, Amount);
					if (Removing) {
						if (!(*(int(__thiscall **)(DWORD, void *, signed int, signed int))(*(DWORD*)Removing + 120))((int)Removing, IPlayer.GetOffset(), 9, -Amount))
							CPlayer::_OutOfInven((void*)PlayerOffset, Removing);
					}
				}
			}

			for (int i = 0; i < Items_.size(); i++) {
				int Index = String2Int(Items_[i]);
				int Amount = String2Int(iAmounts_[i]);
				if (Index && Amount)
					IPlayer.InsertItem(Index, 0, Amount);
			}
			if (task.Honor || task.Reward)
				IPlayer.SetHonor(task.Honor, task.Reward, 0, 0, 0, 0, 0, 0, 0, 0);
			if (task.HTML)
				IPlayer.OpenHTML(task.HTML);
		}
		(*(int(__thiscall **)(DWORD, void *, signed int, signed int))(*(DWORD*)ItemOffset + 120))((int)ItemOffset, IPlayer.GetOffset(), *(DWORD *)(*(DWORD *)((int)ItemOffset + 40) + 156) != 0 ? 43 : 9, -1);

		return Item.GetAmount();
	}

	if (IPlayer.IsOnline() && ItemNPC.count(Item.CheckIndex()))
	{
		if (NPCIDs.count(ItemNPC.find(Item.CheckIndex())->second)) {
			int NPC = NPCIDs.find(ItemNPC.find(Item.CheckIndex())->second)->second;
			if (NPC)
				CPlayer::Write((void*)PlayerOffset, 52, "dwbdddwId", *(DWORD *)(NPC + 28), summonindex, *(DWORD *)(NPC + 452), IPlayer.GetX(), IPlayer.GetY(), IPlayer.GetZ(), *(DWORD *)(NPC + 348), (unsigned __int64)*(DWORD *)(NPC + 280), 0);
			(*(int(__thiscall **)(DWORD, void *, signed int, signed int))(*(DWORD*)ItemOffset + 120))((int)ItemOffset, IPlayer.GetOffset(), *(DWORD *)(*(DWORD *)((int)ItemOffset + 40) + 156) != 0 ? 43 : 9, -1);
		}

		return Item.GetAmount();
	}

	if (IPlayer.IsOnline() && ItemNPCSummoned.count(Item.CheckIndex()))
	{
		SummonNPC npc = ItemNPCSummoned.find(Item.CheckIndex())->second;
		NPCID--;

		CChar::WriteInSight(IPlayer.GetOffset(), 52, "dwbdddwId", NPCID, npc.NPC, npc.Model, IPlayer.GetX(), IPlayer.GetY(), IPlayer.GetZ(), 1, (unsigned __int64)0, 0);

		npc.X = IPlayer.GetX();
		npc.Y = IPlayer.GetY();
		npc.Z = IPlayer.GetZ();
		npc.Time = npc.Time + (int)time(0);

		npcLock.Enter();
		NPCSummoned.insert(std::pair<int, SummonNPC>(NPCID, npc));
		npcLock.Leave();

		(*(int(__thiscall **)(DWORD, void *, signed int, signed int))(*(DWORD*)ItemOffset + 120))((int)ItemOffset, IPlayer.GetOffset(), *(DWORD *)(*(DWORD *)((int)ItemOffset + 40) + 156) != 0 ? 43 : 9, -1);

		return Item.GetAmount();
	}

	if (IPlayer.IsOnline() && BufferCheck.count(Item.CheckIndex()))
	{
		if (IPlayer.GetLevel() <= BufferCheck.find(Item.CheckIndex())->second.Limit)
		{
			double Buff = BufferCheck.find(Item.CheckIndex())->second.Grade;
			int cd = BufferCheck.find(Item.CheckIndex())->second.cd;
			double Refine = BufferCheck.find(Item.CheckIndex())->second.Grade;

			if (IPlayer.IsBuff(1625))
			{
				IPlayer.SystemMessage("You need to wait " + Int2String(IPlayer.GetBuffRemain(1625)) + " seconds to re-use buff.", TEXTCOLOR_RED);
				return Item.GetAmount();
			}
			if (cd)
				IPlayer.Buff(1625, cd, 1);


			if (Buff == 3) Buff = 2.75;
			if (Refine == 3) Refine = 5.5;
			IPlayer.Buff(48, 1800, 8 * Buff + 3);
			IPlayer.Buff(50, 1800, 8 * Buff + 3);
			IPlayer.Buff(47, 1800, 8 * Buff + 3);
			IPlayer.Buff(49, 1800, 8 * Buff + 3);
			IPlayer.Buff(46, 1800, 8 * Buff + 3);
			IPlayer.Buff(36, 1800, 8 * Refine + 16);
			CChar::CancelAllBuff(IPlayer.GetOffset(), 37);
			int AddBuff = CBuff::CreateBuff(37, 1800, 30 * Buff + 5, 20 * Buff + 5);
			(*(int(__thiscall **)(int, int))(*(DWORD *)PlayerOffset + 180))(PlayerOffset, AddBuff);
			IPlayer.Buff(12, 1800, BufferCheck.find(Item.CheckIndex())->second.Speed);
		}
		else {
			IPlayer.SystemMessage("Your level is too high!", TEXTCOLOR_RED);
			return Item.GetAmount();
		}

		if (BufferCheck.find(Item.CheckIndex())->second.Delete)
			(*(int(__thiscall **)(DWORD, void *, signed int, signed int))(*(DWORD*)ItemOffset + 120))((int)ItemOffset, IPlayer.GetOffset(), *(DWORD *)(*(DWORD *)((int)ItemOffset + 40) + 156) != 0 ? 43 : 9, -1);

		return Item.GetAmount();
	}

	if (IPlayer.IsOnline() && ItemQuest.count(Item.CheckIndex())) {
		CIOCriticalSection::Leave((void*)((char *)PlayerOffset + 1020));

		CQuest::Start(ItemQuest.find(Item.CheckIndex())->second, (int)IPlayer.GetOffset());

		CIOCriticalSection::Enter((void*)((int)PlayerOffset + 1020));

		return Item.GetAmount() ? Item.GetAmount() : 1;
	}
	/*
	if (IPlayer.IsOnline() && Item.CheckIndex() == 6725) {
	//if(IPlayer.IsBuff(30)) IPlayer.CancelBuff(30);
	if (IPlayer.IsBuff(BuffNames::expstone)) {
	IPlayer.SystemMessage(thisServerName + " Stone of EXP is already in use!", TEXTCOLOR_YELLOW);
	return Item.GetAmount();
	}
	IPlayer.Buff(BuffNames::expstone, BuffNames::BuffTime, 0);
	IPlayer.SetBuffIcon(1296000 * 1000, 0, 8014, 8014);
	(*(int(__thiscall **)(DWORD, void *, signed int, signed int))(*(DWORD*)ItemOffset + 120))((int)ItemOffset, IPlayer.GetOffset(), *(DWORD *)(*(DWORD *)((int)ItemOffset + 40) + 156) != 0 ? 43 : 9, -1);

	return Item.GetAmount();
	}
	*/
	if (IPlayer.IsOnline() && Item.CheckIndex() == 6726) {
		//if(IPlayer.IsBuff(32)) IPlayer.CancelBuff(32);
		if (IPlayer.IsBuff(BuffNames::fish)) {
			IPlayer.SystemMessage(thisServerName + " Stone of Fish is already in use!", TEXTCOLOR_YELLOW);
			return Item.GetAmount();
		}
		IPlayer.SaveBuff(BuffNames::fish, 86400, 0, 8015, 1074);
		(*(int(__thiscall **)(DWORD, void *, signed int, signed int))(*(DWORD*)ItemOffset + 120))((int)ItemOffset, IPlayer.GetOffset(), *(DWORD *)(*(DWORD *)((int)ItemOffset + 40) + 156) != 0 ? 43 : 9, -1);

		return Item.GetAmount();
	}

	if (IPlayer.IsOnline() && SingleBufferCheck.count(Item.CheckIndex()) && SingleBufferCheck.find(Item.CheckIndex())->second.Index == Item.CheckIndex())
	{
		if (SingleBufferCheck.find(Item.CheckIndex())->second.Type == 37) {
			CChar::CancelAllBuff(IPlayer.GetOffset(), 37);
			int AddBuff = CBuff::CreateBuff(SingleBufferCheck.find(Item.CheckIndex())->second.Type, 1800, 30 * (SingleBufferCheck.find(Item.CheckIndex())->second.Grade) + 5, 20 * (SingleBufferCheck.find(Item.CheckIndex())->second.Grade) + 5);
			(*(int(__thiscall **)(int, int))(*(DWORD *)PlayerOffset + 180))(PlayerOffset, AddBuff);
		}
		else if (SingleBufferCheck.find(Item.CheckIndex())->second.Type == 12) {
			IPlayer.Buff(SingleBufferCheck.find(Item.CheckIndex())->second.Type, 1800, 30 * (SingleBufferCheck.find(Item.CheckIndex())->second.Grade));
		}
		else {
			IPlayer.Buff(SingleBufferCheck.find(Item.CheckIndex())->second.Type, 1800, 8 * (SingleBufferCheck.find(Item.CheckIndex())->second.Grade) + 3);
		}

		if (SingleBufferCheck.find(Item.CheckIndex())->second.Delete)
			(*(int(__thiscall **)(DWORD, void *, signed int, signed int))(*(DWORD*)ItemOffset + 120))((int)ItemOffset, IPlayer.GetOffset(), *(DWORD *)(*(DWORD *)((int)ItemOffset + 40) + 156) != 0 ? 43 : 9, -1);

		return Item.GetAmount();
	}

	if (IPlayer.IsOnline() && (Item.CheckIndex() >= 187 && Item.CheckIndex() <= 196) || Item.CheckIndex() == 484 || Item.CheckIndex() == 485 || (Item.CheckIndex() >= 2157 && Item.CheckIndex() <= 2160))
	{
		if ((IPlayer.IsBuff(160) || IPlayer.IsBuff(180) || IPlayer.IsBuff(179) || IPlayer.IsBuff(161) || IPlayer.IsBuff(BuffNames::PTVsPTBlue) || IPlayer.IsBuff(BuffNames::PTVsPTRed) || IPlayer.IsBuff(162) || IPlayer.IsBuff(163) || IPlayer.IsBuff(170) || IPlayer.IsBuff(171) || IPlayer.IsBuff(373) || IPlayer.IsBuff(374) || IPlayer.IsBuff(902) || IPlayer.IsBuff(903) || IPlayer.IsBuff(BuffNames::LMS) || IPlayer.IsBuff(BuffNames::TriangularType) || IPlayer.GetMap() == SVMap))
		{
			IPlayer.SystemMessage("You can not teleport while in battle.", TEXTCOLOR_RED);
			return Item.GetAmount();
		}
	}

	if (IPlayer.IsOnline() && Item.CheckIndex() == ScrollOfInv){

		if (IPlayer.GetBuffRemain(1950))
		{
			IPlayer.SystemMessage("You can use scroll in " + Int2String(IPlayer.GetBuffRemain(1950)) + " seconds.", TEXTCOLOR_RED);
			return Item.GetAmount();
		}
		if (IPlayer.GetPID() != IPlayer.GetGID())
		{
			IPlayer.SystemMessage("Item can be used only by Guild Leader.", TEXTCOLOR_RED);
			return Item.GetAmount();
		}
		else{
			IPlayer.Buff(1950, 10, 1);
			(*(int(__thiscall **)(DWORD, void *, signed int, signed int))(*(DWORD*)ItemOffset + 120))((int)ItemOffset, IPlayer.GetOffset(), *(DWORD *)(*(DWORD *)((int)ItemOffset + 40) + 156) != 0 ? 43 : 9, -1);
			return Item.GetAmount();
		}
	}

	if (IPlayer.IsOnline() && Item.CheckIndex() == ScrollOfMovingPL){

		int leaderx = 0, leadery = 0, leaderz = 0;
		if (IPlayer.GetBuffRemain(1951))
		{
			int Day = (IPlayer.GetBuffRemain(1951) / 86400);
			int Hour = ((IPlayer.GetBuffRemain(1951) / 3600) % 24);
			int Minute = ((IPlayer.GetBuffRemain(1951) / 60) % 60);
			int Second = (IPlayer.GetBuffRemain(1951) % 60);
			IPlayer.SystemMessage("You can use scroll in " + Int2String(Minute) + " minutes " + Int2String(Second) + " seconds.", TEXTCOLOR_RED);
			return Item.GetAmount();
		}
		if (IPlayer.GetPID() == IPlayer.GetGID())
		{
			IPlayer.SystemMessage("Item can not be used by Guild Leader.", TEXTCOLOR_RED);
			return Item.GetAmount();
		}
		else{
			CIOCriticalSection::Enter((void*)0x4e2078);
			CIOCriticalSection::Enter((void*)0x4e2098);
			CLink::MoveTo((void*)0x4e200c, (int)0x4e2004);
			CIOCriticalSection::Leave((void*)0x4e2098);
			for (DWORD i = *(DWORD*)0x4E2004; i != 0x4E2004; i = *(DWORD*)i)
			{
				IChar Online((void*)(i - 428));
				if (Online.GetPID() == IPlayer.GetGID())
				{
					leaderx = Online.GetX();
					leadery = Online.GetY();
					leaderz = Online.GetZ();
				}
			}
			CIOCriticalSection::Leave((void*)0x4e2078);

			IPlayer.Teleport(leaderx, leadery, leaderz);
			IPlayer.Buff(1951, 300, 1);
			(*(int(__thiscall **)(DWORD, void *, signed int, signed int))(*(DWORD*)ItemOffset + 120))((int)ItemOffset, IPlayer.GetOffset(), *(DWORD *)(*(DWORD *)((int)ItemOffset + 40) + 156) != 0 ? 43 : 9, -1);
			return Item.GetAmount();
		}
	}

	if (IPlayer.IsOnline() && ItemWebsite.count(Item.CheckIndex())) {
		IPlayer.OpenWebsite(ItemWebsite.find(Item.CheckIndex())->second.URL);
		if (ItemWebsite.find(Item.CheckIndex())->second.remove)
			(*(int(__thiscall **)(DWORD, void *, signed int, signed int))(*(DWORD*)ItemOffset + 120))((int)ItemOffset, IPlayer.GetOffset(), *(DWORD *)(*(DWORD *)((int)ItemOffset + 40) + 156) != 0 ? 43 : 9, -1);
		return Item.GetAmount();
	}

	if (IPlayer.IsOnline() && SkillBook.count(Item.CheckIndex()))
	{
		CheckSkillBook Skillbook = SkillBook.find(Item.CheckIndex())->second;
		if (IPlayer.GetClass() == Skillbook.Class)
		{
			int SkillPointer = IPlayer.GetSkillPointer(Skillbook.Action);
			if (SkillPointer)
			{
				ISkill ISkill((void*)SkillPointer);
				int newGrade = ISkill.GetGrade() + Skillbook.UpgradeAmount;

				if (newGrade <= Skillbook.UpgradeMax)
				{
					(*(void(__thiscall **)(int, DWORD, int, signed int))(*(DWORD *)SkillPointer + 8))(SkillPointer, PlayerOffset, newGrade, Skillbook.UpgradeAmount);
					*(DWORD *)(SkillPointer + 8) = newGrade;

					CDBSocket::Write(22, "dbbw", IPlayer.GetPID(), Skillbook.Action, newGrade, IPlayer.GetSkillPoint());
					CPlayer::Write(IPlayer.GetOffset(), 81, "bb", Skillbook.Action, newGrade);

					(*(int(__thiscall **)(DWORD, void *, signed int, signed int))(*(DWORD*)ItemOffset + 120))((int)ItemOffset, IPlayer.GetOffset(), *(DWORD *)(*(DWORD *)((int)ItemOffset + 40) + 156) != 0 ? 43 : 9, -1);
					IPlayer.SystemMessage("Skill successfully upgraded.", TEXTCOLOR_GREEN);
					return Item.GetAmount();
				}
				else {
					IPlayer.SystemMessage("You already have max grade of skill.", TEXTCOLOR_RED);
					return Item.GetAmount();
				}
			}
			else {
				int OldSP = IPlayer.GetSkillPoint();
				if ((Skillbook.Class == 1 && Skillbook.Action == 63))
					LearnSkill(IPlayer, Skillbook.Action, true);
				else if (OldSP) {
					SkillLearnPacket(IPlayer, Skillbook.Action);
					if (OldSP > IPlayer.GetSkillPoint())
						IPlayer.AddSkillPoint(1);
					else if (!(Skillbook.Action >= 85 && Skillbook.Action <= 87)) {
						IPlayer.SystemMessage("You can not learn that skill.", TEXTCOLOR_RED);
						return Item.GetAmount();
					}
				}
				else {
					IPlayer.SystemMessage("1 Skill point is needed to learn this skill.", TEXTCOLOR_RED);
					return Item.GetAmount();
				}

				(*(int(__thiscall **)(DWORD, void *, signed int, signed int))(*(DWORD*)ItemOffset + 120))((int)ItemOffset, IPlayer.GetOffset(), *(DWORD *)(*(DWORD *)((int)ItemOffset + 40) + 156) != 0 ? 43 : 9, -1);
				if (Skillbook.Action == 26){
					SkillPointer = IPlayer.GetSkillPointer(Skillbook.Action);
					if (SkillPointer)
					{
						ISkill ISkill((void*)SkillPointer);
						int newGrade = ISkill.GetGrade() + Skillbook.UpgradeAmount - 1;

						if (newGrade <= Skillbook.UpgradeMax)
						{
							(*(void(__thiscall **)(int, DWORD, int, signed int))(*(DWORD *)SkillPointer + 8))(SkillPointer, PlayerOffset, newGrade, Skillbook.UpgradeAmount);
							*(DWORD *)(SkillPointer + 8) = newGrade;

							CDBSocket::Write(22, "dbbw", IPlayer.GetPID(), Skillbook.Action, newGrade, IPlayer.GetSkillPoint());
							CPlayer::Write(IPlayer.GetOffset(), 81, "bb", Skillbook.Action, newGrade);

							(*(int(__thiscall **)(DWORD, void *, signed int, signed int))(*(DWORD*)ItemOffset + 120))((int)ItemOffset, IPlayer.GetOffset(), *(DWORD *)(*(DWORD *)((int)ItemOffset + 40) + 156) != 0 ? 43 : 9, -1);
							IPlayer.SystemMessage("Skill successfully upgraded.", TEXTCOLOR_GREEN);
							return Item.GetAmount();
						}
						else {
							IPlayer.SystemMessage("You already have max grade of skill.", TEXTCOLOR_RED);
							return Item.GetAmount();
						}
					}
				}
				IPlayer.SystemMessage("Skill successfully learned.", TEXTCOLOR_GREEN);
				return Item.GetAmount();
			}

			IPlayer.SystemMessage("First you must to get skill to upgrade it.", TEXTCOLOR_RED);
			return Item.GetAmount();
		}
		else {
			IPlayer.SystemMessage("Skill book is not for your class.", TEXTCOLOR_RED);
			return Item.GetAmount();
		}
	}

	if (IPlayer.IsOnline() && SkillDowngrade.count(Item.CheckIndex()))
	{
		CheckSkillBook Downbook = SkillDowngrade.find(Item.CheckIndex())->second;
		if (IPlayer.GetClass() == Downbook.Class)
		{
			int SkillPointer = IPlayer.GetSkillPointer(Downbook.Action);
			if (SkillPointer)
			{
				ISkill ISkill((void*)SkillPointer);
				int newGrade = ISkill.GetGrade() - Downbook.DowngradeAmount;

				if (newGrade >= 1)
				{
					(*(void(__thiscall **)(int, DWORD, int, signed int))(*(DWORD *)SkillPointer + 8))(SkillPointer, PlayerOffset, newGrade, Downbook.DowngradeAmount);
					*(DWORD *)(SkillPointer + 8) = newGrade;

					CDBSocket::Write(22, "dbbw", IPlayer.GetPID(), Downbook.Action, newGrade, IPlayer.GetSkillPoint());
					CPlayer::Write(IPlayer.GetOffset(), 81, "bb", Downbook.Action, newGrade);

					IPlayer.AddSkillPoint(Downbook.DowngradeAmount);
					IPlayer.AddReward(Downbook.RewardPoints);

					(*(int(__thiscall **)(DWORD, void *, signed int, signed int))(*(DWORD*)ItemOffset + 120))((int)ItemOffset, IPlayer.GetOffset(), *(DWORD *)(*(DWORD *)((int)ItemOffset + 40) + 156) != 0 ? 43 : 9, -1);
					IPlayer.SystemMessage("Skill successfully downgraded.", TEXTCOLOR_GREEN);
					return Item.GetAmount();
				}
				else {
					IPlayer.SystemMessage("Your skill must be atleast grade 2.", TEXTCOLOR_RED);
					return Item.GetAmount();
				}
			}
			else {
				IPlayer.SystemMessage("Skill doesn't exist.", TEXTCOLOR_RED);
				return Item.GetAmount();
			}

			IPlayer.SystemMessage("First you must to get skill to downgrade it.", TEXTCOLOR_RED);
			return Item.GetAmount();
		}
		else {
			IPlayer.SystemMessage("Skill book is not for your class.", TEXTCOLOR_RED);
			return Item.GetAmount();
		}
	}


	if (IPlayer.IsOnline() && Item.CheckIndex() == 482)
	{
		if (Protect32::Active == true && IPlayer.GetGID())
		{
			if (IPlayer.GetGID() == Protect32::GuildFirst || IPlayer.GetGID() == Protect32::GuildSecond)
				return Item.GetAmount();
		}

		if (CGuild::IsWarringPeriod())
		{
			if (CSMap::IsOnTile(*(void **)((int)IPlayer.Offset + 320), (int)IPlayer.Offset + 332, 1048576))
				return Item.GetAmount();
		}
	}

	if (IPlayer.IsOnline() && (Item.CheckIndex() == 47 || Item.CheckIndex() == 2441 || Item.CheckIndex() == 48 || Item.CheckIndex() == 2442 || Item.CheckIndex() == 2055 || Item.CheckIndex() == 2443) && IPlayer.IsBuff(120))
	{
		if (CInitItem::Use(*(DWORD *)((int)ItemOffset + 40), PlayerOffset))
		{
			if ((Item.CheckIndex() == 47 || Item.CheckIndex() == 2441))
			{
				if (IPlayer.IsValid())
					IPlayer.IncreaseHp(10);
			}

			if ((Item.CheckIndex() == 48 || Item.CheckIndex() == 2442))
			{
				if (IPlayer.IsValid())
					IPlayer.IncreaseHp(30);
			}

			if ((Item.CheckIndex() == 2055 || Item.CheckIndex() == 2443))
			{
				if (IPlayer.IsValid())
					IPlayer.IncreaseHp(50);
			}

			(*(int(__thiscall **)(DWORD, void *, signed int, signed int))(*(DWORD*)ItemOffset + 120))((int)ItemOffset, IPlayer.GetOffset(), 9, -1);

			if (*(DWORD *)(*((DWORD *)ItemOffset + 10) + 172))
				CChar::WriteInRect((int)IPlayer.GetOffset(), 73, 15, "db", IPlayer.GetID(), *(DWORD *)(*((DWORD *)ItemOffset + 10) + 172));

			return Item.GetAmount();
		}
	}

	if (IPlayer.IsOnline() && Item.CheckIndex() == BSOFSky) {
		if (LearnBlessingSonOfSky(IPlayer, (DWORD*)((int)IPlayer.GetOffset() + 624), true))
			(*(int(__thiscall **)(DWORD, void *, signed int, signed int))(*(DWORD*)ItemOffset + 120))((int)ItemOffset, IPlayer.GetOffset(), *(DWORD *)(*(DWORD *)((int)ItemOffset + 40) + 156) != 0 ? 43 : 9, -1);
		return Item.GetAmount();
	}


	if (IPlayer.IsOnline() && Item.CheckIndex() == 2160)
	{
		IPlayer.Teleport(6, 359660, 233716);
		(*(int(__thiscall **)(DWORD, void *, signed int, signed int))(*(DWORD*)ItemOffset + 120))((int)ItemOffset, IPlayer.GetOffset(), *(DWORD *)(*(DWORD *)((int)ItemOffset + 40) + 156) != 0 ? 43 : 9, -1);
		return Item.GetAmount();
	}

	if (IPlayer.IsOnline() && Item.CheckIndex() == 2159)
	{
		if (IPlayer.IsParty())
		{
			void *Party = (void*)CParty::FindParty(IPlayer.GetPartyID());

			if (Party)
			{
				for (int i = CParty::GetPlayerList(Party); i; i = CBaseList::Pop((void*)i))
				{
					IChar IMembers((void*)*(DWORD*)((void*)i));

					if (IPlayer.IsOnline() && IMembers.IsOnline())
						IMembers.Teleport(6, 359660, 233716);
				}
				CIOObject::Release(Party);
			}

			(*(int(__thiscall **)(DWORD, void *, signed int, signed int))(*(DWORD*)ItemOffset + 120))((int)ItemOffset, IPlayer.GetOffset(), *(DWORD *)(*(DWORD *)((int)ItemOffset + 40) + 156) != 0 ? 43 : 9, -1);
			return Item.GetAmount();
		}
		else {
			IPlayer.Teleport(6, 359660, 233716);
			(*(int(__thiscall **)(DWORD, void *, signed int, signed int))(*(DWORD*)ItemOffset + 120))((int)ItemOffset, IPlayer.GetOffset(), *(DWORD *)(*(DWORD *)((int)ItemOffset + 40) + 156) != 0 ? 43 : 9, -1);
			return Item.GetAmount();
		}
	}

	if (IPlayer.IsOnline() && Item.CheckIndex() == 2158)
	{
		IPlayer.Teleport(6, 360931, 187024);
		(*(int(__thiscall **)(DWORD, void *, signed int, signed int))(*(DWORD*)ItemOffset + 120))((int)ItemOffset, IPlayer.GetOffset(), *(DWORD *)(*(DWORD *)((int)ItemOffset + 40) + 156) != 0 ? 43 : 9, -1);
		return Item.GetAmount();
	}

	if (IPlayer.IsOnline() && Item.CheckIndex() == 2157)
	{
		if (IPlayer.IsParty())
		{
			void *Party = (void*)CParty::FindParty(IPlayer.GetPartyID());

			if (Party)
			{
				for (int i = CParty::GetPlayerList(Party); i; i = CBaseList::Pop((void*)i))
				{
					IChar IMembers((void*)*(DWORD*)((void*)i));

					if (IPlayer.IsOnline() && IMembers.IsOnline())
						IMembers.Teleport(6, 360931, 187024);
				}
				CIOObject::Release(Party);
			}

			(*(int(__thiscall **)(DWORD, void *, signed int, signed int))(*(DWORD*)ItemOffset + 120))((int)ItemOffset, IPlayer.GetOffset(), *(DWORD *)(*(DWORD *)((int)ItemOffset + 40) + 156) != 0 ? 43 : 9, -1);
			return Item.GetAmount();
		}
		else {
			IPlayer.Teleport(6, 360931, 187024);
			(*(int(__thiscall **)(DWORD, void *, signed int, signed int))(*(DWORD*)ItemOffset + 120))((int)ItemOffset, IPlayer.GetOffset(), *(DWORD *)(*(DWORD *)((int)ItemOffset + 40) + 156) != 0 ? 43 : 9, -1);
			return Item.GetAmount();
		}
	}

	if (IPlayer.IsOnline() && ItemExpansion.count(Item.CheckIndex())) {

		int IETime = 86400 * ItemExpansion.find(Item.CheckIndex())->second.Time;
		if (!IPlayer.IsBuff(BuffNames::Extension1)) {

			if (IPlayer.IsBuff(BuffNames::Extension2)) {
				int Remain = IPlayer.GetBuffValue(BuffNames::Extension2) - (int)time(0);
				int Remain2 = IPlayer.GetBuffValue(BuffNames::Extension3) - (int)time(0);

				IPlayer.CancelBuff(BuffNames::Extension3);
				IPlayer.CancelBuff(BuffNames::Extension2);
				IPlayer.CancelBuff(BuffNames::Extension1);

				IPlayer.SaveBuff(BuffNames::Extension1, Remain, Remain + (int)time(0), 0, 0);
				IPlayer.SaveBuff(BuffNames::Extension2, Remain2, Remain2 + (int)time(0), 0, 0);
				IPlayer.SaveBuff(BuffNames::Extension3, IETime, IETime + (int)time(0), 0, 0);

				CPlayer::Write(IPlayer.GetOffset(), 204, "d", 108);
				CPlayer::Write(IPlayer.GetOffset(), 181, "dwd", IPlayer.GetID(), 499, IETime);
				CPlayer::Write(IPlayer.GetOffset(), 181, "dwd", IPlayer.GetID(), 500, Remain2);
				CPlayer::Write(IPlayer.GetOffset(), 181, "dwd", IPlayer.GetID(), 501, Remain);
			}
			else
			if (IPlayer.IsBuff(BuffNames::Extension3)) {
				int Remain2 = IPlayer.GetBuffValue(BuffNames::Extension3) - (int)time(0);

				IPlayer.CancelBuff(BuffNames::Extension3);
				IPlayer.CancelBuff(BuffNames::Extension2);
				IPlayer.CancelBuff(BuffNames::Extension1);

				IPlayer.SaveBuff(BuffNames::Extension2, Remain2, Remain2 + (int)time(0), 0, 0);
				IPlayer.SaveBuff(BuffNames::Extension3, IETime, IETime + (int)time(0), 0, 0);
				CPlayer::Write(IPlayer.GetOffset(), 204, "d", 72);
				CPlayer::Write(IPlayer.GetOffset(), 181, "dwd", IPlayer.GetID(), 499, IETime);
				CPlayer::Write(IPlayer.GetOffset(), 181, "dwd", IPlayer.GetID(), 500, Remain2);
			}
			else {
				IPlayer.CancelBuff(BuffNames::Extension3);
				IPlayer.CancelBuff(BuffNames::Extension2);
				IPlayer.CancelBuff(BuffNames::Extension1);

				IPlayer.SaveBuff(BuffNames::Extension3, IETime, IETime + (int)time(0), 0, 0);
				CPlayer::Write(IPlayer.GetOffset(), 204, "d", 36);
				CPlayer::Write(IPlayer.GetOffset(), 181, "dwd", IPlayer.GetID(), 499, IETime);
			}
			IPlayer.BoxMsg("You have successfully Expanded your inventory by 36 more slots for " + Int2String(ItemExpansion.find(Item.CheckIndex())->second.Time) + " days.");
			(*(int(__thiscall **)(DWORD, void *, signed int, signed int))(*(DWORD*)ItemOffset + 120))((int)ItemOffset, IPlayer.GetOffset(), *(DWORD *)(*(DWORD *)((int)ItemOffset + 40) + 156) != 0 ? 43 : 9, -1);
		}
		else
			IPlayer.BoxMsg("You have already expanded your inventory to the max you could!");

		return Item.GetAmount();
	}

	if (IPlayer.IsOnline() && Item.CheckIndex() == 447)
	{
		if (IPlayer.IsBuff(12))
			IPlayer.CancelBuff(12);
	}


	if (IPlayer.IsOnline() && ItemBuffSrv.count(Item.CheckIndex())){
		double Buff = 3;

		double Refine = 3;
		if (Buff == 3) Buff = 2.75;
		if (Refine == 3) Refine = 5.5;

		std::string playerName = IPlayer.GetName();

		CIOCriticalSection::Enter((void*)0x4e2078);
		CIOCriticalSection::Enter((void*)0x4e2098);
		CLink::MoveTo((void*)0x4e200c, (int)0x4e2004);
		CIOCriticalSection::Leave((void*)0x4e2098);
		for (DWORD i = *(DWORD*)0x4E2004; i != 0x4E2004; i = *(DWORD*)i)
		{
			IChar Online((void*)(i - 428));
			if (Online.IsOnline()) {
				Online.Buff(48, 1800, 8 * Buff + 3);
				Online.Buff(50, 1800, 8 * Buff + 3);
				Online.Buff(47, 1800, 8 * Buff + 3);
				Online.Buff(49, 1800, 8 * Buff + 3);
				Online.Buff(46, 1800, 8 * Buff + 3);
				Online.Buff(36, 1800, 8 * Refine + 16);
				CChar::CancelAllBuff(Online.GetOffset(), 37);
				int AddBuff = CBuff::CreateBuff(37, 1800, 30 * Buff + 5, 20 * Buff + 5);
				(*(int(__thiscall **)(int, int))(*(DWORD *)(int)Online.GetOffset() + 180))((int)Online.GetOffset(), AddBuff);
				Online.Buff(12, 1800, 60);
				CPlayer::Write(Online.GetOffset(), 0xFF, "dsd", 247, playerName + " has blessed the whole server, GG!", NOTICECOLOR_ORANGELONG);
			}
		}
		CIOCriticalSection::Leave((void*)0x4e2078);

		(*(int(__thiscall **)(DWORD, void *, signed int, signed int))(*(DWORD*)ItemOffset + 120))((int)ItemOffset, IPlayer.GetOffset(), 9, -1);
		return Item.GetAmount();
	}

	if (IPlayer.IsOnline() && Item.CheckIndex() == NewMystReset)
	{

		if (!NewMystEnable)
		{
			IPlayer.SystemMessage("Mystery Skills are disabled.", TEXTCOLOR_RED);
			return Item.GetAmount();
		}


		int CheckGrade = 0;
		if (IPlayer.GetLevel() >= MystLevelMax)
			CheckGrade = 30;
		else
			CheckGrade = IPlayer.GetLevel() - MystLevel + 1;

		int OTP = IPlayer.IsBuff(BuffNames::MystOTP);
		int EVA = IPlayer.IsBuff(BuffNames::MystEVA);
		int HP = IPlayer.IsBuff(BuffNames::MystHP);
		int PhyAtk = IPlayer.IsBuff(BuffNames::MystPhy);
		int MagAtk = IPlayer.IsBuff(BuffNames::MystMag);
		int Def = IPlayer.IsBuff(BuffNames::MystDef);

		if (!OTP && !EVA && !HP && !PhyAtk && !MagAtk && !Def){
			IPlayer.SystemMessage("You do not have Mystery Passive to reset.", TEXTCOLOR_RED);
			return Item.GetAmount();
		}

		if (OTP){
			IPlayer.RemoveSavedBuff(BuffNames::MystOTP);
			if (CheckGrade)
				IPlayer.RemoveOTP(2 * CheckGrade);
			else
				IPlayer.RemoveOTP(2);
			IPlayer.RemoveBuffIcon(0, 0, MystOTPS, MystOTPS);

			IPlayer.BoxMsg("On Target Point Mystery Skill has resetted.");
		}
		else if (EVA){
			IPlayer.RemoveSavedBuff(BuffNames::MystEVA);
			if (CheckGrade)
				IPlayer.RemoveEva(2 * CheckGrade);
			else
				IPlayer.RemoveEva(2);
			IPlayer.RemoveBuffIcon(0, 0, MystEVAS, MystEVAS);

			IPlayer.BoxMsg("Evasion Point Mystery Skill has resetted.");
		}
		else if (HP){
			IPlayer.RemoveSavedBuff(BuffNames::MystHP);
			if (CheckGrade)
				IPlayer.DecreaseMaxHp(250 * CheckGrade);
			else
				IPlayer.DecreaseMaxHp(250);
			IPlayer.RemoveBuffIcon(0, 0, MystHPS, MystHPS);

			IPlayer.BoxMsg("Health Point Mystery Skill has resetted.");
		}
		else if (Def){
			IPlayer.RemoveSavedBuff(BuffNames::MystDef);
			if (CheckGrade)
				IPlayer.RemoveDef(10 * CheckGrade);
			else
				IPlayer.RemoveDef(10);
			IPlayer.RemoveBuffIcon(0, 0, MystDefS, MystDefS);

			IPlayer.BoxMsg("Defense Point Mystery Skill has resetted.");
		}
		else if (PhyAtk){
			IPlayer.RemoveSavedBuff(BuffNames::MystPhy);
			if (CheckGrade)
				IPlayer.RemoveMinAttack(10 * CheckGrade);
			else
				IPlayer.RemoveMinAttack(10);
			IPlayer.RemoveBuffIcon(0, 0, MystPAtkS, MystPAtkS);

			IPlayer.BoxMsg("Physical Attack Point Mystery Skill has resetted.");
		}
		else if (MagAtk){
			IPlayer.RemoveSavedBuff(BuffNames::MystMag);
			if (CheckGrade)
				IPlayer.RemoveMaxAttack(10 * CheckGrade);
			else
				IPlayer.RemoveMaxAttack(10);
			IPlayer.RemoveBuffIcon(0, 0, MystMAtkS, MystMAtkS);
			IPlayer.BoxMsg("Magical Attack Point Mystery Skill has resetted.");
		}

		(*(int(__thiscall **)(DWORD, void *, signed int, signed int))(*(DWORD*)ItemOffset + 120))((int)ItemOffset, IPlayer.GetOffset(), *(DWORD *)(*(DWORD *)((int)ItemOffset + 40) + 156) != 0 ? 43 : 9, -1);
		return Item.GetAmount();
	}


	if (IPlayer.IsOnline() && ItemScrolls.count(Item.CheckIndex())){
		if ((IPlayer.IsBuff(58) && IPlayer.IsBuff(51) && IPlayer.IsBuff(54) && IPlayer.IsBuff(55) && IPlayer.IsBuff(56) && IPlayer.IsBuff(57)) || (IPlayer.IsBuff(60) && IPlayer.IsBuff(61) && IPlayer.IsBuff(62) && IPlayer.IsBuff(63))) {
			IPlayer.SystemMessage("Scrolls/Potions already in use. Please wait untill its time is over!", TEXTCOLOR_RED);
			return Item.GetAmount();
		}

		int Level = ItemScrolls.find(Item.CheckIndex())->second.level;
		if (IPlayer.GetLevel() < Level){
			IPlayer.SystemMessage("You must be atleast " + Int2String(Level) + " to use this item.", TEXTCOLOR_RED);
			return Item.GetAmount();
		}

		for (int i = 51; i < 58; i++) {
			if (!IPlayer.IsBuff(i))
				IPlayer.Buff(i, 3600, 0);
		}
		for (int i = 60; i < 65; i++) {
			int value = 0;
			if (i == 60 || i == 62 || i == 64) value = 5;
			if (i == 61 || i == 63) value = 10;
			if (!IPlayer.IsBuff(i))
				IPlayer.Buff(i, 3600, value);
		}

		if (ItemScrolls.find(Item.CheckIndex())->second.remove)
			(*(int(__thiscall **)(DWORD, void *, signed int, signed int))(*(DWORD*)ItemOffset + 120))((int)ItemOffset, IPlayer.GetOffset(), *(DWORD *)(*(DWORD *)((int)ItemOffset + 40) + 156) != 0 ? 43 : 9, -1);

		return Item.GetAmount();
	}

	if (IPlayer.IsOnline() && ItemTasty.count(Item.CheckIndex()))
	{
		int Level = ItemTasty.find(Item.CheckIndex())->second.level;

		if (IPlayer.GetLevel() >= Level) {
			if (IPlayer.IsBuff(272) && IPlayer.IsBuff(262) && IPlayer.IsBuff(264) && IPlayer.IsBuff(266) && IPlayer.IsBuff(268) && IPlayer.IsBuff(270)) {
				IPlayer.SystemMessage("All buffs already in use.", TEXTCOLOR_RED);
				return Item.GetAmount();
			}

			if (!IPlayer.IsBuff(272)) {
				IPlayer.Buff(272, 1800, 0);
				IPlayer.Buff(261, 1810, 0);
				IPlayer.SetBuffIcon(1800000, 0, 3645, 430);
				IPlayer.IncreaseMaxHp(1450);
			}
			if (!IPlayer.IsBuff(262)) {
				IPlayer.Buff(262, 1800, 0);
				IPlayer.Buff(263, 1810, 0);
				IPlayer.SetBuffIcon(1800000, 0, 3646, 431);
				IPlayer.IncreaseMaxMp(900);
			}
			if (!IPlayer.IsBuff(264)) {
				IPlayer.Buff(264, 3600, 0);
				IPlayer.Buff(265, 3610, 0);
				IPlayer.SetBuffIcon(3600000, 0, 3601, 415);
				IPlayer.IncreaseMaxHp(500);
				IPlayer.IncreaseMaxMp(500);
			}
			if (!IPlayer.IsBuff(266)) {
				IPlayer.Buff(266, 3600, 0);
				IPlayer.Buff(267, 3610, 0);
				IPlayer.SetBuffIcon(3600000, 0, 3604, 418);
				IPlayer.AddMaxAttack(75);
				IPlayer.AddMinAttack(50);
				IPlayer.AddEva(10);
			}
			if (!IPlayer.IsBuff(268)) {
				IPlayer.Buff(268, 3600, 0);
				IPlayer.Buff(269, 3610, 0);
				IPlayer.SetBuffIcon(3600000, 0, 3603, 417);
				IPlayer.AddMaxAttack(100);
			}
			if (!IPlayer.IsBuff(270)) {
				IPlayer.Buff(270, 3600, 0);
				IPlayer.Buff(271, 3610, 0);
				IPlayer.SetBuffIcon(3600000, 0, 3602, 416);
				IPlayer.AddMinAttack(75);
				IPlayer.AddOTP(10);
			}
			if (ItemTasty.find(Item.CheckIndex())->second.remove)
				(*(int(__thiscall **)(DWORD, void *, signed int, signed int))(*(DWORD*)ItemOffset + 120))((int)ItemOffset, IPlayer.GetOffset(), *(DWORD *)(*(DWORD *)((int)ItemOffset + 40) + 156) != 0 ? 43 : 9, -1);
		}
		else
			IPlayer.SystemMessage("You must be level " + Int2String(Level) + " to use this item.", TEXTCOLOR_RED);

		return Item.GetAmount();
	}



	if (IPlayer.IsOnline() && ItemHpDef.count(Item.CheckIndex())) {
		if (IPlayer.GetBuffRemain(58) >= 9500 || IPlayer.GetBuffRemain(59) >= 9500 || IPlayer.GetBuffRemain(58) >= 9500 && IPlayer.GetBuffRemain(59) >= 9500) {
			IPlayer.SystemMessage("Exceeded Scroll Usage Limit!", TEXTCOLOR_RED);
			return Item.GetAmount();
		}

		int Level = ItemHpDef.find(Item.CheckIndex())->second.level;
		if (IPlayer.GetLevel() < Level){
			IPlayer.SystemMessage("You must be atleast " + Int2String(Level) + " to use this item.", TEXTCOLOR_RED);
			return Item.GetAmount();
		}

		for (int i = 58; i < 60; i++) {
			int Time = 500;

			if (IPlayer.IsBuff(i))
				Time = IPlayer.GetBuffRemain(i) + 500;

			if (Time <= 9500)
				IPlayer.Buff(i, Time, 0);
		}

		if (ItemHpDef.find(Item.CheckIndex())->second.remove)
			(*(int(__thiscall **)(DWORD, void *, signed int, signed int))(*(DWORD*)ItemOffset + 120))((int)ItemOffset, IPlayer.GetOffset(), *(DWORD *)(*(DWORD *)((int)ItemOffset + 40) + 156) != 0 ? 43 : 9, -1);

		return Item.GetAmount();
	}



	if (IPlayer.IsOnline() && Item.CheckIndex() == 2366)
	{
		if (!IPlayer.IsBuff(272)) {
			IPlayer.Buff(272, 1800, 0);
			IPlayer.Buff(261, 1810, 0);
			IPlayer.SetBuffIcon(1800000, 0, 3645, 430);
			IPlayer.IncreaseMaxHp(1450);
			(*(int(__thiscall **)(DWORD, void *, signed int, signed int))(*(DWORD*)ItemOffset + 120))((int)ItemOffset, IPlayer.GetOffset(), *(DWORD *)(*(DWORD *)((int)ItemOffset + 40) + 156) != 0 ? 43 : 9, -1);
		}
		return Item.GetAmount();
	}

	if (IPlayer.IsOnline() && Item.CheckIndex() == 2367)
	{
		if (!IPlayer.IsBuff(262)) {
			IPlayer.Buff(262, 1800, 0);
			IPlayer.Buff(263, 1810, 0);
			IPlayer.SetBuffIcon(1800000, 0, 3646, 431);
			IPlayer.IncreaseMaxMp(900);
			(*(int(__thiscall **)(DWORD, void *, signed int, signed int))(*(DWORD*)ItemOffset + 120))((int)ItemOffset, IPlayer.GetOffset(), *(DWORD *)(*(DWORD *)((int)ItemOffset + 40) + 156) != 0 ? 43 : 9, -1);
		}
		return Item.GetAmount();
	}

	if (IPlayer.IsOnline() && Item.CheckIndex() == 2076)
	{
		if (!IPlayer.IsBuff(264)) {
			IPlayer.Buff(264, 3600, 0);
			IPlayer.Buff(265, 3610, 0);
			IPlayer.SetBuffIcon(3600000, 0, 3601, 415);
			IPlayer.IncreaseMaxHp(500);
			IPlayer.IncreaseMaxMp(500);
			(*(int(__thiscall **)(DWORD, void *, signed int, signed int))(*(DWORD*)ItemOffset + 120))((int)ItemOffset, IPlayer.GetOffset(), *(DWORD *)(*(DWORD *)((int)ItemOffset + 40) + 156) != 0 ? 43 : 9, -1);
		}
		return Item.GetAmount();
	}

	if (IPlayer.IsOnline() && Item.CheckIndex() == 2079)
	{
		if (!IPlayer.IsBuff(266)) {
			IPlayer.Buff(266, 3600, 0);
			IPlayer.Buff(267, 3610, 0);
			IPlayer.SetBuffIcon(3600000, 0, 3604, 418);
			IPlayer.AddMaxAttack(75);
			IPlayer.AddMinAttack(50);
			IPlayer.AddEva(10);
			(*(int(__thiscall **)(DWORD, void *, signed int, signed int))(*(DWORD*)ItemOffset + 120))((int)ItemOffset, IPlayer.GetOffset(), *(DWORD *)(*(DWORD *)((int)ItemOffset + 40) + 156) != 0 ? 43 : 9, -1);
		}
		return Item.GetAmount();
	}

	if (IPlayer.IsOnline() && Item.CheckIndex() == 2078)
	{
		if (!IPlayer.IsBuff(268)) {
			IPlayer.Buff(268, 3600, 0);
			IPlayer.Buff(269, 3610, 0);
			IPlayer.SetBuffIcon(3600000, 0, 3603, 417);
			IPlayer.AddMaxAttack(100);
			(*(int(__thiscall **)(DWORD, void *, signed int, signed int))(*(DWORD*)ItemOffset + 120))((int)ItemOffset, IPlayer.GetOffset(), *(DWORD *)(*(DWORD *)((int)ItemOffset + 40) + 156) != 0 ? 43 : 9, -1);
		}
		return Item.GetAmount();
	}

	if (IPlayer.IsOnline() && Item.CheckIndex() == 2077)
	{
		if (!IPlayer.IsBuff(270)) {
			IPlayer.Buff(270, 3600, 0);
			IPlayer.Buff(271, 3610, 0);
			IPlayer.SetBuffIcon(3600000, 0, 3602, 416);
			IPlayer.AddMinAttack(75);
			IPlayer.AddOTP(10);
			(*(int(__thiscall **)(DWORD, void *, signed int, signed int))(*(DWORD*)ItemOffset + 120))((int)ItemOffset, IPlayer.GetOffset(), *(DWORD *)(*(DWORD *)((int)ItemOffset + 40) + 156) != 0 ? 43 : 9, -1);
		}
		return Item.GetAmount();
	}

	if (IPlayer.IsOnline() && EmokCerts.count(Item.CheckIndex()))
	{
		int BRemain = IPlayer.GetBuffRemain(156);
		int EmokTimeLeft = IPlayer.GetProperty(PlayerProperty::EmokTime);

		EmokCertConf eCert = EmokCerts.find(Item.CheckIndex())->second;
		if (eCert.EXP && (BRemain || EmokTimeLeft)) {
			IPlayer.SystemMessage("You already have an emok timer running out. Please use this certificate once its ended.", TEXTCOLOR_RED);
			return Item.GetAmount();
		}

		int Time = BRemain + eCert.Time;

		if (!BRemain)
			Time += EmokTimeLeft;

		IPlayer.Buff(156, Time, eCert.EXP);
		IPlayer.SetProperty(PlayerProperty::EmokEXP, eCert.EXP);

		if (eCert.EXP) {
			int Times = (int)time(0) + Time;
			CDBSocket::Write(95, "ddddddd", 1, IPlayer.GetPID(), 156, eCert.EXP, 0, 0, BuffNames::BuffTime);
		}

		(*(int(__thiscall **)(DWORD, void *, signed int, signed int))(*(DWORD*)ItemOffset + 120))((int)ItemOffset, IPlayer.GetOffset(), *(DWORD *)(*(DWORD *)((int)ItemOffset + 40) + 156) != 0 ? 43 : 9, -1);
		return Item.GetAmount();
	}

	if (IPlayer.IsOnline() && Item.CheckIndex() == EmokCert)
	{
		if (IPlayer.IsBuff(156))
			IPlayer.Buff(156, IPlayer.GetBuffRemain(156) + 3600, 0);
		else
			IPlayer.Buff(156, IPlayer.GetProperty(PlayerProperty::EmokTime) + 3600, 0);

		(*(int(__thiscall **)(DWORD, void *, signed int, signed int))(*(DWORD*)ItemOffset + 120))((int)ItemOffset, IPlayer.GetOffset(), *(DWORD *)(*(DWORD *)((int)ItemOffset + 40) + 156) != 0 ? 43 : 9, -1);
		return Item.GetAmount();
	}

	if (IPlayer.IsOnline() && Item.CheckIndex() == 2430 && !IPlayer.IsBuff(121))
	{
		IPlayer.Buff(121, 3600, 0);
		IPlayer.Buff(273, 3610, 0);
		IPlayer.SetBuffIcon(3600000, 0, 3877, 442);
		(*(int(__thiscall **)(DWORD, void *, signed int, signed int))(*(DWORD*)ItemOffset + 120))((int)ItemOffset, IPlayer.GetOffset(), *(DWORD *)(*(DWORD *)((int)ItemOffset + 40) + 156) != 0 ? 43 : 9, -1);
		return Item.GetAmount();
	}

	if (IPlayer.IsOnline() && Item.CheckIndex() == 2431 && !IPlayer.IsBuff(122))
	{
		IPlayer.Buff(122, 3600, 0);
		IPlayer.Buff(274, 3610, 0);
		IPlayer.SetBuffIcon(3600000, 0, 3879, 444);
		(*(int(__thiscall **)(DWORD, void *, signed int, signed int))(*(DWORD*)ItemOffset + 120))((int)ItemOffset, IPlayer.GetOffset(), *(DWORD *)(*(DWORD *)((int)ItemOffset + 40) + 156) != 0 ? 43 : 9, -1);
		return Item.GetAmount();
	}

	if (IPlayer.IsOnline() && Item.CheckIndex() == 2433 && !IPlayer.IsBuff(123))
	{
		IPlayer.Buff(123, 3600, 0);
		IPlayer.Buff(275, 3610, 0);
		IPlayer.SetBuffIcon(3600000, 0, 3886, 451);
		IPlayer.AddOTP(15);
		(*(int(__thiscall **)(DWORD, void *, signed int, signed int))(*(DWORD*)ItemOffset + 120))((int)ItemOffset, IPlayer.GetOffset(), *(DWORD *)(*(DWORD *)((int)ItemOffset + 40) + 156) != 0 ? 43 : 9, -1);
		return Item.GetAmount();
	}

	if (IPlayer.IsOnline() && Item.CheckIndex() == 2434 && !IPlayer.IsBuff(124))
	{
		IPlayer.Buff(124, 3600, 0);
		IPlayer.Buff(276, 3610, 0);
		IPlayer.SetBuffIcon(3600000, 0, 3880, 445);
		IPlayer.AddEva(7);
		(*(int(__thiscall **)(DWORD, void *, signed int, signed int))(*(DWORD*)ItemOffset + 120))((int)ItemOffset, IPlayer.GetOffset(), *(DWORD *)(*(DWORD *)((int)ItemOffset + 40) + 156) != 0 ? 43 : 9, -1);
		return Item.GetAmount();
	}

	if (IPlayer.IsOnline() && Item.CheckIndex() == 2438 && !IPlayer.IsBuff(125))
	{
		IPlayer.Buff(125, 3600, 0);
		IPlayer.Buff(277, 3610, 0);
		IPlayer.SetBuffIcon(3600000, 0, 3885, 450);
		IPlayer.AddHp(12);
		(*(int(__thiscall **)(DWORD, void *, signed int, signed int))(*(DWORD*)ItemOffset + 120))((int)ItemOffset, IPlayer.GetOffset(), *(DWORD *)(*(DWORD *)((int)ItemOffset + 40) + 156) != 0 ? 43 : 9, -1);
		return Item.GetAmount();
	}

	if (IPlayer.IsOnline() && Item.CheckIndex() == 2439 && !IPlayer.IsBuff(126))
	{
		IPlayer.Buff(126, 3600, 0);
		IPlayer.Buff(278, 3610, 0);
		IPlayer.SetBuffIcon(3600000, 0, 3884, 449);
		IPlayer.AddWis(12);
		(*(int(__thiscall **)(DWORD, void *, signed int, signed int))(*(DWORD*)ItemOffset + 120))((int)ItemOffset, IPlayer.GetOffset(), *(DWORD *)(*(DWORD *)((int)ItemOffset + 40) + 156) != 0 ? 43 : 9, -1);
		return Item.GetAmount();
	}

	if (IPlayer.IsOnline() && Item.CheckIndex() == 2436 && !IPlayer.IsBuff(127))
	{
		IPlayer.Buff(127, 3600, 0);
		IPlayer.Buff(279, 3610, 0);
		IPlayer.SetBuffIcon(3600000, 0, 3883, 448);
		IPlayer.AddInt(7);
		(*(int(__thiscall **)(DWORD, void *, signed int, signed int))(*(DWORD*)ItemOffset + 120))((int)ItemOffset, IPlayer.GetOffset(), *(DWORD *)(*(DWORD *)((int)ItemOffset + 40) + 156) != 0 ? 43 : 9, -1);
		return Item.GetAmount();
	}

	if (IPlayer.IsOnline() && Item.CheckIndex() == 2437 && !IPlayer.IsBuff(128))
	{
		IPlayer.Buff(128, 3600, 0);
		IPlayer.Buff(280, 3610, 0);
		IPlayer.SetBuffIcon(3600000, 0, 3882, 447);
		IPlayer.AddAgi(7);
		(*(int(__thiscall **)(DWORD, void *, signed int, signed int))(*(DWORD*)ItemOffset + 120))((int)ItemOffset, IPlayer.GetOffset(), *(DWORD *)(*(DWORD *)((int)ItemOffset + 40) + 156) != 0 ? 43 : 9, -1);
		return Item.GetAmount();
	}

	if (IPlayer.IsOnline() && Item.CheckIndex() == 2435 && !IPlayer.IsBuff(129))
	{
		IPlayer.Buff(129, 3600, 0);
		IPlayer.Buff(281, 3610, 0);
		IPlayer.SetBuffIcon(3600000, 0, 3881, 446);
		IPlayer.AddStr(7);
		(*(int(__thiscall **)(DWORD, void *, signed int, signed int))(*(DWORD*)ItemOffset + 120))((int)ItemOffset, IPlayer.GetOffset(), *(DWORD *)(*(DWORD *)((int)ItemOffset + 40) + 156) != 0 ? 43 : 9, -1);
		return Item.GetAmount();
	}

	if (IPlayer.IsOnline() && ItemUsed.count(Item.CheckIndex()))
	{
		IPlayer.OpenHTML(ItemUsed.find(Item.CheckIndex())->second.HTML);

		if (ItemUsed.find(Item.CheckIndex())->second.Remove == 1)
			(*(int(__thiscall **)(DWORD, void *, signed int, signed int))(*(DWORD*)ItemOffset + 120))((int)ItemOffset, IPlayer.GetOffset(), *(DWORD *)(*(DWORD *)((int)ItemOffset + 40) + 156) != 0 ? 43 : 9, -1);

		return Item.GetAmount();
	}

	if (IPlayer.IsOnline() && Item.CheckIndex() >= 1328 && Item.CheckIndex() <= 1365)
	{
		IPlayer.OpenHTML(598692 + Item.CheckIndex());
		return Item.GetAmount();
	}

	if (IPlayer.IsOnline() && Item.CheckIndex() >= 1741 && Item.CheckIndex() <= 1745)
	{
		IPlayer.OpenHTML(598317 + Item.CheckIndex());
		return Item.GetAmount();
	}

	if (IPlayer.IsOnline() && Item.CheckIndex() >= 1796 && Item.CheckIndex() <= 1800)
	{
		IPlayer.OpenHTML(598267 + Item.CheckIndex());
		return Item.GetAmount();
	}

	if (IPlayer.IsOnline() && Item.CheckIndex() >= 2061 && Item.CheckIndex() <= 2069)
	{
		IPlayer.OpenHTML(598007 + Item.CheckIndex());
		return Item.GetAmount();
	}

	if (IPlayer.IsOnline() && Item.CheckIndex() >= 2417 && Item.CheckIndex() <= 2419)
	{
		IPlayer.OpenHTML(597660 + Item.CheckIndex());
		return Item.GetAmount();
	}

	if (IPlayer.IsOnline() && Item.CheckIndex() >= 3060 && Item.CheckIndex() <= 3069)
	{
		IPlayer.OpenHTML(597020 + Item.CheckIndex());
		return Item.GetAmount();
	}

	if (IPlayer.IsOnline() && Item.CheckIndex() == 3090)
	{
		IPlayer.OpenHTML(600090);
		return Item.GetAmount();
	}

	if (IPlayer.IsOnline() && NormalPetTalisman.count(Item.CheckIndex()))
	{
		ConfigTimeTalisman t = NormalPetTalisman.find(Item.CheckIndex())->second;

		bool itemFound = false;

		if (IPlayer.GetBuffValue(BuffNames::PetOwner)) {

			int PetItem = IPlayer.GetBuffValue(BuffNames::PetIID);

			if (!PetLifeCheck.count(PetItem))
			{
				IPlayer.BoxMsg("Pet has no time to extend.");
				return Item.GetAmount();
			}

			if (PetItem) {
				int ItemP = IPlayer.ItemPointerLock(PetItem);

				if (ItemP)
				{
					IItem Itemx((void*)ItemP);

					if (CItem::IsState(ItemP, 1)){
						int ExtendTime = t.time;
						int RemainingTime = PetLifeCheck.findValue(Itemx.GetIID()) - (int)time(0);
						int TotalTime = ExtendTime + RemainingTime;
						PetLifeCheck.replaceInsert(Itemx.GetIID(), (int)time(0) + TotalTime);

						CDBSocket::Write(89, "ddd", IPlayer.GetPID(), (int)time(0) + TotalTime, Itemx.GetIID());
						CPlayer::Write(IPlayer.GetOffset(), 0xFF, "ddd", 230, Itemx.GetIID(), TotalTime);
						*(DWORD*)((int)Itemx.GetOffset() + 68) = GetTickCount() + (2000 * TotalTime);
						*(DWORD*)((int)Itemx.GetOffset() + 72) = 0;
						itemFound = true;
						IPlayer.SystemMessage("Time has successfully extended.", TEXTCOLOR_GREEN);
					}
				}
			}
		}

		if (!itemFound)
		{
			IPlayer.BoxMsg("Please equip Normal Pet before using extension.");
			return Item.GetAmount();
		}

		(*(int(__thiscall **)(DWORD, void *, signed int, signed int))(*(DWORD*)ItemOffset + 120))((int)ItemOffset, IPlayer.GetOffset(), *(DWORD *)(*(DWORD *)((int)ItemOffset + 40) + 156) != 0 ? 43 : 9, -1);
		return Item.GetAmount();
	}

	if (IPlayer.IsOnline() && MonsterPetTalisman.count(Item.CheckIndex()))
	{
		ConfigTimeTalisman t = MonsterPetTalisman.find(Item.CheckIndex())->second;

		bool itemFound = false;

		if (IPlayer.GetBuffValue(BuffNames::PetOwner2)) {

			int PetItem = IPlayer.GetBuffValue(BuffNames::PetIID2);

			if (!PetLifeCheck.count(PetItem))
			{
				IPlayer.BoxMsg("Pet has no time to extend.");
				return Item.GetAmount();
			}

			if (PetItem) {
				int ItemP = IPlayer.ItemPointerLock(PetItem);

				if (ItemP)
				{
					IItem Itemx((void*)ItemP);

					if (CItem::IsState(ItemP, 1)){
						int ExtendTime = t.time;
						int RemainingTime = PetLifeCheck.findValue(Itemx.GetIID()) - (int)time(0);
						int TotalTime = ExtendTime + RemainingTime;
						PetLifeCheck.replaceInsert(Itemx.GetIID(), (int)time(0) + TotalTime);

						CDBSocket::Write(89, "ddd", IPlayer.GetPID(), (int)time(0) + TotalTime, Itemx.GetIID());
						CPlayer::Write(IPlayer.GetOffset(), 0xFF, "ddd", 230, Itemx.GetIID(), TotalTime);
						*(DWORD*)((int)Itemx.GetOffset() + 68) = GetTickCount() + (2000 * TotalTime);
						*(DWORD*)((int)Itemx.GetOffset() + 72) = 0;
						itemFound = true;
						IPlayer.SystemMessage("Time has successfully extended.", TEXTCOLOR_GREEN);
					}
				}
			}
		}

		if (!itemFound)
		{
			IPlayer.BoxMsg("Please equip Monster Pet before using extension.");
			return Item.GetAmount();
		}

		(*(int(__thiscall **)(DWORD, void *, signed int, signed int))(*(DWORD*)ItemOffset + 120))((int)ItemOffset, IPlayer.GetOffset(), *(DWORD *)(*(DWORD *)((int)ItemOffset + 40) + 156) != 0 ? 43 : 9, -1);
		return Item.GetAmount();
	}

	if (IPlayer.IsOnline() && CostumeTalisman.count(Item.CheckIndex()))
	{
		ConfigTimeTalisman t = CostumeTalisman.find(Item.CheckIndex())->second;
		bool itemFound = false;

		if (IPlayer.GetBuffValue(BuffNames::SuitsUsing)) {

			int CostumeItemIndex = IPlayer.GetBuffValue(BuffNames::SuitsUsing);
			int CostumeItem = CPlayer::FindItem(IPlayer.GetOffset(), CostumeItemIndex, 1);
			IItem Costumex((void*)CostumeItem);

			if (CostumeItem && CItem::IsState(CostumeItem, 1)){
				if (!PetLifeCheck.count(Costumex.GetIID()))
				{
					IPlayer.BoxMsg("Costume Suit has no time to extend.");
					return Item.GetAmount();
				}

				int ExtendTime = t.time;
				int RemainingTime = PetLifeCheck.findValue(Costumex.GetIID()) - (int)time(0);
				int TotalTime = ExtendTime + RemainingTime;
				PetLifeCheck.replaceInsert(Costumex.GetIID(), (int)time(0) + TotalTime);

				CDBSocket::Write(89, "ddd", IPlayer.GetPID(), (int)time(0) + TotalTime, Costumex.GetIID());
				CPlayer::Write(IPlayer.GetOffset(), 0xFF, "ddd", 230, Costumex.GetIID(), TotalTime);
				*(DWORD*)((int)Costumex.GetOffset() + 68) = GetTickCount() + (2000 * TotalTime);
				*(DWORD*)((int)Costumex.GetOffset() + 72) = 0;
				itemFound = true;
				IPlayer.SystemMessage("Time has successfully extended.", TEXTCOLOR_GREEN);
			}
		}

		if (!itemFound)
		{
			IPlayer.BoxMsg("Please equip Costume Suit before using extension.");
			return Item.GetAmount();
		}

		(*(int(__thiscall **)(DWORD, void *, signed int, signed int))(*(DWORD*)ItemOffset + 120))((int)ItemOffset, IPlayer.GetOffset(), *(DWORD *)(*(DWORD *)((int)ItemOffset + 40) + 156) != 0 ? 43 : 9, -1);
		return Item.GetAmount();
	}

	if (IPlayer.IsOnline() && SkinTalisman.count(Item.CheckIndex()))
	{
		ConfigTimeTalisman t = SkinTalisman.find(Item.CheckIndex())->second;
		bool itemFound = false;

		if (IPlayer.GetBuffValue(BuffNames::custWeap)) {

			int CostumeItemIndex = IPlayer.GetBuffValue(BuffNames::custWeap);
			int CostumeItem = CPlayer::FindItem(IPlayer.GetOffset(), CostumeItemIndex, 1);
			IItem Costumex((void*)CostumeItem);

			if (CostumeItem && CItem::IsState(CostumeItem, 1)){
				if (!PetLifeCheck.count(Costumex.GetIID()))
				{
					IPlayer.BoxMsg("Costume Skin has no time to extend.");
					return Item.GetAmount();
				}

				int ExtendTime = t.time;
				int RemainingTime = PetLifeCheck.findValue(Costumex.GetIID()) - (int)time(0);
				int TotalTime = ExtendTime + RemainingTime;
				PetLifeCheck.replaceInsert(Costumex.GetIID(), (int)time(0) + TotalTime);

				CDBSocket::Write(89, "ddd", IPlayer.GetPID(), (int)time(0) + TotalTime, Costumex.GetIID());
				CPlayer::Write(IPlayer.GetOffset(), 0xFF, "ddd", 230, Costumex.GetIID(), TotalTime);
				*(DWORD*)((int)Costumex.GetOffset() + 68) = GetTickCount() + (2000 * TotalTime);
				*(DWORD*)((int)Costumex.GetOffset() + 72) = 0;
				itemFound = true;
				IPlayer.SystemMessage("Time has successfully extended.", TEXTCOLOR_GREEN);
			}
		}

		if (!itemFound)
		{
			IPlayer.BoxMsg("Please equip Costume Skin before using extension.");
			return Item.GetAmount();
		}

		(*(int(__thiscall **)(DWORD, void *, signed int, signed int))(*(DWORD*)ItemOffset + 120))((int)ItemOffset, IPlayer.GetOffset(), *(DWORD *)(*(DWORD *)((int)ItemOffset + 40) + 156) != 0 ? 43 : 9, -1);
		return Item.GetAmount();
	}

	if (IPlayer.IsOnline() && BuffedItems.count(Item.CheckIndex())) {
		std::vector<Buffs> BuffVec = BuffedItems.find(Item.CheckIndex())->second.BuffList;
		bool used = false;

		for (int i = 0; i < BuffVec.size(); i++) {
			Buffs buff = BuffVec[i];

			if (!IPlayer.IsBuff(buff.BuffId)) {
				IPlayer.SaveBuff(buff.BuffId, buff.Time, buff.Effect, buff.SBName, buff.SBKey);
				used = true;
			}
		}

		if (used)
			(*(int(__thiscall **)(DWORD, void *, signed int, signed int))(*(DWORD*)ItemOffset + 120))((int)ItemOffset, IPlayer.GetOffset(), *(DWORD *)(*(DWORD *)((int)ItemOffset + 40) + 156) != 0 ? 43 : 9, -1);
		else
			IPlayer.SystemMessage("Item already used.", TEXTCOLOR_RED);

		return Item.GetAmount();
	}

	if (IPlayer.IsOnline() && ItemReward.count(Item.CheckIndex())) {
		IPlayer.systemReward(ItemReward.find(Item.CheckIndex())->second);
		(*(int(__thiscall **)(DWORD, void *, signed int, signed int))(*(DWORD*)ItemOffset + 120))((int)ItemOffset, IPlayer.GetOffset(), *(DWORD *)(*(DWORD *)((int)ItemOffset + 40) + 156) != 0 ? 43 : 9, -1);
		return Item.GetAmount();
	}

	if (IPlayer.IsOnline() && Boxes.count(Item.CheckIndex())) {

		SBoxes t = Boxes.find(Item.CheckIndex())->second;
		int NumberOfItems = t.Amounts.size();

		if (CPlayer::GetInvenSize((int)IPlayer.GetOffset()) < IPlayer.MaxInventorySize() - NumberOfItems) {

			for (int i = 0; i < NumberOfItems; i++) {
				int Index = String2Int(t.Rewards[i]);
				int Amount = String2Int(t.Amounts[i]);

				int Item = CItem::CreateItem(Index, t.Prefix, Amount, -1);

				if (Item) {
					IItem xItemAdd((void*)Item);

					int Info = (t.Bound == 1) ? 128 : 0;

					if (t.Dss)
						*(DWORD*)(Item + 84) = t.Dss;

					if (t.Mix)
						Info += t.Mix;

					if (t.Bof)
						Info += 2097152;

					*(DWORD*)(Item + 48) = Info;

					if (xItemAdd.HighMemory()) {
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

					if (CPlayer::_InsertItem(IPlayer.GetOffset(), 7, Item) == 1)
					{
						if (xItemAdd.HighMemory() && (t.Attack || t.Magic)) {
							CDBSocket::Write(17, "ddbbb", *(DWORD *)(Item + 36), *(DWORD *)(Item + 32), 27, *(DWORD*)(Item + 100), 0);
							CDBSocket::Write(17, "ddbbb", *(DWORD *)(Item + 36), *(DWORD *)(Item + 32), 28, *(DWORD*)(Item + 104), 0);
							CDBSocket::Write(17, "ddbbb", *(DWORD *)(Item + 36), *(DWORD *)(Item + 32), 9, *(DWORD*)(Item + 112), 0);
							CDBSocket::Write(28, "ddbb", *(DWORD *)(Item + 36), *(DWORD *)(Item + 32), 2, *(DWORD*)(Item + 124));
						}

						if (t.ItemStat > 0) {
							itemStat.Enter();
							GetItemStat[*(DWORD *)(Item + 36)] = t.ItemStat;
							itemStat.Leave();
							CDBSocket::Write(90, "dd", t.ItemStat, *(DWORD *)(Item + 36));
							CItem::SendItemInfo((void*)Item, (int)IPlayer.GetOffset(), 92);
						}
					}
					else
						CBase::Delete((void*)Item);
				}
			}
			(*(int(__thiscall **)(DWORD, void *, signed int, signed int))(*(DWORD*)ItemOffset + 120))((int)ItemOffset, IPlayer.GetOffset(), *(DWORD *)(*(DWORD *)((int)ItemOffset + 40) + 156) != 0 ? 43 : 9, -1);
		}
		else
			IPlayer.SystemMessage("Your Inventory is full.", TEXTCOLOR_RED);

		return Item.GetAmount();
	}

	if (IPlayer.IsOnline() && Item.CheckIndex() == 1118)
	{
		IPlayer.SetHonor(1, 10, 0, 0, 0, 0, 0, 0, 0, 0);
		(*(int(__thiscall **)(DWORD, void *, signed int, signed int))(*(DWORD*)ItemOffset + 120))((int)ItemOffset, IPlayer.GetOffset(), *(DWORD *)(*(DWORD *)((int)ItemOffset + 40) + 156) != 0 ? 43 : 9, -1);
		return Item.GetAmount();
	}

	if (IPlayer.IsOnline() && Item.CheckIndex() == 1119)
	{
		IPlayer.SetHonor(3, 30, 0, 0, 0, 0, 0, 0, 0, 0);
		(*(int(__thiscall **)(DWORD, void *, signed int, signed int))(*(DWORD*)ItemOffset + 120))((int)ItemOffset, IPlayer.GetOffset(), *(DWORD *)(*(DWORD *)((int)ItemOffset + 40) + 156) != 0 ? 43 : 9, -1);
		return Item.GetAmount();
	}

	if (IPlayer.IsOnline() && Item.CheckIndex() == 1120)
	{
		IPlayer.SetHonor(5, 50, 0, 0, 0, 0, 0, 0, 0, 0);
		(*(int(__thiscall **)(DWORD, void *, signed int, signed int))(*(DWORD*)ItemOffset + 120))((int)ItemOffset, IPlayer.GetOffset(), *(DWORD *)(*(DWORD *)((int)ItemOffset + 40) + 156) != 0 ? 43 : 9, -1);
		return Item.GetAmount();
	}

	if (IPlayer.IsOnline() && Item.CheckIndex() == 1121)
	{
		IPlayer.SetHonor(10, 100, 0, 0, 0, 0, 0, 0, 0, 0);
		(*(int(__thiscall **)(DWORD, void *, signed int, signed int))(*(DWORD*)ItemOffset + 120))((int)ItemOffset, IPlayer.GetOffset(), *(DWORD *)(*(DWORD *)((int)ItemOffset + 40) + 156) != 0 ? 43 : 9, -1);
		return Item.GetAmount();
	}

	return CItemGeneral::Use(ItemOffset, PlayerOffset);
}