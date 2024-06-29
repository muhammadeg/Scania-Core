void __fastcall DefenseApplySpec(int Item, void *edx, int Player)
{
	IItem IItem((void*)Item);
	IChar IPlayer((void*)Player);

	if (IPlayer.IsOnline())
	{
		int def = IPlayer.GetDef();
		CItemDefense::ApplySpec(Item,Player);
		int check = IPlayer.GetDef() - (def + *((DWORD*)Item + 27));

		if (EquipEffects.count(IItem.CheckIndex())){
			IPlayer.UpdateBuff(BuffNames::EffectsIID, BuffNames::BuffTime, IItem.GetIID());
			IPlayer.UpdateBuff(BuffNames::ItemsEffects, BuffNames::BuffTime, IItem.CheckIndex());
		}

		if (IItem.GetType() == 3) {
			if (isItemCostumeEffect(IItem.CheckIndex())) {
				int Effect = CostumeEffects.find(IItem.CheckIndex())->second * 1000;
				IPlayer.UpdateBuff(BuffNames::CostumeEffect, BuffNames::BuffTime, Effect);
				CChar::WriteInSight(IPlayer.GetOffset(), 0xFE, "ddd", 186, IPlayer.GetID(), Effect);
			}
			else
				IPlayer.UpdateBuff(BuffNames::CostumeEffectCheck, BuffNames::BuffTime, IItem.CheckIndex());
		}

		if (IItem.GetType() == 4) {
			int Show = *(WORD *)(*(DWORD *)(Item + 40) + 64);
			ShowItem(IPlayer, Show);
			if (!isItemSuit(IItem.CheckIndex()))
				IPlayer.UpdateBuff(BuffNames::ArmorWears, BuffNames::BuffTime, Show);
			else
				IPlayer.UpdateBuff(BuffNames::SuitsUsing, BuffNames::BuffTime, Show);
		}

		itemStat.Enter();
		int ItemStat = GetItemStat.count(IItem.GetIID()) ? GetItemStat.find(IItem.GetIID())->second : 0;
		itemStat.Leave();

		if (ItemStat > 0) {

			if (isItemRidingArmor(IItem.CheckIndex()) && ItemStat > 0 && ItemStat <= 10) {
				int index = IItem.CheckIndex();

				if (GetBattleRidingType(index) == 1) {
					if (index == 7883 || index == 7889 || index == 7895 || index == 7901)
						IPlayer.AddStr(RidingHelmet[GetBattleRidingGrade(index) - 1][ItemStat - 1]);
					else
						IPlayer.AddInt(RidingHelmet[GetBattleRidingGrade(index) - 1][ItemStat - 1]);
				}

				if (GetBattleRidingType(index) == 2)
					IPlayer.AddHp(RidingSaddle[GetBattleRidingGrade(index) - 1][ItemStat - 1]);
				if (GetBattleRidingType(index) == 3)
					IPlayer.AddDef(RidingArmor[GetBattleRidingGrade(index) - 1][ItemStat - 1]);
				if (GetBattleRidingType(index) == 4)
					IPlayer.AddAbsorb(RidingCloth[GetBattleRidingGrade(index) - 1][ItemStat - 1]);
				if (GetBattleRidingType(index) == 5)
					IPlayer.AddEva(RidingMagnet[GetBattleRidingGrade(index) - 1][ItemStat - 1]);
			}

			if (isItemSuit(IItem.CheckIndex()) && ItemStat) {
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

			int QigongType = ItemStat % 100;
			int DemonGongStyle = (ItemStat % 100000000) / 10000000;

			if (DemonGongStyle) {
				int DemonGrade = (ItemStat % 10000000) / 1000000;
				int Grade = DemonGrade + 1;

				if (DemonGongStyle == 1) {
					int def = 0, otp = 0;
					if (Grade == 1) {
						def = 2;
						otp = 1;
					}if (Grade == 2) {
						def = 4;
						otp = 1;
					}if (Grade == 3) {
						def = 6;
						otp = 2;
					}if (Grade == 4) {
						def = 8;
						otp = 2;
					}if (Grade == 5) {
						def = 10;
						otp = 2;
					}if (Grade == 6) {
						def = 12;
						otp = 3;
					}if (Grade == 7) {
						def = 15;
						otp = 3;
					}if (Grade == 8) {
						def = 18;
						otp = 3;
					}if (Grade == 9) {
						def = 21;
						otp = 3;
					}if (Grade == 10) {
						def = 26;
						otp = 4;
					}
					IPlayer.AddDef(def);
					IPlayer.AddOTP(otp);
				}
				if (DemonGongStyle == 2) {
					int hp = 0, eva = 0;
					if (Grade == 1) {
						hp = 50;
						eva = 1;
					}if (Grade == 2) {
						hp = 60;
						eva = 2;
					}if (Grade == 3) {
						hp = 80;
						eva = 2;
					}if (Grade == 4) {
						hp = 90;
						eva = 3;
					}if (Grade == 5) {
						hp = 100;
						eva = 3;
					}if (Grade == 6) {
						hp = 110;
						eva = 4;
					}if (Grade == 7) {
						hp = 130;
						eva = 4;
					}if (Grade == 8) {
						hp = 160;
						eva = 4;
					}if (Grade == 9) {
						hp = 190;
						eva = 5;
					}if (Grade == 10) {
						hp = 250;
						eva = 5;
					}
					IPlayer.IncreaseMaxHp(hp);
					IPlayer.AddEva(eva);
				}
				if (DemonGongStyle == 3) {
					int agi = 0, def = 0;
					if (Grade == 1) {
						agi = 1;
						def = 1;
					}if (Grade == 2) {
						agi = 2;
						def = 2;
					}if (Grade == 3) {
						agi = 2;
						def = 3;
					}if (Grade == 4) {
						agi = 2;
						def = 5;
					}if (Grade == 5) {
						agi = 3;
						def = 5;
					}if (Grade == 6) {
						agi = 3;
						def = 6;
					}if (Grade == 7) {
						agi = 3;
						def = 8;
					}if (Grade == 8) {
						agi = 4;
						def = 10;
					}if (Grade == 9) {
						agi = 4;
						def = 11;
					}if (Grade == 10) {
						agi = 5;
						def = 12;
					}
					IPlayer.AddAgi(agi);
					IPlayer.AddDef(def);
				}

			}
			if (QigongType)
			{
				if (IItem.GetType() == 3)
				{
					IPlayer.AddDef((check*QigongChest[QigongType - 1][0]) / 100);
					int Type = QigongChest[QigongType - 1][1];
					int Stat = QigongChest[QigongType - 1][2];

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
				else if (IItem.GetType() == 4)
				{
					IPlayer.AddDef((check*QigongShort[QigongType - 1][0]) / 100);
					int Type = QigongChest[QigongType - 1][1];
					int Stat = QigongChest[QigongType - 1][2];

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
				else {
					IPlayer.AddDef((check*QigongMain[QigongType - 1][0]) / 100);
					int Type = QigongChest[QigongType - 1][1];
					int Stat = QigongChest[QigongType - 1][2];

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
		}

		if (IItem.GetSetGem() == 240)
		{
			IPlayer.AddDef((check*18)/100);
			IPlayer.AddAgi(7);
		} else if (IItem.GetSetGem() == 239)
		{
			IPlayer.AddDef((check*18)/100);
			IPlayer.AddWis(7);
		} else if (IItem.GetSetGem() == 238)
		{
			IPlayer.AddDef((check*18)/100);
			IPlayer.AddInt(7);
		} else if (IItem.GetSetGem() == 237)
		{
			IPlayer.AddDef((check*18)/100);
			IPlayer.AddHp(7);
		} else if (IItem.GetSetGem() == 236)
		{
			IPlayer.AddDef((check*18)/100);
			IPlayer.AddStr(7);
		} else if (IItem.GetSetGem() == 235)
		{
			IPlayer.AddDef((check*16)/100);
			IPlayer.AddAgi(5);
		} else if (IItem.GetSetGem() == 234)
		{
			IPlayer.AddDef((check*16)/100);
			IPlayer.AddWis(5);
		} else if (IItem.GetSetGem() == 233)
		{
			IPlayer.AddDef((check*16)/100);
			IPlayer.AddInt(5);
		} else if (IItem.GetSetGem() == 232)
		{
			IPlayer.AddDef((check*16)/100);
			IPlayer.AddHp(5);
		} else if (IItem.GetSetGem() == 231)
		{
			IPlayer.AddDef((check*16)/100);
			IPlayer.AddStr(5);
		} else if (IItem.GetSetGem() == 230)
		{
			IPlayer.AddDef((check*14)/100);
			IPlayer.AddAgi(3);
		} else if (IItem.GetSetGem() == 229)
		{
			IPlayer.AddDef((check*14)/100);
			IPlayer.AddWis(3);
		} else if (IItem.GetSetGem() == 228)
		{
			IPlayer.AddDef((check*14)/100);
			IPlayer.AddInt(3);
		} else if (IItem.GetSetGem() == 227)
		{
			IPlayer.AddDef((check*14)/100);
			IPlayer.AddHp(3);
		} else if (IItem.GetSetGem() == 226)
		{
			IPlayer.AddDef((check*14)/100);
			IPlayer.AddStr(3);
		} else if (IItem.GetSetGem() == 225)
		{
			IPlayer.AddDef((check*12)/100);
			IPlayer.AddAgi(3);
		} else if (IItem.GetSetGem() == 224)
		{
			IPlayer.AddDef((check*12)/100);
			IPlayer.AddWis(3);
		} else if (IItem.GetSetGem() == 223)
		{
			IPlayer.AddDef((check*12)/100);
			IPlayer.AddInt(3);
		} else if (IItem.GetSetGem() == 222)
		{
			IPlayer.AddDef((check*12)/100);
			IPlayer.AddHp(3);
		} else if (IItem.GetSetGem() == 221)
		{
			IPlayer.AddDef((check*12)/100);
			IPlayer.AddStr(3);
		} else if (IItem.GetSetGem() == 220)
		{
			IPlayer.AddDef((check*10)/100);
			IPlayer.AddAgi(2);
		} else if (IItem.GetSetGem() == 219)
		{
			IPlayer.AddDef((check*10)/100);
			IPlayer.AddWis(2);
		} else if (IItem.GetSetGem() == 218)
		{
			IPlayer.AddDef((check*10)/100);
			IPlayer.AddInt(2);
		} else if (IItem.GetSetGem() == 217)
		{
			IPlayer.AddDef((check*10)/100);
			IPlayer.AddHp(2);
		} else if (IItem.GetSetGem() == 216)
		{
			IPlayer.AddDef((check*10)/100);
			IPlayer.AddStr(2);
		} else if (IItem.GetSetGem() == 215)
		{
			IPlayer.AddDef((check*8)/100);
			IPlayer.AddAgi(2);
		} else if (IItem.GetSetGem() == 214)
		{
			IPlayer.AddDef((check*8)/100);
			IPlayer.AddWis(2);
		} else if (IItem.GetSetGem() == 213)
		{
			IPlayer.AddDef((check*8)/100);
			IPlayer.AddInt(2);
		} else if (IItem.GetSetGem() == 212)
		{
			IPlayer.AddDef((check*8)/100);
			IPlayer.AddHp(2);
		} else if (IItem.GetSetGem() == 211)
		{
			IPlayer.AddDef((check*8)/100);
			IPlayer.AddStr(2);
		} else if (IItem.GetSetGem() == 210)
		{
			IPlayer.AddDef((check*6)/100);
			IPlayer.AddAgi(1);
		} else if (IItem.GetSetGem() == 209)
		{
			IPlayer.AddDef((check*6)/100);
			IPlayer.AddWis(1);
		} else if (IItem.GetSetGem() == 208)
		{
			IPlayer.AddDef((check*6)/100);
			IPlayer.AddInt(1);
		} else if (IItem.GetSetGem() == 207)
		{
			IPlayer.AddDef((check*6)/100);
			IPlayer.AddHp(1);
		} else if (IItem.GetSetGem() == 206)
		{
			IPlayer.AddDef((check*6)/100);
			IPlayer.AddStr(1);
		} else if (IItem.GetSetGem() == 205)
		{
			IPlayer.AddDef((check*4)/100);
			IPlayer.AddAgi(1);
		} else if (IItem.GetSetGem() == 204)
		{
			IPlayer.AddDef((check*4)/100);
			IPlayer.AddWis(1);
		} else if (IItem.GetSetGem() == 203)
		{
			IPlayer.AddDef((check*4)/100);
			IPlayer.AddInt(1);
		} else if (IItem.GetSetGem() == 202)
		{
			IPlayer.AddDef((check*4)/100);
			IPlayer.AddHp(1);
		} else if (IItem.GetSetGem() == 201)
		{
			IPlayer.AddDef((check*4)/100);
			IPlayer.AddStr(1);
		}

		if (IItem.GetInfo() & 2097152)
		{
			int Grade = *(DWORD*)(*(DWORD*)(Item + 40) + 80);
			int Stat = 0;

			if (Grade >= 46 && Grade <= 49)
				Stat = 1;
			else if (Grade >= 50 && Grade <= 53)
				Stat = 2;
			else if (Grade >= 55 && Grade <= 58)
				Stat = 3;
			else if (Grade >= 60 && Grade <= 63)
				Stat = 4;
			else if (Grade >= 65 && Grade <= 68)
				Stat = 5;
			else if (Grade >= 70 && Grade <= 73)
				Stat = 6;
			else if (Grade >= 80 && Grade <= 83)
				Stat = 7;
			else if (Grade >= 90 && Grade <= 93)
				Stat = 8;
			else if (Grade >= 95)
				Stat = 9;

			IPlayer.AddAgi(Stat);
			IPlayer.AddStr(Stat);
			IPlayer.AddInt(Stat);

			if (IItem.GetType() == 2)
				IPlayer.UpdateBuff(BuffNames::BOFHelmet, BuffNames::BuffTime, Grade);
			else if (IItem.GetType() == 3)
				IPlayer.UpdateBuff(BuffNames::BOFChest, BuffNames::BuffTime, Grade);
			else if (IItem.GetType() == 4 && !isItemSuit(IItem.CheckIndex()))
				IPlayer.UpdateBuff(BuffNames::BOFShort, BuffNames::BuffTime, Grade);
			else if (IItem.GetType() == 5)
				IPlayer.UpdateBuff(BuffNames::BOFGloves, BuffNames::BuffTime, Grade);
			else if (IItem.GetType() == 6)
				IPlayer.UpdateBuff(BuffNames::BOFBoots, BuffNames::BuffTime, Grade);

			int BOFBoots = IPlayer.GetBuffValue(BuffNames::BOFBoots);
			int BOFShort = IPlayer.GetBuffValue(BuffNames::BOFShort);
			int BOFGloves = IPlayer.GetBuffValue(BuffNames::BOFGloves);
			int BOFChest = IPlayer.GetBuffValue(BuffNames::BOFChest);
			int BOFHelmet = IPlayer.GetBuffValue(BuffNames::BOFHelmet);
			int BOFHalfSet = IPlayer.GetBuffValue(BuffNames::BOFHalfSet);
			int BOFFullSet = IPlayer.GetBuffValue(BuffNames::BOFFullSet);

			if (BOFBoots && BOFBoots == 46 && BOFShort == 46 && BOFGloves == 46 && !BOFHalfSet)
			{
				IPlayer.UpdateBuff(BuffNames::BOFHalfSet, BuffNames::BuffTime, 46);
				IPlayer.AddAgi(1);
				IPlayer.AddStr(1);
				IPlayer.AddInt(1);
			}

			if (BOFHelmet && BOFHelmet == 46 && BOFChest == 46 && BOFHalfSet == 46 && !BOFFullSet)
			{
				IPlayer.UpdateBuff(BuffNames::BOFFullSet, BuffNames::BuffTime, 46);
				IPlayer.AddAgi(1);
				IPlayer.AddStr(1);
				IPlayer.AddInt(1);
			}

			if (BOFBoots && BOFBoots == 50 && BOFShort == 50 && BOFGloves == 50 && !BOFHalfSet)
			{
				IPlayer.UpdateBuff(BuffNames::BOFHalfSet, BuffNames::BuffTime, 50);
				IPlayer.AddAgi(2);
				IPlayer.AddStr(2);
				IPlayer.AddInt(2);
			}

			if (BOFHelmet == 50 && BOFChest == 50 && BOFHalfSet == 50 && !BOFFullSet)
			{
				IPlayer.UpdateBuff(BuffNames::BOFFullSet, BuffNames::BuffTime, 50);
				IPlayer.AddAgi(2);
				IPlayer.AddStr(2);
				IPlayer.AddInt(2);
			}

			if (BOFBoots && BOFBoots == 55 && BOFShort == 55 && BOFGloves == 55 && !BOFHalfSet)
			{
				IPlayer.UpdateBuff(BuffNames::BOFHalfSet, BuffNames::BuffTime, 55);
				IPlayer.AddAgi(3);
				IPlayer.AddStr(3);
				IPlayer.AddInt(3);
			}

			if (BOFHelmet && BOFHelmet == 55 && BOFChest == 55 && BOFHalfSet == 55 && !BOFFullSet)
			{
				IPlayer.UpdateBuff(BuffNames::BOFFullSet, BuffNames::BuffTime, 55);
				IPlayer.AddAgi(3);
				IPlayer.AddStr(3);
				IPlayer.AddInt(3);
			}

			if (BOFBoots && BOFBoots == 60 && BOFShort == 60 && BOFGloves == 60 && !BOFHalfSet)
			{
				IPlayer.UpdateBuff(BuffNames::BOFHalfSet, BuffNames::BuffTime, 60);
				IPlayer.AddAgi(4);
				IPlayer.AddStr(4);
				IPlayer.AddInt(4);
			}

			if (BOFHelmet && BOFHelmet == 60 && BOFChest == 60 && BOFHalfSet == 60 && !BOFFullSet)
			{
				IPlayer.UpdateBuff(BuffNames::BOFFullSet, BuffNames::BuffTime, 60);
				IPlayer.AddAgi(4);
				IPlayer.AddStr(4);
				IPlayer.AddInt(4);
			}

			if (BOFBoots && BOFBoots == 65 && BOFShort == 65 && BOFGloves == 65 && !BOFHalfSet)
			{
				IPlayer.UpdateBuff(BuffNames::BOFHalfSet, BuffNames::BuffTime, 65);
				IPlayer.AddAgi(5);
				IPlayer.AddStr(5);
				IPlayer.AddInt(5);
			}

			if (BOFHelmet && BOFHelmet == 65 && BOFChest == 65 && BOFHalfSet == 65 && !BOFFullSet)
			{
				IPlayer.UpdateBuff(BuffNames::BOFFullSet, BuffNames::BuffTime, 65);
				IPlayer.AddAgi(5);
				IPlayer.AddStr(5);
				IPlayer.AddInt(5);
			}

			if (BOFBoots && BOFBoots == 70 && BOFShort == 70 && BOFGloves == 70 && !BOFHalfSet)
			{
				IPlayer.UpdateBuff(BuffNames::BOFHalfSet, BuffNames::BuffTime, 70);
				IPlayer.AddAgi(6);
				IPlayer.AddStr(6);
				IPlayer.AddInt(6);
			}

			if (BOFHelmet && BOFHelmet == 70 && BOFChest == 70 && BOFHalfSet == 70 && !BOFFullSet)
			{
				IPlayer.UpdateBuff(BuffNames::BOFFullSet, BuffNames::BuffTime, 70);
				IPlayer.AddAgi(6);
				IPlayer.AddStr(6);
				IPlayer.AddInt(6);
			}

			if (BOFBoots && BOFBoots == 80 && BOFShort == 80 && BOFGloves == 80 && !BOFHalfSet)
			{
				IPlayer.UpdateBuff(BuffNames::BOFHalfSet, BuffNames::BuffTime, 80);
				IPlayer.AddAgi(7);
				IPlayer.AddStr(7);
				IPlayer.AddInt(7);
			}

			if (BOFHelmet && BOFHelmet == 80 && BOFChest == 80 && BOFHalfSet == 80 && !BOFFullSet)
			{
				IPlayer.UpdateBuff(BuffNames::BOFFullSet, BuffNames::BuffTime, 80);
				IPlayer.AddAgi(7);
				IPlayer.AddStr(7);
				IPlayer.AddInt(7);
			}

			if (BOFBoots && BOFBoots == 90 && BOFShort == 90 && BOFGloves == 90 && !BOFHalfSet)
			{
				IPlayer.UpdateBuff(BuffNames::BOFHalfSet, BuffNames::BuffTime, 90);
				IPlayer.AddAgi(8);
				IPlayer.AddStr(8);
				IPlayer.AddInt(8);
			}

			if (BOFHelmet && BOFHelmet == 90 && BOFChest == 90 && BOFHalfSet == 90 && !BOFFullSet)
			{
				IPlayer.UpdateBuff(BuffNames::BOFFullSet, BuffNames::BuffTime, 90);
				IPlayer.AddAgi(8);
				IPlayer.AddStr(8);
				IPlayer.AddInt(8);
			}

			if (BOFBoots && BOFBoots >= 95 && BOFShort >= 95 && BOFGloves >= 95 && !BOFHalfSet)
			{
				if (BOFBoots == BOFShort && BOFShort == BOFGloves && BOFBoots == BOFGloves)
				{
					IPlayer.UpdateBuff(BuffNames::BOFHalfSet, BuffNames::BuffTime, Grade);
					IPlayer.AddAgi(9);
					IPlayer.AddStr(9);
					IPlayer.AddInt(9);
				}
			}

			if (BOFHelmet && BOFHelmet >= 95 && BOFChest >= 95 && BOFHalfSet >= 95 && !BOFFullSet)
			{
				if (BOFHelmet == BOFChest && BOFHelmet == BOFHalfSet && BOFChest == BOFHalfSet)
				{
					IPlayer.UpdateBuff(BuffNames::BOFFullSet, BuffNames::BuffTime, Grade);
					IPlayer.AddAgi(9);
					IPlayer.AddStr(9);
					IPlayer.AddInt(9);
				}
			}
		}
	}

}

void __fastcall ArmorPutOn(int Item, void *edx, int Player)
{

	IItem IItem((void*)Item);
	IChar IPlayer((void*)Player);

	if (IPlayer.IsOnline())
	{
		if (IPlayer.IsOnline() && IPlayer.IsBuff(120))
		{
			if (IItem.LevelLimit() > 5)
				IItem.SetLevelLimit(IItem.LevelLimit() - 5);
		}

		CItemDefense::PutOn(Item, Player);

		if (!CItem::IsState(Item, 1))
			return;

		if (IPlayer.IsOnline() && IPlayer.IsBuff(120))
		{
			if (IItem.LevelLimit() > 5)
				IItem.SetLevelLimit(IItem.LevelLimit() + 5);
		}
	}

}

int __fastcall DefenseSetWearState(int Item, void *edx, int Player)
{

	IItem IItem((void*)Item);
	IChar IPlayer((void*)Player);

	if (IItem.GetType() == 3 && CItem::IsState(Item, 1)) {
		if (CPlayer::IsWState(Player, IItem.GetType()) && !IPlayer.IsBuff(3885)) {
			CPlayer::AddWState((int)IPlayer.GetOffset(), IItem.GetType());

			*(WORD *)(Player + 2 * IItem.GetType() + 1052) = *(WORD *)(*(DWORD *)(Item + 40) + 64);
			(*(void(__thiscall **)(int, int))(*(DWORD *)Item + 104))(Item, (int)IPlayer.GetOffset());
			IPlayer.Buff(3885, BuffNames::BuffTime, 0);
			return 0;
		}
	}

	if (IItem.Exists() && IPlayer.IsOnline() && IItem.GetType() == 4 && CItem::IsState(Item, 1)) {
		if (CPlayer::IsWState(Player, IItem.GetType()) && !IPlayer.IsBuff(3884)) {
			CPlayer::AddWState((int)IPlayer.GetOffset(), IItem.GetType());

			*(WORD *)(Player + 2 * IItem.GetType() + 1052) = *(WORD *)(*(DWORD *)(Item + 40) + 64);
			(*(void(__thiscall **)(int, int))(*(DWORD *)Item + 104))(Item, (int)IPlayer.GetOffset());
			IPlayer.Buff(3884, BuffNames::BuffTime, 0);
			return 0;
		}
	}

	return CItemDefense::SetWearState(Item,Player);
}

void __fastcall DefensePutOff(void *Item, void *edx, int Player)
{

	IItem aItem(Item);
	IChar IPlayer((void*)Player);
	if (IPlayer.IsOnline())
	{
		if (EquipEffects.count(aItem.CheckIndex())){
			if (IPlayer.IsBuff(BuffNames::ItemsEffects)){
				IPlayer.CancelBuff(BuffNames::EffectsIID);
				IPlayer.CancelBuff(BuffNames::ItemsEffects);
			}
		}

		if (!isItemSuit(aItem.CheckIndex()) && aItem.GetType() == 4)
			IPlayer.UpdateBuff(BuffNames::ArmorWears, BuffNames::BuffTime, 0);

		if (aItem.GetType() == 4 && IPlayer.IsBuff(3884))
			IPlayer.CancelBuff(3884);

		if (aItem.GetType() == 3 && IPlayer.IsBuff(3885))
			IPlayer.CancelBuff(3885);

		if (aItem.GetInfo() & 2097152)
		{
			int Grade = *(DWORD*)(*(DWORD*)((int)Item + 40) + 80);
			int Stat = 0;

			if (Grade >= 46 && Grade <= 49)
				Stat = 1;
			else if (Grade >= 50 && Grade <= 53)
				Stat = 2;
			else if (Grade >= 55 && Grade <= 58)
				Stat = 3;
			else if (Grade >= 60 && Grade <= 63)
				Stat = 4;
			else if (Grade >= 65 && Grade <= 68)
				Stat = 5;
			else if (Grade >= 70 && Grade <= 73)
				Stat = 6;
			else if (Grade >= 80 && Grade <= 83)
				Stat = 7;
			else if (Grade >= 90 && Grade <= 93)
				Stat = 8;
			else if (Grade >= 95)
				Stat = 9;

			IPlayer.RemoveAgi(Stat);
			IPlayer.RemoveStr(Stat);
			IPlayer.RemoveInt(Stat);

			if (aItem.GetType() == 2)
				IPlayer.UpdateBuff(BuffNames::BOFHelmet, BuffNames::BuffTime, 0);
			else if (aItem.GetType() == 3)
				IPlayer.UpdateBuff(BuffNames::BOFChest, BuffNames::BuffTime, 0);
			else if (aItem.GetType() == 4 && !isItemSuit(aItem.CheckIndex()))
				IPlayer.UpdateBuff(BuffNames::BOFShort, BuffNames::BuffTime, 0);
			else if (aItem.GetType() == 5)
				IPlayer.UpdateBuff(BuffNames::BOFGloves, BuffNames::BuffTime, 0);
			else if (aItem.GetType() == 6)
				IPlayer.UpdateBuff(BuffNames::BOFBoots, BuffNames::BuffTime, 0);

			int BOFBoots = IPlayer.GetBuffValue(BuffNames::BOFBoots);
			int BOFShort = IPlayer.GetBuffValue(BuffNames::BOFShort);
			int BOFGloves = IPlayer.GetBuffValue(BuffNames::BOFGloves);
			int BOFChest = IPlayer.GetBuffValue(BuffNames::BOFChest);
			int BOFHelmet = IPlayer.GetBuffValue(BuffNames::BOFHelmet);
			int BOFHalfSet = IPlayer.GetBuffValue(BuffNames::BOFHalfSet);
			int BOFFullSet = IPlayer.GetBuffValue(BuffNames::BOFFullSet);

			if (BOFHalfSet && BOFHalfSet == 46)
			{
				if (BOFBoots != 46 || BOFShort != 46 || BOFGloves != 46)
				{
					IPlayer.UpdateBuff(BuffNames::BOFHalfSet, BuffNames::BuffTime, 0);
					IPlayer.RemoveAgi(1);
					IPlayer.RemoveStr(1);
					IPlayer.RemoveInt(1);
				}
			}

			if (BOFFullSet && BOFFullSet == 46)
			{
				if (BOFHalfSet != 46 || BOFChest != 46 || BOFHelmet != 46)
				{
					IPlayer.UpdateBuff(BuffNames::BOFFullSet, BuffNames::BuffTime, 0);
					IPlayer.RemoveAgi(1);
					IPlayer.RemoveStr(1);
					IPlayer.RemoveInt(1);
				}
			}

			if (BOFHalfSet && BOFHalfSet == 50)
			{
				if (BOFBoots != 50 || BOFShort != 50 || BOFGloves != 50)
				{
					IPlayer.UpdateBuff(BuffNames::BOFHalfSet, BuffNames::BuffTime, 0);
					IPlayer.RemoveAgi(2);
					IPlayer.RemoveStr(2);
					IPlayer.RemoveInt(2);
				}
			}

			if (BOFFullSet && BOFFullSet == 50)
			{
				if (BOFHalfSet != 50 || BOFChest != 50 || BOFHelmet != 50)
				{
					IPlayer.UpdateBuff(BuffNames::BOFFullSet, BuffNames::BuffTime, 0);
					IPlayer.RemoveAgi(2);
					IPlayer.RemoveStr(2);
					IPlayer.RemoveInt(2);
				}
			}

			if (BOFHalfSet && BOFHalfSet == 55)
			{
				if (BOFBoots != 55 || BOFShort != 55 || BOFGloves != 55)
				{
					IPlayer.UpdateBuff(BuffNames::BOFHalfSet, BuffNames::BuffTime, 0);
					IPlayer.RemoveAgi(3);
					IPlayer.RemoveStr(3);
					IPlayer.RemoveInt(3);
				}
			}

			if (BOFFullSet && BOFFullSet == 55)
			{
				if (BOFHalfSet != 55 || BOFChest != 55 || BOFHelmet != 55)
				{
					IPlayer.UpdateBuff(BuffNames::BOFFullSet, BuffNames::BuffTime, 0);
					IPlayer.RemoveAgi(3);
					IPlayer.RemoveStr(3);
					IPlayer.RemoveInt(3);
				}
			}

			if (BOFHalfSet && BOFHalfSet == 60)
			{
				if (BOFBoots != 60 || BOFShort != 60 || BOFGloves != 60)
				{
					IPlayer.UpdateBuff(BuffNames::BOFHalfSet, BuffNames::BuffTime, 0);
					IPlayer.RemoveAgi(4);
					IPlayer.RemoveStr(4);
					IPlayer.RemoveInt(4);
				}
			}

			if (BOFFullSet && BOFFullSet == 60)
			{
				if (BOFHalfSet != 60 || BOFChest != 60 || BOFHelmet != 60)
				{
					IPlayer.UpdateBuff(BuffNames::BOFFullSet, BuffNames::BuffTime, 0);
					IPlayer.RemoveAgi(4);
					IPlayer.RemoveStr(4);
					IPlayer.RemoveInt(4);
				}
			}

			if (BOFHalfSet && BOFHalfSet == 65)
			{
				if (BOFBoots != 65 || BOFShort != 65 || BOFGloves != 65)
				{
					IPlayer.UpdateBuff(BuffNames::BOFHalfSet, BuffNames::BuffTime, 0);
					IPlayer.RemoveAgi(5);
					IPlayer.RemoveStr(5);
					IPlayer.RemoveInt(5);
				}
			}

			if (BOFFullSet && BOFFullSet == 65)
			{
				if (BOFHalfSet != 65 || BOFChest != 65 || BOFHelmet != 65)
				{
					IPlayer.UpdateBuff(BuffNames::BOFFullSet, BuffNames::BuffTime, 0);
					IPlayer.RemoveAgi(5);
					IPlayer.RemoveStr(5);
					IPlayer.RemoveInt(5);
				}
			}

			if (BOFHalfSet && BOFHalfSet == 70)
			{
				if (BOFBoots != 70 || BOFShort != 70 || BOFGloves != 70)
				{
					IPlayer.UpdateBuff(BuffNames::BOFHalfSet, BuffNames::BuffTime, 0);
					IPlayer.RemoveAgi(6);
					IPlayer.RemoveStr(6);
					IPlayer.RemoveInt(6);
				}
			}

			if (BOFFullSet && BOFFullSet == 70)
			{
				if (BOFHalfSet != 70 || BOFChest != 70 || BOFHelmet != 70)
				{
					IPlayer.UpdateBuff(BuffNames::BOFFullSet, BuffNames::BuffTime, 0);
					IPlayer.RemoveAgi(6);
					IPlayer.RemoveStr(6);
					IPlayer.RemoveInt(6);
				}
			}

			if (BOFHalfSet && BOFHalfSet == 80)
			{
				if (BOFBoots != 80 || BOFShort != 80 || BOFGloves != 80)
				{
					IPlayer.UpdateBuff(BuffNames::BOFHalfSet, BuffNames::BuffTime, 0);
					IPlayer.RemoveAgi(7);
					IPlayer.RemoveStr(7);
					IPlayer.RemoveInt(7);
				}
			}

			if (BOFFullSet && BOFFullSet == 80)
			{
				if (BOFHalfSet != 80 || BOFChest != 80 || BOFHelmet != 80)
				{
					IPlayer.UpdateBuff(BuffNames::BOFFullSet, BuffNames::BuffTime, 0);
					IPlayer.RemoveAgi(7);
					IPlayer.RemoveStr(7);
					IPlayer.RemoveInt(7);
				}
			}

			if (BOFHalfSet && BOFHalfSet == 90)
			{
				if (BOFBoots != 90 || BOFShort != 90 || BOFGloves != 90)
				{
					IPlayer.UpdateBuff(BuffNames::BOFHalfSet, BuffNames::BuffTime, 0);
					IPlayer.RemoveAgi(8);
					IPlayer.RemoveStr(8);
					IPlayer.RemoveInt(8);
				}
			}

			if (BOFFullSet && BOFFullSet == 90)
			{
				if (BOFHalfSet != 90 || BOFChest != 90 || BOFHelmet != 90)
				{
					IPlayer.UpdateBuff(BuffNames::BOFFullSet, BuffNames::BuffTime, 0);
					IPlayer.RemoveAgi(8);
					IPlayer.RemoveStr(8);
					IPlayer.RemoveInt(8);
				}
			}

			if (BOFHalfSet && BOFHalfSet >= 95)
			{
				if (BOFBoots < 95 || BOFShort < 95 || BOFGloves < 95)
				{
					IPlayer.UpdateBuff(BuffNames::BOFHalfSet, BuffNames::BuffTime, 0);
					IPlayer.RemoveAgi(9);
					IPlayer.RemoveStr(9);
					IPlayer.RemoveInt(9);
				}
			}

			if (BOFFullSet && BOFFullSet >= 95)
			{
				if (BOFHalfSet < 95 || BOFChest < 95 || BOFHelmet < 95)
				{
					IPlayer.UpdateBuff(BuffNames::BOFFullSet, BuffNames::BuffTime, 0);
					IPlayer.RemoveAgi(9);
					IPlayer.RemoveStr(9);
					IPlayer.RemoveInt(9);
				}
			}
		}

		int def = IPlayer.GetDef();
		CItemDefense::PutOff(Item, Player);

		if (CItem::IsState((int)Item, 1))
			return;

		if (aItem.GetType() == -3 && IPlayer.GetBuffValue(2035)) {
			int Old = IPlayer.GetBuffValue(2035);
			IPlayer.UpdateBuff(2035, BuffNames::BuffTime, Old - 1);
			CPlayer::AddWState(Player, -3);
		}

		if (isItemSuit(aItem.CheckIndex())) {

			if (IPlayer.GetBuffValue(BuffNames::ArmorWears)) {
				ShowItem(IPlayer, BuffNames::ArmorWears);
				CPlayer::AddWState(Player, 4);
			}

			IPlayer.UpdateBuff(BuffNames::SuitsUsing, BuffNames::BuffTime, 0);
		}

		if (aItem.GetType() == 3) {
			if (isItemCostumeEffect(aItem.CheckIndex())) {
				int Effect = IPlayer.GetBuffValue(BuffNames::CostumeEffect);
				int Decrease = Effect % 1000;
				if (Decrease) {
					IPlayer.RemoveStr(Decrease);
					IPlayer.RemoveHp(Decrease);
					IPlayer.RemoveAgi(Decrease);
					IPlayer.RemoveWis(Decrease);
					IPlayer.RemoveInt(Decrease);
				}
				CChar::WriteInSight(IPlayer.GetOffset(), 0xFE, "ddd", 187, IPlayer.GetID(), Effect);
				IPlayer.UpdateBuff(BuffNames::CostumeEffect, BuffNames::BuffTime, 0);
			}
			else
				IPlayer.UpdateBuff(BuffNames::CostumeEffectCheck, BuffNames::BuffTime, 0);
	
			if(IPlayer.GetBuffValue(BuffNames::CostumeEffect) || IPlayer.GetBuffValue(BuffNames::CostumeEffectCheck))
				CPlayer::AddWState(Player, 3);
		}

		if (!isItemSuit(aItem.CheckIndex()) && aItem.GetType() == 4 && IPlayer.GetBuffValue(BuffNames::SuitsUsing))
			CPlayer::AddWState(Player, 4);

		int check = def - (IPlayer.GetDef() + *((DWORD *)Item + 27));

		itemStat.Enter();
		int ItemStat = GetItemStat.count(aItem.GetIID()) ? GetItemStat.find(aItem.GetIID())->second : 0;
		itemStat.Leave();
		if (ItemStat)
		{
			if (ItemStat > 0 && ItemStat <= 10 && isItemRidingArmor(aItem.CheckIndex())) {
				int index = aItem.CheckIndex();
				if (GetBattleRidingType(index) == 1) {
					if (index == 7883 || index == 7889 || index == 7895 || index == 7901)
						IPlayer.RemoveStr(RidingHelmet[GetBattleRidingGrade(index) - 1][ItemStat - 1]);
					else
						IPlayer.RemoveInt(RidingHelmet[GetBattleRidingGrade(index) - 1][ItemStat - 1]);
				}

				if (GetBattleRidingType(index) == 2)
					IPlayer.RemoveHp(RidingSaddle[GetBattleRidingGrade(index) - 1][ItemStat - 1]);
				if (GetBattleRidingType(index) == 3)
					IPlayer.RemoveDef(RidingArmor[GetBattleRidingGrade(index) - 1][ItemStat - 1]);
				if (GetBattleRidingType(index) == 4)
					IPlayer.RemoveAbsorb(RidingCloth[GetBattleRidingGrade(index) - 1][ItemStat - 1]);
				if (GetBattleRidingType(index) == 5)
					IPlayer.RemoveEva(RidingMagnet[GetBattleRidingGrade(index) - 1][ItemStat - 1]);

			}

			if (isItemSuit(aItem.CheckIndex()) && ItemStat) {
				int AddingType = SuitStats.count(aItem.CheckIndex()) ? SuitStats.find(aItem.CheckIndex())->second.Type : 0;
				int Multiply = SuitStats.count(aItem.CheckIndex()) ? SuitStats.find(aItem.CheckIndex())->second.Multiply : 3;

				if (Multiply < 2)
					Multiply = 2;

				switch (AddingType) {
				case 0:
					IPlayer.RemoveHp(ItemStat >= 6 ? (((ItemStat - 5) * Multiply) + 10) : ItemStat * (Multiply-1));
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

			int QigongType = ItemStat % 100;
			int DemonGongStyle = (ItemStat % 100000000) / 10000000;

			if (DemonGongStyle) {
				int DemonGrade = (ItemStat % 10000000) / 1000000;
				int Grade = DemonGrade + 1;

				if (DemonGongStyle == 1) {
					int def = 0, otp = 0;
					if (Grade == 1) {
						def = 2;
						otp = 1;
					}if (Grade == 2) {
						def = 4;
						otp = 1;
					}if (Grade == 3) {
						def = 6;
						otp = 2;
					}if (Grade == 4) {
						def = 8;
						otp = 2;
					}if (Grade == 5) {
						def = 10;
						otp = 2;
					}if (Grade == 6) {
						def = 12;
						otp = 3;
					}if (Grade == 7) {
						def = 15;
						otp = 3;
					}if (Grade == 8) {
						def = 18;
						otp = 3;
					}if (Grade == 9) {
						def = 21;
						otp = 3;
					}if (Grade == 10) {
						def = 26;
						otp = 4;
					}
					IPlayer.RemoveDef(def);
					IPlayer.RemoveOTP(otp);
				}
				if (DemonGongStyle == 2) {
					int hp = 0, eva = 0;
					if (Grade == 1) {
						hp = 50;
						eva = 1;
					}if (Grade == 2) {
						hp = 60;
						eva = 2;
					}if (Grade == 3) {
						hp = 80;
						eva = 2;
					}if (Grade == 4) {
						hp = 90;
						eva = 3;
					}if (Grade == 5) {
						hp = 100;
						eva = 3;
					}if (Grade == 6) {
						hp = 110;
						eva = 4;
					}if (Grade == 7) {
						hp = 130;
						eva = 4;
					}if (Grade == 8) {
						hp = 160;
						eva = 4;
					}if (Grade == 9) {
						hp = 190;
						eva = 5;
					}if (Grade == 10) {
						hp = 250;
						eva = 5;
					}
					IPlayer.DecreaseMaxHp(hp);
					IPlayer.RemoveEva(eva);
				}
				if (DemonGongStyle == 3) {
					int agi = 0, def = 0;
					if (Grade == 1) {
						agi = 1;
						def = 1;
					}if (Grade == 2) {
						agi = 2;
						def = 2;
					}if (Grade == 3) {
						agi = 2;
						def = 3;
					}if (Grade == 4) {
						agi = 2;
						def = 5;
					}if (Grade == 5) {
						agi = 3;
						def = 5;
					}if (Grade == 6) {
						agi = 3;
						def = 6;
					}if (Grade == 7) {
						agi = 3;
						def = 8;
					}if (Grade == 8) {
						agi = 4;
						def = 10;
					}if (Grade == 9) {
						agi = 4;
						def = 11;
					}if (Grade == 10) {
						agi = 5;
						def = 12;
					}
					IPlayer.RemoveAgi(agi);
					IPlayer.RemoveDef(def);
				}

			}
			if (QigongType)
			{
				if (aItem.GetType() == 3)
				{
					IPlayer.RemoveDef((check*QigongChest[QigongType - 1][0]) / 100);
					int Type = QigongChest[QigongType - 1][1];
					int Stat = QigongChest[QigongType - 1][2];

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
				else if (aItem.GetType() == 4)
				{
					IPlayer.RemoveDef((check*QigongShort[QigongType - 1][0]) / 100);
					int Type = QigongChest[QigongType - 1][1];
					int Stat = QigongChest[QigongType - 1][2];

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
				else {
					IPlayer.RemoveDef((check*QigongMain[QigongType - 1][0]) / 100);
					int Type = QigongChest[QigongType - 1][1];
					int Stat = QigongChest[QigongType - 1][2];

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
		}

		if (aItem.GetSetGem() == 240)
		{
			IPlayer.RemoveDef((check * 18) / 100);
			IPlayer.RemoveAgi(7);
		}
		else if (aItem.GetSetGem() == 239)
		{
			IPlayer.RemoveDef((check * 18) / 100);
			IPlayer.RemoveWis(7);
		}
		else if (aItem.GetSetGem() == 238)
		{
			IPlayer.RemoveDef((check * 18) / 100);
			IPlayer.RemoveInt(7);
		}
		else if (aItem.GetSetGem() == 237)
		{
			IPlayer.RemoveDef((check * 18) / 100);
			IPlayer.RemoveHp(7);
		}
		else if (aItem.GetSetGem() == 236)
		{
			IPlayer.RemoveDef((check * 18) / 100);
			IPlayer.RemoveStr(7);
		}
		else if (aItem.GetSetGem() == 235)
		{
			IPlayer.RemoveDef((check * 16) / 100);
			IPlayer.RemoveAgi(5);
		}
		else if (aItem.GetSetGem() == 234)
		{
			IPlayer.RemoveDef((check * 16) / 100);
			IPlayer.RemoveWis(5);
		}
		else if (aItem.GetSetGem() == 233)
		{
			IPlayer.RemoveDef((check * 16) / 100);
			IPlayer.RemoveInt(5);
		}
		else if (aItem.GetSetGem() == 232)
		{
			IPlayer.RemoveDef((check * 16) / 100);
			IPlayer.RemoveHp(5);
		}
		else if (aItem.GetSetGem() == 231)
		{
			IPlayer.RemoveDef((check * 16) / 100);
			IPlayer.RemoveStr(5);
		}
		else if (aItem.GetSetGem() == 230)
		{
			IPlayer.RemoveDef((check * 14) / 100);
			IPlayer.RemoveAgi(3);
		}
		else if (aItem.GetSetGem() == 229)
		{
			IPlayer.RemoveDef((check * 14) / 100);
			IPlayer.RemoveWis(3);
		}
		else if (aItem.GetSetGem() == 228)
		{
			IPlayer.RemoveDef((check * 14) / 100);
			IPlayer.RemoveInt(3);
		}
		else if (aItem.GetSetGem() == 227)
		{
			IPlayer.RemoveDef((check * 14) / 100);
			IPlayer.RemoveHp(3);
		}
		else if (aItem.GetSetGem() == 226)
		{
			IPlayer.RemoveDef((check * 14) / 100);
			IPlayer.RemoveStr(3);
		}
		else if (aItem.GetSetGem() == 225)
		{
			IPlayer.RemoveDef((check * 12) / 100);
			IPlayer.RemoveAgi(3);
		}
		else if (aItem.GetSetGem() == 224)
		{
			IPlayer.RemoveDef((check * 12) / 100);
			IPlayer.RemoveWis(3);
		}
		else if (aItem.GetSetGem() == 223)
		{
			IPlayer.RemoveDef((check * 12) / 100);
			IPlayer.RemoveInt(3);
		}
		else if (aItem.GetSetGem() == 222)
		{
			IPlayer.RemoveDef((check * 12) / 100);
			IPlayer.RemoveHp(3);
		}
		else if (aItem.GetSetGem() == 221)
		{
			IPlayer.RemoveDef((check * 12) / 100);
			IPlayer.RemoveStr(3);
		}
		else if (aItem.GetSetGem() == 220)
		{
			IPlayer.RemoveDef((check * 10) / 100);
			IPlayer.RemoveAgi(2);
		}
		else if (aItem.GetSetGem() == 219)
		{
			IPlayer.RemoveDef((check * 10) / 100);
			IPlayer.RemoveWis(2);
		}
		else if (aItem.GetSetGem() == 218)
		{
			IPlayer.RemoveDef((check * 10) / 100);
			IPlayer.RemoveInt(2);
		}
		else if (aItem.GetSetGem() == 217)
		{
			IPlayer.RemoveDef((check * 10) / 100);
			IPlayer.RemoveHp(2);
		}
		else if (aItem.GetSetGem() == 216)
		{
			IPlayer.RemoveDef((check * 10) / 100);
			IPlayer.RemoveStr(2);
		}
		else if (aItem.GetSetGem() == 215)
		{
			IPlayer.RemoveDef((check * 8) / 100);
			IPlayer.RemoveAgi(2);
		}
		else if (aItem.GetSetGem() == 214)
		{
			IPlayer.RemoveDef((check * 8) / 100);
			IPlayer.RemoveWis(2);
		}
		else if (aItem.GetSetGem() == 213)
		{
			IPlayer.RemoveDef((check * 8) / 100);
			IPlayer.RemoveInt(2);
		}
		else if (aItem.GetSetGem() == 212)
		{
			IPlayer.RemoveDef((check * 8) / 100);
			IPlayer.RemoveHp(2);
		}
		else if (aItem.GetSetGem() == 211)
		{
			IPlayer.RemoveDef((check * 8) / 100);
			IPlayer.RemoveStr(2);
		}
		else if (aItem.GetSetGem() == 210)
		{
			IPlayer.RemoveDef((check * 6) / 100);
			IPlayer.RemoveAgi(1);
		}
		else if (aItem.GetSetGem() == 209)
		{
			IPlayer.RemoveDef((check * 6) / 100);
			IPlayer.RemoveWis(1);
		}
		else if (aItem.GetSetGem() == 208)
		{
			IPlayer.RemoveDef((check * 6) / 100);
			IPlayer.RemoveInt(1);
		}
		else if (aItem.GetSetGem() == 207)
		{
			IPlayer.RemoveDef((check * 6) / 100);
			IPlayer.RemoveHp(1);
		}
		else if (aItem.GetSetGem() == 206)
		{
			IPlayer.RemoveDef((check * 6) / 100);
			IPlayer.RemoveStr(1);
		}
		else if (aItem.GetSetGem() == 205)
		{
			IPlayer.RemoveDef((check * 4) / 100);
			IPlayer.RemoveAgi(1);
		}
		else if (aItem.GetSetGem() == 204)
		{
			IPlayer.RemoveDef((check * 4) / 100);
			IPlayer.RemoveWis(1);
		}
		else if (aItem.GetSetGem() == 203)
		{
			IPlayer.RemoveDef((check * 4) / 100);
			IPlayer.RemoveInt(1);
		}
		else if (aItem.GetSetGem() == 202)
		{
			IPlayer.RemoveDef((check * 4) / 100);
			IPlayer.RemoveHp(1);
		}
		else if (aItem.GetSetGem() == 201)
		{
			IPlayer.RemoveDef((check * 4) / 100);
			IPlayer.RemoveStr(1);
		}
	}

}