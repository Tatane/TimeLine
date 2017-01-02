#include "TimeHour.h"
#include <ctime>
#include <sstream>

TimeHour::TimeHour(void)
{
}


TimeHour::~TimeHour(void)
{
}

void TimeHour::set(int year, int month, int day, int hour, int minute, int second)
{
	

	t.tm_year = year - 1900;		// !!!
	t.tm_mon = month - 1;			// !!!
	t.tm_mday = day;
	t.tm_hour = hour;
	t.tm_min = minute;
	t.tm_sec = second;
}

std::string TimeHour::getText()
{
	char buf[256];
	int s = sizeof(buf);
	std::strftime(buf, sizeof(buf), "%Y/%m/%d %H:%M:%S", &t);

	return std::string(buf);
}


