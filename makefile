flags = -L/bin/ld -static -std=c++11

psi_lineage.x: driver.o archive.o brother.o
	g++ $(flags) driver.o archive.o brother.o -o psi

driver.o: driver.cpp archive.h
	g++ -c $(flags) driver.cpp

archive.o: archive.h archive.cpp brother.h
	g++ -c $(flags) archive.cpp

brother.o: brother.h brother.cpp
	g++ -c $(flags) brother.cpp

clean:
	rm psi *.o
