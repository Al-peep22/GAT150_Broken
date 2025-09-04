#include "FrameWork/Component.h"
#include "Physics/Collidable.h"
#include "Event/Observer.h"
#include "Event/Event.h"

class Enemy : public viper::Component, public viper::ICollidable, public viper::IObserver {
public:
	float speed = 200;
	float fireTimer = 0;
	float fireTime = 0;

	viper::RigidBody* rigidBody{ nullptr };

	Enemy() = default;
	/*Enemy(const viper::Transform& transform, std::shared_ptr<viper::Mesh> Mesh) :
		Actor{ transform, Mesh } {
	}
	
	Enemy(const viper::Transform& transform, viper::res_t<viper::Texture> texture) :
		Actor{ transform, texture } {
	}

	Enemy(const viper::Transform& transform) :
		Actor{ transform} {
	}*/

	CLASS_PROTOTYPE(Enemy);

	void Start() override;

	void Update(float dt) override;

	void OnCollision(viper::Actor* other) override;

	void OnNotify(const Event& event) override;
};