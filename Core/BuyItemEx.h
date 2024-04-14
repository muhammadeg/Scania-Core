signed int __fastcall PlayerRemoveItem(void *Player, void *edx, int Value, int Index, int Amount)
{
	IChar IPlayer(Player);

	if (IPlayer.IsOnline())
	{
		if (Index == 639 && IPlayer.IsBuff(BuffNames::NewName)) {
			IPlayer.CancelBuff(BuffNames::NewName);
			return 1;
		}

		if ((Index == 509 || Index == 510)) {
			if (IPlayer.GetMap() == BFMap || IPlayer.GetMap() == ScenarioMap || IPlayer.GetMap() == LMSMap || IPlayer.GetMap() == HellMap || IPlayer.GetMap() == PLMap || IPlayer.GetMap() == SVMap || IPlayer.GetMap() == TBMap || IPlayer.GetMap() == BossEXPMap || IPlayer.GetMap() == 21 || IPlayer.GetMap() == MautMap)
			{
				IPlayer.BoxMsg("Saving location is not allowed during the battle.");
				return 0;
			}

			if (TimedMaps.count(IPlayer.GetMapIndex())) {
				IPlayer.BoxMsg("Saving location is not in timed areas.");
				return 0;
			}

			if (!ScrollEM && EventMaps.count(IPlayer.GetMapIndex())) {
				IPlayer.BoxMsg("Saving location is not available here.");
				return 0;
			}
		}

		if (Index == 515 || Index == 516) {
			if (IPlayer.GetMap() == TBMap && (TriangularBattle::Active || TriangularBattle::CDActive))
				return 0;

			if (Shouts == 1) {
				IPlayer.BoxMsg("Shouts have been temporarily disabled.");
				return 0;
			}
		}
	}

	return CPlayer::RemoveItem(Player,Value,Index,Amount);
}

int __fastcall NPCTick(void *NPC, void *edx)
{

	if (SufferingValley::Active && !SufferingValley::RedOpened && (SufferingValley::Time - (int)time(0)) <= SVTime && *(DWORD*)((int)NPC + 448) == 609)
	{
		(*(void(__thiscall **)(DWORD, DWORD))(*(DWORD*)(int)NPC + 100))((int)NPC, 16);
		*(DWORD *)((int)NPC + 480) = ((SVTime - 3) * 1000) + GetTickCount();
		SufferingValley::RedOpened = true;
	}

	if (SufferingValley::Active && !SufferingValley::BlueOpened && (SufferingValley::Time - (int)time(0)) <= SVTime && *(DWORD*)((int)NPC + 448) == 610)
	{
		(*(void(__thiscall **)(DWORD, DWORD))(*(DWORD*)(int)NPC + 100))((int)NPC, 16);
		*(DWORD *)((int)NPC + 480) = ((SVTime - 3) * 1000) + GetTickCount();
		SufferingValley::BlueOpened = true;
	}

	if (Protect32::Active && !Protect32::RedOpened && Protect32::Time <= 1200 && *(DWORD*)((int)NPC + 448) == PLRNPC)
	{
		(*(void (__thiscall **)(DWORD, DWORD))(*(DWORD*)(int)NPC + 100))((int)NPC, 16);
		*(DWORD *)((int)NPC + 480) = 1197000 + GetTickCount();
		Protect32::RedOpened = true;
	}

	if (Protect32::Active && !Protect32::BlueOpened && Protect32::Time <= 1200 && *(DWORD*)((int)NPC + 448) == PLBNPC)
	{
		(*(void (__thiscall **)(DWORD, DWORD))(*(DWORD*)(int)NPC + 100))((int)NPC, 16);
		*(DWORD *)((int)NPC + 480) = 1197000 + GetTickCount();
		Protect32::BlueOpened = true;
	}

	//if (!RaidDoors::Opened && *(DWORD*)((int)NPC + 448) == 1470 + RaidDoors::Round)
	//{
	//	(*(void(__thiscall **)(DWORD, DWORD))(*(DWORD*)(int)NPC + 100))((int)NPC, 16);
	//	*(DWORD *)((int)NPC + 480) = 1197000 + GetTickCount();
	//	RaidDoors::Opened = true;
	//}

	return CNPCDoor::Tick(NPC);
}

