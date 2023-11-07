void MemoryCopy(void *Destination, void *Source, size_t Size)
{
	unsigned long p1, p2;
	VirtualProtect(Destination, Size, PAGE_EXECUTE_READWRITE, &p1);
	VirtualProtect(Source, Size, PAGE_EXECUTE_READWRITE, &p2);
	CopyMemory(Destination, Source, Size);
	VirtualProtect(Destination, Size, p1, &p1);
	VirtualProtect(Source, Size, p1, &p2);
}
//static unsigned __int64 _ExpTable[312];
//static unsigned __int64 _ExpTable[] = {
//	0, 5, 24, 60, 80, 164, 271, 407, 579, 794, 1125, 1543, 2068, 2722,
//	3534, 4563, 5830, 7385, 9286, 11607, 17493, 21845, 27147, 33593, 41416,
//	51341, 63394, 78005, 95696, 117090, 166758, 203151, 247043, 299942, 363659,
//	440404, 532757, 643849, 777437, 938032, 1211834, 1460324, 1758856, 2117449, 2548126,
//	3065315, 3686331, 4431950, 5327106, 6401717, 10255633, 12320243, 14798389, 17772795,
//	21342730, 25627317, 30769501, 36940820, 44347118, 53235407, 63902104, 76702906, 92064653,
//	110499551, 132622249, 159170373, 191028978, 229260177, 275138508, 330193415, 396260232, 1188853398,
//	1426699190, 1712116603, 2054620005, 2465626643, 2958837208, 3550692535, 4260921625, 5113199283, 12271870776,
//	14726443120, 17671935710, 21206532706, 31810068850, 38172360013, 45807117133, 54968833525, 65962901170, 94986948540,
//	113984718984, 136782053544, 164138865195, 196967049519, 315147841592, 378177986472, 453814174732, 544577615260, 653493758732,
//	980241432400, 1029253504020, 1080716179221, 1134751988182, 1191489587591, 1251064066970, 1313617270318, 1379298133833, 1448263040524, 1448263040524,
//	1520676192550, 1596710002177, 1676545502285, 1760372777399, 1848391416268, 1940810987081, 2037851536435, 2139744113256, 2246731318918, 2359067884863, 2477021279106,
//	2600872343061, 2730915960214, 2867461758224, 3010834846135, 3161376588441, 3319445417863, 3485417688756, 3659688573193, 3842673001852, 4034806651944, 4236546984541,
//	4448374333768, 4670793050456, 4904332702978, 5149549338126, 5407026805032, 5677378145283, 5961247052547, 6259309405174, 6572274875432, 6900888619203, 7245933050163,
//	7608229702671, 7988641187804, 8388073247194, 8807476909553, 9247850755030, 9710243292781, 10195755457420, 10705543230291, 11240820391805, 11802861411395, 12393004481964,
//	13012654706062, 13663287441365, 13936553190192, 14215284253995, 14499589939074, 14789581737855, 15085373372612, 15387080840064, 15694822456865, 16008718906002, 16328893284122,
//	16655471149804, 16988580572800, 17328352184256, 17674919227941, 18028417612499, 18388985964748, 18756765684042, 19131900997722, 19514539017676, 19904829798029, 20302926393989,
//	20708984921868, 21123164620305, 21545627912711, 21976540470965, 22416071280384, 22864392705991, 23321680560110, 23788114171312, 24263876454738, 24749153983832, 25244137063508,
//	25749019804778, 26264000200873, 26789280204890, 27325065808987, 27871567125166, 28428998467669, 28997578437022, 29577530005762, 30169080605877, 30772462217994, 31387911462353,
//	32015669691600, 32655983085432, 33309102747140, 33975284802082, 34654790498123, 35347886308085, 36054844034246, 36775940914930, 37511459733228, 38261688927892, 39026922706449,
//	39807461160577, 40603610383788, 41415682591463, 42243996243292, 43088876168157, 43950653691520, 44829666765350, 45726260100657, 46640785302670, 47573601008723, 48525073028897,
//	49495574489474, 50485485979263, 51495195698848, 52525099612824, 53575601605080, 54647113637181, 55740055909924, 56854857028122, 57991954168684, 59151793252057, 60334829117098,
//	61541525699439, 62772356213427, 64027803337695, 65308359404448, 66614526592536, 67946817124386, 69305753466873, 70691868536210, 72105705906934, 73547820025072, 75018776425573,
//	76519151954084, 78049534993165, 79610525693028, 81202736206888, 82826790931025, 84483326749645, 86172993284637, 87896453150329, 89654382213335, 91447469857601, 93276419254753,
//	95141947639848, 97044786592644, 106749265251908,
//};

void SwitchTable()
{
	DWORD* ExpPtr = (DWORD*)_ExpTable;
	DWORD Exptr2;
	DWORD ExpAdr1[] = {0x004592A6,0x004592BE,0x0046337A,0x0046440F,0x00415649,0x0041566F,0x004156B8,0x00415737};
	DWORD ExpAdr2[] = {0x00459289,0x004592CB,0x00463387,0x00464407,0x00415650,0x00415667,0x004156B0,0x0041572F};

	for(int i = 0;i<sizeof(ExpAdr1)/4;i++)
		MemoryCopy((void*)ExpAdr1[i], (void*) &ExpPtr, 4);

	MemoryCopy((void*)&Exptr2,(void*)0x00415737,4);
	Exptr2 += 0x04;

	for(int i = 0;i<sizeof(ExpAdr2)/4;i++)
		MemoryCopy((void*)ExpAdr2[i], (void*) &Exptr2, 4);
}

int __fastcall PerfectCureFix(int Skill, void* edx, int Argument, int Object) {
	ISkill ISkill((void*)Skill);
	if (ISkill.GetIndex() == 55) {
		*((DWORD *)Skill + 11) = 1;
		return ((35 + (20 * (ISkill.GetGrade() - 1))) * CChar::GetMaxHp(Object) / 100);
	}
	
	return CChar::PerfectCure(Skill, Argument, Object);
}

int __fastcall PerfectCureFix2(void* Skill, void* edx, int Player) {
	ISkill ISkill((void*)Skill);
	return 1;
}

int __fastcall BuffTimer(int Player, void* edx, int Argument) {
	IChar IPlayer((void*)Player);

	int PlayerBRefresh = IPlayer.GetRefreshCheck();
	if (!PlayerBRefresh)
		IPlayer.SetRefreshCheck(GetTickCount() + 995);

	if (PlayerBRefresh <= GetTickCount()) {
		CChar::RefreshBuff((int)Player);
		IPlayer.SetRefreshCheck(GetTickCount() + 995);
	}

	return CChar::IsGState(Player,Argument);
}

int __cdecl MyUpdateProperty(int Player, int Type, int InOut, signed __int64 Exp)
{
	IChar IPlayer((void*)Player);
	IChar IMonster;
	Interface<ITools>Tools;

	if (IPlayer.IsOnline() && Type == 8)
	{
		if (InOut == 1 && IPlayer.GetClass() == 4) {
			int pSkill = IPlayer.GetSkillPointer(16);

			if (pSkill)
			{
				ISkill xSkill((void*)pSkill);
				int Increase = 4 * xSkill.GetGrade();
				Exp += Increase;
			}
		}

		if (ManaCostActive && !InOut) {
			int ManaCost = IPlayer.GetProperty(PlayerProperty::ManaCost);

			if (ManaCost)
				Exp = ManaCost;
		}
	}

	if (Type == 25 && IPlayer.IsOnline() && InOut)
	{


		if (!IPlayer.GetProperty(PlayerProperty::UnGap)) {
			if (LevelGap.count(IPlayer.GetLevel()))
				Exp = (Exp * LevelGap.find(IPlayer.GetLevel())->second) / 100;
		}

		if (IPlayer.GetMap() == LawlessMap)
			Exp += (Exp * (10 * IPlayer.GetBuffValue(BuffNames::LawlessEXP))) / 100;
		
		if (IPlayer.IsBuff(258))
			Exp += (Exp / PPEXP);

		if (IPlayer.IsBuff(BuffNames::CJBEXP))
			Exp += (Exp / CJBEXP);

		if (IPlayer.IsBuff(120))
			Exp += (Exp / 10);

		if (IPlayer.IsBuff(298) && Exp > 100)
			Exp += (Exp * 3) / 100;

		int Pet1 = IPlayer.GetBuffValue(BuffNames::PetOwner);
		int Pet2 = IPlayer.GetBuffValue(BuffNames::PetOwner2);
		int Pet3 = IPlayer.GetBuffValue(BuffNames::PetOwner3);

		if (IPlayer.GetMap() == EmokMap) {
			int EXPAddEmok = IPlayer.GetBuffValue(156);
			if (EXPAddEmok > 0 && EXPAddEmok < 100)
				Exp += Tools->Per_calculation_int64(EXPAddEmok, Exp);
		}


		if (Pet1 && Exp > 100)
		{
			int ExtraExp = PetTime.find(Pet1)->second.Exp;
			if (ExtraExp > 0 && ExtraExp < 100) {
				Exp += Tools->Per_calculation_int64(ExtraExp, Exp);
			}
		}

		if (Pet2 && Exp > 100)
		{
			int ExtraExp = PetTime.find(Pet2)->second.Exp;
			if (ExtraExp > 0 && ExtraExp < 100) {
				Exp += Tools->Per_calculation_int64(ExtraExp, Exp);
			}
		}

		if (Pet3 && Exp > 100)
		{
			int ExtraExp = PetTime.find(Pet3)->second.Exp;
			if (ExtraExp > 0 && ExtraExp < 100) {
				Exp += Tools->Per_calculation_int64(ExtraExp, Exp);
			}
		}


		for (std::map<int, BuffMaker>::const_iterator it = BuffMakerCheck.begin(); it != BuffMakerCheck.end(); ++it) {
			const BuffMaker& buff = it->second;
			if (IPlayer.IsBuff(buff.BuffID) && buff.ExpALLOW == "true") {
				Exp += (Exp * buff.amount) / 100;
			}
		}

		if (IPlayer.IsBuff(BuffNames::F10Buff))
			Exp += (Exp * F10EXPBuff) / 100;
		/*
		if (IPlayer.IsBuff(BuffNames::expstone) && Exp > 100) {
			int EXPValue = IPlayer.GetBuffValue(BuffNames::expstone);

			if (EXPValue)
				Exp += Tools->Per_calculation_int64(EXPValue, Exp);
			else
				Exp += (Exp*0.40);
		}
		*/


		if (IPlayer.GetProperty(PlayerProperty::Reborn))
		{
			int CurrentReborn = IPlayer.GetProperty(PlayerProperty::Reborn);
			if (RebornsPenalty.count(CurrentReborn)) {

				RbPenalty rb = RebornsPenalty.find(CurrentReborn)->second;
				if (rb.rbPenalty)
				{
					Exp = (Exp / rb.rbPenalty * 100);
				}
			}

		}

		if (IPlayer.GetLevel() == levellimit)
			Exp = 0;

	}

	return CPlayer::UpdateProperty(Player, Type, InOut, Exp);
}

int TrigramGrade(void* ItemOffset) {
	IItem Item(ItemOffset);

	itemStat.Enter();
	int Stats = GetItemStat.count(Item.GetIID()) ? GetItemStat.find(Item.GetIID())->second : 0;
	itemStat.Leave();

	int GetCurrentGrade = (Stats % 10000) / 100;
	if (!GetCurrentGrade) {
		if (Item.Prefix())
			GetCurrentGrade = Item.PrefixID() - 1;
	}

	if (GetCurrentGrade < 0)
		GetCurrentGrade = 0;

	return GetCurrentGrade;
}

int SoulPocketDamage(void* Player, int Damage) {
	IChar IPlayer(Player);

	if (IPlayer.GetType() != 0 || !IPlayer.GetBuffValue(BuffNames::SPUpdated))
		return 0;

	IPlayer.UpdateBuff(BuffNames::SPUpdated, BuffNames::BuffTime, 0);
	int nDmg = 0;
	int SoulPocket = IPlayer.GetBuffValue(BuffNames::SoulPocketAmount);
	if (IPlayer.IsOnline() && SoulPocket) {
		double mul = 1.5;
		int Index = IPlayer.GetBuffValue(BuffNames::SoulPIndex);
		if (Index) {
			if (SoulPocketEffect.count(Index))
				mul = 1.0 + ((double)SoulPocketEffect.find(Index)->second / 100.0);
		}
		if (mul >= 1.0) {
			int dmg = Damage / mul;
			nDmg = (Damage - dmg) > 0 ? (Damage - dmg) : 0;
		}
	}

	return nDmg;
}

int _SoulPocketDamage(void* Player, int Damage) {
	IChar IPlayer(Player);

	if (IPlayer.GetType() != 0 || !IPlayer._GetBuffValue(BuffNames::SPUpdated))
		return 0;

	IPlayer._UpdateBuff(BuffNames::SPUpdated, BuffNames::BuffTime, 0);

	int nDmg = 0;
	int SoulPocket = IPlayer._GetBuffValue(BuffNames::SoulPocketAmount);
	if (IPlayer.IsOnline() && SoulPocket) {
		double mul = 1.5;
		int Index = IPlayer._GetBuffValue(BuffNames::SoulPIndex);
		if (Index) {
			if (SoulPocketEffect.count(Index))
				mul = 1.0 + ((double)SoulPocketEffect.find(Index)->second / 100.0);
		}
		if (mul >= 1.0) {
			int dmg = Damage / mul;
			nDmg = (Damage - dmg) > 0 ? (Damage - dmg) : 0;
		}
	}

	return nDmg;
}



void CheckForDailyQuest(void* Player , void* Monster) {
	IChar IPlayer(Player);
	IChar ITarget(Monster);

	if (IPlayer.IsValid() && ITarget.IsValid() && IPlayer.GetType() == 0 && ITarget.GetType() == 1) {
		if (IPlayer.IsParty())
		{
			void *Party = (void *)CParty::FindParty(IPlayer.GetPartyID());
			if (Party) {
				for (int i = CParty::GetPlayerList(Party); i; i = CBaseList::Pop((void*)i))
				{
					int PTMember = *(DWORD*)((void*)i);
					IChar IMembers((void*)PTMember);

					if (IMembers.IsOnline() && CChar::GetRange((int)IPlayer.GetOffset() + 332, PTMember + 332) <= 300) //Daily Quest Range
						updateDailyQuestKill(ITarget.GetMobIndex(), IMembers);
				}

				CIOObject::Release(Party);
			}
		}
		else {
			if (IPlayer.IsOnline())
				updateDailyQuestKill(ITarget.GetMobIndex(), IPlayer);
		}
	}
}

