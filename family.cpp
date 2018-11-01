#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include "family.h"

/*		Brother			*/

brother::brother():year{NULL},name{NULL},big{nullptr}{}
brother::brother(const std::string& n):name{n},big{nullptr}{}
brother::brother(const std::string& y, const std::string& n)
:year{y},name{n},big{nullptr}{}

void brother::setBig(brother* b){
	if(big != nullptr)
		delete big;
	big = b;
}

void brother::replaceLittle(brother* l){
	for(int i = 0; i < littles.size(); ++i){
		if(l->name == littles[i]->name){
			delete littles[i];
			littles[i] = l;
			break;
		}
	}
}

void brother::pushLittle(brother* l){ littles.push_back(l); }

std::string brother::getYear() const{ return year; }
std::string brother::getName() const{ return name; }
std::string brother::getBig() const{ return big->name; }

bool brother::isLittle(const std::string& n, int& l) const{
	if(littles.size() == 0)
		return false;

	for(int i = 0; i < littles.size(); ++i){
		if(littles[i]->name == n){
			l = i;
			return true;
		}	
	}
	return false;
}

void brother::printLine(brother* current){
	if(current->big != nullptr){
		printLine(current->big);
		std::cout << "\t|" << std::endl;
	}
	std::cout << current->name << std::endl;
}

std::string brother::getLittle(const int& i) const{ 
	if(i < littles.size())
		return littles[i]->getName(); 
}
int brother::lilSize() const{ return littles.size(); }

void brother::printInfo() const{
	std::cout << std::left << std::setw(6) << year 
		  << std::setw(25) << name 
		  << std::setw(25) << (big == nullptr ? "" : big->name);
	
	if(littles.size() == 0)
		std::cout << std::endl;

	for(int i = 0; i < littles.size(); ++i){
		std::cout << std::right;		

		if(i == 0)
			std::cout << std::setw(25);
		else
			std::cout << std::setw(81);

		std::string tmp;

		if(littles[i]->name[0] == '"'){
			tmp = littles[i]->name.substr(1);
		}
		else if(littles[i]->name[littles[i]->name.size()-1] == '"'){
			tmp = littles[i]->name.substr(0,
				littles[i]->name.size()-1);
		}
		else
			tmp = littles[i]->name;

		std::cout << tmp << std::endl;
	} 
}

/*		FAMILY			*/

family::family(brother* rt){ root = rt; }
