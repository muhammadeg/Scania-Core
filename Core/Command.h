#define g_MaxUser *(DWORD*)0x4E2138

std::string getUptime() {
	time_t diff = difftime(time(NULL), uptimestart);
	const unsigned int SECS_PER_DAY = 60 * 60 * 24;
	const unsigned int SECS_PER_HR = 60 * 60;
	const unsigned int SECS_PER_MIN = 60;
	unsigned int days = diff / SECS_PER_DAY;
	diff = diff % SECS_PER_DAY;
	unsigned int hours = diff / SECS_PER_HR;
	diff = diff % SECS_PER_HR;
	unsigned int minutes = diff / SECS_PER_MIN;
	diff = diff % SECS_PER_MIN;
	unsigned int seconds = diff;
	std::stringstream uptime;
	uptime << "Server Uptime : " << days << " Days " << hours << " Hours " << minutes << " Minutes " << seconds << " Seconds";

	return uptime.str();
}
std::string getSysUpTime() {
	const unsigned int SECS_PER_DAY = 60 * 60 * 24;
	const unsigned int SECS_PER_HR = 60 * 60;
	const unsigned int SECS_PER_MIN = 60;
	unsigned long long uptime_seconds = GetTickCount64() / 1000;
	unsigned int days = uptime_seconds / SECS_PER_DAY;
	uptime_seconds = uptime_seconds % SECS_PER_DAY;
	unsigned int hours = uptime_seconds / SECS_PER_HR;
	uptime_seconds = uptime_seconds % SECS_PER_HR;
	unsigned int minutes = uptime_seconds / SECS_PER_MIN;
	uptime_seconds = uptime_seconds % SECS_PER_MIN;
	unsigned int seconds = uptime_seconds;
	std::stringstream uptime;
	uptime << "System Uptime : " << days << " Days " << hours << " Hours " << minutes << " Minutes " << seconds << " Seconds";
	return uptime.str();
}


