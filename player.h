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
        Board* previous;
        vector<Link> links{};
        int abilityCount; // # of unused abilities
        map <int, pair<unique_ptr<Ability>, int>> abilities;
        int downloadedV, downloadedF;       
    public:
        Player(Board* pre, int abilityCount, int downloadedV = 0, int downloadedF = 0){};
        char linkAt(int x, int y) override;
        void moveLink(char name, int moveX, int moveY);
        void addAbility(char newName, unique_ptr<Ability> newAbility);
};

#endif