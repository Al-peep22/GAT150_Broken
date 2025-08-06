#pragma once
#include "Core/Time.h"
#include "Core/Singleton.h"
#include "Renderer/Renderer.h"
#include "Renderer/ParticleSystem.h"
#include "Audio/AudioSystem.h"
#include "Input/InputSystem.h"
#include "Resources/ResourceManager.h"
#include <memory>

namespace viper {
	class Renderer;
	class AudioSystem;
	class InputSystem;
	class ParticleSystem;

	class Engine : public Singleton <Engine> {
	public:

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
		friend class Singleton<Engine>;
		Engine() = default;

	private:
		Time time;
		std::unique_ptr<Renderer> renderer;
		std::unique_ptr<AudioSystem> audio;
		std::unique_ptr<InputSystem> input;
		std::unique_ptr<ParticleSystem> particleSystem;
	};

	inline Engine& GetEngine() { return Engine::Instance(); }
	inline Renderer& GetRenderer() { return GetEngine().GetRenderer(); }
}