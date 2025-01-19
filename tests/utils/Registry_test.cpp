#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>
#include "../../include/utils/registries/Registry.hpp"
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
        REQUIRE(registry.get(id) == obj1);
        REQUIRE_THROWS_AS(registry.get(monopoly::ID<struct TestTag>(999)), std::runtime_error);
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
        REQUIRE(registry.get(id1) == obj1);
        REQUIRE(registry.get(id2) == obj2);
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