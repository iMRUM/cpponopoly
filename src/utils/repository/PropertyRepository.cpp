#pragma once
#include "../../../include/utils/repository/IRepository.hpp"
#include "../../../include/model/squares/Property.hpp"

namespace monopoly {
    class PropertyRepository : public IRepository<monopoly::Property, long, int, int> {
        // long id, int price, int base_rent

    };
}