void __cdecl MyStatStr(int Player, unsigned char Packet, char *Format, unsigned char Type, unsigned short Str, unsigned short Otp, unsigned short MinAtk, unsigned short MaxAtk)
{
	IChar IPlayer((void*)Player);
	CPlayer::Write(IPlayer.GetOffset(), 69, "bwwww", 0, IPlayer.GetStr(), CChar::GetHit(Player), CChar::GetMinAttack(Player), CChar::GetMaxAttack(Player));
	CPlayer::Write(IPlayer.GetOffset(), 69, "bwwww", 43, (CChar::GetStr(Player) - IPlayer.GetStr()), CChar::GetHit(Player), CChar::GetMinAttack(Player), CChar::GetMaxAttack(Player));		
}

void __cdecl MyStatHth(int Player, unsigned char Packet, char *Format, unsigned char Type, unsigned short Str, unsigned short Otp, unsigned short MinAtk, unsigned short MaxAtk)
{
	IChar IPlayer((void*)Player);
	CPlayer::Write(IPlayer.GetOffset(), 69, "bwddw", 1, IPlayer.GetHth(), IPlayer.GetCurHp(), CChar::GetMaxHP(Player), CChar::GetResist(IPlayer.GetOffset(), 4));
	CPlayer::Write(IPlayer.GetOffset(), 69, "bwddw", 44, (CChar::GetHth(Player) - IPlayer.GetHth()), IPlayer.GetCurHp(), CChar::GetMaxHP(Player), CChar::GetResist(IPlayer.GetOffset(), 4));
}

void __cdecl MyStatInt(int Player, unsigned char Packet, char* Format, unsigned char statType, unsigned short points, unsigned short curWisdom, unsigned short maxWisdom, unsigned short curse)
{
	IChar IPlayer((void*)Player);
	CPlayer::Write(IPlayer.GetOffset(), 69, "bwwwwww", 2, IPlayer.GetInt(), CChar::GetMinMagic(Player), CChar::GetMaxMagic(Player), CChar::GetResist(IPlayer.GetOffset(), 0), CChar::GetResist(IPlayer.GetOffset(), 1), CChar::GetResist(IPlayer.GetOffset(), 2));
	CPlayer::Write(IPlayer.GetOffset(), 69, "bwwwwww", 45, (CChar::GetInt(Player) - IPlayer.GetInt()), CChar::GetMinMagic(Player), CChar::GetMaxMagic(Player), CChar::GetResist(IPlayer.GetOffset(), 0), CChar::GetResist(IPlayer.GetOffset(), 1), CChar::GetResist(IPlayer.GetOffset(), 2));
}

void __cdecl MyStatWis(int Player, unsigned char Packet, char* Format, unsigned char statType, unsigned short points, unsigned short curWisdom, unsigned short maxWisdom, unsigned short curse)
{
	IChar IPlayer((void*)Player); 
	CPlayer::Write(IPlayer.GetOffset(), 69, "bwwwwww", 3, IPlayer.GetWis(), IPlayer.GetCurMp(), CChar::GetMaxMp(Player), CChar::GetMinMagic(Player), CChar::GetMaxMagic(Player), CChar::GetResist(IPlayer.GetOffset(), 3));
	CPlayer::Write(IPlayer.GetOffset(), 69, "bwwwwww", 46, (CChar::GetWis(Player) - IPlayer.GetWis()), IPlayer.GetCurMp(), CChar::GetMaxMp(Player), CChar::GetMinMagic(Player), CChar::GetMaxMagic(Player), CChar::GetResist(IPlayer.GetOffset(), 3));
}

void __cdecl MyStatAgi(int Player, unsigned char Type, char* format, unsigned char statType, unsigned short points, unsigned short otp, unsigned short evasion, unsigned short minAttack, unsigned short maxAttack)
{
	IChar IPlayer((void*)Player);
	CPlayer::Write(IPlayer.GetOffset(), 69, "bwwwwww", 4, IPlayer.GetAgi(), CChar::GetHit(Player), CChar::GetDodge(Player), CChar::GetDodge(Player), CChar::GetMinAttack(Player), CChar::GetMaxAttack(Player));
	CPlayer::Write(IPlayer.GetOffset(), 69, "bwwwwww", 47, (CChar::GetDex(Player) - IPlayer.GetAgi()), CChar::GetHit(Player), CChar::GetDodge(Player), CChar::GetDodge(Player), CChar::GetMinAttack(Player), CChar::GetMaxAttack(Player));		
}

void __cdecl MyStatCurHp1(int Player, unsigned char Type, char* format, unsigned char statType, unsigned short hp)
{
	IChar IPlayer((void*)Player);
	CPlayer::Write(IPlayer.GetOffset(), 69, "bd", 7, IPlayer.GetCurHp());
}

void __cdecl MyStatCurHp(int Player, unsigned char Type, char* format, unsigned char statType, unsigned short hp, unsigned short maxhp)
{
	IChar IPlayer((void*)Player);
	CPlayer::Write(IPlayer.GetOffset(), 69, "bdd", 5, IPlayer.GetCurHp(), CChar::GetMaxHP(Player));
}

void __cdecl MyStatEXP(int Player, unsigned char Type, char* format, char type, int EXP, int Old, signed __int64 Adding)
{
	IChar IPlayer((void*)Player);
	CConsole::Red("%s", format);
	CPlayer::Write((void*)Player, 69, "bII", 25, IPlayer.GetEXP(), Adding);
}

void __cdecl MyStatEXP1(int Player, unsigned char Type, char* format, char type, int EXP, int Old, signed int Adding, int Difference)
{
	IChar IPlayer((void*)Player);
	CConsole::Red("1- %s", format);
	CPlayer::Write((void*)Player, 69, "bII", 25, IPlayer.GetEXP(), Adding);
}

int __cdecl LowestTrigramGrade(IChar IPlayer)
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

void __cdecl SynchronizationMsg(int Socket, unsigned char Type, char* format, unsigned char msg)
{
	return;
}

int __fastcall PartyEXP(int Party, void *edx, signed int *EXP, int Check, int PlayerX)
{
	if (ChannelActivated) {
		int PTPlayer = CParty::GetRandomPlayer((void*)Party);
		if (PTPlayer) {
			IChar IPlayer((void*)PTPlayer);
			int Channel = IPlayer.GetChannel();
			bool stop = false;
			for (int i = CParty::GetPlayerList((void*)Party); i; i = CBaseList::Pop((void*)i))
			{
				int PTMember = *(DWORD*)((void*)i);
				IChar IMembers((void*)PTMember);
				if (!stop && IMembers.GetOffset() != IPlayer.GetOffset() && IMembers.GetChannel() != Channel)
					stop = true;
			}

			if (stop) {
				IPlayer.SystemMessage("Party EXP can not be gathered by/for players from different channels.", TEXTCOLOR_RED);
				CSkill::ObjectRelease((void*)PTPlayer, PTPlayer + 352);
				return 0;
			}

			CSkill::ObjectRelease((void*)PTPlayer, PTPlayer + 352);
		}
	}

	/*signed int IntEXP = *EXP;

	while (IntEXP > PartyEXPMax) {
		signed int NewEXP = PartyEXPMax;
		CParty::AllotExp(Party, &NewEXP, Check, PlayerX);
		
		IntEXP -= PartyEXPMax;
	}
	*/

	return CParty::AllotExp(Party, EXP, Check, PlayerX);
}

int __fastcall InitMonsterDrop(int InitMonster, void *edx, int Monster, int IsParty, int ID, int a5, int a6)
{
	if (IsParty && !CInitMonster::IsRace(InitMonster, 4)) {
		int PTLvl = 0;
		void *Party = (void *)CParty::FindParty(ID);

		if (Party) {
			PTLvl = *(DWORD *)((int)Party + 24);
			CIOObject::Release(Party);
		}
		
		IChar IMonster((void*)Monster);
		if (PTLvl >= (IMonster.GetLevel() + 100))
			return 0;

	}
	
	return CInitMonster::DropItem(InitMonster, Monster, IsParty, ID, a5, a6);
}

int __fastcall MonsterAllotEXP(int Monster, void *edx, int a2, int TankerID, int* a4)
{
	IChar IMonster((void*)Monster);

	IChar IPlayer((void*)IMonster.GetMobTanker());
	int Check = CMonsterReal::AllotExp(Monster, a2, TankerID, a4);

	if (IPlayer.IsOnline()) {
		int Level = IPlayer.GetLevel();
		if (Level > 100) {
		 if (IMonster.GetLevel() <= (Level - 14))
			{
				return 0;
			}

		}


		if (IPlayer.IsParty())
		{
			int PTLvl = 0;
			void *Party = (void *)CParty::FindParty(IPlayer.GetPartyID());

			if (Party) {
				PTLvl = *(DWORD *)((int)Party + 24);
				if (IPlayer.GetMap() == LawlessMap) {
					for (int i = CParty::GetPlayerList(Party); i; i = CBaseList::Pop((void*)i))
					{
						int PTMember = *(DWORD*)((void*)i);
						IChar IMembers((void*)PTMember);
						if (IMembers.GetMap() == LawlessMap && CChar::GetRange((int)IPlayer.GetOffset() + 332, PTMember + 332) <= 640)
							UpdateLawless((int)IMembers.GetOffset(), LawlessMKill);
					}
				}

				CIOObject::Release(Party);
			}

			if (PTLvl > 100) {
				int MobLvl = IMonster.GetLevel();

				if (IMonster.GetLevel() <= (PTLvl - 14)) {
					return 0;
				}
				
			}
		}
		else
		if (IPlayer.GetMap() == LawlessMap)
			UpdateLawless((int)IPlayer.GetOffset(), LawlessMKill);
	}

	int Index = IMonster.GetMobIndex();

	if (UnGap.count(Index)) {
		if (IPlayer.IsValid()) {
			if (IPlayer.IsParty())
			{
				void *Party = (void *)CParty::FindParty(IPlayer.GetPartyID());
				if (Party) {
					for (int i = CParty::GetPlayerList(Party); i; i = CBaseList::Pop((void*)i))
					{
						int PTMember = *(DWORD*)((void*)i);
						IChar IMembers((void*)PTMember);
						IMembers.SetProperty(PlayerProperty::UnGap, 1);
					}

					CIOObject::Release(Party);
				}
			}
			else
				IPlayer.SetProperty(PlayerProperty::UnGap, 1);
		}
	}
	
	
	if (UnGap.count(Index)) {
		if (IPlayer.IsValid()) {
			if (IPlayer.IsParty())
			{
				void *Party = (void *)CParty::FindParty(IPlayer.GetPartyID());
				if (Party) {
					for (int i = CParty::GetPlayerList(Party); i; i = CBaseList::Pop((void*)i))
					{
						int PTMember = *(DWORD*)((void*)i);
						IChar IMembers((void*)PTMember);
						IMembers.SetProperty(PlayerProperty::UnGap, 0);
					}

					CIOObject::Release(Party);
				}
			}
			else
				IPlayer.SetProperty(PlayerProperty::UnGap, 0);
		}
	}

	return Check;
}

