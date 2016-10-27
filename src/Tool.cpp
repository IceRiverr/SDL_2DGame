
#include "Tool.h"

SDL_Texture* LoadImage(SDL_Renderer* pRen, const std::string ImagePath)
{

#if 0 // SDL_LoadBMP
	SDL_Surface* pSurface = nullptr;
	SDL_Texture* pTexture = nullptr;

	pSurface = SDL_LoadBMP(ImagePath.c_str());
	if (pSurface)
	{
		pTexture = SDL_CreateTextureFromSurface(pRen, pSurface);
		SDL_FreeSurface(pSurface);
	}
	else
	{
		std::cout << SDL_GetError() << std::endl;
	}

	return pTexture;
#endif

	SDL_Texture* pTex = nullptr;
	pTex = IMG_LoadTexture(pRen, ImagePath.c_str());
	if (pTex == nullptr)
		throw std::runtime_error("Failed to load image" + ImagePath + IMG_GetError());

	return pTex;
}

void RenderTexture(SDL_Renderer* pRen, int x, int y, SDL_Texture* pTex, SDL_Rect* pClip)
{
	SDL_Rect pos;
	pos.x = x;
	pos.y = y;

	if (pClip != nullptr)
	{
		pos.w = pClip->w;
		pos.h = pClip->h;
	}
	else
	{
		SDL_QueryTexture(pTex, NULL, NULL, &pos.w, &pos.h);
	}
	SDL_RenderCopy(pRen, pTex, pClip, &pos);
}

SDL_Texture* RenderText(SDL_Renderer* pRen, std::string msg, std::string fontFile, SDL_Color color, int fontSize)
{
	TTF_Font* pFont = TTF_OpenFont(fontFile.c_str(), fontSize);
	if (pFont == nullptr)
		throw std::runtime_error("Failed to load font: " + fontFile + TTF_GetError());

	SDL_Surface* pSurfaceTex = TTF_RenderText_Blended(pFont, msg.c_str(), color);
	SDL_Texture* pTextTex = SDL_CreateTextureFromSurface(pRen, pSurfaceTex);

	SDL_FreeSurface(pSurfaceTex);
	TTF_CloseFont(pFont);

	return pTextTex;
}

SDL_Texture* RenderText(SDL_Renderer* pRen, TTF_Font*  pFont, std::string text,  SDL_Color color, int fontSize)
{
	SDL_Surface* pSurfaceTex = TTF_RenderText_Blended(pFont, text.c_str(), color);
	SDL_Texture* pTextTex = SDL_CreateTextureFromSurface(pRen, pSurfaceTex);
	SDL_FreeSurface(pSurfaceTex);
	return pTextTex;
}
