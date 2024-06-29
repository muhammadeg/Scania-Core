void __fastcall AmplificationOfBlood(IChar IPlayer, int pPacket, int pPos)
{
	int pSkill = IPlayer.GetSkillPointer(38);

	if (IPlayer.IsValid() && pSkill)
	{
		ISkill xSkill((void*)pSkill);
		int nSkillGrade = xSkill.GetGrade();
		int nTargetID = 0; char bType = 0; void *pTarget = 0;
		CPacket::Read((char*)pPacket, (char*)pPos, "bd", &bType, &nTargetID);
		int nMana = (106 + (nSkillGrade * 2));

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

				int XpSkill = IPlayer.GetSkillPointer(41);

				if (XpSkill)
				{
					ISkill xSkillx((void*)XpSkill);
					if (xSkillx.GetGrade() <= CTools::Rate(0, 6)) IPlayer.DecreaseHp((IPlayer.GetCurHp() * 5) / 100);
				}
				else {
					IPlayer.DecreaseHp((IPlayer.GetCurHp() * 5) / 100);
				}

				int nDmg = IPlayer.GetDamage(38, Target.GetOffset());
				if (Target.GetType() == 0) nDmg = (nDmg * SHMAOB) / 100;
				IPlayer._ShowBattleAnimation(Target, 38);
				IPlayer.SetDirection(Target);
				IPlayer.DecreaseMana(nMana);

				int Around = Target.GetObjectListAround(1);
				while (Around)
				{
					IChar Object((void*)CBaseList::Offset((void*)Around));
					if (Object.IsValid() && IPlayer.IsValid() && (*(int(__thiscall **)(int, int, DWORD))(*(DWORD *)IPlayer.GetOffset() + 176))((int)IPlayer.GetOffset(), (int)Object.GetOffset(), 0))
						IPlayer.OktayDamageArea(Object, nDmg, 38);

					Around = CBaseList::Pop((void*)Around);
				}
			}
		}
		else {
			IPlayer.CouldntExecuteSkill();
		}

	}
}

