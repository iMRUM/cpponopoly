#include "../../include/model/GameModel.hpp"
#include <stdexcept>


namespace monopoly {
    std::unique_ptr<GameModel> GameModel::instance = nullptr;

    GameModel::GameModel() {
        board = std::make_unique<Board>();
        std::cout << "GameModel Created" << std::endl;
    }

    // Basic Player and square management
    void GameModel::addPlayers(size_t num_players) {
        //NOT-TESTED
        for (auto i = 0; i < num_players; ++i) {
            addPlayer("Player" + std::to_string(i), i);
        }
    }

    void GameModel::addPlayer(const std::string &name, int id) {
        //NOT-TESTED
        if (players.size() >= 8) {
            throw std::runtime_error("Maximum number of players reached");
        }
        players.push_back(std::make_unique<Player>(name, id));
    }

    void GameModel::addSquare(std::unique_ptr<Square> square) {
        //NOT-TESTED
        if (board->getSize() >= 40) {
            //MAGIC NUMBER WILL BE SOLVED
            throw std::runtime_error("Maximum number of squares reached");
        }
        board->addSquare(std::move(square));
    }


    void GameModel::addRailroad(const std::string &name, int position, int price, int baseRent) {
        //NOT-TESTED
        addSquare(std::make_unique<Railroad>(name, position, price, baseRent));
    }

    void GameModel::addStreet(const std::string &name, int position, int price, int baseRent, int house_cost,
                              SquareGroups color) {
        //NOT-TESTED
        addSquare(std::make_unique<Street>(name, position, price, baseRent, house_cost, color));
    }

    void GameModel::addUtility(const std::string &name, int position) {
        //NOT-TESTED
        addSquare(std::make_unique<Utility>(name, position));
    }

    void GameModel::addSpecialSquare(const std::string &name, int position, SpecialSquareType type) {
        //NOT-TESTED
        addSquare(std::make_unique<SpecialSquare>(name, position, type));
    }

    //Turns management:
   /* void GameModel::handleTurn() {
        state.resetTurnState();
        Player &current_player = getCurrentPlayer();
        handleDiceRoll();
        if (!current_player.isInJail()) {
            moveSteps(state.current_dice_result, state.current_player_id);
        } else if (current_player.getJailTurns() >= 3) {
            payFine(50, current_player);
            outOfJail(current_player);
        }
    }*/

    const Dice &GameModel::rollDice() {
        state.has_rolled = true;
        const auto &dice = Dice{dice_dist(gen_), dice_dist(gen_)};
        state.current_dice_result = dice.getTotal();
        if (dice.isDoubles()) {
            handleDouble();
        }
        return dice;
    }

    void GameModel::handleDouble() {
        Player &current_player = getCurrentPlayer();
        if (!current_player.isInJail()) {
            state.has_another_turn = true;
            return;
        }
        if (current_player.isInJail()) {
            outOfJail(current_player);
        }
        current_player.increaseDoubles();
        if (current_player.hasMaxConsecutiveDoubles()) {
            goToJail(current_player);
        }
    }

    bool GameModel::hasAnotherTurn() {
        return state.has_another_turn;
    }

    void GameModel::isGameWon() {
        //NOT-TESTED
        size_t active_players = players.size();
        for (const auto &player: players) {
            if (player->isBankrupt()) {
                active_players--;
                continue;
            }
            state.winner = player->getId();
            if (player->getBalance() > 3999 || active_players == 1) {
                state.over = true;
                return;
            }
        }
    }

    void GameModel::handleBankruptcy(int player_id) {
        int owner_id = owned_by_map[state.current_square_id];
        Player &bankrupt_player = *players[player_id];

        // Transfer properties to owner who bankrupted the player
        if (ownership_map.count(player_id)) {
            for (int square_id: ownership_map[player_id]) {
                owned_by_map[square_id] = owner_id;
                ownership_map[owner_id].push_back(square_id);
            }
            ownership_map.erase(player_id);
        }

        bankrupt_player.setBankrupt(true);
        isGameWon();
    }

    void GameModel::moveSteps(int steps, int player_id) {
        int new_position = (players[player_id]->getPosition() + steps) % static_cast<int>(board->getSize());
        players[player_id]->setPosition(new_position);
        if (new_position <= state.current_square_id) {
            movedPastGo();
        }
        state.current_square_id = new_position;
    }

    void GameModel::movedPastGo() {
        getCurrentPlayer().increaseBalance(200);
    }

    void GameModel::landOn(int pos, Player &player) {
        Square *square = &getSquareAt(pos);
        if (!square) return;

        if (auto *property = dynamic_cast<Property *>(square)) {
            landOnProperty(*property, player);
        } else if (auto *special = dynamic_cast<SpecialSquare *>(square)) {
            landOnSpecialSquare(*special, player);
        }
        // Other square types can be handled here!
    }

    void GameModel::landOnProperty(Property &property, Player &player) {
        if (!property.isOwned() && player.canAfford(property.getPrice())) {
            state.awaiting_action = true;
            return;
        }
        if (property.isOwned() && property.getOwnerId() != player.getId()) {
            return;
        }

        auto *street = dynamic_cast<Street *>(&property);
        if (street && canBuildOnStreet(*street, player)) {
            state.awaiting_action = true;
        }
    }

