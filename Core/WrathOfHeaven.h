void __fastcall WrathOfHeaven(IChar IPlayer, int pPacket, int pPos)
{
	int pSkill = IPlayer.GetSkillPointer(33);

	if (IPlayer.IsValid() && pSkill)
	{
		ISkill xSkill((void*)pSkill);
		int nSkillGrade = xSkill.GetGrade();
		int nTargetID = 0; char bType = 0; void *pTarget = 0;
		CPacket::Read((char*)pPacket, (char*)pPos, "bd", &bType, &nTargetID);
		int nMana = (IPlayer.GetLevel() + nSkillGrade) * 3 + 50;

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
				if (!IPlayer.IsInRange(Target,300)) {
					
					return;
				}

				if (IPlayer.CheckHit(Target, 30))
				{
					int nDmg = (IPlayer.GetAttack() * TWOHMul) + (nSkillGrade * CTools::Rate(TWOHMin,TWOHMax));

					if (Target.GetType() == 0)
						nDmg = nDmg * TWOHReduce / 100;

					IPlayer.OktayDamageSingle(Target,nDmg,33);
				} else {
					IPlayer._ShowBattleMiss(Target, 33);
				}

				IPlayer.SetDirection(Target);
				IPlayer.DecreaseMana(nMana);
			}
		}
		
	}
}