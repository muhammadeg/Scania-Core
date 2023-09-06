void __fastcall ExplodingSpirit(IChar IPlayer, int pPacket, int pPos)
{
	int pSkill = IPlayer.GetSkillPointer(47);

	if (!IPlayer.IsBuff(406))
		return;

	if (IPlayer.IsValid() && pSkill)
	{
		ISkill xSkill((void*)pSkill);
		int nSkillGrade = xSkill.GetGrade();
		int nTargetID = 0; char bType = 0; void *pTarget = 0;
		CPacket::Read((char*)pPacket, (char*)pPos, "bd", &bType, &nTargetID);
		int nMana = (120 + (nSkillGrade * 2)); int ExtraDamage = 0;
		int XpSkill = IPlayer.GetSkillPointer(32);

		if (XpSkill)
		{
			ISkill xSkillx((void*)XpSkill);
			ExtraDamage = 5 * xSkillx.GetGrade();
		}

		if (IPlayer.IsBuff(412))
		{
			ExtraDamage += IPlayer.GetBuffValue(412);
		}

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
				if (!IPlayer.IsInRange(Target, 300)) {
					
					return;
				}

				int nDmg = IPlayer.GetDamage(47,Target.GetOffset());
				IPlayer._ShowBattleAnimation(Target, 47);
				IPlayer.SetDirection(Target);
				IPlayer.DecreaseMana(nMana);
				IPlayer.IncreaseHp(nDmg);

				int Around = Target.GetObjectListAround(3);
				while(Around)
				{
					IChar Object((void*)CBaseList::Offset((void*)Around));

					if (Object.IsValid() && IPlayer.IsValid() && (*(int(__thiscall **)(int, int, DWORD))(*(DWORD *)IPlayer.GetOffset() + 176))((int)IPlayer.GetOffset(), (int)Object.GetOffset(), 0))
						IPlayer.OktayDamageArea(Object, nDmg, 47);

					Around = CBaseList::Pop((void*)Around);
				}
			}
		} else {
			IPlayer.CouldntExecuteSkill();
		}
		
	}
}