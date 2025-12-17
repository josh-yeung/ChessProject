#include "rook.h"

Rook::Rook(int let, int number, bool white, bool first) : firstMove{first} {
    letter = let;
    num = number;
    isWhite = white;
    lastMove = 0;
}

bool Rook::isValidMove(int x, int y) {
    return cardinalMoves(x, y);
}

char Rook::getType() {
    if (isWhite) return 'R';
    else return 'r';
}

void Rook::switchFirst() {
    firstMove = false;
}

bool Rook::checkFirst() {
    return firstMove;
}

vector<pair<int, int>*> Rook::kingLine(int x, int y) {
    if (x == letter && y != num) {
        return verticalVec(x,y);
    } 
    return horVec(x,y);
}
