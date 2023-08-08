#pragma once

#include "Framework/Resource/Resource.h"
#include "Core/Math/Vector2.h"

struct SDL_Texture;

namespace ane {
	class Texture : public Resource {
		public:
			Texture() = default;
			~Texture();

			virtual bool Create(std::string fileName, ...) override;

			bool Load(const std::string& fileName, class Renderer& renderer);
			Vector2 GetSize();

			friend class Renderer;

		private:
			SDL_Texture* texture = nullptr;
	};
}