#pragma once

#include "Framework/Actor.h"

#include "Framework/Components/SpriteAnimRenderComponent.h"
#include "Framework/Components/PhysicsComponent.h"
#include "Framework/Event/EventManager.h"

class Player : public ane::Actor, ane::IEventListener {
	public:
		CLASS_DECLARATION(Player);

		bool Initialize() override;
		void Update(float deltaTime) override;

		void OnCollisionEnter(Actor* other) override;
		void OnCollisionExit(Actor* other) override;

		void OnAnimationEnd(const ane::Event& event);

	private:
		float speed = 0.0f;
		float maxSpeed = 0.0f;
		float jump = 0.0f;
		int health = 100;
		int groundCount = 0;

		bool swordDrawn = false;
		int attackFrame = 0;
		bool busy = false;

		ane::PhysicsComponent* physicsComponent = nullptr;
		ane::SpriteAnimRenderComponent* spriteAnimRenderComponent = nullptr;
};