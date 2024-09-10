// Seats.h
#pragma once
#include <string>
#include <unordered_map>
#include "Ticket.h"
#include <regex>

using namespace std;
class Seats {
private:
    int seatsPR;
    string range;
    string price;
    unordered_map<string, Ticket*> tickets;

public:
    Seats(const int& seatsPR, const string& range, const string& price);
    void print() const;
    bool isValidSeat(const string& seatNumber) const;
    bool isSeatAvailable(const string& seatNumber) const;
    void bookTicket(const string& username, const string& seatNumber, const string& date, const string& airplane_NO);
    void printAvailableSeats(int& arg) const;
    bool return_ticket(const string& ID);
    bool view_ticket(const string& ID);
};
