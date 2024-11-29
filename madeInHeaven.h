#ifndef MADEINHEAVEN_H
#define MADEINHEAVEN_H
#include "ability.h"
#include "link.h"

class MadeInHeaven : public Ability {
    char id = 'M';
    public:
        void use(Link* link1, Player* player) override;
};

#endif
