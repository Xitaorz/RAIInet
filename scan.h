#ifndef SCAN_H
#define SCAN_H
#include "ability.h"
#include "link.h"

class Scan : public Ability {
    public:
        Scan() { id = 'S'; }
        void use(Player * opp){}
        void use(int col, int row, Player* player){}
        void use(Link* link1, Link* link2){}
        void use(Link* link, Player* player);
};

#endif
