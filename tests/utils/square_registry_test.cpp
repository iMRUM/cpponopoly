#include <catch2/catch_test_macros.hpp>
#include "../../include/utils/registry/SquareRegistry.hpp"
#include <memory>
#include <stdexcept>

using namespace monopoly;

TEST_CASE("SquareRegistry basic operations", "[SquareRegistry]") {
    SquareRegistry registry;
    
    SECTION("Initial state") {
        CHECK(registry.empty());
        CHECK(registry.size() == 0);
    }
    
    SECTION("Register and retrieve squares") {
        auto street = std::make_unique<Street>("Boardwalk", 39, 400, 50, 200);
        registry.registerItem(std::move(street));
        
        CHECK(registry.size() == 1);
        CHECK_FALSE(registry.empty());
        CHECK(registry.getByPosition(39).getName() == "Boardwalk");
    }
    
    SECTION("Cannot register null square") {
        CHECK_THROWS_AS(registry.registerItem(nullptr), std::invalid_argument);
    }
    
    SECTION("Cannot register square at invalid position") {
        auto street = std::make_unique<Street>("Boardwalk", 39, 400, 50, 200);
        registry.registerItem(std::move(street));
        CHECK_THROWS_AS(
            registry.registerItem(std::make_unique<Street>("Invalid", -1, 100, 10, 50)),
            std::invalid_argument
        );
        CHECK_THROWS_AS(
            registry.registerItem(std::make_unique<Street>("Invalid", 39, 100, 10, 50)),
            std::invalid_argument
        );
    }
}

TEST_CASE("SquareRegistry complete board setup", "[SquareRegistry]") {
    SquareRegistry registry;
    
    // GO (Position 0)
    registry.registerItem(std::make_unique<SpecialSquare>("GO", 0, SpecialSquareType::GO));
    
    // Brown properties
    registry.registerItem(std::make_unique<Street>("Mediterranean Avenue", 1, 60, 2, 50));
    registry.registerItem(std::make_unique<Street>("Baltic Avenue", 3, 60, 4, 50));
    
    // First railroad
    registry.registerItem(std::make_unique<Railroad>("Reading Railroad", 5, 200));
    
    // Light blue properties
    registry.registerItem(std::make_unique<Street>("Oriental Avenue", 6, 100, 6, 50));
    registry.registerItem(std::make_unique<Street>("Vermont Avenue", 8, 100, 6, 50));
    registry.registerItem(std::make_unique<Street>("Connecticut Avenue", 9, 120, 8, 50));
    
    // Jail
    registry.registerItem(std::make_unique<SpecialSquare>("Jail", 10, SpecialSquareType::JAIL));
    
    // Pink properties
    registry.registerItem(std::make_unique<Street>("St. Charles Place", 11, 140, 10, 100));
    registry.registerItem(std::make_unique<Street>("States Avenue", 13, 140, 10, 100));
    registry.registerItem(std::make_unique<Street>("Virginia Avenue", 14, 160, 12, 100));
    
    // Second railroad
    registry.registerItem(std::make_unique<Railroad>("Pennsylvania Railroad", 15, 15));
    
    // Orange properties
    registry.registerItem(std::make_unique<Street>("St. James Place", 16, 180, 14, 100));
    registry.registerItem(std::make_unique<Street>("Tennessee Avenue", 18, 180, 14, 100));
    registry.registerItem(std::make_unique<Street>("New York Avenue", 19, 200, 16, 100));
    
    // Free Parking
    registry.registerItem(std::make_unique<SpecialSquare>("Free Parking", 20, SpecialSquareType::FREE_PARKING));
    
    SECTION("Board size verification") {
        CHECK(registry.size() == 16);  // Partial board setup
        
        // Verify specific squares
        CHECK(registry.isSpecialSquare(0));  // GO
        CHECK(registry.isStreet(1));         // Mediterranean
        CHECK(registry.isRailroad(5));       // Reading Railroad
        CHECK(registry.isSpecialSquare(10)); // Jail
    }
    
    SECTION("Square type checks") {
        CHECK(registry.isStreet(1));
        CHECK_FALSE(registry.isRailroad(1));
        CHECK(registry.isRailroad(5));
        CHECK_FALSE(registry.isStreet(5));
        CHECK(registry.isSpecialSquare(0));
        CHECK_FALSE(registry.isProperty(0));
    }
    
    SECTION("Property retrieval") {
        auto& street = registry.getStreetByPosition(1);
        CHECK(street.getName() == "Mediterranean Avenue");
        CHECK(street.getPrice() == 60);
        CHECK(street.getBaseRent() == 2);
        CHECK(street.getHouseCost() == 50);
        
        auto& railroad = registry.getRailroadByPosition(5);
        CHECK(railroad.getName() == "Reading Railroad");
        CHECK(railroad.getPrice() == 200);
        CHECK(railroad.getBaseRent() == 50);
    }
    
    SECTION("Invalid retrievals") {
        CHECK_THROWS_AS(registry.getStreetByPosition(5), std::runtime_error);  // Railroad position
        CHECK_THROWS_AS(registry.getRailroadByPosition(1), std::runtime_error); // Street position
        CHECK_THROWS_AS(registry.getByPosition(-1), std::invalid_argument);     // Invalid position
    }
}

