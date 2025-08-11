#pragma once
#include "Math/Transform.h"
#include <string>
#include <memory>
#include <Renderer/Texture.h>
#include "FrameWork/Object.h"
//#include "../Renderer/Model.h"

namespace viper {
	class Actor : public Object{
	public:
		std::string name;
		std::string tag;

		vec2 velocity{0,0};
		float damping{ 0.0f };

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

		void AddComponent(std::unique_ptr<class Component> component);

	protected:
		std::vector<std::unique_ptr<class Component>> components;
		res_t<Texture> texture;
		std::shared_ptr<Model> model;
		
	};
}