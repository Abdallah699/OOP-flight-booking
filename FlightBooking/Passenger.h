#ifndef PASSENGER_H
#define PASSENGER_H

#include <string>
#include <ctime>

using namespace std;

class Passenger
{
private:
	string name;
	unsigned long long ssn;
	int seatNr;
public:
	Passenger(string name, unsigned long long ssn, int seatNr);
	Passenger();
	virtual ~Passenger();
	void setName(string name);
	string getName();
	void setSsn(unsigned long long ssn);
	unsigned long long getSsn();
	void setSeatNr(int seatNr);
	int getSeatNr();

	virtual string description() = 0;
};


#endif