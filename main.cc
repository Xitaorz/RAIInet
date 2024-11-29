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
    
    int playerNum;

    cout << "Enter the number of players: ";
    cin >> playerNum;

    s.startGame(playerNum);
    unique_ptr<Observer> textObs1 {new Text(&s, 1, 8)};
    unique_ptr<Observer> textObs2 {new Text(&s, 2, 8)};

    string command;

    while (cin >> command){ // Player input command
        cerr << "Curreent turn: Player " << s.whoseTurn() << endl;

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
        // } else if (command == "-graphics") {
        //     //add graphic observer
        //     s.attach();

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
            // TheWorld: "ability <T>" skips the opponent's next turn (player gets 2 turns)
        } else if (command == "ability") {
            int order, x, y;
            char which, whom, link1, link2;
            char temp;
            char abilityId;
            cin >> temp >> abilityId >> temp;
            switch (s.whichAbility(abilityId)) {
                case 1:
                    cin >> whom;
                    s.usePlayerAbilityType1(abilityId, whom);
                case 2:
                    cin >> x >> y;
                    s.usePlayerAbilityType2(abilityId, x, y);
                case 3:
                    cin >> which;
                    s.usePlayerAbilityType3(abilityId, which);
                case 4:
                    cin >> link1 >> link2;
                    s.usePlayerAbilityType4(abilityId, link1, link2);
            }
    }

            

        // WIN/LOSS CONDITIONS ----------------------------------------------------------
        int won = s.whoWon();
        int lost = s.whoLost();
        if (won != 0) {
            cout << "Congratulations! Player " <<  won << ", you've downloaded 4 data, you have won the game!" << endl;
        } if (lost != 0) {
            cout << "Sorry! Player " << lost << ", you've downloaded 4 viruses, you have lost the game!" << endl;
        }

    }
} // main
