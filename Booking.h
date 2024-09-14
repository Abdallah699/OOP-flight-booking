#ifndef BOOKING_H
#define BOOKING_H

#include <memory>
#include "Passenger.h"
#include "Flight.h"

class Booking {
private:
    unique_ptr<Passenger> passenger;
    Flight flight;
    int bookingNr;
    
public:
    Booking(unique_ptr<Passenger> passenger, const Flight& flight, int bookingNr);
    ~Booking();

    string description() const;
    int getBookingNr() const;
};

#endif
