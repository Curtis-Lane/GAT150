#pragma once

#include <vector>
#include "Core/Core.h"
#include "Renderer.h"

namespace ane {
	class Model {
		public:
			Model() = default;
			Model(const std::vector<vec2>& points) : points{points} {;}

			bool Load(const std::string& filename);
			void Draw(Renderer& renderer, const vec2& position, float rotation, float scale);
			void Draw(Renderer& renderer, const Transform& transform);

			float GetRadius();

		private:
			std::vector<vec2> points;
			Color color;
			float radius = 0.0f;
	};
}