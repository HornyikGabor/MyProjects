#include "Menu.h"
#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <chrono>
#include <ctime>

using namespace std;

bool Form::ifLetter = true;
string Form::sender = "";

void mainPage() {
	system("CLS");
	cout << "|" << right << setw(20) << "Posta adminisztraciot segito program" << endl;
	cout << "|" << right << setw(20) << "A program lehetove tesi a felhasznalo szamara " << endl;
	cout << "|" << right << setw(20) << "levelek es csekkek megirasat, kitolteset" << endl;
	cout << "|" << right << setw(20) << "es mas felhasznalasi lehetosegeket is nyujt " << endl;
	auto start = chrono::system_clock::now();
	auto legacyStart = chrono::system_clock::to_time_t(start);
	char temp[30];
	ctime_s(temp, sizeof(temp), &legacyStart);
	cout << "|" << std::right << setw(90) <<  temp << std::endl;
	system("PAUSE");
}

int main(void) {
	mainPage();

	Menu UI;
	UI.run();

	return 0;
}