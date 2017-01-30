#include "DAL/DataAcces.h"
#include "POCO/Event.h"
#include "View/Console/MainWindow.h"

#include <cstdio>
#include <vector>

int main(int argc, char* argv[])
{
	
	
	std::vector<Event*> vecEvents;
	DataAcces::getInstance()->getAllEvents(&vecEvents);



	MainWindow mw(&vecEvents);
	mw.loop();

	// detruire les Events présents dans le vecteur :
	std::vector<Event*>::const_iterator it;
	for(it = vecEvents.begin(); it != vecEvents.end(); ++it)
	{
		delete *it;
	}

}


