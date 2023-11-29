void __fastcall SoulDestruction(void *pSkill, void *pPlayer, int pPacket, int pPos)
{
	ISkill ISkill(pSkill);
	int nSkillGrade = ISkill.GetGrade();

	if (!nSkillGrade)
		return;

	IChar IPlayer(pPlayer);

	int Sight = IPlayer.GetBuffRemain(94);
	if (Sight > 0 && Sight <= 10) {
		IPlayer.CouldntExecuteSkill();
		return;
	}

	int nTargetID = 0; char bType = 0; void *pTarget = 0;
	CPacket::Read((char*)pPacket, (char*)pPos, "bd", &bType, &nTargetID);
	int nMana = ISkill.DecreaseMana();

	if (bType >= 2)
		return;

	TargetFind myTarget(bType, 0, nTargetID);
	pTarget = myTarget.getTarget();

	IChar ITarget(pTarget);

	if (pTarget && ITarget.IsValid() && IPlayer.IsValid() && nTargetID != IPlayer.GetID())
	{
		if (IPlayer.GetCurMp() < nMana)
			return;

		if (!IPlayer.IsInRange(ITarget, 300))
			return;

		int MapX = IPlayer.GetX() >> 13;
		int MapY = IPlayer.GetY() >> 13;
		

		int TargetAOE = 0;
		if (SDAOE && SDPVPAOE)
			TargetAOE = 3;
		else if (SDPVPAOE)
			TargetAOE = 2;
		else if (SDAOE)
			TargetAOE = 1;
		
		int GetWisdom = CChar::GetWis((int)IPlayer.GetOffset());

		if (SDRange && (TargetAOE == 3 || (TargetAOE == 2 && ITarget.GetType() == 0) || (TargetAOE == 1 && ITarget.GetType() == 1)) && (IPlayer.GetSpecialty() == 43 || SDLOWAOE) && !MapSD.count((MapX * 1000) + MapY)) {
			int Around = ITarget.GetObjectListAround(SDRange);
			while (Around)
			{
				IChar Object((void*)CBaseList::Offset((void*)Around));
				if (Object.IsValid() && IPlayer.IsValid() && (*(int(__thiscall **)(int, int, DWORD))(*(DWORD *)IPlayer.GetOffset() + 176))((int)IPlayer.GetOffset(), (int)Object.GetOffset(), 0) && (TargetAOE == 3 || (TargetAOE == 2 && Object.GetType() == 0) || (TargetAOE == 1 && Object.GetType() == 1))) {
					int nDmg = ((GetWisdom * 3 + CTools::Rate(MSDMin, MSDMax)) * IPlayer.GetMagic() / 500) * MSDMul;

					if (ITarget.GetType() == 0)
						nDmg = (nDmg * MSDReduce) / 100;

					IPlayer.OktayDamageArea(Object, nDmg, 40);
					IPlayer._ShowBattleAnimation(Object, 40);
				}
				Around = CBaseList::Pop((void*)Around);
			}
			IPlayer.SetDirection(ITarget);
			IPlayer.DecreaseMana(nMana);
		}
		else {
			if ((*(int(__thiscall **)(int, int, DWORD))(*(DWORD *)IPlayer.GetOffset() + 176))((int)IPlayer.GetOffset(), (int)ITarget.GetOffset(), 0)) {
				IPlayer.SetDirection(ITarget);
				int nDmg = ((GetWisdom * ISkill.GetGrade() + CTools::Rate(MSDMin, MSDMax)) * IPlayer.GetMagic() / 500) * MSDMul;

				if (ITarget.GetType() == 0)
					nDmg = (nDmg * MSDReduce) / 100;

				IPlayer.OktayDamageArea(ITarget, nDmg, 40);

				IPlayer._ShowBattleAnimation(ITarget, 40);
				IPlayer.DecreaseMana(nMana);
			}
		}
	}
}

void __fastcall LifeAbsorption(void *pSkill, void *edx, void *pPlayer, char *pPacket, char *pPos)
{
	ISkill ISkill(pSkill);
	int nSkillGrade = ISkill.GetGrade();

	if (!nSkillGrade)
		return;

	IChar IPlayer(pPlayer);
	int nTargetID = 0; char bType = 0; void *pTarget = 0;
	CPacket::Read(pPacket, pPos, "bd", &bType, &nTargetID);
	int nMana = ISkill.GetGrade() * 6 + 20;

	TargetFind myTarget(bType, 0, nTargetID);
	pTarget = myTarget.getTarget();

	if (bType >= 2)
		return;

	IChar ITarget(pTarget);

	if (pTarget && ITarget.IsValid() && IPlayer.IsValid() && nTargetID != IPlayer.GetID())
	{
		if (IPlayer.GetCurMp() < nMana) {
			return;
		}

		if (!IPlayer.IsInRange(ITarget, 300)) {

			return;
		}

		if ((*(int(__thiscall **)(int, int, DWORD))(*(DWORD *)IPlayer.GetOffset() + 176))((int)IPlayer.GetOffset(), (int)ITarget.GetOffset(), 0)) {
			(*(void(__thiscall **)(int, int))(*(DWORD*)ITarget.GetOffset() + 80))((int)ITarget.GetOffset(), (int)IPlayer.GetOffset());

			int nDmg = 0;

			int Check = IPlayer.GetDamage(ISkill.GetIndex(), ITarget.GetOffset());
			if (Check)
				nDmg = Check;
			else {
				nDmg = ((40 * ISkill.GetGrade() + 50) * CChar::GetAttack(IPlayer.GetOffset()) / 50) * ALAMul;

				if (ITarget.GetType() == 0)
					nDmg = (nDmg * ALAReduce) / 100;
			}

			if (IPlayer.CheckHit(ITarget.GetOffset(), 50))
			{
				unsigned int GetAttackSpeed = CChar::GetASpeed((int)IPlayer.GetOffset());
				unsigned int GetASpeedValue = GetAttackSpeed;
				int NormalDamage = 0, DamageArgument = 0, EBDamage = 0, Check = 0, TypeKind = 0, GetType = 0;
				TypeKind = (*(int(__thiscall **)(LONG, void *))(*(DWORD *)ITarget.GetOffset() + 148))((int)ITarget.GetOffset(), IPlayer.GetOffset());
				Check = (*(int(__thiscall**)(LONG, void*, unsigned int, int*, int*, int*, DWORD))(*(DWORD*)ITarget.GetOffset() + 72))((int)ITarget.GetOffset(), IPlayer.GetOffset(), GetASpeedValue * nDmg / GetAttackSpeed, &NormalDamage, &DamageArgument, &EBDamage, 0);
				GetType = Check | 2 * DamageArgument | 4 * TypeKind;

				if (NormalDamage > 0)
					IPlayer.IncreaseHp((NormalDamage * (10 * ISkill.GetGrade() + 20) / 75));

				int SPDmg = 0;
				if (NormalDamage > 1 && ITarget.GetType() == 1) {
					SPDmg = SoulPocketDamage(pPlayer, NormalDamage);
					NormalDamage -= SPDmg;
				}

				CChar::WriteInSight(IPlayer.GetOffset(), 63, "bddbbwwbd", ISkill.GetIndex(), IPlayer.GetID(), ITarget.GetID(), 1, 1, NormalDamage, 0, GetType, SPDmg);
			}
			else {
				IPlayer._ShowBattleMiss(ITarget, ISkill.GetIndex());
			}

			IPlayer.DecreaseMana(nMana);
		}
	}
	
}