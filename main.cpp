#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;
#include "p1.h"
// ---------------- Main Menu ----------------
int main() {
    int choice;
    do {
        cout << "\n===== MENU =====\n";
        cout << "1. Sign Up\n";
        cout << "2. Sign In\n";
        cout << "3. Forget Password\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            string uname, pass, pass2, role;
            cout << "Enter username: ";
            cin >> uname;
            cout << "Enter password: ";
            cin >> pass;
            cout << "Confirm password: ";
            cin >> pass2;
            cout << "Enter role (patient/dentist): ";
            cin >> role;

            if (pass != pass2) {
                cout << "Password confirmation does not match!\n";
                continue;
            }

            string filename = (role == "patient") ? "accountUser.txt" : "accountAdmin.txt";
            if (usernameExists(filename, uname)) {
                cout << "Username already exists!\n";
                continue;
            }

            if (role == "patient") {
                User u(uname, pass);
                u.saveToFile();
            } else {
                Admin a(uname, pass);
                a.saveToFile();
            }
            cout << "Sign up successful!\n";
        }
        else if (choice == 2) {
            string uname, pass, role;
            cout << "Enter username: ";
            cin >> uname;
            cout << "Enter password: ";
            cin >> pass;
            cout << "Enter role (patient/dentist): ";
            cin >> role;

            string filename = (role == "patient") ? "accountUser.txt" : "accountAdmin.txt";
            if (checkLogin(filename, uname, pass)) {
                cout << "Login successful! Welcome " << uname << " (" << role << ")\n";
            } else {
                cout << "Login failed!\n";
            }
        }
        else if (choice == 3) {
            string uname, newPass, pass2, role;
            cout << "Enter username: ";
            cin >> uname;
            cout << "Enter new password: ";
            cin >> newPass;
            cout << "Confirm new password: ";
            cin >> pass2;
            cout << "Enter role (patient/dentist): ";
            cin >> role;

            if (newPass != pass2) {
                cout << "Password confirmation does not match!\n";
                continue;
            }

            string filename = (role == "patient") ? "accountUser.txt" : "accountAdmin.txt";
            if (resetPassword(filename, uname, newPass)) {
                cout << "Password reset successfully!\n";
            } else {
                cout << "Username not found!\n";
            }
        }
    } while (choice != 0);

    return 0;
}
