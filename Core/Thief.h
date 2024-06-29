void __fastcall Stun(IChar IPlayer, int pPacket, int pPos)
{
	int pSkill = IPlayer.GetSkillPointer(8);

	if (IPlayer.IsValid() && pSkill)
	{
		ISkill xSkill((void*)pSkill);
		int nSkillGrade = xSkill.GetGrade();
		int nTargetID = 0; char bType = 0; void *pTarget = 0;
		CPacket::Read((char*)pPacket, (char*)pPos, "bd", &bType, &nTargetID);
		int nMana = nSkillGrade * 10;

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

				if (IPlayer.CheckHit(Target, 10))
				{
					if (!Target.IsBuff(358))
						Target.SendGStateEx(Target.GetGStateEx() + 32);

					Target.Buff(7, nSkillGrade, 0);
					Target.Buff(358, nSkillGrade, 0);
					Target.Buff(359, nSkillGrade + 5, 0);
					Target.SetBuffIcon(nSkillGrade * 1000, 0, 2009, 207);
					int nDmg = (IPlayer.GetAttack() * TStunMul) + (nSkillGrade * CTools::Rate(TStunMin, TStunMax));

					if (Target.GetType() == 0)
						nDmg = nDmg * TStunReduce / 100;

					IPlayer.OktayDamageSingle(Target, nDmg, 8);
				}
				else {
					IPlayer._ShowBattleMiss(Target, 8);
				}

				IPlayer.SetDirection(Target);
				IPlayer.DecreaseMana(nMana);
			}
		}

	}
}

void __fastcall Strangle(IChar IPlayer, int pPacket, int pPos)
{
	int pSkill = IPlayer.GetSkillPointer(10);

	if (IPlayer.IsValid() && pSkill)
	{
		ISkill xSkill((void*)pSkill);
		int nSkillGrade = xSkill.GetGrade();
		int nTargetID = 0; char bType = 0; void *pTarget = 0;
		CPacket::Read((char*)pPacket, (char*)pPos, "bd", &bType, &nTargetID);
		int nMana = nSkillGrade * 5 + 10;

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

				if (IPlayer.CheckHit(Target, 10))
				{
					if (!Target.IsBuff(357))
						Target.SendGStateEx(Target.GetGStateEx() + 128);

					Target.Buff(357, nSkillGrade, 0);
					Target.Buff(7, nSkillGrade, 0);
					int nDmg = (IPlayer.GetAttack() * TStranMul) + (nSkillGrade * CTools::Rate(TStranMin, TStranMax));

					if (Target.GetType() == 0)
						nDmg = nDmg * TStranReduce / 100;

					IPlayer.OktayDamageSingle(Target, nDmg, 10);
				}
				else {
					IPlayer._ShowBattleMiss(Target, 10);
				}

				IPlayer.SetDirection(Target);
				IPlayer.DecreaseMana(nMana);
			}
		}

	}
}
void __fastcall ContinueRupture(IChar IPlayer)
{
	if (IPlayer.IsValid())
	{
		int TargetAOE = 0;
		if (RupAOE && RupPVPAoe)
			TargetAOE = 3;
		else if (RupPVPAoe)
			TargetAOE = 2;
		else if (RupAOE)
			TargetAOE = 1;

		int nSkillGrade = IPlayer.GetProperty(PlayerProperty::RuptureContinueSkillPlayerSkillGrade);
		void *pTarget = (void*)IPlayer.GetProperty(PlayerProperty::RuptureContinueSkillPlayerTarget);

		if (nSkillGrade && IPlayer.GetProperty(PlayerProperty::RuptureContinueSkillPlayerSkillCount))
		{
			int Count = IPlayer.GetProperty(PlayerProperty::RuptureContinueSkillPlayerSkillCount);
			IPlayer.SetProperty(PlayerProperty::RuptureContinueSkillPlayerSkillCount, Count - 1);

			IChar Target(pTarget);
			if (RupAOE && (TargetAOE == 3 || (TargetAOE && !Target.IsValid()) || (TargetAOE == 2 && Target.GetType() == 0) || (TargetAOE == 1 && Target.GetType() == 1))) {
				int Around = IPlayer.GetObjectListAround(RupAOE);
				while (Around)
				{
					IChar Object((void*)CBaseList::Offset((void*)Around));
					if (Object.IsValid() && IPlayer.IsValid() && (*(int(__thiscall **)(int, int, DWORD))(*(DWORD *)IPlayer.GetOffset() + 176))((int)IPlayer.GetOffset(), (int)Object.GetOffset(), 0) && (TargetAOE == 3 || (TargetAOE == 2 && Object.GetType() == 0) || (TargetAOE == 1 && Object.GetType() == 1))) {
						int nDmg = (IPlayer.GetAttack() * TRupMul) + (nSkillGrade * CTools::Rate(TRupMin, TRupMax));

						if (Object.GetType() == 0)
							nDmg = nDmg * TRupReduce / 100;

						IPlayer.OktayDamageArea(Object, nDmg, 17);
					}
					Around = CBaseList::Pop((void*)Around);
				}
			}
			else {
				if (!Target.IsValid() || !IPlayer.IsValid())
				{
					ResetRuptureContinueSkill(IPlayer);
					return;
				}

				if (CChar::GetRange((int)IPlayer.GetOffset() + 332, (int)pTarget + 332) > 300)
				{
					ResetRuptureContinueSkill(IPlayer);
					return;
				}

				if ((*(int(__thiscall **)(int, int, DWORD))(*(DWORD *)IPlayer.GetOffset() + 176))((int)IPlayer.GetOffset(), (int)Target.GetOffset(), 0)) {
					int nDmg = (IPlayer.GetAttack() * TRupMul) + (nSkillGrade * CTools::Rate(TRupMin, TRupMax));

					if (Target.GetType() == 0)
						nDmg = nDmg * TRupReduce / 100;

					IPlayer.OktayDamageArea(Target, nDmg, 17);
				}
			}

			if (IPlayer.IsOnline())
				IPlayer.SetProperty(PlayerProperty::RuptureContinueSkillPlayerSkillDelay, GetTickCount() + 2000);

			if (pTarget && !Target.IsValid())
				IPlayer.SetProperty(PlayerProperty::RuptureContinueSkillPlayerTarget, 0);

			if (IPlayer.IsOnline() && IPlayer.GetProperty(PlayerProperty::RuptureContinueSkillPlayerSkillCount) == 0)
				ResetRuptureContinueSkill(IPlayer);

			return;
		}
	}

	ResetRuptureContinueSkill(IPlayer);
	return;
}

