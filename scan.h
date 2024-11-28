#ifndef SCAN_H
#define SCAN_H
#include "ability.h"
#include "link.h"

class Scan : public Ability {
    char id = 'S';
    public:
        void use(Link* link, Player* player) override;
};

#endif
