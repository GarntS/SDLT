#include "SDLTGfx.h"

////	SECTION: SDLTRenderable	////

SDLTRenderable::SDLTRenderable(string uri)
{
	texture = nullptr;
	fileUri = uri;
	rotation = 0.0f;
	size = new Vector2<int>(-1, -1);
	origin = new Vector2<int>(0, 0);
	scale = new Vector2<float>(1.0f, 1.0f);
	position = new Vector2<int>(0.0f, 0.0f);
	uid = GenerateUid();
	rendering = true;
}

bool SDLTRenderable::Load(SDL_Renderer *renderTarget)
{
}

void SDLTRenderable::Unload()
{
}

void SDLTRenderable::Render(SDL_Renderer *renderTarget)
{
}

bool SDLTRenderable::IsRendering()
{
	return rendering;
}

Vector2<int> SDLTRenderable::GetSize()
{
	return *size;
}

Vector2<float> SDLTRenderable::GetScale()
{
	return *scale;
}

Vector2<int> SDLTRenderable::GetOrigin()
{
	return *origin;
}

Vector2<int> SDLTRenderable::GetPosition()
{
	return *position;
}

float SDLTRenderable::GetRotation()
{
	return rotation;
}

float SDLTRenderable::GetAlpha()
{
	return alpha;
}

SDLTRenderableType SDLTRenderable::GetType()
{
	return type;
}

unsigned int SDLTRenderable::GetUid()
{
	return uid;
}

SDL_Surface* SDLTRenderable::GetSurface()
{
	return surface;
}

//

void SDLTRenderable::SetRendering(bool value)
{
	rendering = value;
}

void SDLTRenderable::SetRotation(float degrees)
{
	rotation = degrees;
}

void SDLTRenderable::SetAlpha(float newAlpha)
{
	alpha = newAlpha;
	SDL_SetTextureAlphaMod(texture, alpha);
}

void SDLTRenderable::SetScale(float x, float y)
{
	scale->x = x;
	scale->y = y;
}

void SDLTRenderable::SetScale(Vector2<float> newScale)
{
	SafeDelete(scale);
	scale = new Vector2<float>(newScale);
}

void SDLTRenderable::SetOrigin(Vector2<int> og)
{
	SafeDelete(origin);
	origin = new Vector2<int>(og);
}

void SDLTRenderable::SetPosition(Vector2<int> newPosition)
{
	SafeDelete(position);
	position = new Vector2<int>(newPosition);
}

void SDLTRenderable::CenterOrigin()
{
	rendering = false;
	SafeDelete(origin);
	origin = new Vector2<int>(size->x/2, size->y/2);
	rendering = true;
}

void SDLTRenderable::SetType(SDLTRenderableType newType)
{
	type = newType;
}

void SDLTRenderable::SetUid(unsigned int newUid)
{
	uid = newUid;
}

////	ENDSECT: SDLTRenderable	////

////	SECTION: SDLTTexture	////

SDLTTexture::SDLTTexture(string uri) : SDLTRenderable(uri)
{
	type = RENDERABLETYPE_TEXTURE;
}

bool SDLTTexture::Load(SDL_Renderer *renderTarget)
{
	surface = IMG_Load(fileUri.c_str());

	if(surface == NULL)
		return false;

	texture = SDL_CreateTextureFromSurface(renderTarget, surface);
	SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);

	if(texture == NULL)
		return false;

	SDL_QueryTexture(texture, NULL, NULL, &size->x, &size->y);

	//SDL_FreeSurface(surface);

	return true;
}

void SDLTTexture::Unload()
{
	SDL_DestroyTexture(texture);
	texture = nullptr;
}

void SDLTTexture::Render(SDL_Renderer *renderTarget)
{
	if(rendering)
	{
		SDL_Rect rect = {	position->x - origin->x,
							position->y - origin->y,
							(int)((float)size->x * scale->x),
							(int)((float)size->y * scale->y)};

		SDL_Rect src = {0, 0, size->x, size->y};

		SDL_RenderCopyEx(renderTarget, texture, &src, &rect, rotation, NULL, SDL_FLIP_NONE);
	}
}

////	ENDSECT: SDLTTexture	////

////	SECTION: SDLTSpriteSheet	////

SDLTSpriteSheet::SDLTSpriteSheet(string uri, Vector2<int> textureSize) : SDLTRenderable(uri)
{
	type = RENDERABLETYPE_SPRITESHEET;
	texSize = new Vector2<int>(textureSize);
	srcPos = new Vector2<int>(0, 0);
}

void SDLTSpriteSheet::ChangeFrame(int frameNo)
{
	srcPos->y = (frameNo * texSize->x) / size->x;
	srcPos->x = (frameNo * texSize->x) % size->x;
}

void SDLTSpriteSheet::CopyFrameToTexture(int frameNo, SDLTTexture *texture)
{
    SDL_Rect srcRect = {srcPos->x, srcPos->y, texSize->x, texSize->y};
    SDL_Rect destRect = {0, 0, texSize->x, texSize->y};
	SDL_BlitSurface(surface, &srcRect, texture->GetSurface(), &destRect);
}

bool SDLTSpriteSheet::Load(SDL_Renderer *renderTarget)
{
	surface = IMG_Load(fileUri.c_str());

	if(surface == NULL)
		return false;

	texture = SDL_CreateTextureFromSurface(renderTarget, surface);
	SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);

	if(texture == NULL)
		return false;

	SDL_QueryTexture(texture, NULL, NULL, &size->x, &size->y);

	numFrames = (size->x / texSize->x) * (size->x / texSize->y);

	//SDL_FreeSurface(surface);

	return true;
}

