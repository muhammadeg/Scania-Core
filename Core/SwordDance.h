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
						int nDmg = (IPlayer.GetAttack() * KSDMul) + (nSkillGrade * CTools::Rate(KSDMin,KSDMax));

						if(Target.GetType() == 0)
							nDmg = nDmg * KSDReduce / 100;

						IPlayer.OktayDamageSingle(Target,nDmg,43);

						if (IPlayer.IsOnline())
							IPlayer.SetProperty(PlayerProperty::ContinueSkillPlayerSkillDelay, GetTickCount() + 800);

						if (IPlayer.IsOnline() && Count == 1)
							ResetContinueSkill(IPlayer);

						return;
					} else {
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
				IPlayer.SetProperty(PlayerProperty::ContinueSkillPlayerSkillCount, xSkill.GetGrade()+1);
				IPlayer.SetProperty(PlayerProperty::ContinueSkillPlayerSkillDelay, 0);
			}
		}
		
	}
}