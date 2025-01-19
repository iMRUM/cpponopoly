#pragma once
#include <unordered_map>
#include <algorithm>
#include <memory>
#include <stdexcept>
#include "../Id.hpp"

namespace monopoly {
    template<typename T, typename IDType>
    class Registry {
    protected:
        std::unordered_map<uint32_t, std::shared_ptr<T>> objects;
        uint32_t nextId = 1;

    public:
        // Only way to register objects
        IDType registerObject(std::shared_ptr<T> object) {
            if (!object) {
                throw std::invalid_argument("Cannot register null object");
            }
            IDType id(nextId++);
            objects[id.getValue()] = object;
            return id;
        }

       std::shared_ptr<T> get(IDType id) {
            auto it = objects.find(id.getValue());
            if (it == objects.end()) {
                throw std::runtime_error("Object not found");
            }
            return it->second;
        }

        virtual bool remove(IDType id) {
            return objects.erase(id.getValue()) > 0;
        }

        bool exists(IDType id) const {
            return objects.contains(id.getValue());
        }

        const auto& getAllObjects() const { return objects; }

        std::vector<std::shared_ptr<T>>& getAllSharedPtrs() const {//TODO DELETE
            std::vector<std::shared_ptr<T>> result;
            result.reserve(objects.size());
            for (const auto& [_, obj] : objects) {
                result.push_back(obj);
            }
            return result;
        }
        [[nodiscard]] size_t getSize() const { return objects.size(); }
        virtual ~Registry() = default;
    };
}