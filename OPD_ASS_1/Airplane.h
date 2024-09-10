// Airplane.h
#pragma once
#include <string>
#include "Seats.h"

using namespace std;
class Airplane {
private:
    string data;
    string airplane_NO;
    vector<Seats> seats;

public:
    Airplane(const string& d, const string& A, const vector<Seats>& seatList)
        : data(d), airplane_NO(A), seats(seatList) {};
    string getData() const;
    string getAirplane_NO() const;
    void print() const;
    bool validateSeat(const string& seatNumber) const;
    void const bookSeat(const string& username, const string& seatNumber);
    void printAvailableSeats(int& arg) const;
    bool returnTicket(const string& ID);
    bool viewTicket(const string& ID);
    vector<Seats> Seats();
};
