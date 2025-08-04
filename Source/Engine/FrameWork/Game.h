#pragma once
#include <memory>
#include "Renderer/Renderer.h"

namespace viper {
	class Game {
	public:
		Game() = default;

		virtual bool Initialize() = 0;
		virtual void Update(float dt) = 0;
		virtual void Draw(class Renderer& renderer) = 0;
		virtual void Shutdown() = 0;

		void AddPoints(int points) {score += points;}
		int GetPoints() const { return score; }

		void SetLives(int lives) { this->lives = lives; }
		int GetLives() const { return lives; }

	protected:
		int score{ 0 };
		int lives{ 0 };

		std::unique_ptr<class Scene> scene;
	};
}