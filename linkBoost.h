#ifndef LINKBOOST_H
#define LINKBOOST_H
#include <vector>
#include "ability.h"
#include "link.h"

using namespace std;

class LinkBoost : public Ability{
    public:
        LinkBoost() { id = 'L'; }
        void use(Player * opp){}
        void use(int col, int row, Player* player){}
        void use(Link* link1, Link* link2){}
        void use(Link* link, Player* player);

};

#endif
