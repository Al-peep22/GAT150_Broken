//#include "../GameCPH.h"
#include "Enemy.h"
#include "Engine.h"
#include "./FrameWork/Scene.h"
#include "Player.h"
#include "FrameWork/Game.h"
#include "Rocket.h"
#include "GameData.h"
#include <Math/Vector3.h>
#include <Math/Vector2.h>
#include "Renderer/Mesh.h"
#include "Renderer/ParticleSystem.h"
#include "Core/Random.h"
#include <Components/SpriteRenderer.h>
#include <Components/RigidBody.h>
#include <Components/CircleCollider2D.h>
#include "Core/Factory.h"
#include "FrameWork/Actor.h"

FACTORY_REGISTER(Enemy);

//using namespace viper;
void Enemy::Update(float dt)
{
	bool playerSeen = false;

	//// FOLLOW PLAYER
	//Actor* player = owner->scene->GetActorByName<Actor>("player");
	//if (player) {
	//	viper::vec2 owner->direction{ 0, 0 };
	//	owner->direction = owner->player->transform.position - owner->transform.position;

	//	owner->direction = owner->direction.Normalized();
	//	viper::vec2 forward = viper::vec2{ 1,0 }.Rotate(viper::math::degToRad(owner->transform.rotation));

	//	float angle = viper::math::radToDeg(viper::vec2::AngleBetween(forward, direction));
	//	playerSeen = angle <= 30;

	//	
	//	if (playerSeen) {
	//		float angle = viper::vec2::SignedAngleBetween(direction, forward);
	//		angle = viper::math::sign(angle);
	//		owner->transform.rotation += viper::math::radToDeg(angle * 5 * owner->dt); // Adjust rotation to face the player
	//	}

	//	
	//}

	// ROTATION
	viper::vec2 force = viper::vec2{ 1, 0 }.Rotate(viper::math::degToRad(owner->transform.rotation)) * speed;
	//velocity += force * dt;
	//GetComponent<viper::RigidBody>()->velocity += force * dt;
	
	auto rb = owner->GetComponent<viper::RigidBody>();
	if (rb) {
		rb->velocity += force * dt;
	}

	// WRAP POSITION
	owner->transform.position.x = viper::math::wrap(owner->transform.position.x, 0.0f, (float)viper::GetEngine().GetRenderer().GetWidth());
	owner->transform.position.y = viper::math::wrap(owner->transform.position.y, 0.0f, (float)viper::GetEngine().GetRenderer().GetHeight());

	// ENEMY ROCKETS
	fireTimer -= dt;
	if (fireTimer <= 0 && playerSeen) {
		fireTimer = fireTime;

		//std::shared_ptr<viper::Mesh> rocket_Mesh = std::make_shared<viper::Mesh>(GameData::rocket_points, viper::vec3{ 1, 0, 0 });
		//viper::Transform transform{ owner->transform.position,owner->transform.rotation , 2.0f };
		////auto rocket = std::make_unique<Rocket>(transform, rocket_Mesh);
		//auto rocket = std::make_unique<Actor>(transform);//, viper::Resources().Get<viper::Texture>("red_rocket.png", viper::GetEngine().GetRenderer()));

		///*rocket->speed = 500.0f;
		//rocket->lifespan = 1.5f;
		//rocket->name = "rocket";
		//rocket->tag = "enemy";*/

		//auto spriteRenderer = std::make_unique<viper::SpriteRenderer>();
		//spriteRenderer->textureName = "red_rocket.png";

		//owner->rocket->AddComponent(std::move(spriteRenderer));

		//auto rb = std::make_unique<viper::RigidBody>();
		////rb->damping = 0.5f;
		//owner->rocket->AddComponent(std::move(rb));

		//auto collider = std::make_unique<viper::CircleCollider2D>();
		//collider->radius = 10;
		//owner->rocket->AddComponent(std::move(collider));

		//owner->scene->AddActor(std::move(rocket));
	}
	
	//// UPDATE PARENT
	//viper::Actor::Update(dt);
}

void Enemy::OnCollision(viper::Actor* other)
{
	if (owner->tag != other->tag) {
		owner->destroyed = true;
		owner->scene->GetGame()->AddPoints(100);
		for (int i = 0; i < 100; i++) {

			// CREATE PARTICAL EXPLOSION
			viper::Particle particle;
			particle.position = owner->transform.position;
			particle.velocity = viper::random::onUnitCircle() * viper::random::getReal(10.0f,200.0f);
			particle.color = viper::vec3{ 1,1,1 };
			particle.lifespan = 2;

			viper::GetEngine().GetParticleSystem().AddParticle(particle);
		}
	}
}
