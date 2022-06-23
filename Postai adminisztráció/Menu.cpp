#include "Menu.h"
#include <iomanip>
#include <stdlib.h>

const unsigned MAX_ELEMENTS = 10;

enum class Type {
	CheckWrite, LetterWrite, LetterRead, BillWrite, Exit, Default
};

enum class Type2 {
	Letter, Check, Bills, Default
};

using namespace std;

Menu::Menu() 
	: thisCompany(Company()), level(Letter()), csekk(Check()), szamla(Bills()), readIn(){
	readIn.reserve(MAX_ELEMENTS);
}
int Menu::run() {
	string temp;
	Type menupont = Type::Default;
	thisCompany.writeCompany();
	Form::setSender(getThisCompany());
	while (1) {
		printMenu(temp);
		if (temp == "level irasa") {
			menupont = Type::LetterWrite;
			Form::setIfLetter("level");
		}
		else if (temp == "csekk irasa") {
			menupont = Type::CheckWrite;
			Form::setIfLetter("csekk");
		}
		else if (temp == "levelek lekerdezese") {
			menupont = Type::LetterRead;
			Form::setIfLetter("level");
		}
		else if (temp == "szamla irasa") {
			menupont = Type::BillWrite;
			Form::setIfLetter("level");
		}
		else if (temp == "a ceg adatainak lekerdezese") {
			system("CLS");
			cout << thisCompany;
			system("PAUSE");
		}
		else if (temp == "exit")
			menupont = Type::Exit;
		else
			cout << "Nincs a megadottnak megfelelo menupont." << endl;
		switch (menupont) {
		case Type::LetterWrite: runLoopLevelWrite(); break;
		case Type::CheckWrite: runLoopCsekkWrite(); break;
		case Type::LetterRead: runLoopRead(); break;
		case Type::BillWrite: runLoopSzamlaWrite(); break;
		case Type::Exit: return 0;
		case Type::Default: break;
		}
		string().swap(temp);
	}
}
void Menu::printMenu(string& temp) {
	system("CLS");
	cout << "Valaszon az alabbi menupontok kozul!" << endl;
	cout << "<level irasa>" << endl << "<csekk irasa>" << endl << "<szamla irasa>" << endl << "<levelek lekerdezese>" << endl;
	cout << "<a ceg adatainak lekerdezese>" << endl << "<exit>" << endl;
	char* pTemp = new char[31]; int i = 0; char tempp;
	while (1) {
		if (i == 0) {
			tempp = cin.get();
			if (tempp == '\n') 
				i = 0;
			else {
				pTemp[i] = tempp;
				i++;
			}
		}
		else {
			tempp = cin.get();
			if (tempp == '\n')
				break;
			pTemp[i] = tempp;
			i++;
		}
	} 
 	pTemp[i] = '\0';
	temp = string(pTemp);
	delete[] pTemp;
}
void Menu::runLoopLevelWrite() {
	level.setLetterSpec();
	level.setForm();
	string ifWanSee;
	system("CLS");
	cout << "Meg akarja tekinteni a kesz levelet?" << endl;
	cin >> ifWanSee;
	if (ifWanSee == "igen") 
		level.edit(thisCompany);
	system("PAUSE");
	system("CLS");
	cout << "Ki akarja menteni az elekszitett levelet?" << endl;
	cin >> ifWanSee;
	if (ifWanSee == "igen") {
		bool ifSuccess = level.saveOut();
		if (ifSuccess) {
			cout << "Sikeres volt a kimentes." << endl;
			system("PAUSE");
		}
		else {
			cout << "Sikertelen volt a kimentes." << endl;
			system("PAUSE");
		}
	}
}
void Menu::runLoopCsekkWrite() {
	csekk.setCheckSpec();
	csekk.setForm();
	string word;
	system("CLS");
	cout << "Meg akarja tekinteni a kesz csekket?" << endl;
	cin >> word;
	if (word == "igen")
		csekk.edit(thisCompany);
	system("PAUSE");
	system("CLS");
	cout << "Ki akarja menteni az elekszitett csekket?" << endl;
	cin >> word;
	if (word == "igen") {
		bool ifSuccess = csekk.saveOut();
		if (ifSuccess) {
			cout << "Sikeres volt a kimentes." << endl;
			system("PAUSE");
		}
		else {
			cout << "Sikertelen volt a kimentes." << endl;
			system("PAUSE");
		}
	}
}
void Menu::runLoopSzamlaWrite(){
	szamla.setLetterSpec();
	szamla.setCheckSpec();
	szamla.Letter::setForm();
	system("CLS");
	string ifWanSee;
	cout << "Meg akarja tekinteni a kesz levelet?" << endl;
	cin >> ifWanSee;
	if (ifWanSee == "igen")
		szamla.edit(thisCompany);
	system("PAUSE");
	system("CLS");
	cout << "Ki akarja menteni az elkeszitett szamlat?" << endl;
	cin >> ifWanSee;
	if (ifWanSee == "igen") {
		bool ifSuccess = szamla.saveOut();
		if (ifSuccess) {
			cout << "Sikeres volt a kimentes." << endl;
			system("PAUSE");
		}
		else {
			cout << "Sikertelen volt a kimentes." << endl;
			system("PAUSE");
		}
	}
}
void Menu::runLoopRead() {
	system("CLS");
	arrayLoad();
	int j;
	vector<Form*>::iterator i;
	for (i = readIn.begin(), j = 0; i != readIn.end(); i++, j++) {
		system("CLS");
		cout << "Mit akar csinalni?" << endl;
		cout << "Lehetosegek:" << endl << "-dokumentum kiiratasa" << endl;
		cout << "-dokumentumok osszehasonlitasa." << endl << "-exit" << endl;
		string temp;
		getline(cin, temp);
		if (temp == "dokumentum kiiratasa") {
			readIn[j]->edit(thisCompany);
			system("PAUSE");
		}
		else if (temp == "dokumentumok osszehasonlitasa") {
			int similarCount = 0;
			for (int k = 0; k < readIn.size(); k++)
				if (readIn[k] == readIn[j])
					similarCount++;
			cout << "A lekerdezett dokumentumok kozul " << similarCount << " hasonlo az eppen vizsgalt dokumentummal." << endl;
			system("PAUSE");
			continue;
		}
		else if (temp == "exit")
			break;
	}
}
Company Menu::getThisCompany() {
	Company cTemp(this->thisCompany);
	return cTemp;
}

void Menu::arrayLoad() {
	int lettercount = 0, checkcount = 0, billscount = 0;
	for (int j = 0; j < MAX_ELEMENTS; j++) {
		system("CLS");
		Type2 type = Type2::Default;
		cout << "Mit akar lekerdezni?" << endl;
		string temp1;
		cin >> temp1;
		if (temp1 == "levelet") {
			lettercount++;
			readIn.push_back(new Letter);
			try {
				readIn[j]->readIn(lettercount);
			}
			catch (string hiba) {
				cerr << hiba << endl;
			}
		}
		else if (temp1 == "csekket") {
			checkcount++;
			readIn.push_back(new Check);
			try {
				readIn[j]->readIn(checkcount);
			}
			catch (string hiba) {
				cerr << hiba << endl;
			}
		}
		else if (temp1 == "szamlat") {
			billscount++;
			readIn.push_back(new Bills);
			try {
				readIn[j]->readIn(billscount);
			}
			catch (string hiba) {
				cerr << hiba << endl;
			}
		}
		system("CLS");
		cout << "Akar meg mast is a kesobbiekeben lekerdezni?" << endl;
		string temp2;
		cin >> temp2;
		if (temp2 == "nem") 
			break;
	}
}