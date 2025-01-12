#pragma once
//TODO: finish after street, railroad, utility are completed.
// Forward declaration to avoid circular dependency
class Property;

class RentCalculator {
public:
    virtual ~RentCalculator() = default;

    [[nodiscard]] virtual int calculateRent(const Property &property) const = 0;

protected:
    RentCalculator() = default;
};

class StreetRentCalculator : public RentCalculator {
    [[nodiscard]] int calculateRent(const Property &property) const override {
        return 0;
    }
};

class RailroadRentCalculator : public RentCalculator {
    [[nodiscard]] int calculateRent(const Property &property) const override {
        return 0;
    }
};

class UtilityRentCalculator : public RentCalculator {
    [[nodiscard]] int calculateRent(const Property &property) const override {
        return 0;
    }
};

class RentCalculatorRegistry {
private:
    static StreetRentCalculator streetCalculator;
    static RailroadRentCalculator railroadCalculator;
    static UtilityRentCalculator utilityCalculator;

public:
    static const RentCalculator &getStreetCalculator() { return streetCalculator; }
    static const RentCalculator &getRailroadCalculator() { return railroadCalculator; }
    static const RentCalculator &getUtilityCalculator() { return utilityCalculator; }
};
