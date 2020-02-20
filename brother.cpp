#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include "brother.h"

/*		Brother			*/

// Constructors
brother::brother():year{NULL},name{NULL},big{nullptr}{}

brother::brother(const std::string& n):name{n},big{nullptr}{}

brother::brother(const std::string& y, const std::string& n)
:year{y},name{n},big{nullptr}{}

// Sets a brothers big
void brother::setBig(brother* b){
	if(big != nullptr && b != nullptr){
		if(big == b)	
			return;
	}
	if(big != nullptr)
		delete big;
	
	big = b;
}

// Finds existing little and replaces
bool brother::replaceLittle(brother* l){
	for(int i = 0; i < littles.size(); ++i){
		if(!littles[i]->name.size())
			continue;
		if(l->name == littles[i]->name){
			delete littles[i];
		
			l->setBig(this);
			littles[i] = l;
			return true;
		}
	}
	return false;
}

// Adds a new brother into littles
void brother::pushLittle(brother* l){
	if(replaceLittle(l))
		return;
 
	if(l->big == nullptr || l->big != this)
		l->big = this;
	littles.push_back(l); 
}

// Accessors
std::string brother::getName() const{ return name; }
std::string brother::getFName() const{
	std::string fname;

	std::istringstream in(name);
	in >> fname;
	return fname;
}
std::string brother::getLName() const{
	std::string lname;

	std::istringstream in(name);
	in >> lname >> lname;
	return lname;
}

std::string brother::getYear() const{ return year; }
std::string brother::getBig() const{ return big->name; }

brother* brother::Big() const{ return big; }
std::vector<brother*> brother::Littles() const{ return littles; }

bool brother::relatedTo(const std::string& n) const{
	const brother* tmp = this;

	while(tmp != nullptr){
		if(tmp->name == n)
			return true;
		else
			tmp = tmp->big;
	}
	
	return relaTree(this, n);
}

bool brother::relaTree(const brother* current, const std::string& n) const{
	if(current->name == n)
		return true;

	for(auto lil : current->littles){
		if(relaTree(lil, n))
			return true;
	}
	return false;
}

// Helper function
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

// Prints the family label next to name
void brother::famLabel() const{
	if(this->relatedTo("Jennifer Harris"))
		std::cout << " - Possum";
	if(this->relatedTo("Jeff Chamlis"))
		std::cout << " - Mohican";
	if(this->relatedTo("Troy Paolantonio")){
		if(this->relatedTo("Briana Meder"))
			std::cout << " - Zeb";
		else
			std::cout << " - Zeb";
	}
	if(this->relatedTo("Tony Geronimos"))
		std::cout << " - Rabbit";
	if(this->relatedTo("Josh Willoughby"))
		std::cout << " - Whale";
	if(this->relatedTo("Michael Weintraub"))
		std::cout << " - Panda";
}
