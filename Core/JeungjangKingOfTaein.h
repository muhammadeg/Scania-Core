void __fastcall JeungjangKingOfTaein(IChar IPlayer, int pPacket, int pPos)
{
	int pSkill = IPlayer.GetSkillPointer(51);

	if (IPlayer.IsValid() && pSkill)
	{
		ISkill xSkill((void*)pSkill);
		int nSkillGrade = xSkill.GetGrade();
		int Mana = 500 + (nSkillGrade * 2);
		int ExtraTime = 0;
		int XpSkill = IPlayer.GetSkillPointer(53);

		if (XpSkill)
		{
			ISkill xSkillx((void*)XpSkill);
			ExtraTime = 10 * xSkillx.GetGrade();
		}

		if (IPlayer.GetCurMp() <= Mana)
			return;

		IPlayer.DecreaseMana(Mana);
		IPlayer._ShowBattleAnimation(IPlayer, 51);

		if(IPlayer.IsValid())
		{
			int Dmg = IPlayer.GetDamage(51, IPlayer.GetOffset());
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
							if (CChar::GetRange((int)IPlayer.GetOffset() + 332, Members + 332) <= 300 && !IMembers.IsBuff(408))
							{
								IMembers.SetBuffIcon(1000*((nSkillGrade*60)+ExtraTime), 0, 9108, 1017);
								IMembers.AddMaxAttack(Dmg);
								IMembers.AddMinAttack(Dmg);
								IMembers.Buff(407,(nSkillGrade*60)+ExtraTime, (int)IPlayer.GetOffset());
								IMembers.Buff(408,nSkillGrade*100, Dmg);
							}
						}
					}
					CIOObject::Release(Party);
				}
			} else {
				if (!IPlayer.IsBuff(408))
				{
					IPlayer.SetBuffIcon(1000*((nSkillGrade*60)+ExtraTime), 0, 9108, 1017);
					IPlayer.AddMaxAttack(Dmg);
					IPlayer.AddMinAttack(Dmg);
					IPlayer.Buff(407,(nSkillGrade*60)+ExtraTime, (int)IPlayer.GetOffset());
					IPlayer.Buff(408,nSkillGrade*100, Dmg);
				}
			}
		}
	}
}