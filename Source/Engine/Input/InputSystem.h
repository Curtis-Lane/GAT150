#pragma once

#include <vector>
#include <array>
#include "SDL2-2.28.0/include/SDL.h"
#include "Core/Vector2.h"

namespace ane {
	class InputSystem {
		public:
			InputSystem() = default;
			~InputSystem() = default;

			bool Initialize();
			void Shutdown();

			void Update();

			bool GetKeyDown(uint32_t key) const {return keyboardState[key];}
			bool GetPreviousKeyDown(uint32_t key) const {return prevKeyboardState[key];}

			const Vector2& GetMousePosition() const {return mousePosition;}

			bool GetMouseButtonDown(uint32_t button) {return mouseButtonState[button];}
			bool GetMousePreviousButtonDown(uint32_t button) {return prevMouseButtonState[button];}

		private:
			std::vector<uint8_t> keyboardState;
			std::vector<uint8_t> prevKeyboardState;

			Vector2 mousePosition;
			std::array<uint8_t, 3> mouseButtonState;
			std::array<uint8_t, 3> prevMouseButtonState;
	};

	extern InputSystem globalInputSystem;
}