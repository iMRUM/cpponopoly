#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>
#include "../../include/utils/registries/PlayerRegistry.hpp"
#include "../../include/utils/registries/PropertyRegistry.hpp"
TEST_CASE("Registry operations", "[registry]") {
    class TestObject {};
    class TestRegistry : public monopoly::Registry<TestObject, monopoly::ID<struct TestTag>> {};

    TestRegistry registry;
    auto obj1 = std::make_shared<TestObject>();
    auto obj2 = std::make_shared<TestObject>();

    SECTION("Registration") {
        auto id1 = registry.registerObject(obj1);
        REQUIRE(registry.getSize() == 1);
        REQUIRE(registry.exists(id1));
        REQUIRE_THROWS_AS(registry.registerObject(nullptr), std::invalid_argument);
    }

    SECTION("Retrieval") {
        auto id = registry.registerObject(obj1);
        REQUIRE(registry.getObject(id) == obj1);
        REQUIRE_THROWS_AS(registry.getObject(monopoly::ID<struct TestTag>(999)), std::runtime_error);
    }

    SECTION("Removal") {
        auto id = registry.registerObject(obj1);
        REQUIRE(registry.remove(id));
        REQUIRE_FALSE(registry.exists(id));
        REQUIRE_FALSE(registry.remove(id));
    }

    SECTION("Multiple objects") {
        auto id1 = registry.registerObject(obj1);
        auto id2 = registry.registerObject(obj2);
        REQUIRE(registry.getSize() == 2);
        REQUIRE(id1.getValue() != id2.getValue());
        REQUIRE(registry.getObject(id1) == obj1);
        REQUIRE(registry.getObject(id2) == obj2);
    }

    SECTION("Get all objects") {
        registry.registerObject(obj1);
        registry.registerObject(obj2);
        const auto& objects = registry.getAllObjects();
        REQUIRE(objects.size() == 2);
        REQUIRE(std::all_of(objects.begin(), objects.end(),
            [](const auto& pair) { return pair.second != nullptr; }));
    }
}

TEST_CASE("PlayerRegistry", "[registry]") {
    monopoly::PlayerRegistry registry;

    SECTION("Player registration") {
        auto id = registry.registerPlayer("Alice");
        auto player = registry.getObject(id);
        REQUIRE(player->getName() == "Alice");
    }
}

class TestProperty : public monopoly::Property {
public:
    TestProperty(const std::string& name, int position, int price, int base_rent)
        : Property(name, position, price, base_rent, monopoly::PropertyID(1)) {}
};

TEST_CASE("PropertyRegistry", "[registry]") {
    monopoly::PropertyRegistry registry;
    auto prop1 = std::make_shared<TestProperty>("Property1", 1, 100, 10);
    auto prop2 = std::make_shared<TestProperty>("Property2", 2, 200, 20);
    monopoly::PlayerID player1(1);
    monopoly::PlayerID player2(2);
    monopoly::ColorGroupID group1(1);

    SECTION("Ownership") {
        auto id1 = registry.registerObject(prop1);
        auto id2 = registry.registerObject(prop2);

        REQUIRE_FALSE(registry.hasOwner(id1));

        registry.setOwner(id1, player1);
        REQUIRE(registry.hasOwner(id1));
        REQUIRE(registry.getOwner(id1) == player1);
        REQUIRE(registry.getProperties(player1).size() == 1);

        registry.removeOwner(id1);
        REQUIRE_FALSE(registry.hasOwner(id1));
    }

    SECTION("Color groups") {
        auto id1 = registry.registerObject(prop1);
        auto id2 = registry.registerObject(prop2);

        registry.assignToColorGroup(id1, group1);
        registry.assignToColorGroup(id2, group1);

        REQUIRE(registry.getPropertyGroup(id1) == group1);
        REQUIRE(registry.getPropertiesInGroup(group1).size() == 2);

        registry.setOwner(id1, player1);
        registry.setOwner(id2, player1);
        REQUIRE(registry.isGroupComplete(group1, player1));

        registry.setOwner(id2, player2);
        REQUIRE_FALSE(registry.isGroupComplete(group1, player1));
    }

    SECTION("Property removal") {
        auto id = registry.registerObject(prop1);
        registry.setOwner(id, player1);
        registry.assignToColorGroup(id, group1);

        REQUIRE(registry.remove(id));
        REQUIRE_FALSE(registry.hasOwner(id));
        REQUIRE(registry.getPropertiesInGroup(group1).empty());
    }
}