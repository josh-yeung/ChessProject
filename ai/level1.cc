#include "level1.h"
#include <random>
#include <ctime>
#include <iostream>

using namespace std;

//Level1::~Level1(){}

Level1::Level1(Model* m1) {
    m = m1;
}

void Level1::move(bool isWhite) {
    //cout << "here 1" << endl;
    Board *b = m->getBoard();
    PieceSet* set = &b->getWhitePieces();
    if (!isWhite) {
        //cout << 'here' << endl;
        set = &b->getBlackPieces();
    }
    int size = set->numPieces();
    vector<Piece* > pieces = set->getSet();
    vector<int> triedPieces;
    int i = 0;
    // std::mt19937 rng(time(0));
    std::mt19937 engine(random_device{}());
    std::uniform_int_distribution<int> dist(0, size - 1);
    while (true) {
        // cout << "i is: " << i << endl;
        int min = 0;
        int max = size - 1;
        std::uniform_int_distribution<int> dist(min, max);
        int p = dist(engine);
        bool repeat = false;

        for (auto it : triedPieces) {
            if (it == p) {
                repeat = true;
                ++i;
                break;
            }
        }
        //cout << "here1" << endl;

        if (repeat)  {
            continue;
        }

        //cout << pieces[p] << endl;
        //cout << "here2" << endl;
        vector<pair<int,int>*> spots = b->canPieceMove(set, pieces[p]);
        // for (auto it : spots) {
        //     cout << "letter: " << it->first + 1 << " num: " << it->second << endl; 
        // }
        if (spots.size() == 0) {
            triedPieces.emplace_back(p);
            for (auto it : spots) {
                delete it;
            }
            spots.clear();
            continue;
        } 
        // cout << "here3" << endl;

        // cout << spots.size() << endl;
        

        // for (auto it : spots)  {
        //     cout << "Letter: " << static_cast<char>(it->first+ 'A') << ", Number: " << it->second + 1 << endl;;
        // }


        min = 0;
        max = spots.size() - 1;

        std::uniform_int_distribution<int> dist2(min, max);

        int d = dist2(engine);

        // cout << "here4" << endl;

        vector<pair<int,int>*> temp = b->moveLine(set,spots[d], pieces[p]);
        if (temp.size() == 0) {
            for (auto it : spots) {
                delete it;
            }
            spots.clear();
            for (auto it : temp) {
                delete it;
            }
            temp.clear();
            continue;
        }
         //cout << "here5" << endl;
        
        // for (auto it : temp) {
        //     cout << "letter: " << it->first << " num: " << it->second << endl;
        // }
        min = 0;
        max = temp.size()-1;
        std::uniform_int_distribution<int> dist3(min, max);
        int e = dist3(engine);
        // cout << "here6" << endl;
        // cout << "Randome Spot: " << d << endl;
        bool continue1 = false;
        if (!m->move(pieces[p]->getLetter(), pieces[p]->getNum(), temp[e]->first, temp[e]->second, isWhite)) {
            continue1 = true;
        }
        for (auto it : spots) {
            delete it;
        }
        spots.clear();
        for (auto it : temp) {
            delete it;
        }
        temp.clear();

        if (continue1) continue;
         //cout << "here7" << endl;
        
        break;
    }

}
