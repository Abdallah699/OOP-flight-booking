#ifndef ECONOMY_H
#define ECONOMY_H
#include "Passenger.h"


class Economy : public Passenger
{
private:
	int baggageCapacity = 0;
public:
	Economy();
	Economy(int bagageCapacity, string name, unsigned long long ssn, int seatNr);
	~Economy();
	void setBaggageCapacity(int bagageCapacity);
	int getBaggageCapacity();

	string description() override;
};


#endif 
