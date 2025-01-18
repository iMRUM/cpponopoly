#pragma once
#include "IObservable.hpp"

namespace monopoly {
    // Multi-event observable - a base class for observables that emit multiple event types
    template<typename... Events>
    class MultiObservable : public IObservable<Events>... {
        public:
        virtual ~MultiObservable() = default;
        using IObservable<Events>::addObserver...;
        using IObservable<Events>::removeObserver...;
        using IObservable<Events>::notifyObservers...;
    };
}
