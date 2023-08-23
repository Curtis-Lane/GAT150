#include "EventManager.h"

#include "Core/Logger.h"

namespace ane {
	void EventManager::Update(float deltaTime) {
		//
	}

	void EventManager::Subscribe(Event::id_t id, IEventListener* listener, eventFunction function) {
		EventDispatcher dispatcher;

		dispatcher.listener = listener;
		dispatcher.function = function;

		INFO_LOG("Event subscribed: " << id);

		this->dispatchers[id].push_back(dispatcher);
	}

	void EventManager::Unsubscribe(Event::id_t id, IEventListener* listener) {
		// Get list of dispatchers for event
		auto& dispatchers = this->dispatchers[id];

		// Remove dipatcher with matching listener
		for(auto iter = dispatchers.begin(); iter != dispatchers.end(); iter++) {
			if(iter->listener == listener) {
				INFO_LOG("Event unsubscribed: " << id);

				dispatchers.erase(iter);
				break;
			}
		}
	}

	void EventManager::DispatchEvent(Event::id_t id, Event::data_t data) {
		Event event(id, data);

		if(this->dispatchers.find(id) != this->dispatchers.end()) {
			auto& dispatchers = this->dispatchers[id];
			for(auto& dispatcher : dispatchers) {
				dispatcher.function(event);
			}
		}
	}
}