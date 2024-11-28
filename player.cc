#include "player.h"


using namespace std;

Player::Player(Board* pre, int abilityCount, int downloadedV, int downloadedF): 
previous{pre}, abilityCount{abilityCount}, downloadedF{downloadedF}, downloadedV{downloadedV}{}

char Player::linkAt(int x, int y){
    for (Link link : links) {
        if (link.getX() == x && link.getY() == y) {
            return link.getName();
        }
    }
    return previous->linkAt(x, y);
}

void Player::moveLink(char name, int moveX, int moveY) {
    for (Link link : links) {
        if (link.getName() == name) {
            link.move(moveX, moveY);
        }
    }
}

void Player::addAbility(char newName, unique_ptr<Ability> newAbility) {
    for (auto& [id, ability] : abilities) {
        auto& [ptr, uses] = ability;
        if (newName == (*ptr).getName()) uses++;
    }
    abilities[newName] = {newAbility, 1} ;
}
