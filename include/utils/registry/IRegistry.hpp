// IRegistry.hpp
#pragma once
#include <memory>
#include <vector>

namespace monopoly {
    template<typename T>
    class IRegistry {
    public:
        virtual ~IRegistry() = default;

        // Basic registry operations
        virtual void registerItem(std::unique_ptr<T> item) {

        }
        virtual T &getById(int id) const = 0;
        [[nodiscard]] virtual bool exists(int id) const = 0;
        virtual void remove(int id) = 0;
        virtual void clear() = 0;

        // Collection operations
        virtual std::vector<std::unique_ptr<T>> &getAll() const = 0;
        [[nodiscard]] virtual size_t getSize() const = 0;

        // Prevent copying/moving
        IRegistry(const IRegistry&) = delete;
        IRegistry& operator=(const IRegistry&) = delete;
        IRegistry(IRegistry&&) = delete;
        IRegistry& operator=(IRegistry&&) = delete;

    protected:
        std::vector<std::unique_ptr<T>> objects;
        IRegistry(size_t size) {
            objects.reserve(size);
        }
    };
}