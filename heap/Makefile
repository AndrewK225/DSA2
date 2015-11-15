useHeap.exe: useHeap.o heap.o hash.o
	g++ -std=c++11 -o useHeap.exe useHeap.o heap.o hash.o

useHeap.o: useHeap.cpp
	g++ -c -std=c++11 useHeap.cpp

heap.o: heap.cpp heap.h
	g++ -c -std=c++11 heap.cpp

hash.o: hash.cpp hash.h
	g++ -c  -std=c++11 hash.cpp

debug:
	g++ -g -o  -std=c++11 useHeapDebug.exe useHeap.cpp heap.cpp hash.cpp

clean:
	rm -f *.exe *.o *.stackdump *~

backup:
	test -d backups || mkdir backups
	cp *.cpp backups
	cp *.h backups
	cp Makefile backups
