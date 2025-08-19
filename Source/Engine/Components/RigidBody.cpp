#include "RigidBody.h"

namespace viper {

	FACTORY_REGISTER(RigidBody)

	void RigidBody::Update(float dt)
	{
		owner->transform.position += velocity * dt;
		velocity *= (1.0f / (1.0f + damping * dt)); // (< 1) = slow down
	}
	void RigidBody::Draw(Renderer& renderer)
	{
	}
}
