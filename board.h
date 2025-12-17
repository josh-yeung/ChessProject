#ifndef __BOARD_H__
#define __BOARD_H__
#include "pieceset.h"
#include "pieces.h"
#include "tempPiece.h"

class Board {
    PieceSet black;
    PieceSet white;
    int moveCounter = 0;
    // bool checkHelper(PieceSet * ps);
public:
    Board();
    ~Board();
    
    // this initlizes the piecesets for white and black in a default baord configuration
    void initDefaultBoard();
    
    // returns white
    PieceSet& getWhitePieces();
    
    // returns black
    PieceSet& getBlackPieces();
    
    // uses tempPiece data fields to contruct and add a new piece to player isWhite
    void addPiece(bool isWhite, tempPiece* tp);
    
    // uses the data fields inputted to contruct and add a new piece to the player isWhite
    void addPiece(char piece, int x, int y, bool isWhite);
    
    // removes the peice at coordinates (x,y) for the player isWhite
    void removePiece(bool isWhite, int x, int y);
    
    // checks if the move (x,y) is a valid move for Piece p, checking if the piece is doing a valid movement,
    // not jumping over other pieces, and if the move is putting the player in selfCheck
    bool isValidMove(int x, int y, Piece* p); 
    
    // this is a function used to see if a player is in selfCheck or Check
    bool check(bool isWhite);
    
    // this is used by check to run a repeated algorithm with different parameters
    bool checkHelper(PieceSet* ps1, PieceSet* ps2);
    
    // this is a function used to see if a player is in checkmate
    bool checkMate(bool isWhite);
    
    // used to see if there are any peices in between p and the spot it is moving to
    bool inBetween(int x, int y, Piece *p);
    
    // simulates a move and stores the original information of the peices effected in a vector of tempPieces
    vector<tempPiece *> simMove(int x, int y, Piece* p, bool isWhite);
    
    // reverts the simulated move
    void revertMove(vector<tempPiece *> pieces, Piece* p);
    
    // checks if the move a plater is trying to make is a valid castle move
    bool validCastle(int moveLet, int moveNum, Piece* p);
    
    // is called by validCastle to run the castle algorithm for different parameters
    bool castleHelper(int kMoveLet, int kMoveNum, int rMoveLet, int rMoveNum, Piece *king, Piece *rook, PieceSet* set);
    
    // is called by simMove to run the simulate move algorithm with different parameters
    vector<tempPiece *> simHelper(int mLet, int mNum, vector<tempPiece*> tp, PieceSet* set);
    
    // checks if the move made by the player is a valid en passant move
    bool enPassant(int x, int y, Piece* p, PieceSet* mySet, PieceSet* otherSet);
    
    // is called by enPassant to run the enPassant algorithm with different parameters
    bool enPassantHelper(int opLet, int opNum, int let, int num, char op, Piece *p, PieceSet* otherSet);
    
    //returns moveCounter
    int getMoveCounter();
    
    // increases moveCounter
    void incMoveCounter();
    
    // is a tailored simulate function for en passant
    vector<tempPiece *> enPassanSim(int opLet, int opNum, vector<tempPiece *> tp, PieceSet* otherSet);
    
    // sees if the king can move anywhere to but put out of check
    bool canKingMove(PieceSet* mySet, PieceSet* otherSet, Piece* king);
    
    // called to see if the setup mode conditions are met
    bool isValidBoard();
    
    // sees if a peice is able to move, sued for ai
    vector<pair<int,int>*> canPieceMove(PieceSet* mySet, Piece* p);
    
    // returns the line a piece can move to using a reference spot, used by ai
    vector<pair<int,int>*> moveLine(PieceSet* mySet, pair<int,int>* spot, Piece* p);
};  

#endif
