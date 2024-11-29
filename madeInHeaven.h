#ifndef MADEINHEAVEN_H
#define MADEINHEAVEN_H
#include "ability.h"
#include "link.h"

class MadeInHeaven : public Ability {
    public:
        MadeInHeaven() { id = 'M'; }
        void use(Player * opp){}
        void use(int col, int row, Player* player){}
        void use(Link* link1, Link* link2){}
        void use(Link* link1, Player* player);
};

#endif
