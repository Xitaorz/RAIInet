#ifndef POLARIZE_H
#define POLARIZE_H
#include "ability.h"
#include "link.h"

class Polarize : public Ability {
    public:
        Polarize() { id = 'P'; }
        void use(Player * opp){}
        void use(int col, int row, Player* player){}
        void use(Link* link1, Link* link2){}
        void use(Link* link, Player* player);
};

#endif
