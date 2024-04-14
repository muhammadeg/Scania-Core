signed int __fastcall WeaponCharmingCheat(void *Item, void *edx, int Player, int Type, int Value)
{
	int v5; // [sp+4h] [bp-8h]@1
	int v6; // [sp+8h] [bp-4h]@4

	v5 = (int)Item;
	if (CItem::GetLevel((int)Item) < 40 || CItem::IsState(v5, 1))
		return 0;

	v6 = CItem::IsState(v5, 64);
	if (Type == 9)
	{
		*(DWORD *)(v5 + 112) = Value;
		CDBSocket::Write(17, "ddbbb", *(DWORD *)(v5 + 36), *(DWORD *)(v5 + 32), 9, *(DWORD *)(v5 + 112), v6);
	}
	else if (Type == 27)
	{
		*(DWORD *)(v5 + 100) = Value;
		CDBSocket::Write(17, "ddbbb", *(DWORD *)(v5 + 36), *(DWORD *)(v5 + 32), 27, *(DWORD *)(v5 + 100), v6);
	}
	else
	{
		if (Type != 28)
			return 0;

		int ItemType = *(DWORD *)(*(DWORD *)(v5 + 40) + 72);
		if (abs(ItemType) != 1)
			return 0;

		*(DWORD *)(v5 + 104) = Value;
		CDBSocket::Write(17, "ddbbb", *(DWORD *)(v5 + 36), *(DWORD *)(v5 + 32), Type, *(DWORD *)(v5 + 104), v6);
	}
	CItem::SendItemInfo((void *)v5, Player, 92);
	return 1;
}

void __fastcall WeaponUpgradeDestroy(int Item, void *edx, int Player)
{
	signed int v5; // [sp+0h] [bp-20h]@14
	signed int v6; // [sp+4h] [bp-1Ch]@12
	signed int v7; // [sp+8h] [bp-18h]@10
	int v8; // [sp+Ch] [bp-14h]@6
	int v9; // [sp+10h] [bp-10h]@1

	v9 = Item;
	if (CItem::GetLevel(Item) >= 40
		&& !CItem::IsState(v9, 1)
		&& (*(int(__thiscall **)(int, int, signed int))(*(DWORD *)v9 + 88))(v9, Player, 45))
	{
		if (CItem::GetLevel(v9) - 40 >= 20)
			v8 = 20;
		else
			v8 = CItem::GetLevel(v9) - 40;

		int ItemType = *(DWORD *)(*(DWORD *)(v9 + 40) + 72);

		if (abs(ItemType) == 1)
		{
			if (*(DWORD *)(v9 + 104) >= 20)
				v7 = 20;
			else
				v7 = *(DWORD *)(v9 + 104);
			v6 = v7;
		}
		else
		{
			if (*(DWORD *)(v9 + 100) >= 20)
				v5 = 20;
			else
				v5 = *(DWORD *)(v9 + 100);
			v6 = v5;
		}
		CItem::InsertItem(Player, 45, 517, 0, Charming::MinStones[v6] + Charming::MaxStones[v8], -1);
		CPlayer::_OutOfInven((void*)Player, v9);
	}
}

signed int __fastcall WeaponUpgradeLevel(void* Item, void *edx, int Player)
{
	int result; // eax@1
	signed int UpgradeRate; // esi@15
	int v4; // [sp+4h] [bp-30h]@29
	signed int v5; // [sp+Ch] [bp-28h]@13
	signed int v6; // [sp+10h] [bp-24h]@10
	int v7; // [sp+14h] [bp-20h]@5
	int Itemx; // [sp+18h] [bp-1Ch]@1
	signed int v9; // [sp+28h] [bp-Ch]@19
	int MoneyToRemove; // [sp+2Ch] [bp-8h]@8
	int v11; // [sp+30h] [bp-4h]@8

	IChar IPlayer((void*)Player);
	Itemx = (int)Item;
	result = CItem::GetLevel((int)Item);
	if (result >= 40)
	{
		result = CItem::IsState(Itemx, 1);
		if (!result)
		{

			int ItemType = *(DWORD *)(*(DWORD *)(Itemx + 40) + 72);

			v7 = (abs(ItemType) == 1) && !(*(DWORD *)(*(DWORD *)((int)Item + 40) + 96) == 3) ? *(DWORD *)(Itemx + 104) : *(DWORD *)(Itemx + 100);
			result = Itemx;

			if (*(DWORD *)(Itemx + 124) < v7)
			{

				MoneyToRemove = 1500 * (*(DWORD *)(Itemx + 124) + 1);
				result = CPlayer::_FindItem((int)Player, 31, MoneyToRemove);
				v11 = result;
				if (result)
				{
					if (*(DWORD *)(Itemx + 124) >= 19)
						v6 = 19;
					else
						v6 = *(DWORD *)(Itemx + 124);
					if (*(DWORD *)(Itemx + 124) >= 19)
						v5 = 19;
					else
						v5 = *(DWORD *)(Itemx + 124);
					UpgradeRate = Charming::EBMin[v6] + *(DWORD *)(Itemx + 128) * Charming::EBMax[v5];
					if (UpgradeRate < CTools::Rate(1, 100))
					{
						v9 = CTools::Rate(1, 100);
						if (v9 > 60)
						{
							if (v9 > 90)
							{
								CPlayer::Write((void*)Player, 68, "bd", 82, *(DWORD *)(Itemx + 36));
								if (*(DWORD *)(Itemx + 44))
									v4 = *(DWORD *)(*(DWORD *)(Itemx + 44) + 32);
								else
									v4 = 0;
								CDBSocket::Write(3, "ddwdbddd", *(DWORD *)(Itemx + 36), *(DWORD *)(Itemx + 32), *(DWORD *)(*(DWORD *)(Itemx + 40) + 64), *(DWORD *)(Itemx + 52), 47, *(DWORD *)(Itemx + 100) & 0xFF | ((*(DWORD *)(Itemx + 84) & 0xFF) << 8) | ((*(DWORD *)(Itemx + 92) & 0xFF) << 16) | (v4 << 24), ((*(DWORD *)(Itemx + 112) & 0xFF) << 8) | (*(DWORD *)(Itemx + 104) << 24), ((*(DWORD *)(Itemx + 128) & 0xFF) << 8) | ((*(DWORD *)(Itemx + 124) & 0xFF) << 16) | (*(DWORD *)(Itemx + 120) << 24));
								CPlayer::_OutOfInven((void*)Player, Itemx);
								result = CBase::Delete((char *)Itemx);
							}
							else
							{
								*(DWORD *)(Itemx + 128) = 0;
								if (*(DWORD *)(Itemx + 124) <= 0)
									CDBSocket::Write(28, "ddbb", *(DWORD *)(Itemx + 36), *(DWORD *)(Itemx + 32), 2, 0);
								else
									CDBSocket::Write(28, "ddbb", *(DWORD *)(Itemx + 36), *(DWORD *)(Itemx + 32), 2, --*(DWORD *)(Itemx + 124));
								result = CItem::SendItemInfo((void *)Itemx, Player, 92);
							}
						}
						else
						{
							if (!(*(int(__thiscall **)(int, int, signed int, int))(*(DWORD *)v11 + 120))(v11, Player, 47, -MoneyToRemove))
								CPlayer::_OutOfInven((void*)Player, v11);
							CPlayer::Write((void*)Player, 67, "b", 81);
							result = 1;
						}
					}
					else
					{
						if (!(*(int(__thiscall **)(int, int, signed int, int))(*(DWORD *)v11 + 120))(v11, Player, 47, -MoneyToRemove))
							CPlayer::_OutOfInven((void*)Player, v11);
						*(DWORD *)(Itemx + 128) = 0;
						CDBSocket::Write(28, "ddbb", *(DWORD *)(Itemx + 36), *(DWORD *)(Itemx + 32), 2, ++*(DWORD *)(Itemx + 124));
						result = CItem::SendItemInfo((void *)Itemx, Player, 92);
					}
				}
			}
		}
	}
	return result;
}

