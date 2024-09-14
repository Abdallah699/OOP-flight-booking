#include "System.h"
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <ctime>

System::System() : nrOfBusiness(0), nrOfEconomy(0), nrOfAll(0) 
{
    // läser från fil bara en gång i början 
    readFlightsFromFile();
    readBookingsFromFile();
    for (int i = 0; i < 10; ++i) {
        randomDates[i] = generateRandomDate();
    }
}

System::~System() 
{
    for (auto passenger : passengers) {
        delete passenger;
    }
    passengers.clear();
    // skriver in i fil bara i slutet under destrukt
    writeAllBookingsToFile();
}

int System::generateSeatNr() {
    srand(time(nullptr));
    return rand() % 200 + 1;
}

int System::generateBookingNr() {
    srand(time(nullptr));
    return rand() % 900000 + 100000;
}

void System::writeAllBookingsToFile() {
    ofstream passengerDatabase("bookings.txt", ios::out | ios::trunc);
    if (passengerDatabase.is_open()) {
        for (const auto& booking : bookings) {
            passengerDatabase << booking->description() << "\n";
        }
        passengerDatabase.close();
    }
    else {
        cerr << "Cannot open file for writing!\n";
    }
}

void System::clearPassengers() {
    bookings.clear();
    passengers.clear();
}

void System::showAllBookings() {
    system("cls");
    cout << "\033[1;32mList of all bookings: \033[0m" << endl << endl;
    for (const auto& booking : bookings) {
        cout << booking->description() << endl;
    }
}

void System::deleteAllBookings() {
    bookings.clear();
}

void System::readFlightsFromFile() {
    ifstream inputFile("flights.txt");

    string line;
    while (getline(inputFile, line)) {
        stringstream ss(line);
        int flightNumber;
        string destination;

        if (ss >> flightNumber >> destination) {
            auto newFlight = make_unique<Flight>(flightNumber, destination);
            flights.push_back(move(newFlight));
        }
        else {
            cerr << "Error reading line: " << line << endl;
        }
    }

    inputFile.close();
}

void System::moveOnToMenu() {
    cout << "\nPress Enter to continue..." << endl;
    cin.ignore();
    cin.get();
    system("cls");
}

void System::listOfFlights() {
    system("cls");
    cout << "\033[1;32m\nHere are the list of all the upcoming flights fron Ronneby Airport:\033[0m\n" << endl << endl;
    cout << "Flight Number" << "\t" << "Destination" << endl;
    cout << "----------------------------------------" << endl;
    for (const auto& flight : flights) {
        cout << "    " << flight->getflightNr() << "\t\t" << flight->getDestination() << endl;
    }
}

void System::bookAFlight() {
    string name, meal, date, departure, destination;
    unsigned long long ssn;
    int nrOfBagages, flightNr;
    int seatNr = generateSeatNr();
    int bookingNr = generateBookingNr();
    bool flightNrExists = false;
    vector<string> destinations;
    vector<int> flightNumbers;

    for (const auto& x : flights) {
        destinations.push_back(x->getDestination());
        flightNumbers.push_back(x->getflightNr());
    }

    system("cls");

    cout << "Full name: ";
    getline(cin, name);

    cout << "SSN (12 numbers): ";
    cin >> ssn;
    cin.ignore();

    if (cin.fail()) {
        cin.clear();
        cin.ignore();
        system("cls");
        cout << "\033[1;31mSSN must be numbers!\033[0m\n" << endl;
        return;
    }

    if (to_string(ssn).length() != 12) {
        system("cls");
        cout << "\033[1;31mSSN must be 12 numbers!\033[0m\n" << endl;
        return;
    }

    listOfFlights();
    cout << "Flight Number: ";
    cin >> flightNr;
    flightNrExists = false;
    Flight* selectedFlight = nullptr;
    if (!flightNumbers.empty()) {
        for (const auto& flight : flights) {
            if (flight->getflightNr() == flightNr) {
                flightNrExists = true;
                selectedFlight = flight.get();
                break;
            }
        }
    }

    generateDifferentFlights(flightNr);

    if (flightNrExists && selectedFlight != nullptr) {
        system("cls");
        int choice2;
        cout << "\n1) Economy\n2) Business\n--> ";
        cin >> choice2;
        cin.ignore();

        if (choice2 == 1) {
            cout << "Number of bagages: ";
            cin >> nrOfBagages;

            if (cin.fail()) {
                cin.clear();
                cin.ignore();
                system("cls");
                cout << "\033[1;31mNumber of bagages must be number/numbers!\033[0m\n" << endl;
                return;
            }

            if (selectedFlight->limitOfAFlight(120, this->nrOfEconomy)) {
                this->nrOfEconomy++;
                cout << "\033[1;32mBooking confirmed!\033[0m" << endl << endl << "Booking Number: " << bookingNr << endl
                    << "Type: Economy" << endl << "Name: " << name << endl << "SSn: "
                    << ssn << endl << "Seat number: " << seatNr << endl << "Number of bagages: " << nrOfBagages << endl
                    << endl << "Thank you for your purchase!\n" << endl;

                passengers.push_back(new Economy(nrOfBagages, name, ssn, seatNr));

                auto booking = make_unique<Booking>(make_unique<Economy>(nrOfBagages, name, ssn, seatNr), *selectedFlight, bookingNr);
                bookings.push_back(move(booking));

                moveOnToMenu();
            }
        }
        else if (choice2 == 2) {
            cout << "Meal preference for the duration of the flight? ";
            getline(cin, meal);

            if (selectedFlight->limitOfAFlight(30, this->nrOfBusiness)) {
                this->nrOfBusiness++;
                cout << "\033[1;32mBooking confirmed!\033[0m" << endl << endl << "Booking Number: " << bookingNr << endl
                    << "Type: Business" << endl << "Name: " << name << endl << "SSn: "
                    << ssn << endl << "Seat number: " << seatNr << endl << "Meal: " << meal << endl
                    << endl << "Thank you for your purchase!\n" << endl;


                passengers.push_back(new Business(meal, name, ssn, seatNr));

                auto booking = make_unique<Booking>(make_unique<Business>(meal, name, ssn, seatNr), *selectedFlight, bookingNr);
                bookings.push_back(move(booking));

                moveOnToMenu();
            }
        }
    }
    else {
        cout << "\033[1;31mInvalid flight number!\033[0m\n";
    }
}



