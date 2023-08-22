#include "SpaceGame.h"

#include "Player.h"
#include "Enemy.h"
#include "Bomber.h"

#include "Audio/AudioSystem.h"
#include "Input/InputSystem.h"
#include "Renderer/Renderer.h"
#include "Framework/Framework.h"

bool SpaceGame::Initialize() {
	// Load audio
	ane::globalAudioSystem.AddAudio("bow", "bow.wav");
	ane::globalAudioSystem.AddAudio("zombie_hurt1", "zombie_hurt1.wav");
	ane::globalAudioSystem.AddAudio("zombie_death", "zombie_death.wav");
	ane::globalAudioSystem.AddAudio("creeper_hiss3", "creeper_hiss3.wav");
	ane::globalAudioSystem.AddAudio("creeper_death", "creeper_death.wav");
	ane::globalAudioSystem.AddAudio("C418 - Aria Math", "C418_AriaMath.wav");
	ane::globalAudioSystem.PlayOneShot("C418 - Aria Math", true);

	this->scene = std::make_unique<ane::Scene>();
	this->scene->Load("scene.json");
	this->scene->Initialize();

	// Add events
	EVENT_SUBSCRIBE("OnAddPoints", SpaceGame::OnAddPoints);
	EVENT_SUBSCRIBE("OnPlayerDead", SpaceGame::OnPlayerDead);

	return true;
}

void SpaceGame::Shutdown() {
	//
}

