#pragma once
#include "GameState.hpp"

namespace monopoly {
    class LandState : public GameState {
    public:
        static GameState* Instance() {
            static LandState instance;
            return &instance;
        }

        void onEnter(GameController* controller) override {
            auto model = controller->getModel();
            auto currentPlayer = controller->getCurrentPlayerIndex();
            int currentSquare = model->getPlayerPosition(currentPlayer);

            // Determine square type and transition to appropriate state
            switch (model->getSquareType(currentSquare)) {
                case SquareType::Property:
                case SquareType::Railroad:
                case SquareType::Utility: {
                    changeState(controller, LandOnPropertyState::Instance());
                    break;
                }
                case SquareType::Special: {
                    switch (model->getSpecialSquareType(currentSquare)) {
                        case SpecialSquareType::Chance:
                        case SpecialSquareType::CommunityChest:
                        case SpecialSquareType::Tax:
                        case SpecialSquareType::FreeParking:
                        case SpecialSquareType::Go: {
                            changeState(controller, LandOnSpecialSquareState::Instance());
                            break;
                        }
                        case SpecialSquareType::GoToJail: {
                            model->sendToJail(currentPlayer);
                            controller->getView()->showSentToJail();
                            changeState(controller, JailState::Instance());
                            break;
                        }
                        case SpecialSquareType::Jail: {
                            // Just visiting
                            controller->getView()->showJustVisiting();
                            size_t nextPlayer = (currentPlayer + 1) % model->getNumPlayers();
                            controller->setCurrentPlayerIndex(nextPlayer);
                            changeState(controller, RollDiceState::Instance());
                            break;
                        }
                    }
                    break;
                }
            }
        }
    };
}