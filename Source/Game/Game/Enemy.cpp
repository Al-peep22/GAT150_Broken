#include "Enemy.h"
#include "Engine.h"
#include "./FrameWork/Scene.h"
#include "Player.h"
#include "FrameWork/Game.h"
#include "Rocket.h"
#include "GameData.h"
#include <Math/Vector3.h>
#include <Math/Vector2.h>
#include "Renderer/Model.h"
#include "Renderer/ParticleSystem.h"
#include "Core/Random.h"
using namespace viper;
void Enemy::Update(float dt)
{
	bool playerSeen = false;

	// FOLLOW PLAYER
	Player* player = scene->GetActorByName<Player>("player");
	if (player) {
		vec2 direction{ 0, 0 };
		direction = player->transform.position - transform.position;

		direction = direction.Normalized();
		viper::vec2 forward = viper::vec2{ 1,0 }.Rotate(viper::math::degToRad(transform.rotation));

		float angle = viper::math::radToDeg(vec2::AngleBetween(forward, direction));
		playerSeen = angle <= 30;

		
		if (playerSeen) {
			float angle = vec2::SignedAngleBetween(direction, forward);
			angle = viper::math::sign(angle);
			transform.rotation += math::radToDeg(angle * 5 * dt); // Adjust rotation to face the player
		}

		
	}

	// ROTATION
	viper::vec2 force = viper::vec2{ 1, 0 }.Rotate(viper::math::degToRad(transform.rotation)) * speed;
	velocity += force * dt;

	// WRAP POSITION
	transform.position.x = math::wrap(transform.position.x, 0.0f, (float)GetEngine().GetRenderer().GetWidth());
	transform.position.y = math::wrap(transform.position.y, 0.0f, (float)GetEngine().GetRenderer().GetHeight());

	// ENEMY ROCKETS
	fireTimer -= dt;
	if (fireTimer <= 0 && playerSeen) {
		fireTimer = fireTime;

		std::shared_ptr<viper::Model> rocket_model = std::make_shared<viper::Model>(GameData::rocket_points, viper::vec3{ 1, 0, 0 });
		viper::Transform transform{ this->transform.position,this->transform.rotation , 2.0f };
		auto rocket = std::make_unique<Rocket>(transform, rocket_model);

		rocket->speed = 500.0f;
		rocket->lifespan = 1.5f;
		rocket->name = "rocket";
		rocket->tag = "enemy";

		scene->AddActor(std::move(rocket));
	}
	
	// UPDATE PARENT
	Actor::Update(dt);
}

void Enemy::OnCollision(Actor* other)
{
	if (other->tag != tag) {
		destroyed = true;
		scene->GetGame()->AddPoints(100);
		for (int i = 0; i < 100; i++) {

			// CREATE PARTICAL EXPLOSION
			viper::Particle particle;
			particle.position = transform.position;
			particle.velocity = viper::random::onUnitCircle() * random::getReal(10.0f,200.0f);
			particle.color = vec3{ 1,1,1 };
			particle.lifespan = 2;

			viper::GetEngine().GetParticleSystem().AddParticle(particle);
		}
	}
}
