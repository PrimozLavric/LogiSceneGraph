#pragma once
#include <string>

#include "Identifiable.h"

namespace lsg {

class Object;

class Component : public Identifiable {
public:
  explicit Component(const std::string& name, Object* owner);

  virtual ~Component() = default;

protected:
	Object* owner_;
};

}