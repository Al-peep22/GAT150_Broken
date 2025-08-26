#pragma once

#include "Framework/Component.h"

class ringBlast : public viper::Component {
	class ringBlast : public viper::Component, public viper::ICollidable {
	public:
		float speed = 200;
		float fireTimer = 0;

			void Update(float dt) override;

			void OnCollision(class viper::Actor* other);
			void OnCollision(class viper::Actor* other) override;

			void Read(const viper::json::value_t& value) override;
};