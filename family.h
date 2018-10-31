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
		brother();
		brother(const std::string& n);
		brother(const std::string& y, const std::string& n);
	
		void setBig(brother* b);
		void replaceLittle(brother* l);
		void pushLittle(brother* l);

		std::string getName() const;
		std::string getYear() const;
		std::string getBig() const;
		std::string getLittle(const int& i = 0) const;
		int lilSize() const;

		void printInfo() const;

		friend bool operator>(const brother& b1, const brother& b2);
};
#endif
