#include "../FrameWork/Actor.h"
#include "../Renderer/Mesh.h"
#include "../Renderer/Renderer.h"
#include "../Components/RendererComponent.h"


namespace viper {
	FACTORY_REGISTER(Actor);

	Actor::Actor(const Actor& other) : 
		Object{ other },
		tag{ other.tag },
		lifespan{ other.lifespan },
		transform{ other.transform }

	{
		for (auto& component : other.components) {
			auto clone = std::unique_ptr<Component>(dynamic_cast<Component*>(component->Clone().release()));
			components.push_back(std::move(clone));
		}
	}

	void Actor::Start() {
		for (auto& component : _components) {
			component->Start();
		}
	}

	void Actor::Destroyed() {
		for (auto& component : _components) {
			component->Destroyed();
		}
	}

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

	void Actor::OnCollision(Actor* other) {
		auto collidables = GetComponents<ICollidable>();

		for (auto& collidable : collidables) {
			collidable->OnCollision(other);
		}
	}

	void Actor::AddComponent(std::unique_ptr<Component> component)
	{
		component->owner = this; // Set the owner of the component to this actor
		components.push_back(std::move(component));
	}

	void Actor::Read(const json::value_t& value)
	{
		Object::Read(value);

		JSON_READ(value,tag);
		JSON_READ(value,lifespan);
		JSON_READ(value, persistent);


		if (JSON_HAS(value, transform)) transform.Read(JSON_GET(value, transform));

		if (JSON_HAS(value, components)) {
			for (auto& componentValue : JSON_GET(value, components).GetArray()) {

				std::string type;
				JSON_READ(componentValue, type);

				auto component = Factory::Instance().Create<Component>(type);
				component->Read(componentValue);

				AddComponent(std::move(component));
			}
		}
	}

}
