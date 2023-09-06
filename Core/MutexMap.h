#pragma once
#include <windows.h>

class MutexMap {

	Lock *myLock;

public:
	MutexMap(Lock &mL) : myLock(&mL)
	{
		myLock->Enter();
	}

	~MutexMap()
	{
		myLock->Leave();
	}
};