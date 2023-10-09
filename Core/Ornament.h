int __cdecl GetLowestTrigramGrade(IChar IPlayer)
{
	int Grade = 20;

	for (int i = BuffNames::TrigramHP; i <= BuffNames::TrigramHth; i++) {
		int thisGrade = IPlayer.GetBuffValue(i);
		if (thisGrade < Grade)
			Grade = thisGrade;
	}

	if (Grade == 20) Grade = 0;
	return Grade;
}

void insertPet(IChar Player, IItem Item) {
	if (Player.numberOfPets() != 3)
	{
		int Type = 0;
		int IIDType = 0;
		
		if (isNormalPet(Item.CheckIndex())) {
			Type = BuffNames::PetOwner;
			IIDType = BuffNames::PetIID;
		}

		if (isMonsterPet(Item.CheckIndex())) {
			Type = BuffNames::PetOwner2;
			IIDType = BuffNames::PetIID2;
		}

		if (isPremiumPet(Item.CheckIndex())) {
			Type = BuffNames::PetOwner3;
			IIDType = BuffNames::PetIID3;
		}

		if (Type && IIDType) {
		
			int Picks = PetTime.count(Item.CheckIndex()) ? PetTime.find(Item.CheckIndex())->second.Pick : 0;
			if (Picks == 1) {

				int Range = Player.GetPickRange();
				if (PetTime.find(Item.CheckIndex())->second.Range > Range)
					Player.SetPickRange(PetTime.find(Item.CheckIndex())->second.Range);

				int Pick = Player.GetBuffValue(BuffNames::PetPick);
				Player.UpdateBuff(BuffNames::PetPick, BuffNames::BuffTime, Pick + 1);

				CPlayer::Write(Player.GetOffset(), 0xFF, "dd", 221, 1);
			}

			if (!Player.GetBuffValue(Type) && PetTime.count(Item.CheckIndex()) && PetTime.find(Item.CheckIndex())->second.Monster)
				Summon((int)Player.GetOffset(), Player.GetMap(), Player.GetX() - 6, Player.GetY() - 6, PetTime.find(Item.CheckIndex())->second.Monster, 1, false, 0, 0, 1);
			else {
				if (Item.CheckIndex() >= 2004 && Item.CheckIndex() <= 2007)
					CChar::WriteInSight(Player.GetOffset(), 221, "dwdb", Player.GetID(), (unsigned short)Item.CheckIndex(), Item.GetIID(), 2);
				else
					CChar::WriteInSight(Player.GetOffset(), 221, "dwdb", Player.GetID(), (unsigned short)Item.CheckIndex(), Item.GetIID(), 0);
			}

			Player.UpdateBuff(Type, BuffNames::BuffTime, Item.CheckIndex());
			Player.UpdateBuff(IIDType, BuffNames::BuffTime, Item.GetIID());

		}
	}
}

bool HaninEquipped(IChar IPlayer, int Type) {
	for (int i = BuffNames::Essence1; i <= BuffNames::Essence5; i++) {
		int IID = IPlayer.GetBuffValue(i);

		itemStat.Enter();
		int Valuex = GetItemStat.count(IID) ? GetItemStat.find(IID)->second : 0;
		itemStat.Leave();

		if ((Valuex % 100) == Type)
			return true;
	}
	return false;
}

int getHaninEquip(IChar IPlayer, int IID) {
	for (int i = BuffNames::Essence1; i <= BuffNames::Essence5; i++) {
		if (IPlayer.GetBuffValue(i) == IID)
			return i - BuffNames::Essence1;
	}
	return -1;
}

bool isEssensed(IChar IPlayer, int IID) {
	return ((IPlayer.GetBuffValue(BuffNames::Essence1) == IID) || (IPlayer.GetBuffValue(BuffNames::Essence2) == IID) || (IPlayer.GetBuffValue(BuffNames::Essence3) == IID) || (IPlayer.GetBuffValue(BuffNames::Essence4) == IID) || (IPlayer.GetBuffValue(BuffNames::Essence5) == IID));
}

