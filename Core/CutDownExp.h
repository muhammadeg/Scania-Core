int __fastcall CutdownExp(int Player, void* edx, signed int expLoss)
{
	IChar IPlayer((void*)Player);

	if (IPlayer.IsOnline())
	{
		if (IPlayer.GetMap() == LawlessMap)
			return 0;

		if (IPlayer.IsBuff(160) || IPlayer.IsBuff(161))
			return 0;

		if (IPlayer.GetProperty(PlayerProperty::CWPlayer))
			return 0;

		if (IPlayer.IsBuff(BuffNames::PTVsPTBlue) || IPlayer.IsBuff(BuffNames::PTVsPTRed))
			return 0;

		if (SinEvent::Active && IPlayer.GetMapX() == SEMapX && IPlayer.GetMapY() == SEMapY)
			return 0;

		if (IPlayer.IsBuff(162) || IPlayer.IsBuff(163))
			return 0;

		if (IPlayer.IsBuff(166))
			return 0;

		if (IPlayer.IsBuff(170) || IPlayer.IsBuff(171))
			return 0;

		if (IPlayer.IsBuff(BuffNames::LMS))
			return 0;

		if (IPlayer.IsBuff(373) || IPlayer.IsBuff(374))
			return 0;

		if (IPlayer.IsBuff(902) || IPlayer.IsBuff(903))
			return 0;

		return CPlayer::CutdownExp(Player, expLoss);;
	} else {
		return 0;
	}
}