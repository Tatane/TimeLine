#include "Event.h"


Event::Event(void)
{
}


Event::~Event(void)
{
}

TimeHour Event::getStartTime() const
{
	return startTime;
}

TimeHour Event::getEndTime() const
{
	return endTime;
}

std::string Event::getTitle() const
{
	return title;
}

std::string Event::getDescription() const
{
	return description;
}


void Event::setStartTime(int year, int month, int day, int hour, int minute, int second)
{
	// lever exception si bad params values ?

	startTime.set(year, month, day, hour, minute, second);
}

void Event::setEndTime(int year, int month, int day, int hour, int minute, int second)
{
	endTime.set(year, month, day, hour, minute, second);
}

void Event::setTitle(std::string text)
{
	title = text;
}

void Event::setDescription(std::string text)
{
	description = text;
}


