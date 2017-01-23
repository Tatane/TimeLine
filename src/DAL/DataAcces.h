#ifndef DATAACCES_H
#define DATAACCES_H

#include <vector>
#include "../POCO/Event.h"
#include "sqlite3.h"

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
	void insertEvent(const Event *);

	void databaseStatementToEvent(sqlite3_stmt * stmt, Event * event);

};

#endif // DATAACCES_H