int __fastcall OrnamentPutOff(void *Itemx, void *edx, int Playerx)
{
	IItem Item(Itemx);
	IChar Player((void*)Playerx);
	int N = 0;
	if (Player.IsOnline() && Item.Exists())
	{
		if (isSoulPocket(Item.CheckIndex())) {
			Player.UpdateBuff(BuffNames::SoulPocketIID, BuffNames::BuffTime, 0);
			Player.UpdateBuff(BuffNames::SoulPIndex, BuffNames::BuffTime, 0);
			int bf = Player.GetBuffValue(BuffNames::SoulPocketAmount);
			itemStat.Enter();
			GetItemStat[Item.GetIID()] = bf;
			itemStat.Leave();
			CDBSocket::Write(90, "dd", bf, Item.GetIID());
			Player.UpdateBuff(BuffNames::SoulPocketAmount, BuffNames::BuffTime, 0);
			Player.CancelBuff(3704);
		}

		if (BeltBuffs.count(Item.CheckIndex())) {
			if (Player.IsBuff(BuffNames::BeltBuff)) {
				Player.SystemMessage("Please wait for the ornament buff to end before taking your item.", TEXTCOLOR_RED);
				return 0;
			}

			Player.CancelBuff(BuffNames::Belt);
			Player.CancelBuff(BuffNames::BeltBuff);
		}

		if (NecklaceBuffs.count(Item.CheckIndex())) {
			if (Player.IsBuff(BuffNames::OrnamentDmg)) {
				Player.SystemMessage("Please wait for the ornament buff to end before taking your item.", TEXTCOLOR_RED);
				return 0;
			}

			Player.CancelBuff(BuffNames::Necklace);
		}

		if(isNecklace2(Item.CheckIndex()))
			Player.CancelBuff(3705);

		if (Item.CheckIndex() >= 3381 && Item.CheckIndex() <= 3383 && (Player.GetBuffValue(BuffNames::Essence1) || Player.GetBuffValue(BuffNames::Essence2) || Player.GetBuffValue(BuffNames::Essence3) || Player.GetBuffValue(BuffNames::Essence4) || Player.GetBuffValue(BuffNames::Essence5)))
			return 0;

		if (Item.GetType() == -3 && Player.IsBuff(3879))
			Player.CancelBuff(3879);

		if (Item.CheckIndex() >= 3381 && Item.CheckIndex() <= 3383 && Player.GetBuffValue(BuffNames::MirrorBuff))
			Player.UpdateBuff(BuffNames::MirrorBuff, BuffNames::BuffTime, 0);

		if (Item.CheckIndex() >= 3384 && Item.CheckIndex() <= 3386 && Player.GetBuffValue(BuffNames::MirrorBuff))
		{
			int MirrorIID = Player.GetBuffValue(BuffNames::MirrorBuff);
			int Itemy = Player.ItemPointer(MirrorIID);

			if (!Itemy)
				return 0;

			IItem Mirror((void*)Itemy);

			int Valuex = 0, Type = 0; double Stat = 0;

			itemStat.Enter();
			int Counted = GetItemStat.count(Item.GetIID()) ? 1 : 0;
			itemStat.Leave();

			if (!Counted)
				return 0;

			itemStat.Enter();
			Valuex = GetItemStat.find(Item.GetIID())->second;
			itemStat.Leave();

			Type = Valuex % 100;
			Stat = Valuex / 10000;

			int HaninNum = getHaninEquip(Player, Item.GetIID());

			int Removable = 0;

			if (HaninNum != -1)
			{
				Removable = Player.GetBuffValue(BuffNames::HaninStats1 + HaninNum);
				if (Type == 0) Player.RemoveStr(Removable);
				if (Type == 1) Player.RemoveWis(Removable);
				if (Type == 2) Player.RemoveInt(Removable);
				if (Type == 3) Player.RemoveHp(Removable);
				if (Type == 4) Player.RemoveAgi(Removable);
				if (Type == 5) Player.RemoveOTP(Removable);
				if (Type == 6) Player.RemoveEva(Removable);
				if (Type == 7) Player.RemoveDef(Removable);
				if (Type == 8) Player.DecreaseResist((Stat / 3) + 1);
				if (Type == 9) Player.RemoveAbsorb(Stat);
				if (Type == 10) Player.DecreaseMaxHp(Removable);
				if (Type == 11) Player.DecreaseMaxMp(Removable);
				if (Type == 12) Player.DecreaseMovingSpeed(Stat);
				if (Type == 13) Player.RemoveMinAttack(Removable);
				if (Type == 14) Player.RemoveMinAttack(Removable);
				if (Type == 15) Player.DecreaseCritRate((Stat / 3) + 1);
				if (Type == 16) Player.DecreaseCritDamage((Stat / 2) + 1);
				if (Type == 17) Player.RemoveDeathBlow((Stat / 3) + 1);
				if (Type == 18) Player.RemoveMaxAttack(Removable);
				if (Type == 19) Player.RemoveMaxAttack(Removable);
				if (Type == 20 && Player.IsBuff(298)) Player.CancelBuff(298);
				if (Type == 21 && Player.IsBuff(330)) Player.CancelBuff(330);

				Player.CancelBuff(BuffNames::HaninStats1 + HaninNum);
			}
		}

		if (Item.CheckIndex() >= 3384 && Item.CheckIndex() <= 3386)
		{
			int MirrorIID = Player.GetBuffValue(BuffNames::MirrorBuff);
			if (MirrorIID) {
				int Itemy = Player.ItemPointer(MirrorIID);

				if (!Itemy)
					return 0;

				IItem Mirror((void*)Itemy);

				if (Mirror.CheckIndex() == 3381)
				{
					if (Player.GetBuffValue(BuffNames::Essence3) == Item.GetIID())
					{
						*(DWORD*)(*(DWORD*)((int)Itemx + 40) + 72) = -97;
						Player.UpdateBuff(BuffNames::Essence3, BuffNames::BuffTime, 0);
					}
					else if (Player.GetBuffValue(BuffNames::Essence2) == Item.GetIID()) {
						*(DWORD*)(*(DWORD*)((int)Itemx + 40) + 72) = -96;
						Player.UpdateBuff(BuffNames::Essence2, BuffNames::BuffTime, 0);
					}
					else if (Player.GetBuffValue(BuffNames::Essence1) == Item.GetIID()) {
						*(DWORD*)(*(DWORD*)((int)Itemx + 40) + 72) = -95;
						Player.UpdateBuff(BuffNames::Essence1, BuffNames::BuffTime, 0);
					}
				}

				if (Mirror.CheckIndex() == 3382)
				{
					if (Player.GetBuffValue(BuffNames::Essence4) == Item.GetIID())
					{
						*(DWORD*)(*(DWORD*)((int)Itemx + 40) + 72) = -98;
						Player.UpdateBuff(BuffNames::Essence4, BuffNames::BuffTime, 0);
					}
					else if (Player.GetBuffValue(BuffNames::Essence3) == Item.GetIID()) {
						*(DWORD*)(*(DWORD*)((int)Itemx + 40) + 72) = -97;
						Player.UpdateBuff(BuffNames::Essence3, BuffNames::BuffTime, 0);
					}
					else if (Player.GetBuffValue(BuffNames::Essence2) == Item.GetIID()) {
						*(DWORD*)(*(DWORD*)((int)Itemx + 40) + 72) = -96;
						Player.UpdateBuff(BuffNames::Essence2, BuffNames::BuffTime, 0);
					}
					else if (Player.GetBuffValue(BuffNames::Essence1) == Item.GetIID()) {
						*(DWORD*)(*(DWORD*)((int)Itemx + 40) + 72) = -95;
						Player.UpdateBuff(BuffNames::Essence1, BuffNames::BuffTime, 0);
					}
				}

				if (Mirror.CheckIndex() == 3383)
				{
					if (Player.GetBuffValue(BuffNames::Essence5) == Item.GetIID())
					{
						*(DWORD*)(*(DWORD*)((int)Itemx + 40) + 72) = -99;
						Player.UpdateBuff(BuffNames::Essence5, BuffNames::BuffTime, 0);
					}
					else if (Player.GetBuffValue(BuffNames::Essence4) == Item.GetIID()) {
						*(DWORD*)(*(DWORD*)((int)Itemx + 40) + 72) = -98;
						Player.UpdateBuff(BuffNames::Essence4, BuffNames::BuffTime, 0);
					}
					else if (Player.GetBuffValue(BuffNames::Essence3) == Item.GetIID()) {
						*(DWORD*)(*(DWORD*)((int)Itemx + 40) + 72) = -97;
						Player.UpdateBuff(BuffNames::Essence3, BuffNames::BuffTime, 0);
					}
					else if (Player.GetBuffValue(BuffNames::Essence2) == Item.GetIID()) {
						*(DWORD*)(*(DWORD*)((int)Itemx + 40) + 72) = -96;
						Player.UpdateBuff(BuffNames::Essence2, BuffNames::BuffTime, 0);
					}
					else if (Player.GetBuffValue(BuffNames::Essence1) == Item.GetIID()) {
						*(DWORD*)(*(DWORD*)((int)Itemx + 40) + 72) = -95;
						Player.UpdateBuff(BuffNames::Essence1, BuffNames::BuffTime, 0);
					}
				}
			}
		}

		if (Item.CheckIndex() >= 2986 && Item.CheckIndex() <= 3009 && Player.IsBuff(311))
			return 0;

		if (Item.CheckIndex() >= 3018 && Item.CheckIndex() <= 3020)
		{
			if (Player.IsBuff(311) && Player.GetBuffValue(BuffNames::Taegeuk))
			{
				Player.DecreaseMaxHp(TaegeukPrefix[(Player.GetBuffValue(BuffNames::Taegeuk) - 1)][0]);
				Player.DecreaseMaxMp(TaegeukPrefix[(Player.GetBuffValue(BuffNames::Taegeuk) - 1)][1]);
				Player.RemoveMaxAttack(TaegeukPrefix[(Player.GetBuffValue(BuffNames::Taegeuk) - 1)][2]);
				Player.RemoveMinAttack(TaegeukPrefix[(Player.GetBuffValue(BuffNames::Taegeuk) - 1)][2]);
				Player.RemoveStr(TaegeukPrefix[(Player.GetBuffValue(BuffNames::Taegeuk) - 1)][3]);
				Player.RemoveAgi(TaegeukPrefix[(Player.GetBuffValue(BuffNames::Taegeuk) - 1)][4]);
				Player.RemoveInt(TaegeukPrefix[(Player.GetBuffValue(BuffNames::Taegeuk) - 1)][5]);
				Player.RemoveWis(TaegeukPrefix[(Player.GetBuffValue(BuffNames::Taegeuk) - 1)][6]);
				Player.RemoveHp(TaegeukPrefix[(Player.GetBuffValue(BuffNames::Taegeuk) - 1)][7]);
			}
			Player.UpdateBuff(BuffNames::Taegeuk, BuffNames::BuffTime, 0);
		}

		if (Item.CheckIndex() >= 2946 && Item.CheckIndex() <= 2948)
		{
			int YinYangGrade = Player.GetBuffValue(BuffNames::TrigramGrade);
			if (YinYangGrade >= 0 && YinYangGrade <= 14) {
				int YinYangType = 0;
				if (Item.CheckIndex() == 2947) YinYangType = 1;
				if (Item.CheckIndex() == 2948) YinYangType = 2;
				Player.CancelBuff(311);
				Player.DecreaseMaxHp(Player.GetBuffValue(BuffNames::TrigramHP) + ((Player.GetBuffValue(BuffNames::TrigramHP) * YinYangRate[YinYangType][YinYangGrade]) / 100));
				Player.DecreaseMaxMp(Player.GetBuffValue(BuffNames::TrigramMP) + ((Player.GetBuffValue(BuffNames::TrigramMP) * YinYangRate[YinYangType][YinYangGrade]) / 100));
				Player.RemoveMaxAttack(Player.GetBuffValue(BuffNames::TrigramAtk) + ((Player.GetBuffValue(BuffNames::TrigramAtk) * YinYangRate[YinYangType][YinYangGrade]) / 100));
				Player.RemoveMinAttack(Player.GetBuffValue(BuffNames::TrigramAtk) + ((Player.GetBuffValue(BuffNames::TrigramAtk) * YinYangRate[YinYangType][YinYangGrade]) / 100));
				Player.RemoveStr(Player.GetBuffValue(BuffNames::TrigramStr) + ((Player.GetBuffValue(BuffNames::TrigramStr) * YinYangRate[YinYangType][YinYangGrade]) / 100));
				Player.RemoveAgi(Player.GetBuffValue(BuffNames::TrigramAgi) + ((Player.GetBuffValue(BuffNames::TrigramAgi) * YinYangRate[YinYangType][YinYangGrade]) / 100));
				Player.RemoveInt(Player.GetBuffValue(BuffNames::TrigramInt) + ((Player.GetBuffValue(BuffNames::TrigramInt) * YinYangRate[YinYangType][YinYangGrade]) / 100));
				Player.RemoveWis(Player.GetBuffValue(BuffNames::TrigramWis) + ((Player.GetBuffValue(BuffNames::TrigramWis) * YinYangRate[YinYangType][YinYangGrade]) / 100));
				Player.RemoveHp(Player.GetBuffValue(BuffNames::TrigramHth) + ((Player.GetBuffValue(BuffNames::TrigramHth) * YinYangRate[YinYangType][YinYangGrade]) / 100));

				if (Player.GetBuffValue(BuffNames::Taegeuk))
				{
					Player.DecreaseMaxHp(TaegeukPrefix[(Player.GetBuffValue(BuffNames::Taegeuk) - 1)][0]);
					Player.DecreaseMaxMp(TaegeukPrefix[(Player.GetBuffValue(BuffNames::Taegeuk) - 1)][1]);
					Player.RemoveMaxAttack(TaegeukPrefix[(Player.GetBuffValue(BuffNames::Taegeuk) - 1)][2]);
					Player.RemoveMinAttack(TaegeukPrefix[(Player.GetBuffValue(BuffNames::Taegeuk) - 1)][2]);
					Player.RemoveStr(TaegeukPrefix[(Player.GetBuffValue(BuffNames::Taegeuk) - 1)][3]);
					Player.RemoveAgi(TaegeukPrefix[(Player.GetBuffValue(BuffNames::Taegeuk) - 1)][4]);
					Player.RemoveInt(TaegeukPrefix[(Player.GetBuffValue(BuffNames::Taegeuk) - 1)][5]);
					Player.RemoveWis(TaegeukPrefix[(Player.GetBuffValue(BuffNames::Taegeuk) - 1)][6]);
					Player.RemoveHp(TaegeukPrefix[(Player.GetBuffValue(BuffNames::Taegeuk) - 1)][7]);
				}
			}
		}

		if (Item.CheckIndex() >= 2986 && Item.CheckIndex() <= 3009)
		{
			int GetCurrentGrade = TrigramGrade(Item.GetOffset());

			if (GetCurrentGrade) {
				if (Item.CheckIndex() == 2986) Player.UpdateBuff(BuffNames::TrigramHP, BuffNames::BuffTime, 0);
				else if (Item.CheckIndex() == 2994) Player.UpdateBuff(BuffNames::TrigramHP, BuffNames::BuffTime, 0);
				else if (Item.CheckIndex() == 3002) Player.UpdateBuff(BuffNames::TrigramHP, BuffNames::BuffTime, 0);
				else if (Item.CheckIndex() == 2987) Player.UpdateBuff(BuffNames::TrigramMP, BuffNames::BuffTime, 0);
				else if (Item.CheckIndex() == 2995) Player.UpdateBuff(BuffNames::TrigramMP, BuffNames::BuffTime, 0);
				else if (Item.CheckIndex() == 3003) Player.UpdateBuff(BuffNames::TrigramMP, BuffNames::BuffTime, 0);
				else if (Item.CheckIndex() == 2988) Player.UpdateBuff(BuffNames::TrigramAtk, BuffNames::BuffTime, 0);
				else if (Item.CheckIndex() == 2996) Player.UpdateBuff(BuffNames::TrigramAtk, BuffNames::BuffTime, 0);
				else if (Item.CheckIndex() == 3004) Player.UpdateBuff(BuffNames::TrigramAtk, BuffNames::BuffTime, 0);
				else if (Item.CheckIndex() == 2989) Player.UpdateBuff(BuffNames::TrigramStr, BuffNames::BuffTime, 0);
				else if (Item.CheckIndex() == 2997) Player.UpdateBuff(BuffNames::TrigramStr, BuffNames::BuffTime, 0);
				else if (Item.CheckIndex() == 3005) Player.UpdateBuff(BuffNames::TrigramStr, BuffNames::BuffTime, 0);
				else if (Item.CheckIndex() == 2990) Player.UpdateBuff(BuffNames::TrigramAgi, BuffNames::BuffTime, 0);
				else if (Item.CheckIndex() == 2998) Player.UpdateBuff(BuffNames::TrigramAgi, BuffNames::BuffTime, 0);
				else if (Item.CheckIndex() == 3006) Player.UpdateBuff(BuffNames::TrigramAgi, BuffNames::BuffTime, 0);
				else if (Item.CheckIndex() == 2991) Player.UpdateBuff(BuffNames::TrigramInt, BuffNames::BuffTime, 0);
				else if (Item.CheckIndex() == 2999) Player.UpdateBuff(BuffNames::TrigramInt, BuffNames::BuffTime, 0);
				else if (Item.CheckIndex() == 3007) Player.UpdateBuff(BuffNames::TrigramInt, BuffNames::BuffTime, 0);
				else if (Item.CheckIndex() == 2992) Player.UpdateBuff(BuffNames::TrigramWis, BuffNames::BuffTime, 0);
				else if (Item.CheckIndex() == 3000) Player.UpdateBuff(BuffNames::TrigramWis, BuffNames::BuffTime, 0);
				else if (Item.CheckIndex() == 3008) Player.UpdateBuff(BuffNames::TrigramWis, BuffNames::BuffTime, 0);
				else if (Item.CheckIndex() == 2993) Player.UpdateBuff(BuffNames::TrigramHth, BuffNames::BuffTime, 0);
				else if (Item.CheckIndex() == 3001) Player.UpdateBuff(BuffNames::TrigramHth, BuffNames::BuffTime, 0);
				else if (Item.CheckIndex() == 3009) Player.UpdateBuff(BuffNames::TrigramHth, BuffNames::BuffTime, 0);
			}
		}

		if (isPet(Item.CheckIndex()))
		{
			N = Player.numberOfPets();

			int Type = 0;
			int IIDType = 0;
			int MonsterPet = 0;

			if (Item.GetIID() == Player.GetBuffValue(BuffNames::PetIID)) {
				Type = BuffNames::PetOwner;
				IIDType = BuffNames::PetIID;
			}
			else
				if (Item.GetIID() == Player.GetBuffValue(BuffNames::PetIID2)) {
					Type = BuffNames::PetOwner2;
					IIDType = BuffNames::PetIID2;
				}
				else
					if (Item.GetIID() == Player.GetBuffValue(BuffNames::PetIID3)) {
						Type = BuffNames::PetOwner3;
						IIDType = BuffNames::PetIID3;
					}
			if (Type && IIDType) {
				int Index = Player.GetBuffValue(Type);
				int Monster = Player.GetMobPet();
				if (Monster) {
					IChar IMonster((void*)Monster);
					if (IMonster.IsValid() && IMonster.GetMobIndex() == PetTime.find(Index)->second.Monster) {
						*(DWORD *)((int)Monster + 472) = 0;
						Player.SetMobPet(0);
						IMonster.Blob();
					}
				}

				Player.UpdateBuff(IIDType, BuffNames::BuffTime, 0);
				Player.UpdateBuff(Type, BuffNames::BuffTime, 0);
				int Picks = PetTime.count(Item.CheckIndex()) ? PetTime.find(Item.CheckIndex())->second.Pick : 0;
				if (Picks == 1) {
					int Pick = Player.GetBuffValue(BuffNames::PetPick);
					if (Pick > 0) {
						int Range = Player.GetPickRange();

						if (PetTime.find(Item.CheckIndex())->second.Range == Range) {
							int Value = 0;
							if (Player.numberOfPets()) {
								int Pet1 = Player.GetBuffValue(BuffNames::PetOwner);
								int Pet2 = Player.GetBuffValue(BuffNames::PetOwner2);
								int Pet3 = Player.GetBuffValue(BuffNames::PetOwner3);
								int Range1 = (Pet1 && PetTime.count(Pet1) && PetTime.find(Pet1)->second.Pick == 1) ? PetTime.find(Pet1)->second.Range : 0;
								int Range2 = (Pet2 && PetTime.count(Pet2) && PetTime.find(Pet2)->second.Pick == 1) ? PetTime.find(Pet2)->second.Range : 0;
								int Range3 = (Pet3 && PetTime.count(Pet3) && PetTime.find(Pet3)->second.Pick == 1) ? PetTime.find(Pet3)->second.Range : 0;
								Value = maxRange(Range1, Range2, Range3);
							}

							Player.SetPickRange(Value);
						}
						Player.UpdateBuff(BuffNames::PetPick, BuffNames::BuffTime, Pick - 1);

						CPlayer::Write(Player.GetOffset(), 0xFF, "dd", 221, -1);
					}
				}
			}
		}
	}

	int Check = CItemOrnament::PutOff(Itemx, Playerx);

	if (Player.IsOnline() && isPet(Item.CheckIndex()) && N > 1)
		CPlayer::AddWState(Playerx, Item.GetType());

	return Check;

}
int __fastcall ItemOnTimer(int Item, void *edx, int Argument)
{
	IItem IItem((void*)Item);

	if (IItem.Exists() && !Argument)
	{
		int IID = IItem.GetIID();
		int Index = IItem.CheckIndex();

		if (PetLifeCheck.count(IID)) {
			TargetFind myTarget(0, 1, *(DWORD *)(Item + 32));
			int Player = (int)myTarget.getTarget();

			IChar IPlayer((void*)Player);

			if (IPlayer.IsOnline()) {
				int Time = PetLifeCheck.findValue(IID);
				int LeftTime = Time - (int)time(0);

				if (LeftTime <= 43200 && (!(LeftTime % 3600) || (LeftTime < 3600 && !(LeftTime % 60))) && RentalItems.count(Index))
					CPlayer::Write(IPlayer.GetOffset(), 0xFE, "dbdd", 202, 5, IID, LeftTime);

				if (LeftTime <= 0 && IPlayer.ItemPointerLock(IID) == Item)
				{
					*(DWORD*)(Item + 68) = 0;

					if (CItem::IsState(Item, 1))
						IPlayer.PutOffItem(IID);

					if (RentalItems.count(Index)) {
						PetLifeCheck.replaceInsert(IID, 0);
						CPlayer::Write(IPlayer.GetOffset(), 0xFE, "ddd", 201, IID, 1);
					}
					else {
						PetLifeCheck.erase(IID);
						IPlayer.RemoveItemLock(Item);
						IPlayer.BoxMsg("Your item is vanished since the usage period has been expired.");
					}

					return 0;
				}
			}
		}
	}

	return CItem::OnTimer(Item, Argument);
}

