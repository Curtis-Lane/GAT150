#pragma once

#include <memory>

namespace ane {
	class Game {
		public:
			Game() = default;
			virtual ~Game() = default;

			virtual bool Initialize() = 0;
			virtual void Shutdown() = 0;

			virtual void Update(float deltaTime) = 0;
			virtual void Draw(class Renderer& renderer) = 0;

			int GetScore() const {return this->score;}
			void AddPoints(int points) {this->score += points;}

			int GetLives() const {return this->lives;}
			void SetLives(int lives) {this->lives = lives;}

		protected:
			std::unique_ptr<class Scene> scene;

			int score = 0;
			int lives = 0;
	};
}