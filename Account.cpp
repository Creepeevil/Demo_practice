#include "Account.h"
#include <conio.h> 
#include <vector>
#include <fstream>
#include <algorithm> // Required for std::sort
#include <windows.h>
using namespace std;

Account::Account(string id, string user, string pass, string r) {
    account_id = id;
    username = user;
    password = pass;
    role = r;
}

string Account::getId() const { return account_id; }
string Account::getUsername() const { return username; }
string Account::getPassword() const { return password; }
string Account::getRole() const { return role; }
void Account::setPassword(string newPass) { password = newPass; }

void Account::saveToFile(ofstream &out) {
    out << account_id << "," << username << "," << password << "," << role << "\n";
}

bool Account::loadFromFile(ifstream &in) {
    string line;
    if (!getline(in, line)) return false;

    size_t p1 = line.find(',');
    size_t p2 = line.find(',', p1 + 1);
    size_t p3 = line.find(',', p2 + 1);

    if (p1 == string::npos || p2 == string::npos || p3 == string::npos) return false;

    account_id = line.substr(0, p1);
    username   = line.substr(p1 + 1, p2 - p1 - 1);
    password   = line.substr(p2 + 1, p3 - p2 - 1);
    role       = line.substr(p3 + 1);

    return true;
}
int AccountManager:: getNextId(const string& role) {
    string file = (role == "patient") ? "Accountuser.txt" : "Accountadmin.txt";
    ifstream fin(file);
    Account acc;
    int maxId = 0;

    while (acc.loadFromFile(fin)) {
        string idStr = acc.getId().substr(2); // bỏ "ID"
        int idNum = stoi(idStr);
        if (idNum > maxId) maxId = idNum;
    }
    fin.close();
    return maxId + 1;
}

void AccountManager::sortAndRewrite(const string& role) {
    string file = (role == "patient") ? "Accountuser.txt" : "Accountadmin.txt";
    ifstream fin(file);
    vector<Account> accounts;
    Account acc;

    while (acc.loadFromFile(fin)) {
        accounts.push_back(acc);
    }
    fin.close();

    // Quick sort theo ID
    sort(accounts.begin(), accounts.end(), [](const Account& a, const Account& b) {
        return stoi(a.getId().substr(2)) < stoi(b.getId().substr(2));
    });

    ofstream fout(file, ios::trunc);
    for (auto &a : accounts) {
        a.saveToFile(fout);
    }
    fout.close();
}
void AccountManager::addAccount(Account acc) {
    string file = (acc.getRole() == "patient") ? "Accountuser.txt" : "Accountadmin.txt";
    ofstream fout(file, ios::app);
    acc.saveToFile(fout);
    fout.close();
}

Account AccountManager::findAccount(string username, string role) {
    string file = (role == "patient") ? "Accountuser.txt" : "Accountadmin.txt";
    ifstream fin(file);
    Account acc;
    while (acc.loadFromFile(fin)) {
        if (acc.getUsername() == username && acc.getRole() == role) {
            fin.close();
            return acc;
        }
    }
    fin.close();
    return Account("", "", "", "");
}

bool AccountManager::usernameExists(string username, string role) {
    string file = (role == "patient") ? "Accountuser.txt" : "Accountadmin.txt";
    ifstream fin(file);
    Account acc;
    while (acc.loadFromFile(fin)) {
        if (acc.getUsername() == username && acc.getRole() == role) {
            fin.close();
            return true;
        }
    }
    fin.close();
    return false;
}

void AccountManager::printAll() {
    cout << "--- Patients ---\n";
    ifstream fin1("Accountuser.txt");
    Account acc1;
    while (acc1.loadFromFile(fin1)) {
        cout << acc1.getUsername() << " (" << acc1.getRole() << ")\n";
    }
    fin1.close();

    cout << "--- Dentists ---\n";
    ifstream fin2("Accountadmin.txt");
    Account acc2;
    while (acc2.loadFromFile(fin2)) {
        cout << acc2.getUsername() << " (" << acc2.getRole() << ")\n";
    }
    fin2.close();
}

string encryptPassword(string password) {
    string result = "";
    for (char c : password) {
        result += char((c + 3) % 127); // mã hóa dịch ASCII
    }
    return result;
}

bool checkPassword(string encrypted, string raw) {
    return encrypted == encryptPassword(raw);
}

string generateId(int counter) {
    return "ID" + to_string(counter);
}
string getPasswordInput(const string& prompt) {
    string password;
    char ch;

    cout << prompt;
    while ((ch = _getch()) != 13) { // Enter
        if (ch == 8) { // Backspace
            if (!password.empty()) {
                password.pop_back();
                cout << "\b \b";
            }
        } else {
            password.push_back(ch);
            cout << '*';
        }
    }
    cout << endl;
    return password;
}
void AccountManager::signIn() {
    string username, password, role;
    cout << "Username: ";
    getline(cin, username);
    password = getPasswordInput("Password: ");
    cout << "Role (patient/dentist): ";
    getline(cin, role);

    Account acc = findAccount(username, role);
    if (!acc.getUsername().empty() && checkPassword(acc.getPassword(), password)) {
        cout << "Login successful! Welcome " << acc.getUsername() << " (" << acc.getRole() << ")\n";
    } else {
        cout << "Invalid username or password.\n";
    }
}

void AccountManager::signUp() {
    string username, role, password, confirm;
    cout << "Choose username: ";
    getline(cin, username);
    cout << "Role (patient/dentist): ";
    getline(cin, role);

    if (role != "patient" && role != "dentist") {
        cout << "Your role is invalid. Try again\n";
        return;
    }

    if (usernameExists(username, role)) {
        cout << "Username already exists.\n";
        return;
    }

    password = getPasswordInput("Password: ");
    confirm = getPasswordInput("Confirm password: ");

    if (password != confirm) {
        cout << "Passwords do not match.\n";
        return;
    }

    // Tìm ID tiếp theo cho role
    int nextId = getNextId(role);
    string account_id = generateId(nextId);
    string enc_pass = encryptPassword(password);

    Account newAcc(account_id, username, enc_pass, role);
    addAccount(newAcc);

    // Đảm bảo file luôn sắp xếp ID tăng dần
    sortAndRewrite(role);

    cout << "Account created successfully! ";
}
void AccountManager::resetPassword() {
    string username, role, new_pass, confirm;
    cout << "Enter username: ";
    getline(cin, username);
    cout << "Role (patient/dentist): ";
    getline(cin, role);

    Account acc = findAccount(username, role);
    if (acc.getUsername().empty()) {
        cout << "Username not found for this role. Please try again\n";
        return;
    }

    new_pass = getPasswordInput("New password: ");
    confirm = getPasswordInput("Confirm new password: ");

    if (new_pass != confirm) {
        cout << "Passwords do not match.\n";
        return;
    }

    string file = (role == "patient") ? "Accountuser.txt" : "Accountadmin.txt";
    ifstream fin(file);
    ofstream fout("temp.txt");
    Account temp;
    while (temp.loadFromFile(fin)) {
        if (temp.getUsername() == username && temp.getRole() == role) {
            temp.setPassword(encryptPassword(new_pass));
        }
        temp.saveToFile(fout);
    }
    fin.close();
    fout.close();
    remove(file.c_str());
    rename("temp.txt", file.c_str());

    cout << "Password reset successful!\n";
}
