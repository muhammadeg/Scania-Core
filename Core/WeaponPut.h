void __fastcall WeaponApplySpec(int Item, void *edx, int Player)
{
	IItem IItem((void*)Item);
	IChar IPlayer((void*)Player);

	if (IPlayer.IsOnline())
	{
		int atk = IPlayer.GetMaxPhyAttack();
		CItemWeapon::ApplySpec(Item, Player);

		int FirstDemonGongType = 0, SecondDemonGongType = 0, FirstDemonGongStat = 0, SecondDemonGongStat = 0, CustWeapon = 0;
		int Show = *(WORD *)(*(DWORD *)(Item + 40) + 64);
		if (!isItemCustomWeapon(Show)){
			IPlayer.Buff(BuffNames::WeaponWear, BuffNames::BuffTime, Show);
			IPlayer.Buff(BuffNames::WeaponUp, BuffNames::BuffTime, IItem.GetIID());
		}
		else {
			IPlayer.Buff(BuffNames::custWeap, BuffNames::BuffTime, Show);
			CustWeapon = 1;
		}
		int check = IPlayer.GetMaxPhyAttack() - (atk + (*(DWORD*)(Item + 100) * (2 * *(DWORD*)(Item + 100) + 7) / 9));
		IPlayer.UpdateBuff(BuffNames::ItemMixCheck + CustWeapon, BuffNames::BuffTime, check);

		if (EquipEffects.count(IItem.CheckIndex())){
			IPlayer.UpdateBuff(BuffNames::WEffectIID, BuffNames::BuffTime, IItem.GetIID());
			IPlayer.UpdateBuff(BuffNames::WeaponsEffects, BuffNames::BuffTime, IItem.CheckIndex());
		}

		int ItemStat = 0;
		itemStat.Enter();
		if (GetItemStat.count(IItem.GetIID()))
			ItemStat = GetItemStat.find(IItem.GetIID())->second;
		itemStat.Leave();

		if (ItemStat)
		{
			int QigongType = ItemStat % 100;
			int DemonGongStyle = (ItemStat % 100000000) / 10000000;

			if (DemonGongStyle) {
				int DemonGrade = (ItemStat % 10000000) / 1000000;
				int Grade = DemonGrade + 1;

				int minatk = 0, maxatk = 0, hp = 0;
				if (Grade == 1) {
					minatk = 6;
					maxatk = 10;
					hp = 90;
				}if (Grade == 2) {
					minatk = 12;
					maxatk = 20;
					hp = 100;
				}if (Grade == 3) {
					minatk = 18;
					maxatk = 30;
					hp = 110;
				}if (Grade == 4) {
					minatk = 24;
					maxatk = 40;
					hp = 130;
				}if (Grade == 5) {
					minatk = 30;
					maxatk = 50;
					hp = 170;
				}if (Grade == 6) {
					minatk = 36;
					maxatk = 60;
					hp = 190;
				}if (Grade == 7) {
					minatk = 42;
					maxatk = 70;
					hp = 210;
				}if (Grade == 8) {
					minatk = 48;
					maxatk = 80;
					hp = 250;
				}if (Grade == 9) {
					minatk = 54;
					maxatk = 90;
					hp = 290;
				}if (Grade == 10) {
					minatk = 60;
					maxatk = 100;
					hp = 350;
				}
				IPlayer.AddMinAttack(minatk);
				IPlayer.AddMaxAttack(maxatk);
				if (DemonGongStyle == 1)
					IPlayer.AddOTP(Grade);
				if (DemonGongStyle == 2)
					IPlayer.AddEva(Grade);
				if (DemonGongStyle == 3)
					IPlayer.IncreaseMaxHp(hp);

			}

			if (isItemCustomWeapon(IItem.CheckIndex())) {
				int AddingType = SuitStats.count(IItem.CheckIndex()) ? SuitStats.find(IItem.CheckIndex())->second.Type : 0;
				int Multiply = SuitStats.count(IItem.CheckIndex()) ? SuitStats.find(IItem.CheckIndex())->second.Multiply : 3;

				if (Multiply < 2)
					Multiply = 2;

				switch (AddingType) {
				case 0:
					IPlayer.AddHp(ItemStat >= 6 ? (((ItemStat - 5) * Multiply) + 10) : ItemStat * (Multiply - 1));
					break;
				case 1:
					IPlayer.AddStr(ItemStat >= 6 ? (((ItemStat - 5) * Multiply) + 10) : ItemStat * (Multiply - 1));
					break;
				case 2:
					IPlayer.AddHp(ItemStat >= 6 ? (((ItemStat - 5) * Multiply) + 10) : ItemStat * (Multiply - 1));
					break;
				case 3:
					IPlayer.AddInt(ItemStat >= 6 ? (((ItemStat - 5) * Multiply) + 10) : ItemStat * (Multiply - 1));
					break;
				case 4:
					IPlayer.AddWis(ItemStat >= 6 ? (((ItemStat - 5) * Multiply) + 10) : ItemStat * (Multiply - 1));
					break;
				case 5:
					IPlayer.AddAgi(ItemStat >= 6 ? (((ItemStat - 5) * Multiply) + 10) : ItemStat * (Multiply - 1));
					break;
				default:
					IPlayer.AddHp(ItemStat >= 6 ? (((ItemStat - 5) * Multiply) + 10) : ItemStat * (Multiply - 1));
					break;
				}
			}

			if (QigongType)
			{
				IPlayer.AddMaxAttack(check*QigongWeapon[QigongType - 1][0] / 100);
				IPlayer.AddMinAttack(check*QigongWeapon[QigongType - 1][1] / 100);
				IPlayer.IncreaseMaxHp(QigongWeapon[QigongType - 1][2]);
				IPlayer.IncreaseMaxMp(QigongWeapon[QigongType - 1][3]);

				if (IItem.GetType() == -1 || (IItem.GetType() == -3 && IPlayer.GetClass() == 4))
					IPlayer.AddEva(QigongWeapon[QigongType - 1][4]);
				else
					IPlayer.AddOTP(QigongWeapon[QigongType - 1][4]);

				int Type = QigongWeapon[QigongType - 1][5];
				int Stat = QigongWeapon[QigongType - 1][6];

				if (Type == 0)
					IPlayer.AddStr(Stat);
				else if (Type == 1)
					IPlayer.AddHp(Stat);
				else if (Type == 2)
					IPlayer.AddInt(Stat);
				else if (Type == 3)
					IPlayer.AddWis(Stat);
				else if (Type == 4)
					IPlayer.AddAgi(Stat);
			}
		}

		if (IItem.GetSetGem() == 240 && IItem.GetInfo() & 1)
		{
			IPlayer.AddMaxAttack(check * 17 / 100);
			IPlayer.AddMinAttack(check * 17 / 100);
			IPlayer.AddAgi(8);

			if (IItem.GetType() == -1 || (IItem.GetType() == -3 && IPlayer.GetClass() == 4))
				IPlayer.AddEva(18);
			else
				IPlayer.AddOTP(18);

			IPlayer.IncreaseMaxHp(250);
			IPlayer.IncreaseMaxMp(200);
		}
		else if (IItem.GetSetGem() == 239 && IItem.GetInfo() & 1)
		{
			IPlayer.AddMaxAttack(check * 17 / 100);
			IPlayer.AddMinAttack(check * 17 / 100);
			IPlayer.AddWis(8);

			if (IItem.GetType() == -1 || (IItem.GetType() == -3 && IPlayer.GetClass() == 4))
				IPlayer.AddEva(18);
			else
				IPlayer.AddOTP(18);

			IPlayer.IncreaseMaxHp(250);
			IPlayer.IncreaseMaxMp(200);
		}
		else if (IItem.GetSetGem() == 238 && IItem.GetInfo() & 1)
		{
			IPlayer.AddMaxAttack(check * 17 / 100);
			IPlayer.AddMinAttack(check * 17 / 100);
			IPlayer.AddInt(8);

			if (IItem.GetType() == -1 || (IItem.GetType() == -3 && IPlayer.GetClass() == 4))
				IPlayer.AddEva(18);
			else
				IPlayer.AddOTP(18);

			IPlayer.IncreaseMaxHp(250);
			IPlayer.IncreaseMaxMp(200);
		}
		else if (IItem.GetSetGem() == 237 && IItem.GetInfo() & 1)
		{
			IPlayer.AddMaxAttack(check * 17 / 100);
			IPlayer.AddMinAttack(check * 17 / 100);
			IPlayer.AddHp(8);

			if (IItem.GetType() == -1 || (IItem.GetType() == -3 && IPlayer.GetClass() == 4))
				IPlayer.AddEva(18);
			else
				IPlayer.AddOTP(18);

			IPlayer.IncreaseMaxHp(250);
			IPlayer.IncreaseMaxMp(200);
		}
		else if (IItem.GetSetGem() == 236 && IItem.GetInfo() & 1)
		{
			IPlayer.AddMaxAttack(check * 17 / 100);
			IPlayer.AddMinAttack(check * 17 / 100);
			IPlayer.AddStr(8);

			if (IItem.GetType() == -1 || (IItem.GetType() == -3 && IPlayer.GetClass() == 4))
				IPlayer.AddEva(18);
			else
				IPlayer.AddOTP(18);

			IPlayer.IncreaseMaxHp(250);
			IPlayer.IncreaseMaxMp(200);
		}
		else if (IItem.GetSetGem() == 235 && IItem.GetInfo() & 1)
		{
			IPlayer.AddMaxAttack(check * 14 / 100);
			IPlayer.AddMinAttack(check * 14 / 100);
			IPlayer.AddAgi(5);

			if (IItem.GetType() == -1 || (IItem.GetType() == -3 && IPlayer.GetClass() == 4))
				IPlayer.AddEva(15);
			else
				IPlayer.AddOTP(15);

			IPlayer.IncreaseMaxHp(200);
			IPlayer.IncreaseMaxMp(150);
		}
		else if (IItem.GetSetGem() == 234 && IItem.GetInfo() & 1)
		{
			IPlayer.AddMaxAttack(check * 14 / 100);
			IPlayer.AddMinAttack(check * 14 / 100);
			IPlayer.AddWis(5);

			if (IItem.GetType() == -1 || (IItem.GetType() == -3 && IPlayer.GetClass() == 4))
				IPlayer.AddEva(15);
			else
				IPlayer.AddOTP(15);

			IPlayer.IncreaseMaxHp(200);
			IPlayer.IncreaseMaxMp(150);
		}
		else if (IItem.GetSetGem() == 233 && IItem.GetInfo() & 1)
		{
			IPlayer.AddMaxAttack(check * 14 / 100);
			IPlayer.AddMinAttack(check * 14 / 100);
			IPlayer.AddInt(5);

			if (IItem.GetType() == -1 || (IItem.GetType() == -3 && IPlayer.GetClass() == 4))
				IPlayer.AddEva(15);
			else
				IPlayer.AddOTP(15);

			IPlayer.IncreaseMaxHp(200);
			IPlayer.IncreaseMaxMp(150);
		}
		else if (IItem.GetSetGem() == 232 && IItem.GetInfo() & 1)
		{
			IPlayer.AddMaxAttack(check * 14 / 100);
			IPlayer.AddMinAttack(check * 14 / 100);
			IPlayer.AddHp(5);

			if (IItem.GetType() == -1 || (IItem.GetType() == -3 && IPlayer.GetClass() == 4))
				IPlayer.AddEva(15);
			else
				IPlayer.AddOTP(15);

			IPlayer.IncreaseMaxHp(200);
			IPlayer.IncreaseMaxMp(150);
		}
		else if (IItem.GetSetGem() == 231 && IItem.GetInfo() & 1)
		{
			IPlayer.AddMaxAttack(check * 14 / 100);
			IPlayer.AddMinAttack(check * 14 / 100);
			IPlayer.AddStr(5);

			if (IItem.GetType() == -1 || (IItem.GetType() == -3 && IPlayer.GetClass() == 4))
				IPlayer.AddEva(15);
			else
				IPlayer.AddOTP(15);

			IPlayer.IncreaseMaxHp(200);
			IPlayer.IncreaseMaxMp(150);
		}
		else if (IItem.GetSetGem() == 230 && IItem.GetInfo() & 1)
		{
			IPlayer.AddMaxAttack(check * 12 / 100);
			IPlayer.AddMinAttack(check * 12 / 100);
			IPlayer.AddAgi(3);

			if (IItem.GetType() == -1 || (IItem.GetType() == -3 && IPlayer.GetClass() == 4))
				IPlayer.AddEva(12);
			else
				IPlayer.AddOTP(12);

			IPlayer.IncreaseMaxHp(130);
			IPlayer.IncreaseMaxMp(110);
		}
		else if (IItem.GetSetGem() == 229 && IItem.GetInfo() & 1)
		{
			IPlayer.AddMaxAttack(check * 12 / 100);
			IPlayer.AddMinAttack(check * 12 / 100);
			IPlayer.AddWis(3);

			if (IItem.GetType() == -1 || (IItem.GetType() == -3 && IPlayer.GetClass() == 4))
				IPlayer.AddEva(12);
			else
				IPlayer.AddOTP(12);

			IPlayer.IncreaseMaxHp(130);
			IPlayer.IncreaseMaxMp(110);
		}
		else if (IItem.GetSetGem() == 228 && IItem.GetInfo() & 1)
		{
			IPlayer.AddMaxAttack(check * 12 / 100);
			IPlayer.AddMinAttack(check * 12 / 100);
			IPlayer.AddInt(3);

			if (IItem.GetType() == -1 || (IItem.GetType() == -3 && IPlayer.GetClass() == 4))
				IPlayer.AddEva(12);
			else
				IPlayer.AddOTP(12);

			IPlayer.IncreaseMaxHp(130);
			IPlayer.IncreaseMaxMp(110);
		}
		else if (IItem.GetSetGem() == 227 && IItem.GetInfo() & 1)
		{
			IPlayer.AddMaxAttack(check * 12 / 100);
			IPlayer.AddMinAttack(check * 12 / 100);
			IPlayer.AddHp(3);

			if (IItem.GetType() == -1 || (IItem.GetType() == -3 && IPlayer.GetClass() == 4))
				IPlayer.AddEva(12);
			else
				IPlayer.AddOTP(12);

			IPlayer.IncreaseMaxHp(130);
			IPlayer.IncreaseMaxMp(110);
		}
		else if (IItem.GetSetGem() == 226 && IItem.GetInfo() & 1)
		{
			IPlayer.AddMaxAttack(check * 12 / 100);
			IPlayer.AddMinAttack(check * 12 / 100);
			IPlayer.AddStr(3);

			if (IItem.GetType() == -1 || (IItem.GetType() == -3 && IPlayer.GetClass() == 4))
				IPlayer.AddEva(12);
			else
				IPlayer.AddOTP(12);

			IPlayer.IncreaseMaxHp(130);
			IPlayer.IncreaseMaxMp(110);
		}
		else if (IItem.GetSetGem() == 225 && IItem.GetInfo() & 1)
		{
			IPlayer.AddMaxAttack(check * 10 / 100);
			IPlayer.AddMinAttack(check * 10 / 100);
			IPlayer.AddAgi(3);

			if (IItem.GetType() == -1 || (IItem.GetType() == -3 && IPlayer.GetClass() == 4))
				IPlayer.AddEva(10);
			else
				IPlayer.AddOTP(10);

			IPlayer.IncreaseMaxHp(110);
			IPlayer.IncreaseMaxMp(90);
		}
		else if (IItem.GetSetGem() == 224 && IItem.GetInfo() & 1)
		{
			IPlayer.AddMaxAttack(check * 10 / 100);
			IPlayer.AddMinAttack(check * 10 / 100);
			IPlayer.AddWis(3);

			if (IItem.GetType() == -1 || (IItem.GetType() == -3 && IPlayer.GetClass() == 4))
				IPlayer.AddEva(10);
			else
				IPlayer.AddOTP(10);

			IPlayer.IncreaseMaxHp(110);
			IPlayer.IncreaseMaxMp(90);
		}
		else if (IItem.GetSetGem() == 223 && IItem.GetInfo() & 1)
		{
			IPlayer.AddMaxAttack(check * 10 / 100);
			IPlayer.AddMinAttack(check * 10 / 100);
			IPlayer.AddInt(3);

			if (IItem.GetType() == -1 || (IItem.GetType() == -3 && IPlayer.GetClass() == 4))
				IPlayer.AddEva(10);
			else
				IPlayer.AddOTP(10);

			IPlayer.IncreaseMaxHp(110);
			IPlayer.IncreaseMaxMp(90);
		}
		else if (IItem.GetSetGem() == 222 && IItem.GetInfo() & 1)
		{
			IPlayer.AddMaxAttack(check * 10 / 100);
			IPlayer.AddMinAttack(check * 10 / 100);
			IPlayer.AddHp(3);

			if (IItem.GetType() == -1 || (IItem.GetType() == -3 && IPlayer.GetClass() == 4))
				IPlayer.AddEva(10);
			else
				IPlayer.AddOTP(10);

			IPlayer.IncreaseMaxHp(110);
			IPlayer.IncreaseMaxMp(90);
		}
		else if (IItem.GetSetGem() == 221 && IItem.GetInfo() & 1)
		{
			IPlayer.AddMaxAttack(check * 10 / 100);
			IPlayer.AddMinAttack(check * 10 / 100);
			IPlayer.AddStr(3);

			if (IItem.GetType() == -1 || (IItem.GetType() == -3 && IPlayer.GetClass() == 4))
				IPlayer.AddEva(10);
			else
				IPlayer.AddOTP(10);

			IPlayer.IncreaseMaxHp(110);
			IPlayer.IncreaseMaxMp(90);
		}
		else if (IItem.GetSetGem() == 220 && IItem.GetInfo() & 1)
		{
			IPlayer.AddMaxAttack(check * 8 / 100);
			IPlayer.AddMinAttack(check * 8 / 100);
			IPlayer.AddAgi(2);

			if (IItem.GetType() == -1 || (IItem.GetType() == -3 && IPlayer.GetClass() == 4))
				IPlayer.AddEva(8);
			else
				IPlayer.AddOTP(8);

			IPlayer.IncreaseMaxHp(90);
			IPlayer.IncreaseMaxMp(70);
		}
		else if (IItem.GetSetGem() == 219 && IItem.GetInfo() & 1)
		{
			IPlayer.AddMaxAttack(check * 8 / 100);
			IPlayer.AddMinAttack(check * 8 / 100);
			IPlayer.AddWis(2);

			if (IItem.GetType() == -1 || (IItem.GetType() == -3 && IPlayer.GetClass() == 4))
				IPlayer.AddEva(8);
			else
				IPlayer.AddOTP(8);

			IPlayer.IncreaseMaxHp(90);
			IPlayer.IncreaseMaxMp(70);
		}
		else if (IItem.GetSetGem() == 218 && IItem.GetInfo() & 1)
		{
			IPlayer.AddMaxAttack(check * 8 / 100);
			IPlayer.AddMinAttack(check * 8 / 100);
			IPlayer.AddInt(2);

			if (IItem.GetType() == -1 || (IItem.GetType() == -3 && IPlayer.GetClass() == 4))
				IPlayer.AddEva(8);
			else
				IPlayer.AddOTP(8);

			IPlayer.IncreaseMaxHp(90);
			IPlayer.IncreaseMaxMp(70);
		}
		else if (IItem.GetSetGem() == 217 && IItem.GetInfo() & 1)
		{
			IPlayer.AddMaxAttack(check * 8 / 100);
			IPlayer.AddMinAttack(check * 8 / 100);
			IPlayer.AddHp(2);

			if (IItem.GetType() == -1 || (IItem.GetType() == -3 && IPlayer.GetClass() == 4))
				IPlayer.AddEva(8);
			else
				IPlayer.AddOTP(8);

			IPlayer.IncreaseMaxHp(90);
			IPlayer.IncreaseMaxMp(70);
		}
		else if (IItem.GetSetGem() == 216 && IItem.GetInfo() & 1)
		{
			IPlayer.AddMaxAttack(check * 8 / 100);
			IPlayer.AddMinAttack(check * 8 / 100);
			IPlayer.AddStr(2);

			if (IItem.GetType() == -1 || (IItem.GetType() == -3 && IPlayer.GetClass() == 4))
				IPlayer.AddEva(8);
			else
				IPlayer.AddOTP(8);

			IPlayer.IncreaseMaxHp(90);
			IPlayer.IncreaseMaxMp(70);
		}
		else if (IItem.GetSetGem() == 215 && IItem.GetInfo() & 1)
		{
			IPlayer.AddMaxAttack(check * 6 / 100);
			IPlayer.AddMinAttack(check * 6 / 100);
			IPlayer.AddAgi(2);

			if (IItem.GetType() == -1 || (IItem.GetType() == -3 && IPlayer.GetClass() == 4))
				IPlayer.AddEva(6);
			else
				IPlayer.AddOTP(6);

			IPlayer.IncreaseMaxHp(70);
			IPlayer.IncreaseMaxMp(50);
		}
		else if (IItem.GetSetGem() == 214 && IItem.GetInfo() & 1)
		{
			IPlayer.AddMaxAttack(check * 6 / 100);
			IPlayer.AddMinAttack(check * 6 / 100);
			IPlayer.AddWis(2);

			if (IItem.GetType() == -1 || (IItem.GetType() == -3 && IPlayer.GetClass() == 4))
				IPlayer.AddEva(6);
			else
				IPlayer.AddOTP(6);

			IPlayer.IncreaseMaxHp(70);
			IPlayer.IncreaseMaxMp(50);
		}
		else if (IItem.GetSetGem() == 213 && IItem.GetInfo() & 1)
		{
			IPlayer.AddMaxAttack(check * 6 / 100);
			IPlayer.AddMinAttack(check * 6 / 100);
			IPlayer.AddInt(2);

			if (IItem.GetType() == -1 || (IItem.GetType() == -3 && IPlayer.GetClass() == 4))
				IPlayer.AddEva(6);
			else
				IPlayer.AddOTP(6);

			IPlayer.IncreaseMaxHp(70);
			IPlayer.IncreaseMaxMp(50);
		}
		else if (IItem.GetSetGem() == 212 && IItem.GetInfo() & 1)
		{
			IPlayer.AddMaxAttack(check * 6 / 100);
			IPlayer.AddMinAttack(check * 6 / 100);
			IPlayer.AddHp(2);

			if (IItem.GetType() == -1 || (IItem.GetType() == -3 && IPlayer.GetClass() == 4))
				IPlayer.AddEva(6);
			else
				IPlayer.AddOTP(6);

			IPlayer.IncreaseMaxHp(70);
			IPlayer.IncreaseMaxMp(50);
		}
		else if (IItem.GetSetGem() == 211 && IItem.GetInfo() & 1)
		{
			IPlayer.AddMaxAttack(check * 6 / 100);
			IPlayer.AddMinAttack(check * 6 / 100);
			IPlayer.AddStr(2);

			if (IItem.GetType() == -1 || (IItem.GetType() == -3 && IPlayer.GetClass() == 4))
				IPlayer.AddEva(6);
			else
				IPlayer.AddOTP(6);

			IPlayer.IncreaseMaxHp(70);
			IPlayer.IncreaseMaxMp(50);
		}
		else if (IItem.GetSetGem() == 210 && IItem.GetInfo() & 1)
		{
			IPlayer.AddMaxAttack(check * 4 / 100);
			IPlayer.AddMinAttack(check * 4 / 100);
			IPlayer.AddAgi(1);

			if (IItem.GetType() == -1 || (IItem.GetType() == -3 && IPlayer.GetClass() == 4))
				IPlayer.AddEva(4);
			else
				IPlayer.AddOTP(4);

			IPlayer.IncreaseMaxHp(50);
			IPlayer.IncreaseMaxMp(30);
		}
		else if (IItem.GetSetGem() == 209 && IItem.GetInfo() & 1)
		{
			IPlayer.AddMaxAttack(check * 4 / 100);
			IPlayer.AddMinAttack(check * 4 / 100);
			IPlayer.AddWis(1);

			if (IItem.GetType() == -1 || (IItem.GetType() == -3 && IPlayer.GetClass() == 4))
				IPlayer.AddEva(4);
			else
				IPlayer.AddOTP(4);

			IPlayer.IncreaseMaxHp(50);
			IPlayer.IncreaseMaxMp(30);
		}
		else if (IItem.GetSetGem() == 208 && IItem.GetInfo() & 1)
		{
			IPlayer.AddMaxAttack(check * 4 / 100);
			IPlayer.AddMinAttack(check * 4 / 100);
			IPlayer.AddInt(1);

			if (IItem.GetType() == -1 || (IItem.GetType() == -3 && IPlayer.GetClass() == 4))
				IPlayer.AddEva(4);
			else
				IPlayer.AddOTP(4);

			IPlayer.IncreaseMaxHp(50);
			IPlayer.IncreaseMaxMp(30);
		}
		else if (IItem.GetSetGem() == 207 && IItem.GetInfo() & 1)
		{
			IPlayer.AddMaxAttack(check * 4 / 100);
			IPlayer.AddMinAttack(check * 4 / 100);
			IPlayer.AddHp(1);

			if (IItem.GetType() == -1 || (IItem.GetType() == -3 && IPlayer.GetClass() == 4))
				IPlayer.AddEva(4);
			else
				IPlayer.AddOTP(4);

			IPlayer.IncreaseMaxHp(50);
			IPlayer.IncreaseMaxMp(30);
		}
		else if (IItem.GetSetGem() == 206 && IItem.GetInfo() & 1)
		{
			IPlayer.AddMaxAttack(check * 4 / 100);
			IPlayer.AddMinAttack(check * 4 / 100);
			IPlayer.AddStr(1);

			if (IItem.GetType() == -1 || (IItem.GetType() == -3 && IPlayer.GetClass() == 4))
				IPlayer.AddEva(4);
			else
				IPlayer.AddOTP(4);

			IPlayer.IncreaseMaxHp(50);
			IPlayer.IncreaseMaxMp(30);
		}
		else if (IItem.GetSetGem() == 205 && IItem.GetInfo() & 1)
		{
			IPlayer.AddMaxAttack(check * 2 / 100);
			IPlayer.AddMinAttack(check * 2 / 100);
			IPlayer.AddAgi(1);

			if (IItem.GetType() == -1 || (IItem.GetType() == -3 && IPlayer.GetClass() == 4))
				IPlayer.AddEva(2);
			else
				IPlayer.AddOTP(2);

			IPlayer.IncreaseMaxHp(30);
			IPlayer.IncreaseMaxMp(10);
		}
		else if (IItem.GetSetGem() == 204 && IItem.GetInfo() & 1)
		{
			IPlayer.AddMaxAttack(check * 2 / 100);
			IPlayer.AddMinAttack(check * 2 / 100);
			IPlayer.AddWis(1);

			if (IItem.GetType() == -1 || (IItem.GetType() == -3 && IPlayer.GetClass() == 4))
				IPlayer.AddEva(2);
			else
				IPlayer.AddOTP(2);

			IPlayer.IncreaseMaxHp(30);
			IPlayer.IncreaseMaxMp(10);
		}
		else if (IItem.GetSetGem() == 203 && IItem.GetInfo() & 1)
		{
			IPlayer.AddMaxAttack(check * 2 / 100);
			IPlayer.AddMinAttack(check * 2 / 100);
			IPlayer.AddInt(1);

			if (IItem.GetType() == -1 || (IItem.GetType() == -3 && IPlayer.GetClass() == 4))
				IPlayer.AddEva(2);
			else
				IPlayer.AddOTP(2);

			IPlayer.IncreaseMaxHp(30);
			IPlayer.IncreaseMaxMp(10);
		}
		else if (IItem.GetSetGem() == 202 && IItem.GetInfo() & 1)
		{
			IPlayer.AddMaxAttack(check * 2 / 100);
			IPlayer.AddMinAttack(check * 2 / 100);
			IPlayer.AddHp(1);

			if (IItem.GetType() == -1 || (IItem.GetType() == -3 && IPlayer.GetClass() == 4))
				IPlayer.AddEva(2);
			else
				IPlayer.AddOTP(2);

			IPlayer.IncreaseMaxHp(30);
			IPlayer.IncreaseMaxMp(10);
		}
		else if (IItem.GetSetGem() == 201 && IItem.GetInfo() & 1)
		{
			IPlayer.AddMaxAttack(check * 2 / 100);
			IPlayer.AddMinAttack(check * 2 / 100);
			IPlayer.AddStr(1);

			if (IItem.GetType() == -1 || (IItem.GetType() == -3 && IPlayer.GetClass() == 4))
				IPlayer.AddEva(2);
			else
				IPlayer.AddOTP(2);

			IPlayer.IncreaseMaxHp(30);
			IPlayer.IncreaseMaxMp(10);
		}
	}

	if (PVEDamagePimp.count(IItem.PrefixID())) {
		int Value = PVEDamagePimp.find(IItem.PrefixID())->second;
		IPlayer.SystemMessage("Your PVE damage is increased by :" + Int2String(Value) + "%.", TEXTCOLOR_GREEN);
		IPlayer.UpdateBuff(BuffNames::PVEPimp, BuffNames::BuffTime, Value);
	}

	if (PVPDamagePimp.count(IItem.PrefixID())) {
		int Value = PVPDamagePimp.find(IItem.PrefixID())->second;
		IPlayer.SystemMessage("Your PVP damage is increased by :" + Int2String(Value) + "%.", TEXTCOLOR_GREEN);
		IPlayer.UpdateBuff(BuffNames::PVPPimp, BuffNames::BuffTime, Value);
	}
}

