#include "Letter.h"
#include <cstring>
#include <string>
#include <fstream>
#include <iomanip>

using namespace std;

Letter::Letter() : Form() {
	type = "";
	distance = "";
	variety = "";
	ifPriority = false;
	addressing = "";
	isCapitalLetter = false;
}
Letter::Letter(const Letter& other) : Form(other) {
	type = other.type;
	distance = other.distance;
	variety = other.variety;
	ifPriority = other.ifPriority;
	addressing = other.addressing;
	isCapitalLetter = other.isCapitalLetter;
	bodyText = nullptr;
	int n = 0;
	for (char* p = other.bodyText; *p != '\0'; p++)
		n++;
	bodyText = new char[n + 1];
	int i;
	for (i = 0; i < n; i++)
		bodyText[i] = other.bodyText[i];
	bodyText[i] = '\0';
}
Letter::~Letter(){
	string().swap(type); //type.clear();
	string().swap(distance); //distance.clear();
	string().swap(variety); //variety.clear();
	string().swap(addressing); //addressing.clear();
	ifPriority = false;
	isCapitalLetter = false;
}

void Letter::setForm(){
	setSizeXY();
	writePrin();
	writeAdd();
	writeText();
}
void Letter::setLetterSpec() {
	setType();
	setDistance();
	setVariety();
	setIfPriority();
}
void Letter::setType() {
	system("CLS");
	cout << "<ajanlott> vagy <teritveny> " << endl;
	cin >> type;
}
void Letter::setDistance() {
	system("CLS");
	cout << "<nemzetkozi> vagy <belfoldi>" << endl;
	cin >> distance;
}
void Letter::setVariety() {
	system("CLS");
	cout << "<szemelyes>" << endl << "<meghivo>" << endl;
	cout << "<megrendelo>" << endl << "<reklamacio>" << endl;
	cout << "<ajanlat>" << endl << "<tajekoztato>" << endl;
	cin >> variety;
}
void Letter::setIfPriority() {
	system("CLS");
	cout << "Elsobbsegi?" << endl;
	string temp;
	cin >> temp;
	if (temp == "igen")
		ifPriority = true;
	else
		ifPriority = false;
}
void Letter::writeAdd() {
	system("CLS");
	cout << "Adja meg a level cimzettjet(Nev, cim)." << endl;
	cout << "Ha vegzett nyomjon tabulatort, majd entert." << endl;
	char ch;
	char* pTemp = new char[201]; 
	int i = 0;
	while ((ch = cin.get()) != '\t') {
		pTemp[i] = ch;
		i++;
	}
	pTemp[i] = '\0';
	addressing = (string)pTemp;
	cout << "A cimzett adatai csupa nagybetuvel jelenjenek meg?" << endl;
	string beUpper;
	cin >> beUpper;
	if (beUpper == "igen")
		isCapitalLetter = true;
}

void Letter::setIfPriorityB(bool tmp) {
	ifPriority = tmp;
}
void Letter::setSizeXYB(double tmp, double tmp2) {
	sizeX = tmp; sizeY = tmp2;
}
void Letter::setDistanceB(string tmp) {
	distance = tmp;
}
void Letter::setTypeB(string tmp) {
	type = tmp;
}
void Letter::setAddB(string tmp){
	addressing = tmp;
}
void Letter::setVarietyB(string tmp) {
	variety = tmp;
}

string Letter::getAdd() const {
	return addressing;
}
string Letter::getType() const {
	return type;
}
string Letter::getDisntance() const {
	return distance;
}
string Letter::getVariety() const {
	return variety;
}
bool Letter::getIfPriority() const {
	return ifPriority;
}

void Letter::edit(Company& thisCompany) const {
	system("CLS");
	cout << "Szerepeljenek a levelben a ceg adatai?" << endl;
	string ifDo;
	cin >> ifDo;
	for (int i = 0; i < 120; i++) cout << "_";
	cout << endl;
	if (ifDo == "igen") 
		cout << thisCompany;
	cout << *this;
}
void Letter::readIn(int lettercount) {
	fstream fileInput;
	fileInput.open("beolvasas.txt");
	if (fileInput.fail())
		throw "There was an error while trying to read the letter.";
	while (1) {
		string temp;
		getline(fileInput, temp);
		string comp = "Letter " + to_string(lettercount);
		if (temp == comp) {
			fileInput >> *this;
			break;
		}
	}
	fileInput.close();
}
bool Letter::saveOut() const{
	ofstream fileOut;
	fileOut.open("kimentesLevel.txt");
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

bool Letter::operator==(const Form& other) const {
	if ((*this).compare(other))
		if (addressing == other.getAdd())
			return true;
	return false;
}

ostream& operator<<(ostream& os, const Letter& level) {
	if (level.getIfPriority()) {
		os << std::right << setw(50) << "A LEVEL ELSOBBSEGI!" << endl;
	}
	os << "A level meretei: " << level.getSizeX() << "x" << level.getSizeY() << endl;
	if (level.getDisntance() == "nemzetkozi")
		os << "A level nemzetkozi!" << endl;
	else
		os << "A level belfoldi!" << endl;
	if (level.getType() == "ajanlott")
		os << "A level ajanlott." << endl;
	else
		os << "A level teritveny." << endl;
	os << "A level cimzettje: " << endl;
	if (level.isCapitalLetter) {
		for (auto& c : level.getAdd()) {
			c = toupper(c);
			os << c;
		} 
		os << endl;
	}
	else
		os << level.getAdd() << endl;
	os << "A level feladoja: " << endl;
	if (level.isCapitalForm) {
		for (auto& c : level.getPrin()) {
			c = toupper(c);
			os << c;
		}
		os << endl;
	}
	else
		os << level.getPrin() << endl;
	for (int i = 0; level.getBodyT()[i] != '\0'; i++)
		os << level.getBodyT()[i];
	os << endl << endl;
	return os;
}
istream& operator>>(istream& is, Letter& level) {
	string tmp;
	double tmp2, tmp3;
	getline(is, tmp);
	if (tmp == "A LEVEL ELSOBBSEGI!") 
		level.setIfPriorityB(true);
	is >> tmp2;
	is >> tmp3; 
	level.setSizeXYB(tmp2, tmp3);
	is >> tmp; 
	level.setVarietyB(tmp);
	is >> tmp; 
	level.setDistanceB(tmp);
	is >> tmp; 
	level.setTypeB(tmp);
	char p; char* pTemp; int i = 0; int n = 0; 
	while (is.get() != '\n') n++;
	pTemp = new char[n + 1];
	while ((p = is.get()) != '\n') {
		pTemp[i] = p;
		i++;
	}
	pTemp[i] = '\0';
	level.setAddB(string(pTemp));
	getline(is, tmp); 
	level.setPrinB(tmp);
	getline(is, tmp);
	level.setBodyTB(const_cast<char*>(tmp.c_str()));
 	return is;
}