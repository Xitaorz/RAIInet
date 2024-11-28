#ifndef ABILITY_H
#define ABILITY_H
#include <vector>
#

using namespace std;

class Ability{
    char name;
    Board* board;
    public:
        virtual ~Ability() = 0;
        virtual void use();
        void getName();

};

#endif