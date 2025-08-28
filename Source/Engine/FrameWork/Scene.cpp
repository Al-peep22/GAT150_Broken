#include "Scene.h"
#include "Actor.h"
#include "../Core/StringHelper.h"
#include "Scene.h"
#include "Components/ColliderComponent.h"

namespace viper{
	void Scene::Update(float dt) {
		//update all actors
		for (auto& actor : actors) {
			if (actor->active) { // Skip destroyed actors
				actor->Update(dt);
			}
		}

		/*std::erase_if(_actors, [](Actor actor) {
			return (actor->destroyed);
		});*/

		//remove destroyed actors
		for (auto iter = actors.begin(); iter != actors.end(); ) {
			if ((*iter)->destroyed) {
				iter = actors.erase(iter);
			}
			else {iter++;}
		}

		//check for collisions
		for (auto& actorA : actors) {
			for (auto& actorB : actors) {

				if (actorA == actorB || (actorA->destroyed || actorB->destroyed)) continue;
				
				auto colliderA = actorA->GetComponent<ColliderComponent>();
				auto colliderB = actorB->GetComponent<ColliderComponent>();
				
				if (!colliderA || !colliderB) continue; // Skip if no collider

				if (colliderA->CheckCollision(*colliderB)) {
					actorA->OnCollision(actorB.get());
					actorB->OnCollision(actorA.get());
				}
			}
		}
	}

	void Scene::Read(const json::value_t& value)
	{
		if (JSON_HAS(value, prototypes)) {
			for (auto& actorValue : JSON_GET(value, prototypes).GetArray()) {
				auto actor = Factory::Instance().Create<Actor>("Actor");
				actor->Read(actorValue);

				std::string name = actor->name;
				Factory::Instance().RegisterPrototype<Actor>(name, std::move(actor));
			}
		}

		if (JSON_HAS(value, actors)) {
			for (auto& actorValue : JSON_GET(value, actors).GetArray()) {
				auto actor = Factory::Instance().Create<Actor>("Actor");
				actor->Read(actorValue);

				AddActor(std::move(actor), false);
			}
		}
	}

	void Scene::Draw(Renderer& renderer) {
		for (auto& actor : actors) {
			//actor->Draw(renderer);
			if (actor->active) {
				actor->DrawT(renderer);
			}
		}
	}
	void Scene::AddActor(std::unique_ptr<Actor> actor, bool start)
	{
		actor->scene = this; // Set the scene for the actor
		if (start) actor->Start();
		actors.push_back(std::move(actor));
	}

	void Scene::RemoveAllActors(bool force) 
	{
		//actors.clear();
		for (auto iter = actors.begin(); iter != actors.end(); ) {
			if (!(*iter)->persistent || force) {
				iter = actors.erase(iter);
			}
			else { iter++; }
		}
	}

	bool Scene::Load(const std::string& sceneName) {
		// Load json
		json::document_t document;
		if (!json::Load(sceneName, document)) {
			Logger::Error("Could not load scene {}", sceneName);
			return false;
		}

		// Create scene
		Read(document);

		// Start actors
		for (auto& actor : _actors) {
			actor->Start();
		}

		return true;
	}

}