bool isOrnamentCheck(int Index) {
	return ((Index >= 3384 && Index <= 3386) || isPet(Index) || (Index >= 2986 && Index <= 3009) || (Index >= 3199 && Index <= 3204) || (Index >= 3381 && Index <= 3383) || (Index >= 2946 && Index <= 2948) || (Index >= 3018 && Index <= 3020));
}

int __cdecl NewItem(int Value)
{
	int Index = *(DWORD *)(Value + 64);

	if (isItemSuit(Index))
		*(DWORD *)(Value + 72) = 6;
	else
		if (isItemCostumeEffect(Index))
			*(DWORD *)(Value + 72) = 5;

	else if (*(DWORD *)(Value + 68) == -1)
	{
		if (isItemRiding(Index)) {
			*(DWORD *)(Value + 68) = 1;
			*(DWORD *)(Value + 72) = 22;
		}

		else if(isOrnamentCheck(Index)){
			void *Check = 0, *GetPointer = 0;

			Check = (void*)Undefined::GetMonsterValue(0x5Cu);

			if ((int)Check)
				GetPointer = CItemOrnament::CItemOrnament(Check, Value);
			else
				GetPointer = 0;

			if ((int)GetPointer)
			{
				IItem xItem(GetPointer);

				if (Index >= 3384 && Index <= 3386)
				{
					//*(DWORD*)((int)GetPointer + 48) = 128;
					*(DWORD*)(*(DWORD*)((int)GetPointer + 40) + 72) = -95;
					return (int)GetPointer;
				}

				if (isPet(Index))
				{
					*(DWORD*)(*(DWORD*)((int)GetPointer + 40) + 72) = -100;
					if(PetBound)
						*(DWORD*)((int)GetPointer + 48) = 128;
					return (int)GetPointer;
				}

				if (xItem.CheckIndex() == 2986 || xItem.CheckIndex() == 2994 || xItem.CheckIndex() == 3002)
				{
					*(DWORD*)(*(DWORD*)((int)GetPointer + 40) + 72) = -101;
					return (int)GetPointer;
				}

				if (xItem.CheckIndex() == 2987 || xItem.CheckIndex() == 2995 || xItem.CheckIndex() == 3003)
				{
					*(DWORD*)(*(DWORD*)((int)GetPointer + 40) + 72) = -102;
					return (int)GetPointer;
				}

				if (xItem.CheckIndex() == 2988 || xItem.CheckIndex() == 2996 || xItem.CheckIndex() == 3004)
				{
					*(DWORD*)(*(DWORD*)((int)GetPointer + 40) + 72) = -103;
					return (int)GetPointer;
				}

				if (xItem.CheckIndex() == 2989 || xItem.CheckIndex() == 2997 || xItem.CheckIndex() == 3005)
				{
					*(DWORD*)(*(DWORD*)((int)GetPointer + 40) + 72) = -104;
					return (int)GetPointer;
				}

				if (xItem.CheckIndex() == 2990 || xItem.CheckIndex() == 2998 || xItem.CheckIndex() == 3006)
				{
					*(DWORD*)(*(DWORD*)((int)GetPointer + 40) + 72) = -105;
					return (int)GetPointer;
				}

				if (xItem.CheckIndex() == 2991 || xItem.CheckIndex() == 2999 || xItem.CheckIndex() == 3007)
				{
					*(DWORD*)(*(DWORD*)((int)GetPointer + 40) + 72) = -106;
					return (int)GetPointer;
				}

				if (xItem.CheckIndex() == 2992 || xItem.CheckIndex() == 3000 || xItem.CheckIndex() == 3008)
				{
					*(DWORD*)(*(DWORD*)((int)GetPointer + 40) + 72) = -107;
					return (int)GetPointer;
				}

				if (xItem.CheckIndex() == 2993 || xItem.CheckIndex() == 3001 || xItem.CheckIndex() == 3009)
				{
					*(DWORD*)(*(DWORD*)((int)GetPointer + 40) + 72) = -108;
					return (int)GetPointer;
				}

				if (xItem.CheckIndex() >= 3199 && xItem.CheckIndex() <= 3204)
				{
					*(DWORD*)(*(DWORD*)((int)GetPointer + 40) + 72) = -109;
					return (int)GetPointer;
				}

				if (xItem.CheckIndex() >= 3381 && xItem.CheckIndex() <= 3383)
				{
					//*(DWORD*)((int)GetPointer + 48) = 128;
					*(DWORD*)(*(DWORD*)((int)GetPointer + 40) + 72) = -110;
					return (int)GetPointer;
				}

				if (xItem.CheckIndex() >= 2946 && xItem.CheckIndex() <= 2948)
				{
					*(DWORD*)(*(DWORD*)((int)GetPointer + 40) + 72) = -111;
					return (int)GetPointer;
				}

				if (xItem.CheckIndex() >= 3018 && xItem.CheckIndex() <= 3020)
				{
					*(DWORD*)(*(DWORD*)((int)GetPointer + 40) + 72) = -112;
					return (int)GetPointer;
				}

			}
		}
	}
	return CItem::NewItem(Value);
}