void __fastcall BuyItemEx(void *Player, void *edx, char Npc, int Tax, int ItemSize, int pPacket, int pPos)
{

	IChar IPlayer(Player);

	if (IPlayer.IsOnline())
	{
		int Check = pPacket, Amount = 0, Index = 0, Item = 0, Price = 0;
		unsigned __int16 ItemIndex = 0, ItemAmount = 0;

		if (ItemSize <= 0)
			return;

		if (ItemSize > 100)
			return;

		bool StoreCheck = !StoreItems.empty();

		for (int i = 0; *((DWORD*)Player + 274) && i < ItemSize; i++)
		{
			Check = CPacket::Read((char*)Check, (char*)pPos, (const char*)0x004BADB4, &ItemIndex, &ItemAmount);
			Amount = ItemAmount; Index = ItemIndex;

			if (Amount > 0)
			{
				if (StoreCheck && !StoreItems.count(Index)) {
					IPlayer.SystemMessage("You are not allowed to buy this item.", TEXTCOLOR_RED);
					return;
				}

				Item = CItem::CreateItem(Index, 0, Amount, -1);

				if (Item)
				{
					CIOObject::AddRef(Item);
					Price = (int)*(DWORD*)(*(DWORD*)(Item + 40) + 108);

					if (Price <= 0)
					{
						CBase::Delete((void*)Item);
						return;
					}

					if ((Price * Amount) > 2000000000)
					{
						IPlayer.SystemMessage("You are not allowed to buy this amount from this store.", TEXTCOLOR_RED);
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
				}
			}
		}

		CPlayer::BuyItemEx(Player, Npc, Tax, ItemSize, pPacket, pPos);
	}
}

/*void __fastcall BuyItemEx(void *Player, void *edx, char Npc, int Tax, int Mult, int pPacket, int pPos)
{
	IChar IPlayer(Player);

	if (IPlayer.IsOnline())
	{
		int Check = pPacket, Amount = 0, Index = 0, Item = 0, Price = 0;
		unsigned __int16 ItemIndex = 0, ItemAmount = 0;

		unsigned __int16 Size = 0, Type = 0;

		Check = CPacket::Read((char*)Check, (char*)pPos, (const char*)0x004BADB4, &Size, &Type);
		int C = Check;

		int ItemSize = ((Type - 356) / 256) + 1;
		int NNpc = Tax + (256 * Mult);

		if (ItemSize <= 0)
			return;

		if (ItemSize > 100)
			return;

		bool StoreCheck = !StoreItems.empty();

		for (int i = 0; *((DWORD*)Player + 274) && i < ItemSize; i++)
		{
			Check = CPacket::Read((char*)Check, (char*)pPos, (const char*)0x004BADB4, &ItemIndex, &ItemAmount);
			Amount = ItemAmount; Index = ItemIndex;
			if (Amount > 0)
			{
				if (StoreCheck && !StoreItems.count(Index)) {
					IPlayer.SystemMessage("You are not allowed to buy this item.", TEXTCOLOR_RED);
					return;
				}

				Item = CItem::CreateItem(Index, 0, Amount, -1);

				if (Item)
				{
					Price = (int)*(DWORD*)(*(DWORD*)(Item + 40) + 108);

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

					if ((int)Mult == 255) {
						if (CPlayer::RemoveItem(Player, 27, 31, Price*Amount)) {
							CIOObject::AddRef(Item);

							if (CPlayer::InsertItem(Player, 27, Item) != 1)
								CBase::Delete((void*)Item);

							CIOObject::Release((void*)Item);
						}
						else
							CBase::Delete((void*)Item);
					}
					else
						CBase::Delete((void*)Item);
				}
			}
		}

		if ((int)Mult == 255)
			return;

		int CheckNPC = CNPC::FindNPC((char)NNpc);
		if (CheckNPC) {
			int Castle = CCastle::GetCastle(*(DWORD*)(CheckNPC + 464));
			CIOObject::Release((void*)CheckNPC);

			if (Castle) {
				int CastleTax = CCastle::GetTaxRate((void*)Castle);
				if (Tax != CastleTax)
					Tax = CastleTax;
			}
		}

		CPlayer::BuyItemEx(Player, (char)NNpc, Tax, ItemSize, C, pPos);
	}
}*/