void __fastcall ChatCommand(int Player, void *edx, const char *command)
{
	if (!strlen(command))
		return;

	std::string cmd = (std::string)command;
	IChar IPlayer((void*)Player);

	if (IPlayer.IsOnline() && Restri && Restrictions.count(IPlayer.GetPID())) {
		vector<string> arr = explode(" ", cmd);
		vector<string> cmds = explode(",", Restrictions.find(IPlayer.GetPID())->second.Commands);

		for (int i = 0; i < cmds.size(); i++) {
			if (cmds[i] == arr[0]) {
				IPlayer.SystemMessage("You are not allowed to use this command.", TEXTCOLOR_RED);
				return;
			}
		}
	}

	if (IPlayer.IsOnline() && IPlayer.GetAdmin() >= 3) {
		vector<string> arr = explode(" ", cmd);
		if (!arr.empty() && CustomNotices.count(arr[0])) {
			std::string msg = "";
			for (int i = 0; i < arr.size(); i++) {
				if (i)
					msg += ((i == 1) ? "" : " ") + arr[i];
			}
			CPlayer::WriteAll(0xFE, "dds", 178, CustomNotices.find(arr[0])->second, msg.c_str());
			return;
		}
	}

	//if (IPlayer.IsOnline()) {
	//	vector<string> arr = explode(" ", cmd);
	//	if (!arr.empty() && CustomCommands.count(arr[0])) {
	//		std::string playerName = (std::string) IPlayer.GetName();
	//		std::string msg = " [" + playerName + "] ";

	//		for (int i = 0; i < arr.size(); i++) {
	//			if (i)
	//				msg += ((i == 1) ? "" : " ") + arr[i];
	//		}

	//		IPlayer.SystemMessage("Command 0", TEXTCOLOR_GREEN);

	//		for (std::map<std::string, CommandLink>::const_iterator it = CustomCommands.begin(); it != CustomCommands.end(); ++it) {
	//			const CommandLink& cmdS = it->second;

	//			if (arr[0] == cmdS.Command){
	//				IPlayer.OpenWebsite(cmdS.Link);
	//				IPlayer.SystemMessage("Command 1", TEXTCOLOR_GREEN);
	//			}
	//		}
	//		return;
	//	}

	//}

	if (IPlayer.IsOnline()) {
		vector<string> arr = explode(" ", cmd);
		if (!arr.empty() && CustomShouts.count(arr[0]) && CPlayer::FindItem(IPlayer.GetOffset(), CustomShouts.find(arr[0])->second.index, 1)) {
			std::string playerName = (std::string) IPlayer.GetName();
			std::string msg = " [" + playerName + "] ";

			for (int i = 0; i < arr.size(); i++) {
				if (i)
					msg += ((i == 1) ? "" : " ") + arr[i];
			}

			CPlayer::WriteAll(0xFF, "dsd", 218, msg.c_str(), CustomShouts.find(arr[0])->second.color);
			if (CustomShouts.find(arr[0])->second.remove != 0)
				CPlayer::RemoveItem(IPlayer.GetOffset(), 9, CustomShouts.find(arr[0])->second.index, 1);
			return;
		}
		else if (!arr.empty() && CustomShouts.count(arr[0]) && !CPlayer::FindItem(IPlayer.GetOffset(), CustomShouts.find(arr[0])->second.index, 1)) {
			IPlayer.SystemMessage("Missing special shout item", TEXTCOLOR_RED);
			return;
		}
	}

	if (IPlayer.IsOnline()) {
		vector<string> arr = explode(" ", cmd);
		if (!arr.empty() && arr[0] == "/area") {
			std::string playerName = (std::string) IPlayer.GetName();
			std::string msg = " [" + playerName + "] ";

			for (int i = 0; i < arr.size(); i++) {
				if (i)
					msg += ((i == 1) ? "" : " ") + arr[i];
			}
			int Around = IPlayer.GetObjectListAround(100);
			while (Around)
			{
				IChar Object((void*)CBaseList::Offset((void*)Around));

				if (Object.IsValid() && Object.IsOnline() && Object.GetType() == 0) {
					CPlayer::Write(Object.GetOffset(), 0xFF, "dsd", 218, msg.c_str(), TEXTCOLOR_GENERAL);

				}

				Around = CBaseList::Pop((void*)Around);
			}
			return;
		}
	}

	if (IPlayer.IsOnline() && IPlayer.GetMap() == BFMap) {
		vector<string> arr = explode(" ", cmd);
		if (!arr.empty() && arr[0] == "/t") {
			std::string playerName = (std::string) IPlayer.GetName();
			std::string msg = " [" + playerName + "] ";

			for (int i = 0; i < arr.size(); i++) {
				if (i)
					msg += ((i == 1) ? "" : " ") + arr[i];
			}
			int Around = IPlayer.GetObjectListAround(100);
			while (Around)
			{
				IChar Object((void*)CBaseList::Offset((void*)Around));

				if (Object.IsValid() && Object.IsOnline() && Object.GetType() == 0 && Object.IsBuff(160) && IPlayer.IsBuff(160))
					CPlayer::Write(Object.GetOffset(), 0xFF, "dsd", 218, msg.c_str(), TEXTCOLOR_RED);

				if (Object.IsValid() && Object.IsOnline() && Object.GetType() == 0 && Object.IsBuff(161) && IPlayer.IsBuff(161))
					CPlayer::Write(Object.GetOffset(), 0xFF, "dsd", 218, msg.c_str(), TEXTCOLOR_BLUE);


				Around = CBaseList::Pop((void*)Around);
			}
			return;
		}
	}

	if (IPlayer.IsOnline()) {
		int playerHouse = 0;
		if (IPlayer.isSlytherin())
			playerHouse = 1;
		else if (IPlayer.isHufflepuff())
			playerHouse = 2;
		else if (IPlayer.isRavenclaw())
			playerHouse = 3;
		else
			playerHouse = 4;

		vector<string> arr = explode(" ", cmd);
		if (!arr.empty() && CustomHouse.count(arr[0]) && playerHouse == CustomHouse.find(arr[0])->second.index) {
			std::string playerName = (std::string) IPlayer.GetName();
			std::string msg = " [" + playerName + "] ";

			for (int i = 0; i < arr.size(); i++) {
				if (i)
					msg += ((i == 1) ? "" : " ") + arr[i];
			}

			CIOCriticalSection::Enter((void*)0x4e2078);
			CIOCriticalSection::Enter((void*)0x4e2098);
			CLink::MoveTo((void*)0x4e200c, (int)0x4e2004);
			CIOCriticalSection::Leave((void*)0x4e2098);
			for (DWORD i = *(DWORD*)0x4E2004; i != 0x4E2004; i = *(DWORD*)i)
			{
				IChar Online((void*)(i - 428));

				int onlineHouse = 0;
				if (Online.isSlytherin())
					onlineHouse = 1;
				else if (Online.isHufflepuff())
					onlineHouse = 2;
				else if (Online.isRavenclaw())
					onlineHouse = 3;
				else
					onlineHouse = 4;

				if (Online.IsOnline() && onlineHouse == playerHouse) {
					CPlayer::Write(Online.GetOffset(), 0xFF, "dsd", 218, msg.c_str(), CustomHouse.find(arr[0])->second.color);
				}
			}
			CIOCriticalSection::Leave((void*)0x4e2078);
			return;
		}
	}

	if (IPlayer.IsOnline() && IPlayer.isInTrainingMap() && cmd.substr(0, 5) == "/duel")
		return;

	if (IPlayer.IsOnline() && IPlayer.GetMap() == TBMap && cmd.substr(0, 5) == "/duel") {
		CPlayer::Write((void*)Player, 0xFE, "db", 172, 23);
		return;
	}

	if (IPlayer.IsOnline() && cmd.substr(0, 5) == "/exit")
		return;

	if (IPlayer.IsOnline() && IPlayer.GetAdmin() >= 3 && PTCommands.count(cmd)) {
		managePartyRegistration(PTCommands.find(cmd)->second);
		return;
	}

	if (IPlayer.IsOnline() && IPlayer.IsPVPValid() && !IPlayer.isDead() && !IPlayer.isAssassin() && sscanf(command, "/arena %d", &portArena) == 1) {
		if (portArena > 0 && portArena < 9)
			IPlayer.Teleport(0, PartyPortBack[0][portArena], PartyPortBack[1][portArena]);
		else
			IPlayer.SystemMessage("Arenas must be between 1 and 8.", TEXTCOLOR_RED);

		return;
	}

	if (commandDebug == 1) {
		std::string Datoe = "./Debugger/Command/CMD_" + Time::GetDay() + "_" + Time::GetMonth() + "_" + Time::GetYear() + ".txt";
		std::fstream CHLOG;
		CHLOG.open(Datoe, std::fstream::in | std::fstream::out | std::fstream::app);
		CHLOG << Time::GetTime() << " " << IPlayer.GetName() << ": " << cmd << std::endl;
		CHLOG.close();
	}

	if (IPlayer.IsOnline() && IPlayer.GetAdmin() >= 3 && cmd.substr(0, 7) == "/fights") {
		StartWorldCup();
		return;
	}

	if (IPlayer.IsOnline() && IPlayer.GetAdmin() >= 3 && cmd.substr(0, 13) == "/resetsummon") {
		for (std::map<int, MSummonedConfig>::iterator iter = SummonedQuest.begin(); iter != SummonedQuest.end(); ++iter)
		{
			int k = iter->first;
			MSummonedConfig mConfig = iter->second;
			mConfig.Limit = 0;
			SummonedQuest.replaceInsert(k, mConfig);
		}
		IPlayer.SystemMessage("Summon Quests Limit have been reseted.", TEXTCOLOR_GREEN);
		return;
	}

	if (IPlayer.IsOnline() && cmd.substr(0, 7) == "/wcleft") {
		IPlayer.SystemMessage("Players left for World Cup to start: " + Int2String(32 - CupRegistration.size()), TEXTCOLOR_YELLOW);
		return;
	}

	if (IPlayer.IsOnline() && cmd.substr(0, 9) == "/wcwinner") {
		IPlayer.SystemMessage("Current World Cup Winner: " + WCWinner, TEXTCOLOR_INFOMSG);
		return;
	}

	if (IPlayer.IsOnline() && cmd.substr(0, 5) == "/dice") {
		int diceValue = CTools::Rate(1, 6);
		CChar::WriteInSight((void*)Player, 206, "dd", IPlayer.GetID(), diceValue);
		return;
	}

	if (IPlayer.IsOnline() && IPlayer.GetAdmin() >= 3 && cmd.substr(0, 6) == "/lotto") {
		if (XLottery.size() > 0) {
			int Winner = XLottery.randomSelect();
			TargetFind myTarget(0, 1, Winner);
			int player = (int)myTarget.getTarget();

			while (!player && XLottery.size() > 0) {
				XLottery.erase(Winner);
				Winner = XLottery.randomSelect();
				TargetFind myTarget(0, 1, Winner);
				player = (int)myTarget.getTarget();
			}
			if (player) {
				IChar Target((void*)player);
				if (Target.IsOnline())
				{
					Target.systemReward(LottoReward);

					Target.BoxMsg("*************Congratulations***************\n\nYou have been selected as our Lotto's Winner!");

					std::string msg = (std::string) Target.GetName() + " is our new Lotto Winner, Congratulations!";
					CPlayer::WriteAll(0xFF, "ds", 234, msg.c_str());
					CPlayer::WriteAll(15, "s", msg.c_str());
				}
			}
			else {
				CPlayer::WriteAll(0xFF, "ds", 234, "Lotto Selection has ended. There is no winner.");
			}
			RewardLimit.clear();
			XLottery.clear();
		}
	}


	if (IPlayer.IsOnline() && IPlayer.GetAdmin() >= 8 && cmd.substr(0, 10) == "/mobamount") {
		IPlayer.SystemMessage("Mob Amount : " + Int2String(*CMonster::Amount), TEXTCOLOR_GENERAL);
		return;
	}

	if (IPlayer.IsOnline() && IPlayer.GetAdmin() >= 8 && cmd.substr(0, 10) == "/channelon") {
		if (ChannelActivated < 9){
			int MobAmount = *CMonster::Amount;

			if (MobAmount >= 30000)
				IPlayer.SystemMessage("WARNING: The monster amount is high, lags may occur.", TEXTCOLOR_YELLOW);

			ChannelActivated++;
			std::string msg = "Channel number " + Int2String(ChannelActivated) + " is now open.";
			ToNoticeWebhook(msg.c_str());
			CPlayer::WriteAll(0xFF, "dsd", 247, msg.c_str(), 2);
			IPlayer.SystemMessage("Channel " + Int2String(ChannelActivated) + " successfully enabled", TEXTCOLOR_GREEN);
		}
		else
			IPlayer.SystemMessage("Channel " + Int2String(ChannelActivated) + " is already active.", TEXTCOLOR_YELLOW);
		return;
	}

	if (IPlayer.IsOnline() && IPlayer.GetAdmin() >= 8 && cmd.substr(0, 11) == "/channeloff") {
		if (ChannelActivated) {
			int channeltostop = ChannelActivated;
			ChannelActivated--;
			std::string msg = "Channel number " + Int2String(channeltostop) + " is now closed.";
			ToNoticeWebhook(msg.c_str());
			CPlayer::WriteAll(0xFF, "dsd", 247, msg.c_str(), 2);
			IPlayer.SystemMessage("Channel " + Int2String(channeltostop) + " successfully closed.", TEXTCOLOR_GREEN);
		}
		return;
	}

	int playerChannel = 0;
	if (IPlayer.IsOnline() && sscanf(command, "/channel %d", &playerChannel) == 1) {
		if (!ChannelActivated) {
			IPlayer.SystemMessage("Channel system is currently disabled.", TEXTCOLOR_RED);
			return;
		}

		if (playerChannel && ChannelActivated < playerChannel) {
			IPlayer.SystemMessage("This channel number is currently closed.", TEXTCOLOR_RED);
			return;
		}

		int MapX = IPlayer.GetX() >> 13;
		int MapY = IPlayer.GetY() >> 13;

		if (!ChannelMaps.count((MapX * 1000) + MapY)) {
			IPlayer.SystemMessage("Channel system is not enabled in this map.", TEXTCOLOR_RED);
			return;
		}

		if (UnChannel.count((MapX * 1000) + MapY)) {
			IPlayer.SystemMessage("Channel system is disabled in this area.", TEXTCOLOR_RED);
			return;
		}

		if (IPlayer.isAssassin()) {
			IPlayer.SystemMessage("You can not move to channel system as assassin.", TEXTCOLOR_RED);
			return;
		}
		if (IPlayer.isDead()) {
			IPlayer.SystemMessage("You must use rebirth before switching channels.", TEXTCOLOR_RED);
			return;
		}

		if (playerChannel >= 0 && playerChannel <= 9) {
			if ((GetTickCount() - *(DWORD *)((int)Player + 1464) < 10000)) {
				IPlayer.SystemMessage("After 10 sec from the last battle, you may switch channels.", TEXTCOLOR_RED);
				return;
			}

			IPlayer.SetChannelSystem(playerChannel);
		}
		else
			IPlayer.SystemMessage("Channel number can only be between 0 and 9!", TEXTCOLOR_RED);
		return;
	}

	if (IPlayer.IsOnline() && IPlayer.GetAdmin() >= 8 && cmd.substr(0, 10) == "/selection") {
		if (!DuelTournament::Active) {
			AllFights.clear();
			selectParticipants(1);
			CPlayer::WriteAll(0xFF, "ds", 234, "Duel tournament selection has been made.");
		}
		return;
	}

	if (IPlayer.IsOnline() && IPlayer.GetAdmin() >= 8 && cmd.substr(0, 6) == "/pmoff") {
		if (DisablePM.count((std::string)IPlayer.GetName()))
			IPlayer.SystemMessage("Your Private Messages are already turned off.", TEXTCOLOR_YELLOW);
		else {
			DisablePM.insert((std::string)IPlayer.GetName());
			IPlayer.SystemMessage("Your Private Messages are now turned off.", TEXTCOLOR_GREEN);
		}
		return;
	}

	if (IPlayer.IsOnline() && IPlayer.GetAdmin() >= 8 && cmd.substr(0, 5) == "/pmon") {
		if (DisablePM.count((std::string)IPlayer.GetName())) {
			IPlayer.SystemMessage("Your Private Messages are now turned on.", TEXTCOLOR_GREEN);
			DisablePM.erase((std::string)IPlayer.GetName());
		}
		else
			IPlayer.SystemMessage("Your Private Messages are already turned on.", TEXTCOLOR_YELLOW);

		return;
	}

	if (IPlayer.IsOnline() && !IPlayer.isDead() && !IPlayer.isAssassin() && cmd.substr(0, 8) == "/skinoff") {
		IPlayer.setSkinView(IPlayer.IsHide() ? -2 : 1);
		IPlayer.SystemMessage("Skins appearance has been turned off.", TEXTCOLOR_RED);

		if (IPlayer.GetBuffValue(BuffNames::SuitsUsing))
			CPlayer::Write(IPlayer.GetOffset(), 6, "ddw", IPlayer.GetID(), 0, IPlayer.GetBuffValue(BuffNames::SuitsUsing));
		int custWeap = IPlayer.GetBuffValue(BuffNames::custWeap);
		if (custWeap) {
			CPlayer::Write(IPlayer.GetOffset(), 6, "ddw", IPlayer.GetID(), 0, custWeap);
			if (CostWeaponsEffects.count(custWeap)) {
				if (IPlayer.GetClass() == 3)
					CPlayer::Write(IPlayer.GetOffset(), 0xFE, "dds", 176, IPlayer.GetID(), IPlayer.CostEffect(CostWeaponsEffects.find(custWeap)->second).c_str());
				CPlayer::Write(IPlayer.GetOffset(), 0xFE, "dds", 176, IPlayer.GetID(), IPlayer.CostEffect(CostWeaponsEffects.find(custWeap)->second).c_str());
			}
		}

		IPlayer.Teleport(IPlayer.GetMap(), IPlayer.GetX(), IPlayer.GetY(), IPlayer.GetZ());
		return;
	}

	//if (IPlayer.IsOnline() && !IPlayer.isDead() && !IPlayer.isAssassin() && cmd.substr(0, 6) == "/peton") {

	//	IPlayer.SystemMessage("Pet appearance has been turned on.", TEXTCOLOR_GREEN);
	//	IPlayer.CancelBuff(1626);
	//	IPlayer.Teleport(IPlayer.GetMap(), IPlayer.GetX(), IPlayer.GetY(), IPlayer.GetZ());

	//	return;
	//}

	//if (IPlayer.IsOnline() && !IPlayer.isDead() && !IPlayer.isAssassin() && cmd.substr(0, 7) == "/petoff") {

	//	IPlayer.SystemMessage("Pet appearance has been turned off.", TEXTCOLOR_GREEN);
	//	IPlayer.Buff(1626, BuffNames::BuffTime, 1);
	//	IPlayer.Teleport(IPlayer.GetMap(), IPlayer.GetX(), IPlayer.GetY(), IPlayer.GetZ());

	//	return;
	//}

	if (IPlayer.IsOnline() && !IPlayer.isDead() && !IPlayer.isAssassin() && cmd.substr(0, 7) == "/skinon") {
		IPlayer.setSkinView(IPlayer.IsHide() ? -1 : 0);
		IPlayer.SystemMessage("Skins appearance has been turned on.", TEXTCOLOR_GREEN);

		if (IPlayer.GetBuffValue(BuffNames::SuitsUsing))
			CPlayer::Write(IPlayer.GetOffset(), 5, "ddw", IPlayer.GetID(), 0, IPlayer.GetBuffValue(BuffNames::SuitsUsing));

		int custWeap = IPlayer.GetBuffValue(BuffNames::custWeap);
		if (custWeap) {
			CPlayer::Write(IPlayer.GetOffset(), 5, "ddw", IPlayer.GetID(), 0, custWeap);

			if (CostWeaponsEffects.count(custWeap) && IPlayer.GetBuffValue(BuffNames::WeaponWear))
				CPlayer::Write(IPlayer.GetOffset(), 0xFE, "ddsd", 177, IPlayer.GetID(), IPlayer.CostEffect(CostWeaponsEffects.find(custWeap)->second).c_str(), 1);
		}

		IPlayer.Teleport(IPlayer.GetMap(), IPlayer.GetX(), IPlayer.GetY(), IPlayer.GetZ());
		return;
	}

	if (IPlayer.IsOnline() && cmd.substr(0, 7) == "/geonon") {
		IPlayer.SystemMessage("Geon message has been turned on.", TEXTCOLOR_GREEN);
		CPlayer::Write((void*)Player, 0xFE, "dd", 184, 0);
		return;
	}

	if (IPlayer.IsOnline() && cmd.substr(0, 8) == "/geonoff") {
		IPlayer.SystemMessage("Geon message has been turned off.", TEXTCOLOR_GREEN);
		CPlayer::Write((void*)Player, 0xFE, "dd", 184, 1);
		return;
	}

	if (IPlayer.IsOnline() && cmd.substr(0, 9) == "/absorbon") {
		IPlayer.SystemMessage("Absorbing messages have been turned on.", TEXTCOLOR_GREEN);
		CPlayer::Write((void*)Player, 0xFE, "dd", 183, 0);
		return;
	}

	if (IPlayer.IsOnline() && cmd.substr(0, 10) == "/absorboff") {
		IPlayer.SystemMessage("Absorb messages have been turned off.", TEXTCOLOR_GREEN);
		CPlayer::Write((void*)Player, 0xFE, "dd", 183, 1);
		return;
	}

	if (IPlayer.IsOnline() && cmd.substr(0, 7) == "/maskon") {
		int Price = Maskon * 1000;
		int FindItem = CPlayer::FindItem(IPlayer.GetOffset(), 31, Price);

		if (FindItem && !IPlayer.IsBuff(104)){
			IPlayer.Buff(104, 1800, 0);
			CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 31, Price);
		}
		else if (IPlayer.IsBuff(104))
			IPlayer.SystemMessage("Assassin mode is already enabled.", TEXTCOLOR_RED);
		else
			IPlayer.SystemMessage(Int2String(Maskon) + "K Zamogeons is needed to use this feature.", TEXTCOLOR_RED);


		return;
	}

	if (IPlayer.IsOnline() && cmd.substr(0, 8) == "/maskoff") {

		int lastHitTime = (GetTickCount() - *(DWORD *)((int)Player + 1464));
		if (lastHitTime < 60000) {
			IPlayer.SystemMessage("After " + Int2String((60000 - lastHitTime) / 1000) + " sec from the last battle, you may wear off mask.", TEXTCOLOR_RED);
			return;
		}

		int Price = Maskoff * 1000;
		int FindItem = CPlayer::FindItem(IPlayer.GetOffset(), 31, Price);

		if (FindItem && IPlayer.IsBuff(104)){
			IPlayer.CancelBuff(104);
			CPlayer::RemoveItem(IPlayer.GetOffset(), 9, 31, Price);
		}
		else if (!IPlayer.IsBuff(104))
			IPlayer.SystemMessage("Assassin mode is not enabled.", TEXTCOLOR_RED);
		else
			IPlayer.SystemMessage(Int2String(Maskoff) + "K Zamogeons is needed to use this feature.", TEXTCOLOR_RED);


		return;
	}

	int dmg = 0;
	if (IPlayer.IsOnline() && IPlayer.GetAdmin() >= 8 && sscanf(command, "/kill %d", &killmobs) == 1) {
		int Around = IPlayer.GetObjectListAround(killmobs);
		int Count = 0;
		while (Around)
		{
			IChar Object((void*)CBaseList::Offset((void*)Around));

			if (Object.IsValid() && (*(int(__thiscall **)(int, int, DWORD))(*(DWORD *)IPlayer.GetOffset() + 176))((int)IPlayer.GetOffset(), (int)Object.GetOffset(), 0)) {
				Count++;

				*(DWORD *)((int)Object.GetOffset() + 272) = 1;
				int DMG = *(DWORD *)((int)Object.GetOffset() + 272) * 10000;
				int NormalDamage = 0, DamageArgument = 0, EBDamage = 0, Check = 0, TypeKind = 0, GetType = 0;
				//IPlayer.OktayDamageArea(Object, DMG, 40);

				(*(int(__thiscall**)(LONG, void*, unsigned int, int*, int*, int*, DWORD))(*(DWORD*)Object.GetOffset() + 72))((int)Object.GetOffset(), IPlayer.GetOffset(), DMG, &NormalDamage, &DamageArgument, &EBDamage, 0);
			}

			Around = CBaseList::Pop((void*)Around);
		}
		if (Count)
			IPlayer.SystemMessage("You have killed " + Int2String(Count) + " monsters.", TEXTCOLOR_GREEN);
		else
			IPlayer.SystemMessage("No monsters were found, try a bigger range.", TEXTCOLOR_YELLOW);
		return;
	}

	if (IPlayer.IsOnline() && IPlayer.GetAdmin() >= 8 && sscanf(command, "/maskup %d", &maskups) == 1) {
		int Around = IPlayer.GetObjectListAround(maskups);
		while (Around)
		{
			IChar Object((void*)CBaseList::Offset((void*)Around));

			if (Object.IsValid() && Object.GetType() == 0 && Object.GetOffset() != IPlayer.GetOffset() && !Object.IsBuff(104)) {
				Object.Buff(104, 1800, 0);
				Object.SystemMessage("You have entered Sinful Sunday Mode.", TEXTCOLOR_ORANGE);
			}

			Around = CBaseList::Pop((void*)Around);
		}
		return;
	}

	if (IPlayer.IsOnline() && IPlayer.GetAdmin() >= 8 && sscanf(command, "/addsnow %d", &Snow) == 1) {
		if (Snow >= 1 && Snow <= 3) {
			int kSnow = Snow;
			if (Snow == 3)
				kSnow = 4;
			CPlayer::WriteAll(68, "bIdd", 74, 16 * kSnow, 0, 1000, 0);
		}
		else if (Snow == 4){
			CPlayer::WriteAll(68, "bI", 75, 16, 0);
			CPlayer::WriteAll(68, "bI", 75, 32, 0);
			CPlayer::WriteAll(68, "bI", 75, 64, 0);
		}
		return;
	}

	int Hide = 0;
	if (IPlayer.IsOnline() && IPlayer.GetAdmin() >= 3 && sscanf(command, "/hide %d", &Hide) == 1) {
		if (Hide) {
			(*(void(__thiscall **)(int, signed int, DWORD))(*(DWORD *)Player + 104))(Player, 0x80000, 0);
			int curSkinViewDisabled = IPlayer.isSkinView();
			IPlayer.setSkinView(curSkinViewDisabled != 0 ? -2 : -1);
			IPlayer.SystemMessage("You are now hidden.", TEXTCOLOR_GENERAL);
		}
		else {
			(*(void(__thiscall **)(int, signed int, DWORD))(*(DWORD *)Player + 124))(Player, 0x80000, 0);
			int curSkinViewDisabled = IPlayer.isSkinView();
			IPlayer.setSkinView((curSkinViewDisabled == -2) ? 1 : 0);
			IPlayer.SystemMessage("You are now visible.", TEXTCOLOR_GENERAL);
		}

		IPlayer.Teleport(IPlayer.GetMap(), IPlayer.GetX(), IPlayer.GetY(), IPlayer.GetZ());
		return;
	}

	if (IPlayer.IsOnline() && IPlayer.GetAdmin() >= 3 && cmd.substr(0, 5) == "/hide") {
		if (IPlayer.IsHide()) {
			(*(void(__thiscall **)(int, signed int, DWORD))(*(DWORD *)Player + 124))(Player, 0x80000, 0);
			int curSkinViewDisabled = IPlayer.isSkinView();
			IPlayer.setSkinView((curSkinViewDisabled == -2) ? 1 : 0);
			IPlayer.SystemMessage("You are now visible.", TEXTCOLOR_GENERAL);

			IPlayer.Teleport(IPlayer.GetMap(), IPlayer.GetX(), IPlayer.GetY(), IPlayer.GetZ());
		}
		return;
	}


	if (IPlayer.IsOnline() && IPlayer.GetAdmin() >= 8 && sscanf(command, "/snow %d", &Snow) == 1) {
		if (Snow >= 1 && Snow <= 3) {
			int kSnow = Snow;
			if (Snow == 3)
				kSnow = 4;
			CPlayer::WriteAll(68, "bIdd", 74, 16 * kSnow, 0, 1000, 0);
		}
		else if (Snow == 4) {
			CPlayer::WriteAll(68, "bI", 75, 16, 0);
			CPlayer::WriteAll(68, "bI", 75, 32, 0);
			CPlayer::WriteAll(68, "bI", 75, 64, 0);
		}
	}
	int k = 0, kk = 0;
	if (IPlayer.IsOnline() && IPlayer.GetAdmin() >= 8 && sscanf(command, "/tesa %d", &k) == 1) {
		CChar::WriteInSight((void*)Player, 145, "dI", IPlayer.GetID(), __int64(0x400000));
		CChar::WriteInSight((void*)Player, 0xFE, "dd", 172, k);
		IPlayer.Buff(BuffNames::TriangularType, BuffNames::BuffTime, 2);
		IPlayer.Buff(BuffNames::TriangularState, BuffNames::BuffTime, 0x400000);
		return;
	}

	if (IPlayer.IsOnline() && IPlayer.GetAdmin() >= 8 && sscanf(command, "/tesi %d", &k) == 1) {
		CChar::WriteInSight((void*)Player, 145, "dI", IPlayer.GetID(), __int64(0x4000000 + 0x800000));
		CChar::WriteInSight((void*)Player, 0xFE, "dd", 172, k);
		IPlayer.Buff(BuffNames::TriangularType, BuffNames::BuffTime, 3);
		IPlayer.Buff(BuffNames::TriangularState, BuffNames::BuffTime, 0x4000000 + 0x800000);
		return;
	}

	if (IPlayer.IsOnline() && IPlayer.GetAdmin() >= 8 && sscanf(command, "/time %d", &k) == 1) {
		//CPlayer::Write((void*)Player, 0xFE, "dbd", 171, 26, k);
		//CPlayer::Write((void*)Player, 0xFE, "dbbbb", 171, 19, 2, 1, 1);
		CPlayer::Write((void*)Player, 0xFE, "db", 172, k);
		CPlayer::Write((void*)Player, 0xFE, "dbd", 172, 11, k);
		//IPlayer.Teleport(IPlayer.GetMap(), 217224, 252850, 16553);
		IPlayer.OpenHTML(300133);
		return;
	}

	if (IPlayer.IsOnline() && IPlayer.GetAdmin() >= 8 && cmd.substr(0, 17) == "/triangularbattle")
	{
		if (!TriangularBattle::Active && !TriangularBattle::CDActive)
			StartTriangularBattle();
		else
			TriangularBattle::Time = 0;
		return;
	}

	if (IPlayer.IsOnline() && IPlayer.GetAdmin() >= 8 && cmd.substr(0, 16) == "/sufferingvalley")
	{
		if (!SufferingValley::Active)
			startSV();
		else
			SufferingValley::Time = 0;
		return;
	}

	if (IPlayer.IsOnline() && IPlayer.GetAdmin() >= 8 && cmd.substr(0, 13) == "/svselection")
	{
		if (!SufferingValley::Selection)
			SVSelection();
		return;
	}

	signed __int64 exp = 0;
	if (IPlayer.IsOnline() && IPlayer.GetAdmin() >= 8 && sscanf(command, "/exp %lld", &exp) == 1) {
		CPlayer::UpdateProperty(Player, 25, 1, exp);
		return;
	}

	if (IPlayer.IsOnline() && IPlayer.GetAdmin() >= 8 && sscanf(command, "/bypass %s", &bypassName) == 1)
	{
		if (!strlen(bypassName))
			return;

		const char *PlayerName = bypassName;
		TargetFind myTarget(PlayerName);
		int player = (int)myTarget.getTarget();
		IChar Target((void*)player);

		if (Target.IsOnline()){
			if (Target.IsBuff(BuffNames::BypassAFK))
			{
				IPlayer.SystemMessage("Player already has Bypass validation.", TEXTCOLOR_RED);
				return;
			}
			Target.SaveBuff(BuffNames::BypassAFK, BuffNames::BuffTime);
			IPlayer.SystemMessage("Player Bypass successfully added.", TEXTCOLOR_GREEN);
		}
		else
			IPlayer.SystemMessage("Player is not online.", TEXTCOLOR_RED);
		return;
	}

	if (IPlayer.IsOnline() && IPlayer.GetAdmin() >= 8 && sscanf(command, "/unbypass %s", &bypassName) == 1)
	{
		if (!strlen(bypassName))
			return;

		const char *PlayerName = bypassName;
		TargetFind myTarget(PlayerName);
		int player = (int)myTarget.getTarget();
		IChar Target((void*)player);


		if (Target.IsOnline()){
			if (!Target.IsBuff(BuffNames::BypassAFK))
			{
				IPlayer.SystemMessage("Player has no Bypass validation.", TEXTCOLOR_RED);
				return;
			}

			Target.RemoveSavedBuff(BuffNames::BypassAFK);
			IPlayer.SystemMessage("Player Bypass successfully removed.", TEXTCOLOR_GREEN);
		}
		else
			IPlayer.SystemMessage("Player is not online.", TEXTCOLOR_RED);
		return;
	}

	int honor = 0;
	if (IPlayer.IsOnline() && IPlayer.GetAdmin() >= 8 && sscanf(command, "/reward %s %d", &rewardupName, &amount) == 2)
	{
		if (!strlen(rewardupName))
			return;

		const char *PlayerName = rewardupName;
		TargetFind myTarget(PlayerName);
		int player = (int)myTarget.getTarget();
		IChar Target((void*)player);

		if (Target.IsOnline())
		{
			Target.SetHonor(0, amount, 0, 0, 0, 0, 0, 0, 0, 0);
			std::string Targe = "" + Int2String(amount) + " Reward_Point has been added to [" + (std::string)Target.GetName() + "]";
			IPlayer.SystemMessage(Targe, TEXTCOLOR_INFOMSG);
		}

		return;

	}

	if (IPlayer.IsOnline() && IPlayer.GetAdmin() >= 8 && sscanf(command, "/honor %s %d", &honorupName, &amount) == 2)
	{
		if (!strlen(honorupName))
			return;

		const char *PlayerName = honorupName;
		TargetFind myTarget(PlayerName);
		int player = (int)myTarget.getTarget();
		IChar Target((void*)player);

		if (Target.IsOnline())
		{
			Target.SetHonor(amount, 0, 0, 0, 0, 0, 0, 0, 0, 0);
			std::string Targe = "" + Int2String(amount) + " Honor Point has been added to [" + (std::string)Target.GetName() + "]";
			IPlayer.SystemMessage(Targe, TEXTCOLOR_INFOMSG);
		}
		return;

	}

	int fonline = 0;
	if (IPlayer.IsOnline() && IPlayer.GetAdmin() >= 8 && sscanf(command, "/fonline %d", &fonline) == 1) {
		IPlayer.SystemMessage("Players Online : " + Int2String(fonline), TEXTCOLOR_INFOMSG);
		return;
	}

	if (IPlayer.IsOnline() && IPlayer.GetAdmin() >= 3 && cmd.substr(0, 9) == "/clearinv")
	{

		for (int i = 0; i < 100000; i++) {
			int FindItem = CPlayer::FindItem(IPlayer.GetOffset(), i, 1);
			IItem DeletedItem((void*)FindItem);
			if (FindItem && !CItem::IsState(FindItem, 1)){
				int amount = DeletedItem.GetAmount();
				//	IPlayer.RemoveItem(FindItem);
				CPlayer::RemoveItem(IPlayer.GetOffset(), 9, i, amount);
			}
		}
		IPlayer.SystemMessage("Your inventory has been cleaned.", TEXTCOLOR_GREEN);
		return;
	}

	if (IPlayer.IsOnline() && IPlayer.GetAdmin() >= 8 && sscanf(command, "/test %d", &k) == 1) {
		//int playerSpeed = IPlayer.GetSpeed();

		//	CItem::CreateDropItem(k, kk);
/*
		Interface<ITools> Tools;

		auto maxUser = g_MaxUser;

		int maxUsersII = MSocket::GetMaxConnectionsCount();
		IPlayer.SystemMessage(Int2String(maxUser), TEXTCOLOR_GREEN);

		IPlayer.SystemMessage(Int2String(maxUsersII), TEXTCOLOR_RED);
*/
		IPlayer.SystemMessage("Current Speed: " + Int2String(IPlayer.GetSpeed()), TEXTCOLOR_RED);

		CPlayer::Write(IPlayer.GetOffset(), 0xFE, "ddd", 186, IPlayer.GetID(), k);

		return;
	}


	if (IPlayer.IsOnline() && cmd.substr(0, 11) == "/leavechaos")
	{
		if (IPlayer.GetMap() == 16)
		{
			if ((GetTickCount() - *(DWORD *)((int)Player + 1464) < 10000)) {
				IPlayer.SystemMessage("After 10 sec from the last battle, you may leave chaos tower.", TEXTCOLOR_RED);
				return;
			}

			IPlayer.Teleport(25, 267378, 243168);
			return;
		}

		else
		{
			IPlayer.SystemMessage("Command can be used only in Chaos Tower", TEXTCOLOR_RED);
			return;
		}
	}
	if (IPlayer.IsOnline() && IPlayer.GetAdmin() >= 3 && sscanf(command, "/fake %d", &EFakePlayers) == 1)
	{
		EFakePlayers = (EFakePlayers >= FakePlayers.size()) ? FakePlayers.size() : EFakePlayers;

		if (EFakePlayers)
			IPlayer.SystemMessage(Int2String(EFakePlayers) + " Fake Players have appeared.", TEXTCOLOR_GREEN);
		else
			IPlayer.SystemMessage("Fake Players have been disabled.", TEXTCOLOR_RED);

		return;
	}

	if (IPlayer.IsOnline() && IPlayer.GetAdmin() >= 3 && cmd.substr(0, 8) == "/capture") {
		if (CaptureFlag::Active == false) {
			if (CaptureRegistration.size() >= 1) {
				CPlayer::WriteAll(0xFF, "dsd", 247, thisServerName + " Capture the flag has been started.", 2);
				CaptureFlag::Time = CaptureDuration;
				CaptureFlag::RedScore = 0;
				CaptureFlag::BlueScore = 0;
				CaptureFlag::LastHit = 0;
				CaptureFlag::CurrentCapturers = 0;
				CaptureFlag::PlayerID = 0;
				Summon(0, CaptureMap, CPSummonX, CPSummonY, CaptureMonster, 1, 0, 0, 0, 0);
				Summon(0, CaptureMap, CPGateBX, CPGateBY, CPGate, 1, 0, 0, 0, 0);
				Summon(0, CaptureMap, CPGateRX, CPGateRY, CPGate, 1, 0, 0, 0, 0);
				CaptureFlag::Active = true;
			}
		}
		else
			CaptureFlag::Time = 0;
		return;
	}

	if (IPlayer.IsOnline() && IPlayer.GetAdmin() >= 3 && cmd.substr(0, 5) == "/raid") {
		if (Raid::Active == false) {
			if (RaidSystem.size() > 0) {
				CPlayer::WriteAll(0xFF, "dsd", 247, thisServerName + " Raid System has been started.", 2);
				Raid::Time = 315;
				Raid::Round = 0;
				Raid::Active = true;
			}
		}
		else
			Raid::Time = 0;
		return;
	}

	if (IPlayer.IsOnline() && CPlayer::FindItem(IPlayer.GetOffset(), 9372, 1)) {
		if (IPlayer.IsPVPValid() && !IPlayer.isDead() && !IPlayer.isAssassin() && cmd.substr(0, 5) == "/fort")
		{
			IPlayer.Teleport(0, 267542, 242672);
			return;
		}

		if (IPlayer.IsPVPValid() && !IPlayer.isDead() && !IPlayer.isAssassin() && cmd.substr(0, 5) == "/naro")
		{
			IPlayer.Teleport(0, 258042, 259367);
			return;
		}

		if (cmd.substr(0, 8) == "/storage")
		{
			IPlayer.OpenHTML(175);
			return;
		}

		if (cmd.substr(0, 5) == "/vote")
		{
			std::string url = "https://inity-kal.com/vote-rewards.php";
			IPlayer.OpenWebsite(url);
			return;
		}
		if (cmd.substr(0, 7) == "/donate")
		{
			std::string url = "https://inity-kal.com/userpanel/index.php?page=donate";
			IPlayer.OpenWebsite(url);
			return;
		}
	}

	if (IPlayer.GetAdmin() >= 3) {
		if (IPlayer.IsOnline() && IPlayer.IsPVPValid() && !IPlayer.isDead() && !IPlayer.isAssassin() && cmd.substr(0, 5) == "/naro")
		{
			IPlayer.Teleport(0, 258042, 259367);
			return;
		}

		if (IPlayer.IsOnline() && IPlayer.IsPVPValid() && !IPlayer.isDead() && !IPlayer.isAssassin() && cmd.substr(0, 6) == "/cargo")
		{
			IPlayer.Teleport(0, 265073, 262622);
			return;
		}

		if (IPlayer.IsOnline() && IPlayer.IsPVPValid() && !IPlayer.isDead() && !IPlayer.isAssassin() && cmd.substr(0, 5) == "/fort")
		{
			IPlayer.Teleport(0, 267542, 242672);
			return;
		}

		if (IPlayer.IsOnline() && IPlayer.IsPVPValid() && !IPlayer.isDead() && !IPlayer.isAssassin() && cmd.substr(0, 5) == "/mine")
		{
			IPlayer.Teleport(0, 266056, 284973);
			return;
		}

		if (IPlayer.IsOnline() && IPlayer.IsPVPValid() && !IPlayer.isDead() && !IPlayer.isAssassin() && cmd.substr(0, 5) == "/bird")
		{
			IPlayer.Teleport(0, 255764, 288738);
			return;
		}

		if (IPlayer.IsOnline() && IPlayer.IsPVPValid() && !IPlayer.isDead() && !IPlayer.isAssassin() && cmd.substr(0, 4) == "/cop")
		{
			IPlayer.Teleport(0, 232922, 294650);
			return;
		}
	}

	if (IPlayer.IsOnline() && IPlayer.GetAdmin() >= 3 && cmd.substr(0, 8) == "/warinfo")
	{
		int war = CPlayer::CountWarrelationPlayer();
		std::string msg = "War Info: " + Int2String(war);
		IPlayer.SystemMessage(msg, TEXTCOLOR_GREEN);
		return;
	}

	if (IPlayer.IsOnline() && IPlayer.GetAdmin() >= 3 && sscanf(command, "/buffinfo %[a-z | A-Z | 0-9/<>|.,~*;`:!'^+%&/()=?_-£#${[]}\€]", &buffnameplayer) == 1)
	{
		if (!strlen(buffnameplayer))
			return;

		const char *PlayerName = buffnameplayer;
		TargetFind myTarget(PlayerName);
		int player = (int)myTarget.getTarget();
		IChar Target((void*)player);

		if (Target.IsOnline())
		{
			std::string Datko = "./Debugger/Buff/" + (std::string)Target.GetName() + ".txt";
			remove(Datko.c_str());
			std::fstream DGkLOG;
			DGkLOG.open(Datko, std::fstream::in | std::fstream::out | std::fstream::app);


			CriticalLock lock((struct _RTL_CRITICAL_SECTION *)(player + 364));
			for (int i = *(DWORD *)((int)player + 360); i; i = *(DWORD *)(i + 20)) {
				int BuffID = *(DWORD *)(i + 4);
				int Check = *(DWORD *)(i + 8);
				int Value = *(DWORD *)(i + 12);

				DGkLOG << "(BuffInfo (BuffID " << BuffID << ") (Time " << Check << ") (Value " << Value << " ))" << std::endl;
			}

			DGkLOG.close();

			IPlayer.SystemMessage("Buff infos successfully generated in /Buffs folder.", TEXTCOLOR_GREEN);
			return;
		}

		IPlayer.SystemMessage("Buff infos cannot be generated because player is offline.", TEXTCOLOR_RED);
		return;
	}


	if (IPlayer.IsOnline() && IPlayer.GetAdmin() >= 3 && sscanf(command, "/areainfo %[a-z | A-Z | 0-9/<>|.,~*;`:!'^+%&/()=?_-£#${[]}\€]", &nameugog) == 1)
	{
		if (!strlen(nameugog))
			return;

		const char *PlayerName = nameugog;
		TargetFind myTarget(PlayerName);
		int player = (int)myTarget.getTarget();
		IChar Target((void*)player);

		if (Target.IsOnline())
		{
			std::string Datko = "./AreaInfo/" + (std::string)Target.GetName() + ".txt";
			remove(Datko.c_str());
			std::fstream DGkLOG;
			DGkLOG.open(Datko, std::fstream::in | std::fstream::out | std::fstream::app);

			int Around = Target.GetObjectListAround(75);

			while (Around)
			{
				IChar Object((void*)CBaseList::Offset((void*)Around));

				if (Object.IsValid())
				{
					if (Object.GetType() == 0) {
						int MapX = Object.GetX() >> 13;
						int MapY = Object.GetY() >> 13;

						std::string msg = (std::string)Object.GetName() + "- " + Int2String(MapX) + "_" + Int2String(MapY) + " -  X: " + Int2String(Object.GetX()) + " Y: " + Int2String(Object.GetY()) + " Z: " + Int2String(Object.GetZ());
						std::string additionalInfos = "";
						int Color = TEXTCOLOR_SHUTDOWN;
						if (Object.GetZ() != Target.GetZ()) {
							Color = TEXTCOLOR_RED;
							if (Object.GetZ() > Target.GetZ())
								additionalInfos = "OverGround: Z Difference: " + Int2String(abs(Object.GetZ() - Target.GetZ()));
							else
								additionalInfos = "UnderGround: Z Difference: " + Int2String(abs(Object.GetZ() - Target.GetZ()));

							msg += " - " + additionalInfos;
						}

						IPlayer.SystemMessage(msg, Color);
						if (!additionalInfos.empty())
							DGkLOG << "(PlayerInfo (PID " << Object.GetPID() << ")(Name " << Object.GetName() << ")(MapFile " << MapX << "_" << MapY << ")(Map " << Object.GetMap() << ")(X " << Object.GetX() << ")(Y " << Object.GetY() << ")(Z " << Object.GetZ() << ")(Extra '" << additionalInfos << "'))" << std::endl;
						else
							DGkLOG << "(PlayerInfo (PID " << Object.GetPID() << ")(Name " << Object.GetName() << ")(MapFile " << MapX << "_" << MapY << ")(Map " << Object.GetMap() << ")(X " << Object.GetX() << ")(Y " << Object.GetY() << ")(Z " << Object.GetZ() << "))" << std::endl;
					}
				}

				Around = CBaseList::Pop((void*)Around);
			}

			DGkLOG.close();
			return;
		}

		IPlayer.SystemMessage("Targeted player is offline", TEXTCOLOR_RED);
		return;
	}

	if (IPlayer.IsOnline() && NewMystEnable && cmd.substr(0, 8) == "/mystery")
	{
		int OTP = IPlayer.IsBuff(BuffNames::MystOTP);
		int EVA = IPlayer.IsBuff(BuffNames::MystEVA);
		int HP = IPlayer.IsBuff(BuffNames::MystHP);
		int PhyAtk = IPlayer.IsBuff(BuffNames::MystPhy);
		int MagAtk = IPlayer.IsBuff(BuffNames::MystMag);
		int Def = IPlayer.IsBuff(BuffNames::MystDef);

		int OTPV = IPlayer.GetBuffValue(BuffNames::MystOTP);
		int EVAV = IPlayer.GetBuffValue(BuffNames::MystEVA);
		int HPV = IPlayer.GetBuffValue(BuffNames::MystHP);
		int PhyV = IPlayer.GetBuffValue(BuffNames::MystPhy);
		int MagV = IPlayer.GetBuffValue(BuffNames::MystMag);
		int DefV = IPlayer.GetBuffValue(BuffNames::MystDef);

		if (OTP){
			IPlayer.SystemMessage("On Target Point Mystery Grade : " + Int2String(OTPV), TEXTCOLOR_GREEN);
			return;
		}
		else if (EVA){
			IPlayer.SystemMessage("Evasion Point Mystery Grade : " + Int2String(EVAV), TEXTCOLOR_GREEN);
			return;
		}
		else if (HP){
			IPlayer.SystemMessage("Health Point Mystery Grade : " + Int2String(HPV), TEXTCOLOR_GREEN);
			return;
		}
		else if (PhyAtk){
			IPlayer.SystemMessage("Physical Attack Point Mystery Grade : " + Int2String(PhyV), TEXTCOLOR_GREEN);
			return;
		}
		else if (MagAtk){
			IPlayer.SystemMessage("Magical Attack Point Mystery Grade : " + Int2String(MagV), TEXTCOLOR_GREEN);
			return;
		}
		else if (Def){
			IPlayer.SystemMessage("Defense Point Mystery Grade : " + Int2String(DefV), TEXTCOLOR_GREEN);
			return;
		}
		else{
			IPlayer.SystemMessage("You don't have any mystery passive.", TEXTCOLOR_RED);
			return;
		}
	}

	if (IPlayer.IsOnline() && IPlayer.GetAdmin() >= 3 && cmd.substr(0, 5) == "/ugog")
	{
		int Around = IPlayer.GetObjectListAround(50);

		while (Around)
		{
			IChar Object((void*)CBaseList::Offset((void*)Around));

			if (Object.IsValid() && IPlayer.IsValid())
			{
				if (Object.GetType() == 0 && Object.GetZ() != IPlayer.GetZ())
					IPlayer.SystemMessage(Object.GetName(), TEXTCOLOR_SHUTDOWN);
			}

			Around = CBaseList::Pop((void*)Around);
		}
		return;
	}

	int pollValue = 0;

	if (IPlayer.IsOnline() && IPlayer.GetAdmin() >= 3 && sscanf(command, "/poll %d", &pollValue)) {
		if (Polls.count(pollValue))
			pollAsk = Polls.find(pollValue)->second;

		return;
	}

	if (IPlayer.IsOnline() && IPlayer.GetAdmin() >= 3 && sscanf(command, "/newname %[a-z | A-Z | 0-9/<>|.,~*;`:!'^+%&/()=?_-£#${[]}\€]", &ipname) == 1)
	{
		if (!strlen(ipname))
			return;

		const char *PlayerName = ipname;
		IPlayer.ChangeName(PlayerName);
		//ShowMySkin((void*)Player);

		return;
	}



	if (IPlayer.IsOnline() && IPlayer.GetAdmin() >= 3 && sscanf(command, "/charsip %[a-z | A-Z | 0-9/<>|.,~*;`:!'^+%&/()=?_-£#${[]}\€]", &ipname) == 1)
	{
		if (!strlen(ipname))
			return;

		const char *PlayerName = ipname;
		TargetFind myTarget(PlayerName);
		int player = (int)myTarget.getTarget();
		IChar Target((void*)player);

		int n = 0;
		CPlayer::Write((void*)Player, 0xFE, "ds", 213, "Online Players List:\n");
		CIOCriticalSection::Enter((void*)0x4e2078);
		CIOCriticalSection::Enter((void*)0x4e2098);
		CLink::MoveTo((void*)0x4e200c, (int)0x4e2004);
		CIOCriticalSection::Leave((void*)0x4e2098);
		for (DWORD i = *(DWORD*)0x4E2004; i != 0x4E2004; i = *(DWORD*)i)
		{
			n++;
			IChar Online((void*)(i - 428));
			if (Online.IsOnline() && Online.GetHWID() == Target.GetHWID()) {
				std::string name(Online.GetName());
				std::string msg = Int2String(n) + "- " + name;
				CPlayer::Write((void*)Player, 0xFE, "ds", 213, msg.c_str());
			}
		}
		CIOCriticalSection::Leave((void*)0x4e2078);
		return;
	}


	if (IPlayer.IsOnline() && IPlayer.GetAdmin() >= 3 && sscanf(command, "/ip %[a-z | A-Z | 0-9/<>|.,~*;`:!'^+%&/()=?_-£#${[]}\€]", &ipname) == 1)
	{
		if (!strlen(ipname))
			return;

		const char *PlayerName = ipname;
		TargetFind myTarget(PlayerName);
		int player = (int)myTarget.getTarget();
		IChar Target((void*)player);

		if (Target.IsOnline())
		{
			std::string PC = "";
			std::string MAC = "";
			std::string HWID = "";

			//userLock.Enter();
			if (User.count(Target.GetPID())) {
				UserInfo userInfo = User.findValue(Target.GetPID());
				PC = userInfo.PCName;
				MAC = userInfo.MAC;
				HWID = userInfo.Hardware;
			}
			//userLock.Leave();

			IPlayer.SystemMessage("IP Address: " + (string)Target.GetIP(), TEXTCOLOR_GREEN);
			if (!PC.empty())
				IPlayer.SystemMessage("Computer Name: " + PC, TEXTCOLOR_GREEN);
			if (!MAC.empty())
				IPlayer.SystemMessage("Mac Address: " + MAC, TEXTCOLOR_GREEN);
			if (!HWID.empty())
				IPlayer.SystemMessage("Hardware ID: " + HWID, TEXTCOLOR_GREEN);
		}

		return;
	}

	if (IPlayer.IsOnline() && IPlayer.GetAdmin() >= 8 && cmd.substr(0, 7) == "/shouts")
	{
		if (Shouts == 0) {
			Shouts = 1;
			IPlayer.SystemMessage("Shouts have been disabled.", TEXTCOLOR_GREEN);
		}
		else {
			Shouts = 0;
			IPlayer.SystemMessage("Shouts have been enabled.", TEXTCOLOR_GREEN);
		}
		return;
	}

	if (IPlayer.IsOnline() && IPlayer.GetAdmin() >= 3 && cmd.substr(0, 12) == "/coordinates") {
		IPlayer.SystemMessage("[Rect: " + Int2String(IPlayer.GetRectX()) + " " + Int2String(IPlayer.GetRectY()) + "]", TEXTCOLOR_GENERAL);
		IPlayer.SystemMessage("[Map: " + Int2String(IPlayer.GetX() >> 13) + " " + Int2String(IPlayer.GetY() >> 13) + "]", TEXTCOLOR_GENERAL);
	}

	if (IPlayer.IsOnline() && IPlayer.GetAdmin() >= 5 && cmd.substr(0, 6) == "/frame") {
		CPlayer::Write(IPlayer.GetOffset(), 254, "d", 217);
		return;
	}

	if (IPlayer.IsOnline() && IPlayer.GetAdmin() >= 8 && cmd.substr(0, 8) == "/lottery")
	{
		if (LotteryCheck > 0 && Lottery.size() > 0) {
			int Winner = Lottery.randomSelect();
			TargetFind myTarget(0, 1, Winner);
			int player = (int)myTarget.getTarget();

			while (!player && Lottery.size() > 0) {
				Lottery.erase(Winner);
				Winner = Lottery.randomSelect();
				TargetFind myTarget(0, 1, Winner);
				player = (int)myTarget.getTarget();
			}
			if (player) {
				IChar Target((void*)player);

				if (LotteryCheck > 2000000000)
					LotteryCheck = 2000000000;

				if (Target.IsOnline())
				{
					if (GetInventorySize((int)Target.GetOffset(), 0) < 60)
						CItem::InsertItem((int)Target.Offset, 27, LotIndex, 0, LotteryCheck, -1);
					else {
						Target.GiveReward(LotIndex, 0, LotteryCheck, 0, 0, 0, 0, 0, 0, 0, 0, "Congratulations on winning the lottery!");
					}

					Target.BoxMsg("*************Congratulations***************\n\nYou have been selected as our Lottery Winner!");

					std::string msg = (std::string)Target.GetName() + " has won the " + thisServerName + " Public Lottery, Congratulations!";
					CPlayer::WriteAll(0xFF, "ds", 234, msg.c_str());
					CPlayer::WriteAll(15, "s", msg.c_str());
				}
			}
			else {
				CPlayer::WriteAll(0xFF, "ds", 234, "Lottery Selection has ended. There is no winner.");
			}
			RewardLimit.clear();
			LotteryCheck = 0;
			Lottery.clear();
		}
	}

	if (IPlayer.IsOnline() && IPlayer.GetAdmin() >= 3 && sscanf(command, "/jail %d %[a-z | A-Z | 0-9/<>|.,~*;`:!'^+%&/()=?_-£#${[]}\€]", &jailtime, &jailname) == 2)
	{
		const char *PlayerName = jailname;
		TargetFind myTarget(PlayerName);
		int player = (int)myTarget.getTarget();
		IChar Target((void*)player);

		if (Target.IsOnline() && jailtime)
		{
			if (Target.IsBuff(BuffNames::Jail)) {
				Target.CancelBuff(BuffNames::Jail);
				Target.CancelBuff(BuffNames::Mute);
			}

			Target.Buff(BuffNames::Jail, jailtime, 0);
			Target.Buff(BuffNames::Mute, jailtime, 0);
			Target.setMuted(jailtime);

			IPlayer.SystemMessage("Player has been Jailed for " + Int2String(jailtime) + " seconds.", TEXTCOLOR_GREEN);
			Target.BoxMsg("You have been arrested for " + Int2String(jailtime) + " seconds");
		}
		else {
			IPlayer.SystemMessage("Player Not Online", TEXTCOLOR_RED);
		}

		return;
	}

	if (IPlayer.IsOnline() && IPlayer.GetAdmin() >= 3 && sscanf(command, "/unjail %[a-z | A-Z | 0-9/<>|.,~*;`:!'^+%&/()=?_-£#${[]}\€]", &unjailname) == 1)
	{
		const char *PlayerName = unjailname;
		TargetFind myTarget(PlayerName);
		int player = (int)myTarget.getTarget();
		IChar Target((void*)player);

		if (Target.IsOnline() && Target.IsBuff(BuffNames::Jail))
		{
			Target.CancelBuff(BuffNames::Jail);
			Target.CancelBuff(BuffNames::Mute);
			Target.setMuted(0);

			IPlayer.SystemMessage("Player has been unjailed.", TEXTCOLOR_GREEN);
			Target.BoxMsg("You are now free by an admin.");
		}
		else {
			IPlayer.SystemMessage("Player is not in jail.", TEXTCOLOR_RED);
		}

		return;
	}

	if (IPlayer.IsOnline() && IPlayer.GetAdmin() >= 3 && sscanf(command, "/unmute %[a-z | A-Z | 0-9/<>|.,~*;`:!'^+%&/()=?_-£#${[]}\€]", &unmutename) == 1)
	{
		const char *PlayerName = unmutename;
		TargetFind myTarget(PlayerName);
		int player = (int)myTarget.getTarget();
		IChar Target((void*)player);

		if (Target.IsOnline() && Target.isMuted())
		{
			Target.CancelBuff(BuffNames::Mute);
			Target.setMuted(0);

			IPlayer.SystemMessage("Player has been unmuted.", TEXTCOLOR_GREEN);
			Target.BoxMsg("You have been unmuted by an admin.");
		}
		else
			IPlayer.SystemMessage("Player is not muted.", TEXTCOLOR_RED);

		return;
	}

	if (IPlayer.IsOnline() && IPlayer.GetAdmin() >= 3 && sscanf(command, "/mute %d %[a-z | A-Z | 0-9/<>|.,~*;`:!'^+%&/()=?_-£#${[]}\€]", &mutetime, &mutename) == 2)
	{
		const char *PlayerName = mutename;
		TargetFind myTarget(PlayerName);
		int player = (int)myTarget.getTarget();
		IChar Target((void*)player);

		if (Target.IsOnline() && mutetime)
		{
			Target.CancelBuff(BuffNames::Mute);
			Target.Buff(BuffNames::Mute, mutetime, 0);
			Target.setMuted(mutetime);
			IPlayer.SystemMessage("Player has been Muted for " + Int2String(mutetime) + " seconds.", TEXTCOLOR_GREEN);
			Target.BoxMsg("You have been muted for " + Int2String(mutetime) + " seconds");
		}
		else {
			IPlayer.SystemMessage("Player Not Online", TEXTCOLOR_RED);
		}

		return;
	}
	if (IPlayer.IsOnline() && IPlayer.GetAdmin() >= 3 && cmd.substr(0, 8) == "/hunting") {

		if (Hunting::Active == false)
		{
			std::string GetGuildName;

			if (HuntingID)
			{
				Hunting::Guild = HuntingID;
				GetGuildName = HuntingName;
			}
			else {
				Hunting::Guild = 0;
			}

			if (Hunting::Guild > 0 && !GetGuildName.empty())
			{
				Hunting::Active = true;
				std::string msg = "Hunting System started for " + GetGuildName + " guild.";
				CPlayer::WriteAll(0xFF, "dsd", 247, msg.c_str(), 2);
				int Mob = Summon(0, HGMapI, HGXC, HGYC, HGMobI, 1, 0, 0, 3600000, 0);
				Hunting::Time = HTime;
				Hunting::Monster = (void*)Mob;
			}
		}
		else
			Hunting::Time = 0;
	}

	if (IPlayer.IsOnline() && IPlayer.GetAdmin() >= 8 && cmd.substr(0, 10) == "/happyhour")
	{
		if (HappyHour::Active == false) {
			CPlayer::WriteAll(0xFF, "dsd", 247, thisServerName + " Happy Hour started.", 2);
			HappyHour::Active = true;
		}
		else {
			CPlayer::WriteAll(0xFF, "dsd", 247, thisServerName + " Happy Hour Ended.", 2);
			HappyHour::Active = false;
		}
	}

	if (IPlayer.IsOnline() && IPlayer.GetAdmin() >= 3 && cmd.substr(0.5) == "/hell")
	{
		if (Hell::Active == true) {
			CPlayer::WriteInMap(HellMap, 0xFF, "ddddd", 242, 90, 255, 255, 255);
			Hell::Time = 0;
			Hell::Active = false;
			IPlayer.SystemMessage("POH has been ended", TEXTCOLOR_GREEN);
		}
		else
			IPlayer.SystemMessage("POH is not running", TEXTCOLOR_RED);
		return;
	}
	if (IPlayer.IsOnline() && IPlayer.GetAdmin() >= 8 && cmd.substr(0, 9) == "/immortal")
	{
		if (Immortal::Active == false) {
			CPlayer::WriteAll(0xFF, "dsd", 247, thisServerName + " Immortal Event started.");
			Immortal::Active = true;
		}
		else {
			CPlayer::WriteAll(0xFF, "dsd", 247, thisServerName + " Immortal Event Ended.", 2);
			Immortal::Active = false;
		}
		return;
	}

	if (IPlayer.IsOnline() && sscanf(command, "/cokgroup %d", &COKGroup) == 1)
	{
		if (COKGroup >= 1 && COKGroup <= 8)
			ShowWCGroup(IPlayer, COKGroup);

		return;
	}

	if (IPlayer.IsOnline() && cmd.substr(0, 10) == "/cokgroups") {

		for (int Type = 1; Type < 9; Type++)
			ShowWCGroup(IPlayer, Type);

		return;
	}

	if (IPlayer.IsOnline() && cmd.substr(0, 11) == "/topguild") {
		int GID = IPlayer.GetGID();
		if (GID && GuildTopDonatorList.count(GID)) {

			//		int GuildNameId = CPlayer::GetGuildName((int)IPlayer.GetOffset()); // Assuming it's an int identifier
			if (GID) {
				std::vector<GuildTopDonator> topDonators = GuildTopDonatorList.findValue(GID);
				int Length = topDonators.size();

				CPlayer::Write(IPlayer.GetOffset(), 0xFE, "ds", 213, "- Top " + Int2String(Length) + " Guild Buff donators-");

				for (int i = 0; i < Length; i++) {
					GuildTopDonator donator = topDonators[i];
					std::string notice = " " + Int2String(i + 1) + " - " + donator.name + " - " + Int2String(donator.Amount);
					CPlayer::Write(IPlayer.GetOffset(), 0xFE, "ds", 213, notice.c_str());
				}
			}
		}
		return;
	}


	if (IPlayer.IsOnline() && cmd.substr(0, 7) == "/return")
		return;

	if (IPlayer.IsOnline() && IPlayer.GetAdmin() >= 8 && cmd.substr(0, 9) == "/eggevent")
	{
		if (EggEvent::Active == false) {
			CPlayer::WriteAll(0xFF, "dsd", 247, thisServerName + " Egg Event started.");
			EggEvent::Active = true;
		}
		else {
			CPlayer::WriteAll(0xFF, "dsd", 247, thisServerName + " Egg Event Ended.", 2);
			EggEvent::Active = false;
		}
		return;
	}

	if (IPlayer.IsOnline() && IPlayer.GetAdmin() >= 8 && cmd.substr(0, 4) == "/lms")
	{
		if (LastManStand::Active == false)
		{
			if (LastManRegistration.size() > 1)
			{
				std::string msg = std::string(LMSName) + " started.";
				CPlayer::WriteAll(0xFF, "dsd", 247, msg.c_str(), 2);
				LastManStand::Active = true;
				LastManStand::Time = 3;
				Summon(0, LMSMap, LMSMobX, LMSMobY, LMSMobIndex, 1, 1, 0, 0, 0);
			}
			else {
				std::string msg = std::string(LMSName) + " registeration must be higher than 1 Player. ";
				IPlayer.SystemMessage(msg, TEXTCOLOR_RED);
			}
		}

		return;
	}

	if (IPlayer.IsOnline() && IPlayer.GetAdmin() >= 8 && cmd.substr(0, 10) == "/cwdeclare")
	{
		*(DWORD**)0x004E0964 = (DWORD*)1;
		CPlayer::WriteAll(0xFF, "dsd", 247, "Guilds can declare for castle war.", 2);
		return;
	}

	if (IPlayer.IsOnline() && IPlayer.GetAdmin() >= 8 && cmd.substr(0, 13) == "/endcwdeclare")
	{
		*(DWORD**)0x004E0964 = (DWORD*)0;
		CPlayer::WriteAll(0xFF, "dsd", 247, "Declare for castle war ended.", 2);
		return;
	}

	if (IPlayer.IsOnline() && IPlayer.GetAdmin() >= 8 && sscanf(command, "/cwstart %d", &cwtotaltime) == 1)
	{
		time_t MyTime = time(0);
		struct tm *Time = localtime(&MyTime);

		if ((int)*(DWORD**)0x004E0964 != 4 && cwtotaltime)
		{
			int SetCwTime = MyTime;
			SetCwTime += cwtotaltime;
			*(DWORD**)0x004E0964 = (DWORD*)4;
			WarBegin(SetCwTime);
			CPlayer::WriteAll(0xFF, "dsd", 247, thisServerName + " Castle War has started.", 5);
			ToNoticeWebhook(thisServerName + " Castle War has started.");
		}

		return;
	}

	if (IPlayer.IsOnline() && IPlayer.GetAdmin() >= 8 && cmd.substr(0, 8) == "/stats")
	{
		IPlayer.IncreaseStat(255 - IPlayer.GetStr(), 0);
		CDBSocket::Write(16, "dbwbb", IPlayer.GetPID(), 23, IPlayer.GetStatPoint(), 0, *(DWORD *)(Player + 4 * 0 + 64));
		IPlayer.IncreaseStat(255 - IPlayer.GetHth(), 1);
		CDBSocket::Write(16, "dbwbb", IPlayer.GetPID(), 23, IPlayer.GetStatPoint(), 1, *(DWORD *)(Player + 4 * 1 + 64));
		IPlayer.IncreaseStat(255 - IPlayer.GetInt(), 2);
		CDBSocket::Write(16, "dbwbb", IPlayer.GetPID(), 23, IPlayer.GetStatPoint(), 2, *(DWORD *)(Player + 4 * 2 + 64));
		IPlayer.IncreaseStat(255 - IPlayer.GetWis(), 3);
		CDBSocket::Write(16, "dbwbb", IPlayer.GetPID(), 23, IPlayer.GetStatPoint(), 3, *(DWORD *)(Player + 4 * 3 + 64));
		IPlayer.IncreaseStat(255 - IPlayer.GetAgi(), 4);
		CDBSocket::Write(16, "dbwbb", IPlayer.GetPID(), 23, IPlayer.GetStatPoint(), 4, *(DWORD *)(Player + 4 * 4 + 64));
		IPlayer.SystemMessage("Your Base stats Increased to Max", TEXTCOLOR_INFOMSG);
		return;
	}

	char spawnname[BUFSIZ];
	if (IPlayer.IsOnline() && IPlayer.GetAdmin() >= 8 && sscanf(command, "/rect1 %[a-z | A-Z | 0-9/<>|.,~*;`:!'^+%&/()=?_-£#${[]}\€]", &spawnname) == 1)
	{

		std::string textname = "Spawn";
		std::string FileName = "./Coordinate_System/" + (std::string)textname + ".txt";
		std::fstream SpawnLine;
		SpawnLine.open(FileName, std::fstream::in | std::fstream::out | std::fstream::app);

		CoordinatesGet::X1 = IPlayer.GetX();
		CoordinatesGet::Y1 = IPlayer.GetY();
		SpawnLine << "rect" << " " << spawnname << " ) " << CoordinatesGet::X1 / 32 << " " << CoordinatesGet::Y1 / 32;
		SpawnLine.close();
		IPlayer.SystemMessage("Enter 2nd Coordinates", TEXTCOLOR_GREEN);
		return;
	}


	if (IPlayer.IsOnline() && IPlayer.GetAdmin() >= 8 && cmd.substr(0, 7) == "/rect2")
	{

		std::string textname = "Spawn";
		std::string FileName = "./Coordinate_System/" + (std::string)textname + ".txt";
		std::fstream SpawnLine;
		SpawnLine.open(FileName, std::fstream::in | std::fstream::out | std::fstream::app);

		CoordinatesGet::X2 = IPlayer.GetX();
		CoordinatesGet::Y2 = IPlayer.GetY();
		SpawnLine << " " << CoordinatesGet::X2 / 32 << " " << CoordinatesGet::Y2 / 32 << std::endl;
		SpawnLine.close();
		IPlayer.SystemMessage("Coordinates submitted!", TEXTCOLOR_PINK);
		return;
	}

	if (IPlayer.IsOnline() && IPlayer.GetAdmin() >= 8 && cmd.substr(0, 7) == "/hwids")
	{

		std::string textname = "HWIDs";
		std::string FileName = "./Configs" + (std::string)textname + ".txt";
		std::fstream SpawnLine;
		SpawnLine.open(FileName, std::fstream::in | std::fstream::out | std::fstream::app);

		SpawnLine << "((PlayerName " << IPlayer.GetName() << ") (PID " << IPlayer.GetPID() << ") (HWID " << IPlayer.GetHWID() << ")" << std::endl;
		SpawnLine.close();
		IPlayer.SystemMessage("HWID submitted!", TEXTCOLOR_PINK);
		return;
	}

	char npcname[BUFSIZ];
	if (IPlayer.IsOnline() && IPlayer.GetAdmin() >= 8 && sscanf(command, "/npc %[a-z | A-Z | 0-9/<>|.,~*;`:!'^+%&/()=?_-£#${[]}\€]", &npcname) == 1)
	{
		static int index = 1; // Static variable to keep track of index number
		std::string textname = "NPC";
		std::string FileName = "./Coordinate_System/" + (std::string)textname + ".txt";
		std::fstream SpawnLine;
		SpawnLine.open(FileName, std::fstream::in | std::fstream::out | std::fstream::app);

		CoordinatesGet::X3 = IPlayer.GetX();
		CoordinatesGet::Y3 = IPlayer.GetY();
		CoordinatesGet::Z3 = IPlayer.GetZ();

		SpawnLine << "; " << npcname << "\n" << "(gennpc (index " + Int2String(index) + ") (country 2) (kind 5) (shape 75) (html 1) (map 0) (xy " + Int2String(CoordinatesGet::X3) + " " + Int2String(CoordinatesGet::Y3) + " " + Int2String(CoordinatesGet::Z3) + ") ";
		//	SpawnLine << "NPC) " << CoordinatesGet::X3 << " " << CoordinatesGet::Y3 << " " << CoordinatesGet::Z3 << std::endl;
		SpawnLine.close();
		IPlayer.SystemMessage("NPC Coordinates submitted! use /dir to set npc direction.", TEXTCOLOR_PINK);

		index++; // Increase index number for next spawn line
		return;
	}

	if (IPlayer.IsOnline() && IPlayer.GetAdmin() >= 8 && cmd.substr(0, 4) == "/dir")
	{
		static int index = 1; // Static variable to keep track of index number
		std::string textname = "NPC";
		std::string FileName = "./Coordinate_System/" + (std::string)textname + ".txt";
		std::fstream SpawnLine;
		SpawnLine.open(FileName, std::fstream::in | std::fstream::out | std::fstream::app);

		CoordinatesGet::X3 = IPlayer.GetX();
		CoordinatesGet::Y3 = IPlayer.GetY();
		CoordinatesGet::Z3 = IPlayer.GetZ();

		SpawnLine << "(dir " + Int2String(CoordinatesGet::X3) + " " + Int2String(CoordinatesGet::Y3) + "))" << std::endl;
		//	SpawnLine << "NPC) " << CoordinatesGet::X3 << " " << CoordinatesGet::Y3 << " " << CoordinatesGet::Z3 << std::endl;
		SpawnLine.close();
		IPlayer.SystemMessage("Dir Coordinates submitted!", TEXTCOLOR_ALLIANCE);

		index++; // Increase index number for next spawn line
		return;
	}

	if (IPlayer.IsOnline() && IPlayer.GetAdmin() >= 3 && sscanf(command, "/addeva %d", &amount) == 1)
	{
		IPlayer.AddEva(amount);
		std::string Targe = "Your EVA Increase by [" + Int2String(amount) + "]";
		IPlayer.SystemMessage(Targe, TEXTCOLOR_INFOMSG);
		return;
	}


	if (IPlayer.IsOnline() && IPlayer.GetAdmin() >= 3 && cmd.substr(0, 2) == "/+")
	{
		int i = 0;
		if (!IPlayer.IsBuff(BuffNames::PowerAdm)){
			IPlayer.Buff(48, 3600, 100);
			IPlayer.Buff(47, 3600, 100);
			IPlayer.Buff(49, 3600, 100);
			IPlayer.Buff(46, 3600, 100);
			IPlayer.Buff(36, 3600, 100);
			IPlayer.Buff(37, 3600, 100);
			IPlayer.Buff(12, 3600, 500);
			IPlayer.SystemMessage("Power mode activated.", TEXTCOLOR_GREEN);
			do {
				IPlayer.AddMaxAttack(4000);
				IPlayer.AddMinAttack(4000);
				IPlayer.AddOTP(4000);
				IPlayer.AddEva(4000);
				IPlayer.AddDef(4000);
				i++;
			} while (i < 10);
			IPlayer.IncreaseMaxHp(1000000);
			IPlayer.Buff(BuffNames::PowerAdm, 3600, 1);
		}

		else
			IPlayer.SystemMessage("Power mode already enabled.", TEXTCOLOR_RED);

		(*(void(__cdecl **)(void *, signed int, signed int, int))(*(DWORD *)IPlayer.GetOffset() + 88))(IPlayer.GetOffset(), 7, 1, CChar::GetMaxHp((int)IPlayer.GetOffset()));

		return;
	}

	if (IPlayer.IsOnline() && IPlayer.GetAdmin() >= 3 && cmd.substr(0, 10) == "/reloadnpc")
	{
		try{
			InitNPCReload();
			IPlayer.SystemMessage("InitNPC.txt has been reloaded.", TEXTCOLOR_GREEN);
			return;
		}
		catch (const std::exception&){
			IPlayer.SystemMessage("InitNPC.txt reloading has failed.", TEXTCOLOR_RED);
			return;
		}

		return;
	}

	if (IPlayer.IsOnline() && IPlayer.GetAdmin() >= 3 && cmd.substr(0, 10) == "/reloadmob")
	{
		try{
			InitMonsterReload();
			IPlayer.SystemMessage("InitMonster.txt and GenMonster.txt has been reloaded.", TEXTCOLOR_GREEN);

		}
		catch (const std::exception&){
			IPlayer.SystemMessage("InitMonster.txt and GenMonster.txt reloading has failed.", TEXTCOLOR_RED);
			return;
		}
		return;
	}

	if (IPlayer.IsOnline() && IPlayer.GetAdmin() >= 3 && cmd.substr(0, 12) == "/reloadquest")
	{
		try {
			QuestsReload();
			IPlayer.SystemMessage("Quest.txt has been reloaded.", TEXTCOLOR_GREEN);
		}
		catch (const std::exception&){
			IPlayer.SystemMessage("Quest.txt reloading has failed.", TEXTCOLOR_RED);
			return;
		}
		return;
	}

	if (IPlayer.IsOnline() && IPlayer.GetAdmin() >= 3 && cmd.substr(0, 10) == "/reloadgen")
	{
		try {
			GenMonsterReload();
			IPlayer.SystemMessage("GenMonster.txt has been reloaded.", TEXTCOLOR_GREEN);
		}
		catch (const std::exception&){
			IPlayer.SystemMessage("GenMonster.txt reloading has failed.", TEXTCOLOR_RED);
			return;
		}
		return;
	}

	if (IPlayer.IsOnline() && IPlayer.GetAdmin() >= 3 && cmd.substr(0, 8) == "/partyon")
	{
		IMemory *Memory = new IMemory;
		Memory->Fill(0x0044DA11, 0x1E, 1);
		char arty[1024];
		sprintf_s(arty, "30 Player Party activated by %s", IPlayer.GetName());
		CPlayer::WriteAll(0xFF, "dsd", 247, arty, 9);
		delete Memory;
	}


	if (IPlayer.IsOnline() && IPlayer.GetAdmin() >= 3 && cmd.substr(0, 9) == "/partyoff")
	{
		IMemory *Memory = new IMemory;
		Memory->Fill(0x0044DA11, 0x08, 1);
		char party[1024];
		sprintf_s(party, "30 Player Party deactivated by %s", IPlayer.GetName());
		CPlayer::WriteAll(0xFF, "dsd", 247, party, 9);
		delete Memory;
	}

	if (IPlayer.IsOnline() && IPlayer.GetAdmin() >= 3 && cmd.substr(0, 10) == "/RebirthOn")
	{
		IMemory *Memory = new IMemory;
		Memory->Fill(0x41FFA0, 194, 1);
		Memory->Fill(0x41FFA1, 4, 1);
		Memory->Fill(0x41FFA2, 0, 1);;
		char Rebirth[1024];
		sprintf_s(Rebirth, "Rebirths are blocked by %s", IPlayer.GetName());
		CPlayer::WriteAll(0xFF, "dsd", 247, Rebirth, 9);
		delete Memory;
	}

	if (IPlayer.IsOnline() && IPlayer.GetAdmin() >= 3 && cmd.substr(0, 11) == "/RebirthOff")
	{
		IMemory *Memory = new IMemory;
		Memory->Fill(0x41FFA0, 85, 1);
		Memory->Fill(0x41FFA1, 139, 1);
		Memory->Fill(0x41FFA2, 236, 1);
		char Rebirth1[1024];
		sprintf_s(Rebirth1, "Rebirths reactivated by %s", IPlayer.GetName());
		CPlayer::WriteAll(0xFF, "dsd", 247, Rebirth1, 9);
		delete Memory;
	}

	if (IPlayer.IsOnline() && IPlayer.GetAdmin() >= 3 && sscanf(command, "/addcrt %d", &amount) == 1)
	{
		IPlayer.IncreaseCritRate(amount);
		std::string Targe = "Your Critical Rate Increase by [" + Int2String(amount) + "]";
		IPlayer.SystemMessage(Targe, TEXTCOLOR_INFOMSG);
		return;
	}

	if (IPlayer.IsOnline() && IPlayer.GetAdmin() >= 3 && sscanf(command, "/addcdm %d", &amount) == 1)
	{
		IPlayer.IncreaseCritDamage(amount);
		std::string Targe = "Your Critical Damage Increase by [" + Int2String(amount) + "]";
		IPlayer.SystemMessage(Targe, TEXTCOLOR_INFOMSG);
		return;
	}

	if (IPlayer.IsOnline() && IPlayer.GetAdmin() >= 3 && sscanf(command, "/addotp %d", &amount) == 1)
	{
		IPlayer.AddOTP(amount);
		std::string Targe = "Your OTP Increase by [" + Int2String(amount) + "]";
		IPlayer.SystemMessage(Targe, TEXTCOLOR_INFOMSG);
		return;
	}

	if (IPlayer.IsOnline() && IPlayer.GetAdmin() >= 3 && sscanf(command, "/addmp %d", &amount) == 1)
	{
		IPlayer.IncreaseMaxMp(amount);
		(*(void(__cdecl **)(void *, signed int, signed int, int))(*(DWORD *)IPlayer.GetOffset() + 88))(IPlayer.GetOffset(), 8, 1, CChar::GetMaxMp((int)IPlayer.GetOffset()));
		std::string Targe = "Your MP Increase by [" + Int2String(amount) + "]";
		IPlayer.SystemMessage(Targe, TEXTCOLOR_INFOMSG);
		return;
	}

	if (IPlayer.IsOnline() && IPlayer.GetAdmin() >= 3 && sscanf(command, "/addhp %d", &amount) == 1)
	{

		IPlayer.IncreaseMaxHp(amount);
		(*(void(__cdecl **)(void *, signed int, signed int, int))(*(DWORD *)IPlayer.GetOffset() + 88))(IPlayer.GetOffset(), 7, 1, CChar::GetMaxHp((int)IPlayer.GetOffset()));
		std::string Targe = "Your HP Increase by [" + Int2String(amount) + "]";
		IPlayer.SystemMessage(Targe, TEXTCOLOR_INFOMSG);
		return;
	}

	if (IPlayer.IsOnline() && IPlayer.GetAdmin() >= 3 && sscanf(command, "/addabs %d", &amount) == 1)
	{
		IPlayer.AddAbsorb(amount);
		std::string Targe = "Your Absorb Increase by [" + Int2String(amount) + "]";
		IPlayer.SystemMessage(Targe, TEXTCOLOR_INFOMSG);
		return;
	}

	if (IPlayer.IsOnline() && IPlayer.GetAdmin() >= 3 && sscanf(command, "/addcd %d", &amount) == 1)
	{
		IPlayer.IncreaseCritDamage(amount);
		std::string Targe = "Your Critical Damage Increase by [" + Int2String(amount) + "]";
		IPlayer.SystemMessage(Targe, TEXTCOLOR_INFOMSG);
		return;
	}

	if (IPlayer.IsOnline() && IPlayer.GetAdmin() >= 3 && sscanf(command, "/addsp %d", &amount) == 1)
	{
		IPlayer.AddSkillPoint(amount);
		std::string Targe = "Your SkillPoint Increase by [" + Int2String(amount) + "]";
		IPlayer.SystemMessage(Targe, TEXTCOLOR_INFOMSG);
		return;
	}

	if (IPlayer.IsOnline() && IPlayer.GetAdmin() >= 3 && sscanf(command, "/resetlevel %d", &amount) == 1)
	{
		IPlayer.ResetLevel(amount);
		std::string Targe = "Your level is now [" + Int2String(amount) + "]";
		IPlayer.SystemMessage(Targe, TEXTCOLOR_INFOMSG);
		return;
	}

	if (IPlayer.IsOnline() && cmd.substr(0, 7) == "/invite") {
		if (GuildLimit < 64) {
			int Guild = CPlayer::GetGuild(Player);
			if (Guild) {
				int Size = *(DWORD *)(Guild + 388);
				CSkill::ObjectRelease((void*)Guild, (LONG)(Guild + 40));
				if (Size >= GuildLimit) {
					IPlayer.SystemMessage("You can add up to " + Int2String(GuildLimit) + " guild members.", TEXTCOLOR_BLUELIGHT);
					return;
				}
			}
		}
	}

	//if (IPlayer.IsOnline() && PeaceEvil && IPlayer.GetAdmin() >= 11 && sscanf(command, "/invite %[a-z | A-Z | 0-9/<>|.,~*;`:!'^+%&/()=?_-£#${[]}\€]", &guildinvitename) == 1)
	//{
	//	if (!strlen(guildinvitename))
	//		return;

	//	const char *PlayerName = guildinvitename;
	//	TargetFind myTarget(PlayerName);
	//	int player = (int)myTarget.getTarget();
	//	IChar Target((void*)player);

	//	if (Target.IsOnline() && guildinvitename){
	//		if (IPlayer.isSlytherin() && !Target.isSlytherin()){
	//			IPlayer.SystemMessage("You can't invite players from another house to your guild.", TEXTCOLOR_INFOMSG);
	//			return;
	//		}

	//		if (!IPlayer.isSlytherin() && !IPlayer.isRavenclaw() && !IPlayer.isHufflepuff() && (Target.isSlytherin() || Target.isRavenclaw() || Target.isHufflepuff())){
	//			IPlayer.SystemMessage("You can't invite players from another house to your guild.", TEXTCOLOR_INFOMSG);
	//			return;
	//		}

	//		if (IPlayer.isRavenclaw() && !Target.isRavenclaw()){
	//			IPlayer.SystemMessage("You can't invite players from another house to your guild.", TEXTCOLOR_INFOMSG);
	//			return;
	//		}

	//		if (IPlayer.isHufflepuff() && !Target.isHufflepuff()){
	//			IPlayer.SystemMessage("You can't invite players from another house to your guild.", TEXTCOLOR_INFOMSG);
	//			return;
	//		}
	//	}

	//	if (GuildLimit < 64) {
	//		int Guild = CPlayer::GetGuild(Player);
	//		if (Guild) {
	//			int Size = *(DWORD *)(Guild + 388);
	//			CSkill::ObjectRelease((void*)Guild, (LONG)(Guild + 40));
	//			if (Size >= GuildLimit) {
	//				IPlayer.SystemMessage("You can add up to " + Int2String(GuildLimit) + " guild members.", TEXTCOLOR_BLUELIGHT);
	//				return;
	//			}
	//		}
	//	}
	//}

	if (IPlayer.IsOnline() && IPlayer.GetAdmin() >= 11 && sscanf(command, "/senditem %d %d %d %[a-z | A-Z | 0-9/<>|.,~*;`:!'^+%&/()=?_-£#${[]}\€]", &senditemindx, &senditemprefix, &donateamount, &donatename) == 4)
	{
		if (!strlen(donatename))
			return;

		const char *PlayerName = donatename;
		TargetFind myTarget(PlayerName);
		int player = (int)myTarget.getTarget();
		IChar Target((void*)player);

		if (Target.IsOnline() && donateamount){
			CItem::InsertItem((int)Target.Offset, 27, senditemindx, senditemprefix, donateamount, -1);
			IPlayer.SystemMessage("Player has been rewarded.", TEXTCOLOR_GREEN);
		}
		else 
			IPlayer.SystemMessage("Player is offline.", TEXTCOLOR_RED);

		return;
	}


	if (IPlayer.IsOnline() && IPlayer.GetAdmin() >= 11 && sscanf(command, "/sendserv %d %d %d", &senditemindx, &senditemprefix, &donateamount) == 3)
	{

		CIOCriticalSection::Enter((void*)0x4e2078);
		CIOCriticalSection::Enter((void*)0x4e2098);
		CLink::MoveTo((void*)0x4e200c, (int)0x4e2004);
		CIOCriticalSection::Leave((void*)0x4e2098);
		for (DWORD i = *(DWORD*)0x4E2004; i != 0x4E2004; i = *(DWORD*)i)
		{
			IChar Online((void*)(i - 428));
			if (Online.IsOnline()) {
				Online.InsertItem(senditemindx, senditemprefix, donateamount);
				Online.SystemMessage("Compensation has been recieved.", TEXTCOLOR_GREEN);
			}
		}
		CIOCriticalSection::Leave((void*)0x4e2078);
		return;
	}

	if (IPlayer.IsOnline() && IPlayer.GetAdmin() >= 11 && sscanf(command, "/donate -a %d -n %[a-z | A-Z | 0-9/<>|.,~*;`:!'^+%&/()=?_-£#${[]}\€]", &donateamount, &donatename) == 2)
	{
		if (!strlen(donatename))
			return;

		int Item, ValidItem = 0;
		const char *PlayerName = donatename;
		TargetFind myTarget(PlayerName);
		int player = (int)myTarget.getTarget();
		IChar Target((void*)player);

		if (Target.IsOnline() && donateamount)
		{
			if (CPlayer::FindItem(Target.GetOffset(), DonationCoin, 1))
			{
				Item = CPlayer::FindItem(Target.GetOffset(), DonationCoin, 1);

				if (Item)
				{
					(*(int(__thiscall **)(DWORD, void *, signed int, signed int))(*(DWORD*)Item + 120))(Item, Target.GetOffset(), 9, donateamount);
					Target.SystemMessage("You have received Donation Coin.", TEXTCOLOR_PINK);
					IPlayer.SystemMessage("Donation Coin arrived to player successfully.", TEXTCOLOR_PINK);
					CDBSocket::Write(96, "d", Target.GetPID());
				}
			}
			else {
				if (GetInventorySize((int)Target.GetOffset(), 0) < 60)
				{
					Item = CItem::CreateItem(DonationCoin, 0, donateamount, -1);
					if (Item)
					{
						IItem IItem((void*)Item);
						ValidItem = CPlayer::InsertItem(Target.GetOffset(), 7, Item);

						if (ValidItem == 1)
						{
							Target.SystemMessage("You have received Donation Coin.", TEXTCOLOR_PINK);
							IPlayer.SystemMessage("Donation Coin arrived to player successfully.", TEXTCOLOR_PINK);
							CDBSocket::Write(96, "d", Target.GetPID());
						}
						else {
							CBase::Delete((void*)ValidItem);
							IPlayer.SystemMessage("Donation Coin did not arrived.", TEXTCOLOR_PINK);
						}
					}
				}
				else {
					IPlayer.SystemMessage("Donation Coin did not arrived because player inventory is full.", TEXTCOLOR_PINK);
				}
			}
		}
		else {
			IPlayer.SystemMessage("Player is offline.", TEXTCOLOR_RED);
		}

		return;
	}

	if (IPlayer.IsOnline() && IPlayer.GetAdmin() >= 8 && sscanf(command, "/summon -i %d -a %d", &summonindex, &summonamount) == 2)
	{
		if (summonindex && summonamount)
		{
			for (int i = 0; i < summonamount; i++)
			{
				Summon((int)IPlayer.GetOffset(), IPlayer.GetMap(), IPlayer.GetX(), IPlayer.GetY(), summonindex, 1, 1, 0, 0, 0);
			}
		}

		return;
	}

	int dropMIndex = 0, dropMAmount = 0;
	if (IPlayer.IsOnline() && IPlayer.GetAdmin() >= 3 && sscanf(command, "/drop %d %d", &dropMIndex, &dropMAmount) == 2)
	{
		if (dropMIndex == 0 || dropMAmount == 0) return;
		if (dropMAmount > 1000) {
			IPlayer.SystemMessage("[Error] Max 1000 drops", TEXTCOLOR_RED);
			return;
		}

		//turn on AUTOPICK (remove this line if you are gonna use a pet picker)
		//	CPlayer::Write(IPlayer.GetOffset(), 0xFF, "dd", 221, 1);

		IChar ITarget((void*)Summon(0, IPlayer.GetMap(), IPlayer.GetX(), IPlayer.GetY(), dropMIndex, 1, 0, 0, 3616000, 0));

		if (!ITarget.GetOffset())
		{
			IPlayer.SystemMessage("Invalid monster index.", TEXTCOLOR_RED);
			return;
		}

		for (int i = 0; i < dropMAmount; i++) {
			CInitMonster::DropItem(*(DWORD*)((int)ITarget.GetOffset() + 440), (int)ITarget.GetOffset(), NULL, IPlayer.GetID(), (int)IPlayer.GetOffset(), 0);
		}

		if (RMonstersBuff.find(ITarget.GetMobIndex())->second.mobindex)
		{
			if (ITarget.IsValid() && (*(int(__thiscall **)(int, int, DWORD))(*(DWORD *)IPlayer.GetOffset() + 176))((int)IPlayer.GetOffset(), (int)ITarget.GetOffset(), 0)) {

				*(DWORD *)((int)ITarget.GetOffset() + 272) = 1;
				int DMG = *(DWORD *)((int)ITarget.GetOffset() + 272) * 10000;
				int NormalDamage = 0, DamageArgument = 0, EBDamage = 0, Check = 0, TypeKind = 0, GetType = 0;

				(*(int(__thiscall**)(LONG, void*, unsigned int, int*, int*, int*, DWORD))(*(DWORD*)ITarget.GetOffset() + 72))((int)ITarget.GetOffset(), IPlayer.GetOffset(), DMG, &NormalDamage, &DamageArgument, &EBDamage, 0);

			}
		}
		else
			ITarget.MobDelete();

		//TURNOFF AUTOPICK (remove this line if you are gonna use a pet picker)
		//	CPlayer::Write(IPlayer.GetOffset(), 0xFF, "dd", 221, 0);

		return;
	}

	int killMIndex = 0, mobMIamount = 0;
	if (IPlayer.IsOnline() && IPlayer.GetAdmin() >= 3 && sscanf(command, "/killmob %d %d", &killMIndex, &mobMIamount) == 2)
	{
		if (killMIndex == 0 || mobMIamount == 0) return;
		if (mobMIamount > 1000) {
			IPlayer.SystemMessage("[Error] Max 1000 Monsters", TEXTCOLOR_RED);
			return;
		}

		for (int i = 0; i < mobMIamount; i++) {
			Summon((int)IPlayer.GetOffset(), IPlayer.GetMap(), IPlayer.GetX(), IPlayer.GetY(), killMIndex, 1, 1, 0, 0, 0);
			int Around = IPlayer.GetObjectListAround(killmobs);
			int Count = 0;
			while (Around)
			{
				IChar Object((void*)CBaseList::Offset((void*)Around));

				if (Object.IsValid() && (*(int(__thiscall **)(int, int, DWORD))(*(DWORD *)IPlayer.GetOffset() + 176))((int)IPlayer.GetOffset(), (int)Object.GetOffset(), 0)) {
					Count++;

					*(DWORD *)((int)Object.GetOffset() + 272) = 1;
					int DMG = *(DWORD *)((int)Object.GetOffset() + 272) * 10000;
					int NormalDamage = 0, DamageArgument = 0, EBDamage = 0, Check = 0, TypeKind = 0, GetType = 0;

					(*(int(__thiscall**)(LONG, void*, unsigned int, int*, int*, int*, DWORD))(*(DWORD*)Object.GetOffset() + 72))((int)Object.GetOffset(), IPlayer.GetOffset(), DMG, &NormalDamage, &DamageArgument, &EBDamage, 0);
				}

				Around = CBaseList::Pop((void*)Around);
			}

		}

		return;
	}
	int summonia = 0;
	if (IPlayer.IsOnline() && IPlayer.GetAdmin() >= 8 && sscanf(command, "/spawn %d %d", &summonindex, &summonia) == 2)
	{
		if (summonindex && summonia)
		{
			for (int i = 0; i < summonia; i++)
			{
				Summon(0, IPlayer.GetMap(), IPlayer.GetX(), IPlayer.GetY(), summonindex, 1, 0, 0, 0, 0);
			}
		}
		return;
	}

	if (IPlayer.IsOnline() && IPlayer.GetAdmin() >= 8 && sscanf(command, "/spawn %d", &summonindex) == 1)
	{
		Summon(0, IPlayer.GetMap(), IPlayer.GetX(), IPlayer.GetY(), summonindex, 1, 0, 0, 0, 0);
		IPlayer.SystemMessage("Monster has spawned", TEXTCOLOR_GREEN);

		return;
	}

	if (IPlayer.IsOnline() && IPlayer.GetAdmin() >= 8 && sscanf(command, "/buff %d %d %d", &buffid, &bufftime, &buffvalue) == 3)
	{
		IPlayer.Buff(buffid, bufftime, buffvalue);
		return;
	}

	if (IPlayer.IsOnline() && IPlayer.GetAdmin() >= 8 && sscanf(command, "/buff %d %d", &buffid, &bufftime) == 2)
	{
		IPlayer.Buff(buffid, bufftime, 0);
		return;
	}

	if (IPlayer.IsOnline() && IPlayer.GetAdmin() >= 8 && sscanf(command, "/buff %d", &buffid) == 1)
	{
		IPlayer.Buff(buffid, 3600, 0);
		return;
	}

	if (IPlayer.IsOnline() && IPlayer.GetAdmin() >= 8 && sscanf(command, "/cancelbuff %d", &buffid) == 1)
	{
		IPlayer.CancelBuff(buffid);
		return;
	}

	if (IPlayer.IsOnline() && IPlayer.GetAdmin() >= 3 && sscanf(command, "/speed %d", &speedvalue) == 1)
	{
		if (IPlayer.IsHide())
		{
			IPlayer.SaveBuff(12, 1800, speedvalue, 0, 0);
			return;
		}
		//IPlayer.IncreaseMovingSpeed(speedvalue);
		IPlayer.Buff(12, 1800, speedvalue);

		return;
	}


	if (IPlayer.IsOnline() && IPlayer.GetAdmin() >= 11 && sscanf(command, "/geons %d", &geonamount) == 1)
	{
		if (geonamount)
			CItem::InsertItem((int)IPlayer.Offset, 27, 31, 0, geonamount, -1);

		return;
	}

	if (IPlayer.IsOnline() && cmd.substr(0, 10) == "/surrender")
	{
		if (IPlayer.IsBuff(3089) && betSurrender == 1)
			return;

		if (IPlayer.GetMap() == TBMap || IPlayer.GetMap() == SVMap)
			return;

		if (SinEvent::Active && IPlayer.GetMapX() == SEMapX && IPlayer.GetMapY() == SEMapY)
			return;

		if (IPlayer.IsBuff(349))
			IPlayer.DisableRiding();
	}

	if (IPlayer.IsOnline() && cmd.substr(0, 8) == "/suicide")
	{
		if (IPlayer.IsBuff(3089) && betSuicide == 1)
			return;

		if (IPlayer.IsBuff(BuffNames::LMS))
			return;

		if (SinEvent::Active && IPlayer.GetMapX() == SEMapX && IPlayer.GetMapY() == SEMapY)
			return;

		if (IPlayer.GetMap() == TBMap || IPlayer.GetMap() == SVMap)
			return;

		if (IPlayer.IsBuff(160) || IPlayer.IsBuff(161))
			return;

		if (IPlayer.IsBuff(180) || IPlayer.IsBuff(179))
			return;

		if (IPlayer.IsBuff(162) || IPlayer.IsBuff(163))
			return;

		if (IPlayer.IsBuff(166))
			return;

		if (IPlayer.IsBuff(170) || IPlayer.IsBuff(171))
			return;

		if (IPlayer.IsBuff(373) || IPlayer.IsBuff(374))
			return;

		if (IPlayer.IsBuff(902) || IPlayer.IsBuff(903))
			return;

		if (IPlayer.IsBuff(BuffNames::PTVsPTBlue) || IPlayer.IsBuff(BuffNames::PTVsPTRed))
			return;

		if (IPlayer.IsBuff(349))
			IPlayer.DisableRiding();
	}

	if (IPlayer.IsOnline() && IPlayer.GetAdmin() >= 8 && cmd.substr(0, 15) == "/dueltournament")
	{
		if (DuelTournament::Active == false)
			StartTournament();
		return;
	}

	if (IPlayer.IsOnline() && IPlayer.GetAdmin() >= 8 && cmd.substr(0, 4) == "/f10")
	{
		if (F10::Active == false) {
			if (F10::RegisterAmount > 0)
			{
				F10::CheiosSkillDelay = 0;
				F10::DunamicSkillDelay = 0;
				F10::Ilyer = 0;
				F10::Dunamic = 0;
				F10::Cheios = 0;
				F10::KillCount = 0;
				F10::RegisterAmount = 0;
				F10::Active = true;
				CPlayer::WriteAll(0xFF, "dsd", 247, "Ilyer Company System started.", 2);
				Summon(0, 21, 117332, 36840, 702, 1, 0, 3700000, 3700000, 0);
				return;
			}
			else {
				CPlayer::WriteAll(0xFF, "dsd", 247, "Enough players did not registered for Ilyer Company System.", 2);
				return;
			}
		}
		else {
			F10::CheiosSkillDelay = 0;
			F10::DunamicSkillDelay = 0;
			F10::Ilyer = 0;
			F10::Dunamic = 0;
			F10::Cheios = 0;
			F10::KillCount = 0;
			F10::RegisterAmount = 0;
			F10Registration.clear();
			F10::Active = false;
			CPlayer::WriteAll(0xFF, "dsd", 247, "F10 ended.", 2);

			CIOCriticalSection::Enter((void*)0x4e2078);
			CIOCriticalSection::Enter((void*)0x4e2098);
			CLink::MoveTo((void*)0x4e200c, (int)0x4e2004);
			CIOCriticalSection::Leave((void*)0x4e2098);
			for (DWORD i = *(DWORD*)0x4E2004; i != 0x4E2004; i = *(DWORD*)i)
			{
				IChar Online((void*)(i - 428));
				if (Online.IsOnline() && Online.IsBuff(165) && Online.GetMap() == 21)
					Online.CloseScreenTime();
			}
			CIOCriticalSection::Leave((void*)0x4e2078);
			return;
		}
	}

	if (IPlayer.IsOnline() && IPlayer.GetAdmin() >= 8 && cmd.substr(0, 5) == "/maut")
	{
		if (Maut::Active == false) {
			if (!MautRegistration.empty())
			{
				Maut::Boss = 0;
				Maut::Timer = (int)time(0) + 1799;
				Maut::KillCount = 0;
				Maut::RegisterAmount = 0;
				Maut::Active = true;
				CPlayer::WriteAll(0xFF, "dsd", 247, "Mautareta System started.", 2);
				return;
			}
			else {
				CPlayer::WriteAll(0xFF, "dsd", 247, "Enough players did not registered for Mautareta System.", 2);
				return;
			}
		}
		else {
			Maut::Boss = 0;
			Maut::Timer = 0;
			Maut::KillCount = 0;
			Maut::RegisterAmount = 0;
			MautRegistration.clear();
			Maut::Active = false;
			CPlayer::WriteAll(0xFF, "dsd", 247, "Mautareta System ended.", 2);
			return;
		}
	}

	if (IPlayer.IsOnline() && IPlayer.GetAdmin() >= 8 && cmd.substr(0, 8) == "/bossexp")
	{
		if (BossEXP::Active == false) {
			if (!BossEXPRegistration.empty())
			{
				BossEXP::Boss = 0;
				BossEXP::Timer = (int)time(0) + BossEXPTime;
				BossEXP::KillCount = 0;
				BossEXP::RegisterAmount = 0;
				BossEXP::Active = true;
				return;
			}
		}
		else {
			BossEXP::Boss = 0;
			BossEXP::Timer = 0;
			BossEXP::KillCount = 0;
			BossEXP::RegisterAmount = 0;
			BossEXPRegistration.clear();
			BossEXP::Active = false;
			return;
		}
	}

	if (IPlayer.IsOnline() && cmd.substr(0, 11) == "/showguilds")
	{
		if (Scenario::Selection && Scenario::GuildFirst && Scenario::GuildSecond) {
			IPlayer.SystemMessage("Next Destructing Keys will feature " + Scenario::FirstGuild + " vs " + Scenario::SecondGuild + ".", TEXTCOLOR_INFOMSG);
			return;
		}

		IPlayer.SystemMessage("Destructing keys selection has not yet been made.", TEXTCOLOR_FAILED);
		return;
	}

	if (IPlayer.IsOnline() && IPlayer.GetAdmin() >= 8 && cmd.substr(0, 12) == "/destructing")
	{
		if (Scenario::Active == false)
			startGVG();

		else {
			Scenario::Active = false;
			Scenario::Time = 0;
		}
		return;
	}

	if (IPlayer.IsOnline() && IPlayer.GetAdmin() >= 8 && cmd.substr(0, 15) == "/guildselection")
	{
		if (Scenario::Active == false)
			GVGSelection();

		return;
	}

	if (IPlayer.IsOnline() && IPlayer.GetAdmin() >= 3 && cmd.substr(0, 10) == "/reloadgvg") {
		reloadGVG();
		IPlayer.SystemMessage("Guild vs Guild has been reloaded.", TEXTCOLOR_GREEN);
		return;
	}

	if (IPlayer.IsOnline() && IPlayer.GetAdmin() >= 3 && cmd.substr(0, 12) == "/reloadblock") {
		reloadBlock();
		IPlayer.SystemMessage("Block list has been reloaded.", TEXTCOLOR_GREEN);
		return;
	}

	if (IPlayer.IsOnline() && cmd.substr(0, 12) == "/showprotect")
	{
		if (Protect32::Selection && Protect32::GuildFirst && Protect32::GuildSecond) {
			IPlayer.SystemMessage("Next Protecting Laader will feature " + Protect32::FirstGuild + " vs " + Protect32::SecondGuild + ".", TEXTCOLOR_INFOMSG);
			return;
		}

		IPlayer.SystemMessage("Protecting Leader selection has not yet been made.", TEXTCOLOR_FAILED);
		return;
	}

	if (IPlayer.IsOnline() && IPlayer.GetAdmin() >= 8 && cmd.substr(0, 15) == "/protectleader")
	{
		if (Protect32::Active == false)
			startProtect();

		else {
			Protect32::Active = false;
			Protect32::Time = 0;
		}
		return;
	}

	if (IPlayer.IsOnline() && IPlayer.GetAdmin() >= 8 && cmd.substr(0, 17) == "/protectselection")
	{
		if (Protect32::Active == false)
			ProtectSelection();

		return;
	}

	if (IPlayer.IsOnline() && IPlayer.GetAdmin() >= 3 && cmd.substr(0, 14) == "/reloadprotect") {
		reloadProtect();
		IPlayer.SystemMessage("Protect has been reloaded.", TEXTCOLOR_GREEN);
		return;
	}

	if (IPlayer.IsOnline() && IPlayer.GetAdmin() >= 8 && cmd.substr(0, 12) == "/battlefield")
	{
		startBF(false);
		return;
	}

	int EMaps = 0, EMapsF = 0;
	if (IPlayer.IsOnline() && IPlayer.GetAdmin() >= 3 && sscanf(command, "/eventmap %d %d", &EMaps, &EMapsF) == 2)
	{
		if (EventMapStart((EMaps * 1000) + EMapsF))
			IPlayer.SystemMessage("Event Map started.", TEXTCOLOR_GREEN);
		else
			IPlayer.SystemMessage("Event Map couldnt start", TEXTCOLOR_RED);
		return;
	}

	int ERegister = 0, ERegisterF = 0;
	if (IPlayer.IsOnline() && IPlayer.GetAdmin() >= 3 && sscanf(command, "/registeron %d %d", &ERegister, &ERegisterF) == 2)
	{
		if (EventMapRegister((ERegister * 1000) + ERegisterF))
			IPlayer.SystemMessage("Event Map registration activated.", TEXTCOLOR_GREEN);
		else
			IPlayer.SystemMessage("Event Map registration couldnt activate.", TEXTCOLOR_RED);
		return;
	}

	if (IPlayer.IsOnline() && IPlayer.GetAdmin() >= 8 && cmd.substr(0, 11) == "/goodvsevil")
	{
		startBF(true);
		return;
	}

	int SETime = 0;
	if (IPlayer.IsOnline() && IPlayer.GetAdmin() >= 3 && sscanf(command, "/sinevent %d", &SETime) == 1)
	{
		startSinEvent(SETime);
		return;
	}

	if (IPlayer.IsOnline() && IPlayer.GetAdmin() >= 3 && sscanf(command, "/boxnotice %[a-z | A-Z | 0-9/<>|.,~*;`:!'^+%&/()=?_-£#${[]}\€]", &boxnotice) == 1)
	{
		if (strlen(boxnotice))
			CPlayer::WriteAll(0xFF, "ds", 249, boxnotice);

		return;
	}

	if (IPlayer.IsOnline() && cmd.substr(0, 11) == "/ignorelist") {
		CPlayer::Write((void*)Player, 0xFE, "d", 203);
		return;
	}

	if (IPlayer.IsOnline() && sscanf(command, "/unignore %[a-z | A-Z | 0-9/<>|.,~*;`:!'^+%&/()=?_-£#${[]}\€]", &unignoredPlayer) == 1) {
		std::string playerName = unignoredPlayer;
		IPlayer.SystemMessage(playerName + " is approved.", TEXTCOLOR_GENERAL);
		CPlayer::Write((void*)Player, 0xFE, "ds", 204, playerName.c_str());
	}

	if (IPlayer.IsOnline() && sscanf(command, "/ignore %[a-z | A-Z | 0-9/<>|.,~*;`:!'^+%&/()=?_-£#${[]}\€]", &ignoredPlayer) == 1) {
		std::string playerName = ignoredPlayer;
		IPlayer.SystemMessage(playerName + " is now being ignored.", TEXTCOLOR_GENERAL);
		CPlayer::Write((void*)Player, 0xFE, "ds", 205, playerName.c_str());
	}

	if (IPlayer.IsOnline() && sscanf(command, "/bet %[a-z | A-Z | 0-9/<>|.,~*;`:!'^+%&/()=?_-£#${[]}\€]", &bet) == 1)
	{
		if (!strlen(bet))
			return;

		if (IPlayer.isInTrainingMap()) {
			IPlayer.SystemMessage("No duel is available at Training Center.", TEXTCOLOR_RED);
			return;
		}

		if (EFakePlayers && FakeNames.count(bet) && (EFakePlayers*-1) <= FakeNames.findValue(bet)) {
			IPlayer.SystemMessage("Opponent is currently busy on a bet ask", TEXTCOLOR_RED);
			return;
		}

		const char *PlayerName = bet;
		TargetFind myTarget(PlayerName);
		int player = (int)myTarget.getTarget();
		IChar Target((void*)player);

		if (Target.IsValid() && IPlayer.IsValid()) {
			if (IPlayer.GetBuffValue(BuffNames::BetOpponent)) {
				IPlayer.SystemMessage("Wait for your other opponent to answer the bet", TEXTCOLOR_RED);
				return;
			}
			if (Target.GetBuffValue(BuffNames::BetOpponent)) {
				IPlayer.SystemMessage("Opponent is currently busy on a bet ask", TEXTCOLOR_RED);
				return;
			}

			if (Target.GetType() == 0 && Target.GetPID() != IPlayer.GetPID() && Target.IsOnline()) {
				if (CChar::GetRange((int)IPlayer.GetOffset() + 332, (int)Target.GetOffset() + 332) <= 64) {
					IPlayer.SystemMessage("Waiting on " + (std::string)Target.GetName() + " To accept the bet..", TEXTCOLOR_BLUELIGHT);

					IPlayer.UpdateBuff(BuffNames::BetOpponent, BuffNames::BuffTime, Target.GetID());

					Target.UpdateBuff(BuffNames::BetOpponent, BuffNames::BuffTime, IPlayer.GetID());

					CPlayer::AskPvP((int)IPlayer.GetOffset(), Target.GetID());
					Target.BoxMsg("You received a duel bet from " + (std::string)IPlayer.GetName());
				}
				else
					IPlayer.SystemMessage("Player is too far.", TEXTCOLOR_RED);
			}
		}
		else
			IPlayer.SystemMessage("Wrong or Offline Player!", TEXTCOLOR_RED);
		return;
	}

	if (IPlayer.IsOnline() && IPlayer.GetAdmin() >= 8 && cmd.substr(0, 10) == "/cleanload")
	{
		CleanLoadConfig();
		IPlayer.SystemMessage("Configs Cleaned and loaded successfully.", TEXTCOLOR_GREEN);
		return;
	}

	if (IPlayer.IsOnline() && IPlayer.GetAdmin() >= 3 && cmd.substr(0, 7) == "/reload")
	{
		ReadConfig(true);
		for (auto x = modifiedFiles.rbegin(); x != modifiedFiles.rend(); x++)
			IPlayer.SystemMessage(*x + " reloaded successfully.", TEXTCOLOR_GREEN);
		return;
	}

	if (IPlayer.IsOnline() && IPlayer.GetAdmin() >= 3 && cmd.substr(0, 5) == "/list")
	{
		int n = 0;
		CPlayer::Write((void*)Player, 0xFE, "ds", 213, "Online Players List:\n");
		CIOCriticalSection::Enter((void*)0x4e2078);
		CIOCriticalSection::Enter((void*)0x4e2098);
		CLink::MoveTo((void*)0x4e200c, (int)0x4e2004);
		CIOCriticalSection::Leave((void*)0x4e2098);
		for (DWORD i = *(DWORD*)0x4E2004; i != 0x4E2004; i = *(DWORD*)i)
		{
			n++;
			IChar Online((void*)(i - 428));
			if (Online.IsOnline()) {
				std::string name(Online.GetName());
				std::string msg = Int2String(n) + "- " + name + " | Level: " + Int2String(Online.GetLevel());
				CPlayer::Write((void*)Player, 0xFE, "ds", 213, msg.c_str());
			}
		}
		CIOCriticalSection::Leave((void*)0x4e2078);
		return;
	}

	if (IPlayer.IsOnline() && IPlayer.GetAdmin() >= 3 && cmd.substr(0, 7) == "/online")
	{
		std::stringstream onlineplayer;
		onlineplayer << "Players Online : " << InterlockedExchangeAdd(&OnlinePlayers, 0);
		std::string onlineamount = onlineplayer.str();
		IPlayer.SystemMessage(onlineamount.c_str(), TEXTCOLOR_INFOMSG);
		return;
	}

	if (IPlayer.IsOnline() && IPlayer.GetAdmin() >= 3 && cmd.substr(0, 12) == "/portuserall")
	{
		int Map = IPlayer.GetMap();
		int X = IPlayer.GetX();
		int Y = IPlayer.GetY();

		CIOCriticalSection::Enter((void*)0x4e2078);
		CIOCriticalSection::Enter((void*)0x4e2098);
		CLink::MoveTo((void*)0x4e200c, (int)0x4e2004);
		CIOCriticalSection::Leave((void*)0x4e2098);
		for (DWORD i = *(DWORD*)0x4E2004; i != 0x4E2004; i = *(DWORD*)i)
		{
			IChar Online((void*)(i - 428));
			if (Online.IsOnline() && Online.GetPID() != IPlayer.GetPID()) {
				Online.Teleport(Map, X, Y);
			}
		}
		CIOCriticalSection::Leave((void*)0x4e2078);
		return;
	}

	if (IPlayer.IsOnline() && IPlayer.GetAdmin() >= 3 && sscanf(command, "/portuser %[a-z | A-Z | 0-9/<>|.,~*;`:!'^+%&/()=?_-£#${[]}\€]", &portuser) == 1)
	{
		if (strlen(portuser))
		{
			const char *PlayerName = portuser;
			TargetFind myTarget(PlayerName);
			int player = (int)myTarget.getTarget();
			IChar Target((void*)player);

			if (Target.IsOnline()) {
				int Channel = IPlayer.GetChannel();
				int ChannelO = Target.GetChannel();
				if (Channel != ChannelO)
					Target.SetChannelSystem(Channel);

				Target.Teleport(IPlayer.GetMap(), IPlayer.GetX(), IPlayer.GetY(), IPlayer.GetZ());
			}
		}

		return;
	}

	if (IPlayer.IsOnline() && IPlayer.GetAdmin() >= 3 && sscanf(command, "/moveto %[a-z | A-Z | 0-9/<>|.,~*;`:!'^+%&/()=?_-£#${[]}\€]", &moveto) == 1)
	{
		if (strlen(moveto))
		{
			const char *PlayerName = moveto;
			TargetFind myTarget(PlayerName);
			int player = (int)myTarget.getTarget();
			IChar Target((void*)player);

			if (Target.IsOnline()) {
				int Channel = IPlayer.GetChannel();
				int ChannelO = Target.GetChannel();
				if (Channel != ChannelO)
					IPlayer.SetChannelSystem(ChannelO);

				IPlayer.Teleport(Target.GetMap(), Target.GetX(), Target.GetY(), Target.GetZ());
			}
			else
			if (EFakePlayers && FakeNames.count(PlayerName)) {
				int id = FakeNames.findValue(PlayerName);
				if ((EFakePlayers*-1) <= id && FakePlayers.count(id)) {
					FakePlayers_ fPlayer = FakePlayers.findValue(id);
					IPlayer.Teleport(0, fPlayer.x, fPlayer.y, fPlayer.z);
				}
			}
		}

		return;
	}

	if (IPlayer.IsOnline() && cmd.substr(0, 11) == "/servertime")
	{
		std::stringstream servertime;
		servertime << "Server Time : " << Time::GetTime();
		std::string time = servertime.str();
		IPlayer.SystemMessage(time.c_str(), TEXTCOLOR_INFOMSG);
		return;
	}

	int deleteitemindex = 0;
	if (IPlayer.IsOnline() && IPlayer.GetAdmin() >= 3 && sscanf(command, "/deleteitem %d", &deleteitemindex) == 1)
	{
		CIOCriticalSection::Enter((void*)0x4e2078);
		CIOCriticalSection::Enter((void*)0x4e2098);
		CLink::MoveTo((void*)0x4e200c, (int)0x4e2004);
		CIOCriticalSection::Leave((void*)0x4e2098);

		for (DWORD i = *(DWORD*)0x4E2004; i != 0x4E2004; i = *(DWORD*)i)
		{
			IChar Online((void*)(i - 428));
			if (Online.IsOnline()) {
				int FindItem = CPlayer::FindItem(Online.GetOffset(), deleteitemindex, 1);
				IItem DeletedItem((void*)FindItem);
				if (FindItem){
					int amount = DeletedItem.GetAmount();
					CPlayer::RemoveItem(Online.GetOffset(), 9, deleteitemindex, amount);
					CDBSocket::Write(123, "d", deleteitemindex);
				}
			}
		}

		CIOCriticalSection::Leave((void*)0x4e2078);
		IPlayer.SystemMessage("Item with index " + Int2String(deleteitemindex) + " removed from server", TEXTCOLOR_GREEN);
		return;
	}

	if (IPlayer.IsOnline() && IPlayer.GetAdmin() >= 3 && cmd.substr(0, 8) == "/eventon")
	{
		std::string EventHoster = IPlayer.GetName();
		std::string msg = thisServerName + " EXP Event has started by " + EventHoster;
		CPlayer::WriteAll(0xFF, "ds", 234, msg.c_str());

		ToNoticeWebhook(msg.c_str());
		CPlayer::SetEventCode(0, 1);
		return;
	}

	if (IPlayer.IsOnline() && IPlayer.GetAdmin() >= 3 && cmd.substr(0, 7) == "/damage")
	{
		if (DamageEvent::Active){
			DamageEvent::Active = false;
			std::string msg = "Damage Event has ended.";
			CPlayer::WriteAll(0xFF, "dsd", 247, msg.c_str(), 2);
			ToNoticeWebhook(newnotice);

		}
		else{
			std::string msg = "Damage Event has been started.";
			DamageEvent::Active = true;
			CPlayer::WriteAll(0xFF, "dsd", 247, msg.c_str(), 2);
		}
		return;
	}

	if (IPlayer.IsOnline() && IPlayer.GetAdmin() >= 3 && sscanf(command, "/notice %[a-z | A-Z | 0-9/<>|.,~*;`:!'^+%&/()=?_-£#${[]}\€]", &newnotice) == 1)
	{
		if (strlen(newnotice))
			ToNoticeWebhook(newnotice);
	}

	if (IPlayer.IsOnline() && IPlayer.GetAdmin() >= 3 && cmd.substr(0, 7) == "/uptime")
	{
		IPlayer.SystemMessage(getUptime().c_str(), TEXTCOLOR_INFOMSG);
		return;
	}

	if (IPlayer.IsOnline() && IPlayer.GetAdmin() >= 3 && sscanf(command, "/newnotice %d %[a-z | A-Z | 0-9/<>|.,~*;`:!'^+%&/()=?_-£#${[]}\€]", &newnoticetype, &newnotice) == 2)
	{
		if (strlen(newnotice))
			CPlayer::WriteAll(0xFF, "dsd", 247, newnotice, newnoticetype);

		return;
	}

	if (IPlayer.IsOnline() && IPlayer.GetAdmin() >= 3 && sscanf(command, "/hardblock %[a-z | A-Z | 0-9/<>|.,~*;`:!'^+%&/()=?_-£#${[]}\€]", &hardblock) == 1)
	{
		if (!strlen(hardblock))
			return;

		RETCODE rcc; HENV henvc; HDBC hdbcc; HSTMT hstmtc; SDWORD cbDatac; int UID = 0;
		const char *dbc = ConfigCheckDB2.c_str();
		SQLAllocEnv(&henvc);
		SQLAllocConnect(henvc, &hdbcc);
		rcc = SQLConnect(hdbcc, (unsigned char*)dbc, SQL_NTS, 0, 0, 0, 0);

		if ((rcc != SQL_SUCCESS) && (rcc != SQL_SUCCESS_WITH_INFO))
		{
			SQLFreeConnect(hdbcc);
			SQLFreeEnv(henvc);
			return;
		}

		rcc = SQLAllocStmt(hdbcc, &hstmtc);
		std::stringstream query;
		query << "SELECT [UID] FROM [Player] WHERE [Name] = '" << hardblock << "'";
		std::string runquery = query.str();
		const char *sql = runquery.c_str();
		rcc = SQLExecDirect(hstmtc, (unsigned char*)sql, SQL_NTS);
		if ((rcc != SQL_SUCCESS) && (rcc != SQL_SUCCESS_WITH_INFO))
		{
			SQLFreeStmt(hstmtc, SQL_DROP);
			SQLDisconnect(hdbcc);
			SQLFreeConnect(hdbcc);
			SQLFreeEnv(henvc);
			return;
		}
		else{
			for (rcc = SQLFetch(hstmtc); rcc == SQL_SUCCESS; rcc = SQLFetch(hstmtc))
				SQLGetData(hstmtc, 1, SQL_INTEGER, &UID, sizeof(int), &cbDatac);
		}

		SQLFreeStmt(hstmtc, SQL_DROP);
		SQLDisconnect(hdbcc);
		SQLFreeConnect(hdbcc);
		SQLFreeEnv(henvc);

		if (UID)
		{
			RETCODE rcb; HENV henvb; HDBC hdbcb; HSTMT hstmtb;
			const char *dbb = ConfigCheckDB1.c_str();
			SQLAllocEnv(&henvb);
			SQLAllocConnect(henvb, &hdbcb);
			rcb = SQLConnect(hdbcb, (unsigned char*)dbb, SQL_NTS, 0, 0, 0, 0);

			if ((rcb != SQL_SUCCESS) && (rcb != SQL_SUCCESS_WITH_INFO))
			{
				SQLFreeConnect(hdbcb);
				SQLFreeEnv(henvb);
				return;
			}

			rcb = SQLAllocStmt(hdbcb, &hstmtb);
			std::stringstream query;
			query << "UPDATE [Login] SET [Type] = 2 WHERE [UID] = '" << UID << "'";
			std::string runquery = query.str();
			const char *sql = runquery.c_str();
			rcb = SQLExecDirect(hstmtb, (unsigned char*)sql, SQL_NTS);
			if ((rcb != SQL_SUCCESS) && (rcb != SQL_SUCCESS_WITH_INFO))
			{
				SQLFreeStmt(hstmtb, SQL_DROP);
				SQLDisconnect(hdbcb);
				SQLFreeConnect(hdbcb);
				SQLFreeEnv(henvb);
				return;
			}

			SQLFreeStmt(hstmtb, SQL_DROP);
			SQLDisconnect(hdbcb);
			SQLFreeConnect(hdbcb);
			SQLFreeEnv(henvb);
			const char *Player = hardblock;
			TargetFind myTarget(Player);
			int player = (int)myTarget.getTarget();
			IChar Target((void*)player);

			IPlayer.SystemMessage("Player successfully blocked.", TEXTCOLOR_GREEN);
			if (Target.IsOnline())
			{
				//userLock.Enter();
				UserInfo playerInfo = User.findValue(Target.GetPID());
				//userLock.Leave();

				//blockLock.Enter();
				bool NotBlocked = !(BlockList.count(sha256(playerInfo.Hardware)) && BlockList.count(sha256(playerInfo.MAC)) && BlockList.count(sha256(Target.GetIP())));
				//blockLock.Leave();

				if (NotBlocked) {
					std::string Datko = "./Database/HWIDBlock.txt";
					std::fstream DGkLOG;
					DGkLOG.open(Datko, std::fstream::in | std::fstream::out | std::fstream::app);
					DGkLOG << "(hwidblock (uid " << UID << ")(hwid '" << (playerInfo.Hardware) << "')(mac '" << (playerInfo.MAC) << "')(ip '" << (Target.GetIP()) << "'))" << std::endl;
					DGkLOG.close();

					//blockLock.Enter();
					BlockList.insert(sha256(playerInfo.Hardware));
					BlockList.insert(sha256(playerInfo.MAC));
					BlockList.insert(sha256(Target.GetIP()));
					//blockLock.Leave();
				}
				PlayerBlockCheck.insert(Target.GetUID());
				Target.SystemMessage("Your account has been blocked.", TEXTCOLOR_RED);
				//CPlayer::Write(Target.GetOffset(), 0xFE, "d", 246);
				Target.Kick();
			}
		}
		else {
			IPlayer.SystemMessage("Could not block player.", TEXTCOLOR_GREEN);
		}

		return;
	}

	//if (IPlayer.IsOnline() && IPlayer.GetAdmin() >= 3 && sscanf(command, "/block %s %d", &block, &blocktime) == 2)
	//{
	//	if (!strlen(block))
	//		return;

	//	const char *Player = block;
	//	TargetFind myTarget(Player);
	//	int player = (int)myTarget.getTarget();
	//	IChar Target((void*)player);

	//	if (Target.GetUID() && blocktime){

	//		CDBSocket::Write(125, "ddd", 4, Target.GetUID(), blocktime);
	//		IPlayer.SystemMessage("Player successfully blocked.", TEXTCOLOR_GREEN);

	//		if (Target.IsOnline())
	//		{
	//			PlayerBlockCheck.insert(Target.GetUID());
	//			Target.SystemMessage("Your account has been blocked.", TEXTCOLOR_RED);
	//			Target.Kick();
	//		}
	//	}
	//	else {
	//		IPlayer.SystemMessage("Could not block player.", TEXTCOLOR_GREEN);
	//	}

	//	return;
	//}


	//if (IPlayer.IsOnline() && IPlayer.GetAdmin() >= 3 && sscanf(command, "/block %s", &block) == 1)
	//{
	//	if (!strlen(block))
	//		return;

	//	const char *Player = block;
	//	TargetFind myTarget(Player);
	//	int player = (int)myTarget.getTarget();
	//	IChar Target((void*)player);

	//	if (Target.GetUID()){

	//		CDBSocket::Write(125, "dd", 4, Target.GetUID());
	//		IPlayer.SystemMessage("Player successfully blocked.", TEXTCOLOR_GREEN);

	//		if (Target.IsOnline())
	//		{
	//			PlayerBlockCheck.insert(Target.GetUID());
	//			Target.SystemMessage("Your account has been blocked.", TEXTCOLOR_RED);
	//			Target.Kick();
	//		}
	//	}
	//	else {
	//		IPlayer.SystemMessage("Could not block player.", TEXTCOLOR_GREEN);
	//	}

	//	return;
	//}


	if (IPlayer.IsOnline() && IPlayer.GetAdmin() >= 3 && sscanf(command, "/block %[a-z | A-Z | 0-9/<>|.,~*;`:!'^+%&/()=?_-£#${[]}\€]", &block) == 1)
	{
		if (!strlen(block))
			return;

		RETCODE rcd; HENV henvd; HDBC hdbcd; HSTMT hstmtd; SDWORD cbDatad; int UID = 0;
		const char *dbd = ConfigCheckDB2.c_str();
		SQLAllocEnv(&henvd);
		SQLAllocConnect(henvd, &hdbcd);
		rcd = SQLConnect(hdbcd, (unsigned char*)dbd, SQL_NTS, 0, 0, 0, 0);

		if ((rcd != SQL_SUCCESS) && (rcd != SQL_SUCCESS_WITH_INFO))
		{
			SQLFreeConnect(hdbcd);
			SQLFreeEnv(henvd);
			return;
		}

		rcd = SQLAllocStmt(hdbcd, &hstmtd);
		std::stringstream query;
		query << "SELECT [UID] FROM [Player] WHERE [Name] = '" << block << "'";
		std::string runquery = query.str();
		const char *sql = runquery.c_str();
		rcd = SQLExecDirect(hstmtd, (unsigned char*)sql, SQL_NTS);
		if ((rcd != SQL_SUCCESS) && (rcd != SQL_SUCCESS_WITH_INFO))
		{
			SQLFreeStmt(hstmtd, SQL_DROP);
			SQLDisconnect(hdbcd);
			SQLFreeConnect(hdbcd);
			SQLFreeEnv(henvd);
			return;
		}
		else {
			for (rcd = SQLFetch(hstmtd); rcd == SQL_SUCCESS; rcd = SQLFetch(hstmtd))
				SQLGetData(hstmtd, 1, SQL_INTEGER, &UID, sizeof(int), &cbDatad);
		}

		SQLFreeStmt(hstmtd, SQL_DROP);
		SQLDisconnect(hdbcd);
		SQLFreeConnect(hdbcd);
		SQLFreeEnv(henvd);

		if (UID)
		{
			RETCODE rce; HENV henve; HDBC hdbce; HSTMT hstmte;
			const char *db = ConfigCheckDB1.c_str();
			SQLAllocEnv(&henve);
			SQLAllocConnect(henve, &hdbce);
			rce = SQLConnect(hdbce, (unsigned char*)db, SQL_NTS, 0, 0, 0, 0);

			if ((rce != SQL_SUCCESS) && (rce != SQL_SUCCESS_WITH_INFO))
			{
				SQLFreeConnect(hdbce);
				SQLFreeEnv(henve);
				return;
			}

			rce = SQLAllocStmt(hdbce, &hstmte);
			std::stringstream query;
			query << "UPDATE [Login] SET [Type] = 2 WHERE [UID] = '" << UID << "'";
			std::string runquery = query.str();
			const char *sql = runquery.c_str();
			rce = SQLExecDirect(hstmte, (unsigned char*)sql, SQL_NTS);
			if ((rce != SQL_SUCCESS) && (rce != SQL_SUCCESS_WITH_INFO))
			{
				SQLFreeStmt(hstmte, SQL_DROP);
				SQLDisconnect(hdbce);
				SQLFreeConnect(hdbce);
				SQLFreeEnv(henve);
				return;
			}

			SQLFreeStmt(hstmte, SQL_DROP);
			SQLDisconnect(hdbce);
			SQLFreeConnect(hdbce);
			SQLFreeEnv(henve);
			const char *Player = block;
			TargetFind myTarget(Player);
			int player = (int)myTarget.getTarget();
			IChar Target((void*)player);

			IPlayer.SystemMessage("Player successfully blocked.", TEXTCOLOR_GREEN);
			if (Target.IsOnline())
			{
				PlayerBlockCheck.insert(Target.GetUID());
				Target.SystemMessage("Your account has been blocked.", TEXTCOLOR_RED);
				Target.Kick();
			}
		}
		else {
			IPlayer.SystemMessage("Could not block player.", TEXTCOLOR_GREEN);
		}

		return;
	}


	if (IPlayer.IsOnline() && IPlayer.GetAdmin() >= 3 && sscanf(command, "/unblock %[a-z | A-Z | 0-9/<>|.,~*;`:!'^+%&/()=?_-£#${[]}\€]", &unblock) == 1)
	{
		if (!strlen(unblock))
			return;

		RETCODE rc; HENV henv; HDBC hdbc; HSTMT hstmt; SDWORD cbData; int UID = 0;
		const char *db = ConfigCheckDB2.c_str();
		SQLAllocEnv(&henv);
		SQLAllocConnect(henv, &hdbc);
		rc = SQLConnect(hdbc, (unsigned char*)db, SQL_NTS, 0, 0, 0, 0);

		if ((rc != SQL_SUCCESS) && (rc != SQL_SUCCESS_WITH_INFO))
		{
			SQLFreeConnect(hdbc);
			SQLFreeEnv(henv);
			return;
		}

		rc = SQLAllocStmt(hdbc, &hstmt);
		std::stringstream query;
		query << "SELECT [UID] FROM [Player] WHERE [Name] = '" << unblock << "'";
		std::string runquery = query.str();
		const char *sql = runquery.c_str();
		rc = SQLExecDirect(hstmt, (unsigned char*)sql, SQL_NTS);
		if ((rc != SQL_SUCCESS) && (rc != SQL_SUCCESS_WITH_INFO))
		{
			SQLFreeStmt(hstmt, SQL_DROP);
			SQLDisconnect(hdbc);
			SQLFreeConnect(hdbc);
			SQLFreeEnv(henv);
			return;
		}
		else{
			for (rc = SQLFetch(hstmt); rc == SQL_SUCCESS; rc = SQLFetch(hstmt))
				SQLGetData(hstmt, 1, SQL_INTEGER, &UID, sizeof(int), &cbData);
		}

		SQLFreeStmt(hstmt, SQL_DROP);
		SQLDisconnect(hdbc);
		SQLFreeConnect(hdbc);
		SQLFreeEnv(henv);

		if (UID)
		{
			PlayerBlockCheck.erase(UID);
			RETCODE rca; HENV henva; HDBC hdbca; HSTMT hstmta;
			const char *dba = ConfigCheckDB1.c_str();
			SQLAllocEnv(&henva);
			SQLAllocConnect(henva, &hdbca);
			rca = SQLConnect(hdbca, (unsigned char*)dba, SQL_NTS, 0, 0, 0, 0);

			if ((rca != SQL_SUCCESS) && (rca != SQL_SUCCESS_WITH_INFO))
			{
				SQLFreeConnect(hdbca);
				SQLFreeEnv(henva);
				return;
			}

			rca = SQLAllocStmt(hdbca, &hstmta);
			std::stringstream query;
			query << "UPDATE [Login] SET [Type] = 0 WHERE [UID] = '" << UID << "'";
			std::string runquery = query.str();
			const char *sql = runquery.c_str();
			rca = SQLExecDirect(hstmta, (unsigned char*)sql, SQL_NTS);
			if ((rca != SQL_SUCCESS) && (rca != SQL_SUCCESS_WITH_INFO))
			{
				SQLFreeStmt(hstmta, SQL_DROP);
				SQLDisconnect(hdbca);
				SQLFreeConnect(hdbca);
				SQLFreeEnv(henva);
				return;
			}

			SQLFreeStmt(hstmta, SQL_DROP);
			SQLDisconnect(hdbca);
			SQLFreeConnect(hdbca);
			SQLFreeEnv(henva);

			string line;

			ifstream fin;
			fin.open("./Database/HWIDBlock.txt");
			ofstream temp;
			temp.open("./Database/temp.txt");

			while (getline(fin, line))
			{
				int uidTemp = 0;
				char HWID[BUFSIZ], MAC[BUFSIZ], IP[BUFSIZ];
				if (sscanf(line.c_str(), "(hwidblock (uid %d)(hwid '%[a-z | A-Z | 0-9/<>|.,~*;`:!^+%&=?_-£#$€]')(mac '%[a-z | A-Z | 0-9/<>|.,~*;`:!^+%&=?_-£#$€]')(ip '%[a-z | A-Z | 0-9/<>|.,~*;`:!^+%&=?_-£#$€]'))", &uidTemp, &HWID, &MAC, &IP) == 4)
				{
					if (uidTemp == UID) {
						//blockLock.Enter();
						BlockList.erase(sha256(HWID));
						BlockList.erase(sha256(MAC));
						BlockList.erase(sha256(IP));
						//blockLock.Leave();
					}
					else
						temp << line << endl;
				}
			}

			temp.close();
			fin.close();
			remove("./Database/HWIDBlock.txt");
			rename("./Database/temp.txt", "./Database/HWIDBlock.txt");

			IPlayer.SystemMessage("Player successfully unblocked.", TEXTCOLOR_GREEN);
		}
		else {
			IPlayer.SystemMessage("Could not find player.", TEXTCOLOR_GREEN);
		}

		return;
	}

	CPlayer::ChatCommand(Player, command);
}