#ifndef __LEVEL4_H__
#define __LEVEL4_H__
#include <vector>
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <utility>
#include "../ai.h"

using namespace std;


class Level4: public AI {
    public:
        //~Level4() override;
        Level4(Model* m);
        // creates a level 4 move for an ai
        void move(bool isWhite) override;
};

#endif
