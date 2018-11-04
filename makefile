psi_lineage.x: driver.o archive.o family.o
	g++ -std=c++11 driver.o archive.o family.o -o psi_lineage.x

driver.o: driver.cpp archive.h
	g++ -g -c -std=c++11 driver.cpp

archive.o: archive.h archive.cpp family.h
	g++ -g -c -std=c++11 archive.cpp

family.o: family.h family.cpp
	g++ -g -c -std=c++11 family.cpp

clean:
	rm *.o psi_lineage.x
