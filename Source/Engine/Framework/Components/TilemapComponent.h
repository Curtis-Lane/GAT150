#pragma once

#include "Framework/Components/Component.h"
#include "Core/Math/Vector2.h"

#include <vector>

namespace ane {
	class TilemapComponent : public Component {
		public:
			CLASS_DECLARATION(TilemapComponent);

			bool Initialize() override;
			void Update(float deltaTime) override;

		public:
			int numColumns = 0;
			int numRows = 0;
			Vector2 size;

			std::vector<std::string> tileNames;
			std::vector<int> tiles;
	};
}