TEST_CASE("SquareRegistry utilities and special cases", "[SquareRegistry]") {
    SquareRegistry registry;
    
    SECTION("Utility squares") {
        registry.registerItem(std::make_unique<Utility>("Electric Company", 12, 150));
        registry.registerItem(std::make_unique<Utility>("Water Works", 28, 150));
        
        CHECK(registry.isUtility(12));
        CHECK(registry.isUtility(28));
        CHECK_FALSE(registry.isUtility(0));
        
        auto& electric = registry.getUtilityByPosition(12);
        CHECK(electric.getName() == "Electric Company");
        CHECK(electric.getPrice() == 150);
        CHECK(electric.getBaseRent() == 10);  // Multiplier for utilities
    }
    
    SECTION("Special squares") {
        registry.registerItem(std::make_unique<SpecialSquare>("Chance", 7, SpecialSquareType::CHANCE));
        registry.registerItem(std::make_unique<SpecialSquare>("Community Chest", 2, SpecialSquareType::COMMUNITY_CHEST));
        registry.registerItem(std::make_unique<SpecialSquare>("Income Tax", 4, SpecialSquareType::INCOME_TAX));
        
        CHECK(registry.isSpecialSquare(7));
        CHECK(registry.isSpecialSquare(2));
        CHECK(registry.isSpecialSquare(4));
        
        auto& chance = registry.getSpecialSquareByPosition(7);
        CHECK(chance.getName() == "Chance");
        CHECK(chance.getType() == SpecialSquareType::CHANCE);
        
        auto& tax = registry.getSpecialSquareByPosition(4);
        CHECK(tax.getName() == "Income Tax");
        CHECK(tax.getType() == SpecialSquareType::INCOME_TAX);
    }
}
TEST_CASE("SquareRegistry iterator operations", "[SquareRegistry]") {
    SquareRegistry registry;

    SECTION("Iterator over empty registry") {
        CHECK(std::distance(registry.begin(), registry.end()) == 0);
    }

    SECTION("Iterator over squares") {
        registry.registerItem(std::make_unique<Street>("Street1", 0, 100, 10, 50));
        registry.registerItem(std::make_unique<Street>("Street2", 1, 120, 12, 60));

        int count = 0;
        for (const Square& square : registry) {
            CHECK(square.getName() == "Street" + std::to_string(count + 1));
            count++;
        }
        CHECK(count == 2);
    }

    SECTION("Const iterator") {
        registry.registerItem(std::make_unique<Street>("Street1", 0, 100, 10, 50));
        const SquareRegistry& const_registry = registry;

        for (const Square& square : const_registry) {
            CHECK(square.getName() == "Street1");
        }
    }
}