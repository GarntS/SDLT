#ifndef SDLTAPP_H
#define SDLTAPP_H

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "SDLTMath.h"
#include "SDLTScene.h"
#include "SDLTLua.h"
#include "windows.h"
#include "Box2D.h"
#include <vector>
#include <string>
#include <ctime>

////	SECTION: B2DCommand	////

class B2DCommand
{
protected:
	std::string		type;
	
public:	
	std::string		GetType();
	virtual	void	Act() = 0;
};

////	ENDSECT: B2DCommand	////

////	SECTION: SDLTApp	////

class SDLTApp
{
public:	
	SDLTApp();
	int Run();
	
	//SDL Wrapper Functions
	virtual bool Load();
	virtual void Unload();
	virtual void HandleEvent(SDL_Event *event);
	virtual void Update(float dt);
	virtual void Render(float dt);
	
	//Custom Functions
	Vector2<int> WorldToScreen(Vector2<float> og);
	Vector2<float> ScreenToWorld(Vector2<int> og);
	void SetWindowTitle(std::string title);
	void PushCommand(B2DCommand *command);
	
protected:
	 //Primitive Fields
	 bool 			running;
	 bool			canRender;
	 int			width;
	 int			height;
	 
	 //SDL Fields
	 SDL_Window		*window;
	 SDL_Renderer	*renderTarget;
	 
	 //B2D Fields
	 b2World		*world;
	 
	 //Lua Fields
	 lua_State		*luaState;
	 
	 //Custom Fields
	 std::vector<B2DCommand*>	*commandQueue;
};

////	ENDSECT: SDLTApp	////

#endif
