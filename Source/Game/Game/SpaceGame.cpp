#include "SpaceGame.h"

#include "Core/Random.h"
#include "Framework/Scene.h"
#include "Math/Vector2.h"
#include "Player.h"
//#include "Renderer/Font.h"
#include "Renderer/Mesh.h"
#include "Renderer/Renderer.h"
//#include "Renderer/Text.h"
#include "Engine.h"
#include "Input/InputSystem.h"
#include "../GameCPH.h"
#include "Audio/AudioSystem.h"

#include <vector>
#include "Enemy.h"
#include "GameData.h"
#include "Renderer/ParticleSystem.h"

#include "Resources/ResourceManager.h"
#include <Components/SpriteRenderer.h>
#include "Components/RigidBody.h"
#include "Components/CircleCollider2D.h"

using namespace viper;

bool SpaceGame::Initialize() {
    scene = std::make_unique<viper::Scene>(this);

	titleText = std::make_unique<Text>(Resources().GetWithID<Font>("title_font",GameData::gameFont, 128.0f));
    scoreText = std::make_unique<viper::Text>(viper::Resources().GetWithID<viper::Font>("ui_font",GameData::gameFont, 48.0f));
    livesText = std::make_unique<Text>(Resources().Get<Font>(GameData::gameFont2, 48.0f));

    return true;
}

void SpaceGame::Update(float dt) {


    switch (gameState) {
    case SpaceGame::GameState::Initialize:
        gameState = GameState::Title;
		break;
	case SpaceGame::GameState::Title:
		if (viper::GetEngine().GetInput().GetKeyPressed(SDL_SCANCODE_SPACE)) {
		    gameState = GameState::StartGame;
		}        
		break;
	case SpaceGame::GameState::StartGame:
        score = 0;
        lives = 3;
		gameState = GameState::StartRound;
        break;
    case SpaceGame::GameState::StartRound:
    {

        viper::GetEngine().GetAudio().PlaySound("music");

        scene->RemoveAllActors();
        // CREATE PLAYER
        std::shared_ptr<viper::Mesh> ship_Mesh = std::make_shared<viper::Mesh>(GameData::ship_points, viper::vec3{ 0.37f, 1, 0.16f });
        viper::Transform transform{ viper::vec2{ viper::GetEngine().GetRenderer().GetWidth() * 0.5f , viper::GetEngine().GetRenderer().GetHeight() * 0.5f}, 0, 2 };
        //std::unique_ptr<Player> player = std::make_unique<Player>(transform, ship_Mesh);
        std::unique_ptr<Player> player = std::make_unique<Player>(transform);//, viper::Resources().Get<viper::Texture>("blue_01.png", viper::GetEngine().GetRenderer()));

        player->speed = 500.0f;
        player->rotationRate = 180.0f;
        //player->damping = 0.5f;
        player->name = "player";
        player->tag = "player"; 

        auto spriteRenderer = std::make_unique<viper::SpriteRenderer>();
        spriteRenderer->textureName = "blue_01.png";

        player->AddComponent(std::move(spriteRenderer));

        auto rb = std::make_unique<viper::RigidBody>();
        rb->damping = 1.5f;
        player->AddComponent(std::move(rb));

		auto collider = std::make_unique<viper::CircleCollider2D>();
		collider->radius = 60.0f;
        player->AddComponent(std::move(collider));

        scene->AddActor(std::move(player));

        gameState = GameState::Game;
        break;
    }
	case SpaceGame::GameState::Game:
        enemySpawnTimer -= dt;
        if (enemySpawnTimer <= 0) {
            enemySpawnTimer = 4;

            // CREATE ENEMY
			SpawnEnemy();
        }
        break;
	case SpaceGame::GameState::PlayerDead:
        stateTimer -= dt;
        if (stateTimer <= 0) {
            lives--;
            if (lives == 0) { gameState = GameState::GameOver; stateTimer = 3; playedDeathSound = false; }
            else { gameState = GameState::StartRound; }
        }
		break;
	case SpaceGame::GameState::GameOver:
		// PLAY GAME OVER SOUND
		if (!playedDeathSound) {
			viper::GetEngine().GetAudio().PlaySound("death");
			playedDeathSound = true;
		}
        stateTimer -= dt;
        if (stateTimer <= 0) {
            gameState = GameState::Title;
        }
        break;
    }
    scene->Update(viper::GetEngine().GetTime().GetDeltaTime());
}

