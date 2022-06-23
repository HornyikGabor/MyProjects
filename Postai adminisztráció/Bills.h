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
	* A következõ három függvényre azért van szükségem, mert a Bills osztálynak két õsosztály van, amiknek
	* közös az õs osztálya (gyémánt formula). És amikor a Forms* típusú tömböt leszármazottakoból akarom feltölteni,
	* akkor alapesetben csak közvetlen leszármazottakból tölthetem fel
	* de ha a leszármaztatás virtuális, akkor mûködik a feltöltés. De ekkor fellép a kétértelmûség, és ezekkel a függvényekkel tudom megoldani.
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