#ifndef SDLT_SCENE_H
#define SDLT_SCENE_H

#include "SDLTGfx.h"
#include "SDLTMath.h"
#include <vector>
#include <Box2D.h>

class SDLTScene
{
public:
	SDLTScene();
	
	//Standard Functions
	bool Load(SDL_Renderer *renderTarget);
	void Unload();
	void Update(float dt);
	void Render(SDL_Renderer *renderTarget);
				
	//Other functions
	vector<SDLTRenderable*>	GetRenderablesOfType(SDLTRenderableType type);
	SDLTRenderable*			GetRenderableWithUid(unsigned int uid);
	b2Body*					GetBodyWithUid(unsigned int uid);
	b2Fixture*				GetFixtureWithUid(unsigned int uid);
	
	//Accessor Functions
	vector<SDLTRenderable*>	GetRenderables();
	vector<b2Body*>			GetBodies();
	vector<b2Fixture*>		GetFixtures();
	
	unsigned int			AddRenderable(SDLTRenderable *renderable);
	unsigned int			AddBody(b2Body *body);
	unsigned int			AddFixture(b2Fixture *fixture);
	
	void					RemoveRenderable(SDLTRenderable *renderable);
	void					RemoveBody(b2Body *body);
	void					RemoveFixture(b2Fixture *fixture);
	
private:
	vector<SDLTRenderable*>	renderables;
	vector<b2Body*>			bodies;
	vector<b2Fixture*>		fixtures;
};

class SDLTSceneManager
{
public:	
	SDLTSceneManager();

	//Standard Functions
	static bool Load(SDL_Renderer *renderTarget);
	static void Unload();
	static void Update(float dt);
	static void Render(SDL_Renderer *renderTarget);
	
	//Other Methods
	static void TransitionScene(SDLTScene *newScene, SDL_Renderer *renderTarget, float transitionTime = 1.0f);
	
	//Accessor Methods
	static SDLTScene			*GetScene();
	static SDLTSceneManager		*GetInstance();
	
private:
	static SDLTSceneManager	*instance;
	
	SDLTScene	*scene;
	SDLTScene	*newScene;
	bool		transitioning;
	float		transTime;
};

#endif