int __cdecl MyCreateItem(int Index, int Prefix, int Amount, int Argument)
{
	int result = 0, Item = 0, FindItem = 0;

	if (Amount > 0)
	{
		FindItem = CItem::FindInitItem(Index);

		if (FindItem)
		{
			Item = NewItem(FindItem);

			if (Item)
			{
				if (TimedItemBound && (TimedItems.count(Index) || RentalItems.count(Index)))
					*(DWORD*)(Item + 48) = 128;

				if (Prefix >= 256)
				{
					*(DWORD*)(Item + 48) = 128;
					Prefix -= 256;
				}

				(*(void (__thiscall **)(void *, int, int, int))(*(DWORD*)Item + 76))((void*)Item, Prefix, Amount, Argument);
			}
		}
		result = Item;
	}

	return result;
}
int __fastcall InsertItem(void *Player, void *edx, int Argument, int Itemx)
{
	IItem Item((void*)Itemx);

	if (!Item.Exists())
		return 0;

	return CPlayer::_InsertItem(Player,Argument,Itemx);
}

int __fastcall OrnamentPutOn(int Itemx, void *edx, int Playerx)
{
	IItem Item((void*)Itemx);
	IChar Player((void*)Playerx);
	int GetPetTime = 259200;
	if (Player.IsOnline() && Item.Exists())
	{
		if (isNormalPet(Item.CheckIndex()) && Player.GetBuffValue(BuffNames::PetIID)) {
			Player.SystemMessage("Please un-wear your current pet.", TEXTCOLOR_RED);
			return 0;
		}

		if (isMonsterPet(Item.CheckIndex()) && Player.GetBuffValue(BuffNames::PetIID2)) {
			Player.SystemMessage("Please un-wear your current monster pet.", TEXTCOLOR_RED);
			return 0;
		}

		if (isPremiumPet(Item.CheckIndex()) && Player.GetBuffValue(BuffNames::PetIID3)) {
			Player.SystemMessage("Please un-wear your current premium pet.", TEXTCOLOR_RED);
			return 0;
		}

		if (Item.CheckIndex() >= 3384 && Item.CheckIndex() <= 3386 && !CPlayer::IsWState(Playerx, -112))
			return 0;

		if (Item.CheckIndex() >= 3381 && Item.CheckIndex() <= 3383)
		{
			if (Player.GetBuffValue(BuffNames::MirrorBuff))
				return 0;
			else
				Player.UpdateBuff(BuffNames::MirrorBuff, BuffNames::BuffTime, Item.GetIID());
		}

		if (Item.CheckIndex() >= 3384 && Item.CheckIndex() <= 3386)
		{
			if (!Player.GetBuffValue(BuffNames::MirrorBuff))
				return 0;

			int IIDMirror = Player.GetBuffValue(BuffNames::MirrorBuff);

			int Itemy = Player.ItemPointer(IIDMirror);

			if (!Itemy)
				return 0;

			IItem Mirror((void*)Itemy);

			if (isEssensed(Player, Item.GetIID()))
				return 0;

			itemStat.Enter();
			int Counted = GetItemStat.count(Item.GetIID()) ? 1 : 0;
			itemStat.Leave();

			if (!Counted)
				return 0;

			int SlotSize = 0, TotalSlotSize = 0;
			itemStat.Enter();
			SlotSize = (GetItemStat.count(Mirror.GetIID()) ? GetItemStat.find(Mirror.GetIID())->second : 0) + 1;
			itemStat.Leave();

			if (SlotSize == 1 && Mirror.CheckIndex() == 3383) SlotSize = 2;
			if (Player.GetBuffValue(BuffNames::Essence1)) TotalSlotSize += 1;
			if (Player.GetBuffValue(BuffNames::Essence2)) TotalSlotSize += 1;
			if (Player.GetBuffValue(BuffNames::Essence3)) TotalSlotSize += 1;
			if (Player.GetBuffValue(BuffNames::Essence4)) TotalSlotSize += 1;
			if (Player.GetBuffValue(BuffNames::Essence5)) TotalSlotSize += 1;
			if (TotalSlotSize >= SlotSize) {
				return 0;
			}

			itemStat.Enter();
			int Valuex = GetItemStat.find(Item.GetIID())->second;
			itemStat.Leave();

			if (!Valuex)
				return 0;

			int Type = Valuex % 100;

			if (HaninEquipped(Player, Type)) {
				Player.SystemMessage("You are already wearing this kind of hanin mirror.", TEXTCOLOR_RED);
				return 0;
			}

			if (Mirror.CheckIndex() == 3381)
			{
				if (!Player.GetBuffValue(BuffNames::Essence1))
				{
					*(DWORD*)(*(DWORD*)(Itemx + 40) + 72) = -95;
					Player.UpdateBuff(BuffNames::Essence1, BuffNames::BuffTime, Item.GetIID());
				}
				else if (!Player.GetBuffValue(BuffNames::Essence2)) {
					*(DWORD*)(*(DWORD*)(Itemx + 40) + 72) = -96;
					Player.UpdateBuff(BuffNames::Essence2, BuffNames::BuffTime, Item.GetIID());
				}
				else if (!Player.GetBuffValue(BuffNames::Essence3)) {
					*(DWORD*)(*(DWORD*)(Itemx + 40) + 72) = -97;
					Player.UpdateBuff(BuffNames::Essence3, BuffNames::BuffTime, Item.GetIID());
				}
			}

			if (Mirror.CheckIndex() == 3382)
			{
				if (!Player.GetBuffValue(BuffNames::Essence1))
				{
					*(DWORD*)(*(DWORD*)(Itemx + 40) + 72) = -95;
					Player.UpdateBuff(BuffNames::Essence1, BuffNames::BuffTime, Item.GetIID());
				}
				else if (!Player.GetBuffValue(BuffNames::Essence2)) {
					*(DWORD*)(*(DWORD*)(Itemx + 40) + 72) = -96;
					Player.UpdateBuff(BuffNames::Essence2, BuffNames::BuffTime, Item.GetIID());
				}
				else if (!Player.GetBuffValue(BuffNames::Essence3)) {
					*(DWORD*)(*(DWORD*)(Itemx + 40) + 72) = -97;
					Player.UpdateBuff(BuffNames::Essence3, BuffNames::BuffTime, Item.GetIID());
				}
				else if (!Player.GetBuffValue(BuffNames::Essence4)) {
					*(DWORD*)(*(DWORD*)(Itemx + 40) + 72) = -98;
					Player.UpdateBuff(BuffNames::Essence4, BuffNames::BuffTime, Item.GetIID());
				}
			}

			if (Mirror.CheckIndex() == 3383)
			{
				if (!Player.GetBuffValue(BuffNames::Essence1))
				{
					*(DWORD*)(*(DWORD*)(Itemx + 40) + 72) = -95;
					Player.UpdateBuff(BuffNames::Essence1, BuffNames::BuffTime, Item.GetIID());
				}
				else if (!Player.GetBuffValue(BuffNames::Essence2)) {
					*(DWORD*)(*(DWORD*)(Itemx + 40) + 72) = -96;
					Player.UpdateBuff(BuffNames::Essence2, BuffNames::BuffTime, Item.GetIID());
				}
				else if (!Player.GetBuffValue(BuffNames::Essence3)) {
					*(DWORD*)(*(DWORD*)(Itemx + 40) + 72) = -97;
					Player.UpdateBuff(BuffNames::Essence3, BuffNames::BuffTime, Item.GetIID());
				}
				else if (!Player.GetBuffValue(BuffNames::Essence4)) {
					*(DWORD*)(*(DWORD*)(Itemx + 40) + 72) = -98;
					Player.UpdateBuff(BuffNames::Essence4, BuffNames::BuffTime, Item.GetIID());
				}
				else if (!Player.GetBuffValue(BuffNames::Essence5)) {
					*(DWORD*)(*(DWORD*)(Itemx + 40) + 72) = -99;
					Player.UpdateBuff(BuffNames::Essence5, BuffNames::BuffTime, Item.GetIID());
				}
			}
		}

		if (isPet(Item.CheckIndex()))
		{
			if (CSMap::IsOnTile(*(void **)((int)Player.Offset + 320), (int)Player.Offset + 332, 1048576)) {
				Player.SystemMessage("You can not wear pets in war zone.", TEXTCOLOR_RED);
				return 0;
			}

			if (!PetLifeCheck.count(Item.GetIID()))
			{
				if (!(PetTime.count(Item.CheckIndex()) && !PetTime.find(Item.CheckIndex())->second.Time)) {
					if (PetTime.count(Item.CheckIndex()) && PetTime.find(Item.CheckIndex())->second.Time > 0)
						GetPetTime = PetTime.find(Item.CheckIndex())->second.Time;

					PetLifeCheck.replaceInsert(Item.GetIID(), (int)time(0) + GetPetTime);
					CDBSocket::Write(89, "ddd", Player.GetPID(), (int)time(0) + GetPetTime, Item.GetIID());
					CPlayer::Write(Player.GetOffset(), 0xFF, "ddd", 230, Item.GetIID(), GetPetTime);
					*(DWORD*)(Itemx + 68) = GetTickCount() + (2000 * GetPetTime);
					*(DWORD*)(Itemx + 72) = 0;
					CItem::OnTimer(Itemx, 0);
				}
			}
		}

		return CItemOrnament::PutOn(Itemx, Playerx);
	}
	else {
		return 0;
	}
}

