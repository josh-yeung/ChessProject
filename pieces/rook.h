#ifndef __ROOK_H__
#define __ROOK_H__
#include "../pieces.h"

class Rook: public Piece {
    bool firstMove;
    public:
        // constructs a Rook at (let,number) with player: isWhite, bool first is used to 
        // see if the piece has moved
        Rook(int let, int number, bool white, bool first);
        // checks if the move is mechanically valid
        bool isValidMove(int x, int y) override;
        // returns 'R' for white and 'r' for black
        char getType() override;
        // swtiches first ro false
        void switchFirst();
        // returns first
        bool checkFirst();
        // returns the line of moves that can be made to a king at (x,y)
        vector<pair<int, int>*> kingLine(int x, int y) override;
};

#endif
