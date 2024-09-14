#ifndef BUSINESS_H
#define BUSINESS_H

#include "Passenger.h"
class Business : public Passenger {
private:
	string meal;
public:
	Business();
	Business(string meal, string name, unsigned long long ssn, int seatNr);
	~Business();
	string getMeal();
	void setMeal(string meal);

	string description() override;

};


#endif