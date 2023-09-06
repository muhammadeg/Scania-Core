void __fastcall ContinueLightningSlash(IChar IPlayer)
{
	if (IPlayer.IsValid())
	{
		int nSkillGrade = IPlayer.GetProperty(PlayerProperty::ContinueSkillPlayerSkillGrade);
		void *pTarget = (void*)IPlayer.GetProperty(PlayerProperty::ContinueSkillPlayerTarget);

		if (nSkillGrade && pTarget && IPlayer.GetProperty(PlayerProperty::ContinueSkillPlayerSkillCount))
		{
			IChar Target(pTarget);
			int Count = IPlayer.GetProperty(PlayerProperty::ContinueSkillPlayerSkillCount);
			IPlayer.SetProperty(PlayerProperty::ContinueSkillPlayerSkillCount, Count - 1);

			if(IPlayer.IsValid() && Target.IsValid())
			{
				if (!IPlayer.IsInRange(Target, 2))
				{
					ResetContinueSkill(IPlayer);
					return;
				}

				if (IPlayer.IsMoved(IPlayer.GetProperty(PlayerProperty::ContinueSkillPlayerX), IPlayer.GetProperty(PlayerProperty::ContinueSkillPlayerY)))
				{
					ResetContinueSkill(IPlayer);
					return;
				}

				if (IPlayer.CheckHit(Target, 30))
				{
					int nDmg = (IPlayer.GetAttack() * TLSMul) + (nSkillGrade * CTools::Rate(TLSMin,TLSMax));

					if (Target.GetType() == 0)
						nDmg = nDmg * TLSReduce / 100;

					IPlayer.OktayDamageSingle(Target,nDmg,28);
				}

				if (IPlayer.IsOnline())
					IPlayer.SetProperty(PlayerProperty::ContinueSkillPlayerSkillDelay, GetTickCount() + 700);

				if (IPlayer.IsOnline() && Count == 1)
					ResetContinueSkill(IPlayer);

				return;
			}
		}
	}

	ResetContinueSkill(IPlayer);
	return;
}

void __fastcall LightningSlash(IChar IPlayer, int pPacket, int pPos)
{
	int pSkill = IPlayer.GetSkillPointer(28);

	if (IPlayer.IsValid() && pSkill)
	{
		ISkill xSkill((void*)pSkill);
		int nSkillGrade = xSkill.GetGrade();
		int nTargetID = 0; char bType = 0; void *pTarget = 0;
		CPacket::Read((char*)pPacket, (char*)pPos, "bd", &bType, &nTargetID);
		int nMana = (nSkillGrade + IPlayer.GetLevel()) * 3 + 50;

		TargetFind myTarget(bType, 0, nTargetID);
		pTarget = myTarget.getTarget();

		if(bType >= 2)
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

				IPlayer.DecreaseMana(nMana);
				
				if (!IPlayer.GetProperty(PlayerProperty::ContinueSkillPlayerSkillID))
					IPlayer.SetContinueSkill();
				IPlayer.SetProperty(PlayerProperty::ContinueSkillPlayerX, IPlayer.GetX());
				IPlayer.SetProperty(PlayerProperty::ContinueSkillPlayerY, IPlayer.GetY());
				IPlayer.SetProperty(PlayerProperty::ContinueSkillPlayerSkillID, 28);
				IPlayer.SetProperty(PlayerProperty::ContinueSkillPlayerTarget, (int)Target.GetOffset());
				IPlayer.SetProperty(PlayerProperty::ContinueSkillPlayerSkillGrade, xSkill.GetGrade());
				IPlayer.SetProperty(PlayerProperty::ContinueSkillPlayerSkillCount, xSkill.GetGrade() + 1);
				IPlayer.SetProperty(PlayerProperty::ContinueSkillPlayerSkillDelay, 0);
			}
		}
	}
}