void __fastcall WeaponPutOff(void *Item, void *edx, int Player)
{
	IChar IPlayer((void*)Player);
	IItem IItem((void*)Item);

	int atk = IPlayer.GetMaxPhyAttack();
	int Old = *(DWORD *)(Player + 156);

	CItemWeapon::PutOff(Item, Player);
	int CustWeapon = 0;

	if (CItem::IsState((int)Item, 1))
		return;

	if (IPlayer.GetBuffValue(BuffNames::WeaponWear) && IPlayer.GetBuffValue(BuffNames::custWeap)) {
		IPlayer.CancelBuff(2034);
		CPlayer::AddWState(Player, 0);
	}

	if (isItemCustomWeapon(IItem.CheckIndex())) {
		*(DWORD *)(Player + 156) = Old;

		if (CostWeaponsEffects.count(IItem.CheckIndex())) {
			if (IPlayer.GetClass() == 3)
				IPlayer.RemoveFxBone(IPlayer.CostEffect(CostWeaponsEffects.find(IItem.CheckIndex())->second));
			IPlayer.RemoveFxBone(IPlayer.CostEffect(CostWeaponsEffects.find(IItem.CheckIndex())->second));
		}

		CustWeapon = 1;
		IPlayer.CancelBuff(BuffNames::custWeap);
	}
	else {
		int custWep = IPlayer.GetBuffValue(BuffNames::custWeap);

		if (custWep && CostWeaponsEffects.count(custWep)) {
			if (IPlayer.GetClass() == 3)
				IPlayer.RemoveFxBone(IPlayer.CostEffect(CostWeaponsEffects.find(custWep)->second));
			IPlayer.RemoveFxBone(IPlayer.CostEffect(CostWeaponsEffects.find(custWep)->second));
		}

		IPlayer.CancelBuff(BuffNames::WeaponWear);
		IPlayer.CancelBuff(BuffNames::WeaponUp);
	}

	if (EquipEffects.count(IItem.CheckIndex())){
		int ItemXX = IPlayer.GetBuffValue(BuffNames::WeaponsEffects);
		int ItemIID = IPlayer.GetBuffValue(BuffNames::WEffectIID);
		if (ItemIID) {
			std::string effectName = EquipEffects.find(ItemXX)->second.Effect;
			IPlayer.RemoveFxBone(effectName.c_str());
		}
		IPlayer.CancelBuff(BuffNames::WeaponsEffects);
		IPlayer.CancelBuff(BuffNames::WEffectIID);
	}

	int check = atk - (IPlayer.GetMaxPhyAttack() + (*(DWORD*)((int)Item + 100) * (2 * *(DWORD*)((int)Item + 100) + 7) / 9));

	if (IPlayer.GetBuffValue(BuffNames::ItemMixCheck + CustWeapon)) {
		check = IPlayer.GetBuffValue(BuffNames::ItemMixCheck + CustWeapon);
		IPlayer.UpdateBuff(BuffNames::ItemMixCheck + CustWeapon, BuffNames::BuffTime, 0);
	}

	int ItemStat = 0;
	itemStat.Enter();
	if (GetItemStat.count(IItem.GetIID()))
		ItemStat = GetItemStat.find(IItem.GetIID())->second;
	itemStat.Leave();

	if (PVEDamagePimp.count(IItem.PrefixID()))
		IPlayer.UpdateBuff(BuffNames::PVEPimp, BuffNames::BuffTime, 0);

	if (PVPDamagePimp.count(IItem.PrefixID()))
		IPlayer.UpdateBuff(BuffNames::PVPPimp, BuffNames::BuffTime, 0);

	if (ItemStat)
	{
		int QigongType = ItemStat % 100;
		int DemonGongStyle = (ItemStat % 100000000) / 10000000;

		if (DemonGongStyle) {
			int DemonGrade = (ItemStat % 10000000) / 1000000;
			int Grade = DemonGrade + 1;

			int minatk = 0, maxatk = 0, hp = 0;
			if (Grade == 1) {
				minatk = 6;
				maxatk = 10;
				hp = 90;
			}if (Grade == 2) {
				minatk = 12;
				maxatk = 20;
				hp = 100;
			}if (Grade == 3) {
				minatk = 18;
				maxatk = 30;
				hp = 110;
			}if (Grade == 4) {
				minatk = 24;
				maxatk = 40;
				hp = 130;
			}if (Grade == 5) {
				minatk = 30;
				maxatk = 50;
				hp = 170;
			}if (Grade == 6) {
				minatk = 36;
				maxatk = 60;
				hp = 190;
			}if (Grade == 7) {
				minatk = 42;
				maxatk = 70;
				hp = 210;
			}if (Grade == 8) {
				minatk = 48;
				maxatk = 80;
				hp = 250;
			}if (Grade == 9) {
				minatk = 54;
				maxatk = 90;
				hp = 290;
			}if (Grade == 10) {
				minatk = 60;
				maxatk = 100;
				hp = 350;
			}
			IPlayer.RemoveMinAttack(minatk);
			IPlayer.RemoveMaxAttack(maxatk);
			if (DemonGongStyle == 1)
				IPlayer.RemoveOTP(Grade);
			if (DemonGongStyle == 2)
				IPlayer.RemoveEva(Grade);
			if (DemonGongStyle == 3)
				IPlayer.DecreaseMaxHp(hp);

		}

		if (isItemCustomWeapon(IItem.CheckIndex())) {
			int AddingType = SuitStats.count(IItem.CheckIndex()) ? SuitStats.find(IItem.CheckIndex())->second.Type : 0;
			int Multiply = SuitStats.count(IItem.CheckIndex()) ? SuitStats.find(IItem.CheckIndex())->second.Multiply : 3;

			if (Multiply < 2)
				Multiply = 2;

			switch (AddingType) {
			case 0:
				IPlayer.RemoveHp(ItemStat >= 6 ? (((ItemStat - 5) * Multiply) + 10) : ItemStat * (Multiply - 1));
				break;
			case 1:
				IPlayer.RemoveStr(ItemStat >= 6 ? (((ItemStat - 5) * Multiply) + 10) : ItemStat * (Multiply - 1));
				break;
			case 2:
				IPlayer.RemoveHp(ItemStat >= 6 ? (((ItemStat - 5) * Multiply) + 10) : ItemStat * (Multiply - 1));
				break;
			case 3:
				IPlayer.RemoveInt(ItemStat >= 6 ? (((ItemStat - 5) * Multiply) + 10) : ItemStat * (Multiply - 1));
				break;
			case 4:
				IPlayer.RemoveWis(ItemStat >= 6 ? (((ItemStat - 5) * Multiply) + 10) : ItemStat * (Multiply - 1));
				break;
			case 5:
				IPlayer.RemoveAgi(ItemStat >= 6 ? (((ItemStat - 5) * Multiply) + 10) : ItemStat * (Multiply - 1));
				break;
			default:
				IPlayer.RemoveHp(ItemStat >= 6 ? (((ItemStat - 5) * Multiply) + 10) : ItemStat * (Multiply - 1));
				break;
			}
		}

		if (QigongType)
		{
			IPlayer.RemoveMaxAttack(check*QigongWeapon[QigongType - 1][0] / 100);
			IPlayer.RemoveMinAttack(check*QigongWeapon[QigongType - 1][1] / 100);
			IPlayer.DecreaseMaxHp(QigongWeapon[QigongType - 1][2]);
			IPlayer.DecreaseMaxMp(QigongWeapon[QigongType - 1][3]);

			if (IItem.GetType() == -1 || (IItem.GetType() == -3 && IPlayer.GetClass() == 4))
				IPlayer.RemoveEva(QigongWeapon[QigongType - 1][4]);
			else
				IPlayer.RemoveOTP(QigongWeapon[QigongType - 1][4]);

			int Type = QigongWeapon[QigongType - 1][5];
			int Stat = QigongWeapon[QigongType - 1][6];

			if (Type == 0)
				IPlayer.RemoveStr(Stat);
			else if (Type == 1)
				IPlayer.RemoveHp(Stat);
			else if (Type == 2)
				IPlayer.RemoveInt(Stat);
			else if (Type == 3)
				IPlayer.RemoveWis(Stat);
			else if (Type == 4)
				IPlayer.RemoveAgi(Stat);
		}
	}

	if (IItem.GetSetGem() == 240)
	{
		IPlayer.RemoveMaxAttack(check * 17 / 100);
		IPlayer.RemoveMinAttack(check * 17 / 100);
		IPlayer.RemoveAgi(8);

		if (IItem.GetType() == -1 || (IItem.GetType() == -3 && IPlayer.GetClass() == 4))
			IPlayer.RemoveEva(18);
		else
			IPlayer.RemoveOTP(18);

		IPlayer.DecreaseMaxHp(250);
		IPlayer.DecreaseMaxMp(200);
	}
	else if (IItem.GetSetGem() == 239)
	{
		IPlayer.RemoveMaxAttack(check * 17 / 100);
		IPlayer.RemoveMinAttack(check * 17 / 100);
		IPlayer.RemoveWis(8);

		if (IItem.GetType() == -1 || (IItem.GetType() == -3 && IPlayer.GetClass() == 4))
			IPlayer.RemoveEva(18);
		else
			IPlayer.RemoveOTP(18);

		IPlayer.DecreaseMaxHp(250);
		IPlayer.DecreaseMaxMp(200);
	}
	else if (IItem.GetSetGem() == 238)
	{
		IPlayer.RemoveMaxAttack(check * 17 / 100);
		IPlayer.RemoveMinAttack(check * 17 / 100);
		IPlayer.RemoveInt(8);

		if (IItem.GetType() == -1 || (IItem.GetType() == -3 && IPlayer.GetClass() == 4))
			IPlayer.RemoveEva(18);
		else
			IPlayer.RemoveOTP(18);

		IPlayer.DecreaseMaxHp(250);
		IPlayer.DecreaseMaxMp(200);
	}
	else if (IItem.GetSetGem() == 237)
	{
		IPlayer.RemoveMaxAttack(check * 17 / 100);
		IPlayer.RemoveMinAttack(check * 17 / 100);
		IPlayer.RemoveHp(8);

		if (IItem.GetType() == -1 || (IItem.GetType() == -3 && IPlayer.GetClass() == 4))
			IPlayer.RemoveEva(18);
		else
			IPlayer.RemoveOTP(18);

		IPlayer.DecreaseMaxHp(250);
		IPlayer.DecreaseMaxMp(200);
	}
	else if (IItem.GetSetGem() == 236)
	{
		IPlayer.RemoveMaxAttack(check * 17 / 100);
		IPlayer.RemoveMinAttack(check * 17 / 100);
		IPlayer.RemoveStr(8);

		if (IItem.GetType() == -1 || (IItem.GetType() == -3 && IPlayer.GetClass() == 4))
			IPlayer.RemoveEva(18);
		else
			IPlayer.RemoveOTP(18);

		IPlayer.DecreaseMaxHp(250);
		IPlayer.DecreaseMaxMp(200);
	}
	else if (IItem.GetSetGem() == 235)
	{
		IPlayer.RemoveMaxAttack(check * 14 / 100);
		IPlayer.RemoveMinAttack(check * 14 / 100);
		IPlayer.RemoveAgi(5);

		if (IItem.GetType() == -1 || (IItem.GetType() == -3 && IPlayer.GetClass() == 4))
			IPlayer.RemoveEva(15);
		else
			IPlayer.RemoveOTP(15);

		IPlayer.DecreaseMaxHp(200);
		IPlayer.DecreaseMaxMp(150);
	}
	else if (IItem.GetSetGem() == 234)
	{
		IPlayer.RemoveMaxAttack(check * 14 / 100);
		IPlayer.RemoveMinAttack(check * 14 / 100);
		IPlayer.RemoveWis(5);

		if (IItem.GetType() == -1 || (IItem.GetType() == -3 && IPlayer.GetClass() == 4))
			IPlayer.RemoveEva(15);
		else
			IPlayer.RemoveOTP(15);

		IPlayer.DecreaseMaxHp(200);
		IPlayer.DecreaseMaxMp(150);
	}
	else if (IItem.GetSetGem() == 233)
	{
		IPlayer.RemoveMaxAttack(check * 14 / 100);
		IPlayer.RemoveMinAttack(check * 14 / 100);
		IPlayer.RemoveInt(5);

		if (IItem.GetType() == -1 || (IItem.GetType() == -3 && IPlayer.GetClass() == 4))
			IPlayer.RemoveEva(15);
		else
			IPlayer.RemoveOTP(15);

		IPlayer.DecreaseMaxHp(200);
		IPlayer.DecreaseMaxMp(150);
	}
	else if (IItem.GetSetGem() == 232)
	{
		IPlayer.RemoveMaxAttack(check * 14 / 100);
		IPlayer.RemoveMinAttack(check * 14 / 100);
		IPlayer.RemoveHp(5);

		if (IItem.GetType() == -1 || (IItem.GetType() == -3 && IPlayer.GetClass() == 4))
			IPlayer.RemoveEva(15);
		else
			IPlayer.RemoveOTP(15);

		IPlayer.DecreaseMaxHp(200);
		IPlayer.DecreaseMaxMp(150);
	}
	else if (IItem.GetSetGem() == 231)
	{
		IPlayer.RemoveMaxAttack(check * 14 / 100);
		IPlayer.RemoveMinAttack(check * 14 / 100);
		IPlayer.RemoveStr(5);

		if (IItem.GetType() == -1 || (IItem.GetType() == -3 && IPlayer.GetClass() == 4))
			IPlayer.RemoveEva(15);
		else
			IPlayer.RemoveOTP(15);

		IPlayer.DecreaseMaxHp(200);
		IPlayer.DecreaseMaxMp(150);
	}
	else if (IItem.GetSetGem() == 230)
	{
		IPlayer.RemoveMaxAttack(check * 12 / 100);
		IPlayer.RemoveMinAttack(check * 12 / 100);
		IPlayer.RemoveAgi(3);

		if (IItem.GetType() == -1 || (IItem.GetType() == -3 && IPlayer.GetClass() == 4))
			IPlayer.RemoveEva(12);
		else
			IPlayer.RemoveOTP(12);

		IPlayer.DecreaseMaxHp(130);
		IPlayer.DecreaseMaxMp(110);
	}
	else if (IItem.GetSetGem() == 229)
	{
		IPlayer.RemoveMaxAttack(check * 12 / 100);
		IPlayer.RemoveMinAttack(check * 12 / 100);
		IPlayer.RemoveWis(3);

		if (IItem.GetType() == -1 || (IItem.GetType() == -3 && IPlayer.GetClass() == 4))
			IPlayer.RemoveEva(12);
		else
			IPlayer.RemoveOTP(12);

		IPlayer.DecreaseMaxHp(130);
		IPlayer.DecreaseMaxMp(110);
	}
	else if (IItem.GetSetGem() == 228)
	{
		IPlayer.RemoveMaxAttack(check * 12 / 100);
		IPlayer.RemoveMinAttack(check * 12 / 100);
		IPlayer.RemoveInt(3);

		if (IItem.GetType() == -1 || (IItem.GetType() == -3 && IPlayer.GetClass() == 4))
			IPlayer.RemoveEva(12);
		else
			IPlayer.RemoveOTP(12);

		IPlayer.DecreaseMaxHp(130);
		IPlayer.DecreaseMaxMp(110);
	}
	else if (IItem.GetSetGem() == 227)
	{
		IPlayer.RemoveMaxAttack(check * 12 / 100);
		IPlayer.RemoveMinAttack(check * 12 / 100);
		IPlayer.RemoveHp(3);

		if (IItem.GetType() == -1 || (IItem.GetType() == -3 && IPlayer.GetClass() == 4))
			IPlayer.RemoveEva(12);
		else
			IPlayer.RemoveOTP(12);

		IPlayer.DecreaseMaxHp(130);
		IPlayer.DecreaseMaxMp(110);
	}
	else if (IItem.GetSetGem() == 226)
	{
		IPlayer.RemoveMaxAttack(check * 12 / 100);
		IPlayer.RemoveMinAttack(check * 12 / 100);
		IPlayer.RemoveStr(3);

		if (IItem.GetType() == -1 || (IItem.GetType() == -3 && IPlayer.GetClass() == 4))
			IPlayer.RemoveEva(12);
		else
			IPlayer.RemoveOTP(12);

		IPlayer.DecreaseMaxHp(130);
		IPlayer.DecreaseMaxMp(110);
	}
	else if (IItem.GetSetGem() == 225)
	{
		IPlayer.RemoveMaxAttack(check * 10 / 100);
		IPlayer.RemoveMinAttack(check * 10 / 100);
		IPlayer.RemoveAgi(3);

		if (IItem.GetType() == -1 || (IItem.GetType() == -3 && IPlayer.GetClass() == 4))
			IPlayer.RemoveEva(10);
		else
			IPlayer.RemoveOTP(10);

		IPlayer.DecreaseMaxHp(110);
		IPlayer.DecreaseMaxMp(90);
	}
	else if (IItem.GetSetGem() == 224)
	{
		IPlayer.RemoveMaxAttack(check * 10 / 100);
		IPlayer.RemoveMinAttack(check * 10 / 100);
		IPlayer.RemoveWis(3);

		if (IItem.GetType() == -1 || (IItem.GetType() == -3 && IPlayer.GetClass() == 4))
			IPlayer.RemoveEva(10);
		else
			IPlayer.RemoveOTP(10);

		IPlayer.DecreaseMaxHp(110);
		IPlayer.DecreaseMaxMp(90);
	}
	else if (IItem.GetSetGem() == 223)
	{
		IPlayer.RemoveMaxAttack(check * 10 / 100);
		IPlayer.RemoveMinAttack(check * 10 / 100);
		IPlayer.RemoveInt(3);

		if (IItem.GetType() == -1 || (IItem.GetType() == -3 && IPlayer.GetClass() == 4))
			IPlayer.RemoveEva(10);
		else
			IPlayer.RemoveOTP(10);

		IPlayer.DecreaseMaxHp(110);
		IPlayer.DecreaseMaxMp(90);
	}
	else if (IItem.GetSetGem() == 222)
	{
		IPlayer.RemoveMaxAttack(check * 10 / 100);
		IPlayer.RemoveMinAttack(check * 10 / 100);
		IPlayer.RemoveHp(3);

		if (IItem.GetType() == -1 || (IItem.GetType() == -3 && IPlayer.GetClass() == 4))
			IPlayer.RemoveEva(10);
		else
			IPlayer.RemoveOTP(10);

		IPlayer.DecreaseMaxHp(110);
		IPlayer.DecreaseMaxMp(90);
	}
	else if (IItem.GetSetGem() == 221)
	{
		IPlayer.RemoveMaxAttack(check * 10 / 100);
		IPlayer.RemoveMinAttack(check * 10 / 100);
		IPlayer.RemoveStr(3);

		if (IItem.GetType() == -1 || (IItem.GetType() == -3 && IPlayer.GetClass() == 4))
			IPlayer.RemoveEva(10);
		else
			IPlayer.RemoveOTP(10);

		IPlayer.DecreaseMaxHp(110);
		IPlayer.DecreaseMaxMp(90);
	}
	else if (IItem.GetSetGem() == 220)
	{
		IPlayer.RemoveMaxAttack(check * 8 / 100);
		IPlayer.RemoveMinAttack(check * 8 / 100);
		IPlayer.RemoveAgi(2);

		if (IItem.GetType() == -1 || (IItem.GetType() == -3 && IPlayer.GetClass() == 4))
			IPlayer.RemoveEva(8);
		else
			IPlayer.RemoveOTP(8);

		IPlayer.DecreaseMaxHp(90);
		IPlayer.DecreaseMaxMp(70);
	}
	else if (IItem.GetSetGem() == 219)
	{
		IPlayer.RemoveMaxAttack(check * 8 / 100);
		IPlayer.RemoveMinAttack(check * 8 / 100);
		IPlayer.RemoveWis(2);

		if (IItem.GetType() == -1 || (IItem.GetType() == -3 && IPlayer.GetClass() == 4))
			IPlayer.RemoveEva(8);
		else
			IPlayer.RemoveOTP(8);

		IPlayer.DecreaseMaxHp(90);
		IPlayer.DecreaseMaxMp(70);
	}
	else if (IItem.GetSetGem() == 218)
	{
		IPlayer.RemoveMaxAttack(check * 8 / 100);
		IPlayer.RemoveMinAttack(check * 8 / 100);
		IPlayer.RemoveInt(2);

		if (IItem.GetType() == -1 || (IItem.GetType() == -3 && IPlayer.GetClass() == 4))
			IPlayer.RemoveEva(8);
		else
			IPlayer.RemoveOTP(8);

		IPlayer.DecreaseMaxHp(90);
		IPlayer.DecreaseMaxMp(70);
	}
	else if (IItem.GetSetGem() == 217)
	{
		IPlayer.RemoveMaxAttack(check * 8 / 100);
		IPlayer.RemoveMinAttack(check * 8 / 100);
		IPlayer.RemoveHp(2);

		if (IItem.GetType() == -1 || (IItem.GetType() == -3 && IPlayer.GetClass() == 4))
			IPlayer.RemoveEva(8);
		else
			IPlayer.RemoveOTP(8);

		IPlayer.DecreaseMaxHp(90);
		IPlayer.DecreaseMaxMp(70);
	}
	else if (IItem.GetSetGem() == 216)
	{
		IPlayer.RemoveMaxAttack(check * 8 / 100);
		IPlayer.RemoveMinAttack(check * 8 / 100);
		IPlayer.RemoveStr(2);

		if (IItem.GetType() == -1 || (IItem.GetType() == -3 && IPlayer.GetClass() == 4))
			IPlayer.RemoveEva(8);
		else
			IPlayer.RemoveOTP(8);

		IPlayer.DecreaseMaxHp(90);
		IPlayer.DecreaseMaxMp(70);
	}
	else if (IItem.GetSetGem() == 215)
	{
		IPlayer.RemoveMaxAttack(check * 6 / 100);
		IPlayer.RemoveMinAttack(check * 6 / 100);
		IPlayer.RemoveAgi(2);

		if (IItem.GetType() == -1 || (IItem.GetType() == -3 && IPlayer.GetClass() == 4))
			IPlayer.RemoveEva(6);
		else
			IPlayer.RemoveOTP(6);

		IPlayer.DecreaseMaxHp(70);
		IPlayer.DecreaseMaxMp(50);
	}
	else if (IItem.GetSetGem() == 214)
	{
		IPlayer.RemoveMaxAttack(check * 6 / 100);
		IPlayer.RemoveMinAttack(check * 6 / 100);
		IPlayer.RemoveWis(2);

		if (IItem.GetType() == -1 || (IItem.GetType() == -3 && IPlayer.GetClass() == 4))
			IPlayer.RemoveEva(6);
		else
			IPlayer.RemoveOTP(6);

		IPlayer.DecreaseMaxHp(70);
		IPlayer.DecreaseMaxMp(50);
	}
	else if (IItem.GetSetGem() == 213)
	{
		IPlayer.RemoveMaxAttack(check * 6 / 100);
		IPlayer.RemoveMinAttack(check * 6 / 100);
		IPlayer.RemoveInt(2);

		if (IItem.GetType() == -1 || (IItem.GetType() == -3 && IPlayer.GetClass() == 4))
			IPlayer.RemoveEva(6);
		else
			IPlayer.RemoveOTP(6);

		IPlayer.DecreaseMaxHp(70);
		IPlayer.DecreaseMaxMp(50);
	}
	else if (IItem.GetSetGem() == 212)
	{
		IPlayer.RemoveMaxAttack(check * 6 / 100);
		IPlayer.RemoveMinAttack(check * 6 / 100);
		IPlayer.RemoveHp(2);

		if (IItem.GetType() == -1 || (IItem.GetType() == -3 && IPlayer.GetClass() == 4))
			IPlayer.RemoveEva(6);
		else
			IPlayer.RemoveOTP(6);

		IPlayer.DecreaseMaxHp(70);
		IPlayer.DecreaseMaxMp(50);
	}
	else if (IItem.GetSetGem() == 211)
	{
		IPlayer.RemoveMaxAttack(check * 6 / 100);
		IPlayer.RemoveMinAttack(check * 6 / 100);
		IPlayer.RemoveStr(2);

		if (IItem.GetType() == -1 || (IItem.GetType() == -3 && IPlayer.GetClass() == 4))
			IPlayer.RemoveEva(6);
		else
			IPlayer.RemoveOTP(6);

		IPlayer.DecreaseMaxHp(70);
		IPlayer.DecreaseMaxMp(50);
	}
	else if (IItem.GetSetGem() == 210)
	{
		IPlayer.RemoveMaxAttack(check * 4 / 100);
		IPlayer.RemoveMinAttack(check * 4 / 100);
		IPlayer.RemoveAgi(1);

		if (IItem.GetType() == -1 || (IItem.GetType() == -3 && IPlayer.GetClass() == 4))
			IPlayer.RemoveEva(4);
		else
			IPlayer.RemoveOTP(4);

		IPlayer.DecreaseMaxHp(50);
		IPlayer.DecreaseMaxMp(30);
	}
	else if (IItem.GetSetGem() == 209)
	{
		IPlayer.RemoveMaxAttack(check * 4 / 100);
		IPlayer.RemoveMinAttack(check * 4 / 100);
		IPlayer.RemoveWis(1);

		if (IItem.GetType() == -1 || (IItem.GetType() == -3 && IPlayer.GetClass() == 4))
			IPlayer.RemoveEva(4);
		else
			IPlayer.RemoveOTP(4);

		IPlayer.DecreaseMaxHp(50);
		IPlayer.DecreaseMaxMp(30);
	}
	else if (IItem.GetSetGem() == 208)
	{
		IPlayer.RemoveMaxAttack(check * 4 / 100);
		IPlayer.RemoveMinAttack(check * 4 / 100);
		IPlayer.RemoveInt(1);

		if (IItem.GetType() == -1 || (IItem.GetType() == -3 && IPlayer.GetClass() == 4))
			IPlayer.RemoveEva(4);
		else
			IPlayer.RemoveOTP(4);

		IPlayer.DecreaseMaxHp(50);
		IPlayer.DecreaseMaxMp(30);
	}
	else if (IItem.GetSetGem() == 207)
	{
		IPlayer.RemoveMaxAttack(check * 4 / 100);
		IPlayer.RemoveMinAttack(check * 4 / 100);
		IPlayer.RemoveHp(1);

		if (IItem.GetType() == -1 || (IItem.GetType() == -3 && IPlayer.GetClass() == 4))
			IPlayer.RemoveEva(4);
		else
			IPlayer.RemoveOTP(4);

		IPlayer.DecreaseMaxHp(50);
		IPlayer.DecreaseMaxMp(30);
	}
	else if (IItem.GetSetGem() == 206)
	{
		IPlayer.RemoveMaxAttack(check * 4 / 100);
		IPlayer.RemoveMinAttack(check * 4 / 100);
		IPlayer.RemoveStr(1);

		if (IItem.GetType() == -1 || (IItem.GetType() == -3 && IPlayer.GetClass() == 4))
			IPlayer.RemoveEva(4);
		else
			IPlayer.RemoveOTP(4);

		IPlayer.DecreaseMaxHp(50);
		IPlayer.DecreaseMaxMp(30);
	}
	else if (IItem.GetSetGem() == 205)
	{
		IPlayer.RemoveMaxAttack(check * 2 / 100);
		IPlayer.RemoveMinAttack(check * 2 / 100);
		IPlayer.RemoveAgi(1);

		if (IItem.GetType() == -1 || (IItem.GetType() == -3 && IPlayer.GetClass() == 4))
			IPlayer.RemoveEva(2);
		else
			IPlayer.RemoveOTP(2);

		IPlayer.DecreaseMaxHp(30);
		IPlayer.DecreaseMaxMp(10);
	}
	else if (IItem.GetSetGem() == 204)
	{
		IPlayer.RemoveMaxAttack(check * 2 / 100);
		IPlayer.RemoveMinAttack(check * 2 / 100);
		IPlayer.RemoveWis(1);

		if (IItem.GetType() == -1 || (IItem.GetType() == -3 && IPlayer.GetClass() == 4))
			IPlayer.RemoveEva(2);
		else
			IPlayer.RemoveOTP(2);

		IPlayer.DecreaseMaxHp(30);
		IPlayer.DecreaseMaxMp(10);
	}
	else if (IItem.GetSetGem() == 203)
	{
		IPlayer.RemoveMaxAttack(check * 2 / 100);
		IPlayer.RemoveMinAttack(check * 2 / 100);
		IPlayer.RemoveInt(1);

		if (IItem.GetType() == -1 || (IItem.GetType() == -3 && IPlayer.GetClass() == 4))
			IPlayer.RemoveEva(2);
		else
			IPlayer.RemoveOTP(2);

		IPlayer.DecreaseMaxHp(30);
		IPlayer.DecreaseMaxMp(10);
	}
	else if (IItem.GetSetGem() == 202)
	{
		IPlayer.RemoveMaxAttack(check * 2 / 100);
		IPlayer.RemoveMinAttack(check * 2 / 100);
		IPlayer.RemoveHp(1);

		if (IItem.GetType() == -1 || (IItem.GetType() == -3 && IPlayer.GetClass() == 4))
			IPlayer.RemoveEva(2);
		else
			IPlayer.RemoveOTP(2);

		IPlayer.DecreaseMaxHp(30);
		IPlayer.DecreaseMaxMp(10);
	}
	else if (IItem.GetSetGem() == 201)
	{
		IPlayer.RemoveMaxAttack(check * 2 / 100);
		IPlayer.RemoveMinAttack(check * 2 / 100);
		IPlayer.RemoveStr(1);

		if (IItem.GetType() == -1 || (IItem.GetType() == -3 && IPlayer.GetClass() == 4))
			IPlayer.RemoveEva(2);
		else
			IPlayer.RemoveOTP(2);

		IPlayer.DecreaseMaxHp(30);
		IPlayer.DecreaseMaxMp(10);
	}
}

