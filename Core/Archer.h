void __fastcall ContinueArrowExplosion(IChar IPlayer)
{
	if (IPlayer.IsValid())
	{
		IPlayer.CancelBuff(300);
		void *pTarget = (void*)IPlayer.GetProperty(PlayerProperty::ContinueSkillPlayerTarget);
		int nSkillGrade = IPlayer.GetProperty(PlayerProperty::ContinueSkillPlayerSkillGrade);

		if (nSkillGrade && pTarget && IPlayer.GetProperty(PlayerProperty::ContinueSkillPlayerSkillCount))
		{
			int Count = IPlayer.GetProperty(PlayerProperty::ContinueSkillPlayerSkillCount);
			IPlayer.SetProperty(PlayerProperty::ContinueSkillPlayerSkillCount, Count - 1);

			IChar Target(pTarget);

			if (IPlayer.IsValid() && Target.IsValid())
			{
				if (!IPlayer.IsInRange(Target, 300))
				{
					ResetContinueSkill(IPlayer);
					return;
				}

				int Around = Target.GetObjectListAround(3);

				while (Around)
				{
					IChar Object((void*)CBaseList::Offset((void*)Around));

					if (Object.IsValid() && IPlayer.IsValid() && (*(int(__thiscall **)(int, int, DWORD))(*(DWORD *)IPlayer.GetOffset() + 176))((int)IPlayer.GetOffset(), (int)Object.GetOffset(), 0))
					{
						int nDmg = (IPlayer.GetAttack() * AAEMul) + (nSkillGrade * CTools::Rate(AAEMin, AAEMax));

						if (Object.GetType() == 0)
							nDmg = (nDmg * AAEReduce) / 100;

						IPlayer.OktayDamageArea(Object, nDmg, 49);
					}

					Around = CBaseList::Pop((void*)Around);
				}
			}
		}
	}

	ResetContinueSkill(IPlayer);
	return;
}

void __fastcall ContinueArrowExplosion(void* Player)
{
	IChar IPlayer(Player);
	return ContinueArrowExplosion(IPlayer);
}

void __fastcall ArrowExplosion(IChar IPlayer, int pPacket, int pPos)
{
	int pSkill = IPlayer.GetSkillPointer(49);

	if (IPlayer.IsValid() && pSkill)
	{
		ISkill xSkill((void*)pSkill);
		int nSkillGrade = xSkill.GetGrade();
		int nTargetID = 0; char bType = 0; void *pTarget = 0;
		CPacket::Read((char*)pPacket, (char*)pPos, "bd", &bType, &nTargetID);
		int nMana = 20 + (IPlayer.GetLevel() * 4);

		TargetFind myTarget(bType, 0, nTargetID);
		pTarget = myTarget.getTarget();

		if (bType >= 2)
			return;

		if (IPlayer.IsValid() && pTarget && nSkillGrade)
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

				IPlayer.DecreaseMana(nMana);
				IPlayer.SetDirection(Target);
				IPlayer._ShowBattleAnimation(Target, 49);
				IPlayer.Buff(300, 5, 0);
				Target.AddFxToTarget("davi_ef131_04", 1, 0, 0);

				if (!IPlayer.GetProperty(PlayerProperty::ContinueSkillPlayerSkillID))
					IPlayer.SetContinueSkill();

				IPlayer.SetProperty(PlayerProperty::ContinueSkillPlayerSkillID, 49);
				IPlayer.SetProperty(PlayerProperty::ContinueSkillPlayerTarget, (int)Target.GetOffset());
				IPlayer.SetProperty(PlayerProperty::ContinueSkillPlayerSkillGrade, nSkillGrade);
				IPlayer.SetProperty(PlayerProperty::ContinueSkillPlayerSkillCount, 1);
				IPlayer.SetProperty(PlayerProperty::ContinueSkillPlayerSkillDelay, GetTickCount() + (AETime * 1000));

				if (Target.IsValid() && Target.GetType() == 1 && Target.GetMobTanker() && Target.GetMobTanker() != (int)IPlayer.GetOffset())
					Target.SetMobHostility(0);

				if (Target.GetType() == 1)
					IPlayer.OktayDamageSingle(Target, CTools::Rate(500, 750), 42);

				if (Target.IsValid() && Target.GetType() == 1 && Target.GetMobTanker() == (int)IPlayer.GetOffset())
					Target.SetMobHostility(25000);
			}
		}

	}
}
void __fastcall ContinueArrowRain(IChar IPlayer)
{
	if (IPlayer.IsValid())
	{
		int nSkillGrade = IPlayer.GetProperty(PlayerProperty::ContinueSkillPlayerSkillGrade);
		void *pTarget = (void*)IPlayer.GetProperty(PlayerProperty::ContinueSkillPlayerTarget);

		if (pTarget && nSkillGrade && IPlayer.GetProperty(PlayerProperty::ContinueSkillPlayerSkillCount))
		{
			IChar Target(pTarget);
			int Count = IPlayer.GetProperty(PlayerProperty::ContinueSkillPlayerSkillCount);
			IPlayer.SetProperty(PlayerProperty::ContinueSkillPlayerSkillCount, Count - 1);

			if (!IPlayer.IsValid() || !Target.IsValid())
			{
				ResetContinueSkill(IPlayer);
				return;
			}

			if (IPlayer.GetProperty(PlayerProperty::ContinueSkillPlayerX) && IPlayer.GetProperty(PlayerProperty::ContinueSkillPlayerY) && IPlayer.IsMoved(IPlayer.GetProperty(PlayerProperty::ContinueSkillPlayerX), IPlayer.GetProperty(PlayerProperty::ContinueSkillPlayerY)))
			{
				ResetContinueSkill(IPlayer);
				return;
			}

			int Around = Target.GetObjectListAround(3);

			while (Around)
			{
				IChar Object((void*)CBaseList::Offset((void*)Around));

				if (Object.IsValid() && IPlayer.IsValid() && (*(int(__thiscall **)(int, int, DWORD))(*(DWORD *)IPlayer.GetOffset() + 176))((int)IPlayer.GetOffset(), (int)Object.GetOffset(), 0))
				{
					int nDmg = (IPlayer.GetAttack() * AARMul) + (nSkillGrade * CTools::Rate(AARMin, AARMax));

					if (Object.GetType() == 0)
						nDmg = (nDmg * AARReduce) / 100;

					IPlayer.OktayDamageArea(Object, nDmg, 47);
				}

				Around = CBaseList::Pop((void*)Around);
			}

			if (IPlayer.IsOnline())
				IPlayer.SetProperty(PlayerProperty::ContinueSkillPlayerSkillDelay, GetTickCount() + 2000);

			if (IPlayer.IsOnline() && IPlayer.GetProperty(PlayerProperty::ContinueSkillPlayerSkillCount) == 0)
				ResetContinueSkill(IPlayer);

			return;
		}
	}

	ResetContinueSkill(IPlayer);
	return;
}

