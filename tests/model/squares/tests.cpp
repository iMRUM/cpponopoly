#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>
#include "../../../include/model/squares/Street.hpp"
#include "../../../include/model/squares/Railroad.hpp"
#include "../../../include/model/squares/Utility.hpp"


class TestProperty : public monopoly::Property {
public:
    TestProperty(const std::string& name, int position, int price, int base_rent)
        : Property(name, position, price, base_rent, monopoly::PropertyID{1}) {}
};

TEST_CASE("Square construction and basic operations", "[square]") {
    SECTION("Valid construction") {
        auto* square = new Square("Test Square", 5);
        REQUIRE(square->getName() == "Test Square");
        REQUIRE(square->getPosition() == 5);
        delete square;
    }

    SECTION("Invalid position - too low") {
        REQUIRE_THROWS_AS(new Square("Invalid", -1), std::invalid_argument);
    }

    SECTION("Invalid position - too high") {
        REQUIRE_THROWS_AS(new Square("Invalid", BOARD_SIZE), std::invalid_argument);
    }
}

TEST_CASE("Property construction and basic operations", "[property]") {
    SECTION("Valid construction") {
        auto* property = new TestProperty("Test Property", 5, 200, 20);
        REQUIRE(property->getName() == "Test Property");
        REQUIRE(property->getPosition() == 5);
        REQUIRE(property->getPrice() == 200);
        REQUIRE(property->getBaseRent() == 20);
        REQUIRE(property->getId() == monopoly::PropertyID{1});
        delete property;
    }

    SECTION("Invalid price") {
        REQUIRE_THROWS_AS(new TestProperty("Invalid", 5, -200, 20), std::invalid_argument);
    }

    SECTION("Invalid rent") {
        REQUIRE_THROWS_AS(new TestProperty("Invalid", 5, 200, -20), std::invalid_argument);
    }
}

TEST_CASE("Property ownership", "[property]") {
    auto* property = new TestProperty("Test Property", 5, 200, 20);

    SECTION("Initial state") {
        REQUIRE(property->getOwnerId().getValue() == 0);
    }

    SECTION("Set and get owner") {
        monopoly::PlayerID player_id{1};
        property->setOwnerId(player_id);
        REQUIRE(property->getOwnerId() == player_id);
    }

    delete property;
}

TEST_CASE("Property mutations", "[property]") {
    auto* property = new TestProperty("Test Property", 5, 200, 20);
    
    SECTION("Price mutations") {
        property->setPrice(300);
        REQUIRE(property->getPrice() == 300);
        REQUIRE_THROWS_AS(property->setPrice(-100), std::invalid_argument);
    }
    
    SECTION("Base rent mutations") {
        property->setBaseRent(30);
        REQUIRE(property->getBaseRent() == 30);
        REQUIRE_THROWS_AS(property->setBaseRent(-10), std::invalid_argument);
    }
    
    delete property;
}
TEST_CASE("Railroad construction and operations", "[railroad]") {
    auto* railroad = new monopoly::Railroad("Reading Railroad", monopoly::PropertyID{1}, 5);

    SECTION("Default values") {
        REQUIRE(railroad->getPrice() == 200);
        REQUIRE(railroad->getBaseRent() == 50);
    }

    SECTION("Custom values") {
        auto* custom_railroad = new monopoly::Railroad("Custom", monopoly::PropertyID{2}, 10, 300, 75);
        REQUIRE(custom_railroad->getPrice() == 300);
        REQUIRE(custom_railroad->getBaseRent() == 75);
        delete custom_railroad;
    }

    delete railroad;
}

TEST_CASE("Street construction and operations", "[street]") {
    auto* street = new monopoly::Street("Boardwalk", 5, 400, 50, 200, monopoly::PropertyID{1});

    SECTION("Initial state") {
        REQUIRE(street->getHouseCost() == 200);
        REQUIRE(street->getHouses() == 0);
        REQUIRE_FALSE(street->hasHotel());
    }

    SECTION("Building houses") {
        for(int i = 0; i < 4; i++) {
            street->addHouse();
            REQUIRE(street->getHouses() == i + 1);
            REQUIRE_FALSE(street->hasHotel());
        }
        street->addHouse();
        REQUIRE(street->hasHotel());
    }

    delete street;
}

TEST_CASE("Utility construction and operations", "[utility]") {
    auto* utility = new monopoly::Utility("Electric Company", 12, monopoly::PropertyID{1});

    SECTION("Default values") {
        REQUIRE(utility->getPrice() == 150);
        REQUIRE(utility->getBaseRent() == 10);
    }

    SECTION("Custom values") {
        auto* custom_utility = new monopoly::Utility("Water Works", 28, monopoly::PropertyID{2}, 200, 15);
        REQUIRE(custom_utility->getPrice() == 200);
        REQUIRE(custom_utility->getBaseRent() == 15);
        delete custom_utility;
    }

    delete utility;
}