
#include "Texture2D.h"
#include "Tool.h"
#include "Engine.h"

Textrue2D::Textrue2D(SDL_Renderer* pRen,std::string file)
{
	m_pTex = LoadImage(pRen, file);
	SDL_QueryTexture(m_pTex, nullptr, nullptr, &m_nWidth, &m_nHeight);

	m_File = file;
	AddRef();
}


Textrue2D::~Textrue2D()
{
}

void Textrue2D::AddRef()
{
	m_nRefCount++;
}

void Textrue2D::Release()
{
	if (--m_nRefCount == 0)
	{
		SDL_DestroyTexture(m_pTex);
	}
}