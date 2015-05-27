#ifndef SDLT_GFX_H
#define SDLT_GFX_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
//#include <SDL2_gfxPrimitives.h>
#include "SDLTMath.h"
#include <string>

using namespace std;

enum SDLTRenderableType
{
	RENDERABLETYPE_TEXTURE,
	RENDERABLETYPE_LABEL,
	RENDERABLETYPE_SPRITESHEET
};

class SDLTRenderable
{
public:
	SDLTRenderable(string uri);

	//Standard Functions
	virtual bool 	Load(SDL_Renderer *renderTarget);
	virtual void 	Unload();
	virtual void 	Render(SDL_Renderer *renderTarget);

	//Getters and Setters
	bool				IsRendering();
	Vector2<int>		GetSize();
	Vector2<float>		GetScale();
	Vector2<int>		GetOrigin();
	Vector2<int>		GetPosition();
	float				GetRotation();
	float				GetAlpha();
	SDLTRenderableType	GetType();
	unsigned int		GetUid();
	SDL_Surface*		GetSurface();

	void				SetRendering(bool value);
	void				SetScale(float x, float y);
	void				SetScale(Vector2<float> newScale);
	void				SetOrigin(Vector2<int> newOrigin);
	void				SetPosition(Vector2<int> newPosition);
	void				CenterOrigin();
	void				SetRotation(float degrees);
	void				SetAlpha(float newAlpha);
	void				SetType(SDLTRenderableType newType);
	void				SetUid(unsigned int newUid);

protected:
	Vector2<int>		*size;
	Vector2<int>		*origin;
	Vector2<int>		*position;
	Vector2<float>		*scale;

	bool				rendering;
	float				rotation;
	float				alpha;
	unsigned int		uid;
	string				fileUri;

	SDL_Surface			*surface;
	SDL_Texture			*texture;
	SDLTRenderableType	type;
};

class SDLTTexture : public SDLTRenderable
{
public:
	SDLTTexture(string uri);

	//Standard Functions
	bool Load(SDL_Renderer *renderTarget);
	void Unload();
	void Render(SDL_Renderer *renderTarget);
};

class SDLTSpriteSheet : public SDLTRenderable
{
public:
	SDLTSpriteSheet(string uri, Vector2<int> texSize);

	void ChangeFrame(int frameNo);
	void CopyFrameToTexture(int frameNo, SDLTTexture *texture);

	//Standard Functions
	bool Load(SDL_Renderer *renderTarget);
	void Unload();
	void Render(SDL_Renderer *renderTarget);

	Vector2<int> 		*texSize;

private:
	Vector2<int>		*srcPos;
	int					numFrames;
};

class SDLTAnimation
{
public:
	SDLTAnimation(SDLTSpriteSheet *sheet, Vector2<int> frameBounds);

	//Getters and Setters
	bool Load(SDL_Renderer *renderTarget);
	void Unload();

private:
	SDLTSpriteSheet		*spriteSheet;
	int					*frames;
};

class SDLTLabel : public SDLTRenderable
{
public:
	SDLTLabel(string labelText, string uri);
	SDLTLabel();

	void UpdateText(string labelText, SDL_Renderer *renderTarget, SDL_Color *color);
	void UpdateFontSize(int size);

	//Standard Functions
	bool Load(SDL_Renderer *renderTarget);
	void Unload();
	void Render(SDL_Renderer *renderTarget);

private:
	string			text;
	TTF_Font		*font;
};

/* Primitives (Unused)

enum SDLTPrimitiveType
{
	RECTANGLE, ROUND_RECTANGLE, LINE_VERT, LINE_HORIZ, ELLIPSE, TRIANGLE
};

class SDLTPrimitive
{
public:
	SDLTPrimitive(SDLTPrimitiveType primitiveType);
	bool Load(SDL_Color renderColor, Vector2<int> renderSize);
	void Unload();
	void Render(SDL_Renderer *renderTarget, Vector2<int> *renderPos);

private:
	//Primitive type
	SDLTPrimitiveType 	type;
	SDL_Color 			color;
	Vector2<int> 		size;
};

*/

#endif
