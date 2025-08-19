#include "FrameWork/Component.h"

class Enemy : public viper::Component {
public:
	float speed = 200;
	float fireTimer = 0;
	float fireTime = 0;

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

	void Update(float dt) override;

	void OnCollision(class Actor* other);
};