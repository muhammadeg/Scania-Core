
void __fastcall CIOSocketEnter(int Socket, void *edx) {
	char* IP = inet_ntoa(*(struct in_addr *)(Socket + 140));
	int Blocked = BlockList.count(sha256(IP));

	if (Blocked)
		CIOSocket::CIOSocket__Close(Socket);
	else
		CIOSocket::Enter(Socket); 
}

int __fastcall CIOSocketCreate(int CServerThisPointer, void *edx, int Socket, int Infos)
{
	int IPNum = *(DWORD *)(Infos + 4);
	
	if (isIPEnabled() && IPNum != 16777343) {
		if (IPNum == InterlockedExchangeAdd(&LastIP, 0) && InterlockedExchangeAdd(&CreatePacket, 0) >= GetTickCount()) {
			InterlockedExchange(&CreatePacket, GetTickCount() + PacketInBetween);
			return 0;
		}
		
		char* IP = inet_ntoa(*(struct in_addr *)(Infos + 4));

		int Port = *(DWORD *)(Infos + 2);

		if (!IPNum || !IP || !Port)
			return 0;

		int Blocked = BlockList.count(sha256(IP));

		if (Blocked)
			return 0;

		if (PacketInBetween) {
			InterlockedExchange(&LastIP, IPNum);
			InterlockedExchange(&CreatePacket, GetTickCount() + PacketInBetween);
		}
	}

	return CIOSocket::Create(CServerThisPointer, Socket, Infos);
}

void __fastcall CIOSocketClose(int Socket, void* edx) {
	SocketPacket.erase(Socket);
	SocketInfos.erase(Socket);
	PacketDelay.erase(Socket);
	return CIOSocket::CIOSocket__Close(Socket);
}

void __fastcall CIOSocketGracefulClose(int Socket, void* edx) {
	SocketPacket.erase(Socket);
	SocketInfos.erase(Socket);
	PacketDelay.erase(Socket);
	return CIOSocket::GraceFulClose(Socket);
}

void __fastcall Close(int Socket,void *edx,int value){
	//PacketHackCheck.erase((int)Socket);
	CDBSocket::ProcessHtml(Socket,(char)45,(unsigned int)"b",value);
	Undefined::ForKick((void*)Socket, value);
	//CIOSocket::CIOSocket__Close(Socket);
}

void GracefulClose(int Socket) {
	CIOCriticalSection::Enter((struct _RTL_CRITICAL_SECTION *)(Socket + 20));
	int s = InterlockedExchange((volatile LONG *)(Socket + 16), -1);
	CIOCriticalSection::Leave((struct _RTL_CRITICAL_SECTION *)(Socket + 20));
	if (s != -1)
	{
		closesocket(s);
		CIOObject::Release((void*)Socket);
	}
}
int __fastcall GetInventorySize(int Player, void *edx) {

	IChar IPlayer((void*)Player);
	int Size = CPlayer::GetInvenSize(Player);
	if (Size >= 60) {

		if (IPlayer.GetBuffValue(BuffNames::Extension1) >= (int)time(0))
			Size -= 36;
		if (IPlayer.GetBuffValue(BuffNames::Extension2) >= (int)time(0))
			Size -= 36;
		if (IPlayer.GetBuffValue(BuffNames::Extension3) >= (int)time(0))
			Size -= 36;

		Size -= 12;

		Size -= IPlayer.GetProperty(PlayerProperty::InventoryCheck);
		Size += *((DWORD *)Player + 276);
	}
	if (Size < 0) Size = 0;
	return Size;
}

