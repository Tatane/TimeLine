#include "AConfigManager.h"

std::unique_ptr<AConfigManager>  AConfigManager::mConfigManager;

AConfigManager::AConfigManager()
{
}

void AConfigManager::readConfigFile()
{
	// TODO : read and parse .\config.ini

	mDateDisplayFormat = "%d %MMM %YYYY"; // TODO To be confirmed
	mTimeDisplayFormat = "%HH %mm %s"; // TODO To be confirmed
	mDatabaseFileFullPath = "";
	mDatabaseFileRelativePath = ".\\MaBDD"; // If RelativePath is not empty, ignore FullPath.
}


AConfigManager::~AConfigManager()
{
}

std::unique_ptr<AConfigManager>& AConfigManager::getInstance()
{
	if (nullptr == mConfigManager.get())
	{
		//mConfigManager = std::make_unique<AConfigManager>(); // Cant't use std::make_unique because constructor is private.
		mConfigManager = std::unique_ptr<AConfigManager>(new AConfigManager);
	}

	return mConfigManager;
}
