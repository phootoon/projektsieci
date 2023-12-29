#include "player.h"

Player::Player() : alive(true), connected(false), targetIndex(-1) {}

bool Player::isAlive() const {
    return alive;
}

bool Player::isConnected() const {
    return connected;
}

int Player::getTargetIndex() const {
    return targetIndex;
}

void Player::setAlive(bool alive) {
    this->alive = alive;
}

void Player::setConnected(bool connected) {
    this->connected = connected;
}

void Player::setTargetIndex(int targetIndex) {
    this->targetIndex = targetIndex;
}
