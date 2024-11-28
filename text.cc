#include "text.h"
#include  <iostream>

using namespace std;

Text::Text(Studio *studio, int id, int abilities, int sideLength):
studio{studio}, abilities{abilities}, sideLength{sideLength}{
    studio->attach(this);
    if (id == 1) otherId = 2;
    else otherId = 1;
}

void Text::notify () {
    cout << "Player " << id << ':' << endl;
    cout << "Downloaded: ";
    studio->printDownloaded(id);
    cout << endl << "Abilities: ";
    studio->printPlayerAbilityCount(id);
    cout << endl;
    studio->printLinks(id);
    for (int j = 0; j < sideLength; ++j) {
        cout << '=';
    }
    cout << endl;
    for (int i = 0; i < sideLength; ++i) {
        for (int j = 0; j < sideLength; ++j) {
            cout << studio->getState(i, j);
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
    cout << endl << "Abilities: ";
    studio->printPlayerAbilityCount(otherId);
    cout << endl;
    studio->printLinks(otherId);
}
