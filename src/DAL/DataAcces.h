#ifndef DATAACCES_H
#define DATAACCES_H

#include <vector>
#include "POCO/Fact.h"
#include "sqlite3.h"
#include "ACategory.h"

static const char * TABLE_FACT = "Fact";
static const char * TABLE_FACT_COLUMN_ID = "id";
static const char * TABLE_FACT_COLUMN_STARTTIME = "startTime";
static const char * TABLE_FACT_COLUMN_ENDTIME = "endTime";
static const char * TABLE_FACT_COLUMN_TITLE = "title";
static const char * TABLE_FACT_COLUMN_DESCRIPTION = "description";
static const char * TABLE_FACT_COLUMN_CATEGORYID = "categoryId";

class DataAcces
{
private:
	DataAcces(void);
	sqlite3 * db;

	std::string convertDateTimeToStorageString(const ADateTime & dateTime) const;
	ADateTime convertStorageStringToDateTime(std::string str) const;

public:
	static DataAcces * getInstance();
	static DataAcces * instance;
	~DataAcces(void);

	bool open();
    void getAllFacts(std::vector<Fact *> & vecFacts);
    void getFacts(const ADateTime & begin, const ADateTime & end);
    void insertFact(Fact & newFact);
    bool deleteFact(const Fact &);
    bool updateFact(const Fact &);
    bool recreateDatabase() ;
    void getDatesBounds(ADateTime & minimumStartDate, ADateTime & maximumEndDate);
	void getAllCategories(ACategoriesCollection * vecCategories);

    struct Columns_Fact_Table{
        enum {
            idField,
            startField,
            endField,
            titleField,
            descriptionField,
			categoryIdField
        };
    };

	struct Columns_Category_Table
	{
		enum
		{
			idField,
			nameField
		};
	};

	void databaseStatementToFact(sqlite3_stmt * stmt, Fact * fact);
	std::unique_ptr<ACategory> databaseStatementToCategory(sqlite3_stmt * stmt);

};

#endif // DATAACCES_H
