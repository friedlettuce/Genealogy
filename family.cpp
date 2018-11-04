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
	if(big != nullptr && b != nullptr){
		if(big == b)	
			return;
	}
	if(big != nullptr)
		delete big;
	
	big = b;
}

bool brother::replaceLittle(brother* l){
	for(int i = 0; i < littles.size(); ++i){
		if(!littles[i]->name.size())
			continue;
		if(l->name == littles[i]->name){
			if(*l == *littles[i])
				return true;
			delete littles[i];
		
			l->setBig(this);
			littles[i] = l;
			return true;
		}
	}
	return false;
}

void brother::pushLittle(brother* l){
	if(replaceLittle(l))
		return;
 
	if(l->big == nullptr || *l->big != *this){
		l->big = this;
	}
	littles.push_back(l); 
}

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
	
		std::cout << "  ^" << std::endl
			  << "  |" << std::endl;
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

		std::cout << littles[i]->name << std::endl;
	} 
}

bool operator==(const brother& cmp1,
const brother& cmp2){
	if(cmp1.year != cmp2.year)
		return false;
	if(cmp1.name != cmp2.name)
		return false;
	
	// Compares bigs
	if(cmp1.big != nullptr){
		if(cmp2.big != nullptr){
			if(*cmp1.big != *cmp2.big)
				return false;
		} else
			return false;
	} else if(cmp2.big != nullptr)
		return false;

	if(cmp1.littles.size() != cmp2.littles.size())
		return false;
	for(int i = 0; i < cmp1.littles.size(); ++i){
		if(*cmp1.littles[i] != *cmp2.littles[i])
			return false;
	}
	return true;
}

bool operator!=(const brother& cmp1,
const brother& cmp2){ return !(cmp1 == cmp2); } 

/*		FAMILY			*/

family::family(brother* rt){ root = rt; }
