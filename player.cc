#include "player.h"


using namespace std;

Player::Player(Board* pre, int id, int abilityCount, int downloadedV, int downloadedF): 
previous{pre}, id{id}, abilityCount{abilityCount}, downloadedF{downloadedF}, downloadedV{downloadedV}{}


void Player::addLink(int col, int row, int what, int strength, char name){
    links[name] = Link(col, row, what, strength, name);
}

void Player::addFireWall(int col, int row, char name) {
    fireWalls.emplace_back(Link(col, row, 2, 0, name));
}

char Player::linkAt(int col, int row){
    for (auto& [name, link] : links) {
        if (links[name].getCol() == col && links[name].getRow() == row) {
            return name;
        }
    }
    for (auto f : fireWalls) {
        if (f.getCol() == col && f.getRow() == row) {
            return f.getName();
        }
    }
    return previous->linkAt(col, row);
}

Link* Player::getLink(char name) {
    for (int i = 0; i < linkNum; ++i) {
        if (links[i].getName() == name) return &links[i];
    }
    return nullptr;
}

Link* Player::getAllLink(char name) {
    for (int i = 0; i < linkNum; ++i) {
        if (links[i].getName() == name) return &links[i];
    }
    for (auto& [id, opp]: opponents){
        Link* theLink = opp->getLink(name);
        if (theLink) {
            return theLink;
        }
    }
}

int Player::getId() {
    return id;
}

void Player::moveLink(char name, int moveC, int moveR) {
    Link* theLink = &links[name];
    theLink->move(moveC, moveR);
    int newC = theLink->getCol();
    int newR = theLink->getRow();
    //still needs update for four players' case
    if (abs(newR - theLink->initR) == 8) {
        download(name)
    }else if {
        //reach the server
    }
    for (auto [id, opp] : opponents){
        char target = opp->linkAt(newC, newR);
        Link* enemy = opp->getLink(target);
        if (opp->fireWalled(newC, newR)) {
            theLink->reveal();
        }
        if (enemy) {
            bool result = theLink->battle(enemy);
            if (result) {
                download(target);
                cerr << "You won the battle!" << endl;
            }
            else {
                opp->download(name);
                cerr << "You lost the battle!" << endl;
            }
        }
    }
}

void Player::download(char name) {
    Link* link = getLink(name);
    if (link) {
        if(link->isVirus()) downloadedV++;
        else downloadedF++;
        deleteLink(name);
    }else {
        link = getAllLink(name);
        if(link->isVirus()) downloadedV++;
        else downloadedF++;
        for (auto& [id, opp] : opponents) {
            opp->deleteLink(name);
        }      
    }
}

void Player::deleteLink(char name) {
    if (getLink(name)) {
        links.erase(name);
        linkNum--;
    }
}

void Player::addOpponent(int id, Player* opp) {
    opponents[id] = opp;
}

void Player::addAbility(char newName, unique_ptr<Ability> newAbility) {
    for (auto& [id, ability] : abilities) {
        auto& [ptr, uses] = ability;
        if (newName == ptr->getName()) {
            ability.second++;
            break;
        }
    }
    abilities[abilityCount + 1] = {move(newAbility), 1};
    abilityCount++;    
}

bool Player::fireWalled(int col, int row) {
    for (auto f : fireWalls) {
        if (f.getCol() == col && f.getRow() == row) return true;
    }
    return false;
}

void Player::useAbility(int id, int opp){   
    abilities[id].first->use(opponents[opp]);  
    abilities[id].second--;
    abilityCount--;       
}

void Player::useAbility(int id, int col, int row){
    abilities[id].first->use(col, row, this);
    abilities[id].second--;
    abilityCount--;
}

void Player::useAbility(int id, char name){
    abilities[id].first->use(getLink(name), this);
    abilities[id].second--;
    abilityCount--;
}

void Player::useAbility(int id, char name1, char name2){
    abilities[id].first->use(getLink(name1), getLink(name2));
    abilities[id].second--;
    abilityCount--;
}