#ifndef LSG_CORE_COMPONENT_H
#define LSG_CORE_COMPONENT_H

#include <string>

#include "lsg/core/Identifiable.h"
#include "Shared.h"

namespace lsg {

class Object;

class Component : public Identifiable, public std::enable_shared_from_this<Component> {
public:
  explicit Component(const std::string& name, Ref<Object> owner);

  virtual ~Component();

protected:
	Ref<Object> owner_;
};

}

#endif  //LSG_CORE_COMPONENT_H