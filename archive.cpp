#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "archive.h"

// Construct reads in file
archive::archive(std::ifstream& in){
	// Temp storage variables for reading
	std::string name, year, bg, tmp;
	std::getline(in, tmp);		// Discards header row

	// Reads through file of brothers
	while(!in.eof()){
		std::getline(in, year, ',');	// Grabs: semester initiated
		if(year.size() == 0)
			break;

		std::getline(in, name, ','); // name
		std::getline(in, bg, ',');	// big brother
		std::getline(in, tmp);	// littles
		name = format(name);
		bg = format(bg);
		
		// Splits and stores littles
		std::vector<std::string> littles = getLils(tmp);
		for(auto ll : littles)
			ll = format(ll);
		
		int current;
		brother* newB = new brother(year, name);

		// Adds a preliminary newB to brothers
		if(isBro(name)){
			brothers[big] = newB;
			current = big;
		}
		else{
			brothers.push_back(newB);
			current = brothers.size() - 1;
		}

		// Sets big		
		if(isBro(bg)){
			newB->setBig(brothers[big]);
			
			if(!isLittle(newB->getName()))
				brothers[big]->pushLittle(newB);	
		}
		else if(bg.size() > 0)
			newB->setBig(new brother(bg));

		// Adds littles to bro
		for(auto little : littles){
			if(little.size() == 0)
				continue;
			// Checks if little is already a bro
			if(isBro(little))
				brothers[current]->pushLittle(brothers[big]);
			else
				newB->pushLittle(new brother(little));
		}
		
		// Adds a more complete newB to brothers
		if(isBro(name)){
			brothers[big] = newB;
			current = big;
		}
		else{
			brothers.push_back(newB);
			current = brothers.size() - 1;
		}
		if(isLittle(name))
			brothers[big]->replaceLittle(brothers[current]);
	}
	in.close();
}

void archive::printList() const{
	// Header row for bros
	std::cout << std::left << std::setw(6) << "Year" << std::setw(20)
		  << "Name" << std::setw(20) << "Big Bro" << std::right
		  << std::setw(20) << "Little" << std::endl;
	std::cout << std::left << std::setw(6) << "----" << std::setw(20) 
		  << "----" << std::setw(20) << "-------" << std::right 
		  << std::setw(20) << "------" << std::endl;
	
	// Prints out brothers info
	for(int i = 0; i < brothers.size(); ++i){
		brothers[i]->printInfo();
		std::cout << "---------------------------------"
		          << "---------------------------------" << std::endl;
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
		if(brothers[i]->lilSize() == 0)
			continue;;
		for(int j = 0; j < brothers[i]->lilSize(); ++j){
			if(name == brothers[i]->getLittle(j)){
				big = i, lil = j;
				return true;
			}
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
		if((std::isalnum(ch) || std::iswspace(ch)) 
		&& (ch != '\t' || ch != '\n' || ch != '"')){
			tmp += ch;
		}
	}
	return tmp;
}