void __fastcall Rupture(IChar IPlayer, int pPacket, int pPos)
{
	int pSkill = IPlayer.GetSkillPointer(17);

	if (IPlayer.IsValid() && pSkill)
	{
		ISkill xSkill((void*)pSkill);
		int nSkillGrade = xSkill.GetGrade();
		int nTargetID = 0; char bType = 0; void *pTarget = 0;
		CPacket::Read((char*)pPacket, (char*)pPos, "bd", &bType, &nTargetID);
		int nMana = (int)(30 * nSkillGrade + 35);

		TargetFind myTarget(bType, 0, nTargetID);
		pTarget = myTarget.getTarget();

		if (bType >= 2)
			return;

		if (pTarget && IPlayer.IsValid() && nSkillGrade)
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

				if (IPlayer.CheckHit(Target, 10))
				{
					if (!IPlayer.GetProperty(PlayerProperty::RuptureContinueSkillPlayerSkillID))
						IPlayer.SetContinueSkill();

					IPlayer.Buff(353, 20, 0);

					if (!Target.IsBuff(350))
						Target._SendGStateEx(Target._GetGStateEx() + 65536);

					Target.Buff(350, 18, 0);
					IPlayer.SetProperty(PlayerProperty::RuptureContinueSkillPlayerTarget, (int)Target.GetOffset());
					IPlayer.SetProperty(PlayerProperty::RuptureContinueSkillPlayerSkillID, 17);
					IPlayer.SetProperty(PlayerProperty::RuptureContinueSkillPlayerSkillCount, 9);
					IPlayer.SetProperty(PlayerProperty::RuptureContinueSkillPlayerSkillDelay, GetTickCount() + 1000);
					IPlayer.SetProperty(PlayerProperty::RuptureContinueSkillPlayerSkillGrade, nSkillGrade);
					IPlayer._ShowBattleAnimation(IPlayer, 17, nSkillGrade);
				}
				else {
					IPlayer._ShowBattleMiss(Target, 17);
				}

				IPlayer.SetDirection(Target);
				IPlayer.DecreaseMana(nMana);
			}
		}

	}
}
void __fastcall ContinueFatalWound(IChar IPlayer)
{
	if (IPlayer.IsValid())
	{
		int nSkillGrade = IPlayer.GetProperty(PlayerProperty::FarContinueSkillPlayerSkillGrade);
		void *pTarget = (void*)IPlayer.GetProperty(PlayerProperty::FarContinueSkillPlayerTarget);

		if (nSkillGrade && pTarget && IPlayer.GetProperty(PlayerProperty::FarContinueSkillPlayerSkillCount))
		{
			IChar Target(pTarget);
			int Count = IPlayer.GetProperty(PlayerProperty::FarContinueSkillPlayerSkillCount);
			IPlayer.SetProperty(PlayerProperty::FarContinueSkillPlayerSkillCount, Count - 1);

			if (!Target.IsValid() || !IPlayer.IsValid())
			{
				ResetFarContinueSkill(IPlayer);
				return;
			}

			if (!IPlayer.IsInRange(Target, 300))
			{
				ResetFarContinueSkill(IPlayer);
				return;
			}

			if (IPlayer.IsValid() && Target.IsValid())
			{
				int nDmg = (IPlayer.GetAttack() * TFWMul) + (nSkillGrade * CTools::Rate(TFWMin, TFWMax));

				if (Target.GetType() == 0)
					nDmg = (nDmg * TFWReduce) / 100;

				IPlayer.OktayDamageArea(Target, nDmg, 14);
			}

			if (IPlayer.IsOnline())
				IPlayer.SetProperty(PlayerProperty::FarContinueSkillPlayerSkillDelay, GetTickCount() + 2000);

			if (IPlayer.IsOnline() && IPlayer.GetProperty(PlayerProperty::FarContinueSkillPlayerSkillCount) == 0)
				ResetFarContinueSkill(IPlayer);

			return;
		}
	}

	ResetFarContinueSkill(IPlayer);
	return;
}

