#include "MainWindow.h"
#include <iostream>
#include <cstdio>

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

		//int carac = getchar();
		//fgetc(stdin);

		int carac = 0;
		cin>>carac;
		

		switch (carac) {
		case DisplayEvents:
			displayEvents();
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
		std::cout<<evt->getStartTime().getText()<<" - "<<evt->getEndTime().getText()<<" - "<<evt->getTitle()<<" - "<<evt->getDescription()<<std::endl;
	}
	
}

void MainWindow::displayMenu() const
{
	std::cout<<"---- MENU ----"<<endl;
	std::cout<<DisplayEvents<<" - Display events"<<endl;
	std::cout<<CreateNewEvent<<" - Create NEW event"<<endl;
	std::cout<<Quit<<" - Quit"<<endl;
}
