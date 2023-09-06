void __fastcall ShoutOfFightingSpirit(IChar IPlayer)
{
	if (IPlayer.IsOnline())
	{
		int pSkill = IPlayer.GetSkillPointer(92);

		if (IPlayer.IsValid() && pSkill)
		{
			ISkill xSkill((void*)pSkill);
			int Mana = 180 + (1.25 * (xSkill.GetGrade() * (IPlayer.GetLevel() + xSkill.GetGrade())));

			if (IPlayer.GetCurMp() <= Mana)
				return;

			IPlayer.DecreaseMana(Mana);
			IPlayer._ShowBattleAnimation(IPlayer, 92);

			if (IPlayer.IsValid())
			{
				if (IPlayer.IsParty())
				{
					void *Party = (void *)CParty::FindParty(IPlayer.GetPartyID());

					if (Party)
					{
						for (int i = CParty::GetPlayerList(Party); i; i = CBaseList::Pop((void*)i))
						{
							int Members = *(DWORD*)((void*)i);
							IChar IMembers((void*)*(DWORD*)((void*)i));

							if (CChar::IsNormal(Members) && IPlayer.IsValid())
							{
								if (CChar::GetRange((int)IPlayer.GetOffset() + 332, Members + 332) <= 300 && !IMembers.GetBuffValue(BuffNames::SOFSTime))
								{
									IMembers.SetBuffIcon(1000*(4+(xSkill.GetGrade()*3)), 0, 4243, 951);
									IMembers.AddMaxAttack(xSkill.GetGrade()*SOFSMAX);
									IMembers.AddMinAttack(xSkill.GetGrade()*SOFSMIN);
									IMembers.UpdateBuff(BuffNames::SOFSType,BuffNames::BuffTime,xSkill.GetGrade());
									IMembers.UpdateBuff(BuffNames::SOFSTime,BuffNames::BuffTime,GetTickCount()+(1000*(4+(xSkill.GetGrade()*3))));
					
								}
							}
						}
						CIOObject::Release(Party);
					}
				} else {
					if (!IPlayer.GetBuffValue(BuffNames::SOFSTime))
					{
						IPlayer.SetBuffIcon(1000*(4+(xSkill.GetGrade()*3)), 0, 4243, 951);
						IPlayer.AddMaxAttack(xSkill.GetGrade()*SOFSMAX);
						IPlayer.AddMinAttack(xSkill.GetGrade()*SOFSMIN);
						IPlayer.UpdateBuff(BuffNames::SOFSType,BuffNames::BuffTime,xSkill.GetGrade());
						IPlayer.UpdateBuff(BuffNames::SOFSTime,BuffNames::BuffTime,GetTickCount()+(1000*(4+(xSkill.GetGrade()*3))));
					}
				}
			}
		}
	}
}