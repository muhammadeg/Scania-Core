#ifndef __CRITICALSECTION_H
#define __CRITICALSECTION_H

#include <Windows.h>

class CriticalSection
{
private:
	CRITICAL_SECTION *_CriticalSection;

public:
	CriticalSection() { }
	CriticalSection(CRITICAL_SECTION * critSection) { this->_CriticalSection = critSection; }
	void Enter() { CIOCriticalSection::Enter(this->_CriticalSection); }
	void Leave() { CIOCriticalSection::Leave(this->_CriticalSection);}
	bool IsLocked() { return false; }
};

#endif