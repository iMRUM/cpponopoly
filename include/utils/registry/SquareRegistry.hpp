#pragma once
#include <vector>
#include "IRegistry.hpp"
#include"../../model/squares/Property.hpp"
#include"../../model/squares/Railroad.hpp"
#include"../../model/squares/Street.hpp"
#include"../../model/squares/Utility.hpp"
#include"../../model/squares/SpecialSquare.hpp"

namespace monopoly {
    class SquareRegistry : public IRegistry<Square, int> {
    public:
        explicit SquareRegistry(size_t capacity = 0);
        void registerItem(std::unique_ptr<Square> square) override;
        Square& getByPosition(int position) const;
        Property& getPropertyByPosition(int position) const;
        Street& getStreetByPosition(int position) const;
        Railroad& getRailroadByPosition(int position) const;
        Utility& getUtilityByPosition(int position) const;
        SpecialSquare& getSpecialSquareByPosition(int position) const;

        bool isProperty(int position) const;
        bool isStreet(int position) const;
        bool isRailroad(int position) const;
        bool isUtility(int position) const;
        bool isSpecialSquare(int position) const;
    };
}