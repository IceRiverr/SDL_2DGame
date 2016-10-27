#pragma once
#include "Header.h"
#include "Engine.h"
#include "Tool.h"

class IGame
{
public:
	IGame() {}
	virtual ~IGame() {}
	virtual int Init() = 0;
	virtual void Update(float dt) = 0;
	virtual void Render() = 0;
	virtual void Destroy() = 0;
	virtual void HandleEvent(SDL_Event& e) = 0;
private:
};

class GameInfo
{
	int ScreenWidth;
	int ScreenHeight;
	char* TitleName;
};

