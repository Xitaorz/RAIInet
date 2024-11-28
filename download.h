#ifndef DOWNLOAD_H
#define DOWNLOAD_H
#include "player.h"

class Download : public Ability {
    char id = 'D';
    public:
        void use(Link* link, Player* player) override;
};

#endif
