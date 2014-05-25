CFLAGS  = -g -Wall

searchesandsorts: main.o project_1.o project_2.o util.o counter.o timer.o
	g++ $(CFLAGS) main.o project_1.o project_2.o util.o counter.o timer.o -lm  -o searchesandsorts

main.o: main.cpp
	g++ $(CFLAGS) -c main.cpp

project_2.o: project_2.cpp 
	g++ $(CFLAGS) -c project_2.cpp
	
project_1.o: project_1.cpp 
	g++ $(CFLAGS) -c project_1.cpp

util.o: util.cpp
	g++ $(CFLAGS) -c util.cpp 

counter.o: counter.cpp
	g++ $(CFLAGS) -c counter.cpp

timer.o: timer.cpp
	g++ $(CFLAGS) -c timer.cpp
clean:
	rm -rf *.o *.gch *.csv *.png searchesandsorts
