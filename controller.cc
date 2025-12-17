#include "controller.h"
#include <string>
#include <iostream>
#include <sstream>
using namespace std;

Controller::Controller(Model *m) : model(m), isWhite(true), inGame(false)  {}

Controller::~Controller() {
    delete ai;
}
  
//This is called when using the command "game _______ _______"
void Controller::startGame(const string& whitePlayerType, const string& blackPlayerType) {
    if (inGame) {
        cout << "A game is already in progress." << endl;
        return;
    }
    // Initialize players in model as human or computer
    model->initializePlayers(whitePlayerType, blackPlayerType);
    if (model->getPlayer(true) || model->getPlayer(false)) {
        ai = new Level1{model};
    }
   // ai = new Level1{model};
    if (!customSetup) {
        model->getBoard()->initDefaultBoard();
        model->displayUpdate();
    }
    inGame = true;
}

// This is supposed to take a position such as a1 and translate it to 
// row and col coordinates. 
pair<int, int> translateCoordinates(const string& position) {
    if (position.length() != 2) {
        return {-1, -1};
    }
    int x = position[0] - 'a'; 
    int y = position[1] - '1';
    
    if (x < 0 || x >= 8 || y < 0 || y >= 8){
        return {-1, -1};
    } return {x, y};
}

// Handles the move command
bool Controller::move(const string& from, const string& to) {
    if (!inGame) {
        cout << "No game in progress." << std::endl;
        return false;
    }
    // Logic to execute the move
    if (from == to) {
        cout << "Invalid move" << endl;
        return false;
    }
    pair<int, int> orig = translateCoordinates(from);
    pair<int, int> dest = translateCoordinates(to);
    if (!model->move(orig.first, orig.second, dest.first, dest.second, isWhite)) {
        cout << "Invalid move" << endl;
        return false;
    } else {
        cout << "Move: " << model->getMoveCounter() << endl;
        if (isWhite) {
            if (model->check(isWhite)) {
                if (model->isCheckmate(isWhite)) {
                    model->increaseScore(1, true);
                    cout << "Checkmate! White Wins!" << endl;
                    endGame = true;
                    return true;
                }
                cout << "Black is in check." << endl;
                switchTurn();
                return true;
            } 
            switchTurn();
            return true;
        } else {
            if (model->check(isWhite)) {
                if (model->isCheckmate(isWhite)) {
                    model->increaseScore(1, false);
                    cout << "Checkmate! Black Wins!" << endl;
                    endGame = true;
                    return true;
                }
                cout << "White is in check." << endl;
                switchTurn();
                return true;
            }
            switchTurn();
            return true;
        }
    }
    
    // Switch turn after a valid move
}

bool Controller::getWhite() {
    return isWhite;
}

bool Controller::move() {
    if (!inGame) {
        cout << "No game in progress." << std::endl;
        return false;
    }
    ai->move(isWhite);
    cout << "Move: " << model->getMoveCounter() << endl;
    if (isWhite) {
        if (model->check(isWhite)) {
            if (model->isCheckmate(isWhite)) {
                model->increaseScore(1, true);
                cout << "Checkmate! White Wins!" << endl;
                endGame = true;
                return true;
            }
            cout << "Black is in check." << endl;
            switchTurn();
            return true;
        } 
        switchTurn();
        return true;
    } else {
        if (model->check(isWhite)) {
            if (model->isCheckmate(isWhite)) {
                model->increaseScore(1, false);
                cout << "Checkmate! Black Wins!" << endl;
                endGame = true;
                return true;
            }
            cout << "White is in check." << endl;
            switchTurn();
            return true;
        }
        switchTurn();
        return true;
    }
    
    // Switch turn after a valid move
}

// Determines if piece is a valid piece.
bool isValidPiece(string piece) {
    if (piece.size() != 1) {
        return false;
    }
    char a = piece[0];
    if (a != 'Q' && a != 'R' && a != 'N' && a != 'B' && a != 'K' && a != 'P'
    && a != 'q' && a != 'r' && a != 'n' && a != 'b' && a != 'k' && a != 'p') {
        return false;
    }
    return true;
}

// Determines if a given coordinate is valid.
bool isValidCoord(string coord) {
    if (coord.size() != 2) {
        return false;
    }
    char a = coord[0];
    char b = coord[1];
    if (!(a >= 'a' && a <= 'h') || !(b >= '1' && b <= '8')) {
        return false;
    }
    return true;
}


