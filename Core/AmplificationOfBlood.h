void __fastcall AmplificationOfBlood(IChar IPlayer, int pPacket, int pPos)
{
	int pSkill = IPlayer.GetSkillPointer(38);

	if (IPlayer.IsValid() && pSkill)
	{
		ISkill xSkill((void*)pSkill);
		int nSkillGrade = xSkill.GetGrade();
		int nTargetID = 0; char bType = 0; void *pTarget = 0;
		CPacket::Read((char*)pPacket, (char*)pPos, "bd", &bType, &nTargetID);
		int nMana = (106 + (nSkillGrade * 2));

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
				if (!IPlayer.IsInRange(Target,300)) {
					return;
				}

				int XpSkill = IPlayer.GetSkillPointer(41);

				if (XpSkill)
				{
					ISkill xSkillx((void*)XpSkill);
					if (xSkillx.GetGrade() <= CTools::Rate(0,6)) IPlayer.DecreaseHp((IPlayer.GetCurHp() * 5) /100);
				} else {
					IPlayer.DecreaseHp((IPlayer.GetCurHp() * 5) /100);
				}

				int nDmg = IPlayer.GetDamage(38,Target.GetOffset());
				if(Target.GetType() == 0) nDmg = (nDmg * SHMAOB) / 100;
				IPlayer._ShowBattleAnimation(Target, 38);
				IPlayer.SetDirection(Target);
				IPlayer.DecreaseMana(nMana);

				int Around = Target.GetObjectListAround(1);
				while(Around)
				{
					IChar Object((void*)CBaseList::Offset((void*)Around));
					if (Object.IsValid() && IPlayer.IsValid() && (*(int (__thiscall **)(int, int, DWORD))(*(DWORD *)IPlayer.GetOffset() + 176))((int)IPlayer.GetOffset(), (int)Object.GetOffset(), 0))
						IPlayer.OktayDamageArea(Object,nDmg,38);
			
					Around = CBaseList::Pop((void*)Around);
				}
			}
		} else {
			IPlayer.CouldntExecuteSkill();
		}
		
	}
}