#pragma once

#include <string>

class AConfigManager
{
public:
	
	~AConfigManager();

	static std::unique_ptr<AConfigManager> & getInstance();

	static std::string getDateDisplayFormat() { return getInstance()->mDateDisplayFormat; }
	static std::string getTimeDisplayFormat() { return getInstance()->mTimeDisplayFormat; }
	static std::string getDateTimeDisplayFormat() { return getInstance()->mDateTimeDisplayFormat; }
	static std::string getDatabaseFileFullPath() { return getInstance()->mDatabaseFileFullPath; }
	static std::string getDatabaseFileRelativePath() { return getInstance()->mDatabaseFileRelativePath; }

private:
	AConfigManager();
	void readConfigFile();

	static std::unique_ptr<AConfigManager> mConfigManager;

	std::string mDateDisplayFormat;
	std::string mTimeDisplayFormat;
	std::string mDateTimeDisplayFormat;
	std::string mDatabaseFileFullPath;
	std::string mDatabaseFileRelativePath;
};

