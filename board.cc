#include "board.h"
#include <iostream>

using namespace std;


Board::Board() {}

Board::~Board() {
}

void Board::initDefaultBoard() {
    black.initializeNewSet(false);
    white.initializeNewSet(true);
}

PieceSet& Board::getWhitePieces() {
    return white;
}

PieceSet& Board::getBlackPieces() {
    return black;
}

void Board::addPiece(bool isWhite, tempPiece* tp) {
    if (isWhite) {
        white.addPiece(tp->type, tp->letter, tp->num, tp->isWhite);
    } else {
        black.addPiece(tp->type, tp->letter, tp->num, tp->isWhite);
    }
}

void Board::addPiece(char piece, int x, int y, bool isWhite) {
    if (isWhite) {
        white.addPiece(piece, x, y, isWhite);
    } else {
        black.addPiece(piece, x, y, isWhite);
    }
}

void Board::removePiece(bool isWhite, int x, int y) {
    if (isWhite) {
        white.removePiece(x, y);
    } else {
        black.removePiece(x, y);
    }
}

bool Board::inBetween(int x, int y, Piece *p) {
    if (p->getType() == 'n' || p->getType() == 'N') return false;

    if (p->getNum() != y && p->getLetter() == x) {
        int i = y+1;
        int j = p->getNum() - 1;
        if (y > p->getNum()) {
            i = p->getNum() + 1;
            j = y - 1;
        }
        for (; i <= j; i++) {
            if (white.posOccupied(x, i) || black.posOccupied(x,i)) return true;
        }

    } else if (p->getNum() == y && p->getLetter() != x) {
        int i = x+1;
        int j = p->getLetter() - 1;
        if (x > p->getLetter()) {
            i = p->getLetter()+1;
            j = x - 1;
        }
        for (; i <= j; i++) {
            if (white.posOccupied(i, y) || black.posOccupied(i,y)) return true;
        }
    } else if (p->getNum() != y && p->getLetter() != x) {
        // g
        int i = x+1;
        int iEnd = p->getLetter() - 1;
        int j = y+1;
        int jEnd = p->getNum() - 1;
        if (x > p->getLetter() && y > p->getNum()) {
            // x
            // cout << "x" << endl;
            i = p->getLetter() + 1;
            iEnd = x - 1;
            j = p->getNum() + 1;
            jEnd = y - 1;
            for (; i <= iEnd && j <= jEnd; i++) {
                // cout << "i: " << i << " j: " << j << endl;
                if (white.posOccupied(i, j) || black.posOccupied(i,j)) return true;
                j++;
            }            
        } else if (x < p->getLetter() && y > p->getNum()) {
            // d
            // cout << "d" << endl;
            j = y - 1;
            jEnd = p->getNum() + 1;
            for (; i <= iEnd && j >= jEnd; i++) {
                // cout << "i: " << i << " j: " << j << endl;
                if (white.posOccupied(i, j) || black.posOccupied(i,j)) return true;
                j--;
            }               
        } else if (x > p->getLetter() && y < p->getNum()) {
            // h
            // cout << "h" << endl;
            i = x - 1;
            iEnd = p->getLetter() + 1;
            for (; i >= iEnd && j <= jEnd; i--) {
                // cout << "i: " << i << " j: " << j << endl;
                if (white.posOccupied(i, j) || black.posOccupied(i,j)) return true;
                j++;
            }
        } else {
            // cout << "i: " << i << " iEnd: " << iEnd << " j: " << j << " jEnd: " << jEnd << endl;
            for (; i <= iEnd && j <= jEnd; i++) {
                // cout << "i: " << i << " j: " << j << endl;
                if (white.posOccupied(i, j) || black.posOccupied(i,j)) return true;
                j++;
            }
        }
    }

    return false;

}

