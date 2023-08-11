#pragma once

#include "Component.h"

namespace ane {
	class RenderComponent : public Component {
		public:
			virtual void Draw(class Renderer& renderer) = 0;
			virtual float GetRadius() {return 0.0f;}
	};
}