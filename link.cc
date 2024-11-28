#include "link.h"

Link::Link (int x, int y, int what, int strength,  char name, bool visible, bool buffed):
x{x}, y{y}, what{what}, strength{strength}, name{name}, visible{visible}, buffed{buffed} {}

int Link::getX(){
    return x;
}

int Link::getY(){
    return y;
}

char Link::getName(){
    return name;
}

int Link::getStrength(){
    return strength;
}

void Link::move(int moveX, int moveY) {
    
    x += moveX * step;
    y += moveY * step;
    

}

void Link::boost(){
    step++;
}
