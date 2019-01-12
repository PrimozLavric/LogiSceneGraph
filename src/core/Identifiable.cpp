#include "lsg/core/Identifiable.h"

namespace lsg {

std::atomic<size_t> Identifiable::next_id_ = {0};

Identifiable::Identifiable(std::string name)
  : id_(next_id_.fetch_add(1u, std::memory_order::memory_order_relaxed)), name_(std::move(name)) { }

Identifiable::Identifiable(Identifiable&& other) noexcept
  : id_(other.id_), name_(std::move(other.name_)) {}

Identifiable::Identifiable(const Identifiable& other)
  : id_(next_id_.fetch_add(1u, std::memory_order::memory_order_relaxed)),
    name_(other.name_) {}

Identifiable& Identifiable::operator=(Identifiable&& rhs) noexcept {
	id_ = rhs.id_;
	name_ = std::move(rhs.name_);
	return *this;
}

Identifiable& Identifiable::operator=(const Identifiable& rhs) {
	name_ = rhs.name_;
	return *this;
}

size_t Identifiable::id() const {
	return id_;
}

std::string_view Identifiable::name() const {
	return std::string_view(name_.c_str(), name_.size());
}

}
