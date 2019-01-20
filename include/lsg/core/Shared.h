#ifndef LSG_CORE_SHARED_H
#define LSG_CORE_SHARED_H

#include <memory>

namespace lsg {

template <typename T>
class Shared {
public:

  /**
   * @brief   Constructs wrapped object of type T using the provided arguments.
   *
   * @tparam	Args	T constructor arguments types.
   * @param   args	Constructor arguments.
   */
  template <typename... Args>
  explicit Shared(Args ... args);

  /**
   * @brief   Constructs the Shared object and initializes it with the given pointer.
   * @throws  If the given pointer is null or it cannot be cast to type T.
   *
   * @tparam	U	        Type of the input pointer.
   * @param	  init_ptr	Init shared pointer.
   */
  template <typename U, typename = std::enable_if<std::is_convertible<U, T>::value>>
  explicit Shared(std::shared_ptr<U> ptr);

  /**
   * @brief   Implicit conversion from Shared of type T to a Shared of type U.
   *
   * @tparam	U     Type of the converted Shared object. U must be convertible to T.
   */
  template <typename U, typename = std::enable_if<std::is_convertible<U, T>::value>>
  operator Shared<U>();

  /**
   * @brief   Dereferences wrapped object.
   *
   * @return	Pointer to the wrapped object.
   */
  T* operator->() const;

  /**
   * @brief   Retrieve pointer to wrapped object.
   *
   * @return	Pointer to wrapped object.
   */
  T* get() const;

private:
  /**
   * Shared pointer to the object.
   */
  std::shared_ptr<T> ptr_;
};

template <typename T>
template <typename... Args>
Shared<T>::Shared(Args... args)
  : ptr_(std::make_shared<T>(args...)) {}

template <typename T>
template <typename U, typename>
Shared<T>::Shared(std::shared_ptr<U> ptr)
  : ptr_(std::move(std::static_pointer_cast<T>(ptr))) {
  if (!ptr) {
    throw std::runtime_error("Tried to construct Shared with null pointer.");
  }

  // Check if the cast was successful.
  if (!ptr_) {
    throw std::bad_cast();
  }
}

template <typename T>
template <typename U, typename>
Shared<T>::operator Shared<U>() {
  return Shared<U>(ptr_);
}

template <typename T>
T* Shared<T>::operator->() const {
  return *ptr_;
}

template <typename T>
T* Shared<T>::get() const {
  return ptr_.get();
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
  template <typename U, typename = std::enable_if<std::is_convertible<U, T>::value>>
  explicit Ref(const Shared<U>& shared);

  /**
   * @brief   Implicit conversion from Reference of type T to a Reference of type U.
   *
   * @tparam	U     Type of the output Reference. T must be convertible to U.
   * @return  Reference to object of type U.
   */
  template <typename U, typename = std::enable_if<std::is_convertible<U, T>::value>>
  operator Ref<U>();

  /**
   * @brief   Assignment operator for Shared object of type U to a reference of type T.
   *
   * @tparam	U   Type of the Shared object. U must be convertible to T.
   * @param	  rhs	Right hand side Shared object.
   * @return	Reference to this.
   */
  template <typename U, typename = std::enable_if<std::is_convertible<U, T>::value>>
  Ref<T>& operator=(const Shared<U>& rhs);

  /**
   * @brief   Convert reference to Shared object (start sharing ownership).
   *
   * @tparam	U Type of the Shared.
   * @return	Return created Shared object.
   */
  template <typename U = T, typename = std::enable_if<std::is_convertible<T, U>::value>>
  Shared<U> toShared();

  /**
   * @brief   Convert reference to Shared object (start sharing ownership).
   *
   * @tparam	U Type of the Shared.
   */
  template <typename U = T, typename = std::enable_if<std::is_convertible<T, U>::value>>
  explicit operator Shared<U>();

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
template <typename U, typename>
Ref<T>::Ref(const Shared<U>& shared)
  : ptr_(static_cast<T*>(shared.get())) { }

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
Shared<U> Ref<T>::toShared() {
  return Shared<U>(ptr_->shared_from_this());
}

template <typename T>
template <typename U, typename>
Ref<T>::operator Shared<U>() {
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

}

#endif
