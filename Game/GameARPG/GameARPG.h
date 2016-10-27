
#pragma once
#include "IGame.h"

class GameARPG : public IGame
{
public:
	GameARPG();
	~GameARPG();

	virtual int Init();
	virtual void Update(float dt);
	virtual void Render();
	virtual void Destroy();
	virtual void HandleEvent(SDL_Event& e);

private:
	SDL_Texture* BgT;
	SDL_Texture* DotT;
	SDL_Rect Camera;
	SDL_Surface* MainWindowSurf;

	int DotX, DotY;
	int VelX, VelY;
	int DotVel;
	int DotSize;
	float DotAngle;
	float AngleVel;
	
	int MapW, MapH;
	int ScreenW, ScreenH;

	Button TestBtn;
	SDL_Texture* TextT;
	int fontW, fontH;
	
	std::string FontPath;
	TTF_Font* Font;
	SDL_Color FontColor;
	int FontSize;

	SDL_Rect InputField;
	char* InputText;
	bool bInputFlag;
	SDL_Texture* InputTextT;
	int InputLength;
	int InputTextW, InputTextH;
};