#pragma once
#include "Framework/Game.h"
#include <Renderer/Font.h>
#include "Renderer/Text.h"
#include "Renderer/Renderer.h"
#include "Event/Observer.h"

class SpaceGame : public viper::Game, public viper::IObserver {
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
	void Shutdown() override;

	void Update(float dt) override;
	void Draw(class viper::Renderer& renderer) override;

	void OnPlayerDead();
	void OnNotify(const Event& event) override;

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