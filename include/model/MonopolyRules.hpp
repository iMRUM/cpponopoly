#pragma once
#include <vector>
#include <cstdint>

#include "Player.hpp"
#include "Board.hpp"

namespace monopoly::rules {

    // Constants
    constexpr int PASSING_GO_REWARD = 200;
    constexpr int JAIL_FINE = 50;
    constexpr int LUXURY_TAX = 100;

    // Movement & Turn Flow
    bool isJailRequired(Player& player);
    bool canRollAgain(Player& player);
    int calculateNewPosition(Player& player, Board& board);

    // Property Management
    bool canBuyProperty(int player_money, int property_price);
    bool canMortgageProperty(int property_owner_id);
    int calculateMortgageValue(int property_price);

    // Money Handling
    bool isBankrupt(int player_money, int debt);
    int calculateTax(int property_value);
} // namespace monopoly::rules