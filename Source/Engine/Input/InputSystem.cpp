#include "InputSystem.h"

namespace ane {
	InputSystem globalInputSystem;

	bool InputSystem::Initialize() {
		int numKeys;
		// Get pointer to SDL keyboard states and number of keys
		const uint8_t* keyboardState = SDL_GetKeyboardState(&numKeys);

		// Resize of keyboard state vector using numKeys for size
		this->keyboardState.resize(numKeys);

		// Copy the SDL key states to keyboard state
		std::copy(keyboardState, keyboardState + numKeys, this->keyboardState.begin());

		// Set previous keyboard state
		this->prevKeyboardState = this->keyboardState;

		return true;
	}

	void InputSystem::Shutdown() {
	}

	void InputSystem::Update() {
		// Update SDL events
		SDL_Event event;
		SDL_PollEvent(&event);

		// Save previous keyboard state
		this->prevKeyboardState = this->keyboardState;

		// Get SDL keyboard state
		const uint8_t* keyboardState = SDL_GetKeyboardState(nullptr);
		// Copy SDL keyboard state to input system keyboard state
		std::copy(keyboardState, keyboardState + this->keyboardState.size(), this->keyboardState.begin());

		//
		int x, y;
		uint32_t buttons = SDL_GetMouseState(&x, &y);
		this->mousePosition = Vector2{x, y};

		this->prevMouseButtonState = this->mouseButtonState;

		this->mouseButtonState[0] = buttons & SDL_BUTTON_LMASK; // buttons [0001] & [0RML]
		this->mouseButtonState[1] = buttons & SDL_BUTTON_MMASK; // buttons [0010] & [0RML]
		this->mouseButtonState[2] = buttons & SDL_BUTTON_RMASK; // buttons [0100] & [0RML]
	}
}