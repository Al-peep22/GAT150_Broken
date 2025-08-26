#include "FrameWork/Component.h"
#include "FrameWork/Actor.h"
#include "Physics/Collidable.h"

class Rocket : public viper::Component, public viper::ICollidable {
public:
	float speed = 200;

	Rocket() = default;
	/*Rocket(const viper::Transform& transform, std::shared_ptr<viper::Mesh> Mesh) :
		Actor{ transform, Mesh } {
	}
	Rocket(const viper::Transform& transform, viper::res_t<viper::Texture> texture) :
		Actor{ transform, texture } {
	}

	Rocket(const viper::Transform& transform) :
		Actor{ transform } {
	}*/
	CLASS_PROTOTYPE(Rocket);

	void Update(float dt) override;

	void OnCollision(class viper::Actor* other) override;

	void Read(const viper::json::value_t& value) override;
};