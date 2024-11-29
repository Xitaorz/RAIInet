#ifndef DOWNLOAD_H
#define DOWNLOAD_H
#include "ability.h"
#include "player.h"

class Download : public Ability {
    public:
        Download() { id = 'D'; }
        void use(Link* link1, Link* link2) {}

        void use(Player* opp) {}

        void use(int col, int row, Player* player) {}

        void use(Link* link, Player* player);   
};

#endif
