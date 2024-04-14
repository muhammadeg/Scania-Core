bool __fastcall GenMonsterReloadCheck(void* MonsterValue, void* edx, int argument) {
	if (reloadingM)
		return false;

	return Undefined::CheckValues(MonsterValue, argument);
}

int GetChannelPlayerAround(int Genmonster, int range) {

	char N[0x298u];
	memset(N, 0, sizeof(N));
	int GetSetXY[2];
	GetSetXY[0] = *(DWORD *)(Genmonster + 56);
	GetSetXY[1] = *(DWORD *)(Genmonster + 60);
	*(DWORD *)(N + 316) = *(DWORD *)(Genmonster + 36);
	*(DWORD *)(N + 320) = Undefined::MapCheck(*(DWORD *)(Genmonster + 36));
	CChar::SetXY((int)N, (int)GetSetXY);

	return CMonster::GetObjectAround(*(void **)((int)N + 320), (int)N + 324, range);
}

int GetChannelObjectAround(int Genmonster, int range) {

	char N[0x298u];
	memset(N, 0, sizeof(N));
	int GetSetXY[2];
	GetSetXY[0] = *(DWORD *)(Genmonster + 56);
	GetSetXY[1] = *(DWORD *)(Genmonster + 60);
	*(DWORD *)(N + 316) = *(DWORD *)(Genmonster + 36);
	*(DWORD *)(N + 320) = Undefined::MapCheck(*(DWORD *)(Genmonster + 36));
	CChar::SetXY((int)N, (int)GetSetXY);

	return CPlayer::GetObjectAround(*(void **)((int)N + 320), (int)N + 324, range);
}
int __fastcall GenMonsterCheck(void* MonsterValue, void* edx) {

	int Check = Undefined::GetValue(MonsterValue);

	if (Check) {
		int Genmonster = *(DWORD *)(Check + 4);
		int area = *(DWORD *)(Genmonster + 40);
		if (area < 0 && *(DWORD *)(Genmonster + 76) <= GetTickCount()) {
			int Channel = ((area * -1) % 10);
			int MapX = *(DWORD *)(Genmonster + 56) >> 13;
			int MapY = *(DWORD *)(Genmonster + 60) >> 13;
			if (Channel > ChannelActivated || !ChannelMaps.count((MapX*1000) + MapY)) {
				*(DWORD *)(Genmonster + 76) = CTools::Rate(2000, 5000) + GetTickCount();

				if (*(DWORD *)(Genmonster + 80) == 1000)
					*(DWORD *)(Genmonster + 80) = 1100;
			}
			else {
				if (*(DWORD *)(Genmonster + 80) == 1100)
					*(DWORD *)(Genmonster + 80) = 1000;
			}
		}
	}

	return Check;
}

char* __cdecl MonsterChannel(int Monster, int Genmonster) {

	if (reloadingM)
		return 0;

	int Channel = 0;

	int area = *(DWORD *)(Genmonster + 40);
	if (area < 0)
		Channel = ((area * -1) % 10);

	char* MonsterOffset = CMonster::NewMonster(Monster, Genmonster);
	if (MonsterOffset && Channel)
		SetObjectChannel((int)MonsterOffset, Channel);
		
	return MonsterOffset;
}

void __fastcall MonsterSendCreate(void *Monster, void *edx, int Player, int Argument)
{

	IChar IPlayer((void*)Player);
	IChar IMonster(Monster);

	if (IMonster.GetChannel() != IPlayer.GetChannel())
		return;

	CMonster::SendCreate(Monster, Player, Argument);
}

void __cdecl MonsterSendCreateInSight(void *monster, unsigned char Type, char* format, short index, long id, long x, long y, unsigned short direction, long curhp, long maxhp, unsigned long gState, unsigned __int64 mState64, char* guildName, char race, long GID, char* userName)
{

	IChar IMonster(monster);
	CChar::WriteInSight(monster, 0x33, "wdddwddIIsbdsIIbd", index, id, x, y, direction, curhp, maxhp,
		(unsigned __int64)gState, mState64, guildName, race, GID, userName,
		(__int64)0, (__int64)0, 0, IMonster.GetChannel());

	CChar::WriteInSight(monster, 148, "dI", id, (__int64)0);
}

void __cdecl MonsterSendCreatePacket(void *player, unsigned char Type, char* format, short index, long id, long x, long y, unsigned short direction, long curhp, long maxhp, unsigned long gState, unsigned __int64 mState64, char* guildName, char race, long GID, char* userName)
{

	TargetFind myTarget(1, 0, id);
	int monster = (int)myTarget.getTarget();
	IChar IMonster((void*)monster);
	IChar IPlayer(player);

	if (IPlayer.GetChannel() != IMonster.GetChannel())
		return;

	CPlayer::Write(player, 0x33, "wdddwddIIsbdsIIbd", index, id, x, y, direction, curhp, maxhp,
		(unsigned __int64)gState, mState64, guildName, race, GID, userName,
		(__int64)0, (__int64)0, 0, IMonster.GetChannel());

	CPlayer::Write(player, 148, "dI", id, (__int64)0);
}

