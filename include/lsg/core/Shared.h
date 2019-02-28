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

#ifndef LSG_CORE_SHARED_H
#define LSG_CORE_SHARED_H

#include <memory>

namespace lsg {

template <typename T>
class Shared {
public:

  /**
   * @brief   Constructs wrapped object of type T using default constructor.
   */
  Shared();

  /**
   * @brief   Constructs the Shared object and initializes it with the given pointer.
   * @throws  If the given pointer is null or it cannot be cast to type T.
   *
   * @tparam	U	        Type of the input pointer.
   * @param	  ptr	Init shared pointer.
   */
  template <typename U, typename = std::enable_if<std::is_same<T, U>::value || std::is_base_of<T, U>::value>>
  explicit Shared(std::shared_ptr<U> ptr);

  /**
   * @brief   Creates shared object using the given arguments.
   * 
   * @tparam	Args  Argument types.
   * @param	  args  Arguments.
   * @return	Created shared object.
   */
  template <typename... Args>
  static Shared<T> create(Args... args);

  /**
   * @brief   Implicit conversion from Shared of type T to a Shared of type U.
   *
   * @tparam	U     Type of the converted Shared object. U must be convertible to T.
   */
  template <typename U, typename = std::enable_if<std::is_same<T, U>::value || std::is_base_of<U, T>::value>>
  operator Shared<U>() const;

  /**
   * @brief   Dynamically cast to Shared of type U.
   * 
   * @tparam	U Type to cast to.
   * @return	Shared<U>.
   */
  template <typename U>
  Shared<U> dynamicCast() const;

  /**
   * @brief   Statically cast to Shared of type U.
   *
   * @tparam	U Type to cast to.
   * @return	Shared<U>.
   */
  template <typename U>
  Shared<U> staticCast() const;

  /**
   * @brief   Conversion to boolean that is true if underlying shared_ptr is not null.
   *
   * @return  True if underlying shared_ptr is not null.
   */
  operator bool() const;

  /**
   * @brief   Dereferences wrapped object.
   *
   * @return	Pointer to the wrapped object.
   */
  T* operator->() const;

  /**
   * @brief   Dereferences wrapped object.
   *
   * @return	Const reference to the wrapped object.
   */
  const T& operator*() const;

  /**
   * @brief   Retrieve pointer to wrapped object.
   *
   * @return	Pointer to wrapped object.
   */
  T* get() const;

  /**
   * @brief Reset underlying shared ptr.
   */
  void reset();

private:
  /**
   * Shared pointer to the object.
   */
  std::shared_ptr<T> ptr_;
};

template <typename T>
Shared<T>::Shared() : ptr_(nullptr) {}

template <typename T>
template <typename U, typename>
Shared<T>::Shared(std::shared_ptr<U> ptr)
  : ptr_(std::move(std::static_pointer_cast<T>(std::move(ptr)))) { }

template <typename T>
template <typename ... Args>
Shared<T> Shared<T>::create(Args... args) {
	return Shared<T>(std::make_shared<T>(args...));
}

template <typename T>
template <typename U, typename>
Shared<T>::operator Shared<U>() const {
  return Shared<U>(ptr_);
}

template <typename T>
template <typename U>
Shared<U> Shared<T>::dynamicCast() const {
	return Shared<U>(std::dynamic_pointer_cast<U>(ptr_));
}

template <typename T>
template <typename U>
Shared<U> Shared<T>::staticCast() const {
	return Shared<U>(std::static_pointer_cast<U>(ptr_));
}

template <typename T>
Shared<T>::operator bool() const {
	return static_cast<bool>(ptr_);
}

template <typename T>
T* Shared<T>::operator->() const {
  return ptr_.get();
}

template <typename T>
const T& Shared<T>::operator*() const {
	return *ptr_;
}

template <typename T>
T* Shared<T>::get() const {
  return ptr_.get();
}

template <typename T>
void Shared<T>::reset() {
	ptr_.reset();
}


template <typename T>
class Ref {
public:
  /**
   * @brief Construct Reference object with the given pointer.
   *
   * @param	ptr Pointer used to initialize reference object. Default = nullptr.
   */
  explicit Ref(T* ptr = nullptr);

  /**
   * @brief   Construct Reference object that refers to the given shared object.
   *
   * @tparam	U       Type of the Shared object. U must be convertible to T.
   * @param   shared  Shared object of type U.
   */
  template <typename U>
  Ref(const Shared<U>& shared);

