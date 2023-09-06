void __fastcall SendList(void *pSocket, void *_edx, char* Packet)
{
	char* aPacket = Packet;
	Interface<ITools> Tools;
	Packet += 3;
	char nType = Packet[0];
	unsigned char fCount = Packet[1];
	Packet += 2;
	char *offset = Packet;

	size_t nSize = 0;
	for (unsigned char i = 0; i < fCount; i++)
	{
		char* name;
		int id;
		offset = (char*)CPacket::Read(offset, (char*)(aPacket + *(WORD*)aPacket), "ds", &id, &name);
		nSize += 4 + strlen(name) + 1 + 1 + 4 + 1 + 1;
	}

	char *nPacket = new char[nSize];
	offset = nPacket;

	for (unsigned char i = 0; i < fCount; i++)
	{
		char* name;
		int id;
		Packet = (char*)CPacket::Read(Packet, (char*)(aPacket + *(WORD*)aPacket), "ds", &id, &name);
		TargetFind myTarget(name);
		long *pFriend = (long*)myTarget.getTarget();

		bool online = false;
		if (pFriend || (EFakePlayers && FakeNames.count(name)))
			online = true;

		offset = Tools->Compile(offset, "dsbdb", id, name, online, pFriend ? pFriend[0x1c] : 0, 0);
	}
	CDBSocket::ProcessHtml((int)pSocket, 0x12, (int)"bbm", 2, fCount, nPacket, nSize);
	delete[] nPacket;

	CIOBuffer::Free(aPacket);
}

void __cdecl SendAdd(void *vPlayer, unsigned char pType, char* pFormat, char fType, long id, char* name, char type)
{
	TargetFind myTarget(name);
	long *pFriend = (long*)myTarget.getTarget();

	CPlayer::Write(vPlayer, 0x12, "bdsbdb", 0, id, name, pFriend ? true : false, pFriend ? pFriend[0x1c] : 0, 0);
}

void __fastcall SendAssassinList(void *pSocket, void *_edx, char* pData)
{
	char* Data = pData;
	//CIOBuffer::CSocket___CSocket(pSocket, Data);
	struct PKInfo { char Guild[16 + 1], Killer[20 + 1], Dead[20 + 1]; };
	unsigned char nCount = pData[3];
	pData += 4;
	char* nData = new char[nCount * sizeof PKInfo];

	for (unsigned char i = 0; i < nCount; i++)
	{
		PKInfo nf;
		ZeroMemory(&nf, sizeof PKInfo);

		CopyMemory(nf.Guild, &pData[i * 51], 16);
		CopyMemory(nf.Killer, &pData[i * 51 + 17], 16);
		CopyMemory(nf.Dead, &pData[i * 51 + 34], 16);

		CopyMemory(&nData[i * sizeof PKInfo], &nf, sizeof PKInfo);
	}

	CDBSocket::ProcessHtml((int)pSocket, 0x0c, (int)"bm", nCount, nData, nCount * sizeof PKInfo);
	delete[] nData;

	CIOBuffer::Free(Data);
}

void __fastcall ModsItemPutInfo(void *_this, void *_edx, char **spec, int a3)
{
	unsigned long *v4 = (unsigned long*)_this;
	if (!a3) a3 = v4[13];
	*spec = CItem::PutDword(*spec, v4[9]);
	*spec = CItem::PutWord(*spec, *(short*)(v4[10] + 64));
	int v3;
	if (v4[11]) v3 = *(int*)(v4[11] + 32);
	else v3 = 0;
	*spec = CItem::PutByte(*spec, v3);
	*spec = CItem::PutDword(*spec, v4[12]);
	*spec = CItem::PutDword(*spec, a3);

	for (int i = 0; i < 11; i++)
		*spec = CItem::PutByte(*spec, 0);
}

void __fastcall ModsSendStallList(void *player, void *_edx, char* packet)
{
	char* pack = packet;
	Interface<ITools> Tools;
	unsigned char type, pType, Items;
	unsigned long id, version;

	packet = (char*)CPacket::Read((char*)((void*)(packet + 2)), (char*)(pack + *(WORD*)pack), "bbddb", &type, &pType, &id, &version, &Items);

	//packet = (char*)CPacket::xRead(packet + 2, "bbddb", &type, &pType, &id, &version, &Items);
	size_t Size = Items * 71;
	char *Packet = new char[Size];

	TargetFind myTarget(0, 0, id);
	void *GetPlayer = myTarget.getTarget();
	if (!CBase::IsDeleted((int)GetPlayer)) {
		int Class = *(DWORD*)((int)GetPlayer + 460);
		IChar IPlayer(GetPlayer);
		for (unsigned char i = 0; i < Items; i++)
		{
			unsigned short index;
			unsigned long iid;
			unsigned char prefix;
			unsigned long info, amount;
			unsigned char maxend, curend, setgem, xatk, xmagic, xdefense, xhit, xevasion;
			unsigned short xprotect;
			unsigned char upgrlvl, upgrrate;
			unsigned long price;
			unsigned char x = 0, y = 0, z = 0, dsstype = 0, eva = 0, otp = 0, hpinc = 0, mpinc = 0, str = 0, hp = 0, intel = 0, wis = 0, agi = 0, a = 0, dg1stat = 0, dg1type = 0, dg2stat = 0, dg2type = 0, PerfShotCheck = 0;
			unsigned long remaintime = 0, QigongGrade = 0;
			unsigned short phyatk = 0, magatk = 0, def = 0, absorb = 0;

			packet = (char*)CPacket::Read(packet, (char*)(pack + *(WORD*)pack), "dwbddbbbbbbbbbbbd", &iid, &index, &prefix, &info, &amount, &maxend, &curend, &setgem, &xatk,
				&xmagic, &xdefense, &xhit, &xevasion, &xprotect, &upgrlvl, &upgrrate, &price);

			int Item = IPlayer.ItemPointer(iid);
			int ItemStat = 0;
			itemStat.Enter();
			if (GetItemStat.count(iid))
				ItemStat = GetItemStat.find(iid)->second;
			itemStat.Leave();
			int GetStat = ItemStat;

			if (Item)
			{
				IItem IItem((void*)Item);

				if (IItem.GetType() == -2 || IItem.GetType() == 19 || IItem.GetType() == 0 || IItem.GetType() == -3 || IItem.GetType() == -1)
				{
					if (setgem == 240)
					{
						dsstype = 1; phyatk = 17; magatk = 17; agi = 8;
						hpinc = 250; mpinc = 200;
						if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 18; else otp = 18;
					}
					else if (setgem == 239)
					{
						dsstype = 1; phyatk = 17; magatk = 17; wis = 8;
						hpinc = 250; mpinc = 200;
						if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 18; else otp = 18;
					}
					else if (setgem == 238)
					{
						dsstype = 1; phyatk = 17; magatk = 17; intel = 8;
						hpinc = 250; mpinc = 200;
						if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 18; else otp = 18;
					}
					else if (setgem == 237)
					{
						dsstype = 1; phyatk = 17; magatk = 17; hp = 8;
						hpinc = 250; mpinc = 200;
						if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 18; else otp = 18;
					}
					else if (setgem == 236)
					{
						dsstype = 1; phyatk = 17; magatk = 17; str = 8;
						hpinc = 250; mpinc = 200;
						if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 18; else otp = 18;
					}
					else if (setgem == 235)
					{
						dsstype = 2; phyatk = 14; magatk = 14; agi = 5;
						hpinc = 200; mpinc = 150;
						if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 15; else otp = 15;
					}
					else if (setgem == 234)
					{
						dsstype = 2; phyatk = 14; magatk = 14; wis = 5;
						hpinc = 200; mpinc = 150;
						if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 15; else otp = 15;
					}
					else if (setgem == 233)
					{
						dsstype = 2; phyatk = 14; magatk = 14; intel = 5;
						hpinc = 200; mpinc = 150;
						if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 15; else otp = 15;
					}
					else if (setgem == 232)
					{
						dsstype = 2; phyatk = 14; magatk = 14; hp = 5;
						hpinc = 200; mpinc = 150;
						if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 15; else otp = 15;
					}
					else if (setgem == 231)
					{
						dsstype = 2; phyatk = 14; magatk = 14; str = 5;
						hpinc = 200; mpinc = 150;
						if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 15; else otp = 15;
					}
					else if (setgem == 230)
					{
						dsstype = 3; phyatk = 12; magatk = 12; agi = 3;
						hpinc = 130; mpinc = 110;
						if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 12; else otp = 12;
					}
					else if (setgem == 229)
					{
						dsstype = 3; phyatk = 12; magatk = 12; wis = 3;
						hpinc = 130; mpinc = 110;
						if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 12; else otp = 12;
					}
					else if (setgem == 228)
					{
						dsstype = 3; phyatk = 12; magatk = 12; intel = 3;
						hpinc = 130; mpinc = 110;
						if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 12; else otp = 12;
					}
					else if (setgem == 227)
					{
						dsstype = 3; phyatk = 12; magatk = 12; hp = 3;
						hpinc = 130; mpinc = 110;
						if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 12; else otp = 12;
					}
					else if (setgem == 226)
					{
						dsstype = 3; phyatk = 12; magatk = 12; str = 3;
						hpinc = 130; mpinc = 110;
						if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 12; else otp = 12;
					}
					else if (setgem == 225)
					{
						dsstype = 4; phyatk = 10; magatk = 10; agi = 3;
						hpinc = 110; mpinc = 90;
						if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 10; else otp = 10;
					}
					else if (setgem == 224)
					{
						dsstype = 4; phyatk = 10; magatk = 10; wis = 3;
						hpinc = 110; mpinc = 90;
						if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 10; else otp = 10;
					}
					else if (setgem == 223)
					{
						dsstype = 4; phyatk = 10; magatk = 10; intel = 3;
						hpinc = 110; mpinc = 90;
						if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 10; else otp = 10;
					}
					else if (setgem == 222)
					{
						dsstype = 4; phyatk = 10; magatk = 10; hp = 3;
						hpinc = 110; mpinc = 90;
						if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 10; else otp = 10;
					}
					else if (setgem == 221)
					{
						dsstype = 4; phyatk = 10; magatk = 10; str = 3;
						hpinc = 110; mpinc = 90;
						if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 10; else otp = 10;
					}
					else if (setgem == 220)
					{
						dsstype = 5; phyatk = 8; magatk = 8; agi = 2;
						hpinc = 90; mpinc = 70;
						if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 8; else otp = 8;
					}
					else if (setgem == 219)
					{
						dsstype = 5; phyatk = 8; magatk = 8; wis = 2;
						hpinc = 90; mpinc = 70;
						if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 8; else otp = 8;
					}
					else if (setgem == 218)
					{
						dsstype = 5; phyatk = 8; magatk = 8; intel = 2;
						hpinc = 90; mpinc = 70;
						if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 8; else otp = 8;
					}
					else if (setgem == 217)
					{
						dsstype = 5; phyatk = 8; magatk = 8; hp = 2;
						hpinc = 90; mpinc = 70;
						if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 8; else otp = 8;
					}
					else if (setgem == 216)
					{
						dsstype = 5; phyatk = 8; magatk = 8; str = 2;
						hpinc = 90; mpinc = 70;
						if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 8; else otp = 8;
					}
					else if (setgem == 215)
					{
						dsstype = 6; phyatk = 6; magatk = 6; agi = 2;
						hpinc = 70; mpinc = 50;
						if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 6; else otp = 6;
					}
					else if (setgem == 214)
					{
						dsstype = 6; phyatk = 6; magatk = 6; wis = 2;
						hpinc = 70; mpinc = 50;
						if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 6; else otp = 6;
					}
					else if (setgem == 213)
					{
						dsstype = 6; phyatk = 6; magatk = 6; intel = 2;
						hpinc = 70; mpinc = 50;
						if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 6; else otp = 6;
					}
					else if (setgem == 212)
					{
						dsstype = 6; phyatk = 6; magatk = 6; hp = 2;
						hpinc = 70; mpinc = 50;
						if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 6; else otp = 6;
					}
					else if (setgem == 211)
					{
						dsstype = 6; phyatk = 6; magatk = 6; str = 2;
						hpinc = 70; mpinc = 50;
						if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 6; else otp = 6;
					}
					else if (setgem == 210)
					{
						dsstype = 7; phyatk = 4; magatk = 4; agi = 1;
						hpinc = 50; mpinc = 30;
						if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 4; else otp = 4;
					}
					else if (setgem == 209)
					{
						dsstype = 7; phyatk = 4; magatk = 4; wis = 1;
						hpinc = 50; mpinc = 30;
						if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 4; else otp = 4;
					}
					else if (setgem == 208)
					{
						dsstype = 7; phyatk = 4; magatk = 4; intel = 1;
						hpinc = 50; mpinc = 30;
						if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 4; else otp = 4;
					}
					else if (setgem == 207)
					{
						dsstype = 7; phyatk = 4; magatk = 4; hp = 1;
						hpinc = 50; mpinc = 30;
						if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 4; else otp = 4;
					}
					else if (setgem == 206)
					{
						dsstype = 7; phyatk = 4; magatk = 4; str = 1;
						hpinc = 50; mpinc = 30;
						if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 4; else otp = 4;
					}
					else if (setgem == 205)
					{
						dsstype = 8; phyatk = 2; magatk = 2; agi = 1;
						hpinc = 30; mpinc = 10;
						if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 2; else otp = 2;
					}
					else if (setgem == 204)
					{
						dsstype = 8; phyatk = 2; magatk = 2; wis = 1;
						hpinc = 30; mpinc = 10;
						if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 2; else otp = 2;
					}
					else if (setgem == 203)
					{
						dsstype = 8; phyatk = 2; magatk = 2; intel = 1;
						hpinc = 30; mpinc = 10;
						if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 2; else otp = 2;
					}
					else if (setgem == 202)
					{
						dsstype = 8; phyatk = 2; magatk = 2; hp = 1;
						hpinc = 30; mpinc = 10;
						if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 2; else otp = 2;
					}
					else if (setgem == 201)
					{
						dsstype = 8; phyatk = 2; magatk = 2; str = 1;
						hpinc = 30; mpinc = 10;
						if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 2; else otp = 2;
					}
				}

				if (IItem.GetType() >= 1 && IItem.GetType() <= 6)
				{
					if (setgem == 240)
					{
						dsstype = 1; def = 18; agi = 7;
					}
					else if (setgem == 239)
					{
						dsstype = 1; def = 18; wis = 7;
					}
					else if (setgem == 238)
					{
						dsstype = 1; def = 18; intel = 7;
					}
					else if (setgem == 237)
					{
						dsstype = 1; def = 18; hp = 7;
					}
					else if (setgem == 236)
					{
						dsstype = 1; def = 18; str = 7;
					}
					else if (setgem == 235)
					{
						dsstype = 2; def = 16; agi = 5;
					}
					else if (setgem == 234)
					{
						dsstype = 2; def = 16; wis = 5;
					}
					else if (setgem == 233)
					{
						dsstype = 2; def = 16; intel = 5;
					}
					else if (setgem == 232)
					{
						dsstype = 2; def = 16; hp = 5;
					}
					else if (setgem == 231)
					{
						dsstype = 2; def = 16; str = 5;
					}
					else if (setgem == 230)
					{
						dsstype = 3; def = 14; agi = 3;
					}
					else if (setgem == 229)
					{
						dsstype = 3; def = 14; wis = 3;
					}
					else if (setgem == 228)
					{
						dsstype = 3; def = 14; intel = 3;
					}
					else if (setgem == 227)
					{
						dsstype = 3; def = 14; hp = 3;
					}
					else if (setgem == 226)
					{
						dsstype = 3; def = 14; str = 3;
					}
					else if (setgem == 225)
					{
						dsstype = 4; def = 12; agi = 3;
					}
					else if (setgem == 224)
					{
						dsstype = 4; def = 12; wis = 3;
					}
					else if (setgem == 223)
					{
						dsstype = 4; def = 12; intel = 3;
					}
					else if (setgem == 222)
					{
						dsstype = 4; def = 12; hp = 3;
					}
					else if (setgem == 221)
					{
						dsstype = 4; def = 12; str = 3;
					}
					else if (setgem == 220)
					{
						dsstype = 5; def = 10; agi = 2;
					}
					else if (setgem == 219)
					{
						dsstype = 5; def = 10; wis = 2;
					}
					else if (setgem == 218)
					{
						dsstype = 5; def = 10; intel = 2;
					}
					else if (setgem == 217)
					{
						dsstype = 5; def = 10; hp = 2;
					}
					else if (setgem == 216)
					{
						dsstype = 5; def = 10; str = 2;
					}
					else if (setgem == 215)
					{
						dsstype = 6; def = 8; agi = 2;
					}
					else if (setgem == 214)
					{
						dsstype = 6; def = 8; wis = 2;
					}
					else if (setgem == 213)
					{
						dsstype = 6; def = 8; intel = 2;
					}
					else if (setgem == 212)
					{
						dsstype = 6; def = 8; hp = 2;
					}
					else if (setgem == 211)
					{
						dsstype = 6; def = 8; str = 2;
					}
					else if (setgem == 210)
					{
						dsstype = 7; def = 6; agi = 1;
					}
					else if (setgem == 209)
					{
						dsstype = 7; def = 6; wis = 1;
					}
					else if (setgem == 208)
					{
						dsstype = 7; def = 6; intel = 1;
					}
					else if (setgem == 207)
					{
						dsstype = 7; def = 6; hp = 1;
					}
					else if (setgem == 206)
					{
						dsstype = 7; def = 6; str = 1;
					}
					else if (setgem == 205)
					{
						dsstype = 8; def = 4; agi = 1;
					}
					else if (setgem == 204)
					{
						dsstype = 8; def = 4; wis = 1;
					}
					else if (setgem == 203)
					{
						dsstype = 8; def = 4; intel = 1;
					}
					else if (setgem == 202)
					{
						dsstype = 8; def = 4; hp = 1;
					}
					else if (setgem == 201)
					{
						dsstype = 8; def = 4; str = 1;
					}
				}
				if (isItemSuit(index) || isItemCustomWeapon(index) || isItemRiding(index)) {
					int GStat = GetStat;
					if (isBattleRiding(index)) {
						int Satiety = GStat / 100;
						if (Satiety)
							GStat -= (Satiety * 100);
					}

					int AddingType = SuitStats.count(index) ? SuitStats.find(index)->second.Type : 0;
					int Multiply = SuitStats.count(index) ? SuitStats.find(index)->second.Multiply : 3;

					if (Multiply < 2)
						Multiply = 2;

					switch (AddingType) {
					case 0:
						hp += GStat >= 6 ? (((GStat - 5) * Multiply) + 10) : GStat * (Multiply - 1);
						break;
					case 1:
						str += GStat >= 6 ? (((GStat - 5) * Multiply) + 10) : GStat * (Multiply - 1);
						break;
					case 2:
						hp += GStat >= 6 ? (((GStat - 5) * Multiply) + 10) : GStat * (Multiply - 1);
						break;
					case 3:
						intel += GStat >= 6 ? (((GStat - 5) * Multiply) + 10) : GStat * (Multiply - 1);
						break;
					case 4:
						wis += GStat >= 6 ? (((GStat - 5) * Multiply) + 10) : GStat * (Multiply - 1);
						break;
					case 5:
						agi += GStat >= 6 ? (((GStat - 5) * Multiply) + 10) : GStat * (Multiply - 1);
						break;
					default:
						hp += GStat >= 6 ? (((GStat - 5) * Multiply) + 10) : GStat * (Multiply - 1);
						break;
					}
				}
			}

			if (index >= 3381 && index <= 3383)
			{
				CPlayer::Write(player, 194, "dd", iid, 100);
				if (index == 3381) CPlayer::Write(player, 193, "ddd", iid, 101, 10);
				if (index == 3382) CPlayer::Write(player, 193, "ddd", iid, 101, 11);
				if (index == 3383) CPlayer::Write(player, 193, "ddd", iid, 101, 12);

				if (index == 3383 && !GetStat)
					CPlayer::Write(player, 193, "ddd", iid, 100, GetStat + 2);
				else
					CPlayer::Write(player, 193, "ddd", iid, 100, GetStat + 1);
			}

			if (index >= 3384 && index <= 3386)
			{
				if (GetStat)
				{
					int Stat = GetStat / 1000;
					int Value = GetStat % 100;
					CPlayer::Write(player, 194, "dd", iid, Value);
					CPlayer::Write(player, 193, "ddd", iid, Value, Stat);
				}
			}

			if (ItemStat)
			{
				PerfShotCheck = ItemStat / 100000000;
				ItemStat -= (100000000 * PerfShotCheck);
			}

			if (ItemStat)
			{
				int dg1typecheck = ItemStat / 10000000;
				if (dg1typecheck) dg1stat = 1;
				if (dg1typecheck > 0) dg1type = (dg1typecheck - 1);
				ItemStat -= (10000000 * dg1typecheck);
			}

			if (ItemStat)
			{
				int dg1statcheck = ItemStat / 1000000;
				if (dg1statcheck > 0) dg1stat = (dg1statcheck + 1);
				ItemStat -= (1000000 * dg1statcheck);
			}

			if (ItemStat)
			{
				int dg2typecheck = ItemStat / 100000;
				if (dg2typecheck) dg2stat = 1;
				if (dg2typecheck > 0) dg2type = (dg2typecheck - 1);
				ItemStat -= (100000 * dg2typecheck);
			}

			if (ItemStat)
			{
				int dg2statcheck = ItemStat / 10000;
				if (dg2statcheck > 0) dg2stat = (dg2statcheck + 1);
				ItemStat -= (10000 * dg2statcheck);
			}

			if (ItemStat && index >= 2986 && index <= 3009)
			{
				int yinyanggrade = ItemStat / 100;
				prefix = yinyanggrade + 1;
				ItemStat -= (100 * yinyanggrade);
			}

			if (ItemStat)
				QigongGrade = ItemStat % 100;

			if (index >= 3199 && index <= 3201 && prefix == 0)
				prefix = 1;

			if (index >= 2986 && index <= 3009 && prefix == 0)
				prefix = 1;

			if (index >= 3018 && index <= 3020 && GetStat)
				prefix = GetStat / 1000;

			int refill = 0;
			if (isSoulPocket(index)) {
				if (GetStat)
					refill = GetStat;
			}

			if (GetStat && (isItemCustomWeapon(index) || isItemSuit(index) || isItemRiding(index))) {
				int GStat = GetStat;
				if (isBattleRiding(index)) {
					int Satiety = GStat / 100;
					if (Satiety)
						GStat -= (Satiety * 100);
				}
				if (GStat)
					upgrlvl = GStat;
			}

			if (isItemRidingArmor(index)) {
				upgrlvl = GetStat;
				if (GetStat > 0 && GetStat <= 10 && GetBattleRidingGrade(index) > 0) {
					if (GetBattleRidingType(index) == 1) {
						if (index == 7883 || index == 7889 || index == 7895 || index == 7901)
							str += RidingHelmet[GetBattleRidingGrade(index) - 1][GetStat - 1];
						else
							intel += RidingHelmet[GetBattleRidingGrade(index) - 1][GetStat - 1];
					}
					if (GetBattleRidingType(index) == 2)
						hp += RidingSaddle[GetBattleRidingGrade(index) - 1][GetStat - 1];
					if (GetBattleRidingType(index) == 3)
						xdefense += RidingArmor[GetBattleRidingGrade(index) - 1][GetStat - 1];
					if (GetBattleRidingType(index) == 4)
						xdefense += RidingCloth[GetBattleRidingGrade(index) - 1][GetStat - 1];
					if (GetBattleRidingType(index) == 5)
						eva += RidingMagnet[GetBattleRidingGrade(index) - 1][GetStat - 1];
				}
			}

			int restorecount = RestoredIIDs.findExists(iid);

			int dg1 = (dg1type << 24) + (dg1stat << 16);
			int dg2 = (dg2type << 24) + (dg2stat << 16);

			remaintime = PetLifeCheck.findExists(iid);
			if (remaintime)
				remaintime -= (int)time(0);

			Tools->Compile(Packet + i * 71, "wdbddbbbbbbbbwbbdbbbbwwwwbbbbbbbbbbwdddd", index, iid, prefix, info, amount, maxend, curend, setgem, xatk, xmagic, xdefense, xhit, xevasion, xprotect, upgrlvl, upgrrate, remaintime, x, y, restorecount, dsstype, phyatk, magatk, def, absorb, eva, otp, hpinc, mpinc, str, hp, intel, wis, agi, PerfShotCheck, QigongGrade, dg1, dg2, refill, price);
		}

		CPlayer::Write(player, type, "bddbbm", pType, id, version, Items, 0, Packet, Size);
	}

	delete[] Packet;
}

