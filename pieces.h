#ifndef __PIECES_H__
#define __PIECES_H__
#include <vector>
#include <cstdlib>
#include <cmath>
#include <iostream>

using namespace std;

class Piece {
    protected:
        int letter;
        int num;
        bool isWhite;
        int lastMove;
    public:
        //Destructor
        virtual ~Piece();

        //returns letter
        int getLetter();
        
        // returns num
        int getNum();
        
        // returns the if the players is white or black
        bool getPlayer();
        
        // virtual function for each peice to see if the move is mechanically allowed
        virtual bool isValidMove(int x, int y) = 0;
        
        // changes the letter and num for the peice
        void move(int x, int y);
        
        // sees if the move is diagonal accoring to where the peice is
        bool diagonalMoves(int x, int y);
        
        // returns the vector of spots inbetween the piece and a diagonal move
        vector<pair<int, int>*> diagonalVec(int x, int y);
        
        // sees if the move is in a cardinal direction to the peice
        bool cardinalMoves(int x, int y);
        
        // returns the vector of spots inbetween the peice and a horizontal move
        vector<pair<int, int>*> horVec(int x, int y);
        
        // sees if the move is in a vertical direction to the piece
        bool verticalMoves(int x, int y);
        
        // returns the vector of spots inbetween the peice and a vertical move
        vector<pair<int, int>*> verticalVec(int x, int y);
        
        // returns the position of the piece
        pair<int, int> getPosition();
        
        // virtual finction to return the type of a piece, lower case for blakc and uppercase to white
        virtual char getType() = 0;
        
        // sees if the piece can mechanically move to the position (x,y)
        bool kingVision(int x, int y);
        
        // sets lastMove to the number move it made
        void setLastMove(int x);
        
        // returns lastMove
        int getLastMove();
        
        // vritual function to return the line of spots to the coordinate (x,y)
        virtual vector<pair<int, int>*> kingLine(int x, int y) = 0;
        
        // friend overloaded output operator
        friend std::ostream& operator<<(ostream &os,  Piece* p);
};

#endif
