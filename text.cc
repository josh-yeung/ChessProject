#include "text.h"
#include <iostream>

using namespace std;

// Constructs Text that has a Model m
Text::Text(Model* m) : m{m} {
    m->attach(this);
}

// Destructor for Text that detaches itself from Model
Text::~Text() {
    m->detach(this);
}

// prints current state of the board to screen
void Text::notify() {
   int row = 8;
   for (int i = 7; i >= 0; --i) {
    cout << row << " ";
    for (int j = 0; j < 8; ++j) {
        cout << m->getState(i, j);    
    }
    cout << endl;
    --row;
   }
    cout << endl << "  abcdefgh" << endl;
    cout << endl;
}
