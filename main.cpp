#include "Account.h"
#include "Home.h"
#include <iostream>
using namespace std;

int main() {
    Home manager;
    while (true) {
        manager.showMenuUI();  // không cần nhập số nữa
    }
    system("pause");
    return 0;
}