int __fastcall SubState(int Itemx, void *edx, int Type)
{
	if (Type == 1) {
		IItem Item((void*)Itemx);
		TargetFind myTarget(0, 1, *(DWORD*)(Itemx + 32));
		int xPlayer = (int)myTarget.getTarget();
		IChar Player((void*)xPlayer);
		
		if (Player.IsOnline()) {

			if (!isItemSuit(Item.CheckIndex()) && Item.GetType() == 4)
				Player.UpdateBuff(BuffNames::ArmorWears,BuffNames::BuffTime,0);

			if (isItemSuit(Item.CheckIndex()))
				Player.UpdateBuff(BuffNames::SuitsUsing,BuffNames::BuffTime,0);

			if (Item.CheckIndex() >= 2986 && Item.CheckIndex() <= 3009)
			{
				int GetCurrentGrade = TrigramGrade(Item.GetOffset());
				if (!GetCurrentGrade)
					return 0;

				if (Item.CheckIndex() == 2986) Player.UpdateBuff(BuffNames::TrigramHP,BuffNames::BuffTime,0);
				else if (Item.CheckIndex() == 2994) Player.UpdateBuff(BuffNames::TrigramHP,BuffNames::BuffTime,0);
				else if (Item.CheckIndex() == 3002) Player.UpdateBuff(BuffNames::TrigramHP,BuffNames::BuffTime,0);
				else if (Item.CheckIndex() == 2987) Player.UpdateBuff(BuffNames::TrigramMP,BuffNames::BuffTime,0);
				else if (Item.CheckIndex() == 2995) Player.UpdateBuff(BuffNames::TrigramMP,BuffNames::BuffTime,0);
				else if (Item.CheckIndex() == 3003) Player.UpdateBuff(BuffNames::TrigramMP,BuffNames::BuffTime,0);
				else if (Item.CheckIndex() == 2988) Player.UpdateBuff(BuffNames::TrigramAtk,BuffNames::BuffTime,0);
				else if (Item.CheckIndex() == 2996) Player.UpdateBuff(BuffNames::TrigramAtk,BuffNames::BuffTime,0);
				else if (Item.CheckIndex() == 3004) Player.UpdateBuff(BuffNames::TrigramAtk,BuffNames::BuffTime,0);
				else if (Item.CheckIndex() == 2989) Player.UpdateBuff(BuffNames::TrigramStr,BuffNames::BuffTime,0);
				else if (Item.CheckIndex() == 2997) Player.UpdateBuff(BuffNames::TrigramStr,BuffNames::BuffTime,0);
				else if (Item.CheckIndex() == 3005) Player.UpdateBuff(BuffNames::TrigramStr,BuffNames::BuffTime,0);
				else if (Item.CheckIndex() == 2990) Player.UpdateBuff(BuffNames::TrigramAgi,BuffNames::BuffTime,0);
				else if (Item.CheckIndex() == 2998) Player.UpdateBuff(BuffNames::TrigramAgi,BuffNames::BuffTime,0);
				else if (Item.CheckIndex() == 3006) Player.UpdateBuff(BuffNames::TrigramAgi,BuffNames::BuffTime,0);
				else if (Item.CheckIndex() == 2991) Player.UpdateBuff(BuffNames::TrigramInt,BuffNames::BuffTime,0);
				else if (Item.CheckIndex() == 2999) Player.UpdateBuff(BuffNames::TrigramInt,BuffNames::BuffTime,0);
				else if (Item.CheckIndex() == 3007) Player.UpdateBuff(BuffNames::TrigramInt,BuffNames::BuffTime,0);
				else if (Item.CheckIndex() == 2992) Player.UpdateBuff(BuffNames::TrigramWis,BuffNames::BuffTime,0);
				else if (Item.CheckIndex() == 3000) Player.UpdateBuff(BuffNames::TrigramWis,BuffNames::BuffTime,0);
				else if (Item.CheckIndex() == 3008) Player.UpdateBuff(BuffNames::TrigramWis,BuffNames::BuffTime,0);
				else if (Item.CheckIndex() == 2993) Player.UpdateBuff(BuffNames::TrigramHth,BuffNames::BuffTime,0);
				else if (Item.CheckIndex() == 3001) Player.UpdateBuff(BuffNames::TrigramHth,BuffNames::BuffTime,0);
				else if (Item.CheckIndex() == 3009) Player.UpdateBuff(BuffNames::TrigramHth,BuffNames::BuffTime,0);
			}

			if (Item.CheckIndex() >= 3381 && Item.CheckIndex() <= 3383 && Player.GetBuffValue(BuffNames::MirrorBuff))
				Player.UpdateBuff(BuffNames::MirrorBuff,BuffNames::BuffTime,0);

			if (Item.CheckIndex() >= 3384 && Item.CheckIndex() <= 3386 && Player.GetBuffValue(BuffNames::MirrorBuff))
			{
				int MirrorIID = Player.GetBuffValue(BuffNames::MirrorBuff);

				int Itemy = Player.ItemPointer(MirrorIID);

				if (!Itemy)
					return 0;

				IItem Mirror((void*)Itemy);

				if (Mirror.CheckIndex() == 3381)
				{
					if (Player.GetBuffValue(BuffNames::Essence3) == Item.GetIID())
					{
						*(DWORD*)(*(DWORD*)((int)Itemx + 40) + 72) = -97;
						Player.UpdateBuff(BuffNames::Essence3,BuffNames::BuffTime,0);
					}
					else if (Player.GetBuffValue(BuffNames::Essence2) == Item.GetIID()) {
						*(DWORD*)(*(DWORD*)((int)Itemx + 40) + 72) = -96;
						Player.UpdateBuff(BuffNames::Essence2,BuffNames::BuffTime,0);
					}
					else if (Player.GetBuffValue(BuffNames::Essence1) == Item.GetIID()) {
						*(DWORD*)(*(DWORD*)((int)Itemx + 40) + 72) = -95;
						Player.UpdateBuff(BuffNames::Essence1,BuffNames::BuffTime,0);
					}
				}

				if (Mirror.CheckIndex() == 3382)
				{
					if (Player.GetBuffValue(BuffNames::Essence4) == Item.GetIID())
					{
						*(DWORD*)(*(DWORD*)((int)Itemx + 40) + 72) = -98;
						Player.UpdateBuff(BuffNames::Essence4,BuffNames::BuffTime,0);
					}
					else if (Player.GetBuffValue(BuffNames::Essence3) == Item.GetIID()) {
						*(DWORD*)(*(DWORD*)((int)Itemx + 40) + 72) = -97;
						Player.UpdateBuff(BuffNames::Essence3,BuffNames::BuffTime,0);
					}
					else if (Player.GetBuffValue(BuffNames::Essence2) == Item.GetIID()) {
						*(DWORD*)(*(DWORD*)((int)Itemx + 40) + 72) = -96;
						Player.UpdateBuff(BuffNames::Essence2,BuffNames::BuffTime,0);
					}
					else if (Player.GetBuffValue(BuffNames::Essence1) == Item.GetIID()) {
						*(DWORD*)(*(DWORD*)((int)Itemx + 40) + 72) = -95;
						Player.UpdateBuff(BuffNames::Essence1,BuffNames::BuffTime,0);
					}
				}

				if (Mirror.CheckIndex() == 3383)
				{
					if (Player.GetBuffValue(BuffNames::Essence5) == Item.GetIID())
					{
						*(DWORD*)(*(DWORD*)((int)Itemx + 40) + 72) = -99;
						Player.UpdateBuff(BuffNames::Essence5,BuffNames::BuffTime,0);
					}
					else if (Player.GetBuffValue(BuffNames::Essence4) == Item.GetIID()) {
						*(DWORD*)(*(DWORD*)((int)Itemx + 40) + 72) = -98;
						Player.UpdateBuff(BuffNames::Essence4,BuffNames::BuffTime,0);
					}
					else if (Player.GetBuffValue(BuffNames::Essence3) == Item.GetIID()) {
						*(DWORD*)(*(DWORD*)((int)Itemx + 40) + 72) = -97;
						Player.UpdateBuff(BuffNames::Essence3,BuffNames::BuffTime,0);
					}
					else if (Player.GetBuffValue(BuffNames::Essence2) == Item.GetIID()) {
						*(DWORD*)(*(DWORD*)((int)Itemx + 40) + 72) = -96;
						Player.UpdateBuff(BuffNames::Essence2,BuffNames::BuffTime,0);
					}
					else if (Player.GetBuffValue(BuffNames::Essence1) == Item.GetIID()) {
						*(DWORD*)(*(DWORD*)((int)Itemx + 40) + 72) = -95;
						Player.UpdateBuff(BuffNames::Essence1,BuffNames::BuffTime,0);
					}
				}
			}
		}
	}
	return CItem::SubState(Itemx, Type);
}

int __fastcall MirroraFix(int Player, void *edx, int Type)
{
	IChar IPlayer((void*)Player);

	if (Type == 10 && !IPlayer.IsBuff(2738)) {
		IPlayer.Buff(2738, BuffNames::BuffTime, 0);
		return 0;
	}

	if (Type == 0 && !IPlayer.IsBuff(2739)) {
		IPlayer.Buff(2739, BuffNames::BuffTime, 0);
		return 0;
	}

	return CPlayer::IsWState(Player, Type);
}

int __fastcall SuitsFix(int Player, void *edx, int Type)
{
	IChar IPlayer((void*)Player);

	if (IPlayer.IsOnline() && IPlayer.GetBuffValue(BuffNames::RidingUsing) && Type == 13)
		return 0;

	if (IPlayer.IsOnline() && !IPlayer.GetBuffValue(BuffNames::RidingUsing) && Type == 13)
		return 0;

	return CPlayer::IsWState(Player, Type);
}

int __fastcall SuitsFix1(int Player, void *edx, int Type)
{
	IChar IPlayer((void*)Player);

	if (IPlayer.IsOnline() && IPlayer.GetBuffValue(BuffNames::RidingUsing) && Type == 13)
		return 1;

	if (IPlayer.IsOnline() && !IPlayer.GetBuffValue(BuffNames::RidingUsing) && Type == 13)
		return 1;

	return CPlayer::IsWState(Player, Type);
}

int __fastcall MirrorFix(int Player, void *edx, int Type)
{
	IChar IPlayer((void*)Player);

	if (Type == 1 || Type == -3 || Type == 4 || Type == -97 || Type == -98 || Type == -99 || Type == -100 || Type == -101 || Type == -102 || Type == -108 || Type == 20 || Type == 2 || Type == -114)
	 return 0;

 return CPlayer::IsWState(Player,Type);
}

int __fastcall ShortsCheck(int xItem, void *edx, int Type)
{
	IItem Item((void*)xItem);

	TargetFind myTarget(0, 1, *(DWORD*)(xItem + 32));
	int xPlayer = (int)myTarget.getTarget();

	IChar IPlayer((void*)xPlayer);
	
	if (Item.GetType() == 4 && IPlayer.GetBuffValue(BuffNames::ArmorWears) && !IPlayer.GetBuffValue(BuffNames::SuitsUsing))
		return 0;
	if (Item.GetType() == 4 && !IPlayer.GetBuffValue(BuffNames::ArmorWears) && IPlayer.GetBuffValue(BuffNames::SuitsUsing))
		return 0;

	if (Item.GetType() == 3 && IPlayer.GetBuffValue(BuffNames::CostumeEffect) && !IPlayer.GetBuffValue(BuffNames::CostumeEffectCheck))
		return 0;

	if (Item.GetType() == 3 && !IPlayer.GetBuffValue(BuffNames::CostumeEffect) && IPlayer.GetBuffValue(BuffNames::CostumeEffectCheck))
		return 0;

	return CItem::IsState(xItem, Type);
}

int __fastcall ShortsFix(int Player, void *edx, int Type)
{
	IChar IPlayer((void*)Player);

	if (Type == 4 && IPlayer.GetBuffValue(BuffNames::ArmorWears) && !IPlayer.GetBuffValue(BuffNames::SuitsUsing))
		return 0;

	if (Type == 4 && !IPlayer.GetBuffValue(BuffNames::ArmorWears) && IPlayer.GetBuffValue(BuffNames::SuitsUsing))
		return 0;

	if (Type == 3 && IPlayer.GetBuffValue(BuffNames::CostumeEffect) && !IPlayer.GetBuffValue(BuffNames::CostumeEffectCheck))
		return 0;

	if (Type == 3 && !IPlayer.GetBuffValue(BuffNames::CostumeEffect) && IPlayer.GetBuffValue(BuffNames::CostumeEffectCheck))
		return 0;

	if (Type == -3 && IPlayer.GetBuffValue(2035) < 5) {
		int old = IPlayer.GetBuffValue(2035);
		IPlayer.UpdateBuff(2035, BuffNames::BuffTime, old + 1);
		return 0;
	}

	return CPlayer::IsWState(Player, Type);
}

int __fastcall CustomWeaponsFix(int Player, void *edx, int Type)
{
	IChar IPlayer((void*)Player);

	if (IPlayer.IsOnline() && Type == 0 && !IPlayer.IsBuff(2034) && CPlayer::IsWState(Player,Type)) {
		IPlayer.Buff(2034, BuffNames::BuffTime, 0);
		return 0;
	}

	return CPlayer::IsWState(Player, Type);
}

int __fastcall CustomWeapFix(int Item, void *edx, int Argument)
{
	IItem IItem((void*)Item);

	if (!IItem.Exists())
		return 0;

	TargetFind myTarget(0, 1, *(DWORD*)(Item + 32));
	int xPlayer = (int)myTarget.getTarget();
	IChar IPlayer((void*)xPlayer); 
	
	if (IPlayer.IsOnline() && isItemCustomWeapon(IItem.CheckIndex()) && !IPlayer.IsBuff(BuffNames::custWeap) && CItem::IsState(Item, 1)) {
		int Old = *(DWORD *)(xPlayer + 156);
		CPlayer::AddWState((int)IPlayer.GetOffset(), IItem.GetType());
		(*(void(__thiscall **)(int, int))(*(DWORD *)Item + 104))(Item, (int)IPlayer.GetOffset());
		*(DWORD *)(xPlayer + 156) = Old;
		int Show = *(WORD *)(*(DWORD *)(Item + 40) + 64);
		IPlayer.UpdateBuff(BuffNames::custWeap, BuffNames::BuffTime, Show);
		IPlayer.Buff(2034, BuffNames::BuffTime, 0);
		
		return 0;
	}

	
	return CItem::IsState(Item, Argument);
}

int __fastcall ArmorRiding(int Item, void *edx, int Argument)
{
	IItem IItem((void*)Item);

	if (!IItem.Exists())
		return 0;

	TargetFind myTarget(0, 1, *(DWORD*)(Item + 32));
	int xPlayer = (int)myTarget.getTarget();
	IChar IPlayer((void*)xPlayer);
	if (IPlayer.IsOnline() && isItemRidingArmor(IItem.CheckIndex()) && IPlayer.GetBuffValue(2035) < 5 && CItem::IsState(Item, 1)) {
		CPlayer::AddWState((int)IPlayer.GetOffset(), IItem.GetType());
		(*(void(__thiscall **)(int, int))(*(DWORD *)Item + 104))(Item, (int)IPlayer.GetOffset());
		int old = IPlayer.GetBuffValue(2035);
		IPlayer.UpdateBuff(2035, BuffNames::BuffTime, old+1);
		
		return 0;
	}

	
	return CItem::IsState(Item, Argument);
}

int __cdecl FriendList(char Name) {

	return CPlayer::FindPlayerByName(Name);
}

void __cdecl ServerStatus(int StatusWindow, int Type, const char* Text, int Size) {
	CScreen::Add(StatusWindow, Type, Text, Size);


	CScreen::Add(StatusWindow, 1, " %s", getUptime().c_str());
	CScreen::Add(StatusWindow, 1, " %s", getSysUpTime().c_str());

	
	CScreen::Add(StatusWindow, 1, " Online Players: %d", InterlockedExchangeAdd(&OnlinePlayers, 0));
	CScreen::Add(StatusWindow, 1, " Fake Shops: %d", EFakePlayers);
	CScreen::Add(StatusWindow, 1, " Active Channels: %d", ChannelActivated);
	CScreen::Add(StatusWindow, 2, " Blocked Players: %d", PlayerBlockCheck.size());

	CScreen::Add(StatusWindow, 3, " ==============================================================");
	CScreen::Add(StatusWindow, 4, " Lottery: %d", Lottery.size());
	CScreen::Add(StatusWindow, 5, " Lotto: %d", XLottery.size());
	CScreen::Add(StatusWindow, 6, " Boss EXP: %d", BossEXPRegistration.size());
	CScreen::Add(StatusWindow, 7, " F10 Company: %d", F10Registration.size());
	CScreen::Add(StatusWindow, 8, " Mautareta: %d", MautRegistration.size());
	CScreen::Add(StatusWindow, 9, " Raid: %d", RaidSystem.size());
	CScreen::Add(StatusWindow, 10, " Battlefield: %d", BattlefieldRegistration.size());
	CScreen::Add(StatusWindow, 11, " Triangular Battle: %d", TBRegistration.size());
	CScreen::Add(StatusWindow, 12, " Capture The Flag: %d", CaptureRegistration.size());
	CScreen::Add(StatusWindow, 13, " Last Man Standing: %d", LastManRegistration.size());
	CScreen::Add(StatusWindow, 0, " Duel Tournament: %d", DuelRegistrationList.size());
	CScreen::Add(StatusWindow, 0, " World Cup: %d", CupRegistration.size());
	CScreen::Add(StatusWindow, 0, " Party Vs Party: %d", PTRegisterSize);
	CScreen::Add(StatusWindow, 0, " Destructing Key: %d", ScenarioRegistration.size());
	CScreen::Add(StatusWindow, 0, " Protecting Leader: %d", ProtectLeaderList.size());
	CScreen::Add(StatusWindow, 0, " Suffering Valley: %d", SufferingValleyRegistration.size());
	CScreen::Add(StatusWindow, 0, " Hunting Guild: %s", HuntingName.c_str());
}

