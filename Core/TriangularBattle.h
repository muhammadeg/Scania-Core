int PullPlayer = 0;
int SetPlayer = 0;
int FailReturnPlayer = 0;
int FailReturnType = 0;
int TBRandomSize = 0;
int TBBuff = 0;

bool compareTeamByLevel(const int &a, const int &b)
{
	IChar IPlayerA((void*)a);
	IChar IPlayerB((void*)b);
	return IPlayerA.GetLevel() < IPlayerB.GetLevel();
}

void StartTriangularBattle() {
	if (!TriangularBattle::Active && !TriangularBattle::CDActive) {
		if (TBRegistration.size() >= TBPlayersMin) {
			TriangularBattle::Players.clear();

			std::vector<int> Team;
			for (auto x = TBRegistration.begin(); x != TBRegistration.end(); x++) {
				TargetFind myTarget(0, 1, *x);
				void *player = myTarget.getTarget();
				IChar IPlayer(player);
				if (IPlayer.IsOnline() && IPlayer.IsPVPValid() && !(SystemBlacklist.count(5) && SystemBlacklist.find(5)->second.count(IPlayer.GetPID())))
					Team.push_back((int)IPlayer.GetOffset());
			}

			std::sort(Team.begin(), Team.end(), compareTeamByLevel);

			int CurTeam = 1;
			for (int i = 0; i < Team.size(); i++) {
				IChar IPlayer((void*)Team[i]);
				IPlayer.CancelBuff(BuffNames::TriangularType);
				IPlayer.CancelBuff(BuffNames::TriangularState);

				IPlayer.SaveBuff(BuffNames::TriangularType, TBTime + TBCooldown + 10, CurTeam, 0, 0);
				IPlayer.SaveBuff(BuffNames::TriangularState, TBTime + TBCooldown + 10, 0x4000000 + (0x200000 << (CurTeam - 1)), 0, 0);
				TriangularBattle::Players.push_back(IPlayer.GetPID());

				IPlayer.BoxMsg("Triangular Battle Team selection has been made. You can now join your team.");

				if (CurTeam == 3)
					CurTeam = 0;

				CurTeam++;
			}

			TriangularBattle::CooldownTime = (int)time(0) + TBCooldown;
			TriangularBattle::CDActive = true;
			CPlayer::WriteAll(0xFE, "db", 172, 30);
		}
		else
			CPlayer::WriteAll(0xFF, "dsd", 247, "Triangular Battle could not start due to low amount of registered players.", 2);
	}
}

void ClearTBPlayer(IChar IPlayer) {
	if (IPlayer.GetBuffRemain(BuffNames::TriangularEmblemPull) > 2) {
		int TypePull = IPlayer.GetBuffValue(BuffNames::TriangularEmblemPull);

		if (TypePull == 1)
			TriangularBattle::HumanPulling = 0;
		if (TypePull == 2)
			TriangularBattle::DoggebiPulling = 0;
		if (TypePull == 3)
			TriangularBattle::DemonPulling = 0;

		CPlayer::Write(IPlayer.GetOffset(), 0xFE, "db", 171, 12);
		IPlayer.UpdateBuff(BuffNames::TriangularState, BuffNames::BuffTime, IPlayer.GetBuffValue(BuffNames::TriangularState) - 0x2000000);
		IPlayer.CancelBuff(BuffNames::TriangularEmblemPull);
	}

	if (IPlayer.GetBuffRemain(BuffNames::TriangularEmblemSet) > 2) {
		int TypeSet = IPlayer.GetBuffValue(BuffNames::TriangularEmblemSet);

		if (TypeSet == 1)
			TriangularBattle::HumanSetting = 0;
		if (TypeSet == 2)
			TriangularBattle::DoggebiSetting = 0;
		if (TypeSet == 3)
			TriangularBattle::DemonSetting = 0;

		IPlayer.UpdateBuff(BuffNames::TriangularState, BuffNames::BuffTime, IPlayer.GetBuffValue(BuffNames::TriangularState) - 0x1000000);
		CPlayer::Write(IPlayer.GetOffset(), 0xFE, "db", 171, 4);
		IPlayer.CancelBuff(BuffNames::TriangularEmblemSet);
	}
}

