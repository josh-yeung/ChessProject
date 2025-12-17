#ifndef __MODEL_H__
#define __MODEL_H__
#include "board.h"
#include "player.h"
#include "view.h"

class Model {
    vector<View*> observers;
    Board b;
    vector<vector<char>> display;
    Player white;
    Player black;
public:
    Model();
    ~Model();
    
    // calls board.Checkmate()
    bool isCheckmate(bool isWhite);
    
    // used to check stalemate
    bool isStalemate();
    
    // returns whether or not a player is an AI
    bool getPlayer(bool isWhite);
    
    // attaches an observer
    void attach(View* observer);
    
    // detaches an observer
    void detach(View* observer);
    
    // returns the stateof the board
    const char getState(int x, int y) const;

    void notifyObservers() const;
    
    // returns the board stored in model
    Board* getBoard();
    
    // takes a set of coordinates and a set of move coordinates and calls isValidMove in board 
    bool move(int let, int num, int moveLet, int moveNum, bool isWhite);
    
    // increases the score for a player
    void increaseScore(float increase, bool isWhite);
    
    // initizes players to human or ai
    void initializePlayers(const string& player1, const string& player2);
    
    // calls board.Check() to see if a player is in check
    bool check(bool isWhite);
    
    // updates the display vector given a peice and its move coordinates
    void displayUpdate(int let, int num, Piece* p);
    
    // updates the display at (let,num)
    void displayUpdate(int let, int num);
    
    // updates display
    void displayUpdate();
    
    // checks if a pawn is on the last opposing row, and convers the piece to a Queen
    Piece* pawnPromotion(Piece* p);
    
    // increses moveCounter in board
    void incMoveCounter();
    
    // returns the moveCounter in board
    int getMoveCounter();
    
    // returns the score
    int getScore(bool isWhite);
    
    // clears the board
    void resetBoard(); // Clears the pieces on the board
};


#endif
