void ExecuteMonsterSkill(IChar IPlayer, IChar Object, MSkill mSkill) {
	if (IPlayer.IsValid() && Object.IsValid() && Object.GetType() == 0) {
		int DMG = CTools::Rate(mSkill.DamageMin, mSkill.DamageMax);
		int n = DMG;
		int digits = 0;
		while (n /= 10)
			digits++;

		if (digits > 2)
			digits -= 2;
		else
			digits = 0;

		DMG -= (DMG > Object.GetLevel()) ? (Object.GetLevel() * (int)pow(10.0, digits)) : DMG;

		if (DMG && IPlayer.CheckHit(Object, DMG) && (*(int(__thiscall **)(int, int, DWORD))(*(DWORD *)IPlayer.GetOffset() + 176))((int)IPlayer.GetOffset(), (int)Object.GetOffset(), 0)) {
			int NormalDamage = 0, DamageArgument = 0, EBDamage = 0, Check = 0, TypeKind = 0, GetType = 0;

			TypeKind = (*(int(__thiscall **)(LONG, void *))(*(DWORD *)Object.GetOffset() + 148))((int)Object.GetOffset(), IPlayer.GetOffset());

			Check = (*(int(__thiscall**)(LONG, void*, unsigned int, int*, int*, int*, DWORD))(*(DWORD*)Object.GetOffset() + 72))((int)Object.GetOffset(), IPlayer.GetOffset(), DMG, &NormalDamage, &DamageArgument, &EBDamage, 0);
			GetType = Check | 2 * DamageArgument | 4 * TypeKind;
			if (!mSkill.EffectType)
				Object.AddFxToTarget(mSkill.Effect, 0, 0, 0);

			CChar::WriteInSight(IPlayer.GetOffset(), 62, "ddddbd", IPlayer.GetID(), Object.GetID(), NormalDamage, EBDamage, GetType, 0);
		}

		if (mSkill.BuffTime)
			Object.Buff(mSkill.Buff, mSkill.BuffTime, mSkill.BuffValue);

		if (mSkill.SBKey && mSkill.SBName)
			Object.SetBuffIcon(mSkill.BuffTime * 1000, 0, mSkill.SBName, mSkill.SBKey);
	}
}


int __fastcall GetPalsyDamage(int Player, void *edx, int Target)
{
	IChar ITarget((void*)Target);

	if (Target == (int)GuildRaid::Boss)
		return 0;

	return CPlayer::GetPalsyDamage(Player, Target);
}

int __fastcall GetFatalDamage(int Player, void *edx, int Damage, int Argument, int Value)
{
	IChar IPlayer((void*)Player);

	if (Damage == 1)
		return 0;

	Value += IPlayer.GetBuffValue(BuffNames::CritChance);

	int FatalDamage = CChar::GetFatalDamage(Player, Damage, Argument, Value);

	if (FatalDamage) {
		if (IPlayer.GetType() == 0) {
			if (IPlayer.IsBuff(BuffNames::PVPHit))
				FatalDamage = (FatalDamage * FatalDamagePVP) / 100;
			else
				FatalDamage = (FatalDamage * FatalDamagePVE) / 100;

			int Class = IPlayer.GetClass();
			int Spec = IPlayer.GetSpecialty();

			if (FatalDmg.count((Class * 1000) + Spec))
				FatalDamage = (FatalDamage * FatalDmg.find((Class * 1000) + Spec)->second) / 100;
		}
	}

	return FatalDamage;
}

