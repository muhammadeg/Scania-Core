#ifndef __ITE_H
#define __ITE_H

#include <Windows.h>
template <class K>

class MyIterator
{
public:
	K second;

public:
	MyIterator(K second) {
		this->second = second;
	}
	void setSecond(K second) {
		this->second = second;
	}
};

#endif