void __fastcall FatalWound(IChar IPlayer, int pPacket, int pPos)
{
	int pSkill = IPlayer.GetSkillPointer(14);

	if (IPlayer.IsValid() && pSkill)
	{
		ISkill xSkill((void*)pSkill);
		int nSkillGrade = xSkill.GetGrade();
		int nTargetID = 0; char bType = 0; void *pTarget = 0;
		CPacket::Read((char*)pPacket, (char*)pPos, "bd", &bType, &nTargetID);
		int nMana = (int)(30 * nSkillGrade + 15);

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

				if (!Target.IsBuff(348))
				{
					Target.SendGStateEx(Target.GetGStateEx() + 32768);

					if (!IPlayer.GetProperty(PlayerProperty::FarContinueSkillPlayerSkillID))
						IPlayer.SetContinueSkill();

					IPlayer.SetProperty(PlayerProperty::FarContinueSkillPlayerTarget, (int)Target.GetOffset());
					IPlayer.SetProperty(PlayerProperty::FarContinueSkillPlayerSkillID, 14);
					IPlayer.SetProperty(PlayerProperty::FarContinueSkillPlayerSkillCount, 8);
					IPlayer.SetProperty(PlayerProperty::FarContinueSkillPlayerSkillDelay, 0);
					IPlayer.SetProperty(PlayerProperty::FarContinueSkillPlayerSkillGrade, nSkillGrade);
					Target.Buff(348, 16, 0);
				}

				IPlayer.SetDirection(Target);
				IPlayer.DecreaseMana(nMana);
				IPlayer._ShowBattleAnimation(Target, 14, nSkillGrade);
			}
		}

	}
}
void __fastcall VitalStrike(IChar IPlayer, int pPacket, int pPos)
{
	int pSkill = IPlayer.GetSkillPointer(16);

	if (IPlayer.IsValid() && pSkill)
	{
		ISkill xSkill((void*)pSkill);
		int nSkillGrade = xSkill.GetGrade();
		int nTargetID = 0; char bType = 0; void *pTarget = 0;
		CPacket::Read((char*)pPacket, (char*)pPos, "bd", &bType, &nTargetID);
		int nMana = nSkillGrade * 30 + 35;

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

				if (IPlayer.CheckHit(Target, 10))
				{
					if (Target.GetCurHp() <= (Target.GetMaxHp() / 2))
					{
						Target.Buff(7, nSkillGrade * 2, 0);
						Target.Buff(344, nSkillGrade * 2, 0);
						Target.Buff(345, nSkillGrade * 10, 0);
						Target.SetBuffIcon(nSkillGrade * 2000, 0, 2016, 211);
					}

					int nDmg = (IPlayer.GetAttack() * TVSMul) + (nSkillGrade * CTools::Rate(TVSMin, TVSMax));

					if (Target.GetType() == 0)
						nDmg = nDmg * TVSReduce / 100;

					IPlayer.OktayDamageSingle(Target, nDmg, 16);
				}
				else {
					IPlayer._ShowBattleMiss(Target, 16);
				}

				IPlayer.SetDirection(Target);
				IPlayer.DecreaseMana(nMana);
			}
		}

	}
}
void __fastcall Assault(IChar IPlayer, int pPacket, int pPos)
{
	int pSkill = IPlayer.GetSkillPointer(7);

	if (IPlayer.IsValid() && pSkill)
	{
		ISkill xSkill((void*)pSkill);
		int nSkillGrade = xSkill.GetGrade();
		int nTargetID = 0; char bType = 0; void *pTarget = 0;
		CPacket::Read((char*)pPacket, (char*)pPos, "bd", &bType, &nTargetID);

		if (bType >= 2)
			return;

		TargetFind myTarget(bType, 0, nTargetID);
		pTarget = myTarget.getTarget();

		if (pTarget && nSkillGrade && IPlayer.IsValid())
		{
			int nMana = nSkillGrade * 20 + 25;
			IChar Target(pTarget);

			if (pTarget == IPlayer.GetOffset()) {

				return;
			}

			if (IPlayer.GetCurMp() < nMana) {

				return;
			}

			if (IPlayer.IsValid() && Target.IsValid())
			{
				if (!IPlayer.IsInRange(Target, 300)) {

					return;
				}

				if (IPlayer.CheckHit(Target, 20))
				{
					int nDmg = ((IPlayer.GetAttack() + 128) * TAssMul) + (nSkillGrade * CTools::Rate(TAssMin, TAssMax));

					if (Target.GetType() == 0)
						nDmg = (nDmg * TAssReduce) / 100;

					IPlayer.OktayDamageSingle(Target, nDmg, 7);
				}
				else {
					IPlayer._ShowBattleMiss(Target, 7);
				}

				IPlayer.SetDirection(Target);
				IPlayer._ShowBattleAnimation(Target, 7);
				IPlayer.DecreaseMana(nMana);
			}
		}


	}
}
void __fastcall SuicidalBlow(IChar IPlayer, int pPacket, int pPos)
{
	int pSkill = IPlayer.GetSkillPointer(21);

	if (IPlayer.IsValid() && pSkill)
	{
		ISkill xSkill((void*)pSkill);
		int nSkillGrade = xSkill.GetGrade();
		int nTargetID = 0; char bType = 0; void *pTarget = 0;
		CPacket::Read((char*)pPacket, (char*)pPos, "bd", &bType, &nTargetID);
		int nMana = 40 * nSkillGrade + 45;

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

				int nDmg = (IPlayer.GetAttack() * TSuBMul) + (nSkillGrade * CTools::Rate(TSuBMin, TSuBMax));
				int Additional = 0;

				if (IPlayer.GetCurHp() >= 100)
				{
					Additional = (IPlayer.GetCurHp() * 80) / 100;

					if (Additional > 0 && IPlayer.GetCurHp() > Additional)
					{
						IPlayer.DecreaseHp(Additional);
						nDmg = nDmg + (Additional / 2);
					}
				}

				if (Target.GetType() == 0)
					nDmg = nDmg * TSuBReduce / 100;

				if (IPlayer.CheckHit(Target, 110))
					IPlayer.OktayDamageSingle(Target, nDmg, 21);
				else
					IPlayer._ShowBattleMiss(Target, 21);

				IPlayer.SetDirection(Target);
				IPlayer.DecreaseMana(nMana);
			}
		}

	}
}
void __fastcall FinalBlow(IChar IPlayer, int pPacket, int pPos)
{
	int pSkill = IPlayer.GetSkillPointer(18);

	if (IPlayer.IsValid() && pSkill)
	{
		ISkill xSkill((void*)pSkill);
		int nSkillGrade = xSkill.GetGrade();
		int nTargetID = 0; char bType = 0; void *pTarget = 0; int nMana = 450;
		CPacket::Read((char*)pPacket, (char*)pPos, "bd", &bType, &nTargetID);

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
				if (CChar::GetRange((int)IPlayer.GetOffset() + 332, (int)pTarget + 332) > 300) {

					return;
				}

				if (IPlayer.CheckHit(Target, 20) && (Target.GetCurHp() <= (Target.GetMaxHp() / 2)))
				{
					int nDmg = (IPlayer.GetAttack() * TFBMul) + (nSkillGrade * CTools::Rate(TFBMin, TFBMax));

					if (Target.GetType() == 0)
						nDmg = nDmg * TFBReduce / 100;

					IPlayer.OktayDamageSingle(Target, nDmg, 18);
				}
				else {
					IPlayer._ShowBattleMiss(Target, 18);
				}

				IPlayer.SetDirection(Target);
				IPlayer._ShowBattleAnimation(Target, 18);
				IPlayer.DecreaseMana(nMana);
			}
		}

	}
}
void __fastcall SpinAttack(IChar IPlayer, int pPacket, int pPos)
{
	int pSkill = IPlayer.GetSkillPointer(19);

	if (IPlayer.IsValid() && pSkill)
	{
		ISkill xSkill((void*)pSkill);
		int nSkillGrade = xSkill.GetGrade();
		int nTargetID = 0; char bType = 0; void *pTarget = 0;
		CPacket::Read((char*)pPacket, (char*)pPos, "bd", &bType, &nTargetID);
		int nMana = nSkillGrade * 50 + 25;

		if (bType >= 2)
			return;

		TargetFind myTarget(bType, 0, nTargetID);
		pTarget = myTarget.getTarget();

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

				int Around = IPlayer.GetObjectListAround(3);

				while (Around)
				{
					IChar Object((void*)CBaseList::Offset((void*)Around));

					if (Object.IsValid() && IPlayer.IsValid() && (*(int(__thiscall **)(int, int, DWORD))(*(DWORD *)IPlayer.GetOffset() + 176))((int)IPlayer.GetOffset(), (int)Object.GetOffset(), 0))
					{
						int nDmg = (IPlayer.GetAttack() * TSAMul) + (nSkillGrade * CTools::Rate(TSAMin, TSAMax));

						if (Object.GetType() == 0)
							nDmg = (nDmg * TSAReduce) / 100;

						IPlayer.OktayDamageArea(Object, nDmg, 19);
					}

					Around = CBaseList::Pop((void*)Around);
				}

				IPlayer.SetDirection(Target);
				IPlayer._ShowBattleAnimation(Target, 19);
				IPlayer.DecreaseMana(nMana);
			}
		}

	}
}
void __fastcall ContinueTwinBladeStrike(IChar IPlayer)
{
	if (IPlayer.IsValid())
	{
		void *pTarget = (void*)IPlayer.GetProperty(PlayerProperty::FarContinueSkillPlayerTarget);
		IChar Target(pTarget);

		if (pTarget && Target.IsValid() && IPlayer.IsValid())
		{
			if (IPlayer.GetProperty(PlayerProperty::FarContinueSkillPlayerSkillCount))
			{
				int Count = IPlayer.GetProperty(PlayerProperty::FarContinueSkillPlayerSkillCount);
				IPlayer.SetProperty(PlayerProperty::FarContinueSkillPlayerSkillCount, Count - 1);

				if (CChar::GetRange((int)IPlayer.GetOffset() + 332, (int)pTarget + 332) > 300)
				{
					ResetFarContinueSkill(IPlayer);
					return;
				}

				if (IPlayer.CheckHit(Target, 10))
				{
					int nDmg = (IPlayer.GetAttack() * TTBSMul) + (CTools::Rate(TTBSMin, TTBSMax));

					if (Target.GetType() == 0)
						nDmg = nDmg * TTBSReduce / 100;

					IPlayer.OktayDamageArea(Target, nDmg, 23);
				}

				if (IPlayer.IsOnline())
					IPlayer.SetProperty(PlayerProperty::FarContinueSkillPlayerSkillDelay, GetTickCount() + 2000);

				if (IPlayer.IsOnline() && IPlayer.GetProperty(PlayerProperty::FarContinueSkillPlayerSkillCount) == 0)
					ResetFarContinueSkill(IPlayer);

				return;
			}
		}
	}

	ResetFarContinueSkill(IPlayer);
	return;
}

