#include "Core/Core.h"
#include "Framework/Framework.h"
#include "Renderer/Renderer.h"
#include "Input/InputSystem.h"
#include "Audio/AudioSystem.h"
#include "Physics/PhysicsSystem.h"
#include "SpaceGame.h"

#include <functional>
#include <iostream>
#include <vector>

class Star {
	public:
		ane::Vector2 pos;
		ane::Vector2 vel;

	public:
		Star(const ane::Vector2& pos, const ane::Vector2& vel) : pos{pos}, vel{vel} {}

		void Update(int width, int height) {
			this->pos += this->vel * ane::globalTime.GetDeltaTime();

			if(this->pos.x > width) {
				this->pos.x = 0;
			} else if(this->pos.x < 0) {
				this->pos.x = static_cast<float>(width);
			}

			if(this->pos.y > height) {
				this->pos.y = 0;
			} else if(this->pos.y < 0) {
				this->pos.y = static_cast<float>(height);
			}
		}

		void Draw(ane::Renderer& renderer) {
			renderer.DrawPoint(this->pos.x, this->pos.y);
		}
};

void print(int i) {
	std::cout << i << std::endl;
}

int add(int i, int j) {
	return i + j;
}

int sub(int i, int j) {
	return i - j;
}

class A {
	public:
		int add(int i, int j) {
			return i + j;
		}
};

union Data {
	int i;
	bool b;
	char c[6];
};

int main(int argc, char* argv[]) {
	Data data;
	data.i = 0;

	std::cout << data.b << std::endl;

	void (*func_ptr)(int) = &print;
	func_ptr(5);

	int (*op_ptr)(int, int);
	op_ptr = &add;

	std::cout << op_ptr(4, 4) << std::endl;

	op_ptr = &sub;

	std::cout << op_ptr(4, 4) << std::endl;

	std::function<int(int, int)> op;
	op = &add;

	std::cout << op(5, 6) << std::endl;

	A a;
	op = std::bind(&A::add, &a, std::placeholders::_1, std::placeholders::_2);
	std::cout << op(6, 6) << std::endl;

	INFO_LOG("Initializing Engine");

	ane::MemoryTracker::Initialize();

	ane::seedRandom((unsigned int) time(nullptr));
	ane::setFilePath("assets");

	ane::globalRenderer.Initialize();
	ane::globalRenderer.CreateWindow("CRAFTEROIDS", 800, 600);

	ane::globalInputSystem.Initialize();
	ane::globalAudioSystem.Initialize();

	ane::PhysicsSystem::Instance().Initialize();

	std::unique_ptr<SpaceGame> game = std::make_unique<SpaceGame>();
	game->Initialize();
	
	std::vector<Star> stars;
	for(int i = 0; i < 5000; i++) {
		ane::Vector2 pos(ane::Vector2(ane::random(ane::globalRenderer.GetWidth()), ane::random(ane::globalRenderer.GetHeight())));
		ane::Vector2 vel(ane::randomf(100, 250), 0.0f);

		stars.push_back(Star(pos, vel));
	}

	// Main game loop
	bool quit = false;
	while(!quit) {
		ane::globalTime.Tick();

		ane::globalInputSystem.Update();

		ane::globalAudioSystem.Update();

		ane::globalParticleSystem.Update(ane::globalTime.GetDeltaTime());
		 
		if(ane::globalInputSystem.GetKeyDown(SDL_SCANCODE_ESCAPE)) {
			quit = true;
		}

		// Update Game
		game->Update(ane::globalTime.GetDeltaTime());

		// Draw Game
		ane::globalRenderer.SetColor(0, 0, 0, 0);
		ane::globalRenderer.BeginFrame();

		ane::globalRenderer.SetColor(ane::random(0, 255), 255, 0, 0);

		game->Draw(ane::globalRenderer);

		ane::globalParticleSystem.Draw(ane::globalRenderer);
		
		for(Star& star : stars) {
			star.Update(ane::globalRenderer.GetWidth(), ane::globalRenderer.GetHeight());

			ane::globalRenderer.SetColor(ane::random(0, 255), ane::random(0, 255), ane::random(0, 255), 0);
			star.Draw(ane::globalRenderer);
		}
		
		ane::globalRenderer.EndFrame();
	}
	
	stars.clear();

	return 0;
}