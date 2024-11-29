#include "studio.h"
#include "board.h"


char Studio::getState(int row, int col) const {
    return theBoard->linkAt(row, col);
}

void Studio::startGame(char playN){
    int playerNumber = playN - '0';
    playerNum = playerNumber;
    for (int i = 0; i < playerNum; ++i) {    
        players.emplace_back(make_unique<Player>(theBoard, i + 1));
        theBoard = players[i].get();  
        cerr<< "added" << i << endl;
    }

    for (int i = 0; i < playerNum; ++i) {
        for (int j = 0; j < playerNum; ++j){
            if ( i != j) players[i]->addOpponent(j + 1, players[j].get()); 
        }   
    }
}


void Studio::addPlayerAbilities(string abilities, int id) {
    if(abilities ==""){ 
                players[id]->addAbility('L', make_unique<LinkBoost>());
                players[id]->addAbility('F', make_unique<FireWall>()); 
                players[id]->addAbility('D', make_unique<Download>()); 
                players[id]->addAbility('S', make_unique<Scan>()); 
                players[id]->addAbility('P', make_unique<Polarize>());                
            }else{
                for(int i = 0; i < abilities.length(); i++){
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
    if (id == 0) linkNames = "abcdefgh";
    else if (id == 1) linkNames = "ABCDEFGH";
    else if (id == 2) linkNames = "stuvwxyz";
    else linkNames = "STUVWXYZ";
    
    if (id == 0){
        while (i < 8 && file >> token) {
            linkTokens.emplace_back(token);
            int type;                   
            if (token[0] == 'D') type = 0;
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
    }else if (id == 1) {
        while (i < 8 && file >> token) {
            linkTokens.emplace_back(token);
            int type;                   
            if (token[0] == 'D') type = 0;
            else type = 1;
            int strength = token[1] - '0'; // convert char to int using ascii
            if(i == 3 || i == 4){
                players[id]->addLink(i, 7, -1, 5, 'S');
                players[id]->addLink(i, 6, type, strength, linkNames[i]);
            }else {
                players[id]->addLink(i, 7, type, strength, linkNames[i]);
            }
            i++;
        }
    }else if (id == 2) {
        while (i < 8 && file >> token) {
            linkTokens.emplace_back(token);
            int type;                   
            if (token[0] == 'D') type = 0;
            else type = 1;
            int strength = token[1] - '0'; // convert char to int using ascii
            if(i == 3 || i == 4){
                players[id]->addLink(0, i, -1, 5, 'S');
                players[id]->addLink(1, i, type, strength, linkNames[i]);
            }else {
                players[id]->addLink(0, i, type, strength, linkNames[i]);
            }
            i++;
        }
    }else if (id == 3) {
        while (i < 8 && file >> token) {
            linkTokens.emplace_back(token);
            int type;                   
            if (token[0] == 'D') type = 0;
            else type = 1;
            int strength = token[1] - '0'; // convert char to int using ascii
            if(i == 3 || i == 4){
                players[id]->addLink(7, i, -1, 5, 'S');
                players[id]->addLink(6, i, type, strength, linkNames[i]);
            }else {
                players[id]->addLink(7, i, type, strength, linkNames[i]);
            }
            i++;
        }
    }
    

    if (linkTokens.empty()){
        cerr << "No tokens found in file. Random values initialized." << endl;
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
    int id = whoseTurn();
    
    if (players[id]->getLink(link)) {
        if (players[id]->isFreezed()){
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
            if(players[id]->moveLink(link, moveCol, moveRow)){
                cerr << "Invalid move, try again" << endl;
                return true;
            }else {
                turn++;
                return false;
            }
        }
        
    }
    cerr << "Invalid Command, try again" << endl;
    return true;
}


int Studio::whoseTurn(){
    return turn % playerNum;
}

int Studio::whichAbility(char abilityId) {
    int playerId = whoseTurn();
    return players[playerId]->checkAbilityType(abilityId - '0');
}

void Studio::usePlayerAbilityType1(int abilityId, int opp){
    int playerId = whoseTurn();
    players[playerId]->useAbility(abilityId, opp);
}

void Studio::usePlayerAbilityType2(int abilityId, int col, int row){
    int playerId = whoseTurn();
    players[playerId]->useAbility(abilityId, col, row);
}

void Studio::usePlayerAbilityType3(int abilityId, char name){
    int playerId = whoseTurn();
    players[playerId]->useAbility(abilityId, name);
    
}

void Studio::usePlayerAbilityType4(int abilityId, char name1, char name2){
    int playerId = whoseTurn();
    players[playerId]->useAbility(abilityId, name1, name2);
}

int Studio::whoWon(){
    for (int i = 0; i < playerNum; ++i){
        if (players[i]->getDownloadedF() >= 4) return i;
    } 
     return 0; //nobody won
}

int Studio::whoLost(){
    for (int i = 0; i < playerNum; ++i){
        if (players[i]->getDownloadedV() >= 4) return i;
    } 
    return 0; //nobody won
}


void Studio::printDownloaded(int id){
    cout << players[id-1]->getDownloadedF() << "D " << players[id-1]->getDownloadedV() << "V" << endl;
}

void Studio::printPlayerAbilityCount(int id){
    cout << players[id-1]->getAbilityCount() << endl;
}

void Studio::printLinks(int id){
    players[id-1]->printLinks(whoseTurn()+1);
}

void Studio::printPlayerAbilities(){
    players[whoseTurn()]->printAbilities();
}