void __fastcall WeaponPutOn(int Item, void *edx, int Player)
{
	IChar IPlayer((void*)Player);
	IItem IItem((void*)Item);

	if (!isItemCustomWeapon(IItem.CheckIndex()) && IPlayer.GetBuffValue(BuffNames::WeaponWear)) {
		IPlayer.SystemMessage("Please take off your main weapon first.", TEXTCOLOR_RED);
		return;
	}

	if (isItemCustomWeapon(IItem.CheckIndex()) && IPlayer.GetBuffValue(BuffNames::custWeap)) {
		IPlayer.SystemMessage("Please take off your custom weapon first.", TEXTCOLOR_RED);
		return;
	}

	if (IPlayer.IsValid() && IPlayer.IsBuff(120))
	{
		if (IItem.LevelLimit() > 5)
			IItem.SetLevelLimit(IItem.LevelLimit() - 5);
	}

	int Old = *(DWORD *)(Player + 156);

	CItemWeapon::PutOn(Item, Player);

	if (!CItem::IsState(Item, 1))
		return;

	if (IPlayer.IsValid() && IPlayer.IsBuff(120))
	{
		if (IItem.LevelLimit() > 5)
			IItem.SetLevelLimit(IItem.LevelLimit() + 5);
	}

	if (isItemCustomWeapon(IItem.CheckIndex())) {
		*(DWORD *)(Player + 156) = Old;
		if (CostWeaponsEffects.count(IItem.CheckIndex()))
			IPlayer.AddFxToBone(IPlayer.CostEffect(CostWeaponsEffects.find(IItem.CheckIndex())->second), 1);
	}
	else {
		int custWeapon = IPlayer.GetBuffValue(BuffNames::custWeap);
		if (custWeapon) {
			if (CostWeaponsEffects.count(custWeapon))
				IPlayer.AddFxToBone(IPlayer.CostEffect(CostWeaponsEffects.find(custWeapon)->second), 1);
		}
	}
}