#pragma once


namespace monopoly {
    // Generic observer interface
    template<typename Event>
    class IObserver {
    public:
        virtual ~IObserver() = default;
        virtual void onEvent(const Event& event) = 0;
    };
}