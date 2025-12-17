#include "bishop.h"

Bishop::Bishop(int let, int number, bool white) {
    letter = let;
    num = number;
    isWhite = white;
    lastMove = 0;
}

bool Bishop::isValidMove(int x, int y) {
    return diagonalMoves(x, y);
}

char Bishop::getType() {
    if (isWhite) return 'B';
    else return 'b';
}

vector<pair<int, int>*> Bishop::kingLine(int x, int y) {
    return diagonalVec(x, y);
}
