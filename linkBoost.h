#ifndef LINKBOOST_H
#define LINKBOOST_H
#include <vector>
#include "ability.h"
#include "link.h"

using namespace std;

class LinkBoost : public Ability{
    char id = 'L';
    public:
        LinkBoost(); 
        void use(Link* link, Player* player) override;

};

#endif
