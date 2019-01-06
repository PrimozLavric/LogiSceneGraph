#include "Component.h"
#include <cmath>
namespace lsg {


Component::Component(const std::string& name, Object* owner) : Identifiable(name), owner_(owner) {
	std::log2(19);
}

}