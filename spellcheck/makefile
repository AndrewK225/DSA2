koe_spell.exe: koe_spellcheck.o hash.o
	g++ -o koe_spell.exe koe_spellcheck.o hash.o

koe_spellcheck.o: koe_spellcheck.cpp hash.h
	g++ -c -std=c++11 koe_spellcheck.cpp 

hash.o: hash.cpp hash.h
	g++ -c -std=c++11 hash.cpp hash.h

clean:
	rm -f *.exe *.o *.stackdump 
