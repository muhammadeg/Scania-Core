int __fastcall SaveAllProperty(int Player, void *edx, int Value)
{
	int result = 0;
	IChar IPlayer((void*)Player);

	if (IPlayer.IsOnline()) {
		int Rate = CTools::Rate(1, 100);
		if (Rate <= 45) {
			int SoulPocket = IPlayer.GetBuffValue(BuffNames::SoulPocketIID);
			if (SoulPocket)
				CDBSocket::Write(90, "dd", IPlayer.GetBuffValue(BuffNames::SoulPocketAmount), SoulPocket);

			if (IPlayer.isInTrainingMap()) {
				int Time = IPlayer.GetBuffValue(BuffNames::TrainingTime);
				if (Time)
					CDBSocket::Write(95, "ddddddd", 1, IPlayer.GetPID(), BuffNames::TrainingTime, Time, 0, 0, (int)time(0) + BuffNames::BuffTime);
			}
			int diff = BuffNames::MonsterQuestEnd - BuffNames::MonsterQuestBegin;

			for (auto x = MonsterQuests.begin(); x != MonsterQuests.end(); x++)
			{
				std::vector<MonsterDailyQuest> Quests = x->second;
				int Index = x->first;
				for (auto y = Quests.begin(); y != Quests.end(); y++) {
					if (y->MainIndex)
						Index = y->MainIndex;
					else
						Index = x->first;

					if (IPlayer.GetBuffValue((BuffNames::DailyCountBegin + y->Quest) % BuffNames::DailyCountEnd) == -1) {
						ConfigDailyQuest dQuest = DailyQuest.find(y->Quest)->second;

						if (IPlayer.IsParty() && dQuest.Party == 0)
							continue;

						if (!IPlayer.IsParty() && dQuest.Party == 1)
							continue;

						int eachAmount = IPlayer.GetBuffValue(BuffNames::MonsterQuestBegin + ((Index + (y->Quest * 100)) % diff));

						if (eachAmount > maxAmountQ) {
							IPlayer.DailyQuestUpdate(y->Quest, Index, eachAmount - maxAmountQ);
							IPlayer.UpdateBuff(BuffNames::MonsterQuestBegin + ((Index + (y->Quest * 100)) % diff), BuffNames::BuffTime, (eachAmount - maxAmountQ));
						}

						break;
					}
				}
			}
		}
	}

	if (*(DWORD*)(Player + 272) >= 32000 || *(DWORD*)(Player + 276) >= 32000)
	{
		*(DWORD*)(Player + 1440) = 0;
		
		if (*(DWORD*)(Player + 272) >= 32000  && *(DWORD*)(Player + 276) >= 32000)
			CDBSocket::Write(2,"dbbwIbbbbbbwwwwbbddddb",*(DWORD*)(Player + 452),*(DWORD*)(Player + 60),*(DWORD*)(Player + 464),*(DWORD*)(Player + 468),*(DWORD*)(Player + 472),*(DWORD*)(Player + 476),*(DWORD*)(Player + 536),*(DWORD*)(Player + 64),*(DWORD*)(Player + 68),*(DWORD*)(Player + 72),*(DWORD*)(Player + 76),*(DWORD*)(Player + 80),32000,32000,*(DWORD*)(Player + 544),*(DWORD*)(Player + 548),*(DWORD*)(Player + 552),*(DWORD*)(Player + 316),*(DWORD*)(Player + 332),*(DWORD*)(Player + 336),*(DWORD*)(Player + 340),*(DWORD*)(Player + 580),Value);
		else if (*(DWORD*)(Player + 272) >= 32000)
			CDBSocket::Write(2,"dbbwIbbbbbbwwwwbbddddb",*(DWORD*)(Player + 452),*(DWORD*)(Player + 60),*(DWORD*)(Player + 464),*(DWORD*)(Player + 468),*(DWORD*)(Player + 472),*(DWORD*)(Player + 476),*(DWORD*)(Player + 536),*(DWORD*)(Player + 64),*(DWORD*)(Player + 68),*(DWORD*)(Player + 72),*(DWORD*)(Player + 76),*(DWORD*)(Player + 80),32000,*(DWORD*)(Player + 276),*(DWORD*)(Player + 544),*(DWORD*)(Player + 548),*(DWORD*)(Player + 552),*(DWORD*)(Player + 316),*(DWORD*)(Player + 332),*(DWORD*)(Player + 336),*(DWORD*)(Player + 340),*(DWORD*)(Player + 580),Value);
		else
			CDBSocket::Write(2, "dbbwIbbbbbbwwwwbbddddb", *(DWORD*)(Player + 452), *(DWORD*)(Player + 60), *(DWORD*)(Player + 464), *(DWORD*)(Player + 468), *(DWORD*)(Player + 472), *(DWORD*)(Player + 476), *(DWORD*)(Player + 536), *(DWORD*)(Player + 64), *(DWORD*)(Player + 68), *(DWORD*)(Player + 72), *(DWORD*)(Player + 76), *(DWORD*)(Player + 80), *(DWORD*)(Player + 272), 32000, *(DWORD*)(Player + 544), *(DWORD*)(Player + 548), *(DWORD*)(Player + 552), *(DWORD*)(Player + 316), *(DWORD*)(Player + 332), *(DWORD*)(Player + 336), *(DWORD*)(Player + 340), *(DWORD*)(Player + 580), Value);

		CIOCriticalSection::Enter((struct _RTL_CRITICAL_SECTION*)(Player + 1020));

		if (!Value && *(DWORD*)(Player + 1108))
			CItemTransform::SaveInfo(*(DWORD*)(Player + 1108), 0);

		int Check = *(DWORD*)(Player + 1344);
		*(DWORD*)(Player + 1344) = 0;
		result = CIOCriticalSection::Leave((void*)((char*)Player + 1020));

		if (Check)
			result = CPlayer::MLMAccumFee(Player, Check);
	} else {
		result = CPlayer::SaveAllProperty(Player,Value);
	}

	return result;
}