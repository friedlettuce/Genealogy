#ifndef _ARCHIVE_H
#define _ARCHIVE_H

#include <vector>
#include <string>
#include <fstream>
#include "brother.h"

class archive{
	private:
		std::vector<brother*> brothers;

		// Checks if brother exists in brothers
		bool isBro(const std::string& name);
		bool isBro(const brother* b) const;
		bool isLittle(const std::string& name);
		int big, lil;	// Helper indexing values

		bool COLOR = true;
		const int INDENT = 4;

		std::vector<std::string> getLils(std::string& LL);
		
		// Printing helpers
		std::string format(std::string& x);
		std::string indent(const int& id) const;
		
		// Adds a brother to list
		void addBrother(std::string& year, std::string& name,
			std::string& bg, std::string& tmp);
	public:
		~archive();
		void readFile(std::ifstream& in);

		brother* searchBrother(const std::string& n);

		void printBanner() const;
		void printClass(const std::string& c);	// Also fams
		void printInfo(brother* b) const;
		void printFamily(brother* b) const;
		void printLine(brother* b) const;
		void printList() const;
		void printTree(brother* current, const int& id) const;
};
#endif
