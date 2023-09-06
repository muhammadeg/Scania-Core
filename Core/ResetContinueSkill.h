void __fastcall ResetContinueSkill(IChar IPlayer)
{
	if (IPlayer.IsOnline())
	{
		if (IPlayer.IsValid() && IPlayer.IsBuff(300))
			return;

		if (IPlayer.GetProperty(PlayerProperty::ContinueSkillPlayerSkillID)) {
			IPlayer.SetProperty(PlayerProperty::ContinueSkillPlayerSkillCount, 0);
			IPlayer.SetProperty(PlayerProperty::ContinueSkillPlayerSkillDelay, 0);
			IPlayer.SetProperty(PlayerProperty::ContinueSkillPlayerSkillGrade, 0);
			IPlayer.SetProperty(PlayerProperty::ContinueSkillPlayerSkillID, 0);
			IPlayer.SetProperty(PlayerProperty::ContinueSkillPlayerTarget, 0);
			IPlayer.SetProperty(PlayerProperty::ContinueSkillPlayerX, 0);
			IPlayer.SetProperty(PlayerProperty::ContinueSkillPlayerY, 0);
			IPlayer.UnsetContinueSkill();
			IPlayer._CouldntExecuteSkill();
		}
	}
}

void __fastcall ResetFarContinueSkill(IChar IPlayer)
{
	if (IPlayer.IsOnline())
	{
		if (IPlayer.GetProperty(PlayerProperty::FarContinueSkillPlayerSkillID)) {
			IPlayer.SetProperty(PlayerProperty::FarContinueSkillPlayerDamage, 0);
			IPlayer.SetProperty(PlayerProperty::FarContinueSkillPlayerSkillCount, 0);
			IPlayer.SetProperty(PlayerProperty::FarContinueSkillPlayerSkillDelay, 0);
			IPlayer.SetProperty(PlayerProperty::FarContinueSkillPlayerSkillGrade, 0);
			IPlayer.SetProperty(PlayerProperty::FarContinueSkillPlayerSkillID, 0);
			IPlayer.SetProperty(PlayerProperty::FarContinueSkillPlayerTarget, 0);

			IPlayer.UnsetContinueSkill();
		}
	}
}

void __fastcall ResetRuptureContinueSkill(IChar IPlayer)
{
	if (IPlayer.IsOnline())
	{
		if (IPlayer.GetProperty(PlayerProperty::RuptureContinueSkillPlayerSkillID)) {
			IPlayer.SetProperty(PlayerProperty::RuptureContinueSkillPlayerDamage, 0);
			IPlayer.SetProperty(PlayerProperty::RuptureContinueSkillPlayerSkillCount, 0);
			IPlayer.SetProperty(PlayerProperty::RuptureContinueSkillPlayerSkillDelay, 0);
			IPlayer.SetProperty(PlayerProperty::RuptureContinueSkillPlayerSkillGrade, 0);
			IPlayer.SetProperty(PlayerProperty::RuptureContinueSkillPlayerSkillID, 0);
			IPlayer.SetProperty(PlayerProperty::RuptureContinueSkillPlayerTarget, 0);
			IPlayer.UnsetContinueSkill();
		}
	}
}