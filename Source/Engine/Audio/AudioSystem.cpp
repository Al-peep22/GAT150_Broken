#include "AudioSystem.h"
#include <iostream>
#include "../Core/StringHelper.h"
#include "../../ThirdParty/fmod/core/inc/fmod_errors.h"
#include "../../ThirdParty/fmod/core/inc/fmod.hpp"
#include "Core/Logger.h"
#include "AudioClip.h"

using namespace std;
namespace viper {

    bool AudioSystem::CheckFMODResult(FMOD_RESULT result)
    {
        if (result != FMOD_OK) {
           Logger::Error("",FMOD_ErrorString(result));
            return false;
        }
        return true;
    }

    bool viper::AudioSystem::Initialize()
    {
        FMOD_RESULT result = FMOD::System_Create(&system);
        if (!CheckFMODResult(result)) { return false; }

        void* extradriverdat = nullptr;
        result = system->init(32, FMOD_INIT_NORMAL, extradriverdat);
        if (!CheckFMODResult(result)) { return false; }

        return true;
    }

    void viper::AudioSystem::ShutDown()
    {
        //FMOD_RESULT result = system->release();
        CheckFMODResult(system->release());
    }

    void viper::AudioSystem::Update()
    {
        CheckFMODResult(system->update());
    }
    
    bool viper::AudioSystem::AddSound(const std::string& filename, const std::string& name)  
    {  
        std::string key = (name.empty()) ? filename : name;

        key = viper::toLower(key);

        // check if key exists in sounds map
        if (sounds.find(key) != sounds.end()) {
            Logger::Warning("Audio System : name already exists ",key);
            return false;
        }

        // create sound from key
       FMOD::Sound* sound = nullptr;
       FMOD_RESULT result = system->createSound(filename.c_str(), FMOD_DEFAULT, 0, &sound);
       if (!CheckFMODResult(result)) { return false; }

       // insert sound into map
       sounds[key] = sound;

       return true;  
    }
    bool viper::AudioSystem::PlaySound(const std::string& name)
    {
        std::string key = name;

        // convert to lowercase
        for (char& c : key) {
            c = std::tolower(c);
        }

        // check if sound exists in sounds map
        if (sounds.find(key) == sounds.end()) {
            Logger::Warning("Audio System : name doesn't exist ", name);
            return false;
        }

        // play sound from key
        FMOD_RESULT result = system->playSound(sounds[key], 0, false, nullptr);
        if (!CheckFMODResult(result)) { return false; }

        return true;
    }

    bool AudioSystem::PlaySound(AudioClip& audioClip)
    {
        FMOD_RESULT result = system->playSound(audioClip.sound, 0, false, nullptr);
        if (!CheckFMODResult(result)) { return false; }
        return true;
    }

}