#include "player.h"


using namespace std;

Player::Player(Board* pre, int id, int abilityCount, int downloadedV, int downloadedF): 
previous{pre}, id{id}, abilityCount{abilityCount}, downloadedF{downloadedF}, downloadedV{downloadedV}{}

void Player::addLink(int col, int row, int what, int strength, char name){
    links[name] = {col, row, what, strength, name};
}

char Player::linkAt(int x, int y){
    for (int i = 0; i < linkNum; ++i) {
        if (links[i].getCol() == x && links[i].getRow() == y) {
            return links[i].getName();
        }
    }
    return previous->linkAt(x, y);
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
    return opponent->getLink(name);
}

int Player::getId() {
    return id;
}

void Player::moveLink(char name, int moveX, int moveY) {
    for (int i = 0; i < linkNum; ++i) {
        if (links[i].getName() == name) {
            links[i].move(moveX, moveY);
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
        opponent->deleteLink(name);
    }
}

void Player::deleteLink(char name) {
    links.erase(name);
    linkNum--;
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

void Player::useAbility(int id){   
    abilities[id].first->use(opponent);  
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