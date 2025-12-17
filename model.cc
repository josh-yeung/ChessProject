#include "model.h"
#include <iostream>

using namespace std;

Model::Model() : display(8, vector<char>(8)) {
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (i % 2 == 0) {
                if (j % 2 == 0) {
                    display[i][j] = '_';
                } else {
                    display[i][j] = ' ';
                }
            } else {
                if (j % 2 == 0) {
                    display[i][j] = ' ';
                } else {
                    display[i][j] = '_';
                }
            }
        }
    }

    const vector<Piece *> bPieces = b.getBlackPieces().getSet();
    const vector<Piece *> wPieces = b.getWhitePieces().getSet();


    for (auto it : bPieces) {
        display[it->getNum()][it->getLetter()] = it->getType();
    }

    for (auto it : wPieces) {
        display[it->getNum()][it->getLetter()] = it->getType();
    } 
}


// bool Model::isStalemate() {}

Model::~Model(){}

void Model::attach(View* observer) {
    observers.emplace_back(observer);
}

bool Model::getPlayer(bool isWhite) {
    if (isWhite) {
        return !white.getIsHuman();
    } else {
        return !black.getIsHuman();
    }
} 


void Model::detach(View* observer) {
    for (auto it = observers.begin(); it != observers.end(); ++it) {
        if (*it == observer) {
            observers.erase(it);
            break;
        }
    }
}

const char Model::getState(int x, int y) const {
    return display[x][y];
}

void Model::notifyObservers() const {
    for (auto observer: observers) {
        observer->notify();
    }
}

Board* Model::getBoard(){
    return &b;
}

bool Model::move(int let, int num, int moveLet, int moveNum, bool isWhite) {
    // pair<int,int> pieceCord = {let,num};
    Piece *p;

    if (isWhite) {
        if (b.getWhitePieces().findPiece(let, num)) {
            p = b.getWhitePieces().findPiece(let, num);
        } else {
            cout << "piece dne" << endl;
            return false;
        }  
    } else {
        if (b.getBlackPieces().findPiece(let, num)) {
            p = b.getBlackPieces().findPiece(let, num);
        } else {
            cout << "piece dne" << endl;
            return false;
        }
    }
    
    if (b.isValidMove(moveLet, moveNum, p)) {
        p->move(moveLet, moveNum);
        if (p->getType() == 'p' || p->getType() == 'P') {
            dynamic_cast<Pawn*>(p)->switchFirst();
            p = pawnPromotion(p);
            if (p->getType() != 'p' && p->getType() != 'P') {
                displayUpdate(let, num, p);
                return true;
            }
            pair<int, int> temp = {-1, -1};
            pair<int, int> tempEnPass = dynamic_cast<Pawn*>(p)->getEnPassant();
            if (tempEnPass != temp) {
                displayUpdate(tempEnPass.first, tempEnPass.second);
            }
        }
        if (p->getType() == 'k' || p->getType() == 'K') {
            dynamic_cast<King*>(p)->switchFirst();
            if (dynamic_cast<King*>(p)->getCastling()) {
                if (moveLet - 2 == 0) {
                    if (p->getPlayer()) {
                        displayUpdate(moveLet - 2, moveNum, b.getWhitePieces().findPiece(moveLet + 1, moveNum));
                    } else {
                        displayUpdate(moveLet - 2, moveNum, b.getBlackPieces().findPiece(moveLet + 1, moveNum));
                    }
                } else if (moveLet + 1 == 7) {
                    // cout << "here to castle" << endl;
                    if (p->getPlayer()) {
                        displayUpdate(moveLet + 1, moveNum, b.getWhitePieces().findPiece(moveLet - 1, moveNum));
                    } else {
                        displayUpdate(moveLet + 1, moveNum, b.getBlackPieces().findPiece(moveLet - 1, moveNum));
                    }
                }
            }
        }
        if (p->getType() == 'r' || p->getType() == 'R') {
            dynamic_cast<Rook*>(p)->switchFirst();
        }        
        displayUpdate(let, num, p);
        // cout << "getting here" << endl;
        return true;
    } else {
        return false;
    }

}

