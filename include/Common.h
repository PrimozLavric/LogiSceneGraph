#pragma once
#include <memory>

namespace lsg {

template <typename T>
using Ref = std::shared_ptr<T>;

template <typename T, typename... Args>
auto make_ref(Args&&... args) -> decltype(std::make_shared<T>(std::forward<Args>(args)...)) {
	return std::make_shared<T>(std::forward<Args>(args)...);
}

}
