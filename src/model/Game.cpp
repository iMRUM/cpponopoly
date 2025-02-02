#include "../../include/model/Game.hpp"
#include <stdexcept>


namespace monopoly {
    std::unique_ptr<Game> monopoly::Game::instance = nullptr;
    Game::Game() {
        square_registry = std::make_unique<SquareRegistry>();
        player_registry = std::make_unique<PlayerRegistry>();
    }

    // Basic Player and square management
    void Game::addPlayers(size_t num_players) {
        //NOT-TESTED
        for (auto i = 0; i < num_players; ++i) {
            addPlayer("Player" + std::to_string(i), i);
        }
    }

    void Game::addPlayer(const std::string &name, int id) {
        //NOT-TESTED
        if (player_registry->size() >= 8) {
            throw std::runtime_error("Maximum number of players reached");
        }
        player_registry->registerItem(std::make_unique<Player>(name, id));
    }

    void Game::addSquare(std::unique_ptr<Square> square) {
        //NOT-TESTED
        if (square_registry->size() >= board_size) {
            throw std::runtime_error("Maximum number of squares reached");
        }
        square_registry->registerItem(std::move(square));
    }

    void Game::addToSquareGroup(const std::string &name, const int square_id) {
        square_groups[name].push_back(square_id);
    }


    void Game::addRailroad(const std::string &name, int position, int price, int baseRent) {
        //NOT-TESTED
        addSquare(std::make_unique<Railroad>(name, position, price, baseRent));
        addToSquareGroup("Railroad", position);
    }

    void Game::addStreet(const std::string &name, int position, int price, int baseRent, int house_cost,
                         const std::string &color) {
        //NOT-TESTED
        addSquare(std::make_unique<Street>(name, position, price, baseRent, house_cost, color));
        addToSquareGroup(color, position);
    }

    void Game::addUtility(const std::string &name, int position) {
        //NOT-TESTED
        addSquare(std::make_unique<Utility>(name, position));
        addToSquareGroup("Utility", position);
    }

    void Game::addSpecialSquare(const std::string &name, int position, SpecialSquareType type) {
        //NOT-TESTED
        addSquare(std::make_unique<SpecialSquare>(name, position, type));
        addToSquareGroup("SpecialSquare", position);
    }

    //Turns management:
    void Game::handleTurn() {
        state.resetTurnState();
        Player &current_player = getCurrentPlayer();
        handleDiceRoll();
        if (!current_player.isInJail()) {
            moveSteps(state.current_dice_result, state.current_player_id);
        } else if (current_player.getJailTurns() >= 3) {
            payFine(50, current_player);
            outOfJail(current_player);
        }
    }

    Dice Game::rollDice() {
        state.has_rolled = true;
        const auto dice = Dice{dice_dist(gen_), dice_dist(gen_)};
        state.current_dice_result = dice.getTotal();
        return dice;
    }

    void Game::handleDiceRoll() {
        Dice dice = rollDice();
        if (dice.isDoubles()) {
            handleDouble();
        }
    }

    void Game::handleDouble() {
        Player &current_player = getCurrentPlayer();
        if (current_player.isInJail()) {
            outOfJail(current_player);
        }
        current_player.increaseDoubles();
        if (current_player.hasMaxConsecutiveDoubles()) {
            goToJail(current_player);
        }

        if (!current_player.isInJail()) {
            state.has_another_turn = true;
        }
    }

    void Game::isGameWon() {
        //NOT-TESTED
        size_t active_players = player_registry->size();
        for (const Player &player: *player_registry) {
            if (player.isBankrupt()) {
                active_players--;
                continue;
            }
            state.winner = player.getId();
            if (player.getBalance() > 3999 || active_players == 1) {
                state.over = true;
                return;
            }
        }
    }

    void Game::handleBankruptcy(int player_id) {
        Player &current_player = getCurrentPlayer();
        current_player.setBankrupt(true);
        int current_position = current_player.getPosition();
        std::vector<int> &bankrupt_properties = ownership_map[player_id];
        if (owned_by_map.contains(current_position)) {
            ownership_map[owned_by_map[current_position]].insert(ownership_map[owned_by_map[current_position]].end(),
                                                                 bankrupt_properties.begin(),
                                                                 bankrupt_properties.end());
        } else {
            for (int property_id: bankrupt_properties) {
                square_registry->getPropertyByPosition(property_id).setOwnerId(-1); //-1 for bank
            }
        }
        ownership_map.erase(player_id);
        isGameWon();
    }

    void Game::moveSteps(int steps, int player_id) {
        int new_position = (player_registry->getByIdRef(player_id).getPosition() + steps)%static_cast<int>(square_registry->size());
        player_registry->getByIdRef(player_id).setPosition(new_position);
    }

    void Game::movedPastGo(Player &player) {
        player.increaseBalance(200);
    }

    void Game::landOn(int pos, Player &player) {
        Square *square = &getSquareAt(pos);
        if (!square) return;

        if (auto *property = dynamic_cast<Property *>(square)) {
            landOnProperty(*property, player);
        } else if (auto *special = dynamic_cast<SpecialSquare *>(square)) {
            landOnSpecialSquare(*special, player);
        }
        // Other square types can be handled here!
    }