void SDLTSpriteSheet::Unload()
{
	SDL_DestroyTexture(texture);
	texture = nullptr;
}

void SDLTSpriteSheet::Render(SDL_Renderer *renderTarget)
{
	if(rendering)
	{
		SDL_Rect rect = {	position->x - origin->x,
							position->y - origin->y,
							(int)((float)texSize->x * scale->x),
							(int)((float)texSize->y * scale->y)};

		SDL_Rect src = {srcPos->x, srcPos->y, texSize->x, texSize->y};

		SDL_RenderCopyEx(renderTarget, texture, &src, &rect, rotation, NULL, SDL_FLIP_NONE);
	}
}

////	ENDSECT: SDLTSpriteSheet	////

////	SECTION: SDLTAnimation		////

SDLTAnimation::SDLTAnimation(SDLTSpriteSheet *sheet, Vector2<int> frameBounds)
{
	spriteSheet = sheet;
	frames = new int[frameBounds.y - frameBounds.x];
	for(int i = 0; i < (frameBounds.y - frameBounds.x); i++)
		frames[i] = frameBounds.x + i;
} 

//Getters and Setters
bool SDLTAnimation::Load(SDL_Renderer *renderTarget)
{

}

void SDLTAnimation::Unload()
{

}

////	ENDSECT: SDLTAnimation		////

////	SECTION: SDLTLabel		////

SDLTLabel::SDLTLabel(string labelText, string uri) : SDLTRenderable(uri)
{
	text = labelText;
	type = RENDERABLETYPE_LABEL;
}

bool SDLTLabel::Load(SDL_Renderer *renderTarget)
{
	font = TTF_OpenFont(fileUri.c_str(), 20);

	if(font == NULL)
		return false;

	SDL_Color color = {220, 220, 220, 255};

	surface = TTF_RenderText_Solid(font, text.c_str(), color);

	if(surface == NULL)
		return false;

	texture = SDL_CreateTextureFromSurface(renderTarget, surface);
	SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);

	if(texture == NULL)
		return false;

	SDL_QueryTexture(texture, NULL, NULL, &size->x, &size->y);

	return true;
}

void SDLTLabel::Unload()
{
	TTF_CloseFont(font);
	SDL_DestroyTexture(texture);
	texture = nullptr;
}

void SDLTLabel::UpdateText(string labelText, SDL_Renderer *renderTarget, SDL_Color *color)
{
	text = labelText;
	SDL_Color renderColor;

	if(color == NULL)
		renderColor = {220, 220, 220, 255};
	else renderColor=  *color;

	surface = TTF_RenderText_Solid(font, text.c_str(), renderColor);

	texture = SDL_CreateTextureFromSurface(renderTarget, surface);
	SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);

	SDL_QueryTexture(texture, NULL, NULL, &size->x, &size->y);
}

void SDLTLabel::UpdateFontSize(int size)
{
	rendering = false;
	TTF_CloseFont(font);
	TTF_OpenFont(fileUri.c_str(), size);
	rendering = true;
}

void SDLTLabel::Render(SDL_Renderer *renderTarget)
{
	if(rendering)
	{
		int renderHeight;
		SDL_GetRendererOutputSize(renderTarget, NULL, &renderHeight);

		SDL_Rect rect = {	position->x,
							position->y,
							(int)((float)size->x * scale->x),
							(int)((float)size->y * scale->y)};
		SDL_RenderCopy(renderTarget, texture, NULL, &rect);
	}
}

////	ENDSECT: SDLTLabel	////

/*//	SECTION: SDLTPrimitive	////

<-- THIS SECTION IS CURRENTLY BROKEN, IT'S AN OFFICIAL todo() -->

SDLTPrimitive::SDLTPrimitive(SDLTPrimitiveType primitiveType)
{
	type = primitiveType;
}

bool SDLTPrimitive::Load(SDL_Color renderColor, Vector2<int> renderSize)
{
	color = renderColor;
	size = renderSize;
}

void SDLTPrimitive::Unload()
{

}

void SDLTPrimitive::Render(SDL_Renderer *renderTarget, Vector2<int> *renderPos)
{
	switch(type)
	{
		case RECTANGLE:
			rectangleRGBA(	renderTarget,
							renderPos->x, renderPos->y,
							renderPos->x + size.x, renderPos->y + size.y,
							color.r, color.g, color.b, color.a);
			break;
		case ROUND_RECTANGLE:
			roundedRectangleRGBA(	renderTarget,
									renderPos->x, renderPos->y,
									renderPos->x + size.x, renderPos->y + size.y,
									size.y / 8, color.r, color.g, color.b, color.a);
			break;
		case LINE_VERT:
			thickLineRGBA(	renderTarget,
							renderPos->x, renderPos->y,
							renderPos->x, renderPos->y + size.y,
							3, color.r, color.g, color.b, color.a);
			break;
		case LINE_HORIZ:
			thickLineRGBA(	renderTarget,
							renderPos->x, renderPos->y,
							renderPos->x + size.x, renderPos->y,
							3, color.r, color.g, color.b, color.a);
			break;
		case ELLIPSE:
			filledEllipseRGBA(	renderTarget,
								renderPos->x + (size.x/2), renderPos->y + (size.y/2),
								size.x/2, size.y/2,
								color.r, color.g, color.b, color.a);
			break;
		case TRIANGLE:
			filledTrigonRGBA(	renderTarget,
								renderPos->x, renderPos->y + size.y,
								renderPos->x + (size.x / 2), renderPos->y,
								renderPos->x + size.x, renderPos->y + size.y,
								color.r, color.g, color.b, color.a);
			break;
	}
}

////	ENDSECT: SDLTPrimitive	//*/
