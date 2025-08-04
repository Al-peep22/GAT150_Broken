#pragma once
#include <vector>
#include <memory>
#include "Actor.h"
#include <list>

namespace viper{
	class Game;
	class Actor;

	class Scene {
	public:
		Scene(Game* game) : game{ game } {}

		void Update(float dt);
		void Draw(class Renderer& renderer);

		void AddActor(std::unique_ptr<Actor> actor);
		void RemoveAllActors();

		template<typename T = Actor>
		T* GetActorByName(const std::string& name);

		template<typename T = Actor>
		std::vector<T*> GetActorsByTag(const std::string& tag);

		class Game* GetGame() { return game; }

	private:
		class Game* game{nullptr};
		std::list<std::unique_ptr<Actor>> actors;
	};
 
	template<typename T>
	inline T* Scene::GetActorByName(const std::string& name)
	{
		for (auto& actor : actors) {
            if (actor->name == name) {
                T* object = dynamic_cast<T*>(actor.get());
                if (object) {
                    return object;
                }
            }
        }
        return nullptr;
	}

	template<typename T>
	inline std::vector<T*> Scene::GetActorsByTag(const std::string& tag)
	{
		std::vector<T*> results;
		for (auto& actor : actors) {
			if (actor->tag == tag) {
				T* object = dynamic_cast<T*>(actor.get());
				if (object) {
					results.push_back(object);
				}
			}
		}
		return results;
	}
}