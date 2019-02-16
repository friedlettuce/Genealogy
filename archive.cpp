#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "brother.h"
#include "archive.h"

archive::~archive(){
	for(auto b : brothers){
		if(b != nullptr){
			delete b;
		}
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

brother* archive::searchBrother(const std::string& n){
	for(int i = 0; i < brothers.size(); ++i){
		if(brothers[i]->getName().find(n) != std::string::npos)
			return brothers[i];
	}
	return nullptr;
}

void archive::printInfo(brother* b) const{ 
	if(b == nullptr || !isBro(b)){
		std::cout << "Brother not found" << std::endl;
		return;
	}
	std::cout << std::left << std::setw(6) << b->getYear();

	if(COLOR){
		if(b->relatedTo("Jennifer Harris"))
			std::cout << "\033[1;32m";
		if(b->relatedTo("Jeff Chamlis"))
			std::cout << "\033[1;35m";
		if(b->relatedTo("Troy Paolantonio")){
			if(b->relatedTo("Briana Meder"))
				std::cout << "\033[1;30m";
			else
				std::cout << "\033[1;37m";
		}
		if(b->relatedTo("Tony Geronimos"))
			std::cout << "\033[1;33m";
		if(b->relatedTo("Josh Willoughby"))
			std::cout << "\033[1;34m";
		if(b->relatedTo("Michael Weintraub"))
			std::cout << "\033[1;31m";
	}

	std::cout << std::setw(25) << b->getName();
	if(COLOR)
		std::cout << "\033[0m";
	std::cout << std::setw(25) << (b->Big() == nullptr ? "" :
		b->getBig());
	
	if(b->Littles().size() == 0)
		std::cout << std::endl;

	for(int i = 0; i < b->Littles().size(); ++i){
		std::cout << std::right;		

		if(i == 0)
			std::cout << std::setw(25);
		else
			std::cout << std::setw(81);

		std::cout << b->Littles()[i]->getName() << std::endl;
	}
}

void archive::printLine(brother* b) const{
	if(!isBro(b))
		return;
	
	if(b->Big() != nullptr){
		printLine(b->Big());
	
		std::cout << "\t    ^" << std::endl
			  << "\t    |" << std::endl;
	}
	
	std::cout << b->getYear() << " - " << b->getName(); 
	b->famLabel();	
	std::cout << std::endl;
}

void archive::printFamily(brother* b) const{
	if(!isBro(b)){
		std::cout << "Brother not found" << std::endl;
		return;
	} else
		printTree(b, 0);
}

void archive::printTree(brother* current, const int& id) const{
	bool fLil = false;

	// Prints indented name
	std::cout << indent(id-3) << current->getName();
	current->famLabel();
	std::cout << " (" << current->getYear() << ')' << std::endl;

	for(auto lil : current->Littles()){
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
			std::cout << current->getName() << " ("
				  << current->getYear() << ')' << std::endl;
			std::cout << indent(id);
			std::cout << "     ^" << std::endl;
			std::cout << indent(id)
				  << "     |" << std::endl;
			printTree(lil, id+INDENT);
		}
	}
}

void archive::printBanner() const{
	// Header row for bros
	std::cout << std::left << std::setw(6) << "Year" << std::setw(25)
		  << "Name" << std::setw(25) << "Big Bro" << std::right
		  << std::setw(25) << "Little" << std::endl;
	std::cout << std::left << std::setw(6) << "-----" << std::setw(25) 
		  << "----" << std::setw(25) << "-------" << std::right 
		  << std::setw(25) << "------" << std::endl;
}
	
void archive::printList() const{
	if(brothers.size() > 0)
		printBanner();

	// Prints out brothers info
	for(int i = 0; i < brothers.size(); ++i){
		printInfo(brothers[i]);
	}
}

void archive::printClass(const std::string& c){
	bool empty = true;
	
	std::istringstream strs(c);
    	std::string sem, yr, n;
    	strs >> sem;
    	strs >> yr;

    	if(sem == "fa" || sem == "Fa" || sem == "Fall" || sem == "fall")
        	sem = "Fa";
	else if(sem == "sp" || sem == "Sp" || sem == "Spring" || sem == "spring")
        	sem = "Sp";
	if(yr.length() > 2)
		yr = yr.substr(2,4);

	n = sem + ' ' + yr;

	for(int i = n.length() == 5 ? 0 : brothers.size();
		i < brothers.size(); ++i){
		
		if(n == brothers[i]->getYear()){
			if(empty){
				printBanner();
				empty = false;
			}
			printInfo(brothers[i]);
		}
	}

	if(!empty)
		return;
	else
		empty = false;

	if((n.find("Rab") != std::string::npos) ||
		(n.find("rab") != std::string::npos)){
        	printFamily(searchBrother("Tony Geronimos"));
    	} else if((n.find("Mo") != std::string::npos) ||
		(n.find("mo") != std::string::npos)){
        	printFamily(searchBrother("Jeff Chamlis"));
    	} else if((n.find("Zeb") != std::string::npos) ||
		(n.find("zeb") != std::string::npos)){
        	printFamily(searchBrother("Troy Paolantonio"));
    	} else if((n.find("Panda") != std::string::npos) ||
        	(n.find("panda") != std::string::npos) ||
		(n.find("platinum") != std::string::npos) ||
		(n.find("Platinum") != std::string::npos)){
        	printFamily(searchBrother("Michael Weintraub"));
    	} else if((n.find("Possum") != std::string::npos) ||
		(n.find("possum") != std::string::npos)){
		printFamily(searchBrother("Jennifer Harris"));
	} else if((n.find("Whale") != std::string::npos) ||
		(n.find("whale") != std::string::npos) || 
		(n.find("dolphin") != std::string::npos) ||
		(n.find("Dolphin") != std::string::npos)){
		printFamily(searchBrother("Josh Willoughby"));
	}else
		empty = true;
	
	if(empty)
		std::cout << "No brothers found" << std::endl;
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

bool archive::isBro(const brother* b) const{
	if(b == nullptr)
		return false;

	for(auto bro : brothers){
		if(b->getName() == bro->getName())
			return true;
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
	bool isSpace = false;
	bool isChar = false;

	for(int ch = 0; ch < x.size(); ++ch){
		// Handles names with more than 1 space in between
		if(isChar && ch+1 < x.size()){
			if(isSpace && isspace(x[ch]) && isalnum(x[ch+1]))
				isSpace = false;
		}
		// Checks if end of name
		if(isChar && isSpace && (!isalnum(x[ch]) 
		&& x[ch] != '-' && x[ch] != '.'))
			break;
		// Checks for name inbetween name
		if(isChar && isspace(x[ch])){
			isSpace = true;
			tmp += x[ch];
		}
		else if(isChar || isalnum(x[ch])
		|| x[ch] == '-' || x[ch] == '.'){
			isChar = true;
			tmp += x[ch];
		}
	}
	return tmp;
}

void archive::addBrother(std::string& year, std::string& name, 
std::string& bg, std::string& tmp){
	year = format(year);
	name = format(name);
	bg = format(bg);
	std::vector<std::string> littles = getLils(tmp);
	
	if(year.size() == 0)
		return;

	// New Brother	
	brother* newB = new brother(year, name);

	// Sets big		
	if(isBro(bg))
	{	// Sets big, sets bigs little to this
		if(!brothers[big]->replaceLittle(newB))
			brothers[big]->pushLittle(newB);
	}
	else if(bg.size() > 0)	// Catches if big is not bro
		newB->setBig(new brother(bg));

	// Adds littles to bro
	for(auto little : littles){
		little = format(little);
		if(little.size() == 0)
			continue;

		// Checks if little is already a bro
		if(isBro(little)){
			if(!newB->replaceLittle(brothers[big]))
				newB->pushLittle(brothers[big]);
		}
		else{
			newB->pushLittle(new brother(little));
		}
	}
	brothers.push_back(newB);
}

std::string archive::indent(const int& id) const{
	std::string tmp;

	for(int i = 0; i < id; ++i)
		tmp += ' ';
	return tmp;
}
