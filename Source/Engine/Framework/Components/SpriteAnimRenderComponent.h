#pragma once

#include "SpriteRenderComponent.h"

#include <map>

namespace ane {
	class SpriteAnimRenderComponent : public SpriteRenderComponent {
		public:
			struct AnimSequence {
				std::string name;

				float fps = 0.0f;
				int numColumns = 0;
				int numRows = 0;

				int startFrame = 0;
				int endFrame = 0;

				bool loop = true;

				std::shared_ptr<Texture> texture;
			};

		public:
			CLASS_DECLARATION(SpriteAnimRenderComponent);

			bool Initialize() override;
			void Update(float deltaTime) override;

			void SetSequence(const std::string& name);
			void UpdateSource();

		public:
			int frame = 0;
			float frameTimer = 0.0f;

		private:
			std::string defaultSequenceName;
			std::map<std::string, AnimSequence> sequences;
			AnimSequence* currentSequence = nullptr;
	};
}