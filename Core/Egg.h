void __fastcall BloodSuction(IChar IPlayer, int pPacket, int pPos)
{
	if (IPlayer.IsValid() && IPlayer.GetRage() >= 15000 && CChar::IsGState((int)IPlayer.GetOffset(), 512))
	{
		int nTargetID = 0; char bType = 0; void *pTarget = 0;
		CPacket::Read((char*)pPacket, (char*)pPos, "bd", &bType, &nTargetID);

		TargetFind myTarget(bType, 0, nTargetID);
		pTarget = myTarget.getTarget();

		if (bType >= 2)
			return;

		if (pTarget && IPlayer.IsValid())
		{
			IChar ITarget(pTarget);

			if (ITarget.IsValid() && IPlayer.IsValid())
			{
				if (pTarget == IPlayer.GetOffset()) {

					return;
				}

				if (!IPlayer.IsInRange(ITarget, 300)) {

					return;
				}

				int nDmg = (IPlayer.GetAttack() * EBSMul);

				if (ITarget.GetType() == 0)
					nDmg = (nDmg * EBSReduce) / 100;

				int realDamage = IPlayer.OktayDamageSingle(ITarget, nDmg, 115);

				if (realDamage > 5)
					IPlayer.IncreaseHp(realDamage * 30 / 75);

				IPlayer.DecreaseRage(15000);
			}
		}

	}
}
void __fastcall ContinueEggThunderbolt(IChar IPlayer)
{
	if (IPlayer.IsValid() && CChar::IsGState((int)IPlayer.GetOffset(), 512))
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

			while (Around)
			{
				IChar Object((void*)CBaseList::Offset((void*)Around));

				if (Object.IsValid() && IPlayer.IsValid() && (*(int(__thiscall **)(int, int, DWORD))(*(DWORD *)IPlayer.GetOffset() + 176))((int)IPlayer.GetOffset(), (int)Object.GetOffset(), 0))
				{
					int nDmg = (IPlayer.GetMagic() * ETBMul);

					if (Object.GetType() == 0)
						nDmg = (nDmg * ETBReduce) / 100;

					IPlayer.OktayDamageArea(Object, nDmg, 116);
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

void __fastcall HighClassHiding(IChar IPlayer)
{
	if (IPlayer.IsValid())
	{
		if (IPlayer.GetRage() < 9)
			return;

		if (!IPlayer.IsBuff(327))
			IPlayer.SendGStateEx(IPlayer.GetGStateEx() + 2048);

		IPlayer.Buff(327, 30, 0);
		IPlayer._ShowBattleAnimation(IPlayer, 110);
		IPlayer.DecreaseRage(9);
	}
}
void __fastcall ContinueWhirlwindFeather(IChar IPlayer)
{
	if (IPlayer.IsValid() && CChar::IsGState((int)IPlayer.GetOffset(), 512))
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

			while (Around)
			{
				IChar Object((void*)CBaseList::Offset((void*)Around));

				if (Object.IsValid() && Target.IsValid() && IPlayer.IsValid() && (*(int(__thiscall **)(int, int, DWORD))(*(DWORD *)IPlayer.GetOffset() + 176))((int)IPlayer.GetOffset(), (int)Object.GetOffset(), 0))
				{
					int nDmg = (IPlayer.GetAttack() * TEWhirMul);

					if (Object.GetType() == 0)
						nDmg = nDmg * TEWhirReduce / 100;

					IPlayer.OktayDamageArea(Object, nDmg, 114);
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
		int check = CMonsterMagic::Create(568, IPlayer.GetMap(), (int)GetSetXY, 1, (int)IPlayer.GetOffset(), 0, 8000);
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
void __fastcall ShinRhoe(IChar IPlayer)
{
	if (IPlayer.IsValid() && IPlayer.GetRage() >= 4800)
	{
		int Around = IPlayer.GetObjectListAround(2);

		while (Around)
		{
			IChar Object((void*)CBaseList::Offset((void*)Around));

			if (Object.IsValid() && IPlayer.IsValid() && (*(int(__thiscall **)(int, int, DWORD))(*(DWORD *)IPlayer.GetOffset() + 176))((int)IPlayer.GetOffset(), (int)Object.GetOffset(), 0))
			{
				int nDmg = (IPlayer.GetAttack() * TEShinMul);

				if (Object.GetType() == 0)
					nDmg = nDmg * TEShinReduce / 100;

				IPlayer.OktayDamageArea(Object, nDmg, 112);
			}

			Around = CBaseList::Pop((void*)Around);
		}

		IPlayer._ShowBattleAnimation(IPlayer, 112);
		IPlayer.DecreaseRage(4800);
	}
}
void __fastcall ContinueZilPoong(IChar IPlayer)
{
	if (IPlayer.IsValid() && CChar::IsGState((int)IPlayer.GetOffset(), 512))
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

					if (Target.GetType() == 0)
						nDmg = nDmg * TEZilReduce / 100;

					IPlayer.OktayDamageSingle(Target, nDmg, 6);
				}
				else {
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

void __fastcall RevolveAttack(IChar IPlayer)
{
	if (IPlayer.IsValid() && IPlayer.GetRage() >= 15000)
	{
		int Around = IPlayer.GetObjectListAround(2);

		while (Around)
		{
			IChar Object((void*)CBaseList::Offset((void*)Around));

			if (Object.IsValid() && IPlayer.IsValid() && (*(int(__thiscall **)(int, int, DWORD))(*(DWORD *)IPlayer.GetOffset() + 176))((int)IPlayer.GetOffset(), (int)Object.GetOffset(), 0))
			{
				int nDmg = (IPlayer.GetAttack() * ERAMul);

				if (Object.GetType() == 0)
					nDmg = (nDmg * ERAReduce) / 100;

				IPlayer.OktayDamageSingle(Object, nDmg, 113);
			}

			Around = CBaseList::Pop((void*)Around);
		}

		IPlayer.DecreaseRage(15000);
	}
}

void __fastcall EggThunderbolt(IChar IPlayer)
{
	if (IPlayer.IsValid() && IPlayer.GetRage() >= 15000)
	{
		IPlayer.DecreaseRage(15000);
		int *GetSetXY = new int[2];
		GetSetXY[0] = IPlayer.GetX();
		GetSetXY[1] = IPlayer.GetY();
		int check = CMonsterMagic::Create(568, IPlayer.GetMap(), (int)GetSetXY, 1, (int)IPlayer.GetOffset(), 0, 8000);
		delete[] GetSetXY;

		if (!IPlayer.GetProperty(PlayerProperty::ContinueSkillPlayerSkillID))
			IPlayer.SetContinueSkill();
		IPlayer.SetProperty(PlayerProperty::ContinueSkillPlayerSkillID, 116);
		IPlayer.SetProperty(PlayerProperty::ContinueSkillPlayerSkillDelay, 0);
		IPlayer.SetProperty(PlayerProperty::ContinueSkillPlayerX, IPlayer.GetX());
		IPlayer.SetProperty(PlayerProperty::ContinueSkillPlayerY, IPlayer.GetY());
		IPlayer.SetProperty(PlayerProperty::ContinueSkillPlayerSkillCount, 6);
		IPlayer.SetProperty(PlayerProperty::ContinueSkillPlayerTarget, check);
		IPlayer._ShowBattleAnimation(IPlayer, 116);
	}
}