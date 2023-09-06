void __fastcall CriticalDiffusion(IChar IPlayer)
{
	int pSkill = IPlayer.GetSkillPointer(92);

	if (IPlayer.IsValid() && pSkill)
	{
		ISkill xSkill((void*)pSkill);
		int nSkillGrade = xSkill.GetGrade();
		int Mana = 180 + (1.25 * (nSkillGrade * (IPlayer.GetLevel() + nSkillGrade)));

		if (IPlayer.GetCurMp() <= Mana)
			return;

		if (!ScaniaLicense)
			return;

		IPlayer.DecreaseMana(Mana);
		IPlayer._ShowBattleAnimation(IPlayer, 92);

		if(IPlayer.IsValid())
		{
			if (IPlayer.IsParty())
			{
				void *Party = (void *)CParty::FindParty(IPlayer.GetPartyID());

				if (Party)
				{
					for (int i = CParty::GetPlayerList(Party); i; i = CBaseList::Pop((void *)i))
					{
						int Members = *(DWORD*)((void*)i);
						IChar IMembers((void*)*(DWORD*)((void*)i));

						if (CChar::IsNormal(Members) && IPlayer.IsValid())
						{
							if (CChar::GetRange((int)IPlayer.GetOffset() + 332, Members + 332) <= 300 && !IMembers.GetBuffValue(BuffNames::CDTime))
							{
								IMembers.SetBuffIcon(1000*(5+(nSkillGrade*5)), 0, 4245, 953);
								IMembers.IncreaseCritRate((nSkillGrade*10)+10);
								IMembers.IncreaseCritDamage((nSkillGrade*10)+10);
								IMembers.UpdateBuff(BuffNames::CDType,BuffNames::BuffTime,xSkill.GetGrade());
								IMembers.UpdateBuff(BuffNames::CDTime,BuffNames::BuffTime, GetTickCount()+(1000*(5+(nSkillGrade*5))));
							}
						}
					}
					CIOObject::Release(Party);
				}
			} else {
				if (!IPlayer.GetBuffValue(BuffNames::CDTime))
				{
					IPlayer.SetBuffIcon(1000*(5+(nSkillGrade*5)), 0, 4245, 953);
					IPlayer.IncreaseCritRate((nSkillGrade*10)+10);
					IPlayer.IncreaseCritDamage((nSkillGrade*10)+10);
					IPlayer.UpdateBuff(BuffNames::CDType,BuffNames::BuffTime,xSkill.GetGrade());
					IPlayer.UpdateBuff(BuffNames::CDTime,BuffNames::BuffTime, GetTickCount()+(1000*(5+(nSkillGrade*5))));
				}
			}
		}
	}
}