#ifndef KINGCRIMSON_H
#define KINGCRIMSON_H
#include "ability.h"
#include "link.h"

class KingCrimson : public Ability {
    char id = 'K';
    public:
        void use(Link* link1, Link* link2) override;
};

#endif
