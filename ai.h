#ifndef __AI_H__
#define __AI_H__
#include <vector>
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <utility>
#include "model.h"


using namespace std;


class AI {
    protected:
        Model* m;
    public:
        // creates a move for an ai and moves it
        virtual void move(bool isWhite) = 0;
        virtual ~AI();
};

#endif
