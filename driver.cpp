#include <iostream>
#include <fstream>
#include "archive.h"

using namespace std;

int main(int args, char* argsv[]){	
	// Checks and reads file
	ifstream in(argsv[1]);

	if(!in){
		cout << "Usage: psi_lineage.x csv_file" << endl;
		return 0;
	}
	
	// Creates archive for Psi brothers
	archive Psi(in);
	
	Psi.printList();
	
	cout << endl << "Goodbye." << endl;
	return 0;
}
