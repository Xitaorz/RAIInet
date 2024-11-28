#include <iostream>
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
    unique_ptr<Board> board {new Blank};

    Studio* s{board};

    string command;

    vector<Observer*> observers;
    
    s.gameboard() = make_unique<Player>(s.gameboard(), 1 );

    while (std::cin >> command) {
        if (command == "render" ) {
        s.render();
        }
        else if (command == "animate") {
        int n;
        std::cin >> n;
        s.animate(n);
        }
        else if (command == "reset") {
        s.reset();
        }
        else if (command == "filledbox") {
        int top, bottom, left, right;
        char what;
        std::cin >> top >> bottom >> left >> right >> what;
        s.picture() = new FilledBox{s.picture(), top, bottom, left, right, what};     
        }
        else if (command == "blinkingbox") {
        int top, bottom, left, right;
        char what;
        std::cin >> top >> bottom >> left >> right >> what;
        s.picture() = new BlinkingBox{s.picture(), top, bottom, left, right, what};  
        }
        else if (command == "movingbox") {
        int top, bottom, left, right;
        char what, dir;
        std::cin >> top >> bottom >> left >> right >> what >> dir;
        s.picture() = new MovingBox{s.picture(), top, bottom, left, right, what, dir};  
        }
        else if (command == "maskbox") {
        int top, bottom, left, right;
        char what;
        std::cin >> top >> bottom >> left >> right >> what;
        s.picture() = new MaskBox{s.picture(), top, bottom, left, right, what};  
        }
        else if (command == "addtext") {
        int top, bottom, left, right;
        std::cin >> top >> bottom >> left >> right;
        observers.emplace_back(new Text{&s, top, bottom, left, right});
        }
        else if (command == "addgraphics") {
        int top, bottom, left, right;
        std::cin >> top >> bottom >> left >> right;
        observers.emplace_back(new Graphic{&s, top, bottom, left, right});
        } // if
    } // while
    for (auto it : observers) {
        s.detach(it);
        delete it;
    }
} // main
