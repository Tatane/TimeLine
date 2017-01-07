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
}

void DataAcces::databaseStatementToEvent(sqlite3_stmt * statement, Event * event)
{
	int year, month, day, hour, minute, second;
	sscanf((const char *)sqlite3_column_text(statement, 0), "%d-%d-%d %d:%d:%d", &year, &month, &day, &hour, &minute, &second);
	event->setStartTime(year, month, day, hour, minute, second);

	sscanf((const char *)sqlite3_column_text(statement, 1), "%d-%d-%d %d:%d:%d", &year, &month, &day, &hour, &minute, &second);
	event->setEndTime(year, month, day, hour, minute, second);
	
	event->setTitle(std::string((const char*)sqlite3_column_text(statement, 2)));
	event->setDescription(std::string((const char*)sqlite3_column_text(statement, 3)));
}

