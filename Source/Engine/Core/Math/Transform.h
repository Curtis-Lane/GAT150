#pragma once

#include "Vector2.h"
#include "Matrix3x3.h"
#include "Core/JSON.h"

namespace ane {
	class Transform {
		public:
			Vector2 position;
			float rotation = 0.0f;
			float scale = 1.0f;

		public:
			Transform() = default;
			Transform(const vec2& position, float rotation, float scale = 1.0f) {
				this->position = position;
				this->rotation = rotation;
				this->scale = scale;
			}

			Matrix3x3 GetMatrix() const {
				Matrix3x3 matrixScale = Matrix3x3::CreateScale(this->scale);
				Matrix3x3 matrixRotation = Matrix3x3::CreateRotation(this->rotation);
				Matrix3x3 matrixTranslate = Matrix3x3::CreateTranslation(this->position);

				return matrixTranslate * matrixScale * matrixRotation;
			}

			void Read(const JSON_t& value);
	};
}