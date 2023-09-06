#include <windows.h>
#include "IBuff.h"
#include "IChar.h"
#include <time.h>
#include "Functions.h"

IBuff::IBuff(void* Offset)
{
	this->Offset = Offset;
}

IBuff::~IBuff()
{
}

void* IBuff::GetOffset()
{
	return this->Offset;
}

int IBuff::GetValue() {
	if (this->Exists())
		return (*(DWORD *)((int)this->Offset + 12));
	else
		return 0;
}

int IBuff::GetBuffID() {
	if (this->Exists())
		return (*(DWORD *)((int)this->Offset + 4));
	else
		return 0;
}

int IBuff::GetTime() {
	int Check = 0;
	if (this->Exists()) {
		Check = (*(DWORD *)((int)this->Offset + 8));

		if (Check > 0 && ((this->GetBuffID() >= 119 && this->GetBuffID() <= 155) || (this->GetBuffID() >= 30 && this->GetBuffID() <= 32) || this->GetBuffID() == 99 || this->GetBuffID() == 101) && Check > (int)time(0))
			Check = Check - (int)time(0);

		if (Check > 0 && this->GetBuffID() >= 256 && Check > (int)GetTickCount())
			Check = (Check - GetTickCount()) / 1000;
	}

	return Check;
}

bool IBuff::Exists() {

	if ((int)this->GetOffset())
	{
		if (CBase::IsDeleted((int)this->GetOffset()))
			return false;
		else
			return true;
	}
	else {
		return false;
	}
}

int IBuff::GetType() {
	if (this->Exists())
		return (*(DWORD *)((int)this->Offset + 23));
	else
		return 0;
}

void IBuff::updateValue(int value) {
	if(this->Exists())
		*(DWORD*)((int)this->Offset + 12) = value;
}

void IBuff::DeleteThis() {
	delete this;
}