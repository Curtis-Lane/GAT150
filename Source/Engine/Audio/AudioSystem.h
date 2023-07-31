#pragma once

#include <fmod/core/inc/fmod.hpp>
#include <string>
#include <map>

namespace ane {
	class AudioSystem {
		public:
			AudioSystem() = default;
			~AudioSystem() = default;

			bool Initialize();
			void Shutdown();

			void Update();

			void AddAudio(const std::string& name, const std::string& fileName);
			void PlayOneShot(const std::string& name, bool loop = false);

		private:
			FMOD::System* fmodSystem = nullptr;
			std::map<std::string, FMOD::Sound*> sounds;
	};

	extern AudioSystem globalAudioSystem;
}