#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <unordered_map>
#include <regex>

using namespace std;

class FileHandler {
public:
    void read_from_file() {
        string input;

        cout << "Enter path to file: ";
        cin >> input;

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
    bool booked;
    string data;
    string airplane_number;
public:
    Ticket(string p_n, string s_n, string d, string pl_n)
        : passenger_name(p_n), seat_number(s_n), data(d), airplane_number(pl_n) {}


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

    void bookTiket(const string& username,const string& seatnumber, const string& data,const string& airplane_NO ){
        tickets[seatnumber] = new Ticket(username, seatnumber, data, airplane_NO);
    }

};

class Airplane {
private:
    string data;
    string airplane_NO;
    int seats_PR;
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

    string booking(const string& seatNumber) const {
        for (const auto& seat : seats) {
            if (seat.isValidSeat(seatNumber)) {
                seat;
            }
        }

    }
};



int main() {
    FileHandler filehandler;
    filehandler.read_from_file();
    auto tokens = filehandler.info();
    filehandler.print();

    vector<Airplane> airplanes;

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


    return 0;
}
