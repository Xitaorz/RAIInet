#include "player.h"


using namespace std;

Player::Player(Board* pre, int id): 
previous{pre}, id{id}{}


void Player::addLink(int col, int row, int what, int strength, char name){
    if (name == 'S') server.emplace_back(make_unique<Link>(col, row, what, strength, name));
    else links.emplace(name, new Link(col, row, what, strength, name));   
}

void Player::addFireWall(int col, int row, char name) {
    fireWalls.emplace_back(make_unique<Link>(col, row, 2, 0, name));
}

char Player::linkAt(int col, int row){
    for (auto& [name, link] : links) {
        if (link->getCol() == col && link->getRow() == row) {
            return name;
        }
    }
    for (auto& f : fireWalls) {
        if (f->getCol() == col && f->getRow() == row) {
            return f->getName();
        }
    }
    for (auto& s : server) {
        if (s->getCol() == col && s->getRow() == row) {
            return s->getName();
        }
    }
    return previous->linkAt(col, row);
}

Link* Player::getLink(char n) {
    for (auto& [name, link] : links) {
        if (n == name) return link.get();
    }
    return nullptr;
}

Link* Player::getAllLink(char name) {
    Link* target = getLink(name);
    if (target) return target;
    for (auto& [id, opp]: opponents){
        Link* theLink = opp->getLink(name);
        if (theLink) {
            return theLink;
        }
    }
    throw;
}

int Player::getId() {return id;}

int Player::getAbilityCount(){return abilityCount;}

int Player::getDownloadedF(){return downloadedF;}

int Player::getDownloadedV(){return downloadedV;}

bool Player::moveLink(char name, int moveC, int moveR) {
    Link* theLink = links[name].get();
    if(theLink->move(moveC, moveR)) return true;
    int newC = theLink->getCol();
    int newR = theLink->getRow();

    //reached the border
    if (abs(newR - theLink->getInitR()) == 8) {
        download(name);
    }


    for (auto [id, opp] : opponents){
        char target = opp->linkAt(newC, newR);
        Link* enemy = opp->getLink(target);


        //undo the move if enemy is invincible
        if (enemy && enemy->isInvincible()) {
            cerr << "The target link is invincible" << endl;
            theLink->move(-moveC, -moveR);
        }

        //reveal the link if it steps on a firewall
        if (opp->fireWalled(newC, newR)) {
            theLink->reveal();
        }

        //reached the opp's server
        else if (target == 'S'){
            opp->download(name);
        }

        //encountered a link
        if (enemy != nullptr) {
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
    return false;
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
        auto ptr = ability.first.get();
        if (newName == ptr->getName()) {
            ability.second++;
            abilityCount++;  
            return;
        }
    }
    abilities[abilityCount + 1] = {move(newAbility), 1};
    abilityCount++;    
}

bool Player::fireWalled(int col, int row) {
    for (auto& f : fireWalls) {
        if (f->getCol() == col && f->getRow() == row) return true;
    }
    return false;
}

void Player::freeze() {
    freezed++;
}

bool Player::isFreezed() {
    if (freezed > 0) {
        freezed--;
        return true;
    }
    else return false;
}

int Player::checkAbilityType(int id) {
    char name = (abilities[id].first)->getName();
    if (name == 'T') return 1;
    else if (name == 'F') return 2;
    else if (name == 'L' || name == 'P' || name == 'S' || name == 'M') return 3;
    else return 4;
    


}

//case 1
void Player::useAbility(int abilityId, int opp){
    abilities[abilityId].first->use(opponents[opp]);  
    abilities[abilityId].second--;
    abilityCount--;       
}

void Player::useAbility(int abilityId, int col, int row){
    abilities[abilityId].first->use(col, row, this);
    abilities[abilityId].second--;
    abilityCount--;
}

void Player::useAbility(int abilityId, char name){
    (abilities[abilityId].first)->use(getAllLink(name), this);
    abilities[abilityId].second--;
    abilityCount--;
}

void Player::useAbility(int abilityId, char name1, char name2){
    abilities[abilityId].first->use(getLink(name1), getLink(name2));
    abilities[abilityId].second--;
    abilityCount--;
}

void Player::printLinks(int id){
    if (id + 1 == this->id){
        int i = 0;
        for (auto& [name, link] : links){
            cout << link->getName() << ": " << link->getType() << link->getStrength() << ' ';
            if (i == 3) cout << endl;
            i++;
        }
    }else {
        int i = 0;
        for (auto& [name, link] : links){
            if (link->isVisible()){
                cout << link->getName() << ": " << link->getType() << link->getStrength()<< ' ';
            }else{
                cout << link->getName() << ": " << "? " ;
            }
            
            if (i == 3) cout << endl;
            i++;
        }
    }
    cout << endl;
     
}

void Player::printAbilities(){
    for (auto& [abilityId, ability] : abilities) {
        auto ptr = ability.first.get();
        cout << "ID: " << abilityId << ": " << ptr->getName() << " uses: " << ability.second << endl;
    }
}