void __fastcall ModsSendTradeList(void *player, void *_edx, char* packet)
{
	char* pack = packet;
	Interface<ITools> Tools;
	unsigned char type = packet[2];
	unsigned char Items = packet[3];
	packet += 4;
	size_t Size = Items * 67;
	char *Packet = new char[Size];
	void *GetPlayer = *(void**)((int)player + 120);
	int Class = *(DWORD*)((int)GetPlayer + 460);
	for (unsigned char i = 0; i < Items; i++)
	{
		unsigned short index;
		unsigned long iid;
		unsigned char prefix;
		unsigned long info, amount;
		unsigned char maxend, curend, setgem, xatk, xmagic, xdefense, xhit, xevasion;
		unsigned short xprotect;
		unsigned char upgrlvl, upgrrate;
		unsigned char x = 0, y = 0, z = 0, dsstype = 0, eva = 0, otp = 0, hpinc = 0, mpinc = 0, str = 0, hp = 0, intel = 0, wis = 0, agi = 0, a = 0, dg1stat = 0, dg1type = 0, dg2stat = 0, dg2type = 0, PerfShotCheck = 0;
		unsigned long remaintime = 0, QigongGrade = 0;
		unsigned short phyatk = 0, magatk = 0, def = 0, absorb = 0;

		packet = (char*)CPacket::Read(packet, (char*)(pack + *(WORD*)pack), "dwbddbbbbbbbbbbb", &iid, &index, &prefix, &info, &amount, &maxend, &curend, &setgem, &xatk,
			&xmagic, &xdefense, &xhit, &xevasion, &xprotect, &upgrlvl, &upgrrate);

		int CurrentPlayer = CTrade::GetOther(*(DWORD*)((int)GetPlayer + 1100), (int)GetPlayer);
		IChar IPlayer((void*)CurrentPlayer);
		IChar IPlayer2((void*)GetPlayer);

		int Itemxx = IPlayer.ItemPointer(iid);
		int ItemStat = 0;
		itemStat.Enter();
		if (GetItemStat.count(iid))
			ItemStat = GetItemStat.find(iid)->second;
		itemStat.Leave();
		int GetStat = ItemStat;

		if (Itemxx)
		{
			if (IPlayer.GetBuffValue(BuffNames::BetOpponent)) {
				BetTrade bet = BetTrade();
				bet.Item = Itemxx;
				bet.Amount = amount;
				bet.PID = *(DWORD *)(Itemxx + 32);
				itemBet.Enter();
				BetItems[IPlayer.GetPID() * IPlayer2.GetPID()].push_back(bet);
				itemBet.Leave();
			}

			IItem IItem((void*)Itemxx);

			if (IItem.GetType() == -2 || IItem.GetType() == 19 || IItem.GetType() == 0 || IItem.GetType() == -3 || IItem.GetType() == -1)
			{
				if (setgem == 240)
				{
					dsstype = 1; phyatk = 17; magatk = 17; agi = 8;
					hpinc = 250; mpinc = 200;
					if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 18; else otp = 18;
				}
				else if (setgem == 239)
				{
					dsstype = 1; phyatk = 17; magatk = 17; wis = 8;
					hpinc = 250; mpinc = 200;
					if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 18; else otp = 18;
				}
				else if (setgem == 238)
				{
					dsstype = 1; phyatk = 17; magatk = 17; intel = 8;
					hpinc = 250; mpinc = 200;
					if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 18; else otp = 18;
				}
				else if (setgem == 237)
				{
					dsstype = 1; phyatk = 17; magatk = 17; hp = 8;
					hpinc = 250; mpinc = 200;
					if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 18; else otp = 18;
				}
				else if (setgem == 236)
				{
					dsstype = 1; phyatk = 17; magatk = 17; str = 8;
					hpinc = 250; mpinc = 200;
					if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 18; else otp = 18;
				}
				else if (setgem == 235)
				{
					dsstype = 2; phyatk = 14; magatk = 14; agi = 5;
					hpinc = 200; mpinc = 150;
					if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 15; else otp = 15;
				}
				else if (setgem == 234)
				{
					dsstype = 2; phyatk = 14; magatk = 14; wis = 5;
					hpinc = 200; mpinc = 150;
					if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 15; else otp = 15;
				}
				else if (setgem == 233)
				{
					dsstype = 2; phyatk = 14; magatk = 14; intel = 5;
					hpinc = 200; mpinc = 150;
					if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 15; else otp = 15;
				}
				else if (setgem == 232)
				{
					dsstype = 2; phyatk = 14; magatk = 14; hp = 5;
					hpinc = 200; mpinc = 150;
					if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 15; else otp = 15;
				}
				else if (setgem == 231)
				{
					dsstype = 2; phyatk = 14; magatk = 14; str = 5;
					hpinc = 200; mpinc = 150;
					if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 15; else otp = 15;
				}
				else if (setgem == 230)
				{
					dsstype = 3; phyatk = 12; magatk = 12; agi = 3;
					hpinc = 130; mpinc = 110;
					if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 12; else otp = 12;
				}
				else if (setgem == 229)
				{
					dsstype = 3; phyatk = 12; magatk = 12; wis = 3;
					hpinc = 130; mpinc = 110;
					if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 12; else otp = 12;
				}
				else if (setgem == 228)
				{
					dsstype = 3; phyatk = 12; magatk = 12; intel = 3;
					hpinc = 130; mpinc = 110;
					if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 12; else otp = 12;
				}
				else if (setgem == 227)
				{
					dsstype = 3; phyatk = 12; magatk = 12; hp = 3;
					hpinc = 130; mpinc = 110;
					if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 12; else otp = 12;
				}
				else if (setgem == 226)
				{
					dsstype = 3; phyatk = 12; magatk = 12; str = 3;
					hpinc = 130; mpinc = 110;
					if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 12; else otp = 12;
				}
				else if (setgem == 225)
				{
					dsstype = 4; phyatk = 10; magatk = 10; agi = 3;
					hpinc = 110; mpinc = 90;
					if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 10; else otp = 10;
				}
				else if (setgem == 224)
				{
					dsstype = 4; phyatk = 10; magatk = 10; wis = 3;
					hpinc = 110; mpinc = 90;
					if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 10; else otp = 10;
				}
				else if (setgem == 223)
				{
					dsstype = 4; phyatk = 10; magatk = 10; intel = 3;
					hpinc = 110; mpinc = 90;
					if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 10; else otp = 10;
				}
				else if (setgem == 222)
				{
					dsstype = 4; phyatk = 10; magatk = 10; hp = 3;
					hpinc = 110; mpinc = 90;
					if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 10; else otp = 10;
				}
				else if (setgem == 221)
				{
					dsstype = 4; phyatk = 10; magatk = 10; str = 3;
					hpinc = 110; mpinc = 90;
					if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 10; else otp = 10;
				}
				else if (setgem == 220)
				{
					dsstype = 5; phyatk = 8; magatk = 8; agi = 2;
					hpinc = 90; mpinc = 70;
					if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 8; else otp = 8;
				}
				else if (setgem == 219)
				{
					dsstype = 5; phyatk = 8; magatk = 8; wis = 2;
					hpinc = 90; mpinc = 70;
					if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 8; else otp = 8;
				}
				else if (setgem == 218)
				{
					dsstype = 5; phyatk = 8; magatk = 8; intel = 2;
					hpinc = 90; mpinc = 70;
					if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 8; else otp = 8;
				}
				else if (setgem == 217)
				{
					dsstype = 5; phyatk = 8; magatk = 8; hp = 2;
					hpinc = 90; mpinc = 70;
					if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 8; else otp = 8;
				}
				else if (setgem == 216)
				{
					dsstype = 5; phyatk = 8; magatk = 8; str = 2;
					hpinc = 90; mpinc = 70;
					if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 8; else otp = 8;
				}
				else if (setgem == 215)
				{
					dsstype = 6; phyatk = 6; magatk = 6; agi = 2;
					hpinc = 70; mpinc = 50;
					if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 6; else otp = 6;
				}
				else if (setgem == 214)
				{
					dsstype = 6; phyatk = 6; magatk = 6; wis = 2;
					hpinc = 70; mpinc = 50;
					if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 6; else otp = 6;
				}
				else if (setgem == 213)
				{
					dsstype = 6; phyatk = 6; magatk = 6; intel = 2;
					hpinc = 70; mpinc = 50;
					if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 6; else otp = 6;
				}
				else if (setgem == 212)
				{
					dsstype = 6; phyatk = 6; magatk = 6; hp = 2;
					hpinc = 70; mpinc = 50;
					if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 6; else otp = 6;
				}
				else if (setgem == 211)
				{
					dsstype = 6; phyatk = 6; magatk = 6; str = 2;
					hpinc = 70; mpinc = 50;
					if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 6; else otp = 6;
				}
				else if (setgem == 210)
				{
					dsstype = 7; phyatk = 4; magatk = 4; agi = 1;
					hpinc = 50; mpinc = 30;
					if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 4; else otp = 4;
				}
				else if (setgem == 209)
				{
					dsstype = 7; phyatk = 4; magatk = 4; wis = 1;
					hpinc = 50; mpinc = 30;
					if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 4; else otp = 4;
				}
				else if (setgem == 208)
				{
					dsstype = 7; phyatk = 4; magatk = 4; intel = 1;
					hpinc = 50; mpinc = 30;
					if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 4; else otp = 4;
				}
				else if (setgem == 207)
				{
					dsstype = 7; phyatk = 4; magatk = 4; hp = 1;
					hpinc = 50; mpinc = 30;
					if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 4; else otp = 4;
				}
				else if (setgem == 206)
				{
					dsstype = 7; phyatk = 4; magatk = 4; str = 1;
					hpinc = 50; mpinc = 30;
					if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 4; else otp = 4;
				}
				else if (setgem == 205)
				{
					dsstype = 8; phyatk = 2; magatk = 2; agi = 1;
					hpinc = 30; mpinc = 10;
					if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 2; else otp = 2;
				}
				else if (setgem == 204)
				{
					dsstype = 8; phyatk = 2; magatk = 2; wis = 1;
					hpinc = 30; mpinc = 10;
					if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 2; else otp = 2;
				}
				else if (setgem == 203)
				{
					dsstype = 8; phyatk = 2; magatk = 2; intel = 1;
					hpinc = 30; mpinc = 10;
					if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 2; else otp = 2;
				}
				else if (setgem == 202)
				{
					dsstype = 8; phyatk = 2; magatk = 2; hp = 1;
					hpinc = 30; mpinc = 10;
					if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 2; else otp = 2;
				}
				else if (setgem == 201)
				{
					dsstype = 8; phyatk = 2; magatk = 2; str = 1;
					hpinc = 30; mpinc = 10;
					if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 2; else otp = 2;
				}
			}

			if (IItem.GetType() >= 1 && IItem.GetType() <= 6)
			{
				if (setgem == 240)
				{
					dsstype = 1; def = 18; agi = 7;
				}
				else if (setgem == 239)
				{
					dsstype = 1; def = 18; wis = 7;
				}
				else if (setgem == 238)
				{
					dsstype = 1; def = 18; intel = 7;
				}
				else if (setgem == 237)
				{
					dsstype = 1; def = 18; hp = 7;
				}
				else if (setgem == 236)
				{
					dsstype = 1; def = 18; str = 7;
				}
				else if (setgem == 235)
				{
					dsstype = 2; def = 16; agi = 5;
				}
				else if (setgem == 234)
				{
					dsstype = 2; def = 16; wis = 5;
				}
				else if (setgem == 233)
				{
					dsstype = 2; def = 16; intel = 5;
				}
				else if (setgem == 232)
				{
					dsstype = 2; def = 16; hp = 5;
				}
				else if (setgem == 231)
				{
					dsstype = 2; def = 16; str = 5;
				}
				else if (setgem == 230)
				{
					dsstype = 3; def = 14; agi = 3;
				}
				else if (setgem == 229)
				{
					dsstype = 3; def = 14; wis = 3;
				}
				else if (setgem == 228)
				{
					dsstype = 3; def = 14; intel = 3;
				}
				else if (setgem == 227)
				{
					dsstype = 3; def = 14; hp = 3;
				}
				else if (setgem == 226)
				{
					dsstype = 3; def = 14; str = 3;
				}
				else if (setgem == 225)
				{
					dsstype = 4; def = 12; agi = 3;
				}
				else if (setgem == 224)
				{
					dsstype = 4; def = 12; wis = 3;
				}
				else if (setgem == 223)
				{
					dsstype = 4; def = 12; intel = 3;
				}
				else if (setgem == 222)
				{
					dsstype = 4; def = 12; hp = 3;
				}
				else if (setgem == 221)
				{
					dsstype = 4; def = 12; str = 3;
				}
				else if (setgem == 220)
				{
					dsstype = 5; def = 10; agi = 2;
				}
				else if (setgem == 219)
				{
					dsstype = 5; def = 10; wis = 2;
				}
				else if (setgem == 218)
				{
					dsstype = 5; def = 10; intel = 2;
				}
				else if (setgem == 217)
				{
					dsstype = 5; def = 10; hp = 2;
				}
				else if (setgem == 216)
				{
					dsstype = 5; def = 10; str = 2;
				}
				else if (setgem == 215)
				{
					dsstype = 6; def = 8; agi = 2;
				}
				else if (setgem == 214)
				{
					dsstype = 6; def = 8; wis = 2;
				}
				else if (setgem == 213)
				{
					dsstype = 6; def = 8; intel = 2;
				}
				else if (setgem == 212)
				{
					dsstype = 6; def = 8; hp = 2;
				}
				else if (setgem == 211)
				{
					dsstype = 6; def = 8; str = 2;
				}
				else if (setgem == 210)
				{
					dsstype = 7; def = 6; agi = 1;
				}
				else if (setgem == 209)
				{
					dsstype = 7; def = 6; wis = 1;
				}
				else if (setgem == 208)
				{
					dsstype = 7; def = 6; intel = 1;
				}
				else if (setgem == 207)
				{
					dsstype = 7; def = 6; hp = 1;
				}
				else if (setgem == 206)
				{
					dsstype = 7; def = 6; str = 1;
				}
				else if (setgem == 205)
				{
					dsstype = 8; def = 4; agi = 1;
				}
				else if (setgem == 204)
				{
					dsstype = 8; def = 4; wis = 1;
				}
				else if (setgem == 203)
				{
					dsstype = 8; def = 4; intel = 1;
				}
				else if (setgem == 202)
				{
					dsstype = 8; def = 4; hp = 1;
				}
				else if (setgem == 201)
				{
					dsstype = 8; def = 4; str = 1;
				}
			}

			if (isItemSuit(index) || isItemCustomWeapon(index) || isItemRiding(index)) {
				int GStat = GetStat;
				if (isBattleRiding(index)) {
					int Satiety = GStat / 100;
					if (Satiety)
						GStat -= (Satiety * 100);
				}

				int AddingType = SuitStats.count(index) ? SuitStats.find(index)->second.Type : 0;
				int Multiply = SuitStats.count(index) ? SuitStats.find(index)->second.Multiply : 3;

				if (Multiply < 2)
					Multiply = 2;

				switch (AddingType) {
				case 0:
					hp += GStat >= 6 ? (((GStat - 5) * Multiply) + 10) : GStat * (Multiply - 1);
					break;
				case 1:
					str += GStat >= 6 ? (((GStat - 5) * Multiply) + 10) : GStat * (Multiply - 1);
					break;
				case 2:
					hp += GStat >= 6 ? (((GStat - 5) * Multiply) + 10) : GStat * (Multiply - 1);
					break;
				case 3:
					intel += GStat >= 6 ? (((GStat - 5) * Multiply) + 10) : GStat * (Multiply - 1);
					break;
				case 4:
					wis += GStat >= 6 ? (((GStat - 5) * Multiply) + 10) : GStat * (Multiply - 1);
					break;
				case 5:
					agi += GStat >= 6 ? (((GStat - 5) * Multiply) + 10) : GStat * (Multiply - 1);
					break;
				default:
					hp += GStat >= 6 ? (((GStat - 5) * Multiply) + 10) : GStat * (Multiply - 1);
					break;
				}
			}
		}


		if (index >= 3381 && index <= 3383)
		{
			CPlayer::Write(IPlayer2.GetOffset(), 194, "dd", iid, 100);
			if (index == 3381) CPlayer::Write(IPlayer2.GetOffset(), 193, "ddd", iid, 101, 10);
			if (index == 3382) CPlayer::Write(IPlayer2.GetOffset(), 193, "ddd", iid, 101, 11);
			if (index == 3383) CPlayer::Write(IPlayer2.GetOffset(), 193, "ddd", iid, 101, 12);

			if (index == 3383 && !GetStat)
				CPlayer::Write(IPlayer2.GetOffset(), 193, "ddd", iid, 100, GetStat + 2);
			else
				CPlayer::Write(IPlayer2.GetOffset(), 193, "ddd", iid, 100, GetStat + 1);
		}

		if (index >= 3384 && index <= 3386)
		{
			if (GetStat)
			{
				int Stat = GetStat / 1000;
				int Value = GetStat % 100;
				CPlayer::Write(IPlayer2.GetOffset(), 194, "dd", iid, Value);
				CPlayer::Write(IPlayer2.GetOffset(), 193, "ddd", iid, Value, Stat);
			}
		}

		if (ItemStat)
		{
			PerfShotCheck = ItemStat / 100000000;
			ItemStat -= (100000000 * PerfShotCheck);
		}

		if (ItemStat)
		{
			int dg1typecheck = ItemStat / 10000000;
			if (dg1typecheck) dg1stat = 1;
			if (dg1typecheck > 0) dg1type = (dg1typecheck - 1);
			ItemStat -= (10000000 * dg1typecheck);
		}

		if (ItemStat)
		{
			int dg1statcheck = ItemStat / 1000000;
			if (dg1statcheck > 0) dg1stat = (dg1statcheck + 1);
			ItemStat -= (1000000 * dg1statcheck);
		}

		if (ItemStat)
		{
			int dg2typecheck = ItemStat / 100000;
			if (dg2typecheck) dg2stat = 1;
			if (dg2typecheck > 0) dg2type = (dg2typecheck - 1);
			ItemStat -= (100000 * dg2typecheck);
		}

		if (ItemStat)
		{
			int dg2statcheck = ItemStat / 10000;
			if (dg2statcheck > 0) dg2stat = (dg2statcheck + 1);
			ItemStat -= (10000 * dg2statcheck);
		}

		if (ItemStat && index >= 2986 && index <= 3009)
		{
			int yinyanggrade = ItemStat / 100;
			prefix = yinyanggrade + 1;
			ItemStat -= (100 * yinyanggrade);
		}

		if (ItemStat)
			QigongGrade = ItemStat % 100;

		if (index >= 3199 && index <= 3201 && prefix == 0)
			prefix = 1;

		if (index >= 2986 && index <= 3009 && prefix == 0)
			prefix = 1;

		if (index >= 3018 && index <= 3020 && GetStat)
			prefix = GetStat / 1000;

		int refill = 0;
		if (isSoulPocket(index)) {
			if (GetStat)
				refill = GetStat;
		}

		if (GetStat && (isItemCustomWeapon(index) || isItemSuit(index) || isItemRiding(index))) {
			int GStat = GetStat;
			if (isBattleRiding(index)) {
				int Satiety = GStat / 100;
				if (Satiety)
					GStat -= (Satiety * 100);
			}
			if (GStat)
				upgrlvl = GStat;
		}

		if (isItemRidingArmor(index)) {
			upgrlvl = GetStat;
			if (GetStat > 0 && GetStat <= 10 && GetBattleRidingGrade(index) > 0) {
				if (GetBattleRidingType(index) == 1) {
					if (index == 7883 || index == 7889 || index == 7895 || index == 7901)
						str += RidingHelmet[GetBattleRidingGrade(index) - 1][GetStat - 1];
					else
						intel += RidingHelmet[GetBattleRidingGrade(index) - 1][GetStat - 1];
				}
				if (GetBattleRidingType(index) == 2)
					hp += RidingSaddle[GetBattleRidingGrade(index) - 1][GetStat - 1];
				if (GetBattleRidingType(index) == 3)
					xdefense += RidingArmor[GetBattleRidingGrade(index) - 1][GetStat - 1];
				if (GetBattleRidingType(index) == 4)
					xdefense += RidingCloth[GetBattleRidingGrade(index) - 1][GetStat - 1];
				if (GetBattleRidingType(index) == 5)
					eva += RidingMagnet[GetBattleRidingGrade(index) - 1][GetStat - 1];
			}
		}

		int restorecount = RestoredIIDs.findExists(iid);

		int dg1 = (dg1type << 24) + (dg1stat << 16);
		int dg2 = (dg2type << 24) + (dg2stat << 16);

		remaintime = PetLifeCheck.findExists(iid);
		if (remaintime)
			remaintime -= (int)time(0);

		Tools->Compile(Packet + i * 67, "wdbddbbbbbbbbwbbdbbbbwwwwbbbbbbbbbbwddd", index, iid, prefix, info, amount, maxend, curend, setgem, xatk, xmagic, xdefense, xhit, xevasion, xprotect, upgrlvl, upgrrate, remaintime, x, y, restorecount, dsstype, phyatk, magatk, def, absorb, eva, otp, hpinc, mpinc, str, hp, intel, wis, agi, PerfShotCheck, QigongGrade, dg1, dg2, refill);
	}

	CDBSocket::ProcessHtml((int)player, type, (int)"bbm", Items, 0, Packet, Size);
	delete[] Packet;
	CIOBuffer::Free(pack);
}

