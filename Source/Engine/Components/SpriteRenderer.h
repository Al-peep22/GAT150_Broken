#pragma once
#include "Components/RendererComponent.h"
#include "Core/Serializable.h"

namespace viper{
	class SpriteRenderer : public RendererComponent {
	public:
		std::string textureName;
		rect textureRect;
		res_t<Texture> texture;
		bool flipH{ false };
	public:
		virtual std::unique_ptr<Object> Clone() const {
			return std::make_unique<SpriteRenderer>(*this);
		};

		void Start() override;
		void Update(float dt) override;
		void Draw(class Renderer& renderer) override;
	
		void Read(const json::value_t& value) override;
	};
}