#pragma once
#include <functional>
#include <memory>
#include <string>
#include "UIComponent.hpp"


enum class BoardSide {
    Bottom, // Regular square, text reads upward
    Left, // Regular square, text reads rightward
    Top, // Regular square, text reads downward
    Right, // Regular square, text reads leftward
    BottomLeft, // Corner square, text reads diagonally up-right
    BottomRight, // Corner square, text reads diagonally up-left
    TopLeft, // Corner square, text reads diagonally down-right
    TopRight // Corner square, text reads diagonally down-left
};

// View component
class BoardSquare : public UIComponent {
protected:
    static constexpr float REGULAR_WIDTH = 80.f;
    static constexpr float REGULAR_HEIGHT = 120.f;
    static constexpr float CORNER_SIZE = 120.f;
    static constexpr float TEXT_PADDING = 10.f;

    sf::RectangleShape background;
    sf::Text text;
    BoardSide board_side;
    sf::Color background_color;
    sf::Font font;
    std::string name;
    int square_id;  // To link with model

    bool isCornerSquare();
    void initBoardSide();
    void initText();//TODO: perhaps should be virtual since they have different texts.
    void setTextRotation();
    void setTextPosition(); //TODO: should be virtual since positioning is different

public:
    BoardSquare(const sf::Vector2f &pos, const sf::Vector2f &size,
                const std::string &squareName,
                int id,
                const sf::Color bg = sf::Color(210, 230, 210));

    virtual ~BoardSquare() = default;

    // UI functions
    virtual void draw(sf::RenderWindow& window) override = 0;
    virtual bool handleEvent(const sf::Event& event) override = 0;

    // View-specific functionality
    void setBoardSide(const BoardSide side);
    const std::string& getName() const;
    int getSquareId() const;
    virtual void updateView() = 0;  // Called by controller when model changes
};