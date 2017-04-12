#ifndef DATAACCES_H
#define DATAACCES_H

#include <vector>
#include "POCO/Fact.h"
#include "sqlite3.h"


static const char * TABLE_FACT = "Fact";
static const char * TABLE_FACT_COLUMN_ID = "id";
static const char * TABLE_FACT_COLUMN_STARTTIME = "startTime";
static const char * TABLE_FACT_COLUMN_ENDTIME = "endTime";
static const char * TABLE_FACT_COLUMN_TITLE = "title";
static const char * TABLE_FACT_COLUMN_DESCRIPTION = "description";

class DataAcces
{
private:
	DataAcces(void);
	sqlite3 * db;
public:
	static DataAcces * getInstance();
	static DataAcces * instance;
	~DataAcces(void);

    void getAllFacts(std::vector<Fact *> & vecFacts);
    void getFacts(const TimeHour & begin, const TimeHour & end);
    void insertFact(Fact & newFact);
    bool deleteFact(const Fact &);
    bool updateFact(const Fact &);
    bool recreateDatabase() ;

    struct Columns_Fact_Table{
        enum {
            idField,
            startField,
            endField,
            titleField,
            descriptionField
        };
    };

	void databaseStatementToFact(sqlite3_stmt * stmt, Fact * fact);

};

#endif // DATAACCES_H
