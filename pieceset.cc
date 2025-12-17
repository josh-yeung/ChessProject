#include "pieceset.h"
#include <sstream>
#include <string>
#include <iostream>

using namespace std;

PieceSet::~PieceSet() {
    for (auto it : set) {
        delete it;
    }
    set.clear();
}

void PieceSet::initializeNewSet(bool isWhite) {
    if (isWhite) {
        for (int i = 0; i < 16; ++i) {
            if (i < 8) {
                set.emplace_back(new Pawn{i, 1, true, true});
            } else if (i == 8 || i == 15) {
                set.emplace_back(new Rook{i - 8, 0, true, true});
            } else if (i == 9 || i == 14 ) {
                set.emplace_back(new Knight{i - 8, 0, true});
            } else if (i == 10 || i == 13) {
                set.emplace_back(new Bishop{i - 8, 0, true});
            } else if (i == 11) {
                set.emplace_back(new Queen{3, 0, true});
            } else if (i == 12) {
                set.emplace_back(new King{4, 0, true, true, false});
            }
        }
    } else {
        for (int i = 0; i < 16; ++i) {
            if (i < 8) {
                set.emplace_back(new Pawn{i, 6, false, true});
            } else if (i == 8 || i == 15) {
                set.emplace_back(new Rook{i - 8, 7, false, true});
            } else if (i == 9 || i == 14 ) {
                set.emplace_back(new Knight{i - 8, 7, false});
            } else if (i == 10 || i == 13) {
                set.emplace_back(new Bishop{i - 8, 7, false});
            } else if (i == 11) {
                set.emplace_back(new Queen{3, 7, false});
            } else if (i == 12) {
                set.emplace_back(new King{4, 7, false, true, false});
            }
        }
    }
}

void PieceSet::addPiece(char piece, int x, int y, bool isWhite) {
    if (piece == 'P' || piece == 'p') {
        set.emplace_back(new Pawn{x, y, isWhite, false}); // It is not the pawns first move
    }
    if (piece == 'R' || piece == 'r') {
        set.emplace_back(new Rook{x,y, isWhite, false});
    }
    if (piece == 'N' || piece == 'n') {
        set.emplace_back(new Knight{x,y, isWhite});
    }
    if (piece == 'B' || piece == 'b') {
        set.emplace_back(new Bishop{x,y, isWhite});
    }
    if (piece == 'Q' || piece == 'q') {
        set.emplace_back(new Queen{x,y, isWhite});
    }
    if (piece == 'K' || piece == 'k') {
        set.emplace_back(new King{x, y, isWhite, false, false});
    }
}

void PieceSet::removePiece(int x, int y) {
    //cout << "getting called twice" << endl;
    for (auto it = set.begin(); it != set.end();) {
        if ((*it)->getLetter() == x && (*it)->getNum() == y) {
            //cout << "found piece: " << (*it)->getType() << endl;
            delete (*it);
            it = set.erase(it);
            return;
        } else {
            ++it;
        }
    }
}


bool PieceSet::posOccupied(int x, int y) {
    pair<int, int> movePos = {x, y};

    for (auto it = set.begin(); it < set.end(); it++) {
        if ((*it)->getPosition() == movePos) return true;
    }
    return false;
}

const vector<Piece*>& PieceSet::getSet() const {
    return set;
}


Piece* PieceSet::findPiece(int x, int y) const {
    pair<int, int> piece = {x, y};
    for (auto it : set) {
        if (piece == it->getPosition()) return it;
    }
    return nullptr;
}

const pair<int,int> PieceSet::getKing() const {
    for (auto it : set) {
        if (it->getType() == 'k' || it->getType() == 'K') return it->getPosition();
    }
    return {0,0};
}

void PieceSet::clearPieces() {
    for (auto it : set) {
        delete it;
    }
    set.clear();
}

int PieceSet::numPieces() {
    return set.size();
}
