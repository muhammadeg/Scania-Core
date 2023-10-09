void __fastcall CombativeSpirit(IChar IPlayer, int pPacket, int pPos)
{
	int pSkill = IPlayer.GetSkillPointer(51);

	if (IPlayer.IsValid() && pSkill)
	{
		int TargetAOE = 0;
		if (ACAOE && ACPVPAOE)
			TargetAOE = 3;
		else if (ACPVPAOE)
			TargetAOE = 2;
		else if (ACAOE)
			TargetAOE = 1;

		ISkill xSkill((void*)pSkill);
		int nSkillGrade = xSkill.GetGrade();
		int nTargetID = 0; char bType = 0; void *pTarget = 0;
		CPacket::Read((char*)pPacket, (char*)pPos, "bd", &bType, &nTargetID);	
		
		TargetFind myTarget(bType, 0, nTargetID);
		pTarget = myTarget.getTarget();

		if (bType >= 2)
			return;

		if (IPlayer.IsValid() && pTarget && nSkillGrade)
		{
			IChar Target(pTarget);
			int nMana = (int)(((((nSkillGrade-1)+20) * nSkillGrade)+200) * 1.85);

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

				if (IPlayer.CheckHit(Target,30))
				{
					IPlayer.SetDirection(Target);
					IPlayer._ShowBattleAnimation(Target,51);
					int Around = Target.GetObjectListAround(ACAOERange);

					while(Around)
					{
						IChar Object((void*)CBaseList::Offset((void*)Around));

						if (Object.IsValid() && IPlayer.IsValid() && (*(int (__thiscall **)(int, int, DWORD))(*(DWORD *)IPlayer.GetOffset() + 176))((int)IPlayer.GetOffset(), (int)Object.GetOffset(), 0))
						{
							int nDmg = (IPlayer.GetAttack() * ACSMul) + (nSkillGrade * CTools::Rate(ACSMin,ACSMax));

							if (Target.GetType() == 0)
								nDmg = (nDmg * ACSReduce) / 100;

							if (ACAOE && (TargetAOE == 3 || (TargetAOE && !Target.IsValid()) || (TargetAOE == 2 && Target.GetType() == 0) || (TargetAOE == 1 && Target.GetType() == 1)))
								IPlayer.OktayDamageArea(Object,nDmg,51);
							else if
								 (Object.GetX() <= max(IPlayer.GetX(), Target.GetX()) && Object.GetX() >= min(IPlayer.GetX(), Target.GetX()) && Object.GetY() <= max(IPlayer.GetY(), Target.GetY()) && Object.GetY() >= min(IPlayer.GetY(), Target.GetY()))
								 IPlayer.OktayDamageArea(Object, nDmg, 51);

						}

						Around = CBaseList::Pop((void*)Around);
					}
				} else {
					IPlayer._ShowBattleMiss(Target,51);
				}
			}
		}
		
	}
}