void __fastcall Collapse(IChar IPlayer, int pPacket, int pPos)
{
	int pSkill = IPlayer.GetSkillPointer(44);

	if (IPlayer.IsValid() && pSkill)
	{
		ISkill xSkill((void*)pSkill);
		int nSkillGrade = xSkill.GetGrade();
		int nTargetID = 0; char bType = 0; void *pTarget = 0;
		CPacket::Read((char*)pPacket, (char*)pPos, "bd", &bType, &nTargetID);
		int nMana = (111 + (nSkillGrade * 2));

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

				int nDmg = IPlayer.GetDamage(44, Target.GetOffset());
				if (Target.GetType() == 0) nDmg = (nDmg * SHMC) / 100;
				IPlayer.OktayDamageSingle(Target, nDmg, 44);
				IPlayer.SetDirection(Target);
				IPlayer.DecreaseMana(nMana);
			}
		}
		else {
			IPlayer.CouldntExecuteSkill();
		}

	}
}
void __fastcall DrainBlood(IChar IPlayer, int pPacket, int pPos)
{
	int pSkill = IPlayer.GetSkillPointer(28);

	if (IPlayer.IsValid() && pSkill)
	{
		ISkill xSkill((void*)pSkill);
		int nSkillGrade = xSkill.GetGrade();
		int nTargetID = 0; char bType = 0; void *pTarget = 0;
		CPacket::Read((char*)pPacket, (char*)pPos, "bd", &bType, &nTargetID);
		int nMana = (150 + (nSkillGrade * 2));

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

				int nDmg = IPlayer.GetDamage(28, Target.GetOffset());
				if (Target.GetType() == 0) nDmg = (nDmg * SHMDB) / 100;
				IPlayer._ShowBattleAnimation(Target, 28);
				IPlayer.SetDirection(Target);
				IPlayer.DecreaseMana(nMana);
				IPlayer.IncreaseHp(nDmg);

				int Around = Target.GetObjectListAround(3);
				while (Around)
				{
					IChar Object((void*)CBaseList::Offset((void*)Around));

					if (Object.IsValid() && IPlayer.IsValid() && (*(int(__thiscall **)(int, int, DWORD))(*(DWORD *)IPlayer.GetOffset() + 176))((int)IPlayer.GetOffset(), (int)Object.GetOffset(), 0))
						IPlayer.OktayDamageArea(Object, nDmg, 28);

					Around = CBaseList::Pop((void*)Around);
				}
			}
		}
		else {
			IPlayer.CouldntExecuteSkill();
		}

	}
}
void __fastcall Entangling(IChar IPlayer, int pPacket, int pPos)
{
	int pSkill = IPlayer.GetSkillPointer(25);

	if (IPlayer.IsValid() && pSkill)
	{
		ISkill xSkill((void*)pSkill);
		int nSkillGrade = xSkill.GetGrade();
		int nTargetID = 0; char bType = 0; void *pTarget = 0;
		CPacket::Read((char*)pPacket, (char*)pPos, "bd", &bType, &nTargetID);
		int nMana = (nSkillGrade * 2) + 100; int SetTime = 0;

		TargetFind myTarget(bType, 0, nTargetID);
		pTarget = myTarget.getTarget();

		if (bType >= 2)
			return;

		if (pTarget && IPlayer.IsValid() && IPlayer.GetCurMp() >= nMana && nSkillGrade)
		{
			IChar ITarget(pTarget);

			int XpSkill = IPlayer.GetSkillPointer(31);

			if (XpSkill)
			{
				ISkill xSkillx((void*)XpSkill);
				SetTime += xSkillx.GetGrade();
			}

			if (ITarget.IsValid() && IPlayer.IsValid())
			{
				if (!IPlayer.IsInRange(ITarget, 300)) {

					return;
				}

				IPlayer.DecreaseMana(nMana);
				IPlayer._ShowBattleAnimation(ITarget, 25);

				if (bType == 0)
				{
					if (IPlayer.IsOnline() && IPlayer.GetLevel() >= ITarget.GetLevel() - 20) ITarget.Buff(8, (nSkillGrade * 5) + 2 + SetTime, 0);
				}
				else {
					int Around = ITarget.GetObjectListAround(2);

					while (Around)
					{
						IChar Object((void*)CBaseList::Offset((void*)Around));
						if (Object.IsValid() && IPlayer.IsValid() && (*(int(__thiscall **)(int, int, DWORD))(*(DWORD *)IPlayer.GetOffset() + 176))((int)IPlayer.GetOffset(), (int)Object.GetOffset(), 0))
						{
							if (IPlayer.IsOnline() && IPlayer.GetLevel() >= Object.GetLevel() - 20)
								Object.Buff(8, (nSkillGrade * 5) + 2 + SetTime, 0);
						}
						Around = CBaseList::Pop((void*)Around);
					}
				}
			}
		}

	}
}
void __fastcall ExplodingSpirit(IChar IPlayer, int pPacket, int pPos)
{
	int pSkill = IPlayer.GetSkillPointer(47);

	if (!IPlayer.IsBuff(406))
		return;

	if (IPlayer.IsValid() && pSkill)
	{
		ISkill xSkill((void*)pSkill);
		int nSkillGrade = xSkill.GetGrade();
		int nTargetID = 0; char bType = 0; void *pTarget = 0;
		CPacket::Read((char*)pPacket, (char*)pPos, "bd", &bType, &nTargetID);
		int nMana = (120 + (nSkillGrade * 2)); int ExtraDamage = 0;
		int XpSkill = IPlayer.GetSkillPointer(32);

		if (XpSkill)
		{
			ISkill xSkillx((void*)XpSkill);
			ExtraDamage = 5 * xSkillx.GetGrade();
		}

		if (IPlayer.IsBuff(412))
		{
			ExtraDamage += IPlayer.GetBuffValue(412);
		}

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

				int nDmg = IPlayer.GetDamage(47, Target.GetOffset());
				IPlayer._ShowBattleAnimation(Target, 47);
				IPlayer.SetDirection(Target);
				IPlayer.DecreaseMana(nMana);
				IPlayer.IncreaseHp(nDmg);

				int Around = Target.GetObjectListAround(3);
				while (Around)
				{
					IChar Object((void*)CBaseList::Offset((void*)Around));

					if (Object.IsValid() && IPlayer.IsValid() && (*(int(__thiscall **)(int, int, DWORD))(*(DWORD *)IPlayer.GetOffset() + 176))((int)IPlayer.GetOffset(), (int)Object.GetOffset(), 0))
						IPlayer.OktayDamageArea(Object, nDmg, 47);

					Around = CBaseList::Pop((void*)Around);
				}
			}
		}
		else {
			IPlayer.CouldntExecuteSkill();
		}

	}
}
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
							if (CChar::GetRange((int)IPlayer.GetOffset() + 332, Members + 332) <= 300 && !IMembers.IsBuff(414))
							{
								int Adding = IPlayer.GetDamage(93, IPlayer.GetOffset());
								IMembers.SetBuffIcon(1000 * ((nSkillGrade * 60) + 240), 0, 9109, 1018);
								IMembers.AddAgi(Adding);
								IMembers.AddStr(Adding);
								IMembers.AddHp(Adding);
								IMembers.AddWis(Adding);
								IMembers.AddInt(Adding);
								IMembers.Buff(413, (nSkillGrade * 60) + 240, (int)IPlayer.GetOffset());
								IMembers.Buff(414, (nSkillGrade * 100) + 240, Adding);
							}
						}
					}
					CIOObject::Release(Party);
				}
			}
			else {
				if (!IPlayer.IsBuff(414))
				{
					int Adding = IPlayer.GetDamage(93, IPlayer.GetOffset());
					IPlayer.SetBuffIcon(1000 * ((nSkillGrade * 60) + 240), 0, 9109, 1018);
					IPlayer.AddAgi(Adding);
					IPlayer.AddStr(Adding);
					IPlayer.AddHp(Adding);
					IPlayer.AddWis(Adding);
					IPlayer.AddInt(Adding);
					IPlayer.Buff(413, (nSkillGrade * 60) + 240, (int)IPlayer.GetOffset());
					IPlayer.Buff(414, (nSkillGrade * 100) + 240, Adding);
				}
			}
		}
	}
}
void __fastcall GhostKnife(IChar IPlayer, int pPacket, int pPos)
{
	int pSkill = IPlayer.GetSkillPointer(13);

	if (IPlayer.IsValid() && pSkill)
	{
		ISkill xSkill((void*)pSkill);
		int nSkillGrade = xSkill.GetGrade();
		int nTargetID = 0; char bType = 0; void *pTarget = 0;
		CPacket::Read((char*)pPacket, (char*)pPos, "bd", &bType, &nTargetID);
		int nMana = (7 + (nSkillGrade * 2));

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

				int nDmg = IPlayer.GetDamage(13, Target.GetOffset());
				if (Target.GetType() == 0) nDmg = (nDmg * SHMGK) / 100;
				IPlayer.OktayDamageSingle(Target, nDmg, 13);
				IPlayer.SetDirection(Target);
				IPlayer.DecreaseMana(nMana);
			}
		}
		else {
			IPlayer.CouldntExecuteSkill();
		}

	}
}
void __fastcall GhostWindow(IChar IPlayer, int pPacket, int pPos)
{
	int pSkill = IPlayer.GetSkillPointer(19);

	if (IPlayer.IsValid() && pSkill)
	{
		ISkill xSkill((void*)pSkill);
		int nSkillGrade = xSkill.GetGrade();
		int nTargetID = 0; char bType = 0; void *pTarget = 0;
		CPacket::Read((char*)pPacket, (char*)pPos, "bd", &bType, &nTargetID);
		int nMana = (55 + (nSkillGrade * 2));

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

				int nDmg = IPlayer.GetDamage(19, Target.GetOffset());
				if (Target.GetType() == 0) nDmg = (nDmg * SHMGW) / 100;
				IPlayer.OktayDamageSingle(Target, nDmg, 19);
				IPlayer.SetDirection(Target);
				IPlayer.DecreaseMana(nMana);
			}
		}
		else {
			IPlayer.CouldntExecuteSkill();
		}

	}
}
void __fastcall JeungjangKing(IChar IPlayer, int pPacket, int pPos)
{
	int pSkill = IPlayer.GetSkillPointer(37);

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
		IPlayer._ShowBattleAnimation(IPlayer, 37);

		if (IPlayer.IsValid())
		{
			int Dmg = IPlayer.GetDamage(37, IPlayer.GetOffset());
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
							if (CChar::GetRange((int)IPlayer.GetOffset() + 332, Members + 332) <= 300 && !IMembers.IsBuff(404))
							{
								IMembers.SetBuffIcon(1000 * ((nSkillGrade * 60) + ExtraTime), 0, 9105, 1014);
								IMembers.AddMaxAttack(Dmg);
								IMembers.AddMinAttack(Dmg);
								IMembers.Buff(403, (nSkillGrade * 60) + ExtraTime, (int)IPlayer.GetOffset());
								IMembers.Buff(404, nSkillGrade * 100, Dmg);
							}
						}
					}
					CIOObject::Release(Party);
				}
			}
			else {
				if (!IPlayer.IsBuff(404))
				{
					IPlayer.SetBuffIcon(1000 * ((nSkillGrade * 60) + ExtraTime), 0, 9105, 1014);
					IPlayer.AddMaxAttack(Dmg);
					IPlayer.AddMinAttack(Dmg);
					IPlayer.Buff(403, (nSkillGrade * 60) + ExtraTime, (int)IPlayer.GetOffset());
					IPlayer.Buff(404, nSkillGrade * 100, Dmg);
				}
			}
		}
	}
}
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

		if (IPlayer.IsValid())
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
								IMembers.SetBuffIcon(1000 * ((nSkillGrade * 60) + ExtraTime), 0, 9108, 1017);
								IMembers.AddMaxAttack(Dmg);
								IMembers.AddMinAttack(Dmg);
								IMembers.Buff(407, (nSkillGrade * 60) + ExtraTime, (int)IPlayer.GetOffset());
								IMembers.Buff(408, nSkillGrade * 100, Dmg);
							}
						}
					}
					CIOObject::Release(Party);
				}
			}
			else {
				if (!IPlayer.IsBuff(408))
				{
					IPlayer.SetBuffIcon(1000 * ((nSkillGrade * 60) + ExtraTime), 0, 9108, 1017);
					IPlayer.AddMaxAttack(Dmg);
					IPlayer.AddMinAttack(Dmg);
					IPlayer.Buff(407, (nSkillGrade * 60) + ExtraTime, (int)IPlayer.GetOffset());
					IPlayer.Buff(408, nSkillGrade * 100, Dmg);
				}
			}
		}
	}
}
void __fastcall MagicalExplosion(IChar IPlayer, int pPacket, int pPos)
{
	int pSkill = IPlayer.GetSkillPointer(54);

	if (!IPlayer.IsBuff(406))
		return;

	if (IPlayer.IsValid() && pSkill)
	{
		ISkill xSkill((void*)pSkill);
		int nSkillGrade = xSkill.GetGrade();
		int nTargetID = 0; char bType = 0; void *pTarget = 0;
		CPacket::Read((char*)pPacket, (char*)pPos, "bd", &bType, &nTargetID);
		int nMana = (90 + (nSkillGrade * 2)); int ExtraDamage = 0;
		int XpSkill = IPlayer.GetSkillPointer(32);

		if (XpSkill)
		{
			ISkill xSkillx((void*)XpSkill);
			ExtraDamage = 5 * xSkillx.GetGrade();
		}

		if (IPlayer.IsBuff(412))
		{
			ExtraDamage += IPlayer.GetBuffValue(412);
		}

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

				int nDmg = (((IPlayer.GetMaxMagAttack() + ExtraDamage) + ((((IPlayer.GetMaxMagAttack() + ExtraDamage) / 4) + IPlayer.GetDamage(54, Target.GetOffset())))));
				if (Target.GetType() == 0) nDmg = (nDmg * SHMME) / 100;
				IPlayer.OktayDamageSingle(Target, nDmg, 54);
				IPlayer.SetDirection(Target);
				IPlayer.DecreaseMana(nMana);
			}
		}
		else {
			IPlayer.CouldntExecuteSkill();
		}

	}
}
void __fastcall MentalBreakdown(IChar IPlayer, int pPacket, int pPos)
{
	int pSkill = IPlayer.GetSkillPointer(29);

	if (!IPlayer.IsBuff(406))
		return;

	if (IPlayer.IsValid() && pSkill)
	{
		ISkill xSkill((void*)pSkill);
		int nSkillGrade = xSkill.GetGrade();
		int nTargetID = 0; char bType = 0; void *pTarget = 0;
		CPacket::Read((char*)pPacket, (char*)pPos, "bd", &bType, &nTargetID);
		int nMana = (150 + (nSkillGrade * 2));  int ExtraDamage = 0;
		int XpSkill = IPlayer.GetSkillPointer(32);

		if (XpSkill)
		{
			ISkill xSkillx((void*)XpSkill);
			ExtraDamage = 5 * xSkillx.GetGrade();
		}

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

				int Around = Target.GetObjectListAround(3);
				IPlayer._ShowBattleAnimation(Target, 29);
				IPlayer.SetDirection(Target);
				IPlayer.DecreaseMana(nMana);

				while (Around)
				{
					IChar Object((void*)CBaseList::Offset((void*)Around));

					if (Object.IsValid() && IPlayer.IsValid() && (*(int(__thiscall **)(int, int, DWORD))(*(DWORD *)IPlayer.GetOffset() + 176))((int)IPlayer.GetOffset(), (int)Object.GetOffset(), 0))
					{
						if (IPlayer.IsOnline() && IPlayer.GetLevel() >= Object.GetLevel() - 20 && !Object.IsBuff(411) && !Object.IsBuff(415) && !Object.IsBuff(416))
						{
							int Atk = (Object.GetMaxPhyAttack() * nSkillGrade) / 100;
							int Def = (Object.GetDef() * nSkillGrade) / 100;
							int Otp = (CChar::GetHit((int)Object.GetOffset()) * nSkillGrade) / 100;
							Object.Buff(411, (nSkillGrade * 20) + 2, Atk);
							Object.Buff(415, (nSkillGrade * 20) + 2, Def);
							Object.Buff(416, (nSkillGrade * 20) + 2, Otp);
							Object.RemoveMaxAttack(Atk);
							Object.RemoveMinAttack(Atk);
							Object.RemoveDef(Def);
							Object.RemoveOTP(Otp);
						}
					}

					Around = CBaseList::Pop((void*)Around);
				}
			}
		}
		else {
			IPlayer.CouldntExecuteSkill();
		}

	}
}
void __fastcall MudRoom(IChar IPlayer, int pPacket, int pPos)
{
	int pSkill = IPlayer.GetSkillPointer(20);

	if (IPlayer.IsValid() && pSkill)
	{
		ISkill xSkill((void*)pSkill);
		int nSkillGrade = xSkill.GetGrade();
		int nMana = (nSkillGrade * 2) + 80;
		int Time = nSkillGrade * 60;

		if (IPlayer.IsValid() && IPlayer.GetCurMp() >= nMana && nSkillGrade)
		{
			if (IPlayer.IsValid() && !IPlayer.IsBuff(399))
			{
				IPlayer.DecreaseMana(nMana);
				IPlayer._ShowBattleAnimation(IPlayer, 20);
				if (nSkillGrade == 1) IPlayer.Buff(398, 5 + Time, 0);
				if (nSkillGrade == 2) IPlayer.Buff(398, 1000, 0);
				if (nSkillGrade == 3) IPlayer.Buff(398, 2000, 0);
				if (nSkillGrade == 4) IPlayer.Buff(398, 3000, 0);
				if (nSkillGrade == 5) IPlayer.Buff(398, 4000, 0);
				if (nSkillGrade == 6) IPlayer.Buff(398, 5000, 0);
				if (nSkillGrade == 7) IPlayer.Buff(398, 6000, 0);
				if (nSkillGrade == 8) IPlayer.Buff(398, 7000, 0);
				if (nSkillGrade == 9) IPlayer.Buff(398, 8000, 0);
				if (nSkillGrade == 10) IPlayer.Buff(398, 9000, 0);
				IPlayer.Buff(399, 10000, 0);
				IPlayer.AddDef(nSkillGrade);
				IPlayer.AddAbsorb(nSkillGrade);
				IPlayer.SetBuffIcon(Time * 1000, 0, 9101, 1010);
			}
		}
	}
}
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

		if (IPlayer.IsValid())
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
								IMembers.SetBuffIcon(1000 * ((nSkillGrade * 60) + ExtraTime), 0, 9104, 1013);
								IMembers.IncreaseMaxHp(Dmg);
								IMembers.Buff(401, (nSkillGrade * 60) + ExtraTime, (int)IPlayer.GetOffset());
								IMembers.Buff(402, nSkillGrade * 100, Dmg);
							}
						}
					}
					CIOObject::Release(Party);
				}
			}
			else {
				if (!IPlayer.IsBuff(402))
				{
					IPlayer.SetBuffIcon(1000 * ((nSkillGrade * 60) + ExtraTime), 0, 9104, 1013);
					IPlayer.IncreaseMaxHp(Dmg);
					IPlayer.Buff(401, (nSkillGrade * 60) + ExtraTime, (int)IPlayer.GetOffset());
					IPlayer.Buff(402, nSkillGrade * 100, Dmg);
				}
			}
		}
	}
}
void __fastcall JigukKingOfTaein(IChar IPlayer, int pPacket, int pPos)
{
	int pSkill = IPlayer.GetSkillPointer(50);

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
		IPlayer._ShowBattleAnimation(IPlayer, 50);

		if (IPlayer.IsValid())
		{
			int Dmg = IPlayer.GetDamage(50, IPlayer.GetOffset());
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
							if (CChar::GetRange((int)IPlayer.GetOffset() + 332, Members + 332) <= 300 && !IMembers.IsBuff(410))
							{
								IMembers.SetBuffIcon(1000 * ((nSkillGrade * 60) + ExtraTime), 0, 9107, 1016);
								IMembers.IncreaseMaxHp(Dmg);
								IMembers.Buff(409, (nSkillGrade * 60) + ExtraTime, (int)IPlayer.GetOffset());
								IMembers.Buff(410, nSkillGrade * 100, Dmg);
							}
						}
					}
					CIOObject::Release(Party);
				}
			}
			else {
				if (!IPlayer.IsBuff(410))
				{
					IPlayer.SetBuffIcon(1000 * ((nSkillGrade * 60) + ExtraTime), 0, 9107, 1016);
					IPlayer.IncreaseMaxHp(Dmg);
					IPlayer.Buff(409, (nSkillGrade * 60) + ExtraTime, (int)IPlayer.GetOffset());
					IPlayer.Buff(410, nSkillGrade * 100, Dmg);
				}
			}
		}
	}
}
void __fastcall RisingKing4th(IChar IPlayer, int pPacket, int pPos)
{
	int pSkill = IPlayer.GetSkillPointer(91);

	if (IPlayer.IsValid() && pSkill)
	{
		ISkill xSkill((void*)pSkill);
		int nSkillGrade = xSkill.GetGrade();
		int nTargetID = 0; char bType = 0; void *pTarget = 0;
		CPacket::Read((char*)pPacket, (char*)pPos, "bd", &bType, &nTargetID);
		int nMana = (60 + (nSkillGrade * 3));

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

				int nDmg = IPlayer.GetDamage(91, Target.GetOffset());
				if (Target.GetType() == 0) nDmg = (nDmg * SHMRK) / 100;
				IPlayer._ShowBattleAnimation(Target, 91);
				IPlayer.SetDirection(Target);
				IPlayer.DecreaseMana(nMana);
				IPlayer.IncreaseHp(nDmg);

				int Around = Target.GetObjectListAround(3);
				while (Around)
				{
					IChar Object((void*)CBaseList::Offset((void*)Around));

					if (Object.IsValid() && IPlayer.IsValid() && (*(int(__thiscall **)(int, int, DWORD))(*(DWORD *)IPlayer.GetOffset() + 176))((int)IPlayer.GetOffset(), (int)Object.GetOffset(), 0))
						IPlayer.OktayDamageArea(Object, nDmg, 91);


					Around = CBaseList::Pop((void*)Around);
				}
			}
		}
		else {
			IPlayer.CouldntExecuteSkill();
		}

	}
}
void __fastcall SixSouls(IChar IPlayer, int pPacket, int pPos)
{
	int pSkill = IPlayer.GetSkillPointer(46);

	if (IPlayer.IsValid() && pSkill)
	{
		ISkill xSkill((void*)pSkill);
		int nSkillGrade = xSkill.GetGrade();
		int nTargetID = 0; char bType = 0; void *pTarget = 0;
		CPacket::Read((char*)pPacket, (char*)pPos, "bd", &bType, &nTargetID);
		int nMana = (120 + (nSkillGrade * 2));

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

				int nDmg = IPlayer.GetDamage(46, Target.GetOffset());
				if (Target.GetType() == 0) nDmg = (nDmg * SHMSS) / 100;
				IPlayer.OktayDamageSingle(Target, nDmg, 46);
				IPlayer.SetDirection(Target);
				IPlayer.DecreaseMana(nMana);
			}
		}
		else {
			IPlayer.CouldntExecuteSkill();
		}

	}
}
void __fastcall SoulBlow(IChar IPlayer, int pPacket, int pPos)
{
	int pSkill = IPlayer.GetSkillPointer(52);

	if (IPlayer.IsValid() && pSkill)
	{
		ISkill xSkill((void*)pSkill);
		int nSkillGrade = xSkill.GetGrade();
		int nTargetID = 0; char bType = 0; void *pTarget = 0;
		CPacket::Read((char*)pPacket, (char*)pPos, "bd", &bType, &nTargetID);
		int nMana = (130 + (nSkillGrade * 2));

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

				int nDmg = IPlayer.GetDamage(52, Target.GetOffset());
				if (Target.GetType() == 0) nDmg = (nDmg * SHMSP) / 100;
				IPlayer.OktayDamageSingle(Target, nDmg, 52);
				IPlayer.SetDirection(Target);
				IPlayer.DecreaseMana(nMana);
			}
		}
		else {
			IPlayer.CouldntExecuteSkill();
		}

	}
}
void __fastcall SoulShield(IChar IPlayer, int pPacket, int pPos)
{
	int pSkill = IPlayer.GetSkillPointer(15);

	if (IPlayer.IsValid() && pSkill)
	{
		ISkill xSkill((void*)pSkill);
		int nSkillGrade = xSkill.GetGrade();
		int nMana = (nSkillGrade * 2) + 50;
		int Time = 60 + (nSkillGrade * 60);

		if (IPlayer.IsValid() && IPlayer.GetCurMp() >= nMana && nSkillGrade)
		{
			if (IPlayer.IsValid() && !IPlayer.IsBuff(397))
			{
				IPlayer.DecreaseMana(nMana);
				IPlayer._ShowBattleAnimation(IPlayer, 15);
				if (nSkillGrade == 1) IPlayer.Buff(396, 5 + Time, 0);
				if (nSkillGrade == 2) IPlayer.Buff(396, 1000, 0);
				if (nSkillGrade == 3) IPlayer.Buff(396, 2000, 0);
				if (nSkillGrade == 4) IPlayer.Buff(396, 3000, 0);
				if (nSkillGrade == 5) IPlayer.Buff(396, 4000, 0);
				if (nSkillGrade == 6) IPlayer.Buff(396, 5000, 0);
				if (nSkillGrade == 7) IPlayer.Buff(396, 6000, 0);
				if (nSkillGrade == 8) IPlayer.Buff(396, 7000, 0);
				if (nSkillGrade == 9) IPlayer.Buff(396, 8000, 0);
				if (nSkillGrade == 10) IPlayer.Buff(396, 9000, 0);
				IPlayer.Buff(397, 10000, 0);
				IPlayer.AddDef(6 * nSkillGrade);
				IPlayer.SetBuffIcon(Time * 1000, 0, 9100, 1009);
			}
		}
	}
}
void __fastcall SpearOfPain(IChar IPlayer, int pPacket, int pPos)
{
	int pSkill = IPlayer.GetSkillPointer(26);

	if (IPlayer.IsValid() && pSkill)
	{
		ISkill xSkill((void*)pSkill);
		int nSkillGrade = xSkill.GetGrade();
		int nTargetID = 0; char bType = 0; void *pTarget = 0;
		CPacket::Read((char*)pPacket, (char*)pPos, "bd", &bType, &nTargetID);
		int nMana = (85 + (nSkillGrade * 2));

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

				int nDmg = IPlayer.GetDamage(26, Target.GetOffset());
				if (Target.GetType() == 0) nDmg = (nDmg * SHMSOP) / 100;
				IPlayer.OktayDamageSingle(Target, nDmg, 26);
				IPlayer.SetDirection(Target);
				IPlayer.DecreaseMana(nMana);
			}
		}
		else {
			IPlayer.CouldntExecuteSkill();
		}

	}
}
void __fastcall SpiritWave(IChar IPlayer, int pPacket, int pPos)
{
	int pSkill = IPlayer.GetSkillPointer(90);

	if (IPlayer.IsValid() && pSkill)
	{
		ISkill xSkill((void*)pSkill);
		int nSkillGrade = xSkill.GetGrade();
		int nTargetID = 0; char bType = 0; void *pTarget = 0;
		CPacket::Read((char*)pPacket, (char*)pPos, "bd", &bType, &nTargetID);
		int nMana = (170 + (nSkillGrade * 2));

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

				int nDmg = IPlayer.GetDamage(90, Target.GetOffset());
				if (Target.GetType() == 0) nDmg = (nDmg * SHMSW) / 100;
				IPlayer._ShowBattleAnimation(Target, 90);
				IPlayer.SetDirection(Target);
				IPlayer.DecreaseMana(nMana);
				IPlayer.IncreaseHp(nDmg);

				int Around = Target.GetObjectListAround(3);
				while (Around)
				{
					IChar Object((void*)CBaseList::Offset((void*)Around));

					if (Object.IsValid() && IPlayer.IsValid() && (*(int(__thiscall **)(int, int, DWORD))(*(DWORD *)IPlayer.GetOffset() + 176))((int)IPlayer.GetOffset(), (int)Object.GetOffset(), 0))
						IPlayer.OktayDamageArea(Object, nDmg, 90);

					Around = CBaseList::Pop((void*)Around);
				}
			}
		}
		else {
			IPlayer.CouldntExecuteSkill();
		}

	}
}
void __fastcall TheSoulsPenance(IChar IPlayer, int pPacket, int pPos)
{
	int pSkill = IPlayer.GetSkillPointer(22);

	if (IPlayer.IsValid() && pSkill)
	{
		ISkill xSkill((void*)pSkill);
		int nSkillGrade = xSkill.GetGrade();
		int nTargetID = 0; char bType = 0; void *pTarget = 0;
		CPacket::Read((char*)pPacket, (char*)pPos, "bd", &bType, &nTargetID);
		int nMana = (60 + (nSkillGrade * 2));

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

				int SetTime = 3;
				int nDmg = IPlayer.GetDamage(22, Target.GetOffset());
				if (Target.GetType() == 0) nDmg = (nDmg * SHMTSP) / 100;
				IPlayer._ShowBattleAnimation(Target, 22);
				IPlayer.SetDirection(Target);
				IPlayer.DecreaseMana(nMana);
				int XpSkill = IPlayer.GetSkillPointer(24);
				int YpSkill = IPlayer.GetSkillPointer(48);

				if (XpSkill && Target.GetType() == 1)
				{
					ISkill xSkillx((void*)XpSkill);
					SetTime += xSkillx.GetGrade() / 2;
				}

				if (YpSkill)
				{
					ISkill ySkilly((void*)YpSkill);
					nDmg += (ySkilly.GetGrade() * 50);
				}

				int Around = Target.GetObjectListAround(3);
				while (Around)
				{
					IChar Object((void*)CBaseList::Offset((void*)Around));

					if (Object.IsValid() && IPlayer.IsValid() && (*(int(__thiscall **)(int, int, DWORD))(*(DWORD *)IPlayer.GetOffset() + 176))((int)IPlayer.GetOffset(), (int)Object.GetOffset(), 0))
					{
						IPlayer.OktayDamageArea(Object, nDmg, 22);
						if (nDmg && (int)Object.GetOffset() != (int)IPlayer.GetOffset()){
							if (Object.GetType() == 1)
								Object.Buff(400, SetTime, nDmg*0.65);
							else
								Object.Buff(400, SetTime, nDmg*0.38);
						}
					}

					Around = CBaseList::Pop((void*)Around);
				}
				//IPlayer.Buff(3124,SetTime+1,0);
			}
		}
		else {
			IPlayer.CouldntExecuteSkill();
		}

	}
}
void __fastcall Wave(IChar IPlayer, int pPacket, int pPos)
{
	int pSkill = IPlayer.GetSkillPointer(18);

	if (IPlayer.IsValid() && pSkill)
	{
		ISkill xSkill((void*)pSkill);
		int nSkillGrade = xSkill.GetGrade();
		int nTargetID = 0; char bType = 0; void *pTarget = 0;
		CPacket::Read((char*)pPacket, (char*)pPos, "bd", &bType, &nTargetID);
		int nMana = (35 + (nSkillGrade * 2));

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

				int nDmg = IPlayer.GetDamage(18, Target.GetOffset());
				if (Target.GetType() == 0) nDmg = (nDmg * SHMW) / 100;
				IPlayer.OktayDamageSingle(Target, nDmg, 18);
				IPlayer.SetDirection(Target);
				IPlayer.DecreaseMana(nMana);
			}
		}
		else {
			IPlayer.CouldntExecuteSkill();
		}

	}
}
void __fastcall WaveOfEmperor(IChar IPlayer, int pPacket, int pPos)
{
	int pSkill = IPlayer.GetSkillPointer(39);

	if (IPlayer.IsValid() && pSkill)
	{
		ISkill xSkill((void*)pSkill);
		int nSkillGrade = xSkill.GetGrade();
		int nTargetID = 0; char bType = 0; void *pTarget = 0;
		CPacket::Read((char*)pPacket, (char*)pPos, "bd", &bType, &nTargetID);
		int nMana = (77 + (nSkillGrade * 2));

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

				int nDmg = IPlayer.GetDamage(39, Target.GetOffset());
				if (Target.GetType() == 0) nDmg = (nDmg * SHMWOE) / 100;
				IPlayer._ShowBattleAnimation(Target, 39);
				IPlayer.SetDirection(Target);
				IPlayer.DecreaseMana(nMana);

				int Around = Target.GetObjectListAround(3);
				while (Around)
				{
					IChar Object((void*)CBaseList::Offset((void*)Around));

					if (Object.IsValid() && IPlayer.IsValid() && (*(int(__thiscall **)(int, int, DWORD))(*(DWORD *)IPlayer.GetOffset() + 176))((int)IPlayer.GetOffset(), (int)Object.GetOffset(), 0))
						IPlayer.OktayDamageArea(Object, nDmg, 39);

					Around = CBaseList::Pop((void*)Around);
				}
			}
		}
		else {
			IPlayer.CouldntExecuteSkill();
		}

	}
}
void __fastcall ExecutiveDirector(IChar IPlayer, int pPacket, int pPos)
{
	int pSkill = IPlayer.GetSkillPointer(21);

	if (IPlayer.IsValid() && pSkill)
	{
		ISkill xSkill((void*)pSkill);
		int nSkillGrade = xSkill.GetGrade();
		int nTargetID = 0; char bType = 0; void *pTarget = 0;
		CPacket::Read((char*)pPacket, (char*)pPos, "bd", &bType, &nTargetID);
		int nMana = (60 + (nSkillGrade * 2));

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

				int nDmg = IPlayer.GetDamage(21, Target.GetOffset());
				if (Target.GetType() == 0) nDmg = (nDmg * SHMED) / 100;
				IPlayer._ShowBattleAnimation(Target, 21);
				IPlayer.SetDirection(Target);
				IPlayer.DecreaseMana(nMana);

				int Around = Target.GetObjectListAround(3);
				while (Around)
				{
					IChar Object((void*)CBaseList::Offset((void*)Around));

					if (Object.IsValid() && IPlayer.IsValid() && (int)Object.GetOffset() != (int)IPlayer.GetOffset() && (*(int(__thiscall **)(int, int, DWORD))(*(DWORD *)IPlayer.GetOffset() + 176))((int)IPlayer.GetOffset(), (int)Object.GetOffset(), 0))
						IPlayer.OktayDamageArea(Object, nDmg, 21);

					Around = CBaseList::Pop((void*)Around);
				}
			}
		}
		else {
			IPlayer.CouldntExecuteSkill();
		}

	}
}
void __fastcall Doggebi(IChar IPlayer, int pPacket, int pPos)
{
	int pSkill = IPlayer.GetSkillPointer(92);

	if (IPlayer.IsValid() && pSkill)
	{
		ISkill xSkill((void*)pSkill);
		int nSkillGrade = xSkill.GetGrade();
		int nTargetID = 0; char bType = 0; void *pTarget = 0;
		CPacket::Read((char*)pPacket, (char*)pPos, "bd", &bType, &nTargetID);
		int nMana = (170 + (nSkillGrade * 2));

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

				int nDmg = IPlayer.GetDamage(92, Target.GetOffset());
				if (Target.GetType() == 0) nDmg = (nDmg * SHMD) / 100;

				IPlayer.OktayDamageSingle(Target, nDmg, 92);
				IPlayer.SetDirection(Target);
				IPlayer.DecreaseMana(nMana);
			}
		}
		else {
			IPlayer.CouldntExecuteSkill();
		}

	}
}