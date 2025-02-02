#ifndef RAILROADRENTCALCULATOR_HPP
#define RAILROADRENTCALCULATOR_HPP
#include "StrategyRentCalculator.hpp"
#include <cmath>

#include "StrategyRentCalculator.hpp"

class RailroadRentCalculator : public StrategyRentCalculator {
private:
    int baseRent;
    int ownedRailroads;

public:
    RailroadRentCalculator(const int baseRent, const int ownedRailroads)
        : baseRent(baseRent), ownedRailroads(ownedRailroads) {}

    [[nodiscard]] int calculateRent() const override {
        // rent = baseRent * 2^(n-1) where n is number of railroads owned
        return baseRent * static_cast<int>(std::pow(2, ownedRailroads - 1));
    }
};
#endif //RAILROADRENTCALCULATOR_HPP