int __fastcall OrnamentApplySpec(void *Itemx, void *edx, int Playerx)
{
	IItem Item(Itemx);
	IChar Player((void*)Playerx);

	if (Player.IsOnline() && Item.Exists())
	{
		if (isPet(Item.CheckIndex()))
			insertPet(Player, Item);

		if (BeltBuffs.count(Item.CheckIndex()))
			Player.Buff(BuffNames::Belt, BuffNames::BuffTime, Item.CheckIndex());
		
		if (NecklaceBuffs.count(Item.CheckIndex()))
			Player.Buff(BuffNames::Necklace, BuffNames::BuffTime, Item.CheckIndex());

		if (isSoulPocket(Item.CheckIndex())) {
			Player.UpdateBuff(BuffNames::SoulPocketIID, BuffNames::BuffTime, Item.GetIID());
			Player.UpdateBuff(BuffNames::SoulPIndex, BuffNames::BuffTime, Item.CheckIndex());

			itemStat.Enter();
			int Counted = GetItemStat.count(Item.GetIID()) ? 1 : 0;
			itemStat.Leave();

			if (Counted) {
				itemStat.Enter();
				int itemstat = GetItemStat.find(Item.GetIID())->second;
				itemStat.Leave();

				Player.UpdateBuff(BuffNames::SoulPocketAmount, BuffNames::BuffTime, itemstat);
			}
		}

		if (Item.CheckIndex() >= 3381 && Item.CheckIndex() <= 3383 && !Player.GetBuffValue(BuffNames::MirrorBuff))
			Player.UpdateBuff(BuffNames::MirrorBuff, BuffNames::BuffTime, Item.GetIID());

		if (Item.CheckIndex() >= 3384 && Item.CheckIndex() <= 3386)
		{
			if (!(Player.GetBuffValue(BuffNames::MirrorBuff) && isEssensed(Player, Item.GetIID())))
				return 0;

			int MirrorIID = Player.GetBuffValue(BuffNames::MirrorBuff);

			int Itemy = Player.ItemPointer(MirrorIID);

			if (!Itemy)
				return 0;

			IItem Mirror((void*)Itemy);
			int Valuex = 0, Type = 0;
			double Stat = 0.0;

			itemStat.Enter();
			Valuex = GetItemStat.count(Item.GetIID()) ? GetItemStat.find(Item.GetIID())->second : 0;
			itemStat.Leave();

			if (!Valuex)
				return 0;

			Type = Valuex % 100;

			Stat = Valuex / 10000;

			int Str = Player.GetStr(), Wis = Player.GetWis(), Hth = Player.GetHth(), Int = Player.GetInt(), Agi = Player.GetAgi();
			int Otp = Player.GetOTP(), MinPAtk = Player.GetMinPhyAttack(), MaxPAtk = Player.GetMaxPhyAttack(), Eva = Player.GetEva(), HpPoint = Player.GetMaxHp();
			int MpPoint = Player.GetMaxMp(), MinMAtk = Player.GetMinMagAttack(), MaxMAtk = Player.GetMaxMagAttack(), Def = Player.GetDef();

			if (!Stat)
				return 0;

			int HaninNum = getHaninEquip(Player, Item.GetIID());
			int Buff = 0;

			int value = 0;
			if (HaninNum != -1) {
				Buff = BuffNames::HaninStats1 + HaninNum;
				switch (Type) {
				case 0: value = Str;
					break;
				case 1: value = Wis;
					break;
				case 2: value = Int;
					break;
				case 3: value = Hth;
					break;
				case 4: value = Agi;
					break;
				case 5: value = Otp;
					break;
				case 6: value = Eva;
					break;
				case 7: value = Def;
					break;
				case 10: value = HpPoint;
					break;
				case 11: value = MpPoint;
					break;
				case 13: value = MinPAtk;
					break;
				case 14: value = MaxPAtk;
					break;
				case 18: value = MinMAtk;
					break;
				case 19: value = MaxMAtk;
					break;
				}

				double extra = 1;
				if (Mirror.CheckIndex() == 3382)
					extra = 1.1;
				else if (Mirror.CheckIndex() == 3383)
					extra = 1.2;

				value = ceil(((value*Stat) / 100) * extra);
				Player.UpdateBuff(Buff, BuffNames::BuffTime, value);

				if (Type == 0 && Str) Player.AddStr(value);
				if (Type == 1 && Wis) Player.AddWis(value);
				if (Type == 2 && Int) Player.AddInt(value);
				if (Type == 3 && Hth) Player.AddHp(value);
				if (Type == 4 && Agi) Player.AddAgi(value);
				if (Type == 5 && Otp) Player.AddOTP(value);
				if (Type == 6 && Eva) Player.AddEva(value);
				if (Type == 7 && Def) Player.AddDef(value);
				if (Type == 8) Player.IncreaseResist((Stat / 3) + 1);
				if (Type == 9) Player.AddAbsorb(Stat);
				if (Type == 10 && HpPoint) Player.IncreaseMaxHp(value);
				if (Type == 11 && MpPoint) Player.IncreaseMaxMp(value);
				if (Type == 12) Player.IncreaseMovingSpeed(Stat);
				if (Type == 13 && MinPAtk) Player.AddMinAttack(value);
				if (Type == 14 && MaxPAtk) Player.AddMinAttack(value);
				if (Type == 15) Player.IncreaseCritRate((Stat / 3) + 1);
				if (Type == 16) Player.IncreaseCritDamage((Stat / 2) + 1);
				if (Type == 17) Player.AddDeathBlow((Stat / 3) + 1);
				if (Type == 18 && MinMAtk) Player.AddMaxAttack(value);
				if (Type == 19 && MaxMAtk) Player.AddMaxAttack(value);
				if (Type == 20 && !Player.IsBuff(298)) Player.UpdateBuff(298, BuffNames::BuffTime, 0);
				if (Type == 21 && !Player.IsBuff(330)) Player.UpdateBuff(330, BuffNames::BuffTime, 0);
			}
		}

		if (Item.CheckIndex() >= 3018 && Item.CheckIndex() <= 3020 && !Player.GetBuffValue(BuffNames::Taegeuk))
		{
			itemStat.Enter();
			int Stats = GetItemStat.count(Item.GetIID()) ? GetItemStat.find(Item.GetIID())->second : 0;
			itemStat.Leave();
			
			if (Stats > 0) {
				int GetTaegeukPrefix = Stats / 1000;

				if (GetTaegeukPrefix) Player.UpdateBuff(BuffNames::Taegeuk, BuffNames::BuffTime, GetTaegeukPrefix);
				int TaegeukB = Player.GetBuffValue(BuffNames::Taegeuk);
				if (Player.IsBuff(311) && TaegeukB)
				{
					Player.IncreaseMaxHp(TaegeukPrefix[(TaegeukB - 1)][0]);
					Player.IncreaseMaxMp(TaegeukPrefix[(TaegeukB - 1)][1]);
					Player.AddMaxAttack(TaegeukPrefix[(TaegeukB - 1)][2]);
					Player.AddMinAttack(TaegeukPrefix[(TaegeukB - 1)][2]);
					Player.AddStr(TaegeukPrefix[(TaegeukB - 1)][3]);
					Player.AddAgi(TaegeukPrefix[(TaegeukB - 1)][4]);
					Player.AddInt(TaegeukPrefix[(TaegeukB - 1)][5]);
					Player.AddWis(TaegeukPrefix[(TaegeukB - 1)][6]);
					Player.AddHp(TaegeukPrefix[(TaegeukB - 1)][7]);
				}
			}
		}

		if (Item.CheckIndex() >= 2946 && Item.CheckIndex() <= 2948 && Player.GetBuffValue(BuffNames::TrigramHP) > 0
			&& Player.GetBuffValue(BuffNames::TrigramMP) > 0 && Player.GetBuffValue(BuffNames::TrigramAtk) > 0
			&& Player.GetBuffValue(BuffNames::TrigramStr) > 0 && Player.GetBuffValue(BuffNames::TrigramAgi) > 0
			&& Player.GetBuffValue(BuffNames::TrigramInt) > 0 && Player.GetBuffValue(BuffNames::TrigramWis) > 0
			&& Player.GetBuffValue(BuffNames::TrigramHth) > 0)
		{
			int YinYangType = 0;
			if (Item.CheckIndex() == 2947) YinYangType = 1;
			if (Item.CheckIndex() == 2948) YinYangType = 2;
			Player.UpdateBuff(311, 604800, 0);
			int YinYangGrade = Player.GetBuffValue(BuffNames::TrigramGrade);
			Player.IncreaseMaxHp(Player.GetBuffValue(BuffNames::TrigramHP) + ((Player.GetBuffValue(BuffNames::TrigramHP) * YinYangRate[YinYangType][YinYangGrade]) / 100));
			Player.IncreaseMaxMp(Player.GetBuffValue(BuffNames::TrigramMP) + ((Player.GetBuffValue(BuffNames::TrigramMP) * YinYangRate[YinYangType][YinYangGrade]) / 100));
			Player.AddMaxAttack(Player.GetBuffValue(BuffNames::TrigramAtk) + ((Player.GetBuffValue(BuffNames::TrigramAtk) * YinYangRate[YinYangType][YinYangGrade]) / 100));
			Player.AddMinAttack(Player.GetBuffValue(BuffNames::TrigramAtk) + ((Player.GetBuffValue(BuffNames::TrigramAtk) * YinYangRate[YinYangType][YinYangGrade]) / 100));
			Player.AddStr(Player.GetBuffValue(BuffNames::TrigramStr) + ((Player.GetBuffValue(BuffNames::TrigramStr) * YinYangRate[YinYangType][YinYangGrade]) / 100));
			Player.AddAgi(Player.GetBuffValue(BuffNames::TrigramAgi) + ((Player.GetBuffValue(BuffNames::TrigramAgi) * YinYangRate[YinYangType][YinYangGrade]) / 100));
			Player.AddInt(Player.GetBuffValue(BuffNames::TrigramInt) + ((Player.GetBuffValue(BuffNames::TrigramInt) * YinYangRate[YinYangType][YinYangGrade]) / 100));
			Player.AddWis(Player.GetBuffValue(BuffNames::TrigramWis) + ((Player.GetBuffValue(BuffNames::TrigramWis) * YinYangRate[YinYangType][YinYangGrade]) / 100));
			Player.AddHp(Player.GetBuffValue(BuffNames::TrigramHth) + ((Player.GetBuffValue(BuffNames::TrigramHth) * YinYangRate[YinYangType][YinYangGrade]) / 100));
			int TaegeukB = Player.GetBuffValue(BuffNames::Taegeuk);

			if (TaegeukB)
			{
				Player.IncreaseMaxHp(TaegeukPrefix[(TaegeukB - 1)][0]);
				Player.IncreaseMaxMp(TaegeukPrefix[(TaegeukB - 1)][1]);
				Player.AddMaxAttack(TaegeukPrefix[(TaegeukB - 1)][2]);
				Player.AddMinAttack(TaegeukPrefix[(TaegeukB - 1)][2]);
				Player.AddStr(TaegeukPrefix[(TaegeukB - 1)][3]);
				Player.AddAgi(TaegeukPrefix[(TaegeukB - 1)][4]);
				Player.AddInt(TaegeukPrefix[(TaegeukB - 1)][5]);
				Player.AddWis(TaegeukPrefix[(TaegeukB - 1)][6]);
				Player.AddHp(TaegeukPrefix[(TaegeukB - 1)][7]);
			}
		}

		if (Item.CheckIndex() >= 2986 && Item.CheckIndex() <= 3009)
		{
			int GetCurrentGrade = TrigramGrade(Item.GetOffset());

			if (GetCurrentGrade) {
				int TriGrade = Player.GetBuffValue(BuffNames::TrigramGrade);

				if (!TriGrade || GetCurrentGrade < TriGrade)
					Player.UpdateBuff(BuffNames::TrigramGrade, BuffNames::BuffTime, GetCurrentGrade);

				if (Item.CheckIndex() == 2986) Player.UpdateBuff(BuffNames::TrigramHP, BuffNames::BuffTime, TriagramStats[0][GetCurrentGrade]);
				else if (Item.CheckIndex() == 2994) Player.UpdateBuff(BuffNames::TrigramHP, BuffNames::BuffTime, TriagramStats[1][GetCurrentGrade]);
				else if (Item.CheckIndex() == 3002) Player.UpdateBuff(BuffNames::TrigramHP, BuffNames::BuffTime, TriagramStats[2][GetCurrentGrade]);
				else if (Item.CheckIndex() == 2987) Player.UpdateBuff(BuffNames::TrigramMP, BuffNames::BuffTime, TriagramStats[3][GetCurrentGrade]);
				else if (Item.CheckIndex() == 2995) Player.UpdateBuff(BuffNames::TrigramMP, BuffNames::BuffTime, TriagramStats[4][GetCurrentGrade]);
				else if (Item.CheckIndex() == 3003) Player.UpdateBuff(BuffNames::TrigramMP, BuffNames::BuffTime, TriagramStats[5][GetCurrentGrade]);
				else if (Item.CheckIndex() == 2988) Player.UpdateBuff(BuffNames::TrigramAtk, BuffNames::BuffTime, TriagramStats[6][GetCurrentGrade]);
				else if (Item.CheckIndex() == 2996) Player.UpdateBuff(BuffNames::TrigramAtk, BuffNames::BuffTime, TriagramStats[7][GetCurrentGrade]);
				else if (Item.CheckIndex() == 3004) Player.UpdateBuff(BuffNames::TrigramAtk, BuffNames::BuffTime, TriagramStats[8][GetCurrentGrade]);
				else if (Item.CheckIndex() == 2989) Player.UpdateBuff(BuffNames::TrigramStr, BuffNames::BuffTime, TriagramStats[9][GetCurrentGrade]);
				else if (Item.CheckIndex() == 2997) Player.UpdateBuff(BuffNames::TrigramStr, BuffNames::BuffTime, TriagramStats[10][GetCurrentGrade]);
				else if (Item.CheckIndex() == 3005) Player.UpdateBuff(BuffNames::TrigramStr, BuffNames::BuffTime, TriagramStats[11][GetCurrentGrade]);
				else if (Item.CheckIndex() == 2990) Player.UpdateBuff(BuffNames::TrigramAgi, BuffNames::BuffTime, TriagramStats[12][GetCurrentGrade]);
				else if (Item.CheckIndex() == 2998) Player.UpdateBuff(BuffNames::TrigramAgi, BuffNames::BuffTime, TriagramStats[13][GetCurrentGrade]);
				else if (Item.CheckIndex() == 3006) Player.UpdateBuff(BuffNames::TrigramAgi, BuffNames::BuffTime, TriagramStats[14][GetCurrentGrade]);
				else if (Item.CheckIndex() == 2991) Player.UpdateBuff(BuffNames::TrigramInt, BuffNames::BuffTime, TriagramStats[15][GetCurrentGrade]);
				else if (Item.CheckIndex() == 2999) Player.UpdateBuff(BuffNames::TrigramInt, BuffNames::BuffTime, TriagramStats[16][GetCurrentGrade]);
				else if (Item.CheckIndex() == 3007) Player.UpdateBuff(BuffNames::TrigramInt, BuffNames::BuffTime, TriagramStats[17][GetCurrentGrade]);
				else if (Item.CheckIndex() == 2992) Player.UpdateBuff(BuffNames::TrigramWis, BuffNames::BuffTime, TriagramStats[18][GetCurrentGrade]);
				else if (Item.CheckIndex() == 3000) Player.UpdateBuff(BuffNames::TrigramWis, BuffNames::BuffTime, TriagramStats[19][GetCurrentGrade]);
				else if (Item.CheckIndex() == 3008) Player.UpdateBuff(BuffNames::TrigramWis, BuffNames::BuffTime, TriagramStats[20][GetCurrentGrade]);
				else if (Item.CheckIndex() == 2993) Player.UpdateBuff(BuffNames::TrigramHth, BuffNames::BuffTime, TriagramStats[21][GetCurrentGrade]);
				else if (Item.CheckIndex() == 3001) Player.UpdateBuff(BuffNames::TrigramHth, BuffNames::BuffTime, TriagramStats[22][GetCurrentGrade]);
				else if (Item.CheckIndex() == 3009) Player.UpdateBuff(BuffNames::TrigramHth, BuffNames::BuffTime, TriagramStats[23][GetCurrentGrade]);
			}
		}

		return CItemOrnament::ApplySpec(Itemx, Playerx);
	}
	else {
		return 0;
	}
}

