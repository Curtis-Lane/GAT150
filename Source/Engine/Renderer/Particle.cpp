#include "Particle.h"

#include "Renderer.h"

namespace ane {
	void Particle::Update(float deltaTime) {
		this->data.lifeTimer += deltaTime;
		if(this->data.lifeTimer >= this->data.lifeTime) {
			this->isActive = false;
			return;
		}

		this->data.prevPosition = this->data.position;
		this->data.position += this->data.velocity * deltaTime;
		this->data.velocity *= std::pow(1.0f - this->data.damping, deltaTime);
	}

	void Particle::Draw(Renderer& renderer) {
		renderer.SetColor(this->data.color);
		renderer.DrawLine(this->data.position, this->data.prevPosition);
	}
}