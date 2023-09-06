#include "Sha256.h"

std::string inBetween(const std::string start_delim,const std::string stop_delim, const std::string s){
	unsigned first_delim_pos = s.find(start_delim);
	unsigned end_pos_of_first_delim = first_delim_pos + start_delim.length();
	unsigned last_delim_pos = s.find(stop_delim);

	return s.substr(end_pos_of_first_delim,
		last_delim_pos - end_pos_of_first_delim);
}

double getAddition(std::string str,std::string type){

	double plus=0;
	std::string t = type+"+%lf";
	std::string t1 = type+"+ %lf";
	std::string t2 = type+" +%lf";
	std::string t3 = type+" + %lf";
	if((sscanf(str.c_str(), t.c_str(), &plus) == 1) || (sscanf(str.c_str(),t1.c_str(), &plus) == 1) || (sscanf(str.c_str(), t2.c_str(), &plus) == 1) || (sscanf(str.c_str(), t3.c_str(), &plus) == 1))
		return plus;
	else
		return 0;
}

double getMult(std::string str,std::string type){

	double plus=0;
	std::string t = type+"*%lf";
	std::string t1 = type+"* %lf";
	std::string t2 = type+" *%lf";
	std::string t3 = type+" * %lf";

	if((sscanf(str.c_str(), t.c_str(), &plus) == 1) || (sscanf(str.c_str(),t1.c_str(), &plus) == 1) || (sscanf(str.c_str(), t2.c_str(), &plus) == 1) || (sscanf(str.c_str(), t3.c_str(), &plus) == 1))
		return plus;
	else

		if(!str.compare(type))
			return 1;

		else
			return 0;
}

double getDiv(std::string str,std::string type){

	double plus=0;
	std::string t = type+"/%lf";
	std::string t1 = type+"/ %lf";
	std::string t2 = type+" /%lf";
	std::string t3 = type+" / %lf";
	if((sscanf(str.c_str(), t.c_str(), &plus) == 1) || (sscanf(str.c_str(),t1.c_str(), &plus) == 1) || (sscanf(str.c_str(), t2.c_str(), &plus) == 1) || (sscanf(str.c_str(), t3.c_str(), &plus) == 1))
		return plus;
	else
		return 0;
}

double getSoustraction(std::string str,std::string type){

	double plus=0;
	std::string t = type+"-%lf";
	std::string t1 = type+"- %lf";
	std::string t2 = type+" -%lf";
	std::string t3 = type+" - %lf";
	if((sscanf(str.c_str(), t.c_str(), &plus) == 1) || (sscanf(str.c_str(),t1.c_str(), &plus) == 1) || (sscanf(str.c_str(), t2.c_str(), &plus) == 1) || (sscanf(str.c_str(), t3.c_str(), &plus) == 1))
		return plus;
	else
		return 0;
}

bool newParameter(std::string text, std::string before, std::string parameter, int value, int* dmg) {
	bool result = false;
	if (text.find(parameter) != std::string::npos || !text.compare(parameter)) {
		double Addition = getAddition(text, parameter);
		if (Addition) {
			double plus = Addition;

			if (before.size() > 0) {
				if (!before.compare("*"))  *dmg *= (value + plus);
				else if (!before.compare("-"))  *dmg -= (value + plus);
				else if (!before.compare("/")) *dmg /= (value + plus);
				else *dmg += (value + plus);
			}
			else *dmg += (value + plus);
			result = true;
		}
		else {
			double Multi = getMult(text, parameter);
			if (Multi) {
				double plus = Multi;

				if (before.size() > 0) {
					if (!before.compare("*"))  *dmg *= (value * plus);
					else if (!before.compare("-"))  *dmg -= (value * plus);
					else if (!before.compare("/"))  *dmg /= (value * plus);
					else *dmg += (value * plus);
				}
				else *dmg += (value * plus);
				result = true;
			}
			else
			{
				double Soust = getSoustraction(text, parameter);
				if (Soust) {
					double plus = Soust;

					if (before.size() > 0) {
						if (!before.compare("*"))  *dmg *= (value - plus);
						else if (!before.compare("-"))  *dmg -= (value - plus);
						else if (!before.compare("/"))  *dmg /= (value - plus);
						else *dmg += (value - plus);
					}
					else *dmg += (value - plus);
					result = true;
				}
				else {
					double Div = getDiv(text, parameter);
					if (Div) {
						double plus = Div;

						if (before.size() > 0) {
							if (!before.compare("*"))  *dmg *= (value / plus);
							else if (!before.compare("-"))  *dmg -= (value / plus);
							else if (!before.compare("/"))  *dmg /= (value / plus);
							else *dmg += (value / plus);
						}
						else *dmg += (value / plus);
						result = true;
					}
				}
			}
		}
	}

	return result;
}

