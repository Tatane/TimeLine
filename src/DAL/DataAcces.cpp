#include "DataAcces.h"
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>

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

void DataAcces::insertEvent(const Event* event)
{
	std::cout<<"insertEvent"<<std::endl;
	std::cout<<event->getStartTime().toString();

	sqlite3_stmt * statement;

	const char * insertReq = "INSERT INTO Event VALUES (?, ?, ?, ?)";
	int rc = sqlite3_prepare_v2(db, insertReq, strlen(insertReq), &statement, NULL);
	sqlite3_bind_text(statement, 1, event->getStartTime().toString().c_str(), 20, SQLITE_STATIC);
	sqlite3_bind_text(statement, 2, "2002-12-31 23:59:59", 20, SQLITE_STATIC);
	sqlite3_bind_text(statement, 3, "année 2001", 11, SQLITE_STATIC);
	sqlite3_bind_text(statement, 4, "L'ANNEE 2001 environ", 21, SQLITE_STATIC);
	
	sqlite3_step(statement);
	sqlite3_finalize(statement);
	
}

void DataAcces::databaseStatementToEvent(sqlite3_stmt * statement, Event * event)
{
	int year, month, day, hour, minute, second;
	const unsigned char * val = sqlite3_column_text(statement, 0);
	if (val != 0){
		std::cout<<"Val="<<val<<std::endl;
		sscanf((const char *)val, "%d-%d-%d %d:%d:%d", &year, &month, &day, &hour, &minute, &second);
		event->setStartTime(year, month, day, hour, minute, second);
	} else {
		std::cout<<"No value"<<std::endl;
	}

	val = sqlite3_column_text(statement, 1);
	if (val != 0){
		std::cout<<"Val="<<val<<std::endl;
		sscanf((const char *)val, "%d-%d-%d %d:%d:%d", &year, &month, &day, &hour, &minute, &second);
		event->setEndTime(year, month, day, hour, minute, second);
	} else {
		std::cout<<"No value"<<std::endl;
	}
/*	
	event->setTitle(std::string((const char*)sqlite3_column_text(statement, 2)));
	event->setDescription(std::string((const char*)sqlite3_column_text(statement, 3)));
*/
}

