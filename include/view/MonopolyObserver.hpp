#pragma once
#include <string>

#include "../include/utils/Observer/IObserver.hpp"

namespace monopoly {
    // Forward declarations
    class Game;
    class Player;
    class Square;
    // Game event structures
    struct PlayerMoveEvent {
        const Player& player;
        int oldPosition;
        int newPosition;
    };

    struct PropertyPurchaseEvent {
        const Player& player;
        const Square& property;
        int price;
    };

    struct BankruptcyEvent {
        const Player& player;
        int debt;
    };

    struct DiceRollEvent {
        int dice1;
        int dice2;
    };

    struct MoneyChangeEvent {
        const Player& player;
        int oldAmount;
        int newAmount;
        std::string reason;
    };

    struct GameOverEvent {
        const Player& winner;
        int finalMoney;
    };
    class MonopolyObserver :
        public IObserver<PlayerMoveEvent>,
        public IObserver<PropertyPurchaseEvent>,
        public IObserver<BankruptcyEvent>,
        public IObserver<DiceRollEvent>,
        public IObserver<MoneyChangeEvent>,
        public IObserver<GameOverEvent> {
    public:
        ~MonopolyObserver() override = default;
    };

} // namespace monopoly