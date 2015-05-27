#include "SDLTApp.h"

////	SECTION: SDLTApp	////

SDLTApp::SDLTApp()
{
	window = nullptr;
	renderTarget = nullptr;
	width = 800;
	height = 600;
	
	running = true;
	canRender = true;
	
	commandQueue = new std::vector<B2DCommand*>();
}

int SDLTApp::Run()
{
	srand(time(NULL));
	if(!Load())
		return -1;
		
	SDL_Event ev;
	while(running)
	{
		static long prevTime = 0;
		float deltaTime = 0.0;
		long currTime = SDL_GetTicks();
		
		if(currTime >prevTime)
		{
			deltaTime = ((float)(currTime - prevTime)) / 1000;
			prevTime = currTime;
		}
		
		while(SDL_PollEvent(&ev))
			HandleEvent(&ev);
			
		Update(deltaTime);
		Render(deltaTime);
		
		//Update Box2D world
		world->Step(1.0f / 60.0f, 6, 2);
	}
	
	return 0;
}

bool SDLTApp::Load()
{
	//Init SDL
	if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
		return false;
	
	//Init SDL_TTF	
	if(TTF_Init() < 0)
		return false;
	
	//Init SDL_IMG
	int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
	if(IMG_Init(imgFlags) != imgFlags)
		return false;
	
	//Create Window and Renderer
	window = SDL_CreateWindow(	"SDLT App",
								SDL_WINDOWPOS_CENTERED,
								SDL_WINDOWPOS_CENTERED,
								width, height,
								SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
	if(window == NULL)
		return false;
		
	renderTarget = SDL_CreateRenderer(	window,
										-1,
										SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
										
	if(renderTarget == NULL)
		return false;
		
	//Create B2D World
	b2Vec2 gravity = b2Vec2(0, -9.8);
	
	world = new b2World(gravity);
	
	//Initialize Lua
	luaState = luaL_newstate();
	luaL_openlibs(luaState);
	
	return true;
}

void SDLTApp::Unload()
{
	//Kill Lua
	lua_close(luaState);
	
	//Kill SDL Objects
	SDL_DestroyRenderer(renderTarget);
	SDL_DestroyWindow(window);
	
	//Kill B2D
	delete world;
	
	renderTarget = nullptr;
	window = nullptr;
	
	//Kill SDL Libs
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

void SDLTApp::HandleEvent(SDL_Event *event)
{

}

void SDLTApp::Update(float dt)
{
	
}

void SDLTApp::Render(float dt)
{
	
}

Vector2<int> SDLTApp::WorldToScreen(Vector2<float> og)
{
	float pixelsPerMeter = 50; //50 pixels per meter
	int offsetX = width / 2;
	
	return Vector2<int>(	offsetX + (int)(og.x * pixelsPerMeter),
							height - (int)(og.y * pixelsPerMeter));
}

Vector2<float> SDLTApp::ScreenToWorld(Vector2<int> og)
{
	float metersPerPixel = 1/50; //50 pixels per meter
	float offsetX = width / 2;
	
	return Vector2<float>(	offsetX + ((float)og.x * metersPerPixel),
							height - ((float)og.y * metersPerPixel));
}

void SDLTApp::SetWindowTitle(std::string title)
{
	SDL_SetWindowTitle(window, title.c_str());
}

void SDLTApp::PushCommand(B2DCommand *command)
{
	commandQueue->push_back(command);
}
////	ENDSECT: SDLTApp	////

////	SECTION: B2DCommand	////
/*
void B2DCommand::Act()
{
	MessageBoxA(NULL, "ALERT", "ALERT", 0x00000000L);
}
*/
std::string	B2DCommand::GetType()
{
	return type;
}

////	ENDSECT: B2DCommand	////