void __fastcall ArrowRain(IChar IPlayer, int pPacket, int pPos)
{
	int pSkill = IPlayer.GetSkillPointer(47);

	if (IPlayer.IsValid() && pSkill)
	{
		int x = 0, y = 0;
		CPacket::Read((char*)pPacket, (char*)pPos, "dd", &x, &y);
		ISkill xSkill((void*)pSkill);
		int nSkillGrade = xSkill.GetGrade();
		int nMana = 20 + (IPlayer.GetLevel() * 4);

		if (x <= 0 || y <= 0)
			return;

		if (nSkillGrade && IPlayer.IsValid())
		{
			if (IPlayer.GetCurMp() < nMana)
				return;

			IPlayer.DecreaseMana(nMana);
			IPlayer._ShowBattleAnimation(IPlayer, 47);
			int *GetSetXY = new int[2];
			GetSetXY[0] = x;
			GetSetXY[1] = y;
			int check = CMonsterMagic::Create(567, IPlayer.GetMap(), (int)GetSetXY, 1, (int)IPlayer.GetOffset(), 0, 10000);
			delete[] GetSetXY;


			if (!IPlayer.GetProperty(PlayerProperty::ContinueSkillPlayerSkillID))
				IPlayer.SetContinueSkill();
			IPlayer.SetProperty(PlayerProperty::ContinueSkillPlayerSkillID, 47);
			IPlayer.SetProperty(PlayerProperty::ContinueSkillPlayerTarget, check);
			IPlayer.SetProperty(PlayerProperty::ContinueSkillPlayerSkillGrade, nSkillGrade);
			IPlayer.SetProperty(PlayerProperty::ContinueSkillPlayerSkillCount, 5);
			IPlayer.SetProperty(PlayerProperty::ContinueSkillPlayerSkillDelay, 0);
			IPlayer.SetProperty(PlayerProperty::ContinueSkillPlayerX, IPlayer.GetX());
			IPlayer.SetProperty(PlayerProperty::ContinueSkillPlayerY, IPlayer.GetY());
		}
	}
}
void __fastcall ArrowsOfTheMaster(IChar IPlayer, int pPacket, int pPos)
{
	int pSkill = IPlayer.GetSkillPointer(92);

	if (IPlayer.IsValid() && pSkill)
	{
		ISkill xSkill((void*)pSkill);
		int nSkillGrade = xSkill.GetGrade();
		int nTargetID = 0, nMana = 0; char bType = 0; void *pTarget = 0;
		CPacket::Read((char*)pPacket, (char*)pPos, "bd", &bType, &nTargetID);

		TargetFind myTarget(bType, 0, nTargetID);
		pTarget = myTarget.getTarget();

		if (bType >= 2)
			return;

		if (pTarget && nSkillGrade && IPlayer.IsValid())
		{
			nMana = (1.85 * (200 + (nSkillGrade * (20 + (nSkillGrade - 1)))));
			IChar Target(pTarget);

			if (pTarget == IPlayer.GetOffset()) {

				return;
			}

			if (IPlayer.GetCurMp() < nMana){

				return;
			}

			if (IPlayer.IsValid() && Target.IsValid())
			{
				if (!IPlayer.IsInRange(Target, 300)) {

					return;
				}

				int Around = Target.GetObjectListAround(3);

				while (Around)
				{
					IChar Object((void*)CBaseList::Offset((void*)Around));

					if (Object.IsValid() && IPlayer.IsValid() && (*(int(__thiscall **)(int, int, DWORD))(*(DWORD *)IPlayer.GetOffset() + 176))((int)IPlayer.GetOffset(), (int)Object.GetOffset(), 0))
					{
						int nDmg = (IPlayer.GetAttack() * NAOTMMul) + (nSkillGrade * CTools::Rate(NAOTMMin, NAOTMMax));

						if (Object.GetType() == 0)
							nDmg = (nDmg * NAOTMReduce) / 100;

						IPlayer.OktayDamageArea(Object, nDmg, 92);
					}

					Around = CBaseList::Pop((void*)Around);
				}

				IPlayer.DecreaseMana(nMana);
				IPlayer.SetDirection(Target);
				IPlayer._ShowBattleAnimation(Target, 92);
			}
		}


	}
}
void __fastcall CombativeSpirit(IChar IPlayer, int pPacket, int pPos)
{
	int pSkill = IPlayer.GetSkillPointer(51);

	if (IPlayer.IsValid() && pSkill)
	{
		int TargetAOE = 0;
		if (ACAOE && ACPVPAOE)
			TargetAOE = 3;
		else if (ACPVPAOE)
			TargetAOE = 2;
		else if (ACAOE)
			TargetAOE = 1;

		ISkill xSkill((void*)pSkill);
		int nSkillGrade = xSkill.GetGrade();
		int nTargetID = 0; char bType = 0; void *pTarget = 0;
		CPacket::Read((char*)pPacket, (char*)pPos, "bd", &bType, &nTargetID);

		TargetFind myTarget(bType, 0, nTargetID);
		pTarget = myTarget.getTarget();

		if (bType >= 2)
			return;

		if (IPlayer.IsValid() && pTarget && nSkillGrade)
		{
			IChar Target(pTarget);
			int nMana = (int)(((((nSkillGrade - 1) + 20) * nSkillGrade) + 200) * 1.85);

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

				IPlayer.DecreaseMana(nMana);

				if (IPlayer.CheckHit(Target, 30))
				{
					IPlayer.SetDirection(Target);
					IPlayer._ShowBattleAnimation(Target, 51);
					int Around = Target.GetObjectListAround(ACAOERange);

					while (Around)
					{
						IChar Object((void*)CBaseList::Offset((void*)Around));

						if (Object.IsValid() && IPlayer.IsValid() && (*(int(__thiscall **)(int, int, DWORD))(*(DWORD *)IPlayer.GetOffset() + 176))((int)IPlayer.GetOffset(), (int)Object.GetOffset(), 0))
						{
							int nDmg = (IPlayer.GetAttack() * ACSMul) + (nSkillGrade * CTools::Rate(ACSMin, ACSMax));

							if (Target.GetType() == 0)
								nDmg = (nDmg * ACSReduce) / 100;

							if (ACAOE && (TargetAOE == 3 || (TargetAOE && !Target.IsValid()) || (TargetAOE == 2 && Target.GetType() == 0) || (TargetAOE == 1 && Target.GetType() == 1)))
								IPlayer.OktayDamageArea(Object, nDmg, 51);
							else if
								(Object.GetX() <= max(IPlayer.GetX(), Target.GetX()) && Object.GetX() >= min(IPlayer.GetX(), Target.GetX()) && Object.GetY() <= max(IPlayer.GetY(), Target.GetY()) && Object.GetY() >= min(IPlayer.GetY(), Target.GetY()))
								IPlayer.OktayDamageArea(Object, nDmg, 51);

						}

						Around = CBaseList::Pop((void*)Around);
					}
				}
				else {
					IPlayer._ShowBattleMiss(Target, 51);
				}
			}
		}

	}
}
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

				if (!CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 360, 2))
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
				while (Around)
				{
					IChar Object((void*)CBaseList::Offset((void*)Around));

					if (Object.IsValid() && IPlayer.IsValid() && (*(int(__thiscall **)(int, int, DWORD))(*(DWORD *)IPlayer.GetOffset() + 176))((int)IPlayer.GetOffset(), (int)Object.GetOffset(), 0))
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
void __fastcall MassiveFire(IChar IPlayer, int pPacket, int pPos)
{
	int pSkill = IPlayer.GetSkillPointer(91);

	if (pSkill && IPlayer.IsValid())
	{
		ISkill xSkill((void*)pSkill);
		int nSkillGrade = xSkill.GetGrade();
		int nTargetID = 0; char bType = 0; void *pTarget = 0;
		CPacket::Read((char*)pPacket, (char*)pPos, "bd", &bType, &nTargetID);
		int nMana = (1.85 * (200 + (nSkillGrade * (20 + (nSkillGrade - 1)))));

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

				int nDmg = (IPlayer.GetAttack() * NMFMul) + (nSkillGrade * CTools::Rate(NMFMin, NMFMax));

				if (Target.GetType() == 0)
					nDmg = (nDmg * NMFReduce) / 100;

				IPlayer.OktayDamageSingle(Target, nDmg, 91);
				IPlayer.SetDirection(Target);
				IPlayer.DecreaseMana(nMana);
			}
		}

	}
}

