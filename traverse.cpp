// PROJECT IDENTIFIER: 40FB54C86566B9DDEAB902CC80E8CE85C1C62AAD
#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <fstream>
#include <string>

using namespace std;

struct Coordinate {
    size_t x;
    size_t y;
};

struct Options{
    char captain = 'S';
    char firstMate = 'Q';
    string huntOrder = "NESW";
    bool verbose = false;
    bool stats = false;
    char path;

};

struct Legend {
    char symbol = '.';
    char status = 'u';
};

