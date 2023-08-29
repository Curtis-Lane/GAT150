#include "PlatformGame.h"

#include "Audio/AudioSystem.h"
#include "Input/InputSystem.h"
#include "Renderer/Renderer.h"
#include "Framework/Framework.h"

bool PlatformGame::Initialize() {
	this->scene = std::make_unique<ane::Scene>();
	this->scene->Load("Scenes/platform_game_scene.json");
	this->scene->Load("Scenes/tilemap.json");
	this->scene->Initialize();

	// Add events
	EVENT_SUBSCRIBE("OnAddPoints", PlatformGame::OnAddPoints);
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
				//auto actor = INSTANTIATE(ane::Actor, "Crate");
				//actor->transform.position = ane::Vector2(ane::random(ane::globalRenderer.GetWidth()), 100);
				//actor->Initialize();
				//ADD_ACTOR(actor);
			}
			break;
		case State::StartGame:
			break;
		case State::StartLevel:
			break;
		case State::Game:
			break;
		case State::PlayerDeadStart:
			break;
		case State::PlayerDead:
			break;
		case State::GameOver:
			break;
		default:
			break;
	}

	this->scene->Update(deltaTime);
}

void PlatformGame::Draw(ane::Renderer& renderer) {
	this->scene->Draw(renderer);
}

void PlatformGame::OnAddPoints(const ane::Event& event) {
	this->score += std::get<int>(event.data);
}

void PlatformGame::OnPlayerDead(const ane::Event& event) {
	this->lives--;
	this->state = State::PlayerDeadStart;
}
