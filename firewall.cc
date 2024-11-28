#include "firewall.h"

void FireWall::use(int col, int row, Player* player) {
    char name;
    int id = player->getId();
    if (id == 1) name = 'm';
    else name = 'w';
    player->addFireWall(col, row, name);
}