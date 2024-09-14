#include "Passenger.h"

Passenger::Passenger(string name, unsigned long long ssn, int seatNr)
{
	this->name = name;
	this->ssn = ssn;
	this->seatNr = seatNr;
}

Passenger::Passenger()
{
	this->name = "";
	this->ssn = 0;
	this->seatNr = 0;
}

Passenger::~Passenger()
{
}

void Passenger::setName(string name)
{
	this->name = name;
}

string Passenger::getName()
{
	return this->name;
}

void Passenger::setSsn(unsigned long long ssn)
{
	this->ssn = ssn;
}

unsigned long long Passenger::getSsn()
{
	return this->ssn;
}

void Passenger::setSeatNr(int seatNr)
{
	this->seatNr = seatNr;
}

int Passenger::getSeatNr()
{
	return this->seatNr;
}