bool Board::isValidMove(int x, int y, Piece *p) {
    // cout << "here0" << endl;
    if (!p->isValidMove(x, y)) return false;
    // cout << "here1" << endl;

    if (p->getPlayer()) {
        if (white.posOccupied(x, y)) return false;
    } else {
        if (black.posOccupied(x, y)) return false;
    }



    if (p->getType() == 'p') {
        // cout << "i am a pawn" <<endl;
        
        if (dynamic_cast<Pawn *>(p)->takingPiece(x,y)) {
            // cout << "Checking Valid Move: " << p << endl;
            if (!white.posOccupied(x,y)) {
                if (enPassant(x,y,p,&black, &white)) {
                    return true;
                } 
                return false;
            } 
        }
        if (white.posOccupied(x,y)) {
            if (!dynamic_cast<Pawn *>(p)->takingPiece(x,y)) {
                return false;
            }
        }
    } else if (p->getType() == 'P') {
        //cout << "here" << endl;
        if (dynamic_cast<Pawn *>(p)->takingPiece(x,y)) {
            if (!black.posOccupied(x,y)) {
                //cout << "here2" << endl;
                if (enPassant(x,y,p,&white, &black)) {
                    return true;
                } 
                return false;                
            }
        }
        if (black.posOccupied(x,y)) {
            if (!dynamic_cast<Pawn *>(p)->takingPiece(x,y)) {
                return false;
            }
        }        
    }
    // cout << "here2" << endl;
    if (inBetween(x, y, p)) return false;
    // cout << "here3" << endl;
    //pair<int, int> currPos = p->getPosition();

    if (p->getType() == 'k' || p->getType() == 'K') {
        if (dynamic_cast<King *>(p)->getCastling()) {
            // cout << "castling" << endl;
            if (validCastle(x,y,p)) {
                
                dynamic_cast<King *>(p)->setCastling(true);
                return true;
            } else {
                dynamic_cast<King *>(p)->setCastling(false);
                return false;
            }
        }
    }
    bool final = true;
    vector<tempPiece *> tempPieces = simMove(x,y,p,p->getPlayer());
    if (check(!p->getPlayer())) {
        // cout << "in self check" << endl;
        final = false;
    } 

    revertMove(tempPieces, p);

    for (auto ptr : tempPieces) {
        delete ptr;
    }
    tempPieces.clear();

    if (!final) return false;


    if (p->getPlayer()) {
        if (black.posOccupied(x,y)) {
            black.removePiece(x,y);
        } 
    } else { 
        if (white.posOccupied(x,y)) {
            white.removePiece(x,y);
        } 
    }

    return true;

}

bool Board::checkMate(bool isWhite) {
    PieceSet* mySet = &black;
    PieceSet* otherSet = &white;
    if (!isWhite) {
        // cout << "checkign white in checkmate" << endl;
        mySet = &white;
        otherSet = &black;
    } 
    pair<int, int> kingCoor = mySet->getKing();
    Piece* king = mySet->findPiece(kingCoor.first, kingCoor.second);
    // cout << "seg fault here" << endl;
    if (canKingMove(mySet, otherSet, king)) return false;
    // cout << "seg fault here2" << endl;
    
    vector<Piece *> checkPieces;
    // cout << "getting here after king move" << endl;
    //try {
    for (auto it : otherSet->getSet()) {
        if (it->kingVision(kingCoor.first, kingCoor.second)) {
            if (!inBetween(kingCoor.first, kingCoor.second, it)) {
                checkPieces.emplace_back(it);
            }
        }
    }
    // }
    // catch (std::bad_alloc) {
    //     cout << "throwing here" << endl;
    // }

    // for (auto it : checkPieces) {
    //     cout << it << endl;
    // }

    // cout << checkPieces[0] << endl;
    if (checkPieces.size() != 1) return true;
    // cout << "seg fault in this loop" << endl;

    vector<pair<int, int>*> checkSpots = checkPieces[0]->kingLine(kingCoor.first, kingCoor.second);

    // for (auto it : checkSpots) {
    //     cout << " Letter: " << static_cast<char>(it->first + 'A') << " Number: " << it->second + 1 << endl;;
    // }
    // cout << "seg fault in this loop2" << endl;
    bool final = true;
    for (auto it : checkSpots) {
        for (auto piece : mySet->getSet()) {
            if (isValidMove(it->first, it->second, piece)) {
                //cout << piece << endl;
                //cout << "Letter: " << static_cast<char>(it->first + 'A') << " Number: " << it->second + 1 << endl;
                final = false;
                break;
            }
        }
        if (final == false) break;
    }

    for (auto it : checkSpots) {
        delete it;
    }
    cout << "here" << endl;
    
    checkSpots.clear();
    return final;
    // cout << "this is checkmate" << endl;

    return true;
}

