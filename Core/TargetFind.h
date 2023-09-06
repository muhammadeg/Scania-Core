#pragma once
#include <windows.h>

class TargetFind {
	int Target;

public:
	TargetFind(int Type, int Choice,int ID)
	{
		Target = 0;
		if (Type == 0) {
			if (!Choice)
				Target = (int)CPlayer::FindPlayer(ID);
			else
				Target = CPlayer::ScanPlayer(ID);
		}
		else if (Type == 1)
			Target = (int)CMonster::FindMonster(ID);
	}

	TargetFind(const char* Name) {
		Target = 0;
		if(strlen(Name))
			Target = CPlayer::FindPlayerByName((char)Name);
	}

	void* getTarget() {
		return (void*)Target;
	}

	~TargetFind()
	{
		if (Target)
			CSkill::ObjectRelease((void*)Target, Target + 352);
	}
};