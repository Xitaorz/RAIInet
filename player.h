#ifndef Player_H
#define Player_H
#include <vector>
#include <utility>
#include <memory>
#include <map>
#include "board.h"
#include "link.h"
#include "ability.h"


using namespace std;


class Player : public Board {
    protected:
        int id;
        Board* previous;
        map<char, Link> links{};
        int linkNum = 8;
        Player* opponent;
        //map<int, Player *> opponents;     //in case there are more than 2 players
        int abilityCount; // # of unused abilities
        map <int, pair<unique_ptr<Ability>, int>> abilities;
        int downloadedV, downloadedF;       
    public:
        Player(Board* pre, int id, int abilityCount = 0, int downloadedV = 0, int downloadedF = 0){};
        void addLink(int col, int row, int what, int strength, char name);
        char linkAt(int x, int y) override;
        Link* getLink(char name);
        Link* getAllLink(char name);
        int getId();
        void moveLink(char name, int moveX, int moveY);
        void download(char name);
        void deleteLink(char name);
        void addAbility(char newName, unique_ptr<Ability> newAbility);
        void useAbility(int id);                            // for abilities targeting the opponent
        void useAbility(int id, int col, int row);          // for abilities targeting a square
        void useAbility(int id, char name);                 // for abilities targeting a link
        void useAbility(int id, char name1, char name2);    // for abilities targeting two links
};

#endif
