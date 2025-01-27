#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>
class UIComponent {
protected:
    sf::Vector2f position;
    sf::Vector2f size;
    bool isVisible = true;
    bool isEnabled = true;

public:
    UIComponent(const sf::Vector2f& pos, const sf::Vector2f& sz)
        : position(pos), size(sz) {}

    virtual ~UIComponent() = default;

    virtual void draw(sf::RenderWindow& window) = 0;
    virtual bool handleEvent(const sf::Event& event) = 0;
    virtual void updateView() = 0;

    void setPosition(const sf::Vector2f& pos) { position = pos; }
    void setSize(const sf::Vector2f& sz) { size = sz; }

    const sf::Vector2f& getPosition() const { return position; }
    const sf::Vector2f& getSize() const { return size; }

    bool contains(const sf::Vector2f& point) const {
        return point.x >= position.x && point.x <= position.x + size.x &&
               point.y >= position.y && point.y <= position.y + size.y;
    }

    void setVisible(bool visible) { isVisible = visible; }
    void setEnabled(bool enabled) { isEnabled = enabled; }
    bool isComponentVisible() const { return isVisible; }
    bool isComponentEnabled() const { return isEnabled; }
};