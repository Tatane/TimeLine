all: timeline

timeline: main.o TimeHour.o Event.o DataAcces.o MainWindow.o
	g++ main.o POCO/TimeHour.o POCO/Event.o DAL/DataAcces.o DAL/sqlite3.o View/MainWindow.o -o TimeLine -lpthread -ldl

main.o: main.cpp
	g++ -c main.cpp

TimeHour.o:
	g++ -c POCO/TimeHour.cpp -o POCO/TimeHour.o

Event.o:
	g++ -c POCO/Event.cpp -o POCO/Event.o

DataAcces.o:
	g++ -c DAL/DataAcces.cpp -o DAL/DataAcces.o
	gcc -c DAL/sqlite3.c -o DAL/sqlite3.o

MainWindow.o:
	g++ -c View/MainWindow.cpp -o View/MainWindow.o

