#ifndef FIREWALL_H
#define FIREWALL_H
#include "ability.h"
#include "player.h"

class FireWall : public Ability {
    public:
        FireWall() { id = 'F'; }
        void use() {}

        void use(Player* opp) {}
        void use(Link* link, Player* player = nullptr){}
        void use(Link* link1, Link* link2){}

        void use(int col, int row, Player* player) ;
};

#endif
