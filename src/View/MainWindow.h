#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <vector>
#include "../POCO/Event.h"

class MainWindow
{
public:
	MainWindow(void);
	~MainWindow(void);

	void displayEvents(const std::vector<Event*> & vecEvents) const;
};

#endif // MAINWINDOW_H
