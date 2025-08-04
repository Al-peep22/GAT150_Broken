#include "Rocket.h"
#include "Engine.h"
#include "./FrameWork/Scene.h"
#include "Player.h"
#include "Core/Random.h"
#include "Input/InputSystem.h"
#include "Renderer/ParticleSystem.h"
using namespace viper;
void Rocket::Update(float dt)
{
	vec2 direction{ 1, 0 };
	vec2 force = vec2{ 1,0 }.Rotate(math::degToRad(transform.rotation)) * speed;
	velocity = force;

	transform.position.x = math::wrap(transform.position.x, 0.0f, (float)GetEngine().GetRenderer().GetWidth());
	transform.position.y = math::wrap(transform.position.y, 0.0f, (float)GetEngine().GetRenderer().GetHeight());
	
	/*viper::ParticleSystem particle;
	particle.position = transform.position;
	particle.velocity = viper::random::onUnitCircle() * viper::random::getReal(10.0f, 200.0f);
	particle.color = viper::vec3{ 1,1,1 };
	particle.lifespan = 2;*/

	Actor::Update(dt);
}

void Rocket::OnCollision(Actor* other)
{
	if (other->tag != tag) {
		destroyed = true;
	}
	//std::cout << other->tag << std::endl;
}
