#include "graphics.h"
#include <iostream>

using namespace std;

// Constructs Graphics that has a Model m
Graphics::Graphics(Model* m) : m{m} {
    m->attach(this);
    dis = new Xwindow(800, 800);
    for (int i = 7; i >= 0; --i) {
        for (int j = 0; j < 8; ++j) {
            int w = 100;
            int h = 100;
            float jSize = j*100;
            float iSize = (7-i)*100;
            float xRem = (i + 1) % 2;
            float yRem = (j + 1) % 2; 
            if (xRem == yRem) {
                dis->fillRectangle(jSize, iSize, w, h, Xwindow::Black);
            } else {
                dis->fillRectangle(jSize, iSize, w, h, Xwindow::White);
            }
        }
    }
}

// Destructor for Graphics that detaches itself from Model and deletes Xwindow display
Graphics::~Graphics() {
    m->detach(this);
    delete dis;
}

// Uses Xwindow dis to display a graphical interface of the chess board
void Graphics::notify() {
    if (!dis) {
        dis = new Xwindow(800, 800);
    }
    char piece;
    for (int i = 7; i >= 0; --i) {
        for (int j = 0; j < 8; ++j) {
            piece = m->getState(i, j);
            int w = 100;
            int h = 100;
            float jSize = j*100;
            float iSize = (7-i)*100;
            
            float xRem = (i + 1) % 2;
            float yRem = (j + 1) % 2; 
            bool whiteTile;
            if (xRem == yRem) {
                whiteTile = false;
            } else {
                whiteTile = true;
            }

            if (piece == '_') {
                dis->fillRectangle(jSize, iSize, w, h, Xwindow::Black);
            }
            else if (piece == ' ') {
                dis->fillRectangle(jSize, iSize, w, h, Xwindow::White);
            }
            else if (piece == 'P') {
                if (whiteTile) {
                    dis->drawImage(jSize+12.5, iSize+25, "images/whiteWhitePawn.png");
                } else {
                    dis->drawImage(jSize+12.5, iSize+25, "images/whiteBlackPawn.png");
                }
            }
            else if (piece == 'p') {
                if (whiteTile) {
                    dis->drawImage(jSize+12.5, iSize+25, "images/blackWhitePawn.png");
                } else {
                    dis->drawImage(jSize+12.5, iSize+25, "images/blackBlackPawn.png");
                }
            }
            else if (piece == 'R') {
                if (whiteTile) {
                    dis->drawImage(jSize+12.5, iSize+25, "images/whiteWhiteRook.png");
                } else {
                    dis->drawImage(jSize+12.5, iSize+25, "images/whiteBlackRook.png");
                }
            }
            else if (piece == 'r') {
                if (whiteTile) {
                    dis->drawImage(jSize+12.5, iSize+25, "images/blackWhiteRook.png");
                } else {
                    dis->drawImage(jSize+12.5, iSize+25, "images/blackBlackRook.png");
                }
            }
            else if (piece == 'N') {
                if (whiteTile) {
                    dis->drawImage(jSize+12.5, iSize+25, "images/whiteWhiteKnight.png");
                } else {
                    dis->drawImage(jSize+12.5, iSize+25, "images/whiteBlackKnight.png");
                }
            }
            else if (piece == 'n') {
                 if (whiteTile) {
                    dis->drawImage(jSize+12.5, iSize+25, "images/blackWhiteKnight.png");
                } else {
                    dis->drawImage(jSize+12.5, iSize+25, "images/blackBlackKnight.png");
                }
            }
            else if (piece == 'B') {
                if (whiteTile) {
                    dis->drawImage(jSize+12.5, iSize+25, "images/whiteWhiteBishop.png");
                } else {
                    dis->drawImage(jSize+12.5, iSize+25, "images/whiteBlackBishop.png");
                }
            }
            else if (piece == 'b') {
                if (whiteTile) {
                    dis->drawImage(jSize+12.5, iSize+25, "images/blackWhiteBishop.png");
                } else {
                    dis->drawImage(jSize+12.5, iSize+25, "images/blackBlackBishop.png");
                }
            }
            else if (piece == 'Q') {
                if (whiteTile) {
                    dis->drawImage(jSize+12.5, iSize+25, "images/whiteWhiteQueen.png");
                } else {
                    dis->drawImage(jSize+12.5, iSize+25, "images/whiteBlackQueen.png");
                }
            }
            else if (piece == 'q') {
                if (whiteTile) {
                    dis->drawImage(jSize+12.5, iSize+25, "images/blackWhiteQueen.png");
                } else {
                    dis->drawImage(jSize+12.5, iSize+25, "images/blackBlackQueen.png");
                }
            }
            else if (piece == 'K') {
                if (whiteTile) {
                    dis->drawImage(jSize+12.5, iSize+25, "images/whiteWhiteKing.png");
                } else {
                    dis->drawImage(jSize+12.5, iSize+25, "images/whiteBlackKing.png");
                }
            }
            else if (piece == 'k') {
                if (whiteTile) {
                    dis->drawImage(jSize+12.5, iSize+25, "images/blackWhiteKing.png");
                } else {
                    dis->drawImage(jSize+12.5, iSize+25, "images/blackBlackKing.png");
                }
            }    
        }
   }
}