signed int __fastcall WeaponCharming(void* Item, void *edx, int Player, int Type)
{
	signed int result; // eax@3
	int v4; // esi@9
	int v5; // esi@15
	int v6; // esi@19
	signed int v7; // [sp+4h] [bp-40h]@49
	signed int v8; // [sp+8h] [bp-3Ch]@47
	signed int v9; // [sp+Ch] [bp-38h]@45
	int v10; // [sp+10h] [bp-34h]@41
	int v11; // [sp+14h] [bp-30h]@38
	void *v12; // [sp+1Ch] [bp-28h]@1
	signed int v13; // [sp+38h] [bp-Ch]@28
	signed int v14; // [sp+3Ch] [bp-8h]@29
	int v15; // [sp+40h] [bp-4h]@4

	v12 = Item;
	if (CItem::GetLevel((int)Item) < 40 || CItem::IsState((int)v12, 1))
		return 0;
	v15 = CItem::IsState((int)v12, 64);
	if (Type == 9)
	{
		if (*((DWORD *)v12 + 28) < 20)
		{
			v6 = *((DWORD *)v12 + 28);
			if (Charming::XHit[v6] >= CTools::Rate(1, 10000000))
			{
				CDBSocket::Write(17, "ddbbb", *((DWORD *)v12 + 9), *((DWORD *)v12 + 8), 9, ++*((DWORD *)v12 + 28), v15);
				goto LABEL_22;
			}
		}
		goto LABEL_25;
	}
	if (Type == 27)
	{
		if (*((DWORD *)v12 + 25) < 20)
		{
			v4 = *((DWORD *)v12 + 25);
			if (Charming::XAttack[v4] >= CTools::Rate(1, 10000000))
			{
				CDBSocket::Write(17, "ddbbb", *((DWORD *)v12 + 9), *((DWORD *)v12 + 8), Type, ++*((DWORD *)v12 + 25), v15);
				goto LABEL_22;
			}
		}
	LABEL_25:
		if (v15)
		{
			CDBSocket::Write(21, "dddbb", *((DWORD *)v12 + 9), *((DWORD *)v12 + 8), 64, 0, Type);
			CItem::SubState((int)v12, 64);
			CItem::SendItemInfo(v12, Player, 92);
			result = 1;
		}
		else
		{
			if (CTools::Rate(1, 100) > 90)
			{
				*((DWORD *)v12 + 24) = 0;
			}
			else
			{
				v13 = CTools::Rate(1, 100);
				if (v13 <= 50)
				{
					if (v13 <= 20)
						v14 = 3;
					else
						v14 = 2;
				}
				else
				{
					v14 = 1;
				}
				*((DWORD *)v12 + 24) -= v14;
			}
			if (*((DWORD *)v12 + 24) <= 0)
			{
				CPlayer::Write((void*)Player, 91, "db", *((DWORD *)v12 + 9), 0);
				if (*((DWORD *)v12 + 11))
					v11 = *(DWORD *)(*((DWORD *)v12 + 11) + 32);
				else
					v11 = 0;
				CDBSocket::Write(3, "ddwdbddd", *((DWORD *)v12 + 9), *((DWORD *)v12 + 8), *(DWORD *)(*((DWORD *)v12 + 10) + 64), *((DWORD *)v12 + 13), 21, *((DWORD *)v12 + 25) & 0xFF | ((*((DWORD *)v12 + 21) & 0xFF) << 8) | ((*((DWORD *)v12 + 23) & 0xFF) << 16) | (v11 << 24), ((*((DWORD *)v12 + 28) & 0xFF) << 8) | (*((DWORD *)v12 + 26) << 24), ((*((DWORD *)v12 + 32) & 0xFF) << 8) | ((*((DWORD *)v12 + 31) & 0xFF) << 16) | (*((DWORD *)v12 + 30) << 24));
				if (CItem::GetLevel((int)v12) - 40 >= 20)
					v10 = 20;
				else
					v10 = CItem::GetLevel((int)v12) - 40;
				int ItemTypeCheck = *(DWORD *)(*((DWORD *)v12 + 10) + 72);
				if (abs(ItemTypeCheck) == 1)
				{
					if (*((DWORD *)v12 + 26) >= 20)
						v9 = 20;
					else
						v9 = *((DWORD *)v12 + 26);
					v8 = v9;
				}
				else
				{
					if (*((DWORD *)v12 + 25) >= 20)
						v7 = 20;
					else
						v7 = *((DWORD *)v12 + 25);
					v8 = v7;
				}
				CItem::InsertItem(Player, 21, 517, 0, Charming::MinStones[v8] + Charming::MaxStones[v10], -1);
				CBase::Delete((char *)v12);
			}
			else
			{
				CPlayer::Write((void*)Player, 91, "db", *((DWORD *)v12 + 9), *((DWORD *)v12 + 24));
				CDBSocket::Write(18, "ddb", *((DWORD *)v12 + 9), *((DWORD *)v12 + 8), *((DWORD *)v12 + 24));
			}
			result = 1;
		}
		return result;
	}
	if (Type != 28)
		return 0;

	int ItemType = *(DWORD *)(*((DWORD *)v12 + 10) + 72);
	if (abs(ItemType) != 1)
		return 0;

	if (*((DWORD *)v12 + 26) >= 20)
		goto LABEL_25;
	v5 = *((DWORD *)v12 + 26);
	if (Charming::XAttack[v5] < CTools::Rate(1, 10000000))
		goto LABEL_25;
	CDBSocket::Write(17, "ddbbb", *((DWORD *)v12 + 9), *((DWORD *)v12 + 8), Type, ++*((DWORD *)v12 + 26), v15);
LABEL_22:
	if (v15)
		CItem::SubState((int)v12, 64);
	CItem::SendItemInfo(v12, Player, 92);
	return 1;
}

