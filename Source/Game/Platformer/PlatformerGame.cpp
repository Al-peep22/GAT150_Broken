//#include "../GamePCH.h"
#include "PlatformerGame.h"
#include <Event/EventManager.h>
#include <Core/Factory.h>

bool PlatformerGame::Initialize() {
    OBSERVER_ADD(player_dead);
    OBSERVER_ADD(add_points);

    scene = std::make_unique<viper::Scene>(this);
    scene->Load("scenes/prototypes.json");
    scene->Load("scenes/level.json");
    return false;
}

void PlatformerGame::Update(float dt) {
    switch (gameState) {

    case GameState::Initialize:
        gameState = GameState::StartLevel;
        break;

    case GameState::Title:
        break;

    case GameState::StartGame:
        break;

    case GameState::StartLevel:
        SpawnPlayer();
        SpawnEnemy();
        gameState = GameState::Game;
        break;

    case GameState::Game:
        break;

    case GameState::PlayerDead:
        break;

    case GameState::GameOver:
        break;

    default:
        break;
    }

    scene->Update(viper::GetEngine().GetTime().GetDeltaTime());
}

void PlatformerGame::Draw(class viper::Renderer& renderer) {
    scene->Draw(renderer);

    viper::GetEngine().GetParticleSystem().Draw(renderer);
}

void PlatformerGame::OnPlayerDeath() {

}

void PlatformerGame::OnNotify(const viper::Event& event) {

}

void PlatformerGame::Shutdown() {

}

void PlatformerGame::SpawnEnemy() {
    auto enemy = viper::Instantiate("enemy");
    scene->AddActor(std::move(enemy));

    auto bat = viper::Instantiate("bat");
    scene->AddActor(std::move(bat));
}

void PlatformerGame::SpawnPlayer() {
    auto player = viper::Instantiate("player");
    //player->transform.position = viper::vec2{ viper::random::getReal(0.0f, 1080.0f), viper::random::getReal(0.0f, 100.0f) };
    scene->AddActor(std::move(player));
}