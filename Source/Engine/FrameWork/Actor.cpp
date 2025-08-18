#include "../FrameWork/Actor.h"
#include "../Renderer/Mesh.h"
#include "../Renderer/Renderer.h"
#include "../Components/RendererComponent.h"

namespace viper {
	void viper::Actor::Update(float dt)
	{
		if (destroyed) return;

		if (lifespan > 0) {
			lifespan -= dt;
			if (lifespan <= 0) {
				destroyed = true;
				return;
			}
		}

		for (auto& component : components) {
			if (component->active) {
				component->Update(dt);
			}
		}		
	}

	void viper::Actor::Draw(Renderer& renderer)
	{
		if (destroyed) return;

		Mesh->Draw(renderer, transform);

	}

	void viper::Actor::DrawT(Renderer& renderer)
	{
		if (destroyed) return;

		for (auto& component : components) {
			if (component->active) {
				auto rendererComponent = dynamic_cast<RendererComponent*>(component.get());
				if (rendererComponent) {
					rendererComponent->Draw(renderer);
				}
			}
		}

		//renderer.DrawTexture(texture.get(), transform.position.x, transform.position.y, transform.scale, transform.rotation);

	}

	/*float Actor::GetRadius()
	{
		return (Mesh) ? Mesh->GetRadius() * transform.scale * 0.8f : 0.0f;
	}*/

	float Actor::GetRadiusT()
	{
		return 50.0f;//(texture) ? (texture->GetSize().Length() * 0.5f) * transform.scale * 0.3f : 0.0f;
	}

	void Actor::AddComponent(std::unique_ptr<Component> component)
	{
		component->owner = this; // Set the owner of the component to this actor
		components.push_back(std::move(component));
	}

}
