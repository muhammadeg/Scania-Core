void LearnSkill(IChar IPlayer, int SkillID, bool Skillbook) {
	int Value = 0, Argument = 0, Arg = 0, Check = 0, Recheck = 0;
	Value = SkillID + (*((DWORD*)((DWORD*)((int)IPlayer.GetOffset() + 624)) + 1) << 16);
	Undefined::CreateSkillValue((void*)0x004E218C, (int)&Argument, (int)&Value);
	Check = Undefined::Check((int)0x004E218C, (int)&Arg);

	if (*(DWORD*)&Argument != *(DWORD*)Check)
	{
		Recheck = *(DWORD*)(Undefined::GetValue(&Argument) + 4);

		if ((*(int(__thiscall**)(int, DWORD, DWORD))(*(DWORD*)Recheck + 60))(Recheck, *(DWORD *)((int)IPlayer.GetOffset() + 60), *(DWORD*)((int)IPlayer.GetOffset() + 464)))
		{
			if (Undefined::CheckSkillValue((DWORD*)((int)IPlayer.GetOffset() + 624), *(DWORD*)(Recheck + 20), *(DWORD *)(Recheck + 24)))
			{
				Recheck = (int)Undefined::CheckSkillX((void*)Recheck);
				Undefined::CheckSkillY(Recheck, SkillID, 1);
				(*(void(__thiscall **)(int, DWORD, DWORD, DWORD))(*(DWORD*)Recheck + 8))(Recheck, (int)IPlayer.GetOffset(), 0, 0);
				*((DWORD*)(DWORD*)((int)IPlayer.GetOffset() + 624) + SkillID + 2) = Recheck;
				CDBSocket::Write(9, "dbw", IPlayer.GetPID(), SkillID, 1);
				CPlayer::Write(IPlayer.GetOffset(), 81, "bb", SkillID, 1);
				if (!Skillbook)
					IPlayer.RemoveSkillPoint(1);
			}
		}
	}
}

void SkillLearnPacket(IChar IPlayer, int SkillID) {
	if (SkillID == 85) SkillID = 87;
	else if (SkillID == 86) SkillID = 88;
	else if (SkillID == 87) SkillID = 89;

	if (SkillID == 79)
		return;

	if (SkillChecks.count((IPlayer.GetClass() * 1000) + SkillID)) {
		SkillLearn sLearn = SkillChecks.find((IPlayer.GetClass() * 1000) + SkillID)->second;

		bool SpecCheck = false;
		for (int i = 0; i < sLearn.Specialties.size(); i++) {
			if (IPlayer.GetSpecialty() == sLearn.Specialties[i]) {
				SpecCheck = true;
				break;
			}
		}

		if (!SpecCheck) {
			IPlayer.SystemMessage("Wrong Specialty for this skill.", TEXTCOLOR_RED);
			return;
		}

		if (IPlayer.GetLevel() < sLearn.Levels[0]) {
			IPlayer.SystemMessage("This skill can be learnable at level " + Int2String(sLearn.Levels[0]) + ".", TEXTCOLOR_RED);
			return;
		}

		int pSkill = IPlayer.GetSkillPointer(SkillID);

		if (pSkill) {
			ISkill xSkill((void*)pSkill);
			int Grade = xSkill.GetGrade();
			int MaxGrade = sLearn.Levels.size();

			if (Grade >= MaxGrade) {
				IPlayer.SystemMessage("You have already reached the max grade for this skill.", TEXTCOLOR_RED);
				return;
			}

			if (sLearn.Levels[Grade] > IPlayer.GetLevel()) {
				IPlayer.SystemMessage("You can not upgrade to the upper grade yet.", TEXTCOLOR_RED);
				return;
			}
		}

		goto LABEL_2;
	}


	if (IPlayer.GetLevel() >= 81 && SkillID >= 87 && SkillID <= 89 && IPlayer.GetSpecialty() > 1)
	{
		if (!MysteryEnable) {
			IPlayer.SystemMessage("Mystery skills are disabled", TEXTCOLOR_RED);
			return;
		}

		int OTP = IPlayer.GetSkillPointer(87);
		int EVA = IPlayer.GetSkillPointer(88);
		int DEF = IPlayer.GetSkillPointer(89);

		if (OTP || EVA || DEF)
		{
			IPlayer.SystemMessage("You can only learn one mystery skill.", TEXTCOLOR_RED);
			return;
		}

		if (SkillID == 87)
		{
			int Value = 0, Argument = 0, Arg = 0, Check = 0, Recheck = 0;
			Value = SkillID + (*((DWORD*)((DWORD*)((int)IPlayer.GetOffset() + 624)) + 1) << 16);
			Undefined::CreateSkillValue((void*)0x004E218C, (int)&Argument, (int)&Value);
			Check = Undefined::Check((int)0x004E218C, (int)&Arg);

			if (*(DWORD*)&Argument != *(DWORD*)Check)
			{
				Recheck = *(DWORD*)(Undefined::GetValue(&Argument) + 4);

				if ((*(int(__thiscall**)(int, DWORD, DWORD))(*(DWORD*)Recheck + 60))(Recheck, *(DWORD *)((int)IPlayer.GetOffset() + 60), *(DWORD*)((int)IPlayer.GetOffset() + 464)))
				{
					if (Undefined::CheckSkillValue((DWORD*)((int)IPlayer.GetOffset() + 624), *(DWORD*)(Recheck + 20), *(DWORD *)(Recheck + 24)))
					{
						Recheck = (int)Undefined::CheckSkillX((void*)Recheck);
						Undefined::CheckSkillY(Recheck, SkillID, 1);
						(*(void(__thiscall **)(int, DWORD, DWORD, DWORD))(*(DWORD*)Recheck + 8))(Recheck, (int)IPlayer.GetOffset(), 0, 0);
						*((DWORD*)(DWORD*)((int)IPlayer.GetOffset() + 624) + SkillID + 2) = Recheck;
						IPlayer.AddOTP(8);
						CDBSocket::Write(9, "dbw", IPlayer.GetPID(), SkillID, 1);
						CPlayer::Write(IPlayer.GetOffset(), 81, "bb", 85, 1);
					}
				}
			}

			if (IPlayer.GetLevel() > 81)
				AutoLearn((void*)(DWORD*)((int)IPlayer.GetOffset() + 624), 0, 0);
		}

		if (SkillID == 88)
		{
			int Value = 0, Argument = 0, Arg = 0, Check = 0, Recheck = 0;
			Value = SkillID + (*((DWORD*)((DWORD*)((int)IPlayer.GetOffset() + 624)) + 1) << 16);
			Undefined::CreateSkillValue((void*)0x004E218C, (int)&Argument, (int)&Value);
			Check = Undefined::Check((int)0x004E218C, (int)&Arg);

			if (*(DWORD*)&Argument != *(DWORD*)Check)
			{
				Recheck = *(DWORD*)(Undefined::GetValue(&Argument) + 4);

				if ((*(int(__thiscall**)(int, DWORD, DWORD))(*(DWORD*)Recheck + 60))(Recheck, *(DWORD *)((int)IPlayer.GetOffset() + 60), *(DWORD*)((int)IPlayer.GetOffset() + 464)))
				{
					if (Undefined::CheckSkillValue((DWORD*)((int)IPlayer.GetOffset() + 624), *(DWORD*)(Recheck + 20), *(DWORD *)(Recheck + 24)))
					{
						Recheck = (int)Undefined::CheckSkillX((void*)Recheck);
						Undefined::CheckSkillY(Recheck, SkillID, 1);
						(*(void(__thiscall **)(int, DWORD, DWORD, DWORD))(*(DWORD*)Recheck + 8))(Recheck, (int)IPlayer.GetOffset(), 0, 0);
						*((DWORD*)(DWORD*)((int)IPlayer.GetOffset() + 624) + SkillID + 2) = Recheck;
						IPlayer.AddEva(6);
						CDBSocket::Write(9, "dbw", IPlayer.GetPID(), SkillID, 1);
						CPlayer::Write(IPlayer.GetOffset(), 81, "bb", 86, 1);
					}
				}
			}

			if (IPlayer.GetLevel() > 81)
				AutoLearn((void*)(DWORD*)((int)IPlayer.GetOffset() + 624), 0, 0);
		}

		if (SkillID == 89)
		{
			int Value = 0, Argument = 0, Arg = 0, Check = 0, Recheck = 0;
			Value = SkillID + (*((DWORD*)((DWORD*)((int)IPlayer.GetOffset() + 624)) + 1) << 16);
			Undefined::CreateSkillValue((void*)0x004E218C, (int)&Argument, (int)&Value);
			Check = Undefined::Check((int)0x004E218C, (int)&Arg);

			if (*(DWORD*)&Argument != *(DWORD*)Check)
			{
				Recheck = *(DWORD*)(Undefined::GetValue(&Argument) + 4);

				if ((*(int(__thiscall**)(int, DWORD, DWORD))(*(DWORD*)Recheck + 60))(Recheck, *(DWORD *)((int)IPlayer.GetOffset() + 60), *(DWORD*)((int)IPlayer.GetOffset() + 464)))
				{
					if (Undefined::CheckSkillValue((DWORD*)((int)IPlayer.GetOffset() + 624), *(DWORD*)(Recheck + 20), *(DWORD *)(Recheck + 24)))
					{
						Recheck = (int)Undefined::CheckSkillX((void*)Recheck);
						Undefined::CheckSkillY(Recheck, SkillID, 1);
						(*(void(__thiscall **)(int, DWORD, DWORD, DWORD))(*(DWORD*)Recheck + 8))(Recheck, (int)IPlayer.GetOffset(), 0, 0);
						*((DWORD*)(DWORD*)((int)IPlayer.GetOffset() + 624) + SkillID + 2) = Recheck;
						IPlayer.AddDef(31);
						CDBSocket::Write(9, "dbw", IPlayer.GetPID(), SkillID, 1);
						CPlayer::Write(IPlayer.GetOffset(), 81, "bb", 87, 1);
					}
				}
			}

			if (IPlayer.GetLevel() > 81)
				AutoLearn((void*)(DWORD*)((int)IPlayer.GetOffset() + 624), 0, 0);
		}

		return;
	}

	if (IPlayer.GetClass() == 0 && ((SkillID >= 37 && SkillID <= 44) || (SkillID >= 87 && SkillID <= 89) || SkillID == 70 || SkillID == 71 || SkillID == 82))
	{
		int SkillPointer = IPlayer.GetSkillPointer(SkillID);

		if (!SkillPointer)
		{
			if (IPlayer.GetSkillPoint() <= 0 || !SkillUpgradeCheck(IPlayer.GetOffset(), SkillID, 0))
				return;
		}
	}

	if (IPlayer.GetClass() == 1 && ((SkillID >= 63 && SkillID <= 76) || (SkillID >= 87 && SkillID <= 89) || SkillID == 82))
	{
		int SkillPointer = IPlayer.GetSkillPointer(SkillID);

		if (!SkillPointer)
		{
			if (IPlayer.GetSkillPoint() <= 0 || !SkillUpgradeCheck(IPlayer.GetOffset(), SkillID, 0))
				return;
		}
	}

	if (IPlayer.GetClass() == 2 && ((SkillID >= 46 && SkillID <= 51) || (SkillID >= 87 && SkillID <= 89) || SkillID == 82))
	{
		int SkillPointer = IPlayer.GetSkillPointer(SkillID);

		if (!SkillPointer)
		{
			if (IPlayer.GetSkillPoint() <= 0 || !SkillUpgradeCheck(IPlayer.GetOffset(), SkillID, 0))
				return;
		}
	}

	if (IPlayer.GetClass() == 3 && ((SkillID >= 0 && SkillID <= 37) || (SkillID >= 87 && SkillID <= 89) || SkillID == 70 || SkillID == 63))
	{
		int SkillPointer = IPlayer.GetSkillPointer(SkillID);

		if (!SkillPointer)
		{
			if (IPlayer.GetSkillPoint() <= 0 || !SkillUpgradeCheck(IPlayer.GetOffset(), SkillID, 0))
				return;
		}
	}

	if (IPlayer.GetClass() == 4 && SkillID >= 0 && SkillID <= 89)
	{
		int SkillPointer = IPlayer.GetSkillPointer(SkillID);

		if (!SkillPointer)
		{
			if (IPlayer.GetSkillPoint() <= 0 || !SkillUpgradeCheck(IPlayer.GetOffset(), SkillID, 0))
				return;
		}
	}

	if (SkillID >= 90)
		return;

	if (IPlayer.GetClass() == 3 && (SkillID == 80 || SkillID == 81)) {
		int SKPointer = IPlayer.GetSkillPointer(SkillID);

		if (!SKPointer && IPlayer.GetSkillPoint()) {
			IPlayer.RemoveSkillPoint(1);
			IPlayer.Buff(BuffNames::Artillery, BuffNames::BuffTime, 0);
			CPlayer::Write(IPlayer.GetOffset(), 81, "bb", SkillID, 1);
			CDBSocket::Write(9, "dbw", IPlayer.GetPID(), SkillID, IPlayer.GetSkillPoint());
			return;
		}
	}

LABEL_2:
	if (*(DWORD *)((int)IPlayer.GetOffset() + 548) > 0)
		CSkill::LearnSkill((DWORD*)((int)IPlayer.GetOffset() + 624), SkillID);
}

void upgradeSkill(IChar IPlayer, int SkillID) {
	int SkillPointer = IPlayer.GetSkillPointer(SkillID);

	if (SkillPointer)
	{
		ISkill xSkill((void*)SkillPointer);

		if (IPlayer.GetSkillPoint() > 0 && xSkill.GetGrade() < 6)
		{
			CDBSocket::Write(10, "ddbw", IPlayer.GetPID(), SkillID, xSkill.GetGrade() + 1, 56);
			CPlayer::Write(IPlayer.GetOffset(), 81, "bb", SkillID, xSkill.GetGrade() + 1);
			*(DWORD*)((int)xSkill.GetOffset() + 8) = xSkill.GetGrade() + 1;
			IPlayer.RemoveSkillPoint(1);
		}
	}
}

void updateSatiety(IChar IPlayer, int Value) {
	int SatietyGet = IPlayer.GetBuffValue(BuffNames::Satiety);
	Value = Value > 30 ? Value - SatietyGet : Value;
	if (IPlayer.IsBuff(349))
		IPlayer.AddHp(Value / 5);
	int Satiety = SatietyGet + Value;
	int IID = IPlayer.GetBuffValue(BuffNames::RidingIID);
	itemStat.Enter();
	int curValue = GetItemStat.count(IID) ? GetItemStat.find(IID)->second : 0;
	GetItemStat[IID] = curValue + (Value * 100);
	itemStat.Leave();
	CDBSocket::Write(90, "dd", curValue + (Value * 100), IID);
	IPlayer.UpdateBuff(BuffNames::Satiety, BuffNames::BuffTime, Satiety);
	CPlayer::Write(IPlayer.GetOffset(), 0xFE, "ddd", 200, IID, (1728 * Satiety));
}

