class ISkill
{

public:
	void *Offset;

public:
	ISkill()
	{
	}

	ISkill(void *Packet);
	virtual ~ISkill();

	void *GetOffset();
	int GetIndex();
	int GetGrade();
	int GetLoadingTime();
	int GetMaxGrade();
	int DecreaseMana();
	void *GetPlayer();
};