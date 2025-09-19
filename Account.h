#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Account {
private:
    string account_id;
    string username;
    string password; // encrypted
    string role;

public:
    Account() {}
    Account(string id, string user, string pass, string r);

    string getId() const ;
    string getUsername() const ;
    string getPassword() const;
    string getRole() const;
    void setPassword(string newPass);
    void saveToFile(ofstream &out);
    bool loadFromFile(ifstream &in);
};

class AccountManager {
public:
    void addAccount(Account acc);
    Account findAccount(string username, string role);
    bool usernameExists(string username, string role);
    void printAll(); // in ra username + role (không có ID)
    void signIn();
    void signUp();
    void resetPassword();
    int getNextId(const string& role);
    void sortAndRewrite(const string& role);
};

// Helper functions
string encryptPassword(string password);
bool checkPassword(string encrypted, string raw);
string generateId(int counter);
string getPasswordInput(const string& prompt);

#endif
