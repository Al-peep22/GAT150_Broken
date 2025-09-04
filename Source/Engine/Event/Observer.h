#pragma once
#include "Event/Event.h"
namespace viper {
	class IObserver {
	public:
		virtual ~IObserver();
		virtual void OnNotify(const Event& event) = 0;
	};
}