#pragma once
#include <vector>
#include <algorithm>
#include "IObserver.hpp"

namespace monopoly {
    // Generic observable interface
    template<typename Event>
    class IObservable {
    private:
        std::vector<IObserver<Event>*> observers;

    public:
        virtual ~IObservable() = default;

        void addObserver(IObserver<Event>* observer) {
            observers.push_back(observer);
        }

        void removeObserver(IObserver<Event>* observer) {
            observers.erase(
                std::remove(observers.begin(), observers.end(), observer),
                observers.end()
            );
        }

    protected:
        void notifyObservers(const Event& event) {
            for (auto observer : observers) {
                observer->onEvent(event);
            }
        }
    };
}