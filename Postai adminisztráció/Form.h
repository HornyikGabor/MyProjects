#pragma once
#include <string>
#include "Company.h"

class Company;

class Form{
protected:
	double sizeX;
	double sizeY;
	std::string principal;
	char* bodyText;
	static std::string sender;
	static bool ifLetter;
	bool isCapitalForm;
public:
	Form();
	Form(const Form&);
	virtual ~Form();

	static void setSender(const Company&);
	static void setIfLetter(std::string);
	virtual void setSizeXY();
	void writePrin(); 
	void writeText();

	void setPrinB(std::string);
	void setBodyTB(char*);

	double getSizeX() const;
	double getSizeY() const;
	std::string getPrin() const;
	char* getBodyT() const;
	virtual std::string getAdd() const = 0;

	virtual void edit(Company&) const = 0;
	virtual void setForm() = 0;
	virtual void writeAdd() = 0;
	virtual void readIn(int) = 0; 
	virtual bool saveOut() const = 0;

	bool compare(const Form&) const;
};
