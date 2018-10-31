#ifndef _ARCHIVE_H
#define _ARCHIVE_H

#include <vector>
#include <string>
#include <fstream>
#include "family.h"

class archive{
	private:
		std::vector<brother*> brothers;

		// Checks if brother exists in brothers
		bool isBro(const std::string& name);
		bool isLittle(const std::string& name);
		int big, lil;	// Helper indexing values

		std::vector<std::string> getLils(std::string& LL);
		std::string format(std::string& x);
	public:
		archive(std::ifstream& in);
		
		void printList() const;
};
#endif
