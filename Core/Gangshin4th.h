void __fastcall Gangshin4th(IChar IPlayer, int pPacket, int pPos)
{
	int pSkill = IPlayer.GetSkillPointer(93);

	if (IPlayer.IsValid() && pSkill)
	{
		ISkill xSkill((void*)pSkill);
		int nSkillGrade = xSkill.GetGrade();
		int Mana = 10;

		if (IPlayer.GetCurMp() <= Mana)
			return;

		IPlayer.DecreaseMana(Mana);
		IPlayer._ShowBattleAnimation(IPlayer, 93);

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
							if (CChar::GetRange((int)IPlayer.GetOffset() + 332, Members + 332) <= 300 && !IMembers.IsBuff(414))
							{
								int Adding = IPlayer.GetDamage(93, IPlayer.GetOffset());
								IMembers.SetBuffIcon(1000*((nSkillGrade*60)+240), 0, 9109, 1018);
								IMembers.AddAgi(Adding);
								IMembers.AddStr(Adding);
								IMembers.AddHp(Adding);
								IMembers.AddWis(Adding);
								IMembers.AddInt(Adding);
								IMembers.Buff(413,(nSkillGrade*60)+240, (int)IPlayer.GetOffset());
								IMembers.Buff(414,(nSkillGrade*100)+240,Adding);
							}
						}
					}
					CIOObject::Release(Party);
				}
			} else {
				if (!IPlayer.IsBuff(414))
				{
					int Adding = IPlayer.GetDamage(93, IPlayer.GetOffset());
					IPlayer.SetBuffIcon(1000*((nSkillGrade*60)+240), 0, 9109, 1018);
					IPlayer.AddAgi(Adding);
					IPlayer.AddStr(Adding);
					IPlayer.AddHp(Adding);
					IPlayer.AddWis(Adding);
					IPlayer.AddInt(Adding);
					IPlayer.Buff(413,(nSkillGrade*60)+240, (int)IPlayer.GetOffset());
					IPlayer.Buff(414,(nSkillGrade*100)+240, Adding);
				}
			}
		}
	}
}