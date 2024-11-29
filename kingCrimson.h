#ifndef KINGCRIMSON_H
#define KINGCRIMSON_H
#include "ability.h"
#include "link.h"

class KingCrimson : public Ability {
    public:
        KingCrimson() { id = 'K'; }
        void use(Player * opp){}
        void use(int col, int row, Player* player){}
        void use(Link* link, Player* player = nullptr){}
        void use(Link* link1, Link* link2);
};

#endif
