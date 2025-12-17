#include "pieces.h"

struct tempPiece {
    char type;
    int letter;
    int num;
    bool isWhite;
    // Sets tempPiece to p.
    tempPiece(Piece& p);
    
    // MIL for tempPiece.
    tempPiece(char type, int letter, int num, bool isWhite);
};
