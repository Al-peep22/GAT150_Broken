#include "Event/Observer.h"
#include "Event/EventManager.h"

namespace viper {
	IObserver::~IObserver() {
		viper::EventManager::Instance().RemoveObserver(*this);
	}
}