// IRegistry.hpp
#pragma once
#include <memory>
#include <vector>
template<typename T, typename Id>
class IRegistry {
public:
    virtual ~IRegistry() = default;

    virtual void registerItem(std::unique_ptr<T> item) = 0;

    virtual T& getById(const Id& id) const {
        for (const auto& item : objects) {
            if (item->getId() == id) {
                return *item.get();
            }
        }
        throw std::runtime_error("Item not found");
    }

    virtual T& getByIndex(int index) const {
        if (index < 0 || static_cast<size_t>(index) >= objects.size()) {
            throw std::out_of_range("Index out of bounds");
        }
        return *objects[index].get();
    }

    virtual bool exists(const Id& id) const {
        for (const auto& item : objects) {
            if (item->getId() == id) {
                return true;
            }
        }
        return false;
    }

    virtual void remove(const Id& id) {
        auto iterator = objects.begin();
        while (iterator != objects.end()) {
            if ((*iterator)->getId() == id) {
                objects.erase(iterator);
                return;
            }
            ++iterator;
        }
    }

    virtual void clear() {
        objects.clear();
    }

    virtual const std::vector<std::unique_ptr<T>>& getAll() const {
        return objects;
    }

    virtual size_t size() const {
        return objects.size();
    }

    virtual bool empty() const {
        return objects.empty();
    }

    virtual auto begin() const -> typename std::vector<std::unique_ptr<T>>::const_iterator {
        return objects.begin();
    }

    virtual auto end() const -> typename std::vector<std::unique_ptr<T>>::const_iterator {
        return objects.end();
    }

    // Prevent copying/moving
    IRegistry(const IRegistry&) = delete;
    IRegistry& operator=(const IRegistry&) = delete;
    IRegistry(IRegistry&&) = delete;
    IRegistry& operator=(IRegistry&&) = delete;

protected:
    std::vector<std::unique_ptr<T>> objects;
    explicit IRegistry(size_t initialCapacity = 0) {
        if (initialCapacity > 0) {
            objects.reserve(initialCapacity);
        }
    }
};