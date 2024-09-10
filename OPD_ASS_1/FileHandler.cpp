#include "FileHandler.h"

bool FileHandler::read_from_file() {
    string input;

    cout << "Enter path to file: ";
    getline(cin, input);
    cout << endl;


    ifstream input_stream(input);
    if (!input_stream) {
        cerr << "Error opening file: " << input << endl;
        return false;
    }


    string line;
    //getline(input_stream, line);

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
    return true;

}

void FileHandler::print() {
    for (size_t i = 0; i < tokens.size(); i++) {
        for (size_t j = 0; j < tokens[i].size(); j++) {
            cout << tokens[i][j] << endl;
        }
        cout << "--------" << endl;
    }
}

vector<vector<string>> FileHandler::info() {
    return tokens;
}