void __fastcall ContinueArrowRain(IChar IPlayer)
{
	if (IPlayer.IsValid())
	{
		int nSkillGrade = IPlayer.GetProperty(PlayerProperty::ContinueSkillPlayerSkillGrade);
		void *pTarget = (void*)IPlayer.GetProperty(PlayerProperty::ContinueSkillPlayerTarget);

		if (pTarget && nSkillGrade && IPlayer.GetProperty(PlayerProperty::ContinueSkillPlayerSkillCount))
		{
			IChar Target(pTarget);
			int Count = IPlayer.GetProperty(PlayerProperty::ContinueSkillPlayerSkillCount);
			IPlayer.SetProperty(PlayerProperty::ContinueSkillPlayerSkillCount, Count - 1);

			if (!IPlayer.IsValid() || !Target.IsValid())
			{
				ResetContinueSkill(IPlayer);
				return;
			}

			if (IPlayer.GetProperty(PlayerProperty::ContinueSkillPlayerX) && IPlayer.GetProperty(PlayerProperty::ContinueSkillPlayerY) && IPlayer.IsMoved(IPlayer.GetProperty(PlayerProperty::ContinueSkillPlayerX), IPlayer.GetProperty(PlayerProperty::ContinueSkillPlayerY)))
			{
				ResetContinueSkill(IPlayer);
				return;
			}

			int Around = Target.GetObjectListAround(3);

			while(Around)
			{
				IChar Object((void*)CBaseList::Offset((void*)Around));

				if (Object.IsValid() && IPlayer.IsValid() && (*(int (__thiscall **)(int, int, DWORD))(*(DWORD *)IPlayer.GetOffset() + 176))((int)IPlayer.GetOffset(), (int)Object.GetOffset(), 0))
				{
					int nDmg = (IPlayer.GetAttack() * AARMul) + (nSkillGrade * CTools::Rate(AARMin,AARMax));

					if (Object.GetType() == 0)
						nDmg = (nDmg * AARReduce) / 100;

					IPlayer.OktayDamageArea(Object,nDmg,47);
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

void __fastcall ArrowRain(IChar IPlayer, int pPacket, int pPos)
{
	int pSkill = IPlayer.GetSkillPointer(47);

	if (IPlayer.IsValid() && pSkill)
	{
		int x = 0, y = 0;
		CPacket::Read((char*)pPacket, (char*)pPos, "dd", &x, &y);
		ISkill xSkill((void*)pSkill);
		int nSkillGrade = xSkill.GetGrade();
		int nMana = 20 + (IPlayer.GetLevel() * 4);

		if (x <= 0 || y <= 0)
			return;

		if (nSkillGrade && IPlayer.IsValid())
		{
			if (IPlayer.GetCurMp() < nMana)
				return;

			IPlayer.DecreaseMana(nMana);
			IPlayer._ShowBattleAnimation(IPlayer,47);
			int *GetSetXY = new int[2];
			GetSetXY[0] = x;
			GetSetXY[1] = y;
			int check = CMonsterMagic::Create(567,IPlayer.GetMap(),(int)GetSetXY,1,(int)IPlayer.GetOffset(),0,10000);
			delete[] GetSetXY;

			
			if (!IPlayer.GetProperty(PlayerProperty::ContinueSkillPlayerSkillID))
				IPlayer.SetContinueSkill();
			IPlayer.SetProperty(PlayerProperty::ContinueSkillPlayerSkillID, 47);
			IPlayer.SetProperty(PlayerProperty::ContinueSkillPlayerTarget, check);
			IPlayer.SetProperty(PlayerProperty::ContinueSkillPlayerSkillGrade, nSkillGrade);
			IPlayer.SetProperty(PlayerProperty::ContinueSkillPlayerSkillCount, 5);
			IPlayer.SetProperty(PlayerProperty::ContinueSkillPlayerSkillDelay, 0);
			IPlayer.SetProperty(PlayerProperty::ContinueSkillPlayerX, IPlayer.GetX());
			IPlayer.SetProperty(PlayerProperty::ContinueSkillPlayerY, IPlayer.GetY());
		}
	}
}