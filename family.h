#ifndef _FAMILY_H
#define _FAMILY_H

#include <string>
#include <vector>

class brother{
	private:
		std::string name, year;
		brother* big;
		std::vector<brother*> littles;

		std::string indent(const int& id) const;
	public:
		brother();
		brother(const std::string& n);
		brother(const std::string& y, const std::string& n);
	
		void setBig(brother* b);
		void pushLittle(brother* l);
		bool replaceLittle(brother* l);
	
		std::string getName() const;
		std::string getYear() const;
		std::string getBig() const;

		
		std::string getLittle(const int& i = 0) const;
		bool isLittle(const std::string& n, int& l) const;
		int lilSize() const;

		void printInfo() const;
		void printLine(brother* current);
		void printTree(brother* current, const int& indent);

		friend bool operator==(const brother& cmp1, 
			const brother& cmp2);
		friend bool operator!=(const brother& cmp1, 
			const brother& cmp2);
};

// Tree implementation of family

class family{
	private:
		brother* root;
	public:
		family(brother* rt);	
};
#endif