int __cdecl MonsterWriteExclusive(unsigned char Type, char* format, short index, int id, int x, int y, unsigned short direction, int curhp, int maxhp, unsigned long gState, unsigned __int64 mState64, char* guildName, char race, long GID, char* userName)
{

	TargetFind myTarget(1, 0, id);
	int monster = (int)myTarget.getTarget();
	IChar IMonster((void*)monster);
	return CObject::WriteExclusive(0x33, "wdddwddIIsbdsIIbd", index, id, x, y, direction, curhp, maxhp,
		(unsigned __int64)gState, mState64, guildName, race, GID, userName,
		(__int64)0, (__int64)0, 0, IMonster.GetChannel());
}

int __fastcall MonsterScanSight(int Monster, void *edx)
{

	IChar IMonster((void*)Monster);

	if (ChannelActivated && ChannelMaps.count(IMonster.GetMapIndex())) {
		int Channel = IMonster.GetChannel();

		int NewTarget = 0;
		int Around = IMonster.GetPlayerListAround(*(DWORD*)(Monster + 544) >> 5);
		while (Around) {
			IChar Object((void*)CBaseList::Offset((void*)Around));

			if (!NewTarget && Object.IsValid() && Object.GetChannel() == Channel && !CChar::IsGState((int)Object.GetOffset(), 0x2000) && *(DWORD *)((int)Object.GetOffset() + 456) != 4) {
				NewTarget = (int)Object.GetOffset();
				CIOObject::_AddRef(NewTarget, (volatile LONG *)((int)NewTarget + 356));
			}

			Around = CBaseList::Pop((void*)Around);
		}

		return NewTarget;
	}

	return CMonsterReal::ScanSight(Monster);
}

int GetObjectChannel(int Object) {
	return ObjectChannels.findExists(Object);
}

void SetObjectChannel(int Object, int Channel) {
	if (!Channel)
		ObjectChannels.erase(Object);
	else
		ObjectChannels.replaceInsert(Object,Channel);
}

bool is_file_exist(const char *fileName)
{
	std::ifstream infile(fileName);
	return infile.good();
}

void GenMonsterChannel() {

	if (is_file_exist("./Config/GenmonsterC.txt")) {
		remove("./Config/Genmonster.txt");
		rename("./Config/GenmonsterC.txt", "./Config/Genmonster.txt");
	}

	string line;

	ifstream fin;
	fin.open("./Config/Genmonster.txt");
	ofstream temp;
	temp.open("./Config/temp.txt");
	int CurArea = -1;
	while (getline(fin, line))
	{
		if (line[0] == ';') {
			temp << line << endl;
			continue;
		}

		int index = 0, map = 0, area = 0, max = 0, cycle = 0, rect1x = 0, rect1y = 0, rect2x = 0, rect2y = 0;

		std::vector<std::string> lineParameters = getExplode("(", ")", line);
		for (int i = 0; i < lineParameters.size(); i++) {
			if (!index && sscanf(lineParameters[i].c_str(), "index %d", &index) == 1)
				continue;
			if (!map && sscanf(lineParameters[i].c_str(), "map %d", &map) == 1)
				continue;
			if (!area && sscanf(lineParameters[i].c_str(), "area %d", &area) == 1)
				continue;
			if (!max && sscanf(lineParameters[i].c_str(), "max %d", &max) == 1)
				continue;
			if (!cycle && sscanf(lineParameters[i].c_str(), "cycle %d", &cycle) == 1)
				continue;
			if (!rect1x && sscanf(lineParameters[i].c_str(), "rect %d %d %d %d", &rect1x, &rect1y, &rect2x, &rect2y) == 4)
				continue;
		}
		temp << line << endl;
		if (index) {
			if (area > 0) {
				for (int i = 0; i < 9; i++) {
					temp << "(genmonster (index " << index << ") (map " << map << ") (area " << CurArea << ") (max " << max << ") (cycle " << cycle << ") (rect " << rect1x << " " << rect1y << " " << rect2x << " " << rect2y << "))" << endl;
					CurArea--;
				}
				CurArea--;
			}
		}
	}

	temp.close();
	fin.close();
	rename("./Config/Genmonster.txt", "./Config/GenmonsterC.txt");
	rename("./Config/temp.txt", "./Config/Genmonster.txt");
}


int __fastcall CObjectDBOpen(int Object, void *edx, char* File)
{

	bool isGenM = false;

	if (std::string(File) == "Config\\GenMonster.txt") {
		isGenM = true;
		GenMonsterChannel();
	}

	int Result = CObjectDB::Open(Object, File);

	if (isGenM) {
		remove("./Config/Genmonster.txt");
		rename("./Config/GenmonsterC.txt", "./Config/Genmonster.txt");
	}

	return Result;
}

int __fastcall ChannelAround(int Object, void* edx) {
	
	return 0;
}

int __cdecl ChatFix(unsigned char Type, char* format, char* name, char* msg)
{

	TargetFind myTarget(name);
	int player = (int)myTarget.getTarget();
	IChar IPlayer((void*)player);
	return CObject::WriteExclusive(Type, "ssddd", name, msg, 2513, 1325, IPlayer.GetChannel());
}

