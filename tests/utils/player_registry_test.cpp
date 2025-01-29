#include <catch2/catch_test_macros.hpp>
#include "../../include/utils/registry/PlayerRegistry.hpp"

namespace monopoly{
    TEST_CASE("PlayerRegistry basic operations", "[player-registry]") {
        PlayerRegistry registry;

        SECTION("Initially empty") {
            CHECK(registry.empty());
            CHECK(registry.size() == 0);
        }

        SECTION("Register single player") {
            auto player = std::make_unique<Player>("Player1", 1);
            registry.registerItem(std::move(player));

            CHECK_FALSE(registry.empty());
            CHECK(registry.size() == 1);
            CHECK(registry.exists(1));
            CHECK(registry.getById(1).getName() == "Player1");
            CHECK(registry.getById(1).getBalance() == 1500);
        }

        SECTION("Get player by ID") {
            auto player = std::make_unique<Player>("Player1", 1);
            registry.registerItem(std::move(player));

            CHECK(registry.getById(1).getName() == "Player1");
            CHECK_THROWS_AS(registry.getById(2), std::runtime_error);
        }

        SECTION("Get player by index") {
            auto player = std::make_unique<Player>("Player1", 1);
            registry.registerItem(std::move(player));

            CHECK(registry.getByIndex(0).getName() == "Player1");
            CHECK_THROWS_AS(registry.getByIndex(1), std::out_of_range);
        }
    }

    TEST_CASE("PlayerRegistry invalid operations", "[player-registry]") {
        PlayerRegistry registry;

        SECTION("Null player") {
            CHECK_THROWS_AS(registry.registerItem(nullptr), std::invalid_argument);
        }

        SECTION("Duplicate ID") {
            auto player1 = std::make_unique<Player>("Player1", 1);
            registry.registerItem(std::move(player1));

            auto player2 = std::make_unique<Player>("Player2", 1);
            CHECK_THROWS_AS(registry.registerItem(std::move(player2)), std::runtime_error);
        }

        SECTION("Maximum players") {
            for (int i = 1; i <= 8; ++i) {
                auto player = std::make_unique<Player>("Player" + std::to_string(i), i);
                registry.registerItem(std::move(player));
            }

            auto extraPlayer = std::make_unique<Player>("Player9", 9);
            CHECK_THROWS_AS(registry.registerItem(std::move(extraPlayer)), std::runtime_error);
        }
    }

    TEST_CASE("PlayerRegistry state management", "[player-registry]") {
        PlayerRegistry registry;

        SECTION("Player state persistence") {
            auto player = std::make_unique<Player>("Player1", 1);
            player->increaseBalance(500);
            player->setPosition(5);
            registry.registerItem(std::move(player));

            const auto &storedPlayer = registry.getById(1);
            CHECK(storedPlayer.getBalance() == 2000);
            CHECK(storedPlayer.getPosition() == 5);
        }

        SECTION("Remove and clear") {
            auto player = std::make_unique<Player>("Player1", 1);
            registry.registerItem(std::move(player));

            registry.remove(1);
            CHECK(registry.empty());

            for (int i = 1; i <= 3; ++i) {
                auto p = std::make_unique<Player>("Player" + std::to_string(i), i);
                registry.registerItem(std::move(p));
            }

            registry.clear();
            CHECK(registry.empty());
        }
    }

    TEST_CASE("PlayerRegistry iterator operations", "[player-registry]") {
        PlayerRegistry registry;

        SECTION("Iterator over empty registry") {
            CHECK(std::distance(registry.begin(), registry.end()) == 0);
        }

        SECTION("Iterator over players") {
            for (int i = 1; i <= 3; ++i) {
                registry.registerItem(std::make_unique<Player>("Player" + std::to_string(i), i));
            }

            int count = 0;
            for (const Player &player: registry) {
                CHECK(player.getName() == "Player" + std::to_string(player.getId()));
                count++;
            }
            CHECK(count == 3);
        }

        SECTION("Const iterator") {
            registry.registerItem(std::make_unique<Player>("Player1", 1));
            const PlayerRegistry &const_registry = registry;

            for (const Player &player: const_registry) {
                CHECK(player.getName() == "Player1");
            }
        }
    }
} // namespace monopoly::test
