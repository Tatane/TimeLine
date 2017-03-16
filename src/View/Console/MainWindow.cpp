#include "MainWindow.h"
#include <iostream>
#include <cstdio>
#include "DAL/DataAcces.h"

using namespace std;

MainWindow::MainWindow(std::vector<Fact*> * vec)
	: vecFacts(vec)
{
}


MainWindow::~MainWindow(void)
{
}

enum Commands{
	DisplayFacts = 1,
	CreateNewFact,
	Quit,
	NbCommands	
};

void MainWindow::loop()
{
	bool exitLoop = false;
	do {
		displayMenu();

		int carac = 0;
		//cin>>carac;
		
		string s;
		getline(cin, s);
		sscanf(s.c_str(), "%d", &carac);

		switch (carac) {
		case DisplayFacts:
			displayFacts();
			break;
		case CreateNewFact:
			displayCreateNewFact();
			break;
		case Quit:
			exitLoop = true;
		}
	

	} while (exitLoop == false);
	
}

void MainWindow::displayFacts() const
{
	std::vector<Fact*>::const_iterator it;
	for(it=vecFacts->begin(); it != vecFacts->end(); ++it)
	{
		Fact* evt = *it;
		std::cout<<evt->getStartTime().toString()<<" - "<<evt->getEndTime().toString()<<" - "<<evt->getTitle()<<" - "<<evt->getDescription()<<std::endl;
	}
	
}

void MainWindow::displayCreateNewFact()
{
	Fact * newFact = new Fact;
	
	//while(int c = getchar() && c!=EOF){};

	char title[100];
	cout<<"TITLE : ";
	//fscanf(stdin, "%100s", title);
	fgets(title, 100, stdin);
	cout<<title<<endl;	
	newFact->setTitle(string(title));


	char description[1000];
	cout<<"DESCRIPTION : ";
	fgets(description, 1000, stdin);
	//cin>>description;
	cout<<description<<endl;	
	newFact->setDescription(string(description));

	int year = 0, month = 0, day = 0, hour = 0, minute = 0, second = 0;
	cout<<"START of Fact"<<endl<<"----------"<<endl;
	cout<<"Date (YYYY-MM-DD) : ";
	fscanf(stdin, "%4d-%2d-%2d", &year, &month, &day);
	cout<<"Time (hh:mm:ss : ";
	fscanf(stdin, "%d:%d:%d", &hour, &minute, &second);
	
	cout<<year<<"-"<<month<<"-"<<day<<" "<<hour<<":"<<minute<<":"<<second<<endl;
	newFact->setStartTime(year, month, day, hour, minute, second);

	cout<<"END of Fact"<<endl<<"----------"<<endl;
	cout<<"Date (YYYY-MM-DD) : ";
	fscanf(stdin, "%4d-%2d-%2d", &year, &month, &day);
	cout<<"Time (hh:mm:ss : ";
	fscanf(stdin, "%d:%d:%d", &hour, &minute, &second);
	
	cout<<year<<"-"<<month<<"-"<<day<<" "<<hour<<":"<<minute<<":"<<second<<endl;
	newFact->setEndTime(year, month, day, hour, minute, second);

	cout<<endl<<"NEW FACT will be created : "<<endl;
	cout<<newFact->getTitle()<<endl;
	cout<<newFact->getDescription()<<endl;
	cout<<newFact->getStartTime().toString()<<endl;
	cout<<newFact->getEndTime().toString()<<endl;

	DataAcces::getInstance()->insertFact(newFact);
}

void MainWindow::displayMenu() const
{
	std::cout<<"---- MENU ----"<<endl;
	std::cout<<DisplayFacts<<" - Display Facts"<<endl;
	std::cout<<CreateNewFact<<" - Create NEW fact"<<endl;
	std::cout<<Quit<<" - Quit"<<endl;
}
