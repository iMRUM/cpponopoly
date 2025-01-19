#pragma once
#include <string>

#include "../include/utils/Observer/IObserver.hpp"

namespace monopoly {
    // Forward declarations
    class Game;
    class Player;
    class Square;

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