bool aisEssensed(IChar IPlayer, int IID){
	return ((IPlayer.GetBuffValue(BuffNames::Essence1) == IID) || (IPlayer.GetBuffValue(BuffNames::Essence2) == IID) || (IPlayer.GetBuffValue(BuffNames::Essence3) == IID) || (IPlayer.GetBuffValue(BuffNames::Essence4) == IID) || (IPlayer.GetBuffValue(BuffNames::Essence5) == IID));
}

int __fastcall MirrorFixa(int Item, void *edx, int Argument)
{
	IItem IItem((void*)Item);

	if (!IItem.Exists())
		return 0;

	TargetFind myTarget(0, 1, *(DWORD*)(Item + 32));
	int xPlayer = (int)myTarget.getTarget();

	IChar IPlayer((void*)xPlayer);
	
	if (isPet(IItem.CheckIndex()) && IPlayer.IsOnline() && CItem::IsState(Item, 1)) {

		if ((isNormalPet(IItem.CheckIndex()) && IPlayer.GetBuffValue(BuffNames::PetOwner)) || (isMonsterPet(IItem.CheckIndex()) && IPlayer.GetBuffValue(BuffNames::PetOwner2)) || (isPremiumPet(IItem.CheckIndex()) && IPlayer.GetBuffValue(BuffNames::PetOwner3)))
			return CItem::IsState(Item, Argument);

		CPlayer::AddWState((int)IPlayer.GetOffset(), IItem.GetType());
		(*(void(__thiscall **)(int, int))(*(DWORD *)Item + 104))(Item, (int)IPlayer.GetOffset());
		return 0;
	}

	if (isSoulPocket(IItem.CheckIndex()) && CItem::IsState(Item, 1) && !IPlayer.IsBuff(3704)) {
		CPlayer::AddWState((int)IPlayer.GetOffset(), IItem.GetType());
		(*(void(__thiscall **)(int, int))(*(DWORD *)Item + 104))(Item, (int)IPlayer.GetOffset());
		IPlayer.Buff(3704, BuffNames::BuffTime, 0);
		return 0;
	}

	if (isNecklace2(IItem.CheckIndex()) && CItem::IsState(Item, 1) && !IPlayer.IsBuff(3705)) {
		CPlayer::AddWState((int)IPlayer.GetOffset(), IItem.GetType());
		(*(void(__thiscall **)(int, int))(*(DWORD *)Item + 104))(Item, (int)IPlayer.GetOffset());
		IPlayer.Buff(3705, BuffNames::BuffTime, 0);
		return 0;
	}
	
	return CItem::IsState(Item,Argument);
}

int __fastcall SuitsFixe(int xItem, void *edx, int Argument)
{
	IItem Item((void*)xItem);

	int Check = CItem::IsState(xItem, Argument);

	if (Item.Exists() && isItemRiding(Item.CheckIndex()) && Check) {
		TargetFind myTarget(0, 1, *(DWORD*)(xItem + 32));
		int xPlayer = (int)myTarget.getTarget();
		IChar IPlayer((void*)xPlayer);
		if (IPlayer.IsOnline()) {
			if (!IPlayer.GetBuffValue(BuffNames::RidingUsing)) {

				if (isBattleRiding(Item.CheckIndex()))
					IPlayer.UpdateBuff(BuffNames::RidingIID, BuffNames::BuffTime, Item.GetIID());

				CPlayer::AddWState((int)IPlayer.GetOffset(), Item.GetType());
				(*(void(__thiscall **)(int, int))(*(DWORD *)xItem + 104))(xItem, (int)IPlayer.GetOffset());

				IPlayer.UpdateBuff(BuffNames::RidingUsing, BuffNames::BuffTime, xItem);
			}
		}
		return 0;
	}

	return Check;
}

int __fastcall IsNormal(int Player, void *edx)
{
	IChar IPlayer((void*)Player);

	if (IPlayer.IsValid())
	{
		if (IPlayer.GetClass() == 3)
		{
			if (IPlayer.IsBuff(329))
				return 0;
		}

		if (IPlayer.GetClass() < 5 && CChar::IsGState((int)IPlayer.GetOffset(),512))
		{
			if (IPlayer.IsBuff(327))
				return 0;
		}
	}

	return CChar::IsNormal(Player);
}

int __fastcall IsStateCheck(int Item, void *edx, int Value)
{
	IItem IItem((void*)Item);

	if (!IItem.Exists())
		return 0;

	int Check = CItem::IsState(Item, Value);

	if (PlayerOffset.count(*(DWORD*)(Item + 32))) {
		int player = PlayerOffset.findValue(*(DWORD*)(Item + 32));
		IChar IPlayer((void*)player);

		if (IPlayer.IsOnline()) {

			if (!(*(int(__thiscall **)(int, int))(*(DWORD *)Item + 148))(Item, Item) && IItem.GetAmount() > 1) {
				CDBSocket::Write(94, "d", IItem.GetIID());
				*(DWORD *)((int)Item + 52) = 1;
			}

			if (IItem.GetAmount() <= 0) {
				CDBSocket::Write(94, "d", IItem.GetIID());
				return 0;
			}

			if (Check) {
				int ItemIndex = IItem.CheckIndex();
				int ItemStat = 0;

				itemStat.Enter();
				if (GetItemStat.count(IItem.GetIID()))
					ItemStat = GetItemStat.find(IItem.GetIID())->second;
				itemStat.Leave();

				if (ItemIndex >= 3381 && ItemIndex <= 3383)
					IPlayer.UpdateBuff(BuffNames::MirrorBuff, BuffNames::BuffTime, IItem.GetIID());

				if (ItemIndex >= 2986 && ItemIndex <= 3009)
				{
					int TriGrade = IPlayer.GetBuffValue(BuffNames::TrigramGrade);

					int GetCurrentGrade = 0;

					if (ItemStat)
						GetCurrentGrade = TrigramGrade(IItem.GetOffset());

					if (!TriGrade || GetCurrentGrade < TriGrade)
						IPlayer.UpdateBuff(BuffNames::TrigramGrade, BuffNames::BuffTime, GetCurrentGrade);

					if (GetCurrentGrade >= 0 && GetCurrentGrade <= 14) {
						if (ItemIndex == 2986) IPlayer.UpdateBuff(BuffNames::TrigramHP, BuffNames::BuffTime, TriagramStats[0][GetCurrentGrade]);
						else if (ItemIndex == 2994) IPlayer.UpdateBuff(BuffNames::TrigramHP, BuffNames::BuffTime, TriagramStats[1][GetCurrentGrade]);
						else if (ItemIndex == 3002) IPlayer.UpdateBuff(BuffNames::TrigramHP, BuffNames::BuffTime, TriagramStats[2][GetCurrentGrade]);
						else if (ItemIndex == 2987) IPlayer.UpdateBuff(BuffNames::TrigramMP, BuffNames::BuffTime, TriagramStats[3][GetCurrentGrade]);
						else if (ItemIndex == 2995) IPlayer.UpdateBuff(BuffNames::TrigramMP, BuffNames::BuffTime, TriagramStats[4][GetCurrentGrade]);
						else if (ItemIndex == 3003) IPlayer.UpdateBuff(BuffNames::TrigramMP, BuffNames::BuffTime, TriagramStats[5][GetCurrentGrade]);
						else if (ItemIndex == 2988) IPlayer.UpdateBuff(BuffNames::TrigramAtk, BuffNames::BuffTime, TriagramStats[6][GetCurrentGrade]);
						else if (ItemIndex == 2996) IPlayer.UpdateBuff(BuffNames::TrigramAtk, BuffNames::BuffTime, TriagramStats[7][GetCurrentGrade]);
						else if (ItemIndex == 3004) IPlayer.UpdateBuff(BuffNames::TrigramAtk, BuffNames::BuffTime, TriagramStats[8][GetCurrentGrade]);
						else if (ItemIndex == 2989) IPlayer.UpdateBuff(BuffNames::TrigramStr, BuffNames::BuffTime, TriagramStats[9][GetCurrentGrade]);
						else if (ItemIndex == 2997) IPlayer.UpdateBuff(BuffNames::TrigramStr, BuffNames::BuffTime, TriagramStats[10][GetCurrentGrade]);
						else if (ItemIndex == 3005) IPlayer.UpdateBuff(BuffNames::TrigramStr, BuffNames::BuffTime, TriagramStats[11][GetCurrentGrade]);
						else if (ItemIndex == 2990) IPlayer.UpdateBuff(BuffNames::TrigramAgi, BuffNames::BuffTime, TriagramStats[12][GetCurrentGrade]);
						else if (ItemIndex == 2998) IPlayer.UpdateBuff(BuffNames::TrigramAgi, BuffNames::BuffTime, TriagramStats[13][GetCurrentGrade]);
						else if (ItemIndex == 3006) IPlayer.UpdateBuff(BuffNames::TrigramAgi, BuffNames::BuffTime, TriagramStats[14][GetCurrentGrade]);
						else if (ItemIndex == 2991) IPlayer.UpdateBuff(BuffNames::TrigramInt, BuffNames::BuffTime, TriagramStats[15][GetCurrentGrade]);
						else if (ItemIndex == 2999) IPlayer.UpdateBuff(BuffNames::TrigramInt, BuffNames::BuffTime, TriagramStats[16][GetCurrentGrade]);
						else if (ItemIndex == 3007) IPlayer.UpdateBuff(BuffNames::TrigramInt, BuffNames::BuffTime, TriagramStats[17][GetCurrentGrade]);
						else if (ItemIndex == 2992) IPlayer.UpdateBuff(BuffNames::TrigramWis, BuffNames::BuffTime, TriagramStats[18][GetCurrentGrade]);
						else if (ItemIndex == 3000) IPlayer.UpdateBuff(BuffNames::TrigramWis, BuffNames::BuffTime, TriagramStats[19][GetCurrentGrade]);
						else if (ItemIndex == 3008) IPlayer.UpdateBuff(BuffNames::TrigramWis, BuffNames::BuffTime, TriagramStats[20][GetCurrentGrade]);
						else if (ItemIndex == 2993) IPlayer.UpdateBuff(BuffNames::TrigramHth, BuffNames::BuffTime, TriagramStats[21][GetCurrentGrade]);
						else if (ItemIndex == 3001) IPlayer.UpdateBuff(BuffNames::TrigramHth, BuffNames::BuffTime, TriagramStats[22][GetCurrentGrade]);
						else if (ItemIndex == 3009) IPlayer.UpdateBuff(BuffNames::TrigramHth, BuffNames::BuffTime, TriagramStats[23][GetCurrentGrade]);
					}
				}

				if (ItemIndex >= 3018 && ItemIndex <= 3020 && ItemStat)
				{
					int GetTaegeukPrefix = ItemStat / 1000;
					if (GetTaegeukPrefix) IPlayer.UpdateBuff(BuffNames::Taegeuk, BuffNames::BuffTime, GetTaegeukPrefix);
				}
			}
		}
	}
	return Check;
}

int __cdecl OpenPortalFix(int Player)
{
	IChar IPlayer((void*)Player);

	if (IPlayer.isRidingMode())
	{
		IPlayer.SystemMessage("You can not use portal while riding.",TEXTCOLOR_RED);
		return 0;
	}
	
	return CPortal::OpenPortal(Player);
}

int __fastcall MyForPortalCheck(void *Value, void *edx, int Player)
{
	IChar IPlayer((void*)Player);
	if (IPlayer.IsOnline() && (*(DWORD*)((int)Value + 4) & 65536))
	{
		CChar::Unlock(IPlayer.GetOffset());
		IPlayer.Buff(331,3,0);
		CChar::Lock(IPlayer.GetOffset());
	}
	return Undefined::ForPortalCheck(Value,Player);
}

int __fastcall RidingFix(void *Argument, void *edx)
{
	int Check = Undefined::GetValue(Argument);
	int Itemx = *(DWORD*)(Check + 4);
	IItem Item((void*)Itemx);

	TargetFind myTarget(0, 1, *(DWORD*)(Itemx + 32));
	int xPlayer = (int)myTarget.getTarget();
	IChar IPlayer((void*)xPlayer);
	
	if (IPlayer.IsOnline())
	{
		if (IPlayer.IsOnline() && isItemRiding(Item.CheckIndex()) && IPlayer.GetBuffValue(BuffNames::RidingUsing) != Itemx) {
			IPlayer.SystemMessage("You must first wear the riding before using it.", TEXTCOLOR_RED);
			return Check;
		}

		if (IPlayer.IsOnline() && isItemRiding(Item.CheckIndex()) && CChar::IsGState((int)IPlayer.GetOffset(), 4))
			return Check;

		if (IPlayer.IsOnline() && isItemRiding(Item.CheckIndex()) && CChar::IsGState((int)IPlayer.GetOffset(), 512))
			return Check;

		if (IPlayer.IsOnline() && isItemRiding(Item.CheckIndex()) && (IPlayer.IsBuff(18) || IPlayer.IsBuff(19) || IPlayer.IsBuff(313) || IPlayer.IsBuff(329)))
			return Check;

		int MapX = IPlayer.GetX() >> 13;
		int MapY = IPlayer.GetY() >> 13;

		if (IPlayer.IsOnline() && (ItemDisable.count(Item.CheckIndex()*(IPlayer.GetMap() + 1000)) || ItemDisable.count(Item.CheckIndex()*(((MapX)+1000)*((MapY)+100))) || ItemDisable.count(Item.CheckIndex() * 1255))) {
			IPlayer.SystemMessage("This item usage has been temporarly disabled", TEXTCOLOR_RED);
			return Check;
		}

		if (IPlayer.IsOnline() && isItemRiding(Item.CheckIndex()) && CChar::IsGState((int)IPlayer.Offset, 256) && IPlayer.GetMap() != LawlessMap) {
			IPlayer.SystemMessage("You can not use riding pet while youre in sin mode.", TEXTCOLOR_RED);
			return Check;
		}

		if (IPlayer.IsOnline() && isItemRiding(Item.CheckIndex()) && CSMap::IsOnTile(*(void **)((int)IPlayer.Offset + 320), (int)IPlayer.Offset + 332, 1048576)) {
			IPlayer.SystemMessage("You can not use riding pet while youre in castle war zone.", TEXTCOLOR_RED);
			return Check;
		}

		if (IPlayer.IsOnline() && isItemRiding(Item.CheckIndex()) && !IPlayer.IsBuff(349))
		{
			if (IPlayer.IsValid())
			{
				if (!IPlayer.isPortalMode() && isBattleRiding(Item.CheckIndex())) {
					int Satiety = IPlayer.GetBuffValue(BuffNames::Satiety);
					if (Satiety>=5)
						IPlayer.AddHp(ceil(((double)Satiety / 5)));
				}

				IPlayer.Buff(313, 3, 0);
				if (Item.CheckIndex() >= 3412 && Item.CheckIndex() <= 3419) IPlayer.EnableRiding(Item.CheckIndex() - 3411);
				if (Item.CheckIndex() == 4149) IPlayer.EnableRiding(9);
				if (Item.CheckIndex() == 4150) IPlayer.EnableRiding(10);
				if (Item.CheckIndex() == 4151) IPlayer.EnableRiding(11);
				if (Item.CheckIndex() == 4152) IPlayer.EnableRiding(14);
				if (Item.CheckIndex() == 4153) IPlayer.EnableRiding(15);
				if (Item.CheckIndex() == 4156) IPlayer.EnableRiding(12);
				if (Item.CheckIndex() == 4157) IPlayer.EnableRiding(13);
				if (Item.CheckIndex() == 4158) IPlayer.EnableRiding(16);
				if (Item.CheckIndex() == 4159) IPlayer.EnableRiding(17);
				if (Item.CheckIndex() == 4160) IPlayer.EnableRiding(18);
				if (Item.CheckIndex() == 4161) IPlayer.EnableRiding(31);
				if (Item.CheckIndex() == 4162) IPlayer.EnableRiding(32);
				if (Item.CheckIndex() == 6022) IPlayer.EnableRiding(20);
				if (Item.CheckIndex() == 6021) IPlayer.EnableRiding(21);
				if (Item.CheckIndex() == 6023) IPlayer.EnableRiding(22);
				if (Item.CheckIndex() == 6024) IPlayer.EnableRiding(23);
				if (Item.CheckIndex() == 7880) IPlayer.EnableRiding(24);
				if (Item.CheckIndex() == 7881) IPlayer.EnableRiding(25);
				if (Item.CheckIndex() == 7882) IPlayer.EnableRiding(26);
				if (Item.CheckIndex() == 7883) IPlayer.EnableRiding(27);
				if (Item.CheckIndex() == 9663) IPlayer.EnableRiding(28);
				if (Item.CheckIndex() == 9939) IPlayer.EnableRiding(29);
				if (Item.CheckIndex() == 9683) IPlayer.EnableRiding(30);
				if (Item.CheckIndex() == 7126) IPlayer.EnableRiding(7);
			}

			return Check;
		}

		if (IPlayer.IsOnline() && isItemRiding(Item.CheckIndex()) && IPlayer.IsBuff(349))
		{
			IPlayer.Buff(313, 3, 0);
			IPlayer.DisableRiding();
			return Check;
		}
	}
	return Check;
}

