#ifndef LSG_CORE_COMPONENT_H
#define LSG_CORE_COMPONENT_H

#include <string>

#include "lsg/core/Identifiable.h"

namespace lsg {

class Object;

class Component : public Identifiable, public std::enable_shared_from_this<Component> {
public:
  explicit Component(const std::string& name, Object* owner);

  virtual ~Component() = 0;

protected:
	Object* owner_;
};

}

#endif  //LSG_CORE_COMPONENT_H