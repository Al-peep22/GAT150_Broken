#include "Event/Observer.h"
#include "Event/EventManager.h"

namespace viper {
	viper::IObserver::~IObserver() {
		//EventManager::Instance().RemoveObserver(*this);
		OBSERVER_REMOVE_SELF;
	}
}