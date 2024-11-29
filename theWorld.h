#ifndef THEWORLD_H
#define THEWORLD_H
#include "ability.h"
#include "player.h"

class TheWorld : public Ability {
    char id = 'T';
    public:
        void use(Player* player) override;
};

#endif
