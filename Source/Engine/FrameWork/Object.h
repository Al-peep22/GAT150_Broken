#pragma once
#include <string>

namespace viper {
	class Object {
	public:
		std::string name;
		bool active{ false };
	public:
		Object() = default;
		~Object() = default;
	};
}