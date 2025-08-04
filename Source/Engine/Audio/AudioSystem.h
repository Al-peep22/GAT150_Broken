#pragma once
#include "../../ThirdParty/fmod/core/inc/fmod.hpp"
#include <iostream>
#include <string>
#include <map>

namespace viper {
	class AudioSystem {
	public:
		AudioSystem() = default;

		bool Initialize();
		void ShutDown();

		void Update();

		bool AddSound(const std::string& filename, const std::string& name);
		bool PlaySound(const std::string& name);
	private:
		bool CheckFMODResult(FMOD_RESULT result);
	private:
		FMOD::System* system = nullptr;
		std::map<std::string, FMOD::Sound*> sounds;
	};
}