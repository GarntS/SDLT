#ifndef SDLT_KEYBOARD_H
#define SDLT_KEYBOARD_H

#include "SDL.h"

class SDLTKeyboard
{
public:
	SDLTKeyboard();
	
	static SDLTKeyboard* GetInstance();
	static Uint8 isKeyDown(int key);
	
private:
	static SDLTKeyboard	*instance;
	const Uint8			*keys;	
};

#endif
