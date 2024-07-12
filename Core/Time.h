#pragma warning(disable: 4996)

namespace Time
{
	const std::string GetHour() {
		time_t     now = time(0);
		struct tm  tstruct;
		char       buf[80];
		tstruct = *localtime(&now);
		strftime(buf, sizeof(buf), "%H", &tstruct);
		return buf;
	}

	const std::string GetTime() {
		time_t     now = time(0);
		struct tm  tstruct;
		char       buf[80];
		tstruct = *localtime(&now);
		strftime(buf, sizeof(buf), "%X", &tstruct);
		return buf;
	}

	const std::string GetDate() {
		time_t     now = time(0);
		struct tm  tstruct;
		char       buf[80];
		tstruct = *localtime(&now);
		strftime(buf, sizeof(buf), "%Y/%m/%d", &tstruct);
		return buf;
	}

	const std::string GetYear() {
		time_t     now = time(0);
		struct tm  tstruct;
		char       buf[80];
		tstruct = *localtime(&now);
		strftime(buf, sizeof(buf), "%Y", &tstruct);
		return buf;
	}

	const std::string GetMinute() {
		time_t     now = time(0);
		struct tm  tstruct;
		char       buf[80];
		tstruct = *localtime(&now);
		strftime(buf, sizeof(buf), "%M", &tstruct);
		return buf;
	}

	const std::string GetSecond() {
		time_t     now = time(0);
		struct tm  tstruct;
		char       buf[80];
		tstruct = *localtime(&now);
		strftime(buf, sizeof(buf), "%S", &tstruct);
		return buf;
	}

	const std::string GetMonth() {
		time_t     now = time(0);
		struct tm  tstruct;
		char       buf[80];
		tstruct = *localtime(&now);
		strftime(buf, sizeof(buf), "%m", &tstruct);
		return buf;
	}

	const std::string GetDay() {
		time_t     now = time(0);
		struct tm  tstruct;
		char       buf[80];
		tstruct = *localtime(&now);
		strftime(buf, sizeof(buf), "%d", &tstruct);
		return buf;
	}

	const std::string GetDayName() {
		time_t     now = time(0);
		struct tm  tstruct;
		char       buf[80];
		tstruct = *localtime(&now);
		strftime(buf, sizeof(buf), "%A", &tstruct);
		return buf;
	}
}
time_t ConvertToTimeT(const char* timestamp)
{
	struct tm timeinfo;
	memset(&timeinfo, 0, sizeof(timeinfo));

	// Parse the timestamp string manually
	sscanf_s(timestamp, "%d/%d/%d %d:%d:%d %s", &timeinfo.tm_mon, &timeinfo.tm_mday, &timeinfo.tm_year,
		&timeinfo.tm_hour, &timeinfo.tm_min, &timeinfo.tm_sec, timeinfo.tm_hour < 12 ? "AM" : "PM");

	// Adjust the year and month in the struct tm
	timeinfo.tm_year -= 1900; // Years since 1900
	timeinfo.tm_mon -= 1;      // Months since January

							   // Convert struct tm to time_t
	return mktime(&timeinfo);
}