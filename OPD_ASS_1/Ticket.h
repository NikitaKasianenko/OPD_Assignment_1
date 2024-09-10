// Ticket.h
#pragma once
#include "iostream"
#include <string>

using namespace std;

class Ticket {
private:
    string passenger_name;
    string seat_number;
    string data;
    string airplane_number;
    string confirmed_ID;
    string price;
public:
    Ticket(string p_n, string s_n, string d, string pl_n, string p);
    string  ticket_id() const;
    string get_price() const;
    string get_user_name() const;
    string get_airplane() const;
    string get_data() const;
    string get_seat() const;

};