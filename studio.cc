#include "studio.h"
#include "board.h"

void Studio::reset() {

}

void Studio::render() {

}

char Studio::getState(int row, int col) const {
    return theBoard->linkAt(row, col);
}


void Studio::addPlayerAbilities(string abilities, int id) {
    if(abilities ==""){ 
                players[id]->addAbility('L', make_unique<LinkBoost>());
                players[id]->addAbility('F', make_unique<FireWall>()); 
                players[id]->addAbility('D', make_unique<Download>()); 
                players[id]->addAbility('S', make_unique<Scan>()); 
                players[id]->addAbility('P', make_unique<Polarize>());                
            }else{
                for(int i = id; i < abilities.length(); i++){
                    if(abilities[i] == 'L'){
                        players[id]->addAbility('L', make_unique<LinkBoost>());
                    }
                    else if(abilities[i] == 'F'){
                        players[id]->addAbility('F', make_unique<FireWall>());
                    }
                    else if(abilities[i] == 'D'){
                        players[id]->addAbility('D', make_unique<Download>());
                    }
                    else if(abilities[i] == 'S'){
                        players[id]->addAbility('S', make_unique<Scan>()); 
                    }
                    else if(abilities[i] == 'P'){
                        players[id]->addAbility('P', make_unique<Polarize>());
                    }
                    else if(abilities[i] == 'T'){
                        players[id]->addAbility('T', make_unique<TheWorld>()); 
                    }
                    else if(abilities[i] == 'K'){
                        players[id]->addAbility('K', make_unique<KingCrimson>()); 
                    }
                    else if(abilities[i] == 'M'){
                        players[id]->addAbility('M', make_unique<MadeInHeaven>()); 
                    }
                }
            }
}

bool Studio::addPlayerLinks(string filename, int id) {

    ifstream file{filename};

    // TODO: use try catch for error handling???
    if (!file.is_open()) {
        cerr << "Error: Could not open file: " << filename << endl;
        return true;
    }

    // Assign link tokens to the player
    vector<string> linkTokens;
    string token;
    int i = 0;
    string linkNames;
    if (id == 1) linkNames = "abcdefgh";
    else if (id == 2) linkNames = "ABCDEFGH";
    else if (id == 3) linkNames = "stuvwxyz";
    else linkNames = "STUVWXYZ";
    
    while (i < 8 && file >> token) {
        linkTokens.emplace_back(token);
        int type;                   
        if (token[id] == 'D') type = 0;
        else type = 1;
        int strength = token[1] - '0'; // convert char to int using ascii
        if(i == 3 || i == 4){
            players[id]->addLink(i, 0, -1, 5, 'S');
            players[id]->addLink(i, 1, type, strength, linkNames[i]);
        }else {
            players[id]->addLink(i, 0, type, strength, linkNames[i]);
        }
        i++;
    }

    if (linkTokens.empty()){
        cerr << "Error: No tokens found in file. Random values initialized." << endl;
        int strength = (std::rand() % 4) + 1;
        int type = std::rand() % 2;
        for(int i = 0; i < 8; ++i){
            strength = (strength + i) % 4 + 1;
            type = (type + i) % 2 + 1;
            if(i == 3 || i == 4){
                players[id]->addLink(i, 0, -1, 5, 'S');
                players[id]->addLink(i, 1, type, strength, linkNames[i]);  
            }else {
                players[id]->addLink(i, 0, type, strength, linkNames[i]);
            }                           
        }
    }
    return false;

}


//return:
    //true -> something is wrong
    //false -> nothing is wrong
bool Studio::movePlayer(char link, char dir){
    for (int i = 0; i < playerNum; ++i) {
        if (players[i]->getLink(link)) {
            if (players[i]->isFreezed()){
                turn++;
                return false;
            }
            else {
                int moveCol = 0;
                int moveRow = 0;

                //check direction
                if (dir == 'u') {
                    moveRow = -1;
                }else if (dir == 'd'){
                    moveRow = 1;
                }else if (dir == 'l'){
                    moveCol = -1;
                }else{
                    moveCol= 1;
                }
                if(players[i]->moveLink(link, moveCol, moveRow)){
                    cerr << "Invalid move, try again" << endl;
                    return true;
                }else {
                    turn++;
                    return false;
                }
            }
        }
    }
    cerr << "Invalid Command, try again" << endl;
    return true;
}


int Studio::whoseTurn(){
    return turn % playerNum + 1;
}
