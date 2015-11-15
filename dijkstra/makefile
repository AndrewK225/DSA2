dijkstra.exe: dijkstra.o hash.o heap.o graph.o
	g++ -std=c++11 -o dijkstra.exe hash.o heap.o dijkstra.o graph.o

dijkstra.o: dijkstra.cpp
	g++ -std=c++11 -c dijkstra.cpp

heap.o: heap.cpp heap.h
	g++ -std=c++11 -c heap.cpp

hash.o: hash.cpp hash.h
	g++ -std=c++11 -c hash.cpp

graph.o: graph.cpp graph.h
	g++ -std=c++11 -c graph.cpp

debug:
	g++ -std=c++11 -g -o dijkstraDebug.exe dijkstra.cpp heap.cpp hash.cpp graph.cpp

backup:
	test -d backups || mkdir backups
	cp *.cpp backups
	cp *.h backups
	cp Makefile backups
