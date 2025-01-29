#pragma once
#include <memory>

template<typename T>
class IFactory {
protected:
  IFactory() = default;
  IFactory(const IFactory&) = delete;
  IFactory& operator=(const IFactory&) = delete;
  IFactory(IFactory&&) = delete;
  IFactory& operator=(IFactory&&) = delete;
public:
  virtual IFactory() = default;
  virtual std::unique_ptr<T> create() const = 0;
};
