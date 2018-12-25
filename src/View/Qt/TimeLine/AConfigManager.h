#pragma once

#include <string>

class AConfigManager
{
public:
	
	~AConfigManager();

	static std::unique_ptr<AConfigManager> & getInstance();

	std::string getDateDisplayFormat() const { return mDateDisplayFormat; }
	std::string getTimeDisplayFormat() const { return mTimeDisplayFormat; }
	std::string getDatabaseFileFullPath() const { return mDatabaseFileFullPath; }
	std::string getDatabaseFileRelativePath() const { return mDatabaseFileRelativePath; }

private:
	AConfigManager();
	void readConfigFile();

	static std::unique_ptr<AConfigManager> mConfigManager;

	std::string mDateDisplayFormat;
	std::string mTimeDisplayFormat;
	std::string mDatabaseFileFullPath;
	std::string mDatabaseFileRelativePath;
};

