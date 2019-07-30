/**
 * Project LogiSceneGraph source code
 * Copyright (C) 2019 Primoz Lavric
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef LSG_CORE_REF_HPP
#define LSG_CORE_REF_HPP

#include <atomic>
#include <cstdlib>
#include <iostream>

namespace lsg {

template <typename DerivedT>
class RefCounter {
  template <typename T>
  friend class Ref;

 public:
  RefCounter() noexcept : ref_counter_(0) {}

  RefCounter(const RefCounter&) noexcept : ref_counter_(0) {}

  RefCounter& operator=(const RefCounter&) noexcept {
    return *this;
  }

  size_t useCount() const noexcept {
    return ref_counter_.load();
  }

 protected:
  ~RefCounter() = default;

 private:
  void addRef() const noexcept {
    ref_counter_.fetch_add(1u, std::memory_order_acq_rel);
  }

  void release() const noexcept {
    if (ref_counter_.fetch_sub(1u, std::memory_order_acq_rel) == 1u) {
      delete static_cast<const DerivedT*>(this);
    };
  }

  mutable std::atomic<size_t> ref_counter_;
};

template <typename T>
class Ref {
  template <class U>
  friend class Ref;

 public:
  constexpr Ref() noexcept : ptr_(nullptr) {}

  Ref(T* ptr, bool add_ref = true) : ptr_(ptr) {
    if (ptr_ != nullptr && add_ref) {
      ptr_->addRef();
    }
  }

  template <class U>
  Ref(const Ref<U>& rhs) : ptr_(rhs.get()) {
    if (ptr_ != nullptr) {
      ptr_->addRef();
    }
  }

  Ref(const Ref<T>& rhs) : ptr_(rhs.get()) {
    if (ptr_ != nullptr) {
      ptr_->addRef();
    }
  }

  Ref(Ref&& rhs) noexcept : ptr_(rhs.ptr_) {
    rhs.ptr_ = nullptr;
  }

  template <class U>
  Ref(Ref<U>&& rhs) : ptr_(rhs.ptr_) {
    rhs.ptr_ = nullptr;
  }

  Ref& operator=(Ref&& rhs) noexcept {
    if (ptr_ != nullptr) {
      ptr_->release();
    }

    ptr_ = rhs.ptr_;
    rhs.ptr_ = nullptr;
    return *this;
  }

  template <class U>
  Ref& operator=(Ref<U>&& rhs) noexcept {
    if (ptr_ != nullptr) {
      ptr_->release();
    }

    ptr_ = rhs.ptr_;
    rhs.ptr_ = nullptr;
    return *this;
  }

  Ref& operator=(const Ref& rhs) {
    if (ptr_ != nullptr) {
      ptr_->release();
    }
    ptr_ = rhs.ptr_;
    ptr_->addRef();
    return *this;
  }

  Ref& operator=(T* rhs) {
    if (ptr_ != nullptr) {
      ptr_->release();
    }
    ptr_ = rhs;
    ptr_->addRef();
    return *this;
  }

  void reset() {
    if (ptr_ != nullptr) {
      ptr_->release();
      ptr_ = nullptr;
    }
  }

  T* get() const noexcept {
    return ptr_;
  }

  T* detach() noexcept {
    T* ret = ptr_;
    ptr_ = nullptr;
    return ret;
  }

  void swap(Ref& rhs) noexcept {
    T* tmp = ptr_;
    ptr_ = rhs.ptr_;
    rhs.ptr_ = tmp;
  }

  operator bool() const {
    return ptr_ != nullptr;
  }

  T& operator*() const noexcept {
    return *ptr_;
  }

  T* operator->() const noexcept {
    return ptr_;
  }

  template <typename U>
  bool operator<(const Ref<U>& rhs) noexcept {
    return std::less<U*>()(ptr_, rhs.get());
  }

  template <typename U>
  bool operator==(const Ref<U>& rhs) noexcept {
    return ptr_ == rhs.get();
  }

  template <typename U>
  bool operator==(U* rhs) noexcept {
    return ptr_ == rhs;
  }

  template <typename U>
  bool operator!=(const Ref<U>& rhs) noexcept {
    return ptr_ != rhs.get();
  }

  template <typename U>
  bool operator!=(U* rhs) noexcept {
    return ptr_ != rhs;
  }

  ~Ref() {
    if (ptr_ != nullptr) {
      ptr_->release();
    }
  }

 private:
  T* ptr_;
};

template <typename T, typename U>
Ref<T> staticRefCast(const Ref<U>& r) {
  return static_cast<T*>(r.get());
}

template <class T, class U>
Ref<T> constRefCast(const Ref<U>& r) {
  return const_cast<T*>(r.get());
}

template <class T, class U>
Ref<T> dynamicRefCast(const Ref<U>& r) {
  return dynamic_cast<T*>(r.get());
}

template <class T, class U>
Ref<T> staticRefCast(Ref<U>&& p) noexcept {
  return Ref<T>(static_cast<T*>(p.detach()), false);
}

template <class T, class U>
Ref<T> constRefCast(Ref<U>&& p) noexcept {
  return Ref<T>(const_cast<T*>(p.detach()), false);
}

template <class T, class U>
Ref<T> dynamicRefCast(Ref<U>&& p) noexcept {
  T* p2 = dynamic_cast<T*>(p.get());

  Ref<T> r(p2, false);

  if (p2)
    p.detach();

  return r;
}

template <typename T, typename... Args>
Ref<T> makeRef(Args&&... args) {
  return Ref<T>(new T(args...));
}

} // namespace lsg

#endif // LSG_CORE_REF_HPP
