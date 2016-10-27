
#pragma once
#include "Header.h"

SDL_Texture* LoadImage(SDL_Renderer* pRen, const std::string ImagePath);
void RenderTexture(SDL_Renderer* pRen, int x, int y, SDL_Texture* pTex, SDL_Rect* pClip = nullptr);
SDL_Texture* RenderText(SDL_Renderer* pRen, std::string msg, std::string fontFile, SDL_Color color, int fontSize);
SDL_Texture* RenderText(SDL_Renderer* pRen, TTF_Font*  pFont, std::string text, SDL_Color color, int fontSize);

struct Button
{
	SDL_Rect Area;
	char* Name;
	void(*CallBack)(Button&);
};

struct Vector2D
{
	float x;
	float y;
	Vector2D(float _x, float _y) :x(_x), y(_y) {}
	Vector2D operator / (const float& value)
	{
		return Vector2D(x / value, y / value);
	}

	Vector2D operator * (const float& value)
	{
		return Vector2D(x * value, y * value);
	}

	Vector2D operator- (const Vector2D& value)
	{
		return Vector2D(x - value.x, y - value.y);
	}

	Vector2D operator+ (const Vector2D& value)
	{
		return Vector2D(x + value.x, y + value.y);
	}
};

struct Line
{
	float x1, y1, x2, y2;
	Line() { x1 = y1 = x2 = y2 = 0; }
	Line(float _x1, float _y1, float _x2, float _y2) : x1(_x1), y1(_y1), x2(_x2), y2(_y2) {}
};

