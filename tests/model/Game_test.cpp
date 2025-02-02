#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>
#include "../../include/model/GameModel.hpp"

namespace monopoly {
    class GameTest {
    protected:
        GameModel &game = GameModel::getInstance();

        void setup2Players() {
            game.resetGame();
            game.initializeGame(2);
            game.addPlayers(2);
            game.startGame();
        }

        void resetGame() {
            game.endGame();
            REQUIRE_NOTHROW(game.initializeGame(2));
        }
    };

    TEST_CASE_METHOD(GameTest, "GameModel Initialization") {
        SECTION("GameModel starts with correct number of players") {
            REQUIRE_NOTHROW(game.initializeGame(2));
            REQUIRE(game.getPlayersCount() == 0);

            REQUIRE_NOTHROW(game.addPlayers(2));
            REQUIRE(game.getPlayersCount() == 2);
        }

        SECTION("Cannot add more than 8 players") {
            game.resetGame();
            REQUIRE_NOTHROW(game.initializeGame(8));
            REQUIRE_NOTHROW(game.addPlayers(8));
            REQUIRE_THROWS_AS(game.addPlayers(1), std::runtime_error);
        }
    }

    TEST_CASE_METHOD(GameTest, "GameModel State Management") {
        SECTION("GameModel state transitions correctly") {
            REQUIRE(game.isGameInitialized());
            REQUIRE(!game.isGameStarted());
            REQUIRE(!game.isGameOver());

            game.initializeGame(2);
            REQUIRE(game.isGameInitialized());

            game.startGame();
            REQUIRE(game.isGameStarted());

            game.endGame();
            REQUIRE(game.isGameOver());
        }
    }

    TEST_CASE_METHOD(GameTest, "Player Turn Management") {
        setup2Players();

        SECTION("Initial player index is 0") {
            REQUIRE(game.getCurrentPlayerIndex() == 0);
        }

        SECTION("Next turn increments player index") {
            game.nextTurn();
            REQUIRE(game.getCurrentPlayerIndex() == 1);

            game.nextTurn();
            REQUIRE(game.getCurrentPlayerIndex() == 0);
        }
    }

    TEST_CASE_METHOD(GameTest, "Property Management") {
        setup2Players();
        Player &current_player = game.getCurrentPlayer();

        SECTION("Player can buy affordable property") {
            auto *property = dynamic_cast<Property *>(game.getSquareAt(1)); // Mediterranean Avenue
            REQUIRE(property != nullptr);
            REQUIRE(!property->isOwned());
            REQUIRE(current_player.getBalance() >= property->getPrice());

            REQUIRE(game.canBuyProperty(current_player));
        }

        SECTION("Cannot buy already owned property") {
            auto *property = dynamic_cast<Property *>(game.getSquareAt(1));
            REQUIRE(property != nullptr);

            // First player buys property
            game.buyCurrentProperty();
            REQUIRE(property->isOwned());

            // Second player tries to buy
            game.nextTurn();
            Player &next_player = game.getCurrentPlayer();
            REQUIRE(!game.canBuyProperty(next_player));
        }
    }

    TEST_CASE_METHOD(GameTest, "Rent Calculation") {
        setup2Players();

        SECTION("Street rent calculation") {
            auto *property = dynamic_cast<Street *>(game.getSquareAt(1));
            REQUIRE(property != nullptr);

            // Buy property
            Player &owner = game.getCurrentPlayer();
            game.buyCurrentProperty();

            // Next player lands on property
            game.nextTurn();
            REQUIRE(game.mustPayRent());
            REQUIRE(game.calculateCurrentRent() == property->getBaseRent());
        }

        SECTION("Railroad rent calculation") {
            auto *railroad = dynamic_cast<Railroad *>(game.getSquareAt(5));
            REQUIRE(railroad != nullptr);

            // Buy railroad
            Player &owner = game.getCurrentPlayer();
            game.buyCurrentProperty();

            // Next player lands on railroad
            game.nextTurn();
            REQUIRE(game.mustPayRent());
            REQUIRE(game.calculateCurrentRent() == 50); // Base rent for 1 railroad
        }
    }

    TEST_CASE_METHOD(GameTest, "Building Houses") {
        setup2Players();
        Player &current_player = game.getCurrentPlayer();

        SECTION("Cannot build without complete color group") {
            auto *property = dynamic_cast<Street *>(game.getSquareAt(1));
            REQUIRE(property != nullptr);

            game.buyCurrentProperty();
            REQUIRE(!game.canBuildOnProperty(*property, current_player));
        }

        SECTION("Can build with complete color group") {
            // Buy both brown properties (Mediterranean and Baltic)
            auto *mediterranean = dynamic_cast<Street *>(game.getSquareAt(1));
            auto *baltic = dynamic_cast<Street *>(game.getSquareAt(3));
            REQUIRE(mediterranean != nullptr);
            REQUIRE(baltic != nullptr);

            game.buyCurrentProperty();
            game.buyCurrentProperty();

            REQUIRE(game.canBuildOnProperty(*mediterranean, current_player));
            REQUIRE(game.canBuildOnProperty(*baltic, current_player));
        }
    }

    TEST_CASE_METHOD(GameTest, "Bankruptcy Handling") {
        setup2Players();

        SECTION("Player goes bankrupt from rent") {
            Player &bankrupt_player = game.getCurrentPlayer();
            bankrupt_player.setBalance(10); // Set very low balance

            auto *property = dynamic_cast<Property *>(game.getSquareAt(1));
            REQUIRE(property != nullptr);

            // Other player owns property
            game.nextTurn();
            Player &owner = game.getCurrentPlayer();
            game.buyCurrentProperty();

            // Bankrupt player lands on expensive property
            game.nextTurn();
            REQUIRE(game.mustPayRent());
            int rent = game.calculateCurrentRent();
            REQUIRE(bankrupt_player.getBalance() < rent);

            // Pay rent should trigger bankruptcy
            game.payCurrentRent();
            REQUIRE(bankrupt_player.isBankrupt());
        }
    }
} // namespace monopoly
