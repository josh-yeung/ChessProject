#ifndef __LEVEL2_H__
#define __LEVEL2_H__
#include <vector>
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <utility>
#include "../ai.h"

using namespace std;


class Level2: public AI {
    public:
        //~Level2() override;
        Level2(Model* m);
        // creates a level 2 move for an ai
        void move(bool isWhite) override;
};

#endif
