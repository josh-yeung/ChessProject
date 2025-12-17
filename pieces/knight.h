#ifndef __KNIGHT_H__
#define __KNIGHT_H__
#include "../pieces.h"

class Knight: public Piece {
    public:
        // construct a isWhite Knight piece at (let,number)
        Knight(int let, int number, bool white);
        // checks if the move is mechanically valid
        bool isValidMove(int x, int y) override;
        // returns 'N' for white and 'n' for black
        char getType() override;
        // returns the line of moves that can be made to a king at (x,y)
        vector<pair<int, int>*> kingLine(int x, int y) override;
};

#endif
