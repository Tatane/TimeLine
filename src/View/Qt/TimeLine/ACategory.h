#pragma once
#include "string"
#include "map"

class ACategory
{
public:
	ACategory();
	~ACategory();

	void setId(int id) { mId = id; }
	int getId() const { return mId; }

	void setName(std::string name) { mName = name; }
	std::string getName() const { return mName; }

private:
	int mId;
	std::string mName;
};

typedef std::map <int,  std::shared_ptr<ACategory> > ACategoriesCollection;


class ACategories
{
public:
	static ACategoriesCollection& getCategories() { return mCategories; }
	//void setCategories(std::vector < std::unique_ptr<ACategory> > * categories) { mCategories = categories; }

	static bool containsCategoryName(std::string name);

private:
	static ACategoriesCollection mCategories;
};


