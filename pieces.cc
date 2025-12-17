#include "pieces.h"

Piece::~Piece() {}

int Piece::getLetter() {
    return letter;
}

int Piece::getNum() {
    return num;
}

void Piece::move(int x, int y) {
    letter = x;
    num = y;
}

bool Piece::diagonalMoves(int x, int y) {
    int numMove = abs(num - y);
    int letterMove = abs(letter - x);

    if (numMove != letterMove) return false;
    else return true;
}

bool Piece::cardinalMoves(int x, int y) {
    if ((x != letter) && (y == num)) return true;
    else if ((x == letter) && (y != num)) return true;
    else return false;
}

bool Piece::verticalMoves(int x, int y) {
    if ((x == letter) && (y != num)) return true;
    else return false;
}


vector<pair<int, int>*> Piece::diagonalVec(int x, int y) {
    // cout << "diagonalVec" << endl;
    vector<pair<int, int>*> vec;
        // g
    int i = x+1;
    int iEnd = letter;
    int j = y+1;
    int jEnd = num;
    // cout << "i: " << i << " iEnd: " << iEnd << " j: " << j << " jEnd: " << jEnd << endl;
    if (x > letter && y > num) {
        // x
        i = letter;
        iEnd = x-1;
        j = num;
        jEnd = y-1;
        for (; i <= iEnd && j <= jEnd; i++) {
            pair<int, int>* temp = new pair<int,int>{i, j};
            vec.emplace_back(temp);
            j++;
        }            
    } else if (x < letter && y > num) {
        // d
        j = y-1;
        jEnd = num;
        for (; i <= iEnd && j >= jEnd; i++) {
            pair<int, int>* temp = new pair<int,int>{i, j};
            vec.emplace_back(temp);
            j--;
        }               
    } else if (x > letter && y < num) {
        // h
        i = x-1;
        iEnd = letter;
        for (; i >= iEnd && j <= jEnd; i--) {
            pair<int, int>* temp = new pair<int,int>{i, j};
            vec.emplace_back(temp);
            j++;
        }
    } else {
        for (; i <= iEnd && j <= jEnd; i++) {
            pair<int, int>* temp = new pair<int,int>{i, j};
            vec.emplace_back(temp);
            j++;
        }
    }
    return vec;
}

vector<pair<int, int>*> Piece::horVec(int x, int y) {
    vector<pair<int, int>*> vec;
    int i = x+1;
    int j = letter;
    if (x > letter) {
        i = letter;
        j = x-1;
    }
    for (; i <= j; i++) {
        pair<int, int>* temp = new pair<int,int>{i, num};
        vec.emplace_back(temp);
    }
    return vec;
}

vector<pair<int, int>*> Piece::verticalVec(int x, int y) {
    vector<pair<int, int>*> vec;
    int i = y + 1;
    int j = num;
    if (y > num) {
        i = num;
        j = y - 1;
    }
    for (; i <= j; i++) {
        pair<int, int>* temp = new pair<int,int>{letter, i};
        vec.emplace_back(temp);
    }
    return vec;
}



pair<int, int> Piece::getPosition() {
    pair<int, int> position = {letter, num};

    return position;
}

bool Piece::getPlayer() {
    return isWhite;
}


char Piece::getType() {
    return 'Y';
}

void Piece::setLastMove(int x) {
    lastMove = x;
}

int Piece::getLastMove() {
    return lastMove;
}

bool Piece::kingVision(int x, int y) {
    if (isValidMove(x, y)) return true;
    else return false;
}

std::ostream& operator<<(std::ostream & out,  Piece* p) {
    out << "Piece: " << p->getType() << ", Letter: " << static_cast<char>(p->getLetter() + 'A') << ", Number: " << p->getNum() + 1;
    return out;
}
