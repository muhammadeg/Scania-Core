void UpdateLawless(int Player, int newPoint) {
	IChar IPlayer((void*)Player);

	int EXP = IPlayer.GetBuffValue(BuffNames::LawlessEXP);
	int Points = IPlayer.GetBuffValue(BuffNames::LawlessPoints);

	int newPts = Points + newPoint;

	IPlayer.UpdateBuff(BuffNames::LawlessPoints, BuffNames::BuffTime, newPts);

	int EXPType = 0;
	if (newPts >= LawlessEXP.back())
		EXPType = LawlessEXP.size();
	else {
		for (int i = 0; i < LawlessEXP.size(); i++) {
			if (newPts < LawlessEXP[i]) {
				EXPType = i;
				break;
			}
		}
	}

	if (EXP != EXPType) {
		IPlayer.UpdateBuff(BuffNames::LawlessEXP, BuffNames::BuffTime, EXPType);
		if (EXP)
			IPlayer.RemoveFxBone("expgrade" + Int2String(EXP));
		IPlayer.AddFxToBone("expgrade" + Int2String(EXPType), 0);
	}

	IPlayer.Scenario3_3Score(2, Points, newPts);
}

int __fastcall LawlessParty(int Player, void* edx, int Argument) {
	IChar IPlayer((void*)Player);
	int result = CChar::IsGState(Player, Argument);

	if (result && IPlayer.GetMap() == LawlessMap)
		result = 0;

	return result;
}

int __fastcall PartyJoin(int Party, void* edx, int Inviter, int Joiner) {
	int Check = CParty::Join(Party, Inviter, Joiner);

	IChar IPlayer((void*)Joiner);

	if (IPlayer.GetMap() == LawlessMap)
		IPlayer.Teleport(IPlayer.GetMap(), IPlayer.GetX(), IPlayer.GetY());

	return Check;
}

void ClearPartyBuff(int Party, int BuffID, int Player) {
	for (int i = CParty::_GetPlayerList((void*)Party); i; i = CBaseList::Pop((void *)i))
	{
		IChar IMembers((void*)*(DWORD*)((void*)i));
		if ((int)IMembers.GetOffset() != Player)
			IMembers.CancelBuff(BuffID);
	}
}

void LeavePartyCheck(int Party, int Leaver) {	
	IChar IPlayer((void*)Leaver);

	CIOCriticalSection::Enter((struct _RTL_CRITICAL_SECTION *)(Party + 48));

	if (IPlayer.IsOnline()) {
		int SecondCall = IPlayer.GetSecondCall();
		if (SecondCall)
			ClearPartyBuff(Party, SecondCall, Leaver);

		int EventMapsCheck = IPlayer.GetBuffValue(BuffNames::EventMapQuest);
		if (EventMapsCheck) {
			if (EventMapsOn.count(EventMapsCheck)) {
				eventMap questEvent = EventMapsQuests.find(EventMapsCheck)->second;
				if (questEvent.Type == 1 && CParty::GetSize((void*)Party) <= 2)
					EventMapsOn.erase(EventMapsCheck);
			}
		}

		if (!ShamanDisabled) {
			for (int i = 0; i < sizeof(ShamanBuffs) / sizeof(int); i++) {
				int BuffID = ShamanBuffs[i];
				int Value = IPlayer.GetBuffValue(BuffID);
				if (Value) {
					if (Value == Leaver)
						ClearPartyBuff(Party, BuffID, Leaver);
					else
						IPlayer.CancelBuff(BuffID);
				}
			}
		}
	}

	CIOCriticalSection::Leave((struct _RTL_CRITICAL_SECTION *)(Party + 48));
}

void __fastcall PartyLeave(int Party, void* edx, int Leaver) {
	IChar IPlayer((void*)Leaver);

	LeavePartyCheck(Party,Leaver);

	CParty::Leave(Party, Leaver);

	if (IPlayer.GetMap() == LawlessMap)
		IPlayer.Teleport(IPlayer.GetMap(), IPlayer.GetX(), IPlayer.GetY());
}

void __fastcall PartyExile(int Party, void* edx, int kicker, int Leaver) {
	IChar IPlayer((void*)Leaver);

	LeavePartyCheck(Party, Leaver);
	
	CParty::Exile(Party, kicker, Leaver);

	if (IPlayer.GetMap() == LawlessMap)
		IPlayer.Teleport(IPlayer.GetMap(), IPlayer.GetX(), IPlayer.GetY());
}