void __fastcall CriticalStrike(IChar IPlayer, int pPacket, int pPos)
{
	int pSkill = IPlayer.GetSkillPointer(90);

	if (IPlayer.IsValid() && pSkill)
	{
		ISkill xSkill((void*)pSkill);
		int nSkillGrade = xSkill.GetGrade();
		int nTargetID = 0; char bType = 0; void *pTarget = 0;
		CPacket::Read((char*)pPacket, (char*)pPos, "bd", &bType, &nTargetID);
		int nMana = (50 + (3 * (IPlayer.GetLevel() + nSkillGrade)));

		TargetFind myTarget(bType, 0, nTargetID);
		pTarget = myTarget.getTarget();

		if (bType >= 2)
			return;
		
		if (pTarget && nSkillGrade && IPlayer.IsValid())
		{
			if (IPlayer.GetCurMp() < nMana) {
				
				return;
			}

			IChar Target(pTarget);

			if (IPlayer.IsValid() && Target.IsValid())
			{
				if (pTarget == IPlayer.GetOffset()) {
					
					return;
				}

				if (!IPlayer.IsInRange(Target, 300)) {
					
					return;
				}

				int nDmg = (IPlayer.GetAttack() * NCSMul) + (nSkillGrade * CTools::Rate(NCSMin,NCSMax));

				if (Target.GetType() == 0)
					nDmg = nDmg * NCSReduce / 100;
				
				IPlayer.OktayDamageSingle(Target,nDmg,90);
				IPlayer.SetDirection(Target);
				IPlayer.DecreaseMana(nMana);
				IPlayer.OktayDamageSingle(Target,nDmg,90);
			}
		} else {
			IPlayer.CouldntExecuteSkill();
		}
		
	}
}