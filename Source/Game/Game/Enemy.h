#include "FrameWork/Actor.h"

class Enemy : public viper::Actor {
public:
	float speed = 200;
	float fireTimer = 0;
	float fireTime = 0;

	Enemy() = default;
	Enemy(const viper::Transform& transform, std::shared_ptr<viper::Model> model) :
		Actor{ transform, model } {
	}
	
	Enemy(const viper::Transform& transform, viper::res_t<viper::Texture> texture) :
		Actor{ transform, texture } {
	}

	Enemy(const viper::Transform& transform) :
		Actor{ transform} {
	}

	void Update(float dt) override;

	void OnCollision(Actor* other) override;
};