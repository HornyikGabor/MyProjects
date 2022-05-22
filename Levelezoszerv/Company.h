#pragma once
#include <string>
#include <iostream>
#include "Form.h"

class Company{
private:
	std::string name;
	std::string mailingAddress;
	std::string taxID;
	std::string companyRegNum;
public:
	Company();
	Company(const Company&);
	~Company();
	void writeCompany();
	void setName(std::string);
	void setAddress(std::string);
	void setID(std::string);
	void setRegNum(std::string);
	std::string getName() const;
	std::string getTaxID() const;
	std::string getCompanyRegNum() const;
	std::string getMailingAddress() const;
	friend std::istream& operator>>(std::istream& is, Company& p);
	friend std::ostream& operator<<(std::ostream& os, Company& p);
};