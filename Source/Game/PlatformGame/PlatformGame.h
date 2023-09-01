#pragma once

#include "Framework/Event/EventManager.h"
#include "Framework/Game.h"
#include "Renderer/Text.h"

#define ADD_ACTOR(actor) this->scene->Add(std::move(actor))
#define ADD_ACTOR_FULL(actor) actor->game = this; actor->Initialize(); this->scene->Add(std::move(actor))

class PlatformGame : public ane::Game, ane::IEventListener {
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
		void OnPickupCoin(const ane::Event& event);
		void OnPlayerDead(const ane::Event& event);

	private:
		State state = State::Title;
		float spawnTimerCoin = 0.0f;
		float spawnTimeCoin = 10.0f;

		float spawnTimerEnemy = 0.0f;
		float spawnTimeEnemy = 7.0f;

		float stateTimer = 0.0f;

		//float textTimer = -1.0f;
};