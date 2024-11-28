#ifndef FIREWALL_H
#define FIREWALL_H
#include "ability.h"
#include "player.h"

class FireWall : public Ability {
    char id = 'F';
    public:
        void use(int col, int row, Player* player);
};

#endif
