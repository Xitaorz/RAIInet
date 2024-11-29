#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "observer.h"
#include "studio.h"
#include "window.h"

// Graphics -- ConcreteObserver
class Graphics: public Observer {
    Studio *subject;
    int turn;
    
    // window dimensions
    const int width = 700;
    const int height = 700;

    // window dimensions details
    const int cellSize = 50;
    const int boarderSize = 5;
    const int boardSize = 8;

    const int boardWidth = cellSize * boardSize;
    const int boardHeight = cellSize * boardSize;

    // window object details
    Xwindow displayWin;
    const int pixels = 10;

  public:
    Graphics(Studio *subject); 
    ~Graphics();
    void notify() override;

  private:

    int getColour(char c);

};

#endif