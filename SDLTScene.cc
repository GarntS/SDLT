#include "SDLTScene.h"

////	SECTION: SDLTScene////

SDLTScene::SDLTScene()
{
	
}
	
////

bool SDLTScene::Load(SDL_Renderer *renderTarget)
{
	
}

void SDLTScene::Unload()
{
	for(int i = 0; i < renderables.size(); i++)
		renderables[i]->Unload();
}

void SDLTScene::Update(float dt)
{
	
}

void SDLTScene::Render(SDL_Renderer *renderTarget)
{
	
}
			
////
				
vector<SDLTRenderable*> SDLTScene::GetRenderablesOfType(SDLTRenderableType type)
{
	vector<SDLTRenderable*> ofType;
	
	for(int i = 0; i < renderables.size(); i++)
		if(renderables[i]->GetType() == type)
			ofType.push_back(renderables[i]);
	return ofType;
}

SDLTRenderable*	SDLTScene::GetRenderableWithUid(unsigned int uid)
{
	for(int i = 0; i < renderables.size(); i++)
		if(uid == *reinterpret_cast<unsigned int*>(renderables[i]->GetUid()))
	 		return renderables[i];
	return nullptr;
}

b2Body* SDLTScene::GetBodyWithUid(unsigned int uid)
{
	for(int i = 0; i < bodies.size(); i++)
		if(uid == *reinterpret_cast<unsigned int*>(bodies[i]->GetUserData()))
	 		return bodies[i];
	return nullptr;
}

b2Fixture* SDLTScene::GetFixtureWithUid(unsigned int uid)
{
	for(int i = 0; i < fixtures.size(); i++)
		if(uid == *reinterpret_cast<unsigned int*>(fixtures[i]->GetUserData()))
	 		return fixtures[i];
	return nullptr;
}

////
	
vector<SDLTRenderable*> SDLTScene::GetRenderables()
{
	return renderables;
}

vector<b2Body*> SDLTScene::GetBodies()
{
	return bodies;
}

vector<b2Fixture*> SDLTScene::GetFixtures()
{
	return fixtures;
}

////
	
unsigned int SDLTScene::AddRenderable(SDLTRenderable *renderable)
{
	renderables.push_back(renderable);
	return renderable->GetUid();
}

unsigned int SDLTScene::AddBody(b2Body *body)
{
	bodies.push_back(body);
	if(body->GetUserData())
		return *reinterpret_cast<unsigned int*>(body->GetUserData());
	return 0;
}

unsigned int SDLTScene::AddFixture(b2Fixture*fixture)
{
	fixtures.push_back(fixture);
	if(fixture->GetUserData())
		return *reinterpret_cast<unsigned int*>(fixture->GetUserData());
	return 0;
}

////
	
void SDLTScene::RemoveRenderable(SDLTRenderable *renderable)
{
	for(int i = 0; i < renderables.size(); i++)
		if(renderables[i] == renderable)
			renderables.erase(renderables.begin() + i);
}

void SDLTScene::RemoveBody(b2Body *body)
{
	for(int i = 0; i < bodies.size(); i++)
		if(bodies[i] == body)
			bodies.erase(bodies.begin() + i);
}

void SDLTScene::RemoveFixture(b2Fixture *fixture)
{
	for(int i = 0; i < fixtures.size(); i++)
		if(fixtures[i] == fixture)
			fixtures.erase(fixtures.begin() + i);
}

////	ENDSECT: SDLTScene	////

////	SECTION: SDLTSceneManager	////

//Initialize the singleton
SDLTSceneManager* SDLTSceneManager::instance = nullptr;

SDLTSceneManager::SDLTSceneManager()
{
	transitioning = false;
	scene = new SDLTScene();
	newScene = nullptr;
}

//Standard Functions
bool SDLTSceneManager::Load(SDL_Renderer *renderTarget)
{
	instance->scene->Load(renderTarget);
}

void SDLTSceneManager::Unload()
{
	if(instance->newScene)
		instance->newScene->Unload();
	instance->scene->Unload();
}

void SDLTSceneManager::Update(float dt)
{
	static float timeRemaining;
	if(instance->transitioning)
	{
		if(timeRemaining <= 0)
			timeRemaining = instance->transTime;
		
		float desiredAlpha = (dt / timeRemaining) * (1 / instance->transTime);
		
		for(int i = 0; i < instance->scene->GetRenderables().size(); i++)
			instance->scene->GetRenderables()[i]->SetAlpha(desiredAlpha);
			
		timeRemaining -= dt;
		if(timeRemaining <= 0)
		{
			instance->transitioning = false;
			instance->scene->Unload();
			SafeDelete(instance->scene);
			instance->scene = instance->newScene;
			instance->newScene = nullptr;
		}
	}
}

void SDLTSceneManager::Render(SDL_Renderer *renderTarget)
{
	for(int i = 0; i < instance->scene->GetRenderables().size(); i++)
		instance->scene->GetRenderables()[i]->Render(renderTarget);
}
	
////	

void SDLTSceneManager::TransitionScene(SDLTScene *nextScene, SDL_Renderer *renderTarget, float transitionTime)
{
	if(instance->transitioning = true)
		return;
	
	instance->newScene = nextScene;
	instance->newScene->Load(renderTarget);
	 
	instance->transTime = transitionTime;
	instance->transitioning = true;
}
	
////

SDLTScene* SDLTSceneManager::GetScene()
{
	return GetInstance()->scene;
}

SDLTSceneManager* SDLTSceneManager::GetInstance()
{
	if(!SDLTSceneManager::instance)
		SDLTSceneManager::instance = new SDLTSceneManager();
	return SDLTSceneManager::instance;
}

////	ENDSECT: SDLTSceneManager	////
