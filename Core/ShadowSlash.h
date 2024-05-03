void __fastcall ShadowSlash(IChar IPlayer, int pPacket, int pPos)
{
	int pSkill = IPlayer.GetSkillPointer(32);

	if (IPlayer.IsValid() && pSkill)
	{
		ISkill xSkill((void*)pSkill);
		int nSkillGrade = xSkill.GetGrade();
		int nTargetID = 0; char bType = 0; void *pTarget = 0;
		CPacket::Read((char*)pPacket, (char*)pPos, "bd", &bType, &nTargetID);
		int nMana = 230 + (((IPlayer.GetLevel() + nSkillGrade) * nSkillGrade) * 0.63);

		TargetFind myTarget(bType, 0, nTargetID);
		pTarget = myTarget.getTarget();

		if (bType >= 2)
			return;
		
		if (pTarget && IPlayer.IsValid() && nSkillGrade)
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
				if (IPlayer.CheckHit(Target, 30))
				{
					int Around = Target.GetObjectListAround(ShadowRange);

					while(Around)
					{
						IChar Object((void*)CBaseList::Offset((void*)Around));

						if (Object.IsValid() && IPlayer.IsValid() && IPlayer.GetOffset() != Object.GetOffset() && (*(int (__thiscall **)(int, int, DWORD))(*(DWORD *)IPlayer.GetOffset() + 176))((int)IPlayer.GetOffset(), (int)Object.GetOffset(), 0))
						{
							if (((!ShadowAOEPVE || !ShadowAOEPVP) && Target.IsValid() && Target.GetX() <= max(IPlayer.GetX(), Object.GetX()) && Target.GetX() >= min(IPlayer.GetX(), Object.GetX()) && Target.GetY() <= max(IPlayer.GetY(), Object.GetY()) && Target.GetY() >= min(IPlayer.GetY(), Object.GetY())) || ShadowAOEPVE && ShadowAOEPVP)
							{
								Object.Buff(7, nSkillGrade, 0);
								int nDmg = (IPlayer.GetAttack() * TSSMul) + (nSkillGrade * CTools::Rate(TSSMin,TSSMax));

								if (Object.GetType() == 0)
									nDmg = (nDmg * TSSReduce) / 100;

								IPlayer.OktayDamageArea(Object,nDmg,32);
							}
							else if (ShadowAOEPVE && Object.GetType() == 1){

								Object.Buff(7, nSkillGrade, 0);
								int nDmg = (IPlayer.GetAttack() * TSSMul) + (nSkillGrade * CTools::Rate(TSSMin, TSSMax));
								IPlayer.OktayDamageArea(Object, nDmg, 32);
							}
							else if (ShadowAOEPVP && Object.GetType() == 0){

								Object.Buff(7, nSkillGrade, 0);
								int nDmg = (IPlayer.GetAttack() * TSSMul) + (nSkillGrade * CTools::Rate(TSSMin, TSSMax));
									nDmg = (nDmg * TSSReduce) / 100;

								IPlayer.OktayDamageArea(Object, nDmg, 32);
							}
						}

						Around = CBaseList::Pop((void*)Around);
					}
				} else {
					IPlayer._ShowBattleMiss(Target, 32);
				}

				IPlayer.SetDirection(Target);
				IPlayer._ShowBattleAnimation(Target, 32);
				IPlayer.DecreaseMana(nMana);
			}
		}
		
	}
}