void PortTBPlayer(IChar IPlayer, int Team) {
	ClearTBPlayer(IPlayer);
	if (Team == 1)
		IPlayer.Teleport(TBMap, TBBlueX, TBBlueY, TBBlueZ);
	else if (Team == 2)
		IPlayer.Teleport(TBMap, TBRedX, TBRedY, TBRedZ);
	else if (Team == 3)
		IPlayer.Teleport(TBMap, TBYellowX, TBYellowY, TBYellowZ);
}

void PutBackToAlter(IChar IPlayer, int Dropped) {
	CPlayer::RemoveItem(IPlayer.GetOffset(), 27, 1941, 1);
	int TypePull = IPlayer.GetBuffValue(BuffNames::TriangularTime);
	FailReturnPlayer = (int)IPlayer.GetOffset();
	FailReturnType = TypePull;

	if (FailReturnType < 10 && Dropped)
		FailReturnType *= 10;

	if (TypePull >= 10)
		TypePull /= 10;

	if (TypePull == 1) {
		TriangularBattle::HumanScore++;
		CChar::WriteInSight(IPlayer.GetOffset(), 46, "dI", TriangularBattle::HumanNPCID, __int64(0x400 << TriangularBattle::HumanScore));
	}
	if (TypePull == 2) {
		TriangularBattle::DoggebiScore++;
		CChar::WriteInSight(IPlayer.GetOffset(), 46, "dI", TriangularBattle::DoggebiNPCID, __int64(0x400 << TriangularBattle::DoggebiScore));
	}
	if (TypePull == 3) {
		TriangularBattle::DemonScore++;
		CChar::WriteInSight(IPlayer.GetOffset(), 46, "dI", TriangularBattle::DemonNPCID, __int64(0x400 << TriangularBattle::DemonScore));
	}

	CChar::WriteInSight(IPlayer.GetOffset(), 0xFE, "ddd", 170, IPlayer.GetID(), 0);
	IPlayer.CancelBuff(BuffNames::TriangularTime);
}

void QuitTBPlayer(IChar IPlayer) {
	ClearTBPlayer(IPlayer);

	if (IPlayer.GetBuffValue(BuffNames::TriangularTime))
		PutBackToAlter(IPlayer, 1);

	TriangularBattle::QuitSize++;
}

