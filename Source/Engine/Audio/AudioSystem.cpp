#include "AudioSystem.h"

namespace ane {
	AudioSystem globalAudioSystem;

	bool AudioSystem::Initialize() {
		FMOD::System_Create(&(this->fmodSystem));

		void* extraDriverData = nullptr;
		this->fmodSystem->init(32, FMOD_INIT_NORMAL, extraDriverData);

		return true;
	}

	void AudioSystem::Shutdown() {
		for(auto sound : this->sounds) {
			sound.second->release();
		}
		this->sounds.clear();

		this->fmodSystem->close();
		this->fmodSystem->release();
	}

	void AudioSystem::Update() {
		this->fmodSystem->update();
	}

	void AudioSystem::AddAudio(const std::string& name, const std::string& fileName) {
		if(this->sounds.find(name) == this->sounds.end()) {
			FMOD::Sound* sound = nullptr;
			this->fmodSystem->createSound(fileName.c_str(), FMOD_DEFAULT, 0, &sound);
			this->sounds[name] = sound;
		}
	}

	void AudioSystem::PlayOneShot(const std::string& name, bool loop) {
		auto iter = this->sounds.find(name);
		if(iter != this->sounds.end()) {
			FMOD::Sound* sound = iter->second;
			sound->setMode(loop ? FMOD_LOOP_NORMAL : FMOD_LOOP_OFF);

			FMOD::Channel* channel;
			this->fmodSystem->playSound(sound, 0, false, &channel);
		}
	}
}