void SpaceGame::Draw(viper::Renderer& renderer) {

    // CREATE TITLE TEXT
    if (gameState == GameState::Title) {
        titleText->Create(renderer, "ALIEN MOB", viper::vec3{ 1,0,0 });
        titleText->Draw(renderer, 200, 400);
    }

	// CREATE GAME OVER TEXT
    if (gameState == GameState::GameOver) {
        titleText->Create(renderer, "GAME OVER", viper::vec3{ 1,0,0 });
        titleText->Draw(renderer, 200, 400);
    }

	// CREATE SCORE/LIVES TEXT
    if (gameState != GameState::GameOver && gameState != GameState::Title) {
        scoreText->Create(renderer, "SCORE  "+std::to_string(score), {1,1,1});
	    scoreText->Draw(renderer, 20.0f, 20.0f);

        livesText->Create(renderer, "LIVES  " + std::to_string(lives), { 1,1,1 });
        livesText->Draw(renderer, (float)renderer.GetWidth() - 300, 20.0f);
    }

    scene->Draw(renderer);

	viper::GetEngine().GetParticleSystem().Draw(renderer);

    // DRAW TEXT
    //_text->Draw(viper::GetEngine().GetRenderer(), 40.0f, 40.0f);
	//viper::GetEngine()GetParticalSystem().Draw(renderer);
}

void SpaceGame::OnPlayerDead()
{
	gameState = GameState::PlayerDead;
    stateTimer = 2;
}

void SpaceGame::SpawnEnemy()
{
	Player* player = scene->GetActorByName<Player>("player");
    if (player) {

        std::shared_ptr<viper::Mesh> enemy_Mesh = std::make_shared<viper::Mesh>(GameData::enemy_points, viper::vec3{ 1, 0.18f, 0.18f });

        // spawn at random position (not on player)
		viper::vec2 position = player->transform.position + viper::random::onUnitCircle() * viper::random::getReal(200.0f,500.0f);
        viper::Transform enemy_transform{ position, viper::random::getReal(0.0f,360.0f), 2};
        //std::unique_ptr<Enemy> enemy = std::make_unique<Enemy>(enemy_transform, enemy_Mesh);
        std::unique_ptr<Enemy> enemy = std::make_unique<Enemy>(enemy_transform);//, viper::Resources().Get<viper::Texture>("large_red_01.png", viper::GetEngine().GetRenderer()));

        enemy->speed = (viper::random::getReal() * 100) + 100;
        //enemy->damping = 0.5f;
        enemy->fireTime = 1;
        enemy->fireTimer = 1;
        enemy->name = "enemy";
        enemy->tag = "enemy";

        /*auto spriteRenderer = std::make_unique<viper::SpriteRenderer>();
        spriteRenderer->textureName = "large_red_01.png";

        enemy->AddComponent(std::move(spriteRenderer));*/
		auto meshRenderer = std::make_unique<viper::MeshRenderer>();
		meshRenderer->meshName = "Meshes/enemy.txt";
		enemy->AddComponent(std::move(meshRenderer));

        auto rb = std::make_unique<viper::RigidBody>();
        rb->damping = 0.5f;
        enemy->AddComponent(std::move(rb));

        auto collider = std::make_unique<viper::CircleCollider2D>();
        collider->radius = 60.0f;
        enemy->AddComponent(std::move(collider));

        scene->AddActor(std::move(enemy));

    }
}

void SpaceGame::Shutdown() {

}