#ifndef __CONMAP_H
#define __CONMAP_H

#include <map>
#include <Windows.h>
#include "Lock.h"

template<class K, class V>
class ConcurrentMap
{
	typedef typename std::map<K, V>::iterator myIterator;
	typedef typename std::map<K, V>::const_iterator const_iterator;
	typedef typename std::map<K, V>::reverse_iterator reverse_iterator;
	typedef std::map<K, V> myMap;

public:
	ConcurrentMap() {
		MapLock = Lock();
		CMap = myMap();
		defaultVariable = V();
	}

	void lock() {
		MapLock.Enter();
	}

	void unlock() {
		MapLock.Leave();
	}

	bool count(const K& key) {
		MutexMap Lock(MapLock);
		return CMap.count(key) > 0;
	}

	void insert(const std::pair<K, V>& pair) {
		MutexMap Lock(MapLock);
		CMap.insert(pair);
	}

	void replaceInsert(const K& key, const V& Value) {
		MutexMap Lock(MapLock);
		CMap[key] = Value;
	}

	V& operator[](const K& key) {
		MutexMap Lock(MapLock);
		return CMap[key];
	}

	myIterator erase(myIterator key) {
		MutexMap Lock(MapLock);
		return CMap.erase(key);
	}

	void erase(const K& key) {
		MutexMap Lock(MapLock);
		CMap.erase(key);
	}

	void clear() {
		MutexMap Lock(MapLock);
		CMap.clear();
	}

	int size() {
		MutexMap Lock(MapLock);
		return CMap.size();
	}

	bool empty() {
		MutexMap Lock(MapLock);
		return CMap.empty();
	}

	myIterator begin() {
		MutexMap Lock(MapLock);
		return CMap.begin();
	}

	myIterator end() {
		MutexMap Lock(MapLock);
		return CMap.end();
	}

	reverse_iterator rbegin() {
		MutexMap Lock(MapLock);
		return CMap.rbegin();
	}

	reverse_iterator rend() {
		MutexMap Lock(MapLock);
		return CMap.rend();
	}

	const myMap& toMap() const {
		return CMap;
	}

	myIterator find(const K& key) {
		MutexMap Lock(MapLock);
		return CMap.find(key);
	}

	myIterator find(const K& key) const {
		MutexMap Lock(MapLock);
		return CMap.find(key);
	}

	V findValue(const K& Key) {
		MutexMap Lock(MapLock);
		auto it = CMap.find(Key);
		if (it != CMap.end()) {
			return it->second;
		}
		return defaultVariable;
	}

	V findExists(const K& Key) {
		MutexMap Lock(MapLock);
		auto it = CMap.find(Key);
		if (it != CMap.end()) {
			return it->second;
		}
		return defaultVariable;
	}

	V& findPointer(const K& Key) {
		MutexMap Lock(MapLock);
		auto &it = CMap.find(Key);
		if (it == CMap.end()) {
			CMap[Key] = defaultVariable;
			it = CMap.find(Key);
		}
		return it->second;
	}

private:
	myMap CMap;
	Lock MapLock;
	V defaultVariable;
};

#endif // __CONMAP_H
