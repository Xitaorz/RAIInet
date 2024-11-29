#include "graphics.h"

// Public Graphics ConcreteObserver Methods ------------------------------------

// Graphics ctor (attaches observer)
Graphics::Graphics(Studio *subject): 
    subject{subject}, displayWin{width, height} {

    subject->attach(this); // attach observer to studio subject

    // outer boarder lines
    displayWin.fillRectangle(0, 0, boardWidth + 2 * boarderSize, 
                             boarderSize, Xwindow::Black);  // Top border
    displayWin.fillRectangle(0, boardHeight + boarderSize, boardWidth + 2 * boarderSize, 
                             boarderSize, Xwindow::Black);  // Bottom border
    displayWin.fillRectangle(0, 0, boarderSize, 
                             boardHeight + 2 * boarderSize, Xwindow::Black); // Left border
    displayWin.fillRectangle(boardWidth + boarderSize, 0, boarderSize, 
                             boardHeight + 2 * boarderSize, Xwindow::Black); // Right border

    // inner grid lines
    for (int i = 1; i < boardSize; ++i) {
        displayWin.drawLine(boarderSize, boarderSize + i * cellSize, 
                            boarderSize + boardWidth, boarderSize + i * cellSize, Xwindow::Black);
        displayWin.drawLine(boarderSize + i * cellSize, boarderSize, 
                            boarderSize + i * cellSize, boarderSize + boardHeight, Xwindow::Black);
    }
}

// Graphics dtor (detaches observer)
Graphics::~Graphics() { subject->detach(this); }

// Notify display observers
void Graphics::notify() {
    // Display board as a grid of squares/rectangles

    // Inner board state
    for (int i = 0; i < 8; ++i) { // iterate through rows
        for (int j = 0; j < 8; ++j) { // iterate through columns
            if (!subject->getState(i, j)) {
                cout << "Error: Subject->getState is null." << endl;
                cout << "Current iteration: " << i << ", " << j << endl;
                return;
            }
            char c = subject->getState(i, j);
            displayWin.fillRectangle(boarderSize + j * cellSize, 
                                     boarderSize + i * cellSize, 
                                     cellSize, cellSize, getColour(c));

            // TODO: display D/V and strength on each cell, depending on visibility of the current Player (determined through current turn)
        }
    }
}

// Convert char to corresponding color value
int Graphics::getColour(char c) {
    if (c == 'S') return Xwindow::Green;             // Server ports
    if (c == '.') return Xwindow::White;             // Empty space
    if (c == 'w' || c == 'm') return Xwindow::Black; // Firewall
    if (c >= 'a' && c <= 'h') return Xwindow::Red;   // Player 1 links
    if (c >= 'A' && c <= 'Z') return Xwindow::Blue;  // Player 2 links
    return 1;
}