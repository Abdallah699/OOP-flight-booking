#include "Business.h"

Business::Business()
{
}

Business::Business(string meal, string name, unsigned long long ssn, int seatNr)
    :Passenger(name, ssn, seatNr)
{
    this->meal = meal;
}

Business::~Business()
{
}

string Business::getMeal()
{
    return this->meal;
}

void Business::setMeal(string meal)
{
    this->meal = meal;
}

string Business::description()
{
    return "Type: Business, Name: " + getName() + ", SSN : " + to_string(getSsn()) +
        ", Seat number: " + to_string(getSeatNr()) + ", Meal: " + this->meal;
}
