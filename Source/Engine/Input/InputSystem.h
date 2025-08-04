#pragma once
#include "../Math/Vector2.h"
#include <vector>
#include <array>

using namespace std;

namespace viper {
	class InputSystem {
	public:
		InputSystem() = default;
		enum class MouseButton {
			Left,
			Middle,
			Right
		};
		
		enum class Direction {
			Left,
			Right
		};

		//int i = MouseButton::Right;

		bool Initialize();
		void ShutDown();

		void Update();

		//KEYBOARD INPUT
		bool GetKeyDown(uint8_t key) const { return this->keyboardState[key]; }
		bool GetPrevKeyDown(uint8_t key) const { return this->prevKeyboardState[key]; }
		bool GetKeyPressed(uint8_t key) const { return !this->prevKeyboardState[key] && this->keyboardState[key]; }
		bool GetKeyReleased(uint8_t key) const { return this->prevKeyboardState[key] && !this->keyboardState[key]; }

		const vec2& GetMousePosition() const { return this->mousePosition; }
		const vec2& GetPrevMousePosition() const { return this->prevMousePosition; }

		//MOUSE INPUT
		bool GetMouseButtonDown(MouseButton button) { return this->mouseButtonState[static_cast<size_t>(button)]; }
		bool GetPrevMouseButtonDown(MouseButton button) { return this->prevMouseButtonState[static_cast<size_t>(button)]; }
		bool GetMouseButtonPressed(MouseButton button) {  return !this->prevMouseButtonState[static_cast<size_t>(button)] && this->mouseButtonState[static_cast<size_t>(button)]; }
		bool GetMouseButtonReleased(MouseButton button) {  return this->prevMouseButtonState[static_cast<size_t>(button)] && !this->mouseButtonState[static_cast<size_t>(button)];}		

	public:

	private:
		vector<bool> keyboardState;
		vector<bool> prevKeyboardState;

		vec2 mousePosition{0,0};
		vec2 prevMousePosition{0,0};

		array<bool,3> mouseButtonState{false, false, false};
		array<bool, 3> prevMouseButtonState{false, false, false};
	};

}