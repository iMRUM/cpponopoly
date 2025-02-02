#pragma once
#include <string>

namespace monopoly {
    // Generic observer interface

    struct PlayerMoveEvent {
        const int player_id;
        int steps;
    };

    struct PropertyPurchaseEvent {
        const int player_id;
        const int property_id;
        int price;
    };

    struct BankruptcyEvent {
        const int player_id;
        int debt;
    };

    struct DiceRollEvent {
        int dice1;
        int dice2;
    };

    struct MoneyChangeEvent {
        const int player_id;
        int amount; // can be negative
    };

    struct GameOverEvent {
        const int player_id;
        int finalMoney;
    };

    struct HouseBuiltEvent {
        const int player_id;
        const int square_id;
    };
    enum class GameEvent {
        PLAYER_MOVED,
        PROPERTY_PURCHASED,
        RENT_PAID,
        PLAYER_BANKRUPT,
        HOUSE_BUILT,
        GAME_OVER,
        TURN_CHANGED,
        DICE_ROLLED
    };

    class IMonopolyObserver {
    public:
        virtual ~IMonopolyObserver() = default;
        // Event handlers for each event type
        virtual void onEvent(const PlayerMoveEvent& event) = 0;
        virtual void onEvent(const PropertyPurchaseEvent& event) = 0;
        virtual void onEvent(const BankruptcyEvent& event) = 0;
        virtual void onEvent(const DiceRollEvent& event) = 0;
        virtual void onEvent(const MoneyChangeEvent& event) = 0;
        virtual void onEvent(const GameOverEvent& event) = 0;
        virtual void onEvent(const HouseBuiltEvent& event) = 0;
    };
}
