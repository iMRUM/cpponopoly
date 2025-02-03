#pragma once
#include "BoardSquareComponent.hpp"
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

        void updatePlayerAtSquare(int player_id, int new_square_id, int old_square_id);
        void updateHouseOnStreet(int square_id);

        BoardSquareComponent *findSquareById(int square_id);

        void updateView() override;
    };
}