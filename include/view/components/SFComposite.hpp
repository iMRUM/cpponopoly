#pragma once
#include <functional>
#include <memory>
#include <string>
#include "SFComponent.hpp"

class SFComposite : public SFComponent {
protected:
    std::vector<std::unique_ptr<SFComponent>> children;
public:
    SFComposite(const sf::Vector2f& pos, const sf::Vector2f& sz): SFComponent(pos,sz) { std::cout << "SFComposite::SFComposite" << std::endl; };
    void draw(sf::RenderWindow &window) override {
        for (const auto &child : children) {
            child->draw(window);
        }
    }
    void add(std::unique_ptr<SFComponent> component) {
        children.push_back(std::move(component));
    }
    void remove(SFComponent* child) {
        std::erase_if(children, [child](const std::unique_ptr<SFComponent>& ptr) {
            return ptr.get() == child;
        });
    }

};