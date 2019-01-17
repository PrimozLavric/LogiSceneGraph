#ifndef LSG_CORE_SHARED_H
#define LSG_CORE_SHARED_H

#include <memory>

namespace lsg {

template <typename T>
class Shared {
public:
  template <typename... Args>
  explicit Shared(Args ... args);

  explicit Shared(std::shared_ptr<T> ptr);

  Shared* operator->() {
	  return *ptr_;
  }

private:
	std::shared_ptr<T> ptr_;
};

template <typename T>
template <typename ... Args>
Shared<T>::Shared(Args ... args): ptr_(std::make_shared<T>(args...)) {}

template <typename T>
Shared<T>::Shared(std::shared_ptr<T> ptr) : ptr_(std::move(ptr)) {
  
}

template <typename T>
class Ref {
  
};

}

#endif
