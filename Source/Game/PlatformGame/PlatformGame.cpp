#include "PlatformGame.h"

#include "Audio/AudioSystem.h"
#include "Input/InputSystem.h"
#include "Renderer/Renderer.h"
#include "Framework/Framework.h"
#include "Player.h"
#include "Enemy.h"

bool PlatformGame::Initialize() {
	this->scene = std::make_unique<ane::Scene>();
	this->scene->Load("Scenes/platform_game_scene.json");
	this->scene->Load("Scenes/tilemap.json");
	this->scene->Initialize();

	// Add sounds
	ane::globalAudioSystem.AddAudio("sword_slash", "Audio/sword_slash.wav");

	// Add events
	EVENT_SUBSCRIBE("OnPickupCoin", PlatformGame::OnPickupCoin);
	EVENT_SUBSCRIBE("OnPlayerDead", PlatformGame::OnPlayerDead);

	return true;
}

void PlatformGame::Shutdown() {
	//
}

void PlatformGame::Update(float deltaTime) {
	switch(this->state) {
		case State::Title:
			{
				auto healthText = this->scene->GetActorByName("Health");
				if(healthText != nullptr) {
					healthText->active = false;
				}

				auto scoreText = this->scene->GetActorByName("Score");
				if(scoreText != nullptr) {
					scoreText->active = false;
				}

				auto gameOverText = this->scene->GetActorByName("GameOver");
				if(gameOverText != nullptr) {
					gameOverText->active = false;
				}
			}
			if(ane::globalInputSystem.GetKeyDown(SDL_SCANCODE_SPACE)) {
				this->SetState(State::StartGame);
			}
			break;
		case State::StartGame:
			this->score = 0;
			this->lives = 3;

			this->SetState(State::StartLevel);
			break;
		case State::StartLevel:
			this->scene->RemoveAll();
			{
				auto healthText = this->scene->GetActorByName("Health");
				if(healthText != nullptr) {
					healthText->active = true;
				}

				auto scoreText = this->scene->GetActorByName("Score");
				if(scoreText != nullptr) {
					scoreText->active = true;
				}

				auto titleText = this->scene->GetActorByName("Title");
				if(titleText != nullptr) {
					titleText->active = false;
				}

				auto player = INSTANTIATE(Player, "Player");
				player->game = this;
				player->Initialize();
				ADD_ACTOR(player);
			}

			this->spawnTimerCoin = 0.0f;
			this->spawnTimerEnemy = 0.0f;

			this->SetState(State::Game);
			break;
		case State::Game:
			this->spawnTimerCoin += deltaTime;
			if(this->spawnTimerCoin >= this->spawnTimeCoin) {
				auto oldCoin = this->scene->GetActorByName("Coin");
				if(oldCoin == nullptr) {
					auto newCoin = INSTANTIATE(ane::Actor, "Coin");
					ADD_ACTOR_FULL(newCoin);
				}
				this->spawnTimerCoin = 0.0f;
			}

			this->spawnTimerEnemy += deltaTime;
			if(this->spawnTimerEnemy >= this->spawnTimeEnemy) {
				auto enemy = INSTANTIATE(Enemy, "Enemy");
				ADD_ACTOR_FULL(enemy);

				this->spawnTimerEnemy = 0.0f;
			}

			{
				auto healthText = this->scene->GetActorByName("Health");
				if(healthText != nullptr) {
					auto player = this->scene->GetActorByName("Player");
					if(player != nullptr) {
						healthText->GetComponent<ane::TextRenderComponent>()->SetText("Health " + std::to_string(dynamic_cast<Player*>(player)->health));
					}
				}

				auto scoreText = this->scene->GetActorByName("Score");
				if(scoreText != nullptr) {
					scoreText->GetComponent<ane::TextRenderComponent>()->SetText("Score " + std::to_string(this->score));
				}
			}
			break;
		case State::PlayerDeadStart:
			this->stateTimer = 3.0f;
			if(this->lives <= 0) {
				this->state = State::GameOver;
			} else {
				this->state = State::PlayerDead;
			}
			{
				auto healthText = this->scene->GetActorByName("Health");
				if(healthText != nullptr) {
					healthText->GetComponent<ane::TextRenderComponent>()->SetText("Health 0");
				}
			}
			break;
		case State::PlayerDead:
			this->stateTimer -= deltaTime;
			if(this->stateTimer <= 0.0f) {
				this->state = State::StartLevel;
			}
			break;
		case State::GameOver:
			{
				auto gameOverText = this->scene->GetActorByName("GameOver");
				if(gameOverText != nullptr) {
					gameOverText->active = true;
				}
			}
			this->stateTimer -= deltaTime;
			if(this->stateTimer <= 0) {
				this->scene->RemoveAll();
				this->state = State::Title;
				auto titleText = this->scene->GetActorByName("Title");
				if(titleText != nullptr) {
					titleText->active = true;
				}
			}
			break;
		default:
			break;
	}

	this->scene->Update(deltaTime);
}

void PlatformGame::Draw(ane::Renderer& renderer) {
	this->scene->Draw(renderer);
}

void PlatformGame::OnPickupCoin(const ane::Event& event) {
	this->score += std::get<int>(event.data);
}

void PlatformGame::OnPlayerDead(const ane::Event& event) {
	this->lives--;
	this->state = State::PlayerDeadStart;
}
