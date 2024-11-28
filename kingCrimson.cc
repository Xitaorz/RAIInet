#include "kingCrimson.h"

void KingCrimson::use(Link* link1, Link* link2) {
    int col1 = link2->getCol();
    int row1 = link2->getRow();
    int col2 = link1->getCol();
    int row2 = link1->getRow();
    link1->teleport(col1, row1);
    link2->teleport(col2, row2);
}