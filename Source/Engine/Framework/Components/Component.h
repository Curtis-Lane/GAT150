#pragma once

#include "Framework/Object.h"

namespace ane {
	class Component : public Object {
		public:
			virtual void Update(float deltaTime) = 0;

			friend class Actor;
		
		public:
			class Actor* owner = nullptr;
	};
}