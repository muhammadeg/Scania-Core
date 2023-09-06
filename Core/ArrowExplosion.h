void __fastcall ContinueArrowExplosion(IChar IPlayer)
{
	if (IPlayer.IsValid())
	{
		IPlayer.CancelBuff(300);
		void *pTarget = (void*)IPlayer.GetProperty(PlayerProperty::ContinueSkillPlayerTarget);
		int nSkillGrade = IPlayer.GetProperty(PlayerProperty::ContinueSkillPlayerSkillGrade);

		if (nSkillGrade && pTarget && IPlayer.GetProperty(PlayerProperty::ContinueSkillPlayerSkillCount))
		{
			int Count = IPlayer.GetProperty(PlayerProperty::ContinueSkillPlayerSkillCount);
			IPlayer.SetProperty(PlayerProperty::ContinueSkillPlayerSkillCount, Count - 1);

			IChar Target(pTarget);

			if (IPlayer.IsValid() && Target.IsValid())
			{
				if (!IPlayer.IsInRange(Target,300))
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
						int nDmg = (IPlayer.GetAttack() * AAEMul) + (nSkillGrade * CTools::Rate(AAEMin,AAEMax));

						if (Object.GetType() == 0)
							nDmg = (nDmg * AAEReduce) / 100;

						IPlayer.OktayDamageArea(Object,nDmg,49);
					}

					Around = CBaseList::Pop((void*)Around);
				}
			}
		}
	}

	ResetContinueSkill(IPlayer);
	return;
}

void __fastcall ContinueArrowExplosion(void* Player)
{
	IChar IPlayer(Player);
	return ContinueArrowExplosion(IPlayer);
}

void __fastcall ArrowExplosion(IChar IPlayer, int pPacket, int pPos)
{
	int pSkill = IPlayer.GetSkillPointer(49);

	if (IPlayer.IsValid() && pSkill)
	{
		ISkill xSkill((void*)pSkill);
		int nSkillGrade = xSkill.GetGrade();
		int nTargetID = 0; char bType = 0; void *pTarget = 0;
		CPacket::Read((char*)pPacket, (char*)pPos, "bd", &bType, &nTargetID);
		int nMana = 20 + (IPlayer.GetLevel() * 4);

		TargetFind myTarget(bType, 0, nTargetID);
		pTarget = myTarget.getTarget();

		if (bType >= 2)
			return;

		if (IPlayer.IsValid() && pTarget && nSkillGrade)
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
				IPlayer.SetDirection(Target);
				IPlayer._ShowBattleAnimation(Target,49);
				IPlayer.Buff(300,5,0);
				Target.AddFxToTarget("davi_ef131_04",1,0,0);

				if(!IPlayer.GetProperty(PlayerProperty::ContinueSkillPlayerSkillID))
					IPlayer.SetContinueSkill();

				IPlayer.SetProperty(PlayerProperty::ContinueSkillPlayerSkillID, 49);
				IPlayer.SetProperty(PlayerProperty::ContinueSkillPlayerTarget, (int)Target.GetOffset());
				IPlayer.SetProperty(PlayerProperty::ContinueSkillPlayerSkillGrade, nSkillGrade);
				IPlayer.SetProperty(PlayerProperty::ContinueSkillPlayerSkillCount, 1);
				IPlayer.SetProperty(PlayerProperty::ContinueSkillPlayerSkillDelay, GetTickCount() + (AETime * 1000));

				if (Target.IsValid() && Target.GetType() == 1 && Target.GetMobTanker() && Target.GetMobTanker() != (int)IPlayer.GetOffset())
					Target.SetMobHostility(0);

				if (Target.GetType() == 1)
					IPlayer.OktayDamageSingle(Target,CTools::Rate(500,750),42);

				if (Target.IsValid() && Target.GetType() == 1 && Target.GetMobTanker() == (int)IPlayer.GetOffset())
					Target.SetMobHostility(25000);
			}
		}
		
	}
}