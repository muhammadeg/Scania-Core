void __fastcall ContinueFlameInjection(IChar IPlayer)
{
	if (IPlayer.IsValid())
	{
		int nSkillGrade = IPlayer.GetProperty(PlayerProperty::ContinueSkillPlayerSkillGrade);

		if (nSkillGrade && IPlayer.GetProperty(PlayerProperty::ContinueSkillPlayerSkillCount))
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

			int Around = IPlayer.GetObjectListAround(4);

			while(Around)
			{
				IChar Object((void*)CBaseList::Offset((void*)Around));

				if (Object.IsValid() && IPlayer.IsValid() && (*(int (__thiscall **)(int, int, DWORD))(*(DWORD *)IPlayer.GetOffset() + 176))((int)IPlayer.GetOffset(), (int)Object.GetOffset(), 0))
				{
					int nDmg = (IPlayer.GetMagic() * MFIMul) + (nSkillGrade * CTools::Rate(MFIMin,MFIMax));

					if (Object.GetType() == 0)
						nDmg = (nDmg * MFIReduce) / 100;

					IPlayer.OktayDamageArea(Object,nDmg,65);
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

void __fastcall FlameInjection(IChar IPlayer, int pPacket, int pPos)
{
	int pSkill = IPlayer.GetSkillPointer(65);

	if (IPlayer.IsValid() && pSkill)
	{
		ISkill xSkill((void*)pSkill);
		int nSkillGrade = xSkill.GetGrade();
		int nTargetID = 0; char bType = 0; void *pTarget = 0;
		CPacket::Read((char*)pPacket, (char*)pPos, "bd", &bType, &nTargetID);
		int nMana = IPlayer.GetLevel() * 4 + 120;

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

				IPlayer.DecreaseMana(nMana);

				
				if (!IPlayer.GetProperty(PlayerProperty::ContinueSkillPlayerSkillID))
					IPlayer.SetContinueSkill();
				IPlayer.SetProperty(PlayerProperty::ContinueSkillPlayerX, IPlayer.GetX());
				IPlayer.SetProperty(PlayerProperty::ContinueSkillPlayerY, IPlayer.GetY());
				IPlayer.SetProperty(PlayerProperty::ContinueSkillPlayerSkillID, 65);
				IPlayer.SetProperty(PlayerProperty::ContinueSkillPlayerSkillGrade, xSkill.GetGrade());
				IPlayer.SetProperty(PlayerProperty::ContinueSkillPlayerSkillCount, 6);
				IPlayer.SetProperty(PlayerProperty::ContinueSkillPlayerSkillDelay, 0);
				IPlayer._ShowBattleAnimation(IPlayer, 65);
			}
		}
		
	}
}