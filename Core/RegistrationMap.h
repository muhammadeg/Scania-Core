#ifndef __MAPREGISTER_H
#define __MAPREGISTER_H

#include <Windows.h>
template<class T, class K>

class RegistrationMap: public ConcurrentMap<T,K>
{
private:
	std::string regName;

public:
	RegistrationMap() {
		regName = "";
	}

	RegistrationMap(std::string rgName) {
		this->regName = rgName;
		std::string name = "./Database/" + regName + ".db";
		FILE *filekx = fopen(name.c_str(), "r");
		if (filekx != NULL)
		{
			char line[BUFSIZ];
			while (fgets(line, sizeof line, filekx) != NULL)
			{
				int key = 0, value = 0;;
				if (sscanf(line, "(registration (Key %d)(Value %d))", &key,&value) == 2) 
					ConcurrentMap<T, K>::insert(std::pair<T,K>(key,value));
			}
			fclose(filekx);
		}
	}

	void removeLine(T key) {
		std::string Datko = "./Database/" + regName + ".db";
		std::string Datko1 = "./Database/" + regName + "Temp.db";
		string line;

		ifstream fin;
		fin.open(Datko.c_str());
		ofstream temp;
		temp.open(Datko1.c_str());

		while (getline(fin, line))
		{
			int Keya = 0;
			if (sscanf(line.c_str(), "(registration (Key %d)", &Keya) == 1) {
				if (Keya != key)
					temp << line << endl;
			}
		}

		temp.close();
		fin.close();
		remove(Datko.c_str());
		rename(Datko1.c_str(), Datko.c_str());
	}

	void insert(T key, K value) {
		ConcurrentMap<T, K>::replaceInsert(key, value);
		if (!regName.empty()) {
			removeLine(key);
			//Update Current
			std::string Datko = "./Database/" + regName + ".db";
			std::fstream DGkLOG;
			DGkLOG.open(Datko, std::fstream::in | std::fstream::out | std::fstream::app);
			DGkLOG << "(registration (Key " << key << ")(Value " << value << "))" << std::endl;
			DGkLOG.close();
		}
	}

	void erase(T key) {
		ConcurrentMap<T, K>::erase(key);
		removeLine(key);
	}

	void clear() {
		ConcurrentMap<T, K>::clear();
		std::string name = "./Database/" + regName + ".db";
		std::remove(name.c_str());
	}
};
#endif