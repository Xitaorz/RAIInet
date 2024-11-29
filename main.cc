#include <iostream>
#include <fstream>
#include <memory>
#include <utility>
#include <vector>
#include "studio.h"
#include "board.h"
#include "blank.h"
#include "subject.h"
#include "link.h"
#include "player.h"
#include "ability.h"
#include "linkBoost.h"
#include "polarize.h"
#include "firewall.h"
#include "scan.h"
#include "download.h"

using namespace std;        

int main () {

    // INITIALIZATION ----------------------------------------------------------------
    // Board setup (concrete subject)
    unique_ptr<Board> board {new Blank};

    Studio s{move(board)};

    vector<Observer*> observers;
    
    vector<Player*> players;
    int playerNum;

    cout << "Enter the number of players: ";
    cin >> playerNum;
    for (int i = 0; i < playerNum; ++i) {
        auto newPlayer = make_unique<Player>(s.gameboard(), 1);
        players[i] = newPlayer.get();
        s.gameboard() = move(newPlayer);
    }

    for (int i = 0; i < playerNum; ++i) {
        for (int j = 0; j < playerNum; ++j){
            if ( i != j) players[i]->addOpponent(j, players[j]); 
        }   
    }
    
    int turn;
    string command;

    while (cin >> command){ // Player input command
        cerr << "Curreent turn: " << turn << endl;

        // SETUP ABILITIES --------------------------------

        // Specifies abilities for player 1
            // Default: "LFDSP"
        if(command == "-ability1") {
            string abilities;
            cin >> abilities;
            s.addPlayerAbilities(abilities, 1);

            
        
        // Specifies abilities for player 2
            // Default: "LFDSP"
        } else if (command == "-ability2"){
            string abilities;
            cin >> abilities;
            s.addPlayerAbilities(abilities, 2);



        //SETUP LINKS--------------------------------------------------------------

        // Specifies link tokens for player 1
        }else if (command == "-link1"){
            // Get input file for link tokens
            string fileName;
            if (cin >> fileName) {
                if (s.addPlayerLinks(fileName, 1)) return 1;
            } else {
                cerr << "Error: Missing file name for link tokens" << endl;
                return 1;
            } 

        // Specifies link tokens for player 2
        }else if (command == "-link2"){
            // Get input file for link tokens
            string fileName;
            if (cin >> fileName) {
                if (s.addPlayerLinks(fileName, 2)) return 1;
            } else {
                cerr << "Error: Missing file name for link tokens" << endl;
                return 1;
            }

        // Specifies link tokens for player 3
        }else if (command == "-link3"){
            // Get input file for link tokens
            string fileName;
            if (cin >> fileName) {
                if (s.addPlayerLinks(fileName, 2)) return 1;
            } else {
                cerr << "Error: Missing file name for link tokens" << endl;
                return 1;
            }
        
        // Specifies link tokens for player 4
        }else if (command == "-link4"){
            // Get input file for link tokens
            string fileName;
            if (cin >> fileName) {
                if (s.addPlayerLinks(fileName, 2)) return 1;
            } else {
                cerr << "Error: Missing file name for link tokens" << endl;
                return 1;
            }




        // TODO: check implementation & ensure functional display
        } else if (command == "-graphics") {
            //add graphic observer
            s.attach();

        // INTERACTIVE COMMANDS ---------------------------------------------------------

        // "move a <dir>" moves the link 'a' in the direction 'dir'
            // a has to be a link the currrent player controls
            // dir can be 'U', 'D', 'L', or 'R'
        } else if (command == "move") {
            char linkId, dir;
            cin >> linkId;
            cin >> dir;
            while(s.movePlayer(linkId, dir)){
                cin >> linkId;
                cin >> dir;
            }
            
        
        // "ability <N>" uses ability with ID 'N', with some abilities requiring additional info
            // Linkboost: "ability <L> b" attaches linkboost to link 'b'
            // Firewall: "ability <F> x y" creates a firewall at position (x, y)
            // Download: "ability <D> b" immediately downloads the opponent's link 'b'
            // Polarize: "ability <P> b" changes the targeted data to a virus or vice versa for link 'b'
            // Scan: "ability <S> b" reveals the type and strength of any opponent link 'b'
            // MadeInHeaven: "ability <M> b: attaches permanent ability protection on link 'b'
            // KingCrimson: "ability <K> b x y" moves link 'b' to position (x, y)
            // Jumper: "ability <J>" skips the opponent's next turn (player gets 2 turns)
        } else if (command == "ability") {
            int order, x, y;
            char link;
            cin >> order;
            char ability_id = s.whoseTurn();

            if(ability_id ==''){
                cerr << "Error: invalid ability ID" << endl;
            }
            else if (find(longTermLinkAbilitiesId.begin(), longTermLinkAbilitiesId.end(), ability_id) != longTermLinkAbilitiesId.end()) {
                game.playerAbilityToPlayerLink(turn, link, ability_id);
            }
            else if (find(attackAbilitiesId.begin(), attackAbilitiesId.end(), ability_id) != attackAbilitiesId.end()) {
                game.playerAbilityToOpponentLink(turn, link, ability_id);
            }
            else if (ability_id =='F') { // Firewall
                cin >> x >> y ;
                
                game.Board() = new FirewallDecorator(game.Board(), turn, numPlayers, x, y, game.getLinkPositions());
            }
            else if (ability_id == 'J') { // Jumper
                turn++;
                continue; // skips to next iteration immediately
            }
            else if(ability_id == 'K') { // KingCrimson
                cin >>link>> x >> y ;
                game.Board() = new KingCrimsonDecorator(game.Board(), link, x, y, game.getLinkPositions());
            }

        // Display abilities possessed by the current player
            // Display ability ID (1 - 8)
            // Display if ability has been used
        } else if (command == "abilities") {
            game.displayAbilities(turn);

        // Display the current board to the graphics section
        } else if (command == "board") {
            gameboard.render();

        // Exit the game
        } else if (command == "quit" || command == "q") {
            cout << "Game exited successfully!" << endl;
            return 0;
        } else {
            cerr << "Error: invalid command. Please try again. " << endl;
        }

        // WIN/LOSS CONDITIONS ----------------------------------------------------------
        if (game.findWinner() != 0) {
            cout << "Congratulations! Player " <<  game.findWinner() << ", you've downloaded 4 data, you have won the game!" << endl;
        } if (game.findLoser() != 0) {
            cout << "Sorry! Player " << game.findLoser() << ", you've downloaded 4 viruses, you have lost the game!" << endl;
        }

    }
} // main