int __fastcall Process(void *Socket, void *edx, char *Data)
{ 
	char* IP = inet_ntoa(*(struct in_addr *)((int)Socket + 140));
	int Player = (*(DWORD *)((int)Socket + 120));

	int OldP = (unsigned char)Data[2];

	if (SocketInfos.count((int)Socket))
		Data[2] = (unsigned char)Data[2] - (CryptKey + (2 * (firstDig + (3 * SocketInfos.findValue((int)Socket)))));
	else {
		Data[2] = (unsigned char)Data[2] - 89;

		if ((unsigned char)Data[2] == 8) {
			int RandKey = CTools::Rate(2, 200);
			SocketInfos.replaceInsert((int)Socket, RandKey);
			CDBSocket::ProcessHtml((int)Socket, (char)0xFE, (unsigned int)"ddd", 211, (int)uptimestart, RandKey << 13);
		}
	}
	int packet = (unsigned char)Data[2];

	if ((unsigned char)Data[2] == 1)
	{
		int Type = 0, Value = 0, Key = 0, MD5On = 0, MD5Time = 0, DelayCheck = 0, Hash = 0, pos = 0;
		CPacket::Read((char*)((void*)(Data + 3)), (char*)(Data + *(WORD*)Data), "dddddddd", &Type, &Value, &Key, &MD5On, &MD5Time, &DelayCheck, &Hash, &pos);

		int NewKey = Key >> 19;

		if (NewKey <= 0 || NewKey > 200 || (SocketInfos.count((int)Socket) && NewKey == SocketInfos.findValue((int)Socket))) {
			CDBSocket::ProcessHtml((int)Socket, (char)0xFF, (unsigned int)"d", 219);
			CIOSocketClose((int)Socket, 0);
			return 0;
		}

		if (MD5Check && MD5On && pos < (int)MD5FileChecker.size() && pos >= 0) {
			int PosHash = MD5FileChecker.at(pos);

			int TimeCheck = sha256(Int2String((MD5Time - DelayCheck) + PosHash + pos)) % INT_MAX;
			pos++;

			if (Hash == TimeCheck) {
				if ((*(DWORD*)((int)Socket + 120))) {
					IChar IPlayer(*(void**)((int)Socket + 120));
					int lastPos = IPlayer.GetBuffValue(BuffNames::MD5Time);
					if (lastPos && !(lastPos == pos || (lastPos == (MD5FileChecker.size() + 1) && pos == 1))) {
						IPlayer.SystemMessage("Wrong or outdated files detected. Please update your client", TEXTCOLOR_RED);
						CDBSocket::ProcessHtml((int)Socket, (char)0xFE, (unsigned int)"d", 218);
						Close((int)Socket, 0, 3);
						return 0;
					}
					else {
						IPlayer.UpdateBuff(BuffNames::MD5Time, BuffNames::BuffTime, pos + 1);
						IPlayer.UpdateBuff(BuffNames::MD5Hash, BuffNames::BuffTime, GetTickCount() + 300000 + DelayCheck);
					}
				}
			}
			else {
				CDBSocket::ProcessHtml((int)Socket, (char)0xFE, (unsigned int)"d", 218);
				Close((int)Socket, 0, 3);
				return 0;
			}
		}

		SocketInfos.replaceInsert((int)Socket, NewKey);

		*(DWORD*)((int)Socket + 144) = (Type - GetTickCount());
	}

	if (packetDebugger == 1) {
		std::string Dato = "./Debugger/Packet/PROCESS_" + Time::GetDay() + "_" + Time::GetMonth() + "_" + Time::GetYear() + "_" + Time::GetHour() + "." + Time::GetMinute() + ".txt";
		std::fstream DGLOG;
		DGLOG.open(Dato, std::fstream::in | std::fstream::out | std::fstream::app);
		DGLOG << Time::GetTime() << " " << (int)Socket << ": " << packet << std::endl;
		DGLOG.close();
	}

	if ((unsigned char)Data[2] == 253)
	{
		int Type = 0, Value = 0;
		const char *pcname = "";
		CPacket::Read((char*)((void*)(Data + 3)), (char*)(Data + *(WORD*)Data), "dds", &Type, &Value, &pcname, 16);

		if (TrackerActive && Tracker.count(pcname)) {
			IChar IPlayer((void*)Player);
			std::string PCheck = IPlayer.IsOnline() ? IPlayer.GetName() : "Unknown";

			std::string Dato = "./Tracker/" + Tracker.find(pcname)->second;
			std::fstream DGLOG;
			DGLOG.open(Dato, std::fstream::in | std::fstream::out | std::fstream::app);
			DGLOG << Time::GetTime() << " [Name]: '" << PCheck << "' [PC Name]: '" + (std::string)pcname << "' [IP]: '" << IP << "' [Packet]: " << Type << std::endl;
			DGLOG.close();
		}

		if (PacketProtection && Value != uptimestart) {
			CDBSocket::ProcessHtml((int)Socket, (char)0xFF, (unsigned int)"d", 220);
			// instantly close the socket
		//	SocketCheck.insert((int)Socket);
			Close((int)Socket, 0, 3);

	//		MainAtkDebug((int)Socket, IP, 1);
	//		CIOSocket::GraceFulClose((int)Socket);
			return 0;
		}	

		SocketPacket.replaceInsert((int)Socket, Type);
		return 0;
	}

	if ((unsigned char)Data[2] != 253 && (unsigned char)Data[2] != 8 && (unsigned char)Data[2] != 1 && PacketProtection)
	{
		unsigned char DataType = ((unsigned char)Data[2] + ((SocketInfos.count((int)Socket) ? (2 * ((firstDig + 1) + (3 * SocketInfos.findValue((int)Socket)))) : 0)));
		
		if (!SocketPacket.count((int)Socket) || SocketPacket.findValue((int)Socket) != (int)DataType)
		{
			CDBSocket::ProcessHtml((int)Socket, (char)0xFF, (unsigned int)"d", 219);
			Close((int)Socket, 0, 3); 
			MainAtkDebug((int)Socket, IP, 0);
			if (My_PacketProtection) {
				std::string ipString(IP);
				ipBlocked[ipString] = 1;
			}
			return 0;
		}
	}

	if (PacketActive && packet != 174 && packet != 253 && packet != 251 && packet != 250) {

		if (!PacketDelay.count((int)Socket)) {
			PacketCheck pack = PacketCheck();
			pack.FirstDelay = GetTickCount();
			pack.Type = 1;
			PacketDelay.replaceInsert((int)Socket, pack);
		}
		else {
			PacketCheck packetInfos = PacketDelay.findValue((int)Socket);
			packetInfos.Type += 1;
			PacketDelay.replaceInsert((int)Socket, packetInfos);

			if (packetInfos.Type >= PacketLimit) {
				if ((GetTickCount() - packetInfos.FirstDelay) < PacketTime) {
					CIOSocketClose((int)Socket, 0);
					return 0;
				}
				PacketCheck pack = PacketCheck();
				pack.FirstDelay = GetTickCount();
				pack.Type = 1;
				PacketDelay.replaceInsert((int)Socket, pack);
			}
		}
	}

	if ((unsigned char)Data[2] == 217)
	{
		if (MD5Check == 1)
		{
			int Type = 0, Value = 0;
			const char *engineCheck = "";
			CPacket::Read((char*)((void*)(Data + 3)), (char*)(Data + *(WORD*)Data), "dds", &Type, &Value, &engineCheck, 33);
			//AddTest
			if ((PacketProtection && Value != uptimestart) || (Type != 211 && Type != 13 && Type != 1) || strlen(engineCheck) != 32) {
				CDBSocket::ProcessHtml((int)Socket, (char)0xFE, (unsigned int)"d", 218);
				Close((int)Socket, 0, 3);
				CIOSocket::GraceFulClose((int)Socket);
				return 0;
			}

			if (strcmp(engineCheck, ConfigEngine) != 0) {
				CDBSocket::ProcessHtml((int)Socket, (char)0xFE, (unsigned int)"d", 218);
				Close((int)Socket, 0, 3);
				return 0;
			}

			if ((*(DWORD *)((int)Socket + 120)) && Type == 13) {
				IChar IPlayer(*(void**)((int)Socket + 120));
				if (IPlayer.IsOnline())
					IPlayer.Buff(3076, 120, 0);
			}
		}
		return 0;
	}

	if ((unsigned char)Data[2] == 214) {
		int Hash = 0;
		CPacket::Read((char*)((void*)(Data + 3)), (char*)(Data + *(WORD*)Data), "d", &Hash);

		if (MD5Check == 1 && Hash != Hashes) {
			CDBSocket::ProcessHtml((int)Socket, (char)0xFE, (unsigned int)"d", 218);
			Close((int)Socket, 0, 3);
		}

		return 0;
	}

	if ((unsigned char)Data[2] == 216) {
		const char *pcname = "", *hwid = "", *mac = "";
		int Type = 0;
		CPacket::xRead((char*)((void*)(Data + 3)), "dsss", &Type, &pcname, &mac, &hwid);
		
		if (Type != 211 && Type != 13){
			CIOSocketClose((int)Socket, 0);
			return 0;
		}

		bool Blocked = (hwid && BlockList.count(sha256(hwid))) || (strlen(mac) == 12 && BlockList.count(sha256(mac)));

		if (Blocked) {
			CDBSocket::ProcessHtml((int)Socket, (char)0xFE, (unsigned int)"d", 219);
			PacketDelay.erase((int)Socket);
			CIOSocketClose((int)Socket, 0);
			return 0;
		}

		if (Player && Type == 13) {
			IChar IPlayer((void*)Player);
			if (IPlayer.IsOnline() && !User.count(IPlayer.GetPID())) {
				UserInfo thisUser = UserInfo();
				if(hwid && strlen(hwid))
					thisUser.Hardware.assign(hwid);
				if(pcname && strlen(pcname))
					thisUser.PCName.assign(pcname);
				if(mac && strlen(mac) == 12)
					thisUser.MAC.assign(mac);
				User.replaceInsert(IPlayer.GetPID(),thisUser);
			}
		}

		return 0;
	}

	/*if ((unsigned char)Data[2] != 253)
	{
		if ((unsigned char)Data[2] != PacketHackCheck.find((int)Socket)->second)
		{
			CDBSocket::ProcessHtml((int)Socket,(char)0xFF,(unsigned int)"d",220);
			CIOSocket::CIOSocket__Close((int)Socket);
			return 0;
		}
	}*/

	if (PacketBlock.count(packet))
		return 0;

	if (Data[2] == 9 && ((std::string)Active2ndPwd == "true" || (std::string)Active2ndPwd == "True"))
	{
		int Type = 0; const char *RealPwd = "asd", *Pwd2 = "asd", *MyPwd2 = "asd"; Interface<ITools> Tools;
		//Tools->ParseData((char*)((void*)(Data + 3)), "b", &Type);
		CPacket::xRead((char*)((void*)(Data + 3)), "b", &Type);
		if (Type == 0)
		{
			//Tools->ParseData((char*)((void*)(Data + 3)), "bs", &Type, &MyPwd2);
			CPacket::xRead((char*)((void*)(Data + 3)), "bs", &Type, &MyPwd2);
			if (MyPwd2 && strlen(MyPwd2))
				CDBSocket::ProcessHtml((int)Socket, (char)0xFF, (unsigned int)"ds", 252, MyPwd2);
		}

		if (Type == 1)
		{
			//Tools->ParseData((char*)((void*)(Data + 3)), "bss", &Type, &RealPwd, &Pwd2);
			CPacket::xRead((char*)((void*)(Data + 3)), "bss", &Type, &RealPwd, &Pwd2);
			CDBSocket::ProcessHtml((int)Socket, (char)0xFF, (unsigned int)"dss", 251, RealPwd, Pwd2);
		}

		if (Type == 2)
		{
			//Tools->ParseData((char*)((void*)(Data + 3)), "bss", &Type, &RealPwd, &Pwd2);
			CPacket::xRead((char*)((void*)(Data + 3)), "bss", &Type, &RealPwd, &Pwd2);
			CDBSocket::ProcessHtml((int)Socket, (char)0xFF, (unsigned int)"dss", 250, RealPwd, Pwd2);
		}

		return 0;
	}

	if ((unsigned char)Data[2] == 255)
	{
		int Type = 0;
		int LeftPacket = CPacket::Read((char*)((void*)(Data + 3)), (char*)(Data + *(WORD*)Data), "d", &Type);

		if (Type == 1 && ((std::string)Active2ndPwd == "true" || (std::string)Active2ndPwd == "True"))
		{
			const char *MyID, *MyPwd, *My2ndPwd;
			CPacket::xRead((char*)LeftPacket, "sss", &MyID, &MyPwd, &My2ndPwd);

			if (!My2ndPwd || !Read2ndPwd.count(MyID) || !strlen(My2ndPwd))
				return 0;

			std::stringstream strValuexx;
			strValuexx << My2ndPwd << std::endl;
			int Valuexx = 0;
			strValuexx >> Valuexx;
			std::stringstream strValueyy;
			strValueyy << Read2ndPwd.findValue(MyID) << std::endl;
			int Valueyy = 0;
			strValueyy >> Valueyy;

			if (Valuexx == Valueyy)
			{
				if (Undefined::CheckID((int*)MyID))
				{
					if (*(BYTE*)MyPwd)
					{
						Undefined::Login(1, (unsigned int)"dssdw", *(DWORD *)((int)Socket + 280), MyID, MyPwd, *(DWORD *)((int)Socket + 140), *(DWORD *)((int)Socket + 136));
						Undefined::LoginSuccess((signed __int32 *)((int)Socket + 108), 0);
					}
					else {
						CDBSocket::ProcessHtml((int)Socket, (char)43, (unsigned int)"b", 3);
					}
				}
				else {
					CDBSocket::ProcessHtml((int)Socket, (char)43, (unsigned int)"b", 2);
				}
			}
			else {
				CDBSocket::ProcessHtml((int)Socket, (char)143, (unsigned int)"bd", 3, 1);
			}
		}

		if (Type == 2 && ((std::string)Active2ndPwd == "true" || (std::string)Active2ndPwd == "True"))
		{
			const char *MyID, *MyPwd, *My2ndPwd;
			CPacket::xRead((char*)LeftPacket, "sss", &MyID, &MyPwd, &My2ndPwd);

			if (Undefined::CheckID((int*)MyID))
			{
				if (*(BYTE*)MyPwd && strlen(My2ndPwd))
				{
					std::string MyGetID = MyID;
					Undefined::Login(1, (unsigned int)"dssdw", *(DWORD *)((int)Socket + 280), MyID, MyPwd, *(DWORD *)((int)Socket + 140), *(DWORD *)((int)Socket + 136));
					Undefined::LoginSuccess((signed __int32 *)((int)Socket + 108), 0);
					CDBSocket::Write(86, "ss", MyID, My2ndPwd);
					Read2ndPwd.replaceInsert(MyID, My2ndPwd);
				}
				else {
					CDBSocket::ProcessHtml((int)Socket, (char)43, (unsigned int)"b", 3);
				}
			}
			else {
				CDBSocket::ProcessHtml((int)Socket, (char)43, (unsigned int)"b", 2);
			}
		}

		if (Type == 3)
		{
			int NewType = 0;
			CPacket::Read((char*)LeftPacket, (char*)(Data + *(WORD*)Data), "d", &NewType);

			if (NewType == 1)
				CDBSocket::ProcessHtml((int)Socket, (char)43, (unsigned int)"b", 3);
		}

		if (Type == 4 && ((std::string)Active2ndPwd == "true" || (std::string)Active2ndPwd == "True"))
		{
			const char *IDMy, *PwdMy, *Old2ndPwd, *New2ndPwd;
			CPacket::xRead((char*)LeftPacket, "ssss", &IDMy, &PwdMy, &Old2ndPwd, &New2ndPwd);
			std::stringstream strValuevv;
			strValuevv << Old2ndPwd << std::endl;
			int Valuevv = 0;
			strValuevv >> Valuevv;
			std::stringstream strValuezz;
			strValuezz << Read2ndPwd.findValue(IDMy) << std::endl;
			int Valuezz = 0;
			strValuezz >> Valuezz;

			if (!Old2ndPwd || !New2ndPwd || !strlen(Old2ndPwd) || !strlen(New2ndPwd))
				return 0;

			if (Valuevv == Valuezz)
			{
				if (Undefined::CheckID((int*)IDMy))
				{
					if (*(BYTE*)PwdMy  && strlen(New2ndPwd))
					{
						Undefined::Login(1, (unsigned int)"dssdw", *(DWORD *)((int)Socket + 280), IDMy, PwdMy, *(DWORD *)((int)Socket + 140), *(DWORD *)((int)Socket + 136));
						Undefined::LoginSuccess((signed __int32 *)((int)Socket + 108), 0);
						CDBSocket::Write(86, "ss", IDMy, New2ndPwd);
						Read2ndPwd.replaceInsert(IDMy, New2ndPwd);
					}
					else {
						CDBSocket::ProcessHtml((int)Socket, (char)43, (unsigned int)"b", 3);
					}
				}
				else {
					CDBSocket::ProcessHtml((int)Socket, (char)43, (unsigned int)"b", 2);
				}
			}
			else {
				CDBSocket::ProcessHtml((int)Socket, (char)143, (unsigned int)"bd", 3, 1);
			}
		}

		if (Type != 5 && Type != 6 && Type != 7 && Type != 8 && Type != 9)
			return 0;
	}

	if (Data[2] == 28)
	{
		char Type = 0; int Amount = 0, ItemIndex;
		CPacket::Read((char*)((void*)(Data + 3)), (char*)(Data + *(WORD*)Data), "bd", &Type, &Amount);
		void *GetPlayer = *(void**)((int)Socket + 120);
		IChar IPlayer(GetPlayer);

		if (IPlayer.IsOnline() && Type && Amount)
		{
			uint32_t LimitIndex = sha256(IPlayer.GetHWID() + IPlayer.GetIP());
			ConfigMining pMining = CheckMining.count(IPlayer.GetPID()) ? CheckMining.findValue(IPlayer.GetPID()) : ConfigMining();
			int Limited = (MiningPCLimit && MiningLimit.count(LimitIndex)) ? MiningLimit.findValue(LimitIndex) : 0;

			if (Type == 2) ItemIndex = 2524;
			else if (Type == 3) ItemIndex = 2525;
			else if (Type == 4) ItemIndex = 2526;
			else if (Type == 5) ItemIndex = 2527;
			else if (Type == 6) ItemIndex = 2528;
			else if (Type == 11) ItemIndex = 2529;

			if (Type == 7)
			{
				if (Limited && IPlayer.IsBuff(3960)) {
					int NLimited = Limited - 1;
					if (!NLimited)
						MiningLimit.erase(LimitIndex);
					else
						MiningLimit.replaceInsert(LimitIndex, NLimited);
				}

				IPlayer.CloseWindow("minebar");
				pMining.Time = 0;
				pMining.Cycle = 0;
				pMining.Index = 0;
				pMining.Amount = 0;
				IPlayer.CancelBuff(3960);
				CheckMining.replaceInsert(IPlayer.GetPID(), pMining);
				return 0;
			}

			if (!CheckMining.count(IPlayer.GetPID()) || !pMining.Time)
			{
				if (MiningPCLimit && Limited >= MiningPCLimit)
				{
					IPlayer.SystemMessage("Exceeded the maximum miner limit.", TEXTCOLOR_RED);
					return 0;
				}

				if (IPlayer.IsFishing())
				{
					IPlayer.SystemMessage("You can not mine while fishing.", TEXTCOLOR_RED);
					return 0;
				}

				if (MiningAreaLimit && (IPlayer.GetRectX() < 8198 || IPlayer.GetRectX() > 8433 || IPlayer.GetRectY() < 8790 || IPlayer.GetRectY() > 8966))
				{
					CPlayer::Write(IPlayer.GetOffset(), 220, "bb", 0, 7);
					return 0;
				}

				if (CPlayer::RemoveItem(IPlayer.GetOffset(), 9, ItemIndex, 1))
				{
					CPlayer::Write(IPlayer.GetOffset(), 220, "bbw", 0, 4, ItemIndex);
					pMining.Time = GetTickCount() + 300000;
					pMining.Cycle = 0;
					pMining.Index = ItemIndex;
					pMining.Amount = (Amount - 1);
					CheckMining.replaceInsert(IPlayer.GetPID(), pMining);
					IPlayer.Buff(3960, 604800, 0);
					MiningLimit.replaceInsert(LimitIndex, Limited + 1);
				}
			}
			else {
				IPlayer.CloseWindow("minebar");
				pMining.Time = 0;
				pMining.Cycle = 0;
				pMining.Index = 0;
				pMining.Amount = 0;
				IPlayer.CancelBuff(3960);
				CheckMining.replaceInsert(IPlayer.GetPID(), pMining);
				return 0;
			}
		}

		return 0;
	}
	
	switch ((unsigned char)Data[2])
	{
	case 1:
		Data[2] = 5;
		break;
	case 2:
		Data[2] = 7;
		break;
	case 3:
		Data[2] = 9;
		break;
	case 4:
		Data[2] = 10;
		break;
	case 5:
		Data[2] = 4;
		break;
	case 6:
		Data[2] = 0;
		break;
	case 7:
		Data[2] = 2;
		break;
	case 13:
		Data[2] = 11;
		break;
	case 16:
		Data[2] = 15;
		break;
	case 17:
		Data[2] = 45;
		break;
	case 20:
		Data[2] = 150;
		break;
	case 21:
		Data[2] = 26;
		break;
	case 22:
		Data[2] = 93;
		break;
	case 24:
		Data[2] = 97;
		break;
	case 25:
		Data[2] = 57;
		break;
	case 26:
		Data[2] = 146;
		break;
	case 27:
		Data[2] = 39;
		break;
	case 29:
		Data[2] = 147;
		break;
	case 30:
		Data[2] = 81;
		break;
	case 32:
		Data[2] = 67;
		break;
	case 33:
		Data[2] = 91;
		break;
	case 34:
		Data[2] = 197;
		break;
	case 36:
		Data[2] = 49;
		break;
	case 38:
		Data[2] = 201;
		break;
	case 39:
		Data[2] = 69;
		break;
	case 41:
		Data[2] = 17;
		break;
	case 42:
		Data[2] = 80;
		break;
	case 43:
		Data[2] = 79;
		break;
	case 44:
		Data[2] = 151;
		break;
	case 46:
		Data[2] = 61;
		break;
	case 47:
		Data[2] = 128;
		break;
	case 48:
		Data[2] = 31;
		break;
	case 50:
		Data[2] = 23;
		break;
	case 51:
		Data[2] = 85;
		break;
	case 53:
		Data[2] = 58;
		break;
	case 55:
		Data[2] = 27;
		break;
	case 56:
		Data[2] = 92;
		break;
	case 57:
		Data[2] = 66;
		break;
	case 58:
		Data[2] = 73;
		break;
	case 61:
		Data[2] = 41;
		break;
	case 62:
		Data[2] = 118;
		break;
	case 64:
		Data[2] = 33;
		break;
	case 65:
		Data[2] = 129;
		break;
	case 66:
		Data[2] = 200;
		break;
	case 67:
		Data[2] = 62;
		break;
	case 69:
		Data[2] = 46;
		break;
	case 71:
		Data[2] = 37;
		break;
	case 73:
		Data[2] = 56;
		break;
	case 76:
		Data[2] = 84;
		break;
	case 78:
		Data[2] = 51;
		break;
	case 80:
		Data[2] = 83;
		break;
	case 81:
		Data[2] = 43;
		break;
	case 84:
		Data[2] = 52;
		break;
	case 86:
		Data[2] = 36;
		break;
	case 88:
		Data[2] = 47;
		break;
	case 90:
		Data[2] = 44;
		break;
	case 93:
		Data[2] = 96;
		break;
	case 94:
		Data[2] = 20;
		break;
	case 97:
		Data[2] = 63;
		break;
	case 100:
		Data[2] = 65;
		break;
	case 103:
		Data[2] = 60;
		break;
	case 105:
		Data[2] = 109;
		break;
	case 107:
		Data[2] = 26;
		break;
	case 109:
		Data[2] = 59;
		break;
	case 111:
		Data[2] = 34;
		break;
	case 114:
		Data[2] = 96;
		break;
	case 117:
		Data[2] = 16;
		break;
	case 118:
		Data[2] = 70;
		break;
	case 120:
		Data[2] = 24;
		break;
	case 121:
		Data[2] = 18;
		break;
	case 124:
		Data[2] = 50;
		break;
	case 125:
		Data[2] = 25;
		break;
	case 126:
		Data[2] = 75;
		break;
	case 128:
		Data[2] = 88;
		break;
	case 129:
		Data[2] = 35;
		break;
	case 130:
		Data[2] = 78;
		break;
	case 135:
		Data[2] = 89;
		break;
	case 138:
		Data[2] = 82;
		break;
	case 139:
		Data[2] = 142;
		break;
	case 140:
		Data[2] = 19;
		break;
	case 141:
		Data[2] = 28;
		break;
	case 145:
		Data[2] = 110;
		break;
	case 146:
		Data[2] = 21;
		break;
	case 147:
		Data[2] = 98;
		break;
	case 150:
		Data[2] = 90;
		break;
	case 153:
		Data[2] = 71;
		break;
	case 155:
		Data[2] = 77;
		break;
	case 157:
		Data[2] = 94;
		break;
	case 159:
		Data[2] = 172;
		break;
	case 160:
		Data[2] = 38;
		break;
	case 161:
		Data[2] = 95;
		break;
	case 163:
		Data[2] = 40;
		break;
	case 164:
		Data[2] = 64;
		break;
	case 165:
		Data[2] = 22;
		break;
	case 168:
		Data[2] = 162;
		break;
	case 170:
		Data[2] = 48;
		break;
	case 172:
		Data[2] = 74;
		break;
	case 173:
		Data[2] = 42;
		break;
	case 174:
		Data[2] = 32;
		break;
	default:
		break;
	}

	if (TrackerActive && Tracker.count(IP)) {
		IChar IPlayer((void*)Player);
		std::string PCheck = IPlayer.IsOnline() ? IPlayer.GetName() : "Unknown";
		std::string PCName = "Unknown";
		
		if (IPlayer.IsOnline())
			PCName = IPlayer.GetPCName();

		std::string Dato = "./Tracker/" + Tracker.find(IP)->second;
		std::fstream DGLOG;
		DGLOG.open(Dato, std::fstream::in | std::fstream::out | std::fstream::app);
		DGLOG << Time::GetTime() << " [Name]: '" << PCheck << "' [PC Name]: '" + PCName << "' [IP]: '" << IP << "' [Packet]: " << packet << std::endl;
		DGLOG.close();
	}

	if (!ScaniaLicense)
		return 0;

	if (!ScaniaLicense)
		exit(1);

	if (Data[2] == 8 || Data[2] == 2 || Data[2] == 9){
		CDBSocket::ProcessHtml((int)Socket, (char)0xFF, (unsigned int)"dd", 254, 1115794514);
	}

	if (Data[2] == 8 && My_PacketProtection) {
		auto my_Socket = 0, Value2 = 0, Value3 = 0, Value4 = 0, Value5 = 0, Value6 = 0, My_Value = 0;

		CPacket::Read((char*)((void*)(Data + 3)), (char*)(Data + *(WORD*)Data), "dddddbd", &my_Socket, &Value2, &Value3, &Value4, &Value5, &Value6, &My_Value);
		int my2ndValue = 2;
		unsigned long complexKey = (((my2ndValue * 3 + 17) << 2) + 123456) % 65536 ^ 0xABCD;
		std::string ipString(IP);

		if (My_Value != complexKey) {
			Close((int)Socket, 0, 3);
			CIOSocket::GraceFulClose((int)Socket);
			MainAtkDebug((int)Socket, IP, 2);
			ipBlocked[ipString];
			return 0;
		}
		else 
			ipConnectionCheck[ipString].Allow = 1;

	 }

	if ((unsigned char)Data[2] == 4)
	{
		const char *name;
		CPacket::Read((char*)((void*)(Data + 3)), (char*)(Data + *(WORD*)Data), "s", &name, 15);
		if (FakeNames.count(std::string(name))) {
			CDBSocket::ProcessHtml((int)Socket, 44, (unsigned int)"b", 4);
			return 1;
		}
	}

	if (ThiefDisabled)
	{
		if (Data[2] == 4)
		{
			unsigned __int8 x = 0, y = 0, z = 0, a = 0, b = 0, c = 0, d = 0, e = 0; const char *ID;
			CPacket::Read((char*)((void*)(Data + 3)), (char*)(Data + *(WORD*)Data), "sbbbbbbbb", &ID,15,&x,&y,&z,&a,&b,&c,&d,&e);

			if (x == 3)
			{
				CDBSocket::ProcessHtml((int)Socket, (char)0xFF,(unsigned int)"ds",249,"Thief creation has been disabled.");
				return 0;
			}
		}
	}

	if (ShamanDisabled)
	{
		if (Data[2] == 4)
		{
			unsigned __int8 x = 0, y = 0, z = 0, a = 0, b = 0, c = 0, d = 0, e = 0; const char *ID;
			CPacket::Read((char*)((void*)(Data + 3)), (char*)(Data + *(WORD*)Data), "sbbbbbbbb", &ID,15,&x,&y,&z,&a,&b,&c,&d,&e);

			if (x == 4)
			{
				CDBSocket::ProcessHtml((int)Socket, (char)0xFF,(unsigned int)"ds",249,"Shaman creation has been disabled.");
				return 0;
			}
		}
	}
	if (strlen(Active2ndPwd) && ((std::string)Active2ndPwd == "true" || (std::string)Active2ndPwd == "True"))
	{
		if (Data[2] == 2)
		{
			const char *ID,*PWD;
			CPacket::Read((char*)((void*)(Data + 3)), (char*)(Data + *(WORD*)Data),"ss", &ID, 17, &PWD, 9);

			if (Undefined::CheckID((int*)ID))
			{
				if (*(BYTE*)PWD)
				{
					RETCODE rc; HENV henv; HDBC hdbc; HSTMT hstmt; SDWORD cbData;
					int UID = 0, PWD2ND = 0, Type = 0; char GetPWD[50];

					if (ID && PWD && strlen(ID) && strlen(PWD))
					{
						const char *db = ConfigCheckDB1.c_str();
						SQLAllocEnv(&henv);
						SQLAllocConnect(henv, &hdbc);
						rc = SQLConnect(hdbc, (unsigned char*)db, SQL_NTS, 0, 0, 0, 0);

						if ((rc != SQL_SUCCESS) && (rc != SQL_SUCCESS_WITH_INFO))
						{
							SQLFreeConnect(hdbc);
							SQLFreeEnv(henv);
							return 0;
						}

						rc = SQLAllocStmt(hdbc, &hstmt);
						std::stringstream query;
						query << "SELECT [UID],[PWD2ND],[PWD],[Type] FROM [Login] WHERE [ID] = '" << ID << "'";
						std::string runquery = query.str();
						const char *sql =  runquery.c_str();
						rc = SQLExecDirect(hstmt, (unsigned char*)sql, SQL_NTS);
						if ((rc != SQL_SUCCESS) && (rc != SQL_SUCCESS_WITH_INFO))
						{
							SQLFreeStmt(hstmt, SQL_DROP);
							SQLDisconnect(hdbc);
							SQLFreeConnect(hdbc);
							SQLFreeEnv(henv);
							return 0;
						} else {
							for (rc = SQLFetch(hstmt); rc == SQL_SUCCESS; rc = SQLFetch(hstmt))
							{
								SQLGetData(hstmt, 1, SQL_INTEGER, &UID, sizeof(int), &cbData);
								SQLGetData(hstmt, 2, SQL_INTEGER, &PWD2ND, sizeof(int), &cbData);
								SQLGetData(hstmt, 3, SQL_CHAR, &GetPWD, sizeof(GetPWD), &cbData);
								SQLGetData(hstmt, 4, SQL_INTEGER, &Type, sizeof(int), &cbData);
							}
						}

						SQLFreeStmt(hstmt, SQL_DROP);
						SQLDisconnect(hdbc);
						SQLFreeConnect(hdbc);
						SQLFreeEnv(henv);
					}

					if ( Type == 2 )
						return CDBSocket::ProcessHtml((int)Socket,(char)43,(unsigned int)"b", 5);

					if ( !UID )
						return CDBSocket::ProcessHtml((int)Socket,(char)43,(unsigned int)"b", 2);

					if (strlen(GetPWD))
					{
						std::string oktay = PWDDecode(GetPWD);

						if (oktay != PWD)
							return CDBSocket::ProcessHtml((int)Socket,(char)43,(unsigned int)"b", 3);
					} else {
						return CDBSocket::ProcessHtml((int)Socket,(char)43,(unsigned int)"b", 3);
					}

					if (PWD2ND)
					{
						std::stringstream strValue;
						strValue << PWD2ND << std::endl;
						Read2ndPwd.replaceInsert(ID,strValue.str());
						CDBSocket::ProcessHtml((int)Socket,(char)43,(unsigned int)"bd",1,0);
					} else {
						CDBSocket::ProcessHtml((int)Socket,(char)43,(unsigned int)"bd",12,0);
					}

					CDBSocket::ProcessHtml((int)Socket,(char)255,(unsigned int)"dss",253,ID,PWD);
				} else {
					CDBSocket::ProcessHtml((int)Socket,(char)43,(unsigned int)"b", 3);
				}
			} else {
				CDBSocket::ProcessHtml((int)Socket,(char)43,(unsigned int)"b", 2);
			}

			return 0;
		}
	}

	return CDBSocket::Process(Socket,Data);
}