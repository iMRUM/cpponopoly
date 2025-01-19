#pragma once


namespace monopoly {
    // Generic observer interface
    class Player;
    class Square;

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
    template<typename Event>
    class IObserver {
    public:
        virtual ~IObserver() = default;
        virtual void onEvent(const Event& event) = 0;
    };
}