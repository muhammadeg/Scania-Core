void __fastcall BlessingOfAgility(int Packet, void *edx, int Player, int Target, int a3)
{
	IChar IPlayer((void*)Player);
	IChar ITarget((void*)Target);
	ISkill ISkill((void*)Packet);

	if (IPlayer.IsValid() && ITarget.IsValid())
	{
		if (ITarget.IsParty())
		{
			void *Party = (void*)CParty::FindParty(ITarget.GetPartyID());

			if (Party)
			{
				for (int i = CParty::GetPlayerList(Party); i; i = CBaseList::Pop((void*)i))
				{
					int Members = *(DWORD*)((void*)i);
					IChar IMembers((void*)*(DWORD*)((void*)i));

					if (CChar::IsNormal(Members) && IPlayer.IsValid())
					{
						if (CChar::GetRange((int)IPlayer.GetOffset() + 332, Members + 332) <= 300)
						{
							IMembers.Buff(48, 1800, 8 * ISkill.GetGrade() + 3);
							IPlayer._ShowBattleAnimation(IMembers, ISkill.GetIndex());
						}
					}
				}
				CIOObject::Release(Party);
			}
		}
		else {
			ITarget.Buff(48, 1800, 8 * ISkill.GetGrade() + 3);
			IPlayer._ShowBattleAnimation(ITarget, ISkill.GetIndex());
		}
	}
}
void __fastcall BlessingOfCriticalHit(int Packet, void *edx, int Player, int Target, int a3)
{
	IChar IPlayer((void*)Player);
	IChar ITarget((void*)Target);
	ISkill ISkill((void*)Packet);

	if (IPlayer.IsValid() && ITarget.IsValid())
	{
		if (ITarget.IsParty())
		{
			void *Party = (void*)CParty::FindParty(ITarget.GetPartyID());

			if (Party)
			{
				for (int i = CParty::GetPlayerList(Party); i; i = CBaseList::Pop((void*)i))
				{
					int Members = *(DWORD*)((void*)i);
					IChar IMembers((void*)*(DWORD*)((void*)i));

					if (CChar::IsNormal(Members) && IPlayer.IsValid())
					{
						if (CChar::GetRange((int)IPlayer.GetOffset() + 332, Members + 332) <= 300)
						{
							IMembers.Buff(50, 1800, 8 * ISkill.GetGrade() + 3);
							IPlayer._ShowBattleAnimation(IMembers, ISkill.GetIndex());
						}
					}
				}
				CIOObject::Release(Party);
			}
		}
		else {
			ITarget.Buff(50, 1800, 8 * ISkill.GetGrade() + 3);
			IPlayer._ShowBattleAnimation(ITarget, ISkill.GetIndex());
		}
	}
}
void __fastcall BlessingOfHealth(int Packet, void *edx, int Player, int Target, int a3)
{
	IChar IPlayer((void*)Player);
	IChar ITarget((void*)Target);
	ISkill ISkill((void*)Packet);

	if (IPlayer.IsValid() && ITarget.IsValid())
	{
		if (ITarget.IsParty())
		{
			void *Party = (void*)CParty::FindParty(ITarget.GetPartyID());

			if (Party)
			{
				for (int i = CParty::GetPlayerList(Party); i; i = CBaseList::Pop((void*)i))
				{
					int Members = *(DWORD*)((void*)i);
					IChar IMembers((void*)*(DWORD*)((void*)i));

					if (CChar::IsNormal(Members) && IPlayer.IsValid())
					{
						if (CChar::GetRange((int)IPlayer.GetOffset() + 332, Members + 332) <= 300)
						{
							IMembers.Buff(47, 1800, 8 * ISkill.GetGrade() + 3);
							IPlayer._ShowBattleAnimation(IMembers, ISkill.GetIndex());
						}
					}
				}
				CIOObject::Release(Party);
			}
		}
		else {
			ITarget.Buff(47, 1800, 8 * ISkill.GetGrade() + 3);
			IPlayer._ShowBattleAnimation(ITarget, ISkill.GetIndex());
		}
	}
}
void __fastcall BlessingOfIntelligence(int Packet, void *edx, int Player, int Target, int a3)
{
	IChar IPlayer((void*)Player);
	IChar ITarget((void*)Target);
	ISkill ISkill((void*)Packet);

	if (IPlayer.IsValid() && ITarget.IsValid())
	{
		if (ITarget.IsParty())
		{
			void *Party = (void*)CParty::FindParty(ITarget.GetPartyID());

			if (Party)
			{
				for (int i = CParty::GetPlayerList(Party); i; i = CBaseList::Pop((void*)i))
				{
					int Members = *(DWORD*)((void*)i);
					IChar IMembers((void*)*(DWORD*)((void*)i));

					if (CChar::IsNormal(Members) && IPlayer.IsValid())
					{
						if (CChar::GetRange((int)IPlayer.GetOffset() + 332, Members + 332) <= 300)
						{
							IMembers.Buff(49, 1800, 8 * ISkill.GetGrade() + 3);
							IPlayer._ShowBattleAnimation(IMembers, ISkill.GetIndex());
						}
					}
				}
				CIOObject::Release(Party);
			}
		}
		else {
			ITarget.Buff(49, 1800, 8 * ISkill.GetGrade() + 3);
			IPlayer._ShowBattleAnimation(ITarget, ISkill.GetIndex());
		}
	}
}
void __fastcall BlessingOfStrength(int Packet, void *edx, int Player, int Target, int a3)
{
	IChar IPlayer((void*)Player);
	IChar ITarget((void*)Target);
	ISkill ISkill((void*)Packet);

	if (IPlayer.IsValid() && ITarget.IsValid())
	{
		if (ITarget.IsParty())
		{
			void *Party = (void*)CParty::FindParty(ITarget.GetPartyID());

			if (Party)
			{
				for (int i = CParty::GetPlayerList(Party); i; i = CBaseList::Pop((void*)i))
				{
					int Members = *(DWORD*)((void*)i);
					IChar IMembers((void*)*(DWORD*)((void*)i));

					if (CChar::IsNormal(Members) && IPlayer.IsValid())
					{
						if (CChar::GetRange((int)IPlayer.GetOffset() + 332, Members + 332) <= 300)
						{
							IMembers.Buff(46, 1800, 8 * ISkill.GetGrade() + 3);
							IPlayer._ShowBattleAnimation(IMembers, ISkill.GetIndex());
						}
					}
				}
				CIOObject::Release(Party);
			}
		}
		else {
			ITarget.Buff(46, 1800, 8 * ISkill.GetGrade() + 3);
			IPlayer._ShowBattleAnimation(ITarget, ISkill.GetIndex());
		}
	}
}
void __fastcall DefenseImprovement(void *pSkill, void *edx, int pPlayer, void *pPacket, int pPos)
{
	IChar IPlayer((void*)pPlayer);
	ISkill ISkill(pSkill);
	int nTargetID = 0; char bType = 0; void *pTarget = 0;
	CPacket::Read((char*)pPacket, (char*)pPos, "bd", &bType, &nTargetID);

	TargetFind myTarget(bType, 0, nTargetID);
	pTarget = myTarget.getTarget();

	if (pTarget && IPlayer.IsValid())
	{
		if ((**(int(__thiscall ***)(DWORD, DWORD, DWORD))pSkill)((int)pSkill, pPlayer, (int)pTarget))
		{
			IChar ITarget(pTarget);

			if (ITarget.IsValid() && IPlayer.IsValid())
			{
				if (IPlayer.GetCurMp() <= ISkill.DecreaseMana()) {

					return;
				}
				else
					IPlayer.DecreaseMana(ISkill.DecreaseMana());

				if (ITarget.IsParty())
				{
					void *Party = (void*)CParty::FindParty(ITarget.GetPartyID());

					if (Party)
					{
						for (int i = CParty::GetPlayerList(Party); i; i = CBaseList::Pop((void*)i))
						{
							int Members = *(DWORD*)((void*)i);
							IChar IMembers((void*)*(DWORD*)((void*)i));

							if (CChar::IsNormal(Members) && IPlayer.IsValid())
							{
								if (CChar::GetRange((int)IPlayer.GetOffset() + 332, Members + 332) <= 300)
								{
									CChar::CancelAllBuff((void *)Members, 37);
									int AddBuff = CBuff::CreateBuff(37, 1800, 30 * *((DWORD *)pSkill + 2) + 5, 20 * *((DWORD *)pSkill + 2) + 5);
									(*(int(__thiscall **)(int, int))(*(DWORD *)Members + 180))(Members, AddBuff);
									IPlayer._ShowBattleAnimation(IMembers, ISkill.GetIndex());
								}
							}
						}
						CIOObject::Release(Party);
					}
				}
				else {
					CChar::CancelAllBuff(ITarget.GetOffset(), 37);
					int AddBuff = CBuff::CreateBuff(37, 1800, 30 * *((DWORD *)pSkill + 2) + 5, 20 * *((DWORD *)pSkill + 2) + 5);
					(*(int(__thiscall **)(int, int))(*(DWORD *)(int)ITarget.GetOffset() + 180))((int)ITarget.GetOffset(), AddBuff);
					IPlayer._ShowBattleAnimation(ITarget, ISkill.GetIndex());
				}
			}
		}
	}

}
void __fastcall RefiningWeapon(void *pSkill, void *edx, int pPlayer, void *pPacket, int pPos)
{
	IChar IPlayer((void*)pPlayer);
	ISkill ISkill(pSkill);
	int nTargetID = 0; char bType = 0; void *pTarget = 0;
	CPacket::Read((char*)pPacket, (char*)pPos, "bd", &bType, &nTargetID);

	TargetFind myTarget(bType, 0, nTargetID);
	pTarget = myTarget.getTarget();

	if (pTarget && IPlayer.IsValid())
	{
		if ((**(int(__thiscall ***)(DWORD, DWORD, DWORD))pSkill)((int)pSkill, pPlayer, (int)pTarget))
		{
			IChar ITarget(pTarget);

			if (ITarget.IsValid() && IPlayer.IsValid())
			{
				if (IPlayer.GetCurMp() < ISkill.DecreaseMana()) {

					return;
				}
				else
					IPlayer.DecreaseMana(ISkill.DecreaseMana());

				if (ITarget.IsParty())
				{
					void *Party = (void*)CParty::FindParty(ITarget.GetPartyID());

					if (Party)
					{
						for (int i = CParty::GetPlayerList(Party); i; i = CBaseList::Pop((void*)i))
						{
							int Members = *(DWORD*)((void*)i);
							IChar IMembers((void*)*(DWORD*)((void*)i));

							if (CChar::IsNormal(Members) && IPlayer.IsValid())
							{
								if (CChar::GetRange((int)IPlayer.GetOffset() + 332, Members + 332) <= 300)
								{
									CChar::CancelAllBuff((void*)Members, 36);
									int AddBuff = CBuff::CreateBuff(36, 1800, 8 * *(DWORD*)((int)pSkill + 8) + 16, (int)pSkill);
									(*(int(__thiscall **)(int, int))(*(DWORD*)Members + 180))(Members, AddBuff);
									IPlayer._ShowBattleAnimation(IMembers, ISkill.GetIndex());
								}
							}
						}
						CIOObject::Release(Party);
					}
				}
				else {
					CChar::CancelAllBuff(ITarget.GetOffset(), 36);
					int AddBuff = CBuff::CreateBuff(36, 1800, 8 * *(DWORD*)((int)pSkill + 8) + 16, (int)pSkill);
					(*(int(__thiscall **)(int, int))(*(DWORD*)(int)ITarget.GetOffset() + 180))((int)ITarget.GetOffset(), AddBuff);
					IPlayer._ShowBattleAnimation(ITarget, ISkill.GetIndex());
				}
			}
		}
	}

}
void __fastcall SpeedUp(void *pSkill, void *edx, int pPlayer, void *pPacket, int pPos)
{
	IChar IPlayer((void*)pPlayer);
	ISkill ISkill(pSkill);
	int nTargetID = 0; char bType = 0; void *pTarget = 0;
	CPacket::Read((char*)pPacket, (char*)pPos, "bd", &bType, &nTargetID);

	TargetFind myTarget(bType, 0, nTargetID);
	pTarget = myTarget.getTarget();

	if (pTarget && IPlayer.IsValid())
	{
		if ((**(int(__thiscall ***)(DWORD, DWORD, DWORD))pSkill)((int)pSkill, pPlayer, (int)pTarget))
		{
			IChar ITarget(pTarget);

			if (ITarget.IsValid() && IPlayer.IsValid())
			{
				if (IPlayer.GetCurMp() < ISkill.DecreaseMana()) {

					return;
				}
				else
					IPlayer.DecreaseMana(ISkill.DecreaseMana());

				if (ITarget.IsParty())
				{
					void *Party = (void*)CParty::FindParty(ITarget.GetPartyID());

					if (Party)
					{
						for (int i = CParty::GetPlayerList(Party); i; i = CBaseList::Pop((void*)i))
						{
							int Members = *(DWORD*)((void*)i);
							IChar IMembers((void*)*(DWORD*)((void*)i));

							if (CChar::IsNormal(Members) && IPlayer.IsValid())
							{
								if (CChar::GetRange((int)IPlayer.GetOffset() + 332, Members + 332) <= 300)
								{
									IMembers.Buff(12, 600 * ISkill.GetGrade(), 15 * ISkill.GetGrade());
									CChar::WriteInSight(IPlayer.GetOffset(), 63, "bddbb", ISkill.GetIndex(), IPlayer.GetID(), IMembers.GetID(), 0, ISkill.GetGrade());
								}
							}
						}
						CIOObject::Release(Party);
					}
				}
				else {
					ITarget.Buff(12, 600 * ISkill.GetGrade(), 15 * ISkill.GetGrade());
					CChar::WriteInSight(IPlayer.GetOffset(), 63, "bddbb", ISkill.GetIndex(), IPlayer.GetID(), ITarget.GetID(), 0, ISkill.GetGrade());
				}
			}
		}
	}

}
void __fastcall Blessing(IChar IPlayer, int pPacket, int pPos)
{
	int pSkill = IPlayer.GetSkillPointer(69);

	if (IPlayer.IsValid() && pSkill)
	{
		ISkill xSkill((void*)pSkill);
		int nSkillGrade = xSkill.GetGrade();
		int nTargetID = 0; char bType = 0; void *pTarget = 0;
		CPacket::Read((char*)pPacket, (char*)pPos, "bd", &bType, &nTargetID);

		TargetFind myTarget(bType, 0, nTargetID);
		pTarget = myTarget.getTarget();

		if (pTarget && nSkillGrade && IPlayer.IsValid())
		{
			int nMana = nSkillGrade * 10 + 400;
			IChar Target(pTarget);

			if (IPlayer.GetCurMp() < nMana) {

				return;
			}

			if (IPlayer.IsValid() && Target.IsValid())
			{
				if (!IPlayer.IsInRange(Target, 300)) {

					return;
				}

				if (IPlayer.GetID() != Target.GetID())
				{
					Target.Buff(24, (nSkillGrade * 3) + 3, 40);
					Target.RemoveBuffIcon(0, 0, 703, 34);
					CChar::AddMState(Target.GetOffset(), 0, 2147483648);
				}

				IPlayer.Buff(24, (nSkillGrade * 3) + 3, 40);
				IPlayer.RemoveBuffIcon(0, 0, 703, 34);
				CChar::AddMState(IPlayer.GetOffset(), 0, 2147483648);
				IPlayer._ShowBattleAnimation(Target, 69);
				IPlayer.DecreaseMana(nMana);
			}
		}

	}
}

