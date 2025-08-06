#include "FrameWork/Actor.h"

class Rocket : public viper::Actor {
public:
	float speed = 200;

	Rocket() = default;
	Rocket(const viper::Transform& transform, std::shared_ptr<viper::Model> model) :
		Actor{ transform, model } {
	}
	Rocket(const viper::Transform& transform, viper::res_t<viper::Texture> texture) :
		Actor{ transform, texture } {
	}

	void Update(float dt) override;

	void OnCollision(Actor* other) override;
};