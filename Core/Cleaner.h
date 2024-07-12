void InitItemCleaner(std::string FileName, std::string message) {

	std::string scan1 = "(" + message + " %d \"%[^\"]\")";
	std::string scan2 = "( " + message + " %d \"%[^\"]\")";

	std::string filePath = "./Config/" + FileName + ".txt";
	std::string cleanFilePath = "./Config/" + FileName + "Clean" + ".txt";

	ConcurrentMap<int, std::string> Names;
	FILE *filetx = fopen("./Config/Message.txt", "r");
	if (filetx != NULL)
	{
		char line[BUFSIZ];
		while (fgets(line, sizeof line, filetx) != NULL)
		{
			int Name = 0;
			char msg[BUFSIZ];
			if (sscanf(line, scan1.c_str(), &Name, &msg) == 2)
				Names[Name] = msg;
			else
				if (sscanf(line, scan2.c_str(), &Name, &msg) == 2)
					Names[Name] = msg;
		}
		fclose(filetx);
	}
	else
	{
		CConsole::Red("Config/Message.txt not found.", TEXTCOLOR_RED);
		return;
	}

	std::string line;

	std::ifstream fin;
	fin.open(filePath);
	std::ofstream temp;
	temp.open(cleanFilePath);
	int CurArea = -1;
	while (getline(fin, line))
	{
		if (line[0] == ';')
			continue;

		int index = 0;

		std::vector<std::string> lineParameters = getExplode("(", ")", line);
		for (int i = 0; i < lineParameters.size(); i++) {

			if (FileName == "InitNPC" || FileName == "Prefix") {
				if (!index && sscanf(lineParameters[i].c_str(), "index %d", &index) == 1)
					break;
				if (!index && sscanf(lineParameters[i].c_str(), "Index %d", &index) == 1)
					break;
			}
			else {
				if (!index && sscanf(lineParameters[i].c_str(), "name %d", &index) == 1)
					break;
				if (!index && sscanf(lineParameters[i].c_str(), "Name %d", &index) == 1)
					break;
			}
		}

		if (index)
			temp << ";" << (Names.count(index) ? Names.find(index)->second : "Unknown") << std::endl;

		temp << line << std::endl;
	}

	temp.close();
	fin.close();

	CConsole::Blue("%s has been generated.", cleanFilePath.c_str());
}