  /**
   * @brief   Implicit conversion from Reference of type T to a Reference of type U.
   *
   * @tparam	U     Type of the output Reference. T must be convertible to U.
   * @return  Reference to object of type U.
   */
  template <typename U, typename = std::enable_if<std::is_same<T, U>::value || std::is_base_of<U, T>::value>>
  operator Ref<U>();

  /**
   * @brief   Assignment operator for Shared object of type U to a reference of type T.
   *
   * @tparam	U   Type of the Shared object. U must be convertible to T.
   * @param	  rhs	Right hand side Shared object.
   * @return	Reference to this.
   */
  template <typename U, typename = std::enable_if<std::is_same<T, U>::value || std::is_base_of<T, U>::value>>
  Ref<T>& operator=(const Shared<U>& rhs);

  /**
   * @brief   Convert reference to Shared object (start sharing ownership).
   *
   * @tparam	U Type of the Shared.
   * @return	Return created Shared object.
   */
  template <typename U = T, typename = std::enable_if<std::is_same<T, U>::value || std::is_base_of<U, T>::value>>
  Shared<U> toShared() const;

  /**
 * @brief   Dynamically cast to Ref of type U.
 *
 * @tparam	U Type to cast to.
 * @return	Refe<U>.
 */
  template <typename U>
  Ref<U> dynamicCast() const;

  /**
   * @brief   Statically cast to Ref of type U.
   *
   * @tparam	U Type to cast to.
   * @return	Ref<U>.
   */
  template <typename U>
  Ref<U> staticCast() const;

  /**
   * @brief   Convert reference to Shared object (start sharing ownership).
   *
   * @tparam	U Type of the Shared.
   */
  template <typename U = T, typename = std::enable_if<std::is_same<T, U>::value || std::is_base_of<U, T>::value>>
  explicit operator Shared<U>() const;

  /**
   * @brief   Conversion to boolean that is true if reference is not null.
   *
   * @return  True if reference is not null.
   */
  operator bool() const;

  /**
   * @brief   Dereferences the refereed object.
   *
   * @return	Pointer to the referenced object of type T.
   */
  T* operator->() const;

  /**
   * @brief   Retrieves pointer that points to the refereed object. 
   *
   * @return	Pointer to the referenced object of type T.
   */
  T* get() const;

  /**
   * @brief Reset reference.
   */
  void reset();

private:
  /**
   * Points to the referenced object.
   */
  T* ptr_;
};

template <typename T>
Ref<T>::Ref(T* ptr)
  : ptr_(ptr) { }

template <typename T>
template <typename U>
Ref<T>::Ref(const Shared<U>& shared) : ptr_(nullptr) {
	if constexpr (std::is_same<T, U>::value || std::is_base_of<T, U>::value) {
		ptr_ = static_cast<T*>(shared.get());
	} else {
		ptr_ = dynamic_cast<T*>(shared.get());
	}
}

template <typename T>
template <typename U, typename>
Ref<T>::operator Ref<U>() {
	return Ref<U>(static_cast<U*>(ptr_));
}

template <typename T>
template <typename U, typename>
Ref<T>& Ref<T>::operator=(const Shared<U>& rhs) {
  ptr_ = static_cast<T*>(rhs.get());
  return *this;
}

template <typename T>
template <typename U, typename>
Shared<U> Ref<T>::toShared() const {
  return Shared<U>(ptr_->shared_from_this());
}

template <typename T>
template <typename U>
Ref<U> Ref<T>::dynamicCast() const {
	return Ref<U>(dynamic_cast<U*>(ptr_));
}

template <typename T>
template <typename U>
Ref<U> Ref<T>::staticCast() const {
	return Ref<U>(static_cast<U*>(ptr_));
}

template <typename T>
template <typename U, typename>
Ref<T>::operator Shared<U>() const {
  return Shared<U>(ptr_->shared_from_this());
}

template <typename T>
Ref<T>::operator bool() const {
  return ptr_ != nullptr;
}

template <typename T>
T* Ref<T>::operator->() const {
  return ptr_;
}

template <typename T>
T* Ref<T>::get() const {
  return ptr_;
}

template <typename T>
void Ref<T>::reset() {
	ptr_ = nullptr;
}

}

#endif
