class IBuff
{
public:
	void* Offset;

public:
	IBuff()
	{
	}

	IBuff(void* Object);
	virtual ~IBuff();
	void *GetOffset();
	int GetValue();
	int GetBuffID();
	int GetTime();
	bool Exists();
	int GetType();
	void DeleteThis();
	void updateValue(int Value);
};