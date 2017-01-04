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
	/*
	Event * event1 = new Event();
	event1->setStartTime(2001, 01, 01, 0, 0, 0);
	event1->setEndTime(2001, 12, 31, 23, 59, 59);
	event1->setTitle("Annee 2001");
	event1->setDescription("Il s'agit de l'année 2001");
	vecEvents->push_back(event1);

	Event * event2 = new Event();
	event2->setStartTime(2014, 9, 2, 15, 0, 0);
	event2->setEndTime(2015, 9, 1, 23, 59, 59);
	event2->setTitle("PVT 2014");
	event2->setDescription("Premier PVT 2014-2015");
	vecEvents->push_back(event2);
	*/

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
		//std::cout<<event->getEndTime().getText()<<" "<<event->getDescription()<<std::endl;
		std::cout<<event->getText();
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

