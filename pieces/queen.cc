#include "queen.h"

Queen::Queen(int let, int number, bool white) {
    letter = let;
    num = number;
    isWhite = white;
    lastMove = 0;
}

bool Queen::isValidMove(int x, int y) {
    return cardinalMoves(x,y) || diagonalMoves(x,y);
}

char Queen::getType() {
    if (isWhite) return 'Q';
    else return 'q';
}

vector<pair<int, int>*> Queen::kingLine(int x, int y) {
    if (x == letter && y != num) {
        return verticalVec(x,y);
    } else if (x != letter && y==num) {
        return horVec(x,y);
    }
    return diagonalVec(x,y);
    // for (auto it : dTemp) {
    //     cout << " Letter: " << it->first << " Number: " << it->second + 1 << endl;;
    // }
    // for (auto it : hTemp) {
    //     cout << " Letter: " << it->first << " Number: " << it->second + 1 << endl;;
    // }
    // for (auto it : vTemp) {
    //     cout << " Letter: " << it->first << " Number: " << it->second + 1 << endl;;
    // }
}
