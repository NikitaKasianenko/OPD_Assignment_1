#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <unordered_map>
#include <regex>
#include <cstdlib>
#include <ctime> 

using namespace std;

class FileHandler {
public:
    void read_from_file() {
        string input;

        cout << "Enter path to file: ";
        getline(cin, input);


        ifstream input_stream(input);
        if (!input_stream) {
            cerr << "Error opening file: " << input << endl;
            return;
        }

        string line;
        while (getline(input_stream, line)) {
            stringstream ss(line);
            string token;
            vector<string> row;
            char delimiter = ' ';

            while (getline(ss, token, delimiter)) {
                row.push_back(token);
            }

            tokens.push_back(row);
        }

        input_stream.close();
    }

    vector<vector<string>> info() {
        return tokens;
    }

    void print() {
        for (size_t i = 0; i < tokens.size(); i++) {
            for (size_t j = 0; j < tokens[i].size(); j++) {
                cout << tokens[i][j] << endl;
            }
            cout << "--------" << endl;
        }
    }

private:
    vector<vector<string>> tokens;
};

class Ticket {
private:
    string passenger_name;
    string seat_number;
    string data;
    string airplane_number;
    string confirmed_ID;
    string price;
public:
    Ticket(string p_n, string s_n, string d, string pl_n, string p)
        : passenger_name(p_n), seat_number(s_n), data(d), airplane_number(pl_n),price(p) {

        srand((unsigned)time(NULL));  
        string number;  

        for (int i = 1; i <= 5; i++) {
            
            int random = 0 + (rand() % 10);

   
            number += to_string(random);
        }

        confirmed_ID = number;


    }

    string  ticket_id() const {
        return confirmed_ID;
    }

    string get_price() const {
        return price;
    }

    string get_user_name() const {
        return passenger_name;
    }

    string get_airplane() const {
        return airplane_number;
    }

    string get_data() const {
        return data;
    }

    string get_seat() const {
        return seat_number;
    }


};

class Seats {
private:
    int seatsPR;  
    string range; 
    string price;
    unordered_map<string, Ticket*> tickets;

public:
    Seats(const int& seatsPR, const string& range, const string& price)
        : seatsPR(seatsPR), range(range), price(price) {}

    void print() const {
        cout << "Seats range: " << range << ", Seats per row: " << seatsPR << ", Price: " << price << endl;
    }

