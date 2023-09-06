void __fastcall Calls(void *pSkill, void *edx, int Player, int pPacket, int pPos)
{
	IChar IPlayer((void*)Player);

	if (IPlayer.IsValid())
	{
		ISkill ISkill(pSkill);
		int nSkillGrade = ISkill.GetGrade();
		int Action = 0, Check = 0;
		Check = (*(int (__thiscall **)(void *, int))(*(DWORD*)pSkill + 80))(pSkill, Player);

		if (nSkillGrade && Check && IPlayer.IsValid())
		{
			int SecondCall = IPlayer.GetSecondCall();
			if (IPlayer.IsParty())
			{
				void *Party = (void*)CParty::FindParty(IPlayer.GetPartyID());

				if (Party)
				{
					if (IPlayer.GetSpecialty() == 43 && IPlayer.IsValid())
					{
						if (!*(DWORD*)(Player + 584) && SecondCall)
						{
							CChar::CancelAllBuff(IPlayer.GetOffset(), SecondCall);
							IPlayer.SetSecondCall(0);
							if (Check)
								CBuff::Release((void*)Check, 1);
							CIOObject::Release(Party);
							return;
						}

						if (SecondCall && SecondCall == *(DWORD*)(Check + 4)) {
							if (Check)
								CBuff::Release((void*)Check, 1);
							CIOObject::Release(Party);
							return;
						}

						if (*(DWORD*)(Player + 584) && SecondCall)
						{
							for (int i = CParty::GetPlayerList(Party); i; i = CBaseList::Pop((void*)i))
							{
								int Members = *(DWORD*)((void*)i);
								IChar IBuffed((void*)Members);

								if (CChar::IsNormal(Members) && IPlayer.IsValid())
								{
									CChar::CancelAllBuff((void*)Members, *(DWORD*)(Check + 4));

									if (Members != Player && *(DWORD*)(Members + 584) == *(DWORD*)(Check + 4))
										*(DWORD*)(Members + 584) = 0;

									if (Members != Player && IBuffed.GetSecondCall() == *(DWORD*)(Check + 4))
										IBuffed.SetSecondCall(0);

									if (*(DWORD*)(Player + 584))
										CChar::CancelAllBuff((void*)Members, *(DWORD*)(Player + 584));

									if (CChar::GetRange(Player + 332, Members + 332) <= CBuffRange)
									{
										if (Members != Player)
											IBuffed.UpdateBuff(BuffNames::CallBuffer, BuffNames::BuffTime, (int)Player);

										int Buff = (*(int (__thiscall **)(DWORD))(*(DWORD *)Check + 20))(Check);
										(*(void (__thiscall **)(DWORD, DWORD))(*(DWORD*)Members + 180))(Members, Buff);
									}
								}
							}

							*(DWORD*)(Player + 584) = SecondCall;
							IPlayer.SetSecondCall(*(DWORD*)(Check + 4));
						} else if (*(DWORD*)(Player + 584) && !SecondCall)
						{
							if (*(DWORD*)(Player + 584) == *(DWORD*)(Check + 4)) {
								if (Check)
									CBuff::Release((void*)Check, 1);
								CIOObject::Release(Party);
								return;
							}
							for (int i = CParty::GetPlayerList(Party); i; i = CBaseList::Pop((void*)i))
							{
								int Members = *(DWORD*)((void*)i);

								IChar IBuffed((void*)Members);
								if (CChar::IsNormal(Members) && IPlayer.IsValid())
								{
									CChar::CancelAllBuff((void*)Members, *(DWORD*)(Check + 4));

									if (Members != Player && *(DWORD*)(Members + 584) == *(DWORD*)(Check + 4))
										*(DWORD*)(Members + 584) = 0;

									if (Members != Player && IBuffed.GetSecondCall() == *(DWORD*)(Check + 4))
										IBuffed.SetSecondCall(0);

									if (CChar::GetRange(Player + 332, Members + 332) <= CBuffRange)
									{
										if (Members != Player)
											IBuffed.UpdateBuff(BuffNames::CallBuffer, BuffNames::BuffTime, (int)Player);

										int Buff = (*(int (__thiscall **)(DWORD))(*(DWORD *)Check + 20))(Check);
										(*(void (__thiscall **)(DWORD, DWORD))(*(DWORD*)Members + 180))(Members, Buff);
									}
								}
							}

							IPlayer.SetSecondCall(*(DWORD*)(Check + 4));
						} else if (!*(DWORD*)(Player + 584) && !SecondCall)
						{
							for (int i = CParty::GetPlayerList(Party); i; i = CBaseList::Pop((void*)i))
							{
								int Members = *(DWORD*)((void*)i);

								IChar IBuffed((void*)Members);
								if (CChar::IsNormal(Members) && IPlayer.IsValid())
								{
									CChar::CancelAllBuff((void*)Members, *(DWORD*)(Check + 4));

									if (Members != Player && *(DWORD*)(Members + 584) == *(DWORD*)(Check + 4))
										*(DWORD*)(Members + 584) = 0;

									if (Members != Player && IBuffed.GetSecondCall() == *(DWORD*)(Check + 4))
										IBuffed.SetSecondCall(0);

									if (CChar::GetRange(Player + 332, Members + 332) <= CBuffRange)
									{
										if (Members != Player)
											IBuffed.UpdateBuff(BuffNames::CallBuffer, BuffNames::BuffTime, (int)Player);

										int Buff = (*(int (__thiscall **)(DWORD))(*(DWORD *)Check + 20))(Check);
										(*(void (__thiscall **)(DWORD, DWORD))(*(DWORD*)Members + 180))(Members, Buff);
									}
								}
							}

							*(DWORD*)(Player + 584) = *(DWORD*)(Check + 4);
						}
					} else {
						for (int i = CParty::GetPlayerList(Party); i; i = CBaseList::Pop((void*)i))
						{
							int Members = *(DWORD*)((void*)i);

							IChar IBuffed((void*)Members);
							if (CChar::IsNormal(Members) && IPlayer.IsValid())
							{
								CChar::CancelAllBuff((void*)Members, *(DWORD*)(Check + 4));

								if (Members != Player && *(DWORD*)(Members + 584) == *(DWORD*)(Check + 4))
									*(DWORD*)(Members + 584) = 0;

								if (Members != Player && IBuffed.GetSecondCall() == *(DWORD*)(Check + 4))
									IBuffed.SetSecondCall(0);

								if (*(DWORD*)(Player + 584))
									CChar::CancelAllBuff((void*)Members, *(DWORD*)(Player + 584));

								if (CChar::GetRange(Player + 332, Members + 332) <= CBuffRange)
								{
									if (Members != Player)
										IBuffed.UpdateBuff(BuffNames::CallBuffer, BuffNames::BuffTime, (int)Player);

									int Buff = (*(int (__thiscall **)(DWORD))(*(DWORD *)Check + 20))(Check);
									(*(void (__thiscall **)(DWORD, DWORD))(*(DWORD*)Members + 180))(Members, Buff);
								}
							}
						}

						*(DWORD*)(Player + 584) = *(DWORD*)(Check + 4);
					}
					if (Check)
						CBuff::Release((void*)Check, 1);
					CIOObject::Release(Party);
				}
			} else {
				if (IPlayer.GetSpecialty() == 43)
				{
					if (!*(DWORD*)(Player + 584) && SecondCall)
					{
						CChar::CancelAllBuff(IPlayer.GetOffset(), SecondCall);
						IPlayer.SetSecondCall(0);
						if (Check)
							CBuff::Release((void*)Check, 1);
						return;
					}

					if (SecondCall && SecondCall == *(DWORD*)(Check + 4)) {
						if (Check)
							CBuff::Release((void*)Check, 1);
						return;
					}

					if (*(DWORD*)(Player + 584) && SecondCall)
					{
						CChar::CancelAllBuff(IPlayer.GetOffset(), *(DWORD*)(Player + 584));
						*(DWORD*)(Player + 584) = SecondCall;
						(*(void (__thiscall **)(int, int))(*(DWORD*)Player + 180))(Player, Check);
						IPlayer.SetSecondCall(*(DWORD*)(Check + 4));
					} else if (*(DWORD*)(Player + 584) && !SecondCall)
					{
						if (*(DWORD*)(Player + 584) == *(DWORD*)(Check + 4)) {
							if (Check)
								CBuff::Release((void*)Check, 1);
							return;
						}

						(*(void (__thiscall **)(int, int))(*(DWORD*)Player + 180))(Player, Check);
						IPlayer.SetSecondCall(*(DWORD*)(Check + 4));
					} else if (!*(DWORD*)(Player + 584) && !SecondCall)
					{
						(*(void (__thiscall **)(int, int))(*(DWORD*)Player + 180))(Player, Check);
						*(DWORD*)(Player + 584) = *(DWORD*)(Check + 4);
					}
				} else {
					if (*(DWORD*)(Player + 584))
						CChar::CancelAllBuff(IPlayer.GetOffset(), *(DWORD*)(Player + 584));

					(*(void (__thiscall **)(int, int))(*(DWORD*)Player + 180))(Player, Check);
					*(DWORD*)(Player + 584) = *(DWORD*)(Check + 4);
				}
			}

			IPlayer._ShowBattleAnimation(IPlayer,ISkill.GetIndex());
		}
	}
}