void __fastcall OneHitStrike(IChar IPlayer, int pPacket, int pPos)
{
	int pSkill = IPlayer.GetSkillPointer(90);

	if (IPlayer.IsValid() && pSkill)
	{
		ISkill xSkill((void*)pSkill);
		int nSkillGrade = xSkill.GetGrade();
		int nTargetID = 0; char bType = 0; void *pTarget = 0;
		CPacket::Read((char*)pPacket, (char*)pPos, "bd", &bType, &nTargetID);
		int nMana = (1.85 * (200 + (nSkillGrade * (20 + (nSkillGrade - 1)))));

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

				int nDmg = (IPlayer.GetAttack() * NOHSMul) + (nSkillGrade * CTools::Rate(NOHSMin, NOHSMax));

				if (Target.GetType() == 0)
					nDmg = (nDmg * NOHSReduce) / 100;

				IPlayer.OktayDamageSingle(Target, nDmg, 90);
				IPlayer.SetDirection(Target);
				IPlayer.DecreaseMana(nMana);
			}
		}
		else {
			IPlayer.CouldntExecuteSkill();
		}

	}
}
void __fastcall SpiritOfTheArrows(IChar IPlayer, int pPacket, int pPos)
{
	int pSkill = IPlayer.GetSkillPointer(93);

	if (IPlayer.IsValid() && pSkill)
	{
		ISkill xSkill((void*)pSkill);
		int nSkillGrade = xSkill.GetGrade();
		int nTargetID = 0, nMana = 0; char bType = 0; void *pTarget = 0;
		CPacket::Read((char*)pPacket, (char*)pPos, "bd", &bType, &nTargetID);
		nMana = (1.85 * (200 + (nSkillGrade * (20 + (nSkillGrade - 1)))));

		TargetFind myTarget(bType, 0, nTargetID);
		pTarget = myTarget.getTarget();

		if (bType >= 2)
			return;

		if (pTarget && nSkillGrade && IPlayer.IsOnline())
		{
			IChar Target(pTarget);

			if (IPlayer.GetCurMp() < nMana) {

				return;
			}

			if (pTarget == IPlayer.GetOffset()) {

				return;
			}

			if (!IPlayer.IsInRange(Target, 300)) {

				return;
			}

			int Around = Target.GetObjectListAround(3);

			while (Around)
			{
				IChar Object((void*)CBaseList::Offset((void*)Around));

				if (Object.IsValid() && IPlayer.IsValid() && (*(int(__thiscall **)(int, int, DWORD))(*(DWORD *)IPlayer.GetOffset() + 176))((int)IPlayer.GetOffset(), (int)Object.GetOffset(), 0))
				{
					int nDmg = (IPlayer.GetAttack() * NSOTAMul) + (nSkillGrade * CTools::Rate(NSOTAMin, NSOTAMax));

					if (Object.GetType() == 0)
						nDmg = nDmg * NSOTAReduce / 100;

					IPlayer.OktayDamageArea(Object, nDmg, 93);
				}

				Around = CBaseList::Pop((void*)Around);
			}

			IPlayer.SetDirection(Target);
			IPlayer._ShowBattleAnimation(Target, 93);
			IPlayer.DecreaseMana(nMana);
		}

	}
}