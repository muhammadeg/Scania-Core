void __fastcall ContinueTwinBladeStrike(IChar IPlayer)
{
	if (IPlayer.IsValid())
	{
		void *pTarget = (void*)IPlayer.GetProperty(PlayerProperty::FarContinueSkillPlayerTarget);
		IChar Target(pTarget);

		if (pTarget && Target.IsValid() && IPlayer.IsValid())
		{
			if (IPlayer.GetProperty(PlayerProperty::FarContinueSkillPlayerSkillCount))
			{
				int Count = IPlayer.GetProperty(PlayerProperty::FarContinueSkillPlayerSkillCount); 
				IPlayer.SetProperty(PlayerProperty::FarContinueSkillPlayerSkillCount, Count - 1);

				if (CChar::GetRange((int)IPlayer.GetOffset() + 332, (int)pTarget + 332) > 300)
				{
					ResetFarContinueSkill(IPlayer);
					return;
				}

				if (IPlayer.CheckHit(Target, 10))
				{
					int nDmg = (IPlayer.GetAttack() * TTBSMul) + (CTools::Rate(TTBSMin,TTBSMax));

					if(Target.GetType() == 0)
						nDmg = nDmg * TTBSReduce / 100;

					IPlayer.OktayDamageArea(Target,nDmg,23);
				}

				if (IPlayer.IsOnline())
					IPlayer.SetProperty(PlayerProperty::FarContinueSkillPlayerSkillDelay, GetTickCount() + 2000);

				if (IPlayer.IsOnline() && IPlayer.GetProperty(PlayerProperty::FarContinueSkillPlayerSkillCount) == 0)
					ResetFarContinueSkill(IPlayer);

				return;
			}
		}
	}

	ResetFarContinueSkill(IPlayer);
	return;
}

void __fastcall TwinBladeStrike(IChar IPlayer, int pPacket, int pPos)
{
	int pSkill = IPlayer.GetSkillPointer(23);

	if (IPlayer.IsValid() && pSkill)
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

			if (IPlayer.GetCurMp() < 65) {
				
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
					if (!IPlayer.GetProperty(PlayerProperty::FarContinueSkillPlayerSkillID))
						IPlayer.SetContinueSkill();

					IPlayer.SetProperty(PlayerProperty::FarContinueSkillPlayerTarget, (int)Target.GetOffset());
					IPlayer.SetProperty(PlayerProperty::FarContinueSkillPlayerSkillID, 23);
					IPlayer.SetProperty(PlayerProperty::FarContinueSkillPlayerSkillCount, 4);
					IPlayer.SetProperty(PlayerProperty::FarContinueSkillPlayerSkillDelay, GetTickCount() + 2000);
					
					if (!Target.IsBuff(339))
						Target.SendGStateEx(Target.GetGStateEx() + 262144);

					Target.Buff(339,8,0);
					Target.Buff(340,12,0);
					IPlayer.Buff(341,20,0);

					if (Target.GetType() == 0)
					{
						IPlayer.RemoveBuffIcon(0,0,0,219);
						Target.SetBuffIcon(10000, 0, 2021,219);
					}

					int nDmg = (IPlayer.GetAttack() * TTBSMul) + (CTools::Rate(TTBSMin,TTBSMax));

					if (Target.GetType() == 0)
						nDmg = nDmg * TTBSReduce / 100;

					IPlayer.OktayDamageSingle(Target,nDmg,23);
				} else {
					IPlayer._ShowBattleMiss(Target, 23);
				}

				IPlayer.SetDirection(Target);
				IPlayer.DecreaseMana(65);
			}
		}
		
	}
}