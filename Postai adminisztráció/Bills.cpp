#include "Bills.h"
#include "stdlib.h"
#include <fstream>
#include <iomanip>
#include <algorithm>

using namespace std;

Bills::Bills() : Letter(), Check(), topic("") {}
Bills::Bills(const Bills& other) : Letter(other), Check(other){
	topic = other.topic;
}
Bills::~Bills() {
	topic.clear();
}
void Bills::setLetterSpec() {
	Letter::setType();
	setDistance();
	setIfPriority();
	setTopic();
}
void Bills::setCheckSpec() {
	setAmount();
	setAccNum();
	setPaymID();
}
void Bills::setForm() { &Letter::setForm; }
void Bills::writeAdd() { Letter::writeAdd(); }
void Bills::setSizeXY() { Letter::setSizeXY(); }
void Bills::setTopic() {
	system("CLS");
	cout << "Mire allitja ki a szamlat? (a szamla targya)" << endl;
	char* pTemp = new char[21]; int i = 0; char tempp;
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
	topic = string(pTemp);
}

void Bills::setTopicB(string tmp) {
	topic = tmp;
}
void Bills::edit(Company& thisCompany) const{
	system("CLS");
	cout << "Szerepeljenek a szamlaba a ceg adatai?" << endl;
	string ifDo;
	cin >> ifDo;
	for (int i = 0; i < 120; i++) cout << "_";
	cout << endl;
	cout << right;
	if (ifDo == "igen")
		cout << right << setw(40) << thisCompany;
	cout << *this;
}
void Bills::readIn(int billscount) {
	fstream fileInput;
	fileInput.open("beolvasas.txt");
	if (fileInput.fail())
		throw "There was an error while trying to read the letter.";
	while (1) {
		string temp;
		getline(fileInput, temp);
		string comp = "Bills " + to_string(billscount);
		if (temp == comp) {
			fileInput >> *this;
			break;
		}
	}
	fileInput.close();
}
bool Bills::saveOut() const {
	ofstream fileOut;
	fileOut.open("kimentesSzamla.txt");
	if (fileOut.fail()) {
		cerr << "Can not open file!" << endl;
		return false;
	}
	else {
		fileOut << *this;
		return true;
	}
	fileOut.close();
}
string Bills::getTopic() const{
	return topic;
}

ostream& operator<<(ostream& os, const Bills& szamla) {
	if (szamla.getIfPriority())
		os << "A LEVEL ELSOBBSEGI!" << endl;
	os << "A szamlalevel meretei: " << szamla.Letter::getSizeX() << "x" << szamla.Letter::getSizeY() << endl;
	os << "A szamlalevel tipusa: " << szamla.Letter::getType() << endl;
	if (szamla.getDisntance() == "nemzetkozi")
		os << "A szamlalevel nemzetkozi!" << endl;
	else
		os << "A szamlalevel belfoldi!" << endl;
	os << "A szamlalevel targya: " << endl << szamla.getTopic() << endl;
	os << "Befizetesi azonosito: " << szamla.paymentID << endl;
	os << "Befizeto neve, cime: ";
	if (szamla.isCapitalLetter) {
		for (auto& c : szamla.getAdd()) {
			c = toupper(c);
			os << c;
		}
		cout << endl;
	}
	else
		os << szamla.getAdd() << endl;
	os << "Befizeto szamlaszama: " << szamla.accountNum << endl;
	os << "Kedvezmenyezett adatai: ";
	if (szamla.isCapitalForm) {
		for (auto& c : szamla.getPrin()) {
			c = toupper(c);
			os << c;
		}
		cout << endl;
	}
	else
		os << szamla.getPrin() << endl;
	os << "A szamlalevel szovegtorzse: " << endl << szamla.Letter::bodyText << endl;
	return os;
}
istream& operator>>(istream& is, Bills& szamla) {
	string tmp; double a, b;
	getline(is, tmp); 
	if (tmp == "A LEVEL ELSOBBSEGI!")
		szamla.setIfPriorityB(true);
	is >> a; is >> b;
	szamla.setSizeXYB(a, b);
	is.get();
	getline(is, tmp); 
	szamla.Letter::setTypeB(tmp);
	getline(is, tmp);  
	szamla.Letter::setVarietyB(tmp);
	getline(is, tmp);  
	szamla.setDistanceB(tmp);
	getline(is, tmp);
	szamla.setTopicB(tmp);
	is >> a; 
	szamla.setAmountB(a);
	is.get();
	getline(is, tmp);
	szamla.Letter::setAddB(tmp);
	getline(is, tmp);
	szamla.setAccNumB(tmp);
	getline(is, tmp); 
	szamla.Letter::setPrinB(tmp);
	szamla.setPaymID(); 
	getline(is, tmp);
	szamla.setBodyTB(const_cast<char*>(tmp.c_str()));
	return is;
}
