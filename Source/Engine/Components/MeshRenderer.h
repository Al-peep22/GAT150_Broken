#pragma once
#include "Components/RendererComponent.h"

namespace viper {
	class MeshRenderer : public RendererComponent {
	public:
		std::string meshName;
	public:
		MeshRenderer() = default;
		void Update(float dt) override;
		void Draw(class Renderer& renderer) override;
	private:
	};
}