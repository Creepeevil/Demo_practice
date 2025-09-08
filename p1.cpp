#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;
#include "p1.h"
// ---------------- Function hỗ trợ ----------------
bool usernameExists(string filename, string uname) {
    ifstream fin(filename);
    string u, p, r;
    while (fin >> u >> p >> r) {
        if (u == uname) return true;
    }
    return false;
}

bool checkLogin(string filename, string uname, string pass) {
    ifstream fin(filename);
    string u, p, r;
    while (fin >> u >> p >> r) {
        if (u == uname && p == pass) return true;
    }
    return false;
}

bool resetPassword(string filename, string uname, string newPass) {
    ifstream fin(filename);
    vector<Account*> temp;
    string u, p, r;
    bool found = false;

    while (fin >> u >> p >> r) {
        if (u == uname) {
            p = newPass;
            found = true;
        }
        if (r == "patient") temp.push_back(new User(u, p));
        else temp.push_back(new Admin(u, p));
    }
    fin.close();

    // ghi đè lại file
    ofstream fout(filename, ios::trunc);
    for (auto acc : temp) {
        fout << acc->getUsername() << " " << acc->getPassword() << " " << acc->getRole() << endl;
        delete acc;
    }
    fout.close();
    return found;
}
