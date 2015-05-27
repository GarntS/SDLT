#include "SDLTTestApp.h"

////	SECTION: TestApp	////

TestApp* TestApp::instance = nullptr;

TestApp::TestApp()
{
	SDLTApp();
}

bool TestApp::Load()
{
	if(!SDLTApp::Load())
		return false;

	//	SDLT INITIALIZATION	//
	//	END SDLT INTIALIZATION	//

	//	B2D INITIALIZATION	//
	//	END B2D INITIALIZATION	//

	//	GAME INITIALIZATION	//
	//	END GAME INITIALIZATION	//

	return true;
}

void TestApp::Unload()
{
	SDLTApp::Unload();
}

void TestApp::HandleEvent(SDL_Event *event)
{
	switch(event->type)
	{
		case SDL_QUIT:
			running = false;
			break;
		case SDL_KEYDOWN:
			break;
	}
}

void TestApp::Update(float dt)
{

}

void TestApp::Render(float dt)
{
	if(canRender)
	{
		SDL_RenderClear(renderTarget);
			//CUSTOM RENDER CODE
		SDL_RenderPresent(renderTarget);
	}
}

////	ENDSECT: TestApp	////
