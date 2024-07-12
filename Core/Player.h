void CreateFakePlayers(void *Player) {
	CPlayer::Write(Player, 0xFE, "dd", 212, EFakePlayers);

	if (EFakePlayers) {
		Interface<ITools>Tools;
		IChar IPlayer(Player);

		if (IPlayer.IsOnline() && IPlayer.GetType() == 0 && !IPlayer.GetChannel()) {

			int i = 0;
			for (auto x = FakePlayers.rbegin(); x != FakePlayers.rend(); x++)
			{
				if (x->second.check) {
					char * Items = new char[76];
					Tools->Compile(Items, "wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww", x->second.weapon, x->second.chest, x->second.helmet, x->second.glove, x->second.boot, x->second.skirt, x->second.shield, x->second.costume, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
					CPlayer::Write(IPlayer.GetOffset(), 50, "dsbdddwImbbIssdbdddIIbbdbd", x->first, x->second.name.c_str(), x->second.cclass, x->second.x, x->second.y, x->second.z, x->second.direction, (unsigned __int64)x->second.gstate, Items, 76, x->second.face, x->second.hair, (unsigned __int64)0, NULL, NULL, 0, 0, 0, x->second.honor, 0, (unsigned __int64)0, (unsigned __int64)0, 0, 0, 0, 0, x->second.color);//IssdbdddII

					delete[] Items;
					i++;
					if (i >= EFakePlayers)
						break;
				}
			}
		}
	}
}

bool isPlayerInPVP(void* Player) {
	IChar IPlayer(Player);

	int Map = IPlayer.GetMap();
	int MapX = IPlayer.GetX() >> 13;
	int MapY = IPlayer.GetY() >> 13;

	if ((Battlefield::Active && Map == BFMap) || (LastManStand::Active && Map == LMSMap) || (Scenario::Active && Map == ScenarioMap) || (Protect32::Active && Map == PLMap) || (CaptureFlag::Active && Map == CaptureMap) || (TriangularBattle::Active && Map == TBMap) || (SufferingValley::Active && Map == SVMap) || (F10::Active && Map == 21) || (BossEXP::Active && Map == BossEXPMap) || (Maut::Active && Map == MautMap) || (DuelTournament::Active && MapX == 26 && MapY == 34 && IPlayer.GetZ() < 37600) || CChar::IsGState((int)Player, 16) || CChar::IsGState((int)Player, 32))
		return true;

	return false;
}

bool isInMacroMap(int MapX, int MapY) {
	return Macro.count((MapX + 1000)*(MapY + 100)) > 0;
}
int HonorMessageSys(void* Player, int Type) {
	IChar IPlayer(Player);

	if (PeaceEvil != 1)
		return 0;

	int value = 0;
	int SQuest = (SlytherinQuest << 16) + 1;
	int RQuest = (RavenQuest << 16) + 1;
	int HQuest = (HuffleQuest << 16) + 1;

	bool IsSlytherin = CPlayer::CheckQuestFlag((int)Player, SQuest);
	bool IsRavenclaw = CPlayer::CheckQuestFlag((int)Player, RQuest);
	bool IsHufflepuff = CPlayer::CheckQuestFlag((int)Player, HQuest);

	switch (Type) {
	case 0:
		value = IsSlytherin ? Slytherin0 : (IsRavenclaw ? Ravenclaw0 : (IsHufflepuff ? Hufflepuff0 : Gryffindor0));
		break;
	case 1:
		value = IsSlytherin ? Slytherin1 : (IsRavenclaw ? Ravenclaw1 : (IsHufflepuff ? Hufflepuff1 : Gryffindor1));
		break;
	case 2:
		value = IsSlytherin ? Slytherin2 : (IsRavenclaw ? Ravenclaw2 : (IsHufflepuff ? Hufflepuff2 : Gryffindor2));
		break;
	case 3:
		value = IsSlytherin ? Slytherin3 : (IsRavenclaw ? Ravenclaw3 : (IsHufflepuff ? Hufflepuff3 : Gryffindor3));
		break;
	case 4:
		value = IsSlytherin ? Slytherin4 : (IsRavenclaw ? Ravenclaw4 : (IsHufflepuff ? Hufflepuff4 : Gryffindor4));
		break;
	case 5:
		value = IsSlytherin ? Slytherin5 : (IsRavenclaw ? Ravenclaw5 : (IsHufflepuff ? Hufflepuff5 : Gryffindor5));
		break;
	case 6:
		value = IsSlytherin ? Slytherin6 : (IsRavenclaw ? Ravenclaw6 : (IsHufflepuff ? Hufflepuff6 : Gryffindor6));
		break;
	case 7:
		value = IsSlytherin ? Slytherin7 : (IsRavenclaw ? Ravenclaw7 : (IsHufflepuff ? Hufflepuff7 : Gryffindor7));
		break;
	case 8:
		value = IsSlytherin ? Slytherin8 : (IsRavenclaw ? Ravenclaw8 : (IsHufflepuff ? Hufflepuff8 : Gryffindor8));
		break;
	case 9:
		value = IsSlytherin ? Slytherin9 : (IsRavenclaw ? Ravenclaw9 : (IsHufflepuff ? Hufflepuff9 : Gryffindor9));
		break;
	case 10:
		value = IsSlytherin ? Slytherin10 : (IsRavenclaw ? Ravenclaw10 : (IsHufflepuff ? Hufflepuff10 : Gryffindor10));
		break;
	}

	return value;
}


int HonorMessageSysA(void* Player, int Type) {
	IChar IPlayer(Player);

	if (PeaceEvil != 1)
		return 0;

	int value = 0;

	bool IsSlytherin = IPlayer.IsBuff(BuffNames::Slytherin) ? true : false;
	bool IsRavenclaw = IPlayer.IsBuff(BuffNames::Ravenclaw) ? true : false;
	bool IsHufflepuff = IPlayer.IsBuff(BuffNames::Hufflepuff) ? true : false;

	switch (Type) {
	case 0:
		value = IsSlytherin ? Slytherin0 : (IsRavenclaw ? Ravenclaw0 : (IsHufflepuff ? Hufflepuff0 : Gryffindor0));
		break;
	case 1:
		value = IsSlytherin ? Slytherin1 : (IsRavenclaw ? Ravenclaw1 : (IsHufflepuff ? Hufflepuff1 : Gryffindor1));
		break;
	case 2:
		value = IsSlytherin ? Slytherin2 : (IsRavenclaw ? Ravenclaw2 : (IsHufflepuff ? Hufflepuff2 : Gryffindor2));
		break;
	case 3:
		value = IsSlytherin ? Slytherin3 : (IsRavenclaw ? Ravenclaw3 : (IsHufflepuff ? Hufflepuff3 : Gryffindor3));
		break;
	case 4:
		value = IsSlytherin ? Slytherin4 : (IsRavenclaw ? Ravenclaw4 : (IsHufflepuff ? Hufflepuff4 : Gryffindor4));
		break;
	case 5:
		value = IsSlytherin ? Slytherin5 : (IsRavenclaw ? Ravenclaw5 : (IsHufflepuff ? Hufflepuff5 : Gryffindor5));
		break;
	case 6:
		value = IsSlytherin ? Slytherin6 : (IsRavenclaw ? Ravenclaw6 : (IsHufflepuff ? Hufflepuff6 : Gryffindor6));
		break;
	case 7:
		value = IsSlytherin ? Slytherin7 : (IsRavenclaw ? Ravenclaw7 : (IsHufflepuff ? Hufflepuff7 : Gryffindor7));
		break;
	case 8:
		value = IsSlytherin ? Slytherin8 : (IsRavenclaw ? Ravenclaw8 : (IsHufflepuff ? Hufflepuff8 : Gryffindor8));
		break;
	case 9:
		value = IsSlytherin ? Slytherin9 : (IsRavenclaw ? Ravenclaw9 : (IsHufflepuff ? Hufflepuff9 : Gryffindor9));
		break;
	case 10:
		value = IsSlytherin ? Slytherin10 : (IsRavenclaw ? Ravenclaw10 : (IsHufflepuff ? Hufflepuff10 : Gryffindor10));
		break;
	}

	return value;
}


void insertReward(void* Player, int RewardID) {
	if (!RewardID)
		return;
	IChar IPlayer(Player);

	if (IPlayer.IsOnline()) {
		int UniqueRewardID = RewardID + (IPlayer.GetLevel() * 100);
		if (Rewards.count(UniqueRewardID)) {
			int progressValue = Rewards[UniqueRewardID].Progress;

			unsigned __int64 currentLevelExp = _ExpTable[IPlayer.GetLevel() - 1];
			unsigned __int64 nextLevelExp = _ExpTable[IPlayer.GetLevel()];

			// Calculate required experience based on progressValue
			double progressCalc = (static_cast<double>(progressValue) / 1000.0) * nextLevelExp;

			if (progressValue > 1000) {
				// Calculate how many levels to progress
				int levelsToProgress = progressValue / 1000;

				// Calculate total experience needed to progress levelsToProgress levels
				unsigned __int64 totalExpToProgress = 0;
				for (int i = 0; i < levelsToProgress; ++i) {
					totalExpToProgress += _ExpTable[IPlayer.GetLevel() + i];
				}

				unsigned __int64 expToUpdate = static_cast<unsigned __int64>(totalExpToProgress);
				unsigned __int64 currentExp = 0;

				while (expToUpdate > 0) {
					unsigned __int64 updateAmount = min(expToUpdate, static_cast<unsigned __int64>(2147483640));

					CPlayer::UpdateProperty((int)Player, 25, 1, static_cast<int>(updateAmount));
					currentExp += updateAmount;
					expToUpdate -= updateAmount;
				}
			}
			else {
				unsigned __int64 expToUpdate = static_cast<unsigned __int64>(progressCalc);
				unsigned __int64 currentExp = 0;

				while (expToUpdate > 0) {
					unsigned __int64 updateAmount = min(expToUpdate, static_cast<unsigned __int64>(2147483640));

					CPlayer::UpdateProperty((int)Player, 25, 1, static_cast<int>(updateAmount));
					currentExp += updateAmount;
					expToUpdate -= updateAmount;
				}
			}
		}
	}



	if (IPlayer.IsOnline() && Rewards.count(RewardID)) {
		Reward pReward = Rewards.find(RewardID)->second;
		for (int i = 0; i < pReward.Indexes.size(); i++) {
			int Index = String2Int(pReward.Indexes[i]);
			int Amount = String2Int(pReward.Amounts[i]);
			if (Index && Amount)
				IPlayer.InsertItem(Index, pReward.Bound == 1 ? 256 : 0, Amount);
		}

		if (pReward.HonorPts || pReward.RewardPts)
			IPlayer.SetHonor(pReward.HonorPts, pReward.RewardPts, 0, 0, 0, 0, 0, 0, 0, 0);
		if (pReward.HTML)
			IPlayer.OpenHTML(pReward.HTML);
		if (pReward.EXP)
			CPlayer::UpdateProperty((int)Player, 25, 1, pReward.EXP);

		if (!pReward.Notice.empty() && IPlayer.IsValid()){
			std::string msg = (std::string)IPlayer.GetName() + " " + pReward.Notice;
			if (!msg.empty()) {
				int textColor = TEXTCOLOR_GREEN;
				int messageType = 1;

				RewardMessage reward;
				reward.message = msg;
				reward.textColor = textColor;
				reward.messageType = messageType;

				PlayerRewardNotice.push_back(reward);

				std::string avatar = Avatar;
				std::string playerName = std::string(IPlayer.GetName());
				std::string url = NoticeWebHook;
				SendWebhookMessage(url, msg.c_str(), avatar.c_str(), std::string(playerName));
			}
		}

		if (PeaceEvil && pReward.HousePoints)
			IPlayer.AddHousePoints(pReward.HousePoints);
	}

}

std::string GetHardware(void* Player) {
	IChar IPlayer(Player);

	std::string HWID = "";

	if (User.count(IPlayer.GetPID()))
		HWID = User.findValue(IPlayer.GetPID()).Hardware;

	return HWID;
}

std::string GetPC(void* Player) {
	if (!Player)
		return "";
	IChar IPlayer(Player);

	std::string PCName = "";

	if (IPlayer.IsOnline() && User.count(IPlayer.GetPID()))
		PCName = User.findValue(IPlayer.GetPID()).PCName;

	return PCName;
}

std::string GetMACAddr(void* Player) {
	if (!Player)
		return "";
	IChar IPlayer(Player);

	std::string MAC = "";

	if (IPlayer.IsOnline() && User.count(IPlayer.GetPID()))
		MAC = User.findValue(IPlayer.GetPID()).MAC;

	return MAC;
}

void UpdateMD5() {
	CIOCriticalSection::Enter((void*)0x004e2078);
	CIOCriticalSection::Enter((void*)0x004e2098);
	CLink::MoveTo((void*)0x004e200c, (int)0x004e2004);
	CIOCriticalSection::Leave((void*)0x004e2098);
	for (DWORD a = *(DWORD*)0x004E2004; a != 0x004E2004; a = *(DWORD*)a)
	{
		if ((void*)(a - 428))
		{
			IChar IPlayer((void*)(a - 428));
			IPlayer.UpdateBuff(BuffNames::MD5Hash, BuffNames::BuffTime, GetTickCount() + 300000);
		}
	}
	CIOCriticalSection::Leave((void*)0x004e2078);
}

void CheckCalls(IChar IPlayer, int BuffID, int Type) {
	if (BuffID > 0) {
		if (IPlayer.IsParty()) {
			void* Party = (void*)CParty::FindParty(IPlayer.GetPartyID());

			if (Party)
			{
				CIOCriticalSection::Enter((struct _RTL_CRITICAL_SECTION *)((int)IPlayer.GetOffset() + 364));
				int Check = CChar::FindBuff((int)IPlayer.GetOffset(), BuffID);
				CIOCriticalSection::Leave((void*)((char *)(int)IPlayer.GetOffset() + 364));

				for (int i = CParty::GetPlayerList(Party); i; i = CBaseList::Pop((void*)i))
				{
					IChar IMembers((void*)* (DWORD*)((void*)i));

					if (IMembers.IsOnline() && IMembers.GetOffset() != IPlayer.GetOffset())
					{
						int Range = CChar::GetRange((int)IPlayer.GetOffset() + 332, (int)IMembers.GetOffset() + 332);
						if (IMembers.GetBuffValue(BuffNames::CallBuffer) == (int)IPlayer.GetOffset()) {
							if (IMembers.IsBuff(BuffID) && Range >= CRangeCheck) {
								IMembers.UpdateBuff(BuffNames::CallPlayer + Type, BuffNames::BuffTime, BuffID);
								CChar::CancelAllBuff(IMembers.GetOffset(), BuffID);
							}
							else if (IMembers.GetBuffValue(BuffNames::CallPlayer + Type) == BuffID && Range < CRangeCheck && Check) {
								CChar::CancelAllBuff(IMembers.GetOffset(), BuffID);
								int Buff = (*(int(__thiscall **)(DWORD))(*(DWORD *)Check + 20))(Check);
								(*(void(__thiscall **)(DWORD, DWORD))(*(DWORD*)(int)IMembers.GetOffset() + 180))((int)IMembers.GetOffset(), Buff);
								IMembers.UpdateBuff(BuffNames::CallPlayer + Type, BuffNames::BuffTime, 0);
							}
						}
						else {
							if (!IMembers.IsBuff(BuffID) && Range < CRangeCheck && Check) {
								int Buff = (*(int(__thiscall **)(DWORD))(*(DWORD *)Check + 20))(Check);
								(*(void(__thiscall **)(DWORD, DWORD))(*(DWORD*)(int)IMembers.GetOffset() + 180))((int)IMembers.GetOffset(), Buff);
								IMembers.UpdateBuff(BuffNames::CallBuffer, BuffNames::BuffTime, (int)IPlayer.GetOffset());
							}
						}
					}
				}
				CIOObject::Release(Party);
			}
		}
	}
}

void updateRidingCollection(void* Player, int Collection, int Type, int Stat, int Rate) {
	IChar IPlayer(Player);

	if (IPlayer.IsOnline()) {
		switch (Stat) {
		case 1:
			if (Type)
				IPlayer.AddStr(Rate);
			else
				IPlayer.RemoveStr(Rate);
			break;
		case 2:
			if (Type)
				IPlayer.AddHp(Rate);
			else
				IPlayer.RemoveHp(Rate);
			break;
		case 3:
			if (Type)
				IPlayer.AddWis(Rate);
			else
				IPlayer.RemoveWis(Rate);
			break;
		case 4:
			if (Type)
				IPlayer.AddInt(Rate);
			else
				IPlayer.RemoveInt(Rate);
			break;
		case 5:
			if (Type)
				IPlayer.AddAgi(Rate);
			else
				IPlayer.RemoveAgi(Rate);
			break;
		case 6:
			if (Type) {
				IPlayer.IncreaseMaxHp(Rate);
				IPlayer.IncreaseMaxMp(Rate);
			}
			else{
				IPlayer.DecreaseMaxHp(Rate);
				IPlayer.DecreaseMaxMp(Rate);
			}
			break;
		}
		if (Type)
			IPlayer.Buff(5500 + Collection, BuffNames::BuffTime, 0);
		else
			IPlayer.CancelBuff(5500 + Collection);
	}
}

void ShowSummonedNPCs(void *Player) {
	IChar IPlayer(Player);
	int NPCLastCheck = IPlayer.GetBuffValue(BuffNames::NPCSummon);
	if (IPlayer.IsOnline() && NPCLastCheck > NPCID) {
		npcLock.Enter();
		std::map <int, SummonNPC> CloneSummonNPC = NPCSummoned;
		npcLock.Leave();

		for (auto x = CloneSummonNPC.begin(); x != CloneSummonNPC.end(); x++)
		{
			if (x->first >= NPCLastCheck)
				break;

			if (x->second.Time > (int)time(0)) {
				CPlayer::Write((void*)Player, 0xFE, "ddwddddd", 194, x->first, x->second.NPC, x->second.Model, x->second.X, x->second.Y, x->second.Z, x->second.Time - (int)time(0));
				CPlayer::Write((void*)Player, 52, "dwbdddwId", x->first, x->second.NPC, x->second.Model, x->second.X, x->second.Y, x->second.Z, 1, (unsigned __int64)0, 0);
			}
		}

		IPlayer.UpdateBuff(BuffNames::NPCSummon, BuffNames::BuffTime, NPCID);
	}
}

bool isIPEnabled() {
	return (IPEnable == 1) ? true : false;
}

void __fastcall MyOnTeleport(void *Player, void *edx, int Argument, int Value)
{
	CreateFakePlayers(Player);
	ShowSummonedNPCs(Player);
	IChar IPlayer((void*)Player);
	IPlayer.UpdateBuff(BuffNames::SpeedCheckX, BuffNames::BuffTime, 0);
	IPlayer.UpdateBuff(BuffNames::SpeedCheckY, BuffNames::BuffTime, 0);
	int OldMap = IPlayer.GetMap();
	int OldMapX = IPlayer.GetX() >> 13;
	int OldMapY = IPlayer.GetY() >> 13;

	CPlayer::OnTeleport(Player, Argument, Value);

	if (IPlayer.GetBuffValue(BuffNames::MacroMap)) {
		int MapX = IPlayer.GetX() >> 13;
		int MapY = IPlayer.GetY() >> 13;
		if (!(MapX == OldMapX && MapY == OldMapY))
			IPlayer.UpdateBuff(BuffNames::MacroMap, BuffNames::BuffTime, 0);
	}

	int NewMap = IPlayer.GetMap();
	if (OldMap != NewMap) {
		if (OldMap == LawlessMap) {
			int EXP = IPlayer.GetBuffValue(BuffNames::LawlessEXP);
			if (EXP) {
				IPlayer.RemoveFxBone("expgrade" + Int2String(EXP));
				IPlayer.UpdateBuff(BuffNames::LawlessPoints, BuffNames::BuffTime, 0);
				IPlayer.UpdateBuff(BuffNames::LawlessEXP, BuffNames::BuffTime, 0);
			}

			IPlayer.CloseScenario3_3Score();
			/// UPDATED WRITEINMAP
			if (!IPlayer.GetAdmin()) {
				std::string msg = (std::string)IPlayer.GetName() + " has left.";
				CPlayer::WriteAll(0xFE, "dds", 178, TEXTCOLOR_RED, msg.c_str());
				ToNoticeWebhook(msg.c_str());
			}

			IPlayer.CancelBuff(BuffNames::LawlessPort);
			IPlayer.SystemMessage("You have left the Chaos zone.", TEXTCOLOR_YELLOW);
		}

		if (NewMap == LawlessMap) {
			if (!IPlayer.GetAdmin()) {
				std::string msg = (std::string)IPlayer.GetName() + " has entered.";
				CPlayer::WriteAll(0xFE, "dds", 178, TEXTCOLOR_GREEN, msg.c_str());
				ToNoticeWebhook(msg.c_str());
			}
			IPlayer.UpdateBuff(BuffNames::LawlessEXP, BuffNames::BuffTime, 0);
			IPlayer.UpdateBuff(BuffNames::LawlessPoints, BuffNames::BuffTime, 0);
			CPlayer::Write(Player, 0xFF, "ds", 234, "You have entered the Chaos zone.");
		}

		if (NewMap == EmokMap)
			IPlayer.CancelBuff(BuffNames::EmokTeleport);
	}
}

int __fastcall OutOfInv(void *Player, void *edx, int Item)
{
	IItem IItem((void*)Item);
	IChar IPlayer(Player);
	if (IPlayer.IsOnline() && IItem.Exists())
		return CItem::RemoveItem(Player, Item);

	return 0;
}

int isPeaceEvilMode() {
	return PeaceEvil;
}

void PortToStart(void* Player) {
	IChar IPlayer(Player);

	if (PeaceEvil) {
		if (IPlayer.isSlytherin())
			IPlayer.Teleport(0, SlytherinDieX, SlytherinDieY);
		else if (IPlayer.isRavenclaw())
			IPlayer.Teleport(0, RavenDieX, RavenDieY);
		else if (IPlayer.isHufflepuff())
			IPlayer.Teleport(0, HuffleDieX, HuffleDieY);
		else if (IPlayer.isGryffindor())
			IPlayer.Teleport(0, GryffindorDieX, GryffindorDieY);
	}
	else
		IPlayer.Teleport(0, 257514, 259273);
}

void __fastcall MyGameStart(void *Player, void *edx)
{
	IChar IPlayer(Player);

	if (IPlayer.IsOnline())
	{
		if (IPlayer.GetX() < 0 || IPlayer.GetY() < 0 || IPlayer.GetZ() < 0)
		{
			IPlayer.SetX(257514);
			IPlayer.SetY(259273);
			IPlayer.SetZ(16168);
			SaveAllProperty((int)Player, 0, 0);
			IPlayer.Kick();
			return;
		}

		CreateFakePlayers(Player);
		ShowSummonedNPCs(Player);

		int Pet1 = IPlayer.GetBuffValue(BuffNames::PetOwner);
		int Pet2 = IPlayer.GetBuffValue(BuffNames::PetOwner2);
		int Pet3 = IPlayer.GetBuffValue(BuffNames::PetOwner3);
		int PetIID1 = IPlayer.GetBuffValue(BuffNames::PetIID);
		int PetIID2 = IPlayer.GetBuffValue(BuffNames::PetIID2);
		int PetIID3 = IPlayer.GetBuffValue(BuffNames::PetIID3);

		SendCreate create = SendCreate();
		create.Riding = IPlayer.GetBuffValue(349);
		create.NamePad = IPlayer.GetBuffValue(BuffNames::NamePad);
		create.ArmorWears = IPlayer.GetBuffValue(BuffNames::ArmorWears);
		create.CustWear = IPlayer.GetBuffValue(BuffNames::custWeap);
		create.SuitUsing = IPlayer.GetBuffValue(BuffNames::SuitsUsing);
		create.WepWear = IPlayer.GetBuffValue(BuffNames::WeaponWear);
		create.CostumeEffect = IPlayer.GetBuffValue(BuffNames::CostumeEffect);
		create.CostumeEffectCheck = IPlayer.GetBuffValue(BuffNames::CostumeEffectCheck);
		create.Pet1 = Pet1;
		create.Pet2 = Pet2;
		create.Pet3 = Pet3;
		create.PetIID1 = PetIID1;
		create.PetIID2 = PetIID2;
		create.PetIID3 = PetIID3;
		create.LawlessEXP = 0;
		create.GState = (TriangularBattle::Active || TriangularBattle::CDActive) ? IPlayer.GetBuffValue(BuffNames::TriangularState) : 0;
		SendCreatePlayer.replaceInsert((int)Player, create);

		CPlayer::Write(Player, 0xFE, "ddd", 181, ShopLevelLimit, TradeLevelLimit);

		CPlayer::GameStart(Player);

		if (IPlayer.IsOnline())
		{
			CDBSocket::Write(93, "d", IPlayer.GetPID());
			CDBSocket::Write(92, "d", IPlayer.GetPID());
			CDBSocket::Write(116, "d", IPlayer.GetPID());
			CDBSocket::Write(125, "dd", 3, IPlayer.GetPID());
			CDBSocket::Write(125, "dd", 6, IPlayer.GetPID());

			if (DefaultUnblob)
				IPlayer.SetUnblob(1);

			if (RebornActive)
				CDBSocket::Write(120, "d", IPlayer.GetPID());

			IPlayer.CancelBuff(104);

			if (IPlayer.GetLevel() == 1){
				CDBSocket::Write(110, "d", IPlayer.GetPID());
				if (BattlepassActive)
					CDBSocket::Write(122, "dd", IPlayer.GetPID(), 2);
			}

			if (BattlepassActive)
				CDBSocket::Write(122, "dd", IPlayer.GetPID(), 1);

			if (DuelNames.count(IPlayer.GetPID())) {
				std::string NameNew = (std::string)IPlayer.GetName();
				std::string NameOld = DuelNames.find(IPlayer.GetPID())->second;
				if (NameOld != NameNew) {
					DuelNames.replaceInsert(IPlayer.GetPID(), NameNew);
					if (AllFights.empty()) {
						bool changed = false;
						for (int i = 1; i <= 8; i++) {
							if (changed)
								break;
							if (DuelRegistrationList.count(i)) {
								std::vector<DuelRegistre> &RList = DuelRegistrationList.find(i)->second;
								for (auto x = RList.begin(); x != RList.end(); x++) {
									if (x->PID == IPlayer.GetPID()) {
										x->Name = NameNew;
										changed = true;
										break;
									}
								}
							}
						}
					}
					else {
						bool changed = false;
						for (int i = 1; i <= 8; i++) {

							if (changed)
								break;

							if (AllFights.count(i)) {
								std::vector<TOURNAMENT_PARTY> &RList = AllFights.find(i)->second;
								for (auto x = RList.begin(); x != RList.end(); x++) {
									std::string Name(x->szName[0]);
									if (Name == " " + NameOld) {
										std::string Names = NameNew.size() < 21 ? " " + NameNew : NameNew;
										if (Names.size() < 21) {
											int nSize = Names.size();
											for (int k = 0; k < 21; k++) {
												if (k >= nSize)
													x->szName[0][k] = '\0';
												else
													x->szName[0][k] = Names[k];
											}
										}
										changed = true;
										break;
									}
								}
							}
						}
					}

					string line;

					ifstream fin;
					fin.open("./Database/Duel.db");
					ofstream temp;
					temp.open("./Database/tempduel.txt");

					while (getline(fin, line))
					{
						int type = 0, pid = 0;
						if (sscanf(line.c_str(), "(registration (type %d)(PID %d)", &type, &pid) == 2)
						if (pid != IPlayer.GetPID())
							temp << line << endl;
						else
							temp << "(registration (type " << IPlayer.GetDTArena() << ")(PID " << IPlayer.GetPID() << ")(name '" << IPlayer.GetName() << "')(class " << IPlayer.GetClass() << ")(level " << IPlayer.GetLevel() << "))" << std::endl;
					}

					temp.close();
					fin.close();
					remove("./Database/Duel.db");
					rename("./Database/tempduel.txt", "./Database/duel.db");
				}
			}

			std::string IPAddress = IPlayer.GetIP();
			if (loginDebug == 1) {
				std::string PC = "none";
				std::string MAC = "none";
				if (User.count(IPlayer.GetPID())) {
					PC = User.find(IPlayer.GetPID())->second.PCName;
					MAC = User.find(IPlayer.GetPID())->second.MAC;
				}
				std::string Date = "./Debugger/Login/IP_LOG_" + Time::GetDay() + "_" + Time::GetMonth() + "_" + Time::GetYear() + ".txt";
				std::fstream IPLOG;
				IPLOG.open(Date, std::fstream::in | std::fstream::out | std::fstream::app);
				IPLOG << Time::GetTime() << IPlayer.GetName() << " - " << IPAddress << " - " << PC << " - " << MAC << std::endl;
				IPLOG.close();
			}

			IPlayer.Buff(BuffNames::IPAddress, BuffNames::BuffTime, sha256(IPAddress));

			if (PeaceEvil) {
				int Color = PECGryffindor;
				std::string lMsg = GryffindorLoginMSG;
				if (IPlayer.isSlytherin()) {
					lMsg = SlytherinLoginMSG;
					Color = PECSlytherin;
				}

				if (IPlayer.isRavenclaw()) {
					lMsg = RavenclawLoginMSG;
					Color = PECRavenclaw;
				}

				if (IPlayer.isHufflepuff()) {
					lMsg = HufflepuffLoginMSG;
					Color = PECHufflepuff;
				}
				size_t sizeOf = lMsg.find("$playername");
				if (sizeOf != std::string::npos)
					lMsg.replace(sizeOf, sizeof("$playername") - 1, IPlayer.GetName());

				CPlayer::Write(IPlayer.GetOffset(), 0xFF, "dsd", 247, lMsg.c_str(), Color);
			}

			if (MD5Check == 1) {
				if (!IPlayer.IsBuff(3076)) {
					IPlayer.SystemMessage("Illegal Files detected. Re-extract your client", TEXTCOLOR_RED);
					IPlayer.Kick();
					return;
				}
				else
					IPlayer.CancelBuff(3076);
			}

			if (IPlayer.IsOnline() && IPlayer.GetLevel() < 81)
				CPlayer::Write(IPlayer.GetOffset(), 178, "db", IPlayer.GetID(), 0);

			if (IPlayer.IsOnline() && IPlayer.GetLevel() >= 81 && IPlayer.GetLevel() <= 85)
				CPlayer::Write(IPlayer.GetOffset(), 178, "db", IPlayer.GetID(), 1);

			if (IPlayer.IsOnline() && IPlayer.GetLevel() >= 86 && IPlayer.GetLevel() <= 90)
				CPlayer::Write(IPlayer.GetOffset(), 178, "db", IPlayer.GetID(), 2);

			if (IPlayer.IsOnline() && IPlayer.GetLevel() >= 91)
				CPlayer::Write(IPlayer.GetOffset(), 178, "db", IPlayer.GetID(), 3);

			if (IPlayer.IsOnline() && IPlayer.GetClass() == 3 && IPlayer.GetLevel() == 1 && !CPlayer::FindItem(IPlayer.GetOffset(), 1404, 1))
				CItem::InsertItem((int)IPlayer.GetOffset(), 27, 1404, 0, 1, -1);

			if (IPlayer.IsOnline() && IPlayer.GetClass() == 4 && IPlayer.GetLevel() == 1 && !CPlayer::FindItem(IPlayer.GetOffset(), 7200, 1))
				CItem::InsertItem((int)IPlayer.GetOffset(), 27, 7200, 0, 1, -1);

			if (IPlayer.IsOnline() && Pet1)
			{
				if (Pet1 >= 2004 && Pet1 <= 2007)
					CPlayer::Write(IPlayer.GetOffset(), 221, "dwdb", IPlayer.GetID(), (unsigned short)Pet1, PetIID1, 2);
				else
					CPlayer::Write(IPlayer.GetOffset(), 221, "dwdb", IPlayer.GetID(), (unsigned short)Pet1, PetIID1, 0);
			}

			if (IPlayer.IsOnline() && Pet2)
				CPlayer::Write(IPlayer.GetOffset(), 221, "dwdb", IPlayer.GetID(), (unsigned short)Pet2, PetIID2, 0);

			if (IPlayer.IsOnline() && Pet3)
				CPlayer::Write(IPlayer.GetOffset(), 221, "dwdb", IPlayer.GetID(), (unsigned short)Pet3, PetIID3, 0);

			int HonorP = IPlayer.GetHonorTag();
			if (HonorP > 0 || PeaceEvil == 1)
				CChar::WriteInSight(IPlayer.GetOffset(), 255, "dddd", 244, IPlayer.GetID(), (HonorP > 0) ? HonorP : 1, HonorMessageSys(IPlayer.GetOffset(), HonorP));

			if (IPlayer.IsOnline() && !IPlayer.GetAdmin() && maxAllowedSpeed)
				IPlayer.CheckSpeed(maxAllowedSpeed);


			// IP Restriction
			if (HWIDRestrictions.count(IPlayer.GetPID()))
			{
				std::string PC = "";
				std::string MAC = "";
				std::string HWID = "";
				if (User.count(IPlayer.GetPID())) {
					UserInfo userInfo = User.findValue(IPlayer.GetPID());
					PC = userInfo.PCName;
					MAC = userInfo.MAC;
					HWID = userInfo.Hardware;
				}

				const char* playerHWID = HWID.c_str();
				const std::string& allowedHWIDs = HWIDRestrictions.find(IPlayer.GetPID())->second.HWIDs;

				if (allowedHWIDs.find(playerHWID) == std::string::npos)
				{
					IPlayer.SystemMessage("Illegal credentials. You are not allowed to log in this account!", TEXTCOLOR_RED);
					IPlayer.Kick();
					return;
				}
			}

			//if (IPlayer.IsBuff(BuffNames::DailyDuty)){
			//	int QValue = IPlayer.GetBuffValue(BuffNames::DailyDuty);
			//	if (DutyQuest.count(QValue)){
			//		int questIndex = (QValue << 16) + 1;
			//		int missionProgress = IPlayer.GetBuffValue(BuffNames::NormalDuty);
			//		int BossMissionProgress = IPlayer.GetBuffValue(BuffNames::MiniBoss);
			//		int InstanceMissionProgress = IPlayer.GetBuffValue(BuffNames::InstanceDuty);

			//		CPlayer::Write(IPlayer.GetOffset(), 184, "ddd", questIndex, 5000, missionProgress);
			//		CPlayer::Write(IPlayer.GetOffset(), 184, "ddd", questIndex, 5001, BossMissionProgress);
			//		CPlayer::Write(IPlayer.GetOffset(), 184, "ddd", questIndex, 5002, InstanceMissionProgress);
			//	}
			//}

			int CostumeEffect = IPlayer.GetBuffValue(BuffNames::CostumeEffect);
			if (CostumeEffect)
				CPlayer::Write(IPlayer.GetOffset(), 0xFE, "ddd", 186, IPlayer.GetID(), CostumeEffect);

			if (create.NamePad)
				CChar::WriteInSight((void*)Player, 0xFE, "ddd", 209, IPlayer.GetID(), create.NamePad);

			if (create.CustWear && create.WepWear && CostWeaponsEffects.count(create.CustWear))
				CPlayer::Write(IPlayer.GetOffset(), 0xFE, "ddsd", 177, IPlayer.GetID(), IPlayer.CostEffect(CostWeaponsEffects.find(create.CustWear)->second).c_str(), 1);

			if (IPlayer.IsBuff(120))
			{
				IPlayer.Buff(259, 604800, 0);
				IPlayer.SetBuffIcon(IPlayer.GetBuffRemain(120) * 1000, 0, 3691, 423);
				CPlayer::Write(Player, 0xFF, "dd", 238, 0);
			}

			if (IPlayer.IsBuff(119))
			{
				IPlayer.Buff(260, 604800, 0);
				IPlayer.SetBuffIcon(IPlayer.GetBuffRemain(119) * 1000, 0, 3511, 370);
			}


			if (DailyLogin)
				CDBSocket::Write(100, "dddddddss", 1, IPlayer.GetUID(), (int)IPlayer.GetOffset(), String2Int(Time::GetMonth()), String2Int(Time::GetDay()), DailyLoginLimit, IPCheck, IPAddress.c_str(), IPlayer.GetHWID().c_str());

			CPlayer::Write(Player, 0xFE, "dwdd", 199, 1, IPlayer.GetBuffValue(BuffNames::RidingIID), 1728 * IPlayer.GetBuffValue(BuffNames::Satiety));

			if (!RidingCollections.empty()) {
				for (auto x = RidingCollections.begin(); x != RidingCollections.end(); x++)
				{
					RidingCollection ridingCollection = x->second;
					bool isCollection = !ridingCollection.Indexes.empty();

					for (int i = 0; i < ridingCollection.Indexes.size(); i++) {
						if (!CPlayer::FindItem(Player, ridingCollection.Indexes[i], 1)) {
							isCollection = false;
							break;
						}
					}

					if (isCollection)
						updateRidingCollection(Player, x->first, 1, ridingCollection.Stat, ridingCollection.Rate);
				}
			}

			if (Snow >= 1 && Snow <= 3) {
				int kSnow = Snow;
				if (Snow == 3)
					kSnow = 4;
				CPlayer::Write(Player, 68, "bIdd", 74, 16 * kSnow, 0, 1000, 0);
			}

			if (IPlayer.IsBuff(BuffNames::Mute))
				IPlayer.setMuted(IPlayer.GetBuffRemain(BuffNames::Mute));
			if (IPlayer.IsBuff(BuffNames::Jail))
				IPlayer.setMuted(IPlayer.GetBuffRemain(BuffNames::Jail));

			IPlayer.Buff(3723, 10, 0);
		}

	}

	if (IPlayer.IsOnline() && CGuild::IsWarringPeriod()) {
		int Guild = CPlayer::GetGuild((int)IPlayer.GetOffset());
		if (Guild) {
			if (CCastle::IsAllCastleWarRelation(Guild)) {
				IPlayer.SetProperty(PlayerProperty::CWPlayer, 1);
				CChar::WriteInSight(Player, 46, "dI", IPlayer.GetID(), (__int64)*(DWORD *)((int)Player + 280));
			}
			CSkill::ObjectRelease((void*)Guild, (LONG)(Guild + 40));
		}
	}

	if (SufferingValley::Active && IPlayer.GetMap() == SVMap) {
		int PID = IPlayer.GetPID();
		bool IsBlue = SVParticipantsBlue.count(PID);
		bool IsRed = !IsBlue ? SVParticipantsRed.count(PID) : false;
		CPlayer::Write(IPlayer.GetOffset(), 46, "dI", IPlayer.GetID(), __int64(0x20000 << (IsBlue ? 1 : 0)) << 32);
	}

	//New Forest
	UpdateNewMyst(Player);
	UpdateHonorStats(Player);
	if (!DefaultSkinView){
		IPlayer.setSkinView(IPlayer.IsHide() ? -2 : 1);

		if (IPlayer.GetBuffValue(BuffNames::SuitsUsing))
			CPlayer::Write(IPlayer.GetOffset(), 6, "ddw", IPlayer.GetID(), 0, IPlayer.GetBuffValue(BuffNames::SuitsUsing));
		int custWeap = IPlayer.GetBuffValue(BuffNames::custWeap);
		if (custWeap) {
			CPlayer::Write(IPlayer.GetOffset(), 6, "ddw", IPlayer.GetID(), 0, custWeap);
			if (CostWeaponsEffects.count(custWeap)) {
				if (IPlayer.GetClass() == 3)
					CPlayer::Write(IPlayer.GetOffset(), 0xFE, "dds", 176, IPlayer.GetID(), IPlayer.CostEffect(CostWeaponsEffects.find(custWeap)->second).c_str());
				CPlayer::Write(IPlayer.GetOffset(), 0xFE, "dds", 176, IPlayer.GetID(), IPlayer.CostEffect(CostWeaponsEffects.find(custWeap)->second).c_str());
			}
		}
	}
	//CChar::WriteInSight(Player, 46, "dI", IPlayer.GetID(), __int64(0x200000));
}

void __fastcall MySendCreate(void *Player, void *edx, int Object, void *Argument)
{
	IChar IPlayer(Player);
	IChar IObject((void*)Object);

	if (IPlayer.GetChannel() != IObject.GetChannel())
		return;

	if (!Argument)
		return;

	bool Check = IPlayer.IsHide();

	if (!Check)
		CPlayer::SendCreate(Player, Object, Argument);
	else {
		if (IPlayer.GetOffset() != IObject.GetOffset()) {
			CPlayer::Send((int)Player, (int)Argument);
			if (*(DWORD *)(Object + 260))
				CPlayer::Write(Player, 72, "dbw", IObject.GetID(), 32, *(DWORD *)(Object + 260));
		}
	}

	if (IPlayer.IsOnline() && IObject.IsOnline() && IPlayer.GetOffset() != IObject.GetOffset() && IPlayer.GetType() == 0 && IObject.GetType() == 0)
	{
		if (IPlayer.GetLevel() < 81 && !Check)
			CPlayer::Write(IObject.GetOffset(), 178, "db", IPlayer.GetID(), 0);

		if (IPlayer.GetLevel() >= 81 && IPlayer.GetLevel() <= 85 && !Check)
			CPlayer::Write(IObject.GetOffset(), 178, "db", IPlayer.GetID(), 1);

		if (IPlayer.GetLevel() >= 86 && IPlayer.GetLevel() <= 90 && !Check)
			CPlayer::Write(IObject.GetOffset(), 178, "db", IPlayer.GetID(), 2);

		if (IPlayer.GetLevel() >= 91 && !Check)
			CPlayer::Write(IObject.GetOffset(), 178, "db", IPlayer.GetID(), 3);

		if (IObject.GetLevel() < 81)
			CPlayer::Write(IPlayer.GetOffset(), 178, "db", IObject.GetID(), 0);

		if (IObject.GetLevel() >= 81 && IObject.GetLevel() <= 85)
			CPlayer::Write(IPlayer.GetOffset(), 178, "db", IObject.GetID(), 1);

		if (IObject.GetLevel() >= 86 && IObject.GetLevel() <= 90)
			CPlayer::Write(IPlayer.GetOffset(), 178, "db", IObject.GetID(), 2);

		if (IObject.GetLevel() >= 91)
			CPlayer::Write(IPlayer.GetOffset(), 178, "db", IObject.GetID(), 3);

		int HonorP = IPlayer.GetHonorTag();
		int HonorO = IObject.GetHonorTag();

		if ((IPlayer.GetMap() != LawlessMap && HonorO > 0) || (PeaceEvil == 1))
			CPlayer::Write(IPlayer.GetOffset(), 255, "dddd", 244, IObject.GetID(), (HonorO > 0) ? HonorO : 1, HonorMessageSys(IObject.GetOffset(), HonorO));

		if (((IObject.GetMap() != LawlessMap && HonorP > 0) || (PeaceEvil == 1)) && !Check)
			CPlayer::Write(IObject.GetOffset(), 255, "dddd", 244, IPlayer.GetID(), (HonorP > 0) ? HonorP : 1, HonorMessageSys(IPlayer.GetOffset(), HonorP));

		SendCreate playerCreate = SendCreatePlayer.findValue((int)Player);
		SendCreate objectCreate = SendCreatePlayer.findValue(Object);

		int Riding = playerCreate.Riding;
		int RidingO = objectCreate.Riding;
		int NamePad = playerCreate.NamePad;
		int NamePadO = objectCreate.NamePad;
		int SuitUsing = playerCreate.SuitUsing;
		int SuitUsingO = objectCreate.SuitUsing;
		int SkinView = IPlayer.isSkinView();
		SkinView = (SkinView == -1) ? 0 : SkinView;
		int SkinViewO = IObject.isSkinView();
		SkinViewO = (SkinViewO == -1) ? 0 : SkinViewO;
		int WepWear = playerCreate.WepWear;
		int WepWearO = objectCreate.WepWear;
		int CustWear = playerCreate.CustWear;
		int CustWearO = objectCreate.CustWear;
		int ArmorWears = playerCreate.ArmorWears;
		int ArmorWearsO = objectCreate.ArmorWears;
		int CostumeEffect = playerCreate.CostumeEffect;
		int CostumeEffectO = objectCreate.CostumeEffect;
		int CostumeEffectC = playerCreate.CostumeEffectCheck;
		int CostumeEffectCO = objectCreate.CostumeEffectCheck;
		int LawlessEXP = playerCreate.LawlessEXP;
		int LawlessEXPO = objectCreate.LawlessEXP;
		int IsInWarP = IPlayer.GetProperty(PlayerProperty::CWPlayer);
		int IsInWarO = IObject.GetProperty(PlayerProperty::CWPlayer);
		int ISTBBattle = playerCreate.GState;
		int ISTBBattleO = objectCreate.GState;

		if (Riding && !Check)
			CPlayer::Write(IObject.GetOffset(), 255, "ddd", 227, IPlayer.GetID(), Riding);

		if (RidingO)
			CPlayer::Write(IPlayer.GetOffset(), 255, "ddd", 227, IObject.GetID(), RidingO);

		if (NamePad && IPlayer.IsPVPValid() && !Check)
			CPlayer::Write(IObject.GetOffset(), 0xFE, "ddd", 209, IPlayer.GetID(), NamePad);

		if (NamePadO && IObject.IsPVPValid())
			CPlayer::Write(IPlayer.GetOffset(), 0xFE, "ddd", 209, IObject.GetID(), NamePadO);

		if (ArmorWears && !Check)
			CPlayer::Write(IObject.GetOffset(), 5, "ddw", IPlayer.GetID(), 0, (unsigned short)ArmorWears);

		if (ArmorWearsO)
			CPlayer::Write(IPlayer.GetOffset(), 5, "ddw", IObject.GetID(), 0, (unsigned short)ArmorWearsO);

		if (CostumeEffectC && !Check)
			CPlayer::Write(IObject.GetOffset(), 5, "ddw", IPlayer.GetID(), 0, (unsigned short)CostumeEffectC);

		if (CostumeEffectCO)
			CPlayer::Write(IPlayer.GetOffset(), 5, "ddw", IObject.GetID(), 0, (unsigned short)CostumeEffectCO);

		if (SuitUsing && !Check) {
			if (!SkinViewO)
				CPlayer::Write(IObject.GetOffset(), 5, "ddw", IPlayer.GetID(), 0, (unsigned short)SuitUsing);
			else
				CPlayer::Write(IObject.GetOffset(), 6, "ddw", IPlayer.GetID(), 0, (unsigned short)SuitUsing);
		}

		if (SuitUsingO) {
			if (!SkinView)
				CPlayer::Write(IPlayer.GetOffset(), 5, "ddw", IObject.GetID(), 0, (unsigned short)SuitUsingO);
			else
				CPlayer::Write(IPlayer.GetOffset(), 6, "ddw", IObject.GetID(), 0, (unsigned short)SuitUsingO);
		}

		if (WepWear && !Check)
			CPlayer::Write(IObject.GetOffset(), 5, "ddw", IPlayer.GetID(), 0, (unsigned short)WepWear);

		if (WepWearO)
			CPlayer::Write(IPlayer.GetOffset(), 5, "ddw", IObject.GetID(), 0, (unsigned short)WepWearO);

		if (CustWear && !Check) {
			if (!SkinViewO) {
				CPlayer::Write(IObject.GetOffset(), 5, "ddw", IPlayer.GetID(), 0, (unsigned short)CustWear);

				if (WepWear && CostWeaponsEffects.count(CustWear))
					CPlayer::Write(IObject.GetOffset(), 0xFE, "ddsd", 177, IPlayer.GetID(), IPlayer.CostEffect(CostWeaponsEffects.find(CustWear)->second).c_str(), 1);
			}
			else {
				CPlayer::Write(IObject.GetOffset(), 6, "ddw", IPlayer.GetID(), 0, (unsigned short)CustWear);

				if (CostWeaponsEffects.count(CustWear)) {
					if (IPlayer.GetClass() == 3)
						CPlayer::Write(IObject.GetOffset(), 0xFE, "dds", 176, IPlayer.GetID(), IPlayer.CostEffect(CostWeaponsEffects.find(CustWear)->second).c_str());
					CPlayer::Write(IObject.GetOffset(), 0xFE, "dds", 176, IPlayer.GetID(), IPlayer.CostEffect(CostWeaponsEffects.find(CustWear)->second).c_str());
				}
			}
		}

		if (CustWearO) {
			if (!SkinView) {
				CPlayer::Write(IPlayer.GetOffset(), 5, "ddw", IObject.GetID(), 0, (unsigned short)CustWearO);
				if (WepWearO && CostWeaponsEffects.count(CustWearO))
					CPlayer::Write(IPlayer.GetOffset(), 0xFE, "ddsd", 177, IObject.GetID(), IObject.CostEffect(CostWeaponsEffects.find(CustWearO)->second).c_str(), 1);
			}
			else {
				CPlayer::Write(IPlayer.GetOffset(), 6, "ddw", IObject.GetID(), 0, (unsigned short)CustWearO);

				if (CostWeaponsEffects.count(CustWearO)) {
					if (IObject.GetClass() == 3)
						CPlayer::Write(IPlayer.GetOffset(), 0xFE, "dds", 176, IObject.GetID(), IObject.CostEffect(CostWeaponsEffects.find(CustWearO)->second).c_str());
					CPlayer::Write(IPlayer.GetOffset(), 0xFE, "dds", 176, IObject.GetID(), IObject.CostEffect(CostWeaponsEffects.find(CustWearO)->second).c_str());
				}
			}
		}

		if (IObject.GetMap() == LawlessMap && IPlayer.GetMap() == LawlessMap) {
			if (LawlessEXPO) {
				std::string expgrade = "expgrade" + Int2String(LawlessEXPO);
				CPlayer::Write(IPlayer.GetOffset(), 0xFE, "ddsd", 177, IObject.GetID(), expgrade.c_str(), 0);
			}

			if (LawlessEXP && !Check) {
				std::string expgrade = "expgrade" + Int2String(LawlessEXP);
				CPlayer::Write(IObject.GetOffset(), 0xFE, "ddsd", 177, IPlayer.GetID(), expgrade.c_str(), 0);
			}

			if (IPlayer.IsParty() && IPlayer.GetPartyID() == IObject.GetPartyID()) {
				CPlayer::Write(IPlayer.GetOffset(), 46, "dI", IObject.GetID(), __int64(0x00040000) << 32);

				if (!Check)
					CPlayer::Write(IObject.GetOffset(), 46, "dI", IPlayer.GetID(), __int64(0x00040000) << 32);
			}
			else {
				CPlayer::Write(IPlayer.GetOffset(), 46, "dI", IObject.GetID(), __int64(0x00020000) << 32);
				if (!Check)
					CPlayer::Write(IObject.GetOffset(), 46, "dI", IPlayer.GetID(), __int64(0x00020000) << 32);
			}
		}

		if (CostumeEffect && !Check)
			CPlayer::Write(IObject.GetOffset(), 0xFE, "ddd", 185, IPlayer.GetID(), CostumeEffect);

		if (CostumeEffectO)
			CPlayer::Write(IPlayer.GetOffset(), 0xFE, "ddd", 185, IObject.GetID(), CostumeEffectO);

		int Pet1 = playerCreate.Pet1;
		if (Pet1 && (!PetTime.count(Pet1) || !PetTime.find(Pet1)->second.Monster) && !Check)
		{
			if (Pet1 >= 2004 && Pet1 <= 2007)
				CPlayer::Write(IObject.GetOffset(), 221, "dwdb", IPlayer.GetID(), (unsigned short)Pet1, playerCreate.PetIID1, 2);
			else
				CPlayer::Write(IObject.GetOffset(), 221, "dwdb", IPlayer.GetID(), (unsigned short)Pet1, playerCreate.PetIID1, 0);
		}

		int OPet1 = objectCreate.Pet1;
		if (OPet1 && (!PetTime.count(OPet1) || !PetTime.find(OPet1)->second.Monster))
		{
			if (OPet1 >= 2004 && OPet1 <= 2007)
				CPlayer::Write(IPlayer.GetOffset(), 221, "dwdb", IObject.GetID(), (unsigned short)OPet1, objectCreate.PetIID1, 2);
			else
				CPlayer::Write(IPlayer.GetOffset(), 221, "dwdb", IObject.GetID(), (unsigned short)OPet1, objectCreate.PetIID1, 0);
		}

		int Pet2 = playerCreate.Pet2;
		if (Pet2 && (!PetTime.count(Pet2) || !PetTime.find(Pet2)->second.Monster) && !Check)
			CPlayer::Write(IObject.GetOffset(), 221, "dwdb", IPlayer.GetID(), (unsigned short)Pet2, playerCreate.PetIID2, 0);

		int OPet2 = objectCreate.Pet2;
		if (OPet2 && (!PetTime.count(OPet2) || !PetTime.find(OPet2)->second.Monster))
			CPlayer::Write(IPlayer.GetOffset(), 221, "dwdb", IObject.GetID(), (unsigned short)OPet2, objectCreate.PetIID2, 0);

		int Pet3 = playerCreate.Pet3;
		if (Pet3 && (!PetTime.count(Pet3) || !PetTime.find(Pet3)->second.Monster) && !Check)
			CPlayer::Write(IObject.GetOffset(), 221, "dwdb", IPlayer.GetID(), (unsigned short)Pet3, playerCreate.PetIID3, 0);

		int OPet3 = objectCreate.Pet3;
		if (OPet3 && (!PetTime.count(OPet3) || !PetTime.find(OPet3)->second.Monster))
			CPlayer::Write(IPlayer.GetOffset(), 221, "dwdb", IObject.GetID(), (unsigned short)OPet3, objectCreate.PetIID3, 0);

		if (IsInWarP && IsInWarO) {
			CPlayer::Write(IPlayer.GetOffset(), 46, "dI", IObject.GetID(), (__int64)*(DWORD *)((int)IObject.GetOffset() + 280));
			if (!Check)
				CPlayer::Write(IObject.GetOffset(), 46, "dI", IPlayer.GetID(), (__int64)*(DWORD *)((int)IPlayer.GetOffset() + 280));
		}

		if (IPlayer.GetMap() == TBMap && IObject.GetMap() == TBMap) {
			if (((ISTBBattleO & 0x200000) && (ISTBBattle & 0x200000)) || ((ISTBBattleO & 0x400000) && (ISTBBattle & 0x400000)) || ((ISTBBattleO & 0x800000) && (ISTBBattle & 0x800000))) {
				int GuildName = CPlayer::GetGuildName((int)IPlayer.GetOffset());
				int GuildNameO = CPlayer::GetGuildName((int)IObject.GetOffset());

				if (GuildNameO)
					CPlayer::Write(IPlayer.GetOffset(), 0xFE, "ddss", 169, IObject.GetID(), CPlayer::GetGuildClassTitle((int)IObject.GetOffset()), GuildNameO);

				if (GuildName && !Check)
					CPlayer::Write(IObject.GetOffset(), 0xFE, "ddss", 169, IPlayer.GetID(), CPlayer::GetGuildClassTitle((int)IPlayer.GetOffset()), GuildName);
			}

			CPlayer::Write(IPlayer.GetOffset(), 145, "dI", IObject.GetID(), __int64(ISTBBattleO));
			if (!Check)
				CPlayer::Write(IObject.GetOffset(), 145, "dI", IPlayer.GetID(), __int64(ISTBBattle));
		}

		if (IPlayer.GetMap() == LMSMap && IObject.GetMap() == LMSMap) {
			CPlayer::Write(IPlayer.GetOffset(), 46, "dI", IObject.GetID(), __int64(0x20000) << 32);
			if (!Check)
				CPlayer::Write(IObject.GetOffset(), 46, "dI", IPlayer.GetID(), __int64(0x20000) << 32);
		}

		if (IPlayer.GetMap() == SVMap && IObject.GetMap() == SVMap) {
			bool PIsBlue = SVParticipantsBlue.count(IPlayer.GetPID());
			bool PIsRed = !PIsBlue ? SVParticipantsRed.count(IPlayer.GetPID()) : false;

			if (!Check)
				CPlayer::Write(IObject.GetOffset(), 46, "dI", IPlayer.GetID(), __int64(0x20000 << (PIsBlue ? 1 : 0)) << 32);

			PIsBlue = SVParticipantsBlue.count(IObject.GetPID());
			PIsRed = !PIsBlue ? SVParticipantsRed.count(IObject.GetPID()) : false;

			CPlayer::Write(IPlayer.GetOffset(), 46, "dI", IObject.GetID(), __int64(0x20000 << (PIsBlue ? 1 : 0)) << 32);
		}
	}
}

int GetRemain(ConcurrentMap<int, PlayerBuffs> &p, int BuffID) {
	auto it = p.find(BuffID);
	return it != p.end() ? it->second.Remain : 0;
}

int GetValue(ConcurrentMap<int, PlayerBuffs> &p, int BuffID) {
	auto it = p.find(BuffID);
	return it != p.end() ? it->second.Value : 0;
}

void CancelBuff(IChar IPlayer, ConcurrentMap<int, PlayerBuffs> &p, int BuffID) {
	IPlayer.CancelBuff(BuffID);
	p.erase(BuffID);
}

void Buff(IChar IPlayer, ConcurrentMap<int, PlayerBuffs> &p, int BuffID, int Time, int Value) {
	IPlayer.Buff(BuffID, Time, Value);
	PlayerBuffs pBuff = PlayerBuffs();
	pBuff.Value = Value;
	pBuff.Remain = Time;
	p[BuffID] = pBuff;
}

void UpdateBuff(IChar IPlayer, ConcurrentMap<int, PlayerBuffs> &p, int BuffID, int Time, int Value) {
	IPlayer.UpdateBuff(BuffID, Time, Value);
	PlayerBuffs pBuff = PlayerBuffs();
	pBuff.Value = Value;
	pBuff.Remain = Time;
	p[BuffID] = pBuff;
}


int __fastcall Tick(void *Player, void *edx)
{
	//	RemoteLisansCheck();
	//if (!ScaniaLicense)
	//	exit(1);

	IChar IPlayer(Player);
	if (IPlayer.IsOnline() && IPlayer.GetPID()) {
		int MapX = 0;
		int MapY = 0;

		int PlayerBRefresh = IPlayer.GetRefreshCheck();
		if (!PlayerBRefresh)
			IPlayer.SetRefreshCheck(GetTickCount() + 990);

		if (PlayerBRefresh <= GetTickCount()) {
			CChar::RefreshBuff((int)Player);
			IPlayer.SetRefreshCheck(GetTickCount() + 990);
		}

		ConcurrentMap<int, PlayerBuffs> playerBuffs;

		getAllBuffs(Player, 0, playerBuffs);

		MapX = IPlayer.GetX() >> 13;
		MapY = IPlayer.GetY() >> 13;
		int playerMap = IPlayer.GetMap();
		int playerLvl = IPlayer.GetLevel();
		int RectX = IPlayer.GetRectX();
		int RectY = IPlayer.GetRectY();

		TBPlayerTick(IPlayer);
		SVPlayerTick(IPlayer);
		BuffMakerLoad(Player);

		if (AreasExpItems.count(playerMap)) {
			auto expAreaIterator = AreasExpItems.find(playerMap);
			if (expAreaIterator != AreasExpItems.end()) {
				AreaExpItem& expArea = expAreaIterator->second;
				if (expArea.time && playerMap == expArea.map) {
					if (IPlayer.ScaniaTimer(expArea.time) && CPlayer::FindItem(Player, expArea.item, 1)) {
						IPlayer.UpdateProperty(P_EXP, expArea.experience);
					}
				}
			}
		}

		if (IPlayer.IsBuff(82) && !IPlayer.GetAdmin() && IPlayer.GetBuffRemain(82) <= 1)
			IPlayer.CheckSpeed(maxAllowedSpeed);

		if (AreaCertMap.count(playerMap)) {
			Certificates area = AreaCertMap.find(playerMap)->second;
			int buffID = ((area.itemIndex * 2) + area.Map);

			if (!playerBuffs.count(buffID)) {
				IPlayer.PortToVillage();
				IPlayer.SystemMessage("Area Certificate expired. Renew to rejoin.", TEXTCOLOR_RED);
			}
		}

		if (Reborns.count(IPlayer.GetProperty(PlayerProperty::Reborn))) {
			Reborn rb = Reborns.find(IPlayer.GetProperty(PlayerProperty::Reborn))->second;

			if (rb.sbMsg && rb.sbKey) {
				int rbBuffID = (rb.sbKey + rb.sbMsg) * 15;

				if (playerBuffs.count(rbBuffID) && GetRemain(playerBuffs, rbBuffID) < 10) 
					IPlayer.UpdateSavedBuff(rbBuffID, BuffNames::BuffTime, 0, 0, 0);
			}
		}

		if (NewcomerActive && !IPlayer.IsBuff(BuffNames::NewComer) && playerLvl <= NewcomerLevel){

			IPlayer.Buff(BuffNames::NewComer, 86400, NewcomerValue);
			//	Buff(IPlayer, playerBuffs, BuffNames::NewComer, 86400, NewcomerValue);
			IPlayer.SetBuffIcon(-2, -1, 0, NewcomerSys);
		}

		if (IPlayer.IsBuff(BuffNames::NewComer) && playerLvl > NewcomerLevel)
		{
			IPlayer.CancelBuff(BuffNames::NewComer);
			//CancelBuff(IPlayer, playerBuffs, BuffNames::NewComer);
			IPlayer.RemoveBuffIcon(0, 0, 0, NewcomerSys);
		}

		const char* HonorEffects[] = { Honor1, Honor2, Honor3, Honor4, Honor5, Honor6, Honor7, Honor8, Honor9, Honor10 };

		int HonorP = IPlayer.GetHonorTag();
		if (HonorTimer && HonorP >= 1 && HonorP <= 10 && IPlayer.ScaniaTimer(HonorTimer)) {
			IPlayer.AddFxToTarget(HonorEffects[HonorP - 1], 1, 0, 0);
		}

		//F10 BuffSystem
		if (IPlayer.IsOnline() && IPlayer.IsBuff(BuffNames::F10Buff) && !IPlayer.IsBuff(BuffNames::F10BuffCancel)){
			IPlayer.AddStr(F10Str); IPlayer.AddHp(F10Hth); IPlayer.AddInt(F10Int);
			IPlayer.AddWis(F10Wis); IPlayer.AddAgi(F10Agi); IPlayer.AddMinAttack(F10Min);
			IPlayer.AddMaxAttack(F10Max); IPlayer.Buff(BuffNames::F10BuffCancel, 1800, 1);
		}

		if (IPlayer.IsOnline() && IPlayer.GetBuffRemain(BuffNames::F10Buff) < 2 && IPlayer.IsBuff(BuffNames::F10Buff))
		{
			IPlayer.RemoveStr(F10Str); IPlayer.RemoveHp(F10Hth); IPlayer.RemoveInt(F10Int);
			IPlayer.RemoveWis(F10Wis); IPlayer.RemoveAgi(F10Agi);
			IPlayer.RemoveMinAttack(F10Min); IPlayer.RemoveMaxAttack(F10Max);
		}


		/*
		if (IPlayer.IsOnline() && PeaceEvil && HouseRewardTime){
		IPlayer.AddHouseReward(HouseRewardTime, 1);
		}
		*/

		std::string TimeStr = Time::GetTime();

		if (IPlayer.GetMap() == LawlessMap && !playerBuffs.count(BuffNames::LawlessPort)) {
			if (IPlayer.IsValid() && !playerBuffs.count(104)) {
				Buff(IPlayer, playerBuffs, 104, BuffNames::BuffTime, 0);
				IPlayer.RemoveBuffIcon(0, 0, 548, 19);
				CPlayer::Write(Player, 46, "dI", IPlayer.GetID(), __int64(0x00040000) << 32);
				IPlayer.Teleport(IPlayer.GetMap(), IPlayer.GetX(), IPlayer.GetY());
			}

			if (IPlayer.isDead()) {
				if (playerBuffs.count(BuffNames::RevivalCheck)) {
					if (GetRemain(playerBuffs, BuffNames::RevivalCheck) <= 1) {
						IPlayer.Teleport(IPlayer.GetMap(), LawlessSpawnX, LawlessSpawnY);
						Buff(IPlayer, playerBuffs, 24, 6, 40);
						IPlayer.RemoveBuffIcon(0, 0, 703, 34);
						CChar::AddMState(IPlayer.GetOffset(), 0, 2147483648);
						IPlayer.SetBuffIcon(6000, 0, 1793, 201);
					}
					else
						IPlayer.SystemMessage("[Lawless] Reviving in " + Int2String(GetRemain(playerBuffs, BuffNames::RevivalCheck) - 1) + "...", TEXTCOLOR_DARKGREEN);
				}
				else {
					IPlayer.SystemMessage("[Lawless] Reviving in " + Int2String(LawlessReviveCD) + "...", TEXTCOLOR_DARKGREEN);
					IPlayer.Buff(BuffNames::RevivalCheck, LawlessReviveCD + 1, 0);
				}
			}
		}

		//wtf;
		//// Death Effect
		//if (IPlayer.isDead()) {
		//	IPlayer.AddFxToTarget("davi_M630_71", 0, 0, 1);
		//}

		if (playerBuffs.count(BuffNames::MissionBuff)){
			int currentMission = IPlayer.GetBuffValue(BuffNames::MissionBuff);
			if (!currentMission)
				currentMission = AutoMissionQuest;

			int questIndex = (currentMission << 16) + 1;
			int isQuestClear = CPlayer::CheckQuestClear((int)IPlayer.GetOffset(), static_cast<char>(currentMission));
			bool isQuest = (CPlayer::CheckQuestFlag((int)IPlayer.GetOffset(), questIndex) == true);

			if (!isQuestClear && isQuest)
				UpdateAutoMissionItem(IPlayer.GetOffset(), currentMission);
		}

		//EMOKBuffs
		if (playerBuffs.count(BuffNames::BuffHPDecrease))
			IPlayer.RemoveHp(GetValue(playerBuffs, BuffNames::BuffHPDecrease));

		if (playerBuffs.count(BuffNames::BeltBuff)) {
			int Belt = GetValue(playerBuffs, BuffNames::Belt);
			if (GetRemain(playerBuffs, BuffNames::BeltBuff) <= 2 && BeltBuffs.count(Belt)) {
				IPlayer.DecreaseMaxHp(GetValue(playerBuffs, BuffNames::BeltBuff));
				IPlayer.RemoveFxBone(BeltBuffs.find(Belt)->second.Effect);
				CancelBuff(IPlayer, playerBuffs, BuffNames::BeltBuff);
			}
		}

		if (playerBuffs.count(BuffNames::Emote)){
			int eFlag = GetValue(playerBuffs, BuffNames::Emote);
			const std::pair<std::string, int>& emoteData = EmoteSystem.find(eFlag)->second;
			const std::string& particle = emoteData.first;
			if (EmoteSystem.count(eFlag) && GetRemain(playerBuffs, BuffNames::Emote) <= 2)
			{
				IPlayer.RemoveFxBone(particle.c_str());
				CancelBuff(IPlayer, playerBuffs, BuffNames::Emote);
			}
		}

		int GID = IPlayer.GetGID();
		if (GID) {
			for (auto x = GuildBuffQuests.begin(); x != GuildBuffQuests.end(); x++) {
				long Index = uniqueKey(x->first, GID);
				if (ActiveGuildBuffs.count(Index)) {
					std::vector<GuildBuff> gBuffs = ActiveGuildBuffs.findValue(Index);
					int bCheck = gBuffs.size();
					int cAlive = 0;
					for (int i = 0; i < bCheck; i++) {
						GuildBuff gBuff = gBuffs[i];
						if (gBuff.Time > GetTickCount()) {
							if (!playerBuffs.count(gBuff.BuffID)) {
								Buff(IPlayer, playerBuffs, gBuff.BuffID, (gBuff.Time - GetTickCount()) / 1000, gBuff.Value);

								if (gBuff.SBKey && gBuff.SBName)
									IPlayer.SetBuffIcon(gBuff.Time - GetTickCount(), 0, gBuff.SBName, gBuff.SBKey);
							}
						}
						else
							cAlive++;
					}
					if (cAlive == bCheck)
						ActiveGuildBuffs.erase(Index);
				}
			}
		}

		if (WarEndTime && WarEndTime >= (int)time(0) && IPlayer.GetProperty(PlayerProperty::CWPlayer)) {
			if (!CWRLimit || !isRewarded(IPlayer)) {
				int PlayerGuild = CPlayer::GetGuild((int)IPlayer.GetOffset());
				if (PlayerGuild) {
					if (PlayerGuild == GuildWinnerCW){
						IPlayer.systemReward(CwRewardGuild);
						IPlayer.SaveBuff(BuffNames::CastleWarBuffW, 86400, 1, 14142, 14142);
					}
					else
					if (AllyWinnerCW && *(DWORD *)(PlayerGuild + 396) == AllyWinnerCW){
						IPlayer.systemReward(CwRewardAlly);
						IPlayer.SaveBuff(BuffNames::CastleWarBuffW, 86400, 1, 14142, 14142);
					}
					else
						IPlayer.systemReward(CwRewardOther);

					CSkill::ObjectRelease((void*)PlayerGuild, (LONG)(PlayerGuild + 40));
				}
				if (CWRLimit)
					rewardLimit(IPlayer);
			}
			IPlayer.SetProperty(PlayerProperty::CWPlayer, 0);
		}

		int AQuestCheck = GetValue(playerBuffs, BuffNames::AreaQuest);
		int MapIndex = IPlayer.GetMapIndex();
		if (AQuestCheck) {
			if (AreaQuests.count(AQuestCheck)) {
				AreaQuest aQuest = AreaQuests.find(AQuestCheck)->second;
				if (IPlayer.GetMap() != aQuest.TMap || !TimedMaps.count(MapIndex))
					IPlayer.Teleport(aQuest.TMap, aQuest.TX, aQuest.TY);

				if (aQuest.Party == 2 && IPlayer.IsParty())
					CPlayer::LeaveParty((int)Player);

				if ((aQuest.Party == 1 && !IPlayer.IsParty())) {
					CancelBuff(IPlayer, playerBuffs, BuffNames::AreaQuest);
					AQuestCheck = 0;
				}

				if (GetRemain(playerBuffs, BuffNames::AreaQuest) <= 1)
					IPlayer.Buff(2167, ACooldown + 1, AQuestCheck);
			}
		}

		if (!AQuestCheck && TimedMaps.count(MapIndex)) {
			IPlayer.Teleport(0, AQuestBackX, AQuestBackY);
			IPlayer.SystemMessage("You have been ported out of the timed area.", TEXTCOLOR_YELLOW);
			IPlayer.CloseScreenTime();
		}

		if (playerBuffs.count(BuffNames::PTVsPTRed)) {
			int Arena = GetValue(playerBuffs, BuffNames::PTVsPTRed);
			PartyBattle pBattle = CurPartys.find(Arena)->second;
			if (IPlayer.IsParty()) {
				int TimeLeft = (pBattle.Time - GetTickCount()) / 1000;
				IPlayer.SetRed();
				if (GetPTSize(IPlayer.GetPartyID()) == pBattle.PartySize) {
					IPlayer.Scenario3_3Score(TimeLeft, pBattle.RedScore, pBattle.BlueScore);
					if (IPlayer.isDead()) {
						if (playerBuffs.count(BuffNames::RevivalCheck)) {
							int NScore = pBattle.BlueScore + 1;
							IPlayer.Scenario3_3Score(TimeLeft, pBattle.RedScore, NScore);
							if (IsPartyAlive(IPlayer.GetPartyID(), 0))
							if (GetRemain(playerBuffs, BuffNames::RevivalCheck) <= 1) {
								IPlayer.Teleport(0, PartyArenas[0][Arena] + CTools::Rate(-200, 200), PartyArenas[1][Arena] + CTools::Rate(-200, 200));
								Buff(IPlayer, playerBuffs, 24, 3, 40);
								IPlayer.RemoveBuffIcon(0, 0, 703, 34);
								IPlayer.SetBuffIcon(3000, 0, 1793, 201);
								CurPartys[Arena].BlueScore = NScore;

							}
							else
								IPlayer.SystemMessage("[Party Arena] Reviving in " + Int2String(GetRemain(playerBuffs, BuffNames::RevivalCheck) - 1) + "...", TEXTCOLOR_DARKGREEN);
						}
						else {
							IPlayer.SystemMessage("[Party Arena] Reviving in " + Int2String(PartyReviveCD) + "...", TEXTCOLOR_DARKGREEN);
							IPlayer.Buff(BuffNames::RevivalCheck, PartyReviveCD + 1, 0);
						}
					}
				}
			}
			else {
				CancelBuff(IPlayer, playerBuffs, BuffNames::PTVsPTRed);
				IPlayer.Teleport(0, PartyPortBack[0][Arena], PartyPortBack[1][Arena]);
				IPlayer.RemoveSetBlue();
				IPlayer.CloseScenario3_3Score();
			}
		}

		if (playerBuffs.count(BuffNames::PTVsPTBlue)) {
			int Arena = GetValue(playerBuffs, BuffNames::PTVsPTBlue);
			PartyBattle pBattle = CurPartys.find(Arena)->second;
			if (IPlayer.IsParty()) {
				IPlayer.SetBlue();
				if (GetPTSize(IPlayer.GetPartyID()) == pBattle.PartySize) {
					IPlayer.Scenario3_3Score((pBattle.Time - GetTickCount()) / 1000, pBattle.RedScore, pBattle.BlueScore);
					if (IPlayer.isDead()) {
						if (playerBuffs.count(BuffNames::RevivalCheck)) {
							int NScore = pBattle.RedScore + 1;
							IPlayer.Scenario3_3Score((pBattle.Time - GetTickCount()) / 1000, NScore, pBattle.BlueScore);
							if (IsPartyAlive(IPlayer.GetPartyID(), 1))
							if (GetRemain(playerBuffs, BuffNames::RevivalCheck) <= 1) {
								IPlayer.Teleport(0, PartyArenas[0][Arena] + CTools::Rate(-200, 200), PartyArenas[1][Arena] + CTools::Rate(-200, 200));
								Buff(IPlayer, playerBuffs, 24, 3, 40);
								IPlayer.RemoveBuffIcon(0, 0, 703, 34);
								IPlayer.SetBuffIcon(3000, 0, 1793, 201);
								CurPartys[Arena].RedScore = NScore;

							}
							else
								IPlayer.SystemMessage("[Party Arena] Reviving in " + Int2String(GetRemain(playerBuffs, BuffNames::RevivalCheck) - 1) + "...", TEXTCOLOR_DARKGREEN);
						}
						else {
							IPlayer.SystemMessage("[Party Arena] Reviving in " + Int2String(PartyReviveCD) + "...", TEXTCOLOR_DARKGREEN);
							IPlayer.Buff(BuffNames::RevivalCheck, PartyReviveCD + 1, 0);
						}
					}
				}
			}
			else {
				CancelBuff(IPlayer, playerBuffs, BuffNames::PTVsPTBlue);
				IPlayer.Teleport(0, PartyPortBack[0][Arena], PartyPortBack[1][Arena]);
				IPlayer.RemoveSetBlue();
				IPlayer.CloseScenario3_3Score();
			}
		}

		if (playerBuffs.count(308) && !F10::Active)
			CancelBuff(IPlayer, playerBuffs, 308);

		int Channel = IPlayer.GetChannel();
		if (Channel) {
			if (Channel > ChannelActivated || !ChannelMaps.count((MapX * 1000) + MapY))
				IPlayer.SetChannelSystem(0);
		}

		if (GuildRaid::Active) {
			if (IPlayer.GetGID() == GuildRaid::GID && (MapX != 29 || MapY != 42)) {
				IPlayer.Teleport(0, 239381, 347811);
				IPlayer.ScreenTime(GuildRaid::Time - (int)time(0));

				if (playerBuffs.count(333))
					CancelBuff(IPlayer, playerBuffs, 333);

			}
			else
			if (IPlayer.GetGID() != GuildRaid::GID && MapX == 29 && MapY == 42)
				IPlayer.PortToVillage();
		}

		if ((GetTickCount() / 1000) % 2 == 0 && playerBuffs.count(414) && !playerBuffs.count(413))
		{
			int Value = GetValue(playerBuffs, 414);
			if (Value) {
				IPlayer.RemoveBuffIcon(0, 0, 9109, 1018);
				IPlayer.RemoveAgi(Value);
				IPlayer.RemoveStr(Value);
				IPlayer.RemoveHp(Value);
				IPlayer.RemoveInt(Value);
				IPlayer.RemoveWis(Value);
				CancelBuff(IPlayer, playerBuffs, 414);
			}
		}

		if ((GetTickCount() / 1000) % 2 == 0 && playerBuffs.count(410) && !playerBuffs.count(409))
		{
			IPlayer.RemoveBuffIcon(0, 0, 9107, 1016);
			IPlayer.DecreaseMaxHp(GetValue(playerBuffs, 410));
			CancelBuff(IPlayer, playerBuffs, 410);
		}

		if ((GetTickCount() / 1000) % 2 == 0 && playerBuffs.count(408) && !playerBuffs.count(407))
		{
			int Atk = GetValue(playerBuffs, 408);
			if (Atk) {
				IPlayer.RemoveBuffIcon(0, 0, 9108, 1017);
				IPlayer.RemoveMaxAttack(Atk);
				IPlayer.RemoveMinAttack(Atk);
				CancelBuff(IPlayer, playerBuffs, 408);
			}
		}

		if ((GetTickCount() / 1000) % 3 == 0 && playerBuffs.count(406) && !playerBuffs.count(405))
		{
			IPlayer.RemoveBuffIcon(0, 0, 9103, 1012);
			CancelBuff(IPlayer, playerBuffs, 406);
		}

		if ((GetTickCount() / 1000) % 3 == 0 && playerBuffs.count(402) && !playerBuffs.count(401))
		{
			IPlayer.RemoveBuffIcon(0, 0, 9104, 1013);
			IPlayer.DecreaseMaxHp(GetValue(playerBuffs, 402));
			CancelBuff(IPlayer, playerBuffs, 402);
		}

		if ((GetTickCount() / 1000) % 3 == 0 && playerBuffs.count(404) && !playerBuffs.count(403))
		{
			int Atk = GetValue(playerBuffs, 404);
			if (Atk) {
				IPlayer.RemoveBuffIcon(0, 0, 9105, 1014);
				IPlayer.RemoveMaxAttack(Atk);
				IPlayer.RemoveMinAttack(Atk);
				CancelBuff(IPlayer, playerBuffs, 404);
			}
		}

		if ((GetTickCount() / 1000) % 2 == 0 && playerBuffs.count(399) && playerBuffs.count(398))
		{
			int BuffTime = GetRemain(playerBuffs, 398);

			if (BuffTime >= 1 && BuffTime <= 5)
			{
				IPlayer.RemoveDef(1);
				IPlayer.RemoveAbsorb(1);
				CancelBuff(IPlayer, playerBuffs, 399);
				CancelBuff(IPlayer, playerBuffs, 398);
				IPlayer.RemoveBuffIcon(0, 0, 9101, 1010);
			}

			if (BuffTime >= 875 && BuffTime <= 880)
			{
				IPlayer.RemoveDef(2);
				IPlayer.RemoveAbsorb(2);
				CancelBuff(IPlayer, playerBuffs, 399);
				CancelBuff(IPlayer, playerBuffs, 398);
				IPlayer.RemoveBuffIcon(0, 0, 9101, 1010);
			}

			if (BuffTime >= 1815 && BuffTime <= 1820)
			{
				IPlayer.RemoveDef(3);
				IPlayer.RemoveAbsorb(3);
				CancelBuff(IPlayer, playerBuffs, 399);
				CancelBuff(IPlayer, playerBuffs, 398);
				IPlayer.RemoveBuffIcon(0, 0, 9101, 1010);
			}

			if (BuffTime >= 2755 && BuffTime <= 2760)
			{
				IPlayer.RemoveDef(4);
				IPlayer.RemoveAbsorb(4);
				CancelBuff(IPlayer, playerBuffs, 399);
				CancelBuff(IPlayer, playerBuffs, 398);
				IPlayer.RemoveBuffIcon(0, 0, 9101, 1010);
			}

			if (BuffTime >= 3695 && BuffTime <= 3700)
			{
				IPlayer.RemoveDef(5);
				IPlayer.RemoveAbsorb(5);
				CancelBuff(IPlayer, playerBuffs, 399);
				CancelBuff(IPlayer, playerBuffs, 398);
				IPlayer.RemoveBuffIcon(0, 0, 9101, 1010);
			}

			if (BuffTime >= 4635 && BuffTime <= 4640)
			{
				IPlayer.RemoveDef(6);
				IPlayer.RemoveAbsorb(6);
				CancelBuff(IPlayer, playerBuffs, 399);
				CancelBuff(IPlayer, playerBuffs, 398);
				IPlayer.RemoveBuffIcon(0, 0, 9101, 1010);
			}

			if (BuffTime >= 5575 && BuffTime <= 5580)
			{
				IPlayer.RemoveDef(7);
				IPlayer.RemoveAbsorb(7);
				CancelBuff(IPlayer, playerBuffs, 399);
				CancelBuff(IPlayer, playerBuffs, 398);
				IPlayer.RemoveBuffIcon(0, 0, 9101, 1010);
			}

			if (BuffTime >= 6515 && BuffTime <= 6520)
			{
				IPlayer.RemoveDef(8);
				IPlayer.RemoveAbsorb(8);
				CancelBuff(IPlayer, playerBuffs, 399);
				CancelBuff(IPlayer, playerBuffs, 398);
				IPlayer.RemoveBuffIcon(0, 0, 9101, 1010);
			}

			if (BuffTime >= 7455 && BuffTime <= 7460)
			{
				IPlayer.RemoveDef(9);
				IPlayer.RemoveAbsorb(9);
				CancelBuff(IPlayer, playerBuffs, 399);
				CancelBuff(IPlayer, playerBuffs, 398);
				IPlayer.RemoveBuffIcon(0, 0, 9101, 1010);
			}

			if (BuffTime >= 8395 && BuffTime <= 8400)
			{
				IPlayer.RemoveDef(10);
				IPlayer.RemoveAbsorb(10);
				CancelBuff(IPlayer, playerBuffs, 399);
				CancelBuff(IPlayer, playerBuffs, 398);
				IPlayer.RemoveBuffIcon(0, 0, 9101, 1010);
			}
		}

		if ((GetTickCount() / 1000) % 60 == 0 && playerBuffs.count(349)) {
			int Satiety = GetValue(playerBuffs, BuffNames::Satiety) - 1;
			if (Satiety > 0) {
				int IID = GetValue(playerBuffs, BuffNames::RidingIID);
				UpdateBuff(IPlayer, playerBuffs, BuffNames::Satiety, BuffNames::BuffTime, Satiety);
				CPlayer::Write((void*)Player, 0xFE, "ddd", 200, IID, (1728 * Satiety));
				if (!(Satiety % 5)) {
					IPlayer.RemoveHp(1);
					itemStat.Enter();
					int ItemStat = GetItemStat.count(IID) ? GetItemStat.find(IID)->second : 0;
					itemStat.Leave();
					if (ItemStat) {
						int Satietys = ItemStat / 100;
						if (Satietys) {
							ItemStat -= (Satietys * 100);

							itemStat.Enter();
							GetItemStat[IID] = ItemStat + (100 * Satiety);
							itemStat.Leave();
							CDBSocket::Write(90, "dd", ItemStat + (100 * Satiety), IID);
						}
					}
				}
			}
		}

		if ((GetTickCount() / 1000) % 2 == 0 && playerBuffs.count(397) && playerBuffs.count(396))
		{
			int BuffTime = GetRemain(playerBuffs, 396);

			if (BuffTime >= 1 && BuffTime <= 5)
			{
				IPlayer.RemoveDef(6);
				CancelBuff(IPlayer, playerBuffs, 397);
				CancelBuff(IPlayer, playerBuffs, 396);
				IPlayer.RemoveBuffIcon(0, 0, 9100, 1009);
			}

			if (BuffTime >= 815 && BuffTime <= 820)
			{
				IPlayer.RemoveDef(12);
				CancelBuff(IPlayer, playerBuffs, 397);
				CancelBuff(IPlayer, playerBuffs, 396);
				IPlayer.RemoveBuffIcon(0, 0, 9100, 1009);
			}

			if (BuffTime >= 1755 && BuffTime <= 1760)
			{
				IPlayer.RemoveDef(18);
				CancelBuff(IPlayer, playerBuffs, 397);
				CancelBuff(IPlayer, playerBuffs, 396);
				IPlayer.RemoveBuffIcon(0, 0, 9100, 1009);
			}

			if (BuffTime >= 2695 && BuffTime <= 2700)
			{
				IPlayer.RemoveDef(24);
				CancelBuff(IPlayer, playerBuffs, 397);
				CancelBuff(IPlayer, playerBuffs, 396);
				IPlayer.RemoveBuffIcon(0, 0, 9100, 1009);
			}

			if (BuffTime >= 3635 && BuffTime <= 3640)
			{
				IPlayer.RemoveDef(30);
				CancelBuff(IPlayer, playerBuffs, 397);
				CancelBuff(IPlayer, playerBuffs, 396);
				IPlayer.RemoveBuffIcon(0, 0, 9100, 1009);
			}

			if (BuffTime >= 4575 && BuffTime <= 4580)
			{
				IPlayer.RemoveDef(36);
				CancelBuff(IPlayer, playerBuffs, 397);
				CancelBuff(IPlayer, playerBuffs, 396);
				IPlayer.RemoveBuffIcon(0, 0, 9100, 1009);
			}

			if (BuffTime >= 5515 && BuffTime <= 5520)
			{
				IPlayer.RemoveDef(42);
				CancelBuff(IPlayer, playerBuffs, 397);
				CancelBuff(IPlayer, playerBuffs, 396);
				IPlayer.RemoveBuffIcon(0, 0, 9100, 1009);
			}

			if (BuffTime >= 6455 && BuffTime <= 6460)
			{
				IPlayer.RemoveDef(48);
				CancelBuff(IPlayer, playerBuffs, 397);
				CancelBuff(IPlayer, playerBuffs, 396);
				IPlayer.RemoveBuffIcon(0, 0, 9100, 1009);
			}

			if (BuffTime >= 7395 && BuffTime <= 7400)
			{
				IPlayer.RemoveDef(54);
				CancelBuff(IPlayer, playerBuffs, 397);
				CancelBuff(IPlayer, playerBuffs, 396);
				IPlayer.RemoveBuffIcon(0, 0, 9100, 1009);
			}

			if (BuffTime >= 8335 && BuffTime <= 8340)
			{
				IPlayer.RemoveDef(60);
				CancelBuff(IPlayer, playerBuffs, 397);
				CancelBuff(IPlayer, playerBuffs, 396);
				IPlayer.RemoveBuffIcon(0, 0, 9100, 1009);
			}
		}

		if (playerBuffs.count(BuffNames::ItemsEffects))
		{
			int ItemXX = GetValue(playerBuffs, BuffNames::ItemsEffects);
			int ItemIID = GetValue(playerBuffs, BuffNames::EffectsIID);

			if (ItemIID) {
				int Item = IPlayer.ItemPointerLock(ItemIID);

				if (Item)
				{
					IItem Itemx((void*)Item);
					int Timer = EquipEffects.find(ItemXX)->second.effectTime;
					std::string effectName = EquipEffects.find(ItemXX)->second.Effect;

					if (Timer && IPlayer.ScaniaTimer(Timer) && CItem::IsState(Item, 1))
						IPlayer.AddFxToTarget(effectName.c_str(), 0, 0, 1);
				}
			}
		}

		if (playerBuffs.count(BuffNames::WeaponsEffects))
		{
			int ItemXX = GetValue(playerBuffs, BuffNames::WeaponsEffects);
			int ItemIID = GetValue(playerBuffs, BuffNames::WEffectIID);

			if (ItemIID) {
				int Item = IPlayer.ItemPointerLock(ItemIID);

				if (Item)
				{
					IItem Itemx((void*)Item);
					int Timer = EquipEffects.find(ItemXX)->second.effectTime;
					std::string effectName = EquipEffects.find(ItemXX)->second.Effect;

					if (Timer && IPlayer.ScaniaTimer(Timer) && CItem::IsState(Item, 1))
						IPlayer.AddFxToTarget(effectName.c_str(), 0, 0, 1);

					//	IPlayer.AddFxToBone(effectName.c_str(), 1);
				}
			}
		}

		if (CGuild::IsWarringPeriod() && CSMap::IsOnTile(*(void **)((int)IPlayer.Offset + 320), (int)IPlayer.Offset + 332, 1048576)) {
			if (GetValue(playerBuffs, BuffNames::PetOwner)) {

				int PetItem = GetValue(playerBuffs, BuffNames::PetIID);
				if (PetItem) {
					int Item = IPlayer.ItemPointerLock(PetItem);

					if (Item)
					{
						IItem Itemx((void*)Item);

						if (CItem::IsState(Item, 1))
							IPlayer.PutOffItem(PetItem);
					}
				}
			}

			if (GetValue(playerBuffs, BuffNames::PetOwner2)) {
				int PetItem = GetValue(playerBuffs, BuffNames::PetIID2);
				if (PetItem) {
					int Item = IPlayer.ItemPointerLock(PetItem);

					if (Item)
					{
						IItem Itemx((void*)Item);

						if (CItem::IsState(Item, 1))
							IPlayer.PutOffItem(PetItem);
					}
				}
			}

			if (GetValue(playerBuffs, BuffNames::PetOwner3)) {
				int PetItem = GetValue(playerBuffs, BuffNames::PetIID3);
				if (PetItem) {
					int Item = IPlayer.ItemPointerLock(PetItem);

					if (Item)
					{
						IItem Itemx((void*)Item);

						if (CItem::IsState(Item, 1))
							IPlayer.PutOffItem(PetItem);
					}
				}
			}
		}

		if (DamageEvent::Active == true && !playerBuffs.count(3951) && ((GetTickCount() / 1000) % 5 == 0)) {
			IPlayer.SetBuffIcon(-2, -1, DamageSBName, DamageSBKey);
			Buff(IPlayer, playerBuffs, 3951, 7200, 0);
		}

		if ((GetTickCount() / 1000) % 6 == 0 && playerBuffs.count(3951) && DamageEvent::Active == false) {
			IPlayer.RemoveBuffIcon(0, 0, DamageSBName, DamageSBKey);
			CancelBuff(IPlayer, playerBuffs, 3951);
		}

		if (CChar::IsGState((int)IPlayer.Offset, 256) && (SinDisable.count(IPlayer.GetMap()) || SinDisable.count((MapX + 1000)*(MapY + 100)))) {
			CancelBuff(IPlayer, playerBuffs, 104);
			IPlayer.SystemMessage("You can not be in assasin mode here", TEXTCOLOR_RED);
		}

		if (ugog.count((MapX * 1000) + MapY) && (IPlayer.GetZ() < ugog.find((MapX * 1000) + MapY)->second.minZ || IPlayer.GetZ() > ugog.find((MapX * 1000) + MapY)->second.maxZ)) {
			IPlayer.SetX(257518);
			IPlayer.SetY(259273);
			IPlayer.SetZ(16082);
			SaveAllProperty((int)Player, 0, 0);
			playerBuffs.clear();
			IPlayer.Kick();
			return CPlayer::Tick(Player);
		}

		if (IPlayer.isInTrainingMap()) {
			if (CChar::IsGState((int)IPlayer.Offset, 256)) {
				CancelBuff(IPlayer, playerBuffs, 104);
				IPlayer.SystemMessage("No sinning is available at Training Center.", TEXTCOLOR_RED);
			}

			int Time = GetValue(playerBuffs, BuffNames::TrainingTime);
			if (Time) {
				if (Time <= 3) {
					IPlayer.BoxMsg("Training hour is over. Training section is ended.");
					CPlayer::Write((void*)Player, 0xFE, "dd", 207, 0);
					CancelBuff(IPlayer, playerBuffs, BuffNames::TrainingTime);
					CancelBuff(IPlayer, playerBuffs, BuffNames::TrainingHits);
					CDBSocket::Write(95, "ddddddd", 2, IPlayer.GetPID(), BuffNames::TrainingTime, 0, 0, 0, 0);
				}
				else {
					if (!((Time - 1) % 60))
						CPlayer::Write((void*)Player, 0xFE, "dd", 207, (Time - 1) / 60);

					UpdateBuff(IPlayer, playerBuffs, BuffNames::TrainingTime, BuffNames::BuffTime, Time - 1);
				}
			}
		}

		if ((GetTickCount() / 1000) % 2 == 0) {
			int NamePadRemain = GetRemain(playerBuffs, BuffNames::NamePad);
			if (NamePadRemain && NamePadRemain <= 3) {
				CancelBuff(IPlayer, playerBuffs, BuffNames::NamePad);
				IPlayer.RemoveBuffIcon(0, 0, 9900, 9900);
				IPlayer.SystemMessage("Your colored name time came to its end, you can renew it at anytime by pressing C and clicking on Namepad.", TEXTCOLOR_YELLOW);
				CChar::WriteInSight((void*)Player, 0xFE, "ddd", 209, IPlayer.GetID(), 12);
			}
		}

		if (CChar::IsGState((int)IPlayer.Offset, 256) && playerBuffs.count(349) && IPlayer.GetMap() != LawlessMap)
			IPlayer.DisableRiding();

		// Emergency Escape Ride
		if (playerBuffs.count(82) && playerBuffs.count(349)){
			IPlayer.DisableRiding();
			IPlayer.SystemMessage("Riding with Emergency Escape skill is disabled.", TEXTCOLOR_RED);
		}

		if ((GetTickCount() / 1000) % 2 == 0 && playerBuffs.count(51) && !GetValue(playerBuffs, BuffNames::MaxAtk)) {
			int MaxAtk = IPlayer.GetClass() == 1 ? (IPlayer.GetMaxMagAttack() * 10) / 100 : (IPlayer.GetMaxPhyAttack() * 10) / 100;
			int MinAtk = IPlayer.GetClass() == 1 ? (IPlayer.GetMinMagAttack() * 10) / 100 : (IPlayer.GetMinPhyAttack() * 10) / 100;
			UpdateBuff(IPlayer, playerBuffs, BuffNames::MaxAtk, BuffNames::BuffTime, MaxAtk);
			UpdateBuff(IPlayer, playerBuffs, BuffNames::MinAtk, BuffNames::BuffTime, MinAtk);
			IPlayer.AddMinAttack(MinAtk);
			IPlayer.AddMaxAttack(MaxAtk);
		}

		if ((GetTickCount() / 1000) % 3 == 0 && !playerBuffs.count(51) && GetValue(playerBuffs, BuffNames::MaxAtk)) {
			IPlayer.RemoveMinAttack(GetValue(playerBuffs, BuffNames::MinAtk));
			IPlayer.RemoveMaxAttack(GetValue(playerBuffs, BuffNames::MaxAtk));
			UpdateBuff(IPlayer, playerBuffs, BuffNames::MaxAtk, BuffNames::BuffTime, 0);
			UpdateBuff(IPlayer, playerBuffs, BuffNames::MinAtk, BuffNames::BuffTime, 0);
		}

		if ((GetTickCount() / 1000) % 2 == 0 && playerBuffs.count(54) && !GetValue(playerBuffs, BuffNames::DeathBlow)) {
			int DB = (IPlayer.GetDeathBlow() * 5) / 100;
			IPlayer.AddDeathBlow(DB);
			UpdateBuff(IPlayer, playerBuffs, BuffNames::DeathBlow, BuffNames::BuffTime, DB);
		}

		if ((GetTickCount() / 1000) % 3 == 0 && !playerBuffs.count(54) && GetValue(playerBuffs, BuffNames::DeathBlow)) {
			IPlayer.RemoveDeathBlow(GetValue(playerBuffs, BuffNames::DeathBlow));
			UpdateBuff(IPlayer, playerBuffs, BuffNames::DeathBlow, BuffNames::BuffTime, 0);
		}

		if ((GetTickCount() / 1000) % 2 == 0 && playerBuffs.count(56) && !GetValue(playerBuffs, BuffNames::OTP)) {
			IPlayer.AddOTP(10);
			UpdateBuff(IPlayer, playerBuffs, BuffNames::OTP, BuffNames::BuffTime, 10);
		}

		if ((GetTickCount() / 1000) % 3 == 0 && !playerBuffs.count(56) && GetValue(playerBuffs, BuffNames::OTP)) {
			IPlayer.RemoveOTP(10);
			UpdateBuff(IPlayer, playerBuffs, BuffNames::OTP, BuffNames::BuffTime, 0);
		}

		if ((GetTickCount() / 1000) % 2 == 0 && playerBuffs.count(57) && !GetValue(playerBuffs, BuffNames::EVA)) {
			IPlayer.AddEva(5);
			UpdateBuff(IPlayer, playerBuffs, BuffNames::EVA, BuffNames::BuffTime, 5);
		}

		if ((GetTickCount() / 1000) % 3 == 0 && !playerBuffs.count(57) && GetValue(playerBuffs, BuffNames::EVA)) {
			IPlayer.RemoveEva(5);
			UpdateBuff(IPlayer, playerBuffs, BuffNames::EVA, BuffNames::BuffTime, 0);
		}

		if (Hunting::Active == true && IPlayer.GetMap() != HGMapI && Hunting::Guild && Hunting::Guild == IPlayer.GetGID()) {
			IPlayer.Teleport(HGMapI, HGXC, HGYC);
			IPlayer.ScreenTime(Hunting::Time);
		}

		if ((GetTickCount() / 1000) % 3 == 0 && !IPlayer.isDead() && IPlayer.GetCurHp() < IPlayer.GetMaxHp() && !playerBuffs.count(3789)) {
			int Pet1 = GetValue(playerBuffs, BuffNames::PetOwner);
			if (Pet1 && PetTime.count(Pet1)) {
				ConfigPetTime pet = PetTime.find(Pet1)->second;
				if (pet.Heal && pet.HPLimit && IPlayer.GetCurHp() <= (double)((double)IPlayer.GetMaxHp() * ((double)pet.HPLimit / 100.0)))
					IPlayer.IncreaseHp(pet.Heal);
			}

			int Pet2 = GetValue(playerBuffs, BuffNames::PetOwner2);
			if (Pet2 && PetTime.count(Pet2)) {
				ConfigPetTime pet = PetTime.find(Pet2)->second;
				if (pet.Heal && pet.HPLimit && IPlayer.GetCurHp() <= (double)((double)IPlayer.GetMaxHp() * ((double)pet.HPLimit / 100.0)))
					IPlayer.IncreaseHp(pet.Heal);
			}

			int Pet3 = GetValue(playerBuffs, BuffNames::PetOwner3);
			if (Pet3 && PetTime.count(Pet3)) {
				ConfigPetTime pet = PetTime.find(Pet3)->second;
				if (pet.Heal && pet.HPLimit && IPlayer.GetCurHp() <= (double)((double)IPlayer.GetMaxHp() * ((double)pet.HPLimit / 100.0)))
					IPlayer.IncreaseHp(pet.Heal);
			}
		}

		if ((GetTickCount() / 1000) % 3 == 0 && !IPlayer.isDead() && playerBuffs.count(2126) && IPlayer.GetCurHp() < IPlayer.GetMaxHp() && !(playerBuffs.count(160) || playerBuffs.count(180) || playerBuffs.count(179) || playerBuffs.count(161) || playerBuffs.count(162) || playerBuffs.count(163) || playerBuffs.count(170) || playerBuffs.count(171) || playerBuffs.count(373) || playerBuffs.count(374) || playerBuffs.count(902) || playerBuffs.count(903) || playerBuffs.count(BuffNames::LMS)) && (int)*(DWORD**)0x004E0964 != 4) {
			if (!playerBuffs.count(987))
				IPlayer.IncreaseHp(GetValue(playerBuffs, 2126));
			else
				CancelBuff(IPlayer, playerBuffs, 987);
		}

		if (IPlayer.isDead() && (GetTickCount() / 1000) % 3 == 0 && playerBuffs.count(2127) && !(playerBuffs.count(160) || playerBuffs.count(180) || playerBuffs.count(179) || playerBuffs.count(161) || playerBuffs.count(162) || playerBuffs.count(163) || playerBuffs.count(170) || playerBuffs.count(171) || playerBuffs.count(373) || playerBuffs.count(374) || playerBuffs.count(902) || playerBuffs.count(903) || playerBuffs.count(BuffNames::LMS)) && (int)*(DWORD**)0x004E0964 != 4) {
			if (!playerBuffs.count(388))
				IPlayer.Rb(6);
			else
				CancelBuff(IPlayer, playerBuffs, 388);
		}

		if (CheckMining.count(IPlayer.GetPID()))
		{
			ConfigMining pMining = CheckMining.findValue(IPlayer.GetPID());
			if (pMining.Time && IPlayer.IsShopping())
			{
				IPlayer.CloseWindow("minebar");
				pMining.Time = 0;
				pMining.Cycle = 0;
				pMining.Index = 0;
				pMining.Amount = 0;
				IPlayer.CancelBuff(3960);
			}

			if (pMining.Time && IPlayer.IsFishing())
			{
				IPlayer.CloseWindow("minebar");
				pMining.Time = 0;
				pMining.Cycle = 0;
				pMining.Index = 0;
				pMining.Amount = 0;
				IPlayer.CancelBuff(3960);
			}

			if (pMining.Time)
			{
				if (MiningAreaLimit && (RectX < 8198 || RectX > 8433 || RectY < 8790 || RectY > 8966))
				{
					CPlayer::Write(IPlayer.GetOffset(), 220, "bb", 0, 7);
					IPlayer.CloseWindow("minebar");
					pMining.Time = 0;
					pMining.Cycle = 0;
					pMining.Index = 0;
					pMining.Amount = 0;
					IPlayer.CancelBuff(3960);
				}
			}

			if (pMining.Time && GetTickCount() >= pMining.Time)
			{
				int Chance = 0, Type = 0;
				Chance = CTools::Rate(0, 1000);
				if (Chance < 5) Type = 2;
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
				bool ContinueMining = true;

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
						IPlayer.CancelBuff(3960);
						CPlayer::Write(IPlayer.GetOffset(), 220, "bb", 0, 3);
						ContinueMining = false;
					}
				}

				if (ContinueMining == true)
				{
					CPlayer::Write(IPlayer.GetOffset(), 220, "bbw", 0, 4, pMining.Index);
					pMining.Time = GetTickCount() + 300000;
				}
			}
			CheckMining.replaceInsert(IPlayer.GetPID(), pMining);
		}

		/*if ((GetTickCount() / 1000) % 3 == 0 && (IPlayer.GetClass() == 1 || IPlayer.GetClass() == 4) && playerBuffs.count(50))
			CancelBuff(IPlayer, playerBuffs, 50);*/

		if ((GetTickCount() / 1000) % 2 == 0 && (playerBuffs.count(18) || playerBuffs.count(19)) && playerBuffs.count(349))
		{
			CancelBuff(IPlayer, playerBuffs, 18);
			CancelBuff(IPlayer, playerBuffs, 19);
			IPlayer.DisableRiding();
		}

		if (IPlayer.isDead() && playerBuffs.count(349))
			IPlayer.DisableRiding();

		if (CSMap::IsOnTile(*(void **)((int)IPlayer.Offset + 320), (int)IPlayer.Offset + 332, 1048576) && playerBuffs.count(349))
			IPlayer.DisableRiding();

		if ((GetTickCount() / 1000) % 2 == 0 && playerBuffs.count(349) && !IPlayer.IsPVPValid())
			IPlayer.DisableRiding();

		if (CChar::IsMState((int)IPlayer.GetOffset(), 1) && playerBuffs.count(385))
			CChar::SubMState(IPlayer.GetOffset(), 1, 0);

		if (Hunting::Active == true && IPlayer.GetMap() == HGMapI && Hunting::Guild && Hunting::Guild != IPlayer.GetGID())
			IPlayer.PortToVillage();

		if (F10::Active && F10::ShowTime > 10 && playerBuffs.count(165) && !playerBuffs.count(308))
		{
			Buff(IPlayer, playerBuffs, 308, F10::ShowTime, 0);
			IPlayer.ScreenTime(F10::ShowTime);
		}

		if (Maut::Active == true && MautRegistration.count(IPlayer.GetPID()) && IPlayer.IsPVPValid())
		{
			MautRegistration.erase(IPlayer.GetPID());

			if (IPlayer.IsValid())
			{
				IPlayer.Teleport(MautMap, MautX + CTools::Rate(-100, 100), MautY + CTools::Rate(-100, 100));
				Buff(IPlayer, playerBuffs, BuffNames::Mautareta, 3655, 0);
				CPlayer::Write(Player, 0xFF, "ds", 234, "You have entered the Spirit world of sand, Mautareta will appear soon!");
				IPlayer.ScreenTime(1800);
			}
		}

		if (BossEXP::Active == true && !playerBuffs.count(BuffNames::BossEXP) && IPlayer.IsPVPValid() && BossEXPRegistration.count(IPlayer.GetPID()))
		{
			if (IPlayer.IsValid())
			{
				int TimeLeft = BossEXP::Timer - (int)time(0);
				IPlayer.Teleport(BossEXPMap, BossEXPPX + CTools::Rate(-BossEXPRange, BossEXPRange), BossEXPPY + CTools::Rate(-BossEXPRange, BossEXPRange));
				Buff(IPlayer, playerBuffs, BuffNames::BossEXP, TimeLeft + 60, 0);
				std::string SysName(BossEXPName);
				std::string Msg = "You have entered the Spirit world of " + SysName + ", he will appear soon!";
				CPlayer::Write(Player, 0xFF, "ds", 234, Msg.c_str());
				IPlayer.ScreenTime(TimeLeft);
			}
		}

		if (BossEXP::Active && IPlayer.GetMap() != BossEXPMap && playerBuffs.count(BuffNames::BossEXP))
			IPlayer.Teleport(BossEXPMap, BossEXPPX + CTools::Rate(-BossEXPRange, BossEXPRange), BossEXPPY + CTools::Rate(-BossEXPRange, BossEXPRange));

		//if (BossEXP::Active && IPlayer.GetMap() == BossEXPMap && !playerBuffs.count(BuffNames::BossEXP))
		//	IPlayer.PortToVillage();

		if (!BossEXP::Active && playerBuffs.count(BuffNames::BossEXP)) {
			IPlayer.CloseScreenTime();
			CancelBuff(IPlayer, playerBuffs, BuffNames::BossEXP);
		}

		if (Maut::Active && IPlayer.GetMap() != MautMap && playerBuffs.count(BuffNames::Mautareta))
			IPlayer.Teleport(MautMap, MautX + CTools::Rate(-100, 100), MautY + CTools::Rate(-100, 100));

		if (Maut::Active && IPlayer.GetMap() == MautMap && !playerBuffs.count(BuffNames::Mautareta))
			IPlayer.PortToVillage();

		if (!Maut::Active && playerBuffs.count(BuffNames::Mautareta)) {
			IPlayer.CloseScreenTime();
			CancelBuff(IPlayer, playerBuffs, BuffNames::Mautareta);
		}

		if (Protect32::Active == false && IPlayer.GetMap() == PLMap)
		{
			if (Protect32::Winner && IPlayer.GetGID() == Protect32::Winner && (playerBuffs.count(170) || playerBuffs.count(171))) {
				IPlayer.systemReward(WinnerPL);
				IPlayer.SetHonor(0, 0, 0, 0, 0, 0, 1, 0, 0, 0);
			}
			else
			if (Protect32::Winner && IPlayer.GetGID() != Protect32::Winner && (playerBuffs.count(170) || playerBuffs.count(171)))
				IPlayer.systemReward(LoserPL);

			IPlayer.RemoveSetBlue();
			IPlayer.RemoveSetRed();
			IPlayer.CloseSpScore();
			CancelBuff(IPlayer, playerBuffs, 170);
			CancelBuff(IPlayer, playerBuffs, 171);
			IPlayer.PortToVillage();
		}

		if (GetValue(playerBuffs, BuffNames::BossHunt)) {
			if (BossHunting::Time > 0)
				IPlayer.Scenario3_3Score(BossHunting::Time, BossHunting::maxDmg, GetValue(playerBuffs, BuffNames::BossHunt));
			else {
				IPlayer.CloseWindow("Scenario3_3_timescore");
				CancelBuff(IPlayer, playerBuffs, BuffNames::BossHunt);
			}
		}

		if (Protect32::Active == true && (GetTickCount() / 1000) % 5 == 0 && IPlayer.GetMap() == PLMap && !playerBuffs.count(170) && !playerBuffs.count(171))
			IPlayer.PortToVillage();

		if (Protect32::Active == true && Protect32::GuildFirst && IPlayer.GetGID() == Protect32::GuildFirst)
		{
			if (IPlayer.IsValid() && !playerBuffs.count(170)) {
				Buff(IPlayer, playerBuffs, 170, 4000, 0);
				IPlayer.SetHonor(0, 0, 0, 0, 0, 1, 0, 0, 0, 0);
			}

			if (IPlayer.IsValid() && IPlayer.GetMap() != PLMap)
				IPlayer.Teleport(PLMap, 308588 + CTools::Rate(-100, 100), 284483 + CTools::Rate(-100, 100));

			if (IPlayer.isDead())
			{
				if (IPlayer.GetPID() == IPlayer.GetGID() && IPlayer.GetGID() == Protect32::GuildFirst && Protect32::Prayer == 1)
				{
					Buff(IPlayer, playerBuffs, 352, 30, 0);
					Protect32::Prayer = 0;
					Protect32::BluePrayerTime = 0;
				}

				if ((*(DWORD*)((int)IPlayer.GetOffset() + 1452) - GetTickCount()) / 1000 <= 580)
					IPlayer.Teleport(PLMap, 308588 + CTools::Rate(-100, 100), 284483 + CTools::Rate(-100, 100));
			}
		}

		if (Raid::Active && !playerBuffs.count(175))
			Buff(IPlayer, playerBuffs, 175, 7200, 0);

		if (Raid::Active == true && !playerBuffs.count(175) && IPlayer.GetMap() == RaidMap)
			IPlayer.PortToVillage();

		if (Raid::Active == true && playerBuffs.count(175) && IPlayer.GetMap() != RaidMap)
			IPlayer.Teleport(RaidMap, 233670, 236129);

		if (MapX == 26 && MapY == 34 && IPlayer.GetZ() < 37600 && !playerBuffs.count(3871) && !playerBuffs.count(902) && !playerBuffs.count(903) && !playerBuffs.count(373) && !playerBuffs.count(BuffNames::Fighter) && !playerBuffs.count(374) && !playerBuffs.count(BuffNames::PTVsPTBlue) && !playerBuffs.count(BuffNames::PTVsPTRed))
			IPlayer.Teleport(0, 215296, 280724);

		if ((MapX != 26 || MapY != 34 || IPlayer.GetZ() >= 37200 || IPlayer.GetZ() < 36550)) {
			if (playerBuffs.count(BuffNames::PTVsPTBlue) || playerBuffs.count(BuffNames::PTVsPTRed)) {
				int Arena = playerBuffs.count(BuffNames::PTVsPTBlue) ? GetValue(playerBuffs, BuffNames::PTVsPTBlue) : GetValue(playerBuffs, BuffNames::PTVsPTRed);
				IPlayer.Teleport(0, PartyArenas[0][Arena] + CTools::Rate(-100, 100), PartyArenas[1][Arena] + CTools::Rate(-100, 100));
			}
			else
			if (CupRegistration.count(IPlayer.GetPID()) && (playerBuffs.count(902) || playerBuffs.count(903))) {
				Fight playerFight = CupRegistration.find(IPlayer.GetPID())->second.fight;
				IPlayer.Teleport(0, playerFight.CoordX + CTools::Rate(-100, 100), playerFight.CoordY + CTools::Rate(-100, 100));
			}
		}

		if (Protect32::Active == true && Protect32::GuildSecond && IPlayer.GetGID() == Protect32::GuildSecond)
		{
			if (IPlayer.IsValid() && !playerBuffs.count(171)) {
				Buff(IPlayer, playerBuffs, 171, 4000, 0);
				IPlayer.SetHonor(0, 0, 0, 0, 0, 1, 0, 0, 0, 0);
			}

			if (IPlayer.IsValid() && IPlayer.GetMap() != PLMap)
				IPlayer.Teleport(PLMap, 310264 + CTools::Rate(-100, 100), 284486 + CTools::Rate(-100, 100));

			if (IPlayer.isDead())
			{
				if (IPlayer.GetPID() == IPlayer.GetGID() && IPlayer.GetGID() == Protect32::GuildSecond && Protect32::Prayer == 2)
				{
					Buff(IPlayer, playerBuffs, 352, 30, 0);
					Protect32::Prayer = 0;
					Protect32::RedPrayerTime = 0;
				}

				if ((*(DWORD*)((int)IPlayer.GetOffset() + 1452) - GetTickCount()) / 1000 <= 580)
					IPlayer.Teleport(PLMap, 310264 + CTools::Rate(-100, 100), 284486 + CTools::Rate(-100, 100));
			}
		}

		if (Protect32::Active == true && IPlayer.GetGID() == Protect32::GuildFirst && playerBuffs.count(170))
		{
			if (IPlayer.GetPID() != IPlayer.GetGID())
				IPlayer.SetBlue();

			if (IPlayer.GetPID() == IPlayer.GetGID())
			{
				if (Protect32::Prayer == 1)
					CChar::WriteInSight(IPlayer.GetOffset(), 46, "dI", IPlayer.GetID(), __int64(0x00640000) << 32);
				else
					IPlayer.SetBlue();
			}

			if (Protect32::Prayer == 0 && IPlayer.IsValid() && Protect32::Time > 10 && Protect32::Time < 1201 && IPlayer.IsValid() && IPlayer.GetPID() == IPlayer.GetGID() && IPlayer.GetGID() == Protect32::GuildFirst && RectX > 9668 && RectX < 9672 && RectY > 9001 && RectY < 9005 && !playerBuffs.count(352))
				Protect32::Prayer = 1;

			if (Protect32::Prayer == 1 && IPlayer.IsValid() && IPlayer.GetPID() == IPlayer.GetGID() && IPlayer.GetGID() == Protect32::GuildFirst)
			{
				if (RectX < 9668 || RectX > 9672 || RectY < 9001 || RectY > 9005)
					Protect32::Prayer = 0;
			}

			if (Protect32::Prayer == 1 && IPlayer.IsValid() && IPlayer.GetPID() == IPlayer.GetGID() && IPlayer.GetGID() == Protect32::GuildFirst)
			{
				if (Protect32::BluePrayerTime >= 21)
				{
					Protect32::BlueScore += 25;
					Protect32::BluePrayerTime = 0;
				}

				Protect32::BluePrayerTime++;
			}

			if (RectX > 9686 && RectX < 9705 && RectY > 8879 && RectY < 8914)
				IPlayer.Teleport(PLMap, 308588 + CTools::Rate(-100, 100), 284483 + CTools::Rate(-100, 100));

			if (Protect32::Time >= 1200)
			{
				if (RectX < 9631 || RectX > 9653 || RectY < 8879 || RectY > 8897)
					IPlayer.Teleport(PLMap, 308588 + CTools::Rate(-100, 100), 284483 + CTools::Rate(-100, 100));

				IPlayer.CloseSpScore();
				std::string timecheck = "The battle is started.";

				if (Protect32::Time == 1200)
					timecheck = timecheck;
				else
					timecheck = "The battle is starting in " + Int2String(Protect32::Time - 1200) + " seconds.";

				CPlayer::Write(IPlayer.GetOffset(), 0xFF, "dsd", 247, timecheck.c_str(), 0);
			}

			if (Protect32::Time <= 1200)
				IPlayer.SpScore(Protect32::Time, Protect32::Prayer, Protect32::RedScore, Protect32::BlueScore, Protect32::RedWin, Protect32::BlueWin);

			if (Protect32::Time == 0 && (RectX < 9631 || RectX > 9653 || RectY < 8879 || RectY > 8897))
				IPlayer.Teleport(PLMap, 308588 + CTools::Rate(-100, 100), 284483 + CTools::Rate(-100, 100));
		}

		if (Protect32::Active == true && IPlayer.GetGID() == Protect32::GuildSecond && playerBuffs.count(171))
		{
			if (IPlayer.GetPID() != IPlayer.GetGID())
				IPlayer.SetRed();

			if (IPlayer.GetPID() == IPlayer.GetGID())
			{
				if (Protect32::Prayer == 2)
					CChar::WriteInSight(IPlayer.GetOffset(), 46, "dI", IPlayer.GetID(), __int64(0x00620000) << 32);
				else
					IPlayer.SetRed();
			}

			if (Protect32::Prayer == 0 && IPlayer.IsValid() && Protect32::Time > 10 && Protect32::Time < 1201 && IPlayer.IsValid() && IPlayer.GetPID() == IPlayer.GetGID() && IPlayer.GetGID() == Protect32::GuildSecond && RectX > 9668 && RectX < 9672 && RectY > 9001 && RectY < 9005 && !playerBuffs.count(352))
				Protect32::Prayer = 2;

			if (Protect32::Prayer == 2 && IPlayer.IsValid() && IPlayer.GetPID() == IPlayer.GetGID() && IPlayer.GetGID() == Protect32::GuildSecond)
			{
				if (RectX < 9668 || RectX > 9672 || RectY < 9001 || RectY > 9005)
					Protect32::Prayer = 0;
			}

			if (Protect32::Prayer == 2 && IPlayer.IsValid() && IPlayer.GetPID() == IPlayer.GetGID() && IPlayer.GetGID() == Protect32::GuildSecond)
			{
				if (Protect32::RedPrayerTime >= 21)
				{
					Protect32::RedScore += 25;
					Protect32::RedPrayerTime = 0;
				}

				Protect32::RedPrayerTime++;
			}

			if (RectX > 9633 && RectX < 9655 && RectY > 8877 && RectY < 8914)
				IPlayer.Teleport(PLMap, 310264 + CTools::Rate(-100, 100), 284486 + CTools::Rate(-100, 100));

			if (Protect32::Time >= 1200)
			{
				if (RectX < 9685 || RectX > 9707 || RectY < 8879 || RectY > 8896)
					IPlayer.Teleport(PLMap, 310264 + CTools::Rate(-100, 100), 284486 + CTools::Rate(-100, 100));

				IPlayer.CloseSpScore();
				std::string timecheck = "The battle is started.";

				if (Protect32::Time == 1200)
					timecheck = timecheck;
				else
					timecheck = "The battle is starting in " + Int2String(Protect32::Time - 1200) + " seconds.";

				CPlayer::Write(IPlayer.GetOffset(), 0xFF, "dsd", 247, timecheck.c_str(), 1);
			}

			if (Protect32::Time <= 1200)
				IPlayer.SpScore(Protect32::Time, Protect32::Prayer, Protect32::RedScore, Protect32::BlueScore, Protect32::RedWin, Protect32::BlueWin);

			if (Protect32::Time == 0 && (RectX < 9685 || RectX > 9707 || RectY < 8879 || RectY > 8896))
				IPlayer.Teleport(PLMap, 310264 + CTools::Rate(-100, 100), 284486 + CTools::Rate(-100, 100));
		}
		/*
		if ((GetTickCount() / 1000) % 5 == 0 && GetValue(playerBuffs,BuffNames::PetOwner))
		{
		int PetItem = GetValue(playerBuffs,BuffNames::PetIID);
		if (PetItem && !PetLifeCheck.count(PetItem))
		{
		int Item = IPlayer.ItemPointer(PetItem);
		if (Item)
		{
		IItem Itemx((void*)Item);

		if (CItem::IsState(Item, 1) && PetTime.find(Itemx.CheckIndex())->second.Time)
		OrnamentPutOff(Itemx.GetOffset(), 0, (int)IPlayer.GetOffset());
		}
		}
		}

		if ((GetTickCount() / 1000) % 5 == 0 && GetValue(playerBuffs,BuffNames::PetOwner2))
		{
		int PetItem = GetValue(playerBuffs,BuffNames::PetIID2);
		if (PetItem && !PetLifeCheck.count(PetItem))
		{
		int Item = IPlayer.ItemPointer(PetItem);
		if (Item)
		{
		IItem Itemx((void*)Item);

		if (CItem::IsState(Item, 1) && PetTime.find(Itemx.CheckIndex())->second.Time)
		OrnamentPutOff(Itemx.GetOffset(), 0, (int)IPlayer.GetOffset());
		}
		}
		}

		if ((GetTickCount() / 1000) % 5 == 0 && GetValue(playerBuffs,BuffNames::PetOwner3))
		{
		int PetItem = GetValue(playerBuffs,BuffNames::PetIID3);
		if (PetItem && !PetLifeCheck.count(PetItem))
		{
		int Item = IPlayer.ItemPointer(PetItem);
		if (Item)
		{
		IItem Itemx((void*)Item);

		if (CItem::IsState(Item, 1) && PetTime.find(Itemx.CheckIndex())->second.Time)
		OrnamentPutOff(Itemx.GetOffset(), 0, (int)IPlayer.GetOffset());
		}
		}
		}
		*/
		if ((GetTickCount() / 1000) % 2 == 0 && playerBuffs.count(392) && !playerBuffs.count(395))
		{
			CancelBuff(IPlayer, playerBuffs, 392);
			CancelBuff(IPlayer, playerBuffs, 395);
			IPlayer.RemoveBuffIcon(0, 0, 4242, 950);
			IPlayer.AddDef(100);
		}

		if ((GetTickCount() / 1000) % 2 == 0 && playerBuffs.count(393) && !playerBuffs.count(395))
		{
			CancelBuff(IPlayer, playerBuffs, 393);
			CancelBuff(IPlayer, playerBuffs, 395);
			IPlayer.RemoveBuffIcon(0, 0, 4242, 950);
			IPlayer.AddDef(120);
		}

		if ((GetTickCount() / 1000) % 2 == 0 && playerBuffs.count(394) && !playerBuffs.count(395))
		{
			CancelBuff(IPlayer, playerBuffs, 394);
			CancelBuff(IPlayer, playerBuffs, 395);
			IPlayer.RemoveBuffIcon(0, 0, 4242, 950);
			IPlayer.AddDef(140);
		}

		if (IPlayer.GetClass() == 1 && (GetTickCount() / 1000) % 3 == 0 && playerBuffs.count(391) && !playerBuffs.count(390))
		{
			CancelBuff(IPlayer, playerBuffs, 391);
			CancelBuff(IPlayer, playerBuffs, 390);
			IPlayer.RemoveBuffIcon(0, 0, 4244, 952);
			int pSkill = IPlayer.GetSkillPointer(92);

			if (pSkill)
			{
				ISkill xSkill((void*)pSkill);
				IPlayer.DecreaseMaxHp(500 * xSkill.GetGrade());
				IPlayer.RemoveMaxAttack(100 * xSkill.GetGrade());
				IPlayer.RemoveMinAttack(100 * xSkill.GetGrade());
			}
		}

		if ((GetTickCount() / 1000) % 2 == 0 && IPlayer.GetLevel() >= 81 && playerBuffs.count(385))
		{
			CancelBuff(IPlayer, playerBuffs, 12);
			CancelBuff(IPlayer, playerBuffs, 82);

			if (IPlayer.GetCurMp() < 8)
			{
				CancelBuff(IPlayer, playerBuffs, 385);
				CancelBuff(IPlayer, playerBuffs, 40);
				IPlayer.RemoveBuffIcon(-2, -1, 4246, 954);
			}
			else {
				IPlayer.DecreaseMana(8);
			}
		}

		if ((GetTickCount() / 1000) % 2 == 0 && GetValue(playerBuffs, BuffNames::CDTime)) {
			if (GetTickCount() >= GetValue(playerBuffs, BuffNames::CDTime)) {

				IPlayer.RemoveBuffIcon(0, 0, 4245, 953);
				IPlayer.DecreaseCritRate((GetValue(playerBuffs, BuffNames::CDType) * 10) + 10);
				IPlayer.DecreaseCritDamage((GetValue(playerBuffs, BuffNames::CDType) * 10) + 10);
				UpdateBuff(IPlayer, playerBuffs, BuffNames::CDType, BuffNames::BuffTime, 0);
				UpdateBuff(IPlayer, playerBuffs, BuffNames::CDTime, BuffNames::BuffTime, 0);
			}
		}

		if ((GetTickCount() / 1000) % 2 == 0 && GetValue(playerBuffs, BuffNames::SOFSTime)) {
			if (GetTickCount() >= GetValue(playerBuffs, BuffNames::SOFSTime))
			{
				IPlayer.RemoveBuffIcon(0, 0, 4243, 951);
				IPlayer.RemoveMaxAttack(GetValue(playerBuffs, BuffNames::SOFSType) * SOFSMAX);
				IPlayer.RemoveMinAttack(GetValue(playerBuffs, BuffNames::SOFSType) * SOFSMIN);
				UpdateBuff(IPlayer, playerBuffs, BuffNames::SOFSType, BuffNames::BuffTime, 0);
				UpdateBuff(IPlayer, playerBuffs, BuffNames::SOFSTime, BuffNames::BuffTime, 0);
			}
		}

		if ((GetTickCount() / 1000) % 2 == 0 && !playerBuffs.count(379) && playerBuffs.count(380))
		{
			CancelBuff(IPlayer, playerBuffs, 379);
			CancelBuff(IPlayer, playerBuffs, 380);
			IPlayer.RemoveBuffIcon(0, 0, 4240, 948);
			int pSkill = IPlayer.GetSkillPointer(90);

			if (pSkill)
			{
				ISkill xSkill((void*)pSkill);
				IPlayer.RemoveDef(50 + (xSkill.GetGrade() * 50));
			}
		}

		if (IPlayer.IsValid() && (GetTickCount() / 1000) % 3 == 0 && (GetValue(playerBuffs, BuffNames::PetOwner) || GetValue(playerBuffs, BuffNames::PetOwner3)))
		{
			if (!GetValue(playerBuffs, BuffNames::PetBuff))
				UpdateBuff(IPlayer, playerBuffs, BuffNames::PetBuff, BuffNames::BuffTime, GetTickCount() + 300000);

			if ((GetTickCount() / 1000) % 2 == 0)
			{
				if (GetTickCount() >= GetValue(playerBuffs, BuffNames::PetBuff))
				{
					UpdateBuff(IPlayer, playerBuffs, BuffNames::PetBuff, BuffNames::BuffTime, GetTickCount() + 300000);
					int Number = rand() % 8 + 1;

					if (Number == 0 || Number == 1)
					{
						Buff(IPlayer, playerBuffs, 301, 60, 0);
						Buff(IPlayer, playerBuffs, 302, 65, 0);
						IPlayer.SetBuffIcon(60000, 0, 2360, 299);
						IPlayer.AddMaxAttack(32);
						IPlayer.AddMinAttack(32);
						IPlayer.AddDef(5);
						IPlayer.AddFxToTarget("Pet_Attackbuff_02", 1, 0, 0);
					}
					else if (Number == 2)
					{
						Buff(IPlayer, playerBuffs, 303, 60, 0);
						Buff(IPlayer, playerBuffs, 314, 65, 0);
						IPlayer.SetBuffIcon(60000, 0, 2362, 302);
						IPlayer.AddMaxAttack(16);
						IPlayer.AddMinAttack(16);
						IPlayer.AddFxToTarget("Pet_Blowbuff_02", 1, 0, 0);
					}
					else if (Number == 3)
					{
						Buff(IPlayer, playerBuffs, 315, 60, 0);
						Buff(IPlayer, playerBuffs, 316, 65, 0);
						IPlayer.SetBuffIcon(60000, 0, 2361, 300);
						IPlayer.AddMaxAttack(16);
						IPlayer.AddMinAttack(16);
						IPlayer.AddDef(8);
						IPlayer.AddFxToTarget("Pet_Defensebuff_02", 1, 0, 0);
					}
					else if (Number == 4)
					{
						Buff(IPlayer, playerBuffs, 317, 60, 0);
						Buff(IPlayer, playerBuffs, 318, 65, 0);
						IPlayer.SetBuffIcon(60000, 0, 2359, 301);
						IPlayer.AddDef(5);
						IPlayer.AddEva(3);
						IPlayer.AddFxToTarget("Pet_Avoidbuff_02", 1, 0, 0);
					}
					else if (Number == 5)
					{
						Buff(IPlayer, playerBuffs, 319, 60, 0);
						Buff(IPlayer, playerBuffs, 320, 65, 0);
						IPlayer.SetBuffIcon(60000, 0, 2375, 303);
						IPlayer.AddMaxAttack(45);
						IPlayer.AddMinAttack(45);
						IPlayer.AddDef(7);
						IPlayer.AddFxToTarget("Pet_Attackbuff_03", 1, 0, 0);
					}
					else if (Number == 6)
					{
						Buff(IPlayer, playerBuffs, 321, 60, 0);
						Buff(IPlayer, playerBuffs, 322, 65, 0);
						IPlayer.SetBuffIcon(60000, 0, 2377, 306);
						IPlayer.AddMaxAttack(24);
						IPlayer.AddMinAttack(24);
						IPlayer.AddFxToTarget("Pet_Blowbuff_03", 1, 0, 0);
					}
					else if (Number == 7)
					{
						Buff(IPlayer, playerBuffs, 323, 60, 0);
						Buff(IPlayer, playerBuffs, 324, 65, 0);
						IPlayer.SetBuffIcon(60000, 0, 2376, 304);
						IPlayer.AddMaxAttack(24);
						IPlayer.AddMinAttack(24);
						IPlayer.AddDef(10);
						IPlayer.AddFxToTarget("Pet_Defensebuff_03", 1, 0, 0);
					}
					else if (Number == 8)
					{
						Buff(IPlayer, playerBuffs, 325, 60 - 2, 0);
						Buff(IPlayer, playerBuffs, 326, 65, 0);
						IPlayer.SetBuffIcon(60000, 0, 2374, 305);
						IPlayer.AddDef(7);
						IPlayer.AddEva(4);
						IPlayer.AddFxToTarget("Pet_Avoidbuff_03", 1, 0, 0);
					}
				}
			}
		}

		if (CChar::IsGState((int)Player, 2) && playerBuffs.count(400))
			CancelBuff(IPlayer, playerBuffs, 400);

		if (RectX >= 6703 && RectX <= 6721 && RectY >= 8768 && RectY <= 8781 && !playerBuffs.count(373) && !playerBuffs.count(374))
			IPlayer.Teleport(0, 215294, 280808);

		if ((playerBuffs.count(373) || playerBuffs.count(374) || playerBuffs.count(BuffNames::Fighter) || playerBuffs.count(902) || playerBuffs.count(903)) && IPlayer.IsParty())
			CPlayer::LeaveParty((int)Player);

		if ((GetTickCount() / 1000) % 2 == 0 && !playerBuffs.count(373) && playerBuffs.count(375))
		{
			IPlayer.RemoveSetRed();
			CancelBuff(IPlayer, playerBuffs, 375);
			IPlayer.CloseWindow("Scenario3_3_timescore");
			IPlayer.RemoveBuffIcon(-2, -1, 0, 20);
		}

		if ((GetTickCount() / 1000) % 2 == 0 && !playerBuffs.count(374) && playerBuffs.count(376))
		{
			IPlayer.RemoveSetBlue();
			CancelBuff(IPlayer, playerBuffs, 376);
			IPlayer.CloseWindow("Scenario3_3_timescore");
			IPlayer.RemoveBuffIcon(-2, -1, 0, 20);
		}

		if ((GetTickCount() / 1000) % 2 == 0 && !playerBuffs.count(368) && playerBuffs.count(369))
		{
			CancelBuff(IPlayer, playerBuffs, 369);
			CancelBuff(IPlayer, playerBuffs, 40);
			IPlayer.AddEva(10);
			IPlayer.RemoveBuffIcon(0, 0, 2042, 226);
		}

		if (IPlayer.GetCurHp() > 500 && playerBuffs.count(370) && playerBuffs.count(371))
			IPlayer.DecreaseHp(500);

		if ((GetTickCount() / 1000) % 3 == 0 && PlayerVote.count(IPlayer.GetPID())) {

			if (PlayerVote.find(IPlayer.GetPID())->second.Time >= (int)time(0)) {
				if (PlayerVote.find(IPlayer.GetPID())->second.Token.size() > 0) {
					std::string Link = "https://topofmmos.com/api?key=" + (std::string)VoteAPIKey + "&srvid=" + Int2String(VoteID) + "&TokenID=" + PlayerVote.find(IPlayer.GetPID())->second.Token;
					int VoteValue = String2Int(getData(Link));

					if (VoteValue == VoteID) {
						IPlayer.systemReward(VoteReward);

						IPlayer.BoxMsg("Your voting reward has been successfully given.");
						VoteList.replaceInsert(sha256(IPlayer.GetIP()), (int)time(0) + 43200);

						std::string HWID = User.find(IPlayer.GetPID())->second.Hardware;
						VoteList.replaceInsert(sha256(HWID), (int)time(0) + 43200);
						PlayerVote.erase(IPlayer.GetPID());
					}
				}
			}
			else {
				IPlayer.SystemMessage("Your voting token has expired. Please try again using the vote rewards npc.", TEXTCOLOR_RED);
				PlayerVote.erase(IPlayer.GetPID());
			}
		}

		if ((GetTickCount() / 1000) % 2 == 0 && !playerBuffs.count(370) && playerBuffs.count(371))
		{
			CancelBuff(IPlayer, playerBuffs, 371);
			IPlayer.RemoveBuffIcon(0, 0, 2038, 224);
		}

		if (Hell::Active && IPlayer.isDead() && playerBuffs.count(166))
		{
			if (Hell::Rebirth > 0)
			{
				if (Hell::Rebirth == 1)
					CChar::WriteInSight(IPlayer.GetOffset(), 0xFF, "ddddd", 242, 89, 255, 255, 255);

				Hell::Rebirth -= 1;
				IPlayer.Revive();
				Buff(IPlayer, playerBuffs, 24, 6, 40);
				IPlayer.RemoveBuffIcon(0, 0, 703, 34);
				CChar::AddMState(IPlayer.GetOffset(), 0, 2147483648);
				IPlayer.SetBuffIcon(6000, 0, 1793, 201);
			}
			else {
				CChar::WriteInSight(IPlayer.GetOffset(), 0xFF, "ddddd", 242, 91, 255, 255, 255);
				Hell::Active = false;
				Hell::Time = 0;
			}
		}

		if (Hell::Active == true && playerBuffs.count(166))
			IPlayer.SetRebirthTalisman(Hell::Rebirth);

		if (Hell::Active == true && IPlayer.GetMap() != HellMap && playerBuffs.count(166))
			IPlayer.Teleport(HellMap, HellX, HellY);

		if (Hell::Active == true && IPlayer.GetMap() == HellMap && !playerBuffs.count(166))
		{
			if (IPlayer.isDead())
				IPlayer.Revive();

			Buff(IPlayer, playerBuffs, 167, HellCooldown, 0);

			if (Hell::Size > 0 && Hell::Active == true)
				Hell::Size -= 1;

			IPlayer.Teleport(0, HellReturnX, HellReturnY);
			IPlayer.CloseScreenTime();
			IPlayer.CloseRebirthTalisman();
		}

		if (Hell::Active && !IPlayer.IsParty() && playerBuffs.count(166))
		{
			if (IPlayer.isDead())
				IPlayer.Revive();

			CancelBuff(IPlayer, playerBuffs, 166);
		}

		if (!IPlayer.IsCorrect()) {
			CConsole::Red("Stats Overload detected at Player PID: %d", IPlayer.GetPID());
			IPlayer.SystemMessage("Stat problem detected.", TEXTCOLOR_RED);
			IPlayer.Kick();
			playerBuffs.clear();
			return 0;
		}
		if (PeaceEvil && TimerEP && playerBuffs.count(BuffNames::EPEvent) && GetValue(playerBuffs, BuffNames::EPEvent) <= GetTickCount()) {
			int ItemPE = 0;

			if (IPlayer.isSlytherin()) {
				ItemPE = CItem::CreateItem(SlytherinGCIndex, 0, AmountEP, -1);
			}
			else if (IPlayer.isRavenclaw()) {
				ItemPE = CItem::CreateItem(RavenGCIndex, 0, AmountEP, -1);
			}
			else if (IPlayer.isHufflepuff()){
				ItemPE = CItem::CreateItem(HuffleGCIndex, 0, AmountEP, -1);

			}
			else {
				ItemPE = CItem::CreateItem(GryffindorGCIndex, 0, AmountEP, -1);
			}

			if (ItemPE) {
				if (CPlayer::InsertItem(Player, 16, ItemPE) != 1) {
					CBase::Delete((void*)ItemPE);
				}
			}

			// Update the EPEvent buff based on the player's house
			int buffTime = GetTickCount() + (TimerEP * 1000);
			UpdateBuff(IPlayer, playerBuffs, BuffNames::EPEvent, BuffNames::BuffTime, buffTime);
		}


		if (MD5Check == 1) {
			if (playerBuffs.count(BuffNames::MD5Hash) && GetValue(playerBuffs, BuffNames::MD5Hash) <= GetTickCount()) {
				CConsole::Red("MD5 Hack detected PID: %d", IPlayer.GetPID());
				IPlayer.SystemMessage("Please update your client.", TEXTCOLOR_RED);
				IPlayer.Kick();
				playerBuffs.clear();
				return 0;
			}
		}

		if (CRangeCheck) {
			CheckCalls(IPlayer, *(DWORD*)((int)Player + 584), 0);
			CheckCalls(IPlayer, IPlayer.GetSecondCall(), 1);
		}

		int MIndex = (MapX * 1000) + MapY;
		if (MapLvl.count(MIndex)) {
			Area mArea = MapLvl.find(MIndex)->second;
			if (mArea.type) {
				if (IPlayer.GetLevel() < mArea.level || (mArea.item != 0 && !CPlayer::FindItem(Player, mArea.item, 1)))
				{
					IPlayer.PortToVillage();
					IPlayer.SystemMessage("You mess required item or level for this area", TEXTCOLOR_RED);
				}
			}
		}

		if (MapLvl.count(IPlayer.GetMap())){
			Area mArea = MapLvl.find(IPlayer.GetMap())->second;
			if (!mArea.type) {
				if (IPlayer.GetLevel() < mArea.level || (mArea.item != 0 && !CPlayer::FindItem(Player, mArea.item, 1))) {
					IPlayer.PortToVillage();
					IPlayer.SystemMessage("You mess required item or level for this area", TEXTCOLOR_RED);
				}
			}
		}

		if (MapMax.count(MIndex)) {
			AreaMax mArea = MapMax.find(MIndex)->second;
			if (mArea.type) {
				if (IPlayer.GetLevel() >= mArea.maxlevel)
					IPlayer.PortToVillage();
			}
		}

		if (MapMax.count(IPlayer.GetMap())){
			AreaMax mArea = MapMax.find(IPlayer.GetMap())->second;
			if (!mArea.type) {
				if (IPlayer.GetLevel() >= mArea.maxlevel)
					IPlayer.PortToVillage();
			}
		}

		if (IPlayer.GetMap() != JailMap && playerBuffs.count(BuffNames::Jail)) {
			if (!JailCoords.empty()) {
				int Chance = CTools::Rate(0, JailCoords.size() - 1);
				Point coords = JailCoords.at(Chance);
				IPlayer.Teleport(JailMap, coords.X, coords.Y, coords.Z);
			}
		}

		if (IPlayer.GetMap() == JailMap && !playerBuffs.count(BuffNames::Jail)) {
			IPlayer.PortToVillage();
			IPlayer.BoxMsg("Your jail time is now over.");
		}

		if (Immortal::Active == true && (GetTickCount() / 1000) % 5 == 0 && !playerBuffs.count(3088))
		{
			//if (!playerBuffs.count(24))
			//Buff(IPlayer, playerBuffs, 24, 3600, 0);
			IPlayer.SetBuffIcon(-2, -1, ImmortalSBName, ImmortalSBKey);
			Buff(IPlayer, playerBuffs, 3088, 3600, 0);
		}

		if (Immortal::Active == false && (GetTickCount() / 1000) % 5 == 0 && playerBuffs.count(3088))
		{
			IPlayer.RemoveBuffIcon(0, 0, ImmortalSBName, ImmortalSBKey);
			//if (playerBuffs.count(24))
			//CancelBuff(IPlayer, playerBuffs, 24);
			CancelBuff(IPlayer, playerBuffs, 3088);
		}

		if (EggEvent::Active == true && (GetTickCount() / 1000) % 5 == 0 && !playerBuffs.count(3098))
		{
			IPlayer.SetBuffIcon(-2, -1, EggSBName, EggSBKey);
			Buff(IPlayer, playerBuffs, 3098, 18000, 0);
		}
		if (EggEvent::Active == false && (GetTickCount() / 1000) % 5 == 0 && playerBuffs.count(3098))
		{
			IPlayer.RemoveBuffIcon(0, 0, EggSBName, EggSBKey);
			CancelBuff(IPlayer, playerBuffs, 3098);
		}

		if (Hell::Active == true && playerBuffs.count(166) && Hell::Countdown != -1 && !playerBuffs.count(1874)) {
			IPlayer.CloseScreenTime();
			IPlayer.ScreenTime(Hell::Countdown);
			Buff(IPlayer, playerBuffs, 1874, 16, 0);
		}

		if ((GetTickCount() / 1000) % 3 == 0 && Hell::Active == false && (IPlayer.GetMap() == HellMap || playerBuffs.count(166)))
		{
			if (IPlayer.isDead())
				IPlayer.Revive();

			Buff(IPlayer, playerBuffs, 167, HellCooldown, 0);
			CancelBuff(IPlayer, playerBuffs, 166);
			IPlayer.Teleport(0, HellReturnX, HellReturnY);
			IPlayer.CloseScreenTime();
			IPlayer.CloseRebirthTalisman();
			CancelBuff(IPlayer, playerBuffs, 1874);
		}

		if (F10::Active == true && F10Registration.count(IPlayer.GetPID()) && IPlayer.IsPVPValid())
		{
			F10Registration.erase(IPlayer.GetPID());

			if (IPlayer.IsValid())
			{
				IPlayer.Teleport(21, 117339, 36409);
				Buff(IPlayer, playerBuffs, 165, 3700, 0);
			}
		}

		if (F10::Active == true && IPlayer.GetMap() != 21 && playerBuffs.count(165))
			IPlayer.Teleport(21, 117339, 36409);

		if (F10::Active == true && IPlayer.GetMap() == 21 && !playerBuffs.count(165))
			IPlayer.PortToVillage();

		//	Happy Hour
		//if ((Time::GetHour() == "18" || Time::GetHour() == "19"))
		//{
		//	if ((GetTickCount() / 1000) % 5 == 0 && !playerBuffs.count(362))
		//	{
		//		Buff(IPlayer, playerBuffs, 362, 7200, 0);
		//		IPlayer.SetBuffIcon(-2, -1, 1657, 188);
		//		IPlayer.AddOTP(5);
		//	}

		//	if ((GetTickCount() / 1000) % 5 == 0 && !playerBuffs.count(363))
		//	{
		//		Buff(IPlayer, playerBuffs, 363, 7200, 0);
		//		IPlayer.SetBuffIcon(-2, -1, 1663, 194);
		//		IPlayer.AddStr(2);
		//		IPlayer.AddHp(5);
		//		IPlayer.AddInt(2);
		//		IPlayer.AddWis(5);
		//		IPlayer.AddAgi(3);
		//	}

		//	if ((GetTickCount() / 1000) % 5 == 0 && !playerBuffs.count(364))
		//	{
		//		Buff(IPlayer, playerBuffs, 364, 7200, 0);
		//		IPlayer.SetBuffIcon(-2, -1, 1655, 186);
		//		IPlayer.AddStr(7);
		//		IPlayer.AddInt(7);
		//	}

		//	if (TimeStr == "19:59:59")
		//	{
		//		if (playerBuffs.count(362))
		//		{
		//			CancelBuff(IPlayer, playerBuffs, 362);
		//			IPlayer.RemoveBuffIcon(0, 0, 1657, 188);
		//			IPlayer.RemoveOTP(5);
		//		}

		//		if (playerBuffs.count(363))
		//		{
		//			CancelBuff(IPlayer, playerBuffs, 363);
		//			IPlayer.RemoveBuffIcon(0, 0, 1663, 194);
		//			IPlayer.RemoveStr(2);
		//			IPlayer.RemoveHp(5);
		//			IPlayer.RemoveInt(2);
		//			IPlayer.RemoveWis(5);
		//			IPlayer.RemoveAgi(3);
		//		}

		//		if (playerBuffs.count(364))
		//		{
		//			CancelBuff(IPlayer, playerBuffs, 364);
		//			IPlayer.RemoveBuffIcon(0, 0, 1655, 186);
		//			IPlayer.RemoveStr(7);
		//			IPlayer.RemoveInt(7);
		//		}
		//	}
		//}


		// New comers lvl 50 +50 attack
		//if (IPlayer.GetLevel() < 50 && (GetTickCount() / 1000) % 5 == 0 && !playerBuffs.count(366))
		//{
		//	Buff(IPlayer, playerBuffs, 366, 648000, 0);
		//	IPlayer.SetBuffIcon(648000000, 0, 3756, 433);
		//	IPlayer.AddDef(50);
		//	IPlayer.AddMaxAttack(50);
		//	IPlayer.AddMinAttack(50);
		//}

		//if (IPlayer.GetLevel() >= 50 && (GetTickCount() / 1000) % 2 == 0 && playerBuffs.count(366))
		//{
		//	CancelBuff(IPlayer, playerBuffs, 366);
		//	IPlayer.RemoveBuffIcon(0, 0, 3756, 433);
		//	IPlayer.RemoveDef(50);
		//	IPlayer.RemoveMaxAttack(50);
		//	IPlayer.RemoveMinAttack(50);
		//}

		if (ReviveLvl && IPlayer.isDead() && playerLvl <= ReviveLvl){
			if (IPlayer.IsBuff(BuffNames::RevivalCheck)) {
				if (IPlayer.GetBuffRemain(BuffNames::RevivalCheck) <= 1) {
					IPlayer.Revive();
					IPlayer.Buff(24, 6, 40);
					IPlayer.RemoveBuffIcon(0, 0, 703, 34);
					CJBRefBuff(IPlayer.GetOffset(), ReviveBuff, ReviveSpeed);
				}
				else
					IPlayer.SystemMessage("Reviving in " + Int2String(IPlayer.GetBuffRemain(BuffNames::RevivalCheck) - 1) + "...", TEXTCOLOR_DARKGREEN);
			}
			else {
				IPlayer.Buff(BuffNames::RevivalCheck, ReviveCD, 0);
			}
		}

		if (IPlayer.GetMap() == BFMap) {
			POINT pt = *(POINT *)((int)Player + 324);
			if (playerBuffs.count(160)) {
				if (PtInRect(Battlefield::GoodVsEvil ? &rectBlueSafeG : &rectBlueSafe, pt))
					IPlayer.Teleport(BFMap, (Battlefield::GoodVsEvil ? BFTeleRedXG : BFTeleRedX) + CTools::Rate(-BFRange, BFRange), (Battlefield::GoodVsEvil ? BFTeleRedYG : BFTeleRedY) + CTools::Rate(-BFRange, BFRange), (Battlefield::GoodVsEvil ? BFTeleRedZG : BFTeleRedZ));
			}
			else
			if (playerBuffs.count(161)) {
				if (PtInRect(Battlefield::GoodVsEvil ? &rectRedSafeG : &rectRedSafe, pt))
					IPlayer.Teleport(BFMap, (Battlefield::GoodVsEvil ? BFTeleBlueXG : BFTeleBlueX) + CTools::Rate(-BFRange, BFRange), (Battlefield::GoodVsEvil ? BFTeleBlueYG : BFTeleBlueY) + CTools::Rate(-BFRange, BFRange), (Battlefield::GoodVsEvil ? BFTeleBlueZG : BFTeleBlueZ));
			}
		}

		if (SinEvent::Active && MapX == SEMapX && MapY == SEMapY) {
			int timeleft = SinEvent::Time - (int)time(0);

			if (!playerBuffs.count(104))
				Buff(IPlayer, playerBuffs, 104, timeleft, 0);

			if (IPlayer.isDead())
				IPlayer.Rb(SEImmunityTime);

			IPlayer.Scenario3_3Score(timeleft, GetValue(playerBuffs, BuffNames::SinEventPlayers) / SEPtsPerPlayer, GetValue(playerBuffs, BuffNames::SinEventMobs) / SEPtsPerMob);
		}

		if (IPlayer.GetMap() == CaptureMap && playerBuffs.count(180) && ((CPRedSafeX1 && RectX >= CPRedSafeX1) && (CPRedSafeX2 && RectX <= CPRedSafeX2)))
			IPlayer.Teleport(CaptureMap, CPTeleRedX + CTools::Rate(-50, 50), CPTeleRedY + CTools::Rate(-50, 50));

		if (IPlayer.GetMap() == CaptureMap && playerBuffs.count(179) && ((CPBlueSafeX1 && RectX >= CPBlueSafeX1) && (CPBlueSafeX2 && RectX <= CPBlueSafeX2)))
			IPlayer.Teleport(CaptureMap, CPTeleBlueX + CTools::Rate(-50, 50), CPTeleBlueY + CTools::Rate(-50, 50));

		if (IPlayer.GetMap() == ScenarioMap && RectX < 9021 && playerBuffs.count(163) || IPlayer.GetMap() == ScenarioMap && RectX > 9034 && playerBuffs.count(163))
		{
			if (playerBuffs.count(163) && IPlayer.GetMap() == ScenarioMap && RectX < 8920 || playerBuffs.count(163) && IPlayer.GetMap() == ScenarioMap && RectX > 9005)
				IPlayer.Teleport(ScenarioMap, 288802, 350986);
		}

		if (IPlayer.GetMap() == ScenarioMap && RectX < 8891 && playerBuffs.count(162) || IPlayer.GetMap() == ScenarioMap && RectX > 8904 && playerBuffs.count(162))
		{
			if (playerBuffs.count(162) && IPlayer.GetMap() == ScenarioMap && RectX < 8920 || playerBuffs.count(162) && IPlayer.GetMap() == ScenarioMap && RectX > 9005)
				IPlayer.Teleport(ScenarioMap, 284840, 351088);
		}

		if (IPlayer.GetMap() == LMSMap && !playerBuffs.count(BuffNames::LMS))
			IPlayer.PortToVillage();

		if (LastManStand::Active && IPlayer.GetMap() != LMSMap && playerBuffs.count(BuffNames::LMS)) {
			IPlayer.Teleport(LMSMap, LMSX + CTools::Rate(-300, 300), LMSY + CTools::Rate(-300, 300));
			CPlayer::Write(IPlayer.GetOffset(), 46, "dI", IPlayer.GetID(), __int64(0x40000) << 32);
		}

		if (LastManStand::RegisterAmount == 1 && !LastManStand::Time && LastManStand::Active == true && playerBuffs.count(BuffNames::LMS))
		{
			LastManStand::Active = false;
			LastManStand::RegisterAmount = 0;
			LastManStand::Notice = 1;
			LastManStand::WinnerName = std::string(IPlayer.GetName());
			IPlayer.RemoveSetRed();
			IPlayer.RemoveSetBlue();
			IPlayer.PortToVillage();

			std::string Datko = "./Winners/LMS.db";
			std::fstream DGkLOG;
			DGkLOG.open(Datko, std::fstream::in | std::fstream::out | std::fstream::app);
			DGkLOG << "(Winner (Time " << Time::GetDate() + " " + TimeStr << ")(PID " << IPlayer.GetPID() << ")(name '" << IPlayer.GetName() << "'))" << std::endl;
			DGkLOG.close();

			IPlayer.systemReward(WinnerLMS);
			CancelBuff(IPlayer, playerBuffs, BuffNames::LMS);
			LastManRegistration.clear();
			LastManHWID.clear();
		}

		if (LastManStand::RegisterAmount > 1 && CChar::IsGState((int)Player, 2) && playerBuffs.count(BuffNames::LMS))
		{
			CancelBuff(IPlayer, playerBuffs, BuffNames::LMS);
			IPlayer.RemoveSetRed();
			IPlayer.systemReward(LoserLMS);
			IPlayer.RemoveSetBlue();
			IPlayer.PortToVillage();
			LastManStand::RegisterAmount -= 1;
		}

		if (LastManStand::Active == true && LastManRegistration.count(IPlayer.GetPID()))
		{
			if (IPlayer.IsValid() && IPlayer.IsPVPValid())
			{
				Buff(IPlayer, playerBuffs, 24, 15, 40);
				IPlayer.RemoveBuffIcon(0, 0, 703, 34);
				CChar::AddMState(IPlayer.GetOffset(), 0, 2147483648);
				IPlayer.SetBuffIcon(15000, 0, 1793, 201);
				Buff(IPlayer, playerBuffs, BuffNames::LMS, 86400, 0);
				CPlayer::Write(IPlayer.GetOffset(), 46, "dI", IPlayer.GetID(), __int64(0x40000) << 32);
				LastManStand::RegisterAmount += 1;

				if (IPlayer.IsParty())
					CPlayer::LeaveParty((int)Player);

			}
			LastManRegistration.erase(IPlayer.GetPID());
		}

		if (CaptureFlag::Active == true && CaptureRegistration.count(IPlayer.GetPID()) && IPlayer.IsPVPValid())
		{
			int CPBuff = 179;

			if (CaptureFlag::BTeamLvl > CaptureFlag::RTeamLvl) {
				CaptureFlag::RTeamLvl += IPlayer.GetLevel();
				CPBuff = 180;
			}
			else
				CaptureFlag::BTeamLvl += IPlayer.GetLevel();

			CaptureRegistration.erase(IPlayer.GetPID());

			if (IPlayer.IsValid())
				Buff(IPlayer, playerBuffs, CPBuff, 3650, 0);
		}

		if (Scenario::Active == true)
		{
			if (IPlayer.IsValid() && IPlayer.GetGID() && Scenario::GuildFirst && IPlayer.GetGID() == Scenario::GuildFirst && !playerBuffs.count(162)) {
				Buff(IPlayer, playerBuffs, 162, 3650, 0);
				IPlayer.SetHonor(0, 0, 0, 1, 0, 0, 0, 0, 0, 0);
			}

			if (IPlayer.IsValid() && IPlayer.GetGID() && Scenario::GuildSecond && IPlayer.GetGID() == Scenario::GuildSecond && !playerBuffs.count(163)) {
				Buff(IPlayer, playerBuffs, 163, 3650, 0);
				IPlayer.SetHonor(0, 0, 0, 1, 0, 0, 0, 0, 0, 0);
			}
		}

		if (Scenario::Active == false && (GetTickCount() / 1000) % 2 == 0 && playerBuffs.count(162))
		{
			IPlayer.PortToVillage();
			IPlayer.RemoveSetRed();
			IPlayer.RemoveSetBlue();
			IPlayer.CloseScenario3_3Score();
			IPlayer.RemoveBuffIcon(0, 0, 0, 20);
			CancelBuff(IPlayer, playerBuffs, 365);
			int Overlay = 0;
			if (Scenario::RedScore > Scenario::BlueScore)
			{
				IPlayer.systemReward(WinnerDK);
				IPlayer.SetHonor(0, 0, 0, 0, 1, 0, 0, 0, 0, 0);

				if (Scenario::RedTeamTowerCount == 8)
					Overlay = 25;
				else
					Overlay = 26;
			}

			if (Scenario::BlueScore > Scenario::RedScore)
			{
				IPlayer.systemReward(LoserDK);

				if (Scenario::BlueTeamTowerCount == 8)
					Overlay = 14;
				else
					Overlay = 15;
			}

			if (Scenario::RedScore == Scenario::BlueScore)
			{
				IPlayer.systemReward(DrawDK);
				Overlay = 4;
			}

			if (Overlay)
				CPlayer::Write(IPlayer.GetOffset(), 0xFF, "ddddd", 242, Overlay, 255, 255, 255);

			CancelBuff(IPlayer, playerBuffs, 162);
		}

		if (Scenario::Active == false && (GetTickCount() / 1000) % 2 == 0 && playerBuffs.count(163))
		{
			IPlayer.PortToVillage();
			IPlayer.RemoveSetRed();
			IPlayer.RemoveSetBlue();
			IPlayer.CloseScenario3_3Score();
			IPlayer.RemoveBuffIcon(0, 0, 0, 20);
			CancelBuff(IPlayer, playerBuffs, 365);
			int Overlay = 0;
			if (Scenario::BlueScore > Scenario::RedScore)
			{
				IPlayer.systemReward(WinnerDK);
				IPlayer.SetHonor(0, 0, 0, 0, 1, 0, 0, 0, 0, 0);

				if (Scenario::BlueTeamTowerCount == 8)
					Overlay = 14;
				else
					Overlay = 15;
			}

			if (Scenario::RedScore > Scenario::BlueScore)
			{
				IPlayer.systemReward(LoserDK);
				if (Scenario::BlueTeamTowerCount == 8)
					Overlay = 25;
				else
					Overlay = 26;
			}

			if (Scenario::RedScore == Scenario::BlueScore)
			{
				IPlayer.systemReward(DrawDK);
				Overlay = 4;
			}

			if (Overlay)
				CPlayer::Write(IPlayer.GetOffset(), 0xFF, "ddddd", 242, Overlay, 255, 255, 255);

			CancelBuff(IPlayer, playerBuffs, 163);
		}

		if (Battlefield::Active == false && (GetTickCount() / 1000) % 2 == 0 && playerBuffs.count(160))
		{
			IPlayer.PortToVillage();
			IPlayer.RemoveSetRed();
			IPlayer.RemoveSetBlue();
			IPlayer.CloseScenario3_3Score();
			IPlayer.RemoveBuffIcon(0, 0, 0, 20);
			CancelBuff(IPlayer, playerBuffs, 361);
			int Overlay = 0;
			if (Battlefield::RedScore > Battlefield::BlueScore)
			{
				IPlayer.systemReward(Battlefield::GoodVsEvil ? EVGoodReward : WinnerBF);
				Overlay = 53;
				Buff(IPlayer, playerBuffs, 119, 43200, 0);
			}

			if (Battlefield::BlueScore > Battlefield::RedScore)
			{
				IPlayer.systemReward(Battlefield::GoodVsEvil ? EVGoodLoser : LoserBF);
				Overlay = 52;
			}

			if (Battlefield::RedScore == Battlefield::BlueScore)
			{
				IPlayer.systemReward(Battlefield::GoodVsEvil ? EVGoodDraw : DrawBF);
				Overlay = 4;
			}

			if (Overlay)
				CPlayer::Write(IPlayer.GetOffset(), 0xFF, "ddddd", 242, Overlay, 255, 255, 255);

			CancelBuff(IPlayer, playerBuffs, 160);
			CancelBuff(IPlayer, playerBuffs, 161);
		}

		if (Battlefield::Active == false && (GetTickCount() / 1000) % 2 == 0 && playerBuffs.count(161))
		{
			IPlayer.PortToVillage();
			IPlayer.RemoveSetRed();
			IPlayer.RemoveSetBlue();
			IPlayer.CloseScenario3_3Score();
			IPlayer.RemoveBuffIcon(0, 0, 0, 20);
			CancelBuff(IPlayer, playerBuffs, 361);

			int Overlay = 0;
			if (Battlefield::BlueScore > Battlefield::RedScore)
			{
				IPlayer.systemReward(Battlefield::GoodVsEvil ? EVGoodReward : WinnerBF);
				Overlay = 52;
				Buff(IPlayer, playerBuffs, 119, 43200, 0);
			}

			if (Battlefield::RedScore > Battlefield::BlueScore)
			{
				IPlayer.systemReward(Battlefield::GoodVsEvil ? EVGoodLoser : LoserBF);
				Overlay = 53;
			}

			if (Battlefield::RedScore == Battlefield::BlueScore)
			{
				IPlayer.systemReward(Battlefield::GoodVsEvil ? EVGoodDraw : DrawBF);
				Overlay = 4;
			}

			if (Overlay)
				CPlayer::Write(IPlayer.GetOffset(), 0xFF, "ddddd", 242, Overlay, 255, 255, 255);

			CancelBuff(IPlayer, playerBuffs, 160);
			CancelBuff(IPlayer, playerBuffs, 161);
		}

		if (CaptureFlag::Active == false && (GetTickCount() / 1000) % 2 == 0 && playerBuffs.count(180))
		{
			IPlayer.PortToVillage();
			IPlayer.RemoveSetRed();
			IPlayer.RemoveSetBlue();
			IPlayer.CloseScenario3_3Score();
			IPlayer.RemoveBuffIcon(0, 0, 0, 20);
			CancelBuff(IPlayer, playerBuffs, 361);
			int Reward = 0;
			int Honor = 0;
			int Overlay = 0;

			if (CaptureFlag::RedScore > CaptureFlag::BlueScore)
			{
				IPlayer.systemReward(WinnerCapture);
				Honor = CaptureHonorPts;
				Reward = CaptureRewardPts;
				Overlay = 53;
				Buff(IPlayer, playerBuffs, 119, 43200, 0);
			}

			if (CaptureFlag::BlueScore > CaptureFlag::RedScore)
			{
				IPlayer.systemReward(LoserCapture);
				Honor = CaptureHonorPts / 4;
				Reward = CaptureRewardPts / 4;
				Overlay = 52;
			}

			if (CaptureFlag::RedScore == CaptureFlag::BlueScore)
			{
				IPlayer.systemReward(DrawCapture);
				Honor = CaptureHonorPts / 2;
				Reward = CaptureRewardPts / 2;
				Overlay = 4;
			}

			if (Overlay)
				CPlayer::Write(IPlayer.GetOffset(), 0xFF, "ddddd", 242, Overlay, 255, 255, 255);

			CancelBuff(IPlayer, playerBuffs, 180);
		}

		if (CaptureFlag::Active == false && (GetTickCount() / 1000) % 2 == 0 && playerBuffs.count(179))
		{
			IPlayer.PortToVillage();
			IPlayer.RemoveSetRed();
			IPlayer.RemoveSetBlue();
			IPlayer.CloseScenario3_3Score();
			IPlayer.RemoveBuffIcon(0, 0, 0, 20);
			CancelBuff(IPlayer, playerBuffs, 361);
			int Reward = 0;
			int Honor = 0;
			int Overlay = 0;

			if (CaptureFlag::BlueScore > CaptureFlag::RedScore)
			{
				IPlayer.systemReward(WinnerCapture);
				Honor = CaptureHonorPts;
				Reward = CaptureRewardPts;
				Overlay = 52;
				Buff(IPlayer, playerBuffs, 119, 43200, 0);
			}

			if (CaptureFlag::RedScore > CaptureFlag::BlueScore)
			{
				IPlayer.systemReward(LoserCapture);
				Honor = CaptureHonorPts / 4;
				Reward = CaptureRewardPts / 4;
				Overlay = 53;
			}

			if (CaptureFlag::RedScore == CaptureFlag::BlueScore)
			{
				IPlayer.systemReward(DrawCapture);
				Honor = CaptureHonorPts / 2;
				Reward = CaptureRewardPts / 2;
				Overlay = 4;
			}

			if (Overlay)
				CPlayer::Write(IPlayer.GetOffset(), 0xFF, "ddddd", 242, Overlay, 255, 255, 255);

			CancelBuff(IPlayer, playerBuffs, 179);
		}

		if (Scenario::Active && IPlayer.GetMap() != ScenarioMap && playerBuffs.count(162))
		{
			if (IPlayer.IsTransform())
				CPlayer::FreeTransform(Player);

			IPlayer.Teleport(ScenarioMap, 284840, 351088);
		}

		if (Scenario::Active  && IPlayer.GetMap() != ScenarioMap && playerBuffs.count(163))
		{
			if (IPlayer.IsTransform())
				CPlayer::FreeTransform(Player);

			IPlayer.Teleport(ScenarioMap, 288802, 350986);
		}

		if (Battlefield::Active && IPlayer.GetMap() != BFMap && playerBuffs.count(160))
		{
			if (IPlayer.IsTransform())
				CPlayer::FreeTransform(Player);

			IPlayer.Teleport(BFMap, (Battlefield::GoodVsEvil ? BFTeleRedXG : BFTeleRedX) + CTools::Rate(-BFRange, BFRange), (Battlefield::GoodVsEvil ? BFTeleRedYG : BFTeleRedY) + CTools::Rate(-BFRange, BFRange), (Battlefield::GoodVsEvil ? BFTeleRedZG : BFTeleRedZ));
		}

		if (Battlefield::Active && IPlayer.GetMap() != BFMap && playerBuffs.count(161))
		{
			if (IPlayer.IsTransform())
				CPlayer::FreeTransform(Player);

			IPlayer.Teleport(BFMap, (Battlefield::GoodVsEvil ? BFTeleBlueXG : BFTeleBlueX) + CTools::Rate(-BFRange, BFRange), (Battlefield::GoodVsEvil ? BFTeleBlueYG : BFTeleBlueY) + CTools::Rate(-BFRange, BFRange), (Battlefield::GoodVsEvil ? BFTeleBlueZG : BFTeleBlueZ));
		}

		if (CaptureFlag::Active  && IPlayer.GetMap() != CaptureMap && playerBuffs.count(180))
		{
			if (IPlayer.IsTransform())
				CPlayer::FreeTransform(Player);

			IPlayer.Teleport(CaptureMap, CPTeleRedX + CTools::Rate(-50, 50), CPTeleRedY + CTools::Rate(-50, 50));
		}

		if (CaptureFlag::Active  && IPlayer.GetMap() != CaptureMap && playerBuffs.count(179))
		{
			if (IPlayer.IsTransform())
				CPlayer::FreeTransform(Player);

			IPlayer.Teleport(CaptureMap, CPTeleBlueX + CTools::Rate(-50, 50), CPTeleBlueY + CTools::Rate(-50, 50));
		}

		if (Scenario::Active && playerBuffs.count(162))
		{
			IPlayer.SetRed();

			if (!playerBuffs.count(365))
			{
				Buff(IPlayer, playerBuffs, 365, 3650, 0);
				IPlayer.Scenario3_3Score(Scenario::Time, Scenario::RedScore, Scenario::BlueScore);
				IPlayer.SetBuffIcon(-2, -1, 0, 20);
			}
		}
		if (CaptureFlag::Active && playerBuffs.count(180))
		{
			IPlayer.SetRed();

			if (!playerBuffs.count(361))
			{
				Buff(IPlayer, playerBuffs, 361, 3650, 0);
				IPlayer.Scenario3_3Score(CaptureFlag::Time, CaptureFlag::RedScore, CaptureFlag::BlueScore);
				IPlayer.SetBuffIcon(-2, -1, 0, 20);
			}
		}
		if (Scenario::Active && playerBuffs.count(163))
		{
			IPlayer.SetBlue();

			if (!playerBuffs.count(365))
			{
				Buff(IPlayer, playerBuffs, 365, 3650, 0);
				IPlayer.Scenario3_3Score(Scenario::Time, Scenario::RedScore, Scenario::BlueScore);
				IPlayer.SetBuffIcon(-2, -1, 0, 20);
			}
		}
		if (CaptureFlag::Active && playerBuffs.count(179))
		{
			IPlayer.SetBlue();

			if (!playerBuffs.count(361))
			{
				Buff(IPlayer, playerBuffs, 361, 3650, 0);
				IPlayer.Scenario3_3Score(CaptureFlag::Time, CaptureFlag::RedScore, CaptureFlag::BlueScore);
				IPlayer.SetBuffIcon(-2, -1, 0, 20);
			}
		}

		if (Battlefield::Active && playerBuffs.count(160))
		{
			IPlayer.SetRed();

			if (!playerBuffs.count(361))
			{
				Buff(IPlayer, playerBuffs, 361, 3650, 0);
				IPlayer.Scenario3_3Score(Battlefield::Time, Battlefield::RedScore, Battlefield::BlueScore);
				IPlayer.SetBuffIcon(-2, -1, 0, 20);
			}
		}

		if (Battlefield::Active && playerBuffs.count(161))
		{
			IPlayer.SetBlue();

			if (!playerBuffs.count(361))
			{
				Buff(IPlayer, playerBuffs, 361, 3650, 0);
				IPlayer.Scenario3_3Score(Battlefield::Time, Battlefield::RedScore, Battlefield::BlueScore);
				IPlayer.SetBuffIcon(-2, -1, 0, 20);
			}
		}

		if (Scenario::Active && IPlayer.isDead() && (GetTickCount() / 1000) % 5 == 0 && playerBuffs.count(162))
		{
			IPlayer.Teleport(ScenarioMap, 284840, 351088);
			IPlayer.Revive();
		}

		if (Scenario::Active && IPlayer.isDead() && (GetTickCount() / 1000) % 5 == 0 && playerBuffs.count(163))
		{
			IPlayer.Teleport(ScenarioMap, 288802, 350986);
			IPlayer.Revive();
		}

		if (Battlefield::Active && IPlayer.isDead() && playerBuffs.count(160))
		{
			Battlefield::BlueScore += 1;
			IPlayer.Teleport(BFMap, (Battlefield::GoodVsEvil ? BFTeleRedXG : BFTeleRedX) + CTools::Rate(-BFRange, BFRange), (Battlefield::GoodVsEvil ? BFTeleRedYG : BFTeleRedY) + CTools::Rate(-BFRange, BFRange), (Battlefield::GoodVsEvil ? BFTeleRedZG : BFTeleRedZ));
			if (BattlefieldBuffs)
				CJBRefBuff(Player, BattlefieldBuffs, BattlefieldSpeed);
		}

		if (Battlefield::Active && IPlayer.isDead() && playerBuffs.count(161))
		{
			Battlefield::RedScore += 1;
			IPlayer.Teleport(BFMap, (Battlefield::GoodVsEvil ? BFTeleBlueXG : BFTeleBlueX) + CTools::Rate(-BFRange, BFRange), (Battlefield::GoodVsEvil ? BFTeleBlueYG : BFTeleBlueY) + CTools::Rate(-BFRange, BFRange), (Battlefield::GoodVsEvil ? BFTeleBlueZG : BFTeleBlueZ));
			if (BattlefieldBuffs)
				CJBRefBuff(Player, BattlefieldBuffs, BattlefieldSpeed);
		}

		if (CaptureFlag::Active && CaptureFlag::PlayerID == (int)Player) {
			IPlayer.AddFxToTarget(CPBuffEffect, 1, 0, 0);
			if (IPlayer.GetCurHp() > CPHP)
				IPlayer.DecreaseHp(CPHP);
			else {
				IPlayer.Kill();
			}
		}

		if (CaptureFlag::Active && IPlayer.isDead() && CaptureFlag::PlayerID == (int)Player) {
			CaptureFlag::PlayerID = 0;
			CaptureFlag::CurrentCapturers = 0;
			CaptureFlag::MonsterOffset = 0;
			CChar::WriteInSight(Player, 0xFF, "dsd", 247, "Flag Monster has been respawned.", NOTICECOLOR_REDLONG);
			//Spawn(CaptureMonster, 1, CPSummonX, CPSummonY, CaptureMap);
			Summon((int)IPlayer.GetOffset(), CaptureMap, CPSummonX, CPSummonY, CaptureMonster, 1, 0, 0, 0, 0);
		}

		if (CaptureFlag::Active && IPlayer.isDead() && playerBuffs.count(180))
		{
			if (CaptureFlag::PlayerID != (int)Player)
				CaptureFlag::BlueScore += 1;
			IPlayer.Teleport(CaptureMap, CPTeleRedX + CTools::Rate(-50, 50), CPTeleRedY + CTools::Rate(-50, 50));
		}


		if (CaptureFlag::Active && IPlayer.isDead() && playerBuffs.count(179))
		{
			if (CaptureFlag::PlayerID != (int)Player)
				CaptureFlag::RedScore += 1;
			IPlayer.Teleport(CaptureMap, CPTeleBlueX + CTools::Rate(-50, 50), CPTeleBlueY + CTools::Rate(-50, 50));
		}

		if (CaptureFlag::Active && (playerBuffs.count(180) || playerBuffs.count(179)))
			IPlayer.Scenario3_3Score(CaptureFlag::Time, CaptureFlag::RedScore, CaptureFlag::BlueScore);

		if ((GetTickCount() / 1000) % 2 == 0 && IPlayer.GetMap() == CaptureMap && !playerBuffs.count(180) && !playerBuffs.count(179))
			IPlayer.PortToVillage();

		if (Scenario::Active && (playerBuffs.count(162) || playerBuffs.count(163)))
			IPlayer.Scenario3_3Score(Scenario::Time, Scenario::RedScore, Scenario::BlueScore);

		if (Battlefield::Active && (playerBuffs.count(160) || playerBuffs.count(161)))
			IPlayer.Scenario3_3Score(Battlefield::Time, Battlefield::RedScore, Battlefield::BlueScore);

		if ((GetTickCount() / 1000) % 2 == 0 && IPlayer.GetMap() == ScenarioMap && !playerBuffs.count(162) && !playerBuffs.count(163))
			IPlayer.PortToVillage();

		if ((GetTickCount() / 1000) % 2 == 0 && IPlayer.GetMap() == BFMap && !playerBuffs.count(160) && !playerBuffs.count(161))
			IPlayer.PortToVillage();

		if ((GetTickCount() / 1000) % 2 == 0 && !playerBuffs.count(358) && playerBuffs.count(359))
		{
			CancelBuff(IPlayer, playerBuffs, 359);
			IPlayer.RemoveBuffIcon(0, 0, 2009, 207);
		}

		if (playerBuffs.count(BuffNames::OTPScroll) && !playerBuffs.count(BuffNames::OTPScrollCheck)) {
			int Value = GetValue(playerBuffs, BuffNames::OTPScroll);
			IPlayer.AddOTP(Value);
			UpdateBuff(IPlayer, playerBuffs, BuffNames::OTPScrollCheck, BuffNames::BuffTime, Value);
		}

		if (!playerBuffs.count(BuffNames::OTPScroll) && playerBuffs.count(BuffNames::OTPScrollCheck)) {
			int Value = GetValue(playerBuffs, BuffNames::OTPScrollCheck);
			IPlayer.RemoveOTP(Value);
			CancelBuff(IPlayer, playerBuffs, BuffNames::OTPScrollCheck);
		}

		if (playerBuffs.count(BuffNames::EvaScroll) && !playerBuffs.count(BuffNames::EvaScrollCheck)) {
			int Value = GetValue(playerBuffs, BuffNames::EvaScroll);
			IPlayer.AddEva(Value);
			UpdateBuff(IPlayer, playerBuffs, BuffNames::EvaScrollCheck, BuffNames::BuffTime, Value);
		}

		if (!playerBuffs.count(BuffNames::EvaScroll) && playerBuffs.count(BuffNames::EvaScrollCheck)) {
			int Value = GetValue(playerBuffs, BuffNames::EvaScrollCheck);
			IPlayer.RemoveEva(Value);
			CancelBuff(IPlayer, playerBuffs, BuffNames::EvaScrollCheck);
		}

		if ((GetTickCount() / 1000) % 2 == 0 && !playerBuffs.count(354) && playerBuffs.count(355))
		{
			CancelBuff(IPlayer, playerBuffs, 355);
			IPlayer.RemoveBuffIcon(0, 0, 2012, 214);
			int pSkill = IPlayer.GetSkillPointer(12);

			if (pSkill)
			{
				ISkill xSkill((void*)pSkill);
				int nSkillGrade = xSkill.GetGrade();
				IPlayer.RemoveOTP(nSkillGrade * 2);
				IPlayer.RemoveEva(nSkillGrade * 3);
			}
		}

		if ((GetTickCount() / 1000) % 2 == 0 && !playerBuffs.count(344) && playerBuffs.count(345))
		{
			CancelBuff(IPlayer, playerBuffs, 345);
			IPlayer.RemoveBuffIcon(0, 0, 2016, 211);
		}

		if ((GetTickCount() / 1000) % 2 == 0 && !playerBuffs.count(339) && playerBuffs.count(340))
		{
			CancelBuff(IPlayer, playerBuffs, 339);
			IPlayer.RemoveBuffIcon(0, 0, 2021, 219);
		}

		if ((GetTickCount() / 1000) % 2 == 0 && !playerBuffs.count(301) && playerBuffs.count(302))
		{
			CancelBuff(IPlayer, playerBuffs, 302);
			IPlayer.RemoveMaxAttack(32);
			IPlayer.RemoveMinAttack(32);
			IPlayer.RemoveDef(5);
			IPlayer.RemoveBuffIcon(0, 0, 2360, 299);
		}

		if ((GetTickCount() / 1000) % 2 == 0 && !playerBuffs.count(303) && playerBuffs.count(314))
		{
			CancelBuff(IPlayer, playerBuffs, 314);
			IPlayer.RemoveMaxAttack(16);
			IPlayer.RemoveMinAttack(16);
			IPlayer.RemoveBuffIcon(0, 0, 2362, 302);
		}

		if ((GetTickCount() / 1000) % 2 == 0 && !playerBuffs.count(315) && playerBuffs.count(316))
		{
			CancelBuff(IPlayer, playerBuffs, 316);
			IPlayer.RemoveMaxAttack(16);
			IPlayer.RemoveMinAttack(16);
			IPlayer.RemoveDef(8);
			IPlayer.RemoveBuffIcon(0, 0, 2361, 300);
		}

		if ((GetTickCount() / 1000) % 2 == 0 && !playerBuffs.count(317) && playerBuffs.count(318))
		{
			CancelBuff(IPlayer, playerBuffs, 318);
			IPlayer.RemoveDef(5);
			IPlayer.RemoveEva(3);
			IPlayer.RemoveBuffIcon(0, 0, 2359, 301);
		}

		if ((GetTickCount() / 1000) % 2 == 0 && !playerBuffs.count(319) && playerBuffs.count(320))
		{
			CancelBuff(IPlayer, playerBuffs, 320);
			IPlayer.RemoveMaxAttack(45);
			IPlayer.RemoveMinAttack(45);
			IPlayer.RemoveDef(7);
			IPlayer.RemoveBuffIcon(0, 0, 2375, 303);
		}

		if ((GetTickCount() / 1000) % 2 == 0 && !playerBuffs.count(321) && playerBuffs.count(322))
		{
			CancelBuff(IPlayer, playerBuffs, 322);
			IPlayer.RemoveMaxAttack(24);
			IPlayer.RemoveMinAttack(24);
			IPlayer.RemoveBuffIcon(0, 0, 2377, 306);
		}

		if ((GetTickCount() / 1000) % 2 == 0 && !playerBuffs.count(323) && playerBuffs.count(324))
		{
			CancelBuff(IPlayer, playerBuffs, 324);
			IPlayer.RemoveMaxAttack(24);
			IPlayer.RemoveMinAttack(24);
			IPlayer.RemoveDef(10);
			IPlayer.RemoveBuffIcon(0, 0, 2376, 304);
		}

		if ((GetTickCount() / 1000) % 2 == 0 && !playerBuffs.count(325) && playerBuffs.count(326))
		{
			CancelBuff(IPlayer, playerBuffs, 326);
			IPlayer.RemoveDef(7);
			IPlayer.RemoveEva(4);
			IPlayer.RemoveBuffIcon(0, 0, 2374, 305);
		}

		if ((GetTickCount() / 1000) % 2 == 0 && !playerBuffs.count(309) && playerBuffs.count(310))
		{
			CancelBuff(IPlayer, playerBuffs, 310);
			IPlayer.RemoveBuffIcon(0, 0, 2356, 298);
		}

		if ((GetTickCount() / 1000) % 2 == 0 && !playerBuffs.count(305) && playerBuffs.count(306))
		{
			CancelBuff(IPlayer, playerBuffs, 306);
			IPlayer.RemoveBuffIcon(0, 0, 1794, 202);
		}

		if ((GetTickCount() / 1000) % 2 == 0 && !playerBuffs.count(288) && playerBuffs.count(289))
		{
			CancelBuff(IPlayer, playerBuffs, 40);
			CancelBuff(IPlayer, playerBuffs, 289);
			IPlayer.RemoveBuffIcon(0, 0, 2101, 227);
		}

		if ((GetTickCount() / 1000) % 2 == 0 && !playerBuffs.count(286) && playerBuffs.count(287))
		{
			int Grade = 1;
			int pSkill = IPlayer.GetSkillPointer(63);
			if (pSkill)
				Grade = *(DWORD*)(pSkill + 8);

			IPlayer.RemoveDef(100 * Grade);
			IPlayer.RemoveAbsorb(5 * Grade);
			CancelBuff(IPlayer, playerBuffs, 287);
			IPlayer.RemoveBuffIcon(0, 0, 1414, 147);
		}

		if ((GetTickCount() / 1000) % 2 == 0 && !playerBuffs.count(282) && playerBuffs.count(283))
		{
			CancelBuff(IPlayer, playerBuffs, 283);
			CancelBuff(IPlayer, playerBuffs, 284);
		}

		if (GetValue(playerBuffs, BuffNames::ShinyTarget) && playerBuffs.count(307))
		{
			IChar Caster((void*)GetValue(playerBuffs, BuffNames::ShinyTarget));

			if (!Caster.IsOnline())
			{
				CancelBuff(IPlayer, playerBuffs, 307);
				UpdateBuff(IPlayer, playerBuffs, BuffNames::ShinyTarget, BuffNames::BuffTime, 0);
			}

			if (!IPlayer.IsValid())
			{
				CancelBuff(IPlayer, playerBuffs, 307);
				UpdateBuff(IPlayer, playerBuffs, BuffNames::ShinyTarget, BuffNames::BuffTime, 0);
			}
		}

		if ((GetTickCount() / 1000) % 3 == 0 && GetRemain(playerBuffs, 121) > 10)
			IPlayer.SetBuffIcon(GetRemain(playerBuffs, 121) * 1000, 0, 3877, 442);

		if ((GetTickCount() / 1000) % 2 == 0 && playerBuffs.count(121) && !playerBuffs.count(273))
			Buff(IPlayer, playerBuffs, 273, 7200, 0);

		if ((GetTickCount() / 1000) % 2 == 0 && !playerBuffs.count(121) && playerBuffs.count(273))
		{
			IPlayer.RemoveBuffIcon(0, 0, 3877, 442);
			CancelBuff(IPlayer, playerBuffs, 273);
		}

		if ((GetTickCount() / 1000) % 2 == 0 && GetRemain(playerBuffs, 122) > 10)
			IPlayer.SetBuffIcon(GetRemain(playerBuffs, 122) * 1000, 0, 3879, 444);

		if ((GetTickCount() / 1000) % 2 == 0 && playerBuffs.count(122) && !playerBuffs.count(274))
			Buff(IPlayer, playerBuffs, 274, 7200, 0);

		if ((GetTickCount() / 1000) % 2 == 0 && !playerBuffs.count(122) && playerBuffs.count(274))
		{
			IPlayer.RemoveBuffIcon(0, 0, 3879, 444);
			CancelBuff(IPlayer, playerBuffs, 274);
		}

		if ((GetTickCount() / 1000) % 4 == 0 && GetRemain(playerBuffs, 123) > 10)
			IPlayer.SetBuffIcon(GetRemain(playerBuffs, 123) * 1000, 0, 3886, 451);

		if ((GetTickCount() / 1000) % 2 == 0 && playerBuffs.count(123) && !playerBuffs.count(275))
		{
			Buff(IPlayer, playerBuffs, 275, 7200, 0);
			IPlayer.AddOTP(15);
		}

		if ((GetTickCount() / 1000) % 2 == 0 && GetRemain(playerBuffs, 123) < 10 && playerBuffs.count(275))
		{
			IPlayer.RemoveBuffIcon(0, 0, 3886, 451);
			IPlayer.RemoveOTP(15);
			CancelBuff(IPlayer, playerBuffs, 275);
		}

		if ((GetTickCount() / 1000) % 3 == 0 && GetRemain(playerBuffs, 124) > 10)
			IPlayer.SetBuffIcon(GetRemain(playerBuffs, 124) * 1000, 0, 3880, 445);

		if ((GetTickCount() / 1000) % 2 == 0 && playerBuffs.count(124) && !playerBuffs.count(276))
		{
			Buff(IPlayer, playerBuffs, 276, 7200, 0);
			IPlayer.AddEva(7);
		}

		if ((GetTickCount() / 1000) % 2 == 0 && GetRemain(playerBuffs, 124) < 10 && playerBuffs.count(276))
		{
			IPlayer.RemoveBuffIcon(0, 0, 3880, 445);
			IPlayer.RemoveEva(7);
			CancelBuff(IPlayer, playerBuffs, 276);
		}

		if ((GetTickCount() / 1000) % 4 == 0 && GetRemain(playerBuffs, 125) > 10)
			IPlayer.SetBuffIcon(GetRemain(playerBuffs, 125) * 1000, 0, 3885, 450);

		if ((GetTickCount() / 1000) % 2 == 0 && playerBuffs.count(125) && !playerBuffs.count(277))
		{
			Buff(IPlayer, playerBuffs, 277, 7200, 0);
			IPlayer.AddHp(12);
		}

		if ((GetTickCount() / 1000) % 2 == 0 && GetRemain(playerBuffs, 125) < 10 && playerBuffs.count(277))
		{
			IPlayer.RemoveBuffIcon(0, 0, 3885, 450);
			IPlayer.RemoveHp(12);
			CancelBuff(IPlayer, playerBuffs, 277);
		}

		if ((GetTickCount() / 1000) % 4 == 0 && GetRemain(playerBuffs, 126) > 10)
			IPlayer.SetBuffIcon(GetRemain(playerBuffs, 126) * 1000, 0, 3884, 449);

		if ((GetTickCount() / 1000) % 2 == 0 && playerBuffs.count(126) && !playerBuffs.count(278))
		{
			Buff(IPlayer, playerBuffs, 278, 7200, 0);
			IPlayer.AddWis(12);
		}

		if ((GetTickCount() / 1000) % 2 == 0 && GetRemain(playerBuffs, 126) < 10 && playerBuffs.count(278))
		{
			IPlayer.RemoveBuffIcon(0, 0, 3884, 449);
			IPlayer.RemoveWis(12);
			CancelBuff(IPlayer, playerBuffs, 278);
		}

		if ((GetTickCount() / 1000) % 3 == 0 && GetRemain(playerBuffs, 127) > 10)
			IPlayer.SetBuffIcon(GetRemain(playerBuffs, 127) * 1000, 0, 3883, 448);

		if ((GetTickCount() / 1000) % 2 == 0 && playerBuffs.count(127) && !playerBuffs.count(279))
		{
			Buff(IPlayer, playerBuffs, 279, 7200, 0);
			IPlayer.AddInt(7);
		}

		if ((GetTickCount() / 1000) % 2 == 0 && GetRemain(playerBuffs, 127) < 10 && playerBuffs.count(279))
		{
			IPlayer.RemoveBuffIcon(0, 0, 3883, 448);
			IPlayer.RemoveInt(7);
			CancelBuff(IPlayer, playerBuffs, 279);
		}

		if ((GetTickCount() / 1000) % 4 == 0 && GetRemain(playerBuffs, 128) > 10)
			IPlayer.SetBuffIcon(GetRemain(playerBuffs, 128) * 1000, 0, 3882, 447);

		if ((GetTickCount() / 1000) % 2 == 0 && playerBuffs.count(128) && !playerBuffs.count(280))
		{
			Buff(IPlayer, playerBuffs, 280, 7200, 0);
			IPlayer.AddAgi(7);
		}

		if ((GetTickCount() / 1000) % 2 == 0 && GetRemain(playerBuffs, 128) < 10 && playerBuffs.count(280))
		{
			IPlayer.RemoveBuffIcon(0, 0, 3882, 447);
			IPlayer.RemoveAgi(7);
			CancelBuff(IPlayer, playerBuffs, 280);
		}

		if ((GetTickCount() / 1000) % 3 == 0 && GetRemain(playerBuffs, 129) > 10)
			IPlayer.SetBuffIcon(GetRemain(playerBuffs, 129) * 1000, 0, 3881, 446);

		if ((GetTickCount() / 1000) % 2 == 0 && playerBuffs.count(129) && !playerBuffs.count(281))
		{
			Buff(IPlayer, playerBuffs, 281, 7200, 0);
			IPlayer.AddStr(7);
		}

		if ((GetTickCount() / 1000) % 2 == 0 && GetRemain(playerBuffs, 129) < 10 && playerBuffs.count(281))
		{
			IPlayer.RemoveBuffIcon(0, 0, 3881, 446);
			IPlayer.RemoveStr(7);
			CancelBuff(IPlayer, playerBuffs, 281);
		}


		if ((GetTickCount() / 1000) % 2 == 0 && GetRemain(playerBuffs, BuffNames::Blessing) < 2 && playerBuffs.count(BuffNames::BlessingTrigger))
		{
			IPlayer.DecreaseMaxHp(5000);
			CancelBuff(IPlayer, playerBuffs, BuffNames::BlessingTrigger);
		}

		if (IPlayer.GetMap() == 6 && (GetTickCount() / 1000) % 5 == 0)
		{
			int Item = CPlayer::FindItem(Player, 1620, 1);

			if (!Item)
				IPlayer.PortToVillage();
		}

		if ((GetTickCount() / 1000) % 2 == 0 && GetRemain(playerBuffs, 266) < 10 && playerBuffs.count(267))
		{
			IPlayer.RemoveBuffIcon(0, 0, 3604, 418);
			IPlayer.RemoveMaxAttack(75);
			IPlayer.RemoveMinAttack(50);
			IPlayer.RemoveEva(10);
			CancelBuff(IPlayer, playerBuffs, 267);
		}

		if ((GetTickCount() / 1000) % 2 == 0 && GetRemain(playerBuffs, 268) < 10 && playerBuffs.count(269))
		{
			IPlayer.RemoveBuffIcon(0, 0, 3603, 417);
			IPlayer.RemoveMaxAttack(100);
			CancelBuff(IPlayer, playerBuffs, 269);
		}

		if ((GetTickCount() / 1000) % 2 == 0 && GetRemain(playerBuffs, 270) < 10 && playerBuffs.count(271))
		{
			IPlayer.RemoveBuffIcon(0, 0, 3602, 416);
			IPlayer.RemoveMinAttack(75);
			IPlayer.RemoveOTP(10);
			CancelBuff(IPlayer, playerBuffs, 271);
		}

		if ((GetTickCount() / 1000) % 2 == 0 && GetRemain(playerBuffs, 272) < 10 && playerBuffs.count(261))
		{
			IPlayer.RemoveBuffIcon(0, 0, 3645, 430);
			IPlayer.DecreaseMaxHp(1450);
			CancelBuff(IPlayer, playerBuffs, 261);
		}

		if ((GetTickCount() / 1000) % 2 == 0 && GetRemain(playerBuffs, 262) < 10 && playerBuffs.count(263))
		{
			IPlayer.RemoveBuffIcon(0, 0, 3646, 431);
			IPlayer.DecreaseMaxMp(900);
			CancelBuff(IPlayer, playerBuffs, 263);
		}

		if ((GetTickCount() / 1000) % 2 == 0 && !playerBuffs.count(120) && playerBuffs.count(259))
		{
			CancelBuff(IPlayer, playerBuffs, 259);
			IPlayer.RemoveBuffIcon(0, 0, 3691, 423);
			CPlayer::Write(Player, 0xFF, "dd", 238, 128);
		}

		if ((GetTickCount() / 1000) % 2 == 0 && !playerBuffs.count(259) && playerBuffs.count(120))
		{
			Buff(IPlayer, playerBuffs, 259, 604800, 0);
			IPlayer.SetBuffIcon(GetRemain(playerBuffs, 120) * 1000, 0, 3691, 423);
			CPlayer::Write(Player, 0xFF, "dd", 238, 0);
		}

		if ((GetTickCount() / 1000) % 2 == 0 && !playerBuffs.count(119) && playerBuffs.count(260))
		{
			CancelBuff(IPlayer, playerBuffs, 260);
			IPlayer.RemoveBuffIcon(0, 0, 3511, 370);
		}

		if ((GetTickCount() / 1000) % 2 == 0 && !playerBuffs.count(260) && playerBuffs.count(119))
		{
			Buff(IPlayer, playerBuffs, 260, 604800, 0);
			IPlayer.SetBuffIcon(GetRemain(playerBuffs, 119) * 1000, 0, 3511, 370);
		}
		// CJB Party

		if (IPlayer.IsParty() && CJBEXPActive){
			void *Party = (void *)CParty::FindParty(IPlayer.GetPartyID());

			if (Party)
			{
				for (int i = CParty::GetPlayerList(Party); i; i = CBaseList::Pop((void*)i))
				{
					IChar IMembers((void*)*(DWORD*)((void*)i));
					if (IMembers.GetClass() == 1 && (IMembers.GetSpecialty() == 43 || IMembers.GetSpecialty() == 11) && IMembers.IsInRange(IMembers, CJBRange))
					{
						IPlayer.SetBuffIcon(-2, -1, CJBSYS, CJBSYSB);
						Buff(IPlayer, playerBuffs, BuffNames::CJBEXP, 604800, 0);
					}
					else {
						if (playerBuffs.count(BuffNames::CJBEXP)){
							IPlayer.CancelBuff(BuffNames::CJBEXP);
							IPlayer.RemoveBuffIcon(0, 0, CJBSYS, CJBSYSB);
						}
					}
				}
				CIOObject::Release(Party);
			}
		}

		if (!IPlayer.IsParty() && playerBuffs.count(BuffNames::CJBEXP) && CJBEXPActive)
		{
			IPlayer.CancelBuff(BuffNames::CJBEXP);
			IPlayer.RemoveBuffIcon(0, 0, CJBSYS, CJBSYSB);
		}

		// Party Bonus
		if (My_PPActive) {
			int playerID = IPlayer.GetID();

			if (IPlayer.IsParty()) {
				void* Party = (void*)CParty::FindParty(IPlayer.GetPartyID());

				if (Party) {
					int PartySize = CParty::GetSize(Party);
					int membersInRange = CountPartyMembersInRange(IPlayer, Party, My_PPRange);

					if (playerPartySizes[playerID] != membersInRange) {
						if (playerPartySizes.count(playerID) && playerBuffs.count(11750 + playerPartySizes[playerID])) {
							int oldSize = playerPartySizes[playerID];
							PerfectParty oldPP = My_PerfectParty.find(oldSize)->second;
							IPlayer.RemoveBuffIcon(0, 0, oldPP.SBMsg, oldPP.SBKey);
							CancelBuff(IPlayer, playerBuffs, 11750 + oldSize);
						}

						playerPartySizes[playerID] = membersInRange;

						if (My_PerfectParty.count(membersInRange)) {
							PerfectParty pP = My_PerfectParty.find(membersInRange)->second;
							IPlayer.SetBuffIcon(-2, -1, pP.SBMsg, pP.SBKey);
							Buff(IPlayer, playerBuffs, 11750 + membersInRange, 604800, 0);
						}
					}

					CIOObject::Release(Party);
				}
			}
			else {
				if (playerPartySizes.count(playerID) && playerBuffs.count(11750 + playerPartySizes[playerID])) {
					int oldSize = playerPartySizes[playerID];
					PerfectParty oldPP = My_PerfectParty.find(oldSize)->second;
					IPlayer.RemoveBuffIcon(0, 0, oldPP.SBMsg, oldPP.SBKey);
					CancelBuff(IPlayer, playerBuffs, 11750 + oldSize);

					playerPartySizes.erase(playerID);
				}
			}
		}


		// Perfect Party
		if (IPlayer.IsParty() && PPActive)
		{
			int Knight = 0, Archer = 0, Mage = 0, Thief = 0, Shaman = 0, KnightAtk = 0, KnightDef = 0, MageAtk = 0, MageDef = 0, ArcherAtk = 0, ArcherDef = 0, ThiefAtk = 0, ThiefDef = 0, ShamanAtk = 0, ShamanDef = 0;
			void *Party = (void *)CParty::FindParty(IPlayer.GetPartyID());

			if (Party)
			{

				if (CParty::GetSize(Party) == 8) {
					for (int i = CParty::GetPlayerList(Party); i; i = CBaseList::Pop((void*)i))
					{
						IChar IMembers((void*)*(DWORD*)((void*)i));

						if (IMembers.IsOnline())
						{
							if (IMembers.GetClass() == 0)
								Knight++;

							if (IMembers.GetClass() == 0 && (IMembers.GetSpecialty() == 11 || IMembers.GetSpecialty() == 43))
								KnightDef++;

							if (IMembers.GetClass() == 0 && (IMembers.GetSpecialty() == 7 || IMembers.GetSpecialty() == 23))
								KnightAtk++;

							if (IMembers.GetClass() == 1)
								Mage++;

							if (IMembers.GetClass() == 1 && (IMembers.GetSpecialty() == 11 || IMembers.GetSpecialty() == 43))
								MageDef++;

							if (IMembers.GetClass() == 1 && (IMembers.GetSpecialty() == 7 || IMembers.GetSpecialty() == 23))
								MageAtk++;

							if (IMembers.GetClass() == 2)
								Archer++;

							if (IMembers.GetClass() == 2 && (IMembers.GetSpecialty() == 11 || IMembers.GetSpecialty() == 43))
								ArcherDef++;

							if (IMembers.GetClass() == 2 && (IMembers.GetSpecialty() == 7 || IMembers.GetSpecialty() == 23))
								ArcherAtk++;

							if (IMembers.GetClass() == 3)
								Thief++;

							if (IMembers.GetClass() == 3 && (IMembers.GetSpecialty() == 11 || IMembers.GetSpecialty() == 43))
								ThiefDef++;

							if (IMembers.GetClass() == 3 && (IMembers.GetSpecialty() == 7 || IMembers.GetSpecialty() == 23))
								ThiefAtk++;

							if (IMembers.GetClass() == 4)
								Shaman++;

							if (IMembers.GetClass() == 4 && (IMembers.GetSpecialty() == 11 || IMembers.GetSpecialty() == 43))
								ShamanDef++;

							if (IMembers.GetClass() == 4 && (IMembers.GetSpecialty() == 7 || IMembers.GetSpecialty() == 23))
								ShamanAtk++;
						}
					}

					if (ShamanDisabled && ThiefDisabled) {
						if (Knight >= 2 && Mage >= 2 && Archer >= 2)
						{
							if (KnightAtk >= 1 && KnightDef >= 1 && MageAtk >= 1 && MageDef >= 1 && ArcherAtk >= 1 && ArcherDef >= 1)
							{
								IPlayer.SetBuffIcon(-2, -1, PPSys, PPSysB);
								Buff(IPlayer, playerBuffs, 258, 604800, 0);
							}
						}
					}

					else {
						if (Knight == 2 && Mage == 2 && Archer == 2 && Thief == 2)
						{
							if (KnightAtk == 1 && KnightDef == 1 && MageAtk == 1 && MageDef == 1 && ArcherAtk == 1 && ArcherDef == 1 && ThiefAtk == 1 && ThiefDef == 1)
							{
								IPlayer.SetBuffIcon(-2, -1, PPSys, PPSysB);
								Buff(IPlayer, playerBuffs, 258, 604800, 0);
							}
						}

						if (Knight == 2 && Mage == 2 && Archer == 2 && Shaman == 2)
						{
							if (KnightAtk == 1 && KnightDef == 1 && MageAtk == 1 && MageDef == 1 && ArcherAtk == 1 && ArcherDef == 1 && ShamanAtk == 1 && ShamanDef == 1)
							{
								IPlayer.SetBuffIcon(-2, -1, PPSys, PPSysB);
								Buff(IPlayer, playerBuffs, 258, 604800, 0);
							}
						}

						if (Knight == 2 && Mage == 2 && Shaman == 2 && Thief == 2)
						{
							if (KnightAtk == 1 && KnightDef == 1 && MageAtk == 1 && MageDef == 1 && ShamanAtk == 1 && ShamanDef == 1 && ThiefAtk == 1 && ThiefDef == 1)
							{
								IPlayer.SetBuffIcon(-2, -1, PPSys, PPSysB);
								Buff(IPlayer, playerBuffs, 258, 604800, 0);
							}
						}

						if (Knight == 2 && Shaman == 2 && Archer == 2 && Thief == 2)
						{
							if (KnightAtk == 1 && KnightDef == 1 && ShamanAtk == 1 && ShamanDef == 1 && ArcherAtk == 1 && ArcherDef == 1 && ThiefAtk == 1 && ThiefDef == 1)
							{
								IPlayer.SetBuffIcon(-2, -1, PPSys, PPSysB);
								Buff(IPlayer, playerBuffs, 258, 604800, 0);
							}
						}

						if (Shaman == 2 && Mage == 2 && Archer == 2 && Thief == 2)
						{
							if (ShamanAtk == 1 && ShamanDef == 1 && MageAtk == 1 && MageDef == 1 && ArcherAtk == 1 && ArcherDef == 1 && ThiefAtk == 1 && ThiefDef == 1)
							{
								IPlayer.SetBuffIcon(-2, -1, PPSys, PPSysB);
								Buff(IPlayer, playerBuffs, 258, 604800, 0);
							}
						}
					}
				}
				else {
					if (playerBuffs.count(258))
					{
						IPlayer.RemoveBuffIcon(0, 0, PPSys, PPSysB);
						CancelBuff(IPlayer, playerBuffs, 258);
					}
				}
				CIOObject::Release(Party);
			}
			else {
				if (playerBuffs.count(258))
				{
					IPlayer.RemoveBuffIcon(0, 0, PPSys, PPSysB);
					CancelBuff(IPlayer, playerBuffs, 258);
				}
			}
		}
		else {
			if (playerBuffs.count(BuffNames::CallPlayer) || playerBuffs.count(BuffNames::CallPlayer2) || playerBuffs.count(BuffNames::CallBuffer)) {
				UpdateBuff(IPlayer, playerBuffs, BuffNames::CallBuffer, BuffNames::BuffTime, 0);
				UpdateBuff(IPlayer, playerBuffs, BuffNames::CallPlayer, BuffNames::BuffTime, 0);
				UpdateBuff(IPlayer, playerBuffs, BuffNames::CallPlayer2, BuffNames::BuffTime, 0);
			}

			if (playerBuffs.count(258))
			{
				IPlayer.RemoveBuffIcon(0, 0, PPSys, PPSysB);
				CancelBuff(IPlayer, playerBuffs, 258);
			}
		}

		if (IPlayer.GetClass() == 0 && IPlayer.GetLevel() >= 70 && IPlayer.GetSpecialty() == 43)
			IPlayer.SetBuffIcon(-2, -1, 2350, 295);

		if (IPlayer.IsOnline())
		{
			if (((IPlayer.GetClass() == 4 && IPlayer.GetSpecialty() >= 23) || (IPlayer.GetClass() == 0 && IPlayer.GetSpecialty() >= 23) || (IPlayer.GetClass() == 2 && IPlayer.GetSpecialty() >= 23) || (IPlayer.GetClass() == 3 && IPlayer.GetSpecialty() >= 23) || (IPlayer.GetClass() == 1 && IPlayer.GetSpecialty() == 23)) && IPlayer.GetLevel() >= 70)
			{
				int pSkill = IPlayer.GetSkillPointer(70);

				if (pSkill)
				{
					ISkill xSkill((void*)pSkill);

					if (xSkill.GetGrade() == 1 || BSOFSkyMax == 1)
						IPlayer.SetBuffIcon(-2, -1, 1767, 220);
					else
						IPlayer.SetBuffIcon(-2, -1, 3559 + xSkill.GetGrade(), 398 + xSkill.GetGrade());
				}

				pSkill = IPlayer.GetSkillPointer(71);

				if (pSkill && IPlayer.GetClass() == 4 && IPlayer.GetSpecialty() >= 43)
				{
					ISkill xSkill((void*)pSkill);

					if (xSkill.GetGrade() == 1 || BSOFSkyMax == 1)
						IPlayer.SetBuffIcon(-2, -1, 1767, 220);
					else
						IPlayer.SetBuffIcon(-2, -1, 3559 + xSkill.GetGrade(), 398 + xSkill.GetGrade());
				}
			}
		}

		if (IPlayer.GetClass() == 1 && IPlayer.GetSpecialty() == 43 && IPlayer.GetLevel() >= 70)
		{
			int pSkill = IPlayer.GetSkillPointer(71);

			if (pSkill)
			{
				ISkill xSkill((void*)pSkill);

				if (xSkill.GetGrade() == 1 || BSOFSkyMax == 1)
					IPlayer.SetBuffIcon(-2, -1, 1998, 221);
				else
					IPlayer.SetBuffIcon(-2, -1, 3565 + xSkill.GetGrade(), 404 + xSkill.GetGrade());
			}
		}

		if (IPlayer.GetLevel() >= 81 && IPlayer.GetSpecialty() >= 23)
		{
			int pSkill = IPlayer.GetSkillPointer(79);

			if (pSkill)
			{
				ISkill xSkill((void*)pSkill);
				IPlayer.IncreaseMana(2 * xSkill.GetGrade());
			}

			IPlayer.SetBuffIcon(-2, -1, 4259, 956);
		}

		if (IPlayer.GetClass() == 0 && IPlayer.GetLevel() >= 50 && (IPlayer.GetSpecialty() == 11 || IPlayer.GetSpecialty() == 43))
		{
			IPlayer.IncreaseMana(KnightManaCirculation);
			IPlayer.SetBuffIcon(-2, -1, 2260, 251);
		}

		if (IPlayer.GetClass() == 1 && IPlayer.GetLevel() >= 50 && (IPlayer.GetSpecialty() == 11 || IPlayer.GetSpecialty() == 43 || IPlayer.GetSpecialty() == 7 || IPlayer.GetSpecialty() == 23))
		{
			IPlayer.IncreaseMana(MageManaCirculation);
			IPlayer.SetBuffIcon(-2, -1, 2260, 251);
		}

		if (IPlayer.GetClass() == 2 && IPlayer.GetLevel() >= 50 && (IPlayer.GetSpecialty() == 11 || IPlayer.GetSpecialty() == 43))
		{
			IPlayer.IncreaseMana(ArcherManaCirculation);
			IPlayer.SetBuffIcon(-2, -1, 2260, 251);
		}

		if (IPlayer.GetClass() == 4 && IPlayer.GetLevel() >= 50 && IPlayer.GetSpecialty() > 3)
		{
			IPlayer.IncreaseMana(MageManaCirculation);
			IPlayer.SetBuffIcon(-2, -1, 2260, 251);
		}
		if (IPlayer.GetMap() == EmokMap && IPlayer.GetLevel() < EmokLvl)
		{
			IPlayer.PortToVillage();
			IPlayer.SystemMessage("You must be same or higher level required for E-Mok to teleport", TEXTCOLOR_RED);

		}

		if (IPlayer.GetMap() == LawlessMap && IPlayer.ScaniaTimer(60))
			CPlayer::Write(Player, 0xFF, "ds", 234, "You may use /leavechaos to leave the Chaos zone.");

		int EmokRemain = GetRemain(playerBuffs, 156);
		int EmokDay = IPlayer.GetProperty(PlayerProperty::EmokDay);
		int EmokEXP = IPlayer.GetProperty(PlayerProperty::EmokEXP);

		if ((GetTickCount() / 1000) % 2 == 0 && EmokRemain >= 10) {
			int Value = GetValue(playerBuffs, 156);
			IPlayer.SetBuffIcon(EmokRemain * 1000, 0, 3540 + (Value / 10), 382 + (Value / 10));
		}

		if ((GetTickCount() / 1000) % 5 == 0 && EmokRemain >= 10)
		{
			IPlayer.SetProperty(PlayerProperty::EmokTime, EmokRemain);
			CDBSocket::Write(83, "ddd", IPlayer.GetPID(), EmokDay, EmokRemain);
		}

		if (!playerBuffs.count(BuffNames::EmokTeleport)) {
			if (IPlayer.GetMap() == EmokMap && !EmokRemain) {
				int Value = GetValue(playerBuffs, 156);

				CancelBuff(IPlayer, playerBuffs, 156);
				IPlayer.SetProperty(PlayerProperty::EmokTime, 0);
				IPlayer.SetProperty(PlayerProperty::EmokEXP, 0);
				CDBSocket::Write(83, "ddd", IPlayer.GetPID(), EmokDay, 0);
				IPlayer.RemoveBuffIcon(0, 0, 3540 + (Value / 10), 382 + (Value / 10));
				IPlayer.PortToVillage();
			}

			if (EmokRemain && IPlayer.GetMap() != EmokMap)
			{
				IPlayer.SetProperty(PlayerProperty::EmokTime, EmokRemain);
				CDBSocket::Write(83, "ddd", IPlayer.GetPID(), EmokDay, EmokRemain);
				int Value = GetValue(playerBuffs, 156);
				IPlayer.SetProperty(PlayerProperty::EmokEXP, Value);
				IPlayer.RemoveBuffIcon(0, 0, 3540 + (Value / 10), 382 + (Value / 10));
				CancelBuff(IPlayer, playerBuffs, 156);
			}
		}

		if (TimeStr == "01:59:59" || TimeStr == "03:59:59" || TimeStr == "05:59:59" || TimeStr == "07:59:59" || TimeStr == "09:59:59" || TimeStr == "11:59:59" || TimeStr == "13:59:59" || TimeStr == "15:59:59" || TimeStr == "17:59:59" || TimeStr == "19:59:59" || TimeStr == "21:59:59" || TimeStr == "23:59:59") {
			IPlayer.SystemMessage("Caution: Playing for long time may harm your health.", TEXTCOLOR_RED);
		}

		if (TimeStr == "00:29:59" || TimeStr == "02:29:59" || TimeStr == "04:29:59" || TimeStr == "06:29:59" || TimeStr == "08:29:59" || TimeStr == "10:29:59" || TimeStr == "12:29:59" || TimeStr == "14:29:59" || TimeStr == "16:29:59" || TimeStr == "18:29:59" || TimeStr == "20:29:59" || TimeStr == "22:29:59") {
			IPlayer.SystemMessage("This Server is powered by KalTechSolutions - All Rights Reserved.", TEXTCOLOR_BLUE);
		}

		if (IPlayer.GetSpecialty() > 11 && IPlayer.GetSpecialty() < 20 && IPlayer.GetAdmin() <= 3 || IPlayer.GetSpecialty() > 43 && IPlayer.GetAdmin() <= 3)
		{
			IPlayer.SystemMessage("Job hack detected.", TEXTCOLOR_RED);
			IPlayer.Kick();
			return CPlayer::Tick(Player);
		}

		if (*(DWORD*)((int)IPlayer.GetOffset() + 1440) >= 10)
			SaveAllProperty((int)IPlayer.GetOffset(), 0, 0);

		if (IPlayer.IsOnline())
		{
			if (IPlayer.GetX() < 0 || IPlayer.GetY() < 0 || IPlayer.GetZ() < 0 || IPlayer.GetZ() > 199000)
			{
				IPlayer.SetX(257514);
				IPlayer.SetY(259273);
				IPlayer.SetZ(16168);
				SaveAllProperty((int)Player, 0, 0);
				playerBuffs.clear();
				IPlayer.Kick();
				return CPlayer::Tick(Player);
			}
		}

		if ((GetTickCount() / 1000) % 10 == 0)
		{
			int BOFHalfSet = GetValue(playerBuffs, BuffNames::BOFHalfSet);
			int BOFFullSet = GetValue(playerBuffs, BuffNames::BOFFullSet);

			if (BOFHalfSet == 46)
			{
				if (IPlayer.GetClass() == 4)
				{
					std::string Effect = "ef_setitem_01460" + Int2String(IPlayer.GetClass() - 2);
					IPlayer.AddFxToTarget(Effect, 1, 0, 0);
				}
				else {
					std::string Effect = "ef_setitem_01460" + Int2String(IPlayer.GetClass());
					IPlayer.AddFxToTarget(Effect, 1, 0, 0);
				}
			}

			if (BOFFullSet == 46)
			{
				if (IPlayer.GetClass() == 4)
				{
					std::string Effect = "ef_setitem_02460" + Int2String(IPlayer.GetClass() - 2);
					IPlayer.AddFxToTarget(Effect, 1, 0, 0);
				}
				else {
					std::string Effect = "ef_setitem_02460" + Int2String(IPlayer.GetClass());
					IPlayer.AddFxToTarget(Effect, 1, 0, 0);
				}
			}

			if (BOFHalfSet == 50 && IPlayer.GetClass() != 3)
			{
				if (IPlayer.GetClass() == 4)
				{
					std::string Effect = "ef_setitem_01550" + Int2String(IPlayer.GetClass() - 2);
					IPlayer.AddFxToTarget(Effect, 1, 0, 0);
				}
				else {
					std::string Effect = "ef_setitem_01550" + Int2String(IPlayer.GetClass());
					IPlayer.AddFxToTarget(Effect, 1, 0, 0);
				}
			}

			if (BOFHalfSet == 50 && IPlayer.GetClass() == 3)
				IPlayer.AddFxToTarget("ef_setitem_015003", 1, 0, 0);

			if (BOFFullSet == 50 && IPlayer.GetClass() != 3)
			{
				if (IPlayer.GetClass() == 4)
				{
					std::string Effect = "ef_setitem_02550" + Int2String(IPlayer.GetClass() - 2);
					IPlayer.AddFxToTarget(Effect, 1, 0, 0);
				}
				else {
					std::string Effect = "ef_setitem_02550" + Int2String(IPlayer.GetClass());
					IPlayer.AddFxToTarget(Effect, 1, 0, 0);
				}
			}

			if (BOFFullSet == 50 && IPlayer.GetClass() == 3)
				IPlayer.AddFxToTarget("ef_setitem_025003", 1, 0, 0);

			if (BOFHalfSet == 55 && IPlayer.GetClass() != 3)
			{
				if (IPlayer.GetClass() == 4)
				{
					std::string Effect = "ef_setitem_01500" + Int2String(IPlayer.GetClass() - 2);
					IPlayer.AddFxToTarget(Effect, 1, 0, 0);
				}
				else {
					std::string Effect = "ef_setitem_01500" + Int2String(IPlayer.GetClass());
					IPlayer.AddFxToTarget(Effect, 1, 0, 0);
				}
			}

			if (BOFHalfSet == 55 && IPlayer.GetClass() == 3)
				IPlayer.AddFxToTarget("ef_setitem_015503", 1, 0, 0);

			if (BOFFullSet == 55 && IPlayer.GetClass() != 3)
			{
				if (IPlayer.GetClass() == 4)
				{
					std::string Effect = "ef_setitem_02500" + Int2String(IPlayer.GetClass() - 2);
					IPlayer.AddFxToTarget(Effect, 1, 0, 0);
				}
				else {
					std::string Effect = "ef_setitem_02500" + Int2String(IPlayer.GetClass());
					IPlayer.AddFxToTarget(Effect, 1, 0, 0);
				}
			}

			if (BOFFullSet == 55 && IPlayer.GetClass() == 3)
				IPlayer.AddFxToTarget("ef_setitem_025503", 1, 0, 0);

			if (BOFHalfSet == 60)
			{
				if (IPlayer.GetClass() == 4)
				{
					std::string Effect = "ef_setitem_01600" + Int2String(IPlayer.GetClass() - 2);
					IPlayer.AddFxToTarget(Effect, 1, 0, 0);
				}
				else {
					std::string Effect = "ef_setitem_01600" + Int2String(IPlayer.GetClass());
					IPlayer.AddFxToTarget(Effect, 1, 0, 0);
				}
			}

			if (BOFFullSet == 60)
			{
				if (IPlayer.GetClass() == 4)
				{
					std::string Effect = "ef_setitem_02600" + Int2String(IPlayer.GetClass() - 2);
					IPlayer.AddFxToTarget(Effect, 1, 0, 0);
				}
				else {
					std::string Effect = "ef_setitem_02600" + Int2String(IPlayer.GetClass());
					IPlayer.AddFxToTarget(Effect, 1, 0, 0);
				}
			}

			if (BOFHalfSet == 65)
			{
				if (IPlayer.GetClass() == 4)
				{
					std::string Effect = "ef_setitem_01650" + Int2String(IPlayer.GetClass() - 2);
					IPlayer.AddFxToTarget(Effect, 1, 0, 0);
				}
				else {
					std::string Effect = "ef_setitem_01650" + Int2String(IPlayer.GetClass());
					IPlayer.AddFxToTarget(Effect, 1, 0, 0);
				}
			}

			if (BOFFullSet == 65)
			{
				if (IPlayer.GetClass() == 4)
				{
					std::string Effect = "ef_setitem_02650" + Int2String(IPlayer.GetClass() - 2);
					IPlayer.AddFxToTarget(Effect, 1, 0, 0);
				}
				else {
					std::string Effect = "ef_setitem_02650" + Int2String(IPlayer.GetClass());
					IPlayer.AddFxToTarget(Effect, 1, 0, 0);
				}
			}

			if (BOFHalfSet >= 70 && IPlayer.GetClass() != 3)
			{
				if (IPlayer.GetClass() == 4)
				{
					std::string Effect = "ef_setitem_01550" + Int2String(IPlayer.GetClass() - 2);
					IPlayer.AddFxToTarget(Effect, 1, 0, 0);
				}
				else {
					std::string Effect = "ef_setitem_01550" + Int2String(IPlayer.GetClass());
					IPlayer.AddFxToTarget(Effect, 1, 0, 0);
				}
			}

			if (BOFHalfSet >= 70 && IPlayer.GetClass() == 3)
				IPlayer.AddFxToTarget("ef_setitem_015003", 1, 0, 0);

			if (BOFFullSet >= 70 && IPlayer.GetClass() != 3)
			{
				if (IPlayer.GetClass() == 4)
				{
					std::string Effect = "ef_setitem_02550" + Int2String(IPlayer.GetClass() - 2);
					IPlayer.AddFxToTarget(Effect, 1, 0, 0);
				}
				else {
					std::string Effect = "ef_setitem_02550" + Int2String(IPlayer.GetClass());
					IPlayer.AddFxToTarget(Effect, 1, 0, 0);
				}
			}

			if (BOFFullSet >= 70 && IPlayer.GetClass() == 3)
				IPlayer.AddFxToTarget("ef_setitem_025003", 1, 0, 0);
		}

		if (*(DWORD*)((int)IPlayer.GetOffset() + 292) & 2147483648 && !playerBuffs.count(24))
			CChar::SubMState(IPlayer.GetOffset(), 0, 2147483648);

		// might crash check
		if (IPlayer.IsTransform() && GetTickCount() >= *(DWORD*)((int)Player + 1480))
		{
			if (IPlayer.GetRage() <= 0)
			{
				CPlayer::FreeTransform(Player);
			}
			else {
				int RageAmount = IPlayer.GetTransformGrade() & 0xF;

				if (RageAmount > 0)
				{
					if (RageAmount == 1)
						IPlayer.DecreaseRage(357);
					if (RageAmount == 2)
						IPlayer.DecreaseRage(761);
					if (RageAmount == 3)
						IPlayer.DecreaseRage(857);
					if (RageAmount == 4)
						IPlayer.DecreaseRage(1261);
				}

				*(DWORD*)((int)Player + 1480) = GetTickCount() + (((IPlayer.GetRage() <= 0) - 1) & 0xFFFF2928) + 60000;
			}
		}

		if (IPlayer.IsShopping() && strlen(ShopRewardCheck) && ((std::string)ShopRewardCheck == "true" || (std::string)ShopRewardCheck == "True"))
		{
			if (!playerBuffs.count(169)){
				Buff(IPlayer, playerBuffs, 169, ShopRewardTime, 0);
			}


			if (playerBuffs.count(169) && GetRemain(playerBuffs, 169) < 10)
			{
				Buff(IPlayer, playerBuffs, 169, ShopRewardTime, 0);
				for (int i = 0; i < RShopItems.size(); i++) {
					int Index = RShopItems[i];
					int Amount = RShopAmounts[i];
					int Level = RShopLevels[i];

					if (Index && Amount && Level) {
						if (ShopFortCheck && MapX == 32 && MapY == 29 && IPlayer.GetLevel() >= Level)
							IPlayer.InsertItem(Index, ShopBound ? 256 : 0, Amount * 2);
						else
						{
							if (IPlayer.GetLevel() >= Level)
								IPlayer.InsertItem(Index, ShopBound ? 256 : 0, Amount);
						}
					}
				}
			}
		}

		if (!IPlayer.IsShopping() && playerBuffs.count(169)){
			CancelBuff(IPlayer, playerBuffs, 169);
		}
		// crash check
		if (IPlayer.IsValid() && IPlayer.IsShopping() && IPlayer.IsFishing())
			(*(int(__thiscall **)(int, signed int))(*(DWORD*)Player + 112))((int)Player, 96);

		int Map = (MapX * 1000) + MapY;
		int QuestCheck = GetValue(playerBuffs, BuffNames::EventMapQuest);
		if (EventMaps.count(Map) || QuestCheck) {
			if (EventMapsQuests.count(QuestCheck)) {
				eventMap questEvent = EventMapsQuests.find(QuestCheck)->second;
				if (!EventMapsOn.count(QuestCheck)) {
					if (!playerBuffs.count(BuffNames::EventMapLapse)) {
						CancelBuff(Player, playerBuffs, BuffNames::EventMapQuest);
						IPlayer.RemoveSavedBuff(BuffNames::EventMapQuest);
						IPlayer.PortToVillage();
						IPlayer.CloseScreenTime();
					}
					if (questEvent.Type == 1 && !playerBuffs.count(BuffNames::InstanceCD))
						IPlayer.SaveBuff(BuffNames::InstanceCD, questEvent.Cooldown);
				}
				else {
					int RemainLapse = GetRemain(playerBuffs, BuffNames::EventMapLapse);
					if (questEvent.Type == 1 && !IPlayer.IsParty()) {
						CancelBuff(Player, playerBuffs, BuffNames::EventMapQuest);
						IPlayer.RemoveSavedBuff(BuffNames::EventMapQuest);
						IPlayer.PortToVillage();
						IPlayer.CloseScreenTime();
						IPlayer.SaveBuff(BuffNames::InstanceCD, questEvent.Cooldown);
					}
					else if (IPlayer.isDead())
						IPlayer.Rb(3);
					else if (!questEvent.Maps.count(Map))
						IPlayer.Teleport(0, questEvent.TX, questEvent.TY);
					else if (RemainLapse && RemainLapse <= 100)
						IPlayer.SystemMessage("You will be teleported out in " + Int2String(RemainLapse) + " seconds...", TEXTCOLOR_DARKGREEN);
				}
			}
			else {
				IPlayer.PortToVillage();
				IPlayer.CloseScreenTime();
			}
		}
		// crash check
		if (IPlayer.IsValid() && !CSMap::IsOnTile(*(void **)((int)Player + 320), (int)Player + 332, 131072) && !IPlayer.IsShopping() && !IPlayer.IsFishing())
		{
			int Around = IPlayer.GetObjectListAround(10);

			while (Around)
			{
				IChar Object((void*)CBaseList::Offset((void*)Around));

				if (Object.IsValid())
				{
					if (Object.GetType() == 1 && Object.GetDef() != 54123 && !Object.IsBuff(367))
					{
						Object.Buff(367, 1, 0);
						Object.SendGStateEx(Object.GetGStateEx());

						if (IPlayer.IsValid() && Object.IsValid() && !Object.IsMobHaveTarget() && Object.IsMobAggressive() && !playerBuffs.count(327) && !playerBuffs.count(329))
						{
							int Target = MonsterScanSight((int)Object.GetOffset(), 0);
							if (Target) {
								IChar xPlayer((void*)Target);

								if (xPlayer.IsValid()) {
									*(DWORD *)((int)Object.GetOffset() + 656) = 0;
									(*(void(__thiscall **)(DWORD, DWORD))(*(DWORD *)(int)Object.GetOffset() + 188))((int)Object.GetOffset(), Target);
								}
								else
									CSkill::ObjectRelease((void*)Target, (LONG)(Target + 356));
							}
						}
					}
				}

				Around = CBaseList::Pop((void*)Around);
			}
		}

		if (IPlayer.IsValid())
			IPlayer.SendGStateEx(IPlayer.GetGStateEx());

		//new
		if (FishLimit && !IPlayer.IsFishing() && playerBuffs.count(3958))
		{
			int LimitIndex = sha256(IPlayer.GetHWID() + IPlayer.GetIP());

			if (FishingLimit.count(LimitIndex)) {
				int Limited = FishingLimit.findValue(LimitIndex) - 1;
				if (!Limited)
					FishingLimit.erase(LimitIndex);
				else
					FishingLimit.replaceInsert(LimitIndex, Limited);
			}

			CancelBuff(IPlayer, playerBuffs, 3850);
			CancelBuff(IPlayer, playerBuffs, 3958);
		}

		if (ShoppingLimit && !IPlayer.IsShopping() && playerBuffs.count(3959))
		{
			int LimitIndex = sha256(IPlayer.GetHWID() + IPlayer.GetIP());

			if (FishingLimit.count(LimitIndex)) {
				int Limited = ShopLimit.findValue(LimitIndex) - 1;
				if (!Limited)
					ShopLimit.erase(LimitIndex);
				else
					ShopLimit.replaceInsert(LimitIndex, Limited);
			}

			CancelBuff(IPlayer, playerBuffs, 3959);
		}
		//endnew

		if (CChar::IsGState((int)Player, 32)) {
			if (playerBuffs.count(BuffNames::fish) && !playerBuffs.count(3850)) {

				int minutes = GetValue(playerBuffs, BuffNames::fish);
				if (!minutes)
					minutes = 3;

				*(DWORD *)((int)Player + 1468) = GetTickCount() + (minutes * 60000);
				Buff(IPlayer, playerBuffs, 3850, minutes * 61, 0);
			}

			if (GetTickCount() >= *(DWORD *)((int)Player + 1468))
			{
				int Rate = CTools::Rate(1, 1000);

				if (Rate > 0 && Rate <= 10 && FishHardest)
					CItem::InsertItem((int)Player, 27, FishHardest, 0, 1, -1);
				else if (Rate > 2 && Rate <= 20 && FishHard)
					CItem::InsertItem((int)Player, 27, FishHard, 0, 1, -1);
				else if (Rate > 4 && Rate <= 30 && FishNormal)
					CItem::InsertItem((int)Player, 27, FishNormal, 0, 1, -1);
				else if (Rate > 6 && Rate <= 60 && FishLow)
					CItem::InsertItem((int)Player, 27, FishLow, 0, 1, -1);
				else if (Rate > 12 && Rate <= 100 && FishLowest)
					CItem::InsertItem((int)Player, 27, FishLowest, 0, 1, -1);

				CancelBuff(IPlayer, playerBuffs, 3850);
			}

			if (IPlayer.IsShopping()) {
				IPlayer.SystemMessage("You can not fish and shop at the same time.", TEXTCOLOR_RED);
				(*(void(__thiscall **)(int, signed int))(*(DWORD *)(int)Player + 112))((int)Player, 96);
				CItem::InsertItem((int)Player, 27, 238, 0, 1, -1);
			}
			else if (!playerBuffs.count(3958)) {
				int WeaponType = 0;
				if (IPlayer.GetClass() == 0 && playerBuffs.count(BuffNames::WeaponWear)) {
					int ItemWeapon = CItem::CreateItem(GetValue(playerBuffs, BuffNames::WeaponWear), 0, 1, -1);
					if (ItemWeapon) {
						WeaponType = *(DWORD *)(*(DWORD *)(ItemWeapon + 40) + 72) - 2;
						CBase::Delete((void*)ItemWeapon);
					}
				}

				if (WeaponType == 19 || IPlayer.IsTransform()) {
					if (WeaponType == 19)
						IPlayer.SystemMessage("Please un-wear your weapon and try fishing again.", TEXTCOLOR_RED);
					else
						IPlayer.SystemMessage("Fishing can not be done during transformation.", TEXTCOLOR_RED);
					(*(void(__thiscall **)(int, signed int))(*(DWORD *)(int)Player + 112))((int)Player, 96);
					CItem::InsertItem((int)Player, 27, 238, 0, 1, -1);
				}
				else if (FishLimit) {
					if (FishingLimit.count(sha256(IPlayer.GetHWID() + IPlayer.GetIP())) && FishingLimit.findValue(sha256(IPlayer.GetHWID() + IPlayer.GetIP())) >= FishLimit) {
						IPlayer.SystemMessage("You have exceeded the fishing limit!", TEXTCOLOR_RED);
						(*(void(__thiscall **)(int, signed int))(*(DWORD *)(int)Player + 112))((int)Player, 96);
						CItem::InsertItem((int)Player, 27, 238, 0, 1, -1);
					}
					else {
						FishingLimit[sha256(IPlayer.GetHWID() + IPlayer.GetIP())]++;
						Buff(IPlayer, playerBuffs, 3958, 604800, 0);
					}
				}
			}
		}

		if (IPlayer.isInTrainingMap() && GetRemain(playerBuffs, 3723) >= 6)
			CPlayer::Write(Player, 0xFE, "dd", 207, GetValue(playerBuffs, BuffNames::TrainingTime) / 60);

		if (GetValue(playerBuffs, BuffNames::CostumeEffect) && (GetTickCount() / 1000) % 7200 == 0) {
			int NewB = GetValue(playerBuffs, BuffNames::CostumeEffect) + 1;
			int current = (NewB - 1) % 1000;
			if (current < 15) {
				UpdateBuff(IPlayer, playerBuffs, BuffNames::CostumeEffect, BuffNames::BuffTime, NewB);
				CChar::WriteInSight(IPlayer.GetOffset(), 0xFE, "ddd", 186, IPlayer.GetID(), NewB);
				IPlayer.AddStr(1);
				IPlayer.AddHp(1);
				IPlayer.AddAgi(1);
				IPlayer.AddWis(1);
				IPlayer.AddInt(1);
				IPlayer.SystemMessage("Back decoration level :" + Int2String(current + 1), TEXTCOLOR_PUPIL);
			}
		}

		SendCreate create = SendCreate();
		create.Riding = GetValue(playerBuffs, 349);
		create.NamePad = GetValue(playerBuffs, BuffNames::NamePad);
		create.ArmorWears = GetValue(playerBuffs, BuffNames::ArmorWears);
		create.CustWear = GetValue(playerBuffs, BuffNames::custWeap);
		create.SuitUsing = GetValue(playerBuffs, BuffNames::SuitsUsing);
		create.WepWear = GetValue(playerBuffs, BuffNames::WeaponWear);
		create.Pet1 = GetValue(playerBuffs, BuffNames::PetOwner);
		create.Pet2 = GetValue(playerBuffs, BuffNames::PetOwner2);
		create.Pet3 = GetValue(playerBuffs, BuffNames::PetOwner3);
		create.PetIID1 = GetValue(playerBuffs, BuffNames::PetIID);
		create.PetIID2 = GetValue(playerBuffs, BuffNames::PetIID2);
		create.PetIID3 = GetValue(playerBuffs, BuffNames::PetIID3);
		create.CostumeEffect = GetValue(playerBuffs, BuffNames::CostumeEffect);
		create.CostumeEffectCheck = GetValue(playerBuffs, BuffNames::CostumeEffectCheck);
		create.LawlessEXP = GetValue(playerBuffs, BuffNames::LawlessEXP);
		create.GState = GetValue(playerBuffs, BuffNames::TriangularState);
		SendCreatePlayer.replaceInsert((int)Player, create);

		if ((GetTickCount() / 1000) % 2 == 0) {
			auto itArea = RectArea.find((MapX * 1000) + MapY);

			POINT pt = *(POINT *)((int)Player + 324);
			if (itArea != RectArea.end()) {
				std::vector<RectLevel>& Rects = itArea->second;
				for (auto x = Rects.begin(); x != Rects.end(); x++) {
					if (PtInRect(&x->rectangle, pt)) {
						if (IPlayer.GetLevel() < x->LevelMin || IPlayer.GetLevel() > x->LevelMax) {
							IPlayer.PortToVillage();
							IPlayer.SystemMessage("This zone can only be played by players between level " + Int2String(x->LevelMin) + " and " + Int2String(x->LevelMax) + ".", TEXTCOLOR_RED);
						}
						break;
					}
				}
			}

			if (BFAFKActive && IPlayer.GetMap() == BFMap)
			{
				int BAFKTime = GetValue(playerBuffs, BuffNames::AFKTime);
				if (BAFKTime)
				{
					if (BAFKTime <= GetTickCount()){
						IPlayer.PortToVillage();
						IPlayer.RemoveSetRed();
						IPlayer.RemoveSetBlue();
						IPlayer.CloseScenario3_3Score();
						IPlayer.RemoveBuffIcon(0, 0, 0, 20);
						CancelBuff(IPlayer, playerBuffs, 361);
						CancelBuff(IPlayer, playerBuffs, 160);
						CancelBuff(IPlayer, playerBuffs, 161);
						IPlayer.SystemMessage("Due to being AFK in this place/system, you have been ported out", TEXTCOLOR_YELLOW);
						IPlayer.UpdateBuff(BuffNames::AFKTime, BuffNames::BuffTime, 0);
					}
				}
				else
					IPlayer.UpdateBuff(BuffNames::AFKTime, BuffNames::BuffTime, GetTickCount() + (BattlefieldAFK * 1000));
			}

			bool AFKFound = false;
			auto itAfk = AFKMap.find((MapX * 1000) + MapY);
			if (itAfk != AFKMap.end()) {
				int AFKTime = GetValue(playerBuffs, BuffNames::AFKTime);
				std::vector<AFKCheck>& AFK = itAfk->second;
				for (auto x = AFK.begin(); x != AFK.end(); x++) {
					if (PtInRect(&x->rectangle, pt)) {
						AFKFound = true;
						if (AFKTime) {
							if (AFKTime <= GetTickCount() && !IPlayer.IsBuff(BuffNames::BypassAFK)) {
								IPlayer.ClearPVP();
								IPlayer.PortToVillage();
								IPlayer.SystemMessage("Due to being AFK in this place/system, you have been ported out", TEXTCOLOR_YELLOW);
								IPlayer.UpdateBuff(BuffNames::AFKTime, BuffNames::BuffTime, 0);
							}
						}
						else
							IPlayer.UpdateBuff(BuffNames::AFKTime, BuffNames::BuffTime, GetTickCount() + (x->seconds * 1000));
						break;
					}
				}
				if (!AFKFound && AFKTime)
					IPlayer.UpdateBuff(BuffNames::AFKTime, BuffNames::BuffTime, 0);
			}

		}

		bool macroCanceled = false;
		if (isInMacroMap(MapX, MapY)) {
			if (playerBuffs.count(BuffNames::MacroCheck) && !playerBuffs.count(BuffNames::BypassAFK)) {
				int TimeRemain = GetRemain(playerBuffs, BuffNames::MacroCheck);
				if (TimeRemain <= MacroStartTime + 1) {
					if (TimeRemain == 1) {
						macroCanceled = true;
						IPlayer.UpdateBuff(BuffNames::MacroMap, BuffNames::BuffTime, 1);
						CancelBuff(IPlayer, playerBuffs, BuffNames::MacroCheck);
						IPlayer.ClearPVP();
						IPlayer.PortToVillage();
						IPlayer.SystemMessage("Failed the afk check.", TEXTCOLOR_RED);
						CConsole::Red("Player PID : %d Name : %s has failed the Macro Check", IPlayer.GetPID(), IPlayer.GetName());

						CPlayer::Write((void*)Player, 0xFE, "ddd", 191, 0, 0);
					}
					else {
						int Value = GetValue(playerBuffs, BuffNames::MacroCheck);
						if (Value)
							CPlayer::Write((void*)Player, 0xFE, "ddd", 191, TimeRemain - 1, Value << 19);
					}
				}
			}
			else if (GetTickCount() - *(DWORD *)((int)Player + 1464) < 3000)
				Buff(IPlayer, playerBuffs, BuffNames::MacroCheck, CTools::Rate(MinMacro, MaxMacro), CTools::Rate(97, 122));
		}

		if (playerBuffs.count(BuffNames::MacroCheck) && (GetTickCount() - *(DWORD *)((int)Player + 1464)) > 31000) {
			CancelBuff(IPlayer, playerBuffs, BuffNames::MacroCheck);
			CPlayer::Write((void*)Player, 0xFE, "ddd", 191, 0, 0);
		}
		playerBuffs.clear();
	}

	return CPlayer::Tick(Player);
}