signed int __fastcall WeaponChangePrefix(void *Item, void *edx, int Player, int ID, int Chance, int Argument)
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

	if (CItem::IsState((int)IItem.GetOffset(), 1) || ID >= 0 && ID)
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

	if (DisablePrefix.count((IItem.CheckIndex() + 100000)*NewPrefix)) {
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
		int CurrentInfo = 0, CurrentMixInfo = 0, SetMixInfo = 0;

		if (IItem.GetInfo())
			CurrentInfo = IItem.GetInfo();

		if (CurrentInfo >= 1310720)
			CurrentMixInfo = 1310720;
		else if (CurrentInfo >= 1179648)
			CurrentMixInfo = 1179648;
		else if (CurrentInfo >= 1114112)
			CurrentMixInfo = 1114112;
		else if (CurrentInfo >= 1081344)
			CurrentMixInfo = 1081344;
		else if (CurrentInfo >= 1064960)
			CurrentMixInfo = 1064960;
		else if (CurrentInfo >= 1056768)
			CurrentMixInfo = 1056768;
		else if (CurrentInfo >= 1052672)
			CurrentMixInfo = 1052672;
		else if (CurrentInfo >= 1050624)
			CurrentMixInfo = 1050624;
		else if (CurrentInfo >= 1049600)
			CurrentMixInfo = 1049600;
		else if (CurrentInfo >= 1049088)
			CurrentMixInfo = 1049088;
		else if (CurrentInfo >= 1048832)
			CurrentMixInfo = 1048832;
		else if (CurrentInfo >= 589824)
			CurrentMixInfo = 589824;
		else if (CurrentInfo >= 557056)
			CurrentMixInfo = 557056;
		else if (CurrentInfo >= 540672)
			CurrentMixInfo = 540672;
		else if (CurrentInfo >= 532480)
			CurrentMixInfo = 532480;
		else if (CurrentInfo >= 528384)
			CurrentMixInfo = 528384;
		else if (CurrentInfo >= 526336)
			CurrentMixInfo = 526336;
		else if (CurrentInfo >= 525312)
			CurrentMixInfo = 525312;
		else if (CurrentInfo >= 524800)
			CurrentMixInfo = 524800;
		else if (CurrentInfo >= 524544)
			CurrentMixInfo = 524544;

		if (CurrentMixInfo)
			CurrentInfo -= CurrentMixInfo;

		int pveConf = PVEDamagePimp.count(NewPrefix);
		int pvpConf = PVPDamagePimp.count(NewPrefix);

		if (pveConf || pvpConf) {
			std::string successMsg = "Succes: When wearing this weapons,";
			if (pveConf)
				successMsg += "\nYour PVE Damage will be increased by: " + Int2String(PVEDamagePimp.find(NewPrefix)->second) + "%.";
			if (pvpConf)
				successMsg += "\nYour PVP Damage will be increased by: " + Int2String(PVPDamagePimp.find(NewPrefix)->second) + "%.";
			IPlayer.BoxMsg(successMsg);
		}

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
				IPlayer.BoxMsg("Your weapon is not enchanted with demon gong power.");
				return 0;
			}
			itemStat.Enter();
			GetItemStat[IItem.GetIID()] = CurItemStat - ((CurGrade * 1000000) + (DemonGongStyle * 10000000) + (SecondDemonGongType * 100000) + (SecondDemonGongStat * 10000));
			itemStat.Leave();
			CDBSocket::Write(90, "dd", CurItemStat - ((CurGrade * 1000000) + (DemonGongStyle * 10000000) + (SecondDemonGongType * 100000) + (SecondDemonGongStat * 10000)), IItem.GetIID());

			CPlayer::Write(IPlayer.GetOffset(), 255, "dddb", 224, IItem.GetIID(), 0, 0);

			CItem::SendItemInfo(IItem.GetOffset(), (int)IPlayer.GetOffset(), 92);
			IPlayer.SystemMessage("Your demon gong ability has been successfully removed from your weapon.", TEXTCOLOR_DARKGREEN);
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

		if (CheckPimp.count(NewPrefix) && CheckPimp.find(NewPrefix)->second.Prefix)
		{
			PimpConfig pimp = CheckPimp.find(NewPrefix)->second;

			IItem.SetTalismanOA(pimp.GetA);
			IItem.SetTalismanOM(pimp.GetM);

			if (pimp.GetTOA)
				IItem.SetTOA(pimp.GetTOA);

			IItem.SetUpgrade(pimp.GetUpg);

			CDBSocket::Write(17, "ddbbb", IItem.GetIID(), IPlayer.GetPID(), 27, IItem.GetTalismanOA(), 0);
			CDBSocket::Write(17, "ddbbb", IItem.GetIID(), IPlayer.GetPID(), 28, IItem.GetTalismanOM(), 0);
			CDBSocket::Write(17, "ddbbb", IItem.GetIID(), IPlayer.GetPID(), 9, IItem.GetTOA(), 0);
			CDBSocket::Write(28, "ddbb", IItem.GetIID(), IPlayer.GetPID(), 2, IItem.GetUpgrade());
			CItem::SendItemInfo(IItem.GetOffset(), (int)IPlayer.GetOffset(), 92);
			return 1;
		}

		if (MixConfigPrefix.count(NewPrefix))
		{
			SetMixInfo = MixConfigInfo.find(NewPrefix)->second;
			CDBSocket::Write(21, "dddbb", IItem.GetIID(), IPlayer.GetID(), IItem.GetInfo(), 0, 0);
			IItem.SetInfo(CurrentInfo + SetMixInfo);
			CDBSocket::Write(21, "dddbb", IItem.GetIID(), IPlayer.GetID(), CurrentInfo + SetMixInfo, 8, 7);
			CItem::SendItemInfo(IItem.GetOffset(), (int)IPlayer.GetOffset(), 92);
			CPlayer::Write(IPlayer.GetOffset(), 0xFF, "ddddd", 242, 10, 0, 128, 255);

			if (MixConfigMsg.count(NewPrefix))
				IPlayer.SystemMessage(MixConfigMsg.find(NewPrefix)->second, TEXTCOLOR_DARKGREEN);

			return 1;
		}

		if (WeaponReplace.count((IItem.CheckIndex() + 100000)*NewPrefix) && WeaponReplaceIndex.count((IItem.CheckIndex() + 100000)*NewPrefix))
		{
			if (WeaponReplace.find((IItem.CheckIndex() + 100000)*NewPrefix)->second == NewPrefix)
			{
				if (CBase::IsDeleted((int)Item))
					return 0;

				if (IPlayer.IsBuff(328))
					return 0;
				else
					IPlayer.Buff(328, 3, 0);

				int ReplacePrefix = 0, ReplaceItem = 0, ReplaceInfo = 0, ReplaceA = 0, ReplaceM = 0, ReplaceTOA = 0, ReplaceEB = 0, ReplaceGem = 0;
				int ItemStat = 0;

				itemStat.Enter();
				if (GetItemStat.count(IItem.GetIID()))
					ItemStat = GetItemStat.find(IItem.GetIID())->second;
				itemStat.Leave();

				if (*(DWORD *)((int)Item + 44))
					ReplacePrefix = *(DWORD *)(*(DWORD *)((int)Item + 44) + 32);

				if (*(DWORD *)((int)Item + 48))
					ReplaceInfo = *(DWORD *)((int)Item + 48);

				if (*(DWORD *)((int)Item + 100))
					ReplaceA = *(DWORD *)((int)Item + 100);

				if (*(DWORD *)((int)Item + 104))
					ReplaceM = *(DWORD *)((int)Item + 104);

				if (*(DWORD *)((int)Item + 112))
					ReplaceTOA = *(DWORD *)((int)Item + 112);

				if (*(DWORD *)((int)Item + 124))
					ReplaceEB = *(DWORD *)((int)Item + 124);

				if (*(DWORD *)((int)Item + 84))
					ReplaceGem = *(DWORD *)((int)Item + 84);

				int ItemNewIndex = IItem.CheckIndex();
				int DeleteCheck = (*(int(__thiscall **)(DWORD, void *, signed int, signed int))(*(DWORD*)Item + 120))((int)Item, IPlayer.GetOffset(), 9, -1);

				if (!DeleteCheck)
				{
					ReplaceItem = CItem::CreateItem(WeaponReplaceIndex.find((ItemNewIndex + 100000)*NewPrefix)->second, ReplacePrefix, 1, -1);

					if (ReplaceItem)
					{
						CIOObject::AddRef(ReplaceItem);
						*(DWORD *)(ReplaceItem + 48) = ReplaceInfo;
						*(DWORD *)(ReplaceItem + 100) = ReplaceA;
						*(DWORD *)(ReplaceItem + 104) = ReplaceM;
						*(DWORD *)(ReplaceItem + 112) = ReplaceTOA;
						*(DWORD *)(ReplaceItem + 124) = ReplaceEB;
						*(DWORD *)(ReplaceItem + 84) = ReplaceGem;

						if (CPlayer::_InsertItem(IPlayer.GetOffset(), 27, ReplaceItem) != 1)
						{
							CConsole::Red("Real time weapon replace insert item Null error [PID (%d)] ", IPlayer.GetPID());
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
						CDBSocket::Write(17, "ddbbb", *(DWORD *)(ReplaceItem + 36), *(DWORD *)(ReplaceItem + 32), 27, *(DWORD *)(ReplaceItem + 100), 0);
						CDBSocket::Write(17, "ddbbb", *(DWORD *)(ReplaceItem + 36), *(DWORD *)(ReplaceItem + 32), 28, *(DWORD *)(ReplaceItem + 104), 0);
						CDBSocket::Write(17, "ddbbb", *(DWORD *)(ReplaceItem + 36), *(DWORD *)(ReplaceItem + 32), 9, *(DWORD *)(ReplaceItem + 112), 0);
						CDBSocket::Write(28, "ddbb", *(DWORD *)(ReplaceItem + 36), *(DWORD *)(ReplaceItem + 32), 2, *(DWORD *)(ReplaceItem + 124));
						CItem::SendItemInfo((void*)ReplaceItem, (int)IPlayer.GetOffset(), 92);
						CPlayer::Write(IPlayer.GetOffset(), 0xFF, "ddddd", 242, 0, 0, 128, 255);
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

		if (NewPrefix == ImpConfigRead)
		{
			if (IItem.CheckIndex() >= 769 && IItem.CheckIndex() <= 801
				|| IItem.CheckIndex() >= 1433 && IItem.CheckIndex() <= 1441
				|| IItem.CheckIndex() >= 1700 && IItem.CheckIndex() <= 1704
				|| IItem.CheckIndex() >= 3033 && IItem.CheckIndex() <= 3039
				|| IItem.CheckIndex() >= 1921 && IItem.CheckIndex() <= 1927
				|| IItem.CheckIndex() >= 1821 && IItem.CheckIndex() <= 1824
				|| IItem.CheckIndex() >= 1448 && IItem.CheckIndex() <= 1453
				|| IItem.CheckIndex() >= 1442 && IItem.CheckIndex() <= 1445
				|| IItem.CheckIndex() >= 2676 && IItem.CheckIndex() <= 2682
				|| IItem.CheckIndex() >= 2688 && IItem.CheckIndex() <= 2693
				|| IItem.CheckIndex() >= 2700 && IItem.CheckIndex() <= 2705
				|| IItem.CheckIndex() >= 4329 && IItem.CheckIndex() <= 4335
				|| IItem.CheckIndex() == 1853 || IItem.CheckIndex() == 1669
				|| IItem.CheckIndex() == 1668)
			{
				IPlayer.SystemMessage("Your weapon already imperial.", TEXTCOLOR_RED);
				return 0;
			}

			int ItemStat = 0;
			itemStat.Enter();
			if (GetItemStat.count(IItem.GetIID()))
				ItemStat = GetItemStat.find(IItem.GetIID())->second;
			itemStat.Leave();

			int GetWeaponGrade = *(DWORD*)(*(DWORD *)((int)Item + 40) + 80), Imp = 0, xMixPrefix = 0, ImpItem = 0;

			if (GetWeaponGrade > 80)
				return 0;

			switch (GetWeaponGrade)
			{
			case 0x28:
				if (*(DWORD *)(*(DWORD *)((int)Item + 40) + 96) == -1)
				{
					Imp = 7210;
				}
				else if (*(DWORD *)(*(DWORD *)((int)Item + 40) + 96) == 3)
				{
					Imp = 1433;
				}
				else if (*(DWORD *)(*(DWORD *)((int)Item + 40) + 96))
				{
					if (*(DWORD *)(*(DWORD *)((int)Item + 40) + 96) == 1)
						Imp = 771;
					else
						Imp = 770;
				}
				else {
					Imp = 769;
				}
				break;
			case 0x2D:
				if (*(DWORD *)(*(DWORD *)((int)Item + 40) + 96) == -1)
				{
					Imp = 7290;
				}
				else if (*(DWORD *)(*(DWORD *)((int)Item + 40) + 96) == 3)
				{
					Imp = 1434;
				}
				else if (*(DWORD *)(*(DWORD *)((int)Item + 40) + 96))
				{
					if (*(DWORD *)(*(DWORD *)((int)Item + 40) + 96) == 1)
						Imp = 774;
					else
						Imp = 773;
				}
				else {
					Imp = 772;
				}
				break;
			case 0x30:
				if (*(DWORD *)(*(DWORD *)((int)Item + 40) + 96) == -1)
				{
					Imp = 7214;
				}
				else if (*(DWORD *)(*(DWORD *)((int)Item + 40) + 96) == 3)
				{
					Imp = 1435;
				}
				else if (*(DWORD *)(*(DWORD *)((int)Item + 40) + 96))
				{
					if (*(DWORD *)(*(DWORD *)((int)Item + 40) + 96) == 1)
						Imp = 777;
					else
						Imp = 776;
				}
				else {
					Imp = 775;
				}
				break;
			case 0x32:
				if (*(DWORD *)(*(DWORD *)((int)Item + 40) + 96) == -1)
				{
					Imp = 7218;
				}
				else if (*(DWORD *)(*(DWORD *)((int)Item + 40) + 96) == 3)
				{
					Imp = 1436;
				}
				else if (*(DWORD *)(*(DWORD *)((int)Item + 40) + 96))
				{
					if (*(DWORD *)(*(DWORD *)((int)Item + 40) + 96) == 1)
						Imp = 781;
					else
						Imp = 780;
				}
				else {
					Imp = (*(DWORD *)(*(DWORD *)((int)Item + 40) + 72) != 0) + 778;
				}
				break;
			case 0x35:
				if (*(DWORD *)(*(DWORD *)((int)Item + 40) + 96) == -1)
				{
					Imp = 7222;
				}
				else if (*(DWORD *)(*(DWORD *)((int)Item + 40) + 96) == 3)
				{
					Imp = 1437;
				}
				else if (*(DWORD *)(*(DWORD *)((int)Item + 40) + 96))
				{
					if (*(DWORD *)(*(DWORD *)((int)Item + 40) + 96) == 1)
						Imp = 785;
					else
						Imp = 784;
				}
				else {
					Imp = (*(DWORD *)(*(DWORD *)((int)Item + 40) + 72) != 0) + 782;
				}
				break;
			case 0x38:
				if (*(DWORD *)(*(DWORD *)((int)Item + 40) + 96) == -1)
				{
					Imp = 7226;
				}
				else if (*(DWORD *)(*(DWORD *)((int)Item + 40) + 96) == 3)
				{
					Imp = 1438;
				}
				else if (*(DWORD *)(*(DWORD *)((int)Item + 40) + 96))
				{
					if (*(DWORD *)(*(DWORD *)((int)Item + 40) + 96) == 1)
						Imp = 789;
					else
						Imp = 788;
				}
				else {
					Imp = (*(DWORD *)(*(DWORD *)((int)Item + 40) + 72) != 0) + 786;
				}
				break;
			case 0x3B:
				if (*(DWORD *)(*(DWORD *)((int)Item + 40) + 96) == -1)
				{
					Imp = 7230;
				}
				else if (*(DWORD *)(*(DWORD *)((int)Item + 40) + 96) == 3)
				{
					Imp = 1439;
				}
				else if (*(DWORD *)(*(DWORD *)((int)Item + 40) + 96))
				{
					if (*(DWORD *)(*(DWORD *)((int)Item + 40) + 96) == 1)
						Imp = 793;
					else
						Imp = 792;
				}
				else {
					Imp = (*(DWORD *)(*(DWORD *)((int)Item + 40) + 72) != 0) + 790;
				}
				break;
			case 0x3E:
				if (*(DWORD *)(*(DWORD *)((int)Item + 40) + 96) == -1)
				{
					if (IItem.CheckIndex() == 7231)
						Imp = 7230;
					else if (IItem.CheckIndex() == 7233)
						Imp = 7235;
					else if (IItem.CheckIndex() == 7234)
						Imp = 7236;
				}
				else if (*(DWORD *)(*(DWORD *)((int)Item + 40) + 96) == 3)
				{
					Imp = 1440;
				}
				else if (*(DWORD *)(*(DWORD *)((int)Item + 40) + 96))
				{
					if (*(DWORD *)(*(DWORD *)((int)Item + 40) + 96) == 1)
						Imp = 797;
					else
						Imp = 796;
				}
				else {
					Imp = (*(DWORD *)(*(DWORD *)((int)Item + 40) + 72) != 0) + 794;
				}
				break;
			case 0x41:
				if (*(DWORD *)(*(DWORD *)((int)Item + 40) + 96) == -1)
				{
					Imp = 7238;
				}
				else if (*(DWORD *)(*(DWORD *)((int)Item + 40) + 96) == 3)
				{
					Imp = 1441;
				}
				else if (*(DWORD *)(*(DWORD *)((int)Item + 40) + 96))
				{
					if (*(DWORD *)(*(DWORD *)((int)Item + 40) + 96) == 1 && IItem.CheckIndex() == 672)
						Imp = 801;
					else if (*(DWORD *)(*(DWORD *)((int)Item + 40) + 96) == 1 && IItem.CheckIndex() == 1677)
						Imp = 1821;
					else if (*(DWORD *)(*(DWORD *)((int)Item + 40) + 96) == 1 && IItem.CheckIndex() == 1678)
						Imp = 1822;
					else
						Imp = 800;
				}
				else {
					Imp = (*(DWORD *)(*(DWORD *)((int)Item + 40) + 72) != 0) + 798;
				}
				break;
			case 0x46:
				if (*(DWORD *)(*(DWORD *)((int)Item + 40) + 96) == -1)
				{
					if (IItem.CheckIndex() == 7239)
						Imp = 7241;
					else if (IItem.CheckIndex() == 7240)
						Imp = 7242;
				}
				else if (*(DWORD *)(*(DWORD *)((int)Item + 40) + 96) == 3)
				{
					Imp = 1704;
				}
				else if (*(DWORD *)(*(DWORD *)((int)Item + 40) + 96))
				{
					if (*(DWORD *)(*(DWORD *)((int)Item + 40) + 96) == 1 && IItem.CheckIndex() == 1698)
						Imp = 1853;
					else if (*(DWORD *)(*(DWORD *)((int)Item + 40) + 96) == 1 && IItem.CheckIndex() == 1705)
						Imp = 1823;
					else if (*(DWORD *)(*(DWORD *)((int)Item + 40) + 96) == 1 && IItem.CheckIndex() == 1706)
						Imp = 1824;
					else
						Imp = 1702;
				}
				else {
					if (IItem.CheckIndex() == 1695)
						Imp = 1700;
					else
						Imp = 1701;
				}
				break;
			case 0x4B:
				if (*(DWORD *)(*(DWORD *)((int)Item + 40) + 96) == -1)
				{
					if (IItem.CheckIndex() == 7243)
						Imp = 7245;
					else if (IItem.CheckIndex() == 7244)
						Imp = 7246;
				}
				else if (*(DWORD *)(*(DWORD *)((int)Item + 40) + 96) == 3)
				{
					if (IItem.CheckIndex() == -1328)
						Imp = 4335;
					else
						Imp = 1927;
				}
				else if (*(DWORD *)(*(DWORD *)((int)Item + 40) + 96))
				{
					if (IItem.CheckIndex() == 1917)
						Imp = 1924;
					else if (IItem.CheckIndex() == 1918)
						Imp = 1925;
					else if (IItem.CheckIndex() == 1919)
						Imp = 1926;
					else if (*(DWORD *)(*(DWORD *)((int)Item + 40) + 96) == 1 && IItem.CheckIndex() == -1325)
						Imp = 4332;
					else if (*(DWORD *)(*(DWORD *)((int)Item + 40) + 96) == 1 && IItem.CheckIndex() == -1326)
						Imp = 4333;
					else if (*(DWORD *)(*(DWORD *)((int)Item + 40) + 96) == 1 && IItem.CheckIndex() == -1327)
						Imp = 4334;
					else if (IItem.CheckIndex() == -1324)
						Imp = 4331;
					else
						Imp = 1923;
				}
				else {
					if (IItem.CheckIndex() == 1914)
						Imp = 1921;
					else if (IItem.CheckIndex() == -1322)
						Imp = 4329;
					else if (IItem.CheckIndex() == -1323)
						Imp = 4330;
					else
						Imp = 1922;
				}
				break;
			case 0x50:
				if (*(DWORD *)(*(DWORD *)((int)Item + 40) + 96) == -1)
				{
					if (IItem.CheckIndex() == 7247)
						Imp = 7249;
					else if (IItem.CheckIndex() == 7248)
						Imp = 7250;
				}
				else if (*(DWORD *)(*(DWORD *)((int)Item + 40) + 96) == 3)
				{
					Imp = 3039;
				}
				else if (*(DWORD *)(*(DWORD *)((int)Item + 40) + 96))
				{
					if (*(DWORD *)(*(DWORD *)((int)Item + 40) + 96) == 1 && IItem.CheckIndex() == 3029)
						Imp = 3036;
					else if (*(DWORD *)(*(DWORD *)((int)Item + 40) + 96) == 1 && IItem.CheckIndex() == 3030)
						Imp = 3037;
					else if (*(DWORD *)(*(DWORD *)((int)Item + 40) + 96) == 1 && IItem.CheckIndex() == 3031)
						Imp = 3038;
					else
						Imp = 3035;
				}
				else {
					if (IItem.CheckIndex() == 3026)
						Imp = 3033;
					else
						Imp = 3034;
				}
				break;
			case 0x5A:
				if (*(DWORD *)(*(DWORD *)((int)Item + 40) + 96) == -1)
				{
					if (IItem.CheckIndex() == 7251)
						Imp = 7253;
					else if (IItem.CheckIndex() == 7252)
						Imp = 7254;
				}
				else if (*(DWORD *)(*(DWORD *)((int)Item + 40) + 96) == 3)
				{
					Imp = 3161;
				}
				else if (*(DWORD *)(*(DWORD *)((int)Item + 40) + 96))
				{
					if (*(DWORD *)(*(DWORD *)((int)Item + 40) + 96) == 1 && IItem.CheckIndex() == 3150)
						Imp = 3158;
					else if (*(DWORD *)(*(DWORD *)((int)Item + 40) + 96) == 1 && IItem.CheckIndex() == 3151)
						Imp = 3159;
					else if (*(DWORD *)(*(DWORD *)((int)Item + 40) + 96) == 1 && IItem.CheckIndex() == 3152)
						Imp = 3160;
					else
						Imp = 3157;
				}
				else {
					if (IItem.CheckIndex() == 3147)
						Imp = 3155;
					else
						Imp = 3156;
				}
				break;
			default:
				break;
			}

			if (!Imp)
				return 0;

			if (*(DWORD *)((int)Item + 44))
				xMixPrefix = *(DWORD *)(*(DWORD *)((int)Item + 44) + 32);
			else
				xMixPrefix = 0;

			int DeleteCheck = (*(int(__thiscall **)(DWORD, void *, signed int, signed int))(*(DWORD*)Item + 120))((int)Item, IPlayer.GetOffset(), 9, -1);

			if (!DeleteCheck)
			{
				ImpItem = CItem::CreateItem(Imp, xMixPrefix, 1, -1);

				if (ImpItem)
				{
					CIOObject::AddRef(ImpItem);

					if (*(DWORD *)((int)Item + 48))
						*(DWORD *)(ImpItem + 48) = *(DWORD *)((int)Item + 48);

					if (*(DWORD *)((int)Item + 100))
						*(DWORD *)(ImpItem + 100) = *(DWORD *)((int)Item + 100);

					if (*(DWORD *)((int)Item + 104))
						*(DWORD *)(ImpItem + 104) = *(DWORD *)((int)Item + 104);

					if (*(DWORD *)((int)Item + 112))
						*(DWORD *)(ImpItem + 112) = *(DWORD *)((int)Item + 112);

					if (*(DWORD *)((int)Item + 124))
						*(DWORD *)(ImpItem + 124) = *(DWORD *)((int)Item + 124);

					if (*(DWORD *)((int)Item + 84))
						*(DWORD *)(ImpItem + 84) = *(DWORD *)((int)Item + 84);

					if (CPlayer::_InsertItem(IPlayer.GetOffset(), 27, ImpItem) != 1)
					{
						CConsole::Red("MixItem() insert item Null error [PID (%d)] ", IPlayer.GetPID());
						CBase::Delete((void *)ImpItem);
						CIOObject::Release((void *)ImpItem);
						return 0;
					}

					CIOObject::Release((void *)ImpItem);
					itemStat.Enter();
					GetItemStat[*(DWORD *)(ImpItem + 36)] = ItemStat;
					itemStat.Leave();

					CDBSocket::Write(90, "dd", ItemStat, *(DWORD *)(ImpItem + 36));
					CDBSocket::Write(87, "ddd", IPlayer.GetPID(), *(DWORD *)(ImpItem + 84), *(DWORD *)(ImpItem + 36));
					CDBSocket::Write(21, "dddbb", *(DWORD *)(ImpItem + 36), *(DWORD *)(ImpItem + 32), *(DWORD *)(ImpItem + 48), 8, 7);
					CDBSocket::Write(17, "ddbbb", *(DWORD *)(ImpItem + 36), *(DWORD *)(ImpItem + 32), 27, *(DWORD *)(ImpItem + 100), 0);
					CDBSocket::Write(17, "ddbbb", *(DWORD *)(ImpItem + 36), *(DWORD *)(ImpItem + 32), 28, *(DWORD *)(ImpItem + 104), 0);
					CDBSocket::Write(17, "ddbbb", *(DWORD *)(ImpItem + 36), *(DWORD *)(ImpItem + 32), 9, *(DWORD *)(ImpItem + 112), 0);
					CDBSocket::Write(28, "ddbb", *(DWORD *)(ImpItem + 36), *(DWORD *)(ImpItem + 32), 2, *(DWORD *)(ImpItem + 124));
					CItem::SendItemInfo((void*)ImpItem, (int)IPlayer.GetOffset(), 92);
					CPlayer::Write(IPlayer.GetOffset(), 0xFF, "ddddd", 242, 10, 0, 128, 255);
				}
			}
			else {
				return 0;
			}

			return 1;

		}

		int impgrade = HighGradeImperial.find(NewPrefix)->second;
		int impprefix = HighGradeImperial.find(NewPrefix)->first;
		std::string msg = (std::string)IPlayer.GetName();

		if (HighGradeImperial.count(NewPrefix) || NewPrefix == Imp2ConfigRead)
		{
			if (IItem.CheckIndex() >= 769 && IItem.CheckIndex() <= 801
				|| IItem.CheckIndex() >= 1433 && IItem.CheckIndex() <= 1441
				|| IItem.CheckIndex() >= 1700 && IItem.CheckIndex() <= 1704
				|| IItem.CheckIndex() >= 3033 && IItem.CheckIndex() <= 3039
				|| IItem.CheckIndex() >= 1921 && IItem.CheckIndex() <= 1927
				|| IItem.CheckIndex() >= 1821 && IItem.CheckIndex() <= 1824
				|| IItem.CheckIndex() >= 1448 && IItem.CheckIndex() <= 1453
				|| IItem.CheckIndex() >= 1442 && IItem.CheckIndex() <= 1445
				|| IItem.CheckIndex() >= 2676 && IItem.CheckIndex() <= 2682
				|| IItem.CheckIndex() >= 2688 && IItem.CheckIndex() <= 2693
				|| IItem.CheckIndex() >= 2700 && IItem.CheckIndex() <= 2705
				|| IItem.CheckIndex() >= 4329 && IItem.CheckIndex() <= 4335
				|| IItem.CheckIndex() == 1853 || IItem.CheckIndex() == 1669
				|| IItem.CheckIndex() == 1668)
			{
				IPlayer.SystemMessage("Your weapon already imperial.", TEXTCOLOR_RED);
				return 0;
			}

			if (IItem.CheckIndex() == 575)
			{
				IPlayer.SystemMessage("2 Handed Sword can not be upgraded.", TEXTCOLOR_RED);
				return 0;
			}
			int ItemStat = 0;
			itemStat.Enter();
			if (GetItemStat.count(IItem.GetIID()))
				ItemStat = GetItemStat.find(IItem.GetIID())->second;
			itemStat.Leave();

			int GetWeaponGrade = *(DWORD*)(*(DWORD *)((int)Item + 40) + 80), Imp = 0, xMixPrefix = 0, ImpItem = 0;

			if (GetWeaponGrade > 80)
				return 0;

			//if (GetWeaponGrade != impgrade) {
			//	IPlayer.SystemMessage("Imperial Talisman is not compitable with weapon grade.", TEXTCOLOR_RED);
			//	return 0;
			//}

			if (impgrade == GetWeaponGrade || GetWeaponGrade) {
				switch (GetWeaponGrade)
				{
				case 0x28:
					if (*(DWORD *)(*(DWORD *)((int)Item + 40) + 96) == -1)
					{
						Imp = 7210;
					}
					else if (*(DWORD *)(*(DWORD *)((int)Item + 40) + 96) == 3)
					{
						Imp = 1433;
					}
					else if (*(DWORD *)(*(DWORD *)((int)Item + 40) + 96))
					{
						if (*(DWORD *)(*(DWORD *)((int)Item + 40) + 96) == 1)
							Imp = 771;
						else
							Imp = 770;
					}
					else {
						Imp = 769;
					}
					break;
				case 0x2D:
					if (*(DWORD *)(*(DWORD *)((int)Item + 40) + 96) == -1)
					{
						Imp = 7290;
					}
					else if (*(DWORD *)(*(DWORD *)((int)Item + 40) + 96) == 3)
					{
						Imp = 1434;
					}
					else if (*(DWORD *)(*(DWORD *)((int)Item + 40) + 96))
					{
						if (*(DWORD *)(*(DWORD *)((int)Item + 40) + 96) == 1)
							Imp = 774;
						else
							Imp = 773;
					}
					else {
						Imp = 772;
					}
					break;
				case 0x30:
					if (*(DWORD *)(*(DWORD *)((int)Item + 40) + 96) == -1)
					{
						Imp = 7214;
					}
					else if (*(DWORD *)(*(DWORD *)((int)Item + 40) + 96) == 3)
					{
						Imp = 1435;
						msg = msg + " has enhanced " + GetDaggerName(GetWeaponGrade) + " with the Power of Imperial!";

					}
					else if (*(DWORD *)(*(DWORD *)((int)Item + 40) + 96))
					{
						if (*(DWORD *)(*(DWORD *)((int)Item + 40) + 96) == 1) {
							Imp = 777;
							msg = msg + " has enhanced " + GetStickName(GetWeaponGrade) + " with the Power of Imperial!";
						}
						else {
							Imp = 776;
							msg = msg + " has enhanced " + GetBowName(GetWeaponGrade) + " with the Power of Imperial!";

						}
					}
					else {
						Imp = 775;
						msg = msg + " has enhanced " + GetSwordName(GetWeaponGrade) + " with the Power of Imperial!";

					}
					break;
				case 0x32:
					if (*(DWORD *)(*(DWORD *)((int)Item + 40) + 96) == -1)
					{
						Imp = 7218;
					}
					else if (*(DWORD *)(*(DWORD *)((int)Item + 40) + 96) == 3)
					{
						Imp = 1436;
						msg = msg + " has enhanced " + GetDaggerName(GetWeaponGrade) + " with the Power of Imperial!";

					}
					else if (*(DWORD *)(*(DWORD *)((int)Item + 40) + 96))
					{
						if (*(DWORD *)(*(DWORD *)((int)Item + 40) + 96) == 1) {
							Imp = 781;
							msg = msg + " has enhanced " + GetStickName(GetWeaponGrade) + " with the Power of Imperial!";

						}
						else {
							Imp = 780;
							msg = msg + " has enhanced " + GetBowName(GetWeaponGrade) + " with the Power of Imperial!";

						}
					}
					else {
						Imp = (*(DWORD *)(*(DWORD *)((int)Item + 40) + 72) != 0) + 778;
						msg = msg + " has enhanced " + GetSwordName(GetWeaponGrade, (*(DWORD *)(*(DWORD *)((int)Item + 40) + 72) != 0)) + " with the Power of Imperial!";

					}
					break;
				case 0x35:
					if (*(DWORD *)(*(DWORD *)((int)Item + 40) + 96) == -1)
					{
						Imp = 7222;
					}
					else if (*(DWORD *)(*(DWORD *)((int)Item + 40) + 96) == 3)
					{
						Imp = 1437;
						msg = msg + " has enhanced " + GetDaggerName(GetWeaponGrade) + " with the Power of Imperial!";

					}
					else if (*(DWORD *)(*(DWORD *)((int)Item + 40) + 96))
					{
						if (*(DWORD *)(*(DWORD *)((int)Item + 40) + 96) == 1)
						{

							Imp = 785;
							msg = msg + " has enhanced " + GetStickName(GetWeaponGrade) + " with the Power of Imperial!";

						}
						else {
							Imp = 784;
							msg = msg + " has enhanced " + GetBowName(GetWeaponGrade) + " with the Power of Imperial!";

						}
					}
					else {
						Imp = (*(DWORD *)(*(DWORD *)((int)Item + 40) + 72) != 0) + 782;
						msg = msg + " has enhanced " + GetSwordName(GetWeaponGrade, (*(DWORD *)(*(DWORD *)((int)Item + 40) + 72) != 0)) + " with the Power of Imperial!";

					}
					break;
				case 0x38:
					if (*(DWORD *)(*(DWORD *)((int)Item + 40) + 96) == -1)
					{
						Imp = 7226;
					}
					else if (*(DWORD *)(*(DWORD *)((int)Item + 40) + 96) == 3)
					{
						Imp = 1438;
						msg = msg + " has enhanced " + GetDaggerName(GetWeaponGrade) + " with the Power of Imperial!";

					}
					else if (*(DWORD *)(*(DWORD *)((int)Item + 40) + 96))
					{
						if (*(DWORD *)(*(DWORD *)((int)Item + 40) + 96) == 1) {
							Imp = 789;
							msg = msg + " has enhanced " + GetStickName(GetWeaponGrade) + " with the Power of Imperial!";
						}
						else {
							Imp = 788;
							msg = msg + " has enhanced " + GetBowName(GetWeaponGrade) + " with the Power of Imperial!";

						}
					}
					else {
						Imp = (*(DWORD *)(*(DWORD *)((int)Item + 40) + 72) != 0) + 786;
						msg = msg + " has enhanced " + GetSwordName(GetWeaponGrade, (*(DWORD *)(*(DWORD *)((int)Item + 40) + 72) != 0)) + " with the Power of Imperial!";

					}
					break;
				case 0x3B:
					if (*(DWORD *)(*(DWORD *)((int)Item + 40) + 96) == -1)
					{
						Imp = 7230;
					}
					else if (*(DWORD *)(*(DWORD *)((int)Item + 40) + 96) == 3)
					{
						Imp = 1439;
						msg = msg + " has enhanced " + GetDaggerName(GetWeaponGrade) + " with the Power of Imperial!";

					}
					else if (*(DWORD *)(*(DWORD *)((int)Item + 40) + 96))
					{
						if (*(DWORD *)(*(DWORD *)((int)Item + 40) + 96) == 1)
						{

							Imp = 793;
							msg = msg + " has enhanced " + GetStickName(GetWeaponGrade) + " with the Power of Imperial!";
						}
						else {
							Imp = 792;
							msg = msg + " has enhanced " + GetBowName(GetWeaponGrade) + " with the Power of Imperial!";
						}
					}
					else {
						Imp = (*(DWORD *)(*(DWORD *)((int)Item + 40) + 72) != 0) + 790;
						msg = msg + " has enhanced " + GetSwordName(GetWeaponGrade, (*(DWORD *)(*(DWORD *)((int)Item + 40) + 72) != 0)) + " with the Power of Imperial!";

					}
					break;
				case 0x3E:
					if (*(DWORD *)(*(DWORD *)((int)Item + 40) + 96) == -1)
					{
						if (IItem.CheckIndex() == 7231)
							Imp = 7230;
						else if (IItem.CheckIndex() == 7233)
							Imp = 7235;
						else if (IItem.CheckIndex() == 7234)
							Imp = 7236;
					}
					else if (*(DWORD *)(*(DWORD *)((int)Item + 40) + 96) == 3)
					{
						Imp = 1440;
						msg = msg + " has enhanced " + GetDaggerName(GetWeaponGrade) + " with the Power of Imperial!";

					}
					else if (*(DWORD *)(*(DWORD *)((int)Item + 40) + 96))
					{
						if (*(DWORD *)(*(DWORD *)((int)Item + 40) + 96) == 1) {
							Imp = 797;
							msg = msg + " has enhanced " + GetStickName(GetWeaponGrade) + " with the Power of Imperial!";
						}
						else {
							Imp = 796;
							msg = msg + " has enhanced " + GetBowName(GetWeaponGrade) + " with the Power of Imperial!";
						}
					}
					else {
						Imp = (*(DWORD *)(*(DWORD *)((int)Item + 40) + 72) != 0) + 794;
						msg = msg + " has enhanced " + GetSwordName(GetWeaponGrade, (*(DWORD *)(*(DWORD *)((int)Item + 40) + 72) != 0)) + " with the Power of Imperial!";

					}
					break;
				case 0x41:
					if (*(DWORD *)(*(DWORD *)((int)Item + 40) + 96) == -1)
					{
						Imp = 7238;
					}
					else if (*(DWORD *)(*(DWORD *)((int)Item + 40) + 96) == 3)
					{
						Imp = 1441;
						msg = msg + " has enhanced " + GetDaggerName(GetWeaponGrade) + " with the Power of Imperial!";

					}
					else if (*(DWORD *)(*(DWORD *)((int)Item + 40) + 96))
					{
						if (*(DWORD *)(*(DWORD *)((int)Item + 40) + 96) == 1 && IItem.CheckIndex() == 672) {
							Imp = 801;
							msg = msg + " has enhanced " + GetStickName(GetWeaponGrade) + " with the Power of Imperial!";
						}
						else if (*(DWORD *)(*(DWORD *)((int)Item + 40) + 96) == 1 && IItem.CheckIndex() == 1677)
						{
							Imp = 1821;
							msg = msg + " has enhanced " + GetStickName(GetWeaponGrade) + " with the Power of Imperial!";

						}
						else if (*(DWORD *)(*(DWORD *)((int)Item + 40) + 96) == 1 && IItem.CheckIndex() == 1678) {
							Imp = 1822;
							msg = msg + " has enhanced " + GetStickName(GetWeaponGrade) + " with the Power of Imperial!";
						}
						else {
							Imp = 800;
							msg = msg + " has enhanced " + GetBowName(GetWeaponGrade) + " with the Power of Imperial!";
						}
					}
					else {
						Imp = (*(DWORD *)(*(DWORD *)((int)Item + 40) + 72) != 0) + 798;
						msg = msg + " has enhanced " + GetSwordName(GetWeaponGrade, (*(DWORD *)(*(DWORD *)((int)Item + 40) + 72) != 0)) + " with the Power of Imperial!";
					}
					break;
				case 0x46:
					if (*(DWORD *)(*(DWORD *)((int)Item + 40) + 96) == -1)
					{
						if (IItem.CheckIndex() == 7239)
							Imp = 7241;
						else if (IItem.CheckIndex() == 7240)
							Imp = 7242;
					}
					else if (*(DWORD *)(*(DWORD *)((int)Item + 40) + 96) == 3)
					{
						Imp = 1704;
						msg = msg + " has enhanced " + GetDaggerName(GetWeaponGrade) + " with the Power of Imperial!";
					}
					else if (*(DWORD *)(*(DWORD *)((int)Item + 40) + 96))
					{
						if (*(DWORD *)(*(DWORD *)((int)Item + 40) + 96) == 1 && IItem.CheckIndex() == 1698) {
							Imp = 1853;
							msg = msg + " has enhanced " + GetStickName(GetWeaponGrade) + " with the Power of Imperial!";
						}
						else if (*(DWORD *)(*(DWORD *)((int)Item + 40) + 96) == 1 && IItem.CheckIndex() == 1705) {
							Imp = 1823;
							msg = msg + " has enhanced " + GetStickName(GetWeaponGrade) + " with the Power of Imperial!";
						}
						else if (*(DWORD *)(*(DWORD *)((int)Item + 40) + 96) == 1 && IItem.CheckIndex() == 1706) {
							Imp = 1824;
							msg = msg + " has enhanced " + GetStickName(GetWeaponGrade) + " with the Power of Imperial!";
						}
						else {
							Imp = 1702;
							msg = msg + " has enhanced " + GetBowName(GetWeaponGrade) + " with the Power of Imperial!";
						}
					}
					else {
						if (IItem.CheckIndex() == 1695) {
							Imp = 1700;
							msg = msg + " has enhanced " + GetSwordName(GetWeaponGrade, false) + " with the Power of Imperial!";
						}
						else {
							Imp = 1701;
							msg = msg + " has enhanced " + GetSwordName(GetWeaponGrade, true) + " with the Power of Imperial!";
						}
					}
					break;
				case 0x4B:
					if (*(DWORD *)(*(DWORD *)((int)Item + 40) + 96) == -1)
					{
						if (IItem.CheckIndex() == 7243)
							Imp = 7245;
						else if (IItem.CheckIndex() == 7244)
							Imp = 7246;
					}
					else if (*(DWORD *)(*(DWORD *)((int)Item + 40) + 96) == 3)
					{
						if (IItem.CheckIndex() == -1328) {
							Imp = 4335;
							msg = msg + " has enhanced " + GetDaggerName(GetWeaponGrade) + " with the Power of Imperial!";
						}
						else {
							Imp = 1927;
							msg = msg + " has enhanced " + GetDaggerName(GetWeaponGrade) + " with the Power of Imperial!";
						}
					}
					else if (*(DWORD *)(*(DWORD *)((int)Item + 40) + 96))
					{
						if (IItem.CheckIndex() == 1917) {
							Imp = 1924;
							msg = msg + " has enhanced " + GetStickName(GetWeaponGrade) + " with the Power of Imperial!";
						}
						else if (IItem.CheckIndex() == 1918) {
							Imp = 1925;
							msg = msg + " has enhanced " + GetStickName(GetWeaponGrade) + " with the Power of Imperial!";
						}
						else if (IItem.CheckIndex() == 1919) {
							Imp = 1926;
							msg = msg + " has enhanced " + GetStickName(GetWeaponGrade) + " with the Power of Imperial!";
						}
						else if (*(DWORD *)(*(DWORD *)((int)Item + 40) + 96) == 1 && IItem.CheckIndex() == -1325) {
							Imp = 4332;
							msg = msg + " has enhanced " + GetStickName(GetWeaponGrade) + " with the Power of Imperial!";
						}
						else if (*(DWORD *)(*(DWORD *)((int)Item + 40) + 96) == 1 && IItem.CheckIndex() == -1326) {
							Imp = 4333;
							msg = msg + " has enhanced " + GetStickName(GetWeaponGrade) + " with the Power of Imperial!";
						}
						else if (*(DWORD *)(*(DWORD *)((int)Item + 40) + 96) == 1 && IItem.CheckIndex() == -1327) {
							Imp = 4334;
							msg = msg + " has enhanced " + GetStickName(GetWeaponGrade) + " with the Power of Imperial!";
						}
						else if (IItem.CheckIndex() == -1324) {
							Imp = 4331;
							msg = msg + " has enhanced " + GetStickName(GetWeaponGrade) + " with the Power of Imperial!";
						}
						else {
							Imp = 1923;
							msg = msg + " has enhanced " + GetBowName(GetWeaponGrade) + " with the Power of Imperial!";
						}
					}
					else {
						if (IItem.CheckIndex() == 1914) {
							Imp = 1921;
							msg = msg + " has enhanced " + GetSwordName(GetWeaponGrade, false) + " with the Power of Imperial!";
						}
						else if (IItem.CheckIndex() == -1322) {
							Imp = 4329;
							msg = msg + " has enhanced " + GetSwordName(impgrade, false) + " with the Power of Imperial!";
						}
						else if (IItem.CheckIndex() == -1323) {
							Imp = 4330;
							msg = msg + " has enhanced " + GetSwordName(impgrade, false) + " with the Power of Imperial!";
						}
						else {
							Imp = 1922;
							msg = msg + " has enhanced " + GetSwordName(impgrade, true) + " with the Power of Imperial!";

						}
					}
					break;
				case 0x50:
					if (*(DWORD *)(*(DWORD *)((int)Item + 40) + 96) == -1)
					{
						if (IItem.CheckIndex() == 7247)
							Imp = 7249;
						else if (IItem.CheckIndex() == 7248)
							Imp = 7250;
					}
					else if (*(DWORD *)(*(DWORD *)((int)Item + 40) + 96) == 3)
					{
						Imp = 3039;
					}
					else if (*(DWORD *)(*(DWORD *)((int)Item + 40) + 96))
					{
						if (*(DWORD *)(*(DWORD *)((int)Item + 40) + 96) == 1 && IItem.CheckIndex() == 3029)
							Imp = 3036;
						else if (*(DWORD *)(*(DWORD *)((int)Item + 40) + 96) == 1 && IItem.CheckIndex() == 3030)
							Imp = 3037;
						else if (*(DWORD *)(*(DWORD *)((int)Item + 40) + 96) == 1 && IItem.CheckIndex() == 3031)
							Imp = 3038;
						else
							Imp = 3035;
					}
					else {
						if (IItem.CheckIndex() == 3026)
							Imp = 3033;
						else
							Imp = 3034;
					}
					break;
				case 0x5A:
					if (*(DWORD *)(*(DWORD *)((int)Item + 40) + 96) == -1)
					{
						if (IItem.CheckIndex() == 7251)
							Imp = 7253;
						else if (IItem.CheckIndex() == 7252)
							Imp = 7254;
					}
					else if (*(DWORD *)(*(DWORD *)((int)Item + 40) + 96) == 3)
					{
						Imp = 3161;
					}
					else if (*(DWORD *)(*(DWORD *)((int)Item + 40) + 96))
					{
						if (*(DWORD *)(*(DWORD *)((int)Item + 40) + 96) == 1 && IItem.CheckIndex() == 3150)
							Imp = 3158;
						else if (*(DWORD *)(*(DWORD *)((int)Item + 40) + 96) == 1 && IItem.CheckIndex() == 3151)
							Imp = 3159;
						else if (*(DWORD *)(*(DWORD *)((int)Item + 40) + 96) == 1 && IItem.CheckIndex() == 3152)
							Imp = 3160;
						else
							Imp = 3157;
					}
					else {
						if (IItem.CheckIndex() == 3147)
							Imp = 3155;
						else
							Imp = 3156;
					}
					break;
				default:
					break;
				}


			}

			if (!Imp)
				return 0;

			if (*(DWORD *)((int)Item + 44))
				xMixPrefix = *(DWORD *)(*(DWORD *)((int)Item + 44) + 32);
			else
				xMixPrefix = 0;

			int DeleteCheck = (*(int(__thiscall **)(DWORD, void *, signed int, signed int))(*(DWORD*)Item + 120))((int)Item, IPlayer.GetOffset(), 9, -1);

			if (!DeleteCheck)
			{
				ImpItem = CItem::CreateItem(Imp, xMixPrefix, 1, -1);

				if (ImpItem)
				{
					CIOObject::AddRef(ImpItem);

					if (*(DWORD *)((int)Item + 48))
						*(DWORD *)(ImpItem + 48) = *(DWORD *)((int)Item + 48);

					if (*(DWORD *)((int)Item + 100))
						*(DWORD *)(ImpItem + 100) = *(DWORD *)((int)Item + 100);

					if (*(DWORD *)((int)Item + 104))
						*(DWORD *)(ImpItem + 104) = *(DWORD *)((int)Item + 104);

					if (*(DWORD *)((int)Item + 112))
						*(DWORD *)(ImpItem + 112) = *(DWORD *)((int)Item + 112);

					if (*(DWORD *)((int)Item + 124))
						*(DWORD *)(ImpItem + 124) = *(DWORD *)((int)Item + 124);

					if (*(DWORD *)((int)Item + 84))
						*(DWORD *)(ImpItem + 84) = *(DWORD *)((int)Item + 84);

					if (CPlayer::_InsertItem(IPlayer.GetOffset(), 27, ImpItem) != 1)
					{
						CConsole::Red("MixItem() insert item Null error [PID (%d)] ", IPlayer.GetPID());
						CBase::Delete((void *)ImpItem);
						CIOObject::Release((void *)ImpItem);
						return 0;
					}

					CIOObject::Release((void *)ImpItem);
					itemStat.Enter();
					GetItemStat[*(DWORD *)(ImpItem + 36)] = ItemStat;
					itemStat.Leave();

					CDBSocket::Write(90, "dd", ItemStat, *(DWORD *)(ImpItem + 36));
					CDBSocket::Write(87, "ddd", IPlayer.GetPID(), *(DWORD *)(ImpItem + 84), *(DWORD *)(ImpItem + 36));
					CDBSocket::Write(21, "dddbb", *(DWORD *)(ImpItem + 36), *(DWORD *)(ImpItem + 32), *(DWORD *)(ImpItem + 48), 8, 7);
					CDBSocket::Write(17, "ddbbb", *(DWORD *)(ImpItem + 36), *(DWORD *)(ImpItem + 32), 27, *(DWORD *)(ImpItem + 100), 0);
					CDBSocket::Write(17, "ddbbb", *(DWORD *)(ImpItem + 36), *(DWORD *)(ImpItem + 32), 28, *(DWORD *)(ImpItem + 104), 0);
					CDBSocket::Write(17, "ddbbb", *(DWORD *)(ImpItem + 36), *(DWORD *)(ImpItem + 32), 9, *(DWORD *)(ImpItem + 112), 0);
					CDBSocket::Write(28, "ddbb", *(DWORD *)(ImpItem + 36), *(DWORD *)(ImpItem + 32), 2, *(DWORD *)(ImpItem + 124));
					CItem::SendItemInfo((void*)ImpItem, (int)IPlayer.GetOffset(), 92);
					CPlayer::Write(IPlayer.GetOffset(), 0xFF, "ddddd", 242, 10, 0, 128, 255);

					if (!msg.empty() && IPlayer.IsValid()) {
						int textColor = NOTICECOLOR_YELLOW; // Default color
						int messageType = 2; // Default messageType
						RewardMessage reward;
						reward.message = msg;
						reward.textColor = textColor;
						reward.messageType = messageType;

						PlayerRewardNotice.push_back(reward);
						ToNoticeWebhook(msg.c_str());
					}

				}
			}
			else {
				return 0;
			}

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