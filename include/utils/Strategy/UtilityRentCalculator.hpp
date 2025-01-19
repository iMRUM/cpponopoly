#ifndef UTILITYRENTCALCULATOR_HPP
#define UTILITYRENTCALCULATOR_HPP
#include "StrategyRentCalculator.hpp"
#include <cmath>

#include "StrategyRentCalculator.hpp"

class UtilityRentCalculator : public StrategyRentCalculator {
private:
    int base_rent_multiplier;
    int dice_roll;

public:
    UtilityRentCalculator(const int base_rent_multiplier, const int dice_roll)
        : base_rent_multiplier(base_rent_multiplier), dice_roll(dice_roll) {}

    [[nodiscard]] int calculateRent() const override {
        return base_rent_multiplier * dice_roll;
    }
};
#endif //UTILITYRENTCALCULATOR_HPP