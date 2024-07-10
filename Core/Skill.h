int __fastcall PrepSkill(void* pSkill, void* _edx, signed int SkillID, int nTargetID)
{
	ISkill Skill(pSkill);
	IChar IPlayer(Skill.GetPlayer());

	if (CheckCooldownConfig.count(SkillID + (IPlayer.GetClass() * 100)))
	{
		IPlayer.UpdateBuff(BuffNames::SkillPrepTime, BuffNames::BuffTime, GetTickCount() + CheckCooldownConfig.find((SkillID + (IPlayer.GetClass() * 100)))->second.DelayConfig);
		IPlayer.UpdateBuff(BuffNames::SkillPrepID, BuffNames::BuffTime, SkillID);
	}
	int sekey = SkillID + (IPlayer.GetClass() * 100);

	if (Cooldowns.count(sekey)) {
		int Compare3 = Cooldowns[sekey].compare3;
		IPlayer.UpdateBuff(BuffNames::DelayProtect + SkillID, BuffNames::BuffTime, (GetTickCount() + Compare3) - 350);
	}

	return CSkill::PrepareSkill(pSkill, SkillID, nTargetID);
}

int __fastcall LoadInitSkill(int pSkill, void* edx)
{
	int Class = *(DWORD *)(pSkill + 32);
	if (Class > 2) {
		CConsole::Red("%d", *(DWORD *)(pSkill + 32));
		*(DWORD *)(pSkill + 32) = 2;
	}

	return CSkill::LoadInitSkill(pSkill);
}