    void Game::landOnProperty(Property &property, Player &player) {
        if (!property.isOwned() && player.canAfford(property.getPrice())) {
            state.awaiting_action = true;
            return;
        }
        if (property.isOwned() && property.getOwnerId() != player.getId()) {
            return;
        }

        auto* street = dynamic_cast<Street*>(&property);
        if (street && canBuildOnStreet(*street, player)) {
            state.awaiting_action = true;
        }
    }

    void Game::payRent(Property &property, Player &player) {
        std::unique_ptr<StrategyRentCalculator> calculator;

        if (auto *street = dynamic_cast<Street *>(&property)) {
            calculator = std::make_unique<StreetRentCalculator>(
                property.getBaseRent(),
                street->getHouses()
            );
        } else if (auto *railroad = dynamic_cast<Railroad *>(&property)) {
            int railroad_count = getRailroadCount(property.getOwnerId());
            calculator = std::make_unique<RailroadRentCalculator>(50, railroad_count);
        } else if (auto *utility = dynamic_cast<Utility *>(&property)) {
            calculator = std::make_unique<UtilityRentCalculator>(10, state.current_dice_result);
        }

        if (!calculator) return;

        int rent = calculator->calculateRent();
        if (!player.canAfford(rent)) {
            handleBankruptcy(player.getId());
            return;
        }

        auto owner = player_registry->getById(property.getOwnerId());
        player.decreaseBalance(rent);
        owner->increaseBalance(rent);
    }

    int Game::getRailroadCount(int player_id) {
        int count = 0;
        for (int railroad_id: square_groups["Railroad"]) {
            if(owned_by_map.contains(railroad_id) && owned_by_map[railroad_id] == player_id) {
                count++;
            }
        }
        return count;
    }
    void Game::buyProperty(Property &property, Player &player) {
        if (property.isOwned() || !player.canAfford(property.getPrice())) {
            return;
        }

        if (player.decreaseBalance(property.getPrice())) {
            owned_by_map[property.getId()] =  player.getId();
            ownership_map[player.getId()].push_back(property.getId());
            property.setOwnerId(player.getId());
            state.awaiting_action = false;
        }
    }

    void Game::buildOnStreet(int street_id, int player_id) {
    }

    void Game::landOnSpecialSquare(SpecialSquare &special_square, Player &player) {
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

    void Game::goToJail(Player &player) {
        player.toggleJailState();
    }

    void Game::outOfJail(Player &player) {
        player.toggleJailState();
    }

    void Game::payFine(int amount, Player &player) {
        player.decreaseBalance(amount);
    }


    std::unique_ptr<Game> Game::getInstance() {
        if (!instance) {
            instance = std::unique_ptr<Game>(new Game());
        }
        return std::move(instance);
    }

    bool Game::initializeGame(size_t size_players, size_t board_size) {
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
        if (!state.has_another_turn) {
            state.current_player_id = (state.current_player_id + 1) % static_cast<int>(getPlayersCount());
        }
    }

    bool Game::canBuyProperty() const {
        return false;
    }

    bool Game::hasMonopoly(int player_id, const std::string& color) const {
        auto colorGroup = square_groups.find(color);
        if (colorGroup == square_groups.end()) {
            return false;
        }

        for (int square_id : colorGroup->second) {
            auto owner = owned_by_map.find(square_id);
            if (owner == owned_by_map.end() || owner->second != player_id) {
                return false;
            }
        }
        return true;
    }
    /*
    * for (int railroad_id: square_groups["Railroad"]) {
            if(owned_by_map.contains(railroad_id) && owned_by_map[railroad_id] == player_id) {
                count++;
            }
        }
     */

    bool Game::canBuildOnStreet(Street &street, const Player &player) {
        if (!hasMonopoly(player.getId(), street.getColor()) || !player.canAfford(street.getHouseCost())) {
            return false;
        }

        auto color_group = square_groups.find(street.getColor());
        if (color_group == square_groups.end()) {
            return false;
        }

        int current_houses = street.getHouses();
        for (int square_id : color_group->second) {
            auto owner = owned_by_map.find(square_id);
            if (auto *other_street = dynamic_cast<Street*>(&getSquareAt(square_id))) {
                if (other_street->getHouses() < current_houses) {
                    return false;
                }
            }
        }
        return true;
    }

    bool Game::mustPayRent(const int square_id) const {
        if (owned_by_map.contains(square_id)) {
            return owned_by_map.at(square_id) == state.current_player_id;
        }
        return false;
    }

    int Game::calculateCurrentRent() const {
        return state.current_player_id;
    }

    Player &Game::getCurrentPlayer() {
        return player_registry->getByIdRef(state.current_player_id);
    }

    void Game::onEvent(const PlayerMoveEvent &event) {
    }

    void Game::onEvent(const PropertyPurchaseEvent &event) {
    }

    void Game::onEvent(const BankruptcyEvent &event) {
    }

    void Game::onEvent(const DiceRollEvent &event) {
    }

    void Game::onEvent(const MoneyChangeEvent &event) {
    }

    void Game::onEvent(const GameOverEvent &event) {
    }

    void Game::onEvent(const HouseBuiltEvent &event) {
    }
}