void TBPlayerTick(IChar IPlayer) {
	if (IPlayer.IsOnline()) {
		if (TBBuff && IPlayer.IsBuff(TBBuff)) {
			int Value = IPlayer.GetBuffValue(TBBuff);
			if (TBBuff == BuffNames::SpontaneousCure)
				IPlayer.IncreaseHp(Value);

			if (IPlayer.GetBuffRemain(TBBuff) <= 1) {
				switch (TBBuff) {
				case BuffNames::ContractingSpace: {
					IPlayer.DecreaseMovingSpeed(120);
					break;
				}
				case BuffNames::ImprovingAttack: {
					IPlayer.RemoveMinAttack(Value);
					IPlayer.RemoveMaxAttack(Value);
					break;
				}
				case BuffNames::ImprovingDefense: {
					IPlayer.RemoveDef(Value);
					break;
				}
				case BuffNames::RecoveringHP: {
					IPlayer.DecreaseMaxHp(Value);
					break;
				}
				case BuffNames::Precision: {
					IPlayer.RemoveOTP(Value);
					break;
				}
				}
				IPlayer.CancelBuff(TBBuff);
			}
		}

		if (TriangularBattle::Active) {
			void* Player = IPlayer.GetOffset();
			if (IPlayer.IsBuff(BuffNames::TriangularType)) {
				CPlayer::Write((void*)Player, 0xFE, "dbd", 171, 26, TriangularBattle::Time - (int)time(0));
				CPlayer::Write((void*)Player, 0xFE, "dbbbb", 171, 19, TriangularBattle::HumanScore, TriangularBattle::DoggebiScore, TriangularBattle::DemonScore);

				int GState = IPlayer.GetBuffValue(BuffNames::TriangularState);
				int Type = IPlayer.GetBuffValue(BuffNames::TriangularType);

				if (IPlayer.GetMap() != TBMap)
					PortTBPlayer(IPlayer, Type);

				if (IPlayer.isDead()) {
					if (IPlayer.IsBuff(BuffNames::RevivalCheck)) {
						int TimeLeft = IPlayer.GetBuffRemain(BuffNames::RevivalCheck);
						if (TimeLeft <= 1) {
							PortTBPlayer(IPlayer, Type);
							IPlayer.Buff(24, 6, 40);
							IPlayer.RemoveBuffIcon(0, 0, 703, 34);
							CChar::AddMState(IPlayer.GetOffset(), 0, 2147483648);
							IPlayer.SetBuffIcon(6000, 0, 1793, 201);
						}
						else
							IPlayer.SystemMessage("[T-Battle] Reviving in " + Int2String(TimeLeft - 1) + "...", TEXTCOLOR_DARKGREEN);
					}
					else {
						IPlayer.SystemMessage("[T-Battle] Reviving in " + Int2String(10) + "...", TEXTCOLOR_DARKGREEN);
						IPlayer.Buff(BuffNames::RevivalCheck, 11, 0);
					}
				}

				if (IPlayer.IsBuff(BuffNames::TriangularEmblemSet) && IPlayer.GetBuffRemain(BuffNames::TriangularEmblemSet) <= 2 && CPlayer::RemoveItem(Player, 27, 1941, 1)) {
					IPlayer.UpdateBuff(BuffNames::TriangularState, BuffNames::BuffTime, GState - 0x1000000);
					SetPlayer = (int)Player;

					CPlayer::Write(Player, 0xFE, "dd", 171, 3);
					int NState = 0;

					if (Type == 1) {
						TriangularBattle::HumanSetting = 0;
						TriangularBattle::HumanScore++;
						CChar::WriteInSight(Player, 46, "dI", TriangularBattle::HumanNPCID, __int64(0x400 << TriangularBattle::HumanScore));
					}
					if (Type == 2) {
						TriangularBattle::DoggebiSetting = 0;
						TriangularBattle::DoggebiScore++;
						CChar::WriteInSight(Player, 46, "dI", TriangularBattle::DoggebiNPCID, __int64(0x400 << TriangularBattle::DoggebiScore));
					}
					if (Type == 3) {
						TriangularBattle::DemonSetting = 0;
						TriangularBattle::DemonScore++;
						CChar::WriteInSight(Player, 46, "dI", TriangularBattle::DemonNPCID, __int64(0x400 << TriangularBattle::DemonScore));
					}

					CChar::WriteInSight(IPlayer.GetOffset(), 0xFE, "ddd", 170, IPlayer.GetID(), 0);
					IPlayer.CancelBuff(BuffNames::TriangularEmblemSet);
					IPlayer.CancelBuff(BuffNames::TriangularTime);
				}
				else if (IPlayer.IsBuff(BuffNames::TriangularEmblemPull) && IPlayer.GetBuffRemain(BuffNames::TriangularEmblemPull) <= 2) {
					int TypePull = IPlayer.GetBuffValue(BuffNames::TriangularEmblemPull);

					PullPlayer = (int)Player;

					GState = IPlayer.GetBuffValue(BuffNames::TriangularState);
					int Type = IPlayer.GetBuffValue(BuffNames::TriangularType);
					if (TypePull == 1) {
						TriangularBattle::HumanPulling = 0;
						TriangularBattle::HumanScore--;
						CChar::WriteInSight(Player, 46, "dI", TriangularBattle::HumanNPCID, __int64(0x400 << TriangularBattle::HumanScore));
					}
					if (TypePull == 2) {
						TriangularBattle::DoggebiPulling = 0;
						TriangularBattle::DoggebiScore--;
						CChar::WriteInSight(Player, 46, "dI", TriangularBattle::DoggebiNPCID, __int64(0x400 << TriangularBattle::DoggebiScore));
					}
					if (TypePull == 3) {
						TriangularBattle::DemonPulling = 0;
						TriangularBattle::DemonScore--;
						CChar::WriteInSight(Player, 46, "dI", TriangularBattle::DemonNPCID, __int64(0x400 << TriangularBattle::DemonScore));
					}

					IPlayer.Buff(BuffNames::TriangularTime, EmblemExpire + 2, TypePull);
					IPlayer.UpdateBuff(BuffNames::TriangularState, BuffNames::BuffTime, GState - 0x2000000);
					CPlayer::Write(Player, 0xFE, "dd", 171, 11);
					CItem::InsertItem((int)Player, 27, 1941, 256, 1, -1);

					int Item = CPlayer::FindItem(Player, 1941, 1);
					if (Item)
						IPlayer.UpdateBuff(BuffNames::TriangularItemIID, BuffNames::BuffTime, *(DWORD*)(Item + 36));

					IPlayer.CancelBuff(BuffNames::TriangularEmblemPull);
				}

				if (IPlayer.IsBuff(BuffNames::TriangularTime)) {
					int LeftTime = IPlayer.GetBuffRemain(BuffNames::TriangularTime);
					if (LeftTime <= 2) {
						ClearTBPlayer(IPlayer);
						PutBackToAlter(IPlayer, 0);
					}
					else {
						CPlayer::Write(Player, 0xFF, "ddd", 230, IPlayer.GetBuffValue(BuffNames::TriangularItemIID), (LeftTime - 2) * 1000);
						CChar::WriteInSight((void*)Player, 0xFE, "ddd", 170, IPlayer.GetID(), 1);
					}
				}
			}
		}

		if (IPlayer.GetMap() == TBMap && !IPlayer.IsBuff(BuffNames::TriangularType)) {
			CChar::WriteInSight(IPlayer.GetOffset(), 0xFE, "ddd", 170, IPlayer.GetID(), 0);
			IPlayer.RemoveSetBlue();
			CChar::WriteInSight(IPlayer.GetOffset(), 145, "dI", IPlayer.GetID(), __int64(0));
			IPlayer.Teleport(0, TBBackX, TBBackY, TBBackZ);
		}
	}
}

