#include <iostream>
#include <fstream>
#include <string>
#include "archive.h"

using namespace std;

void menu();
string getBrother();
string getClass();

int main(int args, char* argsv[]){	
	// Checks and reads file
	ifstream in(argsv[1]);

	if(!in){
		in.open(("registry.csv"));
		if(!in){
			cout << "Usage: psi_lineage.x csv_file" << endl;
			return 0;
		}
	}
	
	// Creates archive for Psi brothers
	archive Psi;
	Psi.readFile(in);

	cout << endl << "\tPsi Records" << endl;

	string brother;
	int pos = 99;
	int aPos = 128;

	char select;
	do{
		menu();
		cin >> select;

		switch(tolower(select)){
			case 's':
				brother = getBrother();
				Psi.printBanner();

				Psi.printInfo(Psi.searchBrother(brother));
				break;
			case 't':
				Psi.printFamily(
					Psi.searchBrother(getBrother()));
				break;
			case 'r':
				Psi.printATree(
					Psi.searchBrother(getBrother()), aPos);
				break;
			case 'l': 	
				Psi.printList();
				break;
			case 'o':
				Psi.printLine(
					Psi.searchBrother(getBrother()));
				break;
			case 'c':
				Psi.printClass(getClass());
				break;	
			case 'q':
				break;
			default:	
				cout << "Not a valid entry" << endl;
				break;
		}
		cout << endl;
	} while(tolower(select) != 'q');

	cout << endl << "Goodbye." << endl;
	return 0;
}

string getBrother(){
	cin.ignore();
	string brother;
	
	cout << "Enter a brother: ";
	getline(cin, brother);
	cout << endl;
	return brother;
}

string getClass(){
	cin.ignore();
	string c;

	cout << "Enter class: ";
	getline(cin, c);
	cout << endl;
	return c;
}

void menu(){
	cout << "---------------------" << endl
	     << "S\tSearch brother" << endl
	     << "C\tPrint class/family" << endl
	     << "T\tPrint tree" << endl
	     << "R\tPrint normalized tree" << endl
	     << "O\tPrint line of brother" << endl
	     << "L\tList Brothers" << endl
	     << "Q\tQuit" << endl << endl
	     << "> ";
}
