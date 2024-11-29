#ifndef STUDIO_H
#define STUDIO_H
#include <iostream>
#include <fstream>
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
#include "madeInHeaven.h"
#include "theWorld.h"
#include "kingCrimson.h"



using namespace std;

class Studio : public Subject{
    Board* theBoard;
    vector<unique_ptr<Player>> players;
    int playerNum = 0;
    int turn = 0;   
    public:
        // Studio ctor
        explicit Studio(Board* board) : theBoard(board) {}

        // don't need dtor cuz unique pointer being used
        
        // Accessor to theBoard
        unique_ptr<Board> gameboard();

        // Display Methods ----------------------------------------------------

        // calls the cell at the location on the board
        char getState(int row, int col) const override;

        void startGame(char PlayerNum);

        void addPlayerAbilities(string abilities, int id);

        bool addPlayerLinks(string filename, int id);

        bool movePlayer(char link, char dir);

        int whoseTurn();

        int whichAbility(char abilityId);

        void usePlayerAbilityType1(int abilityId, int opp);
        void usePlayerAbilityType2(int abilityId, int col, int row);
        void usePlayerAbilityType3(int abilityId, char name);
        void usePlayerAbilityType4(int abilityId, char name1, char name2);
        
        int whoWon();
        int whoLost();

        void printDownloaded(int id);
        void printPlayerAbilityCount(int id);
        void printLinks(int id);
        void printPlayerAbilities();
};


#endif
