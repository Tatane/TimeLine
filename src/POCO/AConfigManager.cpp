#include "AConfigManager.h"

std::unique_ptr<AConfigManager>  AConfigManager::mConfigManager;

AConfigManager::AConfigManager()
{
	readConfigFile();
}

void AConfigManager::readConfigFile()
{
	// TODO : read and parse .\config.ini

	mDateDisplayFormat = "dd MMM yyyy"; // TODO To be confirmed
	mTimeDisplayFormat = "HH mm s"; // TODO To be confirmed
	mDateTimeDisplayFormat = "dd-MMM-yyyy HH:mm"; // To display a 'h' for the hour, put it between apostrophes: HH'h'mm
	mDatabaseFileFullPath = "";
    mDatabaseFileRelativePath = "TODO"; // If RelativePath is not empty, ignore FullPath.
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
