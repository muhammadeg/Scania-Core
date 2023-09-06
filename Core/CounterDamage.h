void __fastcall CounterDamage(IChar IPlayer)
{
	if (IPlayer.IsValid())
	{
		void *pTarget = (void*)IPlayer.GetProperty(PlayerProperty::FarContinueSkillPlayerTarget);
		IChar Target(pTarget);

		if (pTarget && IPlayer.IsValid() && Target.IsValid())
		{
			IPlayer.AddFxToTarget("Counterattack_Spear_2",1,0,0);

			if (IPlayer.GetProperty(PlayerProperty::FarContinueSkillPlayerSkillCount))
			{
				int Count = IPlayer.GetProperty(PlayerProperty::FarContinueSkillPlayerSkillCount);
				IPlayer.SetProperty(PlayerProperty::FarContinueSkillPlayerSkillCount, Count - 1);

				if (IPlayer.IsValid() && Target.IsValid())
				{
					if (!IPlayer.IsInRange(Target,300))
					{
						ResetFarContinueSkill(IPlayer);
						return;
					}

					if (IPlayer.GetProperty(PlayerProperty::FarContinueSkillPlayerDamage) > 1000)
						IPlayer.SetProperty(PlayerProperty::FarContinueSkillPlayerDamage, 1000);

					int nDmg = IPlayer.GetProperty(PlayerProperty::FarContinueSkillPlayerDamage);
					IPlayer.OktayDamageArea(Target,nDmg,76);

					if (IPlayer.IsOnline() && IPlayer.GetProperty(PlayerProperty::FarContinueSkillPlayerSkillCount) == 0)
						ResetFarContinueSkill(IPlayer);

					if (IPlayer.IsOnline())
						IPlayer.SetProperty(PlayerProperty::FarContinueSkillPlayerSkillDelay, GetTickCount() + 2000);

					return;
				}
			}
		}
	}

	ResetFarContinueSkill(IPlayer);
	return;
}