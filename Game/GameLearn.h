
#pragma  once
#include "IGame.h"
#include "Window.h"

class GameLearn : public IGame
{
public:
	GameLearn();
	~GameLearn();
	virtual int Init();
	virtual void Update(float dt);
	virtual void Render();
	virtual void Destroy();
	virtual void HandleEvent(SDL_Event& e);
	
private:
	Window* m_pMainWindow;
	SDL_Texture* pBackgroundTex;
	SDL_Texture* pImageTex;
	SDL_Texture* pImage1Tex;
	SDL_Texture* pImageSheetTex;
	SDL_Texture* pTextTex;
	SDL_Texture* pTimeTex;
	SDL_Texture* pCurrImageTex;

	std::string fontPath;

	SDL_Rect clips[4];
	int clipIndex;

	Uint32 time;
	float deltaTime;
	int posX;
	int posY;
	int angle;
};