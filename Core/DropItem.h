void __fastcall DropItemONPKDie(void *Player, void *edx)
{

	IChar IPlayer(Player);

	if (IPlayer.IsOnline())
	{
		int MapX = IPlayer.GetX() >> 13;
		int MapY = IPlayer.GetY() >> 13;

		if (strlen(SinCheck) && ((std::string)SinCheck == "disable" || (std::string)SinCheck == "Disable") && !PKDropEnable.count((MapX * 1000) + MapY))
			return;
		else
			CPlayer::DropItemONPKDie(Player);
	}
}

//new
int __fastcall MoneyDrop(int Item, void *edx, int a5, int a6, int a7, int a8, int IsParty, int ID)
{

	if (IsParty) {
		if (ChannelActivated) {
			void *Party = (void *)CParty::FindParty(ID);
			if (Party) {
				int PTPlayer = CParty::GetRandomPlayer((void*)Party);
				if (PTPlayer) {
					IChar IPlayer((void*)PTPlayer);
					int Channel = IPlayer.GetChannel();

					if (Channel)
						ChannelItems.replaceInsert(*(DWORD *)(Item + 28), Channel);

					CSkill::ObjectRelease((void*)PTPlayer, PTPlayer + 352);
				}
				CIOObject::Release(Party);
			}
		}
	}
	else
	{
		TargetFind myTarget(0, 0, ID);
		int Player = (int)myTarget.getTarget();
		if (Player) {
			IChar IPlayer((void*)Player);
			if (IPlayer.IsOnline() && Item) {
				if (ChannelActivated) {
					int Channel = IPlayer.GetChannel();

					if (Channel)
						ChannelItems.replaceInsert(*(DWORD *)(Item + 28), Channel);
				}

				int WealthBuffed = IPlayer.GetBuffValue(2129);
				if (WealthBuffed)
					*(DWORD *)(Item + 52) += WealthBuffed * *(DWORD *)(Item + 52) / 100;
			}
		}
	}

	return CItemMoney::Drop(Item, a5, a6, a7, a8, IsParty, ID);
}
//endnew

void __fastcall DropItem(DWORD a1, void *edx, int Item, int Chance, char a6, int a7, int a8, DWORD *a9, int a10)
{

	TargetFind myTarget(0, 0, a8);
	int Player = (int)myTarget.getTarget();

	IChar IPlayer((void*)Player);

	if(IPlayer.IsOnline() && IPlayer.GetType() == 0 && IPlayer.GetBuffValue(2129))
		Chance *= IPlayer.GetBuffValue(2129);

	CItem::InitDrop(a1, Item, Chance, a6, a7, a8, a9, a10);

}

LONG __fastcall ItemDrop(int Item, void* edx, int a5, int a6, int a7, int a8, int IsParty, int ID)
{

	if (ChannelActivated && ID) {
		if (IsParty) {
			void *Party = (void *)CParty::FindParty(ID);
			if (Party) {
				int PTPlayer = CParty::GetRandomPlayer((void*)Party);
				if (PTPlayer) {
					IChar IPlayer((void*)PTPlayer);
					int Channel = IPlayer.GetChannel();

					if (Channel)
						ChannelItems.replaceInsert(*(DWORD *)(Item + 28), Channel);

					CSkill::ObjectRelease((void*)PTPlayer, PTPlayer + 352);
				}
				CIOObject::Release(Party);
			}
		}
		else {
			TargetFind myTarget(0, 0, ID);
			int xPlayer = (int)myTarget.getTarget();
			IChar IPlayer((void*)xPlayer);

			int Channel = IPlayer.GetChannel();

			if (Channel)
				ChannelItems.replaceInsert(*(DWORD *)(Item + 28), Channel);
		}
	}

	return CItem::Drop(Item, a5, a6, a7, a8, IsParty, ID);
}