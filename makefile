flags = -static-libgcc -static-libstdc++

psi_lineage.x: driver.o archive.o brother.o
	g++ -std=c++11 driver.o archive.o brother.o -o psi flags

driver.o: driver.cpp archive.h
	g++ -c -std=c++11 driver.cpp flags

archive.o: archive.h archive.cpp brother.h
	g++ -c -std=c++11 archive.cpp flags

brother.o: brother.h brother.cpp
	g++ -c -std=c++11 brother.cpp flags

clean:
	rm psi *.o
