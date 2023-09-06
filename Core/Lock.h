#ifndef __LOCK_H
#define __LOCK_H

#include <Windows.h>

class Lock
{
private:
	RTL_CRITICAL_SECTION _CriticalSection;

public:
	Lock() { InitializeCriticalSection(&this->_CriticalSection); }
	virtual ~Lock() { DeleteCriticalSection(&this->_CriticalSection); }
	void Enter() { EnterCriticalSection(&this->_CriticalSection); }
	void Leave() { LeaveCriticalSection(&this->_CriticalSection); }
	bool isFree() { return (this->_CriticalSection.LockCount == -1); }
};

#endif