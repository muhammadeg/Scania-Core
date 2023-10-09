void* __fastcall InitChar(void* Player, void *edx) {
	void *v1; // ST0C_4@1

	v1 = Player;
	CBase::CBase(Player);
	*(DWORD *)v1 = (0x004B4B10);
	CIOCriticalSection::Init((struct _RTL_CRITICAL_SECTION *)((char *)v1 + 364));
	CIOCriticalSection::Init((struct _RTL_CRITICAL_SECTION *)((char *)v1 + 396));
	*((DWORD *)v1 + 88) = 0;
	*((DWORD *)v1 + 89) = 0;
	memset((char *)v1 + 32, 0, 0x19u);
	*((DWORD *)v1 + 15) = 0;
	memset((char *)v1 + 64, 0, 0x1Cu);
	memset((char *)v1 + 92, 0, 0x60u);
	memset((char *)v1 + 188, 0, 0x54u);
	*((DWORD *)v1 + 68) = 0;
	*((DWORD *)v1 + 69) = 0;
	*((DWORD *)v1 + 70) = 0;
	*((DWORD *)v1 + 72) = 0;
	*((DWORD *)v1 + 73) = 0;
	*((DWORD *)v1 + 74) = 0;
	*((DWORD *)v1 + 76) = 0;
	*((DWORD *)v1 + 77) = 0;
	*((DWORD *)v1 + 78) = 0;
	*((DWORD *)v1 + 79) = 0;
	*((DWORD *)v1 + 80) = 0;
	*((DWORD *)v1 + 82) = -1;
	*((DWORD *)v1 + 81) = -1;
	*((DWORD *)v1 + 84) = -1;
	*((DWORD *)v1 + 83) = -1;
	*((DWORD *)v1 + 85) = -1;
	*((DWORD *)v1 + 86) = 0;
	*((DWORD *)v1 + 87) = 1;
	*((DWORD *)v1 + 90) = 0;

	return v1;
}

void* __fastcall InitPlayer(void *PlayerOffset, void *edx, int Socket, int UID, int PID)
{
	void* Player = CPlayer::CPlayer(PlayerOffset, Socket, UID, PID);

	for (int i = 1684; i <= PlayerProperty::MaxSize - 4; i += 4)
		*(DWORD*)((int)Player + i) = 0;

	/*
	*(DWORD*)((int)Player + 1720) = (int)new int[124];
	memset((void*)*(DWORD*)((int)Player + 1720), 0, 124);
	*(DWORD*)((int)Player + 1724) = 0;
	*/

	return Player;
}

int __fastcall IntoInventory(void *Player, void *edx, int Item)
{
	int Check = CPlayer::_IntoInven(Player, Item);

	if (Check)
	{
		int IID = *(DWORD*)(Item + 36);
		int PetLife = PetLifeCheck.findExists(IID);
		if (PetLife) {
			*(DWORD*)(Item + 68) = GetTickCount() + (2000 * abs(PetLife - (int)time(0)));
			*(DWORD*)(Item + 72) = 0;
			CItem::OnTimer(Item, 0);
		}

		if (InvCheck.count(*(DWORD *)(*(DWORD *)(Item + 40) + 64))) {
			IChar IPlayer((void*)Player);
			IPlayer.IncrProperty(PlayerProperty::InventoryCheck);
		}
	}

	return Check;
}

int __fastcall OutOfInventory(void *Player, void *edx, int Item)
{
	if (InvCheck.count(*(DWORD *)(*(DWORD *)(Item + 40) + 64))) {
		IChar IPlayer((void*)Player);
		IPlayer.DecrProperty(PlayerProperty::InventoryCheck);
	}

	return CPlayer::_OutOfInven(Player, Item);
}