int __fastcall GetFinalDamage(void *Target, void *edx, int Player, int Damage, int Argument)
{
	IChar IPlayer((void*)Player);
	IChar ITarget(Target);

	if ((IPlayer.GetType() == 1 || ITarget.GetType() == 1) && InterlockedExchangeAdd(&MonsterReloaded, 0) > GetTickCount())
		return 0;

	if (IPlayer.GetChannel() != ITarget.GetChannel())
		return 0;

	int CheckDamage = CChar::GetFinalDamage(Target, Player, Damage, Argument);

	if (IPlayer.GetType() == 1 && (IPlayer.GetMobIndex() >= 319 && IPlayer.GetMobIndex() <= 333))
		return CheckDamage;

	if (IPlayer.IsValid() && ITarget.IsValid()) {
		if (IPlayer.GetType() == 0 && CheckDamage && isInMacroMap(IPlayer.GetX() >> 13, IPlayer.GetY() >> 13)) {
			if (IPlayer.GetBuffValue(BuffNames::MacroMap) && IPlayer.IsPVPValid())
				return 0;

			*(DWORD *)(Player + 1464) = GetTickCount();
		}

		if (IPlayer.GetType() == 0 && CSMap::IsOnTile(*(void **)((int)IPlayer.Offset + 320), (int)IPlayer.Offset + 332, 131072) && !CChar::IsGState((int)IPlayer.GetOffset(), 128))
			return 0;

		if (ITarget.GetType() == 0 && CSMap::IsOnTile(*(void **)((int)ITarget.Offset + 320), (int)ITarget.Offset + 332, 131072) && !CChar::IsGState((int)ITarget.GetOffset(), 128))
			return 0;

		if (ITarget.GetType() == 0 && ITarget.IsBuff(BuffNames::Unkillableness))
			return 0;

		if (strlen(AntiKsCheck) && ((std::string)AntiKsCheck == "true" || (std::string)AntiKsCheck == "True"))
		{
			if (ITarget.GetType() == 1 && IPlayer.GetType() == 0) {
				if (AntiKs.count(ITarget.GetMobIndex()) && ITarget.GetMobTanker()) {
					IChar Tanker((void*)ITarget.GetMobTanker());
					int KSTime = 0;

					if (AntiKSTime) {
						KSTime = ITarget.GetBuffValue(BuffNames::AntiKS);
						if (!KSTime) {
							KSTime = GetTickCount() + (AntiKSTime * 1000);
							ITarget.UpdateBuff(BuffNames::AntiKS, BuffNames::BuffTime, GetTickCount() + (AntiKSTime * 1000));
						}
					}

					if ((Tanker.IsParty() && Tanker.GetPartyID() != IPlayer.GetPartyID()) || (!Tanker.IsParty() && Tanker.GetPID() != IPlayer.GetPID()))
					{
						if (!AntiKSTime || KSTime >= GetTickCount()) {
							IPlayer.SystemMessage("[Anti ks] Our server doesn't tolerate ksing.", TEXTCOLOR_RED);
							return 0;
						}
						else if (AntiKSTime)
							ITarget.UpdateBuff(BuffNames::AntiKS, BuffNames::BuffTime, GetTickCount() + (AntiKSTime * 1000));
					}
				}
			}
		}

		if (IPlayer.GetType() == 0 && !IPlayer.GetAdmin()) {
			int range = 0;

			if (IPlayer.GetClass() == 0 || IPlayer.GetClass() == 3)
				range = 3;
			if (IPlayer.GetClass() == 2 || IPlayer.GetClass() == 4)
				range = 8;
			if (IPlayer.GetClass() == 1)
				range = 7;

			if (!IPlayer.IsInRange(ITarget, range))
				return 0;
		}

		if (CheckDamage && IPlayer.GetType() == 0 && ITarget.GetType() == 0 && IPlayer.IsBuff(25))
			IPlayer.CancelBuff(25);


		if (CheckDamage && IPlayer.GetType() == 0 && ITarget.GetType() == 0)
		{

			for (std::map<int, PVEWeaponsS>::const_iterator it = PVEWeapon.begin(); it != PVEWeapon.end(); ++it) {
				const PVEWeaponsS& weapon = it->second;
				int PVEWep = CPlayer::FindItem(IPlayer.GetOffset(), weapon.index, 1);

				if (CheckDamage && IPlayer.GetType() == 0 && ITarget.GetType() == 0 && PVEWep && CItem::IsState(PVEWep, 1))
				{

					IPlayer.SystemMessage("You are not allowed to attack players using a PVE Weapon.", TEXTCOLOR_RED);
					return 0;

				}

			}
		}

		if (CheckDamage && IPlayer.GetMap() != LawlessMap && IPlayer.GetType() == 0 && ITarget.GetType() == 0 && AssassinParty)
		{
			if (IPlayer.IsParty() && ITarget.IsParty() && (IPlayer.GetPartyID() == ITarget.GetPartyID()) && CChar::IsGState((int)IPlayer.Offset, 256))
			{
				IPlayer.SystemMessage("You are not allowed to assasinate a party member.", TEXTCOLOR_RED);
				return 0;
			}

		}

		if (CheckDamage && IPlayer.GetMap() != LawlessMap && IPlayer.GetType() == 0 && ITarget.GetType() == 0 && AssassinLimit)
		{
			if ((IPlayer.GetLevel() >= ITarget.GetLevel() + AssassinLimit) && CChar::IsGState((int)IPlayer.Offset, 256))
			{
				IPlayer.SystemMessage("You are not allowed to assasinate a player who is " + Int2String(AssassinLimit) + " levels lower than you.", TEXTCOLOR_RED);
				return 0;
			}

			if ((IPlayer.GetLevel() + AssassinLimit <= ITarget.GetLevel()) && CChar::IsGState((int)ITarget.Offset, 256))
			{
				IPlayer.SystemMessage("You are not allowed to hit assassin who is " + Int2String(AssassinLimit) + " levels higher than you.", TEXTCOLOR_RED);
				return 0;
			}
		}

		if (CheckDamage && IPlayer.GetType() == 0 && (IPlayer.GetClass() == 4 || IPlayer.GetClass() == 1) && !IPlayer.IsBuff(306)) {
			if (IPlayer.GetLevel() + GetLevelDiff() <= ITarget.GetLevel())
				return 0;
		}

		if (CheckDamage && IPlayer.GetType() == 0 && ITarget.GetType() == 0 && CheckDamage >= 1000)
		{
			if (IPlayer.GetLevel() < ITarget.GetLevel())
			{
				int GetLD = ITarget.GetLevel() - IPlayer.GetLevel();

				if (GetLD >= 10)
					CheckDamage = CheckDamage / 2;
				else
					CheckDamage = (CheckDamage * (100 - (5 * GetLD))) / 100;
			}
		}

		//
		//CriticalLock lock2((struct _RTL_CRITICAL_SECTION *)((int)ITarget.GetOffset() + 364));

		if (IPlayer.GetType() == 0 && ITarget.GetType() == 1 && IPlayer.isInTrainingMap() && CheckDamage && ITarget.GetMobIndex() == 1152) {
			if (IPlayer.GetBuffValue(BuffNames::TrainingTime)) {
				int HittingTime = IPlayer.GetBuffValue(BuffNames::TrainingHits);
				if (HittingTime && HittingTime < GetTickCount()) {
					int Drop = -1;
					signed __int64 EXP = 1000 * IPlayer.GetLevel();
					for (int i = IPlayer.GetLevel(); i <= 255; i++) {
						if (TrainingEXP.count(i)) {
							EXP = TrainingEXP.find(i)->second.EXP;
							Drop = TrainingEXP.find(i)->second.Drop;
							break;
						}
					}
					CPlayer::UpdateProperty(Player, 25, 1, EXP);
					int Rate = CTools::Rate(1, 100000);
					if (Drop != -1 && TrainingDrops.count(Drop) && Rate <= TrainingDrops.find(Drop)->second.Chance)
						IPlayer.InsertItem(TrainingDrops.find(Drop)->second.Index, 0, 1);
					IPlayer.UpdateBuff(BuffNames::TrainingHits, BuffNames::BuffTime, 0);
				}
				else if (!HittingTime)
					IPlayer.UpdateBuff(BuffNames::TrainingHits, BuffNames::BuffTime, GetTickCount() + TrainingHit);
			}
			ITarget.IncreaseHp(100000);
			return 1;
		}
		// meat while attack fix
		if (IPlayer.IsBuff(19))
			IPlayer.CancelBuff(19);
		if (IPlayer.IsBuff(18))
			IPlayer.CancelBuff(18);

		if (GuildRaid::Active && Target == GuildRaid::Boss)
			return 1;

		int SkillsEdit = 0;
		int MageMICheck = 0;

		if (IPlayer.GetType() == 0) {
			SkillsEdit = IPlayer.GetProperty(PlayerProperty::SkillsEdit);
			MageMICheck = IPlayer.GetBuffValue(BuffNames::MageMICheck);
		}

		if (IPlayer.GetType() == 0)
			IPlayer.Buff(313, 3, 0);

		if (ITarget.GetType() == 0)
			ITarget.Buff(313, 3, 0);

		if (IPlayer.GetType() == 0 && ITarget.GetType() == 0) {
			if (IPlayer.IsBuff(2126))
				IPlayer.Buff(987, 5, 0);
			if (ITarget.IsBuff(2126))
				ITarget.Buff(987, 5, 0);

			IPlayer.Buff(BuffNames::PVPHit, 3, 0);
		}

		if (ITarget.GetType() == 0 && IPlayer.GetType() == 0 && ITarget.IsBuff(347) && ITarget.GetMap() != BanditsMap)
			ITarget.DisableRiding();

		if (SkillsEdit) {
			int Check = IPlayer.GetDamage(SkillsEdit, ITarget.GetOffset());
			if (Check)
				CheckDamage = Check;
		}

		if (IPlayer.GetType() == 1 && ITarget.GetType() == 0 && ITarget.IsBuff(52) && CheckDamage)
			CheckDamage -= (CheckDamage * 10) / 100;

		if (CheckDamage > 0 && IPlayer.GetType() == 0 && ITarget.GetType() == 1)
		{
			for (std::map<int, BuffMaker>::const_iterator it = BuffMakerCheck.begin(); it != BuffMakerCheck.end(); ++it) {
				const BuffMaker& buff = it->second;
				if (IPlayer.IsBuff(buff.BuffID) && buff.Damage == "true") {
					CheckDamage -= (CheckDamage * buff.MD) / 100;
				}
			}

		}

		int AddCheck = IPlayer.GetBuffValue(2125);

		if (CheckDamage > 0 && IPlayer.GetType() == 0 && ITarget.GetType() == 1 && AddCheck && AddCheck <= 100)
			CheckDamage -= (CheckDamage * AddCheck) / 100;

		int AddCheck2 = ITarget.GetBuffValue(2128);
		if (IPlayer.GetType() == 1 && ITarget.GetType() == 0 && AddCheck2 && AddCheck2 < 100)
			CheckDamage -= ((CheckDamage * AddCheck2) / 100);


		if (IPlayer.GetType() == 0 && ITarget.GetType() == 1 && DamageEvent::Active)
			CheckDamage += (CheckDamage * DamagePercentage) / 100;

		if (IPlayer.GetType() == 0 && ITarget.GetType() == 0) {
			if (IPlayer.GetAdmin() == 0 && ITarget.GetAdmin() == 0 && CheckDamage > ConfigPVPMaxDmg)
				CheckDamage = ConfigPVPMaxDmg;

			int PVPSkill = IPlayer.GetBuffValue(3780);
			if (PVPSkill) {
				if (!((IPlayer.GetClass() == 1 && (PVPSkill == 43 || PVPSkill == 45 || PVPSkill == 48)) || (IPlayer.GetClass() == 2 && PVPSkill == 42))) {
					if (PVPConfigCalculations.count((IPlayer.GetClass() * 1000) + PVPSkill + (ITarget.GetClass() * 100)))
						CheckDamage += ((CheckDamage * PVPConfigCalculations.find((IPlayer.GetClass() * 1000) + PVPSkill + (ITarget.GetClass() * 100))->second.Rate) / 100);

					if (PVPConfigCalculations.count((IPlayer.GetClass() * 1000) + PVPSkill + 500))
						CheckDamage += ((CheckDamage * PVPConfigCalculations.find((IPlayer.GetClass() * 1000) + PVPSkill + 500)->second.Rate) / 100);
				}
				IPlayer.UpdateBuff(3780, BuffNames::BuffTime, 0);
			}

			int PClass = IPlayer.GetClass();
			int TClass = ITarget.GetClass();

			auto it = PlayerVsPlayerDmg.find((PClass * 100000) + (IPlayer.GetSpecialty() * 1000) + (TClass * 100) + ITarget.GetSpecialty());
			if (it != PlayerVsPlayerDmg.end())
				CheckDamage += ((CheckDamage*it->second) / 100);
			else {
				if (PClass == 0) {
					if (TClass == 0) CheckDamage += ((CheckDamage*KVK) / 100);
					else if (TClass == 1) CheckDamage += ((CheckDamage*KVM) / 100);
					else if (TClass == 2) CheckDamage += ((CheckDamage*KVA) / 100);
					else if (TClass == 3) CheckDamage += ((CheckDamage*KVT) / 100);
					else if (TClass == 4) CheckDamage += ((CheckDamage*KVS) / 100);
				}

				else if (PClass == 1) {
					if (TClass == 0) CheckDamage += ((CheckDamage*MVK) / 100);
					else if (TClass == 1) CheckDamage += ((CheckDamage*MVM) / 100);
					else if (TClass == 2) CheckDamage += ((CheckDamage*MVA) / 100);
					else if (TClass == 3) CheckDamage += ((CheckDamage*MVT) / 100);
					else if (TClass == 4) CheckDamage += ((CheckDamage*MVS) / 100);
				}

				else if (PClass == 2) {
					if (TClass == 0) CheckDamage += ((CheckDamage*AVK) / 100);
					else if (TClass == 1) CheckDamage += ((CheckDamage*AVM) / 100);
					else if (TClass == 2) CheckDamage += ((CheckDamage*AVA) / 100);
					else if (TClass == 3) CheckDamage += ((CheckDamage*AVT) / 100);
					else if (TClass == 4) CheckDamage += ((CheckDamage*AVS) / 100);
				}

				else if (PClass == 3) {
					if (TClass == 0) CheckDamage += ((CheckDamage*TVK) / 100);
					else if (TClass == 1) CheckDamage += ((CheckDamage*TVM) / 100);
					else if (TClass == 2) CheckDamage += ((CheckDamage*TVA) / 100);
					else if (TClass == 3) CheckDamage += ((CheckDamage*TVT) / 100);
					else if (TClass == 4) CheckDamage += ((CheckDamage*TVS) / 100);
				}

				else if (PClass == 4) {
					if (TClass == 0) CheckDamage += ((CheckDamage*SVK) / 100);
					else if (TClass == 1) CheckDamage += ((CheckDamage*SVM) / 100);
					else if (TClass == 2) CheckDamage += ((CheckDamage*SVA) / 100);
					else if (TClass == 3) CheckDamage += ((CheckDamage*SVT) / 100);
					else if (TClass == 4) CheckDamage += ((CheckDamage*SVS) / 100);
				}
			}
		}

		if (IPlayer.GetType() == 0 && ITarget.GetType() == 0 && IPlayer.IsBuff(356))
			return 0;

		if (Scenario::Active == true && CheckDamage && IPlayer.GetType() == 0 && ITarget.GetType() == 0 && IPlayer.IsBuff(162) && ITarget.IsBuff(162))
			return 0;

		if (Scenario::Active == true && CheckDamage && IPlayer.GetType() == 0 && ITarget.GetType() == 0 && IPlayer.IsBuff(163) && ITarget.IsBuff(163))
			return 0;

		if (Protect32::Active == true && CheckDamage && IPlayer.GetType() == 0 && ITarget.GetType() == 0 && IPlayer.IsBuff(170) && ITarget.IsBuff(170))
			return 0;

		if (Protect32::Active == true && CheckDamage && IPlayer.GetType() == 0 && ITarget.GetType() == 0 && IPlayer.IsBuff(171) && ITarget.IsBuff(171))
			return 0;

		if (ITarget.GetType() == 1 && IPlayer.GetType() == 0 && CheckDamage) {
			if (ITarget.GetMobIndex() == BossIndex) {
				int BossDmg = IPlayer.GetBuffValue(BuffNames::BossHunt) + CheckDamage;
				IPlayer.UpdateBuff(BuffNames::BossHunt, BuffNames::BuffTime, BossDmg);
				if (BossDmg > BossHunting::maxDmg)
					BossHunting::maxDmg = BossDmg;
			}
		}

		if (CaptureFlag::Active &&  IPlayer.GetType() == 0 && ITarget.GetType() == 1 && CheckDamage) {
			if (IPlayer.IsBuff(CaptureFlag::CurrentCapturers) && ITarget.GetMobIndex() == CaptureMonster)
				return 0;
		}

		if (Scenario::Active == true && ITarget.GetType() == 1 && CheckDamage)
		{
			if ((ITarget.GetMobIndex() == 352 || ITarget.GetMobIndex() == 354) && IPlayer.IsBuff(162))
				return 0;

			if ((ITarget.GetMobIndex() == 356 || ITarget.GetMobIndex() == 358) && IPlayer.IsBuff(163))
				return 0;
		}

		if (Scenario::Active == true && ITarget.GetType() == 1 && CheckDamage)
		{
			if (ITarget.GetMobIndex() == 360 && IPlayer.IsBuff(162) && Scenario::RedTeamSeal == 0)
			{
				IPlayer.SystemMessage("White Tiger seal should be broken to attack Giant Tower.", TEXTCOLOR_RED);
				return 0;
			}

			if (ITarget.GetMobIndex() == 360 && IPlayer.IsBuff(163) && Scenario::BlueTeamSeal == 0)
			{
				IPlayer.SystemMessage("Blue Dragon seal should be broken to attack Giant Tower.", TEXTCOLOR_RED);
				return 0;
			}
		}

		if (Battlefield::Active) {
			if (CheckDamage && IPlayer.GetType() == 0 && ITarget.GetType() == 0 && IPlayer.IsBuff(160) && ITarget.IsBuff(160))
				return 0;

			if (CheckDamage && IPlayer.GetType() == 0 && ITarget.GetType() == 0 && IPlayer.IsBuff(161) && ITarget.IsBuff(161))
				return 0;
		}

		if (CheckDamage && IPlayer.GetType() == 0 && ITarget.GetType() == 0 && IPlayer.IsBuff(BuffNames::PTVsPTBlue) && ITarget.IsBuff(BuffNames::PTVsPTBlue))
			return 0;

		if (CheckDamage && IPlayer.GetType() == 0 && ITarget.GetType() == 0 && IPlayer.IsBuff(BuffNames::PTVsPTRed) && ITarget.IsBuff(BuffNames::PTVsPTRed))
			return 0;

		if (Battlefield::Active && ITarget.GetType() == 1 && CheckDamage)
		{
			if (ITarget.GetMobIndex() == 445 && IPlayer.IsBuff(161))
				return 0;

			if (ITarget.GetMobIndex() == 448 && IPlayer.IsBuff(160))
				return 0;
		}

		if (ITarget.GetType() == 0 && CheckDamage && (CaptureFlag::Active || Battlefield::Active))
		{
			//if ((int)ITarget.GetOffset() == CaptureFlag::PlayerID && CaptureFlag::Active == true)
			//CaptureFlag::LastHit = Player;

			if (CheckDamage >= ITarget.GetCurHp() && (IPlayer.IsBuff(160) || IPlayer.IsBuff(161) || IPlayer.IsBuff(180) || IPlayer.IsBuff(179)))
			{
				IPlayer.SetHonor(1, 1, 0, 0, 0, 0, 0, 0, 0, 1);
				ITarget.SetHonor(0, 0, 1, 0, 0, 0, 0, 0, 0, 0);
			}
		}

		if (ITarget.GetType() == 0 && CheckDamage && (Scenario::Active == true || CaptureFlag::Active))
		{
			if (CheckDamage >= ITarget.GetCurHp() && (IPlayer.IsBuff(162) || IPlayer.IsBuff(163) || IPlayer.IsBuff(180) || IPlayer.IsBuff(80)))
			{
				IPlayer.SetHonor(1, 1, 0, 0, 0, 0, 0, 0, 0, 1);
				ITarget.SetHonor(0, 0, 1, 0, 0, 0, 0, 0, 0, 0);
			}
		}

		if (ITarget.GetType() == 1)
		{
			if (ITarget.IsBuff(159))
				return 0;
		}

		if (IPlayer.GetType() == 1)
		{
			if (IPlayer.IsBuff(159))
				return 0;
		}

		if (ITarget.GetType() == 0)
		{
			if (ITarget.IsBuff(159) || (ITarget.IsBuff(327) && !ITarget.IsBuff(11) && !ITarget.IsBuff(339) && !ITarget.IsBuff(348) && !ITarget.IsBuff(350)) || (ITarget.IsBuff(329) && !ITarget.IsBuff(11) && !ITarget.IsBuff(339) && !ITarget.IsBuff(348) && !ITarget.IsBuff(350))) {
				return 0;
			}
		}

		if (IPlayer.GetType() == 0)
		{
			if (IPlayer.IsBuff(159) || (IPlayer.IsBuff(327) && !IPlayer.IsBuff(352) && !IPlayer.IsBuff(353) && !IPlayer.IsBuff(341)) || (IPlayer.IsBuff(329) && !IPlayer.IsBuff(341) && !IPlayer.IsBuff(352) && !IPlayer.IsBuff(348) && !IPlayer.IsBuff(353))) {
				return 0;
			}
		}

		if (IPlayer.GetType() == 0 && IPlayer.GetClass() == 1 && MageMICheck)
		{
			if (IPlayer.IsBuff(306) && MageMICheck != 43 && MageMICheck != 45 && MageMICheck != 48 && MageMICheck != 73 && MageMICheck != 74 && MageMICheck != 75)
			{
				int pSkill = IPlayer.GetSkillPointer(64);

				if (pSkill)
				{
					ISkill xSkill((void*)pSkill);

					int DmgSCheck = IPlayer.GetDamage(64, ITarget.GetOffset());
					int nDmg = DmgSCheck;

					if (!nDmg) {
						nDmg = (IPlayer.GetMagic() * MMIMul) + (xSkill.GetGrade() * CTools::Rate(MMIMin, MMIMax));

						if (ITarget.GetType() == 0)
							nDmg = nDmg * MMIReduce / 100;
					}

					if (CheckDamage <= 0)
						CheckDamage = nDmg;

					if (CheckDamage)
						CheckDamage += nDmg;
				}
			}
		}

		if (ITarget.GetType() == 0)
		{
			if (ITarget.IsBuff(284) && CheckDamage > 10 && ITarget.GetType() == 0)
				CheckDamage *= (PDPVP / 100);
			if (ITarget.IsBuff(284) && CheckDamage > 10 && ITarget.GetType() != 0)
				CheckDamage /= 10;

			if (ITarget.IsBuff(BuffNames::Blessing) && CheckDamage > 10 && ITarget.GetType() == 0)
				CheckDamage *= (BlessPVP / 100);
			if (ITarget.IsBuff(BuffNames::Blessing) && CheckDamage > 10 && ITarget.GetType() != 0)
				CheckDamage = 0;
		}

		if (ITarget.GetType() == 0)
		{
			if (ITarget.IsBuff(283) && CheckDamage > 10)
				CheckDamage = ((CheckDamage * 6) / 10);
		}

		if (CheckDamage > 100 && ITarget.IsBuff(342))
			CheckDamage += (CheckDamage / 20);

		if (ITarget.GetType() == 0)
		{
			if (ITarget.IsBuff(122) && CheckDamage)
				CheckDamage = ((CheckDamage * 88) / 100);
		}

		if (ITarget.GetType() == 0)
		{
			if (*(DWORD*)((int)ITarget.GetOffset() + 292) & 2147483648)
				return 0;
		}

		if (ITarget.GetType() == 0 && ITarget.GetClass() == 0 && CheckDamage > 0 && ITarget.GetSpecialty() == 23)
		{
			int DefendChance = 135;

			if (ITarget.GetLevel() < 100)
				DefendChance = (((ITarget.GetLevel() - 69) * 7) / 2) + 25;

			if ((int)CTools::Rate(1, 1000) <= DefendChance)
			{
				ITarget.SystemMessage("[Weapon Defend] You blocked enemy's attack.", TEXTCOLOR_RED);
				ITarget._ShowBattleAnimation(ITarget, 37);
				return 0;
			}
		}

		if (ITarget.GetType() == 0 && ITarget.GetClass() == 0)
		{
			if ((ITarget.GetSpecialty() == 43 || ITarget.GetSpecialty() == 11) && CheckDamage >= 100 && ITarget.GetLevel() >= 50)
			{
				int pSkill = ITarget.GetSkillPointer(44);

				if (pSkill)
				{
					ISkill xSkill((void*)pSkill);
					int DevineSuction = xSkill.GetGrade();

					if (CTools::Rate(1, 1000) <= (1000 - (DevineSuction * 180)))
					{
						int RealDamage = CheckDamage;
						CheckDamage = ((CheckDamage * (100 - (DevineSuction * 6))) / 100);
						int AbsorbedDamage = RealDamage - CheckDamage;
						std::string msg = "[Devine Suction] You absorbed " + Int2String(AbsorbedDamage) + " damage from enemy's attack.";
						ITarget.SystemMessage(msg, TEXTCOLOR_RED);
					}
				}
			}
		}

		if (ITarget.GetType() == 0 && ITarget.GetClass() == 3)
		{
			if (ITarget.GetSpecialty() >= 3 && CheckDamage >= 100)
			{
				int pSkill = ITarget.GetSkillPointer(25);

				if (pSkill)
				{
					ISkill xSkill((void*)pSkill);
					int AcroGrade = xSkill.GetGrade();

					if ((int)CTools::Rate(1, 100) <= ((AcroGrade * 2) + 3))
					{
						CheckDamage = CheckDamage * 9 / 10;
						ITarget.SystemMessage("[Acrobatic] Damage reduces by %10.", TEXTCOLOR_RED);
					}
				}
			}

			if (ITarget.GetSpecialty() == 43 && CheckDamage >= 100)
			{
				int pSkill = ITarget.GetSkillPointer(26);

				if (pSkill)
				{
					ISkill xSkill((void*)pSkill);
					int AcroGrade = xSkill.GetGrade();

					if ((int)CTools::Rate(1, 100) <= 7)
					{
						CheckDamage = CheckDamage * 3 / 4;
						ITarget.SystemMessage("[High Grade Acrobatic] Damage reduces by %25.", TEXTCOLOR_RED);
					}
				}
			}
		}

		if (ITarget.GetType() == 0 && ITarget.GetClass() == 1 && CheckDamage >= 100)
		{
			int pSkill = ITarget.GetSkillPointer(76);

			if (pSkill)
			{
				if (!ITarget.GetProperty(PlayerProperty::FarContinueSkillPlayerSkillID) && ITarget.IsBuff(309))
				{
					ISkill xSkill((void*)pSkill);
					ITarget.SetContinueSkill();
					ITarget.SetProperty(PlayerProperty::FarContinueSkillPlayerTarget, (int)IPlayer.GetOffset());
					ITarget.SetProperty(PlayerProperty::FarContinueSkillPlayerSkillID, 76);
					ITarget.SetProperty(PlayerProperty::FarContinueSkillPlayerSkillCount, xSkill.GetGrade());
					ITarget.SetProperty(PlayerProperty::FarContinueSkillPlayerDamage, CheckDamage);
					ITarget.SetProperty(PlayerProperty::FarContinueSkillPlayerSkillDelay, 0);
				}
			}
		}

		if (ITarget.GetType() == 0 && ITarget.GetClass() == 3 && CheckDamage)
		{
			if (ITarget.IsBuff(337) && GetTickCount() >= IPlayer.GetBuffValue(BuffNames::CODelay))
			{
				/* Counter Offensive New Calculation Start */
				int pSkill = ITarget.GetSkillPointer(63);

				if (pSkill && CTools::Rate(1, 1000) >= 650)
				{
					ISkill xSkill((void*)pSkill);
					int nSkillGrade = xSkill.GetGrade();

					int Around = IPlayer.GetObjectListAround(3);

					while (Around)
					{
						IChar Object((void*)*(DWORD*)Around);

						int nDmg = CheckDamage + (nSkillGrade * CTools::Rate(TCOMin, TCOMax));
						/*if (ITarget.GetLevel() >= 70)
							nDmg += ((ITarget.GetLevel() - 69) * 250);	//Counter Offensive Damage Changed 250
							*/
						int nPVPDamage = (nDmg * TCOReduce) / 100;

						if (Object.IsValid() && ITarget.IsValid() && (*(int(__thiscall **)(int, int, DWORD))(*(DWORD *)ITarget.GetOffset() + 176))((int)ITarget.GetOffset(), (int)Object.GetOffset(), 0))
							ITarget.OktayDamageNoAgro(Object, Object.GetType() == 0 ? nPVPDamage : nDmg, 63);

						Around = CBaseList::Pop((void*)Around);
					}

					IPlayer.UpdateBuff(BuffNames::CODelay, BuffNames::BuffTime, GetTickCount() + 1500);
					ITarget._ShowBattleAnimation(IPlayer, 63);
				}
			}

			if (ITarget.IsBuff(335))
			{
				int pSkill = ITarget.GetSkillPointer(20);

				if (pSkill && CTools::Rate(1, 1000) >= 650)
				{
					if (IPlayer.GetCurHp() > 1)
					{
						ISkill xSkill((void*)pSkill);
						int nSkillGrade = xSkill.GetGrade();
						int nDmg = CheckDamage + (nSkillGrade * CTools::Rate(TCAMin, TCAMax));

						if (IPlayer.GetType() == 0)
							nDmg = (nDmg * TCAReduce) / 100;

						ITarget.OktayDamageNoAgro(IPlayer, nDmg, 20);
						ITarget._ShowBattleAnimation(IPlayer, 20);
					}
				}
			}
		}

		if (DuelTournament::Active) {
			if (CheckDamage && IPlayer.GetType() == 0 && ITarget.GetType() == 0 && IPlayer.IsBuff(373) && ITarget.IsBuff(374))
				IPlayer.UpdateBuff(373, BuffNames::BuffTime, IPlayer.GetBuffValue(373) + CheckDamage);

			if (CheckDamage && IPlayer.GetType() == 0 && IPlayer.IsBuff(374) && ITarget.GetType() == 0 && ITarget.IsBuff(373))
				IPlayer.UpdateBuff(374, BuffNames::BuffTime, IPlayer.GetBuffValue(374) + CheckDamage);
		}

		if (IPlayer.GetType() == 0 && ITarget.GetType() == 0 && WorldCup::Active && ((IPlayer.IsBuff(902) && ITarget.IsBuff(903)) || (IPlayer.IsBuff(903) && ITarget.IsBuff(902)))) {
			WCDamage[IPlayer.GetPID()] += CheckDamage;
			WCDamage[ITarget.GetPID()] -= CheckDamage;
		}


		if (CheckDamage > ConfigPVPMaxDmg && IPlayer.GetType() == 0 && ITarget.GetType() == 0 && IPlayer.GetAdmin() == 0 && ITarget.GetAdmin() == 0)
			CheckDamage = ConfigPVPMaxDmg;

		if (IPlayer.GetType() == 0 && CheckDamage && CheckDamage < ITarget.GetCurHp()) {
			int SoulPocket = IPlayer.GetBuffValue(BuffNames::SoulPocketAmount);
			if (SoulPocket) {
				double mul = 1.5;
				int Index = IPlayer.GetBuffValue(BuffNames::SoulPIndex);
				if (Index) {
					if (SoulPocketEffect.count(Index))
						mul = 1 + ((double)SoulPocketEffect.find(Index)->second / 100);
				}
				CheckDamage *= mul;
				updateSoulPocket(IPlayer, SoulPocket);
			}
		}

		if (Restri && Restrictions.count(IPlayer.GetPID()) && Restrictions.find(IPlayer.GetPID())->second.Attack == 0)
			return 0;

		if (CaptureFlag::Active && CaptureFlag::CurrentCapturers &&  IPlayer.GetType() == 1 && IPlayer.GetMobIndex() == CPMob && ITarget.GetType() == 0 && ITarget.IsBuff(CaptureFlag::CurrentCapturers))
			return 0;

		if (CaptureFlag::Active && CaptureFlag::CurrentCapturers &&  ITarget.GetType() == 1 && ITarget.GetMobIndex() == CPMob && IPlayer.GetType() == 0 && IPlayer.IsBuff(CaptureFlag::CurrentCapturers))
			return 0;

		if (ITarget.GetType() == 0 && CheckDamage > ITarget.GetCurHp() && ITarget.IsBuff(349) && ITarget.GetMap() != BanditsMap)
			ITarget.DisableRiding();

		if (IPlayer.IsValid() && IPlayer.GetType() == 1 && MonsterSkills.count(IPlayer.GetMobIndex()) && !IPlayer.GetBuffValue(4999)) {
			std::vector<int> Skills = MonsterSkills.find(IPlayer.GetMobIndex())->second;
			srand(time(0));
			std::random_shuffle(Skills.begin(), Skills.end());
			IPlayer.UpdateBuff(4999, BuffNames::BuffTime, 1);
			for (int i = 0; i < Skills.size(); i++) {
				int Skill = Skills[i];
				if (MSkills.count(Skill) && IPlayer.GetBuffValue(5000 + Skill) < GetTickCount()) {
					MSkill mSkill = MSkills.find(Skill)->second;
					if (mSkill.AOERange) {
						int Around = IPlayer.GetPlayerListAround(mSkill.AOERange);
						while (Around)
						{
							IChar Object((void*)CBaseList::Offset((void*)Around));
							ExecuteMonsterSkill(IPlayer, Object, mSkill);
							Around = CBaseList::Pop((void*)Around);
						}
					}
					else
						ExecuteMonsterSkill(IPlayer, ITarget, mSkill);

					if (mSkill.EffectType)
						IPlayer.AddFxToTarget(mSkill.Effect, 0, 0, 0);
					IPlayer.UpdateBuff(5000 + Skill, BuffNames::BuffTime, GetTickCount() + mSkill.Cooldown);
					break;
				}
			}
			IPlayer.UpdateBuff(4999, BuffNames::BuffTime, 0);
		}

		if (IPlayer.GetType() == 0) {
			if (ITarget.GetType() == 0) {
				int PVPPimp = IPlayer.GetBuffValue(BuffNames::PVPPimp);
				if (PVPPimp)
					CheckDamage += ((CheckDamage*PVPPimp) / 100);
			}
			else {
				int PVEPimp = IPlayer.GetBuffValue(BuffNames::PVEPimp);
				if (PVEPimp)
					CheckDamage += ((CheckDamage*PVEPimp) / 100);
			}

			if (IPlayer.GetAdmin() <= 3)
			{
				if (CheckDamage >= ConfigMaxDamage)
					CheckDamage = ConfigMaxDamage;

				if (IPlayer.GetMinMagAttack() >= ConfigMaxMagAtk || IPlayer.GetMinMagAttack() <= 0)
					return 0;

				if (IPlayer.GetMaxMagAttack() >= ConfigMaxMagAtk || IPlayer.GetMaxMagAttack() <= 0)
					return 0;

				if (IPlayer.GetMaxPhyAttack() >= ConfigMaxPhyAtk || IPlayer.GetMaxPhyAttack() <= 0)
					return 0;

				if (IPlayer.GetMinPhyAttack() >= ConfigMaxPhyAtk || IPlayer.GetMinPhyAttack() <= 0)
					return 0;
			}
		}

		if (OBActive && IPlayer.GetType() == 0 && !IPlayer.IsBuff(BuffNames::NecklaceCD)) {
			if ((!OBPVPEnable && ITarget.GetType() == 1) || OBPVPEnable) {
				int Necklace = IPlayer.GetBuffValue(BuffNames::Necklace);
				if (Necklace && NecklaceBuffs.count(Necklace)) {
					NecklaceBuff bNecklace = NecklaceBuffs.find(Necklace)->second;
					IPlayer.Buff(BuffNames::OrnamentDmg, bNecklace.Duration, bNecklace.Dmg);
					IPlayer.Buff(BuffNames::CritChance, bNecklace.Duration, bNecklace.CritChance);
					IPlayer.Buff(BuffNames::NecklaceCD, bNecklace.Cooldown + bNecklace.Duration, 0);
					IPlayer.AddFxToBone(bNecklace.Effect, 0);
				}
			}
		}

		int nDmg = IPlayer.GetBuffValue(BuffNames::OrnamentDmg);

		if (nDmg)
			CheckDamage += nDmg;

		if (Immortal::Active && ITarget.GetType() == 0) {
			if ((IPlayer.GetType() == 0 && ImmortalPVP) || IPlayer.GetType() == 1)
				CheckDamage -= ((CheckDamage * ImmortalEffect) / 100);
		}

		if (PVPLvLDiffDmg && ITarget.GetType() == 0 && IPlayer.GetType() == 0) {
			int LvlDiff = ITarget.GetLevel() - IPlayer.GetLevel();
			if (LvlDiff > 0) {
				int Reduce = ((CheckDamage * LvlDiff) / 100) + (LvlDiff * PVPLvLDiffDmg);
				if (Reduce > CheckDamage)
					Reduce = CheckDamage;
				CheckDamage -= Reduce;
			}
		}

		if (IPlayer.GetType() == 0 && ITarget.GetType() == 1) {
			if (UnAggro.count(ITarget.GetMobIndex()))
				IPlayer.SetProperty(PlayerProperty::DamageAggro, CheckDamage);
		}

	}

	return CheckDamage;
}
