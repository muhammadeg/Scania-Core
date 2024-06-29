#define g_MonsterCount *(DWORD*)0x4E1810;
#define g_NPCCount (DWORD*)0x4E1A98;
struct mobReload {
int Index;
int Map;
int X;
int Y;
int leftSpawn;
};

auto index = 1;
int CWarLoad = 0; 
std::vector<mobReload> UnReloaded;

void LoadConfig(std::string configName) {
	int *p_qPtr = new int;
	if (CObjectDB::Open((int)p_qPtr, configName.c_str()))
		CConsole::Blue("%s has been reloaded.", configName.c_str());

	else
		CConsole::Red("%s reloading has failed.", configName.c_str());
	delete[] p_qPtr;
}

//Quest.txt//
void QuestsReload() {
	int nObject = 0, nPtr = 0, nOffset = 0, nOther = 0;
	CQuest::ReleaseAll();
	Unnamed::sub_47E0D0(0x4E2118);
	nObject = Unnamed::nGetObject(0x4E210C, (int)&nPtr);
	if (nObject) {
		nOffset = *(DWORD *)(Unnamed::GetOffset(nObject) + 4);
		if (!CBase::IsDeleted(nOffset))
			CBase::Delete((void*)nOffset);

		Unnamed::sub_446090(nObject, (int)&nOther, 0);
	}
	Unnamed::sub_446000((void*)0x4E210C);
	Unnamed::sub_47E1C0(0x4E2118);
	LoadConfig("Config\\Quest.txt");
}


void removeMobs(std::vector<mobReload> &UnReloaded) {
	auto monsterCount = g_MonsterCount;
	do {
		TargetFind target(1, 0, index);
		IChar IMonster(target.getTarget());

		if (IMonster.IsOnline()) {
			if (UnReload.count(IMonster.GetMobIndex())) {
				mobReload reloadMob = mobReload();
				reloadMob.Index = IMonster.GetMobIndex();
				reloadMob.X = IMonster.GetX();
				reloadMob.Y = IMonster.GetY();
				reloadMob.Map = IMonster.GetMap();
				reloadMob.leftSpawn = MonsterDisappear.count((int)IMonster.GetOffset()) ? MonsterDisappear.findValue((int)IMonster.GetOffset()) - GetTickCount() : 0;

				UnReloaded.push_back(reloadMob);
			}

			if (IMonster.GetDef() != 54123) {
				IMonster.MobDelete();
				*(DWORD *)((int)IMonster.GetOffset() + 16) = -6;
			}
		}
		monsterCount = g_MonsterCount;
		index++;
	} while (monsterCount > InterlockedExchangeAdd(&summonPets, 0));
}

void ClearGenMonster() {
	CWarLoad = 1;

	UnReloaded.clear();
	CCastle::Stop();

	removeMobs(UnReloaded);
	int nObject = 0, nPtr = 0, nOffset = 0, nOther = 0;
	Unnamed::sub_47E0D0(0x4E187C);
	nObject = Unnamed::nGetObject(0x4E1870, (int)&nPtr);
	if (nObject) {
		nOffset = *(DWORD *)(Unnamed::GetOffset(nObject) + 4);
		
		Unnamed::sub_446090(nObject, (int)&nOther, 0);
	}
	Unnamed::sub_446000((void*)0x4E1870);
	Unnamed::sub_47E1C0(0x4E187C);
}

void LoadGenMonster() {
	GenMonsterChannel();
	LoadConfig("Config\\GenMonster.txt");

	for (auto x = UnReloaded.begin(); x != UnReloaded.end(); x++)
		Summon(0, x->Map, x->X, x->Y, x->Index, 1, 0, 0, x->leftSpawn, 0);
	CCastle::Start();

	if (is_file_exist("./Config/GenmonsterC.txt")) {
		remove("./Config/Genmonster.txt");
		rename("./Config/GenmonsterC.txt", "./Config/Genmonster.txt");
	}
	UnReloaded.clear();
}
//GenMonster.txt//
void GenMonsterReload() {
	reloadingM = 1;
	CGenMonster::Stop();
	ClearGenMonster();
	LoadGenMonster();
	CIOObject::AddTimer((int)(void*)0x4E1898, 1000, 0);
	*(DWORD**)0x004E1814 = (DWORD*)0;
	reloadingM = 0;
}

