
const char* getMachineName()
{
	static char computerName[1024];
	DWORD size = 1024;
	GetComputerName(computerName, &size);
	return &(computerName[0]);
}
int getVolumeHash()
{
	DWORD serialNum = 0;

	GetVolumeInformation("c:\\", NULL, 0, &serialNum, NULL, NULL, NULL, 0);
	int hash = (int)((serialNum + (serialNum >> 16)) & 0xFFFF);

	return hash;
}

string getIP() {
	WSADATA wsaData;
	int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (result != 0) {
		return "WSAStartup failed";
	}

	char hostname[256];
	if (gethostname(hostname, sizeof(hostname)) == SOCKET_ERROR) {
		WSACleanup();
		return "Error getting hostname";
	}

	struct hostent* host;
	host = gethostbyname(hostname);
	if (host == NULL) {
		WSACleanup();
		return "Error getting host by name";
	}

	struct in_addr addr;
	memcpy(&addr, host->h_addr_list[0], sizeof(struct in_addr));
	char* ip = inet_ntoa(addr);
	if (ip == NULL) {
		WSACleanup();
		return "Error converting IP to string";
	}

	WSACleanup();
	return ip;
}
string getHWID(){

	HKEY hKey = 0;
	wchar_t buf[255];
	DWORD dwBufSize = sizeof(buf);
	const wchar_t* subkey = L"Software\\Microsoft\\Cryptography";
	bool t = false;
	if (RegOpenKeyExW(HKEY_LOCAL_MACHINE, subkey, 0, KEY_READ | KEY_WOW64_64KEY, &hKey) == ERROR_SUCCESS)
	{
		if (RegQueryValueExW(hKey, L"MachineGuid", 0, 0, (BYTE*)buf, &dwBufSize) == ERROR_SUCCESS)
		{
			t = true;
			RegCloseKey(hKey);
		}
		else
		{
			t = false;
		}
	}
	if (t) {
		wstring ws(buf);
		string str(ws.begin(), ws.end());
		return Int2String(203 * getVolumeHash()) + str + Int2String(getVolumeHash() * 9);
	}
	else
		return "";
}