Piece* Model::pawnPromotion(Piece *p) {
    if (p->getPlayer()) {
        if (p->getNum() == 7) {
            char c;
            while (true) {
                cin >> c;
                if (c == 'Q' || c == 'N' || c == 'B' || c == 'R') {
                    break;
                }
            }
            tempPiece* tp = new tempPiece{c, p->getLetter(), p->getNum(), true};
            b.removePiece(true, p->getLetter(), p->getNum());
            b.addPiece(true, tp);
            Piece* ret = b.getWhitePieces().findPiece(tp->letter, tp->num);
            delete tp;
            // cout << ret << endl;
            return ret;
        }
    } else {
        if (p->getNum() == 0) {
            char c;
            while (true) {
                cin >> c;
                if (c == 'q' || c == 'n' || c == 'b' || c == 'r') {
                    break;
                }
            }
            tempPiece* tp = new tempPiece{c, p->getLetter(), p->getNum(), p->getPlayer()};
            b.removePiece(p->getPlayer(), p->getLetter(), p->getNum());
            b.addPiece(p->getPlayer(), tp);
            delete tp;
            return b.getBlackPieces().findPiece(p->getLetter(), p->getNum());
        }
    }
    return p;
}


void Model::displayUpdate(int let, int num) {
    float xRem = (let + 1) % 2;
    float yRem = (num + 1) % 2; 

    if (xRem == yRem) {
        display[num][let] = '_';
    } else {
        display[num][let] = ' ';
    }
}


void Model::displayUpdate(int let, int num, Piece *p) {
    float xRem = (let + 1) % 2;
    float yRem = (num + 1) % 2; 

    if (xRem == yRem) {
        display[num][let] = '_';
    } else {
        display[num][let] = ' ';
    }
    incMoveCounter();
    p->setLastMove(b.getMoveCounter());
    display[p->getNum()][p->getLetter()] = p->getType();
}

void Model::displayUpdate() {
    const vector<Piece *> bPieces = b.getBlackPieces().getSet();
    const vector<Piece *> wPieces = b.getWhitePieces().getSet();

    for (auto it : bPieces) {
        display[it->getNum()][it->getLetter()] = it->getType();
    }

    for (auto it : wPieces) {
        display[it->getNum()][it->getLetter()] = it->getType();
    } 
}



void Model::increaseScore(float increase, bool isWhite) {
    if(isWhite) {
        white.increaseScore(increase);
    } else {
        black.increaseScore(increase);
    }
}

void Model::initializePlayers(const string& player1, const string& player2) {
    if (player1 == "human") {
        white.setHuman(true);
    } else if (player1 == "computer[1]") {
        white.setHuman(false);
        white.setLevel(1);
    } else if (player1 == "computer[2]") {
        white.setHuman(false);
        white.setLevel(2);
    } else if (player1 == "computer[3]") {
        white.setHuman(false);
        white.setLevel(3);
    } else if (player1 == "computer[4]") {
        white.setHuman(false);
        white.setLevel(4);
    }

    if (player2 == "human") {
        black.setHuman(true);
    } else if (player2 == "computer[1]") {
        black.setHuman(false);
        black.setLevel(1);
    } else if (player2 == "computer[2]") {
        black.setHuman(false);
        black.setLevel(2);
    } else if (player2 == "computer[3]") {
        black.setHuman(false);
        black.setLevel(3);
    } else if (player2 == "computer[4]") {
        black.setHuman(false);
        black.setLevel(4);
    }
}

bool Model::check(bool isWhite) {
    return b.check(isWhite);
}

bool Model::isCheckmate(bool isWhite) {
    return b.checkMate(isWhite);
}


void Model::incMoveCounter() {
    b.incMoveCounter();
}

int Model::getMoveCounter() {
    return b.getMoveCounter();
}

int Model::getScore(bool isWhite) {
    if (isWhite) return white.getScore();
    return black.getScore();
}

void Model::resetBoard() {
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (i % 2 == 0) {
                if (j % 2 == 0) {
                    display[i][j] = '_';
                } else {
                    display[i][j] = ' ';
                }
            } else {
                if (j % 2 == 0) {
                    display[i][j] = ' ';
                } else {
                    display[i][j] = '_';
                }
            }
        }
    }
    b.getBlackPieces().clearPieces();
    b.getWhitePieces().clearPieces();
}