//InitMonster.txt
void InitMonsterReload() {
	reloadingM = 1;
	CInitMonster::Stop();
	ClearGenMonster();

	int nObject = 0, nPtr = 0, nOffset = 0, nOther = 0;

	CIOCriticalSection::Enter((void*)0x4E182C);
	nObject = Unnamed::nGetObject(0x4E1820, (int)&nPtr);
	if (nObject) {
		nOffset = *(DWORD *)(Unnamed::GetOffset(nObject) + 4);
		
		Unnamed::sub_446090(nObject, (int)&nOther, 0);
	}
	Unnamed::sub_446000((void*)0x4E1820);
	CIOCriticalSection::Leave((void*)0x4E182C);

	LoadConfig("Config\\InitMonster.txt");

	LoadGenMonster(); 

	CInitMonster::Start(); 
	*(DWORD**)0x004E1814 = (DWORD*)0;

	reloadingM = 0;
}

void InitNPCReload() {
	auto npcCount = *g_NPCCount;
	auto npccurindex = 1;
	do {
		int NPC = CNPC::FindNPC((char)npccurindex);
		if (NPC) {
			CBase::Delete((void*)NPC);
			*(DWORD *)(NPC + 16) = -6;
			CIOObject::Release((void*)NPC);
			CPlayer::WriteAll(57, "d", *(DWORD *)(NPC + 28));
		}
		npcCount = *g_NPCCount;
		npccurindex++;
	} while (npcCount > 0);
	CNPC::InitClose();
	int nObject = 0, nPtr = 0, nOffset = 0, nOther = 0;

	nObject = Unnamed::nGetObject(0x4E1A9C, (int)&nPtr);
	if (nObject) {
		nOffset = *(DWORD *)(Unnamed::GetOffset(nObject) + 4);
		if (!CBase::IsDeleted(nOffset))
			CBase::Delete((void*)nOffset);

		Unnamed::sub_446090(nObject, (int)&nOther, 0);
	}
	Unnamed::sub_446000((void*)0x4E1A9C);

	CNPC::GenClose();
	nObject = Unnamed::nGetObject(0x4E1AA8, (int)&nPtr);
	if (nObject) {
		nOffset = *(DWORD *)(Unnamed::GetOffset(nObject) + 4);
		if (!CBase::IsDeleted(nOffset))
			CBase::Delete((void*)nOffset);

		Unnamed::sub_446090(nObject, (int)&nOther, 0);
	}
	Unnamed::sub_446000((void*)0x4E1AA8);

	LoadConfig("Config\\InitNPC.txt");
	CNPC::Start();
	GetNPCList();
	ShowNPCList();
}

//InitItem.txt//
void InitItemReload() {

	CIOCriticalSection::Enter((void*)0x004e2078);
	CIOCriticalSection::Enter((void*)0x004e2098);
	CLink::MoveTo((void*)0x004e200c, (int)0x004e2004);
	CIOCriticalSection::Leave((void*)0x004e2098);
	for (DWORD a = *(DWORD*)0x004E2004; a != 0x004E2004; a = *(DWORD*)a)
	{
		if ((void*)(a - 428))
		{
			IChar IPlayer((void*)(a - 428));
			if (IPlayer.IsOnline())
				IPlayer.Buff(BuffNames::InitItemReload, BuffNames::BuffTime, 0);

		}
	}
	CIOCriticalSection::Leave((void*)0x004e2078);

	int nObject = 0, nPtr = 0, nOffset = 0, nOther = 0;
	nObject = Unnamed::nGetObject(0x4E10B4, (int)&nPtr);
	if (nObject) {
		nOffset = *(DWORD *)(Unnamed::GetOffset(nObject) + 4);
		if (nOffset)
			CInitItem::Release(nOffset, true);

		Unnamed::sub_446090(nObject, (int)&nOther, 0);
	}
	Unnamed::sub_446000((void*)0x4E10B4);

	LoadConfig("Config\\InitItem.txt");

	setInitItem();
}
