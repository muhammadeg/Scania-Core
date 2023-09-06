#ifndef __SYSREGISTER_H
#define __SYSREGISTER_H

#include <Windows.h>
template<class T>

class SystemRegistration: public ConcurrentSet<T>
{
private:
	std::string regName;

public:
	SystemRegistration() {
		regName = "";
	}

	SystemRegistration(std::string rgName) {
		this->regName = rgName;
		std::string name = "./Database/" + regName + ".db";
		FILE *filekx = fopen(name.c_str(), "r");
		if (filekx != NULL)
		{
			char line[BUFSIZ];
			while (fgets(line, sizeof line, filekx) != NULL)
			{
				int pid = 0;
				if (sscanf(line, "(registration (PID %d))", &pid) == 1) {
					ConcurrentSet<T>::insert(pid);
				}
			}
			fclose(filekx);
		}
	}

	 void insert(T value) {
		if (!this->count(value)) {
			ConcurrentSet<T>::insert(value);
			if (!regName.empty()) {
				std::string Datko = "./Database/" + regName + ".db";
				std::fstream DGkLOG;
				DGkLOG.open(Datko, std::fstream::in | std::fstream::out | std::fstream::app);
				DGkLOG << "(registration (PID " << value << "))" << std::endl;
				DGkLOG.close();
			}
		}
	}

	void clear() {
		ConcurrentSet<T>::clear();
		std::string name = "./Database/" + regName + ".db";
		std::remove(name.c_str());
	}

	T randomSelect() {
		int n = CTools::Rate(0, this->size() - 1);
		auto it = std::begin(this->toSet());
		// 'advance' the iterator n times
		std::advance(it, n);
		return *it;
	}
};
#endif