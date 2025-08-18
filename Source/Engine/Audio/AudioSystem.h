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
		bool PlaySound(class AudioClip& audioClip);

	private:
		static bool CheckFMODResult(FMOD_RESULT result);
	private:
		friend class AudioClip;

		FMOD::System* system = nullptr;
		std::map<std::string, FMOD::Sound*> sounds;
	};
}