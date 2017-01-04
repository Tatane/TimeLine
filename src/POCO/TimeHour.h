#ifndef TIMEHOUR_H
#define TIMEHOUR_H

#include <string>
#include <ostream>

class TimeHour
{
	tm t;

public:
	TimeHour(void);
	~TimeHour(void);

	void set(int year, int month, int day, int hour, int minute, int second);
	tm get() const { return t;}
	std::string getText();
};

#endif // TIMEHOUR_H
