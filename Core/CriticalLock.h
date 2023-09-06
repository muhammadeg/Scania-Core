class CriticalLock {
	CRITICAL_SECTION *section;
public:
	CriticalLock(CRITICAL_SECTION * cs) : section(cs)
	{
		if (section)
			CIOCriticalSection::Enter(section);
	}

	~CriticalLock()
	{
		CIOCriticalSection::Leave(section);
	}
};