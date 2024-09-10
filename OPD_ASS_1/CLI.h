//CLI.h
#pragma once
#include "Airplane.h"
#include "FileHandler.h"

class CLI {
public:
    CLI();
    void start();
    vector<string> user_input();
    void check(const vector<string>& row, vector<Airplane>& airplanes);
    void book(const vector<string>& row, vector<Airplane>& airplanes);
    void return_f(const vector<string>& row, vector<Airplane>& airplanes);
    bool is_number(const string& s);
    void view(const vector<string>& row, vector<Airplane>& airplanes);
private:
    vector<Airplane> airplanes;

};