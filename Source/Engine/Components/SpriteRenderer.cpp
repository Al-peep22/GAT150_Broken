#include "EngineCPH.h"
#include "SpriteRenderer.h"
#include "Renderer/Renderer.h"
#include "Engine.h"
namespace viper {

	FACTORY_REGISTER(SpriteRenderer);

	void SpriteRenderer::Start() {
		texture = Resources().Get<Texture>(textureName, GetEngine().GetRenderer());
	}

	void SpriteRenderer::Update(float dt)
	{
		//
	}

	void SpriteRenderer::Draw(Renderer& renderer)
	{
		auto texture = Resources().Get<Texture>(textureName, renderer);
		if (texture) {
			renderer.DrawTexture(*texture,
			owner->transform.position.x,
			owner->transform.position.y,
			owner->transform.scale,
			owner->transform.rotation);
		}
	}
	void SpriteRenderer::Read(const json::value_t& value)
	{
		Object::Read(value);
		//JSON_READ(value,textureName);
		JSON_READ_NAME(value, "texture_name", textureName);
	}
}
