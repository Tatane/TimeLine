#ifndef ADATETIME_H
#define ADATETIME_H

#include <string>
#include <ostream>
#include <ctime>

class ADateTime
{
	tm t;

public:
	ADateTime(void);
	~ADateTime(void);

	void set(int year, int month, int day, int hour, int minute, int second);
	tm get() const { return t;}
	std::string toString();

	/*
		format :
		%Y Year
		%m Month
		%d Day
		%H Hour
		%M Minute
		%S Second
	*/
	std::string toString(const char * format);

    int year() const {return t.tm_year + 1900;}
    int month() const {return t.tm_mon + 1;}
    int day() const {return t.tm_mday;}
	int hour() const { return t.tm_hour; }
	int minute() const { return t.tm_min; }
	int seconde() const { return t.tm_sec; }
};

#endif // ADATETIME_H
