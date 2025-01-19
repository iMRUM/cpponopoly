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

    void Game::addRailroad(const std::string &name,const PropertyID propertyId, const int position, const int price = 200, const int baseRent= 50) {
        property_registry->registerObject(std::make_shared<Railroad>(name, propertyId, position, price, baseRent));
    }

    void Game::addStreet(const std::string &name, const int position, const int price, const int baseRent, const
               int house_cost,
               const PropertyID propertyId) {
        property_registry->registerObject(std::make_shared<Street>(name, position, price, baseRent, house_cost, propertyId));
    }

    void Game::addUtility(const std::string &name, const int position, const PropertyID propertyId) {
        property_registry->registerObject(std::make_shared<Utility>(name, position, propertyId));
    }

    void Game::addSpecialSquare() {
    }

    //Turns management:
    void Game::handleTurn() {
        state.resetTurnState();
        Player &current_player = getCurrentPlayer();
        handleDiceRoll();
        if (!current_player.isInJail()) {
            moveSteps(state.current_dice_result, current_player);
        } else if (current_player.getJailTurns() >= 3) {
            payFine(50, current_player);
            outOfJail(current_player);
        }
    }

    Game::Dice Game::rollDice() {
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
        if (current_player.hasThreeConsecutiveDoubles()) {
            goToJail(current_player);
        }

        if (!current_player.isInJail()) {
            state.has_another_turn = true;
        }
    }

    void Game::isGameWon() {
        int active_players = 0;
        Player* potential_winner = nullptr;

        // Check active players and high balance
        for (const auto& [_, player] : player_registry->getAllObjects()) {
            if (!player->isBankrupt()) {
                active_players++;
                potential_winner = player.get();

                // Check winning balance condition
                if (player->getBalance() >= 4000) {
                    state.winner = player.get();
                    state.over = true;
                    return;
                }
            }
        }

        // Check single player remaining
        if (active_players == 1) {
            state.winner = potential_winner;
            state.over = true;
        }
    }

    void Game::handleBankruptcy(Player &bankrupt_player) {
        bankrupt_player.setBankrupt(true);

        // Get bankrupt player's position and check if bankruptcy is from property rent
        auto bankrupt_position = bankrupt_player.getPosition();
        if (auto* property = dynamic_cast<Property*>(getSquareAt(bankrupt_position))) {
            if (property->isOwned()) {
                auto creditor = player_registry->getObject(property->getOwnerId());

                // Transfer all properties to creditor
                auto properties = property_registry->getProperties(bankrupt_player.getId());
                for (const auto& prop_id : properties) {
                    property_registry->setOwner(prop_id, creditor->getId());
                }

                // Transfer remaining money
                creditor->increaseBalance(bankrupt_player.getBalance());
            }
        }

        // Clear bankrupt player's assets
        auto properties = property_registry->getProperties(bankrupt_player.getId());
        for (const auto& prop_id : properties) {
            property_registry->removeOwner(prop_id);
        }
        bankrupt_player.setBalance(0);

        isGameWon();
    }

    void Game::moveSteps(int steps, Player &player) {
        int new_position = player.getPosition() + steps;
        if (new_position >= squares.size()) {
            new_position %= static_cast<int>(squares.size());
        }
        player.setPosition(new_position);
        landOn(new_position, player);
    }

    void Game::movedPastGo(Player &player) {
        player.increaseBalance(200);
    }

    void Game::landOn(int pos, Player &player) {
        Square *square = getSquareAt(pos);
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
            payRent(property, player);
            return;
        }
        if(canBuildOnProperty(property, player)) {
            state.awaiting_action = true;
        }
    }

    void Game::payRent(Property &property, Player &player) {
        /*
        std::unique_ptr<StrategyRentCalculator> calculator;

        if (auto* street = dynamic_cast<Street*>(&property)) {
            calculator = std::make_unique<StreetRentCalculator>(
                property.getBaseRent(),
                street->getHouses()
            );
        } else if (auto* railroad = dynamic_cast<Railroad*>(&property)) {
            int railroad_count = static_cast<int>(property_registry->getProperties(property.getOwnerId()).size());
            calculator = std::make_unique<RailroadRentCalculator>(50, railroad_count);
        } else if (auto* utility = dynamic_cast<Utility*>(&property)) {
            calculator = std::make_unique<UtilityRentCalculator>(10, state.current_dice_result);
        }

        if (!calculator) return;

        int rent = calculator->calculateRent();*/
        int rent = calculateCurrentRent();
        if (!player.canAfford(rent)) {
            handleBankruptcy(player);
            return;
        }

        auto owner = player_registry->getObject(property.getOwnerId());
        player.decreaseBalance(rent);
        owner->increaseBalance(rent);
    }

    void Game::buyProperty(Property &property, Player &player) {
        if (property.isOwned() || !player.canAfford(property.getPrice())) {
            return;
        }

        if (player.decreaseBalance(property.getPrice())) {
            property_registry->setOwner(property.getPropertyId(), player.getId());
            property.setOwnerId(player.getId());
            state.awaiting_action = false;
        }
    }

    void Game::buildOnProperty(Property &property, Player &player) {
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

    void Game::processCurrentTurn() {
    }

    void Game::setupColorGroups() {
        color_groups = {
            {ColorGroupID(1), "Brown"},
            {ColorGroupID(2), "Light Blue"},
            {ColorGroupID(3), "Pink"},
            {ColorGroupID(4), "Orange"},
            {ColorGroupID(5), "Red"},
            {ColorGroupID(6), "Yellow"},
            {ColorGroupID(7), "Green"},
            {ColorGroupID(8), "Dark Blue"}
        };
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
        if (!state.has_another_turn) {
            state.current_player_index = (state.current_player_index + 1) % static_cast<int>(getPlayerCount());
        }
    }

    bool Game::canBuyProperty(Player& player){
        if (auto* square = getSquareAt(player.getPosition())) {
            if (auto* property = dynamic_cast<Property*>(square)) {
                return !property->isOwned() &&
                       getCurrentPlayer().canAfford(property->getPrice());
            }
        }
        return false;
    }

    bool Game::canBuildOnProperty(Property& property, Player& player) {
        auto* street = dynamic_cast<Street*>(&property);
        if (!street) return false;

        // Check ownership and group completion
        if (!property_registry->isGroupComplete(
                property_registry->getPropertyGroup(property.getPropertyId()),
                player.getId())) {
            return false;
                }

        // Check if player can afford
        if (!player.canAfford(street->getHouseCost())) {
            return false;
        }

        // Check even development rule
        auto group_properties = property_registry->getPropertiesInGroup(
            property_registry->getPropertyGroup(property.getPropertyId())
        );

        int current_houses = street->getHouses();
        for (const auto& group_property_id : group_properties) {
            auto group_property = property_registry->getObject(group_property_id);
            if (auto* other_street = dynamic_cast<Street*>(group_property.get())) {
                if (other_street->getHouses() < current_houses) {
                    return false;
                }
            }
        }

        return true;
    }
    bool Game::mustPayRent(){
        if (auto* square = getSquareAt(getCurrentPlayer().getPosition())) {
            if (auto* property = dynamic_cast<Property*>(square)) {
                return property->isOwned() &&
                       property->getOwnerId() != getCurrentPlayer().getId();
            }
        }
        return false;
    }

    int Game::calculateCurrentRent(){
        if (auto* square = getSquareAt(getCurrentPlayer().getPosition())) {
            if (auto* property = dynamic_cast<Property*>(square)) {
                std::unique_ptr<StrategyRentCalculator> calculator;

                if (auto* street = dynamic_cast<Street*>(property)) {
                    calculator = std::make_unique<StreetRentCalculator>(
                        property->getBaseRent(),
                        street->getHouses()
                    );
                } else if (auto* railroad = dynamic_cast<Railroad*>(property)) {
                    int railroad_count = property_registry->getProperties(property->getOwnerId()).size();
                    calculator = std::make_unique<RailroadRentCalculator>(50, railroad_count);
                } else if (auto* utility = dynamic_cast<Utility*>(property)) {
                    calculator = std::make_unique<UtilityRentCalculator>(10, state.current_dice_result);
                }

                if (calculator) {
                    return calculator->calculateRent();
                }
            }
        }
        return 0;
    }

    Player &Game::getCurrentPlayer() {
        return *(player_registry->getObject(PlayerID(state.current_player_index)));
    }

    Property *Game::getCurrentProperty(){
        if (auto* square = getSquareAt(getCurrentPlayer().getPosition())) {
            return dynamic_cast<Property*>(square);
        }
        return nullptr;
    }
}
