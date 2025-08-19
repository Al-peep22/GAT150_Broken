#include "Player.h"
#include "Engine.h"
#include "Input/InputSystem.h"
#include <SDL3/SDL_scancode.h>
#include "Math/Math.h"
#include "GameData.h"
#include <Math/Vector3.h>
#include "Rocket.h"
#include "Renderer/Mesh.h"
#include "FrameWork/Scene.h"
#include "SpaceGame.h"
#include "Audio/AudioSystem.h"
#include "Renderer/ParticleSystem.h"
#include "Core/Random.h"
#include <Components/SpriteRenderer.h>
#include <Components/RigidBody.h>
#include <Components/CircleCollider2D.h>
#include "Audio/AudioClip.h"
#include "Core/Factory.h"

FACTORY_REGISTER(Player)


void Player::Update(float dt)
{
	//// CREATE PARTICAL EXPLOSION
	//viper::Particle particle;
	//particle.position = owner->transform.position;
	//particle.velocity = viper::vec2{viper::random::getReal(-200.0f,200.0f),viper::random::getReal(-200.0f,200.0f) };
	//particle.color = viper::vec3{1,1,1};
	//particle.lifespan = 0.5f;
	

	// ROTATION
	float rotate = 0;
	if (viper::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_A)) rotate = -1;
	if (viper::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_D)) rotate = +1;

	//owner->transform.rotation += (rotate * owner->rotationRate) * owner->dt;

	//// THRUST
	//float thrust = 0;
	//if (viper::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_S)) { thrust = -1; }
	//if (viper::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_W)) { thrust = +1; viper::GetEngine().GetParticleSystem().AddParticle(particle);	}

	//// DIRECTION AND VELOCITY
	//viper::vec2 direction{1,0};
	//viper::vec2 force = direction.Rotate(viper::math::degToRad(owner->transform.rotation))*thrust*speed;
	////velocity += force * dt;

	//auto rb = owner->GetComponent<viper::RigidBody>();
	//if (rb) {
	//	rb->velocity += force * dt;
	//}
	

	// WRAP POSITION
	owner->transform.position.x = viper::math::wrap(owner->transform.position.x, 0.0f, (float)viper::GetEngine().GetRenderer().GetWidth());
	owner->transform.position.y = viper::math::wrap(owner->transform.position.y, 0.0f, (float)viper::GetEngine().GetRenderer().GetHeight());

	// PLAYER ROCKETS
	fireTimer -= dt;
	if (viper::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_F) && fireTimer <= 0) {
		fireTimer = fireTime;
		
		//// PLAY ROCKET SHOOT SOUND
		////viper::GetEngine().GetAudio().PlaySound("clap");
		//auto sound = viper::Resources().Get<viper::AudioClip>("clap.wav", viper::GetEngine().GetAudio()).get();
		//if (sound) {
		//	viper::GetEngine().GetAudio().PlaySound(*sound);
		//}

		//std::shared_ptr<viper::Mesh> rocket_Mesh = std::make_shared<viper::Mesh>(GameData::rocket_points, viper::vec3{ 1, 1, 1 });
		//viper::Transform transform{ owner->transform.position,owner->transform.rotation , 2 };
		////auto rocket = std::make_unique<Rocket>(transform, rocket_Mesh);
		//auto rocket = std::make_unique<viper::Actor>(transform);//, viper::Resources().Get<viper::Texture>("blue_rocket.png", viper::GetEngine().GetRenderer()));

		//rocket->speed = 1500.0f;
		//rocket->owner->lifespan = 1.5f;
		//rocket->name = "rocket";
		//rocket->owner->tag = "player";

		//auto spriteRenderer = std::make_unique<viper::SpriteRenderer>();
		//spriteRenderer->textureName = "blue_rocket.png";

		//rocket->owner->AddComponent(std::move(spriteRenderer));

		//auto rb = std::make_unique<viper::RigidBody>();
		////rb->damping = 0.5f;
		//rocket->owner->AddComponent(std::move(rb));

		//auto collider = std::make_unique<viper::CircleCollider2D>();
		//collider->radius = 10;
		//rocket->owner->AddComponent(std::move(collider));

		//owner->scene->AddActor(std::move(rocket));
	}
	//spawn rocket at player position and rotation

	// UPDATE PARENT
	//viper::Actor::Update(owner->dt);
}

void Player::OnCollision(viper::Actor* other)
{
	// COLLISON
	if (owner->tag != other->tag) {
		owner->destroyed = true;
		dynamic_cast<SpaceGame*>(owner->scene->GetGame())->OnPlayerDead();
	}
}
