#include "DataAcces.h"
#include <sqlite3.h>

DataAcces * DataAcces::instance = NULL;

DataAcces::DataAcces(void)
{
	sqlite3 * db;
	sqlite3_open("maBDD", &db);

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

}

