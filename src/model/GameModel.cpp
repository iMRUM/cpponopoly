#include "../../include/model/GameModel.hpp"
#include <stdexcept>


namespace monopoly {
    std::unique_ptr<GameModel> monopoly::GameModel::instance = nullptr;

    GameModel::GameModel() {
        board = std::make_unique<Board>();
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

    void GameModel::executeAction(AwaitedAction action) {
        switch (action) {
            case AwaitedAction::ROLL_DICE:
                handleDiceRoll();
                break;
            case AwaitedAction::MOVE:
                executeMove();
                break;
            case AwaitedAction::BUY_PROPERTY:
                break;
            case AwaitedAction::BUILD_HOUSE:
                break;
            case AwaitedAction::USE_JAIL_CARD:
                break;
            case AwaitedAction::PAY_JAIL_FINE:
                break;
        }
    }


    void GameModel::executeMove() {
        moveSteps(state.current_dice_result, state.current_player_id);
        Player& player = getCurrentPlayer();
        if (player.getPosition() < state.current_dice_result) { // Passed GO
            movedPastGo(player);
        }
        landOn(player.getPosition(), player);

        if (!state.awaiting_action) {
            state.awaited_action = AwaitedAction::TURN_ENDED;
        }
    }

    void GameModel::executeBuyProperty() {
        if (auto* property = dynamic_cast<Property*>(board->getSquare(state.current_square_id))) {
            buyProperty(*property, getCurrentPlayer());
            state.awaited_action = AwaitedAction::TURN_ENDED;
        }
    }

    void GameModel::executeBuildHouse() {
        if (auto* street = dynamic_cast<Street*>(board->getSquare(state.current_square_id))) {
            if (canBuildOnStreet(*street, getCurrentPlayer())) {
                if (street->getHouses() >= rules::MAX_HOUSES) {
                    state.awaited_action = AwaitedAction::TURN_ENDED;
                    return;
                }

                Player& player = getCurrentPlayer();
                int cost = street->getHouseCost();
                if (player.decreaseBalance(cost)) {
                    street->addHouse();
                    state.awaiting_action = true;
                    state.awaited_action = AwaitedAction::BUILD_HOUSE;
                    return;
                }
            }
        }
        state.awaited_action = AwaitedAction::TURN_ENDED;
    }

    void GameModel::executeUseJailCard() {
    }

    void GameModel::executePayJailFine() {
    }

    //Turns management:
    void GameModel::handleTurn() {
        Player &current_player = getCurrentPlayer();
        handleDiceRoll();
        if (state.awaited_action == AwaitedAction::MOVE) {
            moveSteps(state.current_dice_result, state.current_player_id);
        } else if (current_player.getJailTurns() >= 3) {
            payFine(50, current_player);
            outOfJail(current_player);
        }
        state.resetTurnState(nextPlayerId());
    }

    void GameModel::handleDiceRoll() {
        Dice dice = rollDice();
        if (dice.isDoubles()) {
            handleDouble();
            return;
        }
    }

    Dice GameModel::rollDice() {
        state.has_rolled = true;
        const auto dice = Dice{dice_dist(gen_), dice_dist(gen_)};
        state.current_dice_result = dice.getTotal();
        return dice;
    }


    void GameModel::handleDouble() {
        Player &current_player = getCurrentPlayer();
        if (current_player.isInJail()) {
            outOfJail(current_player);
        }
        current_player.increaseDoubles();
        if (current_player.hasMaxConsecutiveDoubles()) {
            goToJail(current_player);
            return;
        }
        if (!current_player.isInJail()) {
            state.has_another_turn = true;
            state.awaited_action = AwaitedAction::MOVE;
        }
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
    }

    void GameModel::movedPastGo(Player &player) {
        player.increaseBalance(200);
    }

    void GameModel::landOn(int pos, Player &player) {
        Square *square = &getSquareAt(pos);
        if (!square) return;

        if (auto *property = dynamic_cast<Property *>(square)) {
            landOnProperty(*property, player);
        } else if (auto *special = dynamic_cast<SpecialSquare *>(square)) {
            landOnSpecialSquare(*special, player);
        }
    }

    void GameModel::landOnProperty(Property &property, Player &player) {
        if (!property.isOwned() && player.canAfford(property.getPrice())) {
            state.awaiting_action = true;
            state.awaited_action = AwaitedAction::BUY_PROPERTY;
            return;
        }
        if (property.isOwned() && property.getOwnerId() != player.getId()) {
            payRent(property, player);
        }

        auto *street = dynamic_cast<Street *>(&property);
        if (street && canBuildOnStreet(*street, player)) {
            state.awaiting_action = true;
            state.awaited_action = AwaitedAction::BUILD_HOUSE;
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
        state.reset();
        board->initSquares();
        addPlayers(size_players);
        state.initialized = true;
        startGame();
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
    }
    int GameModel::nextPlayerId() {
        return (state.current_player_id + 1) % static_cast<int>(getPlayersCount());
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
