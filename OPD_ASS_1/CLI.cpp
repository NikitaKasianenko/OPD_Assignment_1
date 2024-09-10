#include "CLI.h"

CLI::CLI() {
    FileHandler filehandler;
    while(!filehandler.read_from_file());
    auto tokens = filehandler.info();

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

void CLI::start() {
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

vector<string> CLI::user_input() {
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

void CLI::check(const vector<string>& row, vector<Airplane>& airplanes) {

    if (row.size() != 3) {
        cout << "Incorrect input" << endl;
        return;
    }

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

void CLI::book(const vector<string>& row, vector<Airplane>& airplanes) {

    if (row.size() != 5) {
        cout << "Incorrect input" << endl;
        return;
    }

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

void CLI::return_f(const vector<string>& row, vector<Airplane>& airplanes) {

    if (row.size() != 2 || !is_number(row[1])) {
        cout << "Incorrect input" << endl;
        return;
    }

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

bool CLI::is_number(const std::string& s) {
    return !s.empty() && std::all_of(s.begin(), s.end(), ::isdigit);
}

void CLI::view(const vector<string>& row, vector<Airplane>& airplanes) {

    string arg = row[1];
    if (is_number(arg)) {

        if (row.size() != 2) {
            cout << "Incorrect input" << endl;
            return;
        }

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

        if (row.size() != 3) {
            cout << "Incorrect input" << endl;
            return;
        }

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

        if (row.size() != 4) {
            cout << "Incorrect input" << endl;
            return;
        }

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
            cout << "No available places for the flight with such parameters" << endl;
        }

    }
}