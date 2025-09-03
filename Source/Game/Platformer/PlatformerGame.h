#pragma once

#include "Framework/Game.h"
#include "Renderer/Font.h"
#include "Renderer/Text.h"

class PlatformerGame : public viper::Game, public viper::IObserver {
public:
	enum class GameState {
		Initialize,
		Title,
		StartGame,
		StartLevel,
		Game,
		PlayerDead,
		GameOver
	};

public:
	PlatformerGame() = default;

	bool Initialize() override;

	void Update(float dt) override;

	void Draw(class viper::Renderer& renderer) override;

	void OnPlayerDeath();

	void OnNotify(const viper::Event& event) override;

	void Shutdown() override;

private:
	void SpawnEnemy();

	void SpawnPlayer();

	void SpawnRing();

private:
	GameState gameState = GameState::Initialize;
	float enemySpawnTimer{ 0 };
	float stateTimer{ 0 };

	std::unique_ptr<viper::Text> titleText;
	std::unique_ptr<viper::Text> scoreText;
	std::unique_ptr<viper::Text> livesText;
};