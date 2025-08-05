#pragma once
#include <memory>

namespace viper {
	class Resource {
	public:
		Resource() = default;
		~Resource() = default;
	};

	template <typename T = Resource>
	using res_t = std::shared_ptr<T>;
}