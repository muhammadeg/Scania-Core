void __fastcall ContinueSpinBlade(IChar IPlayer)
{
	if (IPlayer.IsValid())
	{
		if (IPlayer.GetProperty(PlayerProperty::ContinueSkillPlayerSkillCount))
		{
			int Count = IPlayer.GetProperty(PlayerProperty::ContinueSkillPlayerSkillCount); 
			IPlayer.SetProperty(PlayerProperty::ContinueSkillPlayerSkillCount, Count - 1);

			if (!IPlayer.IsValid())
			{
				ResetContinueSkill(IPlayer);
				return;
			}

			if (IPlayer.IsMoved(IPlayer.GetProperty(PlayerProperty::ContinueSkillPlayerX), IPlayer.GetProperty(PlayerProperty::ContinueSkillPlayerY)))
			{
				ResetContinueSkill(IPlayer);
				return;
			}

			int Around = IPlayer.GetObjectListAround(3);

			while(Around)
			{
				IChar Object((void*)CBaseList::Offset((void*)Around));

				if (Object.IsValid() && IPlayer.IsValid() && (*(int (__thiscall **)(int, int, DWORD))(*(DWORD *)IPlayer.GetOffset() + 176))((int)IPlayer.GetOffset(), (int)Object.GetOffset(), 0))
				{
					int nDmg = (IPlayer.GetAttack() * TSBMul) + (IPlayer.GetProperty(PlayerProperty::ContinueSkillPlayerSkillGrade) * CTools::Rate(TSBMin,TSBMax));

					if (Object.GetType() == 0)
						nDmg = (nDmg * TSBReduce) / 100;

					if (IPlayer.CheckHit(Object, 10) || Object.GetType() == 1)
						IPlayer.OktayDamageArea(Object,nDmg,36);
				}

				Around = CBaseList::Pop((void*)Around);
			}

			IPlayer._ShowBattleAnimation(IPlayer, 36);

			if (IPlayer.IsOnline())
				IPlayer.SetProperty(PlayerProperty::ContinueSkillPlayerSkillDelay, GetTickCount() + 1000);

			if (IPlayer.IsOnline() && IPlayer.GetProperty(PlayerProperty::ContinueSkillPlayerSkillCount) == 0)
				ResetContinueSkill(IPlayer);

			return;
		}
	}

	ResetContinueSkill(IPlayer);
	return;
}

void __fastcall SpinBlade(IChar IPlayer)
{
	int pSkill = IPlayer.GetSkillPointer(36);

	if (IPlayer.IsValid() && pSkill)
	{
		ISkill xSkill((void*)pSkill);
		int nSkillGrade = xSkill.GetGrade();
		int nMana = (int)((((nSkillGrade+IPlayer.GetLevel()) * nSkillGrade)*1.25) + 180);

		if (IPlayer.GetCurMp() < nMana)
			return;

		if (nSkillGrade && IPlayer.IsValid())
		{
			IPlayer.DecreaseMana(nMana);

			

			if (!IPlayer.GetProperty(PlayerProperty::ContinueSkillPlayerSkillID))
				IPlayer.SetContinueSkill();

			IPlayer.SetProperty(PlayerProperty::ContinueSkillPlayerX, IPlayer.GetX());
			IPlayer.SetProperty(PlayerProperty::ContinueSkillPlayerY, IPlayer.GetY());
			IPlayer.SetProperty(PlayerProperty::ContinueSkillPlayerSkillID, 36);
			IPlayer.SetProperty(PlayerProperty::ContinueSkillPlayerSkillGrade, xSkill.GetGrade());
			IPlayer.SetProperty(PlayerProperty::ContinueSkillPlayerSkillCount, xSkill.GetGrade() + 1);
			IPlayer.SetProperty(PlayerProperty::ContinueSkillPlayerSkillDelay, 0);
		}
	}
}