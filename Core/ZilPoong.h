void __fastcall ContinueZilPoong(IChar IPlayer)
{
	if (IPlayer.IsValid() && CChar::IsGState((int)IPlayer.GetOffset(),512))
	{
		void *pTarget = (void*)IPlayer.GetProperty(PlayerProperty::ContinueSkillPlayerTarget);
		
		if (pTarget && IPlayer.GetProperty(PlayerProperty::ContinueSkillPlayerSkillCount))
		{
			IChar Target(pTarget);
			int Count = IPlayer.GetProperty(PlayerProperty::ContinueSkillPlayerSkillCount);
			IPlayer.SetProperty(PlayerProperty::ContinueSkillPlayerSkillCount, Count - 1);

			if (IPlayer.IsValid() && Target.IsValid())
			{
				if (!IPlayer.IsInRange(Target, 2))
				{
					ResetContinueSkill(IPlayer);
					return;
				}

				if (IPlayer.CheckHit(Target, 20))
				{
					int nDmg = (IPlayer.GetAttack() * TEZilMul);

					if(Target.GetType() == 0)
						nDmg = nDmg * TEZilReduce / 100;

					IPlayer.OktayDamageSingle(Target,nDmg,6);
				} else {
					IPlayer._ShowBattleMiss(Target, 6);
				}

				if (IPlayer.IsOnline())
					IPlayer.SetProperty(PlayerProperty::ContinueSkillPlayerSkillDelay, GetTickCount() + 800);

				if (IPlayer.IsOnline() && IPlayer.GetProperty(PlayerProperty::ContinueSkillPlayerSkillCount) == 0)
					ResetContinueSkill(IPlayer);

				return;
			}
		}
	}

	ResetContinueSkill(IPlayer);
	return;
}

void __fastcall ZilPoong(IChar IPlayer, int pPacket, int pPos)
{
	if (IPlayer.IsValid() && IPlayer.GetRage() >= 4000)
	{
		int nTargetID = 0; char bType = 0; void *pTarget = 0;
		CPacket::Read((char*)pPacket, (char*)pPos, "bd", &bType, &nTargetID);

		TargetFind myTarget(bType, 0, nTargetID);
		pTarget = myTarget.getTarget();

		if (bType >= 2)
			return;

		if (pTarget && IPlayer.IsValid())
		{
			IChar Target(pTarget);

			if (pTarget == IPlayer.GetOffset()) {
				
				return;
			}

			if (IPlayer.IsValid() && Target.IsValid())
			{
				if (!IPlayer.IsInRange(Target, 300)) {
					
					return;
				}

				IPlayer.DecreaseRage(4000);
				

				if (!IPlayer.GetProperty(PlayerProperty::ContinueSkillPlayerSkillID))
					IPlayer.SetContinueSkill();

				IPlayer.SetProperty(PlayerProperty::ContinueSkillPlayerSkillID, 111);
				IPlayer.SetProperty(PlayerProperty::ContinueSkillPlayerSkillDelay, 0);
				IPlayer.SetProperty(PlayerProperty::ContinueSkillPlayerSkillCount, 3);
				IPlayer.SetProperty(PlayerProperty::ContinueSkillPlayerTarget, (int)Target.GetOffset());
				IPlayer._ShowBattleAnimation(IPlayer, 111);
			}
		}
		
	}
}