void __fastcall MagicSkillsFix(int Monster, void* edx, int Player) {

	IChar IMonster((void*)Monster);
	IChar IPlayer((void*)Player);

	int Channel = IPlayer.GetChannel();
	if (Channel)
		*(DWORD *)(Monster + 516) = Channel * -1;

	(*(void(__thiscall **)(int, DWORD))(*(DWORD *)Monster + 196))(Monster, Player);
}

void __fastcall CMapSendPacket(DWORD Player, void *edx, int Packet)
{

	(*(void(__thiscall **)(DWORD, int))(*(DWORD *)Player + 40))(Player, Packet);
}

int __fastcall CBaseNext(int Object, void* edx)
{

	IChar IObject((void*)Object);
	int NextObject = Object;

	while (NextObject = CBase::Next(NextObject)) {
		IChar IObjectNext((void*)NextObject);
		if (IObjectNext.GetType() == 0)
			return NextObject;
	}

	return 0;
}

int __fastcall CBasePlayerNext(int Object, void *edx)
{

	IChar NObject((void*)Object);
	int Type = NObject.GetType();

	while (Object && Type != 0) {
		Object = CBase::Next(Object);
		IChar IObject((void*)Object);
		Type = IObject.GetType();
	}

	IChar IObject((void*)Object);

	int Channel = IObject.GetChannel();
	int NextObject = Object;

	while (NextObject = CBase::Next(NextObject)) {
		IChar IObjectNext((void*)NextObject);
		if (IObjectNext.GetType() == 0 && IObjectNext.GetChannel() == Channel)
			return NextObject;
	}

	return 0;
}

void __cdecl ItemSendCreate(void *player, unsigned char Type, char* format, WORD index, long iid, long x, long y, long amount)
{

	int ItemChannel = (ChannelActivated && ChannelItems.count(iid)) ? ChannelItems.findValue(iid) : 0;

	CPlayer::Write(player, 0x36, "wdddddd", index, iid, x, y, 0xffffffff, amount, ItemChannel);
}

DWORD __cdecl PrepItemDrop(unsigned char Type, char* format, WORD index, long iid, long x, long y, long amount)
{

	int ItemChannel = ChannelActivated ? ChannelItems.findExists(iid) : 0;

	return CObject::WriteExclusive(0x36, "wdddddd", index, iid, x, y, 0xffffffff, amount, ItemChannel);
}

int __cdecl DropItemClean(unsigned char Type, const char *Format, int itemid)
{

	if (ChannelActivated)
		ChannelItems.erase(itemid);

	return CObject::WriteExclusive(Type, Format, itemid);
}

void ChannelSystem()
{
	Interface<IMemory> Memory;
	Interface<ITools> Tools;

	//Memory->Hook(0x490A26, CMapSendPacket, 0xe8, 5);
	//Memory->Hook(0x49296A, CMapSendPacket, 0xe8, 6);
	//Memory->Hook(0x4909DC, CBaseNext);
	//Memory->Hook(0x490A8C, CBasePlayerNext, 0xe8, 5);
	Memory->Hook(0x00493C99, DropItemClean);
	Memory->Hook(0x004266D8, DropItemClean);
	Memory->Hook(0x004269B8, ItemSendCreate);
	Memory->Hook(0x00426FD1, PrepItemDrop);
	Memory->Hook(0x0042DEFE, PrepItemDrop);
	Memory->Hook(0x441F69, MagicSkillsFix, 0xe8, 6);
	Memory->Hook(0x460F96, ChatFix);
	Memory->Hook(0x4387C1, GenMonsterReloadCheck);
	Memory->Hook(0x4387D4, GenMonsterCheck);
	//Memory->Hook(0x43A075, MonsterChannel);

	Memory->Hook(0x0043a577, MonsterSendCreatePacket);		// CMonster::SendCreate
	Memory->Hook(0x0043ab6f, MonsterSendCreatePacket);		// CMonsterReal::SendCreate
	Memory->Hook(0x0044150e, MonsterSendCreateInSight);	// CMonsterGuildWar::Create
	Memory->Hook(0x0043a1de, MonsterSendCreateInSight);	// CMonster::Create
	Memory->Hook(0x004403e9, MonsterSendCreateInSight);	// CMonsterTowerBoss::Create
	Memory->Hook(0x004928F2, MonsterWriteExclusive);	// CMonsterGuildWar::Create
	Memory->Hook(0x00442011, MonsterSendCreateInSight);	// CMonsterMagic::Create
	Memory->Hook(0x00442dd7, MonsterSendCreateInSight);	// CMonsterMaguniMaster::Create
	Memory->Hook(0x0044332a, MonsterSendCreateInSight);	// CMonsterBigBirdMother::Create
	Memory->Hook(0x00444275, MonsterSendCreateInSight);	// CMonsterBigBirdMaster::Create
	Memory->Hook(0x004449f7, MonsterSendCreateInSight);	// CMonsterSiegeGun::Create
	Memory->Hook(0x0044528a, MonsterSendCreateInSight);	// CMonsterSiegeGunBall::Create
}
