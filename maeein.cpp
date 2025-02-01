#include "include/view/Gui.hpp"
#include "view/Gui.hpp"
#include "include/model/Player.hpp"
#include <memory>
#include <chrono>
#include <thread>
#include <iostream>
#include <vector>
#include <random>

using namespace monopoly;

class GameSimulator {
private:
    Gui& gui;
    std::vector<std::unique_ptr<Player>> players;
    size_t currentPlayerIndex;
    std::mt19937 rng{std::random_device{}()};

    // Roll dice and return {dice1, dice2}
    std::pair<int, int> rollDice() {
        std::uniform_int_distribution<int> dist(1, 6);
        return {dist(rng), dist(rng)};
    }

public:
    explicit GameSimulator(Gui& g) : gui(g), currentPlayerIndex(0) {
        // Initialize players with starting money of 1500
        players.emplace_back(std::make_unique<Player>("Player 1"));
        players.emplace_back(std::make_unique<Player>("Player 2"));
        players.emplace_back(std::make_unique<Player>("Player 3"));
        players.emplace_back(std::make_unique<Player>("Player 4"));
    }

    void simulateTurn() {
        auto& currentPlayer = *players[currentPlayerIndex];

        try {
            // Roll dice and move
            auto [dice1, dice2] = rollDice();
            DiceRollEvent diceEvent{dice1, dice2};
            gui.onEvent(diceEvent);
            std::this_thread::sleep_for(std::chrono::seconds(1));

            int oldPosition = currentPlayer.getPosition();
            int spaces = dice1 + dice2;
            currentPlayer.moveSteps(spaces);

            // Notify GUI of movement
            PlayerMoveEvent moveEvent{
                currentPlayer,
                oldPosition,
                currentPlayer.getPosition()
            };
            gui.onEvent(moveEvent);
            std::this_thread::sleep_for(std::chrono::seconds(1));

            // Simulate property purchase if landed on purchasable property
            // (In a real implementation, this would check if the property is available)
            if (currentPlayer.getPosition() % 5 == 0) {  // Arbitrary condition for demo
                const int propertyPrice = 200;


                    currentPlayer.decreaseBalance(propertyPrice);
                    currentPlayer.increaseBalance(currentPlayer.getPosition());

                    MoneyChangeEvent moneyEvent{
                        currentPlayer,
                        -propertyPrice
                    };
                    gui.onEvent(moneyEvent);
                }


            // Check for bankruptcy
            if (currentPlayer.isBankrupt()) {
                BankruptcyEvent bankruptcyEvent{currentPlayer};
                gui.onEvent(bankruptcyEvent);
            }

            // Move to next player
            currentPlayerIndex = (currentPlayerIndex + 1) % players.size();

        } catch (const std::exception& e) {
            std::cerr << "Error in game simulation: " << e.what() << std::endl;
        }
    }

    bool isGameOver() const {
        int activePlayers = 0;
        for (const auto& player : players) {
            if (!player->isBankrupt()) {
                activePlayers++;
            }
        }
        return activePlayers <= 1;
    }

    // Find the winner (player with most money)
    int getWinner() const {

        return 3;
    }
};

int main() {
    try {
        Gui &gui = monopoly::Gui::getInstance();
        GameSimulator simulator(gui);

        while (gui.isOpen() && !simulator.isGameOver()) {
            gui.processSfmlEvents();
            simulator.simulateTurn();
            gui.render();
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }


        return 0;

    } catch (const std::exception& e) {
        std::cerr << "Fatal error: " << e.what() << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "Unknown fatal error occurred" << std::endl;
        return 1;
    }
}