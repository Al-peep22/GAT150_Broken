#include "EngineCPH.h"
#include "AudioClip.h"
#include "AudioSystem.h"

namespace viper {
	AudioClip::~AudioClip()
	{
		if(sound) sound->release();
	}

	bool AudioClip::Load(const std::string& filename, AudioSystem& audioSystem)
	{

		FMOD_RESULT result = audioSystem.system->createSound(filename.c_str(), FMOD_DEFAULT, 0, &sound);
		if (!AudioSystem::CheckFMODResult(result)) { return false; }

		return true;
	}
}