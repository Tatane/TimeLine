#ifndef FACT_H
#define FACT_H

#include <ctime>
#include <string>
#include "ADateTime.h"
#include "ACategory.h"

class Fact
{
    unsigned int id;
	ADateTime startTime;
	ADateTime endTime;
	std::string title;
	std::string description;
	std::shared_ptr<ACategory> mCategory;

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
	void setCategory(std::shared_ptr<ACategory> category) { mCategory = category; }

    int getId() const;
	ADateTime getStartTime() const;
	ADateTime getEndTime() const;
	std::string getTitle() const;
	std::string getDescription() const;
	std::shared_ptr<ACategory> getCategory() const { return mCategory; }

};

#endif // FACT_H
