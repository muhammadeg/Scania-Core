void __fastcall DualShadow(IChar IPlayer, int pPacket, int pPos)
{
	int pSkill = IPlayer.GetSkillPointer(12);

	if (IPlayer.IsValid() && pSkill)
	{
		ISkill xSkill((void*)pSkill);
		int nSkillGrade = xSkill.GetGrade();
		int nTargetID = 0; char bType = 0; void *pTarget = 0;
		CPacket::Read((char*)pPacket, (char*)pPos, "bd", &bType, &nTargetID);

		TargetFind myTarget(bType, 0, nTargetID);
		pTarget = myTarget.getTarget();

		if (bType >= 2)
			return;

		if (pTarget && IPlayer.IsValid() && nSkillGrade)
		{
			IChar Target(pTarget);
			int nMana = nSkillGrade * 10 + 10;

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

				if (IPlayer.CheckHit(Target, 10))
				{
					IPlayer.AddOTP(nSkillGrade * 2);
					IPlayer.AddEva(nSkillGrade * 3);
					IPlayer.SetBuffIcon(8000, 0, 2012, 214);
					IPlayer.Buff(354, 8, 0);
					IPlayer.Buff(355, 13, 0);

					if (Target.GetType() == 1) {
						int Around = Target.GetObjectListAround(5);
						while (Around)
						{
							IChar Object((void*)CBaseList::Offset((void*)Around));

							if (Object.IsValid() && Object.GetType() == 1 && IPlayer.IsValid() && nTargetID != IPlayer.GetID() && (*(int(__thiscall **)(int, int, DWORD))(*(DWORD *)IPlayer.GetOffset() + 176))((int)IPlayer.GetOffset(), (int)Object.GetOffset(), 0))
								IPlayer.OktayDamageSingle(Object, IPlayer.GetAttack() * 2, 12);

							Around = CBaseList::Pop((void*)Around);
						}
					}
					else
					if (Target.GetType() == 0)
						IPlayer.OktayDamageSingle(Target, IPlayer.GetAttack() * 2, 12);

					//if (Target.GetType() == 0 || Target.GetType() == 1)
					//	IPlayer.OktayDamageSingle(Target, IPlayer.GetAttack() * 2, 12);

					IPlayer._ShowBattleAnimation(Target, 12);
				}
				else {
					IPlayer._ShowBattleMiss(Target, 12);
				}

				IPlayer.SetDirection(Target);
				IPlayer._ShowBattleAnimation(Target, 12);
				IPlayer.DecreaseMana(nMana);
			}
		}
		else {
			IPlayer.CouldntExecuteSkill();
		}

	}
}