signed int __fastcall OrnamentChangePrefix(void *Item, void* _edx, int Player, int ID, int Chance, int Argument)
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

	if (CItem::IsState((int)IItem.GetOffset(), 1) || ID >= 0 && ID != 2)
		return 0;

	if (IItem.Prefix())
		CurrentPrefix = IItem.PrefixID();

	NewPrefix = CurrentPrefix;
	int Rate = CTools::Rate(1, 100);

	for (signed int i = 0; i < 2; ++i)
	{
		if (Rate <= (int)*(DWORD*)(Chance + 4 * i))
		{
			NewPrefix = *(DWORD *)(Argument + 4 * i);
			break;
		}
	}

	if (DisablePrefix.count((IItem.CheckIndex() + 100000)*NewPrefix)) {
		IPlayer.BoxMsg("This talisman usage has been disabled for the following item.");
		return 0;
	}

	if (CurrentPrefix == NewPrefix)
	{
		CPlayer::Write(IPlayer.GetOffset(), 67, "b", 54);
	} else {
		if (WeaponReplace.count((IItem.CheckIndex()+100000)*NewPrefix) && WeaponReplaceIndex.count((IItem.CheckIndex()+100000)*NewPrefix))
		{
			std::string msg = (std::string)IPlayer.GetName();

			if (WeaponReplace.find((IItem.CheckIndex()+100000)*NewPrefix)->second && WeaponReplace.find((IItem.CheckIndex()+100000)*NewPrefix)->second == NewPrefix)
			{
				if (WeaponReplaceIndex.find((IItem.CheckIndex()+100000)*NewPrefix)->second)
				{
					if (CBase::IsDeleted((int)Item))
						return 0;

					if (IPlayer.IsBuff(328))
						return 0;
					else
						IPlayer.Buff(328,3,0);

					int ReplacePrefix = 0, ReplaceItem = 0, ReplaceInfo = 0;

					if (*(DWORD *)((int)Item + 44))
						ReplacePrefix = *(DWORD *)(*(DWORD *)((int)Item + 44) + 32);

					if (*(DWORD *)((int)Item + 48))
						ReplaceInfo = *(DWORD *)((int)Item + 48);

					int ItemNewIndex = IItem.CheckIndex();
					int DeleteCheck = (*(int (__thiscall **)(DWORD, void *, signed int, signed int))(*(DWORD*)Item + 120))((int)Item,IPlayer.GetOffset(),9,-1);

					if (!DeleteCheck)
					{
						ReplaceItem = CItem::CreateItem(WeaponReplaceIndex.find((ItemNewIndex+100000)*NewPrefix)->second, ReplacePrefix, 1, -1);

						if (ReplaceItem)
						{
							CIOObject::AddRef(ReplaceItem);
							*(DWORD *)(ReplaceItem + 48) = ReplaceInfo;

							if ( CPlayer::_InsertItem(IPlayer.GetOffset(), 27, ReplaceItem) != 1 )
							{
								CConsole::Red("Real time ornament insert item Null error [PID (%d)] ", IPlayer.GetPID());
								CBase::Delete((void *)ReplaceItem);
								CIOObject::Release((void *)ReplaceItem);
								return 0;
							}

							CIOObject::Release((void *)ReplaceItem);
							CDBSocket::Write(21, "dddbb",*(DWORD *)(ReplaceItem + 36),*(DWORD *)(ReplaceItem + 32),*(DWORD *)(ReplaceItem + 48),8,7);
							CPlayer::Write(IPlayer.GetOffset(), 0xFF, "ddddd", 242, 0, 0, 128, 255);
							std::string& successMsg = WeaponReplaceMsg.find((ItemNewIndex + 100000)*NewPrefix)->second;
							if (WeaponReplaceMsg.count((ItemNewIndex + 100000)*NewPrefix) && !successMsg.empty()){
								msg = msg + " " + successMsg;
								CPlayer::WriteAll(0xFF, "dsd", 247, msg.c_str(), NOTICECOLOR_BLUE);
							}

						}
					} else {
						return 0;
					}

					return 1;
				}
			}
		}

		if (WeaponReplacePrefix.count(NewPrefix))
		{
			IPlayer.BoxMsg("Enchanting item and the talisman are different.");
			return 0;
		}

		AddPrefix = CItem::FindPrefix(NewPrefix);

		if ( !AddPrefix )
			return 0;

		*(DWORD *)((int)IItem.GetOffset() + 44) = AddPrefix;
		CDBSocket::Write(19,"ddbb",IItem.GetIID(),IPlayer.GetID(),NewPrefix);
		CItem::SendItemInfo(IItem.GetOffset(), (int)IPlayer.GetOffset(), 92);
	}

	return 1;
}

