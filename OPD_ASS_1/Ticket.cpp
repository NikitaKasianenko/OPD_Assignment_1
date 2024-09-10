#include "Ticket.h"

Ticket::Ticket(string p_n, string s_n, string d, string pl_n, string p)
    : passenger_name(p_n), seat_number(s_n), data(d), airplane_number(pl_n), price(p) {

    srand((unsigned)time(NULL));
    string number;

    for (int i = 1; i <= 5; i++) {

        int random = 0 + (rand() % 10);


        number += to_string(random);
    }

    confirmed_ID = number;


}

string  Ticket::ticket_id() const {
    return confirmed_ID;
}

string  Ticket::get_price() const {
    return price;
}

string  Ticket::get_user_name() const {
    return passenger_name;
}

string  Ticket::get_airplane() const {
    return airplane_number;
}

string  Ticket::get_data() const {
    return data;
}

string  Ticket::get_seat() const {
    return seat_number;
}