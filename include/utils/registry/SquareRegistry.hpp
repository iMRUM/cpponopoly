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
        //primary storage for squares

    };
}