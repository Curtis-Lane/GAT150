#pragma once

#include "Framework/Singleton.h"

#include <functional>
#include <list>
#include <map>

#include "Event.h"

#define EVENT_SUBSCRIBE(id, function)	ane::EventManager::Instance().Subscribe(id, this, std::bind(&function, this, std::placeholders::_1))
#define EVENT_UNSUBSCRIBE(id)			ane::EventManager::Instance().Unsubscribe(id, this)
#define EVENT_DISPATCH(id, value)		ane::EventManager::Instance().DispatchEvent(id, value)

namespace ane {
	class IEventListener {
		//
	};

	class EventManager : public Singleton<EventManager> {
		public:
			using eventFunction = std::function<void(const Event&)>;

			struct EventDispatcher {
				IEventListener* listener = nullptr; // Object that can listen for events
				eventFunction function; // Function that is called on event
			};

		public:
			void Update(float deltaTime);

			void Subscribe(Event::id_t id, IEventListener* listener, eventFunction function);
			void Unsubscribe(Event::id_t id, IEventListener* listener);

			void DispatchEvent(Event::id_t id, Event::data_t data);

			friend Singleton;

		private:
			EventManager() = default;

		private:
			std::map<Event::id_t, std::list<EventDispatcher>> dispatchers;
	};
}