void __fastcall ModsSendStorageList(void *player, void *_edx, char* packet)
{
	char *pack = packet;
	Interface<ITools> Tools;
	unsigned char type = packet[2];
	unsigned char Items = packet[3];
	packet += 4;
	size_t Size = Items * 67;
	char *Packet = new char[Size];

	void *GetPlayer = *(void**)((int)player + 120);
	int Class = *(DWORD*)((int)GetPlayer + 460);
	int PacketSize = 0;

	for (unsigned char i = 0; i < Items; i++)
	{
		unsigned short index;
		unsigned long iid;
		unsigned char prefix;
		unsigned long info, amount;
		unsigned char maxend, curend, setgem, xatk, xmagic, xdefense, xhit, xevasion;
		unsigned short xprotect;
		unsigned char upgrlvl, upgrrate;
		unsigned char x = 0, y = 0, z = 0, dsstype = 0, eva = 0, otp = 0, hpinc = 0, mpinc = 0, str = 0, hp = 0, intel = 0, wis = 0, agi = 0, a = 0, dg1stat = 0, dg1type = 0, dg2stat = 0, dg2type = 0, PerfShotCheck = 0;
		unsigned long remaintime = 0, QigongGrade = 0;
		unsigned short phyatk = 0, magatk = 0, def = 0, absorb = 0;

		packet = (char*)CPacket::Read(packet, (char*)(pack + *(WORD*)pack), "wdbddbbbbbbbbbbb", &index, &iid, &prefix, &info, &amount, &maxend, &curend, &setgem, &xatk,
			&xmagic, &xdefense, &xhit, &xevasion, &xprotect, &upgrlvl, &upgrrate);

		if (!CItem::FindInitItem(index))
			continue;

		int Value = 0, Item = 0;
		Undefined::CreateMonsterValueNew((char*)GetPlayer + 1128, (int)&Value, (int)&iid);
		int Recheck = 0, Check = 0;
		Check = Undefined::Check((int)((char*)GetPlayer + 1128), (int)&Recheck);

		int ItemStat = 0;

		itemStat.Enter();
		if (GetItemStat.count(iid))
			ItemStat = GetItemStat.find(iid)->second;
		itemStat.Leave();

		int GetStat = ItemStat;

		if (*(DWORD*)&Value != *(DWORD*)Check)
		{
			Item = Undefined::GetValue(&Value);
			int GetNewItem = Item + 4;
			int RealItem = Undefined::NewGetItem(*((DWORD*)GetPlayer + 113), (int)&GetNewItem);
			IItem IItem((void*)RealItem);
			if (IItem.GetType() == -2 || IItem.GetType() == 19 || IItem.GetType() == 0 || IItem.GetType() == -3 || IItem.GetType() == -1)
			{
				if (setgem == 240)
				{
					dsstype = 1; phyatk = 17; magatk = 17; agi = 8;
					hpinc = 250; mpinc = 200;
					if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 18; else otp = 18;
				}
				else if (setgem == 239)
				{
					dsstype = 1; phyatk = 17; magatk = 17; wis = 8;
					hpinc = 250; mpinc = 200;
					if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 18; else otp = 18;
				}
				else if (setgem == 238)
				{
					dsstype = 1; phyatk = 17; magatk = 17; intel = 8;
					hpinc = 250; mpinc = 200;
					if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 18; else otp = 18;
				}
				else if (setgem == 237)
				{
					dsstype = 1; phyatk = 17; magatk = 17; hp = 8;
					hpinc = 250; mpinc = 200;
					if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 18; else otp = 18;
				}
				else if (setgem == 236)
				{
					dsstype = 1; phyatk = 17; magatk = 17; str = 8;
					hpinc = 250; mpinc = 200;
					if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 18; else otp = 18;
				}
				else if (setgem == 235)
				{
					dsstype = 2; phyatk = 14; magatk = 14; agi = 5;
					hpinc = 200; mpinc = 150;
					if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 15; else otp = 15;
				}
				else if (setgem == 234)
				{
					dsstype = 2; phyatk = 14; magatk = 14; wis = 5;
					hpinc = 200; mpinc = 150;
					if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 15; else otp = 15;
				}
				else if (setgem == 233)
				{
					dsstype = 2; phyatk = 14; magatk = 14; intel = 5;
					hpinc = 200; mpinc = 150;
					if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 15; else otp = 15;
				}
				else if (setgem == 232)
				{
					dsstype = 2; phyatk = 14; magatk = 14; hp = 5;
					hpinc = 200; mpinc = 150;
					if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 15; else otp = 15;
				}
				else if (setgem == 231)
				{
					dsstype = 2; phyatk = 14; magatk = 14; str = 5;
					hpinc = 200; mpinc = 150;
					if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 15; else otp = 15;
				}
				else if (setgem == 230)
				{
					dsstype = 3; phyatk = 12; magatk = 12; agi = 3;
					hpinc = 130; mpinc = 110;
					if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 12; else otp = 12;
				}
				else if (setgem == 229)
				{
					dsstype = 3; phyatk = 12; magatk = 12; wis = 3;
					hpinc = 130; mpinc = 110;
					if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 12; else otp = 12;
				}
				else if (setgem == 228)
				{
					dsstype = 3; phyatk = 12; magatk = 12; intel = 3;
					hpinc = 130; mpinc = 110;
					if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 12; else otp = 12;
				}
				else if (setgem == 227)
				{
					dsstype = 3; phyatk = 12; magatk = 12; hp = 3;
					hpinc = 130; mpinc = 110;
					if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 12; else otp = 12;
				}
				else if (setgem == 226)
				{
					dsstype = 3; phyatk = 12; magatk = 12; str = 3;
					hpinc = 130; mpinc = 110;
					if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 12; else otp = 12;
				}
				else if (setgem == 225)
				{
					dsstype = 4; phyatk = 10; magatk = 10; agi = 3;
					hpinc = 110; mpinc = 90;
					if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 10; else otp = 10;
				}
				else if (setgem == 224)
				{
					dsstype = 4; phyatk = 10; magatk = 10; wis = 3;
					hpinc = 110; mpinc = 90;
					if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 10; else otp = 10;
				}
				else if (setgem == 223)
				{
					dsstype = 4; phyatk = 10; magatk = 10; intel = 3;
					hpinc = 110; mpinc = 90;
					if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 10; else otp = 10;
				}
				else if (setgem == 222)
				{
					dsstype = 4; phyatk = 10; magatk = 10; hp = 3;
					hpinc = 110; mpinc = 90;
					if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 10; else otp = 10;
				}
				else if (setgem == 221)
				{
					dsstype = 4; phyatk = 10; magatk = 10; str = 3;
					hpinc = 110; mpinc = 90;
					if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 10; else otp = 10;
				}
				else if (setgem == 220)
				{
					dsstype = 5; phyatk = 8; magatk = 8; agi = 2;
					hpinc = 90; mpinc = 70;
					if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 8; else otp = 8;
				}
				else if (setgem == 219)
				{
					dsstype = 5; phyatk = 8; magatk = 8; wis = 2;
					hpinc = 90; mpinc = 70;
					if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 8; else otp = 8;
				}
				else if (setgem == 218)
				{
					dsstype = 5; phyatk = 8; magatk = 8; intel = 2;
					hpinc = 90; mpinc = 70;
					if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 8; else otp = 8;
				}
				else if (setgem == 217)
				{
					dsstype = 5; phyatk = 8; magatk = 8; hp = 2;
					hpinc = 90; mpinc = 70;
					if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 8; else otp = 8;
				}
				else if (setgem == 216)
				{
					dsstype = 5; phyatk = 8; magatk = 8; str = 2;
					hpinc = 90; mpinc = 70;
					if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 8; else otp = 8;
				}
				else if (setgem == 215)
				{
					dsstype = 6; phyatk = 6; magatk = 6; agi = 2;
					hpinc = 70; mpinc = 50;
					if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 6; else otp = 6;
				}
				else if (setgem == 214)
				{
					dsstype = 6; phyatk = 6; magatk = 6; wis = 2;
					hpinc = 70; mpinc = 50;
					if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 6; else otp = 6;
				}
				else if (setgem == 213)
				{
					dsstype = 6; phyatk = 6; magatk = 6; intel = 2;
					hpinc = 70; mpinc = 50;
					if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 6; else otp = 6;
				}
				else if (setgem == 212)
				{
					dsstype = 6; phyatk = 6; magatk = 6; hp = 2;
					hpinc = 70; mpinc = 50;
					if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 6; else otp = 6;
				}
				else if (setgem == 211)
				{
					dsstype = 6; phyatk = 6; magatk = 6; str = 2;
					hpinc = 70; mpinc = 50;
					if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 6; else otp = 6;
				}
				else if (setgem == 210)
				{
					dsstype = 7; phyatk = 4; magatk = 4; agi = 1;
					hpinc = 50; mpinc = 30;
					if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 4; else otp = 4;
				}
				else if (setgem == 209)
				{
					dsstype = 7; phyatk = 4; magatk = 4; wis = 1;
					hpinc = 50; mpinc = 30;
					if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 4; else otp = 4;
				}
				else if (setgem == 208)
				{
					dsstype = 7; phyatk = 4; magatk = 4; intel = 1;
					hpinc = 50; mpinc = 30;
					if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 4; else otp = 4;
				}
				else if (setgem == 207)
				{
					dsstype = 7; phyatk = 4; magatk = 4; hp = 1;
					hpinc = 50; mpinc = 30;
					if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 4; else otp = 4;
				}
				else if (setgem == 206)
				{
					dsstype = 7; phyatk = 4; magatk = 4; str = 1;
					hpinc = 50; mpinc = 30;
					if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 4; else otp = 4;
				}
				else if (setgem == 205)
				{
					dsstype = 8; phyatk = 2; magatk = 2; agi = 1;
					hpinc = 30; mpinc = 10;
					if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 2; else otp = 2;
				}
				else if (setgem == 204)
				{
					dsstype = 8; phyatk = 2; magatk = 2; wis = 1;
					hpinc = 30; mpinc = 10;
					if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 2; else otp = 2;
				}
				else if (setgem == 203)
				{
					dsstype = 8; phyatk = 2; magatk = 2; intel = 1;
					hpinc = 30; mpinc = 10;
					if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 2; else otp = 2;
				}
				else if (setgem == 202)
				{
					dsstype = 8; phyatk = 2; magatk = 2; hp = 1;
					hpinc = 30; mpinc = 10;
					if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 2; else otp = 2;
				}
				else if (setgem == 201)
				{
					dsstype = 8; phyatk = 2; magatk = 2; str = 1;
					hpinc = 30; mpinc = 10;
					if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 2; else otp = 2;
				}
			}

			if (IItem.GetType() >= 1 && IItem.GetType() <= 6)
			{
				if (setgem == 240)
				{
					dsstype = 1; def = 18; agi = 7;
				}
				else if (setgem == 239)
				{
					dsstype = 1; def = 18; wis = 7;
				}
				else if (setgem == 238)
				{
					dsstype = 1; def = 18; intel = 7;
				}
				else if (setgem == 237)
				{
					dsstype = 1; def = 18; hp = 7;
				}
				else if (setgem == 236)
				{
					dsstype = 1; def = 18; str = 7;
				}
				else if (setgem == 235)
				{
					dsstype = 2; def = 16; agi = 5;
				}
				else if (setgem == 234)
				{
					dsstype = 2; def = 16; wis = 5;
				}
				else if (setgem == 233)
				{
					dsstype = 2; def = 16; intel = 5;
				}
				else if (setgem == 232)
				{
					dsstype = 2; def = 16; hp = 5;
				}
				else if (setgem == 231)
				{
					dsstype = 2; def = 16; str = 5;
				}
				else if (setgem == 230)
				{
					dsstype = 3; def = 14; agi = 3;
				}
				else if (setgem == 229)
				{
					dsstype = 3; def = 14; wis = 3;
				}
				else if (setgem == 228)
				{
					dsstype = 3; def = 14; intel = 3;
				}
				else if (setgem == 227)
				{
					dsstype = 3; def = 14; hp = 3;
				}
				else if (setgem == 226)
				{
					dsstype = 3; def = 14; str = 3;
				}
				else if (setgem == 225)
				{
					dsstype = 4; def = 12; agi = 3;
				}
				else if (setgem == 224)
				{
					dsstype = 4; def = 12; wis = 3;
				}
				else if (setgem == 223)
				{
					dsstype = 4; def = 12; intel = 3;
				}
				else if (setgem == 222)
				{
					dsstype = 4; def = 12; hp = 3;
				}
				else if (setgem == 221)
				{
					dsstype = 4; def = 12; str = 3;
				}
				else if (setgem == 220)
				{
					dsstype = 5; def = 10; agi = 2;
				}
				else if (setgem == 219)
				{
					dsstype = 5; def = 10; wis = 2;
				}
				else if (setgem == 218)
				{
					dsstype = 5; def = 10; intel = 2;
				}
				else if (setgem == 217)
				{
					dsstype = 5; def = 10; hp = 2;
				}
				else if (setgem == 216)
				{
					dsstype = 5; def = 10; str = 2;
				}
				else if (setgem == 215)
				{
					dsstype = 6; def = 8; agi = 2;
				}
				else if (setgem == 214)
				{
					dsstype = 6; def = 8; wis = 2;
				}
				else if (setgem == 213)
				{
					dsstype = 6; def = 8; intel = 2;
				}
				else if (setgem == 212)
				{
					dsstype = 6; def = 8; hp = 2;
				}
				else if (setgem == 211)
				{
					dsstype = 6; def = 8; str = 2;
				}
				else if (setgem == 210)
				{
					dsstype = 7; def = 6; agi = 1;
				}
				else if (setgem == 209)
				{
					dsstype = 7; def = 6; wis = 1;
				}
				else if (setgem == 208)
				{
					dsstype = 7; def = 6; intel = 1;
				}
				else if (setgem == 207)
				{
					dsstype = 7; def = 6; hp = 1;
				}
				else if (setgem == 206)
				{
					dsstype = 7; def = 6; str = 1;
				}
				else if (setgem == 205)
				{
					dsstype = 8; def = 4; agi = 1;
				}
				else if (setgem == 204)
				{
					dsstype = 8; def = 4; wis = 1;
				}
				else if (setgem == 203)
				{
					dsstype = 8; def = 4; intel = 1;
				}
				else if (setgem == 202)
				{
					dsstype = 8; def = 4; hp = 1;
				}
				else if (setgem == 201)
				{
					dsstype = 8; def = 4; str = 1;
				}
			}

			if (isItemSuit(index) || isItemCustomWeapon(index) || isItemRiding(index)) {
				int GStat = GetStat;
				if (isBattleRiding(index)) {
					int Satiety = GStat / 100;
					if (Satiety)
						GStat -= (Satiety * 100);
				}

				int AddingType = SuitStats.count(index) ? SuitStats.find(index)->second.Type : 0;
				int Multiply = SuitStats.count(index) ? SuitStats.find(index)->second.Multiply : 3;

				if (Multiply < 2)
					Multiply = 2;

				switch (AddingType) {
				case 0:
					hp += GStat >= 6 ? (((GStat - 5) * Multiply) + 10) : GStat * (Multiply - 1);
					break;
				case 1:
					str += GStat >= 6 ? (((GStat - 5) * Multiply) + 10) : GStat * (Multiply - 1);
					break;
				case 2:
					hp += GStat >= 6 ? (((GStat - 5) * Multiply) + 10) : GStat * (Multiply - 1);
					break;
				case 3:
					intel += GStat >= 6 ? (((GStat - 5) * Multiply) + 10) : GStat * (Multiply - 1);
					break;
				case 4:
					wis += GStat >= 6 ? (((GStat - 5) * Multiply) + 10) : GStat * (Multiply - 1);
					break;
				case 5:
					agi += GStat >= 6 ? (((GStat - 5) * Multiply) + 10) : GStat * (Multiply - 1);
					break;
				default:
					hp += GStat >= 6 ? (((GStat - 5) * Multiply) + 10) : GStat * (Multiply - 1);
					break;
				}
			}
			if (RealItem)
				CBase::Delete((void*)RealItem);
		}

		if (index >= 3381 && index <= 3383)
		{
			CDBSocket::ProcessHtml((int)player, 194, (int)"dd", iid, 100);
			if (index == 3381) CDBSocket::ProcessHtml((int)player, 193, (int)"ddd", iid, 101, 10);
			if (index == 3382) CDBSocket::ProcessHtml((int)player, 193, (int)"ddd", iid, 101, 11);
			if (index == 3383) CDBSocket::ProcessHtml((int)player, 193, (int)"ddd", iid, 101, 12);

			if (index == 3383 && !GetStat)
				CDBSocket::ProcessHtml((int)player, 193, (int)"ddd", iid, 100, GetStat + 2);
			else
				CDBSocket::ProcessHtml((int)player, 193, (int)"ddd", iid, 100, GetStat + 1);
		}

		if (index >= 3384 && index <= 3386)
		{
			if (GetStat)
			{
				int Stat = GetStat / 1000;
				int Value = GetStat % 100;
				CDBSocket::ProcessHtml((int)player, 194, (int)"dd", iid, Value);
				CDBSocket::ProcessHtml((int)player, 193, (int)"ddd", iid, Value, Stat);
			}
		}

		if (ItemStat)
		{
			PerfShotCheck = ItemStat / 100000000;
			ItemStat -= (100000000 * PerfShotCheck);
		}

		if (ItemStat)
		{
			int dg1typecheck = ItemStat / 10000000;
			if (dg1typecheck) dg1stat = 1;
			if (dg1typecheck > 0) dg1type = (dg1typecheck - 1);
			ItemStat -= (10000000 * dg1typecheck);
		}

		if (ItemStat)
		{
			int dg1statcheck = ItemStat / 1000000;
			if (dg1statcheck > 0) dg1stat = (dg1statcheck + 1);
			ItemStat -= (1000000 * dg1statcheck);
		}

		if (ItemStat)
		{
			int dg2typecheck = ItemStat / 100000;
			if (dg2typecheck) dg2stat = 1;
			if (dg2typecheck > 0) dg2type = (dg2typecheck - 1);
			ItemStat -= (100000 * dg2typecheck);
		}

		if (ItemStat)
		{
			int dg2statcheck = ItemStat / 10000;
			if (dg2statcheck > 0) dg2stat = (dg2statcheck + 1);
			ItemStat -= (10000 * dg2statcheck);
		}

		if (ItemStat && index >= 2986 && index <= 3009)
		{
			int yinyanggrade = ItemStat / 100;
			prefix = yinyanggrade + 1;
			ItemStat -= (100 * yinyanggrade);
		}

		if (ItemStat)
			QigongGrade = ItemStat % 100;

		if (index >= 3199 && index <= 3201 && prefix == 0)
			prefix = 1;

		if (index >= 2986 && index <= 3009 && prefix == 0)
			prefix = 1;

		if (index >= 3018 && index <= 3020 && GetStat)
			prefix = GetStat / 1000;

		int refill = 0;
		if (isSoulPocket(index)) {
			if (GetStat)
				refill = GetStat;
		}

		if (GetStat && (isItemCustomWeapon(index) || isItemSuit(index) || isItemRiding(index))) {
			int GStat = GetStat;
			if (isBattleRiding(index)) {
				int Satiety = GStat / 100;
				if (Satiety)
					GStat -= (Satiety * 100);
			}
			if (GStat)
				upgrlvl = GStat;
		}

		if (isItemRidingArmor(index)) {
			upgrlvl = GetStat;
			if (GetStat > 0 && GetStat <= 10 && GetBattleRidingGrade(index) > 0) {
				if (GetBattleRidingType(index) == 1) {
					if (index == 7883 || index == 7889 || index == 7895 || index == 7901)
						str += RidingHelmet[GetBattleRidingGrade(index) - 1][GetStat - 1];
					else
						intel += RidingHelmet[GetBattleRidingGrade(index) - 1][GetStat - 1];
				}
				if (GetBattleRidingType(index) == 2)
					hp += RidingSaddle[GetBattleRidingGrade(index) - 1][GetStat - 1];
				if (GetBattleRidingType(index) == 3)
					xdefense += RidingArmor[GetBattleRidingGrade(index) - 1][GetStat - 1];
				if (GetBattleRidingType(index) == 4)
					xdefense += RidingCloth[GetBattleRidingGrade(index) - 1][GetStat - 1];
				if (GetBattleRidingType(index) == 5)
					eva += RidingMagnet[GetBattleRidingGrade(index) - 1][GetStat - 1];
			}
		}
		int restorecount = RestoredIIDs.findExists(iid);

		int dg1 = (dg1type << 24) + (dg1stat << 16);
		int dg2 = (dg2type << 24) + (dg2stat << 16);

		remaintime = PetLifeCheck.findExists(iid);
		if (remaintime)
			remaintime -= (int)time(0);

		Tools->Compile(Packet + PacketSize, "wdbddbbbbbbbbwbbdbbbbwwwwbbbbbbbbbbwddd", index, iid, prefix, info, amount, maxend, curend, setgem, xatk, xmagic, xdefense, xhit, xevasion, xprotect, upgrlvl, upgrrate, remaintime, x, y, restorecount, dsstype, phyatk, magatk, def, absorb, eva, otp, hpinc, mpinc, str, hp, intel, wis, agi, PerfShotCheck, QigongGrade, dg1, dg2, refill);
		PacketSize += 67;
	}

	CDBSocket::ProcessHtml((int)player, type, (int)"bm", PacketSize / 67, Packet, PacketSize);
	delete[] Packet;
	CIOBuffer::Free(pack);
}

