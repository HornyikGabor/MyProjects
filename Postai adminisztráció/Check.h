#pragma once
#include "Form.h"
#include <cstring>

class Check : public virtual Form {
protected:
	std::string type;
	std::string purpose;
	std::string variety;
	double amount;
	std::string accountNum;
	int paymentID;
	std::string addressing;
	bool isCapitalCheck;
public:
	Check();
	Check(const Check&);
	virtual ~Check();

	virtual void setForm() override;
	virtual void setCheckSpec();
	void setSizeXY() override;
	void setVariety();
	void setType();
	void setPurpose();
	void setAmount();
	void setAccNum();
	void setPaymID();
	void writeAdd() override;

	void setTypeB(std::string);
	void setAmountB(double);
	void setVarietyB(std::string);
	void setAccNumB(std::string);
	void setAddB(std::string);
	void setPurposeB(std::string);

	std::string getType() const;
	std::string getPurpose() const;
	std::string getVariety() const;
	std::string getAdd() const override;

	void edit(Company&) const override;
	void readIn(int) override;
	virtual bool saveOut() const override;

	bool operator==(const Form&) const;

	friend std::ostream& operator<<(std::ostream& os, const Check& csekk);
	friend std::istream& operator>>(std::istream& is, Check& csekk);

};

