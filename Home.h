#ifndef Home_h
#define Home_h
#include"Account.h"
class Home : public AccountManager{
    public:
        void showMenuUI();
        void drawBox(int x, int y, int w, int h);
        void gotoXY(int x, int y);
        void setColor(int color);
};
#endif
