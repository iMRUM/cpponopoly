// IRegistry.hpp
#pragma once
#include <memory>
#include <vector>
template<typename T, typename Id>
class IRegistry {
//private:

public:
    virtual ~IRegistry() = default;

    virtual void registerItem(std::unique_ptr<T> item) = 0;

    virtual T *getById(const Id &id) const {
        for (const auto& item : objects) {
            if (item->getId() == id) {
                return item.get();
            }
        }
        return nullptr;
    }

    virtual T& getByIdRef(int index) const {
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
    class iterator {
    private:
        typename std::vector<std::unique_ptr<T>>::iterator it;
    public:
        using iterator_category = std::forward_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = T;
        using pointer = T*;
        using reference = T&;

        explicit iterator(typename std::vector<std::unique_ptr<T>>::iterator iterator)
            : it(iterator) {}

        reference operator*() const { return *it->get(); }
        pointer operator->() const { return it->get(); }

        iterator& operator++() {
            ++it;
            return *this;
        }

        iterator operator++(int) {
            iterator tmp = *this;
            ++it;
            return tmp;
        }

        bool operator==(const iterator& other) const { return it == other.it; }
        bool operator!=(const iterator& other) const { return it != other.it; }
    };

    class const_iterator {
    private:
        typename std::vector<std::unique_ptr<T>>::const_iterator it;
    public:
        using iterator_category = std::forward_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = const T;
        using pointer = const T*;
        using reference = const T&;

        explicit const_iterator(typename std::vector<std::unique_ptr<T>>::const_iterator iterator)
            : it(iterator) {}

        reference operator*() const { return *it->get(); }
        pointer operator->() const { return it->get(); }

        const_iterator& operator++() {
            ++it;
            return *this;
        }

        const_iterator operator++(int) {
            const_iterator tmp = *this;
            ++it;
            return tmp;
        }

        bool operator==(const const_iterator& other) const { return it == other.it; }
        bool operator!=(const const_iterator& other) const { return it != other.it; }
    };

    [[nodiscard]] const_iterator begin() const { return const_iterator(objects.begin()); }
    [[nodiscard]] const_iterator end() const { return const_iterator(objects.end()); }
    [[nodiscard]] const_iterator cbegin() const { return const_iterator(objects.cbegin()); }
    [[nodiscard]] const_iterator cend() const { return const_iterator(objects.cend()); }

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