int maxRange(int pet1, int pet2, int pet3)
{
	int max = (pet1 < pet2) ? pet2 : pet1;
	return ((max < pet3) ? pet3 : max);
}

int __cdecl PetPickRange(int Check, int Val)
{
	int result = CChar::GetRange(Check, Val);
	IChar IPlayer((void*)(Check - 332));
	
	if (result > 64 && IPlayer.GetType() == 0 && IPlayer.IsValid()) {
		int Range = IPlayer.GetPickRange();

		if (Range)
			result -= Range;
	}

	return result;
}

int __cdecl KnightBlabla(int BuffID, __int32 Time, int Stat, int Object)
{
	return 0;
}

void __cdecl SendBState(void* Player, const char Type, const char* Format, int id, __int64 Buff, int Time, int a3) {
	CPlayer::Write(Player, Type, "bIdd", 74, __int64(Buff), Time, 0);
}

void __cdecl SendBState2(void* Player, const char Type, const char* Format, int id, __int64 Buff, int a3) {
	CPlayer::Write(Player, Type, "bI", 75, __int64(Buff));
}

int __cdecl ArmorShowFix(void* Player, BYTE bType, const char* Format, int id, int t, unsigned short item) {
	
	return CChar::WriteInSight(Player, bType, Format, id, t, item);
}

int __cdecl FishingItem(int Index,int Prefix, int Value, int Argument){
	if(Index==237 && OriginalLowest) Index = OriginalLowest;
	if(Index==239 && OriginalLow) Index = OriginalLow;
	if(Index==240 && OriginalNormal) Index = OriginalNormal;
	if(Index==444 && OriginalHard) Index = OriginalHard;
	if(Index==241 && OriginalHardest) Index = OriginalHardest;

	if (!FishingList.empty()) {
		int Chance = CTools::Rate(1, 1000);
		Index = 0;
		Value = 0;
		for(auto x = FishingList.begin();x!=FishingList.end();x++){
			std::vector<ChanceItem> fs = x->second;
			int ItemC = CTools::Rate(0, fs.size() - 1);
			ChanceItem f = fs[ItemC];
			if ((f.Chance * 10) >= Chance) {
				Index = f.Index;
				Value = f.Amount;
				break;
			}
		}
		if (!Index) {
			std::vector<ChanceItem> fs = FishingList.rbegin()->second;
			int ItemC = CTools::Rate(0, fs.size() - 1);
			ChanceItem f = fs[ItemC];
			Index = f.Index;
			Value = f.Amount;
		}
	}

	return CItem::CreateItem(Index,Prefix,Value,Argument);
}

int __fastcall MyInventoryCheck(int Player, void *edx)
{
	return GetInventorySize(Player, 0);
}

void PetAttack(IChar Attacker,IChar ITarget,IChar IPlayer) {
	int DMG = CChar::GetAttack(Attacker.GetOffset());
	if (Attacker.CheckHit(ITarget, DMG)) {
		int NormalDamage = 0, DamageArgument = 0, EBDamage = 0, Check = 0, TypeKind = 0, GetType = 0;
		TypeKind = (*(int(__thiscall **)(LONG, void *))(*(DWORD *)ITarget.GetOffset() + 148))((int)ITarget.GetOffset(), Attacker.GetOffset());

		Check = (*(int(__thiscall**)(LONG, void*, unsigned int, int*, int*, int*, DWORD))(*(DWORD*)ITarget.GetOffset() + 72))((int)ITarget.GetOffset(), IPlayer.GetOffset(), DMG, &NormalDamage, &DamageArgument, &EBDamage, 0);
		GetType = Check | 2 * DamageArgument | 4 * TypeKind;

		if(NormalDamage)
			IPlayer.SystemMessage("Your attacking pet gave " + Int2String(NormalDamage) + " Extra damage.", TEXTCOLOR_PINK);

		CPlayer::Write(IPlayer.GetOffset(), 0xFE, "dddddbd", 189, IPlayer.GetID(), ITarget.GetID(), NormalDamage, EBDamage, GetType, 0);
	}
	else
		IPlayer.SystemMessage("Missed hit from your attacking pet", TEXTCOLOR_FAILED);
}

int __cdecl AttackMsg(void* Player, const char Type, const char* Format, int id1, int id2, int Damage, int EBDamage, int GetType) {
	int SPDmg = 0;

	if (Damage > 1) {
		SPDmg = SoulPocketDamage(Player, Damage);
		Damage = Damage - SPDmg;
	}

	IChar Attacker(Player);

	//if (Attacker.IsOnline()) {
	//	int Around = Attacker.GetObjectListAround(15);

	//	while (Around)
	//	{
	//		IChar Object((void*)CBaseList::Offset((void*)Around));
	//		if (Attacker.IsOnline() && Attacker.GetType() == 0 && Object.GetType() == 0){
	//			CPlayer::Write(IPlayer.GetOffset(), 0xFE, "dddddbd", 189, IPlayer.GetID(), ITarget.GetID(), NormalDamage, EBDamage, GetType, 0);

	//		}
	//		Around = CBaseList::Pop((void*)Around);
	//	}
	//}

	if (Attacker.IsOnline() && Attacker.GetType() == 1 && Attacker.GetDef() == 54123) {
		IChar ITarget((void*)Attacker.GetMobTanker());
		if (ITarget.IsOnline()) {
			int PlayerM = *(DWORD *)((int)Player + 232);
			IChar IPlayer((void*)PlayerM);
			if (IPlayer.IsOnline()) {
				int Index = Attacker.GetMobIndex();
				ConfigPetTime pet = PetTime.count(IPlayer.GetBuffValue(BuffNames::PetOwner)) ? PetTime.find(IPlayer.GetBuffValue(BuffNames::PetOwner))->second : ConfigPetTime();
				if (pet.Monster != Index) {
					pet = PetTime.count(IPlayer.GetBuffValue(BuffNames::PetOwner2)) ? PetTime.find(IPlayer.GetBuffValue(BuffNames::PetOwner2))->second : ConfigPetTime();
					if(pet.Monster != Index)
						pet = PetTime.count(IPlayer.GetBuffValue(BuffNames::PetOwner3)) ? PetTime.find(IPlayer.GetBuffValue(BuffNames::PetOwner3))->second : ConfigPetTime();
				}

				if (pet.AttackPet == 2) {
					int Around = Attacker.GetObjectListAround(Attacker.GetMobRange());
					int Count = 0;
					while (Around)
					{
						IChar Object((void*)CBaseList::Offset((void*)Around));

						if (IPlayer.IsValid() && Object.IsValid() && Object.GetType() == 1 && Object.GetMobTanker() == PlayerM && (*(int(__thiscall **)(int, int, DWORD))(*(DWORD *)IPlayer.GetOffset() + 176))((int)IPlayer.GetOffset(), (int)Object.GetOffset(), 0))
						{
							Count++;
							PetAttack(Attacker, Object, IPlayer);
						}

						Around = CBaseList::Pop((void*)Around);
					}
					if (Count > 1) {
						Attacker.AddFxToTarget("effect_ef080", 1, 0, 0);
						Attacker.AddFxToTarget("effect_ef081", 1, 0, 0);
						Attacker.AddFxToTarget("effect_ef082", 1, 0, 0);
						srand(time(0));
						std::random_shuffle(pet.effects.begin(),pet.effects.end());
						ITarget.AddFxToTarget(pet.effects.front(), 1, 0, 0);
						*(DWORD *)((int)Player + 472) = GetTickCount() + pet.AOEDelay;
						Attacker.UnAttack(pet.AOEDelay);
						return 0;
					}
				}
				else
					PetAttack(Attacker, ITarget, IPlayer);
			}
		}
	}
	return CChar::WriteInSight(Player, 62, "ddddbd", id1, id2, Damage, EBDamage, GetType, SPDmg);
}

int __cdecl SkillMSG(void* Player, const char Type, const char* Format, char TargetType, char SkillID, int PlayerID, int TargetID, int Damage, unsigned short GetType2) {
	
	int SPDmg = 0;
	if (Damage > 1) {
		SPDmg = SoulPocketDamage(Player, Damage);
		Damage = Damage - SPDmg;
	}

	return CChar::WriteInSight(Player, 10, "bbddddd", TargetType, SkillID, PlayerID, TargetID, (int)Damage, (int)GetType2, SPDmg);
}

void __cdecl PlayerSkillMSG(void* Player, const char Type, const char* Format, char TargetType, char SkillID, int PlayerID, int TargetID, int Damage, unsigned short GetType2) {
	int SPDmg = 0;
	
	if (Damage > 1) {
		SPDmg = _SoulPocketDamage(Player, Damage);
		Damage = Damage - SPDmg;
	}	
	
	/*IChar Attacker(Player);
	if (Attacker.IsOnline()) {
		int Around = Attacker.GetObjectListAround(15);

		while (Around)
		{
			IChar Object((void*)CBaseList::Offset((void*)Around));

			if (Attacker.IsValid() && Object.IsValid() && Object.GetOffset() != Attacker.GetOffset() && Object.GetType() == 0 && !(Attacker.GetType() == 1 && *(DWORD *)((int)Player + 232) == (int)Object.GetOffset()) && Object.GetBuffValue(BuffNames::TargetAttack) == TargetID)
				CPlayer::Write(Object.GetOffset(), 0xFE, "dddddbd", 189, Object.GetID(), TargetID, 0, 1, TargetType, 0);

			Around = CBaseList::Pop((void*)Around);
		}
	}*/

	return CPlayer::Write(Player, 10, "bbddddd", TargetType, SkillID, PlayerID, TargetID, (int)Damage, (int)GetType2, SPDmg);
}

int __cdecl EBSkillMSG(void* Player, const char Type, const char* Format, char SkillID, int PlayerID, int TargetID, char r1, char r2, unsigned short Damage, unsigned short GetType2, char Last) {
	int SPDmg = 0; 

	if (Damage > 1) {
		SPDmg = SoulPocketDamage(Player, Damage);
		Damage = Damage - SPDmg;
	}
	
	/*IChar Attacker(Player);
	
	if (Attacker.IsOnline()) {
		int Around = Attacker.GetObjectListAround(15);

		while (Around)
		{
			IChar Object((void*)CBaseList::Offset((void*)Around));

			if (Attacker.IsValid() && Object.IsValid() && Object.GetOffset() != Attacker.GetOffset() && Object.GetType() == 0 && (!(Attacker.GetType() == 1 && Attacker.GetDef() == 54123 && *(DWORD *)((int)Player + 232) == (int)Object.GetOffset()) || Attacker.GetType() == 0) && Object.GetBuffValue(BuffNames::TargetAttack) == TargetID)
				CPlayer::Write(Object.GetOffset(), 0xFE, "dddddbd", 189, Object.GetID(), TargetID, 0, 1, Last, 0);

			Around = CBaseList::Pop((void*)Around);
		}
	}*/

	return CChar::WriteInSight(Player, 63, "bddbbwwbd", SkillID, PlayerID, TargetID, r1, r2,Damage, GetType2,Last, SPDmg);
}

int __cdecl MailShowFix(void* Socket,  const char* Format, char id1, char id2) {
	
	return CIOBuffer::PacketBuilder(Socket, "bd", id1, id2+1);
}

void __cdecl SendShopMsg(void* Player, const char Type, const char* Format, int iid, int a6) {
	IChar IPlayer(Player);

	if (a6 == 26) {
		int Shopped = IPlayer.GetBuffValue(2019);
		if (Shopped)
			CPlayer::Write(Player, 8, "dbd", iid, a6, Shopped);
		else
			CPlayer::Write(Player, Type, Format, iid, a6);
	}
	else
		CPlayer::Write(Player, Type, Format, iid, a6);
}

void __cdecl SendShopMsg2(void* Player, const char Type, const char* Format, int iid, int amount, int a6) {
	IChar IPlayer(Player);

	if (a6 == 26) {
		int Shopped = IPlayer.GetBuffValue(2019);
		if (Shopped)
			CPlayer::Write(Player, 90, "ddbd", iid, amount, 26, Shopped);
	}else
		CPlayer::Write(Player, Type, Format, iid, amount, a6);
}

