#pragma once
#include "FrameWork/Component.h"

namespace viper {
	class RendererComponent : public Component {
	public:
		virtual void Update(float dt) = 0;
		virtual void Draw(class Renderer& renderer) = 0;

	};
}