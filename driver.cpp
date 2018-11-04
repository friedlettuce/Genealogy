#include <iostream>
#include <fstream>
#include <string>
#include "archive.h"

using namespace std;

void menu();
void getLine(archive& Psi);
void getBrother(archive& Psi);

int main(int args, char* argsv[]){	
	// Checks and reads file
	ifstream in(argsv[1]);

	if(!in){
		cout << "Usage: psi_lineage.x csv_file" << endl;
		return 0;
	}
	
	// Creates archive for Psi brothers
	archive Psi;
	Psi.readFile(in);

	cout << endl << "\tPsi Records" << endl;

	char select;
	do{
		menu();
		cin >> select;

		switch(tolower(select)){
			case 'l': 	
				Psi.printList();
				break;
			case 'o':
				getLine(Psi);
				break;
			case 'p':
				getBrother(Psi);
				break;	
			case 'q':
				break;
			default:	
				cout << "Not a valid entry" << endl;
				break;
		}
	} while(tolower(select) != 'q');

	cout << endl << "Goodbye." << endl;
	return 0;
}

void getLine(archive& Psi){
	cin.ignore();

	string brother;	// Gets the brother to search
	cout << "Enter a brother: ";
	getline(cin, brother);

	cout << endl;
	Psi.printLine(brother);
	cout << endl;
}

void getBrother(archive& Psi){
	cin.ignore();

	string brother;
	cout << "Enter a brother: ";
	getline(cin, brother);

	cout << endl;
	Psi.printBrother(brother);
	cout << endl;
}

void menu(){
	cout << "---------------------" << endl
	     << "L\tList Brothers" << endl
	     << "O\tPrint line of brother" << endl
	     << "P\tPrint brother" << endl
	     << "Q\tQuit" << endl << endl
	     << "> ";
}