bool Board::canKingMove(PieceSet* mySet, PieceSet* otherSet, Piece* king) {
    vector<pair<int,int>*> kingMoves = dynamic_cast<King*>(king)->possibleMoves();
    // cout << "kingMoves size: " << kingMoves.size() << endl;

    for (auto it = kingMoves.begin(); it != kingMoves.end(); ) {
        if (!isValidMove((*it)->first, (*it)->second, king)) {
            // cout << "here" << endl;
            // Erase returns the iterator to the next element
            delete *it;
            it = kingMoves.erase(it);
        } else {
            // Only increment the iterator if you didn't erase
            ++it;
        }
    }
    // cout << "seg fault here in kingMove" << endl;

    if (kingMoves.size() != 0) {
        for (auto it : kingMoves) delete it;
        kingMoves.clear();
        return true;
    } else {
        return false;
    }
}

vector<pair<int,int>*> Board::canPieceMove(PieceSet* mySet, Piece* p) {
    vector<pair<int,int>*> temp;
    int letter = p->getLetter();
    int num = p->getNum();
    //cout << "dx: " << letter - 1  << " is less than " << letter + 1 << " dy: " << num - 1 << " is less than: " << num + 1<< endl;
    char piece = toupper(p->getType());
    if (piece == 'Q' || piece == 'K') {
        //
        for (int dx = letter - 1; dx <= letter + 1; ++dx) {
            for (int dy = num-1; dy <= num + 1; ++dy) {
                if (dy == num && dx == letter) continue; 
                if (dx >= 0 && dx <= 7 && dy >=0 && dy<=7) {
                    // cout << "dx: " << dx << " dy: " << dy << endl;
                    if (!mySet->posOccupied(dx, dy)) {
                        pair<int, int>* tempPair = new pair<int, int>{dx, dy};
                        temp.emplace_back(tempPair);
                    }
                }
            }
        }
    } else if (piece == 'R') {
        vector<pair<int,int>> spots = {{letter - 1, num}, {letter+1, num}, {letter,num-1}, {letter,num+1}};
        for (auto it : spots) {
            if (it.first >= 0 && it.first <= 7 && it.second >=0 && it.second<=7) {
                //cout << "dx: " << dx << " dy: " << dy << endl;
                if (!mySet->posOccupied(it.first, it.second)) {
                    pair<int, int>* tempPair = new pair<int, int>{it.first, it.second};
                    temp.emplace_back(tempPair);
                }
            }
        }
    } else if (piece == 'B') {
        vector<pair<int,int>> spots = {{letter - 1, num-1}, {letter+1, num+1}, {letter+1,num-1}, {letter-1,num+1}};
        for (auto it : spots) {
            if (it.first >= 0 && it.first <= 7 && it.second >=0 && it.second<=7) {
                //cout << "dx: " << dx << " dy: " << dy << endl;
                if (!mySet->posOccupied(it.first, it.second)) {
                    pair<int, int>* tempPair = new pair<int, int>{it.first, it.second};
                    temp.emplace_back(tempPair);
                }
            }
        }        
    } else if (piece == 'N') {
        temp.emplace_back(new pair<int,int>{letter,num});
    } else if (p->getType() == 'P') {
        vector<pair<int,int>> spots = {{letter - 1, num+1}, {letter+1, num+1}, {letter,num+1}};
        for (auto it : spots) {
            //cout << "letter: " << it.first << " num: " << it.second << endl;
            if (it.first >= 0 && it.first <= 7 && it.second >=0 && it.second<=7) {
                //cout << "dx: " << dx << " dy: " << dy << endl;
                if (!mySet->posOccupied(it.first, it.second)) {
                    pair<int, int>* tempPair = new pair<int, int>{it.first, it.second};
                    temp.emplace_back(tempPair);
                }
            }
        }  
    } else if (p->getType() == 'p') {
        vector<pair<int,int>> spots = {{letter - 1, num-1}, {letter+1, num-1}, {letter,num-1}};
        for (auto it : spots) {
            if (it.first >= 0 && it.first <= 7 && it.second >=0 && it.second<=7) {
                //cout << "dx: " << it.first << " dy: " << it.second << endl;
                if (!mySet->posOccupied(it.first, it.second)) {
                    pair<int, int>* tempPair = new pair<int, int>{it.first, it.second};
                    temp.emplace_back(tempPair);
                }
            }
        } 
    }

    return temp;
}


