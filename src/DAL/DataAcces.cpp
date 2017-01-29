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

void DataAcces::insertEvent(const Event & newEvent)
{
	std::cout<<"insertEvent"<<std::endl;
    std::cout<<newEvent.getStartTime().toString();

	sqlite3_stmt * statement;

	const char * insertReq = "INSERT INTO Event VALUES (?, ?, ?, ?)";
	int rc = sqlite3_prepare_v2(db, insertReq, strlen(insertReq), &statement, NULL);
    sqlite3_bind_text(statement, 1, newEvent.getStartTime().toString().c_str(), 20, SQLITE_STATIC);
    sqlite3_bind_text(statement, 2, newEvent.getEndTime().toString().c_str(), 20, SQLITE_STATIC);
    sqlite3_bind_text(statement, 3, newEvent.getTitle().c_str(), 100, SQLITE_STATIC);
    sqlite3_bind_text(statement, 4, newEvent.getDescription().c_str(), 1000, SQLITE_STATIC);
	
	sqlite3_step(statement);
	sqlite3_finalize(statement);
	
}

void DataAcces::databaseStatementToEvent(sqlite3_stmt * statement, Event * event)
{
	int year, month, day, hour, minute, second;

    const unsigned char * val = sqlite3_column_text(statement, idField);
    if (val != 0){
        int id = 0;
        std::cout<<"Field "<<idField<<" = "<<val<<std::endl;
        sscanf((const char *)val, "%d", &id);
        event->setId(id);
    } else {
        std::cout<<"No value"<<std::endl;
    }

    val = sqlite3_column_text(statement, startField);
	if (val != 0){
        std::cout<<"Field "<<startField<<" = "<<val<<std::endl;
		sscanf((const char *)val, "%d-%d-%d %d:%d:%d", &year, &month, &day, &hour, &minute, &second);
		event->setStartTime(year, month, day, hour, minute, second);
	} else {
		std::cout<<"No value"<<std::endl;
	}

    val = sqlite3_column_text(statement, endField);
	if (val != 0){
        std::cout<<"Field "<<endField<<" = "<<val<<std::endl;
		sscanf((const char *)val, "%d-%d-%d %d:%d:%d", &year, &month, &day, &hour, &minute, &second);
		event->setEndTime(year, month, day, hour, minute, second);
	} else {
		std::cout<<"No value"<<std::endl;
	}

    val = sqlite3_column_text(statement, titleField);
    if (val != 0){
        std::cout<<"Field "<<titleField<<" = "<<val<<std::endl;
        //sscanf((const char*)val, "%s")
        event->setTitle((const char*)val);
    }

    val = sqlite3_column_text(statement, descriptionField);
    if (val != 0){
        std::cout<<"Field "<<descriptionField<<" = "<<val<<std::endl;
        //sscanf((const char*)val, "%s")
        event->setDescription((const char*)val);
    }

/*	
	event->setTitle(std::string((const char*)sqlite3_column_text(statement, 2)));
	event->setDescription(std::string((const char*)sqlite3_column_text(statement, 3)));
*/
}

