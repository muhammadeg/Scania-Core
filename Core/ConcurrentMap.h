#ifndef __CONMAP_H
#define __CONMAP_H

#include <Windows.h>
template<class K, class V>
class ConcurrentMap
{
	typedef typename std::map<K, V>::iterator myIterator;
	typedef typename std::map<K, V>::const_iterator const_iterator;
	typedef typename std::map<K, V> myMap;
	typedef typename std::map<K, V>::reverse_iterator reverse_iterator;
	V defaultVariable;

public:
	ConcurrentMap() {
		MapLock = Lock();
		CMap = myMap();
		defaultVariable = V();
	}

	virtual void lock() {
		MapLock.Enter();
	}

	virtual void unlock() {
		MapLock.Leave();
	}

	virtual bool count(const K& key) {
		MutexMap Lock(MapLock);
		return toMap().count(key) > 0;
	}

	virtual void insert(const std::pair<K, V>& pair) {
		MutexMap Lock(MapLock);
		CMap.insert(pair);
	}

	virtual void replaceInsert(const K& key, const V& Value) {
		MutexMap Lock(MapLock);
		CMap[key] = Value;
	}

	V& operator[](const K& key) {
		MutexMap Lock(MapLock);
		return CMap[key];
	}

	virtual void erase(const K& key) {
		MutexMap Lock(MapLock);
		CMap.erase(key);
	}

	virtual myIterator erase(myIterator& key) {
		MutexMap Lock(MapLock);
		return CMap.erase(key);
	}

	virtual void clear() {
		MutexMap Lock(MapLock);
		CMap.clear();
	}

	virtual int size() {
		MutexMap Lock(MapLock);
		return toMap().size();
	}

	Pointer<MyIterator<V>> find(const K& Key) {
		Pointer<MyIterator<V>> pt(new MyIterator<V>(findValue(Key)));
		return pt;
	}

	virtual bool empty() {
		MutexMap Lock(MapLock);
		return CMap.empty();
	}

	virtual V findValue(const K& Key) {
		MutexMap Lock(MapLock);
		return CMap.find(Key)->second;
	}

	virtual V findExists(const K& Key) {
		MutexMap Lock(MapLock);

		auto it = CMap.find(Key);
		if (it == CMap.end())
			return defaultVariable;

		return it->second;
	}

	virtual V& findPointer(const K& Key) {
		auto &it = CMap.find(Key);
		if (it == CMap.end()) {
			CMap[Key] = defaultVariable;
			it = CMap.find(Key);
		}

		return it->second;
	}

	virtual myIterator begin() {
		MutexMap Lock(MapLock);
		return CMap.begin();
	}

	virtual myIterator end() {
		MutexMap Lock(MapLock);
		return CMap.end();
	}

	virtual reverse_iterator rbegin() {
		MutexMap Lock(MapLock);
		return CMap.rbegin();
	}

	virtual reverse_iterator rend() {
		MutexMap Lock(MapLock);
		return CMap.rend();
	}
	
   const myMap &toMap() const {
		return CMap;
	}

private:
	myMap CMap;
	Lock MapLock;

};
#endif