void __fastcall Packet(__int32 Player, void *edx, int packet, void *pPacket, int pPos)
{
	IChar IPlayer((void*)Player);
	Interface<ITools> Tools;
	if (IPlayer.IsOnline() && IPlayer.GetPID())
	{
		if (PacketSpamConf.count(packet)) {
			int CurTime = PacketSpam.count((IPlayer.GetPID() * 1000) + packet) ? PacketSpam.findValue((IPlayer.GetPID() * 1000) + packet) : 0;
			PacketSpam.replaceInsert((IPlayer.GetPID() * 1000) + packet, GetTickCount() + PacketSpamConf.find(packet)->second);
			if (CurTime >= GetTickCount()) {
				IPlayer.SystemMessage("Please try again in a few moments.", TEXTCOLOR_RED);
				return;
			}
		}

		int PlayerBRefresh = IPlayer.GetRefreshCheck();
		if (!PlayerBRefresh)
			IPlayer.SetRefreshCheck(GetTickCount() + 990);

		if (PlayerBRefresh <= GetTickCount()) {
			CChar::RefreshBuff((int)Player);
			IPlayer.SetRefreshCheck(GetTickCount() + 990);
		}

		if (TrackerActive && Tracker.count(IPlayer.GetName())) {
			std::string PCName = "Unknown";
			PCName = User.find(IPlayer.GetPID())->second.PCName;

			std::string Dato = "./Tracker/" + Tracker.find(IPlayer.GetName())->second;
			std::fstream DGLOG;
			DGLOG.open(Dato, std::fstream::in | std::fstream::out | std::fstream::app);
			DGLOG << Time::GetTime() << " [Name]: '" << IPlayer.GetName() << "' [PC Name]: '" + PCName << "' [IP]: '" << IPlayer.GetIP() << "' [Packet]: " << packet << std::endl;
			DGLOG.close();
		}

		if ((packet == 31 || packet == 61) && IPlayer.IsBuff(349))
			return;

		if (Restri) {

			if ((packet == 58 || packet == 67) && Restrictions.count(IPlayer.GetPID()) && Restrictions.find(IPlayer.GetPID())->second.Shop == 0) {
				IPlayer.CloseWindow("bazaa");
				IPlayer.SystemMessage("You are not allowed to be using this system.", TEXTCOLOR_RED);
				return;
			}

			if ((packet == 34 || packet == 35) && Restrictions.count(IPlayer.GetPID()) && Restrictions.find(IPlayer.GetPID())->second.Trade == 0) {
				IPlayer.SystemMessage("You are not allowed to be using this system.", TEXTCOLOR_RED);
				return;
			}

			if (packet == 32 && Restrictions.count(IPlayer.GetPID()) && Restrictions.find(IPlayer.GetPID())->second.Pick == 0) {
				IPlayer.SystemMessage("You are not allowed to be using this system.", TEXTCOLOR_RED);
				return;
			}

			if ((packet == 44 || packet == 45) && Restrictions.count(IPlayer.GetPID()) && Restrictions.find(IPlayer.GetPID())->second.Party == 0) {
				IPlayer.SystemMessage("You are not allowed to be using this system.", TEXTCOLOR_RED);
				return;
			}

			if ((packet == 80 || packet == 81) && Restrictions.count(IPlayer.GetPID()) && Restrictions.find(IPlayer.GetPID())->second.Duel == 0) {
				IPlayer.SystemMessage("You are not allowed to be using this system.", TEXTCOLOR_RED);
				return;
			}
			if (packet == 49 && Restrictions.count(IPlayer.GetPID()) && Restrictions.find(IPlayer.GetPID())->second.Storage == 0) {
				IPlayer.SystemMessage("You are not allowed to be using this system.", TEXTCOLOR_RED);
				return;
			}
		}

		if ((packet == 44 || packet == 45) && (IPlayer.IsBuff(BuffNames::Fighter) || IPlayer.IsBuff(902) || IPlayer.IsBuff(903) || IPlayer.IsBuff(373) || IPlayer.IsBuff(374))) {
			IPlayer.SystemMessage("You can not use party during battle.", TEXTCOLOR_RED);
			return;
		}

		/*if (packet == 32) {
			int a1 = 0, a2 = 0, a3 = 0;
			char a4 = 0;
			CPacket::Read((char*)pPacket, (char*)pPos, "dddb", &a1, &a2, &a3, &a4);

			if (a4 == 1) {
			if (!IPlayer.GetBuffValue(BuffNames::PetPick))
			return;
			}
			}*/



		if (packet == 18) {
			char type = 0;
			int z = 0;
			CPacket::Read((char*)pPacket, (char*)pPos, "bd", &type, &z);

			if ((type >= 0 && type <= 2) && !z && !IPlayer.isDead() && !IPlayer.isAssassin()) {
				IPlayer.Teleport(IPlayer.GetMap(), IPlayer.GetX(), IPlayer.GetY());
				return;
			}
		}

		if (packet == 22) {
			int offset = 0;
			CPacket::Read((char*)pPacket, (char*)pPos, "d", &offset);
			if (offset < 0) {
				npcLock.Enter();
				int Counted = NPCSummoned.count(offset);
				npcLock.Leave();
				if (Counted) {
					npcLock.Enter();
					SummonNPC npc = NPCSummoned.find(offset)->second;
					npcLock.Leave();
					int TimeLeft = npc.Time - (int)time(0);

					if (TimeLeft > 0)
						CPlayer::Write((void*)Player, 0xFE, "ddd", 195, npc.Store, TimeLeft);
					else {
						IPlayer.SystemMessage("No more time remaining for this NPC Usage!", TEXTCOLOR_RED);
						CChar::WriteInSight((void*)Player, 57, "d", offset);
					}
				}
				return;
			}

			int NPC = CNPC::FindNPC(offset);
			if (NPC) {
				if (*(DWORD*)(NPC + 456) == 699) {
					ShowAuction((void*)Player, 1, 1);
					ShowAuction((void*)Player, 2, 1);
					ShowAuction((void*)Player, 0, 1);
					CIOObject::Release((void*)NPC);
					return;
				}
				CIOObject::Release((void*)NPC);
			}
		}

		if (packet == 177) {
			int ID = 0;
			CPacket::Read((char*)pPacket, (char*)pPos, "d", &ID);

			//	IPlayer.UpdateBuff(BuffNames::TargetAttack, BuffNames::BuffTime, ID);
			return;
		}

		if (packet == 106) {
			int Type1 = 0, Type2 = 0;
			CPacket::Read((char*)pPacket, (char*)pPos, "dd", &Type1, &Type2);

			int Type = Type2 - 10;

			if (!Type)
				return;

			if (Type1 == 5) {
				ShowPotentialParticipants(IPlayer, Type);
				return;
			}

			if (Type1 == 21) {

				duelShowLock.Enter();
				if (AllFights.count(Type)) {
					std::vector<TOURNAMENT_PARTY> pts = AllFights.find(Type)->second;
					int Size = pts.size();
					Interface <ITools> Tools;
					int Packetsize = 0;
					char* PlayerPack = new char[32 * 144];
					for (int i = 0; i < 32; i++) {
						TOURNAMENT_PARTY pt;
						if (Size > i)
							pt = pts[i];
						else {
							pt = tagTournamentParty();
							pt.bNULL = true;
							pt.nPosition = 0;
							pt.nWinCnt = 0;
						}
							
						Tools->Compile(PlayerPack + Packetsize, "s", pt.szName);
						Tools->Compile(PlayerPack + Packetsize + 128, "dddd", pt.bAbsence, pt.bNULL, pt.nPosition, pt.nWinCnt);
						Packetsize += 144;
					}
					CPlayer::Write(IPlayer.GetOffset(), 123, "ddbm", 22, Type2, 32, PlayerPack, Packetsize);
					delete[] PlayerPack;
				}
				duelShowLock.Leave();
			}
			return;
		}

		if (packet == 182) {
			int Quest = 0;
			char index = 0;
			unsigned short a3 = 0;

			CPacket::Read((char*)pPacket, (char*)pPos, "dbw", &Quest, &index, &a3);

			int QuestID = Quest >> 16;
			int Flag = (unsigned __int16)Quest;

			if (QuestExs.count((QuestID * 1000) + Flag)) {
				QuestEx quest = QuestExs.find((QuestID * 1000) + Flag)->second;

				if (!quest.Save) {
					bool checkFlag = CPlayer::CheckQuestFlag(Player, Quest);
					if (checkFlag) {
						IPlayer.SystemMessage("You have already done this questex.", TEXTCOLOR_RED);
						return;
					}
				}

				if (IPlayer.GetLevel() > quest.MaxLvl || IPlayer.GetLevel() < quest.MinLvl) {
					IPlayer.SystemMessage("This questex is only available for players between level " + Int2String(quest.MinLvl) + " and " + Int2String(quest.MaxLvl) + ".", TEXTCOLOR_RED);
					return;
				}

				if (index < 0 || index > quest.Items.size()) {
					IPlayer.SystemMessage("Wrong selection, please try again.", TEXTCOLOR_RED);
					return;
				}

				if (GetInventorySize((int)IPlayer.GetOffset(), 0) >= 60)
				{
					CPlayer::Write(IPlayer.GetOffset(), 67, "b", 40);
					return;
				}

				if (!quest.Required.empty()) {
					for (int i = 0; i < quest.Required.size(); i++) {
						int ItemIndex = quest.Required[i];
						int ItemAmount = quest.Amounts[i];
						if (ItemIndex && ItemAmount) {
							if (!CPlayer::FindItem((void*)Player, ItemIndex, ItemAmount)) {
								IPlayer.SystemMessage("You do not have all the required items.", TEXTCOLOR_RED);
								return;
							}
						}
					}

					for (int i = 0; i < quest.Required.size(); i++) {
						int ItemIndex = quest.Required[i];
						int ItemAmount = quest.Amounts[i];
						if (ItemIndex && ItemAmount)
							CPlayer::RemoveItem((void*)Player, 9, ItemIndex, ItemAmount);
					}
				}

				int iIndex = quest.Items[index];
				int iAmount = quest.SAmounts[index];

				int Item = CItem::CreateItem(iIndex, 0, iAmount, -1);
				if (Item) {
					CIOObject::AddRef(Item);

					if ((*(int(__thiscall **)(int, int))(*(DWORD *)Item + 148))(Item, Item)) {
						if (CPlayer::InsertItem(IPlayer.GetOffset(), 7, Item) != 1)
							CBase::Delete((void*)Item);
					}
					else {
						for (int i = 0; i < iAmount; i++)
							IPlayer.InsertItem(iIndex, 0, 1);

						CBase::Delete((void*)Item);
					}

					CIOObject::Release((void*)Item);
				}

				if (quest.html)
					IPlayer.OpenHTML(quest.html);

				if (!quest.Save)
					CPlayer::SaveQuestFlag(Player, Quest, 1);
			}
			else
				IPlayer.SystemMessage("QuestEx disabled.", TEXTCOLOR_RED);

			return;
		}

		if (packet == 151) {
			if (!MysteryEnable) {
				IPlayer.SystemMessage("Mystery skills are disabled", TEXTCOLOR_RED);
				return;
			}

			int SkillID = 0;
			CPacket::Read((char*)pPacket, (char*)pPos, "d", &SkillID);

			if (SkillID < 85 || SkillID > 87) {
				IPlayer.SystemMessage("Wrong skill to reset.", TEXTCOLOR_RED);
				return;
			}

			SkillID += 2;

			int SkillPointer = IPlayer.GetSkillPointer(SkillID);

			if (!SkillPointer) {
				IPlayer.SystemMessage("You do not have this mystery skill.", TEXTCOLOR_RED);
				return;
			}

			if (!CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 1991, 1)) {
				IPlayer.SystemMessage("You do not have the mystery stone of chance item.", TEXTCOLOR_RED);
				return;
			}

			if (SkillID == 87)
				IPlayer.RemoveOTP(8 * *(DWORD*)(SkillPointer + 8));
			else
			if (SkillID == 88)
				IPlayer.RemoveEva(6 * *(DWORD*)(SkillPointer + 8));
			else
			if (SkillID == 89)
				IPlayer.RemoveDef(24 + (7 * *(DWORD*)(SkillPointer + 8)));

			*(DWORD*)(SkillPointer + 8) = 0;
			CPlayer::Write(IPlayer.GetOffset(), 11, "bb", SkillID - 2, 0);
			CDBSocket::Write(22, "dbbw", IPlayer.GetPID(), SkillID, 0, *(DWORD*)((int)IPlayer.GetOffset() + 548));
			*(DWORD*)((int)IPlayer.GetOffset() + 4 * SkillID + 632) = 0;

			Undefined::DeleteSkill(SkillPointer);
			IPlayer.BoxMsg("Your Mystery Skill has been successfully reset.");
			return;
		}

		if (packet == 150) {
			char type = 0;
			int Index = 0;
			CPacket::Read((char*)pPacket, (char*)pPos, "bd", &type, &Index);
			if (ItemExchanges.count(Index)) {
				ItemExchange exchange = ItemExchanges.find(Index)->second;

				if (CPlayer::RemoveItem((void*)Player, 9, exchange.Material, exchange.MaterialAmount) && CPlayer::RemoveItem((void*)Player, 9, Index, 1))
					IPlayer.InsertItem(exchange.ItemOut, 0, 1);
				else
					IPlayer.SystemMessage("You do not have enough material items.", TEXTCOLOR_RED);
			}
			return;
		}

		if (packet == 200) {
			int iid = 0, AuctionType = 0;
			char Type1 = 0, Type2 = 0;
			CPacket::Read((char*)pPacket, (char*)pPos, "ddbb", &AuctionType, &iid, &Type1, &Type2);

			if (AuctionType == 2513) {
				int Counted = AuctionItems.count(iid);

				if (Counted) {
					AuctionItem item = AuctionItems.find(iid)->second;
					if (CPlayer::RemoveItem((void*)Player, 9, 31, item.Price)) {

						if (item.RPID)
							CDBSocket::Write(104, "dddd", item.RPID, 31, item.CurrentBid, 0);

						CDBSocket::Write(104, "dddd", item.PID, 31, item.Price, 0);
						CDBSocket::Write(30, "dbdbbssdbwbdds", -1, 0, -1, 0, 1, "Kal Online", IPlayer.GetName(), iid, item.SetGem, item.Index, item.Prefix, item.Amount, 0, "Congratulations, you have won the auction for this item.");

						AuctionItems.erase(iid);

						InterlockedDecrement(&auctionItemsNum);
						UpdateAuction();
						CDBSocket::Write(107, "d", iid);
						ShowAuction((void*)Player, 0, 1);
						CPlayer::Write((void*)Player, 0xFE, "db", 206, 3);
					}
					else
						CPlayer::Write((void*)Player, 0xFE, "db", 206, 0xD);
				}
				return;
			}
		}


		if (packet == 197)
		{
			char first = 0, second = 0, third = 0;
			unsigned short Bid = 0;
			CPacket::Read((char*)pPacket, (char*)pPos, "bbbw", &first, &second, &third, &Bid);

			if (Bid) {
				for (int i = 0; i < 3; i++) {
					if (first != i)
						ShowAuction((void*)Player, i, 1);
				}

				ShowAuction((void*)Player, first, Bid);
			}
			return;
		}

		if (packet == 88) {
			int iid = 0, CurrentBid = 0, Price = 0;
			unsigned short Hours = 0;
			CPacket::Read((char*)pPacket, (char*)pPos, "dwdd", &iid, &Hours, &CurrentBid, &Price);

			if (Hours > 0 && Price > 0) {
				int Counted = AuctionItems.count(iid);

				if (Counted)
					return;

				if (Hours != 6 && Hours != 24 && Hours != 72 && Hours != 168)
					return;

				if (Hours == 24 && !CPlayer::RemoveItem((void*)Player, 9, 1827, 1))
					return;
				if (Hours == 72 && !CPlayer::RemoveItem((void*)Player, 9, 1828, 1))
					return;
				if (Hours == 168 && !CPlayer::RemoveItem((void*)Player, 9, 1829, 1))
					return;

				if (CurrentBid > Price)
					return;

				int ItemOffset = IPlayer.ItemPointerLock(iid);

				if (!ItemOffset)
					return;

				IItem IItem((void*)ItemOffset);
				if (IItem.Exists()) {

					if (AuctionItemDisable.count(IItem.CheckIndex())) {
						IPlayer.SystemMessage("This item can not be added in auction.", TEXTCOLOR_RED);
						return;
					}

					if (PetLifeCheck.count(IItem.GetIID())) {
						IPlayer.SystemMessage("Timed items can not be added in auction.", TEXTCOLOR_RED);
						return;
					}

					if (IItem.CheckIndex() == 31) {
						IPlayer.SystemMessage("Geons can not be added in auction.", TEXTCOLOR_RED);
						return;
					}

					if (IItem.GetInfo() & 1) {
						IPlayer.SystemMessage("Equipped items can not be added in auction.", TEXTCOLOR_RED);
						return;
					}

					if (IItem.GetInfo() & 8)
					{
						IPlayer.SystemMessage("Cheat items can not be added in auction.", TEXTCOLOR_RED);
						return;
					}

					if (IItem.GetInfo() & 128)
					{
						IPlayer.SystemMessage("Bound items can not be added in auction.", TEXTCOLOR_RED);
						return;
					}

					if (IItem.GetInfo() & 4194304)
					{
						IPlayer.SystemMessage("Locked items can not be added in aution.", TEXTCOLOR_RED);
						return;
					}

					if (AuctionLimit) {
						int count = 0;
						ConcurrentMap<long, AuctionItem> cloneAuction = AuctionItems;

						for (auto x = cloneAuction.rbegin(); x != cloneAuction.rend(); x++) {
							if (x->second.PID == IPlayer.GetPID())
								count++;

							if (count >= AuctionLimit) {
								IPlayer.SystemMessage("You can only have up to " + Int2String(AuctionLimit) + " registered items in auction.", TEXTCOLOR_RED);
								return;
							}
						}
					}

					unsigned short index;
					unsigned char prefix;
					unsigned long info, amount;
					unsigned char maxend = 0, curend = 0, setgem = 0, xatk = IItem.GetXAttack(), xmagic = IItem.GetXMagic(), xdefense = IItem.GetXDefense(), xhit = IItem.GetXHit(), xevasion = IItem.GetXDodge();
					unsigned short xprotect = 0;
					unsigned char upgrlvl = (char)IItem.GetUpgrade(), upgrrate = (char)IItem.GetUpgrRate();
					unsigned short x = 0, y = 0, z = 0, dsstype = 0, eva = 0, otp = 0, hpinc = 0, mpinc = 0, str = 0, hp = 0, intel = 0, wis = 0, agi = 0, a = 0, dg1stat = 0, dg1type = 0, dg2stat = 0, dg2type = 0, PerfShotCheck = 0;
					unsigned long remaintime = 0, QigongGrade = 0;
					unsigned short phyatk = 0, magatk = 0, def = 0, absorb = 0;

					AuctionItem item = AuctionItem();
					item.Bidder = "";
					item.BidRemain = (int)time(0) + (3600 * Hours);
					item.CurrentBid = CurrentBid;
					item.Price = Price;
					item.Seller = IPlayer.GetName();
					item.PID = IPlayer.GetPID();
					item.RPID = 0;
					curend = IItem.GetIntEndurance();
					index = IItem.CheckIndex();
					amount = IItem.GetAmount();
					prefix = IItem.PrefixID();
					info = IItem.GetInfo();
					setgem = IItem.GetSetGem();
					item.Index = index;
					item.SetGem = setgem;
					item.Prefix = prefix;
					item.Amount = amount;

					if (index == 337 || index == 338 || index == 339 || index == 1596) {
						curend = *(DWORD*)((int)ItemOffset + 92);
						info -= 32;
					}

					maxend = curend;

					int Class = IPlayer.GetClass();
					int ItemStat = 0;

					itemStat.Enter();
					if (GetItemStat.count(iid))
						ItemStat = GetItemStat.find(iid)->second;
					itemStat.Leave();

					int GetStat = ItemStat;

					if (IItem.GetType() == -2 || IItem.GetType() == 19 || IItem.GetType() == 0 || IItem.GetType() == -3 || IItem.GetType() == -1)
					{
						if (IItem.GetSetGem() == 240)
						{
							dsstype = 1; phyatk = 17; magatk = 17; agi = 8;
							hpinc = 250; mpinc = 200;
							if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 18; else otp = 18;
						}
						else if (IItem.GetSetGem() == 239)
						{
							dsstype = 1; phyatk = 17; magatk = 17; wis = 8;
							hpinc = 250; mpinc = 200;
							if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 18; else otp = 18;
						}
						else if (IItem.GetSetGem() == 238)
						{
							dsstype = 1; phyatk = 17; magatk = 17; intel = 8;
							hpinc = 250; mpinc = 200;
							if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 18; else otp = 18;
						}
						else if (IItem.GetSetGem() == 237)
						{
							dsstype = 1; phyatk = 17; magatk = 17; hp = 8;
							hpinc = 250; mpinc = 200;
							if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 18; else otp = 18;
						}
						else if (IItem.GetSetGem() == 236)
						{
							dsstype = 1; phyatk = 17; magatk = 17; str = 8;
							hpinc = 250; mpinc = 200;
							if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 18; else otp = 18;
						}
						else if (IItem.GetSetGem() == 235)
						{
							dsstype = 2; phyatk = 14; magatk = 14; agi = 5;
							hpinc = 200; mpinc = 150;
							if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 15; else otp = 15;
						}
						else if (IItem.GetSetGem() == 234)
						{
							dsstype = 2; phyatk = 14; magatk = 14; wis = 5;
							hpinc = 200; mpinc = 150;
							if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 15; else otp = 15;
						}
						else if (IItem.GetSetGem() == 233)
						{
							dsstype = 2; phyatk = 14; magatk = 14; intel = 5;
							hpinc = 200; mpinc = 150;
							if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 15; else otp = 15;
						}
						else if (IItem.GetSetGem() == 232)
						{
							dsstype = 2; phyatk = 14; magatk = 14; hp = 5;
							hpinc = 200; mpinc = 150;
							if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 15; else otp = 15;
						}
						else if (IItem.GetSetGem() == 231)
						{
							dsstype = 2; phyatk = 14; magatk = 14; str = 5;
							hpinc = 200; mpinc = 150;
							if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 15; else otp = 15;
						}
						else if (IItem.GetSetGem() == 230)
						{
							dsstype = 3; phyatk = 12; magatk = 12; agi = 3;
							hpinc = 130; mpinc = 110;
							if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 12; else otp = 12;
						}
						else if (IItem.GetSetGem() == 229)
						{
							dsstype = 3; phyatk = 12; magatk = 12; wis = 3;
							hpinc = 130; mpinc = 110;
							if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 12; else otp = 12;
						}
						else if (IItem.GetSetGem() == 228)
						{
							dsstype = 3; phyatk = 12; magatk = 12; intel = 3;
							hpinc = 130; mpinc = 110;
							if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 12; else otp = 12;
						}
						else if (IItem.GetSetGem() == 227)
						{
							dsstype = 3; phyatk = 12; magatk = 12; hp = 3;
							hpinc = 130; mpinc = 110;
							if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 12; else otp = 12;
						}
						else if (IItem.GetSetGem() == 226)
						{
							dsstype = 3; phyatk = 12; magatk = 12; str = 3;
							hpinc = 130; mpinc = 110;
							if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 12; else otp = 12;
						}
						else if (IItem.GetSetGem() == 225)
						{
							dsstype = 4; phyatk = 10; magatk = 10; agi = 3;
							hpinc = 110; mpinc = 90;
							if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 10; else otp = 10;
						}
						else if (IItem.GetSetGem() == 224)
						{
							dsstype = 4; phyatk = 10; magatk = 10; wis = 3;
							hpinc = 110; mpinc = 90;
							if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 10; else otp = 10;
						}
						else if (IItem.GetSetGem() == 223)
						{
							dsstype = 4; phyatk = 10; magatk = 10; intel = 3;
							hpinc = 110; mpinc = 90;
							if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 10; else otp = 10;
						}
						else if (IItem.GetSetGem() == 222)
						{
							dsstype = 4; phyatk = 10; magatk = 10; hp = 3;
							hpinc = 110; mpinc = 90;
							if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 10; else otp = 10;
						}
						else if (IItem.GetSetGem() == 221)
						{
							dsstype = 4; phyatk = 10; magatk = 10; str = 3;
							hpinc = 110; mpinc = 90;
							if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 10; else otp = 10;
						}
						else if (IItem.GetSetGem() == 220)
						{
							dsstype = 5; phyatk = 8; magatk = 8; agi = 2;
							hpinc = 90; mpinc = 70;
							if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 8; else otp = 8;
						}
						else if (IItem.GetSetGem() == 219)
						{
							dsstype = 5; phyatk = 8; magatk = 8; wis = 2;
							hpinc = 90; mpinc = 70;
							if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 8; else otp = 8;
						}
						else if (IItem.GetSetGem() == 218)
						{
							dsstype = 5; phyatk = 8; magatk = 8; intel = 2;
							hpinc = 90; mpinc = 70;
							if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 8; else otp = 8;
						}
						else if (IItem.GetSetGem() == 217)
						{
							dsstype = 5; phyatk = 8; magatk = 8; hp = 2;
							hpinc = 90; mpinc = 70;
							if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 8; else otp = 8;
						}
						else if (IItem.GetSetGem() == 216)
						{
							dsstype = 5; phyatk = 8; magatk = 8; str = 2;
							hpinc = 90; mpinc = 70;
							if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 8; else otp = 8;
						}
						else if (IItem.GetSetGem() == 215)
						{
							dsstype = 6; phyatk = 6; magatk = 6; agi = 2;
							hpinc = 70; mpinc = 50;
							if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 6; else otp = 6;
						}
						else if (IItem.GetSetGem() == 214)
						{
							dsstype = 6; phyatk = 6; magatk = 6; wis = 2;
							hpinc = 70; mpinc = 50;
							if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 6; else otp = 6;
						}
						else if (IItem.GetSetGem() == 213)
						{
							dsstype = 6; phyatk = 6; magatk = 6; intel = 2;
							hpinc = 70; mpinc = 50;
							if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 6; else otp = 6;
						}
						else if (IItem.GetSetGem() == 212)
						{
							dsstype = 6; phyatk = 6; magatk = 6; hp = 2;
							hpinc = 70; mpinc = 50;
							if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 6; else otp = 6;
						}
						else if (IItem.GetSetGem() == 211)
						{
							dsstype = 6; phyatk = 6; magatk = 6; str = 2;
							hpinc = 70; mpinc = 50;
							if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 6; else otp = 6;
						}
						else if (IItem.GetSetGem() == 210)
						{
							dsstype = 7; phyatk = 4; magatk = 4; agi = 1;
							hpinc = 50; mpinc = 30;
							if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 4; else otp = 4;
						}
						else if (IItem.GetSetGem() == 209)
						{
							dsstype = 7; phyatk = 4; magatk = 4; wis = 1;
							hpinc = 50; mpinc = 30;
							if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 4; else otp = 4;
						}
						else if (IItem.GetSetGem() == 208)
						{
							dsstype = 7; phyatk = 4; magatk = 4; intel = 1;
							hpinc = 50; mpinc = 30;
							if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 4; else otp = 4;
						}
						else if (IItem.GetSetGem() == 207)
						{
							dsstype = 7; phyatk = 4; magatk = 4; hp = 1;
							hpinc = 50; mpinc = 30;
							if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 4; else otp = 4;
						}
						else if (IItem.GetSetGem() == 206)
						{
							dsstype = 7; phyatk = 4; magatk = 4; str = 1;
							hpinc = 50; mpinc = 30;
							if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 4; else otp = 4;
						}
						else if (IItem.GetSetGem() == 205)
						{
							dsstype = 8; phyatk = 2; magatk = 2; agi = 1;
							hpinc = 30; mpinc = 10;
							if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 2; else otp = 2;
						}
						else if (IItem.GetSetGem() == 204)
						{
							dsstype = 8; phyatk = 2; magatk = 2; wis = 1;
							hpinc = 30; mpinc = 10;
							if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 2; else otp = 2;
						}
						else if (IItem.GetSetGem() == 203)
						{
							dsstype = 8; phyatk = 2; magatk = 2; intel = 1;
							hpinc = 30; mpinc = 10;
							if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 2; else otp = 2;
						}
						else if (IItem.GetSetGem() == 202)
						{
							dsstype = 8; phyatk = 2; magatk = 2; hp = 1;
							hpinc = 30; mpinc = 10;
							if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 2; else otp = 2;
						}
						else if (IItem.GetSetGem() == 201)
						{
							dsstype = 8; phyatk = 2; magatk = 2; str = 1;
							hpinc = 30; mpinc = 10;
							if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 2; else otp = 2;
						}
					}

					if (IItem.GetType() >= 1 && IItem.GetType() <= 6)
					{
						if (IItem.GetSetGem() == 240)
						{
							dsstype = 1; def = 18; agi = 7;
						}
						else if (IItem.GetSetGem() == 239)
						{
							dsstype = 1; def = 18; wis = 7;
						}
						else if (IItem.GetSetGem() == 238)
						{
							dsstype = 1; def = 18; intel = 7;
						}
						else if (IItem.GetSetGem() == 237)
						{
							dsstype = 1; def = 18; hp = 7;
						}
						else if (IItem.GetSetGem() == 236)
						{
							dsstype = 1; def = 18; str = 7;
						}
						else if (IItem.GetSetGem() == 235)
						{
							dsstype = 2; def = 16; agi = 5;
						}
						else if (IItem.GetSetGem() == 234)
						{
							dsstype = 2; def = 16; wis = 5;
						}
						else if (IItem.GetSetGem() == 233)
						{
							dsstype = 2; def = 16; intel = 5;
						}
						else if (IItem.GetSetGem() == 232)
						{
							dsstype = 2; def = 16; hp = 5;
						}
						else if (IItem.GetSetGem() == 231)
						{
							dsstype = 2; def = 16; str = 5;
						}
						else if (IItem.GetSetGem() == 230)
						{
							dsstype = 3; def = 14; agi = 3;
						}
						else if (IItem.GetSetGem() == 229)
						{
							dsstype = 3; def = 14; wis = 3;
						}
						else if (IItem.GetSetGem() == 228)
						{
							dsstype = 3; def = 14; intel = 3;
						}
						else if (IItem.GetSetGem() == 227)
						{
							dsstype = 3; def = 14; hp = 3;
						}
						else if (IItem.GetSetGem() == 226)
						{
							dsstype = 3; def = 14; str = 3;
						}
						else if (IItem.GetSetGem() == 225)
						{
							dsstype = 4; def = 12; agi = 3;
						}
						else if (IItem.GetSetGem() == 224)
						{
							dsstype = 4; def = 12; wis = 3;
						}
						else if (IItem.GetSetGem() == 223)
						{
							dsstype = 4; def = 12; intel = 3;
						}
						else if (IItem.GetSetGem() == 222)
						{
							dsstype = 4; def = 12; hp = 3;
						}
						else if (IItem.GetSetGem() == 221)
						{
							dsstype = 4; def = 12; str = 3;
						}
						else if (IItem.GetSetGem() == 220)
						{
							dsstype = 5; def = 10; agi = 2;
						}
						else if (IItem.GetSetGem() == 219)
						{
							dsstype = 5; def = 10; wis = 2;
						}
						else if (IItem.GetSetGem() == 218)
						{
							dsstype = 5; def = 10; intel = 2;
						}
						else if (IItem.GetSetGem() == 217)
						{
							dsstype = 5; def = 10; hp = 2;
						}
						else if (IItem.GetSetGem() == 216)
						{
							dsstype = 5; def = 10; str = 2;
						}
						else if (IItem.GetSetGem() == 215)
						{
							dsstype = 6; def = 8; agi = 2;
						}
						else if (IItem.GetSetGem() == 214)
						{
							dsstype = 6; def = 8; wis = 2;
						}
						else if (IItem.GetSetGem() == 213)
						{
							dsstype = 6; def = 8; intel = 2;
						}
						else if (IItem.GetSetGem() == 212)
						{
							dsstype = 6; def = 8; hp = 2;
						}
						else if (IItem.GetSetGem() == 211)
						{
							dsstype = 6; def = 8; str = 2;
						}
						else if (IItem.GetSetGem() == 210)
						{
							dsstype = 7; def = 6; agi = 1;
						}
						else if (IItem.GetSetGem() == 209)
						{
							dsstype = 7; def = 6; wis = 1;
						}
						else if (IItem.GetSetGem() == 208)
						{
							dsstype = 7; def = 6; intel = 1;
						}
						else if (IItem.GetSetGem() == 207)
						{
							dsstype = 7; def = 6; hp = 1;
						}
						else if (IItem.GetSetGem() == 206)
						{
							dsstype = 7; def = 6; str = 1;
						}
						else if (IItem.GetSetGem() == 205)
						{
							dsstype = 8; def = 4; agi = 1;
						}
						else if (IItem.GetSetGem() == 204)
						{
							dsstype = 8; def = 4; wis = 1;
						}
						else if (IItem.GetSetGem() == 203)
						{
							dsstype = 8; def = 4; intel = 1;
						}
						else if (IItem.GetSetGem() == 202)
						{
							dsstype = 8; def = 4; hp = 1;
						}
						else if (IItem.GetSetGem() == 201)
						{
							dsstype = 8; def = 4; str = 1;
						}
					}

					if (IItem.GetType() == -3 && otp && *(DWORD*)((int)Player + 460) == 4)
					{
						eva = otp;
						otp = 0;
					}


					if (isItemSuit(index) || isItemCustomWeapon(index) || isItemRiding(index)) {
						int GStat = GetStat;
						if (isBattleRiding(index)) {
							int Satiety = GStat / 100;
							if (Satiety)
								GStat -= (Satiety * 100);
						}
						if (IItem.GetClass() == 0)
							hp += GStat >= 6 ? (((GStat - 5) * 3) + 10) : GStat * 2;
						if (IItem.GetClass() == 1 || IItem.GetClass() == -1)
							hp += GStat >= 6 ? (((GStat - 5) * 3) + 10) : GStat * 2;
						if (IItem.GetClass() == 2 || IItem.GetClass() == 3)
							hp += GStat >= 6 ? (((GStat - 5) * 3) + 10) : GStat * 2;
					}

					if (GetStat)
					{
						PerfShotCheck = ItemStat / 100000000;
						ItemStat -= (100000000 * PerfShotCheck);
					}

					if (ItemStat)
					{
						int dg1typecheck = ItemStat / 10000000;
						if (dg1typecheck) dg1stat = 1;
						if (dg1typecheck > 0) dg1type = (dg1typecheck - 1);
						ItemStat -= (10000000 * dg1typecheck);
					}

					if (ItemStat)
					{
						int dg1statcheck = ItemStat / 1000000;
						if (dg1statcheck > 0) dg1stat = (dg1statcheck + 1);
						ItemStat -= (1000000 * dg1statcheck);
					}

					if (ItemStat)
					{
						int dg2typecheck = ItemStat / 100000;
						if (dg2typecheck) dg2stat = 1;
						if (dg2typecheck > 0) dg2type = (dg2typecheck - 1);
						ItemStat -= (100000 * dg2typecheck);
					}

					if (ItemStat)
					{
						int dg2statcheck = ItemStat / 10000;
						if (dg2statcheck > 0) dg2stat = (dg2statcheck + 1);
						ItemStat -= (10000 * dg2statcheck);
					}

					if (ItemStat && index >= 2986 && index <= 3009)
					{
						int yinyanggrade = ItemStat / 100;
						prefix = yinyanggrade + 1;
						ItemStat -= (100 * yinyanggrade);
					}

					if (ItemStat)
						QigongGrade = ItemStat % 100;

					if (index >= 3199 && index <= 3201 && prefix == 0)
						prefix = 1;

					if (index >= 2986 && index <= 3009 && prefix == 0)
						prefix = 1;

					if (index >= 3018 && index <= 3020 && GetStat)
						prefix = GetStat / 1000;

					int refill = 0;
					if (isSoulPocket(index)) {
						if (GetStat)
							refill = GetStat;
					}

					if (GetStat && (isItemCustomWeapon(index) || isItemSuit(index) || isItemRiding(index) || isItemRidingArmor(index))) {
						int GStat = GetStat;
						if (isBattleRiding(index)) {
							int Satiety = GStat / 100;
							if (Satiety)
								GStat -= (Satiety * 100);
						}
						if (GStat)
							upgrlvl = GStat;
					}

					if (isItemRidingArmor(index)) {
						if (GetStat > 0 && GetStat <= 10 && GetBattleRidingGrade(index) > 0) {
							if (GetBattleRidingType(index) == 1) {
								if (index == 7883 || index == 7889 || index == 7895 || index == 7901)
									str += RidingHelmet[GetBattleRidingGrade(index) - 1][GetStat - 1];
								else
									intel += RidingHelmet[GetBattleRidingGrade(index) - 1][GetStat - 1];
							}
							if (GetBattleRidingType(index) == 2)
								hp += RidingSaddle[GetBattleRidingGrade(index) - 1][GetStat - 1];
							if (GetBattleRidingType(index) == 3)
								xdefense += RidingArmor[GetBattleRidingGrade(index) - 1][GetStat - 1];
							if (GetBattleRidingType(index) == 4)
								xdefense += RidingCloth[GetBattleRidingGrade(index) - 1][GetStat - 1];
							if (GetBattleRidingType(index) == 5)
								eva += RidingMagnet[GetBattleRidingGrade(index) - 1][GetStat - 1];
						}
					}
					memset(item.ItemPacket, 0, sizeof item.ItemPacket);
					Tools->Compile(item.ItemPacket, "wdbddbbbbbbbbwbbbbbdbwwwwbbbbbbbbbbdbbwbbd", index, iid, prefix, info, amount, maxend, curend, setgem, xatk, xmagic, xdefense, xhit, xevasion, xprotect, upgrlvl, upgrrate, x, y, z, remaintime, dsstype, phyatk, magatk, def, absorb, eva, otp, hpinc, mpinc, str, hp, intel, wis, agi, PerfShotCheck, QigongGrade, dg1stat, dg1type, a, dg2stat, dg2type, refill);

					AuctionItems[iid] = item;
					UpdateAuction();
					ShowAuction((void*)Player, 0, 1);
					CDBSocket::Write(105, "sddsdmd", IPlayer.GetName(), (int)time(0) + (3600 * Hours), Price, "", CurrentBid, item.ItemPacket, 67, IPlayer.GetPID());

					int v18 = (*(int(__thiscall **)(int, int, signed int, int))(*(DWORD *)ItemOffset + 132))(ItemOffset, Player, 10, IItem.GetAmount());
					if (v18 == ItemOffset)
						CPlayer::_OutOfInven((void*)Player, ItemOffset);

					InterlockedIncrement(&auctionItemsNum);
					CPlayer::Write((void*)Player, 0xFE, "db", 206, 1);

					int messageType = 2;
					RewardMessage reward;
					std::string msg = "[" + std::string(IPlayer.GetName()) + "] has just listed a new item in the Auction House!";
					reward.message = msg;
					reward.textColor = NOTICECOLOR_YELLOW;
					reward.messageType = messageType;
					ToAuctionNoticeWebhook(msg);
					PlayerRewardNotice.push_back(reward);
					return;
				}
			}
		}

		if (packet == 158) {
			char Face = 0, Hair = 0;
			CPacket::Read((char*)pPacket, (char*)pPos, "bb", &Face, &Hair);

			if (Face >= 1 && Face <= 6 && Hair >= 1 && Hair <= 6 && CPlayer::RemoveItem((void*)Player, 9, 1929, 1)) {
				*(DWORD *)(Player + 556) = Face;
				*(DWORD *)(Player + 560) = Hair;
				CDBSocket::Write(75, "dbb", IPlayer.GetPID(), Face, Hair);

				CPlayer::Write((void*)Player, 0xFE, "dbb", 188, Face, Hair);
				IPlayer.Teleport(IPlayer.GetMap(), IPlayer.GetX(), IPlayer.GetY());
				IPlayer.SystemMessage("Successfully changed your appearance.", TEXTCOLOR_GREEN);
			}
			return;
		}

		if (packet == 201) {
			int BidType = 0;
			int IID = 0;
			int BidPrice = 0;
			char Type = 0, Type2 = 0;
			CPacket::Read((char*)pPacket, (char*)pPos, "ddbbd", &BidType, &IID, &Type, &Type2, &BidPrice);

			int Counted = AuctionItems.count(IID);

			if (Counted) {
				AuctionItem item = AuctionItems.find(IID)->second;

				if (BidPrice == item.Price - 1000) {
					CPlayer::Write((void*)Player, 0xFE, "db", 206, 0x11);
					return;
				}

				if (BidPrice >= item.Price) {
					IPlayer.SystemMessage("Bid price cannot be larger than BUY NOW! price.", TEXTCOLOR_RED);
					return;
				}

				if (BidPrice <= item.CurrentBid) {
					CPlayer::Write((void*)Player, 0xFE, "db", 206, 0xD);
					return;
				}

				if (CPlayer::RemoveItem((void*)Player, 9, 31, BidPrice)) {
					if (item.RPID)
						CDBSocket::Write(104, "dddd", item.RPID, 31, item.CurrentBid, 0);

					item.Bidder = IPlayer.GetName();
					item.RPID = IPlayer.GetPID();
					item.CurrentBid = BidPrice;

					AuctionItems[IID] = item;
					UpdateAuction();
					IPlayer.CloseWindow("auction_main");
					ShowAuction((void*)Player, 1, 1);
					ShowAuction((void*)Player, 2, 1);
					ShowAuction((void*)Player, 0, 1);
					CDBSocket::Write(106, "ddds", IID, IPlayer.GetPID(), BidPrice, IPlayer.GetName());
					CPlayer::Write((void*)Player, 0xFE, "db", 206, 2);
				}
				else
					CPlayer::Write((void*)Player, 0xFE, "db", 206, 0xD);

			}
			return;
		}

		if (packet == 189) {
			int type = 0, key = 0, iid1 = 0, iid2 = 0, iid3 = 0, iid4 = 0, iid5 = 0, iid6 = 0;
			CPacket::Read((char*)pPacket, (char*)pPos, "dddddddd", &type, &key, &iid1, &iid2, &iid3, &iid4, &iid5, &iid6);

			if (type == 2) {
				if (SecretBlackSmith.count(key)) {
					SecretBlackSmithSkill InitSwap = SecretBlackSmith.find(key)->second;
					std::vector<std::string> requireIndex = Tools->Explode(InitSwap.requires, ",");
					std::vector<std::string> requireAmounts = Tools->Explode(InitSwap.requireAmounts, ",");

					if (requireIndex.size() > 0 && requireIndex.size() == requireAmounts.size()) {
						int MoneyAmount = 0;
						int MoneyItem = 0;
						for (int i = 0; i < requireIndex.size(); i++) {
							int Index = String2Int(requireIndex[i]);
							int Amount = String2Int(requireAmounts[i]);
							int ItemFound = CPlayer::FindItem((void*)Player, Index, Amount);
							if (Index && Amount && !ItemFound) {
								IPlayer.SystemMessage("You do not have all the required items.", TEXTCOLOR_RED);
								return;
							}
							if (Index == 31) {
								MoneyItem = ItemFound;
								MoneyAmount = Amount;
							}
						}

						if (MoneyItem && MoneyAmount) {
							if (!(*(int(__thiscall **)(DWORD, void *, signed int, signed int))(*(DWORD*)MoneyItem + 120))(MoneyItem, IPlayer.GetOffset(), 9, -MoneyAmount))
								CPlayer::_OutOfInven((void*)Player, MoneyItem);
						}

						std::vector<int> IIDs;
						IIDs.push_back(iid1);
						IIDs.push_back(iid2);
						IIDs.push_back(iid3);
						IIDs.push_back(iid4);
						IIDs.push_back(iid5);
						IIDs.push_back(iid6);

						for (int i = 0; i < IIDs.size(); i++) {
							int Item = IPlayer.ItemPointerLock(IIDs[i]);
							if (Item) {
								IItem IItem((void*)Item);
								int Amount = 0;

								for (int j = 0; j < requireAmounts.size(); j++) {
									if (String2Int(requireIndex[j]) == IItem.CheckIndex())
										Amount = String2Int(requireAmounts[j]);
								}

								if (!Amount)
									continue;

								if (!(*(int(__thiscall **)(DWORD, void *, signed int, signed int))(*(DWORD*)Item + 120))(Item, IPlayer.GetOffset(), 9, -Amount))
									CPlayer::_OutOfInven((void*)Player, Item);

							}
						}

						std::vector<std::string> rewards = Tools->Explode(InitSwap.rewards, ",");
						srand(time(0));
						std::random_shuffle(rewards.begin(), rewards.end());
						CItem::InsertItem(Player, 27, String2Int(rewards.front()), 0, 1, -1);
						IPlayer.CloseWindow("item_make2");
					}
				}
			}
			return;
		}

		if (packet == 91) {
			char Type = 0;
			int IID = 0;
			int JewelUse = 0;
			CPacket::Read((char*)pPacket, (char*)pPos, "bdd", &Type, &IID, &JewelUse);

			if (IID == JewelUse)
				return;

			if (Type == 0) {

				int Item = IPlayer.ItemPointerLock(IID);

				if (!Item)
					return;

				IItem IItem((void*)Item);

				if (IItem.Exists() && isItemCustomWeapon(IItem.CheckIndex())) {

					if (GetInventorySize((int)IPlayer.GetOffset(), 0) >= 59)
					{
						CPlayer::Write(IPlayer.GetOffset(), 67, "b", 40);
						return;
					}

					int Index1 = IItem.CheckIndex();
					int Grade = IItem.GetGrade();

					if (CPlayer::RemoveItem((void*)Player, 9, 31, 1000) && IPlayer.RemoveItem(Item)) {
						if (Grade >= 3)
							IPlayer.InsertItem(7618, 0, 1);
						else
							IPlayer.InsertItem(7612, 0, 1);

						IPlayer.InsertItem(4134, 0, 1);
					}
					return;
				}

				if (IItem.Exists() && isItemSuit(IItem.CheckIndex())) {

					if (GetInventorySize((int)IPlayer.GetOffset(), 0) >= 60)
					{
						CPlayer::Write(IPlayer.GetOffset(), 67, "b", 40);
						return;
					}

					int ItemStat = 0;
					itemStat.Enter();
					if (GetItemStat.count(IID))
						ItemStat = GetItemStat.find(IID)->second;
					itemStat.Leave();


					if (ItemStat) {
						int Amount = IItem.GetGrade() ? 10 * IItem.GetGrade() : 10;
						for (int i = 0; i < ItemStat - 1; i++)
							Amount += (int)pow(2.0, (double)i);

						if (CPlayer::RemoveItem((void*)Player, 9, 31, 90000 * (int)pow(2.0, (double)ItemStat - 1)) && IPlayer.RemoveItem(Item))
							CItem::InsertItem((int)IPlayer.GetOffset(), 27, 4134, 0, Amount, -1);

					}
					return;
				}

				if (IItem.Exists() && isItemRiding(IItem.CheckIndex())) {
					if (isBattleRiding(IItem.CheckIndex())) {
						IPlayer.SystemMessage("Battle riding pets can not be decomposed.", TEXTCOLOR_RED);
						return;
					}

					if (GetInventorySize((int)IPlayer.GetOffset(), 0) >= 60)
					{
						CPlayer::Write(IPlayer.GetOffset(), 67, "b", 40);
						return;
					}

					int ItemStat = 0;
					itemStat.Enter();
					if (GetItemStat.count(IID))
						ItemStat = GetItemStat.find(IID)->second;
					itemStat.Leave();


					if (ItemStat) {
						int Amount = IItem.GetGrade() ? 10 * IItem.GetGrade() : 10;
						for (int i = 0; i < ItemStat - 1; i++)
							Amount += (int)pow(2.0, (double)i);

						if (CPlayer::RemoveItem((void*)Player, 9, 31, 90000 * (int)pow(2.0, (double)ItemStat - 1)) && IPlayer.RemoveItem(Item))
							CItem::InsertItem((int)IPlayer.GetOffset(), 27, 4135, 0, Amount, -1);

					}
					return;
				}
			}

			if (Type == 9) {

				int Item = IPlayer.ItemPointerLock(IID);

				if (!Item)
					return;
				IItem IItem((void*)Item);

				if (IItem.Exists() && isItemRidingArmor(IItem.CheckIndex())) {
					int ItemStat = 0;
					itemStat.Enter();
					if (GetItemStat.count(IID))
						ItemStat = GetItemStat.find(IID)->second;
					itemStat.Leave();

					if (ItemStat >= 10) {
						IPlayer.BoxMsg("You've reached the max enchant level for this item.");
						return;
					}

					int Grade = GetBattleRidingGrade(IItem.CheckIndex()) - 1;

					int Item1 = CPlayer::FindItem((void*)Player, RidingEnchant[0][Grade], 10);
					int Item2 = CPlayer::FindItem((void*)Player, 31, RidingEnchant[1][Grade]);
					if (Item1 && Item2) {
						if (CPlayer::RemoveItem((void*)Player, 9, RidingEnchant[0][Grade], 10) && CPlayer::RemoveItem((void*)Player, 9, 31, RidingEnchant[1][Grade])) {

							if (Grade && JewelUse)
								JewelUse = CPlayer::RemoveItem((void*)Player, 9, JewelIndex, RidingEnchant[2][Grade]);

							int Rate = CTools::Rate(1, 100);
							if (Rate <= ((90 + (JewelUse*(Grade * 2))) - ((Grade * 18) + (ItemStat * 2)))) {
								itemStat.Enter();
								GetItemStat[IID] = ItemStat + 1;
								itemStat.Leave();
								CDBSocket::Write(90, "dd", ItemStat + 1, IID);
								CItem::SendItemInfo((void*)Item, Player, 92);
							}
							else if (!JewelUse && Grade) {
								int CheckPolish = CItem::IsState((int)IItem.GetOffset(), 64);
								if (CheckPolish)
								{
									CDBSocket::Write(21, "dddbb", IItem.GetIID(), IPlayer.GetID(), 64, 0, 255);
									CItem::SubState((int)IItem.GetOffset(), 64);
									CItem::SendItemInfo(IItem.GetOffset(), (int)IPlayer.GetOffset(), 92);
									return;
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
								return;
							}
							else {
								IPlayer.SystemMessage("Item enchant has failed but item remains.", TEXTCOLOR_FAILED);
								return;
							}
						}
					}
					else {
						IPlayer.BoxMsg("Not Enough enchant items to enchant item.");
						return;
					}
				}
				else
					IPlayer.BoxMsg("Item already destroyed.");

				return;
			}

			if (Type == 3) {

				int Item = IPlayer.ItemPointerLock(IID);

				if (!Item)
					return;

				IItem IItem((void*)Item);

				if (IItem.Exists() && isItemRiding(IItem.CheckIndex())) {
					int ItemStat = 0;
					itemStat.Enter();
					if (GetItemStat.count(IID))
						ItemStat = GetItemStat.find(IID)->second;
					itemStat.Leave();

					if (ItemStat >= 10) {
						IPlayer.BoxMsg("You've reached the max enchant level for this item.");
						return;
					}

					int Amount = (int)pow(2.0, (double)ItemStat);
					int Item1 = CPlayer::FindItem((void*)Player, 31, 150000 * Amount);
					int Item2 = CPlayer::FindItem((void*)Player, 4135, Amount);
					if (Item1 && Item2) {
						CPlayer::RemoveItem((void*)Player, 9, 4135, Amount);
						CPlayer::RemoveItem((void*)Player, 9, 31, 150000 * Amount);
						int Rate = CTools::Rate(1, 100);
						if (Rate <= (93 - (ItemStat * 9))) {
							itemStat.Enter();
							GetItemStat[IID] = ItemStat + 1;
							itemStat.Leave();
							CDBSocket::Write(90, "dd", ItemStat + 1, IID);
							CItem::SendItemInfo((void*)Item, Player, 92);
						}
						else
							IPlayer.SystemMessage("Riding has failed enchanting but remains.", TEXTCOLOR_FAILED);
					}
					else
						IPlayer.BoxMsg("Not enough enchant items or money");
					return;
				}

				if (IItem.Exists() && isItemSuit(IItem.CheckIndex())) {
					int ItemStat = 0;
					itemStat.Enter();
					if (GetItemStat.count(IID))
						ItemStat = GetItemStat.find(IID)->second;
					itemStat.Leave();

					if (ItemStat >= 10) {
						IPlayer.BoxMsg("You've reached the max enchant level for this item.");
						return;
					}

					int Amount = (int)pow(2.0, (double)ItemStat);
					int Item1 = CPlayer::FindItem((void*)Player, 31, 150000 * Amount);
					int Item2 = CPlayer::FindItem((void*)Player, 4134, Amount);
					if (Item1 && Item2) {
						CPlayer::RemoveItem((void*)Player, 9, 4134, Amount);
						CPlayer::RemoveItem((void*)Player, 9, 31, 150000 * Amount);
						int Rate = CTools::Rate(1, 100);
						if (Rate <= (93 - (ItemStat * 9))) {
							itemStat.Enter();
							GetItemStat[IID] = ItemStat + 1;
							itemStat.Leave();
							CDBSocket::Write(90, "dd", ItemStat + 1, IID);
							CItem::SendItemInfo((void*)Item, Player, 92);
						}
						else
							IPlayer.SystemMessage("Costume has failed enchanting but remains.", TEXTCOLOR_FAILED);
					}
					else
						IPlayer.BoxMsg("Not enough enchant items or money");
					return;
				}

				if (IItem.Exists() && isItemCustomWeapon(IItem.CheckIndex())) {
					int ItemStat = 0;
					itemStat.Enter();
					if (GetItemStat.count(IID))
						ItemStat = GetItemStat.find(IID)->second;
					itemStat.Leave();

					if (ItemStat >= 10) {
						IPlayer.BoxMsg("You've reached the max enchant level for this item.");
						return;
					}

					int Amount = (int)pow(2.0, (double)ItemStat);

					int MoneyAmount = CustomWeaponEnchant[ItemStat];

					if (IItem.GetGrade() == 3) {
						Amount *= 2;
						MoneyAmount *= 3;
					}

					int Item1 = CPlayer::FindItem((void*)Player, 7600, Amount);
					int Item2 = CPlayer::FindItem((void*)Player, 31, MoneyAmount);
					if (Item1 && Item2) {
						if (CPlayer::RemoveItem((void*)Player, 9, 7600, Amount) && CPlayer::RemoveItem((void*)Player, 9, 31, MoneyAmount)) {

							int Rate = CTools::Rate(1, 100);
							if (Rate <= (93 - (ItemStat * 8))) {
								itemStat.Enter();
								GetItemStat[IID] = ItemStat + 1;
								itemStat.Leave();
								CDBSocket::Write(90, "dd", ItemStat + 1, IID);
								CItem::SendItemInfo((void*)Item, Player, 92);
							}
							else {
								IPlayer.SystemMessage("Item enchant has failed but item remains.", TEXTCOLOR_FAILED);
								return;
							}
						}
					}
					else {
						IPlayer.BoxMsg("Not Enough enchant items to enchant item.");
						return;
					}
				}
				else
					IPlayer.BoxMsg("Item already destroyed.");

				return;
			}

			if (Type == 5) {

				int Item = IPlayer.ItemPointerLock(IID);

				if (!Item)
					return;
				IItem ItemX((void*)Item);

				if (ItemX.Exists() && isItemRidingArmor(ItemX.CheckIndex())) {
					int ItemStat = 0;
					itemStat.Enter();
					if (GetItemStat.count(IID))
						ItemStat = GetItemStat.find(IID)->second;
					itemStat.Leave();

					if (ItemStat != 10) {
						IPlayer.BoxMsg("You can not upgrade this item yet. Make sure its enchant level is 10.");
						return;
					}

					int Grade = GetBattleRidingGrade(ItemX.CheckIndex()) - 1;

					if (Grade >= 3) {
						IPlayer.BoxMsg("You've reached the max upgrade level for this item.");
						return;
					}

					int Item1 = CPlayer::FindItem((void*)Player, RidingUpgrade[0][Grade], RidingUpgrade[1][Grade]);
					int Item2 = CPlayer::FindItem((void*)Player, 31, RidingUpgrade[2][Grade]);
					if (Item1 && Item2) {

						if (IPlayer.IsBuff(328))
							return;
						else
							IPlayer.Buff(328, 3, 0);

						if (CPlayer::RemoveItem((void*)Player, 9, RidingUpgrade[0][Grade], RidingUpgrade[1][Grade]) && CPlayer::RemoveItem((void*)Player, 9, 31, RidingUpgrade[2][Grade])) {
							int Rate = CTools::Rate(1, 100);
							if (Rate <= (90 - (Grade * 20))) {
								int ReplacePrefix = 0, ReplaceItem = 0, ReplaceInfo = 0, ReplaceDef = 0, ReplaceEva = 0, ReplaceGem = 0;

								if (*(DWORD *)((int)Item + 44))
									ReplacePrefix = *(DWORD *)(*(DWORD *)((int)Item + 44) + 32);

								if (*(DWORD *)((int)Item + 48))
									ReplaceInfo = *(DWORD *)((int)Item + 48);

								if (ItemX.HighMemory() && *(DWORD *)((int)Item + 108))
									ReplaceDef = *(DWORD *)((int)Item + 108);

								if (ItemX.HighMemory() && *(DWORD *)((int)Item + 116))
									ReplaceEva = *(DWORD *)((int)Item + 116);

								if (*(DWORD *)((int)Item + 84))
									ReplaceGem = *(DWORD *)((int)Item + 84);

								int ItemNewIndex = ItemX.CheckIndex();
								int DeleteCheck = (*(int(__thiscall **)(DWORD, void *, signed int, signed int))(*(DWORD*)Item + 120))((int)Item, IPlayer.GetOffset(), 9, -1);

								if (!DeleteCheck)
								{
									CPlayer::_OutOfInven((void*)Player, Item);
									ReplaceItem = CItem::CreateItem(ItemNewIndex + 6, ReplacePrefix, 1, -1);

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

										if (CPlayer::InsertItem(IPlayer.GetOffset(), 27, ReplaceItem) != 1)
										{
											CConsole::Red("Real time armor insert item Null error [PID (%d)] ", IPlayer.GetPID());
											CBase::Delete((void *)ReplaceItem);
											return;
										}

										CIOObject::Release((void *)ReplaceItem);

										CDBSocket::Write(87, "ddd", IPlayer.GetPID(), *(DWORD *)(ReplaceItem + 84), *(DWORD *)(ReplaceItem + 36));
										CDBSocket::Write(21, "dddbb", *(DWORD *)(ReplaceItem + 36), *(DWORD *)(ReplaceItem + 32), *(DWORD *)(ReplaceItem + 48), 8, 7);

										if (ReplaceDef)
											CDBSocket::Write(17, "ddbbb", *(DWORD *)(ReplaceItem + 36), *(DWORD *)(ReplaceItem + 32), 15, *(DWORD *)(ReplaceItem + 108), 0);

										if (ReplaceEva)
											CDBSocket::Write(17, "ddbbb", *(DWORD *)(ReplaceItem + 36), *(DWORD *)(ReplaceItem + 32), 10, *(DWORD *)(ReplaceItem + 116), 0);

										CItem::SendItemInfo((void*)ReplaceItem, (int)IPlayer.GetOffset(), 92);
										CPlayer::Write(IPlayer.GetOffset(), 0xFF, "ddddd", 242, 0, 0, 128, 255);
									}
								}
								else
									return;
							}
							else {
								IPlayer.SystemMessage("Item upgrade has failed.", TEXTCOLOR_FAILED);
								return;
							}
						}
					}
					else
						IPlayer.BoxMsg("Not Enough upgrade items to upgrade item.");
				}

				if (ItemX.Exists() && isItemCustomWeapon(ItemX.CheckIndex())) {
					int Index = ItemX.CheckIndex();

					if (ItemX.GetGrade() >= 3)
						return;

					int ItemStat = 0;
					itemStat.Enter();
					if (GetItemStat.count(IID))
						ItemStat = GetItemStat.find(IID)->second;
					itemStat.Leave();

					if (ItemStat != 10) {
						IPlayer.BoxMsg("You can not upgrade this item yet. Make sure its enchant level is 10.");
						return;
					}

					int Item2 = IPlayer.ItemPointerLock(JewelUse);

					if (!Item2)
						return;

					IItem ItemY((void*)Item2);

					if (!ItemY.Exists() || !isItemCustomWeapon(ItemY.CheckIndex()))
						return;

					int Index1 = ItemY.CheckIndex();

					if (ItemY.GetGrade() == 3)
						return;

					int ItemStat2 = 0;
					itemStat.Enter();
					if (GetItemStat.count(JewelUse))
						ItemStat2 = GetItemStat.find(JewelUse)->second;
					itemStat.Leave();

					if (ItemStat2 != 10) {
						IPlayer.BoxMsg("You can not upgrade this item yet. Make sure its second item enchant level is 10.");
						return;
					}

					if (CPlayer::RemoveItem((void*)Player, 9, 31, 100000000) && IPlayer.RemoveItem(Item2))
					{
						if (IPlayer.IsBuff(328))
							return;
						else
							IPlayer.Buff(328, 3, 0);

						int ReplacePrefix = 0, ReplaceItem = 0, ReplaceInfo = 0, ReplaceDef = 0, ReplaceEva = 0, ReplaceGem = 0;

						if (*(DWORD *)((int)Item + 44))
							ReplacePrefix = *(DWORD *)(*(DWORD *)((int)Item + 44) + 32);

						if (*(DWORD *)((int)Item + 48))
							ReplaceInfo = *(DWORD *)((int)Item + 48);

						if (ItemX.HighMemory() && *(DWORD *)((int)Item + 108))
							ReplaceDef = *(DWORD *)((int)Item + 108);

						if (ItemX.HighMemory() && *(DWORD *)((int)Item + 116))
							ReplaceEva = *(DWORD *)((int)Item + 116);

						if (*(DWORD *)((int)Item + 84))
							ReplaceGem = *(DWORD *)((int)Item + 84);

						int DeleteCheck = (*(int(__thiscall **)(DWORD, void *, signed int, signed int))(*(DWORD*)Item + 120))((int)Item, IPlayer.GetOffset(), 9, -1);

						if (!DeleteCheck)
						{
							CPlayer::_OutOfInven((void*)Player, Item);
							ReplaceItem = CItem::CreateItem(Index + 5, ReplacePrefix, 1, -1);

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

								if (CPlayer::InsertItem(IPlayer.GetOffset(), 27, ReplaceItem) != 1)
								{
									CConsole::Red("Real time armor insert item Null error [PID (%d)] ", IPlayer.GetPID());
									CBase::Delete((void *)ReplaceItem);
									return;
								}

								CIOObject::Release((void *)ReplaceItem);

								CDBSocket::Write(87, "ddd", IPlayer.GetPID(), *(DWORD *)(ReplaceItem + 84), *(DWORD *)(ReplaceItem + 36));
								CDBSocket::Write(21, "dddbb", *(DWORD *)(ReplaceItem + 36), *(DWORD *)(ReplaceItem + 32), *(DWORD *)(ReplaceItem + 48), 8, 7);
								if (ReplaceDef)
									CDBSocket::Write(17, "ddbbb", *(DWORD *)(ReplaceItem + 36), *(DWORD *)(ReplaceItem + 32), 15, *(DWORD *)(ReplaceItem + 108), 0);
								if (ReplaceEva)
									CDBSocket::Write(17, "ddbbb", *(DWORD *)(ReplaceItem + 36), *(DWORD *)(ReplaceItem + 32), 10, *(DWORD *)(ReplaceItem + 116), 0);
								CItem::SendItemInfo((void*)ReplaceItem, (int)IPlayer.GetOffset(), 92);
								CPlayer::Write(IPlayer.GetOffset(), 0xFF, "ddddd", 242, 0, 0, 128, 255);
							}
						}
					}
					else
						IPlayer.BoxMsg("Not Enough upgrade items to upgrade item.");
				}
				return;
			}
		}

		if (packet == 191) {
			if (GetInventorySize((int)IPlayer.GetOffset(), 0) >= 60)
			{
				CPlayer::Write(IPlayer.GetOffset(), 67, "b", 40);
				return;
			}

			int index = 0;

			char a1 = 0;
			CPacket::Read((char*)pPacket, (char*)pPos, "dd", &a1, &index);

			if (MonsterPet.count(index)) {
				CreateMonsterPet monsterPet = MonsterPet.find(index)->second;

				if (!CPlayer::FindItem((void*)Player, monsterPet.Material1, monsterPet.Count1) || !CPlayer::FindItem((void*)Player, monsterPet.Material2, monsterPet.Count2) || (monsterPet.Money && !CPlayer::FindItem((void*)Player, 31, monsterPet.Money)) || (monsterPet.Jewel && !CPlayer::FindItem((void*)Player, 31, monsterPet.Jewel))) {
					IPlayer.SystemMessage("Please make sure that you have all the required items to build your monster pet.", TEXTCOLOR_RED);
					return;
				}

				int Item1 = CPlayer::RemoveItem((void*)Player, 9, monsterPet.Material1, monsterPet.Count1);
				int Item2 = CPlayer::RemoveItem((void*)Player, 9, monsterPet.Material2, monsterPet.Count2);
				int Item3 = 0;

				if (monsterPet.Money)
					Item3 = CPlayer::RemoveItem((void*)Player, 9, 31, monsterPet.Money);
				else
					Item3 = 1;

				int Item4 = 0;
				if (monsterPet.Jewel)
					Item4 = CPlayer::RemoveItem((void*)Player, 9, JewelIndex, monsterPet.Jewel);
				else
					Item4 = 1;

				if (Item1 && Item2 && Item3 && Item4)
					CItem::InsertItem(Player, 27, index, 256, 1, -1);
				else
					IPlayer.SystemMessage("Please make sure that you have all the required items to build your monster pet.", TEXTCOLOR_RED);
			}
			return;
		}

		if (packet == 198) {
			int IID = 0, Type = 0;
			CPacket::Read((char*)pPacket, (char*)pPos, "dd", &Type, &IID);

			int Item = IPlayer.ItemPointerLock(IID);

			if (!Item)
				return;
			IItem IItem((void*)Item);

			if (SoulPockets.count((IItem.CheckIndex() * 1000) + Type)) {
				SoulPocketConfig SPC = SoulPockets.find((IItem.CheckIndex() * 1000) + Type)->second;

				itemStat.Enter();
				int stats = GetItemStat.count(IID) ? GetItemStat.find(IID)->second : 0;
				itemStat.Leave();

				int currentAmount = (IItem.GetInfo() & 1) ? IPlayer.GetBuffValue(BuffNames::SoulPocketAmount) : stats;
				if (SPC.Amount) {
					if ((SPC.Refill + currentAmount) > SPC.Max) {
						CPlayer::Write((void*)Player, 0xFE, "ddd", 210, 4, IItem.CheckIndex());
						return;
					}

					int bf = SPC.Refill;
					int RemoveCheck = 0;

					if (Type == 1)
						RemoveCheck = CPlayer::RemoveItem(IPlayer.GetOffset(), 9, JewelIndex, SPC.Amount);
					else if (Type == 2) {
						RemoveCheck = IPlayer.GetProperty(PlayerProperty::RPx) >= SPC.Amount ? 1 : 0;
						IPlayer.SetHonor(0, -SPC.Amount, 0, 0, 0, 0, 0, 0, 0, 0);
					}

					if (RemoveCheck) {
						if (IItem.GetInfo() & 1) {
							bf += IPlayer.GetBuffValue(BuffNames::SoulPocketAmount);
							IPlayer.UpdateBuff(BuffNames::SoulPocketAmount, BuffNames::BuffTime, bf);
							itemStat.Enter();
							GetItemStat[IID] = bf;
							itemStat.Leave();
						}
						else {
							bf += stats;
							itemStat.Enter();
							GetItemStat[IID] = bf;
							itemStat.Leave();
						}
						CDBSocket::Write(90, "dd", bf, IID);
						CItem::SendItemInfo((void*)Item, Player, 92);

						CPlayer::Write((void*)Player, 0xFE, "ddddd", 210, 0, IItem.CheckIndex(), SPC.Refill, Type);
					}
					else {
						CPlayer::Write((void*)Player, 0xFE, "ddd", 210, Type + 1, IItem.CheckIndex());
					}
				}
			}
			return;
		}

		if ((packet == 65 || packet == 66) && IPlayer.IsBuff(BuffNames::InitItemReload)) {
			IPlayer.SystemMessage("Some Items have been updated/reloaded, please relog to let it take effect.", TEXTCOLOR_RED);
			return;
		}

		if (packet == 66) {

			if (IPlayer.IsBuff(256))
			{
				IPlayer.SystemMessage("You need to wait 3 seconds to put off your item.", TEXTCOLOR_INFOMSG);
				return;
			}

			IPlayer.Buff(256, 2, 0);
		}

		if (packet == 65) {

			if (IPlayer.IsBuff(256))
			{
				IPlayer.SystemMessage("You need to wait 3 seconds to put on your item.", TEXTCOLOR_INFOMSG);
				return;
			}
			IPlayer.Buff(256, 2, 0);

			int IID = 0;
			CPacket::Read((char*)pPacket, (char*)pPos, "d", &IID);

			int Item = IPlayer.ItemPointerLock(IID);

			if (!Item)
				return;

			IItem IItem((void*)Item);

			int ItemGrade = CItem::GetLevel((int)IItem.GetOffset());
			int CurrentReborn = IPlayer.GetProperty(PlayerProperty::Reborn);

			if (RebornGear.count(ItemGrade) && CurrentReborn < RebornGear.find(ItemGrade)->second.Level){
				IPlayer.SystemMessage("You need to have atleast " + Int2String(RebornGear.find(ItemGrade)->second.Level) + " Reborn to equip this item", TEXTCOLOR_INFOMSG);
				return;
			}

			int MapX = IPlayer.GetX() >> 13;
			int MapY = IPlayer.GetY() >> 13;

			if (RentalItems.count(IItem.CheckIndex()) && (!PetLifeCheck.count(IItem.GetIID()) || (int)time(0) + 3 >= PetLifeCheck.findValue(IItem.GetIID()))) {
				if (!(!PetLifeCheck.count(IItem.GetIID()) && TimedItems.count(IItem.CheckIndex()))) {
					CPlayer::Write(IPlayer.GetOffset(), 0xFE, "db", 202, 4);
					CPlayer::Write(IPlayer.GetOffset(), 0xFE, "ddd", 201, IItem.GetIID(), 3);
					return;
				}
			}

			if (IPlayer.IsOnline() && (ItemDisable.count(IItem.CheckIndex()*(IPlayer.GetMap() + 1000)) || ItemDisable.count(IItem.CheckIndex()*(((MapX)+1000)*((MapY)+100))) || ItemDisable.count(IItem.CheckIndex() * 1255))) {
				IPlayer.SystemMessage("This item usage has been temporarly disabled", TEXTCOLOR_RED);
				return;
			}

			if (IPlayer.IsOnline() && TimedItems.count(IItem.CheckIndex()) && TimedItems.find(IItem.CheckIndex())->second.Wearable == 1 && !PetLifeCheck.count(IItem.GetIID())) {

				int Info = IItem.GetInfo();
				if (!(Info & 128)) {
					*(DWORD*)((int)Item + 48) += 128;
					CDBSocket::Write(21, "dddbb", IItem.GetIID(), IPlayer.GetID(), IItem.GetInfo(), 8, 7);
					CItem::SendItemInfo(IItem.GetOffset(), (int)IPlayer.GetOffset(), 92);
				}

				int GetPetTime = TimedItems.find(IItem.CheckIndex())->second.Time;
				//petLifeLock.Enter();
				PetLifeCheck.replaceInsert(IItem.GetIID(), (int)time(0) + GetPetTime);
				//petLifeLock.Leave();

				CDBSocket::Write(89, "ddd", IPlayer.GetPID(), (int)time(0) + GetPetTime, IItem.GetIID());
				CPlayer::Write(IPlayer.GetOffset(), 0xFF, "ddd", 230, IItem.GetIID(), GetPetTime);
				*(DWORD*)(Item + 68) = GetTickCount() + (2000 * GetPetTime);
				*(DWORD*)(Item + 72) = 0;
				ItemOnTimer(Item, 0, 0);
			}
		}

		if ((packet == 34 || packet == 35) && tradePVP && ((int)*(DWORD**)0x004E0964 == 4 || IPlayer.IsBuff(160) || IPlayer.IsBuff(180) || IPlayer.IsBuff(179) || IPlayer.IsBuff(161) || IPlayer.IsBuff(BuffNames::PTVsPTBlue) || IPlayer.IsBuff(BuffNames::PTVsPTRed) || IPlayer.IsBuff(162) || IPlayer.IsBuff(163) || IPlayer.IsBuff(170) || IPlayer.IsBuff(171) || IPlayer.IsBuff(373) || IPlayer.IsBuff(374) || IPlayer.IsBuff(902) || IPlayer.IsBuff(903) || IPlayer.IsBuff(BuffNames::LMS) || IPlayer.GetMap() == SVMap)) {
			IPlayer.SystemMessage("Trade system is disabled during battle mode.", TEXTCOLOR_RED);
			return;
		}


		//jail check 
		if (IPlayer.IsBuff(BuffNames::Jail)) {
			if ((packet == 34 || packet == 35)) {
				IPlayer.SystemMessage("Trading can not be done in jail.", TEXTCOLOR_RED);
				return;
			}

			if ((packet == 58 || packet == 67)) {
				IPlayer.CloseWindow("bazaa");
				IPlayer.SystemMessage("You are not allowed to be shopping in jail.", TEXTCOLOR_RED);
				return;
			}
		}

		if ((packet == 58 || packet == 67) && IPlayer.GetMap() == TBMap) {
			IPlayer.CloseWindow("bazaa");
			CPlayer::Write((void*)Player, 0xFE, "db", 172, 24);
			return;
		}

		if ((packet == 31 || packet == 61) && IPlayer.IsBuff(349))
			return;

		if (packet == 82 && IPlayer.GetBuffValue(BuffNames::RidingUsing)){
			IPlayer.DisableRiding();
			//		IPlayer.SystemMessage("Please un-equip your riding pet before transforming.", TEXTCOLOR_RED);
		}

		if (packet == 167 || packet == 149 || PacketBlock.count(packet))
			return;

		if (packet == 67 && CChar::IsGState(Player, 32)){
			IPlayer.SystemMessage("You can not fish and shop at the same time.", TEXTCOLOR_RED);
			return;
		}

		//if (packet == 67)
		//{
		//	int Start = 0;
		//	CPacket::Read((char*)pPacket, (char*)pPos, "b", &Start);

		//	if (IPlayer.IsOnline() && IPlayer.GetBuffValue(BuffNames::WeaponWear))
		//	{
		//		int ItemIID = IPlayer.GetBuffValue(BuffNames::WeaponWear);
		//		IItem IItem((void*)ItemIID);

		//		if (IItem.Exists() && CItem::IsState((int)IItem.GetOffset(), 1)){
		//			CPlayer::SwitchStall((void*)Player, Start);
		//			return;
		//		}
		//	}
		//}

		if (IPlayer.IsOnline() && packet == C2S_Shop && !IPlayer.IsBuff(3959))
		{
			if (ShoppingLimit && ShopLimit.count(sha256(IPlayer.GetHWID() + IPlayer.GetIP())) && ShopLimit.find(sha256(IPlayer.GetHWID() + IPlayer.GetIP()))->second >= ShoppingLimit) {
				IPlayer.SystemMessage("Exceeded Shop Limit.", TEXTCOLOR_RED);
				return;
			}
		}

		if (packet == 71)
		{
			char Items = 0; int Value = 0, IID = 0;;
			int crPacket = CPacket::Read((char*)pPacket, (char*)pPos, "ddb", &Value, &IID, &Items);

			if (Value > 0) {
				TargetFind myTarget(0, 0, Value);
				void* PlayerShop = myTarget.getTarget();
				IChar Shop(PlayerShop);
				if (Shop.IsOnline())
					Shop.Buff(2019, BuffNames::BuffTime, IPlayer.GetID());
			}

			if (Value < 0 && FakePlayers.count(Value) && (EFakePlayers*-1) <= Value) {
				FakePlayers_ fPlayer = FakePlayers.findValue(Value);
				if (fPlayer.state == 2) {
					ConcurrentMap<int, int>Insert;
					Insert.clear();
					int totalprice = 0;
					for (int i = 0; i < Items; ++i)
					{
						int xiid = 0, xamount = 0;
						crPacket = CPacket::Read((char*)crPacket, (char*)pPos, "dd", &xiid, &xamount);
						if (FakeItems.count(xiid)) {
							FakeItems_ fItem = FakeItems.findValue(xiid);
							if (fItem.amount >= xamount) {
								Insert[fItem.index] = xamount;
								totalprice += fItem.price * xamount;
							}
						}
					}
					int GeonsCheck = CPlayer::FindItem(IPlayer.GetOffset(), 31, totalprice);

					if (GeonsCheck && totalprice > 0)
					{
						CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 31, totalprice);
						for (auto x = Insert.begin(); x != Insert.end(); x++)
						{
							CItem::InsertItem((int)IPlayer.GetOffset(), 27, x->first, 0, x->second, -1);
							if (fPlayer.Shop.count(x->first)) {
								FakePlayers_Shop fShop = fPlayer.Shop.findValue(x->first);

								if (fShop.amount == x->second) {
									FakeItems.erase(fShop.iid);
									fPlayer.Shop.erase(x->first);
								}
								else {
									if (FakeItems.count(fShop.iid)) {
										FakeItems_ fItem = FakeItems.findValue(fShop.iid);
										fShop.amount -= x->second;
										fPlayer.Shop.replaceInsert(x->first, fShop);
										fItem.amount -= x->second;
										FakeItems.replaceInsert(fShop.iid, fItem);
									}
								}
							}
						}
						if (fPlayer.Shop.size() > 0) {
							unsigned char Items = fPlayer.Shop.size();
							size_t Size = Items * 71;
							char *Packet = new char[Size];
							int xi = 0;
							for (auto x = fPlayer.Shop.begin(); x != fPlayer.Shop.end(); x++)
							{
								int CurEnd = 0;
								int intItem = CItem::FindInitItem(x->first);
								if (intItem) {
									int Ipointer = CItem::NewItem(intItem);
									if (Ipointer) {
										CIOObject::AddRef(Ipointer);
										IItem Item((void*)Ipointer);
										CurEnd = Item.GetIntEndurance();
										CBase::Delete((void*)Ipointer);
										CIOObject::Release((void*)Ipointer);
									}
								}

								Tools->Compile(Packet + xi * 71, "wdbddbbbbbbbbwbbbbbdbwwwwbbbbbbbbbbdbbwbbdd", x->first, x->second.iid, 0, 0, x->second.amount, CurEnd, CurEnd,
									0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, x->second.price);
								xi++;
							}
							CPlayer::Write(IPlayer.GetOffset(), 13, "bddbbm", 0, Value, 0, Items, 0, Packet, Size);
							delete[] Packet;
						}
						else {
							CChar::WriteInSight(IPlayer.GetOffset(), 61, "dbb", Value, 11, 0);
							CChar::WriteInSight(IPlayer.GetOffset(), 13, "d", 0);
							fPlayer.gstate = 0;
						}
						FakePlayers.replaceInsert(Value, fPlayer);
					}
				}
				return;
			}
		}
		if (packet == 70)
		{
			char Type = 0; int Value = 0;
			CPacket::Read((char*)pPacket, (char*)pPos, "bd", &Type, &Value);
			if (Value < 0 && FakePlayers.count(Value) && (EFakePlayers*-1) <= Value) {
				FakePlayers_ fPlayer = FakePlayers.findValue(Value);
				if (fPlayer.check && fPlayer.state == 2 && fPlayer.Shop.size() > 0) {
					if (Type == 1)
						CPlayer::Write(IPlayer.GetOffset(), 13, "bds", 1, Value, fPlayer.msg.c_str());
					else {
						unsigned char Items = fPlayer.Shop.size();
						size_t Size = Items * 71;
						char *Packet = new char[Size];
						int xi = 0;
						for (auto x = fPlayer.Shop.begin(); x != fPlayer.Shop.end(); x++)
						{
							int CurEnd = 0;
							int intItem = CItem::FindInitItem(x->first);
							if (intItem) {
								int Ipointer = CItem::NewItem(intItem);
								if (Ipointer) {
									CIOObject::AddRef(Ipointer);
									IItem Item((void*)Ipointer);
									CurEnd = Item.GetIntEndurance();
									CBase::Delete((void*)Ipointer);
									CIOObject::Release((void*)Ipointer);
								}
							}

							Tools->Compile(Packet + xi * 71, "wdbddbbbbbbbbwbbbbbdbwwwwbbbbbbbbbbdbbwbbdd", x->first, x->second.iid, 0, 0, x->second.amount, CurEnd, CurEnd,
								0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, x->second.price);
							xi++;
						}
						CPlayer::Write(IPlayer.GetOffset(), 13, "bddbbm", 0, Value, 0, Items, 0, Packet, Size);
						delete[] Packet;
					}
				}
				return;
			}
		}

		if (packet == 34)
		{
			int ID = 0;
			CPacket::Read((char*)pPacket, (char*)pPos, "d", &ID);
			if (ID < 0 && FakePlayers.count(ID) && (EFakePlayers*-1) <= ID) {
				CPlayer::Write(IPlayer.GetOffset(), 67, "b", 19);
				return;
			}
			if (IPlayer.GetMap() == TBMap) {
				CPlayer::Write((void*)Player, 0xFE, "db", 172, 22);
				return;
			}

			TargetFind myTarget(0, 0, ID);
			IChar ITarget((void*)myTarget.getTarget());
			if (ITarget.IsBuff(BuffNames::Jail)) {
				IPlayer.SystemMessage("Can not trade jailed player.", TEXTCOLOR_RED);
				return;
			}
		}

		if (packet == 44) {
			int TargetID;
			CPacket::Read((char*)pPacket, (char*)pPos, "d", &TargetID);
			if (TargetID < 0 && FakePlayers.count(TargetID) && (EFakePlayers*-1) <= TargetID) {
				CPlayer::Write((void*)Player, 68, "bs", 28, FakePlayers.findValue(TargetID).name.c_str());
				return;
			}

			if (IPlayer.GetMap() == TBMap) {
				TargetFind myTarget(0, 0, TargetID);
				IChar ITarget((void*)myTarget.getTarget());
				if (IPlayer.GetBuffValue(BuffNames::TriangularType) != ITarget.GetBuffValue(BuffNames::TriangularType)) {
					CPlayer::Write((void*)Player, 0xFE, "db", 172, 21);
					return;
				}
			}
		}

		if (packet == 80)
		{
			int Value = 0;
			CPacket::Read((char*)pPacket, (char*)pPos, "d", &Value);
			if (Value < 0 && FakePlayers.count(Value) && (EFakePlayers*-1) <= Value)
				return;
		}

		if (packet == 122) {
			if (CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 1122, 1))
				IPlayer.Buff(24, 10, 0);

			return;
		}

		if (packet == 195) {
			int type = 0, type2 = 0;
			CPacket::Read((char*)pPacket, (char*)pPos, "dd", &type, &type2);

			IItem IItem((void*)IPlayer.GetBuffValue(BuffNames::RidingUsing));
			if (!IItem.Exists())
				return;

			if (type == 1 && !type2) {
				int RPx = IPlayer.GetProperty(PlayerProperty::RPx);
				if (RPx < 300) {
					IPlayer.SystemMessage("A Battle Horse's satiety could not be recovered because honor points are not enough.", TEXTCOLOR_YELLOW);
					return;
				}
				IPlayer.SetHonor(0, -300, 0, 0, 0, 0, 0, 0, 0, 0);
				updateSatiety(IPlayer, 5);
			}

			if (type == 2) {
				if (type2) {
					int JewelCheck = CPlayer::FindItem(IPlayer.GetOffset(), JewelIndex, 42);
					if (JewelCheck) {
						if (!(*(int(__thiscall **)(DWORD, void *, signed int, signed int))(*(DWORD*)JewelCheck + 120))((int)JewelCheck, IPlayer.GetOffset(), 9, -42))
							CPlayer::_OutOfInven((void*)Player, JewelCheck);

						if (IItem.CheckIndex() == 7881)
							updateSatiety(IPlayer, 300);
						else
							updateSatiety(IPlayer, 200);
					}
					else {
						IPlayer.SystemMessage("A Battle Horse's satiety could not be recovered because jewels are not enough.", TEXTCOLOR_YELLOW);
						return;
					}
				}
				else {
					int JewelCheck = CPlayer::FindItem(IPlayer.GetOffset(), JewelIndex, 6);
					if (JewelCheck) {
						if (!(*(int(__thiscall **)(DWORD, void *, signed int, signed int))(*(DWORD*)JewelCheck + 120))((int)JewelCheck, IPlayer.GetOffset(), 9, -6))
							CPlayer::_OutOfInven((void*)Player, JewelCheck);

						updateSatiety(IPlayer, 30);
					}
					else {
						IPlayer.SystemMessage("A Battle Horse's satiety could not be recovered because jewels are not enough.", TEXTCOLOR_YELLOW);
						return;
					}
				}
			}
			IPlayer.SystemMessage("A Battle Horse's satiety is recovered.", TEXTCOLOR_GREEN);
			return;
		}

		if (packet == 185) {
			char type = 0;
			int IID = 0;
			CPacket::Read((char*)pPacket, (char*)pPos, "bd", &type, &IID);

			int Item = IPlayer.ItemPointerLock(IID);

			if (!Item)
				return;

			IItem ItemRental((void*)Item);

			if (!RentalItems.count(ItemRental.CheckIndex()))
				return;

			RentalExtend rental = RentalItems.find(ItemRental.CheckIndex())->second;
			int JewelCheck = CPlayer::FindItem(IPlayer.GetOffset(), JewelIndex, rental.Price);
			if (JewelCheck) {
				int Time = (int)time(0) + rental.Time;
				//petLifeLock.Enter();
				if (PetLifeCheck.count(IID) && PetLifeCheck.findValue(IID) > (int)time(0))
					Time = PetLifeCheck.findValue(IID) + rental.Time;
				//petLifeLock.Leave();

				if (Time - (int)time(0) >= 15552000) {
					CPlayer::Write(IPlayer.GetOffset(), 0xFE, "db", 202, 7);
					CPlayer::Write(IPlayer.GetOffset(), 0xFE, "db", 202, 2);
					return;
				}

				if (!(*(int(__thiscall **)(DWORD, void *, signed int, signed int))(*(DWORD*)JewelCheck + 120))((int)JewelCheck, IPlayer.GetOffset(), 9, -rental.Price))
					CPlayer::_OutOfInven((void*)Player, JewelCheck);

				*(DWORD*)(Item + 68) = GetTickCount() + (2000 * (Time - (int)time(0)));
				*(DWORD*)(Item + 72) = 0;
				//petLifeLock.Enter();
				PetLifeCheck.replaceInsert(IID, Time);
				//petLifeLock.Leave();
				CDBSocket::Write(89, "ddd", IPlayer.GetPID(), Time, IID);
				CPlayer::Write(IPlayer.GetOffset(), 0xFF, "ddd", 230, IID, Time - (int)time(0));
				IPlayer.CloseWindow("rental_extend_question");
				CPlayer::Write(IPlayer.GetOffset(), 0xFE, "ddd", 201, IID, 2);
				IPlayer.SystemMessage("Your item's rental period has been increased.", TEXTCOLOR_GREEN);
				CItem::OnTimer(Item, 0);
			}
			else
				CPlayer::Write(IPlayer.GetOffset(), 0xFE, "db", 202, 3);

			return;
		}

		if (packet == 190) {
			int diceValue = CTools::Rate(1, 6);
			CChar::WriteInSight((void*)Player, 206, "dd", IPlayer.GetID(), diceValue);
			return;
		}

		if (packet == 24) {
			int Store = 0, Npc = 0, Tax = 0, ItemSize = 0;
			int NPCPacket = CPacket::Read((char*)pPacket, (char*)pPos, "ddbb", &Store, &Npc, &Tax, &ItemSize);

			int Check = NPCPacket, Amount = 0, Index = 0, Item = 0, Price = 0;
			unsigned __int16 ItemIndex = 0, ItemAmount = 0;

			if (ItemSize <= 0)
				return;

			if (ItemSize > 100)
				return;

			bool StoreCheck = !StoreItems.empty();
			ConcurrentSet<int> StoreItem;

			if (StoreCheck) {
				auto it = StoreItems.find(Store);
				if (it == StoreItems.end())
				{
					IPlayer.SystemMessage("You are not allowed to buy from this store.", TEXTCOLOR_RED);
					return;
				}
				StoreItem = it->second;
			}

			for (int i = 0; *((DWORD*)Player + 274) && i < ItemSize; i++)
			{
				Check = CPacket::Read((char*)Check, (char*)pPos, (const char*)0x004BADB4, &ItemIndex, &ItemAmount);
				Amount = ItemAmount; Index = ItemIndex;

				if (Amount > 0)
				{
					if (StoreCheck && !StoreItem.count(Index)) {
						IPlayer.SystemMessage("You are not allowed to buy this item from this store.", TEXTCOLOR_RED);
						return;
					}

					Item = CItem::CreateItem(Index, 0, Amount, -1);

					if (Item)
					{
						CIOObject::AddRef(Item);
						Price = (int)*(DWORD*)(*(DWORD*)(Item + 40) + 108);

						if ((Price * Amount) > 2000000000)
						{
							IPlayer.SystemMessage("You are not allowed to buy this amount from this store.", TEXTCOLOR_RED);
							CBase::Delete((void*)Item);
							return;
						}

						if (Price <= 0)
						{
							CBase::Delete((void*)Item);
							return;
						}

						int Check = 2147483647 / Price;

						if (Amount >= Check)
						{
							CBase::Delete((void*)Item);
							return;
						}

						CBase::Delete((void*)Item);
						CIOObject::Release((void*)Item);
						//int SoldCheck = Price * Amount;
						//CDBSocket::Write(122, "d", SoldCheck);
					}
				}
			}

			CPlayer::BuyItemEx((void*)Player, Npc, Tax, ItemSize, NPCPacket, pPos);
			return;
		}

		if (packet == 97) {
			int Type = 0;
			char NPC = 0;
			CPacket::Read((char*)pPacket, (char*)pPos, "db", &Type, &NPC);
			int NPCOffset = CNPC::FindNPC(Type);

			if (NPCOffset) {
				if (*(DWORD*)(NPCOffset + 456) == 866) {
					int Amount = IPlayer.GetLevel() * 1000;
					if (CPlayer::RemoveItem((void*)Player, 9, 31, Amount)) {
						int Time = IPlayer.GetBuffValue(BuffNames::TrainingTime);
						if (!IPlayer.IsBuff(BuffNames::TrainingFree)) {
							int Hour = 23 - String2Int(Time::GetHour());
							int Minutes = 59 - String2Int(Time::GetMinute());
							int TimeLeft = (Hour * 60 * 60) + (Minutes * 60) + String2Int(Time::GetSecond());
							Time += (FreeTime / 1000);
							IPlayer.SaveBuff(BuffNames::TrainingFree, TimeLeft);
							IPlayer.SaveBuff(BuffNames::TrainingTime, BuffNames::BuffTime, Time, 0, 0);
						}
						IPlayer.Teleport(0, 272124, 347854);

						CPlayer::Write((void*)Player, 0xFE, "dd", 207, Time / 60);
					}
					CIOObject::Release((void*)NPCOffset);
					return;
				}
				CIOObject::Release((void*)NPCOffset);
			}
		}

		if (packet == 180) {
			unsigned short type = 0;
			char rateCount = 0;
			int IID1 = 0, IID2 = 0;
			CPacket::Read((char*)pPacket, (char*)pPos, "wddb", &type, &IID1, &IID2, &rateCount);

			if (IID1 == IID2)
				return;

			if (MasterEnchant.count(type)) {
				MasterEnchanting mEnchant = MasterEnchant.find(type)->second;

				if (!EnchantCount.count((mEnchant.Rate * 1000) + rateCount))
					return;

				int ItemIn = IPlayer.ItemPointerLock(IID1);
				int ItemMaterial = IPlayer.ItemPointerLock(IID2);

				if (!ItemIn || !ItemMaterial)
					return;

				IItem IItem1((void*)ItemMaterial);

				if (IItem1.CheckIndex() != mEnchant.MaterialUsed || IItem1.GetAmount() < rateCount)
					return;

				if (!IPlayer.RemoveItemPointer(ItemMaterial, rateCount))
					return;

				IItem IItemIn((void*)ItemIn);
				int ItemIndex = IItemIn.CheckIndex();

				if (ItemIndex != mEnchant.IndexIn)
					return;

				if (CTools::Rate(0, 1000) <= EnchantCount.find((mEnchant.Rate * 1000) + rateCount)->second) {
					int ReplacePrefix = 0, ReplaceItem = 0, ReplaceInfo = 0, ReplaceDef = 0, ReplaceEva = 0, ReplaceGem = 0, ReplaceA = 0, ReplaceM = 0, ReplaceTOA = 0, ReplaceEB = 0, ReplaceMaxEnd = 0, ReplaceNum = 0;


					int ItemStat = 0;

					itemStat.Enter();
					if (GetItemStat.count(*(DWORD *)((int)ItemIn + 36)))
						ItemStat = GetItemStat.find(*(DWORD *)((int)ItemIn + 36))->second;
					itemStat.Leave();

					if (*(DWORD *)((int)ItemIn + 44))
						ReplacePrefix = *(DWORD *)(*(DWORD *)((int)ItemIn + 44) + 32);

					if (*(DWORD *)((int)ItemIn + 48))
						ReplaceInfo = *(DWORD *)((int)ItemIn + 48);

					if (IItemIn.IsTransform()) {
						if (*(DWORD *)((int)ItemIn + 92))
							ReplaceMaxEnd = *(DWORD *)((int)ItemIn + 92);

						if (*(DWORD *)((int)ItemIn + 96))
							ReplaceNum = *(DWORD *)((int)ItemIn + 96);
					}

					if (IItemIn.HighMemory()) {

						if (*(DWORD *)((int)ItemIn + 100))
							ReplaceA = *(DWORD *)((int)ItemIn + 100);

						if (*(DWORD *)((int)ItemIn + 104))
							ReplaceM = *(DWORD *)((int)ItemIn + 104);

						if (!IItemIn.IsTransform()) {
							if (*(DWORD *)((int)ItemIn + 108))
								ReplaceDef = *(DWORD *)((int)ItemIn + 108);

							if (*(DWORD *)((int)ItemIn + 116))
								ReplaceEva = *(DWORD *)((int)ItemIn + 116);

							if (IItemIn.IsWeapon()) {
								if (*(DWORD *)((int)ItemIn + 112))
									ReplaceTOA = *(DWORD *)((int)ItemIn + 112);

								if (*(DWORD *)((int)ItemIn + 124))
									ReplaceEB = *(DWORD *)((int)ItemIn + 124);
							}
						}
					}

					if (*(DWORD *)((int)ItemIn + 84))
						ReplaceGem = *(DWORD *)((int)ItemIn + 84);

					if (IPlayer.RemoveItemLock(ItemIn))
					{
						if (ItemIndex == 337 || ItemIndex == 338 || ItemIndex == 339 || ItemIndex == 1596) {
							int possibleIndexes[] = { 337, 338, 339, 1596 };
							int numberOfIndexes = sizeof(possibleIndexes) / sizeof(possibleIndexes[0]);

							int randomIndex;

							do {
								srand(static_cast<unsigned int>(time(0)));

								randomIndex = possibleIndexes[rand() % numberOfIndexes];
							} while (randomIndex == ItemIndex);

							ReplaceItem = CItem::CreateItem(randomIndex, ReplacePrefix, 1, -1);
						}
						else
							ReplaceItem = CItem::CreateItem(mEnchant.IndexOut, ReplacePrefix, 1, -1);

						if (ReplaceItem)
						{
							IItem IItemOut((void*)ReplaceItem);
							CIOObject::AddRef(ReplaceItem);

							if (ReplaceInfo)
								*(DWORD *)(ReplaceItem + 48) = ReplaceInfo;
							if (ReplaceGem)
								*(DWORD *)(ReplaceItem + 84) = ReplaceGem;
							if (IItemOut.IsTransform())
							{
								if (ReplaceMaxEnd)
									*(DWORD *)(ReplaceItem + 92) = ReplaceMaxEnd;
								if (ReplaceNum)
									*(DWORD *)(ReplaceItem + 96) = ReplaceNum;
							}

							if (IItemOut.HighMemory()) {
								if (ReplaceA)
									*(DWORD *)(ReplaceItem + 100) = ReplaceA;
								if (ReplaceM)
									*(DWORD *)(ReplaceItem + 104) = ReplaceM;
								if (!IItemOut.IsTransform()) {
									if (ReplaceDef)
										*(DWORD *)(ReplaceItem + 108) = ReplaceDef;
									if (ReplaceEva)
										*(DWORD *)(ReplaceItem + 116) = ReplaceEva;
									if (IItemIn.IsWeapon()) {
										if (ReplaceTOA)
											*(DWORD *)(ReplaceItem + 112) = ReplaceTOA;
										if (ReplaceEB)
											*(DWORD *)(ReplaceItem + 124) = ReplaceEB;

									}
								}
							}

							if (CPlayer::InsertItem((void*)Player, 27, ReplaceItem) != 1)
							{
								CConsole::Red("Real time armor insert item Null error [PID (%d)] ", IPlayer.GetPID());
								CBase::Delete((void *)ReplaceItem);
								return;
							}

							CIOObject::Release((void *)ReplaceItem);

							int IID = *(DWORD *)(ReplaceItem + 36);

							if (ItemStat) {
								itemStat.Enter();
								GetItemStat[IID] = ItemStat;
								itemStat.Leave();
								CDBSocket::Write(90, "dd", ItemStat, IID);
							}

							if (ReplaceGem)
								CDBSocket::Write(87, "ddd", IPlayer.GetPID(), ReplaceGem, IID);
							if (ReplaceInfo)
								CDBSocket::Write(21, "dddbb", IID, IPlayer.GetPID(), ReplaceInfo, 8, 7);
							if (ReplaceDef)
								CDBSocket::Write(17, "ddbbb", IID, IPlayer.GetPID(), 15, ReplaceDef, 0);
							if (ReplaceEva)
								CDBSocket::Write(17, "ddbbb", IID, IPlayer.GetPID(), 10, ReplaceEva, 0);
							if (ReplaceA)
								CDBSocket::Write(17, "ddbbb", IID, IPlayer.GetPID(), 27, ReplaceA, 0);
							if (ReplaceM)
								CDBSocket::Write(17, "ddbbb", IID, IPlayer.GetPID(), 28, ReplaceM, 0);
							if (ReplaceTOA)
								CDBSocket::Write(17, "ddbbb", IID, IPlayer.GetPID(), 9, ReplaceTOA, 0);
							if (ReplaceEB)
								CDBSocket::Write(28, "ddbb", IID, IPlayer.GetPID(), 2, ReplaceEB);
							if (ReplaceMaxEnd)
								CDBSocket::Write(125, "dddd", 1, IPlayer.GetPID(), ReplaceMaxEnd, IID);
							if (ReplaceNum)
								CDBSocket::Write(125, "ddddd", 2, IPlayer.GetPID(), 0, IID, ReplaceNum);

							CItem::SendItemInfo((void*)ReplaceItem, (int)IPlayer.GetOffset(), 92);
							CPlayer::Write(IPlayer.GetOffset(), 0xFF, "ddddd", 242, 0, 0, 128, 255);
							CPlayer::Write((void*)Player, 0xFE, "dbd", 193, 0, IID);
						}
					}
				}
				else {
					if (IItemIn.HighMemory()) {
						int CurEndurance = IItemIn.GetEndurance();
						if (CurEndurance) {
							int CheckPolish = CItem::IsState((int)IItemIn.GetOffset(), 64);

							if (CheckPolish)
							{
								CDBSocket::Write(21, "dddbb", IItemIn.GetIID(), IPlayer.GetID(), 64, 0, 255);
								CItem::SubState((int)IItemIn.GetOffset(), 64);
								CItem::SendItemInfo(IItemIn.GetOffset(), (int)IPlayer.GetOffset(), 92);
							}
							else {
								if (CurEndurance >= 5)
									IItemIn.DecreaseEndurance(5);
								else
									IItemIn.DecreaseEndurance(CurEndurance);

								if (IItemIn.GetEndurance() <= 0)
								{
									CPlayer::Write(IPlayer.GetOffset(), 91, "db", IItemIn.GetIID(), IItemIn.GetEndurance());
									CDBSocket::Write(3, "ddwdbddd", IItemIn.GetIID(), IPlayer.GetID(), IItemIn.CheckIndex(), 1, 27, 0, 0, 0);

									if (CItem::GetLevel((int)IItemIn.GetOffset()) >= 40)
										CItem::InsertItem((int)IPlayer.GetOffset(), 27, 517, 0, 15, -1);

									CBase::Delete(IItemIn.GetOffset());

									IPlayer.CloseWindow("master_enchant_rates");

									CPlayer::Write((void*)Player, 0xFE, "db", 193, 2);
									return;
								}
								else {
									CPlayer::Write(IPlayer.GetOffset(), 91, "db", IItemIn.GetIID(), IItemIn.GetEndurance());
									CDBSocket::Write(18, "ddb", IItemIn.GetIID(), IPlayer.GetID(), IItemIn.GetEndurance());
								}
							}
						}
					}

					CPlayer::Write((void*)Player, 0xFE, "db", 193, 1);
				}
			}
			return;
		}

		if (packet == 169) {
			char type = 0;
			int index = 0, IID1 = 0, IID2 = 0;
			CPacket::Read((char*)pPacket, (char*)pPos, "bddd", &type, &index, &IID1, &IID2);

			if (IID1 == IID2)
				return;

			if (type == 1) {
				if (InitPetSwap.count(index)) {
					InitSwap swap = InitPetSwap.find(index)->second;

					int Item1 = IPlayer.ItemPointerLock(IID1);
					int Item2 = IPlayer.ItemPointerLock(IID2);

					if (!Item1 || !Item2)
						return;

					IItem IItem1((void*)Item1);
					IItem IItem2((void*)Item2);

					if (IItem1.Exists() && IItem2.Exists()) {
						if ((IItem1.CheckIndex() == swap.Material1.Index || IItem1.CheckIndex() == swap.Material12.Index) && (IItem2.CheckIndex() == swap.Material2.Index || IItem2.CheckIndex() == swap.Material22.Index)) {

							if (!IPlayer.RemoveItemLock(Item1) || !IPlayer.RemoveItemLock(Item2))
								return;

							int Rate = CTools::Rate(0, 100000);
							for (int i = 0; i < (int)swap.items.size(); i++) {
								if (Rate <= swap.items[i].Chance) {
									CItem::InsertItem(Player, 27, swap.items[i].Index, 0, 1, -1);
									break;
								}
							}
						}
					}
				}
			}
			return;
		}

		if (packet == 192) {
			int nbHours = 0;
			CPacket::Read((char*)pPacket, (char*)pPos, "d", &nbHours);

			if (nbHours <= 0)
				return;

			int JewelCheck = CPlayer::FindItem(IPlayer.GetOffset(), JewelIndex, nbHours*TrainingPrice);
			if (JewelCheck) {
				if (!(*(int(__thiscall **)(DWORD, void *, signed int, signed int))(*(DWORD*)JewelCheck + 120))(JewelCheck, IPlayer.GetOffset(), 9, -(nbHours*TrainingPrice)))
					CPlayer::_OutOfInven((void*)Player, JewelCheck);

				int Time = IPlayer.GetBuffValue(BuffNames::TrainingTime) + (nbHours * 3600);
				IPlayer.SaveBuff(BuffNames::TrainingTime, BuffNames::BuffTime, Time, 0, 0);
				IPlayer.CloseWindow("trainingcountsimple");
				CPlayer::Write((void*)Player, 0xFE, "dd", 207, Time / 60);
			}
			else
				IPlayer.SystemMessage("You do not have enough jewels to extend your training time.", TEXTCOLOR_RED);

			return;
		}

		if (packet == 193) {
			if (IPlayer.GetBuffValue(BuffNames::TrainingTime))
				IPlayer.SystemMessage("Let’s start a training.", TEXTCOLOR_GENERAL);
			return;
		}

		if (packet == 196) {
			int Type = 0;
			CPacket::Read((char*)pPacket, (char*)pPos, "d", &Type);

			if (Type < 1) {
				IPlayer.SystemMessage("Wrong Namepad color.", TEXTCOLOR_RED);
				return;
			}

			if (Type == IPlayer.GetBuffValue(BuffNames::NamePad)) {
				CPlayer::Write((void*)Player, 0xFE, "dd", 208, 3);
				return;
			}

			int JewelCheck = CPlayer::FindItem(IPlayer.GetOffset(), namePadIndex, namePadPrice);

			if (JewelCheck) {
				if (!(*(int(__thiscall **)(DWORD, void *, signed int, signed int))(*(DWORD*)JewelCheck + 120))((int)JewelCheck, IPlayer.GetOffset(), 9, -namePadPrice))
					CPlayer::_OutOfInven((void*)Player, JewelCheck);

				IPlayer.SaveBuff(BuffNames::NamePad, 86400 * namePadDuration, Type, 9900, 9900);
				CChar::WriteInSight((void*)Player, 0xFE, "ddd", 209, IPlayer.GetID(), Type);
				CPlayer::Write((void*)Player, 0xFE, "dd", 208, 0);
				IPlayer.SystemMessage("Your name color has been successfully changed for 7 days.", TEXTCOLOR_GREEN);
			}
			else {
				CPlayer::Write((void*)Player, 0xFE, "dd", 208, 2);
			}

			return;
		}

		if (packet == 188) {
			int JewelCheck = CPlayer::FindItem(IPlayer.GetOffset(), ExpansionIndex, ExpansionAmount);

			if (JewelCheck) {
				int IETime = ExtensionTime;
				if (!IPlayer.IsBuff(BuffNames::Extension1)) {
					if (!(*(int(__thiscall **)(DWORD, void *, signed int, signed int))(*(DWORD*)JewelCheck + 120))((int)JewelCheck, IPlayer.GetOffset(), 9, -ExpansionAmount))
						CPlayer::_OutOfInven((void*)Player, JewelCheck);

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
					IPlayer.BoxMsg("You have successfully Expanded your inventory by 36 more slots for 15 days.");
				}
				else
					IPlayer.BoxMsg("You have already expanded your inventory to the max you could!");
			}
			else
				IPlayer.SystemMessage("You do not have enough gems to expand your inventory!", TEXTCOLOR_RED);
			return;
		}

		if (packet == 218){
			if (MD5Check == 1)
			{
				int engineCheck = 0, Type = 0, Veri = 0;
				CPacket::Read((char*)pPacket, (char*)pPos, "ddd", &Type, &Veri, &engineCheck);

				if (Type != 13 || Veri != 2513 || !engineCheck){
					IPlayer.SystemMessage("Illegal Files detected. Re-extract your client", TEXTCOLOR_RED);
					IPlayer.Kick();
					return;
				}
				else
				if (engineCheck != catchInt(ConfigEngine)){
					IPlayer.SystemMessage("Illegal Files detected. Re-extract your client", TEXTCOLOR_RED);
					IPlayer.Kick();
					return;
				}
				else{
					IPlayer.Buff(3076, 900, 0);
				}
			}
			return;
		}


		if (packet == 215){
			const char *pcname = "none";
			int Type = 0, hwid = 0;
			CPacket::Read((char*)pPacket, (char*)pPos, "dsd", &Type, &pcname, 17, &hwid);

			if (hwid)
				User[IPlayer.GetPID()].Hardware.assign((Int2String(hwid)));
			if (strlen(pcname))
				User[IPlayer.GetPID()].PCName.assign(pcname);

			return;
		}

		// Assume you have a function to get the packet name from an enum value

		//if (packetDebugger == 1) {
		//	std::string Dato = "./Debugger/Packet/PACKETS_" + Time::GetDay() + "_" + Time::GetMonth() + "_" + Time::GetYear() + "_" + Time::GetHour() + "." + Time::GetMinute() + ".txt";
		//	std::fstream DGLOG;
		//	DGLOG.open(Dato, std::fstream::in | std::fstream::out | std::fstream::app);
		//	DGLOG << Time::GetTime() << " " << IPlayer.GetName() << ": " << GetPacketName(packet) << std::endl;
		//	DGLOG.close();
		//	
		//}

		if (packetDebugger == 1) {
			std::string Dato = "./Debugger/Packet/PACKETS_" + Time::GetDay() + "_" + Time::GetMonth() + "_" + Time::GetYear() + "_" + Time::GetHour() + "." + Time::GetMinute() + ".txt";

			std::ofstream DGLOG(Dato, std::ofstream::app);

			if (DGLOG.is_open()) {
				DGLOG << Time::GetTime() << " " << IPlayer.GetName() << ": " << GetPacketName(packet) << std::endl;
				DGLOG.flush();  // Flush the stream
			}
			else {
				CConsole::Red("Error opening Packets_Debug File");
			}
		}

		if (IPlayer.GetBuffValue(BuffNames::BetOpponent)) {
			if (packet == 36) {
				TargetFind myTarget(0, 0, IPlayer.GetBuffValue(BuffNames::BetOpponent));
				void *Target = myTarget.getTarget();
				IChar ITarget(Target);
				ITarget.UpdateBuff(BuffNames::BetOpponent, BuffNames::BuffTime, 0);
				IPlayer.UpdateBuff(BuffNames::BetOpponent, BuffNames::BuffTime, 0);
				IPlayer.CancelBuff(BuffNames::BetType);
				ITarget.CancelBuff(BuffNames::BetType);
				IPlayer.CancelBuff(257);
				ITarget.CancelBuff(257);
				BetItems.erase(IPlayer.GetPID() * ITarget.GetPID());
			}

			if (packet == 62) {
				TargetFind myTarget(0, 0, IPlayer.GetBuffValue(BuffNames::BetOpponent));
				void *Target = myTarget.getTarget();
				IChar ITarget(Target);
				if (ITarget.IsOnline()) {
					IPlayer.UpdateBuff(BuffNames::BetType, BuffNames::BuffTime, 1);
					if (ITarget.GetBuffValue(BuffNames::BetType) == 1) {
						if (CPlayer::_CheckTrade((int)IPlayer.GetOffset()) && CPlayer::_CheckTrade((int)ITarget.GetOffset()) && BetItems.count(IPlayer.GetPID() * ITarget.GetPID())) {
							std::vector<BetTrade>& Items = BetItems.find(IPlayer.GetPID() * ITarget.GetPID())->second;
							for (auto x = Items.begin(); x != Items.end(); x++) {
								BetTrade Item = *x;
								IItem IItem((void*)Item.Item);
								if (IItem.Exists()) {
									int PID = *(DWORD *)(Item.Item + 32) ? *(DWORD *)(Item.Item + 32) : Item.PID;
									int ItemPlayer = 0;
									if (PID == IPlayer.GetPID())
										ItemPlayer = Player;
									else if (PID == ITarget.GetPID())
										ItemPlayer = (int)ITarget.GetOffset();

									if (ItemPlayer) {
										int v18 = (*(int(__thiscall **)(int, int, signed int, int))(*(DWORD *)Item.Item + 132))(Item.Item, ItemPlayer, 10, !Item.Amount ? 1 : Item.Amount);
										if (v18 == Item.Item)
											CPlayer::_OutOfInven((void*)ItemPlayer, Item.Item);
										if (v18)
											x->Item = v18;
									}
								}
							}

							CPlayer::EndTrade(Player, 1);
							CPlayer::EndTrade((int)ITarget.GetOffset(), 1);
							IPlayer.CancelBuff(BuffNames::BetType);
							ITarget.CancelBuff(BuffNames::BetType);
							ITarget.Buff(3089, 10800, 0);
							IPlayer.Buff(3089, 10800, 0);
							IPlayer.CancelBuff(257);
							ITarget.CancelBuff(257);
							CPlayer::OnAskPvP(Player, 1, ITarget.GetID());
							std::string msg = "Duel bet has started : " + (std::string)IPlayer.GetName() + " Vs " + ITarget.GetName();

							CChar::WriteInSight(IPlayer.GetOffset(), 0xFF, "dsd", 248, msg.c_str(), TEXTCOLOR_YELLOW);
							return;
						}
					}
				}
			}

			if (packet == 81 && !IPlayer.IsBuff(3089)) {
				TargetFind myTarget(0, 0, IPlayer.GetBuffValue(BuffNames::BetOpponent));
				void *Target = myTarget.getTarget();
				IChar ITarget(Target);
				if (ITarget.IsValid() && ITarget.GetBuffValue(BuffNames::BetOpponent)) {
					char msg = 0;
					CPacket::Read((char*)pPacket, (char*)pPos, "b", &msg);
					if (msg) {
						if (CChar::GetRange((int)IPlayer.GetOffset() + 332, (int)ITarget.GetOffset() + 332) <= 64)
							CPlayer::OnAskTrade(Player, 1, ITarget.GetID());

						else {
							IPlayer.SystemMessage("Player too far.", TEXTCOLOR_RED);
							ITarget.UpdateBuff(BuffNames::BetOpponent, BuffNames::BuffTime, 0);
							IPlayer.UpdateBuff(BuffNames::BetOpponent, BuffNames::BuffTime, 0);
						}
					}
					else {
						ITarget.UpdateBuff(BuffNames::BetOpponent, BuffNames::BuffTime, 0);
						IPlayer.UpdateBuff(BuffNames::BetOpponent, BuffNames::BuffTime, 0);
						ITarget.SystemMessage((std::string)IPlayer.GetName() + " has refused the duel bet.", TEXTCOLOR_FAILED);
					}
				}
				else
					IPlayer.UpdateBuff(BuffNames::BetOpponent, BuffNames::BuffTime, 0);

				return;
			}
		}

		if ((packet == 34 || packet == 35 || packet == 63 || packet == 62 || packet == 36 || packet == 28) && IPlayer.IsBuff(3089)){
			return;
		}

		if ((packet == 19 || packet == 89) && IPlayer.IsBuff(3089)) {
			IPlayer.SystemMessage("You can not logout in the middle of a bet!", TEXTCOLOR_RED);
			return;
		}


		if (packet == 19)
		{
			if (IPlayer.IsBuff(3723) && !IPlayer.GetAdmin()) {
				IPlayer.SystemMessage("Please allow " + Int2String(IPlayer.GetBuffRemain(3723)) + " more seconds to log off.", TEXTCOLOR_YELLOW);
				return;
			}

			for (int i = BuffNames::Essence1; i <= BuffNames::MirrorBuff; i++) {
				int Value = IPlayer.GetBuffValue(i);
				if (Value) {
					int Item = IPlayer.ItemPointerLock(Value);
					if (Item)
					{
						IItem Mirror((void*)Item);
						*(DWORD*)((int)Mirror.GetOffset() + 48) = 0;
						CItem::SendItemInfo(Mirror.GetOffset(), (int)IPlayer.GetOffset(), 92);
						CPlayer::Write(IPlayer.GetOffset(), 6, "ddw", IPlayer.GetID(), Mirror.GetIID(), Mirror.CheckIndex());
					}
				}
			}
		}

		if ((packet == 94 || packet == C2S_MOVE) && !ScaniaLicense)
			return;

		if (IPlayer.GetMap() == BFMap && IPlayer.GetBuffValue(BuffNames::AFKTime) && packet == C2S_MOVE)
			IPlayer.CancelBuff(BuffNames::AFKTime);

		//if (packet == 94)
		//	IPlayer.SystemMessage("Open Box", TEXTCOLOR_GREEN);

		//if (packet == 89) {
		//	char Fflag = 0;
		//	CPacket::Read((char*)pPacket, (char*)pPos, "b", &Fflag);
		//	CConsole::Blue("Flag: %", Fflag);
		//}

		if (packet == 187)
		{
			char Type = 0, Jewel = 0, Amount = 0; int IID = 0, xIIDx = 0; unsigned short Class = 0;
			CPacket::Read((char*)pPacket, (char*)pPos, "bddbwb", &Type, &IID, &xIIDx, &Jewel, &Class, &Amount);

			if (IID == xIIDx) return;

			int Item = IPlayer.ItemPointerLock(IID);

			if (!Item)
				return;
			IItem MainItem((void*)Item);

			int ItemStatz = 0;
			itemStat.Enter();
			if (GetItemStat.count(IID))
				ItemStatz = GetItemStat.find(IID)->second;
			itemStat.Leave();

			if (Type == 2 && MainItem.CheckIndex() == 3381 && ItemStatz >= 2)
			{
				CPlayer::Write(IPlayer.GetOffset(), 192, "b", 8);
				return;
			}

			if (Type == 2 && MainItem.CheckIndex() == 3382 && ItemStatz >= 3)
			{
				CPlayer::Write(IPlayer.GetOffset(), 192, "b", 8);
				return;
			}

			if (Type == 2 && ItemStatz >= 4)
				return;

			if (Type == 0 && IID && xIIDx && Class == 102)
			{
				int Itemx = IPlayer.ItemPointerLock(xIIDx);

				if (!Itemx)
					return;

				IItem NextItem((void*)Itemx);

				if (NextItem.Exists() && MainItem.Exists()) {

					if (NextItem.CheckIndex() != MainItem.CheckIndex())
						return;

					int chance = CTools::Rate(1, 100);

					if ((Jewel == 1 && Amount == 1) || chance <= HaninChange)
					{
						int JewelAmount = 1;
						if (MainItem.CheckIndex() == 3385) JewelAmount = 10;
						if (MainItem.CheckIndex() == 3386) JewelAmount = 50;
						int JewelCheck = CPlayer::FindItem(IPlayer.GetOffset(), JewelIndex, JewelAmount);

						if ((Jewel == 1 && Amount == 1)) {
							if (JewelCheck) {
								if (!(*(int(__thiscall **)(DWORD, void *, signed int, signed int))(*(DWORD*)JewelCheck + 120))((int)JewelCheck, IPlayer.GetOffset(), 9, -JewelAmount))
									CPlayer::_OutOfInven((void*)Player, JewelCheck);
							}
							else {
								IPlayer.SystemMessage("Not enough Jewels.", TEXTCOLOR_RED);
								return;
							}
						}

						if (!CBase::IsDeleted((int)NextItem.GetOffset())) IPlayer.RemoveItem((int)NextItem.GetOffset());

						if (MainItem.CheckIndex() == 3384)
						{
							int Value = CTools::Rate(0, 12);
							int Add = HaninLow.count(Value) ? CTools::Rate(HaninLow.find(Value)->second.Min, HaninLow.find(Value)->second.Max) : 30;
							CPlayer::Write(IPlayer.GetOffset(), 194, "dd", MainItem.GetIID(), (ItemStatz % 100));
							CPlayer::Write(IPlayer.GetOffset(), 193, "ddd", MainItem.GetIID(), Value, Add);
							CPlayer::Write(IPlayer.GetOffset(), 192, "bddd", 3, MainItem.GetIID(), Value, Add);
							itemStat.Enter();
							GetItemStat[IID] = Value + (Add * 1000);
							itemStat.Leave();

							CDBSocket::Write(90, "dd", Value + (Add * 1000), IID);

						}

						if (MainItem.CheckIndex() == 3385)
						{
							int Value = CTools::Rate(0, 19);
							int Add = HaninMiddle.count(Value) ? CTools::Rate(HaninMiddle.find(Value)->second.Min, HaninMiddle.find(Value)->second.Max) : CTools::Rate(55, 65);
							CPlayer::Write(IPlayer.GetOffset(), 194, "dd", MainItem.GetIID(), (ItemStatz % 100));
							CPlayer::Write(IPlayer.GetOffset(), 193, "ddd", MainItem.GetIID(), Value, Add);
							CPlayer::Write(IPlayer.GetOffset(), 192, "bddd", 3, MainItem.GetIID(), Value, Add);
							itemStat.Enter();
							GetItemStat[IID] = Value + (Add * 1000);
							itemStat.Leave();
							CDBSocket::Write(90, "dd", Value + (Add * 1000), IID);

						}

						if (MainItem.CheckIndex() == 3386)
						{
							int Value = CTools::Rate(0, 21);
							int Add = HaninHigh.count(Value) ? CTools::Rate(HaninHigh.find(Value)->second.Min, HaninHigh.find(Value)->second.Max) : CTools::Rate(85, 95);
							CPlayer::Write(IPlayer.GetOffset(), 194, "dd", MainItem.GetIID(), (ItemStatz % 100));
							CPlayer::Write(IPlayer.GetOffset(), 193, "ddd", MainItem.GetIID(), Value, Add);
							CPlayer::Write(IPlayer.GetOffset(), 192, "bddd", 3, MainItem.GetIID(), Value, Add);
							itemStat.Enter();
							GetItemStat[IID] = Value + (Add * 1000);
							itemStat.Leave();
							CDBSocket::Write(90, "dd", Value + (Add * 1000), IID);

						}
					}
					else {
						if (!CBase::IsDeleted((int)NextItem.GetOffset())) IPlayer.RemoveItem((int)NextItem.GetOffset());
						int SuccessRate = CTools::Rate(1, 1000);

						if (MainItem.CheckIndex() == 3384)
						{
							if (SuccessRate >= 550)
							{
								int Value = CTools::Rate(0, 12);
								int Add = HaninLow.count(Value) ? CTools::Rate(HaninLow.find(Value)->second.Min, HaninLow.find(Value)->second.Max) : 30;
								CPlayer::Write(IPlayer.GetOffset(), 194, "dd", MainItem.GetIID(), (ItemStatz % 100));
								CPlayer::Write(IPlayer.GetOffset(), 193, "ddd", MainItem.GetIID(), Value, Add);
								CPlayer::Write(IPlayer.GetOffset(), 192, "bddd", 3, MainItem.GetIID(), Value, Add);
								itemStat.Enter();
								GetItemStat[IID] = Value + (Add * 1000);
								itemStat.Leave();
								CDBSocket::Write(90, "dd", Value + (Add * 1000), IID);
							}
							else {
								CPlayer::Write(IPlayer.GetOffset(), 192, "b", 4);
							}
						}

						if (MainItem.CheckIndex() == 3385)
						{
							if (SuccessRate >= 850)
							{
								int Value = CTools::Rate(0, 19);
								int Add = HaninMiddle.count(Value) ? CTools::Rate(HaninMiddle.find(Value)->second.Min, HaninMiddle.find(Value)->second.Max) : CTools::Rate(55, 65);
								CPlayer::Write(IPlayer.GetOffset(), 194, "dd", MainItem.GetIID(), (ItemStatz % 100));
								CPlayer::Write(IPlayer.GetOffset(), 193, "ddd", MainItem.GetIID(), Value, Add);
								CPlayer::Write(IPlayer.GetOffset(), 192, "bddd", 3, MainItem.GetIID(), Value, Add);
								itemStat.Enter();
								GetItemStat[IID] = Value + (Add * 1000);
								itemStat.Leave();
								CDBSocket::Write(90, "dd", Value + (Add * 1000), IID);
							}
							else {
								CPlayer::Write(IPlayer.GetOffset(), 192, "b", 4);
							}
						}

						if (MainItem.CheckIndex() == 3386)
						{
							if (SuccessRate >= 950)
							{
								int Value = CTools::Rate(0, 21);
								int Add = HaninHigh.count(Value) ? CTools::Rate(HaninHigh.find(Value)->second.Min, HaninHigh.find(Value)->second.Max) : CTools::Rate(85, 95);
								CPlayer::Write(IPlayer.GetOffset(), 194, "dd", MainItem.GetIID(), (ItemStatz % 100));
								CPlayer::Write(IPlayer.GetOffset(), 193, "ddd", MainItem.GetIID(), Value, Add);
								CPlayer::Write(IPlayer.GetOffset(), 192, "bddd", 3, MainItem.GetIID(), Value, Add);
								itemStat.Enter();
								GetItemStat[IID] = Value + (Add * 1000);
								itemStat.Leave();
								CDBSocket::Write(90, "dd", Value + (Add * 1000), IID);
							}
							else {
								CPlayer::Write(IPlayer.GetOffset(), 192, "b", 4);
							}
						}
					}
				}
			}

			if (Type == 1 && IID && xIIDx && Class == 103)
			{
				int Itemx = IPlayer.ItemPointerLock(IID);
				if (!Itemx)
					return;

				IItem NextItem((void*)Itemx);

				if (!NextItem.Exists())
					return;

				if (NextItem.CheckIndex() != MainItem.CheckIndex())
					return;

				if (MainItem.CheckIndex() == 3386)
					return;

				if (NextItem.CheckIndex() == 3386)
					return;

				int chance = CTools::Rate(1, 100);

				if ((Jewel == 1 && Amount == 1) || chance <= HaninChance)
				{
					int JewelAmount = 5; int Index = MainItem.CheckIndex();
					if (MainItem.CheckIndex() == 3385) JewelAmount = 10;
					int JewelCheck = CPlayer::_FindItem((int)IPlayer.GetOffset(), JewelIndex, JewelAmount);
					if (GetInventorySize((int)IPlayer.GetOffset(), 0) >= 60)
					{
						CPlayer::Write(IPlayer.GetOffset(), 67, "b", 40);
						return;
					}

					if ((Jewel == 1 && Amount == 1)) {
						if (JewelCheck) {
							if (!(*(int(__thiscall **)(DWORD, void *, signed int, signed int))(*(DWORD*)JewelCheck + 120))((int)JewelCheck, IPlayer.GetOffset(), 9, -JewelAmount))
								CPlayer::_OutOfInven((void*)Player, JewelCheck);
						}
						else {
							IPlayer.SystemMessage("Not enough Jewels.", TEXTCOLOR_RED);
							return;
						}
					}

					if (!CBase::IsDeleted((int)MainItem.GetOffset())) IPlayer.RemoveItem((int)MainItem.GetOffset());
					if (!CBase::IsDeleted((int)NextItem.GetOffset())) IPlayer.RemoveItem((int)NextItem.GetOffset());

					if (Index == 3384)
					{
						int xItem = CItem::CreateItem(3385, 0, 1, -1);

						if (xItem)
						{
							IItem IItem((void*)xItem);

							if (CPlayer::InsertItem(IPlayer.GetOffset(), 27, xItem) != 1) {
								CBase::Delete((void*)xItem);
								return;
							}
							int Value = CTools::Rate(0, 19);
							int Add = HaninMiddle.count(Value) ? CTools::Rate(HaninMiddle.find(Value)->second.Min, HaninMiddle.find(Value)->second.Max) : CTools::Rate(55, 65);
							CPlayer::Write(IPlayer.GetOffset(), 193, "ddd", IItem.GetIID(), Value, Add);
							CPlayer::Write(IPlayer.GetOffset(), 192, "bd", 5, IItem.GetIID());
							itemStat.Enter();
							GetItemStat[IItem.GetIID()] = Value + (Add * 1000);
							itemStat.Leave();
							CDBSocket::Write(90, "dd", Value + (Add * 1000), IItem.GetIID());

						}
					}

					if (Index == 3385)
					{
						int xItem = CItem::CreateItem(3386, 0, 1, -1);

						if (xItem)
						{
							IItem IItem((void*)xItem);

							if (CPlayer::InsertItem(IPlayer.GetOffset(), 27, xItem) != 1) {
								CBase::Delete((void*)xItem);
								return;
							}
							int Value = CTools::Rate(0, 21);
							int Add = HaninHigh.count(Value) ? CTools::Rate(HaninHigh.find(Value)->second.Min, HaninHigh.find(Value)->second.Max) : CTools::Rate(85, 95);
							CPlayer::Write(IPlayer.GetOffset(), 193, "ddd", IItem.GetIID(), Value, Add);
							CPlayer::Write(IPlayer.GetOffset(), 192, "bd", 5, IItem.GetIID());
							itemStat.Enter();
							GetItemStat[IItem.GetIID()] = Value + (Add * 1000);
							itemStat.Leave();
							CDBSocket::Write(90, "dd", Value + (Add * 1000), IItem.GetIID());

						}
					}
				}
				else {
					int Index = MainItem.CheckIndex();
					if (CPlayer::GetInvenSize((int)IPlayer.GetOffset()) >= IPlayer.MaxInventorySize())
					{
						IPlayer.SystemMessage("Inventory is full.", TEXTCOLOR_PINK);
						return;
					}
					if (!CBase::IsDeleted((int)MainItem.GetOffset())) IPlayer.RemoveItem((int)MainItem.GetOffset());
					if (!CBase::IsDeleted((int)NextItem.GetOffset())) IPlayer.RemoveItem((int)NextItem.GetOffset());
					int SuccessRate = CTools::Rate(1, 1000);

					if (Index == 3384)
					{
						if (SuccessRate >= 850)
						{
							int xItem = CItem::CreateItem(3385, 0, 1, -1);

							if (xItem)
							{
								IItem IItem((void*)xItem);

								if (CPlayer::InsertItem(IPlayer.GetOffset(), 27, xItem) != 1) {
									CBase::Delete((void*)xItem);
									return;
								}

								int Value = CTools::Rate(0, 19);
								int Add = HaninMiddle.count(Value) ? CTools::Rate(HaninMiddle.find(Value)->second.Min, HaninMiddle.find(Value)->second.Max) : CTools::Rate(55, 65);

								CPlayer::Write(IPlayer.GetOffset(), 193, "ddd", IItem.GetIID(), Value, Add);
								CPlayer::Write(IPlayer.GetOffset(), 192, "bd", 5, IItem.GetIID());
								itemStat.Enter();
								GetItemStat[IItem.GetIID()] = Value + (Add * 1000);
								itemStat.Leave();
								CDBSocket::Write(90, "dd", Value + (Add * 1000), IItem.GetIID());
							}
						}
						else {
							CPlayer::Write(IPlayer.GetOffset(), 192, "b", 6);
						}
					}

					if (Index == 3385)
					{
						if (SuccessRate >= 950)
						{
							int xItem = CItem::CreateItem(3386, 0, 1, -1);

							if (xItem)
							{
								IItem IItem((void*)xItem);

								if (CPlayer::InsertItem(IPlayer.GetOffset(), 27, xItem) != 1) {
									CBase::Delete((void*)xItem);
									return;
								}

								int Value = CTools::Rate(0, 21);
								int Add = HaninHigh.count(Value) ? CTools::Rate(HaninHigh.find(Value)->second.Min, HaninHigh.find(Value)->second.Max) : CTools::Rate(85, 95);
								CPlayer::Write(IPlayer.GetOffset(), 193, "ddd", IItem.GetIID(), Value, Add);
								CPlayer::Write(IPlayer.GetOffset(), 192, "bd", 5, IItem.GetIID());
								itemStat.Enter();
								GetItemStat[IItem.GetIID()] = Value + (Add * 1000);
								itemStat.Leave();
								CDBSocket::Write(90, "dd", Value + (Add * 1000), IItem.GetIID());
							}
						}
						else {
							CPlayer::Write(IPlayer.GetOffset(), 192, "b", 6);
						}
					}
				}
			}

			if (Type == 2 && IID && MainItem.CheckIndex() == 3383) {
				itemStat.Enter();
				if (GetItemStat.find(IID)->second == 0)
					GetItemStat[IID] = 1;
				itemStat.Leave();
			}

			if (Type == 2 && IID)
			{
				itemStat.Enter();
				int Staz = GetItemStat.count(IID) ? GetItemStat.find(IID)->second : 0;
				itemStat.Leave();
				if (Staz >= 1) {
					int JewelCheck = CPlayer::FindItem(IPlayer.GetOffset(), JewelIndex, Staz * 60);

					if (JewelCheck)
					{
						if (!(*(int(__thiscall **)(DWORD, void *, signed int, signed int))(*(DWORD*)JewelCheck + 120))((int)JewelCheck, IPlayer.GetOffset(), 9, -(Staz * 60)))
							CPlayer::_OutOfInven((void*)Player, JewelCheck);

						int newValue = Staz + 1;
						itemStat.Enter();
						GetItemStat[IID] = newValue;
						itemStat.Leave();
						CPlayer::Write(IPlayer.GetOffset(), 194, "dd", IID, 100);
						CPlayer::Write(IPlayer.GetOffset(), 193, "ddd", IID, 100, newValue + 1);
						CDBSocket::Write(90, "dd", newValue, IID);
						CPlayer::Write(IPlayer.GetOffset(), 192, "b", 7);
					}
					else {
						IPlayer.BoxMsg("You do not have enough gems.");
					}
				}
			}

			if (Type == 2 && IID)
			{
				itemStat.Enter();
				int Staz = GetItemStat.count(IID) ? GetItemStat.find(IID)->second : -1;
				itemStat.Leave();
				if (Staz == 0) {
					if (IPlayer.RemoveItem(31, 1000000))
					{
						itemStat.Enter();
						GetItemStat[IID] = Staz + 1;
						itemStat.Leave();
						CPlayer::Write(IPlayer.GetOffset(), 194, "dd", IID, 100);
						CPlayer::Write(IPlayer.GetOffset(), 193, "ddd", IID, 100, Staz + 2);
						CDBSocket::Write(90, "dd", Staz + 1, IID);
						CPlayer::Write(IPlayer.GetOffset(), 192, "b", 7);
					}
					else {
						IPlayer.BoxMsg("You do not have enough zamogeon.");
					}
				}
			}

			return;
		}

		if (packet == 183)
		{
			char Type = 0, Value = 0; int BillCode = 0; unsigned short Amount = 0; const char *GiftName = "none";
			CPacket::Read((char*)pPacket, (char*)pPos, "bbdws", &Type, &Value, &BillCode, &Amount, &GiftName, 21);

			if (Type == 1 && Value == 0)
				CPlayer::Write(IPlayer.GetOffset(), 186, "bbwwm", 3, 1, 1, ItemShopCheck.size(), ItemShopPacket, ItemShopCheck.size() * 12);

			if (QuestRentItem.count(BillCode))
			{
				for (int i = 0; i < QuestRentItem[BillCode].size(); i++) {
					CQuest::Start(QuestRentItem[BillCode][i] << 16 | 1, (int)IPlayer.GetOffset());
				}
				return;
			}
			if (Type == 1 && Value == 1)
			{
				int Jewel = 0, GoldKC = 0, SilverKC = 0, JewelAmount = 0, GoldKCAmount = 0, SilverKCAmount = 0;
				Jewel = CPlayer::FindItem(IPlayer.GetOffset(), ShopJewelIndex, 1);
				GoldKC = CPlayer::FindItem(IPlayer.GetOffset(), ShopGoldIndex, 1);
				SilverKC = CPlayer::FindItem(IPlayer.GetOffset(), ShopSilverIndex, 1);
				if (Jewel)
				{
					IItem xJewel((void*)Jewel);
					JewelAmount = xJewel.GetAmount();
				}
				if (GoldKC)
				{
					IItem xGold((void*)GoldKC);
					GoldKCAmount = xGold.GetAmount();
				}
				if (SilverKC)
				{
					IItem xSilver((void*)SilverKC);
					SilverKCAmount = xSilver.GetAmount();
				}
				CPlayer::Write(IPlayer.GetOffset(), 186, "b", 0);
				CPlayer::Write(IPlayer.GetOffset(), 186, "bdddd", 4, GoldKCAmount, SilverKCAmount, IPlayer.GetProperty(PlayerProperty::RPx), JewelAmount);
			}

			if ((Type == 2 || Type == 4) && ItemShopCheck.count(BillCode) && ItemShopCheck.find(BillCode)->second.Priority == 4)
			{
				CPlayer::Write(IPlayer.GetOffset(), 186, "b", 11);
				return;
			}

			if (Type == 2)
			{
				if (ItemShopCheck.count(BillCode))
				{
					const char *PlayerName = GiftName;

					TargetFind myTarget(PlayerName);
					int player3 = (int)myTarget.getTarget();

					IChar Target((void*)player3);

					if (!Target.IsOnline())
					{
						CPlayer::Write(IPlayer.GetOffset(), 186, "b", 18);
						return;
					}
					if (Amount <= 0)
					{
						CPlayer::Write(IPlayer.GetOffset(), 186, "b", 17);
						return;
					}
					int Price = 0; Price = ItemShopCheck.find(BillCode)->second.Price * Amount;
					if (Price <= 0)
					{
						CPlayer::Write(IPlayer.GetOffset(), 186, "b", 17);
						return;
					}
					int Check = 2147483647 / Price;
					if (Amount >= Check)
					{
						CPlayer::Write(IPlayer.GetOffset(), 186, "b", 17);
						return;
					}
					if (ItemShopCheck.find(BillCode)->second.Discount) Price -= ((Price * ItemShopCheck.find(BillCode)->second.Discount) / 100);
					int Jewel = 0, GoldKC = 0, SilverKC = 0, JewelAmount = 0, GoldKCAmount = 0, SilverKCAmount = 0;
					Jewel = CPlayer::FindItem(IPlayer.GetOffset(), ShopJewelIndex, 1);
					GoldKC = CPlayer::FindItem(IPlayer.GetOffset(), ShopGoldIndex, 1);
					SilverKC = CPlayer::FindItem(IPlayer.GetOffset(), ShopSilverIndex, 1);
					IItem xJewel((void*)Jewel);
					IItem xGold((void*)GoldKC);
					IItem xSilver((void*)SilverKC);
					if (Jewel) JewelAmount = xJewel.GetAmount();
					if (GoldKC) GoldKCAmount = xGold.GetAmount();
					if (SilverKC) SilverKCAmount = xSilver.GetAmount();
					if (ItemShopCheck.find(BillCode)->second.Type == 1)
					{
						if (GoldKC && GoldKCAmount >= Price && Target.IsOnline() && IPlayer.IsOnline())
						{
							CPlayer::Write(IPlayer.GetOffset(), 186, "bdddd", 4, GoldKCAmount - Price, SilverKCAmount, IPlayer.GetProperty(PlayerProperty::RPx), JewelAmount);
							if (!(*(int(__thiscall **)(DWORD, void *, signed int, signed int))(*(DWORD*)(int)xGold.GetOffset() + 120))((int)xGold.GetOffset(), IPlayer.GetOffset(), 9, -Price))
								CPlayer::_OutOfInven((void*)Player, (int)xGold.GetOffset());

							std::string name = IPlayer.GetName();
							std::string msg = "KalOnline Item Shop Gift From Player " + name;
							Target.GiveReward(ItemShopCheck.find(BillCode)->second.ItemIndex, 0, ItemShopCheck.find(BillCode)->second.Amount * Amount, 0, 0, 0, 0, 0, 0, 0, 0, msg.c_str());
							CPlayer::Write(IPlayer.GetOffset(), 186, "b", 16);
						}
						else {
							CPlayer::Write(IPlayer.GetOffset(), 186, "b", 17);
						}
					}
					if (ItemShopCheck.find(BillCode)->second.Type == 4)
					{
						if (Jewel && JewelAmount >= Price)
						{
							CPlayer::Write(IPlayer.GetOffset(), 186, "bdddd", 4, GoldKCAmount, SilverKCAmount, IPlayer.GetProperty(PlayerProperty::RPx), JewelAmount - Price);
							if (!(*(int(__thiscall **)(DWORD, void *, signed int, signed int))(*(DWORD*)(int)xJewel.GetOffset() + 120))((int)xJewel.GetOffset(), IPlayer.GetOffset(), 9, -Price))
								CPlayer::_OutOfInven((void*)Player, (int)xJewel.GetOffset());

							std::string name = IPlayer.GetName();
							std::string msg = "KalOnline Item Shop Gift From Player " + name;
							Target.GiveReward(ItemShopCheck.find(BillCode)->second.ItemIndex, 0, ItemShopCheck.find(BillCode)->second.Amount * Amount, 0, 0, 0, 0, 0, 0, 0, 0, msg.c_str());
							CPlayer::Write(IPlayer.GetOffset(), 186, "b", 16);
							CPlayer::Write(IPlayer.GetOffset(), 186, "b", 16);
						}
						else {
							CPlayer::Write(IPlayer.GetOffset(), 186, "b", 17);
						}
					}
				}
			}

			if (Type == 4)
			{
				if (ItemShopCheck.count(BillCode))
				{
					if (Amount <= 0)
					{
						CPlayer::Write(IPlayer.GetOffset(), 186, "bb", 6, 5);
						return;
					}
					int Price = 0; Price = ItemShopCheck.find(BillCode)->second.Price * Amount;
					if (Price <= 0)
					{
						CPlayer::Write(IPlayer.GetOffset(), 186, "bb", 6, 5);
						return;
					}
					int Check = 2147483647 / Price;
					if (Amount >= Check)
					{
						CPlayer::Write(IPlayer.GetOffset(), 186, "bb", 6, 5);
						return;
					}
					if (ItemShopCheck.find(BillCode)->second.Discount) Price -= ((Price * ItemShopCheck.find(BillCode)->second.Discount) / 100);
					int Jewel = 0, GoldKC = 0, SilverKC = 0, JewelAmount = 0, GoldKCAmount = 0, SilverKCAmount = 0;
					Jewel = CPlayer::FindItem(IPlayer.GetOffset(), ShopJewelIndex, 1);
					GoldKC = CPlayer::FindItem(IPlayer.GetOffset(), ShopGoldIndex, 1);
					SilverKC = CPlayer::FindItem(IPlayer.GetOffset(), ShopSilverIndex, 1);
					IItem xJewel((void*)Jewel);
					IItem xGold((void*)GoldKC);
					IItem xSilver((void*)SilverKC);
					if (Jewel) JewelAmount = xJewel.GetAmount();
					if (GoldKC) GoldKCAmount = xGold.GetAmount();
					if (SilverKC) SilverKCAmount = xSilver.GetAmount();
					if (ItemShopCheck.find(BillCode)->second.Type == 1)
					{
						if (GoldKC && GoldKCAmount >= Price)
						{
							CPlayer::Write(IPlayer.GetOffset(), 186, "bdddd", 4, GoldKCAmount - Price, SilverKCAmount, IPlayer.GetProperty(PlayerProperty::RPx), JewelAmount);
							if (!(*(int(__thiscall **)(DWORD, void *, signed int, signed int))(*(DWORD*)(int)xGold.GetOffset() + 120))((int)xGold.GetOffset(), IPlayer.GetOffset(), 9, -Price))
								CPlayer::_OutOfInven((void*)Player, (int)xGold.GetOffset());

							CItem::InsertItem((int)IPlayer.GetOffset(), 27, ItemShopCheck.find(BillCode)->second.ItemIndex, 0, ItemShopCheck.find(BillCode)->second.Amount * Amount, -1);
							CPlayer::Write(IPlayer.GetOffset(), 186, "bb", 5, 5);
						}
						else {
							CPlayer::Write(IPlayer.GetOffset(), 186, "bb", 6, 5);
						}
					}
					if (ItemShopCheck.find(BillCode)->second.Type == 2)
					{
						if (SilverKC && SilverKCAmount >= Price)
						{
							CPlayer::Write(IPlayer.GetOffset(), 186, "bdddd", 4, GoldKCAmount, SilverKCAmount - Price, IPlayer.GetProperty(PlayerProperty::RPx), JewelAmount);
							if (!(*(int(__thiscall **)(DWORD, void *, signed int, signed int))(*(DWORD*)(int)xSilver.GetOffset() + 120))((int)xSilver.GetOffset(), IPlayer.GetOffset(), 9, -Price))
								CPlayer::_OutOfInven((void*)Player, (int)xSilver.GetOffset());

							CItem::InsertItem((int)IPlayer.GetOffset(), 27, ItemShopCheck.find(BillCode)->second.ItemIndex, 0, ItemShopCheck.find(BillCode)->second.Amount * Amount, -1);
							CPlayer::Write(IPlayer.GetOffset(), 186, "bb", 5, 5);
						}
						else {
							CPlayer::Write(IPlayer.GetOffset(), 186, "bb", 6, 5);
						}
					}
					if (ItemShopCheck.find(BillCode)->second.Type == 3)
					{
						if (IPlayer.GetProperty(PlayerProperty::RPx) >= Price)
						{
							IPlayer.SetHonor(0, -Price, 0, 0, 0, 0, 0, 0, 0, 0);
							CPlayer::Write(IPlayer.GetOffset(), 186, "bdddd", 4, GoldKCAmount, SilverKCAmount, IPlayer.GetProperty(PlayerProperty::RPx), JewelAmount);
							CItem::InsertItem((int)IPlayer.GetOffset(), 27, ItemShopCheck.find(BillCode)->second.ItemIndex, 0, ItemShopCheck.find(BillCode)->second.Amount * Amount, -1);
							CPlayer::Write(IPlayer.GetOffset(), 186, "bb", 5, 5);
						}
						else {
							CPlayer::Write(IPlayer.GetOffset(), 186, "bb", 6, 5);
						}
					}
					if (ItemShopCheck.find(BillCode)->second.Type == 4)
					{
						if (Jewel && JewelAmount >= Price)
						{
							CPlayer::Write(IPlayer.GetOffset(), 186, "bdddd", 4, GoldKCAmount, SilverKCAmount, IPlayer.GetProperty(PlayerProperty::RPx), JewelAmount - Price);
							if (!(*(int(__thiscall **)(DWORD, void *, signed int, signed int))(*(DWORD*)(int)xJewel.GetOffset() + 120))((int)xJewel.GetOffset(), IPlayer.GetOffset(), 9, -Price))
								CPlayer::_OutOfInven((void*)Player, (int)xJewel.GetOffset());

							CItem::InsertItem((int)IPlayer.GetOffset(), 27, ItemShopCheck.find(BillCode)->second.ItemIndex, 0, ItemShopCheck.find(BillCode)->second.Amount * Amount, -1);
							CPlayer::Write(IPlayer.GetOffset(), 186, "bb", 5, 4);
						}
						else {
							CPlayer::Write(IPlayer.GetOffset(), 186, "bb", 6, 4);
						}
					}
				}
			}

			return;
		}


		if (packet == 101)
		{
			if (IPlayer.IsBuff(BuffNames::QuestDBCheck)) {
				IPlayer.SystemMessage("Canceling the quest failed, please try again.", TEXTCOLOR_RED);
				return;
			}


			IPlayer.Buff(BuffNames::QuestDBCheck, 2, 0);
			int QuestID = 0, Repeat = 0;
			CPacket::Read((char*)pPacket, (char*)pPos, "w", &QuestID);

			//if (DutyQuest.count(QuestID)){
			//	IPlayer.SystemMessage("You can not abandon Daily Duty quest.", TEXTCOLOR_RED);
			//	return;
			//}

			if (DutyQuest.count(QuestID))
			{
				IPlayer.CancelBuff(BuffNames::NormalDuty);
				IPlayer.CancelBuff(BuffNames::InstanceDuty);
				IPlayer.CancelBuff(BuffNames::MiniBoss);
				IPlayer.CancelBuff(BuffNames::DailyDuty + QuestID);
				CDBSocket::Write(125, "ddd", 5, IPlayer.GetPID(), QuestID);
			}

			if (MAbandonCheck.count(QuestID)){
				IPlayer.SystemMessage("You can not abandon Auto Missions quest.", TEXTCOLOR_RED);
				return;
			}

			if (MissionQuestsItem.count(QuestID)){
				IPlayer.SystemMessage("You can not abandon Auto Missions quest.", TEXTCOLOR_RED);
				return;
			}

			int Daily = 0;
			if (DailyQuest.count(QuestID)) {
				Daily = 1;
				int diff = BuffNames::MonsterQuestEnd - BuffNames::MonsterQuestBegin;
				ConfigDailyQuest dQuest = DailyQuest.find(QuestID)->second;

				std::vector<std::string> Monsters_ = dQuest.Monsters;
				Repeat = IPlayer.GetBuffValue((BuffNames::DailyRepeatBegin + QuestID) % BuffNames::DailyRepeatEnd);

				IPlayer.UpdateBuff((BuffNames::DailyCountBegin + QuestID) % BuffNames::DailyCountEnd, BuffNames::BuffTime, 0);
				for (int i = 0; i < Monsters_.size(); i++) {
					int Index = String2Int(Monsters_[i]);
					if (dQuest.Type == 1) {
						std::vector<std::string> MonstersPerGroup_ = explode("-", dQuest.Monsters[i]);
						Index = String2Int(MonstersPerGroup_[0]);
					}

					if (Index) {
						IPlayer.CancelBuff(BuffNames::MonsterQuestBegin + ((Index + (QuestID * 100)) % diff));
						CPlayer::Write(IPlayer.GetOffset(), 184, "ddd", QuestID << 16, Index, 0);
					}
				}
			}
			CDBSocket::Write(101, "ddd", IPlayer.GetPID(), QuestID, Daily);

			IPlayer.QuitQuest(QuestID, 0, Repeat, Daily);

			return;
		}

		if (packet == 67 && ShopLimit.count(sha256(IPlayer.GetIP())) && ShopLimit.find(sha256(IPlayer.GetIP()))->second && !IPlayer.IsBuff(297))
		{
			IPlayer.SystemMessage("Exceeded the maximum shop limit.", TEXTCOLOR_RED);
			return;
		}

		if (packet == C2S_SendMail)
		{
			char Type = 0; int Amount = 0;
			int LeftData = CPacket::Read((char*)pPacket, (char*)pPos, "bd", &Type, &Amount);

			if (Type == 12 && Amount > 0)
			{
				if (Amount > 50)
				{
					IPlayer.SystemMessage("You can delete maximum 50 mails in a row.", TEXTCOLOR_RED);
					return;
				}

				for (int i = 0; i < Amount; i++)
				{
					int MAILID = 0;
					LeftData = CPacket::Read((char*)LeftData, (char*)pPos, "d", &MAILID);

					if (MAILID > 0 && IPlayer.IsOnline())
						CPlayer::Write(IPlayer.GetOffset(), 255, "dd", 223, MAILID);
				}

				return;
			}
		}

		if (packet == 54)
		{
			char Type = 0; int Key = 0, Rate = CTools::Rate(1, 1000);
			CPacket::Read((char*)pPacket, (char*)pPos, "bd", &Type, &Key);

			if (Type == 1 && Key)
			{
				if (CPlayer::GetInvenSize(Player) >= IPlayer.MaxInventorySize())
				{
					IPlayer.BoxMsg("Your inventory is full.");
					return;
				}

				if (MakeItem.count(Key)) {
					Interface<ITools> Tools;
					std::vector<std::string> requireIndex = Tools->Explode(MakeItem[Key].requireIndexs, ",");
					std::vector<std::string> requireAmounts = Tools->Explode(MakeItem[Key].requireAmounts, ",");
					if (requireIndex.size() > 0 && requireIndex.size() == requireAmounts.size()) {
						int FoundItems = 0;
						for (int i = 0; i < requireIndex.size(); i++) {
							if (CPlayer::RemoveItem(IPlayer.GetOffset(), 9, atoi(requireIndex[i].c_str()), atoi(requireAmounts[i].c_str())))
								FoundItems++;
						}
						if (requireIndex.size() == FoundItems)
							CItem::InsertItem((int)IPlayer.GetOffset(), 27, MakeItem[Key].item, 0, 1, -1);
					}
					return;
				}

				if (MakeMinerals.count(Key)) {
					SwapMineral mix = MakeMinerals.find(Key)->second;
					Interface<ITools> Tools;
					std::vector<std::string> requireIndex = Tools->Explode(mix.requires, ",");
					std::vector<std::string> requireAmounts = Tools->Explode(mix.requireAmounts, ",");
					std::vector<std::string> chances = Tools->Explode(mix.chances, ",");
					std::vector<std::string> items = Tools->Explode(mix.itemRewards, ",");
					std::vector<std::string> itemAmounts = Tools->Explode(mix.itemAmounts, ",");

					if (requireIndex.size() == requireAmounts.size() && items.size() == itemAmounts.size() && items.size() == chances.size()) {
						for (int i = 0; i < requireIndex.size(); i++) {
							int Index = String2Int(requireIndex[i]);
							int Amount = String2Int(requireAmounts[i]);

							if (Index && Amount && !CPlayer::FindItem((void*)Player, Index, Amount)) {
								IPlayer.SystemMessage("You do not have all the items.", TEXTCOLOR_RED);
								return;
							}
						}

						for (int i = 0; i < requireIndex.size(); i++) {
							int Index = String2Int(requireIndex[i]);
							int Amount = String2Int(requireAmounts[i]);
							if (Index && Amount)
								CPlayer::RemoveItem((void*)Player, 9, Index, Amount);
						}

						for (int i = 0; i < items.size(); i++) {
							int Index = String2Int(items[i]);
							int Amount = String2Int(itemAmounts[i]);
							int Chance = String2Int(chances[i]);

							if (Index && Amount && Chance && Chance >= Rate) {
								CItem::InsertItem((int)IPlayer.GetOffset(), 27, Index, 0, Amount, -1);
								return;
							}
						}
					}
					return;
				}

				if (Key == 1205 && CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 31, 11000000) && CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 2655, 400)
					&& CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 2663, 150) && CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 2668, 80)
					&& CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 2666, 15) && CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 2672, 10)
					&& CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 2675, 6))
				{
					CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2705, 0, 1, -1);
					return;
				}

				if (Key == 1204 && CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 31, 11000000) && CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 2671, 300)
					&& CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 2663, 130) && CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 2668, 85)
					&& CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 2665, 25) && CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 2669, 25)
					&& CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 2675, 6))
				{
					CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2704, 0, 1, -1);
					return;
				}

				if (Key == 1203 && CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 31, 11000000) && CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 2656, 350)
					&& CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 2664, 60) && CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 2667, 150)
					&& CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 2666, 12) && CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 2669, 30)
					&& CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 2675, 6))
				{
					CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2703, 0, 1, -1);
					return;
				}

				if (Key == 1202 && CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 31, 11000000) && CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 2655, 400)
					&& CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 2658, 30) && CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 2661, 100)
					&& CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 2666, 15) && CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 2672, 12)
					&& CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 2675, 6))
				{
					CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2702, 0, 1, -1);
					return;
				}

				if (Key == 1201 && CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 31, 11000000) && CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 2659, 400)
					&& CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 2657, 120) && CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 2662, 38)
					&& CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 2666, 12) && CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 2669, 12)
					&& CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 2675, 6))
				{
					CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2701, 0, 1, -1);
					return;
				}

				if (Key == 1200 && CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 31, 11000000) && CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 2660, 350)
					&& CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 2658, 35) && CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 2667, 150)
					&& CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 2665, 28) && CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 2672, 15)
					&& CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 2675, 6))
				{
					CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2700, 0, 1, -1);
					return;
				}

				if (Key == 1105 && CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 31, 4400000) && CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 2671, 240)
					&& CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 2657, 100) && CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 2664, 50)
					&& CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 2665, 20) && CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 2674, 4))
				{
					CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2693, 0, 1, -1);
					return;
				}

				if (Key == 1104 && CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 31, 4400000) && CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 2655, 300)
					&& CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 2663, 120) && CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 2667, 120)
					&& CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 2669, 20) && CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 2674, 4))
				{
					CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2692, 0, 1, -1);
					return;
				}

				if (Key == 1103 && CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 31, 4400000) && CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 2671, 240)
					&& CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 2664, 50) && CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 2667, 120)
					&& CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 2672, 15) && CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 2674, 4))
				{
					CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2691, 0, 1, -1);
					return;
				}

				if (Key == 1102 && CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 31, 4400000) && CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 2659, 300)
					&& CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 2658, 25) && CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 2668, 40)
					&& CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 2666, 10) && CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 2674, 4))
				{
					CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2690, 0, 1, -1);
					return;
				}

				if (Key == 1101 && CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 31, 4400000) && CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 2656, 200)
					&& CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 2664, 50) && CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 2661, 70)
					&& CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 2666, 10) && CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 2674, 4))
				{
					CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2689, 0, 1, -1);
					return;
				}

				if (Key == 1100 && CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 31, 4400000) && CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 2656, 200)
					&& CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 2663, 120) && CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 2661, 70)
					&& CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 2672, 15) && CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 2674, 4))
				{
					CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2688, 0, 1, -1);
					return;
				}

				if (Key == 1006 && CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 31, 880000) && CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 2655, 120)
					&& CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 2660, 150) && CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 2657, 50)
					&& CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 2669, 10) && CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 2673, 2))
				{
					CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2682, 0, 1, -1);
					return;
				}

				if (Key == 1005 && CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 31, 880000) && CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 2655, 150)
					&& CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 2659, 150) && CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 2658, 12)
					&& CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 2664, 30) && CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 2673, 2))
				{
					CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2681, 0, 1, -1);
					return;
				}

				if (Key == 1004 && CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 31, 880000) && CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 2659, 150)
					&& CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 2671, 80) && CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 2667, 60)
					&& CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 2665, 10) && CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 2673, 2))
				{
					CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2680, 0, 1, -1);
					return;
				}

				if (Key == 1003 && CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 31, 880000) && CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 2656, 100)
					&& CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 2671, 80) && CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 2668, 30)
					&& CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 2665, 10) && CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 2673, 2))
				{
					CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2679, 0, 1, -1);
					return;
				}

				if (Key == 1002 && CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 31, 880000) && CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 2656, 100)
					&& CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 2660, 150) && CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 2663, 60)
					&& CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 2668, 30) && CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 2673, 2))
				{
					CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2678, 0, 1, -1);
					return;
				}

				if (Key == 1001 && CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 31, 880000) && CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 2656, 100)
					&& CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 2659, 150) && CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 2664, 30)
					&& CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 2662, 12) && CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 2673, 2))
				{
					CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2677, 0, 1, -1);
					return;
				}

				if (Key == 1000 && CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 31, 880000) && CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 2655, 150)
					&& CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 2671, 80) && CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 2664, 30)
					&& CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 2661, 30) && CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 2673, 2))
				{
					CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2676, 0, 1, -1);
					return;
				}

				if (Key == 702 && CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 2539, 400) && CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 2654, 1))
				{
					CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2538, 0, 1, -1);
					return;
				}

				if (Key == 701 && CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 2539, 400))
				{
					if (Rate >= 550)
					{
						CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2538, 0, 1, -1);
					}
					else {
						CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2537, 0, 1, -1);
					}

					return;
				}

				if (Key == 602 && CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 2536, 400) && CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 2654, 1))
				{
					CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2675, 0, 1, -1);
					return;
				}

				if (Key == 601 && CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 2536, 400))
				{
					if (Rate >= 550)
					{
						CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2675, 0, 1, -1);
					}
					else {
						CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2537, 0, 1, -1);
					}

					return;
				}

				if (Key == 502 && CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 2535, 350) && CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 2654, 1))
				{
					CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2674, 0, 1, -1);
					return;
				}

				if (Key == 501 && CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 2535, 350))
				{
					if (Rate >= 550)
					{
						CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2674, 0, 1, -1);
					}
					else {
						CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2537, 0, 1, -1);
					}

					return;
				}

				if (Key == 405 && CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 2534, 300))
				{
					if (Rate >= 450)
					{
						if (Rate >= 650)
						{
							CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2671, 0, 1, -1);
						}
						else {
							CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2672, 0, 1, -1);
						}
					}
					else {
						CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2673, 0, 1, -1);
					}

					return;
				}

				if (Key == 404 && CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 2534, 225) && CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 2654, 1))
				{
					if (Rate >= 450)
					{
						if (Rate >= 650)
						{
							CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2671, 0, 1, -1);
						}
						else {
							CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2672, 0, 1, -1);
						}
					}
					else {
						CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2673, 0, 1, -1);
					}

					return;
				}

				if (Key == 403 && CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 2534, 225))
				{
					if (Rate >= 450)
					{
						if (Rate >= 650)
						{
							if (Rate >= 850)
							{
								CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2671, 0, 1, -1);
							}
							else {
								CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2672, 0, 1, -1);
							}
						}
						else {
							CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2673, 0, 1, -1);
						}
					}
					else {
						CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2537, 0, 1, -1);
					}

					return;
				}

				if (Key == 402 && CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 2534, 100) && CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 2654, 1))
				{
					if (Rate >= 550)
					{
						CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2671, 0, 1, -1);
					}
					else {
						CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2672, 0, 1, -1);
					}

					return;
				}

				if (Key == 401 && CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 2534, 100))
				{
					if (Rate >= 450)
					{
						if (Rate >= 750)
						{
							CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2671, 0, 1, -1);
						}
						else {
							CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2672, 0, 1, -1);
						}
					}
					else {
						CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2537, 0, 1, -1);
					}

					return;
				}

				if (Key == 307 && CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 2533, 300))
				{
					if (Rate >= 350)
					{
						if (Rate >= 550)
						{
							if (Rate >= 750)
							{
								CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2667, 0, 1, -1);
							}
							else {
								CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2668, 0, 1, -1);
							}
						}
						else {
							CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2669, 0, 1, -1);
						}
					}
					else {
						CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2670, 0, 1, -1);
					}

					return;
				}

				if (Key == 306 && CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 2533, 225) && CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 2654, 1))
				{
					if (Rate >= 400)
					{
						if (Rate >= 600)
						{
							if (Rate >= 800)
							{
								CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2667, 0, 1, -1);
							}
							else {
								CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2668, 0, 1, -1);
							}
						}
						else {
							CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2669, 0, 1, -1);
						}
					}
					else {
						CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2670, 0, 1, -1);
					}

					return;
				}

				if (Key == 305 && CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 2533, 225))
				{
					if (Rate >= 400)
					{
						if (Rate >= 600)
						{
							if (Rate >= 800)
							{
								if (Rate >= 900)
								{
									CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2667, 0, 1, -1);
								}
								else {
									CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2668, 0, 1, -1);
								}
							}
							else {
								CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2669, 0, 1, -1);
							}
						}
						else {
							CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2670, 0, 1, -1);
						}
					}
					else {
						CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2537, 0, 1, -1);
					}

					return;
				}

				if (Key == 304 && CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 2533, 150) && CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 2654, 1))
				{
					if (Rate >= 400)
					{
						if (Rate >= 600)
						{
							CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2667, 0, 1, -1);
						}
						else {
							CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2668, 0, 1, -1);
						}
					}
					else {
						CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2669, 0, 1, -1);
					}

					return;
				}

				if (Key == 303 && CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 2533, 150))
				{
					if (Rate >= 450)
					{
						if (Rate >= 650)
						{
							if (Rate >= 850)
							{
								CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2667, 0, 1, -1);
							}
							else {
								CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2668, 0, 1, -1);
							}
						}
						else {
							CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2669, 0, 1, -1);
						}
					}
					else {
						CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2537, 0, 1, -1);
					}

					return;
				}

				if (Key == 302 && CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 2533, 75) && CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 2654, 1))
				{
					if (Rate >= 550)
					{
						CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2667, 0, 1, -1);
					}
					else {
						CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2668, 0, 1, -1);
					}

					return;
				}

				if (Key == 301 && CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 2533, 75))
				{
					if (Rate >= 450)
					{
						if (Rate >= 750)
						{
							CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2667, 0, 1, -1);
						}
						else {
							CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2668, 0, 1, -1);
						}
					}
					else {
						CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2537, 0, 1, -1);
					}

					return;
				}

				if (Key == 207 && CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 2532, 300))
				{
					if (Rate >= 350)
					{
						if (Rate >= 550)
						{
							if (Rate >= 750)
							{
								CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2663, 0, 1, -1);
							}
							else {
								CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2664, 0, 1, -1);
							}
						}
						else {
							CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2665, 0, 1, -1);
						}
					}
					else {
						CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2666, 0, 1, -1);
					}

					return;
				}

				if (Key == 206 && CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 2532, 225) && CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 2654, 1))
				{
					if (Rate >= 400)
					{
						if (Rate >= 600)
						{
							if (Rate >= 800)
							{
								CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2663, 0, 1, -1);
							}
							else {
								CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2664, 0, 1, -1);
							}
						}
						else {
							CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2665, 0, 1, -1);
						}
					}
					else {
						CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2666, 0, 1, -1);
					}

					return;
				}

				if (Key == 205 && CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 2532, 225))
				{
					if (Rate >= 400)
					{
						if (Rate >= 600)
						{
							if (Rate >= 800)
							{
								if (Rate >= 900)
								{
									CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2663, 0, 1, -1);
								}
								else {
									CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2664, 0, 1, -1);
								}
							}
							else {
								CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2665, 0, 1, -1);
							}
						}
						else {
							CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2666, 0, 1, -1);
						}
					}
					else {
						CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2537, 0, 1, -1);
					}

					return;
				}

				if (Key == 204 && CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 2532, 150) && CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 2654, 1))
				{
					if (Rate >= 400)
					{
						if (Rate >= 600)
						{
							CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2663, 0, 1, -1);
						}
						else {
							CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2664, 0, 1, -1);
						}
					}
					else {
						CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2665, 0, 1, -1);
					}

					return;
				}

				if (Key == 203 && CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 2532, 150))
				{
					if (Rate >= 450)
					{
						if (Rate >= 650)
						{
							if (Rate >= 850)
							{
								CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2663, 0, 1, -1);
							}
							else {
								CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2664, 0, 1, -1);
							}
						}
						else {
							CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2665, 0, 1, -1);
						}
					}
					else {
						CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2537, 0, 1, -1);
					}

					return;
				}

				if (Key == 202 && CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 2532, 75) && CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 2654, 1))
				{
					if (Rate >= 550)
					{
						CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2663, 0, 1, -1);
					}
					else {
						CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2664, 0, 1, -1);
					}

					return;
				}

				if (Key == 201 && CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 2532, 75))
				{
					if (Rate >= 450)
					{
						if (Rate >= 750)
						{
							CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2663, 0, 1, -1);
						}
						else {
							CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2664, 0, 1, -1);
						}
					}
					else {
						CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2537, 0, 1, -1);
					}

					return;
				}

				if (Key == 107 && CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 2531, 200))
				{
					if (Rate >= 350)
					{
						if (Rate >= 550)
						{
							if (Rate >= 750)
							{
								CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2659, 0, 1, -1);
							}
							else {
								CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2660, 0, 1, -1);
							}
						}
						else {
							CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2661, 0, 1, -1);
						}
					}
					else {
						CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2662, 0, 1, -1);
					}

					return;
				}

				if (Key == 106 && CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 2531, 150) && CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 2654, 1))
				{
					if (Rate >= 400)
					{
						if (Rate >= 600)
						{
							if (Rate >= 800)
							{
								CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2659, 0, 1, -1);
							}
							else {
								CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2660, 0, 1, -1);
							}
						}
						else {
							CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2661, 0, 1, -1);
						}
					}
					else {
						CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2662, 0, 1, -1);
					}

					return;
				}

				if (Key == 105 && CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 2531, 150))
				{
					if (Rate >= 400)
					{
						if (Rate >= 600)
						{
							if (Rate >= 800)
							{
								if (Rate >= 900)
								{
									CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2659, 0, 1, -1);
								}
								else {
									CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2660, 0, 1, -1);
								}
							}
							else {
								CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2661, 0, 1, -1);
							}
						}
						else {
							CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2662, 0, 1, -1);
						}
					}
					else {
						CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2537, 0, 1, -1);
					}

					return;
				}

				if (Key == 104 && CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 2531, 100) && CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 2654, 1))
				{
					if (Rate >= 400)
					{
						if (Rate >= 600)
						{
							CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2659, 0, 1, -1);
						}
						else {
							CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2660, 0, 1, -1);
						}
					}
					else {
						CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2661, 0, 1, -1);
					}

					return;
				}

				if (Key == 103 && CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 2531, 100))
				{
					if (Rate >= 450)
					{
						if (Rate >= 650)
						{
							if (Rate >= 850)
							{
								CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2659, 0, 1, -1);
							}
							else {
								CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2660, 0, 1, -1);
							}
						}
						else {
							CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2661, 0, 1, -1);
						}
					}
					else {
						CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2537, 0, 1, -1);
					}

					return;
				}

				if (Key == 102 && CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 2531, 50) && CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 2654, 1))
				{
					if (Rate >= 550)
					{
						CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2659, 0, 1, -1);
					}
					else {
						CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2660, 0, 1, -1);
					}

					return;
				}

				if (Key == 101 && CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 2531, 50))
				{
					if (Rate >= 550)
					{
						if (Rate >= 750)
						{
							if (Rate >= 900)
							{
								if (Rate >= 950)
								{
									CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2659, 0, 1, -1);
								}
								else {
									CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2660, 0, 1, -1);
								}
							}
							else {
								CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2661, 0, 1, -1);
							}
						}
						else {
							CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2662, 0, 1, -1);
						}
					}
					else {
						CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2537, 0, 1, -1);
					}

					return;
				}

				if (Key == 7 && CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 2530, 200))
				{
					if (Rate >= 350)
					{
						if (Rate >= 550)
						{
							if (Rate >= 750)
							{
								CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2655, 0, 1, -1);
							}
							else {
								CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2656, 0, 1, -1);
							}
						}
						else {
							CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2657, 0, 1, -1);
						}
					}
					else {
						CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2658, 0, 1, -1);
					}

					return;
				}

				if (Key == 6 && CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 2530, 150) && CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 2654, 1))
				{
					if (Rate >= 400)
					{
						if (Rate >= 600)
						{
							if (Rate >= 800)
							{
								CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2655, 0, 1, -1);
							}
							else {
								CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2656, 0, 1, -1);
							}
						}
						else {
							CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2657, 0, 1, -1);
						}
					}
					else {
						CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2658, 0, 1, -1);
					}

					return;
				}

				if (Key == 5 && CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 2530, 150))
				{
					if (Rate >= 400)
					{
						if (Rate >= 600)
						{
							if (Rate >= 800)
							{
								if (Rate >= 900)
								{
									CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2655, 0, 1, -1);
								}
								else {
									CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2656, 0, 1, -1);
								}
							}
							else {
								CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2657, 0, 1, -1);
							}
						}
						else {
							CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2658, 0, 1, -1);
						}
					}
					else {
						CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2537, 0, 1, -1);
					}

					return;
				}

				if (Key == 4 && CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 2530, 100) && CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 2654, 1))
				{
					if (Rate >= 400)
					{
						if (Rate >= 600)
						{
							CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2655, 0, 1, -1);
						}
						else {
							CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2656, 0, 1, -1);
						}
					}
					else {
						CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2657, 0, 1, -1);
					}

					return;
				}

				if (Key == 3 && CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 2530, 100))
				{
					if (Rate >= 450)
					{
						if (Rate >= 650)
						{
							if (Rate >= 850)
							{
								CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2655, 0, 1, -1);
							}
							else {
								CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2656, 0, 1, -1);
							}
						}
						else {
							CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2657, 0, 1, -1);
						}
					}
					else {
						CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2537, 0, 1, -1);
					}

					return;
				}

				if (Key == 2 && CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 2530, 50) && CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 2654, 1))
				{
					if (Rate >= 550)
					{
						CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2655, 0, 1, -1);
					}
					else {
						CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2656, 0, 1, -1);
					}

					return;
				}

				if (Key == 1 && CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 2530, 50))
				{
					if (Rate >= 550)
					{
						if (Rate >= 750)
						{
							if (Rate >= 950)
							{
								CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2655, 0, 1, -1);
							}
							else {
								CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2656, 0, 1, -1);
							}
						}
						else {
							CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2657, 0, 1, -1);
						}
					}
					else {
						CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2537, 0, 1, -1);
					}

					return;
				}
			}
		}

		if (packet == 181)
		{
			int Type = 0, IID = 0, PerfIID = 0, JewelCheck = 0, Argument = 0, JewelAmount = 0, JewelCalculation = 0, GongValue = 0, Value = 0;
			CPacket::Read((char*)pPacket, (char*)pPos, "dddbwb", &IID, &PerfIID, &Type, &JewelCheck, &Argument, &JewelAmount);
			if (IID == PerfIID) return;

			if (!IID || !PerfIID)
				return;

			int PerfItem = IPlayer.ItemPointerLock(PerfIID);

			if (!PerfItem)
				return;

			IItem PerfItemx((void*)PerfItem);

			int ItemGet = IPlayer.ItemPointerLock(IID);

			if (!ItemGet)
				return;

			IItem MainItem((void*)ItemGet);
			int GetRate = 0, PrefixMainItem = MainItem.PrefixID(), PrefixStone = PerfItemx.PrefixID(), Rate = CTools::Rate(0, 10000);
			if (PrefixStone == 0) PrefixStone = 1;
			if (PrefixMainItem == 0) PrefixMainItem = 1;
			GetRate = DemonGongStoneEnchant[PrefixMainItem - 1][PrefixStone - 1];

			if (MainItem.GetInfo() & 4194304)
			{
				IPlayer.SystemMessage("Refining the Stone of Demon Gong can not be use on locked items.", TEXTCOLOR_RED);
				return;
			}

			if (PerfItemx.CheckIndex() < 3199 || PerfItemx.CheckIndex() > 3201)
			{
				IPlayer.BoxMsg("This is wrong material item.");
				return;
			}

			if (MainItem.CheckIndex() < 3199 || MainItem.CheckIndex() > 3201)
			{
				IPlayer.BoxMsg("This is wrong material item.");
				return;
			}

			if (MainItem.PrefixID() >= 10)
			{
				IPlayer.BoxMsg("Material grade already maximum.");
				return;
			}

			if (!CBase::IsDeleted((int)PerfItemx.GetOffset()))
				IPlayer.RemoveItem((int)PerfItemx.GetOffset());

			if (JewelCheck == 1 && JewelAmount >= 1 && JewelAmount <= 10)
			{
				int JewelItem = CPlayer::_FindItem((int)IPlayer.Offset, JewelIndex, (50 * JewelAmount));
				if (JewelItem)
				{
					if (!(*(int(__thiscall **)(DWORD, void *, signed int, signed int))(*(DWORD*)JewelItem + 120))(JewelItem, IPlayer.GetOffset(), 9, -(50 * JewelAmount)))
						CPlayer::_OutOfInven((void*)Player, JewelItem);

					JewelCalculation = JewelAmount;
					GetRate += (JewelCalculation * 500);
				}
				else {
					return;
				}
			}

			if (Rate <= GetRate)
			{
				int AddPrefix = CItem::FindPrefix(PrefixMainItem + 1);

				if (!AddPrefix)
					return;

				*(DWORD *)((int)MainItem.GetOffset() + 44) = AddPrefix;
				CDBSocket::Write(19, "ddbb", MainItem.GetIID(), IPlayer.GetID(), PrefixMainItem + 1);
				CItem::SendItemInfo(MainItem.GetOffset(), (int)IPlayer.GetOffset(), 92);
				CPlayer::Write(IPlayer.GetOffset(), 255, "dbdb", 225, 0, MainItem.GetIID(), PrefixMainItem + 1);
			}
			else {
				IPlayer.BoxMsg("Refining the Stone of Demon Gong has failed.");
				CPlayer::Write(IPlayer.GetOffset(), 255, "dbd", 225, 1, 20);
			}

			return;
		}

		if (packet == 186)
		{
			char Type = 0; int Index = 0;
			CPacket::Read((char*)pPacket, (char*)pPos, "wb", &Index, &Type);

			if (Index && Type)
			{
				ConfigMining pMining = CheckMining.count(IPlayer.GetPID()) ? CheckMining.findValue(IPlayer.GetPID()) : ConfigMining();
				if (CPlayer::RemoveItem(IPlayer.GetOffset(), 9, JewelIndex, 1))
				{
					int Chance = 0, Type = 0;
					Chance = CTools::Rate(0, 1000);
					if (Chance < 50) Type = 2;
					else if (Chance < 200) Type = 1;

					if (MiningItems.count((pMining.Index * 1000) + Type)) {
						MiningItem mItem = MiningItems.find((pMining.Index * 1000) + Type)->second;
						std::vector<ItemStruct> ItemList = mItem.Items;
						for (int i = 0; i < mItem.NumItems; i++) {
							srand(time(0));
							std::random_shuffle(ItemList.begin(), ItemList.end());
							ItemStruct item = ItemList.front();
							CItem::InsertItem((int)Player, 27, item.Index, 0, item.Amount, -1);
						}
					}

					pMining.Cycle = pMining.Cycle + 1;

					if (pMining.Cycle >= 3)
					{
						if (pMining.Amount >= 1 && CPlayer::RemoveItem(IPlayer.GetOffset(), 9, pMining.Index, 1))
						{
							pMining.Amount = pMining.Amount - 1;
							pMining.Cycle = 0;
						}
						else {
							IPlayer.CloseWindow("minebar");
							pMining.Time = 0;
							pMining.Cycle = 0;
							pMining.Index = 0;
							pMining.Amount = 0;
							CheckMining.replaceInsert(IPlayer.GetPID(), pMining);
							CPlayer::Write(IPlayer.GetOffset(), 220, "bb", 0, 3);
							return;
						}
					}

					CPlayer::Write(IPlayer.GetOffset(), 220, "bbw", 0, 4, pMining.Index);
					pMining.Time = GetTickCount() + 300000;
				}
				else {
					IPlayer.CloseWindow("minebar");
					pMining.Time = 0;
					pMining.Cycle = 0;
					pMining.Index = 0;
					pMining.Amount = 0;
				}

				CheckMining.replaceInsert(IPlayer.GetPID(), pMining);
			}

			return;
		}

		if (packet == 178)
		{
			int Type = 0, IID = 0, PerfIID = 0, JewelCheck = 0, Argument = 0, JewelAmount = 0, JewelCalculation = 0, PerfValue = 0, Value = 0;
			CPacket::Read((char*)pPacket, (char*)pPos, "bddbwb", &Type, &IID, &PerfIID, &JewelCheck, &Argument, &JewelAmount);
			if (IID == PerfIID) return;

			if (Type == 0)
			{
				int PerfItem = IPlayer.ItemPointerLock(PerfIID);
				if (!PerfItem)
					return;

				IItem PerfItemx((void*)PerfItem);

				int ItemGet = IPlayer.ItemPointerLock(IID);

				if (!ItemGet)
					return;

				IItem MainItem((void*)ItemGet);
				int PerfGradeCheck = 0;
				int ItemStats = 0;
				itemStat.Enter();
				if (GetItemStat.count(IID))
					ItemStats = GetItemStat.find(IID)->second;
				itemStat.Leave();

				if (ItemStats)
					PerfGradeCheck = ItemStats / 100000000;

				if (PerfGradeCheck >= 1 && (PerfItemx.CheckIndex() == 3057 || PerfItemx.CheckIndex() == 3059))
				{
					IPlayer.SystemMessage("Perforation shot can not be use on item anymore.", TEXTCOLOR_RED);
					return;
				}

				if (MainItem.GetInfo() & 4194304 && (PerfItemx.CheckIndex() == 3057 || PerfItemx.CheckIndex() == 3059))
				{
					IPlayer.SystemMessage("You can not add qigong ability on locked items.", TEXTCOLOR_RED);
					return;
				}

				if (PerfGradeCheck < 1 && PerfItemx.CheckIndex() == 3166)
					return;

				if (MainItem.GetGrade() < 65 && PerfItemx.CheckIndex() == 3166)
					return;

				if (PerfGradeCheck >= 3 && PerfItemx.CheckIndex() == 3166)
				{
					IPlayer.SystemMessage("Gun of demon gong can not be use on item anymore.", TEXTCOLOR_RED);
					return;
				}

				if (MainItem.GetInfo() & 4194304 && PerfItemx.CheckIndex() == 3166)
				{
					IPlayer.SystemMessage("You can not add demon gong ability on locked items.", TEXTCOLOR_RED);
					return;
				}

				if (JewelCheck == 1 && JewelAmount >= 1 && JewelAmount <= 10)
				{
					int Multiply = 10;
					if (PerfItemx.CheckIndex() == 3166) Multiply = 20;

					if (IPlayer.RemoveItem(JewelIndex, (Multiply*JewelAmount)))
					{
						JewelCalculation = JewelAmount;
					}
					else {
						return;
					}
				}

				if (PerfItemx.CheckIndex() == 3057 && IPlayer.RemoveItem(3057, 1))
				{
					int PerfRate = CTools::Rate(1, 1000);

					if (PerfRate >= (850 - (JewelCalculation * 70)))
					{
						int ItemStat = 0;
						itemStat.Enter();
						if (GetItemStat.count(IID))
							ItemStat = GetItemStat.find(IID)->second;

						GetItemStat[IID] = ItemStat + 100000000;
						itemStat.Leave();
						CDBSocket::Write(90, "dd", ItemStat + 100000000, MainItem.GetIID());

						if (CItem::IsState((int)MainItem.GetOffset(), 64))
							CItem::SubState((int)MainItem.GetOffset(), 64);

						CItem::SendItemInfo(MainItem.GetOffset(), (int)IPlayer.GetOffset(), 92);
						CPlayer::Write(IPlayer.GetOffset(), 0xFF, "ddddd", 242, 0, 0, 128, 255);
						return;
					}
					else {
						if (CItem::IsState((int)MainItem.GetOffset(), 64))
						{
							CDBSocket::Write(21, "dddbb", MainItem.GetIID(), IPlayer.GetID(), 64, 0, 255);
							CItem::SubState((int)MainItem.GetOffset(), 64);
							CItem::SendItemInfo(MainItem.GetOffset(), (int)IPlayer.GetOffset(), 92);
							return;
						}

						if (MainItem.GetEndurance() >= 5)
							MainItem.DecreaseEndurance(5);
						else
							MainItem.DecreaseEndurance(MainItem.GetEndurance());

						if (MainItem.GetEndurance() <= 0)
						{
							CPlayer::Write(IPlayer.GetOffset(), 91, "db", MainItem.GetIID(), MainItem.GetEndurance());
							CDBSocket::Write(3, "ddwdbddd", MainItem.GetIID(), IPlayer.GetID(), MainItem.CheckIndex(), 1, 27, 0, 0, 0);

							if (CItem::GetLevel((int)MainItem.GetOffset()) >= 40)
								CItem::InsertItem((int)IPlayer.GetOffset(), 27, 517, 0, 15, -1);

							CBase::Delete(MainItem.GetOffset());
						}
						else {
							CPlayer::Write(IPlayer.GetOffset(), 91, "db", MainItem.GetIID(), MainItem.GetEndurance());
							CDBSocket::Write(18, "ddb", MainItem.GetIID(), IPlayer.GetID(), MainItem.GetEndurance());
						}

						return;
					}
				}

				if (PerfItemx.CheckIndex() == 3059 && IPlayer.RemoveItem(3059, 1))
				{
					int PerfRate = CTools::Rate(1, 1000);

					if (PerfRate <= (Perfo * 10) + (JewelCalculation * 70))
					{
						int ItemStat = 0;
						itemStat.Enter();
						if (GetItemStat.count(IID))
							ItemStat = GetItemStat.find(IID)->second;

						GetItemStat[IID] = ItemStat + 100000000;
						itemStat.Leave();
						CDBSocket::Write(90, "dd", ItemStat + 100000000, MainItem.GetIID());

						if (CItem::IsState((int)MainItem.GetOffset(), 64))
							CItem::SubState((int)MainItem.GetOffset(), 64);

						CItem::SendItemInfo(MainItem.GetOffset(), (int)IPlayer.GetOffset(), 92);
						CPlayer::Write(IPlayer.GetOffset(), 0xFF, "ddddd", 242, 0, 0, 128, 255);
						return;
					}
					else {
						if (CItem::IsState((int)MainItem.GetOffset(), 64))
						{
							CDBSocket::Write(21, "dddbb", MainItem.GetIID(), IPlayer.GetID(), 64, 0, 255);
							CItem::SubState((int)MainItem.GetOffset(), 64);
							CItem::SendItemInfo(MainItem.GetOffset(), (int)IPlayer.GetOffset(), 92);
							return;
						}

						if (MainItem.GetEndurance() >= 5)
							MainItem.DecreaseEndurance(5);
						else
							MainItem.DecreaseEndurance(MainItem.GetEndurance());

						if (MainItem.GetEndurance() <= 0)
						{
							CPlayer::Write(IPlayer.GetOffset(), 91, "db", MainItem.GetIID(), MainItem.GetEndurance());
							CDBSocket::Write(3, "ddwdbddd", MainItem.GetIID(), IPlayer.GetID(), MainItem.CheckIndex(), 1, 27, 0, 0, 0);

							if (CItem::GetLevel((int)MainItem.GetOffset()) >= 40)
								CItem::InsertItem((int)IPlayer.GetOffset(), 27, 517, 0, 15, -1);

							CBase::Delete(MainItem.GetOffset());
						}
						else {
							CPlayer::Write(IPlayer.GetOffset(), 91, "db", MainItem.GetIID(), MainItem.GetEndurance());
							CDBSocket::Write(18, "ddb", MainItem.GetIID(), IPlayer.GetID(), MainItem.GetEndurance());
						}

						return;
					}
				}

				if (PerfItemx.CheckIndex() == 3166 && IPlayer.RemoveItem(3166, 1))
				{
					int PerfRate = CTools::Rate(1, 1000);

					if (PerfRate <= ((Gun * 10) + (JewelCalculation * 70)))
					{
						int ItemStat = 0;
						itemStat.Enter();
						if (GetItemStat.count(IID))
							ItemStat = GetItemStat.find(IID)->second;

						GetItemStat[IID] = ItemStat + 100000000;
						itemStat.Leave();
						CDBSocket::Write(90, "dd", ItemStat + 100000000, MainItem.GetIID());

						if (CItem::IsState((int)MainItem.GetOffset(), 64))
							CItem::SubState((int)MainItem.GetOffset(), 64);

						CItem::SendItemInfo(MainItem.GetOffset(), (int)IPlayer.GetOffset(), 92);
						CPlayer::Write(IPlayer.GetOffset(), 0xFF, "ddddd", 242, 0, 0, 128, 255);
						return;
					}
					else {
						if (CItem::IsState((int)MainItem.GetOffset(), 64))
						{
							CDBSocket::Write(21, "dddbb", MainItem.GetIID(), IPlayer.GetID(), 64, 0, 255);
							CItem::SubState((int)MainItem.GetOffset(), 64);
							CItem::SendItemInfo(MainItem.GetOffset(), (int)IPlayer.GetOffset(), 92);
							return;
						}

						if (MainItem.GetEndurance() >= 5)
							MainItem.DecreaseEndurance(5);
						else
							MainItem.DecreaseEndurance(MainItem.GetEndurance());

						if (MainItem.GetEndurance() <= 0)
						{
							CPlayer::Write(IPlayer.GetOffset(), 91, "db", MainItem.GetIID(), MainItem.GetEndurance());
							CDBSocket::Write(3, "ddwdbddd", MainItem.GetIID(), IPlayer.GetID(), MainItem.CheckIndex(), 1, 27, 0, 0, 0);

							if (CItem::GetLevel((int)MainItem.GetOffset()) >= 40)
								CItem::InsertItem((int)IPlayer.GetOffset(), 27, 517, 0, 15, -1);

							CBase::Delete(MainItem.GetOffset());
						}
						else {
							CPlayer::Write(IPlayer.GetOffset(), 91, "db", MainItem.GetIID(), MainItem.GetEndurance());
							CDBSocket::Write(18, "ddb", MainItem.GetIID(), IPlayer.GetID(), MainItem.GetEndurance());
						}

						return;
					}
				}
			}

			if (Type == 1)
			{
				int SetType = 0;
				int PerfItem = IPlayer.ItemPointerLock(PerfIID);

				if (!PerfItem)
					return;

				IItem QigongItemx((void*)PerfItem);
				int ItemGet = IPlayer.ItemPointerLock(IID);

				if (!ItemGet)
					return;

				IItem MainItem((void*)ItemGet);
				int QigongGradeCheck = 0;

				if (MainItem.GetInfo() & 4194304)
				{
					IPlayer.SystemMessage("Qigong can not be use on locked items.", TEXTCOLOR_RED);
					return;
				}

				int ItemStat = 0;
				itemStat.Enter();
				if (GetItemStat.count(IID))
					ItemStat = GetItemStat.find(IID)->second;
				itemStat.Leave();
				if (ItemStat)
					QigongGradeCheck = ItemStat % 100;

				if (JewelCheck == 1 && JewelAmount >= 1 && JewelAmount <= 10)
				{
					if (IPlayer.RemoveItem(JewelIndex, (10 * JewelAmount)))
					{
						JewelCalculation = JewelAmount;
					}
					else {
						return;
					}
				}

				if (QigongItemx.CheckIndex() == 3056 && IPlayer.RemoveItem(3056, 1))
				{
					int QigongRate = CTools::Rate(1, 1000);

					if (QigongRate >= (550 - (JewelCalculation * 50)))
					{
						if (QigongRate >= (750 - (JewelCalculation * 60)))
						{
							if (QigongRate >= (850 - (JewelCalculation * 60)))
							{
								if (QigongRate >= (950 - (JewelCalculation * 70)))
								{
									if (QigongRate >= (970 - (JewelCalculation * 70)))
									{
										if (QigongRate >= (980 - (JewelCalculation * 80)))
										{
											if (QigongRate >= (990 - (JewelCalculation * 80)))
											{
												int Rate = CTools::Rate(71, 80);
												SetType += Rate;
												std::string msg = (std::string)IPlayer.GetName();
												msg = msg + " has been fused with the Black Spirit Of Insanity!";
												if (fuseNotice){
													CPlayer::WriteAll(0xFF, "dsd", 247, msg.c_str(), 8);
													ToNoticeWebhook(msg.c_str());

												}
											}
											else {
												int Rate = CTools::Rate(61, 70);
												SetType += Rate;
												std::string msg = (std::string)IPlayer.GetName();
												msg = msg + " has been fused with the Black Spirit Of Thunder!";
												if (fuseNotice){
													CPlayer::WriteAll(0xFF, "dsd", 247, msg.c_str(), 8);
													ToNoticeWebhook(msg.c_str());

												}
											}
										}
										else {
											int Rate = CTools::Rate(51, 60);
											SetType += Rate;
										}
									}
									else {
										int Rate = CTools::Rate(41, 50);
										SetType += Rate;
									}
								}
								else {
									int Rate = CTools::Rate(31, 40);
									SetType += Rate;
								}
							}
							else {
								int Rate = CTools::Rate(21, 30);
								SetType += Rate;
							}
						}
						else {
							int Rate = CTools::Rate(11, 20);
							SetType += Rate;
						}
					}
					else {
						int Rate = CTools::Rate(1, 10);
						SetType += Rate;
					}

					itemStat.Enter();
					GetItemStat[IID] = (ItemStat + SetType) - QigongGradeCheck;
					itemStat.Leave();
					CDBSocket::Write(90, "dd", (ItemStat + SetType) - QigongGradeCheck, MainItem.GetIID());
					CItem::SendItemInfo(MainItem.GetOffset(), (int)IPlayer.GetOffset(), 92);
					CPlayer::Write(IPlayer.GetOffset(), 0xFF, "ddd", 235, MainItem.GetIID(), SetType);
					return;
				}

				if (QigongItemx.CheckIndex() == 3058 && IPlayer.RemoveItem(3058, 1))
				{
					int QigongRate = CTools::Rate(1, 100);

					if (QigongRate >= 100 - Insanity) {
						int Rate = CTools::Rate(71, 80);
						SetType += Rate;
						std::string msg = (std::string)IPlayer.GetName();
						msg = msg + " has been fused with the Black Spirit Of Insanity!";
						if (fuseNotice){
							CPlayer::WriteAll(0xFF, "dsd", 247, msg.c_str(), 8);
							ToNoticeWebhook(msg.c_str());

						}
					}
					else if (QigongRate >= 100 - Thunder) {
						int Rate = CTools::Rate(61, 70);
						SetType += Rate;
						std::string msg = (std::string)IPlayer.GetName();
						msg = msg + " has been fused with the Black Spirit Of Thunder!";
						if (fuseNotice){
							CPlayer::WriteAll(0xFF, "dsd", 247, msg.c_str(), 8);
							ToNoticeWebhook(msg.c_str());
						}
					}
					else if (QigongRate >= 100 - Violent) {
						int Rate = CTools::Rate(51, 60);
						SetType += Rate;
					}
					else if (QigongRate >= 100 - Storm) {
						int Rate = CTools::Rate(41, 50);
						SetType += Rate;
					}
					else if (QigongRate >= 100 - Ancient) {
						int Rate = CTools::Rate(31, 40);
						SetType += Rate;
					}
					else {
						int Rate = CTools::Rate(21, 30);
						SetType += Rate;
					}

					int ItemStat = 0;
					itemStat.Enter();
					if (GetItemStat.count(IID))
						ItemStat = GetItemStat.find(IID)->second;

					GetItemStat[IID] = (ItemStat + SetType) - QigongGradeCheck;
					itemStat.Leave();
					CDBSocket::Write(90, "dd", (ItemStat + SetType) - QigongGradeCheck, MainItem.GetIID());
					CItem::SendItemInfo(MainItem.GetOffset(), (int)IPlayer.GetOffset(), 92);
					CPlayer::Write(IPlayer.GetOffset(), 0xFF, "ddd", 235, MainItem.GetIID(), SetType);
					return;
				}

				int QIndex = QigongItemx.CheckIndex();
				if (QIndex >= 4421 && QIndex <= 4424 && IPlayer.RemoveItem(QIndex, 1))
				{
					int Rate = CTools::Rate(41, 50);

					if (QIndex == 4421) {
						Rate = CTools::Rate(71, 80);
						std::string msg = (std::string)IPlayer.GetName();
						msg = msg + " has been fused with the Black Spirit Of Insanity!";
						if (fuseNotice)
							CPlayer::WriteAll(0xFF, "dsd", 247, msg.c_str(), 8);
					}
					else if (QIndex == 4422) {
						Rate = CTools::Rate(61, 70);
						std::string msg = (std::string)IPlayer.GetName();
						msg = msg + " has been fused with the Black Spirit Of Thunder!";
						if (fuseNotice)
							CPlayer::WriteAll(0xFF, "dsd", 247, msg.c_str(), 8);
					}
					else if (QIndex == 4423)
						Rate = CTools::Rate(51, 60);

					SetType += Rate;
					int ItemStat = 0;
					itemStat.Enter();
					if (GetItemStat.count(IID))
						ItemStat = GetItemStat.find(IID)->second;

					GetItemStat[IID] = (ItemStat + SetType) - QigongGradeCheck;
					itemStat.Leave();
					CDBSocket::Write(90, "dd", (ItemStat + SetType) - QigongGradeCheck, MainItem.GetIID());
					CItem::SendItemInfo(MainItem.GetOffset(), (int)IPlayer.GetOffset(), 92);
					CPlayer::Write(IPlayer.GetOffset(), 0xFF, "ddd", 235, MainItem.GetIID(), SetType);
					return;
				}
			}

			if (Type == 2)
			{
				int PerfItem = IPlayer.ItemPointerLock(PerfIID);

				if (!PerfItem)
					return;

				IItem DemonGongItemx((void*)PerfItem);
				int ItemGet = IPlayer.ItemPointerLock(IID);

				if (!ItemGet)
					return;

				IItem MainItem((void*)ItemGet);
				int FirstDemonGongType = 0, DemonGongStyle = 0, GetStonePrefix = 1, FirstDemonGongStat = 0;

				if (MainItem.GetInfo() & 4194304)
				{
					IPlayer.SystemMessage("Demon Gong can not be use on locked items.", TEXTCOLOR_RED);
					return;
				}

				if (DemonGongItemx.CheckIndex() < 3199 || DemonGongItemx.CheckIndex() > 3201)
				{
					IPlayer.BoxMsg("This is wrong material item.");
					return;
				}

				if (DemonGongItemx.PrefixID() > 1) GetStonePrefix = DemonGongItemx.PrefixID();
				if (DemonGongItemx.CheckIndex() == 3199) DemonGongStyle = 1;
				if (DemonGongItemx.CheckIndex() == 3200) DemonGongStyle = 3;
				if (DemonGongItemx.CheckIndex() == 3201) DemonGongStyle = 2;
				if (!DemonGongStyle) return;

				int ItemStat = 0;
				itemStat.Enter();
				if (GetItemStat.count(IID))
					ItemStat = GetItemStat.find(IID)->second;
				itemStat.Leave();
				if (ItemStat)
					FirstDemonGongType = (ItemStat % 100000000) / 10000000;

				if (JewelCheck == 2 && MainItem.GetGrade() >= 90)
				{
					int SecondDemonGongType = (ItemStat % 1000000) / 100000, SecondDemonGongStat = 0;

					if (SecondDemonGongType)
					{
						IPlayer.SystemMessage("This is wrong material item.", TEXTCOLOR_RED);
						return;
					}

					if (SecondDemonGongType && SecondDemonGongType != DemonGongStyle)
					{
						IPlayer.SystemMessage("This is wrong material item.", TEXTCOLOR_RED);
						return;
					}

					if (!CBase::IsDeleted((int)DemonGongItemx.GetOffset()))
						IPlayer.RemoveItem((int)DemonGongItemx.GetOffset());
					itemStat.Enter();
					if (!SecondDemonGongType)
						GetItemStat[IID] = ItemStat + (DemonGongStyle * 100000);

					SecondDemonGongStat = (GetItemStat.find(IID)->second % 100000) / 10000;
					itemStat.Leave();
					if (SecondDemonGongStat) return;
					itemStat.Enter();
					int newV = GetItemStat.find(IID)->second + (GetStonePrefix * 10000) - 10000;
					GetItemStat[IID] = newV;
					itemStat.Leave();
					CDBSocket::Write(90, "dd", newV, MainItem.GetIID());

					if (DemonGongStyle == 1)
						CPlayer::Write(IPlayer.GetOffset(), 255, "dddb", 224, MainItem.GetIID(), 10, JewelCheck);
					else
						CPlayer::Write(IPlayer.GetOffset(), 255, "dddb", 224, MainItem.GetIID(), (DemonGongStyle - 1) << 24, JewelCheck);

					CItem::SendItemInfo(MainItem.GetOffset(), (int)IPlayer.GetOffset(), 92);
					return;
				}

				if (JewelCheck == 1)
				{
					if (FirstDemonGongType)
					{
						IPlayer.SystemMessage("This is wrong material item.", TEXTCOLOR_RED);
						return;
					}

					if (FirstDemonGongType && FirstDemonGongType != DemonGongStyle)
					{
						IPlayer.SystemMessage("This is wrong material item.", TEXTCOLOR_RED);
						return;
					}

					if (!CBase::IsDeleted((int)DemonGongItemx.GetOffset()))
						IPlayer.RemoveItem((int)DemonGongItemx.GetOffset());
					itemStat.Enter();
					if (!FirstDemonGongType)
						GetItemStat[IID] = GetItemStat.find(IID)->second + (DemonGongStyle * 10000000);

					FirstDemonGongStat = (GetItemStat.find(IID)->second % 10000000) / 1000000;
					itemStat.Leave();
					if (FirstDemonGongStat && MainItem.GetGrade() < 90) return;
					itemStat.Enter();
					int NewV = GetItemStat.find(IID)->second + (GetStonePrefix * 1000000) - 1000000;
					GetItemStat[IID] = NewV;
					itemStat.Leave();
					CDBSocket::Write(90, "dd", NewV, MainItem.GetIID());

					if (DemonGongStyle == 1)
						CPlayer::Write(IPlayer.GetOffset(), 255, "dddb", 224, MainItem.GetIID(), 10, JewelCheck);
					else
						CPlayer::Write(IPlayer.GetOffset(), 255, "dddb", 224, MainItem.GetIID(), (DemonGongStyle - 1) << 24, JewelCheck);

					CItem::SendItemInfo(MainItem.GetOffset(), (int)IPlayer.GetOffset(), 92);
					return;
				}

				return;
			}

			return;
		}

		if (packet == 99)
		{
			char  mtype = 0, yintype = 0; int key = 0, TargetIID = 0, Value = 0, CheckWater = 0;
			CPacket::Read((char*)pPacket, (char*)pPos, "bbdd", &mtype, &yintype, &key, &TargetIID);

			int Item = IPlayer.ItemPointerLock(TargetIID);

			if (!Item)
				return;

			IItem MainItem((void*)Item);

			if (key > 1000)
			{
				key -= 1000;
				CheckWater = 1;
			}

			if (mtype == 10 && yintype == 1)
			{
				if (key > 28)
					key -= 6;
				else if (key > 18)
					key -= 4;
				else if (key > 8)
					key -= 2;

				if (IPlayer.IsOnline() && CPlayer::GetInvenSize((int)IPlayer.GetOffset()) < IPlayer.MaxInventorySize())
				{
					if (IPlayer.RemoveItem((key + 2953), 2))
					{
						CItem::InsertItem((int)IPlayer.GetOffset(), 27, (key + 2985), 0, 1, -1);
						IPlayer.CloseWindow("yinyang_enchant");
						IPlayer.OpenWindow("yinyang_enchant", 0, 0);
					}
				}
				else {
					IPlayer.SystemMessage("Inventory is full.", TEXTCOLOR_RED);
				}
			}

			if (mtype == 20 && yintype == 2)
			{
				if (key > 128)
					key -= 6;
				else if (key > 118)
					key -= 4;
				else if (key > 108)
					key -= 2;

				if (IPlayer.RemoveItem((key + 2853), 1))
				{
					if (CheckWater == 1 && !IPlayer.RemoveItem(3024, 1)) {
						IPlayer.SystemMessage("Water trigram was not found, please try again.", TEXTCOLOR_RED);
						IPlayer.CloseWindow("yinyang_enchant");
						IPlayer.OpenWindow("yinyang_enchant", 0, 0);
						CheckWater = 0;
						return;
					}

					int NewValue = 0;
					itemStat.Enter();
					if (GetItemStat.count(TargetIID))
						NewValue = GetItemStat.find(TargetIID)->second;
					itemStat.Leave();

					int GetCurrentGrade = (NewValue % 10000) / 100;
					if (GetCurrentGrade == 0) GetCurrentGrade = 1;
					int GetRate = TriagramUpgradeRate[0][GetCurrentGrade - 1], Rate = CTools::Rate(1, 24000);

					if (Rate <= GetRate + (CheckWater * 1000))
					{
						NewValue += 100;
						itemStat.Enter();
						GetItemStat[TargetIID] = NewValue;
						itemStat.Leave();
						CDBSocket::Write(90, "dd", NewValue, TargetIID);

						CItem::SendItemInfo(MainItem.GetOffset(), (int)IPlayer.GetOffset(), 92);
						CPlayer::Write(IPlayer.GetOffset(), 176, "bbdd", 0, 2, 0, MainItem.GetIID());
					}
					else {
						if (GetCurrentGrade > 4)
						{
							int Rate = CTools::Rate(0, 2);

							if (CheckWater != 1){
								if (!Rate)
								{
									NewValue -= 100;

									CPlayer::Write(IPlayer.GetOffset(), 176, "bb", 0, 3);
									itemStat.Enter();
									GetItemStat[TargetIID] = NewValue;
									itemStat.Leave();
									CDBSocket::Write(90, "dd", NewValue, TargetIID);

									CItem::SendItemInfo(MainItem.GetOffset(), (int)IPlayer.GetOffset(), 92);
								}
								else {
									CPlayer::Write(IPlayer.GetOffset(), 176, "bb", 0, 4);
								}
							}
							else{

								if (!Rate)
								{
									//CPlayer::Write(IPlayer.GetOffset(),176,"bb",0,3);
									//GetItemStat[TargetIID] = GetItemStat.find(TargetIID)->second;
									IPlayer.BoxMsg("Water Upgrading Failed.");
									itemStat.Enter();
									int atemStat = GetItemStat.count(TargetIID) ? GetItemStat.find(TargetIID)->second : 0;
									itemStat.Leave();
									CDBSocket::Write(90, "dd", atemStat, TargetIID);

									CItem::SendItemInfo(MainItem.GetOffset(), (int)IPlayer.GetOffset(), 92);
								}
								else {
									CPlayer::Write(IPlayer.GetOffset(), 176, "bb", 0, 4);
								}


							}
						}
						else {
							CPlayer::Write(IPlayer.GetOffset(), 176, "bb", 0, 4);
						}
					}
				}
			}

			if (mtype == 30 && yintype == 3)
			{
				if (key == 2000 && IPlayer.RemoveItem(31, 5000) && IPlayer.RemoveItem(2655, 3)
					&& IPlayer.RemoveItem(2659, 3) && IPlayer.RemoveItem(2660, 1))
				{
					CItem::InsertItem((int)IPlayer.GetOffset(), 27, 3018, 0, 1, -1);
					return;
				}

				if (key == 2001 && IPlayer.RemoveItem(31, 1000000) && IPlayer.RemoveItem(2655, 36)
					&& IPlayer.RemoveItem(2659, 36) && IPlayer.RemoveItem(2660, 9)
					&& IPlayer.RemoveItem(2671, 9))
				{
					CItem::InsertItem((int)IPlayer.GetOffset(), 27, 3019, 0, 1, -1);
					return;
				}

				if (key == 2002 && IPlayer.RemoveItem(31, 14000000) && IPlayer.RemoveItem(2655, 144)
					&& IPlayer.RemoveItem(2659, 144) && IPlayer.RemoveItem(2660, 24)
					&& IPlayer.RemoveItem(2671, 24) && IPlayer.RemoveItem(2673, 4))
				{
					CItem::InsertItem((int)IPlayer.GetOffset(), 27, 3020, 0, 1, -1);
					return;
				}
			}

			if (mtype == 100 && yintype == 10 && MainItem.CheckIndex() >= 3018 && MainItem.CheckIndex() <= 3020)
			{
				if (IPlayer.GetBuffValue(BuffNames::TrigramGrade) >= 4 && IPlayer.GetBuffValue(BuffNames::TrigramHP)
					&& IPlayer.GetBuffValue(BuffNames::TrigramMP) && IPlayer.GetBuffValue(BuffNames::TrigramAtk)
					&& IPlayer.GetBuffValue(BuffNames::TrigramStr) && IPlayer.GetBuffValue(BuffNames::TrigramAgi)
					&& IPlayer.GetBuffValue(BuffNames::TrigramInt) && IPlayer.GetBuffValue(BuffNames::TrigramWis)
					&& IPlayer.GetBuffValue(BuffNames::TrigramHth))
				{
					itemStat.Enter();
					bool Allowed = (!GetItemStat.count(TargetIID) || !GetItemStat.find(TargetIID)->second);
					itemStat.Leave();
					if (Allowed) {
						int SetPrefix = 0, CurrentGrade = (IPlayer.GetBuffValue(BuffNames::TrigramGrade) + 1);

						if (MainItem.CheckIndex() == 3020)
						{
							if (CurrentGrade == 5) SetPrefix = CTools::Rate(97, 104);
							if (CurrentGrade == 6) SetPrefix = CTools::Rate(105, 112);
							if (CurrentGrade == 7) SetPrefix = CTools::Rate(121, 128);
							if (CurrentGrade == 8) SetPrefix = CTools::Rate(153, 160);
							if (CurrentGrade == 9) SetPrefix = CTools::Rate(113, 120);
							if (CurrentGrade == 10) SetPrefix = CTools::Rate(129, 136);
							if (CurrentGrade == 11) SetPrefix = CTools::Rate(161, 168);
							if (CurrentGrade == 12) SetPrefix = CTools::Rate(137, 144);
							if (CurrentGrade >= 13) SetPrefix = CTools::Rate(169, 176);
						}
						else {
							if (CurrentGrade == 5) SetPrefix = CTools::Rate(1, 8);
							if (CurrentGrade == 6) SetPrefix = CTools::Rate(9, 16);
							if (CurrentGrade == 7) SetPrefix = CTools::Rate(33, 40);
							if (CurrentGrade == 8) SetPrefix = CTools::Rate(65, 72);
							if (CurrentGrade == 9) SetPrefix = CTools::Rate(17, 24);
							if (CurrentGrade == 10) SetPrefix = CTools::Rate(41, 18);
							if (CurrentGrade == 11) SetPrefix = CTools::Rate(73, 80);
							if (CurrentGrade == 12) SetPrefix = CTools::Rate(49, 56);
							if (CurrentGrade == 13) SetPrefix = CTools::Rate(81, 88);
							if (CurrentGrade == 14) SetPrefix = CTools::Rate(145, 152);
							if (CurrentGrade == 15) SetPrefix = CTools::Rate(177, 184);
						}

						CPlayer::Write(IPlayer.GetOffset(), 176, "bbdd", 0, 7, SetPrefix, MainItem.GetIID());
						itemStat.Enter();
						GetItemStat[TargetIID] = (1000 * SetPrefix);
						itemStat.Leave();
						CDBSocket::Write(90, "dd", 1000 * SetPrefix, TargetIID);
						CItem::SendItemInfo(MainItem.GetOffset(), (int)IPlayer.GetOffset(), 92);
					}
				}
			}

			if (mtype == 110 && yintype == 11 && MainItem.CheckIndex() >= 3018 && MainItem.CheckIndex() <= 3020 && IPlayer.RemoveItem(3023, 1))
			{
				CPlayer::Write(IPlayer.GetOffset(), 176, "bbdd", 0, 6);
				itemStat.Enter();
				GetItemStat[TargetIID] = 0;
				itemStat.Leave();

				CDBSocket::Write(90, "dd", 0, MainItem.GetIID());
				CItem::SendItemInfo(MainItem.GetOffset(), (int)IPlayer.GetOffset(), 92);
			}

			return;
		}

		if (packet == 142)
		{
			int MSSIID = 0, MSSX = 0, MSSY = 0, MSSMap = 0, MSSValue = 0, Value = 0, Item = 0;
			CPacket::Read((char*)pPacket, (char*)pPos, "ddddd", &MSSIID, &MSSMap, &MSSX, &MSSY, &MSSValue);

			if (MSSIID)
			{
				if (!IPlayer.IsValid())
					return;

				if (CSMap::IsOnTile(*(void **)((int)IPlayer.Offset + 320), (int)IPlayer.Offset + 332, 131072) || CSMap::IsOnTile(*(void **)((int)IPlayer.Offset + 320), (int)IPlayer.Offset + 332, 1048576))
				{
					IPlayer.SystemMessage("Can not be use in safezones.", TEXTCOLOR_ORANGE);
					return;
				}

				if (MSSMap)
				{
					IPlayer.SystemMessage("Can not be use in dungeon and battle areas.", TEXTCOLOR_ORANGE);
					return;
				}

				int Item = IPlayer.ItemPointerLock(MSSIID);

				if (!Item)
					return;

				IItem MainItem((void*)Item);
				int ItemIndex = MainItem.CheckIndex();

				if (IPlayer.IsValid() && MSS.count(ItemIndex) && MainItem.GetAmount() >= 1 && IPlayer.RemoveItem(MainItem.CheckIndex(), 1))
				{
					for (int i = 0; i < MSS.find(ItemIndex)->second.MonsterList.size(); i++) {
						Msss mss = MSS.find(ItemIndex)->second.MonsterList[i];
						if (mss.MobIndex && mss.Amount)
						{
							for (int j = 0; j < mss.Amount; j++)
							{
								IChar Monster((void*)Summon((int)IPlayer.GetOffset(), IPlayer.GetMap(), MSSX, MSSY, mss.MobIndex, 1, 1, 0, mss.Time * 1000, 0));
								if (Monster.IsValid() && IPlayer.IsValid())
								{
									Monster.Buff(367, BuffNames::BuffTime, 0);
									//MonsterAI[(int)Monster.GetOffset()] = (int)IPlayer.GetOffset();
									if (!mss.Public)
										Monster.UpdateBuff(BuffNames::SummonAI, BuffNames::BuffTime, (int)IPlayer.GetOffset());
								}
								else {
									Monster.Blob();
								}
							}
						}
					}
				}
			}

			return;
		}

		if (packet == 219)
		{
			int Type = 100; const char *Caller = "", *Recall = "";
			CPacket::xRead((char*)pPacket, "dss", &Type, &Caller, &Recall);

			if (!Caller || !Recall || strcmp(Caller, Recall) == 0) return;

			if (strlen(Caller) > 0 && strlen(Recall) > 0)
			{
				TargetFind myTarget(Caller);
				int player3 = (int)myTarget.getTarget();
				IChar RCT((void*)player3);

				TargetFind myTarget1(Recall);
				int player4 = (int)myTarget1.getTarget();

				IChar RC((void*)player4);

				if (Type == 1)
				{
					if (RCT.IsValid() && RC.IsValid() && RCT.IsBuff(304))
					{
						if (CSMap::IsOnTile(*(void **)((int)RCT.Offset + 320), (int)RCT.Offset + 332, 1048576) || RC.IsBuff(349) || (RCT.GetMap() == 6 && !CPlayer::FindItem(RC.Offset, 1620, 1)))
							RC.BoxMsg("Can not Go to the player");
						else
							RC.Teleport(RCT.GetMap(), RCT.GetX(), RCT.GetY());

						RCT.CancelBuff(304);
						return;
					}

					if (RCT.IsValid() && !RC.IsValid())
					{
						std::string name = Recall;
						std::string msg = name + " is not valid or offline.";
						RCT.BoxMsg(msg);
						return;
					}

					if (!RCT.IsValid() && RC.IsValid())
					{
						std::string name = Caller;
						std::string msg = name + " is not valid or offline.";
						RC.BoxMsg(msg);
						return;
					}

					return;
				}

				if (Type == 0 && RCT.IsValid())
				{
					std::string name = Recall;
					std::string msg = name + " refused your recall.";
					RCT.BoxMsg(msg);
					return;
				}
			}

			return;
		}

		if (packet == 118)
		{
			int Type = 0, IID = 0; const char *Name = "";
			CPacket::Read((char*)pPacket, (char*)pPos, "bds", &Type, &IID, &Name, 21);

			if (!Name)
				return;

			int Item = IPlayer.ItemPointerLock(IID);

			if (!Item)
				return;

			IItem Itemx((void*)Item);

			if (strlen(Name) > 0 && Item && Itemx.CheckIndex() == 1472)
			{
				TargetFind myTarget(Name);
				int player4 = (int)myTarget.getTarget();

				IChar Target((void*)player4);

				if (Target.IsValid() && IPlayer.IsValid())
				{
					if (CSMap::IsOnTile(*(void **)((int)IPlayer.Offset + 320), (int)IPlayer.Offset + 332, 1048576) || IPlayer.IsBuff(349)){
						IPlayer.BoxMsg("Can not use recall scroll here");
						return;
					}
					else
					if (IPlayer.RemoveItem(1472, 1))
					{
						std::string getname = IPlayer.GetName();
						std::string send = getname + " will recall you to him(her). Do you accept the recall?";
						CPlayer::Write(Target.GetOffset(), 0xFF, "ddsss", 228, 1000, send.c_str(), IPlayer.GetName(), Target.GetName());
						IPlayer.Buff(304, BuffNames::BuffTime, 0);
						IPlayer.SystemMessage("Recall scroll used.", TEXTCOLOR_GREEN);

					}
				}
				else {
					std::string getname = Name;
					std::string send = getname + " is not valid or offline.";
					IPlayer.BoxMsg(send);
				}

				return;
			}

			if (Itemx.CheckIndex() == 1473)
			{
				if (IPlayer.IsValid() && IPlayer.IsParty())
				{
					IPlayer.SystemMessage("Recall scroll used.", TEXTCOLOR_GREEN);
					IPlayer.Buff(304, BuffNames::BuffTime, 0);

					if (IPlayer.RemoveItem(1473, 1))
					{
						int Party = CParty::FindParty(IPlayer.GetPartyID());
						if (Party) {
							for (int i = CParty::GetPlayerList((void*)Party); i; i = CBaseList::Pop((void *)i))
							{
								IChar Member((void*)*(DWORD*)((void*)i));

								if (Member.IsValid() && IPlayer.IsValid() && Member.GetOffset() != IPlayer.GetOffset())
								{
									std::string getname = IPlayer.GetName();
									std::string send = getname + " will recall you to him(her). Do you accept the recall?";
									CPlayer::Write(Member.GetOffset(), 0xFF, "ddsss", 228, 1000, send.c_str(), IPlayer.GetName(), Member.GetName());
								}
							}
							CIOObject::Release((void*)Party);
						}
					}
				}
				else {
					IPlayer.BoxMsg("You are not in party.");
				}

				return;
			}

			if (Itemx.CheckIndex() == 1474)
			{
				if (IPlayer.IsValid() && IPlayer.GetGID())
				{
					IPlayer.SystemMessage("Recall scroll used.", TEXTCOLOR_GREEN);
					IPlayer.Buff(304, BuffNames::BuffTime, 0);

					if (IPlayer.RemoveItem(1474, 1))
					{
						CIOCriticalSection::Enter((void*)0x004e2078);
						CIOCriticalSection::Enter((void*)0x004e2098);
						CLink::MoveTo((void*)0x004e200c, (int)0x004e2004);
						CIOCriticalSection::Leave((void*)0x004e2098);
						for (DWORD i = *(DWORD*)0x004E2004; i != 0x004E2004; i = *(DWORD*)i)
						{
							if ((void*)(i - 428))
							{
								IChar Check((void*)(i - 428));

								if (Check.IsValid() && Check.GetGID() && Check.GetGID() == IPlayer.GetGID() && Check.GetOffset() != IPlayer.GetOffset())
								{
									std::string getname = IPlayer.GetName();
									std::string send = getname + " will recall you to him(her). Do you accept the recall?";
									CPlayer::Write(Check.GetOffset(), 0xFF, "ddsss", 228, 1000, send.c_str(), IPlayer.GetName(), Check.GetName());
								}
							}
						}

						CIOCriticalSection::Leave((void*)0x004e2078);
					}
				}
				else {
					IPlayer.BoxMsg("You do not have a guild.");
				}

				return;
			}

			return;
		}

		if (packet == 128)
		{
			int a1 = 0, a2 = 0, a3 = 0;
			int Check = CPacket::Read((char*)pPacket, (char*)pPos, "b", &a1);

			switch (a1) {
			case 1: {
						//register
						if (TriangularBattle::Active) {
							CPlayer::Write((void*)Player, 0xFE, "db", 172, 30);
							return;
						}

						if (TriangularBattle::CooldownTime >= (int)time(0)) {
							CPlayer::Write((void*)Player, 0xFE, "db", 172, 3);
							return;
						}

						if (TBRegistration.count(IPlayer.GetPID())) {
							CPlayer::Write((void*)Player, 0xFE, "db", 172, 2);
							return;
						}
						if (TBRegistration.size() > TBPlayersMax) {
							CPlayer::Write((void*)Player, 0xFE, "db", 172, 4);
							return;
						}

						if (IPlayer.GetLevel() < TBMin || IPlayer.GetLevel() > TBMax) {
							IPlayer.BoxMsg("The registration for Triangular Battle can only be done for players between level " + Int2String(TBMin) + " and " + Int2String(TBMax) + ".");
							return;
						}

						TBRegistration.insert(IPlayer.GetPID());
						CPlayer::Write((void*)Player, 0xFE, "db", 172, 1);
						break;
			}
			case 2: {
						//participants
						CPlayer::Write((void*)Player, 0xFE, "dbd", 171, 1, TBRegistration.size());
						break;
			}
			case 3: {
						// go to battle
						if (!TBRegistration.count(IPlayer.GetPID())) {
							CPlayer::Write((void*)Player, 0xFE, "db", 172, 6);
							return;
						}
						if (TriangularBattle::CooldownTime <= (int)time(0)) {
							CPlayer::Write((void*)Player, 0xFE, "db", 172, 7);
							return;
						}
						if (TBRegistration.size() < TBPlayersMin) {
							CPlayer::Write((void*)Player, 0xFE, "db", 172, 8);
							return;
						}

						if (IPlayer.GetMap() != TBMap) {
							PortTBPlayer(IPlayer, IPlayer.GetBuffValue(BuffNames::TriangularType));
							CChar::WriteInSight(IPlayer.GetOffset(), 145, "dI", IPlayer.GetID(), __int64(IPlayer.GetBuffValue(BuffNames::TriangularState)));
						}

						break;
			}

			case 4: {
						CPacket::Read((char*)Check, (char*)pPos, "bb", &a2, &a3);
						if (a2 >= 1 && a2 <= 3) {
							int Scores[3] = { TriangularBattle::HumanScore, TriangularBattle::DoggebiScore, TriangularBattle::DemonScore };
							int Pulling[3] = { TriangularBattle::HumanPulling, TriangularBattle::DoggebiPulling, TriangularBattle::DemonPulling };
							int Setting[3] = { TriangularBattle::HumanSetting, TriangularBattle::DoggebiSetting, TriangularBattle::DemonSetting };

							if (!IPlayer.GetBuffValue(BuffNames::TriangularTime)) {
								int TriangularType = IPlayer.GetBuffValue(BuffNames::TriangularType);
								if (TriangularType && TriangularType != a2) {
									if (Scores[a2 - 1]) {
										if (!Pulling[a2 - 1]) {
											if (!Setting[a2 - 1]) {
												if (GetInventorySize((int)IPlayer.GetOffset(), 0) < 60) {
													int NewValue = IPlayer.GetBuffValue(BuffNames::TriangularState) + 0x2000000;
													IPlayer.UpdateBuff(BuffNames::TriangularState, BuffNames::BuffTime, NewValue);
													CChar::WriteInSight((void*)Player, 145, "dI", IPlayer.GetID(), __int64(NewValue));
													CPlayer::Write((void*)Player, 0xFE, "dbb", 171, 10, EmblemPull);
													IPlayer.Buff(BuffNames::TriangularEmblemPull, EmblemPull + 3, a2);
													if (a2 == 1)
														TriangularBattle::HumanPulling = Player;
													if (a2 == 2)
														TriangularBattle::DoggebiPulling = Player;
													if (a2 == 3)
														TriangularBattle::DemonPulling = Player;
												}
												else
													CPlayer::Write((void*)Player, 0xFE, "db", 171, 16);
											}
											else
												CPlayer::Write((void*)Player, 0xFE, "db", 171, 5);
										}
										else
											CPlayer::Write((void*)Player, 0xFE, "db", 171, 14);
									}
									else
										CPlayer::Write((void*)Player, 0xFE, "db", 171, 13);
								}
							}
						}
						break;
			}
			case 5: {
						CPacket::Read((char*)Check, (char*)pPos, "bb", &a2, &a3);
						if (a2 >= 1 && a2 <= 3) {
							int TriangularType = IPlayer.GetBuffValue(BuffNames::TriangularType);
							if (TriangularType) {
								if (a2 == TriangularType) {
									if ((a2 == 1 && TriangularBattle::HumanPulling) || (a2 == 2 && TriangularBattle::DoggebiPulling) || (a2 == 3 && TriangularBattle::DemonPulling))
										CPlayer::Write((void*)Player, 0xFE, "db", 171, 14);
									else
									if ((a2 == 1 && TriangularBattle::HumanSetting) || (a2 == 2 && TriangularBattle::DoggebiSetting) || (a2 == 3 && TriangularBattle::DemonSetting))
										CPlayer::Write((void*)Player, 0xFE, "db", 171, 5);
									else {
										if (IPlayer.GetBuffValue(BuffNames::TriangularTime) && CPlayer::FindItem((void*)Player, 1941, 1)) {
											int Value = IPlayer.GetBuffValue(BuffNames::TriangularState) + 0x1000000;
											CChar::WriteInSight((void*)Player, 145, "dI", IPlayer.GetID(), __int64(Value));
											IPlayer.UpdateBuff(BuffNames::TriangularState, BuffNames::BuffTime, Value);
											CPlayer::Write((void*)Player, 0xFE, "dbb", 171, 2, EmblemSet);
											IPlayer.Buff(BuffNames::TriangularEmblemSet, EmblemSet + 3, a2);
											if (a2 == 1)
												TriangularBattle::HumanSetting = (int)Player;
											if (a2 == 2)
												TriangularBattle::DoggebiSetting = (int)Player;
											if (a2 == 3)
												TriangularBattle::DemonSetting = (int)Player;
										}
										else
											CPlayer::Write((void*)Player, 0xFE, "db", 171, 8);
									}
								}
							}
						}
						break;
			}
			case 6: case 7: {
						ClearTBPlayer(IPlayer);
						break;
			}
			case 8: {
						//leave
						QuitTBPlayer(IPlayer);
						IPlayer.RemoveSavedBuff(BuffNames::TriangularType);
						IPlayer.RemoveSavedBuff(BuffNames::TriangularState);
						IPlayer.BoxMsg("You have left The Triangular Battle.");
						CPlayer::Write(IPlayer.GetOffset(), 0xFE, "db", 172, 18);
			}
			}

			return;
		}

		if (packet == 129)
		{
			int a1 = 0, a2 = 0;
			int Check = CPacket::Read((char*)pPacket, (char*)pPos, "db", &a1, &a2);

			int GID = IPlayer.GetGID();
			switch (a2) {
				//Register member
			case 1: {
						if (!GID) {
							IPlayer.BoxMsg("Only members of a guild can access to that part of the system.");
							return;
						}

						if (IPlayer.GetPID() != GID) {
							CPlayer::Write((void*)Player, 0xFE, "dbb", 168, 1, 1);
							return;
						}

						if (IPlayer.GetLevel() < 50) {
							CPlayer::Write((void*)Player, 0xFE, "dbb", 168, 1, 3);
							return;
						}

						if (SufferingValleyRegistration.count(GID)) {
							CPlayer::Write((void*)Player, 0xFE, "dbb", 168, 1, 5);
							return;
						}

						if (!CPlayer::RemoveItem((void*)Player, 9, 31, 30000)) {
							CPlayer::Write((void*)Player, 0xFE, "dbb", 168, 1, 6);
							return;
						}
						std::string GuildName = (char*)CPlayer::GetGuildName(Player);
						SufferingValleyRegistration.replaceInsert(GID, GuildName);

						std::string Datko = "./Database/SufferingValley.db";
						std::fstream DGkLOG;
						DGkLOG.open(Datko, std::fstream::in | std::fstream::out | std::fstream::app);
						DGkLOG << "(registration (GID " << GID << ")(name '" << GuildName << "'))" << std::endl;
						DGkLOG.close();

						CPlayer::Write((void*)Player, 0xFE, "dbb", 168, 1, 0);
						break;
			}

			case 2: {
						int Size = SufferingValleyRegistration.size();
						char* PlayerPack = new char[Size * 32];
						int Packetsize = 0;
						Interface<ITools> Tools;
						for (auto x = SufferingValleyRegistration.begin(); x != SufferingValleyRegistration.end(); x++) {
							std::string name = x->second;
							Tools->Compile(PlayerPack + Packetsize, "s", name.c_str());
							Packetsize += name.length() + 1;
						}
						CPlayer::Write((void*)Player, 0xFE, "dbbm", 168, 2, Size, PlayerPack, Size * 32);

						delete[] PlayerPack;
						break;
			}

			case 3: {
						if (!GID) {
							IPlayer.BoxMsg("Only members of a guild can access to that part of the system.");
							return;
						}

						if (IPlayer.GetPID() != GID) {
							CPlayer::Write((void*)Player, 0xFE, "dbb", 168, 5, 3);
							return;
						}
						if (SufferingValley::Active) {
							CPlayer::Write((void*)Player, 0xFE, "dbb", 168, 5, 1);
							return;
						}

						if (GID != SufferingValley::GuildFirst && GID != SufferingValley::GuildSecond) {
							CPlayer::Write((void*)Player, 0xFE, "dbb", 168, 5, 2);
							return;
						}

						char* PlayerPack = new char[7000];
						int Packetsize = 0;
						Interface<ITools> Tools;
						int Amount = 0;

						int Guild = CPlayer::GetGuild(Player);

						if (Guild)
						{
							int v3; // eax@2
							int v6; // [sp+4h] [bp-10h]@2
							int v7; // [sp+8h] [bp-Ch]@6
							DWORD *v8; // [sp+Ch] [bp-8h]@3
							int v9; // [sp+10h] [bp-4h]@1

							CGuild::CriticalSectionEnter((volatile LONG*)0x004E0980);

							Unnamed::nGetObject((Guild + 380), (int)&v9);
							while (1)
							{
								v3 = Undefined::Check((int)((int)Guild + 380), (int)&v6);
								if (!(unsigned __int8)Undefined::CheckValues(&v9, v3))
									break;
								v8 = *(DWORD **)(*(DWORD *)(Undefined::GetValue(&v9) + 4) + 32);
								if (v8) {
									IChar ITarget((void*)v8);
									Tools->Compile(PlayerPack + Packetsize, "dddsb", ITarget.GetPID(), (ITarget.GetClass() << 16) | ITarget.GetSpecialty(), ITarget.GetLevel(), ITarget.GetName(), (SVParticipantsRed.count(ITarget.GetPID()) || SVParticipantsBlue.count(ITarget.GetPID())) ? 1 : 0);
									Packetsize += 13 + strlen(ITarget.GetName()) + 1;
									Amount++;
								}
								Undefined::sub_446090(&v9, (char*)&v7, 0);
							}

							CGuild::CriticalSectionLeave((volatile LONG*)0x004E0980);
							CSkill::ObjectRelease((void*)Guild, (LONG)(Guild + 40));
						}

						CPlayer::Write((void*)Player, 0xFE, "dbbm", 168, 4, Amount, PlayerPack, Packetsize);
						delete[] PlayerPack;
						break;
			}

			case 4: {
						int a3 = 0;
						Check = CPacket::Read((char*)Check, (char*)pPos, "b", &a3);
						if (a3) {
							SVParticipant leader = SVParticipant();
							leader.Name = IPlayer.GetName();
							leader.Level = IPlayer.GetLevel();
							leader.Specialty = (IPlayer.GetClass() << 16) | IPlayer.GetSpecialty();

							if (GID == SufferingValley::GuildFirst) {
								SVParticipantsRed.clear();
								SVParticipantsRed.replaceInsert(IPlayer.GetPID(), leader);
							}
							else
							if (GID == SufferingValley::GuildSecond) {
								SVParticipantsBlue.clear();
								SVParticipantsBlue.replaceInsert(IPlayer.GetPID(), leader);
							}
						}

						for (int i = 0; i < a3; i++) {
							int PID = 0;
							Check = CPacket::Read((char*)Check, (char*)pPos, "d", &PID);
							if (PID) {
								TargetFind myTarget(0, 1, PID);
								void *GetPlayer = myTarget.getTarget();

								if (GetPlayer)
								{
									IChar IParticipant(GetPlayer);

									if (IParticipant.IsOnline())
									{
										SVParticipant participant = SVParticipant();
										participant.Name = IParticipant.GetName();
										participant.Level = IParticipant.GetLevel();
										participant.Specialty = (IParticipant.GetClass() << 16) | IParticipant.GetSpecialty();

										if (GID == SufferingValley::GuildFirst)
											SVParticipantsRed.replaceInsert(PID, participant);
										else
										if (GID == SufferingValley::GuildSecond)
											SVParticipantsBlue.replaceInsert(PID, participant);

										IParticipant.SystemMessage("You have been registered by your guild leader to play on Suffering Valley.", TEXTCOLOR_GREEN);
									}
								}
							}
						}
						break;
			}
				//participant lists
			case 5: {
						char* PlayerPack = new char[7000];
						int Packetsize = 0;
						Interface<ITools> Tools;
						int amount = 0;
						for (auto x = SVParticipantsRed.begin(); x != SVParticipantsRed.end(); x++) {
							std::string name = x->second.Name;
							Tools->Compile(PlayerPack + Packetsize, "ddds", x->first, x->second.Specialty, x->second.Level, name.c_str());
							Packetsize += 12 + name.length() + 1;
							amount++;
						}

						for (auto x = SVParticipantsBlue.begin(); x != SVParticipantsBlue.end(); x++) {
							std::string name = x->second.Name;
							Tools->Compile(PlayerPack + Packetsize, "ddds", x->first, x->second.Specialty, x->second.Level, name.c_str());
							Packetsize += 12 + name.length() + 1;
							amount++;
						}

						CPlayer::Write((void*)Player, 0xFE, "dbbm", 168, 6, amount, PlayerPack, Packetsize);
						delete[] PlayerPack;
						break;
			}
			}
			return;
		}

		if (packet == C2S_SendMsg)
		{
			char *msg;
			CPacket::Read((char*)pPacket, (char*)pPos, "s", &msg, 129);

			if (!msg || !strlen(msg))
				return;

			char firstLetter = *msg;

			std::string chat(msg);

			if (FilterCheck == 1) {
				for each(std::string word in Filter) {
					if (stristr(msg, word.c_str()))
						return;
				}
			}

			if (firstLetter == '%' && (TriangularBattle::Active || TriangularBattle::CDActive)) {
				int Team = IPlayer.GetBuffValue(BuffNames::TriangularType);
				if (Team) {
					int MsgPacket = CObject::WriteExclusive(60, "ss", IPlayer.GetName(), msg);

					CIOCriticalSection::Enter((void*)0x004e2078);
					CIOCriticalSection::Enter((void*)0x004e2098);
					CLink::MoveTo((void*)0x004e200c, (int)0x004e2004);
					CIOCriticalSection::Leave((void*)0x004e2098);
					for (DWORD a = *(DWORD*)0x004E2004; a != 0x004E2004; a = *(DWORD*)a)
					{
						if ((void*)(a - 428))
						{
							IChar XPlayer((void*)(a - 428));
							if (XPlayer.GetBuffValue(BuffNames::TriangularType) == Team)
								CPlayer::Send((int)XPlayer.GetOffset(), MsgPacket);
						}
					}
					CIOCriticalSection::Leave((void*)0x004e2078);

					CIOBuffer::Release((void*)MsgPacket);
				}
				return;
			}

			if (firstLetter == '@') {
				std::string charname = chat.substr(0, chat.find(" "));
				if (!charname.empty()) {
					charname.erase(0, 1);

					if (!DisablePM.empty() && DisablePM.count(charname)) {
						IPlayer.SystemMessage(charname + "'s Private Messages are turned off.", TEXTCOLOR_YELLOW);
						return;
					}

					if (IPlayer.GetMap() == TBMap) {
						TargetFind myTarget(charname.c_str());
						IChar ITarget((void*)myTarget.getTarget());
						if (IPlayer.GetBuffValue(BuffNames::TriangularType) != ITarget.GetBuffValue(BuffNames::TriangularType)) {
							CPlayer::Write((void*)Player, 0xFE, "db", 172, 20);
							return;
						}
					}

					if (EFakePlayers) {
						if (FakeNames.count(charname) && (EFakePlayers*-1) <= FakeNames.findValue(charname)) {
							CPlayer::Write((void*)Player, 60, "ss", IPlayer.GetName(), msg);
							return;
						}
					}
				}
			}

			if (IPlayer.IsBuff(BuffNames::Mute)){
				IPlayer.BoxMsg("You are muted. You can talk again in " + Int2String((*(DWORD *)((int)IPlayer.GetOffset() + 1460) - GetTickCount()) / 1000) + " seconds.");
				return;
			}

			if (chatDebug == 1) {
				std::string Datoe = "./Debugger/Chat/CHAT_" + Time::GetDay() + "_" + Time::GetMonth() + "_" + Time::GetYear() + "_" + Time::GetHour() + "." + Time::GetMinute() + ".txt";
				std::fstream CHLOG;
				CHLOG.open(Datoe, std::fstream::in | std::fstream::out | std::fstream::app);
				CHLOG << Time::GetTime() << " " << IPlayer.GetName() << ": " << chat << std::endl;
				CHLOG.close();
			}
		}

		if (packet == 34 || packet == 44 || packet == 80 || packet == 85 || packet == C2S_AddFriend)
		{
			if (IPlayer.IsBuff(285))
				return;
			else
				IPlayer.Buff(285, 2, 0);
		}

		if (packet == 173)
			return;

		if (packet == 37 && IPlayer.IsBuff(BuffNames::LMS))
			return;

		if (packet == 37 && (IPlayer.IsBuff(160) || IPlayer.IsBuff(161)))
			return;

		if (packet == 37 && (IPlayer.IsBuff(162) || IPlayer.IsBuff(163)))
			return;

		if (packet == 37 && IPlayer.IsBuff(166))
			return;

		if (packet == 37 && (IPlayer.IsBuff(373) || IPlayer.IsBuff(374)))
			return;

		if (packet == 37 && (IPlayer.IsBuff(902) || IPlayer.IsBuff(903) || IPlayer.IsBuff(BuffNames::PTVsPTBlue) || IPlayer.IsBuff(BuffNames::PTVsPTRed)))
			return;

		if (packet == 37 && (IPlayer.IsBuff(170) || IPlayer.IsBuff(171)))
			return;

		if (packet == 26)
		{
			int IID = 0, Amount = 0, Value = 0, Item = 0, Recheck = 0, Check = 0;
			CPacket::Read((char*)pPacket, (char*)pPos, "dd", &IID, &Amount);

			if (Amount > 0 && IID)
			{
				if (IPlayer.GetMap() == TBMap) {
					CPlayer::Write((void*)Player, 0xFE, "db", 172, 25);
					return;
				}

				if (strlen(PlayerCheck) && ((std::string)PlayerCheck == "disable" || (std::string)PlayerCheck == "Disable"))
					return;

				if (Restrictions.count(IPlayer.GetPID()) && Restrictions.find(IPlayer.GetPID())->second.Drop == 0) {
					IPlayer.SystemMessage("You are not allowed to be using this system.", TEXTCOLOR_RED);
					return;
				}

				if (IPlayer.IsBuff(BuffNames::Jail)) {
					IPlayer.SystemMessage("You can not drop in jail.", TEXTCOLOR_RED);
					return;
				}

				if (PetLifeCheck.count(IID)) {
					IPlayer.SystemMessage("Timed Items can not be dropped.", TEXTCOLOR_RED);
					return;
				}

				if (IPlayer.IsBuff(372))
					return;
				else
					IPlayer.Buff(372, 2, 0);

				int Item = IPlayer.ItemPointerLock(IID);

				if (Item && IID)
				{
					IItem Itemx((void*)Item);

					if (Itemx.GetInfo() & 4194304)
						return;
				}
			}
		}

		if (packet == 109)
		{
			const char *Password, *Question, *Answer;
			int LockIID = 0, IID = 0, LockValue = 0, Value = 0, Recheckx = 0, Checkx = 0;
			CPacket::xRead((char*)pPacket, "ddsss", &LockIID, &IID, &Password, &Question, &Answer);
			if (IID == LockIID) return;

			if (!Password || !Question || !Answer || !strlen(Password) || !strlen(Question) || !strlen(Answer))
				return;

			int LockItem = IPlayer.ItemPointerLock(LockIID);

			if (!LockItem)
				return;

			IItem ItemLock((void*)LockItem);
			int Itemx = IPlayer.ItemPointerLock(IID);

			if (!Itemx)
				return;

			IItem xItem((void*)Itemx);

			if (ItemLock.Exists() && ItemLock.CheckIndex() == 1181)
			{
				IPlayer.RemoveItem((int)ItemLock.GetOffset());
				//CItem::RemoveItem((void*)Player, (int)ItemLock.GetOffset());
			}
			else {
				return;
			}

			if (xItem.GetInfo() & 4194304)
				return;

			if (xItem.Exists())
			{
				int CurrentInfo = *(DWORD *)(Itemx + 48) + 4194304;
				CDBSocket::Write(21, "dddbb", xItem.GetIID(), IPlayer.GetID(), xItem.GetInfo(), 0, 0);
				*(DWORD *)(Itemx + 48) = CurrentInfo;
				CDBSocket::Write(21, "dddbb", xItem.GetIID(), *(DWORD*)(Itemx + 28), CurrentInfo, 8, 7);
				CItem::SendItemInfo((void *)Itemx, (int)IPlayer.GetOffset(), 92);
				IPlayer.BoxMsg("You have successfully locked your item.");
				CDBSocket::Write(88, "dsd", IPlayer.GetPID(), Password, xItem.GetIID());
				itemLockLock.Enter();
				ItemLockCheck[xItem.GetIID()] = Password;
				itemLockLock.Leave();
			}
			else {
				return;
			}

			return;
		}

		if (packet == 110)
		{
			const char *Password;
			int KeyIID = 0, IID = 0, KeyValue = 0, Value = 0, Recheckx = 0, Checkx = 0;
			CPacket::Read((char*)pPacket, (char*)pPos, "dds", &KeyIID, &IID, &Password, 13);

			if (IID == KeyIID) return;

			if (!Password || !strlen(Password))
				return;


			int KeyItem = IPlayer.ItemPointerLock(KeyIID);

			if (!KeyItem)
				return;

			IItem KeyLock((void*)KeyItem);
			int Itemx = IPlayer.ItemPointerLock(IID);

			if (!Itemx)
				return;
			IItem xItem((void*)Itemx);

			if (KeyLock.Exists() && KeyLock.CheckIndex() == 1182)
			{
				IPlayer.RemoveItem((int)KeyLock.GetOffset());
				//CItem::RemoveItem((void*)Player, (int)KeyLock.GetOffset());
			}
			else {
				return;
			}

			if (xItem.CheckIndex() && (xItem.GetInfo() & 4194304))
			{
				itemLockLock.Enter();
				std::string pwd = ItemLockCheck.count(IID) ? ItemLockCheck.find(IID)->second : "";
				itemLockLock.Leave();
				if (Password != pwd)
				{
					IPlayer.BoxMsg("You typed wrong password. A Key is consumed.");
					return;
				}

				int CurrentInfo = *(DWORD *)(Itemx + 48) - 4194304;
				CDBSocket::Write(21, "dddbb", xItem.GetIID(), IPlayer.GetID(), xItem.GetInfo(), 0, 0);
				*(DWORD *)(Itemx + 48) = CurrentInfo;
				CDBSocket::Write(21, "dddbb", xItem.GetIID(), *(DWORD*)(Itemx + 28), CurrentInfo, 8, 7);
				CItem::SendItemInfo((void *)Itemx, (int)IPlayer.GetOffset(), 92);
				IPlayer.BoxMsg("You completely unlocked your item. A Key is consumed.");
				CDBSocket::Write(88, "dsd", IPlayer.GetPID(), "nopwd", xItem.GetIID());
				itemLockLock.Enter();
				ItemLockCheck.erase(xItem.GetIID());
				itemLockLock.Leave();
			}
			else {
				return;
			}

			return;
		}

		if (packet == 111)
		{
			const char *Password, *Question, *Answer;
			int LockIID = 0, IID = 0, LockValue = 0, Value = 0, Recheckx = 0, Checkx = 0;
			CPacket::Read((char*)pPacket, (char*)pPos, "ddsss", &LockIID, &IID, &Password, 13, &Question, 17, &Answer, 133);
			if (IID == LockIID) return;

			if (!Password || !Question || !Answer || !strlen(Password) || !strlen(Question) || !strlen(Answer))
				return;

			int LockItem = IPlayer.ItemPointerLock(LockIID);

			if (!LockItem)
				return;

			IItem ItemLock((void*)LockItem);
			int Itemx = IPlayer.ItemPointerLock(IID);

			if (!Itemx)
				return;

			IItem xItem((void*)Itemx);

			if (ItemLock.Exists() && ItemLock.CheckIndex() == 1181)
			{
				IPlayer.RemoveItem((int)ItemLock.GetOffset());
				//CItem::RemoveItem((void*)Player, (int)ItemLock.GetOffset());
			}
			else {
				return;
			}

			if (xItem.GetInfo() & 4194304)
				return;

			if (xItem.Exists())
			{
				int CurrentInfo = *(DWORD *)(Itemx + 48) + 4194304;
				CDBSocket::Write(21, "dddbb", xItem.GetIID(), IPlayer.GetID(), xItem.GetInfo(), 0, 0);
				*(DWORD *)(Itemx + 48) = CurrentInfo;
				CDBSocket::Write(21, "dddbb", xItem.GetIID(), *(DWORD*)(Itemx + 28), CurrentInfo, 8, 7);
				CItem::SendItemInfo((void *)Itemx, (int)IPlayer.GetOffset(), 92);
				IPlayer.BoxMsg("You have successfully locked your item.");
				CDBSocket::Write(88, "dsd", IPlayer.GetPID(), Password, xItem.GetIID());
				itemLockLock.Enter();
				ItemLockCheck[xItem.GetIID()] = Password;
				itemLockLock.Leave();
			}
			else {
				return;
			}

			return;
		}

		if (packet == 75 && IPlayer.GetClass() == 3)
		{
			int SkillID = 0;
			CPacket::Read((char*)pPacket, (char*)pPos, "b", &SkillID);
			int SkillPointer = IPlayer.GetSkillPointer(SkillID);

			if (SkillPointer && SkillID < 90 && SkillID != 79 && SkillID != 37 && SkillID != 50 && SkillID != 70 && SkillID != 87 && SkillID != 88 && SkillID != 89 && (CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 362, 1) || CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 502, 1)))
			{
				if (IPlayer.IsOnline() && IPlayer.GetClass() == 3 && SkillID == 4)
				{
					IPlayer.DecreaseCritRate(*(DWORD*)(SkillPointer + 8));
					IPlayer.DecreaseCritDamage(*(DWORD*)(SkillPointer + 8));
				}

				if (IPlayer.IsOnline() && IPlayer.GetClass() == 3 && SkillID == 5)
				{
					IPlayer.DecreaseCritRate(*(DWORD*)(SkillPointer + 8));
					IPlayer.DecreaseCritDamage(*(DWORD*)(SkillPointer + 8));
				}

				IPlayer.AddSkillPoint(*(DWORD*)(SkillPointer + 8));
				*(DWORD*)(SkillPointer + 8) = 0;
				CPlayer::Write(IPlayer.GetOffset(), 11, "bb", *(DWORD*)(SkillPointer + 4), 0);
				CDBSocket::Write(22, "dbbw", IPlayer.GetPID(), *(DWORD*)(SkillPointer + 4), *(DWORD*)(SkillPointer + 8), *(DWORD*)((int)IPlayer.GetOffset() + 548));
				*(DWORD*)((int)IPlayer.GetOffset() + 4 * *(DWORD*)(SkillPointer + 4) + 632) = 0;
			}
			else {
				return;
			}
		}

		if (packet == 96)
		{
			void *xpPacket = pPacket;
			int xpPos = pPos, Npc = 0, Amount = 0, Index = 0, Item = 0, ValidItem = 0;
			unsigned __int16 ItemIndex = 0, ItemAmount = 0;
			unsigned __int8 Tax = 0, Size = 0;
			int NewpPacket = CPacket::Read((char*)xpPacket, (char*)xpPos, "dbb", &Npc, &Tax, &Size);

			if (Size > 0 && Size < 100)
			{
				for (int i = 0; *((DWORD*)Player + 274) && i < Size; i++)
				{
					NewpPacket = CPacket::Read((char*)NewpPacket, (char*)xpPos, (const char*)0x004BADB4, &ItemIndex, &ItemAmount);
					Amount = ItemAmount; Index = ItemIndex;

					if (Amount > 0 && HonorIndex.count(ItemIndex) && HonorIndex.find(ItemIndex)->second)
					{
						int TotalHonorRemove = Amount * HonorIndex.find(ItemIndex)->second;

						if (TotalHonorRemove > IPlayer.GetProperty(PlayerProperty::RPx))
						{
							IPlayer.SystemMessage("You do not have enough reward points.", TEXTCOLOR_RED);
							return;
						}
						else {
							if (CPlayer::GetInvenSize(Player) >= IPlayer.MaxInventorySize())
							{
								IPlayer.SystemMessage("There is no free space on the storage.", TEXTCOLOR_RED);
								return;
							}
							else {

								int FItem = CPlayer::FindItem((void*)Player, ItemIndex, 1);
								if (FItem && (*(int(__thiscall **)(int, int))(*(DWORD *)FItem + 148))(FItem, FItem)) {
									(*(int(__thiscall **)(DWORD, void *, signed int, signed int))(*(DWORD*)FItem + 120))(FItem, (void*)Player, 9, ItemAmount);
									IPlayer.SetHonor(0, -TotalHonorRemove, 0, 0, 0, 0, 0, 0, 0, 0);
								}
								else {
									Item = CItem::CreateItem(ItemIndex, 0, ItemAmount, -1);

									if (Item)
									{
										IItem IItem((void*)Item);
										ValidItem = CPlayer::InsertItem(IPlayer.GetOffset(), 7, Item);

										if (ValidItem == 1)
										{
											IPlayer.SetHonor(0, -TotalHonorRemove, 0, 0, 0, 0, 0, 0, 0, 0);
											//*(DWORD*)(Item + 48) = 128; (u can change if u wanna keep it bound)
											CDBSocket::Write(21, "dddbb", IItem.GetIID(), *(DWORD*)(Item + 28), 128, 8, 7);
											CItem::SendItemInfo((void *)Item, (int)IPlayer.GetOffset(), 92);
										}
										else
											CBase::Delete((void*)ValidItem);
									}
								}
								return;
							}
						}
					}
				}
			}
		}

		if (packet == C2S_UseItem)
		{
			int IID = 0;
			CPacket::Read((char*)pPacket, (char*)pPos, "d", &IID);

			int Item = IPlayer.ItemPointerLock(IID);

			if (Item && IID)
			{
				IItem Itemx((void*)Item);

				if (OBActive && CItem::IsState(Item, 1) && Itemx.CheckIndex() == IPlayer.GetBuffValue(BuffNames::Belt)) {
					if (!IPlayer.IsBuff(BuffNames::BeltBuff)) {
						int BeltB = IPlayer.GetBuffRemain(BuffNames::BeltCD);
						if (!BeltB && !IPlayer.IsBuff(BuffNames::BeltCD)) {
							if (BeltBuffs.count(Itemx.CheckIndex())) {
								BeltBuff belt = BeltBuffs.find(Itemx.CheckIndex())->second;
								IPlayer.Buff(BuffNames::BeltBuff, belt.Duration + 2, belt.HP);
								IPlayer.SaveBuff(BuffNames::BeltCD, belt.Duration + 2 + belt.Cooldown);
								IPlayer.IncreaseMaxHp(belt.HP);
								IPlayer.IncreaseHp(belt.HP);
								IPlayer.AddFxToBone(belt.Effect, 0);
							}
						}
						else
							IPlayer.SystemMessage("You still have " + Int2String(BeltB) + " seconds before being able to use the buff again.", TEXTCOLOR_RED);
					}
					return;
				}

				if (Itemx.CheckIndex() == 1620)
				{
					if (IPlayer.GetLevel() < VODConf)
					{
						IPlayer.SystemMessage("Your character must be level " + Int2String(VODConf) + " or above.", TEXTCOLOR_RED);
						return;
					}

					if ((IPlayer.IsBuff(160) || IPlayer.IsBuff(180) || IPlayer.IsBuff(179) || IPlayer.IsBuff(161) || IPlayer.IsBuff(BuffNames::PTVsPTBlue) || IPlayer.IsBuff(BuffNames::PTVsPTRed) || IPlayer.IsBuff(162) || IPlayer.IsBuff(163) || IPlayer.IsBuff(170) || IPlayer.IsBuff(171) || IPlayer.IsBuff(373) || IPlayer.IsBuff(374) || IPlayer.IsBuff(902) || IPlayer.IsBuff(903) || IPlayer.IsBuff(BuffNames::LMS) || IPlayer.GetMap() == SVMap))
					{
						IPlayer.SystemMessage("You can not teleport while in battle.", TEXTCOLOR_RED);
						return;
					}

					if (IPlayer.IsValid())
						IPlayer.Teleport(6, 360931, 187024);
					else
						return;
					return;
				}
			}
		}

		if (packet == 63)
		{
			int IID = 0;
			CPacket::Read((char*)pPacket, (char*)pPos, "d", &IID);

			int Item = IPlayer.ItemPointerLock(IID);

			if (Item && IID)
			{
				IItem Itemx((void*)Item);

				if (Itemx.GetInfo() & 4194304)
					return;

				if (TriangularBattle::Active) {
					if (Itemx.CheckIndex() == 1941) {
						IPlayer.SystemMessage("Ancient essence can not be destroyed while Triangular Battle is active.", TEXTCOLOR_YELLOW);
						return;
					}
				}

			}
		}

		if (packet == 172)
		{
			int Str = 0, Hp = 0, Int = 0, Wis = 0, Agi = 0;
			int LeftPacket = CPacket::Read((char*)pPacket, (char*)pPos, "bbbbb", &Str, &Hp, &Int, &Wis, &Agi);
			int GetStr = IPlayer.GetStr(), GetHth = IPlayer.GetHth(), GetInt = IPlayer.GetInt(), GetWis = IPlayer.GetWis(), GetAgi = IPlayer.GetAgi();
			int NeedStatPoint = 0;

			if (Str)
			{
				if (IPlayer.GetStr() + Str >= 255)
				{
					IPlayer.SystemMessage("Base stats can not be higher then 255!", TEXTCOLOR_RED);
					return;
				}

				if (IPlayer.GetClass() == 0)
				{
					for (int i = 0; i < Str; i++)
					{
						NeedStatPoint += _StatTable[GetStr];
						GetStr++;
					}
				}
				else {
					for (int i = 0; i < Str; i++)
					{
						NeedStatPoint += StatTable[GetStr];
						GetStr++;
					}
				}
			}

			if (Hp)
			{
				if (IPlayer.GetHth() + Hp >= 255)
				{
					IPlayer.SystemMessage("Base stats can not be higher then 255!", TEXTCOLOR_RED);
					return;
				}

				for (int i = 0; i < Hp; i++)
				{
					NeedStatPoint += StatTable[GetHth];
					GetHth++;
				}
			}

			if (Int)
			{
				if (IPlayer.GetInt() + Int >= 255)
				{
					IPlayer.SystemMessage("Base stats can not be higher then 255!", TEXTCOLOR_RED);
					return;
				}

				if (IPlayer.GetClass() == 1)
				{
					for (int i = 0; i < Int; i++)
					{
						NeedStatPoint += _StatTable[GetInt];
						GetInt++;
					}
				}
				else {
					for (int i = 0; i < Int; i++)
					{
						NeedStatPoint += StatTable[GetInt];
						GetInt++;
					}
				}
			}

			if (Wis)
			{
				if (IPlayer.GetWis() + Wis >= 255)
				{
					IPlayer.SystemMessage("Base stats can not be higher then 255!", TEXTCOLOR_RED);
					return;
				}

				for (int i = 0; i < Wis; i++)
				{
					NeedStatPoint += StatTable[GetWis];
					GetWis++;
				}
			}

			if (Agi)
			{
				if (IPlayer.GetAgi() + Agi >= 255)
				{
					IPlayer.SystemMessage("Base stats can not be higher then 255!", TEXTCOLOR_RED);
					return;
				}

				if (IPlayer.GetClass() == 2 || IPlayer.GetClass() == 3)
				{
					for (int i = 0; i < Agi; i++)
					{
						NeedStatPoint += _StatTable[GetAgi];
						GetAgi++;
					}
				}
				else {
					for (int i = 0; i < Agi; i++)
					{
						NeedStatPoint += StatTable[GetAgi];
						GetAgi++;
					}
				}
			}

			if (IPlayer.GetStatPoint() < NeedStatPoint || IPlayer.GetStatPoint() <= 0 || NeedStatPoint == 0)
			{
				CPlayer::Write(IPlayer.GetOffset(), 68, "bb", 26, NeedStatPoint);
				return;
			}

			if (Str)
			{
				IPlayer.IncreaseStat(Str, 0);
				CDBSocket::Write(16, "dbwbb", IPlayer.GetPID(), 23, IPlayer.GetStatPoint(), 0, *(DWORD *)(Player + 4 * 0 + 64));
			}

			if (Hp)
			{
				IPlayer.IncreaseStat(Hp, 1);
				CDBSocket::Write(16, "dbwbb", IPlayer.GetPID(), 23, IPlayer.GetStatPoint(), 1, *(DWORD *)(Player + 4 * 1 + 64));

				if (IPlayer.GetClass() == 3)
				{
					int pSkill = *((DWORD*)((int)IPlayer.GetOffset() + 624) + 30 + 2);

					if (pSkill)
					{
						ISkill xSkill((void*)pSkill);
						IPlayer.IncreaseMaxHp((5 * xSkill.GetGrade()) * Hp);
					}
				}
			}

			if (Int)
			{
				IPlayer.IncreaseStat(Int, 2);
				CDBSocket::Write(16, "dbwbb", IPlayer.GetPID(), 23, IPlayer.GetStatPoint(), 2, *(DWORD *)(Player + 4 * 2 + 64));
			}

			if (Wis)
			{
				IPlayer.IncreaseStat(Wis, 3);
				CDBSocket::Write(16, "dbwbb", IPlayer.GetPID(), 23, IPlayer.GetStatPoint(), 3, *(DWORD *)(Player + 4 * 3 + 64));
			}

			if (Agi)
			{
				IPlayer.IncreaseStat(Agi, 4);
				CDBSocket::Write(16, "dbwbb", IPlayer.GetPID(), 23, IPlayer.GetStatPoint(), 4, *(DWORD *)(Player + 4 * 4 + 64));
			}

			if (NeedStatPoint)
				IPlayer.RemoveStatPoint(NeedStatPoint);

			return;
		}

		if (packet == 162)
		{
			int Type = 0, IID = 0, ItemIndex = 0, JewelCheck = 0, Argument = 0, JewelAmount = 0;
			Interface<ITools> Tools;
			CPacket::Read((char*)pPacket, (char*)pPos, "bddbwb", &Type, &IID, &ItemIndex, &JewelCheck, &Argument, &JewelAmount);
			//Tools->ParseData((char*)pPacket,"bddbwb",&Type, &IID, &ItemIndex, &JewelCheck, &Argument, &JewelAmount);
			//CPacket::xRead((char*)pPacket, "bddbwb", &Type, &IID, &ItemIndex, &JewelCheck, &Argument, &JewelAmount);
			if (Type == 1 && IID && ItemIndex)
			{
				CPlayer::Write(IPlayer.GetOffset(), 0xFF, "dd", 240, 1);
				return;
			}

			int item = IPlayer.ItemPointerLock(IID);

			if (ItemIndex < (-1 << 16))
				CPlayer::Write(IPlayer.GetOffset(), 0xFF, "ddd", 240, 1);

			if (!item)
				return;

			int SetType = 200, JewelCalculation = 0;
			IItem MainItem((void*)item);

			if (JewelCheck == 1 && JewelAmount >= 1 && JewelAmount <= 10)
			{
				int Multiply = 10;
				if (MainItem.GetType() >= 1 && MainItem.GetType() <= 6) Multiply = 5;

				if (IPlayer.RemoveItem(JewelIndex, (Multiply*JewelAmount)))
					JewelCalculation = JewelAmount;
				else {
					return;
				}
			}

			int Checkx = CPlayer::FindItem(IPlayer.Offset, 2365, 1);
			if (ItemIndex == 2365 && Checkx)
			{
				int Type = 0, DssRate = CTools::Rate(1, 1000);

				if (DssRate >= (550 - (JewelCalculation * 50)))
				{
					if (DssRate >= (750 - (JewelCalculation * 60)))
					{
						if (DssRate >= (850 - (JewelCalculation * 60)))
						{
							if (DssRate >= (950 - (JewelCalculation * 70)))
							{
								if (DssRate >= (970 - (JewelCalculation * 70)))
								{
									if (DssRate >= (980 - (JewelCalculation * 80)))
									{
										if (DssRate >= (990 - (JewelCalculation * 80)))
										{
											int Rate = CTools::Rate(36, 40);
											SetType += Rate;
											Type = 1;
											std::string msg = (std::string)IPlayer.GetName();
											msg = msg + " has been fused with the Spirit Of Insanity!";
											if (fuseNotice)
												CPlayer::WriteAll(0xFF, "dsd", 247, msg.c_str(), 8);
										}
										else {
											int Rate = CTools::Rate(31, 35);
											SetType += Rate;
											Type = 2;
											std::string msg = (std::string)IPlayer.GetName();
											msg = msg + " has been fused with the Spirit Of Thunder!";
											if (fuseNotice)
												CPlayer::WriteAll(0xFF, "dsd", 247, msg.c_str(), 8);
										}
									}
									else {
										int Rate = CTools::Rate(26, 30);
										SetType += Rate;
										Type = 3;
									}
								}
								else {
									int Rate = CTools::Rate(21, 25);
									SetType += Rate;
									Type = 4;
								}
							}
							else {
								int Rate = CTools::Rate(16, 20);
								SetType += Rate;
								Type = 5;
							}
						}
						else {
							int Rate = CTools::Rate(11, 15);
							SetType += Rate;
							Type = 6;
						}
					}
					else {
						int Rate = CTools::Rate(6, 10);
						SetType += Rate;
						Type = 7;
					}
				}
				else {
					int Rate = CTools::Rate(1, 5);
					SetType += Rate;
					Type = 8;
				}

				MainItem.SetSetGem(SetType);
				CDBSocket::Write(87, "ddd", IPlayer.GetPID(), SetType, MainItem.GetIID());
				CItem::SendItemInfo((void *)item, (int)IPlayer.GetOffset(), 92);
				if (!(*(int(__thiscall **)(DWORD, void *, signed int, signed int))(*(DWORD*)Checkx + 120))(Checkx, IPlayer.GetOffset(), 9, -1))
					CPlayer::_OutOfInven((void*)Player, Checkx);
				CPlayer::Write(IPlayer.GetOffset(), 0xFF, "ddb", 241, MainItem.GetIID(), Type);
				return;
			}

			if (ItemIndex == 2412 && CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 2412, 1))
			{
				int Type = 0, DssRate = CTools::Rate(1, 100);

				if (DssRate >= 100 - Insanity) {
					int Rate = CTools::Rate(36, 40);
					SetType += Rate;
					Type = 1;
					std::string msg = (std::string)IPlayer.GetName();
					msg = msg + " has been fused with the Spirit Of Insanity!";
					if (fuseNotice){
						CPlayer::WriteAll(0xFF, "dsd", 247, msg.c_str(), 8);
						ToNoticeWebhook(msg.c_str());

					}
				}
				else if (DssRate >= 100 - Thunder) {
					int Rate = CTools::Rate(31, 35);
					SetType += Rate;
					Type = 2;
					std::string msg = (std::string)IPlayer.GetName();
					msg = msg + " has been fused with the Spirit Of Thunder!";
					if (fuseNotice){
						CPlayer::WriteAll(0xFF, "dsd", 247, msg.c_str(), 8);
						ToNoticeWebhook(msg.c_str());

					}
				}
				else if (DssRate >= 100 - Violent) {
					int Rate = CTools::Rate(26, 30);
					SetType += Rate;
					Type = 3;
				}
				else if (DssRate >= 100 - Storm) {
					int Rate = CTools::Rate(21, 25);
					SetType += Rate;
					Type = 4;
				}
				else if (DssRate >= 100 - Ancient) {
					int Rate = CTools::Rate(16, 20);
					SetType += Rate;
					Type = 5;
				}
				else {
					int Rate = CTools::Rate(11, 15);
					SetType += Rate;
					Type = 6;
				}

				MainItem.SetSetGem(SetType);
				CDBSocket::Write(87, "ddd", IPlayer.GetPID(), SetType, MainItem.GetIID());
				CItem::SendItemInfo((void *)item, (int)IPlayer.GetOffset(), 92);
				CPlayer::Write(IPlayer.GetOffset(), 0xFF, "ddb", 241, MainItem.GetIID(), Type);
				return;
			}

			if (ItemIndex >= 4411 && ItemIndex <= 4414 && CPlayer::RemoveItem(IPlayer.GetOffset(), 9, ItemIndex, 1))
			{
				int Type = 4;
				int Rate = CTools::Rate(21, 25);

				if (ItemIndex == 4411) {
					Rate = CTools::Rate(36, 40);
					Type = 1;
					std::string msg = (std::string)IPlayer.GetName();
					msg = msg + " has been fused with the Spirit Of Insanity!";
					if (fuseNotice){
						CPlayer::WriteAll(0xFF, "dsd", 247, msg.c_str(), 8);
						ToNoticeWebhook(msg.c_str());

					}
				}
				else if (ItemIndex == 4412) {
					Rate = CTools::Rate(31, 35);
					Type = 2;
					std::string msg = (std::string)IPlayer.GetName();
					msg = msg + " has been fused with the Spirit Of Thunder!";
					if (fuseNotice){
						CPlayer::WriteAll(0xFF, "dsd", 247, msg.c_str(), 8);
						ToNoticeWebhook(msg.c_str());

					}
				}
				else if (ItemIndex == 4413) {
					Rate = CTools::Rate(26, 30);
					Type = 3;
				}

				SetType += Rate;
				MainItem.SetSetGem(SetType);
				CDBSocket::Write(87, "ddd", IPlayer.GetPID(), SetType, MainItem.GetIID());
				CItem::SendItemInfo((void *)item, (int)IPlayer.GetOffset(), 92);
				CPlayer::Write(IPlayer.GetOffset(), 0xFF, "ddb", 241, MainItem.GetIID(), Type);
				return;
			}
			return;
		}

		if (packet == 41)
		{
			int SkillID = 0;
			CPacket::Read((char*)pPacket, (char*)pPos, "b", &SkillID);
			SkillLearnPacket(IPlayer, SkillID);
			return;
		}

		if (packet == 42)
		{
			int SkillID = 0;
			CPacket::Read((char*)pPacket, (char*)pPos, "b", &SkillID);
			if (SkillID == 85) SkillID = 87;
			else if (SkillID == 86) SkillID = 88;
			else if (SkillID == 87) SkillID = 89;

			if (SkillID >= 90)
				return;

			if (SkillID == 79)
				return;

			if (IPlayer.GetLevel() >= 81 && SkillID >= 87 && SkillID <= 89)
				return;

			if (SkillChecks.count((IPlayer.GetClass() * 1000) + SkillID)) {
				SkillLearn sLearn = SkillChecks.find((IPlayer.GetClass() * 1000) + SkillID)->second;

				bool SpecCheck = false;
				for (int i = 0; i < sLearn.Specialties.size(); i++) {
					if (IPlayer.GetSpecialty() == sLearn.Specialties[i]) {
						SpecCheck = true;
						break;
					}
				}

				if (!SpecCheck) {
					IPlayer.SystemMessage("Wrong Specialty for this skill.", TEXTCOLOR_RED);
					return;
				}

				int pSkill = IPlayer.GetSkillPointer(SkillID);

				if (pSkill) {
					ISkill xSkill((void*)pSkill);
					int Grade = xSkill.GetGrade();
					int MaxGrade = sLearn.Levels.size();

					if (Grade >= MaxGrade) {
						IPlayer.SystemMessage("You have already reached the max grade for this skill.", TEXTCOLOR_RED);
						return;
					}

					if (sLearn.Levels[Grade] > IPlayer.GetLevel()) {
						IPlayer.SystemMessage("You can not upgrade to the upper grade yet.", TEXTCOLOR_RED);
						return;
					}

					if (IPlayer.GetSkillPoint() > 0)
					{
						int newGrade = xSkill.GetGrade() + 1;
						(*(void(__thiscall **)(int, DWORD, int, signed int))(*(DWORD *)pSkill + 8))(pSkill, (int)IPlayer.GetOffset(), newGrade, 1);
						*(DWORD *)(pSkill + 8) = newGrade;

						CDBSocket::Write(22, "dbbw", IPlayer.GetPID(), SkillID, newGrade, IPlayer.GetSkillPoint());
						CPlayer::Write(IPlayer.GetOffset(), 81, "bb", SkillID, newGrade);
						IPlayer.RemoveSkillPoint(1);
					}
				}
				return;
			}

			if (IPlayer.GetClass() == 1 && SkillID == 77)
			{
				int SkillPointer = IPlayer.GetSkillPointer(SkillID);

				if (SkillPointer)
				{
					ISkill xSkill((void*)SkillPointer);

					if (IPlayer.GetSkillPoint() > 0 && xSkill.GetGrade() < 6)
					{
						CDBSocket::Write(10, "ddbw", IPlayer.GetPID(), SkillID, xSkill.GetGrade() + 1, 56);
						CPlayer::Write(IPlayer.GetOffset(), 81, "bb", SkillID, xSkill.GetGrade() + 1);
						*(DWORD*)((int)xSkill.GetOffset() + 8) = xSkill.GetGrade() + 1;
						IPlayer.RemoveSkillPoint(1);
					}
				}
				return;
			}

			if (IPlayer.GetClass() == 0 && ((SkillID >= 37 && SkillID <= 44) || (SkillID >= 87 && SkillID <= 89) || SkillID == 70 || SkillID == 71 || SkillID == 82))
			{
				int SkillPointer = IPlayer.GetSkillPointer(SkillID);

				if (SkillPointer)
				{
					ISkill xSkill((void*)SkillPointer);

					if (IPlayer.GetSkillPoint() > 0 && SkillUpgradeCheck(IPlayer.GetOffset(), SkillID, 1))
					{
						CDBSocket::Write(10, "ddbw", IPlayer.GetPID(), SkillID, xSkill.GetGrade() + 1, 56);
						CPlayer::Write(IPlayer.GetOffset(), 81, "bb", SkillID, xSkill.GetGrade() + 1);
						*(DWORD*)((int)xSkill.GetOffset() + 8) = xSkill.GetGrade() + 1;
						IPlayer.RemoveSkillPoint(1);
					}
				}

				return;
			}

			if (IPlayer.GetClass() == 1 && SkillID == 40)
			{
				int SkillPointer = IPlayer.GetSkillPointer(40);

				if (IPlayer.GetSkillPoint() > 0 && SkillPointer)
				{
					ISkill xSkill((void*)SkillPointer);

					if (xSkill.GetGrade() >= 1 && xSkill.GetGrade() < xSkill.GetMaxGrade())
					{
						int Check = (IPlayer.GetLevel() - 47) / 5;

						if (Check > xSkill.GetGrade())
						{
							CDBSocket::Write(10, "ddbw", IPlayer.GetPID(), SkillID, xSkill.GetGrade() + 1, 56);
							CPlayer::Write(IPlayer.GetOffset(), 81, "bb", SkillID, xSkill.GetGrade() + 1);
							*(DWORD*)((int)xSkill.GetOffset() + 8) = xSkill.GetGrade() + 1;
							IPlayer.RemoveSkillPoint(1);
							return;
						}
					}
				}
			}

			if (IPlayer.GetClass() == 1 && SkillID == 26)
			{
				int SkillPointer = IPlayer.GetSkillPointer(26);

				if (IPlayer.GetSkillPoint() > 0 && SkillPointer)
				{
					ISkill xSkill((void*)SkillPointer);

					if (xSkill.GetGrade() >= 1 && xSkill.GetGrade() < xSkill.GetMaxGrade())
					{
						if (IPlayer.GetLevel() >= 30)
						{
							CDBSocket::Write(10, "ddbw", IPlayer.GetPID(), SkillID, xSkill.GetGrade() + 1, 56);
							CPlayer::Write(IPlayer.GetOffset(), 81, "bb", SkillID, xSkill.GetGrade() + 1);
							*(DWORD*)((int)xSkill.GetOffset() + 8) = xSkill.GetGrade() + 1;
							IPlayer.RemoveSkillPoint(1);
							return;
						}
					}
				}
			}

			if (IPlayer.GetClass() == 1 && ((SkillID >= 63 && SkillID <= 76) || (SkillID >= 87 && SkillID <= 89) || SkillID == 82))
			{
				int SkillPointer = IPlayer.GetSkillPointer(SkillID);

				if (SkillPointer)
				{
					ISkill xSkill((void*)SkillPointer);

					if (IPlayer.GetSkillPoint() > 0 && SkillUpgradeCheck(IPlayer.GetOffset(), SkillID, 1))
					{
						CDBSocket::Write(10, "ddbw", IPlayer.GetPID(), SkillID, xSkill.GetGrade() + 1, 56);
						CPlayer::Write(IPlayer.GetOffset(), 81, "bb", SkillID, xSkill.GetGrade() + 1);
						*(DWORD*)((int)xSkill.GetOffset() + 8) = xSkill.GetGrade() + 1;
						IPlayer.RemoveSkillPoint(1);
					}
				}

				return;
			}

			if (IPlayer.GetClass() == 2 && ((SkillID >= 46 && SkillID <= 51) || (SkillID >= 87 && SkillID <= 89) || SkillID == 70 || SkillID == 71 || SkillID == 82))
			{
				int SkillPointer = IPlayer.GetSkillPointer(SkillID);

				if (SkillPointer)
				{
					ISkill xSkill((void*)SkillPointer);

					if (IPlayer.GetSkillPoint() > 0 && SkillUpgradeCheck(IPlayer.GetOffset(), SkillID, 1))
					{
						CDBSocket::Write(10, "ddbw", IPlayer.GetPID(), SkillID, xSkill.GetGrade() + 1, 56);
						CPlayer::Write(IPlayer.GetOffset(), 81, "bb", SkillID, xSkill.GetGrade() + 1);
						*(DWORD*)((int)xSkill.GetOffset() + 8) = xSkill.GetGrade() + 1;
						IPlayer.RemoveSkillPoint(1);
					}
				}

				return;
			}

			if (IPlayer.GetClass() == 3 && ((SkillID >= 0 && SkillID <= 37) || (SkillID >= 87 && SkillID <= 89) || SkillID == 70 || SkillID == 63))
			{
				int SkillPointer = IPlayer.GetSkillPointer(SkillID);

				if (SkillPointer)
				{
					ISkill xSkill((void*)SkillPointer);

					if (IPlayer.GetSkillPoint() > 0 && SkillUpgradeCheck(IPlayer.GetOffset(), SkillID, 1))
					{
						CDBSocket::Write(10, "ddbw", IPlayer.GetPID(), SkillID, xSkill.GetGrade() + 1, 56);
						CPlayer::Write(IPlayer.GetOffset(), 81, "bb", SkillID, xSkill.GetGrade() + 1);
						*(DWORD*)((int)xSkill.GetOffset() + 8) = xSkill.GetGrade() + 1;
						IPlayer.RemoveSkillPoint(1);
					}
				}

				return;
			}

			if (IPlayer.GetClass() == 4 && SkillID >= 0 && SkillID <= 89)
			{
				int SkillPointer = IPlayer.GetSkillPointer(SkillID);

				if (SkillPointer)
				{
					ISkill xSkill((void*)SkillPointer);

					if (IPlayer.GetSkillPoint() > 0 && SkillUpgradeCheck(IPlayer.GetOffset(), SkillID, 1))
					{
						CDBSocket::Write(10, "ddbw", IPlayer.GetPID(), SkillID, xSkill.GetGrade() + 1, 56);
						CPlayer::Write(IPlayer.GetOffset(), 81, "bb", SkillID, xSkill.GetGrade() + 1);
						*(DWORD*)((int)xSkill.GetOffset() + 8) = xSkill.GetGrade() + 1;
						IPlayer.RemoveSkillPoint(1);
					}
				}

				return;
			}
		}

		if (packet == 255)
		{
			int TypeCheck = 0;
			int Check = CPacket::Read((char*)pPacket, (char*)pPos, "d", &TypeCheck);

			if (TypeCheck == 9)
			{
				int RQuestx = (185 << 16) | 1;
				bool checkFlag = CPlayer::CheckQuestFlag(Player, RQuestx);
				if (checkFlag) {
					IPlayer.SystemMessage("You have already rewarded.", TEXTCOLOR_RED);
					return;
				}
				else
					CQuest::Start((185 << 16) | 1, (int)IPlayer.GetOffset());
			}

			if (TypeCheck == 8)
			{
				int SkillID = 0, compare4 = 0, compare3 = 0, Class = 0;
				CPacket::Read((char*)Check, (char*)pPos, "dddd", &SkillID, &compare4, &compare3, &Class);
				int nextExecutionTime = IPlayer.GetBuffValue(BuffNames::CDProtect + SkillID);

				if ((Class == 2 && SkillID == 16) || (Class == 0 && SkillID == 38))
					return;

				if (IPlayer.GetClass() == Class && GetTickCount() >= nextExecutionTime)
				{
					JobSystem cooldownInfo = JobSystem();
					int sekey = SkillID + (Class * 100);

					cooldownInfo.compare4 = compare4;
					cooldownInfo.compare3 = compare3;
					Cooldowns[sekey] = cooldownInfo;
				}
			}

			if (TypeCheck == 5)
			{
				if (IPlayer.IsUnblobbing())
				{
					IPlayer.SetUnblob(0);
					IPlayer.SystemMessage("Monster blob enabled.", TEXTCOLOR_INFOMSG);
				}
				else {
					IPlayer.SetUnblob(1);
					IPlayer.SystemMessage("Monster blob disabled.", TEXTCOLOR_INFOMSG);
				}
			}

			if (TypeCheck == 6) {
				int numLock = 0;
				CPacket::Read((char*)Check, (char*)pPos, "d", &numLock);
				if (numLock == uptimestart || !PacketProtection) {
					if (IPlayer.IsBuff(BuffNames::MacroCheck) && IPlayer.GetBuffRemain(BuffNames::MacroCheck) <= MacroStartTime + 1) {	//MacroCheck Countdown Timer
						IPlayer.SystemMessage("Successfully Passed AFK check.", TEXTCOLOR_GREEN);
						IPlayer.CancelBuff(BuffNames::MacroCheck);
					}
				}
			}

			if (TypeCheck == 7 && OBActive) {
				int Belt = IPlayer.GetBuffValue(BuffNames::Belt);
				if (Belt && !IPlayer.IsBuff(BuffNames::BeltBuff)) {
					int BeltB = IPlayer.GetBuffRemain(BuffNames::BeltCD);
					if (!BeltB && !IPlayer.IsBuff(BuffNames::BeltCD)) {
						if (BeltBuffs.count(Belt)) {
							BeltBuff belt = BeltBuffs.find(Belt)->second;
							IPlayer.Buff(BuffNames::BeltBuff, belt.Duration + 2, belt.HP);
							IPlayer.SaveBuff(BuffNames::BeltCD, belt.Duration + 2 + belt.Cooldown);
							IPlayer.IncreaseMaxHp(belt.HP);
							IPlayer.IncreaseHp(belt.HP);
							IPlayer.AddFxToBone(belt.Effect, 0);
						}
					}
					else
						IPlayer.SystemMessage("You still have " + Int2String(BeltB) + " seconds before being able to use the buff again.", TEXTCOLOR_RED);
				}
			}


			return;
		}

		if (packet == 61)
		{
			int ID = 0; char Type;
			CPacket::Read((char*)pPacket, (char*)pPos, "db", &ID, &Type);

			if (IPlayer.IsOnline() && IPlayer.GetID() != ID)
			{
				IPlayer.Kick();
				return;
			}
		}


		if (packet == C2S_PrepareSkill)
		{
			unsigned __int8 AnimationID = 0; int ID = 0;
			CPacket::Read((char*)pPacket, (char*)pPos, "bd", &AnimationID, &ID);

			if (IPlayer.IsValid() && IPlayer.IsBuff(349))
			{
				if (!(isBattleRiding(IPlayer.GetBuffValue(349) + 7856) && !RidingDisableSkill.count((IPlayer.GetClass() * 1000) + (int)AnimationID))) {

					IPlayer.DisableRiding();
					return;
				}
			}

			if (IPlayer.IsOnline() && IPlayer.GetID() != ID && (int)AnimationID == 1)
			{
				IPlayer.Kick();
				return;
			}

			if (CheckCooldownConfig.count(AnimationID + (IPlayer.GetClass() * 100)))
			{
				IPlayer.UpdateBuff(BuffNames::SkillPrepTime, BuffNames::BuffTime, GetTickCount() + CheckCooldownConfig.find((AnimationID + (IPlayer.GetClass() * 100)))->second.DelayConfig);
				IPlayer.UpdateBuff(BuffNames::SkillPrepID, BuffNames::BuffTime, AnimationID);
			}

			int sekey = AnimationID + (IPlayer.GetClass() * 100);
			if (Cooldowns.count(sekey)) {
				int Compare3 = Cooldowns[sekey].compare3;
				IPlayer.UpdateBuff(BuffNames::DelayProtect + AnimationID, BuffNames::BuffTime, (GetTickCount() + Compare3) - 350);
			}


			if (IPlayer.IsOnline() && AnimationID >= 100 && AnimationID <= 120 && CChar::IsGState((int)IPlayer.GetOffset(), 512))
			{
				CChar::WriteInSight((void*)Player, 61, "dbbd", IPlayer.GetID(), 5, AnimationID, ID);
				return;
			}


			if (IPlayer.IsOnline() && AnimationID == 74 && IPlayer.GetClass() == 1 && ID == IPlayer.GetID())
			{
				int pSkill = IPlayer.GetSkillPointer(74);

				if (pSkill)
				{
					if (IPlayer.GetBuffValue(BuffNames::CheckIceArrow) > GetTickCount())
					{
						IPlayer.SystemMessage("Invalid skill prepare time detected!", TEXTCOLOR_RED);
						return;
					}

					/*
					if (CheckIceArrow.count(IPlayer.GetPID()) && CheckIceArrow.find(IPlayer.GetPID())->second.Cooldown > GetTickCount())
					{
					IPlayer.SystemMessage("Invalid skill cooldown time detected!", TEXTCOLOR_RED);
					return;
					}
					*/

					ISkill xSkill((void*)pSkill);
					int IceArrowGrade = xSkill.GetGrade();
					int Mana = ((450 + (IceArrowGrade * ((IceArrowGrade - 1) + 100)))) * 0.42;
					__int64 GState = 536870912, State = 64, StateEx = 65;

					if (IPlayer.GetCurMp() <= Mana)
						return;
					else
						IPlayer.DecreaseMana(Mana);

					CPlayer::Write((void*)Player, 61, "dbbd", IPlayer.GetID(), 5, AnimationID, ID);

					if (IceArrowGrade == 1)
					{
						IPlayer.Buff(290, 18, 0);
						IPlayer.Buff(295, 18, 0);
						IPlayer.SendGStateExIceArrow(GState);
						IPlayer.SendGStateExIceArrow(State << 32);
					}
					else if (IceArrowGrade == 2)
					{
						IPlayer.Buff(291, 18, 0);
						IPlayer.Buff(295, 18, 0);
						IPlayer.SendGStateExIceArrow(GState * 2);
						IPlayer.SendGStateExIceArrow(State << 32);
					}
					else if (IceArrowGrade == 3)
					{
						IPlayer.Buff(292, 18, 0);
						IPlayer.Buff(295, 18, 0);
						IPlayer.SendGStateExIceArrow(GState * 4);
						IPlayer.SendGStateExIceArrow(State << 32);
					}
					else if (IceArrowGrade == 4)
					{
						IPlayer.Buff(293, 18, 0);
						IPlayer.Buff(295, 18, 0);
						IPlayer.SendGStateExIceArrow(GState * 8);
						IPlayer.SendGStateExIceArrow(State << 32);
					}
					else if (IceArrowGrade == 5)
					{
						IPlayer.Buff(294, 18, 0);
						IPlayer.Buff(295, 18, 0);
						IPlayer.SendGStateExIceArrow(GState * 16);
						IPlayer.SendGStateExIceArrow(StateEx << 32);
					}
					else {
						return;
					}
				}

				return;
			}
		}

		if (packet == 85)
		{
			int ID = 0; unsigned __int8 Type = 0; char Kind = 0;
			int Check = CPacket::Read((char*)pPacket, (char*)pPos, "b", &Type);

			if (Type == 1)
			{
				CPacket::Read((char*)Check, (char*)pPos, "db", &ID, &Kind);
				TargetFind myTarget(0, 0, ID);
				void *GetPlayer = myTarget.getTarget();

				if (GetPlayer)
				{
					IChar Player(GetPlayer);

					if (Player.IsOnline())
					{
						if (Player.GetLevel() > MLMStudentLevel)
						{
							IPlayer.Kick();
							return;
						}
					}
				}
			}
		}

		if (packet == 179)
		{
			char Type = 0; int Key = 0;
			CPacket::Read((char*)pPacket, (char*)pPos, "bw", &Type, &Key);
			int Rate = CTools::Rate(1, 1000);

			if (Type == 1 && Key)
			{
				if (CPlayer::GetInvenSize(Player) >= IPlayer.MaxInventorySize())
				{
					IPlayer.BoxMsg("Your inventory is full.");
					return;
				}

				if (MakeChange.count(Key)) {
					SwapMineral mix = MakeChange.find(Key)->second;
					Interface<ITools> Tools;
					std::vector<std::string> requireIndex = Tools->Explode(mix.requires, ",");
					std::vector<std::string> requireAmounts = Tools->Explode(mix.requireAmounts, ",");
					std::vector<std::string> chances = Tools->Explode(mix.chances, ",");
					std::vector<std::string> items = Tools->Explode(mix.itemRewards, ",");
					std::vector<std::string> itemAmounts = Tools->Explode(mix.itemAmounts, ",");

					if (requireIndex.size() == requireAmounts.size() && items.size() == itemAmounts.size() && items.size() == chances.size()) {
						for (int i = 0; i < requireIndex.size(); i++) {
							int Index = String2Int(requireIndex[i]);
							int Amount = String2Int(requireAmounts[i]);

							if (Index && Amount && !CPlayer::FindItem((void*)Player, Index, Amount)) {
								IPlayer.SystemMessage("You do not have all the items.", TEXTCOLOR_RED);
								return;
							}
						}

						for (int i = 0; i < requireIndex.size(); i++) {
							int Index = String2Int(requireIndex[i]);
							int Amount = String2Int(requireAmounts[i]);
							if (Index && Amount)
								CPlayer::RemoveItem((void*)Player, 9, Index, Amount);
						}

						for (int i = 0; i < items.size(); i++) {
							int Index = String2Int(items[i]);
							int Amount = String2Int(itemAmounts[i]);
							int Chance = String2Int(chances[i]);

							if (Index && Amount && Chance && Chance >= Rate) {
								CItem::InsertItem((int)IPlayer.GetOffset(), 27, Index, 0, Amount, -1);
								return;
							}
						}
					}
				}

				if (Key == 1 && CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 2655, 20) && CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 31, 1000))
				{
					if (Rate >= 550)
					{
						if (Rate >= 750)
						{
							if (Rate >= 900)
							{
								CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2655, 0, 20, -1);
							}
							else {
								CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2656, 0, 5, -1);
							}
						}
						else {
							CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2657, 0, 5, -1);
						}
					}
					else {
						CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2658, 0, 2, -1);
					}

					return;
				}

				if (Key == 2 && CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 2656, 5) && CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 31, 1000))
				{
					if (Rate >= 550)
					{
						if (Rate >= 750)
						{
							if (Rate >= 900)
							{
								CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2655, 0, 20, -1);
							}
							else {
								CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2656, 0, 5, -1);
							}
						}
						else {
							CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2657, 0, 5, -1);
						}
					}
					else {
						CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2658, 0, 2, -1);
					}

					return;
				}

				if (Key == 3 && CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 2657, 5) && CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 31, 1000))
				{
					if (Rate >= 550)
					{
						if (Rate >= 750)
						{
							if (Rate >= 900)
							{
								CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2655, 0, 20, -1);
							}
							else {
								CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2656, 0, 5, -1);
							}
						}
						else {
							CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2657, 0, 5, -1);
						}
					}
					else {
						CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2658, 0, 2, -1);
					}

					return;
				}

				if (Key == 4 && CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 2659, 20) && CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 31, 5000))
				{
					if (Rate >= 550)
					{
						if (Rate >= 750)
						{
							if (Rate >= 900)
							{
								CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2659, 0, 20, -1);
							}
							else {
								CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2660, 0, 5, -1);
							}
						}
						else {
							CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2661, 0, 5, -1);
						}
					}
					else {
						CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2662, 0, 2, -1);
					}

					return;
				}

				if (Key == 5 && CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 2660, 5) && CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 31, 5000))
				{
					if (Rate >= 550)
					{
						if (Rate >= 750)
						{
							if (Rate >= 900)
							{
								CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2659, 0, 20, -1);
							}
							else {
								CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2660, 0, 5, -1);
							}
						}
						else {
							CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2661, 0, 5, -1);
						}
					}
					else {
						CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2662, 0, 2, -1);
					}

					return;
				}

				if (Key == 6 && CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 2661, 5) && CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 31, 5000))
				{
					if (Rate >= 550)
					{
						if (Rate >= 750)
						{
							if (Rate >= 900)
							{
								CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2659, 0, 20, -1);
							}
							else {
								CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2660, 0, 5, -1);
							}
						}
						else {
							CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2661, 0, 5, -1);
						}
					}
					else {
						CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2662, 0, 2, -1);
					}

					return;
				}

				if (Key == 7 && CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 2663, 10) && CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 31, 5000))
				{
					if (Rate >= 550)
					{
						if (Rate >= 750)
						{
							if (Rate >= 900)
							{
								CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2663, 0, 10, -1);
							}
							else {
								CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2664, 0, 5, -1);
							}
						}
						else {
							CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2665, 0, 5, -1);
						}
					}
					else {
						CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2666, 0, 2, -1);
					}

					return;
				}

				if (Key == 8 && CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 2664, 5) && CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 31, 5000))
				{
					if (Rate >= 550)
					{
						if (Rate >= 750)
						{
							if (Rate >= 900)
							{
								CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2663, 0, 10, -1);
							}
							else {
								CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2664, 0, 5, -1);
							}
						}
						else {
							CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2665, 0, 5, -1);
						}
					}
					else {
						CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2666, 0, 2, -1);
					}

					return;
				}

				if (Key == 9 && CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 2665, 5) && CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 31, 5000))
				{
					if (Rate >= 550)
					{
						if (Rate >= 750)
						{
							if (Rate >= 900)
							{
								CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2663, 0, 10, -1);
							}
							else {
								CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2664, 0, 5, -1);
							}
						}
						else {
							CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2665, 0, 5, -1);
						}
					}
					else {
						CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2666, 0, 2, -1);
					}

					return;
				}

				if (Key == 10 && CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 2667, 10) && CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 31, 10000))
				{
					if (Rate >= 550)
					{
						if (Rate >= 750)
						{
							if (Rate >= 900)
							{
								if (Rate >= 950)
								{
									CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2667, 0, 10, -1);
								}
								else {
									CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2668, 0, 5, -1);
								}
							}
							else {
								CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2669, 0, 5, -1);
							}
						}
						else {
							CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2670, 0, 1, -1);
						}
					}
					else {
						CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2538, 0, 1, -1);
					}

					return;
				}

				if (Key == 11 && CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 2668, 5) && CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 31, 10000))
				{
					if (Rate >= 550)
					{
						if (Rate >= 750)
						{
							if (Rate >= 900)
							{
								if (Rate >= 950)
								{
									CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2667, 0, 10, -1);
								}
								else {
									CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2668, 0, 5, -1);
								}
							}
							else {
								CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2669, 0, 5, -1);
							}
						}
						else {
							CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2670, 0, 1, -1);
						}
					}
					else {
						CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2538, 0, 1, -1);
					}

					return;
				}

				if (Key == 12 && CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 2669, 5) && CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 31, 10000))
				{
					if (Rate >= 550)
					{
						if (Rate >= 750)
						{
							if (Rate >= 900)
							{
								if (Rate >= 950)
								{
									CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2667, 0, 10, -1);
								}
								else {
									CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2668, 0, 5, -1);
								}
							}
							else {
								CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2669, 0, 5, -1);
							}
						}
						else {
							CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2670, 0, 1, -1);
						}
					}
					else {
						CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2538, 0, 1, -1);
					}

					return;
				}

				if (Key == 13 && CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 2670, 1) && CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 31, 10000))
				{
					if (Rate >= 550)
					{
						if (Rate >= 750)
						{
							if (Rate >= 900)
							{
								if (Rate >= 950)
								{
									CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2667, 0, 10, -1);
								}
								else {
									CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2668, 0, 5, -1);
								}
							}
							else {
								CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2669, 0, 5, -1);
							}
						}
						else {
							CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2670, 0, 1, -1);
						}
					}
					else {
						CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2538, 0, 1, -1);
					}

					return;
				}

				if (Key == 14 && CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 2671, 10) && CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 31, 30000))
				{
					if (Rate >= 550)
					{
						if (Rate >= 750)
						{
							if (Rate >= 900)
							{
								if (Rate >= 950)
								{
									CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2671, 0, 10, -1);
								}
								else {
									CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2672, 0, 5, -1);
								}
							}
							else {
								CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2673, 0, 1, -1);
							}
						}
						else {
							CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2674, 0, 1, -1);
						}
					}
					else {
						CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2675, 0, 1, -1);
					}

					return;
				}

				if (Key == 15 && CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 2672, 5) && CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 31, 30000))
				{
					if (Rate >= 550)
					{
						if (Rate >= 750)
						{
							if (Rate >= 900)
							{
								if (Rate >= 950)
								{
									CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2671, 0, 10, -1);
								}
								else {
									CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2672, 0, 5, -1);
								}
							}
							else {
								CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2673, 0, 1, -1);
							}
						}
						else {
							CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2674, 0, 1, -1);
						}
					}
					else {
						CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2675, 0, 1, -1);
					}

					return;
				}

				if (Key == 16 && CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 2673, 1) && CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 31, 30000))
				{
					if (Rate >= 550)
					{
						if (Rate >= 750)
						{
							if (Rate >= 900)
							{
								if (Rate >= 950)
								{
									CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2671, 0, 10, -1);
								}
								else {
									CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2672, 0, 5, -1);
								}
							}
							else {
								CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2673, 0, 1, -1);
							}
						}
						else {
							CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2674, 0, 1, -1);
						}
					}
					else {
						CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2675, 0, 1, -1);
					}

					return;
				}

				if (Key == 17 && CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 2674, 1) && CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 31, 30000))
				{
					if (Rate >= 550)
					{
						if (Rate >= 750)
						{
							if (Rate >= 900)
							{
								if (Rate >= 950)
								{
									CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2671, 0, 10, -1);
								}
								else {
									CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2672, 0, 5, -1);
								}
							}
							else {
								CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2673, 0, 1, -1);
							}
						}
						else {
							CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2674, 0, 1, -1);
						}
					}
					else {
						CItem::InsertItem((int)IPlayer.GetOffset(), 27, 2675, 0, 1, -1);
					}

					return;
				}
			}

			return;
		}

		CPlayer::Process((void*)Player, packet, (void*)pPacket, pPos);

		if (IPlayer.IsOnline() && packet == 18 && IPlayer.GetClass() == 4 && IPlayer.IsBuff(406))
			CPlayer::Write(IPlayer.GetOffset(), 148, "dI", IPlayer.GetID(), (__int64)0);

		//new
		if (IPlayer.IsOnline() && packet == 67 && CChar::IsGState(Player, 16) && !IPlayer.IsBuff(3959))
		{
			IPlayer.Buff(3959, 604800, 0);
			ShopLimit[sha256(IPlayer.GetHWID() + IPlayer.GetIP())]++;
		}
		//endnew
	}
}