int __fastcall OnLoadPlayer(void *Player, void *edx, int Value)
{
	IChar IPlayer(Player);

	if (IPlayer.IsOnline())
	{
		InterlockedIncrement(&OnlinePlayers);
		PlayerOffset.replaceInsert(IPlayer.GetPID(), (int)Player);

		CPlayer::Write(Player, 204, "d", 0);
		CPlayer::Write(Player, 0xFF, "dd", 238, 128);
	}

	int Check = CPlayer::OnLoadPlayer(Player,Value);

	if (IPlayer.IsOnline() && Check)
	{
		PlayerOffset.erase(IPlayer.GetPID());
		IPlayer.UpdateBuff(BuffNames::MD5Hash, BuffNames::BuffTime, GetTickCount() + 300000);
		IPlayer.SetRefreshCheck(0);
		CDBSocket::Write(82,"d",IPlayer.GetPID());
		CDBSocket::Write(84, "d", IPlayer.GetPID());
		
		if (PeaceEvil) {
			int SQuest = (SlytherinQuest << 16) + 1;
			bool checkFlag = CPlayer::CheckQuestFlag((int)Player, SQuest);
			int RQuest = (RavenQuest << 16) + 1;
			bool checkFlagR = CPlayer::CheckQuestFlag((int)Player, RQuest);
			int HQuest = (HuffleQuest << 16) + 1;
			bool checkFlagH = CPlayer::CheckQuestFlag((int)Player, HQuest);
			int GQuest = (GryffindorQuest << 16) + 1;
			bool checkFlagG = CPlayer::CheckQuestFlag((int)Player, GQuest);

			if (checkFlag) {
				IPlayer.Buff(BuffNames::Slytherin, BuffNames::BuffTime, 1);
				IPlayer.Buff(BuffNames::NamePad, BuffNames::BuffTime, SlytherinColor);
			}
			else if (checkFlagR){
				IPlayer.Buff(BuffNames::Ravenclaw, BuffNames::BuffTime, 1);
				IPlayer.Buff(BuffNames::NamePad, BuffNames::BuffTime, RavenColor);

			}
			else if (checkFlagH){
				IPlayer.Buff(BuffNames::Hufflepuff, BuffNames::BuffTime, 1);
				IPlayer.Buff(BuffNames::NamePad, BuffNames::BuffTime, HuffleColor);

			}
			else {
				IPlayer.Buff(BuffNames::NamePad, BuffNames::BuffTime, GryffindorColor);
				IPlayer.Buff(BuffNames::Gryffindor, BuffNames::BuffTime, 1);
			}

			IPlayer.Buff(BuffNames::EPEvent, BuffNames::BuffTime, GetTickCount() + (TimerEP * 1000));
		}

		if (GuildColors)
			IPlayer.GuildColor();



		if (IPlayer.GetClass() == 3 && IPlayer.GetStr() < 14 && IPlayer.GetLevel() == 1)
		{
			IPlayer.IncreaseStat(14,0);
			CDBSocket::Write(16,"dbwbb",IPlayer.GetPID(),23,IPlayer.GetStatPoint(),0,*(DWORD *)((int)Player + 4 * 0 + 64));
			IPlayer.IncreaseStat(10,1); 
			CDBSocket::Write(16,"dbwbb",IPlayer.GetPID(),23,IPlayer.GetStatPoint(),1,*(DWORD *)((int)Player + 4 * 1 + 64));
			IPlayer.IncreaseStat(8,2);
			CDBSocket::Write(16,"dbwbb",IPlayer.GetPID(),23,IPlayer.GetStatPoint(),2,*(DWORD *)((int)Player + 4 * 2 + 64));
			IPlayer.IncreaseStat(5,3);
			CDBSocket::Write(16,"dbwbb",IPlayer.GetPID(),23,IPlayer.GetStatPoint(),3,*(DWORD *)((int)Player + 4 * 3 + 64));
			IPlayer.IncreaseStat(18,4);
			CDBSocket::Write(16,"dbwbb",IPlayer.GetPID(),23,IPlayer.GetStatPoint(),4,*(DWORD *)((int)Player + 4 * 4 + 64));
		}

		if (IPlayer.GetClass() == 4 && IPlayer.GetHth() < 10 && IPlayer.GetLevel() == 1)
		{
			IPlayer.IncreaseStat(-52,0);
			CDBSocket::Write(16,"dbwbb",IPlayer.GetPID(),23,IPlayer.GetStatPoint(),0,*(DWORD *)((int)Player + 4 * 0 + 64));
			IPlayer.IncreaseStat(10,1);
			CDBSocket::Write(16,"dbwbb",IPlayer.GetPID(),23,IPlayer.GetStatPoint(),1,*(DWORD *)((int)Player + 4 * 1 + 64));
			IPlayer.IncreaseStat(-140,2);
			CDBSocket::Write(16,"dbwbb",IPlayer.GetPID(),23,IPlayer.GetStatPoint(),2,*(DWORD *)((int)Player + 4 * 2 + 64));
			IPlayer.IncreaseStat(14,3);
			CDBSocket::Write(16,"dbwbb",IPlayer.GetPID(),23,IPlayer.GetStatPoint(),3,*(DWORD *)((int)Player + 4 * 3 + 64));
			IPlayer.IncreaseStat(-64,4);
			CDBSocket::Write(16,"dbwbb",IPlayer.GetPID(),23,IPlayer.GetStatPoint(),4,*(DWORD *)((int)Player + 4 * 4 + 64));
		}

		if (IPlayer.GetX() < 0 || IPlayer.GetY() < 0 || IPlayer.GetZ() < 0)
		{
			IPlayer.BoxMsg("Player has been unstucked.");
			IPlayer.SetX(257514);
			IPlayer.SetY(259273);
			IPlayer.SetZ(16168);
			SaveAllProperty((int)Player, 0, 0);
			IPlayer.Kick();
			return 0;
		}

		if (PlayerBlockCheck.count(IPlayer.GetUID()))
		{
			IPlayer.BoxMsg("Your account has been blocked.");
			IPlayer.Kick();
			return 0;
		}

		if ((IPlayer.GetClass() == 4 || IPlayer.GetClass() == 0 || IPlayer.GetClass() == 2 || IPlayer.GetClass() == 3 || (IPlayer.GetClass() == 1 && IPlayer.GetSpecialty() == 23)) && IPlayer.GetLevel() >= 70)
		{
			int pSkill = IPlayer.GetSkillPointer(70);

			if (pSkill)
			{
				ISkill xSkill((void*)pSkill);
				IPlayer.AddMaxAttack((IPlayer.GetMaxPhyAttack() * (4 + (xSkill.GetGrade() * 4))) / 100);
				IPlayer.AddMinAttack((IPlayer.GetMaxPhyAttack() * (4 + (xSkill.GetGrade() * 4))) / 100);
			}

			pSkill = IPlayer.GetSkillPointer(71);

			if (pSkill)
			{
				ISkill xSkill((void*)pSkill);
				IPlayer.AddMaxAttack((IPlayer.GetMaxPhyAttack() * (4 + (xSkill.GetGrade() * 4))) / 100);
				IPlayer.AddMinAttack((IPlayer.GetMaxPhyAttack() * (4 + (xSkill.GetGrade() * 4))) / 100);
			}
		}

		if (IPlayer.GetClass() == 1 && IPlayer.GetLevel() >= 70 && IPlayer.GetSpecialty() == 43)
		{
			int pSkill = IPlayer.GetSkillPointer(71);

			if (pSkill)
			{
				ISkill xSkill((void*)pSkill);
				IPlayer.AddDef(8 + (xSkill.GetGrade() * 4));
			}
		}

		if (IPlayer.GetClass() == 3)
		{
			int pSkill = IPlayer.GetSkillPointer(2);

			if (pSkill)
			{
				ISkill xSkill((void*)pSkill);
				IPlayer.AddMinAttack(xSkill.GetGrade());
				IPlayer.AddMaxAttack(xSkill.GetGrade());
			}
		}

		if (IPlayer.GetClass() == 3)
		{
			int pSkill = IPlayer.GetSkillPointer(3);

			if (pSkill)
			{
				ISkill xSkill((void*)pSkill);
				IPlayer.AddOTP(xSkill.GetGrade()*2);
			}
		}

		if (IPlayer.GetClass() == 3)
		{
			int Crit = IPlayer.GetSkillPointer(4);
			int CritDamage = IPlayer.GetSkillPointer(5);
			int LastCritDamage = IPlayer.GetSkillPointer(37);

			if (Crit)
			{
				IPlayer.IncreaseCritRate(*(DWORD*)((int)Crit + 8));
				IPlayer.IncreaseCritDamage(*(DWORD*)((int)Crit + 8));
			}

			if (CritDamage)
			{
				IPlayer.IncreaseCritRate(*(DWORD*)((int)CritDamage + 8));
				IPlayer.IncreaseCritDamage(*(DWORD*)((int)CritDamage + 8));
			}

			if (LastCritDamage)
			{
				IPlayer.IncreaseCritRate(*(DWORD*)((int)LastCritDamage + 8));
				IPlayer.IncreaseCritDamage(*(DWORD*)((int)LastCritDamage + 8) * 2);
			}
		}

		/*
		if (IPlayer.GetLevel() >= 96)
		{
			int pSkill = IPlayer.GetSkillPointer(94);

			if (pSkill)
			{
				ISkill xSkill((void*)pSkill);
				IPlayer.IncreaseCritRate(xSkill.GetGrade() * 5);
				IPlayer.IncreaseCritDamage(xSkill.GetGrade() * 5);
			}
		}*/

		if (IPlayer.GetClass() == 3 || IPlayer.GetClass() == 4)
		{
			int pSkill = IPlayer.GetSkillPointer(30);

			if (pSkill)
			{
				ISkill xSkill((void*)pSkill);
				IPlayer.IncreaseMaxHp((xSkill.GetGrade() * 5) * IPlayer.GetHth());
			}
		}

		if (IPlayer.GetClass() == 0 && IPlayer.GetLevel() < 100 && IPlayer.GetSpecialty() == 43)
			IPlayer.AddDef(((IPlayer.GetLevel() - 65) * 5) - ((IPlayer.GetDef() * 2) / 50));
		
		if (IPlayer.GetClass() == 0 && IPlayer.GetLevel() >= 100 && IPlayer.GetSpecialty() == 43)
			IPlayer.AddDef(((100 - 65) * 5) - ((IPlayer.GetDef() * 2) / 50));

		if (IPlayer.GetLevel() >= 81 && MysteryEnable)
		{
			int OTP = IPlayer.GetSkillPointer(87);
			int EVA = IPlayer.GetSkillPointer(88);
			int DEF = IPlayer.GetSkillPointer(89);

			if (OTP)
			{
				ISkill xSkill((void*)OTP);
				IPlayer.AddOTP(8 * xSkill.GetGrade());
			}

			if (EVA)
			{
				ISkill xSkill((void*)EVA);
				IPlayer.AddEva(6 * xSkill.GetGrade());
			}

			if (DEF)
			{
				ISkill xSkill((void*)DEF);
				IPlayer.AddDef(24 + (7 * xSkill.GetGrade()));
			}
		}

		if (IPlayer.GetLevel() >= 70)
		{
			IPlayer.IncreaseMaxHp(250);
			IPlayer.IncreaseMaxMp(100);
		}

		if (IPlayer.GetLevel() >= 75)
		{
			IPlayer.IncreaseMaxHp(300);
			IPlayer.IncreaseMaxMp(125);
		}

		if (IPlayer.GetLevel() >= 80)
		{
			IPlayer.IncreaseMaxHp(350);
			IPlayer.IncreaseMaxMp(150);
		}

		if (IPlayer.GetLevel() >= 85)
		{
			IPlayer.IncreaseMaxHp(550);
			IPlayer.IncreaseMaxMp(250);
		}

		if (IPlayer.GetLevel() >= 90)
		{
			IPlayer.IncreaseMaxHp(950);
			IPlayer.IncreaseMaxMp(450);
		}

		if (IPlayer.GetLevel() >= 95)
		{
			IPlayer.IncreaseMaxHp(1750);
			IPlayer.IncreaseMaxMp(850);
		}

		if (IPlayer.GetLevel() >= 70 && IPlayer.GetLevel() <= 74)
		{
			int Value = IPlayer.GetLevel() - 69;
			IPlayer.IncreaseMaxHp(Value*6);
			IPlayer.IncreaseMaxMp(Value*3);
		}

		if (IPlayer.GetLevel() >= 75 && IPlayer.GetLevel() <= 79)
		{
			int Value = IPlayer.GetLevel() - 74;
			IPlayer.IncreaseMaxHp((Value*12)+30);
			IPlayer.IncreaseMaxMp((Value*6)+15);
		}

		if (IPlayer.GetLevel() >= 80 && IPlayer.GetLevel() <= 84)
		{
			int Value = IPlayer.GetLevel() - 79;
			IPlayer.IncreaseMaxHp((Value*18)+90);
			IPlayer.IncreaseMaxMp((Value*9)+45);
		}

		if (IPlayer.GetLevel() >= 85 && IPlayer.GetLevel() <= 89)
		{
			int Value = IPlayer.GetLevel() - 84;
			IPlayer.IncreaseMaxHp((Value*24)+180);
			IPlayer.IncreaseMaxMp((Value*12)+90);
		}

		if (IPlayer.GetLevel() >= 90 && IPlayer.GetLevel() <= 94)
		{
			int Value = IPlayer.GetLevel() - 89;
			IPlayer.IncreaseMaxHp((Value*30)+300);
			IPlayer.IncreaseMaxMp((Value*15)+150);
		}

		if (IPlayer.GetLevel() >= 95)
		{
			int Value = IPlayer.GetLevel() - 94;
			IPlayer.IncreaseMaxHp((Value*36)+450);
			IPlayer.IncreaseMaxMp((Value*18)+225);
		}

		if(IPlayer.GetClass() == 2 && IPlayer.GetLevel() < 100 && IPlayer.GetSpecialty() == 43)
			IPlayer.AddEva((IPlayer.GetAgi() * (IPlayer.GetLevel() / 2) / 400));

		if(IPlayer.GetClass() == 2 && IPlayer.GetLevel() >= 100 && IPlayer.GetSpecialty() == 43)
			IPlayer.AddEva((IPlayer.GetAgi() * (100 / 2) / 400));

		if (IPlayer.GetClass() == 4)
		{
			int pSkill = IPlayer.GetSkillPointer(17);

			if (pSkill)
			{
				ISkill xSkill((void*)pSkill);
				int nSkillGrade = xSkill.GetGrade();
				IPlayer.IncreaseMaxMp(30*nSkillGrade);
			}
		}

		if (IPlayer.GetClass() == 4)
		{
			int pSkill = IPlayer.GetSkillPointer(23);

			if (pSkill)
			{
				ISkill xSkill((void*)pSkill);
				int nSkillGrade = xSkill.GetGrade();
				IPlayer.AddInt(2*nSkillGrade);
			}
		}

		if(PlayerStats.count((IPlayer.GetClass()*1000)+(IPlayer.GetSpecialty()*1000))){
			for(int i=IPlayer.GetLevel();i>=1;i--){
				if(PlayerStats.count((i*100)+(IPlayer.GetClass()*1000)+(IPlayer.GetSpecialty()*1000))){
					IPlayer.IncreaseMaxHp(PlayerStats.find((i*100)+(IPlayer.GetClass()*1000)+(IPlayer.GetSpecialty()*1000))->second.HP);
					IPlayer.IncreaseMaxMp(PlayerStats.find((i*100)+(IPlayer.GetClass()*1000)+(IPlayer.GetSpecialty()*1000))->second.MP);
					IPlayer.AddAgi(PlayerStats.find((i*100)+(IPlayer.GetClass()*1000)+(IPlayer.GetSpecialty()*1000))->second.Agi);
					IPlayer.AddInt(PlayerStats.find((i*100)+(IPlayer.GetClass()*1000)+(IPlayer.GetSpecialty()*1000))->second.Int);
					IPlayer.AddEva(PlayerStats.find((i*100)+(IPlayer.GetClass()*1000)+(IPlayer.GetSpecialty()*1000))->second.Eva);
					IPlayer.AddOTP(PlayerStats.find((i*100)+(IPlayer.GetClass()*1000)+(IPlayer.GetSpecialty()*1000))->second.OTP);
					IPlayer.AddDef(PlayerStats.find((i*100)+(IPlayer.GetClass()*1000)+(IPlayer.GetSpecialty()*1000))->second.Def);
					IPlayer.AddStr(PlayerStats.find((i*100)+(IPlayer.GetClass()*1000)+(IPlayer.GetSpecialty()*1000))->second.Str);
					IPlayer.AddWis(PlayerStats.find((i*100)+(IPlayer.GetClass()*1000)+(IPlayer.GetSpecialty()*1000))->second.Wis);
					IPlayer.AddHp(PlayerStats.find((i*100)+(IPlayer.GetClass()*1000)+(IPlayer.GetSpecialty()*1000))->second.Hth);
					IPlayer.AddMinAttack(PlayerStats.find((i*100)+(IPlayer.GetClass()*1000)+(IPlayer.GetSpecialty()*1000))->second.ATK);
					IPlayer.AddMaxAttack(PlayerStats.find((i*100)+(IPlayer.GetClass()*1000)+(IPlayer.GetSpecialty()*1000))->second.ATK);
					IPlayer.AddAbsorb(PlayerStats.find((i*100)+(IPlayer.GetClass()*1000)+(IPlayer.GetSpecialty()*1000))->second.Absorb);
				}
			}
		}

		return Check;
	} else {
		return 0;
	}
}