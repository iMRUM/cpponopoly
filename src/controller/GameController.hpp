#pragma once
#include "../model/Game.hpp"
#include "../include/registries/PlayerRegistry.hpp"
#include "../model/squares/Property.hpp"
class Gui;
namespace monopoly {
    class GameController {
        Game& monopoly_instance;
        PlayerRegistry& player_registry;
        Gui* gui; //TODO not sure if pointer or reference, made pointer to avoid errors for now
        bool isGameOver;




        void startGame();
        void endGame();
        void nextTurn();
        void addPlayer(std::unique_ptr<Player> player);
        Player& getCurrentPlayer();//TODO check if right type (Player& and/or Square*)
        Square *getSquareAt(int index);//TODO check if right type

        //Turns management:
        void handleTurn();
        void rollDice();
        void updateGui();
        void handleDiceRoll(int result, bool isDoubles);
        void handleDouble(int result);
        void isGameWon();//TODO

        //Movement management:
        void moveSteps(int steps);
        void movedPastGo();
        void landOn(int pos);

        void landOnProperty(Property* property);//TODO
        void payRent(Property* property); //TODO
        void buyProperty(Property* property);//TODO



        void landOnSpecialSquare();//TODO

        void landOnChance(); //TODO void drawChanceCard();

        void landOnGoToJail();//TODO
        void goToJail();
        void outOfJail();

        void landOnFreeParking();
        void landOnLuxuryTax();
        void landOnInJailJustVisit();



    public:
        explicit GameController(size_t numOfPlayers, Gui& gui, PlayerRegistry& player_registry);


    };
}
