#include "Physics.h"

namespace viper {
	bool Physics::Initialize() {
		b2WorldDef worldDef = b2DefaultWorldDef();
		worldDef.gravity = b2Vec2{ 0.0f, -10.0f };
		worldId = b2CreateWorld(&worldDef);

		return true;
	}

	void Physics::Shutdown() {
		b2DestroyWorld(worldId);
	}

	void Physics::Update(float dt) {
		b2World_Step(worldId, 1.0f / 60.0f, 4);
	}
}