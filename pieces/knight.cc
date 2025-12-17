#include "knight.h"

Knight::Knight(int let, int number, bool white) {
    letter = let;
    num = number;
    isWhite = white;
    lastMove = 0;
}

bool Knight::isValidMove(int x, int y) {
    int letMove = abs(letter - x);
    int numMove = abs(num - y);

    if ((letMove == 2 && numMove == 1) || (letMove == 1 && numMove == 2)) return true;
    else return false; 
}

char Knight::getType() {
    if (isWhite) return 'N';
    else return 'n';
}

vector<pair<int, int>*> Knight::kingLine(int x, int y) {
    return {new pair<int, int>{letter, num}};
}
