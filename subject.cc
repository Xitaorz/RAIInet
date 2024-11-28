#include "subject.h"
#include "observer.h"
#include <vector>

void Subject::attach( Observer* o ) {
    /*** FILL IN ***/
    observers.emplace_back(o);
}

void Subject::detach( Observer* o ) {
    /*** FILL IN ***/    
    for (auto it = observers.begin(); it != observers.end(); ++it) {
        if (*it == o) {
            observers.erase(it);
            break;
        }
    }
}

void Subject::notifyObservers() {
    /*** FILL IN ***/
    for (auto p: observers) p->notify();
}