void *__fastcall CIOCriticalSectionEnter(struct _RTL_CRITICAL_SECTION *a1)
{
	PRTL_CRITICAL_SECTION_DEBUG v4; // ST10_4@2
	LONG v5; // ST14_4@2
	LONG v8; // ST14_4@5
	void *result; // eax@5
	struct _RTL_CRITICAL_SECTION *lpCriticalSection; // [sp+0h] [bp-Ch]@1
	int vars0; // [sp+Ch] [bp+0h]@0
	void *retaddr; // [sp+10h] [bp+4h]@5

	if (a1->LockCount != 0) {
		lpCriticalSection = a1;
		if (!TryEnterCriticalSection(a1))
		{
			v4 = lpCriticalSection[1].DebugInfo;
			v5 = lpCriticalSection[1].LockCount;
			if(lpCriticalSection->LockCount != 0)
				EnterCriticalSection(lpCriticalSection);
		}
		v8 = *(DWORD *)(vars0 + 4);
		result = retaddr;
		lpCriticalSection[1].DebugInfo = (PRTL_CRITICAL_SECTION_DEBUG)retaddr;
		lpCriticalSection[1].LockCount = v8;
	}
	return result;
}

int __cdecl FriendCheck(int Type,const char* Format, int PID, char Choice, const char* Name ) {
	if (FakeNames.count(Name)) {
		TargetFind myTarget(0, 1, PID);
		int Player = (int)myTarget.getTarget();
		if (Player) {
			int FPID = FakeNames.findValue(Name);
			CDBSocket::Write(29, "dbds", PID, 0, FPID, Name);
			CPlayer::Write((void*)Player, 18, "bdsbdb", 0, FPID, Name, (EFakePlayers * -1) <= FPID ? true : false, (EFakePlayers * -1) <= FPID ? 1 : 0, 0);
			
		}
		return 0;
	}

	return CDBSocket::Write(Type, Format, PID, Choice, Name);
}

int __cdecl QuestFix(int Type, const char* Format, int PID, unsigned short QuestID, char Flag, char Clear) {
	return CDBSocket::Write(Type, "dwbbddd", PID, QuestID, Flag, Clear, 0, 0, 0);
}

int __fastcall GoldenCoin(void* Player, void* edx, int Argument, int Item) {
	
	/*IChar IPlayer(Player);
	int Amount = 1;
	int Level = IPlayer.GetLevel();

	if (Level > 70 && Level <= 80)
		Amount = 2;

	if (Level > 80)
		Amount = 3;

	*(DWORD *)(Item + 52) = Amount;*/

	return CPlayer::InsertItem(Player, Argument, Item);
}

int __cdecl CallOfPhy(int BuffID, __int32 Time, int Stat, int Skill) {
	ISkill xSkill((void*)Skill);
	int Buff = CreateBuff(74, 0, (25 * xSkill.GetGrade()) + 25, Skill);
	*(DWORD*)(Buff + 24) = (25 * xSkill.GetGrade()) + 25;
	*(DWORD*)(Buff + 28) = 27;
	return Buff;
}

int __cdecl EmergencyEscape(int BuffID, __int32 Time, int Stat, int Skill) {
	return CreateBuff(BuffID, 15, 0, Skill);
}

char *safe_strcpy(char *dest, size_t size, char *src) {
	if (size > 0) {
		size_t len = strnlen(src, size - 1);
		memcpy(dest, src, len);
		dest[len] = '\0';
	}
	return dest;
}

char* __cdecl WarSetup(char* Dest, const char* Source) {
	if (CWarLoad)
		return NULL;

	return strcpy(Dest, Source);
}

void ServerStartedMessage() {
	DrawMainMenu("Tools");

	CConsole::Black("%s has started %s at : %s",ServerName, Time::GetDayName().c_str(), Time::GetTime().c_str());

}

int __fastcall GuildCreationCheck(void* PT, void* edx) {
	int PartySize = CParty::GetSize(PT);
	if (PartySize > MemberFull1) {
		int LeaderP = *(DWORD *)((int)PT + 20);
		IChar ILeader((void*)LeaderP);
		ILeader.SystemMessage("Your party size has exceeded the limit of " + Int2String(MemberFull1) + " members possible for guild creation.", TEXTCOLOR_RED);
		return 5;
	}
	return PartySize;
}

int __fastcall MLMRewardMoney(void* Player, void* edx, int Argument, int Item) {
	if (!MLMMoneyReward)
		return 0;

	return CPlayer::InsertItem(Player, Argument, Item);
}

int __cdecl MLMCreateMoney(int Index, int Prefix, int Amount, int Argument) {
	if (!MLMMoneyReward)
		return 0;

	return CItem::CreateItem(Index, Prefix, Amount, Argument);
}

int __fastcall MovingScrollFix(int Player, void* edx, int Map, int XY,int Arg1, int Arg2) {
	IChar IPlayer((void*)Player);
	
	if (IPlayer.IsBuff(349)) {
		IPlayer.SystemMessage("You can not use moving scroll while riding.", TEXTCOLOR_RED);
		if (CItem::FindInitItem(511))
			CItem::InsertItem(Player, 27, 511, 0, 1, -1);
		else if (CItem::FindInitItem(512))
			CItem::InsertItem(Player, 27, 512, 0, 1, -1);
		return 0;
	}

	if (Map == EmokMap && IPlayer.IsOnline() && IPlayer.GetMap() != EmokMap) {
		IPlayer.SystemMessage("Please use the Emok NPC to port to Emok.", TEXTCOLOR_RED);
		if (CItem::FindInitItem(511))
			CItem::InsertItem(Player, 27, 511, 0, 1, -1);
		else if(CItem::FindInitItem(512))
			CItem::InsertItem(Player, 27, 512, 0, 1, -1);
		return 0;
	}

	return CPlayer::Teleport(Player, Map, XY, Arg1, Arg2);
}

void __cdecl GStateFix(void* Player, const char Type, const char* Format, int id, int GState) {
	CPlayer::Write(Player, Type, "dI", id, (__int64)GState);
}

void __cdecl SightGStateFix(void* Player, const char Type, const char* Format, int id, int GState) {
	CChar::WriteInSight(Player, Type, "dI", id, (__int64)GState);
}

int __cdecl LoginAttemptsLimit(int Socket, char type, char format, char limit) {
	if (limit == 2 || limit == 3)
		limit = 2;

	return CDBSocket::ProcessHtml(Socket, type, format, limit);
}

int __cdecl Login(int Socket, char type, char format, char a1, int a2, char a3, unsigned char* Items, int ItemsLen) {
	int Check = CDBSocket::ProcessHtml((int)Socket, type, format, a1, a2, a3, Items, ItemsLen);

	if (PeaceEvil && PELoginHTML)
		CDBSocket::ProcessHtml((int)Socket, 74, (unsigned int)"d", PELoginHTML);

	return Check;
}

int __fastcall DebuffMonster(int Monster, void* edx, int Skill) {
	
	if (Monster == (int)GuildRaid::Boss) {
		if(Skill)
			CBuff::Release((void*)Skill, 1);
		return 0;
	}

	return (*(int(__thiscall **)(int, int))(*(DWORD *)Monster + 180))(Monster, Skill);
}

int __fastcall AskParty(int Player, void* edx, int Argument) {

	IChar IPlayer((void*)Player);
	int result = CChar::IsGState(Player, Argument);

	if (!result)
		IPlayer.UpdateBuff(BuffNames::Party, BuffNames::BuffTime, 1);

	return result;
}

int __fastcall OnAskParty(int Player, void* edx, int Argument) {

	IChar IPlayer((void*)Player);
	int result = CChar::IsGState(Player, Argument);

	if (!result) {
		if (!IPlayer.GetBuffValue(BuffNames::Party))
			return 1;

		IPlayer.UpdateBuff(BuffNames::Party, BuffNames::BuffTime, 0);
	}

	return result;
}

int __fastcall AskPvP(int Player, void* edx, int Argument) {

	IChar IPlayer((void*)Player);
	int result = CChar::IsGState(Player, Argument);

	if (!result)
		IPlayer.UpdateBuff(BuffNames::Duel, BuffNames::BuffTime, 1);

	return result;
}

int __fastcall OnAskPvP(int Player, void* edx, int Argument) {

	IChar IPlayer((void*)Player);
	int result = CChar::IsGState(Player, Argument);

	if (!result) {
		if (!IPlayer.GetBuffValue(BuffNames::Duel))
			return 1;

		IPlayer.UpdateBuff(BuffNames::Duel, BuffNames::BuffTime, 0);
	}

	return result;
}

int __cdecl CallsRange(int Value, int Argument)
{
	int Check = CChar::GetRange(Value, Argument);

	if (Check <= CBuffRange) {
		IChar IBuffer((void*)(Value - 332));
		IChar IBuffed((void*)(Argument - 332));

		if (IBuffer.GetOffset() != IBuffed.GetOffset())
			IBuffed.UpdateBuff(BuffNames::CallBuffer, BuffNames::BuffTime, (int)IBuffer.GetOffset());

		return 1;
	}

	return Check;
}

int __fastcall PickCrashFix(void* Player, void* edx, int Argument, int Item) {
	IItem IItem((void*)Item);

	int InitItem = IItem.GetInitItem();

	if (!InitItem)
		return 0;

	int Index = IItem.CheckIndex();

	if (!Index)
		return 0;

	int Check = CPlayer::_InsertItem(Player, Argument, Item);

	if (Check == 1) {
		*(DWORD *)(Item + 40) = InitItem;
		*(DWORD *)(*(DWORD *)(Item + 40) + 64) = Index;
	}

	return Check;
}

int __cdecl MobLevelEggFix(int MobLevel, int PlayerLevel)
{
	if (PlayerLevel > 100) {
		if (MobLevel >= (PlayerLevel - 7))
			return 3;
		else
			return 2;
	}

	return CTools::LvlDiff(MobLevel, PlayerLevel);
}

int __fastcall StandardBuff(int Player, void * edx) {

	if (!STBuffEnabled)
		return 0;

	return CPlayer::IsWearBuffStandard(Player);
}

void __cdecl PlayerSendCreate(void *player, unsigned char Type, const char* Format, long id, const char* name, unsigned char _class, long x, long y, long z, unsigned short direction, unsigned long gState, unsigned char* Items, int ItemsLen, char face, char hair, unsigned __int64 mState64, int target, char* GuildName, long GuildID, char flag, long flagIndex)
{
	IChar IShower(player);
	IChar IPlayer((void*)target);

	if (IPlayer.IsHide())
		return;

	std::string pName(name);
	char* GuildTitle = (char*)CPlayer::GetGuildClassTitle(target);

	if ((int)player != target) {
		int Map = IPlayer.GetMap();
		if (Map == LawlessMap) {
			GuildTitle = 0;
			GuildName = 0;
			pName = IPlayer.ClassName();
		}

		if (Map == TBMap) {
			GuildTitle = 0;
			GuildName = 0;
		}
	}

	Interface <ITools> Tools;
	char *Item = new char[76];

	Tools->Compile(Item, "wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww", *(DWORD*)Items, *(DWORD*)(Items + 2), *(DWORD*)(Items + 4), *(DWORD*)(Items + 6), *(DWORD*)(Items + 8), *(DWORD*)(Items + 10), *(DWORD*)(Items + 12), 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);

	CPlayer::Write(player, 0x32, "dsbdddwImbbIssdbdddIIbbdbd", id, pName.c_str(), _class, x, y, z, direction,
		(unsigned __int64)gState, Item, 76, face, hair, mState64, GuildTitle, GuildName, GuildID, flag, flagIndex,
		0, 0, (__int64)0, (__int64)0, 0, 0, 0, 0, 0);

	delete[] Item;
}

int __cdecl SendExclusiveCreate(unsigned char Type, const char * player, long id, const char* name, unsigned char _class, long x, long y, long z, unsigned short direction, unsigned long gState, unsigned char* Items, int ItemsLen, char face, char hair, unsigned __int64 mState64, int target, char* GuildName, long GuildID, char flag, long flagIndex)
{
	IChar IPlayer((void*)target);
	
	if (IPlayer.IsHide())
		return CObject::WriteExclusive(0xFE, "d", 1);

	std::string pName(name);

	char* GuildTitle = (char*)CPlayer::GetGuildClassTitle(target);

	int Map = IPlayer.GetMap();

	if (Map == LawlessMap) {
		pName = IPlayer.ClassName();
		GuildTitle = 0;
		GuildName = 0;
	}

	if (Map == TBMap) {
		GuildTitle = 0;
		GuildName = 0;
	}

	Interface <ITools> Tools;
	char *Item = new char[76];

	Tools->Compile(Item, "wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww", *(DWORD*)Items, *(DWORD*)(Items + 2), *(DWORD*)(Items + 4), *(DWORD*)(Items + 6), *(DWORD*)(Items + 8), *(DWORD*)(Items + 10), *(DWORD*)(Items + 12), 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);

	int Result = CObject::WriteExclusive(0x32, "dsbdddwImbbIssdbdddIIbbdbd", id, pName.c_str(), _class, x, y, z, direction,
		(unsigned __int64)gState, Item, 76, face, hair, mState64, GuildTitle, GuildName, GuildID, flag, flagIndex,
		0, 0, (__int64)0, (__int64)0, 0, 0, 0, 0, 0);

	delete[] Item;

	return Result;
}

int __fastcall IDFixCreate(int Player, void * edx) {
	return Player;
}

int __cdecl SendTileChange(int Player, void* Packet, int Sight)
{
	LONG Check = CGuild::SendPlayerSight(Player, Packet, Sight);

	if (CGuild::IsWarringPeriod()) {
		IChar IPlayer((void*)Player);
		if(IPlayer.GetProperty(PlayerProperty::CWPlayer))
			CChar::WriteInSight(IPlayer.GetOffset(), 46, "dI", IPlayer.GetID(), (__int64)*(DWORD *)((int)IPlayer.GetOffset() + 280));
	}

	return Check;
}

