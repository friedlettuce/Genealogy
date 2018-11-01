#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "archive.h"

archive::~archive(){
	for(auto b : brothers){
		if(b != nullptr)
			delete b;
	}
}

void archive::readFile(std::ifstream& in){
	// Temp storage variables for reading
	std::string name, year, bg, tmp;
	std::getline(in, tmp);		// Discards header row
	
	while(!in.eof()){
		std::getline(in, year, ',');	// Grabs: semester initiated
		std::getline(in, name, ','); // name
		std::getline(in, bg, ',');	// big brother
		std::getline(in, tmp);	// littles

		addBrother(year, name, bg, tmp);
	}
	in.close();
}

void archive::getLine(std::string& n){
	if(!isBro(n)){
		std::cout << "Is not a valid brother" << std::endl;
		return;
	}

	brothers[big]->printLine(brothers[big]);
}
	
void archive::printList() const{
	// Header row for bros
	std::cout << std::left << std::setw(6) << "Year" << std::setw(25)
		  << "Name" << std::setw(25) << "Big Bro" << std::right
		  << std::setw(25) << "Little" << std::endl;
	std::cout << std::left << std::setw(6) << "-----" << std::setw(25) 
		  << "----" << std::setw(25) << "-------" << std::right 
		  << std::setw(25) << "------" << std::endl;
	
	// Prints out brothers info
	for(int i = 0; i < brothers.size(); ++i){
		brothers[i]->printInfo();
		std::cout << "----------------------------------------"
		          << "-----------------------------------------" 
			  << std::endl;
	}
}

/* PRIVATE HELPER FUNCTIONS */

// Checks if brother exists in brothers
bool archive::isBro(const std::string& name){
	if(name.size() == 0)
		return false;

	for(int i = 0; i < brothers.size(); ++i){
		if(name == brothers[i]->getName()){
			big = i;
			return true;
		}
	}
	return false;
}

// Checks if brother exists as a little
bool archive::isLittle(const std::string& name){
	for(int i = 0; i < brothers.size(); ++i){
		if(brothers[i]->isLittle(name, lil)){
			big = i;
			return true;
		}
	}
	return false;
}

std::vector<std::string> archive::getLils(std::string& LL){
	std::istringstream ss(LL);
	std::vector<std::string> littles;
	std::string little;

	while(std::getline(ss, little, ','))
		littles.push_back(little);
	return littles;
}

std::string archive::format(std::string& x){
	std::string tmp;

	for(auto ch : x){
		if((std::isalnum(ch) || std::iswspace(ch) || ch == '-') 
		&& (ch != '\t' || ch != '\n' || ch != '"')){
			tmp += ch;
		}
	}
	return tmp;
}

void archive::addBrother(std::string& year, std::string& name, 
std::string& bg, std::string& tmp){
	year = format(year);
	name = format(name);
	bg = format(bg);
	
	if(year.size() == 0)
		return;

	// Splits and stores littles
	std::vector<std::string> littles = getLils(tmp);
	for(auto ll : littles)
		ll = format(ll);
		
	brother* newB = new brother(year, name);

	// Sets big		
	if(isBro(bg))
	{	// Sets big, sets bigs little to this
		newB->setBig(brothers[big]);
			
		if(brothers[big]->isLittle(newB->getName(), lil))
			brothers[big]->replaceLittle(newB);
		else
			brothers[big]->pushLittle(newB);	
	}
	else if(bg.size() > 0)	// Catches if big is not bro
		newB->setBig(new brother(bg));

	// Adds littles to bro
	for(auto little : littles){
		if(little.size() == 0)
			continue;
		
		// Checks if little is already a bro
		if(isBro(little)){
			newB->pushLittle(brothers[big]);
			brothers[big]->setBig(newB);
		}
		else
			newB->pushLittle(new brother(little));
	}
	brothers.push_back(newB);
}
