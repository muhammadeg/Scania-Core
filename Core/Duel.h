void HuntingAddAll(int GID, std::string guildName) {
	HuntingID = GID;
	HuntingName = guildName;
}

bool isPKIgnoredItem(int Index) {
	return PKIgnoreItem.count(Index) ? true : false;
}

void __fastcall PKKill(void *Player, void *edx, int Playerr)
{
	IChar Killer(Player);
	IChar Killed((void*)Playerr);

	bool AssassinKiller = Killed.IsBuff(104) ? true : false;

	bool PlayerKilled = Killer.IsBuff(104) ? true : false;

	bool AssaCheck = (AssassinKiller || PlayerKilled) ? true : false;

	CPlayer::PKKill(Player, Playerr);

	if (AssaCheck)
		ToAssassinWebhook("Player " + std::string(Killer.GetName()) + " has killed " + std::string(Killed.GetName()));
	
	if (AssaCheck){
		Killer.SetHonor(0, 0, 0, 0, 0, 0, 0, 0, 0, 1);
		Killed.SetHonor(0, 0, 1, 0, 0, 0, 0, 0, 0, 0);
	}

	if (PKKillActive && AssaCheck && abs(Killer.GetLevel() - Killed.GetLevel()) <= PKLvlDiff) {
		int Rate = CTools::Rate(1, 1000);
		if ((AssassinKiller && Rate <= PKKillChance) || (PlayerKilled && Rate <= PKKillPlayerChance)) {
			int Item = Killed.RandomItem();
			if (Item) {
				IItem IItem((void*)Item);
				int Index = IItem.CheckIndex();
				int Amount = IItem.GetAmount();
				CIOCriticalSection::Enter((struct _RTL_CRITICAL_SECTION*)((int)Killed.GetOffset() + 1020));
				int v18 = (*(int(__thiscall **)(int, int, signed int, int))(*(DWORD *)Item + 132))(Item, Playerr, 10, !IItem.GetAmount() ? 1 : IItem.GetAmount());
				if (v18 == Item)
					CPlayer::_OutOfInven((void*)Playerr, Item);
				CIOCriticalSection::Leave((void*)((char*)Killed.GetOffset() + 1020));

				if (v18) {
					CIOObject::AddRef(v18);

					if (CPlayer::InsertItem((void*)Player, 10, v18) != 1)
						CBase::Delete((void*)v18);

					CIOObject::Release((void*)v18);
				}

				CPlayer::Write((void*)Playerr, 0xFE, "ddd", 179, Index, Amount);
			}
		}
	}

	if (PSActive && AssaCheck && Killer.GetBuffValue(BuffNames::IPAddress) != Killed.GetBuffValue(BuffNames::IPAddress)) {
		if (PSLimit) {
			int KillerIsBuff = Killer.IsBuff(BuffNames::AssaPointsLimit);
			int KilledIsBuff = Killed.IsBuff(BuffNames::AssaPointsLimit);

			if (!KillerIsBuff || !KilledIsBuff) {
				int Hour = 23 - String2Int(Time::GetHour());
				int Minutes = 59 - String2Int(Time::GetMinute());
				int TimeLeft = (Hour * 60 * 60) + (Minutes * 60) + String2Int(Time::GetSecond());
				if (!KillerIsBuff)
				{
					Killer.Buff(BuffNames::AssaPointsLimit, TimeLeft, 1);
					Killer.systemReward(KrPSsysReward);
					if (PeaceEvil)
					Killer.AddHousePoints(1);
				}

				if (!KilledIsBuff)
				{
					Killed.Buff(BuffNames::AssaPointsLimit, TimeLeft, 1);
					Killed.systemReward(KdPSsysReward);
					if (PeaceEvil)
					Killed.AddHousePoints(-1);
				}
			}
			else {
				int KrLimitCheck = Killer.GetBuffValue(BuffNames::AssaPointsLimit);
				int KdLimitCheck = Killed.GetBuffValue(BuffNames::AssaPointsLimit);

				if (KrLimitCheck < PSLimit) {
					Killer.UpdateBuff(BuffNames::AssaPointsLimit, BuffNames::BuffTime, KrLimitCheck + 1);
					Killer.systemReward(KrPSsysReward);
					if (PeaceEvil)
					Killer.AddHousePoints(1);
				}
				if (KdLimitCheck < PSLimit) {
					Killer.UpdateBuff(BuffNames::AssaPointsLimit, BuffNames::BuffTime, KdLimitCheck + 1);
					Killer.systemReward(KdPSsysReward);
					if (PeaceEvil)
					Killer.AddHousePoints(1);

				}
			}
		}
		else
			Killer.systemReward(KrPSsysReward);
		Killed.systemReward(KdPSsysReward);
		if (PeaceEvil){
			Killer.AddHousePoints(1);
			Killed.AddHousePoints(-1);
		}
	}

	if (Killer.GetMap() == LawlessMap) {
		std::string msg = (std::string)Killer.GetName() + " has killed " + (std::string)Killed.GetName() + ".";
		CChar::WriteInSight(Killer.GetOffset(), 0xFE, "dds", 178, RGB(255, 255, CTools::Rate(100, 255)), msg.c_str());

		Killer.SystemMessage("You have killed " + (std::string)Killed.GetName() + " inside the lawless zone.", TEXTCOLOR_GREEN);
		Killed.SystemMessage("You have been killed by " + (std::string)Killer.GetName() + " inside the lawless zone.", TEXTCOLOR_RED);

		int Points = Killed.GetBuffValue(BuffNames::LawlessPoints);
		if (Points) {
			int LostPTs = (Points * LawlessPKill) / 100;
			UpdateLawless((int)Killed.GetOffset(), -LostPTs);
			UpdateLawless((int)Killer.GetOffset(), LostPTs);
		}
	}

	if (TriangularBattle::Active && Killed.GetMap() == TBMap) {
		Killer.SetHonor(0, 0, 0, 0, 0, 0, 0, 0, 0, 1);
		if (PeaceEvil){
		Killer.AddHousePoints(1);
		Killed.AddHousePoints(-1);
	}
		Killed.SetHonor(0, 0, 1, 0, 0, 0, 0, 0, 0, 0);


		if (Killed.IsBuff(BuffNames::TriangularTime)) {
			if (Killer.GetBuffValue(BuffNames::TriangularTime))
				PutBackToAlter(Killed, 0);
			else {
				CPlayer::RemoveItem(Killed.GetOffset(), 27, 1941, 1);
				int Time = Killed.GetBuffRemain(BuffNames::TriangularTime);
				Killer.Buff(BuffNames::TriangularTime, Time, 10 * Killed.GetBuffValue(BuffNames::TriangularTime));
				Killed.CancelBuff(BuffNames::TriangularTime);
				CChar::WriteInSight(Killed.GetOffset(), 0xFE, "ddd", 170, Killed.GetID(), 0);
				CChar::WriteInSight(Killer.GetOffset(), 0xFE, "ddd", 170, Killer.GetID(), 1);
				CItem::InsertItem((int)Killer.GetOffset(), 27, 1941, 256, 1, -1);

				int Item = CPlayer::FindItem(Killer.GetOffset(), 1941, 1);
				if (Item)
					Killer.UpdateBuff(BuffNames::TriangularItemIID, BuffNames::BuffTime, *(DWORD*)(Item + 36));

				Killer.SystemMessage("You got " + Int2String(Time) + " seconds before putting the Ancient Essence to your altar.", TEXTCOLOR_BLUELIGHT);
			}
		}
		ClearTBPlayer(Killed);
	}
	if (Protect32::Active && Killed.GetMap() == PLMap && Killer.GetMap() == PLMap)
	{
		Killer.SetHonor(KillerHPPL, KillerRPPL, 0, 0, 0, 0, 0, 0, 0, 0);
		Killed.SetHonor(KilledHPPL, KilledRPPL, 0, 0, 0, 0, 0, 0, 0, 0);
		if (PeaceEvil){
			Killer.AddHousePoints(1);
			Killed.AddHousePoints(-1);
		}
	}
	if (Battlefield::Active && Killed.GetMap() == BFMap && Killer.GetMap() == BFMap)
	{
		Killer.SetHonor(KillerHPBF, KillerRPBF, 0, 0, 0, 0, 0, 0, 0, 0);
		Killed.SetHonor(KilledHPBF, KilledRPBF, 0, 0, 0, 0, 0, 0, 0, 0);
		if (PeaceEvil){
			Killer.AddHousePoints(1);
			Killed.AddHousePoints(-1);
		}
	}
	if (Scenario::Active && Killed.GetMap() == ScenarioMap && Killer.GetMap() == ScenarioMap)
	{
		Killer.SetHonor(KillerHPGVG, KillerRPGVG, 0, 0, 0, 0, 0, 0, 0, 0);
		Killed.SetHonor(KilledHPGVG, KilledRPGVG, 0, 0, 0, 0, 0, 0, 0, 0);
		if (PeaceEvil){
			Killer.AddHousePoints(1);
			Killed.AddHousePoints(-1);
		}
	}

	if (SufferingValley::Active && Killer.GetMap() == SVMap && Killed.GetMap() == SVMap) {
		Killer.SetHonor(0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
		Killed.SetHonor(0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
		if (PeaceEvil){
			Killer.AddHousePoints(1);
			Killed.AddHousePoints(-1);
		}

		bool IsBlue = SVParticipantsBlue.count(Killer.GetPID());
		bool IsRed = !IsBlue ? SVParticipantsRed.count(Killer.GetPID()) : false;

		if (IsBlue)
			SufferingValley::BlueScore += SVPtPlayer;
		else if (IsRed)
			SufferingValley::RedScore += SVPtPlayer;
	}

	if (SinEvent::Active && Killer.GetMapX() == SEMapX && Killer.GetMapY() == SEMapY) {
		std::string msg = (std::string)Killed.GetName() + " has been killed by " + (std::string)Killer.GetName() + ".";
		CChar::WriteInSight(Killer.GetOffset(), 0xFE, "dds", 178, RGB(255, 255, CTools::Rate(100, 255)), msg.c_str());
		Killer.UpdateBuff(BuffNames::SinEventPlayers, BuffNames::BuffTime, Killer.GetBuffValue(BuffNames::SinEventPlayers) + SEPtsPerPlayer);
	}
}

int __fastcall EndPvP(void* Player, void *edx, int nextPlayer, int a6, int a7, int a8) {
	IChar Winner((void*)nextPlayer);
	IChar Loser(Player);

	if (Winner.IsOnline() && Loser.IsOnline() && Winner.IsBuff(3089) && Loser.IsBuff(3089) && Loser.GetID() == Winner.GetBuffValue(BuffNames::BetOpponent) && Loser.GetBuffValue(BuffNames::BetOpponent) == Winner.GetID() && BetItems.count(Winner.GetPID() * Loser.GetPID())) {
		std::vector<BetTrade> Items = BetItems.find(Winner.GetPID() * Loser.GetPID())->second;
		for (int i = 0; i < (int)Items.size(); i++) {
			BetTrade Item = Items[i];
			IItem IItem((void*)Item.Item);

			if (IItem.Exists()) {
				if (a6 != 4) {
					if (Item.Item) {
						CIOObject::AddRef(Item.Item);

						if (CPlayer::InsertItem(Winner.GetOffset(), 10, Item.Item) != 1)
							CBase::Delete((void*)Item.Item);

						CIOObject::Release((void*)Item.Item);
					}
				}
				else {
					int PID = Item.PID;
					IChar Offset(0);
					if (PID == Winner.GetPID())
						Offset = Winner;
					else if (PID == Loser.GetPID())
						Offset = Loser;

					if (Offset.IsOnline()) {
						if (Item.Item) {
							CIOObject::AddRef(Item.Item);

							if (CPlayer::InsertItem(Offset.GetOffset(), 10, Item.Item) != 1)
								CBase::Delete((void*)Item.Item);

							CIOObject::Release((void*)Item.Item);
						}
					}
				}
			}
		}
		std::string msg = "";
		if (a6 != 4)
			msg = (std::string)Winner.GetName() + " has won the duel bet against " + (std::string)Loser.GetName();
		else
			msg = "Duel bet between " + (std::string) Loser.GetName() + "and " + (std::string)Winner.GetName() + " has ended in a draw";

		CChar::WriteInSight(Winner.GetOffset(), 0xFF, "dsd", 248, msg.c_str(), TEXTCOLOR_YELLOW);
	}

	BetItems.erase(Winner.GetPID() * Loser.GetPID());

	Winner.UpdateBuff(BuffNames::BetOpponent, BuffNames::BuffTime, 0);
	Winner.CancelBuff(3089);

	Loser.UpdateBuff(BuffNames::BetOpponent, BuffNames::BuffTime, 0);
	Loser.CancelBuff(3089);

	return CPlayer::EndPvP(Player, nextPlayer, a6, a7, a8);
}