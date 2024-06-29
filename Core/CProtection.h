std::map<std::string, int> ipConnectionCount;
int MAX_CONNECTIONS_PER_IP = 15;
unsigned int CONNECTION_DELAY = 5000;

Lock ipConnectionCountMutex;
std::map<std::string, DWORD> lastConnectionTime;

int __fastcall OnCloseSocket(DWORD pSocket, void* /*unused*/)
{
	struct in_addr inaddr = *(struct in_addr*)(pSocket + 140);
	char* ipStr = inet_ntoa(inaddr);
	std::string ipString(ipStr);
	MutexMap Lock(ipConnectionCountMutex);
	// Decrement the connection count for this IP
	auto it = ipConnectionCount.find(ipString);
	if (it != ipConnectionCount.end())
	{
		if (--it->second <= 0)
		{
			ipConnectionCount.erase(it);
		}
	}

	return MSocket::OnClose(pSocket);
}

int __fastcall AcceptConnection(struct in_addr* in_addr, void* /*unused*/)
{
	char* ipStr = inet_ntoa(in_addr[35]);
	std::string ipString(ipStr);
	MutexMap Lock(ipConnectionCountMutex);
	const auto& it = ipConnectionCount.find(ipString);
	if (it != ipConnectionCount.end()) {
		if (it->second >= MAX_CONNECTIONS_PER_IP)
		{
			// User already has max connections
			return MSocket::GetCurConnectionsCount();
		}
	}
	DWORD now = GetTickCount();
	auto lastTimeIt = lastConnectionTime.find(ipString);
	if (lastTimeIt != lastConnectionTime.end())
	{
		DWORD elapsed = now - lastTimeIt->second;

		if (elapsed < CONNECTION_DELAY)
			return MSocket::GetCurConnectionsCount();
	}
	// Update the last connection time
	lastConnectionTime[ipString] = now;

	// Increment the connection count for this IP
	ipConnectionCount[ipString]++;

		return MSocket::AcceptConnection((void*)in_addr);
}

//int __fastcall AcceptConnection(struct in_addr* in_addr, void* /*unused*/)
//{
//	char* ipStr = inet_ntoa(in_addr[35]);
//	std::string ipString(ipStr);
//
//	const auto& it = ipConnectionCount.find(ipString);
//	if (it != ipConnectionCount.end()) {
//		if (it->second >= MAX_CONNECTIONS_PER_IP)
//		{
//			// User already has max connections
//			return MSocket::GetCurConnectionsCount();
//		}
//	}
//
//	// Increment the connection count for this IP
//	ipConnectionCount[ipString]++;
//
//	return MSocket::AcceptConnection((void*)in_addr);
//}

//
//int __fastcall OnCloseSocket(DWORD pSocket, void* /*unused*/)
//{
//	struct in_addr inaddr = *(struct in_addr*)(pSocket + 140);
//	char* ipStr = inet_ntoa(inaddr);
//	std::string ipString(ipStr);
//
//	// Decrement the connection count for this IP
//	auto it = ipConnectionCount.find(ipString);
//	if (it != ipConnectionCount.end())
//	{
//		if (--it->second <= 0)
//		{
//			ipConnectionCount.erase(it);
//		}
//	}
//
//	return MSocket::OnClose(pSocket);
//}