void __fastcall ExecuteSkill(void *pSkill, void* edx, signed int SkillID, int pPacket, int pPos)
{
	if (SkillID > 100)
		return;

	if (SkillID == 88) SkillID = 95;

	ISkill Skill(pSkill);
	IChar IPlayer(Skill.GetPlayer());
	int SkillPointerCheck = IPlayer.GetSkillPointer(SkillID);
	DWORD CdTime = 0, CooldownCheck = 0, DelayTime = 0;

	if (!IPlayer.GetAdmin() && IPlayer.GetClass() == 2 && SkillID == 31)
		IPlayer.CheckSpeed(maxAllowedSpeed + 200);

	IPlayer.Buff(313, 3, 0);

	if (skillDebug == 1 || skillDebug == 3) {
		std::string Datoe = "./Debugger/Skill/SKILL_" + Time::GetDay() + "_" + Time::GetMonth() + "_" + Time::GetYear() + "_" + Time::GetHour() + "." + Time::GetMinute() + ".txt";
		std::fstream CHLOG;
		CHLOG.open(Datoe, std::fstream::in | std::fstream::out | std::fstream::app);
		CHLOG << Time::GetTime() << " " << IPlayer.GetName() << ": " << SkillID << std::endl;
		CHLOG.close();
	}

	if (Restri && Restrictions.count(IPlayer.GetPID()) && Restrictions.find(IPlayer.GetPID())->second.Attack != 0 && Restrictions.find(IPlayer.GetPID())->second.Skill == 0) {
		IPlayer.SystemMessage("You are not allowed to be using this system.", TEXTCOLOR_RED);
		return;
	}

	if (IPlayer.IsValid() && IPlayer.isInTrainingMap()) {
		IPlayer.SystemMessage("Skills execution is disabled in training map.", TEXTCOLOR_RED);
		return;
	}

	int sekey = SkillID + (IPlayer.GetClass() * 100);

	if (Cooldowns.count(sekey)) {
		int Compare4 = Cooldowns[sekey].compare4;
		int Compare3 = Cooldowns[sekey].compare3;
		int nextExecutionTime = IPlayer.GetBuffValue(BuffNames::CDProtect + SkillID);
		int nextPrepareTime = IPlayer.GetBuffValue(BuffNames::DelayProtect + SkillID);

		if (!IPlayer.IsBuff(329)){
			if ((Compare3 > 100) && GetTickCount() < nextExecutionTime + (Compare3 - 100)) {
				IPlayer.SystemMessage("invalid skill cooldown time..", TEXTCOLOR_RED);
				return;
			}

			if (GetTickCount() < nextExecutionTime) {
				IPlayer.SystemMessage("invalid skill cooldown time.", TEXTCOLOR_RED);
				return;

			}
			else if (GetTickCount() < nextPrepareTime) {
				IPlayer.SystemMessage("invalid skill casting time.", TEXTCOLOR_RED);
				return;

			}
		}
		IPlayer.UpdateBuff(BuffNames::CDProtect + SkillID, BuffNames::BuffTime, (GetTickCount() + Compare4) - My_CDValue);
	}

	if (IPlayer.IsValid() && IPlayer.IsBuff(349))
	{
		if (!(isBattleRiding(IPlayer.GetBuffValue(349) + 7856) && !RidingDisableSkill.count((IPlayer.GetClass() * 1000) + SkillID))) {

			IPlayer.DisableRiding();
			IPlayer.SystemMessage("Skills execution is disabled in riding.", TEXTCOLOR_RED);
			return;
		}
	}

	if (!SkillPointerCheck) {
		IPlayer.SystemMessage("Skill does not exist.", TEXTCOLOR_RED);
		return;
	}

	if (DisableSkill.count((IPlayer.GetClass() * 1000) + SkillID) && (DisableSkill.find((IPlayer.GetClass() * 1000) + SkillID)->second.count(IPlayer.GetMap()) || DisableSkill.find((IPlayer.GetClass() * 1000) + SkillID)->second.count(255))) {
		IPlayer.SystemMessage("This Skill is temporarly disabled here.", TEXTCOLOR_RED);
		return;
	}

	int MapX = IPlayer.GetX() >> 13;
	int MapY = IPlayer.GetY() >> 13;

	if (IPlayer.IsOnline() && MapX == 29 && MapY == 42) {
		IPlayer.SystemMessage("Skills can not be used inside guild raid map.", TEXTCOLOR_RED);
		return;
	}

	if (DisableSkillFile.count((IPlayer.GetClass() * 1000) + SkillID) && DisableSkillFile.find((IPlayer.GetClass() * 1000) + SkillID)->second.count((MapX * 1000) + MapY)) {
		IPlayer.SystemMessage("This Skill is temporarly disabled here.", TEXTCOLOR_RED);
		return;
	}

	if (CheckCooldownConfig.count(SkillID + (IPlayer.GetClass() * 100))) {
		if (CheckCooldownConfig.find(SkillID + (IPlayer.GetClass() * 100))->second.DelayConfig) {
			if (IPlayer.GetBuffValue(BuffNames::SkillPrepID) != SkillID || IPlayer.GetBuffValue(BuffNames::SkillPrepTime) >= GetTickCount()) {
				IPlayer.SystemMessage("Invalid skill cast time.", TEXTCOLOR_RED);
				return;
			}
		}

		CdTime = CheckCooldownConfig.find(SkillID + (IPlayer.GetClass() * 100))->second.CooldownConfig;
	}


	if (IPlayer.IsValid()) {

		int nTargetID = 0;
		char bType = 0;
		void *pTarget = 0;
		CPacket::Read((char*)pPacket, (char*)pPos, "bd", &bType, &nTargetID);

		TargetFind myTarget(bType, 0, nTargetID);
		pTarget = myTarget.getTarget();
		IChar Target(pTarget);

		if (Target.GetOffset() && Target.IsValid()){
			if (!CheckRangeProtection((int)IPlayer.GetOffset(), SkillID, (int)Target.GetOffset(), pPacket, pPos))
			{
				IPlayer.SystemMessage("Invalid range detected.", TEXTCOLOR_RED);

				if (rangeDebug == 1) {
					std::string Datoe = "./Debugger/SkillRange/SKILL_" + Time::GetDay() + "_" + Time::GetMonth() + "_" + Time::GetYear() + "_" + Time::GetHour() + ".txt";
					std::fstream CHLOG;
					CHLOG.open(Datoe, std::fstream::in | std::fstream::out | std::fstream::app);
					CHLOG << Time::GetTime() << " Player: " << IPlayer.GetName() << ", SkillID: " << SkillID << ", Class: " << IPlayer.GetClass() << std::endl;
					CHLOG.close();
				}

				if (RangeKick)
					IPlayer.Kick();

				return;
			}
		}
	}


	// Cure 3 // Cure 2
	if (IPlayer.GetClass() == 1 && HealScale && (SkillID == 35 || SkillID == 22))
	{
		int nTargetID = 0; char bType = 0; void *pTarget = 0;
		CPacket::Read((char*)pPacket, (char*)pPos, "bd", &bType, &nTargetID);

		TargetFind myTarget(bType, 0, nTargetID);
		pTarget = myTarget.getTarget();

		if (pTarget) {
			IChar ITarget(pTarget);

			int HealAmount = 0;
			int PlayerWisdom = CChar::GetWis((int)IPlayer.GetOffset());

			if (ITarget.IsValid() && PlayerWisdom)
			{
				ITarget.IncreaseHp(PlayerWisdom * 3);
			}
		}
	}

	// Group Cure 2
	if (IPlayer.GetClass() == 1 && HealScale && SkillID == 57)
	{
		int PlayerWisdom = CChar::GetWis((int)IPlayer.GetOffset());

		if (IPlayer.IsParty()) {
			void *Party = (void*)CParty::FindParty(IPlayer.GetPartyID());

			if (Party)
			{
				for (int i = CParty::GetPlayerList(Party); i; i = CBaseList::Pop((void*)i))
				{
					int Members = *(DWORD*)((void*)i);
					IChar IBuffed((void*)Members);

					IBuffed.IncreaseHp(PlayerWisdom * 3);
				}
				CIOObject::Release(Party);
			}
		}
		else
			IPlayer.IncreaseHp(PlayerWisdom * 3);
	}

	if (IPlayer.IsValid() && !CChar::IsGState((int)IPlayer.GetOffset(), 512))
	{
		if (IPlayer.GetClass() == 1 && SkillID == 48 && FireStormVThief)
		{
			int Around = IPlayer.GetObjectListAround(30);
			while (Around)
			{
				IChar Object((void*)CBaseList::Offset((void*)Around));

				if (Object.IsValid() && Object.GetOffset() != IPlayer.GetOffset()) {

					if (Object.GetClass() == 3 && Object.GetType() == 0 && Object.IsBuff(329)) {
						IPlayer.CancelBuff(329);
						IPlayer.CancelBuff(40);
					}
				}
				Around = CBaseList::Pop((void*)Around);
			}
		}

		if (IPlayer.GetClass() == 1 && IPlayer.GetMap() == 21 && (SkillID == 43 || SkillID == 45 || SkillID == 48)) {
			IPlayer.SystemMessage("Storms execution is disabled in F10.", TEXTCOLOR_RED);
			return;
		}

		if (DelaySpam > 0 && DisableSkill.count((IPlayer.GetClass() * 1000) + SkillID) && DisableSkill.find((IPlayer.GetClass() * 1000) + SkillID)->second.count(254)) {
			if (IPlayer.GetBuffValue(BuffNames::SpamSkillID) != SkillID && IPlayer.GetBuffValue(BuffNames::SpamSkillTime) >= GetTickCount()) {
				IPlayer.SystemMessage("You need to wait " + Int2String(ceil(DelaySpam)) + " seconds between the execution of different skills.", TEXTCOLOR_INFOMSG);
				return;
			}
			else {
				IPlayer.UpdateBuff(BuffNames::SpamSkillTime, BuffNames::BuffTime, GetTickCount() + (DelaySpam * 1000));
				IPlayer.UpdateBuff(BuffNames::SpamSkillID, BuffNames::BuffTime, SkillID);
			}
		}

		if (SkillID == 0)
		{
			IPlayer.SystemMessage("Run skill is disabled.", TEXTCOLOR_YELLOW);
			return;
		}

		if (SkillID == 0 && IPlayer.IsBuff(385))
			return;

		if (SkillID == 6 && IPlayer.IsBuff(329))
		{
			IPlayer.CancelBuff(329);
			IPlayer.CancelBuff(40);
			return;
		}

		//CDLock.Enter();
		//if (CooldownTable.count(IPlayer.GetPID()+4000000000+(SkillID*1000000)))
		//	CooldownCheck = CooldownTable.find(IPlayer.GetPID()+4000000000+(SkillID*1000000))->second;
		//CDLock.Leave();

		if (IPlayer.GetClass() == 1 && SkillID == 74) {
			CdTime = 450;
			DelayTime = 0;
		}

		if (CdTime || DelayTime)
			CooldownCheck = IPlayer.GetBuffValue(5200 + SkillID);

		if (CooldownCheck > GetTickCount())
		{
			IPlayer.SystemMessage("Invalid skill time detected!", TEXTCOLOR_RED);
			return;
		}
		else if (CdTime || DelayTime)
			IPlayer.UpdateBuff(5200 + SkillID, BuffNames::BuffTime, GetTickCount() + CdTime + DelayTime);

		if (IPlayer.GetClass() == 1 && IPlayer.GetSpecialty() == 23)
			IPlayer.UpdateBuff(BuffNames::MageMICheck, BuffNames::BuffTime, SkillID);

		if (SkillID != 0 && IPlayer.IsBuff(329))
		{
			IPlayer.CancelBuff(329);
			IPlayer.CancelBuff(40);

			if (SkillID != 7 && SkillID != 8 && SkillID != 10 && SkillID != 33) {
				IPlayer.SystemMessage("Skill has been avoided.", TEXTCOLOR_RED);
				return;
			}
		}

		if (IPlayer.GetProperty(PlayerProperty::ContinueSkillPlayerSkillID))
			ResetContinueSkill(IPlayer);

		if (IPlayer.GetClass() == 0 && SkillID == 10) {
			int pSkill = IPlayer.GetSkillPointer(10);

			if (pSkill)
			{
				ISkill xSkill((void*)pSkill);
				IPlayer.Buff(9, 900, 3 * xSkill.GetGrade());
			}
		}

		if (SkillsPVP.count((IPlayer.GetClass() * 100) + SkillID))
			IPlayer.UpdateBuff(3780, BuffNames::BuffTime, SkillID);

		bool SDamaged = false;

		int Key = (IPlayer.GetClass() * 1000) + SkillID;

		if (SkillsDamage.count(Key) || SkillsDamage.count(Key + 100) || SkillsDamage.count(Key + 200)) {
			IPlayer.SetProperty(PlayerProperty::SkillsEdit, SkillID);
			SDamaged = true;
		}

		if (IPlayer.GetClass() == 0 && SkillID == 38 && IPlayer.GetSpecialty() == 23)
		{
			SpinSlash(IPlayer);
			goto LABEL_1;
		}

		if (IPlayer.GetClass() == 0 && SkillID == 40 && IPlayer.GetSpecialty() == 43)
		{
			PerfectDefense(IPlayer);
			goto LABEL_1;
		}

		if (IPlayer.GetClass() == 0 && SkillID == 41 && (IPlayer.GetSpecialty() == 11 || IPlayer.GetSpecialty() == 43))
		{
			PowerfulWideningWound(IPlayer, pPacket, pPos);
			goto LABEL_1;
		}

		if (IPlayer.GetClass() == 0 && SkillID == 42 && IPlayer.GetSpecialty() == 43)
		{
			ProvocationOfBlow(IPlayer, pPacket, pPos);
			goto LABEL_1;
		}

		if (IPlayer.GetClass() == 0 && SkillID == 43 && IPlayer.GetSpecialty() == 23)
		{
			SwordDance(IPlayer, pPacket, pPos);
			goto LABEL_1;
		}

		if (IPlayer.GetClass() == 0 && IPlayer.GetLevel() >= 81 && SkillID == 90 && IPlayer.GetSpecialty() == 23)
		{
			ShoutOfDefense(IPlayer);
			goto LABEL_1;
		}

		if (IPlayer.GetClass() == 0 && IPlayer.GetLevel() >= 81 && SkillID == 91 && IPlayer.GetSpecialty() == 43)
		{
			TheBoomOfEarth(IPlayer);
			goto LABEL_1;
		}

		if (IPlayer.GetClass() == 0 && IPlayer.GetLevel() >= 81 && SkillID == 92 && IPlayer.GetSpecialty() == 23)
		{
			ShoutOfFightingSpirit(IPlayer);
			goto LABEL_1;
		}

		if (IPlayer.GetClass() == 0 && IPlayer.GetLevel() >= 81 && SkillID == 93 && IPlayer.GetSpecialty() == 43)
		{
			TheWaveOfEarth(IPlayer);
			goto LABEL_1;
		}

		if (IPlayer.GetClass() == 2 && IPlayer.GetLevel() >= 81 && SkillID == 90 && IPlayer.GetSpecialty() == 23)
		{
			OneHitStrike(IPlayer, pPacket, pPos);
			goto LABEL_1;
		}

		if (IPlayer.GetClass() == 2 && IPlayer.GetLevel() >= 81 && SkillID == 92 && IPlayer.GetSpecialty() == 23)
		{
			ArrowsOfTheMaster(IPlayer, pPacket, pPos);
			goto LABEL_1;
		}

		if (IPlayer.GetClass() == 2 && IPlayer.GetLevel() >= 81 && SkillID == 91 && IPlayer.GetSpecialty() == 43)
		{
			MassiveFire(IPlayer, pPacket, pPos);
			goto LABEL_1;
		}

		if (IPlayer.GetClass() == 2 && IPlayer.GetLevel() >= 81 && SkillID == 93 && IPlayer.GetSpecialty() == 43)
		{
			SpiritOfTheArrows(IPlayer, pPacket, pPos);
			goto LABEL_1;
		}

		if (IPlayer.GetLevel() >= 81 && SkillID == 95 && IPlayer.GetSpecialty() >= 23)
		{
			if (CChar::IsMState((int)IPlayer.GetOffset(), 1))
				CChar::SubMState(IPlayer.GetOffset(), 1, 0);

			WalkOnTheAir(IPlayer);
			goto LABEL_1;
		}

		if (IPlayer.GetClass() == 1 && IPlayer.IsBuff(287) && (SkillID == 17 || SkillID == 18 || SkillID == 19 || SkillID == 20 || SkillID == 21))
		{
			IPlayer.CouldntExecuteSkill();
			goto LABEL_1;
		}

		if (IPlayer.GetClass() == 1 && IPlayer.GetLevel() >= 81 && SkillID == 90 && IPlayer.GetSpecialty() == 23)
		{
			Punishment(IPlayer, pPacket, pPos);
			goto LABEL_1;
		}

		if (IPlayer.GetClass() == 1 && IPlayer.GetLevel() >= 81 && SkillID == 91 && IPlayer.GetSpecialty() == 43)
		{
			Incapacitation(IPlayer);
			goto LABEL_1;
		}

		if (IPlayer.GetClass() == 1 && IPlayer.GetLevel() >= 81 && SkillID == 92 && IPlayer.GetSpecialty() == 23)
		{
			ReleasingTheEnergy(IPlayer);
			goto LABEL_1;
		}

		if (IPlayer.GetClass() == 1 && IPlayer.GetLevel() >= 81 && SkillID == 93 && IPlayer.GetSpecialty() == 43)
		{
			Bombing(IPlayer);
			goto LABEL_1;
		}

		if (IPlayer.GetClass() == 1 && SkillID == 40)
		{
			SoulDestruction((void*)SkillPointerCheck, IPlayer.GetOffset(), pPacket, pPos);
			goto LABEL_1;
		}

		if (IPlayer.GetClass() == 1 && SkillID == 59)
		{
			int pSkill = IPlayer.GetSkillPointer(59);

			if (IPlayer.IsValid() && pSkill)
			{
				ISkill xSkill((void*)pSkill);
				int nTargetID = 0; char bType = 0; void *pTarget = 0;
				CPacket::Read((char*)pPacket, (char*)pPos, "bd", &bType, &nTargetID);

				TargetFind myTarget(bType, 0, nTargetID);
				pTarget = myTarget.getTarget();

				if (pTarget && IPlayer.IsValid())
				{
					IChar Target(pTarget);
					if (IPlayer.GetCurMp() < xSkill.DecreaseMana()) {
						goto LABEL_1;
					}

					if (IPlayer.IsValid() && Target.IsValid())
					{
						if (!IPlayer.IsInRange(Target, 300)) {

							goto LABEL_1;
						}
						IPlayer.DecreaseMana(xSkill.DecreaseMana());
						Target.IncreaseHp(Target.GetMaxHp());
						IPlayer._ShowBattleAnimation(Target, 55);
					}
				}

			}

			goto LABEL_1;
		}

		if (IPlayer.GetClass() == 1 && SkillID == 63)
		{
			int pSkill = IPlayer.GetSkillPointer(63);

			if (pSkill)
			{
				ISkill xSkill((void*)pSkill);

				if (IPlayer.IsBuff(286) || IPlayer.IsBuff(287))
					goto LABEL_1;

				if (IPlayer.GetCurMp() >= 102)
				{
					IPlayer.DecreaseMana(102);
					IPlayer.Buff(286, 900, 0);
					IPlayer.Buff(287, 905, 0);
					IPlayer.AddDef(100 * xSkill.GetGrade());
					IPlayer.AddAbsorb(5 * xSkill.GetGrade());
					IPlayer.SetBuffIcon(900000, 0, 1414, 147);
					IPlayer._ShowBattleAnimation(IPlayer, 63);
				}
			}

			goto LABEL_1;
		}

		if (IPlayer.GetClass() == 1 && SkillID == 64 && !IPlayer.IsBuff(305))
		{
			int pSkill = IPlayer.GetSkillPointer(64);
			int nMana = IPlayer.GetLevel() * 5;

			if (pSkill)
			{
				ISkill xSkill((void*)pSkill);

				if (IPlayer.GetCurMp() < nMana)
					goto LABEL_1;

				if (IPlayer.IsBuff(305) || IPlayer.IsBuff(306))
					goto LABEL_1;

				IPlayer.DecreaseMana(nMana);
				IPlayer.Buff(305, 20 + (xSkill.GetGrade() * 5), 0);
				IPlayer.Buff(306, 25 + (xSkill.GetGrade() * 5), 0);
				IPlayer.SetBuffIcon(20000 + (xSkill.GetGrade() * 5000), 0, 1794, 202);
				IPlayer._ShowBattleAnimation(IPlayer, 64);
			}

			goto LABEL_1;
		}

		if (IPlayer.GetClass() == 1 && SkillID == 65 && IPlayer.GetSpecialty() == 23)
		{
			FlameInjection(IPlayer, pPacket, pPos);
			goto LABEL_1;
		}

		if (IPlayer.GetClass() == 1 && SkillID == 66 && IPlayer.GetSpecialty() == 23)
		{
			Icicle(IPlayer);
			goto LABEL_1;
		}

		if (IPlayer.GetClass() == 1 && SkillID == 67 && IPlayer.GetSpecialty() == 23)
		{
			LightningArrow(IPlayer, pPacket, pPos);
			goto LABEL_1;
		}

		if (IPlayer.GetClass() == 1 && IPlayer.GetMap() != 21 && (SkillID == 4 || SkillID == 9 || SkillID == 23 || SkillID == 31 || SkillID == 42 || SkillID == 75))
			ActivateShiny(IPlayer, pPacket, pPos);

		if (IPlayer.GetClass() == 1 && SkillID == 69 && IPlayer.GetSpecialty() == 43)
		{
			Blessing(IPlayer, pPacket, pPos);
			goto LABEL_1;
		}

		if (IPlayer.GetClass() == 1 && SkillID == 77 && IPlayer.GetSpecialty() == 43)
		{
			GroupBlessing(IPlayer, pPacket, pPos);
			goto LABEL_1;
		}

		if (IPlayer.GetClass() == 1 && SkillID == 72 && IPlayer.GetSpecialty() == 43)
		{
			TherapeuticTouch(IPlayer, pPacket, pPos);
			goto LABEL_1;
		}

		if (IPlayer.GetClass() == 1 && SkillID == 73 && IPlayer.GetSpecialty() == 23)
		{
			Fireball(IPlayer, pPacket, pPos);
			goto LABEL_1;
		}

		if (IPlayer.GetClass() == 1 && SkillID == 74 && IPlayer.GetSpecialty() == 23)
		{
			IceArrow(IPlayer, pPacket, pPos);
			goto LABEL_1;
		}

		if (IPlayer.GetClass() == 1 && SkillID == 75 && IPlayer.GetSpecialty() == 23)
		{
			Thunderbolt(IPlayer, pPacket, pPos);
			goto LABEL_1;
		}

		if (IPlayer.GetClass() == 1 && SkillID == 76 && (IPlayer.GetSpecialty() == 11 || IPlayer.GetSpecialty() == 43) && !IPlayer.IsBuff(309))
		{
			int pSkill = IPlayer.GetSkillPointer(76);

			if (pSkill)
			{
				ISkill xSkill((void*)pSkill);
				int nMana = (xSkill.GetGrade() * 10) + 590;

				if (IPlayer.GetCurMp() < nMana)
					goto LABEL_1;

				IPlayer.DecreaseMana(nMana);
				IPlayer.Buff(309, (15 + (xSkill.GetGrade() * 5)), 0);
				IPlayer.Buff(310, (20 + (xSkill.GetGrade() * 5)), 0);
				IPlayer.SetBuffIcon((15 + (xSkill.GetGrade() * 5)) * 1000, 0, 2356, 298);
				IPlayer._ShowBattleAnimation(IPlayer, 76);
			}

			goto LABEL_1;
		}

		if (IPlayer.GetClass() == 2 && SkillID == 46 && IPlayer.GetSpecialty() == 23 && !IPlayer.IsBuff(289))
		{
			int pSkill = *((DWORD*)((int)IPlayer.GetOffset() + 624) + 46 + 2);
			IPlayer.SetBuffIcon(30000, 0, 2101, 227);
			IPlayer.Buff(40, 30, 90);
			IPlayer.RemoveBuffIcon(0, 0, 798, 54);
			IPlayer.Buff(288, 30, 0);
			IPlayer.Buff(289, 60, 0);

			if (IPlayer.GetCurMp() >= 50 && pSkill)
				IPlayer.DecreaseMana(50);
			else
				goto LABEL_1;

			IPlayer._ShowBattleAnimation(IPlayer, 46);
			goto LABEL_1;
		}

		if (IPlayer.GetClass() == 2 && SkillID == 45 && (IPlayer.GetSpecialty() == 11 || IPlayer.GetSpecialty() == 43)) {
			int nTargetID = 0; char bType = 0; void *pTarget = 0;
			CPacket::Read((char*)pPacket, (char*)pPos, "bd", &bType, &nTargetID);

			TargetFind myTarget(bType, 0, nTargetID);
			pTarget = myTarget.getTarget();

			if (pTarget) {
				IChar ITarget(pTarget);
				if (ITarget.IsValid()) {
					ITarget.CancelBuff(282);
					ITarget.CancelBuff(283);
					ITarget.CancelBuff(284);
				}

			}
		}

		if (IPlayer.GetClass() == 2 && SkillID == 47 && IPlayer.GetSpecialty() == 23)
		{
			ArrowRain(IPlayer, pPacket, pPos);
			goto LABEL_1;
		}

		if (IPlayer.GetClass() == 2 && SkillID == 49 && IPlayer.GetSpecialty() == 43)
		{
			ArrowExplosion(IPlayer, pPacket, pPos);
			goto LABEL_1;
		}

		if (IPlayer.GetClass() == 2 && SkillID == 50 && IPlayer.GetSpecialty() == 43)
		{
			VirulentArrow(IPlayer, pPacket, pPos);
			goto LABEL_1;
		}

		if (IPlayer.GetClass() == 2 && SkillID == 51 && IPlayer.GetSpecialty() == 23)
		{
			CombativeSpirit(IPlayer, pPacket, pPos);
			goto LABEL_1;
		}

		if (IPlayer.GetClass() == 3 && SkillID == 1)
		{
			Behead(IPlayer, pPacket, pPos);
			goto LABEL_1;
		}

		if (IPlayer.GetClass() == 4 && SkillID == 1)
		{
			Behead(IPlayer, pPacket, pPos);
			goto LABEL_1;
		}

		if (IPlayer.GetClass() == 3 && SkillID == 6)
		{
			Hiding(IPlayer);
			goto LABEL_1;
		}

		if (IPlayer.GetClass() == 3 && IPlayer.GetLevel() >= 81 && SkillID == 90 && IPlayer.GetSpecialty() == 23)
		{
			CriticalStrike(IPlayer, pPacket, pPos);
			goto LABEL_1;
		}

		if (IPlayer.GetClass() == 3 && IPlayer.GetLevel() >= 81 && SkillID == 92 && IPlayer.GetSpecialty() == 23)
		{
			CriticalDiffusion(IPlayer);
			goto LABEL_1;
		}

		if (IPlayer.GetClass() == 3 && IPlayer.GetLevel() >= 81 && SkillID == 91 && IPlayer.GetSpecialty() == 43)
		{
			StrikeOfGod(IPlayer);
			goto LABEL_1;
		}

		if (IPlayer.GetClass() == 3 && IPlayer.GetLevel() >= 81 && SkillID == 93 && IPlayer.GetSpecialty() == 43)
		{
			DestroyingArmor(IPlayer);
			goto LABEL_1;
		}

		if (IPlayer.GetClass() == 3 && SkillID == 33 && IPlayer.GetSpecialty() == 23)
		{
			WrathOfHeaven(IPlayer, pPacket, pPos);
			goto LABEL_1;
		}

		if (IPlayer.GetClass() == 3 && SkillID == 36 && IPlayer.GetSpecialty() == 23)
		{
			SpinBlade(IPlayer);
			goto LABEL_1;
		}

		if (IPlayer.GetClass() == 3 && SkillID == 32 && IPlayer.GetSpecialty() == 43)
		{
			ShadowSlash(IPlayer, pPacket, pPos);
			goto LABEL_1;
		}

		if (IPlayer.GetClass() == 3 && SkillID == 28 && IPlayer.GetSpecialty() == 43)
		{
			LightningSlash(IPlayer, pPacket, pPos);
			goto LABEL_1;
		}

		if (IPlayer.GetClass() == 3 && SkillID == 19 && (IPlayer.GetSpecialty() == 11 || IPlayer.GetSpecialty() == 43))
		{
			SpinAttack(IPlayer, pPacket, pPos);
			goto LABEL_1;
		}

		if (IPlayer.GetClass() == 3 && SkillID == 22 && (IPlayer.GetSpecialty() == 11 || IPlayer.GetSpecialty() == 43))
		{
			ArmorBreaker(IPlayer, pPacket, pPos);
			goto LABEL_1;
		}

		if (IPlayer.GetClass() == 3 && SkillID == 23 && (IPlayer.GetSpecialty() == 11 || IPlayer.GetSpecialty() == 43))
		{
			TwinBladeStrike(IPlayer, pPacket, pPos);
			goto LABEL_1;
		}

		if (IPlayer.GetClass() == 3 && SkillID == 18 && (IPlayer.GetSpecialty() == 7 || IPlayer.GetSpecialty() == 23))
		{
			FinalBlow(IPlayer, pPacket, pPos);
			goto LABEL_1;
		}

		if (IPlayer.GetClass() == 3 && SkillID == 21 && (IPlayer.GetSpecialty() == 7 || IPlayer.GetSpecialty() == 23))
		{
			SuicidalBlow(IPlayer, pPacket, pPos);
			goto LABEL_1;
		}

		if (IPlayer.GetClass() == 3 && SkillID == 15 && (IPlayer.GetSpecialty() == 7 || IPlayer.GetSpecialty() == 23))
		{
			AnkleAmputate(IPlayer, pPacket, pPos);
			goto LABEL_1;
		}

		if (IPlayer.GetClass() == 3 && SkillID == 16 && (IPlayer.GetSpecialty() == 7 || IPlayer.GetSpecialty() == 23))
		{
			VitalStrike(IPlayer, pPacket, pPos);
			goto LABEL_1;
		}

		if (IPlayer.GetClass() == 3 && SkillID == 14 && (IPlayer.GetSpecialty() == 7 || IPlayer.GetSpecialty() == 23))
		{
			FatalWound(IPlayer, pPacket, pPos);
			goto LABEL_1;
		}

		if (IPlayer.GetClass() == 3 && SkillID == 17 && (IPlayer.GetSpecialty() == 7 || IPlayer.GetSpecialty() == 23))
		{
			Rupture(IPlayer, pPacket, pPos);
			goto LABEL_1;
		}

		if (IPlayer.GetClass() == 3 && SkillID == 7)
		{
			Assault(IPlayer, pPacket, pPos);
			goto LABEL_1;
		}

		if (IPlayer.GetClass() == 3 && SkillID == 13 && (IPlayer.GetSpecialty() == 11 || IPlayer.GetSpecialty() == 43) && !IPlayer.IsBuff(333))
		{
			int pSkill = IPlayer.GetSkillPointer(13);

			if (pSkill)
			{
				ISkill xSkill((void*)pSkill);
				int nSkillGrade = xSkill.GetGrade();
				int nMana = nSkillGrade * 20 + 80;

				if (IPlayer.GetCurMp() >= nMana && nSkillGrade)
				{
					if (!IPlayer.IsBuff(333))
						IPlayer.SendGStateEx(IPlayer.GetGStateEx() + 1024);

					IPlayer.Buff(333, nSkillGrade * 15, 0);
					IPlayer.DecreaseMana(nMana);
					IPlayer._ShowBattleAnimation(IPlayer, 13, nSkillGrade);
				}
			}

			goto LABEL_1;
		}

		if (IPlayer.GetClass() == 3 && IPlayer.GetSpecialty() >= 3)
		{
			if (SkillID == 8)
			{
				Stun(IPlayer, pPacket, pPos);
				goto LABEL_1;
			}

			if (SkillID == 9)
			{
				Confusion(IPlayer, pPacket, pPos);
				goto LABEL_1;
			}

			if (SkillID == 10)
			{
				Strangle(IPlayer, pPacket, pPos);
				goto LABEL_1;
			}

			if (SkillID == 12 && !IPlayer.IsBuff(354) && !IPlayer.IsBuff(355))
			{
				DualShadow(IPlayer, pPacket, pPos);
				goto LABEL_1;
			}
		}

		if (IPlayer.GetClass() == 3 && SkillID == 20 && (IPlayer.GetSpecialty() == 11 || IPlayer.GetSpecialty() == 43) && !IPlayer.IsBuff(335))
		{
			int pSkill = IPlayer.GetSkillPointer(20);

			if (pSkill)
			{
				ISkill xSkill((void*)pSkill);
				int nSkillGrade = xSkill.GetGrade();
				int nMana = nSkillGrade * 30 + 45;

				if (IPlayer.GetCurMp() >= nMana && nSkillGrade)
				{
					IPlayer.Buff(335, 10, 0);
					IPlayer.SetBuffIcon(10000, 0, 2019, 217);
					IPlayer.DecreaseMana(nMana);
					IPlayer._ShowBattleAnimation(IPlayer, 20);
					CChar::CancelAllBuff(IPlayer.GetOffset(), 337);
				}
			}

			goto LABEL_1;
		}

		if (IPlayer.GetClass() == 3 && SkillID == 63 && (IPlayer.GetSpecialty() == 11 || IPlayer.GetSpecialty() == 43) && !IPlayer.IsBuff(337))
		{
			int pSkill = IPlayer.GetSkillPointer(63);

			if (pSkill)
			{
				ISkill xSkill((void*)pSkill);
				int nSkillGrade = xSkill.GetGrade();
				int nMana = nSkillGrade * 30 + 50;

				if (IPlayer.GetCurMp() >= nMana && nSkillGrade)
				{
					IPlayer.Buff(337, 30, 0);
					IPlayer.Buff(338, 35, 0);
					IPlayer.SetBuffIcon(30000, 0, 2427, 323);
					IPlayer.DecreaseMana(nMana);
					IPlayer._ShowBattleAnimation(IPlayer, 63);
					CChar::CancelAllBuff(IPlayer.GetOffset(), 335);
				}
			}

			goto LABEL_1;
		}

		if (IPlayer.GetClass() == 4 && IPlayer.GetSpecialty() >= 1)
		{
			if (SkillID == 13)
			{
				GhostKnife(IPlayer, pPacket, pPos);
				goto LABEL_1;
			}

			if (SkillID == 14)
			{
				GhostFlash(IPlayer, pPacket, pPos);
				goto LABEL_1;
			}

			if (SkillID == 15)
			{
				SoulShield(IPlayer, pPacket, pPos);
				goto LABEL_1;
			}
		}

		if (IPlayer.GetClass() == 4 && IPlayer.GetSpecialty() >= 3)
		{
			if (SkillID == 18)
			{
				Wave(IPlayer, pPacket, pPos);
				goto LABEL_1;
			}

			if (SkillID == 19)
			{
				GhostWindow(IPlayer, pPacket, pPos);
				goto LABEL_1;
			}

			if (SkillID == 20)
			{
				MudRoom(IPlayer, pPacket, pPos);
				goto LABEL_1;
			}

			if (SkillID == 21)
			{
				ExecutiveDirector(IPlayer, pPacket, pPos);
				goto LABEL_1;
			}

			if (SkillID == 22)
			{
				TheSoulsPenance(IPlayer, pPacket, pPos);
				goto LABEL_1;
			}
		}

		if (IPlayer.GetClass() == 4 && (IPlayer.GetSpecialty() == 7 || IPlayer.GetSpecialty() == 23))
		{
			if (SkillID == 25)
			{
				Entangling(IPlayer, pPacket, pPos);
				goto LABEL_1;
			}

			if (SkillID == 26)
			{
				SpearOfPain(IPlayer, pPacket, pPos);
				goto LABEL_1;
			}

			if (SkillID == 27)
			{
				int pSkill = IPlayer.GetSkillPointer(27);

				if (IPlayer.IsValid() && pSkill && !IPlayer.IsBuff(406))
				{
					ISkill xSkill((void*)pSkill);
					int nSkillGrade = xSkill.GetGrade();
					int nMana = (nSkillGrade * 2) + 300;

					if (IPlayer.IsValid() && IPlayer.GetCurMp() >= nMana && nSkillGrade)
					{
						IPlayer._ShowBattleAnimation(IPlayer, 27);
						IPlayer.DecreaseMana(nMana);
						IPlayer.SetBuffIcon(((nSkillGrade * 60) + 300) * 1000, 0, 9103, 1012);
						IPlayer.Buff(405, (nSkillGrade * 60) + 300, 0);
						IPlayer.Buff(406, (nSkillGrade * 100) + 300, 0);
					}
				}

				goto LABEL_1;
			}

			if (SkillID == 28)
			{
				DrainBlood(IPlayer, pPacket, pPos);
				goto LABEL_1;
			}

			if (SkillID == 29)
			{
				MentalBreakdown(IPlayer, pPacket, pPos);
				goto LABEL_1;
			}

			if (SkillID == 54)
			{
				MagicalExplosion(IPlayer, pPacket, pPos);
				goto LABEL_1;
			}
		}

		if (IPlayer.GetClass() == 4 && (IPlayer.GetSpecialty() == 11 || IPlayer.GetSpecialty() == 43))
		{
			if (SkillID == 36)
			{
				JigukKing(IPlayer, pPacket, pPos);
				goto LABEL_1;
			}

			if (SkillID == 37)
			{
				JeungjangKing(IPlayer, pPacket, pPos);
				goto LABEL_1;
			}

			if (SkillID == 38)
			{
				AmplificationOfBlood(IPlayer, pPacket, pPos);
				goto LABEL_1;
			}

			if (SkillID == 39)
			{
				WaveOfEmperor(IPlayer, pPacket, pPos);
				goto LABEL_1;
			}
		}

		if (IPlayer.GetClass() == 4 && IPlayer.GetSpecialty() == 23)
		{
			if (SkillID == 44)
			{
				Collapse(IPlayer, pPacket, pPos);
				goto LABEL_1;
			}

			if (SkillID == 45)
			{
				if (!IPlayer.IsBuff(406))
					goto LABEL_1;

				int pSkill = IPlayer.GetSkillPointer(45);

				if (IPlayer.IsValid() && pSkill)
				{
					ISkill xSkill((void*)pSkill);
					int nSkillGrade = xSkill.GetGrade();
					int nMana = (nSkillGrade * 2) + 200;

					if (IPlayer.IsValid() && IPlayer.GetCurMp() >= nMana && nSkillGrade)
					{
						IPlayer._ShowBattleAnimation(IPlayer, 45);
						IPlayer.DecreaseMana(nMana);
						IPlayer.SetBuffIcon(-2, -1, 9106, 1015);
						IPlayer.Buff(412, BuffNames::BuffTime, 15 * nSkillGrade);
					}
				}

				goto LABEL_1;
			}

			if (SkillID == 46)
			{
				SixSouls(IPlayer, pPacket, pPos);
				goto LABEL_1;
			}

			if (SkillID == 47)
			{
				ExplodingSpirit(IPlayer, pPacket, pPos);
				goto LABEL_1;
			}

			if (SkillID == 90)
			{
				SpiritWave(IPlayer, pPacket, pPos);
				goto LABEL_1;
			}

			if (SkillID == 92)
			{
				Doggebi(IPlayer, pPacket, pPos);
				goto LABEL_1;
			}
		}

		if (IPlayer.GetClass() == 4 && IPlayer.GetSpecialty() == 43)
		{
			if (SkillID == 50)
			{
				JigukKingOfTaein(IPlayer, pPacket, pPos);
				goto LABEL_1;
			}

			if (SkillID == 51)
			{
				JeungjangKingOfTaein(IPlayer, pPacket, pPos);
				goto LABEL_1;
			}

			if (SkillID == 52)
			{
				SoulBlow(IPlayer, pPacket, pPos);
				goto LABEL_1;
			}

			if (SkillID == 91)
			{
				RisingKing4th(IPlayer, pPacket, pPos);
				goto LABEL_1;
			}

			if (SkillID == 93)
			{
				Gangshin4th(IPlayer, pPacket, pPos);
				goto LABEL_1;
			}
		}

		CSkill::ExecuteSkill(pSkill, SkillID, pPacket, pPos);

		if (IPlayer.GetClass() == 1 && IPlayer.GetMap() != 21 && SkillID == 41 && IPlayer.IsValid()) {
			int Around = IPlayer.GetObjectListAround(4);
			while (Around)
			{
				IChar Object((void*)CBaseList::Offset((void*)Around));

				if (IPlayer.IsValid() && Object.IsValid() && IPlayer.IsValid() && IPlayer.GetOffset() != Object.GetOffset() && IPlayer.GetOffset() != Object.GetOffset() && (*(int(__thiscall **)(int, int, DWORD))(*(DWORD *)IPlayer.GetOffset() + 176))((int)IPlayer.GetOffset(), (int)Object.GetOffset(), 0))
				{
					if (Object.IsBuff(307))
						StormActivateShiny(IPlayer, Object);
				}

				Around = CBaseList::Pop((void*)Around);
			}
		}

		int KeyZ = (IPlayer.GetClass() * 1000) + SkillID;
		if (SkillsDamage.count(KeyZ) || SkillsDamage.count(KeyZ + 100) || SkillsDamage.count(KeyZ + 200)) {
			int range = 0;
			if (SkillsDamage.count(KeyZ))
				range = SkillsDamage.find(KeyZ)->second.AOE;
			if (SkillsDamage.count(KeyZ + 100))
				range = SkillsDamage.find(KeyZ + 100)->second.AOE;
			if (SkillsDamage.count(KeyZ + 200))
				range = SkillsDamage.find(KeyZ + 200)->second.AOE;

			if (range) {
				int nTargetID = 0;
				char bType = 0;
				void *pTarget = 0;
				CPacket::Read((char*)pPacket, (char*)pPos, "bd", &bType, &nTargetID);

				TargetFind myTarget(bType, 0, nTargetID);
				pTarget = myTarget.getTarget();
				IChar Target(pTarget);

				int Around = IPlayer.GetObjectListAround(range);
				while (Around)
				{
					IChar Object((void*)CBaseList::Offset((void*)Around));
					int damage = IPlayer.GetDamage(SkillID, Object.GetOffset());

					if (Object.IsValid() && IPlayer.IsValid() && Object.GetOffset() != Target.GetOffset() && Object.GetOffset() != IPlayer.GetOffset() && (*(int(__thiscall **)(int, int, DWORD))(*(DWORD *)IPlayer.GetOffset() + 176))((int)IPlayer.GetOffset(), (int)Object.GetOffset(), 0))
						IPlayer.OktayDamageArea(Object, damage, SkillID);

					Around = CBaseList::Pop((void*)Around);
				}
			}
		}

	LABEL_1:
		if (SDamaged)
			IPlayer.SetProperty(PlayerProperty::SkillsEdit, 0);
		return;
	}
}