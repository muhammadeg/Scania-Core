void __fastcall ContinueRupture(IChar IPlayer)
{
	if (IPlayer.IsValid())
	{
		int TargetAOE = 0;
		if (RupAOE && RupPVPAoe)
			TargetAOE = 3;
		else if (RupPVPAoe)
			TargetAOE = 2;
		else if (RupAOE)
			TargetAOE = 1;

		int nSkillGrade = IPlayer.GetProperty(PlayerProperty::RuptureContinueSkillPlayerSkillGrade);
		void *pTarget = (void*)IPlayer.GetProperty(PlayerProperty::RuptureContinueSkillPlayerTarget);

		if (nSkillGrade && IPlayer.GetProperty(PlayerProperty::RuptureContinueSkillPlayerSkillCount))
		{
			int Count = IPlayer.GetProperty(PlayerProperty::RuptureContinueSkillPlayerSkillCount);
			IPlayer.SetProperty(PlayerProperty::RuptureContinueSkillPlayerSkillCount, Count - 1);

			IChar Target(pTarget);
			if (RupAOE && (TargetAOE == 3 || (TargetAOE && !Target.IsValid()) || (TargetAOE == 2 && Target.GetType() == 0) || (TargetAOE == 1 && Target.GetType() == 1))) {
				int Around = IPlayer.GetObjectListAround(RupAOE);
				while (Around)
				{
					IChar Object((void*)CBaseList::Offset((void*)Around));
					if (Object.IsValid() && IPlayer.IsValid() && (*(int(__thiscall **)(int, int, DWORD))(*(DWORD *)IPlayer.GetOffset() + 176))((int)IPlayer.GetOffset(), (int)Object.GetOffset(), 0) && (TargetAOE == 3 || (TargetAOE == 2 && Object.GetType() == 0) || (TargetAOE == 1 && Object.GetType() == 1))) {
						int nDmg = (IPlayer.GetAttack() * TRupMul) + (nSkillGrade * CTools::Rate(TRupMin, TRupMax));

						if (Object.GetType() == 0)
							nDmg = nDmg * TRupReduce / 100;

						IPlayer.OktayDamageArea(Object, nDmg, 17);
					}
					Around = CBaseList::Pop((void*)Around);
				}
			}
			else {
				if (!Target.IsValid() || !IPlayer.IsValid())
				{
					ResetRuptureContinueSkill(IPlayer);
					return;
				}

				if (CChar::GetRange((int)IPlayer.GetOffset() + 332, (int)pTarget + 332) > 300)
				{
					ResetRuptureContinueSkill(IPlayer);
					return;
				}

				if ((*(int(__thiscall **)(int, int, DWORD))(*(DWORD *)IPlayer.GetOffset() + 176))((int)IPlayer.GetOffset(), (int)Target.GetOffset(), 0)) {
					int nDmg = (IPlayer.GetAttack() * TRupMul) + (nSkillGrade * CTools::Rate(TRupMin, TRupMax));

					if (Target.GetType() == 0)
						nDmg = nDmg * TRupReduce / 100;

					IPlayer.OktayDamageArea(Target, nDmg, 17);
				}
			}

			if (IPlayer.IsOnline())
				IPlayer.SetProperty(PlayerProperty::RuptureContinueSkillPlayerSkillDelay, GetTickCount() + 2000);

			if (pTarget && !Target.IsValid())
				IPlayer.SetProperty(PlayerProperty::RuptureContinueSkillPlayerTarget, 0);

			if (IPlayer.IsOnline() && IPlayer.GetProperty(PlayerProperty::RuptureContinueSkillPlayerSkillCount) == 0)
				ResetRuptureContinueSkill(IPlayer);

			return;
		}
	}

	ResetRuptureContinueSkill(IPlayer);
	return;
}

void __fastcall Rupture(IChar IPlayer, int pPacket, int pPos)
{
	int pSkill = IPlayer.GetSkillPointer(17);

	if (IPlayer.IsValid() && pSkill)
	{
		ISkill xSkill((void*)pSkill);
		int nSkillGrade = xSkill.GetGrade();
		int nTargetID = 0; char bType = 0; void *pTarget = 0;
		CPacket::Read((char*)pPacket, (char*)pPos, "bd", &bType, &nTargetID);
		int nMana = (int)(30 * nSkillGrade + 35);

		TargetFind myTarget(bType, 0, nTargetID);
		pTarget = myTarget.getTarget();

		if (bType >= 2)
			return;

		if (pTarget && IPlayer.IsValid() && nSkillGrade)
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

				if (IPlayer.CheckHit(Target, 10))
				{
					if (!IPlayer.GetProperty(PlayerProperty::RuptureContinueSkillPlayerSkillID))
						IPlayer.SetContinueSkill();

					IPlayer.Buff(353,20,0);
					
					if (!Target.IsBuff(350))
						Target._SendGStateEx(Target._GetGStateEx() + 65536);

					Target.Buff(350, 18, 0);
					IPlayer.SetProperty(PlayerProperty::RuptureContinueSkillPlayerTarget, (int)Target.GetOffset());
					IPlayer.SetProperty(PlayerProperty::RuptureContinueSkillPlayerSkillID, 17);
					IPlayer.SetProperty(PlayerProperty::RuptureContinueSkillPlayerSkillCount, 9);
					IPlayer.SetProperty(PlayerProperty::RuptureContinueSkillPlayerSkillDelay, GetTickCount() + 1000);
					IPlayer.SetProperty(PlayerProperty::RuptureContinueSkillPlayerSkillGrade, nSkillGrade);
					IPlayer._ShowBattleAnimation(IPlayer, 17, nSkillGrade);
				} else {
					IPlayer._ShowBattleMiss(Target, 17);
				}

				IPlayer.SetDirection(Target);
				IPlayer.DecreaseMana(nMana);
			}
		}
		
	}
}