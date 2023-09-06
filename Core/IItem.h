class IItem
{
	public:
		void* Offset;

	public:
		IItem()
		{
		}
        
	IItem(void* Object);
    virtual ~IItem();
    void *GetOffset();
	int GetInfo();
	int GetType();
	bool Exists();
	int Prefix();
	int PrefixID();
	int GetIntEndurance();
	int GetEndurance();
	int GetIID();
	int CheckIndex();
	int GetItemClass();
	bool HighMemory();
	bool IsOrnament();
	bool IsMoney();
	bool IsGeneral();
	bool IsQuest();
	bool IsWeapon();
	bool IsMask();
	bool IsStandard();
	bool IsDefense();
	bool IsTransform();
	int GetInitItem();
	void IncreaseEndurance(int Value);
	void DecreaseEndurance(int Value);
	void SetInfo(int Value);
	int GetTalismanOA();
	int GetTalismanOM();
	int GetTOA();
	int GetUpgrade();
	void SetTalismanOA(int Value);
	void SetTalismanOM(int Value);
	void SetTOA(int Value);
	void SetUpgrade(int Value);
	int GetAmount();
	int GetSetGem();
	void SetSetGem(int Value);
	int LevelLimit();
	void SetLevelLimit(int Value);
	int GetItemPointerFromIID(void *Player,int IID);
	int GetGrade();
	int GetClass();
	int GetXDefense();
	int GetXDodge();
	int GetXHit();
	char GetXAttack();
	int GetXMagic();
	int GetUpgrRate();
};