#ifndef LINK_H
#define LINK_H
#include <vector>

using namespace std;

class Link{
    int col, row, what, strength;
    int step = 1;
    char name;
    bool visible = false;
    public:
        Link(int col, int row, int what, int strength, char name);
        int getCol();
        int getRow();
        char getName();
        int getStrength();
        void move(int moveX, int moveY);
        void boost();
        void polarize();
        void reveal();
        bool isVirus();

};

#endif