void __fastcall GroupBlessing(IChar IPlayer, int pPacket, int pPos)
{
	int pSkill = IPlayer.GetSkillPointer(77);
	if (IPlayer.IsValid() && pSkill)
	{
		ISkill xSkill((void*)pSkill);
		int nSkillGrade = xSkill.GetGrade();
		int nTargetID = 0; char bType = 0; void *pTarget = 0;
		CPacket::Read((char*)pPacket, (char*)pPos, "bd", &bType, &nTargetID);

		TargetFind myTarget(bType, 0, nTargetID);
		pTarget = myTarget.getTarget();

		if (pTarget && nSkillGrade && IPlayer.IsValid())
		{
			int nMana = nSkillGrade * 10 + 400;
			IChar Target(pTarget);
			int Time = nSkillGrade + 1;
			if (IPlayer.GetCurMp() < nMana) {

				return;
			}

			if (IPlayer.IsValid() && Target.IsValid())
			{
				if (!IPlayer.IsInRange(Target, 300)) {

					return;
				}

				if (Target.IsParty())
				{
					void *Party = (void *)CParty::FindParty(Target.GetPartyID());

					if (Party)
					{
						for (int i = CParty::GetPlayerList(Party); i; i = CBaseList::Pop((void *)i))
						{
							int Members = *(DWORD*)((void*)i);
							IChar IMembers((void*)*(DWORD*)((void*)i));

							if (CChar::IsNormal(Members) && IPlayer.IsValid())
							{
								if (CChar::GetRange((int)IPlayer.GetOffset() + 332, Members + 332) <= 300)
								{
									//	IMembers.Buff(24, Time, 40);
									IMembers.Buff(BuffNames::Blessing, Time, 1);
									//	IMembers.RemoveBuffIcon(0, 0, 703, 34);
									CChar::AddMState(IMembers.GetOffset(), 0, 2147483648);
								}
							}
						}
						CIOObject::Release(Party);
					}
				}
				else {
					IPlayer.SystemMessage("The target is not in a current party group.", TEXTCOLOR_RED);

					return;
				}
				IPlayer._ShowBattleAnimation(Target, 69);
				IPlayer.DecreaseMana(nMana);
			}
		}

	}
}
void __fastcall Fireball(IChar IPlayer, int pPacket, int pPos)
{
	int pSkill = IPlayer.GetSkillPointer(73);

	if (IPlayer.IsValid() && pSkill)
	{
		ISkill xSkill((void*)pSkill);
		int nSkillGrade = xSkill.GetGrade();
		int nTargetID = 0; char bType = 0; void *pTarget = 0;
		CPacket::Read((char*)pPacket, (char*)pPos, "bd", &bType, &nTargetID);
		int nMana = (int)(((((nSkillGrade - 1) + 30) * nSkillGrade) + 300) * 0.79);

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

				int nDmg = (IPlayer.GetMagic() * MFBMul) + (xSkill.GetGrade() * CTools::Rate(MFBMin, MFBMax));

				if (Target.GetType() == 0)
					nDmg = (nDmg * MFBReduce) / 100;

				IPlayer.OktayDamageSingle(Target, nDmg, 73);
				IPlayer.SetDirection(Target);
				IPlayer.DecreaseMana(nMana);
			}
		}

	}
}
void __fastcall ContinueFlameInjection(IChar IPlayer)
{
	if (IPlayer.IsValid())
	{
		int nSkillGrade = IPlayer.GetProperty(PlayerProperty::ContinueSkillPlayerSkillGrade);

		if (nSkillGrade && IPlayer.GetProperty(PlayerProperty::ContinueSkillPlayerSkillCount))
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

			int Around = IPlayer.GetObjectListAround(4);

			while (Around)
			{
				IChar Object((void*)CBaseList::Offset((void*)Around));

				if (Object.IsValid() && IPlayer.IsValid() && (*(int(__thiscall **)(int, int, DWORD))(*(DWORD *)IPlayer.GetOffset() + 176))((int)IPlayer.GetOffset(), (int)Object.GetOffset(), 0))
				{
					int nDmg = (IPlayer.GetMagic() * MFIMul) + (nSkillGrade * CTools::Rate(MFIMin, MFIMax));

					if (Object.GetType() == 0)
						nDmg = (nDmg * MFIReduce) / 100;

					IPlayer.OktayDamageArea(Object, nDmg, 65);
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

void __fastcall FlameInjection(IChar IPlayer, int pPacket, int pPos)
{
	int pSkill = IPlayer.GetSkillPointer(65);

	if (IPlayer.IsValid() && pSkill)
	{
		ISkill xSkill((void*)pSkill);
		int nSkillGrade = xSkill.GetGrade();
		int nTargetID = 0; char bType = 0; void *pTarget = 0;
		CPacket::Read((char*)pPacket, (char*)pPos, "bd", &bType, &nTargetID);
		int nMana = IPlayer.GetLevel() * 4 + 120;

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
				IPlayer.SetProperty(PlayerProperty::ContinueSkillPlayerSkillID, 65);
				IPlayer.SetProperty(PlayerProperty::ContinueSkillPlayerSkillGrade, xSkill.GetGrade());
				IPlayer.SetProperty(PlayerProperty::ContinueSkillPlayerSkillCount, 6);
				IPlayer.SetProperty(PlayerProperty::ContinueSkillPlayerSkillDelay, 0);
				IPlayer._ShowBattleAnimation(IPlayer, 65);
			}
		}

	}
}
void __fastcall IceArrow(IChar IPlayer, int pPacket, int pPos)
{
	int pSkill = IPlayer.GetSkillPointer(74);
	__int64 GState = 536870912, State = 64, StateEx = 65, CancelState = 1;

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

		if (pTarget && nSkillGrade && IPlayer.IsValid())
		{
			IChar Target(pTarget);

			if (pTarget == IPlayer.GetOffset()) {

				return;
			}

			if (IPlayer.IsValid() && Target.IsValid())
			{
				if (!IPlayer.IsInRange(Target, 300)) {

					return;
				}


				if (IPlayer.GetBuffValue(BuffNames::CheckIceArrow) < GetTickCount()) {
					int TimeCheck = 0;
					if (CheckCooldownConfig.count(174)) {
						CheckConfigCooldown cdConfig = CheckCooldownConfig.find(174)->second;
						TimeCheck = cdConfig.CooldownConfig + cdConfig.DelayConfig;
					}

					IPlayer.UpdateBuff(BuffNames::CheckIceArrow, BuffNames::BuffTime, TimeCheck ? GetTickCount() + TimeCheck : GetTickCount() + 70200);
				}

				if (IPlayer.IsValid() && IPlayer.IsBuff(294))
				{
					IPlayer.CancelBuff(294);
					IPlayer.Buff(293, 18, 0);
					IPlayer.Buff(295, 18, 0);
					IPlayer.SendGStateExIceArrow(GState * 8);
					IPlayer.SendGStateExIceArrow(State << 32);
				}
				else if (IPlayer.IsValid() && IPlayer.IsBuff(293))
				{
					IPlayer.CancelBuff(293);
					IPlayer.Buff(292, 18, 0);
					IPlayer.Buff(295, 18, 0);
					IPlayer.SendGStateExIceArrow(GState * 4);
					IPlayer.SendGStateExIceArrow(State << 32);
				}
				else if (IPlayer.IsValid() && IPlayer.IsBuff(292))
				{
					IPlayer.CancelBuff(292);
					IPlayer.Buff(291, 18, 0);
					IPlayer.Buff(295, 18, 0);
					IPlayer.SendGStateExIceArrow(GState * 2);
					IPlayer.SendGStateExIceArrow(State << 32);
				}
				else if (IPlayer.IsValid() && IPlayer.IsBuff(291))
				{
					IPlayer.CancelBuff(291);
					IPlayer.Buff(290, 18, 0);
					IPlayer.Buff(295, 18, 0);
					IPlayer.SendGStateExIceArrow(GState);
					IPlayer.SendGStateExIceArrow(State << 32);
				}
				else if (IPlayer.IsValid() && IPlayer.IsBuff(290))
				{
					IPlayer.CancelBuff(290);
					IPlayer.CancelBuff(295);
				}
				else {

					return;
				}

				int nDmg = (IPlayer.GetMagic() * MIAMul) + (xSkill.GetGrade() * CTools::Rate(MIAMin, MIAMax));

				if (Target.GetType() == 0)
					nDmg = (nDmg * MIAReduce) / 100;

				IPlayer.OktayDamageSingle(Target, nDmg, 74);
				IPlayer.SetDirection(Target);
			}
		}

	}
}
void __fastcall ContinueIcicle(IChar IPlayer)
{
	if (IPlayer.IsValid())
	{
		if (IPlayer.GetProperty(PlayerProperty::ContinueSkillPlayerSkillCount))
		{
			int Count = IPlayer.GetProperty(PlayerProperty::ContinueSkillPlayerSkillCount);
			IPlayer.SetProperty(PlayerProperty::ContinueSkillPlayerSkillCount, Count - 1);

			if (IPlayer.IsMoved(IPlayer.GetProperty(PlayerProperty::ContinueSkillPlayerX), IPlayer.GetProperty(PlayerProperty::ContinueSkillPlayerY)))
			{
				ResetContinueSkill(IPlayer);
				return;
			}

			if (!IPlayer.IsValid())
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
					int nDmg = (IPlayer.GetMagic() * MIcicleMul) + (IPlayer.GetProperty(PlayerProperty::ContinueSkillPlayerSkillGrade) * CTools::Rate(MIcicleMin, MIcicleMax));

					if (Object.GetType() == 0)
						nDmg = (nDmg * MIcicleReduce) / 100;

					IPlayer.OktayDamageArea(Object, nDmg, 66);
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

void __fastcall Icicle(IChar IPlayer)
{
	int pSkill = IPlayer.GetSkillPointer(66);

	if (IPlayer.IsValid() && pSkill)
	{
		int nMana = IPlayer.GetLevel() * 4 + 120;

		if (IPlayer.GetCurMp() < nMana)
			return;

		IPlayer.DecreaseMana(nMana);
		ISkill xSkill((void*)pSkill);

		if (!IPlayer.GetProperty(PlayerProperty::ContinueSkillPlayerSkillID))
			IPlayer.SetContinueSkill();
		IPlayer.SetProperty(PlayerProperty::ContinueSkillPlayerX, IPlayer.GetX());
		IPlayer.SetProperty(PlayerProperty::ContinueSkillPlayerY, IPlayer.GetY());
		IPlayer.SetProperty(PlayerProperty::ContinueSkillPlayerSkillID, 66);
		IPlayer.SetProperty(PlayerProperty::ContinueSkillPlayerSkillGrade, xSkill.GetGrade());
		IPlayer.SetProperty(PlayerProperty::ContinueSkillPlayerSkillCount, 5);
		IPlayer.SetProperty(PlayerProperty::ContinueSkillPlayerSkillDelay, 0);
		IPlayer._ShowBattleAnimation(IPlayer, 66);
	}
}
void __fastcall ContinueThunderbolt(IChar IPlayer)
{
	if (IPlayer.IsValid())
	{
		void *pTarget = (void*)IPlayer.GetProperty(PlayerProperty::ContinueSkillPlayerTarget);
		IChar Target(pTarget);

		if (!Target.IsValid())
		{
			ResetContinueSkill(IPlayer);
			return;
		}

		if (IPlayer.GetProperty(PlayerProperty::ContinueSkillPlayerSkillCount))
		{
			int Count = IPlayer.GetProperty(PlayerProperty::ContinueSkillPlayerSkillCount);
			IPlayer.SetProperty(PlayerProperty::ContinueSkillPlayerSkillCount, Count - 1);

			if (!IPlayer.IsInRange(Target, 30))
			{
				ResetContinueSkill(IPlayer);
				return;
			}

			if (!IPlayer.IsValid() || !Target.IsValid())
			{
				ResetContinueSkill(IPlayer);
				return;
			}

			int nDmg = (IPlayer.GetMagic() * MTBMul) + (IPlayer.GetProperty(PlayerProperty::ContinueSkillPlayerSkillGrade) * CTools::Rate(MTBMin, MTBMax));

			if (Target.GetType() == 0)
				nDmg = nDmg * MTBReduce / 100;

			IPlayer.OktayDamageSingle(Target, nDmg, 75);
			IPlayer.SetDirection(Target);

			if (IPlayer.IsOnline())
				IPlayer.SetProperty(PlayerProperty::ContinueSkillPlayerSkillDelay, GetTickCount() + 200);

			if (IPlayer.IsOnline() && IPlayer.GetProperty(PlayerProperty::ContinueSkillPlayerSkillCount) == 0)
				ResetContinueSkill(IPlayer);

			return;
		}
	}

	ResetContinueSkill(IPlayer);
	return;
}

void __fastcall Thunderbolt(IChar IPlayer, int pPacket, int pPos)
{
	int pSkill = IPlayer.GetSkillPointer(75);

	if (IPlayer.IsValid() && pSkill)
	{
		ISkill xSkill((void*)pSkill);
		int nTargetID = 0; char bType = 0; void* pTarget = 0;
		CPacket::Read((char*)pPacket, (char*)pPos, "bd", &bType, &nTargetID);
		int nMana = (int)(((((xSkill.GetGrade() - 1) + 45) * xSkill.GetGrade()) + 280) * 0.75);

		TargetFind myTarget(bType, 0, nTargetID);
		pTarget = myTarget.getTarget();

		if (bType >= 2)
			return;

		if (pTarget && xSkill.GetGrade() && IPlayer.IsValid())
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
				IPlayer.DecreaseMana(nMana);


				if (!IPlayer.GetProperty(PlayerProperty::ContinueSkillPlayerSkillID))
					IPlayer.SetContinueSkill();

				IPlayer.SetProperty(PlayerProperty::ContinueSkillPlayerSkillID, 75);
				IPlayer.SetProperty(PlayerProperty::ContinueSkillPlayerTarget, (int)Target.GetOffset());
				IPlayer.SetProperty(PlayerProperty::ContinueSkillPlayerSkillGrade, xSkill.GetGrade());
				IPlayer.SetProperty(PlayerProperty::ContinueSkillPlayerSkillCount, 6);
				IPlayer.SetProperty(PlayerProperty::ContinueSkillPlayerSkillDelay, 0);
			}
		}

	}
}
void __fastcall TherapeuticTouch(IChar IPlayer, int pPacket, int pPos)
{
	int pSkill = IPlayer.GetSkillPointer(72);

	if (IPlayer.IsValid() && pSkill)
	{
		ISkill xSkill((void*)pSkill);
		int nTargetID = 0; char bType = 0; void *pTarget = 0;
		CPacket::Read((char*)pPacket, (char*)pPos, "bd", &bType, &nTargetID);
		int nMana = (int)(((((xSkill.GetGrade() - 1) + 50) * xSkill.GetGrade()) + 100) * 1.98);

		TargetFind myTarget(bType, 0, nTargetID);
		pTarget = myTarget.getTarget();

		if (bType >= 1)
			return;

		if (IPlayer.GetCurMp() < nMana) {
			if (pTarget)

				return;
		}

		if (pTarget && IPlayer.IsValid())
		{
			IChar Target(pTarget);

			if (!IPlayer.IsInRange(Target, 300)) {

				return;
			}

			if (IPlayer.IsValid() && Target.IsValid())
			{
				Target.Buff(45, 12, xSkill.GetGrade() * 120);
				Target.RemoveBuffIcon(0, 0, 803, 59);
				IPlayer._ShowBattleAnimation(Target, 72);
				IPlayer.DecreaseMana(nMana);
			}
		}

	}
}
void __fastcall Bombing(IChar IPlayer)
{
	int pSkill = IPlayer.GetSkillPointer(93);

	if (IPlayer.IsValid() && pSkill)
	{
		ISkill xSkill((void*)pSkill);
		int nSkillGrade = xSkill.GetGrade();

		if (IPlayer.IsValid() && nSkillGrade)
		{
			int nMana = 180 + (1.25 * (nSkillGrade * (IPlayer.GetLevel() + nSkillGrade)));

			if (IPlayer.GetCurMp() < nMana)
				return;

			int Around = IPlayer.GetObjectListAround(3);

			while (Around)
			{
				IChar Object((void*)CBaseList::Offset((void*)Around));

				if (Object.IsValid() && IPlayer.IsValid() && (*(int(__thiscall **)(int, int, DWORD))(*(DWORD *)IPlayer.GetOffset() + 176))((int)IPlayer.GetOffset(), (int)Object.GetOffset(), 0))
				{
					int nDmg = (IPlayer.GetMagic() * NBOMMul) + (nSkillGrade * CTools::Rate(NBOMMin, NBOMMax));

					if (Object.GetType() == 0)
						nDmg = (nDmg * NBOMReduce) / 100;

					IPlayer.OktayDamageArea(Object, nDmg, 93);
				}

				Around = CBaseList::Pop((void*)Around);
			}

			IPlayer.DecreaseMana(nMana);
			IPlayer._ShowBattleAnimation(IPlayer, 93);
		}
	}
}
void __fastcall StormActivateShiny(IChar IPlayer, IChar Target)
{
	if (Target.IsValid() && IPlayer.IsValid() && Target.IsBuff(BuffNames::ShinyTarget))
	{
		if (Target.GetBuffValue(BuffNames::ShinyDelay) >= GetTickCount())
			return;

		if (Target.GetBuffValue(BuffNames::ShinyTarget) && Target.IsBuff(307))
		{
			IChar Caster((void*)Target.GetBuffValue(BuffNames::ShinyTarget));

			Target.UpdateBuff(BuffNames::ShinyDelay, BuffNames::BuffTime, GetTickCount() + 500);

			if (IPlayer.IsValid() && Caster.IsValid() && Target.IsValid())
			{
				if (!IPlayer.IsInRange(Target, 300))
					return;

				if (!Caster.IsInRange(Target, 300))
					return;

				int pSkill = Caster.GetSkillPointer(67);

				if (pSkill && Target.IsValid())
				{
					bool IsDMGEdit = false;
					int SkillDmg = IPlayer.GetDamage(67, Target.GetOffset());
					int OldSkillDmg = 0;
					if (SkillDmg) {
						OldSkillDmg = IPlayer.GetProperty(PlayerProperty::SkillsEdit);
						IPlayer.SetProperty(PlayerProperty::SkillsEdit, 67);
						IsDMGEdit = true;
					}

					ISkill xSkill((void*)pSkill);
					int nSkillGrade = xSkill.GetGrade();
					int Around = Target.GetObjectListAround(3);
					while (Around)
					{
						IChar Object((void*)CBaseList::Offset((void*)Around));

						if (Object.IsValid() && Caster.IsValid() && IPlayer.IsValid() && Target.IsValid() && (*(int(__thiscall **)(int, int, DWORD))(*(DWORD *)Caster.GetOffset() + 176))((int)Caster.GetOffset(), (int)Object.GetOffset(), 0))
						{
							if (!(Target.GetType() == 0 && CChar::IsGState((int)IPlayer.Offset, 128) && !CChar::IsGState((int)Object.Offset, 128)) && !(Target.GetType() == 0 && CChar::IsGState((int)Target.Offset, 256) && Object.GetID() != Target.GetID()) && Target.GetType() == Object.GetType()) {
								int nDmg = (Caster.GetMagic() * MLAMul) + (nSkillGrade * CTools::Rate(MLAMin, MLAMax));

								if (Object.GetType() == 0)
									nDmg = nDmg * MLAReduce / 100;

								Caster.OktayDamageArea(Object, nDmg, 67);

								if (Object.GetType() == 0 && Caster.GetID() != Object.GetID() && Object.GetID() != IPlayer.GetID())
									Object.AddFxToTarget("davi_ef129", 1, 0, 0);

								if (Object.GetType() == 1)
									Object.AddFxToTarget("davi_ef129", 1, 0, 0);
							}
						}

						Around = CBaseList::Pop((void*)Around);
					}

					if (IsDMGEdit)
						IPlayer.SetProperty(PlayerProperty::SkillsEdit, OldSkillDmg);
				}
			}
			else {
				if (Target.IsValid())
				{
					Target.CancelBuff(307);
					Target.UpdateBuff(BuffNames::ShinyTarget, BuffNames::BuffTime, 0);
				}
			}
		}
	}
}

void __fastcall ActivateShiny(IChar IPlayer, int pPacket, int pPos)
{
	int nTargetID = 0; char bType = 0; void *pTarget = 0;
	CPacket::Read((char*)pPacket, (char*)pPos, "bd", &bType, &nTargetID);

	if (bType >= 2)
		return;

	TargetFind myTarget(bType, 0, nTargetID);
	pTarget = myTarget.getTarget();

	IChar Target(pTarget);

	if (pTarget && IPlayer.IsValid() && Target.IsValid() && Target.IsBuff(BuffNames::ShinyTarget))
	{
		if (Target.GetBuffValue(BuffNames::ShinyDelay) >= GetTickCount())
			return;

		if (Target.GetBuffValue(BuffNames::ShinyTarget) && Target.IsBuff(307))
		{
			IChar Caster((void*)Target.GetBuffValue(BuffNames::ShinyTarget));
			Target.UpdateBuff(BuffNames::ShinyDelay, BuffNames::BuffTime, GetTickCount() + 500);

			if (IPlayer.IsValid() && Caster.IsValid() && Target.IsValid())
			{
				if (!IPlayer.IsInRange(Target, 300))
					return;

				if (!Caster.IsInRange(Target, 300))
					return;

				int pSkill = Caster.GetSkillPointer(67);

				if (pSkill && Target.IsValid())
				{
					bool IsDMGEdit = false;
					int OldSkillDmg = 0;
					int SkillDmg = IPlayer.GetDamage(67, Target.GetOffset());
					if (SkillDmg) {
						OldSkillDmg = IPlayer.GetProperty(PlayerProperty::SkillsEdit);
						IPlayer.SetProperty(PlayerProperty::SkillsEdit, 67);
						IsDMGEdit = true;
					}

					ISkill xSkill((void*)pSkill);
					int nSkillGrade = xSkill.GetGrade();
					int Around = Target.GetObjectListAround(3);

					while (Around)
					{
						IChar Object((void*)CBaseList::Offset((void*)Around));

						if (Object.IsValid() && Caster.IsValid() && IPlayer.IsValid() && Target.IsValid() && (*(int(__thiscall **)(int, int, DWORD))(*(DWORD *)Caster.GetOffset() + 176))((int)Caster.GetOffset(), (int)Object.GetOffset(), 0))
						{
							if (!(Target.GetType() == 0 && CChar::IsGState((int)IPlayer.Offset, 128) && !CChar::IsGState((int)Object.Offset, 128)) && !(Target.GetType() == 0 && CChar::IsGState((int)Target.Offset, 256) && Object.GetID() != Target.GetID()))
							{
								if (Target.GetType() == Object.GetType()) {
									int nDmg = (Caster.GetMagic() * MLAMul) + (nSkillGrade * CTools::Rate(MLAMin, MLAMax));

									if (Object.GetType() == 0)
										nDmg = nDmg * MLAReduce / 100;

									Caster.OktayDamageArea(Object, nDmg, 67);

									if (Object.GetType() == 0 && Caster.GetID() != Object.GetID() && Object.GetID() != IPlayer.GetID())
										Object.AddFxToTarget("davi_ef129", 1, 0, 0);

									if (Object.GetType() == 1)
										Object.AddFxToTarget("davi_ef129", 1, 0, 0);
								}
							}
						}

						Around = CBaseList::Pop((void*)Around);
					}
					if (IsDMGEdit)
						IPlayer.SetProperty(PlayerProperty::SkillsEdit, OldSkillDmg);
				}
			}
			else {
				if (Target.IsValid())
				{
					Target.CancelBuff(307);
					Target.UpdateBuff(BuffNames::ShinyTarget, BuffNames::BuffTime, 0);
				}
			}
		}
	}

}

void __fastcall LightningArrow(IChar IPlayer, int pPacket, int pPos)
{
	int pSkill = IPlayer.GetSkillPointer(67);

	if (IPlayer.IsValid() && pSkill)
	{
		ISkill xSkill((void*)pSkill);
		int nTargetID = 0; char bType = 0; void *pTarget = 0;
		CPacket::Read((char*)pPacket, (char*)pPos, "bd", &bType, &nTargetID);
		int nMana = IPlayer.GetLevel() * 4 + 120;

		TargetFind myTarget(bType, 0, nTargetID);
		pTarget = myTarget.getTarget();

		if (bType >= 2)
			return;

		IChar Target(pTarget);

		if (pTarget && IPlayer.IsValid() && Target.IsValid())
		{
			if (pTarget == IPlayer.GetOffset()){

				return;
			}

			if (IPlayer.GetCurMp() < nMana){

				return;
			}

			int nDmg = (IPlayer.GetMagic() * xSkill.GetGrade()) / 3;

			if (IPlayer.IsValid() && Target.IsValid())
			{
				if (!IPlayer.IsInRange(Target, 300)){

					return;
				}

				if (strlen(AntiKsCheck) && ((std::string)AntiKsCheck == "true" || (std::string)AntiKsCheck == "True"))
				{
					if (Target.GetType() == 1 && IPlayer.GetType() == 0) {
						if (!AntiKs.count(Target.GetMobIndex()) && Target.GetMobTanker()) {
							IChar Tanker((void*)Target.GetMobTanker());

							if ((Tanker.IsParty() && Tanker.GetPartyID() != IPlayer.GetPartyID()) || (!Tanker.IsParty() && Tanker.GetPID() != IPlayer.GetPID()))
							{
								IPlayer.SystemMessage("[Anti ks] Our server doesn't tolerate ksing.", TEXTCOLOR_RED);

								return;
							}
						}
					}
				}
				if (Target.IsBuff(307))
					StormActivateShiny(IPlayer, Target);

				Target.UpdateBuff(BuffNames::ShinyTarget, BuffNames::BuffTime, (int)IPlayer.GetOffset());
				IPlayer.SetDirection(Target);
				IPlayer.OktayDamageSingle(Target, nDmg, 67);
				Target.Buff(307, 600, 0);
				IPlayer.DecreaseMana(nMana);
			}
		}

	}
}

int __cdecl CMonsterMagicCreate(int Index, int Value, int Argument, int Arg, int Player, int Damage, int Time)
{
	IChar Object((void*)Player);

	if (Object.IsOnline()) {
		switch (Index) {

			//CThunderStorm
		case 228: {
					  if (ConfigCalculations.count(143))
						  Damage += ((Damage * ConfigCalculations.find(143)->second.Rate) / 100);
					  break;
		}

			//CIceStorm
		case 229: {
					  if (ConfigCalculations.count(145))
						  Damage += ((Damage * ConfigCalculations.find(145)->second.Rate) / 100);
					  break;
		}

			//CFireRain
		case 230: {
					  if (ConfigCalculations.count(148))
						  Damage += ((Damage * ConfigCalculations.find(148)->second.Rate) / 100);
					  break;
		}

			//poison cloud
		case 231: {
					  if (ConfigCalculations.count(242))
						  Damage += ((Damage * ConfigCalculations.find(242)->second.Rate) / 100);
					  break;
		}
		}
	}

	int check = CMonsterMagic::Create(Index, Value, Argument, Arg, Player, Damage, Time);

	if (check)
	{
		if (Object.IsOnline() && Object.GetType() == 0) {
			if (Index == 228) {
				*(DWORD*)(check + 144) = 45236;
				*(DWORD*)(check + 124) = Player;
			}
		}
	}

	return check;
}

int __fastcall MagicTick(void *Monster, void *edx)
{
	IChar IMonster(Monster);
	int result = CMonster::IsRemoved(Monster);

	if (!result)
	{
		CChar::Lock(Monster);
		IChar IPlayer((void*)*(DWORD*)((int)Monster + 484));

		if (*(DWORD*)((int)Monster + 468) < GetTickCount())
		{
			CChar::Unlock(Monster);
			return CSkill::MagicTick(Monster);
		}

		if (*(DWORD*)((int)Monster + 484))
		{
			if (CBase::IsDeleted(*(DWORD*)((int)Monster + 484)))
			{
				CChar::Unlock(Monster);
				return CSkill::MagicTick(Monster);
			}

			if (IPlayer.IsValid())
			{
				if (IPlayer.GetType() == 0)
				{
					int Index = IMonster.GetMobIndex();
					if (IMonster.GetMobIndex() == 231)
					{
						int Dmg = *(DWORD*)((int)Monster + 136);
						int Around = IMonster.GetObjectListAround(4);

						while (Around)
						{
							IChar Object((void*)CBaseList::Offset((void*)Around));

							if (Object.IsValid() && IPlayer.IsValid() && IMonster.GetOffset() != Object.GetOffset() && (*(int(__thiscall **)(int, int, DWORD))(*(DWORD *)IPlayer.GetOffset() + 176))((int)IPlayer.GetOffset(), (int)Object.GetOffset(), 0))
							{
								int Check = IPlayer.GetDamage(42, Object.GetOffset());
								if (Check)
									Dmg = Check;

								if (PVPConfigCalculations.count((IPlayer.GetClass() * 1000) + 42 + (Object.GetClass() * 100)))
									Dmg += ((Dmg * PVPConfigCalculations.find((IPlayer.GetClass() * 1000) + 42 + (Object.GetClass() * 100))->second.Rate) / 100);

								if (PVPConfigCalculations.count((IPlayer.GetClass() * 1000) + 42 + 500))
									Dmg += ((Dmg * PVPConfigCalculations.find((IPlayer.GetClass() * 1000) + 42 + 500)->second.Rate) / 100);

								if (Object.GetType() == 0)
									IPlayer.OktayDamageStorm(Object, Dmg);
								else
									IPlayer.OktayDamageStorm(Object, Dmg * 3);
							}

							Around = CBaseList::Pop((void*)Around);
						}
					}
					else {
						IPlayer.UpdateBuff(BuffNames::MageMICheck, BuffNames::BuffTime, 43);

						int Dmg = *(DWORD*)((int)Monster + 136);
						int Around = IMonster.GetObjectListAround(4);
						while (Around)
						{
							IChar Object((void*)CBaseList::Offset((void*)Around));

							if (Object.IsValid() && IPlayer.IsValid() && IMonster.GetOffset() != Object.GetOffset() && (*(int(__thiscall **)(int, int, DWORD))(*(DWORD *)IPlayer.GetOffset() + 176))((int)IPlayer.GetOffset(), (int)Object.GetOffset(), 0)) {
								int SkillID = 0;
								switch (Index) {
								case 228: SkillID = 43;	break;
								case 229: SkillID = 45; break;
								case 230: SkillID = 48; break;
								}

								if (SkillID) {
									int Check = IPlayer.GetDamage(SkillID, Object.GetOffset());
									if (Check)
										Dmg = Check;

									if (PVPConfigCalculations.count((IPlayer.GetClass() * 1000) + SkillID + (Object.GetClass() * 100)))
										Dmg += ((Dmg * PVPConfigCalculations.find((IPlayer.GetClass() * 1000) + SkillID + (Object.GetClass() * 100))->second.Rate) / 100);

									if (PVPConfigCalculations.count((IPlayer.GetClass() * 1000) + SkillID + 500))
										Dmg += ((Dmg * PVPConfigCalculations.find((IPlayer.GetClass() * 1000) + SkillID + 500)->second.Rate) / 100);
								}
								IPlayer.OktayDamageStorm(Object, Dmg);

								if (SkillID == 45) {
									int Skill = IPlayer.GetSkillPointer(45);
									if (Skill && *(DWORD *)((int)IPlayer.GetOffset() + 972)) {
										if ((*(int(__thiscall **)(int, int, int))(*(DWORD *)Skill + 40))(Skill, (int)IPlayer.GetOffset(), (int)Object.GetOffset())){
											int Buff = CBuff::CreateBuff(0, *(DWORD *)((int)IPlayer.GetOffset() + 972) + 2, -20 * *(DWORD *)((int)IPlayer.GetOffset() + 972), Skill);
											if (Buff)
												(*(void(__thiscall **)(int, int))(*(DWORD *)(int)Object.GetOffset() + 180))((int)Object.GetOffset(), Buff);
										}
									}
								}
							}
							Around = CBaseList::Pop((void*)Around);
						}
					}

					if (IMonster.GetMobIndex() == 228 && *(DWORD*)((int)IMonster.GetOffset() + 144) == 45236)
					{
						IChar IPlayer((void*)*(DWORD*)((int)IMonster.GetOffset() + 124));

						if (IPlayer.IsValid())
						{
							int Around = IMonster.GetObjectListAround(3);
							while (Around)
							{
								IChar Object((void*)CBaseList::Offset((void*)Around));

								if (Object.IsValid() && IPlayer.IsValid() && IPlayer.GetOffset() != Object.GetOffset() && IMonster.GetOffset() != Object.GetOffset() && (*(int(__thiscall **)(int, int, DWORD))(*(DWORD *)IPlayer.GetOffset() + 176))((int)IPlayer.GetOffset(), (int)Object.GetOffset(), 0))
								{
									if (Object.IsBuff(307))
										StormActivateShiny(IPlayer, Object);
								}

								Around = CBaseList::Pop((void*)Around);
							}
						}
					}
				}
				else {
					if (IPlayer.GetType() == 1)
					{
						int Around = IPlayer.GetObjectListAround(4);

						while (Around)
						{
							IChar Object((void*)CBaseList::Offset((void*)Around));

							if (IPlayer.IsValid() && IPlayer.GetOffset() != Object.GetOffset() && Object.GetType() == 0)
								IPlayer.OktayDamageStorm(Object, CTools::Rate(750, 1000));

							Around = CBaseList::Pop((void*)Around);
						}
					}
				}
			}
		}

		result = CChar::Unlock(Monster);
	}

	return result;
}
void __fastcall RevivalSkill(void *Player, void *edx, int Argument, int Target)
{
	CPlayer::RevivalSkill(Player, Argument, Target);
	IChar IPlayer(Player);

	if (IPlayer.IsOnline())
	{
		if (IPlayer.IsBuff(4))
		{
			IPlayer.Buff(24, 6, 40);
			IPlayer.RemoveBuffIcon(0, 0, 703, 34);
			CChar::AddMState(IPlayer.GetOffset(), 0, 2147483648);
			IPlayer.SetBuffIcon(6000, 0, 1793, 201);

			if (Protect32::Active == true && IPlayer.GetGID() == IPlayer.GetPID())
			{
				if (IPlayer.GetGID() == Protect32::GuildFirst)
					IPlayer.CancelBuff(352);

				if (IPlayer.GetGID() == Protect32::GuildSecond)
					IPlayer.CancelBuff(352);
			}
		}
	}
}

void __fastcall RevivalItem(void *Player, void *edx, int Argument)
{
	CPlayer::RevivalItem(Player, Argument);
	IChar IPlayer(Player);

	if (IPlayer.IsOnline())
	{
		IPlayer.Buff(24, 6, 40);
		IPlayer.RemoveBuffIcon(0, 0, 703, 34);
		CChar::AddMState(IPlayer.GetOffset(), 0, 2147483648);
		IPlayer.SetBuffIcon(6000, 0, 1793, 201);
	}
}
void __fastcall Incapacitation(IChar IPlayer)
{
	int pSkill = IPlayer.GetSkillPointer(91);

	if (pSkill && IPlayer.IsValid())
	{
		ISkill xSkill((void*)pSkill);
		int nSkillGrade = xSkill.GetGrade();
		int Mana = (1.85 * (200 + (nSkillGrade * (20 + (nSkillGrade - 1)))));

		if (IPlayer.GetCurMp() < Mana)
			return;
		else
			IPlayer.DecreaseMana(Mana);

		if (IPlayer.IsValid() && nSkillGrade)
		{
			IPlayer._ShowBattleAnimation(IPlayer, 91);
			int Around = IPlayer.GetObjectListAround(3);

			while (Around)
			{
				IChar Object((void*)CBaseList::Offset((void*)Around));

				if (Object.IsValid() && IPlayer.IsValid() && (*(int(__thiscall **)(int, int, DWORD))(*(DWORD *)IPlayer.GetOffset() + 176))((int)IPlayer.GetOffset(), (int)Object.GetOffset(), 0))
				{
					if (!Object.IsBuff(395) && Object.GetDef() >= 140)
					{
						Object.Buff(395, 8 + (xSkill.GetGrade() * 2), 0);
						Object.Buff(391 + xSkill.GetGrade(), 15 + (xSkill.GetGrade() * 2), 0);
						Object.RemoveDef(80 + (xSkill.GetGrade() * 20));

						if (Object.GetType() == 0)
							Object.SetBuffIcon(8000 + (2000 * xSkill.GetGrade()), 0, 4242, 950);
					}
				}

				Around = CBaseList::Pop((void*)Around);
			}
		}
	}
}
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

		int TargetAOE = 0;
		if (SDAOE && SDPVPAOE)
			TargetAOE = 3;
		else if (SDPVPAOE)
			TargetAOE = 2;
		else if (SDAOE)
			TargetAOE = 1;

		int GetWisdom = CChar::GetWis((int)IPlayer.GetOffset());

		if (SDRange && (TargetAOE == 3 || (TargetAOE == 2 && ITarget.GetType() == 0) || (TargetAOE == 1 && ITarget.GetType() == 1)) && (IPlayer.GetSpecialty() == 43 || SDLOWAOE)) {
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
void __fastcall ReleasingTheEnergy(IChar IPlayer)
{
	if (IPlayer.IsBuff(391))
		return;

	int pSkill = IPlayer.GetSkillPointer(92);

	if (IPlayer.IsOnline() && pSkill)
	{
		ISkill xSkill((void*)pSkill);
		int Mana = (15 + (xSkill.GetGrade() * 5));

		if (IPlayer.GetCurMp() < Mana)
			return;

		if (IPlayer.IsValid() && !IPlayer.IsBuff(391))
		{
			IPlayer.DecreaseMana(Mana);
			IPlayer.Buff(390, 10 * xSkill.GetGrade(), 0);
			IPlayer.Buff(391, 3600, 0);
			IPlayer._ShowBattleAnimation(IPlayer, 92);
			IPlayer.SetBuffIcon(10000 * xSkill.GetGrade(), 0, 4244, 952);
			IPlayer.IncreaseMaxHp(500 * xSkill.GetGrade());
			IPlayer.IncreaseHp(500 * xSkill.GetGrade());
			IPlayer.AddMaxAttack(100 * xSkill.GetGrade());
			IPlayer.AddMinAttack(100 * xSkill.GetGrade());
		}
	}
}

void __fastcall Punishment(IChar IPlayer, int pPacket, int pPos)
{
	int pSkill = IPlayer.GetSkillPointer(90);

	if (IPlayer.IsValid() && pSkill)
	{
		ISkill xSkill((void*)pSkill);
		int nSkillGrade = xSkill.GetGrade();
		int nTargetID = 0; char bType = 0; void *pTarget = 0;
		CPacket::Read((char*)pPacket, (char*)pPos, "bd", &bType, &nTargetID);
		int nMana = (300 - (20 * (nSkillGrade - 1)));

		TargetFind myTarget(bType, 0, nTargetID);
		pTarget = myTarget.getTarget();

		if (bType >= 2)
			return;

		if (pTarget && nSkillGrade && IPlayer.IsValid())
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

				int nDmg = (IPlayer.GetMagic() * NMPMul) + (nSkillGrade * CTools::Rate(NMPMin, NMPMax));

				if (Target.GetType() == 0)
					nDmg = (nDmg * NMPReduce) / 100;

				IPlayer.SetDirection(Target);
				IPlayer.OktayDamageSingle(Target, nDmg, 90);
				IPlayer.DecreaseMana(nMana);
			}
		}

	}
}