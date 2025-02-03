#pragma once
class Controller;
class IMonopolyState {
public:
    virtual ~IMonopolyState() = default;
    virtual void execute() = 0;
};