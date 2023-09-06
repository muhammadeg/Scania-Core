template<class T>
class Pointer {
public:
	Pointer(T* obj) {
		m_pointer = obj;
	}

	~Pointer() {
		delete m_pointer;
	}

	inline T* operator->()
	{
		return(m_pointer);
	}

	inline bool IsValid() const {
		return m_pointer != NULL;
	}

public:
	T* m_pointer;
};