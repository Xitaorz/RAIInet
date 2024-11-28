#include "download.h"

void Download::use(Link* link, Player* player) {
    player->download(link->getName());
}
