all: timeline

timeline: main.o POCO/TimeHour.o POCO/Event.o DAL/DataAcces.o View/Console/MainWindow.o DAL/sqlite3.o
	g++ -g main.o POCO/TimeHour.o POCO/Event.o DAL/DataAcces.o DAL/sqlite3.o View/Console/MainWindow.o -o TimeLine -lpthread 

main.o: main.cpp
	g++ -c -g -I. main.cpp

POCO/TimeHour.o: POCO/TimeHour.cpp POCO/TimeHour.h
	g++ -c -g POCO/TimeHour.cpp -o POCO/TimeHour.o

POCO/Event.o: POCO/Event.cpp POCO/Event.h
	g++ -c -g POCO/Event.cpp -o POCO/Event.o

DAL/DataAcces.o: DAL/DataAcces.cpp DAL/DataAcces.h
	g++ -c -g -I. DAL/DataAcces.cpp -o DAL/DataAcces.o

DAL/sqlite3.o: DAL/sqlite3.h DAL/sqlite3.c
	gcc -c -g DAL/sqlite3.c -o DAL/sqlite3.o

View/Console/MainWindow.o: View/Console/MainWindow.h View/Console/MainWindow.cpp DAL/DataAcces.h
	g++ -c -g -I. View/Console/MainWindow.cpp -o View/Console/MainWindow.o

