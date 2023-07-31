#pragma once

#include "Framework/Game.h"
#include "Renderer/Text.h"

class SpaceGame : public ane::Game {
	public:
		enum class State {
			Title,
			StartGame,
			StartLevel,
			Game,
			PlayerDeadStart,
			PlayerDead,
			GameOver
		};

	public:
		virtual bool Initialize() override;
		virtual void Shutdown() override;
		virtual void Update(float deltaTime) override;
		virtual void Draw(class ane::Renderer& renderer) override;

		void SetState(State state) {this->state = state;}

	private:
		State state = State::Title;
		float spawnTimer = 0.0f;
		float spawnTime = 3.0f;

		float stateTimer = 0.0f;

		float textTimer = -1.0f;

		std::shared_ptr<ane::Font> font;
		std::unique_ptr<ane::Text> scoreText;
		std::unique_ptr<ane::Text> livesText;
		std::unique_ptr<ane::Text> powerupText;
		std::unique_ptr<ane::Text> titleText;
		std::unique_ptr<ane::Text> gameOverText;
};