void TBOnTimer() {
	if (TriangularBattle::CDActive) {
		if (TriangularBattle::CooldownTime <= (int)time(0)) {
			TriangularBattle::CDActive = false;
			TriangularBattle::CooldownTime = 0;
			TriangularBattle::QuitSize = 0; 
			
			PullPlayer = 0;
			SetPlayer = 0;
			FailReturnPlayer = 0;
			FailReturnType = 0;
			TBRandomSize = 0;
			TBBuff = 0;

			TriangularBattle::HumanScore = 1;
			TriangularBattle::DoggebiScore = 1;
			TriangularBattle::DemonScore = 1;

			CPlayer::WriteInMap(TBMap, 46, "dI", TriangularBattle::HumanNPCID, __int64(0x400 << TriangularBattle::HumanScore));
			CPlayer::WriteInMap(TBMap, 46, "dI", TriangularBattle::DoggebiNPCID, __int64(0x400 << TriangularBattle::HumanScore));
			CPlayer::WriteInMap(TBMap, 46, "dI", TriangularBattle::DemonNPCID, __int64(0x400 << TriangularBattle::HumanScore));

			TriangularBattle::HumanPulling = 0;
			TriangularBattle::DoggebiPulling = 0;
			TriangularBattle::DemonPulling = 0;

			TriangularBattle::HumanSetting = 0;
			TriangularBattle::DoggebiSetting = 0;
			TriangularBattle::DemonSetting = 0; 
			
			vector< int >::iterator it = TriangularBattle::Players.begin();
			while (it != TriangularBattle::Players.end()) {
				int PID = *it;
				TargetFind myTarget(0, 1, PID);
				int Player = (int)myTarget.getTarget();
				IChar IPlayer((void*)Player);
				if (IPlayer.GetMap() != TBMap) {
					if (IPlayer.IsOnline()) {
						IPlayer.RemoveSavedBuff(BuffNames::TriangularType);
						IPlayer.RemoveSavedBuff(BuffNames::TriangularState);
						IPlayer.BoxMsg("You can not participate to Triangular Battle since you did not join the fight.");
					}
					else {
						CDBSocket::Write(95, "ddddddd", 2, PID, BuffNames::TriangularType, 0, 0, 0, 0);
						CDBSocket::Write(95, "ddddddd", 2, PID, BuffNames::TriangularState, 0, 0, 0, 0);
					}
					it = TriangularBattle::Players.erase(it);
				}
				else {
					if (IPlayer.IsOnline()) {
						for (int i = 0; i < 180; i++) {
							if (!CPlayer::RemoveItem((void*)Player, 27, 1941, 1))
								break;
						}
					}
					++it;
				}
			}

			TriangularBattle::QuitSize = 0;
			TriangularBattle::Time = (int)time(0) + TBTime;
			TriangularBattle::BuffTime = (int)time(0) + TBBuffEach;

			CPlayer::WriteInMap(TBMap, 0xFE, "dd", 172, 12);
			TBRegistration.clear();
			TriangularBattle::Active = true;
		}
		else {
			int LeftTime = TriangularBattle::CooldownTime - (int)time(0);
			if (LeftTime > 0) {
				if (LeftTime >= 60) {
					if (!(LeftTime % 60))
						CPlayer::WriteInMap(TBMap, 0xFE, "dbd", 172, 10, LeftTime / 60);
				}
				else
					if (!(LeftTime % 10) || LeftTime <= 5)
						CPlayer::WriteInMap(TBMap, 0xFE, "dbd", 172, 11, LeftTime);
			}
		}
	}

	if (TriangularBattle::Active) {
		if (PullPlayer) {
			IChar IPlayer((void*)PullPlayer);
			CPlayer::WriteInMap(TBMap, 0xFE, "dbsbb", 171, 18, IPlayer.GetName(), IPlayer.GetBuffValue(BuffNames::TriangularType), 0);
			PullPlayer = 0;
		}

		if (SetPlayer) {
			IChar IPlayer((void*)SetPlayer);
			CPlayer::WriteInMap(TBMap, 0xFE, "dbsbb", 171, 9, IPlayer.GetName(), IPlayer.GetBuffValue(BuffNames::TriangularType), 0);
			SetPlayer = 0;
		}

		if (FailReturnPlayer) {
			IChar IPlayer((void*)FailReturnPlayer);
			if (FailReturnType >= 10) {
				FailReturnType /= 10;
				CPlayer::WriteInMap(TBMap, 0xFE, "dbb", 171, 25, FailReturnType);
			}
			else
				CPlayer::WriteInMap(TBMap, 0xFE, "dbsbb", 171, 24, IPlayer.GetName(), IPlayer.GetBuffValue(BuffNames::TriangularType), FailReturnType);

			FailReturnPlayer = 0;
		}

		if (TriangularBattle::BuffTime <= (int)time(0)) {
			TriangularBattle::BuffTime = (int)time(0) + TBBuffEach;
			int i = 0;
			int BuffedPlayers = 0;
			while (BuffedPlayers < TBRandomSize && i < TriangularBattle::Players.size()) {
				int PID = TriangularBattle::Players[i];
				TargetFind myTarget(0, 1, PID);
				int Player = (int)myTarget.getTarget();
				IChar IPlayer((void*)Player);
				if (IPlayer.IsOnline() && !IPlayer.IsBuff(TBBuff) && IPlayer.GetBuffValue(BuffNames::TriangularType)) {
					if (TBBuff == BuffNames::Recovery)
						IPlayer.IncreaseHp(IPlayer.GetMaxHp());
					else
						if (TBBuff == BuffNames::TeleportBuff && !IPlayer.IsBuff(BuffNames::TriangularEmblemSet) && !IPlayer.IsBuff(BuffNames::TriangularEmblemPull))
							PortTBPlayer(IPlayer, CTools::Rate(1, 3));
						else {
							int SBKey = 363 + (TBBuff - (TBBuff >= BuffNames::Unkillableness ? BuffNames::ImprovingAttack : BuffNames::ContractingSpace));
							int SBName = 3400 + (TBBuff - BuffNames::ContractingSpace);

							int Time = 30;
							if (TBBuff == BuffNames::SpontaneousCure || TBBuff == BuffNames::Unkillableness || TBBuff == BuffNames::Precision)
								Time = 20;

							int Value = 0;
							switch (TBBuff) {
							case BuffNames::ContractingSpace: {
								IPlayer.IncreaseMovingSpeed(120);
								break;
							}
							case BuffNames::ImprovingAttack: {
								if (IPlayer.GetClass() == 1 || IPlayer.GetClass() == 4)
									Value = IPlayer.GetMinMagAttack();
								else
									Value = IPlayer.GetMinPhyAttack();

								IPlayer.AddMinAttack(Value);
								IPlayer.AddMaxAttack(Value);
								break;
							}
							case BuffNames::ImprovingDefense: {
								Value = IPlayer.GetDef();
								IPlayer.AddDef(Value);
								break;
							}
							case BuffNames::RecoveringHP: {
								Value = IPlayer.GetMaxHp();
								IPlayer.IncreaseMaxHp(Value);
								IPlayer.IncreaseHp(Value);
								break;
							}
							case BuffNames::SpontaneousCure: {
								Value = (IPlayer.GetMaxHp() * 10 / 100);
								break;
							}
							case BuffNames::Precision: {
								Value = IPlayer.GetOTP();
								IPlayer.AddOTP(Value);
								break;
							}
							}
							IPlayer.Buff(TBBuff, Time + 1, Value);

							IPlayer.SetBuffIcon((Time - 1) * 1000, -1, SBName, SBKey);
						}
						BuffedPlayers++;
				}
				i++;
			}
			TBRandomSize = 0;
		}
		else
			if ((TriangularBattle::BuffTime - 5) <= (int)time(0) && !TBRandomSize) {
				TBRandomSize = CTools::Rate(1, (TriangularBattle::Players.size() - TriangularBattle::QuitSize));
				TBBuff = CTools::Rate(BuffNames::ContractingSpace, BuffNames::TeleportBuff);
				srand(time(0));
				std::random_shuffle(TriangularBattle::Players.begin(), TriangularBattle::Players.end());
				CPlayer::WriteInMap(TBMap, 0xFE, "dbbbb", 171, 28, TBRandomSize, (TBBuff - BuffNames::ContractingSpace) + 1, TriangularBattle::BuffTime - (int)time(0));
			}

		if (TriangularBattle::Time < (int)time(0)) {
			CPlayer::WriteInMap(TBMap, 0xFE, "db", 172, 13);

			int TeamScores[3] = { TriangularBattle::HumanScore, TriangularBattle::DoggebiScore, TriangularBattle::DemonScore };

			for (int i = 0; i < TriangularBattle::Players.size(); i++) {
				int PID = TriangularBattle::Players[i];
				TargetFind myTarget(0, 1, PID);
				int Player = (int)myTarget.getTarget();
				IChar IPlayer((void*)Player);
				if (IPlayer.IsOnline() && IPlayer.GetMap() == TBMap) {
					int Team = IPlayer.GetBuffValue(BuffNames::TriangularType);
					if (Team) {
						int Score = TeamScores[Team - 1];
						switch (Score) {
						case 0: IPlayer.systemReward(TBReward0); break;
						case 1: IPlayer.systemReward(TBReward1); break;
						case 2: IPlayer.systemReward(TBReward2); break;
						case 3: IPlayer.systemReward(TBReward3); break;
						}
					}
				}
			}

			TriangularBattle::Active = false;
			TriangularBattle::Time = 0;
			TriangularBattle::CDActive = false;
		}
	}
}


void __fastcall NPCSendCreate(int Npc, void *edx, int Player, int Argument)
{
	CNPC::SendCreate(Npc, Player, Argument);

	if (TriangularBattle::Active) {
		int ID = (*(DWORD*)(Npc + 448));

		if (ID == 729)
			CPlayer::Write((void*)Player, 46, "dI", (*(DWORD*)(Npc + 28)), __int64(0x400 << TriangularBattle::HumanScore));
		
		if (ID == 730)
			CPlayer::Write((void*)Player, 46, "dI", (*(DWORD*)(Npc + 28)), __int64(0x400 << TriangularBattle::DoggebiScore));
		
		if (ID == 731)
			CPlayer::Write((void*)Player, 46, "dI", (*(DWORD*)(Npc + 28)), __int64(0x400 << TriangularBattle::DemonScore));
	}
}
