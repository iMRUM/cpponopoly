#pragma once
#include <functional>
#include <memory>
#include <string>

#include "PlayerTokenComponent.hpp"

/*
#pragma once
#include "BoardSquareComponent.hpp"
class : public BoardSquareComponent {

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
class BoardSquareComponent : public SFComponent {
protected:

    int square_id;  // To link with model
    sf::RectangleShape background;
    sf::Text name_text;
    sf::Text lower_text;
    BoardSide board_side;
    sf::Color background_color;
    sf::Font font;
    std::string name;
    std::vector<std::unique_ptr<PlayerTokenComponent>> player_tokens;


    bool isCornerSquare();
    void setupSize();
    void setBackground();
    void initText();
    void setTextRotation();

public:
    static constexpr float TOKEN_SPACING = 5.0f;  // Space between tokens
    static constexpr float TOKEN_PADDING = 10.0f;  // Padding from square edges


    BoardSquareComponent(const sf::Vector2f &pos,
                    const std::string &squareName,
                    int id,
                    BoardSide side,
                    sf::Color bg = sf::Color(210, 230, 210));
    virtual ~BoardSquareComponent() = default;

    // UI functions
    void draw(sf::RenderWindow& window) override;
    void drawPlayers(sf::RenderWindow &window);
    bool handleEvent(const sf::Event& event) override = 0;
    virtual void setTexts() = 0;
    void addPlayer(int player_id);
    void removePlayer(int player_id);
    void clearPlayers();
    void repositionTokens();  // Helper to update token positions
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
    void testChange() {
        std::cout << square_id + "WAS CHANGED" << std::endl;
    }
    virtual void updateView() = 0;  // Called by controller when model changes
};