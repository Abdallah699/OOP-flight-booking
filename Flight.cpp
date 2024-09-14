#include "Flight.h"

Flight::Flight()
    :flightNr(0), destination("") 
{
}

Flight::Flight(int flightNr, string destination) {
    this->flightNr = flightNr;
    this->destination = destination;
}

Flight::~Flight()
{
}



int Flight::getflightNr() const { 
    return this->flightNr;
}

string Flight::getDestination() const { 
    return this->destination;
}

bool Flight::limitOfAFlight(int limit, int nrOf) {
    return nrOf < limit;
}
