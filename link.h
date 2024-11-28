#ifndef LINK_H
#define LINK_H
#include <vector>

using namespace std;

class Link{
    int x , y, what, strength;
    int step = 1;
    char name;
    bool visible;
    bool buffed;
    public:
        Link(int x, int y, int what, int strength, char name, bool visible = false, bool buffed = false);
        int getX();
        int getY();
        char getName();
        int getStrength();
        void move(int moveX, int moveY);
        void boost();

};

#endif