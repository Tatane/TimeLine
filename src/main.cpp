#include "DAL/DataAcces.h"
#include "POCO/Fact.h"
#include "View/Console/MainWindow.h"

#include <cstdio>
#include <vector>

int main(int argc, char* argv[])
{
	
	
	std::vector<Fact*> vecFacts;
	DataAcces::getInstance()->getAllFacts(&vecFacts);



	MainWindow mw(&vecFacts);
	mw.loop();

	// detruire les Facts présents dans le vecteur :
	std::vector<Fact*>::const_iterator it;
	for(it = vecFacts.begin(); it != vecFacts.end(); ++it)
	{
		delete *it;
	}

}


