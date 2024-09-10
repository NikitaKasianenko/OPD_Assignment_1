#include "Seats.h"

Seats::Seats(const int& seatsPR, const string& range, const string& price)
    : seatsPR(seatsPR), range(range), price(price) {}

void Seats::print() const {
    cout << "Seats range: " << range << ", Seats per row: " << seatsPR << ", Price: " << price << endl;
}

bool Seats::isValidSeat(const string& seatNumber) const {
    string seatPattern = "^([1-9][0-9]?)([A-" + string(1, 'A' + seatsPR - 1) + "])$";
    regex seatRegex(seatPattern);

    if (!regex_match(seatNumber, seatRegex)) {
        cout << "Invalid seat format. Expected format: row number (1-99) + seat letter (A-" << (char)('A' + seatsPR - 1) << ").\n";
        return false;
    }

    int row = stoi(seatNumber.substr(0, seatNumber.size() - 1));
    char seatLetter = seatNumber.back();

    size_t dashPos = range.find('-');
    int startRow = stoi(range.substr(0, dashPos));
    int endRow = stoi(range.substr(dashPos + 1));

    if (row < startRow || row > endRow) {
        cout << "Invalid row number. Row must be between " << startRow << " and " << endRow << ".\n";
        return false;
    }

    return true;
}

bool Seats::isSeatAvailable(const string& seatNumber) const {
    for (const auto& ticket : tickets) {
        if (ticket.first == seatNumber) {
            return false;
        }
    }
    return true;
}


void Seats::bookTicket(const string& username, const string& seatNumber, const string& date, const string& airplane_NO) {
    if (tickets.find(seatNumber) == tickets.end()) {
        tickets[seatNumber] = new Ticket(username, seatNumber, date, airplane_NO, price);
        cout << "Successfully booked seat " << seatNumber << " for " << username << endl;
        cout << "Confirmed with ID " << tickets[seatNumber]->ticket_id() << endl;
    }
    else {
        cout << "Seat " << seatNumber << " is already booked." << endl;
    }
}


void Seats::printAvailableSeats(int& arg) const {
    size_t dashPos = range.find('-');
    int startRow = stoi(range.substr(0, dashPos));
    int endRow = stoi(range.substr(dashPos + 1));

    for (int row = startRow; row <= endRow; ++row) {
        for (char seat = 'A'; seat < 'A' + seatsPR; ++seat) {
            string seatNumber = to_string(row) + seat;

            if (arg == 0) {


                if (isSeatAvailable(seatNumber)) {
                    cout << seatNumber << " " << price << endl;
                }
                else {
                    cout << seatNumber << " - Booked" << endl;
                }
            }

            if (arg == 1) {
                if (!isSeatAvailable(seatNumber)) {

                    auto ticket = tickets.find(seatNumber);
                    string username = ticket->second->get_user_name();
                    string price = ticket->second->get_price();
                    cout << seatNumber << " " << username << " " << price << endl;

                }

            }
        }
    }
}



bool Seats::return_ticket(const string& ID) {
    for (auto iter = tickets.begin(); iter != tickets.end(); ++iter) {
        if (iter->second->ticket_id() == ID) {
            cout << "Refund " << iter->second->get_price() << " for " << iter->second->get_user_name() << endl;
            tickets.erase(iter);
            return true;
        }
    }
    return false;
}

bool Seats::view_ticket(const string& ID) {
    if (!ID.empty() && std::all_of(ID.begin(), ID.end(), ::isdigit)) {

        for (auto iter = tickets.begin(); iter != tickets.end(); ++iter) {
            if (iter->second->ticket_id() == ID) {
                cout << "Flight " << iter->second->get_airplane() << " , " << iter->second->get_data() << ", seat "
                    << iter->second->get_seat() << " price " << iter->second->get_price() << endl;

                return true;
            }
        }
    }
    else {


        bool finded = false;
        int counter = 1;

        for (auto iter = tickets.begin(); iter != tickets.end(); ++iter) {

            if (iter->second->get_user_name() == ID) {

                cout << counter << ". Flight " << iter->second->get_airplane() << ", " << iter->second->get_data() << ", seat "
                    << iter->second->get_seat() << " price " << iter->second->get_price() << endl;
                counter++;
                finded = true;

            }
        }
        if (finded) {
            return true;

        }


    }




    return false;
}


