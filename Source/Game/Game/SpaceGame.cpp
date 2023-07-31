#include "SpaceGame.h"

#include "Player.h"
#include "Enemy.h"
#include "Bomber.h"

#include "Audio/AudioSystem.h"
#include "Input/InputSystem.h"
#include "Renderer/Renderer.h"
#include "Renderer/Text.h"
#include "Framework/Scene.h"

#include "Renderer/ModelManager.h"

bool SpaceGame::Initialize() {
	// Create font / text
	this->font = std::make_shared<ane::Font>("ArcadeClassic.ttf", 24);
	this->scoreText = std::make_unique<ane::Text>(this->font);
	this->scoreText->Create(ane::globalRenderer, "SCORE 0000", ane::Color(1.0f, 1.0f, 1.0f, 1.0f));

	this->titleText = std::make_unique<ane::Text>(this->font);
	this->titleText->Create(ane::globalRenderer, "CRAFTEROIDS", ane::Color(1.0f, 1.0f, 1.0f, 1.0f));

	this->gameOverText = std::make_unique<ane::Text>(this->font);
	this->gameOverText->Create(ane::globalRenderer, "GAME OVER", ane::Color(1.0f, 1.0f, 1.0f, 1.0f));

	this->livesText = std::make_unique<ane::Text>(this->font);
	this->livesText->Create(ane::globalRenderer, "LIVES 3", ane::Color(1.0f, 1.0f, 1.0f, 1.0f));

	this->powerupText = std::make_unique<ane::Text>(this->font);
	this->powerupText->Create(ane::globalRenderer, "", ane::Color(1.0f, 1.0f, 1.0f, 1.0f));

	// Load audio
	ane::globalAudioSystem.AddAudio("bow", "bow.wav");
	ane::globalAudioSystem.AddAudio("zombie_hurt1", "zombie_hurt1.wav");
	ane::globalAudioSystem.AddAudio("zombie_death", "zombie_death.wav");
	ane::globalAudioSystem.AddAudio("creeper_hiss3", "creeper_hiss3.wav");
	ane::globalAudioSystem.AddAudio("creeper_death", "creeper_death.wav");
	ane::globalAudioSystem.AddAudio("C418 - Aria Math", "C418_AriaMath.wav");
	ane::globalAudioSystem.PlayOneShot("C418 - Aria Math", true);

	this->scene = std::make_unique<ane::Scene>();

	return true;
}

void SpaceGame::Shutdown() {
	//
}

void SpaceGame::Update(float deltaTime) {
	switch(this->state) {
		case State::Title:
			if(ane::globalInputSystem.GetKeyDown(SDL_SCANCODE_SPACE)) {
				this->state = State::StartGame;
			}
			break;
		case State::StartGame:
			this->score = 0;
			this->lives = 3;
			this->state = State::StartLevel;
			break;
		case State::StartLevel:
			this->scene->RemoveAll();
			{
				std::unique_ptr<Player> player = std::make_unique<Player>(7.5f, ane::Pi, ane::Transform(ane::vec2(400, 300), 0.0f, 10.0f), ane::globalModelManager.Get("steve.txt"));
				player->tag = "Player";
				player->game = this;
				player->SetDamping(0.9f);
				this->scene->Add(std::move(player));
			}
			this->state = State::Game;
			break;
		case State::Game:
			if(this->textTimer != -1.0f) {
				this->textTimer -= deltaTime;
			}
			if(this->textTimer <= 0 && this->textTimer != -1.0f) {
				this->powerupText->Create(ane::globalRenderer, "", ane::Color(1.0f, 1.0f, 1.0f, 1.0f));
				this->textTimer = -1.0f;
			}

			if(this->score >= 2500) {
				Player* player = this->scene->GetActor<Player>();
				if(player != nullptr) {
					// This funky bit of code basically just checks if the player has the SlowMo powerup
					auto it = std::find(player->powerups.begin(), player->powerups.end(), Player::Powerups::SlowMo);
					if(it == player->powerups.end()) {
						player->powerups.push_back(Player::Powerups::SlowMo);
						this->powerupText->Create(ane::globalRenderer, "YOU HAVE EARNED SLOWMO!", ane::Color(1.0f, 1.0f, 1.0f, 1.0f));
						this->textTimer = 5.0f;
					}
				}
			}

			if(this->score >= 5000) {
				Player* player = this->scene->GetActor<Player>();
				if(player != nullptr) {
					// This funky bit of code basically just checks if the player has the DoubleShot powerup
					auto it = std::find(player->powerups.begin(), player->powerups.end(), Player::Powerups::DoubleShot);
					if(it == player->powerups.end()) {
						player->powerups.push_back(Player::Powerups::DoubleShot);
						this->powerupText->Create(ane::globalRenderer, "YOU HAVE EARNED DOUBLE SHOT!", ane::Color(1.0f, 1.0f, 1.0f, 1.0f));
						this->textTimer = 5.0f;
					}
				}
			}

			this->spawnTimer += deltaTime + (1.0f * (this->score / 250000.0f));
			if(this->spawnTimer >= this->spawnTime) {
				this->spawnTimer = 0.0f;

				if(ane::random(10) < 7) {
					std::unique_ptr enemy = std::make_unique<Enemy>(ane::randomf(75.0f, 150.0f), ane::Pi, ane::Transform(ane::vec2(ane::random(ane::globalRenderer.GetWidth()), ane::random(ane::globalRenderer.GetHeight())), ane::randomf(ane::TwoPi), 6.0f), ane::globalModelManager.Get("zombie.txt"));
					enemy->tag = "Enemy";
					enemy->game = this;
					this->scene->Add(std::move(enemy));					
				} else {
					std::unique_ptr enemy = std::make_unique<Bomber>(ane::randomf(150.0f, 250.0f), ane::Pi, ane::Transform(ane::vec2(ane::random(ane::globalRenderer.GetWidth()), ane::random(ane::globalRenderer.GetHeight())), ane::randomf(ane::TwoPi), 5.5f), ane::globalModelManager.Get("creeper.txt"));
					enemy->tag = "Enemy";
					enemy->game = this;
					this->scene->Add(std::move(enemy));
				}
			}
			this->scoreText->Create(ane::globalRenderer, "SCORE " + std::to_string(this->score), ane::Color(1.0f, 1.0f, 1.0f, 1.0f));
			this->livesText->Create(ane::globalRenderer, "LIVES " + std::to_string(this->lives), ane::Color(1.0f, 1.0f, 1.0f, 1.0f));
			break;
		case State::PlayerDeadStart:
			this->stateTimer = 3.0f;
			if(this->lives <= 0) {
				this->state = State::GameOver;
			} else {
				this->state = State::PlayerDead;
			}
			break;
		case State::PlayerDead:
			this->stateTimer -= deltaTime;
			if(this->stateTimer <= 0.0f) {
				this->state = State::StartLevel;
			}
			break;
		case State::GameOver:
			this->stateTimer -= deltaTime;
			if(this->stateTimer <= 0) {
				this->scene->RemoveAll();
				this->state = State::Title;
			}
			break;
		default:
			break;
	}
		
	this->scene->Update(deltaTime);
}

void SpaceGame::Draw(ane::Renderer& renderer) {
	if(this->state == State::Title) {
		this->titleText->Draw(renderer, 335, 300);
	}
	if(this->state == State::GameOver) {
		this->gameOverText->Draw(renderer, 335, 300);
	}
	this->powerupText->Draw(renderer, 300, 300);

	this->livesText->Draw(renderer, 650, 30);
	this->scoreText->Draw(renderer, 40, 30);
	this->scene->Draw(renderer);
}
