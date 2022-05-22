#include"Company.h"
#include <fstream>
#include <stdlib.h>

using namespace std;

Company::Company(){
	name = "";
	taxID = "";
	mailingAddress = "";
	companyRegNum = "";
}
Company::Company(const Company& other){
	name = other.getName();
	mailingAddress = other.getMailingAddress();
	taxID = other.getTaxID();
	companyRegNum = other.getCompanyRegNum();
}
Company::~Company() {
	string().swap(name); //name.clear();
	string().swap(mailingAddress); //mailingAddress.clear();
	string().swap(taxID); //taxID.clear();
	string().swap(companyRegNum); //companyRegNum.clear();
}
void Company::writeCompany() {
	system("CLS");
	bool newBool = true;
	string oldornew;
	cout << "A <korabbi> ceg adataival vagy <uj> adatokkal akar dolgozni?" << endl;
	getline(cin, oldornew);
	if (oldornew == "uj")
		newBool = false;
	if (newBool == false) {
		cout << "Adja meg a ceg adatait: " << endl;
		cin >> *this;
	}
	else {
		ifstream file;
		file.open("ceg.txt");
		if (file.fail())
			cerr << "Can not open file!" << endl;
		else {
			string temp; int i = 0;
			while (getline(file, temp)) {
				switch (i) {
				case 0: setName(temp); break;
				case 1: setAddress(temp); break;
				case 2: setID(temp); break;
				case 3: setRegNum(temp); break;
				}
				i++;
			}
		}
		file.close();
	}
}
void Company::setName(string str) {
	name = str;
}
void Company::setAddress(string str) {
	mailingAddress = str;
}
void Company::setID(string str) {
	taxID = str;
}
void Company::setRegNum(std::string str) {
	companyRegNum = str;
}
string Company::getName() const{
	return name;
}
string Company::getTaxID() const{
	return taxID;
}
string Company::getCompanyRegNum() const{
	return companyRegNum;
}
string Company::getMailingAddress() const {
	return mailingAddress;
}

istream& operator>>(istream& is, Company& p) {
	string temp = "";
	getline(is, temp);
	p.setName(temp);
	getline(is, temp);
	p.setAddress(temp);
	getline(is, temp);
	p.setID(temp);
	getline(is, temp);
	p.setRegNum(temp);
	return is;
}

ostream& operator<<(ostream& os, Company& p) {
	os << "A ceg neve: " << p.name << std::endl;
	os << "A ceg levelezesi cime: " << p.mailingAddress << std::endl;
	os << "A ceg adoszama: " << p.taxID << std::endl;
	os << "A ceg regisztracios azonositoja: " << p.companyRegNum << std::endl;
	return os;
}

