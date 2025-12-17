#ifndef __BISHOP_H__
#define __BISHOP_H__
#include "../pieces.h"

class Bishop: public Piece {
    public:
        // contructs an isWhite Bishop piece at (x,y)
        Bishop(int let, int number, bool white);
        // checks if the move is mechanically valid
        bool isValidMove(int x, int y) override;
        // returns 'P' if youre white and 'p' if you're black
        char getType() override;
        // returns the line to a king at (x,y)
        vector<pair<int, int>*> kingLine(int x, int y) override;
};

#endif