void __fastcall ModsSendItemInfo(void *player, void *_edx, char* Inventory)
{
	char* Inv = Inventory;
	//int PSize = *((DWORD *)Inventory + 2000) - 4;

	if (!CBase::IsDeleted((int)player)) {
		std::set<int> itemsF = std::set<int>();
		IChar IPlayer(player);
		Interface<ITools> Tools;
		int Class = *(DWORD*)((int)player + 460);
		unsigned char type = Inventory[2];
		unsigned char Items = Inventory[3];
		Inventory += 4;
		char *FindSize = Inventory;
		char *FindSize2 = Inventory;
		char *WriteWear = Inventory;
		unsigned short RidingBattlesAmount = 0;
		unsigned char FixedLoop = 0;
		unsigned char BattleLoop = 0;
		int InvC = 0;

		for (unsigned char i = 0; i < Items; i++)
		{
			unsigned short index = 0;
			int iid = 0;
			char prefix = 0;
			int info = 0, amount = 0;
			char maxend = 0, curend = 0, setgem = 0, xatk = 0, xmagic = 0, xdefense = 0, xhit = 0, xevasion = 0;
			unsigned short xprotect = 0;
			char upgrlvl = 0, upgrrate = 0;
			char x = 0, y = 0, z = 0, dsstype = 0, eva = 0, otp = 0, hpinc = 0, mpinc = 0, str = 0, hp = 0, intel = 0, wis = 0, agi = 0, a = 0, dg1stat = 0, dg1type = 0, dg2stat = 0, dg2type = 0, PerfShotCheck = 0;
			int remaintime = 0, QigongGrade = 0;
			unsigned short phyatk = 0, magatk = 0, def = 0, absorb = 0;

			FindSize = (char*)CPacket::Read(FindSize, (char*)(Inv + *(WORD*)Inv), "dwbddbbbbbbbbbbb", &iid, &index, &prefix, &info, &amount, &maxend, &curend, &setgem, &xatk, &xmagic, &xdefense, &xhit, &xevasion, &xprotect, &upgrlvl, &upgrrate);

			if (info & 1)
				itemsF.insert(iid);
		}

		for (unsigned char i = 0; i < Items; i++)
		{
			int Size = itemsF.size();

			if (Size >= 119)
				break;

			unsigned short index = 0;
			int iid = 0;
			char prefix = 0;
			int info = 0, amount = 0;
			char maxend = 0, curend = 0, setgem = 0, xatk = 0, xmagic = 0, xdefense = 0, xhit = 0, xevasion = 0;
			unsigned short xprotect = 0;
			char upgrlvl = 0, upgrrate = 0;
			char x = 0, y = 0, z = 0, dsstype = 0, eva = 0, otp = 0, hpinc = 0, mpinc = 0, str = 0, hp = 0, intel = 0, wis = 0, agi = 0, a = 0, dg1stat = 0, dg1type = 0, dg2stat = 0, dg2type = 0, PerfShotCheck = 0;
			int remaintime = 0, QigongGrade = 0;
			unsigned short phyatk = 0, magatk = 0, def = 0, absorb = 0;
			FindSize2 = (char*)CPacket::Read(FindSize2, (char*)(Inv + *(WORD*)Inv), "dwbddbbbbbbbbbbb", &iid, &index, &prefix, &info, &amount, &maxend, &curend, &setgem, &xatk, &xmagic, &xdefense, &xhit, &xevasion, &xprotect, &upgrlvl, &upgrrate);

			if (!(info & 1))
				itemsF.insert(iid);
		}

		size_t ShowWear = itemsF.size() * 67;

		char *xPacket = new char[ShowWear];

		for (unsigned char i = 0; i < Items; i++)
		{
			unsigned short index;
			unsigned long iid;
			unsigned char prefix;
			unsigned long info, amount;
			unsigned char maxend, curend, setgem, xatk, xmagic, xdefense, xhit, xevasion;
			unsigned short xprotect;
			unsigned char upgrlvl, upgrrate;
			unsigned short x = 0, y = 0, z = 0, dsstype = 0, eva = 0, otp = 0, hpinc = 0, mpinc = 0, str = 0, hp = 0, intel = 0, wis = 0, agi = 0, a = 0, dg1stat = 0, dg1type = 0, dg2stat = 0, dg2type = 0, PerfShotCheck = 0;
			unsigned long remaintime = 0, QigongGrade = 0;
			unsigned short phyatk = 0, magatk = 0, def = 0, absorb = 0;

			WriteWear = (char*)CPacket::Read(WriteWear, (char*)(Inv + *(WORD*)Inv), "dwbddbbbbbbbbbbb", &iid, &index, &prefix, &info, &amount, &maxend, &curend, &setgem, &xatk,
				&xmagic, &xdefense, &xhit, &xevasion, &xprotect, &upgrlvl, &upgrrate);

			if (!itemsF.count(iid))
				continue;

			int Itemxx = IPlayer.ItemPointer(iid);

			int ItemStat = 0;

			itemStat.Enter();
			if (GetItemStat.count(iid))
				ItemStat = GetItemStat.find(iid)->second;
			itemStat.Leave();

			int GetStat = ItemStat;
			if (Itemxx)
			{
				IItem IItem((void*)Itemxx);
				if (IItem.GetType() == -2 || IItem.GetType() == 19 || IItem.GetType() == 0 || IItem.GetType() == -3 || IItem.GetType() == -1)
				{
					if (setgem == 240)
					{
						dsstype = 1; phyatk = 17; magatk = 17; agi = 8;
						hpinc = 250; mpinc = 200;
						if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 18; else otp = 18;
					}
					else if (setgem == 239)
					{
						dsstype = 1; phyatk = 17; magatk = 17; wis = 8;
						hpinc = 250; mpinc = 200;
						if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 18; else otp = 18;
					}
					else if (setgem == 238)
					{
						dsstype = 1; phyatk = 17; magatk = 17; intel = 8;
						hpinc = 250; mpinc = 200;
						if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 18; else otp = 18;
					}
					else if (setgem == 237)
					{
						dsstype = 1; phyatk = 17; magatk = 17; hp = 8;
						hpinc = 250; mpinc = 200;
						if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 18; else otp = 18;
					}
					else if (setgem == 236)
					{
						dsstype = 1; phyatk = 17; magatk = 17; str = 8;
						hpinc = 250; mpinc = 200;
						if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 18; else otp = 18;
					}
					else if (setgem == 235)
					{
						dsstype = 2; phyatk = 14; magatk = 14; agi = 5;
						hpinc = 200; mpinc = 150;
						if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 15; else otp = 15;
					}
					else if (setgem == 234)
					{
						dsstype = 2; phyatk = 14; magatk = 14; wis = 5;
						hpinc = 200; mpinc = 150;
						if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 15; else otp = 15;
					}
					else if (setgem == 233)
					{
						dsstype = 2; phyatk = 14; magatk = 14; intel = 5;
						hpinc = 200; mpinc = 150;
						if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 15; else otp = 15;
					}
					else if (setgem == 232)
					{
						dsstype = 2; phyatk = 14; magatk = 14; hp = 5;
						hpinc = 200; mpinc = 150;
						if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 15; else otp = 15;
					}
					else if (setgem == 231)
					{
						dsstype = 2; phyatk = 14; magatk = 14; str = 5;
						hpinc = 200; mpinc = 150;
						if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 15; else otp = 15;
					}
					else if (setgem == 230)
					{
						dsstype = 3; phyatk = 12; magatk = 12; agi = 3;
						hpinc = 130; mpinc = 110;
						if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 12; else otp = 12;
					}
					else if (setgem == 229)
					{
						dsstype = 3; phyatk = 12; magatk = 12; wis = 3;
						hpinc = 130; mpinc = 110;
						if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 12; else otp = 12;
					}
					else if (setgem == 228)
					{
						dsstype = 3; phyatk = 12; magatk = 12; intel = 3;
						hpinc = 130; mpinc = 110;
						if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 12; else otp = 12;
					}
					else if (setgem == 227)
					{
						dsstype = 3; phyatk = 12; magatk = 12; hp = 3;
						hpinc = 130; mpinc = 110;
						if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 12; else otp = 12;
					}
					else if (setgem == 226)
					{
						dsstype = 3; phyatk = 12; magatk = 12; str = 3;
						hpinc = 130; mpinc = 110;
						if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 12; else otp = 12;
					}
					else if (setgem == 225)
					{
						dsstype = 4; phyatk = 10; magatk = 10; agi = 3;
						hpinc = 110; mpinc = 90;
						if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 10; else otp = 10;
					}
					else if (setgem == 224)
					{
						dsstype = 4; phyatk = 10; magatk = 10; wis = 3;
						hpinc = 110; mpinc = 90;
						if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 10; else otp = 10;
					}
					else if (setgem == 223)
					{
						dsstype = 4; phyatk = 10; magatk = 10; intel = 3;
						hpinc = 110; mpinc = 90;
						if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 10; else otp = 10;
					}
					else if (setgem == 222)
					{
						dsstype = 4; phyatk = 10; magatk = 10; hp = 3;
						hpinc = 110; mpinc = 90;
						if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 10; else otp = 10;
					}
					else if (setgem == 221)
					{
						dsstype = 4; phyatk = 10; magatk = 10; str = 3;
						hpinc = 110; mpinc = 90;
						if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 10; else otp = 10;
					}
					else if (setgem == 220)
					{
						dsstype = 5; phyatk = 8; magatk = 8; agi = 2;
						hpinc = 90; mpinc = 70;
						if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 8; else otp = 8;
					}
					else if (setgem == 219)
					{
						dsstype = 5; phyatk = 8; magatk = 8; wis = 2;
						hpinc = 90; mpinc = 70;
						if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 8; else otp = 8;
					}
					else if (setgem == 218)
					{
						dsstype = 5; phyatk = 8; magatk = 8; intel = 2;
						hpinc = 90; mpinc = 70;
						if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 8; else otp = 8;
					}
					else if (setgem == 217)
					{
						dsstype = 5; phyatk = 8; magatk = 8; hp = 2;
						hpinc = 90; mpinc = 70;
						if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 8; else otp = 8;
					}
					else if (setgem == 216)
					{
						dsstype = 5; phyatk = 8; magatk = 8; str = 2;
						hpinc = 90; mpinc = 70;
						if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 8; else otp = 8;
					}
					else if (setgem == 215)
					{
						dsstype = 6; phyatk = 6; magatk = 6; agi = 2;
						hpinc = 70; mpinc = 50;
						if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 6; else otp = 6;
					}
					else if (setgem == 214)
					{
						dsstype = 6; phyatk = 6; magatk = 6; wis = 2;
						hpinc = 70; mpinc = 50;
						if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 6; else otp = 6;
					}
					else if (setgem == 213)
					{
						dsstype = 6; phyatk = 6; magatk = 6; intel = 2;
						hpinc = 70; mpinc = 50;
						if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 6; else otp = 6;
					}
					else if (setgem == 212)
					{
						dsstype = 6; phyatk = 6; magatk = 6; hp = 2;
						hpinc = 70; mpinc = 50;
						if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 6; else otp = 6;
					}
					else if (setgem == 211)
					{
						dsstype = 6; phyatk = 6; magatk = 6; str = 2;
						hpinc = 70; mpinc = 50;
						if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 6; else otp = 6;
					}
					else if (setgem == 210)
					{
						dsstype = 7; phyatk = 4; magatk = 4; agi = 1;
						hpinc = 50; mpinc = 30;
						if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 4; else otp = 4;
					}
					else if (setgem == 209)
					{
						dsstype = 7; phyatk = 4; magatk = 4; wis = 1;
						hpinc = 50; mpinc = 30;
						if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 4; else otp = 4;
					}
					else if (setgem == 208)
					{
						dsstype = 7; phyatk = 4; magatk = 4; intel = 1;
						hpinc = 50; mpinc = 30;
						if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 4; else otp = 4;
					}
					else if (setgem == 207)
					{
						dsstype = 7; phyatk = 4; magatk = 4; hp = 1;
						hpinc = 50; mpinc = 30;
						if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 4; else otp = 4;
					}
					else if (setgem == 206)
					{
						dsstype = 7; phyatk = 4; magatk = 4; str = 1;
						hpinc = 50; mpinc = 30;
						if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 4; else otp = 4;
					}
					else if (setgem == 205)
					{
						dsstype = 8; phyatk = 2; magatk = 2; agi = 1;
						hpinc = 30; mpinc = 10;
						if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 2; else otp = 2;
					}
					else if (setgem == 204)
					{
						dsstype = 8; phyatk = 2; magatk = 2; wis = 1;
						hpinc = 30; mpinc = 10;
						if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 2; else otp = 2;
					}
					else if (setgem == 203)
					{
						dsstype = 8; phyatk = 2; magatk = 2; intel = 1;
						hpinc = 30; mpinc = 10;
						if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 2; else otp = 2;
					}
					else if (setgem == 202)
					{
						dsstype = 8; phyatk = 2; magatk = 2; hp = 1;
						hpinc = 30; mpinc = 10;
						if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 2; else otp = 2;
					}
					else if (setgem == 201)
					{
						dsstype = 8; phyatk = 2; magatk = 2; str = 1;
						hpinc = 30; mpinc = 10;
						if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 2; else otp = 2;
					}
				}

				if (IItem.GetType() >= 1 && IItem.GetType() <= 6)
				{
					if (setgem == 240)
					{
						dsstype = 1; def = 18; agi = 7;
					}
					else if (setgem == 239)
					{
						dsstype = 1; def = 18; wis = 7;
					}
					else if (setgem == 238)
					{
						dsstype = 1; def = 18; intel = 7;
					}
					else if (setgem == 237)
					{
						dsstype = 1; def = 18; hp = 7;
					}
					else if (setgem == 236)
					{
						dsstype = 1; def = 18; str = 7;
					}
					else if (setgem == 235)
					{
						dsstype = 2; def = 16; agi = 5;
					}
					else if (setgem == 234)
					{
						dsstype = 2; def = 16; wis = 5;
					}
					else if (setgem == 233)
					{
						dsstype = 2; def = 16; intel = 5;
					}
					else if (setgem == 232)
					{
						dsstype = 2; def = 16; hp = 5;
					}
					else if (setgem == 231)
					{
						dsstype = 2; def = 16; str = 5;
					}
					else if (setgem == 230)
					{
						dsstype = 3; def = 14; agi = 3;
					}
					else if (setgem == 229)
					{
						dsstype = 3; def = 14; wis = 3;
					}
					else if (setgem == 228)
					{
						dsstype = 3; def = 14; intel = 3;
					}
					else if (setgem == 227)
					{
						dsstype = 3; def = 14; hp = 3;
					}
					else if (setgem == 226)
					{
						dsstype = 3; def = 14; str = 3;
					}
					else if (setgem == 225)
					{
						dsstype = 4; def = 12; agi = 3;
					}
					else if (setgem == 224)
					{
						dsstype = 4; def = 12; wis = 3;
					}
					else if (setgem == 223)
					{
						dsstype = 4; def = 12; intel = 3;
					}
					else if (setgem == 222)
					{
						dsstype = 4; def = 12; hp = 3;
					}
					else if (setgem == 221)
					{
						dsstype = 4; def = 12; str = 3;
					}
					else if (setgem == 220)
					{
						dsstype = 5; def = 10; agi = 2;
					}
					else if (setgem == 219)
					{
						dsstype = 5; def = 10; wis = 2;
					}
					else if (setgem == 218)
					{
						dsstype = 5; def = 10; intel = 2;
					}
					else if (setgem == 217)
					{
						dsstype = 5; def = 10; hp = 2;
					}
					else if (setgem == 216)
					{
						dsstype = 5; def = 10; str = 2;
					}
					else if (setgem == 215)
					{
						dsstype = 6; def = 8; agi = 2;
					}
					else if (setgem == 214)
					{
						dsstype = 6; def = 8; wis = 2;
					}
					else if (setgem == 213)
					{
						dsstype = 6; def = 8; intel = 2;
					}
					else if (setgem == 212)
					{
						dsstype = 6; def = 8; hp = 2;
					}
					else if (setgem == 211)
					{
						dsstype = 6; def = 8; str = 2;
					}
					else if (setgem == 210)
					{
						dsstype = 7; def = 6; agi = 1;
					}
					else if (setgem == 209)
					{
						dsstype = 7; def = 6; wis = 1;
					}
					else if (setgem == 208)
					{
						dsstype = 7; def = 6; intel = 1;
					}
					else if (setgem == 207)
					{
						dsstype = 7; def = 6; hp = 1;
					}
					else if (setgem == 206)
					{
						dsstype = 7; def = 6; str = 1;
					}
					else if (setgem == 205)
					{
						dsstype = 8; def = 4; agi = 1;
					}
					else if (setgem == 204)
					{
						dsstype = 8; def = 4; wis = 1;
					}
					else if (setgem == 203)
					{
						dsstype = 8; def = 4; intel = 1;
					}
					else if (setgem == 202)
					{
						dsstype = 8; def = 4; hp = 1;
					}
					else if (setgem == 201)
					{
						dsstype = 8; def = 4; str = 1;
					}
				}

				if (isItemSuit(index) || isItemCustomWeapon(index) || isItemRiding(index)) {
					int GStat = GetStat;
					if (isBattleRiding(index)) {
						int Satiety = GStat / 100;
						if (Satiety)
							GStat -= (Satiety * 100);
					}

					int AddingType = SuitStats.count(index) ? SuitStats.find(index)->second.Type : 0;
					int Multiply = SuitStats.count(index) ? SuitStats.find(index)->second.Multiply : 3;

					if (Multiply < 2)
						Multiply = 2;

					switch (AddingType) {
					case 0:
						hp += GStat >= 6 ? (((GStat - 5) * Multiply) + 10) : GStat * (Multiply - 1);
						break;
					case 1:
						str += GStat >= 6 ? (((GStat - 5) * Multiply) + 10) : GStat * (Multiply - 1);
						break;
					case 2:
						hp += GStat >= 6 ? (((GStat - 5) * Multiply) + 10) : GStat * (Multiply - 1);
						break;
					case 3:
						intel += GStat >= 6 ? (((GStat - 5) * Multiply) + 10) : GStat * (Multiply - 1);
						break;
					case 4:
						wis += GStat >= 6 ? (((GStat - 5) * Multiply) + 10) : GStat * (Multiply - 1);
						break;
					case 5:
						agi += GStat >= 6 ? (((GStat - 5) * Multiply) + 10) : GStat * (Multiply - 1);
						break;
					default:
						hp += GStat >= 6 ? (((GStat - 5) * Multiply) + 10) : GStat * (Multiply - 1);
						break;
					}
				}
			}

			if (ItemStat)
			{
				PerfShotCheck = ItemStat / 100000000;
				ItemStat -= (100000000 * PerfShotCheck);
			}

			if (ItemStat)
			{
				int dg1typecheck = ItemStat / 10000000;
				if (dg1typecheck) dg1stat = 1;
				if (dg1typecheck > 0) dg1type = (dg1typecheck - 1);
				ItemStat -= (10000000 * dg1typecheck);
			}

			if (ItemStat)
			{
				int dg1statcheck = ItemStat / 1000000;
				if (dg1statcheck > 0) dg1stat = (dg1statcheck + 1);
				ItemStat -= (1000000 * dg1statcheck);
			}

			if (ItemStat)
			{
				int dg2typecheck = ItemStat / 100000;
				if (dg2typecheck) dg2stat = 1;
				if (dg2typecheck > 0) dg2type = (dg2typecheck - 1);
				ItemStat -= (100000 * dg2typecheck);
			}

			if (ItemStat)
			{
				int dg2statcheck = ItemStat / 10000;
				if (dg2statcheck > 0) dg2stat = (dg2statcheck + 1);
				ItemStat -= (10000 * dg2statcheck);
			}

			if (ItemStat && index >= 2986 && index <= 3009)
			{
				int yinyanggrade = ItemStat / 100;
				prefix = yinyanggrade + 1;
				ItemStat -= (100 * yinyanggrade);
			}

			if (ItemStat)
				QigongGrade = ItemStat % 100;

			if (index >= 3199 && index <= 3201 && prefix == 0)
				prefix = 1;

			if (index >= 2986 && index <= 3009 && prefix == 0)
				prefix = 1;

			if (index >= 3018 && index <= 3020 && GetStat)
				prefix = GetStat / 1000;

			int refill = 0;
			if (isSoulPocket(index)) {
				if (GetStat)
					refill = GetStat;
			}

			if (index >= 3381 && index <= 3383)
			{
				CPlayer::Write(player, 194, "dd", iid, 100);
				if (index == 3381) CPlayer::Write(player, 193, "ddd", iid, 101, 10);
				if (index == 3382) CPlayer::Write(player, 193, "ddd", iid, 101, 11);
				if (index == 3383) CPlayer::Write(player, 193, "ddd", iid, 101, 12);

				if (index == 3383 && !GetStat)
					CPlayer::Write(player, 193, "ddd", iid, 100, GetStat + 2);
				else
					CPlayer::Write(player, 193, "ddd", iid, 100, GetStat + 1);
			}

			if (index >= 3384 && index <= 3386)
			{
				if (GetStat)
				{
					int Stat = GetStat / 1000;
					int Value = GetStat % 100;
					CPlayer::Write(player, 194, "dd", iid, Value);
					CPlayer::Write(player, 193, "ddd", iid, Value, Stat);
				}
			}
			if (GetStat && (isItemCustomWeapon(index) || isItemSuit(index) || isItemRiding(index)) || isItemRidingArmor(index)) {
				int GStat = GetStat;
				if (isBattleRiding(index)) {
					int Satiety = GStat / 100;
					if (Satiety)
						GStat -= (Satiety * 100);
				}
				if (GStat)
					upgrlvl = GStat;
			}
			if (isItemRidingArmor(index)) {
				upgrlvl = GetStat;
				if (GetStat > 0 && GetStat <= 10 && GetBattleRidingGrade(index) > 0) {
					if (GetBattleRidingType(index) == 1) {
						if (index == 7883 || index == 7889 || index == 7895 || index == 7901)
							str += RidingHelmet[GetBattleRidingGrade(index) - 1][GetStat - 1];
						else
							intel += RidingHelmet[GetBattleRidingGrade(index) - 1][GetStat - 1];
					}
					if (GetBattleRidingType(index) == 2)
						hp += RidingSaddle[GetBattleRidingGrade(index) - 1][GetStat - 1];
					if (GetBattleRidingType(index) == 3)
						xdefense += RidingArmor[GetBattleRidingGrade(index) - 1][GetStat - 1];
					if (GetBattleRidingType(index) == 4)
						xdefense += RidingCloth[GetBattleRidingGrade(index) - 1][GetStat - 1];
					if (GetBattleRidingType(index) == 5)
						eva += RidingMagnet[GetBattleRidingGrade(index) - 1][GetStat - 1];
				}
			}

			int restorecount = RestoredIIDs.findExists(iid);

			int dg1 = (dg1type << 24) + (dg1stat << 16);
			int dg2 = (dg2type << 24) + (dg2stat << 16);

			remaintime = PetLifeCheck.findExists(iid);
			if (remaintime)
				remaintime -= (int)time(0);

			Tools->Compile(xPacket + FixedLoop * 67, "wdbddbbbbbbbbwbbdbbbbwwwwbbbbbbbbbbwddd", index, iid, prefix, info, amount, maxend, curend, setgem, xatk, xmagic, xdefense, xhit, xevasion, xprotect, upgrlvl, upgrrate, remaintime, x, y, restorecount, dsstype, phyatk, magatk, def, absorb, eva, otp, hpinc, mpinc, str, hp, intel, wis, agi, PerfShotCheck, QigongGrade, dg1, dg2, refill);
			FixedLoop += 1;
		}

		CPlayer::Write(player, type, "wm", itemsF.size(), xPacket, ShowWear);
		delete[] xPacket;

		if (Items <= itemsF.size()) {
			CIOBuffer::Free(Inv);
			return;
		}

		for (unsigned char i = 0; i < Items; i++)
		{
			unsigned short index;
			unsigned long iid;
			unsigned char prefix;
			unsigned long info, amount;
			unsigned char maxend, curend, setgem, xatk, xmagic, xdefense, xhit, xevasion;
			unsigned short xprotect;
			unsigned char upgrlvl, upgrrate;
			unsigned short x = 0, y = 0, z = 0, dsstype = 0, eva = 0, otp = 0, hpinc = 0, mpinc = 0, str = 0, hp = 0, intel = 0, wis = 0, agi = 0, a = 0, dg1stat = 0, dg1type = 0, dg2stat = 0, dg2type = 0, PerfShotCheck = 0;
			unsigned long remaintime = 0, QigongGrade = 0;
			unsigned short phyatk = 0, magatk = 0, def = 0, absorb = 0;

			Inventory = (char*)CPacket::Read(Inventory, (char*)(Inv + *(WORD*)Inv), "dwbddbbbbbbbbbbb", &iid, &index, &prefix, &info, &amount, &maxend, &curend, &setgem, &xatk,
				&xmagic, &xdefense, &xhit, &xevasion, &xprotect, &upgrlvl, &upgrrate);

			if (itemsF.count(iid))
				continue;

			int ItemStat = 0;

			itemStat.Enter();
			if (GetItemStat.count(iid))
				ItemStat = GetItemStat.find(iid)->second;
			itemStat.Leave();

			int GetStat = ItemStat;

			int Itemxx = IPlayer.ItemPointer(iid);

			if (Itemxx)
			{
				IItem IItem((void*)Itemxx);

				if (IItem.GetType() == -2 || IItem.GetType() == 19 || IItem.GetType() == 0 || IItem.GetType() == -3 || IItem.GetType() == -1)
				{
					if (setgem == 240)
					{
						dsstype = 1; phyatk = 17; magatk = 17; agi = 8;
						hpinc = 250; mpinc = 200;
						if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 18; else otp = 18;
					}
					else if (setgem == 239)
					{
						dsstype = 1; phyatk = 17; magatk = 17; wis = 8;
						hpinc = 250; mpinc = 200;
						if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 18; else otp = 18;
					}
					else if (setgem == 238)
					{
						dsstype = 1; phyatk = 17; magatk = 17; intel = 8;
						hpinc = 250; mpinc = 200;
						if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 18; else otp = 18;
					}
					else if (setgem == 237)
					{
						dsstype = 1; phyatk = 17; magatk = 17; hp = 8;
						hpinc = 250; mpinc = 200;
						if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 18; else otp = 18;
					}
					else if (setgem == 236)
					{
						dsstype = 1; phyatk = 17; magatk = 17; str = 8;
						hpinc = 250; mpinc = 200;
						if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 18; else otp = 18;
					}
					else if (setgem == 235)
					{
						dsstype = 2; phyatk = 14; magatk = 14; agi = 5;
						hpinc = 200; mpinc = 150;
						if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 15; else otp = 15;
					}
					else if (setgem == 234)
					{
						dsstype = 2; phyatk = 14; magatk = 14; wis = 5;
						hpinc = 200; mpinc = 150;
						if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 15; else otp = 15;
					}
					else if (setgem == 233)
					{
						dsstype = 2; phyatk = 14; magatk = 14; intel = 5;
						hpinc = 200; mpinc = 150;
						if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 15; else otp = 15;
					}
					else if (setgem == 232)
					{
						dsstype = 2; phyatk = 14; magatk = 14; hp = 5;
						hpinc = 200; mpinc = 150;
						if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 15; else otp = 15;
					}
					else if (setgem == 231)
					{
						dsstype = 2; phyatk = 14; magatk = 14; str = 5;
						hpinc = 200; mpinc = 150;
						if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 15; else otp = 15;
					}
					else if (setgem == 230)
					{
						dsstype = 3; phyatk = 12; magatk = 12; agi = 3;
						hpinc = 130; mpinc = 110;
						if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 12; else otp = 12;
					}
					else if (setgem == 229)
					{
						dsstype = 3; phyatk = 12; magatk = 12; wis = 3;
						hpinc = 130; mpinc = 110;
						if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 12; else otp = 12;
					}
					else if (setgem == 228)
					{
						dsstype = 3; phyatk = 12; magatk = 12; intel = 3;
						hpinc = 130; mpinc = 110;
						if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 12; else otp = 12;
					}
					else if (setgem == 227)
					{
						dsstype = 3; phyatk = 12; magatk = 12; hp = 3;
						hpinc = 130; mpinc = 110;
						if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 12; else otp = 12;
					}
					else if (setgem == 226)
					{
						dsstype = 3; phyatk = 12; magatk = 12; str = 3;
						hpinc = 130; mpinc = 110;
						if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 12; else otp = 12;
					}
					else if (setgem == 225)
					{
						dsstype = 4; phyatk = 10; magatk = 10; agi = 3;
						hpinc = 110; mpinc = 90;
						if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 10; else otp = 10;
					}
					else if (setgem == 224)
					{
						dsstype = 4; phyatk = 10; magatk = 10; wis = 3;
						hpinc = 110; mpinc = 90;
						if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 10; else otp = 10;
					}
					else if (setgem == 223)
					{
						dsstype = 4; phyatk = 10; magatk = 10; intel = 3;
						hpinc = 110; mpinc = 90;
						if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 10; else otp = 10;
					}
					else if (setgem == 222)
					{
						dsstype = 4; phyatk = 10; magatk = 10; hp = 3;
						hpinc = 110; mpinc = 90;
						if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 10; else otp = 10;
					}
					else if (setgem == 221)
					{
						dsstype = 4; phyatk = 10; magatk = 10; str = 3;
						hpinc = 110; mpinc = 90;
						if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 10; else otp = 10;
					}
					else if (setgem == 220)
					{
						dsstype = 5; phyatk = 8; magatk = 8; agi = 2;
						hpinc = 90; mpinc = 70;
						if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 8; else otp = 8;
					}
					else if (setgem == 219)
					{
						dsstype = 5; phyatk = 8; magatk = 8; wis = 2;
						hpinc = 90; mpinc = 70;
						if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 8; else otp = 8;
					}
					else if (setgem == 218)
					{
						dsstype = 5; phyatk = 8; magatk = 8; intel = 2;
						hpinc = 90; mpinc = 70;
						if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 8; else otp = 8;
					}
					else if (setgem == 217)
					{
						dsstype = 5; phyatk = 8; magatk = 8; hp = 2;
						hpinc = 90; mpinc = 70;
						if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 8; else otp = 8;
					}
					else if (setgem == 216)
					{
						dsstype = 5; phyatk = 8; magatk = 8; str = 2;
						hpinc = 90; mpinc = 70;
						if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 8; else otp = 8;
					}
					else if (setgem == 215)
					{
						dsstype = 6; phyatk = 6; magatk = 6; agi = 2;
						hpinc = 70; mpinc = 50;
						if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 6; else otp = 6;
					}
					else if (setgem == 214)
					{
						dsstype = 6; phyatk = 6; magatk = 6; wis = 2;
						hpinc = 70; mpinc = 50;
						if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 6; else otp = 6;
					}
					else if (setgem == 213)
					{
						dsstype = 6; phyatk = 6; magatk = 6; intel = 2;
						hpinc = 70; mpinc = 50;
						if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 6; else otp = 6;
					}
					else if (setgem == 212)
					{
						dsstype = 6; phyatk = 6; magatk = 6; hp = 2;
						hpinc = 70; mpinc = 50;
						if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 6; else otp = 6;
					}
					else if (setgem == 211)
					{
						dsstype = 6; phyatk = 6; magatk = 6; str = 2;
						hpinc = 70; mpinc = 50;
						if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 6; else otp = 6;
					}
					else if (setgem == 210)
					{
						dsstype = 7; phyatk = 4; magatk = 4; agi = 1;
						hpinc = 50; mpinc = 30;
						if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 4; else otp = 4;
					}
					else if (setgem == 209)
					{
						dsstype = 7; phyatk = 4; magatk = 4; wis = 1;
						hpinc = 50; mpinc = 30;
						if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 4; else otp = 4;
					}
					else if (setgem == 208)
					{
						dsstype = 7; phyatk = 4; magatk = 4; intel = 1;
						hpinc = 50; mpinc = 30;
						if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 4; else otp = 4;
					}
					else if (setgem == 207)
					{
						dsstype = 7; phyatk = 4; magatk = 4; hp = 1;
						hpinc = 50; mpinc = 30;
						if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 4; else otp = 4;
					}
					else if (setgem == 206)
					{
						dsstype = 7; phyatk = 4; magatk = 4; str = 1;
						hpinc = 50; mpinc = 30;
						if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 4; else otp = 4;
					}
					else if (setgem == 205)
					{
						dsstype = 8; phyatk = 2; magatk = 2; agi = 1;
						hpinc = 30; mpinc = 10;
						if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 2; else otp = 2;
					}
					else if (setgem == 204)
					{
						dsstype = 8; phyatk = 2; magatk = 2; wis = 1;
						hpinc = 30; mpinc = 10;
						if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 2; else otp = 2;
					}
					else if (setgem == 203)
					{
						dsstype = 8; phyatk = 2; magatk = 2; intel = 1;
						hpinc = 30; mpinc = 10;
						if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 2; else otp = 2;
					}
					else if (setgem == 202)
					{
						dsstype = 8; phyatk = 2; magatk = 2; hp = 1;
						hpinc = 30; mpinc = 10;
						if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 2; else otp = 2;
					}
					else if (setgem == 201)
					{
						dsstype = 8; phyatk = 2; magatk = 2; str = 1;
						hpinc = 30; mpinc = 10;
						if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 2; else otp = 2;
					}
				}

				if (IItem.GetType() >= 1 && IItem.GetType() <= 6)
				{
					if (setgem == 240)
					{
						dsstype = 1; def = 18; agi = 7;
					}
					else if (setgem == 239)
					{
						dsstype = 1; def = 18; wis = 7;
					}
					else if (setgem == 238)
					{
						dsstype = 1; def = 18; intel = 7;
					}
					else if (setgem == 237)
					{
						dsstype = 1; def = 18; hp = 7;
					}
					else if (setgem == 236)
					{
						dsstype = 1; def = 18; str = 7;
					}
					else if (setgem == 235)
					{
						dsstype = 2; def = 16; agi = 5;
					}
					else if (setgem == 234)
					{
						dsstype = 2; def = 16; wis = 5;
					}
					else if (setgem == 233)
					{
						dsstype = 2; def = 16; intel = 5;
					}
					else if (setgem == 232)
					{
						dsstype = 2; def = 16; hp = 5;
					}
					else if (setgem == 231)
					{
						dsstype = 2; def = 16; str = 5;
					}
					else if (setgem == 230)
					{
						dsstype = 3; def = 14; agi = 3;
					}
					else if (setgem == 229)
					{
						dsstype = 3; def = 14; wis = 3;
					}
					else if (setgem == 228)
					{
						dsstype = 3; def = 14; intel = 3;
					}
					else if (setgem == 227)
					{
						dsstype = 3; def = 14; hp = 3;
					}
					else if (setgem == 226)
					{
						dsstype = 3; def = 14; str = 3;
					}
					else if (setgem == 225)
					{
						dsstype = 4; def = 12; agi = 3;
					}
					else if (setgem == 224)
					{
						dsstype = 4; def = 12; wis = 3;
					}
					else if (setgem == 223)
					{
						dsstype = 4; def = 12; intel = 3;
					}
					else if (setgem == 222)
					{
						dsstype = 4; def = 12; hp = 3;
					}
					else if (setgem == 221)
					{
						dsstype = 4; def = 12; str = 3;
					}
					else if (setgem == 220)
					{
						dsstype = 5; def = 10; agi = 2;
					}
					else if (setgem == 219)
					{
						dsstype = 5; def = 10; wis = 2;
					}
					else if (setgem == 218)
					{
						dsstype = 5; def = 10; intel = 2;
					}
					else if (setgem == 217)
					{
						dsstype = 5; def = 10; hp = 2;
					}
					else if (setgem == 216)
					{
						dsstype = 5; def = 10; str = 2;
					}
					else if (setgem == 215)
					{
						dsstype = 6; def = 8; agi = 2;
					}
					else if (setgem == 214)
					{
						dsstype = 6; def = 8; wis = 2;
					}
					else if (setgem == 213)
					{
						dsstype = 6; def = 8; intel = 2;
					}
					else if (setgem == 212)
					{
						dsstype = 6; def = 8; hp = 2;
					}
					else if (setgem == 211)
					{
						dsstype = 6; def = 8; str = 2;
					}
					else if (setgem == 210)
					{
						dsstype = 7; def = 6; agi = 1;
					}
					else if (setgem == 209)
					{
						dsstype = 7; def = 6; wis = 1;
					}
					else if (setgem == 208)
					{
						dsstype = 7; def = 6; intel = 1;
					}
					else if (setgem == 207)
					{
						dsstype = 7; def = 6; hp = 1;
					}
					else if (setgem == 206)
					{
						dsstype = 7; def = 6; str = 1;
					}
					else if (setgem == 205)
					{
						dsstype = 8; def = 4; agi = 1;
					}
					else if (setgem == 204)
					{
						dsstype = 8; def = 4; wis = 1;
					}
					else if (setgem == 203)
					{
						dsstype = 8; def = 4; intel = 1;
					}
					else if (setgem == 202)
					{
						dsstype = 8; def = 4; hp = 1;
					}
					else if (setgem == 201)
					{
						dsstype = 8; def = 4; str = 1;
					}
				}

				if (!CBase::IsDeleted((int)player) && IItem.GetType() == -3 && otp && *(DWORD*)((int)player + 460) == 4)
				{
					eva = otp;
					otp = 0;
				}


				if (isItemSuit(index) || isItemCustomWeapon(index) || isItemRiding(index)) {
					int GStat = GetStat;
					if (isBattleRiding(index)) {
						int Satiety = GStat / 100;
						if (Satiety)
							GStat -= (Satiety * 100);
					}

					int AddingType = SuitStats.count(index) ? SuitStats.find(index)->second.Type : 0;
					int Multiply = SuitStats.count(index) ? SuitStats.find(index)->second.Multiply : 3;

					if (Multiply < 2)
						Multiply = 2;

					switch (AddingType) {
					case 0:
						hp += GStat >= 6 ? (((GStat - 5) * Multiply) + 10) : GStat * (Multiply - 1);
						break;
					case 1:
						str += GStat >= 6 ? (((GStat - 5) * Multiply) + 10) : GStat * (Multiply - 1);
						break;
					case 2:
						hp += GStat >= 6 ? (((GStat - 5) * Multiply) + 10) : GStat * (Multiply - 1);
						break;
					case 3:
						intel += GStat >= 6 ? (((GStat - 5) * Multiply) + 10) : GStat * (Multiply - 1);
						break;
					case 4:
						wis += GStat >= 6 ? (((GStat - 5) * Multiply) + 10) : GStat * (Multiply - 1);
						break;
					case 5:
						agi += GStat >= 6 ? (((GStat - 5) * Multiply) + 10) : GStat * (Multiply - 1);
						break;
					default:
						hp += GStat >= 6 ? (((GStat - 5) * Multiply) + 10) : GStat * (Multiply - 1);
						break;
					}
				}
			}

			if (GetStat)
			{
				PerfShotCheck = ItemStat / 100000000;
				ItemStat -= (100000000 * PerfShotCheck);
			}

			if (ItemStat)
			{
				int dg1typecheck = ItemStat / 10000000;
				if (dg1typecheck) dg1stat = 1;
				if (dg1typecheck > 0) dg1type = (dg1typecheck - 1);
				ItemStat -= (10000000 * dg1typecheck);
			}

			if (ItemStat)
			{
				int dg1statcheck = ItemStat / 1000000;
				if (dg1statcheck > 0) dg1stat = (dg1statcheck + 1);
				ItemStat -= (1000000 * dg1statcheck);
			}

			if (ItemStat)
			{
				int dg2typecheck = ItemStat / 100000;
				if (dg2typecheck) dg2stat = 1;
				if (dg2typecheck > 0) dg2type = (dg2typecheck - 1);
				ItemStat -= (100000 * dg2typecheck);
			}

			if (ItemStat)
			{
				int dg2statcheck = ItemStat / 10000;
				if (dg2statcheck > 0) dg2stat = (dg2statcheck + 1);
				ItemStat -= (10000 * dg2statcheck);
			}

			if (ItemStat && index >= 2986 && index <= 3009)
			{
				int yinyanggrade = ItemStat / 100;
				prefix = yinyanggrade + 1;
				ItemStat -= (100 * yinyanggrade);
			}

			if (ItemStat)
				QigongGrade = ItemStat % 100;

			if (index >= 3199 && index <= 3201 && prefix == 0)
				prefix = 1;

			if (index >= 2986 && index <= 3009 && prefix == 0)
				prefix = 1;

			if (index >= 3018 && index <= 3020 && GetStat)
				prefix = GetStat / 1000;

			if (index >= 3381 && index <= 3383)
			{
				CPlayer::Write(player, 194, "dd", iid, 100);
				if (index == 3381) CPlayer::Write(player, 193, "ddd", iid, 101, 10);
				if (index == 3382) CPlayer::Write(player, 193, "ddd", iid, 101, 11);
				if (index == 3383) CPlayer::Write(player, 193, "ddd", iid, 101, 12);

				if (index == 3383 && !GetStat)
					CPlayer::Write(player, 193, "ddd", iid, 100, GetStat + 2);
				else
					CPlayer::Write(player, 193, "ddd", iid, 100, GetStat + 1);
			}

			int refill = 0;
			if (isSoulPocket(index)) {
				if (GetStat)
					refill = GetStat;
			}

			if (index >= 3384 && index <= 3386)
			{
				if (GetStat)
				{
					int Stat = GetStat / 1000;
					int Value = GetStat % 100;
					CPlayer::Write(player, 194, "dd", iid, Value);
					CPlayer::Write(player, 193, "ddd", iid, Value, Stat);
				}
			}

			if (GetStat && (isItemCustomWeapon(index) || isItemSuit(index) || isItemRiding(index) || isItemRidingArmor(index))) {
				int GStat = GetStat;
				if (isBattleRiding(index)) {
					int Satiety = GStat / 100;
					if (Satiety)
						GStat -= (Satiety * 100);
				}
				if (GStat)
					upgrlvl = GStat;
			}

			if (isItemRidingArmor(index)) {
				if (GetStat > 0 && GetStat <= 10 && GetBattleRidingGrade(index) > 0) {
					if (GetBattleRidingType(index) == 1) {
						if (index == 7883 || index == 7889 || index == 7895 || index == 7901)
							str += RidingHelmet[GetBattleRidingGrade(index) - 1][GetStat - 1];
						else
							intel += RidingHelmet[GetBattleRidingGrade(index) - 1][GetStat - 1];
					}
					if (GetBattleRidingType(index) == 2)
						hp += RidingSaddle[GetBattleRidingGrade(index) - 1][GetStat - 1];
					if (GetBattleRidingType(index) == 3)
						xdefense += RidingArmor[GetBattleRidingGrade(index) - 1][GetStat - 1];
					if (GetBattleRidingType(index) == 4)
						xdefense += RidingCloth[GetBattleRidingGrade(index) - 1][GetStat - 1];
					if (GetBattleRidingType(index) == 5)
						eva += RidingMagnet[GetBattleRidingGrade(index) - 1][GetStat - 1];
				}
			}
			int restorecount = RestoredIIDs.findExists(iid);

			int dg1 = (dg1type << 24) + (dg1stat << 16);
			int dg2 = (dg2type << 24) + (dg2stat << 16);

			remaintime = PetLifeCheck.findExists(iid);
			if (remaintime)
				remaintime -= (int)time(0);

			CPlayer::Write(player, 7, "wdbddbbbbbbbbwbbdbbbbwwwwbbbbbbbbbbwddd", index, iid, prefix, info, amount, maxend, curend, setgem, xatk, xmagic, xdefense, xhit, xevasion, xprotect, upgrlvl, upgrrate, remaintime, x, y, restorecount, dsstype, phyatk, magatk, def, absorb, eva, otp, hpinc, mpinc, str, hp, intel, wis, agi, PerfShotCheck, QigongGrade, dg1, dg2, refill);
		}
	}
	CIOBuffer::Free(Inv);
}

