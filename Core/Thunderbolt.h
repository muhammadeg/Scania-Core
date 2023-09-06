void __fastcall ContinueThunderbolt(IChar IPlayer)
{
	if (IPlayer.IsValid())
	{
		void *pTarget = (void*)IPlayer.GetProperty(PlayerProperty::ContinueSkillPlayerTarget);
		IChar Target(pTarget);

		if (!Target.IsValid())
		{
			ResetContinueSkill(IPlayer);
			return;
		}

		if (IPlayer.GetProperty(PlayerProperty::ContinueSkillPlayerSkillCount))
		{
			int Count = IPlayer.GetProperty(PlayerProperty::ContinueSkillPlayerSkillCount);
			IPlayer.SetProperty(PlayerProperty::ContinueSkillPlayerSkillCount, Count - 1);

			if (!IPlayer.IsInRange(Target, 30))			
			{
				ResetContinueSkill(IPlayer);
				return;
			}

			if(!IPlayer.IsValid() || !Target.IsValid())
			{
				ResetContinueSkill(IPlayer);
				return;
			}

			int nDmg = (IPlayer.GetMagic() * MTBMul) + (IPlayer.GetProperty(PlayerProperty::ContinueSkillPlayerSkillGrade) * CTools::Rate(MTBMin,MTBMax));

			if (Target.GetType() == 0)
				nDmg = nDmg * MTBReduce / 100;

			IPlayer.OktayDamageSingle(Target,nDmg,75);
			IPlayer.SetDirection(Target);

			if (IPlayer.IsOnline())
				IPlayer.SetProperty(PlayerProperty::ContinueSkillPlayerSkillDelay, GetTickCount() + 200);

			if (IPlayer.IsOnline() && IPlayer.GetProperty(PlayerProperty::ContinueSkillPlayerSkillCount) == 0)
				ResetContinueSkill(IPlayer);

			return;
		}
	}

	ResetContinueSkill(IPlayer);
	return;
}

void __fastcall Thunderbolt(IChar IPlayer, int pPacket, int pPos)
{
	int pSkill = IPlayer.GetSkillPointer(75);

	if (IPlayer.IsValid() && pSkill)
	{
		ISkill xSkill((void*)pSkill);
		int nTargetID = 0; char bType = 0; void* pTarget = 0;
		CPacket::Read((char*)pPacket, (char*)pPos, "bd", &bType, &nTargetID);
		int nMana = (int)(((((xSkill.GetGrade()-1)+45) * xSkill.GetGrade())+280) * 0.75);

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
				IPlayer.DecreaseMana(nMana);
				

				if (!IPlayer.GetProperty(PlayerProperty::ContinueSkillPlayerSkillID))
					IPlayer.SetContinueSkill();

				IPlayer.SetProperty(PlayerProperty::ContinueSkillPlayerSkillID, 75);
				IPlayer.SetProperty(PlayerProperty::ContinueSkillPlayerTarget, (int)Target.GetOffset());
				IPlayer.SetProperty(PlayerProperty::ContinueSkillPlayerSkillGrade, xSkill.GetGrade());
				IPlayer.SetProperty(PlayerProperty::ContinueSkillPlayerSkillCount, 6);
				IPlayer.SetProperty(PlayerProperty::ContinueSkillPlayerSkillDelay, 0);
			}
		}
		
	}
}