void __fastcall TwinBladeStrike(IChar IPlayer, int pPacket, int pPos)
{
	int pSkill = IPlayer.GetSkillPointer(23);

	if (IPlayer.IsValid() && pSkill)
	{
		int nTargetID = 0; char bType = 0; void *pTarget = 0;
		CPacket::Read((char*)pPacket, (char*)pPos, "bd", &bType, &nTargetID);

		TargetFind myTarget(bType, 0, nTargetID);
		pTarget = myTarget.getTarget();

		if (bType >= 2)
			return;

		if (pTarget && IPlayer.IsValid())
		{
			IChar Target(pTarget);

			if (IPlayer.GetCurMp() < 65) {

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
					if (!IPlayer.GetProperty(PlayerProperty::FarContinueSkillPlayerSkillID))
						IPlayer.SetContinueSkill();

					IPlayer.SetProperty(PlayerProperty::FarContinueSkillPlayerTarget, (int)Target.GetOffset());
					IPlayer.SetProperty(PlayerProperty::FarContinueSkillPlayerSkillID, 23);
					IPlayer.SetProperty(PlayerProperty::FarContinueSkillPlayerSkillCount, 4);
					IPlayer.SetProperty(PlayerProperty::FarContinueSkillPlayerSkillDelay, GetTickCount() + 2000);

					if (!Target.IsBuff(339))
						Target.SendGStateEx(Target.GetGStateEx() + 262144);

					Target.Buff(339, 8, 0);
					Target.Buff(340, 12, 0);
					IPlayer.Buff(341, 20, 0);

					if (Target.GetType() == 0)
					{
						IPlayer.RemoveBuffIcon(0, 0, 0, 219);
						Target.SetBuffIcon(10000, 0, 2021, 219);
					}

					int nDmg = (IPlayer.GetAttack() * TTBSMul) + (CTools::Rate(TTBSMin, TTBSMax));

					if (Target.GetType() == 0)
						nDmg = nDmg * TTBSReduce / 100;

					IPlayer.OktayDamageSingle(Target, nDmg, 23);
				}
				else {
					IPlayer._ShowBattleMiss(Target, 23);
				}

				IPlayer.SetDirection(Target);
				IPlayer.DecreaseMana(65);
			}
		}

	}
}
void __fastcall CounterDamage(IChar IPlayer)
{
	if (IPlayer.IsValid())
	{
		void *pTarget = (void*)IPlayer.GetProperty(PlayerProperty::FarContinueSkillPlayerTarget);
		IChar Target(pTarget);

		if (pTarget && IPlayer.IsValid() && Target.IsValid())
		{
			IPlayer.AddFxToTarget("Counterattack_Spear_2", 1, 0, 0);

			if (IPlayer.GetProperty(PlayerProperty::FarContinueSkillPlayerSkillCount))
			{
				int Count = IPlayer.GetProperty(PlayerProperty::FarContinueSkillPlayerSkillCount);
				IPlayer.SetProperty(PlayerProperty::FarContinueSkillPlayerSkillCount, Count - 1);

				if (IPlayer.IsValid() && Target.IsValid())
				{
					if (!IPlayer.IsInRange(Target, 300))
					{
						ResetFarContinueSkill(IPlayer);
						return;
					}

					if (IPlayer.GetProperty(PlayerProperty::FarContinueSkillPlayerDamage) > 1000)
						IPlayer.SetProperty(PlayerProperty::FarContinueSkillPlayerDamage, 1000);

					int nDmg = IPlayer.GetProperty(PlayerProperty::FarContinueSkillPlayerDamage);
					IPlayer.OktayDamageArea(Target, nDmg, 76);

					if (IPlayer.IsOnline() && IPlayer.GetProperty(PlayerProperty::FarContinueSkillPlayerSkillCount) == 0)
						ResetFarContinueSkill(IPlayer);

					if (IPlayer.IsOnline())
						IPlayer.SetProperty(PlayerProperty::FarContinueSkillPlayerSkillDelay, GetTickCount() + 2000);

					return;
				}
			}
		}
	}

	ResetFarContinueSkill(IPlayer);
	return;
}
void __fastcall ContinueLightningSlash(IChar IPlayer)
{
	if (IPlayer.IsValid())
	{
		int nSkillGrade = IPlayer.GetProperty(PlayerProperty::ContinueSkillPlayerSkillGrade);
		void *pTarget = (void*)IPlayer.GetProperty(PlayerProperty::ContinueSkillPlayerTarget);

		if (nSkillGrade && pTarget && IPlayer.GetProperty(PlayerProperty::ContinueSkillPlayerSkillCount))
		{
			IChar Target(pTarget);
			int Count = IPlayer.GetProperty(PlayerProperty::ContinueSkillPlayerSkillCount);
			IPlayer.SetProperty(PlayerProperty::ContinueSkillPlayerSkillCount, Count - 1);

			if (IPlayer.IsValid() && Target.IsValid())
			{
				if (!IPlayer.IsInRange(Target, 2))
				{
					ResetContinueSkill(IPlayer);
					return;
				}

				if (IPlayer.IsMoved(IPlayer.GetProperty(PlayerProperty::ContinueSkillPlayerX), IPlayer.GetProperty(PlayerProperty::ContinueSkillPlayerY)))
				{
					ResetContinueSkill(IPlayer);
					return;
				}

				if (IPlayer.CheckHit(Target, 30))
				{
					int nDmg = (IPlayer.GetAttack() * TLSMul) + (nSkillGrade * CTools::Rate(TLSMin, TLSMax));

					if (Target.GetType() == 0)
						nDmg = nDmg * TLSReduce / 100;

					IPlayer.OktayDamageSingle(Target, nDmg, 28);
				}

				if (IPlayer.IsOnline())
					IPlayer.SetProperty(PlayerProperty::ContinueSkillPlayerSkillDelay, GetTickCount() + 700);

				if (IPlayer.IsOnline() && Count == 1)
					ResetContinueSkill(IPlayer);

				return;
			}
		}
	}

	ResetContinueSkill(IPlayer);
	return;
}

