#ifndef LINKBOOST_H
#define LINKBOOST_H
#include <vector>
#include "ability.h"

using namespace std;

class LinkBoost : public Ability{
    char id = 'L';
    Link* theLink;
    public:
        void use(Link* link);

};

#endif