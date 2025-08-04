#include "Time.h"

namespace viper {
	void Time::Tick()
	{
		clock::time_point now = clock::now();
		this->time = std::chrono::duration<float>(now - this->startTime).count();
		this->deltaTime = std::chrono::duration<float>(now - this->frameTime).count();
		this->frameTime = now;
	}
}
