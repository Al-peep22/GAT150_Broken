#include "RigidBody.h"

namespace viper {
	void RigidBody::Update(float dt)
	{
		owner->transform.position += velocity * dt;
		velocity *= (1.0f / (1.0f + damping * dt)); // (< 1) = slow down
	}
	void RigidBody::Draw(Renderer& renderer)
	{
	}
}
