#include "Core/Core.h"
#include "Framework/Framework.h"
#include "Renderer/Renderer.h"
#include "Input/InputSystem.h"
#include "Audio/AudioSystem.h"
#include "Physics/PhysicsSystem.h"

#include "PlatformGame.h"

int main(int argc, char* argv[]) {
	INFO_LOG("Initializing Engine");

	ane::MemoryTracker::Initialize();

	// Initialize engine
	ane::seedRandom((unsigned int) time(nullptr));
	ane::setFilePath("assets/PlatformGame");

	ane::globalRenderer.Initialize();
	ane::globalRenderer.CreateWindow("Platformer", 832, 600);

	ane::globalInputSystem.Initialize();
	ane::globalAudioSystem.Initialize();

	ane::PhysicsSystem::Instance().Initialize();

	// Create game
	std::unique_ptr<PlatformGame> game = std::make_unique<PlatformGame>();
	game->Initialize();

	// Main game loop
	bool quit = false;
	while(!quit) {
		ane::globalTime.Tick();

		ane::globalInputSystem.Update();
		ane::globalAudioSystem.Update();

		ane::globalParticleSystem.Update(ane::globalTime.GetDeltaTime());

		ane::PhysicsSystem::Instance().Update(ane::globalTime.GetDeltaTime());

		if(ane::globalInputSystem.GetKeyDown(SDL_SCANCODE_ESCAPE)) {
			quit = true;
		}

		// Update Game
		game->Update(ane::globalTime.GetDeltaTime());

		// Draw Game
		ane::globalRenderer.SetColor(0, 0, 0, 0);
		ane::globalRenderer.BeginFrame();

		game->Draw(ane::globalRenderer);

		ane::globalParticleSystem.Draw(ane::globalRenderer);

		ane::globalRenderer.EndFrame();
	}

	return 0;
}