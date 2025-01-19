#include <catch2/catch_test_macros.hpp>
#include "../../include/model/Game.hpp"
#include "../../include/view/Gui.hpp"
#include "../../include/model/Player.hpp"
#include "../../include/model/squares/Square.hpp"

namespace monopoly {
    class MockPlayer : public Player {
    public:
        MockPlayer(const std::string &name, int id) : Player(name), id_(id) {
        }

    private:
        int id_;
    };

    class MockSquare : public Square {
    public:
        MockSquare(const std::string &name, int price) : name_(name), price_(price) {
        }

        std::string getName() const override { return name_; }
        int getPrice() const { return price_; }

    private:
        std::string name_;
        int price_;
    };

    TEST_CASE("GUI Singleton", "[gui]") {
        SECTION("getInstance creates singleton") {
            auto &gui1 = Gui::getInstance();
            auto &gui2 = Gui::getInstance();

            REQUIRE(&gui1 == &gui2);
        }

        SECTION("cleanup removes instance") {
            auto &gui1 = Gui::getInstance();
            Gui::cleanup();
            auto &gui2 = Gui::getInstance();

            REQUIRE(&gui1 != &gui2);
        }
    }

    TEST_CASE("GUI Event Handling", "[gui]") {
        auto &gui = Gui::getInstance();

        SECTION("PlayerMoveEvent updates player position") {
            MockPlayer player("Test", 0);
            PlayerMoveEvent event{player, 0, 5};

            gui.onEvent(event);
            // Visual verification required - can't easily test SFML rendering
        }

        SECTION("PropertyPurchaseEvent displays message") {
            MockPlayer player("Test", 0);
            MockSquare property("Boardwalk", 400);
            PropertyPurchaseEvent event{player, property, 400};

            gui.onEvent(event);
            // Visual verification required
        }

        SECTION("BankruptcyEvent displays message") {
            MockPlayer player("Test", 0);
            BankruptcyEvent event{player, 1000};

            gui.onEvent(event);
            // Visual verification required
        }

        SECTION("DiceRollEvent updates dice values") {
            DiceRollEvent event{3, 4};
            gui.onEvent(event);
            // Visual verification required
        }
    }

    TEST_CASE("GUI User Input", "[gui]") {
        auto &gui = Gui::getInstance();

        SECTION("getYesNoResponse handles user input") {
            // Manual testing required - can't automate keyboard input
        }

        SECTION("displayError shows error message") {
            gui.displayError("Test Error");
            // Visual verification required
        }
    }

    // Clean up after all tests
    TEST_CASE("GUI Cleanup", "[gui]") {
        Gui::cleanup();
    }
}
