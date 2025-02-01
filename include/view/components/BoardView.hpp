#pragma once
#include "SFComposite.hpp"
// holds squares and players
namespace monopoly {
    class BoardView : public SFComposite{
    public:
        BoardView(float width, float height);
        void createBottomSquares();
        void createLeftSquares();
        void createTopSquares();
        void createRightSquares();
        void createCornerSquares();

        bool handleEvent(const sf::Event &event) override;

        void updateView() override;
    };
}