int __fastcall ReturnToVillage(int Player, void* edx, int Map, int XY, int Arg1, int Arg2) {
	IChar IPlayer((void*)Player);

	if (!(CGuild::IsWarringPeriod() && IPlayer.GetProperty(PlayerProperty::CWPlayer))) {
		if (IPlayer.GetMap() == LawlessMap) {
			int *GetSetXY = new int[2];
			GetSetXY[0] = LawlessSpawnX;
			GetSetXY[1] = LawlessSpawnY;
			int Check = CPlayer::Teleport(Player, LawlessMap, (int)GetSetXY, 0, 1);
			delete[] GetSetXY;
			IPlayer.CancelBuff(BuffNames::RevivalCheck);
			return Check;
		}

		if (IPlayer.GetMap() == BanditsMap && Bandits::Active == true) {
			int *GetSetXY = new int[2];
			GetSetXY[0] = BanditsTX;
			GetSetXY[1] = BanditsTY;
			int FindItem = CPlayer::FindItem(IPlayer.GetOffset(), BanditsMaxDeathItem, 1);
			int Check = CPlayer::Teleport(Player, BanditsMap, (int)GetSetXY, 0, 1);
			delete[] GetSetXY;
			int playerID = IPlayer.GetPID();
			IPlayer.CancelBuff(BuffNames::RevivalCheck);
			CPlayer::RemoveItem(IPlayer.GetOffset(), 9, BanditsIndex, 1);
			CPlayer::RemoveItem(IPlayer.GetOffset(), 9, BanditsMaxDeathItem, 1);
			if (!FindItem){	
			IPlayer.SystemMessage("You have exceeded max death times. Good luck next time", TEXTCOLOR_RED);
			IPlayer.Buff(104, 3600, 0);

		}
			return Check;

		}

		if (isPeaceEvilMode()) {
			if (IPlayer.isSlytherin() && SlytherinDieX && SlytherinDieY) {
				int *GetSetXY = new int[2];
				GetSetXY[0] = SlytherinDieX;
				GetSetXY[1] = SlytherinDieY;
				int Check = CPlayer::Teleport(Player, 0, (int)GetSetXY, SlytherinDieZ, 1);
				delete[] GetSetXY;
				return Check;
			}
			 if (IPlayer.isRavenclaw() && RavenDieX && RavenDieY) {
				int *GetSetXY = new int[2];
				GetSetXY[0] = RavenDieX;
				GetSetXY[1] = RavenDieY;
				int Check = CPlayer::Teleport(Player, 0, (int)GetSetXY, RavenDieZ, 1);
				delete[] GetSetXY;
				return Check;
			}
			 if (IPlayer.isHufflepuff() && HuffleDieX && HuffleDieY) {
				 int *GetSetXY = new int[2];
				 GetSetXY[0] = HuffleDieX;
				 GetSetXY[1] = HuffleDieY;
				 int Check = CPlayer::Teleport(Player, 0, (int)GetSetXY, HuffleDieZ, 1);
				 delete[] GetSetXY;
				 return Check;
			 }
			 if (GryffindorDieX && GryffindorDieY) {
				int *GetSetXY = new int[2];
				GetSetXY[0] = GryffindorDieX;
				GetSetXY[1] = GryffindorDieY;
				int Check = CPlayer::Teleport(Player, 0, (int)GetSetXY, GryffindorDieZ, 1);
				delete[] GetSetXY;
				return Check;
			}
		}
	}

	return CPlayer::Teleport(Player, Map, XY, Arg1, Arg2);
}

int __cdecl WarCannonFix(char NPCCannon, int Player) {
	int Check = CNPC::OpenNPC(NPCCannon, Player);
	
	IChar IPlayer((void*)Player);
	IPlayer.OpenHTML(274);

	return Check;
}

int __cdecl SiegeGunStateFix(void* Player, const char Type, const char* Format, char Type1, int ID, int State) {
	return CChar::WriteInSight(Player, Type, "bdI", Type1, ID, __int64(State));
}

int __cdecl SiegeGunStoneStateFix(void* Player, const char Type, const char* Format, char Type1, int ID, int State, int Index) {
	return CChar::WriteInSight(Player, Type, "bdId", Type1, ID, __int64(State), Index);
}

void __fastcall PlayerGunUnset(int Player, void* edx, int Type) {
	CPlayer::SiegeGunUnset(Player, Type);
	//IChar IPlayer((void*)Player);
	//IPlayer.Teleport(IPlayer.GetMap(), IPlayer.GetX(), IPlayer.GetY(), IPlayer.GetZ());
}

void __cdecl LawlessPortCheck(void* Player, const char Type, const char* Format, signed int Map, int a2, int a3, int a4, int a5) {
	IChar IPlayer(Player);

	if (IPlayer.IsOnline()) {
		int CurMap = IPlayer.GetMap();
		if (CurMap != Map) {
			if (CurMap == LawlessMap) {
				IPlayer.Buff(BuffNames::LawlessPort, 60, 0);
				IPlayer.RemoveSetBlue();
				IPlayer.CancelBuff(104);
			}
		}
	}

	CPlayer::Write(Player, Type, Format, Map, a2, a3, a4, a5);
}

int __cdecl DelSkill(int Value)
{
	CConsole::Red("%d", *(DWORD*)(Value + 4));
	return Undefined::DeleteSkill(Value);
}

std::string GetExeFileName()
{
	char buffer[MAX_PATH];
	GetModuleFileName(NULL, buffer, MAX_PATH);
	return std::string(buffer);
}

std::string GetExePath()
{
	std::string f = GetExeFileName();
	return f.substr(0, f.find_last_of("\\/"));
}

bool startsWith(std::string mainStr, std::string toMatch)
{
	// Convert mainStr to lower case
	std::transform(mainStr.begin(), mainStr.end(), mainStr.begin(), ::tolower);
	// Convert toMatch to lower case
	std::transform(toMatch.begin(), toMatch.end(), toMatch.begin(), ::tolower);
	if (mainStr.find(toMatch) == 0)
		return true;
	else
		return false;
}

int __cdecl AuthSvrFix(char* Message) {
	int Check = CConsole::Red(Message);

	int newPort = *AuthSocket::Port + 2;
	*AuthSocket::Port = newPort;

	string line;

	ifstream fin;
	fin.open("./AuthConfig.txt");
	ofstream temp;
	temp.open("./tempAuth.txt");

	while (getline(fin, line))
	{
		int port = 0;

		if (startsWith(line, "port=") || startsWith(line, "port =")) {
			temp << "port=" << newPort << endl;
		}
		else
			if (startsWith(line, "cmdport=") || startsWith(line, "cmdport ="))
				temp << "cmdport=" << newPort - 1 << endl;
			else
				temp << line << endl;
	}

	temp.close();
	fin.close();

	remove("./AuthConfig.txt");
	rename("./tempAuth.txt", "./AuthConfig.txt");

	std::string Path = GetExePath() + "\\" + AuthSvr;

	CConsole::Blue("[Core Auto-Recovery] Launching %s...", Path.c_str());

	ShellExecute(NULL, "open", Path.c_str(), NULL, NULL, SW_SHOWDEFAULT);

	return Check;
}

int __fastcall AuthDefaultPort(char* value, void* edx, char* type, int Default) {
	string line;

	ifstream fin;
	fin.open("./AuthConfig.txt");

	int port = 0;
	while (getline(fin, line))
	{
		if (sscanf(line.c_str(), "port=%d", &port) == 1 || sscanf(line.c_str(), "port = %d", &port) == 1 || sscanf(line.c_str(), "port= %d", &port) == 1)
			break;
		else
			port = 0;
	}

	fin.close();

	return port ? port : CConfig::GetInt(value, type, Default);
}

int __fastcall ManaCostCheck(void* pSkill, void* edx) {
	return 0;
}

int __cdecl EXPCutDown(int Player, int Type, int InOut, signed __int64 Exp) {
	IChar IPlayer((void*)Player);
	IPlayer.UpdateBuff(BuffNames::EXPLoss, BuffNames::BuffTime, Exp);

	return (*(int(__cdecl **)(int, signed int, signed int, unsigned __int64, unsigned __int64))(*(DWORD *)Player + 88))(Player, 25, 0, Exp, HIDWORD(Exp));
}

int __fastcall StorageItemCheck(void* ItemValue, void* edx) {
	int Check = Undefined::GetValue(ItemValue);

	if (Check) {
		int Item = *(DWORD *)(Check + 4);
		if (Item) {
			int IID = *(DWORD *)(Item + 36);
			itemStat.Enter();
			int ItemStatOld = GetItemStat.count(IID) ? GetItemStat.find(IID)->second : 0;
			itemStat.Leave();

			if (ItemStatOld)
				ItemStatDisable.insert(IID);

			if (PetLifeCheck.count(IID))
				ItemTimerDisable.insert(IID);
		}
	}

	return Check;
}

/*int __cdecl ShoutsMessage(char Type, const char* Format, char* Name, char * msg) {
	int MsgPacket = CObject::WriteExclusive(60, "ss", Name, msg);

	std::set<int> OPlayers(Players.toSet());

	for (auto x = OPlayers.begin(); x != OPlayers.end(); x++)
	{
		IChar IPlayer((void*)*x);

		if (IPlayer.IsOnline())
			CPlayer::Send((int)IPlayer.GetOffset(), MsgPacket);
	}

	return CIOBuffer::Release((void*)MsgPacket);
}*/

void __cdecl SkillLearnFix(int Player, unsigned char Type, char* format, int SkillID, int Grade)
{
	if (SkillID == 95)
		SkillID = 88;

	CPlayer::Write((void*)Player, Type, format, SkillID, Grade);
}

int __fastcall ArtilleryFix(void* pSkill, void* edx, int SkillID) {
	IChar IPlayer((void*)*(DWORD*)pSkill);

	if (IPlayer.GetClass() == 3) {
		if (IPlayer.IsBuff(BuffNames::Artillery))
			return 1;

		return 0;
	}

	if (IPlayer.GetClass() == 4)
		return (CSkill::IsSkill(pSkill, 34) || CSkill::IsSkill(pSkill, 42) || CSkill::IsSkill(pSkill, SkillID));
	
	return CSkill::IsSkill(pSkill, SkillID);
}

void __cdecl NameChangeRealTime(int Player, unsigned char Type, char* format, char type, char changed, const char* name)
{
	IChar IPlayer((void*)Player);
	IPlayer.CloseWindow("changename_msg");

	std::string Name(name);
	IPlayer.BoxMsg("Your new name is now: " + Name +".");

	int a4a = Player;
	
	CChar::Lock((void*)Player);
	int Packet = SendExclusiveCreate(50, "", *(DWORD *)(a4a + 28), Name.c_str(), *(DWORD *)(a4a + 460), *(DWORD *)(a4a + 332), *(DWORD *)(a4a + 336), *(DWORD *)(a4a + 340), *(DWORD *)(a4a + 348), *(DWORD *)(a4a + 280), (unsigned char*)(a4a + 1052), 14, *(DWORD *)(a4a + 556), *(DWORD *)(a4a + 560), *(DWORD *)(a4a + 288), a4a, (char*)CPlayer::GetGuildName(a4a), *(DWORD *)(a4a + 480), *(DWORD *)(a4a + 1112), *(DWORD *)(a4a + 512));
	CPlayer::Send(Player, Packet);
	CSellMap::SendCreate(*(char **)(a4a + 320), a4a, a4a + 324, Packet);
	CIOBuffer::Release((void*)Packet);
	CChar::Unlock((void*)Player);

	CPlayer::Write((void*)Player, 0xFE, "ds", 175, name);
	CPlayer::LeaveParty(Player);
}

