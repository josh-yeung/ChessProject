#ifndef __PLAYER_H__
#define __PLAYER_H__
// #include "ai.h"
// #include "ai/level1.h"
// #include "ai/level2.h"
// #include "ai/level3.h"
// #include "ai/level4.h"
// #include "model.h"
class Model;
class Player {
    float score;
    bool isHuman;
    int level;
    public:
        Player();

        // Increases score by the amount increase given to it.
        void increaseScore(float increase);

        // Will set player.isHuman to either true or false (whatever b equals),
        //    letting us know is the player is a human or AI.
        void setHuman(bool b);

        // Will set the level that the AI player is (can be level 1-4).
        void setLevel(int l);

        // Returns score.
        float getScore();

        // Returns if player is human or AI (true/false).
        bool getIsHuman();

        // Returns the level the AI is.
        int getLevel();
};

#endif
