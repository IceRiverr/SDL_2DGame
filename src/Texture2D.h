
#pragma once
#include "Header.h"

class Textrue2D
{
public:
	Textrue2D(SDL_Renderer* pRen ,std::string file);
	~Textrue2D();

	void AddRef();
	void Release();

public:
	int m_nWidth;
	int m_nHeight;
	SDL_Texture* m_pTex;
	SDL_Rect m_SrcRect;

private:
	std::string m_File;
	int m_nRefCount;
};