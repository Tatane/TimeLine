#ifndef FACT_H
#define FACT_H

#include <ctime>
#include <string>
#include "ADateTime.h"

class Fact
{
    unsigned int id;
	ADateTime startTime;
	ADateTime endTime;
	std::string title;
	std::string description;

public:
	Fact(void);
	virtual ~Fact(void);

    void setId(int id);
	void setStartTime(const ADateTime & dateTime);
	void setStartTime(int year, int month, int day, int hour, int minute, int second);
	void setEndTime(const ADateTime & dateTime);
	void setEndTime(int year, int month, int day, int hour, int minute, int second);
	void setTitle(std::string text);
	void setDescription(std::string text);

    int getId() const;
	ADateTime getStartTime() const;
	ADateTime getEndTime() const;
	std::string getTitle() const;
	std::string getDescription() const;

};

#endif // FACT_H
