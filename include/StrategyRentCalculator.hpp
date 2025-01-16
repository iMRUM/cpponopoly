#pragma once
class StrategyRentCalculator {
public:
    virtual ~StrategyRentCalculator() = default;
    [[nodiscard]] virtual int calculateRent() const = 0;
};
