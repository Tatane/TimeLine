#include "Fact.h"
#include <cstdio>

Fact::Fact(void)
    : id(0)
    , startTime()
    , endTime()
    , title("")
    , description("")
{
}


Fact::~Fact(void)
{
}

int Fact::getId() const
{
    return id;
}

ADateTime Fact::getStartTime() const
{
	return startTime;
}

ADateTime Fact::getEndTime() const
{
	return endTime;
}

std::string Fact::getTitle() const
{
	return title;
}

std::string Fact::getDescription() const
{
	return description;
}

void Fact::setId(int id)
{
    this->id = id;
}

void Fact::setStartTime(const ADateTime & dateTime)
{
	startTime = dateTime;
}

void Fact::setStartTime(int year, int month, int day, int hour, int minute, int second)
{
	// lever exception si bad params values ?

	startTime.set(year, month, day, hour, minute, second);
}

void Fact::setEndTime(const ADateTime & dateTime)
{
	endTime = dateTime;
}

void Fact::setEndTime(int year, int month, int day, int hour, int minute, int second)
{
	endTime.set(year, month, day, hour, minute, second);
}

void Fact::setTitle(std::string text)
{
	title = text;
}

void Fact::setDescription(std::string text)
{
    description = text;
}
