void __fastcall JigukKing(IChar IPlayer, int pPacket, int pPos)
{
	int pSkill = IPlayer.GetSkillPointer(36);

	if (IPlayer.IsValid() && pSkill)
	{
		ISkill xSkill((void*)pSkill);
		int nSkillGrade = xSkill.GetGrade();
		int Mana = 300 + (nSkillGrade * 2);
		int ExtraTime = 0;
		int XpSkill = IPlayer.GetSkillPointer(40);

		if (XpSkill)
		{
			ISkill xSkillx((void*)XpSkill);
			ExtraTime = 10 * xSkillx.GetGrade();
		}

		if (IPlayer.GetCurMp() <= Mana)
			return;

		IPlayer.DecreaseMana(Mana);
		IPlayer._ShowBattleAnimation(IPlayer, 50);

		if(IPlayer.IsValid())
		{
			int Dmg = IPlayer.GetDamage(36, IPlayer.GetOffset());
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
							if (CChar::GetRange((int)IPlayer.GetOffset() + 332, Members + 332) <= 300 && !IMembers.IsBuff(402))
							{
								IMembers.SetBuffIcon(1000*((nSkillGrade*60)+ExtraTime), 0, 9104, 1013);
								IMembers.IncreaseMaxHp(Dmg);
								IMembers.Buff(401,(nSkillGrade*60)+ExtraTime, (int)IPlayer.GetOffset());
								IMembers.Buff(402,nSkillGrade*100, Dmg);
							}
						}
					}
					CIOObject::Release(Party);
				}
			} else {
				if (!IPlayer.IsBuff(402))
				{
					IPlayer.SetBuffIcon(1000*((nSkillGrade*60)+ExtraTime), 0, 9104, 1013);
					IPlayer.IncreaseMaxHp(Dmg);
					IPlayer.Buff(401,(nSkillGrade*60)+ExtraTime, (int)IPlayer.GetOffset());
					IPlayer.Buff(402,nSkillGrade*100, Dmg);
				}
			}
		}
	}
}