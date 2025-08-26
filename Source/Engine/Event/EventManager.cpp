#include "EngineCPH.h"

#include "Core/StringHelper.h"

namespace viper {
	void EventManager::AddObserver(const Event::id_t& id, IObserver& observer) {
		observers[toLower(id)].push_back(&observer);
	}

	void EventManager::RemoveObserver(IObserver& observer) {
		IObserver* observerPtr = &observer;

		// Itrerate through all event types
		for (auto& eventType : observers) {
			// Get list of observers for event type
			auto observers = eventType.second;

			// Remove matching observers from this event type
			std::erase_if(observers, [observerPtr](auto observer) {
				return (observer == observerPtr);
				});
		}
	}

	void EventManager::Notify(const Event& event) {
		auto it = observers.find(toLower(event.id));
		if (it != observers.end()) {
			auto& observers = it->second;
			for (auto observer : observers) {
				observer->OnNotify(event);
			}
		}
		else {
			Logger::Warning("Could not find event {}", event.id);
		}
	}
}