void SpaceGame::Update(float deltaTime) {
	switch(this->state) {
		case State::Title:
			{
				auto gameOverText = this->scene->GetActorByName("Game Over");
				if(gameOverText != nullptr) {
					gameOverText->active = false;
				}
			}
			if(ane::globalInputSystem.GetKeyDown(SDL_SCANCODE_SPACE)) {
				this->state = State::StartGame;
				auto titleText = this->scene->GetActorByName("Title");
				if(titleText != nullptr) {
					titleText->active = false;
				}
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
				// Create Player
				std::unique_ptr<Player> player = std::make_unique<Player>(7.5f, ane::Pi, ane::Transform(ane::vec2(400, 300), 0.0f, 1.0f));
				player->tag = "Player";
				player->game = this;

				// Create sprite component
				std::unique_ptr<ane::SpriteRenderComponent> renderComponent = CREATE_CLASS(SpriteRenderComponent);
				renderComponent->texture = GET_RESOURCE(ane::Texture, "steve.png", ane::globalRenderer);
				player->AddComponent(std::move(renderComponent));

				// Create physics component
				std::unique_ptr<ane::EnginePhysicsComponent> physicsComponent = CREATE_CLASS(EnginePhysicsComponent);
				physicsComponent->damping = 0.9f;
				player->AddComponent(std::move(physicsComponent));

				// Create collision component
				std::unique_ptr<ane::CircleCollisionComponent> collisionComponent = CREATE_CLASS(CircleCollisionComponent);
				collisionComponent->radius = 30.0f;
				player->AddComponent(std::move(collisionComponent));

				player->Initialize();

				this->scene->Add(std::move(player));
			}
			this->state = State::Game;
			break;
		case State::Game:
			if(this->textTimer != -1.0f) {
				this->textTimer -= deltaTime;
			}
			if(this->textTimer <= 0 && this->textTimer != -1.0f) {
				auto powerUpText = this->scene->GetActorByName("Power Up");
				if(powerUpText != nullptr) {
					powerUpText->active = false;
				}
				this->textTimer = -1.0f;
			}

			if(this->score >= 2500) {
				Player* player = this->scene->GetActor<Player>();
				if(player != nullptr) {
					// This funky bit of code basically just checks if the player has the SlowMo powerup
					auto it = std::find(player->powerups.begin(), player->powerups.end(), Player::Powerups::SlowMo);
					if(it == player->powerups.end()) {
						player->powerups.push_back(Player::Powerups::SlowMo);
						auto powerUpText = this->scene->GetActorByName("Power Up");
						if(powerUpText != nullptr) {
							powerUpText->GetComponent<ane::TextRenderComponent>()->SetText("YOU HAVE EARNED SLOWMO!");
							powerUpText->active = true;
						}
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
						auto powerUpText = this->scene->GetActorByName("Power Up");
						if(powerUpText != nullptr) {
							powerUpText->GetComponent<ane::TextRenderComponent>()->SetText("YOU HAVE EARNED DOUBLE SHOT!");
							powerUpText->active = true;
						}
						this->textTimer = 5.0f;
					}
				}
			}

			this->spawnTimer += deltaTime + (1.0f * (this->score / 250000.0f));
			if(this->spawnTimer >= this->spawnTime) {
				this->spawnTimer = 0.0f;

				if(ane::random(10) < 7) {
					// Create zombie
					std::unique_ptr enemy = std::make_unique<Enemy>(ane::randomf(75.0f, 150.0f), ane::Pi, ane::Transform(ane::vec2(ane::random(ane::globalRenderer.GetWidth()), ane::random(ane::globalRenderer.GetHeight())), ane::randomf(ane::TwoPi), 0.6f));
					enemy->tag = "Enemy";
					enemy->game = this;
					// Create components
					std::unique_ptr<ane::SpriteRenderComponent> component = std::make_unique<ane::SpriteRenderComponent>();
					component->texture = GET_RESOURCE(ane::Texture, "zombie.png", ane::globalRenderer);
					enemy->AddComponent(std::move(component));

					std::unique_ptr<ane::CircleCollisionComponent> collisionComponent = std::make_unique<ane::CircleCollisionComponent>();
					collisionComponent->radius = 30.0f;
					enemy->AddComponent(std::move(collisionComponent));

					enemy->Initialize();

					this->scene->Add(std::move(enemy));
				} else {
					// Create creeper
					std::unique_ptr enemy = std::make_unique<Bomber>(ane::randomf(150.0f, 250.0f), ane::Pi, ane::Transform(ane::vec2(ane::random(ane::globalRenderer.GetWidth()), ane::random(ane::globalRenderer.GetHeight())), ane::randomf(ane::TwoPi), 0.55f));
					enemy->tag = "Enemy";
					enemy->game = this;
					// Create components
					std::unique_ptr<ane::SpriteRenderComponent> component = std::make_unique<ane::SpriteRenderComponent>();
					component->texture = GET_RESOURCE(ane::Texture, "creeper.png", ane::globalRenderer);
					enemy->AddComponent(std::move(component));

					std::unique_ptr<ane::CircleCollisionComponent> collisionComponent = std::make_unique<ane::CircleCollisionComponent>();
					collisionComponent->radius = 30.0f;
					enemy->AddComponent(std::move(collisionComponent));

					enemy->Initialize();

					this->scene->Add(std::move(enemy));
				}
			}
			{
				auto scoreText = this->scene->GetActorByName("Score");
				if(scoreText != nullptr) {
					scoreText->GetComponent<ane::TextRenderComponent>()->SetText("SCORE " + std::to_string(this->score));
				}
			}
			{
				auto livesText = this->scene->GetActorByName("Lives");
				if(livesText != nullptr) {
					livesText->GetComponent<ane::TextRenderComponent>()->SetText("LIVES " + std::to_string(this->lives));
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
			break;
		case State::PlayerDead:
			this->stateTimer -= deltaTime;
			if(this->stateTimer <= 0.0f) {
				this->state = State::StartLevel;
			}
			break;
		case State::GameOver:
			{
				auto gameOverText = this->scene->GetActorByName("Game Over");
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

void SpaceGame::Draw(ane::Renderer& renderer) {
	this->scene->Draw(renderer);
}

void SpaceGame::OnAddPoints(const ane::Event& event) {
	this->score += std::get<int>(event.data);
}

void SpaceGame::OnPlayerDead(const ane::Event& event) {
	this->lives--;
	this->state = State::PlayerDeadStart;
}
