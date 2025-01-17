#pragma once
#include <vector>
#include <algorithm>

namespace monopoly {

    // Generic observer interface
    template<typename Event>
    class IObserver {
    public:
        virtual ~IObserver() = default;
        virtual void onEvent(const Event& event) = 0;
    };