vector<pair<int,int>*> Board::moveLine(PieceSet* mySet, pair<int,int>* spot, Piece* p) {
    int letter = p->getLetter();
    int num = p->getNum();
    int moveLet = spot->first;
    int moveNum = spot->second;
    vector<pair<int,int>*> temp;
    if (toupper(p->getType()) == 'P') {
        if (isValidMove(moveLet, moveNum, p)) temp.emplace_back(new pair<int,int>(moveLet, moveNum));
        //temp.emplace_back(new pair<int,int>(moveLet, moveNum));
        if (p->getType() == 'P') {
            if (letter == moveLet && moveNum > num) {
                if (dynamic_cast<Pawn *>(p)->checkFirst()) {
                    if (isValidMove(moveLet, moveNum + 1, p)) temp.emplace_back(new pair<int,int>(moveLet, moveNum + 1)); 
                    //temp.emplace_back(new pair<int,int>(moveLet, moveNum + 1));
                }
            }
        } else if (p->getType() == 'p') {
            if (letter == moveLet && moveNum < num) {
                if (dynamic_cast<Pawn *>(p)->checkFirst()) {
                    if (isValidMove(moveLet, moveNum - 1, p)) temp.emplace_back(new pair<int,int>(moveLet, moveNum - 1));
                    //temp.emplace_back(new pair<int,int>(moveLet, moveNum - 1)); 
                }
            }
        }
    } else if (toupper(p->getType()) == 'N') {
        vector<pair<int,int>> moves = {{letter - 1, num + 2}, {letter - 1, num - 2}, {letter + 1, num + 2}, {letter+ 1, num-2},
                                        {letter - 2, num + 1}, {letter - 2, num - 1}, {letter + 2, num + 1}, {letter+ 2, num-1}};
        for (auto it : moves) {
            if (it.first >= 0 && it.first <= 7 && it.second >= 0 && it.second <=7) {
                temp.emplace_back(new pair<int,int>(it.first, it.second));
            }
        }
    } else if (moveLet > letter && moveNum > num) {
        int x = letter;
        int y = num;
        while (x <= 7 && y <= 7) {
            ++x;
            ++y;
        }
       temp = p->diagonalVec(x, y);
    } else if (moveLet < letter && moveNum < num) {
        int x = letter;
        int y = num;
        while (x >= 0 && y >= 0) {
            --x;
            --y;
        }
       temp = p->diagonalVec(x, y);
    } else if (moveLet > letter && moveNum < num) {
        int x = letter;
        int y = num;
        while (x <= 7 && y >= 0) {
            ++x;
            --y;
        }
       temp = p->diagonalVec(x, y);
    } else if (moveLet < letter && moveNum > num) {
        int x = letter;
        int y = num;
        while (x >= 0 && y <= 7) {
            --x;
            ++y;
        }
        temp = p->diagonalVec(x, y);
    } else if (moveLet == letter && moveNum > num) {
        temp = p->verticalVec(letter, 7);
    } else if (moveLet == letter && moveNum < num) {
        temp = p->verticalVec(letter, 0);
    } else if (moveLet > letter && moveNum == num) {
        temp = p->horVec(7, num);
    } else if (moveLet < letter && moveNum == num) {
        temp = p->horVec(0, num);
    }

    for (auto it = temp.begin(); it != temp.end();) {
        if (!isValidMove((*it)->first, (*it)->second, p)) {
            delete *it;
            it = temp.erase(it);
        } else {
            ++it;
        }
    }

    return temp;
}

 vector<tempPiece *> Board::enPassanSim(int opLet, int opNum, vector<tempPiece *> tp, PieceSet* otherSet) {
    tempPiece *r = new tempPiece{*otherSet->findPiece(opLet, opNum)};
    tp.emplace_back(r);
    otherSet->removePiece(opLet, opNum);
    return tp;
 }


