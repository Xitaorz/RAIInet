#include "text.h"
#include  <iostream>

using namespace std;

Text::Text(Studio *studio, int id, int sideLength):
id{id}, studio{studio}, sideLength{sideLength}{
    studio->attach(this);
    if (id == 1) otherId = 2;
    else otherId = 1;
}

void Text::notify () {
    cout << "Player 1" << endl;
    cout << "Downloaded: ";
    studio->printDownloaded(id);
    cout << "Abilities: ";
    studio->printPlayerAbilityCount(id);
    studio->printLinks(id);
    for (int j = 0; j < sideLength; ++j) {
        cout << '=';
    }
    cout << endl;
    for (int i = 0; i < sideLength; ++i) {
        for (int j = 0; j < sideLength; ++j) {
            cout << studio->getState(j, i);
        }
        cout << endl;
    }
    for (int j = 0; j < sideLength; ++j) {
        cout << '=';
    }
    cout << endl;
    cout << "Player " << otherId << ':' << endl;
    cout << "Downloaded: ";
    studio->printDownloaded(otherId);
    cout  << "Abilities: ";
    studio->printPlayerAbilityCount(otherId);
    studio->printLinks(otherId);
}
