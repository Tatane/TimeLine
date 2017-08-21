#ifndef TIMEHOUR_H
#define TIMEHOUR_H

#include <string>
#include <ostream>
#include <ctime>

class TimeHour
{
	tm t;

public:
	TimeHour(void);
	~TimeHour(void);

	void set(int year, int month, int day, int hour, int minute, int second);
	tm get() const { return t;}
	std::string toString();

    int year() const {return t.tm_year + 1900;}
    int month() const {return t.tm_mon + 1;}
    int day() const {return t.tm_mday;}
};

#endif // TIMEHOUR_H
