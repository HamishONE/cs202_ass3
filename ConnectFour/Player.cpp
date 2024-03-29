#include "Player.hpp"

Player::Player(const std::string& name) {

    this->name = name;

    // Initialise score and wins to zero
    score = 0;
    wins = 0;
}

std::string Player::getName() const {
    return name;
}

unsigned int Player::getScore() const {
    return score;
}

void Player::resetScore() {
    score = 0;
}

void Player::increaseScore() {
    score++;
}

unsigned int Player::getWins() const {
    return wins;
}

void Player::increaseWins() {
    wins++;
}
