void __fastcall TheSoulsPenance(IChar IPlayer, int pPacket, int pPos)
{
	int pSkill = IPlayer.GetSkillPointer(22);

	if (IPlayer.IsValid() && pSkill)
	{
		ISkill xSkill((void*)pSkill);
		int nSkillGrade = xSkill.GetGrade();
		int nTargetID = 0; char bType = 0; void *pTarget = 0;
		CPacket::Read((char*)pPacket, (char*)pPos, "bd", &bType, &nTargetID);
		int nMana = (60 + (nSkillGrade * 2));

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

				int SetTime = 3;
				int nDmg = IPlayer.GetDamage(22,Target.GetOffset());
				if(Target.GetType() == 0) nDmg = (nDmg * SHMTSP) / 100;
				IPlayer._ShowBattleAnimation(Target, 22);
				IPlayer.SetDirection(Target);
				IPlayer.DecreaseMana(nMana);
				int XpSkill = IPlayer.GetSkillPointer(24);
				int YpSkill = IPlayer.GetSkillPointer(48);

				if (XpSkill && Target.GetType() == 1)
				{
					ISkill xSkillx((void*)XpSkill);
					SetTime += xSkillx.GetGrade()/2;
				}

				if (YpSkill)
				{
					ISkill ySkilly((void*)YpSkill);
					nDmg += (ySkilly.GetGrade() * 50);
				}

				int Around = Target.GetObjectListAround(3);
				while(Around)
				{
					IChar Object((void*)CBaseList::Offset((void*)Around));

					if (Object.IsValid() && IPlayer.IsValid() && (*(int (__thiscall **)(int, int, DWORD))(*(DWORD *)IPlayer.GetOffset() + 176))((int)IPlayer.GetOffset(), (int)Object.GetOffset(), 0))
					{
						IPlayer.OktayDamageArea(Object,nDmg,22);
						if(nDmg && (int)Object.GetOffset() != (int)IPlayer.GetOffset()){
							if(Object.GetType() == 1)
								Object.Buff(400,SetTime,nDmg*0.65);
							else
								Object.Buff(400,SetTime,nDmg*0.38);
						}
					}
					
					Around = CBaseList::Pop((void*)Around);
				}
				//IPlayer.Buff(3124,SetTime+1,0);
			}
		} else {
			IPlayer.CouldntExecuteSkill();
		}
		
	}
}