#include "Economy.h"



Economy::Economy()
{
}

Economy::Economy(int bagageCapacity, string name, unsigned long long ssn, int seatNr)
    : Passenger(name, ssn, seatNr)
{
    this->baggageCapacity = bagageCapacity;
}

Economy::~Economy()
{
}

void Economy::setBaggageCapacity(int bagageCapacity)
{
    this->baggageCapacity = bagageCapacity;
}

int Economy::getBaggageCapacity()
{
    return this->baggageCapacity;
}

string Economy::description()
{
    return "Type: Economy, Name: " + getName() + ", SSN: " + to_string(getSsn()) +
        ", Seat number: " + to_string(getSeatNr()) + ", Number of baggage: " + to_string(this->baggageCapacity);
}
