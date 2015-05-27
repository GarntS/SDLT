#include "SDLTKeyboard.h"

SDLTKeyboard* SDLTKeyboard::instance = nullptr;

SDLTKeyboard::SDLTKeyboard()
{
	keys = SDL_GetKeyboardState(NULL);
}

SDLTKeyboard* SDLTKeyboard::GetInstance()
{
	if(!instance)
		instance = new SDLTKeyboard();
	return instance;
}

Uint8 SDLTKeyboard::isKeyDown(int key)
{
	return GetInstance()->keys[key];
}
