void __fastcall ContinueWhirlwindFeather(IChar IPlayer)
{
	if (IPlayer.IsValid() && CChar::IsGState((int)IPlayer.GetOffset(),512))
	{
		void *pTarget = (void*)IPlayer.GetProperty(PlayerProperty::ContinueSkillPlayerTarget);
		
		if (pTarget && IPlayer.GetProperty(PlayerProperty::ContinueSkillPlayerSkillCount))
		{
			IChar Target(pTarget);
			int Count = IPlayer.GetProperty(PlayerProperty::ContinueSkillPlayerSkillCount);
			IPlayer.SetProperty(PlayerProperty::ContinueSkillPlayerSkillCount, Count - 1);

			if (!IPlayer.IsValid() || !Target.IsValid())
			{
				ResetContinueSkill(IPlayer);
				return;
			}

			int Around = Target.GetObjectListAround(2);

			while(Around)
			{
				IChar Object((void*)CBaseList::Offset((void*)Around));

				if (Object.IsValid() && Target.IsValid() && IPlayer.IsValid() && (*(int (__thiscall **)(int, int, DWORD))(*(DWORD *)IPlayer.GetOffset() + 176))((int)IPlayer.GetOffset(), (int)Object.GetOffset(), 0))
				{
					int nDmg = (IPlayer.GetAttack() * TEWhirMul);

					if (Object.GetType() == 0)
						nDmg = nDmg * TEWhirReduce / 100;

					IPlayer.OktayDamageArea(Object,nDmg,114);
				}

				Around = CBaseList::Pop((void*)Around);
			}

			if (IPlayer.IsOnline())
				IPlayer.SetProperty(PlayerProperty::ContinueSkillPlayerSkillDelay, GetTickCount() + 1500);

			if (IPlayer.IsOnline() && IPlayer.GetProperty(PlayerProperty::ContinueSkillPlayerSkillCount) == 0)
				ResetContinueSkill(IPlayer);

			return;
		}
	}

	ResetContinueSkill(IPlayer);
	return;
}

void __fastcall WhirlwindFeather(IChar IPlayer)
{
	if (IPlayer.IsValid() && IPlayer.GetRage() >= 15000)
	{
		IPlayer.DecreaseRage(15000);
		int *GetSetXY = new int[2];
		GetSetXY[0] = IPlayer.GetX();
		GetSetXY[1] = IPlayer.GetY();
		int check = CMonsterMagic::Create(568,IPlayer.GetMap(),(int)GetSetXY,1,(int)IPlayer.GetOffset(),0,8000);
		delete[] GetSetXY;
		

		if (!IPlayer.GetProperty(PlayerProperty::ContinueSkillPlayerSkillID))
			IPlayer.SetContinueSkill();

		IPlayer.SetProperty(PlayerProperty::ContinueSkillPlayerSkillID, 114);
		IPlayer.SetProperty(PlayerProperty::ContinueSkillPlayerSkillDelay, 0);
		IPlayer.SetProperty(PlayerProperty::ContinueSkillPlayerX, IPlayer.GetX());
		IPlayer.SetProperty(PlayerProperty::ContinueSkillPlayerY, IPlayer.GetY());
		IPlayer.SetProperty(PlayerProperty::ContinueSkillPlayerSkillCount, 6);
		IPlayer.SetProperty(PlayerProperty::ContinueSkillPlayerTarget, check);
		IPlayer._ShowBattleAnimation(IPlayer, 114);
	}
}