    bool isValidSeat(const string& seatNumber) const {
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

    bool isSeatAvailable(const string& seatNumber) const {
        for (const auto& ticket : tickets) {
            if (ticket.first == seatNumber) {
                return false;
            }
        }
        return true;
    }


    void bookTicket(const string& username, const string& seatNumber, const string& date, const string& airplane_NO) {
        if (tickets.find(seatNumber) == tickets.end()) {
            tickets[seatNumber] = new Ticket(username, seatNumber, date, airplane_NO, price); 
            cout << "Successfully booked seat " << seatNumber << " for " << username << endl;
            cout << "Confirmed with ID " << tickets[seatNumber]->ticket_id() << endl;
        }
        else {
            cout << "Seat " << seatNumber << " is already booked." << endl;
        }
    }


    void printAvailableSeats(int& arg) const {
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

                        for (auto& ticket : tickets) {
                            string username = ticket.second->get_user_name();
                            string price = ticket.second->get_price();

                            cout << seatNumber << " " << username << " " << price << endl;
                        }

                    }

                }
            }
        }
    }



    bool return_ticket(const string& ID) {
        for (auto iter = tickets.begin(); iter != tickets.end(); ++iter) {
            if (iter->second->ticket_id() == ID) {
                cout << "Refund " << iter->second->get_price() << " for " << iter->second->get_user_name() << endl;
                tickets.erase(iter);
                return true;
            }
        }
        return false;
    }

    bool view_ticket(const string& ID) {
        if (!ID.empty() && std::all_of(ID.begin(), ID.end(), ::isdigit)){

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

                    cout << counter<<". Flight " << iter->second->get_airplane() << ", " << iter->second->get_data() << ", seat "
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



};

class Airplane {
private:
    string data;
    string airplane_NO;
    vector<Seats> seats;

public:
    Airplane(const string& d, const string& A, const vector<Seats>& seatList)
        : data(d), airplane_NO(A), seats(seatList) {}

    string getData() const {
        return data;
    }

    string getAirplane_NO() const {
        return airplane_NO;
    }

    void print() const {
        cout << "Airplane NO: " << airplane_NO << ", Date: " << data << endl;
        cout << "Range to Price: " << endl;
        for (const auto& seat : seats) {
            seat.print();
        }
        cout << "--------" << endl;
    }

    bool validateSeat(const string& seatNumber) const {
        for (const auto& seat : seats) {
            if (seat.isValidSeat(seatNumber)) {
                return true;
            }
        }
        cout << "Invalid seat for airplane " << airplane_NO << ".\n";
        return false;
    }

    void const bookSeat(const string& username, const string& seatNumber) {
        for (auto& seat : seats) {
            if (seat.isValidSeat(seatNumber)) {
                seat.bookTicket(username, seatNumber, data, airplane_NO);
                return;
            }
        }
        cout << "Invalid seat number for this flight." << endl;
    }

    void printAvailableSeats(int& arg) const {
        for (const auto& seat : seats) {
            seat.printAvailableSeats(arg);  
        }
    }

    bool returnTicket (const string& ID){
        for (auto& seat : seats) {
            if (seat.return_ticket(ID)) {
                return true;
            }
        }
        return false;


    }

    bool viewTicket(const string& ID) {
        for (auto& seat : seats) {
            if (seat.view_ticket(ID)) {
                return true;
            }
        }
        return false;


    }

    vector<Seats> Seats(){
        return seats;
    }

};

class CLI {
public:
    CLI() {
        FileHandler filehandler;
        filehandler.read_from_file();
        auto tokens = filehandler.info();
        filehandler.print();

        for (auto& row : tokens) {
            string data = row[0];
            string airplane_NO = row[1];
            int seats = atoi(row[2].c_str());

            vector<Seats> seatList;

            for (size_t i = 3; i + 1 < row.size(); i += 2) {
                string range = row[i];
                string price = row[i + 1];
                seatList.emplace_back(seats, range, price);
            }

            airplanes.emplace_back(data, airplane_NO, seatList);
        }

        for (const auto& airplane : airplanes) {
            airplane.print();
        }
    };

    void start() {
        while (1) {
            auto input = user_input();
            if (input.empty()) continue;

            string command = input[0]; 

            if (command == "check") {
                check(input, airplanes);
            }
            else if (command == "book") {
                book(input, airplanes);
            }
            else if (command == "return") {
                return_f(input, airplanes);
            }
            else if (command == "view") {

                view(input, airplanes);
            }
            else if (command == "exit") {
                break;
            }
            else {
                cout << "Unknown command" << endl;
            }
        }
    }

    vector<string> user_input() {
        string line;
        cout << "Input: ";
        getline(cin, line);  
        stringstream ss(line);
        string token;
        vector<string> row;
        char delimiter = ' ';

        while (getline(ss, token, delimiter)) {
            row.push_back(token);  
        }

        /*for (const auto& words : row) {
            cout << words << " "; 
        }*/

        return row;
    }

    void check(const vector<string>& row, vector<Airplane>& airplanes) {
        string Date = row[1];
        string FlightNo = row[2];
        int arg = 0;

        bool find_airplane = false;
        for (const auto& airplane : airplanes) {
            if (Date == airplane.getData() && FlightNo == airplane.getAirplane_NO()) {
                airplane.printAvailableSeats(arg);
                find_airplane = true;
            }
        }
        if (!find_airplane) {
            cout << "No avalible places for the filght with such parameters" << endl;
        }

    }

    void book(const vector<string>& row, vector<Airplane>& airplanes) {
        string Date = row[1];
        string FlightNo = row[2];
        string place = row[3];
        string Username = row[4];

        bool find_airplane = false;
        for (auto& airplane : airplanes) {
            if (Date == airplane.getData() && FlightNo == airplane.getAirplane_NO() && airplane.validateSeat(place)) {

                airplane.bookSeat(Username, place);
                find_airplane = true;
            }
        }
        if (!find_airplane) {
            cout << "No avalible places for the filght with such parameters" << endl;
        }

    }

    void return_f(const vector<string>& row, vector<Airplane>& airplanes) {
        string ID = row[1];
        bool find_ticket = false;

        for (auto& airplane : airplanes) {
            if (airplane.returnTicket(ID)) {
                find_ticket = true;
                break;
            }
        }

        if (!find_ticket) {
            cout << "No ticket with such ID" << endl;
        }
    }

    bool is_number(const std::string& s) {
        return !s.empty() && std::all_of(s.begin(), s.end(), ::isdigit);
    }

    void view(const vector<string>& row, vector<Airplane>& airplanes) {

        string arg = row[1];
            if (is_number(arg)) {

                string ID = arg;
                bool find_ticket = false;

                for (auto& airplane : airplanes) {
                    if (airplane.viewTicket(ID)) {
                        find_ticket = true;
                        break;
                    }
                }

                if (!find_ticket) {
                    cout << "No ticket with such ID" << endl;
                }

            }

            if (arg == "username") {

                string username = row[2];
                bool find_ticket = false;

                for (auto& airplane : airplanes) {
                    if (airplane.viewTicket(username)) {
                        find_ticket = true;
                        break;
                    }
                }

                if (!find_ticket) {
                    cout << "No user with such name" << endl;
                }


            }

            if (arg == "flight") {

                string Date = row[3];
                string FlightNO = row[2];
                int arg = 1;

                bool find_airplane = false;
                for (const auto& airplane : airplanes) {
                    if (Date == airplane.getData() && FlightNO == airplane.getAirplane_NO()) {
                        airplane.printAvailableSeats(arg);
                        find_airplane = true;
                    }
                }
                if (!find_airplane) {
                    cout << "No avalible places for the filght with such parameters" << endl;
                }


            }


    }

private:
    vector<Airplane> airplanes;

};

int main() {

    CLI CLI;
    CLI.start();

    return 0;
}
