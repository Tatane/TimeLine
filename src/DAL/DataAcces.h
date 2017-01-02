#ifndef DATAACCES_H
#define DATAACCES_H

#include <vector>
#include "../POCO/Event.h"

class DataAcces
{
private:
	DataAcces(void);
public:
	static DataAcces * getInstance();
	static DataAcces * instance;
	~DataAcces(void);

	void getAllEvents(std::vector<Event*> * vecEvents);
};

#endif // DATAACCES_H
