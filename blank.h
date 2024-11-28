#ifndef BLANK_H
#define BLANK_H
#include <iostream>
#include "board.h"

class Blank : public Board {
    public:
        //No links detected
        //Returns '.'
        char linkAt(int x, int y);
};

#endif