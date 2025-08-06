#include "../FrameWork/Actor.h"
#include "../Renderer/Model.h"
#include "../Renderer/Renderer.h"

namespace viper {
	void viper::Actor::Update(float dt)
	{
		if (destroyed) return;

		if (lifespan != 0) {
			lifespan -= dt;
			destroyed = (lifespan <= 0);
		}

		transform.position += velocity * dt;
		velocity *= (1.0f / (1.0f + damping * dt));
	}

	void viper::Actor::Draw(Renderer& renderer)
	{
		if (destroyed) return;

		model->Draw(renderer, transform);

	}

	void viper::Actor::DrawT(Renderer& renderer)
	{
		if (destroyed) return;

		renderer.DrawTexture(texture.get(), transform.position.x, transform.position.y, transform.scale, transform.rotation);

	}

	float Actor::GetRadius()
	{
		return (model) ? model->GetRadius() * transform.scale * 0.8f : 0.0f;
	}

	float Actor::GetRadiusT()
	{
		return (texture) ? (texture->GetSize().Length() * 0.5f) * transform.scale * 0.8f : 0.0f;
	} 
}
