#ifndef FLIGHT_H
#define FLIGHT_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

class Flight {
private:
    int flightNr;
    string destination;

public:
    Flight();
    Flight(int flightNr, string destination);
    ~Flight();

    int getflightNr() const;
    string getDestination() const;
    bool limitOfAFlight(int limit, int nrOf);
};

#endif
