#include "studio.h"
#include "board.h"

void Studio::reset() {

}

void Studio::render() {

}

char Studio::getState(int row, int col) const {
    return theBoard->linkAt(row, col);
}





