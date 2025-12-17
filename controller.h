#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__
#include "model.h"
#include "text.h"
#include "ai.h"
#include "ai/level1.h"
#include <string>
using namespace std;

class Controller {
private:
    Model *model;
    bool isWhite = true; // True for white's turn, false for black's turn
    bool inGame; // True if a game is ongoing, false otherwise
    bool customSetup = false;
    bool endGame = false;
    AI* ai;
public:
    //destructor
    ~Controller();

    Controller(Model *m);

    // Initialize a new game
    void startGame(const string& whitePlayerType, const string& blackPlayerType);

    // Handle the move command
    bool move(const string& from, const string& to);

    // Handle move for ai
    bool move();

    // Return whos turn it is
    bool getWhite();

    // Setup mode
    void setup();

    // Concede the game
    void resign();

    // resets the game
    void resetGame();

    //Prints Scores when Ctrl-D is pressed
    void gameEnded();

    // Switch turns
    void switchTurn();

    //printsboard
    void printBoard();

    // will get the state of a game, if endgame true or false
    bool getEndGame();
};

#endif