void __fastcall LightningSlash(IChar IPlayer, int pPacket, int pPos)
{
	int pSkill = IPlayer.GetSkillPointer(28);

	if (IPlayer.IsValid() && pSkill)
	{
		ISkill xSkill((void*)pSkill);
		int nSkillGrade = xSkill.GetGrade();
		int nTargetID = 0; char bType = 0; void *pTarget = 0;
		CPacket::Read((char*)pPacket, (char*)pPos, "bd", &bType, &nTargetID);
		int nMana = (nSkillGrade + IPlayer.GetLevel()) * 3 + 50;

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

				IPlayer.DecreaseMana(nMana);

				if (!IPlayer.GetProperty(PlayerProperty::ContinueSkillPlayerSkillID))
					IPlayer.SetContinueSkill();
				IPlayer.SetProperty(PlayerProperty::ContinueSkillPlayerX, IPlayer.GetX());
				IPlayer.SetProperty(PlayerProperty::ContinueSkillPlayerY, IPlayer.GetY());
				IPlayer.SetProperty(PlayerProperty::ContinueSkillPlayerSkillID, 28);
				IPlayer.SetProperty(PlayerProperty::ContinueSkillPlayerTarget, (int)Target.GetOffset());
				IPlayer.SetProperty(PlayerProperty::ContinueSkillPlayerSkillGrade, xSkill.GetGrade());
				IPlayer.SetProperty(PlayerProperty::ContinueSkillPlayerSkillCount, xSkill.GetGrade() + 1);
				IPlayer.SetProperty(PlayerProperty::ContinueSkillPlayerSkillDelay, 0);
			}
		}
	}
}
void __fastcall ShadowSlash(IChar IPlayer, int pPacket, int pPos)
{
	int pSkill = IPlayer.GetSkillPointer(32);

	if (IPlayer.IsValid() && pSkill)
	{
		ISkill xSkill((void*)pSkill);
		int nSkillGrade = xSkill.GetGrade();
		int nTargetID = 0; char bType = 0; void *pTarget = 0;
		CPacket::Read((char*)pPacket, (char*)pPos, "bd", &bType, &nTargetID);
		int nMana = 230 + (((IPlayer.GetLevel() + nSkillGrade) * nSkillGrade) * 0.63);

		TargetFind myTarget(bType, 0, nTargetID);
		pTarget = myTarget.getTarget();

		if (bType >= 2)
			return;

		if (pTarget && IPlayer.IsValid() && nSkillGrade)
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
				if (IPlayer.CheckHit(Target, 30))
				{
					int Around = Target.GetObjectListAround(ShadowRange);

					while (Around)
					{
						IChar Object((void*)CBaseList::Offset((void*)Around));

						if (Object.IsValid() && IPlayer.IsValid() && IPlayer.GetOffset() != Object.GetOffset() && (*(int(__thiscall **)(int, int, DWORD))(*(DWORD *)IPlayer.GetOffset() + 176))((int)IPlayer.GetOffset(), (int)Object.GetOffset(), 0))
						{
							if (((!ShadowAOEPVE || !ShadowAOEPVP) && Target.IsValid() && Target.GetX() <= max(IPlayer.GetX(), Object.GetX()) && Target.GetX() >= min(IPlayer.GetX(), Object.GetX()) && Target.GetY() <= max(IPlayer.GetY(), Object.GetY()) && Target.GetY() >= min(IPlayer.GetY(), Object.GetY())) || ShadowAOEPVE && ShadowAOEPVP)
							{
								Object.Buff(7, nSkillGrade, 0);
								int nDmg = (IPlayer.GetAttack() * TSSMul) + (nSkillGrade * CTools::Rate(TSSMin, TSSMax));

								if (Object.GetType() == 0)
									nDmg = (nDmg * TSSReduce) / 100;

								IPlayer.OktayDamageArea(Object, nDmg, 32);
							}
							else if (ShadowAOEPVE && Object.GetType() == 1){

								Object.Buff(7, nSkillGrade, 0);
								int nDmg = (IPlayer.GetAttack() * TSSMul) + (nSkillGrade * CTools::Rate(TSSMin, TSSMax));
								IPlayer.OktayDamageArea(Object, nDmg, 32);
							}
							else if (ShadowAOEPVP && Object.GetType() == 0){

								Object.Buff(7, nSkillGrade, 0);
								int nDmg = (IPlayer.GetAttack() * TSSMul) + (nSkillGrade * CTools::Rate(TSSMin, TSSMax));
								nDmg = (nDmg * TSSReduce) / 100;

								IPlayer.OktayDamageArea(Object, nDmg, 32);
							}
						}

						Around = CBaseList::Pop((void*)Around);
					}
				}
				else {
					IPlayer._ShowBattleMiss(Target, 32);
				}

				IPlayer.SetDirection(Target);
				IPlayer._ShowBattleAnimation(Target, 32);
				IPlayer.DecreaseMana(nMana);
			}
		}

	}
}
void __fastcall WrathOfHeaven(IChar IPlayer, int pPacket, int pPos)
{
	int pSkill = IPlayer.GetSkillPointer(33);

	if (IPlayer.IsValid() && pSkill)
	{
		ISkill xSkill((void*)pSkill);
		int nSkillGrade = xSkill.GetGrade();
		int nTargetID = 0; char bType = 0; void *pTarget = 0;
		CPacket::Read((char*)pPacket, (char*)pPos, "bd", &bType, &nTargetID);
		int nMana = (IPlayer.GetLevel() + nSkillGrade) * 3 + 50;

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

				if (IPlayer.CheckHit(Target, 30))
				{
					int nDmg = (IPlayer.GetAttack() * TWOHMul) + (nSkillGrade * CTools::Rate(TWOHMin, TWOHMax));

					if (Target.GetType() == 0)
						nDmg = nDmg * TWOHReduce / 100;

					IPlayer.OktayDamageSingle(Target, nDmg, 33);
				}
				else {
					IPlayer._ShowBattleMiss(Target, 33);
				}

				IPlayer.SetDirection(Target);
				IPlayer.DecreaseMana(nMana);
			}
		}

	}
}
void __fastcall ContinueSpinBlade(IChar IPlayer)
{
	if (IPlayer.IsValid())
	{
		if (IPlayer.GetProperty(PlayerProperty::ContinueSkillPlayerSkillCount))
		{
			int Count = IPlayer.GetProperty(PlayerProperty::ContinueSkillPlayerSkillCount);
			IPlayer.SetProperty(PlayerProperty::ContinueSkillPlayerSkillCount, Count - 1);

			if (!IPlayer.IsValid())
			{
				ResetContinueSkill(IPlayer);
				return;
			}

			if (IPlayer.IsMoved(IPlayer.GetProperty(PlayerProperty::ContinueSkillPlayerX), IPlayer.GetProperty(PlayerProperty::ContinueSkillPlayerY)))
			{
				ResetContinueSkill(IPlayer);
				return;
			}

			int Around = IPlayer.GetObjectListAround(3);

			while (Around)
			{
				IChar Object((void*)CBaseList::Offset((void*)Around));

				if (Object.IsValid() && IPlayer.IsValid() && (*(int(__thiscall **)(int, int, DWORD))(*(DWORD *)IPlayer.GetOffset() + 176))((int)IPlayer.GetOffset(), (int)Object.GetOffset(), 0))
				{
					int nDmg = (IPlayer.GetAttack() * TSBMul) + (IPlayer.GetProperty(PlayerProperty::ContinueSkillPlayerSkillGrade) * CTools::Rate(TSBMin, TSBMax));

					if (Object.GetType() == 0)
						nDmg = (nDmg * TSBReduce) / 100;

					if (IPlayer.CheckHit(Object, 10) || Object.GetType() == 1)
						IPlayer.OktayDamageArea(Object, nDmg, 36);
				}

				Around = CBaseList::Pop((void*)Around);
			}

			IPlayer._ShowBattleAnimation(IPlayer, 36);

			if (IPlayer.IsOnline())
				IPlayer.SetProperty(PlayerProperty::ContinueSkillPlayerSkillDelay, GetTickCount() + 1000);

			if (IPlayer.IsOnline() && IPlayer.GetProperty(PlayerProperty::ContinueSkillPlayerSkillCount) == 0)
				ResetContinueSkill(IPlayer);

			return;
		}
	}

	ResetContinueSkill(IPlayer);
	return;
}

