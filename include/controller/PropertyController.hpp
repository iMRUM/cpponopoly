#pragma once
#include "../model/GameModel.hpp"
#include "../view/GameView.hpp"

namespace monopoly {
    class PropertyController {
    public:
        PropertyController(GameModel* model, GameView* view);
        void handlePropertyLanding(Player& player, Property& property);
        bool purchaseProperty(Player& player, Property& property);

    private:
        void collectRent(Player& player, const Property& property);
        int calculateRent(const Property& property) const;
        Player* getPlayerById(int id) const;

        GameModel* model_;
        GameView* view_;
    };
}