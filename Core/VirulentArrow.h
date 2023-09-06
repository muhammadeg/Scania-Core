void __fastcall VirulentArrow(IChar IPlayer, int pPacket, int pPos)
{
	int pSkill = IPlayer.GetSkillPointer(50);

	if (IPlayer.IsValid() && pSkill)
	{
		ISkill xSkill((void*)pSkill);
		int nSkillGrade = xSkill.GetGrade();
		int nTargetID = 0; char bType = 0; void *pTarget = 0;
		CPacket::Read((char*)pPacket, (char*)pPos, "bd", &bType, &nTargetID);
		int nMana = (int)(((((nSkillGrade - 1) + 25) * nSkillGrade) + 230) * 0.98);

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

				if (!CPlayer::RemoveItem(IPlayer.GetOffset(),9,360,2))
					return;

				IPlayer.DecreaseMana(nMana);
				IPlayer._ShowBattleAnimation(Target, 50);
				IPlayer.SetDirection(Target);
				int nDmg = (IPlayer.GetAttack() * AVAMul) + (nSkillGrade * CTools::Rate(AVAMin, AVAMax));

				int nPoison = (IPlayer.GetAttack() * AVAMul) + (nSkillGrade * CTools::Rate(AVAPoisonMin, AVAPoisonMax));

				if (AVAMin == AVAPoisonMin && AVAMax == AVAPoisonMax)
					nPoison = nDmg;

				bool isSkillEdit = (IPlayer.GetProperty(PlayerProperty::SkillsEdit) == 50);

				int Around = Target.GetObjectListAround(4);
				while(Around)
				{
					IChar Object((void*)CBaseList::Offset((void*)Around));

					if (Object.IsValid() && IPlayer.IsValid() && (*(int (__thiscall **)(int, int, DWORD))(*(DWORD *)IPlayer.GetOffset() + 176))((int)IPlayer.GetOffset(), (int)Object.GetOffset(), 0))
					{
						if (!(Object.GetType() == 1 && (Object.GetMobIndex() >= 1025 && Object.GetMobIndex() <= 1028) || Object.GetOffset() == GuildRaid::Boss)) {

							if (Object.GetType() == 0) {
								nDmg = nDmg * AVAReduce / 100;
								nPoison = nPoison * AVAReduce / 100;
							}

							if (Object.GetType() == 0)
								IPlayer.OktayDamageArea(Object, IPlayer.GetAttack(), 50);

							if (Object.GetType() == 1)
								IPlayer.OktayDamageArea(Object, IPlayer.GetAttack()*xSkill.GetGrade(), 50);

							int SDmg = 0;

							if (isSkillEdit)
								SDmg = IPlayer.GetDamage(50, Object.GetOffset());

							Object.Buff(11, 10, SDmg > 0 ? SDmg : nPoison);
						}
					}

					Around = CBaseList::Pop((void*)Around);
				}
			}
		}
		
	}
}