bool Board::enPassantHelper(int opLet, int opNum, int let, int num, char op, Piece *p, PieceSet* otherSet){
    //  cout << "en passant" << endl;
    if (otherSet->posOccupied(opLet, opNum)) {
        if (otherSet->findPiece(opLet, opNum)->getType() == op) {
            if (otherSet->findPiece(opLet, opNum)->getLastMove() == moveCounter) {
                // cout << "en passant" << endl;
                vector<tempPiece *> pieces;
                tempPiece *p1 = new tempPiece{*p};
                pieces.emplace_back(p1);
                pieces = enPassanSim(opLet, opNum, pieces, otherSet);
                if (check(!p->getPlayer())) {
                    revertMove(pieces, p);
                    for (auto it : pieces) delete it;
                    pieces.clear();
                    return false;
                } else {
                    revertMove(pieces, p);
                    for (auto it : pieces) delete it;
                    pieces.clear();
                    otherSet->removePiece(opLet, opNum);
                    dynamic_cast<Pawn *>(p)->setEnPassant(opLet, opNum);
                }
            } else return false;
        } else return false;
    } else return false;
    return true;
}

// pair<int, int> 

bool Board::enPassant(int x, int y, Piece *p, PieceSet* mySet, PieceSet* otherSet) {
    if (y == 2 && !p->getPlayer()) {
        vector<Piece *> temp;
        if (p->getLetter() >= 1 && p->getLetter() <= 6) {
            if (enPassantHelper(p->getLetter() - 1, p->getNum(), x, y, 'P', p, otherSet)) {
                return true;
            } else if (enPassantHelper(p->getLetter() + 1, p->getNum(), x, y, 'P', p, otherSet)) {
                return true;
            } else return false;
        } else if (p->getLetter() == 0) {
            if (enPassantHelper(p->getLetter() + 1, p->getNum(), x, y, 'P', p, otherSet)) {
                return true;
            } else return false;
        } else if (p->getLetter() == 7) {
            if (enPassantHelper(p->getLetter() - 1, p->getNum(), x, y, 'P', p, otherSet)) {
                return true;
            } else return false;      
        }
    } else if (y == 5 && p->getPlayer()) { 
        //cout << "in enpassant for white" << endl;
        if (p->getLetter() >= 1 && p->getLetter() <= 6) {
            if (enPassantHelper(p->getLetter() - 1, p->getNum(), x, y, 'p', p, otherSet)) {
                return true;
            } else if (enPassantHelper(p->getLetter() + 1, p->getNum(), x, y, 'p', p, otherSet)) {
                return true;
            } else {
                return false;
            } 
        } else if (p->getLetter() == 0) {
            if (enPassantHelper(p->getLetter() + 1, p->getNum(), x, y, 'p', p, otherSet)) {
                return true;
            } else return false;
        } else if (p->getLetter() == 7) {
            if (enPassantHelper(p->getLetter() - 1, p->getNum(), x, y, 'p', p, otherSet)) {
                return true;
            } else return false;          
        }        
    } 
    return false;
}




// bool Board::moveHelper(int x, int y, Piece* p) {}

bool Board::castleHelper(int kMoveLet, int kMoveNum, int rMoveLet, int rMoveNum, Piece *king, Piece *rook, PieceSet* set) {
    if (dynamic_cast<Rook*>(rook)->checkFirst()) {
        vector<tempPiece *> kingTp = simMove(kMoveLet, kMoveNum, king, king->getPlayer());
        vector<tempPiece *> rookTp = simMove(rMoveLet, rMoveNum, rook, rook->getPlayer());
        if (check(!king->getPlayer())) {
            revertMove(kingTp, king);
            revertMove(rookTp, rook);
            for (auto it : kingTp) delete it;
            for (auto it : rookTp) delete it;
            kingTp.clear();
            rookTp.clear();
            return false;
        } else {
            revertMove(kingTp, king);
            revertMove(rookTp, rook);
            for (auto it : kingTp) delete it;
            for (auto it : rookTp) delete it;
            kingTp.clear();
            rookTp.clear();
            rook->move(rMoveLet, rMoveNum);
            return true;
        }
    }
    return false;
}

