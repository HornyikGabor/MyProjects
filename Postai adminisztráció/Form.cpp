#include "Form.h"
#include <iostream>
#include <stdio.h>
#include <cstring>
#include <fstream>
#include <iomanip>

using namespace std;

Form::Form() {
	sizeX = 0;
	sizeY = 0;
	principal = "";
	bodyText = nullptr;
	isCapitalForm = false;
}
Form::Form(const Form& other) {
	sizeX = other.sizeX;
	sizeY = other.sizeY;
	principal = other.principal;
	isCapitalForm = other.isCapitalForm;
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
Form::~Form() {
	sizeX = 0;
	sizeY = 0;
	string().swap(principal); //principal.clear();
	if (bodyText != nullptr) {
		delete[] bodyText;
		bodyText = nullptr;
	}
	isCapitalForm = false;
}

void Form::setSender(const Company& p) {
	sender = p.getName() + p.getMailingAddress();
}
void Form::setIfLetter(string word) {
	if (word == "level")
		ifLetter = true;
	else
		ifLetter = false;
}
void Form::setSizeXY() {
	system("CLS");
	cout << "Adja meg a nyomtatvany mereteit ('mm' pontossaggal): " << endl;
	cin >> sizeX;
	cin >> sizeY;
	cout << endl;
}
void Form::writePrin() {
	system("CLS");
	string temp;
	if (ifLetter) {
		cout << "Adja meg a felado nevet es cimet." << endl;
		cout << "A ceg adataival akarja elkuldeni a levelet ?" << endl;
	}
	else {
		cout << "Adja meg a megbizo nevet, cimet es szamlaszamat." << endl;
		cout << "A ceg adataival akarja elkuldeni a csekket?" << endl;
	}
	string word; 
	cin >> word;
	if (word == "igen") {
		principal = sender;
	}
	else {
		cout << "Nev, iranyitoszam, varos, utca es hazszam sorrendben." << endl;
		cout << "Ha vegzett nyomjon tabulatort, majd entert." << endl;
		char ch;
		char* pTemp = new char[201]; //DINAMIKUSAN FOGLALT MEMORIA
		int i = 0;
		cin.get(ch);
		while (ch != '\t') {
			pTemp[i] = ch;
			cin.get(ch);
			i++;
		}
		pTemp[i] = '\0';
		principal = (string)pTemp;
	}
	cout << "A felado adatai csupa nagybetuvel jelenjenek meg?" << endl;
	string beUpper;
	cin >> beUpper;
	if (beUpper == "igen")
		isCapitalForm = true;
}
void Form::writeText() {
	system("CLS");
	if (ifLetter) 
		cout << "Ide irhatja a level torzset: " << endl;
	else 
		cout << "Ide irhat a csekkre vonatkozo megjegyzest: " << endl;
	cout << "(Ha vegzett a szoveg megirasaval nyomjon tabulatort, majd entert.)" << endl;
	char ch;
	char* pTemp = new char[201]; 
	int i = 0;
	while ((ch = cin.get()) != '\t') {
		pTemp[i] = ch;
		i++;
	}
	pTemp[i] = '\0';
	int n = 0;
	for (int j = 0; pTemp[j] != '\0'; j++) n++;
	bodyText = new char[n + 1];
	bodyText = pTemp;
}

void Form::setPrinB(string tmp) {
	principal = tmp;
}
void Form::setBodyTB(char* tmp) {
	bodyText = new char[strlen(tmp) + 1];
	strcpy_s(bodyText, strlen(tmp) + 1, tmp);
}

double Form::getSizeX() const {
	return sizeX;
}
double Form::getSizeY() const {
	return sizeY;
}
string Form::getPrin() const {
	return principal;
}
char* Form::getBodyT() const {
	return bodyText;
}

bool Form::compare(const Form& other) const {
	if (principal == other.getPrin())
		return true;
	else
		return false;
}
