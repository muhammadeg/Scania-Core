void ContinuesSkill(void *Pack)
{
	while (true)
	{
		CIOCriticalSection::Enter((void*)0x004e2078);
		CIOCriticalSection::Enter((void*)0x004e2098);
		CLink::MoveTo((void*)0x004e200c, (int)0x004e2004);
		CIOCriticalSection::Leave((void*)0x004e2098);
		for (DWORD a = *(DWORD*)0x004E2004; a != 0x004E2004; a = *(DWORD*)a)
		{
			if ((void*)(a - 428))
			{
				IChar IPlayer((void*)(a - 428));

				int PlayerBRefresh = IPlayer.GetRefreshCheck();
				if (!PlayerBRefresh)
					IPlayer.SetRefreshCheck(GetTickCount() + 990);

				if (PlayerBRefresh <= GetTickCount()) {
					CChar::RefreshBuff((int)IPlayer.GetOffset());
					IPlayer.SetRefreshCheck(GetTickCount() + 990);
				}

				if (pollAsk.HTML && !CChar::IsGState((int)IPlayer.GetOffset(), 32)) {
					IPlayer.OpenHTML(pollAsk.HTML);
					IPlayer.BoxMsg(pollAsk.Question);
				}

				if (IPlayer.isContinueSkill())
				{
					int RuptureContinueSkillPlayerSkillID = IPlayer.GetProperty(PlayerProperty::RuptureContinueSkillPlayerSkillID);
					int FarContinueSkillPlayerSkillID = IPlayer.GetProperty(PlayerProperty::FarContinueSkillPlayerSkillID);
					int ContinueSkillPlayerSkillID = IPlayer.GetProperty(PlayerProperty::ContinueSkillPlayerSkillID);
					int ContinueSkillPlayerSkillDelay = IPlayer.GetProperty(PlayerProperty::ContinueSkillPlayerSkillDelay);
					int FarContinueSkillPlayerSkillDelay = IPlayer.GetProperty(PlayerProperty::FarContinueSkillPlayerSkillDelay);
					int ContinueSkillPlayerSkillCount = IPlayer.GetProperty(PlayerProperty::ContinueSkillPlayerSkillCount);
					int FarContinueSkillPlayerSkillCount = IPlayer.GetProperty(PlayerProperty::FarContinueSkillPlayerSkillCount);
					int RuptureContinueSkillPlayerSkillDelay = IPlayer.GetProperty(PlayerProperty::RuptureContinueSkillPlayerSkillDelay);
					int RuptureContinueSkillPlayerSkillCount = IPlayer.GetProperty(PlayerProperty::RuptureContinueSkillPlayerSkillCount);
					
					if (ContinueSkillPlayerSkillID && IPlayer.GetClass() == 3 && IPlayer.IsBuff(329))
						ResetContinueSkill(IPlayer);

					if (RuptureContinueSkillPlayerSkillID && CChar::IsGState((int)IPlayer.GetOffset(), 2) && IPlayer.GetClass() == 3)
						ResetRuptureContinueSkill(IPlayer);

					if (FarContinueSkillPlayerSkillID && CChar::IsGState((int)IPlayer.GetOffset(), 2))
						ResetFarContinueSkill(IPlayer);

					if (ContinueSkillPlayerSkillID && CChar::IsGState((int)IPlayer.GetOffset(), 2))
						ResetContinueSkill(IPlayer);

					if (RuptureContinueSkillPlayerSkillID == 17 && RuptureContinueSkillPlayerSkillCount && GetTickCount() >= RuptureContinueSkillPlayerSkillDelay && IPlayer.GetClass() == 3)
						ContinueRupture(IPlayer);

					if (FarContinueSkillPlayerSkillID && FarContinueSkillPlayerSkillCount)
					{
						if (IPlayer.GetClass() == 1 && FarContinueSkillPlayerSkillID == 76 && GetTickCount() >= FarContinueSkillPlayerSkillDelay)
							CounterDamage(IPlayer);

						if (IPlayer.GetClass() == 3 && FarContinueSkillPlayerSkillID == 23 && GetTickCount() >= FarContinueSkillPlayerSkillDelay)
							ContinueTwinBladeStrike(IPlayer);

						if (IPlayer.GetClass() == 3 && FarContinueSkillPlayerSkillID == 14 && GetTickCount() >= FarContinueSkillPlayerSkillDelay)
							ContinueFatalWound(IPlayer);
					}

					if (ContinueSkillPlayerSkillID && ContinueSkillPlayerSkillCount)
					{
						if (IPlayer.GetClass() == 0 && ContinueSkillPlayerSkillID == 43 && GetTickCount() >= ContinueSkillPlayerSkillDelay)
							ContinueSwordDance(IPlayer);

						if (IPlayer.GetClass() == 1 && ContinueSkillPlayerSkillID == 65 && GetTickCount() >= ContinueSkillPlayerSkillDelay)
							ContinueFlameInjection(IPlayer);

						if (IPlayer.GetClass() == 1 && ContinueSkillPlayerSkillID == 66 && GetTickCount() >= ContinueSkillPlayerSkillDelay)
							ContinueIcicle(IPlayer);

						if (IPlayer.GetClass() == 1 && ContinueSkillPlayerSkillID == 75 && GetTickCount() >= ContinueSkillPlayerSkillDelay)
							ContinueThunderbolt(IPlayer);

						if (IPlayer.GetClass() == 2 && ContinueSkillPlayerSkillID == 49 && GetTickCount() >= ContinueSkillPlayerSkillDelay)
							ContinueArrowExplosion(IPlayer);

						if (IPlayer.GetClass() == 2 && ContinueSkillPlayerSkillID == 47 && GetTickCount() >= ContinueSkillPlayerSkillDelay)
							ContinueArrowRain(IPlayer);

						if (IPlayer.GetClass() == 3 && ContinueSkillPlayerSkillID == 36 && GetTickCount() >= ContinueSkillPlayerSkillDelay)
							ContinueSpinBlade(IPlayer);

						if (IPlayer.GetClass() == 3 && ContinueSkillPlayerSkillID == 28 && GetTickCount() >= ContinueSkillPlayerSkillDelay)
							ContinueLightningSlash(IPlayer);

						if (ContinueSkillPlayerSkillID == 111 && GetTickCount() >= ContinueSkillPlayerSkillDelay)
							ContinueZilPoong(IPlayer);

						if (ContinueSkillPlayerSkillID == 114 && GetTickCount() >= ContinueSkillPlayerSkillDelay)
							ContinueWhirlwindFeather(IPlayer);

						if (ContinueSkillPlayerSkillID == 116 && GetTickCount() >= ContinueSkillPlayerSkillDelay)
							ContinueEggThunderbolt(IPlayer);
					}
				}
			}
		}
		CIOCriticalSection::Leave((void*)0x004e2078);
		pollAsk.HTML = 0;
		Sleep(120);
	}
}