bool Board::validCastle(int moveLet, int moveNum, Piece* p) {
    if (moveLet - 2 == 0) {
        if (!inBetween(0, moveNum, p)) {
            if (p->getPlayer()) {
                if (white.findPiece(moveLet - 2, moveNum)->getType() == 'R') {
                    // cout << "white queen side castle" << endl;
                    return castleHelper(moveLet, moveNum, moveLet + 1, moveNum, p, white.findPiece(moveLet - 2, moveNum), &white);
                } else return false;
            } else {
                
                if (black.findPiece(moveLet - 2, moveNum)->getType() == 'r') {
                    // cout << "black queen side castle" << endl;
                    return castleHelper(moveLet, moveNum, moveLet + 1, moveNum, p, black.findPiece(moveLet - 2, moveNum), &black);
                } else return false;
            }
        } else return false;
    } else if (moveLet + 1 == 7) {
        if (!inBetween(7, moveNum, p)) {
            if (p->getPlayer()) {
                if (white.findPiece(moveLet + 1, moveNum)->getType() == 'R') {
                    return castleHelper(moveLet, moveNum, moveLet - 1, moveNum, p, white.findPiece(moveLet + 1, moveNum), &white);
                } else return false;
            } else {
                if (black.findPiece(moveLet + 1, moveNum)->getType() == 'r') {
                    return castleHelper(moveLet, moveNum, moveLet - 1, moveNum, p, black.findPiece(moveLet + 1, moveNum), &black);
                } else return false;
            }  
        } else return false;      
    }
    return false;
}


bool Board::check(bool isWhite) {
    if (isWhite) {
        // cout << "checking black in check" << endl;
        return checkHelper(&white, &black);
    } else {
        // cout << "checking white in check" << endl;
        return checkHelper(&black, &white);
    }
    return false;
}

bool Board::checkHelper(PieceSet* mySet, PieceSet* otherSet) {
    pair<int, int> king = otherSet->getKing();
    for (auto it : mySet->getSet()) {
        if (it->kingVision(king.first, king.second)) {
            if (!inBetween(king.first, king.second, it)) return true;
        }
    }
    return false;
}

vector<tempPiece *> Board::simMove(int x, int y, Piece* p, bool isWhite) {
    vector<tempPiece *> pieces;
    tempPiece *p1 = new tempPiece{*p};
    pieces.emplace_back(p1);
    if (isWhite) {
        pieces = simHelper(x, y, pieces, &black);
    } else { 
        // cout << "sim move black" << endl;
        pieces = simHelper(x,y,pieces,&white);
    }
    p->move(x, y);
    return pieces;
}

vector<tempPiece *> Board::simHelper(int mLet, int mNum, vector<tempPiece*> tp, PieceSet* set) {
    if (set->posOccupied(mLet, mNum)) {
        tempPiece *r = new tempPiece{*set->findPiece(mLet, mNum)};
        tp.emplace_back(r);
        set->removePiece(mLet, mNum);
    }
    return tp;
}

void Board::revertMove(vector<tempPiece *> pieces, Piece* p) {
    p->move(pieces[0]->letter, pieces[0]->num);
    if (pieces.size() == 2) {
        if (pieces[1]->isWhite) {
            white.addPiece(pieces[1]->type, pieces[1]->letter, pieces[1]->num, pieces[1]->isWhite);
        } else {
            black.addPiece(pieces[1]->type, pieces[1]->letter, pieces[1]->num, pieces[1]->isWhite);
        }
    } 
}


int Board::getMoveCounter() {
    return moveCounter;
}

void Board::incMoveCounter() {
    ++moveCounter;
}

bool Board::isValidBoard() {
    int whiteKing = 0;
    int blackKing = 0;
    const vector<Piece*> w = white.getSet();
    const vector<Piece*> b = black.getSet();
    for (auto piece : w) {
        if (piece->getType() == 'K') {
            ++whiteKing;
            if (whiteKing > 1) {
                return false;
            }
        }
        if (piece->getType() == 'P') {
            if (piece->getNum() == 0 || piece->getNum() == 7) {
                return false;
            }
        }
    }
    for (auto piece : b) {
        if (piece->getType() == 'k') {
            ++blackKing;
            if (blackKing > 1) {
                return false;
            }
        }
        if (piece->getType() == 'p') {
            if (piece->getNum() == 0 || piece->getNum() == 7) {
                return false;
            }
        }
    }
    if (!(blackKing == 1 && whiteKing == 1)) {
        return false;
    }
    if (check(true) || check(false)) {
        return false;
    }
    return true;
}
