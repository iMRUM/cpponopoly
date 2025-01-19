#include "../../include/model/Player.hpp"
namespace monopoly{
void Player::increaseBalance(const int amount) {
    if (amount < 0) {
        throw std::invalid_argument("Cannot increase balance by negative amount");
    }
    balance += amount;
}

bool Player::decreaseBalance(int amount) { // will be used also for determining bankruptcy
    if (amount < 0) {
        throw std::invalid_argument("Cannot decrease balance by negative amount");
    }
    if (balance < amount) {
        return false;
    }
    balance -= amount;
    return true;
}

void Player::moveSteps(int steps) {
    if (steps < 0) {
        throw std::invalid_argument("Cannot move negative steps");
    }
    setPosition((position + steps) % BOARD_SIZE);
}

void Player::toggleJailState() {
    const bool new_state = !isInJail();
    resetJailTurns();
    setJailState(new_state);
}

bool Player::incrementJailTurns() {
    if(getJailTurns()<MAX_JAIL_TURNS) {
        jail_turns++;
        return true;
    }
    return false;
    //TO BE COMPLETED FOR FINE MANAGEMENT
}
}