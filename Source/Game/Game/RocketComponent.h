#pragma once

#include "Framework/Components/Component.h"
#include "Audio/AudioSystem.h"

namespace ane {
	class RocketComponent : public Component {
		public:
		/*
		Rocket(float speed, const ane::Transform& transform, const std::string& fireSound) :
			ane::Actor(transform) {
			this->speed = speed;
			this->lifeSpan = 2.0f;
			ane::globalAudioSystem.PlayOneShot(fireSound);
		}
		*/

		//

		bool Initialize() override;

		void Update(float deltaTime) override;
		void OnCollision(Actor* other);
		void Read(const JSON_t& value);

		private:
			float speed = 0.0f;
	};
}