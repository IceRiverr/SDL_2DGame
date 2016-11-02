
#include "Sprite.h"


Sprite::Sprite()
	: x(0), y(0), angle(0), w(-1), h(-1)
{

}

Sprite::~Sprite()
{
	Destroy();
}

void Sprite::Init()
{

}

void Sprite::Draw(Camera* pCam)
{
	//SDL_Rect drawRect;
	if (pCam == nullptr)
	{
		//drawRect = {};

		//SDL_RenderCopyEx(Engine::get)
	}
}

void Sprite::Destroy()
{
	SDL_DestroyTexture(m_pTexture);
}
