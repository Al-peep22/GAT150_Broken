#pragma once
#include "Components/ColliderComponent.h"

namespace viper {
	class CircleCollider2D : public ColliderComponent {
	public:
		float radius{0};
	public:
		CircleCollider2D() = default;

	private:

		// Inherited via ColliderComponent
		void Update(float dt) override;
		bool CheckCollision(ColliderComponent& other) override;
	};
}