void crashDebug(int Type) {
	std::string Dato = "./Debugger/CrashCheck/GET_" + Time::GetDay() + "_" + Time::GetMonth() + "_" + Time::GetYear() + "_" + Time::GetHour() + "." + Time::GetMinute() + ".txt";
	std::fstream DGLOG;
	DGLOG.open(Dato, std::fstream::in | std::fstream::out | std::fstream::app);
	DGLOG << Time::GetTime() << " " << Type << std::endl;
	DGLOG.close();
}

void __fastcall ModsSendUpdateItemInfo(void *player, void *_edx, char* Item)
{
	Interface<ITools> Tools;
	char Type = Item[2];
	unsigned short index;
	unsigned long iid;
	unsigned char prefix;
	unsigned long info, amount;
	unsigned char maxend, curend, setgem, xatk, xmagic, xdefense, xhit, xevasion;
	unsigned short xprotect;
	unsigned char upgrlvl, upgrrate;
	unsigned char x = 0, y = 0, z = 0, dsstype = 0, eva = 0, otp = 0, hpinc = 0, mpinc = 0, str = 0, hp = 0, intel = 0, wis = 0, agi = 0, a = 0, dg1stat = 0, dg1type = 0, dg2stat = 0, dg2type = 0, PerfShotCheck = 0;
	unsigned long remaintime = 0, QigongGrade = 0;
	unsigned short phyatk = 0, magatk = 0, def = 0, absorb = 0;

	int refill = 0;

	CPacket::Read((char*)((void*)(Item + 3)), (char*)(Item + *(WORD*)Item), "dwbddbbbbbbbbbbb", &iid, &index, &prefix, &info, &amount, &maxend, &curend, &setgem, &xatk,
		&xmagic, &xdefense, &xhit, &xevasion, &xprotect, &upgrlvl, &upgrrate);

	int ItemStat = 0;
	int GetStat = 0;

	int Class = *(DWORD*)((int)player + 460);
	if (!isSoulPocket(index)) {

		itemStat.Enter();
		if (GetItemStat.count(iid))
			ItemStat = GetItemStat.find(iid)->second;
		itemStat.Leave();

		GetStat = ItemStat;

		int xValue = 0, xItem = 0;
		Undefined::CreateMonsterValueNew((char*)player + 1128, (int)&xValue, (int)&iid);
		int xRecheck = 0, xCheck = 0;
		xCheck = Undefined::Check((int)((char*)player + 1128), (int)&xRecheck);

		if (*(DWORD*)&xValue != *(DWORD*)xCheck)
		{
			xItem = Undefined::GetValue(&xValue);
			int xGetNewItem = xItem + 4;
			int xRealItem = Undefined::NewGetItem(*((DWORD*)player + 113), (int)&xGetNewItem);
			IItem IItem((void*)xRealItem);

			if (IItem.GetType() == -2 || IItem.GetType() == 19 || IItem.GetType() == 0 || IItem.GetType() == -3 || IItem.GetType() == -1)
			{
				if (setgem == 240)
				{
					dsstype = 1; phyatk = 17; magatk = 17; agi = 8;
					hpinc = 250; mpinc = 200;
					if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 18; else otp = 18;
				}
				else if (setgem == 239)
				{
					dsstype = 1; phyatk = 17; magatk = 17; wis = 8;
					hpinc = 250; mpinc = 200;
					if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 18; else otp = 18;
				}
				else if (setgem == 238)
				{
					dsstype = 1; phyatk = 17; magatk = 17; intel = 8;
					hpinc = 250; mpinc = 200;
					if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 18; else otp = 18;
				}
				else if (setgem == 237)
				{
					dsstype = 1; phyatk = 17; magatk = 17; hp = 8;
					hpinc = 250; mpinc = 200;
					if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 18; else otp = 18;
				}
				else if (setgem == 236)
				{
					dsstype = 1; phyatk = 17; magatk = 17; str = 8;
					hpinc = 250; mpinc = 200;
					if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 18; else otp = 18;
				}
				else if (setgem == 235)
				{
					dsstype = 2; phyatk = 14; magatk = 14; agi = 5;
					hpinc = 200; mpinc = 150;
					if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 15; else otp = 15;
				}
				else if (setgem == 234)
				{
					dsstype = 2; phyatk = 14; magatk = 14; wis = 5;
					hpinc = 200; mpinc = 150;
					if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 15; else otp = 15;
				}
				else if (setgem == 233)
				{
					dsstype = 2; phyatk = 14; magatk = 14; intel = 5;
					hpinc = 200; mpinc = 150;
					if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 15; else otp = 15;
				}
				else if (setgem == 232)
				{
					dsstype = 2; phyatk = 14; magatk = 14; hp = 5;
					hpinc = 200; mpinc = 150;
					if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 15; else otp = 15;
				}
				else if (setgem == 231)
				{
					dsstype = 2; phyatk = 14; magatk = 14; str = 5;
					hpinc = 200; mpinc = 150;
					if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 15; else otp = 15;
				}
				else if (setgem == 230)
				{
					dsstype = 3; phyatk = 12; magatk = 12; agi = 3;
					hpinc = 130; mpinc = 110;
					if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 12; else otp = 12;
				}
				else if (setgem == 229)
				{
					dsstype = 3; phyatk = 12; magatk = 12; wis = 3;
					hpinc = 130; mpinc = 110;
					if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 12; else otp = 12;
				}
				else if (setgem == 228)
				{
					dsstype = 3; phyatk = 12; magatk = 12; intel = 3;
					hpinc = 130; mpinc = 110;
					if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 12; else otp = 12;
				}
				else if (setgem == 227)
				{
					dsstype = 3; phyatk = 12; magatk = 12; hp = 3;
					hpinc = 130; mpinc = 110;
					if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 12; else otp = 12;
				}
				else if (setgem == 226)
				{
					dsstype = 3; phyatk = 12; magatk = 12; str = 3;
					hpinc = 130; mpinc = 110;
					if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 12; else otp = 12;
				}
				else if (setgem == 225)
				{
					dsstype = 4; phyatk = 10; magatk = 10; agi = 3;
					hpinc = 110; mpinc = 90;
					if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 10; else otp = 10;
				}
				else if (setgem == 224)
				{
					dsstype = 4; phyatk = 10; magatk = 10; wis = 3;
					hpinc = 110; mpinc = 90;
					if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 10; else otp = 10;
				}
				else if (setgem == 223)
				{
					dsstype = 4; phyatk = 10; magatk = 10; intel = 3;
					hpinc = 110; mpinc = 90;
					if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 10; else otp = 10;
				}
				else if (setgem == 222)
				{
					dsstype = 4; phyatk = 10; magatk = 10; hp = 3;
					hpinc = 110; mpinc = 90;
					if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 10; else otp = 10;
				}
				else if (setgem == 221)
				{
					dsstype = 4; phyatk = 10; magatk = 10; str = 3;
					hpinc = 110; mpinc = 90;
					if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 10; else otp = 10;
				}
				else if (setgem == 220)
				{
					dsstype = 5; phyatk = 8; magatk = 8; agi = 2;
					hpinc = 90; mpinc = 70;
					if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 8; else otp = 8;
				}
				else if (setgem == 219)
				{
					dsstype = 5; phyatk = 8; magatk = 8; wis = 2;
					hpinc = 90; mpinc = 70;
					if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 8; else otp = 8;
				}
				else if (setgem == 218)
				{
					dsstype = 5; phyatk = 8; magatk = 8; intel = 2;
					hpinc = 90; mpinc = 70;
					if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 8; else otp = 8;
				}
				else if (setgem == 217)
				{
					dsstype = 5; phyatk = 8; magatk = 8; hp = 2;
					hpinc = 90; mpinc = 70;
					if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 8; else otp = 8;
				}
				else if (setgem == 216)
				{
					dsstype = 5; phyatk = 8; magatk = 8; str = 2;
					hpinc = 90; mpinc = 70;
					if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 8; else otp = 8;
				}
				else if (setgem == 215)
				{
					dsstype = 6; phyatk = 6; magatk = 6; agi = 2;
					hpinc = 70; mpinc = 50;
					if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 6; else otp = 6;
				}
				else if (setgem == 214)
				{
					dsstype = 6; phyatk = 6; magatk = 6; wis = 2;
					hpinc = 70; mpinc = 50;
					if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 6; else otp = 6;
				}
				else if (setgem == 213)
				{
					dsstype = 6; phyatk = 6; magatk = 6; intel = 2;
					hpinc = 70; mpinc = 50;
					if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 6; else otp = 6;
				}
				else if (setgem == 212)
				{
					dsstype = 6; phyatk = 6; magatk = 6; hp = 2;
					hpinc = 70; mpinc = 50;
					if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 6; else otp = 6;
				}
				else if (setgem == 211)
				{
					dsstype = 6; phyatk = 6; magatk = 6; str = 2;
					hpinc = 70; mpinc = 50;
					if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 6; else otp = 6;
				}
				else if (setgem == 210)
				{
					dsstype = 7; phyatk = 4; magatk = 4; agi = 1;
					hpinc = 50; mpinc = 30;
					if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 4; else otp = 4;
				}
				else if (setgem == 209)
				{
					dsstype = 7; phyatk = 4; magatk = 4; wis = 1;
					hpinc = 50; mpinc = 30;
					if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 4; else otp = 4;
				}
				else if (setgem == 208)
				{
					dsstype = 7; phyatk = 4; magatk = 4; intel = 1;
					hpinc = 50; mpinc = 30;
					if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 4; else otp = 4;
				}
				else if (setgem == 207)
				{
					dsstype = 7; phyatk = 4; magatk = 4; hp = 1;
					hpinc = 50; mpinc = 30;
					if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 4; else otp = 4;
				}
				else if (setgem == 206)
				{
					dsstype = 7; phyatk = 4; magatk = 4; str = 1;
					hpinc = 50; mpinc = 30;
					if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 4; else otp = 4;
				}
				else if (setgem == 205)
				{
					dsstype = 8; phyatk = 2; magatk = 2; agi = 1;
					hpinc = 30; mpinc = 10;
					if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 2; else otp = 2;
				}
				else if (setgem == 204)
				{
					dsstype = 8; phyatk = 2; magatk = 2; wis = 1;
					hpinc = 30; mpinc = 10;
					if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 2; else otp = 2;
				}
				else if (setgem == 203)
				{
					dsstype = 8; phyatk = 2; magatk = 2; intel = 1;
					hpinc = 30; mpinc = 10;
					if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 2; else otp = 2;
				}
				else if (setgem == 202)
				{
					dsstype = 8; phyatk = 2; magatk = 2; hp = 1;
					hpinc = 30; mpinc = 10;
					if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 2; else otp = 2;
				}
				else if (setgem == 201)
				{
					dsstype = 8; phyatk = 2; magatk = 2; str = 1;
					hpinc = 30; mpinc = 10;
					if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 2; else otp = 2;
				}
			}

			if (IItem.GetType() >= 1 && IItem.GetType() <= 6)
			{
				if (setgem == 240)
				{
					dsstype = 1; def = 18; agi = 7;
				}
				else if (setgem == 239)
				{
					dsstype = 1; def = 18; wis = 7;
				}
				else if (setgem == 238)
				{
					dsstype = 1; def = 18; intel = 7;
				}
				else if (setgem == 237)
				{
					dsstype = 1; def = 18; hp = 7;
				}
				else if (setgem == 236)
				{
					dsstype = 1; def = 18; str = 7;
				}
				else if (setgem == 235)
				{
					dsstype = 2; def = 16; agi = 5;
				}
				else if (setgem == 234)
				{
					dsstype = 2; def = 16; wis = 5;
				}
				else if (setgem == 233)
				{
					dsstype = 2; def = 16; intel = 5;
				}
				else if (setgem == 232)
				{
					dsstype = 2; def = 16; hp = 5;
				}
				else if (setgem == 231)
				{
					dsstype = 2; def = 16; str = 5;
				}
				else if (setgem == 230)
				{
					dsstype = 3; def = 14; agi = 3;
				}
				else if (setgem == 229)
				{
					dsstype = 3; def = 14; wis = 3;
				}
				else if (setgem == 228)
				{
					dsstype = 3; def = 14; intel = 3;
				}
				else if (setgem == 227)
				{
					dsstype = 3; def = 14; hp = 3;
				}
				else if (setgem == 226)
				{
					dsstype = 3; def = 14; str = 3;
				}
				else if (setgem == 225)
				{
					dsstype = 4; def = 12; agi = 3;
				}
				else if (setgem == 224)
				{
					dsstype = 4; def = 12; wis = 3;
				}
				else if (setgem == 223)
				{
					dsstype = 4; def = 12; intel = 3;
				}
				else if (setgem == 222)
				{
					dsstype = 4; def = 12; hp = 3;
				}
				else if (setgem == 221)
				{
					dsstype = 4; def = 12; str = 3;
				}
				else if (setgem == 220)
				{
					dsstype = 5; def = 10; agi = 2;
				}
				else if (setgem == 219)
				{
					dsstype = 5; def = 10; wis = 2;
				}
				else if (setgem == 218)
				{
					dsstype = 5; def = 10; intel = 2;
				}
				else if (setgem == 217)
				{
					dsstype = 5; def = 10; hp = 2;
				}
				else if (setgem == 216)
				{
					dsstype = 5; def = 10; str = 2;
				}
				else if (setgem == 215)
				{
					dsstype = 6; def = 8; agi = 2;
				}
				else if (setgem == 214)
				{
					dsstype = 6; def = 8; wis = 2;
				}
				else if (setgem == 213)
				{
					dsstype = 6; def = 8; intel = 2;
				}
				else if (setgem == 212)
				{
					dsstype = 6; def = 8; hp = 2;
				}
				else if (setgem == 211)
				{
					dsstype = 6; def = 8; str = 2;
				}
				else if (setgem == 210)
				{
					dsstype = 7; def = 6; agi = 1;
				}
				else if (setgem == 209)
				{
					dsstype = 7; def = 6; wis = 1;
				}
				else if (setgem == 208)
				{
					dsstype = 7; def = 6; intel = 1;
				}
				else if (setgem == 207)
				{
					dsstype = 7; def = 6; hp = 1;
				}
				else if (setgem == 206)
				{
					dsstype = 7; def = 6; str = 1;
				}
				else if (setgem == 205)
				{
					dsstype = 8; def = 4; agi = 1;
				}
				else if (setgem == 204)
				{
					dsstype = 8; def = 4; wis = 1;
				}
				else if (setgem == 203)
				{
					dsstype = 8; def = 4; intel = 1;
				}
				else if (setgem == 202)
				{
					dsstype = 8; def = 4; hp = 1;
				}
				else if (setgem == 201)
				{
					dsstype = 8; def = 4; str = 1;
				}
			}

			if (!CBase::IsDeleted((int)player) && IItem.GetType() == -3 && otp && *(DWORD*)((int)player + 460) == 4)
			{
				eva = otp;
				otp = 0;
			}

			if (xRealItem)
				CBase::Delete((void*)xRealItem);
		}

		IChar IPlayer(player);
		int Itemxx = IPlayer._ItemPointer(iid);
		if (Itemxx)
		{
			IItem IItem((void*)Itemxx);
			if (IItem.GetType() == -2 || IItem.GetType() == 19 || IItem.GetType() == 0 || IItem.GetType() == -3 || IItem.GetType() == -1)
			{
				if (setgem == 240)
				{
					dsstype = 1; phyatk = 17; magatk = 17; agi = 8;
					hpinc = 250; mpinc = 200;
					if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 18; else otp = 18;
				}
				else if (setgem == 239)
				{
					dsstype = 1; phyatk = 17; magatk = 17; wis = 8;
					hpinc = 250; mpinc = 200;
					if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 18; else otp = 18;
				}
				else if (setgem == 238)
				{
					dsstype = 1; phyatk = 17; magatk = 17; intel = 8;
					hpinc = 250; mpinc = 200;
					if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 18; else otp = 18;
				}
				else if (setgem == 237)
				{
					dsstype = 1; phyatk = 17; magatk = 17; hp = 8;
					hpinc = 250; mpinc = 200;
					if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 18; else otp = 18;
				}
				else if (setgem == 236)
				{
					dsstype = 1; phyatk = 17; magatk = 17; str = 8;
					hpinc = 250; mpinc = 200;
					if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 18; else otp = 18;
				}
				else if (setgem == 235)
				{
					dsstype = 2; phyatk = 14; magatk = 14; agi = 5;
					hpinc = 200; mpinc = 150;
					if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 15; else otp = 15;
				}
				else if (setgem == 234)
				{
					dsstype = 2; phyatk = 14; magatk = 14; wis = 5;
					hpinc = 200; mpinc = 150;
					if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 15; else otp = 15;
				}
				else if (setgem == 233)
				{
					dsstype = 2; phyatk = 14; magatk = 14; intel = 5;
					hpinc = 200; mpinc = 150;
					if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 15; else otp = 15;
				}
				else if (setgem == 232)
				{
					dsstype = 2; phyatk = 14; magatk = 14; hp = 5;
					hpinc = 200; mpinc = 150;
					if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 15; else otp = 15;
				}
				else if (setgem == 231)
				{
					dsstype = 2; phyatk = 14; magatk = 14; str = 5;
					hpinc = 200; mpinc = 150;
					if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 15; else otp = 15;
				}
				else if (setgem == 230)
				{
					dsstype = 3; phyatk = 12; magatk = 12; agi = 3;
					hpinc = 130; mpinc = 110;
					if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 12; else otp = 12;
				}
				else if (setgem == 229)
				{
					dsstype = 3; phyatk = 12; magatk = 12; wis = 3;
					hpinc = 130; mpinc = 110;
					if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 12; else otp = 12;
				}
				else if (setgem == 228)
				{
					dsstype = 3; phyatk = 12; magatk = 12; intel = 3;
					hpinc = 130; mpinc = 110;
					if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 12; else otp = 12;
				}
				else if (setgem == 227)
				{
					dsstype = 3; phyatk = 12; magatk = 12; hp = 3;
					hpinc = 130; mpinc = 110;
					if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 12; else otp = 12;
				}
				else if (setgem == 226)
				{
					dsstype = 3; phyatk = 12; magatk = 12; str = 3;
					hpinc = 130; mpinc = 110;
					if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 12; else otp = 12;
				}
				else if (setgem == 225)
				{
					dsstype = 4; phyatk = 10; magatk = 10; agi = 3;
					hpinc = 110; mpinc = 90;
					if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 10; else otp = 10;
				}
				else if (setgem == 224)
				{
					dsstype = 4; phyatk = 10; magatk = 10; wis = 3;
					hpinc = 110; mpinc = 90;
					if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 10; else otp = 10;
				}
				else if (setgem == 223)
				{
					dsstype = 4; phyatk = 10; magatk = 10; intel = 3;
					hpinc = 110; mpinc = 90;
					if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 10; else otp = 10;
				}
				else if (setgem == 222)
				{
					dsstype = 4; phyatk = 10; magatk = 10; hp = 3;
					hpinc = 110; mpinc = 90;
					if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 10; else otp = 10;
				}
				else if (setgem == 221)
				{
					dsstype = 4; phyatk = 10; magatk = 10; str = 3;
					hpinc = 110; mpinc = 90;
					if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 10; else otp = 10;
				}
				else if (setgem == 220)
				{
					dsstype = 5; phyatk = 8; magatk = 8; agi = 2;
					hpinc = 90; mpinc = 70;
					if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 8; else otp = 8;
				}
				else if (setgem == 219)
				{
					dsstype = 5; phyatk = 8; magatk = 8; wis = 2;
					hpinc = 90; mpinc = 70;
					if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 8; else otp = 8;
				}
				else if (setgem == 218)
				{
					dsstype = 5; phyatk = 8; magatk = 8; intel = 2;
					hpinc = 90; mpinc = 70;
					if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 8; else otp = 8;
				}
				else if (setgem == 217)
				{
					dsstype = 5; phyatk = 8; magatk = 8; hp = 2;
					hpinc = 90; mpinc = 70;
					if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 8; else otp = 8;
				}
				else if (setgem == 216)
				{
					dsstype = 5; phyatk = 8; magatk = 8; str = 2;
					hpinc = 90; mpinc = 70;
					if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 8; else otp = 8;
				}
				else if (setgem == 215)
				{
					dsstype = 6; phyatk = 6; magatk = 6; agi = 2;
					hpinc = 70; mpinc = 50;
					if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 6; else otp = 6;
				}
				else if (setgem == 214)
				{
					dsstype = 6; phyatk = 6; magatk = 6; wis = 2;
					hpinc = 70; mpinc = 50;
					if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 6; else otp = 6;
				}
				else if (setgem == 213)
				{
					dsstype = 6; phyatk = 6; magatk = 6; intel = 2;
					hpinc = 70; mpinc = 50;
					if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 6; else otp = 6;
				}
				else if (setgem == 212)
				{
					dsstype = 6; phyatk = 6; magatk = 6; hp = 2;
					hpinc = 70; mpinc = 50;
					if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 6; else otp = 6;
				}
				else if (setgem == 211)
				{
					dsstype = 6; phyatk = 6; magatk = 6; str = 2;
					hpinc = 70; mpinc = 50;
					if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 6; else otp = 6;
				}
				else if (setgem == 210)
				{
					dsstype = 7; phyatk = 4; magatk = 4; agi = 1;
					hpinc = 50; mpinc = 30;
					if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 4; else otp = 4;
				}
				else if (setgem == 209)
				{
					dsstype = 7; phyatk = 4; magatk = 4; wis = 1;
					hpinc = 50; mpinc = 30;
					if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 4; else otp = 4;
				}
				else if (setgem == 208)
				{
					dsstype = 7; phyatk = 4; magatk = 4; intel = 1;
					hpinc = 50; mpinc = 30;
					if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 4; else otp = 4;
				}
				else if (setgem == 207)
				{
					dsstype = 7; phyatk = 4; magatk = 4; hp = 1;
					hpinc = 50; mpinc = 30;
					if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 4; else otp = 4;
				}
				else if (setgem == 206)
				{
					dsstype = 7; phyatk = 4; magatk = 4; str = 1;
					hpinc = 50; mpinc = 30;
					if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 4; else otp = 4;
				}
				else if (setgem == 205)
				{
					dsstype = 8; phyatk = 2; magatk = 2; agi = 1;
					hpinc = 30; mpinc = 10;
					if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 2; else otp = 2;
				}
				else if (setgem == 204)
				{
					dsstype = 8; phyatk = 2; magatk = 2; wis = 1;
					hpinc = 30; mpinc = 10;
					if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 2; else otp = 2;
				}
				else if (setgem == 203)
				{
					dsstype = 8; phyatk = 2; magatk = 2; intel = 1;
					hpinc = 30; mpinc = 10;
					if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 2; else otp = 2;
				}
				else if (setgem == 202)
				{
					dsstype = 8; phyatk = 2; magatk = 2; hp = 1;
					hpinc = 30; mpinc = 10;
					if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 2; else otp = 2;
				}
				else if (setgem == 201)
				{
					dsstype = 8; phyatk = 2; magatk = 2; str = 1;
					hpinc = 30; mpinc = 10;
					if (IItem.GetType() == -1 || (IItem.GetType() == -3 && Class == 4)) eva = 2; else otp = 2;
				}
			}

			if (IItem.GetType() >= 1 && IItem.GetType() <= 6)
			{
				if (setgem == 240)
				{
					dsstype = 1; def = 18; agi = 7;
				}
				else if (setgem == 239)
				{
					dsstype = 1; def = 18; wis = 7;
				}
				else if (setgem == 238)
				{
					dsstype = 1; def = 18; intel = 7;
				}
				else if (setgem == 237)
				{
					dsstype = 1; def = 18; hp = 7;
				}
				else if (setgem == 236)
				{
					dsstype = 1; def = 18; str = 7;
				}
				else if (setgem == 235)
				{
					dsstype = 2; def = 16; agi = 5;
				}
				else if (setgem == 234)
				{
					dsstype = 2; def = 16; wis = 5;
				}
				else if (setgem == 233)
				{
					dsstype = 2; def = 16; intel = 5;
				}
				else if (setgem == 232)
				{
					dsstype = 2; def = 16; hp = 5;
				}
				else if (setgem == 231)
				{
					dsstype = 2; def = 16; str = 5;
				}
				else if (setgem == 230)
				{
					dsstype = 3; def = 14; agi = 3;
				}
				else if (setgem == 229)
				{
					dsstype = 3; def = 14; wis = 3;
				}
				else if (setgem == 228)
				{
					dsstype = 3; def = 14; intel = 3;
				}
				else if (setgem == 227)
				{
					dsstype = 3; def = 14; hp = 3;
				}
				else if (setgem == 226)
				{
					dsstype = 3; def = 14; str = 3;
				}
				else if (setgem == 225)
				{
					dsstype = 4; def = 12; agi = 3;
				}
				else if (setgem == 224)
				{
					dsstype = 4; def = 12; wis = 3;
				}
				else if (setgem == 223)
				{
					dsstype = 4; def = 12; intel = 3;
				}
				else if (setgem == 222)
				{
					dsstype = 4; def = 12; hp = 3;
				}
				else if (setgem == 221)
				{
					dsstype = 4; def = 12; str = 3;
				}
				else if (setgem == 220)
				{
					dsstype = 5; def = 10; agi = 2;
				}
				else if (setgem == 219)
				{
					dsstype = 5; def = 10; wis = 2;
				}
				else if (setgem == 218)
				{
					dsstype = 5; def = 10; intel = 2;
				}
				else if (setgem == 217)
				{
					dsstype = 5; def = 10; hp = 2;
				}
				else if (setgem == 216)
				{
					dsstype = 5; def = 10; str = 2;
				}
				else if (setgem == 215)
				{
					dsstype = 6; def = 8; agi = 2;
				}
				else if (setgem == 214)
				{
					dsstype = 6; def = 8; wis = 2;
				}
				else if (setgem == 213)
				{
					dsstype = 6; def = 8; intel = 2;
				}
				else if (setgem == 212)
				{
					dsstype = 6; def = 8; hp = 2;
				}
				else if (setgem == 211)
				{
					dsstype = 6; def = 8; str = 2;
				}
				else if (setgem == 210)
				{
					dsstype = 7; def = 6; agi = 1;
				}
				else if (setgem == 209)
				{
					dsstype = 7; def = 6; wis = 1;
				}
				else if (setgem == 208)
				{
					dsstype = 7; def = 6; intel = 1;
				}
				else if (setgem == 207)
				{
					dsstype = 7; def = 6; hp = 1;
				}
				else if (setgem == 206)
				{
					dsstype = 7; def = 6; str = 1;
				}
				else if (setgem == 205)
				{
					dsstype = 8; def = 4; agi = 1;
				}
				else if (setgem == 204)
				{
					dsstype = 8; def = 4; wis = 1;
				}
				else if (setgem == 203)
				{
					dsstype = 8; def = 4; intel = 1;
				}
				else if (setgem == 202)
				{
					dsstype = 8; def = 4; hp = 1;
				}
				else if (setgem == 201)
				{
					dsstype = 8; def = 4; str = 1;
				}
			}

			if (!CBase::IsDeleted((int)player) && IItem.GetType() == -3 && otp && *(DWORD*)((int)player + 460) == 4)
			{
				eva = otp;
				otp = 0;
			}

			if (isItemSuit(index) || isItemCustomWeapon(index) || isItemRiding(index)) {
				int GStat = GetStat;
				if (isBattleRiding(index)) {
					int Satiety = GStat / 100;
					if (Satiety)
						GStat -= (Satiety * 100);
				}


				int AddingType = SuitStats.count(index) ? SuitStats.find(index)->second.Type : 0;
				int Multiply = SuitStats.count(index) ? SuitStats.find(index)->second.Multiply : 3;

				if (Multiply < 2)
					Multiply = 2;

				switch (AddingType) {
				case 0:
					hp += GStat >= 6 ? (((GStat - 5) * Multiply) + 10) : GStat * (Multiply - 1);
					break;
				case 1:
					str += GStat >= 6 ? (((GStat - 5) * Multiply) + 10) : GStat * (Multiply - 1);
					break;
				case 2:
					hp += GStat >= 6 ? (((GStat - 5) * Multiply) + 10) : GStat * (Multiply - 1);
					break;
				case 3:
					intel += GStat >= 6 ? (((GStat - 5) * Multiply) + 10) : GStat * (Multiply - 1);
					break;
				case 4:
					wis += GStat >= 6 ? (((GStat - 5) * Multiply) + 10) : GStat * (Multiply - 1);
					break;
				case 5:
					agi += GStat >= 6 ? (((GStat - 5) * Multiply) + 10) : GStat * (Multiply - 1);
					break;
				default:
					hp += GStat >= 6 ? (((GStat - 5) * Multiply) + 10) : GStat * (Multiply - 1);
					break;
				}
			}

			if (TimedItems.count(index) && TimedItems.find(index)->second.Wearable != 1) {
				if (IPlayer.GetBuffValue(BuffNames::TimedCheck) != index) {
					int GetPetTime = TimedItems.find(index)->second.Time;
					if (GetPetTime > 0) {
						if (!PetLifeCheck.count(iid)) {
							CDBSocket::Write(89, "ddd", *(DWORD *)((int)player + 452), (int)time(0) + GetPetTime, iid);
							*(DWORD*)(Itemxx + 68) = GetTickCount() + (2000 * GetPetTime);
							*(DWORD*)(Itemxx + 72) = 0;
							CItem::OnTimer(Itemxx, 0);
							PetLifeCheck.replaceInsert(iid, (int)time(0) + GetPetTime);
						}
					}
				}
			}

			if (isItemRiding(index) && RidingCollectionIndex.count(index)) {
				int Type = RidingCollectionIndex.find(index)->second;
				if (RidingCollections.count(Type) && !IPlayer.IsBuff(5500 + Type)) {
					RidingCollection ridingCollection = RidingCollections.find(Type)->second;
					bool isCollection = !ridingCollection.Indexes.empty();
					for (int i = 0; i < ridingCollection.Indexes.size(); i++) {

						if (ridingCollection.Indexes[i] == index)
							continue;

						if (!CPlayer::_FindItem((int)player, ridingCollection.Indexes[i], 1)) {
							isCollection = false;
							break;
						}
					}

					if (isCollection)
						updateRidingCollection(player, Type, 1, ridingCollection.Stat, ridingCollection.Rate);
				}
			}
		}

		if (ItemStat)
		{
			PerfShotCheck = ItemStat / 100000000;
			ItemStat -= (100000000 * PerfShotCheck);
		}

		if (ItemStat)
		{
			int dg1typecheck = ItemStat / 10000000;
			if (dg1typecheck) dg1stat = 1;
			if (dg1typecheck > 0) dg1type = (dg1typecheck - 1);
			ItemStat -= (10000000 * dg1typecheck);
		}

		if (ItemStat)
		{
			int dg1statcheck = ItemStat / 1000000;
			if (dg1statcheck > 0) dg1stat = (dg1statcheck + 1);
			ItemStat -= (1000000 * dg1statcheck);
		}

		if (ItemStat)
		{
			int dg2typecheck = ItemStat / 100000;
			if (dg2typecheck) dg2stat = 1;
			if (dg2typecheck > 0) dg2type = (dg2typecheck - 1);
			ItemStat -= (100000 * dg2typecheck);
		}

		if (ItemStat)
		{
			int dg2statcheck = ItemStat / 10000;
			if (dg2statcheck > 0) dg2stat = (dg2statcheck + 1);
			ItemStat -= (10000 * dg2statcheck);
		}

		if (ItemStat && index >= 2986 && index <= 3009)
		{
			int yinyanggrade = ItemStat / 100;
			prefix = yinyanggrade + 1;
			ItemStat -= (100 * yinyanggrade);
		}

		if (ItemStat)
			QigongGrade = ItemStat % 100;

		if (index >= 3199 && index <= 3201 && prefix == 0)
			prefix = 1;

		if (index >= 2986 && index <= 3009 && prefix == 0)
			prefix = 1;

		if (index >= 3018 && index <= 3020 && GetStat)
			prefix = GetStat / 1000;

		if (index >= 3381 && index <= 3383)
		{
			if (!GetStat || GetStat < 0) {
				itemStat.Enter();
				GetItemStat[iid] = 0;
				itemStat.Leave();
			}
			CPlayer::Write(player, 194, "dd", iid, 100);
			if (index == 3381) CPlayer::Write(player, 193, "ddd", iid, 101, 10);
			if (index == 3382) CPlayer::Write(player, 193, "ddd", iid, 101, 11);
			if (index == 3383) CPlayer::Write(player, 193, "ddd", iid, 101, 12);

			if (index == 3383 && !GetStat)
				CPlayer::Write(player, 193, "ddd", iid, 100, GetStat + 2);
			else
				CPlayer::Write(player, 193, "ddd", iid, 100, GetStat + 1);
		}

		if (index >= 3384 && index <= 3386)
		{
			if (GetStat)
			{
				int Stat = GetStat / 1000;
				int Value = GetStat % 100;
				CPlayer::Write(player, 194, "dd", iid, Value);
				CPlayer::Write(player, 193, "ddd", iid, Value, Stat);
			}
		}

		if (GetStat && (isItemCustomWeapon(index) || isItemSuit(index) || isItemRiding(index))) {
			int GStat = GetStat;
			if (isBattleRiding(index)) {
				int Satiety = GStat / 100;
				if (Satiety)
					GStat -= (Satiety * 100);
			}
			if (GStat)
				upgrlvl = GStat;
		}

		if (isItemRidingArmor(index)) {
			upgrlvl = GetStat;

			if (GetStat > 0 && GetStat <= 10 && GetBattleRidingGrade(index) > 0) {
				if (GetBattleRidingType(index) == 1) {
					if (index == 7883 || index == 7889 || index == 7895 || index == 7901)
						str += RidingHelmet[GetBattleRidingGrade(index) - 1][GetStat - 1];
					else
						intel += RidingHelmet[GetBattleRidingGrade(index) - 1][GetStat - 1];
				}
				if (GetBattleRidingType(index) == 2)
					hp += RidingSaddle[GetBattleRidingGrade(index) - 1][GetStat - 1];
				if (GetBattleRidingType(index) == 3)
					xdefense += RidingArmor[GetBattleRidingGrade(index) - 1][GetStat - 1];
				if (GetBattleRidingType(index) == 4)
					xdefense += RidingCloth[GetBattleRidingGrade(index) - 1][GetStat - 1];
				if (GetBattleRidingType(index) == 5)
					eva += RidingMagnet[GetBattleRidingGrade(index) - 1][GetStat - 1];
			}
		}
	}
	else {
		IChar IPlayer2(player);
		if (info & 1)
			refill = IPlayer2.GetBuffValue(BuffNames::SoulPocketAmount);
		else {
			itemStat.Enter();
			if (GetItemStat.count(iid))
				refill = GetItemStat.find(iid)->second;
			itemStat.Leave();
		}
	}

	int restorecount = RestoredIIDs.findExists(iid);

	int dg1 = (dg1type << 24) + (dg1stat << 16);
	int dg2 = (dg2type << 24) + (dg2stat << 16);

	remaintime = PetLifeCheck.findExists(iid);
	if (remaintime)
		remaintime -= (int)time(0);

	CPlayer::Write(player, Type, "wdbddbbbbbbbbwbbdbbbbwwwwbbbbbbbbbbwddd", index, iid, prefix, info, amount, maxend, curend, setgem, xatk, xmagic, xdefense, xhit, xevasion, xprotect, upgrlvl, upgrrate, remaintime, x, y, restorecount, dsstype, phyatk, magatk, def, absorb, eva, otp, hpinc, mpinc, str, hp, intel, wis, agi, PerfShotCheck, QigongGrade, dg1, dg2, refill);
}

void ItemFixes()
{
	Interface<IMemory> Memory;
	Memory->Fill(0x00458039, IMemory::_I_NOP, 8);
	Memory->Hook(0x0045803f, ModsSendItemInfo);
	Memory->HookAPI(0x00426750, ModsItemPutInfo);
	Memory->Hook(0x0042748c, ModsSendUpdateItemInfo);
	Memory->Hook(0x0045ec94, ModsSendStorageList);
	Memory->Hook(0x0045f4f9, ModsSendStallList);
	Memory->Hook(0x0045e65c, ModsSendTradeList);
	Memory->Hook(0x00467fd5, SendList);
	//Memory->Hook(0x004681D5, RefreshList);
	Memory->Hook(0x00467c26, SendAdd);
	Memory->Hook(0x0046b50f, SendAssassinList);
}