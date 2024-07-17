void MainAtkDebug(int Socket, char *IP, int Parameter) {
	if (attackDebug == 1) {
		std::string debug = "[DEBUG]";
		if (Parameter == 1)
			debug = "[[DEBUG]]";
		if (Parameter == 2)
			debug = "[Prevention]";

		std::string Datoe = "./Debugger/DDoSCheck/Prevention_" + Time::GetDay() + "_" + Time::GetMonth() + "_" + Time::GetYear() + "_" + Time::GetHour() + ".txt";
		std::fstream CHLOG;
		CHLOG.open(Datoe, std::fstream::in | std::fstream::out | std::fstream::app);
		CHLOG << "[" << Time::GetTime() << "] " << debug << " MainServer: Incoming attack prevented."
			<< " Details: { Socket: " << (int)Socket
			<< ", IP Address: " << IP
			<< ", Description: Unauthorized access attempt detected and blocked }"
			<< std::endl;
		CHLOG.close();
	}
}

ConcurrentMap<std::string, int> ipConnectionCount;

struct ConnectionsS {
	int Allow;
};

ConcurrentMap<std::string, ConnectionsS> ipConnectionCheck;
ConcurrentMap<std::string, int> ipBlocked;

Lock ipConnectionCountMutex;
ConcurrentMap<std::string, DWORD> lastConnectionTime;

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

	if (ipBlocked.count(ipString)) {
		MainAtkDebug((int)in_addr, ipStr, 2);
		return MSocket::GetCurConnectionsCount();
	}

		int Allow = ipConnectionCheck.find(ipString)->second.Allow;

		if (!Allow && ipConnectionCount.find(ipString)->second < 2 || Allow)
			return MSocket::AcceptConnection((void*)in_addr);
		else {
			MainAtkDebug((int)in_addr, ipStr, 2);
			return MSocket::GetCurConnectionsCount();
		}

}
