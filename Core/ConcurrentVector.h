#ifndef __CONVEC_H
#define __CONVEC_H

#include <Windows.h>
template<class K>

class ConcurrentVector
{
	typedef typename std::vector<K>::reverse_iterator reverse_iterator;
	typedef typename std::vector<K>::iterator iterator;

protected:
	std::vector<K> CVector;
	Lock VectorLock;

public:

	ConcurrentVector() {
		VectorLock = Lock();
		CVector = std::vector<K>();
	}

	virtual void push_back(const K& key) {
		MutexMap Lock(VectorLock);
		CVector.push_back(key);
	}

	virtual iterator erase(const iterator& it) {
		MutexMap Lock(VectorLock);
		return CVector.erase(it);
	}

	virtual void clear() {
		MutexMap Lock(VectorLock);
		CVector.clear();
	}

	virtual int size() {
		MutexMap Lock(VectorLock);
		return CVector.size();
	}

	virtual bool empty() {
		MutexMap Lock(VectorLock);
		return CVector.empty();
	}

	K& operator[](const int& key) {
		MutexMap Lock(VectorLock);
		return CVector[key];
	}

	virtual std::vector<K> toVector() {
		MutexMap Lock(VectorLock);
		return CVector;
	}

	virtual K front() {
		MutexMap Lock(VectorLock);
		return CVector.front();
	}

	virtual iterator begin() {
		MutexMap Lock(VectorLock);
		return CVector.begin();
	}

	virtual iterator end() {
		MutexMap Lock(VectorLock);
		return CVector.end();
	}
	virtual reverse_iterator rbegin() {
		MutexMap Lock(VectorLock);
		return CVector.rbegin();
	}
	virtual reverse_iterator rend() {
		MutexMap Lock(VectorLock);
		return CVector.rend();
	}
};
#endif