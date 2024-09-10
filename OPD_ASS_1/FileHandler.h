// FileHandler.h
#pragma once
#include <vector>
#include <string>
#include "iostream"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

class FileHandler {
public:
	bool read_from_file();
	void print();
	vector<vector<string>> info();
private:
	vector<vector<string>> tokens;
};
