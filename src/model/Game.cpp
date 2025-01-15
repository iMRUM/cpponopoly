#include "Game.hpp"

#include <stdexcept>
//deleteboard
namespace monopoly {
    std::unique_ptr<Game> Game::instance = nullptr;

    Game::Game() {
        board = Board::getInstance();
        property_registry = std::make_unique<PropertyRegistry>();
        player_registry = std::make_unique<PlayerRegistry>();
    }

    Game &Game::getInstance() {
        if (!instance) {
            instance = std::unique_ptr<Game>(new Game());
        }
        return *instance;
    }


    bool Game::initializeGame(size_t size_players) {
        if (size_players < 2 || size_players > 8) {
            return false;
        }
        // Clear existing players if any
        state.reset();
        state.initialized = true;
        return isGameInitialized();
    }

    bool Game::startGame() {
        if (!isGameInitialized()) {
            return false;
        }
        state.started = true;
        return isGameStarted();
    }

    bool Game::endGame() {
        if (!isGameStarted()) {
            return false;
        }
        state.over = true;
        return isGameOver();
    }

    void Game::nextTurn() {
        state.current_player_index = (state.current_player_index + 1) % static_cast<int>(player_registry->getSize());
        state.resetTurnState();
    }

    void Game::addPlayer(const std::string &player) {
        if (player_registry->getSize() >= 8) {
            throw std::runtime_error("Maximum number of players reached");
        }
        player_registry->registerPlayer(player);
    }

    Player &Game::getCurrentPlayer() {
        return *(player_registry->get(PlayerID(state.current_player_index)));
    }

    void Game::handleTurn() {
    }
    Game::Dice Game::rollDice() {
        return Dice{dice_dist(gen_), dice_dist(gen_)};
    }

    void Game::handleDiceRoll(int result, bool isDoubles) {
    }

    void Game::handleDouble(int result) {
    }

    void Game::isGameWon() {
    }

    void Game::handleBankruptcy(Player& bankrupt_player) {
        bankrupt_player.setBankrupt(true);
        auto bankrupt_position = bankrupt_player.getPosition();

        // Check if bankruptcy is from property rent
        if (auto property = dynamic_cast<Property*>(getSquareAt(bankrupt_position).get())) {
            if (auto owner = property_registry->getOwner(PropertyID(property->getId()))) {
                // Transfer all properties to creditor
                auto properties = property_registry->getProperties(PlayerID(bankrupt_player.getId()));
                for (const auto& prop_id : properties) {
                    property_registry->setOwner(prop_id, owner);
                }
                // Transfer remaining money
                Player& creditor = *player_registry->get(owner);
                creditor.increaseBalance(bankrupt_player.getBalance());
            }
        }

        // Clear bankrupt player's assets
        auto properties = property_registry->getProperties(PlayerID(bankrupt_player.getId()));
        for (const auto& prop_id : properties) {
            property_registry->removeOwner(prop_id);
        }
        bankrupt_player.setBalance(0);

        isGameWon();
    }
}
