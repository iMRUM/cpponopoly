#pragma once
#include <unordered_map>
#include <algorithm>
#include <memory>
#include <stdexcept>
#include "../utils/Id.hpp"

namespace monopoly {

    template<typename T, typename IDType>
    class Registry {
    protected:
        std::unordered_map<uint32_t, std::unique_ptr<T>> objects;
        uint32_t nextId = 1;

    public:
        IDType create(std::unique_ptr<T> object) {
            if (!object) {
                throw std::invalid_argument("Cannot register null object");
            }
            IDType id(nextId++);
            objects[id.getValue()] = std::move(object);
            return id;
        }

        T* get(IDType id) const {
            auto it = objects.find(id.getValue());
            if (it == objects.end()) {
                throw std::runtime_error("Object not found");
            }
            return it->second.get();
        }

        virtual bool remove(IDType id) {
            return objects.erase(id.getValue()) > 0;
        }
        bool exists(IDType id) const {
            return objects.contains(id.getValue());
        }

        virtual ~Registry() = default;
    };

} // namespace monopoly