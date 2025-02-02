#pragma once
#include <functional>
#include <memory>
#include <string>
#include <unordered_set>

#include "SFComponent.hpp"

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
class BoardSquare : public SFComponent {
protected:
    // Existing members
    int square_id;
    sf::RectangleShape background;
    sf::Text name_text;
    sf::Text lower_text;
    BoardSide board_side;
    sf::Color background_color;
    sf::Font font;
    std::string name;

    // New members for player tracking
    std::unordered_set<int> players_present;
    static constexpr float PLAYER_DOT_RADIUS = 10.0f;
    static constexpr float PLAYER_TEXT_SIZE = 12.0f;

    // Helper methods
    void drawPlayers(sf::RenderWindow& window);
    sf::Vector2f calculatePlayerPosition(size_t index) const;
    bool isCornerSquare();
    void setupSize();
    void setBackground();
    void initText();
    void setTextRotation();

public:
    BoardSquare(const sf::Vector2f &pos,
                const std::string &squareName,
                int id,
                BoardSide side,
                sf::Color bg = sf::Color(210, 230, 210));

    virtual ~BoardSquare() = default;

    // Player management methods
    void addPlayer(int player_id);
    void removePlayer(int player_id);
    void clearPlayers();
    bool hasPlayer(int player_id) const;

    // Existing methods
    virtual void draw(sf::RenderWindow& window) override;
    virtual bool handleEvent(const sf::Event& event){return true;}
    virtual void setTexts() = 0;
    virtual void updateView() = 0;

    // Existing getters
    [[nodiscard]] const sf::RectangleShape & getBackground() const { return background; }
    [[nodiscard]] const sf::Text & getNameText() const { return name_text; }
    [[nodiscard]] BoardSide getBoardSide() const { return board_side; }
    [[nodiscard]] const sf::Color & getBackgroundColor() const { return background_color; }
    [[nodiscard]] const sf::Font & getFont() const { return font; }
    [[nodiscard]] const std::string & getName() const { return name; }
    [[nodiscard]] int getSquareId() const { return square_id; }
};
