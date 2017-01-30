#include "MainWindow.h"
#include <iostream>
#include <cstdio>
#include "DAL/DataAcces.h"

using namespace std;

MainWindow::MainWindow(std::vector<Event*> * vec)
	: vecEvents(vec)
{
}


MainWindow::~MainWindow(void)
{
}

enum Commands{
	DisplayEvents = 1,
	CreateNewEvent,
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

		char command[3] = "\0";
		fgets(command, 3, stdin);
		sscanf(command, "%d", &carac);

		int c;
		while (c=getchar() != '\n' && c != EOF){}

		switch (carac) {
		case DisplayEvents:
			displayEvents();
			break;
		case CreateNewEvent:
			displayCreateNewEvent();
			break;
		case Quit:
			exitLoop = true;
		}
	

	} while (exitLoop == false);
	
}

void MainWindow::displayEvents() const
{
	std::vector<Event*>::const_iterator it;
	for(it=vecEvents->begin(); it != vecEvents->end(); ++it)
	{
		Event* evt = *it;
		std::cout<<evt->getStartTime().toString()<<" - "<<evt->getEndTime().toString()<<" - "<<evt->getTitle()<<" - "<<evt->getDescription()<<std::endl;
	}
	
}

void MainWindow::displayCreateNewEvent()
{
	Event * newEvent = new Event;
	
	//while(int c = getchar() && c!=EOF){};

	char title[100];
	cout<<"TITLE : ";
	//fscanf(stdin, "%100s", title);
	fgets(title, 100, stdin);
	cout<<title<<endl;	
	newEvent->setTitle(string(title));


	char description[1000];
	cout<<"DESCRIPTION : ";
	fgets(description, 1000, stdin);
	//cin>>description;
	cout<<description<<endl;	
	newEvent->setDescription(string(description));

	int year = 0, month = 0, day = 0, hour = 0, minute = 0, second = 0;
	cout<<"START of Event"<<endl<<"----------"<<endl;
	cout<<"Date (YYYY-MM-DD) : ";
	fscanf(stdin, "%4d-%2d-%2d", &year, &month, &day);
	cout<<"Time (hh:mm:ss : ";
	fscanf(stdin, "%d:%d:%d", &hour, &minute, &second);
	
	cout<<year<<"-"<<month<<"-"<<day<<" "<<hour<<":"<<minute<<":"<<second<<endl;
	newEvent->setStartTime(year, month, day, hour, minute, second);

	cout<<"END of Event"<<endl<<"----------"<<endl;
	cout<<"Date (YYYY-MM-DD) : ";
	fscanf(stdin, "%4d-%2d-%2d", &year, &month, &day);
	cout<<"Time (hh:mm:ss : ";
	fscanf(stdin, "%d:%d:%d", &hour, &minute, &second);
	
	cout<<year<<"-"<<month<<"-"<<day<<" "<<hour<<":"<<minute<<":"<<second<<endl;
	newEvent->setEndTime(year, month, day, hour, minute, second);

	cout<<endl<<"NEW EVENT will be created : "<<endl;
	cout<<newEvent->getTitle()<<endl;
	cout<<newEvent->getDescription()<<endl;
	cout<<newEvent->getStartTime().toString()<<endl;
	cout<<newEvent->getEndTime().toString()<<endl;

	DataAcces::getInstance()->insertEvent(*newEvent);
}

void MainWindow::displayMenu() const
{
	std::cout<<"---- MENU ----"<<endl;
	std::cout<<DisplayEvents<<" - Display events"<<endl;
	std::cout<<CreateNewEvent<<" - Create NEW event"<<endl;
	std::cout<<Quit<<" - Quit"<<endl;
}
