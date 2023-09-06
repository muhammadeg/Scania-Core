#pragma once
#include <windows.h>

class Buffer {
	char* Packet;

public:
	Buffer(int Size)
	{
		Packet = new char[Size];
	}

	char* getPacket() {
		return Packet;
	}

	~Buffer()
	{
		delete[] Packet;
	}
};