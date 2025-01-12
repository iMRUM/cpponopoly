#include "Game.hpp"

#include <stdexcept>

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
    game_started = false;
    game_over = false;
    current_player_index = 0;
    game_initialized = true;
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

void Game::addPlayer(std::unique_ptr<Player> player) {
    if (players.size() >= 8) {
        throw std::runtime_error("Maximum number of players reached");
    }
    players.push_back(std::move(player));
}

Player & Game::getCurrentPlayer() {
    if (players.empty()) {
        throw std::runtime_error("No players in game");
    }
    return *players[current_player_index];
}

void Game::nextTurn() {
    if (++current_player_index >= players.size()) {
        current_player_index = 0;
    }
}

Game::Dice Game::rollDice() {
    return Dice{dice_dist(gen_), dice_dist(gen_)};
}
