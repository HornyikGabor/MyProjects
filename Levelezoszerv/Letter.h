#pragma once
#include <string>
#include "Form.h"
#include "Company.h"
#include <iostream>

class Letter : public virtual Form {
protected:
	std::string type;
	std::string distance;
	std::string variety;
	bool ifPriority;
	std::string addressing;
	bool isCapitalLetter;
public:
	Letter();
	Letter(const Letter&);
	virtual ~Letter();

	virtual void setForm() override;
	virtual void setLetterSpec();

	void setType();
	void setDistance();
	void setVariety();
	void setIfPriority();
	void writeAdd() override;

	void setIfPriorityB(bool);
	void setSizeXYB(double, double);
	void setDistanceB(std::string);
	void setTypeB(std::string);
	void setAddB(std::string);
	void setVarietyB(std::string);

	std::string getAdd() const override;
	std::string getType() const;
	std::string getDisntance() const;
	std::string getVariety() const;
	bool getIfPriority() const;

	void edit(Company&) const override;
	void readIn(int) override;
	virtual bool saveOut() const override;

	friend std::ostream& operator<<(std::ostream& os, const Letter& level);
	friend std::istream& operator>>(std::istream& is, Letter& level);

	bool operator==(const Form&) const;

};