int __fastcall OrnamentSetWearState(int Item, void *edx, int Player)
{
	IItem IItem((void*)Item);
	IChar IPlayer((void*)Player);

	if (!IPlayer.IsOnline() || !IItem.Exists())
		return 0;

	if (IItem.GetType() == -108 && CItem::IsState(Item, 1)) {
		CPlayer::AddWState((int)IPlayer.GetOffset(), IItem.GetType());
		(*(void(__thiscall **)(int, int))(*(DWORD *)Item + 104))(Item, (int)IPlayer.GetOffset());
		return 0;
	}

	if (IItem.GetType() == -3 && CItem::IsState(Item, 1)) {
		if (CPlayer::IsWState((int)IPlayer.GetOffset(), IItem.GetType()) && IPlayer.GetBuffValue(3879) < 2 && IPlayer.GetBuffValue(BuffNames::Essence3)) {
			CPlayer::AddWState((int)IPlayer.GetOffset(), IItem.GetType());
			(*(void(__thiscall **)(int, int))(*(DWORD *)Item + 104))(Item, (int)IPlayer.GetOffset());
			int old = IPlayer.GetBuffValue(3879);
			IPlayer.UpdateBuff(3879, 1296000, old+1);
			return 0;
		}
	}

	if (IPlayer.IsOnline()) {

		if (IItem.CheckIndex() >= 3381 && IItem.CheckIndex() <= 3383 && !IPlayer.GetBuffValue(BuffNames::MirrorBuff) && IItem.GetInfo() & 1)
			IPlayer.UpdateBuff(BuffNames::MirrorBuff, BuffNames::BuffTime, IItem.GetIID());

		if (IItem.CheckIndex() >= 3384 && IItem.CheckIndex() <= 3386 && IItem.GetInfo() & 1)
		{
			int Count = 0;
			for (int i = BuffNames::Essence1; i <= BuffNames::Essence5; i++) {
				if (IPlayer.GetBuffValue(i))
					Count++;
			}

			if (Count == 5) {
				CItem::SubState(Item, 1);
				CDBSocket::Write(5, "d", *(DWORD *)(Item + 36));
				return 0;
			}
			bool wore = false;
			if (!IPlayer.GetBuffValue(BuffNames::Essence1))
			{
				wore = true;
				*(DWORD*)(*(DWORD*)(Item + 40) + 72) = -95;
				IPlayer.UpdateBuff(BuffNames::Essence1, BuffNames::BuffTime, IItem.GetIID());
			}
			else if (!IPlayer.GetBuffValue(BuffNames::Essence2)) {
				wore = true;
				*(DWORD*)(*(DWORD*)(Item + 40) + 72) = -96;
				IPlayer.UpdateBuff(BuffNames::Essence2, BuffNames::BuffTime, IItem.GetIID());
			}
			else if (!IPlayer.GetBuffValue(BuffNames::Essence3)) {
				wore = true;
				*(DWORD*)(*(DWORD*)(Item + 40) + 72) = -97;
				IPlayer.UpdateBuff(BuffNames::Essence3, BuffNames::BuffTime, IItem.GetIID());
			}
			else if (!IPlayer.GetBuffValue(BuffNames::Essence4)) {
				wore = true;
				*(DWORD*)(*(DWORD*)(Item + 40) + 72) = -98;
				IPlayer.UpdateBuff(BuffNames::Essence4, BuffNames::BuffTime, IItem.GetIID());
			}
			else if (!IPlayer.GetBuffValue(BuffNames::Essence5)) {
				wore = true;
				*(DWORD*)(*(DWORD*)(Item + 40) + 72) = -99;
				IPlayer.UpdateBuff(BuffNames::Essence5, BuffNames::BuffTime, IItem.GetIID());
			}
			else {
				CItem::SubState(Item, 1);
				CDBSocket::Write(5, "d", *(DWORD *)(Item + 36));
			}

			if(wore){
				CPlayer::AddWState((int)IPlayer.GetOffset(), IItem.GetType());
				(*(void(__thiscall **)(int, int))(*(DWORD *)Item + 104))(Item, (int)IPlayer.GetOffset());
			}

			return 0;
		}
	}

	return CItemOrnament::SetWearState(Item,Player);
}