all: timeline

timeline: main.o TimeHour.o Event.o DataAcces.o MainWindow.o
	g++ main.o POCO/TimeHour.o POCO/Event.o DAL/DataAcces.o View/MainWindow.o -o TimeLine

main.o: main.cpp
	g++ -c main.cpp

TimeHour.o:
	g++ -c POCO/TimeHour.cpp

Event.o:
	g++ -c POCO/Event.cpp

DataAcces.o:
	g++ -c DAL/DataAcces.cpp sqlite.c

MainWindow.o:
	g++ -c View/MainWindow.cpp

