void __fastcall ContinueIcicle(IChar IPlayer)
{
	if (IPlayer.IsValid())
	{
		if (IPlayer.GetProperty(PlayerProperty::ContinueSkillPlayerSkillCount))
		{
			int Count = IPlayer.GetProperty(PlayerProperty::ContinueSkillPlayerSkillCount);
			IPlayer.SetProperty(PlayerProperty::ContinueSkillPlayerSkillCount, Count - 1);

			if (IPlayer.IsMoved(IPlayer.GetProperty(PlayerProperty::ContinueSkillPlayerX), IPlayer.GetProperty(PlayerProperty::ContinueSkillPlayerY)))
			{
				ResetContinueSkill(IPlayer);
				return;
			}

			if (!IPlayer.IsValid())
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
					int nDmg = (IPlayer.GetMagic() * MIcicleMul) + (IPlayer.GetProperty(PlayerProperty::ContinueSkillPlayerSkillGrade) * CTools::Rate(MIcicleMin,MIcicleMax));

					if (Object.GetType() == 0)
						nDmg = (nDmg * MIcicleReduce) / 100;

					IPlayer.OktayDamageArea(Object,nDmg,66);
				}

				Around = CBaseList::Pop((void*)Around);
			}

			if (IPlayer.IsOnline())
				IPlayer.SetProperty(PlayerProperty::ContinueSkillPlayerSkillDelay, GetTickCount() + 2000);

			if (IPlayer.IsOnline() && IPlayer.GetProperty(PlayerProperty::ContinueSkillPlayerSkillCount) == 0)
				ResetContinueSkill(IPlayer);

			return;
		}
	}

	ResetContinueSkill(IPlayer);
	return;
}

void __fastcall Icicle(IChar IPlayer)
{
	int pSkill = IPlayer.GetSkillPointer(66);

	if (IPlayer.IsValid() && pSkill)
	{
		int nMana = IPlayer.GetLevel() * 4 + 120;

		if (IPlayer.GetCurMp() < nMana)
			return;

		IPlayer.DecreaseMana(nMana);
		ISkill xSkill((void*)pSkill);
		
		if (!IPlayer.GetProperty(PlayerProperty::ContinueSkillPlayerSkillID))
			IPlayer.SetContinueSkill();
		IPlayer.SetProperty(PlayerProperty::ContinueSkillPlayerX, IPlayer.GetX());
		IPlayer.SetProperty(PlayerProperty::ContinueSkillPlayerY, IPlayer.GetY());
		IPlayer.SetProperty(PlayerProperty::ContinueSkillPlayerSkillID, 66);
		IPlayer.SetProperty(PlayerProperty::ContinueSkillPlayerSkillGrade, xSkill.GetGrade());
		IPlayer.SetProperty(PlayerProperty::ContinueSkillPlayerSkillCount, 5);
		IPlayer.SetProperty(PlayerProperty::ContinueSkillPlayerSkillDelay, 0);
		IPlayer._ShowBattleAnimation(IPlayer, 66);
	}
}