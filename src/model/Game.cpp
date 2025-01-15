#include "Game.hpp"

#include <stdexcept>
namespace monopoly {
    std::unique_ptr<Game> Game::instance = nullptr;

    Game::Game() {
        board = Board::getInstance();
        property_registry = std::make_unique<PropertyRegistry>();
        player_registry = std::make_unique<PlayerRegistry>();
    }

    Game & Game::getInstance() {
        if (!instance) {
            instance = std::unique_ptr<Game>(new Game());
        }
        return *instance;
    }

    const std::vector<std::unique_ptr<Player>> & Game::getPlayers() const {
        return players;
    }

    bool Game::initializeGame(size_t size_players) {
        if (size_players < 2 || size_players > 8) {
            return false;
        }
        // Clear existing players if any
        players.clear();
        players.resize(size_players);
        state.reset();
        state.initialized = true;
        return isGameInitialized();
    }

    bool Game::startGame() {
        if (!isGameInitialized()) {
            return false;
        }
        game_started = true;
        return isGameStarted();
    }

    bool Game::endGame() {
        if (!isGameStarted()) {
            return false;
        }
        game_over = true;
        return isGameOver();
    }

    void Game::addPlayer(const std::string& player) {
        if (player_registry->getSize() >= 8) {
            throw std::runtime_error("Maximum number of players reached");
        }
        player_registry->registerPlayer(player);
    }

    Player & Game::getCurrentPlayer() {
        return *player_registry->get(PlayerID(state.current_player_index));
    }

    void Game::nextTurn() {
        state.current_player_index = (state.current_player_index + 1) % static_cast<int>(player_registry->getSize());
        state.resetTurnState();
    }

    Game::Dice Game::rollDice() {
        return Dice{dice_dist(gen_), dice_dist(gen_)};
    }
}