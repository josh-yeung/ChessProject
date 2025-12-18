#include <iostream>
#include "model.h"
#include "text.h"
#include "graphics.h"
#include "board.h"
#include <string>
#include "controller.h"
#include "ai.h"
#include "ai/level1.h"

using namespace std;

int main() {
    Model m{};
    Text t{&m};
    Graphics g{&m};
    Controller c{&m};
    string command;
    while (cin >> command) {
        if (command == "game") {
            string player1;
            string player2;
            cin >> player1;
            cin >> player2;
            if ((player1 == "human" || player1 == "computer[1]" 
                || player1 == "computer[2]" || player1 == "computer[3]" 
                || player1 == "computer[4]") && 
                (player2 == "human" || player2 == "computer[1]" 
                || player2 == "computer[2]" || player2 == "computer[3]" 
                || player2 == "computer[4]")) {
                c.startGame(player1, player2);
                c.printBoard();
                } 
        } else if (command == "setup") {
            c.setup();
        } else if (command == "resign") {
            c.resign();
        } else if (command == "move") {
            if (m.getPlayer(c.getWhite())) {
                c.move();
            } else {
                string from;
                string to;
                cin >> from;
                cin >> to;
                c.move(from, to);
            }
            c.printBoard();
            if (c.getEndGame()) {
                c.resetGame();
            }
        }
    }
    c.gameEnded();
}
