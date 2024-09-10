#include "Airplane.h"

string Airplane::getData() const {
    return data;
}

string Airplane::getAirplane_NO() const {
    return airplane_NO;
}

void Airplane::print() const {
    cout << "Airplane NO: " << airplane_NO << ", Date: " << data << endl;
    cout << "Range to Price: " << endl;
    for (const auto& seat : seats) {
        seat.print();
    }
    cout << "--------" << endl;
}

bool Airplane::validateSeat(const string& seatNumber) const {
    for (const auto& seat : seats) {
        if (seat.isValidSeat(seatNumber)) {
            return true;
        }
    }
    cout << "Invalid seat for airplane " << airplane_NO << ".\n";
    return false;
}

void const Airplane::bookSeat(const string& username, const string& seatNumber) {
    for (auto& seat : seats) {
        if (seat.isValidSeat(seatNumber)) {
            seat.bookTicket(username, seatNumber, data, airplane_NO);
            return;
        }
    }
    cout << "Invalid seat number for this flight." << endl;
}

void Airplane::printAvailableSeats(int& arg) const {
    for (const auto& seat : seats) {
        seat.printAvailableSeats(arg);
    }
}

bool Airplane::returnTicket(const string& ID) {
    for (auto& seat : seats) {
        if (seat.return_ticket(ID)) {
            return true;
        }
    }
    return false;


}

bool Airplane::viewTicket(const string& ID) {
    for (auto& seat : seats) {
        if (seat.view_ticket(ID)) {
            return true;
        }
    }
    return false;


}

vector<Seats> Airplane::Seats() {
    return seats;
}