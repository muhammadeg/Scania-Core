int __fastcall UpdateExp(int PlayerEgg ,void *edx, int Player, int Check)
{
	IChar IPlayer((void*)Player);

	if (*(DWORD *)(PlayerEgg + 92) >= 100)
		return 0;
	/*
	static bool hasIncreasedMovingSpeed = false;

	if (!hasIncreasedMovingSpeed && *(DWORD*)(PlayerEgg + 92) <= 100)
	{
		IPlayer.IncreaseMovingSpeed(400);
		IPlayer.SystemMessage("Moving speed has increased by 400", TEXTCOLOR_GREEN);
		hasIncreasedMovingSpeed = true; 
	}
//	Egg speed increase
	*/
	int ExpKill = EggExpKill;
	int ExpTime = EggExpTime;

	if (EggEvent::Active) {
		ExpKill += (ExpKill * EggPercentage / 100);
		ExpTime += (ExpTime * EggPercentage / 100);
	}

	// Egg Stone of Exp
	if (IPlayer.IsBuff(3829)) {
		ExpKill += (ExpKill * 10000 / 100);
		ExpTime += (ExpTime * 10000 / 100);
	}

	for (std::map<int, int>::iterator it = GoldenEggBuffs.begin(); it != GoldenEggBuffs.end(); ++it) {
		int buffID = it->first;
		int buffValue = it->second;
		if (IPlayer.IsBuff(buffID)) {
			ExpKill += (ExpKill * buffValue) / 100;
		}
	}

	if (Check)
	{
		if (*(DWORD *)(PlayerEgg + 100) == 179)
		{

			if (IPlayer.IsBuff(119) && IPlayer.IsBuff(120))
				*(DWORD *)(PlayerEgg + 96) += (ExpTime + ((ExpTime * 4) / 10)) - 10;
			else if (IPlayer.IsBuff(120))
				*(DWORD *)(PlayerEgg + 96) += (ExpTime + (ExpTime / 10)) - 10;
			else if (IPlayer.IsBuff(119))
				*(DWORD *)(PlayerEgg + 96) += (ExpTime + ((ExpTime * 3) / 10)) - 10;


			else
				*(DWORD *)(PlayerEgg + 96) += ExpTime - 10;

			if (IPlayer.IsBuff(330) && ExpTime > 100)
				*(DWORD *)(PlayerEgg + 96) += (ExpTime * 3) / 100;

			if (IPlayer.GetBuffValue(2124))
				*(DWORD *)(PlayerEgg + 96) += (ExpKill *IPlayer.GetBuffValue(2124)) / 100;
		}
	} else {
		int Remove = 1;

		if (IPlayer.GetLevel() > 20)
			Remove = ((IPlayer.GetLevel() - 11) / 10) + 1;

		if (IPlayer.IsBuff(119) && IPlayer.IsBuff(120))
			*(DWORD *)(PlayerEgg + 96) += (ExpKill + ((ExpKill *4) / 10)) - Remove;
		else if (IPlayer.IsBuff(120))
			*(DWORD *)(PlayerEgg + 96) += (ExpKill + (ExpKill / 10)) - Remove;
		else if (IPlayer.IsBuff(119))
			*(DWORD *)(PlayerEgg + 96) += (ExpKill + ((ExpKill *3) / 10)) - Remove;
		else
			*(DWORD *)(PlayerEgg + 96) += ExpKill - Remove;

		if (IPlayer.IsBuff(330) && ExpKill > 100)
			*(DWORD *)(PlayerEgg + 96) += (ExpKill * 3) / 100;

		if (IPlayer.GetBuffValue(2124))
			*(DWORD *)(PlayerEgg + 96) += (ExpKill *IPlayer.GetBuffValue(2124)) / 100;
	}

	return CItemTransform::UpdateExp(PlayerEgg,Player,Check);
}