int __fastcall CanAttack(void *Player, void *edx, int Target, int Value)
{
	IChar IPlayer(Player);
	IChar ITarget((void*)Target);

	if (IPlayer.GetChannel() != ITarget.GetChannel())
		return 0;

	if (IPlayer.IsOnline() && ITarget.IsOnline())
	{
		if (ITarget.GetType() == 1 && *(DWORD *)(Target + 144) == 54123)
			return 0;

		if (GuildRaid::Active && Target == (int)GuildRaid::Boss && IPlayer.GetGID() != GuildRaid::GID)
			return 0;

		if (IPlayer.GetType() == 0) {

			if (IPlayer.IsValid() && ITarget.IsValid() && ITarget.IsBuff(327))
				return 0;

			if (IPlayer.IsValid() && ITarget.IsValid() && ITarget.IsBuff(329))
				return 0;

			if (ITarget.GetType() == 0) {
				if (IPlayer.IsValid() && ITarget.IsValid() && IPlayer.IsBuff(BuffNames::LMS) && ITarget.IsBuff(BuffNames::LMS))
					return 1;

				if (TriangularBattle::Active) {
					int TB = IPlayer.GetBuffValue(BuffNames::TriangularType);
					int TB1 = ITarget.GetBuffValue(BuffNames::TriangularType);
					if (TB && TB1 && TB != TB1)
						return 1;
				}

				if (IPlayer.GetMap() == SVMap && ITarget.GetMap() == SVMap) {
					if (SVParticipantsBlue.count(IPlayer.GetPID()) && SVParticipantsBlue.count(ITarget.GetPID()))
						return 0;

					if (SVParticipantsRed.count(IPlayer.GetPID()) && SVParticipantsRed.count(ITarget.GetPID()))
						return 0;

					return 1;
				}

				if (IPlayer.GetMap() == LawlessMap && ITarget.GetMap() == LawlessMap) {
					if (IPlayer.IsParty() && IPlayer.GetPartyID() == ITarget.GetPartyID())
						return 0;
					
					if (IPlayer.GetOffset() == ITarget.GetOffset())
						return 0;

					return 1;
				}

				if (*(DWORD *)((int)Player + 1516) == (int)Target && *(DWORD *)((int)Target + 1516) == (int)Player && *(DWORD *)((int)Player + 1512) == *(DWORD *)((int)Target + 1512)) {
					int C1 = *(DWORD*)((int)Player + 1520);
					int C2 = *(DWORD*)((int)Target + 1520);

					int C = max(C1, C2);
					if (C < 4u)
						return 0;
				}

				if (IPlayer.IsValid() && ITarget.IsValid() && IPlayer.IsBuff(BuffNames::PTVsPTBlue) && ITarget.IsBuff(BuffNames::PTVsPTRed))
					return 1;

				if (IPlayer.IsValid() && ITarget.IsValid() && IPlayer.IsBuff(BuffNames::PTVsPTRed) && ITarget.IsBuff(BuffNames::PTVsPTBlue))
					return 1;

				if (IPlayer.IsValid() && ITarget.IsValid() && IPlayer.IsBuff(160) && ITarget.IsBuff(161))
					return 1;

				if (IPlayer.IsValid() && ITarget.IsValid() && IPlayer.IsBuff(161) && ITarget.IsBuff(160))
					return 1;

				if (IPlayer.IsValid() && ITarget.IsValid() && IPlayer.IsBuff(180) && ITarget.IsBuff(179))
					return 1;

				if (IPlayer.IsValid() && ITarget.IsValid() && IPlayer.IsBuff(179) && ITarget.IsBuff(180))
					return 1;

				if (IPlayer.IsValid() && ITarget.IsValid() && IPlayer.IsBuff(162) && ITarget.IsBuff(163))
					return 1;

				if (IPlayer.IsValid() && ITarget.IsValid() && IPlayer.IsBuff(163) && ITarget.IsBuff(162))
					return 1;

				if (IPlayer.IsValid() && ITarget.IsValid() && IPlayer.IsBuff(170) && ITarget.IsBuff(171))
					return 1;

				if (IPlayer.IsValid() && ITarget.IsValid() && IPlayer.IsBuff(171) && ITarget.IsBuff(170))
					return 1;

				if (IPlayer.IsValid() && ITarget.IsValid() && IPlayer.IsBuff(373) && ITarget.IsBuff(374))
					return 1;

				if (IPlayer.IsValid() && ITarget.IsValid() && IPlayer.IsBuff(902) && ITarget.IsBuff(903))
					return 1;

				if (IPlayer.IsValid() && ITarget.IsValid() && IPlayer.IsBuff(903) && ITarget.IsBuff(902))
					return 1;

				if (IPlayer.IsValid() && ITarget.IsValid() && IPlayer.IsBuff(374) && ITarget.IsBuff(373))
					return 1;
			}
		}
	}
	return CPlayer::CanAttack(Player, Target, Value);
}

int __fastcall CheckHit(void* Attacker, void *edx, void* Target, int Value)
{
	IChar IAttacker(Attacker);
	IChar ITarget(Target);

	if (IAttacker.GetChannel() != ITarget.GetChannel())
		return 0;

	if (IAttacker.IsOnline() && ITarget.IsOnline() && IAttacker.GetType() == 0 && ITarget.GetType() == 0 && *(DWORD *)((int)Attacker + 1516) == (int)Target && *(DWORD *)((int)Target + 1516) == (int)Attacker && *(DWORD *)((int)Attacker + 1512) == *(DWORD *)((int)Target + 1512)) {
		int C1 = *(DWORD*)((int)Attacker + 1520);
		int C2 = *(DWORD*)((int)Target + 1520);

		int C = max(C1, C2);
		if (C < 4u)
			return 0;
	}

	if (IAttacker.GetType() == 0)
		*(DWORD *)((int)IAttacker.GetOffset() + 1464) = GetTickCount();

	if (ITarget.GetType() == 0)
		*(DWORD *)((int)ITarget.GetOffset() + 1464) = GetTickCount();

	return CChar::CheckHit(Attacker, Target, Value);
}