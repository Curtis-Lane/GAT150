#pragma once

#include "Framework/Resource/Resource.h"

#include "Core/Core.h"
#include "Renderer.h"

#include <vector>

namespace ane {
	class Model : public Resource {
		public:
			Model() = default;
			Model(const std::vector<vec2>& points) : points{points} {;}

			virtual bool Create(std::string fileName, ...) override;
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