void System::clearAllBookings() {
    bookings.clear();
    system("cls");
    cout << "\033[1;32mAll bookings are now deleted.\033[0m" << endl;
    moveOnToMenu();
}

void System::generateDifferentFlights(int flightNr) {
    vector<string> destinations;
    vector<int> flightNumbers;

    for (const auto& flight : flights) {
        destinations.push_back(flight->getDestination());
        flightNumbers.push_back(flight->getflightNr());
    }
    system("cls");

    cout << "\033[1;32mHere is the list of flights to the chosen destination:\033[0m\n" << endl;
    cout << "Choose from the list please" << endl;
    cout << "Choice number\tFlight Number\tDestination\tDate" << endl;
    cout << "------------------------------------------------------------------------------------------------------------------" << endl;

    for (int i = 0; i < flightNumbers.size(); i++) {
        if (flightNr == flightNumbers[i]) {
            for (int j = 0; j < 10; j++) {
                this->randomDates[j] = generateRandomDate();
                cout << j << "\t" << "Flight Number: " << flightNumbers[i] << "\t" << "Destination: " << destinations[i] << "\t" << "Date: " << this->randomDates[j] << endl;
            }
            break;
        }
    }

    int choice;
    for (int i = 0; i < flightNumbers.size(); i++) {
        if (flightNr == flightNumbers[i]) {
            cout << "\nType in your choice: ";
            cin >> choice;
            if (choice >= 0 && choice < 10) {
                cout << "Flight Number: " << flightNumbers[i] << "\t" << "Destination: " << destinations[i] << "\t" << "Date: " << this->randomDates[choice] << "\t" << endl;
            }
            else {
                cout << "\033[1;31mInvalid choice!\033[0m" << endl;
            }
            break;
        }
    }
}

void System::readBookingsFromFile() {
    ifstream inputFile("bookings.txt");

    if (!inputFile.is_open()) {
        cerr << "Cannot open file for reading!\n";
        return;
    }

    string line;
    while (getline(inputFile, line)) {
        stringstream ss(line);
        string type, name, meal, destination;
        unsigned long long ssn;
        int seatNr, nrOfBagages, bookingNr, flightNr;

        getline(ss, type, ':');
        ss.ignore(); 
        getline(ss, type, ',');

        getline(ss, line, ':');
        ss.ignore();
        getline(ss, name, ',');

        getline(ss, line, ':');
        ss.ignore();
        ss >> ssn;
        ss.ignore();

        getline(ss, line, ':');
        ss.ignore();
        ss >> seatNr;
        ss.ignore();

        if (type == "Economy") {
            getline(ss, line, ':');
            ss.ignore();
            ss >> nrOfBagages;
            ss.ignore();

            getline(ss, line, ':');
            ss.ignore();
            ss >> flightNr;
            ss.ignore();

            getline(ss, line, ':');
            ss.ignore();
            getline(ss, destination, ',');

            getline(ss, line, ':');
            ss.ignore();
            ss >> bookingNr;

            Flight* flight = nullptr;
            for (const auto& f : flights) {
                if (f->getflightNr() == flightNr) {
                    flight = f.get();
                    break;
                }
            }

            if (flight) {
                this->passengers.push_back(new Economy(nrOfBagages, name, ssn, seatNr));
                auto passenger = make_unique<Economy>(nrOfBagages, name, ssn, seatNr);
                auto booking = make_unique<Booking>(move(passenger), *flight, bookingNr);
                bookings.push_back(move(booking));
            }
        }
        else if (type == "Business") {
            getline(ss, line, ':');
            ss.ignore();
            getline(ss, meal, ',');

            getline(ss, line, ':');
            ss.ignore();
            ss >> flightNr;
            ss.ignore();

            getline(ss, line, ':');
            ss.ignore();
            getline(ss, destination, ',');

            getline(ss, line, ':');
            ss.ignore();
            ss >> bookingNr;

            Flight* flight = nullptr;
            for (const auto& f : flights) {
                if (f->getflightNr() == flightNr) {
                    flight = f.get();
                    break;
                }
            }

            if (flight) {
                this->passengers.push_back(new Business(meal, name, ssn, seatNr));
                auto passenger = make_unique<Business>(meal, name, ssn, seatNr);
                auto booking = make_unique<Booking>(move(passenger), *flight, bookingNr);
                bookings.push_back(move(booking));
            }
        }
        else {
            cerr << "\033[1;31mUnknown booking type!\033[0m" << type << endl;
        }
    }

    inputFile.close();
}


