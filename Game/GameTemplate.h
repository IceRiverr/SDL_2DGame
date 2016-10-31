
#include "IGame.h"
#include "Window.h"

class GameTemplate : public IGame
{
public:
	GameTemplate();
	~GameTemplate();

	virtual int Init();
	virtual void Update(float dt);
	virtual void Render();
	virtual void Destroy();
	virtual void HandleEvent(SDL_Event& e);

private:
	Window* m_pMainWindow;
	SDL_Texture* BgT;
	SDL_Texture* DotT;
	SDL_Rect Camera;

	int DotX, DotY;
	int VelX, VelY;
	int DotVel;
	int DotSize;
	float DotAngle;
	float AngleVel;
	
	int MapW, MapH;
};