#ifndef ABILITY_H
#define ABILITY_H
#include <vector>


using namespace std;

//forward declaration
class Player;
class Link;

class Ability{
    protected:
        char id;
    public:
        virtual ~Ability() = 0;
        virtual void use();
        virtual void use(Player * opp);
        virtual void use(int col, int row, Player* player);
        virtual void use(Link* link, Player* player = nullptr);
        virtual void use(Link* link1, Link* link2);
        char getName();

};

#endif