void ExpMultiplier()
{
	Interface<IMemory> Memory;
	Interface<ITools> Tools;
	ChannelSystem();

	int SiegeGunDissambleCancel = 126;
	int SiegeGunAssembleCancel = 116;

	int AuthRefresh = 1000;

	int StatusHeight = 50;
	int PlayerSize = PlayerProperty::MaxSize; //Original: 1680 (0x690u)

	int EggGradeLimit = 100;
	int ItemTimer = 1000;
	int SocketTime = 327675;
	int GCoinTime = GoldenCoinT * 1000;
	int DMGLevelCheck = 24;
	signed int ResetLevelMax = 127;

	/*
	std::vector<TeleCoordinates> Tele_Scrolls = CreateTeleScrolls();
	const uintptr_t* p_tele = reinterpret_cast<const uintptr_t*>(Tele_Scrolls.data());
	Memory->Set(reinterpret_cast<void*>(0x0041FD2B), reinterpret_cast<const char*>(&p_tele), 4);
	*/
	// Teleport Scrolls
	//Memory->Hook(0x460BCF, ShoutsMessage);

	Memory->Hook(0x44A654, ArtilleryFix);
	Memory->Hook(0x44A668, ArtilleryFix);
	Memory->Hook(0x44AA04, ArtilleryFix);
	Memory->Hook(0x44AA18, ArtilleryFix);
	Memory->Hook(0x46DA01, ArtilleryFix);
	Memory->Hook(0x46DA15, ArtilleryFix);

	Memory->Hook(0x47F8D5, SkillLearnFix);

	Memory->Hook(0x45EE34, StorageItemCheck);
	Memory->Hook(0x45F188, StorageItemCheck);
	Memory->Hook(0x45E5B6, StorageItemCheck);

	/*if (ManaCostActive) {
		Memory->Hook(0x480EDE, ManaCostCheck, 0xe8, 6);
		Memory->Hook(0x4825CE, ManaCostCheck, 0xe8, 6);
		Memory->Hook(0x485B3E, ManaCostCheck, 0xe8, 6);
		Memory->Hook(0x4868BE, ManaCostCheck, 0xe8, 6);
		Memory->Hook(0x486E99, ManaCostCheck, 0xe8, 6);
		Memory->Hook(0x487966, ManaCostCheck, 0xe8, 6);
		Memory->Hook(0x487BA2, ManaCostCheck, 0xe8, 6);
		Memory->Hook(0x487D56, ManaCostCheck, 0xe8, 6);
		Memory->Hook(0x489590, ManaCostCheck, 0xe8, 6);
		Memory->Hook(0x489607, ManaCostCheck, 0xe8, 6);
		Memory->Hook(0x489A6E, ManaCostCheck, 0xe8, 6);
		Memory->Hook(0x48A59E, ManaCostCheck, 0xe8, 6);
	}
	*/

	Memory->Copy((void*)0x00495D4B, &PlayerSize, 4);
	Memory->Copy((void*)0x004014B9, &AuthRefresh, 4);
	Memory->Copy((void*)0x0043464A, &StatusHeight, 1);

	Memory->Copy((void*)0x0044AB95, &SiegeGunDissambleCancel, 1);
	Memory->Copy((void*)0x00449F28, &SiegeGunAssembleCancel, 1);
	Memory->Copy((void*)0x0044A918, &SiegeGunAssembleCancel, 1);
	
	if (AllyMemberFull > 8)
		AllyMemberFull = 8;

	if (MemberFull1 < 6)
		MemberFull1 = 6;
	
	Memory->Hook(0x0046D0E7, NameChangeRealTime);

	Memory->Hook(0x00432AB0, AuthDefaultPort);
	Memory->Hook(0x00401258, AuthSvrFix);
	Memory->Hook(0x004014AE, AuthSvrFix);
	Memory->Hook(0x0045CD44, LawlessPortCheck);

	Memory->Hook(0x0044A2F5, SiegeGunStoneStateFix);
	Memory->Hook(0x00444CC8, SiegeGunStateFix);
	Memory->Hook(0x0044A428, SiegeGunStateFix);
	Memory->Hook(0x0046DEA8, SiegeGunStateFix);

	//Memory->Hook(0x0046D928, WarCannonFix);
	Memory->Hook(0x0046E0BD, ReturnToVillage);
	Memory->Hook(0x00464742, ReturnToVillage);

	//CW show fix
	Memory->Hook(0x41287F, SendTileChange);
	Memory->Hook(0x414D4E, SendTileChange);
	Memory->Hook(0x413FAF, SendTileChange);
	Memory->Hook(0x41422C, SendTileChange);
	Memory->Hook(0x4147C2, SendTileChange);
	Memory->Hook(0x414A6A, SendTileChange);
	Memory->Hook(0x4168E4, SendTileChange);

	Memory->Hook(0x45FB3B, LawlessParty);
	Memory->Hook(0x45FB95, LawlessParty);

	Memory->Hook(0x004582C6, IDFixCreate);
	Memory->Hook(0x00451415, IDFixCreate);
	Memory->Hook(0x0045838A, IDFixCreate);
	Memory->Hook(0x0045D000, IDFixCreate);
	Memory->Hook(0x00491862, IDFixCreate);

	Memory->Hook(0x00458358, PlayerSendCreate);
	Memory->Hook(0x004514a1, PlayerSendCreate);
	Memory->Hook(0x00458412, SendExclusiveCreate);
	Memory->Set(0x0045840b, "\xff\x75\xf8\x90\x90", 5);
	Memory->Hook(0x0045d088, SendExclusiveCreate);
	Memory->Set(0x0045d081, "\xff\x75\xf4\x90\x90", 5);
	Memory->Hook(0x004918eb, SendExclusiveCreate);
	Memory->Set(0x004918e4, "\xff\x75\x08\x90\x90", 5);

	Memory->Copy((void*)0x0045CA7D, &iceStoneValue, 1);

	Memory->Copy((void*)0x00463497, &ResetLevelMax, 1);
	Memory->Copy((void*)0x00463360, &ResetLevelMax, 1);
	Memory->Hook(0x43EB9B, MobLevelEggFix);
	Memory->Hook(0x43EC8A, MobLevelEggFix);
	Memory->Hook(0x44F01F, MobLevelEggFix);

	Memory->Hook(0x46BC4C, StandardBuff);
	Memory->Hook(0x4939A6, PickCrashFix);

	Memory->Hook(0x460386, AskPvP);
	Memory->Hook(0x460546, OnAskPvP);
	Memory->Hook(0x4603E5, AskPvP);
	Memory->Hook(0x4605A5, OnAskPvP);

	Memory->Hook(0x45FBD2, AskParty);
	Memory->Hook(0x45FC7C, OnAskParty);

	Memory->Hook(0x44F340, CallsRange, 0xe8, 5);
	Memory->Copy((void*)0x00452B9E, &GCoinTime, 4);
	Memory->Copy((void*)0x00450383, &GCoinTime, 4);
	Memory->Copy((void*)0x00452BB2, &GoldenCoinI, 4);
	Memory->Copy((void*)0x00452BAE, &GoldenCoinA, 1);

	Memory->Hook(0x4877AE, DebuffMonster, 0xe8, 6);
	Memory->Hook(0x4886FF, DebuffMonster, 0xe8, 6);
	Memory->Hook(0x48BF8C, DebuffMonster, 0xe8, 6);
	Memory->Hook(0x482F23, DebuffMonster, 0xe8, 6);

	Memory->Copy((void*)0x004944FF, &SocketTime, 4);
	Memory->Hook(0x0049596F, Login);
	Memory->Hook(0x004958B0, LoginAttemptsLimit);
	Memory->Hook(0x00487536, KnightBlabla);

	//Memory->Hook(0x00494536, CIOSocaketClose);
	int MaxDayAlly = (MaxTimeAlly * 86400) + 60;

	Memory->Hook(0x0046C8EC, MovingScrollFix);
	Memory->Hook(0x0046B664, BuffTimer);

	/*Memory->Hook(0x4877AE, DebuffMonster, 0xe8, 6);
	Memory->Hook(0x4886FF, DebuffMonster, 0xe8, 6);
	Memory->Hook(0x48BF8C, DebuffMonster, 0xe8, 6);*/

	Memory->Hook(0x435248, ServerStartedMessage);
	Memory->Hook(0x4962AE, ServerStatus);
	Memory->Hook(0x00493962, PetPickRange, 0xe8, 5);

	Memory->Copy((void*)0x00465A2B, &MLMStudentLevel, 1);
	Memory->Copy((void*)0x00465AF0, &MLMTeacherLevel, 1);
	Memory->Copy((void*)0x00465AFD, &MLMMax, 1);
	Memory->Copy((void*)0x00465AFD, &MLMMax, 1);
	Memory->Copy((void*)0x0046620C, &MLMLevel1Reward, 1);
	Memory->Hook(0x0046723F, MLMRewardMoney);
	Memory->Hook(0x004672EE, MLMCreateMoney);

	Memory->Hook(0x00412B0B, GuildCreationCheck);
	Memory->Copy((void*)0x0041719C, &MaxDayAlly, 4);
	Memory->Copy((void*)0x004120C5, &GuildEXPGrade4, 4);
	Memory->Copy((void*)0x00415775, &GuildEXPGrade4, 4);
	Memory->Copy((void*)0x004157A4, &GuildEXPGrade4, 4);
	Memory->Copy((void*)0x004157B1, &GuildEXPGrade4, 4);
	Memory->Copy((void*)0x004157C3, &GuildEXPGrade4, 4);
	Memory->Copy((void*)0x004158BF, &GuildEXPGrade4, 4);
	Memory->Copy((void*)0x00416B2F, &GuildEXPGrade4, 4);
	Memory->Copy((void*)0x004120DD, &GuildEXPGrade3, 4);
	Memory->Copy((void*)0x00416B44, &GuildEXPGrade3, 4);
	Memory->Copy((void*)0x004120F5, &GuildEXPGrade2, 4);
	Memory->Copy((void*)0x00416B59, &GuildEXPGrade2, 4);
	Memory->Copy((void*)0x00415FB7, &MemberFull1, 1);
	Memory->Copy((void*)0x00415FC2, &MemberFull2, 1);
	Memory->Copy((void*)0x00415FCD, &MemberFull3, 1);
	Memory->Copy((void*)0x00415FD8, &MemberFull4, 1);
	Memory->Copy((void*)0x00413E25, &TempMemberFull, 1);
	Memory->Copy((void*)0x00416E67, &AllyMemberFull, 1);
	Memory->Copy((void*)0x00417113, &AllyMemberFull, 1);
	
	Memory->Copy((void*)0x0042670F, &ItemTimer, 4);
	Memory->Copy((void*)0x0042F212, &EggGradeLimit, 1);

	//Memory->Hook(0x452BD0, GoldenCoin);

	/*Memory->Hook(0x48A938, EmergencyEscape);
	Memory->Hook(0x48A96E, EmergencyEscape);
	*/
	//Memory->Hook(0x48ADB8, CallOfPhy);

	Memory->Hook(0x4677F2, FriendCheck);

	Memory->Hook(0x45FFF0, QuestFix);
	Memory->Hook(0x4600B0, QuestFix);

	Memory->Hook(0x42D127, SendShopMsg);
	Memory->Hook(0x427056, SendShopMsg);
	Memory->Hook(0x42D09B, SendShopMsg2);
	//NORMAL DMG
	Memory->Hook(0x440D62, AttackMsg);
	Memory->Hook(0x43D847, AttackMsg);
	Memory->Hook(0x44004B, AttackMsg);
	Memory->Hook(0x45CBDA, AttackMsg);

	//SKILL SHOW FIX
	Memory->Hook(0x4076F3, PlayerSkillMSG);
	Memory->Hook(0x4079D3, PlayerSkillMSG);
	Memory->Hook(0x4082BB, PlayerSkillMSG);
	Memory->Hook(0x408608, PlayerSkillMSG);
	Memory->Hook(0x44F279, SkillMSG);
	Memory->Hook(0x481DD4, SkillMSG);
	Memory->Hook(0x4843BA, SkillMSG);
	Memory->Hook(0x48467D, SkillMSG);
	Memory->Hook(0x484939, SkillMSG);
	Memory->Hook(0x484B71, SkillMSG);
	Memory->Hook(0x484E69, SkillMSG);
	Memory->Hook(0x487320, SkillMSG);
	Memory->Hook(0x48B7DC, SkillMSG);
	Memory->Hook(0x48B95C, SkillMSG);
	Memory->Hook(0x48BEAE, SkillMSG);
	Memory->Hook(0x48CCED, SkillMSG);
	Memory->Hook(0x48D0B1, SkillMSG);
	Memory->Hook(0x48D622, SkillMSG);

	//EB SHOW FIX
	Memory->Hook(0x481924, EBSkillMSG);
	Memory->Hook(0x4831C0, EBSkillMSG);
	Memory->Hook(0x487149, EBSkillMSG);
	Memory->Hook(0x487819, EBSkillMSG);
	Memory->Hook(0x48851D, EBSkillMSG);
	Memory->Hook(0x48876A, EBSkillMSG);
	Memory->Hook(0x488E25, EBSkillMSG);
	Memory->Hook(0x488FE3, EBSkillMSG);
	Memory->Hook(0x489C66, EBSkillMSG);
	Memory->Hook(0x48C299, EBSkillMSG);
	Memory->Hook(0x48C499, EBSkillMSG);
	Memory->Hook(0x48C799, EBSkillMSG);
	Memory->Hook(0x48CD61, EBSkillMSG);
	Memory->Hook(0x48D359, EBSkillMSG);

	Memory->Hook(0x409D5A, SendBState);
	Memory->Hook(0x451E5D, SendBState);
	Memory->Hook(0x451F31, SendBState2);
	Tools->FillMemoryEx(0x0040A978, ITools::_I_NOP, 5);
	Tools->FillMemoryEx(0x0045265A, ITools::_I_NOP, 5);
	Tools->FillMemoryEx(0x00494604, ITools::_I_NOP, 5);
	//Tools->FillMemoryEx(0x00438874, ITools::_I_NOP, 5);
	//Tools->FillMemoryEx(0x00414A19, ITools::_I_NOP, 5);
	Memory->Hook(0x00441286, WarSetup);
	//Tools->FillMemoryEx(0x00451C65, ITools::_I_NOP, 5);
	Tools->FillMemoryEx(0x0046D0B8, ITools::_I_NOP, 5);
	Memory->Hook(0x00452958,FishingItem);
	Memory->Hook(0x0042C7DD,MirrorFix);
	Memory->Hook(0x00427AAC, CustomWeapFix);
	Memory->Hook(0x0042A80E, ArmorRiding);
	Memory->Hook(0x0042C0C6, SuitsFix);
	Memory->Hook(0x0042BFF8, SuitsFix);
	Memory->Hook(0x0042C1CF,SuitsFix1);
	Memory->Hook(0x0042AC8D, ShortsFix);
	Memory->Hook(0x004281AC, CustomWeaponsFix);
	Memory->Hook(0x0042C4BE,MirrorFixa, 0xe8, 5);
	Memory->Hook(0x0042BEB7,SuitsFixe, 0xe8, 5);
	Memory->Hook(0x00455FC9,MyInventoryCheck);
	Memory->Hook(0x004560DA,MyInventoryCheck);
	Memory->Hook(0x0045DE7D,MyInventoryCheck);
	Memory->Hook(0x0045E4CC,MyInventoryCheck);
	Memory->Hook(0x0045EEFE,MyInventoryCheck);
	Memory->Hook(0x0045F6CB,MyInventoryCheck);
	Memory->Hook(0x00464FD3,MyInventoryCheck);
	Memory->Hook(0x00469752,MyInventoryCheck);
	Memory->Hook(0x0043D0A5, IsNormal, 0xe8, 5);
	Memory->Hook(0x0043E95C, IsNormal, 0xe8, 5);
	Memory->Hook(0x0043F525, IsNormal, 0xe8, 5);
	Memory->Hook(0x0043F925, IsNormal, 0xe8, 5);
	Memory->Hook(0x00440599, IsNormal, 0xe8, 5);
	Memory->Hook(0x0044109D, IsNormal, 0xe8, 5);
	Memory->Hook(0x00441B5B, IsNormal, 0xe8, 5);
	Memory->Hook(0x00442774, IsNormal, 0xe8, 5);
	Memory->Hook(0x00444A59, IsNormal, 0xe8, 5);
	Memory->Hook(0x004453F9, IsNormal, 0xe8, 5);
	Memory->Hook(0x00445839, IsNormal, 0xe8, 5);
	Memory->Hook(0x00490C78, IsNormal, 0xe8, 5);
	Memory->Hook(0x00457127, IsStateCheck, 0xe8, 5);
	Memory->Hook(0x004923DF, OpenPortalFix, 0xe8, 5);
	Memory->Set(0x004B92E0, "ddddb", 6);
	Memory->Hook(0x00458965,MyStatStr);
	Memory->Hook(0x00459A8E,MyStatStr);
	Memory->Hook(0x0045B361,MyStatStr);
	Memory->Hook(0x00458AA7,MyStatHth);
	Memory->Hook(0x00459CA8,MyStatHth);
	Memory->Hook(0x0045B587,MyStatHth);
	Memory->Hook(0x00458C81,MyStatInt);
	Memory->Hook(0x00459FDF,MyStatInt);
	Memory->Hook(0x0045B8CA,MyStatInt);
	Memory->Hook(0x00458E05,MyStatWis);
	Memory->Hook(0x0045A301,MyStatWis);
	Memory->Hook(0x0045BBf8,MyStatWis);
	Memory->Hook(0x00458F6E,MyStatAgi);
	Memory->Hook(0x0045A56F,MyStatAgi);
	Memory->Hook(0x0045BE72,MyStatAgi);
	Memory->Hook(0x0045903B,MyStatCurHp1);
	Memory->Hook(0x00459556,MyStatCurHp);
	Memory->Hook(0x0045A61C,MyStatCurHp);
	Memory->Hook(0x0045BF2B, MyStatCurHp);

	//Memory->Hook(0x00459311, MyStatEXP);
	//Memory->Hook(0x004593D7, MyStatEXP1);
	//Memory->Hook(0x004917A0, MyForPortalCheck, 0xe8, 5);
	Memory->Hook(0x0045DD79, RidingFix, 0xe8, 5);
	//Tools->FillMemoryEx(0x0046BC20, ITools::_I_NOP, 5);
}