void __fastcall SpinBlade(IChar IPlayer)
{
	int pSkill = IPlayer.GetSkillPointer(36);

	if (IPlayer.IsValid() && pSkill)
	{
		ISkill xSkill((void*)pSkill);
		int nSkillGrade = xSkill.GetGrade();
		int nMana = (int)((((nSkillGrade + IPlayer.GetLevel()) * nSkillGrade)*1.25) + 180);

		if (IPlayer.GetCurMp() < nMana)
			return;

		if (nSkillGrade && IPlayer.IsValid())
		{
			IPlayer.DecreaseMana(nMana);



			if (!IPlayer.GetProperty(PlayerProperty::ContinueSkillPlayerSkillID))
				IPlayer.SetContinueSkill();

			IPlayer.SetProperty(PlayerProperty::ContinueSkillPlayerX, IPlayer.GetX());
			IPlayer.SetProperty(PlayerProperty::ContinueSkillPlayerY, IPlayer.GetY());
			IPlayer.SetProperty(PlayerProperty::ContinueSkillPlayerSkillID, 36);
			IPlayer.SetProperty(PlayerProperty::ContinueSkillPlayerSkillGrade, xSkill.GetGrade());
			IPlayer.SetProperty(PlayerProperty::ContinueSkillPlayerSkillCount, xSkill.GetGrade() + 1);
			IPlayer.SetProperty(PlayerProperty::ContinueSkillPlayerSkillDelay, 0);
		}
	}
}

