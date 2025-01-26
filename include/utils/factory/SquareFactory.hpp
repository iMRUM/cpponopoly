#pragma once
#include <memory>
#include <string>
#include "../../model/squares/Square.hpp"
#include "../../model/squares/Street.hpp"
#include "../../model/squares/Railroad.hpp"
#include "../../model/squares/Utility.hpp"
#include "../../model/squares/SpecialSquare.hpp"

namespace monopoly {

class SquareFactory {
public:
    static std::unique_ptr<Street> createStreet(
        const std::string& name,
        int position,
        const PropertyID& propertyId,
        int price,
        int baseRent,
        int houseCost) {
        return std::make_unique<Street>(
            name,
            position,
            price,
            baseRent,
            houseCost,
            propertyId
        );
    }

    static std::unique_ptr<Railroad> createRailroad(
        const std::string& name,
        int position,
        const PropertyID& propertyId) {
        return std::make_unique<Railroad>(
            name,
            propertyId,
            position
        );
    }

    static std::unique_ptr<Utility> createUtility(
        const std::string& name,
        int position,
        const PropertyID& propertyId) {
        return std::make_unique<Utility>(
            name,
            position,
            propertyId
        );
    }

    static std::unique_ptr<SpecialSquare> createSpecialSquare(
        const std::string& name,
        int position) {
        return std::make_unique<SpecialSquare>(
            name,
            position,
            getSpecialSquareType(name)
        );
    }

private:
    static SpecialSquareType getSpecialSquareType(const std::string& name) {
        if (name == "GO") return SpecialSquareType::GO;
        if (name == "Community Chest") return SpecialSquareType::COMMUNITY_CHEST;
        if (name == "Income Tax") return SpecialSquareType::INCOME_TAX;
        if (name == "Luxury Tax") return SpecialSquareType::LUXURY_TAX;
        if (name == "Jail") return SpecialSquareType::JAIL;
        if (name == "Go To Jail") return SpecialSquareType::GO_TO_JAIL;
        if (name == "Free Parking") return SpecialSquareType::FREE_PARKING;
        if (name == "Chance") return SpecialSquareType::CHANCE;

        throw std::invalid_argument("Invalid special square name: " + name);
    }
};

} // namespace monopoly