#pragma once

#include <box2d/include/box2d/b2_world_callbacks.h>

namespace ane {
	class ContactListener : public b2ContactListener {
		public:
			void BeginContact(class b2Contact* contact) override;
			void EndContact(class b2Contact* contact) override;
	};
}