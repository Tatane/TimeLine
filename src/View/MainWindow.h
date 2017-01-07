#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <vector>
#include "../POCO/Event.h"

class MainWindow
{
public:
	MainWindow(std::vector<Event*> *);
	~MainWindow(void);

	void loop();
	void displayEvents() const;
	void displayMenu() const;

private:
	std::vector<Event*> * vecEvents;
};

#endif // MAINWINDOW_H
