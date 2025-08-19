#pragma once
#include "FrameWork/Component.h"
#include "FrameWork/Actor.h"

class Player : public viper::Component {
public:
	float speed = 200;
	float rotationRate = 180.0f;
	float fireTime = 0.2f;
	float fireTimer = 0.0f;

	Player() = default;
	/*Player(const viper::Transform& transform, std::shared_ptr<viper::Mesh> Mesh) :
		Actor{ transform, Mesh } {
	}

	Player(const viper::Transform& transform, viper::res_t<viper::Texture> texture) :
		Actor{ transform, texture } {
	}

	Player(const viper::Transform& transform) :
		Actor{ transform} {*/

	void Update(float dt) override;

	void OnCollision(viper::Actor* other);
};