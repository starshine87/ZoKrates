#pragma once
#include <iostream>
#include <fstream>
using namespace std;

class Util {
public:
    string fileName;
    string pureName;
    string root;
    Util();
    static bool isValid(char c);
    static bool isNum(char c);
};