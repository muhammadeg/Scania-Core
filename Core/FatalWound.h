void __fastcall ContinueFatalWound(IChar IPlayer)
{
	if (IPlayer.IsValid())
	{
		int nSkillGrade = IPlayer.GetProperty(PlayerProperty::FarContinueSkillPlayerSkillGrade);
		void *pTarget = (void*)IPlayer.GetProperty(PlayerProperty::FarContinueSkillPlayerTarget);

		if (nSkillGrade && pTarget && IPlayer.GetProperty(PlayerProperty::FarContinueSkillPlayerSkillCount))
		{
			IChar Target(pTarget);
			int Count = IPlayer.GetProperty(PlayerProperty::FarContinueSkillPlayerSkillCount); 
			IPlayer.SetProperty(PlayerProperty::FarContinueSkillPlayerSkillCount, Count - 1);

			if (!Target.IsValid() || !IPlayer.IsValid())
			{
				ResetFarContinueSkill(IPlayer);
				return;
			}

			if (!IPlayer.IsInRange(Target,300))
			{
				ResetFarContinueSkill(IPlayer);
				return;
			}

			if (IPlayer.IsValid() && Target.IsValid())
			{
				int nDmg = (IPlayer.GetAttack() * TFWMul) + (nSkillGrade * CTools::Rate(TFWMin,TFWMax));

				if (Target.GetType() == 0)
					nDmg = (nDmg * TFWReduce) / 100;

				IPlayer.OktayDamageArea(Target,nDmg,14);
			}

			if (IPlayer.IsOnline())
				IPlayer.SetProperty(PlayerProperty::FarContinueSkillPlayerSkillDelay, GetTickCount() + 2000);

			if (IPlayer.IsOnline() && IPlayer.GetProperty(PlayerProperty::FarContinueSkillPlayerSkillCount) == 0)
				ResetFarContinueSkill(IPlayer);

			return;
		}
	}

	ResetFarContinueSkill(IPlayer);
	return;
}

void __fastcall FatalWound(IChar IPlayer, int pPacket, int pPos)
{
	int pSkill = IPlayer.GetSkillPointer(14);

	if (IPlayer.IsValid() && pSkill)
	{
		ISkill xSkill((void*)pSkill);
		int nSkillGrade = xSkill.GetGrade();
		int nTargetID = 0; char bType = 0; void *pTarget = 0;
		CPacket::Read((char*)pPacket, (char*)pPos, "bd", &bType, &nTargetID);
		int nMana = (int)(30 * nSkillGrade + 15);

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
				if (!IPlayer.IsInRange(Target, 300)) {
					
					return;
				}

				if (!Target.IsBuff(348))
				{
					Target.SendGStateEx(Target.GetGStateEx() + 32768); 
					
					if (!IPlayer.GetProperty(PlayerProperty::FarContinueSkillPlayerSkillID))
						IPlayer.SetContinueSkill();

					IPlayer.SetProperty(PlayerProperty::FarContinueSkillPlayerTarget, (int)Target.GetOffset());
					IPlayer.SetProperty(PlayerProperty::FarContinueSkillPlayerSkillID, 14);
					IPlayer.SetProperty(PlayerProperty::FarContinueSkillPlayerSkillCount, 8);
					IPlayer.SetProperty(PlayerProperty::FarContinueSkillPlayerSkillDelay, 0);
					IPlayer.SetProperty(PlayerProperty::FarContinueSkillPlayerSkillGrade, nSkillGrade);
					Target.Buff(348, 16, 0);
				}

				IPlayer.SetDirection(Target);
				IPlayer.DecreaseMana(nMana);
				IPlayer._ShowBattleAnimation(Target, 14, nSkillGrade);
			}
		}
		
	}
}