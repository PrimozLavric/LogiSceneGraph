#include "lsg/core/Component.h"
#include <cmath>
namespace lsg {


Component::Component(const std::string& name, const Ref<Object> owner) : Identifiable(name), owner_(owner) {
}

Component::~Component() = default;

}
