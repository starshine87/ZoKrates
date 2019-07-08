#include <iostream>
#include <fstream>
#include <vector>
#include "Util.cpp"
using namespace std;

int main()
{
    Util util;
    string rawFile = util.fileName + ".veq";
    ifstream fin(rawFile);
    string exp;
    getline(fin, exp);
    vector<string> paramName;
    bool flag = false;
    string buffer = "";
    for (int i=0; i<exp.length(); ++i) {
        if (flag) {
            if (Util::isValid(exp[i]) || Util::isNum(exp[i])) {
                buffer += exp[i];
            } else {
                // TODO
                if (buffer == "hash") {

                }
                paramName.push_back(buffer);
                buffer = "";
                flag = false;
            }
        } else {
            if (Util::isValid(exp[i])) {
                buffer += exp[i];
                flag = true;
            }
        }
    }

    string outFile = util.pureName + ".code";
    ofstream fout(util.root + outFile);
    fout << "def main(";
    for (int i=0; i<paramName.size(); ++i) {
        if (i!=0) fout << ", ";
        fout << "private field " << paramName[i];
    }
    fout << ") -> (field):\n";
    fout << "  field result = if ";
    for (int i=0; i<exp.length(); ++i) {
        if (exp[i] == '=') fout << "==";
        else fout << exp[i];
    }
    fout << " then 1 else 0 fi\n" << "  return result";
    fout.close();
    ofstream fbash(util.root + "make.sh");
    fbash << "#!/bin/bash\n" << endl;
    fbash << "./zokrates compile -i " << outFile << endl;
    fbash << "./zokrates setup" << endl;
    fbash << "./zokrates compute-witness -a ";
    string s;
    while (fin >> s) {
        fbash << s << " ";
    }
    fbash << endl;
    fbash << "./zokrates generate-proof\n" << "./zokrates export-verifier\n";
    fbash.close();
    fin.close();
    return 0;
}