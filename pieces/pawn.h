#ifndef __PAWN_H__
#define __PAWN_H__
#include "../pieces.h"

class Pawn: public Piece {
    bool firstMove;
    pair<int, int> enPassant = {-1,-1};
    public:
        // constructs a Pawn at (let,number) with player: isWhite, bool first is used to 
        // see if the piece has moved
        Pawn(int let, int number, bool white, bool first);
        // checks if the move is mechanically valid
        bool isValidMove(int x, int y) override;
        // returns 'P' for white and 'p' for black
        char getType() override;
        // switches first to false
        void switchFirst();
        // checks if the piece is moveing diagonally because 
        // a pawn can only take a peice if it moves diagonally
        bool takingPiece(int x, int y);
        // returns first
        bool checkFirst();
        // sets enPassant to [x,y]
        void setEnPassant(int x, int y);
        // returns enPassant
        pair<int,int> getEnPassant();
        // returns the line of moves that can be made to a king at (x,y)
        vector<pair<int, int>*> kingLine(int x, int y) override;
};

#endif
