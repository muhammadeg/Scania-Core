#ifndef __CONSET_H
#define __CONSET_H

#include <Windows.h>
template<class K>

class ConcurrentSet
{
	typedef typename std::set<K>::iterator mySetIterator;
	typedef typename std::set<K>::reverse_iterator my_reverseSetIterator;
	typedef typename std::set<K>::const_iterator const_set_iterator;
protected:
	std::set<K> CSet;
	Lock SetLock;

public:
	ConcurrentSet() {
		SetLock = Lock();
		CSet = std::set<K>();
	}

	virtual bool count(const K& key) {
		MutexMap Lock(SetLock);
		return CSet.count(key) > 0;
	}

	virtual void insert(const K& key) {
		MutexMap Lock(SetLock);
		CSet.insert(key);
	}

	virtual void erase(const K& key) {
		MutexMap Lock(SetLock);
		CSet.erase(key);
	}

	virtual void clear() {
		MutexMap Lock(SetLock);
		CSet.clear();
	}

	virtual int size() {
		MutexMap Lock(SetLock);
		return CSet.size();
	}

	virtual std::set<K> toSet() {
		MutexMap Lock(SetLock);
		return CSet;
	}

	virtual mySetIterator begin() {
		MutexMap Lock(SetLock);
		return CSet.begin();
	}

	virtual mySetIterator end() {
		MutexMap Lock(SetLock);
		return CSet.end();
	}

	virtual bool empty() {
		MutexMap Lock(SetLock);
		return CSet.empty();
	}

	virtual my_reverseSetIterator rbegin() {
		MutexMap Lock(SetLock);
		return CSet.rbegin();
	}

	virtual my_reverseSetIterator rend() {
		MutexMap Lock(SetLock);
		return CSet.rend();
	}

};
#endif