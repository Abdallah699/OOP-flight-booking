#include <iostream>
#include "System.h"
#include "Flight.h"
#include <random>
#include <ctime>
#include <vector>

using namespace std;

int main() {

    System system;

    bool stillBooking = true;

    while (stillBooking) {
        int choice;

        cout << "Please choose an option from the menu:\n"
            << "1) List of flights\n"
            << "2) Book a flight\n"
            << "3) Show all bookings\n"
            << "4) Search for a booking with booking number\n"
            << "5) Delete a booking with booking number\n"
            << "6) Clear all bookings\n"
            << "7) Show all passengers\n"
            << "8) Search for a passenger via ssn\n"
            << "9) Quit\n--> ";
        cin >> choice;
        cin.ignore();

        if (cin.fail() || choice > 9) {
            cin.clear();
            cin.ignore();
            cout << "\033[1;31mInvalid choice!\033[0m" << endl;
            continue;
        }

        switch (choice) {
        case 1:
            system.listOfFlights();
            system.moveOnToMenu();
            break;
        case 2:
            system.bookAFlight();
            break;
        case 3:
            system.showAllBookings();
            system.moveOnToMenu();
            break;
        case 4:
            system.SearchBooking();
            system.moveOnToMenu();
            break;
        case 5:
            system.deleteBooking();
            break;
        case 6:
            system.clearAllBookings();
            break;    
        case 7:
            system.showAllPassengers();
            break;
        case 8:
            system.searchPassenger();
            break;
        case 9:
            stillBooking = false;
            break;
        default:
            cout << "\033[1;31mInvalid choice!\033[0m" << endl;
            break;
        }
    }

    return 0;
}
