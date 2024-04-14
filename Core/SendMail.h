void __fastcall MAILProcess(void *Player, void *edx, int Type, int pPacket, int pPos)
{
	IChar IPlayer(Player);
	if (IPlayer.IsOnline() && Type == 0) {

		if (IPlayer.IsBuff(BuffNames::SendMailResult)) {
			IPlayer.SystemMessage("Please try again in a few seconds.", TEXTCOLOR_YELLOW);
			IPlayer.Buff(BuffNames::SendMailResult, 7, 0);
			return;
		}

		if (!CPlayer::FindItem(Player, 31, 5)) {
			IPlayer.SystemMessage("Not enough money.", TEXTCOLOR_YELLOW);
			return;
		}

		char Msg[512] = { 0 };
		unsigned char vVal = 0;
		int Check = CPacket::Read((char *)pPacket, (char *)pPos, "bs", &vVal, &Msg, 513);
		if (vVal == 1) {
			if (!CPlayer::FindItem(Player, 31, 100)) {
				IPlayer.SystemMessage("Not enough money.", TEXTCOLOR_YELLOW);
				return;
			}
		}

		IPlayer.Buff(BuffNames::SendMailResult, 10, 0);
	}

	if (IPlayer.IsOnline() && Type == 7)
	{
		int Check = 0, nMID = 0, nIID = 0; char byMType = 0; unsigned __int16 wLen = 0; char Msg[512] = { 0 };

		Check = CPacket::xRead((void *)pPacket, "dbdw", &nMID, &byMType, &nIID, &wLen);
		Check = CPacket::xRead((void *)Check, "m", &Msg, wLen);

		if (nIID) {
			Interface<ITools> Tools;
			unsigned short Index;
			unsigned char Prefix;
			unsigned long Info, Amount;
			unsigned char MaxEnd, CurEnd, SetGem, XAtk, XMagic, XDefense, XHit, XEvasion;
			unsigned short XProtect;
			unsigned char UpgrLevel, Upgrrate;

			CPacket::xRead((char*)Check, "wbddbbbbbbbbbbb", &Index, &Prefix, &Info, &Amount, &MaxEnd, &CurEnd, &SetGem, &XAtk,
				&XMagic, &XDefense, &XHit, &XEvasion, &XProtect, &UpgrLevel, &Upgrrate);
			
			if (Index > 0)
			{
				char Packet[67] = { 0 };
				unsigned char x = 0, y = 0, z = 0, dsstype = 0, eva = 0, otp = 0, hpinc = 0, mpinc = 0, str = 0, hp = 0, intel = 0, wis = 0, agi = 0, a = 0, dg1stat = 0, dg1type = 0, dg2stat = 0, dg2type = 0, PerfShotCheck = 0;
				unsigned long remaintime = 0, QigongGrade = 0;
				unsigned short phyatk = 0, magatk = 0, def = 0, absorb = 0;

				int ItemStat = 0;
				itemStat.Enter();
				if (GetItemStat.count(nIID))
					ItemStat = GetItemStat.find(nIID)->second;
				itemStat.Leave();

				int GetStat = ItemStat;
				int MakeItem = CItem::CreateItem(Index, 0, 1, -1);

				if (MakeItem)
				{
					IItem IItem((void*)MakeItem);

					if (IItem.GetType() == -2 || IItem.GetType() == 19 || IItem.GetType() == 0 || IItem.GetType() == -3 || IItem.GetType() == -1)
					{
						if (SetGem == 240)
						{
							dsstype = 1; phyatk = 17; magatk = 17; agi = 8;
							hpinc = 250; mpinc = 200;
							if (IItem.GetType() == -1) eva = 18; else otp = 18;
						}
						else if (SetGem == 239)
						{
							dsstype = 1; phyatk = 17; magatk = 17; wis = 8;
							hpinc = 250; mpinc = 200;
							if (IItem.GetType() == -1) eva = 18; else otp = 18;
						}
						else if (SetGem == 238)
						{
							dsstype = 1; phyatk = 17; magatk = 17; intel = 8;
							hpinc = 250; mpinc = 200;
							if (IItem.GetType() == -1) eva = 18; else otp = 18;
						}
						else if (SetGem == 237)
						{
							dsstype = 1; phyatk = 17; magatk = 17; hp = 8;
							hpinc = 250; mpinc = 200;
							if (IItem.GetType() == -1) eva = 18; else otp = 18;
						}
						else if (SetGem == 236)
						{
							dsstype = 1; phyatk = 17; magatk = 17; str = 8;
							hpinc = 250; mpinc = 200;
							if (IItem.GetType() == -1) eva = 18; else otp = 18;
						}
						else if (SetGem == 235)
						{
							dsstype = 2; phyatk = 14; magatk = 14; agi = 5;
							hpinc = 200; mpinc = 150;
							if (IItem.GetType() == -1) eva = 15; else otp = 15;
						}
						else if (SetGem == 234)
						{
							dsstype = 2; phyatk = 14; magatk = 14; wis = 5;
							hpinc = 200; mpinc = 150;
							if (IItem.GetType() == -1) eva = 15; else otp = 15;
						}
						else if (SetGem == 233)
						{
							dsstype = 2; phyatk = 14; magatk = 14; intel = 5;
							hpinc = 200; mpinc = 150;
							if (IItem.GetType() == -1) eva = 15; else otp = 15;
						}
						else if (SetGem == 232)
						{
							dsstype = 2; phyatk = 14; magatk = 14; hp = 5;
							hpinc = 200; mpinc = 150;
							if (IItem.GetType() == -1) eva = 15; else otp = 15;
						}
						else if (SetGem == 231)
						{
							dsstype = 2; phyatk = 14; magatk = 14; str = 5;
							hpinc = 200; mpinc = 150;
							if (IItem.GetType() == -1) eva = 15; else otp = 15;
						}
						else if (SetGem == 230)
						{
							dsstype = 3; phyatk = 12; magatk = 12; agi = 3;
							hpinc = 130; mpinc = 110;
							if (IItem.GetType() == -1) eva = 12; else otp = 12;
						}
						else if (SetGem == 229)
						{
							dsstype = 3; phyatk = 12; magatk = 12; wis = 3;
							hpinc = 130; mpinc = 110;
							if (IItem.GetType() == -1) eva = 12; else otp = 12;
						}
						else if (SetGem == 228)
						{
							dsstype = 3; phyatk = 12; magatk = 12; intel = 3;
							hpinc = 130; mpinc = 110;
							if (IItem.GetType() == -1) eva = 12; else otp = 12;
						}
						else if (SetGem == 227)
						{
							dsstype = 3; phyatk = 12; magatk = 12; hp = 3;
							hpinc = 130; mpinc = 110;
							if (IItem.GetType() == -1) eva = 12; else otp = 12;
						}
						else if (SetGem == 226)
						{
							dsstype = 3; phyatk = 12; magatk = 12; str = 3;
							hpinc = 130; mpinc = 110;
							if (IItem.GetType() == -1) eva = 12; else otp = 12;
						}
						else if (SetGem == 225)
						{
							dsstype = 4; phyatk = 10; magatk = 10; agi = 3;
							hpinc = 110; mpinc = 90;
							if (IItem.GetType() == -1) eva = 10; else otp = 10;
						}
						else if (SetGem == 224)
						{
							dsstype = 4; phyatk = 10; magatk = 10; wis = 3;
							hpinc = 110; mpinc = 90;
							if (IItem.GetType() == -1) eva = 10; else otp = 10;
						}
						else if (SetGem == 223)
						{
							dsstype = 4; phyatk = 10; magatk = 10; intel = 3;
							hpinc = 110; mpinc = 90;
							if (IItem.GetType() == -1) eva = 10; else otp = 10;
						}
						else if (SetGem == 222)
						{
							dsstype = 4; phyatk = 10; magatk = 10; hp = 3;
							hpinc = 110; mpinc = 90;
							if (IItem.GetType() == -1) eva = 10; else otp = 10;
						}
						else if (SetGem == 221)
						{
							dsstype = 4; phyatk = 10; magatk = 10; str = 3;
							hpinc = 110; mpinc = 90;
							if (IItem.GetType() == -1) eva = 10; else otp = 10;
						}
						else if (SetGem == 220)
						{
							dsstype = 5; phyatk = 8; magatk = 8; agi = 2;
							hpinc = 90; mpinc = 70;
							if (IItem.GetType() == -1) eva = 8; else otp = 8;
						}
						else if (SetGem == 219)
						{
							dsstype = 5; phyatk = 8; magatk = 8; wis = 2;
							hpinc = 90; mpinc = 70;
							if (IItem.GetType() == -1) eva = 8; else otp = 8;
						}
						else if (SetGem == 218)
						{
							dsstype = 5; phyatk = 8; magatk = 8; intel = 2;
							hpinc = 90; mpinc = 70;
							if (IItem.GetType() == -1) eva = 8; else otp = 8;
						}
						else if (SetGem == 217)
						{
							dsstype = 5; phyatk = 8; magatk = 8; hp = 2;
							hpinc = 90; mpinc = 70;
							if (IItem.GetType() == -1) eva = 8; else otp = 8;
						}
						else if (SetGem == 216)
						{
							dsstype = 5; phyatk = 8; magatk = 8; str = 2;
							hpinc = 90; mpinc = 70;
							if (IItem.GetType() == -1) eva = 8; else otp = 8;
						}
						else if (SetGem == 215)
						{
							dsstype = 6; phyatk = 6; magatk = 6; agi = 2;
							hpinc = 70; mpinc = 50;
							if (IItem.GetType() == -1) eva = 6; else otp = 6;
						}
						else if (SetGem == 214)
						{
							dsstype = 6; phyatk = 6; magatk = 6; wis = 2;
							hpinc = 70; mpinc = 50;
							if (IItem.GetType() == -1) eva = 6; else otp = 6;
						}
						else if (SetGem == 213)
						{
							dsstype = 6; phyatk = 6; magatk = 6; intel = 2;
							hpinc = 70; mpinc = 50;
							if (IItem.GetType() == -1) eva = 6; else otp = 6;
						}
						else if (SetGem == 212)
						{
							dsstype = 6; phyatk = 6; magatk = 6; hp = 2;
							hpinc = 70; mpinc = 50;
							if (IItem.GetType() == -1) eva = 6; else otp = 6;
						}
						else if (SetGem == 211)
						{
							dsstype = 6; phyatk = 6; magatk = 6; str = 2;
							hpinc = 70; mpinc = 50;
							if (IItem.GetType() == -1) eva = 6; else otp = 6;
						}
						else if (SetGem == 210)
						{
							dsstype = 7; phyatk = 4; magatk = 4; agi = 1;
							hpinc = 50; mpinc = 30;
							if (IItem.GetType() == -1) eva = 4; else otp = 4;
						}
						else if (SetGem == 209)
						{
							dsstype = 7; phyatk = 4; magatk = 4; wis = 1;
							hpinc = 50; mpinc = 30;
							if (IItem.GetType() == -1) eva = 4; else otp = 4;
						}
						else if (SetGem == 208)
						{
							dsstype = 7; phyatk = 4; magatk = 4; intel = 1;
							hpinc = 50; mpinc = 30;
							if (IItem.GetType() == -1) eva = 4; else otp = 4;
						}
						else if (SetGem == 207)
						{
							dsstype = 7; phyatk = 4; magatk = 4; hp = 1;
							hpinc = 50; mpinc = 30;
							if (IItem.GetType() == -1) eva = 4; else otp = 4;
						}
						else if (SetGem == 206)
						{
							dsstype = 7; phyatk = 4; magatk = 4; str = 1;
							hpinc = 50; mpinc = 30;
							if (IItem.GetType() == -1) eva = 4; else otp = 4;
						}
						else if (SetGem == 205)
						{
							dsstype = 8; phyatk = 2; magatk = 2; agi = 1;
							hpinc = 30; mpinc = 10;
							if (IItem.GetType() == -1) eva = 2; else otp = 2;
						}
						else if (SetGem == 204)
						{
							dsstype = 8; phyatk = 2; magatk = 2; wis = 1;
							hpinc = 30; mpinc = 10;
							if (IItem.GetType() == -1) eva = 2; else otp = 2;
						}
						else if (SetGem == 203)
						{
							dsstype = 8; phyatk = 2; magatk = 2; intel = 1;
							hpinc = 30; mpinc = 10;
							if (IItem.GetType() == -1) eva = 2; else otp = 2;
						}
						else if (SetGem == 202)
						{
							dsstype = 8; phyatk = 2; magatk = 2; hp = 1;
							hpinc = 30; mpinc = 10;
							if (IItem.GetType() == -1) eva = 2; else otp = 2;
						}
						else if (SetGem == 201)
						{
							dsstype = 8; phyatk = 2; magatk = 2; str = 1;
							hpinc = 30; mpinc = 10;
							if (IItem.GetType() == -1) eva = 2; else otp = 2;
						}
					}

					if (IItem.GetType() >= 1 && IItem.GetType() <= 6)
					{
						if (SetGem == 240)
						{
							dsstype = 1; def = 18; agi = 7;
						}
						else if (SetGem == 239)
						{
							dsstype = 1; def = 18; wis = 7;
						}
						else if (SetGem == 238)
						{
							dsstype = 1; def = 18; intel = 7;
						}
						else if (SetGem == 237)
						{
							dsstype = 1; def = 18; hp = 7;
						}
						else if (SetGem == 236)
						{
							dsstype = 1; def = 18; str = 7;
						}
						else if (SetGem == 235)
						{
							dsstype = 2; def = 16; agi = 5;
						}
						else if (SetGem == 234)
						{
							dsstype = 2; def = 16; wis = 5;
						}
						else if (SetGem == 233)
						{
							dsstype = 2; def = 16; intel = 5;
						}
						else if (SetGem == 232)
						{
							dsstype = 2; def = 16; hp = 5;
						}
						else if (SetGem == 231)
						{
							dsstype = 2; def = 16; str = 5;
						}
						else if (SetGem == 230)
						{
							dsstype = 3; def = 14; agi = 3;
						}
						else if (SetGem == 229)
						{
							dsstype = 3; def = 14; wis = 3;
						}
						else if (SetGem == 228)
						{
							dsstype = 3; def = 14; intel = 3;
						}
						else if (SetGem == 227)
						{
							dsstype = 3; def = 14; hp = 3;
						}
						else if (SetGem == 226)
						{
							dsstype = 3; def = 14; str = 3;
						}
						else if (SetGem == 225)
						{
							dsstype = 4; def = 12; agi = 3;
						}
						else if (SetGem == 224)
						{
							dsstype = 4; def = 12; wis = 3;
						}
						else if (SetGem == 223)
						{
							dsstype = 4; def = 12; intel = 3;
						}
						else if (SetGem == 222)
						{
							dsstype = 4; def = 12; hp = 3;
						}
						else if (SetGem == 221)
						{
							dsstype = 4; def = 12; str = 3;
						}
						else if (SetGem == 220)
						{
							dsstype = 5; def = 10; agi = 2;
						}
						else if (SetGem == 219)
						{
							dsstype = 5; def = 10; wis = 2;
						}
						else if (SetGem == 218)
						{
							dsstype = 5; def = 10; intel = 2;
						}
						else if (SetGem == 217)
						{
							dsstype = 5; def = 10; hp = 2;
						}
						else if (SetGem == 216)
						{
							dsstype = 5; def = 10; str = 2;
						}
						else if (SetGem == 215)
						{
							dsstype = 6; def = 8; agi = 2;
						}
						else if (SetGem == 214)
						{
							dsstype = 6; def = 8; wis = 2;
						}
						else if (SetGem == 213)
						{
							dsstype = 6; def = 8; intel = 2;
						}
						else if (SetGem == 212)
						{
							dsstype = 6; def = 8; hp = 2;
						}
						else if (SetGem == 211)
						{
							dsstype = 6; def = 8; str = 2;
						}
						else if (SetGem == 210)
						{
							dsstype = 7; def = 6; agi = 1;
						}
						else if (SetGem == 209)
						{
							dsstype = 7; def = 6; wis = 1;
						}
						else if (SetGem == 208)
						{
							dsstype = 7; def = 6; intel = 1;
						}
						else if (SetGem == 207)
						{
							dsstype = 7; def = 6; hp = 1;
						}
						else if (SetGem == 206)
						{
							dsstype = 7; def = 6; str = 1;
						}
						else if (SetGem == 205)
						{
							dsstype = 8; def = 4; agi = 1;
						}
						else if (SetGem == 204)
						{
							dsstype = 8; def = 4; wis = 1;
						}
						else if (SetGem == 203)
						{
							dsstype = 8; def = 4; intel = 1;
						}
						else if (SetGem == 202)
						{
							dsstype = 8; def = 4; hp = 1;
						}
						else if (SetGem == 201)
						{
							dsstype = 8; def = 4; str = 1;
						}
					}

					CBase::Delete((void*)MakeItem);
				}

				if (index >= 3381 && index <= 3383)
				{
					CPlayer::Write(Player, 194, "dd", nIID, 100);
					if (index == 3381) CPlayer::Write(Player, 193, "ddd", nIID, 101, 10);
					if (index == 3382) CPlayer::Write(Player, 193, "ddd", nIID, 101, 11);
					if (index == 3383) CPlayer::Write(Player, 193, "ddd", nIID, 101, 12);

					if (index == 3383 && !GetStat)
						CPlayer::Write(Player, 193, "ddd", nIID, 100, GetStat + 2);
					else
						CPlayer::Write(Player, 193, "ddd", nIID, 100, GetStat + 1);
				}

				if (Index >= 3384 && Index <= 3386)
				{
					if (GetStat)
					{
						int Stat = GetStat / 1000;
						int Value = GetStat % 100;
						CPlayer::Write(Player, 194, "dd", nIID, Value);
						CPlayer::Write(Player, 193, "ddd", nIID, Value, Stat);
					}
				}

				if (ItemStat)
				{
					PerfShotCheck = ItemStat / 100000000;
					ItemStat -= (100000000 * PerfShotCheck);
				}

				if (ItemStat)
				{
					int dg1typecheck = ItemStat / 10000000;
					if (dg1typecheck) dg1stat = 1;
					if (dg1typecheck > 0) dg1type = (dg1typecheck - 1);
					ItemStat -= (10000000 * dg1typecheck);
				}

				if (ItemStat)
				{
					int dg1statcheck = ItemStat / 1000000;
					if (dg1statcheck > 0) dg1stat = (dg1statcheck + 1);
					ItemStat -= (1000000 * dg1statcheck);
				}

				if (ItemStat)
				{
					int dg2typecheck = ItemStat / 100000;
					if (dg2typecheck) dg2stat = 1;
					if (dg2typecheck > 0) dg2type = (dg2typecheck - 1);
					ItemStat -= (100000 * dg2typecheck);
				}

				if (ItemStat)
				{
					int dg2statcheck = ItemStat / 10000;
					if (dg2statcheck > 0) dg2stat = (dg2statcheck + 1);
					ItemStat -= (10000 * dg2statcheck);
				}

				if (ItemStat && Index >= 2986 && Index <= 3009)
				{
					int yinyanggrade = ItemStat / 100;
					Prefix = yinyanggrade + 1;
					ItemStat -= (100 * yinyanggrade);
				}

				if (ItemStat)
					QigongGrade = ItemStat % 100;

				if (Index >= 3199 && Index <= 3201 && Prefix == 0)
					Prefix = 1;

				if (Index >= 2986 && Index <= 3009 && Prefix == 0)
					Prefix = 1;

				if (Index >= 3018 && Index <= 3020 && GetStat)
					Prefix = GetStat / 1000;

				int refill = 0;
				if (Index == 9979 || Index == 9963) {
					if (GetStat)
						refill = GetStat;
				}

				if (isItemCustomWeapon(Index))
					UpgrLevel = GetStat;

				if (isItemRidingArmor(Index)) {
					UpgrLevel = GetStat;
					if (GetStat > 0 && GetStat <= 10) {
						if (GetBattleRidingType(Index) == 1) {
							if (Index == 7883 || Index == 7889 || Index == 7895 || Index == 7901)
								str += RidingHelmet[GetBattleRidingGrade(Index) - 1][GetStat - 1];
							else
								intel += RidingHelmet[GetBattleRidingGrade(Index) - 1][GetStat - 1];
						}
						if (GetBattleRidingType(Index) == 2)
							hp += RidingSaddle[GetBattleRidingGrade(Index) - 1][GetStat - 1];
						if (GetBattleRidingType(Index) == 3)
							XDefense += RidingArmor[GetBattleRidingGrade(Index) - 1][GetStat - 1];
						if (GetBattleRidingType(Index) == 4)
							XDefense += RidingCloth[GetBattleRidingGrade(Index) - 1][GetStat - 1];
						if (GetBattleRidingType(Index) == 5)
							eva += RidingMagnet[GetBattleRidingGrade(Index) - 1][GetStat - 1];
					}
				}

				int restorecount = RestoredIIDs.findExists(nIID);

				int dg1 = (dg1type << 24) + (dg1stat << 16);
				int dg2 = (dg2type << 24) + (dg2stat << 16);

				remaintime = PetLifeCheck.findExists(nIID);
				if (remaintime)
					remaintime -= (int)time(0);

				Tools->Compile(Packet, "wdbddbbbbbbbbwbbdbbbbwwwwbbbbbbbbbbwddd", Index, nIID, Prefix, Info, Amount, MaxEnd, CurEnd, SetGem, XAtk, XMagic, XDefense, XHit, XEvasion, XProtect, UpgrLevel, Upgrrate, remaintime, x, y, restorecount, dsstype, phyatk, magatk, def, absorb, eva, otp, hpinc, mpinc, str, hp, intel, wis, agi, PerfShotCheck, QigongGrade, dg1, dg2, refill);
				CPlayer::Write(Player, 19, "bdbdwmm", 2, nMID, byMType, nIID, wLen, &Msg, wLen, Packet, 67);
				return;
			}
		}
	}

	CPlayer::MAILProcess(Player,Type,pPacket,pPos); 
}