int calculDmg(void* Player, int SkillID, void* Target) {
	IChar IPlayer(Player);
	IChar ITarget(Target);

	if (!IPlayer.IsOnline() || !ITarget.IsOnline())
		return 0;

	int TargetType = ITarget.GetType();
	int Key = (IPlayer.GetClass() * 1000) + SkillID;

	SkillDamage sDmg = SkillDamage();

	auto it = SkillsDamage.find(Key + ((TargetType + 1) * 100));

	if (it != SkillsDamage.end())
		sDmg = it->second;
	else {
		it = SkillsDamage.find(Key);
		if (it != SkillsDamage.end())
			sDmg = it->second;
		else
			return 0;
	}

	std::string str = sDmg.damage;

	int dmg = 0;

	int pSkill = IPlayer.GetSkillPointer(SkillID);

	if (IPlayer.IsValid() && pSkill) {
		ISkill xSkill((void*)pSkill);
		int nSkillGrade = xSkill.GetGrade();

		std::vector<std::string> arra = getExplode("(", ")", str);

		std::string before;
		int position = 0;
		for (size_t i = 0; i < arra.size(); i++) {
			if (i > 0)
				before = str[position + i - 1];

			std::string dmgText = arra[i];

			position += dmgText.length() + 2;

			if (newParameter(dmgText, before, "MagAtk", IPlayer.GetMagAtk(), &dmg))
				continue;
			else if (newParameter(dmgText, before, "CleanAtk", CChar::GetMaxMagic((int)Player), &dmg))
				continue;
			else if (newParameter(dmgText, before, "PhyAtk", IPlayer.GetPhyAtk(), &dmg))
				continue;
			else if (newParameter(dmgText, before, "DeathBlow", IPlayer.GetDeathBlow(), &dmg))
				continue;
			else if (newParameter(dmgText, before, "CleanPhyAtk", CChar::GetMaxAttack((int)Player), &dmg))
				continue;
			else if (newParameter(dmgText, before, "Int", IPlayer.GetInt(), &dmg))
				continue;
			else if (newParameter(dmgText, before, "Str", IPlayer.GetStr(), &dmg))
				continue;
			else if (newParameter(dmgText, before, "Hth", IPlayer.GetHth(), &dmg))
				continue;
			else if (newParameter(dmgText, before, "Agi", IPlayer.GetAgi(), &dmg))
				continue;
			else if (newParameter(dmgText, before, "Level", IPlayer.GetLevel(), &dmg))
				continue;
			else if (newParameter(dmgText, before, "SkillGrade", nSkillGrade, &dmg))
				continue;
			else if (newParameter(dmgText, before, "Wis", IPlayer.GetWis(), &dmg))
				continue;
			else if (newParameter(dmgText, before, "OTP", IPlayer.GetOTP(), &dmg))
				continue;
			else if (newParameter(dmgText, before, "SkillLoading", xSkill.GetLoadingTime(), &dmg))
				continue;
			else if (newParameter(dmgText, before, "Eva", IPlayer.GetEva(), &dmg))
				continue;
			else if (newParameter(dmgText, before, "TargetDefense", ITarget.GetDef(), &dmg))
				continue;
			else if (TargetType == 0 && newParameter(dmgText, before, "TargetEva", ITarget.GetEva(), &dmg))
				continue;
		}

		if (TargetType == 0 && sDmg.Reduce > 0)
			dmg = (dmg * (sDmg.Reduce)) / 100;

		if (TargetType == 1 && sDmg.PVE > 0 && dmg > sDmg.PVE)
			dmg = sDmg.PVE;

		if (TargetType == 0 && sDmg.PVP > 0 && dmg > sDmg.PVP)
			dmg = sDmg.PVP;
	}

	return dmg;
}
