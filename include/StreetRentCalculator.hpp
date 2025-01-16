#ifndef STREETRENTCALCULATOR_HPP
#define STREETRENTCALCULATOR_HPP
#include "StrategyRentCalculator.hpp"
#include <cmath>

class StreetRentCalculator : public StrategyRentCalculator {
    int base_rent;
    int house_count;
public:
    StreetRentCalculator(const int base_rent, const int house_count): base_rent(base_rent), house_count(house_count) {}
    [[nodiscard]] int calculateRent() const override {
        // rent = baseRent * 2^(houses)
        int rent = base_rent * static_cast<int>(std::pow(2, house_count));
        // Hotel (5 buildings) has fixed rent
        if (house_count == 5) {
            rent += 500;
        }
        return rent;
    }
};
#endif //STREETRENTCALCULATOR_HPP
