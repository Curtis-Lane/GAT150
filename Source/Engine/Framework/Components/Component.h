#pragma once

namespace ane {
	class Component {
		public:
			virtual void Update(float deltaTime) = 0;

			friend class Actor;
		
		protected:
			class Actor* owner = nullptr;
	};
}