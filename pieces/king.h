#ifndef __KING_H__
#define __KING_H__
#include "../pieces.h"

class King: public Piece {
    bool firstMove;
    bool castling;
    public:
        // constructs a King at (let,number) with player: isWhite, bool first is used to 
        // see if the piece has moved, and castling is used if the piece has castled
        King(int let, int number, bool white, bool first, bool castling);
        // checks if the move is mechanically valid
        bool isValidMove(int x, int y) override;
        // returns 'K' for white and 'k' for black
        char getType() override;
        // switches first to false
        void switchFirst();
        // returns castling
        bool getCastling();
        // returns first
        bool checkFirst();
        // sets castling to castle
        void setCastling(bool castle);
        // returns the possible moves for a king
        vector<pair<int, int>*> possibleMoves();
        // returns the line of moves that can be made to a king at (x,y)
        vector<pair<int, int>*> kingLine(int x, int y) override;
};

#endif
