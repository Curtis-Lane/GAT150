#pragma once

#include "Core/Vector2.h"

struct SDL_Texture;

namespace ane {
	class Texture {
		public:
			Texture() = default;
			~Texture();

			bool Create(class Renderer& renderer, const std::string& fileName);
			Vector2 GetSize();

			friend class Renderer;

		private:
			SDL_Texture* texture = nullptr;
	};
}