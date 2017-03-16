#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <vector>
#include "POCO/Fact.h"

class MainWindow
{
public:
	MainWindow(std::vector<Fact*> *);
	~MainWindow(void);

	void loop();
	void displayFacts() const;
	void displayMenu() const;
	void displayCreateNewFact();

private:
	std::vector<Fact*> * vecFacts;
};

#endif // MAINWINDOW_H
