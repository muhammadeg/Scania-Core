void __fastcall Doggebi(IChar IPlayer, int pPacket, int pPos)
{
	int pSkill = IPlayer.GetSkillPointer(92);

	if (IPlayer.IsValid() && pSkill)
	{
		ISkill xSkill((void*)pSkill);
		int nSkillGrade = xSkill.GetGrade();
		int nTargetID = 0; char bType = 0; void *pTarget = 0;
		CPacket::Read((char*)pPacket, (char*)pPos, "bd", &bType, &nTargetID);
		int nMana = (170 + (nSkillGrade * 2));

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

			if(IPlayer.IsValid() && Target.IsValid())
			{
				if (!IPlayer.IsInRange(Target, 300)) {
					
					return;
				}
				
				int nDmg = IPlayer.GetDamage(92,Target.GetOffset());
				if(Target.GetType() == 0) nDmg = (nDmg * SHMD) / 100;

				IPlayer.OktayDamageSingle(Target, nDmg, 92);
				IPlayer.SetDirection(Target);
				IPlayer.DecreaseMana(nMana);
			}
		} else {
			IPlayer.CouldntExecuteSkill();
		}
		
	}
}