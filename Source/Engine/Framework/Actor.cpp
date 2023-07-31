#include "Actor.h"

namespace ane {
	void Actor::Update(float deltaTime) {
		if(this->lifeSpan != -1.0f) {
			this->lifeSpan -= deltaTime;

			if(this->lifeSpan <= 0.0f) {
				this->destroyed = true;
			}
		}

		this->transform.position += this->velocity * deltaTime;
		this->velocity *= std::pow(1.0f - this->damping, deltaTime);
	}

	void Actor::Draw(ane::Renderer& renderer) {
		this->model->Draw(renderer, this->transform);
	}
}
