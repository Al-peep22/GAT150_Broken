#include "InputSystem.h"
#include <SDL3/SDL.h>

using namespace std;

namespace viper {
	bool InputSystem::Initialize()
	{
		int numKeys;
		const bool* keyboardState = SDL_GetKeyboardState(&numKeys);
		
		this->keyboardState.resize(numKeys);
		copy(keyboardState, keyboardState + numKeys, this->keyboardState.begin());
		this->prevKeyboardState = this->keyboardState;

		SDL_GetMouseState(&this->mousePosition.x, &this->mousePosition.y);
		this->prevMousePosition = this->mousePosition;

		return true;
	}
	void InputSystem::ShutDown()
	{

	}
	void InputSystem::Update()
	{
		//keyboard input
		this->prevKeyboardState = this->keyboardState;
		const bool* keyboardState = SDL_GetKeyboardState(nullptr);
		copy(keyboardState, keyboardState + this->keyboardState.size(), this->keyboardState.begin());

		//mouse input
		this->prevMousePosition = this->mousePosition;

		this->prevMouseButtonState = this->mouseButtonState;
		uint32_t mouseButtonState = SDL_GetMouseState(&this->mousePosition.x,&this->mousePosition.y);
		
        this->mouseButtonState[static_cast<size_t>(MouseButton::Left)] = mouseButtonState & SDL_BUTTON_LMASK;  
        this->mouseButtonState[static_cast<size_t>(MouseButton::Middle)] = mouseButtonState & SDL_BUTTON_MMASK;  
        this->mouseButtonState[static_cast<size_t>(MouseButton::Right)] = mouseButtonState & SDL_BUTTON_RMASK;
	}
}