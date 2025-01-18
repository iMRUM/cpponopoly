#include "../include/model/Game.hpp"

#include <stdexcept>
namespace monopoly {
    Game::Game() {
        property_registry = std::make_unique<PropertyRegistry>();
        player_registry = std::make_unique<PlayerRegistry>();
    }
    // Basic Player and square management
    void Game::addPlayers(size_t num_players) {
        for (auto i = 0; i < num_players; ++i) {
            addPlayer("Player" + std::to_string(i));
        }
    }

    void Game::addPlayer(const std::string &player) {
        if (player_registry->getSize() >= 8) {
            throw std::runtime_error("Maximum number of players reached");
        }
        player_registry->registerPlayer(player);
    }

    void Game::addSquare() {
    }

    void Game::addProperty() {
    }

    void Game::addRailroad() {
    }

    void Game::addStreet() {
    }

    void Game::addUtility() {
    }

    void Game::addSpecialSquare() {
    }

    //Turns management:
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
        /*auto bankrupt_position = bankrupt_player.getPosition();

        // Check if bankruptcy is from property rent
        if (auto property = dynamic_cast<Property*>(getSquareAt(bankrupt_position))) {
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
        *///TODO: Complete tomorrow!!
        isGameWon();
    }

    void Game::moveSteps(int steps) {
    }

    void Game::movedPastGo() {
    }

    void Game::landOn(int pos) {
    }

    void Game::landOnProperty(Property &property) {
    }

    void Game::payRent(Property &property) {
    }

    void Game::buyProperty(Property &property) {
    }

    void Game::buildOnProperty(Property &property) {
    }

    void Game::landOnSpecialSquare(SpecialSquare &special_square) {
    }

    void Game::landOnFreeParking() {
    }

    void Game::landOnInJailJustVisit() {
    }

    void Game::landOnLuxuryTax() {
    }

    void Game::landOnChance() {
    }

    void Game::landOnGoToJail() {
    }

    void Game::goToJail() {
    }

    void Game::outOfJail() {
    }

    void Game::processCurrentTurn() {
    }

    void Game::setupColorGroups() {
    }

    void Game::createProperties() {
    }

    void Game::createSpecialSquares() {
    }

    Game &Game::getInstance() {
        if (!instance) {
            instance = std::unique_ptr<Game>(new Game());
        }
        return *instance;
    }

    bool Game::initializeGame(size_t size_players) {
        state.initialized = true;
        return state.initialized;
    }

    bool Game::startGame() {
        state.started = true;
        return state.started;
    }

    bool Game::endGame() {
        state.over = true;
        return state.over;
    }

    void Game::nextTurn() {
    }

    bool Game::canBuyProperty() const {
    }

    bool Game::mustPayRent() const {
    }

    int Game::calculateCurrentRent() const {
    }

    Player & Game::getCurrentPlayer() {
    }

    Property * Game::getCurrentProperty() const {
    }
}
