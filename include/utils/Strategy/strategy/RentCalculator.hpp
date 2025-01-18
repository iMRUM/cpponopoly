#ifndef RENT_CALCULATOR_HPP
#define RENT_CALCULATOR_HPP

#include <cstdint>
#include <cmath>

class RentCalculator {
protected:
    RentCalculator() = default;

public:
    virtual ~RentCalculator() = default;

    static int calculateStreetRent(const int baseRent, const int houseCount) {
        // rent = baseRent * 2^(houses)
        int rent = baseRent * static_cast<int>(std::pow(2, houseCount));
        // Hotel (5 buildings) has fixed rent
        if (houseCount == 5) {
            rent+=500;
        }
        return rent;
    }

    static int calculateRailroadRent(const int baseRent, const int ownedRailroads) {
        // rent = baseRent * 2^(n-1) where n is number of railroads owned
        return baseRent * static_cast<int>(std::pow(2, ownedRailroads - 1));
    }

    static int calculateUtilityRent(int baseRentMultiplier, const int diceRoll) {
        // rent = baseRentMultiplier*diceRoll
        return baseRentMultiplier * diceRoll;
    }
};

#endif // RENT_CALCULATOR_HPP
