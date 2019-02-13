#include <iostream>
#include <iomanip>
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
			//if(*l == *littles[i])
			//	return true;
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
std::string brother::getYear() const{ return year; }
std::string brother::getName() const{ return name; }
std::string brother::getBig() const{ return big->name; }

bool brother::relatedTo(const brother* current, const std::string& n) const{
	const brother* tmp = current;

	while(current != nullptr){
		if(current->name == n)
			return true;
		else
			current = current->big;
	}
	
	current = tmp;
	return relaTree(current, n);
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

// Prints lineage of first brother passed in
void brother::printLine(brother* current){
	if(current->big != nullptr){
		printLine(current->big);
	
		std::cout << "\t    ^" << std::endl
			  << "\t    |" << std::endl;
	}
	
	std::cout << current->year << " - " << current->name; 
	famLabel(current);	
	std::cout << std::endl;
}

// Prints family of brother recursively
void brother::printTree(brother* current, const int& id){
	bool fLil = false;

	// Prints indented name
	std::cout << indent(id-3) << current->name;
	famLabel(current);
	std::cout << " (" << current->year << ')' << std::endl;

	for(auto lil : current->littles){
		if(!fLil){
			std::cout << indent(id) << "   ^\n"
				  << indent(id) << "   |\n"
				  << indent(id) << "   --\n"
				  << indent(id) << "    |"
				  << std::endl;
			fLil = true;

			printTree(lil, id+INDENT);
		} else{
			std::cout << std::endl << indent(id-3);
			std::cout << current->name << " ("
				  << current->year << ')' << std::endl;
			std::cout << indent(id);
			std::cout << "     ^" << std::endl;
			std::cout << indent(id)
				  << "     |" << std::endl;
			printTree(lil, id+INDENT);
		}
	}
}

// Accesses a littles name
std::string brother::getLittle(const int& i) const{ 
	if(i < littles.size())
		return littles[i]->getName(); 
}

// Returns size of littles
int brother::lilSize() const{ return littles.size(); }

// Prints general info of brother
void brother::printInfo() const{
	std::cout << std::left << std::setw(6) << year;
	const brother* current = this;

	if(COLOR){
		if(relatedTo(current, "Jennifer Harris"))
			std::cout << "\033[1;32m";
		if(relatedTo(current, "Jeff Chamlis"))
			std::cout << "\033[1;35m";
		if(relatedTo(current, "Troy Paolantonio")){
			if(relatedTo(current, "Briana Meder"))
				std::cout << "\033[1;30m";
			else
				std::cout << "\033[1;37m";
		}
		if(relatedTo(current, "Tony Geronimos"))
			std::cout << "\033[1;33m";
		if(relatedTo(current, "Josh Willoughby"))
			std::cout << "\033[1;34m";
		if(relatedTo(current, "Michael Weintraub"))
			std::cout << "\033[1;31m";
	}

	std::cout << std::setw(25) << name;
	if(COLOR)
		std::cout << "\033[0m";
	std::cout << std::setw(25) << (big == nullptr ? "" : big->name);
	
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

// Helps formatting printing
std::string brother::indent(const int& id) const{
	std::string tmp;

	for(int i = 0; i < id; ++i)
		tmp += ' ';
	return tmp;
}

// Prints the family label next to name
void brother::famLabel(const brother* current) const{
	if(relatedTo(current, "Jennifer Harris"))
		std::cout << "\033[1;32m - Possum\033[0m";
	if(relatedTo(current, "Jeff Chamlis"))
		std::cout << "\033[1;35m - Mohecian\033[0m";
	if(relatedTo(current, "Troy Paolantonio")){
		if(relatedTo(current, "Briana Meder"))
			std::cout << "\033[1;30m - Zeb\033[0m";
		else
			std::cout << "\033[1;37m - Zeb\033[0m";
	}
	if(relatedTo(current, "Tony Geronimos"))
		std::cout << "\033[1;33m - Rabbit\033[0m";
	if(relatedTo(current, "Josh Willoughby"))
		std::cout << "\033[1;34m - Whale\033[0m";
	if(relatedTo(current, "Michael Weintraub"))
		std::cout << "\033[1;31m - Panda\033[0m";
}
