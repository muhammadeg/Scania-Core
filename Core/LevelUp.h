int __fastcall LevelUp(void *Player, void *edx)
{
	IChar IPlayer(Player);
	int result = 0;

	if (IPlayer.IsOnline()) {
		result = CPlayer::LevelUp(Player);
		
		int Stats = 0;

		int Level = IPlayer.GetLevel();
		if (Level >= 72 && Level < 76) Stats = 2;
		if (Level >= 76 && Level < 81) Stats = 3;
		if (Level >= 81 && Level < 86) Stats = 4;
		if (Level >= 86 && Level < 91) Stats = 5;
		if (Level >= 91 && Level < 96) Stats = 6;
		if (Level >= 96) Stats = 7;

		if (Stats)
			IPlayer.AddStatPoint(Stats);
	}

	if (IPlayer.IsOnline() && MLMRewards.count(IPlayer.GetLevel())) {
		CIOCriticalSection::Enter((struct _RTL_CRITICAL_SECTION *)((int)IPlayer.GetOffset() + 1308));
		int MLMActive = CPlayer::_MLMFind((int)IPlayer.GetOffset(), 2, 0);

		if (MLMActive) {
			int TeacherPID = *(DWORD *)(MLMActive + 4);
			CIOCriticalSection::Leave((struct _RTL_CRITICAL_SECTION *)((int)IPlayer.GetOffset() + 1308));
			std::vector<MLMReward> Rewards = MLMRewards.find(IPlayer.GetLevel())->second;

			TargetFind myTeacher(0, 1, TeacherPID);
			int Teacher = (int)myTeacher.getTarget();
			IChar ITeacher((void*)Teacher);
			std::string studentMessage = "Congratulations on achieving your new level as a student!";
			std::string teacherMessage = "Your student " + (std::string)IPlayer.GetName() + " has leveled up, here is your reward as a teacher!";
			for (int i = 0; i < (int)Rewards.size(); i++)
			{
				MLMReward reward = Rewards[i];
				if (reward.Type == 0 || reward.Type == 1 && (reward.Class == IPlayer.GetClass() || reward.Class == 5)) {
					IPlayer.GiveReward(reward.Index, reward.Prefix, reward.Amount, reward.Info, reward.Attack, reward.Magic, reward.Toa, reward.Upgrade, reward.Defense, reward.Evasion, reward.Endurance, studentMessage.c_str());
				}

				if (reward.Type == 0 || reward.Type == 2) {
					if (!ITeacher.IsOnline())
						insertOfflineReward(TeacherPID, reward.Index, reward.Amount, reward.Class, reward.Prefix, reward.Info, reward.Attack, reward.Magic, reward.Toa, reward.Upgrade, reward.Defense, reward.Evasion, reward.Endurance, 0, teacherMessage.c_str());
					else
						if (reward.Class == ITeacher.GetClass() || reward.Class == 5) {
							ITeacher.GiveReward(reward.Index, reward.Prefix, reward.Amount, reward.Info, reward.Attack, reward.Magic, reward.Toa, reward.Upgrade, reward.Defense, reward.Evasion, reward.Endurance, teacherMessage.c_str());
						}
				}
			}
		}
		else
			CIOCriticalSection::Leave((struct _RTL_CRITICAL_SECTION *)((int)IPlayer.GetOffset() + 1308));
	}

	if (IPlayer.IsOnline() && LevelReward.count(IPlayer.GetLevel()))
	{
		std::vector<ConfigLevelReward> lvlReward = LevelReward.find(IPlayer.GetLevel())->second;
		for (int i = 0; i < (int)lvlReward.size(); i++)
		{
			ConfigLevelReward reward = lvlReward[i];
			if (reward.Class == IPlayer.GetClass() || reward.Class == 5)
				IPlayer.GiveReward(reward.Index, reward.Prefix, reward.Amount, reward.Info, reward.Attack, reward.Magic, reward.Toa, reward.Upgrade, reward.Defense, reward.Evasion, reward.Endurance, reward.Msg.c_str());
		}
	}

	if (IPlayer.IsOnline() && !IPlayer.GetAdmin() && IPlayer.GetLevel() >= GZLvl)
		InterlockedExchange(&PlayerLevelNotice, (int)Player);

	if (IPlayer.IsOnline())
	{
		if (IPlayer.GetLevel() == 81)
			CChar::WriteInSight(IPlayer.GetOffset(),178,"db",IPlayer.GetID(),1);

		if (IPlayer.GetLevel() == 86)
			CChar::WriteInSight(IPlayer.GetOffset(),178,"db",IPlayer.GetID(),2);

		if (IPlayer.GetLevel() == 91)
			CChar::WriteInSight(IPlayer.GetOffset(),178,"db",IPlayer.GetID(),3);
	}

	if (IPlayer.IsOnline() && IPlayer.GetLevel() == 70)
	{
		IPlayer.IncreaseMaxHp(250);
		IPlayer.IncreaseMaxMp(100);
	}

	if (IPlayer.IsOnline() && IPlayer.GetLevel() == 75)
	{
		IPlayer.IncreaseMaxHp(300);
		IPlayer.IncreaseMaxMp(125);

		if (IPlayer.GetSpecialty() == 43 && IPlayer.GetClass() == 1)
			IPlayer.RemoveBuffIcon(0, 0, 1998, 221);
		else
			IPlayer.RemoveBuffIcon(0, 0, 1767, 220);
	}

	if (IPlayer.IsOnline() && IPlayer.GetLevel() == 80)
	{
		IPlayer.IncreaseMaxHp(350);
		IPlayer.IncreaseMaxMp(150);

		if (IPlayer.GetSpecialty() == 43 && IPlayer.GetClass() == 1)
			IPlayer.RemoveBuffIcon(0, 0, 3567, 406);
		else
			IPlayer.RemoveBuffIcon(0, 0, 3561, 400);
	}

	if (IPlayer.IsOnline() && IPlayer.GetLevel() == 85)
	{
		IPlayer.IncreaseMaxHp(550);
		IPlayer.IncreaseMaxMp(250);

		if (IPlayer.GetSpecialty() == 43 && IPlayer.GetClass() == 1)
			IPlayer.RemoveBuffIcon(0, 0, 3568, 407);
		else
			IPlayer.RemoveBuffIcon(0, 0, 3562, 401);
	}

	if (IPlayer.IsOnline() && IPlayer.GetLevel() == 90)
	{
		IPlayer.IncreaseMaxHp(950);
		IPlayer.IncreaseMaxMp(450);

		if (IPlayer.GetSpecialty() == 43 && IPlayer.GetClass() == 1)
			IPlayer.RemoveBuffIcon(0, 0, 3569, 408);
		else
			IPlayer.RemoveBuffIcon(0, 0, 3563, 402);
	}

	if (IPlayer.IsOnline() && IPlayer.GetLevel() == 95)
	{
		IPlayer.IncreaseMaxHp(1750);
		IPlayer.IncreaseMaxMp(850);

		if (IPlayer.GetSpecialty() == 43 && IPlayer.GetClass() == 1)
			IPlayer.RemoveBuffIcon(0, 0, 3570, 409);
		else
			IPlayer.RemoveBuffIcon(0, 0, 3564, 403);
	}

	if (IPlayer.IsOnline() && IPlayer.GetLevel() >= 70 && IPlayer.GetLevel() <= 74)
	{
		IPlayer.IncreaseMaxHp(6);
		IPlayer.IncreaseMaxMp(3);
	}

	if (IPlayer.IsOnline() && IPlayer.GetLevel() >= 75 && IPlayer.GetLevel() <= 79)
	{
		IPlayer.IncreaseMaxHp(12);
		IPlayer.IncreaseMaxMp(6);
	}

	if (IPlayer.IsOnline() && IPlayer.GetLevel() >= 80 && IPlayer.GetLevel() <= 84)
	{
		IPlayer.IncreaseMaxHp(18);
		IPlayer.IncreaseMaxMp(9);
	}

	if (IPlayer.IsOnline() && IPlayer.GetLevel() >= 85 && IPlayer.GetLevel() <= 89)
	{
		IPlayer.IncreaseMaxHp(24);
		IPlayer.IncreaseMaxMp(12);
	}

	if (IPlayer.IsOnline() && IPlayer.GetLevel() >= 90 && IPlayer.GetLevel() <= 94)
	{
		IPlayer.IncreaseMaxHp(30);
		IPlayer.IncreaseMaxMp(15);
	}

	if (IPlayer.IsOnline() && IPlayer.GetLevel() >= 95)
	{
		IPlayer.IncreaseMaxHp(36);
		IPlayer.IncreaseMaxMp(18);
	}

	if (PlayerStats.size() > 0 && PlayerStats.count((IPlayer.GetLevel() * 100) + (IPlayer.GetClass() * 1000) + (IPlayer.GetSpecialty() * 1000))) {
		IPlayer.IncreaseMaxHp(PlayerStats.find((IPlayer.GetLevel() * 100) + (IPlayer.GetClass() * 1000) + (IPlayer.GetSpecialty() * 1000))->second.HP);
		IPlayer.IncreaseMaxMp(PlayerStats.find((IPlayer.GetLevel() * 100) + (IPlayer.GetClass() * 1000) + (IPlayer.GetSpecialty() * 1000))->second.MP);
		IPlayer.AddAgi(PlayerStats.find((IPlayer.GetLevel() * 100) + (IPlayer.GetClass() * 1000) + (IPlayer.GetSpecialty() * 1000))->second.Agi);
		IPlayer.AddInt(PlayerStats.find((IPlayer.GetLevel() * 100) + (IPlayer.GetClass() * 1000) + (IPlayer.GetSpecialty() * 1000))->second.Int);
		IPlayer.AddWis(PlayerStats.find((IPlayer.GetLevel() * 100) + (IPlayer.GetClass() * 1000) + (IPlayer.GetSpecialty() * 1000))->second.Wis);
		IPlayer.AddEva(PlayerStats.find((IPlayer.GetLevel() * 100) + (IPlayer.GetClass() * 1000) + (IPlayer.GetSpecialty() * 1000))->second.Eva);
		IPlayer.AddOTP(PlayerStats.find((IPlayer.GetLevel() * 100) + (IPlayer.GetClass() * 1000) + (IPlayer.GetSpecialty() * 1000))->second.OTP);
		IPlayer.AddDef(PlayerStats.find((IPlayer.GetLevel() * 100) + (IPlayer.GetClass() * 1000) + (IPlayer.GetSpecialty() * 1000))->second.Def);
		IPlayer.AddStr(PlayerStats.find((IPlayer.GetLevel() * 100) + (IPlayer.GetClass() * 1000) + (IPlayer.GetSpecialty() * 1000))->second.Str);
		IPlayer.AddHp(PlayerStats.find((IPlayer.GetLevel() * 100) + (IPlayer.GetClass() * 1000) + (IPlayer.GetSpecialty() * 1000))->second.Hth);
		IPlayer.AddMinAttack(PlayerStats.find((IPlayer.GetLevel() * 100) + (IPlayer.GetClass() * 1000) + (IPlayer.GetSpecialty() * 1000))->second.ATK);
		IPlayer.AddMaxAttack(PlayerStats.find((IPlayer.GetLevel() * 100) + (IPlayer.GetClass() * 1000) + (IPlayer.GetSpecialty() * 1000))->second.ATK);
		IPlayer.AddAbsorb(PlayerStats.find((IPlayer.GetLevel() * 100) + (IPlayer.GetClass() * 1000) + (IPlayer.GetSpecialty() * 1000))->second.Absorb);
	}

	if (IPlayer.IsOnline() && IPlayer.GetClass() == 0 && IPlayer.GetLevel() >= 71 && IPlayer.GetLevel() < 101 && IPlayer.GetSpecialty() == 43)
		IPlayer.AddDef(5);

	return result;
}