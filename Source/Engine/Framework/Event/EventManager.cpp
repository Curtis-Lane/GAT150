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
		//
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