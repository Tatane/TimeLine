#include "DataAcces.h"
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cassert>

DataAcces * DataAcces::instance = NULL;

DataAcces::DataAcces(void)
{
	if (sqlite3_open("maBDD", &db) != SQLITE_OK)
	{
		std::cerr<<sqlite3_errmsg(db)<<std::endl;
	} else {
		std::cout<<"Database opened"<<std::endl;
	}
}

DataAcces* DataAcces::getInstance()
{
	if (instance == NULL)
	{
		instance = new DataAcces();
	}

	return instance;
}

DataAcces::~DataAcces(void)
{
}

void DataAcces::getAllEvents(std::vector<Event*> * vecEvents)
{
	sqlite3_stmt * statement;
	const char * requete = "SELECT * FROM event";
	int ret = sqlite3_prepare_v2(db, requete, strlen(requete), &statement, NULL);
	if (ret != SQLITE_OK) {
		std::cerr<<"Error on slite3_prepare_v2"<<std::endl;
		exit(-1);
	}
	
	while (sqlite3_step(statement) == SQLITE_ROW){
		Event * event = new Event;
		databaseStatementToEvent(statement, event);
		vecEvents->push_back(event);
	}

    sqlite3_finalize(statement);
}

void DataAcces::getEvents(const TimeHour &begin, const TimeHour &end)
{
    assert(false && "DataAcces::getEvents is not implemented.");
}

bool DataAcces::deleteEvent(const Event &)
{
    assert(false && "DataAcces::deleteEvent is not implemented.");
}

void DataAcces::updateEvent(const Event &)
{
    assert(false && "DataAcces::updateEvent is not implemented.");
}

bool DataAcces::recreateDatabase()
{
    assert(false && "DataAcces::recreateDatabase is not implemented.");

    // TODO


    sqlite3_stmt * statement;

    const char * creationReq = "CREATE TABLE 'Event'('startTime' DateTime NOT NULL, 'endTime' DateTime NOT NULL)";
    //'title'	varchar(100),
    //'description'	varchar(1000),
    //'id'	INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE


    int ret = sqlite3_prepare_v2(db, creationReq, strlen(creationReq), &statement, NULL);
    if (ret != SQLITE_OK) {
        std::cerr<<"Error on slite3_prepare_v2"<<std::endl;
        exit(-1);
    }

    sqlite3_step(statement);

    sqlite3_finalize(statement);
}

void DataAcces::insertEvent(Event * newEvent)
{
	std::cout<<"insertEvent"<<std::endl;
    std::cout<<newEvent->getStartTime().toString();

	sqlite3_stmt * statement;

    char insertReq[256];
    sprintf(insertReq, "INSERT INTO %s (%s, %s, %s, %s) VALUES (?, ?, ?, ?)", TABLE_EVENT, TABLE_EVENT_COLUMN_STARTTIME, TABLE_EVENT_COLUMN_ENDTIME, TABLE_EVENT_COLUMN_TITLE, TABLE_EVENT_COLUMN_DESCRIPTION);
    int rc = sqlite3_prepare_v2(db, insertReq, strlen(insertReq), &statement, NULL);

    std::string param = newEvent->getStartTime().toString();
    rc = sqlite3_bind_text(statement, 1, param.c_str(), param.size(), SQLITE_STATIC);

    param = newEvent->getEndTime().toString();
    rc = sqlite3_bind_text(statement, 2, param.c_str(), param.size(), SQLITE_STATIC);

    param = newEvent->getTitle();
    rc = sqlite3_bind_text(statement, 3, param.c_str(), param.size(), SQLITE_STATIC);

    param = newEvent->getDescription();
    rc = sqlite3_bind_text(statement, 4, param.c_str(), param.size(), SQLITE_STATIC);
	
    rc = sqlite3_step(statement);

    rc = sqlite3_finalize(statement);

    // retrieve new id field (auto increment) :
    char req[256];
    sprintf(req, "SELECT seq FROM sqlite_sequence WHERE name='%s'", TABLE_EVENT);
    rc = sqlite3_prepare_v2(db, req, strlen(req), &statement, NULL);

    rc = sqlite3_step(statement);
    if ( rc == SQLITE_ROW)
    {
        int val = sqlite3_column_int(statement, 0);
        //newEvent->setId(val);
        int stop = 0;
    }

    rc = sqlite3_finalize(statement);
	
}

void DataAcces::databaseStatementToEvent(sqlite3_stmt * statement, Event * event)
{
	int year, month, day, hour, minute, second;

    const unsigned char * val = sqlite3_column_text(statement, Columns_Event_Table::idField);
    if (val != 0){
        int id = 0;
        std::cout<<"Field "<<Columns_Event_Table::idField<<" = "<<val<<std::endl;
        sscanf((const char *)val, "%d", &id);
        event->setId(id);
    } else {
        std::cout<<"No value"<<std::endl;
    }

    val = sqlite3_column_text(statement, Columns_Event_Table::startField);
	if (val != 0){
        std::cout<<"Field "<<Columns_Event_Table::startField<<" = "<<val<<std::endl;
		sscanf((const char *)val, "%d-%d-%d %d:%d:%d", &year, &month, &day, &hour, &minute, &second);
		event->setStartTime(year, month, day, hour, minute, second);
	} else {
		std::cout<<"No value"<<std::endl;
	}

    val = sqlite3_column_text(statement, Columns_Event_Table::endField);
	if (val != 0){
        std::cout<<"Field "<<Columns_Event_Table::endField<<" = "<<val<<std::endl;
		sscanf((const char *)val, "%d-%d-%d %d:%d:%d", &year, &month, &day, &hour, &minute, &second);
		event->setEndTime(year, month, day, hour, minute, second);
	} else {
		std::cout<<"No value"<<std::endl;
	}

    val = sqlite3_column_text(statement, Columns_Event_Table::titleField);
    if (val != 0){
        std::cout<<"Field "<<Columns_Event_Table::titleField<<" = "<<val<<std::endl;
        //sscanf((const char*)val, "%s")
        event->setTitle((const char*)val);
    }

    val = sqlite3_column_text(statement, Columns_Event_Table::descriptionField);
    if (val != 0){
        std::cout<<"Field "<<Columns_Event_Table::descriptionField<<" = "<<val<<std::endl;
        //sscanf((const char*)val, "%s")
        event->setDescription((const char*)val);
    }

/*	
	event->setTitle(std::string((const char*)sqlite3_column_text(statement, 2)));
	event->setDescription(std::string((const char*)sqlite3_column_text(statement, 3)));
*/
}