bool System::SearchBooking() {
    system("cls");
    int bookingNr;
    cout << "Enter booking number: ";
    cin >> bookingNr;
    system("cls");
    for (const auto& booking : bookings) {
        if (booking->getBookingNr() == bookingNr) {
            cout << "\033[1;32mBooking found:\033[0m" << endl << booking->description() << endl;

            return true;
        }
    }
    
    cout << "\033[1;31mBooking not found!\033[0m" << endl;
    return false;
}

bool System::deleteBooking() {
    int bookingNr;
    cout << "Enter booking number: ";
    cin >> bookingNr;

    for (auto it = bookings.begin(); it != bookings.end(); ++it) {
        if ((*it)->getBookingNr() == bookingNr) {
            bookings.erase(it);
            cout << "\033[1;32mBooking deleted successfully!\033[0m" << endl;
            return true;
        }
    }

    cout << "\033[1;31mBooking not found!\033[0m" << endl;
    return false;
}

void System::showAllPassengers()
{
    system("cls");
    if (passengers.empty()) {
        cout << "\033[1;31mNo passengers found!\033[0m\n";
        return;
    }

    cout << "\033[1;32mList of all passengers:\033[0m" << endl;
    for (const auto& passenger : passengers) {
        cout << "\nName: " << passenger->getName() << endl;
        cout << "SSN: " << passenger->getSsn() << endl;
        cout << "Seat Number: " << passenger->getSeatNr() << endl;

        if (auto business = dynamic_cast<Business*>(passenger)) {
            cout << "Type: Business" << endl;
            cout << "Meal Preference: " << business->getMeal() << endl;
        }
        else if (auto economy = dynamic_cast<Economy*>(passenger)) {
            cout << "Type: Economy" << endl;
            cout << "Number of Bagages: " << economy->getBaggageCapacity() << endl;
        }
        cout << "---------------------------------" << endl << endl;
    }
    moveOnToMenu();
}

void System::searchPassenger()
{
    string name;
    unsigned long long ssn;
    bool found = false;

    system("cls");

    cout << "Enter the full name of the passenger: ";
    getline(cin, name);

    cout << "Enter the SSN (12 digits) of the passenger: ";
    cin >> ssn;
    cin.ignore();  

    if (cin.fail() || to_string(ssn).length() != 12) {
        cin.clear();
        cin.ignore(); 
        system("cls");
        cout << "\033[1;31mInvalid SSN! SSN must be 12 digits.\033[0m\n" << endl;
        return;
    }
    system("cls");
    for (const auto& passenger : passengers) {
        if (passenger->getName() == name && passenger->getSsn() == ssn) {
            cout << "\033[1;32mPassenger found:\033[0m" << endl;
            cout << "Name: " << passenger->getName() << endl;
            cout << "SSN: " << passenger->getSsn() << endl;
            cout << "Seat Number: " << passenger->getSeatNr() << endl;
            if (auto business = dynamic_cast<Business*>(passenger)) {
                cout << "Meal Preference: " << business->getMeal() << endl;
            }
            else if (auto economy = dynamic_cast<Economy*>(passenger)) {
                cout << "Number of Bagages: " << economy->getBaggageCapacity() << endl;
            }
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "\033[1;31mPassenger not found!\033[0m\n";
    }
    moveOnToMenu();
}




string System::generateRandomDate()
{
    int day = rand() % 30 + 1;
    int month = rand() % 12 + 1;
    int year = 2000 + rand() % 1 + 24;
    return to_string(year) + "-" + to_string(month) + "-" + to_string(day);
}
