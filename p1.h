#ifndef P1_H
#define P1_H
// Base class
class Account {
protected:
    string username;
    string password;
    string role; // "patient" or "dentist"
public:
    Account() {}
    Account(string u, string p, string r) : username(u), password(p), role(r) {}

    string getUsername() { return username; }
    string getPassword() { return password; }
    string getRole() { return role; }

    void setPassword(string newPass) { password = newPass; }

    virtual void saveToFile() = 0; // abstract
};

// Class User (Patient)
class User : public Account {
public:
    User(string u, string p) : Account(u, p, "patient") {}
    void saveToFile() override {
        ofstream fout("accountUser.txt", ios::app);
        fout << username << " " << password << " " << role << endl;
        fout.close();
    }
};

// Class Admin (Dentist)
class Admin : public Account {
public:
    Admin(string u, string p) : Account(u, p, "dentist") {}
    void saveToFile() override {
        ofstream fout("accountAdmin.txt", ios::app);
        fout << username << " " << password << " " << role << endl;
        fout.close();
    }
};

#endif
