int __fastcall StandardBroken(void* Item, void* edx, int Player, int Argument) {

	if (!StBroken)
		return 0;

	IItem IItem(Item);

	if (!IItem.Exists())
		return 0;

	if (!IItem.CheckIndex())
		return 0;

	if (isItemRiding(IItem.CheckIndex()) || UnBreak.count(IItem.CheckIndex()))
		return 0;

	return CItemStandard::Broken(Item, Player, Argument);
}

void __fastcall StandardApplySpec(int Item, void *edx, int Player)
{
	IItem IItem((void*)Item);
	IChar IPlayer((void*)Player);

	if (IPlayer.IsOnline())
	{
		CItemStandard::ApplySpec(Item, Player);

		int Satiety = 0;
		itemStat.Enter();
		int ItemStat = GetItemStat.count(IItem.GetIID()) ? GetItemStat.find(IItem.GetIID())->second : 0;
		itemStat.Leave();

		int GStat = ItemStat;
		if (GStat > 0 && isItemRiding(IItem.CheckIndex())) {
			Satiety = ItemStat / 100;
			if (Satiety > 0) {
				IPlayer.UpdateBuff(BuffNames::Satiety, BuffNames::BuffTime, Satiety);
				GStat -= (Satiety * 100);
			}

			if (isItemRiding(IItem.CheckIndex()) && GStat > 0) {
				if (IItem.GetClass() == 0)
					IPlayer.AddHp(GStat >= 6 ? (((GStat - 5) * 3) + 10) : GStat * 2);
				if (IItem.GetClass() == 1 || IItem.GetClass() == -1)
					IPlayer.AddHp(GStat >= 6 ? (((GStat - 5) * 3) + 10) : GStat * 2);
				if (IItem.GetClass() == 2 || IItem.GetClass() == 3)
					IPlayer.AddHp(GStat >= 6 ? (((GStat - 5) * 3) + 10) : GStat * 2);
			}
		}

		if (isBattleRiding(IItem.CheckIndex())) {

			if (IPlayer.GetBuffValue(BuffNames::RidingUsing))
				CPlayer::Write((void*)Player, 0xFE, "ddd", 200, IItem.GetIID(), (1728 * Satiety));

			IPlayer.UpdateBuff(BuffNames::RidingIID, BuffNames::BuffTime, IItem.GetIID());
		}
	}
}

void __fastcall StandardPutOff(void *Item, void *edx, int Player)
{
	IItem Removing((void*)Item);
	IChar IPlayer((void*)Player);

	int BF = *(DWORD *)(Player + 1116);
	int BF1 = *(DWORD *)(Player + 512);
	int BF2 = *(DWORD *)(Player + 1120);


	IPlayer.CancelBuff(BuffNames::StandardOn);

	if (IPlayer.IsOnline() && Removing.Exists() && isItemRiding(Removing.CheckIndex())) {

		CPlayer::Write((void*)Player, 0xFE, "ddd", 200, Removing.GetIID(), 0);
		if (IPlayer.IsBuff(349))
			IPlayer.DisableRiding();

		if (IPlayer.GetBuffValue(BuffNames::RidingUsing)) {
			IItem Ride((void*)IPlayer.GetBuffValue(BuffNames::RidingUsing));
			*(DWORD *)((int)Ride.GetOffset() + 128) = 0;
			CItemStandard::PutOff(Ride.GetOffset(), Player);

			if (IPlayer.IsBuff(349))
				IPlayer.DisableRiding();

			IPlayer.UpdateBuff(BuffNames::RidingUsing, BuffNames::BuffTime, 0);

			if (BF && CItem::IsState(BF, 1)) {
				*(DWORD *)(Player + 1116) = BF;
				*(DWORD *)(Player + 1120) = BF2;
				*(DWORD *)(Player + 512) = BF1;
			}
		}
	}

	CItemStandard::PutOff(Item, Player);

	if (BF && isItemRiding(Removing.CheckIndex()) && CItem::IsState(BF, 1)) {
		*(DWORD *)(Player + 1116) = BF;
		*(DWORD *)(Player + 1120) = BF2;
		*(DWORD *)(Player + 512) = BF1;
	}

	itemStat.Enter();
	int ItemStat = GetItemStat.count(Removing.GetIID()) ? GetItemStat.find(Removing.GetIID())->second : 0;
	itemStat.Leave();
	int GStat = ItemStat;
	if (ItemStat > 0 && isItemRiding(Removing.CheckIndex())) {
		int Satiety = ItemStat / 100;
		if (Satiety > 0)
			GStat -= (Satiety * 100);

		int PSasiety = IPlayer.GetBuffValue(BuffNames::Satiety);
		if (PSasiety)
			Satiety = PSasiety;

		if (GStat > 0) {
			if (Removing.GetClass() == 0)
				IPlayer.RemoveHp(GStat >= 6 ? (((GStat - 5) * 3) + 10) : GStat * 2);
			if (Removing.GetClass() == 1 || Removing.GetClass() == -1)
				IPlayer.RemoveHp(GStat >= 6 ? (((GStat - 5) * 3) + 10) : GStat * 2);
			if (Removing.GetClass() == 2 || Removing.GetClass() == 3)
				IPlayer.RemoveHp(GStat >= 6 ? (((GStat - 5) * 3) + 10) : GStat * 2);
		}
		if (isBattleRiding(Removing.CheckIndex())) {
			if (Satiety) {

				itemStat.Enter();
				GetItemStat[Removing.GetIID()] = ItemStat + (100 * Satiety);
				itemStat.Leave();
				CDBSocket::Write(90, "dd", ItemStat + (100 * Satiety), Removing.GetIID());

				CPlayer::Write((void*)Player, 0xFE, "ddd", 200, Removing.GetIID(), 1728 * Satiety);
			}

			IPlayer.UpdateBuff(BuffNames::RidingIID, BuffNames::BuffTime, 0);
			IPlayer.CancelBuff(BuffNames::Satiety);
		}
	}
}

void __fastcall StandardPutOn(int Item, void *edx, int Player)
{
	IItem IItem((void*)Item);
	IChar IPlayer((void*)Player);
	if (IPlayer.IsOnline() && isItemRiding(IItem.CheckIndex())) {
		if (IPlayer.IsBuff(347))
			return;

		if (IPlayer.GetBuffValue(BuffNames::RidingUsing)) {
			IPlayer.SystemMessage("Riding pet is already equipped", TEXTCOLOR_YELLOW);
			return;
		}
	}

	int BF = *(DWORD *)(Player + 1116);
	int BF1 = *(DWORD *)(Player + 512);
	int BF2 = *(DWORD *)(Player + 1120);

	if (IPlayer.IsBuff(BuffNames::StandardOn)){
		IPlayer.SystemMessage("An item is already equipped.", TEXTCOLOR_RED);
		return;
	}
	IPlayer.Buff(BuffNames::StandardOn, 604800, 1);

	CItemStandard::PutOn(Item, Player);

	if (CItem::IsState(Item, 1) && isItemRiding(IItem.CheckIndex())) {
		IPlayer.UpdateBuff(BuffNames::RidingUsing, BuffNames::BuffTime, Item);
		if (BF) {
			if (CItem::IsState(BF, 1)) {
				*(DWORD *)(Player + 1116) = BF;
				*(DWORD *)(Player + 1120) = BF2;
				*(DWORD *)(Player + 512) = BF1;
			}
			else {
				*(DWORD *)(Player + 512) &= 0xFFFFu;
				*(DWORD *)(Player + 1116) = 0;
				*(DWORD *)(Player + 1120) = -1;
			}
		}
	}
}