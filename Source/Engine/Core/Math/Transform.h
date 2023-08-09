#pragma once

//#include "Vector2.h"
#include "Matrix2x2.h"

namespace ane {
	class Transform {
		public:
			Vector2 position;
			float rotation = 0;
			float scale = 1;

		public:
			Transform() = default;
			Transform(const vec2& position, float rotation, float scale = 1.0f) {
				this->position = position;
				this->rotation = rotation;
				this->scale = scale;
			}

			Matrix2x2 GetMatrix() const {
				Matrix2x2 matrixScale = Matrix2x2::CreateScale(this->scale);
				Matrix2x2 matrixRotation = Matrix2x2::CreateRotation(this->rotation);

				return matrixScale * matrixRotation;
			}
	};
}