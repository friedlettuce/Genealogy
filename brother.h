#ifndef _FAMILY_H
#define _FAMILY_H

#include <string>
#include <vector>

class brother{
	private:
		std::string name, year;
		brother* big;
		std::vector<brother*> littles;

		const int INDENT = 4;

		std::string indent(const int& id) const;
	public:
		// Constructors
		brother();
		brother(const std::string& n);
		brother(const std::string& y, const std::string& n);
	
		// Mutators
		void setBig(brother* b);
		void pushLittle(brother* l);
		bool replaceLittle(brother* l);
	
		// Accessors
		std::string getName() const;
		std::string getYear() const;
		std::string getBig() const;
		bool relatedTo(brother* current, const std::string& n) const;
		bool relaTree(brother* current, const std::string& n) const;
		
		std::string getLittle(const int& i = 0) const;
		bool isLittle(const std::string& n, int& l) const;
		int lilSize() const;

		// Printing
		void printInfo() const;
		void printLine(brother* current);
		void printTree(brother* current, const int& indent);
};
#endif
