#include "Rocket.h"
#include "Engine.h"
#include "./FrameWork/Scene.h"
#include "Player.h"
#include "Core/Random.h"
#include "Input/InputSystem.h"
#include "Renderer/ParticleSystem.h"

FACTORY_REGISTER(Rocket)

using namespace viper;
void Rocket::Update(float dt)
{

	vec2 force = vec2{ 1,0 }.Rotate(math::degToRad(transform.rotation)) * speed;
	//velocity = force;
	auto* rb = GetComponent<viper::RigidBody>();
	if (rb) {
		rb->velocity = force;
	}

	// WRAP POSITION
	transform.position.x = math::wrap(transform.position.x, 0.0f, (float)GetEngine().GetRenderer().GetWidth());
	transform.position.y = math::wrap(transform.position.y, 0.0f, (float)GetEngine().GetRenderer().GetHeight());
	
	// PARTICLE EXPLOSION
	float angle = transform.rotation + viper::random::getReal(-60.0f, 60.0f);
	viper::vec2 velocity = viper::vec2{ 1, 0 }.Rotate(viper::math::degToRad(angle));
	velocity *= viper::random::getReal(80.0f, 150.0f);


	viper::Particle particle;
	particle.position = transform.position;
	particle.velocity = velocity;
	particle.color = (tag == "enemy") ? viper::vec3{ 0, 1, 1 } : viper::vec3{ 1, 1, 0 };
	particle.lifespan = viper::random::getReal(0.15f, 0.3f);

	viper::GetEngine().GetParticleSystem().AddParticle(particle);

	Actor::Update(dt);
}

void Rocket::OnCollision(Actor* other)
{
	if (other->tag != tag) {
		destroyed = true;
	}
	//std::cout << other->tag << std::endl;
}
