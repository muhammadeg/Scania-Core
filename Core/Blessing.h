void __fastcall Blessing(IChar IPlayer, int pPacket, int pPos)
{
	int pSkill = IPlayer.GetSkillPointer(69);

	if (IPlayer.IsValid() && pSkill)
	{
		ISkill xSkill((void*)pSkill);
		int nSkillGrade = xSkill.GetGrade();
		int nTargetID = 0; char bType = 0; void *pTarget = 0;
		CPacket::Read((char*)pPacket, (char*)pPos, "bd", &bType, &nTargetID);

		TargetFind myTarget(bType, 0, nTargetID);
		pTarget = myTarget.getTarget();

		if (pTarget && nSkillGrade && IPlayer.IsValid())
		{
			int nMana = nSkillGrade * 10 + 400;
			IChar Target(pTarget);

			if (IPlayer.GetCurMp() < nMana) {

				return;
			}

			if (IPlayer.IsValid() && Target.IsValid())
			{
				if (!IPlayer.IsInRange(Target, 300)) {

					return;
				}

				if (IPlayer.GetID() != Target.GetID())
				{
					Target.Buff(24, (nSkillGrade * 3) + 3, 40);
					Target.RemoveBuffIcon(0, 0, 703, 34);
					CChar::AddMState(Target.GetOffset(), 0, 2147483648);
				}

				IPlayer.Buff(24, (nSkillGrade * 3) + 3, 40);
				IPlayer.RemoveBuffIcon(0, 0, 703, 34);
				CChar::AddMState(IPlayer.GetOffset(), 0, 2147483648);
				IPlayer._ShowBattleAnimation(Target, 69);
				IPlayer.DecreaseMana(nMana);
			}
		}

	}
}

void __fastcall GroupBlessing(IChar IPlayer, int pPacket, int pPos)
{
	int pSkill = IPlayer.GetSkillPointer(77);
	if (IPlayer.IsValid() && pSkill)
	{
		ISkill xSkill((void*)pSkill);
		int nSkillGrade = xSkill.GetGrade();
		int nTargetID = 0; char bType = 0; void *pTarget = 0;
		CPacket::Read((char*)pPacket, (char*)pPos, "bd", &bType, &nTargetID);

		TargetFind myTarget(bType, 0, nTargetID);
		pTarget = myTarget.getTarget();

		if (pTarget && nSkillGrade && IPlayer.IsValid())
		{
			int nMana = nSkillGrade * 10 + 400;
			IChar Target(pTarget);
			int Time = nSkillGrade + 1;
			if (IPlayer.GetCurMp() < nMana) {

				return;
			}

			if (IPlayer.IsValid() && Target.IsValid())
			{
				if (!IPlayer.IsInRange(Target, 300)) {

					return;
				}

				if (Target.IsParty())
				{
					void *Party = (void *)CParty::FindParty(Target.GetPartyID());

					if (Party)
					{
						for (int i = CParty::GetPlayerList(Party); i; i = CBaseList::Pop((void *)i))
						{
							int Members = *(DWORD*)((void*)i);
							IChar IMembers((void*)*(DWORD*)((void*)i));

							if (CChar::IsNormal(Members) && IPlayer.IsValid())
							{
								if (CChar::GetRange((int)IPlayer.GetOffset() + 332, Members + 332) <= 300)
								{
									//	IMembers.Buff(24, Time, 40);
									IMembers.Buff(BuffNames::Blessing, Time, 1);
									//	IMembers.RemoveBuffIcon(0, 0, 703, 34);
									CChar::AddMState(IMembers.GetOffset(), 0, 2147483648);
								}
							}
						}
						CIOObject::Release(Party);
					}
				}
				else {
					IPlayer.SystemMessage("The target is not in a current party group.", TEXTCOLOR_RED);

					return;
				}
				IPlayer._ShowBattleAnimation(Target, 69);
				IPlayer.DecreaseMana(nMana);
			}
		}

	}
}