int __fastcall SendMail(void* Player, void *edx, int a1, int a2, char* ReceiverName, const char *Message, int a5, int IID, int Index, int Prefix, int Amount, int Price)
{
	IChar IPlayer(Player);

	if (IID) {
		itemStat.Enter();
		int ItemStatOld = GetItemStat.count(IID) ? GetItemStat.find(IID)->second : 0;
		itemStat.Leave();

		if (ItemStatOld)
			ItemStatDisable.insert(IID);

		if (PetLifeCheck.count(IID))
			ItemTimerDisable.insert(IID);
	}

	if (IPlayer.IsOnline())
	{
		if (IPlayer.GetLevel() < 11 && a2 != 3) {
			IPlayer.SystemMessage("You must be atleast Level 11 to use this system.", TEXTCOLOR_YELLOW);
			return 0;
		}

		if (IPlayer.IsBuff(1973)) {
			if (a2 != 3) {
				IPlayer.SystemMessage("Please Allow " + Int2String(IPlayer.GetBuffRemain(1973)) + " seconds to send another message.", TEXTCOLOR_YELLOW);
				return 0;
			}
		}
		else {
			IPlayer.Buff(1973, 20, 0);
		}


		if (Restri && Restrictions.count(IPlayer.GetPID()) && Restrictions.find(IPlayer.GetPID())->second.Mail == 0 && Index != 0) {
			IPlayer.SystemMessage("You are not allowed to be using this system.", TEXTCOLOR_RED);
			return 0;
		}

		if (IPlayer.IsBuff(BuffNames::Jail)){
			IPlayer.SystemMessage("You can not send messages while you're in jail!", TEXTCOLOR_RED);
			return 0;
		}
		
		if (Index == 31 && Price > 0)
		{
			IPlayer.SystemMessage("You can not send geons with price!", TEXTCOLOR_RED);
			return 0;
		}

		if (EFakePlayers && FakeNames.count(ReceiverName)){
			if(CPlayer::RemoveItem(Player,9,31,5))
				IPlayer.SystemMessage("The message is sent to "+(std::string)ReceiverName+".",TEXTCOLOR_BLUE);
			return 0;
		}

	}
	return CPlayer::SendMail(Player, a1, a2, ReceiverName, Message, a5, IID, Index, Prefix, Amount, Price);
}