void __fastcall AnkleAmputate(IChar IPlayer, int pPacket, int pPos)
{
	int pSkill = IPlayer.GetSkillPointer(15);

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

		if (IPlayer.IsValid() && pTarget && nSkillGrade)
		{
			if (pTarget == IPlayer.GetOffset()) {

				return;
			}

			int nMana = (10 * nSkillGrade) + 45;
			IChar Target(pTarget);

			if (IPlayer.GetCurMp() < nMana) {

				return;
			}

			if (IPlayer.IsValid() && Target.IsValid())
			{
				if (!CanAttack(IPlayer.GetOffset(), 0, (int)Target.GetOffset(), 0)) {

					return;
				}

				if (!IPlayer.IsInRange(Target, 300)) {

					return;
				}

				IPlayer.DecreaseMana(nMana);
				Target.Buff(40, nSkillGrade * 3, -50);

				if (!Target.IsBuff(346))
					Target.SendGStateEx(Target.GetGStateEx() + 256);

				if (Target.GetType() == 0)
					Target.RemoveBuffIcon(0, 0, 0, 54);

				Target.Buff(346, nSkillGrade * 3, 0);
				IPlayer.SetDirection(Target);
				IPlayer._ShowBattleAnimation(Target, 15, nSkillGrade);
			}
		}

	}
}
void __fastcall ArmorBreaker(IChar IPlayer, int pPacket, int pPos)
{
	int pSkill = IPlayer.GetSkillPointer(22);

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

		if (IPlayer.IsValid() && pTarget && nSkillGrade)
		{
			if (pTarget == IPlayer.GetOffset()) {

				return;
			}

			int nMana = (30 * nSkillGrade) + 35;
			IChar Target(pTarget);

			if (IPlayer.GetCurMp() < nMana) {

				return;
			}

			if (IPlayer.IsValid() && Target.IsValid())
			{
				if (!CanAttack(IPlayer.GetOffset(), 0, (int)Target.GetOffset(), 0)) {

					return;
				}

				if (!IPlayer.IsInRange(Target, 300)) {

					return;
				}

				IPlayer.DecreaseMana(nMana);

				if (!Target.IsBuff(342))
				{
					Target.SendGStateEx(Target.GetGStateEx() + 131072);
					Target.Buff(342, 9, 0);
				}

				IPlayer.SetDirection(Target);
				IPlayer._ShowBattleAnimation(Target, 22, nSkillGrade);
			}
		}

	}
}
void __fastcall Confusion(IChar IPlayer, int pPacket, int pPos)
{
	int pSkill = IPlayer.GetSkillPointer(9);

	if (IPlayer.IsValid() && pSkill)
	{
		ISkill xSkill((void*)pSkill);
		int nSkillGrade = xSkill.GetGrade();
		int nTargetID = 0; char bType = 0; void *pTarget = 0;
		CPacket::Read((char*)pPacket, (char*)pPos, "bd", &bType, &nTargetID);
		int nMana = (int)(20 * nSkillGrade + 10);

		TargetFind myTarget(bType, 0, nTargetID);
		pTarget = myTarget.getTarget();

		if (bType >= 2)
			return;

		if (IPlayer.IsValid() && pTarget && nSkillGrade)
		{
			if (IPlayer.GetCurMp() < nMana) {

				return;
			}

			if (pTarget == IPlayer.GetOffset()) {

				return;
			}

			IChar Target(pTarget);

			if (IPlayer.IsValid() && Target.IsValid())
			{
				if (!IPlayer.IsInRange(Target, 300)) {

					return;
				}

				if (IPlayer.CheckHit(Target, 10) && Target.GetOffset() != IPlayer.GetOffset())
				{
					if (Target.GetType() == 1)
						Target.Buff(7, 2 + (nSkillGrade * 2), 0);
					else
						Target.Buff(7, 2 + (nSkillGrade), 0);

					if (!Target.IsBuff(356))
						Target.SendGStateEx(Target.GetGStateEx() + 64);

					Target.Buff(356, 2 + (nSkillGrade * 2), 0);
				}
				else {
					IPlayer._ShowBattleMiss(Target, 9);
				}

				IPlayer.SetDirection(Target);
				IPlayer._ShowBattleAnimation(Target, 9, nSkillGrade);
				IPlayer.DecreaseMana(nMana);
			}
		}

	}
}
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

		if (IPlayer.IsValid())
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
								IMembers.SetBuffIcon(1000 * (5 + (nSkillGrade * 5)), 0, 4245, 953);
								IMembers.IncreaseCritRate((nSkillGrade * 10) + 10);
								IMembers.IncreaseCritDamage((nSkillGrade * 10) + 10);
								IMembers.UpdateBuff(BuffNames::CDType, BuffNames::BuffTime, xSkill.GetGrade());
								IMembers.UpdateBuff(BuffNames::CDTime, BuffNames::BuffTime, GetTickCount() + (1000 * (5 + (nSkillGrade * 5))));
							}
						}
					}
					CIOObject::Release(Party);
				}
			}
			else {
				if (!IPlayer.GetBuffValue(BuffNames::CDTime))
				{
					IPlayer.SetBuffIcon(1000 * (5 + (nSkillGrade * 5)), 0, 4245, 953);
					IPlayer.IncreaseCritRate((nSkillGrade * 10) + 10);
					IPlayer.IncreaseCritDamage((nSkillGrade * 10) + 10);
					IPlayer.UpdateBuff(BuffNames::CDType, BuffNames::BuffTime, xSkill.GetGrade());
					IPlayer.UpdateBuff(BuffNames::CDTime, BuffNames::BuffTime, GetTickCount() + (1000 * (5 + (nSkillGrade * 5))));
				}
			}
		}
	}
}
void __fastcall CriticalStrike(IChar IPlayer, int pPacket, int pPos)
{
	int pSkill = IPlayer.GetSkillPointer(90);

	if (IPlayer.IsValid() && pSkill)
	{
		ISkill xSkill((void*)pSkill);
		int nSkillGrade = xSkill.GetGrade();
		int nTargetID = 0; char bType = 0; void *pTarget = 0;
		CPacket::Read((char*)pPacket, (char*)pPos, "bd", &bType, &nTargetID);
		int nMana = (50 + (3 * (IPlayer.GetLevel() + nSkillGrade)));

		TargetFind myTarget(bType, 0, nTargetID);
		pTarget = myTarget.getTarget();

		if (bType >= 2)
			return;

		if (pTarget && nSkillGrade && IPlayer.IsValid())
		{
			if (IPlayer.GetCurMp() < nMana) {

				return;
			}

			IChar Target(pTarget);

			if (IPlayer.IsValid() && Target.IsValid())
			{
				if (pTarget == IPlayer.GetOffset()) {

					return;
				}

				if (!IPlayer.IsInRange(Target, 300)) {

					return;
				}

				int nDmg = (IPlayer.GetAttack() * NCSMul) + (nSkillGrade * CTools::Rate(NCSMin, NCSMax));

				if (Target.GetType() == 0)
					nDmg = nDmg * NCSReduce / 100;

				IPlayer.OktayDamageSingle(Target, nDmg, 90);
				IPlayer.SetDirection(Target);
				IPlayer.DecreaseMana(nMana);
				IPlayer.OktayDamageSingle(Target, nDmg, 90);
			}
		}
		else {
			IPlayer.CouldntExecuteSkill();
		}

	}
}
void __fastcall DestroyingArmor(IChar IPlayer)
{
	int pSkill = IPlayer.GetSkillPointer(93);

	if (IPlayer.IsValid() && pSkill)
	{
		ISkill xSkill((void*)pSkill);
		int nSkillGrade = xSkill.GetGrade();
		int nMana = 180 + (1.25 * (nSkillGrade * (IPlayer.GetLevel() + nSkillGrade)));

		if (IPlayer.GetCurMp() < nMana)
			return;

		if (IPlayer.IsValid())
		{
			int Around = IPlayer.GetObjectListAround(3);

			while (Around)
			{
				IChar Object((void*)CBaseList::Offset((void*)Around));

				if (Object.IsValid() && IPlayer.IsValid() && (*(int(__thiscall **)(int, int, DWORD))(*(DWORD *)IPlayer.GetOffset() + 176))((int)IPlayer.GetOffset(), (int)Object.GetOffset(), 0))
				{
					int nDmg = (IPlayer.GetAttack() * NDAMul) + (nSkillGrade * CTools::Rate(NDAMin, NDAMax));

					if (Object.GetType() == 0)
						nDmg = (nDmg * NDAReduce) / 100;

					IPlayer.OktayDamageArea(Object, nDmg, 93);
				}

				Around = CBaseList::Pop((void*)Around);
			}

			IPlayer._ShowBattleAnimation(IPlayer, 93);
			IPlayer.DecreaseMana(nMana);
		}
	}
}
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
void __fastcall GhostFlash(IChar IPlayer, int pPacket, int pPos)
{
	int pSkill = IPlayer.GetSkillPointer(14);

	if (IPlayer.IsValid() && pSkill)
	{
		ISkill xSkill((void*)pSkill);
		int nSkillGrade = xSkill.GetGrade();
		int nTargetID = 0; char bType = 0; void *pTarget = 0;
		CPacket::Read((char*)pPacket, (char*)pPos, "bd", &bType, &nTargetID);
		int nMana = (13 + (nSkillGrade * 2));

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

				int nDmg = IPlayer.GetDamage(14, Target.GetOffset());
				if (Target.GetType() == 0) nDmg = (nDmg * SHMGF) / 100;
				IPlayer.OktayDamageSingle(Target, nDmg, 14);
				IPlayer.SetDirection(Target);
				IPlayer.DecreaseMana(nMana);
			}
		}
		else {
			IPlayer.CouldntExecuteSkill();
		}

	}
}
void __fastcall Hiding(IChar IPlayer)
{
	int pSkill = IPlayer.GetSkillPointer(6);

	if (IPlayer.IsValid() && pSkill)
	{
		ISkill xSkill((void*)pSkill);
		int hide = xSkill.GetGrade(), sstep = 0, time = 0, nMana = 0;
		int sstepcheck = IPlayer.GetSkillPointer(27);
		int dbreath = IPlayer.GetSkillPointer(24);
		nMana = hide * 10 + 10;
		time = (hide * 5) + 15;

		if (dbreath)
			time += 10;

		if (sstepcheck)
			sstep = 1;

		if (IPlayer.GetCurMp() < nMana)
			return;

		if (!IPlayer.IsBuff(329))
			IPlayer.SendGStateEx(IPlayer.GetGStateEx() + 16);

		if (sstep)
			IPlayer.Buff(40, time, -50 + 20);
		else
			IPlayer.Buff(40, time, -50);

		IPlayer.RemoveBuffIcon(0, 0, 0, 54);
		IPlayer._ShowBattleAnimation(IPlayer, 6, hide);
		IPlayer.Buff(329, time, 0);
		IPlayer.DecreaseMana(nMana);
	}
}

