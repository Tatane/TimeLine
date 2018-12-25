#include "ADateTime.h"
#include <ctime>
#include <sstream>
#include <cstring>

ADateTime::ADateTime(void)
{
    memset(&t, 0, sizeof(t));
}


ADateTime::~ADateTime(void)
{
}

void ADateTime::set(int year, int month, int day, int hour, int minute, int second)
{
	

	t.tm_year = year - 1900;		// !!!
	t.tm_mon = month - 1;			// !!!
	t.tm_mday = day;
	t.tm_hour = hour;
	t.tm_min = minute;
	t.tm_sec = second;
}

std::string ADateTime::toString()
{
	return toString("%Y-%m-%d %H:%M:%S");
}

std::string ADateTime::toString(const char * format)
{
	char buf[256];
	int s = sizeof(buf);
	std::strftime(buf, sizeof(buf), format, &t);

	return std::string(buf);

}


