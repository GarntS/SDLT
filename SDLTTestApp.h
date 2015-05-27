#ifndef SDLT_TESTAPP_H
#define SDLT_TESTAPP_H

#include "SDLTApp.h"
#include "SDLTGfx.h"
#include <vector>

////	SECTION: TestApp	////

class TestApp : public SDLTApp
{
public:	
	//Singleton
	static TestApp	*instance;
	
	//TestApp-Specific junk
	TestApp();
	void GetNewWord();
	
	//Inherited from SDLTApp
	void HandleEvent(SDL_Event *event);	
	bool Load();
	void Unload();
	void Update(float dt);
	void Render(float dt);
	
	//Singleton Accessor	
	static TestApp *GetInstance()
	{
		if(!instance)
			instance = new TestApp();
		return instance;
	}
};

////	ENDSECT: TestApp	////

#endif
