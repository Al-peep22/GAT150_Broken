#pragma once
#include "FrameWork/Component.h"

namespace viper {
	class AudioSource : public Component {
	public:
		std::string audioClipName;

	public:


		// Inherited via Component
		void Update(float dt) override;

		void Play();
	};
}