#include "Time.h"

#include "MathUtils.h"

namespace ane {
	Time globalTime;

	void Time::Tick() {
		clock_duration duration = clock::now() - this->startTime;
		this->time = duration.count() / static_cast<float>(clock_duration::period::den);

		duration = clock::now() - this->frameTime;
		this->deltaTime = duration.count() / static_cast<float>(clock_duration::period::den);
		this->deltaTime = Min(this->deltaTime, 1.0f);

		this->frameTime = clock::now();
	}

	Time::clock_rep Time::GetElapsedNanoseconds() {
		return std::chrono::duration_cast<std::chrono::nanoseconds>(clock::now() - this->startTime).count();
	}

	Time::clock_rep Time::GetElapsedMicroseconds() {
		return std::chrono::duration_cast<std::chrono::microseconds>(clock::now() - this->startTime).count();
	}

	Time::clock_rep Time::GetElapsedMilliseconds() {
		return std::chrono::duration_cast<std::chrono::milliseconds>(clock::now() - this->startTime).count();
	}

	float Time::GetElapsedSeconds() {
		return (clock::now() - this->startTime).count() / static_cast<float>(clock_duration::period::den);
	}
}

