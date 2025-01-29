#include <catch2/catch_test_macros.hpp>
#include "SquareFactory.hpp"

using namespace monopoly;

TEST_CASE("SquareFactory - Street Creation", "[SquareFactory]") {
    SECTION("Valid street creation") {
        auto street = SquareFactory::createStreet("Boardwalk", 39, PropertyID(), 400, 50, 200);
        
        REQUIRE(street->getName() == "Boardwalk");
        REQUIRE(street->getPosition() == 39);
        REQUIRE(street->getPrice() == 400);
        REQUIRE(street->getBaseRent() == 50);
        REQUIRE(street->getHouseCost() == 200);
        REQUIRE_FALSE(street->isOwned());
    }
    
    SECTION("Invalid position throws") {
        REQUIRE_THROWS_AS(
            SquareFactory::createStreet("Test", -1, PropertyID(), 100, 10, 50),
            std::invalid_argument
        );
        REQUIRE_THROWS_AS(
            SquareFactory::createStreet("Test", 40, PropertyID(), 100, 10, 50),
            std::invalid_argument
        );
    }
}

TEST_CASE("SquareFactory - Railroad Creation", "[SquareFactory]") {
    SECTION("Valid railroad creation") {
        auto railroad = SquareFactory::createRailroad("Reading Railroad", 5, PropertyID());
        
        REQUIRE(railroad->getName() == "Reading Railroad");
        REQUIRE(railroad->getPosition() == 5);
        REQUIRE(railroad->getPrice() == 200);  // Default price
        REQUIRE(railroad->getBaseRent() == 50); // Default base rent
        REQUIRE_FALSE(railroad->isOwned());
    }
    
    SECTION("Invalid position throws") {
        REQUIRE_THROWS_AS(
            SquareFactory::createRailroad("Test", -1, PropertyID()),
            std::invalid_argument
        );
    }
}

TEST_CASE("SquareFactory - Utility Creation", "[SquareFactory]") {
    SECTION("Valid utility creation") {
        auto utility = SquareFactory::createUtility("Electric Company", 12, PropertyID());
        
        REQUIRE(utility->getName() == "Electric Company");
        REQUIRE(utility->getPosition() == 12);
        REQUIRE(utility->getPrice() == 150);  // Default price
        REQUIRE(utility->getBaseRent() == 10); // Default multiplier
        REQUIRE_FALSE(utility->isOwned());
    }
    
    SECTION("Invalid position throws") {
        REQUIRE_THROWS_AS(
            SquareFactory::createUtility("Test", 40, PropertyID()),
            std::invalid_argument
        );
    }
}

TEST_CASE("SquareFactory - Special Square Creation", "[SquareFactory]") {
    SECTION("Valid special square creation") {
        auto go = SquareFactory::createSpecialSquare("GO", 0);
        REQUIRE(go->getName() == "GO");
        REQUIRE(go->getPosition() == 0);
        REQUIRE(go->getType() == SpecialSquareType::GO);
        
        auto chance = SquareFactory::createSpecialSquare("Chance", 7);
        REQUIRE(chance->getType() == SpecialSquareType::CHANCE);
    }
    
    SECTION("Invalid special square name throws") {
        REQUIRE_THROWS_AS(
            SquareFactory::createSpecialSquare("Invalid", 0),
            std::invalid_argument
        );
    }
    
    SECTION("Invalid position throws") {
        REQUIRE_THROWS_AS(
            SquareFactory::createSpecialSquare("GO", -1),
            std::invalid_argument
        );
    }
}

TEST_CASE("SquareFactory - Special Square Types", "[SquareFactory]") {
    SECTION("All special square types are created correctly") {
        std::vector<std::pair<std::string, SpecialSquareType>> squares = {
            {"GO", SpecialSquareType::GO},
            {"Community Chest", SpecialSquareType::COMMUNITY_CHEST},
            {"Income Tax", SpecialSquareType::INCOME_TAX},
            {"Luxury Tax", SpecialSquareType::LUXURY_TAX},
            {"Jail", SpecialSquareType::JAIL},
            {"Go To Jail", SpecialSquareType::GO_TO_JAIL},
            {"Free Parking", SpecialSquareType::FREE_PARKING},
            {"Chance", SpecialSquareType::CHANCE}
        };
        
        for (const auto& [name, type] : squares) {
            auto square = SquareFactory::createSpecialSquare(name, 0);
            REQUIRE(square->getName() == name);
            REQUIRE(square->getType() == type);
        }
    }
}