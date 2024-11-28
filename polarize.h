#ifndef POLARIZE_H
#define POLARIZE_H
#include "ability.h"
#include "link.h"

class Polarize : public Ability {
    char id = 'P';
    public:
        void use(Link* , Player* player) override;
};

#endif
