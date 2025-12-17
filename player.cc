#include "player.h"

Player::Player() : score{0}, isHuman{true}, level{0} {}

void Player::increaseScore(float increase) {
    score += increase;
}

void Player::setHuman(bool b) {
    isHuman = b;
}

void Player::setLevel(int l) {
    level = l;
    // aiLevel = new Level1{m};
}

float Player::getScore() {
    return score;
}

bool Player::getIsHuman() {
    return isHuman;
}

int Player::getLevel() {
    return level;
}
