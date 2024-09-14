#include "Booking.h"

Booking::Booking(unique_ptr<Passenger> passenger, const Flight& flight, int bookingNr)
    : passenger(move(passenger)), flight(flight), bookingNr(bookingNr) {}

Booking::~Booking() {}

string Booking::description() const {
    return passenger->description() + ", Flight Number: " + to_string(flight.getflightNr()) + ", Destination: " + flight.getDestination() + ", Booking Number: " + to_string(bookingNr);
}

int Booking::getBookingNr() const {
    return bookingNr;
}
