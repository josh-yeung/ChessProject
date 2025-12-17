#ifndef __LEVEL3_H__
#define __LEVEL3_H__
#include <vector>
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <utility>
#include "../ai.h"

using namespace std;


class Level3: public AI {
    public:
        //~Level3() override;
        Level3(Model* m);
        // creates a level 3 move for an ai
        void move(bool isWhite) override;
};

#endif
