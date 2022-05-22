#pragma once
#include "Letter.h"
#include "Check.h"
#include <string>
#include <iostream>

class Bills : public Letter, public Check{
private:
	std::string topic; 
public:
	Bills();
	Bills(const Bills&);
	~Bills();

	void setLetterSpec() override;
	void setCheckSpec() override;
	/*
	* A k�vetkez� h�rom f�ggv�nyre az�rt van sz�ks�gem, mert a Bills oszt�lynak k�t �soszt�ly van, amiknek
	* k�z�s az �s oszt�lya (gy�m�nt formula). �s amikor a Forms* t�pus� t�mb�t lesz�rmazottakob�l akarom felt�lteni,
	* akkor alapesetben csak k�zvetlen lesz�rmazottakb�l t�lthetem fel
	* de ha a lesz�rmaztat�s virtu�lis, akkor m�k�dik a felt�lt�s. De ekkor fell�p a k�t�rtelm�s�g, �s ezekkel a f�ggv�nyekkel tudom megoldani.
	*/
	void setForm() override;
	void writeAdd() override;
	void setSizeXY() override;
	void setTopic();
	void setTopicB(std::string);

	std::string getTopic() const;
	std::string getAdd() const { return Letter::getAdd(); }
	void edit(Company&) const override;
	void readIn(int) override;
	bool saveOut() const override;



	friend std::ostream& operator<<(std::ostream& os, const Bills& szamla);
	friend std::istream& operator>>(std::istream& is, Bills& szamla);
};