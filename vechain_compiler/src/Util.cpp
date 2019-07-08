#include "Util.hpp"
using namespace std;

Util::Util()
{
    string config = "./vechain_compiler/config/data.config";
    string root = "./target/release/";
    ifstream fin(config);
    string s;
    fin >> s;
    fin >> s;
    fin >> s;
    fileName = s;
    pureName = fileName.substr(0, fileName.rfind('.'));
}

bool Util::isValid(char c)
{
    return (c >= 'A' && c <= 'Z' || c >= 'a' && c <= 'z' || c == '_');
}

bool Util::isNum(char c) 
{
    return (c >= '0' && c <= '9');
}