#ifndef LSG_CORE_COMPONENT_H
#define LSG_CORE_COMPONENT_H

#include <string>

#include "lsg/core/Identifiable.h"

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

#endif  //LSG_CORE_COMPONENT_H