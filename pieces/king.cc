#include "king.h"
#include <iostream>
using namespace std;

King::King(int let, int number, bool white, bool first, bool castling) : firstMove{first}, castling{castling} {
    letter = let;
    num = number;
    isWhite = white;
    lastMove = 0;
}

bool King::isValidMove(int x, int y) {
    int letMove = abs(letter - x);
    int numMove = abs(num - y);
    if (firstMove) {
        if ((x == 2 || x == 6) && numMove == 0) {
            castling = true;
            return true; 
        }
    }

    return (letMove == 1 && numMove == 1) || 
    (letMove == 0 && numMove == 1) || (letMove == 1 && numMove == 0);
}

char King::getType() {
    if (isWhite) return 'K';
    else return 'k';
}

void King::switchFirst() {
    firstMove = false;
}

bool King::getCastling() {
    return castling;
}

bool King::checkFirst() {
    return firstMove;
}

void King::setCastling(bool castle) {
    castling = castle;
}

vector<pair<int,int>*> King::possibleMoves() {
    vector<pair<int,int>*> temp;
    //cout << "dx: " << letter - 1  << " is less than " << letter + 1 << " dy: " << num - 1 << " is less than: " << num + 1<< endl;
    for (int dx = letter - 1; dx <= letter + 1; ++dx) {
        for (int dy = num-1; dy <= num + 1; ++dy) {
            if (dy == num && dx == letter) continue; 
            if (dx >= 0 && dx <= 7 && dy >=0 && dy<=7) {
                //cout << "dx: " << dx << " dy: " << dy << endl;
                pair<int, int>* tempPair = new pair<int, int>{dx, dy};
                temp.emplace_back(tempPair);
            }
        }
    }
    return temp;
}

vector<pair<int, int>*> King::kingLine(int x, int y) {
    return {};
}
