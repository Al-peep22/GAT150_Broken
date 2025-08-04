#pragma once
#include "Framework/Game.h"
#include <Renderer/Font.h>
#include "Renderer/Text.h"
#include "Renderer/Renderer.h"

class SpaceGame : public viper::Game {
public:
	enum class GameState {
		Initialize,
		Title,
		StartGame,
		StartRound,
		Game,
		PlayerDead,
		GameOver,
	}; 
	SpaceGame() = default;

	bool Initialize() override;
	void Update(float dt) override;
	void Shutdown() override;

	void Draw(class viper::Renderer& renderer) override;

	void OnPlayerDead();

private:
	void SpawnEnemy();

private:
	GameState gameState = GameState::Initialize;
	float enemySpawnTimer = { 0 };
	float stateTimer = {0};
	bool playedDeathSound = false;

	std::shared_ptr<viper::Font> titleFont;
	std::shared_ptr<viper::Font> uiFont;

	std::unique_ptr<viper::Text> titleText;
	std::unique_ptr<viper::Text> scoreText;
	std::unique_ptr<viper::Text> livesText;
};