    void GameModel::payRent(Property &property, Player &player) {
        std::unique_ptr<StrategyRentCalculator> calculator;

        if (auto *street = dynamic_cast<Street *>(&property)) {
            calculator = std::make_unique<StreetRentCalculator>(
                property.getBaseRent(),
                street->getHouses()
            );
        } else if (auto *railroad = dynamic_cast<Railroad *>(&property)) {
            int railroad_count = getRailroadCount(property.getId(), player.getId());
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

        auto &owner = players[property.getOwnerId()];
        player.decreaseBalance(rent);
        owner->increaseBalance(rent);
    }

    int GameModel::getRailroadCount(const int property_id, const int player_id) {
        int count = 0;
        for (int railroad_id: board->getPropertyIdsInGroup(property_id)) {
            if (owned_by_map.contains(railroad_id) && owned_by_map[railroad_id] == player_id) {
                count++;
            }
        }
        return count;
    }

    void GameModel::buyProperty(Property &property, Player &player) {
        if (property.isOwned() || !player.canAfford(property.getPrice())) {
            return;
        }

        if (player.decreaseBalance(property.getPrice())) {
            owned_by_map[property.getId()] = player.getId();
            ownership_map[player.getId()].push_back(property.getId());
            property.setOwnerId(player.getId());
            state.awaiting_action = false;
        }
    }

    void GameModel::buildOnStreet(int street_id, int player_id) {
    }

    void GameModel::landOnSpecialSquare(SpecialSquare &special_square, Player &player) {
    }

    void GameModel::landOnFreeParking() {
    }

    void GameModel::landOnInJailJustVisit() {
    }

    void GameModel::landOnLuxuryTax() {
        if (!getCurrentPlayer().decreaseBalance(rules::LUXURY_TAX)) {
            handleBankruptcy(state.current_player_id);
        }
    }

    void GameModel::landOnChance() {
    }

    void GameModel::landOnGoToJail() {
    }

    void GameModel::goToJail(Player &player) {
        player.toggleJailState();
        player.setPosition(10);
    }

    void GameModel::outOfJail(Player &player) {
        player.toggleJailState();
    }

    void GameModel::payFine(int amount, Player &player) {
        player.decreaseBalance(amount);
    }


    std::unique_ptr<GameModel> GameModel::getInstance() {
        if (!instance) {
            instance = std::unique_ptr<GameModel>(new GameModel());
        }
        return std::move(instance);
    }

    void GameModel::initializeGame(size_t size_players) {
        board->initSquares();
        addPlayers(size_players);
        state.initialized = true;
    }

    void GameModel::startGame() {
        state.started = true;
    }

    void GameModel::endGame() {
        state.over = true;
    }

    void GameModel::nextTurn() {
        if (!state.has_another_turn) {
            state.current_player_id = (state.current_player_id + 1) % static_cast<int>(getPlayersCount());
        }
        /*void GameModel::nextTurn() {
        if (!state.has_another_turn) {
            const int player_count = static_cast<int>(getPlayersCount());
            int next_player = state.current_player_id;
            int checked_players = 0;

            // Keep looking for next valid player until we've checked everyone
            do {
                next_player = (next_player + 1) % player_count;
                checked_players++;

                // If we've checked all players, the game should be over
                if (checked_players >= player_count) {
                    state.over = true;
                    return;
                }
            } while (players[next_player]->isBankrupt());

            state.current_player_id = next_player;
        }
    }*/
    }

    bool GameModel::canBuyProperty() const {
        if (auto property = dynamic_cast<Property *>(board->getSquare(state.current_square_id))) {
            return players[state.current_player_id]->canAfford(property->getPrice());
        }
        return false;
    }


    bool GameModel::canBuildOnStreet(Street &street, const Player &player) {
        //monopoly check
        if (!hasMonopoly(player.getId(), street.getId()) || !player.canAfford(street.getHouseCost())) {
            return false;
        }
        //"even houses amount rule"
        int current_houses = street.getHouses();
        for (auto *other_street: board->getPropertiesInGroup(street.getId())) {
            if (!other_street) continue;

            if (auto *street_ptr = dynamic_cast<Street *>(other_street)) {
                if (street_ptr->getHouses() < current_houses) {
                    return false;
                }
            }
        }
        return true;
    }

    bool GameModel::hasMonopoly(int player_id, int square_id) const {
        std::vector<Property *> group_properties = board->getPropertiesInGroup(square_id);

        // Check if all properties in group are owned by same player
        return std::all_of(group_properties.begin(), group_properties.end(),
                           [player_id](const Property *prop) {
                               return prop->getOwnerId() == player_id;
                           });
    }

    bool GameModel::mustPayRent(const int square_id) const {
        if (owned_by_map.contains(square_id)) {
            return owned_by_map.at(square_id) == state.current_player_id;
        }
        return false;
    }

    int GameModel::calculateCurrentRent() const {
        return state.current_player_id;
    }

    Player &GameModel::getCurrentPlayer() {
        return *players[state.current_player_id];
    }
}
