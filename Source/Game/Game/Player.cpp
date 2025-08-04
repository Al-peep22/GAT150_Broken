#include "Player.h"
#include "Engine.h"
#include "Input/InputSystem.h"
#include <SDL3/SDL_scancode.h>
#include "Math/Math.h"
#include "GameData.h"
#include <Math/Vector3.h>
#include "Rocket.h"
#include "Renderer/Model.h"
#include "FrameWork/Scene.h"
#include "SpaceGame.h"
#include "Audio/AudioSystem.h"
#include "Renderer/ParticleSystem.h"
#include "Core/Random.h"

using namespace viper;

void Player::Update(float dt)
{
	// CREATE PARTICAL EXPLOSION
	viper::Particle particle;
	particle.position = transform.position;
	particle.velocity = viper::vec2{viper::random::getReal(-200.0f,200.0f),random::getReal(-200.0f,200.0f) };
	particle.color = vec3{1,1,1};
	particle.lifespan = 0.5f;
	

	// ROTATION
	float rotate = 0;
	if (viper::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_A)) rotate = -1;
	if (viper::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_D)) rotate = +1;

	transform.rotation += (rotate * rotationRate) * dt;

	// THRUST
	float thrust = 0;
	if (viper::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_S)) { thrust = -1; }
	if (viper::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_W)) { thrust = +1; GetEngine().GetParticleSystem().AddParticle(particle);	}

	// DIRECTION AND VELOCITY
	viper::vec2 direction{1,0};
	viper::vec2 force = direction.Rotate(viper::math::degToRad(transform.rotation))*thrust*speed;
	velocity += force * dt;

	// WRAP POSITION
	transform.position.x = math::wrap(transform.position.x, 0.0f, (float)GetEngine().GetRenderer().GetWidth());
	transform.position.y = math::wrap(transform.position.y, 0.0f, (float)GetEngine().GetRenderer().GetHeight());

	// PLAYER ROCKETS
	fireTimer -= dt;
	if (viper::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_F) && fireTimer <= 0) {
		fireTimer = fireTime;
		
		// PLAY ROCKET SHOOT SOUND
		viper::GetEngine().GetAudio().PlaySound("clap");

		std::shared_ptr<viper::Model> rocket_model = std::make_shared<viper::Model>(GameData::rocket_points, viper::vec3{ 1, 1, 1 });
		viper::Transform transform{ this->transform.position,this->transform.rotation , 2 };
		auto rocket = std::make_unique<Rocket>(transform, rocket_model);

		rocket->speed = 1500.0f;
		rocket->lifespan = 1.5f;
		rocket->name = "rocket";
		rocket->tag = "player";


		scene->AddActor(std::move(rocket));
	}
	//spawn rocket at player position and rotation

	// UPDATE PARENT
	Actor::Update(dt);
}

void Player::OnCollision(Actor* other)
{
	// COLLISON
	if (other->tag != tag) {
		destroyed = true;
		dynamic_cast<SpaceGame*>(scene->GetGame())->OnPlayerDead();
	}
}
