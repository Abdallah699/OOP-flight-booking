#ifndef SYSTEM_H
#define SYSTEM_H

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "Booking.h"
#include "Business.h"
#include "Economy.h"
#include "Flight.h"
#include "Passenger.h"

class System {
private:
    vector<unique_ptr<Booking>> bookings;
    vector<unique_ptr<Flight>> flights;
    vector<Passenger*> passengers;
    int nrOfBusiness;
    int nrOfEconomy;
    int nrOfAll;
    string randomDates[10];

public:
    System();
    ~System();

    int generateSeatNr();
    int generateBookingNr();
    void writeAllBookingsToFile();
    void clearPassengers();
    void showAllBookings();
    void deleteAllBookings();
    void listOfFlights();
    void bookAFlight();
    bool SearchBooking();
    void clearAllBookings();
    void generateDifferentFlights(int flightNr);
    string generateRandomDate();
    void readFlightsFromFile();
    void readBookingsFromFile();
    void moveOnToMenu();
    bool deleteBooking();

    void showAllPassengers();
    void searchPassenger();
};


#endif 
