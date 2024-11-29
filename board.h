#ifndef BOARD_H
#define BOARD_H
#include <iostream>

class Board {
    //In case we want to make this game to gain more flexibility
    //int Length;
    //int Width;
    public:
        virtual ~Board();
        virtual char linkAt(int x, int y) = 0;
};

#endif