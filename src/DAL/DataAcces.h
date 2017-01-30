#ifndef DATAACCES_H
#define DATAACCES_H

#include <vector>
#include "POCO/Event.h"
#include "sqlite3.h"


static const char * TABLE_EVENT = "Event";
static const char * TABLE_EVENT_COLUMN_ID = "id";
static const char * TABLE_EVENT_COLUMN_STARTTIME = "startTime";
static const char * TABLE_EVENT_COLUMN_ENDTIME = "endTime";
static const char * TABLE_EVENT_COLUMN_TITLE = "title";
static const char * TABLE_EVENT_COLUMN_DESCRIPTION = "description";

class DataAcces
{
private:
	DataAcces(void);
	sqlite3 * db;
public:
	static DataAcces * getInstance();
	static DataAcces * instance;
	~DataAcces(void);

	void getAllEvents(std::vector<Event*> * vecEvents);
    void getEvents(const TimeHour & begin, const TimeHour & end);
    void insertEvent(Event * newEvent);
    bool deleteEvent(const Event &);
    void updateEvent(const Event &);
    bool recreateDatabase() ;

    struct Columns_Event_Table{
        enum {
            idField,
            startField,
            endField,
            titleField,
            descriptionField
        };
    };

	void databaseStatementToEvent(sqlite3_stmt * stmt, Event * event);

};

#endif // DATAACCES_H
