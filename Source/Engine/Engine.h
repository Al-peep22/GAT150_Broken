#pragma once
#include "Core/Time.h"
#include <memory>
#include "Renderer/Renderer.h"

namespace viper {
	class Renderer;
	class AudioSystem;
	class InputSystem;
	class ParticleSystem;

	class Engine {
	public:
		Engine() = default;

		bool Initialize();
		void Shutdown();

		void Update();
		void Draw();

		Renderer& GetRenderer() { return *this->renderer; }
		AudioSystem& GetAudio() { return *this->audio; }
		InputSystem& GetInput() { return *this->input; }
		ParticleSystem& GetParticleSystem() { return *this->particleSystem; }

		Time& GetTime() { return time; }

		int width = 1280;
		int height = 1024;

	private:
		Time time;
		std::unique_ptr<Renderer> renderer;
		std::unique_ptr<AudioSystem> audio;
		std::unique_ptr<InputSystem> input;
		std::unique_ptr<ParticleSystem> particleSystem;
	};

	Engine& GetEngine();
	inline Renderer& GetRenderer() { return GetEngine().GetRenderer(); }
}