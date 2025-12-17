#ifndef __QUEEN_H__
#define __QUEEN_H__
#include "../pieces.h"

class Queen: public Piece {
    public:
        // contructs an isWhite Queen piece at (x,y) 
        Queen(int let, int number, bool white);
        // checks if the move is mechanically valid
        bool isValidMove(int x, int y) override;
        // returns 'Q' for white and 'q' for black
        char getType() override;
        // returns the line to a king at (x,y)
        vector<pair<int, int>*> kingLine(int x, int y) override;
};

#endif
