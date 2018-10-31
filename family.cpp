#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include "family.h"

// Brother
brother::brother():year{NULL},name{NULL},big{nullptr}{}

brother::brother(const std::string& n):name{n},big{nullptr}{}

brother::brother(const std::string& y, const std::string& n)
:year{y},name{n},big{nullptr}{}

void brother::setBig(brother* b){
	big = b;
	
	for(auto lil : b->littles){
		if(name == lil->name)
			lil = this;
	}
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
std::string brother::getLittle(const int& i) const{ 
	return littles[i]->getName(); 
}
int brother::lilSize() const{ return littles.size(); }

void brother::printInfo() const{
	std::cout << std::left << std::setw(6) << year 
		  << std::setw(20) << name 
		  << std::setw(20) << (big == nullptr ? "" : big->name);
	
	if(littles.size() == 0)
		std::cout << std::endl;

	for(int i = 0; i < littles.size(); ++i){
		std::cout << std::right;		

		if(i == 0)
			std::cout << std::setw(20);
		else
			std::cout << std::setw(66);

		std::cout << littles[i]->name << std::endl;
	} 
}

bool operator>(const brother& b1, const brother& b2){
	int b1Objs = 0, b2Objs = 0;	// Counts how many things objects have

	if(b1.year.size() > b2.year.size())
		++b1Objs;
	else if(b2.year.size() > b1.year.size())
		++b2Objs;
	
	if(b1.name.size() > b2.name.size())
		++b1Objs;
	else if(b2.name.size() > b1.name.size())
		++b2Objs;

	if(b1.big == nullptr){
		if(b2.big != nullptr)
			++b2Objs;
	} else if(b2.big == nullptr){
		if(b1.big != nullptr)
			++b1Objs;
	}
	else if(b1.big->name.size() > b2.big->name.size())
		++b2Objs;
	else if(b2.big->name.size() > b1.big->name.size())
		++b1Objs;

	if(b1.littles.size() > b2.littles.size())
		++b1Objs;
	else if(b2.littles.size() > b1.littles.size())
		++b2Objs;
	
	return b1 > b2;
}
