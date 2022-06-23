#include "Check.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <stdlib.h>
#include <random>
#include <ctime>
#include <algorithm>

using namespace std;

Check::Check() : Form() {
	type = "";
	purpose = "";
	variety = "";
	amount = 0;
	accountNum = "";
	paymentID = 0;
	addressing = "";
	isCapitalCheck = false;
}
Check::Check(const Check& other) : Form(other) {
	type = other.type;
	purpose = other.purpose;
	variety = other.variety;
	amount = other.amount;
	accountNum = other.accountNum;
	paymentID = other.paymentID;
	addressing = other.addressing;
	isCapitalCheck = other.isCapitalCheck;
}
Check::~Check() {
	type.clear();
	purpose.clear();
	variety.clear();
	amount = 0;
	accountNum.clear();
	paymentID = 0;
	addressing.clear();
	isCapitalCheck = false;
}

void Check::setForm() {
	setSizeXY();
	writePrin();
	writeAdd();
	writeText();
}
void Check::setSizeXY() {
	if (type == "vagott") {
		sizeX = 210;
		sizeY = 106;
	}
	if (type == "ivesitett") {
		sizeX = 210;
		sizeY = 318;
	}
	if (type == "szamlalevel") {
		sizeX = 210;
		sizeY = 297;
	}
}
void Check::setCheckSpec() {
	setType();
	setPurpose();
	setVariety();
	setAmount();
	setAccNum();
	setPaymID();
}
void Check::setType() {
	system("CLS");
	cout << "<vagott> vagy <ivesitett> vagy <szamlalevel>" << endl;
	cin >> type;
}
void Check::setVariety() {
	system("CLS");
	cout << "<bemutatora> vagy <megnevezettre> vagy <keresztezett>" << endl;
	cin >> variety;
}
void Check::setPurpose() {
	system("CLS");
	cout << "<bankcsekk> vagy <utazasi> vagy <elszamolo>" << endl;
	cin >> purpose;
}
void Check::setAmount() {
	system("CLS");
	cout << "Adja meg az osszeget: " << endl;
	cin >> amount;
}
void Check::setAccNum() {
	system("CLS");
	cout << "Adja meg a kedvezmenyezet szamlaszamat: " << endl;
	cin >> accountNum;
}
void Check::setPaymID() {
	srand((unsigned)time(0));
	paymentID = rand();
}
void Check::writeAdd() {
	system("CLS");
	cout << "Adja meg a csekk cimzettjet(nev, cim, szamlaszam)." << endl;
	cout << "Ha vegzett nyomjon tabulatort, majd entert." << endl;
	char ch;
	char* pTemp = new char[201]; //DINAMIKUSAN FOGLALT MEMORIA
	int i = 0;
	while ((ch = cin.get()) != '\t') {
		pTemp[i] = ch;
		i++;
	}
	pTemp[i] = '\0';
	addressing = (string)pTemp;
	cout << "A cimzett csupa nagybetuvel jelenjen meg?" << endl;
	string beUpper;
	cin >> beUpper;
	if (beUpper == "igen")
		isCapitalCheck = true;
}

void Check::setTypeB(string tmp) {
	type = tmp;
}
void Check::setAmountB(double tmp) {
	amount = tmp;
}
void Check::setVarietyB(string tmp) {
	variety = tmp;
}
void Check::setAddB(string tmp) {
	addressing = tmp;
}
void Check::setAccNumB(string tmp) {
	accountNum = tmp;
}
void Check::setPurposeB(string tmp) {
	purpose = tmp;
}

string Check::getType() const {
	return type;
}
string Check::getPurpose() const {
	return purpose;
}
string Check::getVariety() const{
	return variety;
}
string Check::getAdd() const {
	return addressing;
}

void Check::edit(Company& thisCompany) const {
	system("CLS");
	cout << "Szerepeljenek a csekkben a ceg adatai?" << endl;
	string ifDo;
	cin >> ifDo;
	for (int i = 0; i < 120; i++) cout << "_";
	cout << endl;
	cout << right;
	if (ifDo == "igen") 
		cout << right << setw(40) << thisCompany;
	cout << *this;
}
void Check::readIn(int checkcount) {
	fstream fileInput;
	fileInput.open("beolvasas.txt");
	if (fileInput.fail())
		throw "There was an error while trying to read the letter.";
	while (1) {
		string temp;
		getline(fileInput, temp);
		string comp = "Check " + to_string(checkcount);
		if (temp == comp) {
			fileInput >> *this;
			break;
		}
	}
	fileInput.close();
}
bool Check::saveOut() const {
	ofstream fileOut;
	fileOut.open("kimentesCsekk.txt");
	if (fileOut.fail()) {
		cerr << "Can not open file!" << endl;
		return false;
	}
	else {
		fileOut << *this;
	}
	return true;
	fileOut.close();
}

bool Check::operator==(const Form& other) const {
	if ((*this).compare(other))
		if (addressing == other.getAdd())
			return true;
	return false;
}

ostream& operator<<(ostream& os, const Check& csekk) {
	if (csekk.type == "vagott") 
		os << "A csekk tipusa vagott, ezert meretei: " << csekk.sizeX << "x" << csekk.sizeY << endl;
	else if (csekk.type == "ivesitett") 
		os << "A csekk tipusa ivesitett, ezert meretei: " << csekk.sizeX << "x" << csekk.sizeY << endl;
	else if (csekk.type == "szamlalevel") 
		os << "A csekk szamlalevel vagott, ezert meretei: " << csekk.sizeX << "x" << csekk.sizeY << endl;
	os << "Osszeg: " << csekk.amount << "Ft" << endl;
	os << "A csekk fajata: " << csekk.variety << endl;
	os << "Befizetesi azonosito: " << csekk.paymentID << endl;
	os << "Befizeto neve, cime es szamlaszama: ";
	if (csekk.isCapitalCheck) {
		for (auto& c : csekk.getAdd()) {
			c = toupper(c);
			os << c;
		}
		cout << endl;
	}
	else
		os << csekk.getAdd() << endl;
	os << "Kedvezmenyezet szamlaszama: " << csekk.accountNum << endl;
	os << "Kedvezmenyezett adatai: ";
	if (csekk.isCapitalForm) {
		for (auto& c : csekk.getPrin()) {
			c = toupper(c);
			os << c;
		}
		cout << endl;
	}
	else
		os << csekk.getPrin() << endl;
	os << "Megjegyzes: " << csekk.bodyText << endl;
	return os;
}
istream& operator>>(istream& is, Check& csekk) {
	string tmp; double tmp2;
	getline(is, tmp);  
	csekk.setTypeB(tmp);
	csekk.setSizeXY();
	is >> tmp2; 
	csekk.setAmountB(tmp2);
	is.get();
	getline(is, tmp);  
	csekk.setVarietyB(tmp);
	getline(is, tmp); 
	csekk.setPurposeB(tmp);
	getline(is, tmp);
	csekk.setPrinB(tmp); 
	csekk.setPaymID(); 
	getline(is, tmp);
	csekk.setAccNumB(tmp);
	getline(is, tmp);
	csekk.setAddB(tmp);
	getline(is, tmp);
	csekk.setBodyTB(const_cast<char*>(tmp.c_str()));
	return is;
}
