#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

class FileHandler {
public:
    void read_from_file() {
        string input;

        cout << "Enter path to file: ";
        cin >> input;

        ifstream input_stream(input);
        if (!input_stream) {
            cerr << "Error opening file: " << input << std::endl;
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


int main() {
    FileHandler filehandler;
    filehandler.read_from_file();
    auto tokens = filehandler.info();
    filehandler.print();

    return 0;
}
