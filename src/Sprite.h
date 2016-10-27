
#pragma once
#include "Header.h"

class Sprite
{
public:
	Sprite();
	~Sprite();

	void Init();
	void Update();
	void Render();
	void Destroy();

	void SetImageFile(const char* ImageFile);
	
	int x, y;
	std::string m_sImageFile;
	SDL_Texture* m_pImage;
};