void __fastcall StrikeOfGod(IChar IPlayer)
{
	int pSkill = IPlayer.GetSkillPointer(91);

	if (IPlayer.IsValid() && pSkill)
	{
		ISkill xSkill((void*)pSkill);
		int nMana = 180 + (1.25 * (xSkill.GetGrade() * (IPlayer.GetLevel() + xSkill.GetGrade())));

		if (IPlayer.GetCurMp() < nMana)
			return;

		if (IPlayer.IsValid())
		{
			int Around = IPlayer.GetObjectListAround(3);

			while (Around)
			{
				IChar Object((void*)CBaseList::Offset((void*)Around));

				if (Object.IsValid() && IPlayer.IsValid() && (*(int(__thiscall **)(int, int, DWORD))(*(DWORD *)IPlayer.GetOffset() + 176))((int)IPlayer.GetOffset(), (int)Object.GetOffset(), 0))
				{
					int nDmg = (IPlayer.GetAttack() * NSOGMul) + (xSkill.GetGrade() * CTools::Rate(NSOGMin, NSOGMax));

					if (Object.GetType() == 0)
						nDmg = nDmg * NSOGReduce / 100;

					IPlayer.OktayDamageArea(Object, nDmg, 91);
				}

				Around = CBaseList::Pop((void*)Around);
			}

			IPlayer._ShowBattleAnimation(IPlayer, 91);
			IPlayer.DecreaseMana(nMana);
		}
	}
}