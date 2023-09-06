namespace Panther {
	enum { G1 = 65, G2, G3, G4, EarthThorn = 107, ShadowCanine, Adamant, BloodSeduction = 115 };
}

namespace Tiger {
	enum { G1 = 1, G2, G3, G4, HardHit = 104, Destruction, Rage, RevolveAttack = 113 };
}

namespace Bird {
	enum { G1 = 97, G2, G3, G4, LightningWave = 101, IcyStorm, Phoenix, ThunderBolt = 116 };
}

namespace Eagle {
	enum { G1 = 129, G2, G3, G4, HighClassHide = 110, ZilPoong, ShinRhoe, WhirlwindFeather = 114 };
}

void __fastcall ExecuteTransformSkill(void *pSkill, void* edx, signed int SkillID, int pPacket, int pPos)
{
	ISkill Skill(pSkill);
	IChar IPlayer(Skill.GetPlayer());
	DWORD CdTime = 0, CooldownCheck = 0, DelayTime = 0;
	bool Ret = false;
	if (IPlayer.IsValid() && CChar::IsGState((int)IPlayer.GetOffset(),512))
	{
		//*CHECKS*//
		if (IPlayer.GetTransformGrade() == Panther::G1)
			if (SkillID == Panther::EarthThorn)
				Ret = true;

		if (IPlayer.GetTransformGrade() == Panther::G2)
			if (SkillID == Panther::EarthThorn || SkillID == Panther::ShadowCanine)
				Ret = true;

		if (IPlayer.GetTransformGrade() == Panther::G3)
			if (SkillID == Panther::EarthThorn || SkillID == Panther::ShadowCanine || SkillID == Panther::Adamant)
				Ret = true;

		if (IPlayer.GetTransformGrade() == Panther::G4)
			if (SkillID == Panther::EarthThorn || SkillID == Panther::ShadowCanine || SkillID == Panther::Adamant || SkillID == Panther::BloodSeduction)
				Ret = true;

		/* Tiger Skill*/

		if (IPlayer.GetTransformGrade() == Tiger::G1)
			if (SkillID == Tiger::HardHit)
				Ret = true;

		if (IPlayer.GetTransformGrade() == Tiger::G2)
			if (SkillID == Tiger::HardHit || SkillID == Tiger::Destruction)
				Ret = true;

		if (IPlayer.GetTransformGrade() == Tiger::G3)
			if (SkillID == Tiger::HardHit || SkillID == Tiger::Destruction || SkillID == Tiger::Rage)
				Ret = true;

		if (IPlayer.GetTransformGrade() == Tiger::G4)
			if (SkillID == Tiger::HardHit || SkillID == Tiger::Destruction || SkillID == Tiger::Rage || SkillID == Tiger::RevolveAttack)
				Ret = true;

		/* Bird Skills */

		if (IPlayer.GetTransformGrade() == Bird::G1)
			if (SkillID == Bird::LightningWave)
				Ret = true;

		if (IPlayer.GetTransformGrade() == Bird::G2)
			if (SkillID == Bird::LightningWave || SkillID == Bird::IcyStorm)
				Ret = true;

		if (IPlayer.GetTransformGrade() == Bird::G3)
			if (SkillID == Bird::LightningWave || SkillID == Bird::IcyStorm || SkillID == Bird::Phoenix)
				Ret = true;

		if (IPlayer.GetTransformGrade() == Bird::G4)
			if (SkillID == Bird::LightningWave || SkillID == Bird::IcyStorm || SkillID == Bird::Phoenix || SkillID == Bird::ThunderBolt)
				Ret = true;

		/* Eagle */
		if (IPlayer.GetTransformGrade() == Eagle::G1)
			if (SkillID == Eagle::HighClassHide)
				Ret = true;

		if (IPlayer.GetTransformGrade() == Eagle::G2)
			if (SkillID == Eagle::HighClassHide || SkillID == Eagle::ZilPoong)
				Ret = true;
		 
		if (IPlayer.GetTransformGrade() == Eagle::G3)
			if (SkillID == Eagle::HighClassHide || SkillID == Eagle::ZilPoong || SkillID == Eagle::ShinRhoe)
				Ret = true;

		if (IPlayer.GetTransformGrade() == Eagle::G4)
			if (SkillID == Eagle::HighClassHide || SkillID == Eagle::ZilPoong || SkillID == Eagle::ShinRhoe || SkillID == Eagle::WhirlwindFeather)
				Ret = true;
		 
		if (!Ret) {
			IPlayer.SystemMessage("Invalid egg skill usage!", TEXTCOLOR_RED);
			return;
		}
		//*ENDCHECKS*//

		if (skillDebug == 2 || skillDebug == 3) {
			std::string Datoe = "./Debugger/Skill/EGGSKILL_" + Time::GetDay() + "_" + Time::GetMonth() + "_" + Time::GetYear() + "_" + Time::GetHour() + "." + Time::GetMinute() + ".txt";
			std::fstream CHLOG;
			CHLOG.open(Datoe, std::fstream::in | std::fstream::out | std::fstream::app);
			CHLOG << Time::GetTime() << " " << IPlayer.GetName() << ": " << SkillID << std::endl;
			CHLOG.close();
		}

		if (DelaySpam) {
			if (IPlayer.GetBuffValue(BuffNames::SpamSkillID) != SkillID && IPlayer.GetBuffValue(BuffNames::SpamSkillTime) >= GetTickCount()) {
				IPlayer.SystemMessage("You need to wait " + Int2String(ceil(DelaySpam)) + " seconds between the execution of different skills.", TEXTCOLOR_INFOMSG);
				return;
			}
			else {
				IPlayer.UpdateBuff(BuffNames::SpamSkillTime, BuffNames::BuffTime, GetTickCount() + (DelaySpam * 1000));
				IPlayer.UpdateBuff(BuffNames::SpamSkillID, BuffNames::BuffTime, SkillID);
			}
		}

		if (CheckEggCooldownConfig.count(SkillID))
		{
			CdTime = CheckEggCooldownConfig.find(SkillID)->second.EggCooldownConfig;
			DelayTime = CheckEggCooldownConfig.find(SkillID)->second.EggDelayConfig;
		}
				
		if(CdTime || DelayTime)
			CooldownCheck = IPlayer.GetBuffValue(5000 + SkillID);

		int nTargetID = 0; char bType = 0;
		CPacket::Read((char*)pPacket, (char*)pPos, "bd", &bType, &nTargetID);
		void* pTarget = 0;

		TargetFind myTarget(bType, 0, nTargetID);
		pTarget = myTarget.getTarget();

		IChar Target(pTarget);

		if (SkillID == 110 && IPlayer.IsBuff(327))
		{
			IPlayer.CancelBuff(327);
			
			return;
		}

		if (CooldownCheck > GetTickCount())
		{
			IPlayer.SystemMessage("Invalid egg skill time detected!", TEXTCOLOR_RED); 
			return;
		} else {
			if(CdTime || DelayTime)
				IPlayer.UpdateBuff(5000 + SkillID, BuffNames::BuffTime, GetTickCount() + CdTime + DelayTime);
		}

		IPlayer.CancelBuff(327);

		if (IPlayer.GetProperty(PlayerProperty::ContinueSkillPlayerSkillID))
			ResetContinueSkill(IPlayer);

		if (IPlayer.GetTransformGrade() == 1 && Target.IsValid())
		{
			if (SkillID == 104)
			{
				SkillID -= 37;
				IPlayer._ShowBattleAnimation(Target, SkillID + 37);
			} else {
				
				return;
			}
		}

		if (IPlayer.GetTransformGrade() == 2 && Target.IsValid())
		{
			if (SkillID == 104 || SkillID == 105)
			{
				SkillID -= 37;
				IPlayer._ShowBattleAnimation(Target, SkillID + 37);
			} else {
				
				return;
			}
		}

		if (IPlayer.GetTransformGrade() == 3)
		{
			if ((SkillID == 104 || SkillID == 105) && Target.IsValid())
			{
				SkillID -= 37;
				IPlayer._ShowBattleAnimation(Target, SkillID + 37);
			} else if(SkillID == 106)
			{
				SkillID -= 37;
				IPlayer._ShowBattleAnimation(IPlayer, SkillID + 37);
			} else {
				
				return;
			}
		}

		if (IPlayer.GetTransformGrade() == 97 && Target.IsValid())
		{
			if (SkillID == 101)
			{
				SkillID -= 37;
				IPlayer._ShowBattleAnimation(Target, SkillID + 37);
			} else {
				
				return;
			}
		}

		if (IPlayer.GetTransformGrade() == 98)
		{
			if (SkillID == 101 && Target.IsValid())
			{
				SkillID -= 37;
				IPlayer._ShowBattleAnimation(Target, SkillID + 37);
			} else if (SkillID == 102)
			{
				SkillID -= 37;
				IPlayer._ShowBattleAnimation(IPlayer, SkillID + 37);
			} else {
				
				return;
			}
		}

		if (IPlayer.GetTransformGrade() == 99)
		{
			if (SkillID == 101 && Target.IsValid())
			{
				SkillID -= 37;
				IPlayer._ShowBattleAnimation(Target, SkillID + 37);
			} else if (SkillID == 102)
			{
				SkillID -= 37;
				IPlayer._ShowBattleAnimation(IPlayer, SkillID + 37);
			} else if (SkillID == 103)
			{
				SkillID -= 37;
				IPlayer._ShowBattleAnimation(IPlayer, SkillID + 37);
			} else {
				
				return;
			}
		}

		if (IPlayer.GetTransformGrade() == 65 && Target.IsValid())
		{
			if (SkillID == 107)
			{
				SkillID -= 37;
				IPlayer._ShowBattleAnimation(Target, SkillID + 37);
			} else {
				
				return;
			}
		}

		if (IPlayer.GetTransformGrade() == 66)
		{
			if (SkillID == 107 && Target.IsValid())
			{
				SkillID -= 37;
				IPlayer._ShowBattleAnimation(Target, SkillID + 37);
			} else if (SkillID == 108)
			{
				SkillID -= 37;
				IPlayer._ShowBattleAnimation(IPlayer, SkillID + 37);
			} else {
				
				return;
			}
		}

		if (IPlayer.GetTransformGrade() == 67)
		{
			if (SkillID == 107 && Target.IsValid())
			{
				SkillID -= 37;
				IPlayer._ShowBattleAnimation(Target, SkillID + 37);
			} else if (SkillID == 108)
			{
				SkillID -= 37;
				IPlayer._ShowBattleAnimation(IPlayer, SkillID + 37);
			} else if (SkillID == 109)
			{
				SkillID -= 37;
				IPlayer._ShowBattleAnimation(IPlayer, SkillID + 37);
			} else {
				
				return;
			}
		}

		if (IPlayer.GetTransformGrade() == 4)
		{
			if ((SkillID == 104 || SkillID == 105) && Target.IsValid())
			{
				SkillID -= 37;
				IPlayer._ShowBattleAnimation(Target, SkillID + 37);
			} else if (SkillID == 106)
			{
				SkillID -= 37;
				IPlayer._ShowBattleAnimation(IPlayer, SkillID + 37);
			} else if (SkillID == 113)
			{
				RevolveAttack(IPlayer);
				return;
			} else {
				
				return;
			}
		}

		if (IPlayer.GetTransformGrade() == 68)
		{
			if (SkillID == 107 && Target.IsValid())
			{
				SkillID -= 37;
				IPlayer._ShowBattleAnimation(Target, SkillID + 37);
			} else if (SkillID == 108)
			{
				SkillID -= 37;
				IPlayer._ShowBattleAnimation(IPlayer, SkillID + 37);
			} else if (SkillID == 109)
			{
				SkillID -= 37;
				IPlayer._ShowBattleAnimation(IPlayer, SkillID + 37);
			} else if (SkillID == 115)
			{
				BloodSuction(IPlayer,pPacket,pPos);
				
				return;
			} else {
				
				return;
			}
		}

		if (IPlayer.GetTransformGrade() == 100)
		{
			if (SkillID == 101 && Target.IsValid())
			{
				SkillID -= 37;
				IPlayer._ShowBattleAnimation(Target, SkillID + 37);
			} else if (SkillID == 102)
			{
				SkillID -= 37;
				IPlayer._ShowBattleAnimation(IPlayer, SkillID + 37);
			} else if (SkillID == 103)
			{
				SkillID -= 37;
				IPlayer._ShowBattleAnimation(IPlayer, SkillID + 37);
			} else if (SkillID == 116)
			{
				EggThunderbolt(IPlayer);
			} else {
				
				return;
			}
		}

		if (IPlayer.GetTransformGrade() == 129)
		{
			if (SkillID == 110)
			{
				HighClassHiding(IPlayer);
				
				return;
			}
		}

		if (IPlayer.GetTransformGrade() == 130)
		{
			if (SkillID == 110)
			{
				HighClassHiding(IPlayer);
				
				return;
			}

			if (SkillID == 111)
			{
				ZilPoong(IPlayer, pPacket, pPos);
				
				return;
			}
		}

		if (IPlayer.GetTransformGrade() == 131)
		{
			if (SkillID == 110)
			{
				HighClassHiding(IPlayer);
				
				return;
			}

			if (SkillID == 111)
			{
				ZilPoong(IPlayer, pPacket, pPos);
				
				return;
			}

			if (SkillID == 112)
			{
				ShinRhoe(IPlayer);
				
				return;
			}
		}

		if (IPlayer.GetTransformGrade() == 132)
		{
			if (SkillID == 110)
			{
				HighClassHiding(IPlayer);
				
				return;
			}

			if (SkillID == 111)
			{
				ZilPoong(IPlayer, pPacket, pPos);
				
				return;
			}

			if (SkillID == 112)
			{
				ShinRhoe(IPlayer);
				
				return;
			}

			if (SkillID == 114)
			{
				WhirlwindFeather(IPlayer);
				
				return;
			}
		}

		if (IPlayer.GetMap() != 21 && SkillID == 101 && IPlayer.GetTransformGrade() >= 97 && IPlayer.GetTransformGrade() <= 100)
			ActivateShiny(IPlayer, pPacket, pPos);

		
		CSkill::ExecuteTransformSkill(pSkill, SkillID, pPacket, pPos);
	}
}