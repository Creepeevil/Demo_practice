#include "Account.h"
#include "Home.h"
#include <conio.h> 
#include <windows.h>
#include<iostream>
using namespace std;
// Hàm vẽ khung chữ nhật
void Home::gotoXY(int x, int y) {
    COORD coord; coord.X = x; coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void Home::setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}


void Home::drawBox(int x, int y, int w, int h) {
    gotoXY(x, y); cout << char(218);
    for (int i = 0; i < w - 2; i++) cout << char(196);
    cout << char(191);

    for (int i = 1; i < h - 1; i++) {
        gotoXY(x, y + i); cout << char(179);
        gotoXY(x + w - 1, y + i); cout << char(179);
    }

    gotoXY(x, y + h - 1); cout << char(192);
    for (int i = 0; i < w - 2; i++) cout << char(196);
    cout << char(217);
}
void Home::showMenuUI() {
    int current = 0;
    string buttons[4] = {"Sign in", "Sign up", "Forgot password", "Exit"};

    while (true) {
        system("cls");

        // Vẽ khung ngoài
        int boxX = 20, boxY = 8, boxW = 60, boxH = 5;
        drawBox(boxX, boxY, boxW, boxH);

        // Tính toán vị trí các nút
        int spacing = (boxW - 3 * 12) / 4;
        int y = boxY + 2;
        int x1 = boxX + spacing;
        int x2 = x1 + 12 + spacing;
        int x3 = x2 + 12 + spacing;
        int exitX = boxX + (boxW / 2) - 3;
        int exitY = boxY + 8;

        // Vẽ 3 nút đầu
        int xPos[3] = {x1, x2, x3};
        for (int i = 0; i < 3; i++) {
            gotoXY(xPos[i], y);
            if (i == current) {
                setColor(112);
                cout << " " << buttons[i] << " ";
                setColor(7);
            } else {
                cout << " " << buttons[i] << " ";
            }
        }

        // Vẽ nút Exit
        gotoXY(exitX, exitY);
        if (current == 3) {
            setColor(112);
            cout << " " << buttons[3] << " ";
            setColor(7);
        } else {
            cout << " " << buttons[3] << " ";
        }

        // Chờ phím
        char key = _getch();

        if (key == -32) { // phím mũi tên
            key = _getch();
            if (key == 75 && current > 0 && current < 3) current--; // ←
            else if (key == 77 && current < 2) current++;           // →
            else if (key == 72 && current == 3) current = 1;        // ↑
            else if (key == 80 && current < 3) current = 3;         // ↓
        } 
        else if (key == 13) { // Enter
            system("cls");
            if (current == 0) { 
                // Đăng nhập
                signIn();
                _getch();
            }
            else if (current == 1) { 
                // Đăng ký
                signUp();
                cout << "\n\n Press Enter to return Menu...";
                cin.ignore();
            }
            else if (current == 2) { 
                // Quên mật khẩu
                resetPassword();
                cout << "\n\n Press Enter to return Menu...";
                cin.ignore();
            }
            else if (current == 3) {
                cout << "Goodbye!\n";
                exit(0);
            }
        }
    }
}
