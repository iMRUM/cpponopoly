#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>
#include "../../include/utils/Id.hpp"
TEST_CASE("ID class operations", "[id]") {
    SECTION("Construction and equality") {
        monopoly::ID<struct TestTag> id1(1);
        monopoly::ID<struct TestTag> id2(1);
        monopoly::ID<struct TestTag> id3(2);

        REQUIRE(id1 == id2);
        REQUIRE(id1 != id3);
        REQUIRE(id1.getValue() == 1);
    }

    SECTION("Comparison operators") {
        monopoly::ID<struct TestTag> id1(1);
        monopoly::ID<struct TestTag> id2(2);

        REQUIRE(id1 < id2);
        REQUIRE(id2 > id1);
    }

    SECTION("Hash function") {
        monopoly::ID<struct TestTag> id(42);
        monopoly::ID<struct TestTag>::Hash hasher;
        size_t hash = hasher(id);
        REQUIRE(hash == std::hash<uint32_t>()(42));
    }

    SECTION("Type safety") {
        monopoly::SquareID square_id(1);
        monopoly::PropertyID property_id(1);

        // Following line should not compile:
        // bool comparison = square_id == property_id;

        // Different tag types create distinct types
        static_assert(!std::is_same_v<monopoly::SquareID, monopoly::PropertyID>);
    }
}