#pragma once

#include "Core/Core.h"
#include "Renderer/Renderer.h"
#include "Renderer/Model.h"

#include <memory>

namespace ane {
	class Actor {
		public:
			Actor() = default;
			Actor(const ane::Transform& transform, std::shared_ptr<Model> model) {this->transform = transform; this->model = model;}
			Actor(const ane::Transform& transform) {this->transform = transform; this->model = nullptr;}

			virtual void Update(float deltaTime);
			virtual void Draw(ane::Renderer& renderer);

			float GetRadius() {return (this->model != nullptr) ? this->model->GetRadius() * this->transform.scale : -10000;}
			virtual void OnCollision(Actor* other) {;}

			void AddForce(const vec2& force) {this->velocity += force;}
			void SetDamping(float damping) {this->damping = damping;}

			class Scene* scene = nullptr;

			class Game* game = nullptr;

			friend class Scene;
			friend class Enemy;
			ane::Transform transform;
			std::string tag;
			float lifeSpan = -1.0f;

		protected:
			bool destroyed = false;
			std::shared_ptr<Model> model;

			vec2 velocity;
			float damping = 0.0f;
	};
}