void __fastcall PerfectDefense(IChar IPlayer)
{
	int pSkill = IPlayer.GetSkillPointer(40);

	if (IPlayer.IsValid() && pSkill)
	{
		ISkill xSkill((void*)pSkill);
		int nMana = (int)(IPlayer.GetLevel() * 4 + 20) + (((IPlayer.GetLevel() * 4 + 20) * xSkill.GetGrade()) / 10);

		if (IPlayer.IsBuff(282))
			return;

		if (IPlayer.GetCurMp() <= nMana)
			return;
		else
			IPlayer.DecreaseMana(nMana);

		if (IPlayer.IsValid() && IPlayer.IsParty())
		{
			void *Party = (void*)CParty::FindParty(IPlayer.GetPartyID());

			if (Party)
			{
				for (int i = CParty::GetPlayerList(Party); i; i = CBaseList::Pop((void*)i))
				{
					int Members = *(DWORD*)((void*)i);
					IChar IMembers((void*)*(DWORD*)((void*)i));

					if (IMembers.IsValid() && IPlayer.IsValid())
					{
						if (CChar::GetRange((int)IPlayer.GetOffset() + 332, Members + 332) <= 300 && !IMembers.IsBuff(282) && !IMembers.IsBuff(283))
						{
							IMembers.SendGStateEx(IMembers.GetGStateEx() + 1);
							IMembers.SetBuffIcon((10 + (xSkill.GetGrade() * PDMul)) * 1000, 0, 1795, 200);
							IMembers.Buff(282, 9 + (xSkill.GetGrade() * PDMul), 0);
							IMembers.Buff(283, 15 + (xSkill.GetGrade() * PDMul), 0);

							if (IPlayer.GetOffset() == IMembers.GetOffset())
								IPlayer.Buff(284, 15 + (xSkill.GetGrade() * PDMul), 0);
						}
					}
				}
				CIOObject::Release(Party);
			}
		}
		else {
			if (IPlayer.IsValid() && !IPlayer.IsBuff(282) && !IPlayer.IsBuff(283))
			{
				IPlayer.SendGStateEx(IPlayer.GetGStateEx() + 1);
				IPlayer.SetBuffIcon((10 + (xSkill.GetGrade() * PDMul)) * 1000, 0, 1795, 200);
				IPlayer.Buff(282, 9 + (xSkill.GetGrade() * PDMul), 0);
				IPlayer.Buff(283, 15 + (xSkill.GetGrade() * PDMul), 0);
				IPlayer.Buff(284, 15 + (xSkill.GetGrade() * PDMul), 0);
			}
		}

		IPlayer._ShowBattleAnimation(IPlayer, 40);
	}
}
void __fastcall PowerfulWideningWound(IChar IPlayer, int pPacket, int pPos)
{
	int pSkill = IPlayer.GetSkillPointer(41);

	if (IPlayer.IsValid() && pSkill)
	{
		ISkill xSkill((void*)pSkill);
		int nTargetID = 0; char bType = 0; void *pTarget = 0;
		CPacket::Read((char*)pPacket, (char*)pPos, "bd", &bType, &nTargetID);
		int nMana = xSkill.GetGrade() + 30;

		TargetFind myTarget(bType, 0, nTargetID);
		pTarget = myTarget.getTarget();

		if (bType >= 2)
			return;

		if (pTarget && xSkill.GetGrade() && IPlayer.IsValid())
		{
			IChar Target(pTarget);

			if (IPlayer.GetCurMp() < nMana) {

				return;
			}

			if (pTarget == IPlayer.GetOffset()) {

				return;
			}

			if (IPlayer.IsValid() && Target.IsValid())
			{
				if (!IPlayer.IsInRange(Target, 300)) {

					return;
				}

				if (IPlayer.CheckHit(Target, 10 + ((IPlayer.GetLevel() / 20) + xSkill.GetGrade() * 3)))
				{
					int nDmg = (320 + (196 * xSkill.GetGrade())) + (IPlayer.GetAttack() * KPWWMul) + (xSkill.GetGrade() * CTools::Rate(KPWWMin, KPWWMax));

					if (Target.GetType() == 0)
						nDmg = nDmg * KPWWReduce / 100;

					if (Target.GetType() == 1)
						IPlayer.SetProperty(PlayerProperty::DamageAggro, nDmg*1.2);

					IPlayer.OktayDamageSingle(Target, nDmg, 41);
				}
				else {
					IPlayer._ShowBattleMiss(Target, 41);
				}

				IPlayer.SetDirection(Target);
				IPlayer.DecreaseMana(nMana);
			}
		}

	}
}
void __fastcall ProvocationOfBlow(IChar IPlayer, int pPacket, int pPos)
{
	int pSkill = IPlayer.GetSkillPointer(42);

	if (IPlayer.IsValid() && pSkill)
	{
		ISkill xSkill((void*)pSkill);
		int nSkillGrade = xSkill.GetGrade();
		int nTargetID = 0, nMana = 0; char bType = 0; void *pTarget = 0;
		CPacket::Read((char*)pPacket, (char*)pPos, "bd", &bType, &nTargetID);

		if (bType >= 2)
			return;

		TargetFind myTarget(bType, 0, nTargetID);
		pTarget = myTarget.getTarget();

		if (pTarget && nSkillGrade && IPlayer.IsValid())
		{
			if (nSkillGrade <= 1)
				nMana = 220;
			else if (nSkillGrade == 2)
				nMana = 242;
			else if (nSkillGrade == 3)
				nMana = 266;
			else if (nSkillGrade == 4)
				nMana = 292;
			else if (nSkillGrade >= 5)
				nMana = 320;

			if (IPlayer.IsOnline() && CPlayer::IsWState((int)IPlayer.GetOffset(), 12)) {

				return;
			}

			if (IPlayer.GetCurMp() < nMana) {

				return;
			}

			if (pTarget == IPlayer.GetOffset()) {

				return;
			}

			if (pTarget && IPlayer.IsOnline())
			{
				IChar Target(pTarget);

				if (!IPlayer.IsInRange(Target, 300)) {

					return;
				}

				int Around = IPlayer.GetObjectListAround(KPOBRange);

				while (Around)
				{
					IChar Object((void*)CBaseList::Offset((void*)Around));

					if (Object.IsValid() && IPlayer.IsValid() && (*(int(__thiscall **)(int, int, DWORD))(*(DWORD *)IPlayer.GetOffset() + 176))((int)IPlayer.GetOffset(), (int)Object.GetOffset(), 0))
					{
						int nDmg = (IPlayer.GetAttack() * KPOBMul) + (nSkillGrade * CTools::Rate(KPOBMin, KPOBMax));

						if (Object.GetType() == 0)
							nDmg = nDmg * KPOBReduce / 100;

						IPlayer.SetProperty(PlayerProperty::DamageAggro, nDmg * 9);

						IPlayer.OktayDamageArea(Object, nDmg, 42);
					}

					Around = CBaseList::Pop((void*)Around);
				}

				IPlayer._ShowBattleAnimation(Target, 42);
				IPlayer.SetDirection(Target);
				IPlayer.DecreaseMana(nMana);
			}
		}

	}
}
void __fastcall ShoutOfDefense(IChar IPlayer)
{
	if (IPlayer.IsBuff(380))
		return;

	if (IPlayer.IsValid())
	{
		int pSkill = IPlayer.GetSkillPointer(90);
		int Mana = (20 + IPlayer.GetLevel()) + ((20 + (IPlayer.GetLevel() * 4)) / 10);

		if (IPlayer.GetCurMp() <= Mana)
			return;

		if (pSkill && IPlayer.IsValid() && !IPlayer.IsBuff(380))
		{
			IPlayer.DecreaseMana(Mana);
			ISkill xSkill((void*)pSkill);
			IPlayer.Buff(379, 25, 0);
			IPlayer.Buff(380, 3600, 0);
			IPlayer._ShowBattleAnimation(IPlayer, 90);
			IPlayer.SetBuffIcon(25000, 0, 4240, 948);
			IPlayer.AddDef(50 + (xSkill.GetGrade() * 50));
		}
	}
}
void __fastcall ShoutOfFightingSpirit(IChar IPlayer)
{
	if (IPlayer.IsOnline())
	{
		int pSkill = IPlayer.GetSkillPointer(92);

		if (IPlayer.IsValid() && pSkill)
		{
			ISkill xSkill((void*)pSkill);
			int Mana = 180 + (1.25 * (xSkill.GetGrade() * (IPlayer.GetLevel() + xSkill.GetGrade())));

			if (IPlayer.GetCurMp() <= Mana)
				return;

			IPlayer.DecreaseMana(Mana);
			IPlayer._ShowBattleAnimation(IPlayer, 92);

			if (IPlayer.IsValid())
			{
				if (IPlayer.IsParty())
				{
					void *Party = (void *)CParty::FindParty(IPlayer.GetPartyID());

					if (Party)
					{
						for (int i = CParty::GetPlayerList(Party); i; i = CBaseList::Pop((void*)i))
						{
							int Members = *(DWORD*)((void*)i);
							IChar IMembers((void*)*(DWORD*)((void*)i));

							if (CChar::IsNormal(Members) && IPlayer.IsValid())
							{
								if (CChar::GetRange((int)IPlayer.GetOffset() + 332, Members + 332) <= 300 && !IMembers.GetBuffValue(BuffNames::SOFSTime))
								{
									IMembers.SetBuffIcon(1000 * (4 + (xSkill.GetGrade() * 3)), 0, 4243, 951);
									IMembers.AddMaxAttack(xSkill.GetGrade()*SOFSMAX);
									IMembers.AddMinAttack(xSkill.GetGrade()*SOFSMIN);
									IMembers.UpdateBuff(BuffNames::SOFSType, BuffNames::BuffTime, xSkill.GetGrade());
									IMembers.UpdateBuff(BuffNames::SOFSTime, BuffNames::BuffTime, GetTickCount() + (1000 * (4 + (xSkill.GetGrade() * 3))));

								}
							}
						}
						CIOObject::Release(Party);
					}
				}
				else {
					if (!IPlayer.GetBuffValue(BuffNames::SOFSTime))
					{
						IPlayer.SetBuffIcon(1000 * (4 + (xSkill.GetGrade() * 3)), 0, 4243, 951);
						IPlayer.AddMaxAttack(xSkill.GetGrade()*SOFSMAX);
						IPlayer.AddMinAttack(xSkill.GetGrade()*SOFSMIN);
						IPlayer.UpdateBuff(BuffNames::SOFSType, BuffNames::BuffTime, xSkill.GetGrade());
						IPlayer.UpdateBuff(BuffNames::SOFSTime, BuffNames::BuffTime, GetTickCount() + (1000 * (4 + (xSkill.GetGrade() * 3))));
					}
				}
			}
		}
	}
}
void __fastcall SpinSlash(IChar IPlayer)
{
	int pSkill = IPlayer.GetSkillPointer(38);

	if (IPlayer.IsValid() && pSkill)
	{
		ISkill xSkill((void*)pSkill);
		int nMana = (xSkill.GetGrade() == 1) ? 209 : (200 + (xSkill.GetGrade() * 20));

		if (IPlayer.GetCurMp() < nMana)
			return;

		if (IPlayer.IsValid() && CPlayer::IsWState((int)IPlayer.GetOffset(), 12))
		{
			int Around = IPlayer.GetObjectListAround(SpinSlashRange);

			while (Around)
			{
				IChar Object((void*)CBaseList::Offset((void*)Around));

				if (Object.IsValid() && IPlayer.IsValid() && (*(int(__thiscall **)(int, int, DWORD))(*(DWORD *)IPlayer.GetOffset() + 176))((int)IPlayer.GetOffset(), (int)Object.GetOffset(), 0))
				{
					int nDmg = (IPlayer.GetAttack() * KSSMul) + (xSkill.GetGrade() * CTools::Rate(KSSMin, KSSMax));

					if (Object.GetType() == 0)
						nDmg = (nDmg * KSSReduce) / 100;

					IPlayer.OktayDamageArea(Object, nDmg, 38);
				}

				Around = CBaseList::Pop((void*)Around);
			}

			IPlayer._ShowBattleAnimation(IPlayer, 38);
			IPlayer.RemoveDeathBlow(IPlayer.GetDeathBlow());
			IPlayer.DecreaseMana(nMana);
		}
	}
}
void __fastcall ContinueSwordDance(IChar IPlayer)
{
	if (IPlayer.IsValid())
	{
		int nSkillGrade = IPlayer.GetProperty(PlayerProperty::ContinueSkillPlayerSkillGrade);
		void *pTarget = (void*)IPlayer.GetProperty(PlayerProperty::ContinueSkillPlayerTarget);

		if (nSkillGrade && pTarget && IPlayer.IsValid())
		{
			if (IPlayer.GetProperty(PlayerProperty::ContinueSkillPlayerSkillCount))
			{
				IChar Target(pTarget);

				if (IPlayer.IsValid() && Target.IsValid())
				{
					int Count = IPlayer.GetProperty(PlayerProperty::ContinueSkillPlayerSkillCount);
					IPlayer.SetProperty(PlayerProperty::ContinueSkillPlayerSkillCount, Count - 1);

					if (!IPlayer.IsValid())
					{
						ResetContinueSkill(IPlayer);
						return;
					}

					if (IPlayer.IsOnline() && !CPlayer::IsWState((int)IPlayer.GetOffset(), 12))
					{
						ResetContinueSkill(IPlayer);
						return;
					}

					if (IPlayer.IsOnline() && !IPlayer.IsInRange(Target, 2))
					{
						ResetContinueSkill(IPlayer);
						return;
					}

					if (IPlayer.CheckHit(Target, 30))
					{
						int nDmg = (IPlayer.GetAttack() * KSDMul) + (nSkillGrade * CTools::Rate(KSDMin, KSDMax));

						if (Target.GetType() == 0)
							nDmg = nDmg * KSDReduce / 100;

						IPlayer.OktayDamageSingle(Target, nDmg, 43);

						if (IPlayer.IsOnline())
							IPlayer.SetProperty(PlayerProperty::ContinueSkillPlayerSkillDelay, GetTickCount() + 800);

						if (IPlayer.IsOnline() && Count == 1)
							ResetContinueSkill(IPlayer);

						return;
					}
					else {
						if (IPlayer.IsOnline())
							IPlayer.SetProperty(PlayerProperty::ContinueSkillPlayerSkillDelay, GetTickCount() + 800);

						IPlayer._ShowBattleMiss(Target, 43);

						if (IPlayer.IsOnline() && IPlayer.GetProperty(PlayerProperty::ContinueSkillPlayerSkillCount) == 0)
							ResetContinueSkill(IPlayer);

						return;
					}
				}
			}
		}
	}

	ResetContinueSkill(IPlayer);
	return;
}

