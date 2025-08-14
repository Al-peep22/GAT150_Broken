#pragma once
#include "Math/Transform.h"
#include <string>
#include <memory>
#include <Renderer/Texture.h>
#include "FrameWork/Object.h"
#include <vector>
#include "Component.h"

namespace viper {
	class Actor : public Object{
	public:
		std::string name;
		std::string tag;

		bool destroyed{ false };
		float lifespan{ 0 };
	

		Transform transform;
		class Scene* scene{ nullptr };

	public:
		Actor() = default;
		Actor(const viper::Transform& transform, std::shared_ptr<class Model> model) :
			transform{ transform }, 
			model{ model } {}

		Actor(const viper::Transform& transform, viper::res_t<viper::Texture> texture) :
			transform{ transform }, 
			texture{ texture } {}

		Actor(const viper::Transform& transform) :
			transform{ transform } {}

		virtual void Update(float dt);
		virtual void Draw(class Renderer& renderer);
		virtual void DrawT(class Renderer& renderer);

		Transform& GetTransform() { return transform; }//Dont need not private anymore

		virtual void OnCollision(Actor* other) = 0;

		float GetRadius();
		float GetRadiusT();

		void AddComponent(std::unique_ptr<Component> component);

		template<typename T>
		T* GetComponent();

		template<typename T>
		std::vector<T*> GetComponents();

	protected:
		std::vector<std::unique_ptr<Component>> components;
		res_t<Texture> texture;
		std::shared_ptr<class Model> model;
		
	};

	template<typename T>
	inline T* Actor::GetComponent()
	{
		for (const auto& component : components) {
			auto castedComponent = dynamic_cast<T*>(component.get());
			if (castedComponent) {return castedComponent;}
		}
		return nullptr;
	}


	template<typename T>
	inline std::vector<T*> Actor::GetComponents()
	{
		std::vector<T*> results;
		for (const auto& component : components) {
			auto castedComponent = dynamic_cast<T*>(component.get());
				if (castedComponent) { 
					results.push_back(castedComponent);
				}
		}
		return results;
	}

}