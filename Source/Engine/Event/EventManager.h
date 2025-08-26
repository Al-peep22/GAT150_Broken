#pragma once

#include "Core/Singleton.h"
#include "Event.h"
#include "Observer.h"

#include <map>

#define OBSERVER_ADD(event_id)				viper::EventSystem::Instance().AddObserver(#event_id, *this)
#define OBSERVER_REMOVE_SELF				viper::EventSystem::Instance().RemoveObserver(*this)
#define EVENT_NOTIFY_DATA(event_id, data)	viper::EventSystem::Instance().Notify({ #event_id, data })
#define EVENT_NOTIFY(event_id)				viper::EventSystem::Instance().Notify({ #event_id, true })

namespace viper {
	class EventManager : public Singleton<EventManager> {
	public:
		void AddObserver(const Event::id_t& id, IObserver& observer);

		void RemoveObserver(IObserver& observer);

		void Notify(const Event& event);

		void RemoveAll() {observers.clear();}

	private:
		std::map<Event::id_t, std::list<IObserver*>> observers;
	};
}