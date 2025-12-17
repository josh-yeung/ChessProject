#ifndef __LEVEL1_H__
#define __LEVEL1_H__
#include <vector>
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <utility>
#include "../ai.h"
#include "../pieceset.h"


using namespace std;


class Level1: public AI {
    public:
        //~Level1() override;
        // constructs a level1 ai with model
        Level1(Model* m);
        // level 1 move for an ai
        void move(bool isWhite) override;
};

#endif
