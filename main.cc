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
#include "text.h"
#include "graphics.h"
#include "observer.h"

using namespace std;        

int main () {

    // INITIALIZATION ----------------------------------------------------------------
    // Board setup (concrete subject)
    unique_ptr<Board> board {new Blank};

    Studio s{board.get()};

    vector<Observer*> observers;
    
    char playerNum;

    cout << "Enter the number of players: ";
    cin >> playerNum;
    
    s.startGame(playerNum);
    unique_ptr<Observer> textObs1 {new Text(&s, 1, 8)};
    //unique_ptr<Observer> textObs2 {new Text(&s, 2, 8)};

    string command;
    cerr << "please enter the link setup for player1" << endl;
    while(cin>>command) {
        if (command == "-link1"){
            // Get input file for link tokens
            string fileName;
            if (cin >> fileName) {
                if (s.addPlayerLinks(fileName, 0)) return 1;
                break;
            } else {
                cerr << "Error: Missing file name for link tokens" << endl;
                return 1;
            }
        }
   }
   

    cerr << "please enter the link setup for player2" << endl;
    while(cin>>command) {
        if (command == "-link2"){
            // Get input file for link tokens
            string fileName;
            if (cin >> fileName) {
                if (s.addPlayerLinks(fileName, 1)) return 1;
                break;
            } else {
                cerr << "Error: Missing file name for link tokens" << endl;
                return 1;
            }
        }
    }
    

    cerr << "please enter the ability setup for player1" << endl;
    while(cin>>command) {      
        if(command == "-ability1") {
            string abilities;
            cin >> abilities;
            s.addPlayerAbilities(abilities, 0);
            break;
        }
   }

    cerr << "please enter the ability setup for player2" << endl;
    while(cin>>command) {
        if(command == "-ability2") {
            string abilities;
            cin >> abilities;
            s.addPlayerAbilities(abilities, 1);
            break;
        }
   }
    cout << "=======================" << endl;
    cout << "current Player: Player" << s.whoseTurn() + 1 << endl;
    cout << "=======================" << endl;

    ifstream f{};
    while (f >> command || cin >> command){ // Player input command
        // TODO: check implementation & ensure functional display
        // } else if (command == "-graphics") {
        //     //add graphic observer
        //     s.attach();
        if (f.eof()){
            f.close();
        }
        if (s.jumpPlayer()) {
                cerr << "Player " << s.whoseTurn() + 1 << " is jumped due to The World" << endl;
                s.turnOver();
                cout << "=======================" << endl;
                cout << "current Player: Player" << s.whoseTurn() + 1 << endl;
                cout << "=======================" << endl;         
                continue;
            }
        // INTERACTIVE COMMANDS ---------------------------------------------------------

        // "move a <dir>" moves the link 'a' in the direction 'dir'
            // a has to be a link the currrent player controls
            // dir can be 'U', 'D', 'L', or 'R'
        if (command == "move") {
            
            char linkId, dir;
            cin >> linkId;
            cin >> dir;
            while(s.movePlayer(linkId, dir)){
                cin >> command;
                cin >> linkId;
                cin >> dir;
            }
            s.notifyObservers();
            
        
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
            int x, y;
            char which, whom, link1, link2;
            char cAbilityId;
            cin >> cAbilityId;
            int abilityId = cAbilityId - '0';
            int whichType = s.whichAbility(cAbilityId);
            switch (whichType) {
                case 1:
                    cin >> whom;
                    s.usePlayerAbilityType1(abilityId, whom - '0');
                    break;
                case 2:
                    cin >> x >> y;
                    s.usePlayerAbilityType2(abilityId, x, y);
                    break;
                case 3:
                    cin >> which;
                    s.usePlayerAbilityType3(abilityId, which);
                    break;
                case 4:
                    cin >> link1 >> link2;
                    s.usePlayerAbilityType4(abilityId, link1, link2);
                    break;
            }
            continue;

        }else if (command == "board"){
            s.notifyObservers();
            continue;
        }else if (command == "abilities"){
            s.printPlayerAbilities();
            continue;
        }else if (command == "sequence"){
            string filename;
            cin >> filename;
            f.open(filename);
            continue;
        }else if (command == "graphics"){
            unique_ptr<Graphics> graphic{new Graphics{&s}};
        }else if (command == "quit"){
            return 2;
        }else {
            cerr << "invalid command, try again"<< endl;
            continue;
        }

            

        // WIN/LOSS CONDITIONS ----------------------------------------------------------
        int won = s.whoWon();
        int lost = s.whoLost();
        if (won != 0) {
            cout << "Congratulations! Player " <<  won << ", you've downloaded 4 data, you have won the game!" << endl;
            return 0;
        }else if (lost != 0) {
            cout << "Sorry! Player " << lost << ", you've downloaded 4 viruses, you have lost the game!" << endl;
            return 0;
        }else{
            s.turnOver();
            cout << "=======================" << endl;
            cout << "current Player: Player" << s.whoseTurn() + 1 << endl;
            cout << "=======================" << endl;
        }

    }
} // main
