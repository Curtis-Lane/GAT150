#pragma once

#include <random>

namespace ane {
	inline void seedRandom(unsigned int seed) {srand(seed);}
	
	inline int random() {return rand();}
	inline int random(unsigned int max) {return rand() % max;} // 0 - (max - 1)
	inline int random(unsigned int min, unsigned int max) {return min + random((max + 1) - min);} // max - min

	inline float randomf() {return ((float) random()) / RAND_MAX;}
	inline float randomf(float max) {return randomf() * max;}
	inline float randomf(float min, float max) {return min + (randomf() * (max - min));}
}