#pragma once
#include <functional>
#include <memory>
#include <string>
#include "UIComponent.hpp"

/*
#pragma once
#include "BoardSquare.hpp"
class : public BoardSquare {

};

 */
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


    sf::RectangleShape background;
    sf::Text name_text;
    sf::Text lower_text;
    BoardSide board_side;
    sf::Color background_color;
    sf::Font font;
    std::string name;
    int square_id;  // To link with model

    bool isCornerSquare();
    void setupSize();
    void setBackground();
    void initText();//TODO: perhaps should be virtual since they have different texts.
    void setTextRotation();

public:
    //first constructor is not used, should be deleted
    BoardSquare(const sf::Vector2f &pos, const sf::Vector2f &size,
                const std::string &squareName,
                int id,
                BoardSide side,
                sf::Color bg = sf::Color(210, 230, 210)); // to be deprecated
    BoardSquare(const sf::Vector2f &pos,
                    const std::string &squareName,
                    int id,
                    BoardSide side,
                    sf::Color bg = sf::Color(210, 230, 210));
    virtual ~BoardSquare() = default;

    // UI functions
    virtual void draw(sf::RenderWindow& window) override = 0;
    virtual bool handleEvent(const sf::Event& event) override = 0;

    // View-specific functionality
    void setBoardSide(const BoardSide side);

    [[nodiscard]] const sf::RectangleShape & getBackground() const {
        return background;
    }

    [[nodiscard]] const sf::Text & getNameText() const {
        return name_text;
    }

    [[nodiscard]] BoardSide getBoardSide() const {
        return board_side;
    }

    [[nodiscard]] const sf::Color & getBackgroundColor() const {
        return background_color;
    }

    [[nodiscard]] const sf::Font & getFont() const {
        return font;
    }

    [[nodiscard]] const std::string & getName() const {
        return name;
    }

    [[nodiscard]] int getSquareId() const {
        return square_id;
    }

    virtual void updateView() = 0;  // Called by controller when model changes
};