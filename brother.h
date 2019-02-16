#ifndef _FAMILY_H
#define _FAMILY_H

#include <string>
#include <vector>

class brother{
	private:
		std::string name, year;
		brother* big;
		std::vector<brother*> littles;
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
		std::string getFName() const;
		std::string getLName() const;

		std::string getYear() const;
		std::string getBig() const;
		void famLabel() const;
		
		brother* Big() const;
		std::vector<brother*> Littles() const;

		bool relatedTo(const std::string& n) const;
		bool relaTree(const brother* current, const std::string& n) const;
		
		bool isLittle(const std::string& n, int& l) const;
};
#endif