// Set up mode
void Controller::setup() {
    if (inGame) {
        cout << "Game is already running." << endl;
        return;
    }

    while (!cin.eof()) {

        stringstream ss;
        string input;
        string operation;
        string action1;
        string action2;
        getline(cin, input);
        
        if (input == "done") {
            if (model->getBoard()->isValidBoard()) {
                customSetup = true;
                return;
            } else {
                cout << "Board is invalid" << endl;
            }
        }

        ss << input;
        ss >> operation >> action1 >> action2;

        if (operation == "=") {
            if (action1 == "black" && action2 == "") {
                isWhite = false;
            } else if (action1 == "white" && action2 == "") {
                isWhite = true;
            }
        } else if (operation == "-") {
            if (isValidCoord(action1) && action2 == "") {
                pair<int, int> pos = translateCoordinates(action1);
                model->getBoard()->removePiece(true, pos.first, pos.second);
                model->getBoard()->removePiece(false, pos.first, pos.second);
                model->displayUpdate(pos.first, pos.second);
                model->displayUpdate();
                printBoard();
            }
        } else if (operation == "+" && isValidPiece(action1) && isValidCoord(action2)) {
            pair<int, int> pos = translateCoordinates(action2);
            PieceSet& black = model->getBoard()->getBlackPieces();
            PieceSet& white = model->getBoard()->getWhitePieces();
            if (black.posOccupied(pos.first, pos.second)) {
                black.removePiece(pos.first, pos.second);
            }
            if (white.posOccupied(pos.first, pos.second)) {
                white.removePiece(pos.first, pos.second);
            }
            if (action1 == "P") {
                model->getBoard()->addPiece('P', pos.first, pos.second, true);
                model->displayUpdate();
                printBoard();
            } else if (action1 == "p") {
                model->getBoard()->addPiece('p', pos.first, pos.second, false);
                model->displayUpdate();
                printBoard();              
            } else if (action1 == "R") {
                model->getBoard()->addPiece('R', pos.first, pos.second, true);
                model->displayUpdate();
                printBoard();
            } else if (action1 == "r") {
                model->getBoard()->addPiece('r', pos.first, pos.second, false);
                model->displayUpdate();
                printBoard();              
            } else if (action1 == "B") {
                model->getBoard()->addPiece('B', pos.first, pos.second, true);
                model->displayUpdate();
                printBoard();
            } else if (action1 == "b") {
                model->getBoard()->addPiece('b', pos.first, pos.second, false);
                model->displayUpdate();
                printBoard();    
            } else if (action1 == "N") {
                model->getBoard()->addPiece('N', pos.first, pos.second, true);
                model->displayUpdate();
                printBoard();
            } else if (action1 == "n") {
                model->getBoard()->addPiece('n', pos.first, pos.second, false);
                model->displayUpdate();
                printBoard();
            } else if (action1 == "Q") {
                model->getBoard()->addPiece('Q', pos.first, pos.second, true);
                model->displayUpdate();
                printBoard();
            } else if (action1 == "q") {
                model->getBoard()->addPiece('q', pos.first, pos.second, false);
                model->displayUpdate();
                printBoard();
            } else if (action1 == "K") {
                model->getBoard()->addPiece('K', pos.first, pos.second, true);
                model->displayUpdate();
                printBoard();
            } else if (action1 == "k") {
                model->getBoard()->addPiece('k', pos.first, pos.second, false);
                model->displayUpdate();
                printBoard();
            }          
        }
    }
}


// Concede the game
void Controller::resign() {
    
    if (!inGame) {
        cout << "No game in progress." << endl;
        return;
    }
    model->getBoard()->getBlackPieces().clearPieces();
    model->getBoard()->getWhitePieces().clearPieces();
    if (isWhite){
        
        model->increaseScore(1, false);
        inGame = false;
        resetGame();
        cout << "Black wins!" << endl;
    } else {
        model->increaseScore(1,true);
        inGame = false;
        resetGame();
        cout << "White wins!" << endl;
    }
}

void Controller::gameEnded() {
    cout << "Final Score:" << endl;
    cout << "White: " << model->getScore(true) << endl;
    cout << "Black: " << model->getScore(false) << endl;
}

// Switch turns
void Controller::switchTurn() {
    isWhite = !isWhite;
}

void Controller::printBoard() {
    model->notifyObservers();
}

void Controller::resetGame() {
    endGame = false;
    inGame = false;
    isWhite = true;
    customSetup = false;
    model->resetBoard();
}

bool Controller::getEndGame() {
    return endGame;
}
