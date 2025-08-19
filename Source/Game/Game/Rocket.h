#include "FrameWork/Component.h"
#include "FrameWork/Actor.h"

class Rocket : public viper::Component {
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

	void Update(float dt) override;

	void OnCollision(class viper::Actor* other);
};