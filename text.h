#ifndef TEXT_H
#define TEXT_H
#include <iostream>
#include "observer.h"
#include "studio.h"

class Text : public Observer {
    Studio *studio;
    int id, otherId, abilities, sideLength;
    public:
        Text(Studio *studio, int id, int sideLength);
        void notify() override;

};

#endif
