#pragma once
#include <cstring>
#include "Letter.h"
#include "Check.h"
#include "Form.h"
#include "Bills.h"
#include "Company.h"
#include <vector>
#include <iostream>

class Menu{
private:
	Letter level;
	Check csekk;
	Bills szamla;
	Company thisCompany;
	std::vector<Form*> readIn;
public:
	Menu();
	int run();
	void runLoopLevelWrite();
	void runLoopCsekkWrite();
	void runLoopSzamlaWrite();
	void runLoopRead();
	void printMenu(std::string&);
	Company getThisCompany();
	void arrayLoad();
};
