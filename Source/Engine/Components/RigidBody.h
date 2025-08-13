#pragma once
#include "Components/RendererComponent.h"

namespace viper {
	class RigidBody : public RendererComponent {
		/*public:
			std::string textureName;*/
	public:
		RigidBody() = default;
		void Update(float dt) override;
		void Draw(class Renderer& renderer) override;
	private:
	};
}