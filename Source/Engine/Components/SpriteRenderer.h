#pragma once
#include "Components/RendererComponent.h"

namespace viper{
	class SpriteRenderer : public RendererComponent {
	public:
		std::string textureName;
	public:
		SpriteRenderer() = default;
		void Update(float dt) override;
		void Draw(class Renderer& renderer) override;
	private:
	};
}