void __fastcall SwordDance(IChar IPlayer, int pPacket, int pPos)
{
	int pSkill = IPlayer.GetSkillPointer(43);

	if (IPlayer.IsValid() && pSkill)
	{
		ISkill xSkill((void*)pSkill);
		int nTargetID = 0, nMana = 0, nSkillGrade = 0; char bType = 0; void *pTarget = 0;
		nSkillGrade = xSkill.GetGrade();
		CPacket::Read((char*)pPacket, (char*)pPos, "bd", &bType, &nTargetID);

		if (nSkillGrade <= 1)
			nMana = 245;
		else if (nSkillGrade == 2)
			nMana = 283;
		else if (nSkillGrade == 3)
			nMana = 325;
		else if (nSkillGrade == 4)
			nMana = 371;
		else if (nSkillGrade >= 5)
			nMana = 420;

		TargetFind myTarget(bType, 0, nTargetID);
		pTarget = myTarget.getTarget();

		if (bType >= 2)
			return;

		if (pTarget && nSkillGrade && IPlayer.IsValid())
		{
			IChar Target(pTarget);

			if (IPlayer.GetCurMp() < nMana) {

				return;
			}

			if (pTarget == IPlayer.GetOffset()) {

				return;
			}

			if (IPlayer.IsValid() && Target.IsValid())
			{
				IPlayer.DecreaseMana(nMana);


				if (!IPlayer.GetProperty(PlayerProperty::ContinueSkillPlayerSkillID))
					IPlayer.SetContinueSkill();

				IPlayer.SetProperty(PlayerProperty::ContinueSkillPlayerSkillID, 43);
				IPlayer.SetProperty(PlayerProperty::ContinueSkillPlayerTarget, (int)Target.GetOffset());
				IPlayer.SetProperty(PlayerProperty::ContinueSkillPlayerSkillGrade, xSkill.GetGrade());
				IPlayer.SetProperty(PlayerProperty::ContinueSkillPlayerSkillCount, xSkill.GetGrade() + 1);
				IPlayer.SetProperty(PlayerProperty::ContinueSkillPlayerSkillDelay, 0);
			}
		}

	}
}
void __fastcall TheBoomOfEarth(IChar IPlayer)
{
	if (IPlayer.IsOnline())
	{
		int pSkill = IPlayer.GetSkillPointer(91);

		if (pSkill && IPlayer.IsValid())
		{
			if (CPlayer::IsWState((int)IPlayer.GetOffset(), 12))
				return;

			ISkill xSkill((void*)pSkill);
			int Mana = 200 + (xSkill.GetGrade() * (20 + (xSkill.GetGrade() - 1)));

			if (IPlayer.GetCurMp() <= Mana)
				return;

			IPlayer.DecreaseMana(Mana);
			IPlayer._ShowBattleAnimation(IPlayer, 91);

			if (IPlayer.IsValid())
			{
				int Around = IPlayer.GetObjectListAround(3);

				while (Around)
				{
					IChar Object((void*)CBaseList::Offset((void*)Around));

					if (Object.IsValid() && IPlayer.IsValid() && Object.GetOffset() != IPlayer.GetOffset() && (*(int(__thiscall **)(int, int, DWORD))(*(DWORD *)IPlayer.GetOffset() + 176))((int)IPlayer.GetOffset(), (int)Object.GetOffset(), 0))
						Object.Buff(7, 2 * xSkill.GetGrade(), 0);

					Around = CBaseList::Pop((void*)Around);
				}
			}
		}
	}
}
void __fastcall TheWaveOfEarth(IChar IPlayer)
{
	if (IPlayer.IsOnline())
	{
		int pSkill = IPlayer.GetSkillPointer(93);

		if (IPlayer.IsValid() && pSkill)
		{
			if (CPlayer::IsWState((int)IPlayer.GetOffset(), 12))
				return;

			ISkill xSkill((void*)pSkill);
			int Mana = 180 + (1.25 * (xSkill.GetGrade() * (IPlayer.GetLevel() + xSkill.GetGrade())));

			if (IPlayer.GetCurMp() <= Mana)
				return;

			IPlayer.DecreaseMana(Mana);
			IPlayer._ShowBattleAnimation(IPlayer, 93);

			if (IPlayer.IsValid())
			{
				int Around = IPlayer.GetObjectListAround(3);

				while (Around)
				{
					IChar Object((void*)CBaseList::Offset((void*)Around));

					if (Object.IsValid() && IPlayer.IsValid() && (*(int(__thiscall **)(int, int, DWORD))(*(DWORD *)IPlayer.GetOffset() + 176))((int)IPlayer.GetOffset(), (int)Object.GetOffset(), 0))
					{
						int nDmg = (IPlayer.GetAttack() * NWOEMul) + (xSkill.GetGrade() * CTools::Rate(NWOEMin, NWOEMax));

						if (Object.GetType() == 0)
							nDmg = nDmg * NWOEReduce / 100;

						IPlayer.OktayDamageArea(Object, nDmg, 93);
					}

					Around = CBaseList::Pop((void*)Around);
				}
			}
		}
	}
}