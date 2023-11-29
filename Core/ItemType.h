void ShowItem(IChar IPlayer, int Buff) {
	if (IPlayer.IsOnline() && IPlayer.IsBuff(Buff)) {
		int Player = (int)IPlayer.GetOffset();
		int Value = IPlayer.GetBuffValue(Buff);
		//CPlayer::AddWState(Player, 4);
		//*(WORD *)(Player + 2 * 4 + 1052) = Value;
		if (Value) {
			int v7 = *(DWORD *)(Player + 28);
			CChar::WriteInSight((void*)Player, 5, "ddw", v7, 0, Value);
		}
	}
}

bool isRewarded(IChar IPlayer) {
	std::string check = IPlayer.GetIP();
	if (RewardHWID && User.count(IPlayer.GetPID()))
		check = User.findValue(IPlayer.GetPID()).Hardware;

	return RewardLimit.count(check);
}

void rewardLimit(IChar IPlayer) {
	std::string check = IPlayer.GetIP();
	if (RewardHWID && User.count(IPlayer.GetPID()))
		check = User.findValue(IPlayer.GetPID()).Hardware;

	RewardLimit.insert(check);
}

bool isBFRewarded(IChar IPlayer) {
	std::string check = IPlayer.GetIP();
	if (RewardHWID && User.count(IPlayer.GetPID()))
		check = User.findValue(IPlayer.GetPID()).Hardware;

	return BFRewardLimit.count(check);
}

void BFrewardLimit(IChar IPlayer) {
	std::string check = IPlayer.GetIP();
	if (RewardHWID && User.count(IPlayer.GetPID()))
		check = User.findValue(IPlayer.GetPID()).Hardware;

	BFRewardLimit.insert(check);
}

bool isDKRewarded(IChar IPlayer) {
	std::string check = IPlayer.GetIP();
	if (RewardHWID && User.count(IPlayer.GetPID()))
		check = User.findValue(IPlayer.GetPID()).Hardware;

	return DKRewardLimit.count(check);
}

void DKrewardLimit(IChar IPlayer) {
	std::string check = IPlayer.GetIP();
	if (RewardHWID && User.count(IPlayer.GetPID()))
		check = User.findValue(IPlayer.GetPID()).Hardware;

	DKRewardLimit.insert(check);
}

bool isItemRiding(int Index) {
	if(NewItemType.count(Index))
		return NewItemType.find(Index)->second == RIDING_PET;
	return false;
}

bool isItemSuit(int Index) {
	if (NewItemType.count(Index))
		return NewItemType.find(Index)->second == COSTUME_SUIT;
	return false;
}

bool isItemCustomWeapon(int Index) {
	if (NewItemType.count(Index))
		return NewItemType.find(Index)->second == CUSTOM_WEAPON;
	return false;
}

bool isItemCostumeEffect(int Index) {
	if (NewItemType.count(Index))
		return NewItemType.find(Index)->second == COSTUMEEFFECT;
	return false;
}

bool isItemRidingArmor(int Index) {
	if (NewItemType.count(Index))
		return NewItemType.find(Index)->second == RIDING_ARMOR;
	return false;
}

bool isBattleRiding(int Index) {
	return (Index >= 7880 && Index <= 7882) || Index == 9663;
}

bool isPremiumPet(int Index) {
	if (NewItemType.count(Index))
		return NewItemType.find(Index)->second == PREMIUM_PET;
	return false;
}

bool isNormalPet(int Index) {
	if (NewItemType.count(Index))
		return NewItemType.find(Index)->second == NORMAL_PET;
	return false;
}

bool isMonsterPet(int Index) {
	if (NewItemType.count(Index))
		return NewItemType.find(Index)->second == MONSTER_PET;
	return false;
}

bool isPet(int Index) {
	return isNormalPet(Index) || isMonsterPet(Index) || isPremiumPet(Index);
}

int GetBattleRidingType(int Index) {

	if (Index == 7883 || Index == 7884 || Index == 7889 || Index == 7890 || Index == 7895 || Index == 7896 || Index == 7901 || Index == 7902)
		return 1;

	if (Index == 7886 || Index == 7892 || Index == 7898 || Index == 7904)
		return 2;

	if (Index == 7885 || Index == 7891 || Index == 7897 || Index == 7903)
		return 3;

	if (Index == 7887 || Index == 7893 || Index == 7899 || Index == 7905)
		return 4;

	if (Index == 7888 || Index == 7894 || Index == 7900 || Index == 7906)
		return 5;

	return 0;
}

int GetBattleRidingGrade(int Index) {
	if (Index >= 7883 && Index <= 7888)
		return 1;

	if (Index >= 7889 && Index <= 7894)
		return 2;

	if (Index >= 7895 && Index <= 7900)
		return 3;

	if (Index >= 7901 && Index <= 7906)
		return 4;

	return 0;
}

bool isSoulPocket(int Index) {
	if (NewItemType.count(Index))
		return NewItemType.find(Index)->second == SOUL_POCKET;
	return false;
}

bool isNecklace2(int Index) {
	if (NewItemType.count(Index))
		return NewItemType.find(Index)->second == NECKLACE2;
	return false;
}

void updateSoulPocket(IChar IPlayer, int SoulPocket) {
	if (IPlayer.IsOnline() && SoulPocket>0) {
		int IID = IPlayer.GetBuffValue(BuffNames::SoulPocketIID);
		if (IID) {
			int usage = SoulPocket - 1;
			IPlayer.UpdateBuff(BuffNames::SoulPocketAmount, BuffNames::BuffTime, usage);
			IPlayer.UpdateBuff(BuffNames::SPUpdated, BuffNames::BuffTime, 1);
			CPlayer::Write(IPlayer.GetOffset(), 0xFE, "ddd", 198, IID, usage);
		}
	}
}

void _updateSoulPocket(IChar IPlayer, int SoulPocket) {
	if (IPlayer.IsOnline() && SoulPocket>0) {
		int IID = IPlayer._GetBuffValue(BuffNames::SoulPocketIID);
		if (IID) {
			int usage = SoulPocket - 1;
			IPlayer._UpdateBuff(BuffNames::SoulPocketAmount, BuffNames::BuffTime, usage);
			IPlayer._UpdateBuff(BuffNames::SPUpdated, BuffNames::BuffTime, 1);
			CPlayer::Write(IPlayer.GetOffset(), 0xFE, "ddd", 198, IID, usage);
		}
	}
}
