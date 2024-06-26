signed int __fastcall DefenseChangePrefix(void *Item, void* edx, int Player, int ID, int Chance, int Argument)
{

	IChar IPlayer((void*)Player);
	IItem IItem(Item);

	int CurrentPrefix = 0, NewPrefix = 0, AddPrefix = 0;

	if (!IPlayer.IsValid())
		return 0;

	if (IItem.GetInfo() & 4194304)
	{
		IPlayer.BoxMsg("Item is locked.");
		return 0;
	}

	if (CItem::IsState((int)IItem.GetOffset(), 1) || ID >= 0 && ID != 1)
		return 0;

	if (IItem.Prefix())
		CurrentPrefix = IItem.PrefixID();

	NewPrefix = CurrentPrefix;
	int Rate = CTools::Rate(1, 100);
	int CheckPolish = CItem::IsState((int)IItem.GetOffset(), 64);

	for (signed int i = 0; i < 2; ++i)
	{
		if (Rate <= (int)*(DWORD*)(Chance + 4 * i))
		{
			NewPrefix = *(DWORD *)(Argument + 4 * i);
			break;
		}
	}

	if (DisablePrefix.count((IItem.CheckIndex() + 100000)*NewPrefix) || DisablePrefix.count((IItem.CheckIndex() + 100000)*CurrentPrefix)) {
		IPlayer.BoxMsg("This talisman usage has been disabled for the following item.");
		return 0;
	}

	if (CurrentPrefix == NewPrefix)
	{
		if (CheckPolish)
		{
			CDBSocket::Write(21, "dddbb", IItem.GetIID(), IPlayer.GetID(), 64, 0, 255);
			CItem::SubState((int)IItem.GetOffset(), 64);
			CItem::SendItemInfo(IItem.GetOffset(), (int)IPlayer.GetOffset(), 92);
			return 1;
		}

		if (IItem.GetEndurance() >= 5)
			IItem.DecreaseEndurance(5);
		else
			IItem.DecreaseEndurance(IItem.GetEndurance());

		if (IItem.GetEndurance() <= 0)
		{
			CPlayer::Write(IPlayer.GetOffset(), 91, "db", IItem.GetIID(), IItem.GetEndurance());
			CDBSocket::Write(3, "ddwdbddd", IItem.GetIID(), IPlayer.GetID(), IItem.CheckIndex(), 1, 27, 0, 0, 0);

			if (CItem::GetLevel((int)IItem.GetOffset()) >= 40)
				CItem::InsertItem((int)IPlayer.GetOffset(), 27, 517, 0, 15, -1);

			CBase::Delete(IItem.GetOffset());
		}
		else {
			CPlayer::Write(IPlayer.GetOffset(), 91, "db", IItem.GetIID(), IItem.GetEndurance());
			CDBSocket::Write(18, "ddb", IItem.GetIID(), IPlayer.GetID(), IItem.GetEndurance());
		}
	}
	else {
		int CurrentInfo = 0;

		if (IItem.GetInfo())
			CurrentInfo = IItem.GetInfo();

		if (NewPrefix == dgConfigRead) {

			itemStat.Enter();
			int CurItemStat = GetItemStat.count(IItem.GetIID()) ? GetItemStat.find(IItem.GetIID())->second : 0;
			itemStat.Leave();
			if (!CurItemStat) {
				IPlayer.BoxMsg("Wrong item.");
				return 0;
			}

			int DemonGongStyle = (CurItemStat % 100000000) / 10000000;
			int CurGrade = ((CurItemStat % 10000000) / 1000000);
			int SecondDemonGongType = (CurItemStat % 1000000) / 100000;
			int SecondDemonGongStat = (CurItemStat % 100000) / 10000;

			if (!DemonGongStyle && !CurGrade && !SecondDemonGongStat && !SecondDemonGongType) {
				IPlayer.BoxMsg("Your armor is not enchanted with demon gong power.");
				return 0;
			}
			itemStat.Enter();
			GetItemStat[IItem.GetIID()] = CurItemStat - ((CurGrade * 1000000) + (DemonGongStyle * 10000000) + (SecondDemonGongType * 100000) + (SecondDemonGongStat * 10000));
			itemStat.Leave();
			CDBSocket::Write(90, "dd", CurItemStat - ((CurGrade * 1000000) + (DemonGongStyle * 10000000) + (SecondDemonGongType * 100000) + (SecondDemonGongStat * 10000)), IItem.GetIID());

			CPlayer::Write(IPlayer.GetOffset(), 255, "dddb", 224, IItem.GetIID(), 0, 0);

			CItem::SendItemInfo(IItem.GetOffset(), (int)IPlayer.GetOffset(), 92);
			IPlayer.SystemMessage("Your demon gong ability has been successfully removed from your armor.", TEXTCOLOR_DARKGREEN);
			return 1;
		}


		if (NewPrefix == insanityRead) {
			int SetGem = IItem.GetSetGem();
			if (SetGem < 236 || SetGem > 240) {
				IPlayer.BoxMsg("Item must already be equipped with spirit of insanity.");
				return 0;
			}

			std::vector<int> range;
			for (int i = 36; i <= 40; i++) {
				if ((200 + i) != SetGem)
					range.push_back(i);
			}
			srand(time(0));
			std::random_shuffle(range.begin(), range.end());

			int NewType = 200 + range.front();
			int Type = 1;

			IItem.SetSetGem(NewType);
			CDBSocket::Write(87, "ddd", IPlayer.GetPID(), NewType, IItem.GetIID());
			CItem::SendItemInfo(IItem.GetOffset(), (int)IPlayer.GetOffset(), 92);
			CPlayer::Write(IPlayer.GetOffset(), 0xFF, "ddb", 241, IItem.GetIID(), Type);

			IPlayer.SystemMessage("Your new spirit of insanity has successfully been applied.", TEXTCOLOR_DARKGREEN);
			return 1;
		}

		if (NewPrefix == qigongRead) {

			int ItemStat = 0;
			itemStat.Enter();
			if (GetItemStat.count(IItem.GetIID()))
				ItemStat = GetItemStat.find(IItem.GetIID())->second;
			itemStat.Leave();

			int QigongGradeCheck = ItemStat % 100;

			if (QigongGradeCheck < 71 || QigongGradeCheck > 80) {
				IPlayer.BoxMsg("Item must already be equipped with qigong spirit of insanity.");
				return 0;
			}

			std::vector<int> range;
			for (int i = 71; i <= 80; i++) {
				if (i != QigongGradeCheck)
					range.push_back(i);
			}
			srand(time(0));
			std::random_shuffle(range.begin(), range.end());

			int Adding = range.front();
			itemStat.Enter();
			GetItemStat[IItem.GetIID()] = (ItemStat + Adding) - QigongGradeCheck;
			itemStat.Leave();
			CDBSocket::Write(90, "dd", (ItemStat + Adding) - QigongGradeCheck, IItem.GetIID());
			CItem::SendItemInfo(IItem.GetOffset(), (int)IPlayer.GetOffset(), 92);
			CPlayer::Write(IPlayer.GetOffset(), 0xFF, "ddd", 235, IItem.GetIID(), Adding);

			IPlayer.SystemMessage("Your new qigong spirit of insanity has successfully been applied.", TEXTCOLOR_DARKGREEN);
			return 1;
		}

		if (NewPrefix == BofConfigRead)
		{
			if (CurrentInfo & 2097152)
			{
				IPlayer.BoxMsg("Bead of Fire is already equipped.");
				return 0;
			}
			else if (CItem::GetLevel((int)IItem.GetOffset()) < 46 || CItem::GetLevel((int)IItem.GetOffset()) > 120)
			{
				IPlayer.BoxMsg("Bead of Fire can not be equipped on this armor.");
				return 0;
			}
			else {
				CDBSocket::Write(21, "dddbb", IItem.GetIID(), IPlayer.GetID(), IItem.GetInfo(), 0, 0);
				IItem.SetInfo(2097152 + CurrentInfo);
				CDBSocket::Write(21, "dddbb", IItem.GetIID(), IPlayer.GetID(), 2097152 + CurrentInfo, 8, 7);
				CItem::SendItemInfo(IItem.GetOffset(), (int)IPlayer.GetOffset(), 92);
				IPlayer.BoxMsg("Equipping the Bead of Fire has succeeded.");
				if (BofNotices){
					std::string msg = (std::string)IPlayer.GetName();
					msg = msg + " has enchanted with Bead of Fire";
					int textColor = NOTICECOLOR_WHITE; // Default color
					int messageType = 2; // Default messageType

					RewardMessage reward;
					reward.message = msg;
					reward.textColor = textColor;
					reward.messageType = messageType;

					PlayerRewardNotice.push_back(reward);
					ToNoticeWebhook(msg.c_str());
				}
				return 1;
			}
		}

		int armorClass = IItem.GetClass();
		int isHelmet = (IItem.GetType() == 2);
		int isArmor = (IItem.GetType() == 3);
		int isBoots = (IItem.GetType() == 6);
		int isGloves = (IItem.GetType() == 5);
		int isShorts = (IItem.GetType() == 4);


	//	int grade = HighGradeBof.find(NewPrefix)->second;
		int prefix = HighGradeBof.find(NewPrefix)->first;

		if (HighGradeBof.count(NewPrefix) || NewPrefix == Bof2ConfigRead)
		{

			//if (CItem::GetLevel((int)IItem.GetOffset()) == 52 && grade == 50)
			//	grade = 52;

			//if (CItem::GetLevel((int)IItem.GetOffset()) != grade)
			//{
			//	IPlayer.BoxMsg("Bead of Fire can not be equipped on this armor.");
			//	return 0;
			//}
			if (CurrentInfo & 2097152)
			{
				IPlayer.BoxMsg("Bead of Fire is already equipped.");
				return 0;
			}
			else if (CItem::GetLevel((int)IItem.GetOffset()) < 46 || CItem::GetLevel((int)IItem.GetOffset()) > 100)
			{
				IPlayer.BoxMsg("Bead of Fire can not be equipped on this armor.");
				return 0;
			}
			else {
				int grade = CItem::GetLevel((int)IItem.GetOffset());
				CDBSocket::Write(21, "dddbb", IItem.GetIID(), IPlayer.GetID(), IItem.GetInfo(), 0, 0);
				IItem.SetInfo(2097152 + CurrentInfo);
				CDBSocket::Write(21, "dddbb", IItem.GetIID(), IPlayer.GetID(), 2097152 + CurrentInfo, 8, 7);
				CItem::SendItemInfo(IItem.GetOffset(), (int)IPlayer.GetOffset(), 92);
				IPlayer.BoxMsg("Equipping the Bead of Fire has succeeded.");
				std::string msg = (std::string)IPlayer.GetName();
				if (CItem::GetLevel((int)IItem.GetOffset()) == 52)
				{
						msg = msg + " has enchanted Iron Shield with Gong with Bead of Fire";
				}
				else if (isBoots){
					if (armorClass == 0)
						msg = msg + " has enchanted " + GetKnightBootsName(grade) + " with Bead of Fire";
					else if (armorClass == 1)
						msg = msg + " has enchanted " + GetMageShoesName(grade) + " with Bead of Fire";
					else if (armorClass == 2)
						msg = msg + " has enchanted " + GetArcherBootsName(grade) + " with Bead of Fire";
					else
						msg = msg + " has enchanted " + GetThiefBootsName(grade) + " with Bead of Fire";
				}
				else if (isArmor) {
					// Handle Armor messages for all classes and grades similarly
					std::string armorName = "Unknown Armor";
					if (armorClass == 0) {  // Knight
						armorName = GetKnightArmorName(grade);
					}
					else if (armorClass == 1) {  // Mage
						armorName = GetMageArmorName(grade);
					}
					else if (armorClass == 2) {  // Archer
						armorName = GetArcherArmorName(grade);
					}
					else   // Thief
						armorName = GetThiefSuitName(grade);

					msg = msg + " has enchanted " + armorName + " with Bead of Fire";
				}
				else if (isHelmet) {
					// Handle Helmet messages for all classes and grades similarly
					std::string helmetName = "Unknown Helmet";
					if (armorClass == 0) {  // Knight
						helmetName = GetKnightHelmetName(grade);
					}
					else if (armorClass == 1) {  // Mage
						helmetName = GetMageHairDecorationName(grade);
					}
					else if (armorClass == 2) {  // Archer
						helmetName = GetArcherHelmetName(grade);
					}
					else   // Thief
						helmetName = GetThiefHoodName(grade);
					msg = msg + " has enchanted " + helmetName + " with Bead of Fire";
				}
				else if (isGloves) {
					// Handle Gloves messages for all classes and grades similarly
					std::string glovesName = "Unknown Gloves";
					if (armorClass == 0) {  // Knight
						glovesName = GetKnightGlovesName(grade);
					}
					else if (armorClass == 1) {  // Mage
						glovesName = GetMageGlovesName(grade);
					}
					else if (armorClass == 2) {  // Archer
						glovesName = GetArcherGlovesName(grade);
					}
					else if (armorClass == 3) {  // Thief
						glovesName = GetThiefGlovesName(grade);
					}
					msg = msg + " has enchanted " + glovesName + " with Bead of Fire";
				}
				else if (isShorts) {
					// Handle Shorts messages for all classes and grades similarly
					std::string shortsName = "Unknown Shorts";
					if (armorClass == 0) {  // Knight
						shortsName = GetKnightShortsName(grade);
					}
					else if (armorClass == 1) {  // Mage
						shortsName = GetMageShortsName(grade);
					}
					else if (armorClass == 2) {  // Archer
						shortsName = GetArcherShortsName(grade);
					}
					else if (armorClass == 3) {  // Thief
						shortsName = GetThiefShortsName(grade);
					}
					msg = msg + " has enchanted " + shortsName + " with Bead of Fire";
				}

				if (!msg.empty() && IPlayer.IsValid()) {
					int textColor = NOTICECOLOR_WHITE; // Default color
					int messageType = 2; // Default messageType

					RewardMessage reward;
					reward.message = msg;
					reward.textColor = textColor;
					reward.messageType = messageType;

					PlayerRewardNotice.push_back(reward);
					ToNoticeWebhook(msg.c_str());
				}
				return 1;
			}
		}

		if (WeaponReplace.count((IItem.CheckIndex() + 100000)*NewPrefix) && WeaponReplaceIndex.count((IItem.CheckIndex() + 100000)*NewPrefix))
		{
			std::string msg = (std::string)IPlayer.GetName();

			if (WeaponReplace.find((IItem.CheckIndex() + 100000)*NewPrefix)->second == NewPrefix)
			{
				if (CBase::IsDeleted((int)Item))
					return 0;

				if (IPlayer.IsBuff(328))
					return 0;
				else
					IPlayer.Buff(328, 3, 0);

				int ReplacePrefix = 0, ReplaceItem = 0, ReplaceInfo = 0, ReplaceDef = 0, ReplaceEva = 0, ReplaceGem = 0;
				int ItemStat = 0;

				itemStat.Enter();
				if (GetItemStat.count(IItem.GetIID()))
					ItemStat = GetItemStat.find(IItem.GetIID())->second;
				itemStat.Leave();

				if (*(DWORD *)((int)Item + 44))
					ReplacePrefix = *(DWORD *)(*(DWORD *)((int)Item + 44) + 32);

				if (*(DWORD *)((int)Item + 48))
					ReplaceInfo = *(DWORD *)((int)Item + 48);

				if (*(DWORD *)((int)Item + 108))
					ReplaceDef = *(DWORD *)((int)Item + 108);

				if (IItem.HighMemory()) {
					if (*(DWORD *)((int)Item + 116))
						ReplaceEva = *(DWORD *)((int)Item + 116);

					if (*(DWORD *)((int)Item + 84))
						ReplaceGem = *(DWORD *)((int)Item + 84);
				}

				int ItemNewIndex = IItem.CheckIndex();
				int DeleteCheck = (*(int(__thiscall **)(DWORD, void *, signed int, signed int))(*(DWORD*)Item + 120))((int)Item, IPlayer.GetOffset(), 9, -1);

				if (!DeleteCheck)
				{
					ReplaceItem = CItem::CreateItem(WeaponReplaceIndex.find((ItemNewIndex + 100000)*NewPrefix)->second, ReplacePrefix, 1, -1);

					if (ReplaceItem)
					{
						CIOObject::AddRef(ReplaceItem);
						if (ReplaceInfo)
							*(DWORD *)(ReplaceItem + 48) = ReplaceInfo;
						if (ReplaceDef)
							*(DWORD *)(ReplaceItem + 108) = ReplaceDef;
						if (ReplaceEva)
							*(DWORD *)(ReplaceItem + 116) = ReplaceEva;
						if (ReplaceGem)
							*(DWORD *)(ReplaceItem + 84) = ReplaceGem;

						if (CPlayer::_InsertItem(IPlayer.GetOffset(), 27, ReplaceItem) != 1)
						{
							CConsole::Red("Real time armor insert item Null error [PID (%d)] ", IPlayer.GetPID());
							CBase::Delete((void *)ReplaceItem);
							CIOObject::Release((void *)ReplaceItem);
							return 0;
						}

						CIOObject::Release((void *)ReplaceItem);
						itemStat.Enter();
						GetItemStat[*(DWORD *)(ReplaceItem + 36)] = ItemStat;
						itemStat.Leave();

						CDBSocket::Write(90, "dd", ItemStat, *(DWORD *)(ReplaceItem + 36));
						CDBSocket::Write(87, "ddd", IPlayer.GetPID(), *(DWORD *)(ReplaceItem + 84), *(DWORD *)(ReplaceItem + 36));
						CDBSocket::Write(21, "dddbb", *(DWORD *)(ReplaceItem + 36), *(DWORD *)(ReplaceItem + 32), *(DWORD *)(ReplaceItem + 48), 8, 7);

						if (ReplaceDef)
							CDBSocket::Write(17, "ddbbb", *(DWORD *)(ReplaceItem + 36), *(DWORD *)(ReplaceItem + 32), 15, *(DWORD *)(ReplaceItem + 108), 0);
						if (ReplaceEva)
							CDBSocket::Write(17, "ddbbb", *(DWORD *)(ReplaceItem + 36), *(DWORD *)(ReplaceItem + 32), 10, *(DWORD *)(ReplaceItem + 116), 0);

						CItem::SendItemInfo((void*)ReplaceItem, (int)IPlayer.GetOffset(), 92);
						CPlayer::Write(IPlayer.GetOffset(), 0xFF, "ddddd", 242, 0, 0, 128, 255);
						std::string& successMsg = WeaponReplaceMsg.find((ItemNewIndex + 100000)*NewPrefix)->second;
						if (WeaponReplaceMsg.count((ItemNewIndex + 100000)*NewPrefix) && !successMsg.empty()){
							//CPlayer::WriteAll(0xFF, "dsd", 247, msg.c_str(), NOTICECOLOR_PINK);
							msg = msg + " " + successMsg;
							if (!msg.empty() && IPlayer.IsValid()) {
								int textColor = NOTICECOLOR_PINK; // Default color
								int messageType = 2; // Default messageType
								RewardMessage reward;
								reward.message = msg;
								reward.textColor = textColor;
								reward.messageType = messageType;

								PlayerRewardNotice.push_back(reward);

								std::string avatar = Avatar;
								std::string playerName = std::string(IPlayer.GetName());
								std::string url = NoticeWebHook;
								SendWebhookMessage(url, msg.c_str(), avatar.c_str(), std::string(playerName));
								ToNoticeWebhook(msg.c_str());
							}
						}
					}
				}
				else {
					return 0;
				}

				return 1;
			}
		}

		if (WeaponReplacePrefix.count(NewPrefix))
		{
			IPlayer.BoxMsg("Enchanting item and the talisman are different.");
			return 0;
		}

		if (ArmorPimpConfig.count(NewPrefix) && IItem.HighMemory())
		{
			*(DWORD *)((int)Item + 108) = ArmorPimpConfig.find(NewPrefix)->second;
			*(DWORD *)((int)Item + 116) = 1;
			CDBSocket::Write(17, "ddbbb", *(DWORD *)((int)Item + 36), *(DWORD *)((int)Item + 32), 15, *(DWORD *)((int)Item + 108), 0);
			CDBSocket::Write(17, "ddbbb", *(DWORD *)((int)Item + 36), *(DWORD *)((int)Item + 32), 10, *(DWORD *)((int)Item + 116), 0);
			CItem::SendItemInfo(IItem.GetOffset(), (int)IPlayer.GetOffset(), 92);
			return 1;
		}

		AddPrefix = CItem::FindPrefix(NewPrefix);

		if (!AddPrefix)
			return 0;

		*(DWORD *)((int)IItem.GetOffset() + 44) = AddPrefix;
		CDBSocket::Write(19, "ddbb", IItem.GetIID(), IPlayer.GetID(), NewPrefix);

		if (CheckPolish)
			CItem::SubState((int)IItem.GetOffset(), 64);

		CItem::SendItemInfo(IItem.GetOffset(), (int)IPlayer.GetOffset(), 92);
	}

	return 1;
}