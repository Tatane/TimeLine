#ifndef FACT_H
#define FACT_H

#include <ctime>
#include <string>
#include <vector>
#include "ADateTime.h"
#include "ACategory.h"

class Fact
{
    unsigned int id;
	ADateTime startTime;
	ADateTime endTime;
	std::string title;
	std::string description;
    std::vector<int> mCategoriesId;

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
    void setCategory(const std::vector<int> & category) { mCategoriesId = category; }

    int getId() const;
	ADateTime getStartTime() const;
	ADateTime getEndTime() const;
	std::string getTitle() const;
	std::string getDescription() const;
    std::vector<std::shared_ptr<ACategory>> getCategories() const;/* const { return mCategory; }*/

};

#endif // FACT_H
