#pragma once
#include "FrameWork/Component.h"

namespace viper {
	class ColliderComponent : public Component {
	public:

		virtual bool CheckCollision(ColliderComponent& other) = 0;

	};
}