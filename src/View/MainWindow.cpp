#include "MainWindow.h"
#include <iostream>

MainWindow::MainWindow(void)
{
}


MainWindow::~MainWindow(void)
{
}

void MainWindow::displayEvents(const std::vector<Event*> & vecEvents) const
{
	std::vector<Event*>::const_iterator it;
	for(it=vecEvents.begin(); it != vecEvents.end(); ++it)
	{
		Event* evt = *it;
		std::cout<<evt->getStartTime().getText()<<" - "<<evt->getEndTime().getText()<<" - "<<evt->getTitle()<<" - "<<evt->getDescription()<<std::endl;
	}
	
}
