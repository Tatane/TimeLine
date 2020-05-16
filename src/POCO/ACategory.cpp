#include "ACategory.h"

ACategoriesCollection ACategories::mCategories;

ACategory::ACategory()
	: mId(0)
	, mName("")
{
}


ACategory::~ACategory()
{
}

bool ACategories::containsCategoryName(std::string name)
{
	for (auto pair : ACategories::getCategories())
	{
		if (pair.second->getName() == name)
		{
			return true;
		}
	}
	return false;
}
