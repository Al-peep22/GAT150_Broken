#pragma once
#include "Components/RendererComponent.h"
#include "FrameWork/Component.h"

namespace viper {
	class RigidBody : public Component {
	public:
		vec2 velocity;
		float damping{0};
	public:
		RigidBody() = default;
		void Update(float dt) override;
		void Draw(class Renderer& renderer);
	private:
	};
}