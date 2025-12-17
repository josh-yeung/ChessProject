#ifndef __PIECESET_H__
#define __PIECESET_H__
#include "pieces.h"
#include "pieces/pawn.h"
#include "pieces/king.h"
#include "pieces/queen.h"
#include "pieces/knight.h"
#include "pieces/rook.h"
#include "pieces/bishop.h"
#include <vector>
#include <string>

using namespace std;

class PieceSet {
    vector<Piece*> set;
public:
    ~PieceSet();
    int numPieces();

    // Initializes a new set of pieces for white and black set, putting 
    //    the pieces in a set, putting it in their default places.
    void initializeNewSet(bool isWhite); 

    // Will add the piece (a char) into position x,y 
    //    and will put uses isWhite to put it as a white/black piece.
    void addPiece(char piece, int x, int y, bool isWhite);

    // Will delete the piece at position x,y.
    void removePiece(int x, int y);

    // Returns if the position at x,y is occupied or not.
    bool posOccupied(int x, int y);

    // Returns a pointer to the piece at position x,y else returns a nullptr.
    Piece* findPiece(int x, int y) const;

    // Returns the set of pieces.
    const vector<Piece*>& getSet() const;

    // Returns the position that the King piece is at, if it isn't found
    //    returns 0,0.
    const pair<int, int> getKing() const;

    // Clears pieces for a new game.
    void clearPieces(); 
};


#endif
