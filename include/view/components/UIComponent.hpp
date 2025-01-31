#pragma once
#include <memory>

class UIComponent {
    using pu_component = std::unique_ptr<UIComponent>;
    using p_component = UIComponent*;
public:
    void add(pu_component component);
    void remove(p_component component);
    void draw();
};
