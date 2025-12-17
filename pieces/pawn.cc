#include "pawn.h"
#include <iostream>
using namespace std;

Pawn::Pawn(int let, int number, bool white, bool first) : firstMove{first} {
    letter = let;
    num = number;
    isWhite = white;
    lastMove = 0;

}

bool Pawn::isValidMove(int x, int y) {
    int letMove = abs(letter - x);
    int numMove = y - num;
    if (!isWhite) {
        numMove = num - y;
    }
    if (!firstMove) {
        return (letMove == 1 && numMove == 1) || (letMove == 0 && numMove == 1);
    } else {
        // cout << "getting here" << endl;
        return (letMove == 1 && numMove == 1) || (letMove == 0 && numMove == 2) || (letMove == 0 && numMove == 1);
    }
}

char Pawn::getType() {
    if (isWhite) return 'P';
    else return 'p';
}

void Pawn::switchFirst() {
    firstMove = false;
}

bool Pawn::takingPiece(int x, int y) {
    int letMove = abs(letter - x);
    int numMove = y - num;
    if (!isWhite) {
        numMove = num - y;
    }
    return (letMove == 1 && numMove == 1);
}

bool Pawn::checkFirst() {
    return firstMove;
}

void Pawn::setEnPassant(int x, int y) {
    enPassant = {x,y};
}

pair<int,int> Pawn::getEnPassant() {
    return enPassant;

}

vector<pair<int, int>*> Pawn::kingLine(int x, int y) {
    return {new pair<int, int>{letter, num}};
}
