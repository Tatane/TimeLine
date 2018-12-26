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
