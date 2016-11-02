
#pragma once
#include "Header.h"
#include "Camera.h"
#include "Engine.h"

class Sprite
{
public:
	Sprite();
	~Sprite();

	void Init();
	void Draw(Camera* pCam = nullptr);
	void Destroy();

	void SetTexure(SDL_Texture* pTex)
	{
		if(m_pTexture!= pTex)
			m_pTexture = pTex;
	}

	float x, y, angle;
	int w, h;
private:
	
	SDL_Texture* m_pTexture;
};
