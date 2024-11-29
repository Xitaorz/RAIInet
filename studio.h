#ifndef STUDIO_H
#define STUDIO_H
#include <iostream>
#include <memory>
#include <utility>
#include <vector>
#include "subject.h"
#include "link.h"
#include "player.h"
#include "ability.h"
#include "linkBoost.h"
#include "polarize.h"
#include "firewall.h"
#include "scan.h"
#include "download.h"

using namespace std;

class Studio : public Subject{
    unique_ptr<Board> theBoard;

    public:
        // Studio ctor
        explicit Studio(unique_ptr<Board> board) : theBoard(move(board)) {}

        // don't need dtor cuz unique pointer being used
        
        // Accessor to theBoard
        unique_ptr<Board> gameboard();

        // Display Methods ----------------------------------------------------
        void reset();
        // renders next move
        void render();

        // calls the cell at the location on the board
        char getState(int row, int col) const override;

        
};


#endif
