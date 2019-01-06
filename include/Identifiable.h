#pragma once

#include <string>
#include <atomic>

namespace lsg {

class Identifiable {
public:
  explicit Identifiable(std::string name);
  
  Identifiable(Identifiable&& other) noexcept;

  Identifiable(const Identifiable& other);

  Identifiable& operator=(Identifiable&& rhs) noexcept;

  Identifiable& operator=(const Identifiable& rhs);

  size_t id() const;

  std::string_view name() const;

  virtual ~Identifiable() = default;

private:
	static std::atomic<size_t> next_id_;

	size_t id_;
  std::string name_;
};

}
