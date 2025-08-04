#include "Scene.h"
#include "Actor.h"
#include "../Core/StringHelper.h"
#include "Scene.h"
namespace viper{
	void Scene::Update(float dt) {
		//update all actors
		for (auto& actor : actors) {
			actor->Update(dt);
		}

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
				float distance = (actorA->transform.position - actorB->transform.position).Length();
				if (distance <= actorA->GetRadius() + actorB->GetRadius()) {
					actorA->OnCollision(actorB.get());
					actorB->OnCollision(actorA.get());
				}
			}
		}
	}
	void Scene::Draw(Renderer& renderer) {
		for (auto& actor : actors) {
			actor->Draw(renderer);
		}
	}
	void Scene::AddActor(std::unique_ptr<Actor> actor)
	{
		actor->scene = this; // Set the scene for the actor
		actors.push_back(std::move(actor));
	}

	void Scene::RemoveAllActors() 
	{
		actors.clear();
	}
}