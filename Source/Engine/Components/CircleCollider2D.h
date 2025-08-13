#pragma once
#include "Components/RendererComponent.h"

namespace viper {
	class CircleCollider2D : public RendererComponent {
		/*public:
			std::string textureName;*/
	public:
		CircleCollider2D() = default;
		void Update(float dt) override;
		void Draw(class Renderer& renderer) override;
	private:
	};
}