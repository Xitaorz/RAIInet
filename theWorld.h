#ifndef THEWORLD_H
#define THEWORLD_H
#include "ability.h"
#include <iostream>
#include "player.h"

class TheWorld : public Ability {
    public:
        
        TheWorld() { id = 'T'; }
        void use(int col, int row, Player* player){}
        void use(Link* link, Player* player = nullptr){}
        void use(Link* link1, Link* link2){}
        void use(Player* player);
};

#endif
