
#include "Sprite.h"

Sprite::Sprite()
	: m_pImage(nullptr)
	, x(0)
	, y(0)
{

}

Sprite::~Sprite()
{

}

void Sprite::Init()
{

}

void Sprite::Update()
{

}

void Sprite::Render()
{

}

void Sprite::Destroy()
{

}

void Sprite::SetImageFile(const char* ImageFile)
{
	m_sImageFile = std::string(ImageFile);
}