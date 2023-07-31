#pragma once

#include <chrono>

namespace ane {
	class Time {
	private:
		using clock = std::chrono::high_resolution_clock;
		using clock_duration = clock::duration;
		using clock_rep = clock::rep;

	public:
		Time() : 
			startTime{ clock::now() },
			frameTime{ clock::now() }
		{}

		void Tick();
		void Reset() { this->startTime = clock::now(); }

		clock_rep GetElapsedNanoseconds();
		clock_rep GetElapsedMicroseconds();
		clock_rep GetElapsedMilliseconds();
		float GetElapsedSeconds();

		float GetTime() const {return this->time;}
		float GetDeltaTime() const {return this->deltaTime * this->timeScale;}
		float GetUnscaledDeltaTime() const {return this->deltaTime;}

		float GetTimeScale() const {return this->timeScale;}
		void SetTimeScale(float timeScale) {this->timeScale = timeScale;}

	private:
		float time;
		float deltaTime;
		float timeScale = 1;

		clock::time_point startTime;
		clock::time_point frameTime;
	};

	extern Time globalTime;
}