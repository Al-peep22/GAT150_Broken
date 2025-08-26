#pragma once
#include "Components/RendererComponent.h"
#include "FrameWork/Component.h"

namespace viper {
	class RigidBody : public Component {
	public:
		vec2 velocity;
		float damping{0};
	public:
		CLASS_PROTOTYPE(RigidBody);
		RigidBody() = default;
		void Update(float dt) override;
		void Draw(class Renderer& renderer);
		void Read(const json::value_t& value) override;
	private:
	};
}