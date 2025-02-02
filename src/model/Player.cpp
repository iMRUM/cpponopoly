#include "../../include/model/Player.hpp"

namespace monopoly {
    void Player::increaseBalance(const int amount) {
        if (amount < 0) {
            throw std::invalid_argument("Cannot increase balance by negative amount");
        }
        balance += amount;
    }

    bool Player::decreaseBalance(int amount) {
        // will be used also for determining bankruptcy
        if (balance < amount) {
            return false;
        }
        balance -= amount;
        return true;
    }

    void Player::moveSteps(int steps) {
        setPosition((position + steps));
    }

    void Player::toggleJailState() {
        in_jail = !in_jail;
        if (!in_jail) {
            resetJailTurns();
        }
    }

    void Player::incrementJailTurns() {
        jail_turns++;
    }
}
